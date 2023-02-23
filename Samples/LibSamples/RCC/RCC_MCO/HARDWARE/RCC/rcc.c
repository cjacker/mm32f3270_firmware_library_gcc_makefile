////////////////////////////////////////////////////////////////////////////////
/// @file    rcc.c
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
#define _RCC_C_

// Files includes
#include "rcc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup RCC
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup RCC_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  set MCO, use LSI
/// @param  void
/// @retval None
////////////////////////////////////////////////////////////////////////////////
static void MCO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    GPIO_PinAFConfig( GPIOA, GPIO_PinSource8, GPIO_AF_0);
    //MCO use PA8

    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed =  GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    RCC_MCOConfig(RCC_MCO_LSI);//
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Tamper test
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_OUT_Init(void)
{

    MCO_Config();

}





/// @}

/// @}

/// @}
