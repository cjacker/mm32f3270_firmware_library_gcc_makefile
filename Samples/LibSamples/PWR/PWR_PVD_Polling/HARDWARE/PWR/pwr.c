////////////////////////////////////////////////////////////////////////////////
/// @file    pwr.c
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
#define _PWR_C_

// Files includes
#include "delay.h"
#include "led.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup PWR
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup PWR_Exported_Functions
/// @{
////////////////////////////////////////////////////////////////////////////////
/// @brief  delay config.
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void deleyNop(u32 DlyTime)
{
    u32 i, j;
    for(i = 0; i < DlyTime; i++) {
        for(j = 0; j < 100; j++) {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize PWR_PVD_Polling
/// @note  
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void PWR_PVD_PollInit(void)
{
    u16 i;
    deleyNop(10000);

    LED_Init();

    for(i = 0; i < 10; i++) {
        LED2_TOGGLE();
        deleyNop(3000);
    } 
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWR, ENABLE);
    // Configure EXTI Line to generate an interrupt on falling edge
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFG, ENABLE);
    //Configure the PVD Level to 1.7 ~ 4.7V
//    PWR_PVDLevelConfig(emPVD_LEVEL0 );
//    PWR_PVDLevelConfig(emPVD_LEVEL1 );
//    PWR_PVDLevelConfig(emPVD_LEVEL2 );
//    PWR_PVDLevelConfig(emPVD_LEVEL3 );
    PWR_PVDLevelConfig(emPVD_LEVEL4 );
//    PWR_PVDLevelConfig(emPVD_LEVEL5 );
//    PWR_PVDLevelConfig(emPVD_LEVEL6 );
//    PWR_PVDLevelConfig(emPVD_LEVEL7 );
//    PWR_PVDLevelConfig(emPVD_LEVEL8 );
//    PWR_PVDLevelConfig(emPVD_LEVEL9 );
//    PWR_PVDLevelConfig(emPVD_LEVEL10);


    // Enable the PVD Output
    PWR_PVDCmd(ENABLE);


}
/// @}

/// @}

/// @}
