# TIM1_Monopulse

## Introduction

This demo shows the TIM1's single pulse output feature. 

 PA9 (TIM1_CH2) captures the rising edge from external signal source. Then TIM1_CH2 triggers TIM1_CH1 internally. PA8 (TIM1_CH1) outputs a pulse with 5ms's length .

## Note

1. Connect the logic analyzer or oscilloscope to monitor the output signal of PA8.

## Run

When TIM1_CH2(PA9) captures the rising edge of signal, TIM1_CH1(PA8) will output a pulse with a length of 5ms.
