demod_src_top := $(if $(filter /%,$(src)),$(src),$(srctree)/$(src))



obj-m 			:= demod_khal.o
demod_khal-objs	:= khal_drv.o
demod_khal-objs	+= khal_core.o
demod_khal-objs	+= khal_proc.o


ccflags-y		+= -I$(abspath $(demod_src_top)/)
ccflags-y		+= -I$(abspath $(demod_src_top)/../../demod)
ccflags-y		+= -I$(abspath $(demod_src_top)/../../i2c)
ccflags-y		+= -I$(abspath $(demod_src_top)/../../../include)
ccflags-y		+= -I$(abspath $(demod_src_top)/../../base)
ccflags-y		+= -I$(abspath $(demod_src_top)/../../../chip)