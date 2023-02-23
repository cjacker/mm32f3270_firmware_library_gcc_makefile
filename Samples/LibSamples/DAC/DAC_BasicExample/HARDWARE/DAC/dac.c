////////////////////////////////////////////////////////////////////////////////
/// @file    dac.c
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
#define _DAC_C_

// Files includes

#include "dac.h"
#include "led.h"
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
/// @brief  : DAC Channel Single
/// @param  : FirstBackupData
/// @retval : None
////////////////////////////////////////////////////////////////////////////////
void DAC_Channel_Single(u32 DAC_Channel_x)
{
    DAC_InitTypeDef  DAC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* DAC Periph clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_DAC, ENABLE);
    /* GPIOA Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    DAC_InitStructure.DAC_Trigger = DAC_Trigger_Software ;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;

    DAC_Init((emDACCH_TypeDef)DAC_Channel_x, &DAC_InitStructure);

    DAC_Cmd((emDACCH_TypeDef)DAC_Channel_x, ENABLE);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  : DAC Software Trigger Data
/// @param  : Portx , State
/// @retval : None
////////////////////////////////////////////////////////////////////////////////
void DAC_SoftwareTrigger_Data(u32 DAC_Channel_x, u16 uiData)
{
    u8 ucFlag = 0;
    if((emDACCH_TypeDef)DAC_Channel_x == DAC_Channel_1) {
        ucFlag = 1;
        DAC_SetChannel1Data(DAC_Align_12b_R, uiData & 0xfff);
    }
    else if((emDACCH_TypeDef)DAC_Channel_x == DAC_Channel_2) {
        ucFlag = 1;
        DAC_SetChannel2Data(DAC_Align_12b_R, uiData & 0xfff);
    }
    if(ucFlag == 1) {
        DAC_SoftwareTriggerCmd((emDACCH_TypeDef)DAC_Channel_x, ENABLE);
    }
}


/// @}

/// @}

/// @}
