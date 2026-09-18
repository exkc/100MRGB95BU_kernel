#-----------------------------------------------------------------------------------------
# arch_dev.mk describles the default device description
#-----------------------------------------------------------------------------------------
include $(KDRV_TOP_DIR)/../chip/l18/os/arch_dev.mk

# TODO: List all modules whcih is always set to NO
# - some modules can't be tested with simple env.
# - some modules have their own test plan.
#
INCLUDE_KDRV_DENC		:= NO
INCLUDE_KDRV_DENC		:= NO
INCLUDE_KDRV_SCI		:= NO
INCLUDE_KDRV_HDMI		:= YES
INCLUDE_KDRV_VENC		:= NO
INCLUDE_KDRV_CIPLUS		:= NO
INCLUDE_KDRV_SPI       	:= NO
INCLUDE_KDRV_SLT		:= NO
INCLUDE_KDRV_PE			:= YES
