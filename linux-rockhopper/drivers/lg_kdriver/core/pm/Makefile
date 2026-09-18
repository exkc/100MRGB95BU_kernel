# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#                                                                              #
#   ---------------------------------------------------------------------------#
#                                                                              #
#	FILE NAME	:	makefile                                       #
#	VERSION		:	1.0                                            #
#	AUTHOR		:	ingyu.yang (ingyu.yang@lge.com                 #
#	DATE            :       2009.12.30                                     #
#	DESCRIPTION	:	Makefile for building pm module                #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk
include $(pwd)
LOCAL_PATH := $(call my-dir)
pm_MODULE			:= pm

# TODO: define your driver source file
#-------------------------------------------------------------------------------

kdrv_pm-objs		:= pm_cfg.o
kdrv_pm-objs		+= pm_drv.o
kdrv_pm-objs		+= pm_proc.o
kdrv_pm-objs		+= pm_core.o
ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/o26/pm/pm_o26_main.o
kdrv_pm-objs            += ../../chip/o26/pm/pm_o26_proc.o
kdrv_pm-objs            += ../../chip/o26/pm/pm_o26_func.o
kdrv_pm-objs            += ../../chip/o26/pm/pm_o26_governor.o
kdrv_pm-objs            += ../../chip/o26/pm/pm_o26_test.o
kdrv_pm-objs            += ../../chip/o26/pm/pm_o26_avs.o
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/o24/pm/pm_o24_main.o
kdrv_pm-objs            += ../../chip/o24/pm/pm_o24_proc.o
kdrv_pm-objs            += ../../chip/o24/pm/pm_o24_func.o
kdrv_pm-objs            += ../../chip/o24/pm/pm_o24_governor.o
kdrv_pm-objs            += ../../chip/o24/pm/pm_o24_test.o
kdrv_pm-objs            += ../../chip/o24/pm/pm_o24_avs.o
endif
ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/m23/pm/pm_m23_main.o
kdrv_pm-objs            += ../../chip/m23/pm/pm_m23_proc.o
kdrv_pm-objs            += ../../chip/m23/pm/pm_m23_clockgating.o
kdrv_pm-objs            += ../../chip/m23/pm/pm_m23_func.o
kdrv_pm-objs            += ../../chip/m23/pm/pm_m23_governor.o
kdrv_pm-objs            += ../../chip/m23/pm/pm_m23_test.o
kdrv_pm-objs            += ../../chip/m23/pm/pm_m23_avs.o
endif
ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/m17/pm/pm_m17_main.o
kdrv_pm-objs            += ../../chip/m17/pm/pm_m17_proc.o
kdrv_pm-objs            += ../../chip/m17/pm/pm_m17_clockgating.o
kdrv_pm-objs            += ../../chip/m17/pm/pm_m17_func.o
kdrv_pm-objs            += ../../chip/m17/pm/pm_m17_governor.o
kdrv_pm-objs            += ../../chip/m17/pm/pm_m17_test.o
kdrv_pm-objs            += ../../chip/m17/pm/pm_m17_avs.o
endif
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/o22/pm/pm_o22_main.o
kdrv_pm-objs            += ../../chip/o22/pm/pm_o22_proc.o
kdrv_pm-objs            += ../../chip/o22/pm/pm_o22_clockgating.o
kdrv_pm-objs            += ../../chip/o22/pm/pm_o22_func.o
kdrv_pm-objs            += ../../chip/o22/pm/pm_o22_governor.o
kdrv_pm-objs            += ../../chip/o22/pm/pm_o22_test.o
kdrv_pm-objs            += ../../chip/o22/pm/pm_o22_avs.o
endif
ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/e60/pm/pm_e60_main.o
kdrv_pm-objs            += ../../chip/e60/pm/pm_e60_proc.o
kdrv_pm-objs            += ../../chip/e60/pm/pm_e60_clockgating.o
kdrv_pm-objs            += ../../chip/e60/pm/pm_e60_func.o
kdrv_pm-objs            += ../../chip/e60/pm/pm_e60_governor.o
kdrv_pm-objs            += ../../chip/e60/pm/pm_e60_test.o
kdrv_pm-objs            += ../../chip/e60/pm/pm_e60_avs.o
endif
ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/o20/pm/pm_o20_main.o
kdrv_pm-objs            += ../../chip/o20/pm/pm_o20_proc.o
kdrv_pm-objs            += ../../chip/o20/pm/pm_o20_clockgating.o
kdrv_pm-objs            += ../../chip/o20/pm/pm_o20_func.o
kdrv_pm-objs            += ../../chip/o20/pm/pm_o20_governor.o
kdrv_pm-objs            += ../../chip/o20/pm/pm_o20_test.o
kdrv_pm-objs            += ../../chip/o20/pm/pm_o20_avs.o
endif
ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/o18/pm/pm_o18_main.o
kdrv_pm-objs            += ../../chip/o18/pm/pm_o18_proc.o
kdrv_pm-objs            += ../../chip/o18/pm/pm_o18_clockgating.o
kdrv_pm-objs            += ../../chip/o18/pm/pm_o18_func.o
kdrv_pm-objs            += ../../chip/o18/pm/pm_o18_governor.o
kdrv_pm-objs            += ../../chip/o18/pm/pm_o18_test.o
kdrv_pm-objs            += ../../chip/o18/pm/pm_o18_avs.o
endif
ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_pm-objs            += ../../chip/m19/pm/pm_m19_main.o
kdrv_pm-objs            += ../../chip/m19/pm/pm_m19_proc.o
kdrv_pm-objs            += ../../chip/m19/pm/pm_m19_clockgating.o
kdrv_pm-objs            += ../../chip/m19/pm/pm_m19_func.o
kdrv_pm-objs            += ../../chip/m19/pm/pm_m19_governor.o
kdrv_pm-objs            += ../../chip/m19/pm/pm_m19_test.o
kdrv_pm-objs            += ../../chip/m19/pm/pm_m19_avs.o
endif
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_pm-CFLAGS	+= -I./
kdrv_pm-CFLAGS	+=
kdrv_pm-CFLAGS	+=
kdrv_pm-ASFLAGS	+= -I./

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(pm_MODULE)/,$(kdrv_pm-objs))
else
obj-m				:= kdrv_pm.o
endif
