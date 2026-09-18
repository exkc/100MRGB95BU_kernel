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
 *  proc file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2015.05.28
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */


/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/proc_fs.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "os_util.h"
#include "proc_util.h"
#include "be_kapi.h"
#include "be_cfg.h"
#include "be_dbg.h"
#include "be_def.h"

#include "be_top_drv.h"
#include "fwl_drv.h"
#include "int_drv.h"
#include "ipc_drv.h"
#include "h3d_drv.h"
#include "frc_drv.h"
#include "led_drv.h"
#include "pwm_drv.h"

#include "ovi_hal.h"
#include "pwm_hal.h"
#include "be_top_hal.h"

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
	PROC_ID_PM_TEST,
	PROC_ID_STATUS,
	PROC_ID_CID_MASK,
	PROC_ID_CID_LIST,
	PROC_ID_PWM_DUTY,
	PROC_ID_OBJ_APL,
	PROC_ID_DISPOUT,
	PROC_ID_MAX,
};

enum {
	PROC_MOD_ID_FRC,	/* proc sub_module : FRC */
	PROC_MOD_ID_FWI,	/* proc sub_module : FWI */
	PROC_MOD_ID_PWM,	/* proc sub_module : PWM */
	PROC_MOD_ID_LED,	/* proc sub_module : LED */
	PROC_MOD_ID_TOP,	/* proc sub_module : TOP */
	PROC_MOD_ID_H3D,	/* proc sub_module : H3D */
	PROC_MOD_ID_OBJ,	/* proc sub_module : OBJ */
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int v4l2_vbe_get_cid_mask(char* buffer);
extern int v4l2_vbe_set_cid_mask(int mask);
extern int v4l2_vbe_pm_runtime_help(char* buffer);
extern int v4l2_vbe_pm_runtime_test(char* command);
extern int v4l2_vbe_dbg_get_pwm_duty(char* buffer);
extern int v4l2_vbe_dbg_set_pwm_duty(char* command);
extern int v4l2_vbe_dbg_obj_apl_help(char* buffer);
extern int v4l2_vbe_dbg_obj_apl_test(char* command);
extern int v4l2_vbe_dbg_dispout_help(char* buffer);
extern int v4l2_vbe_dbg_dispout_test(char* command);
extern char *vbe_ctrl_id_to_str(int id);
extern void vbe_status(struct seq_file *m, void* data);
extern int vbe_dpc_command(char* command);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static void _BE_PROC_PrintStatus(struct seq_file *m, void* data);
static int _be_proc_show_cid_list(struct seq_file *m);

int be_proc__parse_msgfromfw__PQ_RPT_PCCE(char*);	//mhlee, pcce msg from fw

void BE_PROC_Init(void);
void BE_PROC_Cleanup(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
OS_PROC_SEQRD_DEFINE_EX(be_status_proc_fops, _BE_PROC_PrintStatus, -1)
OS_PROC_SEQRD_DEFINE(_g_be_proc_cid_list_fops, _be_proc_show_cid_list)

static OS_PROC_DESC_TABLE_T _g_be_device_proc_table[] =
{
	{ "author",     PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
	{ "command",    PROC_ID_COMMAND, OS_PROC_FLAG_WRITE },
	{ "pm_test",    PROC_ID_PM_TEST, OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "status",     PROC_ID_STATUS,   OS_PROC_FLAG_SEQRD, (void*)&be_status_proc_fops },
	{ "cid_mask",   PROC_ID_CID_MASK,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cid_list",   PROC_ID_CID_LIST,OS_PROC_FLAG_SEQRD,(void*)&_g_be_proc_cid_list_fops},
	{ "pwm_duty",   PROC_ID_PWM_DUTY,OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "obj_apl",    PROC_ID_OBJ_APL, OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "dispout",    PROC_ID_DISPOUT, OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ NULL,         PROC_ID_MAX     , 0 }
};

/* FRC sub_module proc definition */
OS_PROC_SEQRD_DEFINE_EX(be_frc_status_proc_fops, _BE_PROC_PrintStatus, PROC_MOD_ID_FRC)

static const OS_PROC_DESC_TABLE_T _be_frc_proc_table[] = {
    { "status", 0x0, OS_PROC_FLAG_SEQRD, (void*)&be_frc_status_proc_fops },
    { NULL,     0x1, 0 } };

/* FWI sub_module proc definition */
OS_PROC_SEQRD_DEFINE_EX(be_fwi_status_proc_fops, _BE_PROC_PrintStatus, PROC_MOD_ID_FWI)

static const OS_PROC_DESC_TABLE_T _be_fwi_proc_table[] = {
    { "status", 0x0, OS_PROC_FLAG_SEQRD, (void*)&be_fwi_status_proc_fops },
    { NULL,     0x1, 0 } };

/* PWM sub_module proc definition */
OS_PROC_SEQRD_DEFINE_EX(be_pwm_status_proc_fops, _BE_PROC_PrintStatus, PROC_MOD_ID_PWM)

static const OS_PROC_DESC_TABLE_T _be_pwm_proc_table[] = {
    { "status", 0x0, OS_PROC_FLAG_SEQRD, (void*)&be_pwm_status_proc_fops },
    { NULL,     0x1, 0 } };

/* LED sub_module proc definition */
OS_PROC_SEQRD_DEFINE_EX(be_led_status_proc_fops, _BE_PROC_PrintStatus, PROC_MOD_ID_LED)

static const OS_PROC_DESC_TABLE_T _be_led_proc_table[] = {
    { "status", 0x0, OS_PROC_FLAG_SEQRD, (void*)&be_led_status_proc_fops },
    { NULL,     0x1, 0 } };

/* TOP sub_module proc definition */
OS_PROC_SEQRD_DEFINE_EX(be_top_status_proc_fops, _BE_PROC_PrintStatus, PROC_MOD_ID_TOP)

static const OS_PROC_DESC_TABLE_T _be_top_proc_table[] = {
    { "status", 0x0, OS_PROC_FLAG_SEQRD, (void*)&be_top_status_proc_fops },
    { NULL,     0x1, 0 } };

/* H3D sub_module proc definition */
OS_PROC_SEQRD_DEFINE_EX(be_h3d_status_proc_fops, _BE_PROC_PrintStatus, PROC_MOD_ID_H3D)

static const OS_PROC_DESC_TABLE_T _be_h3d_proc_table[] = {
    { "status", 0x0, OS_PROC_FLAG_SEQRD, (void*)&be_h3d_status_proc_fops },
    { NULL,     0x1, 0 } };

/* H3D sub_module proc definition */
OS_PROC_SEQRD_DEFINE_EX(be_obj_status_proc_fops, _BE_PROC_PrintStatus, PROC_MOD_ID_OBJ)

static const OS_PROC_DESC_TABLE_T _be_obj_proc_table[] = {
    { "status", 0x0, OS_PROC_FLAG_SEQRD, (void*)&be_obj_status_proc_fops },
    { NULL,     0x1, 0 } };

static struct proc_dir_entry* be_proc_dir;

BE_PQ_RPT_PCCE_T be_pq_rpt_pcce_t = { /*.ui = 0, .en = 0, .status = 0,*/ .str[0] = '\0' };	// mhlee, pcce msg from fw

/*----------------------------------------------------------------------------------------
	Static Function Implementation
----------------------------------------------------------------------------------------*/
static int _be_proc_show_cid_list(struct seq_file *m)
{
	unsigned int i;
	int start = V4L2_CID_USER_EXT_VBE_BASE;

	seq_printf(m,"-------------------------------------------------------------------------\n");
	for (i=start; i<(start+0x1000); i++)
	{
		if (strncasecmp(vbe_ctrl_id_to_str(i), "V4L2_CID_EXT_UNKOWN", strlen("V4L2_CID_EXT_UNKOWN"))) {
			seq_printf(m,"%-50s = 0x%08x (%d)\n", vbe_ctrl_id_to_str(i), i, i);
		}
	}
	seq_printf(m,"-------------------------------------------------------------------------\n");
	return 0;
}

static int	_BE_PROC_SimpleReadProcHandler(UINT32 proc_id, char* buffer)
{
	int		ret;

	switch(proc_id)
	{
		case PROC_ID_AUTHOR:
		{
			ret = snprintf( buffer, 50, "%s\n", "dj911.kim@lge.com" );
		}
		break;

		case PROC_ID_PM_TEST :
		{
			ret = v4l2_vbe_pm_runtime_help(buffer);
		}break;

		case PROC_ID_CID_MASK:
		{
			ret = v4l2_vbe_get_cid_mask(buffer);
		}break;

		case PROC_ID_PWM_DUTY:
		{
			ret = v4l2_vbe_dbg_get_pwm_duty(buffer);
		}break;

		case PROC_ID_OBJ_APL:
		{
			ret = v4l2_vbe_dbg_obj_apl_help(buffer);
		}break;

		case PROC_ID_DISPOUT:
		{
			ret = v4l2_vbe_dbg_dispout_help(buffer);
		}break;

		default:
		{
			ret = snprintf( buffer, 50, "%s(%d)\n", "unimplemented proc", proc_id);
		}
	}

	return ret;
}

static int _BE_PROC_SimpleWriteProcHandler(UINT32 proc_id, char* command)
{
	// int ret;
	// UINT32 val[2];

	switch(proc_id)
	{
		case PROC_ID_COMMAND:
		{
			if (!strncmp(command,"dpc",strlen("dpc"))) {
				vbe_dpc_command(command);
			}
		}
		break;

		case PROC_ID_PM_TEST:
		{
			v4l2_vbe_pm_runtime_test(command);
		}
		break;

		case PROC_ID_CID_MASK:
		{
			int mask;
			sscanf(command," %x",&mask);
			v4l2_vbe_set_cid_mask(mask);
		}break;

		case PROC_ID_PWM_DUTY:
		{
			v4l2_vbe_dbg_set_pwm_duty(command);
		}break;

		case PROC_ID_OBJ_APL:
		{
			v4l2_vbe_dbg_obj_apl_test(command);
		}break;

		case PROC_ID_DISPOUT:
		{
			v4l2_vbe_dbg_dispout_test(command);
		}break;

		default: /* do nothing */ break;
	}

	return strlen(command);
}

/**
 * @brief   Check if the message from MCU to the kernel starts with "PQ_RPT_PCCE:" and parse the following message.
 * @author  manho.lee (mhlee)
 * @date    2025.07.02
 * @param   *str: [IN] message from MCU to Kernel (after "PQ_RPT_PCCE:")
 * @return  ( 0) OK
 */
int be_proc__parse_msgfromfw__PQ_RPT_PCCE(char *str)
{
	// printk("%s(), START\n", __func__);
	// printk("%s(), str[%s]\n", __func__, str);
	int str_max = BE_PQ_RPT_PCCE__STR_MAX - 1;
	int str_len = strlen(str);
	strncpy(be_pq_rpt_pcce_t.str, str, str_max);
	be_pq_rpt_pcce_t.str[str_len < str_max ? str_len : str_max] = '\0';	// string terminator
	// printk("%s(), END\n", __func__);
	return 0;
}

/** print OVI kdriver status
 *
 */
static void _BE_PROC_PrintStatus(struct seq_file *m, void* data)
{
	int mod_id = (int)(uintptr_t)data;

	switch(mod_id)
	{
		case PROC_MOD_ID_FRC: BE_FRC_ProcHandler(BE_FRC_PROC_ID_DETAIL_INFO, m, data); break;
		case PROC_MOD_ID_FWI: BE_FW_ProcHandler (BE_FWI_PROC_ID_DETAIL_INFO, m, data); break;
		case PROC_MOD_ID_PWM: BE_PWM_ProcHandler(BE_PWM_PROC_ID_DETAIL_INFO, m, data); break;
		case PROC_MOD_ID_LED: BE_LED_ProcHandler(BE_LED_PROC_ID_DETAIL_INFO, m, data); break;
		case PROC_MOD_ID_TOP: BE_TOP_ProcHandler(BE_TOP_PROC_ID_DETAIL_INFO, m, data); break;
		case PROC_MOD_ID_H3D: BE_H3D_ProcHandler(BE_H3D_PROC_ID_DETAIL_INFO, m, data); break;

		default:
			vbe_status(m,(mod_id == PROC_MOD_ID_OBJ)? (void* )1:data);
			// seq_printf(m, be_pq_rpt_pcce_t.str);	//mhlee, pcce msg from fw
			break;
	}
}

/*========================================================================================
	Implementation Group
========================================================================================*/

static int vbe_proc_show(struct seq_file *m, void *v)
{
	if (!m)	return 0;

	OVI_HAL_ProcHandler(OVI_HAL_PROC_ID_DISP_OUTPUT_INFO, m, (void*)be_pq_rpt_pcce_t.str/*v*/);	//mhlee, pcce msg from fw
	BE_PWM_HAL_ProcHandler(BE_PWM_PROC_ID_SIMPLE_INFO,m,v);
	BE_TOP_HAL_ProcHandler(BE_TOP_PROC_ID_ORBIT_INFO,m,v);
	BE_TOP_HAL_ProcHandler(BE_TOP_PROC_ID_LSR_INFO,m,v);
	BE_TOP_HAL_ProcHandler(BE_TOP_PROC_ID_GSR_INFO,m,v);
	BE_TOP_HAL_ProcHandler(BE_TOP_PROC_ID_OSDLVL_INFO,m,v);
	BE_TOP_HAL_ProcHandler(BE_TOP_PROC_ID_CPC_INFO,m,v);
	vbe_status(m,(void* )2);

    return 0;
}

static int vbe_proc_open(struct inode *inode, struct file *file)
{
	int ret;

	if (!file)	return 0;

	ret = single_open (file, vbe_proc_show, NULL);
	if (ret < 0)
		return ret;

	return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
const struct proc_ops vbe_proc_fops = {
	.proc_open = vbe_proc_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations vbe_proc_fops = {
	.open = vbe_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif

void	BE_PROC_Init (void)
{
	be_proc_dir = OS_PROC_CreateEntryEx(BE_MODULE, _g_be_device_proc_table, _BE_PROC_SimpleReadProcHandler, _BE_PROC_SimpleWriteProcHandler);

	OS_PROC_CreateEntry("frc", be_proc_dir, (OS_PROC_DESC_TABLE_T*)_be_frc_proc_table, NULL, NULL );
	OS_PROC_CreateEntry("fwi", be_proc_dir, (OS_PROC_DESC_TABLE_T*)_be_fwi_proc_table, NULL, NULL );
	OS_PROC_CreateEntry("pwm", be_proc_dir, (OS_PROC_DESC_TABLE_T*)_be_pwm_proc_table, NULL, NULL );
	OS_PROC_CreateEntry("led", be_proc_dir, (OS_PROC_DESC_TABLE_T*)_be_led_proc_table, NULL, NULL );
	OS_PROC_CreateEntry("top", be_proc_dir, (OS_PROC_DESC_TABLE_T*)_be_top_proc_table, NULL, NULL );
	OS_PROC_CreateEntry("h3d", be_proc_dir, (OS_PROC_DESC_TABLE_T*)_be_h3d_proc_table, NULL, NULL );
	OS_PROC_CreateEntry("obj", be_proc_dir, (OS_PROC_DESC_TABLE_T*)_be_obj_proc_table, NULL, NULL );

	{
		struct proc_dir_entry *proc_vbe;
		struct proc_dir_entry *proc_entry = OS_PROC_GetLinuxTvEntry();

		if (!proc_entry)
		{
			BE_PRINT("proc_entry is not ready\n");
			return;
		}

		proc_vbe = proc_mkdir ("vbe", proc_entry);

		proc_create_data("vbe-status", 0440, proc_vbe, &vbe_proc_fops, NULL);
	}
}

void	BE_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry(BE_MODULE);
}


/** @} */
