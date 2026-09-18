# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

#   ---------------------------------------------------------------------------#
#                                                                              #
#	FILE NAME	:	makefile                                                   #
#	VERSION		:	1.0                                                        #
#	AUTHOR		:	raxis.lim@lge.com
#	DATE        :	2021.08.25
#	DESCRIPTION	:	Makefile for building pwm module
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

pwm_MODULE			:= pwm

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
ifeq ($(CONFIG_PWM),y)
kdrv_pwm-objs		:= lg1k_pwm_drv.o
kdrv_pwm-objs		+= lg1k_pwm_cfg.o
kdrv_pwm-objs		+= fan/lg1k_pwm_fan_drv.o
#kdrv_pwm-objs		+= fan/m19/lg1k_pwm_m19_fan_drv.o
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_pwm-objs		+= fan/o22/lg1k_pwm_o22_fan_drv.o
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_pwm-objs		+= fan/o24/lg1k_pwm_o24_fan_drv.o
endif
ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_pwm-objs		+= fan/o26/lg1k_pwm_o26_fan_drv.o
endif
kdrv_pwm-objs		+=

else
kdrv_pwm-objs		:= lg1k_pwm_dummy.o
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_pwm-CFLAGS += -DCHIP_NAME_$(PLATFORM_CHIP_NAME)
kdrv_pwm-CFLAGS	+=
kdrv_pwm-CFLAGS	+=
kdrv_pwm-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_pwm-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(pwm_MODULE)/,$(kdrv_pwm-objs))
else
obj-m				:= kdrv_pwm.o
endif


