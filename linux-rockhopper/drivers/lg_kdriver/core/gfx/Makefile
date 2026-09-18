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
#	AUTHOR		:	raxis.lim (raxis.lim@lge.com)
#	DATE        :	2009.12.30
#	DESCRIPTION	:	Makefile for building gfx module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

gfx_MODULE			:= gfx

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_gfx-objs		:= gfx_cfg.o
kdrv_gfx-objs		+= gfx_drv.o
kdrv_gfx-objs		+= gfx_proc.o
kdrv_gfx-objs       += gfx_hw.o
kdrv_gfx-objs       += gfx_surface.o
kdrv_gfx-objs       += gfx_export.o

ifeq ($(INCLUDE_M16P_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/m16p/gfx/gfx_drv_m16p.o
kdrv_gfx-objs       += ../../chip/m16p/gfx/gfx_hw_m16p.o
endif

ifeq ($(INCLUDE_L18_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/l18/gfx/gfx_drv_l18f.o
kdrv_gfx-objs       += ../../chip/l18/gfx/gfx_hw_l18f.o
endif

ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/o18/gfx/gfx_drv_o18.o
kdrv_gfx-objs       += ../../chip/o18/gfx/gfx_hw_o18.o
endif

ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/m19/gfx/gfx_drv_m19.o
kdrv_gfx-objs       += ../../chip/m19/gfx/gfx_hw_m19.o
endif

ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/o20/gfx/gfx_drv_o20.o
kdrv_gfx-objs       += ../../chip/o20/gfx/gfx_hw_o20.o
endif

ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/e60/gfx/gfx_drv_e60.o
kdrv_gfx-objs       += ../../chip/e60/gfx/gfx_hw_e60.o
endif

ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/o22/gfx/gfx_drv_o22.o
kdrv_gfx-objs       += ../../chip/o22/gfx/gfx_hw_o22.o
endif

ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/m23/gfx/gfx_drv_m23.o
kdrv_gfx-objs       += ../../chip/m23/gfx/gfx_hw_m23.o
endif

ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/o24/gfx/gfx_drv_o24.o
kdrv_gfx-objs       += ../../chip/o24/gfx/gfx_hw_o24.o
endif

ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_gfx-objs       += ../../chip/o26/gfx/gfx_drv_o26.o
kdrv_gfx-objs       += ../../chip/o26/gfx/gfx_hw_o26.o
endif

#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_gfx-CFLAGS	+=
kdrv_gfx-CFLAGS	+=
kdrv_gfx-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_gfx-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(gfx_MODULE)/,$(kdrv_gfx-objs))
else
obj-m				:= kdrv_gfx.o
endif
