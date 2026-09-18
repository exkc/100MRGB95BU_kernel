#*******************************************************************************#
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA			      	#
#  Copyright(c) 2013 by LG Electronics Inc.					#
# 										#
#  This program is free software; you can redistribute it and/or		#
#  modify it under the terms of the GNU General Public License			#
#  version 2 as published by the Free Software Foundation.			#
# 										#
#  This program is distributed in the hope that it will be useful,		#
#  but WITHOUT ANY WARRANTY; without even the implied warranty of		#
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the		#
#  GNU General Public License for more details.					#
#*******************************************************************************#  

#******************************************************************************#
#   ---------------------------------------------------------------------------#
#                                                                              #
#	FILE NAME	:	makefile                                                   #
#	VERSION		:	1.0                                                        #
#	AUTHOR		:	ingyu.yang (ingyu.yang@lge.com)
#	DATE        :	2009.12.30
#	DESCRIPTION	:	Makefile for building gpio module                      #
#******************************************************************************#
include $(KDRV_TOP_DIR)/modules.mk

spi_MODULE			:= spi

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_spi-objs		+= spi_drv.o
kdrv_spi-objs		+= spi_proc.o
#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_spi-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_spi-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(spi_MODULE)/,$(kdrv_spi-objs))
else
obj-m				:= kdrv_spi.o
endif
