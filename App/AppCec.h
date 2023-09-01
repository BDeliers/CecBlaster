/**
 * @file    AppCec.h
 * @author  BDeliers
 * @brief   CEC app module, wrapping the CEC driver
 * 
 */

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

/// @brief          Register a callback to incoming frames
/// @param target   The target logical address of the commands
/// @param clbk     The callback function to be called
/// @return         true if success, false otherwise
bool AppCec_RegisterCallback(CEC_LOGICAL_ADDRESS target, APP_CEC_CLBK clbk);

/// @brief      Send a CEC command asynchronously
/// @param cmd  The command to be sent
/// @return     true if success, false otherwise (when queue is already full)
bool AppCec_Send(CEC_COMMAND* cmd);

#endif /* APP_CEC_H */
