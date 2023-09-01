//      INCLUDES
#include "DrvCec.h"

#include <string.h>
#include "stm32h5xx_hal.h"

//      EXTERN VARIABLES
extern CEC_HandleTypeDef            hcec;

//      LOCAL VARIABLES
static bool                         cec_received_frame  = false;
static bool                         cec_error           = false;
static uint8_t                      cec_frame_size      = 0;
static uint8_t                      cec_rx_buff[16]     = {0};
static CEC_COMMAND                  cec_parsed_cmd      = {0};
static CEC_RX_HANDLER               rx_handler          = NULL;
static CEC_ERROR_HANDLER            error_handler       = NULL;

//      STATIC FUNCTIONS PROTOTYPES
static void CecErrorClbk(CEC_HandleTypeDef *hcec);
static void CecRxClbk(CEC_HandleTypeDef *hcec, uint32_t frame_size);
static bool CecParseFrame(uint8_t* payload, uint8_t size, CEC_COMMAND* cmd);

//      STATIC FUNCTIONS DEFINITION
static void CecRxClbk(CEC_HandleTypeDef *hcec, uint32_t frame_size)
{
	cec_received_frame = true;
	cec_frame_size	   = frame_size;
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

    return true;
}

bool DrvCec_Handler(void)
{
    if (cec_error)
    {
        if (error_handler != NULL)
        {
            error_handler();
        }

        cec_error = false;
    }
    // CEC frame received
    if (cec_received_frame)
    {
        // Parse it as a CEC command strcture
        CecParseFrame(cec_rx_buff, cec_frame_size, &cec_parsed_cmd);

        if (rx_handler != NULL)
        {
            // Call RX handler to higher app level
            rx_handler(&cec_parsed_cmd);
        }
        cec_received_frame = false;
    }

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
