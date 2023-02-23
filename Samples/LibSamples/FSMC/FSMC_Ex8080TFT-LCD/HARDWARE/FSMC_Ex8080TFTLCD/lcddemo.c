////////////////////////////////////////////////////////////////////////////////
/// @file    lcddemo.c
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
#define _LCDDEMO_C_

// Files includes
#include "hal_conf.h"
#include "stdio.h"
#include "delay.h"
#include "lcd.h"
#include "lcddemo.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup LCDDEMO
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup LCDDEMO_Exported_Constants
/// @{

////////////////////////////////////////////////////////////////////////////////
u16 getColor(u8 c)
{
    u16 colorTab[] = { 0x0000, 0x000F, 0x03E0, 0x03EF, 0x7800, 0x780F, 0x7BE0, 0xC618,
                       0x7BEF, 0x001F, 0x07E0, 0x07FF, 0xF800, 0xF81F, 0xFFE0, 0xFFFF
                     };
    return colorTab[c];
}

////////////////////////////////////////////////////////////////////////////////
void randRefresh()
{
    u16 x, y, w, h, c;
    drawSquare(dx,  dy,  dw, dh, SPACE, NUL);
    if (drawBlockCnt++ % 2) {
        x = rand();
        x %= (dw - 2);
        y = rand();
        y %= (dh - 2);
        w = rand();
        w %= DMAX;
        h = rand();
        h %= DMAX;
        c = rand();
        c &= 0x0f;
        if ((x + w) > (dw - 2)) x = dw - w - 2;
        if ((y + h) > (dh - 2)) y = dh - h - 2;
        drawRec (x + dx + 1, y + dy + 1, w, h, getColor(c));
    }
    else {
        c = rand();
        c &= 0x0f;
        drawRec (dx + 1, dy + 1, dw - 2, dh - 2, getColor(c));
    }

}

////////////////////////////////////////////////////////////////////////////////
void clearLeftScreen()
{
    drawRec (dx, dy, dw, dh + 95, Black);
}

////////////////////////////////////////////////////////////////////////////////
void clearButtomScreen()
{
    drawRec (dx, dy + dh + 95, dw, 240, Black);
}

void drawMMSlogan(u16 x, u16 y, u16 w)
{
    u16 color = SkyBlue;
    u8 xsub = 1, ysub = 1;

    drawLine(x + 0 * w, y + 1 * w, x + 1 * w, y + 0 * w, color); //M0 - M1
    drawLine(x + 1 * w, y + 0 * w, x + 2 * w - xsub, y + 0 * w, color); //M1 - M2
    drawLine(x + 2 * w - xsub, y + 0 * w, x + 2 * w - xsub, y + 1 * w + ysub, color); //M2 - M3
    drawLine(x + 1 * w, y + 2 * w, x + 2 * w, y + 1 * w, color); //M3 - M4
    drawLine(x + 1 * w, y + 2 * w, x + 2 * w, y + 3 * w, color); //M4 - M5
    drawLine(x + 2 * w, y + 3 * w, x + 3 * w - xsub, y + 2 * w + ysub, color); //M5 - M6
    drawLine(x + 3 * w - xsub, y + 2 * w + ysub, x + 4 * w - xsub, y + 2 * w + ysub, color); //M6 - M7
    drawLine(x + 4 * w - xsub, y + 2 * w + ysub, x + 4 * w - xsub, y + 3 * w + ysub, color); //M7 - M8
    drawLine(x + 3 * w, y + 4 * w, x + 4 * w - xsub, y + 3 * w + ysub, color); //M8 - M9
    drawLine(x + 3 * w, y + 4 * w, x + 1 * w, y + 4 * w, color); //M9 - M10
    drawLine(x + 1 * w, y + 4 * w, x + 1 * w, y + 3 * w, color); //M10 - M11
    drawLine(x + 1 * w, y + 3 * w, x + 0 * w, y + 3 * w, color); //M11 - M12
    drawLine(x + 0 * w, y + 3 * w, x + 0 * w, y + 1 * w, color); //M12 - M0

    color = Yellow;
    drawLine(x + 2 * w + xsub, y + 1 * w - ysub, x + 3 * w, y + 0 * w, color); //M0 - M1
    drawLine(x + 3 * w, y + 0 * w, x + 5 * w, y + 0 * w, color); //M1 - M2
    drawLine(x + 5 * w, y + 0 * w, x + 5 * w, y + 1 * w, color); //M2 - M3
    drawLine(x + 5 * w, y + 1 * w, x + 6 * w, y + 1 * w, color); //M3 - M4
    drawLine(x + 6 * w, y + 1 * w, x + 6 * w, y + 3 * w, color); //M4 - M5
    drawLine(x + 5 * w, y + 4 * w, x + 6 * w, y + 3 * w, color); //M5 - M6
    drawLine(x + 4 * w + xsub, y + 4 * w, x + 5 * w, y + 4 * w, color); //M6 - M7
    drawLine(x + 4 * w + xsub, y + 4 * w, x + 4 * w + xsub, y + 3 * w - ysub, color); //M7 - M8
    drawLine(x + 4 * w + xsub, y + 3 * w - ysub, x + 5 * w, y + 2 * w, color); //M8 - M9
    drawLine(x + 4 * w, y + 1 * w, x + 5 * w, y + 2 * w, color); //M9 - M10
    drawLine(x + 3 * w + xsub, y + 2 * w - ysub, x + 4 * w, y + 1 * w, color); //M10 - M11
    drawLine(x + 2 * w + xsub, y + 2 * w - ysub, x + 3 * w + xsub, y + 2 * w - ysub, color); //M11 - M12
    drawLine(x + 2 * w + xsub, y + 2 * w - ysub, x + 2 * w + xsub, y + 1 * w - ysub, color); //M12 - M0

    putStr(x + 6 * w, y + 0 * w + 2, 2, 1, "MindMotion");
    putStr(x + 6 * w + 3, y + 1 * w, 0, 1, "Soc Solutions");
}

////////////////////////////////////////////////////////////////////////////////
void initLcdDemo()
{
    text.fore = SkyBlue;
    text.back = Black;
    color.c1 = Blue;

    drawSquare(dx,  dy,  dw, dh, SPACE, NUL);
    color.c1 = LightGrey;
    color.c2 = DarkCyan;
    color.c3 = White;
    color.c4 = Yellow;

    drawCircle(60,  195, 30, Yellow);
    drawCircle(190, 195, 30, Yellow);

    drawSquare(10,  160, 40, 25, SPACE, NUL);
    drawSquare(10,  210, 40, 25, FRAME, NUL);

    drawSquare(105, 160, 40, 25, FRAME, NUL);
    drawSquare(105, 210, 40, 25, SPACE, NUL);

    drawSquare(205,  160, 40, 25, SPACE, NUL);
    drawSquare(205,  210, 40, 25, FRAME, NUL);

    drawLine (10, 160, 50, 185, Red);
    drawLine (205, 185, 245, 160, Red);
}

////////////////////////////////////////////////////////////////////////////////
void BSP_LCD_Configure()
{
    initGPIO_LCD();
    initFSMC();

    LCDC_Init_Reg();
    lcdFillColor(Black);
    lcdBlcH();
}

/// @}

/// @}

/// @}
