/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013-2019 by LG Electronics Inc.
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


/*  @file
 *
 *	demod utils for o20
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-06-12
 *	@note
 */
#define DEMOD_TAG "[CHIP.UTIL] "

#include <linux/kernel.h>	/**< printk() */
#include <linux/types.h> 	/**< size_t */

#include "sys_regs.h"
#include "os_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "demod_module.h"

#include "demod_util.h"

#include "demod_common_o20.h"

static char * _reg_uart0_sel_names[] = {"TZ", "CPU0", "CPU1", "PQE", "HDMI", "VDEC", "TE", "CPU2", "DEMOD", "PQE", "MICOM"};
static int _reg_uart0_sel_nums = sizeof(_reg_uart0_sel_names) / sizeof(char *);
//static int _reg_uart0_sel = 0;
static const int _reg_uart0_sel_dbb = 8;

/*
static char * _reg_uart1_sel_names[] = {"CPU0", "TZ", "CPU1", "PQE", "HDMI", "VDEC", "TE", "CPU2", "DEMOD", "PQE", "MICOM"};
static int _reg_uart1_sel_nums = sizeof(_reg_uart1_sel_names) / sizeof(char *);
*/
static char * _reg_jtag0_sel_names[] = {"CPU", "PQE", "VDEC", "TE0", "TE1", "BMC", "PQE1", "PQE2", "DEMOD"};
static int _reg_jtag0_sel_nums = sizeof(_reg_jtag0_sel_names) / sizeof(char *);
//static int _reg_jtag0_sel = 0;
static const int _reg_jtag0_sel_dbb = 5;



int DEMOD_O20_Get_UART(BOOLEAN *pStatus){
	int temp = 0;

	CTOP_CTRL_O20Ax_RdFL(CTOP_ATG, uart_mux);
	CTOP_CTRL_O20Ax_Rd01(CTOP_ATG, uart_mux, reg_uart0_sel, temp);

	if (temp == _reg_uart0_sel_dbb)
		*pStatus = TRUE;
	else
		*pStatus = FALSE;
	
	return RET_OK;
}

int DEMOD_O20_Set_UART(int enable){
	int sel = ((enable == TRUE)? _reg_uart0_sel_dbb : 1);	// select DEMOD or CPU0
	int temp;

	CTOP_CTRL_O20Ax_RdFL(CTOP_ATG, uart_mux);
	CTOP_CTRL_O20Ax_Wr01(CTOP_ATG, uart_mux, reg_uart0_sel, sel);
	CTOP_CTRL_O20Ax_WrFL(CTOP_ATG, uart_mux);

	CTOP_CTRL_O20Ax_RdFL(CTOP_ATG, uart_mux);
	CTOP_CTRL_O20Ax_Rd01(CTOP_ATG, uart_mux, reg_uart0_sel, temp);
	DEMOD_NOTI("uart select %s(%d)\n", _reg_uart0_sel_names[temp % _reg_uart0_sel_nums], temp);

	return RET_OK;
}

int DEMOD_O20_Get_JTAG(BOOLEAN *pStatus){
	int temp = 0;

	// sync shadow register (read from phy regs)
	CTOP_CTRL_O20Ax_RdFL(CTOP_ATG, jtag_mux);
	CTOP_CTRL_O20Ax_Rd01(CTOP_ATG, jtag_mux, reg_jtag0_sel, temp);

	if (temp == _reg_jtag0_sel_dbb)
		*pStatus = TRUE;
	else
		*pStatus = FALSE;

	return RET_OK;
}

int DEMOD_O20_Set_JTAG(int enable){
	int sel = ((enable == TRUE)? _reg_jtag0_sel_dbb : 0);	// select DEMOD or CPU0
	int temp;

	CTOP_CTRL_O20Ax_RdFL(CTOP_ATG, jtag_mux);
	CTOP_CTRL_O20Ax_Wr01(CTOP_ATG, jtag_mux, reg_jtag0_sel, sel);
	CTOP_CTRL_O20Ax_WrFL(CTOP_ATG, jtag_mux);

	CTOP_CTRL_O20Ax_RdFL(CTOP_ATG, jtag_mux);
	CTOP_CTRL_O20Ax_Rd01(CTOP_ATG, jtag_mux, reg_jtag0_sel, temp);
	DEMOD_NOTI("jtag select %s(%d)\n", _reg_jtag0_sel_names[temp % _reg_jtag0_sel_nums], temp);

	return RET_OK;
}

int DEMOD_O20_Get_Trace(char * pDbglog, int * pDbgidx){
#if defined(DEMOD_CHIP_NAME_o20)
	int dbgidx = 0;

	UINT32 pc;
	UINT32 data;
	UINT32 state;
	int ret;

	ret = DEMOD_L1_API_GetTrace(DEMOD_O20_GetContext()->demod, &pc, &data, &state);

	if (NO_DEMOD_ERROR == ret)
		dbgidx += sprintf(pDbglog + dbgidx, "Trace PC 0x%08X, DATA 0x%08X, State 0x%08X\n", pc, data, state);
	else
		DEMOD_ERROR("failed DEMOD_L1_API_GetTrace with %d\n", ret);

	*pDbgidx = dbgidx;
#endif
	return RET_OK;
}

int DEMOD_O20_Set_Trace(int enable){
#if defined(DEMOD_CHIP_NAME_o20)
	int ret;

	ret = DEMOD_L1_API_SetTrace(DEMOD_O20_GetContext()->demod, enable);

	DEMOD_NOTI("set trace %d ret %d\n", enable, ret);
	return ret;
#else
	return RET_OK;
#endif
}

static int _demod_o20_mcu_baudrate = 115200;

int DEMOD_O20_MCU_Set_UART(int enable){
	int ret = NO_DEMOD_ERROR;

#if defined(DEMOD_CHIP_NAME_o20)
	do {
		if (enable == TRUE)
			ret = DEMOD_L1_IPC_Send (DEMOD_O20_GetContext()->demod, CMD_TYPE_SYSTEM_UART_ON, 0, (char *)&_demod_o20_mcu_baudrate, sizeof(_demod_o20_mcu_baudrate));
		else
			ret = DEMOD_L1_IPC_Send (DEMOD_O20_GetContext()->demod, CMD_TYPE_SYSTEM_UART_OFF, 0, NULL, 0);
	} while (ret != NO_DEMOD_ERROR);

	DEMOD_INFO("send SYSTEM_UART_%s\n", ((enable == TRUE)? "ON" : "OFF"));
	do {
		ret = DEMOD_L1_IPC_Send_Count(DEMOD_O20_GetContext()->demod);
	} while (ret > 0);
	DEMOD_NOTI("send SYSTEM_UART_%s done\n", ((enable == TRUE)? "ON" : "OFF"));
#endif
	return ret;
}

int DEMOD_O20_MCU_Set_UART_Speed(int speed) {
	switch (speed) {
	case 115200:
	case 460800:
		_demod_o20_mcu_baudrate = speed;
		break;
	}
	DEMOD_O20_MCU_Set_UART(TRUE);

	return RET_OK;
}

int DEMOD_O20_MCU_Set_UART_HEX(int enable){
	int ret = NO_DEMOD_ERROR;

#if defined(DEMOD_CHIP_NAME_o20)
	do {
		ret = DEMOD_L1_IPC_Send (DEMOD_O20_GetContext()->demod, ((enable == TRUE)? CMD_TYPE_SYSTEM_HEX_ON : CMD_TYPE_SYSTEM_HEX_OFF), 0, NULL, 0);
	} while (ret != NO_DEMOD_ERROR);

	DEMOD_INFO("send SYSTEM_HEX_%s\n", ((enable == TRUE)? "ON" : "OFF"));
	do {
		ret = DEMOD_L1_IPC_Send_Count(DEMOD_O20_GetContext()->demod);
	} while (ret > 0);
	DEMOD_NOTI("send SYSTEM_HEX_%s done\n", ((enable == TRUE)? "ON" : "OFF"));
#endif
	return ret;
}

