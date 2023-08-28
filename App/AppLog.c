//      INCLUDES
#include "AppLog.h"

#include "log.h"
#include "cmsis_os2.h"

#include "stm32h5xx_hal.h"

#include <string.h>

//      LOCAL MACRO
#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

//      LOCAL TYPEDEFS AND ENUMS

//      EXTERN VARIABLES
extern UART_HandleTypeDef               huart3;

//      LOCAL VARIABLES
static osMessageQueueId_t               queue_uart_tx       = NULL;
static osThreadId_t                     thread_uart_tx      = NULL;
static osMutexId_t                      mutex_log_module    = NULL;

//      STATIC FUNCTIONS PROTOTYPES
static void UartTxRunner(void *argument);
static void LogLockFunction(bool lock, void *lock_ptr);

//      STATIC FUNCTIONS DEFINITION
PUTCHAR_PROTOTYPE
{
    // Just enqueue the byte
    osMessageQueuePut(queue_uart_tx, &ch, 0, 0);

    return ch;
}

static void UartTxRunner(void *argument)
{
    char byte;

    for (;;)
    {
        // Send byte to UART module if queue not empty
        if (osMessageQueueGet(queue_uart_tx, &byte, 0, 0) == osOK)
        {
            HAL_UART_Transmit(&huart3, (uint8_t *)&byte, 1, 0xFFFF);
        }

        osDelay(1);
    }
}

static void LogLockFunction(bool lock, void *lock_ptr)
{
    if (lock)
    {
        osMutexAcquire(mutex_log_module, 0);
    }
    else
    {
        osMutexRelease(mutex_log_module);
    }
}

//      PUBLIC FUNCTIONS DEFINITION
bool AppLog_Init(void)
{
    osMessageQueueAttr_t queue_uart_tx_attr = {
        .name = "Queue - UART TX"
    };
    queue_uart_tx = osMessageQueueNew(1024, sizeof(char), &queue_uart_tx_attr);
    if (queue_uart_tx == NULL)
    {
        return false;
    }

    osThreadAttr_t thread_uart_tx_attr = {
        .name = "Thread - UART TX",
        .stack_size = 1024,
        .priority = osPriorityBelowNormal
    };
    thread_uart_tx = osThreadNew(UartTxRunner, NULL, &thread_uart_tx_attr);
    if (thread_uart_tx == NULL)
    {
        return false;
    }

    osMutexAttr_t  mutex_log_module_attr = {
        .name = "Mutex - Log module"
    };
    mutex_log_module = osMutexNew(&mutex_log_module_attr);
    if (mutex_log_module == NULL)
    {
        return false;
    }

    log_set_lock(LogLockFunction, &mutex_log_module);
    
    return true;
}