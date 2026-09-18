# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

CHIP_NAME := $(PLATFORM_CHIP_NAME)

aud_src := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

aud-objs += kaimc.o
aud-objs += module_list.o
aud-objs += pipeline.o
aud-objs += proc.o
aud-objs += regs.o
aud-objs += user_imc.o
aud-objs += blind.o
aud-objs += init.o
aud-objs += block_manager.o
aud-objs += farm.o

aud-objs += input.o
aud-objs += decoder.o
aud-objs += renderer.o
aud-objs += mixer.o
aud-objs += se.o
aud-objs += output.o
aud-objs += capture.o
aud-objs += encoder.o
aud-objs += clock.o

aud-objs += platform.o
aud-objs += driver.o
aud-objs += aapi_media.o
aud-objs += aapi_debug.o
aud-objs += dsp_control.o

aud-objs += notifier.o

aud-objs += alsa/alsa_machine.o
aud-objs += alsa/alsa_codec.o
aud-objs += alsa/alsa_platform.o
aud-objs += alsa/alsa_platform_dai.o
aud-objs += alsa/alsa_decoder.o
aud-objs += alsa/alsa_sndout.o
aud-objs += alsa/alsa_sif.o
aud-objs += alsa/alsa_se.o
aud-objs += alsa/alsa_playback.o
aud-objs += alsa/alsa_capture.o

aud-objs += aad_if.o
aud-objs += aad/aad.o
aud-objs += aad/aad_cfg.o
aud-objs += aad/aad_info.o
aud-objs += aad/aad_debug.o

aud-objs += hal/$(CHIP_NAME)/hal.o
aud-objs += hal/$(CHIP_NAME)/hal_bc.o
aud-objs += hal/$(CHIP_NAME)/hal_clock.o
aud-objs += hal/$(CHIP_NAME)/hal_codec.o
aud-objs += hal/$(CHIP_NAME)/hal_output.o
aud-objs += hal/$(CHIP_NAME)/hal_ipc.o

EXTRA_CFLAGS += -DCHIP_NAME_$(CHIP_NAME)

$(info BUILD_FEATURE_y26_board=$(BUILD_FEATURE_y26_board))
$(info BUILD_FEATURE_audio_board=$(BUILD_FEATURE_audio_board))
#default values for PIONEER  (don't have BUILD_FEATURE_yxx_board)
ifeq ($(CHIP_NAME),m23)
Y2X_CFLAGS := -DMS12_VER=24
Y2X_CFLAGS += -DSE_VER=80
else
Y2X_CFLAGS := -DMS12_VER=28
Y2X_CFLAGS += -DSE_VER=82
Y2X_CFLAGS += -DSUPPORT_DAFC
endif

ifeq ($(BUILD_FEATURE_y22_board),y)
Y2X_CFLAGS := -DMS12_VER=24
Y2X_CFLAGS += -DSE_VER=73
Y2X_CFLAGS += -DSUPPORT_WMA
endif

ifeq ($(BUILD_FEATURE_y23_board),y)
Y2X_CFLAGS := -DMS12_VER=24
Y2X_CFLAGS += -DSE_VER=80
ifneq ($(CHIP_NAME),m23)
Y2X_CFLAGS += -DSUPPORT_DTSX
endif
Y2X_CFLAGS += -DSUPPORT_WMA
endif

ifeq ($(BUILD_FEATURE_y24_board),y)
Y2X_CFLAGS := -DMS12_VER=26
ifeq ($(CHIP_NAME),o24)
Y2X_CFLAGS += -DSE_VER=81
else
Y2X_CFLAGS += -DSE_VER=80
endif
Y2X_CFLAGS += -DSUPPORT_DTSX
Y2X_CFLAGS += -DSUPPORT_WMA
endif

ifeq ($(BUILD_FEATURE_y25_board),y)
Y2X_CFLAGS := -DMS12_VER=28
Y2X_CFLAGS += -DSUPPORT_DAFC
Y2X_CFLAGS += -DSUPPORT_MUSIC_MODE
ifeq ($(BUILD_FEATURE_audio_board),y)
Y2X_CFLAGS += -DSE_VER=83
Y2X_CFLAGS += -DSUPPORT_SOUNDBAR
else
Y2X_CFLAGS += -DSE_VER=82
endif
Y2X_CFLAGS += -DSUPPORT_WMA
endif

ifeq ($(BUILD_FEATURE_y26_board),y)
Y2X_CFLAGS := -DMS12_VER=28
Y2X_CFLAGS += -DSUPPORT_DAFC
Y2X_CFLAGS += -DSUPPORT_MUSIC_MODE
Y2X_CFLAGS += -DSE_VER=83
ifeq ($(BUILD_FEATURE_audio_board),y)
Y2X_CFLAGS += -DSUPPORT_SOUNDBAR
endif
endif

EXTRA_CFLAGS += $(Y2X_CFLAGS)

# see http://jira.lge.com/issue/browse/SICDTV-15376
# do not handle HDMI on audio only board
ifneq ($(BUILD_FEATURE_audio_board), y)
ifeq ($(CHIP_NAME), $(filter $(CHIP_NAME),o20 e60 o22 m23 o24 o26))
EXTRA_CFLAGS += -DINCLUDE_KDRV_HDMI20
EXTRA_CFLAGS += -DHAVE_HDMI21
endif
# ultrasense only for TV
EXTRA_CFLAGS += -DSUPPORT_ULTRASENSE
endif

ifeq ($(PLATFORM_CHIP_TYPE),FPGA)
EXTRA_CFLAGS += -DCHIP_TYPE_FPGA
endif

BUILD_SLT := $(if $(findstring slt,$(BUILD_FEATURES)),y,)
ifeq ($(BUILD_SLT),y)
EXTRA_CFLAGS += -DCHIP_TYPE_SLT
endif

ifeq ($(CHIP_NAME), $(filter $(CHIP_NAME),o24 o26))
EXTRA_CFLAGS += -D_LNX_
endif

ifeq ($(CHIP_NAME), $(filter $(CHIP_NAME),o24 o26))
EXTRA_CFLAGS += -D_DOLBY_IPP_
endif

# This flags for ID commercial and signage model.
#$(info INCLUDE_COMMERCIAL_PLATFORM=$(INCLUDE_COMMERCIAL_PLATFORM))
#$(info INCLUDE_SIGNAGE_PLATFORM=$(INCLUDE_SIGNAGE_PLATFORM))

ifeq ($(INCLUDE_COMMERCIAL_PLATFORM),YES)
EXTRA_CFLAGS += -DINCLUDE_COMMERCIAL_PLATFORM
endif

ifeq ($(INCLUDE_SIGNAGE_PLATFORM),YES)
EXTRA_CFLAGS += -DINCLUDE_SIGNAGE_PLATFORM
endif

EXTRA_CFLAGS += -I$(aud_src)
EXTRA_CFLAGS += -I$(aud_src)/include
EXTRA_CFLAGS += -I$(aud_src)/common_cfg
EXTRA_CFLAGS += -I$(aud_src)/../../include
EXTRA_CFLAGS += -I$(aud_src)/../../chip
EXTRA_CFLAGS += -I$(aud_src)/../base
EXTRA_CFLAGS += -I$(aud_src)/../gpio
EXTRA_CFLAGS += -I$(aud_src)/../hma
EXTRA_CFLAGS += -I$(aud_src)/../fwload
EXTRA_CFLAGS += -I$(aud_src)/../lgbus
EXTRA_CFLAGS += -I$(aud_src)/../sys
EXTRA_CFLAGS += -I$(aud_src)/../aud/common
EXTRA_CFLAGS += -I$(aud_src)/platform
EXTRA_CFLAGS += -DINCLUDE_$(shell echo $(CHIP_NAME) | tr [a-z] [A-Z])_CHIP_KDRV

ifeq ($(KDRV_MODULE_BUILD), YES)
CONFIG_LG_BUILTIN_KDRIVER := m
endif
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += aud.o
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += alsa/

ifeq ($(CHIP_NAME), $(filter $(CHIP_NAME),o22 m23 o24 o26))
audio_common-objs	+= common/buffer/adec_buf_dbg.o
audio_common-objs	+= common/buffer/adec_buf_helper.o
audio_common-objs	+= common/buffer/adec_common_buf.o
audio_common-objs	+= common/buffer/adec_inter_buf.o
audio_common-objs	+= common/buffer/adec_inter_buf_reader.o
audio_common-objs	+= common/buffer/adec_inter_buf_writer.o
audio_common-objs	+= common/module/adec_module_list.o
audio_common-objs	+= common/buffer/adec_buf_monitor.o
audio_common-objs	+= common/buffer/adec_buf_evt.o
audio_common-objs	+= common/buffer/adec_internal_buf.o
audio_common-objs	+= common/buffer/adec_multi_sink_buf.o
audio_common-objs	+= common/buffer/adec_multi_sink_client.o

audio_common-objs	+= common/common/adec_error.o
audio_common-objs	+= common/common/adec_processor_adap.o
audio_common-objs	+= common/common/adec_reg_api.o
audio_common-objs	+= common/common/adec_debug_index.o
audio_common-objs	+= common/common/log.o

audio_common-objs	+= common/imc/aimc_port.o
audio_common-objs	+= common/imc/adec_imc.o
audio_common-objs	+= common/ipc/adec_ipc.o
audio_common-objs	+= common/ipc/adec_ipc_dbg.o
audio_common-objs	+= common/util/adec_rbtree.o
audio_common-objs	+= common/platform/adec_platform_arm64.o

obj-$(CONFIG_LG_BUILTIN_KDRIVER) += audio_common.o
endif
