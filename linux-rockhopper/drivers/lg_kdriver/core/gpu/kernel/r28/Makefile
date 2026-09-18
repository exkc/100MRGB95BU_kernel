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

DDK_BUILD_TOP	:= $(PWD)/..
LINUX := linux
KERNELDIR := $(DDK_BUILD_TOP)/$(LINUX)
INSTALL_DIR	:= $(DDK_BUILD_TOP)/result_kernel
MIDG_K := arm64

#------------------------------------------------------------------------------
# load cfg
#------------------------------------------------------------------------------
ifeq ($(MIDG_K),arm64)
export ARCH_KERNEL=arm64
export KDIR=$(KERNELDIR)
export CROSS_COMPILE=$(CROSS_COMPILE_AARCH64)
else
export ARCH_KERNEL=arm
export KDIR=$(KERNELDIR)
export CROSS_COMPILE=$(CROSS_COMPILE_AARCH32)
endif

TGT_CC		:= $(shell which $(CROSS_COMPILE)gcc)

SCONS_CONFIGS := CONFIG_MALI_MIDGARD=m
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_FAKE=y

SCONS_CFLAGS :=-DMALI_GCC_WORKAROUND_MIDCOM_4598=0
SCONS_CFLAGS +=-DCONFIG_MALI_PLATFORM_FAKE
SCONS_CFLAGS +=-DLGE_DVFS_SUPPORT
SCONS_CFLAGS +=-DLGE_PAGE_POOL_MAX=0

ifeq ($(MIDG_HARDWARE_PLATFORM),M16_PLATFORM)
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1312=y
SCONS_CFLAGS += -DCONFIG_MALI_PLATFORM_LG1312
else ifeq ($(MIDG_HARDWARE_PLATFORM),M17_PLATFORM)
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1313=y
SCONS_CFLAGS += -DCONFIG_MALI_PLATFORM_LG1313
else ifeq ($(MIDG_HARDWARE_PLATFORM),O18_PLATFORM)
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1211=y
SCONS_CFLAGS += -DCONFIG_MALI_PLATFORM_LG1211
else ifeq ($(MIDG_HARDWARE_PLATFORM),O20_PLATFORM)
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1212=y
SCONS_CFLAGS += -DCONFIG_MALI_PLATFORM_LG1212
else
SCONS_CONFIGS += CONFIG_MALI_PLATFORM_LG1312=y
SCONS_CFLAGS += -DCONFIG_MALI_PLATFORM_LG1312
endif


#------------------------------------------------------------------------------
# main
#------------------------------------------------------------------------------
.PHONEY : chk_env param help
.PHONEY : check_evn param install
.PHONEY : midgard_k.b midgard_k.clean

all: chk_env param midgard_k.b install
	$(ECHO) "<!> build done..."

clean: midgard_k.clean cmn.clean
	$(ECHO) "<!> clean done..."

install: midgard_k.install
	$(ECHO) "<!> install done..."

midgard_k.b:
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/kernel/drivers/base/dma_buf_unified
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/kernel/drivers/gpu/arm/midgard SCONS_CONFIGS='$(SCONS_CONFIGS)' SCONS_CFLAGS='$(SCONS_CFLAGS)'

midgard_k.clean:
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/kernel/drivers/base/dma_buf_unified clean
	$(MAKE) -j10 -C $(DDK_BUILD_TOP)/kernel/drivers/gpu/arm/midgard clean

midgard_k.install:
	$(CP) $(DDK_BUILD_TOP)/kernel/drivers/gpu/arm/midgard/mali_kbase.ko $(INSTALL_DIR)
	$(CP) $(DDK_BUILD_TOP)/kernel/drivers/base/dma_buf_unified/dma_buf_unified.ko $(INSTALL_DIR)
cmn.clean:
	$(RM) -rf $(INSTALL_DIR)

# check build environment before entering the real build process
chk_env:
	@if [ ! -e $(KERNELDIR) ]; then \
		echo "[ERR] 'linux' kernel link not found or invalid";  \
		exit -1;\
	fi

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
