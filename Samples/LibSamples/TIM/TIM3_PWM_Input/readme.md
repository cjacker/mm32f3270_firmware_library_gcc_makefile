# TIM3_PWM_Input 

## Introduction

This demo shows the  TIM3's PWM input capture feature. 
Configure TIM2_CH3(PB10)  to output PWM as the TIM3_CH1's PWM input source. 
In the program, through the two capture registers of TIM3, one is used to capture the period and the other is used to capture the duty cycle. 

## Note

1. Connect PA6 to PB10, and connect the logic analyzer to detect the output of PA6.

## Run

Observe two variables in the Watch window: "period" and "duty"
The value of period is 0x03E7.
The value of duty is 0x018F.
The logic analyzer observes that the TIM2_CH3(PB10) output PWM period is 2ms, and the duty cycle is 40%.
The calculated data is consistent with the waveform data.  