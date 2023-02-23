////////////////////////////////////////////////////////////////////////////////
/// @file    lcd.c
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
#define _LCD_C_

// Files includes
#include "stdlib.h"
#include "hal_conf.h"
#include "hal_device.h"
#include "delay.h"
#include "lcd.h"
#include "font.h"
#include "hal_fsmc.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup LCD
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup LCD_Exported_Constants
/// @{

////////////////////////////////////////////////////////////////////////////////
void initGPIO_LCD()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOE, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOF, ENABLE);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource3, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_12);
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_12);

    GPIO_InitStructure.GPIO_Pin     =  GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOF, GPIO_Pin_11);
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    lcdCsL();
}

////////////////////////////////////////////////////////////////////////////////
void initFSMC(void)
{
    FSMC_InitTypeDef                FSMC_InitStructure;
    FSMC_NORSRAM_Bank_InitTypeDef   FSMC_BankInitStructure;

    RCC_AHB3PeriphClockCmd(RCC_AHB3ENR_FSMC, ENABLE);

    FSMC_BankInitStructure.FSMC_SMReadPipe    = 0;
    FSMC_BankInitStructure.FSMC_ReadyMode     = 0;
    FSMC_BankInitStructure.FSMC_WritePeriod   = 0x2;
    FSMC_BankInitStructure.FSMC_WriteHoldTime = 1;
    FSMC_BankInitStructure.FSMC_AddrSetTime   = 3;
    FSMC_BankInitStructure.FSMC_ReadPeriod    = 0x1;
    FSMC_BankInitStructure.FSMC_DataWidth     = FSMC_DataWidth_16bits;
    FSMC_NORSRAM_Bank_Init(&FSMC_BankInitStructure, FSMC_NORSRAM_BANK0);

    FSMC_InitStructure.FSMC_Mode = FSMC_Mode_8080;
    FSMC_InitStructure.FSMC_TimingRegSelect = FSMC_TimingRegSelect_0;
    FSMC_InitStructure.FSMC_MemSize = FSMC_MemSize_64MB;
    FSMC_InitStructure.FSMC_MemType = FSMC_MemType_NorSRAM;
    FSMC_InitStructure.FSMC_AddrDataMode = FSMC_AddrDataMUX;
    FSMC_NORSRAMInit(&FSMC_InitStructure);
}

////////////////////////////////////////////////////////////////////////////////
void lcdCmd(u8 cmd)
{
    *(u16*)(0x60000000) = cmd;
}

////////////////////////////////////////////////////////////////////////////////
void lcdData(u8 dat)
{
    *(u16*)(0x60000000 | (0x01 << 19)) = dat;
}

////////////////////////////////////////////////////////////////////////////////
void lcdData16(u16 dat)
{
    *(u16*)(0x60000000 | (0x01 << 19)) = dat;
}

////////////////////////////////////////////////////////////////////////////////
void lcdSetWindow(u32 x, u32 y, u32 w, u32 h)
{
    lcdCmd(0x2A);
    lcdData(x >> 8);
    lcdData(x & 0xFF);
    lcdData((x + w - 1) >> 8);
    lcdData((x + w - 1) & 0xFF);

    lcdCmd(0x2B);
    lcdData(y >> 8);
    lcdData(y & 0xFF);
    lcdData((y + h - 1) >> 8);
    lcdData((y + h - 1) & 0xFF);
}

////////////////////////////////////////////////////////////////////////////////
void lcdRst()
{

}

////////////////////////////////////////////////////////////////////////////////
void lcdFillColor(u16 c)
{
    u16 i;
    lcdSetWindow(0, 0, WIDTH,  HEIGHT);
    lcdCmd(0x2c);
    lcdData(c);
    for(i = 0; i < (WIDTH * HEIGHT) / 8 ; i++) {
        lcdData(0x0000);
        lcdData(0x0000);
        lcdData(0x0000);
        lcdData(0x0000);
        lcdData(0x0000);
        lcdData(0x0000);
        lcdData(0x0000);
        lcdData(0x0000);
    }
}

////////////////////////////////////////////////////////////////////////////////
void drawSquare(u16 x, u16 y, u16 w, u16 h, u8 frame, u8 fill)
{
    if (!frame) {
        if (fill)
            drawRec (x, y, w, h, color.c2);
        drawRec (x,             y,          w,  1, color.c1);
        drawRec (x,             y + h - 1,  w,  1, color.c1);
        drawRec (x,             y,          1,  h, color.c1);
        drawRec (x + w - 1,     y,          1,  h, color.c1);
    }
    else {
        drawRec (x, y, w, h, color.c1);
    }
}

////////////////////////////////////////////////////////////////////////////////
void drawShadow(u16 x, u16 y, u16 w, u16 h, u8 frame, u16 c)
{
    drawLine (x + 1,    y + h,  x + w, y + h, c);
    drawLine (x + w, y + 1,     x + w, y + h, c);
}

////////////////////////////////////////////////////////////////////////////////
void drawFrame(u16 x, u16 y, u16 w, u16 h, u8 frame, u8 sel)
{
    u16 colour;
    drawSquare(x, y, w, h, frame, FILL);

    colour = (!sel) ?  color.c3 :  color.c4;
    drawShadow(x, y, w, h, frame, colour);
}

////////////////////////////////////////////////////////////////////////////////
void drawSquare_1(u16 x, u16 y, u16 w, u16 h, u16 c)
{
    drawRec (x, y, w, h, c);
}
////////////////////////////////////////////////////////////////////////////////
void drawFrame_1(u16 x, u16 y, u16 w, u16 h, u16 c)
{
    drawRec (x,             y,          w,  1, c);
    drawRec (x,             y + h - 1,  w,  1, c);
    drawRec (x,             y,          1,  h, c);
    drawRec (x + w - 1,     y,          1,  h, c);
}

////////////////////////////////////////////////////////////////////////////////
void drawDialog(u16 w, u16 h, char* str, Color_Def c)
{
    u16 x = (320 - w) / 2;
    u16 y = (240 - h) / 2;

    drawSquare_1(x, y, w, h, c.back);
    drawFrame_1(x + 6,  y + 6,  w - 12,  h - 12,  c.fore);

    text.back = LightGrey;
    putStr(x + 12,  y + 1, 2, 1, str);
}

////////////////////////////////////////////////////////////////////////////////
void clearDialog(u16 w, u16 h, Color_Def c)
{
    u16 x = (320 - w) / 2;
    u16 y = (240 - h) / 2;
    drawSquare_1(x, y, w, h, c.back);
}

////////////////////////////////////////////////////////////////////////////////
void drawButton(u16 x, u16 y, u16 w, u16 h, u8 frame, u8 sel, char* str)
{
    drawFrame(x,  y,  w,  h,  frame,  sel);
    putStr(x + (w -  strlen((char*)str) * 8) / 2,  y + 3, 2, 0, str);
}

////////////////////////////////////////////////////////////////////////////////
static void _delay(u32 n)
{
    u32 i;
    for(i = 0; i < n; i++);
}

////////////////////////////////////////////////////////////////////////////////
void drawChar_6x8(u16 x, u16 y, u8 bc, u8 chr)
{
    u16 i, j;
    if (0x1F < chr && chr < 0x90) {
        u16 k = (chr - 0x20) * 8;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 6; j++) {
                if (Font_6x8_h[k + i] & (0x01 << (7 - j))) {
                    drawPoint(x + j, y + i, text.fore);
                }
                else {
                    if (bc) {
                        drawPoint(x + j, y + i, text.back);
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void drawChar_8x16(u16 x, u16 y, u8 bc, u8 chr)
{
    u16 i, j;
    if (0x1F < chr && chr < 0x90) {
        u16 k = (chr - 0x20) * 16;
        for (i = 0; i < 16; i++) {
            for (j = 0; j < 8; j++) {
                if (Font_8x16_h[k + i] & (0x01 << (7 - j))) {
                    drawPoint(x + j, y + i, text.fore);
                }
                else {
                    if (bc) {
                        drawPoint(x + j, y + i, text.back);
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void drawChar_8x12(u16 x, u16 y,  u8 bc, char c)
{
    u16 i, j;
    if (0x1F < c && c < 0x90) {
        u16 k = (c - 0x20) * 12;
        for (i = 0; i < 12; i++) {
            for (j = 0; j < 8; j++) {
                if (Font_8x12_h[k + i] & 0x01 << (7 - j)) {
                    drawPoint(x + j, y + i, text.fore);
                }
                else {
                    if (bc) {
                        drawPoint(x + j, y + i, text.back);
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void drawChar_16x24(u16 x, u16 y, u8 bc, char c)
{
    u16 i, j;
    if (0x1F < c && c < 0x90) {
        u16 k = (c - 0x20) * 24;
        for (i = 0; i < 24; i++) {
            for (j = 0; j < 16; j++) {
                if (Font_16x24_h[k + i] & (0x01 << j)) {
                    drawPoint(x + j, y + i, text.fore);
                }
                else {
                    if (bc) {
                        drawPoint(x + j, y + i, text.back);
                    }
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void putChar(u16 x, u16 y, u8 font, u8 bc, char c)
{
    if (c & 0x80) return;
    switch (font) {
        case 0:  /* Font 6 x 8 */
            drawChar_6x8(x, y, bc, c);
            break;
        case 1:  /* Font 6 x 8 */
            drawChar_8x12(x, y, bc, c);
            break;
        case 2:  /* Font 8 x 16 */
            drawChar_8x16(x, y, bc, c);
            break;
        default:
            drawChar_16x24(x, y, bc, c);
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
void putStr(u16 x, u16 y, u8 font, u8 bc, char* str)
{
    while (*str) {
        switch(font) {
            case 0:
                putChar(x, y, font, bc, *str++);
                x += 6;
                break;
            case 1:
                putChar(x, y, font, bc, *str++);
                x += 8;
                break;
            case 2:
                putChar(x, y, font, bc, *str++);
                x += 8;
                break;
            default:
                putChar(x, y, font, bc, *str++);
                x += 16;
                break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void putBmp(u16 x, u16 y, u16 w, u16 h, u16* ptr)
{
    u32 i;
    lcdSetWindow(x, y, w, h);
    lcdCmd(0x2c);

    for(i = 0; i < (w * h); i++) {
        lcdData(*ptr++);
    }
}

////////////////////////////////////////////////////////////////////////////////
void drawRec (u16 x, u16 y, u16 w, u16 h, u16 c)
{
    u16 i, cnt, mod;
    lcdSetWindow (x, y, w, h);
    lcdCmd(0x2c);

    cnt = (w * h) / 8;
    mod = (w * h) % 8;

    for (i = 0; i < cnt; i++) {
        lcdData16(c);
        lcdData16(c);
        lcdData16(c);
        lcdData16(c);
        lcdData16(c);
        lcdData16(c);
        lcdData16(c);
        lcdData16(c);
    }

    for (i = 0; i < mod; i++) {
        lcdData16(c);
    }
}

////////////////////////////////////////////////////////////////////////////////
void drawPoint(u16 x, u16 y, u16 c)
{
    drawRec(x, y, 1, 1, c);
}

////////////////////////////////////////////////////////////////////////////////
void drawLine (s16 x1, s16 y1, s16 x2, s16 y2, u16 c)
{
    u16 i;
    u16 w = (x1 > x2) ? (x1 - x2) : (x2 - x1);
    u16 h = (y1 > y2) ? (y1 - y2) : (y2 - y1);

    u16 x = (x1 > x2) ? (x2) : (x1);
    u16 y = (y1 > y2) ? (y2) : (y1);

    if (y1 == y2) {
        drawRec(x, y, w, 1, c);
    }
    else if (x1 == x2) {
        drawRec(x, y, 1, h, c);
    }
    else if (w >= h) {
        for (i = 0; i <= w; i++) {
            drawRec(x + i,
                    i * (y2 - y1) / w + y1,
                    1,
                    1,
                    c);
        }
    }
    else {
        for (i = 0; i < h; i ++) {
            drawRec(
                ((y + i) * w ) / h + x,
                y + i,
                1,
                1,
                c);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void drawTab(u16 x, u16 y, u16 w, u16 h, u8 m, u8 n)
{
    u8 i;
    for (i = 1; i < m; i++) {
        drawLine (x + i * (w / m),   y,  x + i * (w / m),  y + h,  color.c1);
    }
    for (i = 1; i < n; i++) {
        drawLine (x,  y + i * (h / n),  x + w,  y + i * (h / n),  color.c1);
    }
    drawSquare(x, y, w, h, SPACE, NUL);
}

////////////////////////////////////////////////////////////////////////////////
void drawCircle(u16 x, u16 y, u16 r, u16 c)
{
    s32 D = 3 - (r << 1);   /* Decision Variable */
    u32 CurX = 0;           /* Current X Value */
    u32 CurY = r;           /* Current Y Value */

    while (CurX <= CurY) {
        drawRec(x + CurX, y + CurY, 1, 1, c);
        drawRec(x + CurX, y - CurY, 1, 1, c);
        drawRec(x - CurX, y + CurY, 1, 1, c);
        drawRec(x - CurX, y - CurY, 1, 1, c);
        drawRec(x + CurY, y + CurX, 1, 1, c);
        drawRec(x + CurY, y - CurX, 1, 1, c);
        drawRec(x - CurY, y + CurX, 1, 1, c);
        drawRec(x - CurY, y - CurX, 1, 1, c);
        if (D < 0) {
            D += (CurX << 2) + 6;
        }
        else {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }
}

////////////////////////////////////////////////////////////////////////////////
void lcdSetTextColor (u16 _color)
{
    text.fore = _color;
}

////////////////////////////////////////////////////////////////////////////////
u16 lcdGetTextColor (void)
{
    return text.fore;
}

////////////////////////////////////////////////////////////////////////////////
void lcdSetBackColor (u16 _color)
{
    text.back = _color;
}

////////////////////////////////////////////////////////////////////////////////
u16 lcdGetBackColor (void)
{
    return text.back;
}

////////////////////////////////////////////////////////////////////////////////
void LCDC_Init_Reg()
{
    lcdCmd(0x28);   //display off

    lcdCmd(0xCB);   //Power control A
    lcdData(0x39);
    lcdData(0x2C);
    lcdData(0x00);
    lcdData(0x34);
    lcdData(0x02);

    lcdCmd(0xCF);   //Power control B
    lcdData(0x00);
    lcdData(0xC1);  //lcdData(0x81);
    lcdData(0X30);

    lcdCmd(0xED);   //Power on sequence control
    lcdData(0x64);
    lcdData(0x03);
    lcdData(0X12);
    lcdData(0X81);

    lcdCmd(0xE8);   //Driver timing control A
    lcdData(0x85);
    lcdData(0x10);
    lcdData(0x7A);

    lcdCmd(0xF7);   //Pump ratio control
    lcdData(0x20);

    lcdCmd(0xEA);   //Driver timing control B
    lcdData(0x00);
    lcdData(0x00);

    lcdCmd(0xC0);    //Power control
    lcdData(0x1B);   //VRH[5:0]  1B

    lcdCmd(0xC1);    //Power control
    lcdData(0x01);   //SAP[2:0];BT[3:0]

    lcdCmd(0xC5);    //VCM control
    lcdData(0x45);   //3F
    lcdData(0x25);   //3C

    lcdCmd(0xC7);    //VCM control2
    lcdData(0XB7);   //b7

    lcdCmd(0x36);    // Memory Access Control
    lcdData(0xA8);

    lcdCmd(0x3A);    //Pixel Format Set
    lcdData(0x55);

    lcdCmd(0xB1);    //Frame Rate Control
    lcdData(0x00);
    lcdData(0x1A);

    lcdCmd(0xB6);    //Display Function Control
    lcdData(0x0A);
    lcdData(0x82);  //0x02,REV = 0,normally back; 0x82,REV = 1,normally white; 

    lcdCmd(0xF2);    //3Gamma Function Disable
    lcdData(0x00);

    lcdCmd(0x26);    //Gamma curve selected
    lcdData(0x01);

    lcdCmd(0xE0);    //Set Gamma
    lcdData(0x0F);
    lcdData(0x2A);
    lcdData(0x28);
    lcdData(0x08);
    lcdData(0x0E);
    lcdData(0x08);
    lcdData(0x54);
    lcdData(0XA9);
    lcdData(0x43);
    lcdData(0x0A);
    lcdData(0x0F);
    lcdData(0x00);
    lcdData(0x00);
    lcdData(0x00);
    lcdData(0x00);

    lcdCmd(0xE1);    //Set Gamma
    lcdData(0x00);
    lcdData(0x15);
    lcdData(0x17);
    lcdData(0x07);
    lcdData(0x11);
    lcdData(0x06);
    lcdData(0x2B);
    lcdData(0x56);
    lcdData(0x3C);
    lcdData(0x05);
    lcdData(0x10);
    lcdData(0x0F);
    lcdData(0x3F);
    lcdData(0x3F);
    lcdData(0x0F);

    lcdCmd(0x11);   //Exit Sleep
    _delay(200000);
    lcdCmd(0x29);   //display on
}

/// @}

/// @}

/// @}
