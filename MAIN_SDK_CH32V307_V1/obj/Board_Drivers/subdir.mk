################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Drivers/adc.c \
../Board_Drivers/i2c2.c \
../Board_Drivers/spi2.c \
../Board_Drivers/spi3.c \
../Board_Drivers/timer2.c \
../Board_Drivers/timer3.c \
../Board_Drivers/timer4.c \
../Board_Drivers/timer5.c \
../Board_Drivers/timer6.c \
../Board_Drivers/timer7.c \
../Board_Drivers/timer8.c \
../Board_Drivers/timer9.c 

C_DEPS += \
./Board_Drivers/adc.d \
./Board_Drivers/i2c2.d \
./Board_Drivers/spi2.d \
./Board_Drivers/spi3.d \
./Board_Drivers/timer2.d \
./Board_Drivers/timer3.d \
./Board_Drivers/timer4.d \
./Board_Drivers/timer5.d \
./Board_Drivers/timer6.d \
./Board_Drivers/timer7.d \
./Board_Drivers/timer8.d \
./Board_Drivers/timer9.d 

OBJS += \
./Board_Drivers/adc.o \
./Board_Drivers/i2c2.o \
./Board_Drivers/spi2.o \
./Board_Drivers/spi3.o \
./Board_Drivers/timer2.o \
./Board_Drivers/timer3.o \
./Board_Drivers/timer4.o \
./Board_Drivers/timer5.o \
./Board_Drivers/timer6.o \
./Board_Drivers/timer7.o \
./Board_Drivers/timer8.o \
./Board_Drivers/timer9.o 

DIR_OBJS += \
./Board_Drivers/*.o \

DIR_DEPS += \
./Board_Drivers/*.d \

DIR_EXPANDS += \
./Board_Drivers/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Board_Drivers/%.o: ../Board_Drivers/%.c
	@	riscv-wch-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g3 -ggdb -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/User" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Core" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Debug" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Peripheral/inc" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Drivers" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/CherryRB" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Simulation" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/LADRC" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_SOFT" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_DMP/Driver" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MPU6050/MPU6050_DMP/eMPL" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Letter_Shell" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/SFUD/inc" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/OLED_SPI" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/TFT_ST7735S" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/FLASH_W25Q16" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/Encoder_Speed" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/MultiTimer" -I"e:/ladrc_board/MAIN_SDK_CH32V307_V1/Board_Component/LADRC" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

