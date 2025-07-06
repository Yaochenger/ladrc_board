################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/src/ch32f20x_adc.c \
../Peripheral/src/ch32f20x_bkp.c \
../Peripheral/src/ch32f20x_can.c \
../Peripheral/src/ch32f20x_crc.c \
../Peripheral/src/ch32f20x_dac.c \
../Peripheral/src/ch32f20x_dbgmcu.c \
../Peripheral/src/ch32f20x_dma.c \
../Peripheral/src/ch32f20x_dvp.c \
../Peripheral/src/ch32f20x_exti.c \
../Peripheral/src/ch32f20x_flash.c \
../Peripheral/src/ch32f20x_fsmc.c \
../Peripheral/src/ch32f20x_gpio.c \
../Peripheral/src/ch32f20x_i2c.c \
../Peripheral/src/ch32f20x_iwdg.c \
../Peripheral/src/ch32f20x_misc.c \
../Peripheral/src/ch32f20x_opa.c \
../Peripheral/src/ch32f20x_pwr.c \
../Peripheral/src/ch32f20x_rcc.c \
../Peripheral/src/ch32f20x_rng.c \
../Peripheral/src/ch32f20x_rtc.c \
../Peripheral/src/ch32f20x_sdio.c \
../Peripheral/src/ch32f20x_spi.c \
../Peripheral/src/ch32f20x_tim.c \
../Peripheral/src/ch32f20x_usart.c \
../Peripheral/src/ch32f20x_wwdg.c 

OBJS += \
./Peripheral/src/ch32f20x_adc.o \
./Peripheral/src/ch32f20x_bkp.o \
./Peripheral/src/ch32f20x_can.o \
./Peripheral/src/ch32f20x_crc.o \
./Peripheral/src/ch32f20x_dac.o \
./Peripheral/src/ch32f20x_dbgmcu.o \
./Peripheral/src/ch32f20x_dma.o \
./Peripheral/src/ch32f20x_dvp.o \
./Peripheral/src/ch32f20x_exti.o \
./Peripheral/src/ch32f20x_flash.o \
./Peripheral/src/ch32f20x_fsmc.o \
./Peripheral/src/ch32f20x_gpio.o \
./Peripheral/src/ch32f20x_i2c.o \
./Peripheral/src/ch32f20x_iwdg.o \
./Peripheral/src/ch32f20x_misc.o \
./Peripheral/src/ch32f20x_opa.o \
./Peripheral/src/ch32f20x_pwr.o \
./Peripheral/src/ch32f20x_rcc.o \
./Peripheral/src/ch32f20x_rng.o \
./Peripheral/src/ch32f20x_rtc.o \
./Peripheral/src/ch32f20x_sdio.o \
./Peripheral/src/ch32f20x_spi.o \
./Peripheral/src/ch32f20x_tim.o \
./Peripheral/src/ch32f20x_usart.o \
./Peripheral/src/ch32f20x_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32f20x_adc.d \
./Peripheral/src/ch32f20x_bkp.d \
./Peripheral/src/ch32f20x_can.d \
./Peripheral/src/ch32f20x_crc.d \
./Peripheral/src/ch32f20x_dac.d \
./Peripheral/src/ch32f20x_dbgmcu.d \
./Peripheral/src/ch32f20x_dma.d \
./Peripheral/src/ch32f20x_dvp.d \
./Peripheral/src/ch32f20x_exti.d \
./Peripheral/src/ch32f20x_flash.d \
./Peripheral/src/ch32f20x_fsmc.d \
./Peripheral/src/ch32f20x_gpio.d \
./Peripheral/src/ch32f20x_i2c.d \
./Peripheral/src/ch32f20x_iwdg.d \
./Peripheral/src/ch32f20x_misc.d \
./Peripheral/src/ch32f20x_opa.d \
./Peripheral/src/ch32f20x_pwr.d \
./Peripheral/src/ch32f20x_rcc.d \
./Peripheral/src/ch32f20x_rng.d \
./Peripheral/src/ch32f20x_rtc.d \
./Peripheral/src/ch32f20x_sdio.d \
./Peripheral/src/ch32f20x_spi.d \
./Peripheral/src/ch32f20x_tim.d \
./Peripheral/src/ch32f20x_usart.d \
./Peripheral/src/ch32f20x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/%.o: ../Peripheral/src/%.c
	@	@	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mthumb-interwork -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\MRS_DATA\workspace\CH32F203VCT6\Core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Gui" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\custom" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_customer_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\ui_misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Encoder_Speed" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\FLASH_W25Q16" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LADRC" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Letter_Shell" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_SOFT" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MultiTimer" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\OLED_SPI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Simulation" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\TFT_ST7735S" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\USR_printf" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\VOFA+" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Drivers" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Sample" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\CherryRB" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Debug" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

