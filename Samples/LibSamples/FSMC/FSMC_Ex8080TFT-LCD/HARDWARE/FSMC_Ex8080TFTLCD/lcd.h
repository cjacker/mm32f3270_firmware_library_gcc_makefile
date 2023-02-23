////////////////////////////////////////////////////////////////////////////////
/// @file    lcd.h
/// @author  AE TEAM
/// @brief   THIS FILE PROVIDES ALL THE SYSTEM FIRMWARE FUNCTIONS.
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
#ifndef __LCD_H
#define __LCD_H

// Files includes

#include "hal_device.h"
#include "stdlib.h"

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Example_Layer
/// @brief MM32 Example Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_RESOURCE
/// @brief MM32 Examples resource modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Constants
/// @{


/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Enumeration
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief XXXX enumerate definition.
/// @anchor XXXX
////////////////////////////////////////////////////////////////////////////////

#define WIDTH       320                 /* Screen Width (in pixels)           */
#define HEIGHT      240                 /* Screen Hight (in pixels)           */

enum {  SPACE,  FRAME};
enum {  NUL,    FILL};


#define Black        0x0000     /*   0,   0,   0  ???       */
#define Navy         0x000F     /*   0,   0, 128  ?????     */
#define DarkGreen    0x03E0     /*   0, 128,   0  ?????     */
#define DarkCyan     0x03EF     /*   0, 128, 128  ?????     */
#define Maroon       0x7800     /* 128,   0,   0  ????     */
#define Purple       0x780F     /* 128,   0, 128  ???       */
#define Olive        0x7BE0     /* 128, 128,   0  ?????     */
#define LightGrey    0xC618     /* 192, 192, 192  ????     */
#define DarkGrey     0x7BEF     /* 128, 128, 128  ????     */
#define Blue         0x001F     /*   0,   0, 255  ???       */
#define Green        0x07E0     /*   0, 255,   0  ???       */
#define Cyan         0x07FF     /*   0, 255, 255  ???       */
#define Red          0xF800     /* 255,   0,   0  ???       */
#define Magenta      0xF81F     /* 255,   0, 255  ???       */
#define Yellow       0xFFE0     /* 255, 255, 0    ???       */
#define White        0xFFFF     /* 255, 255, 255  ???       */
//chend:RGB565
#define Orange       0xFBE4      /*   0,   0,   0 */
#define SkyBlue      0x749F

////////////////////////////////////////////////////////////////////////////////
#define lcdCsL()    GPIOD->BRR =   GPIO_Pin_7;
#define lcdCsH()    GPIOD->BSRR =  GPIO_Pin_7;

#define lcdBlcL()   GPIOF->BRR =   GPIO_Pin_11;
#define lcdBlcH()   GPIOF->BSRR =  GPIO_Pin_11;

typedef struct {
    u16 c1;     // button  line
    u16 c2;     // button  back
    u16 c3;     // button  shadow   active
    u16 c4;     // button  shadow   not active
} colorDef;

typedef struct {
    u16 fore;
    u16 back;
} Color_Def;

typedef struct {
    u16 width;
    u16 height;
    u16 id;
    u8  dir;
    u16  wramcmd;
    u16  setxcmd;
    u16  setycmd;
} Lcd_Dev_Def;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Variables
/// @{
#ifdef _LCD_C_
#define GLOBAL


#else
#define GLOBAL extern
#endif

GLOBAL colorDef     color;
GLOBAL Color_Def    text;
GLOBAL Lcd_Dev_Def  lcdDev;

#undef GLOBAL

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{
////////////////////////////////////////////////////////////////////////////////
void drawPoint(u16 x, u16 y, u16 c);
void drawLine (s16 x1, s16 y1, s16 x2, s16 y2, u16 c);
void drawSquare(u16 x, u16 y, u16 w, u16 h, u8 frame, u8 fill);
void drawRec (u16 x, u16 y, u16 w, u16 h, u16 c);
void drawCircle(u16 Xpos, u16 Ypos, u16 Radius, u16 c);
void drawTab(u16 x, u16 y, u16 w, u16 h, u8 m, u8 n);

void drawChar_6x8(u16 x, u16 y, u8 bc, u8 chr);
void drawChar_8x16(u16 x, u16 y, u8 bc, u8 chr);

void putChar(u16 x, u16 y, u8 font, u8 bc, char c);
void putStr(u16 x, u16 y, u8 fontsize, u8 backcolor, char* string);
void putBmp(u16 x, u16 y, u16 w, u16 h, u16* ptr);

void drawDialog(u16 w, u16 h, char* str, Color_Def c);
void clearDialog(u16 w, u16 h, Color_Def c);

void drawButton(u16 x, u16 y, u16 w, u16 h, u8 att, u8 sel, char* str);

void lcdSetTextColor (u16 c);
u16 lcdGetTextColor (void);
void lcdSetBackColor (u16 c);
u16 lcdGetBackColor (void);
void LCDC_Init_Reg(void);

void lcdRst(void);
void lcdFillColor(u16 c);

void lcdCmd(u8 cmd);
void lcdData(u8 dat);

static void _delay(u32 n);

void initGPIO_LCD(void);
void initFSMC(void);


/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////





