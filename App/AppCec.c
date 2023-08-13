//      INCLUDES
#include "AppCec.h"
#include "DrvCec.h"

#include <string.h>
#include <stdio.h>

//      LOCAL TYPEDEFS DEFINES AND ENUMS
#define MAX_CALLBACKS_CNT       10U
#define FULL_LOG_RX             1U

typedef struct
{
    CEC_LOGICAL_ADDRESS target;
    CEC_LOGICAL_ADDRESS source;
    CEC_COMMANDS        opcode;
    APP_CEC_CLBK        callback;
}
CEC_CLBK_STRUCT;

//      EXTERN VARIABLES

//      LOCAL VARIABLES

#if FULL_LOG_RX
    const char* CEC_COMMANDS_STRING[] = {
        "FEATURE_ABORT",NULL,NULL,NULL,"IMAGE_VIEW_ON","TUNER_STEP_INCREMENT","TUNER_STEP_DECREMENT","TUNER_DEVICE_STATUS",
        "GIVE_TUNER_DEVICE_STATUS","RECORD_ON","RECORD_STATUS","RECORD_OFF",NULL,"TEXT_VIEW_ON",NULL,"RECORD_TV_SCREEN",
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"GIVE_DECK_STATUS","DECK_STATUS",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"SET_MENU_LANGUAGE","CLEAR_ANALOGUE_TIMER",
        "SET_ANALOGUE_TIMER","TIMER_STATUS","STANDBY",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"PLAY","DECK_CONTROL",
        "TIMER_CLEARED_STATUS","USER_CONTROL_PRESSED","USER_CONTROL_RELEASED","SET_OSD_NAME",
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,"SET_OSD_STRING",NULL,NULL,"SET_TIMER_PROGRAM_TITLE",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        "SYSTEM_AUDIO_MODE_REQUEST","GIVE_AUDIO_STATUS","SET_SYSTEM_AUDIO_MODE",NULL,NULL,NULL,NULL,NULL,NULL,NULL,"REPORT_AUDIO_STATUS",
        NULL,NULL,"GIVE_SYSTEM_AUDIO_MODE_STATUS","SYSTEM_AUDIO_MODE_STATUS",NULL,"ROUTING_CHANGE","ROUTING_INFORMATION","ACTIVE_SOURCE",
        "GIVE_PHYSICAL_ADDRESS","REPORT_PHYSICAL_ADDRESS","REQUEST_ACTIVE_SOURCE","SET_STREAM_PATH","DEVICE_VENDOR_ID",NULL,
        "VENDOR_COMMAND","VENDOR_REMOTE_BUTTON_DOWN","VENDOR_REMOTE_BUTTON_UP","GIVE_DEVICE_VENDOR_ID","MENU_REQUEST","MENU_STATUS",
        "GIVE_DEVICE_POWER_STATUS","REPORT_POWER_STATUS","GET_MENU_LANGUAGE","SELECT_ANALOGUE_SERVICE","SELECT_DIGITAL_SERVICE",
        NULL,NULL,NULL,"SET_DIGITAL_TIMER",NULL,"CLEAR_DIGITAL_TIMER","SET_AUDIO_RATE",NULL,NULL,"INACTIVE_SOURCE","CEC_VERSION",
        "GET_CEC_VERSION","VENDOR_COMMAND_WITH_ID","CLEAR_EXTERNAL_TIMER","SET_EXTERNAL_TIMER","REPORT_SHORT_AUDIO_DESCRIPTOR",
        "REQUEST_SHORT_AUDIO_DESCRIPTOR",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"INITIATE_ARC","REPORT_ARC_INITIATED","REPORT_ARC_TERMINATED",
        "REQUEST_ARC_INITIATION","REQUEST_ARC_TERMINATION","TERMINATE_ARC",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
        NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"CDC_MESSAGE",NULL,NULL,NULL,NULL,NULL,NULL,"ABORT",
    };

    const char* CEC_LOGICAL_ADDRESS_STRING[] = {
        "TV","RECORDING_1","RECORDING_2","TUNER_1","PLAYBACK_1","AUDIO_SYSTEM","TUNER_2","TUNER_3",
        "PLAYBACK_2","RECORDING_3","TUNER_4","PLAYBACK_3","BACKUP_1","BACKUP_2","SPECIFIC",
        "UNREGISTERED_BROADCAST","CEC_DEVICE_COUNT",
    };
#endif

static uint8_t          callbacks_count                   = 0;
static CEC_CLBK_STRUCT  callbacks_list[MAX_CALLBACKS_CNT] = {0};

//      STATIC FUNCTIONS PROTOTYPES

//      STATIC FUNCTIONS DEFINITION
void CecRxHandler(CEC_COMMAND* cmd)
{
#if FULL_LOG_RX
        printf("[AppCec] Received command ");
        if (cmd->payload_size == 1)
        {
            printf("POLLING");
        }
        else
        {
            if (CEC_COMMANDS_STRING[cmd->opcode] != NULL)
            {
                printf("%s", CEC_COMMANDS_STRING[cmd->opcode]);
            }
            else
            {
                printf("UNKNOWN %02x", cmd->opcode);
            }
        }
        printf(" from %s to %s", CEC_LOGICAL_ADDRESS_STRING[cmd->source], CEC_LOGICAL_ADDRESS_STRING[cmd->target]);

        if (cmd->payload_size > 0)
        {
            printf(" with payload: \r\n\t");
            for (uint8_t i = 0; i < cmd->payload_size; i++)
            {
                printf("%02x ", cmd->payload[i]);
            }
        }

        printf("\r\n");
#endif

    for (size_t i = 0; i < callbacks_count; i++)
    {
        if (   callbacks_list[i].target == cmd->target
            && callbacks_list[i].source == cmd->source
            && callbacks_list[i].opcode == cmd->opcode)
        {
            callbacks_list[i].callback(cmd);
        }
    }
}

void CecErrorHandler(void)
{
    printf("[AppCec] Error\r\n");
}

//      PUBLIC FUNCTIONS DEFINITION
bool AppCec_Init(void)
{
    if (!DrvCec_Init())
    {
        return false;
    }

    if (!DrvCec_RegisterRxHandler(CecRxHandler) || !DrvCec_RegisterErrorHandler(CecErrorHandler))
    {
        return false;
    }

    return true;
}

bool AppCec_Handler(void)
{
    return DrvCec_Handler();
}

bool AppCec_RegisterCallback(CEC_LOGICAL_ADDRESS source, CEC_LOGICAL_ADDRESS target, CEC_COMMANDS opcode, APP_CEC_CLBK clbk)
{
    if (callbacks_count < MAX_CALLBACKS_CNT)
    {
        // Two callbacks might be assigned to the same command
        callbacks_list[callbacks_count].source   = source;
        callbacks_list[callbacks_count].target   = target;
        callbacks_list[callbacks_count].opcode   = opcode;
        callbacks_list[callbacks_count].callback = clbk;
        callbacks_count++;

        return true;
    }

    return false;
}
