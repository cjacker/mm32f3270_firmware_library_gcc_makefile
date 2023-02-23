# CAN_Polling

## Introduction

This demo shows the  MCU's CAN feature.
The CAN receives the loopback data and sends it to the host computer by UART.

## Note

1. Connect the CAN test tool, CAN_L--CAN_L，CAN_H--CAN_H. 

## Run

USB_CAN_DebugTool sends "00 11 22 33 44 55 66 77" to the MCU tby CAN, and the MCU prints out "CANID: 0x172 Data: 011223344556677" through UART, otherwise  the MCU prints out "CCANID:0x13dd8fff  Data: 3ffdcba9fe94fe22"

(CAN:  ID: 0X173 , Baud rate:250K，extended frame)
