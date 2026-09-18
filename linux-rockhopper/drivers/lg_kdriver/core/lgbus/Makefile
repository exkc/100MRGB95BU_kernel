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
#	AUTHOR		:	root													   #
#	DATE        :	2009.12.07												   #
#	DESCRIPTION	:	Makefile for building lgbus module						   #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

lgbus_MODULE			:= lgbus

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_lgbus-objs		:= lgbus_cfg.o
kdrv_lgbus-objs		+= lgbus_drv.o
kdrv_lgbus-objs		+= lgbus_hw.o
kdrv_lgbus-objs		+= lgbus_proc.o
ifeq ($(INCLUDE_H13_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/h13/lgbus/lgbus_h13.o
endif
ifeq ($(INCLUDE_M14_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/m14/lgbus/lgbus_m14.o
kdrv_lgbus-objs		+= ../../chip/m14/lgbus/lgbus_m14a0.o
kdrv_lgbus-objs		+= ../../chip/m14/lgbus/lgbus_m14b0.o
endif
ifeq ($(INCLUDE_H14_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/h14/lgbus/lgbus_h14.o
endif
ifeq ($(INCLUDE_H15_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/h15/lgbus/lgbus_h15.o
kdrv_lgbus-objs		+= ../../chip/h15/lgbus/veri_sw/veri_sw_h15_drv.o
endif

ifeq ($(INCLUDE_M16_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/m16/lgbus/lgbus_m16.o
kdrv_lgbus-objs		+= ../../chip/m16/lgbus/lgbus_m16_mpro.o
endif

ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/m17/lgbus/lgbus_m17.o
kdrv_lgbus-objs		+= ../../chip/m17/lgbus/lgbus_m16p_mpro.o
endif

ifeq ($(INCLUDE_L18_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/l18/lgbus/lgbus_l18.o
kdrv_lgbus-objs		+= ../../chip/l18/lgbus/lgbus_l18_mpro.o
endif

ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/o18/lgbus/lgbus_o18.o
kdrv_lgbus-objs		+= ../../chip/o18/lgbus/lgbus_o18_mpro.o
endif

ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/m19/lgbus/lgbus_m19.o
kdrv_lgbus-objs		+= ../../chip/m19/lgbus/lgbus_m19_mpro.o
endif

ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/o20/lgbus/lgbus_o20.o
kdrv_lgbus-objs		+= ../../chip/o20/lgbus/lgbus_o20_mpro.o
endif

ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/e60/lgbus/lgbus_e60.o
kdrv_lgbus-objs		+= ../../chip/e60/lgbus/lgbus_e60_mpro.o
endif

ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/o22/lgbus/lgbus_o22.o
kdrv_lgbus-objs		+= ../../chip/o22/lgbus/lgbus_o22_mpro.o
endif

ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/m23/lgbus/lgbus_m23.o
kdrv_lgbus-objs		+= ../../chip/m23/lgbus/lgbus_m23_mpro.o
endif

ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/o24/lgbus/lgbus_o24.o
kdrv_lgbus-objs		+= ../../chip/o24/lgbus/lgbus_o24_mpro.o
endif

ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_lgbus-objs		+= ../../chip/o26/lgbus/lgbus_o26.o
kdrv_lgbus-objs		+= ../../chip/o26/lgbus/lgbus_o26_mpro.o
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_lgbus-CFLAGS	+=
kdrv_lgbus-CFLAGS	+=
kdrv_lgbus-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_lgbus-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(lgbus_MODULE)/,$(kdrv_lgbus-objs))
else
obj-m				:= kdrv_lgbus.o
endif
