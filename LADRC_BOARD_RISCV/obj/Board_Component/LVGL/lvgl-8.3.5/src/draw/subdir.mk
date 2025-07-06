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
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g3 -ggdb -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\CherryRB" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Simulation" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LADRC" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\USR_printf" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Debug" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\custom" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated\guider_customer_fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated\guider_fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_SOFT" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Letter_Shell" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Gui" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Port" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\SFUD\inc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Core" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\User" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Drivers" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\OLED_SPI" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\TFT_ST7735S" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\FLASH_W25Q16" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Encoder_Speed" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Peripheral\inc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\ui_misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MultiTimer" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LADRC" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\VOFA+" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

