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
 *  sdec driver
 *
 *  @author	Kyungseok Hyun
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#include "te_impl.h"
#include "te_reg_ctrl.h"

#ifdef INCLUDE_O20_CHIP_KDRV
#include "o20/te/te_reg_o20.h"
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#include "e60/te/te_reg_e60.h"
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#include "o22/te/te_reg_o22.h"
#endif
// M23 TPI swapped; see SICDTV-10480 for details
#ifdef INCLUDE_M23_CHIP_KDRV
#include "m23/te/te_reg_m23.h"
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#include "o24/te/te_reg_o24.h"
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
#include "o26/te/te_reg_o26.h"
#endif

#if CONFIG_LX_BOARD_FPGA || defined(TE_EMULATOR)
#define NO_CTOP
#endif

#ifdef NO_CTOP
#define HAL_FUNC(func, ...)		(0)
#else
#define HAL_FUNC(func, ...)				\
({							\
	int __ret;					\
	if (hal_func && hal_func->func)			\
		__ret = hal_func->func(__VA_ARGS__);	\
	else						\
		__ret = -EPERM;				\
	__ret;						\
})
#endif


typedef struct {
	int (*Init)(void);

	int (*SetInitValue)(void);
	int (*SetCiInput)(enum te_reg_ci_input src);
	int (*GetCiInput)(enum te_reg_ci_input *src);
	int (*SetCiOutClk)(enum te_reg_out_clk clk);
	int (*SetInOutPort)(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			    enum te_reg_tpo_mode mode, enum te_reg_out_clk clk);
	int (*SetStccClockSource)(u8 ch, enum te_reg_stcc_src src);
	int (*GetDcoInputClock)(u32 *freq);

	int (*SelectUart)(enum te_reg_uart_type uart);
	int (*SelectJtag)(enum te_reg_jtag_type jtag);
	int (*SetGlitchFreeFilter)(bool en);
	int (*SetInputMux)(enum te_reg_input_mux type);
	int (*ClockGate)(bool disable);
} HAL_FUNC_T;

#ifndef NO_CTOP
#ifdef INCLUDE_O20_CHIP_KDRV
static const HAL_FUNC_T hal_func_o20 = {
	.SetInitValue = O20_TE_REG_CTOP_SetInitValue,
	.SetCiInput = te_reg_set_ci_input,
	.GetCiInput = te_reg_get_ci_input,
	.SetCiOutClk = O20_TE_REG_SetCiOutClk,
	.SetInOutPort = O20_TE_REG_SetInOutPort,
	.SetStccClockSource = O20_TE_REG_SetStccClockSource,
	.GetDcoInputClock = O20_TE_REG_GetDcoInputClock,
	.SelectUart = O20_TE_REG_SelectUart,
	.SelectJtag = O20_TE_REG_SelectJtag,
	.SetGlitchFreeFilter = O20_TE_REG_SetGlitchFreeFilter,
	.SetInputMux = O20_TE_REG_SetInputMux,
};
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
static const HAL_FUNC_T hal_func_e60 = {
	.SetInitValue = E60_TE_REG_CTOP_SetInitValue,
	.SetCiInput = te_reg_set_ci_input,
	.GetCiInput = te_reg_get_ci_input,
	.SetCiOutClk = E60_TE_REG_SetCiOutClk,
	.SetInOutPort = E60_TE_REG_SetInOutPort,
	.SetStccClockSource = E60_TE_REG_SetStccClockSource,
	.GetDcoInputClock = E60_TE_REG_GetDcoInputClock,
	.SelectUart = E60_TE_REG_SelectUart,
	.SelectJtag = E60_TE_REG_SelectJtag,
	.SetGlitchFreeFilter = E60_TE_REG_SetGlitchFreeFilter,
	.SetInputMux = E60_TE_REG_SetInputMux,
};
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
static const HAL_FUNC_T hal_func_o22 = {
	.SetInitValue = O22_TE_REG_CTOP_SetInitValue,
	.SetCiInput = te_reg_set_ci_input,
	.GetCiInput = te_reg_get_ci_input,
	.SetCiOutClk = O22_TE_REG_SetCiOutClk,
	.SetInOutPort = O22_TE_REG_SetInOutPort,
	.SetStccClockSource = O22_TE_REG_SetStccClockSource,
	.GetDcoInputClock = O22_TE_REG_GetDcoInputClock,
	.SelectUart = O22_TE_REG_SelectUart,
	.SelectJtag = O22_TE_REG_SelectJtag,
	.SetGlitchFreeFilter = O22_TE_REG_SetGlitchFreeFilter,
	.SetInputMux = O22_TE_REG_SetInputMux,
	.ClockGate = O22_TE_REG_ClockGate,
};
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
static const HAL_FUNC_T hal_func_m23 = {
	.SetInitValue = M23_TE_REG_CTOP_SetInitValue,
	.SetCiInput = te_reg_set_ci_input,
	.GetCiInput = te_reg_get_ci_input,
	.SetCiOutClk = M23_TE_REG_SetCiOutClk,
	.SetInOutPort = M23_TE_REG_SetInOutPort,
	.SelectUart = M23_TE_REG_SelectUart,
	.SelectJtag = M23_TE_REG_SelectJtag,
	.SetInputMux = M23_TE_REG_SetInputMux,
	.ClockGate = M23_TE_REG_ClockGate,
};
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
static const HAL_FUNC_T hal_func_o24 = {
	.SetInitValue = O24_TE_REG_CTOP_SetInitValue,
	.SetCiInput = te_reg_set_ci_input,
	.GetCiInput = te_reg_get_ci_input,
	.SetCiOutClk = O24_TE_REG_SetCiOutClk,
	.SetInOutPort = O24_TE_REG_SetInOutPort,
	.SelectUart = O24_TE_REG_SelectUart,
	.SelectJtag = O24_TE_REG_SelectJtag,
	.SetInputMux = O24_TE_REG_SetInputMux,
	.ClockGate = O24_TE_REG_ClockGate,
};
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
static const HAL_FUNC_T hal_func_o26 = {
	.SetInitValue = O26_TE_REG_CTOP_SetInitValue,
	.SetCiInput = te_reg_set_ci_input,
	.GetCiInput = te_reg_get_ci_input,
	.SetCiOutClk = O26_TE_REG_SetCiOutClk,
	.SetInOutPort = O26_TE_REG_SetInOutPort,
	.SelectUart = O26_TE_REG_SelectUart,
	.SelectJtag = O26_TE_REG_SelectJtag,
	.SetInputMux = O26_TE_REG_SetInputMux,
	.ClockGate = O26_TE_REG_ClockGate,
};
#endif

static const HAL_FUNC_T *hal_func;

#endif				//NO_CTOP


int TE_REG_CTOP_Init(void)
{
#ifdef NO_CTOP
	return 0;
#else
	switch (lx_chip()) {
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
		hal_func = &hal_func_o26;
		break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
		hal_func = &hal_func_o24;
		break;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
		hal_func = &hal_func_m23;
		break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	case LX_CHIP_O22:
		hal_func = &hal_func_o22;
		break;
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	case LX_CHIP_E60:
		hal_func = &hal_func_e60;
		break;
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	case LX_CHIP_O20:
		hal_func = &hal_func_o20;
		break;
#endif
	default:
		panic("not implemented CTOP 0x%x\n", lx_chip());
	}

	if (hal_func->Init)
		return hal_func->Init();

	return 0;
#endif
};

int TE_REG_CTOP_SetInitValue(void)
{
	return HAL_FUNC(SetInitValue);
}

int TE_REG_SetCiInput(enum te_reg_ci_input src)
{
	return HAL_FUNC(SetCiInput, src);
}

int TE_REG_GetCiInput(enum te_reg_ci_input *src)
{
#ifdef NO_CTOP
	*src = CI_INPUT_SRC_NONE;
	return 0;
#else
	return HAL_FUNC(GetCiInput, src);
#endif
}

int TE_REG_SetCiOutClk(enum te_reg_out_clk clk)
{
	return HAL_FUNC(SetCiOutClk, clk);
}

int TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src)
{
	return HAL_FUNC(SetStccClockSource, ch, src);
}

int TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			enum te_reg_tpo_mode mode, enum te_reg_out_clk clk)
{
	return HAL_FUNC(SetInOutPort, port, dir, mode, clk);
}

int TE_REG_GetDcoInputClock(u32 *freq)
{
#ifdef NO_CTOP
	*freq = 200;		/* temporal value - no DCO in FPGA */
	return 0;
#else
	return HAL_FUNC(GetDcoInputClock, freq);
#endif
}

int TE_REG_SelectUart(enum te_reg_uart_type uart)
{
	return HAL_FUNC(SelectUart, uart);
}

int TE_REG_SelectJtag(enum te_reg_jtag_type jtag)
{
	return HAL_FUNC(SelectJtag, jtag);
}

//FIXME: maybe deprecated
int TE_REG_SetGlitchFreeFilter(bool en)
{
	return HAL_FUNC(SetGlitchFreeFilter, en);
}

int TE_REG_SetInputMux(enum te_reg_input_mux type)
{
	return HAL_FUNC(SetInputMux, type);
}

int TE_REG_ClockGate(bool disable)
{
	struct te_config *cfg = te_get_config();

	if (cfg->reg_clock_gate) {
		log_noti("register %s", disable ? "gated" : "recovered");
		return HAL_FUNC(ClockGate, disable);
	} else {
		log_noti("register %s (no reg access)", disable ? "gated" :
								  "recovered");
		return 0;
	}
}

