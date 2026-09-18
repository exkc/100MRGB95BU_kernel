# SPDX-License-Identifier: GPL-2.0
#
# Makefile for Enhanced Kernel Protection (EKP) for ARMv8 AArch64
#

KASAN_SANITIZE := n

ccflags-y += -I$(src)
subdir-ccflags-y += -I$(src)

obj-y	+= init.o start.o tunnel.o romem.o
obj-y	+= fw/

obj-$(CONFIG_EKP_MODULE_PROTECTION)	+= module.o
obj-$(CONFIG_EKP_CRED_PROTECTION)	+= cred.o
obj-$(CONFIG_EKP_FAULT_NOTIFIER)	+= fault-notifier.o
obj-$(CONFIG_PROC_FS)	+= procfs.o
obj-$(CONFIG_EKP_DEBUG)	+= debug/
