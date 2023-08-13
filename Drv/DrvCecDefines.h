#ifndef DRV_CEC_DEFINES_H
#define DRV_CEC_DEFINES_H

//      INCLUDES
#include <stdint.h>
#include <stdbool.h>

//      PUBLIC DEFINES

//      PUBLIC TYPEDEFS AND ENUMS
// CEC opcodes from 1.4 spec
typedef enum
{
    // One touch play
    ACTIVE_SOURCE = 0x82,
    IMAGE_VIEW_ON = 0x04,
    TEXT_VIEW_ON  = 0x0D,
    // Routing control
    INACTIVE_SOURCE       = 0x9D,
    REQUEST_ACTIVE_SOURCE = 0x85,
    ROUTING_CHANGE        = 0x80,
    ROUTING_INFORMATION   = 0x81,
    SET_STREAM_PATH       = 0x86,
    // Standby
    STANDBY = 0x36,
    // One touch record
    RECORD_OFF       = 0x0B,
    RECORD_ON        = 0x09,
    RECORD_STATUS    = 0x0A,
    RECORD_TV_SCREEN = 0x0F,
    // Timer programming
    CLEAR_ANALOGUE_TIMER    = 0x33,
    CLEAR_DIGITAL_TIMER     = 0x99,
    CLEAR_EXTERNAL_TIMER    = 0xA1,
    SET_ANALOGUE_TIMER      = 0x34,
    SET_DIGITAL_TIMER       = 0x97,
    SET_EXTERNAL_TIMER      = 0xA2,
    SET_TIMER_PROGRAM_TITLE = 0x67,
    TIMER_CLEARED_STATUS    = 0x43,
    TIMER_STATUS            = 0x35,
    // System information
    // POLLING              = --
    CEC_VERSION             = 0x9E,
    GET_CEC_VERSION         = 0x9F,
    GIVE_PHYSICAL_ADDRESS   = 0x83,
    GET_MENU_LANGUAGE       = 0x91,
    REPORT_PHYSICAL_ADDRESS = 0x84,
    SET_MENU_LANGUAGE       = 0x32,
    // Deck control
    DECK_CONTROL     = 0x42,
    DECK_STATUS      = 0x1B,
    GIVE_DECK_STATUS = 0x1A,
    PLAY             = 0x41,
    // Tuner control
    GIVE_TUNER_DEVICE_STATUS = 0x08,
    SELECT_ANALOGUE_SERVICE  = 0x92,
    SELECT_DIGITAL_SERVICE   = 0x93,
    TUNER_DEVICE_STATUS      = 0x07,
    TUNER_STEP_DECREMENT     = 0x06,
    TUNER_STEP_INCREMENT     = 0x05,
    // Vendor specific
    DEVICE_VENDOR_ID          = 0x87,
    GIVE_DEVICE_VENDOR_ID     = 0x8C,
    VENDOR_COMMAND            = 0x89,
    VENDOR_COMMAND_WITH_ID    = 0xA0,
    VENDOR_REMOTE_BUTTON_DOWN = 0x8A,
    VENDOR_REMOTE_BUTTON_UP   = 0x8B,
    // OSD display
    SET_OSD_STRING = 0x64,
    // OSD transfer
    GIVE_OSD_NAME = 0x46,
    SET_OSD_NAME  = 0x46,
    // Device menu control & Remote control passtrough
    MENU_REQUEST            = 0x8D,
    MENU_STATUS             = 0x8E,
    USER_CONTROL_PRESSED    = 0x44,
    USER_CONTROL_RELEASED   = 0x45,
    // Power status
    GIVE_DEVICE_POWER_STATUS = 0x8F,
    REPORT_POWER_STATUS      = 0x90,
    // General protocol
    FEATURE_ABORT = 0x00,
    ABORT         = 0xFF,
    // System audio control
    GIVE_AUDIO_STATUS               = 0x71,
    GIVE_SYSTEM_AUDIO_MODE_STATUS   = 0x7D,
    REPORT_AUDIO_STATUS             = 0x7A,
    REPORT_SHORT_AUDIO_DESCRIPTOR   = 0xA3,
    REQUEST_SHORT_AUDIO_DESCRIPTOR  = 0xA4,
    SET_SYSTEM_AUDIO_MODE           = 0x72,
    SYSTEM_AUDIO_MODE_REQUEST       = 0x70,
    SYSTEM_AUDIO_MODE_STATUS        = 0x7E,
    // Audio rate control
    SET_AUDIO_RATE = 0x9A,
    // Audio return channel
    INITIATE_ARC            = 0xC0,
    REPORT_ARC_INITIATED    = 0xC1,
    REPORT_ARC_TERMINATED   = 0xC2,
    REQUEST_ARC_INITIATION  = 0xC3,
    REQUEST_ARC_TERMINATION = 0xC4,
    TERMINATE_ARC           = 0xC5,
    CDC_MESSAGE             = 0xF8,
}
CEC_COMMANDS;

typedef enum
{
    TV,
    RECORDING_1,
    RECORDING_2,
    TUNER_1,
    PLAYBACK_1,
    AUDIO_SYSTEM,
    TUNER_2,
    TUNER_3,
    PLAYBACK_2,
    RECORDING_3,
    TUNER_4,
    PLAYBACK_3,
    BACKUP_1,
    BACKUP_2,
    SPECIFIC,
    UNREGISTERED_BROADCAST,
    CEC_DEVICE_COUNT
}
CEC_LOGICAL_ADDRESS;

typedef struct
{
    CEC_COMMANDS        opcode;
    CEC_LOGICAL_ADDRESS source;
    CEC_LOGICAL_ADDRESS target;
    uint8_t             payload[14];
    uint8_t             payload_size;
}
CEC_COMMAND;

#endif /* DRV_CEC_DEFINES_H */
