# RCC_CSR_Reset

## Introduction

This demo shows the  RCC's reset feature, which including reset caused by WWDG, IWDG, SOFT.

## Run

1. The WWDG reset function is executed by default. 
    The serial debugging assistant shows as follows: 
    RCC_CSR TEST! 
    WWDG Reset Test! 
    1.RCC->CSR =0x44000023 
    2.RCC->CSR =0x23 
    Bit [30] of the RCC_CSR register, WWDGRSTF is set, that is, a WWDG reset has occurred.  
2. Set i = 2, then run the WWDG   reset function. 
    The serial port debugging assistant displays as follows: 
    RCC_CSR TEST! 
    IWDG Reset Test! 
    1.RCC->CSR =0x24000023 
    2.RCC->CSR =0x23 
    Bit [29] IWDGRSTF of the RCC_CSR register is set, that is, an IWDG reset has occurred.  


3. Set i = 3, then run the software reset function. 
    The serial debugging assistant shows as follows: 
    RCC_CSR TEST!
    SOFT Reset Test!
    1.RCC->CSR =0x14000023
    2.RCC->CSR =0x23
    The bit [28] SFTRSTF of the RCC_CSR register is set, that is, a software reset has occurred.  
