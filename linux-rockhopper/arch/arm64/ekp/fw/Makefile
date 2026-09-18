# SPDX-License-Identifier: GPL-2.0

obj-y	+= fw-init.o
obj-y	+= ekp-fw.o

file := $(strip $(subst $(quote),,$(CONFIG_EKP_ISE_FIRMWARE)))

ifneq ($(file),)
firmware := $(file)
endif

ifdef firmware

ifneq ($(patsubst /%,,$(firmware)),)
firmware := $(strip $(srctree)/$(firmware))
endif

ifneq ($(wildcard $(firmware)),)
AFLAGS_ekp-fw.o += -DEKP_FW_IMAGE='"$(firmware)"'
quiet_fw_info = echo '  WITH    $@'
else
quiet_fw_info = echo '  WITHOUT $@'
endif

silent_fw_info = :
       fw_info = :

$(firmware): FORCE
	@$($(quiet)fw_info)

$(obj)/ekp-fw.o: $(firmware)

endif # firmware
