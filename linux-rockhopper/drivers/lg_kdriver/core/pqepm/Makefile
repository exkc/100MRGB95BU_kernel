
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.


#	---------------------------------------------------------------------------#
#																			   #
#	FILE NAME	:	makefile												   #
#	VERSION		:	1.0														   #
#	AUTHOR		:	dongho7.park (dongho7.park@lge.com)
#	DATE		:	2009.12.30
#	DESCRIPTION :	Makefile for building de module						 #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

pqepm_MODULE			:= pqepm

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_pqepm-objs		:=
kdrv_pqepm-objs		+= pqe_pm_drv.o
kdrv_pqepm-objs		+= pqe_pm_proc.o

ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_pqepm-objs		+= chip/o20/pqe_pm_o20_hw.o
kdrv_pqepm-objs		+=
endif
ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_pqepm-objs		+=
kdrv_pqepm-objs		+=
endif
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_pqepm-objs		+= chip/o22/pqe_pm_o22_hw.o
kdrv_pqepm-objs		+=
endif
ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_pqepm-objs		+= chip/m23/pqe_pm_m23_hw.o
kdrv_pqepm-objs		+=
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_pqepm-objs		+= chip/o24/pqe_pm_o24_hw.o
kdrv_pqepm-objs		+=
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_pqepm-objs		+= chip/o26/pqe_pm_o26_hw.o
kdrv_pqepm-objs		+=
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_pqepm-CFLAGS	+=
kdrv_pqepm-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_pqepm-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(pqepm_MODULE)/,$(kdrv_pqepm-objs))
else
obj-m				:= kdrv_pqepm.o
endif
