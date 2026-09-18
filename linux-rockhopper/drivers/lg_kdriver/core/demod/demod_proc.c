/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file
 *
 *  Linux proc interface for demod device.
 *	demod device will teach you how to make device driver with new platform.
 *
 *  author		jeongpil.yun (jeongpil.yun@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define DEMOD_TAG "[CORE.PROC] "

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

//#include "sys_regs.h"  //chungiii fpga
#include "demod_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#if defined(DEMOD_CONFIG_LGDBB_IPC)
#include "demod_util.h"
#endif
#include "demod_module.h"
#include "demod_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_COMMAND,
	PROC_ID_PROPERTY,
	PROC_ID_POWER_SAVE,
	PROC_ID_API,
	PROC_ID_IPC,
	PROC_ID_DUMP,
	PROC_ID_UART,
	PROC_ID_JTAG,
	PROC_ID_TRACE,
	PROC_ID_FW,
	PROC_ID_READ_REGISTER,
	PROC_ID_WRITE_REGISTER,
	PROC_ID_DEBUG,
	PROC_ID_SIG_STATUS,
	PROC_ID_REG_STATUS,
	PROC_ID_TUNE,
	PROC_ID_TEST,
	PROC_ID_MAX,
};

#define MAX_VALUE	0xFFFFFFFF
#define MAX_ADDRESS	0xFFFFFFFF

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
struct proc_dir_entry * DEMOD_PROC_ENTRY = NULL;
EXPORT_SYMBOL(DEMOD_PROC_ENTRY);



/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static OS_PROC_DESC_TABLE_T	_g_demod_device_proc_table[] =
{
	{ "author",				PROC_ID_AUTHOR,			OS_PROC_FLAG_READ},
	{ "command",			PROC_ID_COMMAND,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "property",			PROC_ID_PROPERTY,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},	
	{ "power_save",			PROC_ID_POWER_SAVE,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
#if defined(DEMOD_CONFIG_LGDBB_IPC)
	{ "api",				PROC_ID_API,			OS_PROC_FLAG_READ},
	{ "ipc",				PROC_ID_IPC,			OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "dump",				PROC_ID_DUMP,			OS_PROC_FLAG_READ},
	{ "uart",				PROC_ID_UART,			OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "jtag",				PROC_ID_JTAG,			OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "trace",				PROC_ID_TRACE,			OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "fw",					PROC_ID_FW,				OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
#endif
	{ "read_register",		PROC_ID_READ_REGISTER,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "write_register",		PROC_ID_WRITE_REGISTER,	OS_PROC_FLAG_WRITE},
	{ "debug",				PROC_ID_DEBUG,			OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ "signal_status",		PROC_ID_SIG_STATUS,		OS_PROC_FLAG_READ},
	{ "register_status",	PROC_ID_REG_STATUS,		OS_PROC_FLAG_READ},
	{ "demod_tune",			PROC_ID_TUNE,			OS_PROC_FLAG_WRITE},
	{ "test",				PROC_ID_TEST,			OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ NULL, 				PROC_ID_MAX,			0}
};

static UINT32 _read_reg_addr = MAX_ADDRESS;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*
 * read_proc implementation of demod device
 *
*/
static int _DEMOD_ReadProcFunction (UINT32 procId, char* buffer)
{
	int ret = 0;
	BOOLEAN pStatus;
	//static char buff[64];
	int dbgidx = 0;
	DEMOD_PRINT("procId %u\n", procId);

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret += snprintf(buffer + ret, 48,"%s\n", "jeongpil.yun (jeongpil.yun@lge.com)" );
		}
		break;
		case PROC_ID_COMMAND:
		break;
		case PROC_ID_PROPERTY:
		break;
		case PROC_ID_POWER_SAVE:
			ret += sprintf(buffer + ret, "\ncontrol demod power_save mode\n"
					"usage:\n"
					"- echo 0 > /proc/lg/demod/power_save\n"
					"- echo 1 > /proc/lg/demod/power_save\n");
		break;
#if defined(DEMOD_CONFIG_LGDBB_IPC)
		case PROC_ID_API:
		{ 
			DEMOD_API_Status(buffer + ret, &dbgidx);
			ret += dbgidx; 
		}
		break;

		case PROC_ID_IPC:
		{
			DEMOD_IPC_Status(buffer + ret, &dbgidx);
			ret += dbgidx;
			ret += sprintf(buffer + ret,
				"\n* ipc usage\n"
				"echo 0 > ipc => reset ipc mem, cbuf\n"
				"echo 1 > ipc => mcu sw reset\n"
				"echo 2 > ipc => check alive\n"
				"\n"
				);
		}
		break;

		case PROC_ID_DUMP:
		{
			ret += sprintf(buffer + ret, "\n* dump API regs\n");				
			DEMOD_API_Dump(buffer + ret, &dbgidx);
			ret += dbgidx;
			ret += sprintf(buffer + ret, "\n");
			break;
		}
		break;

		case PROC_ID_UART:
		{
			DEMOD_Get_UART(&pStatus);			
			ret += sprintf(buffer + ret, "UART %s\n", ((pStatus == TRUE) ? "Enabled" : "Disabled"));

			ret += sprintf(buffer + ret, "\nusage) echo N > uart\n"
				"\t0 : uart0 set cpu\n"
				"\t1 : uart0 set dbb\n"
				"\t2 : dbb hex off\n"
				"\t3 : dbb hex on, uart0 set dbb\n"
				"\t115200 : dbb uart set 115200\n"
				"\t460800 : dbb uart set 460800\n"
				"\n"
				);
		}
		break;

		case PROC_ID_JTAG:
		{
			DEMOD_Get_JTAG(&pStatus);
			ret += sprintf(buffer + ret, "JTAG %s", ((pStatus == TRUE) ? "Enabled" : "Disabled"));
		}
		break;

		case PROC_ID_TRACE:
		{
			DEMOD_Get_Trace(buffer + ret, &dbgidx);
			ret += dbgidx;
			ret += sprintf(buffer + ret, "\n");
		}
		break;

		case PROC_ID_FW:
		{
			ret += sprintf(buffer + ret, "echo 0 > fw => forced init & load\n");
			ret += sprintf(buffer + ret, "echo 1 > fw => sw reset & load\n");
			ret += sprintf(buffer + ret, "echo 2 > fw => reset\n");

			ret += sprintf(buffer + ret, "fw compare with file and DDR (result check @kernel log)\n");
			DEMOD_FW_ReInit(3);
		}
		break;
#endif
		case PROC_ID_SIG_STATUS:
		{
			ret += DEMOD_Signal_Dump(buffer + ret);
			ret += sprintf(buffer + ret, "\n");
		}
		break;

		case PROC_ID_REG_STATUS:
		{
			ret += DEMOD_Register_Dump(buffer + ret);
			ret += sprintf(buffer + ret, "\n");
		}
		break;

		case PROC_ID_READ_REGISTER:
		{
			UINT32 value = MAX_VALUE;
			UINT32 address = _read_reg_addr;

			if (address == MAX_ADDRESS)
			{
				printk("Input address is invalid. Please, Try again\n");
			}
			else
			{
				if(RET_OK != DEMOD_DBB_APB_Read((UINT16)address, &value))
				{
					DEMOD_PRINT("[DEMOD_CORE] FAIL, DEMOD_APB_Write() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			ret += sprintf(buffer + ret, "READ_REGISTER address = 0x%04x value = 0x%08x\n", address, value);
		}
		break;

		case PROC_ID_DEBUG:
		{
			ret += DEMOD_Get_Debug_Level(buffer + ret);
		}
		break;

		case PROC_ID_TEST:
		{
			ret += DEMOD_Get_Test(buffer + ret);
		}
		break;

		default:
		{
			ret = snprintf( buffer, 48, "%s(%d)\n", "unimplemented read proc", procId );
		}
		break;
	}

	return ret;
}

/*
 * write_proc implementation of demod device
 *
*/
static int _DEMOD_WriteProcFunction (UINT32 procId, char* command)
{
	int arg1;

#if defined(DEMOD_CONFIG_LGDBB_IPC)
/*
	cbuf_t * cpu2mcu = DEMOD_IPC_Cbuf_Get(DEMOD_IPC_CBUF_CPU2MCU);
	cbuf_t * mcu2cpu = DEMOD_IPC_Cbuf_Get(DEMOD_IPC_CBUF_MCU2CPU);
*/
#endif
	DEMOD_NOTI("command %s\n", command);

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			DEMOD_PRINT("command string : %s\n", command );
			//chungiii
			DEMOD_APB_AccessControl(TRUE);
			DEMOD_PRINT("DEMOD_APB_AccessControl : %s\n", command );
		}
		break;

		case PROC_ID_PROPERTY:
		break;

		case PROC_ID_POWER_SAVE:
		{
			sscanf(command, " %d", &arg1);
			DEMOD_Power_Save(0xF0 + arg1);
		}
		break;

#if defined(DEMOD_CONFIG_LGDBB_IPC)
		case PROC_ID_IPC:
		{
//			int ipc_src = 0;
			sscanf(command, " %d", &arg1);
			switch(arg1) {
			case 0:
				DEMOD_NOTI(DEMOD_TAG "ipc, cbuf all reset\n");
				//DEMOD_Set_IPC_Enable(FALSE);;
				//DEMOD_IPC_Reset();
				//DEMOD_Set_IPC_Enable(TRUE);
				break;

			case 1:
				DEMOD_NOTI(DEMOD_TAG "ipc, request mcu sw reset\n");
				//DEMOD_IPC_Send(CMD_TYPE_SYSTEM_INIT, NULL, 0);
				break;

			case 2:
				DEMOD_NOTI(DEMOD_TAG "ipc, request alive check\n");
				//DEMOD_IPC_Send(CMD_TYPE_SYSTEM_CHECK, NULL, 0);
				break;

			case 3:
				DEMOD_NOTI(DEMOD_TAG "ipc, mcu uart debug on\n");
				//DEMOD_IPC_Send(CMD_TYPE_DEBUG_ON, NULL, 0);
				break;

			case 4:
				DEMOD_NOTI(DEMOD_TAG "ipc, mcu uart debug off\n");
				//DEMOD_IPC_Send(CMD_TYPE_DEBUG_OFF, NULL, 0);
				break;

			case 100:
				DEMOD_NOTI(DEMOD_TAG "ipc, forced timeout\n");
				//DEMOD_IPC_Send(CMD_TYPE_ERROR_TO, NULL, 0);
				break;

			case 200:
				DEMOD_NOTI(DEMOD_TAG "ipc, test mode stop\n");
				//DEMOD_IPC_Send(0xFF00, NULL, 0);
				break;

			case 201:
				DEMOD_NOTI(DEMOD_TAG "ipc, test mode start\n");
				//DEMOD_IPC_Send(0xFF01, NULL, 0);
				break;

			}
		}
		break;

		case PROC_ID_UART:
		{
			sscanf(command, " %d", &arg1);
			switch (arg1) {
			case 0:
				DEMOD_Set_UART(FALSE);
				break;
			case 1:
				DEMOD_Set_UART(TRUE);
				break;
			case 2:
				DEMOD_Set_UART_HEX(FALSE);
				break;
			case 3:
				DEMOD_Set_UART_HEX(TRUE);
				DEMOD_Set_UART(TRUE);
				break;
			case 115200:
			case 460800:
				DEMOD_Set_UART_Speed(arg1);
				DEMOD_Set_UART(TRUE);
				break;
			}
		}
		break;

		case PROC_ID_JTAG:
		{
			sscanf(command, " %d", &arg1);
			DEMOD_Set_JTAG(arg1 > 0);
		}
		break;

		case PROC_ID_TRACE:
		{
			sscanf(command, " %d", &arg1);
			DEMOD_Set_Trace(arg1);
		}
		break;

		case PROC_ID_FW:
		{
			sscanf(command, " %d", &arg1);
			if (arg1 >= 0 && arg1 < 3)
				DEMOD_FW_ReInit(arg1);
		}
		break;
#endif
		case PROC_ID_WRITE_REGISTER:
		{
			UINT32 value = MAX_VALUE;
			UINT32 address = MAX_ADDRESS;

			sscanf( command, " %x %x",&address, &value);
			printk("WRITE_REGISTER address = 0x%x, value = 0x%x\n", address , value);

			if (value == MAX_VALUE || address == MAX_ADDRESS)
			{
				printk("Input value or address is invalid. Please, Try again\n");
			}
			else
			{
				if(RET_OK != DEMOD_DBB_APB_Write((UINT16)address, &value))
				{
					DEMOD_PRINT("[DEMOD_CORE] FAIL, DEMOD_APB_Write() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
		}
		break;

		case PROC_ID_READ_REGISTER:
		{
			UINT32 value = MAX_VALUE;
			UINT32 address = MAX_ADDRESS;

			sscanf( command, " %x", &address);
			printk("READ_REGISTER address = 0x%x\n", address);

			if (address == MAX_ADDRESS)
			{
				printk("Input address is invalid. Please, Try again\n");
			}
			else
			{
				if(RET_OK != DEMOD_DBB_APB_Read((UINT16)address, &value))
				{
					DEMOD_PRINT("[DEMOD_CORE] FAIL, DEMOD_APB_Write() \n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			printk("RESULT address = 0x%x value = 0x%x\n", address, value);
			_read_reg_addr = address;
		}
		break;

		case PROC_ID_DEBUG:
		{
			sscanf(command, " %d", &arg1);
			DEMOD_Set_Debug_Level(arg1);
		}
		break;

		case PROC_ID_TEST:
		{
			sscanf(command, " %d", &arg1);
			DEMOD_Set_Test(arg1);
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return strlen(command);
}

/**
 * initialize proc utility for demod device
 *
 * @see DEMOD_Init
*/
void	DEMOD_PROC_Init (void)
{
	DEMOD_PROC_ENTRY = OS_PROC_CreateEntryEx (DEMOD_MODULE, _g_demod_device_proc_table,
						_DEMOD_ReadProcFunction,
						_DEMOD_WriteProcFunction );
}

/**
 * cleanup proc utility for demod device
 *
 * @see DEMOD_Cleanup
*/
void	DEMOD_PROC_Cleanup (void)
{
	DEMOD_PROC_ENTRY = NULL;
	OS_PROC_RemoveEntry(DEMOD_MODULE);
}

/** @} */

