////////////////////////////////////////////////////////////////////////////////
/// @file    exti.c
/// @author  AE TEAM
/// @brief   key intput.
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
#define _EXTI_C_

// Files includes
#include "exti.h"
#include "delay.h"
#include "led.h"


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup KEY
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup KEY_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize KEY GPIO pin
/// @note   if use jtag/swd interface GPIO PIN as KEY, need to be careful,
///         can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA | RCC_AHBENR_GPIOB | RCC_AHBENR_GPIOC, ENABLE);

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1;                                 //PB1, K1
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;                               //set as pull up input
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_2;                                  //PB2, K2
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;                               //set as pull down input
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10 | GPIO_Pin_11;                   //PB10 K3, PB11 K4
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;                               //set as pull up input
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize exti nvic config
/// @note   if use jtag/swd interface GPIO PIN as KEY, need to be careful,
///         can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void EXTI_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

}
////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize exti interrupt Line
/// @note   if use jtag/swd interface GPIO PIN as KEY, need to be careful,
///         can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void EXTI_NVIC_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);

    //PB.1 use EXTI line 1
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);
    EXTI_StructInit(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = EXTI_Line1;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
    //PB.2 use EXTI line 2
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource2);
    EXTI_InitStruct.EXTI_Line = EXTI_Line2;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);

    //PB.10 use EXTI line 10
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10);
    EXTI_InitStruct.EXTI_Line = EXTI_Line10;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
    //PB.11 use EXTI line 11
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource11);
    EXTI_InitStruct.EXTI_Line = EXTI_Line11;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  This function EXTI config
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI_Config(void)
{
    EXTI_NVIC_Config();
    EXTI_NVIC_Init();
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is EXTI0 1 Handler
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI1_IRQHandler(void)
{
    u16 EXTI_DELAY = 0;
    for(EXTI_DELAY = 0; EXTI_DELAY < 1000; EXTI_DELAY++);

    if(KEY1 == 1) {
        LED1_TOGGLE();
    }
    EXTI_ClearFlag(EXTI_Line1);

}

////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is EXTI0 1 Handler
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI2_IRQHandler(void)
{
    u16 EXTI_DELAY = 0;
    for(EXTI_DELAY = 0; EXTI_DELAY < 1000; EXTI_DELAY++);
    if(WK_UP == 0) {
        LED2_TOGGLE();
    }
    EXTI_ClearFlag(EXTI_Line2);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is EXTI4 15 Handler
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI15_10_IRQHandler(void)
{
    u16 EXTI_DELAY = 0;
    for(EXTI_DELAY = 0; EXTI_DELAY < 1000; EXTI_DELAY++);
    if(KEY3 == 0) {
        LED3_TOGGLE();
    }
    else if(KEY4 == 0) {
        LED4_TOGGLE();
    }
    EXTI_ClearFlag(EXTI_Line10 | EXTI_Line13 | EXTI_Line11);
}


/// @}


/// @}

/// @}

