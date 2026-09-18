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

/** @file pe_tsk_hw_m23.c
 *
 *  task func. for picture enhance. ( used only within kdriver )
 *
 *	@author			Seung-Jun,Youm(sj.youm@lge.com)
 *  @modifier		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *	@version		0.1
 *	@note
 *	@date			2012.04.12
 *  @modified date  2015.05.26 for SWMD
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_hw_m23.h"
#include "pe_tsk_m23.h"
#include "pe_fwi_m23.h"
#include "pe_reg_m23.h"
#include "pe_win_hw_m23.h"
#include "pe_shp_hw_m23.h"
#include "pe_dcm_hw_m23.h"
#include "pe_hst_hw_m23.h"
#include "pe_cmn_hw_m23.h"
#include "pe_dnt_hw_m23.h"
#include "pe_nrd_hw_m23.h"
#include "pe_csc_hw_m23.h"
#include "pe_hdr_hw_m23.h"
#include "pe_cmg_hw_m23.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_TSK_M23_TIME_START		(0)
#define PE_TSK_M23_TIME_END			(1)
#define PE_TSK_M23_HDLR_MIN_MSEC	(10)

/* handler count loop max(0~10003) */
#define PE_TSK_M23_HDL_CNT_LOOP_MAX		(10003)

/* check skip handler count number (120hz:0x3, 60hz:0x1, 30hz:0x0)*/
#define PE_TSK_M23_CHK_SKIP_HDL_CNT_NUM		(0x1)

/* check increase handler count number(120hz:0x3f, 60hz:0x1f, 30hz:0xf) */
#define PE_TSK_M23_CHK_INC_HDL_CNT_NUM		(0x1f)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_TSK_M23_CHECK_CODE(_checker,_action,fmt,args...)	\
	{if(_checker){PE_PRINT_ERROR(fmt,##args);_action;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe task elapsed time info type
 */
typedef struct
{
	UINT32 tick_start_time[PE_TSK_M23_TIME_MAX];	///< start time
	UINT32 tick_end_time[PE_TSK_M23_TIME_MAX];		///< end time
}
PE_TSK_M23_TIME_INFO_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

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
static int PE_TSK_M23_CheckTime(char *fn_str, PE_TSK_M23_TIME location, UINT32 pos);
static int PE_TSK_M23_PicTask(void *data);
static int PE_TSK_M23_PicSyncHandler(void);
static int PE_TSK_M23_PicPeriodicProcess(PE_TSK_M23_CFG_T *pCfg);
static int PE_TSK_M23_PicSetWinCmnCcmHstFwiDcm(PE_TSK_M23_CFG_T *pCfg);
static int PE_TSK_M23_PicSetModes(PE_TSK_M23_CFG_T *pCfg);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static DECLARE_WAIT_QUEUE_HEAD(_wq_pe_m23);
static struct task_struct *g_pstPeTaskM23 = NULL;
static OS_SEM_T	_g_pe_tsk_m23_sem;
static UINT32 _g_pe_tsk_m23_trace=0x0;		//default should be off.
static PE_TSK_M23_CFG_T _g_pe_tsk_m23_cfg;
static UINT32 _g_pe_tsk_m23_started=0x0;	//started value for resume
static UINT32 _g_pe_tsk_m23_resume=0x0;		//1:suspend started, 0:resume/normal
/* check skip handler count number (120hz:0x3, 60hz:0x1, 30hz:0x0)*/
static UINT32 _g_pe_tsk_m23_skip_hdl_cnt_num =0x1;
static UINT32 _g_pe_tsk_m23_hdl_min_msec =0xa;


/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * set task suspend
 *
 * @param   onOff [in] UINT32
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_TSK_M23_SuspendModule(UINT32 onOff)
{
	_g_pe_tsk_m23_resume = onOff;
	PE_PRINT_NOTI("set _g_pe_tsk_m23_resume:%d\n",_g_pe_tsk_m23_resume);
	return RET_OK;
}
/**
 * debug setting
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_TSK_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_pe_tsk_m23_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(ETC)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(ETC)),\
			pstParams->print_lvl,_g_pe_tsk_m23_trace,pstParams->bypass);
	}while(0);
	return ret;
}
/**
 * set task operation
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  void
 * @see     PE_TSK_M23_OPR_T
 * @author
 */
int PE_TSK_M23_SetTaskOperation(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	static UINT32 pre_registered = 0xff;
	PE_TSK_M23_HDLR_OPR_T *pHdlrCfg = &_g_pe_tsk_m23_cfg.hdlr_opr;
	PE_TSK_M23_OPR_T *pOpr = &_g_pe_tsk_m23_cfg.opr;
	do {
		CHECK_KNULL(pstParams);
		PE_TSK_M23_CHECK_CODE((sizeof(UINT32)*pstParams->size)!=sizeof(PE_TSK_M23_OPR_T),break,"size mismatch.\n");
		/* start task */
		if((pOpr->pause_task==PE_TSK_M23_RUN_STOP_TASK) && \
			(pstParams->data[0]==PE_TSK_M23_RUN_START))
		{
			pOpr->pause_task=PE_TSK_M23_RUN_START;
			wake_up_interruptible(&_wq_pe_m23);
			PE_PRINT_NOTI("re-start pic_task.\n");
		}
		/* use task(force) */
		if (pstParams->data[0]==PE_TSK_M23_RUN_TEST_TASK)
		{
			pre_registered = pHdlrCfg->is_registered;
			pHdlrCfg->is_registered = FALSE;
		}
		else if ((pOpr->pause_task==PE_TSK_M23_RUN_TEST_TASK) && \
			(pstParams->data[0]!=PE_TSK_M23_RUN_TEST_TASK))
		{
			pHdlrCfg->is_registered = pre_registered;
		}
		PE_DBG_TSK("pause,time,dbg_md,reg_hdlr:%d,%d,%d,%d <- %d,%d,%d,%d\n", \
			pOpr->pause_task,pOpr->timeout,pOpr->dbgmode,pHdlrCfg->is_registered,\
			pstParams->data[0],pstParams->data[1],pstParams->data[2],pre_registered);
		memcpy(pOpr,&pstParams->data[0],sizeof(PE_TSK_M23_OPR_T));
	} while(0);
	return ret;
}
/**
 * get task operation
 *
 * @param   *pstParams [in/out] LX_PE_ETC_TBL_T
 * @return  void
 * @see     PE_TSK_M23_OPR_T
 * @author
 */
int PE_TSK_M23_GetTaskOperation(LX_PE_ETC_TBL_T *pstParams)
{
	int ret = RET_OK;
	PE_TSK_M23_HDLR_OPR_T *pHdlrCfg = &_g_pe_tsk_m23_cfg.hdlr_opr;
	PE_TSK_M23_OPR_T *pOpr = &_g_pe_tsk_m23_cfg.opr;
	do{
		CHECK_KNULL(pstParams);
		PE_TSK_M23_CHECK_CODE((sizeof(UINT32)*pstParams->size)!=sizeof(PE_TSK_M23_OPR_T),break,"size mismatch.\n");
		memcpy(&pstParams->data[0],pOpr,sizeof(PE_TSK_M23_OPR_T));
		PE_DBG_TSK("pause,time,dbg_md,reg_hdlr:%d,%d,%d,%d\n", \
			pOpr->pause_task,pOpr->timeout,pOpr->dbgmode,pHdlrCfg->is_registered);
	}while(0);
	return ret;
}
/**
 * create pe m23 task
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_TSK_M23_CreatePicTask(void)
{
	int ret = RET_OK;
	do{
		if(g_pstPeTaskM23)
		{
			PE_PRINT_NOTI("pic_task is already created.\n");
			ret = RET_OK;
			break;
		}
		g_pstPeTaskM23 = kthread_create(PE_TSK_M23_PicTask, (void *)NULL, "pe_thread_m23");
		if(g_pstPeTaskM23)
		{
			PE_PRINT_NOTI("pic_task is created successfully.\n");
		}
		else
		{
			PE_PRINT_NOTI("pic_task creation fail.\n");
			ret = RET_ERROR;
			break;
		}
	}while(0);
	return ret;
}
/**
 * start pe m23 task
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_TSK_M23_StartPicTask(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	int hdlr_num = -1;
	PE_TSK_M23_CFG_T *pCfg = &_g_pe_tsk_m23_cfg;
	do{
		CHECK_KNULL(pstParams);
		OS_InitMutex(&_g_pe_tsk_m23_sem, OS_SEM_ATTR_DEFAULT);

		_g_pe_tsk_m23_skip_hdl_cnt_num = 0x3;//TODO:adjust for 60hz
		_g_pe_tsk_m23_hdl_min_msec = 0x5;

		if(g_pstPeTaskM23)
		{
			if (!_g_pe_tsk_m23_started)
			{
				memset0(_g_pe_tsk_m23_cfg);
				pCfg->opr.pause_task = PE_TSK_M23_RUN_START;
				pCfg->opr.dbgmode = PE_TSK_M23_DBG_OFF;

				pCfg->opr.timeout = 1000;
				if(pCfg->hdlr_opr.is_registered == FALSE)
				{
					#ifdef INCLUDE_KDRV_DE
					hdlr_num = de_sync_register(TRUE,PE_TSK_M23_PicSyncHandler,TO_STR(PE_TSK_M23_PicSyncHandler));
					#endif
					PE_PRINT_NOTI("sync_hadler number : %d\n", hdlr_num);
					pCfg->hdlr_opr.is_registered = TRUE;
				}
				wake_up_process(g_pstPeTaskM23);
				PE_PRINT_NOTI("pic_task and sync_hadler start success.\n");

				_g_pe_tsk_m23_started = 1;
			}
			else
			{
				PE_PRINT_NOTI("already pic_task and sync_hadler start.\n");
			}
			if (!_g_pe_tsk_m23_resume)
			{
				_g_pe_tsk_m23_resume = 1;
				PE_PRINT_NOTI("_g_pe_tsk_m23_resume on.\n");
			}
			else
			{
				PE_PRINT_NOTI("already _g_pe_tsk_m23_resume on.\n");
			}
		}
		else
		{
			PE_PRINT_NOTI("start fail. pic_task is not created.\n");
			ret = RET_ERROR;
			break;
		}
	}while(0);
	return ret;
}
/**
 * stop pe m23 task
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_TSK_M23_StopPicTask(void)
{
	int ret = RET_OK;
	int hdlr_num = -1;
	PE_TSK_M23_CFG_T *pCfg = &_g_pe_tsk_m23_cfg;
	do{
		if(g_pstPeTaskM23)
		{
			kthread_stop(g_pstPeTaskM23);
			g_pstPeTaskM23 = NULL;
			PE_PRINT_NOTI("pic_task stopped.\n");
			if(pCfg->hdlr_opr.is_registered == TRUE)
			{
				#ifdef INCLUDE_KDRV_DE
				hdlr_num = de_sync_register(FALSE,PE_TSK_M23_PicSyncHandler,TO_STR(PE_TSK_M23_PicSyncHandler));
				#endif
				PE_PRINT_NOTI("sync_hadler number : %d\n", hdlr_num);
				pCfg->hdlr_opr.is_registered = FALSE;
				PE_PRINT_NOTI("sync_hadler unregistered.\n");
			}
		}
		else
		{
			PE_PRINT_NOTI("stop fail. pic_task is not created.\n");
			break;
		}
	}while(0);
	return ret;
}
static int PE_TSK_M23_CheckTime(char *fn_str, PE_TSK_M23_TIME location, UINT32 pos)
{
	static PE_TSK_M23_TIME_INFO_T time_info;
	UINT32 time_diff = 0;
	switch(pos)
	{
		case PE_TSK_M23_TIME_START:
			time_info.tick_start_time[location] = OS_GetMsecTicks();
			break;
		case PE_TSK_M23_TIME_END:
		default:
			time_info.tick_end_time[location] = OS_GetMsecTicks();
			if(time_info.tick_end_time[location] >= time_info.tick_start_time[location])
				time_diff = time_info.tick_end_time[location] - time_info.tick_start_time[location];
			else
				time_diff = time_info.tick_start_time[location] + (0xFFFFFFFF - time_info.tick_end_time[location]);
			PE_DBG_TSK("%s :	%d msec  elapsed\n", fn_str, (time_diff==0)?1:time_diff);
			break;
	}
	return RET_OK;
}
/**
 * pe picture task
 *
 * @param   *data [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_TSK_M23_PicTask(void *data)
{
	bool frozen;

	static UINT32 task_cnt = 0;
	PE_TSK_M23_CFG_T *pCfg = &_g_pe_tsk_m23_cfg;
	PE_TSK_M23_OPR_T *pOpr = &_g_pe_tsk_m23_cfg.opr;
	static UINT32 hdlr_cnt = 0;
	PE_PRINT_NOTI("pic_task start.\n");

	set_freezable();

	while (!kthread_freezable_should_stop(&frozen))
	{
		if(frozen)
		{
			printk("++ kthread(%s) wakes up\n",__F__);
		}

		/* check stop condition when device is closed */
		if(kthread_should_stop())
		{
			PE_PRINT_NOTI("pic_task exit.\n");
			break;
		}

		if(pOpr->dbgmode==PE_TSK_M23_DBG_TIME)
		{
			PE_TSK_M23_CheckTime("[pic_task]",PE_TSK_M23_TIME_TASK, PE_TSK_M23_TIME_START);
		}
		/* check pic sync handler registered. */
		if (pCfg->hdlr_opr.is_registered == TRUE)
		{
			if(pOpr->dbgmode==PE_TSK_M23_DBG_ON)
			{
				PE_DBG_TSK("[pic_task]hdlr_opr.count : %d -> %d (%s)\n", \
					hdlr_cnt, pCfg->hdlr_opr.count,(hdlr_cnt == pCfg->hdlr_opr.count)? "not increased":"normal");
			}
			hdlr_cnt = pCfg->hdlr_opr.count;
		}
		else
		{
			/* picture periodic process */
			PE_TSK_M23_PicPeriodicProcess(pCfg);
		}
		if(pOpr->dbgmode==PE_TSK_M23_DBG_TIME)
		{
			PE_TSK_M23_CheckTime("[pic_task]",PE_TSK_M23_TIME_TASK, PE_TSK_M23_TIME_END);
		}
		if(pOpr->dbgmode==PE_TSK_M23_DBG_CNT)
		{
			PE_DBG_TSK("[pic_task]task_cnt :%d\n", task_cnt);
		}
		if(task_cnt > 10000)
		{
			task_cnt = 1;
		}
		else
		{
			task_cnt++;
		}
		/**********************************************/
		OS_MsecSleep(pOpr->timeout);
		if (pOpr->pause_task == PE_TSK_M23_RUN_STOP_TASK)
		{
			PE_PRINT_NOTI("pic_task is paused.\n");
			wait_event_interruptible(_wq_pe_m23, (pOpr->pause_task != PE_TSK_M23_RUN_STOP_TASK));
		}
	}
	return RET_OK;
}
/**
 * pe picture sync handler
 *
 * @param   data [in] void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_TSK_M23_PicSyncHandler(void)
{
	PE_TSK_M23_CFG_T *pCfg = &_g_pe_tsk_m23_cfg;
	PE_TSK_M23_OPR_T *pOpr = &_g_pe_tsk_m23_cfg.opr;
	do {
		if (!_g_pe_tsk_m23_resume)
			break;
		if (pCfg->hdlr_opr.is_registered == FALSE)
			break;
		if (pOpr->pause_task == PE_TSK_M23_RUN_STOP_HDLR)
			break;

		if(pOpr->dbgmode==PE_TSK_M23_DBG_TIME)
		{
			PE_TSK_M23_CheckTime("[pic_sync_handler]",PE_TSK_M23_TIME_HNDL, PE_TSK_M23_TIME_START);
		}

		/* picture periodic process */
		PE_TSK_M23_PicPeriodicProcess(pCfg);

		if(pOpr->dbgmode==PE_TSK_M23_DBG_TIME)
		{
			PE_TSK_M23_CheckTime("[pic_sync_handler]",PE_TSK_M23_TIME_HNDL, PE_TSK_M23_TIME_END);
		}
		if(pOpr->dbgmode==PE_TSK_M23_DBG_CNT)
		{
			PE_DBG_TSK("[pic_sync_handler]hdlr_opr.count :%d\n",pCfg->hdlr_opr.count);
		}

		if(pCfg->hdlr_opr.count >= PE_TSK_M23_HDL_CNT_LOOP_MAX)
		{
			pCfg->hdlr_opr.count = 0;
		}
		else
		{
			pCfg->hdlr_opr.count++;
		}
	}while(0);
	return RET_OK;
}
/**
 * pe picture periodic process
 *	- causion : never use kmalloc,ipc,ioremap, on pic_sync_handler
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_TSK_M23_PicPeriodicProcess(PE_TSK_M23_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	PE_TSK_M23_OPR_T *p_opr = &(pCfg->opr);
	PE_TSK_M23_HDLR_OPR_T *p_hdlr_opr = &(pCfg->hdlr_opr);
	LX_PE_INF_DISPLAY_T *p_disp0_info = &(pCfg->inf.disp_info[LX_PE_WIN_0]);
	LX_PE_INF_DISPLAY_T *p_disp1_info = &(pCfg->inf.disp_info[LX_PE_WIN_1]);
	PE_INF_M23_CTRL_T *p_ctrl0_info = &(pCfg->inf.ctrl_info[LX_PE_WIN_0]);
	PE_INF_M23_CTRL_T *p_ctrl1_info = &(pCfg->inf.ctrl_info[LX_PE_WIN_1]);
	do {
		CHECK_KNULL(pCfg);
		/**********************************************/
		/* add specific func.                         */
		/**********************************************/
		if (p_hdlr_opr->is_registered == TRUE)
		{
			p_hdlr_opr->cur_time = OS_GetMsecTicks();
			p_hdlr_opr->time_dif = (p_hdlr_opr->cur_time - p_hdlr_opr->pre_time);

			if (((p_hdlr_opr->count&_g_pe_tsk_m23_skip_hdl_cnt_num)!=_g_pe_tsk_m23_skip_hdl_cnt_num) || \
				(p_hdlr_opr->time_dif<=_g_pe_tsk_m23_hdl_min_msec))
			{
				if(p_opr->dbgmode==PE_TSK_M23_DBG_BRK)
				{
					PE_DBG_TSK("cnt:%d(%d). T c,p:%d,%d(d:%d). cnt_num:%d. min:%d, run nothing.\n", \
						pCfg->hdlr_opr.count, (pCfg->hdlr_opr.count&_g_pe_tsk_m23_skip_hdl_cnt_num), \
						p_hdlr_opr->cur_time, p_hdlr_opr->pre_time, p_hdlr_opr->time_dif,_g_pe_tsk_m23_skip_hdl_cnt_num,_g_pe_tsk_m23_hdl_min_msec);
				}
				p_hdlr_opr->pre_time = p_hdlr_opr->cur_time;
				break;
			}
			else
			{
				if(p_opr->dbgmode==PE_TSK_M23_DBG_BRK)
				{
					PE_DBG_TSK("cnt:%d(%d). T c,p:%d,%d(d:%d), run all.\n", \
						pCfg->hdlr_opr.count, (pCfg->hdlr_opr.count&_g_pe_tsk_m23_skip_hdl_cnt_num), \
						p_hdlr_opr->cur_time, p_hdlr_opr->pre_time, p_hdlr_opr->time_dif);
				}
				p_hdlr_opr->pre_time = p_hdlr_opr->cur_time;
			}
		}

		/* check info */
		ret = PE_INF_M23_CheckSclInfo();
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_INF_M23_CheckSclInfo() error.\n");
		/* get disp info */
		ret = PE_INF_M23_GetCurDispInfSettings(LX_PE_WIN_0, p_disp0_info);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_INF_M23_GetCurDispInfSettings(LX_PE_WIN_0) error.\n");
		ret = PE_INF_M23_GetCurDispInfSettings(LX_PE_WIN_1, p_disp1_info);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_INF_M23_GetCurDispInfSettings(LX_PE_WIN_1) error.\n");
		/* get ctrl info */
		ret = PE_INF_M23_GetCurCtrlInfSettings(LX_PE_WIN_0, p_ctrl0_info);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_INF_M23_GetCurCtrlInfSettings(LX_PE_WIN_0) error.\n");
		ret = PE_INF_M23_GetCurCtrlInfSettings(LX_PE_WIN_1, p_ctrl1_info);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_INF_M23_GetCurCtrlInfSettings(LX_PE_WIN_1) error.\n");

		ret = PE_TSK_M23_PicSetWinCmnCcmHstFwiDcm(pCfg);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_TSK_M23_SetWinCmnCcmHstFwiDcm() error.\n");

		if (p_opr->pause_task == PE_TSK_M23_RUN_STOP_OVWR)
			break;

		/* check fw status */
		ret = PE_FWI_M23_CheckFwStatus(pCfg);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_FWI_M23A_CheckFwStatus() error.\n");

		/* from here, reg. overwrite functions */
		ret = PE_TSK_M23_PicSetModes(pCfg);

		/**********************************************/
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * Sets the picture window, lrcr config, acr gain, histo info, blur_v_gain
 * cmn and other operations
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_TSK_M23_PicSetWinCmnCcmHstFwiDcm(PE_TSK_M23_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		/* set picture window */
		ret = PE_WIN_HW_M23_SetEnhancingWindow(pCfg);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_WIN_HW_M23_SetEnhancingWindow() error.\n");
		/* check global histo info */
		ret = PE_HST_HW_M23_CheckGlobalHistoInfo(pCfg);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_HST_HW_M23_CheckGlobalHistoInfo() error.\n");
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}

/**
 * Sets the tnr, dnr, ifc, clc, pblur, csc & lvctrl mode
 *
 * @param   *pCfg [in] PE_TSK_M23_CFG_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_TSK_M23_PicSetModes(PE_TSK_M23_CFG_T *pCfg)
{
	int ret = RET_OK;
	#ifdef PE_HW_M23_BRINGUP
	do {
		/* set tnr mode */
		ret = PE_NRD_HW_M23_SetTnrMode(pCfg);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_NRD_HW_M23_SetTnrMode() error.\n");
		/* set clc mode */
		PE_DNT_HW_M23_SetClcMode(pCfg);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_DNT_HW_M23_SetClcMode() error.\n");
		/* set vfy mode */
		PE_DNT_HW_M23_SetVfyMode(pCfg);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_DNT_HW_M23_SetVfyMode() error.\n");
		/* set etc mode */
		PE_DNT_HW_M23_SetIpcMode(pCfg);
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_DNT_HW_M23_SetEtcMode() error.\n");
		ret = PE_CMG_HW_M23_SetTargetSat();
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_CMG_HW_M23_SetTargetSat() error.\n");
		ret = PE_SHP_HW_M23_SetOBCGainLUT();
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_SHP_HW_M23_SetOBCGainLUT() error.\n");
		ret = PE_SHP_HW_M23_SetObcMode();
		PE_TSK_M23_CHECK_CODE(ret,break,"PE_SHP_HW_M23_SetObcMode() error.\n");
	}while(0);
	#endif /*PE_HW_M23_BRINGUP*/
	return ret;
}
