////////////////////////////////////////////////////////////////////////////////
/// @file    main.c
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _MAIN_C_

// Files includes


#include "main.h"
#include "tim3_pwm_output.h"
#include "delay.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Constants
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is main entrance.
/// @param  None.
/// @retval  0.
////////////////////////////////////////////////////////////////////////////////
s32 main(void)
{
    u8 dir = 1;

    DELAY_Init();
    TIM3_GPIO_Init();
    TIM3_PWM_Init(99, 0);
    TIM_SetCompare1(TIM3, 49);
    while (1) {
        DELAY_Ms(40);
        TIM_ForcedOC1Config(TIM3, TIM_OCMode_PWM2);
        TIM_Cmd(TIM3, ENABLE);
        DELAY_Ms(40);
        TIM_Cmd(TIM3, DISABLE);
        if(dir == 1) {
            dir = 0;
            TIM_ForcedOC1Config(TIM3, TIM_ForcedAction_Active);
        }
        else {
            dir = 1;
            TIM_ForcedOC1Config(TIM3, TIM_ForcedAction_InActive);
        }

    }
}



/// @}

/// @}

/// @}
