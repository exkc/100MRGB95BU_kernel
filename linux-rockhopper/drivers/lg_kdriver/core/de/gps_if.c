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
 *  @date		2018-11-29
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
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/delay.h>
#include "os_util.h"
#include "base_device.h"
#include "gps_if.h"
#include "v4l2_gps_dbg.h"

static int unused __attribute__((unused));


extern int VIDEO_GPS_WaitVsync(void);
extern int VIDEO_GPSDMA_WaitVsync(void);

typedef union {
	UINT32 udata32;
	struct {						//0xC9009C30 RO 0x0000_0000
	UINT32 r_x0                             :13;	//(12:0,RO,0x0)
	UINT32 resvd0                           :3;
	UINT32 r_y0                             :13;	//(28:16,RO,0x0)
	UINT32 resvd1                           :1;
	UINT32 v_lock                           :1;	//(30,RO,0x0) //
	UINT32 h_lock                           :1;	//(31,RO,0x0) //
	};
}gps_if_get_bbd_stat0_t;

typedef union {
	UINT32 udata32;
	struct {						//0xC9009C34 RO 0x0000_0000
	UINT32 r_x1                             :13;	//(12:0,RO,0x0)
	UINT32 resvd0                           :3;
	UINT32 r_y1                             :13;	//(28:16,RO,0x0) //
	UINT32 resvd1                           :3;
	};
}gps_if_get_bbd_stat1_t;

struct gps_if_priv {
	void *m2a;
	void *a2m;
	void *stat;
	unsigned int phys;
	OS_SEM_T	lock;
	unsigned int crc[2];
	unsigned int *p_crc[2];
};

struct gps_if_priv gps_if;

int gps_if_streamon(void);
int gps_if_streamoff(void);
int gps_proc_control(int enable, int gps_id, int vdec_id, unsigned int w, unsigned h);
int gps_proc_wait_intr(void);

int gps_if_init(void)
{
	int ret = RET_OK;
	LX_DE_MEM_SYS_INFO_T mem_info;
	UINT32 phys = 0, size = 0;

	OS_InitMutex(&gps_if.lock, OS_SEM_ATTR_DEFAULT);

	ret = DE_IO_GetMEMInfo((unsigned long)&mem_info, 1);
	phys = mem_info.de_gps.base;
	size = mem_info.de_gps.size;
	gps_if.phys = phys;
	gps_if.crc[0] = mem_info.de_gps_crc.base;
	gps_if.crc[1] = gps_if.crc[0] + 4;
	if(gps_if.crc[0]) {
		gps_if.p_crc[0] = (void*)vmap_phys(gps_if.crc[0], sizeof(unsigned int));
		gps_if.p_crc[1] = (void*)vmap_phys(gps_if.crc[1], sizeof(unsigned int));
	}
	else
	{
		gps_if.p_crc[0] = gps_if.p_crc[1] = 0;
	}

	if(phys)
	{
		gps_if.m2a = (void*)vmap_phys(phys, sizeof(struct gps_shared_mem_to_cpu)+sizeof(struct gps_shared_mem_to_mcu)+sizeof(struct gps_shared_mem_status));
		gps_if.a2m = gps_if.m2a + sizeof(struct gps_shared_mem_to_cpu);
		gps_if.stat = gps_if.a2m + sizeof(struct gps_shared_mem_to_mcu);
		memset(gps_if.m2a, 0, sizeof(struct gps_shared_mem_to_cpu));
		memset(gps_if.a2m, 0, sizeof(struct gps_shared_mem_to_mcu));
		memset(gps_if.stat, 0, sizeof(struct gps_shared_mem_status));
		wmb();
	}
	else
	{
		DE_ERROR("no shared-mem");
		return RET_ERROR;
	}

	DE_NOTI("done. phys[0x%08x]", phys);

	return ret;
}

int gps_if_uninit(void)
{
	int ret = RET_OK;

	if(gps_if.m2a)			vunmap_phys(gps_if.m2a);
	if (gps_if.p_crc[0])	vunmap_phys(gps_if.p_crc[0]);
	if (gps_if.p_crc[1])	vunmap_phys(gps_if.p_crc[1]);

	return ret;
}

int gps_if_control(LX_DE_GPS_CTRL_T *p)
{
	int ret = RET_OK;

	p->shared_mem_base = gps_if.phys;

	DE_NOTI("en[%d]/gps[%d]/vdec[%d]/w[%d/%d]h[%d/%d]/s[%d]/y0[0x%08x]/c0[0x%08x]", \
		p->enable, p->gps_id, p->vdec_id, p->width, p->max_w, p->height, p->max_h, p->stride,\
		p->buffer_addr_y[0], p->buffer_addr_c[0]);

	DE_NOTI("y1[0x%08x]/c1[0x%08x]", p->buffer_addr_y[1], p->buffer_addr_c[1]);
	DE_NOTI("y2[0x%08x]/c2[0x%08x]", p->buffer_addr_y[2], p->buffer_addr_c[2]);

	DE_NOTI("bbd[%d][%d/%d/%d/%d/%d]",p->bbd_id,p->bbd_en,\
		(p->bbd_xw>>16)&0xffff,(p->bbd_yh>>16)&0xffff,p->bbd_xw&0xffff,p->bbd_yh&0xffff);

	DE_NOTI("pix_fmt[%s] src_attr[%d]\n", p->pix_fmt == 0 ? "420"  : \
			                 p->pix_fmt == 1 ? "422"  : \
							 p->pix_fmt == 2 ? "ARGB" : \
							 p->pix_fmt == 3 ? "ABGR" : \
							 p->pix_fmt == 4 ? "RGBA" : "None", p->src_attr);

	ret = DE_IO_SetGPSControl((unsigned long)p);

	return ret;
}

int gps_if_streamon(void)
{
	return 0;
}

int gps_if_streamoff(void)
{
	return 0;
}

int gps_if_wait_intr(unsigned int ctrl)
{
	int ret = RET_OK;

	ret = VIDEO_GPSDMA_WaitVsync();

	return ret;

}
static unsigned char update_count[GPS_MAX_INSTANCE] = { 0 };

int gps_if_lock_buffer(unsigned int instance, unsigned int idx, unsigned int flag, unsigned int log_enable)
{
	int ret = RET_OK;
	struct gps_shared_mem_to_mcu *p;

	if (instance>=GPS_MAX_INSTANCE) return RET_ERROR;
	if (idx>=GPS_MAX_BUFFER) return RET_ERROR;
	if (!gps_if.a2m) {DE_ERROR("error"); return RET_ERROR;}

	unused = OS_LockMutex(&gps_if.lock);
	p = gps_if.a2m;
	p->lock_buffer_index[instance] = idx;
	p->lock_buffer_flag[instance][idx] = flag;
	p->count[idx] = update_count[idx]++;
	OS_UnlockMutex(&gps_if.lock);

	if(log_enable == 0)
	DE_NOTI("%s: inst[%d] idx[%d] flag[%d/%d/%d],  update[%d]", flag?"lock":"unlock",\
		instance, idx, p->lock_buffer_flag[instance][0], p->lock_buffer_flag[instance][1], p->lock_buffer_flag[instance][2],update_count[idx]);

	return ret;
}

int gps_if_set_bbd(unsigned int instance, unsigned int *mode)
{
	int ret = RET_OK;
	struct gps_shared_mem_to_mcu *p;

	if(instance>=GPS_MAX_INSTANCE)	return -101;
	if(!gps_if.a2m)					return -102;
	if(!mode)						return -103;

	unused = OS_LockMutex(&gps_if.lock);
	p = gps_if.a2m;
	wmb();
	p->bbd_en[instance] = *mode;
	wmb();
	OS_UnlockMutex(&gps_if.lock);

	GPS_NOTI("bbd : id:%d, en:%d\n",instance,*mode);

	return ret;
}

int gps_if_get_bbd(unsigned int instance, unsigned int *info)
{
	int ret = RET_OK;
	unsigned int i,ratio_w=0,ratio_h=0;
	unsigned int same_mask=0,same_cnt=0;
	unsigned int in_x=0,in_y=0,in_w=0,in_h=0;
	unsigned int out_x=0,out_y=0,out_w=0,out_h=0;
	unsigned int cur_xw=0,cur_yh=0;
	static unsigned int pre_xw[GPS_MAX_INSTANCE] = {-1,-1,-1,-1,-1,-1,-1,-1};
	static unsigned int pre_yh[GPS_MAX_INSTANCE] = {-1,-1,-1,-1,-1,-1,-1,-1};
	gps_bbd_info_t bbd_info;
	gps_if_get_bbd_stat0_t *pre_stat0,*cur_stat0;
	gps_if_get_bbd_stat1_t *pre_stat1,*cur_stat1;
	struct gps_shared_mem_status *p;

	//DE_NOTI("S get_bbd\n");

	unused = OS_LockMutex(&gps_if.lock);

	do {
		#if 1
		if(instance>=GPS_MAX_INSTANCE)	{ret = -101;break;}
		if(!gps_if.stat)				{ret = -102;break;}
		if(!info)						{ret = -103;break;}

		p = gps_if.stat;
		rmb();
		memcpy(&bbd_info,&p->bbd_info[instance],sizeof(gps_bbd_info_t));
		rmb();

		if (bbd_info.in.w==0)		{ret = -104;break;}
		if (bbd_info.in.h==0)		{ret = -105;break;}
		if (bbd_info.out.w==0)		{ret = -106;break;}
		if (bbd_info.out.h==0)		{ret = -107;break;}
		#endif

		cur_stat0 = (gps_if_get_bbd_stat0_t *)&bbd_info.mod_stat0[0];
		cur_stat1 = (gps_if_get_bbd_stat1_t *)&bbd_info.mod_stat1[0];
		for (i=1;i<5;i++)
		{
			pre_stat0 = (gps_if_get_bbd_stat0_t *)&bbd_info.mod_stat0[i];
			pre_stat1 = (gps_if_get_bbd_stat1_t *)&bbd_info.mod_stat1[i];
			if (pre_stat0->r_x0 == cur_stat0->r_x0 && pre_stat0->r_y0 == cur_stat0->r_y0 && \
				pre_stat1->r_x1 == cur_stat1->r_x1 && pre_stat1->r_y1 == cur_stat1->r_y1)
			{
				same_mask |= (0x1<<(i-1));
				same_cnt++;
			}
		}

		if (bbd_info.cnt.update<3)	/*20200424,case of insufficient frame*/
		{
			out_x = 0;
			out_w = bbd_info.out.w;
			out_y = 0;
			out_h = bbd_info.out.h;

			cur_xw = ((out_x&0xffff)<<16)|(out_w&0xffff);
			cur_yh = ((out_y&0xffff)<<16)|(out_h&0xffff);
		}
		else if (same_cnt>=3)	/*20171004,same_cnt for bad connect(QEVENTSEVT-15952,QEVENTSEVT-15801)*/
		{
			/* 20170901, add abnormal case(eg. full black):set zero (MIRACAST-3208) */
			if (cur_stat0->r_x0>cur_stat1->r_x1 || cur_stat0->r_y0>cur_stat1->r_y1)
			{
				in_x = in_y = in_w = in_h = 0;
			}
			else
			{
				in_x = cur_stat0->r_x0;
				in_w = cur_stat1->r_x1-cur_stat0->r_x0+1;
				in_x <<= 1;
				in_w <<= 1;
				in_y = cur_stat0->r_y0;
				in_h = cur_stat1->r_y1-cur_stat0->r_y0+1;
			}

			/* 20200422, update scaled data (SCDCR-3405) */
			ratio_w = (bbd_info.out.w<<10)/bbd_info.in.w;
			ratio_h = (bbd_info.out.h<<10)/bbd_info.in.h;
			out_x = (in_x*ratio_w)>>10;
			out_w = (in_w*ratio_w)>>10;
			out_y = (in_y*ratio_h)>>10;
			out_h = (in_h*ratio_h)>>10;

			cur_xw = ((out_x&0xffff)<<16)|(out_w&0xffff);
			cur_yh = ((out_y&0xffff)<<16)|(out_h&0xffff);
		}
		else
		{
			cur_xw = pre_xw[instance];
			cur_yh = pre_yh[instance];
		}

		/* debug */
		if (bbd_info.dif_stat0>0 || bbd_info.dif_stat1>0)
		{
			gps_if_get_bbd_stat0_t *o00 = (gps_if_get_bbd_stat0_t *)&bbd_info.org_stat0[0];
			gps_if_get_bbd_stat0_t *o01 = (gps_if_get_bbd_stat0_t *)&bbd_info.org_stat0[1];
			gps_if_get_bbd_stat0_t *m00 = (gps_if_get_bbd_stat0_t *)&bbd_info.mod_stat0[0];
			gps_if_get_bbd_stat0_t *d00 = (gps_if_get_bbd_stat0_t *)&bbd_info.dif_stat0;
			gps_if_get_bbd_stat1_t *o10 = (gps_if_get_bbd_stat1_t *)&bbd_info.org_stat1[0];
			gps_if_get_bbd_stat1_t *o11 = (gps_if_get_bbd_stat1_t *)&bbd_info.org_stat1[1];
			gps_if_get_bbd_stat1_t *m10 = (gps_if_get_bbd_stat1_t *)&bbd_info.mod_stat1[0];
			gps_if_get_bbd_stat1_t *d10 = (gps_if_get_bbd_stat1_t *)&bbd_info.dif_stat1;
			DE_NOTI("DIF]%d]:%d,%d,%d,%d|%d,%d,%d,%d -> %d,%d,%d,%d (%d,%d,%d,%d)\n",instance,\
				o01->r_x0,o01->r_y0,o11->r_x1,o11->r_y1,o00->r_x0,o00->r_y0,o10->r_x1,o10->r_y1,\
				m00->r_x0,m00->r_y0,m10->r_x1,m10->r_y1,d00->r_x0,d00->r_y0,d10->r_x1,d10->r_y1);
		}

		#if 1
		if (pre_xw[instance]!=cur_xw || pre_yh[instance]!=cur_yh)
		{
			GPS_NOTI("{%d,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x}\n",\
				instance,bbd_info.cnt.udata32,bbd_info.in.udata32,bbd_info.out.udata32,\
				bbd_info.org_stat0[0],bbd_info.org_stat1[0],bbd_info.org_stat0[1],bbd_info.org_stat1[1],\
				bbd_info.org_stat0[2],bbd_info.org_stat1[2],bbd_info.org_stat0[3],bbd_info.org_stat1[3],\
				bbd_info.org_stat0[4],bbd_info.org_stat1[4]);
			GPS_NOTI("{0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x}\n",\
				bbd_info.mod_stat0[0],bbd_info.mod_stat1[0],bbd_info.mod_stat0[1],bbd_info.mod_stat1[1],\
				bbd_info.mod_stat0[2],bbd_info.mod_stat1[2],bbd_info.mod_stat0[3],bbd_info.mod_stat1[3],\
				bbd_info.mod_stat0[4],bbd_info.mod_stat1[4],bbd_info.dif_stat0,bbd_info.dif_stat1);
			GPS_NOTI("%x,%x|%d,%d,%d,%d|%d,%d|%d,%d,%d,%d -> %d,%d,%d,%d\n",\
				same_cnt,same_mask,in_x,in_y,in_w,in_h,ratio_w,ratio_h,\
				(pre_xw[instance]>>16)&0xffff,(pre_yh[instance]>>16)&0xffff,\
				pre_xw[instance]&0xffff,pre_yh[instance]&0xffff,\
				(cur_xw>>16)&0xffff,(cur_yh>>16)&0xffff,cur_xw&0xffff,cur_yh&0xffff);
			pre_xw[instance]=cur_xw;
			pre_yh[instance]=cur_yh;
		}
		#endif

		GPS_TRACE1("{%d,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x}\n",\
			instance,bbd_info.cnt.udata32,bbd_info.in.udata32,bbd_info.out.udata32,\
			bbd_info.org_stat0[0],bbd_info.org_stat1[0],bbd_info.org_stat0[1],bbd_info.org_stat1[1],\
			bbd_info.org_stat0[2],bbd_info.org_stat1[2],bbd_info.org_stat0[3],bbd_info.org_stat1[3],\
			bbd_info.org_stat0[4],bbd_info.org_stat1[4]);
		GPS_TRACE1("{0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,0x%x}\n",\
			bbd_info.mod_stat0[0],bbd_info.mod_stat1[0],bbd_info.mod_stat0[1],bbd_info.mod_stat1[1],\
			bbd_info.mod_stat0[2],bbd_info.mod_stat1[2],bbd_info.mod_stat0[3],bbd_info.mod_stat1[3],\
			bbd_info.mod_stat0[4],bbd_info.mod_stat1[4],bbd_info.dif_stat0,bbd_info.dif_stat1);
		GPS_TRACE1("%x,%x|%d,%d,%d,%d|%d,%d|%d,%d,%d,%d -> %d,%d,%d,%d\n",\
			same_cnt,same_mask,in_x,in_y,in_w,in_h,ratio_w,ratio_h,\
			(pre_xw[instance]>>16)&0xffff,(pre_yh[instance]>>16)&0xffff,\
			pre_xw[instance]&0xffff,pre_yh[instance]&0xffff,\
			(cur_xw>>16)&0xffff,(cur_yh>>16)&0xffff,cur_xw&0xffff,cur_yh&0xffff);

		info[0] = pre_xw[instance];
		info[1] = pre_yh[instance];
	} while(0);

	OS_UnlockMutex(&gps_if.lock);

	//DE_NOTI("E get_bbd(%d)\n",ret);

	return ret;
}

int gps_if_get_data(int *pInst, struct gps_instance_info *pData)
{
	int ret = RET_OK;
	//int count = 0;
	int wr_done_flag = 0;
	//int instance = 0;
	struct gps_shared_mem_to_cpu *p;

	if(!pInst)  return RET_ERROR;
	if(!pData) return RET_ERROR;
	if(!gps_if.m2a) {DE_ERROR("error"); return RET_ERROR;}

	unused = OS_LockMutex(&gps_if.lock);
	p = gps_if.m2a;

	// read data from shared memory
	wr_done_flag = p->write_done_id;
	//DE_NOTI("wr_done_flag = 0x%08x", wr_done_flag);
#if 0
	do
	{
		if(wr_done_flag & 0x1)
		{
			memcpy(pData, &p->gps_instance[count], sizeof(struct gps_instance_info));
			*pInst = count;
			break;
		}
		wr_done_flag = (wr_done_flag>>1);
	} while(count++<32);
	#if 0
	if(count < 32)
	{
		DE_NOTI("%d :  buf_index[%d], w/h[%d/%d], fr[%d], pts[0x%08x], err_no[%d]", \
						count, \
						p->gps_instance[count].buf_index[0], \
						p->gps_instance[count].ret_w, p->gps_instance[count].ret_h,\
						p->gps_instance[count].fr,	  p->gps_instance[count].pts,\
						p->gps_instance[count].err_no);
	}
	#endif
#else
	if((wr_done_flag>>*pInst) & 0x1){
		memcpy(pData, &p->gps_instance[*pInst], sizeof(struct gps_instance_info));
		p->write_done_id &= ~(1<<*pInst);
		wmb();
	}
	else {
		OS_UnlockMutex(&gps_if.lock);
		return RET_ERROR;
	}
#endif
	OS_UnlockMutex(&gps_if.lock);

	return ret;
}

int gps_if_get_index(unsigned int instance_id, unsigned int *idx)
{
	int ret = RET_OK;
	struct gps_shared_mem_to_cpu *p;

	if(instance_id >= GPS_MAX_INSTANCE) return RET_ERROR;
	if(!idx) return RET_ERROR;
	if(!gps_if.m2a) {DE_ERROR("error"); return RET_ERROR;}

	unused = OS_LockMutex(&gps_if.lock);
	p = gps_if.m2a;
	*idx = p->gps_instance[instance_id].buf_index[0];
	OS_UnlockMutex(&gps_if.lock);

	return ret;
}

char g_en_inst[8] = {0,0,0,0,0,0,0,0};

int gps_proc_control(int enable, int gps_id, int vdec_id, unsigned int w, unsigned h)
{
	int ret = RET_OK;
	LX_DE_GPS_CTRL_T ctrl;
	LX_DE_MEM_SYS_INFO_T mem_info;
	unsigned int frame_base;
	unsigned int y_size = 3*1024*1024;
	unsigned int c_size = y_size>>1;

	ret = DE_IO_GetMEMInfo((unsigned long)&mem_info, 1);
	frame_base = mem_info.de_vt_m2.base + gps_id*(3*y_size + 3*c_size);

	g_en_inst[vdec_id] = enable;

	ctrl.enable = enable;
	ctrl.gps_id = gps_id;
	ctrl.vdec_id = vdec_id;
	ctrl.width = w;
	ctrl.height = h;
	ctrl.shared_mem_base = gps_if.phys;

	ctrl.buffer_addr_y[0] = frame_base;
	ctrl.buffer_addr_y[1] = ctrl.buffer_addr_y[0] + y_size;
	ctrl.buffer_addr_y[2] = ctrl.buffer_addr_y[1] + y_size;

	ctrl.buffer_addr_c[0] = ctrl.buffer_addr_y[2] + y_size;
	ctrl.buffer_addr_c[1] = ctrl.buffer_addr_c[0] + c_size;
	ctrl.buffer_addr_c[2] = ctrl.buffer_addr_c[1] + c_size;

	ret = gps_if_control(&ctrl);

	return ret;
}

int gps_proc_wait_intr(void)
{
	int ret = RET_OK;
	int count = 20;
	int idx;
	struct gps_instance_info inst_info;

	do {
		ret = gps_if_wait_intr(0);

		gps_if_get_data(&idx, &inst_info);
	} while(count--);
	return 0;
}

int gps_if_dma_start(LX_DE_GPSDMA_IPC_T stParams, unsigned int crc_mode)
{
	int ret = 0;
	stParams.crc_y_base = gps_if.crc[0];
	stParams.crc_c_base = gps_if.crc[1];
	stParams.crc_mode   = crc_mode;
	//DE_NOTI("crc y/c base = 0x%08x/0x%08x/%d", stParams.crc_y_base, stParams.crc_c_base, crc_mode);
	ret = DE_IO_SetGPSDMA((unsigned long)&stParams);

	return ret;
}

int gps_if_get_crc(unsigned int crc_mode, unsigned int *crc_y, unsigned int *crc_c)
{
	int ret = 0;
	if (gps_if.p_crc[0] && gps_if.p_crc[1])
	{
		*crc_y = *gps_if.p_crc[0];
		*crc_c = *gps_if.p_crc[1];
	}
	else
	{
		*crc_y = *crc_c = 0;
	}
	if(crc_mode > 0) GPS_NOTI("mode[%d] y[0x%08x] c[0x%08x]",crc_mode, *crc_y, *crc_c);
	return ret;
}
