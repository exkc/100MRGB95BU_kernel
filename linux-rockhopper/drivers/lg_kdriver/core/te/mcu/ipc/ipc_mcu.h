/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  ipc driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-02-03
 *  @note		Additional information.
 */

#ifndef _IPC_MCU_H_
#define _IPC_MCU_H_

#ifdef TE_EMULATOR
#define MCU_DATA_CACHED_ADDR		g_te_emul_mem_base
#define MCU_DATA_UNCACHED_ADDR		g_te_emul_mem_base
#else
#define MCU_DATA_CACHED_ADDR		0x60000000
#define MCU_DATA_UNCACHED_ADDR		0x80000000
#endif
#define MCU_DATA_USER_ADDR		0xA0000000

#define MCU_DATA_PREDEF0_ADDR		0x70000000
#define MCU_DATA_PREDEF1_ADDR		0x90000000
#define MCU_DATA_PREDEF2_ADDR		0xB0000000

#define MCU_SRAM_SLOT_SIZE		0x10000000
#define MCU_LEGACY_SRAM_SLOT_SIZE	0x20000000

/* MCU Register Offset */
#define MCU_REG_OFFSET_SROM_OFFSET	0x010
#define MCU_REG_OFFSET_SRAM_OFFSET_0	0x014
#define MCU_REG_OFFSET_SRAM_OFFSET_1	0x018
#define MCU_REG_OFFSET_SRAM_OFFSET_2	0x01C
#define MCU_REG_OFFSET_SRAM_OFFSET_3	0x0BC
#define MCU_REG_OFFSET_SRAM_OFFSET_4	0x0C0
#define MCU_REG_OFFSET_SRAM_OFFSET_5	0x0C4

#define MCU_REG_OFFSET_E_INTR_EN	0x030
#define MCU_REG_OFFSET_E_INTR_ST	0x034
#define MCU_REG_OFFSET_E_INTR_CL	0x038
#define MCU_REG_OFFSET_INTR2MCU_EV	0x03C
#define MCU_INTR_IPC_MASK			(0x1 << 0)
#define	MCU_EV_IPC_MASK				(0x1 << 0)

#define MCU_REG_OFFSET_IPC		0x100
#define MCU_REG_SIZE_IPC		0x100

#define MCU_REG_SIZE			0x200

/* max number of each items */
#define IPC_MSG_SEND_MSG_COUNT		8
#define IPC_MSG_RECV_MSG_COUNT		64	/* 256 * 64 = 16KB */

#define IPC_TS_CH_COUNT			8
#define IPC_FILTER_COUNT		256

#define IPC_ATSC3_FILTER_PLP_COUNT	8
#define IPC_ATSC3_FILTER_IP_COUNT       32
#define IPC_ATSC3_FILTER_LKS_COUNT      16
#define IPC_ATSC3_FILTER_UDP_COUNT      128
#define IPC_ATSC3_FILTER_CH_COUNT       3

#define IPC_CIPLUS_UP_CH_COUNT		3
#define IPC_CIPLUS_DN_CH_COUNT		3

#define IPC_ARIB2_FILTER_CH_COUNT	3
#define IPC_ARIB2_FILTER_TLV_COUNT      32
#define IPC_ARIB2_FILTER_IP_COUNT	3
#define IPC_ARIB2_FILTER_MMT_PID_COUNT	32
#define IPC_ARIB2_FILTER_MMT_SI_COUNT	64
#define IPC_ARIB2_FILTER_MMT_AV_COUNT	32

#endif				/* _IPC_MCU_H_ */
