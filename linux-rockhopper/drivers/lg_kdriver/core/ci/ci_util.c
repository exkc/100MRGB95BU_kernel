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
 *  Core driver implementation for ci device.
 *
 *  author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version		1.0
 *  date		2010.02.19
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
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/cdev.h>
#include <linux/delay.h>	// for usleep_range, jinhwan.bae 20131018

#include "ci_util.h"
#include "ci_cfg.h"

const char* ci_get_delaystr(UINT32 type)
{
	switch(type)
	{
		case DELAY_CIS_CONFIG_FIRST_TUPLE_OK:		return "cis_config_first_tuple_ok";
		case DELAY_CIS_CONFIG_FIRST_TUPLE_NG:		return "cis_config_first_tuple_ng";
		case DELAY_CIS_END_WRITE_COR:				return "cis_end_write_cor";
		case DELAY_CIS_DURING_READ_TUPLE:			return "cis_during_read_tuple";
		case DELAY_CIS_END_READ_TUPLE_INITIAL:		return "cis_end_read_tuple_init";
		case DELAY_CIS_PARSE_NON_CI_TUPLE:			return "cis_parse_non_ci_tuple";
		case DELAY_INIT_POWER_CONTROL:				return "init_power_control";
		case DELAY_INIT_AFTER_INTERRUPT_ENABLE:		return "init_after_intr_en";
		case DELAY_CAM_INIT_VCC_CARD_RESET:			return "cam_init_vcc_card_reset";
		case DELAY_CAM_INIT_CARD_RESET_NOT_RESET:	return "cam_init_card_reset_not_reset";
		case DELAY_CAM_INIT_CARD_RESET_EN_PCCARD:	return "cam_init_card_reset_en_pccard";
		case DELAY_IO_SOFT_RESET_CHECK_FR:			return "io_soft_reset_check_FR";
		case DELAY_IO_END_SOFT_RESET:				return "io_end_soft_reset";
		case DELAY_IO_NEGO_BUFF_BEFORE_SOFT_RESET:	return "io_nego_buff_before_soft_reset";
		case DELAY_IO_NEGO_BUFF_CHECK_DA:			return "io_nego_buff_check_DA";
		case DELAY_IO_NEGO_BUFF_CHECK_FR:			return "io_nego_buff_check_FR";
		case DELAY_IO_NEGO_BUFF_AFTER_WRITE_DATA:	return "io_nego_buff_after_write_data";
		case DELAY_IO_READ_CHECK_DA:				return "io_read_check_DA";
		case DELAY_IO_WRITE_CHECK_DA:				return "io_write_check_DA";
		case DELAY_IO_WRITE_CHECK_FR:				return "io_write_check_FR";
		case DELAY_IO_WRITE_1ST_BYTE_STAT_RD_FR_WE:	return "io_write_1st_byte_stat_rd_FR_WE";
		case DELAY_IO_WRITE_MIDDLE_BYTE_CHECK_WE:	return "io_write_middle_byte_check_WE";
		case DELAY_IO_WRITE_LAST_BYTE_CHECK_WE:		return "io_write_last_byte_check_WE";
		case DELAY_MAX_COUNT_R_PRE:					return "max_count_r_pre";
		case DELAY_MAX_COUNT_R:						return "max_count_r";
		case DELAY_MAX_COUNT_W_PRE:					return "max_count_w_pre";
		case DELAY_MAX_COUNT_W:						return "max_count_w";
		case DELAY_MAX_COUNT_DIV:					return "max_count_div";
		case DELAY_MAXIM_RETRY_CNT:					return "max_retry_count";
		case DELAY_MAX_COUNT_CIS_CHK:				return "max_count_cis_check";
		default: return "unknown";
	}
}

void *ci_malloc(int size)
{
	return OS_Malloc(size);
}

void *ci_zalloc(int size)
{
	void *ptr = OS_Malloc(size);
	memset(ptr, 0x00, size);
	return ptr;
}

void ci_free(void *mem)
{
	if (mem != NULL)
		OS_Free(mem);
}

void ci_sleep(int delay)
{
	usleep_range(delay*1000, delay*1000);
}

/*
 * [Proc API updated]
 * commit ebfd2d4db863335c903ac76cb01f376b62c1e18f
 * Author: raxis.lim <raxis.lim@lge.com>
 * Date:   Tue Mar 10 16:27:56 2015 +0900
 * Change-Id: I95710b4e2a13cb869f1b589c9c9fbd5a5ab27dbe
 *
 * Return value : int -> struct proc_dir_entry *d
 */
struct proc_dir_entry *ci_proc_get_base_dir(void)
{
	return OS_PROC_GetBaseEntry();
}

struct proc_dir_entry *ci_proc_create_entry(char *name,
								struct proc_dir_entry *parent,
								OS_PROC_DESC_TABLE_T *table,
								OS_PROC_READ_FUNC_T rd_func,
								OS_PROC_WRITE_FUNC_T wr_func)
{
	return OS_PROC_CreateEntry(name, parent, table, rd_func, wr_func);
}

struct proc_dir_entry *ci_proc_create_entry_ex(char *name,
								OS_PROC_DESC_TABLE_T *table,
								OS_PROC_READ_FUNC_T rd_func,
								OS_PROC_WRITE_FUNC_T wr_func)
{
	return ci_proc_create_entry(name, NULL, table, rd_func, wr_func);
}

int ci_proc_remove_entry(char *module_name)
{
	return OS_PROC_RemoveEntry(module_name);
}

