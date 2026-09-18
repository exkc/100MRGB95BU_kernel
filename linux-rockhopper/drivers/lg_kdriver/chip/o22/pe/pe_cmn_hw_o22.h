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

/** @file pe_cmn_hw_o22.h
 *
 *  driver header for picture enhance common functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CMN_HW_O22_H_
#define	_PE_CMN_HW_O22_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "pe_tsk_o22.h"
#include "de_kapi.h"
#include "pe_fwi_o22.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
* get db info type enum
* - SEC_XXX needs section type number
*/
typedef enum
{
	PE_CMN_HW_O22_DB_INF_IS_DB_INIT =  0, ///< is initialized or not
	PE_CMN_HW_O22_DB_INF_TOP_VERSION,     ///< top version
	PE_CMN_HW_O22_DB_INF_TOP_BASE,        ///< top base addr
	PE_CMN_HW_O22_DB_INF_TOP_SEC_NUM,     ///< top section total number
	PE_CMN_HW_O22_DB_INF_SEC_BASE,        ///< section base address
	PE_CMN_HW_O22_DB_INF_SEC_SIZE,        ///< section size
	PE_CMN_HW_O22_DB_INF_SEC_VERSION,     ///< section version
	PE_CMN_HW_O22_DB_INF_SEC_TYPE,        ///< section type
	PE_CMN_HW_O22_DB_INF_SEC_ITEM_NUM,    ///< section item total number
	PE_CMN_HW_O22_DB_INF_SEC_ITEM_SIZE,   ///< section item size
	PE_CMN_HW_O22_DB_INF_SEC_DATA_BASE,   ///< section data base
	PE_CMN_HW_O22_DB_INF_MD0_SHP_FW_EN,   ///< md0 shp fw en
	PE_CMN_HW_O22_DB_INF_MD0_HST_FW_EN,   ///< md0 hst fw en
	PE_CMN_HW_O22_DB_INF_MD0_SCL_FW_EN,   ///< md0 scl fw en
	PE_CMN_HW_O22_DB_INF_MD0_TNR_FW_EN,   ///< md0 tnr fw en
	PE_CMN_HW_O22_DB_INF_MD0_DNR_FW_EN,   ///< md0 dnr fw en
	PE_CMN_HW_O22_DB_INF_NUM              ///< max num
}
PE_CMN_HW_O22_DB_INF_TYPE;

/**
 *	pe common settings type
 */
typedef struct
{
	UINT32 pre_ihsv_v_gain;				///< pre_ihsv_v_gain
	UINT32 pre_ihsv_v_ofst;				///< pre_ihsv_v_ofst
	UINT32 cur_lvctrl_gain;				///< cur_lvctrl_gain
	UINT32 cur_lvctrl_ofst;				///< cur_lvctrl_ofst
	UINT32 pre_lvctrl_gain;				///< pre_lvctrl_gain
	UINT32 pre_lvctrl_ofst;				///< pre_lvctrl_ofst
	UINT32 dbg_print_lvl;				///< pe debug print level
	UINT32 dbg_bypass[LX_PE_WIN_NUM];	///< bypass each module
	UINT32 db_initialized;				///< db_initialized
	UINT32 db2_initialized;				///< db2_initialized
	UINT32 db_mode_data[1];				///< db_mode_data, see PE_DDR_O22_MD0_T 
	UINT32 lgsr_db_initialized;			///< lgsr_db_initialized
	UINT32 lgsr_db2_initialized;			///< lgsr_db2_initialized
}
PE_CMN_HW_O22_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_CMN_HW_O22_Init(PE_CFG_CTRL_T *pstParams);
int PE_CMN_HW_O22_GetMemInfo(unsigned int *base, unsigned int *size);
int PE_CMN_HW_O22_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CMN_HW_O22_GetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CMN_HW_O22_SetContrast(void *pstParams);
int PE_CMN_HW_O22_GetContrast(void *pstParams);
int PE_CMN_HW_O22_SetBrightness(void *pstParams);
int PE_CMN_HW_O22_GetBrightness(void *pstParams);
int PE_CMN_HW_O22_SetSaturation(LX_PE_CMN_SATURATION_T *pstParams);
int PE_CMN_HW_O22_GetSaturation(LX_PE_CMN_SATURATION_T *pstParams);
int PE_CMN_HW_O22_SetHue(LX_PE_CMN_HUE_T *pstParams);
int PE_CMN_HW_O22_GetHue(LX_PE_CMN_HUE_T *pstParams);
int PE_CMN_HW_O22_SetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams);
int PE_CMN_HW_O22_GetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams);
int PE_CMN_HW_O22_DownloadDb(PE_CFG_CTRL_T *pstParams);
int PE_CMN_O22_DownloadDbBin(LX_PE_ETC_TBL_T *pstParams);
int PE_CMN_O22_GetDownloadInfo(LX_PE_ETC_TBL_T *pstParams);
UINT32 PE_CMN_HW_O22_GetDbInfo(UINT32 inf_type, UINT32 sec_type);
UINT32 PE_CMN_HW_O22_SetDbInfo(UINT32 inf_type, UINT32 sec_type, UINT32 value);
int PE_CMN_HW_O22_SuspendModule(void);
int PE_CMN_HW_O22_ResumeModule(UINT32 enable);
int PE_CMN_HW_O22_SetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);
int PE_CMN_HW_O22_GetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);
int PE_CMN_HW_O22_SetVcpSaturationCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);
int PE_CMN_HW_O22_SetBypassBlock(LX_PE_CMN_BYPASS_BLOCKS_T *pstParams);
#if 0
int PE_CMN_HW_O22_DownloadLGSRDb(PE_CFG_CTRL_T *pstParams);
int PE_CMN_HW_O22F22_DownloadLGSRDb(PE_CFG_CTRL_T *pstParams);
#endif
int PE_LGSR_HW_O22_GetMemInfo(void *pstMem);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CMN_HW_O22_H_ */
