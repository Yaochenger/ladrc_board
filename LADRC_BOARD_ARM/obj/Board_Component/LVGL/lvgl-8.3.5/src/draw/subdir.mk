################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_arc.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_img.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_label.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_layer.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_line.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_mask.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_rect.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_transform.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_triangle.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_buf.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_cache.c \
../Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_decoder.c 

OBJS += \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_arc.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_img.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_label.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_layer.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_line.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_mask.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_rect.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_transform.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_triangle.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_buf.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_cache.o \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_decoder.o 

C_DEPS += \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_arc.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_img.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_label.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_layer.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_line.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_mask.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_rect.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_transform.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_draw_triangle.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_buf.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_cache.d \
./Board_Component/LVGL/lvgl-8.3.5/src/draw/lv_img_decoder.d 


# Each subdirectory must supply rules for building sources it contributes
Board_Component/LVGL/lvgl-8.3.5/src/draw/%.o: ../Board_Component/LVGL/lvgl-8.3.5/src/draw/%.c
	@	@	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mthumb-interwork -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\MRS_DATA\workspace\CH32F203VCT6\Core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Gui" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\custom" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_customer_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\ui_misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Encoder_Speed" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\FLASH_W25Q16" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LADRC" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Letter_Shell" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_SOFT" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MultiTimer" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\OLED_SPI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Simulation" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\TFT_ST7735S" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\USR_printf" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\VOFA+" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Drivers" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Sample" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\CherryRB" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Debug" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

