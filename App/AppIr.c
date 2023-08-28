//      INCLUDES
#include "AppIr.h"
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
static osThreadId_t         thread_ir_handler                   = NULL;
static osMessageQueueId_t   queue_ir_tx                         = NULL;

//      STATIC FUNCTIONS PROTOTYPES
#if LOG_TX
static void LogTx(SIRC_FRAME* frame);
#endif // LOG_TX

static void AppIrRunner(void* argument);

//      STATIC FUNCTIONS DEFINITION
#if LOG_TX
static void LogTx(SIRC_FRAME* frame)
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

static void AppIrRunner(void* argument)
{
    SIRC_FRAME frame = {0};

    for (;;)
    {
        // Process outgoing frames
        if (osMessageQueueGetCount(queue_ir_tx) > 0)
        {
            if (DrvIrSirc_IsReady())
            {
                if (osMessageQueueGet(queue_ir_tx, &frame, 0, 0) == osOK)
                {
                    if (DrvIrSirc_Transmit(&frame))
                    {
                        #if LOG_TX
                        LogTx(&frame);
                        #endif
                    }
                }
            }
        }

        osDelay(1);
    }
}

//      PUBLIC FUNCTIONS DEFINITION
bool AppIr_Init(void)
{
    if (!DrvIrSirc_Init())
    {
        return false;
    }

    osMessageQueueAttr_t queue_ir_tx_attr = {
        .name = "Queue - IR TX"
    };
    queue_ir_tx = osMessageQueueNew(10, sizeof(SIRC_FRAME), &queue_ir_tx_attr);
    if (queue_ir_tx == NULL)
    {
        return false;
    }

    osThreadAttr_t thread_ir_handler_attr = {
        .name = "Thread - IR HANDLER",
        .stack_size = 2048,
        .priority = osPriorityNormal
    };
    thread_ir_handler = osThreadNew(AppIrRunner, NULL, &thread_ir_handler_attr);
    if (thread_ir_handler == NULL)
    {
        return false;
    }

    return true;
}

bool AppIr_Transmit(const SIRC_FRAME* frame)
{
    // Just enqueue the frame for async transmission
    return (osMessageQueuePut(queue_ir_tx, frame, 0, 0) == osOK);
}
