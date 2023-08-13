#ifndef APP_CEC_H
#define APP_CEC_H

//      INCLUDES
#include <stdint.h>
#include <stdbool.h>

#include "DrvCecDefines.h"

//      PUBLIC DEFINES

//      PUBLIC TYPEDEFS AND ENUMS
typedef void (*APP_CEC_CLBK)(CEC_COMMAND* cmd);

//      PUBLIC FUNCTIONS PROTOTYPES
bool AppCec_Init(void);
bool AppCec_Handler(void);

bool AppCec_RegisterCallback(CEC_LOGICAL_ADDRESS source, CEC_LOGICAL_ADDRESS target, CEC_COMMANDS opcode, APP_CEC_CLBK clbk);

#endif /* APP_CEC_H */
