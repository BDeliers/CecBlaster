//      INCLUDES
#include "AppLog.h"
#include "AppCec.h"
#include "AppRemote.h"

#include "log.h"

#include "stm32h5xx_hal.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "timers.h"

#include <string.h>

//      LOCAL TYPEDEFS AND ENUMS

//      EXTERN VARIABLES

//      LOCAL VARIABLES
static bool             audio_on                = false;
static uint8_t          last_user_control       = 0xFF;

static TimerHandle_t    timer_ir_delayed_key    = NULL;
static APP_REMOTE_KEYS  ir_delayed_key          = KEY_COUNT;

//      STATIC FUNCTIONS PROTOTYPES
static void Cec_Clbk(CEC_COMMAND* cmd);

static void IrDelayedKey_Clbk(TimerHandle_t pxTimer);

//      STATIC FUNCTIONS DEFINITION

/// @brief      CEC callback function, called each time a CEC frame arrived
/// @param cmd  The received command
static void Cec_Clbk(CEC_COMMAND* cmd)
{
    APP_REMOTE_KEYS ir_cmd_out  = KEY_COUNT;
    CEC_COMMAND        cec_cmd_out = {.source = AUDIO_SYSTEM, .target = cmd->source};
    bool send_ir  = false;
    bool send_cec = false;
    
    if (!cmd->polling)
    {
        switch (cmd->opcode)
        {
            case STANDBY:
            {
                if (audio_on)
                {
                    audio_on   = false;
                    ir_cmd_out = KEY_POWER;
                    send_ir    = true;
                }
                break;
            }

            case GIVE_PHYSICAL_ADDRESS:
            {
                cec_cmd_out.opcode       = REPORT_PHYSICAL_ADDRESS;
                cec_cmd_out.payload_size = 1;
                cec_cmd_out.payload[0]   = AUDIO_SYSTEM;
                send_cec = true;
                break;
            }

            case GET_CEC_VERSION:
            {
                cec_cmd_out.opcode       = CEC_VERSION;
                cec_cmd_out.payload_size = 1;
                cec_cmd_out.payload[0]   = 0x05; // CEC 1.4b
                send_cec = true;
                break;
            }

            case GIVE_DEVICE_VENDOR_ID:
            {
                cec_cmd_out.opcode       = DEVICE_VENDOR_ID;
                cec_cmd_out.payload_size = 3;
                cec_cmd_out.payload[0]   = 0x18;
                cec_cmd_out.payload[1]   = 0x03;
                cec_cmd_out.payload[2]   = 0x99;
                send_cec = true;
                break;
            }

            case GIVE_DEVICE_POWER_STATUS:
            {
                cec_cmd_out.opcode       = REPORT_POWER_STATUS;
                cec_cmd_out.payload_size = 1;
                cec_cmd_out.payload[0]   = (audio_on ? 0x00 : 0x01); // On or Standby
                send_cec = true;
                break;
            }

            case USER_CONTROL_PRESSED:
            {
                // Just retain control that was pressed
                last_user_control = cmd->payload[0];
                break;
            }

            case SYSTEM_AUDIO_MODE_REQUEST:
            {
                cec_cmd_out.opcode       = SET_SYSTEM_AUDIO_MODE;
                cec_cmd_out.target       = UNREGISTERED_BROADCAST;
                cec_cmd_out.payload_size = 1;
                cec_cmd_out.payload[0]   = 1; // On
                send_cec = true;

                if (!audio_on)
                {
                    audio_on   = true;
                    ir_cmd_out = KEY_POWER;
                    send_ir    = true;

                    // Send switch to right input after delay
                    ir_delayed_key = KEY_IN_VIDEO2;
                    if (xTimerStart(timer_ir_delayed_key, 0) != pdTRUE)
                    {
                        log_error("Can't start IR timer");
                    }
                }
                break;
            }

            case USER_CONTROL_RELEASED:
            {
                send_ir = true;

                switch (last_user_control)
                {
                    case 0x41: // Volume Up
                        ir_cmd_out = KEY_VOL_UP;
                        break;
                    case 0x42: // Volume Down
                        ir_cmd_out = KEY_VOL_DOWN;
                        break;
                    case 0x43: // Mute
                        ir_cmd_out = KEY_VOL_MUTE;
                        break;
                    default:
                        send_ir = false;
                        break;
                }
                break;
            }

            case FEATURE_ABORT:
            {
                break;
            }

            default:
            {
                cec_cmd_out.opcode       = FEATURE_ABORT;
                cec_cmd_out.payload_size = 1;
                cec_cmd_out.payload[0]   = 0x00;    // Unrecognized opcode
                send_cec = true;
                break;
            }
        }
    }

    // Send the IR frame if needed
    if (send_ir)
    {
        if (!AppRemote_Transmit(ir_cmd_out))
        {
            log_error("Failed to send IR frame\r");
        }
    }

    // Send the CEC frame if needed
    if (send_cec)
    {
        if (!AppCec_Send(&cec_cmd_out))
        {
            log_error("Failed to send CEC frame\r");
        }
    }
}

/// @brief          Callback function when timer_ir_delayed_key expires
/// @param argument unused
static void IrDelayedKey_Clbk(TimerHandle_t pxTimer)
{
    if (!AppRemote_Transmit(ir_delayed_key))
    {
        log_error("Failed to send IR frame\r");
    }

    // Stop timer
    xTimerStop(timer_ir_delayed_key, 0);
}

/// @brief External interrupt callback 
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    // If user button is pressed
    if (GPIO_Pin == GPIO_PIN_13)
    {
        if (!audio_on)
        {
            log_trace("Button pressed, starting audio amp\r");

            AppRemote_Transmit(KEY_POWER);
            audio_on = true;

            ir_delayed_key = KEY_IN_VIDEO2;
            xTimerStartFromISR(timer_ir_delayed_key, NULL);
        }
        else
        {
            log_trace("Button pressed, stopping audio amp\r");

            AppRemote_Transmit(KEY_POWER);
            audio_on = false;
        }
    }
}

//      PUBLIC FUNCTIONS DEFINITION
bool AppMain_Init(void)
{
    // Initialize all modules
    if (!AppLog_Init() || !AppCec_Init() || !AppRemote_Init())
    {
        return false;
    }

    // Register callback for the incoming CEC commands to broadcast and audio system
    if (!AppCec_RegisterCallback(UNREGISTERED_BROADCAST, Cec_Clbk)
        || !AppCec_RegisterCallback(AUDIO_SYSTEM, Cec_Clbk))
    {
        return false;
    }

    // Initialize delayed key timer
    timer_ir_delayed_key = xTimerCreate("TIMER - delayed IR key", pdMS_TO_TICKS(4000), pdFALSE, NULL, IrDelayedKey_Clbk);
    if (timer_ir_delayed_key == NULL)
    {
        return false;
    }
    
    log_info("Startup\r");

    return true;
}
