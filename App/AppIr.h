#ifndef APP_IR_H
#define APP_IR_H

//      INCLUDES
#include <stdint.h>
#include <stdbool.h>

#include "DrvIrSirc.h"

//      PUBLIC DEFINES

//      PUBLIC TYPEDEFS AND ENUMS

//      PUBLIC FUNCTIONS PROTOTYPES
bool AppIr_Init(void);

bool AppIr_Transmit(const SIRC_FRAME* frame);

#endif /* APP_CEC_H */
