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
#include "de_def.h"
#include "de_kapi.h"
#include "v4l2_vsc_event.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* ver, yyyy/mm/dd/hh:mm */
#define PROC_DISP_VER		"2022/01/03/17:22"

#define	PROC_DISP_STR_MAX	16

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct proc_disp_ctx
{
	char in_size[PROC_DISP_STR_MAX];
	char out_size[PROC_DISP_STR_MAX];
	char hdr_type[PROC_DISP_STR_MAX];

	struct {
		int wid;
		int connect;
		int sub;//0:none,1:pip,2:pbp
		int hdr;//0:sdr,1:h10,2:hlg
		int i_w;//input width
		int i_h;//input height
		int o_w;//output width
		int o_h;//output height
	} param;
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
static int de_proc_disp_get_param(void);
static int de_proc_disp_run(void);
int de_proc_disp_help(char* buffer);
int de_proc_disp_command(char* command);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct proc_disp_ctx _g_de_proc_disp_ctx = {
	.in_size = "4k",
	.out_size = "2k",
	.hdr_type = "hdr10",
};

/*========================================================================================
	Implementation Group
========================================================================================*/
int de_proc_disp_help(char* buffer)
{
	int len = 0;
	struct proc_disp_ctx *p_ctx = &_g_de_proc_disp_ctx;

	if (!buffer)	return 0;

	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- version : %s\n",PROC_DISP_VER);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- config\n");
	len += sprintf( buffer+len, "%-10s : %s\n","in_size",p_ctx->in_size);
	len += sprintf( buffer+len, "%-10s : %s\n","out_size",p_ctx->out_size);
	len += sprintf( buffer+len, "%-10s : %s\n","hdr_type",p_ctx->hdr_type);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- param\n");
	len += sprintf( buffer+len, "%-10s : %d\n","wid",p_ctx->param.wid);
	len += sprintf( buffer+len, "%-10s : %d\n","connect",p_ctx->param.connect);
	len += sprintf( buffer+len, "%-10s : %d\n","sub",p_ctx->param.sub);
	len += sprintf( buffer+len, "%-10s : %d\n","hdr",p_ctx->param.hdr);
	len += sprintf( buffer+len, "%-10s : %d\n","i_w",p_ctx->param.i_w);
	len += sprintf( buffer+len, "%-10s : %d\n","i_h",p_ctx->param.i_h);
	len += sprintf( buffer+len, "%-10s : %d\n","o_w",p_ctx->param.o_w);
	len += sprintf( buffer+len, "%-10s : %d\n","o_h",p_ctx->param.o_h);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- usage\n");
	len += sprintf( buffer+len, "echo [%s] [%s] > /proc/lg/de/disp\n","main,pip,pbp","on,off");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- edit\n");
	len += sprintf( buffer+len, "echo insize=[%s] > /proc/lg/de/disp\n","2k,4k,8k");
	len += sprintf( buffer+len, "echo outsize=[%s] > /proc/lg/de/disp\n","2k,4k,8k");
	len += sprintf( buffer+len, "echo hdrtype=[%s] > /proc/lg/de/disp\n","sdr,hdr10,hlg");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "- related command\n");
	len += sprintf( buffer+len, "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD\n");
	len += sprintf( buffer+len, "./test_vdec -f [HEVC,H264] -d 1 -v 1 -t [FILE] -b -r 999 &\n");
	len += sprintf( buffer+len, "eg) ./test_vdec -f HEVC -d 1 -v 1 -t ./hevc/4k_hvc1_h10_Lego_20s.hevc -b -r 999 &\n");
	len += sprintf( buffer+len, "pkill -9 test_vdec\n");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");

	return len;
}

int de_proc_disp_command(char* command)
{
	char *tok, *sav_tok;
	char delim[] = "= \t\n";
	struct proc_disp_ctx *p_ctx = &_g_de_proc_disp_ctx;

	if (!command)	return 0;

	tok=simple_strtok(command, delim, &sav_tok);

	while(tok)
	{
		if (!strncasecmp(tok, "main", strlen("main")) || \
			!strncasecmp(tok, "sub", strlen("sub")) || \
			!strncasecmp(tok, "pip", strlen("pip")) || \
			!strncasecmp(tok, "pbp", strlen("pbp")))
		{
			if (!strncasecmp(tok, "main", strlen("main")))
			{
				p_ctx->param.wid = 0;
			}
			else if (!strncasecmp(tok, "sub", strlen("sub")))
			{
				p_ctx->param.wid = 1;
			}

			if (!strncasecmp(tok, "pbp", strlen("pbp")))
			{
				p_ctx->param.sub = 2;
			}
			else if (!strncasecmp(tok, "pip", strlen("pip")))
			{
				p_ctx->param.sub = 1;
			}
			else
			{
				p_ctx->param.sub = 0;
			}

			tok=simple_strtok(NULL, delim, &sav_tok);

			if(tok)
			{
				if (!strncasecmp(tok, "on", strlen("on")))
				{
					p_ctx->param.connect = 1;
				}
				else
				{
					p_ctx->param.connect = 0;
				}
				de_proc_disp_run();
			}
		}

		if (!strncasecmp(tok, "insize", strlen("insize")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);

			if(tok)
			{
				strncpy(p_ctx->in_size,tok,PROC_DISP_STR_MAX);
			}
			break;
		}

		if (!strncasecmp(tok, "outsize", strlen("outsize")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);

			if(tok)
			{
				strncpy(p_ctx->out_size,tok,PROC_DISP_STR_MAX);
			}
			break;
		}

		if (!strncasecmp(tok, "hdrtype", strlen("hdrtype")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);

			if(tok)
			{
				strncpy(p_ctx->hdr_type,tok,PROC_DISP_STR_MAX);
			}
			break;
		}

		tok=simple_strtok(NULL, delim, &sav_tok);
	}

	return 0;
}

static int de_proc_disp_get_param(void)
{
	struct proc_disp_ctx *p_ctx = &_g_de_proc_disp_ctx;

	if (!strncasecmp(p_ctx->in_size, "2k", strlen("2k")))
	{
		p_ctx->param.i_w = 1920;
		p_ctx->param.i_h = 1080;
	}
	else if (!strncasecmp(p_ctx->in_size, "4k", strlen("4k")))
	{
		p_ctx->param.i_w = 3840;
		p_ctx->param.i_h = 2160;
	}
	else
	{
		p_ctx->param.i_w = 7680;
		p_ctx->param.i_h = 4320;
	}

	if (!strncasecmp(p_ctx->out_size, "2k", strlen("2k")))
	{
		p_ctx->param.o_w = 1920;
		p_ctx->param.o_h = 1080;
	}
	else if (!strncasecmp(p_ctx->out_size, "4k", strlen("4k")))
	{
		p_ctx->param.o_w = 3840;
		p_ctx->param.o_h = 2160;
	}
	else
	{
		p_ctx->param.o_w = 7680;
		p_ctx->param.o_h = 4320;
	}

	if (!strncasecmp(p_ctx->hdr_type, "hdr10", strlen("hdr10")))
	{
		p_ctx->param.hdr = 1;
	}
	else if (!strncasecmp(p_ctx->hdr_type, "hlg", strlen("hlg")))
	{
		p_ctx->param.hdr = 2;
	}
	else
	{
		p_ctx->param.hdr = 0;
	}

	return 0;
}

static int de_proc_disp_run(void)
{
	int val;
	struct v4l2_ext_vsc_connect_info input;
	struct v4l2_ext_vsc_win_region win;
	struct v4l2_ext_vsc_orbit_window orbit_w;
	struct v4l2_ext_vsc_orbit_move orbit_m;
	struct v4l2_ext_vsc_win_prop sub_mode;
	struct proc_disp_ctx *p_ctx = &_g_de_proc_disp_ctx;

	de_proc_disp_get_param();

	if (p_ctx->param.wid==0)
	{
		if (p_ctx->param.connect==1)
		{
			/* set input */
			/* echo 0 1 0 4 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func */
			input.in.src=V4L2_EXT_VSC_INPUT_SRC_VDEC;
			input.in.index=0;
			input.in.attr=0;
			input.out=V4L2_EXT_VSC_DEST_DISPLAY;
			vsc_set_input(1,0,&input);

			/* set hdr */
			/* echo 11 1 0 hdr > /proc/lg/de/v4l2_vsc_debug_func */
			if (p_ctx->param.hdr==2)
			{
				val = V4L2_EXT_VSC_HDR_TYPE_HLG;
			}
			else if (p_ctx->param.hdr==1)
			{
				val = V4L2_EXT_VSC_HDR_TYPE_HDR10;
			}
			else
			{
				val = V4L2_EXT_VSC_HDR_TYPE_SDR;
			}
			vsc_set_hdr_type(1,0,&val);

			/* set win info */
			/* echo 2 1 0 0 0 w h w h 0 0 w h 0 > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&win,0,sizeof(struct v4l2_ext_vsc_win_region));
			win.in.crop.w = p_ctx->param.i_w;
			win.in.crop.h = p_ctx->param.i_h;
			win.in.res.w = p_ctx->param.i_w;
			win.in.res.h = p_ctx->param.i_h;
			win.out.w = p_ctx->param.o_w;
			win.out.h = p_ctx->param.o_h;
			vsc_set_win_info(1,0,1,&win);

			/* set orbit win */
			/* echo 25 0 0 0 0 0 0 0 0 w h 0 0 0 0 0 0 w h > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&orbit_w,0,sizeof(struct v4l2_ext_vsc_orbit_window));
			orbit_w.video_input.w = p_ctx->param.i_w;
			orbit_w.video_input.h = p_ctx->param.i_h;
			orbit_w.video_output.w = p_ctx->param.o_w;
			orbit_w.video_output.h = p_ctx->param.o_h;
			vsc_set_orbit_window(1,0,&orbit_w);

			/* set orbit move */
			/* echo 25 1 0 0 0 0 0 0 0 w h 0 0 0 0 0 0 w h > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&orbit_m,0,sizeof(struct v4l2_ext_vsc_orbit_window));
			orbit_m.video_input.w = p_ctx->param.o_w;
			orbit_m.video_input.h = p_ctx->param.o_h;
			orbit_m.video_output.w = p_ctx->param.o_w;
			orbit_m.video_output.h = p_ctx->param.o_h;
			vsc_set_orbit_move(1,0,&orbit_m);

			/* set mute */
			/* echo 1 1 0 0 > /proc/lg/de/v4l2_vsc_debug_func */
			val = 0;
			vsc_set_mute(1,0,&val);
		}
		else
		{
			/* set hdr */
			/* echo 11 1 0 0 > /proc/lg/de/v4l2_vsc_debug_func */
			val = V4L2_EXT_VSC_HDR_TYPE_SDR;
			vsc_set_hdr_type(1,0,&val);

			/* set mute */
			/* echo 1 1 0 1 > /proc/lg/de/v4l2_vsc_debug_func */
			val = 1;
			vsc_set_mute(1,0,&val);

			/* set input */
			/* echo 0 1 0 0 0 0 0 > /proc/lg/de/v4l2_vsc_debug_func */
			input.in.src=V4L2_EXT_VSC_INPUT_SRC_NONE;
			input.in.index=0;
			input.in.attr=0;
			input.out=V4L2_EXT_VSC_DEST_NONE;
			vsc_set_input(1,0,&input);
		}
	}
	else
	{
		if (p_ctx->param.connect==1 && p_ctx->param.sub==2)
		{
			/* set sub mode */
			/* echo 3 1 0 2 2 2 > /proc/lg/de/v4l2_vsc_debug_func */
			sub_mode.win_mode = V4L2_EXT_VSC_WIN_MODE_PBP;
			sub_mode.mirror_mode = V4L2_EXT_VSC_MIRROR_MODE_OFF;
			sub_mode.mem_type = V4L2_EXT_VSC_MEMORY_TYPE_MULTI;
			vsc_set_sub_mode(1,(UINT8)p_ctx->param.wid,&sub_mode);

			/* set win info */
			/* echo 2 1 0 0 0 w h w h 0 0 w h 0 > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&win,0,sizeof(struct v4l2_ext_vsc_win_region));
			win.in.crop.w = p_ctx->param.i_w;
			win.in.crop.h = p_ctx->param.i_h;
			win.in.res.w = p_ctx->param.i_w;
			win.in.res.h = p_ctx->param.i_h;
			win.out.w = p_ctx->param.o_w;
			win.out.h = p_ctx->param.o_h;
			vsc_set_win_info(1,0,1,&win);

			/* set orbit win */
			/* echo 25 0 0 0 0 0 0 0 0 w h 0 0 0 0 0 0 w h > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&orbit_w,0,sizeof(struct v4l2_ext_vsc_orbit_window));
			orbit_w.video_input.w = p_ctx->param.i_w;
			orbit_w.video_input.h = p_ctx->param.i_h;
			orbit_w.video_output.x = p_ctx->param.o_w;
			orbit_w.video_output.w = p_ctx->param.o_w;
			orbit_w.video_output.h = p_ctx->param.o_h;
			vsc_set_orbit_window(1,0,&orbit_w);

			/* set orbit move */
			/* echo 25 1 0 0 0 0 0 0 0 w h 0 0 0 0 0 0 w h > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&orbit_m,0,sizeof(struct v4l2_ext_vsc_orbit_window));
			orbit_m.video_input.x = p_ctx->param.o_w;
			orbit_m.video_input.w = p_ctx->param.o_w;
			orbit_m.video_input.h = p_ctx->param.o_h;
			orbit_m.video_output.x = p_ctx->param.o_w;
			orbit_m.video_output.w = p_ctx->param.o_w;
			orbit_m.video_output.h = p_ctx->param.o_h;
			vsc_set_orbit_move(1,0,&orbit_m);

			/* set input */
			/* echo 0 1 1 4 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func */
			input.in.src=V4L2_EXT_VSC_INPUT_SRC_VDEC;
			input.in.index=0;
			input.in.attr=0;
			input.out=V4L2_EXT_VSC_DEST_DISPLAY;
			vsc_set_input(1,1,&input);

			/* set adaptive stream */
			/* echo 9 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func */
			val = 1;
			vsc_set_adaptives_stream(1,1,&val);

			/* set hdr */
			/* echo 11 1 1 hdr > /proc/lg/de/v4l2_vsc_debug_func */
			if (p_ctx->param.hdr==2)
			{
				val = V4L2_EXT_VSC_HDR_TYPE_HLG;
			}
			else if (p_ctx->param.hdr==1)
			{
				val = V4L2_EXT_VSC_HDR_TYPE_HDR10;
			}
			else
			{
				val = V4L2_EXT_VSC_HDR_TYPE_SDR;
			}
			vsc_set_hdr_type(1,1,&val);

			/* set win info */
			/* echo 2 1 1 0 0 w h w h w 0 w h 0 > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&win,0,sizeof(struct v4l2_ext_vsc_win_region));
			win.in.crop.w = p_ctx->param.i_w;
			win.in.crop.h = p_ctx->param.i_h;
			win.in.res.w = p_ctx->param.i_w;
			win.in.res.h = p_ctx->param.i_h;
			win.out.w = p_ctx->param.o_w;
			win.out.h = p_ctx->param.o_h;
			vsc_set_win_info(1,1,1,&win);

			/* set orbit win */
			/* echo 25 0 1 0 0 0 0 0 0 w h 0 0 0 0 w 0 w h > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&orbit_w,0,sizeof(struct v4l2_ext_vsc_orbit_window));
			orbit_w.video_input.w = p_ctx->param.i_w;
			orbit_w.video_input.h = p_ctx->param.i_h;
			orbit_w.video_output.w = p_ctx->param.o_w;
			orbit_w.video_output.h = p_ctx->param.o_h;
			vsc_set_orbit_window(1,1,&orbit_w);

			/* set orbit move */
			/* echo 25 1 1 0 0 0 0 w 0 w h 0 0 0 0 w 0 w h > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&orbit_m,0,sizeof(struct v4l2_ext_vsc_orbit_window));
			orbit_m.video_input.w = p_ctx->param.o_w;
			orbit_m.video_input.h = p_ctx->param.o_h;
			orbit_m.video_output.w = p_ctx->param.o_w;
			orbit_m.video_output.h = p_ctx->param.o_h;
			vsc_set_orbit_move(1,1,&orbit_m);

			/* set mute */
			/* echo 1 1 1 0 > /proc/lg/de/v4l2_vsc_debug_func */
			val = 0;
			vsc_set_mute(1,1,&val);
		}
		else if (p_ctx->param.connect==1 && p_ctx->param.sub==1)
		{
			/* set sub mode */
			/* echo 3 1 0 1 2 2 > /proc/lg/de/v4l2_vsc_debug_func */
			sub_mode.win_mode = V4L2_EXT_VSC_WIN_MODE_PIP;
			sub_mode.mirror_mode = V4L2_EXT_VSC_MIRROR_MODE_OFF;
			sub_mode.mem_type = V4L2_EXT_VSC_MEMORY_TYPE_MULTI;
			vsc_set_sub_mode(1,(UINT8)p_ctx->param.wid,&sub_mode);

			/* set input */
			/* echo 0 1 1 4 0 0 1 > /proc/lg/de/v4l2_vsc_debug_func */
			input.in.src=V4L2_EXT_VSC_INPUT_SRC_VDEC;
			input.in.index=0;
			input.in.attr=0;
			input.out=V4L2_EXT_VSC_DEST_DISPLAY;
			vsc_set_input(1,1,&input);

			/* set adaptive stream */
			/* echo 9 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func */
			val = 1;
			vsc_set_adaptives_stream(1,1,&val);

			/* set hdr */
			/* echo 11 1 1 hdr > /proc/lg/de/v4l2_vsc_debug_func */
			if (p_ctx->param.hdr==2)
			{
				val = V4L2_EXT_VSC_HDR_TYPE_HLG;
			}
			else if (p_ctx->param.hdr==1)
			{
				val = V4L2_EXT_VSC_HDR_TYPE_HDR10;
			}
			else
			{
				val = V4L2_EXT_VSC_HDR_TYPE_SDR;
			}
			vsc_set_hdr_type(1,1,&val);

			/* set win info */
			/* echo 2 1 1 0 0 w h w h 0 0 w h 0 > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&win,0,sizeof(struct v4l2_ext_vsc_win_region));
			win.in.crop.w = p_ctx->param.i_w;
			win.in.crop.h = p_ctx->param.i_h;
			win.in.res.w = p_ctx->param.i_w;
			win.in.res.h = p_ctx->param.i_h;
			win.out.w = p_ctx->param.o_w;
			win.out.h = p_ctx->param.o_h;
			vsc_set_win_info(1,1,1,&win);

			/* set orbit win */
			/* echo 25 0 1 0 0 0 0 0 0 w h 0 0 0 0 0 0 w h > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&orbit_w,0,sizeof(struct v4l2_ext_vsc_orbit_window));
			orbit_w.video_input.w = p_ctx->param.i_w;
			orbit_w.video_input.h = p_ctx->param.i_h;
			orbit_w.video_output.w = p_ctx->param.o_w;
			orbit_w.video_output.h = p_ctx->param.o_h;
			vsc_set_orbit_window(1,1,&orbit_w);

			/* set orbit move */
			/* echo 25 1 1 0 0 0 0 0 0 w h 0 0 0 0 0 0 w h > /proc/lg/de/v4l2_vsc_debug_func */
			memset(&orbit_m,0,sizeof(struct v4l2_ext_vsc_orbit_window));
			orbit_m.video_input.w = p_ctx->param.o_w;
			orbit_m.video_input.h = p_ctx->param.o_h;
			orbit_m.video_output.w = p_ctx->param.o_w;
			orbit_m.video_output.h = p_ctx->param.o_h;
			vsc_set_orbit_move(1,1,&orbit_m);

			/* set mute */
			/* echo 1 1 1 0 > /proc/lg/de/v4l2_vsc_debug_func */
			val = 0;
			vsc_set_mute(1,1,&val);
		}
		else
		{
			/* set adaptive stream */
			/* echo 9 1 1 0 > /proc/lg/de/v4l2_vsc_debug_func */
			val = 0;
			vsc_set_adaptives_stream(1,1,&val);

			/* set hdr */
			/* echo 11 1 1 0 > /proc/lg/de/v4l2_vsc_debug_func */
			val = V4L2_EXT_VSC_HDR_TYPE_SDR;
			vsc_set_hdr_type(1,1,&val);

			/* set mute */
			/* echo 1 1 1 1 > /proc/lg/de/v4l2_vsc_debug_func */
			val = 1;
			vsc_set_mute(1,1,&val);

			/* set sub mode */
			/* echo 3 1 0 0 0 0 > /proc/lg/de/v4l2_vsc_debug_func */
			sub_mode.win_mode = V4L2_EXT_VSC_WIN_MODE_NONE;
			sub_mode.mirror_mode = V4L2_EXT_VSC_MIRROR_MODE_NONE;
			sub_mode.mem_type = V4L2_EXT_VSC_MEMORY_TYPE_NONE;
			vsc_set_sub_mode(1,1,&sub_mode);

			/* set input */
			/* echo 0 1 1 0 0 0 0 > /proc/lg/de/v4l2_vsc_debug_func */
			input.in.src=V4L2_EXT_VSC_INPUT_SRC_NONE;
			input.in.index=0;
			input.in.attr=0;
			input.out=V4L2_EXT_VSC_DEST_NONE;
			vsc_set_input(1,1,&input);
		}
	}
	return 0;
}

