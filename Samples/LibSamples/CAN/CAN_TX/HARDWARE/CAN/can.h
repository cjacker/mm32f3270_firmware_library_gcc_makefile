////////////////////////////////////////////////////////////////////////////////
/// @file    can.h
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
#ifndef __CAN_H
#define __CAN_H

// Files includes
#include <string.h>

#include "mm32_device.h"
#include "hal_conf.h"




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


#define CAN_ID_STD                      0
#define CAN_ID_EXT                      1
#define CAN_DATA_FRAME                  0
#define CAN_REMOTE_FRAME                1
#define CAN_500K                        500000
#define CAN_250K                        250000

#define TX_CANID                        0x172

typedef struct {
    u32 CANID;
    u32 CANIDtype;
    u8 RTR;
    u8 DLC;
    u8 Data[8];
} CanTxMsg;
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Enumeration
/// @{
typedef enum {
    StandardFrame_SingleFilter = 0,
    ExtendedFrame_SingleFilter = 1,
    StandardFrame_DoubleFilter = 2,
    ExtendedFrame_DoubleFilter = 3,
} CAN_Mode;




////////////////////////////////////////////////////////////////////////////////
/// @brief XXXX enumerate definition.
/// @anchor XXXX
////////////////////////////////////////////////////////////////////////////////



/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Variables
/// @{
#ifdef _CAN_C_






#define GLOBAL




GLOBAL u8 flag = 0;


#else
#define GLOBAL extern

GLOBAL u8 flag;





#endif

GLOBAL CanPeliRxMsg CanPeliRxMsgStruct;




#undef GLOBAL


/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{


static void CNA_GPIO_Init(void);
void CAN_SendFrame(CanTxMsg* TxMessage);
void CAN_TX_Init(void);


/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
