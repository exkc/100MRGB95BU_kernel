INCLUDE_O26_CHIP_KDRV = YES

#-----------------------------------------------------------------------------------------
# arch_dev.mk describles the default device description
#-----------------------------------------------------------------------------------------
include $(KDRV_TOP_DIR)/../chip/o26/os/arch_dev.mk

INCLUDE_KDRV_SAMPLE     := NO
INCLUDE_KDRV_AFE        := NO
#INCLUDE_KDRV_AUDIO      := YES
INCLUDE_KDRV_CI         := NO
INCLUDE_KDRV_LEGACY_CI  := NO
INCLUDE_KDRV_DE         := NO
INCLUDE_KDRV_DEMOD      := NO
INCLUDE_KDRV_DENC       := NO
INCLUDE_KDRV_EMMC       := NO
#INCLUDE_KDRV_FBDEV      := YES
#INCLUDE_KDRV_GFX        := YES
INCLUDE_KDRV_GPIO       := NO
INCLUDE_KDRV_HDMI       := NO
INCLUDE_KDRV_HDMI20     := NO
INCLUDE_KDRV_I2C        := NO
INCLUDE_KDRV_PE         := NO
#INCLUDE_KDRV_TE         := YES
#INCLUDE_KDRV_CIPLUS     := YES
INCLUDE_KDRV_TE_LEGACY  := NO
#INCLUDE_KDRV_SDEC       := YES
#INCLUDE_KDRV_PVR        := YES
INCLUDE_KDRV_CLK        := NO
INCLUDE_KDRV_VBI        := NO
#INCLUDE_KDRV_VDEC       := YES
INCLUDE_KDRV_VENC       := NO
INCLUDE_KDRV_PNG        := NO
INCLUDE_KDRV_SE         := NO
INCLUDE_KDRV_SYS        := YES
#INCLUDE_KDRV_SCI        := YES
INCLUDE_KDRV_MONITOR    := NO
INCLUDE_KDRV_MJPEG      := NO
INCLUDE_KDRV_APR        := NO
INCLUDE_KDRV_MEMPROT    := NO
INCLUDE_KDRV_PM         := NO
INCLUDE_KDRV_BE         := NO
INCLUDE_KDRV_LGBUS      := NO
INCLUDE_KDRV_OVI        := NO
INCLUDE_KDRV_LOGM       := YES
INCLUDE_KDRV_VIP        := NO
INCLUDE_KDRV_SLT        := NO
INCLUDE_KDRV_SPI        := NO
#INCLUDE_KDRV_ATSC3      := YES
INCLUDE_KDRV_SWCEC      := NO
#INCLUDE_KDRV_ARIB2      := YES
INCLUDE_KDRV_CI20       := NO

# (2023/03/20) 빌드 에러 방지용으로 IRB 빌드 제외
INCLUDE_KDRV_IRB        := NO

#-----------------------------------------------------------------------------------------
# O18 arch default PM
#-----------------------------------------------------------------------------------------
KDRV_CONFIG_PM_SAMPLE   := NO
KDRV_CONFIG_PM_AFE      := NO
KDRV_CONFIG_PM_LEGACY_CI := NO
KDRV_CONFIG_PM_DE       := NO
KDRV_CONFIG_PM_DEMOD    := NO
KDRV_CONFIG_PM_DENC     := NO
KDRV_CONFIG_PM_EMMC     := NO
KDRV_CONFIG_PM_FBDEV    := YES
KDRV_CONFIG_PM_GFX      := NO
KDRV_CONFIG_PM_GPIO     := NO
KDRV_CONFIG_PM_HDMI     := NO
KDRV_CONFIG_PM_HDMI20   := NO
KDRV_CONFIG_PM_I2C      := NO
KDRV_CONFIG_PM_PE       := NO
KDRV_CONFIG_PM_PVR      := NO
KDRV_CONFIG_PM_SDEC     := NO
KDRV_CONFIG_PM_TE       := NO
KDRV_CONFIG_PM_CIPLUS   := NO
KDRV_CONFIG_PM_VBI      := NO
KDRV_CONFIG_PM_MMCU     := NO
KDRV_CONFIG_PM_VDEC     := NO
KDRV_CONFIG_PM_VENC     := NO
KDRV_CONFIG_PM_PNG      := NO
KDRV_CONFIG_PM_SE       := NO
KDRV_CONFIG_PM_SYS      := NO
KDRV_CONFIG_PM_SCI      := NO
KDRV_CONFIG_PM_CLK      := NO
KDRV_CONFIG_PM_MONITOR  := NO
KDRV_CONFIG_PM_MJPEG    := NO
KDRV_CONFIG_PM_APR      := NO
KDRV_CONFIG_PM_MEMPROT  := NO
KDRV_CONFIG_PM_PM       := NO
KDRV_CONFIG_PM_BE       := NO
KDRV_CONFIG_PM_LGBUS    := NO
KDRV_CONFIG_PM_OVI      := NO
KDRV_CONFIG_PM_LOGM     := NO
KDRV_CONFIG_PM_VIP      := NO
KDRV_CONFIG_PM_SPI      := NO
#-----------------------------------------------------------------------------------------
# GAL(GFX) device
#-----------------------------------------------------------------------------------------
export GAL_CPC_VERSION := 5.0.11.p3
