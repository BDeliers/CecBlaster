#ifndef APP_CEC_H
#define APP_CEC_H

//      INCLUDES
#include <stdint.h>
#include <stdbool.h>

//      PUBLIC DEFINES

//      PUBLIC TYPEDEFS AND ENUMS
enum CEC_COMMANDS
{
    POLLING_MESSAGE=0,
    FEATURE_ABORT=0x00,
    IMAGE_VIEW_ON=0x04,
    TUNER_STEP_INCREMENT=0x05,
    TUNER_STEP_DECREMENT=0x06,
    TUNER_DEVICE_STATUS=0x07,
    GIVE_TUNER_DEVICE_STATUS=0x08,
    RECORD_ON=0x09,
    RECORD_STATUS=0x0A,
    RECORD_OFF=0x0B,
    TEXT_VIEW_ON=0x0D,
    RECORD_TV_SCREEN=0x0F,
    GIVE_DECK_STATUS=0x1A,
    DECK_STATUS=0x1B,
    SET_MENU_LANGUAGE=0x32,
    CLEAR_ANALOGUE_TIMER=0x33,
    SET_ANALOGUE_TIMER=0x34,
    TIMER_STATUS=0x35,
    STANDBY=0x36,
    PLAY=0x41,
    DECK_CONTROL=0x42,
    TIMER_CLEARED_STATUS=0x43,
    USER_CONTROL_PRESSED=0x44,
    USER_CONTROL_RELEASED=0x45,
    GIVE_OSD_NAME=0x46,
    SET_OSD_NAME=0x47,
    SET_OSD_STRING=0x64,
    SET_TIMER_PROGRAM_TITLE=0x67,
    SYSTEM_AUDIO_MODE_REQUEST=0x70,
    GIVE_AUDIO_STATUS=0x71,
    SET_SYSTEM_AUDIO_MODE=0x72,
    REPORT_AUDIO_STATUS=0x7A,
    GIVE_SYSTEM_AUDIO_MODE_STATUS=0x7D,
    SYSTEM_AUDIO_MODE_STATUS=0x7E,
    ROUTING_CHANGE=0x80,
    ROUTING_INFORMATION=0x81,
    ACTIVE_SOURCE=0x82,
    GIVE_PHYSICAL_ADDRESS=0x83,
    REPORT_PHYSICAL_ADDRESS=0x84,
    REQUEST_ACTIVE_SOURCE=0x85,
    SET_STREAM_PATH=0x86,
    DEVICE_VENDOR_ID=0x87,
    VENDOR_COMMAND=0x89,
    VENDOR_REMOTE_BUTTON_DOWN=0x8A,
    VENDOR_REMOTE_BUTTON_UP=0x8B,
    GIVE_DEVICE_VENDOR_ID=0x8C,
    MENU_REQUEST=0x8D,
    MENU_STATUS=0x8E,
    GIVE_DEVICE_POWER_STATUS=0x8F,
    REPORT_POWER_STATUS=0x90,
    GET_MENU_LANGUAGE=0x91,
    SELECT_ANALOGUE_SERVICE=0x92,
    SELECT_DIGITAL_SERVICE=0x93,
    SET_DIGITAL_TIMER=0x97,
    CLEAR_DIGITAL_TIMER=0x99,
    SET_AUDIO_RATE=0x9A,
    INACTIVE_SOURCE=0x9D,
    CEC_VERSION=0x9E,
    GET_CEC_VERSION=0x9F,
    VENDOR_COMMAND_WITH_ID=0xA0,
    CLEAR_EXTERNAL_TIMER=0xA1,
    SET_EXTERNAL_TIMER=0xA2,
    ABORT=0xFF
};

enum CEC_LOGICAL_ADDRESS
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
};

//      PUBLIC FUNCTIONS PROTOTYPES
bool AppCec_Init(void);
bool AppCec_Handler(void);
void AppCec_SetFullLog(bool state);

#endif /* APP_CEC_H */
