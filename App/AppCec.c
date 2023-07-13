//      INCLUDES
#include "AppCec.h"

#include <stdio.h>
#include "stm32h5xx_hal.h"

//      EXTERN VARIABLES
extern CEC_HandleTypeDef            hcec;

//      LOCAL VARIABLES
static bool                         cec_received_frame  = false;
static bool                         cec_error           = false;
static uint8_t                      cec_frame_size      = 0;
static uint8_t                      cec_rx_buff[16]     = {0};
static bool                         full_log            = false;

//      STATIC FUNCTIONS PROTOTYPES
static void CecErrorClbk(CEC_HandleTypeDef *hcec);
static void CecRxClbk(CEC_HandleTypeDef *hcec, uint32_t frame_size);

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


//      PUBLIC FUNCTIONS DEFINITION
bool AppCec_Init(void)
{
	HAL_CEC_ChangeRxBuffer(&hcec, cec_rx_buff);

    if (HAL_CEC_RegisterRxCpltCallback(&hcec, CecRxClbk) != HAL_OK
        || HAL_CEC_RegisterCallback(&hcec, HAL_CEC_ERROR_CB_ID, CecErrorClbk) != HAL_OK)
    {
        return false;
    }

    return true;
}

bool AppCec_Handler(void)
{
    if (cec_error)
    {
        if (full_log)
        {
            printf("CEC error\r\n");
        }

        cec_error = false;
    }
    if (cec_received_frame)
    {
        if (full_log)
        {
            printf("CEC received frame = ");
            for (uint8_t i = 0; i < cec_frame_size; i++)
            {
                printf("%02X", cec_rx_buff[i]);
                if ((i+1) < cec_frame_size)
                {
                    printf(":");
                }
            }
            printf("\r\n");
        }

        cec_received_frame = false;
    }

    return true;
}

void AppCec_SetFullLog(bool state)
{
    full_log = state;
}
