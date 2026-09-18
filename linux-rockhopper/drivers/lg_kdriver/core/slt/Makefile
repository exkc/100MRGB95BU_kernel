#******************************************************************************#
#	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA						   #
#	Copyright(c) 2013 by LG Electronics Inc.								   #
#																			   #
#	This program is free software; you can redistribute it and/or			   #
#	modify it under the terms of the GNU General Public License				   #
#	version 2 as published by the Free Software Foundation.					   #
#																			   #
#	This program is distributed in the hope that it will be useful,			   #
#	but WITHOUT ANY WARRANTY; without even the implied warranty of			   #
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the			   #
#	GNU General Public License for more details.							   #
#																			   #
#   ---------------------------------------------------------------------------#
#                                                                              #
#	FILE NAME	:	makefile                                                   #
#	VERSION		:	1.0                                                        #
#	AUTHOR		:	wunseo.yeo												   #
#	DATE        :	2014.08
#	DESCRIPTION	:	Makefile for building slt module						   #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

slt_MODULE			:= slt

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_slt-objs		:= slt_cfg.o
kdrv_slt-objs		+= slt_drv.o
kdrv_slt-objs		+= slt_hal.o
kdrv_slt-objs		+= slt_proc.o
ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_slt-objs		+= ../../chip/m17/slt/slt_m17.o
endif
ifeq ($(INCLUDE_L18_CHIP_KDRV), YES)
kdrv_slt-objs		+= ../../chip/l18/slt/slt_l18.o
endif
ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_slt-objs		+= ../../chip/o18/slt/slt_o18.o
endif
ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_slt-objs		+= ../../chip/o20/slt/slt_o20.o
endif
ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_slt-objs		+= ../../chip/e60/slt/slt_e60.o
endif
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_slt-objs		+= ../../chip/o22/slt/slt_o22.o
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_slt-CFLAGS	+=
kdrv_slt-CFLAGS	+=
kdrv_slt-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_slt-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(slt_MODULE)/,$(kdrv_slt-objs)) 
else
obj-m				:= kdrv_slt.o
endif
