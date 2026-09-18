# SPDX-License-Identifier: GPL-2.0
# Rules for making the NTFS driver.

ifneq ($(KERNELRELEASE),)
obj-$(CONFIG_NTFS_FS) += ntfs.o

ntfs-y := aops.o attrib.o collate.o debug.o dir.o file.o \
	  index.o inode.o mft.o mst.o namei.o runlist.o super.o sysctl.o \
	  unistr.o upcase.o attrlist.o security.o bitmap.o lcnalloc.o \
	  logfile.o quota.o reparse.o ea.o compress.o ntfs_iomap.o

ccflags-y := -DNTFS_VERSION=\"4.3.00-90ba298-for-webos-5.4-v4.3.0-04\"
ccflags-$(CONFIG_NTFS_IOMAP_DEBUG)	+= -DDEBUG
else
# Called from external kernel module build

KERNELRELEASE	?= $(shell uname -r)
KDIR	?= /lib/modules/${KERNELRELEASE}/build
MDIR	?= /lib/modules/${KERNELRELEASE}
PWD	:= $(shell pwd)

export CONFIG_NTFS_FS := m

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

help:
	$(MAKE) -C $(KDIR) M=$(PWD) help

install: ntfs.ko
	rm -f ${MDIR}/kernel/fs/ntfs/ntfs.ko
	install -m644 -b -D ntfs.ko ${MDIR}/kernel/fs/ntfs/ntfs.ko
	depmod -aq

uninstall:
	rm -rf ${MDIR}/kernel/fs/ntfs
	depmod -aq

endif

.PHONY : all clean install uninstall
