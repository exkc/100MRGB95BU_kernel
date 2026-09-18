#
# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#


#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------

ifeq ($(KDRV_INC_DIR),)
	$(error KDRV_INC_DIR is empty)
endif

ifeq ($(TE_EMULATOR_DIR),)
	$(error TE_EMULATOR_DIR is empty)
endif

kdrv_src	:= $(shell cd $(src)/../ && pwd)
mcu_src		:= $(shell rm -f $(src)/src && \
				ln -sf $(TE_EMULATOR_DIR) $(src)/src && \
				cd $(src)/src && pwd)

obj-m			+= te_mcu_emul.o

te_mcu_emul-y	:= driver.o
te_mcu_emul-y	+= proc.o
te_mcu_emul-y	+= src/main.o
te_mcu_emul-y	+= src/isr.o
te_mcu_emul-y	+= src/ipc.o
te_mcu_emul-y	+= src/dsc.o
te_mcu_emul-y	+= src/fe_engine.o
te_mcu_emul-y	+= src/ciplus.o
te_mcu_emul-y	+= src/debug.o
te_mcu_emul-y	+= src/atsc3.o
te_mcu_emul-y	+= src/bb_frame.o
te_mcu_emul-y	+= src/alp.o
te_mcu_emul-y	+= src/ipudp.o
te_mcu_emul-y	+= src/route.o
te_mcu_emul-y	+= src/mmt.o

ccflags-y	:= -I$(kdrv_src) -I$(src) -I$(src)/include -I$(KDRV_INC_DIR) -D_EMULATOR_

