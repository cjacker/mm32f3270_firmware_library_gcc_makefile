# mm32f3270_firmware_library_gcc_makefile
This is pre-converted mm32f3270 firmware library with gcc / makefile support.

It is converted from [MM32F3270_Lib_Samples](https://www.mindmotion.com.cn/uploadfiles/2022/07/MM32F3270_Lib_Samples.zip) downloaded from [Shanghai MindMotion official website](https://www.mindmotion.com).

Changes from original "MM32F3270_Lib_Samples" includes:
- convert keil startup asm file to GCC startup asm file.
- add linker script "Device/mm32f3273g8p.ld"
- modify from "GPIO_Toggle" example to match my dev board (LED on PA1)
- add a Makefile, allow it build under linux command line.

Besides above changes, a Keil MDK pack file downloaded from official website and a 'pyocd.yaml' config file 
had been added to support pyOCD.

The default part set to "mm32f3273g8p", if you work with other mm32f3270 part models, you should:
- change the target name in 'Makefile'.
- change the RAM and FLASH SIZE in 'Device/mm32f3273g8p.ld'.

To build it, type 'make'.
