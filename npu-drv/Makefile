obj-m += npu-drv.o
npu-drv-y += src/npu_drv.o
npu-drv-y += src/npu_que.o
npu-drv-y += src/npu_utilization.o
npu-drv-y += src/npu_hwc_loader.o
#npu-drv-y += src/npu_hwc_emul.o
npu-drv-y += src/npu_hwc_dne.o
npu-drv-y += src/npu_hwc_lnx.o
npu-drv-y += src/npu_hwc_lnx_v2.o

ifneq ($(PLATFORM_CHIP_NAME),)
CHIP_NAME ?= $(PLATFORM_CHIP_NAME)
endif

CHIP_NAME ?= a00

subdir-ccflags-y += -DCHIP_NAME=\"$(CHIP_NAME)\"
subdir-ccflags-y += -DCHIP_NAME_$(CHIP_NAME)

ifeq ($(filter $(CHIP_NAME),o22 m23 o24),)
#subdir-ccflags-y += -DUSE_IOMMU
# TODO: remove after bringup period
subdir-ccflags-y += -DBRINGUP
endif

SRC := $(shell pwd)
npu_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

ccflags-y = -I$(KERNEL_SRC)/drivers/lg_kdriver/include
ccflags-y += -I$(npu_src_top)/include
ccflags-y += -I$(npu_src_top)/hw
ccflags-y += -I$(KERNEL_SRC)/drivers/lg_kdriver/core/base
ccflags-y += -I$(KERNEL_SRC)/drivers/lg_kdriver/core/hma
ccflags-y += -I$(KERNEL_SRC)/drivers/lg_kdriver/core/logm
ccflags-y += -I$(KERNEL_SRC)/drivers/lg_kdriver/core/pqepm

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules

modules_install:
	$(MAKE) -C $(KERNEL_SRC) M=$(SRC) modules_install

clean:
	rm -f *.o *~ core .depend .*.cmd *.ko *.mod.c
	rm -f Module.markers Module.symvers modules.order
	rm -rf .tmp_versions Modules.symvers
