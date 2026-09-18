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

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		justine.jeong
 *  @version	1.0
 *  @date		2018-05-29
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
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"

#include "os_util.h"
#include "debug_util.h"
#include "proc_util.h"
#include "base_device.h"
#ifdef INCLUDE_KDRV_SYS
#include "sys_io.h"
#include "sys_bwm.h"
#endif
#include "de_def.h"
#include "de_kapi.h"
#include "vsc_bwm.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define VSC_BWM_INPUT_NUM		8
#define VSC_BWM_INPUT_HDMI444	7

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct vsc_bwm_ctx
{
	struct vsc_bwm_cfg cur_cfg;
	struct vsc_bwm_cfg pre_cfg;
	struct vsc_bwm_cfg dbg_cfg;
	UINT32 skip_noti;//for debug
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
const char* input_str_table[] = {"none","avd","adc","hdmi","vdec","jpeg","fb","hdmi444"};
const char* hdr_str_table[] = {"sdr","hlg","hdr10","dolby","ll_dolby"};

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct vsc_bwm_ctx _g_vsc_bwm_ctx;

/*========================================================================================
	Implementation Group
========================================================================================*/
int vsc_bwm_init(void)
{
	memset(&_g_vsc_bwm_ctx, 0x0, sizeof(struct vsc_bwm_ctx));
	DE_NOTI("done\n");
	return 0;
}

int vsc_bwm_set_config(enum vsc_bwm_opt opt, struct vsc_bwm_cfg *cfg)
{
	struct vsc_bwm_cfg *p_cur = &_g_vsc_bwm_ctx.cur_cfg;

	if (!cfg || opt>=VSC_BWM_OPT_MAX)	return 0;

	switch (opt)
	{
		case VSC_BWM_OPT_INPUT:
			p_cur->input = cfg->input;
			break;
		case VSC_BWM_OPT_SIZE:
			p_cur->size.w = cfg->size.w;
			p_cur->size.h = cfg->size.h;
			p_cur->size.rate = cfg->size.rate;
			break;
		case VSC_BWM_OPT_HDR:
			p_cur->hdr = cfg->hdr;
			break;
		case VSC_BWM_OPT_HDMI444:
			p_cur->hdmi444 = cfg->hdmi444;
			break;
		default:
			break;
	}

	DE_NOTI("[bwm] opt:%d, input:%d,%dx%d@%d, hdr:%d, hdmi444:%d\n",\
		opt,p_cur->input,p_cur->size.w,p_cur->size.h,p_cur->size.rate,p_cur->hdr,p_cur->hdmi444);

	return 0;
}

static UINT32 vsc_bwm_getinputid(UINT32 input, UINT32 hdmi444)
{
	UINT32 id = 0;

	if (input == V4L2_EXT_VSC_INPUT_SRC_HDMI && hdmi444 == 1) {
		id = VSC_BWM_INPUT_HDMI444;
	}
	else if (input < VSC_BWM_INPUT_NUM) {
		id = input;
	}

	return id;
}

static UINT32 vsc_bwm_gethdrid(UINT32 hdr)
{
	UINT32 id;

	if (hdr == V4L2_EXT_VSC_HDR_TYPE_DOLBY_LL)
	{
		id = 4;
	}
	else if (hdr == V4L2_EXT_VSC_HDR_TYPE_DOLBY || \
		hdr == V4L2_EXT_VSC_HDR_TYPE_DOLBY_RF)
	{
		id = 3;
	}
	else if (hdr == V4L2_EXT_VSC_HDR_TYPE_HDR10 || \
		hdr == V4L2_EXT_VSC_HDR_TYPE_PRIME)
	{
		id = 2;
	}
	else if (hdr == V4L2_EXT_VSC_HDR_TYPE_HLG)
	{
		id = 1;
	}
	else
	{
		id = 0;
	}

	return id;
}

int vsc_bwm_noti(void)
{
	UINT32 id;
	UINT32 skip_noti = _g_vsc_bwm_ctx.skip_noti;
	struct vsc_bwm_cfg *p_cur = &_g_vsc_bwm_ctx.cur_cfg;
	struct vsc_bwm_cfg *p_pre = &_g_vsc_bwm_ctx.pre_cfg;

	if (p_pre->input != p_cur->input || \
		p_pre->size.w != p_cur->size.w || \
		p_pre->size.h != p_cur->size.h || \
		p_pre->size.rate != p_cur->size.rate || \
		p_pre->hdmi444 != p_cur->hdmi444)
	{
		id = vsc_bwm_getinputid(p_cur->input,p_cur->hdmi444);

		DE_NOTI("[bwm] sys_bwm_noti(pqe.input=%s,%dx%d@%d) %s\n",input_str_table[id],p_cur->size.w,p_cur->size.h,p_cur->size.rate/10,(skip_noti == 0)? "noti":"skip");

		#ifdef INCLUDE_KDRV_SYS
		if (skip_noti == 0)
		{
			sys_bwm_noti(BWM_OPT_DEFAULT,"pqe.input=%s,%dx%d@%d",input_str_table[id],p_cur->size.w,p_cur->size.h,p_cur->size.rate/10);
		}
		#endif

		p_pre->input = p_cur->input;
		p_pre->size.w = p_cur->size.w;
		p_pre->size.h = p_cur->size.h;
		p_pre->size.rate = p_cur->size.rate;
		p_pre->hdmi444 = p_cur->hdmi444;
	}

	if (p_pre->hdr != p_cur->hdr)
	{
		id = vsc_bwm_gethdrid(p_cur->hdr);

		DE_NOTI("[bwm] sys_bwm_noti(pqe.hdr=%s) %s\n",hdr_str_table[id],(skip_noti == 0)? "noti":"skip");

		#ifdef INCLUDE_KDRV_SYS
		if (skip_noti == 0)
		{
			sys_bwm_noti(BWM_OPT_DEFAULT,"pqe.hdr=%s",hdr_str_table[id]);
		}
		#endif

		p_pre->hdr = p_cur->hdr;
	}

	return 0;
}

int vsc_bwm_help(char* buffer)
{
	int len = 0;
	UINT32 i;
	struct vsc_bwm_cfg *p_cur = &_g_vsc_bwm_ctx.cur_cfg;
	struct vsc_bwm_cfg *p_dbg = &_g_vsc_bwm_ctx.dbg_cfg;

	if (!buffer)	return 0;

	len += sprintf( buffer+len, "-------------------------------------------------------------------\n");
	len += sprintf( buffer+len, "- cur : input=%s(%d),%d,%d@%d, hdr=%s(%d), hdmi444=%d\n",\
		input_str_table[vsc_bwm_getinputid(p_cur->input,p_cur->hdmi444)],\
		p_cur->input,p_cur->size.w,p_cur->size.h,p_cur->size.rate,\
		hdr_str_table[vsc_bwm_gethdrid(p_cur->hdr)],p_cur->hdr,p_cur->hdmi444);
	len += sprintf( buffer+len, "-------------------------------------------------------------------\n");
	len += sprintf( buffer+len, "- input : ");
	for (i=0; i<(sizeof(input_str_table)/sizeof(input_str_table[0])); i++)
	{
		len += sprintf( buffer+len, "%d:%s ",i,input_str_table[i]);
	}
	len += sprintf( buffer+len, "\n");
	len += sprintf( buffer+len, "- hdr   : ");
	for (i=0; i<(sizeof(hdr_str_table)/sizeof(hdr_str_table[0])); i++)
	{
		len += sprintf( buffer+len, "%d:%s ",i,hdr_str_table[i]);
	}
	len += sprintf( buffer+len, "\n");
	len += sprintf( buffer+len, "-------------------------------------------------------------------\n");
	len += sprintf( buffer+len, "- dbg : input=%s,%d,%d@%d, hdr=%s, hdmi444=%d, skip=%d\n",\
		input_str_table[p_dbg->input],p_dbg->size.w,p_dbg->size.h,p_dbg->size.rate,\
		hdr_str_table[p_dbg->hdr],p_dbg->hdmi444,_g_vsc_bwm_ctx.skip_noti);
	len += sprintf( buffer+len, "-------------------------------------------------------------------\n");
	len += sprintf( buffer+len, "- example\n");
	len += sprintf( buffer+len, "echo input=hdmi,3840,2160@1440 hdr=hdr10 hdmi444=1 > /proc/lg/de/bwm\n");
	len += sprintf( buffer+len, "echo input=vdec,3840,2160@600 > /proc/lg/de/bwm\n");
	len += sprintf( buffer+len, "echo input=none,0,0,0 > /proc/lg/de/bwm\n");
	len += sprintf( buffer+len, "echo hdr=dolby > /proc/lg/de/bwm\n");
	len += sprintf( buffer+len, "echo hdmi444=1 > /proc/lg/de/bwm\n");
	len += sprintf( buffer+len, "echo skip=1 > /proc/lg/de/bwm\n");
	len += sprintf( buffer+len, "-------------------------------------------------------------------\n");

	return len;
}

int vsc_bwm_set_dbg(char* command)
{
	UINT32 i,num;
	char *tok, *sav_tok;
	char delim[] = ",:=@ \t\n";
	char str[64];
	struct vsc_bwm_cfg *p_cur = &_g_vsc_bwm_ctx.cur_cfg;
	struct vsc_bwm_cfg *p_dbg = &_g_vsc_bwm_ctx.dbg_cfg;
	struct vsc_bwm_cfg flag;

	if (!command)	return 0;

	if ((num = strlen(command)) == 0)	return 0;
	if (num > 64)	num=64;
	strncpy(str,command,num);
	//DE_NOTI("[bwm] str(%d):%s\n"num,str);

	memcpy(p_dbg,p_cur,sizeof(struct vsc_bwm_cfg));
	p_dbg->input = vsc_bwm_getinputid(p_cur->input,p_cur->hdmi444);
	p_dbg->hdr = vsc_bwm_gethdrid(p_cur->hdr);
	memset(&flag,0,sizeof(flag));

	tok=simple_strtok(str, delim, &sav_tok);

	while (tok)
	{
		// eg. input=hdmi,3840,2160@1440
		if (!strncasecmp(tok, "input", strlen("input")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);
			num = sizeof(input_str_table)/sizeof(input_str_table[0]);
			for (i=0; i<num; i++)
			{
				if (!strncasecmp(tok, input_str_table[i], strlen(input_str_table[i])))
				{
					p_dbg->input = i;
					tok=simple_strtok(NULL, delim, &sav_tok);
					sscanf(tok,"%d",&p_dbg->size.w);
					tok=simple_strtok(NULL, delim, &sav_tok);
					sscanf(tok,"%d",&p_dbg->size.h);
					tok=simple_strtok(NULL, delim, &sav_tok);
					sscanf(tok,"%d",&p_dbg->size.rate);
					flag.input = 1;
					break;
				}
			}
		}

		// eg. hdr=hdr10
		if (!strncasecmp(tok, "hdr", strlen("hdr")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);
			num = sizeof(hdr_str_table)/sizeof(hdr_str_table[0]);
			for (i=0; i<num; i++)
			{
				if (!strncasecmp(tok, hdr_str_table[i], strlen(hdr_str_table[i])))
				{
					p_dbg->hdr = i;
					flag.hdr = 1;
					break;
				}
			}
		}

		// eg. hdmi444=1
		if (!strncasecmp(tok, "hdmi444", strlen("hdmi444")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);
			sscanf(tok,"%d",&p_dbg->hdmi444);
			flag.hdmi444 = 1;
		}

		// eg. skip=1
		if (!strncasecmp(tok, "skip", strlen("skip")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);
			sscanf(tok,"%d",&_g_vsc_bwm_ctx.skip_noti);
		}

		tok=simple_strtok(NULL, delim, &sav_tok);
	}

	if (flag.input == 1 || flag.hdmi444 == 1)
	{
		i = (p_dbg->input == V4L2_EXT_VSC_INPUT_SRC_HDMI && p_dbg->hdmi444 == 1)? VSC_BWM_INPUT_HDMI444:p_dbg->input;
		DE_NOTI("[bwm] sys_bwm_noti(pqe.input=%s,%dx%d@%d) noti\n",input_str_table[i],p_dbg->size.w,p_dbg->size.h,p_dbg->size.rate/10);
		#ifdef INCLUDE_KDRV_SYS
		sys_bwm_noti(BWM_OPT_DEFAULT,"pqe.input=%s,%dx%d@%d",input_str_table[i],p_dbg->size.w,p_dbg->size.h,p_dbg->size.rate/10);
		#endif
	}

	if (flag.hdr == 1)
	{
		i = p_dbg->hdr;//id
		DE_NOTI("[bwm] sys_bwm_noti(pqe.hdr=%s) noti\n",hdr_str_table[i]);
		#ifdef INCLUDE_KDRV_SYS
		sys_bwm_noti(BWM_OPT_DEFAULT,"pqe.hdr=%s",hdr_str_table[i]);
		#endif
	}

	return 0;
}
