
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

#-------------------------------------------------------------------------------#
#										#
#	FILE NAME	:	makefile					#
#	VERSION		:	1.1						#
#	AUTHOR		:	jeongpil.yun (jeongpil.yun@lge.com)		#
#	MODIFIER	:	samin.ryu					#
#	DATE		:	2009.12.30					#
#	MODIFY		:	2021.01.04					#
#	DESCRIPTION	:	Makefile for building demod module		#
#*******************************************************************************#

include $(KDRV_TOP_DIR)/modules.mk

demod_MODULE	:= demod

# DEMOD_CHIP_OPT  [SOC or EXT, IPC, DDR, POLL]
# SOC or EXT : communication interface using APB for SOC or using I2C for External Demod
# IPC : kdriver <-> mcu communication with IPC logic
# DDR : mcu booting using DDR
# POLL : use polling thread instead of interrupt handler when using IPC. if EXT, POLL is default

# PLATFORM_CHIP o20, DEMOD_CHIP o20
# set build option O20, don't have to set DEMOD_CHIP_NAME
# valid combinations
# - SOC (traditional version) / SOC IPC / SOC IPC DDR / SOC IPC POLL / SOC IPC DDR POLL

DEMOD_CHIP_OPT	+= SOC
DEMOD_CHIP_OPT	+= IPC
DEMOD_CHIP_OPT	+= DDR
#DEMOD_CHIP_OPT	+= EXT
#DEMOD_CHIP_OPT	+= POLL

# O22 CPBOX (CROSS PLATFORM)
#DEMOD_CHIP_NAME := o24

# if didn't defined DEMOD_CHIP_NAME, default set according to PLATFORM_CHIP_NAME
ifeq ($(DEMOD_CHIP_NAME),)
DEMOD_CHIP_NAME := $(PLATFORM_CHIP_NAME)
endif

# remove unnecessary spaces of until line end, to upper case
#DEMOD_CHIP_NAME := $(shell echo $(strip $(DEMOD_CHIP_NAME)) | tr a-z A-Z)
# remove unnecessary spaces of until line end
DEMOD_CHIP_NAME := $(strip $(DEMOD_CHIP_NAME))
DEMOD_CHIP_OPT  := $(strip $(DEMOD_CHIP_OPT))

# replace comma to space
comma:= ,
empty:=
space:= $(empty) $(empty)
DEMOD_CHIP_OPT  := $(subst $(comma),$(space),$(DEMOD_CHIP_OPT))
DEMOD_CHIP_OPT  := $(strip $(DEMOD_CHIP_OPT))

# add define chip name for DEMOD
kdrv_demod-CFLAGS := -DDEMOD_CHIP_NAME=$(DEMOD_CHIP_NAME) -DDEMOD_CHIP_NAME_$(DEMOD_CHIP_NAME)

# if different from PLATFORM_CHIP And DEDOD_CHIP, adding config of CROSS_PLATFORM.
ifneq ($(PLATFORM_CHIP_NAME), $(DEMOD_CHIP_NAME))
DEMOD_CHIP_OPT := $(filter-out SOC, $(DEMOD_CHIP_OPT))
DEMOD_CHIP_OPT += CROSS_PLATFORM
DEMOD_CHIP_OPT += EXT
DEMOD_CHIP_OPT += POLL
endif

# if didn't define interface option, set interface as default(SOC)
ifeq ($(findstring EXT, $(DEMOD_CHIP_OPT)),)
ifeq ($(findstring SOC, $(DEMOD_CHIP_OPT)),)
DEMOD_CHIP_OPT += SOC
endif
endif

# not support IPC in M17, L18, O18, M19, remove IPC, DDR
ifneq ($(filter m16p m17 l18 o18 m19, $(DEMOD_CHIP_NAME)),)
DEMOD_CHIP_OPT := $(filter-out IPC DDR, $(DEMOD_CHIP_OPT))
endif

# if set POLL, but didn't set IPC, delete POLL
ifeq ($(findstring POLL, $(DEMOD_CHIP_OPT)), POLL)
ifeq ($(findstring IPC, $(DEMOD_CHIP_OPT)), )
DEMOD_CHIP_OPT := $(filter-out POLL, $(DEMOD_CHIP_OPT))
endif
endif

# if EXT, add POLL
ifeq ($(findstring EXT, $(DEMOD_CHIP_OPT)), EXT)
ifeq ($(findstring POLL, $(DEMOD_CHIP_OPT)),)
DEMOD_CHIP_OPT += POLL
endif
endif

# default demod setting for ipc chip (after o20, ex o20, e60, o22 ..)
INCLUDE_LGDBB_MODULE 		:= YES
INCLUDE_LGDBB_IPC_MODULE	:= YES
INCLUDE_LGDBB_DTMB_MODULE 	:= YES
INCLUDE_LGDBB_L1_TABLE	 	:= NO
INCLUDE_LGDBB_COMMON		:= NO

ifeq ($(DEMOD_CHIP_NAME), o20)
endif
ifeq ($(DEMOD_CHIP_NAME), e60)
endif
ifeq ($(DEMOD_CHIP_NAME), o22)
ifeq ($(PLATFORM_CHIP_TYPE),FPGA)
DEMOD_CHIP_OPT			+= POLL
endif
INCLUDE_LGDBB_L1_TABLE	 	:= YES
endif
ifeq ($(DEMOD_CHIP_NAME), m23)
ifeq ($(PLATFORM_CHIP_TYPE),FPGA)
DEMOD_CHIP_OPT			+= POLL
endif
kdrv_demod-CFLAGS		+= -I$(KDRV_TOP_DIR)/te/include
INCLUDE_LGDBB_L1_TABLE	 	:= YES
endif
ifeq ($(DEMOD_CHIP_NAME), o24)
ifeq ($(PLATFORM_CHIP_TYPE),FPGA)
DEMOD_CHIP_OPT			+= POLL
endif
INCLUDE_LGDBB_COMMON		:= YES
endif

#chungiii fpga ready
ifeq ($(DEMOD_CHIP_NAME), o26)
ifeq ($(PLATFORM_CHIP_TYPE),FPGA)
DEMOD_CHIP_OPT			+= POLL
endif
INCLUDE_LGDBB_COMMON		:= YES
endif


# make DEMOD_CONFIG list
$(foreach opt, $(DEMOD_CHIP_OPT), $(eval DEMOD_CONFIG_$(opt) := YES))
$(foreach opt, $(DEMOD_CHIP_OPT), $(eval kdrv_demod-CFLAGS += -DDEMOD_CONFIG_$(opt)))

# default files (core/demod/)
kdrv_demod-objs		:= demod_cfg.o
kdrv_demod-objs		+= demod_drv.o
kdrv_demod-objs		+= demod_proc.o
kdrv_demod-objs		+= demod_module.o
kdrv_demod-objs		+= demod_hw.o
kdrv_demod-objs		+= demod_util.o

# RPATH is relative path for build (make)
# APATH is absolute path for gcc include
DEMOD_CHIP_RPATH	:= ../../chip/$(DEMOD_CHIP_NAME)/demod
DEMOD_CHIP_APATH	:= $(KDRV_CHIP_DIR)/$(DEMOD_CHIP_NAME)/demod

ifeq ($(INCLUDE_LGDBB_COMMON), YES)
DEMOD_COMM_RPATH	:= common
DEMOD_COMM_APATH	:= $(KDRV_TOP_DIR)/demod/common
else
DEMOD_COMM_RPATH	:= $(DEMOD_CHIP_RPATH)/lgdbb
DEMOD_COMM_APATH	:= $(DEMOD_CHIP_APATH)/lgdbb
endif

#$(info DEMOD build kdrv_top $(KDRV_TOP_DIR), kdrv_chip $(KDRV_CHIP_DIR), demod chip $(DEMOD_CHIP_RPATH), apath $(DEMOD_CHIP_APATH))

# include i2c_core.h
EXTRA_CFLAGS		+= -I$(KDRV_TOP_DIR)/i2c

# DBB
ifeq ($(INCLUDE_LGDBB_MODULE), YES)
kdrv_demod-CFLAGS	+= -I$(DEMOD_CHIP_APATH)
kdrv_demod-CFLAGS	+= -I$(DEMOD_COMM_APATH)
kdrv_demod-CFLAGS	+= -DDEMOD_CONFIG_LGDBB

kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_drv_$(DEMOD_CHIP_NAME).o
kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_common_$(DEMOD_CHIP_NAME).o
kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_dvb_$(DEMOD_CHIP_NAME).o
kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_sat_$(DEMOD_CHIP_NAME).o
kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_vqi_$(DEMOD_CHIP_NAME).o

ifeq ($(INCLUDE_LGDBB_DTMB_MODULE), YES)
kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_dtmb_$(DEMOD_CHIP_NAME).o
endif

kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L0_Connection.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L1_API.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L1_Commands.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L1_Properties.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L2_DVB_API.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L2_Common_API.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L2_ATSC_API.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L2_ISDB_API.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L2_SAT_API.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L2_DTMB_API.o

ifeq ($(INCLUDE_LGDBB_IPC_MODULE), YES)
kdrv_demod-CFLAGS += -DDEMOD_CONFIG_LGDBB_IPC

kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_api_$(DEMOD_CHIP_NAME).o
kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_ipc_$(DEMOD_CHIP_NAME).o
kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_util_$(DEMOD_CHIP_NAME).o
kdrv_demod-objs		+= $(DEMOD_CHIP_RPATH)/demod_fw_$(DEMOD_CHIP_NAME).o

kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L0_CBUF.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L0_CBUF_RAM.o
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L1_IPC.o
endif

ifeq ($(INCLUDE_LGDBB_L1_TABLE), YES)
kdrv_demod-objs		+= $(DEMOD_COMM_RPATH)/DBB_DEMOD_L1_TABLE.o
endif
endif

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_demod-CFLAGS)

#$(info demod build cflgas = $(kdrv_demod-CFLAGS))
#$(info build cflgas = $(EXTRA_CFLAGS))

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(demod_MODULE)/,$(kdrv_demod-objs))
else
obj-m			:= kdrv_demod.o
endif


