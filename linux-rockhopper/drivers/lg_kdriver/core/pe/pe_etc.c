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

/** @file pe_etc.c
 *
 *  driver for picture enhance etc functions. ( used only within kdriver )
 *	- functional functions regardless of modules
 *	
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.07.16
 *	@see		
 */

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_reg.h"
#include "pe_def.h"
#include "pe_spd.h"
#include "pe_etc.h"
#include "pe_reg_hw.h"
#include "pe_etc_hw.h"
#include "pe_cmn_hw.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_ETC_DBG_PRINT(fmt, args...)	\
	if (_g_etc_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/
typedef struct
{
	int (*hw_inf_init)(PE_CFG_CTRL_T *pstParams);
	int (*start_pic_task)(PE_CFG_CTRL_T *pstParams);
	int (*download_db)(PE_CFG_CTRL_T *pstParams);
	int (*set_default)(LX_PE_DEFAULT_SETTINGS_T *pstParams);
	int (*set_tsk_debug)(LX_PE_DBG_SETTINGS_T *pstParams);
	int (*set_inf_debug)(LX_PE_DBG_SETTINGS_T *pstParams);
	int (*set_misc_tbl)(LX_PE_ETC_TBL_T *pstParams);
	int (*get_misc_tbl)(LX_PE_ETC_TBL_T *pstParams);
	int (*set_disp_info)(LX_PE_INF_DISPLAY_T *pstParams);
	int (*get_disp_info)(LX_PE_INF_DISPLAY_T *pstParams);
	int (*get_level_info)(LX_PE_INF_LEVEL_T *pstParams);
	int (*set_trace_pkt)(LX_PE_PKT_T *pstParams);
	int (*download_lgsrdb)(PE_CFG_CTRL_T *pstParams);
	int (*download_lgsrdb2)(PE_CFG_CTRL_T *pstParams);
	int (*proc_show_db)(int id, void *p, void *data);
}
PE_ETC_CB_FUNC_T;

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/
static PE_ETC_CB_FUNC_T _g_pe_etc_cb_fn;
static UINT32 _g_etc_trace=0x0;	//default should be off.

/*============================================================================
	Implementation Group
============================================================================*/
/**
 * register call back functions
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_etc_cb_fn, 0, sizeof(PE_ETC_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_O26_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_O26_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_O26_DownloadDb;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_O26_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_O26_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_O26_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_O26_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_O26_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_O26_GetDisplayInfo;
			_g_pe_etc_cb_fn.proc_show_db		= pe_inf_o26_proc_show_db;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_O24_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_O24_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_O24_DownloadDb;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_O24_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_O24_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_O24_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_O24_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_O24_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_O24_GetDisplayInfo;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_M23_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_M23_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_M23_DownloadDb;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_M23_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_M23_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_M23_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_M23_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_M23_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_M23_GetDisplayInfo;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_O22_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_O22_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_O22_DownloadDb;
			_g_pe_etc_cb_fn.set_default			= NULL;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_O22_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_O22_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_O22_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_O22_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_O22_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_O22_GetDisplayInfo;
			_g_pe_etc_cb_fn.get_level_info		= PE_INF_O22_GetLevelInfo;
			_g_pe_etc_cb_fn.set_trace_pkt		= PE_INF_O22_SetTracePacketData;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_E60_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_E60_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_E60_DownloadDb;
			_g_pe_etc_cb_fn.set_default			= NULL;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_E60_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_E60_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_E60_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_E60_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_E60_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_E60_GetDisplayInfo;
			_g_pe_etc_cb_fn.get_level_info		= PE_INF_E60_GetLevelInfo;
			_g_pe_etc_cb_fn.set_trace_pkt		= PE_INF_E60_SetTracePacketData;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_O20_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_O20_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_O20_DownloadDb;
			_g_pe_etc_cb_fn.set_default			= NULL;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_O20_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_O20_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_O20_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_O20_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_O20_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_O20_GetDisplayInfo;
			_g_pe_etc_cb_fn.get_level_info		= PE_INF_O20_GetLevelInfo;
			_g_pe_etc_cb_fn.set_trace_pkt		= PE_INF_O20_SetTracePacketData;
			//_g_pe_etc_cb_fn.download_lgsrdb		= PE_CMN_HW_O20_DownloadLGSRDb;
			//_g_pe_etc_cb_fn.download_lgsrdb2	= PE_CMN_HW_F20_DownloadLGSRDb;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O18
		if (PE_KDRV_VER_O18)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_O18_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_O18_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_O18_DownloadDb;
			_g_pe_etc_cb_fn.set_default			= NULL;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_O18_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_O18_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_O18_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_O18_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_O18_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_O18_GetDisplayInfo;
			_g_pe_etc_cb_fn.get_level_info		= PE_INF_O18_GetLevelInfo;
			_g_pe_etc_cb_fn.set_trace_pkt		= PE_INF_O18_SetTracePacketData;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M17
		if (PE_KDRV_VER_M17CX)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_M17C0_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_M17C0_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_M17C0_DownloadDb;
			_g_pe_etc_cb_fn.set_default			= NULL;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_M17C0_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_M17C0_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_M17C0_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_M17C0_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_M17C0_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_M17C0_GetDisplayInfo;
			_g_pe_etc_cb_fn.get_level_info		= PE_INF_M17C0_GetLevelInfo;
			_g_pe_etc_cb_fn.set_trace_pkt		= PE_INF_M17C0_SetTracePacketData;
		}
		else if (PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_M17_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_M17_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_M17_DownloadDb;
			_g_pe_etc_cb_fn.set_default			= NULL;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_M17_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_M17_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_M17_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_M17_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_M17_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_M17_GetDisplayInfo;
			_g_pe_etc_cb_fn.get_level_info		= PE_INF_M17_GetLevelInfo;
			_g_pe_etc_cb_fn.set_trace_pkt		= PE_INF_M17_SetTracePacketData;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M19
		if (PE_KDRV_VER_M19)
		{
			_g_pe_etc_cb_fn.hw_inf_init			= PE_INF_M19_Init;
			_g_pe_etc_cb_fn.start_pic_task		= PE_TSK_M19_StartPicTask;
			_g_pe_etc_cb_fn.download_db			= PE_CMN_HW_M19_DownloadDb;
			_g_pe_etc_cb_fn.set_default			= NULL;
			_g_pe_etc_cb_fn.set_tsk_debug		= PE_TSK_M19_SetDebugSettings;
			_g_pe_etc_cb_fn.set_inf_debug		= PE_INF_M19_SetDebugSettings;
			_g_pe_etc_cb_fn.set_misc_tbl		= PE_INF_M19_SetMiscTbl;
			_g_pe_etc_cb_fn.get_misc_tbl		= PE_INF_M19_GetMiscTbl;
			_g_pe_etc_cb_fn.set_disp_info		= PE_INF_M19_SetDisplayInfo;
			_g_pe_etc_cb_fn.get_disp_info		= PE_INF_M19_GetDisplayInfo;
			_g_pe_etc_cb_fn.get_level_info		= PE_INF_M19_GetLevelInfo;
			_g_pe_etc_cb_fn.set_trace_pkt		= PE_INF_M19_SetTracePacketData;
			_g_pe_etc_cb_fn.download_lgsrdb		= NULL;//PE_CMN_HW_M19_DownloadLGSRDb;
		}
		else
		#endif
		{
			PE_PRINT_ERROR("[%x,%x] kdrv chip ver is wrong.\n", \
				PE_CHIP_VER, g_pe_kdrv_ver_mask);
			ret = RET_ERROR;
		}
	}while (0);
	return ret;
}
/**
 * set trace packet data
 *
 * @param   *pstParams [in] LX_PE_PKT_T int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */ 
int PE_ETC_SetTracePacketData(LX_PE_PKT_T *pstParams)
{
    int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_etc_cb_fn.set_trace_pkt)
		{
			ret = _g_pe_etc_cb_fn.set_trace_pkt(pstParams);
			PE_CHECK_CODE(ret, break, "set_trace_pkt() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * misc. module
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_etc_cb_fn.hw_inf_init)
		{
			ret = _g_pe_etc_cb_fn.hw_inf_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_inf_init() error.\n");
		}
		/* download_db should be the last in the pe initialization */
		if(_g_pe_etc_cb_fn.download_db)
		{
			ret = _g_pe_etc_cb_fn.download_db(pstParams);
			PE_CHECK_CODE(ret, break, "download_db() error.\n");
		}
		#if 0
		if(_g_pe_etc_cb_fn.download_lgsrdb)
		{
			ret = _g_pe_etc_cb_fn.download_lgsrdb(pstParams);
			PE_CHECK_CODE(ret, break, "download_lgsrdb() error.\n");
		}
		if(_g_pe_etc_cb_fn.download_lgsrdb2)
		{
			ret = _g_pe_etc_cb_fn.download_lgsrdb2(pstParams);
			PE_CHECK_CODE(ret, break, "download_lgsrdb2() error.\n");
		}
		#endif
		/* Starting task should be the last in the pe initialization */
		if(_g_pe_etc_cb_fn.start_pic_task)
		{
			ret = _g_pe_etc_cb_fn.start_pic_task(pstParams);
			PE_CHECK_CODE(ret, break, "start_pic_task() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of etc setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#ifdef PE_KDRV_USE_SPD_FUNC
#define PE_ETC_SET_FSDP(_struct, _func, _sdp)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_ETC_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			ret = PE_SPD_COPY_FROM_USER(_sdp, (void *)&param, (void *)p_rcv, datasize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s error.\n", __F__, __L__, #_sdp);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_ETC_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break
#endif

#define PE_ETC_SET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_ETC_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_ETC_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

#define PE_ETC_SET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_ETC_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size, 0, 16) * sizeof(UINT32);\
			PE_CHECK_CODE(!bufsize, break, \
				"[%s,%d] bufsize zero.\n", __F__, __L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CHECK_CODE(!p_data, break, \
				"[%s,%d] p_data is null.\n", __F__, __L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_from_user error.\n", __F__, __L__);\
			param.func_num = p_rcv->func_num;\
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_ETC_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, 
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_ETC_SET_TABL(LX_PE_ETC_TBL_T, 			PE_ETC_SetMiscTbl);
		PE_ETC_SET_FUNC(LX_PE_INF_DISPLAY_T, 		PE_ETC_SetDisplayInfo);
		PE_ETC_SET_FUNC(LX_PE_DBG_SETTINGS_T, 		PE_ETC_SetDebugSettings);
		PE_ETC_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T, 	PE_ETC_SetDefaultSettings);
		default:
		{
			PE_PRINT_ERROR("functype(%d) default case.\n", functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of etc getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_ETC_GET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
		}while (0);\
	}\
	break

#define PE_ETC_GET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_ETC_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size, 0, 16) * sizeof(UINT32);\
			PE_CHECK_CODE(!bufsize, break, \
				"[%s,%d] bufsize zero.\n", __F__, __L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CHECK_CODE(!p_data, break, \
				"[%s,%d] p_data is null.\n", __F__, __L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_from_user error.\n", __F__, __L__);\
			param.func_num = p_rcv->func_num;\
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_to_user error.\n", __F__, __L__);\
			PE_ETC_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_ETC_GET_TABL(LX_PE_ETC_TBL_T, 		PE_ETC_GetMiscTbl);
		PE_ETC_GET_FUNC(LX_PE_INF_DISPLAY_T, 	PE_ETC_GetDisplayInfo);
		PE_ETC_GET_FUNC(LX_PE_INF_LEVEL_T, 		PE_ETC_GetLevelInfo);
		default:
		{
			PE_PRINT_ERROR("functype(%d) default case.\n", functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}
/**
 * debug setting
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if (pstParams->type&LX_PE_DBG_LV)
		{
			_g_etc_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(ETC)))? 0x1:0x0;
		}
		if(_g_pe_etc_cb_fn.set_tsk_debug)
		{
			ret = _g_pe_etc_cb_fn.set_tsk_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_tsk_debug() error.\n");
		}
		if(_g_pe_etc_cb_fn.set_inf_debug)
		{
			ret = _g_pe_etc_cb_fn.set_inf_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_inf_debug() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * default setting
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_ETC_DBG_PRINT("[win id:%d]\n", pstParams->win_id);
	}while (0);
	return ret;
}
/**
 * set misc table
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_SetMiscTbl(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_etc_cb_fn.set_misc_tbl)
		{
			ret = _g_pe_etc_cb_fn.set_misc_tbl(pstParams);
			PE_CHECK_CODE(ret, break, "set_misc_tbl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get misc debug(for debug)
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_GetMiscTbl(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_etc_cb_fn.get_misc_tbl)
		{
			ret = _g_pe_etc_cb_fn.get_misc_tbl(pstParams);
			PE_CHECK_CODE(ret, break, "get_misc_tbl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set display info
 *
 * @param   *pstParams [in] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_SetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_etc_cb_fn.set_disp_info)
		{
			ret = _g_pe_etc_cb_fn.set_disp_info(pstParams);
			PE_CHECK_CODE(ret, break, "set_disp_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get display info
 *
 * @param   *pstParams [in/out] LX_PE_INF_DISPLAY_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_GetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_etc_cb_fn.get_disp_info)
		{
			ret = _g_pe_etc_cb_fn.get_disp_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_disp_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get level info
 *
 * @param   *pstParams [in/out] LX_PE_INF_LEVEL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_ETC_GetLevelInfo(LX_PE_INF_LEVEL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_etc_cb_fn.get_level_info)
		{
			ret = _g_pe_etc_cb_fn.get_level_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_level_info() error.\n");
		}
	}while (0);
	return ret;
}

int pe_inf_proc_show_db(int id, void *p, void *data)
{
	int ret = RET_OK;
	if(_g_pe_etc_cb_fn.proc_show_db) {
		ret = _g_pe_etc_cb_fn.proc_show_db(id,p,data);
	}
	return ret;
}
