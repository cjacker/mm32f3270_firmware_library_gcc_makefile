////////////////////////////////////////////////////////////////////////////////
/// @file    main.c
/// @author  AE TEAM
/// @brief   Output system clock(Observing PA9 with an oscilloscope).
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
#include "rcc.h"
#include "hal_rcc.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Constants
/// @{

/// @}

void verifyLSI_Cal(void)
{
    u32 j;
    RCC->APB1ENR |= RCC_APB1ENR_PWR;
    PWR->CFGR &= ~(PWR_CFGR_LSICAL | PWR_CFGR_LSICALSEL);
    PWR->CFGR |= (0x10 << PWR_CFGR_LSICAL_Pos );
    PWR->CFGR |= (0x1F << PWR_CFGR_LSICALSEL_Pos );
    for(j = 0; j < 10000; j++) {
        __NOP();
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is main entrance.
/// @param  None.
/// @retval  0.
////////////////////////////////////////////////////////////////////////////////
s32 main(void)
{
    __IO u32 sysfreq = 0;
    RCC_OUT_Init();
    RCC_LSICmd(ENABLE);
    verifyLSI_Cal();
    sysfreq = RCC_GetSysClockFreq();
    while(1) {

    }
}


/// @}

/// @}

/// @}
