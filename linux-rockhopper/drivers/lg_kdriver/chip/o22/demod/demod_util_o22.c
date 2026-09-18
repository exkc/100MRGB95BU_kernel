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
#include "proc_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "demod_module.h"

#include "demod_util.h"

#include "demod_common_o22.h"
#include "demod_ipc_o22.h"

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



int DEMOD_O22_Get_UART(BOOLEAN *pStatus){
	int temp = 0;

#if 0 // for fpga Test
	CTOP_CTRL_O22Ax_RdFL(CTOP_ATG, uart_mux);
	CTOP_CTRL_O22Ax_Rd01(CTOP_ATG, uart_mux, reg_uart0_sel, temp);

	if (temp == _reg_uart0_sel_dbb)
		*pStatus = TRUE;
	else
		*pStatus = FALSE;
#endif	
	return RET_OK;
}

int DEMOD_O22_Set_UART(int enable){

#if 0 // for fpga Test
	int sel = ((enable == TRUE)? _reg_uart0_sel_dbb : 1);	// select DEMOD or CPU0
	int temp;

	CTOP_CTRL_O22Ax_RdFL(CTOP_ATG, uart_mux);
	CTOP_CTRL_O22Ax_Wr01(CTOP_ATG, uart_mux, reg_uart0_sel, sel);
	CTOP_CTRL_O22Ax_WrFL(CTOP_ATG, uart_mux);

	CTOP_CTRL_O22Ax_RdFL(CTOP_ATG, uart_mux);
	CTOP_CTRL_O22Ax_Rd01(CTOP_ATG, uart_mux, reg_uart0_sel, temp);
	DEMOD_NOTI("uart select %s(%d)\n", _reg_uart0_sel_names[temp % _reg_uart0_sel_nums], temp);
#endif

	return RET_OK;
}

int DEMOD_O22_Get_JTAG(BOOLEAN *pStatus){
	int temp = 0;
	
#if 0 // for fpga Test
	// sync shadow register (read from phy regs)
	CTOP_CTRL_O22Ax_RdFL(CTOP_ATG, jtag_mux);
	CTOP_CTRL_O22Ax_Rd01(CTOP_ATG, jtag_mux, reg_jtag0_sel, temp);

	if (temp == _reg_jtag0_sel_dbb)
		*pStatus = TRUE;
	else
		*pStatus = FALSE;
#endif
	return RET_OK;
}

int DEMOD_O22_Set_JTAG(int enable){

#if 0 // for fpga Test

	int sel = ((enable == TRUE)? _reg_jtag0_sel_dbb : 0);	// select DEMOD or CPU0
	int temp;

	CTOP_CTRL_O22Ax_RdFL(CTOP_ATG, jtag_mux);
	CTOP_CTRL_O22Ax_Wr01(CTOP_ATG, jtag_mux, reg_jtag0_sel, sel);
	CTOP_CTRL_O22Ax_WrFL(CTOP_ATG, jtag_mux);

	CTOP_CTRL_O22Ax_RdFL(CTOP_ATG, jtag_mux);
	CTOP_CTRL_O22Ax_Rd01(CTOP_ATG, jtag_mux, reg_jtag0_sel, temp);
	DEMOD_NOTI("jtag select %s(%d)\n", _reg_jtag0_sel_names[temp % _reg_jtag0_sel_nums], temp);
#endif

	return RET_OK;
}

int DEMOD_O22_Get_Trace(char * pDbglog, int * pDbgidx){
#if defined(DEMOD_CHIP_NAME_o22)
	int dbgidx = 0;

	UINT32 pc;
	UINT32 data;
	UINT32 state;
	int ret;

	ret = DEMOD_L1_API_GetTrace(DEMOD_O22_GetContext()->demod, &pc, &data, &state);

	if (NO_DEMOD_ERROR == ret)
		dbgidx += sprintf(pDbglog + dbgidx, "Trace PC 0x%08X, DATA 0x%08X, State 0x%08X\n", pc, data, state);
	else
		DEMOD_ERROR("failed DEMOD_L1_API_GetTrace with %d\n", ret);

	*pDbgidx = dbgidx;
#endif
	return RET_OK;
}

int DEMOD_O22_Set_Trace(int enable){
#if defined(DEMOD_CHIP_NAME_o22)
	int ret;

	ret = DEMOD_L1_API_SetTrace(DEMOD_O22_GetContext()->demod, enable);

	DEMOD_NOTI("set trace %d ret %d\n", enable, ret);
	return ret;
#else
	return RET_OK;
#endif
}

static int _demod_o20_mcu_baudrate = 115200;

int DEMOD_O22_MCU_Set_UART(int enable){
	int ret = NO_DEMOD_ERROR;

#if defined(DEMOD_CHIP_NAME_o22)
	do {
		if (enable == TRUE)
			ret = DEMOD_L1_IPC_Send (DEMOD_O22_GetContext()->demod, CMD_TYPE_SYSTEM_UART_ON, 0, (char *)&_demod_o20_mcu_baudrate, sizeof(_demod_o20_mcu_baudrate));
		else
			ret = DEMOD_L1_IPC_Send (DEMOD_O22_GetContext()->demod, CMD_TYPE_SYSTEM_UART_OFF, 0, NULL, 0);
	} while (ret != NO_DEMOD_ERROR);

	DEMOD_INFO("send SYSTEM_UART_%s\n", ((enable == TRUE)? "ON" : "OFF"));
	do {
		ret = DEMOD_L1_IPC_Send_Count(DEMOD_O22_GetContext()->demod);
	} while (ret > 0);
	DEMOD_NOTI("send SYSTEM_UART_%s done\n", ((enable == TRUE)? "ON" : "OFF"));
#endif
	return ret;
}

int DEMOD_O22_MCU_Set_UART_Speed(int speed) {
	switch (speed) {
	case 115200:
	case 460800:
		_demod_o20_mcu_baudrate = speed;
		break;
	}
	DEMOD_O22_MCU_Set_UART(TRUE);

	return RET_OK;
}

int DEMOD_O22_MCU_Set_UART_HEX(int enable){
	int ret = NO_DEMOD_ERROR;

#if defined(DEMOD_CHIP_NAME_o22)
	do {
		ret = DEMOD_L1_IPC_Send (DEMOD_O22_GetContext()->demod, ((enable == TRUE)? CMD_TYPE_SYSTEM_HEX_ON : CMD_TYPE_SYSTEM_HEX_OFF), 0, NULL, 0);
	} while (ret != NO_DEMOD_ERROR);

	DEMOD_INFO("send SYSTEM_HEX_%s\n", ((enable == TRUE)? "ON" : "OFF"));
	do {
		ret = DEMOD_L1_IPC_Send_Count(DEMOD_O22_GetContext()->demod);
	} while (ret > 0);
	DEMOD_NOTI("send SYSTEM_HEX_%s done\n", ((enable == TRUE)? "ON" : "OFF"));
#endif
	return ret;
}




/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_USAGE	= 0,
	PROC_ID_TEST,
	PROC_ID_MAX,
};

#define MAX_VALUE	0xFFFFFFFF
#define MAX_ADDRESS	0xFFFFFFFF

static OS_PROC_DESC_TABLE_T	_demod_chip_proc_table[] =
{
	{ "usage",			PROC_ID_USAGE,		OS_PROC_FLAG_READ},
	{ "test",			PROC_ID_TEST,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ NULL, 			PROC_ID_MAX,		0}
};

/*----------------------------------------------------------------------------------------
	Static Function Implementation
----------------------------------------------------------------------------------------*/
static int _demod_chip_read_proc (UINT32 procId, char* buffer)
{
	int ret = 0;

	DEMOD_NOTI("procId %u\n", procId);

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_USAGE:
			ret += sprintf(buffer + ret, 
					"* demod_o22\n"
					"  - test\n"
				      );
			break;
		case PROC_ID_TEST:
			ret += sprintf(buffer + ret, 
					"* demod_o22 test usage\n"
					"  - echo n > /proc/lg/demod/khal/test\n"
					"  - n value\n"
					"	1: kdrv -> mcu no recv test\n"
					"	2: kdrv -> mcu no resp test\n"
				      );
			break;
		default:
			break;
	}

	return ret;
}

static int _demod_chip_write_proc (UINT32 procId, char* command)
{
	int arg1;

	DEMOD_NOTI("procId %u, command %s\n", procId, command);

	switch(procId) 	{
		case PROC_ID_TEST:
			sscanf(command, " %d", &arg1);
			DEMOD_O22_IPC_Send(CMD_TYPE(CMD_MAJOR_TYPE_TEST, arg1), 0, NULL, 0);
			break;
		default:
			DEMOD_WARN("N/I procId\n");
			break;
	}

	return strlen(command);
}

extern struct proc_dir_entry * DEMOD_PROC_ENTRY;
static char * _proc_name = NULL;
static BOOL _proc_init = FALSE;

void DEMOD_CHIP_PROC_Init(void)
{
	if (FALSE == _proc_init) {
		_proc_name = (DEMOD_PROC_ENTRY == NULL) ? "demod_chip" : "chip";
		OS_PROC_CreateEntry(_proc_name, DEMOD_PROC_ENTRY, _demod_chip_proc_table,
						_demod_chip_read_proc,
						_demod_chip_write_proc);
		_proc_init = TRUE;
	}
}

void DEMOD_CHIP_PROC_cleanup(void)
{
	if (TRUE == _proc_init) {
		OS_PROC_RemoveEntry(_proc_name);
		_proc_name = NULL;
		_proc_init = FALSE;
	}
}

