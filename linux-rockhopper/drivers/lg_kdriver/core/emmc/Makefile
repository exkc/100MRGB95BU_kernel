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
#	DATE            :       2015.07.17                                     #
#	DESCRIPTION	:	Makefile for building emmc module                #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk
include $(pwd)
LOCAL_PATH := $(call my-dir)
emmc_MODULE			:= emmc

emmc_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_emmc-objs		:= emmc_cfg.o
kdrv_emmc-objs		+= emmc_drv.o
kdrv_emmc-objs		+= emmc_core.o
kdrv_emmc-objs		+= emmc_proc.o
kdrv_emmc-objs		+= emmc_func.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_emmc-CFLAGS	+= -I$(emmc_src_top)/./
kdrv_emmc-CFLAGS	+=
kdrv_emmc-CFLAGS	+=
kdrv_emmc-ASFLAGS	+= -I$(emmc_src_top)/./

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_emmc-CFLAGS)
EXTRA_CFLAGS		+= $(kdrv_emmc-ASFLAGS)
EXTRA_CFLAGS		+= -I$(emmc_src_top)/./

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(emmc_MODULE)/,$(kdrv_emmc-objs))
else
obj-m				:= kdrv_emmc.o
endif
