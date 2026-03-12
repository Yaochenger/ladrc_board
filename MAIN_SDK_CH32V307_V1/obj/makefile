################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include Board_Drivers/subdir.mk
-include Board_Component/TFT_ST7735S/subdir.mk
-include Board_Component/Simulation/subdir.mk
-include Board_Component/SFUD/src/subdir.mk
-include Board_Component/SFUD/port/subdir.mk
-include Board_Component/OLED_SPI/subdir.mk
-include Board_Component/MultiTimer/subdir.mk
-include Board_Component/MPU6050/MPU6050_SOFT/subdir.mk
-include Board_Component/MPU6050/MPU6050_DMP/Driver/subdir.mk
-include Board_Component/Letter_Shell/subdir.mk
-include Board_Component/LADRC/subdir.mk
-include Board_Component/FLASH_W25Q16/subdir.mk
-include Board_Component/Encoder_Speed/subdir.mk
-include Board_Component/CherryRB/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
MAIN_SDK_CH32V307_V1.hex \

SECONDARY_LIST += \
MAIN_SDK_CH32V307_V1.lst \

SECONDARY_SIZE += \
MAIN_SDK_CH32V307_V1.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: MAIN_SDK_CH32V307_V1.elf secondary-outputs

# Tool invocations
MAIN_SDK_CH32V307_V1.elf: $(OBJS) $(USER_OBJS_ESCAPE)
	@	riscv-wch-elf-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -g3 -ggdb -T "e:\ladrc_board\MAIN_SDK_CH32V307_V1\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Xlinker --print-memory-usage -Wl,-Map,"MAIN_SDK_CH32V307_V1.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -o "MAIN_SDK_CH32V307_V1.elf" $(OBJS) $(LIBS)
MAIN_SDK_CH32V307_V1.hex: MAIN_SDK_CH32V307_V1.elf
	@	riscv-wch-elf-objcopy -O ihex "MAIN_SDK_CH32V307_V1.elf" "MAIN_SDK_CH32V307_V1.hex"
MAIN_SDK_CH32V307_V1.lst: MAIN_SDK_CH32V307_V1.elf
	@	riscv-wch-elf-objdump --all-headers --demangle --disassemble -M xw "MAIN_SDK_CH32V307_V1.elf" > "MAIN_SDK_CH32V307_V1.lst"
MAIN_SDK_CH32V307_V1.siz: MAIN_SDK_CH32V307_V1.elf
	riscv-wch-elf-size --format=berkeley "MAIN_SDK_CH32V307_V1.elf"

# Other Targets
clean:
	-$(RM) $(DIR_OBJS) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE) MAIN_SDK_CH32V307_V1.elf
	-$(RM) $(DIR_EXPANDS) $(CALLGRAPH_DOT)
	-$(RM) $(DIR_DEPS)
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets