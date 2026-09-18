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
 *  PWM reg driver file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>

#include "os_util.h"
#include "be_dbg.h"
#include "be_def.h"

#include "be_pwm_hw_m19.h"

#include "../reg/be_reg_pwm_m19.h"

#include "../fwi/ipc_def_m19.h"
#include "ipc_drv.h"
#include "ipc_cmd_header.h"

#include "../../../../core/sys/sys_regs.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PWM_DUTY_MAX_S		255
#define PWM_DUTY_RATIO_MAX_S	100

#define MS_TO_NS(x) ((x) * 1000000L)

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	PWM_ORD_1ST_S  ,
	PWM_ORD_2ND_S  ,
	PWM_ORD_3RD_S  ,
	PWM_ORD_4TH_S  ,
	PWM_ORD_5TH_S  ,
	PWM_ORD_6TH_S  ,
	PWM_ORD_7TH_S  ,
	PWM_ORD_8TH_S  ,
	PWM_ORD_MAX_S
} PWM_ORD_S_T;

typedef enum {
	PWM_FREQ_60HZ_S  ,
	PWM_FREQ_120HZ_S ,
	PWM_FREQ_240HZ_S ,
	PWM_FREQ_480HZ_S ,
	PWM_FREQ_MAX_S
} PWM_FREQ_S_T;

typedef enum {
	PWM_FREE_OFF_S ,
	PWM_FREE_ON_S  ,
	PWM_FREE_MAX_S
} PWM_FREE_S_T;

typedef enum {
	PWM_RES_256_S   ,
	PWM_RES_512_S   ,
	PWM_RES_1024_S  ,
	PWM_RES_MAX_S
} PWM_RES_S_T;

typedef enum {
	PWM_MODE_DUTY_S	,
	PWM_MODE_WIDTH_S	,
	PWM_MODE_MAX_S
} PWM_MODE_S_T;

typedef enum {
	PWM_CTRL_ENB_S ,
	PWM_CTRL_FRQ_S ,
	PWM_CTRL_FRE_S ,
	PWM_CTRL_RES_S ,
	PWM_CTRL_INV_S ,
	PWM_CTRL_MOD_S ,
	PWM_CTRL_POS_S ,
	PWM_CTRL_LOW_S ,
	PWM_CTRL_HIG_S ,
	PWM_CTRL_WDH_S ,
	PWM_CTRL_MSK_S ,
	PWM_CTRL_MAX_S
} PWM_CTRL_TYPE_S_T;

typedef struct {
	BOOLEAN						enable;
	BE_PWM_ADAPT_FREQ_DB_T	freqDb;
} PWM_ADAPT_FREQ_CTRL_S_T;

typedef struct {
	// ctrl0 reg
	UINT32 pwm_en		;
	UINT32 pwm_freq_mode;
	UINT32 pwm_resolution;
	UINT32 pwm_inv		;
	UINT32 pwm_sel		;
	UINT32 pwm_width_falling_pos;
	// ctrl1 reg
	UINT32 pwm_free_width       ;
	// ctrl2 reg
	UINT32 pwm_intr_mask	;
	UINT32 pwm_method	;
	UINT32 pwm_mux	;
	UINT32 pwm_fc_h_disp;
	UINT32 pwm_fc_l_disp;
} PWM_CTRL_S_T;

typedef struct {
	UINT32 pwm_v_f;		// rising count
	UINT32 pwm_v_r;		// falling count
	UINT32 pwm_v_id;	// Duty range ID
	UINT32 pwm_v_we;	// load/write
} PWM_TIMING_S_T;

typedef struct {
	PWM_ADAPT_FREQ_CTRL_S_T adaptFreqCtrl;
	UINT32             unit;
	UINT32             ordr;
	UINT32             pxls;
	UINT32			   mask;
	UINT32			   wdth;
	PWM_CTRL_S_T   ctrl;
	PWM_TIMING_S_T t1st;
	PWM_TIMING_S_T t2nd;
	UINT32             duty;
	UINT32             offs;
	UINT32             freq;
	UINT32			   dutyRatio;
	struct hrtimer		timer;
	BOOLEAN lowPowerModeEn;
} PWM_INFO_S_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern PE_PWM_REG_M19_T gPE_PWM_M19;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static PWM_INFO_S_T gPwmInfo[BE_PWM_MAX];

static UINT32 vSyncFreq = 120; // Default PWM frequency

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PWM_InitCtrl(void);
static int PWM_SetCtrl(UINT32 pwmId, PWM_CTRL_TYPE_S_T ctrId, UINT32 ctrVal);
static int PWM_SetFrequency(UINT32 pwmId, UINT32 freq);
static int PWM_SetDuty(UINT32 pwmId, UINT16 duty, UINT16 offset);
static int PWM_SetTiming(UINT32 pwmId, PWM_ORD_S_T pwmOrd, UINT32 *pR1st, UINT32 *pR2nd, UINT32 *pF1st, UINT32 *pF2nd);
static int PWM_GetTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall);
static int PWM_SetRegCtrl(UINT32 pwmId, BOOLEAN zeroDuty);
static enum hrtimer_restart PWM_TimerCallback_SetDuty(struct hrtimer *timer);
static int _REG_SetPwmCtrl(UINT32 pwmId, BOOLEAN zeroDuty);
static int _REG_SetPwmTiming(UINT32 pwmId);
static int _REG_GetPwmTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall);

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_PWM_HW_M19_Init(void)
{
	int ret = RET_OK;
	BE_PWM_ID_T pwmId;
	static UINT8 init_flag = FALSE;

	do {
		if(init_flag) break;
		ret = PWM_InitCtrl();
		if (ret) break;
		pwmId = BE_PWM1;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_ENB_S, TRUE);
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_FRQ_S, PWM_FREQ_120HZ_S);
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_MOD_S, PWM_MODE_DUTY_S);
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_FRE_S, PWM_FREE_ON_S);
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_RES_S, PWM_RES_1024_S);
		if (ret) break;

		ret = PWM_SetCtrl(pwmId, PWM_CTRL_MSK_S, 0x00);	// mask intr
		if (ret) break;
		ret = PWM_SetCtrl(pwmId, PWM_CTRL_WDH_S, FALSE);	// duty mode
		if (ret) break;

		init_flag = TRUE;
	} while ( 0 );

	return ret;
}

int BE_PWM_HW_M19_SetPwmControl(BE_PWM_CTRL_T *pstParams)
{
	int ret = RET_OK;

	do {
		if(pstParams->port >= BE_PWM_MAX)
		{
			BE_ERROR("PWM port %d is not supported!\n", pstParams->port);
			BREAK_WRONG(pstParams->port);
		}

		// W/A for M+ low power mode
#if 1
		if (pstParams->port < BE_PWM2)
		{
			gPwmInfo[pstParams->port].lowPowerModeEn = pstParams->lowPowerMode;
		}
#endif

		PWM_SetCtrl(pstParams->port, PWM_CTRL_ENB_S, pstParams->enable); // force to high

		if(!pstParams->enable) break;

		switch (pstParams->pwmOutput)
		{
			case BE_PWM_LOW :
				PWM_SetCtrl(pstParams->port, PWM_CTRL_LOW_S, TRUE);
				break;
			case BE_PWM_NORMAL :
				PWM_SetCtrl(pstParams->port, PWM_CTRL_LOW_S, FALSE);
				PWM_SetCtrl(pstParams->port, PWM_CTRL_HIG_S, FALSE);
				PWM_SetCtrl(pstParams->port, PWM_CTRL_INV_S, FALSE);
				break;
			case BE_PWM_HIGH :
				PWM_SetCtrl(pstParams->port, PWM_CTRL_HIG_S, TRUE);
				break;
			case BE_PWM_INVERSION :
				PWM_SetCtrl(pstParams->port, PWM_CTRL_INV_S, TRUE);
				break;
			default :
				BREAK_WRONG(pstParams->pwmOutput);
		}

		PWM_SetCtrl(pstParams->port, PWM_CTRL_FRE_S, (pstParams->pwmMode)?PWM_FREE_OFF_S:PWM_FREE_ON_S);
	} while(0);

	return ret;
}

int BE_PWM_HW_M19_SetPwmAdaptFreqControl(BE_PWM_ADAPT_FREQ_CTRL_T *pstParams)
{
	int ret = RET_OK;
	BOOLEAN freqSet = FALSE;

	do {
		if (pstParams->port >= BE_PWM_MAX)
		{
			BE_ERROR("PWM port %d is not supported!\n", pstParams->port);
			BREAK_WRONG(pstParams->port);
		}

		if ((gPwmInfo[pstParams->port].adaptFreqCtrl.enable == FALSE && pstParams->enable == TRUE)
			|| ((pstParams->enable == TRUE) && ((gPwmInfo[pstParams->port].adaptFreqCtrl.freqDb.freq_48nHz != pstParams->freqDb.freq_48nHz)
												|| (gPwmInfo[pstParams->port].adaptFreqCtrl.freqDb.freq_50nHz != pstParams->freqDb.freq_50nHz)
												|| (gPwmInfo[pstParams->port].adaptFreqCtrl.freqDb.freq_60nHz != pstParams->freqDb.freq_60nHz))))
		{
			freqSet = TRUE;
		}

		gPwmInfo[pstParams->port].adaptFreqCtrl.freqDb = pstParams->freqDb;
		gPwmInfo[pstParams->port].adaptFreqCtrl.enable = pstParams->enable;

		if (freqSet)
		{
			BE_PWM_FREQ_T stParams;

			stParams.port = pstParams->port;
			stParams.frequency = 0; // Use vSyncFreq
			ret = BE_PWM_HW_M19_SetPwmSync(&stParams);
			if(ret) BREAK_WRONG(ret);
		}
	} while(0);

	return ret;
}

int BE_PWM_HW_M19_SetPwmFrequency(BE_PWM_FREQ_T *pstParams)
{
	int ret = RET_OK;
	BE_PWM_ID_T nPort;

	do {
		if(!pstParams) BREAK_WRONG((unsigned int)(uintptr_t)pstParams);
		if(pstParams->port >= BE_PWM_MAX) BREAK_WRONG(pstParams->port);

		nPort = pstParams->port;

		ret = PWM_SetFrequency(nPort, pstParams->frequency);
		if (ret) BREAK_WRONG(ret);

		ret = PWM_SetDuty(nPort, gPwmInfo[nPort].duty, gPwmInfo[nPort].offs);
	} while(0);

	return ret;
}

int BE_PWM_HW_M19_SetPwmDutyCycle(BE_PWM_DUTY_T *pstParams)
{
	int ret = RET_OK;

	do {
		if(!pstParams) BREAK_WRONG((unsigned int)(uintptr_t)pstParams);
		if(pstParams->port >= BE_PWM_MAX) BREAK_WRONG(pstParams->port);
		if(pstParams->duty > PWM_DUTY_MAX_S) BREAK_WRONG(pstParams->duty);
		if(pstParams->offset > PWM_DUTY_MAX_S) BREAK_WRONG(pstParams->offset);

		ret = PWM_SetDuty(pstParams->port, pstParams->duty, pstParams->offset);
		if (ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_PWM_HW_M19_SetPwmDutyRatio(BE_PWM_DUTY_RATIO_T *pstParams)
{
	int ret = RET_OK;
	BE_PWM_ID_T nPort;

	do {
		if(!pstParams) BREAK_WRONG((unsigned int)(uintptr_t)pstParams);
		if(pstParams->port >= BE_PWM_MAX) BREAK_WRONG(pstParams->port);
		if(pstParams->percent > PWM_DUTY_RATIO_MAX_S) BREAK_WRONG(pstParams->percent);

		nPort = pstParams->port;
		
		gPwmInfo[nPort].dutyRatio = pstParams->percent;

		ret = PWM_SetDuty(nPort, gPwmInfo[nPort].duty, gPwmInfo[nPort].offs);
		if (ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_PWM_HW_M19_SetPwmParams(LX_BE_PWM_PARAMS_T *pstParams)
{
	int ret = RET_OK;
	LX_BE_PWM_PARAMS_T pwmParams;
	int i;

	do {
		if(pstParams == NULL) BREAK_WRONG((unsigned int)(uintptr_t)pstParams);
		if (((pstParams->portMask) >> LX_BE_PWM_PORT_MAX) != 0) BREAK_WRONG(pstParams->portMask);

		memcpy((void *)&pwmParams, (void *)pstParams, sizeof(LX_BE_PWM_PARAMS_T));
		
		for(i = 0; i < LX_BE_PWM_PORT_MAX; i++)
		{
			if ((pwmParams.portMask >> i) & 0x01)
			{
				BE_PWM_CTRL_T pwmCtrlParam;
				BE_PWM_ADAPT_FREQ_CTRL_T pwmAdaptFreqCtrlParam;
				BE_PWM_DUTY_T pwmDutyParam;
					
				if(pwmParams.portParams[i].duty > PWM_DUTY_MAX_S) BREAK_WRONG(pwmParams.portParams[i].duty);
				if(pwmParams.portParams[i].offset > PWM_DUTY_MAX_S) BREAK_WRONG(pwmParams.portParams[i].offset);

				if (pwmParams.portParams[i].scanningModeEn
					&& (pwmParams.portParams[i].duty + pwmParams.portParams[i].offset > PWM_DUTY_MAX_S))
				{
					pwmDutyParam.offset = PWM_DUTY_MAX_S - pwmParams.portParams[i].duty;
				}
				else
				{
					pwmDutyParam.offset = pwmParams.portParams[i].offset;
				}
				pwmDutyParam.duty = pwmParams.portParams[i].duty;

				// Update duty/offset value for frequency setting
				gPwmInfo[i].duty = pwmDutyParam.duty;
				gPwmInfo[i].offs = pwmDutyParam.offset;

				pwmCtrlParam.port = i;
				pwmCtrlParam.enable = pwmParams.portParams[i].enable;
				pwmCtrlParam.pwmMode = pwmParams.portParams[i].lockModeEn;
				pwmCtrlParam.lowPowerMode = pwmParams.portParams[i].lowPowerModeEn;
				pwmCtrlParam.pwmOutput = pwmParams.portParams[i].pwmOutput;
				ret = BE_PWM_HW_M19_SetPwmControl(&pwmCtrlParam);
				if(ret) BREAK_WRONG(ret);

				pwmAdaptFreqCtrlParam.port = i;
				pwmAdaptFreqCtrlParam.enable = pwmParams.portParams[i].adaptFreqEn;
				pwmAdaptFreqCtrlParam.freqDb = pwmParams.portParams[i].adaptFreqDb;
				ret = BE_PWM_HW_M19_SetPwmAdaptFreqControl(&pwmAdaptFreqCtrlParam);
				if(ret) BREAK_WRONG(ret);

				if (!pwmParams.portParams[i].adaptFreqEn)
				{
					BE_PWM_FREQ_T pwmFreqParams;

					pwmFreqParams.port = i;
					pwmFreqParams.frequency = pwmParams.portParams[i].frequency;
					ret = BE_PWM_HW_M19_SetPwmFrequency(&pwmFreqParams);
					if(ret) BREAK_WRONG(ret);
				}

				pwmDutyParam.port = i;
				ret = BE_PWM_HW_M19_SetPwmDutyCycle(&pwmDutyParam);
				if(ret) BREAK_WRONG(ret);
			}
		}
		if (ret != RET_OK) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_PWM_HW_M19_GetPwmInfo(BE_EXTERNAL_PWM_T *pstParams)
{
	int ret = RET_OK;
	UINT32 freq_mode = 0;
	UINT32 time_low[4] = { 0 };
	UINT32 time_high[4] = { 0 };
	UINT32 i=0, iteration=0;
	UINT32 duty = 0, duty_sum = 0;
	static UINT16 prev_freq = 0;

	do {
		CHECK_NULL(pstParams);

		if (pstParams->frequency == 0) // Print debug info
		{
			for (i=0; i<BE_PWM_MAX; i++)
			{
				BE_ERROR("PWM Ctrl[%d] : [En:%d][freqMode:%d][freeWidth:%d][freerun:%d][Hi:%d][Lo:%d]\n", i,
							gPwmInfo[i].ctrl.pwm_en,
							gPwmInfo[i].ctrl.pwm_freq_mode,
							gPwmInfo[i].ctrl.pwm_free_width,
							gPwmInfo[i].ctrl.pwm_method,
							gPwmInfo[i].ctrl.pwm_fc_h_disp,
							gPwmInfo[i].ctrl.pwm_fc_l_disp);

				BE_ERROR("PWM Low Power Mode[%d] : [En:%d]\n", i,
							gPwmInfo[i].lowPowerModeEn);

				BE_ERROR("PWM Adaptive Freq. Ctrl[%d] : [En:%d][DB:%d,%d,%d]\n", i,
							gPwmInfo[i].adaptFreqCtrl.enable,
							gPwmInfo[i].adaptFreqCtrl.freqDb.freq_48nHz,
							gPwmInfo[i].adaptFreqCtrl.freqDb.freq_50nHz,
							gPwmInfo[i].adaptFreqCtrl.freqDb.freq_60nHz);

				BE_ERROR("PWM  set[%d] : [duty:%d][offset:%d][freq:%d][dutyRatio:%d]\n\n\r", i,
							gPwmInfo[i].duty,
							gPwmInfo[i].offs,
							gPwmInfo[i].freq,
							gPwmInfo[i].dutyRatio);

				OS_MsecSleep(1);
			}
		}
		else
		{
			switch (pstParams->frequency)
			{
				case 48 :
				case 50 :
				case 60 :
					freq_mode = PWM_FREQ_60HZ_S;
					iteration = 1;
					break;
				case 96 :
				case 100 :
				case 120 :
					freq_mode = PWM_FREQ_120HZ_S;
					iteration = 2;
					break;
				case 192 :
				case 200 :
				case 240 :
					freq_mode = PWM_FREQ_240HZ_S;
					iteration = 4;
					break;
				default :
					freq_mode = PWM_FREQ_120HZ_S;
					iteration = 2;
					break;
			}

			if(prev_freq != pstParams->frequency)
			{
				 ret = PWM_SetCtrl(BE_PWM3, PWM_CTRL_FRQ_S, freq_mode);
				 if(ret) break;
				 ret = PWM_SetRegCtrl(BE_PWM3, FALSE);
				 if(ret) break;
			}
			prev_freq = pstParams->frequency;

			for(i=0;i<iteration;i++)
			{
				PWM_GetTiming(i, &time_low[i], &time_high[i]);
				if(time_low[i] == 0 && time_high[i] == 0)
				{
					BE_DEBUG("%s : low & high are zero  (ord %d)\n", __F__, i);
					pstParams->duty = 0;
					break;
				}
				duty = (time_high[i] * 1023) / (time_low[i] + time_high[i]);
				duty_sum += duty;
				BE_DEBUG("%d : high[%d] low[%d] -> duty[%d]\n", i, time_high[i], time_low[i], duty);
			}
			pstParams->duty = duty_sum/iteration;
			BE_DEBUG("avg duty[%d]\n", duty_sum/iteration);
		}
	} while(0);

	return ret;
}

int BE_PWM_HW_M19_SetPwmSync(BE_PWM_FREQ_T *pstParams)
{
	int ret = RET_OK;
	UINT32 pwmFreq;
	UINT32 prevPwmfreq;
	UINT32 port;
	UINT32 freq;
	UINT32 i;

	do {
		CHECK_NULL(pstParams);

		port = pstParams->port;
		freq = pstParams->frequency;

		if (port < BE_PWM_MAX || freq == 0) // if (Call from IOCTL || Invalid frequency)
		{
			freq = vSyncFreq;
		}
		else // if (Call from ISR && Valid frequency)
		{
			vSyncFreq = freq;
		}

		for(i=(port < BE_PWM_MAX ? port : 0);
			i<(port < BE_PWM_MAX ? port+1 : BE_PWM_MAX); i++)
		{
			if(!gPwmInfo[i].adaptFreqCtrl.enable)
				continue;

			/* u32Frequency가 48/50/60의 공배수(ex.240Hz)가 올 수 없다는 전제가 필요함 */
			if(freq%48 == 0 && gPwmInfo[i].adaptFreqCtrl.freqDb.freq_48nHz)
			{
				pwmFreq = gPwmInfo[i].adaptFreqCtrl.freqDb.freq_48nHz;
			}
			else if(freq%50 == 0 && gPwmInfo[i].adaptFreqCtrl.freqDb.freq_50nHz)
			{
				pwmFreq = gPwmInfo[i].adaptFreqCtrl.freqDb.freq_50nHz;
			}
			else if(freq%60 == 0 && gPwmInfo[i].adaptFreqCtrl.freqDb.freq_60nHz)
			{
				pwmFreq = gPwmInfo[i].adaptFreqCtrl.freqDb.freq_60nHz;
			}
			else
			{
				pwmFreq = freq;
			}

			prevPwmfreq = gPwmInfo[i].freq;

			ret = PWM_SetFrequency(i, pwmFreq);
			if(ret) break;

			if ((gPwmInfo[i].ctrl.pwm_method == PWM_FREE_OFF_S)
				&& (gPwmInfo[i].ordr >= PWM_ORD_2ND_S)
				&& (prevPwmfreq != 0))
			{
				ktime_t timeDelay;

				timeDelay = ktime_set(0, MS_TO_NS((1000*(gPwmInfo[i].ordr+(gPwmInfo[i].ordr+1))/prevPwmfreq) + 1));
				hrtimer_start(&gPwmInfo[i].timer, timeDelay, HRTIMER_MODE_REL);
			}
			else
			{
				ret = PWM_SetDuty(i, gPwmInfo[i].duty, gPwmInfo[i].offs);
				if(ret) break;
			}
		}
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

static int PWM_InitCtrl(void)
{
	int ret = RET_OK;
	UINT32 pwmId;

	for (pwmId=0;pwmId<BE_PWM_MAX;pwmId++) {
		gPwmInfo[pwmId].ctrl.pwm_en				 = FALSE;
		gPwmInfo[pwmId].ctrl.pwm_freq_mode			 = PWM_FREQ_60HZ_S;
		gPwmInfo[pwmId].ctrl.pwm_resolution		 = PWM_RES_1024_S;
		gPwmInfo[pwmId].ctrl.pwm_inv				 = FALSE;
		gPwmInfo[pwmId].ctrl.pwm_sel				 = PWM_MODE_DUTY_S;
		gPwmInfo[pwmId].ctrl.pwm_width_falling_pos  = 0;
		gPwmInfo[pwmId].ctrl.pwm_method			 = PWM_FREE_OFF_S;
		gPwmInfo[pwmId].ctrl.pwm_fc_h_disp			 = FALSE;
		gPwmInfo[pwmId].ctrl.pwm_fc_l_disp			 = FALSE;
		gPwmInfo[pwmId].wdth						 = 0;
		gPwmInfo[pwmId].mask						 = 0xff;
		gPwmInfo[pwmId].unit						 = 2417;
		gPwmInfo[pwmId].duty					= 0;
		gPwmInfo[pwmId].freq					= 0;
		gPwmInfo[pwmId].dutyRatio				= PWM_DUTY_RATIO_MAX_S;
		gPwmInfo[pwmId].adaptFreqCtrl.enable		= FALSE;
		gPwmInfo[pwmId].adaptFreqCtrl.freqDb.freq_48nHz= 0;
		gPwmInfo[pwmId].adaptFreqCtrl.freqDb.freq_50nHz= 0;
		gPwmInfo[pwmId].adaptFreqCtrl.freqDb.freq_60nHz= 0;

		hrtimer_init(&gPwmInfo[pwmId].timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
		gPwmInfo[pwmId].timer.function = &PWM_TimerCallback_SetDuty;
	}

	return ret;
}

static int PWM_SetCtrl(UINT32 pwmId, PWM_CTRL_TYPE_S_T ctrId, UINT32 ctrVal)
{
	int ret = RET_OK;

	switch (ctrId) {
		case PWM_CTRL_ENB_S :
			gPwmInfo[pwmId].ctrl.pwm_en				= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_FRQ_S :
			gPwmInfo[pwmId].ctrl.pwm_freq_mode			= ctrVal & 0x3;
			break;
		case PWM_CTRL_FRE_S :
			gPwmInfo[pwmId].ctrl.pwm_method			= ctrVal & 0x1;
			break;
		case PWM_CTRL_RES_S :
			gPwmInfo[pwmId].ctrl.pwm_resolution		= ctrVal & 0x3;
			break;
		case PWM_CTRL_INV_S :
			gPwmInfo[pwmId].ctrl.pwm_inv				= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_MOD_S :
			gPwmInfo[pwmId].ctrl.pwm_sel				= ctrVal;
			break;
		case PWM_CTRL_POS_S :
			gPwmInfo[pwmId].ctrl.pwm_width_falling_pos = ctrVal & 0x3FFFFF;
			break;
		case PWM_CTRL_LOW_S :
			gPwmInfo[pwmId].ctrl.pwm_fc_l_disp			= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_HIG_S :
			gPwmInfo[pwmId].ctrl.pwm_fc_h_disp			= ctrVal?TRUE:FALSE;
			break;
		case PWM_CTRL_WDH_S :
			gPwmInfo[pwmId].wdth						= ctrVal;
			break;
		case PWM_CTRL_MSK_S :
			gPwmInfo[pwmId].mask						= ctrVal;
			break;
		default :
			break;
	}

	return ret;
}

static int PWM_SetFrequency(UINT32 pwmId, UINT32 freq)
{
	int ret = RET_OK;

	if(freq == 0) return RET_INVALID_PARAMS;

	if (freq > 24000) // For PWM high frequency
	{
		gPwmInfo[pwmId].unit = 256;
		gPwmInfo[pwmId].ctrl.pwm_resolution = PWM_RES_256_S;
	}
	else
	{
		gPwmInfo[pwmId].unit = 1024;
		gPwmInfo[pwmId].ctrl.pwm_resolution = PWM_RES_1024_S;
	}
	gPwmInfo[pwmId].freq = freq;

	if (1) // Check clock setting
	{
		UINT32 regField;

		CTOP_CTRL_M19Ax_RdFL(DPE_SYN, crg_dpe01);
		regField = CTOP_CTRL_M19Ax_RdFd(DPE_SYN, crg_dpe01, tcon_pix2_clk_sel);

		if (regField == 0x0) // 4k 120Hz (pix2_clk : 594MHz)
		{
			freq = freq/2;
		}
		else if (regField == 0x2) // 2k 120Hz (pix2_clk : 148.5MHz)
		{	
			freq = freq*2;
		}
		else if (regField == 0x3) // 2k 60Hz (pix2_clk : 74.25MHz)
		{
			freq = freq*4;
		}
	}

	if( gPwmInfo[pwmId].ctrl.pwm_method == PWM_FREE_OFF_S ) // locking mode
	{
		/*
		 * h      = hactive + hsync + h_bp + h_fp
		 * v      = vactive + vsync + v_bp + v_fp
		 * pixels = h * v
		 *
		 * result ->
		 * 60_h   = 1920    + 44    + 148  + 88   = 2200
		 * 60_v   = 1080    +  5    + 36   + 4    = 1125
		 *    h*v = 2475000
		 * 50_h   = 1920    + 44    + 148  + 88   = 2200
		 * 50_v   = 1080    +  5    + 36   + 229  = 1350
		 *    h*v = 2970000
		 * 48_h   = 1920    + 44    + 148  + 638  = 2750
		 * 48_v   = 1080    +  5    + 36   + 4    = 1125
		 *    h*v = 3093750
		 *
		 *    for UD (3820x2160 30p,25p,24p)
		 * 30_h   = 1920    + 44    + 88   + 72   = 2124
		 * 30_v   = 2160    + 148   + 10   + 8    = 2326
		 *    h*v = 4940424
		 * 25_h   = 1920    + 44    + 88   + 72   = 2124
		 * 25_v   = 2160    + 148   + 10   + 458  = 2776
		 *    h*v = 5896224
		 * 24_h   = 1920    + 44    + 638  + 72   = 2674
		 * 24_v   = 2160    + 148   + 10   + 8    = 2326
		 *    h*v = 6219724

		 */
		#define PWM_PIXELS_60HZ	2475000*2
		#define PWM_PIXELS_50HZ	2970000*2
		#define PWM_PIXELS_48HZ	3093750*2
		#define PWM_PIXELS_30HZ 	4940424*2
		#define PWM_PIXELS_25HZ 	5896224*2
		#define PWM_PIXELS_24HZ 	6219724*2

		switch ( freq )
		{
			case 384 :
			case 400 :
			case 480 :
				gPwmInfo[pwmId].ordr				  = PWM_ORD_8TH_S;
				gPwmInfo[pwmId].ctrl.pwm_method	  = FALSE;
				gPwmInfo[pwmId].ctrl.pwm_freq_mode = 3;
				if( freq == 384) 		gPwmInfo[pwmId].pxls = PWM_PIXELS_48HZ >> 3;
				else if(freq == 400) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_50HZ >> 3;
				else if(freq == 480) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_60HZ >> 3;
				break;
			case 192 :
			case 200 :
			case 240 :
				gPwmInfo[pwmId].ordr				  = PWM_ORD_4TH_S;
				gPwmInfo[pwmId].ctrl.pwm_method	  = FALSE;
				gPwmInfo[pwmId].ctrl.pwm_freq_mode = 2;
				if( freq == 192) 		gPwmInfo[pwmId].pxls = PWM_PIXELS_48HZ >> 2;
				else if(freq == 200) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_50HZ >> 2;
				else if(freq == 240) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_60HZ >> 2;
				break;
			case 96 :
			case 100 :
			case 120 :
				gPwmInfo[pwmId].ordr				  = PWM_ORD_2ND_S;
				gPwmInfo[pwmId].ctrl.pwm_method	  = FALSE;
				gPwmInfo[pwmId].ctrl.pwm_freq_mode = 1;
				if( freq == 96) 		gPwmInfo[pwmId].pxls = PWM_PIXELS_48HZ >> 1;
				else if(freq == 100) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_50HZ >> 1;
				else if(freq == 120) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_60HZ >> 1;
				break;
			case 48 :
			case 50 :
			case 60 :
				gPwmInfo[pwmId].ordr				  = PWM_ORD_1ST_S;
				gPwmInfo[pwmId].ctrl.pwm_method	  = FALSE;
				gPwmInfo[pwmId].ctrl.pwm_freq_mode = 0;
				if( freq == 48) 		gPwmInfo[pwmId].pxls = PWM_PIXELS_48HZ >> 0;
				else if(freq == 50) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_50HZ >> 0;
				else if(freq == 60) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_60HZ >> 0;
				break;
			case 24 :
			case 25 :
			case 30 :
				gPwmInfo[pwmId].ordr               = PWM_ORD_1ST_S;
				gPwmInfo[pwmId].ctrl.pwm_method    = TRUE;
				gPwmInfo[pwmId].ctrl.pwm_freq_mode = 0;
				if( freq == 24) 		gPwmInfo[pwmId].pxls = PWM_PIXELS_24HZ >> 0;
				else if(freq == 25) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_25HZ >> 0;
				else if(freq == 30) 	gPwmInfo[pwmId].pxls = PWM_PIXELS_30HZ >> 0;
				break;
			case 180 :
			case 160 :
			default :
				gPwmInfo[pwmId].ordr				  = PWM_ORD_1ST_S;
				gPwmInfo[pwmId].pxls				  = (2475000*2) * 60 / freq;
				gPwmInfo[pwmId].ctrl.pwm_free_width= (2475000*2) * 60 / freq;
				gPwmInfo[pwmId].ctrl.pwm_method	  = TRUE;
				gPwmInfo[pwmId].ctrl.pwm_freq_mode = 0;
				break;
		}
	}
	else	// freeeun mode
	{
		gPwmInfo[pwmId].ordr				   = PWM_ORD_1ST_S;
		gPwmInfo[pwmId].pxls				   = (2475000*2) * 60 / freq;
		gPwmInfo[pwmId].ctrl.pwm_free_width = (2475000*2) * 60 / freq;
		gPwmInfo[pwmId].ctrl.pwm_method	   = TRUE;
		gPwmInfo[pwmId].ctrl.pwm_freq_mode  = 0;
	}

	return ret;
}

static int PWM_SetDuty(UINT32 pwmId, UINT16 duty, UINT16 offset)
{
	int ret = RET_OK;
	UINT32 i;
	UINT32 ordr;
	UINT32 offs;
	UINT32 high;
	UINT32 falt;
	UINT32 unit_pixel;

	gPwmInfo[pwmId].duty = duty;
	gPwmInfo[pwmId].offs = offset;

	duty = (duty * gPwmInfo[pwmId].dutyRatio)/PWM_DUTY_RATIO_MAX_S;

	unit_pixel = gPwmInfo[pwmId].pxls / gPwmInfo[pwmId].unit;
	ordr	   = gPwmInfo[pwmId].ordr;

	if((offset + duty) > PWM_DUTY_MAX_S)
	{
		duty = PWM_DUTY_MAX_S - offset;
	}

	offs = (unit_pixel * offset)/PWM_DUTY_MAX_S;
	high = (unit_pixel * duty)/PWM_DUTY_MAX_S;
	falt = offs + high;

	// W/A for M+ low power mode
	if (gPwmInfo[pwmId].lowPowerModeEn)
	{
		IPC_SET_DEFAULT_PARAM(BE_IPC_LED_PWM_T, stHwParams);
		
		stHwParams.uPwmPort	= pwmId;
		stHwParams.bLowPowerModeEn = gPwmInfo[pwmId].lowPowerModeEn;
		stHwParams.uPwmCtrlParam = gPwmInfo[pwmId].ctrl.pwm_free_width;
		stHwParams.uPwmDutyParams = (offset << 16) | duty;

		/* Send command  to MCU via IPC & Check result */
		ret = BE_KIPC_SetData(DPPB_PACK_CMD(BE_LED_SET_PWM), &stHwParams, sizeof(BE_IPC_LED_PWM_T));
		if (ret)
		{
			BE_PRINT("[%s][WARN] IPC error!\n\r", __F__);
		}
		
		PWM_SetRegCtrl(pwmId, offs == falt ? TRUE : FALSE); /* In case of zero duty, force to low PWM signal. */
		
		return RET_OK;
	}

	for(i=PWM_ORD_1ST_S; i<ordr+1; i++)
	{
		BE_DEBUG("Port[%d] : ordr[%d] -  unit_pixel[%d] offs[%d] falt[%d] high[%d] \n", pwmId, i, unit_pixel, offs, falt, high);

		ret = PWM_SetTiming(pwmId, i, &offs, &offs, &falt, &falt);
		if(ret) break;
	}

	// Set invalid params for the other IDs - If not, it may give affects to PWM waveform at frequency change
	if (ordr >= PWM_ORD_2ND_S)
	{
		UINT32 invalid_offs = unit_pixel+1;
		UINT32 invalid_falt = 0;

		for(i=ordr+1; i<16; i++)
		{
			ret = PWM_SetTiming(pwmId, i, &invalid_offs, &invalid_offs, &invalid_falt, &invalid_falt);
			if(ret) break;
		}
	}

	ret = PWM_SetRegCtrl(pwmId, offs == falt ? TRUE : FALSE); /* In case of zero duty, force to low PWM signal. */

	return ret;
}

static int PWM_SetTiming(UINT32 pwmId, PWM_ORD_S_T pwmOrd, UINT32 *pR1st, UINT32 *pR2nd, UINT32 *pF1st, UINT32 *pF2nd)
{
	PWM_TIMING_S_T t1st;
	PWM_TIMING_S_T t2nd;

	t1st = gPwmInfo[pwmId].t1st;
	t2nd = gPwmInfo[pwmId].t2nd;
	t1st.pwm_v_id = pwmOrd & 0xf;
	t2nd.pwm_v_id = pwmOrd & 0xf;
	t1st.pwm_v_we = TRUE;
	t2nd.pwm_v_we = TRUE;
	do {
		if (pR1st) t1st.pwm_v_r = *pR1st;
		if (pR2nd) t2nd.pwm_v_r = *pR2nd;
		else if (pR1st) t2nd.pwm_v_r = *pR1st;

		if (pF1st) t1st.pwm_v_f = *pF1st;
		if (pF2nd) t2nd.pwm_v_f = *pF2nd;
		else if (pF1st) t2nd.pwm_v_f = *pF1st;
	} while ( 0 );
	gPwmInfo[pwmId].t1st = t1st;
	gPwmInfo[pwmId].t2nd = t2nd;

	return _REG_SetPwmTiming(pwmId);
}

static int PWM_GetTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall)
{
	int ret = RET_OK;

	ret = _REG_GetPwmTiming(freq_mode, pRising, pFall);

	return ret;
}

static int PWM_SetRegCtrl(UINT32 pwmId, BOOLEAN zeroDuty)
{
	int ret = RET_OK;

	ret = _REG_SetPwmCtrl(pwmId, zeroDuty);

	return ret;
}

static enum hrtimer_restart PWM_TimerCallback_SetDuty(struct hrtimer *timer)
{
	UINT32 pwmId;

	for (pwmId=0; pwmId<BE_PWM_MAX; pwmId++)
	{
		if (&gPwmInfo[pwmId].timer == timer) break;
	}

	if (pwmId != BE_PWM_MAX)
	{
		PWM_SetDuty(pwmId, gPwmInfo[pwmId].duty, gPwmInfo[pwmId].offs);
	}

	return HRTIMER_NORESTART;
}

static int _REG_SetPwmCtrl(UINT32 pwmId, BOOLEAN zeroDuty)
{
	int ret = RET_OK;

	switch (pwmId) {
		case 0 :
			PE_PWM_M19_RdFL(pe_pwm0_ctrl0);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_RdFL(pe_pwm0_ctrl1);
			}
			PE_PWM_M19_RdFL(pe_pwm0_ctrl2);
			PE_PWM_M19_Wr01(pe_pwm0_ctrl0, pwm0_en, gPwmInfo[pwmId].ctrl.pwm_en);
			PE_PWM_M19_Wr01(pe_pwm0_ctrl0, pwm0_freq_mode, gPwmInfo[pwmId].ctrl.pwm_freq_mode);
			PE_PWM_M19_Wr01(pe_pwm0_ctrl0, pwm0_resolution, gPwmInfo[pwmId].ctrl.pwm_resolution);
			PE_PWM_M19_Wr01(pe_pwm0_ctrl0, pwm0_inv, gPwmInfo[pwmId].ctrl.pwm_inv);
			PE_PWM_M19_Wr01(pe_pwm0_ctrl0, pwm0_sel, gPwmInfo[pwmId].ctrl.pwm_sel);
			PE_PWM_M19_Wr01(pe_pwm0_ctrl0, pwm0_width_falling_pos, gPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_Wr01(pe_pwm0_ctrl1, pwm0_free_width, gPwmInfo[pwmId].ctrl.pwm_free_width);
			}
			PE_PWM_M19_Wr01(pe_pwm0_ctrl2, pwm0_method, gPwmInfo[pwmId].ctrl.pwm_method);
			PE_PWM_M19_Wr01(pe_pwm0_ctrl2, pwm0_fc_h_disp, gPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			if(zeroDuty && (!gPwmInfo[pwmId].ctrl.pwm_fc_h_disp))
			{
				PE_PWM_M19_Wr01(pe_pwm0_ctrl2, pwm0_fc_l_disp, 1);
			}
			else
			{
				PE_PWM_M19_Wr01(pe_pwm0_ctrl2, pwm0_fc_l_disp, gPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			}
			PE_PWM_M19_WrFL(pe_pwm0_ctrl0);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_WrFL(pe_pwm0_ctrl1);
			}
			PE_PWM_M19_WrFL(pe_pwm0_ctrl2);
			break;
		case 1 :
			PE_PWM_M19_RdFL(pe_pwm1_ctrl0);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_RdFL(pe_pwm1_ctrl1);
			}
			PE_PWM_M19_RdFL(pe_pwm1_ctrl2);
			PE_PWM_M19_Wr01(pe_pwm1_ctrl0, pwm1_en, gPwmInfo[pwmId].ctrl.pwm_en);
			PE_PWM_M19_Wr01(pe_pwm1_ctrl0, pwm1_freq_mode, gPwmInfo[pwmId].ctrl.pwm_freq_mode);
			PE_PWM_M19_Wr01(pe_pwm1_ctrl0, pwm1_resolution, gPwmInfo[pwmId].ctrl.pwm_resolution);
			PE_PWM_M19_Wr01(pe_pwm1_ctrl0, pwm1_inv, gPwmInfo[pwmId].ctrl.pwm_inv);
			PE_PWM_M19_Wr01(pe_pwm1_ctrl0, pwm1_sel, gPwmInfo[pwmId].ctrl.pwm_sel);
			PE_PWM_M19_Wr01(pe_pwm1_ctrl0, pwm1_width_falling_pos, gPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_Wr01(pe_pwm1_ctrl1, pwm1_free_width, gPwmInfo[pwmId].ctrl.pwm_free_width);
			}
			PE_PWM_M19_Wr01(pe_pwm1_ctrl2, pwm1_method, gPwmInfo[pwmId].ctrl.pwm_method);
			PE_PWM_M19_Wr01(pe_pwm1_ctrl2, pwm1_fc_h_disp, gPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			if(zeroDuty && (!gPwmInfo[pwmId].ctrl.pwm_fc_h_disp))
			{
				PE_PWM_M19_Wr01(pe_pwm1_ctrl2, pwm1_fc_l_disp, 1);
			}
			else
			{
				PE_PWM_M19_Wr01(pe_pwm1_ctrl2, pwm1_fc_l_disp, gPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			}
			PE_PWM_M19_WrFL(pe_pwm1_ctrl0);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_WrFL(pe_pwm1_ctrl1);
			}
			PE_PWM_M19_WrFL(pe_pwm1_ctrl2);
			break;
		case 2 :
			PE_PWM_M19_RdFL(pe_pwm2_ctrl0);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_RdFL(pe_pwm2_ctrl1);
			}
			PE_PWM_M19_RdFL(pe_pwm2_ctrl2);
			PE_PWM_M19_Wr01(pe_pwm2_ctrl0, pwm2_en, gPwmInfo[pwmId].ctrl.pwm_en);
			PE_PWM_M19_Wr01(pe_pwm2_ctrl0, pwm2_freq_mode, gPwmInfo[pwmId].ctrl.pwm_freq_mode);
			PE_PWM_M19_Wr01(pe_pwm2_ctrl0, pwm2_resolution, gPwmInfo[pwmId].ctrl.pwm_resolution);
			PE_PWM_M19_Wr01(pe_pwm2_ctrl0, pwm2_inv, gPwmInfo[pwmId].ctrl.pwm_inv);
			PE_PWM_M19_Wr01(pe_pwm2_ctrl0, pwm2_sel, gPwmInfo[pwmId].ctrl.pwm_sel);
			PE_PWM_M19_Wr01(pe_pwm2_ctrl0, pwm2_width_falling_pos, gPwmInfo[pwmId].ctrl.pwm_width_falling_pos);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_Wr01(pe_pwm2_ctrl1, pwm2_free_width, gPwmInfo[pwmId].ctrl.pwm_free_width);
			}
			PE_PWM_M19_Wr01(pe_pwm2_ctrl2, pwm2_method, gPwmInfo[pwmId].ctrl.pwm_method);
			PE_PWM_M19_Wr01(pe_pwm2_ctrl2, pwm2_fc_h_disp, gPwmInfo[pwmId].ctrl.pwm_fc_h_disp);
			if(zeroDuty && (!gPwmInfo[pwmId].ctrl.pwm_fc_h_disp))
			{
				PE_PWM_M19_Wr01(pe_pwm2_ctrl2, pwm2_fc_l_disp, 1);
			}
			else
			{
				PE_PWM_M19_Wr01(pe_pwm2_ctrl2, pwm2_fc_l_disp, gPwmInfo[pwmId].ctrl.pwm_fc_l_disp);
			}
			PE_PWM_M19_WrFL(pe_pwm2_ctrl0);
			if (!gPwmInfo[pwmId].lowPowerModeEn) // W/A for M+ low power mode
			{
				PE_PWM_M19_WrFL(pe_pwm2_ctrl1);
			}
			PE_PWM_M19_WrFL(pe_pwm2_ctrl2);
			break;

		case 3 :
			PE_PWM_M19_RdFL(pe_pwm3_ctrl0);
			PE_PWM_M19_Wr01(pe_pwm3_ctrl0, pwm3_en, gPwmInfo[pwmId].ctrl.pwm_en);
			PE_PWM_M19_Wr01(pe_pwm3_ctrl0, pwm3_freq_mode, gPwmInfo[pwmId].ctrl.pwm_freq_mode);
			PE_PWM_M19_WrFL(pe_pwm3_ctrl0);
			break;
		default :
			break;
	}

	return ret;
}

static int _REG_SetPwmTiming(UINT32 pwmId)
{
	int ret = RET_OK;

	switch (pwmId) {
		case 0 :
			PE_PWM_M19_RdFL(pe_pwm_v_load_write);
			PE_PWM_M19_RdFL(pe_pwm0_v_r);
			PE_PWM_M19_RdFL(pe_pwm0_v_f);
			PE_PWM_M19_RdFL(pe_pwm0_v_sub_r);
			PE_PWM_M19_RdFL(pe_pwm0_v_sub_f);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm0_v_we, gPwmInfo[pwmId].t1st.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm0_v_r, pwm0_v_r, gPwmInfo[pwmId].t1st.pwm_v_r);
			PE_PWM_M19_Wr01(pe_pwm0_v_r, pwm0_v_r_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm0_v_f, pwm0_v_f, gPwmInfo[pwmId].t1st.pwm_v_f);
			PE_PWM_M19_Wr01(pe_pwm0_v_f, pwm0_v_f_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm0_v_sub_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm0_v_sub_r, pwm0_v_sub, gPwmInfo[pwmId].t2nd.pwm_v_r);
			PE_PWM_M19_Wr01(pe_pwm0_v_sub_r, pwm0_v_sub_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm0_v_sub_f_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm0_v_sub_f, pwm0_v_sub_f, gPwmInfo[pwmId].t2nd.pwm_v_f);
			PE_PWM_M19_Wr01(pe_pwm0_v_sub_f, pwm0_v_sub_f_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			PE_PWM_M19_WrFL(pe_pwm_v_load_write);
			PE_PWM_M19_WrFL(pe_pwm0_v_r);
			PE_PWM_M19_WrFL(pe_pwm0_v_f);
			PE_PWM_M19_WrFL(pe_pwm0_v_sub_r);
			PE_PWM_M19_WrFL(pe_pwm0_v_sub_f);
			break;
		case 1 :
			PE_PWM_M19_RdFL(pe_pwm_v_load_write);
			PE_PWM_M19_RdFL(pe_pwm1_v_r);
			PE_PWM_M19_RdFL(pe_pwm1_v_f);
			PE_PWM_M19_RdFL(pe_pwm1_v_sub_r);
			PE_PWM_M19_RdFL(pe_pwm1_v_sub_f);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm1_v_we, gPwmInfo[pwmId].t1st.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm1_v_r, pwm1_v_r, gPwmInfo[pwmId].t1st.pwm_v_r);
			PE_PWM_M19_Wr01(pe_pwm1_v_r, pwm1_v_r_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm1_v_f, pwm1_v_f, gPwmInfo[pwmId].t1st.pwm_v_f);
			PE_PWM_M19_Wr01(pe_pwm1_v_f, pwm1_v_f_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm1_v_sub_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm1_v_sub_r, pwm1_v_sub, gPwmInfo[pwmId].t2nd.pwm_v_r);
			PE_PWM_M19_Wr01(pe_pwm1_v_sub_r, pwm1_v_sub_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm1_v_sub_f_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm1_v_sub_f, pwm1_v_sub_f, gPwmInfo[pwmId].t2nd.pwm_v_f);
			PE_PWM_M19_Wr01(pe_pwm1_v_sub_f, pwm1_v_sub_f_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			PE_PWM_M19_WrFL(pe_pwm_v_load_write);
			PE_PWM_M19_WrFL(pe_pwm1_v_r);
			PE_PWM_M19_WrFL(pe_pwm1_v_f);
			PE_PWM_M19_WrFL(pe_pwm1_v_sub_r);
			PE_PWM_M19_WrFL(pe_pwm1_v_sub_f);
			break;
		case 2 :
			PE_PWM_M19_RdFL(pe_pwm_v_load_write);
			PE_PWM_M19_RdFL(pe_pwm2_v_r);
			PE_PWM_M19_RdFL(pe_pwm2_v_f);
			PE_PWM_M19_RdFL(pe_pwm2_v_sub_r);
			PE_PWM_M19_RdFL(pe_pwm2_v_sub_f);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm2_v_we, gPwmInfo[pwmId].t1st.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm2_v_r, pwm2_v_r, gPwmInfo[pwmId].t1st.pwm_v_r);
			PE_PWM_M19_Wr01(pe_pwm2_v_r, pwm2_v_r_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm2_v_f, pwm2_v_f, gPwmInfo[pwmId].t1st.pwm_v_f);
			PE_PWM_M19_Wr01(pe_pwm2_v_f, pwm2_v_f_id, gPwmInfo[pwmId].t1st.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm2_v_sub_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm2_v_sub_r, pwm2_v_sub, gPwmInfo[pwmId].t2nd.pwm_v_r);
			PE_PWM_M19_Wr01(pe_pwm2_v_sub_r, pwm2_v_sub_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			PE_PWM_M19_Wr01(pe_pwm_v_load_write, pwm2_v_sub_f_we, gPwmInfo[pwmId].t2nd.pwm_v_we);
			PE_PWM_M19_Wr01(pe_pwm2_v_sub_f, pwm2_v_sub_f, gPwmInfo[pwmId].t2nd.pwm_v_f);
			PE_PWM_M19_Wr01(pe_pwm2_v_sub_f, pwm2_v_sub_f_id, gPwmInfo[pwmId].t2nd.pwm_v_id);
			PE_PWM_M19_WrFL(pe_pwm_v_load_write);
			PE_PWM_M19_WrFL(pe_pwm2_v_r);
			PE_PWM_M19_WrFL(pe_pwm2_v_f);
			PE_PWM_M19_WrFL(pe_pwm2_v_sub_r);
			PE_PWM_M19_WrFL(pe_pwm2_v_sub_f);
			break;
		default :
			break;
	}

	return ret;
}

static int _REG_GetPwmTiming(UINT32 freq_mode, UINT32 *pRising, UINT32 *pFall)
{
	int ret = RET_OK;

	do {
		switch (freq_mode)
		{
			case 0 :
				PE_PWM_M19_RdFL(pe_pwm3_0_low);
				PE_PWM_M19_RdFL(pe_pwm3_0_high);
				PE_PWM_M19_Rd01(pe_pwm3_0_low, pwm3_0_low, *pRising);
				PE_PWM_M19_Rd01(pe_pwm3_0_high, pwm3_0_high, *pFall);
				break;
			case 1 :
				PE_PWM_M19_RdFL(pe_pwm3_1_low);
				PE_PWM_M19_RdFL(pe_pwm3_1_high);
				PE_PWM_M19_Rd01(pe_pwm3_1_low, pwm3_1_low, *pRising);
				PE_PWM_M19_Rd01(pe_pwm3_1_high, pwm3_1_high, *pFall);
				break;
			case 2 :
				PE_PWM_M19_RdFL(pe_pwm3_2_low);
				PE_PWM_M19_RdFL(pe_pwm3_2_high);
				PE_PWM_M19_Rd01(pe_pwm3_2_low, pwm3_2_low, *pRising);
				PE_PWM_M19_Rd01(pe_pwm3_2_high, pwm3_2_high, *pFall);
				break;
			case 3 :
				PE_PWM_M19_RdFL(pe_pwm3_3_low);
				PE_PWM_M19_RdFL(pe_pwm3_3_high);
				PE_PWM_M19_Rd01(pe_pwm3_3_low, pwm3_3_low, *pRising);
				PE_PWM_M19_Rd01(pe_pwm3_3_high, pwm3_3_high, *pFall);
				break;
			default :
				BREAK_WRONG(freq_mode);
		}
	} while(0);

	return ret;
}

int BE_PWM_HW_M19_ProcHandler(BE_PWM_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int	i;

	switch(proc_id)
	{
		case BE_PWM_PROC_ID_DETAIL_INFO:
		{
			for (i=0;i<BE_PWM_MAX;i++)
			{
				seq_printf(m, "pwm%d.ctrl.enable: %s (0x%x)\n", i, (gPwmInfo[i].ctrl.pwm_en)? "on":"off", gPwmInfo[i].ctrl.pwm_en);

				if (gPwmInfo[i].ctrl.pwm_en)
				{
					seq_printf(m, "pwm%d.ctrl.freq_mode: 0x%x\n", i, gPwmInfo[i].ctrl.pwm_freq_mode);
					seq_printf(m, "pwm%d.ctrl.resolution: 0x%x\n", i, gPwmInfo[i].ctrl.pwm_resolution);
					seq_printf(m, "pwm%d.ctrl.inv: 0x%x\n", i, gPwmInfo[i].ctrl.pwm_inv);
					seq_printf(m, "pwm%d.ctrl.sel: 0x%x\n", i, gPwmInfo[i].ctrl.pwm_sel);
					seq_printf(m, "pwm%d.ctrl.width_falling_pos: 0x%x\n", i, gPwmInfo[i].ctrl.pwm_width_falling_pos);
					seq_printf(m, "pwm%d.ctrl.method: 0x%x\n", i, gPwmInfo[i].ctrl.pwm_method);
					seq_printf(m, "pwm%d.ctrl.fc_h_disp: 0x%x\n", i, gPwmInfo[i].ctrl.pwm_fc_h_disp);
					seq_printf(m, "pwm%d.ctrl.fc_l_disp: 0x%x\n", i, gPwmInfo[i].ctrl.pwm_fc_l_disp);
					seq_printf(m, "pwm%d.width: 0x%x\n", i, gPwmInfo[i].wdth);
					seq_printf(m, "pwm%d.mask: 0x%x\n", i, gPwmInfo[i].mask);
					seq_printf(m, "pwm%d.unit: 0x%x\n", i, gPwmInfo[i].unit);
					seq_printf(m, "pwm%d.duty: 0x%x\n", i, gPwmInfo[i].duty);
					seq_printf(m, "pwm%d.freq: 0x%x\n", i, gPwmInfo[i].freq);
					seq_printf(m, "pwm%d.dutyRatio: 0x%x\n", i, gPwmInfo[i].dutyRatio);
					seq_printf(m, "pwm%d.adapt_freq_ctrl.enable: 0x%x\n", i, gPwmInfo[i].adaptFreqCtrl.enable);
					seq_printf(m, "pwm%d.adapt_freq_ctrl.freq_db.48nHz: 0x%x\n", i, gPwmInfo[i].adaptFreqCtrl.freqDb.freq_48nHz);
					seq_printf(m, "pwm%d.adapt_freq_ctrl.freq_db.50nHz: 0x%x\n", i, gPwmInfo[i].adaptFreqCtrl.freqDb.freq_50nHz);
					seq_printf(m, "pwm%d.adapt_freq_ctrl.freq_db.60nHz: 0x%x\n", i, gPwmInfo[i].adaptFreqCtrl.freqDb.freq_60nHz);
				}
				seq_printf(m, "\n");
			}
		}
		break;

		default: break;
	}

	return RET_OK;
}

