/**
 * @file    DrvSirc.h
 * @brief   Infrared Sony SIRC protocol driver
*/

#ifndef DRV_IR_SIRC_H
#define DRV_IR_SIRC_H

//      INCLUDES
#include <stdint.h>
#include <stdbool.h>

//      PUBLIC DEFINES

//      PUBLIC TYPEDEFS AND ENUMS
typedef enum
{
    C7_A5,
    C7_A8,
    C7_A5_EXT,
    SIRC_VERSION_COUNT
}
SIRC_VERSION;

typedef struct
{
    uint8_t      command;
    uint8_t      address;
    uint8_t      extended;
    SIRC_VERSION version;
}
SIRC_FRAME;

//      PUBLIC FUNCTIONS PROTOTYPES
bool DrvIrSirc_Init(void);

bool DrvIrSirc_IsReady(void);

/// @brief          Transmit the specified frame over Infrared
/// @param frame    The frame to be sent
/// @param repeats  The number of times to repeat the frame (will be sent 1 + repeats times)
bool DrvIrSirc_Transmit(const SIRC_FRAME* frame, uint8_t repeats);

#endif /* DRV_IR_SIRC_H */
