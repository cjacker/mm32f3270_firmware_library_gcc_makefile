////////////////////////////////////////////////////////////////////////////////
/// @file    main.c
/// @author  AE TEAM
/// @brief   None.
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
#include "comp.h"
#include "uart.h"



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
/// @brief  This function is main entrance.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
__IO u8 ucA;
s32 main(void)
{   
    CONSOLE_Init(115200);
    COMP_Test();
    while(1) {
        ucA = Comp_StatusCheck(COMP1);
        if(ucA == 1)
        {
            printf("the comparator result is: %d\r\n",ucA); //The non-inverting input is greater than the inverting input
        }
        else
        {
            printf("the comparator result is: %d\r\n",ucA); //The non-inverting input is smaller than the inverting input
        }
    }
}
/// @}


/// @}

/// @}

