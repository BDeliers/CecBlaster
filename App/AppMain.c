//      INCLUDES
#include "AppCec.h"
#include "DrvIrSirc.h"

#include "log.h"

#include "stm32h5xx_hal.h"

#include <string.h>

//      LOCAL TYPEDEFS AND ENUMS
typedef enum
{
    RM_AAU013_POWER,
    RM_AAU013_VOL_UP,
    RM_AAU013_VOL_DOWN,
    RM_AAU013_VOL_MUTE,
    RM_AAU013_IN_VIDEO2,
    RM_AAU013_IN_CD,
    RM_AAU013_MODE_STEREO,
    RM_AAU013_MODE_AFD,
    RM_AAU013_MODE_MOVIE,
    RM_AAU013_MODE_MUSIC,
    RM_AAU013_COMMANDS_COUNT
}
RM_AAU013_COMMANDS;

//      EXTERN VARIABLES

//      LOCAL VARIABLES

// Sony remote power button command
static const SIRC_FRAME RM_AAU013_COMMAND_SET[RM_AAU013_COMMANDS_COUNT] = {
    { .command = 0x15, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x12, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x13, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x14, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x1E, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x25, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x41, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x42, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x43, .address = 0x30, .extended = 0x00, .version = C7_A8 },
    { .command = 0x44, .address = 0x30, .extended = 0x00, .version = C7_A8 },
};

static bool     audio_on            = false;
static uint8_t  last_user_control   = 0xFF;

//      STATIC FUNCTIONS PROTOTYPES
static void Cec_Clbk(CEC_COMMAND* cmd);

//      STATIC FUNCTIONS DEFINITION
static void Cec_Clbk(CEC_COMMAND* cmd)
{
    RM_AAU013_COMMANDS ir_cmd_out  = RM_AAU013_COMMANDS_COUNT;
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
                    ir_cmd_out = RM_AAU013_POWER;
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
                    ir_cmd_out = RM_AAU013_POWER;
                    send_ir    = true;

                    // Send switch to right source, to be queued with delay...
                }
                break;
            }

            case USER_CONTROL_RELEASED:
            {
                send_ir = true;

                switch (last_user_control)
                {
                    case 0x40: // Power
                        ir_cmd_out = RM_AAU013_POWER;
                        audio_on = true;
                        break;
                    case 0x41: // Volume Up
                        ir_cmd_out = RM_AAU013_VOL_UP;
                        break;
                    case 0x42: // Volume Down
                        ir_cmd_out = RM_AAU013_VOL_DOWN;
                        break;
                    case 0x43: // Mute
                        ir_cmd_out = RM_AAU013_VOL_MUTE;
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
    if (send_ir && DrvIrSirc_IsReady())
    {
        if (!DrvIrSirc_Transmit(&RM_AAU013_COMMAND_SET[ir_cmd_out], 2))
        {
            log_error("Failed to send IR frame\r");
        }
        /*else
        {
            log_debug("Sent IR command %02x\r", RM_AAU013_COMMAND_SET[ir_cmd_out].command);
        }*/
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

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_13)
    {
        log_trace("Button pressed, startign audio amp\r");
        DrvIrSirc_Transmit(&RM_AAU013_COMMAND_SET[RM_AAU013_POWER], 2);
        audio_on = !audio_on;
    }
}

//      PUBLIC FUNCTIONS DEFINITION
bool AppMain_Init(void)
{
    if (!AppCec_Init() || !DrvIrSirc_Init())
    {
        return false;
    }

    // Register callback for the incoming CEC commands to broadcast and audio system
    if (!AppCec_RegisterCallback(TV, UNREGISTERED_BROADCAST, Cec_Clbk)
        || !AppCec_RegisterCallback(TV, AUDIO_SYSTEM, Cec_Clbk)
        || !AppCec_RegisterCallback(PLAYBACK_1, AUDIO_SYSTEM, Cec_Clbk))
    {
        return false;
    }

    return true;
}

bool AppMain_Handler(void)
{
    return AppCec_Handler();
}
