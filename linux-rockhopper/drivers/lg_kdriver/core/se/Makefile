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

ifeq ($(SE_STANDALONE_MAKEFILE), )

include $(KDRV_TOP_DIR)/modules.mk

se_MODULE			:= se

#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------
kdrv_se-objs			:= se_cfg.o
kdrv_se-objs			+= ree_kdrv.o
kdrv_se-objs			+= se_drv.o
kdrv_se-objs			+= se_proc.o
kdrv_se-objs			+= dmabuf_importer.o

#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_se-CFLAGS	+=
kdrv_se-CFLAGS	+=
kdrv_se-CFLAGS	+=

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_se-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(se_MODULE)/,$(kdrv_se-objs))
else
obj-m				:= kdrv_se.o
endif

else	#SE_STANDALONE_MAKEFILE

include $(SE_STANDALONE_MAKEFILE)

endif	#SE_STANDALONE_MAKEFILE

