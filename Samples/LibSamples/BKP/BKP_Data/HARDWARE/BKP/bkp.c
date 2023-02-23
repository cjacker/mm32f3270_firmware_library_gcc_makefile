////////////////////////////////////////////////////////////////////////////////
/// @file    bkp.c
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
#define _BKP_C_

// Files includes

#include "bkp.h"
#include "led.h"
#include "delay.h"



////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MAIN_Exported_Constants
/// @{



////////////////////////////////////////////////////////////////////////////////
/// @brief  : Write data to register library
/// @param  : FirstBackupData
/// @retval : None
////////////////////////////////////////////////////////////////////////////////
void WriteToBackupReg(u16 FirstBackupData)
{
    u32 index = 0;

    for (index = 0; index < 10; index++) {
        // Write data into the corresponding register
        BKP_WriteBackupRegister(BKPDataReg[index], FirstBackupData);
    }
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  : Determine if the write data is correct
/// @param  : FirstBackupData
/// @retval : index + 1,error
///           0,success
////////////////////////////////////////////////////////////////////////////////
u8 CheckBackupReg(u16 FirstBackupData)
{
    u32 index = 0;

    for (index = 0; index < 10; index++) {
        if (BKP_ReadBackupRegister(BKPDataReg[index]) != FirstBackupData) {
            return (index + 1);
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  : Start intrusion detection
/// @param  : Portx , State
/// @retval : None
////////////////////////////////////////////////////////////////////////////////
void BKP_Test(void)
{

    // Enable PWR and BKP clock

    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWR, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1ENR_BKP, ENABLE);
    // Enable write access to Backup domain
    PWR_BackupAccessCmd(ENABLE);

    // Write data to register library
    WriteToBackupReg(0xabcd);
    // Check if the written data are correct
    if(CheckBackupReg(0xabcd) == 0x00) {
        // Turn off LED1
        LED1_OFF();//Correct data reading and writing
    }
    else {
        // Turn on LED1
        LED1_ON();//Data read-write error
    }
    while(1) {

    }
}




/// @}

/// @}

/// @}
