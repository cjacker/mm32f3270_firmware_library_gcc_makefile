////////////////////////////////////////////////////////////////////////////////
/// @file     tim1_pwm_shift.c
/// @author   AE TEAM
/// @brief    PWM output.
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
// Define to prevent recursive inclusion  --------------------------------------
#define _TIM1_PWM_SHIFT_C_

// Files includes  -------------------------------------------------------------
#include "tim1_pwm_shift.h"
extern u32 SystemCoreClock;
////////////////////////////////////////////////////////////////////////////////
/// @brief  Timer Pin Config
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM1_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Time1 initialization configuration
/// @note   It must be careful of the Chip Version.
/// @param  psc: Clock frequency division value.
/// @param  arr: Preloading value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM1_PWM_Shift_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
    TIM_OCInitTypeDef  TIM_OCInitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1, ENABLE);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
    TIM_TimeBaseStruct.TIM_Period = arr;
    TIM_TimeBaseStruct.TIM_Prescaler = psc;
    //Setting Clock Segmentation
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
    ///TIM Upward Counting Mode
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);

    TIM_OCStructInit(&TIM_OCInitStruct);
    //Select Timer Mode: TIM Pulse Width Modulation Mode 2
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    //Setting the Pulse Value of the Capture Comparison Register to be Loaded
    TIM_OCInitStruct.TIM_Pulse = 300;
    //Output polarity: TIM output is more polar
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1, &TIM_OCInitStruct);

    TIM_OCInitStruct.TIM_Pulse = 350;
    TIM_OC2Init(TIM1, &TIM_OCInitStruct);

    TIM_OCInitStruct.TIM_Pulse = 250;
    TIM_OC3Init(TIM1, &TIM_OCInitStruct);

    TIM_SetCCR2FALL(TIM1, 250);
    TIM_SetCCR3FALL(TIM1, 350);

    TIM_PWMShiftConfig(TIM1, TIM_PDER_CCR2SHIFTEN | TIM_PDER_CCR3SHIFTEN, ENABLE);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_Cmd(TIM1, ENABLE);
}
/// @}


/// @}

/// @}



