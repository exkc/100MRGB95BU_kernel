INCLUDE_O24_CHIP_KDRV = YES

#-----------------------------------------------------------------------------------------
# arch_dev.mk describles the default device description
#-----------------------------------------------------------------------------------------
include $(KDRV_TOP_DIR)/../chip/o24/os/arch_dev.mk

ifeq ($(BUILD_FEATURE_audio_board), y)
include $(KDRV_TOP_DIR)/../platform/o24_pioneer/audio_board/platform_dev.mk
else
INCLUDE_KDRV_SAMPLE     := NO
INCLUDE_KDRV_AFE        := YES
INCLUDE_KDRV_AUDIO      := YES
INCLUDE_KDRV_CI         := YES
INCLUDE_KDRV_LEGACY_CI  := NO
INCLUDE_KDRV_DE         := YES
INCLUDE_KDRV_DEMOD      := YES
INCLUDE_KDRV_DENC       := NO
INCLUDE_KDRV_EMMC       := NO
INCLUDE_KDRV_FBDEV      := YES
INCLUDE_KDRV_GFX        := YES
INCLUDE_KDRV_GPIO       := YES
INCLUDE_KDRV_HDMI       := NO
INCLUDE_KDRV_HDMI20     := YES
INCLUDE_KDRV_I2C        := YES
INCLUDE_KDRV_PE         := YES
INCLUDE_KDRV_TE         := YES
INCLUDE_KDRV_CIPLUS     := YES
INCLUDE_KDRV_TE_LEGACY  := NO
INCLUDE_KDRV_SDEC       := YES
INCLUDE_KDRV_PVR        := YES
INCLUDE_KDRV_CLK        := NO
INCLUDE_KDRV_VBI        := YES
INCLUDE_KDRV_VDEC       := YES
INCLUDE_KDRV_VENC       := YES
INCLUDE_KDRV_PNG        := NO
INCLUDE_KDRV_SE         := YES
INCLUDE_KDRV_SYS        := YES
INCLUDE_KDRV_SCI        := YES
INCLUDE_KDRV_MONITOR    := NO
INCLUDE_KDRV_MJPEG      := YES
INCLUDE_KDRV_APR        := NO
INCLUDE_KDRV_MEMPROT    := NO
INCLUDE_KDRV_PM         := YES
INCLUDE_KDRV_BE         := YES
INCLUDE_KDRV_LGBUS      := YES
INCLUDE_KDRV_OVI        := YES
INCLUDE_KDRV_LOGM       := YES
INCLUDE_KDRV_VIP        := NO
INCLUDE_KDRV_SLT        := NO
INCLUDE_KDRV_SPI        := NO
INCLUDE_KDRV_ATSC3      := YES
INCLUDE_KDRV_SWCEC      := NO
INCLUDE_KDRV_ARIB2      := YES
INCLUDE_KDRV_CI20       := YES
INCLUDE_KDRV_ION       := NO

# (2023/03/20) 빌드 에러 방지용으로 IRB 빌드 제외
INCLUDE_KDRV_IRB        := YES
INCLUDE_KDRV_UCOM       := YES
INCLUDE_KDRV_PQE_PM     := YES
INCLUDE_KDRV_PWM        := YES
endif

#-----------------------------------------------------------------------------------------
# GAL(GFX) device
#-----------------------------------------------------------------------------------------
export GAL_CPC_VERSION := 5.0.11.p3
