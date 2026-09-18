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
 *  driver interface header for demod device. ( used only within kdriver )
 *	demod device will teach you how to make device driver with new platform.
 *
 *  @author		jeongpil.yun (jeongpil.yun@lge.com)
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#define DEMOD_TAG "[CORE.HW] "

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <linux/delay.h>	/**< mdelay */

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <asm/uaccess.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/freezer.h>


#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <linux/delay.h>	/**< mdelay */

#ifdef KDRV_CONFIG_PM	// added by SC Jung for quick booting
#include <linux/platform_device.h>
#endif
#include "os_util.h"
//#include "base_dev_cfg.h"
#include "base_device.h"
//#include "ctop_regs.h"  //chungiii fpga
#include "demod_drv.h"
#include "demod_impl.h"
#include "demod_module.h"
#//include "sys_regs.h"  // chungiii fpga
#include "i2c_core.h"

#ifndef PLATFORM_FPGA
#include "sys_bwm.h"
#endif



/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

#ifdef KDRV_CONFIG_PM
	unsigned int guiPmClk;
	unsigned int guiPmBbmode;
	unsigned int guiPmI2C;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

extern void DEMOD_PROC_Init (void);
extern int SYS_IO_ReadRegArray (UINT32 addr, UINT32 size, void *data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

UINT64 				pauseTimeDemod = 0xFFFFFFFFFFFFFFFFULL ;
static wait_queue_head_t 	g_DEMOD_Tuning_WaitQ;
LX_DEMOD_TASK_MSG_T		g_requestMsg;
unsigned int 			g_NewTuneReqeustTime;
unsigned int 			g_RetuneStartTime;
UINT32 				notifyinglockTimeOut = LX_DEMOD_LOCK_DEALY_1500;
extern BOOLEAN			gPanama;


static DECLARE_WAIT_QUEUE_HEAD(g_DEMOD_Tuning_WaitQ);

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int DEMOD_UnLock_Notify (UINT8 deviceNum);
static void DEMOD_CheckDemodPayloads_and_Pause (UINT8 deviceNum, UINT64 timeout);

static int _DEMOD_ChannelChangeDVBT(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeDTMB(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeDVBT2(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeDVBC(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeDVBC2(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeISDBT(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeATSC(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeQAM(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeDVBS(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeDVBS2(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);
static int _DEMOD_ChannelChangeATSC3(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg);

static int _DEMOD_Get_TunedCFG_VSB(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_VSB(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_ISDBT(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_DVBT(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_DVBT2(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_DVBC(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_DVBS(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_DVBS2(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_ANALOG(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_DTMB(DEMOD_CTX_T *pDemodInfo);
static int _DEMOD_Get_TunedCFG_ATSC3(DEMOD_CTX_T *pDemodInfo);

static int DEMOD_FW_Recovery (void);
//static int KHAL_Get_DEMOD_CTX(DEMOD_CTX_T *pDemodInfo);

static int _DEMOD_Get_TunedCFG_QAM(DEMOD_CTX_T *pDemodInfo);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
DEMOD_HAL_T g_demod_hal;

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * _DEMOD_ChannelChangeDVBT.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeDVBT(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.dvbt.tuneMode 		= pDemodCfg->dvbt.tuneMode;
	pDemodInfo->setCfgParam.dvbt.channelBW 		= pDemodCfg->dvbt.channelBW;
	pDemodInfo->setCfgParam.dvbt.bSpectrumInv	= pDemodCfg->dvbt.bSpectrumInv;
	pDemodInfo->setCfgParam.dvbt.bSetHp 		= pDemodCfg->dvbt.bSetHp;
	pDemodInfo->setCfgParam.dvbt.FFTMode	 	= pDemodCfg->dvbt.FFTMode;
	pDemodInfo->setCfgParam.dvbt.gIMode	 		= pDemodCfg->dvbt.gIMode;
	pDemodInfo->setCfgParam.dvbt.hierachMode 	= pDemodCfg->dvbt.hierachMode;
	pDemodInfo->setCfgParam.dvbt.lpCodeRate 	= pDemodCfg->dvbt.lpCodeRate;
	pDemodInfo->setCfgParam.dvbt.hpCodeRate 	= pDemodCfg->dvbt.hpCodeRate;
	pDemodInfo->setCfgParam.dvbt.qamMode 		= pDemodCfg->dvbt.qamMode;
	pDemodInfo->systemMode						= pDemodCfg->dvbt.qamMode;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= pDemodInfo->setCfgParam.dvbt.channelBW;
	symbr	 	= pDemodInfo->symbr;
	tuneMode 	= pDemodInfo->setCfgParam.dvbt.tuneMode;

	DEMOD_UnlockDevice();

	if(RET_OK != DEMOD_TPOutCLKEnable(FALSE))
	{
		DEMOD_ERROR("FAIL, DEMOD_TPOutCLKEnable()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT("DEMOD_TPOutCLKEnable is disable\n");

	usleep_range(35000,36000);	/* 35ms ~ 36ms Tuner Stabilization time for pervention channel skip*/

	if(RET_OK != DEMOD_DVBT_Set_DefaultRegisterValue(bandWd))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
/* Not used function
	if(RET_OK != DEMOD_DVBT_Set_NeverLockWaitTime(LX_DEMOD_DVBT_NEVERLOCK_WAIT_TIME))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_NeverLockWaitTime()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_Set_SpectrumCtrl(FALSE, FALSE))
	{
		DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
*/
	if(LX_DEMOD_TUNE_NORMAL != tuneMode)
	{
		if(RET_OK != DEMOD_DVBT_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_DVBT_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbt)))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_PartialConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}
	else
	{
#if 1
		if(RET_OK != DEMOD_DVBT_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_DVBT_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbt)))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_PartialConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
#else
		if(RET_OK != DEMOD_DVBT_Set_Config_auto(FALSE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_DVBT_Set_FullConfig(&(pDemodInfo->setCfgParam.dvbt)))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_FullConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

#endif
	}
#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_ERROR("FAIL, DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif

	if(gPanama)
	{
		DEMOD_ADC_Enable();
		DEMOD_INFO("DEMOD_ADC_Enable for Panama\n");
	}

	DEMOD_LockDevice();

	//Send event for Tuning task
	g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();

	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeDTMB.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeDTMB(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.dtmb.bM720			= pDemodCfg->dtmb.bM720;
	pDemodInfo->setCfgParam.dtmb.channelBW 		= pDemodCfg->dtmb.channelBW;
	pDemodInfo->setCfgParam.dtmb.carrierMode	= pDemodCfg->dtmb.carrierMode;
	pDemodInfo->setCfgParam.dtmb.codeRate		= pDemodCfg->dtmb.codeRate;
	pDemodInfo->setCfgParam.dtmb.constellation	= pDemodCfg->dtmb.constellation;
	pDemodInfo->setCfgParam.dtmb.pnMode			= pDemodCfg->dtmb.pnMode;
	pDemodInfo->setCfgParam.dtmb.tuneMode		= pDemodCfg->dtmb.tuneMode;
	pDemodInfo->systemMode						= pDemodCfg->dtmb.constellation;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= pDemodInfo->setCfgParam.dtmb.channelBW;
	symbr	 	= pDemodInfo->symbr;
	tuneMode 	= pDemodInfo->setCfgParam.dtmb.tuneMode;

	DEMOD_UnlockDevice();
/*
	if(RET_OK != DEMOD_StdOperModeContrl(operMode, bandWd,	symbr))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_StdOperModeContrl() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
*/

	//	usleep_range(40000,50000);	/* 1ms ~ 10ms */
	usleep_range(35000,36000);	/* 35ms ~ 40ms Tuner Stabilization time for pervention channel skip */


	if(RET_OK != DEMOD_DTMB_Set_Config_auto(TRUE))
	{
		DEMOD_ERROR("FAIL, DEMOD_DTMB_Set_Config_auto()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_DTMB_Set_PartialConfig(&(pDemodInfo->setCfgParam.dtmb)))
	{
		DEMOD_ERROR("FAIL, DEMOD_DTMB_Set_PartialConfig()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_PRINT("[DEMOD] FAIL, DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif

	DEMOD_LockDevice();

	//Send event for Tuning task
	g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();

	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}




/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeDVBT2.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
  * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
* @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeDVBT2(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.dvbt2.tuneMode 		= pDemodCfg->dvbt2.tuneMode;
	pDemodInfo->setCfgParam.dvbt2.channelBW 	= pDemodCfg->dvbt2.channelBW;
	pDemodInfo->setCfgParam.dvbt2.bSpectrumInv	= pDemodCfg->dvbt2.bSpectrumInv;
	pDemodInfo->setCfgParam.dvbt2.FFTMode	 	= pDemodCfg->dvbt2.FFTMode;
	pDemodInfo->setCfgParam.dvbt2.gIMode	 	= pDemodCfg->dvbt2.gIMode;
	pDemodInfo->setCfgParam.dvbt2.codeRate 		= pDemodCfg->dvbt2.codeRate;
	pDemodInfo->setCfgParam.dvbt2.qamMode 		= pDemodCfg->dvbt2.qamMode;
	pDemodInfo->setCfgParam.dvbt2.groupID		= pDemodCfg->dvbt2.groupID;
	pDemodInfo->setCfgParam.dvbt2.unPLP			= pDemodCfg->dvbt2.unPLP;
	pDemodInfo->systemMode						= pDemodCfg->dvbt2.qamMode;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= pDemodInfo->setCfgParam.dvbt2.channelBW;
	symbr	 	= pDemodInfo->symbr;
	tuneMode 	= pDemodInfo->setCfgParam.dvbt2.tuneMode;

	DEMOD_UnlockDevice();

	if(RET_OK != DEMOD_TPOutCLKEnable(FALSE))
	{
		DEMOD_ERROR("FAIL, DEMOD_TPOutCLKEnable()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_PRINT("DEMOD_TPOutCLKEnable is disable\n");

	usleep_range(35000,36000);	/* 35ms ~ 36ms Tuner Stabilization time for pervention channel skip */

	if(RET_OK != DEMOD_DVBT2_Set_DefaultRegisterValue(bandWd))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
/* Not used function
	if(RET_OK != DEMOD_DVBT2_Set_NeverLockWaitTime(LX_DEMOD_DVBT_NEVERLOCK_WAIT_TIME))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_NeverLockWaitTime()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_Set_SpectrumCtrl(FALSE, FALSE))
	{
		DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
*/
	if(LX_DEMOD_TUNE_NORMAL != tuneMode)
	{
		if(RET_OK != DEMOD_DVBT2_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT2_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

#if 0
		if(RET_OK != DEMOD_DVBT2_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbt2)))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT2_Set_PartialConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
#endif
	}
	else
	{

#if 1
		if(RET_OK != DEMOD_DVBT2_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT2_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

#if 0
		if(RET_OK != DEMOD_DVBT2_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbt2)))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT2_Set_PartialConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
#endif

#else
		if(RET_OK != DEMOD_DVBT2_Set_Config_auto(FALSE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT2_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_DVBT2_Set_FullConfig(&(pDemodInfo->setCfgParam.dvbt2)))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT2_Set_FullConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

#endif


	}

#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_ERROR("FAIL, DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif
	if(gPanama)
	{
		DEMOD_ADC_Enable();
		DEMOD_INFO("DEMOD_ADC_Enable for Panama\n");
	}

	DEMOD_LockDevice();

	//Send event for Tuning task
	g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeDVBC.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeDVBC(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.dvbc.tuneMode 		= pDemodCfg->dvbc.tuneMode;
	pDemodInfo->setCfgParam.dvbc.channelBW 		= pDemodCfg->dvbc.channelBW;
	pDemodInfo->setCfgParam.dvbc.bSpectrumInv 	= pDemodCfg->dvbc.bSpectrumInv;
	pDemodInfo->setCfgParam.dvbc.qamMode 		= pDemodCfg->dvbc.qamMode;
	pDemodInfo->setCfgParam.dvbc.symbolRate 	= pDemodCfg->dvbc.symbolRate;
	pDemodInfo->setCfgParam.dvbc.frequency		= pDemodCfg->dvbc.frequency;
	pDemodInfo->systemMode						= pDemodCfg->dvbc.qamMode;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= pDemodInfo->setCfgParam.dvbc.channelBW;
	symbr	 	= pDemodInfo->symbr;
	tuneMode 	= pDemodInfo->setCfgParam.dvbc.tuneMode;


	DEMOD_UnlockDevice();

/*
	if(RET_OK != DEMOD_StdOperModeContrl(operMode, bandWd,	symbr))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_StdOperModeContrl() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
*/

	usleep_range(40000,41000);	/* 35ms ~ 40ms Tuner Stabilization time for pervention channel skip */

	if(RET_OK != DEMOD_DVBC_Set_DefaultRegisterValue())
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
/* Not used function
	if(RET_OK != DEMOD_DVBC2_Set_StartFrequency(pDemodInfo->setCfgParam.dvbc.frequency))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBC2_Set_StartFrequency()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_DVBC_Set_NeverLockWaitTime(LX_DEMOD_DVBC_NEVERLOCK_WAIT_TIME))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_NeverLockWaitTime()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_Set_SpectrumCtrl(TRUE, FALSE))
	{
		DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
*/
	DEMOD_ADC_Enable();

//	if((LX_DEMOD_TUNE_NORMAL != tuneMode) && (LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA != tuneMode)) //Before M16
	if(LX_DEMOD_TUNE_SPEC_DVBC_FIXED_DATA != tuneMode)   //After M16
	{
/*
		if(RET_OK != DEMOD_DVBC_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
*/
		if(RET_OK != DEMOD_DVBC_AutoSymbolRateDet(LX_DEMOD_SYMR_FULL_SCAN_MODE, LX_DEMOD_SYMBOL_RATE_6900_KHZ))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBC_AutoSymbolRateDet()\n");
			DEMOD_RETURN_FAIL(__F__);
		}


	}
	else
	{
/*
		if(RET_OK != DEMOD_DVBC_Set_Config_auto(FALSE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
*/
		if(RET_OK != DEMOD_DVBC_AutoSymbolRateDet(LX_DEMOD_SYMR_FULL_SCAN_MODE, pDemodInfo->setCfgParam.dvbc.symbolRate))  //need to be modified for H14
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBC_AutoSymbolRateDet()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_DVBC_Set_QamMode(pDemodInfo->setCfgParam.dvbc.qamMode))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_QamMode()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

	}

#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_ERROR("FAIL, DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif

	DEMOD_LockDevice();

	//Send event for Tuning task
	g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}



/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeDVBC2.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeDVBC2(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.dvbc2.tuneMode 		= pDemodCfg->dvbc2.tuneMode;
	pDemodInfo->setCfgParam.dvbc2.channelBW 	= pDemodCfg->dvbc2.channelBW;
	pDemodInfo->setCfgParam.dvbc2.bSpectrumInv 	= pDemodCfg->dvbc2.bSpectrumInv;
	pDemodInfo->setCfgParam.dvbc2.qamMode 		= pDemodCfg->dvbc2.qamMode;
	pDemodInfo->setCfgParam.dvbc2.groupID		= pDemodCfg->dvbc2.groupID;
	pDemodInfo->setCfgParam.dvbc2.unPLP			= pDemodCfg->dvbc2.unPLP;
	pDemodInfo->setCfgParam.dvbc2.sliceID		= pDemodCfg->dvbc2.sliceID;
	pDemodInfo->setCfgParam.dvbc2.frequency		= pDemodCfg->dvbc2.frequency;
	pDemodInfo->systemMode						= pDemodCfg->dvbc2.qamMode;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= pDemodInfo->setCfgParam.dvbc2.channelBW;
	symbr	 	= pDemodInfo->symbr;
	tuneMode 	= pDemodInfo->setCfgParam.dvbc2.tuneMode;

	DEMOD_UnlockDevice();
/*
	if(RET_OK != DEMOD_StdOperModeContrl(operMode, bandWd,	symbr))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_StdOperModeContrl() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
*/

	usleep_range(40000,41000);	/* 35ms ~ 40ms Tuner Stabilization time for pervention channel skip */

	if(RET_OK != DEMOD_DVBC2_Set_DefaultRegisterValue())
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBC2_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_DVBC2_Set_StartFrequency(pDemodInfo->setCfgParam.dvbc2.frequency))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBC2_Set_StartFrequency()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	if(RET_OK != DEMOD_DVBC2_Set_NeverLockWaitTime(LX_DEMOD_DVBC_NEVERLOCK_WAIT_TIME))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_NeverLockWaitTime()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_Set_SpectrumCtrl(TRUE, FALSE))
	{
		DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	if(LX_DEMOD_TUNE_NORMAL != tuneMode)
	{

		if(RET_OK != DEMOD_DVBC2_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_DVBC2_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbc2)))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBC2_Set_PartialConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}
	else
	{
		if(RET_OK != DEMOD_DVBC2_Set_Config_auto(FALSE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBC_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_DVBC2_Set_FullConfig(&(pDemodInfo->setCfgParam.dvbc2)))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBC2_Set_FullConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

	}

#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_ERROR("FAIL, DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif


	DEMOD_LockDevice();

	//Send event for Tuning task
	g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeDVBC2.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
  * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
* @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeISDBT(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.isdbt.tuneMode 		= pDemodCfg->isdbt.tuneMode;
	pDemodInfo->setCfgParam.isdbt.channelBW 	= pDemodCfg->isdbt.channelBW;
	pDemodInfo->setCfgParam.isdbt.bSpectrumInv 	= pDemodCfg->isdbt.bSpectrumInv;
	pDemodInfo->setCfgParam.isdbt.FFTMode	 	= pDemodCfg->isdbt.FFTMode;
	pDemodInfo->setCfgParam.isdbt.gIMode	 	= pDemodCfg->isdbt.gIMode;
	pDemodInfo->setCfgParam.isdbt.tmcc		 	= pDemodCfg->isdbt.tmcc;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= pDemodInfo->setCfgParam.isdbt.channelBW;
	symbr	 	= pDemodInfo->symbr;
	tuneMode 	= pDemodInfo->setCfgParam.isdbt.tuneMode;

	DEMOD_UnlockDevice();
/*
	if(RET_OK != DEMOD_StdOperModeContrl(operMode, bandWd,	symbr))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_StdOperModeContrl() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
*/
	usleep_range(40000,50000);	/* 40ms ~ 50ms Tuner Stabilization time for pervention channel skip */

	if(RET_OK != DEMOD_ISDBT_Set_DefaultRegisterValue())
	{
		DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_ISDBT_Set_NeverLockWaitTime(LX_DEMOD_ISDBT_NEVERLOCK_WAIT_TIME))
	{
		DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_NeverLockWaitTime()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_Set_SpectrumCtrl(FALSE, FALSE))
	{
		DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	if(LX_DEMOD_TUNE_NORMAL != tuneMode)
	{
		if(RET_OK != DEMOD_ISDBT_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_ISDBT_Set_PartialConfig(&(pDemodInfo->setCfgParam.isdbt)))
		{
			DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_PartialConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}
	else
	{

		if(RET_OK != DEMOD_ISDBT_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_ISDBT_Set_PartialConfig(&(pDemodInfo->setCfgParam.isdbt)))
		{
			DEMOD_ERROR("FAIL, DEMOD_ISDBT_Set_PartialConfig()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}

	if(gPanama)
	{
		DEMOD_ADC_Enable();
		DEMOD_INFO("DEMOD_ADC_Enable for Panama\n");
	}

#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_ERROR("FAIL, DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif
	DEMOD_LockDevice();

	//Send event for Tuning task
	g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}


/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeATSC.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeATSC(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.vsb.tuneMode 		= pDemodCfg->vsb.tuneMode;
	pDemodInfo->setCfgParam.vsb.channelBW 		= pDemodCfg->vsb.channelBW;
	pDemodInfo->setCfgParam.vsb.bSpectrumInv 	= pDemodCfg->vsb.bSpectrumInv;
	pDemodInfo->systemMode						= LX_DEMOD_VSB;
	pDemodInfo->bIsTPoutEn 						= TRUE;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= pDemodInfo->setCfgParam.vsb.channelBW;
	symbr	 	= pDemodInfo->symbr;
	tuneMode 	= pDemodInfo->setCfgParam.vsb.tuneMode;

	DEMOD_UnlockDevice();
/*
	if(RET_OK != DEMOD_StdOperModeContrl(operMode, bandWd,	symbr))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_StdOperModeContrl() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
*/
	usleep_range(40000,50000);	/* 40ms ~ 50ms Tuner Stabilization time for pervention channel skip */

	if(pDemodInfo->instantBoot == TRUE)
	{
		usleep_range(50000,50000);	/* 50ms */
		DEMOD_NOTI("check instant boot tuning DEMOD_VSB_SetDemod 50ms\n");
		if(RET_OK != DEMOD_VSB_SetDemod(pDemodInfo))
		{
			DEMOD_ERROR("FAIL, DEMOD_VSB_SetDemod()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}


	if(RET_OK != DEMOD_VSB_Set_DefaultRegisterValue())
	{
		DEMOD_ERROR("FAIL, DEMOD_VSB_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	//if(RET_OK != DEMOD_VSB_Set_NeverLockWaitTime(LX_DEMOD_VSB_NEVERLOCK_WAIT_TIME))
	if(RET_OK != DEMOD_VSB_Set_NeverLockWaitTime(600))
	{
		DEMOD_ERROR("FAIL, DEMOD_VSB_Set_NeverLockWaitTime()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	if(RET_OK != DEMOD_Set_SpectrumCtrl(FALSE, FALSE))
	{
		DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(gPanama)
	{
		DEMOD_ADC_Enable();
		DEMOD_INFO("DEMOD_ADC_Enable for Panama\n");
	}


#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_ERROR("FAIL, DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif

	DEMOD_LockDevice();

	//Send event for Tuning task
	if(pDemodInfo->instantBoot == TRUE)
	{
		DEMOD_NOTI("Check instant boot VSB tuning task\n");
		g_requestMsg = LX_DEMOD_INSTANTBOOT_TUNE_REQUEST;
		wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	}
	else
	{
		g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
		wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	}


	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}




/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeATSC.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeQAM(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.qam.tuneMode 		= pDemodCfg->qam.tuneMode;
	pDemodInfo->setCfgParam.qam.channelBW 		= pDemodCfg->qam.channelBW;
	pDemodInfo->setCfgParam.qam.bSpectrumInv 	= pDemodCfg->qam.bSpectrumInv;
	pDemodInfo->setCfgParam.qam.qamMode 		= pDemodCfg->qam.qamMode;
	pDemodInfo->systemMode						= pDemodCfg->qam.qamMode;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= LX_DEMOD_VSB_NO_OPERATION; //pDemodInfo->setCfgParam.qam.channelBW;
	symbr	 	= pDemodInfo->symbr;
	tuneMode 	= pDemodInfo->setCfgParam.qam.tuneMode;

	DEMOD_UnlockDevice();
/*
	if(RET_OK != DEMOD_StdOperModeContrl(operMode, bandWd,	symbr))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_StdOperModeContrl() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
*/
	usleep_range(40000,50000);	/* 40ms ~ 50ms Tuner Stabilization time for pervention channel skip */

	if(pDemodInfo->instantBoot == TRUE)
	{
		usleep_range(50000,50000);	/* 15ms ~ 20ms */
		DEMOD_NOTI("####check instant boot tuning DEMOD_QAM_SetDemod 50ms\n");
		if(RET_OK != DEMOD_QAM_SetDemod(pDemodInfo))
		{
			DEMOD_ERROR("FAIL, DEMOD_QAM_SetDemod()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}

	if(RET_OK != DEMOD_QAM_Set_DefaultRegisterValue())
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBT_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_QAM_Set_NeverLockWaitTime(LX_DEMOD_QAM_NEVERLOCK_WAIT_TIME))
	{
		DEMOD_ERROR("FAIL, DEMOD_QAM_Set_NeverLockWaitTime()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(LX_DEMOD_TUNE_NORMAL != tuneMode)
	{

		if(RET_OK != DEMOD_QAM_ModeAutoDetection(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_QAM_ModeAutoDetection()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_Set_SpectrumCtrl(TRUE, FALSE))
		{
			DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}
	else
	{
		if(RET_OK != DEMOD_QAM_ModeAutoDetection(FALSE))
		{
			DEMOD_ERROR("FAIL, DEMOD_QAM_ModeAutoDetection()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(RET_OK != DEMOD_Set_SpectrumCtrl(TRUE, pDemodInfo->setCfgParam.qam.bSpectrumInv))
		{
			DEMOD_ERROR("FAIL, DEMOD_Set_SpectrumCtrl()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
		if(LX_DEMOD_64QAM == pDemodInfo->setCfgParam.qam.qamMode)
		{
			if(RET_OK != DEMOD_QAM_64Mode())
			{
				DEMOD_ERROR("FAIL, DEMOD_QAM_64Mode()\n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		else if(LX_DEMOD_256QAM == pDemodInfo->setCfgParam.qam.qamMode)
		{
			if(RET_OK != DEMOD_QAM_256Mode())
			{
				DEMOD_ERROR("FAIL, DEMOD_QAM_256Mode()\n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		else
		{
				DEMOD_ERROR("FAIL, Invalid QAM Mode\n");
				DEMOD_RETURN_FAIL(__F__);
		}

	}
	if(gPanama)
	{
		DEMOD_ADC_Enable();
		DEMOD_INFO("DEMOD_ADC_Enable for Panama\n");
	}
#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_PRINT("[DEMOD] FAIL  DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif

	DEMOD_LockDevice();

	//Send event for Tuning task
	if(pDemodInfo->instantBoot == TRUE)
	{
		DEMOD_NOTI("####check instant boot QAM tuning task\n");
		g_requestMsg = LX_DEMOD_INSTANTBOOT_TUNE_REQUEST;
		wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	}
	else
	{
		g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
		wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	}


	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeDVBS.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeDVBS(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.dvbs.tuneMode 		= pDemodCfg->dvbs.tuneMode;
	pDemodInfo->setCfgParam.dvbs.symbolRate 	= pDemodCfg->dvbs.symbolRate;
	pDemodInfo->setCfgParam.dvbs.bSpectrumInv	= pDemodCfg->dvbs.bSpectrumInv;
	pDemodInfo->setCfgParam.dvbs.codeRate 		= pDemodCfg->dvbs.codeRate;
	pDemodInfo->setCfgParam.dvbs.frequency		= pDemodCfg->dvbs.frequency;
	pDemodInfo->setCfgParam.dvbs.operatingMode	= pDemodCfg->dvbs.operatingMode;
	pDemodInfo->systemMode						= LX_DEMOD_QPSK;

	operMode 	= pDemodInfo->operMode;
	bandWd	 	= LX_DEMOD_DVBS_NO_OPERATION;
	symbr	 	= LX_DEMOD_SYMR_DVBS_NO_OPERATION_MODE;
	tuneMode 	= pDemodInfo->setCfgParam.dvbs.tuneMode;

	DEMOD_UnlockDevice();

	DEMOD_PRINT("frequency = %d\n",pDemodInfo->setCfgParam.dvbs.frequency);
	DEMOD_PRINT("symbolRate = %d\n",pDemodInfo->setCfgParam.dvbs.symbolRate);
/*
	if(RET_OK != DEMOD_StdOperModeContrl(operMode, bandWd,	symbr))
	{
		DEMOD_PRINT("[DEMOD] FAIL  DEMOD_StdOperModeContrl()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
*/

	//	usleep_range(40000,50000);	/* 1ms ~ 10ms */
		usleep_range(30000,35000);	/* 40ms ~ 50ms Tuner Stabilization time for pervention channel skip */

/*
	if(RET_OK != DEMOD_DVBS_Set_DefaultRegisterValue())
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
*/
/*
	if(pDemodInfo->setCfgParam.dvbs.operatingMode == LX_DEMOD_DVBS_BLIND_SCAN_MODE)
	{
//		if(RET_OK != DEMOD_DVBS_Set_BlindSpectrumMode(LX_DEMOD_DVBS_BLIND_SCAN_MODE))
//		{
//			DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_BlindSpectrumMode(LX_DEMOD_DVBS_BLIND_SCAN_MODE)\n");
//			DEMOD_RETURN_FAIL(__F__);
//		}

		if(pDemodInfo->setCfgParam.dvbs.tuneMode == LX_DEMOD_TUNE_AUTO_FULL)
		{
			if(RET_OK != DEMOD_DVBS_Set_SpectrumModeConfig(TRUE, 20000))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_SpectrumModeConfig(TRUE, 20000)\n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}
		else
		{
			if(RET_OK != DEMOD_DVBS_Set_SpectrumModeConfig(FALSE, pDemodInfo->setCfgParam.dvbs.symbolRate))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_SpectrumModeConfig(TRUE, 0)\n");
				DEMOD_RETURN_FAIL(__F__);
			}
		}

	}
	else
	{
//		if(RET_OK != DEMOD_DVBS_Set_BlindSpectrumMode(pDemodInfo->setCfgParam.dvbs.operatingMode))
//		{
//			DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_BlindSpectrumMode()\n");
//			DEMOD_RETURN_FAIL(__F__);
//		}

		if(LX_DEMOD_TUNE_NORMAL != tuneMode)
		{
			if(RET_OK != DEMOD_DVBS_Set_Config_auto(TRUE))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_Config_auto()\n");
				DEMOD_RETURN_FAIL(__F__);
			}

//			if(RET_OK != DEMOD_DVBS_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbs)))
//			{
//				DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_PartialConfig()\n");
//				DEMOD_RETURN_FAIL(__F__);
//			}
		}
		else
		{

			if(RET_OK != DEMOD_DVBS_Set_Config_auto(TRUE))
			{
				DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_Config_auto()\n");
				DEMOD_RETURN_FAIL(__F__);
			}

//			if(RET_OK != DEMOD_DVBS_Set_PartialConfig(&(pDemodInfo->setCfgParam.dvbs)))
//			{
//				DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_PartialConfig()\n");
//				DEMOD_RETURN_FAIL(__F__);
//			}
		}
*/


	if(pDemodInfo->setCfgParam.dvbs.operatingMode != LX_DEMOD_DVBS_BLIND_SCAN_MODE)
	{
		if(RET_OK != DEMOD_DVBS_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBS_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}

#if 0
	if(RET_OK != DEMOD_SoftwareReset())
	{
		DEMOD_PRINT("[DEMOD] FAIL  DEMOD_SoftwareReset()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
#endif
	DEMOD_LockDevice();

	//Send event for Tuning task
	g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeDVBS2.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeDVBS2(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	LX_DEMOD_OPER_MODE_T 		operMode 	= LX_DEMOD_UNKOWN_OPMODE;
	LX_DEMOD_BWMODE_T			bandWd 		= LX_DEMOD_BW_UNKNOWN;
	LX_DEMOD_SYMRDET_MODE_T 	symbr 		= LX_DEMOD_SYMR_UNKOWN_MODE;
	LX_DEMOD_TUNE_MODE_T		tuneMode 	= LX_DEMOD_TUNE_UNKNOWN;

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.dvbs2.tuneMode 		= pDemodCfg->dvbs2.tuneMode;
	pDemodInfo->setCfgParam.dvbs2.bSpectrumInv	= pDemodCfg->dvbs2.bSpectrumInv;
	pDemodInfo->setCfgParam.dvbs2.symbolRate 	= pDemodCfg->dvbs2.symbolRate;
	pDemodInfo->setCfgParam.dvbs2.codeRate 		= pDemodCfg->dvbs2.codeRate;
	pDemodInfo->setCfgParam.dvbs2.frequency		= pDemodCfg->dvbs2.frequency;
	pDemodInfo->setCfgParam.dvbs2.operatingMode	= pDemodCfg->dvbs2.operatingMode;
	pDemodInfo->systemMode						= pDemodCfg->dvbs2.constellation;

	operMode 	= pDemodInfo->operMode;
	bandWd		= LX_DEMOD_DVBS_NO_OPERATION;
	symbr		= LX_DEMOD_SYMR_DVBS_NO_OPERATION_MODE;
	tuneMode 	= pDemodInfo->setCfgParam.dvbs2.tuneMode;


	DEMOD_UnlockDevice();

	DEMOD_PRINT("operMode = 0x%02x\n",operMode);
	DEMOD_PRINT("frequency = %d\n",pDemodInfo->setCfgParam.dvbs2.frequency);
	DEMOD_PRINT("symbolRate = %d\n",pDemodInfo->setCfgParam.dvbs2.symbolRate);
	DEMOD_PRINT("tuneMode = %d\n",pDemodInfo->setCfgParam.dvbs2.tuneMode);
	DEMOD_PRINT("operatingMode = %d\n",pDemodInfo->setCfgParam.dvbs2.operatingMode);
/*
	if(RET_OK != DEMOD_StdOperModeContrl(operMode, bandWd,	symbr))
	{
		DEMOD_PRINT("[DEMOD] FAIL (%s:%d) DEMOD_StdOperModeContrl() !!!\n", __F__, __L__);
		DEMOD_RETURN_FAIL(__F__);
	}
*/

	//	usleep_range(40000,50000);	/* 1ms ~ 10ms */
		usleep_range(30000,35000);	/* 40ms ~ 50ms Tuner Stabilization time for pervention channel skip */


	if(RET_OK != DEMOD_DVBS2_Set_DefaultRegisterValue())
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBS2_Set_DefaultRegisterValue()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(pDemodInfo->setCfgParam.dvbs2.operatingMode != LX_DEMOD_DVBS_BLIND_SCAN_MODE)
	{
		if(RET_OK != DEMOD_DVBS2_Set_Config_auto(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_DVBS2_Set_Config_auto()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}

	DEMOD_LockDevice();

	//Send event for Tuning task
	g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD Task START\n");

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * _DEMOD_ChannelChangeATSC3.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_ChannelChangeATSC3(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_LockDevice();

	pDemodInfo->setCfgParam.atsc3.tuneMode 		= pDemodCfg->atsc3.tuneMode;
	pDemodInfo->setCfgParam.atsc3.bSpectrumInv 	= pDemodCfg->atsc3.bSpectrumInv;
	//pDemodInfo->systemMode						= pDemodCfg->atsc3.constellation;
	pDemodInfo->setCfgParam.atsc3.plpData[0] 	= pDemodCfg->atsc3.plpData[0];
	pDemodInfo->setCfgParam.atsc3.plpData[1] 	= pDemodCfg->atsc3.plpData[1];
	pDemodInfo->setCfgParam.atsc3.plpData[2] 	= pDemodCfg->atsc3.plpData[2];
	pDemodInfo->setCfgParam.atsc3.plpData[3]	= pDemodCfg->atsc3.plpData[3];
	pDemodInfo->bIsTPoutEn 						= TRUE;

	DEMOD_PRINT("atsc3 tuneMode[0x%02x], constellation[0x%02x]\n", pDemodInfo->setCfgParam.atsc3.tuneMode, pDemodInfo->systemMode);
	DEMOD_UnlockDevice();

	usleep_range(40000,50000);	/* 40ms ~ 50ms Tuner Stabilization time for pervention channel skip */

	if(gPanama)
	{
		DEMOD_ADC_Enable();
		DEMOD_INFO("DEMOD_ADC_Enable for Panama\n");
	}

	DEMOD_LockDevice();

	//Send event for Tuning task
	if(pDemodInfo->instantBoot == TRUE)
	{
		DEMOD_NOTI("Check instant boot ATSC3 tuning task\n");
		g_requestMsg = LX_DEMOD_INSTANTBOOT_TUNE_REQUEST;
		wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	}
	else
	{
		g_requestMsg = LX_DEMOD_NEWTUNE_REQUEST;
		wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	}


	DEMOD_UnlockDevice();
	DEMOD_NOTI("DEMOD ATSC3 Task START\n");

	pDemodInfo->getCfgParam.atsc3.plpData[0] = pDemodCfg->atsc3.plpData[0];
	pDemodInfo->getCfgParam.atsc3.plpData[1] = pDemodCfg->atsc3.plpData[1];
	pDemodInfo->getCfgParam.atsc3.plpData[2] = pDemodCfg->atsc3.plpData[2];
	pDemodInfo->getCfgParam.atsc3.plpData[3] = pDemodCfg->atsc3.plpData[3];
	return RET_OK;

}


#if 0
#endif

/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_VSB
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_VSB(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_BWMODE_T 				channelBW;
	LX_DEMOD_LOCK_STATE_T 			spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 			spectrumInv;

	//BandWidth ?
	if(RET_OK != DEMOD_Get_BandWidthMode(&channelBW ))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_BandWidthMode()\n");
	}

	//Spectrum inversion ?
	if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus()\n");
	}
	if(LX_DEMOD_AUTO == spectrumAuto)
	{
		pDemodInfo->getCfgParam.vsb.bSpectrumInv = (spectrumInv == LX_DEMOD_INVERSION) ? TRUE : FALSE;;
	}
	else
	{
		pDemodInfo->getCfgParam.vsb.bSpectrumInv = pDemodInfo->setCfgParam.vsb.bSpectrumInv ;
	}

	pDemodInfo->getCfgParam.vsb.tuneMode 	= pDemodInfo->setCfgParam.vsb.tuneMode;
	pDemodInfo->getCfgParam.vsb.channelBW 	= channelBW;
	pDemodInfo->systemMode					= LX_DEMOD_VSB;
	pDemodInfo->bSignalStatusValid			= TRUE;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_QAM
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_QAM(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_BWMODE_T 				channelBW;
	LX_DEMOD_LOCK_STATE_T 			spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 			spectrumInv;
	LX_DEMOD_RF_MODE_T		 		qamMode;

	//BandWidth ?
	if(RET_OK != DEMOD_Get_BandWidthMode(&channelBW ))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_BandWidthMode()\n");
	}

	//Spectrum inversion ?
	if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus()\n");
	}

	if(LX_DEMOD_AUTO == spectrumAuto)
	{
		pDemodInfo->getCfgParam.qam.bSpectrumInv	= (spectrumInv == LX_DEMOD_INVERSION) ? TRUE : FALSE;;
	}
	else
	{
		pDemodInfo->getCfgParam.qam.bSpectrumInv	= pDemodInfo->setCfgParam.qam.bSpectrumInv;
	}

	//QAM mode	?
	if(RET_OK != DEMOD_Get_QAMMode(&qamMode))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_QAMMode()\n");
	}



	pDemodInfo->getCfgParam.qam.tuneMode		= pDemodInfo->setCfgParam.qam.tuneMode;
	pDemodInfo->getCfgParam.qam.channelBW		= pDemodInfo->setCfgParam.qam.channelBW;
	pDemodInfo->getCfgParam.qam.qamMode			= qamMode;
	pDemodInfo->systemMode						= qamMode;
	pDemodInfo->bSignalStatusValid				= TRUE;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_ISDBT
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_ISDBT(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_BWMODE_T 				channelBW;
	LX_DEMOD_LOCK_STATE_T 			spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 			spectrumInv;
	LX_DEMOD_LOCK_STATE_T 			txModeLock;
	LX_DEMOD_FFTMODE_T				fftMode;
	LX_DEMOD_GIMODE_T 				gIMode;
	LX_DEMOD_ISDBT_TMCC_CONFIG_T 	tmccParams;


	//BandWidth ?
	if(RET_OK != DEMOD_Get_BandWidthMode(&channelBW ))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_BandWidthMode()\n");
	}

	//Spectrum inversion ?
	if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus()\n");
	}
	if(LX_DEMOD_AUTO == spectrumAuto)
	{
		pDemodInfo->getCfgParam.isdbt.bSpectrumInv	= (spectrumInv == LX_DEMOD_INVERSION) ? TRUE : FALSE;
	}
	else
	{
		pDemodInfo->getCfgParam.isdbt.bSpectrumInv	= pDemodInfo->setCfgParam.isdbt.bSpectrumInv;
	}

	//FFT mode ?
	if(RET_OK != DEMOD_ISDBT_Get_FFTMode(&txModeLock, &fftMode))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBT_Get_FFTMode()\n");
	}


	//GI mode ?
	if(RET_OK != DEMOD_ISDBT_Get_GuradIntervalMode(&gIMode))
	{
		DEMOD_ERROR("FAIL, DEMOD_ISDBT_Get_GuradIntervalMode()\n");
	}


	//TMCC info ?
	if(RET_OK != DEMOD_ISDBT_Get_TMCCInfo(&tmccParams))
	{
		DEMOD_ERROR("FAIL, DEMOD_ISDBT_Get_TMCCInfo()\n");
	}


	pDemodInfo->getCfgParam.isdbt.tuneMode		= pDemodInfo->setCfgParam.isdbt.tuneMode;
	pDemodInfo->getCfgParam.isdbt.channelBW		= pDemodInfo->setCfgParam.isdbt.channelBW	;
	pDemodInfo->getCfgParam.isdbt.FFTMode		= (txModeLock == LX_DEMOD_LOCKED) ? fftMode : LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
	pDemodInfo->getCfgParam.isdbt.gIMode 		= gIMode;

	memcpy(&(pDemodInfo->getCfgParam.isdbt.tmcc), &tmccParams, sizeof(LX_DEMOD_ISDBT_TMCC_CONFIG_T) );


	if((tmccParams.layerASegmentNum > tmccParams.layerBSegmentNum) && (tmccParams.layerASegmentNum > tmccParams.layerCSegmentNum))
  	{
  		pDemodInfo->systemMode = tmccParams.layerAQamMode;
  	}
  	else if((tmccParams.layerBSegmentNum > tmccParams.layerASegmentNum) && (tmccParams.layerBSegmentNum > tmccParams.layerCSegmentNum))
  	{
  		pDemodInfo->systemMode = tmccParams.layerBQamMode;
  	}
  	 else if((tmccParams.layerCSegmentNum > tmccParams.layerASegmentNum) && (tmccParams.layerCSegmentNum > tmccParams.layerBSegmentNum))
  	{
  		pDemodInfo->systemMode = tmccParams.layerCQamMode;
  	}
  	else
  	{
  		pDemodInfo->systemMode = LX_DEMOD_UNKOWN_MODE;
  	}
	pDemodInfo->bSignalStatusValid = TRUE;

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_DVBT
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_DVBT(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T 			spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 			spectrumInv;
	LX_DEMOD_FFTMODE_T				fftMode;
	LX_DEMOD_GIMODE_T 				gIMode;
	LX_DEMOD_LOCK_STATE_T			lockState;
	LX_DEMOD_SIGNAL_TUNE_CFG_T		tuneCfg;

	if(RET_OK != DEMOD_Tune_Cfg_infomation(&tuneCfg))
	{
		DEMOD_ERROR("FAIL, DEMOD_Tune_Cfg_infomation()\n");
		DEMOD_RETURN_FAIL(__F__);
	}


	switch(tuneCfg.fftMode)
	{
		case DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_2K :
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_2K;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_4K:
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_4K;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_FFT_MODE_8K:
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_8K;
			break;
		default :
			fftMode = LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
			break;
	}
	switch(tuneCfg.guardInterval)
	{
		case DEMOD_DVBT_STATUS_RESPONSE_GI_1_32 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_32;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_GI_1_16:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_16;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_GI_1_8 :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_8;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_GI_1_4:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_4;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_GI_1_128:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_128;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_GI_19_128:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_128;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_GI_19_256:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_19_256;
			break;
		case DEMOD_DVBT_STATUS_RESPONSE_GI_1_64:
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_1_64;
			break;
		default :
			gIMode = LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN;
			break;
	}

	if(RET_OK != DEMOD_Get_Lock(LX_DEMOD_TPS_LOCK, &lockState))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_Lock()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if((gIMode != LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN) || (lockState != LX_DEMOD_UNLOCKED) )
	{
		switch(tuneCfg.constellation)
		{
			case DEMOD_STATUS_RESPONSE_CONSTELLATION_QPSK :
				pDemodInfo->getCfgParam.dvbt.qamMode = LX_DEMOD_QPSK;
				break;
			case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM16 :
				pDemodInfo->getCfgParam.dvbt.qamMode = LX_DEMOD_16QAM;
				break;
			case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM64 :
				pDemodInfo->getCfgParam.dvbt.qamMode = LX_DEMOD_64QAM;
				break;
			default :
				pDemodInfo->getCfgParam.dvbt.qamMode = LX_DEMOD_UNKOWN_MODE;
				break;
		}
		//High or Low prioty ?
		if(TRUE == pDemodInfo->setCfgParam.dvbt.bSetHp)
		{
			if(tuneCfg.hierarchy_sel == DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_HP)
			{
				switch(tuneCfg.codeRate)
				{
					case DEMOD_DVBT_STATUS_RESPONSE_CR_1_2 :
						pDemodInfo->getCfgParam.dvbt.hpCodeRate = LX_DEMOD_CODE_1_2;
						break;
					case DEMOD_DVBT_STATUS_RESPONSE_CR_2_3:
						pDemodInfo->getCfgParam.dvbt.hpCodeRate = LX_DEMOD_CODE_2_3;
						break;
					case DEMOD_DVBT_STATUS_RESPONSE_CR_3_4 :
						pDemodInfo->getCfgParam.dvbt.hpCodeRate = LX_DEMOD_CODE_3_4;
						break;
					case DEMOD_DVBT_STATUS_RESPONSE_CR_5_6:
						pDemodInfo->getCfgParam.dvbt.hpCodeRate = LX_DEMOD_CODE_5_6;
						break;
					case DEMOD_DVBT_STATUS_RESPONSE_CR_7_8:
						pDemodInfo->getCfgParam.dvbt.hpCodeRate = LX_DEMOD_CODE_7_8;
						break;
					default :
						pDemodInfo->getCfgParam.dvbt.hpCodeRate = LX_DEMOD_CODE_UNKNOWN;
						break;
				}
			}
			else
			{
				pDemodInfo->getCfgParam.dvbt.hpCodeRate = LX_DEMOD_CODE_UNKNOWN;
			}
		}
		else
		{
			if(tuneCfg.hierarchy_sel == DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_SEL_LP)
			{
				switch(tuneCfg.codeRate)
				{
					case DEMOD_DVBT_STATUS_RESPONSE_CR_1_2 :
						pDemodInfo->getCfgParam.dvbt.lpCodeRate = LX_DEMOD_CODE_1_2;
						break;
					case DEMOD_DVBT_STATUS_RESPONSE_CR_2_3:
						pDemodInfo->getCfgParam.dvbt.lpCodeRate = LX_DEMOD_CODE_2_3;
						break;
					case DEMOD_DVBT_STATUS_RESPONSE_CR_3_4 :
						pDemodInfo->getCfgParam.dvbt.lpCodeRate = LX_DEMOD_CODE_3_4;
						break;
					case DEMOD_DVBT_STATUS_RESPONSE_CR_5_6:
						pDemodInfo->getCfgParam.dvbt.lpCodeRate = LX_DEMOD_CODE_5_6;
						break;
					case DEMOD_DVBT_STATUS_RESPONSE_CR_7_8:
						pDemodInfo->getCfgParam.dvbt.lpCodeRate = LX_DEMOD_CODE_7_8;
						break;
					default :
						pDemodInfo->getCfgParam.dvbt.lpCodeRate = LX_DEMOD_CODE_UNKNOWN;
						break;
				}
			}
			else
			{
				pDemodInfo->getCfgParam.dvbt.lpCodeRate = LX_DEMOD_CODE_UNKNOWN;
			}
		}
		//Hierachy mode ?

		switch(tuneCfg.hierarchy)
		{
			case DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_NONE :
				pDemodInfo->getCfgParam.dvbt.hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_NONE;
				break;
			case DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA1:
				pDemodInfo->getCfgParam.dvbt.hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_1;
				break;
			case DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA2 :
				pDemodInfo->getCfgParam.dvbt.hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_2;
				break;
			case DEMOD_DVBT_STATUS_RESPONSE_HIERARCHY_ALFA4:
				pDemodInfo->getCfgParam.dvbt.hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_4;
				break;
			default :
				pDemodInfo->getCfgParam.dvbt.hierachMode = LX_DEMOD_DVB_TPS_HIERACHY_UNKNOWN;
				break;
		}

		//Spectrum inversion ?
		if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
		{
			DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus()\n");
		}

		if(LX_DEMOD_AUTO == spectrumAuto)
		{
			pDemodInfo->getCfgParam.dvbt.bSpectrumInv	= (spectrumInv == LX_DEMOD_INVERSION) ? TRUE : FALSE;
		}
		else
		{
			pDemodInfo->getCfgParam.dvbt.bSpectrumInv	= pDemodInfo->setCfgParam.dvbt.bSpectrumInv;
		}
	}
	else
	{
		DEMOD_ERROR("FAIL, GI(%d) is UNLOCKED !! \n",gIMode);

	}

	pDemodInfo->getCfgParam.dvbt.tuneMode		= pDemodInfo->setCfgParam.dvbt.tuneMode;
	pDemodInfo->getCfgParam.dvbt.channelBW		= pDemodInfo->setCfgParam.dvbt.channelBW;
	pDemodInfo->getCfgParam.dvbt.bSetHp 		= pDemodInfo->setCfgParam.dvbt.bSetHp;
	pDemodInfo->getCfgParam.dvbt.FFTMode		= (lockState == LX_DEMOD_LOCKED) ? fftMode : LX_DEMOD_DVBT_ISDBT_FFT_UNKNOWN;
	pDemodInfo->getCfgParam.dvbt.gIMode 		= gIMode;
//	pDemodInfo->getCfgParam.dvbt.qamMode		= pDemodInfo->setCfgParam.dvbt.qamMode;
	pDemodInfo->systemMode						= pDemodInfo->getCfgParam.dvbt.qamMode;
	pDemodInfo->bSignalStatusValid				= TRUE;

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_DVBT2
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_DVBT2(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_DVBT2_CONFIG_T 		plpParams;
	LX_DEMOD_LOCK_STATE_T 			spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 			spectrumInv;


	//BandWidth ?
	if(RET_OK != DEMOD_DVBT2_Get_PlpInfo( &plpParams))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBT2_Get_PlpInfo()\n");
	}

	if(plpParams.gIMode == LX_DEMOD_DVBT_ISDBT_GIMODE_UNKNOWN)
	{
		DEMOD_ERROR("FAIL, GI(%d) is UNLOCKED !! \n",plpParams.gIMode);
		DEMOD_RETURN_FAIL(__F__);
	}

	//Spectrum inversion ?
	if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus()\n");
	}
	if(LX_DEMOD_AUTO == spectrumAuto)
	{
		pDemodInfo->getCfgParam.dvbt2.bSpectrumInv	= (spectrumInv == LX_DEMOD_INVERSION) ? TRUE : FALSE;
	}
	else
	{
		pDemodInfo->getCfgParam.dvbt2.bSpectrumInv	= pDemodInfo->getCfgParam.dvbt.bSpectrumInv;
	}


	pDemodInfo->getCfgParam.dvbt2.tuneMode		= pDemodInfo->setCfgParam.dvbt2.tuneMode;
	pDemodInfo->getCfgParam.dvbt2.channelBW		= pDemodInfo->setCfgParam.dvbt2.channelBW;
	pDemodInfo->getCfgParam.dvbt2.FFTMode		= plpParams.FFTMode;
	pDemodInfo->getCfgParam.dvbt2.gIMode 		= plpParams.gIMode;
	pDemodInfo->getCfgParam.dvbt2.codeRate		= plpParams.codeRate;
	pDemodInfo->getCfgParam.dvbt2.qamMode		= plpParams.qamMode;
	pDemodInfo->getCfgParam.dvbt2.unPLP			= plpParams.unPLP;
	pDemodInfo->getCfgParam.dvbt2.qamMode		= plpParams.qamMode;
	pDemodInfo->systemMode						= plpParams.qamMode;
	pDemodInfo->bSignalStatusValid				= TRUE;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_DVBC
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_DVBC(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T 				spectrumAuto;
	LX_DEMOD_LOCK_STATE_T 				spectrumInv;
	LX_DEMOD_QAMMODE_STATE_T 			qamModeDet;
	LX_DEMOD_SYMBOLRATE_STATE_T 		symbolRateDet;
	LX_DEMOD_LOCK_STATE_T				lockState;
	LX_DEMOD_SIGNAL_TUNE_CFG_T		tuneCfg;

	if(RET_OK != DEMOD_Tune_Cfg_infomation(&tuneCfg))
	{
		DEMOD_ERROR("FAIL, DEMOD_Tune_Cfg_infomation()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	//Spectrum inversion ?
	if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus()\n");
	}

	if(LX_DEMOD_AUTO == spectrumAuto)
	{
		pDemodInfo->getCfgParam.dvbc.bSpectrumInv	= (spectrumInv == LX_DEMOD_INVERSION) ? TRUE : FALSE;;
	}
	else
	{
		pDemodInfo->getCfgParam.dvbc.bSpectrumInv	= pDemodInfo->setCfgParam.dvbc.bSpectrumInv;
	}

	if(RET_OK != DEMOD_Get_Lock(LX_DEMOD_TPS_LOCK, &lockState))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_Lock()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	if(lockState != LX_DEMOD_UNLOCKED)
	{
		switch (tuneCfg.constellation)
		{
			case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM16	:
				qamModeDet.qamMode = LX_DEMOD_16QAM;
				break;
			case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM32	:
				qamModeDet.qamMode = LX_DEMOD_32QAM;
				break;
			case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM64	:
				qamModeDet.qamMode = LX_DEMOD_64QAM;
				break;
			case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM128	:
				qamModeDet.qamMode = LX_DEMOD_128QAM;
				break;
			case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM256	:
				qamModeDet.qamMode = LX_DEMOD_256QAM;
				break;
			default  :
				qamModeDet.qamMode = LX_DEMOD_UNKOWN_MODE;
				break;
		}
		qamModeDet.status 	= LX_DEMOD_DETECTED;
	}
	else
	{
		qamModeDet.qamMode = LX_DEMOD_UNKOWN_MODE;
		qamModeDet.status 	= LX_DEMOD_UNLOCKED;
	}

	if((LX_DEMOD_DETECTED == qamModeDet.status) || (LX_DEMOD_DETECTION_MANUAL == qamModeDet.status))
	{
		pDemodInfo->getCfgParam.dvbc.qamMode		= qamModeDet.qamMode;
		pDemodInfo->systemMode						= qamModeDet.qamMode;
	}
	else
	{
		pDemodInfo->getCfgParam.dvbc.qamMode		= LX_DEMOD_UNKOWN_MODE;
		pDemodInfo->systemMode						= LX_DEMOD_UNKOWN_MODE;
	}

	symbolRateDet.status 			= LX_DEMOD_DETECTED;
	symbolRateDet.symbolRate 		= tuneCfg.sym_rate ;

	if(LX_DEMOD_DETECTED == symbolRateDet.status)
	{
		pDemodInfo->getCfgParam.dvbc.symbolRate = symbolRateDet.symbolRate;
	}
	else
	{
		pDemodInfo->getCfgParam.dvbc.symbolRate = pDemodInfo->setCfgParam.dvbc.symbolRate;
	}

	pDemodInfo->getCfgParam.dvbc.tuneMode		= pDemodInfo->setCfgParam.dvbc.tuneMode;
	pDemodInfo->getCfgParam.dvbc.channelBW		= pDemodInfo->setCfgParam.dvbc.channelBW;
	pDemodInfo->bSignalStatusValid				= TRUE;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_DVBS
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_DVBS(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T				spectrumAuto;
	LX_DEMOD_LOCK_STATE_T				spectrumInv;
	UINT32 								symbolRate;
	LX_DEMOD_CODERATE_T 				codeRate;
	LX_DEMOD_SIGNAL_TUNE_CFG_T			tuneCfg;

	if(RET_OK != DEMOD_Tune_Cfg_infomation(&tuneCfg))
	{
		DEMOD_ERROR("FAIL, DEMOD_Tune_Cfg_infomation()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	//Spectrum inversion ?
	if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus()\n");
	}
	if(LX_DEMOD_AUTO == spectrumAuto)
	{
		pDemodInfo->getCfgParam.dvbs.bSpectrumInv	= (spectrumInv == LX_DEMOD_INVERSION) ? TRUE : FALSE;
	}
	else
	{
		pDemodInfo->getCfgParam.dvbs.bSpectrumInv	= pDemodInfo->setCfgParam.dvbs.bSpectrumInv;
	}
	//symbol rate
	symbolRate = tuneCfg.sym_rate;
	//code rate
	switch(tuneCfg.codeRate)
	{
		case 0x00 :
			codeRate = LX_DEMOD_CODE_1_2;
			break;
		case 0x02:
			codeRate = LX_DEMOD_CODE_2_3;
			break;
		case 0x04 :
			codeRate = LX_DEMOD_CODE_3_4;
			break;
		case 0x08:
			codeRate = LX_DEMOD_CODE_5_6;
			break;
		case 0x09:
			codeRate = LX_DEMOD_CODE_7_8;
			break;
		default :
			codeRate = LX_DEMOD_CODE_UNKNOWN;
			break;
	}

	pDemodInfo->getCfgParam.dvbs.tuneMode		= pDemodInfo->setCfgParam.dvbs.tuneMode;
	pDemodInfo->getCfgParam.dvbs.symbolRate		= symbolRate;
	pDemodInfo->getCfgParam.dvbs.codeRate		= codeRate;
	pDemodInfo->getCfgParam.dvbs.constellation	= LX_DEMOD_QPSK;
	pDemodInfo->systemMode						= LX_DEMOD_QPSK;
	pDemodInfo->bSignalStatusValid				= TRUE;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_DVBS2
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_DVBS2(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_LOCK_STATE_T			spectrumAuto;
	LX_DEMOD_LOCK_STATE_T			spectrumInv;
	UINT32 							symbolRate;
	BOOLEAN 						pilot;
	LX_DEMOD_CODERATE_T 			codeRate;
	LX_DEMOD_RF_MODE_T 				qamMode;


	//Spectrum inversion ?
	if(RET_OK != DEMOD_Get_SpectrumStatus(&spectrumAuto, &spectrumInv))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_SpectrumStatus()\n");
	}
	if(LX_DEMOD_AUTO == spectrumAuto)
	{
		pDemodInfo->getCfgParam.dvbs2.bSpectrumInv	= (spectrumInv == LX_DEMOD_INVERSION) ? TRUE : FALSE;
	}
	else
	{
		pDemodInfo->getCfgParam.dvbs2.bSpectrumInv	= pDemodInfo->getCfgParam.dvbs.bSpectrumInv;
	}
	//symbol rate
	if(RET_OK != DEMOD_DVBS2_Get_SymbolRate(&symbolRate))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBS2_Get_SymbolRate()\n");
	}

	//bPilot
	if(RET_OK != DEMOD_DVBS2_Get_Pilot(&pilot)) // return false of fixed value
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBS2_Get_Pilot()\n");
	}
	//code rate
	if(RET_OK != DEMOD_DVBS2_Get_CoderRate(&codeRate ))
	{
		DEMOD_ERROR("FAIL, DEMOD_DVBS2_Get_CoderRate()\n");
	}

	//QAM mode
	if(RET_OK != DEMOD_Get_QAMMode(&qamMode))
	{
		DEMOD_ERROR("FAIL, DEMOD_Get_QAMMode()\n");
	}


	pDemodInfo->getCfgParam.dvbs2.tuneMode		= pDemodInfo->setCfgParam.dvbs2.tuneMode;
	pDemodInfo->getCfgParam.dvbs2.symbolRate	= symbolRate;
	pDemodInfo->getCfgParam.dvbs2.bPilot		= pilot;
	pDemodInfo->getCfgParam.dvbs2.codeRate		= codeRate;
	pDemodInfo->getCfgParam.dvbs2.constellation	= qamMode;
	pDemodInfo->systemMode						= qamMode;
	pDemodInfo->bSignalStatusValid				= TRUE;

	return RET_OK;


}


/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_ANALOG
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_ANALOG(DEMOD_CTX_T *pDemodInfo)
{

	pDemodInfo->getCfgParam.analog.freqOffset 	= pDemodInfo->freqOffset;
	pDemodInfo->bSignalStatusValid			= TRUE;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_DTMB
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	jinwoo.han (jinwoo.han@lge.com)
*/

int _DEMOD_Get_TunedCFG_DTMB(DEMOD_CTX_T *pDemodInfo)
{
	BOOLEAN							bM720;				///< Time interval 240 or 720
	LX_DEMOD_CARRIERMODE_T 			carrierMode;		///< carrier mode
	LX_DEMOD_PNMODE_T 				pnMode;				///< PN Mode
	LX_DEMOD_CODERATE_T 			codeRate;			///< ?? FEC rates
	LX_DEMOD_RF_MODE_T				constellation;
	LX_DEMOD_SIGNAL_TUNE_CFG_T		tuneCfg;

	if(RET_OK != DEMOD_Tune_Cfg_infomation(&tuneCfg))
	{
		DEMOD_ERROR("FAIL, DEMOD_Tune_Cfg_infomation()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	//Time Interval
	bM720 = (tuneCfg.il_mode == DEMOD_DTMB_STATUS_RESPONSE_IL_MODE_720) ? TRUE : FALSE ;

	//carrier mode
	switch(tuneCfg.carr_mode)
	{
		case DEMOD_DTMB_STATUS_RESPONSE_CARR_MODE_SC :
			carrierMode = LX_DEMOD_CARRIER_SINGLE;
			break;
		case DEMOD_DTMB_STATUS_RESPONSE_CARR_MODE_MC :
			carrierMode = LX_DEMOD_CARRIER_MULTI;
			break;
		default :
			carrierMode = LX_DEMOD_CARRIER_UNKNOWN;
			break;
	}

	//PN mode
	 if(tuneCfg.pn_const == DEMOD_DTMB_STATUS_RESPONSE_PN_CONST_CONSTANT)
 	{
		switch(tuneCfg.pn_mode)
		{
			case DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN420 :
				pnMode = LX_DEMOD_TPS_GUARD_420_C;
				break;
			case DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN595 :
				pnMode = LX_DEMOD_TPS_GUARD_595;
				break;
			case DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN945 :
				pnMode = LX_DEMOD_TPS_GUARD_945_C;
				break;
			default :
				pnMode = LX_DEMOD_TPS_GUARD_UNKNOWN;
				break;
		}
	}
	else
	{
		switch(tuneCfg.pn_mode)
		{
			case DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN420 :
				pnMode = LX_DEMOD_TPS_GUARD_420_V;
				break;
			case DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN595 :
				pnMode = LX_DEMOD_TPS_GUARD_595;
				break;
			case DEMOD_DTMB_STATUS_RESPONSE_PN_MODE_PN945 :
				pnMode = LX_DEMOD_TPS_GUARD_945_V;
				break;
			default :
				pnMode = LX_DEMOD_TPS_GUARD_UNKNOWN;
				break;
		}
	}

	//codeRate
	switch(tuneCfg.codeRate)
	{
		case DEMOD_STATUS_RESPONSE_CODERATE_2_5:
			codeRate = LX_DEMOD_CODE_2_5;
			break;
		case DEMOD_STATUS_RESPONSE_CODERATE_3_5:
			codeRate = LX_DEMOD_CODE_3_5;
			break;
		case DEMOD_STATUS_RESPONSE_CODERATE_4_5:
			codeRate = LX_DEMOD_CODE_4_5;
			break;
		default :
			codeRate = LX_DEMOD_CODE_UNKNOWN;
			break;
	}

	//constellation
	switch(tuneCfg.constellation)
	{
		case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM4NR :
			constellation = LX_DEMOD_4QAM_NR;
			break;
		case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM4:
			constellation = LX_DEMOD_4QAM;
			break;
		case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM16:
			constellation = LX_DEMOD_16QAM;
			break;
		case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM32:
			constellation = LX_DEMOD_32QAM;
			break;
		case DEMOD_STATUS_RESPONSE_CONSTELLATION_QAM64:
			constellation = LX_DEMOD_64QAM;
			break;
		default :
			constellation = LX_DEMOD_UNKOWN_MODE;
			break;
	}

	pDemodInfo->getCfgParam.dtmb.tuneMode		= pDemodInfo->setCfgParam.dtmb.tuneMode;
	pDemodInfo->getCfgParam.dtmb.channelBW		= pDemodInfo->setCfgParam.dtmb.channelBW;
	pDemodInfo->getCfgParam.dtmb.bM720 			= bM720;
	pDemodInfo->getCfgParam.dtmb.carrierMode	= carrierMode;
	pDemodInfo->getCfgParam.dtmb.pnMode			= pnMode;
	pDemodInfo->getCfgParam.dtmb.codeRate		= codeRate;
	pDemodInfo->getCfgParam.dtmb.constellation	= constellation;
	pDemodInfo->systemMode						= constellation;
	pDemodInfo->bSignalStatusValid				= TRUE;

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
* _DEMOD_Get_TunedCFG_ATSC3
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int _DEMOD_Get_TunedCFG_ATSC3(DEMOD_CTX_T *pDemodInfo)
{

	LX_DEMOD_ATSC3_GIMODE_T				GIMode;
	LX_DEMOD_FFTMODE_T					FftMode;
	LX_DEMOD_ATSC3_CODERATE_T			CodeRate;
	LX_DEMOD_ATSC3_CONSTELLATION_T		Constellation;
	LX_DEMOD_ATSC3_MULTI_PLP_ID_T 		Atsc3mPLPInfo;

	if(RET_OK != DEMOD_ATSC3_Get_GuradIntervalMode(&GIMode ))
	{
		DEMOD_ERROR("FAIL, DEMOD_ATSC3_Get_GuradIntervalMode()\n");
	}

	if(RET_OK != DEMOD_ATSC3_Get_FFTMode(&FftMode ))
	{
		DEMOD_ERROR("FAIL, DEMOD_ATSC3_Get_FFTMode()\n");
	}

	if(RET_OK != DEMOD_ATSC3_Get_CodeRate(&CodeRate ))
	{
		DEMOD_ERROR("FAIL, DEMOD_ATSC3_Get_CodeRate()\n");
	}

	if(RET_OK != DEMOD_ATSC3_Get_Constellation(&Constellation ))
	{
		DEMOD_ERROR("FAIL, DEMOD_ATSC3_Get_Constellation()\n");
	}

	if(RET_OK != DEMOD_ATSC3_Get_MPLP_Info(&Atsc3mPLPInfo, LX_DEMOD_LLS_ONLY_PLP_ID))
	{
		DEMOD_ERROR("FAIL, DEMOD_ATSC3_Get_MPLP_Info()\n");
	}

	pDemodInfo->getCfgParam.atsc3.tuneMode 	= pDemodInfo->setCfgParam.atsc3.tuneMode;
	//pDemodInfo->getCfgParam.atsc3.
	//	.unPLP			= plpParams.unPLP;

	pDemodInfo->getCfgParam.atsc3.gIMode 			= GIMode;
	pDemodInfo->getCfgParam.atsc3.FFTMode 			= FftMode;
	pDemodInfo->getCfgParam.atsc3.codeRate 			= CodeRate;
	pDemodInfo->getCfgParam.atsc3.constellation 	= Constellation;


	return RET_OK;

}



#if 0
#endif

/***********************************************************************************
* Common function
************************************************************************************/

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_MediaChange.
 * Set stand operation mode
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pTranMedia  [IN] LX_DEMOD_INIT_PARAM_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

#define CHECK_DVB_TER(opmode)		((LX_DEMOD_DVBT == opmode) || (LX_DEMOD_DVBT2 == opmode))
#define CHECK_DVB_CAB(opmode)		((LX_DEMOD_DVBC == opmode))
#define CHECK_DVB_SAT(opmode)		((LX_DEMOD_DVBS == opmode) || (LX_DEMOD_DVBS2 == opmode))
#define CHECK_DVB_TER_CAB(opmode)	(CHECK_DVB_TER(opmode) || CHECK_DVB_CAB(opmode))
#define CHECK_DVB(opmode)		(CHECK_DVB_TER(opmode) || CHECK_DVB_CAB(opmode) || CHECK_DVB_SAT(opmode))
#define CHECK_SLEEP(opmode)		(opmode == LX_DEMOD_UNKOWN_OPMODE || opmode == LX_DEMOD_DIGITAL_Sleep || opmode == LX_DEMOD_ALWAYSREADY)

int DEMOD_MediaChange(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_INIT_PARAM_T *pTranMedia)
{
	DEMOD_DEV_T	*pDemodDev = DEMOD_Get_Device_Data();
	DEMOD_NOTI("[%s]\n",__FUNCTION__);
	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}
	if(NULL == pTranMedia)
	{
		DEMOD_RETURN_FAIL(__F__);
	}
	if(NULL == pDemodDev)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_NOTI("MediaChange %s(0x%02x) => %s(0x%02x), mem %d, swt %d\n",
			DEMOD_Get_OPER_MODE_Name(pDemodInfo->operMode), pDemodInfo->operMode,
			DEMOD_Get_OPER_MODE_Name(pTranMedia->operMode), pTranMedia->operMode,
			pDemodDev->mem_alloc, pDemodDev->sw_type);
	pDemodInfo->tranMode = pTranMedia->operMode;

	if (!CHECK_SLEEP(pTranMedia->operMode) && (FALSE == pDemodDev->apb_access)) {
		DEMOD_NOTI("enable APB Access\n");
		if (RET_OK != DEMOD_APB_AccessControl(TRUE))
		{
			DEMOD_ERROR("FAIL, DEMOD_APB_AccessControl()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}

	if (CHECK_DVB_TER_CAB(pDemodInfo->operMode) && CHECK_DVB_SAT(pTranMedia->operMode))		// DVB T/T2/C -> DVB S/S2
	{
		DEMOD_OperModeReset(LX_DEMOD_DVBS);

		if(RET_OK != DEMOD_SAT_FW_Initialize())
		{
			DEMOD_ERROR("FAIL, DEMOD_SAT_FW_Initialize()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		DEMOD_NOTI("DEMOD Reset for DVB-S / S2\n");
		OS_MsecSleep(10);

		DEMOD_FW_Configuration_Initialize(pTranMedia->operMode);
	}
	else if (CHECK_DVB_SAT(pDemodInfo->operMode) && CHECK_DVB_TER(pTranMedia->operMode))		// DVB S/S2 -> DVB T/T2
	{
		DEMOD_OperModeReset(LX_DEMOD_DVBT);

		if(RET_OK != DEMOD_FW_Initialize())
		{
			DEMOD_ERROR("FAIL, DEMOD_FW_Initialize()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		DEMOD_NOTI("DEMOD Reset for DVB-T / T2\n");
		OS_MsecSleep(10);

		DEMOD_FW_Configuration_Initialize(pTranMedia->operMode);
	}
	else if(CHECK_DVB_SAT(pDemodInfo->operMode) && CHECK_DVB_CAB(pTranMedia->operMode))		// DVB S/S2 -> DVB C
	{
		DEMOD_OperModeReset(LX_DEMOD_DVBC);

		if(RET_OK != DEMOD_FW_Initialize())
		{
			DEMOD_ERROR("FAIL, DEMOD_FW_Initialize(\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		OS_MsecSleep(10);

		DEMOD_FW_Configuration_Initialize(pTranMedia->operMode);

		DEMOD_DVB_Set_MemSconfig();
		DEMOD_NOTI("DEMOD Reset for DVB C\n");
	}
	else if (pTranMedia->operMode == LX_DEMOD_DTMB)							// any -> DTMB
	{
		DEMOD_OperModeReset(LX_DEMOD_DTMB);

		if(RET_OK != DEMOD_FW_Initialize())
		{
			DEMOD_PRINT("[DEMOD] FAIL, DEMOD_FW_Initialize()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
		DEMOD_FW_Configuration_Initialize(pTranMedia->operMode);

		DEMOD_PRINT("DEMOD Reset for DTMB\n");
	}
	else
	{
		if (pTranMedia->operMode == LX_DEMOD_DVBC)
		{
			if(RET_OK != DEMOD_DVB_C_reset())
			{
				DEMOD_ERROR("FAIL, DEMOD_DVB_C_reset()\n");
				DEMOD_RETURN_FAIL(__F__);
			}
//				resetFlagDVBC = TRUE;

			DEMOD_NOTI("DEMOD_DVB_C_reset\n");
		}

		DEMOD_INFO("Media_change_ panama[%d]\n",gPanama);
		if(gPanama)
		{
			if((pTranMedia->operMode == LX_DEMOD_ISDBT) || (pTranMedia->operMode == LX_DEMOD_ATSC) || (pTranMedia->operMode == LX_DEMOD_QAM))
			{
				if(RET_OK != DEMOD_DVB_C_reset())
				{
					DEMOD_ERROR("FAIL, DEMOD_DVB_C_reset()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
				DEMOD_NOTI("DEMOD_DVB_C_reset panama[%d]\n", gPanama);
			}
		}
	}

	/* to do ->  task stop */
	//Send event for Tuning task
	DEMOD_LockDevice();
	g_requestMsg = LX_DEMOD_STOP_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	DEMOD_UnlockDevice();

	if (CHECK_SLEEP(pTranMedia->operMode))
	{
		if (FALSE == pDemodDev->power_save) {
			if(RET_OK != DEMOD_Power_Save(TRUE))
			{
				DEMOD_ERROR("FAIL, DEMOD_Power_Save()\n");
				DEMOD_RETURN_FAIL(__F__);
			}

			if (RET_OK != DEMOD_APB_AccessControl(FALSE))
			{
				DEMOD_ERROR("FAIL, DEMOD_APB_AccessControl()\n");
				DEMOD_RETURN_FAIL(__F__);
			}

			OS_MsecSleep(10);
			DEMOD_UnregisterMemMap();
			DEMOD_INFO("DEMOD_RegisterMemMap done\n");
		} else {

		}
	}
	else
	{
		DEMOD_LockDevice();
		pDemodInfo->operMode	= pTranMedia->operMode;
		pDemodInfo->symbr	= pTranMedia->symbr;
		pDemodInfo->IFFrq	= pTranMedia->ifFrq;
		DEMOD_UnlockDevice();

		if (FALSE == pDemodDev->mem_alloc) {
			switch (pTranMedia->operMode) {
				case LX_DEMOD_DVBT:
				case LX_DEMOD_DVBT2:
				case LX_DEMOD_DVBC:
				case LX_DEMOD_DVBC2:
				case LX_DEMOD_DVBS:
				case LX_DEMOD_DVBS2:
					DEMOD_RegisterMemMap("dvb");
					break;
				case LX_DEMOD_ATSC:
				case LX_DEMOD_QAM:
					break;
				case LX_DEMOD_ATSC3:
					DEMOD_RegisterMemMap("atsc3");
					break;
				case LX_DEMOD_ISDBT:
					DEMOD_RegisterMemMap("isdbt");
					break;
				case LX_DEMOD_DTMB:
					DEMOD_RegisterMemMap("dtmb");
					break;
				default:
					break;
					
			}
			if (TRUE == pDemodDev->mem_alloc)
				DEMOD_INFO("DEMOD_RegisterMemMap done\n");
		} else {
			DEMOD_NOTI("DEMOD_RegisterMemMap skip, already done\n");
		}
		
		#ifndef PLATFORM_FPGA
		if((pTranMedia->operMode == LX_DEMOD_ATSC3))
		{
			sys_bwm_noti(BWM_OPT_DEFAULT,"demod.tune=atsc3");
			DEMOD_NOTI("change mem config atsc3\n");
		}
		else
		{
			sys_bwm_noti(BWM_OPT_DEFAULT,"demod.tune=others");
			DEMOD_NOTI("change mem config not atsc3\n");
		}
		#endif


		DEMOD_PRINT("Call the DEMOD_StdOperModeContrl\n");
		if(RET_OK != DEMOD_StdOperModeContrl(pTranMedia->operMode, pTranMedia->bandWd,	pTranMedia->symbr))
		{
			DEMOD_ERROR("FAIL, DEMOD_StdOperModeContrl()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		DEMOD_PRINT("check IF freq[%d KHz]\n", pDemodInfo->IFFrq);
		if(RET_OK != DEMOD_Set_IF_Frq(pDemodInfo->IFFrq))
		{
			DEMOD_ERROR("FAIL, DEMOD_Set_IF_Frq()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if (CHECK_DVB_TER(pDemodInfo->operMode))	// DVB T/T2
		{
			if(RET_OK != DEMOD_Set_CountryGrp(pDemodInfo->bCountryGrpEU))
			{
				DEMOD_ERROR("FAIL, DEMOD_Set_CountryGrp()\n");
				DEMOD_RETURN_FAIL(__F__);
			}

			DEMOD_PRINT("bCountryGrpEU is 0x%x\n",pDemodInfo->bCountryGrpEU);
		}
		else
		{
			DEMOD_PRINT("Dosen't set CountryGrp\n");

		}

		DEMOD_PRINT("DEMOD_Power_Save(FALSE)\n");
		if(RET_OK != DEMOD_Power_Save(FALSE))
		{
			DEMOD_ERROR("FAIL, DEMOD_Power_Save()\n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}

	DEMOD_NOTI("MediaChange %s(0x%02x) done, if %d, country %d, ps %d, mem %d, swt %d\n",
		DEMOD_Get_OPER_MODE_Name(pDemodInfo->operMode), pDemodInfo->operMode,
		pDemodInfo->IFFrq, pDemodInfo->bCountryGrpEU, pDemodDev->power_save, pDemodDev->mem_alloc, pDemodDev->sw_type);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ChannelChange.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @param *pDemodCfg  [IN] LX_DEMOD_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ChannelChange(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_CONFIG_T *pDemodCfg)
{
	DEMOD_NOTI("[%s]\n",__FUNCTION__);
	DEMOD_DEV_T	*pDemodDev = DEMOD_Get_Device_Data();

	if(NULL == pDemodInfo)
	{
		DEMOD_RETURN_FAIL(__F__);
	}
	if(NULL == pDemodCfg)
	{
		DEMOD_RETURN_FAIL(__F__);
	}
	if(NULL == pDemodDev)
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	/* task stop */
	//Send event for Tuning task
	DEMOD_LockDevice();
	g_requestMsg = LX_DEMOD_STOP_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	DEMOD_UnlockDevice();
	DEMOD_PRINT("DEMOD Task STOP\n");

	DEMOD_NOTI("ChannelChange (%s(0x%02x)m cfg%s(0x%02x)\n",
			DEMOD_Get_OPER_MODE_Name(pDemodInfo->operMode), pDemodInfo->operMode,
			DEMOD_Get_OPER_MODE_Name(pDemodCfg->operMode), pDemodCfg->operMode);

	pDemodInfo->bNotifiedUnlock	= FALSE;
	pDemodInfo->bNotifiedLock	= FALSE;

	if(pDemodInfo->operMode == pDemodCfg->operMode)
	{
		DEMOD_PRINT("The Opermode is the same (0x%02x)\n",pDemodInfo->operMode);
	}
	else
	{
		DEMOD_PRINT("Oops, The Opermode is different!!\n");
		DEMOD_PRINT("pDemodInfo->operMode = 0x%02x, pDemodCfg->operMode = 0x%02x\n",pDemodInfo->operMode, pDemodCfg->operMode);
		pDemodInfo->operMode = pDemodCfg->operMode;
	}

	switch(pDemodInfo->operMode)
	{
		case LX_DEMOD_DVBT :
			{
				if(RET_OK != _DEMOD_ChannelChangeDVBT(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeDVBT()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_DVBT2 :
			{
				if(RET_OK != _DEMOD_ChannelChangeDVBT2(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeDVBT2()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_DVBC :
			{
				if(RET_OK != _DEMOD_ChannelChangeDVBC(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeDVBC()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_DVBC2 :
			{
				if(RET_OK != _DEMOD_ChannelChangeDVBC2(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeDVBC2()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_ATSC :
			{
				if(RET_OK != _DEMOD_ChannelChangeATSC(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeATSC()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_QAM :
			{
				if(RET_OK != _DEMOD_ChannelChangeQAM(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeQAM()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_ISDBT :
			{
				if(RET_OK != _DEMOD_ChannelChangeISDBT(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeISDBT()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_DVBS :
			{
				if(RET_OK != _DEMOD_ChannelChangeDVBS(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeDVBS()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_DVBS2 :
			{
				if(RET_OK != _DEMOD_ChannelChangeDVBS2(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeDVBS2()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_DTMB :
			{
				if(RET_OK != _DEMOD_ChannelChangeDTMB(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChangeDTMB()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;
		case LX_DEMOD_ATSC3 :
			{
				if(RET_OK != _DEMOD_ChannelChangeATSC3(pDemodInfo, pDemodCfg))
				{
					DEMOD_ERROR("FAIL, _DEMOD_ChannelChange ATSC3()\n");
					DEMOD_RETURN_FAIL(__F__);
				}
			}
			break;

		case LX_DEMOD_UNKOWN_OPMODE:
			{
				/* nothing to do  so far */
			}
			break;
		case LX_DEMOD_ANALOG:
			DEMOD_WARN("No more support ABB\n");
			break;
		default :
			{
				DEMOD_RETURN_FAIL(__F__);
			}
			break;
	}
	DEMOD_NOTI("ChannelChange (%s(0x%02x)m cfg%s(0x%02x) done\n",
		DEMOD_Get_OPER_MODE_Name(pDemodInfo->operMode), pDemodInfo->operMode,
		DEMOD_Get_OPER_MODE_Name(pDemodCfg->operMode), pDemodCfg->operMode);
	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
* DEMOD_Get_TunedCFG
* Get all tuned configuration parameters
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_TunedCFG(DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_OPER_MODE_T operMode;

	if((LX_DEMOD_ANALOG != pDemodInfo->getCfgParam.operMode) && (LX_DEMOD_ANALOG != pDemodInfo->operMode))
	{
		if(RET_OK != DEMOD_Get_OperMode(&operMode))
		{
			DEMOD_ERROR("FAIL, DEMOD_Get_OperMode()\n");
			DEMOD_RETURN_FAIL(__F__);
		}

		if(operMode != pDemodInfo->operMode)
		{
			DEMOD_PRINT("Operation Mode Change by DEMOD_Get_OperMode()\n");
		}
		pDemodInfo->getCfgParam.operMode 	= operMode;
	}
	else
	{
		operMode 				= pDemodInfo->operMode;
		pDemodInfo->getCfgParam.operMode 	= pDemodInfo->operMode;
	}
	DEMOD_PRINT("OperMode = 0x%02x\n",operMode);

	if(LX_DEMOD_LOCKED == pDemodInfo->lockStatus)
	{
		switch(operMode)
		{
			case LX_DEMOD_DVBT :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_DVBT(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_DVBT()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_DVBT2 :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_DVBT2(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_DVBT2()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_DVBC :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_DVBC(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_DVBC()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_ATSC :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_VSB(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_VSB()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_QAM :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_QAM(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_QAM()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_ISDBT :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_ISDBT(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_ISDBT()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_DVBS :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_DVBS(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_DVBS()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_DVBS2 :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_DVBS2(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_DVBS2()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_ANALOG :
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_ANALOG(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_ANALOG()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_DTMB:
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_DTMB(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_DTMB()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_ATSC3:
				{
					if(RET_OK != _DEMOD_Get_TunedCFG_ATSC3(pDemodInfo))
					{
						DEMOD_ERROR("FAIL, _DEMOD_Get_TunedCFG_ATSC3()\n");
						DEMOD_RETURN_FAIL(__F__);
					}
				}
				break;
			case LX_DEMOD_UNKOWN_OPMODE:
				{
					/* nothing to do  so far */
				}
				break;
			default :
				break;
		}
	}

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
* DEMOD_Get_signal_status
* Get signal status - SNR, BER, packet  error
*
* @param *pDemodInfo [IN] DEMOD_CTX_T
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_Get_signal_status(DEMOD_CTX_T *pDemodInfo)
{
	LX_DEMOD_SIGNAL_TOTAL_T sigStatus;
	memset(&sigStatus, 0, sizeof(LX_DEMOD_SIGNAL_TOTAL_T));

	if(NULL == pDemodInfo)
	{
		return RET_ERROR;
	}

	pDemodInfo->signalStatus.operMode		= pDemodInfo->operMode;
	pDemodInfo->signalStatus.rfMode			= pDemodInfo->systemMode;

	if(RET_OK != DEMOD_Total_Signal_infomation(&sigStatus))
	{
		DEMOD_ERROR("FAIL, DEMOD_Total_Signal_infomation()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	pDemodInfo->signalStatus.packetError		= sigStatus.packetError;
	pDemodInfo->signalStatus.ber			= sigStatus.vBer;
	pDemodInfo->signalStatus.agc			= sigStatus.ifAgc;
	pDemodInfo->signalStatus.m.mse			= sigStatus.sigMse.mse;
	pDemodInfo->signalStatus.m.bMse			= sigStatus.sigMse.bMse;
	pDemodInfo->signalStatus.m.constPwr		= sigStatus.sigMse.constPwr;
	pDemodInfo->freqOffset				= sigStatus.freqOff;

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
* DEMOD_UnLock_Notify
* This function is called from the TunerTask loop when
     in NOT_LOCKED state. If 2 seconds has elapsed since the
     core called DDI_TUNER_RequestSatLock and the core has not yet
     been notified, this function notifies the core of the
     not locked condition.
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

static int DEMOD_UnLock_Notify(UINT8 deviceNum)
{
	unsigned int currentTime = 0;
	unsigned int elapsedTime = 0;

	DEMOD_CTX_T *pDemodInfo;

	pDemodInfo = &g_demod_ctx_info[deviceNum];

	currentTime = jiffies_to_msecs(jiffies);

	if(!pDemodInfo->bNotifiedUnlock)
	{
		elapsedTime = currentTime - g_RetuneStartTime;

		if(elapsedTime > notifyinglockTimeOut)
		{
			pDemodInfo->bNotifiedUnlock	= TRUE;
			pDemodInfo->bNotifiedLock	= FALSE;
			pDemodInfo->lockStatus		= LX_DEMOD_UNLOCKED;

			DEMOD_NOTI("MSG_FRONT_END_NOT_LOCKED... Elapse time is %d msec\n", elapsedTime);
		}
	}
	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * CheckDemodPayloads_and_Pause.
 * Set channel change parameters
 *
 * @param deviceNum [IN] UINT8
 * @param timeout [IN] UINT64
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

static void DEMOD_CheckDemodPayloads_and_Pause(UINT8 deviceNum, UINT64 timeout)
{

	UINT64	ui64TaskTimeout;

	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = &g_demod_ctx_info[deviceNum];

	ui64TaskTimeout = timeout;

	wait_event_freezable_timeout( g_DEMOD_Tuning_WaitQ,
			(DEMOD_TASK_OpenCount() == 0) || (g_requestMsg != LX_DEMOD_TASK_NONE_REQUEST),
			msecs_to_jiffies(ui64TaskTimeout) );

	if (DEMOD_TASK_OpenCount() == 0)
		return;

	DEMOD_LockDevice_NoRet();
	switch (g_requestMsg)
	{
		case LX_DEMOD_NEWTUNE_REQUEST:
			DEMOD_NOTI("TASK NEWTUNE REQ, %s(0x%02x)\n", DEMOD_Get_OPER_MODE_Name(pDemodInfo->operMode), pDemodInfo->operMode);

			if(pDemodInfo->operMode != LX_DEMOD_UNKOWN_OPMODE) {
				pDemodInfo->bSetParams				= TRUE;

				pDemodInfo->lockStatus				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->bNotifiedUnlock 			= FALSE;

				pDemodInfo->controlState			= LX_DEMOD_TUNE_START;
				pDemodInfo->acqState				= LX_DEMOD_TUNNING_PROCESS;
				pDemodInfo->scanJobFlag 			= LX_DEMOD_FLAG_START;
				pDemodInfo->bMonitorEnable			= TRUE;

				pDemodInfo->unLockCount 			= 0;
				pDemodInfo->unLockLongCount 			= 0;
				pDemodInfo->lockCount				= 0;

				pDemodInfo->signalStatus.agc			= 0;
				pDemodInfo->signalStatus.ber			= 0xffff;
				pDemodInfo->signalStatus.bSignalValid		= FALSE;
				pDemodInfo->signalStatus.m.mse			= 0xffff;
				pDemodInfo->signalStatus.packetError		= 0xffffffff;
				pDemodInfo->bSignalStatusValid			= FALSE;
//				pDemodInfo->bCountryGrpEU			= FALSE; //add for CAM Munich issue

				pauseTimeDemod					= LX_DEMOD_NOT_LOCKED_PAUSE_TIME;
				g_requestMsg					= LX_DEMOD_TASK_NONE_REQUEST;
				g_NewTuneReqeustTime				= jiffies_to_msecs(jiffies);
				g_RetuneStartTime				= g_NewTuneReqeustTime;
				notifyinglockTimeOut				= LX_DEMOD_LOCK_DEALY_2500;

				memset(&(pDemodInfo->getCfgParam), 0x0, sizeof(LX_DEMOD_CONFIG_T) );

			} else 	{
				pDemodInfo->bSetParams				= FALSE;

				pDemodInfo->lockStatus				= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock			= FALSE;
				pDemodInfo->bNotifiedUnlock			= FALSE;

				pDemodInfo->controlState			= LX_DEMOD_TUNE_START;
				pDemodInfo->acqState				= LX_DEMOD_IDLE_PROCESS;
				pDemodInfo->scanJobFlag				= LX_DEMOD_FLAG_START;
				pDemodInfo->bMonitorEnable			= FALSE;

				pDemodInfo->unLockCount				= 0;
				pDemodInfo->unLockLongCount			= 0;
				pDemodInfo->lockCount				= 0;

				pDemodInfo->signalStatus.agc			= 0;
				pDemodInfo->signalStatus.ber			= 0xffff;
				pDemodInfo->signalStatus.bSignalValid		= FALSE;
				pDemodInfo->signalStatus.m.mse			= 0xffff;
				pDemodInfo->signalStatus.packetError		= 0xffffffff;
				pDemodInfo->bSignalStatusValid			= FALSE;

				pauseTimeDemod					= LX_DEMOD_FOREVER_PAUSE_TIME;
				g_requestMsg					= LX_DEMOD_TASK_NONE_REQUEST;

				memset(&(pDemodInfo->getCfgParam), 0x0, sizeof(LX_DEMOD_CONFIG_T));

				DEMOD_WARN("Wrong tune From Channel Manager\n");
			}
			break;

		case LX_DEMOD_STOP_REQUEST :
			DEMOD_NOTI("TASK STOP REQ\n");

			pDemodInfo->bSetParams					= FALSE;

			pDemodInfo->lockStatus					= LX_DEMOD_UNLOCKED;
			pDemodInfo->bNotifiedLock				= FALSE;
			pDemodInfo->bNotifiedUnlock 				= FALSE;

			pDemodInfo->controlState				= LX_DEMOD_TUNE_START;
			pDemodInfo->acqState					= LX_DEMOD_IDLE_PROCESS;

			pDemodInfo->bMonitorEnable				= FALSE;

			pDemodInfo->unLockCount 				= 0;
			pDemodInfo->unLockLongCount 				= 0;
			pDemodInfo->lockCount					= 0;

			pDemodInfo->signalStatus.agc				= 0;
			pDemodInfo->signalStatus.ber				= 0xffff;
			pDemodInfo->signalStatus.bSignalValid			= FALSE;
			pDemodInfo->signalStatus.m.mse				= 0xffff;
			pDemodInfo->signalStatus.packetError			= 0xffffffff;
			pDemodInfo->bSignalStatusValid				= FALSE;

			pauseTimeDemod						= LX_DEMOD_FOREVER_PAUSE_TIME;
			g_requestMsg						= LX_DEMOD_TASK_NONE_REQUEST;

			memset(&(pDemodInfo->getCfgParam), 0x0, sizeof(LX_DEMOD_CONFIG_T));
			break;

		case LX_DEMOD_PLP_CHANGE_REQUEST :
			DEMOD_NOTI("TASK PLP_CHANGE REQ, %s(0x%02x)\n", DEMOD_Get_OPER_MODE_Name(pDemodInfo->operMode), pDemodInfo->operMode);

			pDemodInfo->bSetParams					= TRUE;

			pDemodInfo->lockStatus					= LX_DEMOD_UNLOCKED;
			pDemodInfo->bNotifiedLock				= FALSE;
			pDemodInfo->bNotifiedUnlock 				= FALSE;

			pDemodInfo->controlState				= LX_DEMOD_TUNE_START;
			pDemodInfo->acqState					= LX_DEMOD_TUNNING_PROCESS;
			pDemodInfo->scanJobFlag 				= LX_DEMOD_FLAG_START;
			pDemodInfo->bMonitorEnable				= TRUE;

			pDemodInfo->unLockCount 				= 0;
			pDemodInfo->unLockLongCount 				= 0;
			pDemodInfo->lockCount					= 0;

			pDemodInfo->signalStatus.agc				= 0;
			pDemodInfo->signalStatus.ber				= 0xffff;
			pDemodInfo->signalStatus.bSignalValid			= FALSE;
			pDemodInfo->signalStatus.m.mse				= 0xffff;
			pDemodInfo->signalStatus.packetError			= 0xffffffff;
			pDemodInfo->bSignalStatusValid				= FALSE;

			pauseTimeDemod						= LX_DEMOD_NOT_LOCKED_PAUSE_TIME;
			g_requestMsg						= LX_DEMOD_TASK_NONE_REQUEST;
			g_NewTuneReqeustTime					= jiffies_to_msecs(jiffies);
			g_RetuneStartTime					= g_NewTuneReqeustTime;
			notifyinglockTimeOut					= LX_DEMOD_LOCK_DEALY_2500;

			memset(&(pDemodInfo->getCfgParam), 0x0, sizeof(LX_DEMOD_CONFIG_T));
			break;

		case LX_DEMOD_INSTANTBOOT_TUNE_REQUEST:
			DEMOD_NOTI("TASK INSTANTBOOT TUNE REQ, %s(0x%02x)\n", DEMOD_Get_OPER_MODE_Name(pDemodInfo->operMode), pDemodInfo->operMode);

			if(pDemodInfo->operMode != LX_DEMOD_UNKOWN_OPMODE)
			{
				pDemodInfo->bSetParams					= TRUE;

				pDemodInfo->lockStatus					= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock				= FALSE;
				pDemodInfo->bNotifiedUnlock 				= FALSE;

				pDemodInfo->controlState				= LX_DEMOD_SIGNAL_STABLE;//LX_DEMOD_SYNC_CHECKING;
				pDemodInfo->acqState					= LX_DEMOD_TUNNING_PROCESS;
				pDemodInfo->scanJobFlag 				= LX_DEMOD_FLAG_START;
				pDemodInfo->bMonitorEnable				= TRUE;

				pDemodInfo->unLockCount 				= 0;
				pDemodInfo->unLockLongCount 				= 0;
				pDemodInfo->lockCount					= 0;

				pDemodInfo->signalStatus.agc				= 0;
				pDemodInfo->signalStatus.ber				= 0xffff;
				pDemodInfo->signalStatus.bSignalValid			= FALSE;
				pDemodInfo->signalStatus.m.mse				= 0xffff;
				pDemodInfo->signalStatus.packetError			= 0xffffffff;
				pDemodInfo->bSignalStatusValid				= FALSE;

				pauseTimeDemod						= LX_DEMOD_NOT_LOCKED_PAUSE_TIME;
				g_requestMsg						= LX_DEMOD_TASK_NONE_REQUEST;
				g_NewTuneReqeustTime					= jiffies_to_msecs(jiffies);
				g_RetuneStartTime					= g_NewTuneReqeustTime;
				notifyinglockTimeOut					= LX_DEMOD_LOCK_DEALY_2500;

				memset(&(pDemodInfo->getCfgParam), 0x0, sizeof(LX_DEMOD_CONFIG_T));
			}
			else
			{
				pDemodInfo->bSetParams					= FALSE;

				pDemodInfo->lockStatus					= LX_DEMOD_UNLOCKED;
				pDemodInfo->bNotifiedLock				= FALSE;
				pDemodInfo->bNotifiedUnlock 				= FALSE;

				pDemodInfo->controlState				= LX_DEMOD_TUNE_START;
				pDemodInfo->acqState					= LX_DEMOD_IDLE_PROCESS;
				pDemodInfo->scanJobFlag 				= LX_DEMOD_FLAG_START;
				pDemodInfo->bMonitorEnable				= FALSE;

				pDemodInfo->unLockCount 				= 0;
				pDemodInfo->unLockLongCount 				= 0;
				pDemodInfo->lockCount					= 0;

				pDemodInfo->signalStatus.agc				= 0;
				pDemodInfo->signalStatus.ber				= 0xffff;
				pDemodInfo->signalStatus.bSignalValid			= FALSE;
				pDemodInfo->signalStatus.m.mse				= 0xffff;
				pDemodInfo->signalStatus.packetError			= 0xffffffff;
				pDemodInfo->bSignalStatusValid				= FALSE;

				pauseTimeDemod						= LX_DEMOD_FOREVER_PAUSE_TIME;
				g_requestMsg						= LX_DEMOD_TASK_NONE_REQUEST;

				memset(&(pDemodInfo->getCfgParam), 0x0, sizeof(LX_DEMOD_CONFIG_T));
			}
			break;

		default:
			break;
	}  /*switch (msg.typeB.msgID & 0xf)*/

	DEMOD_UnlockDevice();
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Tuning_Task.
 * Set channel change parameters
 *
 * @param NONE  [IN/OUT] void
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Tuning_Task(void *i_pvParam)
{
	bool 	frozen;
	UINT8 	deviceNum = 0;
	#ifdef TMA_TEST
	UINT32	m_value = 0;
	#endif
	DEMOD_CTX_T *pDemodInfo;

	pDemodInfo = &g_demod_ctx_info[deviceNum];

	set_freezable();

	while (!kthread_freezable_should_stop(&frozen) && DEMOD_TASK_OpenCount() > 0)
	{
		if(frozen)
		{
			printk("++ kthread(%s) wakes up\n",__F__);
		}

		if(pDemodInfo->bSetParams)
		{
			DEMOD_LockDevice();
			#ifdef TMA_TEST
			SYS_IO_ReadRegArray(0xC80251F0, 4, &m_value);
			m_value = (m_value>>28)&0x01;
			//printk("[DEMOD M16 GBB] (%s:%d) ####chungiii check mute value[%d] !!!\n", __F__, __L__, m_value);
			#endif

			switch(pDemodInfo->acqState) /* 3 possible tuner states NOT_LOCKED, LOCKED and NTSC_LOCKED */
			{
				case LX_DEMOD_TUNNING_PROCESS:
					{
//						pauseTimeDemod = LX_DEMOD_NOT_LOCKED_PAUSE_TIME;
						switch(pDemodInfo->operMode)
						{
							case LX_DEMOD_DVBT :
								DEMOD_DVBT_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBT2 :
								DEMOD_DVBT2_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBC :
								DEMOD_DVBC_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBC2 :
								DEMOD_DVBC2_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_ATSC :
								DEMOD_VSB_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_QAM :
								DEMOD_QAM_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_ISDBT :
								DEMOD_ISDBT_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBS :
								DEMOD_DVBS_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBS2 :
								DEMOD_DVBS2_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DTMB :
								DEMOD_DTMB_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_ATSC3 :
								DEMOD_ATSC3_Obtaining_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_ANALOG :
								DEMOD_WARN("No more support ABB\n");

							default :
								break;

						}

						if(pDemodInfo->controlState == LX_DEMOD_SIGNAL_LOCKED )
						{
							#ifdef TMA_TEST
							if(m_value == 0)
							{
								pDemodInfo->acqState = LX_DEMOD_MONITOR_PROCESS;
								pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
								//printk("[DEMOD M16 GBB] (%s:%d) ####chungiii check mute off[%d] !!!\n", __F__, __L__, m_value);
							}
							else
							{
								if (RET_OK != DEMOD_Get_signal_status(pDemodInfo))
								{
									DEMOD_ERROR("FAIL, DEMOD_Get_signal_status()\n");
									DEMOD_RETURN_FAIL(__F__);
								}
							}
							#else
								pDemodInfo->acqState 	= LX_DEMOD_MONITOR_PROCESS;
								pauseTimeDemod 		= LX_DEMOD_LOCKED_PAUSE_TIME;
							#endif

						}
						else if(pDemodInfo->controlState == LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK)
						{
							if(((pDemodInfo->operMode == LX_DEMOD_DVBS) && (pDemodInfo->setCfgParam.dvbs.operatingMode != LX_DEMOD_DVBS_NORMAL_MODE)) ||
								((pDemodInfo->operMode == LX_DEMOD_DVBS2) && (pDemodInfo->setCfgParam.dvbs2.operatingMode != LX_DEMOD_DVBS_NORMAL_MODE)))
							{
								pDemodInfo->acqState 	= LX_DEMOD_IDLE_PROCESS;
								DEMOD_PRINT("pDemodInfo->controlState == LX_DEMOD_IDLE_PROCESS\n");
							}
							else
							{
								pDemodInfo->acqState 	= LX_DEMOD_MONITOR_PROCESS;
								pauseTimeDemod 		= LX_DEMOD_LOCK_FAIL_PAUSE_TIME;
								DEMOD_PRINT("pDemodInfo->controlState == LX_DEMOD_TUNE_SCAN_FINISH_UNLOCK");
							}
						}
						else if(pDemodInfo->bNotifiedUnlock == TRUE)
						{
//							pDemodInfo->acqState = LX_DEMOD_MONITOR_PROCESS;
							pauseTimeDemod = LX_DEMOD_LOCK_FAIL_PAUSE_TIME;
						}
						else
						{
							/*** Notify core of not locked if 2 seconds elapsed ***/
							/*** since last call to HDIRequestSatLock.			***/
							DEMOD_UnLock_Notify(deviceNum);
						}
					}
					break;
				case LX_DEMOD_MONITOR_PROCESS:
					{
//						pauseTimeDemod = LX_DEMOD_LOCKED_PAUSE_TIME;
						switch(pDemodInfo->operMode)
						{
							case LX_DEMOD_DVBT :
								DEMOD_DVBT_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBT2 :
								DEMOD_DVBT2_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBC :
								DEMOD_DVBC_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBC2 :
								DEMOD_DVBC2_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_ATSC :
								DEMOD_VSB_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_QAM :
								DEMOD_QAM_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_ISDBT :
								DEMOD_ISDBT_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBS :
								DEMOD_DVBS_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DVBS2 :
								DEMOD_DVBS2_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_DTMB :
								DEMOD_DTMB_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_ATSC3 :
								DEMOD_ATSC3_Monitoring_Signal_Lock(pDemodInfo);
								break;

							case LX_DEMOD_ANALOG :
								DEMOD_WARN("No more support ABB\n");
								break;

							default :
								break;
						}
					}
					break;
				case LX_DEMOD_IDLE_PROCESS :
					{
						pauseTimeDemod = LX_DEMOD_FOREVER_PAUSE_TIME;
					}
					break;
				default :
					pDemodInfo->acqState = LX_DEMOD_TUNNING_PROCESS;
					DEMOD_PRINT("Oops, Invaild control !!, Going to LX_DEMOD_UNLOCKED");
					break;
			} /* switch */
			DEMOD_UnlockDevice();
		}
		DEMOD_CheckDemodPayloads_and_Pause(deviceNum, pauseTimeDemod);
	}

	printk("stop demod task..\n");
	return RET_OK;
}

int DEMOD_WakeUpTask(void)
{
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	return 0;
}

int DEMOD_Signal_Dump(char * dbglog)
{
	int dbgidx = 0;
	DEMOD_CTX_T *pDemodInfo;

	pDemodInfo = DEMOD_Get_CTX(0);

	dbgidx += sprintf(dbglog + dbgidx,"*******************************************************\n");
	dbgidx += sprintf(dbglog + dbgidx,"*****************DEMOD_Debug_TotalInfo*****************\n");

	if (pDemodInfo->lockStatus != LX_DEMOD_LOCKED)
	{
		dbgidx += sprintf(dbglog + dbgidx, "Demod status	=	UNLOCK\n");
	}
	else
	{
		dbgidx += sprintf(dbglog + dbgidx, "Demod status	=	LOCK\n");
	}

	switch(pDemodInfo->operMode)
	{
		case LX_DEMOD_DVBT :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       DVBT\n");

				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.dvbt.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.dvbt.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.dvbt.tuneMode == 0x30) ? "Auto" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Channel BW  =       %s\n",
												(pDemodInfo->getCfgParam.dvbt.channelBW	== 0x0) ? "1.7MHz" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x1) ? "5MHz" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x2) ? "6MHz" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x3) ? "7MHz" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x4) ? "8MHz" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x5) ? "7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x6) ? "8MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x7) ? "8MHz, 7MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x8) ? "8MHz, 7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0x9) ? "DVB-T No operation" :
												(pDemodInfo->getCfgParam.dvbt.channelBW == 0xA) ? "VSB No operation"	: "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Spec Inv    =       %s\n", (pDemodInfo->getCfgParam.dvbt.bSpectrumInv == FALSE) ? "False" : "True");

				dbgidx += sprintf(dbglog + dbgidx, "Priority    =       %s\n", (pDemodInfo->getCfgParam.dvbt.bSetHp == FALSE) ? "False" : "True");

				dbgidx += sprintf(dbglog + dbgidx, "Hierarchy Mode =    %s\n",
												(pDemodInfo->getCfgParam.dvbt.hierachMode== 0x0) ? "None" :
												(pDemodInfo->getCfgParam.dvbt.hierachMode == 0x1) ? "Alpha -> 1" :
												(pDemodInfo->getCfgParam.dvbt.hierachMode == 0x2) ? "Alpha -> 2" :
												(pDemodInfo->getCfgParam.dvbt.hierachMode == 0x3) ? "Alpha -> 4" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "FFT Mode    =       %s\n",
												(pDemodInfo->getCfgParam.dvbt.FFTMode == 0x0) ? "1K" :
												(pDemodInfo->getCfgParam.dvbt.FFTMode == 0x1) ? "2K" :
												(pDemodInfo->getCfgParam.dvbt.FFTMode == 0x2) ? "4K" :
												(pDemodInfo->getCfgParam.dvbt.FFTMode == 0x3) ? "8K" :
												(pDemodInfo->getCfgParam.dvbt.FFTMode == 0x4) ? "16K" :
												(pDemodInfo->getCfgParam.dvbt.FFTMode == 0x5) ? "32K" :
												(pDemodInfo->getCfgParam.dvbt.FFTMode == 0x6) ? "64K" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Guard Int   =       %s\n",
												(pDemodInfo->getCfgParam.dvbt.gIMode == 0x0) ? "19/256" :
												(pDemodInfo->getCfgParam.dvbt.gIMode == 0x1) ? "19/128" :
												(pDemodInfo->getCfgParam.dvbt.gIMode == 0x2) ? "1/128" :
												(pDemodInfo->getCfgParam.dvbt.gIMode == 0x3) ? "1/64" :
												(pDemodInfo->getCfgParam.dvbt.gIMode == 0x4) ? "1/32" :
												(pDemodInfo->getCfgParam.dvbt.gIMode == 0x5) ? "1/16" :
												(pDemodInfo->getCfgParam.dvbt.gIMode == 0x6) ? "1/8" :
												(pDemodInfo->getCfgParam.dvbt.gIMode == 0x7) ? "1/4" : "UNKNOWN");
				if(pDemodInfo->getCfgParam.dvbt.bSetHp == TRUE)
				{
					dbgidx += sprintf(dbglog + dbgidx, "HP Code Rate        =       %s\n",
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 0) ? "1 / 2" :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 1) ? "1 / 3 Only DVBS2" :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 2) ? "1 / 4 Only DVBS2" :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 3) ? "2 / 3 " :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 4) ? "3 / 4 " :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 5) ? "2 / 5 Only DVBS2" :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 6) ? "3 / 5 " :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 7) ? "4 / 5 " :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 8) ? "5 / 6 " :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 9) ? "6 / 7 " :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 10) ? "7 / 8 " :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 11) ? "8 / 9 Only DVBS2" :
													(pDemodInfo->getCfgParam.dvbt.hpCodeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");
				}
				else
				{
					dbgidx += sprintf(dbglog + dbgidx, "LP Code Rate        =       %s\n",
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 0) ? "1 / 2" :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 1) ? "1 / 3 Only DVBS2" :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 2) ? "1 / 4 Only DVBS2" :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 3) ? "2 / 3 " :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 4) ? "3 / 4 " :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 5) ? "2 / 5 Only DVBS2" :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 6) ? "3 / 5 " :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 7) ? "4 / 5 " :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 8) ? "5 / 6 " :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 9) ? "6 / 7 " :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 10) ? "7 / 8 " :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 11) ? "8 / 9 Only DVBS2" :
													(pDemodInfo->getCfgParam.dvbt.lpCodeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");

				}
				dbgidx += sprintf(dbglog + dbgidx, "QAM Mode    =       %s\n",
												(pDemodInfo->getCfgParam.dvbt.qamMode== 0) ? "QAM16" :
												(pDemodInfo->getCfgParam.dvbt.qamMode== 1) ? "QAM32" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 2) ? "QAM64" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 3) ? "QAM128 " :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 4) ? "QAM256 " :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 5) ? "QAM1024" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 6) ? "QAM4096 " :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 7) ? "BPSK " :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 8) ? "QPSK" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 9) ? "DQPSK " :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 10) ? "VSB " :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 11) ? "PSK8" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 12) ? "APSK16" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 13) ? "APSK32" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 14) ? "NTSC" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 15) ? "PAL" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 16) ? "SECAM" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 17) ? "QAM4_NR" :
												(pDemodInfo->getCfgParam.dvbt.qamMode == 18) ? "QAM4" :"UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Cell ID     =       0x%x\n", pDemodInfo->signalStatus.cellID);
			}
			break;
		case LX_DEMOD_DVBT2 :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       DVBT2\n");
				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.dvbt2.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.dvbt2.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.dvbt2.tuneMode == 0x30) ? "Auto" : "UNKNOWN");


				dbgidx += sprintf(dbglog + dbgidx, "Channel BW  =       %s\n", 	(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x0) ? "1.7MHz" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x1) ? "5MHz" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x2) ? "6MHz" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x3) ? "7MHz" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x4) ? "8MHz" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x5) ? "7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x6) ? "8MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x7) ? "8MHz, 7MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x8) ? "8MHz, 7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0x9) ? "DVB-T No operation" :
												(pDemodInfo->getCfgParam.dvbt2.channelBW == 0xA) ? "VSB No operation"  : "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Spec Inv    =       %s\n", (pDemodInfo->getCfgParam.dvbt2.bSpectrumInv == FALSE) ? "False" : "True");

				dbgidx += sprintf(dbglog + dbgidx, "FFT Mode    =       %s\n",	(pDemodInfo->getCfgParam.dvbt2.FFTMode == 0x0) ? "1K" :
												(pDemodInfo->getCfgParam.dvbt2.FFTMode == 0x1) ? "2K" :
												(pDemodInfo->getCfgParam.dvbt2.FFTMode == 0x2) ? "4K" :
												(pDemodInfo->getCfgParam.dvbt2.FFTMode == 0x3) ? "8K" :
												(pDemodInfo->getCfgParam.dvbt2.FFTMode == 0x4) ? "16K" :
												(pDemodInfo->getCfgParam.dvbt2.FFTMode == 0x5) ? "32K" :
												(pDemodInfo->getCfgParam.dvbt2.FFTMode == 0x6) ? "64K" : "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Guard Int   =       %s\n",	(pDemodInfo->getCfgParam.dvbt2.gIMode == 0x0) ? "19/256" :
												(pDemodInfo->getCfgParam.dvbt2.gIMode == 0x1) ? "19/128" :
												(pDemodInfo->getCfgParam.dvbt2.gIMode == 0x2) ? "1/128" :
												(pDemodInfo->getCfgParam.dvbt2.gIMode == 0x3) ? "1/32" :
												(pDemodInfo->getCfgParam.dvbt2.gIMode == 0x4) ? "1/32" :
												(pDemodInfo->getCfgParam.dvbt2.gIMode == 0x5) ? "1/16" :
												(pDemodInfo->getCfgParam.dvbt2.gIMode == 0x6) ? "1/8" :
												(pDemodInfo->getCfgParam.dvbt2.gIMode == 0x7) ? "1/4" : "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Code Rate   =       %s\n",	(pDemodInfo->getCfgParam.dvbt2.codeRate == 0) ? "1 / 2" :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 1) ? "1 / 3 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 2) ? "1 / 4 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 3) ? "2 / 3 " :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 4) ? "3 / 4 " :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 5) ? "2 / 5 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 6) ? "3 / 5 " :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 7) ? "4 / 5 " :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 8) ? "5 / 6 " :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 9) ? "6 / 7 " :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 10) ? "7 / 8 " :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 11) ? "8 / 9 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbt2.codeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "QAM Mode    =       %s\n",	(pDemodInfo->getCfgParam.dvbt2.qamMode== 0) ? "QAM16" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode== 1) ? "QAM32" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 2) ? "QAM64" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 3) ? "QAM128 " :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 4) ? "QAM256 " :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 5) ? "QAM1024" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 6) ? "QAM4096 " :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 7) ? "BPSK " :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 8) ? "QPSK" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 9) ? "DQPSK " :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 10) ? "VSB " :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 11) ? "PSK8" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 12) ? "APSK16" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 13) ? "APSK32" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 14) ? "NTSC" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 15) ? "PAL" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 16) ? "SECAM" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 17) ? "QAM4_NR" :
												(pDemodInfo->getCfgParam.dvbt2.qamMode == 18) ? "QAM4" :"UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "groupID     =       0x%x\n", pDemodInfo->getCfgParam.dvbt2.groupID);
				dbgidx += sprintf(dbglog + dbgidx, "unPLP       =       0x%x\n", pDemodInfo->getCfgParam.dvbt2.unPLP);
				dbgidx += sprintf(dbglog + dbgidx, "Cell ID     =       0x%x\n", pDemodInfo->signalStatus.cellID);
			}
			break;
		case LX_DEMOD_DVBC :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       DVBC\n");

				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.dvbc.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.dvbc.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.dvbc.tuneMode == 0x30) ? "Auto" :
												(pDemodInfo->getCfgParam.dvbc.tuneMode == 0x42) ? "Fixed Data" :"UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Channel BW  =       %s\n",	(pDemodInfo->getCfgParam.dvbc.channelBW	== 0x0) ? "1.7MHz" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x1) ? "5MHz" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x2) ? "6MHz" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x3) ? "7MHz" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x4) ? "8MHz" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x5) ? "7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x6) ? "8MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x7) ? "8MHz, 7MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x8) ? "8MHz, 7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0x9) ? "DVB-T No operation" :
												(pDemodInfo->getCfgParam.dvbc.channelBW == 0xA) ? "VSB No operation"	: "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Spec Inv    =       %s\n",	(pDemodInfo->getCfgParam.dvbc.bSpectrumInv == FALSE) ? "False" : "True");
				dbgidx += sprintf(dbglog + dbgidx, "Symbol Rate =       %d\n",	pDemodInfo->getCfgParam.dvbc.symbolRate);
				dbgidx += sprintf(dbglog + dbgidx, "QAM Mode    =       %s\n",	(pDemodInfo->getCfgParam.dvbc.qamMode== 0) ? "QAM16" :
												(pDemodInfo->getCfgParam.dvbc.qamMode== 1) ? "QAM32" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 2) ? "QAM64" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 3) ? "QAM128 " :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 4) ? "QAM256 " :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 5) ? "QAM1024" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 6) ? "QAM4096 " :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 7) ? "BPSK " :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 8) ? "QPSK" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 9) ? "DQPSK " :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 10) ? "VSB " :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 11) ? "PSK8" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 12) ? "APSK16" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 13) ? "APSK32" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 14) ? "NTSC" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 15) ? "PAL" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 16) ? "SECAM" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 17) ? "QAM4_NR" :
												(pDemodInfo->getCfgParam.dvbc.qamMode == 18) ? "QAM4" :"UNKNOWN");
			}
			break;
		case LX_DEMOD_ATSC :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       VSB\n");
				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.vsb.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.vsb.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.vsb.tuneMode == 0x30) ? "Auto" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Channel BW  =       %s\n", 	(pDemodInfo->getCfgParam.vsb.channelBW == 0x0) ? "1.7MHz" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x1) ? "5MHz" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x2) ? "6MHz" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x3) ? "7MHz" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x4) ? "8MHz" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x5) ? "7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x6) ? "8MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x7) ? "8MHz, 7MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x8) ? "8MHz, 7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0x9) ? "DVB-T No operation" :
												(pDemodInfo->getCfgParam.vsb.channelBW == 0xA) ? "VSB No operation"  : "UNKNOWN");
			}
			break;
		case LX_DEMOD_QAM :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       QAM	\n");
				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.qam.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.qam.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.qam.tuneMode == 0x30) ? "Auto" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Channel BW  =       %s\n",	(pDemodInfo->getCfgParam.qam.channelBW == 0x0) ? "1.7MHz" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x1) ? "5MHz" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x2) ? "6MHz" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x3) ? "7MHz" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x4) ? "8MHz" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x5) ? "7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x6) ? "8MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x7) ? "8MHz, 7MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x8) ? "8MHz, 7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0x9) ? "DVB-T No operation" :
												(pDemodInfo->getCfgParam.qam.channelBW == 0xA) ? "VSB No operation"  : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Spec Inv    =       %s\n",	(pDemodInfo->getCfgParam.qam.bSpectrumInv == FALSE) ? "False" : "True");
				dbgidx += sprintf(dbglog + dbgidx, "QAM Mode    =       %s\n",	(pDemodInfo->getCfgParam.qam.qamMode== 0) ? "QAM16" :
												(pDemodInfo->getCfgParam.qam.qamMode== 1) ? "QAM32" :
												(pDemodInfo->getCfgParam.qam.qamMode == 2) ? "QAM64" :
												(pDemodInfo->getCfgParam.qam.qamMode == 3) ? "QAM128 " :
												(pDemodInfo->getCfgParam.qam.qamMode == 4) ? "QAM256 " :
												(pDemodInfo->getCfgParam.qam.qamMode == 5) ? "QAM1024" :
												(pDemodInfo->getCfgParam.qam.qamMode == 6) ? "QAM4096 " :
												(pDemodInfo->getCfgParam.qam.qamMode == 7) ? "BPSK " :
												(pDemodInfo->getCfgParam.qam.qamMode == 8) ? "QPSK" :
												(pDemodInfo->getCfgParam.qam.qamMode == 9) ? "DQPSK " :
												(pDemodInfo->getCfgParam.qam.qamMode == 10) ? "VSB " :
												(pDemodInfo->getCfgParam.qam.qamMode == 11) ? "PSK8" :
												(pDemodInfo->getCfgParam.qam.qamMode == 12) ? "APSK16" :
												(pDemodInfo->getCfgParam.qam.qamMode == 13) ? "APSK32" :
												(pDemodInfo->getCfgParam.qam.qamMode == 14) ? "NTSC" :
												(pDemodInfo->getCfgParam.qam.qamMode == 15) ? "PAL" :
												(pDemodInfo->getCfgParam.qam.qamMode == 16) ? "SECAM" :
												(pDemodInfo->getCfgParam.qam.qamMode == 17) ? "QAM4_NR" :
												(pDemodInfo->getCfgParam.qam.qamMode == 18) ? "QAM4" :"UNKNOWN");

			}
			break;
		case LX_DEMOD_ISDBT :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       ISDBT\n");
				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.isdbt.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.isdbt.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.isdbt.tuneMode == 0x30) ? "Auto" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Channel BW  =       %s\n",	(pDemodInfo->getCfgParam.isdbt.channelBW == 0x0) ? "1.7MHz" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x1) ? "5MHz" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x2) ? "6MHz" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x3) ? "7MHz" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x4) ? "8MHz" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x5) ? "7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x6) ? "8MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x7) ? "8MHz, 7MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x8) ? "8MHz, 7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0x9) ? "DVB-T No operation" :
												(pDemodInfo->getCfgParam.isdbt.channelBW == 0xA) ? "VSB No operation"  : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Spec Inv    =       %s\n",	(pDemodInfo->getCfgParam.isdbt.bSpectrumInv == FALSE) ? "False" : "True");
				dbgidx += sprintf(dbglog + dbgidx, "FFT Mode    =       %s\n",	(pDemodInfo->getCfgParam.isdbt.FFTMode == 0x0) ? "1K" :
												(pDemodInfo->getCfgParam.isdbt.FFTMode == 0x1) ? "2K" :
												(pDemodInfo->getCfgParam.isdbt.FFTMode == 0x2) ? "4K" :
												(pDemodInfo->getCfgParam.isdbt.FFTMode == 0x3) ? "8K" :
												(pDemodInfo->getCfgParam.isdbt.FFTMode == 0x4) ? "16K" :
												(pDemodInfo->getCfgParam.isdbt.FFTMode == 0x5) ? "32K" :
												(pDemodInfo->getCfgParam.isdbt.FFTMode == 0x6) ? "64K" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Guard Int   =       %s\n",	(pDemodInfo->getCfgParam.isdbt.gIMode == 0x0) ? "19/256" :
												(pDemodInfo->getCfgParam.isdbt.gIMode == 0x1) ? "19/128" :
												(pDemodInfo->getCfgParam.isdbt.gIMode == 0x2) ? "1/128" :
												(pDemodInfo->getCfgParam.isdbt.gIMode == 0x3) ? "1/64" :
												(pDemodInfo->getCfgParam.isdbt.gIMode == 0x4) ? "1/32" :
												(pDemodInfo->getCfgParam.isdbt.gIMode == 0x5) ? "1/16" :
												(pDemodInfo->getCfgParam.isdbt.gIMode == 0x6) ? "1/8" :
												(pDemodInfo->getCfgParam.isdbt.gIMode == 0x7) ? "1/4" :	"UNKNOWN");
				if(pDemodInfo->getCfgParam.isdbt.tmcc.layerASegmentNum != 0)
				{
					dbgidx += sprintf(dbglog + dbgidx, "LayerA QAM Mode =   %s\n",	(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode== 0) ? "QAM16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 1) ? "QAM32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 2) ? "QAM64" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 3) ? "QAM128 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 4) ? "QAM256 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 5) ? "QAM1024" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 6) ? "QAM4096 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 7) ? "BPSK " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 8) ? "QPSK" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 9) ? "DQPSK " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 10) ? "VSB " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 11) ? "PSK8" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 12) ? "APSK16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 13) ? "APSK32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 14) ? "NTSC" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 15) ? "PAL" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 16) ? "SECAM" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 17) ? "QAM4_NR" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerAQamMode == 18) ? "QAM4" :"UNKNOWN");
					dbgidx += sprintf(dbglog + dbgidx, "LayerA Code Rate =  %s\n",	(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 0) ? "1 / 2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 1) ? "1 / 3 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 2) ? "1 / 4 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 3) ? "2 / 3 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 4) ? "3 / 4 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 5) ? "2 / 5 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 6) ? "3 / 5 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 7) ? "4 / 5 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 8) ? "5 / 6 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 9) ? "6 / 7 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 10) ? "7 / 8 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 11) ? "8 / 9 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerACodeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");


					dbgidx += sprintf(dbglog + dbgidx, "LayerA Time Interleaving = %s\n",
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerATimeInterleavingLen == 0x0) ? "Length 0" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerATimeInterleavingLen == 0x1) ? "Length 1" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerATimeInterleavingLen == 0x2) ? "Length 2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerATimeInterleavingLen == 0x3) ? "Length 4" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerATimeInterleavingLen == 0x4) ? "Length 8" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerATimeInterleavingLen == 0x5) ? "Length 16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerATimeInterleavingLen == 0x6) ? "Length 32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerATimeInterleavingLen == 0x6) ? "Reserved" : "UNUSED");
				}
				else
				{
					dbgidx += sprintf(dbglog + dbgidx, "LayerA is unused hierarchy layer.\n");
				}

				if(pDemodInfo->getCfgParam.isdbt.tmcc.layerBSegmentNum != 0)
				{
					dbgidx += sprintf(dbglog + dbgidx, "LayerB QAM Mode =   %s\n",
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode== 0) ? "QAM16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 1) ? "QAM32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 2) ? "QAM64" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 3) ? "QAM128 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 4) ? "QAM256 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 5) ? "QAM1024" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 6) ? "QAM4096 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 7) ? "BPSK " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 8) ? "QPSK" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 9) ? "DQPSK " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 10) ? "VSB " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 11) ? "PSK8" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 12) ? "APSK16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 13) ? "APSK32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 14) ? "NTSC" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 15) ? "PAL" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 16) ? "SECAM" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 17) ? "QAM4_NR" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBQamMode == 18) ? "QAM4" :"UNKNOWN");
					dbgidx += sprintf(dbglog + dbgidx, "LayerB Code Rate =  %s\n",
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 0) ? "1 / 2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 1) ? "1 / 3 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 2) ? "1 / 4 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 3) ? "2 / 3 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 4) ? "3 / 4 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 5) ? "2 / 5 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 6) ? "3 / 5 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 7) ? "4 / 5 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 8) ? "5 / 6 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 9) ? "6 / 7 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 10) ? "7 / 8 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 11) ? "8 / 9 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBCodeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");

					dbgidx += sprintf(dbglog + dbgidx, "LayerB Time Interleaving = %s\n",
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBTimeInterleavingLen == 0x0) ? "Length 0" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBTimeInterleavingLen == 0x1) ? "Length 1" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBTimeInterleavingLen == 0x2) ? "Length 2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBTimeInterleavingLen == 0x3) ? "Length 4" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBTimeInterleavingLen == 0x4) ? "Length 8" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBTimeInterleavingLen == 0x5) ? "Length 16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBTimeInterleavingLen == 0x6) ? "Length 32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerBTimeInterleavingLen == 0x6) ? "Reserved" : "UNUSED");

				}
				else
				{
					dbgidx += sprintf(dbglog + dbgidx, "LayerB is unused hierarchy layer.\n");
				}

				if(pDemodInfo->getCfgParam.isdbt.tmcc.layerCSegmentNum != 0)
				{
					dbgidx += sprintf(dbglog + dbgidx, "LayerC QAM Mode =   %s\n",
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode== 0) ? "QAM16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 1) ? "QAM32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 2) ? "QAM64" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 3) ? "QAM128 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 4) ? "QAM256 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 5) ? "QAM1024" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 6) ? "QAM4096 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 7) ? "BPSK " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 8) ? "QPSK" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 9) ? "DQPSK " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 10) ? "VSB " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 11) ? "PSK8" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 12) ? "APSK16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 13) ? "APSK32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 14) ? "NTSC" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 15) ? "PAL" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 16) ? "SECAM" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 17) ? "QAM4_NR" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCQamMode == 18) ? "QAM4" :"UNKNOWN");
					dbgidx += sprintf(dbglog + dbgidx, "LayerC Code Rate =  %s\n",
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 0) ? "1 / 2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 1) ? "1 / 3 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 2) ? "1 / 4 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 3) ? "2 / 3 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 4) ? "3 / 4 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 5) ? "2 / 5 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 6) ? "3 / 5 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 7) ? "4 / 5 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 8) ? "5 / 6 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 9) ? "6 / 7 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 10) ? "7 / 8 " :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 11) ? "8 / 9 Only DVBS2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCCodeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");


					dbgidx += sprintf(dbglog + dbgidx, "LayerC Time Interleaving = %s\n",
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCTimeInterleavingLen == 0x0) ? "Length 0" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCTimeInterleavingLen == 0x1) ? "Length 1" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCTimeInterleavingLen == 0x2) ? "Length 2" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCTimeInterleavingLen == 0x3) ? "Length 4" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCTimeInterleavingLen == 0x4) ? "Length 8" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCTimeInterleavingLen == 0x5) ? "Length 16" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCTimeInterleavingLen == 0x6) ? "Length 32" :
													(pDemodInfo->getCfgParam.isdbt.tmcc.layerCTimeInterleavingLen == 0x6) ? "Reserved" : "UNUSED");
				}
				else
				{
					dbgidx += sprintf(dbglog + dbgidx, "[debug] LayerC is unused hierarchy layer.\n");
				}

			}
			break;
		case LX_DEMOD_DVBS :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       DVBS!\n");

				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.dvbs.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.dvbs.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.dvbs.tuneMode == 0x30) ? "Auto" : "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Spec Inv    =       %s\n", (pDemodInfo->getCfgParam.dvbs.bSpectrumInv == FALSE) ? "False" : "True");


				dbgidx += sprintf(dbglog + dbgidx, "HP Code Rate =      %s\n",	(pDemodInfo->getCfgParam.dvbs.codeRate == 0) ? "1 / 2" :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 1) ? "1 / 3 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 2) ? "1 / 4 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 3) ? "2 / 3 " :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 4) ? "3 / 4 " :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 5) ? "2 / 5 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 6) ? "3 / 5 " :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 7) ? "4 / 5 " :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 8) ? "5 / 6 " :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 9) ? "6 / 7 " :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 10) ? "7 / 8 " :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 11) ? "8 / 9 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbs.codeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Constellation =     %s\n",	(pDemodInfo->getCfgParam.dvbs.constellation== 0) ? "QAM16" :
												(pDemodInfo->getCfgParam.dvbs.constellation== 1) ? "QAM32" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 2) ? "QAM64" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 3) ? "QAM128 " :
												(pDemodInfo->getCfgParam.dvbs.constellation == 4) ? "QAM256 " :
												(pDemodInfo->getCfgParam.dvbs.constellation == 5) ? "QAM1024" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 6) ? "QAM4096 " :
												(pDemodInfo->getCfgParam.dvbs.constellation == 7) ? "BPSK " :
												(pDemodInfo->getCfgParam.dvbs.constellation == 8) ? "QPSK" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 9) ? "DQPSK " :
												(pDemodInfo->getCfgParam.dvbs.constellation == 10) ? "VSB " :
												(pDemodInfo->getCfgParam.dvbs.constellation == 11) ? "PSK8" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 12) ? "APSK16" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 13) ? "APSK32" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 14) ? "NTSC" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 15) ? "PAL" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 16) ? "SECAM" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 17) ? "QAM4_NR" :
												(pDemodInfo->getCfgParam.dvbs.constellation == 18) ? "QAM4" :"UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Symbol Rate =       %d\n",	pDemodInfo->getCfgParam.dvbs.symbolRate);
				dbgidx += sprintf(dbglog + dbgidx, "Frequency   =       %d\n",	pDemodInfo->getCfgParam.dvbs.frequency);

				dbgidx += sprintf(dbglog + dbgidx, "OperatingMode =     %s\n",	(pDemodInfo->getCfgParam.dvbs.operatingMode== 0) ? "DEBUGGING_MODE" :
												(pDemodInfo->getCfgParam.dvbs.operatingMode== 1) ? "NORMAL_MODE" :
												(pDemodInfo->getCfgParam.dvbs.operatingMode == 2) ? "BLIND_LOCK_MODE" :
												(pDemodInfo->getCfgParam.dvbs.operatingMode == 3) ? "BLIND_SCAN_MODE " : "UNKNOWN");
			}
			break;
		case LX_DEMOD_DVBS2 :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       DVBS2\n");
				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.dvbs2.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.dvbs2.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.dvbs2.tuneMode == 0x30) ? "Auto" : "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Spect Inv   =       %s\n", (pDemodInfo->getCfgParam.dvbs2.bSpectrumInv == FALSE) ? "False" : "True");


				dbgidx += sprintf(dbglog + dbgidx, "HP Code Rate =      %s\n",	(pDemodInfo->getCfgParam.dvbs2.codeRate == 0) ? "1 / 2" :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 1) ? "1 / 3 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 2) ? "1 / 4 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 3) ? "2 / 3 " :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 4) ? "3 / 4 " :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 5) ? "2 / 5 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 6) ? "3 / 5 " :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 7) ? "4 / 5 " :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 8) ? "5 / 6 " :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 9) ? "6 / 7 " :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 10) ? "7 / 8 " :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 11) ? "8 / 9 Only DVBS2" :
												(pDemodInfo->getCfgParam.dvbs2.codeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");

				dbgidx += sprintf(dbglog + dbgidx, "Constellation =     %s\n",	(pDemodInfo->getCfgParam.dvbs2.constellation== 0) ? "QAM16" :
												(pDemodInfo->getCfgParam.dvbs2.constellation== 1) ? "QAM32" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 2) ? "QAM64" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 3) ? "QAM128 " :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 4) ? "QAM256 " :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 5) ? "QAM1024" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 6) ? "QAM4096 " :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 7) ? "BPSK " :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 8) ? "QPSK" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 9) ? "DQPSK " :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 10) ? "VSB " :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 11) ? "PSK8" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 12) ? "APSK16" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 13) ? "APSK32" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 14) ? "NTSC" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 15) ? "PAL" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 16) ? "SECAM" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 17) ? "QAM4_NR" :
												(pDemodInfo->getCfgParam.dvbs2.constellation == 18) ? "QAM4" :"UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Symbol Rate =       %d\n",	pDemodInfo->getCfgParam.dvbs2.symbolRate);
				dbgidx += sprintf(dbglog + dbgidx, "Frequency   =       %d\n",	pDemodInfo->getCfgParam.dvbs2.frequency);

				dbgidx += sprintf(dbglog + dbgidx, "OperatingMode =     %s\n",	(pDemodInfo->getCfgParam.dvbs2.operatingMode== 0) ? "DEBUGGING_MODE" :
												(pDemodInfo->getCfgParam.dvbs2.operatingMode== 1) ? "NORMAL_MODE" :
												(pDemodInfo->getCfgParam.dvbs2.operatingMode == 2) ? "BLIND_LOCK_MODE" :
												(pDemodInfo->getCfgParam.dvbs2.operatingMode == 3) ? "BLIND_SCAN_MODE " : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "bPilot      =       0x%x\n", pDemodInfo->getCfgParam.dvbs2.bPilot);
			}
			break;
		case LX_DEMOD_ANALOG :
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       ANALOG\n");

			}
			break;
		case LX_DEMOD_DTMB:
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode    =       DTMB\n");
				dbgidx += sprintf(dbglog + dbgidx, "Tune Mode   =       %s\n",	(pDemodInfo->getCfgParam.dtmb.tuneMode == 0x10) ? "Normal" :
												(pDemodInfo->getCfgParam.dtmb.tuneMode == 0x20) ? "Manual" :
												(pDemodInfo->getCfgParam.dtmb.tuneMode == 0x30) ? "Auto" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Channel BW  =       %s\n", 	(pDemodInfo->getCfgParam.dtmb.channelBW	== 0x0) ? "1.7MHz" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x1) ? "5MHz" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x2) ? "6MHz" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x3) ? "7MHz" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x4) ? "8MHz" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x5) ? "7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x6) ? "8MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x7) ? "8MHz, 7MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x8) ? "8MHz, 7MHz, 6MHz(Auto Detection)" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0x9) ? "DVB-T No operation" :
												(pDemodInfo->getCfgParam.dtmb.channelBW == 0xA) ? "VSB No operation"	: "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Carrier Mode =      %s\n",	(pDemodInfo->getCfgParam.dtmb.carrierMode== 0x0) ? "Single Carrier" :
												(pDemodInfo->getCfgParam.dtmb.carrierMode == 0x1) ? "Multi Carrier" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Code Rate   =       %s\n",	(pDemodInfo->getCfgParam.dtmb.codeRate == 0) ? "1 / 2" :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 1) ? "1 / 3 Only DVBS2" :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 2) ? "1 / 4 Only DVBS2" :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 3) ? "2 / 3 " :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 4) ? "3 / 4 " :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 5) ? "2 / 5 Only DVBS2" :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 6) ? "3 / 5 " :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 7) ? "4 / 5 " :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 8) ? "5 / 6 " :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 9) ? "6 / 7 " :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 10) ? "7 / 8 " :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 11) ? "8 / 9 Only DVBS2" :
												(pDemodInfo->getCfgParam.dtmb.codeRate == 12) ? "9 / 10 Only DVBS2" : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "PN Mode     =       %s\n",	(pDemodInfo->getCfgParam.dtmb.pnMode== 0) ? "420_C" :
												(pDemodInfo->getCfgParam.dtmb.pnMode== 1) ? "420_V" :
												(pDemodInfo->getCfgParam.dtmb.pnMode == 2) ? "595" :
												(pDemodInfo->getCfgParam.dtmb.pnMode == 3) ? "945_C " :
												(pDemodInfo->getCfgParam.dtmb.pnMode == 4) ? "945_V " : "UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Constellation =     %s\n",	(pDemodInfo->getCfgParam.dtmb.constellation== 0) ? "QAM16" :
												(pDemodInfo->getCfgParam.dtmb.constellation== 1) ? "QAM32" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 2) ? "QAM64" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 3) ? "QAM128 " :
												(pDemodInfo->getCfgParam.dtmb.constellation == 4) ? "QAM256 " :
												(pDemodInfo->getCfgParam.dtmb.constellation == 5) ? "QAM1024" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 6) ? "QAM4096 " :
												(pDemodInfo->getCfgParam.dtmb.constellation == 7) ? "BPSK " :
												(pDemodInfo->getCfgParam.dtmb.constellation == 8) ? "QPSK" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 9) ? "DQPSK " :
												(pDemodInfo->getCfgParam.dtmb.constellation == 10) ? "VSB " :
												(pDemodInfo->getCfgParam.dtmb.constellation == 11) ? "PSK8" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 12) ? "APSK16" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 13) ? "APSK32" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 14) ? "NTSC" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 15) ? "PAL" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 16) ? "SECAM" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 17) ? "QAM4_NR" :
												(pDemodInfo->getCfgParam.dtmb.constellation == 18) ? "QAM4" :"UNKNOWN");
				dbgidx += sprintf(dbglog + dbgidx, "Time interval =     %s\n",	(pDemodInfo->getCfgParam.dtmb.bM720	== TRUE) ? "720" : "240");

			}
			break;
		case LX_DEMOD_UNKOWN_OPMODE:
			{
				dbgidx += sprintf(dbglog + dbgidx, "OperMode = UNKOWN_OPMODE\n");
			}
			break;
		default :
			break;
	}

	dbgidx += sprintf(dbglog + dbgidx,"*********************Signal Status*********************\n");
	dbgidx += sprintf(dbglog + dbgidx, "Packet Error =    %d\n",pDemodInfo->signalStatus.packetError);
	dbgidx += sprintf(dbglog + dbgidx, "BER =             %d\n",pDemodInfo->signalStatus.ber);
	dbgidx += sprintf(dbglog + dbgidx, "AGC =             %d\n",pDemodInfo->signalStatus.agc);
	dbgidx += sprintf(dbglog + dbgidx, "MSE =             %d\n",pDemodInfo->signalStatus.m.mse);
	dbgidx += sprintf(dbglog + dbgidx, "bMSE =            %d\n",pDemodInfo->signalStatus.m.bMse);
	dbgidx += sprintf(dbglog + dbgidx, "Const Power	=     %d\n",pDemodInfo->signalStatus.m.constPwr);
	dbgidx += sprintf(dbglog + dbgidx, "Frequency Offset= %d\n",pDemodInfo->freqOffset);
	dbgidx += sprintf(dbglog + dbgidx,"*******************************************************\n");

	return dbgidx;

}

int DEMOD_Register_Dump(char * dbglog)
{
	int dbgidx = 0;

	UINT32 regValue = 0;
	UINT16 regAddress = 0;

	dbgidx += sprintf(dbglog + dbgidx,"*******************************************************\n");

	dbgidx += sprintf(dbglog + dbgidx,"*********************Register_Info*********************\n");

	dbgidx += sprintf(dbglog + dbgidx,"\n  *********************COMMON*********************\n");
//Common
	regAddress = 0x0090 ; //AGC Signal Power Address
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  AgcSigPwr[0x%04x][31:16]	=	0x%08x\n", regAddress,regValue);

	regAddress = 0x0000 ; //CR center Frequency
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  CRCenterF[0x%04x][23:0] 	=	0x%08x\n", regAddress,regValue);

	regAddress = 0x0004 ; //TR center Frequency
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  TRCenterF[0x%04x][23:0] 	=	0x%08x\n", regAddress,regValue);

	regAddress = 0x00C8 ; //CSTS DONE
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  CSTS_DONE[0x%04x][27]		=	0x%08x [1 : Done / 0 : Undone]\n", regAddress,regValue);

	regAddress = 0x00CC ; //ICFO DONE
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  ICFO_DONE[0x%04x][8]		=	0x%08x [1 : Done / 0 : Undone]\n", regAddress,regValue);

	regAddress = 0x00DC ; //TXP DONE
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  TXP_LOCK[0x%04x][28]		=	0x%08x [1 : Lock / 0 : Unlock]\n", regAddress,regValue);

	regAddress = 0x000C ; //RISIC_AUTO_ON
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  RISIC_AUTO_ON[0x%04x][11]	=	0x%08x\n", regAddress,regValue);

	dbgidx += sprintf(dbglog + dbgidx,"\n  *********************DVB_T2*********************\n");

	regAddress = 0x3040 ; //The number of PLP
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  NUM_PLP[0x%04x][15:8]		=	0x%08x\n", regAddress,regValue);

	regAddress = 0x3038 ; //The number of DATA PLP
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  NUM_DATA_PLP[0x%04x][7:0]	=	0x%08x\n", regAddress,regValue);

	regAddress = 0x3050 ; //Current PLP ID
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  Current_PLP_ID[0x%04x][31:24]	=	0x%08x\n", regAddress,regValue);

	regAddress = 0x3048 ; //L1 Pre Done , L1 Post Done
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  L1_DONE[0x%04x][28:L1_PRE,27:L1_POST] =	0x%08x [1 : Done / 0 : Undone]\n", regAddress,regValue);

	dbgidx += sprintf(dbglog + dbgidx,"\n  ***************DVB-C,DVB-S/S2,QAM***************\n");
	regAddress = 0x0014 ; //nbw Stg
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx, "  nbw_stg[0x%04x][27:24]	=	0x%08x\n", regAddress,regValue);

	dbgidx += sprintf(dbglog + dbgidx,"\n  ***********************VSB**********************\n");
	regAddress = 0x00b8 ; //scfpll
	if(RET_OK != DEMOD_DBB_APB_DEBUG_Read (regAddress, &regValue))
	{
		DEMOD_ERROR("FAIL, DEMOD_DBB_APB_DEBUG_Read()\n");
		DEMOD_RETURN_FAIL(__F__);
	}
	dbgidx += sprintf(dbglog + dbgidx,"  scfpll[0x%04x][7:lock,3:done] =	0x%08x [1 : Done/Lock / 0 : Undone/Unlock]\n", regAddress,regValue);
	dbgidx += sprintf(dbglog + dbgidx,"\n*******************************************************\n");

	return dbgidx;

}


#if 0
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_RepeaterEnable.
 * Enable / Disable GBB I2C repeater function
 *
 * @param bEnable [IN] 	BOOLEAN - Enable/Disable I2C repeater
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_RepeaterEnable(BOOLEAN bEnable)
{
	if(NULL == g_demod_hal.RepeaterEnable)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.RepeaterEnable(bEnable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_SoftwareReset
 * Reset GBB module by software.
 *
 * @param  NONE
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_SoftwareReset(void)
{
	if(NULL == g_demod_hal.SoftwareReset)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.SoftwareReset())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Serial_Control
 * Control TS output mode(serial/Parallel)
 *
 * @param bEnable 	[IN] Serial(TRUE) / Parallel(FALSE)
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_Serial_Control(BOOLEAN bEnable)
{
	if(NULL == g_demod_hal.Serial_Control)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Serial_Control(bEnable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_Serial_Control);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Access_Control
 * Enable/Disable demod apb access control
 *
 * @param bEnable 	[IN] power save mode(TRUE) / normal mode(FALSE)
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_APB_AccessControl (BOOLEAN bEnable)
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();
	int ret = RET_OK;

	if(NULL == g_demod_hal.APB_AccessControl) {
		DEMOD_NOT_SUPPORTED(__F__);
	}

	ret = g_demod_hal.APB_AccessControl(bEnable);

	DEMOD_NOTI("apb access %s %s\n",
			(bEnable == TRUE) ? "allow" : "deny",
			(RET_OK == ret) ? "ok" : "error");

	if (RET_OK == ret) {
		pDemodDev->apb_access = bEnable;
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Power_Save
 * Enable/Disable power save mode
 *
 * @param bEnable 	[IN] power save mode(TRUE) / normal mode(FALSE)
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_Power_Save(BOOLEAN bEnable)
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();
	int ret = RET_OK;

	if(NULL == g_demod_hal.Power_Save) {
		pr_err("LowPower::error::groupother::demod::%d::%s-%s::%s::error::reason(not support)\n",
			DEMOD_TASK_OpenCount(),
			current->group_leader->comm, current->comm,
			(bEnable == TRUE) ? "enter" : "leave");
		return RET_OK;
	}

	ret = g_demod_hal.Power_Save(bEnable);

	pr_info("LowPower::info::groupother::demod::%d::%s-%s::%s::%s\n",
			DEMOD_TASK_OpenCount(),
			current->group_leader->comm, current->comm,
			(bEnable == TRUE) ? "enter" : "leave",
			(RET_OK == ret) ? "ok" : "error");

	if (RET_OK == ret) {
		pDemodDev->power_save = bEnable;
	}

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
* DEMOD_StdOperModeContrl
* Set standard operation mode, Bandwidth and symbol rate
*
* @param operMode [IN] LX_DEMOD_OPER_MODE_T - DVBT, DVBC, ATSC, QAM, ISDBT
* @param bandWd [IN] LX_DEMOD_BWMODE_T
* @param symbr [IN] LX_DEMOD_SYMRDET_MODE_T.
* @return if Succeeded - RET_OK else-RET_ERROR
* @see
* @author  Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_StdOperModeContrl( LX_DEMOD_OPER_MODE_T operMode, LX_DEMOD_BWMODE_T bandWd, LX_DEMOD_SYMRDET_MODE_T symbr)
{
	if(NULL == g_demod_hal.StdOperModeContrl)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.StdOperModeContrl(operMode, bandWd, symbr ))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/**
 * DEMOD_NeverlockScan
 * Get the neverlock flag indicator.
 *
 * @param	*pDemodInfo			[IN] DEMOD_CTX_T.
 * @param	ResetOn				[IN] 	LX_DEMOD_FLAG_T  - force to initialize the postjob.
 * @param	*pScanProcessing		[OUT] LX_DEMOD_FLAG_T- the flag that scan is done or not done.
 * @param	*pScanLock			[OUT] LX_DEMOD_LOCK_STATE_T - scan lock result.
 * @return if Succeeded - RET_OK else-TU_ERROR
 * @author 	Jeongpil.yun(jeongpil.yun@lge.com)
*/
int DEMOD_NeverlockScan(DEMOD_CTX_T *pDemodInfo, LX_DEMOD_FLAG_T ResetOn, LX_DEMOD_FLAG_T *pScanProcessing, LX_DEMOD_LOCK_STATE_T *pScanLock)
{
	if(NULL == g_demod_hal.NeverlockScan)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.NeverlockScan(pDemodInfo, ResetOn, pScanProcessing, pScanLock))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_TPOutCLKEnable
 * Enable/Diable the output of TP CLK
 *
 * @param bEnable 	[IN] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_TPOutCLKEnable(BOOLEAN bEnable)
{
	DEMOD_DEV_T * pDemodDev = DEMOD_Get_Device_Data();

	if(NULL == g_demod_hal.TPOutCLKEnable)
		DEMOD_NOT_SUPPORTED(__F__);

	DEMOD_NOTI("call TPOutCLKEnable(%s), ps %d\n", bEnable ? "true" : "false", pDemodDev->power_save);

	//if (FALSE == pDemodDev->power_save) {
		if(RET_OK != g_demod_hal.TPOutCLKEnable(bEnable))
			DEMOD_RETURN_FAIL(__F__);
	//} else {
	//	DEMOD_NOTI("skip, power_save");
	//}
	return RET_OK;

}
EXPORT_SYMBOL(DEMOD_TPOutCLKEnable);


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_GetTsClkRate
 * Enable/Diable the output of TP CLK
 *
 * @param bEnable 	[IN] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_GetTsClkRate(UINT32 *demodTsClkRate)
{
	if(NULL == g_demod_hal.GetTsClkRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.GetTsClkRate(demodTsClkRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_GetTsClkRate);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Set_IF_Frq
 * Set IF frequency registers on DVB-C mode.
 *
 * @param ifFrq 	[IN] UINT32 - IF frequency.
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Set_IF_Frq(UINT32 ifFrq)
{
	if(NULL == g_demod_hal.Set_IF_Frq)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_IF_Frq(ifFrq))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_Set_IF_Frq);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Set_AGCPolarity
 * Set IF frequency registers on DVB.
 *
 * @param ifFrq 	[IN] UINT32 - IF frequency.
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Set_AGCPolarity(LX_DEMOD_AGC_POLAR_T agcPola)
{
	if(NULL == g_demod_hal.Set_AGCPolarity)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_AGCPolarity(agcPola))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Set_SpectrumCtrl
 * Set IF frequency registers on DVB.
 *
 * @param bAutoEnable 		[IN] BOOLEAN - auto or manual.
 * @param bSpecInvEnable 	[IN] BOOLEAN - normal or inversion.
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Set_SpectrumCtrl(BOOLEAN bAutoEnable, BOOLEAN bSpecInvEnable)
{
	if(NULL == g_demod_hal.Set_SpectrumCtrl)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_SpectrumCtrl(bAutoEnable, bSpecInvEnable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_Id.
 * Get GBB demod ID.
 *
 * @param *cell_id [OUT] UINT16 - GBB demod ID
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_Id(UINT16 *pId)  //jeongpil.yun
{
	if(NULL == g_demod_hal.Get_Id)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_Id(pId))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_SpectrumStatus.
 * Get spectrum mode info.
 * It is only useful when auto spectrum mode detection is set.
 *
 * @param  *pSpectrumAuto [OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMOD_AUTO or LX_DEMOD_MANUAL.
 * @param  *pSpectrumInv [OUT] LX_DEMOD_LOCK_STATE_T - LX_DEMOD_NORMAL or LX_DEMOD_INVERSION.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_SpectrumStatus(LX_DEMOD_LOCK_STATE_T *pSpectrumAuto, LX_DEMOD_LOCK_STATE_T *pSpectrumInv)
{
	if(NULL == g_demod_hal.Get_SpectrumStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_SpectrumStatus(pSpectrumAuto, pSpectrumInv))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_IFAGC
 * Get IF AGC value
 *
 * @param *pIfAgc 	[OUT] UINT16 .
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_IFAGC(UINT16 *pIfAgc)
{
	if(NULL == g_demod_hal.Get_IFAGC)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_IFAGC(pIfAgc))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_OperMode.
 * Get GBB operation mode.
 *
 * @param *pOperMode [OUT] LX_DEMOD_OPER_MODE_T - GBB operation mode
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_OperMode(LX_DEMOD_OPER_MODE_T *pOperMode)
{
	if(NULL == g_demod_hal.Get_OperMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_OperMode(pOperMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_Get_OperMode);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_CarrierFreqOffset
 * Get carrier offset frequency in KHz
 *
 * @param *pFreqOff 	[OUT] SINT32 - offset frequency: unit: KHz.
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_CarrierFreqOffset(SINT32 *pFreqOff)
{
	if(NULL == g_demod_hal.Get_CarrierFreqOffset)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_CarrierFreqOffset(pFreqOff))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_Get_CarrierFreqOffset);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_TPIFStatus
 * @param *pbEnable	  [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_TPIFStatus(BOOLEAN *pbEnable)
{
	if(NULL == g_demod_hal.Get_TPIFStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_TPIFStatus(pbEnable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_VABER
 * Get BER before RS on DVB
 *
 * @param berInterval 	[IN] VABERCNTMODE_T - 10^6 data is default
 * @param *pVber 	[OUT] UINT32.
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_VABER(UINT32 *pVber)
{
	if(NULL == g_demod_hal.Get_VABER)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_VABER(pVber))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Total_Signal_infomation
 * Get Total_Signal_information
 *
 * @param
 * @param
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/

int DEMOD_Total_Signal_infomation(LX_DEMOD_SIGNAL_TOTAL_T *pSignalStatus)
{
	if(NULL == g_demod_hal.Get_Total_Signal_Infomation)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_Total_Signal_Infomation(pSignalStatus))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Tune_Cfg_infomation
 * Get Total_Signal_information
 *
 * @param
 * @param
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/

int DEMOD_Tune_Cfg_infomation(LX_DEMOD_SIGNAL_TUNE_CFG_T *pSignalStatus)
{
	if(NULL == g_demod_hal.Get_Cfg_Information)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_Cfg_Information(pSignalStatus))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_Packet_Error
 * Get packet error
 *
 * @param *pSnr 	[OUT] UINT8.
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_Packet_Error(UINT32 *pError)
{
	if(NULL == g_demod_hal.Get_Packet_Error)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_Packet_Error(pError))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;

}
EXPORT_SYMBOL(DEMOD_Get_Packet_Error);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_BandWidthMode
 * Get the information of bandwidth .
 *
 * @param *ChannelBW 	[OUT] LX_DEMOD_BWMODE_T - 6, 7 and 8 MHZ.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_BandWidthMode( LX_DEMOD_BWMODE_T *ChannelBW )
{
	if(NULL == g_demod_hal.Get_BandWidthMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_BandWidthMode(ChannelBW))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 DEMOD_Get_QAMMode
 * Get the information of QAM mode .
 *
 * @param *pQamMode [OUT] LX_DEMOD_RF_MODE_T - 16QAM, 32QAM, 64QAM, 128QAM, 256QAM, QPSK.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_QAMMode( LX_DEMOD_RF_MODE_T *pQamMode )
{
	if(NULL == g_demod_hal.Get_QAMMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_QAMMode(pQamMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Get_MseInfo
 * Get signal MSE info.
 *
 * @param *pSigMse [OUT] LX_DEMOD_MSE_T.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_Get_MseInfo( LX_DEMOD_MSE_T *pSigMse)
{
	if(NULL == g_demod_hal.Get_MseInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_MseInfo(pSigMse))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Lock
 * Check the DVB lock state
 *
 * @param whatLock 		[IN] LX_DEMOD_LOCK_STATUS_T - which lock flags are selected.
 * @param lockState 	[OUT] LX_DEMOD_LOCK_STATE_T - LOCKED OR NOT LOCKED.
 *  @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Get_Lock(LX_DEMOD_LOCK_STATUS_T whatLock, LX_DEMOD_LOCK_STATE_T *lockState)
{
	if(NULL == g_demod_hal.Get_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_Lock(whatLock, lockState))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_Get_Lock);


int DEMOD_Get_SysLockTime(UINT16 *pSyslocktime)
{
	if(NULL == g_demod_hal.Get_SysLockTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_SysLockTime(pSyslocktime))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Get_FecLockTime(UINT16 *pFeclocktime)
{
	if(NULL == g_demod_hal.Get_FecLockTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_FecLockTime(pFeclocktime))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Set_Frame_resynchronizaiton(BOOLEAN bEnable)
{
	if(NULL == g_demod_hal.Set_Frame_resynchronizaiton)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_Frame_resynchronizaiton(bEnable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;

}
EXPORT_SYMBOL(DEMOD_Set_Frame_resynchronizaiton);

int DEMOD_Get_FW_PartInfo(UINT32 *pFW_Info)
{
	if(NULL == g_demod_hal.Get_FW_Info)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_FW_Info(pFW_Info))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;

}
EXPORT_SYMBOL(DEMOD_Get_FW_PartInfo);

int DEMOD_Get_Dump(void)
{
	if(NULL == g_demod_hal.Get_Dump)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_Dump())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}


int DEMOD_ADC_Enable(void)
{
	if(NULL == g_demod_hal.ADC_Enable)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ADC_Enable())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}




/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_Set_CountryGrp
 * Enable/Diable the output of TP CLK
 *
 * @param bEnable 	[IN] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_Set_CountryGrp(BOOLEAN bEnable)
{
	if(NULL == g_demod_hal.CountryGrpSetting)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.CountryGrpSetting(bEnable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;

}
EXPORT_SYMBOL(DEMOD_Set_CountryGrp);


#if 0
#endif

/***********************************************************************************
* DVB common FUNCTIONS
************************************************************************************/

#if 0
#endif

/***********************************************************************************
* DVBC function
************************************************************************************/


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_AutoSymbolRateDet
 * Enable/Diable automatic symbol rate detection on DVB-C mode.
 *
 * @param  symrateMode  [IN]  LX_DEMOD_SYMRDET_MODE_T.
 * @param  SymbolRate  [IN]   UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_AutoSymbolRateDet(LX_DEMOD_SYMRDET_MODE_T symrateMode, UINT16 SymbolRate)
{
	if(NULL == g_demod_hal.DVBC_AutoSymbolRateDet)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_AutoSymbolRateDet(symrateMode, SymbolRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_IsSymbolRateAuto
 * Enable/Diable automatic symbol rate detection on DVB-C mode.
 *
 * @param  *bAuto - BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_IsSymbolRateAuto(BOOLEAN *bAuto)
{
	if(NULL == g_demod_hal.DVBC_IsSymbolRateAuto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_IsSymbolRateAuto(bAuto))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_IsQammodeAutoDet
 * Control automatic setting of DVBC config.
 *
 * @param *bAutoQam 	[OUT] BOOLEAN - dectection automatically  (TRUE) or manually(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_IsQammodeAutoDet (BOOLEAN *bAutoQam)
{
	if(NULL == g_demod_hal.DVBC_IsQammodeAutoDet)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_IsQammodeAutoDet(bAutoQam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T.
 * This function is applied only to A0 version, not to A1 version.
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Set_DefaultRegisterValue(void)
{
	if(NULL == g_demod_hal.DVBC_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Set_DefaultRegisterValue())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Set_Config_auto
 * Control automatic setting of DVBC config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Set_Config_auto (BOOLEAN bAutoDetect)
{
	if(NULL == g_demod_hal.DVBC_Set_Config_auto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Set_Config_auto(bAutoDetect))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Set_QamMode
 * Set DVBC config parameters manually.
 *
 * @param constel 		[IN] UINT8 - QAM mode : 16QAM(0), 32QAM(1), 64QAM(2), 128QAM(3), 256QAM(4).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_DVBC_Set_QamMode (LX_DEMOD_RF_MODE_T constel)
{
	if(NULL == g_demod_hal.DVBC_Set_QamMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Set_QamMode(constel))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Set_NeverLockWaitTime(UINT32 waitMs)
{
	if(NULL == g_demod_hal.DVBC_Set_NeverLockWaitTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Set_NeverLockWaitTime(waitMs))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Get_SymbolRateDetect
 * Get symbol rate in KHz (Don't use this function until revision A1)
 *
 * @param *pSymbolRate 	[OUT] UINT16 - symbol rate : unit: KHz.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Get_SymbolRateDetect(UINT16 *pSymbolRate)
{
	if(NULL == g_demod_hal.DVBC_Get_SymbolRateDetect)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Get_SymbolRateDetect(pSymbolRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Get_SymbolRateStatus
 * Get symbol rate detection state on DVB-C
 * Don't use this function until revision A1.
 *
 * @param *pSymbolRateDet 	[OUT] SYMBOLRATE_STATE_T - status and detected symbol rate .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Get_SymbolRateStatus(LX_DEMOD_SYMBOLRATE_STATE_T *pSymbolRateDet)
{
	if(NULL == g_demod_hal.DVBC_Get_SymbolRateStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Get_SymbolRateStatus(pSymbolRateDet))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Get_QamModeDetectStatus
 * Get QAM mode detection state and detected QAM mode on DVB-C
 *
 * @param *pQamModeDet 	[OUT] SYMBOLRATE_STATE_T - status and detected QAM mode .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Get_QamModeDetectStatus(LX_DEMOD_QAMMODE_STATE_T *pQamModeDet)
{
	if(NULL == g_demod_hal.DVBC_Get_QamModeDetectStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Get_QamModeDetectStatus(pQamModeDet))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Get_DvbInfo
 * Get all information on DVB-C for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Get_DvbInfo(void)
{
	if(NULL == g_demod_hal.DVBC_Get_DvbInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Get_DvbInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	if(NULL == g_demod_hal.DVBC_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DVBC_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

#if 0
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_IsQammodeAutoDet
 * Control automatic setting of DVBC2 config.
 *
 * @param *bAutoQam 	[OUT] BOOLEAN - dectection automatically  (TRUE) or manually(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_IsQammodeAutoDet (BOOLEAN *bAutoQam)
{
	if(NULL == g_demod_hal.DVBC2_IsQammodeAutoDet)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_IsQammodeAutoDet(bAutoQam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T.
 * This function is applied only to A0 version, not to A1 version.
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Set_DefaultRegisterValue(void)
{
	if(NULL == g_demod_hal.DVBC2_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Set_DefaultRegisterValue())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Set_Config_auto
 * Control automatic setting of DVBC config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Set_Config_auto (BOOLEAN bAutoDetect)
{
	if(NULL == g_demod_hal.DVBC2_Set_Config_auto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Set_Config_auto(bAutoDetect))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_DVBC2_Set_Config_auto is enabled.
 *
 * @param *pDvbc2ConfigParam 	[IN] LX_DEMOD_DVBC2_CONFIG_T - DVB-C2 config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Set_PartialConfig (LX_DEMOD_DVBC2_CONFIG_T *pDvbc2ConfigParam)
{
	if(NULL == g_demod_hal.DVBC2_Set_PartialConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Set_PartialConfig(pDvbc2ConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Set_FullConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_DVBC2_Set_Config_auto is enabled.
 *
 * @param *pDvbc2ConfigParam 	[IN] LX_DEMOD_DVBC2_CONFIG_T - DVB-C2 config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Set_FullConfig (LX_DEMOD_DVBC2_CONFIG_T *pDvbc2ConfigParam)
{
	if(NULL == g_demod_hal.DVBC2_Set_FullConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Set_FullConfig(pDvbc2ConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Set_QamMode
 * Set DVBC config parameters manually.
 *
 * @param constel 		[IN] UINT8 - QAM mode : 16QAM(0), 32QAM(1), 64QAM(2), 128QAM(3), 256QAM(4).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_DVBC2_Set_QamMode (UINT8 constel)
{
	if(NULL == g_demod_hal.DVBC2_Set_QamMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Set_QamMode(constel))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Set_NeverLockWaitTime(UINT32 waitMs)
{
	if(NULL == g_demod_hal.DVBC2_Set_NeverLockWaitTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Set_NeverLockWaitTime(waitMs))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Set_StartFrequency
 * Set start frequency.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Set_StartFrequency(UINT32 frequency)
{
	if(NULL == g_demod_hal.DVBC2_Set_StartFrequency)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Set_StartFrequency(frequency))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Get_QamModeDetectStatus
 * Get QAM mode detection state and detected QAM mode on DVB-C
 *
 * @param *pQamModeDet 	[OUT] SYMBOLRATE_STATE_T - status and detected QAM mode .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Get_QamModeDetectStatus(LX_DEMOD_QAMMODE_STATE_T *pQamModeDet)
{
	if(NULL == g_demod_hal.DVBC2_Get_QamModeDetectStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Get_QamModeDetectStatus(pQamModeDet))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Get_multiPLP_ID.
 * Set channel change parameters
 *
 * @param *pParamMultiPLPInfo  [OUT] LX_DEMOD_DVBC2_MULTI_PLP_INFO_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Get_multiPLP_ID(LX_DEMOD_DVBC2_MULTI_PLP_INFO_T *pParamMultiPLPInfo)
{

	if(NULL == g_demod_hal.DVBC2_Get_multiPLP_ID)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Get_multiPLP_ID(pParamMultiPLPInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Get_DvbInfo
 * Get all information on DVB-C2 for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Get_DvbInfo(void)
{
	if(NULL == g_demod_hal.DVBC2_Get_DvbInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Get_DvbInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	if(NULL == g_demod_hal.DVBC2_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC2_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBC2_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{


	if(NULL == g_demod_hal.DVBC2_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBC2_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

#if 0
#endif
/***********************************************************************************
* DVBT function
************************************************************************************/


/**
 * DEMOD_DVBT_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T.
 * This function is applied only to A0 version, not to A1 version.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Set_DefaultRegisterValue(LX_DEMOD_BWMODE_T band)
{
	if(NULL == g_demod_hal.DVBT_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Set_DefaultRegisterValue(band))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Set_Config_auto (BOOLEAN bAutoDetect)
{
	if(NULL == g_demod_hal.DVBT_Set_Config_auto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Set_Config_auto(bAutoDetect))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_DVBT_Set_Config_auto is enabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Set_PartialConfig (LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam)
{
	if(NULL == g_demod_hal.DVBT_Set_PartialConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Set_PartialConfig(pDvbtConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Set_FullConfig
 * Set all config parameters on DVB-T.
 * This function is used when LX_DEMOD_DVBT_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Set_FullConfig (LX_DEMOD_DVBT_CONFIG_T *pDvbtConfigParam)
{
	if(NULL == g_demod_hal.DVBT_Set_FullConfig )
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Set_FullConfig (pDvbtConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Set_NeverLockWaitTime(UINT32 waitMs)
{
	if(NULL == g_demod_hal.DVBT_Set_NeverLockWaitTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Set_NeverLockWaitTime(waitMs))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBT_Set_NeverLockWaitTime);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_DelaySpreadStatus
 * Get delay spread state on DVB-T.
 *
 * @param *pDelaySpread 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_DelaySpreadStatus(UINT16 *pDelaySpread)
{
	if(NULL == g_demod_hal.DVBT_Get_DelaySpreadStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_DelaySpreadStatus(pDelaySpread))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_Hierach_HPSel
 * Get the information if the hierachical HP is selected.
 *
 * @param *pBSetHp 	[OUT] BOOLEAN - HP (TRUE) / LP(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_Hierach_HPSel( BOOLEAN *pBSetHp )
{
	if(NULL == g_demod_hal.DVBT_Get_Hierach_HPSel)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_Hierach_HPSel(pBSetHp))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_FFTMode
 * Get the information of bandwidth on DVB-T.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_FFTMode( LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode )
{
	if(NULL == g_demod_hal.DVBT_Get_FFTMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_FFTMode(pTxModeLock, pFftMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_GuradIntervalMode
 * Get the information of guard interval on DVB-T.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_DVBT_Get_GuradIntervalMode( LX_DEMOD_GIMODE_T *pGIMode )
{
	if(NULL == g_demod_hal.DVBT_Get_GuradIntervalMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_GuradIntervalMode(pGIMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_HierachyMode
 * Get the information of hierachical mode on DVB-T.
 *
 * @param *pHierachMode[OUT] DEMOD_H13_DVB_TPS_HIERACHY_T - alpha = none, 1, 2 and 4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_HierachyMode( LX_DEMOD_DVB_TPS_HIERACHY_T *pHierachMode )
{
	if(NULL == g_demod_hal.DVBT_Get_HierachyMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_HierachyMode(pHierachMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_LpCoderRate
 * Get the information of LP code rate on DVB-T.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_DVB_TPS_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_LpCoderRate( LX_DEMOD_CODERATE_T *pLpCodeRate )
{
	if(NULL == g_demod_hal.DVBT_Get_LpCoderRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_LpCoderRate(pLpCodeRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_HpCoderRate
 * Get the information of HP code rate on DVB-T.
 *
 * @param *pLpCodeRate[OUT] LX_DEMOD_DVB_TPS_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_HpCoderRate( LX_DEMOD_CODERATE_T *pHpCodeRate )
{
	if(NULL == g_demod_hal.DVBT_Get_HpCoderRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_HpCoderRate(pHpCodeRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_CellId
 * Get TPS cell ID on DVB-T.
 *
 * @param *pCellIDLength[OUT] UINT8 - cell ID length.
 * @param *cell_id[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_CellId(UINT8 *pCellIDLength, UINT16 *cell_id)
{
	if(NULL == g_demod_hal.DVBT_Get_CellId)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_CellId(pCellIDLength, cell_id))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBT_Get_CellId);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_TpsInfo
 * Get TPS information on DVB-T
 *
 * @param *pTpsParams [OUT] LX_DEMOD_DVBT_CONFIG_T - TPS data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_TpsInfo( LX_DEMOD_DVBT_CONFIG_T *pTpsParams)
{
	if(NULL == g_demod_hal.DVBT_Get_TpsInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_TpsInfo(pTpsParams))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_TotalInfo
 * Get all information on DVB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_TotalInfo( void)
{
	if(NULL == g_demod_hal.DVBT_Get_TotalInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_TotalInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_IFO_LOCK
 * Get IFO lock on DVB-T.
 *
 * @param *pSnr [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_IFO_LOCK( BOOLEAN *pIfoLock)
{
	if(NULL == g_demod_hal.DVBT_Get_IFO_LOCK)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_IFO_LOCK(pIfoLock))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Get_CochanDetIndicator
 * Get co-channel detection indicator  on DVB-T.
 *
 * @param *pDetStatus  [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Get_CochanDetIndicator( BOOLEAN *pDetStatus)
{
	if(NULL == g_demod_hal.DVBT_Get_CochanDetIndicator)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Get_CochanDetIndicator(pDetStatus))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_EqualizereReset.
 * Reset DVB EQ module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_EqualizereReset(void)
{
	if(NULL == g_demod_hal.DVBT_EqualizereReset)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_EqualizereReset())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	if(NULL == g_demod_hal.DVBT_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBC_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	if(NULL == g_demod_hal.DVBT_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

#if 0
#endif
/***********************************************************************************
* DVBT2 function
************************************************************************************/


/**
 * DEMOD_DVBT_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T2.
 * This function is applied only to A0 version, not to A1 version.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Set_DefaultRegisterValue(LX_DEMOD_BWMODE_T band)
{
	if(NULL == g_demod_hal.DVBT2_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Set_DefaultRegisterValue(band))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Set_Config_auto
 * Control automatic setting of DVB-T2 config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Set_Config_auto (BOOLEAN bAutoDetect)
{
	if(NULL == g_demod_hal.DVBT2_Set_Config_auto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Set_Config_auto(bAutoDetect))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_DVBT_Set_Config_auto is enabled.
 *
 * @param *pDvbt2ConfigParam 	[IN] LX_DEMOD_DVBT2_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Set_PartialConfig (LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam)
{
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

#if 1
 	if(NULL == g_demod_hal.DVBT2_Set_PartialConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Set_PartialConfig(pDvbt2ConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	pDemodInfo->setCfgParam.dvbt2.unPLP = pDvbt2ConfigParam->unPLP;
	OS_MsecSleep(150);

#else

	pDemodInfo->operMode = 						LX_DEMOD_DVBT2;
	pDemodInfo->setCfgParam.dvbt2.tuneMode 		= LX_DEMOD_TUNE_NORMAL;
	pDemodInfo->setCfgParam.dvbt2.unPLP			= pDvbt2ConfigParam->unPLP;


	pDemodInfo->bNotifiedUnlock 			= FALSE;
	pDemodInfo->bNotifiedLock 				= FALSE;

	DEMOD_LockDevice();
	g_requestMsg = LX_DEMOD_STOP_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
	DEMOD_UnlockDevice();
	DEMOD_PRINT("DEMOD Task STOP\n");

	OS_MsecSleep(20);

	DEMOD_LockDevice();
	g_requestMsg = LX_DEMOD_PLP_CHANGE_REQUEST;
	wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

	DEMOD_UnlockDevice();
	DEMOD_PRINT("DEMOD Task START\n");

	OS_MsecSleep(500);
#endif

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBT2_Set_PartialConfig);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Set_FullConfig
 * Set all config parameters on DVB-T2.
 * This function is used when LX_DEMOD_DVBT_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBT_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Set_FullConfig (LX_DEMOD_DVBT2_CONFIG_T *pDvbt2ConfigParam)
{
	if(NULL == g_demod_hal.DVBT2_Set_FullConfig )
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Set_FullConfig (pDvbt2ConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Set_NeverLockWaitTime(UINT32 waitMs)
{
	if(NULL == g_demod_hal.DVBT2_Set_NeverLockWaitTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Set_NeverLockWaitTime(waitMs))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Get_DelaySpreadStatus
 * Get delay spread state on DVB-T2.
 *
 * @param *pDelaySpread 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Get_DelaySpreadStatus(UINT16 *pDelaySpread)
{
	if(NULL == g_demod_hal.DVBT2_Get_DelaySpreadStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Get_DelaySpreadStatus(pDelaySpread))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Get_FFTMode
 * Get the information of bandwidth on DVB-T2.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Get_FFTMode( LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode )
{
	if(NULL == g_demod_hal.DVBT2_Get_FFTMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Get_FFTMode(pTxModeLock, pFftMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Get_GuradIntervalMode
 * Get the information of guard interval on DVB-T2.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_DVBT2_Get_GuradIntervalMode( LX_DEMOD_GIMODE_T *pGIMode )
{
	if(NULL == g_demod_hal.DVBT2_Get_GuradIntervalMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Get_GuradIntervalMode(pGIMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Get_LpCoderRate
 * Get the information of LP code rate on DVB-T2.
 *
 * @param *pCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate )
{
	if(NULL == g_demod_hal.DVBT2_Get_CoderRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Get_CoderRate(pCodeRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Get_MultiPLPInfo.
 * Set channel change parameters
 *
 * @param *pDemodInfo [OUT] LX_DEMOD_DVBT2_CONFIG_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Get_PlpInfo(LX_DEMOD_DVBT2_CONFIG_T *pPlpParams)
{

	if(NULL == g_demod_hal.DVBT2_Get_PlpInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Get_PlpInfo(pPlpParams))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Get_multiPLP_ID.
 * Set channel change parameters
 *
 * @param *pParamMultiPLPInfo  [OUT] LX_DEMOD_DVBT2_MULTI_PLP_INFO_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Get_multiPLP_ID(LX_DEMOD_DVBT2_MULTI_PLP_INFO_T *pParamMultiPLPInfo)
{
	if(NULL == g_demod_hal.DVBT2_Get_multiPLP_ID)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Get_multiPLP_ID(pParamMultiPLPInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBT2_Get_multiPLP_ID);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Get_TotalInfo
 * Get all information on DVB-T2 for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Get_TotalInfo( void)
{
	if(NULL == g_demod_hal.DVBT2_Get_TotalInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Get_TotalInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_DVBT2_Set_MemSconfig(void)
{
	DEMOD_PRINT(" Start\n");

	if(NULL == g_demod_hal.DVBT2_Set_MemSconfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Set_MemSconfig())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_DVB_Set_MemSconfig(void)
{
	if(NULL == g_demod_hal.DVB_Set_MemSconfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVB_Set_MemSconfig())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DVBT2_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBT2_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBT2_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DVBT2_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBT2_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

#if 0
#endif

/***********************************************************************************
* VSB  function
************************************************************************************/

int DEMOD_VSB_SetDemod(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.LGDBB_VSB_SetDemod)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.LGDBB_VSB_SetDemod(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_Set_DefaultRegisterValue.
 * Initialize GBB VSB module .
 *
 * @param  NONE [IN] void
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_Set_DefaultRegisterValue(void)  //jeongpil.yun
{
	if(NULL == g_demod_hal.VSB_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_Set_DefaultRegisterValue())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_Set_NeverLockWaitTime(UINT32 waitMs)
{
	if(NULL == g_demod_hal.VSB_Set_NeverLockWaitTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_Set_NeverLockWaitTime(waitMs))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_CochannelExist.
 * Get the informantion if co-channel(NTSC) signal exists or not on VSB mode.
 *
 * @param  *pCochannel [OUT] BOOLEAN - exists /doesn't exist.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_CochannelExist(BOOLEAN *pCochannel)	//jeongpil.yun
{
	if(NULL == g_demod_hal.VSB_CochannelExist)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_CochannelExist(pCochannel))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_PreMonitor.
 * Set registers against  various noise conditions before  monitoring.
 *
 * @param  NONE [IN] void .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_PreMonitor(void)
{
	if(NULL == g_demod_hal.VSB_PreMonitor)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_PreMonitor())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_Monitor.
 * Get the RF signal status - phase noise signal, ghost signal, sync SNR B condition, phase tracker SNR A condition..
 *
 * @param  *pDemodInfo [IN] DEMOD_CTX_T .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_Monitor(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.VSB_Monitor)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_Monitor(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_Get_MSEdynStatus.
 * Get the flag whether MSE would be under operation limit (snr > 16dB : TRUE)
 *
 * @param  *pbEnable [OUT] BOOLEAN - get signal noise ratio
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_Get_MSEdynStatus(BOOLEAN *pbEnable)
{
	if(NULL == g_demod_hal.VSB_Get_MSEdynStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_Get_MSEdynStatus(pbEnable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_Get_TotalInfo
 * Get all information on VSB for debug
 *
 * @param NONE [IN].
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_Get_TotalInfo( void)
{
	if(NULL == g_demod_hal.VSB_Get_TotalInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_Get_TotalInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	if(NULL == g_demod_hal.VSB_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_VSB_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_VSB_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{

	if(NULL == g_demod_hal.VSB_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.VSB_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

#if 0
#endif

/***********************************************************************************
* QAM function
************************************************************************************/


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_SoftwareResetFEC.
 * Reset QAM FEC module.
 *
 * @param [in] NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_SoftwareResetFEC(void) //jeongpil.yun
{
	if(NULL == g_demod_hal.QAM_SoftwareResetFEC)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_SoftwareResetFEC())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_Monitor.
 * Monitoring
 *
 * @param  NONE [IN] void .
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_Monitor(void)
{
	if(NULL == g_demod_hal.QAM_Monitor)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_Monitor())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_ModeAutoDetection.
 * Enable/Disable the detection of QAM mode
 *
 * @param  bEnable [IN] - BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_ModeAutoDetection(BOOLEAN bEnable)
{
	if(NULL == g_demod_hal.QAM_ModeAutoDetection)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_ModeAutoDetection(bEnable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_H13_QAM_64Mode.
 * Set the QAM mode to QAM64 manually
 *
 * @param  NONE [IN/OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_64Mode(void)  //jeongpil.yun
{
	if(NULL == g_demod_hal.QAM_64Mode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_64Mode())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_256Mode.
 * Set the QAM mode to QAM256 manually
 *
 * @param  NONE [IN/OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_256Mode(void)  //jeongpil.yun
{
	if(NULL == g_demod_hal.QAM_256Mode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_256Mode())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_QAM_SetDemod(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.LGDBB_VSB_SetDemod)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.LGDBB_QAM_SetDemod(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_Set_DefaultRegisterValue.
 * Initialize LG1150 GBB for QAM mode.
 *
 * @param  NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR.
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_Set_DefaultRegisterValue(void)  //jeongpil.yun
{
	if(NULL == g_demod_hal.QAM_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_Set_DefaultRegisterValue())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_Set_NeverLockWaitTime(UINT32 waitMs)
{
	if(NULL == g_demod_hal.QAM_Set_NeverLockWaitTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_Set_NeverLockWaitTime(waitMs))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_Get_TotalInfo
 * Get all information on QAM for debug
 *
 * @param NONE [IN / OUT].
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_Get_TotalInfo( void)
{
	if(NULL == g_demod_hal.QAM_Get_TotalInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_Get_TotalInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.QAM_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.QAM_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_QAM_EQ_Signal_Detector.
 * Disable no signal detector function
 *
 * @param [in] NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_QAM_EQ_Signal_Detector(BOOLEAN OnOff)
{
	if(NULL == g_demod_hal.QAM_EQ_Signal_Detector)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.QAM_EQ_Signal_Detector(OnOff))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

#if 0
#endif

/***********************************************************************************
* ISDBT function
************************************************************************************/




/**
 * DEMOD_ISDBT_Set_DefaultRegisterValue
 * Set defualt register value on DVB-T.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Set_DefaultRegisterValue(void)
{
	if(NULL == g_demod_hal.ISDBT_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Set_DefaultRegisterValue())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Set_Config_auto
 * Control automatic setting of DVB-T config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Set_Config_auto (BOOLEAN bAutoDetect)
{
	if(NULL == g_demod_hal.ISDBT_Set_Config_auto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Set_Config_auto(bAutoDetect))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;

}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when DEMOD_ISDBT_Set_Config_auto is enabled.
 *
 * @param *pIsdbtConfigParam 	[IN] LX_DEMOD_ISDBT_CONFIG_T - ISDBT config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Set_PartialConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam)
{
	if(NULL == g_demod_hal.ISDBT_Set_PartialConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Set_PartialConfig(pIsdbtConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Set_FullConfig
 * Set all config parameters on ISDB-T.
 * This function is used when DEMOD_H13_ISDBT_Set_Config_auto is disabled.
 *
 * @param *pIsdbtConfigParam 	[IN] LX_DEMOD_ISDBT_CONFIG_T - ISDB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Set_FullConfig (LX_DEMOD_ISDBT_CONFIG_T *pIsdbtConfigParam)
{
	if(NULL == g_demod_hal.ISDBT_Set_FullConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Set_FullConfig(pIsdbtConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Set_NeverLockWaitTime
 * Set neverlock waiting period.
 *
 * @param waitMs 	[IN] UINT32 - unit: ms
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Set_NeverLockWaitTime(UINT32 waitMs)
{
	if(NULL == g_demod_hal.ISDBT_Set_NeverLockWaitTime)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Set_NeverLockWaitTime(waitMs))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Get_DelaySpreadStatus
 * Get delay spread state on ISDB-T.
 *
 * @param *pDelaySpread 	[OUT] UINT16.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Get_DelaySpreadStatus(UINT16 *pDelaySpread)
{
	if(NULL == g_demod_hal.ISDBT_Get_DelaySpreadStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Get_DelaySpreadStatus(pDelaySpread))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Get_FFTMode
 * Get the information of bandwidth on DVB-T.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Get_FFTMode( LX_DEMOD_LOCK_STATE_T *pTxModeLock, LX_DEMOD_FFTMODE_T *pFftMode )
{
	if(NULL == g_demod_hal.ISDBT_Get_FFTMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Get_FFTMode(pTxModeLock, pFftMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Get_GuradIntervalMode
 * Get the information of guard interval on ISDB-T.
 *
 * @param *pGIMode 	[OUT] LX_DEMOD_GIMODE_T - 1/32, 1/16, 1/8 and 1/4.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Get_GuradIntervalMode( LX_DEMOD_GIMODE_T *pGIMode )
{
	if(NULL == g_demod_hal.ISDBT_Get_GuradIntervalMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Get_GuradIntervalMode(pGIMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Get_TMCCInfo
 * Get TPS information on ISDB-T
 *
 * @param *pTpsParams [OUT] LX_DEMOD_ISDBT_TMCC_CONFIG_T - TMCC data structure.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Get_TMCCInfo( LX_DEMOD_ISDBT_TMCC_CONFIG_T *pTmccParams)
{
	if(NULL == g_demod_hal.ISDBT_Get_TMCCInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Get_TMCCInfo(pTmccParams))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Get_TotalInfo
 * Get all information on ISDB-T for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Get_TotalInfo( void)
{
	if(NULL == g_demod_hal.ISDBT_Get_TotalInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Get_TotalInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Get_IFO_LOCK
 * Get IFO lock on ISDB-T.
 *
 * @param *pSnr [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Get_IFO_LOCK( BOOLEAN *pIfoLock)
{
	if(NULL == g_demod_hal.ISDBT_Get_IFO_LOCK)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Get_IFO_LOCK(pIfoLock))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Get_CochanDetIndicator
 * Get co-channel detection indicator  on ISDB-T.
 *
 * @param *pDetStatus  [OUT] BOOLEAN.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Get_CochanDetIndicator( BOOLEAN *pDetStatus)
{
	if(NULL == g_demod_hal.ISDBT_Get_CochanDetIndicator)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Get_CochanDetIndicator(pDetStatus))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_EqualizereReset.
 * Reset DVB EQ module by software.
 *
 * @param  NONE
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_EqualizereReset(void)
{
	if(NULL == g_demod_hal.ISDBT_EqualizereReset)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_EqualizereReset())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.ISDBT_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ISDBT_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ISDBT_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.ISDBT_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_ISDBT_Set_MemSconfig(void)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.ISDBT_Set_MemSconfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_Set_MemSconfig())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_ISDBT_GetEmergencyAlertFlagStatus( BOOLEAN *pEalarm)
{
	if(NULL == g_demod_hal.ISDBT_GetEmergencyAlertFlagStatus)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ISDBT_GetEmergencyAlertFlagStatus(pEalarm))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ISDBT_GetEmergencyAlertFlagStatus);

#if 0
#endif
/***********************************************************************************
* DVBS function
************************************************************************************/


/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Set_DefaultRegisterValue
 * Set defualt register value on DVB-S.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Set_DefaultRegisterValue(void)
{
	if(NULL == g_demod_hal.DVBS_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Set_DefaultRegisterValue())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Set_Config_auto
 * Control automatic setting of DVB-S config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Set_Config_auto (BOOLEAN bAutoDetect)
{
	if(NULL == g_demod_hal.DVBS_Set_Config_auto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Set_Config_auto(bAutoDetect))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_DVBS_Set_Config_auto is enabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBS_CONFIG_T - DVB-S config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Set_PartialConfig (LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam)
{
	if(NULL == g_demod_hal.DVBS_Set_PartialConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Set_PartialConfig(pDvbsConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Set_FullConfig
 * Set all config parameters on DVB-S.
 * This function is used when LX_DEMOD_DVBS_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBS_CONFIG_T - DVB-S config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Set_FullConfig (LX_DEMOD_DVBS_CONFIG_T *pDvbsConfigParam)
{
	if(NULL == g_demod_hal.DVBS_Set_FullConfig )
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Set_FullConfig (pDvbsConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Get_CoderRate
 * Get the information of code rate on DVB-S.
 *
 * @param *pCodeRate[OUT] LX_DEMOD_DVBS_CODERATE_T - code rate : 1/2, 2/3, 3/4, 5/6 and 7/8.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate )
{
	if(NULL == g_demod_hal.DVBS_Get_CoderRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Get_CoderRate(pCodeRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Get_SymbolRate
 * Get the information of symbol rate on DVB-S.
 *
 * @param *pSymbolRate 	[OUT] UINT32
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Get_SymbolRate(UINT32 *pSymbolRate )
{
	if(NULL == g_demod_hal.DVBS_Get_SymbolRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Get_SymbolRate(pSymbolRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Get_TotalInfo
 * Get all information on DVB-S for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Get_TotalInfo( void)
{
	if(NULL == g_demod_hal.DVBS_Get_TotalInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Get_TotalInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Set_DiseqcToneMessageCtrl
 * Get all information on DVB-S for debug
 *
 * @param *pDiseqcMsg [IN] LX_DEMOD_DVBS_DiSEqC_MSG_T.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Set_DiseqcToneMessageCtrl( LX_DEMOD_DVBS_DiSEqC_MSG_T *pDiseqcMsg)
{
	if(NULL == g_demod_hal.DVBS_Set_DiseqcToneMessageCtrl)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Set_DiseqcToneMessageCtrl(pDiseqcMsg))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBS_Set_DiseqcToneMessageCtrl);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Set_EnvelopModeCtrl
 * Get all information on DVB-S for debug
 *
 * @param messageType [IN]  LX_DEMOD_MESSAGE_TYPE_T.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Set_EnvelopModeCtrl(LX_DEMOD_MESSAGE_TYPE_T messageType)
{
	if(NULL == g_demod_hal.DVBS_Set_EnvelopModeCtrl)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Set_EnvelopModeCtrl(messageType))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Get_BlindInfo
 * Get all information on DVB-S
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Get_BlindInfo(UINT32 centerFreq,  LX_DEMOD_DVBS_BLIND_PARAM_T *pBlindParam)
{
	if(NULL == g_demod_hal.DVBS_Get_BlindInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Get_BlindInfo(centerFreq, pBlindParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBSX_BlindScan_Init
 * notification BlindScan_init on DVB-S
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	jinwoo.han (jinwoo.han@lge.com)
*/

int DEMOD_DVBSX_BlindScan_Init(LX_DEMOD_BLIND_SCAN_INIT_FREQ_PARAM_T *initFreq)
{
	if(NULL == g_demod_hal.DVBSX_BlindScan_Init)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBSX_BlindScan_Init(initFreq))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBSX_BlindScan_Init);
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBSX_BlindScan_End
 * notification BlindScan_init on DVB-S
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	jinwoo.han (jinwoo.han@lge.com)
*/

int DEMOD_DVBSX_BlindScan_End(void)
{
	if(NULL == g_demod_hal.DVBSX_BlindScan_End)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBSX_BlindScan_End())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBSX_BlindScan_End);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBSX_GetTunerFreq
 * Get all information on DVB-S
 *
 * @param LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	jinwoo.han (jinwoo.han@lge.com)
*/

int DEMOD_DVBSX_GetTunerFreq(LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T *pFreqInfo)
{
	if(NULL == g_demod_hal.DVBSX_Get_TunerFreq)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBSX_Get_TunerFreq(pFreqInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBSX_GetTunerFreq);
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBSX_Get_OffsetFreq
 * Get all information on DVB-S
 *
 * @param LX_DEMOD_BLIND_SCAN_FREQ_PARAM_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	jinwoo.han (jinwoo.han@lge.com)
*/

int DEMOD_DVBSX_Get_OffsetFreq(LX_DEMOD_BLIND_SCAN_OFFSET_PARAM_T* pOffsetInfo)
{
	if(NULL == g_demod_hal.DVBSX_Get_OffsetFreq)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBSX_Get_OffsetFreq(pOffsetInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBSX_Get_OffsetFreq);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBSX_SymbolRate_Detect
 * SymbolRate Detecton DVB-S
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	jinwoo.han (jinwoo.han@lge.com)
*/

int DEMOD_DVBSX_SymbolRate_Detect(void)
{
	if(NULL == g_demod_hal.DVBSX_SymbolRate_Detec)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBSX_SymbolRate_Detec())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBSX_SymbolRate_Detect);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBSX_BlindLock_Loop
 * SymbolRate Detecton DVB-S
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	jinwoo.han (jinwoo.han@lge.com)
*/
int DEMOD_DVBSX_BlindLock_Loop(void)
{
	if(NULL == g_demod_hal.DVBSX_BlindLock_Loop)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBSX_BlindLock_Loop())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBSX_BlindLock_Loop);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBSX_Get_Nextfreq_Status
 * Get all information on DVB-S
 *
 * @param BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	jinwoo.han (jinwoo.han@lge.com)
*/

int DEMOD_DVBSX_Get_Nextfreq_Status(BOOLEAN* pBlindScanEnd)
{
	if(NULL == g_demod_hal.DVBSX_Get_Nextfreq_Status)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBSX_Get_Nextfreq_Status(pBlindScanEnd))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_DVBSX_Get_Nextfreq_Status);

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Set_BlindSpectrumMode
 * Set spectrum mode on DVB-S
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Set_BlindSpectrumMode(LX_DEMOD_DVBS_OPERATION_MODE_T spectrumMode)
{
	if(NULL == g_demod_hal.DVBS_Set_BlindSpectrumMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Set_BlindSpectrumMode(spectrumMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Set_SpectrumModeConfig
 * Set spectrum mode config on DVB-S
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_DVBS_Set_SpectrumModeConfig( BOOLEAN isBlindScan, UINT32 symbolRate)
{
	if(NULL == g_demod_hal.DVBS_Set_SpectrumModeConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Set_SpectrumModeConfig(isBlindScan,symbolRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_DVBS_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DVBS_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DVBS_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

#if 0
#endif
/***********************************************************************************
* DVBS2 function
************************************************************************************/

/**
 * DEMOD_DVBS2_Set_DefaultRegisterValue
 * Set defualt register value on DVB-S2.
 *
 * @param none
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Set_DefaultRegisterValue(void)
{
	if(NULL == g_demod_hal.DVBS2_Set_DefaultRegisterValue)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Set_DefaultRegisterValue())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Set_Config_auto
 * Control automatic setting of DVB-S2 config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/
int DEMOD_DVBS2_Set_Config_auto (BOOLEAN bAutoDetect)
{
	if(NULL == g_demod_hal.DVBS2_Set_Config_auto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Set_Config_auto(bAutoDetect))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_DVBS2_Set_Config_auto is enabled.
 *
 * @param *pDvbt2ConfigParam 	[IN] LX_DEMOD_DVBS2_CONFIG_T - DVB-S2 config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Set_PartialConfig (LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam)
{
	if(NULL == g_demod_hal.DVBS2_Set_PartialConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Set_PartialConfig(pDvbs2ConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Set_FullConfig
 * Set all config parameters on DVB-S2.
 * This function is used when LX_DEMOD_DVBS2_Set_Config_auto is disabled.
 *
 * @param *pDvbtConfigParam 	[IN] LX_DEMOD_DVBS2_CONFIG_T - DVB-S2 config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Set_FullConfig (LX_DEMOD_DVBS2_CONFIG_T *pDvbs2ConfigParam)
{
	if(NULL == g_demod_hal.DVBS2_Set_FullConfig )
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Set_FullConfig (pDvbs2ConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Get_CoderRate
 * Get the information of code rate on DVB-S2.
 *
 * @param *pCodeRate[OUT] LX_DEMOD_CODERATE_T - code rate : 1/2, 1/3, 1/4, 2/3, 3/4, 5/6, 8/9 and 9/10.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Get_CoderRate( LX_DEMOD_CODERATE_T *pCodeRate )
{
	if(NULL == g_demod_hal.DVBS2_Get_CoderRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Get_CoderRate(pCodeRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Get_Pilot
 * Get the information of pilot on DVB-S2.
 *
 * @param *pPilot[OUT] BOOLEAN
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Get_Pilot(BOOLEAN *pPilot )
{
	if(NULL == g_demod_hal.DVBS2_Get_Pilot)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Get_Pilot(pPilot))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Get_SymbolRate
 * Get the information of symbol rate on DVB-S2.
 *
 * @param *pSymbolRate 	[OUT] UINT32
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Get_SymbolRate(UINT32 *pSymbolRate )
{
	if(NULL == g_demod_hal.DVBS2_Get_SymbolRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Get_SymbolRate(pSymbolRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Get_TotalInfo
 * Get all information on DVB-S2 for debug
 *
 * @param NONE.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Get_TotalInfo( void)
{
	if(NULL == g_demod_hal.DVBS2_Get_TotalInfo)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Get_TotalInfo())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_DVBS2_Set_MemSconfig(void)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.DVBS2_Set_MemSconfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Set_MemSconfig())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DVBS2_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DVBS2_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DVBS2_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DVBS2_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DVBS2_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Obtaining_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DTMB_Obtaining_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DTMB_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Monitoring_Signal_Lock.
 * Set channel change parameters
 *
 * @param *pDemodInfo [IN] DEMOD_CTX_T
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DTMB_Monitoring_Signal_Lock(DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.DTMB_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Get_Carrier_Mode
 * Get the information of carrier_mode .
 *
 * @param *pCodeRate[OUT] LX_DEMOD_CARRIERMODE_T - carrier mode : Single and Multi.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/

int DEMOD_DTMB_Get_Carrier_Mode( LX_DEMOD_CARRIERMODE_T *pCarrierMode )
{
	if(NULL == g_demod_hal.DTMB_Get_CarrierMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Get_CarrierMode(pCarrierMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Get_Time_Interval
 * Get the information of Time Interval.
 *
 * @param *pCodeRate[OUT] LX_DEMOD_CARRIERMODE_T - carrier mode : Single and Multi.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/

int DEMOD_DTMB_Get_Time_Interval( BOOLEAN *pbM720 )
{
	if(NULL == g_demod_hal.DTMB_Get_Time_Interval)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Get_Time_Interval(pbM720))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Get_PN_Mode
 * Get the information of code rate on D.
 *
 * @param *pCodeRate[OUT] LX_DEMOD_CARRIERMODE_T - carrier mode : Single and Multi.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/

int DEMOD_DTMB_Get_PN_Mode( LX_DEMOD_PNMODE_T *pPnMode )
{
	if(NULL == g_demod_hal.DTMB_Get_PnMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Get_PnMode(pPnMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Get_Code_Rate
 * Get the information of code rate on DVB-S2.
 *
 * @param *pCodeRate[OUT] LX_DEMOD_CARRIERMODE_T - carrier mode : Single and Multi.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/

int DEMOD_DTMB_Get_Code_Rate( LX_DEMOD_CODERATE_T *pCodeRate )
{
	if(NULL == g_demod_hal.DTMB_Get_CodeRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Get_CodeRate(pCodeRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Get_Constellation
 * Get the information of code rate on DVB-S2.
 *
 * @param *pCodeRate[OUT] LX_DEMOD_CARRIERMODE_T - carrier mode : Single and Multi.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jinwoo.han (Jinwoo.han@lge.com)
*/

int DEMOD_DTMB_Get_Constellation( LX_DEMOD_RF_MODE_T *pConstellation )
{
	if(NULL == g_demod_hal.DTMB_Get_Constellation)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Get_Constellation(pConstellation))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Set_Config_auto
 * Control automatic setting of DVB-T2 config.
 *
 * @param bAutoDetect 	[IN] BOOLEAN - automatic setting (TRUE) / manual setting(FALSE).
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DTMB_Set_Config_auto (BOOLEAN bAutoDetect)
{
	if(NULL == g_demod_hal.DTMB_Set_Config_auto)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Set_Config_auto(bAutoDetect))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_DTMB_Set_PartialConfig
 * Set hierachical signal path and bandwidth.
 * This function is used when LX_DEMOD_DVBT_Set_Config_auto is enabled.
 *
 * @param *pDvbt2ConfigParam 	[IN] LX_DEMOD_DVBT2_CONFIG_T - DVB-T config. structure
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_DTMB_Set_PartialConfig (LX_DEMOD_DTMB_CONFIG_T *pDtmbConfigParam)
{
	if(NULL == g_demod_hal.DTMB_Set_PartialConfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Set_PartialConfig(pDtmbConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_DTMB_Set_MemSconfig(void)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.DTMB_Set_MemSconfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.DTMB_Set_MemSconfig())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

#if 0
#endif

/***********************************************************************************
************************************************************************************/
/**
 * DEMOD_ATSC3_Get_FFTMode
 * Get the information of bandwidth onATSC3.
 *
 * @param *pTxModeLock 	[OUT] LX_DEMOD_LOCK_STATE_T - FFT mode lock state.
 * @param *pFftMode 	[OUT] LX_DEMOD_FFTMODE_T - detected FFT mode.
 * @return if Succeeded - RET_OK else-RET_ERROR
 * @see
 * @author 	Jeongpil.yun (jeongpil.yun@lge.com)
*/

int DEMOD_ATSC3_Get_FFTMode(LX_DEMOD_FFTMODE_T *pFftMode )
{
	if(NULL == g_demod_hal.ATSC3_Get_FFTMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Get_FFTMode(pFftMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ATSC3_Get_FFTMode);



int DEMOD_ATSC3_Get_GuradIntervalMode(LX_DEMOD_ATSC3_GIMODE_T *pGIMode)
{
	if(NULL == g_demod_hal.ATSC3_Get_GuradIntervalMode)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Get_GuradIntervalMode(pGIMode))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ATSC3_Get_GuradIntervalMode);


int DEMOD_ATSC3_Get_CodeRate(LX_DEMOD_ATSC3_CODERATE_T *pCodeRate)
{
	if(NULL == g_demod_hal.ATSC3_Get_CodeRate)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Get_CodeRate(pCodeRate))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ATSC3_Get_CodeRate);



int DEMOD_ATSC3_Get_Constellation (LX_DEMOD_ATSC3_CONSTELLATION_T *pConstellation)
{
	if(NULL == g_demod_hal.ATSC3_Get_Constellation)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Get_Constellation(pConstellation))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ATSC3_Get_Constellation);


int DEMOD_ATSC3_Obtaining_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.ATSC3_Obtaining_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Obtaining_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}


int DEMOD_ATSC3_Monitoring_Signal_Lock (DEMOD_CTX_T *pDemodInfo)
{
	if(NULL == g_demod_hal.ATSC3_Monitoring_Signal_Lock)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Monitoring_Signal_Lock(pDemodInfo))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}


int DEMOD_ATSC3_Set_PLP (LX_DEMOD_ATSC3_CONFIG_T *pAtsc3ConfigParam)
{
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

	if (NULL == pDemodInfo) {
		DEMOD_RETURN_FAIL(__F__);
	}

	if(NULL == g_demod_hal.ATSC3_Set_PLP)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Set_PLP(pAtsc3ConfigParam))
		DEMOD_RETURN_FAIL(__F__);

	pDemodInfo->setCfgParam.atsc3.plpData[0] = pAtsc3ConfigParam->plpData[0];
	pDemodInfo->setCfgParam.atsc3.plpData[1] = pAtsc3ConfigParam->plpData[1];
	pDemodInfo->setCfgParam.atsc3.plpData[2] = pAtsc3ConfigParam->plpData[2];
	pDemodInfo->setCfgParam.atsc3.plpData[3] = pAtsc3ConfigParam->plpData[3];

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ATSC3_Set_PLP);




int DEMOD_ATSC3_Get_MPLP_Info (LX_DEMOD_ATSC3_MULTI_PLP_ID_T *pAtsc3mPLPInfo, LX_DEMOD_ATSC3_MULTI_PLP_ID_SEL_T plpSel)
{
	if(NULL == g_demod_hal.ATSC3_Get_MPLP_Info)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Get_MPLP_Info(pAtsc3mPLPInfo, plpSel))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ATSC3_Get_MPLP_Info);


int DEMOD_ATSC3_Set_OIFType (LX_DEMOD_ATSC3_OIF_TYPE_T *pAtsc3OifType) // htlim
{
	if(NULL == g_demod_hal.ATSC3_Set_OIFType)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Set_OIFType(pAtsc3OifType))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}
EXPORT_SYMBOL(DEMOD_ATSC3_Set_OIFType);

int DEMOD_ATSC3_Set_MemSconfig(void)
{
	if(NULL == g_demod_hal.ATSC3_Set_MemSconfig)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.ATSC3_Set_MemSconfig())
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}


int DEMOD_ANALOG_Set_ClampingCtrl(UINT8 clampCount, UINT16 stepsize)
{
	DEMOD_WARN("No more support ABB\n");
    return RET_OK;
}

#if 0
#endif


#if 0
#endif

// for demod_fw , demod_ipc , demod_util

int DEMOD_IPC_Enable(int enable)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.IPC_Enable)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.IPC_Enable(enable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Get_UART(BOOLEAN *pStatus)
{
	DEMOD_PRINT("Start\n");
	DEMOD_INFO("chip %x, chip_rev %x\n", lx_chip(), lx_chip_rev());

	if(NULL == g_demod_hal.Get_UART)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_UART(pStatus))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Set_UART(int enable)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.Set_UART)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_UART(enable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Set_UART_Speed(int speed)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.Set_UART_Speed)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_UART_Speed(speed))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Set_UART_HEX(int enable)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.Set_UART_HEX)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_UART_HEX(enable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Get_JTAG(BOOLEAN *pStatus)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.Get_JTAG)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_JTAG(pStatus))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Set_JTAG(int enable)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.Set_JTAG)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_JTAG(enable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_Get_Trace (char * pDbgbuf, int * pDbgidx)
{
	if(NULL == g_demod_hal.Get_Trace)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Get_Trace(pDbgbuf, pDbgidx))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}


int DEMOD_Set_Trace(int enable)
{
	DEMOD_PRINT("Start\n");

	if(NULL == g_demod_hal.Set_Trace)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.Set_Trace(enable))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_API_Status( char * pDbglog, int * pDbgidx)
{
	if(NULL == g_demod_hal.API_Status)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.API_Status(pDbglog,pDbgidx))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_API_Dump( char * pDbglog, int * pDbgidx)
{
	if(NULL == g_demod_hal.API_Dump)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.API_Dump(pDbglog,pDbgidx))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_IPC_Status( char * pDbglog, int * pDbgidx)
{
	if(NULL == g_demod_hal.IPC_Status)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.IPC_Status(pDbglog,pDbgidx))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_IPC_Dump( char * pDbglog, int * pDbgidx)
{
	if(NULL == g_demod_hal.IPC_Dump)
		DEMOD_NOT_SUPPORTED(__F__);

	if(RET_OK != g_demod_hal.IPC_Dump(pDbglog,pDbgidx))
		DEMOD_RETURN_FAIL(__F__);

	return RET_OK;
}

int DEMOD_IPC_Init(void) {
	int err = RET_OK;

	if(NULL == g_demod_hal.IPC_Init)
		DEMOD_NOT_SUPPORTED(__F__);

	err = g_demod_hal.IPC_Init();
	if(RET_OK != err)
		DEMOD_RETURN_FAIL(__F__);

	return err;
}

/*
 * DEMOD FW Recovery
 */

int DEMOD_Retune(LX_DEMOD_OPER_MODE_T reply_opmode) {
	int ret = RET_OK;
	LX_DEMOD_CONFIG_T channelChangeConfig;
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

	LX_DEMOD_INIT_PARAM_T 	mediaChageParams = { .operMode = LX_DEMOD_UNKOWN_OPMODE, };

	DEMOD_NOTI("send NEWTUNE\n");

	if (LX_DEMOD_UNKOWN_OPMODE == reply_opmode) {
		DEMOD_LockDevice();

		//Send event for Tuning task
		g_requestMsg = LX_DEMOD_STOP_REQUEST;
		wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);

		DEMOD_UnlockDevice();
		return RET_OK;
	}

	if ((reply_opmode != pDemodInfo->tranMode) || (reply_opmode != pDemodInfo->operMode)) {
		DEMOD_NOTI("opmode check, req 0x%02x, operMode 0x%02x, tranMode 0x%02x\n", reply_opmode, pDemodInfo->operMode, pDemodInfo->tranMode);
	}

	switch (reply_opmode) {
		case LX_DEMOD_DVBT:
			mediaChageParams.bandWd		= pDemodInfo->setCfgParam.dvbt.channelBW;
			channelChangeConfig.dvbt	= pDemodInfo->setCfgParam.dvbt;
			channelChangeConfig.dvbt2	= pDemodInfo->setCfgParam.dvbt2;
			break;
		case LX_DEMOD_DVBT2:
			mediaChageParams.bandWd		= pDemodInfo->setCfgParam.dvbt2.channelBW;
			channelChangeConfig.dvbt	= pDemodInfo->setCfgParam.dvbt;
			channelChangeConfig.dvbt2	= pDemodInfo->setCfgParam.dvbt2;
			break;
		case LX_DEMOD_ATSC:
			mediaChageParams.bandWd 	= pDemodInfo->setCfgParam.vsb.channelBW;
			channelChangeConfig.vsb		= pDemodInfo->setCfgParam.vsb;
			break;
		case LX_DEMOD_ISDBT:
			mediaChageParams.bandWd		= pDemodInfo->setCfgParam.isdbt.channelBW;
			channelChangeConfig.isdbt	= pDemodInfo->setCfgParam.isdbt;
			break;
		case LX_DEMOD_DTMB:
			mediaChageParams.bandWd 	= pDemodInfo->setCfgParam.dtmb.channelBW;
			channelChangeConfig.dtmb	= pDemodInfo->setCfgParam.dtmb;
			break;
		case LX_DEMOD_DVBC:
			mediaChageParams.bandWd 	= pDemodInfo->setCfgParam.dvbc.channelBW;
			channelChangeConfig.dvbc 	= pDemodInfo->setCfgParam.dvbc;
			break;
		case LX_DEMOD_QAM:
			mediaChageParams.bandWd 	= pDemodInfo->setCfgParam.qam.channelBW;
			channelChangeConfig.qam 	= pDemodInfo->setCfgParam.qam;
			break;
		case LX_DEMOD_DVBS:
			mediaChageParams.bandWd 	= LX_DEMOD_DVBS_NO_OPERATION;
			channelChangeConfig.dvbs	= pDemodInfo->setCfgParam.dvbs;
			break;
		case LX_DEMOD_DVBS2:
			mediaChageParams.bandWd 	= LX_DEMOD_DVBS_NO_OPERATION;
			channelChangeConfig.dvbs2	= pDemodInfo->setCfgParam.dvbs2;
			break;
		case LX_DEMOD_ATSC3:
			mediaChageParams.bandWd 	= LX_DEMOD_BW_6MHZ;
			channelChangeConfig.atsc3	= pDemodInfo->setCfgParam.atsc3;
			break;
		default:
			DEMOD_NOTI("send NEWTUNE skip, unknown opmode req 0x%02X\n", reply_opmode);
			return RET_OK;
	}

	mediaChageParams.operMode 	 = reply_opmode;
	mediaChageParams.symbr 		 = pDemodInfo->symbr;
	mediaChageParams.ifFrq 		 = pDemodInfo->IFFrq;

	channelChangeConfig.operMode = reply_opmode;

	if (LX_DEMOD_UNKOWN_OPMODE != mediaChageParams.operMode) {
		//LX_DEMOD_CONFIG_T ccCfg = pDemodInfo->setCfgParam;

		DEMOD_NOTI("mediaChange operMode 0x%02x\n", mediaChageParams.operMode);
		ret = DEMOD_MediaChange(pDemodInfo, &mediaChageParams);
		if (RET_OK != ret) {
			DEMOD_ERROR("FAIL, DEMOD_MediaChange()\n");
			return RET_ERROR;
		}
		//ret = KHAL_DEMOD_MediaChange(&mediaChageParams);
		//DEMOD_NOTI("KHAL_DEMOD_MediaChange ret %d", ret);

		OS_MsecSleep(100);

		DEMOD_NOTI("channelChange operMode 0x%02x\n", channelChangeConfig.operMode);
		ret = DEMOD_ChannelChange(pDemodInfo, &channelChangeConfig);
		if (RET_OK != ret) {
			DEMOD_ERROR("FAIL, DEMOD_ChannelChange()\n");
			return RET_ERROR;
		}
		//ret = KHAL_DEMOD_ChannelChange(&channelChangeConfig);
		//DEMOD_NOTI("KHAL_DEMOD_ChannelChange ret %d", ret);
	}

	return RET_OK;
}

int DEMOD_FW_Recovery (void)
{
	DEMOD_CTX_T * pDemodInfo;
	DEMOD_DEV_T * pDemodDev;

	LX_DEMOD_OPER_MODE_T opmode;

	int ret = RET_OK;

	pDemodInfo = DEMOD_Get_CTX(0);
	pDemodDev = DEMOD_Get_Device_Data();

	if (FALSE == pDemodDev->apb_access) {
		DEMOD_NOTI("demod not activated, stop");
		return RET_OK;
	}

	DEMOD_LockDevice();
	ret = DEMOD_Get_OperMode (&opmode);
	if (RET_OK != ret) {
		opmode = pDemodInfo->tranMode;
	}

	DEMOD_OperModeReset(pDemodInfo->operMode);

	if (RET_OK == ret)
		DEMOD_Power_Save(TRUE);

	DEMOD_NOTI("opmode 0x%02x, ret %d => %s, mem %d, swt %d\n", opmode, ret, DEMOD_Get_OPER_MODE_Name(opmode), pDemodDev->mem_alloc, pDemodDev->sw_type);

	DEMOD_API_Suspend();

	if (pDemodDev->sw_type & DEMOD_SW_TYPE_ATSC) {
		if (RET_OK != DEMOD_ATSC_SW_Init()) {
			DEMOD_PRINT("FAIL, DEMOD_ATSC_SW_Init() \n");
			DEMOD_RETURN_FAIL(__F__);
		}
	} else if (pDemodDev->sw_type & DEMOD_SW_TYPE_DVB) {
		if (RET_OK != DEMOD_DVB_SW_Init()) {
			DEMOD_PRINT("FAIL, DEMOD_DVB_SW_Init() \n");
			DEMOD_RETURN_FAIL(__F__);
		}
	} else if (pDemodDev->sw_type & DEMOD_SW_TYPE_DTMB) {
		if (RET_OK != DEMOD_DTMB_SW_Init()) {
			DEMOD_PRINT("FAIL, DEMOD_DTMB_SW_Init() \n");
			DEMOD_RETURN_FAIL(__F__);
		}
	}
	DEMOD_UnlockDevice();

	if (!CHECK_DVB_SAT(opmode)) {
		ret = DEMOD_FW_Initialize();
	} else {
		ret = DEMOD_SAT_FW_Initialize();
	}

	if(RET_OK != ret) {
		DEMOD_PRINT("FAIL, DEMOD_FW_Initialize() \n");
		DEMOD_RETURN_FAIL(__F__);
	}

	DEMOD_INFO("try newtune\n");
	DEMOD_Retune(opmode);

	return RET_OK;
}

extern BOOLEAN _gIsFWDn;

int DEMOD_FW_ReInit(int mode)
{
	if(NULL != g_demod_hal.FW_ReInit) {
		/* for O22, M23 */
		if(RET_OK != g_demod_hal.FW_ReInit(mode))
			DEMOD_RETURN_FAIL(__F__);
		return RET_OK;
	}

	switch (mode) {
		case 2: {
			DEMOD_CTX_T *pDemodInfo = DEMOD_Get_CTX(0);
			DEMOD_Retune(pDemodInfo->operMode);
			break;
		}
		case 1: {
			DEMOD_NOTI("try TASK STOP\n");
			DEMOD_LockDevice();
			g_requestMsg = LX_DEMOD_STOP_REQUEST;
			_gIsFWDn = FALSE;
			wake_up_interruptible_all(&g_DEMOD_Tuning_WaitQ);
			DEMOD_UnlockDevice();

			while (LX_DEMOD_TASK_NONE_REQUEST != g_requestMsg) {
				DEMOD_NOTI("wait TASK STOP\n");
				usleep_range(10000, 11000);
			}
			DEMOD_NOTI("finish TASK STOP\n");
			DEMOD_FW_Recovery();
			break;			
		}
		case 0: {
			DEMOD_FW_Recovery();
			break;
		}
	}

	return RET_OK;
}

//// for KHAL interface
int KHAL_DEMOD_Init(void)
{
	int ret = RET_OK;
	LX_DEMOD_INCLK_SEL_T inclk = LX_DEMOD_ARM_SETTING;

	DEMOD_CLR_CTX();

	/* TODO : initialize your module not specific minor device */
	//DEMOD_InitHW();

	DEMOD_TASK_Open();

	if(RET_OK != DEMOD_SetI2C())
	{
		ret = RET_ERROR;
	}

	if(RET_OK != DEMOD_AdcInit())
	{
		ret = RET_ERROR;
	}

	if(RET_OK != DEMOD_SetInclk(&inclk))
	{
		ret = RET_ERROR;
	}

	DEMOD_PRINT("DEMOD_Initialize End\n");

	/* END */
	return 0;
}
EXPORT_SYMBOL(KHAL_DEMOD_Init);

int KHAL_DEMOD_MediaChange(LX_DEMOD_INIT_PARAM_T *pTranMedia)
{
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

	if(NULL == pTranMedia ||NULL == pDemodInfo )
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_MediaChange(pDemodInfo, pTranMedia))
	{
		DEMOD_ERROR("FAIL, DEMOD_MediaChange()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	return RET_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_MediaChange);


int KHAL_DEMOD_ChannelChange(LX_DEMOD_CONFIG_T *pDemodCfg)
{

	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

	if(NULL == pDemodCfg ||NULL == pDemodInfo )
	{
		DEMOD_RETURN_FAIL(__F__);
	}

	if(RET_OK != DEMOD_ChannelChange(pDemodInfo, pDemodCfg))
	{
		DEMOD_ERROR("FAIL, DEMOD_ChannelChange()\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	return RET_OK;
}
EXPORT_SYMBOL(KHAL_DEMOD_ChannelChange);

#if 0
int KHAL_Get_DEMOD_CTX(DEMOD_CTX_T *pDemodInfo)
{
	/*Check signal state with the specified parameters*/
	pDemodInfo = DEMOD_Get_CTX(0);
	if(NULL == pDemodInfo)
	{
		DEMOD_ERROR("FAIL, pDemodInfo is NULL\n");
		DEMOD_RETURN_FAIL(__F__);
	}

	return RET_OK;
}
#endif


int KHAL_Get_DEMOD_Sigstatus(LX_DEMOD_SIGNAL_CTX_T *pSigCtx)
{
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

	DEMOD_DEBUG("Start\n");

	if(pDemodInfo->lockStatus != LX_DEMOD_LOCKED )
	{

		pSigCtx->bSignalValid		= FALSE;
		pSigCtx->packetError	 	= 0xffffffff;
		pSigCtx->ber			= 0xffffffff;
		pSigCtx->agc			= 0;
		pSigCtx->m.mse			= 0xffff;
		pSigCtx->m.bMse			= 0xffff;
		pSigCtx->m.constPwr		= 0xffff;
		pSigCtx->offsetFrq_Hz		= 0;
		pSigCtx->sigQ			= 0;
		pSigCtx->unSNR			= 0;
	}
	else
	{
		pSigCtx->bSignalValid		= pDemodInfo->signalStatus.bSignalValid;
		pSigCtx->packetError		= pDemodInfo->signalStatus.packetError;
		pSigCtx->ber			= pDemodInfo->signalStatus.ber;
		pSigCtx->agc			= pDemodInfo->signalStatus.agc;
		pSigCtx->m.mse			= pDemodInfo->signalStatus.m.mse;
		pSigCtx->m.bMse			= pDemodInfo->signalStatus.m.bMse;
		pSigCtx->m.constPwr		= pDemodInfo->signalStatus.m.constPwr;
		pSigCtx->offsetFrq_Hz		= pDemodInfo->freqOffset;
		pSigCtx->sigQ			= pDemodInfo->signalStatus.sigQ;
		pSigCtx->unSNR			= pDemodInfo->signalStatus.unSNR;

	}

	pSigCtx->operMode 	= pDemodInfo->operMode;
	pSigCtx->rfMode		= pDemodInfo->systemMode;
	pSigCtx->cellID		= pDemodInfo->signalStatus.cellID;

	return RET_OK;
}

EXPORT_SYMBOL(KHAL_Get_DEMOD_Sigstatus);



int KHAL_Get_DEMOD_NotifiedStatus(BOOLEAN *pNotifiedStatus)
{
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

//	DEMOD_PRINT("Start\n");

	if((TRUE == pDemodInfo->bNotifiedLock) || (TRUE == pDemodInfo->bNotifiedUnlock))
	{
		*pNotifiedStatus = TRUE;
		//printk("################################notifiedstatus = TRUE\n");
	}
	else
	{
		*pNotifiedStatus = FALSE;
//		DEMOD_PRINT("notifiedstatus = FALSE\n");
	}

	return RET_OK;
}
EXPORT_SYMBOL(KHAL_Get_DEMOD_NotifiedStatus);

int KHAL_Get_DEMOD_NotifiedLock(LX_DEMOD_LOCK_STATE_T *pNotifiedLock)
{
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

//	DEMOD_PRINT("Start\n");

	if(TRUE == pDemodInfo->bNotifiedLock)
	{
		*pNotifiedLock = LX_DEMOD_LOCKED;
		DEMOD_PRINT("pNotifiedStatus = LX_DEMOD_LOCKED\n");
	}
	else
	{
		*pNotifiedLock = LX_DEMOD_UNLOCKED;
		DEMOD_PRINT("pNotifiedStatus = LX_DEMOD_UNLOCKED\n");
	}

	return RET_OK;
}
EXPORT_SYMBOL(KHAL_Get_DEMOD_NotifiedLock);



int KHAL_Get_DEMOD_ChannelPara(LX_DEMOD_CONFIG_T	*pChannelParams)
{
	int i = 0;
	DEMOD_CTX_T *pDemodInfo;
	pDemodInfo = DEMOD_Get_CTX(0);

	memset(pChannelParams, 0x00, sizeof(LX_DEMOD_CONFIG_T));

	for ( i = 0 ; i < 10 ; i++)
	{
		if (pDemodInfo->bSignalStatusValid)
		{
			DEMOD_PRINT("Signal Status updated with Count : %d\n", i );
			break;
		}
		else
		{
			DEMOD_PRINT("Signal Status updating\n" );
		}
		usleep_range(10000,11000);	/* 10ms ~ 11ms */
	}

	memcpy(pChannelParams,&(pDemodInfo->getCfgParam),sizeof(LX_DEMOD_CONFIG_T));

//	DEMOD_PRINT("[DEMOD]  pDemodInfo->getCfgParam.dvbc.qamMode = 0x%x\n" , pDemodInfo->getCfgParam.dvbc.qamMode);
//	DEMOD_PRINT("[DEMOD]  pChannelParams->dvbc.qamMode = 0x%x\n", pChannelParams->dvbc.qamMode);

	return RET_OK;
}
EXPORT_SYMBOL(KHAL_Get_DEMOD_ChannelPara);

#if 0
#endif
/** @} */

