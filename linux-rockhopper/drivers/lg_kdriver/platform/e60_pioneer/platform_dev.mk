INCLUDE_E60_CHIP_KDRV	?= YES

#-----------------------------------------------------------------------------------------
# arch_dev.mk describles the default device description
#-----------------------------------------------------------------------------------------
include $(KDRV_TOP_DIR)/../chip/e60/os/arch_dev.mk

INCLUDE_KDRV_SAMPLE     := NO
INCLUDE_KDRV_LEGACY_CI  := NO
INCLUDE_KDRV_HDMI       := NO
#INCLUDE_KDRV_AUDIO		:= NO
INCLUDE_KDRV_TE_LEGACY  := NO
INCLUDE_KDRV_PNG        := NO
INCLUDE_KDRV_MONITOR    := NO
INCLUDE_KDRV_APR        := NO
INCLUDE_KDRV_MEMPROT    := NO
INCLUDE_KDRV_VIP        := NO
INCLUDE_KDRV_SLT        := NO
INCLUDE_KDRV_SPI        := NO
export GAL_CPC_VERSION := 5.0.11.p3
