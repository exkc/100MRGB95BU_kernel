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

/** @file pe_win.c
 *
 *  driver for picture enhance window control functions.
 *  ( used only within kdriver )
 *	- control window of each pe module
 *	
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
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
#include "pe_etc.h"
#include "pe_win.h"
#include "pe_etc_hw.h"
#include "pe_win_hw.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_WIN_DBG_PRINT(fmt, args...)	\
	if (_g_win_trace)\
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
}
PE_WIN_CB_FUNC_T;

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
static PE_WIN_CB_FUNC_T _g_pe_win_cb_fn;
static UINT32 _g_win_trace=0x0;	//default should be off.

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
int PE_WIN_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_win_cb_fn, 0, sizeof(PE_WIN_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_win_cb_fn.hw_init 			= PE_WIN_HW_O26_Init;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_O26_SetDebugSettings;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_win_cb_fn.hw_init 			= PE_WIN_HW_O24_Init;
			_g_pe_win_cb_fn.set_default 		= NULL;//NULL;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_O24_SetDebugSettings;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_win_cb_fn.hw_init 			= PE_WIN_HW_M23_Init;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_M23_SetDebugSettings;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_win_cb_fn.hw_init 			= PE_WIN_HW_O22_Init;
			_g_pe_win_cb_fn.set_default 		= NULL;//NULL;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_O22_SetDebugSettings;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_win_cb_fn.hw_init 			= PE_WIN_HW_E60_Init;
			_g_pe_win_cb_fn.set_default 		= NULL;//NULL;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_E60_SetDebugSettings;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_win_cb_fn.hw_init 			= PE_WIN_HW_O20_Init;
			_g_pe_win_cb_fn.set_default 		= NULL;//NULL;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_O20_SetDebugSettings;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O18
		if (PE_KDRV_VER_O18)
		{
			_g_pe_win_cb_fn.hw_init				= PE_WIN_HW_O18_Init;
			_g_pe_win_cb_fn.set_default			= NULL;//NULL;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_O18_SetDebugSettings;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M17
		if (PE_KDRV_VER_M17CX)
		{
			_g_pe_win_cb_fn.hw_init				= PE_WIN_HW_M17C0_Init;
			_g_pe_win_cb_fn.set_default			= NULL;//NULL;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_M17C0_SetDebugSettings;
		}
		else if (PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
		{
			_g_pe_win_cb_fn.hw_init				= PE_WIN_HW_M17_Init;
			_g_pe_win_cb_fn.set_default			= NULL;//NULL;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_M17_SetDebugSettings;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M19
		if (PE_KDRV_VER_M19)
		{
			_g_pe_win_cb_fn.hw_init				= PE_WIN_HW_M19_Init;
			_g_pe_win_cb_fn.set_default			= NULL;//NULL;
			_g_pe_win_cb_fn.set_debug			= PE_WIN_HW_M19_SetDebugSettings;
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
 * init pe window
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_win_cb_fn.hw_init)
		{
			ret = _g_pe_win_cb_fn.hw_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_init() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of win setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_WIN_SET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_WIN_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_WIN_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_WIN_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_WIN_SetDefaultSettings);
		PE_WIN_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_WIN_SetDebugSettings);
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
 * standard function of win getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_WIN_GET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_WIN_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
			PE_WIN_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
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
 * set default settings
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_WIN_DBG_PRINT("[win id:%d]\n", pstParams->win_id);
	}while (0);
	return ret;
}
/**
 * set debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_WIN_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if (pstParams->type&LX_PE_DBG_LV)
		{
			_g_win_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(WIN)))? 0x1:0x0;
		}
		if(_g_pe_win_cb_fn.set_debug)
		{
			ret = _g_pe_win_cb_fn.set_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_debug() error.\n");
		}
	}while (0);
	return ret;
}

