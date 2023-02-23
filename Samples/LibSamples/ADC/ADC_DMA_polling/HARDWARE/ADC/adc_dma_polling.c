////////////////////////////////////////////////////////////////////////////////
/// @file     adc_dma_polling.c
/// @author   AE TEAM
/// @brief    In DMA mode, sampling is done by polling.
///
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
#define _ADC_DMA_polling_C_

// Files includes
#include "adc_dma_polling.h"


////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ADC_DMA_POLLING
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup ADC_Exported_Functions
/// @{

u32 adc_value = 0;

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configure sampling GPIO with single conversion mode for ADC1
/// @note    Note the corresponding channel selection.
/// @param  ADC_Channel_x: The sampling channel
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADCConfig(ADCCHANNEL_TypeDef adc_channel)
{
    if( ADC_Channel_0 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOA, GPIO_Pin_0);
        ADCSingleChannelInit(ADC_Channel_0);
    }
    else if( ADC_Channel_1 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOA, GPIO_Pin_1);
    }
    else if( ADC_Channel_2 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOA, GPIO_Pin_2);
    }
    else if( ADC_Channel_3 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOA, GPIO_Pin_3);
    }
    else if( ADC_Channel_4 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOA, GPIO_Pin_4);
    }
    else if( ADC_Channel_5 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOA, GPIO_Pin_5);
    }
    else if( ADC_Channel_6 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOA, GPIO_Pin_6);
    }
    else if( ADC_Channel_7 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOA, GPIO_Pin_7);
    }
    else if( ADC_Channel_8 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOB, GPIO_Pin_0);
    }
    else if( ADC_Channel_9 == adc_channel ) {
        GPIO_PinConfigAnalog(GPIOB, GPIO_Pin_1);
    }
    else {
    }
    ADCSingleChannelInit(adc_channel);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configure the ADC1 single conversion mode to correspond to the PIN
/// @note    It must be careful of the Chip Version.
/// @param  GPIOn: The sampling GPIOn corresponds to the port
/// @param  gpio_pin: The sampling gpio_pin corresponds to the pin.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void GPIO_PinConfigAnalog(GPIO_TypeDef* GPIOn, u16 gpio_pin)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(GPIOn == GPIOA) {
        RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    }
    if(GPIOn == GPIOB) {
        RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
    }
    if(GPIOn == GPIOC) {
        RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOC, ENABLE);
    }
    if(GPIOn == GPIOD) {
        RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOD, ENABLE);
    }
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin  =  gpio_pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOn, &GPIO_InitStruct);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configure ADC1 single conversion mode¡¢external interrupt source
///         interrupt priority
/// @note   Configure parameters according to requirements.
/// @param  ADC_Channel_x: The sampling channel
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADCSingleChannelInit(ADCCHANNEL_TypeDef ADC_Channel_x)
{
    ADC_InitTypeDef  ADC_InitStruct;
    ADC_StructInit(&ADC_InitStruct);

    //Initialize PA1 to analog input mode
    //Enable ADC clock
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_ADC1, ENABLE);

    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    //ADC prescale factor
    ADC_InitStruct.ADC_PRESCARE = ADC_PCLK2_PRESCARE_16;
    //Set ADC mode to continuous conversion mode
    ADC_InitStruct.ADC_Mode = ADC_Mode_Continue;
    //AD data right-justified
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    ADC_Init(ADC1, &ADC_InitStruct);

    //Enable the channel
    ADC_RegularChannelConfig(ADC1, ADC_Channel_x, 0, ADC_Samctl_240_5);
    //Enable ADCDMA
    ADC_DMACmd(ADC1, ENABLE);
    //Enable AD conversion
    ADC_Cmd(ADC1, ENABLE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  DMA and interrupt priority configuration
/// @note   Configure parameters according to requirements.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void DMAInit(void)
{
    DMA_InitTypeDef DMA_InitStruct;


    RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1, ENABLE);
    DMA_DeInit(DMA1_Channel1);
    DMA_StructInit(&DMA_InitStruct);
    //DMA transfer peripheral address
    DMA_InitStruct.DMA_PeripheralBaseAddr = (u32) & (ADC1->DR);
    //DMA transfer memory address
    DMA_InitStruct.DMA_MemoryBaseAddr = (u32)&ADCValue;
    //DMA transfer direction from peripheral to memory
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
    //DMA cache size
    DMA_InitStruct.DMA_BufferSize = 20;
    //After receiving the data, the peripheral address is forbidden to move
    //backward
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    //After receiving the data, the memory address is shifted backward
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //Define the peripheral data width to 16 bits
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    //Define the memory data width to 16 bits
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    //Cycle conversion mode
    DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
    //DMA priority is high
    DMA_InitStruct.DMA_Priority = DMA_Priority_High;
    //M2M mode is disabled
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStruct.DMA_Auto_reload = DMA_Auto_Reload_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStruct);
    DMA_Cmd(DMA1_Channel1, ENABLE);


}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Process values read from DMA,ADC second-order filter,
///         when the filter is completed erection filter end marker.
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void ADCFilter(void)
{
    static u16 cntFilter;
    static u32 lADCFilterValue = 0;
    for(cntFilter = 0; cntFilter < 20; cntFilter++) {
        lADCFilterValue += ADCValue[cntFilter];
    }
    cntFilter = 0;

    ADCFilterflag = 1;
    ADCFilterValue = (lADCFilterValue / 20 * 30 + ADCFilterValue * 70) / 100;
    lADCFilterValue = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Transform the optimized data to get the final result.
/// @note   None.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void Get_ADCVolatge(void)
{
    ADCVolatge = ((float)ADCFilterValue / 4095) * REFVOLATGE;
}



/// @}

/// @}

/// @}


