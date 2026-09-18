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

/** @file pe_nrd.c
 *
 *  driver for picture enhance noise reduction functions.
 *  ( used only within kdriver )
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
#include "pe_spd.h"
#include "pe_etc.h"
#include "pe_cmn.h"
#include "pe_nrd.h"
#include "pe_etc_hw.h"
#include "pe_nrd_hw.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_NRD_DBG_PRINT(fmt, args...)	\
	if (_g_nrd_trace)\
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
	int (*set_dnr_cmn)(void *pstParams);
	int (*get_dnr_cmn)(void *pstParams);
	int (*set_dnr2nd_cmn)(void *pstParams);
	int (*get_dnr2nd_cmn)(void *pstParams);
	int (*set_dnr_detail)(void *pstParams);
	int (*get_dnr_detail)(void *pstParams);
	int (*set_dnr2nd_detail)(void *pstParams);
	int (*set_dnr_dcnt_cmn)(void *pstParams);
	int (*get_dnr_dcnt_cmn)(void *pstParams);
	int (*set_dnr_dcnt2nd_cmn)(void *pstParams);
	int (*get_dnr_dcnt2nd_cmn)(void *pstParams);
	int (*set_dnr_dcnt_detail)(void *pstParams);
	int (*get_dnr_dcnt_detail)(void *pstParams);
	int (*set_dnr_dcnt2nd_detail)(void *pstParams);
	int (*set_tnr_cmn)(void *pstParams);
	int (*get_tnr_cmn)(void *pstParams);
	int (*set_tnr_detail)(void *pstParams);
	int (*get_tnr_detail)(void *pstParams);
	int (*set_tnr2nd_cmn)(void *pstParams);
	int (*get_tnr2nd_cmn)(void *pstParams);
	int (*set_tnr2nd_detail)(void *pstParams);
	int (*get_tnr2nd_detail)(void *pstParams);
	int (*set_tnr3rd_cmn)(void *pstParams);
	int (*get_tnr3rd_cmn)(void *pstParams);
	int (*set_tnr3rd_detail)(void *pstParams);
	int (*set_led_dcnt_cmn)(void *pstParams);
	int (*get_led_dcnt_cmn)(void *pstParams);
	int (*set_led_dcnt_detail)(void *pstParams);
	int (*get_led_dcnt_detail)(void *pstParams);
	int (*set_tnr_sqm_cmn)(void *pstParams);
	int (*get_tnr_sqm_cmn)(void *pstParams);
	int (*set_tnr2nd_sqm_cmn)(void *pstParams);
	int (*get_tnr2nd_sqm_cmn)(void *pstParams);
	int (*set_tnr3rd_sqm_cmn)(void *pstParams);
	int (*get_tnr3rd_sqm_cmn)(void *pstParams);
	int (*set_dnr_sqm_cmn)(void *pstParams);
	int (*get_dnr_sqm_cmn)(void *pstParams);
	int (*set_dnr2nd_sqm_cmn)(void *pstParams);
	int (*get_dnr2nd_sqm_cmn)(void *pstParams);
	int (*set_dnr_dcnt_sqm_cmn)(void *pstParams);
	int (*get_dnr_dcnt_sqm_cmn)(void *pstParams);
	int (*set_dnr_dcnt2nd_sqm_cmn)(void *pstParams);
	int (*get_dnr_dcnt2nd_sqm_cmn)(void *pstParams);
	int (*set_led_dcnt_sqm_cmn)(void *pstParams);
	int (*get_led_dcnt_sqm_cmn)(void *pstParams);
	int (*set_tnr_all)(void *pstParams);
	int (*set_dnr_all)(void *pstParams);
	int (*set_dnr_dcnt_all)(void *pstParams);
	int (*get_tnr_all)(void);
	int (*get_dnr_all)(void);
	int (*get_dnr_dcnt_all)(void);
	int (*set_tnr_face)(void *pstParams);
}
PE_NRD_CB_FUNC_T;

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
static PE_NRD_CB_FUNC_T _g_pe_nrd_cb_fn;
static UINT32 _g_nrd_trace=0x0;	//default should be off.

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
int PE_NRD_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_nrd_cb_fn, 0, sizeof(PE_NRD_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_O26_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_O26_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_O26_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_O26_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_O26_GetDnrUserDb;//PE_NRD_HW_O26_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr2nd_cmn		= PE_NRD_HW_O26_SetDnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr2nd_cmn		= PE_NRD_HW_O26_GetDnr2ndUserDb;//PE_NRD_HW_O26_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_O26_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_O26_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr2nd_detail	= PE_NRD_HW_O26_SetDnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn	= PE_NRD_HW_O26_SetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn	= PE_NRD_HW_O26_GetDnrDcntUserDb;//PE_NRD_HW_O26_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt2nd_cmn	= PE_NRD_HW_O26_SetDnrDcnt2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt2nd_cmn	= PE_NRD_HW_O26_GetDnrDcnt2ndUserDb;//PE_NRD_HW_O26_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_detail	= PE_NRD_HW_O26_SetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_detail	= PE_NRD_HW_O26_GetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt2nd_detail	= PE_NRD_HW_O26_SetDnrDcnt2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_O26_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_O26_GetTnrUserDb;//PE_NRD_HW_O26_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_O26_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_O26_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_O26_GetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_cmn		= PE_NRD_HW_O26_SetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_cmn		= PE_NRD_HW_O26_GetTnr2ndUserDb;//PE_NRD_HW_O26_GetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_detail	= PE_NRD_HW_O26_SetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_detail	= PE_NRD_HW_O26_GetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr3rd_cmn		= PE_NRD_HW_O26_SetTnr3rdCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr3rd_cmn		= PE_NRD_HW_O26_GetTnr3rdUserDb;
			_g_pe_nrd_cb_fn.set_tnr3rd_detail	= PE_NRD_HW_O26_SetTnr3rdDetailCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_cmn	= PE_NRD_HW_O26_SetCCODcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_cmn	= PE_NRD_HW_O26_GetCCODcntUserDb;//PE_NRD_HW_O26_GetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_detail	= PE_NRD_HW_O26_SetCCODcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_detail	= PE_NRD_HW_O26_GetCCODcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_sqm_cmn			= PE_NRD_HW_O26_SetTnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_sqm_cmn			= PE_NRD_HW_O26_GetTnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn		= PE_NRD_HW_O26_SetTnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_sqm_cmn		= PE_NRD_HW_O26_GetTnr2ndSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr3rd_sqm_cmn		= PE_NRD_HW_O26_SetTnr3rdSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr3rd_sqm_cmn		= PE_NRD_HW_O26_GetTnr3rdSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_sqm_cmn			= PE_NRD_HW_O26_SetDnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_sqm_cmn			= PE_NRD_HW_O26_GetDnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr2nd_sqm_cmn		= PE_NRD_HW_O26_SetDnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr2nd_sqm_cmn		= PE_NRD_HW_O26_GetDnr2ndSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O26_SetDnrDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O26_GetDnrDcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_dcnt2nd_sqm_cmn	= PE_NRD_HW_O26_SetDnrDcnt2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt2nd_sqm_cmn	= PE_NRD_HW_O26_GetDnrDcnt2ndSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_led_dcnt_sqm_cmn	= PE_NRD_HW_O26_SetCCODcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_sqm_cmn	= PE_NRD_HW_O26_GetCCODcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr_all			= NULL;//PE_NRD_HW_O26F22_SetTnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_tnr_all			= NULL;//PE_CHPI_TNR_HW_O26F22_GetCtrl;
			_g_pe_nrd_cb_fn.set_dnr_all			= NULL;//PE_NRD_HW_O26F22_SetDnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_dnr_all			= NULL;//PE_CHPI_DNR_HW_O26F22_GetCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_all		= NULL;//PE_NRD_HW_O26F22_SetDnrDcntCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_all		= NULL;//PE_CHPI_DNR_HW_O26F22_GetDcntCtrl;
			_g_pe_nrd_cb_fn.set_tnr_face			= PE_NRD_HW_O26_SetTnrFaceCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_O24_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_O24_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_O24_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_O24_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_O24_GetDnrUserDb;//PE_NRD_HW_O24_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_O24_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_O24_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn	= PE_NRD_HW_O24_SetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn	= PE_NRD_HW_O24_GetDnrDcntUserDb;//PE_NRD_HW_O24_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_detail	= PE_NRD_HW_O24_SetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_detail	= PE_NRD_HW_O24_GetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_O24_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_O24_GetTnrUserDb;//PE_NRD_HW_O24_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_O24_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_O24_GetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_cmn		= PE_NRD_HW_O24_SetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_cmn		= PE_NRD_HW_O24_GetTnr2ndUserDb;//PE_NRD_HW_O24_GetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_detail	= PE_NRD_HW_O24_SetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_detail	= PE_NRD_HW_O24_GetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_cmn	= PE_NRD_HW_O24_SetCCODcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_cmn	= PE_NRD_HW_O24_GetCCODcntUserDb;//PE_NRD_HW_O24_GetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_detail	= PE_NRD_HW_O24_SetCCODcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_detail	= PE_NRD_HW_O24_GetCCODcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_sqm_cmn			= PE_NRD_HW_O24_SetTnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_sqm_cmn			= PE_NRD_HW_O24_GetTnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn		= PE_NRD_HW_O24_SetTnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_sqm_cmn		= PE_NRD_HW_O24_GetTnr2ndSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_sqm_cmn			= PE_NRD_HW_O24_SetDnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_sqm_cmn			= PE_NRD_HW_O24_GetDnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O24_SetDnrDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O24_GetDnrDcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_led_dcnt_sqm_cmn	= PE_NRD_HW_O24_SetCCODcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_sqm_cmn	= PE_NRD_HW_O24_GetCCODcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr_all			= NULL;//PE_NRD_HW_O24F22_SetTnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_tnr_all			= NULL;//PE_CHPI_TNR_HW_O24F22_GetCtrl;
			_g_pe_nrd_cb_fn.set_dnr_all			= NULL;//PE_NRD_HW_O24F22_SetDnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_dnr_all			= NULL;//PE_CHPI_DNR_HW_O24F22_GetCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_all		= NULL;//PE_NRD_HW_O24F22_SetDnrDcntCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_all		= NULL;//PE_CHPI_DNR_HW_O24F22_GetDcntCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_M23_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_M23_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_M23_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_M23_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_M23_GetDnrUserDb;//PE_NRD_HW_M23_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_M23_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_M23_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn	= PE_NRD_HW_M23_SetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn	= PE_NRD_HW_M23_GetDnrDcntUserDb;//PE_NRD_HW_M23_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_detail	= PE_NRD_HW_M23_SetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_detail	= PE_NRD_HW_M23_GetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_M23_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_M23_GetTnrUserDb;//PE_NRD_HW_M23_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_M23_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_M23_GetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_cmn		= PE_NRD_HW_M23_SetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_cmn		= PE_NRD_HW_M23_GetTnr2ndUserDb;//PE_NRD_HW_M23_GetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_detail	= PE_NRD_HW_M23_SetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_detail	= PE_NRD_HW_M23_GetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_sqm_cmn			= PE_NRD_HW_M23_SetTnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_sqm_cmn			= PE_NRD_HW_M23_GetTnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn		= PE_NRD_HW_M23_SetTnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_sqm_cmn		= PE_NRD_HW_M23_GetTnr2ndSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_sqm_cmn			= PE_NRD_HW_M23_SetDnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_sqm_cmn			= PE_NRD_HW_M23_GetDnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn	= PE_NRD_HW_M23_SetDnrDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_sqm_cmn	= PE_NRD_HW_M23_GetDnrDcntSqmCmnUserDb;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_O22_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_O22_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_O22_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_O22_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_O22_GetDnrUserDb;//PE_NRD_HW_O22_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_O22_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_O22_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn	= PE_NRD_HW_O22_SetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn	= PE_NRD_HW_O22_GetDnrDcntUserDb;//PE_NRD_HW_O22_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_detail	= PE_NRD_HW_O22_SetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_detail	= PE_NRD_HW_O22_GetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_O22_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_O22_GetTnrUserDb;//PE_NRD_HW_O22_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_O22_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_O22_GetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_cmn		= PE_NRD_HW_O22_SetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_cmn		= PE_NRD_HW_O22_GetTnr2ndUserDb;//PE_NRD_HW_O22_GetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_detail	= PE_NRD_HW_O22_SetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_detail	= PE_NRD_HW_O22_GetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_cmn	= NULL;//PE_NRD_HW_O22_SetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_cmn	= NULL;//PE_NRD_HW_O22_GetLedDcntUserDb;//PE_NRD_HW_O22_GetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_detail	= NULL;//PE_NRD_HW_O22_SetLedDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_detail	= NULL;//PE_NRD_HW_O22_GetLedDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_sqm_cmn			= PE_NRD_HW_O22_SetTnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_sqm_cmn			= PE_NRD_HW_O22_GetTnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn		= PE_NRD_HW_O22_SetTnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_sqm_cmn		= PE_NRD_HW_O22_GetTnr2ndSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_sqm_cmn			= PE_NRD_HW_O22_SetDnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_sqm_cmn			= PE_NRD_HW_O22_GetDnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O22_SetDnrDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O22_GetDnrDcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_led_dcnt_sqm_cmn	= NULL;//PE_NRD_HW_O22_SetLedDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_sqm_cmn	= NULL;//PE_NRD_HW_O22_GetLedDcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr_all			= PE_NRD_HW_O22F22_SetTnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_tnr_all			= PE_CHPI_TNR_HW_O22F22_GetCtrl;
			_g_pe_nrd_cb_fn.set_dnr_all			= PE_NRD_HW_O22F22_SetDnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_dnr_all			= PE_CHPI_DNR_HW_O22F22_GetCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_all		= PE_NRD_HW_O22F22_SetDnrDcntCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_all		= PE_CHPI_DNR_HW_O22F22_GetDcntCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_E60_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_E60_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_E60_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_E60_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_E60_GetDnrUserDb;//PE_NRD_HW_E60_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_E60_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_E60_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn	= PE_NRD_HW_E60_SetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn	= PE_NRD_HW_E60_GetDnrDcntUserDb;//PE_NRD_HW_E60_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_detail	= PE_NRD_HW_E60_SetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_detail	= PE_NRD_HW_E60_GetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_E60_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_E60_GetTnrUserDb;//PE_NRD_HW_E60_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_E60_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_E60_GetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_cmn		= PE_NRD_HW_E60_SetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_cmn		= PE_NRD_HW_E60_GetTnr2ndUserDb;//PE_NRD_HW_E60_GetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_detail	= PE_NRD_HW_E60_SetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_detail	= PE_NRD_HW_E60_GetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_cmn	= PE_NRD_HW_E60_SetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_cmn	= PE_NRD_HW_E60_GetLedDcntUserDb;//PE_NRD_HW_E60_GetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_detail	= PE_NRD_HW_E60_SetLedDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_detail	= PE_NRD_HW_E60_GetLedDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_sqm_cmn			= PE_NRD_HW_E60_SetTnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_sqm_cmn			= PE_NRD_HW_E60_GetTnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn		= PE_NRD_HW_E60_SetTnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_sqm_cmn		= PE_NRD_HW_E60_GetTnr2ndSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_sqm_cmn			= PE_NRD_HW_E60_SetDnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_sqm_cmn			= PE_NRD_HW_E60_GetDnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn	= PE_NRD_HW_E60_SetDnrDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_sqm_cmn	= PE_NRD_HW_E60_GetDnrDcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_led_dcnt_sqm_cmn	= PE_NRD_HW_E60_SetLedDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_sqm_cmn	= PE_NRD_HW_E60_GetLedDcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr_all			= PE_NRD_HW_E60F20_SetTnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_tnr_all			= PE_CHPI_TNR_HW_E60F20_GetCtrl;
			_g_pe_nrd_cb_fn.set_dnr_all			= PE_NRD_HW_E60F20_SetDnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_dnr_all			= PE_CHPI_DNR_HW_E60F20_GetCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_all		= PE_NRD_HW_E60F20_SetDnrDcntCmnAllCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_all		= PE_CHPI_DNR_HW_E60F20_GetDcntCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_O20_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_O20_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_O20_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_O20_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_O20_GetDnrUserDb;//PE_NRD_HW_O20_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_O20_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_O20_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn	= PE_NRD_HW_O20_SetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn	= PE_NRD_HW_O20_GetDnrDcntUserDb;//PE_NRD_HW_O20_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_detail	= PE_NRD_HW_O20_SetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_detail	= PE_NRD_HW_O20_GetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_O20_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_O20_GetTnrUserDb;//PE_NRD_HW_O20_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_O20_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_O20_GetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_cmn		= PE_NRD_HW_O20_SetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_cmn		= PE_NRD_HW_O20_GetTnr2ndUserDb;//PE_NRD_HW_O20_GetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_detail	= PE_NRD_HW_O20_SetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_detail	= PE_NRD_HW_O20_GetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_cmn	= PE_NRD_HW_O20_SetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_cmn	= PE_NRD_HW_O20_GetLedDcntUserDb;//PE_NRD_HW_O20_GetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_detail	= PE_NRD_HW_O20_SetLedDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_detail	= PE_NRD_HW_O20_GetLedDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_sqm_cmn			= PE_NRD_HW_O20_SetTnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_sqm_cmn			= PE_NRD_HW_O20_GetTnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn		= PE_NRD_HW_O20_SetTnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_sqm_cmn		= PE_NRD_HW_O20_GetTnr2ndSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_sqm_cmn			= PE_NRD_HW_O20_SetDnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_sqm_cmn			= PE_NRD_HW_O20_GetDnrSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O20_SetDnrDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O20_GetDnrDcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_led_dcnt_sqm_cmn	= PE_NRD_HW_O20_SetLedDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_sqm_cmn	= PE_NRD_HW_O20_GetLedDcntSqmCmnUserDb;
			_g_pe_nrd_cb_fn.set_tnr_all			= PE_NRD_HW_F20_SetTnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.set_dnr_all			= PE_NRD_HW_F20_SetDnrCmnAllCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_all			= PE_NRD_HW_F20_SetDnrDcntCmnAllCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O18
		if (PE_KDRV_VER_O18)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_O18_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_O18_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_O18_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_O18_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_O18_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_O18_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_O18_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn	= PE_NRD_HW_O18_SetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn	= PE_NRD_HW_O18_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_detail	= PE_NRD_HW_O18_SetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_detail	= PE_NRD_HW_O18_GetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_O18_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_O18_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_O18_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_O18_GetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_cmn		= PE_NRD_HW_O18_SetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_cmn		= PE_NRD_HW_O18_GetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_detail	= PE_NRD_HW_O18_SetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_detail	= PE_NRD_HW_O18_GetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_cmn	= PE_NRD_HW_O18_SetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_cmn	= PE_NRD_HW_O18_GetLedDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_detail	= PE_NRD_HW_O18_SetLedDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_led_dcnt_detail	= PE_NRD_HW_O18_GetLedDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_sqm_cmn			= PE_NRD_HW_O18_SetTnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn		= PE_NRD_HW_O18_SetTnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_sqm_cmn			= PE_NRD_HW_O18_SetDnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn	= PE_NRD_HW_O18_SetDnrDcntSqmCmnCtrl;
			_g_pe_nrd_cb_fn.set_led_dcnt_sqm_cmn	= PE_NRD_HW_O18_SetLedDcntSqmCmnCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M17
		if (PE_KDRV_VER_M17CX)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_M17C0_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_M17C0_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_M17C0_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_M17C0_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_M17C0_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_M17C0_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_M17C0_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_M17C0_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_M17C0_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_M17C0_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_M17C0_GetTnrDetailCtrl;
		}
		else if (PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_M17_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_M17_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_M17_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_M17_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_M17_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_M17_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_M17_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_M17_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_M17_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_M17_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_M17_GetTnrDetailCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M19
		if (PE_KDRV_VER_M19)
		{
			_g_pe_nrd_cb_fn.hw_init				= PE_NRD_HW_M19_Init;
			_g_pe_nrd_cb_fn.set_default			= PE_NRD_HW_M19_SetDefault;
			_g_pe_nrd_cb_fn.set_debug			= PE_NRD_HW_M19_SetDebugSettings;
			_g_pe_nrd_cb_fn.set_dnr_cmn			= PE_NRD_HW_M19_SetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_cmn			= PE_NRD_HW_M19_GetDnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_detail		= PE_NRD_HW_M19_SetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_detail		= PE_NRD_HW_M19_GetDnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn	= PE_NRD_HW_M19_SetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn	= PE_NRD_HW_M19_GetDnrDcntCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_detail	= PE_NRD_HW_M19_SetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.get_dnr_dcnt_detail	= PE_NRD_HW_M19_GetDnrDcntDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_cmn			= PE_NRD_HW_M19_SetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr_cmn			= PE_NRD_HW_M19_GetTnrCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr_detail		= PE_NRD_HW_M19_SetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr_detail		= PE_NRD_HW_M19_GetTnrDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_cmn		= PE_NRD_HW_M19_SetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_cmn		= PE_NRD_HW_M19_GetTnr2ndCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_detail	= PE_NRD_HW_M19_SetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.get_tnr2nd_detail	= PE_NRD_HW_M19_GetTnr2ndDetailCtrl;
			_g_pe_nrd_cb_fn.set_tnr_sqm_cmn			= PE_NRD_HW_M19_SetTnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn		= PE_NRD_HW_M19_SetTnr2ndSqmCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_sqm_cmn			= PE_NRD_HW_M19_SetDnrSqmCmnCtrl;
			_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn	= PE_NRD_HW_M19_SetDnrDcntSqmCmnCtrl;
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
 * init nrd init
 * 	- h14, h13, l9 tnr alpha lut loading sequence
 *		: load time on -> tnr off -> loading alpha lut -> tnr on -> load time off
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.hw_init)
		{
			ret = _g_pe_nrd_cb_fn.hw_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_init() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of nrd setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_NRD_SET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		do{\
			PE_NRD_DBG_PRINT("S TABL %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size, 0, 16);\
			PE_CHECK_CODE(!bufsize, break, \
				"[%s,%d] bufsize zero.\n", __F__, __L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CHECK_CODE(!p_data, break, \
				"[%s,%d] p_data is null.\n", __F__, __L__);\
			ret = copy_from_user(p_data, (void __user *)p_rcv->data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_from_user error.\n", __F__, __L__);\
			param.win_id = p_rcv->win_id;\
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_NRD_DBG_PRINT("E TABL %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

#define PE_NRD_SET_FUNC(_struct, _func, _void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_NRD_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_NRD_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_NRD_SET_FUNC(LX_PE_NRD_SUDO_DNR_CMN_T,	PE_NRD_SetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR6_CMN_T,		PE_NRD_SetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR7_CMN_T,		PE_NRD_SetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR8_CMN_T,		PE_NRD_SetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR9_CMN_T,		PE_NRD_SetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR5_DETAIL_T,	PE_NRD_SetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR6_DETAIL_T,	PE_NRD_SetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR7_DETAIL_T,	PE_NRD_SetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR8_DETAIL_T,	PE_NRD_SetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_DNR9_DETAIL_T,	PE_NRD_SetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR5_CMN_T,		PE_NRD_SetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR6_CMN_T,		PE_NRD_SetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR7_CMN_T,		PE_NRD_SetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR8_CMN_T,		PE_NRD_SetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR5_DETAIL_T,	PE_NRD_SetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR6_DETAIL_T,	PE_NRD_SetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR7_DETAIL_T,	PE_NRD_SetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR2ND1_CMN_T,	PE_NRD_SetTnr2ndCmnCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_NRD_TNR2ND1_DETAIL_T,	PE_NRD_SetTnr2ndDetailCtrl,	_VOID___INPUT_);
		PE_NRD_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_NRD_SetDefaultSettings,	_STRUCT_INPUT_);
		PE_NRD_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_NRD_SetDebugSettings,	_STRUCT_INPUT_);
		PE_NRD_SET_TABL(LX_PE_NRD_DNR_CMN_T,		PE_NRD_SetDnrCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_DNR_DETAIL_T,		PE_NRD_SetDnrDetailCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_DCNT_CMN_T,		PE_NRD_SetDnrDcntCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_DCNT_DETAIL_T,	PE_NRD_SetDnrDcntDetailCtrl);
		PE_NRD_SET_TABL(LX_PE_LED_DCNT_CMN_T,		PE_NRD_SetLedDcntCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_LED_DCNT_DETAIL_T,	PE_NRD_SetLedDcntDetailCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_TNR_CMN_T,		PE_NRD_SetTnrCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_TNR_DETAIL_T,		PE_NRD_SetTnrDetailCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_TNR2ND_CMN_T,		PE_NRD_SetTnr2ndCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_TNR2ND_DETAIL_T,	PE_NRD_SetTnr2ndDetailCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_DNR_SQM_CMN_T,	PE_NRD_SetDnrSqmCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_TNR_SQM_CMN_T,	PE_NRD_SetTnrSqmCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_TNR2ND_SQM_CMN_T,	PE_NRD_SetTnr2ndSqmCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_NRD_DCNT_SQM_CMN_T,	PE_NRD_SetDnrDcntSqmCmnCtrl);
		PE_NRD_SET_TABL(LX_PE_LED_DCNT_SQM_CMN_T,	PE_NRD_SetLedDcntSqmCmnCtrl);
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
 * standard function of nrd getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in/out] unsigned int
 * @param   datasize [in/out] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_NRD_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define _VOID___INPUT_		1
#define _STRUCT_INPUT_		0

#define PE_NRD_GET_FUNC(_struct, _func, _void_input)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_NRD_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = (_void_input)? (_func((void *)&param)):(_func(&param));\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
			PE_NRD_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

#define PE_NRD_GET_TABL(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_NRD_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			bufsize = GET_BITS(p_rcv->size, 0, 16);\
			PE_CHECK_CODE(!bufsize, break, \
				"[%s,%d] bufsize zero.\n", __F__, __L__);\
			p_data = OS_Malloc(bufsize);\
			PE_CHECK_CODE(!p_data, break, \
				"[%s,%d] p_data is null.\n", __F__, __L__);\
			param.win_id = p_rcv->win_id;\
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_to_user error.\n", __F__, __L__);\
			PE_NRD_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

/* get table all(including ret size) */
#define PE_NRD_GET_TBLA(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		UINT32 *p_data = NULL;\
		UINT32 bufsize;\
		memset0(param);\
		do{\
			PE_NRD_DBG_PRINT("S %s\n", #_struct);\
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
			param.oper = p_rcv->oper;\
			param.size = p_rcv->size;\
			param.data = p_data;\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			ret = copy_to_user((void __user *)p_rcv->data, p_data, bufsize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] copy_to_user error.\n", __F__, __L__);\
			p_rcv->oper = param.oper;\
			p_rcv->size = param.size;\
			PE_NRD_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
		if (p_data){OS_Free(p_data);}\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch (functype)
	{
		PE_NRD_GET_FUNC(LX_PE_NRD_SUDO_DNR_CMN_T,	PE_NRD_GetDnrCmnCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR6_CMN_T,		PE_NRD_GetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR7_CMN_T,		PE_NRD_GetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR8_CMN_T,		PE_NRD_GetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR9_CMN_T,		PE_NRD_GetDnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR5_DETAIL_T,	PE_NRD_GetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR6_DETAIL_T,	PE_NRD_GetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR7_DETAIL_T,	PE_NRD_GetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR8_DETAIL_T,	PE_NRD_GetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_DNR9_DETAIL_T,	PE_NRD_GetDnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR5_CMN_T,		PE_NRD_GetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR6_CMN_T,		PE_NRD_GetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR7_CMN_T,		PE_NRD_GetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR8_CMN_T,		PE_NRD_GetTnrCmnCtrl,		_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR5_DETAIL_T,	PE_NRD_GetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR6_DETAIL_T,	PE_NRD_GetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR7_DETAIL_T,	PE_NRD_GetTnrDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR2ND1_CMN_T,	PE_NRD_GetTnr2ndCmnCtrl,	_VOID___INPUT_);
		PE_NRD_GET_FUNC(LX_PE_NRD_TNR2ND1_DETAIL_T,	PE_NRD_GetTnr2ndDetailCtrl,	_VOID___INPUT_);
		PE_NRD_GET_TABL(LX_PE_NRD_DNR_CMN_T,		PE_NRD_GetDnrCmnCtrl);
		PE_NRD_GET_TABL(LX_PE_NRD_DNR_DETAIL_T,		PE_NRD_GetDnrDetailCtrl);
		PE_NRD_GET_TABL(LX_PE_NRD_DCNT_CMN_T,		PE_NRD_GetDnrDcntCmnCtrl);
		PE_NRD_GET_TABL(LX_PE_NRD_DCNT_DETAIL_T,	PE_NRD_GetDnrDcntDetailCtrl);
		PE_NRD_GET_TABL(LX_PE_LED_DCNT_CMN_T,		PE_NRD_GetLedDcntCmnCtrl);
		PE_NRD_GET_TABL(LX_PE_LED_DCNT_DETAIL_T,	PE_NRD_GetLedDcntDetailCtrl);
		PE_NRD_GET_TABL(LX_PE_NRD_TNR_CMN_T,		PE_NRD_GetTnrCmnCtrl);
		PE_NRD_GET_TABL(LX_PE_NRD_TNR_DETAIL_T,		PE_NRD_GetTnrDetailCtrl);
		PE_NRD_GET_TABL(LX_PE_NRD_TNR2ND_CMN_T,		PE_NRD_GetTnr2ndCmnCtrl);
		PE_NRD_GET_TABL(LX_PE_NRD_TNR2ND_DETAIL_T,	PE_NRD_GetTnr2ndDetailCtrl);
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
int PE_NRD_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_default)
		{
			ret = _g_pe_nrd_cb_fn.set_default(pstParams);
			PE_CHECK_CODE(ret, break, "set_default() error.\n");
		}
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
int PE_NRD_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if (pstParams->type&LX_PE_DBG_LV)
		{
			_g_nrd_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(NRD)))? 0x1:0x0;
		}
		if(_g_pe_nrd_cb_fn.set_debug)
		{
			ret = _g_pe_nrd_cb_fn.set_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_debug() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dnr common ctrl
 * - use input struct LX_PE_NRD_DNR1_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr common ctrl
 * - use input struct LX_PE_NRD_DNR1_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dnr2nd common ctrl
 * - use input struct LX_PE_NRD_DNR1_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr2nd_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr2nd_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr2nd_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr common ctrl
 * - use input struct LX_PE_NRD_DNR1_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr2nd_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr2nd_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr2nd_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dnr common ctrl
 * - use input struct LX_PE_NRD_DCNT1_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_dcnt_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_dcnt_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_dcnt_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr common ctrl
 * - use input struct LX_PE_NRD_DCNT1_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_dcnt_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_dcnt_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr_dcnt_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dcnt2nd common ctrl
 * - use input struct LX_PE_NRD_DCNT1_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrDcnt2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_dcnt2nd_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_dcnt2nd_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_dcnt2nd_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dcnt2nd common ctrl
 * - use input struct LX_PE_NRD_DCNT1_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrDcnt2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_dcnt2nd_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_dcnt2nd_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr_dcnt2nd_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dnr common ctrl
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetLedDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_led_dcnt_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_led_dcnt_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_led_dcnt_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr common ctrl
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetLedDcntCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_led_dcnt_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_led_dcnt_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_led_dcnt_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR1_DETAIL_T for O18 webOS4.5
 * - use input struct LX_PE_NRD_DNR2_DETAIL_T for M16P3 webOS4.5
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_detail)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_detail(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR1_DETAIL_T for O18 webOS4.5
 * - use input struct LX_PE_NRD_DNR2_DETAIL_T for M16P3 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_detail)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_detail(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dnr2nd detail ctrl
 * - use input struct LX_PE_NRD_DNR1_DETAIL_T for O18 webOS4.5
 * - use input struct LX_PE_NRD_DNR2_DETAIL_T for M16P3 webOS4.5
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnr2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr2nd_detail)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr2nd_detail(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr2nd_detail() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR1_DETAIL_T for O18 webOS4.5
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_dcnt_detail)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_dcnt_detail(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dcnt detail ctrl
 * - use input struct LX_PE_NRD_DNR1_DETAIL_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_dcnt_detail)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_dcnt_detail(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dcnt2nd detail ctrl
 * - use input struct LX_PE_NRD_DNR1_DETAIL_T for O18 webOS4.5
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrDcnt2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_dcnt2nd_detail)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_dcnt2nd_detail(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_dcnt2nd_detail() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR2_DETAIL_T for O18
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetLedDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_led_dcnt_detail)
		{
			ret = _g_pe_nrd_cb_fn.set_led_dcnt_detail(pstParams);
			PE_CHECK_CODE(ret, break, "set_led_dcnt_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr detail ctrl
 * - use input struct LX_PE_NRD_DNR2_DETAIL_T for O18
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetLedDcntDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_led_dcnt_detail)
		{
			ret = _g_pe_nrd_cb_fn.get_led_dcnt_detail(pstParams);
			PE_CHECK_CODE(ret, break, "get_led_dcnt_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set tnr face ctrl
 * - use input struct LX_PE_NRD_TNR3_CMN_T for H14A
 * - use input struct LX_PE_NRD_TNR2_CMN_T for H13BX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnrFaceCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr_face)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr_face(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr_face() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set tnr common ctrl
 * - use input struct LX_PE_NRD_TNR3_CMN_T for H14A
 * - use input struct LX_PE_NRD_TNR2_CMN_T for H13BX
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get tnr common ctrl
 * - use input struct LX_PE_NRD_TNR3_CMN_T for H14A
 * - use input struct LX_PE_NRD_TNR2_CMN_T for H13BX
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnrCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_tnr_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR7DETAIL_T for O18
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr_detail)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr_detail(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR7DETAIL_T for O18
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnrDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr_detail)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr_detail(pstParams);
			PE_CHECK_CODE(ret, break, "get_tnr_detail() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set tnr common ctrl
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr2nd_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr2nd_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get tnr common ctrl
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnr2ndCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr2nd_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr2nd_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_tnr2nd_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR2ND1_DETAIL_T for O18
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnr2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr2nd_detail)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr2nd_detail(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr2nd_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR2ND1_DETAIL_T for O18
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnr2ndDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr2nd_detail)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr2nd_detail(pstParams);
			PE_CHECK_CODE(ret, break, "get_tnr_detail() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set tnr common ctrl
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnr3rdCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr3rd_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr3rd_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set tnr common ctrl
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnr3rdCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr3rd_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr3rd_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_tnr3rd_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set tnr detail ctrl
 * - use input struct LX_PE_NRD_TNR2ND1_DETAIL_T for O18
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnr3rdDetailCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr3rd_detail)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr3rd_detail(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr_detail() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dnr sqm cmn ctrl
 * - use input struct LX_PE_NRD_DNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr sqm cmn ctrl
 * - use input struct LX_PE_NRD_DNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dnr2nd sqm cmn ctrl
 * - use input struct LX_PE_NRD_DNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnr2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr2nd_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr2nd_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr2nd_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr2nd sqm cmn ctrl
 * - use input struct LX_PE_NRD_DNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnr2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr2nd_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr2nd_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr2nd_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set tnr sqm cmn ctrl
 * - use input struct LX_PE_NRD_TNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnrSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get tnr sqm cmn ctrl
 * - use input struct LX_PE_NRD_TNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnrSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_tnr_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set tnr2nd sqm cmn ctrl
 * - use input struct LX_PE_NRD_TNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnr2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr2nd_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr2nd_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get tnr2nd sqm cmn ctrl
 * - use input struct LX_PE_NRD_TNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnr2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr2nd_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr2nd_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_tnr2nd_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set tnr3rd sqm cmn ctrl
 * - use input struct LX_PE_NRD_TNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnr3rdSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr3rd_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr3rd_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr3rd_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get tnr3rd sqm cmn ctrl
 * - use input struct LX_PE_NRD_TNR_SQM_CMN_T for  O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnr3rdSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr3rd_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr3rd_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_tnr3rd_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}


/**
 * set dnr dcnt sqm cmn ctrl
 * - use input struct LX_PE_NRD_DCNT_SQM_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrDcntSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_dcnt_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_dcnt_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr dcnt sqm cmn ctrl
 * - use input struct LX_PE_NRD_DCNT_SQM_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrDcntSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_dcnt_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_dcnt_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr_dcnt_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set dnr dcnt2nd sqm cmn ctrl
 * - use input struct LX_PE_NRD_DCNT_SQM_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrDcnt2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_dcnt2nd_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_dcnt2nd_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_dcnt2nd_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr dcnt2nd sqm cmn ctrl
 * - use input struct LX_PE_NRD_DCNT_SQM_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrDcnt2ndSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_dcnt2nd_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_dcnt2nd_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_dnr_dcnt2nd_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * set led dcnt sqm cmn ctrl
 * - use input struct LX_PE_LED_DCNT_SQM_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetLedDcntSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_led_dcnt_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.set_led_dcnt_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "set_led_dcnt_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get led dcnt sqm cmn ctrl
 * - use input struct LX_PE_LED_DCNT_SQM_CMN_T for O18 webOS4.5
 *
 * @param   *pstParams [in/out] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetLedDcntSqmCmnCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_led_dcnt_sqm_cmn)
		{
			ret = _g_pe_nrd_cb_fn.get_led_dcnt_sqm_cmn(pstParams);
			PE_CHECK_CODE(ret, break, "get_led_dcnt_sqm_cmn() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set tnr common all ctrl
 * - use input struct LX_PE_NRD_TNR_ALL_CMN_T for F20
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetTnrCmnAllCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_tnr_all)
		{
			ret = _g_pe_nrd_cb_fn.set_tnr_all(pstParams);
			PE_CHECK_CODE(ret, break, "set_tnr_all() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dnr common all ctrl
 * - use input struct LX_PE_NRD_DNR_ALL_CMN_T for F20
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrCmnAllCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_all)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_all(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_all() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set dnr common all ctrl
 * - use input struct LX_PE_NRD_DCT_ALL_CMN_T for F20
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_SetDnrDcntCmnAllCtrl(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.set_dnr_dcnt_all)
		{
			ret = _g_pe_nrd_cb_fn.set_dnr_dcnt_all(pstParams);
			PE_CHECK_CODE(ret, break, "set_dnr_dcnt_all() error.\n");
		}
	}while (0);
	return ret;
}


/**
 * get tnr common all ctrl
 * - use input struct LX_PE_NRD_TNR_ALL_CMN_T for F20
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetTnrCmnAllCtrl(void)
{
	int ret = RET_OK;
	do{
		//CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_tnr_all)
		{
			ret = _g_pe_nrd_cb_fn.get_tnr_all();
			PE_CHECK_CODE(ret, break, "get_tnr_all() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr common all ctrl
 * - use input struct LX_PE_NRD_DNR_ALL_CMN_T for F20
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrCmnAllCtrl(void)
{
	int ret = RET_OK;
	do{
		//CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_all)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_all();
			PE_CHECK_CODE(ret, break, "get_dnr_all() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get dnr common all ctrl
 * - use input struct LX_PE_NRD_DCT_ALL_CMN_T for F20
 *
 * @param   *pstParams [in] void
 * @return  OK if success, ERROR otherwise.
 * @see		set discription
 * @author
 */
int PE_NRD_GetDnrDcntCmnAllCtrl(void)
{
	int ret = RET_OK;
	do{
		//CHECK_KNULL(pstParams);
		if(_g_pe_nrd_cb_fn.get_dnr_dcnt_all)
		{
			ret = _g_pe_nrd_cb_fn.get_dnr_dcnt_all();
			PE_CHECK_CODE(ret, break, "get_dnr_dcnt_all() error.\n");
		}
	}while (0);
	return ret;
}

