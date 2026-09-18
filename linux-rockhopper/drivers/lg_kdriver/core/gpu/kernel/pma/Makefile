
gpu_pma_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

ifeq ($(KDRV_MODULE_BUILD), YES)
CONFIG_LG_BUILTIN_KDRIVER := m
endif

GPU_PMA-o24 := $(CONFIG_LG_BUILTIN_KDRIVER)
GPU_PMA := $(GPU_PMA-$(PLATFORM_CHIP_NAME))
obj-$(GPU_PMA) += pma_hma.o

ccflags-y += -I$(gpu_pma_src_top)/../$(GPU_RELEASE)/include
ccflags-y += -I$(gpu_pma_src_top)/../../../hma

