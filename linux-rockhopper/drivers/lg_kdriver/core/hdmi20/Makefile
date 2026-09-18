
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
#	AUTHOR		:	won.hur (won.hur@lge.com)
#	DATE        :	2012.04.18                                                 
#	DESCRIPTION	:	Makefile for building HDMI20 module                        #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

hdmi20_MODULE			:= hdmi20

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_hdmi20-objs		:= hdmi20_cfg.o
kdrv_hdmi20-objs		+= hdmi20_drv.o
kdrv_hdmi20-objs		+= hdmi20_module.o
kdrv_hdmi20-objs		+= hdmi20_proc.o

kdrv_hdmi20-objs		+= ./hdmi20_engine/synopsys_api/hdmi_rx_ctrl_hdcp.o
kdrv_hdmi20-objs		+= ./hdmi20_engine/synopsys_api/hdmi_rx_ctrl.o

kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_hal_driver.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_disland.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_irq.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_misc.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_phy.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_deframer.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_frl.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_hdcp.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_isrunit.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_misc.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_pdec.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_pextract.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_pfifo.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_scdc.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_vmon.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_vpgen.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_snps_vproc.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_audio.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_audio_path_i2s.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_audio_path_spdif.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_earc_driver.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_dsc.o
kdrv_hdmi20-objs		+= ./hdmi21_engine/hdmi21_rx_ddcmon.o

kdrv_hdmi20-objs		+= ../../chip/o20/hdmi20/hdmi21_rx_phy_o20a0.o
kdrv_hdmi20-objs		+= ../../chip/o20/hdmi20/hdmi21_rx_phy_o20b0.o
kdrv_hdmi20-objs		+= ../../chip/o20/hdmi20/hdmi21_earc_phy_o20.o

kdrv_hdmi20-objs		+= ../../chip/e60/hdmi20/hdmi21_rx_phy_e60a0.o
kdrv_hdmi20-objs		+= ../../chip/e60/hdmi20/hdmi21_rx_phy_e60b0.o

kdrv_hdmi20-objs		+= ../../chip/o22/hdmi20/hdmi21_rx_phy_o22a0.o
kdrv_hdmi20-objs		+= ../../chip/o22/hdmi20/o22a0_reg_table.o

kdrv_hdmi20-objs		+= ../../chip/m23/hdmi20/hdmi21_rx_phy_m23a0.o
kdrv_hdmi20-objs		+= ../../chip/m23/hdmi20/m23a0_reg_table.o

kdrv_hdmi20-objs		+= ../../chip/o24/hdmi20/hdmi21_rx_phy_o24a0.o
kdrv_hdmi20-objs		+= ../../chip/o24/hdmi20/o24a0_reg_table.o

kdrv_hdmi20-objs		+= ../../chip/o26/hdmi20/hdmi21_rx_phy_o26a0.o
kdrv_hdmi20-objs		+= ../../chip/o26/hdmi20/o26a0_reg_table.o

kdrv_hdmi20-objs		+= hdmi20_kwarp.o
kdrv_hdmi20-objs 		+= ./v4l2_hdmi20/v4l2_hdmi20.o
kdrv_hdmi20-objs 		+= ./v4l2_earc/v4l2_earc.o

kdrv_hdmi20-objs		+= ./hdmicec/hdmicec_drv.o
#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
# to enable hw cec 
kdrv_hdmi20-CFLAGS	+= -DENABLE_HDMI_CEC

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_hdmi20-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(hdmi20_MODULE)/,$(kdrv_hdmi20-objs))
else
obj-m				:= kdrv_hdmi20.o
endif
