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

/** @file pe_hst.c
 *
 *  driver for picture enhance histogram module functions. ( used only within kdriver )
 *	- histogram information and configuration.
 *	
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.02
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

#include "pe_def.h"
#include "pe_hst.h"
#include "pe_etc_hw.h"
#include "pe_hst_hw.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_HST_DBG_PRINT(fmt, args...)	\
	if (_g_hst_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/
typedef struct
{
	int (*hw_init)(PE_CFG_CTRL_T *pstParams);
	int (*set_default)(LX_PE_DEFAULT_SETTINGS_T *pstParams);
	int (*set_debug)(LX_PE_DBG_SETTINGS_T *pstParams);
	int (*get_histo_info)(LX_PE_HST_HISTO1_INFO_T *pstParams);
	int (*get_hdr_info)(LX_PE_HST_HDR_INFO_T *pstParams);
	int (*set_histo_config)(LX_PE_HST_HISTO_CFG_T *pstParams);
	int (*get_histo_config)(LX_PE_HST_HISTO_CFG_T *pstParams);
	int (*get_apl_info)(LX_PE_HST_APL_INFO_T *pstParams);
	int (*get_blk_apl)(LX_PE_HST_BLK_APL_T *pstParams);
	int (*proc_show_histo)(int id, void *p, void *data);
}
PE_HST_CB_FUNC_T;

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
static PE_HST_CB_FUNC_T _g_pe_hst_cb_fn;
static UINT32 _g_hst_trace=0x0;	//default should be off.

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
int PE_HST_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_hst_cb_fn, 0, sizeof(PE_HST_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_O26_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_O26_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_O26_GetHistogramInfo;//TODO:incompatible pointer type
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_O26_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_O26_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_O26_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = NULL;
			_g_pe_hst_cb_fn.proc_show_histo     = pe_hst_hw_o26_proc_show_histo;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_O24_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_O24_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_O24_GetHistogramInfo;//TODO:incompatible pointer type
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_O24_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_O24_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_O24_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = NULL;
			_g_pe_hst_cb_fn.proc_show_histo     = pe_hst_hw_o24_proc_show_histo;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_M23_Init;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_M23_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_M23_GetHistogramInfo;//TODO:incompatible pointer type
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_M23_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_M23_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_M23_GetAplInfo;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_O22_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_O22_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_O22_GetHistogramInfo;//TODO:incompatible pointer type
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_O22_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_O22_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_O22_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = NULL;
			_g_pe_hst_cb_fn.proc_show_histo     = pe_hst_hw_o22_proc_show_histo;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_E60_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_E60_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_E60_GetHistogramInfo;//TODO:incompatible pointer type
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_E60_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_E60_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_E60_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = NULL;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_O20_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_O20_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_O20_GetHistogramInfo;//TODO:incompatible pointer type
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_O20_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_O20_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_O20_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = NULL;//PE_HST_HW_O20_GetBlkAplData;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O18
		if (PE_KDRV_VER_O18)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_O18_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_O18_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_O18_GetHistogramInfo;
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_O18_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_O18_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_O18_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = PE_HST_HW_O18_GetBlkAplData;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M17
		if (PE_KDRV_VER_M17CX)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_M17C0_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_M17C0_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_M17C0_GetHistogramInfo;
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_M17C0_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_M17C0_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_M17C0_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = PE_HST_HW_M17C0_GetBlkAplData;
		}
		else if (PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_M17_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_M17_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_M17_GetHistogramInfo;
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_M17_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_M17_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_M17_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = PE_HST_HW_M17_GetBlkAplData;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M19
		if (PE_KDRV_VER_M19)
		{
			_g_pe_hst_cb_fn.hw_init				= PE_HST_HW_M19_Init;
			_g_pe_hst_cb_fn.set_default			= NULL;
			_g_pe_hst_cb_fn.set_debug			= PE_HST_HW_M19_SetDebugSettings;
			_g_pe_hst_cb_fn.get_histo_info		= PE_HST_HW_M19_GetHistogramInfo;
			_g_pe_hst_cb_fn.get_hdr_info		= NULL;
			_g_pe_hst_cb_fn.set_histo_config	= PE_HST_HW_M19_SetHistoConfig;
			_g_pe_hst_cb_fn.get_histo_config	= PE_HST_HW_M19_GetHistoConfig;
			_g_pe_hst_cb_fn.get_apl_info	    = PE_HST_HW_M19_GetAplInfo;
			_g_pe_hst_cb_fn.get_blk_apl	        = PE_HST_HW_M19_GetBlkAplData;
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
 * init dynamic contrast module
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_hst_cb_fn.hw_init)
		{
			ret = _g_pe_hst_cb_fn.hw_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_init() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of hst setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_HST_SET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_HST_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_HST_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_HST_SET_FUNC(LX_PE_HST_HISTO_CFG_T,		PE_HST_SetHistoConfig);
		PE_HST_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_HST_SetDefaultSettings);
		PE_HST_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_HST_SetDebugSettings);
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
 * standard function of hst getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_HST_GET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_HST_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
			PE_HST_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

/** get func without start,
*   end print(WOPT:WithOut PRint) because of too many prints */
#define PE_HST_GET_WOPR(_struct, _func)	\
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

#define PE_HST_GET_TABL(_struct, _func)	\
		case PE_ITEM_PKTFUNC(_struct):\
		{\
			_struct *p_rcv, param;\
			UINT32 *p_data = NULL;\
			UINT32 bufsize;\
			memset0(param);\
			do{\
				PE_HST_DBG_PRINT("S %s\n", #_struct);\
				PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
					"[%s,%d] size mismatch.\n", __F__, __L__);\
				p_rcv = (_struct *)data;\
				bufsize = GET_BITS(p_rcv->size, 0, 16) * sizeof(UINT32);\
				PE_CHECK_CODE(!bufsize, break, \
					"[%s,%d] bufsize zero.\n", __F__, __L__);\
				p_data = OS_Malloc(bufsize);\
				PE_CHECK_CODE(!p_data, break, \
					"[%s,%d] p_data is null.\n", __F__, __L__);\
				param.win_id = p_rcv->win_id;\
				param.size = p_rcv->size;\
				param.data = p_data;\
				ret = _func(&param);\
				PE_CHECK_CODE(ret, break, \
					"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
				ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
				PE_CHECK_CODE(ret, break, \
					"[%s,%d] copy_to_user error.\n", __F__, __L__);\
				PE_HST_DBG_PRINT("E %s\n", #_struct);\
			}while (0);\
			if (p_data){OS_Free(p_data);}\
		}\
		break


	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_HST_GET_WOPR(LX_PE_HST_HISTO_INFO_T,		PE_HST_GetHistogramInfo);
		PE_HST_GET_WOPR(LX_PE_HST_HDR_INFO_T,		PE_HST_GetHdrInfo);
		PE_HST_GET_FUNC(LX_PE_HST_HISTO_CFG_T,		PE_HST_GetHistoConfig);
		PE_HST_GET_FUNC(LX_PE_HST_APL_INFO_T,		PE_HST_GetAplInfo);
		PE_HST_GET_TABL(LX_PE_HST_BLK_APL_T,		PE_HST_GetBlkApl);
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
 * default setting
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_HST_DBG_PRINT("[win id:%d]\n", pstParams->win_id);
	}while (0);
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
int PE_HST_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if (pstParams->type&LX_PE_DBG_LV)
		{
			_g_hst_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(HST)))? 0x1:0x0;
		}
		if(_g_pe_hst_cb_fn.set_debug)
		{
			ret = _g_pe_hst_cb_fn.set_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_debug() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dce histogram info
 *
 * @param   *pstParams [in/out] LX_PE_HST_HISTO_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_GetHistogramInfo(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_hst_cb_fn.get_histo_info)
		{
			ret = _g_pe_hst_cb_fn.get_histo_info((LX_PE_HST_HISTO1_INFO_T *)pstParams);
			PE_CHECK_CODE(ret, break, "get_histo_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get hdr info
 *
 * @param   *pstParams [in/out] LX_PE_HST_HDR_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_GetHdrInfo(LX_PE_HST_HDR_INFO_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_hst_cb_fn.get_hdr_info)
		{
			ret = _g_pe_hst_cb_fn.get_hdr_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_hdr_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set histogram config
 *
 * @param   *pstParams [in] LX_PE_HST_HISTO_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_SetHistoConfig(LX_PE_HST_HISTO_CFG_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_hst_cb_fn.set_histo_config)
		{
			ret = _g_pe_hst_cb_fn.set_histo_config(pstParams);
			PE_CHECK_CODE(ret, break, "set_histo_config() error.\n");
		}
	} while (0);
	return ret;
}
/**
 * get histogram config
 *
 * @param   *pstParams [in/out] LX_PE_HST_HISTO_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_GetHistoConfig(LX_PE_HST_HISTO_CFG_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_hst_cb_fn.get_histo_config)
		{
			ret = _g_pe_hst_cb_fn.get_histo_config(pstParams);
			PE_CHECK_CODE(ret, break, "get_histo_config() error.\n");
		}
	} while (0);
	return ret;
}
/**
 * get apl info
 *
 * @param   *pstParams [in/out] LX_PE_HST_HISTO_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_GetAplInfo(LX_PE_HST_APL_INFO_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_hst_cb_fn.get_apl_info)
		{
			ret = _g_pe_hst_cb_fn.get_apl_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_apl_info() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get blk apl
 *
 * @param   *pstParams [in/out] LX_PE_HST_HISTO_INFO_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_HST_GetBlkApl(LX_PE_HST_BLK_APL_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_hst_cb_fn.get_blk_apl)
		{
			ret = _g_pe_hst_cb_fn.get_blk_apl(pstParams);
			PE_CHECK_CODE(ret, break, "get_blk_apl() error.\n");
		}
	}while (0);
	return ret;
}

int pe_hst_proc_show_histo(int id, void *p, void *data)
{
	int ret = RET_OK;
	if(_g_pe_hst_cb_fn.proc_show_histo) {
		ret = _g_pe_hst_cb_fn.proc_show_histo(id,p,data);
	}
	return ret;
}
