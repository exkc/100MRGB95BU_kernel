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
#include <asm/io.h>			/**< For ioremap_nocache */

#include "sys_regs.h"
#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "demod_module.h"

#include "demod_util.h"

#include "demod_common_m23.h"
#include "demod_ipc_m23.h"

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



int DEMOD_M23_Get_UART(BOOLEAN *pStatus){
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

int DEMOD_M23_Set_UART(int enable){

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

int DEMOD_M23_Get_JTAG(BOOLEAN *pStatus){
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

int DEMOD_M23_Set_JTAG(int enable){

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

int DEMOD_M23_Get_Trace(char * pDbglog, int * pDbgidx){
#if defined(DEMOD_CHIP_NAME_o22)
	int dbgidx = 0;

	UINT32 pc;
	UINT32 data;
	UINT32 state;
	int ret;

	ret = DEMOD_L1_API_GetTrace(DEMOD_Get_LGDBB_Context()->demod, &pc, &data, &state);

	if (NO_DEMOD_ERROR == ret)
		dbgidx += sprintf(pDbglog + dbgidx, "Trace PC 0x%08X, DATA 0x%08X, State 0x%08X\n", pc, data, state);
	else
		DEMOD_ERROR("failed DEMOD_L1_API_GetTrace with %d\n", ret);

	*pDbgidx = dbgidx;
#endif
	return RET_OK;
}

int DEMOD_M23_Set_Trace(int enable){
#if defined(DEMOD_CHIP_NAME_o22)
	int ret;

	ret = DEMOD_L1_API_SetTrace(DEMOD_Get_LGDBB_Context()->demod, enable);

	DEMOD_NOTI("set trace %d ret %d\n", enable, ret);
	return ret;
#else
	return RET_OK;
#endif
}

static int _demod_o20_mcu_baudrate = 115200;

int DEMOD_M23_MCU_Set_UART(int enable){
	int ret = NO_DEMOD_ERROR;

#if defined(DEMOD_CHIP_NAME_o22)
	do {
		if (enable == TRUE)
			ret = DEMOD_L1_IPC_Send (DEMOD_Get_LGDBB_Context()->demod, CMD_TYPE_SYSTEM_UART_ON, 0, (char *)&_demod_o20_mcu_baudrate, sizeof(_demod_o20_mcu_baudrate));
		else
			ret = DEMOD_L1_IPC_Send (DEMOD_Get_LGDBB_Context()->demod, CMD_TYPE_SYSTEM_UART_OFF, 0, NULL, 0);
	} while (ret != NO_DEMOD_ERROR);

	DEMOD_INFO("send SYSTEM_UART_%s\n", ((enable == TRUE)? "ON" : "OFF"));
	do {
		ret = DEMOD_L1_IPC_Send_Count(DEMOD_Get_LGDBB_Context()->demod);
	} while (ret > 0);
	DEMOD_NOTI("send SYSTEM_UART_%s done\n", ((enable == TRUE)? "ON" : "OFF"));
#endif
	return ret;
}

int DEMOD_M23_MCU_Set_UART_Speed(int speed) {
	switch (speed) {
	case 115200:
	case 460800:
		_demod_o20_mcu_baudrate = speed;
		break;
	}
	DEMOD_M23_MCU_Set_UART(TRUE);

	return RET_OK;
}

int DEMOD_M23_MCU_Set_UART_HEX(int enable){
	int ret = NO_DEMOD_ERROR;

#if defined(DEMOD_CHIP_NAME_o22)
	do {
		ret = DEMOD_L1_IPC_Send (DEMOD_Get_LGDBB_Context()->demod, ((enable == TRUE)? CMD_TYPE_SYSTEM_HEX_ON : CMD_TYPE_SYSTEM_HEX_OFF), 0, NULL, 0);
	} while (ret != NO_DEMOD_ERROR);

	DEMOD_INFO("send SYSTEM_HEX_%s\n", ((enable == TRUE)? "ON" : "OFF"));
	do {
		ret = DEMOD_L1_IPC_Send_Count(DEMOD_Get_LGDBB_Context()->demod);
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
	PROC_ID_READ_REG,
	PROC_ID_WRITE_REG,
	PROC_ID_DUMP_REG,
	PROC_ID_MONITOR_REG,
	PROC_ID_OPTION,
	PROC_ID_FENCE,
	PROC_ID_MAX,
};

#define MAX_VALUE	0xFFFFFFFF
#define MAX_ADDRESS	0xFFFFFFFF

static OS_PROC_DESC_TABLE_T	_demod_chip_proc_table[] =
{
	{ "usage",			PROC_ID_USAGE,		OS_PROC_FLAG_READ},
	{ "test",			PROC_ID_TEST,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "read_reg",		PROC_ID_READ_REG,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "write_reg",		PROC_ID_WRITE_REG,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "dump_reg",		PROC_ID_DUMP_REG,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "monitor_reg",	PROC_ID_MONITOR_REG,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "option",			PROC_ID_OPTION,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "fence",			PROC_ID_FENCE,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ NULL, 			PROC_ID_MAX,		0}
};

static UINT32 _read_reg_addr = MAX_ADDRESS;
static UINT32 _dump_reg_addr = MAX_ADDRESS;
static UINT32 _dump_reg_size = MAX_ADDRESS;
static UINT32 _mon_reg_addrs[16] = { MAX_ADDRESS, };

static volatile UINT32 * _dbb_reg_map = NULL;
static UINT32 _dbb_reg_addr = M23_DBB_IP_TOP_BASE;
static UINT32 _dbb_reg_size = 0x6000;

static int _demod_chip_read_reg(UINT32 addr, UINT32 * data, int size) {
	addr = addr & 0xFFFF;
	size = (size + 3) & ~0x3;

	if (addr + size > _dbb_reg_size) {
		DEMOD_WARN("out of range, addr 0x%04x, size %u\n", addr, size);
		return RET_ERROR;
	}

	if (NULL == _dbb_reg_map) {
		_dbb_reg_map = (volatile UINT32 *)ioremap(_dbb_reg_addr, _dbb_reg_size);
		if (NULL == _dbb_reg_map) {
			DEMOD_ERROR("ioremap for dbb_reg failed\n");
			return RET_ERROR;
		}
	}

	memcpy(data, _dbb_reg_map + (addr >> 2), size);
	return RET_OK;
}

static int _demod_chip_write_reg(UINT32 addr, UINT32 data) {
	addr = addr & 0xFFFF;

	if (addr >= _dbb_reg_size) {
		DEMOD_WARN("out of range, addr 0x%04x\n", addr);
		return RET_ERROR;
	}

	if (NULL == _dbb_reg_map) {
		_dbb_reg_map = (volatile UINT32 *)ioremap(_dbb_reg_addr, _dbb_reg_size);
		if (NULL == _dbb_reg_map) {
			DEMOD_ERROR("ioremap for dbb_reg failed\n");
			return -1;
		}
	}

	*(_dbb_reg_map + (addr >> 2)) = data;
	return RET_OK;
}

/*----------------------------------------------------------------------------------------
	Static Function Implementation
----------------------------------------------------------------------------------------*/
static int _demod_chip_read_proc (UINT32 procId, char* buffer)
{
	LX_DEMOD_L2_Context *	pFrontend = DEMOD_Get_LGDBB_Context();

	int ret = 0;

	DEMOD_NOTI("procId %u\n", procId);

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_USAGE: {
			ret += sprintf(buffer + ret, 
					"* DEMOD_M23\n"
					"  - test\n"
				      );
		}
		break;

		case PROC_ID_TEST: {
			ret += sprintf(buffer + ret, 
					"* DEMOD_M23 test usage\n"
					"  - echo n > /proc/lg/demod/khal/test\n"
					"  - n value\n"
					"	1: kdrv -> mcu no recv test\n"
					"	2: kdrv -> mcu no resp test\n"
				      );
		}
		break;

		case PROC_ID_READ_REG: {
			UINT32 data = MAX_VALUE;
			UINT32 addr = _read_reg_addr;

			if (addr == MAX_ADDRESS)
			{
				printk("Input address is invalid. Please, Try again\n");
			}
			else
			{
				if (RET_OK != _demod_chip_read_reg(addr, &data, 4)) {
					DEMOD_ERROR("chip_read_reg failed, addr 0x%04x\n", addr);
					return -ERROR_DEMOD_READ;
				}
			}
			ret += sprintf(buffer + ret, "READ_REG addr = 0x%04x val = 0x%08x\n", addr, data);
		}
		break;

		case PROC_ID_DUMP_REG: {
			UINT32 value = MAX_VALUE;
			UINT32 addr = _dump_reg_addr;
			UINT32 size = _dump_reg_size;

			if (addr == MAX_ADDRESS || size == 0 || size == MAX_ADDRESS)
			{
				addr = 0x5300;
				size = 256;
				DEMOD_INFO("dump reg addr 0x%04x, size %u\n", addr, size);
			}
			
			{
				char dump[DEMOD_REGMAP_SIZE];
				
				UINT32 * wptr = (UINT32 *)dump;
				
				memset(dump, 0, DEMOD_REGMAP_SIZE);
	
				if (RET_OK != _demod_chip_read_reg(addr, wptr, size)) {
					DEMOD_ERROR("chip_read_reg failed, addr 0x%04x\n", addr);
					return -ERROR_DEMOD_READ;
				}
/*
				if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(pFrontend->demod->chip, addr, size, wptr))
					return -ERROR_DEMOD_READ;
*/				
				ret += SPRINTF(buffer + ret, "reg dump addr 0x%04x, size %u\n", addr, size);
				
				ret += DEMOD_DUMP_WORD(buffer + ret, wptr, size);
			}
			break;
		}

		case PROC_ID_OPTION: {
			break;
		}

		case PROC_ID_FENCE: {
			UINT32 fdi_size = 0;
			_demod_chip_read_reg(REG_ATSC3_FDI_SIZE, &fdi_size, 4);
			volatile UINT32 * fence_addr = (UINT32 *)vmap_phys(gMemCfgDEMOD.memory_base + fdi_size + 0x100000 - 32, 48);

			ret += SPRINTF(buffer + ret, "check fence \n");
			ret += SPRINTF(buffer + ret, "0x%08x: %08x %08x %08x %08x\n", gMemCfgDEMOD.memory_base + fdi_size + 0x100000 - 32, fence_addr[0], fence_addr[1], fence_addr[2], fence_addr[3]);
			ret += SPRINTF(buffer + ret, "0x%08x: %08x %08x %08x %08x\n", gMemCfgDEMOD.memory_base + fdi_size + 0x100000 - 16, fence_addr[4], fence_addr[5], fence_addr[6], fence_addr[7]);
			ret += SPRINTF(buffer + ret, "0x%08x: %08x %08x %08x %08x\n", gMemCfgDEMOD.memory_base + fdi_size + 0x100000 -  0, fence_addr[8], fence_addr[9], fence_addr[10], fence_addr[11]);
			vunmap_phys(fence_addr);
			break;
		}

		default:
			break;
	}

	return ret;
}

static int _demod_chip_write_proc (UINT32 procId, char* command)
{
	LX_DEMOD_L2_Context *	pFrontend = DEMOD_Get_LGDBB_Context();

	DEMOD_NOTI("procId %u, command %s\n", procId, command);

	switch(procId) 	{
		case PROC_ID_TEST: {
			int arg1;
			sscanf(command, " %d", &arg1);
			DEMOD_M23_IPC_Send(CMD_TYPE(CMD_MAJOR_TYPE_TEST, arg1), 0, NULL, 0);
		}
		break;

		case PROC_ID_WRITE_REG: {
			UINT32 addr = MAX_ADDRESS;
			UINT32 data = MAX_VALUE;

			sscanf( command, " %x %x", &addr, &data);
			DEMOD_NOTI("WRITE_REG addr 0x%x, data 0x%x\n", addr, data);

			if (addr == MAX_ADDRESS)
			{
				printk("Input value or address is invalid. Please, Try again\n");
			}
			else
			{
				if (RET_OK != _demod_chip_write_reg(addr, data)) {
					DEMOD_ERROR("chip_write_reg failed, addr 0x%04x\n", addr);
					return -ERROR_DEMOD_WRITE;
				}
/*
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, addr, 4, &data)) {
					DEMOD_ERROR("write_reg: error, addr 0x%04x, data 0x%08x\n", addr, data);
					return -ERROR_DEMOD_WRITE;
				}
*/
			}
		}
		break;

		case PROC_ID_READ_REG: {
			UINT32 addr = MAX_ADDRESS;

			sscanf( command, " %x", &addr);
			if (addr >= 0 && addr < 0x10000) {
				_read_reg_addr = addr;
				DEMOD_INFO("read_reg addr set as 0x%04x\n", addr);
			}
		}
		break;			

		case PROC_ID_DUMP_REG: {
			UINT32 addr = MAX_ADDRESS;
			UINT32 size = MAX_ADDRESS;

			sscanf( command, " %x %x",&addr, &size);
			if ((addr >= 0 && addr < 0x10000) && (size > 0 && size <= DEMOD_REGMAP_SIZE)) {
				_dump_reg_addr = addr;
				_dump_reg_size = size;
				DEMOD_INFO("dump_reg addr 0x%04x, size %u\n", addr, size);
			}
		}
		break;			

		case PROC_ID_OPTION: {
			UINT32 option = 0;

			sscanf(command, " %x", &option);
			DEMOD_INFO("chip opt 0x%0x\n", option);
		}

		case PROC_ID_FENCE: {
			UINT32 fdi_size = 0;
			_demod_chip_read_reg(REG_ATSC3_FDI_SIZE, &fdi_size, 4);

			UINT32 test = 0;
			sscanf(command, " %x", &test);

			volatile UINT32 * fence_addr = (UINT32 *)vmap_phys(gMemCfgDEMOD.memory_base + fdi_size + 0x100000 - 16, 16);
			DEMOD_INFO("test fence before ... %08x %08x %08x %08x\n", fence_addr[0], fence_addr[1], fence_addr[2], fence_addr[3]);
			fence_addr[0] = test;
			fence_addr[1] = test;
			fence_addr[2] = test;
			fence_addr[3] = test;
			DEMOD_INFO("test fence after ... %08x %08x %08x %08x\n", fence_addr[0], fence_addr[1], fence_addr[2], fence_addr[3]);
			wmb();
			vunmap_phys(fence_addr);
			break;
		}

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
		memset(_mon_reg_addrs, 0xFF, sizeof(_mon_reg_addrs));
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

