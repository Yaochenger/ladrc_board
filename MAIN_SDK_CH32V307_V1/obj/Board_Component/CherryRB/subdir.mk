################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Component/CherryRB/chry_ringbuffer.c 

C_DEPS += \
./Board_Component/CherryRB/chry_ringbuffer.d 

OBJS += \
./Board_Component/CherryRB/chry_ringbuffer.o 

DIR_OBJS += \
./Board_Component/CherryRB/*.o \

DIR_DEPS += \
./Board_Component/CherryRB/*.d \

DIR_EXPANDS += \
./Board_Component/CherryRB/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Board_Component/CherryRB/%.o: ../Board_Component/CherryRB/%.c
	@	riscv-wch-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g3 -ggdb -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/User" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Core" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Debug" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Peripheral/inc" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Drivers" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/CherryRB" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Simulation" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/LADRC" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_SOFT" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_DMP/Driver" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_DMP/eMPL" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Letter_Shell" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/SFUD/inc" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/OLED_SPI" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/TFT_ST7735S" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/FLASH_W25Q16" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Encoder_Speed" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MultiTimer" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/LADRC" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

