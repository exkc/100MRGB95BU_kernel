
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
#	AUTHOR		:	wonsik.do (wonsik.do@lge.com)
#	DATE        :	2009.12.30
#	DESCRIPTION	:	Makefile for building afe module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

afe_MODULE			:= afe

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_afe-objs		:= afe_cfg.o
kdrv_afe-objs		+= afe_drv.o
kdrv_afe-objs		+= afe_proc.o
#kdrv_afe-objs		+= adc_AAD.o
#kdrv_afe-objs           += adc_IBD.o
#kdrv_afe-objs           += adc_IFM.o
#kdrv_afe-objs           += adc_AGOC.o
#kdrv_afe-objs           += adc_control.o
#kdrv_afe-objs           += adc_module.o
#kdrv_afe-objs           += resolution.o
kdrv_afe-objs           += cvd_hal.o
kdrv_afe-objs           += cvd_control.o
kdrv_afe-objs           += cvd_task.o
kdrv_afe-objs           += cvd_module.o
kdrv_afe-objs           += afe_kwrap.o
#kdrv_afe-objs           += v4l2_adc/v4l2_adc.o
kdrv_afe-objs           += v4l2_avd/v4l2_avd.o

ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_afe-objs			+= ../../chip/o26/afe/cvd_hw_o26a0.o	
PE_REG_O26 = $(KDRV_TOP_DIR)/../chip/o26/pe/reg
ifneq ($(wildcard $(PE_REG_O26)),)
EXTRA_CFLAGS += -DINCLUDE_O26_PE_REG
endif
endif 

ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_afe-objs			+= ../../chip/o24/afe/cvd_hw_o24a0.o	
endif

ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_afe-objs			+= ../../chip/m23/afe/cvd_hw_m23a0.o	
endif 

ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_afe-objs			+= ../../chip/o22/afe/cvd_hw_o22a0.o	
endif 

ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
#kdrv_afe-objs			+= ../../chip/e60/afe/adc_hw_e60a0.o	
kdrv_afe-objs			+= ../../chip/e60/afe/cvd_hw_e60a0.o	
endif 

ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
#kdrv_afe-objs			+= ../../chip/o20/afe/adc_hw_o20a0.o	
kdrv_afe-objs			+= ../../chip/o20/afe/cvd_hw_o20a0.o	
endif 

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_afe-CFLAGS	+= -I$(KDRV_TOP_DIR)/pe
#kdrv_afe-CFLAGS	+= -I$(KDRV_TOP_DIR)/pe/common/reg
#kdrv_afe-CFLAGS	+= -I$(KDRV_TOP_DIR)/pe/h15/reg
#kdrv_afe-CFLAGS	+= -I$(KDRV_TOP_DIR)/pe/m16/reg

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_afe-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(afe_MODULE)/,$(kdrv_afe-objs))
else
obj-m				:= kdrv_afe.o
endif
