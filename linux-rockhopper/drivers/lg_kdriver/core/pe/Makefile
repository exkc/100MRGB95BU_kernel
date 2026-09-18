# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or 
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
# GNU General Public License for more details.
 

#------------------------------------------------------------------------------#
#                                                                              #
#	FILE NAME	:	makefile                                                   #
#	VERSION		:	1.0                                                        #
#	AUTHOR		:	sj.youm (sj.youm@lge.oom)                                  #
#	DATE		:	2011.06.22                                                 #
#	DESCRIPTION	:	Makefile for building pe module                            #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

pe_MODULE			:= pe

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_pe-objs		:= pe_cfg.o
kdrv_pe-objs		+= pe_drv.o
kdrv_pe-objs		+= reg/pe_reg.o
kdrv_pe-objs		+= pe_io.o
kdrv_pe-objs		+= pe_proc.o
kdrv_pe-objs		+= pe_proc_dbg.o
kdrv_pe-objs		+= pe_proc_hdr.o
kdrv_pe-objs		+= pe_hal.o
kdrv_pe-objs		+= pe_cmg.o
kdrv_pe-objs		+= pe_cmn.o
kdrv_pe-objs		+= pe_csc.o
kdrv_pe-objs		+= pe_dcm.o
kdrv_pe-objs		+= pe_dnt.o
kdrv_pe-objs		+= pe_nrd.o
kdrv_pe-objs		+= pe_shp.o
kdrv_pe-objs		+= pe_win.o
kdrv_pe-objs		+= pe_spd.o
kdrv_pe-objs		+= pe_etc.o
kdrv_pe-objs		+= pe_hst.o
kdrv_pe-objs		+= pe_hdr.o
kdrv_pe-objs		+= pe_kwrap.o
kdrv_pe-objs		+= pe_kwrap_cmg.o
kdrv_pe-objs		+= pe_kwrap_cmn.o
kdrv_pe-objs		+= pe_kwrap_csc.o
kdrv_pe-objs		+= pe_kwrap_dcm.o
kdrv_pe-objs		+= pe_kwrap_dnt.o
kdrv_pe-objs		+= pe_kwrap_hst.o
kdrv_pe-objs		+= pe_kwrap_nrd.o
kdrv_pe-objs		+= pe_kwrap_shp_ren.o
kdrv_pe-objs		+= pe_kwrap_shp_sre.o
kdrv_pe-objs		+= v4l2_vpq.o
kdrv_pe-objs		+= v4l2_vpq_cmn.o
kdrv_pe-objs		+= v4l2_vpq_be.o
kdrv_pe-objs		+= v4l2_vpq_hdr.o
kdrv_pe-objs		+= v4l2_vpq_pe.o
kdrv_pe-objs		+= vpq_hwrap.o
kdrv_pe-objs		+= vpq_hwrap_be.o
kdrv_pe-objs		+= vpq_hwrap_hdr.o
kdrv_pe-objs		+= vpq_hwrap_pe.o
kdrv_pe-objs		+= vpq_proc.o
kdrv_pe-objs		+= v4l2_lgsr.o
kdrv_pe-objs		+= v4l2_vpq_latency.o
kdrv_pe-objs		+= test/pe_test.o

ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/m17/pe/reg/pe_reg_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_cmn_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_cmg_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_csc_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_dcm_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_nrd_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_dnt_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_shp_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_fwi_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_tsk_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_inf_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_win_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_hst_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_hdr_hw_m17.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_cmn_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_ccm_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_cmg_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_csc_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_dcm_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_nrd_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_dnt_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_shp_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_fwi_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_tsk_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_inf_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_win_hw_m17c0.o
kdrv_pe-objs		+= ../../chip/m17/pe/pe_hst_hw_m17c0.o
endif

ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/m19/pe/reg/pe_reg_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_cmn_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_cmg_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_csc_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_dcm_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_nrd_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_dnt_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_shp_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_fwi_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_tsk_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_inf_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_win_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_hst_hw_m19.o
kdrv_pe-objs		+= ../../chip/m19/pe/pe_hdr_hw_m19.o
endif

ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/o18/pe/reg/pe_reg_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_cmn_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_cmg_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_csc_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_dcm_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_nrd_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_dnt_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_shp_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_fwi_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_tsk_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_inf_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_win_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_hst_hw_o18.o
kdrv_pe-objs		+= ../../chip/o18/pe/pe_hdr_hw_o18.o
endif

ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/o20/pe/reg/pe_reg_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_cmn_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_cmg_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_csc_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_dcm_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_nrd_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_dnt_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_shp_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_fwi_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_tsk_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_inf_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_win_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_hst_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_hdr_hw_o20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_chpi_shp_hw_f20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_chpi_obc_hw_f20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_chpi_tnr_hw_f20.o
kdrv_pe-objs		+= ../../chip/o20/pe/pe_chpi_dnr_hw_f20.o
endif

ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/e60/pe/reg/pe_reg_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_cmn_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_cmg_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_csc_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_dcm_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_nrd_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_dnt_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_shp_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_fwi_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_tsk_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_inf_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_win_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_hst_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_hdr_hw_e60.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_chpi_shp_hw_e60f20.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_chpi_obc_hw_e60f20.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_chpi_tnr_hw_e60f20.o
kdrv_pe-objs		+= ../../chip/e60/pe/pe_chpi_dnr_hw_e60f20.o
endif

ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/o22/pe/reg/pe_reg_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_cmn_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_cmg_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_csc_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_dcm_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_nrd_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_dnt_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_shp_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_fwi_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_tsk_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_inf_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_win_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_hst_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_hdr_hw_o22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_chpi_shp_hw_o22f22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_chpi_obc_hw_o22f22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_chpi_tnr_hw_o22f22.o
kdrv_pe-objs		+= ../../chip/o22/pe/pe_chpi_dnr_hw_o22f22.o
endif

ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/m23/pe/reg/pe_reg_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_cmn_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_cmg_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_csc_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_dcm_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_nrd_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_dnt_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_shp_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_fwi_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_tsk_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_inf_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_win_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_hst_hw_m23.o
kdrv_pe-objs		+= ../../chip/m23/pe/pe_hdr_hw_m23.o
endif

ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/o24/pe/reg/pe_reg_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_cmn_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_cmg_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_csc_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_dcm_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_nrd_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_dnt_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_shp_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_fwi_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_tsk_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_inf_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_win_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_hst_hw_o24.o
kdrv_pe-objs		+= ../../chip/o24/pe/pe_hdr_hw_o24.o
#kdrv_pe-objs		+= ../../chip/o24/pe/pe_chpi_shp_hw_o24f22.o
#kdrv_pe-objs		+= ../../chip/o24/pe/pe_chpi_obc_hw_o24f22.o
#kdrv_pe-objs		+= ../../chip/o24/pe/pe_chpi_tnr_hw_o24f22.o
#kdrv_pe-objs		+= ../../chip/o24/pe/pe_chpi_dnr_hw_o24f22.o
kdrv_pe-objs		+= test/chip/o24/pe_test_main_o24.o
kdrv_pe-objs		+= test/chip/o24/pe_test_check_vpq_o24.o
kdrv_pe-objs		+= test/chip/o24/pe_test_check_hdr_o24.o
kdrv_pe-objs		+= test/chip/o24/pe_test_check_vbe_o24.o
kdrv_pe-objs		+= test/chip/o24/pe_test_check_dov_o24.o
endif

ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_pe-objs		+= ../../chip/o26/pe/reg/pe_reg_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_cmn_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_cmg_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_csc_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_dcm_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_nrd_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_dnt_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_shp_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_fwi_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_tsk_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_inf_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_win_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_hst_hw_o26.o
kdrv_pe-objs		+= ../../chip/o26/pe/pe_hdr_hw_o26.o
kdrv_pe-objs		+= test/chip/o26/pe_test_main_o26.o
kdrv_pe-objs		+= test/chip/o26/pe_test_check_vpq_o26.o
kdrv_pe-objs		+= test/chip/o26/pe_test_check_hdr_o26.o
kdrv_pe-objs		+= test/chip/o26/pe_test_check_vbe_o26.o
kdrv_pe-objs		+= test/chip/o26/pe_test_check_dov_o26.o
endif

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/afe
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/de
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/be
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/be/fwi
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/be/top
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/be/frc
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/be/led
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/be/pwm
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/ovi
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/hw_param/lgsr
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/hw_param/drc
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/hw_param/scl
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/hw_param/scl/p032
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/pe/hw_param/scl/p256

ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m17/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/m17/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/m17/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m17/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m17/pe/hw_param/m17a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m17/pe/hw_param/m17c0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m17/afe
endif

ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m19/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/m19/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/m19/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m19/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m19/pe/hw_param/m19a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m19/afe
endif

ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o18/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o18/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o18/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o18/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o18/pe/hw_param/o18a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o18/afe
endif

ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o20/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o20/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o20/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o20/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o20/pe/hw_param/o20a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o20/pe/hw_param/f20a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o20/afe
endif

ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/e60/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/e60/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/e60/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/e60/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/e60/pe/hw_param/e60a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/e60/pe/hw_param/e60f20a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/e60/afe
endif

ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o22/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o22/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o22/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o22/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o22/pe/hw_param/o22a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o22/pe/hw_param/o22f22a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o22/afe
endif

ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m23/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/m23/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/m23/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m23/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m23/pe/hw_param/m23a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/m23/afe
endif

ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o24/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o24/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o24/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o24/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o24/pe/hw_param/o24a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o24/pe/hw_param/o24f22a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o24/afe
endif

ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o26/de
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o26/pe
kdrv_pe-CFLAGS	 += -I$(KDRV_TOP_DIR)/../chip/o26/pe/reg
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o26/pe/hw_param
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o26/pe/hw_param/o26a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o26/pe/hw_param/o26f22a0
kdrv_pe-CFLAGS   += -I$(KDRV_TOP_DIR)/../chip/o26/afe
endif

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_pe-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(pe_MODULE)/,$(kdrv_pe-objs))
else
obj-m				:= kdrv_pe.o
endif
