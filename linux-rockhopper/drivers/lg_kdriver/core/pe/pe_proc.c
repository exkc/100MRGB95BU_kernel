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
 *  Linux proc interface for pe device.
 *	pe device will teach you how to make device driver with new platform.
 *
 *  author		wonsik.do (wonsik.do@lge.com)
 *  version		1.0
 *  date		2018.05.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_pe
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
#include <linux/proc_fs.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"
#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"
#include "pe_cfg.h"
#include "pe_def.h"
#include "pe_drv.h"
#include "pe_proc_dbg.h"
#include "pe_etc.h"
#include "pe_hst.h"
#include "pe_hdr.h"

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
	PROC_ID_VERSION	= 0,
	PROC_ID_COMMAND,
	PROC_ID_DBG_WRAP_FUNC,
	PROC_ID_DBG_KDRV_FUNC,
	PROC_ID_HDR_FUNC,
	PROC_ID_MASK_IOCTL,
	PROC_ID_BYPASS_BLOCK,
	PROC_ID_PM_TEST,
	PROC_ID_DBG_LATENCY,
	PROC_ID_CID_MASK,
	PROC_ID_CID_LIST,
	PROC_ID_HISTO0,
	PROC_ID_HISTO1,
	PROC_ID_PE_DDR,
	PROC_ID_HDR_HIST0,
	PROC_ID_HDR_HIST1,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int v4l2_vpq_get_ioctl_mask(char* buffer);
extern int v4l2_vpq_set_ioctl_mask(int mask);
extern int v4l2_vpq_get_cid_mask(char* buffer);
extern int v4l2_vpq_set_cid_mask(int mask);
extern int v4l2_vpq_cmn_get_bypass_block(char* buffer);
extern int v4l2_vpq_cmn_set_bypass_block(int mask);
extern int v4l2_vpq_pm_runtime_help(char* buffer);
extern int v4l2_vpq_pm_runtime_test(char* command);
extern int v4l2_lgsr_pm_runtime_help(char* buffer);
extern int v4l2_lgsr_pm_runtime_test(char* command);
extern int v4l2_vpq_latency_set_debug(UINT32 value);
extern UINT32 v4l2_vpq_latency_get_debug(void);
extern int pe_proc_hdr_help(char* buffer);
extern void pe_proc_hdr_func(char *command);
extern void pe_proc_hdr_init(struct proc_dir_entry *entry);
extern char *vpq_ctrl_id_to_str(int id);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _pe_proc_show_cid_list(struct seq_file *m);
static int _pe_proc_show_pe_ddr(struct seq_file *m);
static int _pe_proc_show_histo(struct seq_file *m, void* data);

void	PE_PROC_Init (void);
void	PE_PROC_Cleanup (void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
OS_PROC_SEQRD_DEFINE(_g_pe_proc_cid_list_fops, _pe_proc_show_cid_list)
OS_PROC_SEQRD_DEFINE(_g_pe_proc_pe_ddr_fops, _pe_proc_show_pe_ddr)
OS_PROC_SEQRD_DEFINE_EX(_g_pe_proc_histo0_fops, _pe_proc_show_histo, "histo0")
OS_PROC_SEQRD_DEFINE_EX(_g_pe_proc_histo1_fops, _pe_proc_show_histo, "histo1")
OS_PROC_SEQRD_DEFINE_EX(_g_pe_proc_hdr_hist0_fops, _pe_proc_show_histo, "hdr-hist0")
OS_PROC_SEQRD_DEFINE_EX(_g_pe_proc_hdr_hist1_fops, _pe_proc_show_histo, "hdr-hist1")

static OS_PROC_DESC_TABLE_T	_g_pe_device_proc_table[] =
{
	{ "version",            PROC_ID_VERSION,            OS_PROC_FLAG_READ  },
	{ "command",            PROC_ID_COMMAND,            OS_PROC_FLAG_WRITE },
	{ "dbg_wrap_func",      PROC_ID_DBG_WRAP_FUNC,      OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "dbg_kdrv_func",      PROC_ID_DBG_KDRV_FUNC,      OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "hdr_func",           PROC_ID_HDR_FUNC,           OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "mask_ioctl",         PROC_ID_MASK_IOCTL,         OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "bypass_block",       PROC_ID_BYPASS_BLOCK,       OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "pm_test",            PROC_ID_PM_TEST,            OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "latency",            PROC_ID_DBG_LATENCY,        OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cid_mask",           PROC_ID_CID_MASK,           OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE },
	{ "cid_list",           PROC_ID_CID_LIST,           OS_PROC_FLAG_SEQRD,(void*)&_g_pe_proc_cid_list_fops},
	{ "histo0",             PROC_ID_HISTO0,             OS_PROC_FLAG_SEQRD,(void*)&_g_pe_proc_histo0_fops},
	{ "histo1",             PROC_ID_HISTO1,             OS_PROC_FLAG_SEQRD,(void*)&_g_pe_proc_histo1_fops},
	{ "pe-ddr",             PROC_ID_PE_DDR,             OS_PROC_FLAG_SEQRD,(void*)&_g_pe_proc_pe_ddr_fops},
	{ "hdr-hist0",          PROC_ID_HDR_HIST0,          OS_PROC_FLAG_SEQRD,(void*)&_g_pe_proc_hdr_hist0_fops},
	{ "hdr-hist1",          PROC_ID_HDR_HIST1,          OS_PROC_FLAG_SEQRD,(void*)&_g_pe_proc_hdr_hist1_fops},
	{ NULL,                 PROC_ID_MAX,                0                  }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
static int pe_proc_show_version(struct seq_file *m)
{
    char chip_name[8];

	if (!m)	return 0;

	memset(chip_name,0,8);
	if (PE_KDRV_VER_O22BX)		snprintf(chip_name, 8, "o22b0");
	else if (PE_KDRV_VER_O22AX)	snprintf(chip_name, 8, "o22a0");
	else if (PE_KDRV_VER_E60BX)	snprintf(chip_name, 8, "e60b0");
	else if (PE_KDRV_VER_E60AX)	snprintf(chip_name, 8, "e60a0");
	else if (PE_KDRV_VER_O20BX)	snprintf(chip_name, 8, "o20b0");
	else if (PE_KDRV_VER_O20AX)	snprintf(chip_name, 8, "o20a0");
	else if (PE_KDRV_VER_M19)	snprintf(chip_name, 8, "m16p3");
	seq_printf(m, "chip_name=%s\n",chip_name);

	return 0;
}

static int pe_proc_show(struct seq_file *m, void *v)
{
	if (!m)	return 0;

	pe_proc_show_version(m);

	pe_proc_show_status(m);

    return 0;
}

static int _pe_proc_show_cid_list(struct seq_file *m)
{
	int len = 0;
	unsigned int i,n;
	int start = V4L2_CID_USER_EXT_PQ_BASE;

	seq_printf(m,"-------------------------------------------------------------------------\n");
	for (i=start, n=0xff; i<(start+0x1000); i++)
	{
		if (!strncasecmp(vpq_ctrl_id_to_str(i), "V4L2_CID_EXT_UNKOWN", strlen("V4L2_CID_EXT_UNKOWN"))) {
			i = start + n;
			n += 0x100;
			continue;
		}
		seq_printf(m,"%-50s = 0x%08x (%d)\n", vpq_ctrl_id_to_str(i), i, i);
	}
	seq_printf(m,"-------------------------------------------------------------------------\n");
	return len;
}

static int _pe_proc_show_pe_ddr(struct seq_file *m)
{
	if (!m)	return 0;
	pe_inf_proc_show_db(0, (void *)m, NULL);
	return 0;
}

static int _pe_proc_show_histo(struct seq_file *m, void* data)
{
	char *name = (char*)data;
	struct entry {
		char *name;
		int (*func)(int, void *, void *);
		int id;
	} *p, entry_list[] = {
		{.name="histo0",    .func=pe_hst_proc_show_histo, .id=0},
		{.name="histo1",    .func=pe_hst_proc_show_histo, .id=1},
		{.name="hdr-hist0", .func=pe_hdr_proc_show_histo, .id=0},
		{.name="hdr-hist1", .func=pe_hdr_proc_show_histo, .id=1},
		{.name=NULL}
	};

	if (!m || !data) {
		return 0;
	}

	for (p = entry_list; p->name != NULL; p++) {
		if (!strncmp(p->name, name, strlen(p->name))) {
			if (p->func) {
				seq_printf(m,"name:%s id:%d\n",p->name,p->id);
				p->func(p->id,(void *)m,NULL);
			}
			break;
		}
	}

	return 0;
}

static int pe_proc_open(struct inode *inode, struct file *file)
{
	int ret;

	if (!file)	return 0;

	ret = single_open (file, pe_proc_show, NULL);
	if (ret < 0)
		return ret;

	return ret;
}
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops pe_proc_fops = {
	.proc_open = pe_proc_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations pe_proc_fops = {
	.open = pe_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif
/*
 * read_proc implementation of pe device
 *
*/
static int _PE_ReadProcFunction(UINT32 procId, char* buffer)
{
	int ret = RET_OK;;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_VERSION:
		{
			ret = snprintf( buffer, 48, "%s\n", "20210514 10:35" );
		}break;
		case PROC_ID_DBG_WRAP_FUNC:
		{
			ret = pe_proc_dbg_wrap_help(buffer);
		}break;
		case PROC_ID_DBG_KDRV_FUNC:
		{
			pe_proc_dbg_kdrv_help();
		}break;
		case PROC_ID_HDR_FUNC:
		{
			ret = pe_proc_hdr_help(buffer);
		}break;
		case PROC_ID_MASK_IOCTL:
		{
			ret = v4l2_vpq_get_ioctl_mask(buffer);
		}break;
		case PROC_ID_CID_MASK:
		{
			ret = v4l2_vpq_get_cid_mask(buffer);
		}break;
		case PROC_ID_BYPASS_BLOCK:
		{
			ret = v4l2_vpq_cmn_get_bypass_block(buffer);
		}break;
		case PROC_ID_PM_TEST :
		{
			ret = v4l2_vpq_pm_runtime_help(buffer);
			ret += v4l2_lgsr_pm_runtime_help(buffer+ret);
		}break;
		case PROC_ID_DBG_LATENCY:
		{
			ret = sprintf( buffer, "latency : %d\n", v4l2_vpq_latency_get_debug());
		}break;
		default:
		{
			ret = snprintf( buffer, 48, "%s(%d)\n", "unimplemented read proc", procId );
		}break;
	}

	return ret;
}

/*
 * write_proc implementation of pe device
 *
*/
static int _PE_WriteProcFunction(UINT32 procId, char* command)
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			printk("do nothing\n");
		}break;
		case PROC_ID_DBG_WRAP_FUNC:
		{
			pe_proc_dbg_wrap_func(command);
		}break;
		case PROC_ID_DBG_KDRV_FUNC:
		{
			pe_proc_dbg_kdrv_func(command);
		}break;
		case PROC_ID_HDR_FUNC:
		{
			pe_proc_hdr_func(command);
		}break;
		case PROC_ID_MASK_IOCTL:
		{
			int mask;
			sscanf(command," %x",&mask);
			v4l2_vpq_set_ioctl_mask(mask);
		}break;
		case PROC_ID_CID_MASK:
		{
			int mask;
			sscanf(command," %x",&mask);
			v4l2_vpq_set_cid_mask(mask);
		}break;
		case PROC_ID_BYPASS_BLOCK:
		{
			int mask;
			sscanf(command," %x",&mask);
			v4l2_vpq_cmn_set_bypass_block(mask);
		}break;
		case PROC_ID_PM_TEST:
		{
			if (!strncasecmp(command, "lgsr_", strlen("lgsr_"))) {
				v4l2_lgsr_pm_runtime_test(command);
			}
			else
			{
				v4l2_vpq_pm_runtime_test(command);
			}
		}break;
		case PROC_ID_DBG_LATENCY:
		{
			UINT32 latency;
			sscanf(command," %d", &latency);
			v4l2_vpq_latency_set_debug(latency);
		}break;
		default:
		{
			/* do nothing */
		}break;
	}

	return strlen(command);
}

void	PE_PROC_Init (void)
{
	struct proc_dir_entry *proc_pe;

	proc_pe = OS_PROC_CreateEntryEx ( PE_MODULE, _g_pe_device_proc_table,
											_PE_ReadProcFunction,
											_PE_WriteProcFunction );

	if (!proc_pe)
	{
		PE_PRINT_ERROR("proc_pe is not ready\n");
		return;
	}

	proc_create_data("pe-status", 0440, proc_pe, &pe_proc_fops, NULL);

	pe_proc_hdr_init(proc_pe);

	return;
}

void	PE_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( PE_MODULE );
}

/** @} */

