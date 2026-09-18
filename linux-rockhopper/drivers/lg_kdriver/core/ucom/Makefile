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
#	DESCRIPTION	:	Makefile for building ucom module                #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk
include $(pwd)
LOCAL_PATH := $(call my-dir)
ucom_MODULE			:= ucom

# TODO: define your driver source file
#-------------------------------------------------------------------------------

kdrv_ucom-objs		:= ucom_cfg.o
kdrv_ucom-objs		+= ucom_drv.o
kdrv_ucom-objs		+= ucom_proc.o
kdrv_ucom-objs		+= ucom_core.o

ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_ucom-objs            += ../../chip/o26/ucom/ucom_o26_main.o
kdrv_ucom-objs            += ../../chip/o26/ucom/ucom_o26_proc.o
kdrv_ucom-objs            += ../../chip/o26/ucom/ucom_o26_func.o
endif

ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_ucom-objs            += ../../chip/o24/ucom/ucom_o24_main.o
kdrv_ucom-objs            += ../../chip/o24/ucom/ucom_o24_proc.o
kdrv_ucom-objs            += ../../chip/o24/ucom/ucom_o24_func.o
endif

ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_ucom-objs            += ../../chip/m23/ucom/ucom_m23_main.o
kdrv_ucom-objs            += ../../chip/m23/ucom/ucom_m23_proc.o
kdrv_ucom-objs            += ../../chip/m23/ucom/ucom_m23_func.o
endif

ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_ucom-objs            += ../../chip/o22/ucom/ucom_o22_main.o
kdrv_ucom-objs            += ../../chip/o22/ucom/ucom_o22_proc.o
kdrv_ucom-objs            += ../../chip/o22/ucom/ucom_o22_func.o
endif

ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_ucom-objs            += ../../chip/o20/ucom/ucom_o20_main.o
kdrv_ucom-objs            += ../../chip/o20/ucom/ucom_o20_proc.o
kdrv_ucom-objs            += ../../chip/o20/ucom/ucom_o20_func.o
endif

ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_ucom-objs            += ../../chip/e60/ucom/ucom_e60_main.o
kdrv_ucom-objs            += ../../chip/e60/ucom/ucom_e60_proc.o
kdrv_ucom-objs            += ../../chip/e60/ucom/ucom_e60_func.o
endif
#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_ucom-CFLAGS	+= -I./
kdrv_ucom-CFLAGS	+=
kdrv_ucom-CFLAGS	+=
kdrv_ucom-ASFLAGS	+= -I./

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(ucom_MODULE)/,$(kdrv_ucom-objs))
else
obj-m				:= kdrv_ucom.o
endif
