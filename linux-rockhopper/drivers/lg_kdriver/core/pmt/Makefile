pmt_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))

obj-m := pmt.o
pmt-objs := pmt_drv.o
ccflags-y += -I$(KDRV_INC_DIR)
ccflags-y += -I$(pmt_src_top)/../../include

EXTRA_CFLAGS += -I$(KDRV_INC_DIR)
EXTRA_CFLAGS += -I$(pmt_src_top)
EXTRA_CFLAGS += -I$(pmt_src_top)/../../include

