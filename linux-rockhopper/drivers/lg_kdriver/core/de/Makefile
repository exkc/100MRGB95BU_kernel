
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

de_MODULE			:= de

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_de-objs		:= de_cfg.o
kdrv_de-objs		+= de_drv.o
kdrv_de-objs		+= de_proc.o
kdrv_de-objs		+= de_proc_dbg.o
kdrv_de-objs		+= de_proc_assign.o
kdrv_de-objs		+= de_proc_bin.o
kdrv_de-objs		+= de_proc_disp.o
kdrv_de-objs		+= de_proc_slt.o

kdrv_de-objs		+= de_mem.o
kdrv_de-objs		+= resource_mgr.o
kdrv_de-objs		+= history_mgr.o
#kdrv_de-objs		+= pe_history.o
kdrv_de-objs		+= de_history.o
kdrv_de-objs		+= de_io.o
kdrv_de-objs		+= de_sync.o
kdrv_de-objs		+= hal/de_hal.o
kdrv_de-objs		+= hal/ipc_hal.o
kdrv_de-objs		+= hal/ipc_phys_hal.o
kdrv_de-objs		+=
kdrv_de-objs		+= mcu/mcu_test.o
kdrv_de-objs		+= mcu/io_video.o
kdrv_de-objs		+= mcu/de_fw.o
kdrv_de-objs		+= mcu/de_ipc.o
kdrv_de-objs		+= mcu/de_int.o
kdrv_de-objs		+= mcu/de_dbi.o
kdrv_de-objs		+= vp_kwrap.o
#kdrv_de-objs		+= vp_kwrap_bbd.o
kdrv_de-objs		+= vp_kwrap_hdmi.o
kdrv_de-objs		+= de_kwrap.o
kdrv_de-objs		+= de_kwrap_cap.o
kdrv_de-objs		+= de_kwrap_cvi.o
kdrv_de-objs		+= vsc/hal_vsc_hwrap.o
kdrv_de-objs		+= export_vsc_adapter.o
kdrv_de-objs		+= export_vsc_orbit_adapter.o

#kdrv_de-objs		+= vt/hal_vt_hwrap.o
#kdrv_de-objs		+= vt/vtv_gcp_hwrap.o
#kdrv_de-objs		+= vt/hal_vt_hwrap_debug.o

kdrv_de-objs		+= v4l2_vsc.o
kdrv_de-objs		+= v4l2_vsc_event.o
#kdrv_de-objs		+= v4l2_vsc_bbd.o
kdrv_de-objs		+= vsc_bbd.o
kdrv_de-objs		+= vsc_bwm.o
kdrv_de-objs		+= vsc_fw.o
kdrv_de-objs		+= vsc_wdog.o
kdrv_de-objs		+= vsc_print.o
kdrv_de-objs		+= vsc_util.o
kdrv_de-objs		+= v4l2_vt.o
kdrv_de-objs		+= vb2_gen_memop.o
kdrv_de-objs		+= v4l2_gps.o
kdrv_de-objs		+= v4l2_gps_dbg.o
kdrv_de-objs		+= v4l2_gps_ctrls.o
kdrv_de-objs		+= gps_if.o
kdrv_de-objs		+= v4l2_lg_dev_configs.o
kdrv_de-objs		+= v4l2_dolby_proc.o
kdrv_de-objs		+= v4l2_dolby.o
ifeq ($(USE_VIDEO_UART2_FOR_MCU), YES)
ifneq ($(KDRV_GLOBAL_LINK), YES)
kdrv_de-objs		:= hal/de_hal.o
endif
endif

kdrv_de-objs		+= test/de_test.o
kdrv_de-objs		+= dolby_io.o
kdrv_de-objs		+= hal/dolby_hal.o
kdrv_de-objs		+= cg/vsc_cg.o

ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/o26/de/de_reg_o26.o
kdrv_de-objs		+= ../../chip/o26/de/de_cfg_o26.o
kdrv_de-objs		+= ../../chip/o26/de/de_ipc_o26.o
kdrv_de-objs		+= ../../chip/o26/de/dolby_reg_o26.o
kdrv_de-objs		+= ../../chip/o26/de/de_dosd_o26.o
kdrv_de-objs		+= test/chip/o26/de_test_main_o26.o
kdrv_de-objs		+= test/chip/o26/de_test_check_pqe_o26.o
kdrv_de-objs		+= test/chip/o26/de_test_check_vsc_o26.o
kdrv_de-objs		+= test/chip/o26/de_test_check_gps_o26.o
kdrv_de-objs		+= test/chip/o26/de_test_check_cap_o26.o
kdrv_de-objs		+= test/chip/o26/util/de_test_util_o26.o
kdrv_de-objs		+= cg/o26/vsc_cg_o26.o
endif
ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/o24/de/de_reg_o24.o
kdrv_de-objs		+= ../../chip/o24/de/de_cfg_o24.o
kdrv_de-objs		+= ../../chip/o24/de/de_ipc_o24.o
kdrv_de-objs		+= ../../chip/o24/de/dolby_reg_o24.o
kdrv_de-objs		+= ../../chip/o24/de/de_dosd_o24.o
kdrv_de-objs		+= test/chip/o24/de_test_main_o24.o
kdrv_de-objs		+= test/chip/o24/de_test_check_pqe_o24.o
kdrv_de-objs		+= test/chip/o24/de_test_check_vsc_o24.o
kdrv_de-objs		+= test/chip/o24/de_test_check_gps_o24.o
kdrv_de-objs		+= test/chip/o24/de_test_check_cap_o24.o
kdrv_de-objs		+= test/chip/o24/util/de_test_util_o24.o
kdrv_de-objs		+= cg/o24/vsc_cg_o24.o
endif
ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/m23/de/de_reg_m23.o
kdrv_de-objs		+= ../../chip/m23/de/de_cfg_m23.o
kdrv_de-objs		+= ../../chip/m23/de/de_fw_m23.o
kdrv_de-objs		+= ../../chip/m23/de/de_ipc_m23.o
kdrv_de-objs		+= test/chip/m23/de_test_m23.o
endif
ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/o22/de/de_reg_o22.o
kdrv_de-objs		+= ../../chip/o22/de/de_cfg_o22.o
kdrv_de-objs		+= ../../chip/o22/de/de_prm_o22.o
kdrv_de-objs		+= ../../chip/o22/de/de_fw_o22.o
kdrv_de-objs		+= ../../chip/o22/de/de_ipc_o22.o
kdrv_de-objs		+= ../../chip/o22/de/de_init_o22.o
kdrv_de-objs		+= ../../chip/o22/de/dolby_reg_o22.o
kdrv_de-objs		+= test/chip/o22/de_test_o22.o
endif
ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/o20/de/de_reg_o20.o
kdrv_de-objs		+= ../../chip/o20/de/de_cfg_o20.o
kdrv_de-objs		+= ../../chip/o20/de/de_prm_o20.o
kdrv_de-objs		+= ../../chip/o20/de/de_fw_o20.o
kdrv_de-objs		+= ../../chip/o20/de/de_ipc_o20.o
kdrv_de-objs		+= ../../chip/o20/de/de_init_o20.o
kdrv_de-objs  	+= ../../chip/o20/de/dolby_reg_o20.o
endif
ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/e60/de/de_reg_e60.o
kdrv_de-objs		+= ../../chip/e60/de/de_prm_e60.o
kdrv_de-objs		+= ../../chip/e60/de/de_fw_e60.o
kdrv_de-objs		+= ../../chip/e60/de/de_ipc_e60.o
kdrv_de-objs		+= ../../chip/e60/de/de_init_e60.o
kdrv_de-objs  	+= ../../chip/e60/de/dolby_reg_e60.o
endif
ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/o18/de/de_reg_o18.o
kdrv_de-objs		+= ../../chip/o18/de/de_prm_o18.o
kdrv_de-objs		+= ../../chip/o18/de/de_fw_o18.o
kdrv_de-objs		+= ../../chip/o18/de/de_ipc_o18.o
kdrv_de-objs		+= ../../chip/o18/de/de_init_o18.o
kdrv_de-objs  	+= ../../chip/o18/de/dolby_reg_o18.o
endif
ifeq ($(INCLUDE_L18_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/l18/de/de_reg_l18.o
kdrv_de-objs		+= ../../chip/l18/de/de_prm_l18.o
kdrv_de-objs		+= ../../chip/l18/de/de_fw_l18.o
kdrv_de-objs		+= ../../chip/l18/de/de_ipc_l18.o
kdrv_de-objs		+= ../../chip/l18/de/de_init_l18.o
endif
ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/m17/de/de_reg_m17.o
kdrv_de-objs		+= ../../chip/m17/de/de_prm_m17.o
kdrv_de-objs		+= ../../chip/m17/de/de_fw_m17.o
kdrv_de-objs		+= ../../chip/m17/de/de_ipc_m17.o
kdrv_de-objs		+= ../../chip/m17/de/de_init_m17.o
kdrv_de-objs  	+= ../../chip/m17/de/dolby_reg_m17.o
endif
ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_de-objs		+= ../../chip/m19/de/de_reg_m19.o
kdrv_de-objs		+= ../../chip/m19/de/de_prm_m19.o
kdrv_de-objs		+= ../../chip/m19/de/de_fw_m19.o
kdrv_de-objs		+= ../../chip/m19/de/de_ipc_m19.o
kdrv_de-objs		+= ../../chip/m19/de/de_init_m19.o
kdrv_de-objs  	+= ../../chip/m19/de/dolby_reg_m19.o
endif


#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_de-CFLAGS	+= -I$(KDRV_TOP_DIR)/de/hal/
kdrv_de-CFLAGS	+= -I$(KDRV_TOP_DIR)/chip/
kdrv_de-CFLAGS  += -I$(KDRV_TOP_DIR)/pe/
kdrv_de-CFLAGS  += -I$(KDRV_TOP_DIR)/afe/
kdrv_de-CFLAGS	+= -I$(KDRV_TOP_DIR)/se/
kdrv_de-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_de-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(de_MODULE)/,$(kdrv_de-objs))
else
obj-m				:= kdrv_de.o
endif
