#******************************************************************************#
#	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
#	Copyright(c) 2013 by LG Electronics Inc.
#
#	This program is free software; you can redistribute it and/or
#	modify it under the terms of the GNU General Public License
#	version 2 as published by the Free Software Foundation.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#	GNU General Public License for more details.
#******************************************************************************#

KDRV_TOP_DIR	:= $(shell pwd)

ifneq ($(AARCH_DRV),aarch64_drv)
KERNEL_DIR 	:= $(KDRV_TOP_DIR)/../../../linux/linux-lg1k-4.4
else
KERNEL_DIR	:= $(KDRV_TOP_DIR)/../../../linux/linux-lg1k
endif

se_MODULE		:= se

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_se-objs			:= se_cfg.o
kdrv_se-objs			+= se_drv.o
kdrv_se-objs			+= se_proc.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_se-CFLAGS	+=
kdrv_se-CFLAGS	+= -D_SE_STANDALONE_

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_se-CFLAGS)

obj-m				:= kdrv_se.o

ifneq ($(AARCH_DRV),aarch64_drv)
module :
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules ARCH=arm
else
module :
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules ARCH=arm64
endif

clean :
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
	rm -rf *.order
	rm -rf *.symvers
	rm -rf *.tmp_versions

