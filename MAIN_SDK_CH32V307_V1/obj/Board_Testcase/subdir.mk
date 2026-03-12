################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Testcase/adc_case.c \
../Board_Testcase/flash_case.c \
../Board_Testcase/gpio_case.c \
../Board_Testcase/i2c2_mpu6050_case.c \
../Board_Testcase/motor_encoder_case.c \
../Board_Testcase/spi3_lcd_st7735s_case.c \
../Board_Testcase/uart2_ble_case.c \
../Board_Testcase/uart6_rs485_case.c 

C_DEPS += \
./Board_Testcase/adc_case.d \
./Board_Testcase/flash_case.d \
./Board_Testcase/gpio_case.d \
./Board_Testcase/i2c2_mpu6050_case.d \
./Board_Testcase/motor_encoder_case.d \
./Board_Testcase/spi3_lcd_st7735s_case.d \
./Board_Testcase/uart2_ble_case.d \
./Board_Testcase/uart6_rs485_case.d 

OBJS += \
./Board_Testcase/adc_case.o \
./Board_Testcase/flash_case.o \
./Board_Testcase/gpio_case.o \
./Board_Testcase/i2c2_mpu6050_case.o \
./Board_Testcase/motor_encoder_case.o \
./Board_Testcase/spi3_lcd_st7735s_case.o \
./Board_Testcase/uart2_ble_case.o \
./Board_Testcase/uart6_rs485_case.o 

DIR_OBJS += \
./Board_Testcase/*.o \

DIR_DEPS += \
./Board_Testcase/*.d \

DIR_EXPANDS += \
./Board_Testcase/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Board_Testcase/%.o: ../Board_Testcase/%.c
	@	riscv-wch-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -fdump-rtl-expand -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g3 -ggdb -I"e:/ladrc_board/LADRC_BOARD_RISCV" -I"e:/ladrc_board/LADRC_BOARD_RISCV/User" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Core" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Debug" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Peripheral/inc" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Drivers" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/CherryRB" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/Simulation" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/LADRC" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/MPU6050/MPU6050_SOFT" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/MPU6050/MPU6050_DMP/Driver" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/MPU6050/MPU6050_DMP/eMPL" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/Letter_Shell" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/SFUD/inc" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/OLED_SPI" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/TFT_ST7735S" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/FLASH_W25Q16" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/Encoder_Speed" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/MultiTimer" -I"e:/ladrc_board/LADRC_BOARD_RISCV/Board_Component/LADRC" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

