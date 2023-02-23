////////////////////////////////////////////////////////////////////////////////
/// @file     tim1_monopulse.c
/// @author   AE TEAM
/// @brief    monopulse output.
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
#define _TIM1_MONOPULSE_C_

// Files includes
#include "tim1_monopulse.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup TIM1_MONOPULSE
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup TIM_Exported_Functions
/// @{

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
    GPIO_InitStruct.GPIO_Pin     = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin     = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode    = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
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
/// @brief  Monopulse output mode initialization configuration
/// @note    It must be careful of the Chip Version.
/// @param  psc: Clock frequency division value.
/// @param  arr: Preloading value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM1_Monopulse_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
    TIM_OCInitTypeDef  TIM_OCInitStruct;
    TIM_ICInitTypeDef  TIM_ICInitStruct;

    //Enable the TIM1 clock. The default clock source is PCLK2.
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1, ENABLE);

    TIM_DeInit(TIM1);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
    TIM_TimeBaseStruct.TIM_Period = arr;
    TIM_TimeBaseStruct.TIM_Prescaler = psc;
    //Setting Clock Segmentation
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;
    ///TIM Upward Counting Mode
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);

    TIM_OCStructInit(&TIM_OCInitStruct);
    //Select Timer Mode: TIM Pulse Width Modulation Mode 2
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    //Setting the Pulse Value of the Capture Comparison Register to be Loaded
    TIM_OCInitStruct.TIM_Pulse = arr / 2;
    //Output polarity: TIM output is more polar
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OC1Init(TIM1, &TIM_OCInitStruct);
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

    TIM_ICStructInit(&TIM_ICInitStruct);

    TIM_ICInitStruct.TIM_Channel     = TIM_Channel_2;
    TIM_ICInitStruct.TIM_ICPolarity  = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICFilter    = 0x0;
    TIM_ICInit(TIM1, &TIM_ICInitStruct);

    TIM_ARRPreloadConfig(TIM1, ENABLE);
    //Generate a single pulse: the counter stops at the next update event
    TIM_SelectOnePulseMode(TIM1, TIM_OPMode_Single);
    //TIM filtered timer input 2
    TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);
    //The counter starts on the rising edge of the trigger
    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Trigger);
    TIM_SetCounter(TIM1, 0);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_Cmd(TIM1, ENABLE);
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
    TIM_OCInitStruct.TIM_Pulse = (arr / 4) * 3;
    //Output polarity: TIM output is more polar
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM3, &TIM_OCInitStruct);

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_SetCounter(TIM3, 0);

    TIM_Cmd(TIM3, ENABLE);
}
/// @}


/// @}

/// @}



