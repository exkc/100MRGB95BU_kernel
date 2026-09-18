CHIP_NAME := $(PLATFORM_CHIP_NAME)

aalsa_src := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

ifeq ($(KDRV_MODULE_BUILD), YES)
CONFIG_LG_BUILTIN_KDRIVER := m
endif

obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lgsic_bc.o
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lgsic_pdm.o
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lgsic_mc.o
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lgsic_card.o
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lgsic_machine.o

EXTRA_CFLAGS += -I$(aalsa_src)/../../hma
EXTRA_CFLAGS += -I$(aalsa_src)/../../fwload
EXTRA_CFLAGS += -I$(aalsa_src)/../../../include
EXTRA_CFLAGS += -I$(aalsa_src)/..
EXTRA_CFLAGS += -I$(aalsa_src)/../../..
EXTRA_CFLAGS += -I$(aalsa_src)/../../base
EXTRA_CFLAGS += -I$(aalsa_src)/../../sys
EXTRA_CFLAGS += -I$(aalsa_src)/../common
EXTRA_CFLAGS += -I$(aalsa_src)/../../../chip
EXTRA_CFLAGS += -DINCLUDE_$(shell echo $(CHIP_NAME) | tr [a-z] [A-Z])_CHIP_KDRV
#EXTRA_CFLAGS += -I$(aalsa_src)/../platform

EXTRA_CFLAGS += -D_ADEC_ARM
EXTRA_CFLAGS += -DCHIP_NAME_$(CHIP_NAME)
EXTRA_CFLAGS += -DAPPLY_DYNAMIC_ALLOCATION=1
EXTRA_CFLAGS += -DCODE_USER=1
EXTRA_CFLAGS += -DCODE_KERNEL=2
EXTRA_CFLAGS += -DCODE_DSP=3
EXTRA_CFLAGS += -DADEC_OPT_CODE=CODE_KERNEL
EXTRA_CFLAGS += -DKDRV_DEBUG_BUILD

EXTRA_CFLAGS += -DAPPLY_SINGLE_DSP=0
EXTRA_CFLAGS += -DSUPPORT_ARC
EXTRA_CFLAGS += -DKDRV_CONFIG_PM
EXTRA_CFLAGS += -DKDRV_CONFIG_PM_AAD
EXTRA_CFLAGS += -DKDRV_CONFIG_PM_AUDIO

ifeq ($(PLATFORM_CHIP_TYPE),FPGA)
EXTRA_CFLAGS += -DCHIP_TYPE_FPGA
endif

ifeq ($(BUILD_FEATURE_audio_board),y)
EXTRA_CFLAGS += -DSUPPORT_SOUNDBAR
endif
