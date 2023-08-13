//      INCLUDES
#include "DrvIrSirc.h"

#include <string.h>
#include "stm32h5xx_hal.h"

//      LOCAL TYPEDEFS DEFINES AND ENUMS
#define SIRC_MAX_NIBBLES            65U   // Start phase + 20 nibbles = max 65 if transmitting only ones
#define SIRC_REPEAT_INTERVAL        36U   // Repeat commands with 22ms interval

//      EXTERN VARIABLES
extern TIM_HandleTypeDef            htim1;
extern TIM_HandleTypeDef            htim2;

//      LOCAL VARIABLES
static bool         transmitting                    = false;
static bool         nibbles[SIRC_MAX_NIBBLES]       = {0};
static uint8_t      nibble_index                    = 0;
static uint8_t      nibbles_count                   = 0;
static uint8_t      tx_repeat                       = 0;
static uint8_t      tx_pause_counter                = 0;

//      STATIC FUNCTIONS PROTOTYPES

/// @brief ISR callback in charge of sending the nibbles
static void NibbleTimerPeriodClbk(struct __TIM_HandleTypeDef *htim);

/// @brief  Convert a binary value to a mark/space list
static uint8_t MakeNibbles(bool* nibbles, uint8_t value, uint8_t bits);

//      STATIC FUNCTIONS DEFINITION
static void NibbleTimerPeriodClbk(struct __TIM_HandleTypeDef *htim)
{
    // If we're in the blank time between two repeats
    if (tx_pause_counter > 0)
    {
        tx_pause_counter--;

        // Pause is finished
        if(tx_pause_counter == 0)
        {
            nibble_index = 0;
            tx_pause_counter   = false;
        }
        else
        {
            return;
        }
    }

    // Send each nibble
    if (nibble_index < nibbles_count)
    {
        // Mark
        if (nibbles[nibble_index])
        {
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        }
        // Space
        else
        { 
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
        }

        nibble_index++;
    }
    else
    {
        if (tx_repeat == 0)
        {
            // End of transmission
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
            HAL_TIM_Base_Stop_IT(&htim2);
            transmitting = false;
        }
        else
        {
            tx_pause_counter = SIRC_REPEAT_INTERVAL;
            tx_repeat--;
        }
    }
}

static uint8_t MakeNibbles(bool* nibbles, uint8_t value, uint8_t bits)
{
    uint8_t count = 0;

    for (uint8_t i = 0; i < bits; i++)
    {
        // 1 is 1.2ms mark and 0.6ms space
        if (((value >> i) & 0x01) == 1)
        {
            *nibbles++ = true;
            *nibbles++ = true;
            *nibbles++ = false;
            count += 3;
        }
        // 0 is 0.6ms mark and 0.6ms space
        else
        {
            *nibbles++ = true;
            *nibbles++ = false;
            count += 2;
        }
    }

    return count;
}

//      PUBLIC FUNCTIONS DEFINITION
bool DrvIrSirc_Init(void)
{
    // We assume here that TIM1 is configured to output a carrier signal of 40kHz
    // TIM2 will be used to generate an interrupt each 0.6ms
    htim2.PeriodElapsedCallback = NibbleTimerPeriodClbk;

    return true;
}

bool DrvIrSirc_IsReady(void)
{
    return !transmitting;
}

bool DrvIrSirc_Transmit(const SIRC_FRAME* frame, uint8_t repeats)
{
    if (transmitting)
    {
        return false;
    }

    // Convert command to a list of nibbles
    // Start phase is 2.4ms mark and 0.6ms space
    nibbles[0] = true;
    nibbles[1] = true;
    nibbles[2] = true;
    nibbles[3] = true;
    nibbles[4] = false;

    nibbles_count = 5;

    nibbles_count += MakeNibbles(&nibbles[nibbles_count], frame->command, 7);

    if (frame->version == C7_A5)
    {
        nibbles_count += MakeNibbles(&nibbles[nibbles_count], frame->address, 5);
    }
    else
    {
        nibbles_count += MakeNibbles(&nibbles[nibbles_count], frame->address, 8);
    }

    if (frame->version == C7_A5_EXT)
    {
        nibbles_count += MakeNibbles(&nibbles[nibbles_count], frame->extended, 8);
    }

    // Initialize command transmission
    transmitting = true;
    nibble_index = 0;
    tx_pause_counter   = 0;
    tx_repeat    = repeats;

    // Start sampling timer
    if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
    {
        return false;
    }

    return true;
}
