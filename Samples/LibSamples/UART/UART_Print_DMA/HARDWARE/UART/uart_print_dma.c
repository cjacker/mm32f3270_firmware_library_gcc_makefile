////////////////////////////////////////////////////////////////////////////////
/// @file     uart_print_dma.c
/// @author   AE TEAM
/// @brief    Completed UART's print feature by using plliong meathod.
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
#define _UART_PRINT_DMA_C_

// Files includes
#include "uart_print_dma.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief  UART1 Pin Config
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART1_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);
    //UART1_TX   GPIOA.9
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    //UART1_RX    GPIOA.10
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Serial port initialization configuration
/// @note    It must be careful of the Chip Version.
/// @param  baudrate: Baud rate
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void UART1_DMA_Init(u32 baudrate)
{
    UART_InitTypeDef UART_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_UART1, ENABLE);

    //Baud rate
    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.BaudRate = baudrate;
    //The word length is in 8-bit data format.
    UART_InitStruct.WordLength = UART_WordLength_8b;
    UART_InitStruct.StopBits = UART_StopBits_1;
    //No even check bit.
    UART_InitStruct.Parity = UART_Parity_No;
    //No hardware data flow control.
    UART_InitStruct.HWFlowControl = UART_HWFlowControl_None;
    UART_InitStruct.Mode = UART_Mode_Rx | UART_Mode_Tx;

    UART_Init(UART1, &UART_InitStruct);
    UART_Cmd(UART1, ENABLE);

    UART1_GPIO_Init();
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  DMA and interrupt priority configuration
/// @note   Configure parameters according to requirements.
/// @param  DMA_CHx (channel).
/// @param  cpar    (UART address).
/// @param  cmar    (data address).
/// @param  cndtr   (data length).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_Config(DMA_Channel_TypeDef* dam_chx, u32 cpar, u32 cmar, u16 cndtr)
{
    DMA_InitTypeDef DMA_InitStruct;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1, ENABLE);

    DMA_DeInit(dam_chx);
    DMA_StructInit(&DMA_InitStruct);
    //DMA transfer peripheral address
    DMA_InitStruct.DMA_PeripheralBaseAddr = cpar;
    //DMA transfer memory address
    DMA_InitStruct.DMA_MemoryBaseAddr = cmar;
    //DMA transfer direction from peripheral to memory
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
    //DMA cache size
    DMA_InitStruct.DMA_BufferSize = cndtr;
    //After receiving the data, the peripheral address is forbidden to move
    //backward
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    //After receiving the data, the memory address is shifted backward
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //Define the peripheral data width to 8 bits
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
    //M2M mode is disabled
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStruct.DMA_Auto_reload = DMA_Auto_Reload_Disable;
    DMA_Init(dam_chx, &DMA_InitStruct);

}
////////////////////////////////////////////////////////////////////////////////
/// @brief  ENABLE CHANNEL.
/// @note   None.
/// @param  DMA_CHx(channel).
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMA_Enable(DMA_Channel_TypeDef* dma_chx)
{
    DMA_Cmd(dma_chx, ENABLE);
}


/// @}


/// @}

/// @}

