////////////////////////////////////////////////////////////////////////////////
/// @file    can.c
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
#define _CAN_C_

// Files includes
#include "stdio.h"
#include "hal_can.h"
#include "can.h"


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Example_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup CAN
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup CAN_Exported_Constants
/// @{

u8 gTimeFlag1s;

////////////////////////////////////////////////////////////////////////////////
/// @brief   CAN initialize
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void CAN_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB1PeriphClockCmd(RCC_APB1ENR_CAN, ENABLE);
    //CAN RX PB8
    RCC_AHBPeriphClockCmd( RCC_AHBENR_GPIOB, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    //CAN TX PB9
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_9);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_9);


}

////////////////////////////////////////////////////////////////////////////////
/// @brief   parameter configuration
/// @note    It must be careful of the Chip Version.
/// @param  CAN_Pre: CAN_250K  CAN_500K ( CAN traffic rate.)
/// @param  CAN_Mode:
///                  StandardFrame_SingleFilter=0
///                  StandardFrame_SingleFilter=1
///                  ExtendedFrame_SingleFilter=2
///                  ExtendedFrame_DoubleFilter=3
/// @param  idCode1:receiving address1
/// @param  idCode2:receiving address2
/// @param  mask1  : Mask frame Settings
/// @param  mask2  : Mask frame Settings
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_Config(u32 CAN_Pre, CAN_Mode ID, u32 idCode1, u32 idCode2, u32 mask1, u32 mask2)
{
    CAN_Peli_InitTypeDef          CAN_Peli_InitStruct;
    RCC_ClocksTypeDef             RCC_Clocks;
    u32 idCodeTemp1, idMaskTemp1;
    u32 idCodeTemp2, idMaskTemp2;
    CAN_Peli_FilterInitTypeDef    CAN_Peli_FilterInitStruct;
    //Enter reset mode
    CAN_ResetMode_Cmd(CAN1, ENABLE);
    //CAN enters Peli mode
    CAN_Mode_Cmd(CAN1, CAN_PELIMode);

    RCC_GetClocksFreq(&RCC_Clocks);

    CAN_Peli_StructInit(&CAN_Peli_InitStruct);
    CAN_Peli_FilterStructInit(&CAN_Peli_FilterInitStruct);
    CAN_AutoCfg_BaudParam( &CAN_Peli_InitStruct, RCC_Clocks.PCLK1_Frequency, CAN_Pre);
    //sampling point
    CAN_Peli_InitStruct.SAM = RESET;
    //Self-test mode
    CAN_Peli_InitStruct.STM = DISABLE;
    //Listen to model
    CAN_Peli_InitStruct.LOM = DISABLE;
    //  CAN_Peli_InitStruct.EWLR = 0x96;
    CAN_Peli_Init(&CAN_Peli_InitStruct);

    switch(ID) {
        case StandardFrame_SingleFilter:
            idCodeTemp1 = idCode1 << (3 + 18);
            idMaskTemp1 = mask1 << (3 + 18);
            CAN_Peli_FilterInitStruct.AFM = CAN_FilterMode_Singal;
            CAN_Peli_FilterInitStruct.CAN_FilterId0 = (idCodeTemp1 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId1 = (idCodeTemp1 >> 16) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId2 = (idCodeTemp1 >> 8) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId3 = (idCodeTemp1 >> 0) & 0xff;

            CAN_Peli_FilterInitStruct.CAN_FilterMaskId0 = (idMaskTemp1 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId1 = ((idMaskTemp1 >> 16) & 0xff) | 0x1f;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId2 = ((idMaskTemp1 >> 8) & 0xff) | 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId3 = ((idMaskTemp1 >> 0) & 0xff) | 0xff;
            break;
        case ExtendedFrame_SingleFilter:
            idCodeTemp1 = idCode1 << 3;
            idMaskTemp1 = mask1 << 3;
            CAN_Peli_FilterInitStruct.AFM = CAN_FilterMode_Singal;
            CAN_Peli_FilterInitStruct.CAN_FilterId0 = (idCodeTemp1 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId1 = (idCodeTemp1 >> 16) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId2 = (idCodeTemp1 >> 8) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId3 = idCodeTemp1 & 0xff;

            CAN_Peli_FilterInitStruct.CAN_FilterMaskId0 = (idMaskTemp1 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId1 = ((idMaskTemp1 >> 16) & 0xff);
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId2 = ((idMaskTemp1 >> 8) & 0xff);
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId3 = ((idMaskTemp1 >> 0) & 0xff);
            break;
        case StandardFrame_DoubleFilter:
            idCodeTemp1 = idCode1 << (3 + 18);
            idMaskTemp1 = mask1 << (3 + 18);
            idCodeTemp2 = idCode2 << (3 + 18);
            idMaskTemp2 = mask2 << (3 + 18);
            CAN_Peli_FilterInitStruct.AFM = CAN_FilterMode_Double;
            CAN_Peli_FilterInitStruct.CAN_FilterId0 = (idCodeTemp1 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId1 = (idCodeTemp1 >> 16) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId2 = (idCodeTemp2 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId3 = (idCodeTemp2 >> 16) & 0xff;

            CAN_Peli_FilterInitStruct.CAN_FilterMaskId0 = (idMaskTemp1 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId1 = ((idMaskTemp1 >> 16) & 0xff) | 0x1f;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId2 = (idMaskTemp2 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId3 = ((idMaskTemp2 >> 16) & 0xff) | 0x1f;
            break;
        case ExtendedFrame_DoubleFilter:
            idCodeTemp1 = idCode1 << (3);
            idMaskTemp1 = mask1 << (3);
            idCodeTemp2 = idCode2 << (3);
            idMaskTemp2 = mask2 << (3);
            CAN_Peli_FilterInitStruct.AFM = CAN_FilterMode_Double;
            CAN_Peli_FilterInitStruct.CAN_FilterId0 = (idCodeTemp1 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId1 = (idCodeTemp1 >> 16) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId2 = (idCodeTemp2 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterId3 = (idCodeTemp2 >> 16) & 0xff;

            CAN_Peli_FilterInitStruct.CAN_FilterMaskId0 = (idMaskTemp1 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId1 = (idMaskTemp1 >> 16) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId2 = (idMaskTemp2 >> 24) & 0xff;
            CAN_Peli_FilterInitStruct.CAN_FilterMaskId3 = (idMaskTemp2 >> 16) & 0xff;
            break;
        default:
            break;
    }
    CAN_Peli_FilterInit(&CAN_Peli_FilterInitStruct);
    //Exit reset mode and enter working mode
    CAN_ResetMode_Cmd(CAN1, DISABLE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Send function
/// @note   the register configuration if there is no return value.
/// @param  TxMessage:Sent message.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void Send_CANFrame(CanTxMsg* TxMessage)
{
    CanPeliTxMsg     CanPeliTxMsgStruct;
    u32 ID = 0;
    u32 i;

    if(TxMessage->CANIDtype) {
        ID = TxMessage->CANID << 3;

        CanPeliTxMsgStruct.FF   = 0x01;
        CanPeliTxMsgStruct.IDLL = (ID >> 0) & 0xff;
        CanPeliTxMsgStruct.IDLH = (ID >> 8) & 0xff;
        CanPeliTxMsgStruct.IDHL = (ID >> 16) & 0xff;
        CanPeliTxMsgStruct.IDHH = (ID >> 24) & 0xff;
    }
    else {
        ID = TxMessage->CANID << 21;

        CanPeliTxMsgStruct.FF   = 0x00;
        CanPeliTxMsgStruct.IDHL = (ID >> 16) & 0xff;
        CanPeliTxMsgStruct.IDHH = (ID >> 24) & 0xff;
    }

    CanPeliTxMsgStruct.DLC  = TxMessage->DLC;
    CanPeliTxMsgStruct.RTR  = TxMessage->RTR;

    for(i = 0; i < 8; i ++ ) {
        CanPeliTxMsgStruct.Data[i] = *(TxMessage->Data + i);
    }

    CAN_Peli_Transmit(&CanPeliTxMsgStruct);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Interrupt service function
/// @note   If error occurs,Simulation to see if you can enter the interrupt
///         function.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void TIM2_IRQHandler(void)
{
    static u32 cnt;
    cnt++;
    if(cnt >= 1000) {
        cnt = 0;
        gTimeFlag1s = 1;
    }
    //Flag bit clearing
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Timer parameters and interrupt priority configuration.
/// @note   Configure parameters according to requirements.
/// @param  Prescaler: Divide the clock frequency.
/// @param  Period: Preload value.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void Tim2_UPCountInit(u16 Prescaler, u16 Period)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    NVIC_InitTypeDef NVIC_StructInit;

    //Enable clock, default clock source is PCLK1,other clock source is optional
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM2, ENABLE);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStruct);
    TIM_TimeBaseStruct.TIM_Period = Period;
    TIM_TimeBaseStruct.TIM_Prescaler = Prescaler;
    //Digital filter sampling frequency, does not affect the timer clock
    TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStruct);

    //Configure timer 2 interrupt channel and priority.
    NVIC_StructInit.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_StructInit.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_StructInit.NVIC_IRQChannelSubPriority = 1;
    NVIC_StructInit.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_StructInit);

    //Update timer will generate update time, clear the flag bit.
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    //Timer 2 update interrupt is allowed.
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM2, ENABLE);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize LED GPIO pin
/// @note   if use jtag/swd interface GPIO PIN as LED, need to be careful,
///         can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void CAN_PollingInit(void)
{
    //Serial port initialization 115200

    CAN_GPIO_Config();
    // Rate ��CAN_250K   Mode��Spread spectrum double filtering  ID��0x172,0x325
    CAN_Config(CAN_250K, ExtendedFrame_DoubleFilter, 0x172, 0x325, 0x00, 0x00);
    //The timer is set to 1s
    Tim2_UPCountInit(47, 1000);

}



/// @}

/// @}

/// @}
