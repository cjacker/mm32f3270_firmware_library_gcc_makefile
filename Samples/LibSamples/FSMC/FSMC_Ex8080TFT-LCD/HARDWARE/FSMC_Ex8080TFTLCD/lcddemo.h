////////////////////////////////////////////////////////////////////////////////
/// @file    lcddemo.h
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

#ifndef _LCDDEMO_H
#define _LCDDEMO_H


#define DMAX        80
#define offsetH     50

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Enumeration
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief XXXX enumerate definition.
/// @anchor XXXX
////////////////////////////////////////////////////////////////////////////////

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Variables
/// @{
#ifdef _LCDDEMO_C_
#define GLOBAL

u16 dx = 5;
u16 dy = 10;
u16 dw = 242;
u16 dh = 135;

#else
#define GLOBAL extern
#endif

GLOBAL u16 dx;
GLOBAL u16 dy;
GLOBAL u16 dw;
GLOBAL u16 dh;
GLOBAL u16 drawBlockCnt;
GLOBAL u16 lcdCnt;

#undef GLOBAL

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{
/// @}

u16 getColor(u8 c);
void randRefresh(void);
void clearLeftScreen(void);
void clearButtomScreen(void);
void drawMMSlogan(u16 x, u16 y, u16 w);
void initLcdDemo(void);
void BSP_LCD_Configure(void);

/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
