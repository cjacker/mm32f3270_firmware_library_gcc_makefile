////////////////////////////////////////////////////////////////////////////////
/// @file    dma.c
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
#define _DMA_C_

// Files includes



#include "hal_device.h"
#include "hal_conf.h"
#include "stdio.h"
#include "dma.h"
#include "delay.h"
#include "led.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup DMA
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup DMA_Exported_Constants
/// @{





vu8 gDMA1Flag1 = 0x0;
vu8 gDMA1Flag2 = 0x0;
u8 gDMATxData[64 * 4];
u8 gDMARxData[64 * 4];





s32 DMA_FunctionTest(void)
{
    DMA_m8tom8_test();
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  DMA1 Channel 2 and 3 IRQ Handler
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA1_Channel2_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_IT_HT2)) {
        DMA_ClearITPendingBit(DMA1_IT_HT2);
        gDMA1Flag1 = 0x1;
    }
    if(DMA_GetITStatus(DMA1_IT_TC2)) {
        DMA_ClearITPendingBit(DMA1_IT_TC2);
        gDMA1Flag2 = 0x1;
    }

}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Check DMA status
/// @param  DMA_FLAG  input check bits.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMAcheckStatus(DMA_Flags_TypeDef DMA_FLAG)
{
    while(1) {
        if(DMA_GetFlagStatus(DMA_FLAG)) {
            DMA_ClearFlag(DMA_FLAG);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  DMA Channel Disable
/// @param  DMAy_Channelx Channel number.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMAdisable(DMA_Channel_TypeDef* DMAy_Channelx)
{
    DMA_Cmd(DMAy_Channelx, DISABLE);
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the DMA and test DMA move 64 8bits data for A address to
/// B address.
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_m8tom8_test(void)
{
    u32 i;
    u8* p;
    u8* q;
    u32 temp;
    DMA_InitTypeDef DMA_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    p = (u8*)gDMATxData;
    q = (u8*)gDMARxData;
    for(i = 0; i < 64; i++) {
        *(p + i) = i + 1;
    }

    DMA_DeInit(DMA1_Channel2);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1, ENABLE);
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)gDMARxData;
    DMA_InitStruct.DMA_MemoryBaseAddr = (u32)gDMATxData;
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStruct.DMA_BufferSize = 64;
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStruct.DMA_Priority = DMA_Priority_Low;
    DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;
    DMA_InitStruct.DMA_Auto_reload = DMA_Auto_Reload_Disable;
    DMA_Init(DMA1_Channel2, &DMA_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel2_IRQn ;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
    DMA_ITConfig(DMA1_Channel2, DMA_IT_HT, ENABLE);
    gDMA1Flag1 = 0x0;
    gDMA1Flag2 = 0x0;
    DMA_Cmd(DMA1_Channel2, ENABLE);

    while(1) {
        if(gDMA1Flag1) {
            gDMA1Flag1 = 0x0;
            break;
        }
    }
    while(1) {
        if(gDMA1Flag2) {
            gDMA1Flag2 = 0x0;
            break;
        }
    }

    DMA_Cmd(DMA1_Channel2, DISABLE);
    temp = 0;
    for(i = 0; i < 64; i++) {
        if((u8)(*p++) == (u8)(*q++)) {
            temp++;
        }
    }
}

/// @}

/// @}

/// @}
