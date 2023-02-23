////////////////////////////////////////////////////////////////////////////////
/// @file    main.c
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
#define _MAIN_C_

// Files includes
#include "led.h"
#include "uart.h"
#include "lcddemo.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Constants
/// @{

u32 sysCnt;
bool ready;

////////////////////////////////////////////////////////////////////////////////
void SysTick_Handler(void)
{
    if(sysCnt++ >= 100) {
        sysCnt = 0;
        if(ready)
            randRefresh();
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is main entrance.
/// @param  None.
/// @retval  0.
////////////////////////////////////////////////////////////////////////////////
s32 main(void)
{
    exRCC_SystickEnable(1000);
    NVIC_SetPriority(SysTick_IRQn, 0x0);
    //in delay.c must set #define USE_SYSTICK_DELAY 0
    //0 = use NOP loop as the delay

    LED_Init();
    BSP_LCD_Configure();

    initLcdDemo();
    ready = true;

    clearLeftScreen();
    clearButtomScreen();
    drawMMSlogan(40, 155, 20);

    while(1) {

    }

}


/// @}

/// @}

/// @}
