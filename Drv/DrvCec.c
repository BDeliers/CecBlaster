//      INCLUDES
#include "DrvCec.h"

#include <string.h>
#include "stm32h5xx_hal.h"
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "timers.h"

//      EXTERN VARIABLES
extern CEC_HandleTypeDef            hcec;

//      LOCAL VARIABLES
static volatile bool                cec_dropped_frame   = false;
static volatile bool                cec_error           = false;
static uint8_t                      cec_rx_buff[16]     = {0};
static CEC_COMMAND                  cec_parsed_cmd      = {0};
static CEC_RX_HANDLER               rx_handler          = NULL;
static CEC_ERROR_HANDLER            error_handler       = NULL;
static MessageBufferHandle_t        message_buffer      = NULL;
static TimerHandle_t                timer_handler       = NULL;

//      STATIC FUNCTIONS PROTOTYPES
static void CecErrorClbk(CEC_HandleTypeDef *hcec);
static void CecRxClbk(CEC_HandleTypeDef *hcec, uint32_t frame_size);
static bool CecParseFrame(uint8_t* payload, uint8_t size, CEC_COMMAND* cmd);
static void Handler(TimerHandle_t pxTimer);

//      STATIC FUNCTIONS DEFINITION
static void CecRxClbk(CEC_HandleTypeDef *hcec, uint32_t frame_size)
{	
    if (xMessageBufferSendFromISR(message_buffer, cec_rx_buff, frame_size, NULL) == 0)
    {
        cec_dropped_frame = true;
    }
}

static void CecErrorClbk(CEC_HandleTypeDef *hcec)
{
	cec_error = true;
}

static bool CecParseFrame(uint8_t* payload, uint8_t size, CEC_COMMAND* cmd)
{
    // If we have a valid frame
    if (size == 0 || size > 16)
    {
        return false;
    }

    // Cleanup struct
    memset(cmd, 0, sizeof(CEC_COMMAND));

    // Source/target are in the first byte
    cmd->source = (payload[0] & 0xF0) >> 4;
    cmd->target = payload[0] & 0x0F;

    // If not polling
    if (size > 1)
    {
        cmd->opcode = payload[1];

        // If a payload is provided
        if (size > 2)
        {
            cmd->payload_size = size-2;
            memcpy(cmd->payload, payload+2, size-2);
        }
    }
    else
    {
        cmd->polling = true;
    }

    return true;
}

static void Handler(TimerHandle_t pxTimer)
{
    static uint8_t tmp_buffer[16] = {0};
    static uint8_t read_bytes     = 0;

    if (cec_error || cec_dropped_frame)
    {
        if (error_handler != NULL)
        {
            error_handler();
        }

        cec_error         = false;
        cec_dropped_frame = false;
    }
    // CEC frame received
    if (xMessageBufferIsEmpty(message_buffer) == pdFALSE)
    {
        read_bytes = 0;

        do
        {
            // Get un-parsed frame from buffer
            read_bytes = xMessageBufferReceive(message_buffer, tmp_buffer, 16, 0);

            if (read_bytes > 0)
            {
                // Parse it as a CEC command strcture
                CecParseFrame(tmp_buffer, read_bytes, &cec_parsed_cmd);

                if (rx_handler != NULL)
                {
                    // Call RX handler to higher app level
                    rx_handler(&cec_parsed_cmd);
                }
            }
        }
        while (read_bytes > 0);
    }
}

//      PUBLIC FUNCTIONS DEFINITION
bool DrvCec_Init(void)
{
    // Use our buffer to received CEC frames
	HAL_CEC_ChangeRxBuffer(&hcec, cec_rx_buff);

    // Link Rx and error callbacks to this source
    if (HAL_CEC_RegisterRxCpltCallback(&hcec, CecRxClbk) != HAL_OK
        || HAL_CEC_RegisterCallback(&hcec, HAL_CEC_ERROR_CB_ID, CecErrorClbk) != HAL_OK)
    {
        return false;
    }

    // Create a message buffer that can contain 10 frames
    message_buffer = xMessageBufferCreate(10 * 16);
    if (message_buffer == NULL)
    {
        return false;
    }

    // Initialize handler task to be called each 20 ticks
    timer_handler = xTimerCreate("TIMER - CEC handler", 20, pdTRUE, NULL, Handler);
    if (timer_handler == NULL)
    {
        return false;
    }
    xTimerStart(timer_handler, 0);

    return true;
}

bool DrvCec_RegisterRxHandler(CEC_RX_HANDLER handler)
{
    if (handler == NULL)
    {
        return false;
    }

    rx_handler = handler;
    return true;
}

bool DrvCec_RegisterErrorHandler(CEC_ERROR_HANDLER handler)
{
    if (handler == NULL)
    {
        return false;
    }

    error_handler = handler;
    return true;
}

bool DrvCec_IsReady(void)
{
    return (HAL_CEC_GetState(&hcec) == HAL_CEC_STATE_READY);
}

bool DrvCec_Send(CEC_COMMAND* cmd)
{
    if (cmd == NULL)
    {
        return false;   
    }

    // Concatenate payload and opcode
    uint8_t tmp[15] = {0};
    tmp[0] = cmd->opcode;
    memcpy(tmp+1, cmd->payload, cmd->payload_size);

    // Send data
    if (HAL_CEC_Transmit_IT(&hcec, cmd->source, cmd->target, tmp, cmd->payload_size+1) != HAL_OK)
    {
        return false;
    }

    return true;
}
