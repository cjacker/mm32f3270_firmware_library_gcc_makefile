////////////////////////////////////////////////////////////////////////////////
/// @file    spi.c
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
#define _SPI_C_

// Files includes
#include "delay.h"
#include "uart.h"
#include "spi.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup SPI
/// @{


u8 gTxData[256];
u8 gRxData[256];
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup SPI_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  SPI FLASH Read
/// @note   page = 256 bytes.
/// @param  Address:address.
/// @param  number:length.
/// @param  p:data buff.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void W25xx_PageRead(u32 address, u8* p, u32 number)
{
    u8 addr0, addr1, addr2;
    u32 i;
    address = address & 0xffffff00;
    addr0 = (u8)(address >> 16);
    addr1 = (u8)(address >> 8);
    addr2 = (u8)address;
    W25xx_CS_Low();
    W25xx_ReadWriteByte(READ);
    W25xx_ReadWriteByte(addr0);
    W25xx_ReadWriteByte(addr1);
    W25xx_ReadWriteByte(addr2);
    for(i = 0; i < 256; i++) {
        gRxData[i] = W25xx_ReadWriteByte(0x00);
    }
    W25xx_CS_High();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  SPI FLASH Write
/// @note   page = 256 bytes.
/// @param  Address:address.
/// @param  number:length.
/// @param  p:data buff.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void W25xx_PageProgram(u32 address, u8* p, u32 number)
{
    u32 j;
    u8 addr0, addr1, addr2;
    address = address & 0xffffff00;
    addr0 = (u8)(address >> 16);
    addr1 = (u8)(address >> 8);
    addr2 = (u8)address;
    W25xx_WriteEnable();
    W25xx_CS_Low();
    W25xx_ReadWriteByte(PP);
    W25xx_ReadWriteByte(addr0);
    W25xx_ReadWriteByte(addr1);
    W25xx_ReadWriteByte(addr2);
    for(j = 0; j < number; j++) {
        W25xx_ReadWriteByte(*(p++));
    }
    W25xx_CS_High();
    W25xx_CheckStatus();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  SPI Sector Erase
/// @note   None.
/// @param  Addr:address.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void W25xx_SectorErase(u32 address)
{
    u8 addr0, addr1, addr2;
    address = address & 0xffff0000;
    addr0 = ((u8)(address >> 16)) & 0xff;
    addr1 = ((u8)(address >> 8)) & 0xff;
    addr2 = ((u8)address) & 0xff;

    W25xx_WriteEnable();
    W25xx_CS_Low();
    W25xx_ReadWriteByte(SE);
    W25xx_ReadWriteByte(addr0);
    W25xx_ReadWriteByte(addr1);
    W25xx_ReadWriteByte(addr2);
    W25xx_CS_High();

    W25xx_CheckStatus();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  SPI send a byte data
/// @note   None.
/// @param  tx_data:send data.
/// @retval RX data.
////////////////////////////////////////////////////////////////////////////////
u32 W25xx_ReadWriteByte(u8 tx_data)
{
    SPI_SendData(SPI2, tx_data);
    while (1) {
        if(SPI_GetFlagStatus(SPI2, SPI_FLAG_TXEPT)) {
            break;
        }
    }
    while (1) {
        if(SPI_GetFlagStatus(SPI2, SPI_FLAG_RXAVL)) {
            return SPI_ReceiveData(SPI2);
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize SPI2 MODE1(master)
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void SPI2_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_5);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_5);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_5);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_5);
    //spi2_cs    pb12
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    //spi2_sck   pb13
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    //spi2_mosi  pb15
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    //spi2_miso  pb14
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

}
////////////////////////////////////////////////////////////////////////////////
/// @brief  SPI Config
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void SPI2_Config(u16 spi_baud_div)
{
    SPI_InitTypeDef SPI_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1ENR_SPI2, ENABLE);
    SPI_StructInit(&SPI_InitStruct);
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_DataWidth = 8;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = (SPI_BaudRatePrescaler_TypeDef)spi_baud_div;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI2, &SPI_InitStruct);
    if(SPI_InitStruct.SPI_BaudRatePrescaler <= 8) {
        exSPI_DataEdgeAdjust(SPI2, SPI_DataEdgeAdjust_FAST);
    }
    SPI_BiDirectionalLineConfig(SPI2, SPI_Direction_Rx);
    SPI_BiDirectionalLineConfig(SPI2, SPI_Direction_Tx);
    SPI_Cmd(SPI2, ENABLE);

}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Modifiable parameter initialization SPI.
/// @note   None.
/// @param  datawidth:data byte length.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SPI_FlashInit(u16 spi_baud_div)
{
    SPI2_GPIO_Config();
    SPI2_Config(spi_baud_div);
    W25xx_CS_High();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Read ID
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void W25xx_ReadID()
{
    u8 temp[5];
    u32 i;
    W25xx_CS_Low();
    W25xx_ReadWriteByte(RDID);
    for(i = 0; i < 3; i++) {
        temp[i] = W25xx_ReadWriteByte(0x01);
    }
    W25xx_CS_High();
    for(i = 0; i < 3; i++) {
        printf("temp=0x%x\r\n", temp[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable Read
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void W25xx_WriteEnable()
{
    W25xx_CS_Low();
    W25xx_ReadWriteByte(WREN);
    W25xx_CS_High();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  check Status
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void W25xx_CheckStatus()
{
    u8 temp;
    W25xx_CS_Low();
    W25xx_ReadWriteByte(RDSR);
    while(1) {
        temp = W25xx_ReadWriteByte(0x00);
        if((temp & 0x01) == 0x0)
            break;
    }
    W25xx_CS_High();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reset internal NSS pins for selected SPI software
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void W25xx_CS_Low()
{
    //Spi cs assign to this pin,select
    SPI_CSInternalSelected(SPI2, ENABLE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reset internal NSS pins for selected SPI software
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void W25xx_CS_High()
{
    //Spi cs release
    SPI_CSInternalSelected(SPI2, DISABLE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize LED GPIO pin
/// @note   if use jtag/swd interface GPIO PIN as LED, need to be careful,
///         can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void SPI_FlashTest(void)
{
    u32 i;
    for(i = 0; i < 256; i++) {
        gTxData[i] = i;
    }
    printf("SPI2 test\r\n");
    W25xx_ReadID();
    W25xx_SectorErase(0);
    W25xx_PageProgram(0, gTxData, 256);
    for(i = 0; i < 256; i++) {
        gRxData[i] = 0x0;
    }
    W25xx_PageRead(0, gRxData, 256);
    for(i = 0; i < 10; i++) {
        printf("rx[%d]=0x%x\r\n", i, gRxData[i]);
    }
    printf("SPI2 test over\r\n");
}

/// @}

/// @}

/// @}
