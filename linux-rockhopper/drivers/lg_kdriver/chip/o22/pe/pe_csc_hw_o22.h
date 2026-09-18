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

/** @file pe_csc_hw_o22.h
 *
 *  driver header for picture enhance csc functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CSC_HW_O22_H_
#define	_PE_CSC_HW_O22_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* 20191012, moved to fw setting(if fw ready)(AVTASK-399) */
#undef PE_CSC_HW_O22_SETTING_ON_DRV

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe hdr mode type enumeration
 */
typedef enum
{
	PE_CSC_HW_O22_HDR_OFF = 0,		///< off
	PE_CSC_HW_O22_HDR_ON_Y709,		///< hdr 709
	PE_CSC_HW_O22_HDR_ON_2020,		///< hdr 2020
	PE_CSC_HW_O22_HDR_DB_Y709,		///< dolby 709
	PE_CSC_HW_O22_HDR_DB_2020,		///< dolby 2020
	PE_CSC_HW_O22_HDR_NUM			///< max num
}
PE_CSC_HW_O22_HDR_TYPE;

/**
 *	pe pq mode csc type enumeration
 */
typedef enum
{
	PE_POST_CSC_HW_O22_Y601 = 0,	///< 601
	PE_POST_CSC_HW_O22_Y709,		///< 709
	PE_POST_CSC_HW_O22_BT2020,		///< 2020
	PE_POST_CSC_HW_O22_NUM,		///< 2020
}
PE_CSC_HW_O22_PQ_MODE_TYPE;


/**
 *	pe csc module settings type
 */
typedef struct
{
	UINT32 pre_post_type;			///< pre post type
	UINT32 cur_post_type;			///< cur post type
	LX_PE_CSC_INPUT_T pre_in_csc[LX_PE_WIN_ALL];///< pre input csc
	UINT32 ext_frc_mode;			///< external frc mode: 1:yes, 0:no frc
	UINT32 pre_dtm_type;			///< pre post type
	UINT32 cur_dtm_type;			///< cur post type
	UINT32 is_external_chip;		///< 60Hz or 120Hz model, 0:60Hz, 1:120Hz
}
PE_CSC_HW_O22_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_CSC_HW_O22_Init(PE_CFG_CTRL_T *pstParams);
int PE_CSC_HW_O22_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CSC_HW_O22_SetPostCsc(LX_PE_CSC_POST_T *pstParams);
int PE_CSC_HW_O22_GetPostCsc(LX_PE_CSC_POST_T *pstParams);
int PE_CSC_HW_O22_SetInputCsc(LX_PE_CSC_INPUT_T *pstParams);
int PE_CSC_HW_O22_GetInputCsc(LX_PE_CSC_INPUT_T *pstParams);
int PE_CSC_HW_O22_SetCscMode(PE_TSK_O22_CFG_T *pCfg);
int PE_CSC_HW_O22_SetLllut(LX_PE_CSC_LLLUT_CTRL_T *pstParams);
int PE_CSC_HW_O22_GetLllut(LX_PE_CSC_LLLUT_CTRL_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CSC_HW_O22_H_ */
