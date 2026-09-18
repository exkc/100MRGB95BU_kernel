#
# DDK integrated build system (SIC Lab. LG Electronics,Inc)
#
#
#------------------------------------------------------------------------------
# macro function
#------------------------------------------------------------------------------
_cnd_define  = $(if $(subst $(1)A,,$(strip $($2))A),,-D$2)
_cnd_assign  = $(if $(subst $(1)A,,$(strip $($2))A),$4,$3)
cond_define  = $(call _cnd_define,$(strip $1),$(strip $2))
cond_assign  = $(call _cnd_assign,$(strip $1),$(strip $2),$(strip $3),$(strip $4))

V			?= 0
Q			:= $(call cond_assign, 0, V, @,)
ECHO		:= $(Q)echo
MKDIR		:= $(Q)mkdir
CP			:= $(Q)cp
RM			:= $(Q)rm
MV			:= $(Q)mv

KDRV_TOP_DIR	:= $(PWD)
DDK_BUILD_TOP	:= $(KDRV_TOP_DIR)
LINUX := $(DDK_BUILD_TOP)/../linux
KERNELDIR := $(LINUX)
INSTALL_DIR	:= $(PWD)/gpu-modules/ko

#------------------------------------------------------------------------------
# load cfg
#------------------------------------------------------------------------------
ifeq ($(MIDG_K), arm64)
export ARCH=arm64
export KDIR=$(LINUX)
export CROSS_COMPILE=aarch64-linux-gnu-
else
export ARCH=arm
export KDIR=$(LINUX)
export CROSS_COMPILE=arm-starfish-linux-gnueabi-
endif

export PLATFORM_CHIP=lg1313

TGT_CC		:= $(shell which $(CROSS_COMPILE)gcc)

SCONS_CONFIGS := CONFIG_KDS=m CONFIG_MALI_MIDGARD=m
SCONS_CONFIGS += CONFIG_UMP=y
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_FAKE=y

SCONS_CFLAGS :=-DMALI_GCC_WORKAROUND_MIDCOM_4598=0
SCONS_CFLAGS +=-DCONFIG_KDS -DCONFIG_UMP
SCONS_CFLAGS +=-DCONFIG_MALI_PLATFORM_FAKE
SCONS_CFLAGS +=-DLGE_DVFS_SUPPORT
SCONS_CFLAGS +=-DLGE_PAGE_POOL_MAX=0
SCONS_CFLAGS +=-DLG_DISABLE_SECURE_MEMALLOC
SCONS_CFLAGS +=-DCONFIG_MALI_MIDGARD_DVFS

ifeq ($(PLATFORM_CHIP), lg1210)
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1210=y
SCONS_CFLAGS +=-DCONFIG_MALI_PLATFORM_LG1210
else ifeq ($(PLATFORM_CHIP), lg1312)
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1312=y
SCONS_CFLAGS +=-DCONFIG_MALI_PLATFORM_LG1312
else ifeq ($(PLATFORM_CHIP), lg1313)
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1313=y
SCONS_CFLAGS +=-DCONFIG_MALI_PLATFORM_LG1313
else ifeq ($(PLATFORM_CHIP), lg1314)
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1314=y
SCONS_CFLAGS +=-DCONFIG_MALI_PLATFORM_LG1314
else
$(error PLATFORM_CHIP not set correctly.)
endif

#------------------------------------------------------------------------------
# main
#------------------------------------------------------------------------------
.PHONEY : chk_env param help
.PHONEY : check_evn param
.PHONEY : midgard_k.b midgard_k.clean

all: chk_env param midgard_k.b
	$(ECHO) "<!> build done..."

#clean: midgard_k.clean cmn.clean
clean: midgard_k.clean
	$(ECHO) "<!> clean done..."

install: midgard_k.install
	$(ECHO) "<!> install done..."

midgard_k.b:
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/kds
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/dma_buf_unified
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/ump/src SCONS_CFLAGS='$(SCONS_CFLAGS)'
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/ump/src/imports/lgfb
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/ump/src/imports/ion
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/gpu/arm/midgard SCONS_CONFIGS='$(SCONS_CONFIGS)' SCONS_CFLAGS='$(SCONS_CFLAGS)'

midgard_k.clean:
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/kds clean
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/dma_buf_unified clean
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/ump/src clean
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/ump/src/imports/lgfb clean
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/base/ump/src/imports/ion clean
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/drivers/gpu/arm/midgard clean
	$(RM) -f $(INSTALL_DIR)/*

midgard_k.install: midgard_k.b
	$(CP) $(DDK_BUILD_TOP)/drivers/gpu/arm/midgard/mali_kbase.ko $(INSTALL_DIR)
	$(CP) $(DDK_BUILD_TOP)/drivers/base/kds/kds.ko $(INSTALL_DIR)
	$(CP) $(DDK_BUILD_TOP)/drivers/base/dma_buf_unified/dma_buf_unified.ko $(INSTALL_DIR)
	$(CP) $(DDK_BUILD_TOP)/drivers/base/ump/src/imports/ion/ump_ion_import.ko $(INSTALL_DIR)
	$(CP) $(DDK_BUILD_TOP)/drivers/base/ump/src/imports/lgfb/ump_lgfb_import.ko $(INSTALL_DIR)
	$(CP) $(DDK_BUILD_TOP)/drivers/base/ump/src/ump.ko $(INSTALL_DIR)

# check build environment before entering the real build process
chk_env:
	@if [ "x" = "x$(TGT_CC)" ]; then \
		echo "[ERR] cross compiler $(CROSS_TOOL)gcc not found. add it to your PATH"; \
		exit -1;\
	fi

	$(MKDIR) -p $(INSTALL_DIR)

	$(ECHO) "<!> environment check ok.."

#------------------------------------------------------------------------------
# param reporter
#------------------------------------------------------------------------------
param:
	@echo "-------------------------------------------------------------------------------"
	@echo "Q               = $(Q)"
	@echo "-------------------------------------------------------------------------------"
	@echo "CC             = $(TGT_CC)"
	@echo "-------------------------------------------------------------------------------"
	@echo "-------------------------------------------------------------------------------"

#------------------------------------------------------------------------------
# help
#------------------------------------------------------------------------------
help:
