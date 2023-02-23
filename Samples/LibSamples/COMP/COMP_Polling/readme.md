# COMP_Polling

## Introduction

This demo shows the  COMP's Polling featue.

The PA5 pin is used as an inverting input.  
The PA1 pin is used as a positive phase input.  

Compare the positive input with the negative input. If the positive input is greater than the negative input, the ucA value is 1. If the positive input is smaller than the negative input, the ucA value is 0.

## Run

1. Connect PA1 to GND and connect PA5 to VCC, the non-inverting input is smaller than the inverting input. The serial port with baud rate of 115200 prints out 'the comparator result is: 0'.
2. Connect PA1 to VCC and connect PA5 to GND, the non-inverting input is greater than the inverting input. The serial port with baud rate of 115200 prints out 'the comparator result is: 1'.
