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
#	DESCRIPTION	:	Makefile for building irb module                #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk
include $(pwd)
LOCAL_PATH := $(call my-dir)
irb_MODULE			:= irb

# TODO: define your driver source file
#-------------------------------------------------------------------------------

kdrv_irb-objs		:= irb_cfg.o
kdrv_irb-objs		+= irb_drv.o
kdrv_irb-objs		+= irb_proc.o
kdrv_irb-objs		+= irb_core.o
ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_irb-objs            += ../../chip/o20/irb/irb_o20_main.o
kdrv_irb-objs            += ../../chip/o20/irb/irb_o20_proc.o
kdrv_irb-objs            += ../../chip/o20/irb/irb_o20_func.o
endif
ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_irb-objs            += ../../chip/e60/irb/irb_e60_main.o
kdrv_irb-objs            += ../../chip/e60/irb/irb_e60_proc.o
kdrv_irb-objs            += ../../chip/e60/irb/irb_e60_func.o
endif
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_irb-objs            += ../../chip/o22/irb/irb_o22_main.o
kdrv_irb-objs            += ../../chip/o22/irb/irb_o22_proc.o
kdrv_irb-objs            += ../../chip/o22/irb/irb_o22_func.o
endif
ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_irb-objs            += ../../chip/m23/irb/irb_m23_main.o
kdrv_irb-objs            += ../../chip/m23/irb/irb_m23_proc.o
kdrv_irb-objs            += ../../chip/m23/irb/irb_m23_func.o
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_irb-objs            += ../../chip/o24/irb/irb_o24_main.o
kdrv_irb-objs            += ../../chip/o24/irb/irb_o24_proc.o
kdrv_irb-objs            += ../../chip/o24/irb/irb_o24_func.o
endif
ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_irb-objs            += ../../chip/o26/irb/irb_o26_main.o
kdrv_irb-objs            += ../../chip/o26/irb/irb_o26_proc.o
kdrv_irb-objs            += ../../chip/o26/irb/irb_o26_func.o
endif
#-------------------------------------------------------------------------------
#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------

kdrv_irb-CFLAGS	+= -I./
kdrv_irb-ASFLAGS	+= -I./

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(irb_MODULE)/,$(kdrv_irb-objs))
else
obj-m				:= kdrv_irb.o
endif
