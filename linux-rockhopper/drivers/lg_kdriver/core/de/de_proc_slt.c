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
 *  Linux proc interface for de device.
 *	de device will teach you how to make device driver with new platform.
 *
 *  author
 *  version
 *  date
 *  note
 *
 *  @addtogroup
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
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/delay.h>
#include "proc_util.h"
#include "os_util.h"
#include "debug_util.h"
#include "de_def.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define DE_PROC_SLT_PRINT(_m, _fmt, args...)	\
	if ((_m) == NULL) { DE_NOTI(_fmt,##args); } else { seq_printf((_m),_fmt,##args); }

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct de_proc_slt_str_node {
	UINT32 sec;
	UINT32 msec;
	UINT32 usec;
	char *str;
	struct de_proc_slt_str_node *next;
};

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
static void de_proc_slt_print_node(struct seq_file *m);
static void de_proc_slt_append_node(char *str);
int de_proc_slt_status(struct seq_file *m);
int de_proc_slt_push_log(char *str);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
struct de_proc_slt_str_node *gp_de_proc_slt_str_node = NULL;

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_proc_slt_status(struct seq_file *m)
{
	de_proc_slt_print_node(m);
	return 0;
}

static DEFINE_MUTEX(slt_cmd_mutex);
int de_proc_slt_push_log(char *str)
{
	if (str == NULL) {
		DE_NOTI("str is null\n");
		return 0;
	}

	mutex_lock(&slt_cmd_mutex);
	de_proc_slt_append_node(str);
	mutex_unlock(&slt_cmd_mutex);
	return 0;
}

static void de_proc_slt_print_node(struct seq_file *m)
{
	UINT32 cnt = 0;
	struct de_proc_slt_str_node *p_curr = gp_de_proc_slt_str_node;

	while (p_curr != NULL) {
		DE_PROC_SLT_PRINT(m,"[%2d] [%06d.%03d%03d] %s\n",cnt,p_curr->sec,p_curr->msec,p_curr->usec,p_curr->str);
		p_curr = p_curr->next;
		cnt++;
	}

	DE_PROC_SLT_PRINT(m,"[%2d] EOF\n",cnt);
}

static void de_proc_slt_append_node(char *str)
{
	size_t len;
	UINT32 sec, msec, usec, cnt = 0;
	struct de_proc_slt_str_node *p_curr = gp_de_proc_slt_str_node;

	if (str == NULL) {
		DE_NOTI("str is null\n");
		return;
	}

	len = strlen(str);
	OS_GetCurrentTicks(&sec, &msec, &usec);

	if (p_curr == NULL) {
		gp_de_proc_slt_str_node = p_curr = (struct de_proc_slt_str_node *)kcalloc(1,sizeof(struct de_proc_slt_str_node),GFP_KERNEL);
		if (!p_curr) {
			DE_ERROR("[c][%2d] [%06d.%03d%03d] (len:%zd) p kcalloc err\n",cnt,sec,msec,usec,len);
			return;
		}
		p_curr->sec = sec;
		p_curr->msec = msec;
		p_curr->usec = usec;
		p_curr->str = (char *)kcalloc(1,len,GFP_KERNEL);
		if (!p_curr->str) {
			DE_ERROR("[c][%2d] [%06d.%03d%03d] (len:%zd) str kcalloc err\n",cnt,sec,msec,usec,len);
			return;
		}
		strncpy(p_curr->str,str,len);
		p_curr->next = NULL;
		DE_NOTI("[c][%2d] [%06d.%03d%03d] (%s) (len:%zd)\n",cnt,sec,msec,usec,p_curr->str,len);
		return;
	}

	while (p_curr->next != NULL) {
		p_curr = p_curr->next;
		cnt++;
	}

	p_curr->next = (struct de_proc_slt_str_node *)kcalloc(1,sizeof(struct de_proc_slt_str_node),GFP_KERNEL);
	if (!p_curr->next) {
		DE_ERROR("[n][%2d] [%06d.%03d%03d] (len:%zd) p kcalloc err\n",cnt,sec,msec,usec,len);
		return;
	}
	p_curr->next->sec = sec;
	p_curr->next->msec = msec;
	p_curr->next->usec = usec;
	p_curr->next->str = (char *)kcalloc(1,len,GFP_KERNEL);
	if (!p_curr->next->str) {
		DE_ERROR("[n][%2d] [%06d.%03d%03d] (len:%zd) str kcalloc err\n",cnt,sec,msec,usec,len);
		return;
	}
	strncpy(p_curr->next->str,str,len);
	p_curr->next->next = NULL;
	DE_NOTI("[n][%2d] [%06d.%03d%03d] (%s) (len:%zd)\n",cnt,sec,msec,usec,p_curr->next->str,len);
	//de_proc_slt_print_node(NULL);
}
