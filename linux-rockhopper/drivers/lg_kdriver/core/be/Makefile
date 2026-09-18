
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
#	AUTHOR		:	justine.jeong@lge.com
#	DATE		:	2012.02.13
#	DESCRIPTION	:	Makefile for building be module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

be_MODULE			:= be


#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_be-objs		:= be_drv.o
kdrv_be-objs		+= be_cfg.o
kdrv_be-objs		+= be_proc.o

kdrv_be-objs		+= top/be_top_drv.o
kdrv_be-objs		+= top/be_top_hal.o
kdrv_be-objs		+= reg/be_reg.o
kdrv_be-objs		+= fwi/fwl_drv.o
kdrv_be-objs		+= fwi/fwl_hal.o
kdrv_be-objs		+= fwi/ipc_drv.o
kdrv_be-objs		+= fwi/ipc_hal.o
kdrv_be-objs		+= fwi/int_drv.o
kdrv_be-objs		+= fwi/int_hal.o
kdrv_be-objs		+= led/led_drv.o
kdrv_be-objs		+= led/led_hal.o
kdrv_be-objs		+= frc/frc_drv.o
kdrv_be-objs		+= frc/frc_hal.o

kdrv_be-objs		+= h3d/h3d_drv.o
kdrv_be-objs		+= h3d/h3d_hal.o
kdrv_be-objs		+= pwm/pwm_drv.o
kdrv_be-objs		+= pwm/pwm_hal.o

kdrv_be-objs		+= fwi/mcu/mcu_ipc_test.o
kdrv_be-objs		+= video_status_keeper.o

kdrv_be-objs		+= v4l2_vbe.o
kdrv_be-objs		+= vbe_event.o
kdrv_be-objs		+= vbe_dpc.o
kdrv_be-objs		+= vbe_dpc_algo.o

ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/m17/be/top/be_top_hw_m17.o
kdrv_be-objs		+= ../../chip/m17/be/frc/be_frc_hw_m17.o
kdrv_be-objs		+= ../../chip/m17/be/led/be_led_hw_m17.o
kdrv_be-objs		+= ../../chip/m17/be/h3d/be_h3d_hw_m17.o
kdrv_be-objs		+= ../../chip/m17/be/fwi/be_fwl_hw_m17.o
kdrv_be-objs		+= ../../chip/m17/be/fwi/be_ipc_hw_m17.o
kdrv_be-objs		+= ../../chip/m17/be/fwi/be_int_hw_m17.o
kdrv_be-objs		+= ../../chip/m17/be/pwm/be_pwm_hw_m17.o
kdrv_be-objs		+= ../../chip/m17/be/reg/be_reg_hw_m17.o
endif
ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/o18/be/top/be_top_hw_o18.o
kdrv_be-objs		+= ../../chip/o18/be/frc/be_frc_hw_o18.o
kdrv_be-objs		+= ../../chip/o18/be/led/be_led_hw_o18.o
kdrv_be-objs		+= ../../chip/o18/be/fwi/be_fwl_hw_o18.o
kdrv_be-objs		+= ../../chip/o18/be/fwi/be_ipc_hw_o18.o
kdrv_be-objs		+= ../../chip/o18/be/fwi/be_int_hw_o18.o
kdrv_be-objs		+= ../../chip/o18/be/pwm/be_pwm_hw_o18.o
kdrv_be-objs		+= ../../chip/o18/be/reg/be_reg_hw_o18.o
endif
ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/m19/be/top/be_top_hw_m19.o
kdrv_be-objs		+= ../../chip/m19/be/frc/be_frc_hw_m19.o
kdrv_be-objs		+= ../../chip/m19/be/led/be_led_hw_m19.o
kdrv_be-objs		+= ../../chip/m19/be/h3d/be_h3d_hw_m19.o
kdrv_be-objs		+= ../../chip/m19/be/fwi/be_fwl_hw_m19.o
kdrv_be-objs		+= ../../chip/m19/be/fwi/be_ipc_hw_m19.o
kdrv_be-objs		+= ../../chip/m19/be/fwi/be_int_hw_m19.o
kdrv_be-objs		+= ../../chip/m19/be/pwm/be_pwm_hw_m19.o
kdrv_be-objs		+= ../../chip/m19/be/reg/be_reg_hw_m19.o
endif
ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/o20/be/top/be_top_hw_o20.o
kdrv_be-objs		+= ../../chip/o20/be/frc/be_frc_hw_o20.o
kdrv_be-objs		+= ../../chip/o20/be/led/be_led_hw_o20.o
kdrv_be-objs		+= ../../chip/o20/be/fwi/be_fwl_hw_o20.o
kdrv_be-objs		+= ../../chip/o20/be/fwi/be_ipc_hw_o20.o
kdrv_be-objs		+= ../../chip/o20/be/fwi/be_int_hw_o20.o
kdrv_be-objs		+= ../../chip/o20/be/pwm/be_pwm_hw_o20.o
kdrv_be-objs		+= ../../chip/o20/be/reg/be_reg_hw_o20.o
endif
ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/e60/be/top/be_top_hw_e60.o
kdrv_be-objs		+= ../../chip/e60/be/frc/be_frc_hw_e60.o
kdrv_be-objs		+= ../../chip/e60/be/led/be_led_hw_e60.o
kdrv_be-objs		+= ../../chip/e60/be/fwi/be_fwl_hw_e60.o
kdrv_be-objs		+= ../../chip/e60/be/fwi/be_ipc_hw_e60.o
kdrv_be-objs		+= ../../chip/e60/be/fwi/be_int_hw_e60.o
kdrv_be-objs		+= ../../chip/e60/be/pwm/be_pwm_hw_e60.o
kdrv_be-objs		+= ../../chip/e60/be/reg/be_reg_hw_e60.o
endif
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/o22/be/top/be_top_hw_o22.o
kdrv_be-objs		+= ../../chip/o22/be/frc/be_frc_hw_o22.o
kdrv_be-objs		+= ../../chip/o22/be/led/be_led_hw_o22.o
kdrv_be-objs		+= ../../chip/o22/be/fwi/be_fwl_hw_o22.o
kdrv_be-objs		+= ../../chip/o22/be/fwi/be_ipc_hw_o22.o
kdrv_be-objs		+= ../../chip/o22/be/fwi/be_int_hw_o22.o
kdrv_be-objs		+= ../../chip/o22/be/pwm/be_pwm_hw_o22.o
kdrv_be-objs		+= ../../chip/o22/be/reg/be_reg_hw_o22.o
endif
ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/m23/be/top/be_top_hw_m23.o
kdrv_be-objs		+= ../../chip/m23/be/frc/be_frc_hw_m23.o
kdrv_be-objs		+= ../../chip/m23/be/led/be_led_hw_m23.o
kdrv_be-objs		+= ../../chip/m23/be/fwi/be_fwl_hw_m23.o
kdrv_be-objs		+= ../../chip/m23/be/fwi/be_ipc_hw_m23.o
kdrv_be-objs		+= ../../chip/m23/be/fwi/be_int_hw_m23.o
kdrv_be-objs		+= ../../chip/m23/be/pwm/be_pwm_hw_m23.o
kdrv_be-objs		+= ../../chip/m23/be/reg/be_reg_hw_m23.o
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/o24/be/top/be_top_hw_o24.o
kdrv_be-objs		+= ../../chip/o24/be/frc/be_frc_hw_o24.o
kdrv_be-objs		+= ../../chip/o24/be/led/be_led_hw_o24.o
kdrv_be-objs		+= ../../chip/o24/be/fwi/be_fwl_hw_o24.o
kdrv_be-objs		+= ../../chip/o24/be/fwi/be_ipc_hw_o24.o
kdrv_be-objs		+= ../../chip/o24/be/fwi/be_int_hw_o24.o
kdrv_be-objs		+= ../../chip/o24/be/pwm/be_pwm_hw_o24.o
kdrv_be-objs		+= ../../chip/o24/be/reg/be_reg_hw_o24.o
endif
ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_be-objs		+= ../../chip/o26/be/top/be_top_hw_o26.o
kdrv_be-objs		+= ../../chip/o26/be/frc/be_frc_hw_o26.o
kdrv_be-objs		+= ../../chip/o26/be/led/be_led_hw_o26.o
kdrv_be-objs		+= ../../chip/o26/be/fwi/be_fwl_hw_o26.o
kdrv_be-objs		+= ../../chip/o26/be/fwi/be_ipc_hw_o26.o
kdrv_be-objs		+= ../../chip/o26/be/fwi/be_int_hw_o26.o
kdrv_be-objs		+= ../../chip/o26/be/pwm/be_pwm_hw_o26.o
kdrv_be-objs		+= ../../chip/o26/be/reg/be_reg_hw_o26.o
endif

#------------------------------------------------------------------------------
# REVISION maker using MD5
# -----------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/top
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/reg
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/fwi
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/h3d
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/frc
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/led
kdrv_be-CFLAGS   += -I$(KDRV_TOP_DIR)/be/pwm

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_be-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(be_MODULE)/,$(kdrv_be-objs))
else
obj-m				:= kdrv_be.o
endif

