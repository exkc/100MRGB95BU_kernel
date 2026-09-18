#-----------------------------------------------------------------------------------------
# arch_dev.mk describles the default device description
#-----------------------------------------------------------------------------------------
include $(KDRV_TOP_DIR)/../chip/o22/os/arch_dev.mk

# (2023/04/17) kernel size optimization
#
INCLUDE_O20_CHIP_KDRV := NO
INCLUDE_E60_CHIP_KDRV := NO
INCLUDE_M23_CHIP_KDRV := NO

# customize device driver inclusion
#
INCLUDE_KDRV_SAMPLE		:= NO
INCLUDE_KDRV_AAD		:= NO
#INCLUDE_KDRV_CI		:= NO
#INCLUDE_KDRV_DEMOD		:= NO
INCLUDE_KDRV_DENC		:= NO
INCLUDE_KDRV_TE_LEGACY  := NO
INCLUDE_KDRV_PNG		:= NO
#INCLUDE_KDRV_SCI		:= NO
INCLUDE_KDRV_MONITOR	:= NO
INCLUDE_KDRV_APR		:= NO
INCLUDE_KDRV_MEMPROT	:= NO
INCLUDE_KDRV_PM			:= YES
INCLUDE_KDRV_EMMC       := YES
INCLUDE_KDRV_LGBUS		:= YES
#INCLUDE_KDRV_LOGM 		:= NO	# enable LOGM by os/arch_dev_mk
INCLUDE_KDRV_VIP		:= NO
INCLUDE_KDRV_SLT		:= NO
INCLUDE_KDRV_SPI		:= YES

#-----------------------------------------------------------------------------------------
# GAL(GFX) device
#-----------------------------------------------------------------------------------------
export GAL_CPC_VERSION := 5.0.11.p3
