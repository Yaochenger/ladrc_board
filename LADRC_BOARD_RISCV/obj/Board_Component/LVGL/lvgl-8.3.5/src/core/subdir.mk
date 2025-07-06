################################################################################
# MRS Version: 1.9.2
# �Զ����ɵ��ļ�����Ҫ�༭��
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
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g3 -ggdb -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\CherryRB" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Simulation" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LADRC" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\USR_printf" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Debug" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\custom" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated\guider_customer_fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated\guider_fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\generated" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_SOFT" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Letter_Shell" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Fonts" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Gui" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LLGUI\Port" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\SFUD\inc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Core" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\User" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Drivers" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\OLED_SPI" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\TFT_ST7735S" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\FLASH_W25Q16" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\Encoder_Speed" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Peripheral\inc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_GUI\ui_misc" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\MultiTimer" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\LADRC" -I"H:\LADRC_Board\Code\ladrc_board\LADRC_Board_NoneOS\Board_Component\VOFA+" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

