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
 *	de sync.
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

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "base_device.h"

#include "de_kapi.h"
#include "de_sync.h"
#include "de_def.h"
#include "de_hal.h"
#include "ipc_phys_hal.h"
#include "mcu/de_ipc_def.h"
#include "mcu/de_ipc.h"
#include "mcu/de_int.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_HDMI
int HDMI_Get_AVISizeData(int *width, int *height);
#endif

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions  
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
DE_SYNC_CB_T gcb[MAX_CB_NUM];
DE_SYNC_CB_T gcb_srcsync[MAX_CB_NUM];

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _sync_call(void);
static int _srcsync_call(void);
static int _seamless_call(void);
static int _set_sys_timestamp(void);
int test_src_sync(void);

/*========================================================================================
 *   Implementation Group
 *=======================================================================================*/
static BOOLEAN sync_log_enable = 0;

int test_src_sync(void)
{
	UINT32 t_sec, t_msec, t_usec;
	static UINT32 msec_time_cur, msec_time_old;
	UINT32 diff;

	OS_GetCurrentTicks(&t_sec, &t_msec, &t_usec);
	msec_time_cur = t_sec*1000 + t_msec;
	diff = msec_time_cur - msec_time_old;
	if(sync_log_enable) DE_NOTI("Time diff = %d msec\n", diff);
	msec_time_old = msec_time_cur;

	return 0;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief init sync handler for processing with de-vsync 
 */
int de_sync_init(void)
{
	int ret = RET_OK;
	// OS_FILE_T file;
#if 0
	if(RET_OK != OS_OpenFile(&file, "/var/vsync_log", O_RDONLY, 0666))
	{
		sync_log_enable = 0;
	}
	else
	{
		sync_log_enable = 1;
	}
#endif
	do {
		memset(gcb, 0, sizeof(DE_SYNC_CB_T) * MAX_CB_NUM);
		DE_VSYNC_Register("vsync", _sync_call);
		DE_VSYNC_Register("srcsync", _srcsync_call);
		DE_VSYNC_Register("seamless", _seamless_call);
		DE_PRINT("de_sync_init :  done  ret[%d] %s\n", \
						ret, (ret==RET_OK)?"OK":"FAIL");

		//for test
		de_srcsync_register(1, test_src_sync, "srcsync_handler");
		de_sync_register(1, _set_sys_timestamp, "set_sys_time");
#ifdef INCLUDE_KDRV_BE
		extern int vbe_vsync_notification(void);
		de_sync_register(1, vbe_vsync_notification, "vbe_gps_vsync");
#endif
	} while(0);
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief free sync handler 
 */
int de_sync_free(void)
{
	return DE_VSYNC_Free();
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief  wait until next vsync 
 */
int de_sync_wait(DE_SYNC_WAIT_TYPE_T type)
{
	int ret = RET_OK;

	switch(type)
	{
		case SYNC_WAIT_JPG :
			ret = VIDEO_JPG_WaitVsync();
			break;
		case SYNC_WAIT_USB :
			ret = VIDEO_USB_WaitVsync();
			break;
		case SYNC_WAIT_WEL :
			ret = VIDEO_WEL_WaitVsync();
			break;
		case SYNC_WAIT_WER :
			VIDEO_WER_WaitVsync();
			break;
		case SYNC_WAIT_DELAY :
			ret = VIDEO_Wait_VideoDelayInterrupt();
			break;
		case SYNC_WAIT_MUTEOFF:
			ret = VIDEO_Wait_MuteStatus();
			break;
		case SYNC_WAIT_VIDEO_DELAY:
			ret = VIDEO_Wait_VideoDelayLipsync();
			break;
		case SYNC_WAIT_VSYNC:
			ret = DE_VSYNC_WaitTimeOut(0, 10);
			break;
		default :
			break;
	}

	return ret;
}

int de_sync_wait_with_window(unsigned int wid, DE_SYNC_WAIT_TYPE_T type)
{
	int ret = RET_OK;

	if(type == SYNC_WAIT_VSYNC) {
			ret = DE_VSYNC_WaitTimeOut(wid, 32);
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief  send signal to terminate thread
 */
int de_sync_signal(DE_SYNC_WAIT_TYPE_T type)
{
	int ret = RET_OK;

	switch(type)
	{
		case SYNC_WAIT_DELAY :
			ret = VIDEO_Signal_VideoDelayInterrupt();
			break;
		case SYNC_WAIT_MUTEOFF:
			ret = VIDEO_Signal_MuteStatus();
			break;
		case SYNC_WAIT_VIDEO_DELAY:
			ret = VIDEO_Signal_VideoDelayLipsync();
			break;
		case SYNC_WAIT_VSYNC:
			DE_VSYNC_WakeUp();
			break;
		default :
			break;
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief  register callback function 
 */
int de_sync_register(BOOLEAN flag, int (*func)(void), char *str)
{
	int i = 0, j = 0;

	for(i=0;i<MAX_CB_NUM;i++)
	{
		if(flag) // register
		{
			if(!gcb[i].f)
			{
				gcb[i].f = func;
				for(j=0;j < MAX_CB_STR;j++)
				{
					gcb[i].s[j] = str[j];
					if(str[j] == 0) break;
				}
				return i;
			}
		}
		else     // unregister
		{
			if(gcb[i].f == func)
			{
				gcb[i].f = NULL;
				memset(gcb[i].s, 0, MAX_CB_STR);
				return i;
			}
		}
	}
	return -1;
}
EXPORT_SYMBOL(de_sync_register);

/**
 * @callgraph
 * @callergraph
 *
 * @brief  register src sync callback function
 */
int de_srcsync_register(BOOLEAN flag, int (*func)(void), char *str)
{
	int i = 0, j = 0;

	for(i=0;i<MAX_CB_NUM;i++)
	{
		if(flag) // register
		{
			if(!gcb_srcsync[i].f)
			{
				gcb_srcsync[i].f = func;
				for(j=0;j < MAX_CB_STR;j++)
				{
					gcb_srcsync[i].s[j] = str[j];
					if(str[j] == 0) break;
				}
				return i;
			}
		}
		else     // unregister
		{
			if(gcb_srcsync[i].f == func)
			{
				gcb_srcsync[i].f = NULL;
				memset(gcb_srcsync[i].s, 0, MAX_CB_STR);
				return i;
			}
		}
	}
	return -1;
}
EXPORT_SYMBOL(de_srcsync_register);

/**
 * @callgraph
 * @callergraph
 *
 * @brief display list of all registered callback function 
 */
int de_sync_display(void)
{
	int i = 0;
	DE_PRINT("List of de vsync callback function\n");
	for(i=0;i<MAX_CB_NUM;i++)
	{
		if(gcb[i].f) DE_PRINT("\t[%d]  %s\n", i, gcb[i].s);
	}

	DE_PRINT("List of de src sync callback function\n");
	for(i=0;i<MAX_CB_NUM;i++)
	{
		if(gcb_srcsync[i].f) DE_PRINT("\t[%d]  %s\n", i, gcb_srcsync[i].s);
	}
	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief display list of all registered callback function 
 */
int de_sync_vsync_enable(BOOLEAN enable)
{
	int ret = RET_OK;
	static int initialized = 0;
	if(!initialized || (enable > 1))
	{
		ret = DE_VSYNC_Init();
		initialized = 1;
	}
	return ret;
}

#ifdef INCLUDE_KDRV_HDMI
static int _sync_intr_to_mcu(UINT32 param, UINT16 x, UINT16 y, UINT16 w, UINT16 h)
{
	int ret = RET_OK;
	LX_DE_RECT_T rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	ret = DE_HAL_SetSeamlessInfo(&rect);

	ret = ipc_phys_hal_WakeUpSeamless(0);

	return ret;
}
#endif

static int _sync_call(void)
{
	int i = 0;
	static int s_count = 0;
	#define COUNT_END_TIME 1200 // every 20 seconds
	for(i=0;i<MAX_CB_NUM;i++)
	{
		if(gcb[i].f) gcb[i].f();
		if(s_count == COUNT_END_TIME) 
		{
			if(gcb[i].f) DE_TRACE("%s\n",gcb[i].s);
		}
	}
	if(s_count++ == COUNT_END_TIME)
		s_count = 0;
	return RET_OK;
}

static int _srcsync_call(void)
{
	int i = 0;
	static int s_count = 0;
#define COUNT_END_TIME 1200 // every 20 seconds
	for(i=0;i<MAX_CB_NUM;i++)
	{
		if(gcb_srcsync[i].f) gcb_srcsync[i].f();
		if(s_count == COUNT_END_TIME)
		{
			if(gcb_srcsync[i].f) DE_TRACE("%s\n",gcb_srcsync[i].s);
		}
	}
	if(s_count++ == COUNT_END_TIME)
		s_count = 0;
	return RET_OK;
}

static int _seamless_call(void)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_HDMI
	int width, height;
	ret = HDMI_Get_AVISizeData(&width, &height);
	ret = _sync_intr_to_mcu(0, 0, 0, width, height);
#endif
	return ret;
}

static int _set_sys_timestamp(void)
{
	int ret = RET_OK;
	UINT32 t_sec, t_msec, t_usec;

	ktime_t 	   t = ktime_get_real();
	struct timespec64 ts = ktime_to_timespec64(t);

	t_sec  = ts.tv_sec;
	t_msec = ts.tv_nsec/1000000;
	t_usec = (ts.tv_nsec%1000000)/1000;

	ret = DE_HAL_SetSysTime(&t_sec, &t_msec, &t_usec);

	return ret;
}

