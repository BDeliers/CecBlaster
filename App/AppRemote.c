//      INCLUDES
#include "AppRemote.h"
#include "DrvIrSirc.h"

#include "cmsis_os2.h"
#include "log.h"

#include <string.h>

//      LOCAL MACROs
#define LOG_TX              1U
#define SNPRINTF_BUF_SIZE   128U

//      LOCAL TYPEDEFS DEFINES AND ENUMS

//      EXTERN VARIABLES

//      LOCAL VARIABLES

// Sony remote commands
static const SIRC_FRAME RM_AAU013_COMMAND_SET[KEY_COUNT] = {
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

static osThreadId_t         thread_ir_handler                   = NULL;
static osMessageQueueId_t   queue_ir_tx                         = NULL;

//      STATIC FUNCTIONS PROTOTYPES
#if LOG_TX
static void LogTx(const SIRC_FRAME* frame);
#endif

static void AppRemoteRunner(void* argument);

//      STATIC FUNCTIONS DEFINITION
#if LOG_TX
/// @brief          Log a frame to standard output
/// @param frame    The frame to be logged
static void LogTx(const SIRC_FRAME* frame)
{
    char buf[SNPRINTF_BUF_SIZE];
    uint8_t idx = 0;

    idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, "Sent frame with command %02x to address %02x", frame->command, frame->address);

    if (frame->version == C7_A8)
    {
        idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, " (8b)");
    }
    else
    {
        idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, " (5b)");
        if (frame->version == C7_A5_EXT)
        {
            idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, " and extended  bytes %02x", frame->extended);
        }
    }

    idx += snprintf(buf+idx, SNPRINTF_BUF_SIZE-idx, "\r");
    log_debug(buf);
}
#endif // LOG_TX

/// @brief          AppRemote main thread
/// @param argument unused
static void AppRemoteRunner(void* argument)
{
    APP_REMOTE_KEYS cmd = {0};

    for (;;)
    {
        // If frames are waiting to be sent
        if (osMessageQueueGetCount(queue_ir_tx) > 0)
        {
            // Only if driver is ready
            if (DrvIrSirc_IsReady())
            {
                if (osMessageQueueGet(queue_ir_tx, &cmd, 0, 0) == osOK)
                {
                    // Transmit frame, repeat twice (will be sent 3 times so)
                    if (DrvIrSirc_Transmit(&RM_AAU013_COMMAND_SET[cmd], 2))
                    {
                        #if LOG_TX
                        LogTx(&RM_AAU013_COMMAND_SET[cmd]);
                        #endif
                    }
                }
            }
        }

        osDelay(1);
    }
}

//      PUBLIC FUNCTIONS DEFINITION
bool AppRemote_Init(void)
{
    if (!DrvIrSirc_Init())
    {
        return false;
    }

    // Frames to be sent will be queued
    osMessageQueueAttr_t queue_ir_tx_attr = {
        .name = "Queue - IR TX"
    };
    queue_ir_tx = osMessageQueueNew(10, sizeof(APP_REMOTE_KEYS), &queue_ir_tx_attr);
    if (queue_ir_tx == NULL)
    {
        return false;
    }

    osThreadAttr_t thread_ir_handler_attr = {
        .name = "Thread - IR HANDLER",
        .stack_size = 2048,
        .priority = osPriorityNormal
    };
    thread_ir_handler = osThreadNew(AppRemoteRunner, NULL, &thread_ir_handler_attr);
    if (thread_ir_handler == NULL)
    {
        return false;
    }

    return true;
}

bool AppRemote_Transmit(APP_REMOTE_KEYS key)
{
    // Just enqueue the frame for async transmission
    return (osMessageQueuePut(queue_ir_tx, &key, 0, 0) == osOK);
}
