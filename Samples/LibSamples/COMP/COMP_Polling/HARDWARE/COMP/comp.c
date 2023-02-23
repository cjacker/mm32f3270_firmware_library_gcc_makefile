////////////////////////////////////////////////////////////////////////////////
/// @file    comp.c
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
#define _COMP_C_

// Files includes
#include "comp.h"


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup COMP
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup COMPExported_Constants
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is comp test entrance.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_Test(void)
{
    RCC_ConfigInit();
    Comp_Config(COMP1);
    COMPOut_GPIO_ConfigInit();
    COMPOutPA6_GPIO_ConfigInit();
    COMPOutPA11_GPIO_ConfigInit();
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  GPIO config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMPOut_GPIO_ConfigInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_7);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  GPIO config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMPOutPA6_GPIO_ConfigInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_7);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  GPIO config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMPOutPA11_GPIO_ConfigInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_7);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  COMP GPIO config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void COMP_GPIO_ConfigInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_1 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  GPIO config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_ConfigInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}



////////////////////////////////////////////////////////////////////////////////
/// @brief  COMP config
/// @note   None.
/// @param  : COMP_Selection_COMPx
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void Comp_Config(COMP_Selection_TypeDef COMP_Selection_COMPx)
{
    COMP_InitTypeDef COMP_InitStruct;
    GPIO_ConfigInit();
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_COMP, ENABLE);
    COMP_StructInit(&COMP_InitStruct);
    COMP_InitStruct.COMP_InvertingInput = COMP_InvertingInput_IO2;
    COMP_InitStruct.COMP_NonInvertingInput = COMP_NonInvertingInput_IO2;
    COMP_InitStruct.COMP_Output = COMP_Output_None;
    COMP_InitStruct.COMP_OutputPol = COMP_OutputPol_NonInverted;
    COMP_InitStruct.COMP_Hysteresis = COMP_Hysteresis_No;
    COMP_InitStruct.COMP_Mode = COMP_Mode_MediumSpeed;
    COMP_InitStruct.OFLT = COMP_Filter_4_Period;
    COMP_Init(COMP_Selection_COMPx, &COMP_InitStruct);

    COMP_Cmd(COMP_Selection_COMPx, ENABLE);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  RCC config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void RCC_ConfigInit(void)
{

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);

}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Check COMP status
/// @note   None.
/// @param  : COMP_Selection_COMPx
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
u8 Comp_StatusCheck(COMP_Selection_TypeDef COMP_Selection_COMPx)
{
    u8 chCapStatus = 2;
    if(COMP_GetOutputLevel(COMP_Selection_COMPx) == 0) {
        chCapStatus = 0;
    }
    else {
        chCapStatus = 1;
    }
    return chCapStatus;
}


/// @}

/// @}

/// @}
