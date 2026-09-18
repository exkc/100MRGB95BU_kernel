/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2016 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

/** @file vpq_proc.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author
 *  @version	1.0
 *  @date
 *  @note		Additional information.
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
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"
#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"
#include "pe_cfg.h"
#include "pe_def.h"
#include "v4l2_vpq.h"
#include "v4l2_vpq_cmn.h"
#include "v4l2_vpq_be.h"
#include "v4l2_vpq_hdr.h"
#include "v4l2_vpq_pe.h"
#include "v4l2_dolby.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
void vpq_proc_init(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
static int vpq_proc_show_version(struct seq_file *m, void *v)
{
    char chip_name[8];

	if (!m)	return 0;

	memset(chip_name,0,8);
	if (PE_KDRV_VER_M23)		snprintf(chip_name, 8, "m23");
	else if (PE_KDRV_VER_O22)	snprintf(chip_name, 8, "o22");
	else if (PE_KDRV_VER_E60BX)	snprintf(chip_name, 8, "e60b0");
	else if (PE_KDRV_VER_E60AX)	snprintf(chip_name, 8, "e60a0");
	else if (PE_KDRV_VER_O20BX)	snprintf(chip_name, 8, "o20b0");
	else if (PE_KDRV_VER_O20AX)	snprintf(chip_name, 8, "o20a0");
	else if (PE_KDRV_VER_M19)	snprintf(chip_name, 8, "m16p3");
	seq_printf(m, "chip_name=%s\n",chip_name);

	return 0;
}
static int vpq_proc_show_srcinfo(struct seq_file *m, void *v)
{
	int ret;
	ret = vpq_proc_show_status_srcinfo(m, v);
	return ret;
}

static int vpq_proc_show_status(struct seq_file *m, void *v, int id)
{
	if (!m)	return 0;

//	seq_printf(m, "%s=",vpq_ctrl_id_to_str(id)+13);

	switch (id) {
		case V4L2_CID_EXT_VPQ_LOW_DELAY_MODE:
		case V4L2_CID_EXT_VPQ_TESTPATTERN:
		case V4L2_CID_EXT_VPQ_PICTURE_CTRL:
		case V4L2_CID_EXT_VPQ_BLACK_LEVEL:
		case V4L2_CID_EXT_VPQ_REAL_CINEMA:
		case V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN:
			seq_printf(m, "%s=",vpq_ctrl_id_to_str(id)+13);
			vpq_proc_show_status_pe(m,v,id);
			break;
		case V4L2_CID_EXT_LED_DEMOMODE:
		case V4L2_CID_EXT_LED_CONTROL_SPI:
		case V4L2_CID_EXT_LED_DB_IDX:
		case V4L2_CID_EXT_LED_EN:
#ifdef INCLUDE_KDRV_BE
			seq_printf(m, "%s=",vpq_ctrl_id_to_str(id)+13);
			vpq_proc_show_status_be(m,v,id);
#endif
			break;
		case V4L2_CID_EXT_MEMC_LOW_DELAY_MODE:
#ifdef INCLUDE_KDRV_BE
			vpq_proc_show_status_be(m,v,id);
#endif
			break;
		case V4L2_CID_EXT_MEMC_MOTION_PRO:
		case V4L2_CID_EXT_MEMC_MOTION_COMP:
		case V4L2_CID_EXT_VPQ_COLORTEMP_DATA:
		case V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST:
		case V4L2_CID_EXT_DOLBY_PWM_RATIO:
#ifdef INCLUDE_KDRV_BE
			seq_printf(m, "%s=",vpq_ctrl_id_to_str(id)+13);
			vpq_proc_show_status_be(m,v,id);
#endif
			break;
		case V4L2_CID_EXT_HDR_COLOR_CORRECTION:
		case V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL:
			seq_printf(m, "%s=",vpq_ctrl_id_to_str(id)+13);
			vpq_proc_show_status_hdr(m,v,id,0);
			break;
		case V4L2_CID_EXT_VPQ_BYPASS_BLOCK:
		case V4L2_CID_EXT_VPQ_PQ_MODE_INFO:
			seq_printf(m, "%s=",vpq_ctrl_id_to_str(id)+13);
			vpq_proc_show_status_cmn(m,v,id,0);
			break;
		case V4L2_CID_EXT_DOLBY_PICTURE_MODE:
		case V4L2_CID_EXT_DOLBY_PICTURE_MENU:
			#ifdef INCLUDE_KDRV_DE
			seq_printf(m, "%s=",vpq_ctrl_id_to_str(id)+13);
			vpq_proc_show_status_dolby(m,v,id);
			#endif
			break;
		default:
			seq_printf(m, "{not support}\n");
			break;
	}
	return 0;
}

static int vpq_proc_show(struct seq_file *m, void *v)
{
	if (!m)	return 0;

	vpq_proc_show_version(m,v);
	vpq_proc_show_srcinfo(m,v);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_LED_DEMOMODE);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_LED_EN);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_LED_DB_IDX);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_LED_CONTROL_SPI);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_MEMC_LOW_DELAY_MODE);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_MEMC_MOTION_COMP);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_MEMC_MOTION_PRO);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_HDR_COLOR_CORRECTION);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_HDR_HLG_Y_GAIN_TBL);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_DOLBY_PICTURE_MODE);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_DOLBY_PICTURE_MENU);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_DOLBY_PWM_RATIO);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_PICTURE_CTRL);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_BYPASS_BLOCK);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_BLACK_LEVEL);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_LOW_DELAY_MODE);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_DYNAMIC_CONTRAST_COLOR_GAIN);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_TESTPATTERN);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_COLORTEMP_DATA);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_REAL_CINEMA);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_GAMUT_MATRIX_POST);
	vpq_proc_show_status(m,v,V4L2_CID_EXT_VPQ_PQ_MODE_INFO);

    return 0;
}

static int vpq_proc_open(struct inode *inode, struct file *file)
{
	int ret;

	if (!file)	return 0;

	ret = single_open (file, vpq_proc_show, NULL);
	if (ret < 0)
		return ret;

	return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(6, 11, 0))
static const struct proc_ops vpq_proc_fops = {
	.proc_open = vpq_proc_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};
#else
static struct file_operations vpq_proc_fops = {
	.open = vpq_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};
#endif

void vpq_proc_init(void)
{
	struct proc_dir_entry *proc_vpq;
	struct proc_dir_entry *proc_entry = OS_PROC_GetLinuxTvEntry();

	if (!proc_entry)
	{
		PE_PRINT_ERROR("proc_entry is not ready\n");
		return;
	}

	proc_vpq = proc_mkdir ("vpq", proc_entry);

	proc_create_data("pq-status", 0440, proc_vpq, &vpq_proc_fops, NULL);

	return;
}

/** @} */

