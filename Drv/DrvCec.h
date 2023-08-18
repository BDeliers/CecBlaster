/**
 * @file    DrvCec.h
 * @brief   HDMI CEC driver for STM32H563
*/

#ifndef DRV_CEC_H
#define DRV_CEC_H

//      INCLUDES
#include <stdint.h>
#include <stdbool.h>

#include "DrvCecDefines.h"

//      PUBLIC DEFINES

//      PUBLIC TYPEDEFS AND ENUMS

typedef void (*CEC_RX_HANDLER)(CEC_COMMAND* cmd);
typedef void (*CEC_ERROR_HANDLER)(void);

//      PUBLIC FUNCTIONS PROTOTYPES
bool DrvCec_Init(void);
bool DrvCec_Handler(void);

bool DrvCec_IsReady(void);

bool DrvCec_RegisterRxHandler(CEC_RX_HANDLER handler);
bool DrvCec_RegisterErrorHandler(CEC_ERROR_HANDLER handler);

bool DrvCec_Send(CEC_COMMAND* cmd);

#endif /* DRV_CEC_H */
