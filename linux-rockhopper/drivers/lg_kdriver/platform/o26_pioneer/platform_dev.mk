INCLUDE_O26_CHIP_KDRV=YES

#-----------------------------------------------------------------------------------------
# arch_dev.mk describles the default device description
#-----------------------------------------------------------------------------------------
include $(KDRV_TOP_DIR)/../chip/o26/os/arch_dev.mk

ifeq ($(BUILD_FEATURE_audio_board),y)
include $(KDRV_TOP_DIR)/../platform/o26_pioneer/audio/platform_dev.mk
else
include $(KDRV_TOP_DIR)/../platform/o26_pioneer/tv/platform_dev.mk
endif

export GAL_CPC_VERSION := 5.0.11.p3

