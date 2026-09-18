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
 *  Linux proc interface for ci device.
 *	ci device will teach you how to make device driver with new platform.
 *
 *  author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com) /  Hwajeong Lee (hwajeong.lee@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
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
#include <linux/init.h>
#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>
#include <linux/mm.h>
#include <linux/rmap.h>
#include <linux/poll.h>
#include <linux/version.h>
#include <linux/smp.h>
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <linux/clk.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/pm_runtime.h>
#include <linux/suspend.h>
#include <linux/namei.h>
#include <linux/path.h>
#include <asm/div64.h>
#include <asm/page.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include <asm/memory.h>

#include "ci_dev.h"
#include "ci_hw_ops.h"
#include "ci_hw_cis.h"
#include "ci_proc.h"
#include "ci_util.h"

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
	PROC_ID_AUTHOR		= 0,
	PROC_ID_COMMAND,
	PROC_ID_DELAY,
	/* */
	PROC_ID_PCAP_DUMP	= 0x10,
	PROC_ID_PCAP_SHOW,
	PROC_ID_PCAP_SIZE,
	PROC_ID_STAT_CAM,
	/* */
	PROC_ID_STAT_ERR	= 0x20,
	PROC_ID_STAT_PERF,
	PROC_ID_STAT_REG,
	/* */
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
#if defined(CI_PROC_PCAP_ON)
extern struct file_operations ci_pcap_dump_fops;
extern struct file_operations ci_pcap_show_fops;
extern struct file_operations ci_pcap_size_fops;
#endif

extern int ci_pcap_mon_init(CI_DEV_T *cidev);
extern int ci_pcap_mon_uninit(CI_DEV_T *cidev);

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#define CI_PROC_TIME_FORMAT		"%5ld.%06ld"

#define PCAP_ROOT_NAME		"pcap"
#define PCAP_DUMP_NAME		"pcap_dump"
#define PCAP_SHOW_NAME		"pcap_show"
#define PCAP_SIZE_NAME		"pcap_size"

#define STAT_ROOT_NAME		"stat"
#define STAT_CAM_NAME		"stat_cam"
#define STAT_ERR_NAME		"stat_err"
#define STAT_PERF_NAME		"stat_perf"
#define STAT_REG_NAME		"stat_reg"

static int proc_read_delay(char* buf)
{
	int i, ret = 0;
	CI_DEV_T* dev = CI_GetDevs();
	UINT32 *d = dev->cfg->delays;

	for(i=0; i< DELAY_ENTRY_MAX; i++)
	{
		ret += snprintf(buf + ret, OS_PROC_RD_BUF_SZ, "[%02d] %-32s = [%4d]\n",
						i, ci_get_delaystr(i), d[i]);
	}

	return ret;
}

static void proc_write_delay(char* cmd)
{
	UINT32 type, val;
	CI_DEV_T* dev = CI_GetDevs();
	UINT32 *d = dev->cfg->delays;
	int rc;

	rc = sscanf( cmd, "%d %d", &type, &val);
	if(rc != 2) goto usage;

	if(type >= DELAY_ENTRY_MAX)
	{
		printk(KERN_ERR "type should be < %d\n", DELAY_ENTRY_MAX);
		goto usage;
	}

	d[type] = val;
	printk(KERN_ERR "Set %s as [%4d] ms\n", ci_get_delaystr(type), d[type]);

	return;
usage:
	printk(KERN_ERR "\n");
	printk(KERN_ERR "usage> type val\n");
}

//CI_OS_PROC_BASE
/*
 * read_proc implementation of ci device
 *
*/
static int _ci_read_proc_function(u32 proc_id, char *buf)
{
	int	ret = 0;

	/* TODO: add your proc_write implementation */
	switch (proc_id) {
	case PROC_ID_AUTHOR:
		ret = snprintf(buf, OS_PROC_RD_BUF_SZ, "%s\n", "Hyunho Kim (hyunho747.kim@lge.com)");
		break;
	case PROC_ID_DELAY:
		{
			ret = proc_read_delay(buf);
			break;
		}
	default:
		ret = snprintf(buf, OS_PROC_RD_BUF_SZ, "%s(%d)\n", "unimplemented read proc", proc_id);
		break;
	}

	return ret;
}

/**
 * write_proc implementation of ci device
 *
*/
static int _ci_write_proc_function(u32 proc_id, char* cmd)
{
	/* TODO: add your proc_write implementation */
	switch (proc_id) {
	case PROC_ID_COMMAND:
		printk("command string : %s\n", cmd);
		break;
	case PROC_ID_DELAY:
		proc_write_delay(cmd);
		break;

	default:
		/* do nothing */
		break;
	}

	return strlen(cmd);
}

#define DEFINE_CI_STAT_FOPS(_name)	\
	static int ci_stat_##_name##_show(struct seq_file *m, void *v)	\
	{	\
		CI_DEV_T *cidev = (CI_DEV_T *)m->private;	\
		if (!capable(CAP_SYS_ADMIN)) {	\
			LOG_ERROR("capable(CAP_SYS_ADMIN) error\n");	\
			return -EPERM;	\
		}	\
		if (cidev == NULL) {	\
			LOG_ERROR("NULL cidev\n");	\
			return -ENODEV;	\
		}	\
		CI_MUTEX_LOCK(cidev);	\
		ci_stat_##_name##_info(m, cidev);	\
		CI_MUTEX_UNLOCK(cidev);	\
		return 0;	\
	}	\
	static int ci_stat_##_name##_open(struct inode *inode, struct file *file)	\
	{	\
		return single_open(file, ci_stat_##_name##_show, PDE_DATA(inode));	\
	}	\
	static const struct file_operations ci_stat_##_name##_fops = {	\
		.owner		= THIS_MODULE,	\
		.open		= ci_stat_##_name##_open,	\
		.read		= seq_read,	\
		.llseek		= seq_lseek,	\
		.release	= single_release,	\
	}

#define CI_STAT_PREFIX		" "

#define ci_stat_printf(m, format, args...)	\
	seq_printf(m, CI_STAT_PREFIX format, ##args)

#define ci_stat_reg_printf(_m, _cidev, _reg, _name)	\
	ci_stat_printf(_m, "[0x%02X] %32s [0x%04X]\n", _reg, _name, CI_READ16(_cidev, _reg))

static void ci_stat_reg_info(struct seq_file *m, CI_DEV_T *cidev)
{
	seq_printf(m, "[%s reg. status]\n", ci_dev_name(cidev));

	ci_stat_reg_printf(m, cidev, CREG_CTRL_STATUS_1, "Control and Status 1");
	ci_stat_reg_printf(m, cidev, CREG_CTRL_STATUS_2, "Control and Status 2");
	ci_stat_reg_printf(m, cidev, CREG_CTRL_STATUS_3, "Control and Status 3");
	ci_stat_reg_printf(m, cidev, CREG_PC_CARD_CTRL_1, "PC Card Control 1");
	ci_stat_reg_printf(m, cidev, CREG_PC_CARD_CTRL_2, "PC Card Control 2");
	ci_stat_reg_printf(m, cidev, CREG_PC_CARD_CTRL_3, "PC Card Control 3");
	ci_stat_reg_printf(m, cidev, CREG_BUSRT_CTRL, "Burst Control");
	ci_stat_reg_printf(m, cidev, CREG_INTR_FLAG, "Interrupt Flag");
	ci_stat_reg_printf(m, cidev, CREG_INTR_MASK, "Interrupt Mask");
	ci_stat_reg_printf(m, cidev, CREG_INTR_CTRL, "Interrupt Control");
	ci_stat_reg_printf(m, cidev, CREG_PCMCIA_IDX, "PCMCIA Address Index");
	ci_stat_reg_printf(m, cidev, CREG_HS_CTRL_1, "Power On Interval 1");
	ci_stat_reg_printf(m, cidev, CREG_HS_CTRL_2, "Power On Interval 2");
	ci_stat_reg_printf(m, cidev, CREG_HS_CTRL_3, "Enable Interval 1");
	ci_stat_reg_printf(m, cidev, CREG_HS_CTRL_4, "Enable Interval 2");
	ci_stat_reg_printf(m, cidev, CREG_HS_CTRL_5, "Card Insert Done Interval 1");
	ci_stat_reg_printf(m, cidev, CREG_HS_CTRL_6, "Card Insert Done Interval 2");
	ci_stat_reg_printf(m, cidev, CREG_HS_CTRL_7, "Card Removal Done Interval 1");
	ci_stat_reg_printf(m, cidev, CREG_HS_CTRL_8, "Card Removal Done Interval 2");
	seq_putc(m, '\n');
}

DEFINE_CI_STAT_FOPS(reg);
/*
static int ci_stat_reg_show(struct seq_file *m, void *v)
{
	ci_stat_info_t *stat_info = (ci_stat_info_t *)m->private;
	CI_DEV_T *cidev;

	if (!capable(CAP_SYS_ADMIN)) {
		LOG_ERROR("capable(CAP_SYS_ADMIN) error\n");
		return -EPERM;
	}

	if (stat_info == NULL) {
		LOG_ERROR("NULL stat_info\n");
		return -ENODEV;
	}
	cidev = stat_info->cidev;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}

	ci_mutex_lock(cidev);

	ci_stat_reg_info(m, cidev);

	ci_mutex_unlock(cidev);

	return 0;
}

static int ci_stat_reg_open(struct inode *inode, struct file *file)
{
	return single_open(file, ci_stat_reg_show, PDE_DATA(inode));
}

static const struct file_operations ci_stat_reg_fops = {
	.owner		= THIS_MODULE,
	.open		= ci_stat_reg_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};
*/

static void ci_stat_perf_info(struct seq_file *m, CI_DEV_T *cidev)
{
	ktime_t w_time, r_time;
	s64 w_size, r_size;
	int w_speed, r_speed;

#if 1
	if (!ci_is_init_done(cidev)) {
		ci_stat_printf(m, "* CI Block Init not completed\n");
		return;
	}
#else
	if (!ci_is_card_detected(cidev)) {
		ci_stat_printf(m, "* CAM not inserted\n");
		return;
	}
	if (!ci_is_cam_init_done(cidev)) {
		ci_stat_printf(m, "* CAM Init not completed\n");
		return;
	}
#endif

	ci_dbg_perf_get_data(cidev, &w_time, &w_size, &r_time, &r_size);
	w_speed = ci_cal_mbps(w_size, w_time);
	r_speed = ci_cal_mbps(r_size, r_time);

	seq_printf(m, "[%s IO Perf. Estimated]\n", ci_dev_name(cidev));

	ci_stat_printf(m, " - Write : size[%16lld], elapsed[%16lld us] : %d.%03d Mbps\n",
			w_size, ktime_to_us(w_time), w_speed/1000, w_speed%1000);
	ci_stat_printf(m, " - Read  : size[%16lld], elapsed[%16lld us] : %d.%03d Mbps\n",
			r_size, ktime_to_us(r_time), r_speed/1000, r_speed%1000);
	seq_putc(m, '\n');
}

DEFINE_CI_STAT_FOPS(perf);
/*
static int ci_stat_perf_show(struct seq_file *m, void *v)
{
	ci_stat_info_t *stat_info = (ci_stat_info_t *)m->private;
	CI_DEV_T *cidev;

	if (!capable(CAP_SYS_ADMIN)) {
		LOG_ERROR("capable(CAP_SYS_ADMIN) error\n");
		return -EPERM;
	}

	if (stat_info == NULL) {
		LOG_ERROR("NULL stat_info\n");
		return -ENODEV;
	}
	cidev = stat_info->cidev;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}

	ci_mutex_lock(cidev);

	ci_stat_perf_info(m, cidev);

	ci_mutex_unlock(cidev);

	return 0;
}

static int ci_stat_perf_open(struct inode *inode, struct file *file)
{
	return single_open(file, ci_stat_perf_show, PDE_DATA(inode));
}

static const struct file_operations ci_stat_perf_fops = {
	.owner		= THIS_MODULE,
	.open		= ci_stat_perf_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};
*/

static void ci_stat_err_info(struct seq_file *m, CI_DEV_T *cidev)
{
	struct timeval tv;
	int err_cnt;
	int err_code;
	int i;
//	int ret = 0;

#if 1
	if (!ci_is_init_done(cidev)) {
		ci_stat_printf(m, "* CI Block Init not completed\n");
		return;
	}
#else
	if (!ci_is_card_detected(cidev)) {
		ci_stat_printf(m, "* CAM not inserted\n");
		return;
	}
	if (!ci_is_cam_init_done(cidev)) {
		ci_stat_printf(m, "* CAM Init not completed\n");
		return;
	}
	if (!ci_is_cam_cis_done(cidev)) {
		ci_stat_printf(m, "* CAM CIS-Check not completed\n");
		return;
	}
	if (!ci_is_cam_cor_done(cidev)) {
		ci_stat_printf(m, "* CAM COR-Write not completed\n");
		return;
	}
	if (!ci_is_cam_nego_done(cidev)) {
		ci_stat_printf(m, "* CAM Nego-Buff not completed\n");
		return;
	}
#endif

	seq_printf(m, "[%s err info]\n", ci_dev_name(cidev));

	/*
	 * These list data are maintained until new CAM operation begins
	 */
	ci_io_lock(cidev);

	ci_stat_printf(m, "[IO Write Error List]\n");
	err_cnt = ci_get_io_wr_err_cnt(cidev);
	if (err_cnt) {
		for (i = 0; i < err_cnt; i++) {
			tv = ktime_to_timeval(ci_get_io_wr_err_time(cidev, i));
			err_code = ci_get_io_wr_err_code(cidev, i);
			ci_stat_printf(m, " [%d] " CI_PROC_TIME_FORMAT " code = 0x%02X\n",
						i, tv.tv_sec, tv.tv_usec, err_code);
		}
	} else {
		ci_stat_printf(m, "* No Error Detected\n");
	}
	seq_putc(m, '\n');

	ci_stat_printf(m, "[IO Read Error List]\n");
	err_cnt = ci_get_io_rd_err_cnt(cidev);
	if (err_cnt) {
		for (i = 0; i < err_cnt; i++) {
			tv = ktime_to_timeval(ci_get_io_rd_err_time(cidev, i));
			err_code = ci_get_io_rd_err_code(cidev, i);
			ci_stat_printf(m, " [%d] " CI_PROC_TIME_FORMAT " code = 0x%02X\n",
						i, tv.tv_sec, tv.tv_usec, err_code);
		}
	} else {
		ci_stat_printf(m, "* No Error Detected\n");
	}
	seq_putc(m, '\n');

	ci_io_unlock(cidev);
}

DEFINE_CI_STAT_FOPS(err);
/*
static int ci_stat_err_show(struct seq_file *m, void *v)
{
	ci_stat_info_t *stat_info = (ci_stat_info_t *)m->private;
	CI_DEV_T *cidev;

	if (!capable(CAP_SYS_ADMIN)) {
		LOG_ERROR("capable(CAP_SYS_ADMIN) error\n");
		return -EPERM;
	}

	if (stat_info == NULL) {
		LOG_ERROR("NULL stat_info\n");
		return -ENODEV;
	}
	cidev = stat_info->cidev;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}

	ci_mutex_lock(cidev);

	ci_stat_err_info(m, cidev);

	ci_mutex_unlock(cidev);

	return 0;
}

static int ci_stat_err_open(struct inode *inode, struct file *file)
{
	return single_open(file, ci_stat_err_show, PDE_DATA(inode));
}

static const struct file_operations ci_stat_err_fops = {
	.owner		= THIS_MODULE,
	.open		= ci_stat_err_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};
*/

static void ci_stat_cam_info_cis_time(struct seq_file *m,
									char *pformat,
									ktime_t time_t,
									int rbyte)
{
	__kernel_time_t time_s, time_ms, time_us;
	struct timeval tv;
	char tstring[64];

	tv = ktime_to_timeval(time_t);
	time_s = tv.tv_sec;
	time_ms = tv.tv_usec / USEC_PER_MSEC;
	time_us = tv.tv_usec % USEC_PER_MSEC;

	if (time_s || (time_ms > 99L)) {
		snprintf(tstring, sizeof(tstring), "%s %ld.%03ld s", pformat, time_s, time_ms);
	} else if (time_ms) {
		snprintf(tstring, sizeof(tstring), "%s %ld.%03ld ms", pformat, time_ms, time_us);
	} else {
		snprintf(tstring, sizeof(tstring), "%s %ld us", pformat, time_us);
	}
	ci_stat_printf(m, "%s (%d)\n", tstring, rbyte);
}

struct cft_inf_type_info {
	int		dedicated;
	char	*name;
};
typedef struct cft_inf_type_info cft_inf_type_info_t;

static const cft_inf_type_info_t cft_inf_type[] = {
	[0]	= {1, "Memory"},
	[1] = {1, "I/O and Memory"},
	[2] = {0, NULL},
	[3] = {0, NULL},
	[4] = {1, "Custom Interface 0"},
	[5] = {1, "Custom Interface 1"},
	[6] = {1, "Custom Interface 2"},
	[7] = {1, "Custom Interface 3"},
};

static char *ci_get_cft_inf_type_name(int idx)
{
	cft_inf_type_info_t *inf_type;
	char *name = NULL;

	if (idx < ARRAY_SIZE(cft_inf_type)) {
		inf_type = (cft_inf_type_info_t *)&cft_inf_type[idx];
		name = (inf_type->dedicated)? inf_type->name : NULL;
	}
	return name;
}

static int _ci_stat_cam_info_cis_info(struct seq_file *m, ci_dev_cis_info_t *cis_info)
{
	cis_status_t *cis_status = &cis_info->info_status;
	ktime_t time_t;
	int cis_step = cis_info->cis_step;

#if 1
	if (cis_step == CIS_CHECK_STEP_NONE) {
		ci_stat_printf(m, "* CAM CIS-Check not completed\n");
		return -EFAULT;
	}
#else
	if (!ci_is_cam_cis_done(cidev)) {
		ci_stat_printf(m, "* CAM CIS-Check not completed\n");
		return -EFAULT;
	}
#endif

	ci_stat_printf(m, "[CIS-Check Result]\n");
	ci_stat_printf(m, " - Op. Retry Count       : %d\n", cis_info->retry);
	time_t = ktime_sub(cis_info->end_1st_t, cis_info->start_t);
	ci_stat_cam_info_cis_time(m, " - Op. Time(1st tuple)   :", time_t, cis_info->rcnt_1st_det);
	time_t = ktime_sub(cis_info->end_last_t, cis_info->end_1st_t);
	ci_stat_cam_info_cis_time(m, " - Op. Time(Analysis)    :", time_t, cis_info->rcnt_analysis);

	if (ci_chk_compliance(cis_status) != DVB_CI_COMPLIANT) {
		ci_stat_printf(m, "* Non DVB-CI device, last step[%d]\n", cis_step);
		return -EFAULT;
	}
	if (cis_step < CIS_CHECK_STEP_LAST_DONE) {
		ci_stat_printf(m, "* CIS-Check not completed, last step[%d]\n", cis_step);
		return -EFAULT;
	}

	return 0;
}

static void _ci_stat_cam_info_cis_vers_1(struct seq_file *m, ci_dev_cis_info_t *cis_info)
{
	cis_vers_1_t *cis_vers_1 = &cis_info->info_vers_1;

	ci_stat_printf(m, " - CISTPL_VERS_1\n");
	ci_stat_printf(m, "   Version               : Major(0x%02X), Minor(0x%02X)\n",
				cis_vers_1->major, cis_vers_1->minor);
	ci_stat_printf(m, "   Manufact. / Product   : %s / %s\n",
				cis_vers_1->manufact, cis_vers_1->product);
	ci_stat_printf(m, "   Add1 / Add2 Str.      : %s / %s\n",
				cis_vers_1->add1, cis_vers_1->add2);
	ci_stat_printf(m, "   Is it CI+ CAM         : %d[%s]\n",cis_vers_1->is_ci_plus,
											(cis_vers_1->is_ci_plus)? "yes" : "no");
	if (!cis_vers_1->is_ci_plus) {
		return;
	}

	ci_stat_printf(m, "   CI+ Version           : 0x%08X\n", cis_vers_1->version);
	ci_stat_printf(m, "   CI+ Profile           : 0x%08X\n", cis_vers_1->profile);
}

static void _ci_stat_cam_info_cis_config(struct seq_file *m, ci_dev_cis_info_t *cis_info)
{
	cis_config_t *cis_config = &cis_info->info_config;
	cis_ccst_cif_t *ccst_cif = &cis_config->ccst_cif;

	ci_stat_printf(m, " - CISTPL_CONFIG\n");
	ci_stat_printf(m, "   TPCC_xxxx             : RASZ(%d), RMSZ(%d), RFSZ(%d)\n",
				cis_config->tpcc_rasz, cis_config->tpcc_rmsz, cis_config->tpcc_rfsz);
	ci_stat_printf(m, "   Last Entry / COR Addr : 0x%02X / 0x%04X\n",
				cis_config->last_index, cis_config->base_addr);
	ci_stat_printf(m, "   I/F ID / Desc. Str.   : 0x%04X / %s\n",
				ccst_cif->if_id_num, ccst_cif->str);
}

static void _ci_stat_cam_info_cis_cftable(struct seq_file *m, ci_dev_cis_info_t *cis_info)
{
	cis_cftable_entry_t *cis_cftable = &cis_info->info_cftable;
	cis_cftable_feature_t *feat = &cis_cftable->feat;
	cis_stce_evpd_t *stce_evpd = &cis_cftable->stce_evpd;
	int idx, feature;
	char *cft_type_name;

	ci_stat_printf(m, " - CISTPL_CFTABLE_ENTRY\n");
	idx = cis_cftable->idx;
	ci_stat_printf(m, "   CFTABLE - Index       : 0x%02X\n", idx);
	ci_stat_printf(m, "               x... .... : Interface        - 0x%02X\n", (idx>>7)&0x01);
	ci_stat_printf(m, "               .x.. .... : Default          - 0x%02X\n", (idx>>6)&0x01);
	ci_stat_printf(m, "               ..xx xxxx : Config Entry Num - 0x%02X\n", CIS_CFTABLE_ENTRY_NUM(idx));

	cft_type_name = ci_get_cft_inf_type_name(cis_cftable->intf & 0x0F);
	ci_stat_printf(m, "   CFTABLE - I/F Type    : 0x%02X [%s]\n",
				cis_cftable->intf,
				(cft_type_name != NULL)? cft_type_name : "Reserved for future standardization");

	feature = cis_cftable->feature;
	ci_stat_printf(m, "   CFTABLE - Feature Sel : 0x%02X\n", feature);
	ci_stat_printf(m, "               x... .... : Misc             - 0x%02X [0x%02X]\n", feat_flag_misc(feat), feat->misc);
	ci_stat_printf(m, "               .xx. .... : Mem space        - 0x%02X [0x%02X]\n", feat_flag_mem_space(feat), feat->mem_space);
	ci_stat_printf(m, "               ...x .... : IRQ              - 0x%02X [0x%02X]\n", feat_flag_irq(feat), feat->irq);
	ci_stat_printf(m, "               .... x... : IO Space         - 0x%02X [0x%02X]\n", feat_flag_io_space(feat), feat->io_space);
	ci_stat_printf(m, "               .... .x.. : Time             - 0x%02X [0x%02X]\n", feat_flag_time(feat), feat->time);
	ci_stat_printf(m, "               .... ..xx : Power            - 0x%02X\n", feat_flag_power(feat));

	ci_stat_printf(m, "   Env. / Phy. Dev Str.  : %s / %s\n",
				stce_evpd->environment, stce_evpd->physical_dev);
}

static void ci_stat_cam_info_cis(struct seq_file *m, CI_DEV_T *cidev)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;

	if (_ci_stat_cam_info_cis_info(m, cis_info) != 0) {
		return;
	}

	_ci_stat_cam_info_cis_vers_1(m, cis_info);
	_ci_stat_cam_info_cis_config(m, cis_info);
	_ci_stat_cam_info_cis_cftable(m, cis_info);

	seq_putc(m, '\n');
}

static void ci_stat_cam_info_cor(struct seq_file *m, CI_DEV_T *cidev)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_config_t *cis_config = &cis_info->info_config;
	cis_cftable_entry_t *cis_cftable = &cis_info->info_cftable;

#if 1
	if (cis_info->cor_step == COR_WRITE_STEP_NONE) {
		ci_stat_printf(m, "* CAM COR-Write not completed\n");
		return;
	}
#else
	if (!ci_is_cam_cor_done(cidev)) {
		ci_stat_printf(m, "* CAM COR-Write not completed\n");
		return;
	}
#endif

	ci_stat_printf(m, "[COR-Write Result]\n");
	ci_stat_printf(m, " - Index     : 0x%02X\n", CIS_CFTABLE_ENTRY_NUM(cis_cftable->idx));
	ci_stat_printf(m, " - Base Addr : 0x%08X\n", cis_config->base_addr);
	seq_putc(m, '\n');
}

static void ci_stat_cam_info_nego(struct seq_file *m, CI_DEV_T *cidev)
{
	int buff_size = 0;

#if 1
	if (ci_nego_step(cidev) == CI_NEGO_STEP_NONE) {
		ci_stat_printf(m, "* CAM Nego-Buff not completed\n");
		return;
	}
#else
	if (!ci_is_cam_nego_done(cidev)) {
		ci_stat_printf(m, "* CAM Nego-Buff not completed\n");
		return;
	}
#endif
	if (ci_nego_step(cidev) < CI_NEGO_STEP_SET_BUFF_SIZE) {
		ci_stat_printf(m, "* Nego-Buff not completed, last step[%d]\n", ci_nego_step(cidev));
		return;
	}

	buff_size = ci_nego_buff_size(cidev);
	ci_stat_printf(m, "[Nego-Buff Result]\n");
	ci_stat_printf(m, " - Buffer Size = %d[0x%04X]\n", buff_size, buff_size);
	seq_putc(m, '\n');
}

static void ci_stat_cam_info_bus(struct seq_file *m, CI_DEV_T *cidev)
{
	ci_stat_printf(m, "[IO Bus Speed]\n");
	ci_stat_printf(m, " - Speed   : 0x%02X\n", ci_bus_speed(cidev));
	ci_stat_printf(m, " - Param 1 : 0x%04X\n", ci_bus_param_1(cidev));
	ci_stat_printf(m, " - Param 2 : 0x%04X\n", ci_bus_param_2(cidev));
	seq_putc(m, '\n');
}

static void ci_stat_cam_info(struct seq_file *m, CI_DEV_T *cidev)
{
//	int ret = 0;

#if 1
	if (!ci_is_init_done(cidev)) {
		ci_stat_printf(m, "* CI Block Init not completed\n");
		return;
	}
#else
	if (!ci_is_card_detected(cidev)) {
		ci_stat_printf(m, "* CAM not inserted\n");
		return;
	}
	if (!ci_is_cam_init_done(cidev)) {
		ci_stat_printf(m, "* CAM Init not completed\n");
		return;
	}
#endif

	seq_printf(m, "[%s cam info]\n", ci_dev_name(cidev));

	ci_stat_cam_info_cis(m, cidev);
	ci_stat_cam_info_cor(m, cidev);
	ci_stat_cam_info_nego(m, cidev);
	ci_stat_cam_info_bus(m, cidev);
}

DEFINE_CI_STAT_FOPS(cam);
/*
static int ci_stat_cam_show(struct seq_file *m, void *v)
{
	ci_stat_info_t *stat_info = (ci_stat_info_t *)m->private;
	CI_DEV_T *cidev;

	if (!capable(CAP_SYS_ADMIN)) {
		LOG_ERROR("capable(CAP_SYS_ADMIN) error\n");
		return -EPERM;
	}

	if (stat_info == NULL) {
		LOG_ERROR("NULL stat_info\n");
		return -ENODEV;
	}
	cidev = stat_info->cidev;
	if (cidev == NULL) {
		LOG_ERROR("NULL cidev\n");
		return -ENODEV;
	}

	ci_mutex_lock(cidev);

	ci_stat_cam_info(m, cidev);

	ci_mutex_unlock(cidev);

	return 0;
}

static int ci_stat_cam_open(struct inode *inode, struct file *file)
{
	return single_open(file, ci_stat_cam_show, PDE_DATA(inode));
}

static const struct file_operations ci_stat_cam_fops = {
	.owner		= THIS_MODULE,
	.open		= ci_stat_cam_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};
*/

static int ci_free_proc(CI_DEV_T *cidev)
{
	if (cidev->proc != NULL) {
		ci_free(cidev->proc);
		cidev->proc = NULL;
	}
	return 0;
}

static int ci_alloc_proc(CI_DEV_T *cidev)
{
	ci_proc_t *proc = NULL;

	proc = (ci_proc_t *)ci_zalloc(sizeof(ci_proc_t));
	if (proc == NULL) {
		LOG_ERROR("unabled to allocate proc for ci[%d]\n", cidev->idx);
		return -ENOMEM;
	}
	proc->cidev = cidev;
	cidev->proc = proc;
	return 0;
}

//CI_OS_PROC_BASE
static const OS_PROC_DESC_TABLE_T _g_ci_device_proc_table[] =
{
	{ "author",			PROC_ID_AUTHOR,		OS_PROC_FLAG_READ },
	{ "command",		PROC_ID_COMMAND,	OS_PROC_FLAG_WRITE },
	{ "delay",			PROC_ID_DELAY,	OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE },
	//
	/*
	 * /proc/lg/ci0/pcap_dump
	 *              pcap_show
	 *              pcap_size
	 *              stat_cam
	 *              stat_err
	 *              stat_perf
	 *              stat_reg
	 */
#if defined(CI_PROC_PCAP_ON)
	{ PCAP_DUMP_NAME,	PROC_ID_PCAP_DUMP,	OS_PROC_FLAG_SEQRD,	(struct file_operations *)&ci_pcap_dump_fops, (void *)NULL},
	{ PCAP_SHOW_NAME,	PROC_ID_PCAP_SHOW,	OS_PROC_FLAG_SEQRD,	(struct file_operations *)&ci_pcap_show_fops, (void *)NULL},
	{ PCAP_SIZE_NAME,	PROC_ID_PCAP_SIZE,	OS_PROC_FLAG_SEQRW|OS_PROC_FLAG_WRITE,	(struct file_operations *)&ci_pcap_size_fops, (void *)NULL},
#endif
	{ STAT_CAM_NAME,	PROC_ID_STAT_CAM,	OS_PROC_FLAG_SEQRD,	(struct file_operations *)&ci_stat_cam_fops, (void *)NULL},
	{ STAT_ERR_NAME,	PROC_ID_STAT_ERR,	OS_PROC_FLAG_SEQRD,	(struct file_operations *)&ci_stat_err_fops, (void *)NULL},
	{ STAT_PERF_NAME,	PROC_ID_STAT_PERF,	OS_PROC_FLAG_SEQRD,	(struct file_operations *)&ci_stat_perf_fops, (void *)NULL},
	{ STAT_REG_NAME,	PROC_ID_STAT_REG,	OS_PROC_FLAG_SEQRD,	(struct file_operations *)&ci_stat_reg_fops, (void *)NULL},
	{ NULL, 			PROC_ID_MAX		, 0 }
};
#define CI_DEV_PROC_TBL_SIZE		sizeof(_g_ci_device_proc_table)

static int ci_init_proc_os_table(CI_DEV_T *cidev)
{
	OS_PROC_DESC_TABLE_T *proc_table = NULL;
	OS_PROC_DESC_TABLE_T *table;
	struct proc_dir_entry *dentry = NULL;
	int ret = 0;
	int i;

	proc_table = (OS_PROC_DESC_TABLE_T *)ci_malloc(CI_DEV_PROC_TBL_SIZE);
	if (proc_table == NULL) {
		LOG_ERROR("unabled to allocated proc_table\n");
		ret = -ENOMEM;
		goto out;
	}
	memcpy((void *)proc_table, (void *)_g_ci_device_proc_table, CI_DEV_PROC_TBL_SIZE);

	table = proc_table;
	for (i=0 ; (table->name != NULL) ; i++) {
		if (table->fop != NULL) {
			table->data = cidev;
		}
		table++;
	}

	/*
	 * [Proc API updated]
	 * commit ebfd2d4db863335c903ac76cb01f376b62c1e18f
     * Author: raxis.lim <raxis.lim@lge.com>
     * Date:   Tue Mar 10 16:27:56 2015 +0900
     * Change-Id: I95710b4e2a13cb869f1b589c9c9fbd5a5ab27dbe
     * Return value : int -> struct proc_dir_entry *d
	 */
	dentry = ci_proc_create_entry_ex(ci_dev_name(cidev),
								proc_table,
								_ci_read_proc_function,
								_ci_write_proc_function);
	if (dentry == NULL) {
		LOG_ERROR("ci_proc_create_entry failed\n");
		ci_free(proc_table);
		goto out;
	}
	cidev->proc->root = dentry;
	cidev->proc->table = proc_table;

out:
	return ret;
}

static int ci_uninit_proc_os_table(CI_DEV_T *cidev)
{
	ci_proc_remove_entry(ci_dev_name(cidev));
	cidev->proc->root = NULL;
	if (cidev->proc->table != NULL) {
		ci_free(cidev->proc->table);
		cidev->proc->table = NULL;
	}
	return 0;
}

int ci_init_proc(CI_DEV_T *cidev)
{
	int ret = 0;

	if (cidev == NULL) {
		return -ENODEV;
	}
	if (cidev->proc != NULL) {
		LOG_WARNING("proc already allocated\n");
		return 0;
	}

	ret = ci_alloc_proc(cidev);
	if (ret != 0) {
		goto out;
	}

	ret = ci_init_proc_os_table(cidev);
	if (ret != 0) {
		goto out_free;
	}

	ret = ci_pcap_mon_init(cidev);
	if (ret != 0) {
		goto out_os;
	}

	LOG_NOTI("CI PROC Initialized");
	return 0;

out_os:
	ci_uninit_proc_os_table(cidev);

out_free:
	ci_free_proc(cidev);

out:
	return ret;
}

/**
 * cleanup proc utility for ci device
 *
 * @see CI_Cleanup
*/
void ci_uninit_proc(CI_DEV_T *cidev)
{
	ci_pcap_mon_uninit(cidev);

	ci_uninit_proc_os_table(cidev);

	ci_free_proc(cidev);

	LOG_NOTI("CI PROC Uninitialized");
}


