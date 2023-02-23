////////////////////////////////////////////////////////////////////////////////
/// @file    pwr.c
/// @author  AE TEAM
/// @brief    In window comparator mode,The transformation results are detected
///           Set the threshold value from 0 to 3V, and connect PB6 and PA0 with
///           jumper cap to see the effect.
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
#define _PWR_C_

// Files includes
#include "hal_device.h"
#include "hal_conf.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup PWR
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup PWR_Exported_Functions
/// @{

void SystemInit(void);

////////////////////////////////////////////////////////////////////////////////
/// @brief  NVIC Exti Config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void EXTI_NVIC_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;

    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  EXTI Config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void EXTI_Config(void)
{
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_StructInit(&EXTI_InitStruct);
    //External interrupt Mode
    SYSCFG_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    EXTI_StructInit(&EXTI_InitStruct);
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  External interrupt wake-up standby initialization
/// @note   External Wake-up Pin Selection.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init( GPIOA, &GPIO_InitStruct);

}
////////////////////////////////////////////////////////////////////////////////
/// @brief  enter sleep
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void PWR_SLEEP_ExtiInit(void)
{
    GPIO_Configuration();
    EXTI_Config();
    EXTI_NVIC_Init();
    __WFI();
    //After enter STOP mode, the SYSCLK changed to HSI/6
    //Need re-initialize the SYSCLK , set HSI/4+PLL to 48Mhz as SYSCLK
    SystemInit();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  External interrupt 0, clears interrupt flag after entering.
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void EXTI0_IRQHandler(void)
{
    EXTI_ClearITPendingBit(EXTI_Line0);
}


/// @}

/// @}

/// @}
