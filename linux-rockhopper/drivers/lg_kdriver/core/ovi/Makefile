
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
#	AUTHOR		:	dj911.kim@lge.com
#	DATE        :	2012.09.09
#	DESCRIPTION	:	Makefile for building ovi module                           #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

ovi_MODULE			:= ovi


#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_ovi-objs		+= ovi_drv.o
kdrv_ovi-objs		+= ovi_cfg.o
kdrv_ovi-objs		+= ovi_hal.o
kdrv_ovi-objs		+= ovi_proc.o
ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/m17/ovi/ovi_hw_m17.o
endif
ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/o18/ovi/ovi_hw_o18.o
endif
ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/m19/ovi/ovi_hw_m19.o
endif
ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/o20/ovi/ovi_hw_o20.o
endif
ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/e60/ovi/ovi_hw_e60.o
endif
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/o22/ovi/ovi_hw_o22.o
endif
ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/m23/ovi/ovi_hw_m23.o
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/o24/ovi/ovi_hw_o24.o
endif
ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_ovi-objs		+= ../../chip/o26/ovi/ovi_hw_o26.o
endif

#------------------------------------------------------------------------------
# REVISION maker using MD5
# -----------------------------------------------------------------------------


#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/be
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/be/pwm
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/ovi
ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m17/ovi
endif
ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o18/ovi
endif
ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m19/ovi
endif
ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/e60/ovi
endif
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o22/ovi
endif
ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m23/ovi
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o24/ovi
endif
ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_ovi-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o26/ovi
endif

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_ovi-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(ovi_MODULE)/,$(kdrv_ovi-objs))
else
obj-m				:= kdrv_ovi.o
endif
