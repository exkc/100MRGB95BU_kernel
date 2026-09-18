/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file de_cap_kwrap.c
 *
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		dongho7.park (dongho7.park@lge.com)
 *
 *  @version	1.0
 *  @date		2010-02-07
 *  @note		Additional information.
 *
 * 	some functions from de_kwrap.c are moved here by
 * 	srinivasan.shanmugam@lge.com on 2015-04-16
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
//#include "unistd.h"
//#include "osa_kadp.h"
//#include "debug_kadp.h"
#include "de_kwrap.h"
#include "de_kapi.h"
#include "de_kwrap_defs.h"
//#include "libhma.h"
#include "linux/syscalls.h"
#include "de_qkb.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/mm.h>
#include <linux/sched.h>

#ifdef KDRV_CONFIG_PM // added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif

#include "os_util.h"
#include "base_device.h"
#include "de_drv.h"
#include "de_mem.h"

#include "de_model.h"
#include "de_ver_def.h"

#include "de_def.h"
#include "mcu/de_ipc_def.h"
#include "mcu/de_ipc.h"
#include "mcu/de_int.h"
#include "de_io.h"
#include "de_hal.h"

#include "resource_mgr.h"
#include "history_mgr.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define CAP_MODULE_NAME      "/dev/lg/de1"

#define DE_FC_MMAP_HEIGHT_SIZE		1080

#define VTM_VER2
#define MAX_VTM_FRAME_COUNT LX_DE_WIN_MAX
#define GCP_HEADER_COUNT 2
#define GCP_HEADER_ARM2MCU 0
#define GCP_HEADER_MCU2ARM 1
#define DOLBY_WINID_CHECK(_param) {if(_param != LX_DE_WIN_MAIN){DE_ERROR("Window ID not Supported\n"); break;}}
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	SET_INFO_TO_VTM_HEADER = 0,
	GET_INFO_FROM_VTM_HEADER
} p_vtm_meta_info_access_direction;
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
//extern LX_DE_CTX_T		g_de_ctx;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
extern int g_de_kap_logm_fd;
extern int memDev;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
/*static LX_DE_CTX_T		g_cap_ctx =
{
	.dev_fd		= -1,
	.dev_mtx	= NULL,
	.ref_cnt	= 0,
};*/

__attribute__((unused)) static LX_DE_CAPACITY_T g_chip_capa;

struct mem_handle {
	UINT32                  shared_phys;
	LX_DE_VTM_FRAME_INFO_T *shared_virt[MAX_VTM_FRAME_COUNT];
	LX_DE_GCP_INFO_T  *shared_virt_gcp[LX_DE_WIN_MAX];
	int shared_mem_fd;
};

__attribute__((unused)) struct mem_handle mem_handle = {.shared_mem_fd=-1};
__attribute__((unused)) struct mem_handle gcp_mem_handle = {.shared_mem_fd=-1};
__attribute__((unused)) static UINT32 *virt, *virt_gcp;
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
//#define DE_NOTI(fmt, args...) DE_PRINT(fmt,##args);
//#define DE_ERROR(fmt, args...) DE_PRINT(fmt,##args);
/*========================================================================================
	Implementation Group
========================================================================================*/
#if 0	//not used
/**
 *	de debug function as to capture raw image
 *
 */
int de_kwrap_getcapturerawimage(LX_DE_PAR_CAPTURE_RAW_IMAGE_T *capture_info)
{
	int ret = RET_OK;
	LX_DE_PAR_CAPTURE_RAW_IMAGE_T param = {0, };
	UINT32 *pAddress = NULL;
	//static int fd = -1;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);
	do{
		CHECK_NULL(capture_info);

	//	DE_LOCK();
	//	DE_TRACE_BEGIN();

		//if (fd < 0) fd = open("/dev/mem", O_RDONLY, 0777);	// open kernel memory device
		//if (fd > 0) pAddress = (void *)mmap((void *)0, 0x4080000, PROT_READ, MAP_SHARED, fd, 0x819b0000);
		pAddress = (void *)ioremap(0x819b0000,0x4080000);
		param.base_addr = (void *)pAddress;
		param.mode = 0;
		param.size = 0x4080000;

		memcpy(capture_info, &param, sizeof(param));

	//	DE_TRACE_END();
	//	DE_UNLOCK();
	}while(0);
	return ret;
}


/**
 *	Capture video frame.
 *
 */
int de_kwrap_capturevideoframe(LX_DE_CAPTURE_CTRL_T *param)
{
	int ret = RET_OK;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);
	do{
		CHECK_NULL(param);

		//DE_LOCK();
		//DE_TRACE_BEGIN();

		//ret = ioctl(g_de_ctx.dev_fd, DE_IOW_SET_CAPTURE, param);
		ret = resource_mgr_ioctl(DE_IOW_SET_CAPTURE,(unsigned long)param,1);
		DE_CHECK_CODE( ret<0, goto func_exit, "[DE_KWRAP] %s : error in ioctl call.\n", __F__ );


	}while(0);
	func_exit:

		//	DE_TRACE_END();
		//	DE_UNLOCK();

	return ret;
}

int de_kwrap_framecapture(UINT32 isOn, LX_DE_CAPTURE_CTRL_T *param)
{
	int ret = RET_OK;

	return ret;
}

/**
 *	cap device open
 *
 */
int de_kwrap_cap_open(void)
{
	int dev_fd;
	int ret = RET_ERROR;

#ifdef SEE_TV
#else
	KADP_InitSystem(); /* initialize kadp system if necessary */

	do{
		/* if device is already opened, just increase ref_cnt and exit */
		if( g_cap_ctx.dev_fd >= 0 )
		{
			g_cap_ctx.ref_cnt++;
			DE_PRINT("ignore multiple open\n", __F__ );
			return RET_OK;
		}

		dev_fd = open(CAP_MODULE_NAME, O_RDWR);
		if(dev_fd < 0) {DE_PRINT("can't open CAP device (%s)\n", __F__, CAP_MODULE_NAME); break;}
		g_cap_ctx.dev_fd = dev_fd;
		g_cap_ctx.ref_cnt = 1;

		ret = RET_OK;
	}while(0);
#endif
	return ret;
}

/**
 *	cap device check open status
 *
 */
int de_kwrap_cap_isopen(void)
{
#ifdef SEE_TV
	return RET_OK;
#else
	if (g_cap_ctx.dev_fd < 0)
		return	RET_ERROR;
	else
		return	RET_OK;
#endif
}

/**
 *	cap device clode
 *
 */
int de_kwrap_cap_close(void)
{
	int ret = RET_ERROR;

#ifdef SEE_TV
#else
	do{
		/* check DE ref_cnt before closing the real device */
		if ( --g_cap_ctx.ref_cnt > 0 )
		{
			ret = RET_OK;
			break;
		}

		ret = close( g_cap_ctx.dev_fd );
		if(ret<0){DE_PRINT("can't close CAP device (%s)\n", __F__, CAP_MODULE_NAME);break;}

		g_cap_ctx.dev_fd = -1;

		DE_PRINT("device is closed\n" );

		ret = RET_OK;
	}while(0);
#endif
	return ret;
}

/*function only called from debugger. need not port*/

int de_kwrap_cap_capturevideoframe(LX_DE_CAPTURE_CTRL_T *param)
{
	int ret = RET_OK;

	return ret;
}


int de_kwrap_cap_framecapture(UINT32 isOn, LX_DE_CAPTURE_CTRL_T *param)
{
	int ret = RET_ERROR;

	return ret;
}

/*
*
* M16 utilizes 2 VTM header buffer: one for read only (to get status) and another for write only (to set request)
* H15 and previous chips uses only 1 VTM header buffer.
* this private funtion returns proper VTM header index for each chipset.
*/
static UINT32  _get_vtm_shared_header_index(UINT32 chip_id, p_vtm_meta_info_access_direction direction, UINT32 win_id)
{
#if defined(VTM_VER2)
	if(chip_id >= 5) /*M16*/
	{
		if(direction == SET_INFO_TO_VTM_HEADER)
			return (win_id*2);
		else /*VTM_GET*/
			return (win_id*2+1);
	}
	else
#endif
		return win_id;
}

static UINT32  _convert_vtg_rate(UINT32 chip_id, UINT32 rate)
{
#if defined(VTM_VER2)
	if(chip_id >= 5) /*M16*/
	{
		//if(rate>0) rate-=1;
	}
#endif

	return rate;
}

//#define USE_HMA

/**
 *	set information(wid/enable/freeze) for Video frame to Memory.
 *
 */
int de_kwrap_setvtm(LX_DE_VTM_FRAME_INFO_T *param)
{
	int ret = RET_OK;

	return ret;
}

/**
 *	Get information for Video frame to Memory.
 *
 */
int de_kwrap_getvtm(LX_DE_VTM_FRAME_INFO_T *param)
{
	int ret = RET_OK;

	return ret;
}

/**
 *	Get buffer address for Video frame to Memory.
 *
 */
int de_kwrap_getvtmbuffer(LX_DE_VTM_FRAME_INFO_T *param)
{
	int ret = RET_OK;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);
	do{
		CHECK_NULL(param);

		//DE_LOCK();
		//DE_TRACE_BEGIN();

		//ret = ioctl(g_de_ctx.dev_fd, DE_IOW_GET_VTM_BUFFER, param);
		ret = resource_mgr_ioctl(DE_IOW_GET_VTM_BUFFER,(unsigned long)param,1);
		DE_CHECK_CODE( ret<0, goto func_exit, "[DE_KWRAP] %s : error in ioctl call.\n", __F__ );


	}while(0);
func_exit:

		//DE_TRACE_END();
		//DE_UNLOCK();

	return ret;
}

/**
 *	Get frame index for Video frame to Memory.
 *
 */
int de_kwrap_getvtmindex(LX_DE_WIN_ID_T win_id, UINT32 *idx)
{
	int ret = RET_OK;
	UINT32 vtm_header_index;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);
	do{
		CHECK_NULL(idx);

		//DE_LOCK();
		//DE_TRACE_BEGIN();

		if (mem_handle.shared_mem_fd > 0)
		{
			vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, GET_INFO_FROM_VTM_HEADER, (UINT32)win_id);
			*idx = mem_handle.shared_virt[vtm_header_index]->r_idx;
			DE_NOTI(" idx : %d\n", mem_handle.shared_virt[vtm_header_index]->r_idx);
		}
		else
		{
			DE_PRINT(" %s %d  disable VTM status", __F__, __L__);
			ret = RET_ERROR;
		}

		//DE_TRACE_END();
		//DE_UNLOCK();
	}while(0);
	return ret;
}

/**
 *	Get Status info for Video frame to Memory.
 *
 */
int de_kwrap_getvtmstatus(LX_DE_WIN_ID_T win_id, LX_DE_VTM_FRAME_INFO_T *param)
{
	int ret = RET_OK;

	return ret;
}



int de_kwrap_dumpvtmstatusfull(void)
{
	int ret = RET_OK;

	return ret;
}

/**
 *	Set freeze and frame rate for Video frame to Memory.
 *
 */
int de_kwrap_vtmframecontrol(LX_DE_WIN_ID_T win_id, UINT32 read_flag, UINT32 rate)
{
	int ret = RET_OK;


	return ret;
}

/**
 *	Set extention command for Video frame to Memory.
 *
 */
int de_kwrap_cmdvtm(lx_de_vt_ext_cmd_t cmd, lx_de_vt_ext_param_t *p_param)
{
	int ret = RET_OK;
#ifdef _USE_VT_EXTENTION_
	UINT32 win_id = p_param->win_id;
	LX_DE_RECT_T rect = {0, 0, 0, 0};
	LX_DE_VTM_FRAME_INFO_T    *p_shared_org_info;
	LX_DE_VT_EXTENTION_INFO_T *p_shared_ext_info;
	LX_DE_CAPACITY_T chip_capa;
	LX_DE_SRC_STATUS_T src_status;
	UINT32 vtm_header_index;
	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	DE_NOTI("[DE_KWRAP] set vtm extention command  (cmd %d)   shared_mem_fd[%d] win_id[%d].\n", cmd, mem_handle.shared_mem_fd, p_param->win_id);

	if (mem_handle.shared_mem_fd <= 0)
	{
		ret = -1;
		DE_CHECK_CODE( ret<0, goto func_exit, "[DE_KWRAP] %s : invalid shared_mem_fd[%d].\n", __F__, mem_handle.shared_mem_fd );
	}


	//ret = ioctl(g_de_ctx.dev_fd, DE_IOR_GET_CAPACITY, &chip_capa);
	ret = resource_mgr_ioctl(DE_IOR_GET_CAPACITY,(unsigned long)&chip_capa,1);

	src_status.status_type = LX_DE_SRC_STATUS_OPER;
	//ret = ioctl(g_de_ctx.dev_fd, DE_IOR_GET_SRC_STATUS, &src_status);
	ret = resource_mgr_ioctl(DE_IOR_GET_SRC_STATUS,(unsigned long)&src_status,1);

	switch(cmd)
	{
		case VTM_GET_CAPTURE_LOCATION:
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, GET_INFO_FROM_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				switch(chip_capa.vtm_capa.locationLimit)
				{
					case 0:
						p_param->location = 0;
						break;
					case 1:
					default:
						p_param->location = 1;
						break;
					case 2:
						p_param->location = p_shared_ext_info->location;
						break;
				}
			}
			break;
		case VTM_SET_CAPTURE_LOCATION:
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, SET_INFO_TO_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				if(chip_capa.max_out_size.w < 1920)
				{
					ret = RET_ERROR;
					goto func_exit;
				}
				else
				{
					p_shared_ext_info->location = p_param->location;
				}
			}
			break;
		case VTM_GET_OUTPUT_REGION:
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, GET_INFO_FROM_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				p_param->stride                 = p_shared_org_info->stride;
				if(chip_capa.max_out_size.w <= 1920)
				{
					p_param->output_max_region.x    = 0;
					p_param->output_max_region.y    = 0;
					p_param->output_max_region.w    = 960;
					p_param->output_max_region.h    = 540;
					p_param->output_active_region.x = p_shared_org_info->winSize.x;
					p_param->output_active_region.y = p_shared_org_info->winSize.y;
					p_param->output_active_region.w = p_shared_org_info->winSize.w;
					p_param->output_active_region.h = p_shared_org_info->winSize.h;
				}
				else
				{
					p_param->output_max_region.x	= p_shared_ext_info->w_out_size.x;
					p_param->output_max_region.y	= p_shared_ext_info->w_out_size.y;
					p_param->output_max_region.w	= p_shared_ext_info->w_out_size.w;
					p_param->output_max_region.h	= p_shared_ext_info->w_out_size.h;
					p_param->output_active_region.x = p_shared_org_info->winSize.x;
					p_param->output_active_region.y = p_shared_org_info->winSize.y;
					p_param->output_active_region.w = p_shared_org_info->winSize.w;
					if(p_shared_org_info->scan)
						p_param->output_active_region.h = p_shared_org_info->winSize.h;
					else
					{
						if(p_shared_ext_info->location == 0) // source capture
							p_param->output_active_region.h = p_shared_org_info->winSize.h>>1;
						else
							p_param->output_active_region.h = p_shared_org_info->winSize.h;
					}
				}
			}
			break;
		case VTM_SET_OUTPUT_REGION:
			{
				LX_DE_VTM_FRAME_INFO_T param;
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, SET_INFO_TO_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				if(chip_capa.max_out_size.w <= 1920)
				{
					//ret = RET_ERROR;
					//goto func_exit;
					DE_PRINT("[SET_OUTPUT_REGION] This soc supports the fixed output region(960x540).");
				}
				else
				{
					de_kwrap_getvtmbuffer(&param);
					//DE_NOTI("VT buffer base = 0x%08X", param.address);
					p_shared_org_info->y_frame[0] = param.address;

					p_shared_ext_info->w_out_size.x = p_param->output_max_region.x;
					p_shared_ext_info->w_out_size.y = p_param->output_max_region.y;
					p_shared_ext_info->w_out_size.w = p_param->output_max_region.w;
					p_shared_ext_info->w_out_size.h = p_param->output_max_region.h;
					p_shared_ext_info->frc_mode     = p_param->frc_mode;
				}
			}
			break;
		case VTM_SET_INPUT_REGION:
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, SET_INFO_TO_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				if(chip_capa.max_out_size.w <= 1920)
				{
					ret = RET_ERROR;
					goto func_exit;
				}
				else
				{
					p_shared_ext_info->crop_size.x = p_param->input_region.x;
					p_shared_ext_info->crop_size.y = p_param->input_region.y;
					p_shared_ext_info->crop_size.w = p_param->input_region.w;
					p_shared_ext_info->crop_size.h = p_param->input_region.h;
				}
			}
			break;
		case VTM_GET_INPUT_INFO: // original source size
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, GET_INFO_FROM_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				if(chip_capa.max_out_size.w <= 1920)
					p_param->scan       = 1; // progressive
				else
					p_param->scan       = p_shared_org_info->scan;
				p_param->input_region.x = 0;
				p_param->input_region.y = 0;
				p_param->input_region.w = p_shared_org_info->srcSize.w;;
				p_param->input_region.h = p_shared_org_info->srcSize.h;;
				p_param->is3D           = (src_status.operType == LX_DE_OPER_3D)?TRUE:FALSE;
			}
			break;
		case VTM_GET_OUTPUT_INFO:
			{
				ret = de_kwrap_getoutwincached(p_param->win_id, &rect);
				if(ret == RET_ERROR) break;
				p_param->scan                = 1; // progressive
				p_param->output_max_region.x = 0;
				p_param->output_max_region.y = 0;
				p_param->output_max_region.w = 3840;
				p_param->output_max_region.h = 2160;
				p_param->output_active_region.x = rect.x;
				p_param->output_active_region.y = rect.y;
				p_param->output_active_region.w = rect.w;
				p_param->output_active_region.h = rect.h;
			}
			break;
		case VTM_GET_MUTE_STATUS:
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, GET_INFO_FROM_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				p_param->mute_status = p_shared_org_info->mute;
			}
			break;
		case VTM_SET_FREEZE:
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, SET_INFO_TO_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				p_shared_ext_info->frz = (UINT8)p_param->frz;
			}
			break;
		case VTM_SET_RATE:
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, SET_INFO_TO_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				p_shared_ext_info->rate = p_param->rate;
			}
			break;
		case VTM_GET_FREEZE_RATE:
			{
				vtm_header_index = _get_vtm_shared_header_index(g_chip_capa.chip_id, SET_INFO_TO_VTM_HEADER, (UINT32)win_id);
				p_shared_org_info = mem_handle.shared_virt[vtm_header_index];
				p_shared_ext_info = &p_shared_org_info->ext_info;
				p_param->rate = p_shared_ext_info->rate;
				p_param->frz  = p_shared_ext_info->frz;
			}
			break;
		default:
			break;
	}
#if 0
	for(i=0;i<sizeof(LX_DE_VTM_FRAME_INFO_T)>>2;i++)
	{
		UINT32 *p;
		p = (UINT32 *)p_shared_org_info;
		DE_NOTI("shared_virt[%d] :  0x%08x\n", i, p[i]);
	}
#endif
func_exit:

	//DE_TRACE_END();
	//DE_UNLOCK();
#endif
	return ret;
}

int de_kwrap_setvtmblockstate(LX_DE_VTM_BLOCK_STATE_T *pstBlockState)
{
	int ret = RET_OK;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);
	do{
		CHECK_NULL(pstBlockState);

		//DE_LOCK();
		//DE_TRACE_BEGIN();

		//ret = ioctl(g_de_ctx.dev_fd, DE_IOWR_SET_VTM_BLOCK_STATE, pstBlockState);
		ret = resource_mgr_ioctl(DE_IOWR_SET_VTM_BLOCK_STATE,(unsigned long )pstBlockState,1);
		DE_CHECK_CODE( ret<0, goto func_exit, "[DE_KWRAP] %s : error in ioctl call.\n", __F__ );

	}while(0);
func_exit:

		//DE_TRACE_END();
		//DE_UNLOCK();

	return ret;
}
#if 0
// Old dolby function (will be removed.)
int DE_KWRAP_SetDHDRInit(void)
{
	return RET_OK;
}
#endif
/**
 * @callgraph
 * @callergraph
 *
 * @brief Capture video path of general purpose
 * @param
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_setgcpinit(void)
{
	int ret = RET_OK;
	int i;

	gcp_mem_handle.shared_mem_fd = -1;

	for (i=0;i<GCP_HEADER_COUNT;i++)
	{
		gcp_mem_handle.shared_virt_gcp[i] = (LX_DE_GCP_INFO_T *)NULL;
	}

	return ret;
}
#if 0
// Old dolby function (will be removed.)
int DE_KWRAP_SetDHDR(LX_DE_DOLBYHDR_INFO_T *param)
{
	return RET_OK;
}
#endif
/**
 * @callgraph
 * @callergraph
 *
 * @brief Capture video path of general purpose
 * @param
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_setgcp(LX_DE_GCP_INFO_T *param)
{
	int ret = RET_OK;

	return ret;
}
#if 0
// Old dolby function (will be removed.)
int DE_KWRAP_SetDHDRStatus(int dir, LX_DE_DOLBYHDR_INFO_T *param)
{
	return RET_OK;
}
#endif
/**
 * @callgraph
 * @callergraph
 *
 * @brief Capture video path of general purpose
 * @param
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_setgcpstatus(int dir, LX_DE_GCP_INFO_T *param)
{
	if(gcp_mem_handle.shared_mem_fd == -1 || gcp_mem_handle.shared_virt_gcp[GCP_HEADER_ARM2MCU] == NULL)
	{
		//DE_WARN("gcp_mem_handle.shared_mem_fd is invalid.");
		DE_WARN("gcp_mem_handle.shared_mem_fd is invalid. [%d]\n", gcp_mem_handle.shared_mem_fd);
		return -1;
	}
	if(dir == 0)
	{
		memcpy(param, gcp_mem_handle.shared_virt_gcp[GCP_HEADER_ARM2MCU], sizeof(LX_DE_GCP_INFO_T));
	}
	else
	{
		memcpy(gcp_mem_handle.shared_virt_gcp[GCP_HEADER_ARM2MCU], param, sizeof(LX_DE_GCP_INFO_T));
	}
	return 0;
}
#if 0
// Old dolby function (will be removed.)
int DE_KWRAP_GetDHDRStatus(LX_DE_DOLBYHDR_INFO_T *param)
{
	return RET_OK;
}
#endif
/**
 * @callgraph
 * @callergraph
 *
 * @brief Capture video path of general purpose
 * @param
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_getgcpstatus(LX_DE_GCP_INFO_T *param)
{
	LX_DE_GCP_INFO_T *p = gcp_mem_handle.shared_virt_gcp[GCP_HEADER_MCU2ARM];

	if(gcp_mem_handle.shared_mem_fd == -1 || p == NULL)
	{
		return -1;
	}

	memcpy(param, p, sizeof(LX_DE_GCP_INFO_T));
	return 0;
}
#if 0
// Old dolby function (will be removed.)
int DE_KWRAP_WaitDHDRInt(UINT32 *param)
{
	return RET_OK;
}
#endif
/**
 * @callgraph
 * @callergraph
 *
 * @brief Capture video path of general purpose
 * @param
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_waitgcpint(UINT32 *param)
{
	int ret = RET_OK;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);
	do{
		CHECK_NULL(param);

		////DE_LOCK();
		//DE_TRACE_BEGIN();

		//ret = ioctl(g_de_ctx.dev_fd, DE_IOR_GET_DOLBY_HDR_INT, param);
		ret = resource_mgr_ioctl(DE_IOR_GET_DOLBY_HDR_INT,(unsigned long)param,1);
		DE_CHECK_CODE( ret<0, goto func_exit, "[DE_KWRAP] %s : error in ioctl call.\n", __F__ );

	}while(0);
func_exit:

	//DE_TRACE_END();
	////DE_UNLOCK();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief User space API to initialize Dolby HDR IP through ioctl
 *
 * @param ucWinID [IN] UINT8:Window Id
 *
 * @param io_sPtrDolbyInit [OUT]  LX_DOLBY_IO_MAP_T *:Defines OTT,LUT & Frame index DDR physical Address & Size
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripinit(UINT8 i_ucWinID,LX_DOLBY_IO_MAP_T *io_sPtrDolbyInit)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_INIT_T sParam;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);


	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		CHECK_NULL(io_sPtrDolbyInit);
		DOLBY_WINID_CHECK(i_ucWinID);

		sParam.ucWinID = i_ucWinID;
		sParam.sptrDolbyInit = io_sPtrDolbyInit;
		//ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IORW_INIT, &sParam);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IORW_INIT,(unsigned long)&sParam,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : error in ioctl call. %d\n", __F__ ,ret);
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief User space API to Check HDMI DM MetData is ready interrupt occured & reads HDMI DM MetaData from Dolby HDR IP through ioctl
 *
 * @param ucWinID [IN] UINT8:Window Id
 *
 * @param io_eMDType [OUT]  LX_DOLBY_DM_MD_TYPE *:Defines HDMI DM is Big/Lile Endian
 *
 * @param o_sPtrMetaData [OUT]  LX_DOLBY_DM_MD_T *:Defines HDMI DM MetaData & Size
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripgethdmimetadata(UINT8 i_ucWinID,LX_DOLBY_DM_MD_TYPE *io_eMDType,LX_DOLBY_DM_MD_T *o_sPtrMetaData)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_HDMI_MD_T sParam;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

//Note: Removing the lock as it is blocking call
//	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		CHECK_NULL(o_sPtrMetaData);
		//CR:Harish --> WINID check is wrong plz update
		DOLBY_WINID_CHECK(i_ucWinID);

		sParam.ucWinID = i_ucWinID;
		sParam.sptrMetadata = o_sPtrMetaData;
		sParam.eMDType = io_eMDType;

		//ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IOR_HDMI_MD_READ, &sParam);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IOR_HDMI_MD_READ,(unsigned long)&sParam,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : ioctl call returned %d\n", __F__ ,ret);
			break;
		}
	}while(0);

	//DE_TRACE_END();
//	//DE_UNLOCK();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief User space API to Check OTT MetData is ready interrupt occured
 *
 * @param i_ucWindId [IN] UINT8:Window Id
 *
 * @param o_nptrFlag [OUT]  UINT32 *:Defines OTT MetData ready Interrupt occured or not
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripgetottmetadata(UINT8 i_ucWindId,UINT32 *o_nptrFlag)
{
	int ret = RET_ERROR;
	LX_DOLBY_OTT_MD_IOCTL_T sParam;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);
//Note: Removing the lock as it is blocking call
//	DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		//CR:Harish --> WINID check is wrong plz update
		DOLBY_WINID_CHECK(i_ucWindId);

		sParam.ucWinID = i_ucWindId;
		sParam.nptrInfo = o_nptrFlag;

	//	ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IOR_OTT_MD_READ,&sParam);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IOR_OTT_MD_READ,(unsigned long)&sParam,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s :  ioctl call returned  %d\n", __F__ ,ret);
			break;
		}

	}while(0);

	//DE_TRACE_END();
//	DE_UNLOCK();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief User space API to Configure Dolby HDR IP composer & DM
 *
 * @param i_ucWinID [IN] UINT8:Window Id
 *
 * @param o_nptrFlag [OUT]  LX_DOLBY_CONFIG_REG_T *:Defines Composer & DM IP core register values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripsetconfig(UINT8 i_ucWinID,LX_DOLBY_CONFIG_REG_T *i_sPtrDolbyConfigParam)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_CONFIG_REG_T sParam;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {

		CHECK_NULL(i_sPtrDolbyConfigParam);
		DOLBY_WINID_CHECK(i_ucWinID);

		sParam.ucWinID = i_ucWinID;
		sParam.sDolbyConfig = i_sPtrDolbyConfigParam;

		//ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IOW_CONFIG, &sParam);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IOW_CONFIG,(unsigned long)&sParam,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : error in ioctl call. %d\n", __F__ ,ret);
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

int de_kwrap_dhdripgetconfig(UINT8 i_ucWinId,LX_DOLBY_CONFIG_REG_T *o_sPtrDolbyConfigParam)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_CONFIG_REG_T sParam;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);


	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		CHECK_NULL(o_sPtrDolbyConfigParam);
		DOLBY_WINID_CHECK(i_ucWinId);

		sParam.ucWinID = i_ucWinId;
		sParam.sDolbyConfig = o_sPtrDolbyConfigParam;

		//ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IOW_GET_CONFIG, &sParam);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IOW_GET_CONFIG,(unsigned long )&sParam,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : error in ioctl call.\n", __F__ );
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}
/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief User space API to Configure 3D & TC Lut Address
 *
 * @param i_ucWinID [IN] UINT8:Window Id
 *
 * @param i_unFrameNum [IN]  UINT32 *:Defines the frame number
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripsetlutconfig(UINT8 i_ucWinId,UINT32 *i_nptrFrameNum)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_CONFIG_LUT_T sParam;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);


	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		CHECK_NULL(i_nptrFrameNum);
		sParam.ucWinID = i_ucWinId;
		sParam.unFrameNum = *i_nptrFrameNum;

		//ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IOW_LUT_CONFIG, &sParam);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IOW_LUT_CONFIG,(unsigned long)&sParam,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : error in ioctl call. %d\n", __F__ ,ret);
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief User space API to Configure pic init for Dolby HDR IP
 *
 * @param i_ucWinID [IN] UINT8:Window Id
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripstart(UINT8 i_ucWinID)
{
	int ret = RET_ERROR;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		DOLBY_WINID_CHECK(i_ucWinID);

		//ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IOW_START,&i_ucWinID);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IOW_START,(unsigned long)&i_ucWinID,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : error in ioctl call. %d\n", __F__ ,ret);
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief User space API to unblock the interrupt for HDMI & OTT mode while reading MetaData
 *
 * @param i_ucWinID [IN] UINT8:Window Id
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripmdreadunblock(UINT8 i_ucWinID)
{
	int ret = RET_ERROR;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		DOLBY_WINID_CHECK(i_ucWinID);

		//ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IOW_MDREAD_UNBLOCK,&i_ucWinID);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IOW_MDREAD_UNBLOCK,(unsigned long)&i_ucWinID,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : error in ioctl call. %d\n", __F__ ,ret);
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * [Unused function: Kept it for future]
 * @brief User space API to un-initialize Dolby HDR Driver
 *
 * @param i_ucWinID [IN] UINT8:Window Id
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripuninit(UINT8 i_ucWinID)
{
	int ret = RET_ERROR;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		DOLBY_WINID_CHECK(i_ucWinID);

//		ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IORW_UNINIT,&i_ucWinID);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IORW_UNINIT,(unsigned long)&i_ucWinID,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : error in ioctl call. %d\n", __F__ ,ret);
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 * @brief User space API to Configure Dolby HDR HDMI Metadata path
 *
 * @param i_ucWinID [IN] UINT8:Window Id
 *
 * @param o_nptrFlag [OUT]  LX_DOLBY_CONFIG_REG_T *:Defines Composer & DM IP core register values
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int de_kwrap_dhdripsethdmimdpath(UINT8 i_ucWinID,LX_HDR_HDMI_MD_PATH_T e_md_path)
{
	int ret = RET_ERROR;
	LX_DOLBY_IOCTL_MD_PATH_T sParam;

	//CHECK_DEV_FD(g_de_ctx.dev_fd);

	//DE_LOCK();
	//DE_TRACE_BEGIN();

	do {
		DOLBY_WINID_CHECK(i_ucWinID);

		sParam.ucWinID = i_ucWinID;
		sParam.e_md_path = e_md_path;

		//ret = ioctl(g_de_ctx.dev_fd, DE_DHDR_IP_IOW_SET_HDMI_MD_PATH, &sParam);
		ret = resource_mgr_ioctl(DE_DHDR_IP_IOW_SET_HDMI_MD_PATH,(unsigned long)&sParam,1);
		if ( ret < 0 )
		{
			DE_ERROR("[DE_KWRAP] %s : error in ioctl call. %d\n", __F__ ,ret);
			break;
		}
	}while(0);

	//DE_TRACE_END();
	//DE_UNLOCK();

	return ret;
}



#define WINID_VT 0
#define MIN_SRC_WIDTH 320
#define MIX_SRC_HEIGHT 240
#define MAX_SRC_WIDTH 4096
#define MAX_SRC_HEIGHT 2160
#define MAX_CAP_WIDTH  960
#define MAX_CAP_HEIGHT 540
#define DEFAULT_CAP_WIDTH 960
#define DEFAULT_CAP_HEIGHT 540
#define IS_VALID_ADDR(addr)  (addr != ((void *)-1) && addr != 0x0)
/*support 10bit YUV422 only*/
typedef struct {
	unsigned char *physYaddr;
	unsigned char *physCaddr;
	LX_DE_GRAB_COLOR_T	*output;
	int winId;
	int capId;
	int orgSrcWidth;
	int orgSrcHeight;
	int capSrcWidth;
	int capSrcHeight;
	int copyX;
	int copyY;
	int copyWidth;
	int copyHeight;
	int capStride;
}CviSrcCaptureProperty;

static int de_kwrap_srccapturestart(CviSrcCaptureProperty *pProp)
{
	int ret = RET_OK;

	return ret;
}

static int de_kwrap_srccaptureacquire(CviSrcCaptureProperty *pProp)
{
	int ret = RET_OK;

	return ret;
}

static int de_kwrap_srccapturestop(CviSrcCaptureProperty *pProp)
{
	int ret = RET_OK;
	LX_DE_VTM_FRAME_INFO_T	 vtm_param;

	memset(&vtm_param,0x0,sizeof(LX_DE_VTM_FRAME_INFO_T));
	vtm_param.win_id = pProp->capId;
	vtm_param.enable = 0;	/*disable*/
	//vtm_param.address = (UINT32)getpid();
	vtm_param.address = (UINT32)current->pid;
	ret = de_kwrap_setvtm(&vtm_param);

	return ret;
}

static int de_kwrap_srccapturecopypixels(CviSrcCaptureProperty *pProp)
{
	int ret = RET_OK;
	int x,y,w,h;
	int cntx, cnty, bufidx = 0;
	unsigned char *pY=NULL, *pC=NULL;

	//pY = mmap (NULL, pProp->capStride*pProp->capSrcHeight, PROT_READ, MAP_PRIVATE, mem_handle.shared_mem_fd, (off_t)pProp->physYaddr);
	pY = ioremap((unsigned long)pProp->physYaddr,pProp->capStride*pProp->capSrcHeight);
	if(pY == NULL)
	{
		return RET_ERROR;
	}
	//pC = mmap (NULL, pProp->capStride*pProp->capSrcHeight, PROT_READ, MAP_PRIVATE, mem_handle.shared_mem_fd,  (off_t)pProp->physCaddr);
	pC = ioremap((unsigned long)pProp->physCaddr,pProp->capStride*pProp->capSrcHeight);
	if(pC == NULL)
	{
		//munmap (pY , pProp->capStride*pProp->capSrcHeight);
		iounmap(pY);
		return RET_ERROR;
	}

	x = pProp->copyX;
	y = pProp->copyY;
	w = pProp->copyWidth;
	h = pProp->copyHeight;
	bufidx = 0;

	/*downscale capture : if src size is larger than FHD, coordinate shall be recalculated propotional to captured size. */
	if(pProp->orgSrcWidth != pProp->capSrcWidth)
	{
		x = (pProp->capSrcWidth*x)/pProp->orgSrcWidth;
	}
	if(pProp->orgSrcHeight != pProp->capSrcHeight)
	{
		y = (pProp->capSrcHeight*y)/pProp->orgSrcHeight;
	}

	/*currently YUV 422 only*/
	for(cnty = y; cnty < (y+h); cnty++)
	{
		for(cntx = x; cntx < (x+w); cntx++)
		{
			pProp->output[bufidx].pixelGrabY = pY[cnty*pProp->capStride+cntx]<<2;
			pProp->output[bufidx].pixelGrabCb= pC[cnty*pProp->capStride+(cntx-(cntx%2))]<<2;
			pProp->output[bufidx++].pixelGrabCr= pC[cnty*pProp->capStride+(cntx-(cntx%2)+1)]<<2;
		}
	}

	//munmap (pC , pProp->capStride*pProp->capSrcHeight);
	//munmap (pY , pProp->capStride*pProp->capSrcHeight);
	iounmap(pC);
	iounmap(pY);
	return ret;
}

int de_kwrap_getsourcecapturebuffer(LX_DE_CVI_RW_VIDEO_FRAME_T param)
{
	int ret = RET_OK;
	LX_DE_VTM_FRAME_INFO_T	 vtm_param;
	CviSrcCaptureProperty  capProp;

	memset(&capProp, 0x0, sizeof(CviSrcCaptureProperty));
	capProp.winId = param.region.win_id;
	capProp.capId = WINID_VT;
	capProp.orgSrcWidth = param.region.realPixelGrabW;
	capProp.orgSrcHeight = param.region.realPixelGrabH;
	capProp.capSrcWidth = MAX_CAP_WIDTH; //((capProp.capSrcWidth > MAX_CAP_WIDTH) ? MAX_CAP_WIDTH : capProp.orgSrcWidth);
	capProp.capSrcHeight = MAX_CAP_HEIGHT; //((capProp.capSrcHeight > MAX_CAP_HEIGHT) ? MAX_CAP_HEIGHT : capProp.orgSrcHeight);
	capProp.output = param.color;
	capProp.copyX = param.region.pixelGrabX;
	capProp.copyY = param.region.pixelGrabY;
	capProp.copyWidth = param.region.pixelGrabW;
	capProp.copyHeight = param.region.pixelGrabH;

	if(capProp.orgSrcWidth > MAX_SRC_WIDTH || capProp.orgSrcHeight > MAX_SRC_HEIGHT || capProp.orgSrcWidth < MIN_SRC_WIDTH || capProp.orgSrcHeight < MIX_SRC_HEIGHT)
	{
		DE_ERROR(" Unsupported resolution: %dx%d\n", capProp.orgSrcWidth, capProp.orgSrcHeight);
		return RET_ERROR;
	}

	if(capProp.capSrcWidth > MAX_CAP_WIDTH)
	{
		capProp.capSrcWidth = MAX_CAP_WIDTH;
	}

	if(capProp.capSrcHeight > MAX_CAP_HEIGHT)
	{
		capProp.capSrcHeight = MAX_CAP_HEIGHT;
	}

	ret = de_kwrap_srccapturestart(&capProp);
	DE_CHECK_CODE( ret<0, goto func_exit, "[DE_KWRAP] %s : error in line %d.\n", __F__ ,__L__);

	ret = de_kwrap_srccaptureacquire(&capProp);
	DE_CHECK_CODE( ret<0, goto func_exit, "[DE_KWRAP] %s : error in line %d.\n", __F__ ,__L__);


	if(IS_VALID_ADDR(capProp.physYaddr) && IS_VALID_ADDR(capProp.physCaddr) && (mem_handle.shared_mem_fd != -1))
	{
		ret = de_kwrap_srccapturecopypixels(&capProp);
		DE_CHECK_CODE( ret<0, goto func_exit, "[DE_KWRAP] %s : error in line %d.\n", __F__ ,__L__);
	}

func_exit:
	de_kwrap_srccapturestop(&capProp);

	return ret;
}
#endif

