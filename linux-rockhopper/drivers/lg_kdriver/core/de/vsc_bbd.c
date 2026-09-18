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
#endif
#include "de_def.h"
#include "de_kapi.h"
#include "vsc_bbd.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* ver, yyyy/mm/dd/hh:mm */
#define VSC_BBD_VER		"2024/05/30/15:24"

/* diff(t-2),same(t-1),same(t) : should be bigger than 0 */
#define VSC_BBD_MASK	(0x7)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
struct vsc_bbd_ctx
{
	unsigned int dbg_level;
	unsigned int dif_th;
	unsigned int year;
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
static int vsc_bbd_init_ctrl(struct vsc_bbd_cfg *pcfg);
static int vsc_bbd_is_gav(struct vsc_bbd_cfg *pcfg);
static int vsc_bbd_is_hdr(struct vsc_bbd_cfg *pcfg);
static int vsc_bbd_get_isize(struct vsc_bbd_cfg *pcfg);
static int vsc_bbd_get_state(struct vsc_bbd_cfg *pcfg);
static int vsc_bbd_get_win(struct vsc_bbd_cfg *pcfg);
static unsigned int vsc_bbd_get_board_year(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static struct vsc_bbd_ctx _g_vsc_bbd_ctx;

/*========================================================================================
	Implementation Group
========================================================================================*/
int vsc_bbd_init(void)
{
	memset(&_g_vsc_bbd_ctx,0,sizeof(_g_vsc_bbd_ctx));
	_g_vsc_bbd_ctx.dif_th = 5;
	_g_vsc_bbd_ctx.year = vsc_bbd_get_board_year();

	DE_NOTI("dif_th:%d, year:%d\n",_g_vsc_bbd_ctx.dif_th,_g_vsc_bbd_ctx.year);

	return 0;
}

int vsc_bbd_status(char* buffer)
{
	int len = 0;

	if (!buffer)	return 0;

	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "%-10s : %s\n","version",VSC_BBD_VER);
	len += sprintf( buffer+len, "%-10s : %x\n","dbg_level",_g_vsc_bbd_ctx.dbg_level);
	len += sprintf( buffer+len, "%-10s : %d\n","dif_th",_g_vsc_bbd_ctx.dif_th);
	len += sprintf( buffer+len, "%-10s : %d\n","year",_g_vsc_bbd_ctx.year);
	len += sprintf( buffer+len, "-------------------------------------------------------\n");
	len += sprintf( buffer+len, "usage:\n");
	len += sprintf( buffer+len, "echo %s [%s] > /proc/lg/de/bbd\n","dbg_level","number(hexa)");
	len += sprintf( buffer+len, "echo %s [%s] > /proc/lg/de/bbd\n","dif_th","number(decimal)");
	len += sprintf( buffer+len, "-------------------------------------------------------\n");

	return len;
}

int vsc_bbd_command(char* command)
{
	char *tok, *sav_tok;
	char delim[] = "= \t\n";

	if (!command)	return 0;

	tok=simple_strtok(command, delim, &sav_tok);

	while(tok)
	{
		if (!strncasecmp(tok, "dbg_level", strlen("dbg_level")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				unsigned int dbg_level;
				if(1 != sscanf(tok, "%x", &dbg_level))
				{
					DE_ERROR("invalid param: %s\n", tok);
				}
				_g_vsc_bbd_ctx.dbg_level = dbg_level;
			}
			break;
		}

		if (!strncasecmp(tok, "dif_th", strlen("dif_th")))
		{
			tok=simple_strtok(NULL, delim, &sav_tok);
			if(tok)
			{
				unsigned int dif_th;
				if(1 != sscanf(tok, "%d", &dif_th))
				{
					DE_ERROR("invalid param: %s\n", tok);
				}
				_g_vsc_bbd_ctx.dif_th = dif_th;
			}
			break;
		}

		tok=simple_strtok(NULL, delim, &sav_tok);
	}

	return 0;
}

int vsc_bbd_setdbglevel(int level)
{
	_g_vsc_bbd_ctx.dbg_level = level;
	DE_NOTI("level:%d\n",level);
	return 0;
}

int vsc_bbd_getdbglevel(void)
{
	return _g_vsc_bbd_ctx.dbg_level;
}

int vsc_bbd_init_cfg(int wid, struct vsc_bbd_cfg *pcfg)
{
	int ret;

	if (!pcfg)				return -1;
	if (wid>=LX_DE_WIN_MAX)	return -2;

	memset(pcfg,0,sizeof(struct vsc_bbd_cfg));

	pcfg->wid = wid;
	pcfg->bbd_pos = (pcfg->wid == 0)? 1:0;//1:mid,0:input

	memset(&(pcfg->pre_bbd),-1,sizeof(struct vsc_bbd_rect));
	memset(&(pcfg->ret_bbd),-1,sizeof(struct vsc_bbd_rect));
	memset(pcfg->pre_act,-1,sizeof(struct vsc_bbd_rect)*VSC_BBD_NUM);
	memset(&(pcfg->pre_rpt),-1,sizeof(struct vsc_bbd_rect));
	memset(&(pcfg->pre),-1,sizeof(struct vsc_bbd_win));

	ret = vsc_bbd_init_ctrl(pcfg);
	if (ret<0)	return -3;

	return 0;
}

/* 1:update */
int vsc_bbd_checkupdate(struct vsc_bbd_cfg *pcfg)
{
	int ret_update = 0;
	int ret,i;

	if (!pcfg)						return 0;
	if (pcfg->wid>=LX_DE_WIN_MAX)	return 0;

	do {
		pcfg->step = 0;
		do {
			if (pcfg->hsize == 0)	{pcfg->skip = 1;break;}
			if (pcfg->vsize == 0)	{pcfg->skip = 2;break;}
			if (pcfg->vfreq == 0)	{pcfg->skip = 3;break;}
			ret = vsc_bbd_get_isize(pcfg);
			if (ret<0)				{pcfg->skip = 4;break;}
			if (pcfg->reg_isize.hsize_i==0)	{pcfg->skip = 5;break;}
			if (pcfg->reg_isize.vsize_i==0)	{pcfg->skip = 6;break;}
			pcfg->skip = 0;
		} while(0);

		if (pcfg->skip>0)
		{
			pcfg->update = 0x0;
			memset(&(pcfg->pre),-1,sizeof(struct vsc_bbd_win));
			break;
		}
		pcfg->step |= 0x1;

		ret = vsc_bbd_get_win(pcfg);
		if (ret<0)	{pcfg->step |= 0x2;break;}

		/* check act_win valid */
		if (pcfg->cur.act.w>pcfg->cur.org.w || pcfg->cur.act.h>pcfg->cur.org.h)
		{
			pcfg->step |= 0x4;
			pcfg->cur.act.x = pcfg->cur.act.y = 0;
			pcfg->cur.act.w = pcfg->cur.org.w;
			pcfg->cur.act.h = pcfg->cur.org.h;
		}

		/* cmp pre vs cur */
		if (memcmp(&(pcfg->pre), &(pcfg->cur), sizeof(struct vsc_bbd_win))==0)
		{
			pcfg->step |= 0x10;
			pcfg->update = (pcfg->update<<1)|0x1;
		}
		else
		{
			pcfg->step |= 0x20;
			pcfg->update = (pcfg->update<<1)|0x0;
		}

		/* check same_cnt,same_mask(except for zero) : windowing from T to T-4 */
		pcfg->same_cnt = pcfg->same_mask = 0;
		if (pcfg->cur.act.w == 0 || pcfg->cur.act.h == 0)
		{
			pcfg->step |= 0x100;
		}
		else
		{
			pcfg->step |= 0x200;
			pcfg->same_cnt = 1;
			for (i=0; i<VSC_BBD_NUM; i++)
			{
				if (memcmp(&(pcfg->pre_act[i]), &(pcfg->cur.act), sizeof(struct vsc_bbd_rect))==0)
				{
					pcfg->same_cnt = pcfg->same_cnt+1;
					pcfg->same_mask |= (0x1<<i);
				}
			}
		}

		/* 20171004, add same_cnt,same_mask for bad connection(QEVENTSEVT-15952,QEVENTSEVT-15801) */
		if ((pcfg->update&VSC_BBD_MASK)==(VSC_BBD_MASK>>1) || pcfg->same_cnt>=3)
		{
			if (memcmp(&(pcfg->pre_rpt), &(pcfg->cur.act), sizeof(struct vsc_bbd_rect))==0)
			{
				pcfg->step |= 0x1000;
			}
			else
			{
				pcfg->step |= 0x2000;
				DE_NOTI("%d)%d,%d|%08x,%08x|%08x,%x,%x|%d,%d,%d|%d,%d|%d,%d,%d,%d\n",\
					pcfg->wid,pcfg->hdr_type,pcfg->win_mode,pcfg->reg_isize.addr,pcfg->reg_isize.data,\
					pcfg->update,pcfg->same_cnt,pcfg->same_mask,\
					pcfg->hsize,pcfg->vsize,pcfg->vfreq,\
					pcfg->pre.org.w,pcfg->pre.org.h,\
					pcfg->pre.act.x,pcfg->pre.act.y,pcfg->pre.act.w,pcfg->pre.act.h);
				DE_NOTI("%d)%d,%d,%d,%d -> %d,%d,%d,%d(%d,%d)\n",\
					pcfg->wid,pcfg->cur_bbd.x,pcfg->cur_bbd.y,pcfg->cur_bbd.w,pcfg->cur_bbd.h,\
					pcfg->ret_bbd.x,pcfg->ret_bbd.y,pcfg->ret_bbd.w,pcfg->ret_bbd.h,\
					pcfg->dif_bbd.x,pcfg->dif_bbd.w);
				DE_NOTI("%d)%d,%d,%d,%d -----> %d,%d|%d,%d,%d,%d\n",\
					pcfg->wid,pcfg->pre_rpt.x,pcfg->pre_rpt.y,pcfg->pre_rpt.w,pcfg->pre_rpt.h,\
					pcfg->cur.org.w,pcfg->cur.org.h,\
					pcfg->cur.act.x,pcfg->cur.act.y,pcfg->cur.act.w,pcfg->cur.act.h);
				pcfg->pre_rpt = pcfg->cur.act;
				ret_update = 1;
			}
		}
		memcpy(&(pcfg->pre), &(pcfg->cur), sizeof(struct vsc_bbd_win));
		/* update pre_act, see VSC_BBD_NUM */
		pcfg->pre_act[3] = pcfg->pre_act[2];
		pcfg->pre_act[2] = pcfg->pre_act[1];
		pcfg->pre_act[1] = pcfg->pre_act[0];
		pcfg->pre_act[0] = pcfg->cur.act;
	} while(0);

	if ((vsc_bbd_getdbglevel()>>pcfg->wid)&1) {
		DE_NOTI("%d]%d,%d|%08x,%08x|%08x,%x,%x|%d,%d,%d|%d,%d|%d,%d,%d,%d\n",\
			pcfg->wid,pcfg->hdr_type,pcfg->win_mode,pcfg->reg_isize.addr,pcfg->reg_isize.data,\
			pcfg->update,pcfg->same_cnt,pcfg->same_mask,\
			pcfg->hsize,pcfg->vsize,pcfg->vfreq,\
			pcfg->pre.org.w,pcfg->pre.org.h,\
			pcfg->pre.act.x,pcfg->pre.act.y,pcfg->pre.act.w,pcfg->pre.act.h);
		DE_NOTI("%d]%d,%x,%08x|%d,%d,%d,%d -> %d,%d,%d,%d(%d,%d)\n",\
			pcfg->wid,pcfg->skip,pcfg->step,pcfg->update,\
			pcfg->cur_bbd.x,pcfg->cur_bbd.y,pcfg->cur_bbd.w,pcfg->cur_bbd.h,\
			pcfg->ret_bbd.x,pcfg->ret_bbd.y,pcfg->ret_bbd.w,pcfg->ret_bbd.h,\
			pcfg->dif_bbd.x,pcfg->dif_bbd.w);
		DE_NOTI("%d]%d,%d|%d,%d,%d,%d|%d,%d,%d,%d -> %d,%d|%d,%d,%d,%d\n",\
			pcfg->wid,pcfg->pre.org.w,pcfg->pre.org.h,\
			pcfg->pre.act.x,pcfg->pre.act.y,pcfg->pre.act.w,pcfg->pre.act.h,\
			pcfg->pre_rpt.x,pcfg->pre_rpt.y,pcfg->pre_rpt.w,pcfg->pre_rpt.h,\
			pcfg->cur.org.w,pcfg->cur.org.h,\
			pcfg->cur.act.x,pcfg->cur.act.y,pcfg->cur.act.w,pcfg->cur.act.h);
	}

	return ret_update;
}

static int vsc_bbd_get_win(struct vsc_bbd_cfg *pcfg)
{
	int ret;
	unsigned int x0=1,y0=1,x1=1,y1=1;
	unsigned int pre_x0,pre_x1,pre_y0,pre_y1,cur_x0,cur_y0,cur_x1,cur_y1,dif_x0,dif_x1;

	if (!pcfg)						return -1;
	if (pcfg->wid>=LX_DE_WIN_MAX)	return -2;

	pcfg->cur.org.w = pcfg->hsize;
	pcfg->cur.org.h = pcfg->vsize;

	ret = vsc_bbd_get_state(pcfg);
	if (ret<0)			return -3;

	#if 1	//20200604, adj x0,x1 (QEVENTTWEN-25769)
	cur_x0 = pcfg->reg_stat0.x0;
	cur_y0 = pcfg->reg_stat0.y0;
	cur_x1 = pcfg->reg_stat1.x1;
	cur_y1 = pcfg->reg_stat1.y1;

	pcfg->cur_bbd.x = (unsigned short)cur_x0;
	pcfg->cur_bbd.y = (unsigned short)cur_y0;
	pcfg->cur_bbd.w = (unsigned short)cur_x1;
	pcfg->cur_bbd.h = (unsigned short)cur_y1;

	pre_x0 = pcfg->pre_bbd.x;
	pre_x1 = pcfg->pre_bbd.w;
	pre_y0 = pcfg->pre_bbd.y;
	pre_y1 = pcfg->pre_bbd.h;
	dif_x0 = (pre_x0>cur_x0)? (pre_x0-cur_x0):(cur_x0-pre_x0);
	dif_x1 = (pre_x1>cur_x1)? (pre_x1-cur_x1):(cur_x1-pre_x1);

	#if 1	//20200729, use prev coordinate result, if diff sum is 10 or less.(QEVENTSIT-3896)
	if ((dif_x0 + dif_x1) <= _g_vsc_bbd_ctx.dif_th)
	#else
	if (dif_x0<=2 || dif_x1<=2)
	#endif
	{
		x0 = pcfg->ret_bbd.x;
		x1 = pcfg->ret_bbd.w;
	}
	else
	{
		x0 = cur_x0;
		x1 = cur_x1;
	}
	y0 = cur_y0;
	y1 = cur_y1;

	pcfg->dif_bbd.x = (unsigned short)dif_x0;
	pcfg->dif_bbd.w = (unsigned short)dif_x1;

	pcfg->pre_bbd.x = (unsigned short)cur_x0;
	pcfg->pre_bbd.w = (unsigned short)cur_x1;
	pcfg->pre_bbd.y = (unsigned short)cur_y0;
	pcfg->pre_bbd.h = (unsigned short)cur_y1;

	pcfg->ret_bbd.x = (unsigned short)x0;
	pcfg->ret_bbd.w = (unsigned short)x1;
	pcfg->ret_bbd.y = (unsigned short)y0;
	pcfg->ret_bbd.h = (unsigned short)y1;

	if (dif_x0>0 || dif_x1>0)
	{
		DE_NOTI("D)%d]%d,%d|%d,%d,%d,%d|%d,%d,%d,%d > %d,%d,%d,%d (%d,%d)\n",\
			pcfg->wid,pcfg->hdr_type,pcfg->win_mode,pre_x0,pre_y0,pre_x1,pre_y1,cur_x0,cur_y0,cur_x1,cur_y1,x0,y0,x1,y1,dif_x0,dif_x1);
	}
	#else	//legacy
	cur_x0 = pcfg->cur_bbd.x = (unsigned short)cur_x0;
	cur_y0 = pcfg->cur_bbd.y = (unsigned short)cur_y0;
	cur_x1 = pcfg->cur_bbd.w = (unsigned short)cur_x1;
	cur_y1 = pcfg->cur_bbd.h = (unsigned short)cur_y1;
	#endif

	// 20170719, add abnormal case:set org
	// 20170901, add abnormal case(eg. full black):set zero (MIRACAST-3208)
	if (x0>x1 || y0>y1)
	{
		pcfg->cur.act.x = 0;
		pcfg->cur.act.y = 0;
		pcfg->cur.act.w = 0;
		pcfg->cur.act.h = 0;
	}
	else
	{
		/* get act.x, act.w */
		pcfg->cur.act.x = x0;
		pcfg->cur.act.w = (x1>x0)? (x1-x0+1):0;
		pcfg->cur.act.x <<= 1;
		pcfg->cur.act.w <<= 1;
		/* get act.y, act.h */
		pcfg->cur.act.y = y0;
		pcfg->cur.act.h = (y1>y0)? (y1-y0+1):0;
	}
	return 0;
}

static int vsc_bbd_init_ctrl(struct vsc_bbd_cfg *pcfg)
{
	int ret;
	struct vsc_bbd_reg_ctrl0 ctrl00 = {.addr=0,};
	struct vsc_bbd_reg_ctrl0 ctrl01 = {.addr=0,};

	if (!pcfg)						return -1;
	if (pcfg->wid>=LX_DE_WIN_MAX)	return -2;

	if (lx_chip_rev() >= LX_CHIP_REV( O22, A0))
	{
		// not support from o22 (moved to f/w)
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( E60, A0))
	{
		if (pcfg->wid==0) {
			ctrl00.addr = 0xc900e370;//ND0
		}
		else {
			ctrl00.addr = 0xc9008820;//IPP_M1
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O20, A0))
	{
		if (pcfg->wid==0) {
			ctrl00.addr = 0xc9018370;//ND0
		}
		else {
			ctrl00.addr = 0xc9014720;//IPP_M1
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))
	{
		if (pcfg->wid==0) {
			ctrl00.addr = 0xc9003370;//ND0
		}
		else {
			ctrl00.addr = 0xc9014720;//IPP_M1
		}
	}
	else
	{
		return -3;
	}

	#ifdef INCLUDE_KDRV_SYS
	if (ctrl00.addr) {
		ret = SYS_IO_ReadRegArray(ctrl00.addr,4,&ctrl00.data);
		ctrl00.reg_bbd_en = 1;
		ctrl00.reg_hys_mode = 0;
		ctrl00.reg_op_mode = 0;
		ctrl00.reg_cnt_th = 1;
		ctrl00.reg_diff_th = (pcfg->bbd_pos==0)? 21:18;	//if input, 19+2, else 16+2
		//ctrl00.reg_bbd_mux = 0;
		ret = SYS_IO_WriteRegArray(ctrl00.addr,4,&ctrl00.data);
		DE_NOTI("0] %d, %d, %08x, %08x\n",pcfg->wid,pcfg->bbd_pos,ctrl00.addr,ctrl00.data);
	}

	if (ctrl01.addr) {
		ret = SYS_IO_ReadRegArray(ctrl01.addr,4,&ctrl01.data);
		ctrl01.reg_bbd_en = 1;
		ctrl01.reg_hys_mode = 0;
		ctrl01.reg_op_mode = 0;
		ctrl01.reg_cnt_th = 1;
		ctrl01.reg_diff_th = (pcfg->bbd_pos==0)? 21:18;	//if input, 19+2, else 16+2
		//ctrl01.reg_bbd_mux = 0;
		ret = SYS_IO_WriteRegArray(ctrl01.addr,4,&ctrl01.data);
		DE_NOTI("1] %d, %d, %08x, %08x\n",pcfg->wid,pcfg->bbd_pos,ctrl01.addr,ctrl01.data);
	}
	#endif

	return 0;
}

static int vsc_bbd_is_gav(struct vsc_bbd_cfg *pcfg)
{
	return (!pcfg)? 0:(pcfg->wid==1 && pcfg->win_mode == V4L2_EXT_VSC_WIN_MODE_PBP)? 0:1;
}

static int vsc_bbd_is_hdr(struct vsc_bbd_cfg *pcfg)
{
	return (!pcfg)? 0:(pcfg->hdr_type == V4L2_EXT_VSC_HDR_TYPE_HDR10 || pcfg->hdr_type == V4L2_EXT_VSC_HDR_TYPE_HLG)? 1:0;
}

static int vsc_bbd_get_isize(struct vsc_bbd_cfg *pcfg)
{
	int ret;
	unsigned int is_gav,is_hdr;
	struct vsc_bbd_reg_isize isize = {.addr=0,};

	if (!pcfg)						return -1;
	if (pcfg->wid>=LX_DE_WIN_MAX)	return -2;

	is_gav = vsc_bbd_is_gav(pcfg);
	is_hdr = vsc_bbd_is_hdr(pcfg);

	if (lx_chip_rev() >= LX_CHIP_REV( O26, A0))
	{
		if (pcfg->wid==0) {
			isize.addr = 0xccc10414;//IPP_M0
		}
		else {
			if (is_gav==1) {
				isize.addr = 0xccc13d14;//IPP_G0
			}
			else {
				isize.addr = 0xccc10614;//IPP_M1
			}
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O24, A0))
	{
		if (pcfg->wid==0) {
			isize.addr = 0xcc820414;//IPP_M0
		}
		else {
			if (is_gav==1) {
				isize.addr = 0xcc823c14;//IPP_G0
			}
			else {
				isize.addr = 0xcc820614;//IPP_M1
			}
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( M23, A0))
	{
		if (pcfg->wid==0) {
			isize.addr = 0xcc6d0414;//IPP_M0
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O22, A0))
	{
		if (pcfg->wid==0) {
			isize.addr = 0xcc8c0414;//IPP_M0
		}
		else {
			is_gav = (pcfg->win_mode == V4L2_EXT_VSC_WIN_MODE_PIP)? 1:0;
			if (is_gav==1) {
				isize.addr = 0xcc8c3b14;//IPP_G0
			}
			else {
				isize.addr = 0xcc8c0614;//IPP_M1
			}
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( E60, A0))
	{
		if (pcfg->wid==0) {
			isize.addr = 0xc9003634;//IPP_M0
		}
		else {
			isize.addr = 0xc9008734;//IPP_M1
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O20, A0))
	{
		if (pcfg->wid==0) {
			isize.addr = 0xc9014434;//IPP_M0
		}
		else {
			isize.addr = 0xc9014634;//IPP_M1
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))
	{
		if (pcfg->wid==0) {
			isize.addr = 0xc9014434;//IPP_M0
		}
		else {
			isize.addr = 0xc9014634;//IPP_M1
		}
	}
	else
	{
		return -3;
	}

	#ifdef INCLUDE_KDRV_SYS
	if (isize.addr) {
		ret = SYS_IO_ReadRegArray(isize.addr,4,&isize.data);
		pcfg->reg_isize.addr = isize.addr;
		pcfg->reg_isize.data = isize.data;
	}
	#endif

	return 0;
}

static int vsc_bbd_get_state(struct vsc_bbd_cfg *pcfg)
{
	int ret;
	unsigned int is_gav,is_hdr;
	struct vsc_bbd_reg_stat0 stat0 = {.addr=0,};
	struct vsc_bbd_reg_stat1 stat1 = {.addr=0,};

	if (!pcfg)						return -1;
	if (pcfg->wid>=LX_DE_WIN_MAX)	return -2;

	is_gav = vsc_bbd_is_gav(pcfg);
	is_hdr = vsc_bbd_is_hdr(pcfg);

	if (lx_chip_rev() >= LX_CHIP_REV( O26, A0))
	{
		if (pcfg->wid==0) {
			stat0.addr = 0xccc104d4;//IPP_M0
			stat1.addr = 0xccc104d8;//IPP_M0
		}
		else {
			if (is_gav==1) {
				stat0.addr = 0xccc13878;//HDR_S
				stat1.addr = 0xccc1387c;//HDR_S
			}
			else {
				stat0.addr = 0xccc106d4;//IPP M1
				stat1.addr = 0xccc106d8;//IPP M1
			}
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O24, A0))
	{
		if (pcfg->wid==0) {
			stat0.addr = 0xcc8204d4;//IPP_M0,20230828,change stat reg from 0xccc6037c;//ND0
			stat1.addr = 0xcc8204d8;//IPP_M0,20230828,change stat reg from 0xccc60380;//ND0
		}
		else {
			if (is_gav==1) {
				stat0.addr = 0xcc823878;//HDR_S
				stat1.addr = 0xcc82387c;//HDR_S
			}
			else {
				stat0.addr = 0xcc8206d4;//IPP M1
				stat1.addr = 0xcc8206d8;//IPP M1
			}
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( M23, A0))
	{
		if (pcfg->wid==0) {
			stat0.addr = 0xcc6d04d4;//IPP_M0,20230828,change stat reg from 0xcc5b037c;//ND0
			stat1.addr = 0xcc6d04d8;//IPP_M0,20230828,change stat reg from 0xcc5b0380;//ND0
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O22, A0))
	{
		if (pcfg->wid==0) {
			stat0.addr = 0xcc8c04d4;//IPP_M0,20230828,change stat reg from 0xcc80037c;//ND0
			stat1.addr = 0xcc8c04d8;//IPP_M0,20230828,change stat reg from 0xcc800380;//ND0
		}
		else {
			is_gav = (pcfg->win_mode == V4L2_EXT_VSC_WIN_MODE_PIP)? 1:0;
			if (is_gav==1) {
				stat0.addr = 0xcc8c38b0;//HDR_S
				stat1.addr = 0xcc8c38b4;//HDR_S
			}
			else {
				stat0.addr = 0xcc8c06d4;//IPP M1
				stat1.addr = 0xcc8c06d8;//IPP M1
			}
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( E60, A0))
	{
		if (pcfg->wid==0) {
			stat0.addr = 0xc900e37c;//ND0
			stat1.addr = 0xc900e380;//ND0
		}
		else {
			stat0.addr = 0xc9008830;//IPP M1
			stat1.addr = 0xc9008834;//IPP M1
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O20, A0))
	{
		if (pcfg->wid==0) {
			stat0.addr = 0xc901837c;//ND0
			stat1.addr = 0xc9018380;//ND0
		}
		else {
			stat0.addr = 0xc9014730;//IPP M1
			stat1.addr = 0xc9014734;//IPP M1
		}
	}
	else if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))
	{
		if (pcfg->wid==0) {
			stat0.addr = 0xc900337c;//ND0
			stat1.addr = 0xc9003380;//ND0
		}
		else {
			stat0.addr = 0xc9014730;//IPP M1
			stat1.addr = 0xc9014734;//IPP M1
		}
	}
	else
	{
		return -3;
	}

	#ifdef INCLUDE_KDRV_SYS
	if (stat0.addr) {
		ret = SYS_IO_ReadRegArray(stat0.addr,4,&stat0.data);
		pcfg->reg_stat0.addr = stat0.addr;
		pcfg->reg_stat0.data = stat0.data;
	}

	if (stat1.addr) {
		ret = SYS_IO_ReadRegArray(stat1.addr,4,&stat1.data);
		pcfg->reg_stat1.addr = stat1.addr;
		pcfg->reg_stat1.data = stat1.data;
	}
	#endif

	return 0;
}

static unsigned int vsc_bbd_get_board_year(void)
{
	unsigned int year = 0;

#ifdef BUILD_FEATURE_y29_board
	year = 29;
#elif defined BUILD_FEATURE_y28_board
	year = 28;
#elif defined BUILD_FEATURE_y27_board
	year = 27;
#elif defined BUILD_FEATURE_y26_board
	year = 26;
#elif defined BUILD_FEATURE_y25_board
	year = 25;
#elif defined BUILD_FEATURE_y24_board
	year = 24;
#elif defined BUILD_FEATURE_y23_board
	year = 23;
#elif defined BUILD_FEATURE_y22_board
	year = 22;
#endif

	return year;
}
