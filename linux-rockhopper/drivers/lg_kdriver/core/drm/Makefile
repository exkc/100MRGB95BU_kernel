# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2021 by LG Electronics Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

CHIP_NAME := $(PLATFORM_CHIP_NAME)
lg1kdrm_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

EXTRA_CFLAGS += -DCHIP_NAME_$(CHIP_NAME)
EXTRA_CFLAGS += -I$(lg1kdrm_src_top)
EXTRA_CFLAGS += -I$(lg1kdrm_src_top)/../hma
EXTRA_CFLAGS += -I$(lg1kdrm_src_top)/../logm
EXTRA_CFLAGS += -I$(lg1kdrm_src_top)/../fbdev
EXTRA_CFLAGS += -I$(lg1kdrm_src_top)/../../include

ifeq ($(KDRV_MODULE_BUILD), YES)
CONFIG_LG_BUILTIN_KDRIVER := m
endif
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lg1kdrm.o


ifeq ($(VERSION),4)
lg1kdrm-objs += drm_4_4.o
else
lg1kdrm-objs += drm.o
endif
lg1kdrm-objs += chma.o

