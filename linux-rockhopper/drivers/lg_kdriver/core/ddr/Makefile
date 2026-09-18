
KDRV_TOP_DIR    := $(if $(filter /%,$(src)),$(src)/..,$(srctree)/$(src)/..)
KDRV_INC_DIR    := $(realpath $(KDRV_TOP_DIR)/../include)
KDRV_PLT_DIR    := $(realpath $(KDRV_TOP_DIR)/../platform)
KDRV_CHIP_DIR   := $(realpath $(KDRV_TOP_DIR)/../chip)
export KDRV_TOP_DIR

include $(KDRV_TOP_DIR)/modules.mk

#
export KDRV_MODULE_BUILD

ifeq ($(KDRV_MODULE_BUILD),YES)
CONFIG_LG_BUILTIN_KDRIVER := m
endif
ifeq ($(CONFIG_LG_BUILTIN_KDRIVER),)
CONFIG_LG_BUILTIN_KDRIVER := m
endif

#
CHIP_NAME := $(PLATFORM_CHIP_NAME)

ddr_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lg1kddr.o

ccflags-y += -I$(ddr_src_top)/include
ccflags-y += -DCHIP_NAME_$(CHIP_NAME)

ifeq ($(CHIP_NAME), m23)
lg1kddr-objs += m23_ddr_init.o
lg1kddr-objs += m23_ddr_ctrl.o
endif

ifeq ($(CHIP_NAME), o24)
lg1kddr-objs += o24_ddr_init.o
lg1kddr-objs += o24_ddr_ctrl.o
lg1kddr-objs += dmcu.o
endif

lg1kddr-objs += top_ddr.o

lg1kddr-objs += register.o
lg1kddr-objs += ddr_drv.o
lg1kddr-objs += proc.o
lg1kddr-objs += command.o
lg1kddr-objs += monitor.o
