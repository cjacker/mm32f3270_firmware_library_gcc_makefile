////////////////////////////////////////////////////////////////////////////////
/// @file    adc_dma_polling.h
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
#ifndef __ADC_DMA_polling_H
#define __ADC_DMA_polling_H

// Files includes

#include "hal_device.h"
#include "hal_conf.h"
#include "stdio.h"
#include "string.h"
//#include "drv.h"


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


#define REFVOLATGE              3.3

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Enumeration
/// @{



/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Variables
/// @{
#ifdef _ADC_DMA_polling_C_
#define GLOBAL







#else
#define GLOBAL extern







#endif


GLOBAL vu16 ADCVAL;
GLOBAL vu16 ADC_flag;
GLOBAL float fValue;
GLOBAL vu16 ADCValue[20];
GLOBAL float ADCVolatge;
GLOBAL vu16 ADCFilterValue;
GLOBAL vu8 ADCFilterflag;
#undef GLOBAL

/// @}


////////////////////////////////////////////////////////////////////////////////
/// @defgroup MM32_Exported_Functions
/// @{





void ADCConfig(ADCCHANNEL_TypeDef adc_channel);
void EXTIX_Init(void);
u16 Get_Adc_Average(u8 times);
u16 ADC1_SingleChannel_Get(void);
void GPIO_Clock_Set(GPIO_TypeDef* GPIOn, FunctionalState state);
void GPIO_PinConfigAnalog(GPIO_TypeDef* GPIOn, u16 gpio_pin);
void ADCSingleChannelInit(ADCCHANNEL_TypeDef ADC_Channel_x);
void DMAInit(void);
void ADCFilter(void);
void Get_ADCVolatge(void);


/// @}


/// @}

/// @}


////////////////////////////////////////////////////////////////////////////////
#endif
////////////////////////////////////////////////////////////////////////////////
