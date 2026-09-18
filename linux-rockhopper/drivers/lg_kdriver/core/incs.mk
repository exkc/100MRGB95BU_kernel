# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

#   ---------------------------------------------------------------------------#
#                                                                              #
#   FILE NAME   :   incs.mk                                                    #
#   VERSION     :   1.0                                                        #
#   AUTHOR      :   raxis.lim@lge.com                                          #
#   DATE        :                                                              #
#   DESCRIPTION :   Basic header files for kernel driver                       #
#                   see tools.mk and incs.mk in TV src directory               #
#******************************************************************************#

#==============================================================================
#
#   BUILD FLAGS
#
#==============================================================================
# if KDRV_GLOBAL_LINK is YES, the big one kernel module is created.
# if NO, all modules creates its own kernel module.
# default value is YES
KDRV_GLOBAL_LINK    ?= YES

# if you want to test a power management, set KDRV_CONFIG_PM to YES
# default value is NO
KDRV_CONFIG_PM      ?= YES

# enable debug feature
DEBUG               ?= y

SIC_LAB_BOARD       ?= NO

export KDRV_GLOBAL_LINK KDRV_CONFIG_PM DEBUG

#==============================================================================
# Global macro functions to define compiler directives
#------------------------------------------------------------------------------
#     1. Macro function cond_define(param1,param2)
#       This macro wll be expanded to
#           -Dparam2    <== If 'param2' has a same value with param1
#     2. Macro function cond_assign(param1,param2,param3,param4)
#       This macro wll be expanded to
#           param3      <== if 'param2' has a same value with param1
#           param4      <== otherwise
#
# cond_define = $(strip $(if $(subst $(strip $1)A,,$($(strip $2))A),,-D$(strip $2)))
# cond_assign = $(strip $(if $(subst $(strip $1)A,,$($(strip $2))A),$4,$3))
#==============================================================================
_cnd_define  = $(if $(subst $(1)A,,$(strip $($2))A),,-D$2)
_cnd_assign  = $(if $(subst $(1)A,,$(strip $($2))A),$4,$3)
cond_define  = $(call _cnd_define,$(strip $1),$(strip $2))
cond_assign  = $(call _cnd_assign,$(strip $1),$(strip $2),$(strip $3),$(strip $4))

#==============================================================================
# Chip Configuration
#
# by default, all chip driver shoule be enabled.
# if the specific driver is built for the mass production, only one driver should
# be enabled
#==============================================================================
INCLUDE_L8_CHIP_KDRV  := NO
INCLUDE_L9_CHIP_KDRV  := NO
INCLUDE_H13_CHIP_KDRV ?= NO
INCLUDE_M14_CHIP_KDRV ?= NO
INCLUDE_H14_CHIP_KDRV ?= NO
INCLUDE_H15_CHIP_KDRV ?= NO
INCLUDE_M16_CHIP_KDRV ?= NO
INCLUDE_M16P_CHIP_KDRV?= NO
INCLUDE_M17_CHIP_KDRV ?= NO
INCLUDE_O18_CHIP_KDRV ?= NO
INCLUDE_L18_CHIP_KDRV ?= NO
INCLUDE_M19_CHIP_KDRV ?= NO
INCLUDE_O20_CHIP_KDRV ?= NO
INCLUDE_E60_CHIP_KDRV ?= NO
INCLUDE_O22_CHIP_KDRV ?= YES
INCLUDE_M23_CHIP_KDRV ?= YES
INCLUDE_O24_CHIP_KDRV ?= YES
INCLUDE_O26_CHIP_KDRV ?= YES

ifeq ($(PLATFORM_CHIP_TYPE), FPGA)
INCLUDE_KDRV_VER_FPGA ?= YES
endif

