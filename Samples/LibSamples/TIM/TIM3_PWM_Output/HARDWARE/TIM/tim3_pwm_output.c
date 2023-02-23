////////////////////////////////////////////////////////////////////////////////
/// @file     tim3_pwm_output.c
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
// Define to prevent recursive inclusion
#define _TIM3_PWM_OUTPUT_C_

// Files includes
#include "tim3_pwm_output.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief  TIM3 Pin Config
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM3_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_2);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  PWM output mode initialization configuration
/// @note    It must be careful of the Chip Version.
/// @param  psc: Clock frequency division value.
/// @param  arr: Preloading value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM3_PWM_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
    TIM_OCInitTypeDef  TIM_OCInitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3, ENABLE);

    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
    TIM_TimeBaseStruct.TIM_Period = arr;
    TIM_TimeBaseStruct.TIM_Prescaler = psc;
    //Setting Clock Segmentation
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
    ///TIM Upward Counting Mode
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct);

    TIM_OCStructInit(&TIM_OCInitStruct);
    //Select Timer Mode: TIM Pulse Width Modulation Mode 2
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    //Setting the Pulse Value of the Capture Comparison Register to be Loaded
    TIM_OCInitStruct.TIM_Pulse = 0;
    //Output polarity: TIM output is more polar
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM3, &TIM_OCInitStruct);

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);

    TIM_Cmd(TIM3, ENABLE);
}
/// @}


/// @}

/// @}



