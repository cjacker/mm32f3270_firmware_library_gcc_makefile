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
    __IO u32 AHB_HCLK_freq = 0;
    __IO u32 APB1_PCLK1_freq = 0;    
    __IO u32 APB2_PCLK2_freq = 0;    
    RCC_OUT_Init();
    RCC_LSICmd(ENABLE);
    verifyLSI_Cal();

    sysfreq = RCC_GetSysClockFreq();
// RCC_SYSCLK_Div1: AHB clock = SYSCLK
// RCC_SYSCLK_Div2: AHB clock = SYSCLK/2
// RCC_SYSCLK_Div4: AHB clock = SYSCLK/4
// RCC_SYSCLK_Div8: AHB clock = SYSCLK/8
// RCC_SYSCLK_Div16: AHB clock = SYSCLK/16
// RCC_SYSCLK_Div64: AHB clock = SYSCLK/64
// RCC_SYSCLK_Div128: AHB clock = SYSCLK/128
// RCC_SYSCLK_Div256: AHB clock = SYSCLK/256
// RCC_SYSCLK_Div512: AHB clock = SYSCLK/512
    RCC_HCLKConfig(RCC_SYSCLK_Div4);
    
// RCC_HCLK_Div1: APB1 clock = hclk
// RCC_HCLK_Div2: APB1 clock = hclk/2
// RCC_HCLK_Div4: APB1 clock = hclk/4
// RCC_HCLK_Div8: APB1 clock = hclk/8
// RCC_HCLK_Div16: APB1 clock = hclk/16
    RCC_PCLK1Config(RCC_HCLK_Div4);
    
// RCC_HCLK_Div1: APB2 clock = hclk
// RCC_HCLK_Div2: APB2 clock = hclk/2
// RCC_HCLK_Div4: APB2 clock = hclk/4
// RCC_HCLK_Div8: APB2 clock = hclk/8
// RCC_HCLK_Div16: APB2 clock = hclk/16

    RCC_PCLK2Config(RCC_HCLK_Div2);
    
    AHB_HCLK_freq = RCC_GetHCLKFreq();
    APB1_PCLK1_freq = RCC_GetPCLK1Freq();
    APB2_PCLK2_freq = RCC_GetPCLK2Freq();
    while(1) {

    }
}


/// @}

/// @}

/// @}
