#-----------------------------------------------------------------------------------------
# arch_dev.mk describles the default device description
#-----------------------------------------------------------------------------------------
include $(KDRV_TOP_DIR)/../chip/m23/os/arch_dev.mk

# (2022/04/15)
# M23 은 1.5GB DDR 의 작은 메모리 공간내에서 동작을 해야 하므로, 사용되지 않은 칩 드라이버가
# 동작하지 않도록 조치한다. 이를 통해 최소 약 12 MB 정도의 커널 메모리를 절감할 수 있다.
#
# kdriver 빌드시에 platform_dev.mk 는 가장 마지막으로 설정을 바꿀 수 있는 곳이므로,
# 공통 코드는 수정하지 않고 M23 특화 설정은 이곳에 두는 것이 맞다.
#
INCLUDE_O20_CHIP_KDRV := NO
INCLUDE_E60_CHIP_KDRV := NO
INCLUDE_O22_CHIP_KDRV := NO

# customize device driver inclusion
#

# arch_dev.mk 에서 default YES 인것중, 미검증된 것은 NO 를 기본이 되게 한다.
# 적어도 컴파일 에러가 없는 것, 칩에 무관한 것들만 YES 로 바꾸도록 한다
#

INCLUDE_KDRV_AUDIO      := YES
INCLUDE_KDRV_AFE        := YES
INCLUDE_KDRV_CI         := YES
INCLUDE_KDRV_DE         := YES
INCLUDE_KDRV_DEMOD      := YES
INCLUDE_KDRV_DENC       := NO # YES
INCLUDE_KDRV_EMMC       := YES
INCLUDE_KDRV_FBDEV      := YES
INCLUDE_KDRV_GFX        := YES
INCLUDE_KDRV_GPIO       := YES
INCLUDE_KDRV_HDMI20     := YES
INCLUDE_KDRV_I2C        := YES
INCLUDE_KDRV_PE         := YES
INCLUDE_KDRV_TE         := YES
INCLUDE_KDRV_CIPLUS     := YES
INCLUDE_KDRV_CI20       := YES
INCLUDE_KDRV_SDEC       := YES
INCLUDE_KDRV_PVR        := YES
INCLUDE_KDRV_ATSC3      := YES
INCLUDE_KDRV_ARIB2      := YES
INCLUDE_KDRV_CLK        := NO # YES
INCLUDE_KDRV_VBI        := YES
INCLUDE_KDRV_VDEC       := YES
INCLUDE_KDRV_VENC       := YES
INCLUDE_KDRV_SE         := YES # YES
INCLUDE_KDRV_SCI        := YES
INCLUDE_KDRV_MONITOR    := NO # YES
INCLUDE_KDRV_MJPEG      := YES
INCLUDE_KDRV_APR        := NO # YES
INCLUDE_KDRV_PM         := YES # YES
INCLUDE_KDRV_BE         := YES
INCLUDE_KDRV_LGBUS      := YES # YES
INCLUDE_KDRV_OVI        := YES
INCLUDE_KDRV_VIP        := NO # YES
INCLUDE_KDRV_SLT        := NO # YES
INCLUDE_KDRV_SPI        := NO # YES
INCLUDE_KDRV_UCOM       := YES
INCLUDE_KDRV_IRB        := YES
INCLUDE_KDRV_PWM		:= NO # YES

#-----------------------------------------------------------------------------------------
# GAL(GFX) device
#-----------------------------------------------------------------------------------------
export GAL_CPC_VERSION := 5.0.11.p3
