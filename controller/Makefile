# 项目编译目标名
TARGET = cwFOC

# 调试信息
DEBUG = 0
# 优化等级
OPT = -Ofast
# 链接时优化
LTO = -flto


# 编译临时文件目录
BUILD_DIR = build
EXEC_DIR = build_exec

# 模块导入
Core_DIR = Core
include Core/Core.mk

# 芯片厂商代码库
Libraries_DIR = Libraries
include Libraries/Libraries.mk

# # 第三方库
# ThirdParty_Lib_DIR = ThirdParty_Lib
# include ThirdParty_Lib/ThirdParty_Lib.mk


# C源文件宏定义
# C_DEFS += -D

# C头文件目录
C_INCLUDES +=

# C源文件
C_SOURCES +=



# 链接库
LIBS += -lc -lm -lnosys 
# 库文件路径
LIBDIR += 

#######################################
# 编译器指定
#######################################
PREFIX = arm-none-eabi-
# 启用下一项以指定GCC目录
# GCC_PATH = 
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
DUMP = $(GCC_PATH)/$(PREFIX)objdump
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# 目标单片机配置信息
#######################################
# cpu
CPU = -mcpu=cortex-m0plus

# fpu
FPU = #none

# float-abi
FLOAT-ABI = #none

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections 

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

NO_COLOR = \033[00m
OK_COLOR = \033[32m
ERR_COLOR = \033[31m

#######################################
# LDFLAGS
#######################################

# libraries
LDFLAGS = $(MCU) -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref \
-Wl,--gc-sections -ffunction-sections --specs=nano.specs --specs=nosys.specs $(LTO) 

# default action: build all
all: $(EXEC_DIR)/$(TARGET).elf $(EXEC_DIR)/$(TARGET).hex $(EXEC_DIR)/$(TARGET).bin POST_BUILD

#######################################
# build the application
#######################################
# list of objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	@echo "[CC]    $<"
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@echo "[AS]    $<"
	@$(AS) -c $(ASFLAGS) $< -o $@

$(EXEC_DIR)/$(TARGET).elf: $(OBJECTS) Makefile | $(EXEC_DIR)
	@echo "[LD]    $@"
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(EXEC_DIR)/%.hex: $(EXEC_DIR)/%.elf | $(EXEC_DIR)
	@echo "[HEX]   $< -> $@"
	@$(HEX) $< $@
	
$(EXEC_DIR)/%.bin: $(EXEC_DIR)/%.elf | $(EXEC_DIR)
	@echo "[BIN]   $< -> $@"
	@$(BIN) $< $@
	
$(BUILD_DIR):
	@mkdir $@

$(EXEC_DIR):
	@mkdir $@

#######################################
# POST_BUILD
#######################################
.PHONY: POST_BUILD
POST_BUILD: $(EXEC_DIR)/$(TARGET).elf
	@echo "[DUMP]  $< -> $(EXEC_DIR)/$(TARGET).s"
	@$(DUMP) -d $< > $(EXEC_DIR)/$(TARGET).s

	@echo "[SIZE]  $<"
	@$(SZ) $<
	@echo -e "$(OK_COLOR)Build Finish$(NO_COLOR)"
	
#######################################
# 构建标准库
#######################################
.PHONY: lib
lib:
	@make -C $(Libraries_DIR)
	@echo -e "$(OK_COLOR)Build Lib Finish$(NO_COLOR)"

#######################################
# 清除临时文件
#######################################
.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@echo -e "$(OK_COLOR)Clean Build Finish$(NO_COLOR)"

.PHONY: cleanall
cleanall: clean
	@rm -rf $(EXEC_DIR)
	@echo -e "$(OK_COLOR)Clean Exec Finish$(NO_COLOR)"

#######################################
# 烧录程序
#######################################
.PHONY: flash
flash: $(EXEC_DIR)/$(TARGET).elf
	@echo -e "$(OK_COLOR)Start pyOCD$(NO_COLOR)"
	@pyocd flash $<

#######################################
# 构建并烧录程序
#######################################
.PHONY: run
run:
	@make -j
	@make flash
  
#######################################
# 依赖文件
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

