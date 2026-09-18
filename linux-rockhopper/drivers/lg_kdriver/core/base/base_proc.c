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
 *	kdriver main
 *
 *  author      daeyoung lim ( raxis.lim@lge.com )
 *  version		1.0
 *  date		2009.11.04
 *
 *  @addtogroup lg1150_base
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_drv.h"

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
	PROC_ID_MEMCFG	= 0,
	PROC_ID_STATUS,
	PROC_ID_DCHIP,
	PROC_ID_DCHIP_NAME,
	PROC_ID_ACHIP,
	PROC_ID_PLATFORM,
	PROC_ID_BOARD_OPT,
	PROC_ID_GRAPHIC_RES,
	PROC_ID_REG_RD,
	PROC_ID_REG_WR,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void	BASE_DEVMEM_DumpMemCfg(struct seq_file* m, UINT32 opt);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void BASE_PROC_PrintStatus(struct seq_file *m, void* data);
static void BASE_PROC_PrintMemStatus(struct seq_file *m, void* data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
OS_PROC_SEQRD_DEFINE_EX(base_memcfg_dump_fops, BASE_PROC_PrintMemStatus, NULL)
OS_PROC_SEQRD_DEFINE_EX(base_status_proc_fops, BASE_PROC_PrintStatus, NULL)

static OS_PROC_DESC_TABLE_T	_g_base_proc_table[] =
{
	{ "memcfg",			PROC_ID_MEMCFG,		OS_PROC_FLAG_FOP, (void*)&base_memcfg_dump_fops },
	{ "status",			PROC_ID_STATUS,		OS_PROC_FLAG_FOP, (void*)&base_status_proc_fops },

	{ "chip_rev",		PROC_ID_DCHIP, 		OS_PROC_FLAG_READ },
	{ "chip_name",		PROC_ID_DCHIP_NAME, OS_PROC_FLAG_READ },
	{ "ace_rev",		PROC_ID_ACHIP, 		OS_PROC_FLAG_READ },
	{ "platform",		PROC_ID_PLATFORM, 	OS_PROC_FLAG_READ },
	{ "board_opt",		PROC_ID_BOARD_OPT, 	OS_PROC_FLAG_READ },
	{ "graphic_res",	PROC_ID_GRAPHIC_RES,OS_PROC_FLAG_READ },

	{ "reg_rd",			PROC_ID_REG_RD,		OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "reg_wr",			PROC_ID_REG_WR,		OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },

	{ NULL, 			0,			 		0 },
};

/*========================================================================================
	Implementation Group
========================================================================================*/

static int	BASE_PROC_ReadProcFunction( UINT32 procId, char* buffer )
{
	int		len = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_DCHIP:
		{
			len += sprintf( buffer, "0x%x\n", lx_chip_rev() );
		}
		break;

		case PROC_ID_DCHIP_NAME:
		{
			len += sprintf( buffer, "%s\n", CHIP_NAME );
		}
		break;

		case PROC_ID_ACHIP:
		{
			len += sprintf( buffer, "0x%x\n", lx_ace_rev() );
		}
		break;

		case PROC_ID_PLATFORM:
		{
			len += sprintf( buffer, "0x%x\n", lx_chip_plt() );
		}
		break;

		case PROC_ID_BOARD_OPT:
		{
			len += sprintf( buffer, "0x%x\n", lx_board_opt() );
		}
		break;

		case PROC_ID_GRAPHIC_RES:
		{
			len += sprintf( buffer, "0x%x\n", lx_chip_graphic_res() );
		}
		break;

		case PROC_ID_REG_RD:
		{
			len += sprintf( buffer, "<usage> echo #addr > /proc/lg/base/reg_rd\n");
		}
		break;

		case PROC_ID_REG_WR:
		{
			len += sprintf( buffer, "<usage> echo #addr #val > /proc/lg/base/reg_wr\n");
		}
		break;

		default:
		{
			len = sprintf( buffer, "%s(%d)\n", "unimplemented read proc",procId );
		}
	}

	return len;
}

/*
 * write_proc implementation of ttx device
 *
*/
static int BASE_PROC_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
        case PROC_ID_REG_RD:
        {
            UINT32 addr, val;
            sscanf( command, " %x", &addr );
            OS_RdReg( addr, &val );
            printk("\nAddr 0x%x = 0x%08x\n", addr, val );
        }
        break;

        case PROC_ID_REG_WR:
        {
            UINT32 addr, val;

            sscanf( command, " %x %x", &addr, &val );
            OS_WrReg( addr, val );
            OS_RdReg( addr, &val );
            printk("\nAddr 0x%x = 0x%08x\n", addr, val );
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

static void BASE_PROC_PrintMemStatus( struct seq_file* m, void* data)
{
	BASE_DEVMEM_DumpMemCfg(m, 0x1);
}

static void BASE_PROC_PrintStatus( struct seq_file* m, void* data)
{
	/* print simple memory layout */
	BASE_DEVMEM_DumpMemCfg(m, 0x0);
}

/**
 * Initialize proc system for debug utility
 *
 */
void	BASE_PROC_Init ( void )
{
	OS_PROC_CreateEntryEx ( "base" ,	_g_base_proc_table,
										BASE_PROC_ReadProcFunction,
										BASE_PROC_WriteProcFunction );
}

