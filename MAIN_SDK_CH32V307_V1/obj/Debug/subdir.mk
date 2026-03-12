################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

C_DEPS += \
./Debug/debug.d 

OBJS += \
./Debug/debug.o 

DIR_OBJS += \
./Debug/*.o \

DIR_DEPS += \
./Debug/*.d \

DIR_EXPANDS += \
./Debug/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	riscv-wch-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g3 -ggdb -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/User" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Core" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Debug" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Peripheral/inc" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Drivers" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/CherryRB" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Simulation" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/LADRC" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_SOFT" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_DMP/Driver" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_DMP/eMPL" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Letter_Shell" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/SFUD/inc" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/OLED_SPI" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/TFT_ST7735S" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/FLASH_W25Q16" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Encoder_Speed" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MultiTimer" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/LADRC" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

