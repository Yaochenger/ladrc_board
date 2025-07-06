################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_disp.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_event.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_group.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_indev.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_indev_scroll.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_class.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_draw.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_pos.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_scroll.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_style.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_style_gen.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_tree.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_refr.c \
../Board_Component/LVGL/lvgl-8.3.5/src/core/lv_theme.c 

OBJS += \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_disp.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_event.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_group.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_indev.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_indev_scroll.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_class.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_draw.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_pos.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_scroll.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_style.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_style_gen.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_tree.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_refr.o \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_theme.o 

C_DEPS += \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_disp.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_event.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_group.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_indev.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_indev_scroll.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_class.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_draw.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_pos.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_scroll.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_style.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_style_gen.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_obj_tree.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_refr.d \
./Board_Component/LVGL/lvgl-8.3.5/src/core/lv_theme.d 


# Each subdirectory must supply rules for building sources it contributes
Board_Component/LVGL/lvgl-8.3.5/src/core/%.o: ../Board_Component/LVGL/lvgl-8.3.5/src/core/%.c
	@	@	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mthumb-interwork -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\MRS_DATA\workspace\CH32F203VCT6\Core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Gui" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\custom" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_customer_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\ui_misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Encoder_Speed" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\FLASH_W25Q16" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LADRC" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Letter_Shell" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_SOFT" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MultiTimer" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\OLED_SPI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Simulation" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\TFT_ST7735S" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\USR_printf" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\VOFA+" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Drivers" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Sample" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\CherryRB" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Debug" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

