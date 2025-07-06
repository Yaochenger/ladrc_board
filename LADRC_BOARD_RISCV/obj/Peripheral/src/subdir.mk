################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Peripheral/src/ch32v30x_adc.c \
../Peripheral/src/ch32v30x_bkp.c \
../Peripheral/src/ch32v30x_can.c \
../Peripheral/src/ch32v30x_crc.c \
../Peripheral/src/ch32v30x_dac.c \
../Peripheral/src/ch32v30x_dbgmcu.c \
../Peripheral/src/ch32v30x_dma.c \
../Peripheral/src/ch32v30x_dvp.c \
../Peripheral/src/ch32v30x_eth.c \
../Peripheral/src/ch32v30x_exti.c \
../Peripheral/src/ch32v30x_flash.c \
../Peripheral/src/ch32v30x_fsmc.c \
../Peripheral/src/ch32v30x_gpio.c \
../Peripheral/src/ch32v30x_i2c.c \
../Peripheral/src/ch32v30x_iwdg.c \
../Peripheral/src/ch32v30x_misc.c \
../Peripheral/src/ch32v30x_opa.c \
../Peripheral/src/ch32v30x_pwr.c \
../Peripheral/src/ch32v30x_rcc.c \
../Peripheral/src/ch32v30x_rng.c \
../Peripheral/src/ch32v30x_rtc.c \
../Peripheral/src/ch32v30x_sdio.c \
../Peripheral/src/ch32v30x_spi.c \
../Peripheral/src/ch32v30x_tim.c \
../Peripheral/src/ch32v30x_usart.c \
../Peripheral/src/ch32v30x_wwdg.c 

OBJS += \
./Peripheral/src/ch32v30x_adc.o \
./Peripheral/src/ch32v30x_bkp.o \
./Peripheral/src/ch32v30x_can.o \
./Peripheral/src/ch32v30x_crc.o \
./Peripheral/src/ch32v30x_dac.o \
./Peripheral/src/ch32v30x_dbgmcu.o \
./Peripheral/src/ch32v30x_dma.o \
./Peripheral/src/ch32v30x_dvp.o \
./Peripheral/src/ch32v30x_eth.o \
./Peripheral/src/ch32v30x_exti.o \
./Peripheral/src/ch32v30x_flash.o \
./Peripheral/src/ch32v30x_fsmc.o \
./Peripheral/src/ch32v30x_gpio.o \
./Peripheral/src/ch32v30x_i2c.o \
./Peripheral/src/ch32v30x_iwdg.o \
./Peripheral/src/ch32v30x_misc.o \
./Peripheral/src/ch32v30x_opa.o \
./Peripheral/src/ch32v30x_pwr.o \
./Peripheral/src/ch32v30x_rcc.o \
./Peripheral/src/ch32v30x_rng.o \
./Peripheral/src/ch32v30x_rtc.o \
./Peripheral/src/ch32v30x_sdio.o \
./Peripheral/src/ch32v30x_spi.o \
./Peripheral/src/ch32v30x_tim.o \
./Peripheral/src/ch32v30x_usart.o \
./Peripheral/src/ch32v30x_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32v30x_adc.d \
./Peripheral/src/ch32v30x_bkp.d \
./Peripheral/src/ch32v30x_can.d \
./Peripheral/src/ch32v30x_crc.d \
./Peripheral/src/ch32v30x_dac.d \
./Peripheral/src/ch32v30x_dbgmcu.d \
./Peripheral/src/ch32v30x_dma.d \
./Peripheral/src/ch32v30x_dvp.d \
./Peripheral/src/ch32v30x_eth.d \
./Peripheral/src/ch32v30x_exti.d \
./Peripheral/src/ch32v30x_flash.d \
./Peripheral/src/ch32v30x_fsmc.d \
./Peripheral/src/ch32v30x_gpio.d \
./Peripheral/src/ch32v30x_i2c.d \
./Peripheral/src/ch32v30x_iwdg.d \
./Peripheral/src/ch32v30x_misc.d \
./Peripheral/src/ch32v30x_opa.d \
./Peripheral/src/ch32v30x_pwr.d \
./Peripheral/src/ch32v30x_rcc.d \
./Peripheral/src/ch32v30x_rng.d \
./Peripheral/src/ch32v30x_rtc.d \
./Peripheral/src/ch32v30x_sdio.d \
./Peripheral/src/ch32v30x_spi.d \
./Peripheral/src/ch32v30x_tim.d \
./Peripheral/src/ch32v30x_usart.d \
./Peripheral/src/ch32v30x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/%.o: ../Peripheral/src/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g3 -ggdb -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\CherryRB" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Simulation" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LADRC" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\USR_printf" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Debug" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\custom" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated\guider_customer_fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated\guider_fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_SOFT" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Letter_Shell" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Gui" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Port" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\SFUD\inc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Core" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\User" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Drivers" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\OLED_SPI" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\TFT_ST7735S" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\FLASH_W25Q16" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Encoder_Speed" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Peripheral\inc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\ui_misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MultiTimer" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LADRC" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\VOFA+" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

