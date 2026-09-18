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
#include <linux/io.h> // for adding memcpy_fromio 
#include <asm/io.h>			/**< For ioremap_nocache */

//#include "sys_regs.h"  //chungiii
#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "demod_module.h"

#include "demod_util.h"

#include "demod_common_o26.h"
#include "demod_ipc_o26.h"
#include "demod_util_o26.h"

int DEMOD_O26_Get_UART(BOOLEAN *pStatus){
	return RET_OK;
}

int DEMOD_O26_Set_UART(int enable){
	return RET_OK;
}

int DEMOD_O26_Get_JTAG(BOOLEAN *pStatus){
	return RET_OK;
}

int DEMOD_O26_Set_JTAG(int enable){
	return RET_OK;
}

int DEMOD_O26_Get_Trace(char * pDbglog, int * pDbgidx){
	return RET_OK;
}

int DEMOD_O26_Set_Trace(int enable){
	return RET_OK;
}

int DEMOD_O26_MCU_Set_UART(int enable){
	return RET_OK;
}

int DEMOD_O26_MCU_Set_UART_Speed(int speed) {
	return RET_OK;
}

int DEMOD_O26_MCU_Set_UART_HEX(int enable){
	return RET_OK;
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
	PROC_ID_PROP_MODE,
	PROC_ID_POWER_SAVE,
	PROC_ID_SW_RESET,
	PROC_ID_MAX,
};

#define MAX_VALUE	0xFFFFFFFF
#define MAX_ADDRESS	0xFFFFFFFF

static OS_PROC_DESC_TABLE_T	_demod_chip_proc_table[] =
{
	{ "usage",		PROC_ID_USAGE,		OS_PROC_FLAG_READ},
	{ "test",		PROC_ID_TEST,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "read_reg",		PROC_ID_READ_REG,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "write_reg",		PROC_ID_WRITE_REG,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "dump_reg",		PROC_ID_DUMP_REG,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "monitor_reg",	PROC_ID_MONITOR_REG,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "option",		PROC_ID_OPTION,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "prop_mode",		PROC_ID_PROP_MODE,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "power_save",		PROC_ID_POWER_SAVE,	OS_PROC_FLAG_WRITE},
	{ "sw_reset",		PROC_ID_SW_RESET,	OS_PROC_FLAG_WRITE},
	{ NULL, 		PROC_ID_MAX,		0}
};

static UINT32 _read_reg_addr = MAX_ADDRESS;
static UINT32 _dump_reg_addr = MAX_ADDRESS;
static UINT32 _dump_reg_size = MAX_ADDRESS;
static UINT32 _mon_reg_addrs[16] = { MAX_ADDRESS, };

static volatile UINT32 * _dbb_reg_map = NULL;
static UINT32 _dbb_reg_addr = O26_DBB_IP_BASE;
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

	
	//memcpy(data, _dbb_reg_map + (addr >> 2), size);
	memcpy_fromio(data, _dbb_reg_map + (addr >> 2), size); // memcpy -> memcpy_fromio
	
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
					"* DEMOD_O26\n"
					"  - test\n"
				      );
		}
		break;

		case PROC_ID_TEST: {
			ret += sprintf(buffer + ret,
					"* DEMOD_O26 test usage\n"
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
				if (0xff00 == (addr & 0x0000ff00)) {
					// virtual register
					if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(pFrontend->demod->chip, addr, 4, &data)) {
						DEMOD_ERROR("chip_read_reg failed, virt addr 0x%04x\n", addr);
						return -ERROR_DEMOD_READ;
					}
					ret += sprintf(buffer + ret, "READ_REG virt addr = 0x%04x val = 0x%08x\n", addr, data);
				} else {
					if (RET_OK != _demod_chip_read_reg(addr, &data, 4)) {
						DEMOD_ERROR("chip_read_reg failed, direct addr 0x%04x\n", addr);
						return -ERROR_DEMOD_READ;
					}
					ret += sprintf(buffer + ret, "READ_REG direct addr = 0x%04x val = 0x%08x\n", addr, data);
				}
			}

		}
		break;

		case PROC_ID_DUMP_REG: {
			//UINT32 value = MAX_VALUE;
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

				ret += SPRINTF(buffer + ret, "reg dump addr 0x%04x, size %u\n", addr, size);

				ret += DEMOD_DUMP_WORD(buffer + ret, wptr, size);
			}
			break;
		}

		case PROC_ID_OPTION: {
			break;
		}

		case PROC_ID_PROP_MODE: {
			//int retc = NO_DEMOD_ERROR;

			if (NO_DEMOD_ERROR != DEMOD_L2_Get_Property(pFrontend, DEMOD_PROP_MODE_CODE)) {
				DEMOD_NOTI("FAIL, DEMOD_L2_Get_Property()\n");
				ret += SPRINTF(buffer + ret, "get prop mode failed\n");
			}

			ret += SPRINTF(buffer + ret, "get prop mode (0x%02x)\n", pFrontend->demod->prop->dd_mode.modulation);
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
			DEMOD_O26_IPC_Send(CMD_TYPE(CMD_MAJOR_TYPE_TEST, arg1), 0, NULL, 0);
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
				if (0xff00 == (addr & 0x0000ff00)) {
					// virtual register
					if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, addr, 4, &data)) {
						DEMOD_ERROR("chip_read_reg failed, virt addr 0x%04x\n", addr);
						return -ERROR_DEMOD_WRITE;
					}
					DEMOD_NOTI("WRITE_REG virt addr = 0x%04x val = 0x%08x\n", addr, data);
				} else {
					if (RET_OK != _demod_chip_write_reg(addr, data)) {
						DEMOD_ERROR("chip_write_reg failed, direct addr 0x%04x\n", addr);
						return -ERROR_DEMOD_WRITE;
					}
					DEMOD_NOTI("WRITE_REG direct addr = 0x%04x val = 0x%08x\n", addr, data);
				}
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
		break;

		case PROC_ID_PROP_MODE: {
			int retc = NO_DEMOD_ERROR;
			UINT32 opmode = 0;
			sscanf(command, " %x", &opmode);

			switch (opmode) {
			case DEMOD_MODULATION_VSB:
			case DEMOD_MODULATION_QAM:
			case DEMOD_MODULATION_ATSC3:
			case DEMOD_MODULATION_ISDBT:
			case DEMOD_MODULATION_ISDBC:
			case DEMOD_MODULATION_DVBT:
			case DEMOD_MODULATION_DVBT2:
			case DEMOD_MODULATION_DVBC:
			case DEMOD_MODULATION_DVBC2:
			case DEMOD_MODULATION_DVBS:
			case DEMOD_MODULATION_DVBS2:
			case DEMOD_MODULATION_DVBS2X:
			case DEMOD_MODULATION_DTMB:
			case DEMOD_MODULATION_SLEEP:
				DEMOD_NOTI("forced set_prop mode as (0x%02x)\n", opmode);
				pFrontend->demod->propertyWriteMode = DEMOD_DD_DOWNLOAD_ALWAYS;
				pFrontend->demod->prop->dd_mode.modulation = opmode;
				retc = DEMOD_L2_Set_Property(pFrontend, DEMOD_PROP_MODE_CODE);
				pFrontend->demod->propertyWriteMode = DEMOD_DD_DOWNLOAD_ON_CHANGE;
				if (NO_DEMOD_ERROR != retc) {
					DEMOD_NOTI("FAIL, DEMOD_L2_Set_Property()\n");
				}
				break;
			default:
				DEMOD_NOTI("unknown mode prop (0x%02x)\n", opmode);
				break;
			}

			break;
		}

		case PROC_ID_POWER_SAVE: {
			UINT32 onoff = 0;
			sscanf(command, " %x", &onoff);

			if (onoff) {
				DEMOD_NOTI("forced enter power_save\n");
				if (NO_DEMOD_ERROR != DEMOD_L2_Standby(pFrontend)) {
					DEMOD_NOTI("FAIL, DEMOD_L2_Standby()\n");
				}
			} else {
				DEMOD_NOTI("forced leave power_save\n");
				if (NO_DEMOD_ERROR != DEMOD_L2_WakeUp(pFrontend)) {
					DEMOD_NOTI("FAIL, DEMOD_L2_WakeUp()\n");
				}
			}
			break;
		}

		case PROC_ID_SW_RESET: {
			UINT32 reset_arg = 0;
			sscanf(command, " %x", &reset_arg);

			DEMOD_NOTI("forced sw reset\n");
			DEMOD_L2_Set_SoftRst(pFrontend, 1, 0, 0, 0, 0, 0, 0);
		}
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

