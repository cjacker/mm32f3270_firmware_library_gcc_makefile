////////////////////////////////////////////////////////////////////////////////
/// @file    adcx.c
/// @author  AE TEAM
/// @brief   Output received data.
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
#define _ADCX_C_

// Files includes



#include "main.h"
#include "delay.h"
#include "adcx.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ADCX
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ADC_Exported_Functions
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @brief  Setup the ADC port clock
/// @note   This function should affected by chip version.
/// @param  ADCn : Select ADC port.
/// @param  state : Enable or disable the ADC clock.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC_RCC_ClockSet(ADC_TypeDef* ADCn, FunctionalState state)
{

    if(ADCn == ADC1) {
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1, ENABLE);                    //Enable ADC clock
    }
    else if(ADCn == ADC2) {
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC2, ENABLE);                    //Enable ADC clock
    }
    else if(ADCn == ADC3) {
        RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC3, ENABLE);                    //Enable ADC clock
    }
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  ADC Pin Config
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADCxAssignPin(GPIO_TypeDef* GPIOn, u16 pin)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_StructInit(&GPIO_InitStruct);
    RCC_GPIO_ClockCmd(GPIOn, ENABLE);
    GPIO_InitStruct.GPIO_Pin  =  pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;                           //Output speed
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;                               //GPIO mode
    GPIO_Init(GPIOn, &GPIO_InitStruct);
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable the selected ADC channel
/// @param  ADCn: where n can be 1, 2 to select the ADC peripheral.
/// @param  channel: the ADC channel to configure.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADCxChannelEnable(ADC_TypeDef* ADCn, ADCCHANNEL_TypeDef channel)
{
    ADCn->CHSR &= ~(1 << channel);
    ADCn->CHSR |=  (1 << channel);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Disable the selected ADC channel
/// @param  ADCn: where n can be 1, 2 to select the ADC peripheral.
/// @param  channel: the ADC channel to configure.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADCxChannelDisable(ADC_TypeDef* ADCn, ADCCHANNEL_TypeDef channel)
{
    ADCn->CHSR &= ~(1 << channel);
}


////////////////////////////////////////////////////////////////////////////////
/// @brief  ADC1 Pin Config
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC1PinConfigWithParameter(void)
{
    //customer can change below config based Pin assign
    //sample No.1
    ADCxAssignPin(GPIOA, GPIO_Pin_1);
    //ADCxAssignPin(GPIOA, GPIO_Pin_4);
    //ADCxAssignPin(GPIOA, GPIO_Pin_5);
    //sample No.2
    //ADCxAssignPin(GPIOA, GPIO_Pin_4);
    //ADCxAssignPin(GPIOA, GPIO_Pin_5);
    //ADCxAssignPin(GPIOA, GPIO_Pin_6);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  Enable the selected ADC channel
/// @param  ADCn: where n can be 1, 2 to select the ADC peripheral.
/// @param  channel: the ADC channel to configure.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC1ChannelConfigWithParameter(void)
{
    ADC_TypeDef* ADCn;
    ADCn = ADC1;
    ADCxChannelEnable(ADCn, ADC_Channel_1);
//    ADCxChannelEnable(ADCn,ADC_Channel_1);
//    ADCxChannelEnable(ADCn,ADC_Channel_2);
//    ADCxChannelEnable(ADCn,ADC_Channel_3);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Serial GPIOn initialization configuration
/// @note
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC1BasicConfigWithParameter(void)
{
    ADC_InitTypeDef  ADC_InitStruct;
    ADC_TypeDef* ADCn;
    ADCn = ADC1;
    ADC_StructInit(&ADC_InitStruct);

    ADC_RCC_ClockSet(ADCn, ENABLE);                                                //Enable ADC clock

    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;                     //ADC prescale factor
    ADC_InitStruct.ADC_Mode = ADC_Mode_Imm;                             //Set ADC mode to single conversion mode
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                      //AD data right-justified
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;

    ADC_Init(ADCn, &ADC_InitStruct);

    ADC_RegularChannelConfig(ADCn, ADC_Channel_1, 0, ADC_Samctl_240_5);
    ADC_Cmd(ADCn, ENABLE);                                                      //Enable AD conversion
}


//==============================================================================
//ADC interrupt
//==============================================================================
////////////////////////////////////////////////////////////////////////////////
/// @brief  NVIC Configure, Applicable to Cortex M0 or M3 processors.
/// @param  NVIC Channel, Priority or SubPriority.
/// @arg    ch: IRQChannel
/// @arg    pri: Priority, Use only Cortex-M3
/// @arg    sub: SubPriority
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
static void NVIC_Configure(u8 ch, u8 pri, u8 sub)
{
    exNVIC_Init_TypeDef  NVIC_InitStruct;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);


    NVIC_InitStruct.NVIC_IRQChannel = ch;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = pri;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = sub;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

    exNVIC_Init(&NVIC_InitStruct);
}
////////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param
/// @retval UART IRQ index
////////////////////////////////////////////////////////////////////////////////
u8 Get_ADC_IRQ_Flag(ADC_TypeDef* ADCn)
{
    u8 ret = ADC1_IRQn;
    if      (ADCn == ADC1)      ret = ADC1_2_IRQn;

    if      (ADCn == ADC2)      ret = ADC2_IRQn;
    if      (ADCn == ADC3)      ret = ADC3_IRQn;
    return ret;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  ADC Nvic initialization
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADCxNvicInit(ADC_TypeDef* ADCn, u8 pri, u8 sub)
{
    NVIC_Configure(Get_ADC_IRQ_Flag(ADCn), pri, sub);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  ADC1 Nvic initialization
/// @param  None
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC1NvicInitWithParameters(void)
{
    ADCxNvicInit(ADC1, 0, 1);
}


void ADC1_2_IRQHandler(void)
{
    if(RESET != ADC_GetITStatus(ADC1, ADC_IT_EOC)) {
        ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
        ADC_SoftwareStartConvCmd(ADC1, DISABLE);//ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);
        ADC_Result = 0xFFF & ADC_GetConversionValue(ADC1);
        ADC_Flag = 1;
    }
}
u16 ADC1_SingleChannel_Get(void)
{
    u16 uiADData;
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                                     //Software start conversion
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
    ADC_Flag = 0;
    while(1) {
        if(1 == ADC_Flag) {
            uiADData = (u16)ADC_Result;
            ADC_Flag = 0;
            break;
        }
    }
    //ADC_SoftwareStartConvCmd(ADC1, DISABLE);
    return uiADData;
}
////////////////////////////////////////////////////////////////////////////////
/// @brief  This function is getting the average of ADC
/// @note   None.
/// @param  times.
/// @retval average.
////////////////////////////////////////////////////////////////////////////////
u16 Get_Adc_Average(u8 times)
{
    u32 temp_val = 0;
    u8 t;
    u8 delay;
    for(t = 0; t < times; t++) {
        temp_val += ADC1_SingleChannel_Get();
        for(delay = 0; delay < 100; delay++);
    }
    return temp_val / times;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  initialize LED GPIO pin
/// @note   if use jtag/swd interface GPIO PIN as LED, need to be careful,
///         can not debug or program.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADC1SingleChannelInit(void)
{
    printf("ADC1_CH1 test\r\n");
    ADC1BasicConfigWithParameter();
    ADC1ChannelConfigWithParameter();
    ADC1PinConfigWithParameter();
    ADC1NvicInitWithParameters();
}

/// @}


/// @}

/// @}


