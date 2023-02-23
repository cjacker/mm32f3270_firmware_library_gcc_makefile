######################################
# target
######################################
TARGET = mm32f3273g8p

TARGET_DEFS = 

TARGET_LD_SCRIPT = Device/mm32f3273g8p.ld

USER_SOURCES = \
GPIO_Toggle/HARDWARE/LED/led.c \
GPIO_Toggle/SYSTEM/SYS/sys.c \
GPIO_Toggle/SYSTEM/UART/uart.c \
GPIO_Toggle/SYSTEM/DELAY/delay.c \
GPIO_Toggle/USER/main.c \

USER_INCLUDES = \
-IGPIO_Toggle/HARDWARE/LED \
-IGPIO_Toggle/USER \
-IGPIO_Toggle/SYSTEM/SYS \
-IGPIO_Toggle/SYSTEM/UART \
-IGPIO_Toggle/SYSTEM/DELAY


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization for size
OPT = -Os


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES = \
Device/MM32F327x/HAL_Lib/Src/hal_rtc.c \
Device/MM32F327x/HAL_Lib/Src/hal_fsmc.c \
Device/MM32F327x/HAL_Lib/Src/hal_crc.c \
Device/MM32F327x/HAL_Lib/Src/hal_i2c.c \
Device/MM32F327x/HAL_Lib/Src/hal_pwr.c \
Device/MM32F327x/HAL_Lib/Src/hal_flash.c \
Device/MM32F327x/HAL_Lib/Src/hal_uid.c \
Device/MM32F327x/HAL_Lib/Src/hal_dac.c \
Device/MM32F327x/HAL_Lib/Src/hal_dma.c \
Device/MM32F327x/HAL_Lib/Src/hal_sdio.c \
Device/MM32F327x/HAL_Lib/Src/hal_rcc.c \
Device/MM32F327x/HAL_Lib/Src/hal_exti.c \
Device/MM32F327x/HAL_Lib/Src/hal_wwdg.c \
Device/MM32F327x/HAL_Lib/Src/hal_dbg.c \
Device/MM32F327x/HAL_Lib/Src/hal_eth.c \
Device/MM32F327x/HAL_Lib/Src/hal_gpio.c \
Device/MM32F327x/HAL_Lib/Src/hal_misc.c \
Device/MM32F327x/HAL_Lib/Src/hal_ver.c \
Device/MM32F327x/HAL_Lib/Src/hal_crs.c \
Device/MM32F327x/HAL_Lib/Src/hal_uart.c \
Device/MM32F327x/HAL_Lib/Src/hal_spi.c \
Device/MM32F327x/HAL_Lib/Src/hal_adc.c \
Device/MM32F327x/HAL_Lib/Src/hal_tim.c \
Device/MM32F327x/HAL_Lib/Src/hal_can.c \
Device/MM32F327x/HAL_Lib/Src/hal_bkp.c \
Device/MM32F327x/HAL_Lib/Src/hal_comp.c \
Device/MM32F327x/HAL_Lib/Src/hal_iwdg.c \
Device/MM32F327x/Source/system_mm32f327x.c \
$(USER_SOURCES)

# ASM sources
ASM_SOURCES = Device/MM32F327x/Source/GCC/startup_mm32f327x_gcc.S


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# fpu
# NONE for Cortex-M0/M0+/M3

# float-abi

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

AS_DEFS =

# C defines
C_DEFS = $(TARGET_DEFS) 

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-I Device/CMSIS/KEIL_Core \
-I Device/MM32F327x/HAL_Lib/Inc \
-I Device/MM32F327x/Include \
$(USER_INCLUDES) 

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = $(TARGET_LD_SCRIPT)

# libraries
LIBS = -lc -lm -lnosys
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,--no-warn-rwx-segments -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.S=.o)))
vpath %.S $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@
#$(LUAOBJECTS) $(OBJECTS)
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# program
#######################################
program:
	pyocd erase -c -t mm32f3273g8p --config pyocd.yaml
	pyocd load build/$(TARGET).hex -t mm32f3273g8p --config pyocd.yaml

#######################################
# debug
#######################################
debug_pyocd:
	pyocd-gdbserver -t mm32f3273g8p --config pyocd.yaml

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
