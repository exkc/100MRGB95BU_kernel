# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

include $(KDRV_TOP_DIR)/modules.mk

base_MODULE			:= base_r2

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_base-objs		:= base_drv.o
kdrv_base-objs		+= base_device.o
kdrv_base-objs		+= os_util.o
kdrv_base-objs		+= memcfg_util.o
kdrv_base-objs		+= memcfg_util_legacy.o
kdrv_base-objs		+= proc_util.o
kdrv_base-objs		+= board_util.o
kdrv_base-objs		+= ../../platform/$(KDRV_PLATFORM_CFG)/platform_init.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_base-CFLAGS	+=
kdrv_base-CFLAGS	+=
kdrv_base-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_base-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
KDRV_MODULE_OBJS	+= $(addprefix $(base_MODULE)/,$(kdrv_base-objs))
else
obj-m				:= kdrv_base.o
endif

