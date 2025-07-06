################################################################################
# MRS Version: 1.9.2
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board_Component/LLGUI/Misc/LL_Characters.c \
../Board_Component/LLGUI/Misc/LL_Font.c \
../Board_Component/LLGUI/Misc/LL_Lattice.c \
../Board_Component/LLGUI/Misc/LL_Linked_List.c \
../Board_Component/LLGUI/Misc/LL_Port.c \
../Board_Component/LLGUI/Misc/LL_Queue.c \
../Board_Component/LLGUI/Misc/LL_String.c \
../Board_Component/LLGUI/Misc/LL_Timer.c \
../Board_Component/LLGUI/Misc/LL_ZkBin.c \
../Board_Component/LLGUI/Misc/freeRtosHeap4.c \
../Board_Component/LLGUI/Misc/qrcodegen.c \
../Board_Component/LLGUI/Misc/tlsf.c 

OBJS += \
./Board_Component/LLGUI/Misc/LL_Characters.o \
./Board_Component/LLGUI/Misc/LL_Font.o \
./Board_Component/LLGUI/Misc/LL_Lattice.o \
./Board_Component/LLGUI/Misc/LL_Linked_List.o \
./Board_Component/LLGUI/Misc/LL_Port.o \
./Board_Component/LLGUI/Misc/LL_Queue.o \
./Board_Component/LLGUI/Misc/LL_String.o \
./Board_Component/LLGUI/Misc/LL_Timer.o \
./Board_Component/LLGUI/Misc/LL_ZkBin.o \
./Board_Component/LLGUI/Misc/freeRtosHeap4.o \
./Board_Component/LLGUI/Misc/qrcodegen.o \
./Board_Component/LLGUI/Misc/tlsf.o 

C_DEPS += \
./Board_Component/LLGUI/Misc/LL_Characters.d \
./Board_Component/LLGUI/Misc/LL_Font.d \
./Board_Component/LLGUI/Misc/LL_Lattice.d \
./Board_Component/LLGUI/Misc/LL_Linked_List.d \
./Board_Component/LLGUI/Misc/LL_Port.d \
./Board_Component/LLGUI/Misc/LL_Queue.d \
./Board_Component/LLGUI/Misc/LL_String.d \
./Board_Component/LLGUI/Misc/LL_Timer.d \
./Board_Component/LLGUI/Misc/LL_ZkBin.d \
./Board_Component/LLGUI/Misc/freeRtosHeap4.d \
./Board_Component/LLGUI/Misc/qrcodegen.d \
./Board_Component/LLGUI/Misc/tlsf.d 


# Each subdirectory must supply rules for building sources it contributes
Board_Component/LLGUI/Misc/%.o: ../Board_Component/LLGUI/Misc/%.c
	@	@	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mthumb-interwork -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common  -g -I"C:\MRS_DATA\workspace\CH32F203VCT6\Core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\draw" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\extra" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Gui" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI\Port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\core" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\font" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\hal" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\src\widgets" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL\lvgl-8.3.5\examples\porting" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\custom" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_customer_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\generated\guider_fonts" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_GUI\ui_misc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Encoder_Speed" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\FLASH_W25Q16" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LADRC" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Letter_Shell" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LLGUI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\LVGL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\Driver" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_DMP\eMPL" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MPU6050\MPU6050_SOFT" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\MultiTimer" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\OLED_SPI" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\SFUD\port" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\Simulation" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\TFT_ST7735S" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\USR_printf" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\VOFA+" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Drivers" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Sample" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Board_Component\CherryRB" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Debug" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\inc" -I"C:\MRS_DATA\workspace\CH32F203VCT6\Peripheral\src" -I"C:\MRS_DATA\workspace\CH32F203VCT6\User" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

