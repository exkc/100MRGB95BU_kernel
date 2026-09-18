/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 *  te chip reg functions
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2018-04-23
 *  @note		Additional information.
 */

#ifndef _TE_REG_M19_H_
#define _TE_REG_M19_H_

#include <lg1k/te/reg.h>

/* CTOP */
int M19_TE_REG_CTOP_SetInitValue(void);
int M19_TE_REG_SetCiInput(enum te_reg_ci_input src);
int M19_TE_REG_GetCiInput(enum te_reg_ci_input *src);
int M19_TE_REG_SetCiOutClk(enum te_reg_out_clk clk);
int M19_TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src);
int M19_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			    enum te_reg_tpo_mode mode, enum te_reg_out_clk clk);
int M19_TE_REG_GetDcoInputClock(u32 *freq);
int M19_TE_REG_SelectUart(enum te_reg_uart_type uart);
int M19_TE_REG_SelectJtag(enum te_reg_jtag_type jtag);
int M19_TE_REG_SetGlitchFreeFilter(bool en);

#endif				/* _TE_REG_M19_H_ */

/** @} */
