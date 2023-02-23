# LibSamples_MM32F3270

## Introduction

LibSamples_MM32F3270 is to provide the software package for developing MindMotion MM32F3270 MCU. The software package includes the device's header file, linker file, startup code, peripherals drivers and examples projects.

## User guide

### ToolChains

- Keil MDK for Arm, v5.34.0.0, with MindMotion.MM32F3270_DFP.pack.
- IAR IDE for Arm, v8.30.1, with zip file MM32_IAR_EWARM_pack.zip.

### Hardware board

- Mini-F3270(MM32F3273G6P)

### Source files

| directory                                | description              |
| ---------------------------------------- | ------------------------ |
| `\Device\MM32F3270`                      | NPI enablement files.    |
| `\Device\MM32F3270\HAL_Lib`              | Drivers.                 |
| `\Samples\LibSamples\<MODULE>\<Example>` | Driver example projects. |

### Example projects

 - ADC
     - ADC_Awdg
     - ADC_DMA_polling
     - ADC_Interrupt
     - ADC_Polling
 - BKP
     - BKP_Data
     - BKP_Tamper
 - CAN
     - CAN_Polling
     - CAN_RX_Interrupt
     - CAN_TX
 - COMP
     - COMP_Polling
 - CRC
     - CRC_BasicExample
 - DAC
     - DAC_BasicExample
 - DMA
     - DMA_SRAMtoSRAM
     - DMA_SRAMtoSRAM_Half_Full
 - EXTI
     - EXTI_Key
 - FLASH
     - FLASH_Program
     - FLASH_SIM_EEPROM
 - FSMC
     - FSMC_Ex8080TFT-LCD
 - GPIO
     - GPIO_Key
     - GPIO_Toggle
 - I2C
     - I2C_EEPROM_Polling
 - IWDG
     - IWDG_Reset
 - PWR
     - PWR_PVD_Polling
     - PWR_Sleep_WFI_Wakeup
     - PWR_Standby_IWDG_Wakeup
 - RCC
     - RCC_Bus_ClockDivide
     - RCC_CSR_Reset
     - RCC_MCO
 - RTC
     - RTC_LSE
     - RTC_LSI
 - SPI
     - SPI_FLASH_DMA_Polling
     - SPI_FLASH_Interrupt
     - SPI_FLASH_Polling
     - SPI_FLASH_SoftNSS
 - SYSTICK
     - SYSTICK_System1msDelay
 - TIM
     - TIM1_6Steps
     - TIM1_7PWM_Outputs
     - TIM1_BasicExample
     - TIM1_Interrupt
     - TIM1_Monopulse
     - TIM1_PWM_Shift
     - TIM2_BasicExample
     - TIM3_PWM_Input
     - TIM3_PWM_Output
 - UART
     - UART_DMA_Polling
     - UART_Interrupt
     - UART_Polling
     - UART_Print_DMA
     - UART_Print_Polling
 - WWDG
     - WWDG_Reset

## Known issues

- On-board MM32Link UART  issue
    On-board MM32Link UART output data is with abnormal sequence.

- SDIO module is not enabled in this version of software package.
