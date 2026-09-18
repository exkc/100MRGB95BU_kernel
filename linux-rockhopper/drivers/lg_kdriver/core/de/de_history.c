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
 *	History manager implementation for de and pe devices.
 *
 *
 *	author		arjun.purushothaman (arjun.purushothaman@lge.com)
 *	version		1.0
 *	date		2014.11.3
 *	note		Additional information.
 *
 *	@addtogroup lg1150_de
 *	@{
 */

#include <linux/slab.h>
#include <linux/string.h>
#include "os_util.h"
#include "base_device.h"
#include "history_mgr.h"
#include "de_history.h"

#ifdef USE_HISTORY	

#define ENABLE_RESTRCTURED_CODE

//global variables
//HIST_BUF_T g_history_buffer[HIST_MAX_NUM];	//buffer for module independent command history
extern HIST_BUF_T *g_history_buffer;
extern int g_hist_index;	//reference index for combined history
extern int g_buf_ovflow_flag;
extern int g_isPopActive;
extern int gUseHistory;
//FILE *histfile;
/*
HIST_BUF_T g_de_hist_buff[HIST_DE_MAX_NUM];	//buffer for only DE functions
int g_de_hist_index = 0;

HIST_BUF_T g_pe_hist_buff[HIST_PE_MAX_NUM];	//buffer for only PE functions
int g_pe_hist_index = 0;

//add other module history buffers here
*/
//static functions


#ifdef ENABLE_RESTRCTURED_CODE
static void DE_Pop_SYSTEM_Hist(unsigned int cmd, unsigned int index);
static void DE_Pop_SRC_Hist(unsigned int cmd, unsigned int index);
static void DE_Pop_WIN_Hist(unsigned int cmd, unsigned int index);
static void DE_Pop_OP_Hist(unsigned int cmd, unsigned int index);
static void DE_Pop_CNTL_Hist(unsigned int cmd, unsigned int index);
static void DE_Pop_MISC_Hist(unsigned int cmd, unsigned int index);
static void DE_Populate_SYSTEM_Fn(void);
static void DE_Populate_SRC_Fn(void);
static void DE_Populate_WIN_Fn(void);
static void DE_Populate_OP_Fn(void);
static void DE_Populate_MISC_Fn(void);
static void DE_Populate_CNTL_Fn(void);

extern FUNC_NAME_LIST_T g_de_func_list[];

#endif

//Push function for DE functions
int DE_Push_Hist(unsigned int cmd, unsigned long arg )
{
	int ret = RET_OK;
	void *param = (void __user *)arg;
	//printk("in DE push\n");
	UINT32 idx  = (UINT32)((cmd >> _IOC_NRSHIFT)   & _IOC_NRMASK);
	UINT32 size = (UINT32)((cmd >> _IOC_SIZESHIFT) & _IOC_SIZEMASK);

	if(idx > DE_IOC_MAXNR) {
		return RET_ERROR;
	}

	//printk("idx = %x size = %x\n",idx,size);
	g_history_buffer[g_hist_index].c = cmd;
	g_history_buffer[g_hist_index].pe_info = 0;//unused variable in de case.
	if(g_history_buffer[g_hist_index].p == NULL){
		g_history_buffer[g_hist_index].p = (UINT8 *)OS_Malloc(size);
	}

	ret = copy_from_user(g_history_buffer[g_hist_index].p, (void __user *)param, size);
	if(ret) printk("de push history error\n");

	return ret;
}

#ifndef ENABLE_RESTRCTURED_CODE
//Pop function for DE functions
static int DE_Pop_Hist(unsigned int cmd, unsigned int index)
{
	int ret = RET_OK;
	char funcName[NAME_MAX_SIZE];
	int i,j,callindex, ioctlNR=-1;
	for(i=0;i<(sizeof(g_de_func_list)/sizeof(g_de_func_list[0]));i++)
	{
		if(g_de_func_list[i].c == cmd)
		{
			for(j=0;j<NAME_MAX_SIZE;j++)
			{
				funcName[j] = g_de_func_list[i].s[j];
				if(g_de_func_list[i].s[j] == 0) break;
			}
		}
	}
	callindex = index + g_buf_ovflow_flag*HIST_MAX_NUM;

	printk("\n\t%d) At timestamp : %06d.%06d seconds after Bootup\n\t",callindex, \
								g_history_buffer[index].t.sec, \
								g_history_buffer[index].t.msec*1000 + g_history_buffer[index].t.usec);
	printk("%s Called with Parameters:\n ",funcName);

	switch(cmd)
			{
				case DE_IOW_DE_INIT:
					{LX_DE_PANEL_TYPE_T *p = (LX_DE_PANEL_TYPE_T *)g_history_buffer[index].p;
					printk("\t\tpanel type [%d] ",*p);
					printk("\t\t(0:1920/1366/1024/1365/3840/1280/720/640/576)\n");
					}break;
				case DE_IOR_GET_FIRMWARE_INFO:
					{LX_DE_FIRMWARE_INFO_T *p = (LX_DE_FIRMWARE_INFO_T *)g_history_buffer[index].p;
					printk("\t\tversion [%d] y/m/d  %d/%d/%d\n",  \
					p->version,p->date.year,p->date.month,p->date.day);}break;
				case DE_IOW_FW_DOWNLOAD:
					{LX_DE_FW_DWLD_T *p = (LX_DE_FW_DWLD_T *)g_history_buffer[index].p;
					printk("\t\tfw inx[%d] cfg[%d], size[%d]\n",p->inx,p->cfg,p->size);}break;
				case DE_IOW_SET_IF_CONFIG:
					{LX_DE_IF_CONFIG_T *p = (LX_DE_IF_CONFIG_T *)g_history_buffer[index].p;
					printk("\t\tconfig_type   [%d] ",p->config_type);
					printk("\t\t(0:all,1:display_device,2:mirror,3:frc,4:3d)\n");
					printk("\t\tdisplay_type  [%d] ",p->display_type);
					printk("\t\t(0:LCD/PDP/OLED/CP/STB)\n");
					printk("\t\tdisplay_mirror[%d] ",p->display_mirror);
					printk("\t\t(0:off/x/y/x_y)\n");
					printk("\t\tfrc_type      [%d] ",p->frc_type);
					printk("\t\t(0:internal/external)\n");
					printk("\t\ttrid_type [%d] (0:off/on)\n",p->trid_type);}break;
				case DE_IOW_SET_DIS_FMT:
					{LX_DE_DIS_FMT_T *p = (LX_DE_DIS_FMT_T *)g_history_buffer[index].p;
					printk("\t\tpanel_type [%d]\n",p->panel_type);
					printk("\t\tfr_rate    [%d]\n",p->fr_rate);
					printk("\t\th_total    [%d]\n",p->h_total);
					printk("\t\tv_total    [%d]\n",p->v_total);
					printk("\t\th_active   [%d]\n",p->h_active);
					printk("\t\tv_active   [%d]\n",p->v_active);
					printk("\t\tdev_type   [%d] (0:LCD/PDP/OLED/BOX/GTV_STB)\n",\
					p->dev_type);}break;
				case DE_IOW_SET_FR_RATE:
					{LX_DE_FR_RATE_T *p = (LX_DE_FR_RATE_T *)g_history_buffer[index].p;
					printk("\t\tfree run   [%d]\n",p->isForceFreeRun);
					printk("\t\tframe rate [%d]\n",p->fr_rate);}break;
				case DE_IOR_GET_OUT_FR_RATE:
					{LX_DE_FR_RATE_T *p = (LX_DE_FR_RATE_T *)g_history_buffer[index].p;
					printk("\t\tfree run   [%d]\n",p->isForceFreeRun);
					printk("\t\tframe rate [%d]\n",p->fr_rate);}break;
				case DE_IOW_SET_DIS_OUT:
					{BOOLEAN *p = (BOOLEAN *)g_history_buffer[index].p;
					printk("\t\tdisplay out [%d]\n", *p);}break;
				case DE_IOW_SET_INPUT_WIN:
					{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)g_history_buffer[index].p;
					printk("\t\twin [%d]\n",p->win_id);
					printk("\t\trect w/h/x/y  %d/%d/%d/%d\n",\
					p->rect.w,p->rect.h,p->rect.x,p->rect.y);}break;
				case DE_IOW_SET_OUT_WIN:
					{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)g_history_buffer[index].p;
					printk("\t\twin [%d]\n",p->win_id);
					printk("\t\trect w/h/x/y  %d/%d/%d/%d\n",\
					p->rect.w,p->rect.h,p->rect.x,p->rect.y);}break;
				case DE_IOW_SET_WIN_BLANK:
					{LX_DE_SET_WIN_BLANK_T *p = (LX_DE_SET_WIN_BLANK_T *)g_history_buffer[index].p;
					printk("\t\twin    [%d]\n",p->win_id);
					printk("\t\tenable [%d]  isRGB [%d]\n",p->bEnable,p->isRGB);
					printk("\t\tcolor r/g/b  %d/%d/%d\n",\
					p->win_color.r,p->win_color.g,p->win_color.b);}break;
				case DE_IOW_SET_BG_COLOR:
					{LX_DE_COLOR_T *p = (LX_DE_COLOR_T *)g_history_buffer[index].p;
					printk("\t\tr/g/b  %d/%d/%d\n",p->r,p->g,p->b);}break;
				case DE_IOW_SET_ZLIST:
					{LX_DE_ZLIST_T *p = (LX_DE_ZLIST_T *)g_history_buffer[index].p;
					printk("\t\tenable [%d]\n",p->enable);
					printk("\t\torder %d/%d (top/bot)\n",p->z_list[0],p->z_list[1]);
					printk("\t\talpha %d/%d (top/bot)\n",p->alpha[0],p->alpha[1]);}break;
				case DE_IOW_SET_MULTI_VISION:   // for multi-vision demo
					{LX_DE_RECT_T *p = (LX_DE_RECT_T *)g_history_buffer[index].p;
					printk("\t\tw/h/x/y %d/%d/%d/%d\n",p->w,p->h,p->x,p->y);}break;
				case DE_IOW_SET_CVI_SRC_TYPE:
					{LX_DE_CVI_SRC_TYPE_T *p = (LX_DE_CVI_SRC_TYPE_T *)g_history_buffer[index].p;
					printk("\t\tcvi ch   [%d]\n",p->cvi_channel);
					printk("\t\tsrc size h/v/ho/vo %d/%d/%d/%d\n",\
					p->size_offset.hsize,p->size_offset.vsize,\
					p->size_offset.hoffset,p->size_offset.voffset);
					printk("\t\tcolor [%d] (0:601SD,1:709HD,2:RGB,3:RGBEX,\n",p->color);
					printk("\t\t           4:XVYCC601,5:XVYCC709,6:601CVD)\n");
					printk("\t\taspect   [%d] (0:4|3,1:16|9)\n",p->aspect);
					printk("\t\tscan     [%d] (0:I,1:P)\n",p->scan);
					printk("\t\tbit      [%d] (0:10bit,1:8bit)\n",p->bit_res);
					printk("\t\tc_sample [%d] (0:422,1:444)\n",p->c_sample);
					printk("\t\tde_mode  [%d] (0:normal sync,1:hdmi sync)\n",p->de_mode);
					printk("\t\tsampling [%d] (0:normal,1:double,2:quad)\n",p->sampling);
					printk("\t\tscaler c sample [%d] (0:yuv420,1:422,2:444)\n",p->sc_c_sample);
					printk("\t\tsync stability [%d] (0:std,1:nonstd)\n",p->stability);
					printk("\t\tfield polarity [%d] (0:org,1:reverse)\n",p->field_polarity);
					printk("\t\tyc_delay    [%d] (0:bypass,1:atv,2:others)\n",p->yc_delay);
					printk("\t\tcvi port    [%d] (0:ext_a,1:ext_b,2:cvd,3:adc)\n",p->cvi_port);
					printk("\t\t3d full fmt [%d] (0:nor,1:FP,2:SSF,3:FIA,\n",p->trid_full_format);
					printk("\t\t                 4:row-inter5:col-inter,6:4k2k)\n");
					printk("\t\tcvi src [%d] (0:VGA,1:YPbPr,2:ATV,3:CVBS,\n",p->cvi_input_src);
					printk("\t\t             4:SVIDEO,5:SCART,6:HDMI)\n");
					printk("\t\tcolor std [%d] (0:default,1:NTSC_M,2:NTSC_M_RF,3:PAL,4:PAL_RF,\n",\
					p->cvd_color_std);
					printk("\t\t               5:SECAM,6:SECAM_RF,7:NTSC_443,8:NTSC_443_RF,\n");
					printk("\t\t               9:PAL_60,10:PAL_M_RF,11:PAL_M,12:PAL_M_RF,\n");
					printk("\t\t               13:PAL_NC,14:PAL_NC_RF,15:UNKNOWN)\n");}break;
				case DE_IOW_SET_3D_INOUT_CTRL:  // 3D
					{LX_DE_3D_INOUT_CTRL_T *p = (LX_DE_3D_INOUT_CTRL_T *)g_history_buffer[index].p;
					printk("\t\trun mode     [%d] ",p->run_mode);
					printk("\t\t(0:off,1:on,2:3dTo2d,3:2dTo3d\n");
					printk("\t\tin_fmt       [%d] ",p->in_img_fmt);
					printk("\t\t(0:TB,1:SS,2:QNC,3:CB,4:FP,5:FRI,6:FIA,7:FS,8:LIA,");
					printk("\t\t9:SSF,10:DHD,11:COA,12:LIAH)\n");
					printk("\t\tin_lr_order  [%d] ",p->in_lr_order);
					printk("\t\t(0:r first,1:l first)\n");
					printk("\t\tout fmt      [%d] ",p->out_img_fmt);
					printk("\t\t(0:2D,1:TB,2:SS,3:FS,4:FU,5:DTB,6:DSS)\n");
					printk("\t\tout_lr_order [%d] ",p->out_lr_order);
					printk("\t\t(0:r first,1:l first)\n");}break;
				case DE_IOW_SET_UD_MODE:        // UD
					{BOOLEAN *p = (BOOLEAN *)g_history_buffer[index].p;
					printk("\t\tud mode [%d]\n",*p);}break;
				case DE_IOW_MULTI_WIN_ENABLE:   // PIP
					{BOOLEAN *p = (BOOLEAN *)g_history_buffer[index].p;
					printk("\t\tpip en [%d]\n",*p);}break;
				case DE_IOW_SET_CVE:
					{LX_DE_CVE_PARAM_T *p = (LX_DE_CVE_PARAM_T *)g_history_buffer[index].p;
					printk("\t\tpath [%d] (0:w/osd,1:wo/osd,2:src)\n",p->fb);
					printk("\t\ttime [%d] (0:NTSC,1:PAL,2:SECAM)\n",p->std);}break;
				case DE_IOW_SET_DVR_FMT_CTRL:
					{LX_DE_DVR_DISFMT_T *p = (LX_DE_DVR_DISFMT_T *)g_history_buffer[index].p;
					printk("\t\tonoff [%d]\n",p->bOnOff);
					printk("\t\tscan  [%d] (0:i,1:p)\n",p->scan);
					printk("\t\th/v   %d/%d\n", p->h_size,p->v_size);
					printk("\t\tfr rate    %d\n",p->fr_rate);
					printk("\t\tbase addr  0x%08x\n",p->baseAddr);}break;
				case DE_IOW_SET_VTM:
					{LX_DE_VTM_FRAME_INFO_T *p = (LX_DE_VTM_FRAME_INFO_T *)g_history_buffer[index].p;
					printk("\t\twin    [%d]\n",p->win_id);
					printk("\t\taddr   0x%08x\n",p->address);
					printk("\t\tfd     [%d]\n",p->mem_fd);
					printk("\t\tenable [%d]\n",p->enable);
					printk("\t\tstride %d\n",p->stride);
					printk("\t\tsampling [%d] (0:420,1:422,2:444)\n",p->sampling);}break;
				case DE_IOR_GET_VTM:
					{LX_DE_VTM_FRAME_INFO_T *p = (LX_DE_VTM_FRAME_INFO_T *)g_history_buffer[index].p;
					printk("\t\twin    [%d]\n",p->win_id);}break;
				case DE_IOR_GET_SCALER_INFO:    // for emp csc converter(YC->ARGB)
					{LX_DE_SCALER_INFO_T *p = (LX_DE_SCALER_INFO_T *)g_history_buffer[index].p;
					printk("\t\twin [%d]\n",p->win_id);
					printk("\t\tw/h/s %d/%d/%d\n",p->width,p->height,p->stride);
					printk("\t\tsampling [%d] (0:420/422/444)\n",p->sampling);
					printk("\t\ty/c addr 0x%08x/0x%08x\n",\
					(UINT32)p->p_y_frame,(UINT32)p->p_cbcr_frame);}break;
				case DE_IOW_SET_LOW_DELAY:
					{UINT32 *p = (UINT32 *)g_history_buffer[index].p;
					printk("\t\tparam  0x%08x\n",*p);}break;
				case DE_IOW_SET_CAPTURE:
					{LX_DE_CAPTURE_CTRL_T *p = (LX_DE_CAPTURE_CTRL_T *)g_history_buffer[index].p;
					printk("\t\tlocation [%d] (0:source,1:display)\n",p->location);
					printk("\t\tin win w/h/x/y %d/%d/%d/%d\n",\
					p->inWin.w,p->inWin.h,p->inWin.x,p->inWin.y);
					printk("\t\tout win w/h %d/%d\n",p->wOutSize,p->hOutSize);
					printk("\t\tpixel fmt [%d] (0:RGB10/RGB8/YC444_10/444_8/",p->pixelFormat);
					printk("\t\t422_10/422_8/420_10/420_8)\n");
					printk("\t\ty/c addr 0x%08x/0x%08x, stride[%d]\n",\
					(UINT32)p->p_y_frame,(UINT32)p->p_cbcr_frame, p->stride);}break;
				case DE_IOW_SET_CVI_FREEZE:
					{LX_DE_CVI_CAPTURE_FREEZE_T *p = (LX_DE_CVI_CAPTURE_FREEZE_T *)g_history_buffer[index].p;
					printk("\t\tOn/Off capture [%d] cvifreeze [%d]\n",\
							p->bCaptureOnOff, p->bCviFreezeOnOff);}break;
				case DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER:
					{LX_DE_CVI_RW_VIDEO_FRAME_T *p = (LX_DE_CVI_RW_VIDEO_FRAME_T *)g_history_buffer[index].p;
					printk("\t\twin [%d]\n",p->region.win_id);
					printk("\t\tw/h/x/y %d/%d/%d/%d\n",\
					p->region.pixelGrabW,p->region.pixelGrabH,\
					p->region.pixelGrabX,p->region.pixelGrabY);
					printk("\t\treal w/h in memory  %d/%d\n",\
					p->region.realPixelGrabW,p->region.realPixelGrabH);
					printk("\t\tcolorspace [%d] (0:yuv,1:rgb)\n",p->region.colorSpace);
					printk("\t\tcolorDepth [%d] (0:8bit,1:10bit)\n",p->region.colorDepth);
					printk("\t\tphy Y8/Y2/C8/C2 [0x%08x/0x%08x/0x%08x/0x%08x] , stride [%d]",\
					p->frameAddr.phyFrameAddrY8,p->frameAddr.phyFrameAddrC8,\
					p->frameAddr.phyFrameAddrY2,p->frameAddr.phyFrameAddrC2,\
					p->frameAddr.stride);}break;
				case DE_IOW_SET_INNER_PATTERN:
					{LX_DE_INNER_PATTERN_T *p = (LX_DE_INNER_PATTERN_T *)g_history_buffer[index].p;
					printk("\t\tinner pattern  en[%d] type[%d](0:full-gray,1:white-box) level[%d]\n",
					p->enable,p->type,p->level);}break;
				case DE_IOW_SET_WIN_FREEZE:
					{LX_DE_WIN_FREEZE_T *p = (LX_DE_WIN_FREEZE_T *)g_history_buffer[index].p;
					printk("\t\twin[%d] enable[%d] loc[%d] (0:disp,1:input,2:sub)\n",\
					p->win_id, p->bEnable,p->location);}break;
				case DE_IOW_SET_WIN_PORT_SRC:
					{LX_DE_INPUT_SOURCE_T *p = (LX_DE_INPUT_SOURCE_T *)g_history_buffer[index].p;
					printk("\t\twin[%d] type[%d] port[%d] \n" ,p->srcId, p->srcType,p->srcPort);
					printk("\t\t type=(0:none,1:vga,2:ypbpr,3:atv,4:cvbs,5:scart,");
					printk("\t\t       6:hdmi,7:mvi,8:cpu,9:fb)\n");}break;
				case DE_IOW_SET_CVI_TPG:
					{LX_DE_CVI_TPG_T *p = (LX_DE_CVI_TPG_T *)g_history_buffer[index].p;
					printk("\t\tcvi channel[%d] ptn[%d] frz[%d] gbr[%d]\n",\
					p->cvi_channel,p->isPtnOn,p->isFrzOn,p->isGBR);
					printk("\t\tpattern color[%d]\n",p->ptnColor);
					printk("\t\t 0:white,1:yellow,2:cyan,3:green,4:magenta,5:red,6:blue,7:black\n");
					printk("\t\t 8:gradation-h,9:grad-v,10:grad-c,11:grad-yc,12:black/white\n");
					}break;
				case DE_IOW_SET_SRC_MIRROR:
					{LX_DE_SRC_MIRROR_T *p = (LX_DE_SRC_MIRROR_T *)g_history_buffer[index].p;
					printk("\t\tsrcPort[%d] dstPort[%d] enb[%d]\n",\
					p->srcPort,p->destPort,p->enable);}break;
				case DE_IOW_SET_ACT_FMT_DETECT:
					{LX_DE_ACT_FORMAT_T *p = (LX_DE_ACT_FORMAT_T *)g_history_buffer[index].p;
					printk("\t\tenable[%d] win_id[%d]\n",p->enable,p->win_id);}break;
				case DE_IOW_SET_CVI_FIR:
					{LX_DE_CVI_FIR_T *p = (LX_DE_CVI_FIR_T *)g_history_buffer[index].p;
					printk("\t\tcvi_ch[%d] enable[%d]\n",p->cvi_channel,p->isEnable);
					printk("\t\ty[%02x %02x %02x %02x %02x %02x %02x %02x]\n",\
					p->fir_coef[0], p->fir_coef[1], p->fir_coef[2], p->fir_coef[3],\
					p->fir_coef[4], p->fir_coef[5], p->fir_coef[6], p->fir_coef[7]);
					printk("\t\tc[%02x %02x %02x %02x %02x %02x]\n",\
					p->fir_coef_CbCr[0], p->fir_coef_CbCr[1], p->fir_coef_CbCr[2],\
					p->fir_coef_CbCr[3], p->fir_coef_CbCr[4], p->fir_coef_CbCr[5]);}break;
				case DE_IOW_SET_CVI_CSAMPLE_MODE:
					{LX_DE_CSAMPLE_MODE_T *p = (LX_DE_CSAMPLE_MODE_T *)g_history_buffer[index].p;
					printk("\t\tcvi_ch[%d] is3tap[%d]\n",p->cvi_channel,p->is3tap);}break;
				case DE_IOW_SET_SUB_WIN:
					{LX_DE_SET_SUB_WIN_T *p = (LX_DE_SET_SUB_WIN_T *)g_history_buffer[index].p;
					printk("\t\tsub_win[%d]\n",p->win_id);}break;
				case DE_IOR_GET_SYS_STATUS:
					{LX_DE_SYS_STATUS_T *p = (LX_DE_SYS_STATUS_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,status_type,"\n");}break;
				case DE_IOR_GET_CAPACITY:
					{LX_DE_CAPACITY_T *p = (LX_DE_CAPACITY_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,chip_id," ");PRINT_FIELD(p,max_win," ");PRINT_FIELD(p,max_layer,"\n");
					PRINT_FIELD(p,max_in_fr_rate," ");PRINT_FIELD(p,max_out_fr_rate," ");PRINT_FIELD(p,mvir_start_num,"\n");
					PRINT_FIELD(p,default_3d_out_fmt,"\n");}break;
				case DE_IOR_GET_INPUT_WIN:
					{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,win_id,"\n");}break;
				case DE_IOR_GET_OUT_WIN:
					{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,win_id,"\n");}break;
				case DE_IOR_GET_SRC_STATUS:
					{LX_DE_SRC_STATUS_T *p = (LX_DE_SRC_STATUS_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,status_type,"\n");}break;
				case DE_IOW_SET_CVI_HDMIPORT:
					{LX_DE_HDMIPORT_T *p = (LX_DE_HDMIPORT_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,win_id," ");PRINT_FIELD(p,port_num,"\n");}break;
				case DE_IOR_GET_LOW_DELAY:
					{LX_DE_LOW_DELAY_T *p = (LX_DE_LOW_DELAY_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,wId_enable,"\n");}break;
				case DE_IOW_SET_VCS:
					{LX_DE_VCS_IPC_T *p = (LX_DE_VCS_IPC_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,inx," ");PRINT_FIELD(p,data,"\n");}break;
				case DE_IOW_SET_OPERATION:
					{LX_DE_OPERATION_CTRL_T *p = (LX_DE_OPERATION_CTRL_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,win_id," ");PRINT_FIELD(p,operation," ");printk("ONE_WIN(0) TWO_WIN(1) 3D(2) UD(3) VENC(4)\n");
					PRINT_FIELD(p,multiCtrl," ");PRINT_FIELD(p,udCtrl," ");printk("OFF(0) ON(1) HALF(2)\n");
					PRINT_FIELD(p,ctrl3D.run_mode," ");printk("OFF(0) ON(1) 3DTO2D(2) 2DTO3D(3)\n");
					PRINT_FIELD(p,ctrl3D.in_img_fmt," ");printk("TOPNBOTTOM(0) SIDEBYSIDE(1) QUINCUNX(2) CHECKERBOARD(3)\n");
					printk("\t\t\t\t\tFRAMEPACKING(4) FRAMEINTERLACE(5) FIELDALTERNATE(6) FRAMESEQ(7) LINEALTERNATIVE(8) \n");
					printk("\t\t\t\t\tSIDEBYSIDE_FULL(9) DUAL_HD(10) COLUMNALTERNATIVE(11) LINEALTERNATIVE_HALF(12) \n");
					PRINT_FIELD(p,ctrl3D.in_lr_order," ");printk("R_FIRST(0) L_FIRST(1)\n");
					PRINT_FIELD(p,ctrl3D.out_img_fmt," ");printk("SINGLE_2D(0) SINGLE_TB(1) SINGLE_SS(2) SINGLE_FS(3)\n");
					printk("\t\t\t\t\tDUAL_FULL(4) DUAL_TB(5) DUAL_SS(6) SINGLE_LA(7)  \n");
					PRINT_FIELD(p,ctrl3D.out_lr_order," ");printk("R_FIRST(0) L_FIRST(1)\n");
					PRINT_FIELD(p,vencCtrl.bOnOff," ");printk("OFF(0) ON(1)\n");
					PRINT_FIELD(p,vencCtrl.scan," ");printk("INTERLACED(0) PROGRESSIVE(1)\n");
					PRINT_FIELD(p,vencCtrl.hSize," ");PRINT_FIELD(p,vencCtrl.vSize," ");PRINT_FIELD(p,vencCtrl.frRate,"\n");}break;
				case DE_IOW_SET_SUB_OPERATION:
					{LX_DE_SUB_OPERATION_CTRL_T *p = (LX_DE_SUB_OPERATION_CTRL_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,win_id," ");PRINT_FIELD(p,operation," ");printk("OFF(0) CAPTURE(1) VENC(2) SCART_OUT(3)\n");
					PRINT_FIELD(p,capture_enable,"\n");
					PRINT_FIELD(p,vencCtrl.bOnOff," ");printk("OFF(0) ON(1)\n");
					PRINT_FIELD(p,vencCtrl.scan," ");printk("INTERLACED(0) PROGRESSIVE(1)\n");
					PRINT_FIELD(p,vencCtrl.hSize," ");PRINT_FIELD(p,vencCtrl.vSize," ");PRINT_FIELD(p,vencCtrl.frRate,"\n");}break;
				case DE_IOW_REG_WR:
					{LX_DE_REG_WR_T *p = (LX_DE_REG_WR_T *)g_history_buffer[index].p;
					PRINT_FIELD(p,wr_addr," ");PRINT_FIELD(p,wr_data,"\n");}break;
				default :printk("\t\t unimplemented DE History Print \n");
					break;
			}
	return ret;
}

#else

static void DE_Pop_SYSTEM_Hist(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOW_DE_INIT:
			{LX_DE_PANEL_TYPE_T *p = (LX_DE_PANEL_TYPE_T *)g_history_buffer[index].p;
			printk("\t\tpanel type [%d] ",*p);
			printk("\t\t(0:1920/1366/1024/1365/3840/1280/720/640/576)\n");
			}break;
		case DE_IOR_GET_FIRMWARE_INFO:
			{LX_DE_FIRMWARE_INFO_T *p = (LX_DE_FIRMWARE_INFO_T *)g_history_buffer[index].p;
			printk("\t\tversion [%d] y/m/d	%d/%d/%d\n",  \
			p->version,p->date.year,p->date.month,p->date.day);
			}break;
		case DE_IOW_FW_DOWNLOAD:
			{LX_DE_FW_DWLD_T *p = (LX_DE_FW_DWLD_T *)g_history_buffer[index].p;
			printk("\t\tfw inx[%d] cfg[%d], size[%d]\n",p->inx,p->cfg,p->size);
			}break;
		case DE_IOW_SET_IF_CONFIG:
			{LX_DE_IF_CONFIG_T *p = (LX_DE_IF_CONFIG_T *)g_history_buffer[index].p;
			printk("\t\tconfig_type   [%d] ",p->config_type);
			printk("\t\t(0:all,1:display_device,2:mirror,3:frc,4:3d)\n");
			printk("\t\tdisplay_type  [%d] ",p->display_type);
			printk("\t\t(0:LCD/PDP/OLED/CP/STB)\n");
			printk("\t\tdisplay_mirror[%d] ",p->display_mirror);
			printk("\t\t(0:off/x/y/x_y)\n");
			printk("\t\tfrc_type	  [%d] ",p->frc_type);
			printk("\t\t(0:internal/external)\n");
			printk("\t\ttrid_type [%d] (0:off/on)\n",p->trid_type);
			}break;
		case DE_IOR_GET_CAPACITY:
			{LX_DE_CAPACITY_T *p = (LX_DE_CAPACITY_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,chip_id," ");PRINT_FIELD(p,max_win," ");PRINT_FIELD(p,max_layer,"\n");
			PRINT_FIELD(p,max_in_fr_rate," ");PRINT_FIELD(p,max_out_fr_rate," ");PRINT_FIELD(p,mvir_start_num,"\n");
			PRINT_FIELD(p,default_3d_out_fmt,"\n");
			}break;
		case DE_IOW_SET_OUTPUT_MODE:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_DIS_FMT:
			{LX_DE_DIS_FMT_T *p = (LX_DE_DIS_FMT_T *)g_history_buffer[index].p;
			printk("\t\tpanel_type [%d]\n",p->panel_type);
			printk("\t\tfr_rate    [%d]\n",p->fr_rate);
			printk("\t\th_total    [%d]\n",p->h_total);
			printk("\t\tv_total    [%d]\n",p->v_total);
			printk("\t\th_active   [%d]\n",p->h_active);
			printk("\t\tv_active   [%d]\n",p->v_active);
			printk("\t\tdev_type   [%d] (0:LCD/PDP/OLED/BOX/GTV_STB)\n",\
			p->dev_type);
			}break;
		case DE_IOW_SET_FR_RATE:
			{LX_DE_FR_RATE_T *p = (LX_DE_FR_RATE_T *)g_history_buffer[index].p;
			printk("\t\tfree run   [%d]\n",p->isForceFreeRun);
			printk("\t\tframe rate [%d]\n",p->fr_rate);
			}break;
		case DE_IOR_GET_OUT_FR_RATE:
			{LX_DE_FR_RATE_T *p = (LX_DE_FR_RATE_T *)g_history_buffer[index].p;
			printk("\t\tfree run   [%d]\n",p->isForceFreeRun);
			printk("\t\tframe rate [%d]\n",p->fr_rate);
			}break;
		case DE_IOW_SET_DIS_OUT:
			{BOOLEAN *p = (BOOLEAN *)g_history_buffer[index].p;
			printk("\t\tdisplay out [%d]\n", *p);
			}break;
		case DE_IOR_GET_SYS_STATUS:
			{LX_DE_SYS_STATUS_T *p = (LX_DE_SYS_STATUS_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,status_type,"\n");
			}break;
		default:
			{
				printk("\t\t unimplemented DE History Print \n");
			}
	}
}

static void DE_Pop_SRC_Hist(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOW_SET_WIN_PORT_SRC:
			{LX_DE_INPUT_SOURCE_T *p = (LX_DE_INPUT_SOURCE_T *)g_history_buffer[index].p;
			printk("\t\twin[%d] type[%d] port[%d] \n" ,p->srcId, p->srcType,p->srcPort);
			printk("\t\t type=(0:none,1:vga,2:ypbpr,3:atv,4:cvbs,5:scart,");
			printk("\t\t	   6:hdmi,7:mvi,8:cpu,9:fb)\n");
			}break;
		case DE_IOW_SET_CVI_SRC_TYPE:
			{LX_DE_CVI_SRC_TYPE_T *p = (LX_DE_CVI_SRC_TYPE_T *)g_history_buffer[index].p;
			printk("\t\tcvi ch	 [%d]\n",p->cvi_channel);
			printk("\t\tsrc size h/v/ho/vo %d/%d/%d/%d\n",\
			p->size_offset.hsize,p->size_offset.vsize,\
			p->size_offset.hoffset,p->size_offset.voffset);
			printk("\t\tcolor [%d] (0:601SD,1:709HD,2:RGB,3:RGBEX,\n",p->color);
			printk("\t\t		   4:XVYCC601,5:XVYCC709,6:601CVD)\n");
			printk("\t\taspect	 [%d] (0:4|3,1:16|9)\n",p->aspect);
			printk("\t\tscan	 [%d] (0:I,1:P)\n",p->scan);
			printk("\t\tbit 	 [%d] (0:10bit,1:8bit)\n",p->bit_res);
			printk("\t\tc_sample [%d] (0:422,1:444)\n",p->c_sample);
			printk("\t\tde_mode  [%d] (0:normal sync,1:hdmi sync)\n",p->de_mode);
			printk("\t\tsampling [%d] (0:normal,1:double,2:quad)\n",p->sampling);
			printk("\t\tscaler c sample [%d] (0:yuv420,1:422,2:444)\n",p->sc_c_sample);
			printk("\t\tsync stability [%d] (0:std,1:nonstd)\n",p->stability);
			printk("\t\tfield polarity [%d] (0:org,1:reverse)\n",p->field_polarity);
			printk("\t\tyc_delay	[%d] (0:bypass,1:atv,2:others)\n",p->yc_delay);
			printk("\t\tcvi port	[%d] (0:ext_a,1:ext_b,2:cvd,3:adc)\n",p->cvi_port);
			printk("\t\t3d full fmt [%d] (0:nor,1:FP,2:SSF,3:FIA,\n",p->trid_full_format);
			printk("\t\t				 4:row-inter5:col-inter,6:4k2k)\n");
			printk("\t\tcvi src [%d] (0:VGA,1:YPbPr,2:ATV,3:CVBS,\n",p->cvi_input_src);
			printk("\t\t			 4:SVIDEO,5:SCART,6:HDMI)\n");
			printk("\t\tcolor std [%d] (0:default,1:NTSC_M,2:NTSC_M_RF,3:PAL,4:PAL_RF,\n",\
			p->cvd_color_std);
			printk("\t\t			   5:SECAM,6:SECAM_RF,7:NTSC_443,8:NTSC_443_RF,\n");
			printk("\t\t			   9:PAL_60,10:PAL_M_RF,11:PAL_M,12:PAL_M_RF,\n");
			printk("\t\t			   13:PAL_NC,14:PAL_NC_RF,15:UNKNOWN)\n");
			}break;
		case DE_IOW_SET_CVI_CSAMPLE_MODE:
			{LX_DE_CSAMPLE_MODE_T *p = (LX_DE_CSAMPLE_MODE_T *)g_history_buffer[index].p;
			printk("\t\tcvi_ch[%d] is3tap[%d]\n",p->cvi_channel,p->is3tap);
			}break;
		case DE_IOR_GET_MVI_COLORIMETRY:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_CVI_HDMIPORT:
			{LX_DE_HDMIPORT_T *p = (LX_DE_HDMIPORT_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,win_id," ");PRINT_FIELD(p,port_num,"\n");
			}break;
		case DE_IOW_SET_CVI_FIR:
			{LX_DE_CVI_FIR_T *p = (LX_DE_CVI_FIR_T *)g_history_buffer[index].p;
			printk("\t\tcvi_ch[%d] enable[%d]\n",p->cvi_channel,p->isEnable);
			printk("\t\ty[%02x %02x %02x %02x %02x %02x %02x %02x]\n",\
			p->fir_coef[0], p->fir_coef[1], p->fir_coef[2], p->fir_coef[3],\
			p->fir_coef[4], p->fir_coef[5], p->fir_coef[6], p->fir_coef[7]);
			printk("\t\tc[%02x %02x %02x %02x %02x %02x]\n",\
			p->fir_coef_CbCr[0], p->fir_coef_CbCr[1], p->fir_coef_CbCr[2],\
			p->fir_coef_CbCr[3], p->fir_coef_CbCr[4], p->fir_coef_CbCr[5]);
			}break;
		case DE_IOR_GET_SRC_STATUS:
			{LX_DE_SRC_STATUS_T *p = (LX_DE_SRC_STATUS_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,status_type,"\n");
			}break;
		case DE_IOW_SET_SRC_MIRROR:
			{LX_DE_SRC_MIRROR_T *p = (LX_DE_SRC_MIRROR_T *)g_history_buffer[index].p;
			printk("\t\tsrcPort[%d] dstPort[%d] enb[%d]\n",\
			p->srcPort,p->destPort,p->enable);
			}break;
		default:
			{
				printk("\t\t unimplemented DE History Print \n");
			}
	}
}
static void DE_Pop_CNTL_Hist(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOR_GET_LOW_DELAY:
			{LX_DE_LOW_DELAY_T *p = (LX_DE_LOW_DELAY_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,wId_enable,"\n");
			}break;
		case DE_IOW_SET_LOW_DELAY:
			{UINT32 *p = (UINT32 *)g_history_buffer[index].p;
			printk("\t\tparam  0x%08x\n",*p);
			}break;
		case DE_IOW_SET_WIN_FREEZE:
			{LX_DE_WIN_FREEZE_T *p = (LX_DE_WIN_FREEZE_T *)g_history_buffer[index].p;
			printk("\t\twin[%d] enable[%d] loc[%d] (0:disp,1:input,2:sub)\n",\
			p->win_id, p->bEnable,p->location);
			}break;
		case DE_IOW_SET_ACT_FMT_DETECT:
			{LX_DE_ACT_FORMAT_T *p = (LX_DE_ACT_FORMAT_T *)g_history_buffer[index].p;
			printk("\t\tenable[%d] win_id[%d]\n",p->enable,p->win_id);
			}break;
		default:
			{
				printk("\t\t unimplemented DE History Print \n");
			}
	}
}

static void DE_Pop_WIN_Hist(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOR_GET_INPUT_WIN:
			{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,win_id,"\n");
			}break;
		case DE_IOR_GET_OUT_WIN:
			{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,win_id,"\n");
			}break;
		case DE_IOW_SET_INPUT_WIN:
			{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)g_history_buffer[index].p;
			printk("\t\twin [%d]\n",p->win_id);
			printk("\t\trect w/h/x/y  %d/%d/%d/%d\n",\
			p->rect.w,p->rect.h,p->rect.x,p->rect.y);
			}break;
		case DE_IOW_SET_OUT_WIN:
			{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)g_history_buffer[index].p;
			printk("\t\twin [%d]\n",p->win_id);
			printk("\t\trect w/h/x/y  %d/%d/%d/%d\n",\
			p->rect.w,p->rect.h,p->rect.x,p->rect.y);}break;
		case DE_IOW_SET_ZLIST:
			{LX_DE_ZLIST_T *p = (LX_DE_ZLIST_T *)g_history_buffer[index].p;
			printk("\t\tenable [%d]\n",p->enable);
			printk("\t\torder %d/%d (top/bot)\n",p->z_list[0],p->z_list[1]);
			printk("\t\talpha %d/%d (top/bot)\n",p->alpha[0],p->alpha[1]);
			}break;
		case DE_IOW_SET_MULTI_VISION:
			{LX_DE_RECT_T *p = (LX_DE_RECT_T *)g_history_buffer[index].p;
			printk("\t\tw/h/x/y %d/%d/%d/%d\n",p->w,p->h,p->x,p->y);
			}break;
		case DE_IOW_SET_WIN_BLANK:
			{LX_DE_SET_WIN_BLANK_T *p = (LX_DE_SET_WIN_BLANK_T *)g_history_buffer[index].p;
			printk("\t\twin    [%d]\n",p->win_id);
			printk("\t\tenable [%d]  isRGB [%d]\n",p->bEnable,p->isRGB);
			printk("\t\tcolor r/g/b  %d/%d/%d\n",\
			p->win_color.r,p->win_color.g,p->win_color.b);
			}break;
		case DE_IOW_SET_BG_COLOR:
			{LX_DE_COLOR_T *p = (LX_DE_COLOR_T *)g_history_buffer[index].p;
			printk("\t\tr/g/b  %d/%d/%d\n",p->r,p->g,p->b);
			}break;
		case DE_IOW_SET_INNER_PATTERN:
			{LX_DE_INNER_PATTERN_T *p = (LX_DE_INNER_PATTERN_T *)g_history_buffer[index].p;
			printk("\t\tinner pattern  en[%d] type[%d](0:full-gray,1:white-box) level[%d]\n",
			p->enable,p->type,p->level);
			}break;
		case DE_IOW_SET_CVI_TPG:
			{LX_DE_CVI_TPG_T *p = (LX_DE_CVI_TPG_T *)g_history_buffer[index].p;
			printk("\t\tcvi channel[%d] ptn[%d] frz[%d] gbr[%d]\n",\
			p->cvi_channel,p->isPtnOn,p->isFrzOn,p->isGBR);
			printk("\t\tpattern color[%d]\n",p->ptnColor);
			printk("\t\t 0:white,1:yellow,2:cyan,3:green,4:magenta,5:red,6:blue,7:black\n");
			printk("\t\t 8:gradation-h,9:grad-v,10:grad-c,11:grad-yc,12:black/white\n");
			}break;
		case DE_IOW_SET_SUB_WIN:
			{LX_DE_SET_SUB_WIN_T *p = (LX_DE_SET_SUB_WIN_T *)g_history_buffer[index].p;
			printk("\t\tsub_win[%d]\n",p->win_id);
			}break;
		default:
			{
				printk("\t\t unimplemented DE History Print \n");
			}
	}
}

static void DE_Pop_OP_Hist(unsigned int cmd, unsigned int index)
{

	switch(cmd)
	{
		case DE_IOW_SET_3D_INOUT_CTRL:
			{LX_DE_3D_INOUT_CTRL_T *p = (LX_DE_3D_INOUT_CTRL_T *)g_history_buffer[index].p;
			printk("\t\trun mode	 [%d] ",p->run_mode);
			printk("\t\t(0:off,1:on,2:3dTo2d,3:2dTo3d\n");
			printk("\t\tin_fmt		 [%d] ",p->in_img_fmt);
			printk("\t\t(0:TB,1:SS,2:QNC,3:CB,4:FP,5:FRI,6:FIA,7:FS,8:LIA,");
			printk("\t\t9:SSF,10:DHD,11:COA,12:LIAH)\n");
			printk("\t\tin_lr_order  [%d] ",p->in_lr_order);
			printk("\t\t(0:r first,1:l first)\n");
			printk("\t\tout fmt 	 [%d] ",p->out_img_fmt);
			printk("\t\t(0:2D,1:TB,2:SS,3:FS,4:FU,5:DTB,6:DSS)\n");
			printk("\t\tout_lr_order [%d] ",p->out_lr_order);
			printk("\t\t(0:r first,1:l first)\n");
			}break;
		case DE_IOW_SET_UD_MODE:
			{BOOLEAN *p = (BOOLEAN *)g_history_buffer[index].p;
			printk("\t\tud mode [%d]\n",*p);
			}break;
		case DE_IOW_MULTI_WIN_ENABLE:
			{BOOLEAN *p = (BOOLEAN *)g_history_buffer[index].p;
			printk("\t\tpip en [%d]\n",*p);
			}break;
		case DE_IOR_GET_SCALER_INFO:
			{LX_DE_SCALER_INFO_T *p = (LX_DE_SCALER_INFO_T *)g_history_buffer[index].p;
			printk("\t\twin [%d]\n",p->win_id);
			printk("\t\tw/h/s %d/%d/%d\n",p->width,p->height,p->stride);
			printk("\t\tsampling [%d] (0:420/422/444)\n",p->sampling);
			printk("\t\ty/c addr 0x%08x/0x%08x\n",\
			(UINT32)p->p_y_frame,(UINT32)p->p_cbcr_frame);
			}break;
		case DE_IOW_SET_CVE:
			{LX_DE_CVE_PARAM_T *p = (LX_DE_CVE_PARAM_T *)g_history_buffer[index].p;
			printk("\t\tpath [%d] (0:w/osd,1:wo/osd,2:src)\n",p->fb);
			printk("\t\ttime [%d] (0:NTSC,1:PAL,2:SECAM)\n",p->std);
			}break;
		case DE_IOW_SET_DVR_FMT_CTRL:
			{LX_DE_DVR_DISFMT_T *p = (LX_DE_DVR_DISFMT_T *)g_history_buffer[index].p;
			printk("\t\tonoff [%d]\n",p->bOnOff);
			printk("\t\tscan  [%d] (0:i,1:p)\n",p->scan);
			printk("\t\th/v   %d/%d\n", p->h_size,p->v_size);
			printk("\t\tfr rate    %d\n",p->fr_rate);
			printk("\t\tbase addr  0x%08x\n",p->baseAddr);
			}break;
		case DE_IOW_SET_VTM:
			{LX_DE_VTM_FRAME_INFO_T *p = (LX_DE_VTM_FRAME_INFO_T *)g_history_buffer[index].p;
			printk("\t\twin    [%d]\n",p->win_id);
			printk("\t\taddr   0x%08x\n",p->address);
			printk("\t\tfd	   [%d]\n",p->mem_fd);
			printk("\t\tenable [%d]\n",p->enable);
			printk("\t\tstride %d\n",p->stride);
			printk("\t\tsampling [%d] (0:420,1:422,2:444)\n",p->sampling);
			}break;
		case DE_IOR_GET_VTM:
			{LX_DE_VTM_FRAME_INFO_T *p = (LX_DE_VTM_FRAME_INFO_T *)g_history_buffer[index].p;
			printk("\t\twin    [%d]\n",p->win_id);
			}break;
		case DE_IOW_SET_CAPTURE:
			{LX_DE_CAPTURE_CTRL_T *p = (LX_DE_CAPTURE_CTRL_T *)g_history_buffer[index].p;
			printk("\t\tlocation [%d] (0:source,1:display)\n",p->location);
			printk("\t\tin win w/h/x/y %d/%d/%d/%d\n",\
			p->inWin.w,p->inWin.h,p->inWin.x,p->inWin.y);
			printk("\t\tout win w/h %d/%d\n",p->wOutSize,p->hOutSize);
			printk("\t\tpixel fmt [%d] (0:RGB10/RGB8/YC444_10/444_8/",p->pixelFormat);
			printk("\t\t422_10/422_8/420_10/420_8)\n");
			printk("\t\ty/c addr 0x%08x/0x%08x, stride[%d]\n",\
			(UINT32)p->p_y_frame,(UINT32)p->p_cbcr_frame, p->stride);
			}break;
		case DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER:
			{LX_DE_CVI_RW_VIDEO_FRAME_T *p = (LX_DE_CVI_RW_VIDEO_FRAME_T *)g_history_buffer[index].p;
			printk("\t\twin [%d]\n",p->region.win_id);
			printk("\t\tw/h/x/y %d/%d/%d/%d\n",\
			p->region.pixelGrabW,p->region.pixelGrabH,\
			p->region.pixelGrabX,p->region.pixelGrabY);
			printk("\t\treal w/h in memory	%d/%d\n",\
			p->region.realPixelGrabW,p->region.realPixelGrabH);
			printk("\t\tcolorspace [%d] (0:yuv,1:rgb)\n",p->region.colorSpace);
			printk("\t\tcolorDepth [%d] (0:8bit,1:10bit)\n",p->region.colorDepth);
			printk("\t\tphy Y8/Y2/C8/C2 [0x%08x/0x%08x/0x%08x/0x%08x] , stride [%d]",\
			p->frameAddr.phyFrameAddrY8,p->frameAddr.phyFrameAddrC8,\
			p->frameAddr.phyFrameAddrY2,p->frameAddr.phyFrameAddrC2,\
			p->frameAddr.stride);
			}break;
		case DE_IOWR_SET_VTM_BLOCK_STATE:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_VCS:
			{LX_DE_VCS_IPC_T *p = (LX_DE_VCS_IPC_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,inx," ");PRINT_FIELD(p,data,"\n");
			}break;
		case DE_IOW_SET_OPERATION:
			{LX_DE_OPERATION_CTRL_T *p = (LX_DE_OPERATION_CTRL_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,win_id," ");PRINT_FIELD(p,operation," ");printk("ONE_WIN(0) TWO_WIN(1) 3D(2) UD(3) VENC(4)\n");
			PRINT_FIELD(p,multiCtrl," ");PRINT_FIELD(p,udCtrl," ");printk("OFF(0) ON(1) HALF(2)\n");
			PRINT_FIELD(p,ctrl3D.run_mode," ");printk("OFF(0) ON(1) 3DTO2D(2) 2DTO3D(3)\n");
			PRINT_FIELD(p,ctrl3D.in_img_fmt," ");printk("TOPNBOTTOM(0) SIDEBYSIDE(1) QUINCUNX(2) CHECKERBOARD(3)\n");
			printk("\t\t\t\t\tFRAMEPACKING(4) FRAMEINTERLACE(5) FIELDALTERNATE(6) FRAMESEQ(7) LINEALTERNATIVE(8) \n");
			printk("\t\t\t\t\tSIDEBYSIDE_FULL(9) DUAL_HD(10) COLUMNALTERNATIVE(11) LINEALTERNATIVE_HALF(12) \n");
			PRINT_FIELD(p,ctrl3D.in_lr_order," ");printk("R_FIRST(0) L_FIRST(1)\n");
			PRINT_FIELD(p,ctrl3D.out_img_fmt," ");printk("SINGLE_2D(0) SINGLE_TB(1) SINGLE_SS(2) SINGLE_FS(3)\n");
			printk("\t\t\t\t\tDUAL_FULL(4) DUAL_TB(5) DUAL_SS(6) SINGLE_LA(7)  \n");
			PRINT_FIELD(p,ctrl3D.out_lr_order," ");printk("R_FIRST(0) L_FIRST(1)\n");
			PRINT_FIELD(p,vencCtrl.bOnOff," ");printk("OFF(0) ON(1)\n");
			PRINT_FIELD(p,vencCtrl.scan," ");printk("INTERLACED(0) PROGRESSIVE(1)\n");
			PRINT_FIELD(p,vencCtrl.hSize," ");PRINT_FIELD(p,vencCtrl.vSize," ");PRINT_FIELD(p,vencCtrl.frRate,"\n");
			}break;
		case DE_IOW_SET_SUB_OPERATION:
			{LX_DE_SUB_OPERATION_CTRL_T *p = (LX_DE_SUB_OPERATION_CTRL_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,win_id," ");PRINT_FIELD(p,operation," ");printk("OFF(0) CAPTURE(1) VENC(2) SCART_OUT(3)\n");
			PRINT_FIELD(p,capture_enable,"\n");
			PRINT_FIELD(p,vencCtrl.bOnOff," ");printk("OFF(0) ON(1)\n");
			PRINT_FIELD(p,vencCtrl.scan," ");printk("INTERLACED(0) PROGRESSIVE(1)\n");
			PRINT_FIELD(p,vencCtrl.hSize," ");PRINT_FIELD(p,vencCtrl.vSize," ");PRINT_FIELD(p,vencCtrl.frRate,"\n");}break;
		default:
			{
				printk("\t\t unimplemented DE History Print \n");
			}
	}
}


static void DE_Pop_MISC_Hist(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOW_SET_DEINTERLACE:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOR_REG_RD:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_REG_WR:
			{LX_DE_REG_WR_T *p = (LX_DE_REG_WR_T *)g_history_buffer[index].p;
			PRINT_FIELD(p,wr_addr," ");PRINT_FIELD(p,wr_data,"\n");
			}break;
		case DE_IOR_GET_DBG:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_DBG:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_UART_FOR_MCU:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_EVAL_DBG:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_SCART_RGB_BYPASS_MODE:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_SUB_SC_FREEZE:
			{
				printk("\t\t unimplemented DE History Print \n");
			}break;
		case DE_IOW_SET_CVI_FREEZE:
			{LX_DE_CVI_CAPTURE_FREEZE_T *p = (LX_DE_CVI_CAPTURE_FREEZE_T *)g_history_buffer[index].p;
			printk("\t\tOn/Off capture [%d] cvifreeze [%d]\n",\
					p->bCaptureOnOff, p->bCviFreezeOnOff);
			}break;
		default:
			{
				printk("\t\t unimplemented DE History Print \n");
			}
	}
}

int DE_Pop_Hist(unsigned int cmd, unsigned int index)
{
	int ret = RET_OK;
	char funcName[NAME_MAX_SIZE];
	int i,j,callindex, ioctlNR=-1;

	callindex = index + g_buf_ovflow_flag*HIST_MAX_NUM;

	printk("\n\t%d) At timestamp : %06d.%06d seconds after Bootup\n\t",callindex, \
								g_history_buffer[index].t.sec, \
								g_history_buffer[index].t.msec*1000 + g_history_buffer[index].t.usec);

	printk("%s Called with Parameters:\n ",g_de_func_list[_IOC_NR(cmd)].s);

	//Find the category of IOCTL then call the respective pop function
	switch(GET_IOCTL_CATEGORY(cmd))
	{
		case DE_SYSTEM_IOCTL:
			{
				DE_Pop_SYSTEM_Hist(cmd,index);
			}break;
		case DE_SRC_IOCTL:
			{
				DE_Pop_SRC_Hist(cmd,index);
			}break;

		case DE_WIN_IOCTL:
			{
				DE_Pop_WIN_Hist(cmd,index);
			}break;
		case DE_OP_IOCTL:
			{
				DE_Pop_OP_Hist(cmd,index);
			}break;
		case DE_CNTL_IOCTL:
			{
				DE_Pop_CNTL_Hist(cmd,index);
			}break;
		case DE_MISC_IOCTL:
			{
				DE_Pop_MISC_Hist(cmd,index);
			}break;
		default:
			{
				printk("\t\t Unknown IOCTL implementation\n");
			}
	}

	return ret;
}

void DE_Populate_Fn_Table(void)
{
	DE_Populate_SYSTEM_Fn();
	DE_Populate_SRC_Fn();
	DE_Populate_WIN_Fn();
	DE_Populate_OP_Fn();
	DE_Populate_MISC_Fn();
	DE_Populate_CNTL_Fn();
}

static void DE_Populate_SYSTEM_Fn(void)
{
	char *str;
	str = "DE_IO_Init";
	g_de_func_list[_IOC_NR(DE_IOW_DE_INIT)].c = DE_IOW_DE_INIT;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_DE_INIT)].s, str, sizeof(str));

	str = "DE_IO_GetFirmwareInfo";
	g_de_func_list[_IOC_NR(DE_IOR_GET_FIRMWARE_INFO)].c = DE_IOR_GET_FIRMWARE_INFO;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_FIRMWARE_INFO)].s, str, sizeof(str));

	str = "DE_IO_FW_Download";
	g_de_func_list[_IOC_NR(DE_IOW_FW_DOWNLOAD)].c = DE_IOW_FW_DOWNLOAD;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_FW_DOWNLOAD)].s, str, sizeof(str));

	str = "DE_IO_SetInterfaceConfig";
	g_de_func_list[_IOC_NR(DE_IOW_SET_IF_CONFIG)].c = DE_IOW_SET_IF_CONFIG;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_IF_CONFIG)].s, str, sizeof(str));

	str = "DE_IO_GetCapacity";
	g_de_func_list[_IOC_NR(DE_IOR_GET_CAPACITY)].c = DE_IOR_GET_CAPACITY;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_CAPACITY)].s, str, sizeof(str));

	str = "DE_IO_SetOutmode";
	g_de_func_list[_IOC_NR(DE_IOW_SET_OUTPUT_MODE)].c = DE_IOW_SET_OUTPUT_MODE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_OUTPUT_MODE)].s, str, sizeof(str));

	str = "DE_IO_SetDisFmt";
	g_de_func_list[_IOC_NR(DE_IOW_SET_DIS_FMT)].c = DE_IOW_SET_DIS_FMT;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_DIS_FMT)].s, str, sizeof(str));

	str = "DE_IO_SetFrRate";
	g_de_func_list[_IOC_NR(DE_IOW_SET_FR_RATE)].c = DE_IOW_SET_FR_RATE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_FR_RATE)].s, str, sizeof(str));

	str = "DE_IO_GetOutFrRate";
	g_de_func_list[_IOC_NR(DE_IOR_GET_OUT_FR_RATE)].c = DE_IOR_GET_OUT_FR_RATE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_OUT_FR_RATE)].s, str, sizeof(str));

	str = "DE_IO_SetDisOut";
	g_de_func_list[_IOC_NR(DE_IOW_SET_DIS_OUT)].c = DE_IOW_SET_DIS_OUT;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_DIS_OUT)].s, str, sizeof(str));

	str = "DE_IO_GetSystemStatus";
	g_de_func_list[_IOC_NR(DE_IOR_GET_SYS_STATUS)].c = DE_IOR_GET_SYS_STATUS;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_SYS_STATUS)].s, str, sizeof(str));

	//Undefined function DE_IO_UnknownFunction
}

static void DE_Populate_SRC_Fn()
{
	char *str;

	str = "DE_IO_SetWinPortSrc";
	g_de_func_list[_IOC_NR(DE_IOW_SET_WIN_PORT_SRC)].c = DE_IOW_SET_WIN_PORT_SRC;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_WIN_PORT_SRC)].s, str, sizeof(str));

	str = "DE_IO_SetCviSrcType";
	g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_SRC_TYPE)].c = DE_IOW_SET_CVI_SRC_TYPE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_SRC_TYPE)].s, str, sizeof(str));

	str = "DE_IO_SetCviFir";
	g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_FIR)].c = DE_IOW_SET_CVI_FIR;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_FIR)].s, str, sizeof(str));

	str = "DE_IO_SetCviCsampleMode";
	g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_CSAMPLE_MODE)].c = DE_IOW_SET_CVI_CSAMPLE_MODE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_CSAMPLE_MODE)].s, str, sizeof(str));

	str = "DE_IO_SetHDMIPort";
	g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_HDMIPORT)].c = DE_IOW_SET_CVI_HDMIPORT;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_HDMIPORT)].s, str, sizeof(str));

	str = "DE_IO_GetSourceStatus";
	g_de_func_list[_IOC_NR(DE_IOR_GET_SRC_STATUS)].c = DE_IOR_GET_SRC_STATUS;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_SRC_STATUS)].s, str, sizeof(str));

	str = "DE_IO_SetSrcMirror";
	g_de_func_list[_IOC_NR(DE_IOW_SET_SRC_MIRROR)].c = DE_IOW_SET_SRC_MIRROR;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_SRC_MIRROR)].s, str, sizeof(str));

//Undefined function DE_IO_UnknownFunction
	str = "DE_IO_UnknownFunction";
	g_de_func_list[_IOC_NR(DE_IOR_GET_MVI_COLORIMETRY)].c = DE_IOR_GET_MVI_COLORIMETRY;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_MVI_COLORIMETRY)].s, str, sizeof(str));

}

static void DE_Populate_CNTL_Fn()
{
	char *str;

	str = "DE_IO_GetLowDelay";
	g_de_func_list[_IOC_NR(DE_IOR_GET_LOW_DELAY)].c = DE_IOR_GET_LOW_DELAY;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_LOW_DELAY)].s, str, sizeof(str));

	str = "DE_IO_SetLowDelay";
	g_de_func_list[_IOC_NR(DE_IOW_SET_LOW_DELAY)].c = DE_IOW_SET_LOW_DELAY;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_LOW_DELAY)].s, str, sizeof(str));

	str = "DE_IO_SetWinFreeze";
	g_de_func_list[_IOC_NR(DE_IOW_SET_WIN_FREEZE)].c = DE_IOW_SET_WIN_FREEZE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_WIN_FREEZE)].s, str, sizeof(str));

	str = "DE_IO_SetActFmtDetect";
	g_de_func_list[_IOC_NR(DE_IOW_SET_ACT_FMT_DETECT)].c = DE_IOW_SET_ACT_FMT_DETECT;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_ACT_FMT_DETECT)].s, str, sizeof(str));

	//Undefined function DE_IO_UnknownFunction
}

static void DE_Populate_WIN_Fn(void)
{
	char *str;

	str = "DE_IO_GetInputWin";
	g_de_func_list[_IOC_NR(DE_IOR_GET_INPUT_WIN)].c = DE_IOR_GET_INPUT_WIN;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_INPUT_WIN)].s, str, sizeof(str));

	str = "DE_IO_GetOutWin";
	g_de_func_list[_IOC_NR(DE_IOR_GET_OUT_WIN)].c = DE_IOR_GET_OUT_WIN;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_OUT_WIN)].s, str, sizeof(str));

	str = "DE_IO_SetInputWin";
	g_de_func_list[_IOC_NR(DE_IOW_SET_INPUT_WIN)].c = DE_IOW_SET_INPUT_WIN;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_INPUT_WIN)].s, str, sizeof(str));

	str = "DE_IO_SetOutWin";
	g_de_func_list[_IOC_NR(DE_IOW_SET_OUT_WIN)].c = DE_IOW_SET_OUT_WIN;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_OUT_WIN)].s, str, sizeof(str));

	str = "DE_IO_SetZList";
	g_de_func_list[_IOC_NR(DE_IOW_SET_ZLIST)].c = DE_IOW_SET_ZLIST;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_ZLIST)].s, str, sizeof(str));

	str = "DE_IO_SetMultiVision";
	g_de_func_list[_IOC_NR(DE_IOW_SET_MULTI_VISION)].c = DE_IOW_SET_MULTI_VISION;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_MULTI_VISION)].s, str, sizeof(str));

	str = "DE_IO_SetWinBlank";
	g_de_func_list[_IOC_NR(DE_IOW_SET_WIN_BLANK)].c = DE_IOW_SET_WIN_BLANK;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_WIN_BLANK)].s, str, sizeof(str));

	str = "DE_IO_SetBgColor";
	g_de_func_list[_IOC_NR(DE_IOW_SET_BG_COLOR)].c = DE_IOW_SET_BG_COLOR;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_BG_COLOR)].s, str, sizeof(str));

	str = "DE_IO_SetInnerPattern";
	g_de_func_list[_IOC_NR(DE_IOW_SET_INNER_PATTERN)].c = DE_IOW_SET_INNER_PATTERN;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_INNER_PATTERN)].s, str, sizeof(str));

	str = "DE_IO_SetCviTpg";
	g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_TPG)].c = DE_IOW_SET_CVI_TPG;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_TPG)].s, str, sizeof(str));

	str = "DE_IO_SetSubWindow";
	g_de_func_list[_IOC_NR(DE_IOW_SET_SUB_WIN)].c = DE_IOW_SET_SUB_WIN;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_SUB_WIN)].s, str, sizeof(str));

	str = "DE_IO_GetOutWinCached";
	g_de_func_list[_IOC_NR(DE_IOR_GET_OUT_WIN_CACHED)].c = DE_IOR_GET_OUT_WIN_CACHED;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_OUT_WIN_CACHED)].s, str, sizeof(str));

	//Undefined function DE_IO_UnknownFunction
}

static void DE_Populate_OP_Fn(void)
{
	char *str;

	str = "DE_IO_Set3DInOutCtrl";
	g_de_func_list[_IOC_NR(DE_IOW_SET_3D_INOUT_CTRL)].c = DE_IOW_SET_3D_INOUT_CTRL;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_3D_INOUT_CTRL)].s, str, sizeof(str));

	str = "DE_IO_SetUDMode";
	g_de_func_list[_IOC_NR(DE_IOW_SET_UD_MODE)].c = DE_IOW_SET_UD_MODE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_UD_MODE)].s, str, sizeof(str));

	str = "DE_IO_MultiWinEnable";
	g_de_func_list[_IOC_NR(DE_IOW_MULTI_WIN_ENABLE)].c = DE_IOW_MULTI_WIN_ENABLE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_MULTI_WIN_ENABLE)].s, str, sizeof(str));

	str = "DE_IO_GetScalerInfo";
	g_de_func_list[_IOC_NR(DE_IOR_GET_SCALER_INFO)].c = DE_IOR_GET_SCALER_INFO;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_SCALER_INFO)].s, str, sizeof(str));

	str = "DE_IO_SetCve";
	g_de_func_list[_IOC_NR(DE_IOW_SET_CVE)].c = DE_IOW_SET_CVE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_CVE)].s, str, sizeof(str));

	str = "DE_IO_SetDvrFmtCtrl";
	g_de_func_list[_IOC_NR(DE_IOW_SET_DVR_FMT_CTRL)].c = DE_IOW_SET_DVR_FMT_CTRL;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_DVR_FMT_CTRL)].s, str, sizeof(str));

	str = "DE_IO_SetVTM";
	g_de_func_list[_IOC_NR(DE_IOW_SET_VTM)].c = DE_IOW_SET_VTM;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_VTM)].s, str, sizeof(str));

	str = "DE_IO_GetVTM";
	g_de_func_list[_IOC_NR(DE_IOR_GET_VTM)].c = DE_IOR_GET_VTM;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_VTM)].s, str, sizeof(str));

	str = "DE_IO_SetCaptureControl";
	g_de_func_list[_IOC_NR(DE_IOW_SET_CAPTURE)].c = DE_IOW_SET_CAPTURE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_CAPTURE)].s, str, sizeof(str));

	str = "DE_IO_SetCviVideoFrameBuffer";
	g_de_func_list[_IOC_NR(DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER)].c = DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER;
	strncpy(g_de_func_list[_IOC_NR(DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER)].s, str, sizeof(str));

	str = "DE_IO_SetVcs";
	g_de_func_list[_IOC_NR(DE_IOW_SET_VCS)].c = DE_IOW_SET_VCS;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_VCS)].s, str, sizeof(str));

	str = "DE_IO_SetOperation";
	g_de_func_list[_IOC_NR(DE_IOW_SET_OPERATION)].c = DE_IOW_SET_OPERATION;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_OPERATION)].s, str, sizeof(str));

	str = "DE_IO_SetSubOperation";
	g_de_func_list[_IOC_NR(DE_IOW_SET_SUB_OPERATION)].c = DE_IOW_SET_SUB_OPERATION;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_SUB_OPERATION)].s, str, sizeof(str));

	//Undefined function DE_IO_UnknownFunction
	str = "DE_IO_UnknownFunction";
	g_de_func_list[_IOC_NR(DE_IOWR_SET_VTM_BLOCK_STATE)].c = DE_IOWR_SET_VTM_BLOCK_STATE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOWR_SET_VTM_BLOCK_STATE)].s, str, sizeof(str));

}

static void DE_Populate_MISC_Fn(void)
{
	char *str;

	str = "DE_IO_RegRd";
	g_de_func_list[_IOC_NR(DE_IOR_REG_RD)].c = DE_IOR_REG_RD;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_REG_RD)].s, str, sizeof(str));

	str = "DE_IO_RegWr";
	g_de_func_list[_IOC_NR(DE_IOW_REG_WR)].c = DE_IOW_REG_WR;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_REG_WR)].s, str, sizeof(str));

	str = "DE_IO_SetUart4MCU";
	g_de_func_list[_IOC_NR(DE_IOW_SET_UART_FOR_MCU)].c = DE_IOW_SET_UART_FOR_MCU;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_UART_FOR_MCU)].s, str, sizeof(str));

	str = "DE_IO_SetCviFreeze";
	g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_FREEZE)].c = DE_IOW_SET_CVI_FREEZE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_CVI_FREEZE)].s, str, sizeof(str));


	//Undefined DE_IO_UnknownFunction
	str = "DE_IO_MultiWinEnable";
	g_de_func_list[_IOC_NR(DE_IOW_SET_DEINTERLACE)].c = DE_IOW_SET_DEINTERLACE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_DEINTERLACE)].s, str, sizeof(str));

	str = "DE_IO_UnknownFunction";
	g_de_func_list[_IOC_NR(DE_IOR_GET_DBG)].c = DE_IOR_GET_DBG;
	strncpy(g_de_func_list[_IOC_NR(DE_IOR_GET_DBG)].s, str, sizeof(str));

	str = "DE_IO_UnknownFunction";
	g_de_func_list[_IOC_NR(DE_IOW_SET_DBG)].c = DE_IOW_SET_DBG;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_DBG)].s, str, sizeof(str));

	str = "DE_IO_UnknownFunction";
	g_de_func_list[_IOC_NR(DE_IOW_SET_EVAL_DBG)].c = DE_IOW_SET_EVAL_DBG;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_EVAL_DBG)].s, str, sizeof(str));

	str = "DE_IO_UnknownFunction";
	g_de_func_list[_IOC_NR(DE_IOW_SET_SCART_RGB_BYPASS_MODE)].c = DE_IOW_SET_SCART_RGB_BYPASS_MODE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_SCART_RGB_BYPASS_MODE)].s, str, sizeof(str));

	str = "DE_IO_UnknownFunction";
	g_de_func_list[_IOC_NR(DE_IOW_SET_SUB_SC_FREEZE)].c = DE_IOW_SET_SUB_SC_FREEZE;
	strncpy(g_de_func_list[_IOC_NR(DE_IOW_SET_SUB_SC_FREEZE)].s, str, sizeof(str));


}
#endif //ENABLE_RESTRCTURED_CODE
#endif //#ifdef USE_HISTORY	

