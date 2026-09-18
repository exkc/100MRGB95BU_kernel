#-----------------------------------------------------------------------------------------
# arch_dev.mk describles the default device description
#-----------------------------------------------------------------------------------------
include $(KDRV_TOP_DIR)/../chip/m16p/os/arch_dev.mk

INCLUDE_KDRV_LOGM 		:= YES


# m16p_fpga configs (2016/04/29)
#INCLUDE_KDRV_AAD		:= YES
#INCLUDE_KDRV_AUDIO		:= YES
#INCLUDE_KDRV_AFE		:= YES
#INCLUDE_KDRV_CI		:= NO
#INCLUDE_KDRV_DE		:= YES
#INCLUDE_KDRV_DEMOD		:= NO
#INCLUDE_KDRV_DENC		:= NO
#INCLUDE_KDRV_EMMC		:= NO
#INCLUDE_KDRV_FBDEV		:= YES
#INCLUDE_KDRV_GFX		:= YES
#INCLUDE_KDRV_GPIO		:= NO
#INCLUDE_KDRV_HDMI		:= NO
#INCLUDE_KDRV_HDMI20	:= NO
#INCLUDE_KDRV_I2C		:= NO
#INCLUDE_KDRV_PE		:= NO
#INCLUDE_KDRV_TE        := YES
#INCLUDE_KDRV_CIPLUS    := NO
#INCLUDE_KDRV_TE_LEGACY := NO
#INCLUDE_KDRV_SDEC		:= YES
#INCLUDE_KDRV_PVR		:= YES
#INCLUDE_KDRV_CLK		:= YES
#INCLUDE_KDRV_VBI		:= YES
#INCLUDE_KDRV_VDEC		:= YES
#INCLUDE_KDRV_VENC		:= NO
#INCLUDE_KDRV_PNG		:= NO
#INCLUDE_KDRV_SE		:= NO
#INCLUDE_KDRV_SYS		:= YES
#INCLUDE_KDRV_SCI		:= NO
#INCLUDE_KDRV_MONITOR	:= NO
#INCLUDE_KDRV_MJPEG		:= NO
#INCLUDE_KDRV_APR		:= NO
#INCLUDE_KDRV_MEMPROT	:= NO
#INCLUDE_KDRV_PM		:= NO
#INCLUDE_KDRV_BE		:= NO
#INCLUDE_KDRV_LGBUS		:= NO
#INCLUDE_KDRV_OVI		:= NO
#INCLUDE_KDRV_LOGM 		:= YES
#INCLUDE_KDRV_VIP		:= NO
#INCLUDE_KDRV_SLT		:= NO
#INCLUDE_KDRV_SPI       := NO

#-----------------------------------------------------------------------------------------
# GAL(GFX) device
#-----------------------------------------------------------------------------------------
export GAL_CPC_VERSION := 5.0.11.p3
