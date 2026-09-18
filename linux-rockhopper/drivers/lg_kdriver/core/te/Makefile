#
# SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2025 by LG Electronics Inc.
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

include $(KDRV_TOP_DIR)/modules.mk

te_module		:= te
#-------------------------------------------------------------------------------
# TODO: define your driver source file
#-------------------------------------------------------------------------------

te_sub_modules		:=
te-CFLAGS		:=

te_core-objs		:=
te_core-objs		+= te_cfg.o
te_core-objs		+= te_drv.o
te_core-objs		+= te_core.o
te_core-objs		+= te_device.o
te_core-objs		+= te_interrupt.o
te_core-objs		+= te_ioctl.o
te_core-objs		+= te_debug.o
te_core-objs		+= te_timer.o
te_core-objs		+= te_util.o
te_core-objs		+= te_debug_util.o
te_core-objs		+= te_buffer.o
te_core-objs		+= te_mem.o
te_core-objs		+= te_io.o
te_core-objs		+= te_clock.o
te_core-objs		+= te_dump.o
te_core-objs		+= te_dumper.o
te_core-objs		+= te_clockgate.o

ifeq ($(INCLUDE_KDRV_ION),YES)
ifeq ($(PLATFORM_CHIP_NAME), o24)
te-CFLAGS	+= -DCONFIG_ION_MASTER_SLAVE
te_core-objs	+= ion/ion_ci_reg_slave.o
te_core-objs	+= ion/ion_io_reg_slave.o
endif
te_core-objs	+= ion/ion_drv.o
te_core-objs	+= ion/ion_spi.o
te_core-objs	+= ion/ion_ci_reg.o
te_core-objs	+= ion/ion_io_reg.o
te_core-objs	+= ion/ion_debug.o
te-CFLAGS	+= -DCONFIG_TE_ION
te-CFLAGS	+= -I$(KDRV_TOP_DIR)/spi/
endif


CONFIG_TE_MCU_VERIFY	:= y
te_sub_modules		+= mcu
te_mcu-objs		+= mcu/te_mcu.o
te_mcu-objs		+= mcu/ipc/te_ipc.o
te_mcu-objs		+= mcu/ipc/te_ipc_mcu.o
te_mcu-objs		+= mcu/ipc/te_ipc_core.o
ifeq ($(CONFIG_TE_MCU_VERIFY),y)
te_mcu-objs		+= mcu/te_mcu_verify.o
te-CFLAGS		+= -DCONFIG_TE_MCU_VERIFY
endif


te_sub_modules		+= reg
te_reg-objs		+= reg/te_reg.o
te_reg-objs		+= reg/te_reg_ctop.o
te_reg-objs		+= reg/te_reg_top.o
te_reg-objs		+= reg/te_reg_tpi.o
te_reg-objs		+= reg/te_reg_fe_pidf.o
te_reg-objs		+= reg/te_reg_fe_tsbuf.o
te_reg-objs		+= reg/te_reg_fe_stcc.o
te_reg-objs		+= reg/te_reg_be.o
te_reg-objs		+= reg/te_reg_upload.o
te_reg-objs		+= reg/te_reg_ciplus.o
te_reg-objs		+= reg/te_reg_atsc3.o
te_reg-objs		+= reg/te_reg_arib2.o
te_reg-objs		+= reg/te_reg_dumper.o
te_reg-objs		+= reg/te_reg_dsc.o

ifeq ($(INCLUDE_M17_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/m17/te/te_reg_ctop_m17.o
endif

ifeq ($(INCLUDE_L18_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/l18/te/te_reg_ctop_l18.o
endif

ifeq ($(INCLUDE_O18_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/o18/te/te_reg_ctop_o18.o
endif

ifeq ($(INCLUDE_M19_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/m19/te/te_reg_ctop_m19.o
endif

ifeq ($(INCLUDE_O20_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/o20/te/te_reg_ctop_o20.o
endif

ifeq ($(INCLUDE_E60_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/e60/te/te_reg_ctop_e60.o
endif

ifeq ($(INCLUDE_O22_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/o22/te/te_reg_ctop_o22.o
endif

ifeq ($(INCLUDE_M23_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/m23/te/te_reg_ctop_m23.o
endif

ifeq ($(INCLUDE_O24_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/o24/te/te_reg_ctop_o24.o
endif

ifeq ($(INCLUDE_O26_CHIP_KDRV), YES)
te_reg-objs		+= ../../chip/o26/te/te_reg_ctop_o26.o
te_reg-objs		+= ../../chip/o26/ion/ion_ci_reg_o26.o
te_reg-objs		+= ../../chip/o26/ion/ion_io_reg_o26.o
endif

te_reg-CFLAGS		+= -I$(KDRV_TOP_DIR)/$(te_module)/reg/

CONFIG_TE_DVB		:= y
ifeq ($(INCLUDE_KDRV_SDEC),YES)
CONFIG_TE_DVB_DEMUX	:= y
else
CONFIG_TE_DVB_DEMUX	:= n
endif
ifeq ($(INCLUDE_KDRV_PVR),YES)
CONFIG_TE_DVB_DVR	:= y
else
CONFIG_TE_DVB_DVR	:= n
endif
ifeq ($(INCLUDE_KDRV_CI),YES)
CONFIG_TE_DVB_CI	:= y
else
CONFIG_TE_DVB_CI	:= n
endif
ifeq ($(INCLUDE_KDRV_CIPLUS),YES)
CONFIG_TE_DVB_CIPLUS	:= y
else
CONFIG_TE_DVB_CIPLUS	:= n
endif
ifeq ($(INCLUDE_KDRV_SCI),YES)
CONFIG_TE_DVB_SCI	:= y
else
CONFIG_TE_DVB_SCI	:= n
endif
ifeq ($(INCLUDE_KDRV_ATSC3)$(INCLUDE_KDRV_ARIB2),YESYES)
CONFIG_TE_DVB_DELIVERY	:= y
else
CONFIG_TE_DVB_DELIVERY	:= n
endif

ifeq ($(CONFIG_TE_DVB),y)
te_sub_modules		+= dvb-core
te_dvb-core-objs	+= dvb-core/lxdvb_drv.o
te_dvb-core-objs	+= dvb-core/lxdvb_dev.o
te_dvb-core-objs	+= dvb-core/lxdvb_proc.o
ifeq ($(CONFIG_TE_DVB_DEMUX),y)
te_dvb-core-objs	+= dvb-core/lxdvb_demux.o
te_dvb-core-objs	+= dvb-core/lxdvb_nagra.o
te-CFLAGS		+= -DCONFIG_TE_DVB_DEMUX
endif
ifeq ($(CONFIG_TE_DVB_DVR),y)
te_dvb-core-objs	+= dvb-core/lxdvb_dvr.o
te-CFLAGS		+= -DCONFIG_TE_DVB_DVR
endif
ifeq ($(CONFIG_TE_DVB_CI),y)
te_dvb-core-objs	+= dvb-core/lxdvb_ca.o
te-CFLAGS		+= -DCONFIG_TE_DVB_CI
endif
ifeq ($(CONFIG_TE_DVB_CIPLUS),y)
te_dvb-core-objs	+= dvb-core/lxdvb_ci14.o
te-CFLAGS		+= -DCONFIG_TE_DVB_CIPLUS
endif
ifeq ($(CONFIG_TE_DVB_SCI),y)
te_dvb-core-objs	+= dvb-core/lxdvb_sci.o
te-CFLAGS		+= -DCONFIG_TE_DVB_SCI
endif
ifeq ($(CONFIG_TE_DVB_DELIVERY),y)
te_dvb-core-objs	+= dvb-core/lxdvb_delivery.o
te-CFLAGS		+= -DCONFIG_TE_DVB_DELIVERY
endif
te-CFLAGS		+= -I$(KDRV_TOP_DIR)/$(te_module)/dvb-core/
te-CFLAGS		+= -I$(srctree)/drivers/media/dvb-core/
te-CFLAGS		+= -DCONFIG_TE_DVB
endif

CONFIG_TE_CRYPTO	:= y
ifeq ($(CONFIG_TE_CRYPTO),y)
te_sub_modules          += crypto
te_crypto-objs		+= crypto/crypto_drv.o
te_crypto-objs		+= crypto/crypto_core.o
te_crypto-objs		+= crypto/crypto_debug.o
te-CFLAGS		+= -DCONFIG_TE_CRYPTO
endif

ifeq ($(INCLUDE_KDRV_SDEC),YES)
te_sub_modules		+= sdec
te_sdec-objs		+= sdec/sdec_cfg.o
te_sdec-objs		+= sdec/sdec_drv.o
te_sdec-objs		+= sdec/sdec_debug.o
te_sdec-objs		+= sdec/sdec_core.o
te_sdec-objs		+= sdec/sdec_io.o
te_sdec-objs		+= sdec/sdec_filter.o
te_sdec-objs		+= sdec/sdec_temi.o
te_sdec-objs		+= sdec/sdec_clock.o
te_sdec-objs		+= sdec/sdec_descrambler.o
te_sdec-objs		+= sdec/sdec_isr.o
te_sdec-objs		+= sdec/sdec_mm.o
endif

ifeq ($(INCLUDE_KDRV_PVR),YES)
te_sub_modules		+= pvr
te_pvr-objs		+= pvr/pvr_cfg.o
te_pvr-objs		+= pvr/pvr_drv.o
te_pvr-objs		+= pvr/pvr_debug.o
te_pvr-objs		+= pvr/pvr_core.o
te_pvr-objs		+= pvr/pvr_dn.o
te_pvr-objs		+= pvr/pvr_up.o
te_pvr-objs		+= pvr/pvr_isr.o
endif

ifeq ($(INCLUDE_KDRV_CIPLUS),YES)
te_sub_modules		+= ciplus
te_ciplus-objs		+= ciplus/ciplus_cfg.o
te_ciplus-objs		+= ciplus/ciplus_drv.o
te_ciplus-objs		+= ciplus/ciplus_core.o
te_ciplus-objs		+= ciplus/ciplus_isr.o
te_ciplus-objs		+= ciplus/ciplus_io.o
te_ciplus-objs		+= ciplus/ciplus_ipd.o
te_ciplus-objs		+= ciplus/ciplus_pidf.o
te_ciplus-objs		+= ciplus/ciplus_mm.o
te_ciplus-objs		+= ciplus/ciplus_debug.o
endif

ifeq ($(INCLUDE_KDRV_ATSC3),YES)
te_sub_modules		+= atsc3
te_atsc3-objs		+= atsc3/atsc3_cfg.o
te_atsc3-objs		+= atsc3/atsc3_drv.o
te_atsc3-objs		+= atsc3/atsc3_core.o
te_atsc3-objs		+= atsc3/atsc3_filter.o
te_atsc3-objs		+= atsc3/atsc3_io.o
te_atsc3-objs		+= atsc3/atsc3_clock.o
te_atsc3-objs		+= atsc3/atsc3_mm.o
te_atsc3-objs		+= atsc3/atsc3_isr.o
te_atsc3-objs		+= atsc3/atsc3_debug.o
endif

ifeq ($(INCLUDE_KDRV_ARIB2),YES)
te_sub_modules		+= arib2
te_arib2-objs		+= arib2/arib2_cfg.o
te_arib2-objs		+= arib2/arib2_mm.o
te_arib2-objs		+= arib2/arib2_drv.o
te_arib2-objs		+= arib2/arib2_core.o
te_arib2-objs		+= arib2/arib2_debug.o
te_arib2-objs		+= arib2/arib2_io.o
te_arib2-objs		+= arib2/arib2_isr.o
te_arib2-objs		+= arib2/arib2_filter.o
te_arib2-objs		+= arib2/arib2_clock.o
endif

ifeq ($(INCLUDE_KDRV_CI),YES)
te_sub_modules		+= ci
te_ci-objs	+= ci/ci_drv.o
endif

ifeq ($(INCLUDE_KDRV_SCI),YES)
te_sub_modules		+= sci
te_sci-objs		+= sci/sci_drv.o
te_sci-objs		+= sci/sci_cfg.o
te_sci-objs		+= sci/sci_core.o
te_sci-objs		+= sci/sci_isr.o
te_sci-objs		+= sci/sci_ctop.o
te_sci-objs		+= sci/sci_reg.o
te_sci-objs		+= sci/sci_debug.o
endif

ifeq ($(INCLUDE_KDRV_CI20),YES)
te_sub_modules		+= ci20
te_ci20-objs	+= ci20/ci20_drv.o
endif

ifeq ($(USE_TE_EMULATOR),YES)
te_sub_modules		+= emulator
te_emulator-objs	+= emulator/te_emul.o
te_emulator-objs	+= emulator/hw_mcu.o
te_emulator-objs	+= emulator/hw_cpu.o
te_emulator-objs	+= emulator/hw_te_mcu.o
te_emulator-objs	+= emulator/hw_te_atsc3.o

kdrv_te-CFLAGS		+= -DTE_EMULATOR

ifneq ($(TE_EMULATOR_DIR),)
obj-y	+= $(te_module)/emulator/mcu/
endif

endif


# add all submodule objects
kdrv_te-objs	+= $(te_core-objs)
kdrv_te-objs	+= $(foreach m,$(te_sub_modules),$(te_$(m)-objs))


#-------------------------------------------------------------------------------
# TODO: define your driver specific CFLAGS
#-------------------------------------------------------------------------------
kdrv_te-CFLAGS	+= -DNEW_TE
kdrv_te-CFLAGS	+= -I$(KDRV_TOP_DIR)/$(te_module)/include
#kdrv_te-CFLAGS	+= $(addprefix -I$(KDRV_TOP_DIR)/$(te_module)/,$(te_sub_modules))
kdrv_te-CFLAGS	+=
kdrv_te-CFLAGS	+=

# only apply to specific modules
ifneq ($(VERSION), 4)
define te_make_module_cflags
$(foreach o,$(te_$(1)-objs), \
	$(eval CFLAGS_te/$(o)+=$(te-CFLAGS) $(te_$(1)-CFLAGS)))
endef
else
define te_make_module_cflags
$(foreach o,$(notdir $(te_$(1)-objs)), \
	$(eval CFLAGS_$(o)+=$(te-CFLAGS) $(te_$(1)-CFLAGS)))
endef
endif

$(call te_make_module_cflags,core)
$(foreach m,$(te_sub_modules),$(call te_make_module_cflags,$(m)))

#-------------------------------------------------------------------------------
# DO NOT change the below part
#-------------------------------------------------------------------------------
EXTRA_CFLAGS		+= $(kdrv_te-CFLAGS)

ifeq ($(KDRV_GLOBAL_LINK), YES)
# KDRV_MODULE_OBJS is used for KDRV_GLOBAL_LINK mode
KDRV_MODULE_OBJS	+= $(addprefix $(te_module)/,$(kdrv_te-objs))
else
obj-m				:= kdrv_te.o
endif
