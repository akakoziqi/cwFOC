# 模块名_DIR 是上一层传递下来的参数，
# 是从工程根目录到该模块文件夹的路径

# 向 C_SOURCES 中添加需要编译的源文件
C_SOURCES += $(wildcard $(Core_DIR)/app/*.c)
C_SOURCES += $(wildcard $(Core_DIR)/api/*.c)
C_SOURCES += $(wildcard $(Core_DIR)/drv/*.c)
C_SOURCES += $(wildcard $(Core_DIR)/sys/*.c)
C_SOURCES += $(wildcard $(Core_DIR)/utl/*.c)

# 向 C_INCLUDES 中添加头文件路径
C_INCLUDES += -I$(Core_DIR)/app
C_INCLUDES += -I$(Core_DIR)/api
C_INCLUDES += -I$(Core_DIR)/drv
C_INCLUDES += -I$(Core_DIR)/sys
C_INCLUDES += -I$(Core_DIR)/utl
