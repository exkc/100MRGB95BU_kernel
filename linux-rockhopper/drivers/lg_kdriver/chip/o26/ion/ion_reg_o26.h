/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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
 *  ion chip reg functions(CTOP)
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-17
 *  @note	Additional information.
 */

#ifndef _ION_REG_O26_H_
#define _ION_REG_O26_H_

#ifdef INCLUDE_O26_CHIP_KDRV

#include <linux/types.h>

#define ION_TP_PKT_SIZE 0xbb

/* ION IO */
int O26_ION_IO_Set_ClockGate(u8 idx, u8 v);
int O26_ION_IO_Reset(u8 idx);
int O26_ION_IO_Set_mux(u8 tpi_num);
int O26_ION_IO_Set_ptg_cfg(void);
int O26_ION_IO_Set_ptg_pkt0(u8 tpi_num);
int O26_ION_IO_Set_align_cfg0(u8 tpi_num, u8 is_serial, u8 check_sop);
int O26_ION_IO_Set_start_code(u8 tpi_num, u8 tlv_en, u8 code);

u32 O26_ION_IO_reg_read(u32 addr);
int O26_ION_IO_reg_write(u32 addr, u32 val);

/* ION CI */
int O26_ION_CI_REG_SetInitValue(void);
int O26_ION_CI_Reset(void);
int O26_ION_CI_Reset_TP(bool assert);
int O26_ION_CI_Init_TP_Checker(u16 pkt_cnt);
int O26_ION_CI_Start_TP_Checker(u16 pkt_cnt, u16 *pkt, u16 *err);

/* Pro:Idiom specific APIs */
int O26_ION_IO_Set_tpi_mux(u8 tpi_num, u8 val);
int O26_ION_CI_Set_tpo_mode(u8 is_serial);

#endif /* INCLUDE_O26_CHIP_KDRV */
#endif	/* _ION_REG_O26_H_ */

/** @} */
