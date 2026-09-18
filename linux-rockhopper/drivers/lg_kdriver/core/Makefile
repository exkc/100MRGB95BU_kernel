# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

#
#   FILE NAME   :   makefile
#   VERSION     :   1.0
#   AUTHOR      :   raxis@lge.com
#   DATE        :   2010/11/17
#   DESCRIPTION :   Makefile for building LG kernel driver
#

ifeq ($(KERNEL_NAME),)
$(error KERNEL_NAME is not defined, please define this variable above )
endif

DIR_INSTALL_DEBUG	?= ./target
KDRV_TOP_DIR		:= $(realpath $(shell pwd))
KDRV_INC_DIR		:= $(realpath $(KDRV_TOP_DIR)/../include)
KDRV_PLT_DIR		:= $(realpath $(KDRV_TOP_DIR)/../platform)
KDRV_CHIP_DIR		:= $(realpath $(KDRV_TOP_DIR)/../chip)

# export core environment variable for each module Makefile
export KDRV_TOP_DIR KDRV_INC_DIR KDRV_PLT_DIR KDRV_CHIP_DIR

# linux kernel arch
export ARCH=arm64

OUT_DIR			?= ./dir_rootfs

# KERNEL_NAME should be defined outside of this makefile
# If you want to fix KERNEL_NAME for test. uncomment the below line
# KERNEL_NAME		?= linux-2.6.33-mvista
KERNEL_DIR		:= $(KDRV_TOP_DIR)/../../linux/$(KERNEL_NAME)

# this flag makes kdriver to be kernel module regardless of kernel configuration
KDRV_MODULE_BUILD 	?= YES

include $(KDRV_TOP_DIR)/modules.mk


all build_kdriver :
ifeq ($(KDRV_MODULE_BUILD), YES)
	$(MAKE) -C $(KERNEL_DIR) M=$(KDRV_TOP_DIR)/.. modules $(if $(KDRV_GEN_BUILD_LOG),|& tee build/compile.log; test $${PIPESTATUS[0]} -eq 0)
	$(if $(KDRV_GEN_BUILD_LOG),./build/log_filter build/logs < build/compile.log,true)

	$(MAKE) -C $(KERNEL_DIR) M=$(KDRV_TOP_DIR)/.. modules_install INSTALL_MOD_PATH=$(OUT_DIR)

	# copy built ko to debug backup directory before strip
	mkdir -p $(DIR_INSTALL_DEBUG)
	cp -Rf $(OUT_DIR)/lib/modules/*/extra/* $(DIR_INSTALL_DEBUG)

	# strip debug symbol...
	for ko in `find $(OUT_DIR)/lib/modules/*/extra/ -name \*.ko`; do \
		echo strip debug. $$ko; \
		$(STRIP) -d $$ko; \
	done;
endif

