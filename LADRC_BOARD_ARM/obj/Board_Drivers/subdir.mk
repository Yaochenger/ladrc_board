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
	@	@	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mthumb-interwork -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\MRS_DATA\workspace\CH32F203VCT6\Core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Gui" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\custom" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_customer_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\ui_misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Encoder_Speed" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\FLASH_W25Q16" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LADRC" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Letter_Shell" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_SOFT" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MultiTimer" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\OLED_SPI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Simulation" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\TFT_ST7735S" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\USR_printf" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\VOFA+" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Drivers" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Sample" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\CherryRB" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Debug" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

