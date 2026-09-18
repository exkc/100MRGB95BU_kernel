# SoC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2024 by LG Electronics Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
sheap_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

sheap-objs		:= sheap_drv.o

sheap-cflags	:= -I$(abspath $(sheap_src_top))
sheap-cflags	+= -I$(abspath $(sheap_src_top)/../../include)
sheap-cflags	+= -I$(abspath $(sheap_src_top)/../hma)
sheap-cflags	+= -I$(abspath $(sheap_src_top)/../logm)

ifneq ($(filter bulssi, $(BUILD_FEATURES)),)
sheap-cflags	+= -DTEST_IOCTL_ALLOWED
endif

ccflags-y		+= $(sheap-cflags)

ifeq ($(KDRV_MODULE_BUILD), YES)
CONFIG_LG_BUILTIN_KDRIVER := m
endif
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += sheap.o
