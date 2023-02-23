# I2C_EEPROM_Polling

## Introduction

This demo shows the  I2C's polling feature.

Configure I2C polling mode to write and read data.

The program is initialized t standard speed mode; In the fast mode, data can be read and written, but the waveform can be viewed by the logic analyzer, which has the problem that the frequency is not 400K.

## Run

Run the program and print 16 sent data through the serial port with baud rate of 115200，which is：

TX data 0 is: aa 
TX data 1 is: bb 
TX data 2 is: cc 
TX data 3 is: dd 
TX data 4 is: ee 
TX data 5 is: ff 
TX data 6 is: 11 
TX data 7 is: 22 
TX data 8 is: 33 
TX data 9 is: 44 
TX data10 is: 55 
TX data11 is: 66 
TX data12 is: 77 
TX data13 is: 88 
TX data14 is: 99 
TX data15 is: 99 

 Start receive data...
RX data 0 is: aa 
RX data 1 is: bb 
RX data 2 is: cc 
RX data 3 is: dd 
RX data 4 is: ee 
RX data 5 is: ff 
RX data 6 is: 11 
RX data 7 is: 22 
RX data 8 is: 33 
RX data 9 is: 44 
RX data10 is: 55 
RX data11 is: 66 
RX data12 is: 77 
RX data13 is: 88 
RX data14 is: 99 
RX data15 is: 99 
I2C1 polling test successfully
