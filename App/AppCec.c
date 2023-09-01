//      INCLUDES
#include "AppCec.h"
#include "DrvCec.h"

#include "cmsis_os2.h"
#include "log.h"

#include <string.h>

//      LOCAL TYPEDEFS DEFINES AND ENUMS
#define MAX_CALLBACKS_CNT       10U
#define LOG_RXTX                1U
#define SNPRINTF_BUF_SIZE       128U

/// @brief  Callback function structure
/// @var target   The CEC logical address of the target
/// @var callback The actual callback function
typedef struct
{
    CEC_LOGICAL_ADDRESS target;
    APP_CEC_CLBK        callback;
}
CEC_CLBK_STRUCT;

//      EXTERN VARIABLES

//      LOCAL VARIABLES

#if LOG_RXTX
    /// @brief CEC commands as string
    const char* CEC_COMMANDS_STRING[] = {
        "FEATURE_ABORT",NULL,NULL,NULL,"IMAGE_VIEW_ON","TUNER_STEP_INCREMENT","TUNER_STEP_DECREMENT","TUNER_DEVICE_STATUS",
        "GIVE_TUNER_DEVICE_STATUS","RECORD_ON","RECORD_STATUS","RECORD_OFF",NULL,"TEXT_VIEW_ON",NULL,"RECORD_TV_SCREEN",
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"GIVE_DECK_STATUS","DECK_STATUS",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"SET_MENU_LANGUAGE","CLEAR_ANALOGUE_TIMER",
        "SET_ANALOGUE_TIMER","TIMER_STATUS","STANDBY",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"PLAY","DECK_CONTROL",
        "TIMER_CLEARED_STATUS","USER_CONTROL_PRESSED","USER_CONTROL_RELEASED","GIVE_OSD_NAME","SET_OSD_NAME",
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,"SET_OSD_STRING",NULL,NULL,"SET_TIMER_PROGRAM_TITLE",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        "SYSTEM_AUDIO_MODE_REQUEST","GIVE_AUDIO_STATUS","SET_SYSTEM_AUDIO_MODE",NULL,NULL,NULL,NULL,NULL,NULL,NULL,"REPORT_AUDIO_STATUS",
        NULL,NULL,"GIVE_SYSTEM_AUDIO_MODE_STATUS","SYSTEM_AUDIO_MODE_STATUS",NULL,"ROUTING_CHANGE","ROUTING_INFORMATION","ACTIVE_SOURCE",
        "GIVE_PHYSICAL_ADDRESS","REPORT_PHYSICAL_ADDRESS","REQUEST_ACTIVE_SOURCE","SET_STREAM_PATH","DEVICE_VENDOR_ID",NULL,
        "VENDOR_COMMAND","VENDOR_REMOTE_BUTTON_DOWN","VENDOR_REMOTE_BUTTON_UP","GIVE_DEVICE_VENDOR_ID","MENU_REQUEST","MENU_STATUS",
        "GIVE_DEVICE_POWER_STATUS","REPORT_POWER_STATUS","GET_MENU_LANGUAGE","SELECT_ANALOGUE_SERVICE","SELECT_DIGITAL_SERVICE",
        NULL,NULL,NULL,"SET_DIGITAL_TIMER",NULL,"CLEAR_DIGITAL_TIMER","SET_AUDIO_RATE",NULL,NULL,"INACTIVE_SOURCE","CEC_VERSION",
        "GET_CEC_VERSION","VENDOR_COMMAND_WITH_ID","CLEAR_EXTERNAL_TIMER","SET_EXTERNAL_TIMER","REPORT_SHORT_AUDIO_DESCRIPTOR",
        "REQUEST_SHORT_AUDIO_DESCRIPTOR",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"INITIATE_ARC","REPORT_ARC_INITIATED","REPORT_ARC_TERMINATED",
        "REQUEST_ARC_INITIATION","REQUEST_ARC_TERMINATION","TERMINATE_ARC",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"CDC_MESSAGE",NULL,NULL,NULL,NULL,NULL,NULL,"ABORT",
    };

    /// @brief CEC logical addresses as string
    const char* CEC_LOGICAL_ADDRESS_STRING[] = {
        "TV","RECORDING_1","RECORDING_2","TUNER_1","PLAYBACK_1","AUDIO_SYSTEM","TUNER_2","TUNER_3",
        "PLAYBACK_2","RECORDING_3","TUNER_4","PLAYBACK_3","BACKUP_1","BACKUP_2","SPECIFIC",
        "UNREGISTERED_BROADCAST","CEC_DEVICE_COUNT",
    };
#endif

static uint8_t              callbacks_count                     = 0;
static CEC_CLBK_STRUCT      callbacks_list[MAX_CALLBACKS_CNT]   = {0};

static osThreadId_t         thread_cec_handler                  = NULL;
static osMessageQueueId_t   queue_cec_tx                        = NULL;
static osMessageQueueId_t   queue_cec_rx                        = NULL;

//      STATIC FUNCTIONS PROTOTYPES
static void CecErrorHandler(void);
static void CecRxHandler(CEC_COMMAND* cmd);

#if LOG_RXTX
static void LogRxTx(const CEC_COMMAND* cmd, bool received);
#endif

static void AppCecRunner(void* argument);

//      STATIC FUNCTIONS DEFINITION

/// @brief      Handler called each time the DrvCec received and processed a frame
/// @param cmd  The received command 
static void CecRxHandler(CEC_COMMAND* cmd)
{
    // Just enqueue the frame
    osMessageQueuePut(queue_cec_rx, cmd, 0, 0);
}

/// @brief      Handler called each time the DrvCec received an error
static void CecErrorHandler(void)
{
    log_error("Error\r");
}

#if LOG_RXTX
/// @brief          Log a command to standard output
/// @param cmd      The command to be logged
/// @param received true if the command was received, false if it was sent
static void LogRxTx(const CEC_COMMAND* cmd, bool received)
{
    char buf[SNPRINTF_BUF_SIZE];
    uint8_t idx = 0;

    if (received)
    {
        idx = snprintf(buf, SNPRINTF_BUF_SIZE, "Received command ");
    }
    else
    {
        idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, "Sent command ");
    }

    // Polling command = no opcode, no payload
    if (cmd->polling)
    {
        idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, "POLLING");
    }
    else
    {
        if (CEC_COMMANDS_STRING[cmd->opcode] != NULL)
        {
            idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, "%s", CEC_COMMANDS_STRING[cmd->opcode]);
        }
        // Unknown command
        else
        {
            idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, "UNKNOWN %02x", cmd->opcode);
        }
    }
    idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, " from %s to %s", CEC_LOGICAL_ADDRESS_STRING[cmd->source], CEC_LOGICAL_ADDRESS_STRING[cmd->target]);

    if (cmd->payload_size > 0)
    {
        idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, " with payload: \t");
        for (uint8_t i = 0; i < cmd->payload_size; i++)
        {
            idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, "%02x ", cmd->payload[i]);
        }
    }

    idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, "\r");
    log_debug(buf);
}
#endif // LOG_RXTX

/// @brief          AppCec main thread
/// @param argument unused
void AppCecRunner(void* argument)
{
    CEC_COMMAND cmd = {0};

    for (;;)
    {
        // Parse incoming frames
        DrvCec_Handler();

        // Process outgoing frames if available
        if (osMessageQueueGetCount(queue_cec_tx) > 0)
        {
            // Only if the CEC driver is ready to send
            if (DrvCec_IsReady())
            {
                if (osMessageQueueGet(queue_cec_tx, &cmd, 0, 0) == osOK)
                {
                    if (DrvCec_Send(&cmd))
                    {
                        #if LOG_RXTX
                        LogRxTx(&cmd, false);
                        #endif
                    }
                    else
                    {
                        log_error("Failed to send frame");
                    }
                }
            }
        }

        // Process incoming frames
        if (osMessageQueueGet(queue_cec_rx, &cmd, 0, 0) == osOK)
        {
            #if LOG_RXTX
            LogRxTx(&cmd, true);
            #endif

            // Call handlers
            for (size_t i = 0; i < callbacks_count; i++)
            {
                if (callbacks_list[i].target == cmd.target)
                {
                    callbacks_list[i].callback(&cmd);
                }
            }
        }

        osDelay(1);
    }
}

//      PUBLIC FUNCTIONS DEFINITION
bool AppCec_Init(void)
{
    if (!DrvCec_Init())
    {
        return false;
    }

    // Map callbacks
    if (!DrvCec_RegisterRxHandler(CecRxHandler) || !DrvCec_RegisterErrorHandler(CecErrorHandler))
    {
        return false;
    }

    // Outgoing traffic is queued and sent asynchronously
    osMessageQueueAttr_t queue_cec_tx_attr = {
        .name = "Queue - CEC TX"
    };
    queue_cec_tx = osMessageQueueNew(10, sizeof(CEC_COMMAND), &queue_cec_tx_attr);
    if (queue_cec_tx == NULL)
    {
        return false;
    }

    // Incoming traffic is queued and processed asynchronously
    osMessageQueueAttr_t queue_cec_rx_attr = {
        .name = "Queue - CEC RX"
    };
    queue_cec_rx = osMessageQueueNew(20, sizeof(CEC_COMMAND), &queue_cec_rx_attr);
    if (queue_cec_rx == NULL)
    {
        return false;
    }

    // AppCec main thread
    osThreadAttr_t thread_cec_handler_attr = {
        .name = "Thread - CEC HANDLER",
        .stack_size = 4096,
        .priority = osPriorityHigh
    };
    thread_cec_handler = osThreadNew(AppCecRunner, NULL, &thread_cec_handler_attr);
    if (thread_cec_handler == NULL)
    {
        return false;
    }

    return true;
}

bool AppCec_RegisterCallback(CEC_LOGICAL_ADDRESS target, APP_CEC_CLBK clbk)
{
    if (callbacks_count < MAX_CALLBACKS_CNT)
    {
        // Two callbacks might be assigned to the same target
        callbacks_list[callbacks_count].target   = target;
        callbacks_list[callbacks_count].callback = clbk;
        callbacks_count++;

        return true;
    }

    return false;
}

bool AppCec_Send(CEC_COMMAND* cmd)
{
    // Just enqueue the frame for async transmission
    return (osMessageQueuePut(queue_cec_tx, cmd, 0, 0) == osOK);
}
