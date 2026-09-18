lne_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

ifeq ($(PLATFORM_CHIP_NAME),m16p)
CHIP_NAME := m17
else
CHIP_NAME := $(PLATFORM_CHIP_NAME)
endif

#-------------------------------------------------------------------------------
# Driver source files
#-------------------------------------------------------------------------------
lne-objs           := driver.o

#-------------------------------------------------------------------------------
# Driver specific CFLAGS
#-------------------------------------------------------------------------------
lne-cflags	:= -I$(abspath $(lne_src_top))
lne-cflags	+= -I$(abspath $(lne_src_top)/../../chip)
lne-cflags	+= -I$(abspath $(lne_src_top)/../../include)
lne-cflags	+= -I$(abspath $(lne_src_top)/../base)
lne-cflags	+= -I$(abspath $(lne_src_top)/../sys)
lne-cflags	+= -I$(abspath $(lne_src_top)/../hma)
lne-cflags	+= -I$(abspath $(lne_src_top)/../logm)
lne-cflags	+= -DCHIP_NAME=\"$(CHIP_NAME)\"
lne-cflags	+= -DCHIP_NAME_$(CHIP_NAME)

#
# Etc
#
ccflags-y	+= $(lne-cflags)


ifeq ($(KDRV_MODULE_BUILD), YES)
CONFIG_LG_BUILTIN_KDRIVER := m
endif
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lne.o
obj-$(CONFIG_LG_BUILTIN_KDRIVER) += lne_pqe_ipc.o
