################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Component/Letter_Shell/log.c \
../Board_Component/Letter_Shell/lshell_port.c \
../Board_Component/Letter_Shell/shell.c \
../Board_Component/Letter_Shell/shell_cmd_list.c \
../Board_Component/Letter_Shell/shell_companion.c \
../Board_Component/Letter_Shell/shell_ext.c 

C_DEPS += \
./Board_Component/Letter_Shell/log.d \
./Board_Component/Letter_Shell/lshell_port.d \
./Board_Component/Letter_Shell/shell.d \
./Board_Component/Letter_Shell/shell_cmd_list.d \
./Board_Component/Letter_Shell/shell_companion.d \
./Board_Component/Letter_Shell/shell_ext.d 

OBJS += \
./Board_Component/Letter_Shell/log.o \
./Board_Component/Letter_Shell/lshell_port.o \
./Board_Component/Letter_Shell/shell.o \
./Board_Component/Letter_Shell/shell_cmd_list.o \
./Board_Component/Letter_Shell/shell_companion.o \
./Board_Component/Letter_Shell/shell_ext.o 

DIR_OBJS += \
./Board_Component/Letter_Shell/*.o \

DIR_DEPS += \
./Board_Component/Letter_Shell/*.d \

DIR_EXPANDS += \
./Board_Component/Letter_Shell/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Board_Component/Letter_Shell/%.o: ../Board_Component/Letter_Shell/%.c
	@	riscv-wch-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g3 -ggdb -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/User" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Core" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Debug" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Peripheral/inc" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Drivers" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/CherryRB" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Simulation" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/LADRC" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_SOFT" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_DMP/Driver" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_DMP/eMPL" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Letter_Shell" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/SFUD/inc" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/OLED_SPI" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/TFT_ST7735S" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/FLASH_W25Q16" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Encoder_Speed" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MultiTimer" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/LADRC" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

