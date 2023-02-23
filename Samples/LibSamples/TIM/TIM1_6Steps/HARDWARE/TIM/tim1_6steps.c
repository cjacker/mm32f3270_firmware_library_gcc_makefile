////////////////////////////////////////////////////////////////////////////////
/// @file     tim_6Steps.c
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
#define _TIM_6STEPS_C_

// Files includes
#include "tim1_6steps.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup TIM_6STEPS
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup TIM_Exported_Functions
/// @{

u32 step = 1;
////////////////////////////////////////////////////////////////////////////////
/// @brief  Timer Pin Config
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM1_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA | RCC_AHBENR_GPIOB, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_1);
    GPIO_StructInit(&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Tim1 Base initialization configuration
/// @note
/// @param  psc: Clock frequency division value.
/// @param  arr: Preloading value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM1_PWM_Init(u16 arr, u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
    TIM_OCInitTypeDef  TIM_OCInitStruct;
    TIM_BDTRInitTypeDef  TIM_BDTRInitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_TIM1, ENABLE);

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
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 2047;
    TIM_OCInitStruct.TIM_OCNPolarity = (TIMCCxNP_Typedef)TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Set;

    TIM_OC1Init(TIM1, &TIM_OCInitStruct);

    TIM_OCInitStruct.TIM_Pulse = 1023;
    TIM_OC2Init(TIM1, &TIM_OCInitStruct);

    TIM_OCInitStruct.TIM_Pulse = 511;
    TIM_OC3Init(TIM1, &TIM_OCInitStruct);

    TIM_CCPreloadControl(TIM1, ENABLE);
    TIM_ITConfig(TIM1, TIM_IT_COM, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_BDTRStructInit(&TIM_BDTRInitStruct);
    // Automatic Output enable, Break, dead time and lock configuration
    TIM_BDTRInitStruct.TIM_OSSIState = TIM_OSSIState_Enable;
    TIM_BDTRInitStruct.TIM_OSSRState = TIM_OSSRState_Enable;
    TIM_BDTRInitStruct.TIM_Break = TIM_Break_Enable;
    TIM_BDTRInitStruct.TIM_BreakPolarity = TIM_BreakPolarity_High;
    TIM_BDTRInitStruct.TIM_DeadTime = 1;
    TIM_BDTRInitStruct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStruct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(TIM1, &TIM_BDTRInitStruct);

    TIM_Cmd(TIM1, ENABLE);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  NVIC Configure, Applicable to Cortex M0 or M3 processors.
/// @param  NVIC Channel, Priority or SubPriority.
/// @arg    ch: IRQChannel
/// @arg    pri: Priority, Use only Cortex-M3
/// @arg    sub: SubPriority
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void NVIC_Configure(u8 ch, u8 pri)
{
    NVIC_InitTypeDef  NVIC_InitStruct;

    NVIC_InitStruct.NVIC_IRQChannel = ch;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = pri;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  TIM1_BRK_UP_TRG_COM Handler Funtion
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM1_TRG_COM_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM1, TIM_IT_COM);
    if(step == 1) {
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        //  Channel1 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        //  Channel2 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
        step++;


    }
    else if(step == 2) {
        // Next step: Step 3 Configuration
        //  Channel1 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        //  Channel2 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Enable);
        step++;
    }
    else if(step == 3) {
        // Next step: Step 4 Configuration
        //  Channel2 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        //  Channel1 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
        step++;
    }
    else if(step == 4) {
        // Next step: Step 5 Configuration
        //  Channel3 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Disable);

        //  Channel2 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        //  Channel1 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Enable);
        step++;
    }
    else if(step == 5) {
        // Next step: Step 6 Configuration
        //  Channel1 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_2, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
        step++;
    }
    else if(step == 6) {
        // Next step: Step 1 Configuration ----------------------------
        //  Channel2 configuration
        TIM_CCxCmd(TIM1, TIM_Channel_2, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_2, TIM_CCxN_Disable);

        //  Channel1 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_1, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_1, TIM_CCx_Enable);
        TIM_CCxNCmd(TIM1, TIM_Channel_1, TIM_CCxN_Disable);

        //  Channel3 configuration
        TIM_SelectOCxM(TIM1, TIM_Channel_3, TIM_OCMode_PWM1);
        TIM_CCxCmd(TIM1, TIM_Channel_3, TIM_CCx_Disable);
        TIM_CCxNCmd(TIM1, TIM_Channel_3, TIM_CCxN_Enable);
        step = 1;
    }
}
/// @}


/// @}

/// @}



