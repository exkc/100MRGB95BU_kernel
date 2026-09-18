/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/** @file
 *
 *  main driver implementation for lgbus device.
 *	lgbus device will teach you how to make device driver with new platform.
 *
 *  author		bongrae.cho (bongrae.cho@lge.com)
 *  version		1.0
 *  date		2012.11.10
 *  note		Additional information.
 *
 *  @addtogroup lg115x_lgbus
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "proc_util.h"
#include "sys_regs.h"

#include "lgbus_kapi.h"
#include "lgbus_drv.h"
#include "lgbus_cfg.h"
#include "lgbus_hw.h"

#include <linux/seq_file.h>

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
    PROC_ID_SUSPEND,
    PROC_ID_RESUME,
	PROC_ID_STATUS,

    PROC_ID_PMT_CTRL,
	PROC_ID_PMT_INFO,
	PROC_ID_PMT_OPTS,

    PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern  char*   simple_strtok(char *s, const char *delim, char **save_ptr);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int LGBUS_PROC_Reader(UINT32 procId, char* buffer);
static int LGBUS_PROC_Writer(UINT32 procId, char* command);

static void LGBUS_PROC_PrintPMTInfo (struct seq_file *m);
static void LGBUS_PROC_PrintStatus  (struct seq_file *m);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
OS_PROC_SEQRD_DEFINE(lgbus_pmtinfo_proc_fops, LGBUS_PROC_PrintPMTInfo)
OS_PROC_SEQRD_DEFINE(lgbus_status_proc_fops, LGBUS_PROC_PrintStatus)

static OS_PROC_DESC_TABLE_T	_g_lgbus_device_proc_table[] =
{
	{ "pmtctrl",				PROC_ID_PMT_CTRL,	OS_PROC_FLAG_WRITE|OS_PROC_FLAG_READ},
	{ "pmtinfo",				PROC_ID_PMT_INFO,	OS_PROC_FLAG_SEQRD, (void*)&lgbus_pmtinfo_proc_fops },
	{ "pmtopts",				PROC_ID_PMT_OPTS,	OS_PROC_FLAG_WRITE|OS_PROC_FLAG_READ},
	{ "suspend",				PROC_ID_SUSPEND,	OS_PROC_FLAG_WRITE },
	{ "resume",					PROC_ID_RESUME,		OS_PROC_FLAG_WRITE },
	{ "status",					PROC_ID_STATUS,		OS_PROC_FLAG_SEQRD, (void*)&lgbus_status_proc_fops },
	{ NULL, 		            PROC_ID_MAX		, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static int LGBUS_PROC_Reader(UINT32 procId, char* buffer)
{
    unsigned int ret = 0;

	switch(procId)
	{
		case PROC_ID_PMT_CTRL:
		{
			int	len = 0;

			len += sprintf(buffer + len, "lgbus pmt control\n");
			len += sprintf(buffer + len, "usage: echo val > pmtctrl\n");
			len += sprintf(buffer + len, "            val: 0 if stop, 1 if start\n");
			ret = len;
		}
		break;

		case PROC_ID_PMT_OPTS:
		{
			int	len = 0;
			LGBUS_HW_OPT_T hwopts = LGBUS_HW_GetOption();

			len += sprintf(buffer + len, "pmt_sync: %s\n", (hwopts & LGBUS_HW_OPT_PMT_SYNC)? "on":"off");
			len += sprintf(buffer + len, "pmt_bw_org: %s\n", (hwopts & LGBUS_HW_OPT_PMT_BW_ORG)? "on":"off");
			len += sprintf(buffer + len, "pmt_bw_dummy: %s\n", (hwopts & LGBUS_HW_OPT_PMT_BW_DUMMY)? "on":"off");

			ret = len;
		}
		break;

        default:
		{
			// do nothing
		}
		break;
	}

    return ret;
}

static int LGBUS_PROC_Writer( UINT32 procId, char* command )
{
	int cmdlen = strlen(command);

	switch(procId)
	{
		case PROC_ID_PMT_CTRL:
		{
			int	opt;

			sscanf(command," %d", &opt);

			if		(opt==1) { LGBUS_HW_Open();  }
			else if (opt==0) { LGBUS_HW_Close(); }
			else			 { /* invalid command */ }
		}
		break;

		case PROC_ID_PMT_OPTS:
		{
			char *tok, *sav_tok;
			char delim[] = " ,\t\n";

			LGBUS_HW_OPT_T hwopts = LGBUS_HW_GetOption();

			tok = simple_strtok(command, delim, &sav_tok);

			while(tok)
			{
				LGBUS_HW_OPT_T opt = 0;

				if		(!strncasecmp(tok+1, "pmt_sync",     8))	{ opt = LGBUS_HW_OPT_PMT_SYNC; }
				else if	(!strncasecmp(tok+1, "pmt_bw_org",  10))	{ opt = LGBUS_HW_OPT_PMT_BW_ORG; }
				else if	(!strncasecmp(tok+1, "pmt_bw_dummy",12))	{ opt = LGBUS_HW_OPT_PMT_BW_DUMMY; }
				else												{ goto new_tok; }

				if		(tok[0] == '+')	{ hwopts |= opt; }
				else if	(tok[0] == '-') { hwopts &= ~opt;}
				else					{ goto new_tok;  }
new_tok:
				tok = simple_strtok(NULL, delim, &sav_tok);
			}

			LGBUS_HW_SetOption(hwopts);
		}
		break;

		case PROC_ID_SUSPEND:
		{
			LGBUS_HW_Suspend( );
		}
		break;

		case PROC_ID_RESUME:
		{
			LGBUS_HW_Resume( );
		}
		break;

        default:

            break;
	}

	return cmdlen;
}

void LGBUS_PROC_Init(void)
{
	OS_PROC_CreateEntryEx(LGBUS_MODULE, _g_lgbus_device_proc_table,
										LGBUS_PROC_Reader,
										LGBUS_PROC_Writer);
}

void LGBUS_PROC_Cleanup(void)
{
	OS_PROC_RemoveEntry(LGBUS_MODULE);
}

static void LGBUS_PROC_PrintPMTInfo(struct seq_file *m)
{
	LGBUS_HW_PrintPMTInfo(m);
}

static void LGBUS_PROC_PrintStatus(struct seq_file *m)
{
	LGBUS_HW_PrintStatus(m);
}

/** @} */

