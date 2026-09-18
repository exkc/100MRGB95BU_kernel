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
 *  author		<none>
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_gfx
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include "proc_util.h"
#include "pqe_pm_impl.h"

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
	PROC_ID_STATUS,
	PROC_ID_UNIT_TEST,
	PROC_ID_REQUEST_TEST,
	PROC_ID_DBG_HW,
	PROC_ID_MASK,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void pqe_pm_dbg_hw(void);
extern void pqe_pm_loop_cg_off_on(int type, int loop_num);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int pqe_pm_read_proc(UINT32 procId, char* buffer);
static int pqe_pm_write_proc(UINT32 procId, char* command);

OS_PROC_SEQRD_DEFINE(status_proc_fops,	pqe_pm_print_status)
OS_PROC_SEQRD_DEFINE(dbg_hw_proc_fops,	pqe_pm_print_dbg_hw)

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static OS_PROC_DESC_TABLE_T	_g_pqepm_device_proc_table[] =
{
	{ "status",			PROC_ID_STATUS,			OS_PROC_FLAG_SEQRD, (void*)&status_proc_fops },
	{ "unit_test",		PROC_ID_UNIT_TEST,		OS_PROC_FLAG_WRITE },
	{ "request_test",	PROC_ID_REQUEST_TEST,	OS_PROC_FLAG_WRITE },
	{ "dbg_hw",			PROC_ID_DBG_HW,			OS_PROC_FLAG_SEQRD, (void*)&dbg_hw_proc_fops },
	{ "mask",			PROC_ID_MASK,			OS_PROC_FLAG_WRITE },
	{ NULL, 			PROC_ID_MAX,		 	0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
/* initialize proc utility for gfx device
 *
 * @see GFX_Init
*/
void	pqe_pm_init_proc (void)
{
	OS_PROC_CreateEntryEx (PQE_PM_MODULE, _g_pqepm_device_proc_table, pqe_pm_read_proc, pqe_pm_write_proc);
}

void	pqe_pm_cleanup_proc (void)
{
	OS_PROC_RemoveEntry(PQE_PM_MODULE);
}

static int pqe_pm_read_proc(UINT32 procId, char* buffer)
{
	return 0;
}

static int _pqe_pm_test_device_callback(int cmd)
{
	switch(cmd)
	{
		case PQE_PM_DEVICE_SUSPEND_PREPARE:		/* do nothing */ break;
		case PQE_PM_DEVICE_SUSPEND:				/* do nothing */ break;
		case PQE_PM_DEVICE_SUSPEND_COMPLETED:	/* do nothing */ break;

		case PQE_PM_DEVICE_RESUME_PREPARE:		/* do nothing */ break;
		case PQE_PM_DEVICE_RESUME:				/* do nothing */ break;
		case PQE_PM_DEVICE_RESUME_COMPLETED:	/* do nothing */ break;

		default: 								/* unknown */ break;
	}

	return RET_OK;
}

static int pqe_pm_write_proc( UINT32 procId, char* command )
{
	switch(procId)
	{
		case PROC_ID_UNIT_TEST:
		{
			struct pqe_pm_config t0 = { .name = "N_0", .order = 0, .callback = _pqe_pm_test_device_callback };
			struct pqe_pm_config t1 = { .name = "N_1", .order = 0, .callback = _pqe_pm_test_device_callback };
			struct pqe_pm_config t2 = { .name = "N_2", .order = 0, .callback = _pqe_pm_test_device_callback };
			struct pqe_pm_config t3 = { .name = "N_3", .order = 0, .callback = _pqe_pm_test_device_callback };
			struct pqe_pm_config t4 = { .name = "H_0", .order =99, .callback = _pqe_pm_test_device_callback };
			struct pqe_pm_config t5 = { .name = "H_1", .order =50, .callback = _pqe_pm_test_device_callback };
			struct pqe_pm_config t6 = { .name = "N_4", .order = 0, .callback = _pqe_pm_test_device_callback };

			pqe_pm_unregister(0);
			pqe_pm_unregister(1);
			pqe_pm_unregister(2);
			pqe_pm_unregister(3);
			pqe_pm_unregister(4);
			pqe_pm_unregister(5);
			pqe_pm_unregister(6);

			pqe_pm_register(&t0);
			pqe_pm_register(&t1);
			pqe_pm_register(&t2);
			pqe_pm_register(&t3);
			pqe_pm_register(&t4);
			pqe_pm_register(&t5);
			pqe_pm_register(&t6);

			pqe_pm_request_suspend(0);
			pqe_pm_request_suspend(1);
			pqe_pm_request_suspend(2);
			pqe_pm_request_suspend(3);
			pqe_pm_request_suspend(4);
			pqe_pm_request_suspend(5);
			pqe_pm_request_suspend(6);

			pqe_pm_request_resume(0);

			pqe_pm_request_suspend(0);

			pqe_pm_unregister(0);
			pqe_pm_unregister(1);
			pqe_pm_unregister(2);
			pqe_pm_unregister(3);
			pqe_pm_unregister(4);
			pqe_pm_unregister(5);
			pqe_pm_unregister(6);
		}break;
		case PROC_ID_REQUEST_TEST:
		{
			int cmd,i;
			sscanf(command,"%d\n",&cmd);
			switch (cmd)
			{
				case 0:
				{
					for (i=0; i<PQE_PM_NUM_MAX; i++)
					{
						pqe_pm_request_suspend(i);
					}
				}break;
				case 1:
				{
					for (i=0; i<PQE_PM_NUM_MAX; i++)
					{
						pqe_pm_request_resume(i);
					}
				}break;
				case 2:
				{
					int loop_num;
					sscanf(command,"%d %d\n",&cmd,&loop_num);
					pqe_pm_loop_cg_off_on(cmd,loop_num);
				}break;
			}
		}break;
		case PROC_ID_MASK:
		{
			int type,data;
			sscanf(command,"%d %x\n",&type,&data);
			pqe_pm_dbg_set_mask(type,data);
		}break;
	}

	return strlen(command);
}

/** @} */

