################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Component/LLGUI/Gui/LL_Background.c \
../Board_Component/LLGUI/Gui/LL_Button.c \
../Board_Component/LLGUI/Gui/LL_ButtonEx.c \
../Board_Component/LLGUI/Gui/LL_CheckBox.c \
../Board_Component/LLGUI/Gui/LL_ComboBox.c \
../Board_Component/LLGUI/Gui/LL_DateTime.c \
../Board_Component/LLGUI/Gui/LL_Gauge.c \
../Board_Component/LLGUI/Gui/LL_General.c \
../Board_Component/LLGUI/Gui/LL_Gui.c \
../Board_Component/LLGUI/Gui/LL_IconSlider.c \
../Board_Component/LLGUI/Gui/LL_Image.c \
../Board_Component/LLGUI/Gui/LL_Keyboard.c \
../Board_Component/LLGUI/Gui/LL_LineEdit.c \
../Board_Component/LLGUI/Gui/LL_ProgressBar.c \
../Board_Component/LLGUI/Gui/LL_QRCode.c \
../Board_Component/LLGUI/Gui/LL_Slider.c \
../Board_Component/LLGUI/Gui/LL_Text.c \
../Board_Component/LLGUI/Gui/LL_Window.c 

OBJS += \
./Board_Component/LLGUI/Gui/LL_Background.o \
./Board_Component/LLGUI/Gui/LL_Button.o \
./Board_Component/LLGUI/Gui/LL_ButtonEx.o \
./Board_Component/LLGUI/Gui/LL_CheckBox.o \
./Board_Component/LLGUI/Gui/LL_ComboBox.o \
./Board_Component/LLGUI/Gui/LL_DateTime.o \
./Board_Component/LLGUI/Gui/LL_Gauge.o \
./Board_Component/LLGUI/Gui/LL_General.o \
./Board_Component/LLGUI/Gui/LL_Gui.o \
./Board_Component/LLGUI/Gui/LL_IconSlider.o \
./Board_Component/LLGUI/Gui/LL_Image.o \
./Board_Component/LLGUI/Gui/LL_Keyboard.o \
./Board_Component/LLGUI/Gui/LL_LineEdit.o \
./Board_Component/LLGUI/Gui/LL_ProgressBar.o \
./Board_Component/LLGUI/Gui/LL_QRCode.o \
./Board_Component/LLGUI/Gui/LL_Slider.o \
./Board_Component/LLGUI/Gui/LL_Text.o \
./Board_Component/LLGUI/Gui/LL_Window.o 

C_DEPS += \
./Board_Component/LLGUI/Gui/LL_Background.d \
./Board_Component/LLGUI/Gui/LL_Button.d \
./Board_Component/LLGUI/Gui/LL_ButtonEx.d \
./Board_Component/LLGUI/Gui/LL_CheckBox.d \
./Board_Component/LLGUI/Gui/LL_ComboBox.d \
./Board_Component/LLGUI/Gui/LL_DateTime.d \
./Board_Component/LLGUI/Gui/LL_Gauge.d \
./Board_Component/LLGUI/Gui/LL_General.d \
./Board_Component/LLGUI/Gui/LL_Gui.d \
./Board_Component/LLGUI/Gui/LL_IconSlider.d \
./Board_Component/LLGUI/Gui/LL_Image.d \
./Board_Component/LLGUI/Gui/LL_Keyboard.d \
./Board_Component/LLGUI/Gui/LL_LineEdit.d \
./Board_Component/LLGUI/Gui/LL_ProgressBar.d \
./Board_Component/LLGUI/Gui/LL_QRCode.d \
./Board_Component/LLGUI/Gui/LL_Slider.d \
./Board_Component/LLGUI/Gui/LL_Text.d \
./Board_Component/LLGUI/Gui/LL_Window.d 


# Each subdirectory must supply rules for building sources it contributes
Board_Component/LLGUI/Gui/%.o: ../Board_Component/LLGUI/Gui/%.c
	@	@	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mthumb-interwork -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\MRS_DATA\workspace\CH32F203VCT6\Core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Gui" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\custom" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_customer_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\ui_misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Encoder_Speed" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\FLASH_W25Q16" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LADRC" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Letter_Shell" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_SOFT" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MultiTimer" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\OLED_SPI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Simulation" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\TFT_ST7735S" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\USR_printf" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\VOFA+" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Drivers" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Sample" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\CherryRB" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Debug" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

