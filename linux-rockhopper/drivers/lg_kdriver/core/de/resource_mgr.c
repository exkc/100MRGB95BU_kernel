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
 *	resource manager implementation for de device.
 *
 *	author
 *	version		1.0
 *	date
 *	note
 *
 *	@addtogroup
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define TEST_IPC_LOGICAL_LAYER

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include "os_util.h"
#include "base_device.h"
#include "resource_mgr.h"
#include "de_def.h"
#include "de_model.h"
#include "de_io.h"
#include "de_cfg.h"
#include "de_sync.h"
#include "de_mem.h"
#include "hal/ipc_hal.h"
#include "mcu/de_dbi.h"
#include "dolby_io.h"
//#include "dolby_int.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define EXECUTE_FUNCTION

#define COPY_FROM_USER(dst,size,nFlag) { \
	if(nFlag == 0) {\
		ret = copy_from_user(&dst, (void __user *)arg, sizeof(size));}\
	else {\
		memcpy(&dst, (void *)arg, sizeof(size)); ret = RET_OK;}}
#define COPY_TO_USER(src,size,nFlag)   { \
	if(nFlag == 0) {\
	ret = copy_to_user(  (void __user *)arg, &src, sizeof(size));\
	if(ret) break;}\
	else \
		memcpy((void *)arg,&src,sizeof(size));}
#define CHECK_PTR(ptr)          \
	if(ptr==NULL){\
		DE_ERROR("===)>   ptr is NULL. at %s line[%d]\n", __F__, __L__); \
		ret = RET_ERROR;break;}
#define EXIT_ERROR() { \
	DE_ERROR("%s [%d] : exit by error\n", __F__, __L__);return RET_ERROR;}

/**
* Mapping to Denc type and frequencies
* and scanlines
*/
unsigned short DE_DENC_FREQ_MAP[]={60,50,50}; //indexs are DE_DENC_FREQ_MAP[LX_DE_CVE_NTSC,LX_DE_CVE_PAL,LX_DE_CVE_SECAM]={60,50,50}
unsigned short DE_DENC_SCANLINES_MAP[]={480,576,576}; //indexs are DE_DENC_FREQ_MAP[LX_DE_CVE_NTSC,LX_DE_CVE_PAL,LX_DE_CVE_SECAM]={60,50,50}

#ifdef EXECUTE_FUNCTION

#define CALL_IO(func) { \
	ret = func(arg,nFlag); \
	__push_ioc_buf(cmd, #func, arg,nFlag);\
	__pop_ioc_buf(0, cmd); }
#define RESUME_IO(func, p,nFlag) { \
	arg = (unsigned long)p;  \
	ret = func(arg,nFlag); \
	if(ret)break; \
	}

#else

#define CALL_IO(func) { \
	ret = __push_ioc_buf(cmd, #func, arg);\
	__pop_ioc_buf(0, cmd); }

//As seen the usage of RESUME_IO if used with-in switch case
//then break will only break the switch. Do break meant to put
//the execution at the end of function????

#define RESUME_IO(func, p,nFlag) { \
	arg = (unsigned long)p;
	}
#endif //#ifndef EXECUTE_FUNCTION
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern int v4l2_vsc_de_init_late(unsigned int flag);
extern int de_test_command(unsigned long arg,unsigned int flag);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _init_manager(void);
static int _uninit_manager(void);
static int _create_device(  int     index,        \
							char    *name,        \
							BOOLEAN active,       \
							LX_DE_IN_SRC_T src);
static int _destroy_device(int index);

static int _ioctl_system(unsigned int cmd, unsigned long arg,unsigned int nFlag);
static int _ioctl_source(unsigned int cmd, unsigned long arg,unsigned int nFlag);
static int _ioctl_window(unsigned int cmd, unsigned long arg,unsigned int nFlag);
static int _ioctl_operation(unsigned int cmd, unsigned long arg,unsigned int nFlag);
static int _ioctl_control(unsigned int cmd, unsigned long arg,unsigned int nFlag);
static int _ioctl_etc(unsigned int cmd, unsigned long arg,unsigned int nFlag);
// static int _ioctl_dolby(unsigned int cmd, unsigned long arg,unsigned int nFlag);
static int _init_ioc_buf(BOOLEAN sel);
static int _thread_handle(void);

static int __operation(		DISP_DEV_TYPE  dev_id,   \
							OPERATION_TYPE opr_type, \
							EXECUTE_CMD    cmd,      \
							void           *param);
static int __control(		DISP_DEV_TYPE    dev_id, \
							DISP_DEV_CONTROL ctrl,   \
							EXECUTE_CMD      cmd,    \
							void             *param);
static int __operation_map( OPERATION_TYPE *p_opr,   \
							OPERATION_TYPE  cur_opr, \
							EXECUTE_CMD     cmd);
static int __source_win_port_map(LX_DE_INPUT_SOURCE_T param);
static int __source_property(LX_DE_CVI_SRC_TYPE_T param);
static int __source_mirror(LX_DE_SRC_MIRROR_T param);
static int __view_device(void);
static int __view_ioctl(void);
static int __view_misc(void);
static int __push_ioc_buf(unsigned int cmd, char *c, unsigned long arg,unsigned int nFlag);
static int __pop_ioc_buf(BOOLEAN dump_all, unsigned int cmd);

static void __pop_WIN_ioc_buf(unsigned int cmd,unsigned int index);
static void __pop_CNTL_ioc_buf(unsigned int cmd,unsigned int index);
static void __pop_OP_ioc_buf(unsigned int cmd,unsigned int index);
static void __pop_MISC_ioc_buf(unsigned int cmd,unsigned int index);
static void __pop_SYSTEM_ioc_buf(unsigned int cmd,unsigned int index);
static void __pop_SRC_ioc_buf(unsigned int cmd,unsigned int index);
static void __free_resource(void *resource);
static void __source_TypeToString(LX_DE_IN_SRC_T srcType,char *srcStr);
static void __operation_TypeToString(OPERATION_TYPE opType,char *opStr);
//static void __device_TypeToString(DISP_DEV_TYPE devType,char *devStr);
static int resource_mgr_resume_dev(void);

static int __test_ipc(UINT32 reset);
static int _test_execute4mcu(void);
static int __test_cmd2mcu(int argc, char* cmd, char* param0,   \
		char* param1, char* param2, char* param3, char* param4,\
		char* param5, char* param6, char* param7);
static int __test_local_mute(void);
static int __test_hdmi_pixel_access(void);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DISPLAY_DEV_T *g_dev[DISP_DEV_MAX];
static SOURCE_INFO_T *g_src[DISP_DEV_MAX];
static SYSTEM_INFO_T *g_sys;
static WINDOW_INFO_T *g_win;
static CMD_PARAM_BUF_T ioc_buf[DE_IOC_MAXNR + 1];
static UINT32 thread_timeout = 1000;


/*========================================================================================
	Implementation Group
========================================================================================*/
int resource_mgr_init(void)
{
	int ret = RET_OK;

	DE_IO_IPC_Init(0);

	_init_manager();
	_init_ioc_buf(TRUE);

	_create_device(DISP_DEV_MAIN,  "main",    TRUE,  LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_SUB_1, "sub1",    FALSE, LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_SUB_2, "sub2",    FALSE, LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_SUB_3, "sub3",    FALSE, LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_VTS,   "vcr",     FALSE, LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_VTV,   "dvr",     FALSE, LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_VTM,   "vtg",     FALSE, LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_VTC,   "capture", FALSE, LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_GRAB,  "grab",    FALSE, LX_DE_IN_SRC_NONE);
	_create_device(DISP_DEV_VTH,   "hdr",     FALSE, LX_DE_IN_SRC_NONE);

	return ret;

}

int resource_mgr_cleanup(void)
{
	int ret = RET_OK;

	de_sync_free();
	DE_IO_IPC_Cleanup(0);

	_destroy_device(DISP_DEV_MAX);
	_uninit_manager();
	_init_ioc_buf(FALSE); //uninit

	return ret;
}

DISPLAY_DEV_T *susp_dev[DISP_DEV_MAX];
SOURCE_INFO_T *susp_src[DISP_DEV_MAX];
SYSTEM_INFO_T *susp_sys;
WINDOW_INFO_T *susp_win;

int resource_mgr_suspend(void)
{
	int ret = RET_OK;
	int i;

	do {
		// kmalloc area is stored to NVMEM.
		// So, data backup is not needed.
		// (step1/step2 :  susp_dev, susp_src, susp_sys, susp_win)
		//
		// step 1. alloc memory for suspending last state of each device
		susp_sys = (SYSTEM_INFO_T *)kmalloc(sizeof(SYSTEM_INFO_T),\
										GFP_KERNEL);
		susp_win = (WINDOW_INFO_T *)kmalloc(sizeof(WINDOW_INFO_T),\
										GFP_KERNEL);
		memset(susp_sys, 0, sizeof(SYSTEM_INFO_T));
		memset(susp_win, 0, sizeof(WINDOW_INFO_T));

		for(i=0;i<DISP_DEV_MAX;i++)
		{
			susp_src[i] = (SOURCE_INFO_T *)kmalloc(sizeof(SOURCE_INFO_T),\
										GFP_KERNEL);
			memset(susp_src[i], 0, sizeof(SOURCE_INFO_T));

			susp_dev[i] = (DISPLAY_DEV_T *)kmalloc(sizeof(DISPLAY_DEV_T),\
										GFP_KERNEL);
			memset(susp_dev[i], 0, sizeof(DISPLAY_DEV_T));
			susp_dev[i]->src = susp_src[i];
			susp_dev[i]->sys = susp_sys;
			susp_dev[i]->win = susp_win;
		}

		// step 2. backup all data
		memcpy(susp_sys, g_sys, sizeof(SYSTEM_INFO_T));
		memcpy(susp_win, g_win, sizeof(WINDOW_INFO_T));
		for(i=0;i<DISP_DEV_MAX;i++)
		{
			memcpy(susp_src[i], g_src[i], sizeof(SOURCE_INFO_T));
			memcpy(susp_dev[i], g_dev[i], sizeof(DISPLAY_DEV_T));
		}
	} while(0);

	return ret;
}

static void __source_TypeToString(LX_DE_IN_SRC_T srcType,char *srcStr)
{
	char *str;
    switch(srcType)
	{
		case LX_DE_IN_SRC_NONE :
			{
				str = "NONE";
			}
			break;
		case LX_DE_IN_SRC_VGA :
			{
            	str = "VGA";
			}
			break;
		case LX_DE_IN_SRC_YPBPR :
			{
            	str = "YPBPR";
			}
			break;
		case LX_DE_IN_SRC_ATV :
			{
            	str = "ATV";
			}
			break;
		case LX_DE_IN_SRC_CVBS :
			{
            	str = "CVBS";
			}
			break;
		case LX_DE_IN_SRC_SCART :
			{
            	str = "NONE";
			}
			break;
		case LX_DE_IN_SRC_HDMI :
			{
            	str = "HDMI";
			}
			break;
		case LX_DE_IN_SRC_MVI :
			{
            	str = "MVI";
			}
			break;
		case LX_DE_IN_SRC_CPU :
			{
            	str = "CPU";
			}
			break;
		case LX_DE_IN_SRC_FB :
			{
            	str = "FB";
			}
			break;
		default :
			{
            	str = "UNDEFINED";
			}
			break;
	}
	if(strlen(str) < DEV_NAME_MAX)
		strncpy(srcStr, str, strlen(str));
}

static void __operation_TypeToString(OPERATION_TYPE opType,char *opStr)
{
	char *str;
    switch(opType)
    {
		case OPER_MODE_NONE :
		case OPER_MODE_2D :
			{
            	str = "2D";
			}break;
		case OPER_MODE_3D :
			{
            	str = "3D";
			}break;
		case OPER_MODE_UD :
			{
            	str = "UD";
			}break;
		case OPER_MODE_PIP :
			{
            	str = "PIP";
			}break;
		case OPER_MODE_MEM :
			{
            	str = "MEM";
			}break;
        default :
			{
            	str = "UNDEFINED";
			}break;
	}
	if(strlen(str) < DEV_NAME_MAX)
		strncpy(opStr, str, strlen(str));
}
#if 0
static void __device_TypeToString(DISP_DEV_TYPE devType,char *devStr)
{
	char *str;
    switch(devType)
    {
		case DISP_DEV_MAIN :
			{
    	    	str = "MAIN";
			}break;
		case DISP_DEV_SUB_1 :
			{
				str = "SUB_1";
			}break;
		case DISP_DEV_SUB_2 :
			{
				str = "SUB_2";
			}break;
		case DISP_DEV_SUB_3 :
			{
				str = "SUB_3";
			}break;
		case DISP_DEV_VTS :
			{
				str = "VCR";
			}break;
		case DISP_DEV_VTV :
			{
				str = "DVR";
			}break;
		case DISP_DEV_VTM :
			{
				str = "VTG";
			}break;
		case DISP_DEV_VTC :
			{
				str = "CAPTURE";
			}break;
        default :
			{
				str = "UNDEFINED";
			}break;
	}
	if(strlen(str) < DEV_NAME_MAX)
		strncpy(devStr, str, strlen(str));
}
#endif
static void __free_resource(void *resource)
{
	if(resource)
		kfree(resource);
}

//Harish: Some problem is there in this RESUME_IO concept
//if some device setting failed then also it will proceed further
//with other devices as the break will only put him out of the
//switch loop??????????????
// break is missing for SUB devices is it ok???????
static int resource_mgr_resume_dev(void)
{
	int ret = RET_OK;
	int i = 0;
	DISPLAY_DEV_T *dev;
	unsigned int flag;
	unsigned long arg;
	UINT32 nFlag = 1;

	// dev state
	for(i=0;i<DISP_DEV_SUB_1;i++) // resume main window only for webos3.0
	{
		dev = g_dev[i];
		if(!dev->active) continue;

		DE_PRINT("dev name : %s\n", dev->name);

		switch(i)
		{
			case DISP_DEV_SUB_1:
			case DISP_DEV_SUB_2:
			case DISP_DEV_SUB_3:
			case DISP_DEV_MAIN:
				{
					LX_DE_INPUT_SOURCE_T param;
					LX_DE_CVI_SRC_TYPE_T cvi_param;

					if (i != DISP_DEV_MAIN) {
						// pip enable
						flag = TRUE;
						RESUME_IO(DE_IO_MultiWinEnable, &flag,nFlag);
					}

					dev->win->blank[i].bEnable = 1;
					dev->win->blank[i].win_id   = 0;
					dev->win->blank[i].isRGB    = 0;
					dev->win->blank[i].win_color.g = 0;
					dev->win->blank[i].win_color.b = 128;
					dev->win->blank[i].win_color.r = 128;
					RESUME_IO(DE_IO_SetWinBlank, &dev->win->blank[i],nFlag);

					// source
					param.srcId = i;
					param.srcType = dev->src->map;
					param.srcPort = dev->src->port;
					param.srcAttr = dev->src->attr;
					RESUME_IO(DE_IO_SetWinPortSrc, &param,nFlag);
					if(param.srcType > LX_DE_IN_SRC_NONE && param.srcType <= LX_DE_IN_SRC_HDMI)
					{
						memcpy((char*)&cvi_param, \
								(char*)&dev->src->type, \
								sizeof(LX_DE_CVI_SRC_TYPE_T));
						RESUME_IO(DE_IO_SetCviSrcType, &cvi_param,nFlag);
					}

					//source size,  in/out window
					RESUME_IO(DE_IO_SetWinInfo,	 &dev->win->win_info[i],nFlag);
					RESUME_IO(DE_IO_SetOrbit,	 &dev->win->orbit_win[i],nFlag);
					RESUME_IO(DE_IO_SetOrbit,	 &dev->win->orbit_mov[i],nFlag);					
				}
				break;
			case DISP_DEV_VTM:
				{
					RESUME_IO(DE_IO_ResetVTM,1,nFlag);
				}
				break;
			default:
				break;
		}
	}

	return ret;
}

int resource_mgr_resume(void)
{
	int ret = RET_OK;
	unsigned long arg;
	int i;
	DISPLAY_DEV_T *dev = NULL;
	UINT32 nFlag = 1;

	do {
		dev = g_dev[0];
		DE_IO_Resume(TRUE);

		// system state
		dev->sys->rate.fr_rate = 60; // initial frame rate
		RESUME_IO(DE_IO_SetFrRate, &dev->sys->rate,nFlag);
		RESUME_IO(DE_IO_SetInterfaceConfig, &dev->sys->if_cfg,nFlag);

		if( resource_mgr_resume_dev() != RET_OK)
			break;

	} while(0);

//Harish::Need to be verify. Placement of DE_IO_RESUME
	DE_IO_Resume(FALSE);

	__free_resource(susp_sys);
	__free_resource(susp_win);

	for(i=0;i<DISP_DEV_MAX;i++)
	{
		__free_resource(susp_src[i]);
		__free_resource(susp_dev[i]);
	}

	if(ret)
		DE_ERROR("resuming is fail.\n");

	return ret;
}

int resource_mgr_probe(void)
{
	int ret = RET_OK;

	return ret;
}

int resource_mgr_remove(void)
{
	int ret = RET_OK;

	return ret;
}

int resource_mgr_ioctl(unsigned int cmd, unsigned long arg, CALL_TYPE_T nFlag)
{
	int ret = RET_OK;

	switch(GET_IOCTL_CATEGORY(cmd))
	{
		case DE_SYSTEM_IOCTL:
			{
				ret = _ioctl_system(cmd, arg,nFlag);
			}break;
		case DE_SRC_IOCTL:
			{
				ret = _ioctl_source(cmd, arg,nFlag);
			}break;

		case DE_CNTL_IOCTL:
			{
				ret = _ioctl_control(cmd, arg,nFlag);
			}break;

		case DE_WIN_IOCTL:
			{
				ret = _ioctl_window(cmd, arg,nFlag);
			}break;
		case DE_OP_IOCTL:
			{
				ret = _ioctl_operation(cmd, arg,nFlag);
			}break;
		case DE_MISC_IOCTL:
			{
				ret = _ioctl_etc(cmd, arg,nFlag);
			}break;
		case DE_DHDR_IP_IOCTL:
			{
				//ret = _ioctl_dolby(cmd,arg,nFlag);
			}break;
		default:
			{
				printk("\t\t Unknown IOCTL implementation\n");
			}
	}

	return ret;
}

DISPLAY_DEV_T* resource_mgr_get_handle(DISP_DEV_TYPE dev)
{
	return g_dev[dev];
}

void resource_mgr_thread(void)
{
	bool frozen;

	set_freezable();

	while (!kthread_freezable_should_stop(&frozen))
	{
		if(frozen)
		{
			printk("++ kthread(%s) wakes up\n",__F__);
		}

		if(thread_timeout) OS_MsecSleep(thread_timeout);
		_thread_handle();
	}
}

static int _thread_handle(void)
{
	int ret = RET_OK;
	SYSTEM_INFO_T *p = g_sys;
	static UINT32 reset = 0;

	do {
		switch(p->thread_handle.type)
		{
			case THREAD_TYPE_MONITOR :
				reset = 1;
				break;
			case THREAD_TYPE_IPC_TEST :
				__test_ipc(reset);
				reset = 0;
				break;
			case THREAD_TYPE_LOCAL_MUTE :
				__test_local_mute();
				break;
			case THREAD_TYPE_HDMI_PIXEL_TEST :
				__test_hdmi_pixel_access();
				break;
			default:
				break;
		}
	} while(0);

	return ret;
}

static int _init_manager(void)
{
	int ret = RET_OK;
	int i;

	// create global source & system & window manager
	for(i=0;i<DISP_DEV_MAX;i++)
	{
		g_src[i] = (SOURCE_INFO_T *)OS_Malloc(sizeof(SOURCE_INFO_T));
		memset(g_src[i], 0, sizeof(SOURCE_INFO_T));
	}
	g_sys = (SYSTEM_INFO_T *)OS_Malloc(sizeof(SYSTEM_INFO_T));
	g_win = (WINDOW_INFO_T *)OS_Malloc(sizeof(WINDOW_INFO_T));
	memset(g_sys, 0, sizeof(SYSTEM_INFO_T));
	memset(g_win, 0, sizeof(WINDOW_INFO_T));

	g_win->order.enable = FALSE; // hw default order (win0-bot,win1-top)
	g_sys->out_en       = TRUE;
	g_sys->initialized  = FALSE;

	return ret;
}

static int _uninit_manager(void)
{
	int ret = RET_OK;
	int i;

	// free system & window manager
	OS_Free(g_sys);
	OS_Free(g_win);
	// free source manager
	for(i=0;i<DISP_DEV_MAX;i++)
	{
		OS_Free(g_src[i]);
	}

	return ret;
}

static int _create_device(  int     index,        \
							char    *name,        \
							BOOLEAN active,       \
							LX_DE_IN_SRC_T src)
{
	int ret = RET_OK;
	DISPLAY_DEV_T *dev = NULL;

	do {
		dev = (DISPLAY_DEV_T *)OS_Malloc(sizeof(DISPLAY_DEV_T));
		memset(dev, 0, sizeof(DISPLAY_DEV_T));

		dev->src = g_src[index];
		dev->sys = g_sys;
		dev->win = g_win;

		strncpy(dev->name, name, DEV_NAME_MAX-1);
		DE_TRACE("@@@ %s   dev[%p]       @@@\n", \
				dev->name, dev);
		dev->active   = active;
		dev->src->map = src;
		dev->opr      = OPER_MODE_2D;

		g_dev[index]  = dev;
	}
	while(0);

	return ret;
}

static int _destroy_device(int index)
{
	int ret = RET_OK;
	int i;

	switch(index)
	{
		case DISP_DEV_MAX:
			for(i=0;i<DISP_DEV_MAX;i++)
			{
				OS_Free(g_dev[i]);
			}
			break;
		default :
			if(index >= DISP_DEV_MAX) break;
			OS_Free(g_dev[index]);
			break;
	}

	return ret;
}

static int _ioctl_system(unsigned int cmd, unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	SYSTEM_INFO_T *p = g_sys;

	DE_TRACE("@@ ##  %s \n", __F__);

	switch(cmd)
	{
		case DE_IOW_DE_INIT:
			if (RET_OK == DE_IO_SupportInitData())
			{
				ret = DE_IO_SetInitData();
			}

			if(!p->initialized)
			{
				// Not use at L18F
				if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) ) 
					break;


				COPY_FROM_USER(p->p_type, LX_DE_PANEL_TYPE_T,nFlag);
				ret = de_sync_init();

				CALL_IO(DE_IO_Init);

				DE_IO_GetDisplayType(&p->disp_type);
				p->initialized = TRUE;

				v4l2_vsc_de_init_late(nFlag);
			}
			break;
		case DE_IOW_FW_DOWNLOAD:
			{
				COPY_FROM_USER(p->fw_dwld, LX_DE_FW_DWLD_T,nFlag);
				CALL_IO(DE_IO_FW_Download);
			}
			break;
		case DE_IOR_GET_FIRMWARE_INFO:
			{
				CALL_IO(DE_IO_GetFirmwareInfo);
				COPY_FROM_USER(p->fw_info, LX_DE_FIRMWARE_INFO_T,nFlag);
			}
			break;
		case DE_IOW_SET_IF_CONFIG:
			{
				COPY_FROM_USER(p->if_cfg, LX_DE_IF_CONFIG_T,nFlag);
				CALL_IO(DE_IO_SetInterfaceConfig);
			}
			break;
		case DE_IOW_SET_OUTPUT_MODE :
			{
				COPY_FROM_USER(p->out_mode, LX_DE_OUTPUT_MODE_T,nFlag);
				ret = RET_OK;//CALL_IO(DE_IO_SetOutmode);
			}
			break;
		case DE_IOW_SET_DIS_FMT:
			{
				COPY_FROM_USER(p->fmt, LX_DE_DIS_FMT_T,nFlag);
				CALL_IO(DE_IO_SetDisFmt);
			}
			break;
		case DE_IOW_SET_FR_RATE:
			{
				COPY_FROM_USER(p->rate, LX_DE_FR_RATE_T,nFlag);
				CALL_IO(DE_IO_SetFrRate);
			}
			break;
		case DE_IOR_GET_OUT_FR_RATE:
			{
				CALL_IO(DE_IO_GetOutFrRate);
				COPY_FROM_USER(p->out_rate, LX_DE_FR_RATE_T,nFlag);
			}
			break;
		case DE_IOW_SET_DIS_OUT:
			{
				COPY_FROM_USER(p->out_en, BOOLEAN,nFlag);
				CALL_IO(DE_IO_SetDisOut);
			}
			break;
		case DE_IOR_GET_SYS_STATUS:
			{
				CALL_IO(DE_IO_GetSystemStatus);
			}
			break;
		case DE_IOR_GET_CAPACITY:
			{
				CALL_IO(DE_IO_GetCapacity);
			}
			break;
		case DE_IOW_SET_HDMITX_INFO:
			{
				CALL_IO(DE_IO_SetHDMITXInfo);
			}
			break;
		case DE_IOR_GET_MEM_INFO:
			{
				CALL_IO(DE_IO_GetMEMInfo);
			}
			break;
		case DE_IOR_GET_TIME_DIFF:
			{
				CALL_IO(DE_IO_GetTimeDiff);
			}
			break;
		case DE_IOR_GET_VIDEO_DELAY_INT:
			{
				CALL_IO(DE_IO_GetVideoDelay);
			}
			break;
		default:
			break;
	}

	return ret;
}

static int _ioctl_window(unsigned int cmd, unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	WINDOW_INFO_T *p = g_win;

//	DE_TRACE("@@ ##  %s \n", __F__);

	switch(cmd)
	{
		case DE_IOW_SET_INPUT_WIN:
			{
				LX_DE_WIN_DIMENSION_T param;
				COPY_FROM_USER(param, LX_DE_WIN_DIMENSION_T,nFlag);
				memcpy(&p->in_win[param.win_id], \
						&param,                  \
						sizeof(LX_DE_WIN_DIMENSION_T));
				CALL_IO(DE_IO_SetInputWin);
			}
			break;
		case DE_IOW_SET_OUT_WIN:
			{
				LX_DE_WIN_DIMENSION_T param;
				COPY_FROM_USER(param, LX_DE_WIN_DIMENSION_T,nFlag);
				memcpy(&p->out_win[param.win_id], \
						&param,                   \
						sizeof(LX_DE_WIN_DIMENSION_T));
				CALL_IO(DE_IO_SetOutWin);
			}
			break;
		case DE_IOR_GET_INPUT_WIN:
			{
				LX_DE_WIN_DIMENSION_T param;
				COPY_FROM_USER(param, LX_DE_WIN_DIMENSION_T,nFlag);
				CALL_IO(DE_IO_GetInputWin);
				COPY_FROM_USER(p->in_win[param.win_id], \
							LX_DE_WIN_DIMENSION_T,nFlag);
			}
			break;
		case DE_IOR_GET_OUT_WIN:
			{
				LX_DE_WIN_DIMENSION_T param;
				COPY_FROM_USER(param, LX_DE_WIN_DIMENSION_T,nFlag);
				CALL_IO(DE_IO_GetOutWin);
				COPY_FROM_USER(p->out_win[param.win_id], \
							LX_DE_WIN_DIMENSION_T,nFlag);
			}
			break;
		case DE_IOR_GET_OUT_WIN_CACHED:
			{
				LX_DE_WIN_DIMENSION_T param;
				COPY_FROM_USER(param, LX_DE_WIN_DIMENSION_T,nFlag);
				COPY_TO_USER(p->out_win[param.win_id], \
							LX_DE_WIN_DIMENSION_T,nFlag);
			}
			break;
		case DE_IOW_SET_WIN_INFO:
			{
				LX_DE_WIN_INFO_T param;
				COPY_FROM_USER(param, LX_DE_WIN_INFO_T,nFlag);
				memcpy(&p->win_info[param.wId], \
						&param,                   \
						sizeof(LX_DE_WIN_INFO_T));
				CALL_IO(DE_IO_SetWinInfo);
			}
			break;
		case DE_IOW_SET_ORBIT:
			{
				LX_DE_ORBIT_T param;
				COPY_FROM_USER(param, LX_DE_ORBIT_T,nFlag);
				if(param.type == 0) { // window
					memcpy(&p->orbit_win[param.wId], \
					&param,                   \
					sizeof(LX_DE_ORBIT_T));
				}
				else if(param.type == 1) { // move
					memcpy(&p->orbit_mov[param.wId], \
					&param, 				  \
					sizeof(LX_DE_ORBIT_T));
				}
				CALL_IO(DE_IO_SetOrbit);
			}
			break;
		case DE_IOR_GET_WIN_INFO:
			{
				LX_DE_WIN_INFO_T param;
				COPY_FROM_USER(param, LX_DE_WIN_INFO_T,nFlag);
				if(param.wId > LX_DE_WIN_3)
				{
					ret = RET_ERROR;
					break;
				}
				CALL_IO(DE_IO_GetWinInfo);
				COPY_FROM_USER(p->win_info[param.wId], LX_DE_WIN_INFO_T,nFlag);
			}
			break;
		case DE_IOW_SET_WIN_BLANK:
			{
				LX_DE_SET_WIN_BLANK_T param;
				COPY_FROM_USER(param, LX_DE_SET_WIN_BLANK_T,nFlag);
				if(param.win_id < (LX_DE_WIN_ID_T)DISP_DEV_MAX)
				{
					memcpy(&p->blank[param.win_id], \
							&param,                 \
							sizeof(LX_DE_SET_WIN_BLANK_T));
				}
				CALL_IO(DE_IO_SetWinBlank);
			}
			break;
		case DE_IOW_SET_ZLIST:
			{
				LX_DE_ZLIST_T param;
				COPY_FROM_USER(param, LX_DE_ZLIST_T,nFlag);
				memcpy(&p->order, \
						&param,   \
						sizeof(LX_DE_ZLIST_T));
				CALL_IO(DE_IO_SetZList);
			}
			break;
		case DE_IOW_SET_MULTI_VISION:
			{
				LX_DE_RECT_T param;
				COPY_FROM_USER(param, LX_DE_RECT_T,nFlag);
				memcpy(&p->multi_vision, \
						&param,          \
						sizeof(LX_DE_RECT_T));
				CALL_IO(DE_IO_SetMultiVision);
			}
			break;
		case DE_IOW_SET_BG_COLOR:
			{
				LX_DE_COLOR_T param;
				COPY_FROM_USER(param, LX_DE_COLOR_T,nFlag);
				memcpy(&p->bg_color, \
						&param,      \
						sizeof(LX_DE_COLOR_T));
				CALL_IO(DE_IO_SetBgColor);
			}
			break;
		case DE_IOW_SET_INNER_PATTERN:
			{
				LX_DE_INNER_PATTERN_T param;
				COPY_FROM_USER(param, LX_DE_INNER_PATTERN_T,nFlag);
				memcpy(&p->inner_pattern, \
						&param,      \
						sizeof(LX_DE_INNER_PATTERN_T));
				CALL_IO(DE_IO_SetInnerPattern);
			}
			break;
		case DE_IOW_SET_CVI_TPG:
			{
				LX_DE_CVI_TPG_T param;
				COPY_FROM_USER(param, LX_DE_CVI_TPG_T,nFlag);
				memcpy(&p->cvi_tpg,  \
						&param,      \
						sizeof(LX_DE_CVI_TPG_T));
				CALL_IO(DE_IO_SetCviTpg);
			}
			break;
		case DE_IOW_SET_SUB_WIN:
			{
				COPY_FROM_USER(p->sub_win, LX_DE_SET_SUB_WIN_T,nFlag);
				CALL_IO(DE_IO_SetSubWindow);
			}
			break;
		case DE_IOW_SET_SUB_MODE:
			{
				COPY_FROM_USER(p->sub_mode, LX_DE_SUB_MODE_T,nFlag);
				CALL_IO(DE_IO_SetSubMode);
			}
			break;
		case DE_IOW_GET_SUB_MODE:
			{			
				COPY_TO_USER(p->sub_mode, LX_DE_SUB_MODE_T,nFlag);
			}
			break;			
		case DE_IOW_SET_SUB_SHAPE:
			{
				COPY_FROM_USER(p->sub_shape, LX_DE_SUB_SHAPE_T,nFlag);
				CALL_IO(DE_IO_SetSubShape);
			}
			break;
		case DE_IOW_SET_SRC_SIZE:
			{
				LX_DE_SOURCE_SIZE_WIN_T param;
				COPY_FROM_USER(param, LX_DE_SOURCE_SIZE_WIN_T,nFlag);
				if(param.win_id > LX_DE_WIN_MAX)
					break;
				COPY_FROM_USER(p->src_size_win[param.win_id], LX_DE_SOURCE_SIZE_WIN_T,nFlag);
				CALL_IO(DE_IO_SetSourceSizeWin);
				//DE_NOTI("SET_SRC_SIZE : [%d] w/h = %d/%d\n", param.win_id, p->src_size_win[param.win_id].inSize.w, p->src_size_win[param.win_id].inSize.h);
			}
			break;	
		case DE_IOR_GET_SRC_SIZE:
			{
				LX_DE_SOURCE_SIZE_WIN_T param;
				COPY_FROM_USER(param, LX_DE_SOURCE_SIZE_WIN_T,nFlag);
				if(param.win_id > LX_DE_WIN_MAX)
					break;
				COPY_TO_USER(p->src_size_win[param.win_id], LX_DE_SOURCE_SIZE_WIN_T,nFlag);
				//DE_NOTI("GET_SRC_SIZE : [%d] w/h = %d/%d\n", param.win_id, p->src_size_win[param.win_id].inSize.w, p->src_size_win[param.win_id].inSize.h);
			}
			break;
		default:
			break;
	}

	return ret;
}

static int _ioctl_source(unsigned int cmd, unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;

//	DE_TRACE("@@ ##  %s \n", __F__);

	switch(cmd)
	{
		case DE_IOW_SET_CVI_SRC_TYPE:
			{
				LX_DE_CVI_SRC_TYPE_T param;
				COPY_FROM_USER(param, LX_DE_CVI_SRC_TYPE_T,nFlag);
				ret = __source_property(param);
				CALL_IO(DE_IO_SetCviSrcType);
			}
			break;
		case DE_IOW_SET_CVI_FIR:
			{
				LX_DE_CVI_FIR_T param;
				COPY_FROM_USER(param, LX_DE_CVI_FIR_T,nFlag);
				//ret = __source_property(param);
				CALL_IO(DE_IO_SetCviFir);
			}
			break;
		case DE_IOW_SET_CVI_CSAMPLE_MODE:
			{
				LX_DE_CSAMPLE_MODE_T param;
				COPY_FROM_USER(param, LX_DE_CSAMPLE_MODE_T,nFlag);
				//ret = __source_property(param);
				CALL_IO(DE_IO_SetCviCsampleMode);
			}
			break;
		case DE_IOW_SET_WIN_PORT_SRC:
			{
				LX_DE_INPUT_SOURCE_T param;
				COPY_FROM_USER(param, LX_DE_INPUT_SOURCE_T,nFlag);
				if(param.srcId > 8/*LX_DE_WIN_3*/)
				{
					ret = RET_ERROR;
					break;
				}
				ret = __source_win_port_map(param);
				CALL_IO(DE_IO_SetWinPortSrc);
			}
			break;
		case DE_IOR_GET_SRC_STATUS:
			{
				CALL_IO(DE_IO_GetSourceStatus);
			}
			break;
		case DE_IOW_SET_CVI_HDMIPORT:
			{
				LX_DE_HDMIPORT_T param;
				COPY_FROM_USER(param, LX_DE_HDMIPORT_T,nFlag);
				CALL_IO(DE_IO_SetHDMIPort);
			}
			break;
		case DE_IOW_SET_SRC_MIRROR:
			{
				LX_DE_SRC_MIRROR_T param;
				COPY_FROM_USER(param, LX_DE_SRC_MIRROR_T,nFlag);
				ret = __source_mirror(param);
				CALL_IO(DE_IO_SetSrcMirror);
			}
			break;
		default:
			break;
	}

	return ret;
}

static int _ioctl_control(unsigned int cmd, unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;

	switch(cmd)
	{
		case DE_IOW_SET_LOW_DELAY:
			{
				UINT32 param;
				COPY_FROM_USER(param, UINT32,nFlag);
				ret = __control(DISP_DEV_MAIN,           \
									DEV_CONTROL_LOW_DLY, \
									EXEC_CMD_RUN,        \
									(void *)&param);
				CALL_IO(DE_IO_SetLowDelay);
				break;
			}
		case DE_IOR_GET_LOW_DELAY:
			{
				// DE_IO_GetLowDelay(arg);
				CALL_IO(DE_IO_GetLowDelay);
			}
			break;
		case DE_IOW_SET_WIN_FREEZE:
			{
				LX_DE_WIN_FREEZE_T param;
				COPY_FROM_USER(param, LX_DE_WIN_FREEZE_T,nFlag);
				if(param.win_id > LX_DE_WIN_3)
				{
					ret = RET_ERROR;
					break;
				}
				ret = __control((DISP_DEV_TYPE)param.win_id,    \
									DEV_CONTROL_FRZ,            \
									(param.bEnable == FALSE) ?  \
									EXEC_CMD_OFF : EXEC_CMD_RUN,\
									(void *)&param);
				CALL_IO(DE_IO_SetWinFreeze);
			}
			break;
		case DE_IOW_SET_ACT_FMT_DETECT:
			{
				LX_DE_ACT_FORMAT_T param;
				COPY_FROM_USER(param, LX_DE_ACT_FORMAT_T,nFlag);
				ret = __control(DISP_DEV_MAIN,                  \
									DEV_CONTROL_ACT_FMT,        \
									(param.enable == FALSE) ?   \
									EXEC_CMD_OFF : EXEC_CMD_RUN,\
									(void *)&param);
				CALL_IO(DE_IO_SetActFmtDetect);
			}
			break;
		case DE_IOW_SET_FRAME_DELAY:
			{
				LX_DE_SET_DELAY_BUFFER_T param;
				COPY_FROM_USER(param, LX_DE_SET_DELAY_BUFFER_T,nFlag);
				CALL_IO(DE_IO_SetFrameDelay);
			}
			break;
		case DE_IOW_SET_ROTATE:
			{
				LX_DE_ROTATE_INFO_T param;
				COPY_FROM_USER(param, LX_DE_ROTATE_INFO_T,nFlag);
				CALL_IO(DE_IO_SetRotate);
			}
			break;		
		case DE_IOW_SET_PATTERN:
			{
				CALL_IO(DE_IO_SetTestPattern);
			}
			break;
		case DE_IOW_SET_LATENCY_MEASURE:
			{
				CALL_IO(DE_IO_SetLatencyMeasure);
			}
			break;
		case DE_IOW_SET_ORBIT:
			{
				CALL_IO(DE_IO_SetOrbit);
			}
			break;
		case DE_IOW_SET_SCAN_MODE:
			{
				CALL_IO(DE_IO_SetScanMode);
			}
			break;
		case DE_IOW_SET_PIXELTOPIXEL:
			{
				CALL_IO(DE_IO_SetPixelToPixel);
			}
			break;

		default:
			break;
	}

	return ret;
}

static int _ioctl_operation(unsigned int cmd, unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;

//	DE_TRACE("@@ ##  %s  cmd = %d\n", __F__, cmd & 0xFF);

	switch(cmd)
	{
		case DE_IOW_SET_3D_INOUT_CTRL:  // 3D
			{
				LX_DE_3D_INOUT_CTRL_T param;
				COPY_FROM_USER(param, LX_DE_3D_INOUT_CTRL_T,nFlag);
				/*for now, 3D commad accepted when main window is on(connected)*/
				if(g_dev[0]!=NULL && g_dev[0]->src != NULL && g_dev[0]->src->map != 0 && g_dev[DISP_DEV_VTH]->active == 0)
				{
					ret = __operation(DISP_DEV_MAIN,                      \
								OPER_MODE_3D,                             \
								!(param.run_mode && LX_DE_3D_RUNMODE_OFF), \
								(void *)&param);

					CALL_IO(DE_IO_Set3DInOutCtrl);
				}
			}
			break;
		case DE_IOW_SET_UD_MODE:        // UD
			{
				BOOLEAN param;
				COPY_FROM_USER(param, BOOLEAN,nFlag);
				ret = __operation(DISP_DEV_MAIN,                    \
									OPER_MODE_UD,                   \
									param,      					\
									(void *)NULL);
				CALL_IO(DE_IO_SetUDMode);
			}
			break;
		case DE_IOW_MULTI_WIN_ENABLE:   // PIP
			{
				BOOLEAN param;
				COPY_FROM_USER(param, BOOLEAN,nFlag);
				ret = __operation(DISP_DEV_SUB_1,                     \
									OPER_MODE_PIP,                    \
									param,							  \
									(void *)NULL);
				CALL_IO(DE_IO_MultiWinEnable);
			}
			break;
		case DE_IOW_SET_CVE:
			{
				LX_DE_CVE_PARAM_T param;
				COPY_FROM_USER(param, LX_DE_CVE_PARAM_T,nFlag);
				ret = __operation(DISP_DEV_VTS,                       \
									OPER_MODE_MEM,                    \
									EXEC_CMD_RUN,                     \
									(void *)&param);
				CALL_IO(DE_IO_SetCve);
			}
			break;
		case DE_IOW_SET_DVR_FMT_CTRL:
			{
				LX_DE_DVR_DISFMT_T param;
				COPY_FROM_USER(param, LX_DE_DVR_DISFMT_T,nFlag);
				ret = __operation(DISP_DEV_VTV,                       \
									OPER_MODE_MEM,                    \
									(EXECUTE_CMD)param.bOnOff,         \
									(void *)&param);
				CALL_IO(DE_IO_SetDvrFmtCtrl);
			}
			break;
		case DE_IOW_SET_VTM:
			{
				LX_DE_VTM_FRAME_INFO_T param;
				COPY_FROM_USER(param, LX_DE_VTM_FRAME_INFO_T,nFlag);
				ret = __operation(DISP_DEV_VTM,                       \
									OPER_MODE_MEM,                    \
									param.enable,
									(void *)&param);
				CALL_IO(DE_IO_SetVTM);
				COPY_FROM_USER(param, LX_DE_VTM_FRAME_INFO_T,nFlag);
				param.mem_fd = de_mem_fd();
				COPY_TO_USER(param, LX_DE_VTM_FRAME_INFO_T,nFlag);
			}
			break;
		case DE_IOW_GET_FPP_INFO:
			{
				CALL_IO(DE_IO_GetFPPInfo);
			}
			break;
		case DE_IOW_SET_CVI_FREEZE:
			{
				LX_DE_CVI_CAPTURE_FREEZE_T param;
				COPY_FROM_USER(param, LX_DE_CVI_CAPTURE_FREEZE_T,nFlag);
				CALL_IO(DE_IO_SetCviFreeze);
			}
			break;
		case DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER:
			{
				LX_DE_CVI_RW_VIDEO_FRAME_T param;
				COPY_FROM_USER(param, LX_DE_CVI_RW_VIDEO_FRAME_T,nFlag);
				ret = __operation(DISP_DEV_GRAB,                      \
									OPER_MODE_MEM,                    \
									EXEC_CMD_ONESHOT,                 \
									(void *)&param);
				CALL_IO(DE_IO_SetCviVideoFrameBuffer);
			}
			break;
		case DE_IOR_GET_VTM:
			{
				LX_DE_VTM_FRAME_INFO_T param;
				COPY_FROM_USER(param, LX_DE_VTM_FRAME_INFO_T,nFlag);
				if(param.win_id == 0)
					de_sync_wait(SYNC_WAIT_WEL);
				else if(param.win_id == 1)
					de_sync_wait(SYNC_WAIT_WER);
				else{}
			}
			break;
		case DE_IOW_GET_VTM_BUFFER:
			{
				LX_DE_VTM_FRAME_INFO_T param;
				COPY_FROM_USER(param, LX_DE_VTM_FRAME_INFO_T,nFlag);
				CALL_IO(DE_IO_GetVTM);
			}
			break;
		case DE_IOR_GET_SCALER_INFO:// for emp csc converter(YC->ARGB)
				CALL_IO(DE_IO_GetScalerInfo);
			break;
		case DE_IOW_SET_CAPTURE:
			{
//remove legacy code(20190311)
			}
			break;
		case DE_IOW_GPSDMA_START:
			{
				LX_DE_GPSDMA_PARAM_T param;
				COPY_FROM_USER(param, LX_DE_GPSDMA_PARAM_T,nFlag);
				CALL_IO(DE_IO_UserSetGPSDMA);
			} break;
		case DE_IOW_SET_VCS:
			{
				LX_DE_VCS_IPC_T param;
				COPY_FROM_USER(param, LX_DE_VCS_IPC_T,nFlag);
				CALL_IO(DE_IO_SetVcs);
			} break;
		case DE_IOW_SET_OPERATION :
			{
				CALL_IO(DE_IO_SetOperation);
			} break;
		case DE_IOW_SET_SUB_OPERATION :
			{
				CALL_IO(DE_IO_SetSubOperation);
			} break;
		case DE_IOWR_SET_VTM_BLOCK_STATE :
			{
				CALL_IO(DE_IO_SetVTMBlockState);
			} break;
		case DE_IOW_SET_SIGNAGE_MODE :
			{
				CALL_IO(DE_IO_SetSignageMode);
			} break;
		case DE_IOR_GET_GCP_INT:
			{
				de_sync_wait(SYNC_WAIT_USB);
			}
			break;
		case DE_IOW_SET_GCP_MODE:
			{
				LX_DE_GCP_INFO_T param;
				COPY_FROM_USER(param, LX_DE_GCP_INFO_T,nFlag);
				ret = __operation(DISP_DEV_VTH,             \
								OPER_MODE_MEM,              \
								param.enable == TRUE ? EXEC_CMD_RUN : EXEC_CMD_OFF,	\
								(void *)&param);
				CALL_IO(DE_IO_SetGeneralCapturePath);
			} break;
		case DE_IOW_DUAL_MODE_ENABLE:
			{
				CALL_IO(DE_IO_DualModeEnable);
			} break;
		case DE_IOW_SET_SRC_SYNC_LOW_DELAY:
			{
				CALL_IO(DE_IO_SetLowDelayBySourceSync);
			} break;
		case DE_IOW_SET_HIGH_FRAME_RATE:
			{
				CALL_IO(DE_IO_SetHighFrameRate);
			} break;
		default:
			break;
	}

	return ret;
}

static int _ioctl_etc(unsigned int cmd, unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;

	DE_TRACE("@@ ##  %s \n", __F__);

	switch(cmd)
	{
		case DE_IOW_REG_WR:
			{
				CALL_IO(DE_IO_RegWr);
			}
			break;
		case DE_IOR_REG_RD:
			{
				CALL_IO(DE_IO_RegRd);
			}
			break;
		case DE_IOW_SET_UART_FOR_MCU:
			{
				CALL_IO(DE_IO_SetUart4MCU);
			}
			break;
		case DE_IOW_SET_EVAL_DBG :
			{
				LX_DE_SET_EVAL_DBG_T param;
				COPY_FROM_USER(param, LX_DE_SET_EVAL_DBG_T,nFlag);
				switch (param.cmd)
				{
					case LX_DE_EVAL_CMD_DBI :
					{
						ret = DBI_VIDEO_Execute(param.arg.argc,\
												param.arg.argv);
					}
					break;
					default :
						break;
				}
			}
			break;
		case DE_IOW_IPC_SET_HDR_MODE:
			{
				ret = DE_IO_SetIPCHDRMode(arg,nFlag);
			}
			break;
		case DE_IOWR_TEST_CMD:
			{
				ret = de_test_command(arg,nFlag);
			}
			break;
		case DE_IOW_SET_DBG:
			{
				LX_DE_SET_DBG_T param;
				COPY_FROM_USER(param, LX_DE_SET_DBG_T,nFlag);

				if(param.type == LX_DE_DBG_SET_PATTERN)
				{
					DE_IO_SetTestPattern(arg,nFlag);
				}
				else if(param.type == LX_DE_DBG_SET_LATENCY_MEASURE)
				{
					DE_IO_SetLatencyMeasure(arg,nFlag);
				}
				else if(param.type == LX_DE_DBG_DEVICE_STATUS)
				{
					__view_device();
				}
				else if(param.type == LX_DE_DBG_TRACE_IOCTL)
				{
					__view_ioctl();
				}
				else if(param.type == LX_DE_DBG_MISC_DATA)
				{
#ifdef TEST_IPC_LOGICAL_LAYER
					struct ipc_handle *ipc_handle;
					LX_DE_WIN_FREEZE_T stParams;
					LX_DE_FIRMWARE_INFO_T fw_info;
					UINT32 ipcCmd = 0x53;

					DE_PRINT("ipc logical layer test\n");

					ipc_handle = ipc_hal_open("de", 0); // MCU_ID = 0
					DE_PRINT("mcu ipc is open. handle = 0x%08x\n", \
														(UINT32)ipc_handle);
					stParams.win_id = 0;
					stParams.bEnable = 1;
					stParams.location = 0;
					ret = ipc_handle->m_ipc_client->write(ipcCmd,   \
							&stParams,\
							sizeof(LX_DE_WIN_FREEZE_T));
					ipcCmd = 0x2;
					ret = ipc_handle->m_ipc_client->write(ipcCmd,   \
							&fw_info,\
							0);
					ret = ipc_handle->m_ipc_client->read(&fw_info,\
							sizeof(LX_DE_FIRMWARE_INFO_T));
					DE_PRINT("Fw. info.  : ver %d , y/m/d %04d/%02d/%02d\n",\
							fw_info.version,   \
							fw_info.date.year, \
							fw_info.date.month,\
							fw_info.date.day);
					ipc_hal_close(ipc_handle);
#endif
					__view_misc();
					ipc_hal_list();
				}
				else if(param.type == LX_DE_DBG_IPC_TEST)
				{
					SYSTEM_INFO_T *p = g_sys;
					p->thread_handle.type   = (param.bParam==TRUE) ? \
											  THREAD_TYPE_IPC_TEST : \
											  THREAD_TYPE_MONITOR;
					p->thread_handle.enable = param.bParam;
					p->thread_handle.param  = param.u32Param;
					if(p->thread_handle.type == THREAD_TYPE_MONITOR)
						thread_timeout = 30;
					else if(p->thread_handle.type == THREAD_TYPE_IPC_TEST)
						thread_timeout = 0;
					DE_PRINT("IPC_TEST : enable [%d] , count [%d]\n",\
							param.bParam, param.u32Param);
				}
				else if(param.type == LX_DE_DBG_VERIFY_FW)
				{
					DE_IO_VerifyFirmware(arg,nFlag);
				}
				else if(param.type == LX_DE_DBG_TRACE_IPC)
				{
					ipc_hal_trace(param.bParam);
				}
				else if(param.type == LX_DE_DBG_RESUME_TEST)
				{
					resource_mgr_suspend();
					//resource_mgr_resume();
				}
				else if(param.type == LX_DE_DBG_UHD_SETUP)
				{
					_test_execute4mcu();
				}
				else if(param.type == LX_DE_DBG_LOCAL_MUTE_TIME)
				{
					SYSTEM_INFO_T *p = g_sys;
					p->thread_handle.type   = (param.bParam==TRUE) ? \
											  THREAD_TYPE_LOCAL_MUTE : \
											  THREAD_TYPE_MONITOR;
					p->thread_handle.enable = param.bParam;
					p->thread_handle.param  = param.u32Param;
					if(param.bParam == FALSE)
						thread_timeout = 30;
					else
						thread_timeout = 1;
					DE_PRINT("Start monitor for local mute...\n");
				}
				else if(param.type == LX_DE_DBG_TEST_HDMI_PIXEL_DELAY)
				{
					SYSTEM_INFO_T *p = g_sys;
					if(param.bParam == FALSE)
					{
						thread_timeout = 30;
						p->thread_handle.type = THREAD_TYPE_MONITOR;
					}
					else
					{
						thread_timeout = 0;
						p->thread_handle.type = THREAD_TYPE_HDMI_PIXEL_TEST;
					}
					DE_PRINT("Test HDMI pixel delay with accessing CCO/DPE/...   on/off[%d]\n", param.bParam);
				}	
				else if(param.type == 1) //LX_DE_DBG_SYNC_POSITION
				{
					extern UINT32 ipc_error_sim;
					ipc_error_sim = 1;
					DE_NOTI("Simulation 'ON'   for IPC error case\n");
				}
				else if(param.type == 2) //LX_DE_DBG_CVI_RESET
				{
					extern UINT32 ipc_error_sim;
					ipc_error_sim = 0;
					DE_NOTI("Simulation 'OFF'   for IPC error case\n");
				}
				else
				{
					CALL_IO(DE_IO_SetDebug);
				}
			}
			break;
		case DE_IOW_SET_SCART_RGB_BYPASS_MODE: // sw work-around
		default :
			break;
	}

	return ret;
}

#if 0 //not used
static int _ioctl_dolby(unsigned int cmd,unsigned long arg,unsigned int nFlag)
{
	int ret = RET_ERROR;
	DE_TRACE("@@ ##  %s \n", __F__);

	switch(cmd)
	{
		case DE_DHDR_IP_IORW_INIT:
			{
				//ret = DE_DHDR_IP_IO_Init(arg);
			}
			break;
		case DE_DHDR_IP_IOR_HDMI_MD_READ:
			{
				//ret = DE_DHDR_IP_IO_GetHDMIMetaData(arg); // Get 110 bytes of MetaData
			}
			break;
		case DE_DHDR_IP_IOR_OTT_MD_READ:
			{
				//ret = DE_DHDR_IP_IO_GetOTTMetaData(arg);
			}
			break;
		case DE_DHDR_IP_IOW_CONFIG:
			{
				//ret = DE_DHDR_IP_IO_SetConfig(arg);
			}
			break;
		case DE_DHDR_IP_IOW_LUT_CONFIG:
			{
				//ret = DE_DHDR_IP_IO_SetLut(arg);
			}
			break;
		case DE_DHDR_IP_IOW_START:
			{
				//ret = DE_DHDR_IP_IO_Start(arg);
			}
			break;
		case DE_DHDR_IP_IORW_UNINIT:
			{
				//ret = DE_DHDR_IP_IO_Uninit(arg);
			}
			break;
		case DE_DHDR_IP_IOW_MDREAD_UNBLOCK:
			{
				//ret = DE_DHDR_IP_INTR_MDReadUnblock(arg);
			}
			break;
		case DE_DHDR_IP_IOW_GET_CONFIG:
			{
				//ret = DE_DHDR_IP_IO_GetConfig(arg);
			}
			break;
		case DE_DHDR_IP_IOW_SET_HDMI_MD_PATH:
			{
				//ret = DE_DHDR_IP_IO_Set_HDMI_MD_Path(arg);
			}
			break;
		default:
			break;
	}
	return ret;
}
#endif

static int __operation(	DISP_DEV_TYPE  dev_id,  \
						OPERATION_TYPE opr_type,\
						EXECUTE_CMD    cmd,     \
						void          *param)
{
	int ret = RET_OK;
	DISPLAY_DEV_T *dev = g_dev[dev_id];
	SOURCE_INFO_T *src = dev->src;
	WINDOW_INFO_T *win = dev->win;
	SYSTEM_INFO_T *sys = dev->sys;
	BOOLEAN cmdRunStatus = (cmd == EXEC_CMD_RUN) ? TRUE : FALSE;
	BOOLEAN cmdOnOffStatus = (cmd == EXEC_CMD_OFF) ? FALSE : TRUE;

	do {
		CHECK_PTR(dev);

		//OPR_MAP(dev->opr, opr_type, cmd);
		__operation_map(&dev->opr, opr_type, cmd);

		switch(dev_id)
		{
			case DISP_DEV_MAIN :
				{
		//			dev->active = (cmd == EXEC_CMD_RUN) ? TRUE : FALSE;
				}
				break;
			case DISP_DEV_SUB_1:
				{
					//dev->active = (cmd == EXEC_CMD_RUN) ? TRUE : FALSE;
					dev->active = cmdRunStatus;

				}
				break;
			case DISP_DEV_VTS :
				{
					LX_DE_CVE_PARAM_T *p = (LX_DE_CVE_PARAM_T *)param;
					dev->active = TRUE;
					src->map = LX_DE_IN_SRC_FB;
					win->scan[dev_id] = LX_DE_INTERLACED;
					win->out_win[dev_id].rect.w = 720;

					win->out_win[dev_id].rect.h = DE_DENC_SCANLINES_MAP[p->std];
					win->rate[dev_id] = DE_DENC_FREQ_MAP[p->std];
					win->base_addr[dev_id] = p->fb; //(0:NTSC,1:PAL,2:SECAM)
					sys->cve_param.fb  = p->fb;
					sys->cve_param.std = p->std;
				}
				break;
			case DISP_DEV_VTV  :
				{
					LX_DE_DVR_DISFMT_T *p = (LX_DE_DVR_DISFMT_T *)param;
					#if 0
					dev->active = (cmd == EXEC_CMD_OFF) ? FALSE : TRUE;
					src->map = ((p->bOnOff & 0xF) == 1) ?       \
							   g_dev[DISP_DEV_MAIN]->src->map : \
							   ((p->bOnOff & 0xF) > 1)  ? 0 : 1;
					#else //Harish:: Need to test properly
						dev->active = cmdOnOffStatus;


						src->map = p->bOnOff ? g_dev[DISP_DEV_MAIN]->src->map:1;

					#endif
					win->scan[dev_id] = p->scan;
					win->out_win[dev_id].rect.w = p->h_size;
					win->out_win[dev_id].rect.h = p->v_size;
					win->rate[dev_id] = p->fr_rate;
					win->base_addr[dev_id] = p->baseAddr;
				}
				break;
			case DISP_DEV_VTM  :
				{
					LX_DE_VTM_FRAME_INFO_T *p = (LX_DE_VTM_FRAME_INFO_T *)param;
					//dev->active = (cmd == EXEC_CMD_OFF) ? FALSE : TRUE;
					dev->active = cmdOnOffStatus;
					if((DISP_DEV_TYPE)p->win_id >= DISP_DEV_MAX) break;
					src->map = g_dev[p->win_id]->src->map;
					win->scan[dev_id] = LX_DE_PROGRESSIVE;
					win->out_win[dev_id].rect.w = win->out_win[p->win_id].rect.w;
					win->out_win[dev_id].rect.h = win->out_win[p->win_id].rect.h;
					win->rate[dev_id] = sys->rate.fr_rate;
					win->base_addr[dev_id] = p->y_frame[0];
				}
				break;
			case DISP_DEV_VTC  :
				{
					LX_DE_CAPTURE_CTRL_T *p = (LX_DE_CAPTURE_CTRL_T *)param;
					//dev->active = (cmd == EXEC_CMD_OFF) ? FALSE : TRUE;
					dev->active = cmdOnOffStatus;
					src->map = g_dev[p->win_id]->src->map;
					win->scan[dev_id] = LX_DE_PROGRESSIVE;
					win->out_win[dev_id].rect.w = p->wOutSize;
					win->out_win[dev_id].rect.h = p->hOutSize;
					win->rate[dev_id] = sys->rate.fr_rate;
					win->base_addr[dev_id] = (uintptr_t)p->p_y_frame;
				}
				break;
			case DISP_DEV_GRAB :
				{
					//LX_DE_CVI_RW_VIDEO_FRAME_T *p = (LX_DE_CVI_RW_VIDEO_FRAME_T *)param;
					//dev->active = (cmd == EXEC_CMD_OFF) ? FALSE : TRUE;
					dev->active = cmdOnOffStatus;
					src->map = g_dev[DISP_DEV_MAIN]->src->map;
				}
				break;
			case DISP_DEV_VTH :
				{
					dev->active = cmdOnOffStatus;
				}
			break;
			case DISP_DEV_SUB_2:
			case DISP_DEV_SUB_3:
			case DISP_DEV_MAX  :
			default:
				DE_WARN("%s : un-defined dev[%d]\n", __F__, dev_id);
				break;
		}
	} while(0);

	return RET_OK;
}

static int __control(	DISP_DEV_TYPE    dev_id,\
						DISP_DEV_CONTROL ctrl,  \
						EXECUTE_CMD      cmd,   \
						void             *param)
{
	int ret = RET_OK;
	DISPLAY_DEV_T *dev = g_dev[dev_id];

	switch(ctrl)
	{
		case DEV_CONTROL_LOW_DLY :
			dev->low_delay = *(UINT32 *)param;
			break;
		case DEV_CONTROL_FRZ :
			dev->freeze    = (cmd == TRUE) ? TRUE : FALSE;
			break;
		case DEV_CONTROL_ACT_FMT :
			dev->act_fmt_detect = (cmd == TRUE) ? TRUE : FALSE;
			break;
		default :
			break;
	}

	return ret;
}

static int __operation_map( OPERATION_TYPE *p_opr,   \
							OPERATION_TYPE  cur_opr, \
							EXECUTE_CMD     cmd)
{
	int ret = RET_OK;

	if(cmd == EXEC_CMD_OFF)
	{
		*p_opr &= ~cur_opr;
	}
	else if((cmd == EXEC_CMD_RUN) || (cmd == EXEC_CMD_ONESHOT))
	{
		*p_opr |= cur_opr;
	}

	return ret;
}

static int __source_win_port_map(LX_DE_INPUT_SOURCE_T param)
{
	int ret = RET_OK;
	DISP_DEV_TYPE dev_id = (DISP_DEV_TYPE)param.srcId;
	DISPLAY_DEV_T *dev   = g_dev[dev_id];
	SOURCE_INFO_T *src   = dev->src;
	WINDOW_INFO_T *win   = g_win;

	do {
		CHECK_PTR(dev);
		src->map  = (LX_DE_IN_SRC_T)param.srcType;
		src->port = param.srcPort;
		src->attr = param.srcAttr;
		if(src->map == LX_DE_IN_SRC_NONE)
		{
			win->src_size_win[param.srcId].inSize.w = 0;
			win->src_size_win[param.srcId].inSize.h = 0;
		}
	} while(0);

	return ret;
}

static int __source_mirror(LX_DE_SRC_MIRROR_T param)
{
	int ret = RET_OK;
	DISP_DEV_TYPE dev_id = DISP_DEV_VTS;
	DISPLAY_DEV_T *dev   = g_dev[dev_id];
	SOURCE_INFO_T *src   = dev->src;

	do {
		CHECK_PTR(dev);
		src->mirror.srcPort  = param.srcPort;
		src->mirror.destPort = param.destPort;
		src->mirror.enable	 = param.enable;
	} while(0);

	return ret;
}

static int __source_property(LX_DE_CVI_SRC_TYPE_T param)
{
	int ret = RET_OK;
	DISP_DEV_TYPE dev_id = (DISP_DEV_TYPE)param.cvi_channel;
	DISPLAY_DEV_T *dev   = g_dev[dev_id];
	SOURCE_INFO_T *src   = dev->src;

	do {
		CHECK_PTR(dev);
		memcpy(&src->type, &param, sizeof(LX_DE_CVI_SRC_TYPE_T));
	} while(0);

	return ret;
}

static int __view_device(void)
{
	int ret = RET_OK;
	DISPLAY_DEV_T *dev = NULL;
	int i = 0;
	char str_src[MAX_SRC_NAME], str_oper[MAX_OP_NAME];

	do {
		DE_PRINT("\n@@  System Info.\n");
		DE_PRINT("Panel size : %d (0:FHD,1:WXGA(HD),2:1024x768, ...)\n",\
															g_sys->p_type);
		DE_PRINT("Fw. info.  : ver %d , y/m/d %04d/%02d/%02d\n",\
											g_sys->fw_info.version,   \
											g_sys->fw_info.date.year, \
											g_sys->fw_info.date.month,\
											g_sys->fw_info.date.day);
		DE_PRINT("Output en  : %s\n", g_sys->out_en?"TRUE":"FALSE");
		DE_PRINT("h/v/ha/va  : %d/%d/%d/%d\n", \
											g_sys->fmt.h_total, \
											g_sys->fmt.v_total, \
											g_sys->fmt.h_active,\
											g_sys->fmt.v_active);
		DE_PRINT("Panel type : %d (0:LCD,1:PDP,2:OLED,3:BOX,4:GTV_STB)\n",\
											g_sys->fmt.dev_type);
		DE_PRINT("Fr rate    : %d\n", g_sys->rate.fr_rate);
		DE_PRINT("act_fmt_detect : %d\n", g_dev[0]->act_fmt_detect);
		DE_PRINT("(oper bit 0:2D,1:3D,2:UD,3:PIP,4:MEM)\n");

		for(i=DISP_DEV_MAIN;i<DISP_DEV_MAX;i++)
		{
			dev = g_dev[i];
			CHECK_PTR(dev);

			__source_TypeToString(dev->src->map, &str_src[0]);
			__operation_TypeToString(dev->opr, &str_oper[0]);

			DE_PRINT("=== dev[%d] =====================================================\n", i);
			/*DE_PRINT("handle  : dev->0x%08x src->0x%08x opr->0x%08x\n",\
			 		 	i,                     \
						(unsigned int)dev,     \
						(unsigned int)dev->src,\
						(unsigned int)dev->opr);*/
			DE_PRINT("name    : %s\n", dev->name);
			DE_PRINT("active  : %s\n", (dev->active==FALSE)?"FALSE":"TRUE");
			//if(dev->active == TRUE)
			{
				LX_DE_CVI_SRC_TYPE_T p;
				DE_PRINT("opmode  : 0x%X \n", dev->opr);
				DE_PRINT("source  : %s\n", str_src);
				if(i < DISP_DEV_VTS){
					if(dev->win->order.enable == FALSE) {
						DE_PRINT("order   : hw default zorder (win0-bot/win1-top)\n");
					}
					else{
						DE_PRINT("order   : zorder win%d/win%d , alpha : %d/%d\n",\
								dev->win->order.z_list[0],\
								dev->win->order.z_list[1],\
								dev->win->order.alpha[0],\
								dev->win->order.alpha[1]);
					}

					DE_PRINT("bit res : %d", dev->bit_res);
					DE_PRINT(" , low delay : 0x%x , freeze : %d\n",\
							dev->low_delay,\
							dev->freeze);
				}
				DE_PRINT("in_win  : x(%d)/y(%d)/w(%d)/h(%d)\n", \
						dev->win->in_win[i].rect.x,\
						dev->win->in_win[i].rect.y,\
						dev->win->in_win[i].rect.w,\
						dev->win->in_win[i].rect.h);
				DE_PRINT("out_win : x(%d)/y(%d)/w(%d)/h(%d)\n", \
						dev->win->out_win[i].rect.x,\
						dev->win->out_win[i].rect.y,\
						dev->win->out_win[i].rect.w,\
						dev->win->out_win[i].rect.h);
				if(dev->win->inner_pattern.enable)
				{
					DE_PRINT("inner pattern : en(%d) type(%d)(0:full-gray,1:white-box) level(%d)\n",\
							dev->win->inner_pattern.enable, \
							dev->win->inner_pattern.type,   \
							dev->win->inner_pattern.level);
				}
				else
					DE_PRINT("inner pattern disabled");
				if(	(dev->src->map >  LX_DE_IN_SRC_HDMI) || \
					(dev->src->map == LX_DE_IN_SRC_NONE)) continue;
				memcpy(&p, &dev->src->type, sizeof(LX_DE_CVI_SRC_TYPE_T));
				DE_PRINT("  src size h/v/ho/vo %d/%d/%d/%d\n",\
							p.size_offset.hsize,p.size_offset.vsize,\
							p.size_offset.hoffset,p.size_offset.voffset);
				DE_PRINT("  color [%d] (0:601SD,1:709HD,2:RGB,3:RGBEX,\n",p.color);
				DE_PRINT("             4:XVYCC601,5:XVYCC709,6:601CVD)\n");
				DE_PRINT("  aspect   [%d] (0:4|3,1:16|9)\n",p.aspect);
				DE_PRINT("  scan     [%d] (0:I,1:P)\n",p.scan);
				DE_PRINT("  bit      [%d] (0:10bit,1:8bit)\n",p.bit_res);
				DE_PRINT("  c_sample [%d] (0:422,1:444)\n",p.c_sample);
				DE_PRINT("  de_mode  [%d] (0:normal sync,1:hdmi sync)\n",p.de_mode);
				DE_PRINT("  sampling [%d] (0:normal,1:double,2:quad)\n",p.sampling);
				DE_PRINT("  scaler c sample [%d] (0:yuv420,1:422,2:444)\n",p.sc_c_sample);
				DE_PRINT("  sync stability [%d] (0:std,1:nonstd)\n",p.stability);
				DE_PRINT("  field polarity [%d] (0:org,1:reverse)\n",p.field_polarity);
				DE_PRINT("  yc_delay    [%d] (0:bypass,1:atv,2:others)\n",p.yc_delay);
				DE_PRINT("  cvi port    [%d] (0:ext_a,1:ext_b,2:cvd,3:adc)\n",p.cvi_port);
				DE_PRINT("  3d full fmt [%d] (0:nor,1:FP,2:SSF,3:FIA,\n",p.trid_full_format);
				DE_PRINT("                   4:row-inter5:col-inter,6:4k2k)\n");
				DE_PRINT("  cvi src [%d] (0:VGA,1:YPbPr,2:ATV,3:CVBS,\n",p.cvi_input_src);
				DE_PRINT("               4:SVIDEO,5:SCART,6:HDMI)\n");
				DE_PRINT("  color std [%d] (0:default,1:NTSC_M,2:NTSC_M_RF,3:PAL,4:PAL_RF,\n",\
							p.cvd_color_std);
				DE_PRINT("                 5:SECAM,6:SECAM_RF,7:NTSC_443,8:NTSC_443_RF,\n");
				DE_PRINT("                 9:PAL_60,10:PAL_M_RF,11:PAL_M,12:PAL_M_RF,\n");
				DE_PRINT("                 13:PAL_NC,14:PAL_NC_RF,15:UNKNOWN)\n");
			}
		}
		DE_PRINT("===============================================================\n\n");
	} while(0);

	return ret;
}

static int __view_misc(void)
{
	/* memory configuration */
	de_cfg_disply();

	/* list of callback function  */
	de_sync_display();

	return RET_OK;
}


/* ioctl trace (called history) */

static int __view_ioctl(void)
{
	/* history of ioctl call  */
	__pop_ioc_buf(TRUE, 1);

	return RET_OK;
}

static int _init_ioc_buf(BOOLEAN sel)
{
	int ret = RET_OK;
	int i;

	if(sel == TRUE) // init
	{
		for(i=0;i<DE_IOC_MAXNR;i++)
		{
			memset(ioc_buf[i].s, 0, PARAM_NAME_MAX);
			ioc_buf[i].t.sec  = 0;
			ioc_buf[i].t.msec = 0;
			ioc_buf[i].t.usec = 0;
			ioc_buf[i].p      = NULL;
		}
	}
	else	// cleanup ioc buffer
	{
		for(i=0;i<DE_IOC_MAXNR;i++)
		{
			if(ioc_buf[i].p != NULL){
				OS_Free(ioc_buf[i].p);
				ioc_buf[i].p = NULL;
			}
		}
	}

	return ret;
}

static int __push_ioc_buf(unsigned int cmd, char *c, unsigned long arg,unsigned int nFlag)
{
	int ret = RET_OK;
	void *param = (void __user *)arg;
	TIME_STAMP_T t;
	UINT32 idx  = (UINT32)((cmd >> _IOC_NRSHIFT)   & _IOC_NRMASK);
	UINT32 size = (UINT32)((cmd >> _IOC_SIZESHIFT) & _IOC_SIZEMASK);
	UINT32 i = 0;

	if(idx > DE_IOC_MAXNR) EXIT_ERROR();

	if(ioc_buf[idx].p == NULL)
		ioc_buf[idx].p = (UINT8 *)OS_Malloc(size);

	ioc_buf[idx].c = cmd;
	if(nFlag == 0) {
		ret = copy_from_user(ioc_buf[idx].p, (void __user *)param, size);
		if(ret) DE_ERROR("copy error\n");
	}
	else {
		memcpy(ioc_buf[idx].p, param, size);
		ret = 0;
	}

	memset(ioc_buf[idx].s, 0, PARAM_NAME_MAX);
	for(i=0;i<PARAM_NAME_MAX;i++)
	{
		ioc_buf[idx].s[i] = c[i];
		if(c[i] == 0) break;
	}

	OS_GetCurrentTicks(&t.sec, &t.msec, &t.usec);
	memcpy(&ioc_buf[idx].t, (char*)&t, sizeof(TIME_STAMP_T));

	return RET_OK;
}

static void __pop_SYSTEM_ioc_buf(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOW_DE_INIT:
			{LX_DE_PANEL_TYPE_T *p = (LX_DE_PANEL_TYPE_T *)ioc_buf[index].p;
			DE_TRACE("\t\tpanel type [%d] ",*p);
			DE_TRACE("\t\t(0:1920/1366/1024/1365/3840/1280/720/640/576)\n");
			}break;
		case DE_IOR_GET_FIRMWARE_INFO:
			{LX_DE_FIRMWARE_INFO_T *p = (LX_DE_FIRMWARE_INFO_T *)ioc_buf[index].p;
			DE_TRACE("\t\tversion [%d] y/m/d  %d/%d/%d\n",  \
			p->version,p->date.year,p->date.month,p->date.day);
			}break;
		case DE_IOW_FW_DOWNLOAD:
			{LX_DE_FW_DWLD_T *p = (LX_DE_FW_DWLD_T *)ioc_buf[index].p;
			DE_TRACE("\t\tfw inx[%d] cfg[%d] size[%d]\n",p->inx,p->cfg,p->size);
			}break;
		case DE_IOW_SET_IF_CONFIG:
			{LX_DE_IF_CONFIG_T *p = (LX_DE_IF_CONFIG_T *)ioc_buf[index].p;
			DE_TRACE("\t\tconfig_type   [%d] ",p->config_type);
			DE_TRACE("\t\t(0:all,1:display_device,2:mirror,3:frc,4:3d)\n");
			DE_TRACE("\t\tdisplay_type  [%d] ",p->display_type);
			DE_TRACE("\t\t(0:LCD/PDP/OLED/CP/STB)\n");
			DE_TRACE("\t\tdisplay_mirror[%d] ",p->display_mirror);
			DE_TRACE("\t\t(0:off/x/y/x_y)\n");
			DE_TRACE("\t\tfrc_type      [%d] ",p->frc_type);
			DE_TRACE("\t\t(0:internal/external)\n");
			DE_TRACE("\t\ttrid_type [%d] (0:off/on)\n",p->trid_type);
			}break;
		case DE_IOR_GET_CAPACITY:
			break;
		case DE_IOW_SET_OUTPUT_MODE:
			break;
		case DE_IOW_SET_DIS_FMT:
			{LX_DE_DIS_FMT_T *p = (LX_DE_DIS_FMT_T *)ioc_buf[index].p;
			DE_TRACE("\t\tpanel_type [%d]\n",p->panel_type);
			DE_TRACE("\t\tfr_rate    [%d]\n",p->fr_rate);
			DE_TRACE("\t\th_total    [%d]\n",p->h_total);
			DE_TRACE("\t\tv_total    [%d]\n",p->v_total);
			DE_TRACE("\t\th_active   [%d]\n",p->h_active);
			DE_TRACE("\t\tv_active   [%d]\n",p->v_active);
			DE_TRACE("\t\tdev_type   [%d] (0:LCD/PDP/OLED/BOX/GTV_STB)\n",\
			p->dev_type);
			}break;
		case DE_IOW_SET_FR_RATE:
			{LX_DE_FR_RATE_T *p = (LX_DE_FR_RATE_T *)ioc_buf[index].p;
			DE_TRACE("\t\tfree run   [%d]\n",p->isForceFreeRun);
			DE_TRACE("\t\tframe rate [%d]\n",p->fr_rate);
			}break;
		case DE_IOR_GET_OUT_FR_RATE:
			{LX_DE_FR_RATE_T *p = (LX_DE_FR_RATE_T *)ioc_buf[index].p;
			DE_TRACE("\t\tfree run   [%d]\n",p->isForceFreeRun);
			DE_TRACE("\t\tframe rate [%d]\n",p->fr_rate);
			}break;
		case DE_IOW_SET_DIS_OUT:
			{BOOLEAN *p = (BOOLEAN *)ioc_buf[index].p;
			DE_TRACE("\t\tdisplay out [%d]\n", *p);
			}break;
		case DE_IOR_GET_SYS_STATUS:
			break;
		default:
			{
				DE_TRACE("\t\t undefined CMD \n");
			}
	}
}


static void __pop_SRC_ioc_buf(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOW_SET_WIN_PORT_SRC:
			{LX_DE_INPUT_SOURCE_T *p = (LX_DE_INPUT_SOURCE_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin[%d] type[%d] port[%d] attr[%d]\n" ,p->srcId, p->srcType,p->srcPort,p->srcAttr);
			DE_TRACE("\t\t type=(0:none,1:vga,2:ypbpr,3:atv,4:cvbs,5:scart,");
			DE_TRACE("\t\t	   6:hdmi,7:mvi,8:cpu,9:fb)\n");
			}break;
		case DE_IOW_SET_CVI_SRC_TYPE:
			{LX_DE_CVI_SRC_TYPE_T *p = (LX_DE_CVI_SRC_TYPE_T *)ioc_buf[index].p;
			DE_TRACE("\t\tcvi ch   [%d]\n",p->cvi_channel);
			DE_TRACE("\t\tsrc size h/v/ho/vo %d/%d/%d/%d\n",\
			p->size_offset.hsize,p->size_offset.vsize,\
			p->size_offset.hoffset,p->size_offset.voffset);
			DE_TRACE("\t\tcolor [%d] (0:601SD,1:709HD,2:RGB,3:RGBEX,\n",p->color);
			DE_TRACE("\t\t           4:XVYCC601,5:XVYCC709,6:601CVD)\n");
			DE_TRACE("\t\taspect   [%d] (0:4|3,1:16|9)\n",p->aspect);
			DE_TRACE("\t\tscan     [%d] (0:I,1:P)\n",p->scan);
			DE_TRACE("\t\tbit      [%d] (0:10bit,1:8bit)\n",p->bit_res);
			DE_TRACE("\t\tc_sample [%d] (0:422,1:444)\n",p->c_sample);
			DE_TRACE("\t\tde_mode  [%d] (0:normal sync,1:hdmi sync)\n",p->de_mode);
			DE_TRACE("\t\tsampling [%d] (0:normal,1:double,2:quad)\n",p->sampling);
			DE_TRACE("\t\tscaler c sample [%d] (0:yuv420,1:422,2:444)\n",p->sc_c_sample);
			DE_TRACE("\t\tsync stability [%d] (0:std,1:nonstd)\n",p->stability);
			DE_TRACE("\t\tfield polarity [%d] (0:org,1:reverse)\n",p->field_polarity);
			DE_TRACE("\t\tyc_delay    [%d] (0:bypass,1:atv,2:others)\n",p->yc_delay);
			DE_TRACE("\t\tcvi port    [%d] (0:ext_a,1:ext_b,2:cvd,3:adc)\n",p->cvi_port);
			DE_TRACE("\t\t3d full fmt [%d] (0:nor,1:FP,2:SSF,3:FIA,\n",p->trid_full_format);
			DE_TRACE("\t\t                 4:row-inter5:col-inter,6:4k2k)\n");
			DE_TRACE("\t\tcvi src [%d] (0:VGA,1:YPbPr,2:ATV,3:CVBS,\n",p->cvi_input_src);
			DE_TRACE("\t\t             4:SVIDEO,5:SCART,6:HDMI)\n");
			DE_TRACE("\t\tcolor std [%d] (0:default,1:NTSC_M,2:NTSC_M_RF,3:PAL,4:PAL_RF,\n",\
			p->cvd_color_std);
			DE_TRACE("\t\t               5:SECAM,6:SECAM_RF,7:NTSC_443,8:NTSC_443_RF,\n");
			DE_TRACE("\t\t               9:PAL_60,10:PAL_M_RF,11:PAL_M,12:PAL_M_RF,\n");
			DE_TRACE("\t\t			   13:PAL_NC,14:PAL_NC_RF,15:UNKNOWN)\n");
			}break;
		case DE_IOW_SET_CVI_CSAMPLE_MODE:
			{LX_DE_CSAMPLE_MODE_T *p = (LX_DE_CSAMPLE_MODE_T *)ioc_buf[index].p;
			DE_TRACE("\t\tcvi_ch[%d] is3tap[%d]\n",p->cvi_channel,p->is3tap);
			}break;
		case DE_IOR_GET_MVI_COLORIMETRY:
			break;
		case DE_IOW_SET_CVI_HDMIPORT:
			break;
		case DE_IOW_SET_CVI_FIR:
			{LX_DE_CVI_FIR_T *p = (LX_DE_CVI_FIR_T *)ioc_buf[index].p;
			DE_TRACE("\t\tcvi_ch[%d] enable[%d]\n",p->cvi_channel,p->isEnable);
			DE_TRACE("\t\ty[%02x %02x %02x %02x %02x %02x %02x %02x]\n",\
			p->fir_coef[0], p->fir_coef[1], p->fir_coef[2], p->fir_coef[3],\
			p->fir_coef[4], p->fir_coef[5], p->fir_coef[6], p->fir_coef[7]);
			DE_TRACE("\t\tc[%02x %02x %02x %02x %02x %02x]\n",\
			p->fir_coef_CbCr[0], p->fir_coef_CbCr[1], p->fir_coef_CbCr[2],\
			p->fir_coef_CbCr[3], p->fir_coef_CbCr[4], p->fir_coef_CbCr[5]);
			}break;
		case DE_IOR_GET_SRC_STATUS:
			break;
		case DE_IOW_SET_SRC_MIRROR:
			{LX_DE_SRC_MIRROR_T *p = (LX_DE_SRC_MIRROR_T *)ioc_buf[index].p;
			DE_TRACE("\t\tsrcPort[%d] dstPort[%d] enb[%d]\n",\
			p->srcPort,p->destPort,p->enable);
			}break;
		default:
			{
				DE_TRACE("\t\t undefined CMD \n");
			}
	}
}

static void __pop_CNTL_ioc_buf(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOR_GET_LOW_DELAY:
			break;
		case DE_IOW_SET_LOW_DELAY:
			{UINT32 *p = (UINT32 *)ioc_buf[index].p;
			DE_TRACE("\t\tparam  0x%08x\n",*p);
			}break;
		case DE_IOW_SET_WIN_FREEZE:
			{LX_DE_WIN_FREEZE_T *p = (LX_DE_WIN_FREEZE_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin[%d] enable[%d] loc[%d] (0:disp,1:input,2:sub)\n",\
			p->win_id, p->bEnable,p->location);
			}break;
		case DE_IOW_SET_ACT_FMT_DETECT:
			{LX_DE_ACT_FORMAT_T *p = (LX_DE_ACT_FORMAT_T *)ioc_buf[index].p;
			DE_TRACE("\t\tenable[%d] win_id[%d]\n",p->enable,p->win_id);
			}break;
		case DE_IOW_SET_FRAME_DELAY:
			{LX_DE_SET_DELAY_BUFFER_T *p = (LX_DE_SET_DELAY_BUFFER_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin [%d] , buffer num[%d]\n",p->win_id, p->ubuffer);
			}break;
		case DE_IOW_SET_ROTATE:
			{LX_DE_ROTATE_INFO_T *p = (LX_DE_ROTATE_INFO_T *)ioc_buf[index].p;
			DE_TRACE("\t\trotate [%d] 0/1/2/3 = 0/90/180/270 degree\n",*p);
			}break;		
		default:
			{
				DE_TRACE("\t\t undefined CMD \n");
			}
	}
}

static void __pop_WIN_ioc_buf(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOR_GET_INPUT_WIN:
			break;
		case DE_IOR_GET_OUT_WIN:
			break;
		case DE_IOW_SET_INPUT_WIN:
			{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin [%d]\n",p->win_id);
			DE_TRACE("\t\trect w/h/x/y  %d/%d/%d/%d\n",\
			p->rect.w,p->rect.h,p->rect.x,p->rect.y);
			}break;
		case DE_IOW_SET_OUT_WIN:
			{LX_DE_WIN_DIMENSION_T *p = (LX_DE_WIN_DIMENSION_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin [%d]\n",p->win_id);
			DE_TRACE("\t\trect w/h/x/y  %d/%d/%d/%d\n",\
			p->rect.w,p->rect.h,p->rect.x,p->rect.y);}break;
		case DE_IOW_SET_WIN_INFO:
			{LX_DE_WIN_INFO_T *p = (LX_DE_WIN_INFO_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin [%d]\n",p->wId);
			DE_TRACE("\t\trot[%d] src%dx%d win in%d/%d/%d/%d out%d/%d/%d/%d\n",\
			p->rot,p->in_size.w,p->in_size.h,p->in_win.x,p->in_win.y,p->in_win.w,\
			p->in_win.h,p->out_win.x,p->out_win.y,p->out_win.w,p->out_win.h);}break;
		case DE_IOW_SET_ZLIST:
			{LX_DE_ZLIST_T *p = (LX_DE_ZLIST_T *)ioc_buf[index].p;
			DE_TRACE("\t\tenable [%d]\n",p->enable);
			DE_TRACE("\t\torder %d/%d (top/bot)\n",p->z_list[0],p->z_list[1]);
			DE_TRACE("\t\talpha %d/%d (top/bot)\n",p->alpha[0],p->alpha[1]);
			}break;
		case DE_IOW_SET_MULTI_VISION:
			{LX_DE_RECT_T *p = (LX_DE_RECT_T *)ioc_buf[index].p;
			DE_TRACE("\t\tw/h/x/y %d/%d/%d/%d\n",p->w,p->h,p->x,p->y);
			}break;
		case DE_IOW_SET_WIN_BLANK:
			{LX_DE_SET_WIN_BLANK_T *p = (LX_DE_SET_WIN_BLANK_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin    [%d]\n",p->win_id);
			DE_TRACE("\t\tenable [%d]  isRGB [%d]\n",p->bEnable,p->isRGB);
			DE_TRACE("\t\tcolor r/g/b  %d/%d/%d\n",\
			p->win_color.r,p->win_color.g,p->win_color.b);
			}break;
		case DE_IOW_SET_BG_COLOR:
			{LX_DE_COLOR_T *p = (LX_DE_COLOR_T *)ioc_buf[index].p;
			DE_TRACE("\t\tr/g/b  %d/%d/%d\n",p->r,p->g,p->b);
			}break;
		case DE_IOW_SET_INNER_PATTERN:
			{LX_DE_INNER_PATTERN_T *p = (LX_DE_INNER_PATTERN_T *)ioc_buf[index].p;
			DE_TRACE("\t\tinner pattern  en[%d] type[%d](0:full-gray,1:white-box) level[%d]\n",
			p->enable,p->type,p->level);
			}break;
		case DE_IOW_SET_CVI_TPG:
			{LX_DE_CVI_TPG_T *p = (LX_DE_CVI_TPG_T *)ioc_buf[index].p;
			DE_TRACE("\t\tcvi channel[%d] ptn[%d] frz[%d] gbr[%d]\n",\
			p->cvi_channel,p->isPtnOn,p->isFrzOn,p->isGBR);
			DE_TRACE("\t\tpattern color[%d]\n",p->ptnColor);
			DE_TRACE("\t\t 0:white,1:yellow,2:cyan,3:green,4:magenta,5:red,6:blue,7:black\n");
			DE_TRACE("\t\t 8:gradation-h,9:grad-v,10:grad-c,11:grad-yc,12:black/white\n");
			}break;
		case DE_IOW_SET_SUB_WIN:
			{LX_DE_SET_SUB_WIN_T *p = (LX_DE_SET_SUB_WIN_T *)ioc_buf[index].p;
			DE_TRACE("\t\tsub_win[%d]\n",p->win_id);
			}break;
		case DE_IOW_SET_SUB_MODE:
			{LX_DE_SUB_MODE_T *p = (LX_DE_SUB_MODE_T *)ioc_buf[index].p;
			DE_TRACE("\t\tsub_mode[%d] (0:PIP, 1:PBP)\n",*p);
			}break;
		case DE_IOW_SET_SUB_SHAPE:
			{LX_DE_SUB_SHAPE_T *p = (LX_DE_SUB_SHAPE_T *)ioc_buf[index].p;
			DE_TRACE("\t\tsub_shape[%d](0:CIRCLE,1:RECT) w/h[%d/%d]\n",\
			p->sub_shape,p->org_win.w,p->org_win.h);
			}break;
		case DE_IOW_SET_SRC_SIZE:
			{LX_DE_SOURCE_SIZE_WIN_T *p = (LX_DE_SOURCE_SIZE_WIN_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin[%d] src size(%d/%d/%d/%d) in_win(%d/%d/%d/%d)\n",\
			p->win_id,p->inSize.x,p->inSize.y,p->inSize.w,p->inSize.h,\
			p->inWin.x,p->inWin.y,p->inWin.w,p->inWin.h);
			}break;		
		default:
			{
				DE_TRACE("\t\t undefined CMD \n");
			}
	}
}

static void __pop_OP_ioc_buf(unsigned int cmd, unsigned int index)
{

	switch(cmd)
	{
		case DE_IOW_SET_3D_INOUT_CTRL:
			{LX_DE_3D_INOUT_CTRL_T *p = (LX_DE_3D_INOUT_CTRL_T *)ioc_buf[index].p;
			DE_TRACE("\t\trun mode     [%d] ",p->run_mode);
			DE_TRACE("\t\t(0:off,1:on,2:3dTo2d,3:2dTo3d\n");
			DE_TRACE("\t\tin_fmt       [%d] ",p->in_img_fmt);
			DE_TRACE("\t\t(0:TB,1:SS,2:QNC,3:CB,4:FP,5:FRI,6:FIA,7:FS,8:LIA,");
			DE_TRACE("\t\t9:SSF,10:DHD,11:COA,12:LIAH)\n");
			DE_TRACE("\t\tin_lr_order  [%d] ",p->in_lr_order);
			DE_TRACE("\t\t(0:r first,1:l first)\n");
			DE_TRACE("\t\tout fmt      [%d] ",p->out_img_fmt);
			DE_TRACE("\t\t(0:2D,1:TB,2:SS,3:FS,4:FU,5:DTB,6:DSS)\n");
			DE_TRACE("\t\tout_lr_order [%d] ",p->out_lr_order);
			DE_TRACE("\t\t(0:r first,1:l first)\n");
			}break;
		case DE_IOW_SET_UD_MODE:
			{BOOLEAN *p = (BOOLEAN *)ioc_buf[index].p;
			DE_TRACE("\t\tud mode [%d]\n",*p);
			}break;
		case DE_IOW_MULTI_WIN_ENABLE:
			{BOOLEAN *p = (BOOLEAN *)ioc_buf[index].p;
			DE_TRACE("\t\tpip en [%d]\n",*p);
			}break;
		case DE_IOR_GET_SCALER_INFO:
			{LX_DE_SCALER_INFO_T *p = (LX_DE_SCALER_INFO_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin [%d]\n",p->win_id);
			DE_TRACE("\t\tw/h/s %d/%d/%d\n",p->width,p->height,p->stride);
			DE_TRACE("\t\tsampling [%d] (0:420/422/444)\n",p->sampling);
			DE_TRACE("\t\ty/c addr %p/%p\n",\
			p->p_y_frame,p->p_cbcr_frame);
			}break;
		case DE_IOW_SET_CVE:
			{LX_DE_CVE_PARAM_T *p = (LX_DE_CVE_PARAM_T *)ioc_buf[index].p;
			DE_TRACE("\t\tpath [%d] (0:w/osd,1:wo/osd,2:src)\n",p->fb);
			DE_TRACE("\t\ttime [%d] (0:NTSC,1:PAL,2:SECAM)\n",p->std);
			}break;
		case DE_IOW_SET_DVR_FMT_CTRL:
			{LX_DE_DVR_DISFMT_T *p = (LX_DE_DVR_DISFMT_T *)ioc_buf[index].p;
			DE_TRACE("\t\tonoff [%d]\n",p->bOnOff);
			DE_TRACE("\t\tscan  [%d] (0:i,1:p)\n",p->scan);
			DE_TRACE("\t\th/v   %d/%d\n", p->h_size,p->v_size);
			DE_TRACE("\t\tfr rate    %d\n",p->fr_rate);
			DE_TRACE("\t\tbase addr  0x%08x\n",p->baseAddr);
			}break;
		case DE_IOW_SET_VTM:
			{LX_DE_VTM_FRAME_INFO_T *p = (LX_DE_VTM_FRAME_INFO_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin    [%d]\n",p->win_id);
			DE_TRACE("\t\taddr   0x%08x\n",p->address);
			DE_TRACE("\t\tfd     [%d]\n",p->mem_fd);
			DE_TRACE("\t\tenable [%d]\n",p->enable);
			DE_TRACE("\t\tstride %d\n",p->stride);
			DE_TRACE("\t\tsampling [%d] (0:420,1:422,2:444)\n",p->sampling);
			}break;
		case DE_IOR_GET_VTM:
			{LX_DE_VTM_FRAME_INFO_T *p = (LX_DE_VTM_FRAME_INFO_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin [%d]\n",p->win_id);
			}break;
		case DE_IOW_GET_VTM_BUFFER:
			{LX_DE_VTM_FRAME_INFO_T *p = (LX_DE_VTM_FRAME_INFO_T *)ioc_buf[index].p;
			DE_TRACE("\t\t vt buffer base [0x%08X]\n",p->address);
			}break;
		case DE_IOW_SET_CAPTURE:
			{LX_DE_CAPTURE_CTRL_T *p = (LX_DE_CAPTURE_CTRL_T *)ioc_buf[index].p;
			DE_TRACE("\t\tlocation [%d] (0:source,1:display)\n",p->location);
			DE_TRACE("\t\tin win w/h/x/y %d/%d/%d/%d\n",\
			p->inWin.w,p->inWin.h,p->inWin.x,p->inWin.y);
			DE_TRACE("\t\tout win w/h %d/%d\n",p->wOutSize,p->hOutSize);
			DE_TRACE("\t\tpixel fmt [%d] (0:RGB10/RGB8/YC444_10/444_8/",p->pixelFormat);
			DE_TRACE("\t\t422_10/422_8/420_10/420_8)\n");
			DE_TRACE("\t\ty/c addr %p/%p, stride[%d]\n",\
			p->p_y_frame,p->p_cbcr_frame, p->stride);
			}break;
		case DE_IOWR_SET_CVI_VIDEO_FRAME_BUFFER:
			{LX_DE_CVI_RW_VIDEO_FRAME_T *p = (LX_DE_CVI_RW_VIDEO_FRAME_T *)ioc_buf[index].p;
			DE_TRACE("\t\twin [%d]\n",p->region.win_id);
			DE_TRACE("\t\tw/h/x/y %d/%d/%d/%d\n",\
			p->region.pixelGrabW,p->region.pixelGrabH,\
			p->region.pixelGrabX,p->region.pixelGrabY);
			DE_TRACE("\t\treal w/h in memory  %d/%d\n",\
			p->region.realPixelGrabW,p->region.realPixelGrabH);
			DE_TRACE("\t\tcolorspace [%d] (0:yuv,1:rgb)\n",p->region.colorSpace);
			DE_TRACE("\t\tcolorDepth [%d] (0:8bit,1:10bit)\n",p->region.colorDepth);
			DE_TRACE("\t\tphy Y8/Y2/C8/C2 [0x%08x/0x%08x/0x%08x/0x%08x] , stride [%d]",\
			p->frameAddr.phyFrameAddrY8,p->frameAddr.phyFrameAddrC8,\
			p->frameAddr.phyFrameAddrY2,p->frameAddr.phyFrameAddrC2,\
			p->frameAddr.stride);
			}break;
		case DE_IOWR_SET_VTM_BLOCK_STATE:
			break;
		case DE_IOW_SET_VCS:
			break;
		case DE_IOW_SET_OPERATION:
			break;
		case DE_IOW_SET_SUB_OPERATION:
			break;
		case DE_IOW_SET_SIGNAGE_MODE:
			{BOOLEAN *p = (BOOLEAN *)ioc_buf[index].p;
			DE_TRACE("\t\t signage mode en [%d]\n",*p);
			}break;
		case DE_IOW_SET_GCP_MODE:
			{LX_DE_GCP_INFO_T *p = (LX_DE_GCP_INFO_T *)ioc_buf[index].p;
			DE_TRACE("\t\t General Capture Path enable [%d]\n",p->enable);
			}break;
		case DE_IOW_DUAL_MODE_ENABLE:
			{BOOLEAN *p = (BOOLEAN *)ioc_buf[index].p;
			DE_TRACE("\t\t 4k dual mode en [%d]\n",*p);
			}break;
		case DE_IOW_SET_SRC_SYNC_LOW_DELAY:
			{UINT32 *p = (BOOLEAN *)ioc_buf[index].p;
			DE_TRACE("\t\t New low delay mode [%d]\n",*p);
			}break;
		case DE_IOW_SET_HIGH_FRAME_RATE:
			{UINT32 *p = (BOOLEAN *)ioc_buf[index].p;
			DE_TRACE("\t\t set high frame rate mode [%d]\n",*p);
			}break;
		default:
			{
				DE_TRACE("\t\t undefined CMD \n");
			}
	}
}


static void __pop_MISC_ioc_buf(unsigned int cmd, unsigned int index)
{
	switch(cmd)
	{
		case DE_IOW_SET_DEINTERLACE:
			break;
		case DE_IOR_REG_RD:
			break;
		case DE_IOW_REG_WR:
			break;
		case DE_IOR_GET_DBG:
			break;
		case DE_IOW_SET_DBG:
			break;
		case DE_IOW_SET_UART_FOR_MCU:
			break;
		case DE_IOW_SET_EVAL_DBG:
			break;
		case DE_IOW_SET_SCART_RGB_BYPASS_MODE:
			break;
		case DE_IOW_SET_SUB_SC_FREEZE:
			break;
		case DE_IOW_SET_CVI_FREEZE:
			{LX_DE_CVI_CAPTURE_FREEZE_T *p = (LX_DE_CVI_CAPTURE_FREEZE_T *)ioc_buf[index].p;
			DE_TRACE("\t\tOn/Off capture [%d] cvifreeze [%d]\n",\
					p->bCaptureOnOff, p->bCviFreezeOnOff);
			}break;
		default:
			{
				DE_TRACE("\t\t undefined CMD \n");
			}
	}
}



static int __pop_ioc_buf(BOOLEAN dump_all, unsigned int c)
{
	int i = 0;
	unsigned int cmd = c ;
	UINT32 idx  = (UINT32)((c >> _IOC_NRSHIFT)   & _IOC_NRMASK);

	if(cmd == 0) return RET_OK;

	if(!dump_all)
		i = idx;

	do
	{

		if(ioc_buf[i].p == NULL) continue;
		else cmd = ioc_buf[i].c;

		/*DE_TRACE("%s : cmd = %d , \t%06d.%06d \n", \
							ioc_buf[i].s, i,  \
							ioc_buf[i].t.sec, \
							ioc_buf[i].t.msec*1000 + ioc_buf[i].t.usec);*/

		switch(GET_IOCTL_CATEGORY(cmd))
		{
			case DE_SYSTEM_IOCTL:
				{
					__pop_SYSTEM_ioc_buf(cmd,i);
				}break;
			case DE_SRC_IOCTL:
				{
					__pop_SRC_ioc_buf(cmd,i);
				}break;

			case DE_WIN_IOCTL:
				{
					__pop_WIN_ioc_buf(cmd,i);
				}break;
			case DE_OP_IOCTL:
				{
					__pop_OP_ioc_buf(cmd,i);
				}break;
			case DE_CNTL_IOCTL:
				{
					__pop_CNTL_ioc_buf(cmd,i);
				}break;
			case DE_MISC_IOCTL:
				{
					__pop_MISC_ioc_buf(cmd,i);
				}break;
			default:
				{
					printk("\t\t Unknown IOCTL implementation\n");
				}
		}

	}while(dump_all && ++i <= DE_IOC_MAXNR);

	return RET_OK;
}

static int __test_ipc(UINT32 reset)
{
	int ret = RET_OK;
	SYSTEM_INFO_T *p = g_sys;
	static UINT32 send_count = 0;
	static UINT32 discont_count = 0;
	LX_DE_FIRMWARE_INFO_T send_info;
	unsigned long arg = (unsigned long)&send_info;
	static TIME_STAMP_T t[2];

	do {
		if(reset)
		{
			send_count = 0;
			discont_count = 0;
			OS_GetCurrentTicks(&t[0].sec, &t[0].msec, &t[0].usec);
		}
		send_info.ipc_count = send_count;
		DE_IO_GetFirmwareInfo(arg,1);
		COPY_FROM_USER(send_info, LX_DE_FIRMWARE_INFO_T,1);
		if((send_count + 1) != send_info.ipc_count)
		{
			discont_count++;
			DE_PRINT("Discontinuty : received count[%d] , sent count [%d]\n", \
					send_info.ipc_count, send_count);
		}
		send_count++;
		if(send_count >= p->thread_handle.param)
		{
			OS_GetCurrentTicks(&t[1].sec, &t[1].msec, &t[1].usec);

			DE_PRINT("Self-Ipc-Test\n");
			DE_PRINT("#########################################\n");
			DE_PRINT("Done. Total iteration [%d]\n", send_count);
			DE_PRINT("Started  at %d.%06d  sec\n", t[0].sec, t[0].msec * 1000 + t[0].usec);
			DE_PRINT("Finished at %d.%06d  sec\n", t[1].sec, t[1].msec * 1000 + t[1].usec);
			DE_PRINT("Discontinuity is occured [ %d ] times\n", discont_count);
			DE_PRINT("#########################################\n\n");

			p->thread_handle.type = THREAD_TYPE_MONITOR;
			p->thread_handle.enable = TRUE;
			send_count = 0;
			discont_count = 0;
		}
	} while(0);

	return ret;
}

static int _test_execute4mcu(void)
{
	__test_cmd2mcu(3, "WR", "0xC428", "0xFFFFFFFF",0,0,0,0,0,0);
	__test_cmd2mcu(4, "MVVDO", "0", "0x10","0xF0",0,0,0,0,0);
	__test_cmd2mcu(2, "MVDF", "4", 0,0,0,0,0,0,0);
	__test_cmd2mcu(3, "WR", "0xC428", "0",0,0,0,0,0,0);
	__test_cmd2mcu(2, "MVDF", "4", 0,0,0,0,0,0,0);

	printk("%s : done...\n", __F__);
	return 0;
}

static int __test_cmd2mcu(int argc, char* cmd, char* param0,   \
		char* param1, char* param2, char* param3, char* param4,\
		char* param5, char* param6, char* param7)
{
	char *cmd_buf[9];
	int i;
	int ret = 0;

	if(argc < 1) return ret;

	cmd_buf[0] = cmd;
	cmd_buf[1] = param0;
	cmd_buf[2] = param1;
	cmd_buf[3] = param2;
	cmd_buf[4] = param3;
	cmd_buf[5] = param4;
	cmd_buf[6] = param5;
	cmd_buf[7] = param6;
	cmd_buf[8] = param7;

	for(i=0;i<8;i++)
	{
		if(cmd_buf[i] != 0)	printk("%s ", cmd_buf[i]);
	}
	printk("\n");

	ret = DBI_VIDEO_Execute(argc, (char**)cmd_buf);

	if (ret) printk("cmd error\n");
	OS_MsecSleep(30);
	return ret;
}

static int __test_local_mute(void)
{
	int ret = 0;
	unsigned long arg;
	UINT32 mute_status = 0;
	static UINT32 prev_status = 0;

	arg = (unsigned long)&mute_status;
	ret = DE_IO_GetLocalMuteValue(arg,1);

	if(mute_status == 1 && prev_status == 0)
		DE_PRINT("scaler_local_mute is on\n");
	else if(mute_status == 0 && prev_status == 1)
		DE_PRINT("scaler_local_mute is off\n");

	prev_status = mute_status;

	return ret;
}
#include "de_hal.h"
static int __test_hdmi_pixel_access(void)
{
	UINT32 regVal = 0;
	//DE_HAL_ReadReg(0xC900C5B8, &regVal); regVal++; // VCP_DISP
	DE_HAL_ReadReg((void *)(uintptr_t)0xC900D0B0, &regVal); regVal++; // VSD_SHP
	DE_HAL_ReadReg((void *)(uintptr_t)0xC9025034, &regVal); regVal++; // CC
	//DE_HAL_ReadReg(0xC9020008, &regVal); regVal++; // LED
	return regVal;
}

