/**
 * @file    AppRemote.h
 * @author  BDeliers
 * @brief   Remote module, translating remote keys to infrared frames
 * 
 */

#ifndef APP_REMOTE_H
#define APP_REMOTE_H

//      INCLUDES
#include <stdint.h>
#include <stdbool.h>

#include "DrvIrSirc.h"

//      PUBLIC DEFINES

//      PUBLIC TYPEDEFS AND ENUMS

/// @brief Remote keys that can be simulated by the app
typedef enum
{
    KEY_POWER,
    KEY_VOL_UP,
    KEY_VOL_DOWN,
    KEY_VOL_MUTE,
    KEY_IN_VIDEO2,
    KEY_IN_CD,
    KEY_MODE_STEREO,
    KEY_MODE_AFD,
    KEY_MODE_MOVIE,
    KEY_MODE_MUSIC,
    KEY_COUNT
}
APP_REMOTE_KEYS;

//      PUBLIC FUNCTIONS PROTOTYPES
bool AppRemote_Init(void);

/// @brief      Send a key over infrared, asynchronously
/// @param key  The remote key to send
/// @return     true in case of success, false otherwise (when queue is already full)
bool AppRemote_Transmit(APP_REMOTE_KEYS key);

#endif /* APP_REMOTE_H */
