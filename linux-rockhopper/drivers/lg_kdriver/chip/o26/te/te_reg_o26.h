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
 *  te chip reg functions(CTOP)
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#ifndef _TE_REG_O26_H_
#define _TE_REG_O26_H_

#ifdef INCLUDE_O26_CHIP_KDRV
#include <lg1k/te/reg.h>

/* CTOP */
int O26_TE_REG_CTOP_SetInitValue(void);
int O26_TE_REG_SetCiOutClk(enum te_reg_out_clk clk);
int O26_TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			    enum te_reg_tpo_mode mode, enum te_reg_out_clk clk);
int O26_TE_REG_SelectUart(enum te_reg_uart_type uart);
int O26_TE_REG_SelectJtag(enum te_reg_jtag_type jtag);
int O26_TE_REG_SetInputMux(enum te_reg_input_mux type);
int O26_TE_REG_ClockGate(bool disable);
#endif /* INCLUDE_O26_CHIP_KDRV */

#endif				/* _TE_REG_O26_H_ */

/** @} */
