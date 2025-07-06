################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Drivers/adc.c \
../Board_Drivers/drv_def.c \
../Board_Drivers/i2c2.c \
../Board_Drivers/key.c \
../Board_Drivers/led.c \
../Board_Drivers/spi2.c \
../Board_Drivers/spi3.c \
../Board_Drivers/timer2.c \
../Board_Drivers/timer3.c \
../Board_Drivers/timer4.c \
../Board_Drivers/timer5.c \
../Board_Drivers/timer6.c \
../Board_Drivers/timer7.c \
../Board_Drivers/timer8.c \
../Board_Drivers/timer9.c \
../Board_Drivers/uart2.c \
../Board_Drivers/uart4.c \
../Board_Drivers/uart6.c \
../Board_Drivers/uart7.c \
../Board_Drivers/uart8.c 

OBJS += \
./Board_Drivers/adc.o \
./Board_Drivers/drv_def.o \
./Board_Drivers/i2c2.o \
./Board_Drivers/key.o \
./Board_Drivers/led.o \
./Board_Drivers/spi2.o \
./Board_Drivers/spi3.o \
./Board_Drivers/timer2.o \
./Board_Drivers/timer3.o \
./Board_Drivers/timer4.o \
./Board_Drivers/timer5.o \
./Board_Drivers/timer6.o \
./Board_Drivers/timer7.o \
./Board_Drivers/timer8.o \
./Board_Drivers/timer9.o \
./Board_Drivers/uart2.o \
./Board_Drivers/uart4.o \
./Board_Drivers/uart6.o \
./Board_Drivers/uart7.o \
./Board_Drivers/uart8.o 

C_DEPS += \
./Board_Drivers/adc.d \
./Board_Drivers/drv_def.d \
./Board_Drivers/i2c2.d \
./Board_Drivers/key.d \
./Board_Drivers/led.d \
./Board_Drivers/spi2.d \
./Board_Drivers/spi3.d \
./Board_Drivers/timer2.d \
./Board_Drivers/timer3.d \
./Board_Drivers/timer4.d \
./Board_Drivers/timer5.d \
./Board_Drivers/timer6.d \
./Board_Drivers/timer7.d \
./Board_Drivers/timer8.d \
./Board_Drivers/timer9.d \
./Board_Drivers/uart2.d \
./Board_Drivers/uart4.d \
./Board_Drivers/uart6.d \
./Board_Drivers/uart7.d \
./Board_Drivers/uart8.d 


# Each subdirectory must supply rules for building sources it contributes
Board_Drivers/%.o: ../Board_Drivers/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g3 -ggdb -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\CherryRB" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Simulation" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LADRC" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\USR_printf" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Debug" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\custom" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated\guider_customer_fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated\guider_fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_SOFT" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Letter_Shell" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Gui" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Port" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\SFUD\inc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Core" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\User" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Drivers" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\OLED_SPI" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\TFT_ST7735S" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\FLASH_W25Q16" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Encoder_Speed" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Peripheral\inc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\ui_misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MultiTimer" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LADRC" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\VOFA+" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

