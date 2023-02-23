# CAN_Rx_interrupt

## Introduction

This demo shows the  CAN's Rx data feature by interruption method.

## Note

1. Connect the CAN test tool, CAN_L--CAN_L，CAN_H--CAN_H. 

## Run

USB_CAN_DebugTool sends "00 11 22 33 44 55 66 77" to the MCU tby CAN, and the MCU prints out "CANID: 0x172 Data011223344556677" through UART

(CAN:  ID: 0X173 , Baud rate:250K，extended frame)
