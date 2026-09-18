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

/** @file pe_tsk_e60.h
 *
 *  task func. for picture enhance. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.09
 *	@see
 */

#ifndef	_PE_TSK_E60_H_
#define	_PE_TSK_E60_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "pe_inf_e60.h"
#include "de_sync.h"

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
 *	pe task time mode
 */
typedef enum
{
	PE_TSK_E60_RUN_START = 0,	///< run start
	PE_TSK_E60_RUN_STOP_TASK,	///< run stop task
	PE_TSK_E60_RUN_STOP_HDLR,	///< run stop handler
	PE_TSK_E60_RUN_STOP_OVWR,	///< run stop overwrite
	PE_TSK_E60_RUN_STOP_ALGO,	///< run stop algorithm
	PE_TSK_E60_RUN_STOP_MODE,	///< run stop mode
	PE_TSK_E60_RUN_STOP_WIN2,	///< run stop win2
	PE_TSK_E60_RUN_TEST_TASK,	///< use task(force)
	PE_TSK_E60_RUN_NUM			///< max num
}
PE_TSK_E60_OPR_RUN_MODE;

/**
 *	pe task debug mode
 */
typedef enum
{
	PE_TSK_E60_DBG_OFF = 0,		///< off
	PE_TSK_E60_DBG_ON,			///< on
	PE_TSK_E60_DBG_TIME,		///< time check
	PE_TSK_E60_DBG_CNT,			///< count check
	PE_TSK_E60_DBG_BRK,			///< break check
	PE_TSK_E60_DBG_MAX			///< max num
}
PE_TSK_E60_OPR_DBG_MODE;

/**
 *	pe task time mode
 */
typedef enum
{
	PE_TSK_E60_TIME_TASK = 0,	///< task time
	PE_TSK_E60_TIME_HNDL,		///< handler time
	PE_TSK_E60_TIME_MAX			///< max num
}
PE_TSK_E60_TIME;

/**
 *	pe task e60 operation type
 */
typedef struct
{
	UINT32 pause_task;		///< 1:pause, 0:task run
	UINT32 timeout;			///< task timeout, msec
	UINT32 dbgmode;			///< debug mode
}
PE_TSK_E60_OPR_T;

/**
 *	pe task e60 handler operation type
 */
typedef struct
{
	UINT32 is_registered;		///< is registered
	UINT32 count;				///< count
	UINT32 cur_time;			///< current time
	UINT32 pre_time;			///< previous time
	UINT32 time_dif;			///< time diff
}
PE_TSK_E60_HDLR_OPR_T;

/**
 *	pe lrcr histo control type
 */
typedef struct
{
	UINT32 win_mod;			///< window mode, see PE_HST_HW_E60_LRC_HST_WIN_MOD
	UINT32 tb0_t_pos[4];	///< tb0 t position, [0]x0,[1]y0,[2]x1,[3]y1
	UINT32 tb0_b_pos[4];	///< tb0 b position, [0]x0,[1]y0,[2]x1,[3]y1
	UINT32 tb1_t_pos[4];	///< tb1 t position, [0]x0,[1]y0,[2]x1,[3]y1
	UINT32 tb1_b_pos[4];	///< tb1 b position, [0]x0,[1]y0,[2]x1,[3]y1
	UINT32 ss0_l_pos[4];	///< ss0 l position, [0]x0,[1]y0,[2]x1,[3]y1
	UINT32 ss0_r_pos[4];	///< ss0 r position, [0]x0,[1]y0,[2]x1,[3]y1
	UINT32 ss1_l_pos[4];	///< ss1 l position, [0]x0,[1]y0,[2]x1,[3]y1
	UINT32 ss1_r_pos[4];	///< ss1 r position, [0]x0,[1]y0,[2]x1,[3]y1
	UINT32 pxl_cnt[4];		///< pixel count, [0]tb0,[1]ss0,[2]tb1,[3]ss1
}
PE_TSK_E60_LRC_HST_CTRL_T;

/**
 *	pe task e60 cfg type
 */
typedef struct {
	PE_INF_E60_SETTINGS_T inf;			///< info
	PE_TSK_E60_OPR_T opr;				///< operation mode
	PE_TSK_E60_HDLR_OPR_T hdlr_opr;		///< handler operation mode
	PE_TSK_E60_LRC_HST_CTRL_T lrc;		///< lrcr ctrl
}
PE_TSK_E60_CFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_TSK_E60_SuspendModule(UINT32 onOff);
int PE_TSK_E60_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_TSK_E60_SetTaskOperation(LX_PE_ETC_TBL_T *pstParams);
int PE_TSK_E60_GetTaskOperation(LX_PE_ETC_TBL_T *pstParams);
int PE_TSK_E60_CreatePicTask(void);
int PE_TSK_E60_StartPicTask(PE_CFG_CTRL_T *pstParams);
int PE_TSK_E60_StopPicTask(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_TSK_E60_H_ */
