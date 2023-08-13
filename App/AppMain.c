//      INCLUDES
#include "AppCec.h"
#include "DrvIrSirc.h"

#include <string.h>
#include <stdio.h>

//      LOCAL TYPEDEFS AND ENUMS

//      EXTERN VARIABLES

//      LOCAL VARIABLES

// Sony remote power button command
static const SIRC_FRAME RM_AAU013_POWER = {
    .command  = 0x15,
    .address  = 0x30,
    .extended = 0x00,
    .version  = C7_A8
};

static bool audio_on = false;

//      STATIC FUNCTIONS PROTOTYPES
void Cec_OnOffClbk(CEC_COMMAND* cmd);

//      STATIC FUNCTIONS DEFINITION
void Cec_OnOffClbk(CEC_COMMAND* cmd)
{
    if (DrvIrSirc_IsReady())
    {
        // Power on/off the audio amplifier over infrared
        DrvIrSirc_Transmit(&RM_AAU013_POWER, 2);
    }

    if (cmd->opcode == STANDBY)
    {
        audio_on = false;
        printf("[AppMain] Switching audio off\r\n");
    }
    else
    {
        audio_on = true;
        printf("[AppMain] Switching audio on\r\n");
    }
}

//      PUBLIC FUNCTIONS DEFINITION
bool AppMain_Init(void)
{
    if (!AppCec_Init() || !DrvIrSirc_Init())
    {
        return false;
    }

    // Register callback to global power on and off the audio system (TODO)
    if (!AppCec_RegisterCallback(TV, UNREGISTERED_BROADCAST, STANDBY, Cec_OnOffClbk)
        || !AppCec_RegisterCallback(TV, SPECIFIC, GIVE_DEVICE_POWER_STATUS, Cec_OnOffClbk))
    {
        return false;
    }

    return true;
}

bool AppMain_Handler(void)
{
    return AppCec_Handler();
}