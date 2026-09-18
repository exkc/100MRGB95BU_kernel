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
 *  Brief description. 
 *  Detailed description starts here. 
 *
 *  @author		wonsik.do
 *  @version	1.0 
 *  @date		2012-04-25
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "afe_drv.h"
#include "os_util.h"
#include "cvd_module.h"
#include "cvd_control.h"
#include "cvd_task.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define CVD_BURST_GATE_ADJUST_FOR_BURST_POSITION_SHIFT
#define CVD_ADAPTIVE_BURST_GATE_END_MODE

#undef CVD_USE_NO_BURST_FLAG

//Workaround for Field Stream(양천구 신월동 11채널 영상 Sync흔들림)
//Set hstate_fixed to '1' on NTSC RF signal
#define CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC

#define	CVD_SYSTEM_DETECTION_BY_CORDIC_ONLY
//#define	CVD_SYSTEM_DETECTION_BY_CORDIC_CS0_CS1

// Workaround for stable AGC on EBC field stream
//Disable AGC WA for H13B0 Revision
//#define L9_WA_FOR_EBS_STABLE_AGC
#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
#ifdef CVD_CDTO_CONTROL
#define	CVD_STABLE_COUNT_1	3
#else
#define	CVD_STABLE_COUNT_1	2
#endif
#else
#define	CVD_STABLE_COUNT_1	1
#endif
#define	CVD_STABLE_COUNT_20	20

//Workaround for PERU noisy field signal(low freq cut-off, status_noise is 0x3ff), flickering and unstable sync
//Disable AGC WA for H13B0 Revision
//#define L9_AGC_BYPASS_WA_FOR_NOISY_SIGNAL

//Workaround for Field Stream(대전 대덕구 화면 펄럭임발생 문제 : 수직 동기 떨림 빈도 100%)
//Set vsync_cntl 0x2, vsync_cntl_noisy 0x1, vloop_tc 0x3
//#define L9_VSYNC_CNTL_FOR_STABLE_VSYNC

// Workaround for DONG_GO_DONG_RAK stream :	20120208
#define CVD_CHANGE_FIELD_DETECT_MODE_ON_DONG_GO_DONG_RAK

//Disable AGC WA for H13B0 Revision
//#define L9_ADAPTIVE_AGC_PEAK_EN_CONTROL
#define CVD_ADAPTIVE_AGC_PEAK_EN_CONTROL
//#define L9_DONT_KILL_CHROMALOCK_ON_CLOCK_LOST
#define CVD_BYPASS_AGC_ON_ADAPTIVE_BURST_GATE_END_MODE

#define CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD	8	// 10 to 8 : 140428

#define CVD_ADAPTIVE_BURST_GATE_COUNT_ITERATION	20	// 20 is about 1 sec.
#define CVD_ADAPTIVE_BURST_GATE_THRESHOLD_0	0x3D090		// Threshold for enter CDTO value(hex value of 250K)
#define CVD_ADAPTIVE_BURST_GATE_THRESHOLD_1	0xCE4			// Threshold for CORDIC FREQ VALUE *20 (hex value of 3.3k)
#define CVD_ADAPTIVE_BURST_GATE_THRESHOLD_3	0x27100		// Threshold for leave CDTO value(hex value of 160K)
#define CVD_STABLE_COUNT_FOR_AGC_CONTROL	20

#define CVD_FAST_VLINE625_DETECT

#define CVD_BLACK_LEVEL_CONTROL

#define	CVD_VDCT_WA_FOR_FAST_VLINE_DETECTION
#define	CVD_HDCT_WA_FOR_HLOCK_ERROR

#define CVD_VFREQ_STABLE_COUNT	5

// Code for H15 color bar
//#define M16_CVD_COLORBAR_PARAMS_TEMP

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern CVD_STATUS_3CS_T	g_CVD_Status_3CS ;

extern CVD_COLOR_SYSTEM_ARRAY_3CS_T *pSetColorSystem_3CS;
//extern CVD_STATE_T	gMainCVD_State;
//extern CVD_STATE_T	gPrevious_Main_System;
//extern CVD_STATE_T	Current_State ;
//extern CVD_STATE_T	Next_State ;
//extern LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T g_CVD_Color_System_Support;
//extern int		gAutoProgramming;
//extern BOOLEAN gPortChangeDetected;
extern CVD_PATTERN_DETECTION_T g_CVD_Pattern_Detection_t ;
//extern BOOLEAN g_CVD_RF_Input_Mode;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
UINT32 g_CVD_TASK_DRV_REV = 0x25052700;

UINT32 g_CVD_WA_Low_Burst_ATV_Noise = 0;
UINT32 g_CVD_Soft_Reset_WA_for_HLock_Error = 1;	//for full white pattern clamping errror
UINT32 g_CVD_Adaptive_Burst_WA_for_SECAM = 1;	//burst/cordic control for abnormal secam signal
UINT32 g_CVD_No_Burst_SECAM_WA = 1;	//191114 : WA for no burst signal not to determined to SECAM
UINT32 g_CVD_Low_Burst_PAL_WA = 1;	//191202 : WA for low burst PAL signal not to go into noburst mode
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static CVD_STATE_T CVD_Check_Color_System_Support(LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	forced_color_system);
static int CVD_Video_NotReady_State_Control(void);
static int CVD_VideoReadyToDetect_State_Control(void);
static int CVD_NTSC_State_Control(void);
static int CVD_NTSC443_State_Control(void);
static int CVD_PALi_State_Control(void);
static int CVD_PALm_State_Control(void);
static int CVD_PALCn_State_Control(void);
static int CVD_PAL60_State_Control(void);
static int CVD_SECAM_State_Control(void);
static int CVD_Setting_After_State_Change(void);
static int CVD_Setting_State_Change_to_Sync_Lock(void);
static int CVD_Setting_State_Change_to_No_Signal(void);
static int CVD_Update_Status_Variables(void);
static int CVD_Workaround_Stable_Count_More_Than_20(void);
static int CVD_Workaround_Stable_Count_20(void);
static int CVD_Workaround_Stable_Count_1(void);
static int CVD_Workaround_Stable_Count_Less_Than_20(void) ;
static int CVD_Workaround_Stable_Count_3(void);
static int CVD_Workaround_Stable_Count_5(void);
static int CVD_Workaround_Stable_Count_More_Than_1(void);
static int CVD_Workaround_Low_Burst_Magnitude(void);
static int CVD_Workaround_PAL_RF_CGAC(void);
static int CVD_Workaround_NTSC_RF_CGAC(void);
static int CVD_Workaround_NTSC_AV_CGAC(void);
static int CVD_Workaround_SECAM_Burst_Position(void);

static UINT32 g_mute_off_count = 0;
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static unsigned int _CVD_NoSignal_Time = 0;
static unsigned int _CVD_SignalLocked_Time = 0;
static unsigned int _CVD_LockedStable_Time = 0;

//static UINT8 MainCVD_Same_State_Count=0;
static int _g_cagc_for_ntscj, _g_cagc_for_ntscm;
static int _g_ntsc_rf_low_burst_mode = 0;

static int _g_burst1_mag_sum = 0;
static int _g_burst2_mag_sum = 0;

static int _g_pal_lowburst_chromalock_level_modified = 0;
/*========================================================================================
	Implementation Group
========================================================================================*/

int	CVD_Task_3cdetect(void)
{

	int loop;
#ifdef CVD_COMB2D_ONLY_CONTROL
//	UINT32 rbuf1_empty, rbuf2_empty, rbuf3_empty, rbuf4_empty, wbuf_ful, wbuf_empty;
#endif

	//CVD_Check_CVD_Memory();

#ifdef CVD_FAST_VLINE625_DETECT
	CVD_Fast_Vline_625_Using_Vdetec_Vcount();
#endif

	CVD_Update_Status_Variables();



	if( (g_CVD_Status_3CS.h_lock_flag || g_CVD_Status_3CS.v_lock_flag || (g_CVD_Status_3CS.cvd_lock_stable_count > 0) ) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count < 10) )
	{
		CVD_THREAD_DEBUG("NO[%d],HL[%d],VL[%d],V625[%d],PAL[%d],SECAM[%d],ChromaL[%d]\n cordic_freq[%d], noise[%d], , noburst[%d], c_state[%d], st_count[%d]\n ",g_CVD_Status_3CS.no_signal_flag, g_CVD_Status_3CS.h_lock_flag, g_CVD_Status_3CS.v_lock_flag, g_CVD_Status_3CS.vline_625_flag, g_CVD_Status_3CS.cvd_pal_flag, g_CVD_Status_3CS.cvd_secam_flag, g_CVD_Status_3CS.cvd_chromalock_flag, g_CVD_Status_3CS.cvd_cordic_freq, g_CVD_Status_3CS.status_noise, g_CVD_Status_3CS.no_burst_flag, g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cvd_lock_stable_count);
		CVD_THREAD_DEBUG("cs0_pal[%d],cs0_secam[%d],cs0_chroma[%d],cs0_cordic[%d],cs1_pal[%d],cs1_secam[%d],cs1_chroma[%d],cs1_cordic[%d],\n ",g_CVD_Status_3CS.cs0_pal_flag, g_CVD_Status_3CS.cs0_secam_flag, g_CVD_Status_3CS.cs0_chromalock_flag, g_CVD_Status_3CS.cs0_cordic_freq, g_CVD_Status_3CS.cs1_pal_flag, g_CVD_Status_3CS.cs1_secam_flag, g_CVD_Status_3CS.cs1_chromalock_flag, g_CVD_Status_3CS.cs1_cordic_freq);
	}

	switch(g_CVD_Status_3CS.cvd_color_system)
	{
		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
		case CVD_STATE_VideoNotReady:
			CVD_Video_NotReady_State_Control();
			//MainCVD_No_Signal = 1;
			/* fall through */
		case CVD_STATE_VideoReadyToDetect:
			CVD_VideoReadyToDetect_State_Control();

			break;

		#pragma GCC diagnostic pop
		case CVD_STATE_NTSC:
			CVD_NTSC_State_Control();
			break;

		case CVD_STATE_NTSC443:
			CVD_NTSC443_State_Control();
			break;

		case CVD_STATE_PALi:
			CVD_PALi_State_Control();
			break;

		case CVD_STATE_PALm:
			CVD_PALm_State_Control();
			break;

		case CVD_STATE_PALCn:
			CVD_PALCn_State_Control();
			break;

		case CVD_STATE_PAL60:
			CVD_PAL60_State_Control();
			break;

		case CVD_STATE_SECAM:
			CVD_SECAM_State_Control();
			break;

		default:
			break;
	}

	// #1 	: sync lock detected
	//		: reset "g_CVD_Status_3CS.cvd_no_signal_count"
	if((g_CVD_Status_3CS.cvd_next_state != CVD_STATE_VideoNotReady) && (g_CVD_Status_3CS.cvd_next_state != CVD_STATE_VideoReadyToDetect))
	{
		g_CVD_Status_3CS.cvd_no_signal_count = 0;
		// Continuous Write on ckill register when signal locked state.
		//		CVD_Force_Color_Kill(0);
	}

	// #2 	: State Change Detected !!!!!
	//		:
	if( (g_CVD_Status_3CS.cvd_next_state != g_CVD_Status_3CS.cvd_color_system) || (g_CVD_Status_3CS.port_change_detected == TRUE))
	{
		CVD_CSD_DEBUG("Before State Change : Locked Stable count [%d]\n", g_CVD_Status_3CS.cvd_lock_stable_count);
		g_CVD_Status_3CS.cvd_lock_stable_count = 0;
		g_CVD_Status_3CS.cvd_noise_sum = 0;	//clear noise sum value
		//		chromalock_count = 0;	//clear noise sum value
	//	g_CVD_Status_3CS.port_change_detected = FALSE;
		g_CVD_Status_3CS.cvd_no_signal_count = 0;

		_g_burst1_mag_sum =0;
		_g_burst2_mag_sum =0;

		//g_CVD_Status_3CS.cvd_color_system = g_CVD_Status_3CS.cvd_next_state;
		CVD_CSD_DEBUG("CVD State Change to [%d]\n", g_CVD_Status_3CS.cvd_next_state);
		CVD_CSD_DEBUG("NO[%d],HL[%d],VL[%d],V625[%d],PAL[%d],SECAM[%d],ChromaL[%d], cordic_freq[%d], noise[%d], noburst[%d], burst_mag[%d], c_state[%d], g_State[%d], prev[%d]\n ",g_CVD_Status_3CS.no_signal_flag, g_CVD_Status_3CS.h_lock_flag, g_CVD_Status_3CS.v_lock_flag, g_CVD_Status_3CS.vline_625_flag, g_CVD_Status_3CS.cvd_pal_flag, g_CVD_Status_3CS.cvd_secam_flag, g_CVD_Status_3CS.cvd_chromalock_flag, g_CVD_Status_3CS.cvd_cordic_freq, g_CVD_Status_3CS.status_noise, g_CVD_Status_3CS.no_burst_flag, g_CVD_Status_3CS.cvd_burst_mag, g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cvd_prev_color_system);
		CVD_CSD_DEBUG("CS0:PAL[%d],SECAM[%d],ChromaL[%d] cordic_freq[%d]\n ", g_CVD_Status_3CS.cs0_pal_flag, g_CVD_Status_3CS.cs0_secam_flag, g_CVD_Status_3CS.cs0_chromalock_flag, g_CVD_Status_3CS.cs0_cordic_freq);
		CVD_CSD_DEBUG("CS1:PAL[%d],SECAM[%d],ChromaL[%d] cordic_freq[%d]\n ", g_CVD_Status_3CS.cs1_pal_flag, g_CVD_Status_3CS.cs1_secam_flag, g_CVD_Status_3CS.cs1_chromalock_flag, g_CVD_Status_3CS.cs1_cordic_freq);
		CVD_CSD_DEBUG("Color_System_Support[0x%x], port changed [%d]\n", g_CVD_Status_3CS.color_system_support, g_CVD_Status_3CS.port_change_detected);

		// For proper color system detection, at first set cstate value to default.
		//CVD_Program_Color_System_PreJob(&pSetColorSystem_3CS->Color_System_Params[CVD_STATE_Default]);
		CVD_No_Color_Cstate_Control(&g_CVD_Status_3CS, 1);

		//120328 : not to excute following function on signal transition period.
		//CVD_NoBurst_CKill_Control(&g_CVD_Status_3CS);

		for(loop = 0;loop < 10;loop++) {
			g_CVD_Status_3CS.burst_mag_array[loop] = 0xFFFF ;
			g_CVD_Status_3CS.burst_mag_sum += g_CVD_Status_3CS.burst_mag_array[loop];
		}

		g_CVD_Status_3CS.burst_mag_prev=0;
		g_CVD_Status_3CS.burst_mag_next=0;
		g_CVD_Status_3CS.prev_burst_mag_avg = 0xbc0;
		g_CVD_Status_3CS.cagc_target = 0xbc0;

		CVD_Setting_After_State_Change();

		// #3 	: State Change Detected && Sync Lock Detected !!!
		//		:
		if(g_CVD_Status_3CS.cvd_next_state < CVD_STATE_VideoNotReady)
		{
			CVD_Setting_State_Change_to_Sync_Lock();
		}
		// #7 	: State Change to NO SIGNAL !!!!!
		//		:
		else if(g_CVD_Status_3CS.cvd_next_state != CVD_STATE_VideoReadyToDetect)  // No Signal or color system change
		{
			CVD_Setting_State_Change_to_No_Signal();
		}
		// #8 	: State Change to videoreadytodetect !!!!!
		//		: never enter here
		else
		{
			// From Ok : SW workaround for 3D comb operation 2010/06/04
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoReadyToDetect;
		}
		//MainCVD_Same_State_Count = 0;

		//1126 for fast standard detection
		//gMainCVD_State = g_CVD_Status_3CS.cvd_next_state;
		g_CVD_Status_3CS.cvd_color_system = g_CVD_Status_3CS.cvd_next_state;

		//120711 : modified not to use noburst_ckill register. 
		// Jitter on noburst cross hatch signal can be improved by setting reg_fixed_cstate to '0', reg_cstate to '5'
		// cstate values were modified(reg_fixed_cstate to '1', reg_cstate to '7') to satisfy sub-carrier pull-in range test.
		// CVD driver is modified that, when chroma is Unlocked and burst magnitude is Not small cstate values will be modified.

		// Set Noburst Ckill to 0(default value) whenever state change occur
		//CVD_CSD_DEBUG("Set No Burst CKill to 0\n");
		//CVD_NoBurst_CKill_Control(&g_CVD_Status_3CS, 1);
		if(g_CVD_Status_3CS.port_change_detected)
		{
			CVD_CSD_DEBUG("@@@ Port changed ... clear prev color system @@@\n");
			g_CVD_Status_3CS.cvd_prev_color_system = CVD_STATE_VideoNotReady;
			g_CVD_Status_3CS.port_change_detected = FALSE;
			g_CVD_Status_3CS.cvd_no_signal_count = 0;
		}

	} // #2 	: State Change Detected 

	// #8 	: Same State Again
	else // same state again
	{

		// #9 	: Same State and Sync Lock
		//		CVD_CSD_DEBUG("Same State and Sync Lock , g_CVD_Status_3CS.cvd_next_state[%d], gAutoProgramming[%d]\n",g_CVD_Status_3CS.cvd_next_state, g_CVD_Status_3CS.in_atv_tunning );

		if (g_CVD_Status_3CS.cvd_next_state < CVD_STATE_VideoNotReady)
		{
			if(g_CVD_Status_3CS.in_atv_tunning == FALSE) {

				g_CVD_Status_3CS.cvd_noise_sum += g_CVD_Status_3CS.status_noise;
				//CVD_DEBUG("@@@ status_noise[0x%x], noise_sum[0x%x], stable_count[%d] @@@\n", g_CVD_Status_3CS.status_noise, g_CVD_Status_3CS.cvd_noise_sum, g_CVD_Status_3CS.cvd_lock_stable_count);

				//				if(g_CVD_Status_3CS.cvd_chromalock_flag)
				//					chromalock_count++;


				if(g_CVD_Status_3CS.cvd_lock_stable_count > CVD_STABLE_COUNT_20) 
					CVD_Workaround_Stable_Count_More_Than_20();
				else if(g_CVD_Status_3CS.cvd_lock_stable_count == CVD_STABLE_COUNT_20) 
					CVD_Workaround_Stable_Count_20();
#if 0
				else if(g_CVD_Status_3CS.cvd_lock_stable_count == (CVD_STABLE_COUNT_1 + 2) )
				{
#ifdef CVD_COMB2D_ONLY_CONTROL
					CVD_DEBUG("$$$ Comb2d only MD [0] $$$\n");
					CVD_Set_comb2d_only_md(g_SetColorSystem_3CS[g_CVD_Status_3CS.cvd_next_state]->reg_comb2d_only);
#endif
					g_CVD_Status_3CS.cvd_lock_stable_count++;
				}
				else if(g_CVD_Status_3CS.cvd_lock_stable_count == (CVD_STABLE_COUNT_1 + 1) )
				{
#ifdef CVD_COMB2D_ONLY_CONTROL
					CVD_DEBUG("$$$ Comb2d only [0] $$$\n");
					CVD_Set_comb2d_only(g_SetColorSystem_3CS[g_CVD_Status_3CS.cvd_next_state]->reg_comb2d_only);
#endif
					g_CVD_Status_3CS.cvd_lock_stable_count++;
				}
#endif
				else if(g_CVD_Status_3CS.cvd_lock_stable_count == (CVD_STABLE_COUNT_1 + 4) )
					CVD_Workaround_Stable_Count_5();
				else if(g_CVD_Status_3CS.cvd_lock_stable_count == (CVD_STABLE_COUNT_1 + 2) )
					CVD_Workaround_Stable_Count_3();
				
				else if(g_CVD_Status_3CS.cvd_lock_stable_count == CVD_STABLE_COUNT_1)
					CVD_Workaround_Stable_Count_1();

				else if(g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_20)
					CVD_Workaround_Stable_Count_Less_Than_20(); 

				if(g_CVD_Status_3CS.cvd_lock_stable_count > 0)
				{
					//Enable NoBurst CKill Control after color system is detected and stable
					//CVD_NoBurst_CKill_Control(&g_CVD_Status_3CS, 0);

					//120711 : adaptive cstate control for sub-carrier pull-in-range test
					//CVD_Cstate_Control_for_SC_PullInRange(&g_CVD_Status_3CS, 0);
					CVD_No_Color_Cstate_Control(&g_CVD_Status_3CS, 0);
				}

				if(g_CVD_Status_3CS.cvd_lock_stable_count > CVD_STABLE_COUNT_1)
					CVD_Workaround_Stable_Count_More_Than_1();
			}
		}
		// #10 	: Same State , but no signal
		//		:
		else
		{
#ifdef CVD_ADAPTIVE_AGC_PEAK_EN_CONTROL
			if( (g_CVD_Status_3CS.h_lock_flag == 0) && ( g_CVD_Status_3CS.v_lock_flag == 0) )
			{
				// to prevent frequent agc peak control on weak RF signal
				// set agc peak en off only when h_lock & v_lock are unlocked
				CVD_AGC_Peak_En_Control(0, 0, 0); //force off peak_en

				/* 131219 : disable agc half en control : dark video after channel change (from no signal)*/
				if( g_CVD_Status_3CS.in_rf_mode == TRUE )
				{
					CVD_agc_half_en_control(1);//gogosing agc
				}
			}
#endif
			g_CVD_Status_3CS.cvd_lock_stable_count = 0;
		}

		//g_CVD_Status_3CS.cvd_color_system = g_CVD_Status_3CS.cvd_next_state;
#if 0
		//periodic reset of CS0/CS1 is needed???
		if ( lx_chip_rev( ) >= LX_CHIP_REV( L9, B0 ) )
		{
			CVD_swrst_CS( CVD_SEL_CS_CS0);
			CVD_swrst_CS( CVD_SEL_CS_CS1);
		}
#endif


	}
	/*
	if(g_mute_off_count < 20)
	{
		g_mute_off_count ++;
	}
	else if(g_mute_off_count == 20) {

		AFE_PRINT("### 1 SEC after Mute off ###\n");
#ifdef CVD_COMB2D_ONLY_CONTROL
#ifndef CVD_3DCOMB_TEST_TMP
		CVD_DEBUG("$$$ Comb2d only [0] : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
		CVD_Set_comb2d_only(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state].reg_comb2d_only);
	//	CVD_DEBUG("$$$ Comb2d only MD [0] : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
	//	CVD_Set_comb2d_only_md(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state].reg_comb2d_only);
#endif
#endif
		g_mute_off_count ++;
	}
	*/


//	CVD_Comb2d_Only_Test(0,0,0,0,0,0);

	return 0;
}

static CVD_STATE_T CVD_Check_Color_System_Support(LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	forced_color_system)
{
	CVD_STATE_T	system_ret = CVD_STATE_Default;

	// For user force color system
	if(forced_color_system == LX_COLOR_SYSTEM_NTSC_M)		// For Kor/US
		system_ret = CVD_STATE_NTSC;
	else if(forced_color_system == LX_COLOR_SYSTEM_PAL_G)
		system_ret = CVD_STATE_PALi;
	else if(forced_color_system == LX_COLOR_SYSTEM_PAL_NC)
		system_ret = CVD_STATE_PALCn;
	else if(forced_color_system == LX_COLOR_SYSTEM_PAL_M)
		system_ret = CVD_STATE_PALm;
	else if(forced_color_system == LX_COLOR_SYSTEM_SECAM)
		system_ret = CVD_STATE_SECAM;
	else if(forced_color_system == LX_COLOR_SYSTEM_NTSC_443)
		system_ret = CVD_STATE_NTSC443;
	else if(forced_color_system == LX_COLOR_SYSTEM_PAL_60)
		system_ret = CVD_STATE_PAL60;

	return system_ret;
}

int CVD_Channel_Change_Control(BOOLEAN bATV_Channel_Change)
{
	if(bATV_Channel_Change)
	{
#ifdef CVD_COMB2D_ONLY_CONTROL
#ifndef CVD_3DCOMB_TEST_TMP
		CVD_Set_comb2d_only(1);
		CVD_Set_comb2d_only_md(1);
		CVD_DEBUG("### Comb2d only [1] [%s][%d] ###\n",__func__, __LINE__ );
#endif
#endif
		CVD_DEBUG("ATV Channel Change Detected !!!\n");

//		g_CVD_Status_3CS.port_change_detected = TRUE;
	}
	else
	{
		CVD_DEBUG("### Mute off ### : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
#ifdef CVD_COMB2D_ONLY_CONTROL
#ifndef CVD_3DCOMB_TEST_TMP
		CVD_DEBUG("$$$ Comb2d only [0] : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
		CVD_Set_comb2d_only(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state].reg_comb2d_only);
	//	CVD_DEBUG("$$$ Comb2d only MD [0] : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
	//	CVD_Set_comb2d_only_md(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state].reg_comb2d_only);
#endif
#endif
		CVD_DEBUG("ATV Channel Change End !!!\n");
		g_mute_off_count = 0;
	}

	return 0;
}

int CVD_Set_Color_System_3CS(CVD_STATE_T cvd_next_state)
{
	switch(cvd_next_state)
	{
		case CVD_STATE_NTSC:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_NTSC;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_PAL60;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALm;
			break;

		case CVD_STATE_NTSC443:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_NTSC443;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_NTSC;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALm;
			break;

		case CVD_STATE_PALm:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_PALm;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_PAL60;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_NTSC;
			break;

		case CVD_STATE_PAL60:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_PAL60;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_NTSC;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALm;
			break;

		case CVD_STATE_PALi:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_PALi;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_SECAM;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALCn;
			break;

		case CVD_STATE_PALCn:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_PALCn;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_SECAM;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALi;
			break;

		case CVD_STATE_SECAM:
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_SECAM;
			g_CVD_Status_3CS.cs0_color_system = CVD_STATE_PALi;
			g_CVD_Status_3CS.cs1_color_system = CVD_STATE_PALCn;
			break;

		default:
			AFE_PRINT("ERROR INVALID COLOR SYSTEM!!![%d]\n", cvd_next_state);
			break;
	}

	if(g_CVD_Status_3CS.cvd_color_system <= CVD_STATE_SECAM)
	{

		CVD_CSD_DEBUG("Set Color System : CVD[%d], CS0[%d], CS1[%d]\n", g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cs0_color_system, g_CVD_Status_3CS.cs1_color_system);
		/*
		   CVD_Program_Color_System_buffer_only(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system]);
		   CVD_Program_Color_System_Main_Multi(&pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC]);
		 */
		CVD_Program_Color_System_Main_Multi(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system]);


		CVD_Program_Color_System_CS(CVD_SEL_CS_CS0, &pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cs0_color_system]);
		CVD_Program_Color_System_CS(CVD_SEL_CS_CS1, &pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cs1_color_system]);

		//111221 by kim.min for better color standard detection performance
		CVD_swrst_CS( CVD_SEL_CS_CS0);
		CVD_swrst_CS( CVD_SEL_CS_CS1);

	}

	return 0;
}

static int CVD_Video_NotReady_State_Control(void)
{
	static int no_signal_clamp_step_rewrite_count = 0;
	static int clamping_error_count = 0;
	UINT8 cvbs_icon_value, cvbs_pdb_value, cvbs_cp_value, cvbs_insel_value, cvbs_pdbm_value;

#ifdef CVD_CH42_SKIP_WORKAROUND
	if ( (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.use_internal_demod) )	// if using internal demod
	{
		no_signal_clamp_step_rewrite_count++;
		if(no_signal_clamp_step_rewrite_count > 20)	// no signal for more than 1sec.
		{
			CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
			no_signal_clamp_step_rewrite_count = 0;
		}
	}
	//CVD_ClampAGC_OnOff(0); // agc off on No signal for ch42 no signal workaround
	//			if ( lx_chip_rev( ) < LX_CHIP_REV( L9, A0 ) )
	//				CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
	//			else
	//			{
	//Disable Clampagc reset workaround (Clamp AGC problem is fixed by disabling x2 LPF setting at Set_AAF_Params)
	//CVD_Reset_Clampagc();
	//CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
	//			}
#endif
	// dws 0809 for 42ch no signal problem
	if(g_CVD_Status_3CS.cvd_no_signal_count > 4) 
	{
#ifdef	CVD_HDCT_WA_FOR_HLOCK_ERROR
		if( (g_CVD_Status_3CS.no_signal_flag == 0) && (g_CVD_Status_3CS.h_lock_flag == 0) \
				&& (g_CVD_Status_3CS.v_lock_flag == 1) && (g_CVD_Status_3CS.vnon_standard_flag == 1) )
		{
			CVD_Reset_hdct(1);
			CVD_DEBUG("!!! CVD HDCT WORKAROUND !!!\n");
			//					OS_MsecSleep(5);
			CVD_Reset_hdct(0);
		}
#endif
		//TVHWKR-132 : ATV US-06 clamping issue
		if( (g_CVD_Soft_Reset_WA_for_HLock_Error == 1) \
				&& (g_CVD_Status_3CS.in_atv_tunning == FALSE) && (g_CVD_Status_3CS.in_rf_mode == TRUE) \
				&& (g_CVD_Status_3CS.no_signal_flag == 0) && (g_CVD_Status_3CS.h_lock_flag == 0) \
				&& (g_CVD_Status_3CS.v_lock_flag == 1) /*&& (g_CVD_Status_3CS.vnon_standard_flag == 1)*/ \
				&& ( (lx_chip_rev() >= LX_CHIP_REV(M23,A0) ) || \
					( (lx_chip_rev() < LX_CHIP_REV(M23,A0) ) && (g_CVD_Status_3CS.hnon_standard_flag == 1) ) )
				/*	&& (g_CVD_Status_3CS.no_burst_flag == 1)*/ )
		{
			if( ( (lx_chip_rev() >= LX_CHIP_REV(M23,A0)) && (clamping_error_count > 1) ) || ( (lx_chip_rev() < LX_CHIP_REV(M23,A0)) && (clamping_error_count > 5) ) )
			{
				AFE_PRINT("Clamping ERROR !!!  cvd soft reset : no_signal count [%d], clamping error count [%d]\n", g_CVD_Status_3CS.cvd_no_signal_count, clamping_error_count);
				CVD_CVD_Soft_Reset();
				clamping_error_count = 0;
			}
			else
				clamping_error_count++;

			AFE_PRINT("Clamping ERROR ? : no_signal count [%d], clamping error count [%d]\n", g_CVD_Status_3CS.cvd_no_signal_count, clamping_error_count);

		}
		else
			clamping_error_count = 0;

		if(g_CVD_Status_3CS.cvd_no_signal_count == 30)
		{
			CVD_Get_AFE_CVBS_status(&cvbs_icon_value, &cvbs_pdb_value, &cvbs_cp_value, &cvbs_insel_value, &cvbs_pdbm_value);
			AFE_PRINT("CVD Not Lock : NO[%d],HL[%d],VL[%d],V625[%d],PAL[%d],SEC[%d],ChL[%d],cor_fr[%d],noi[%d],nobu[%d],c_state[%d],st_cnt[%d],hn[%d],vn[%d],tun[%d],rf[%d],no_cnt[%d]\n",g_CVD_Status_3CS.no_signal_flag, g_CVD_Status_3CS.h_lock_flag, g_CVD_Status_3CS.v_lock_flag, g_CVD_Status_3CS.vline_625_flag, g_CVD_Status_3CS.cvd_pal_flag, g_CVD_Status_3CS.cvd_secam_flag, g_CVD_Status_3CS.cvd_chromalock_flag, g_CVD_Status_3CS.cvd_cordic_freq, g_CVD_Status_3CS.status_noise, g_CVD_Status_3CS.no_burst_flag, g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cvd_lock_stable_count, g_CVD_Status_3CS.hnon_standard_flag, g_CVD_Status_3CS.vnon_standard_flag ,g_CVD_Status_3CS.in_atv_tunning, g_CVD_Status_3CS.in_rf_mode, g_CVD_Status_3CS.cvd_no_signal_count);
			AFE_PRINT("CVBS AFE : icon[%d],pdb[%d],cp[%d],insel[%d],pdbm[%d]\n", cvbs_icon_value, cvbs_pdb_value, cvbs_cp_value, cvbs_insel_value, cvbs_pdbm_value);
			CVD_CVD_Soft_Reset();
		}

		if(g_CVD_Status_3CS.cvd_no_signal_count < 100000)
		g_CVD_Status_3CS.cvd_no_signal_count++;

	}
	else if(g_CVD_Status_3CS.cvd_no_signal_count == 4) // Remain No Signal for 2 seconds
	{
		// dws 0906 for color kill on no signal
		CVD_Force_Color_Kill(1);
		g_CVD_Status_3CS.cvd_no_signal_count++;
	}
	else
	{
		clamping_error_count = 0;
		g_CVD_Status_3CS.cvd_no_signal_count++;
	}

	return 0;
}

static int CVD_VideoReadyToDetect_State_Control(void)
{
	UINT8	No_Signal_Flag, HV_Lock_Flag;
	CVD_STATE_T	check_supporting_color_system;

	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	No_Signal_Flag = 0;

	if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;
	// For user force color system
	else if ((check_supporting_color_system = CVD_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
		g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;
	else if(g_CVD_Status_3CS.color_system_support == (LX_COLOR_SYSTEM_PAL_M | LX_COLOR_SYSTEM_NTSC_M | LX_COLOR_SYSTEM_PAL_NC) )	// For Brazil
	{
		if ( g_CVD_Status_3CS.vline_625_flag ) //Vertical 625 Line
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
		else
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
		//g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
	}
	else // for Multi System
	{
		if ( g_CVD_Status_3CS.vline_625_flag ) //Vertical 625 Line
		{
			if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
			else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
			else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
		}
		else
		{
			if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
			else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
			else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
			else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)
				g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;
		}
	}

	if(g_CVD_Status_3CS.cvd_next_state != CVD_STATE_VideoNotReady)
	{
		_CVD_SignalLocked_Time = jiffies_to_msecs(jiffies);
		CVD_CSD_DEBUG("CVD Lock !!! g_CVD_Color_System_Support[0x%x], check_supporting_color_system[0x%x], Next_State[%d], port changed [%d]\n", g_CVD_Status_3CS.color_system_support, check_supporting_color_system, g_CVD_Status_3CS.cvd_next_state, g_CVD_Status_3CS.port_change_detected);
	}
	return 0;
}

static int CVD_NTSC_State_Control(void)
{
	UINT8	No_Signal_Flag, HV_Lock_Flag;
	CVD_STATE_T	check_supporting_color_system;

	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	No_Signal_Flag = 0;

	if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

	// For user force color system
	else if ((check_supporting_color_system = CVD_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
		g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;
#ifdef CVD_USE_NO_BURST_FLAG
	else if(!g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// For No burst signal, with 525 line system remain in NTSC
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
#endif
	else if(g_CVD_Status_3CS.vline_625_flag)
	{
		if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
	}
#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	else if ( (g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_1) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count > 0) )	// added 130709 : in atv tunning mode color system detection not working
		g_CVD_Status_3CS.cvd_next_state = g_CVD_Status_3CS.cvd_color_system;
#endif
	// 111028 wonsik.do : Check PAL-M before NTSC-M to fix slow color system transition to PAL-M (both NTSC-M & PAL-M locked for long time)
	// 130704 wondik.do : add 10 on FC_MORE_THRESHOLD, for transition to PAL-M on SIC ch 45.
	// 141126 wondik.do : for PAL-M 141029_1623 : CS0/CS1 both cordic high and noisy signal
	else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && ( (g_CVD_Status_3CS.cs1_cordic_freq <= (FC_MORE_THRESHOLD+10) || ( (g_CVD_Status_3CS.cs1_cordic_freq > (FC_MORE_THRESHOLD+10) && (g_CVD_Status_3CS.cs0_cordic_freq > (FC_MORE_THRESHOLD+10) ) && (g_CVD_Status_3CS.status_noise > 800)) ) ) ) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) // Transition to PALm
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

	else if(!g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)) // Remain in NTSC
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;

	else if(g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)) // Transition to PAL60
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

	else if(!g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cs0_pal_flag && !g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)) // Transition to NTSC443
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

	else
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;

	return 0;
}

static int CVD_NTSC443_State_Control(void)
{
	UINT8	No_Signal_Flag, HV_Lock_Flag;
	CVD_STATE_T	check_supporting_color_system;

	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	No_Signal_Flag = 0;

	if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

	// For user force color system
	else if ((check_supporting_color_system = CVD_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
		g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
	else if(!g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// For no burst signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
#endif

	else if(g_CVD_Status_3CS.vline_625_flag)
	{
		if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
	}
#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	else if ( (g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_1) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count > 0) )	// added 130709 : in atv tunning mode color system detection not working
		g_CVD_Status_3CS.cvd_next_state = g_CVD_Status_3CS.cvd_color_system;
#endif

	else if(!g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)) // Remain in NTSC443
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

	else if(!g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)) // Transition to NTSC
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

	else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) // Transition to PALm
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

	else if(g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cs0_pal_flag && !g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)) // Transition to PAL60
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

	//120613 for EIDEN NTSC-443 to PAL-m transition
	else if(!g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq > (FC_MORE_THRESHOLD+ 30) )  && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD)&& (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) 
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

	else
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

	return 0;
}

static int CVD_PALi_State_Control(void)
{
	UINT8	No_Signal_Flag, HV_Lock_Flag;
	CVD_STATE_T	check_supporting_color_system;

	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	No_Signal_Flag = 0;

	g_CVD_Status_3CS.cs0_secam_flag &= CVD_Get_SECAM_Flag_CS0();//130204

	if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

	// For user force color system
	else if ((check_supporting_color_system = CVD_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
		g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
	else if(g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 625 line signal
	{
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
	}
#endif
	else if(g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_color_detected)	// no burst 625 line signal
	{
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
	}

	else if(!g_CVD_Status_3CS.vline_625_flag)	// Transition to 525 line system
	{
		if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;
	}

#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	else if ( (g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_1) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count > 0) )	// added 130709 : in atv tunning mode color system detection not working
		g_CVD_Status_3CS.cvd_next_state = g_CVD_Status_3CS.cvd_color_system;
#endif
	else if(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Remain in PALi
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

	//111028 added cvd choromalock flag to AND with cvd pal flag to determine SECAM detection
	//110809 added cvd pal flag
	//130123 added burst mag for secam detection
	//130201 cvd_fc_flag more than 0 for secam detection
	else if(!(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag) && !g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_secam_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cvd_burst_mag > 0x100) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD)  && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM) \
			&& !(g_CVD_No_Burst_SECAM_WA && g_CVD_Status_3CS.no_burst_flag && g_CVD_Pattern_Detection_t.static_pattern_found && !g_CVD_Pattern_Detection_t.pattern_found)) // Transition to SECAM //191113 : R-12(no color) wrong color system detection (SECAM)
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

	// 140301 : for faster SECAM detection
	// Added 120613 for EIDEN-3116A SECAM detection
	// 130123 : modified cvd_cordic_freq
	// 130615 : only for AV inputs (indonesia field stream detected as SECAM : PAL_130603_0715_490 )
	// 140121 : modified for EIDEN SECAM RF detection(both PAL & SECAM detected)
	else if( (g_CVD_Status_3CS.status_noise < 500) &&
			(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq > ( FC_MORE_THRESHOLD + 0) )) &&
			!g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_secam_flag && g_CVD_Status_3CS.cs0_chromalock_flag && 
			!g_CVD_Status_3CS.cs1_pal_flag && !g_CVD_Status_3CS.cs1_secam_flag && /*!g_CVD_Status_3CS.cs1_chromalock_flag &&*/ 	//added 140121 for EIDEN RF
			( abs(g_CVD_Status_3CS.cs0_cordic_freq - 128) < 0x30 ) &&
			( g_CVD_Status_3CS.cs1_cordic_freq < (FC_LESS_THRESHOLD - 30) ) &&
			/*	(g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && */
			(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM) ) // Transition to SECAM
	{
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
	}

	else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Transition to PALCn
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

#ifdef	CVD_SYSTEM_DETECTION_BY_CORDIC_ONLY
	else if((g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Remain in PALi
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
#ifdef CVD_SYSTEM_DETECTION_BY_CORDIC_CS0_CS1
	else if((g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Transition to SECAM
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
	else if((g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Transition to PALCn
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
#endif
#endif
	else
	{
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
	}

	return 0;
}

static int CVD_PALm_State_Control(void)
{
	UINT8	No_Signal_Flag, HV_Lock_Flag;
	CVD_STATE_T	check_supporting_color_system;

	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	No_Signal_Flag = 0;

	if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

	// For user force color system
	else if ((check_supporting_color_system = CVD_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
		g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
	else if(!g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 525 line
	{
		if(g_CVD_Status_3CS.color_system_support == (LX_COLOR_SYSTEM_PAL_M | LX_COLOR_SYSTEM_NTSC_M | LX_COLOR_SYSTEM_PAL_NC) )	// For Brazil
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
		else
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
	}
#endif

	else if(g_CVD_Status_3CS.vline_625_flag)
	{
		if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
	}

#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	else if ( (g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_1) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count > 0) )	// added 130709 : in atv tunning mode color system detection not working
		g_CVD_Status_3CS.cvd_next_state = g_CVD_Status_3CS.cvd_color_system;
#endif
	else if(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= ( FC_MORE_THRESHOLD + 0x40) ) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) // Remain in PALm
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

	else if(g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)) // Transition to PAL60
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

	else if(!g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)) // Transition to NTSC
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;

	else if(!g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cs0_pal_flag && !g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) /*&& (g_CVD_Status_3CS.cs0_cordic_freq < FC_LESS_THRESHOLD)*/ && (g_CVD_Status_3CS.cs1_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)) // Transition to NTSC443
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

	else
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

	return 0;
}

static int CVD_PALCn_State_Control(void)
{
	UINT8	No_Signal_Flag, HV_Lock_Flag;
	CVD_STATE_T	check_supporting_color_system;

	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	No_Signal_Flag = 0;

	if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

	// For user force color system
	else if ((check_supporting_color_system = CVD_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
		g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
	else if(g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 625 line
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
#endif

	else if(!g_CVD_Status_3CS.vline_625_flag)		// Transition to 525 line systems
	{
		if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;
	}

#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	else if ( (g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_1) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count > 0) )	// added 130709 : in atv tunning mode color system detection not working
		g_CVD_Status_3CS.cvd_next_state = g_CVD_Status_3CS.cvd_color_system;
#endif
	else if(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Remain in PALCn
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

	else if(!g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_secam_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Transition to SECAM
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

	else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

#ifdef	CVD_SYSTEM_DETECTION_BY_CORDIC_ONLY
	else if((g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Remain in PALCn
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

#ifdef CVD_SYSTEM_DETECTION_BY_CORDIC_CS0_CS1
	else if((g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Transition to SECAM
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

	else if((g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
#endif
#endif

	else
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

	return 0;
}

static int CVD_PAL60_State_Control(void)
{
	UINT8	No_Signal_Flag, HV_Lock_Flag;
	CVD_STATE_T	check_supporting_color_system;

	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	No_Signal_Flag = 0;

	if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

	// For user force color system
	else if ((check_supporting_color_system = CVD_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
		g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
	else if(!g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 525 line
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
#endif

	else if(g_CVD_Status_3CS.vline_625_flag)
	{
		if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
	}

#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	else if ( (g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_1) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count > 0) )	// added 130709 : in atv tunning mode color system detection not working
		g_CVD_Status_3CS.cvd_next_state = g_CVD_Status_3CS.cvd_color_system;
#endif
	else if(g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)) // Remain in PAL60
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

	else if(!g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)) // Transition to NTSC
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;

	else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)) // Transition to PALm
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;

	else if(!g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cs0_pal_flag && !g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq < FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)) // Transition to NTSC443
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;

	else
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;

	return 0;
}

static int CVD_SECAM_State_Control(void)
{
	UINT8	No_Signal_Flag, HV_Lock_Flag;
	CVD_STATE_T	check_supporting_color_system;

	HV_Lock_Flag = g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag;
	No_Signal_Flag = 0;

	if ( !HV_Lock_Flag || No_Signal_Flag)	// No signal
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;

	// For user force color system
	else if ((check_supporting_color_system = CVD_Check_Color_System_Support(g_CVD_Status_3CS.color_system_support)) > 0)
		g_CVD_Status_3CS.cvd_next_state = check_supporting_color_system;

#ifdef CVD_USE_NO_BURST_FLAG
	else if(g_CVD_Status_3CS.vline_625_flag && g_CVD_Status_3CS.no_burst_flag)	// no burst 625line
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;
#endif

	else if(!g_CVD_Status_3CS.vline_625_flag)		//Transition to 625line system
	{
		if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_M)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_M)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALm;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_NTSC_443)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_NTSC443;
		else if(g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_60)
			g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PAL60;
	}

#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	else if ( (g_CVD_Status_3CS.cvd_lock_stable_count < CVD_STABLE_COUNT_1) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count > 0) )	// added 130709 : in atv tunning mode color system detection not working
		g_CVD_Status_3CS.cvd_next_state = g_CVD_Status_3CS.cvd_color_system;
#endif
	else if(!g_CVD_Status_3CS.cvd_pal_flag && g_CVD_Status_3CS.cvd_secam_flag && g_CVD_Status_3CS.cvd_chromalock_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Remain in SECAM
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

	else if(g_CVD_Status_3CS.cs0_pal_flag && g_CVD_Status_3CS.cs0_chromalock_flag && (g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

	else if(g_CVD_Status_3CS.cs1_pal_flag && g_CVD_Status_3CS.cs1_chromalock_flag && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Transition to PALCn
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;

	// 130123 : added for no burst signal
	else if(!g_CVD_Status_3CS.cvd_pal_flag && !g_CVD_Status_3CS.cvd_secam_flag && (g_CVD_Status_3CS.cvd_burst_mag < 0x300) && !g_CVD_Status_3CS.cs1_pal_flag && !g_CVD_Status_3CS.cs1_chromalock_flag && !g_CVD_Status_3CS.cs1_secam_flag && (g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

#ifdef	CVD_SYSTEM_DETECTION_BY_CORDIC_ONLY
	else if((g_CVD_Status_3CS.cvd_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cvd_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_SECAM)) // Remain in SECAM
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;
#ifdef CVD_SYSTEM_DETECTION_BY_CORDIC_CS0_CS1
	else if((g_CVD_Status_3CS.cs0_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs0_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_G)) // Transition to PALi
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALi;

	else if((g_CVD_Status_3CS.cs1_cordic_freq <= FC_MORE_THRESHOLD) && (g_CVD_Status_3CS.cs1_cordic_freq >= FC_LESS_THRESHOLD) && (g_CVD_Status_3CS.color_system_support & LX_COLOR_SYSTEM_PAL_NC)) // Transition to PALCn
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_PALCn;
#endif
#endif

	else
		g_CVD_Status_3CS.cvd_next_state = CVD_STATE_SECAM;

	return 0;
}

static int CVD_Setting_After_State_Change(void)
{

	// restore to default value
	CVD_Set_force_vcr(0);
	CVD_Set_vcr_auto_switch_en(0);

	if(g_CVD_Low_Burst_PAL_WA == 1)
	{
		//for Fast Chroma Lock/Unlocking !!!
		CVD_chromalock_level_control(0x5);
		_g_pal_lowburst_chromalock_level_modified = 0;
	}

#ifdef CVD_COMB2D_ONLY_CONTROL
#ifndef CVD_3DCOMB_ERROR_WORKAROUND
	//120705 : Enable comb2d_only when state changed !!!
	CVD_DEBUG("### Comb2d only [1] [%s][%d] ###\n",__func__, __LINE__ );
	CVD_Set_comb2d_only(1);
	CVD_Set_comb2d_only_md(1);
#endif
#endif

#ifdef CVD_FAST_3DCOMB_WORKAROUND
	if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
	{
		//Enable vf_nstd_en when state changed (WA for 3DComb buffer control error)
		CVD_vf_nstd_control(1);	//default value when state changed
		// Set Hnon_std_threshold to '0' when state changed (WA for 3DComb buffer control error)
		CVD_Set_HNon_Standard_Threshold(0);	//121222 : kim.min
	}
#endif
#ifdef CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
	//		CVD_CSD_DEBUG("Set hstate_fixed value to 0 (default) \n");
	CVD_Set_Hstate_Fixed(0);
	CVD_Set_Hstate_Max(3);
#endif
	// #2.1 	: State Change & Previously Locked State is NTSC
	if( g_CVD_Status_3CS.cvd_prev_color_system == CVD_STATE_NTSC)
	{
		// Restore cagc value to default
		CVD_CSD_DEBUG("Cagc value to default \n");
		CVD_Set_CVD_CAGC(CVD_BURST_MAG_STATE_BIG,&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system], g_CVD_Status_3CS.cvd_prev_color_system);

		CVD_Set_CVD_Saturation_Value(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system].reg_saturation);
		//120131
		/*
		//if saturation value is adjusted, restoring initial value is needed (for same color system detection case)
		if ( lx_chip_rev() >= LX_CHIP_REV( L9, B0) ) {
		CVD_Set_CVD_Saturation_Value(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system].reg_saturation);
		}
		*/
#ifdef CVD_NTSC_NOISY_STABLE_VSYNC_WORKAROUND
		CVD_Enable_LPF_en(0);

		//Fix AV using RF hrs_ha_start value
		if (g_CVD_Status_3CS.in_rf_mode == TRUE)
			CVD_Hstart_Position_Compensator(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system]);
#endif

#ifdef CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
		//		CVD_CSD_DEBUG("Set hstate_fixed value to 0 (default) \n");
		//	CVD_Set_Hstate_Fixed(0);
		//	CVD_Set_Hstate_Max(5);
#endif
#ifdef CVD_CHANGE_FIELD_DETECT_MODE_ON_DONG_GO_DONG_RAK

		CVD_Set_for_Field_Detect_Mode(2);
#endif
#ifdef CVD_ADAPTIVE_AGC_PEAK_EN_CONTROL
		//		CVD_AGC_Peak_En_Control(2, 0, 0);	// force on peak_en
#endif

#ifdef CVD_BURST_GATE_ADJUST_FOR_BURST_POSITION_SHIFT
		if ( g_CVD_Status_3CS.burst_gate_modified )
		{
			CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system].reg_burst_gate_start_new, pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system].reg_burst_gate_end_new);

			g_CVD_Status_3CS.burst_gate_modified = 0;
		}
#endif

	}
	// #2.2 	: State Change & Previously Locked State is PALm
	else if( g_CVD_Status_3CS.cvd_prev_color_system == CVD_STATE_PALm)
	{
#ifdef CVD_ENABLE_PALM_STABLE_SYNC_MODE //not used
		CVD_Set_PALm_Stable_HSync_Mode(0);
#endif
#ifdef CVD_DONT_KILL_CHROMALOCK_ON_CLOCK_LOST
		CVD_OnOff_Chromalock_Ckill(1);
#endif
#ifdef CVD_ADAPTIVE_BURST_GATE_END_MODE
		CVD_Set_for_Burst_Gate_End_On_Noisy(pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALm].reg_burst_gate_end_new ,0);
		CVD_Set_Cpump_Auto_Stip_Noisy_Value(1);
#ifdef CVD_BYPASS_AGC_ON_ADAPTIVE_BURST_GATE_END_MODE
		CVD_AGC_Bypass(0);
#endif
#endif
	}
	// #2.3 	: State Change & Previously Locked State is PALi
	else if( g_CVD_Status_3CS.cvd_prev_color_system == CVD_STATE_PALi) {

		// Restore cagc value to default
		CVD_CSD_DEBUG("Cagc value to default : color_system [%d] \n", g_CVD_Status_3CS.cvd_prev_color_system);
		CVD_Set_CVD_CAGC(CVD_BURST_MAG_STATE_BIG, &pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system], g_CVD_Status_3CS.cvd_prev_color_system);

#ifdef	M16_PAL_STABLE_VSYNC_WORKAROUND	// not used
		CVD_Set_Vsync_Cntl(&pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALi], 0);	// direct vsync
#endif
#ifdef CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
		//		CVD_CSD_DEBUG("Set hstate_fixed value to 0 (default) \n");
		//CVD_Set_Hstate_Fixed(0);
#endif
#ifdef CVD_BURST_GATE_ADJUST_FOR_BURST_POSITION_SHIFT
		if ( g_CVD_Status_3CS.burst_gate_modified )
		{
			CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system].reg_burst_gate_start_new, pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_prev_color_system].reg_burst_gate_end_new);

			g_CVD_Status_3CS.burst_gate_modified = 0;
		}
#endif
		//120217 : added for PAL channel change
	} // #2.4 	: State Change & Previously Locked State is SECAM
	else if( g_CVD_Status_3CS.cvd_prev_color_system == CVD_STATE_SECAM) {
	} // #2.5 	: State Change & Previously Locked State is not NTSC/PALm/PALi/SECAM
	else {
	}
	// NTSC Pattern Detection Function
	if( g_CVD_Pattern_Detection_t.bEnable == TRUE )
	{
		g_CVD_Pattern_Detection_t.pattern_found = 0x0 ;
		g_CVD_Pattern_Detection_t.prev_motion_value = 0x0 ;
		g_CVD_Pattern_Detection_t.global_motion_count = 0x0 ;
		g_CVD_Pattern_Detection_t.static_pattern_found = 0x0 ;
		g_CVD_Pattern_Detection_t.static_pattern_count = 0x0 ;
	}

	if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
		CVD_AGC_Bypass_Function(0, 0, 1 );
	//CVD_AGC_Bypass_Function((UINT32)g_CVD_Status_3CS.status_noise, (UINT32)g_CVD_Status_3CS.h_lock_flag, (UINT32)g_CVD_Status_3CS.no_signal_flag );
	//if((g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) ||(g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALi))
	// Sync Detected !!!
	//
	//
	return 0;
}

static int CVD_Setting_State_Change_to_Sync_Lock(void)
{

	/* Cpump Auto Stip to 1 */
	/* Cpump_Auto_Stip should be '1' : White saturation on normal signal */
	//CVD_Set_Cpump_Auto_Stip_Value(1);

	// If any color system is detected, disable color kill.
	CVD_Force_Color_Kill(0);

	if( g_CVD_Status_3CS.in_rf_mode == TRUE )
	{
		CVD_agc_half_en_control(0);//gogosing agc
	}

	/*
	//120217 for test only
	if ( lx_chip_rev( ) >= LX_CHIP_REV( L9, B0 ) )
	CVD_Reset_mif(0);
	*/

	//		if(g_CVD_Status_3CS.cvd_prev_color_system != g_CVD_Status_3CS.cvd_next_state) // IF from no signal, do not re-setting cvd register to the same value

	// #4 	: State Change from No signal or Color System Change
	//		:
	if( (g_CVD_Status_3CS.cvd_prev_color_system != g_CVD_Status_3CS.cvd_next_state) || (g_CVD_Status_3CS.cvd_color_system==CVD_STATE_VideoNotReady) || ( g_CVD_Status_3CS.prev_av_rf_mode != g_CVD_Status_3CS.in_rf_mode) )
	{

		// #5 	: State Change from No signal, and different color system from previously locked color system OR AV/RF input source change.
		//		:
		//if( ( g_CVD_Status_3CS.cvd_prev_color_system != g_CVD_Status_3CS.cvd_next_state) || (MainCVD_Is_Prev_RF_Input != g_CVD_Status_3CS.in_rf_mode))
		CVD_CSD_DEBUG("Color System Change or Locked: prev system[%d], next[%d], cvd system[%d] ,port changed [%d], prev_rf[%d], in_rf[%d]\n", g_CVD_Status_3CS.cvd_prev_color_system ,g_CVD_Status_3CS.cvd_next_state, g_CVD_Status_3CS.cvd_color_system,  g_CVD_Status_3CS.port_change_detected,  g_CVD_Status_3CS.prev_av_rf_mode,  g_CVD_Status_3CS.in_rf_mode);

		if( ( g_CVD_Status_3CS.cvd_prev_color_system != g_CVD_Status_3CS.cvd_next_state) || (g_CVD_Status_3CS.port_change_detected == TRUE) || ( g_CVD_Status_3CS.prev_av_rf_mode != g_CVD_Status_3CS.in_rf_mode))
		{
			CVD_CSD_DEBUG("Setting CVD [%d]\n", g_CVD_Status_3CS.cvd_next_state);

			/*
			   if((g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) ||(g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSCj)|| (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC443) )
			   {
			   gEnable_SW3DCOMBControl = 1;
			   cvd_pe_color_system = LX_CVD_PQ_NTSC_M;
			   }
			   else
			   {
			   gEnable_SW3DCOMBControl = 0;
			   CVD_Set_motion_mode(0x1, 0x0) ;
			   cvd_pe_color_system = LX_CVD_PQ_PAL;
			   }

			   CVD_Set_PQ_Mode(cvd_pe_color_system);

*/
			{
				//AFE_PRINT("HDCT/CDCT Reset 1\n");
				CVD_Reset_hdct(1);
				CVD_Reset_cdct(1);
#ifdef CVD_COMB2D_ONLY_CONTROL
				/*
				//120718 : comb2d_only on control when color system change
				CVD_DEBUG("$$$ Comb2d only [1] $$$\n");
				CVD_Read_Buffer_Status(&rbuf1_empty, &rbuf2_empty, &rbuf3_empty, &rbuf4_empty, &wbuf_ful, &wbuf_empty);
				CVD_DEBUG("### rbuf1_empty[%d], rbuf2_empty[%d], rbuf3_empty[%d], rbuf4_empty[%d], wbuf_ful[%d], wbuf_empty[%d] #### \n", rbuf1_empty, rbuf2_empty, rbuf3_empty, rbuf4_empty, wbuf_ful, wbuf_empty);
				CVD_Set_comb2d_only(1);
				*/
#endif

				//						OS_MsecSleep(5);
			}

#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
			CVD_3DComb_Workaround(1);
#endif

			CVD_Set_Color_System_3CS(g_CVD_Status_3CS.cvd_next_state);
			//MainCVD_Prev_Written_Color_System = g_CVD_Status_3CS.cvd_next_state;
			g_CVD_Status_3CS.cvd_prev_color_system = g_CVD_Status_3CS.cvd_next_state;
			//MainCVD_Is_Prev_RF_Input = g_CVD_Status_3CS.in_rf_mode;

			{
				CVD_Reset_hdct(0);
				CVD_Reset_cdct(0);
			}

			// Move CVD PQ setting function from DDI to Kernel
			if(0) {
				if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) {
					if(g_CVD_Status_3CS.in_rf_mode == TRUE)
						CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_M_RF);
					else
						CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_M);

					CVD_Set_PE_Param_Flag(0x1, 0x1, g_CVD_Status_3CS.in_rf_mode, 1);
				}
				else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALi) {
					if(g_CVD_Status_3CS.in_rf_mode == TRUE)
						CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_RF);
					else
						CVD_Set_PQ_Mode(LX_CVD_PQ_PAL);

					CVD_Set_PE_Param_Flag(0x1, 0x2, g_CVD_Status_3CS.in_rf_mode, 1);
				}
				else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_SECAM) {
					if(g_CVD_Status_3CS.in_rf_mode == TRUE)
						CVD_Set_PQ_Mode(LX_CVD_PQ_SECAM_RF);
					else
						CVD_Set_PQ_Mode(LX_CVD_PQ_SECAM);

					CVD_Set_PE_Param_Flag(0x1, 0x3, g_CVD_Status_3CS.in_rf_mode, 1);
				}
				else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC443) {
					if(g_CVD_Status_3CS.in_rf_mode == TRUE)
						CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_443_RF);
					else
						CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_443);

					CVD_Set_PE_Param_Flag(0x1, 0x4, g_CVD_Status_3CS.in_rf_mode, 1);
				}
				else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PAL60) {
					if(g_CVD_Status_3CS.in_rf_mode == TRUE)
						CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_60_RF);
					else
						CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_60);

					CVD_Set_PE_Param_Flag(0x1, 0x7, g_CVD_Status_3CS.in_rf_mode, 1);
				}
				else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALm) {
					if(g_CVD_Status_3CS.in_rf_mode == TRUE)
						CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_M_RF);
					else
						CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_M);

					CVD_Set_PE_Param_Flag(0x1, 0x5, g_CVD_Status_3CS.in_rf_mode, 1);
				}
				else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALCn) {
					if(g_CVD_Status_3CS.in_rf_mode == TRUE)
						CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_NC_RF);
					else
						CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_NC);

					CVD_Set_PE_Param_Flag(0x1, 0x6, g_CVD_Status_3CS.in_rf_mode, 1);
				}
				else
					AFE_ERROR("ERROR Invalid Color system [%s][%d]\n", __func__, __LINE__);
			}
			g_CVD_Status_3CS.prev_av_rf_mode = g_CVD_Status_3CS.in_rf_mode;
		}
		// #6 	: State Change from No signal, and but same color system with previsouly locked system.
		//		: IF from VideoReadyToDetect, do not re-setting cvd register to the same value
		else
		{
#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
			CVD_3DComb_Workaround(1);
#endif
			CVD_CSD_DEBUG("Same system [%d] again\n", g_CVD_Status_3CS.cvd_next_state);
#ifdef CVD_COMB2D_ONLY_CONTROL
			/*
			//120718 : Disable comb2d_only when CVD signal detected according to the next color system
			CVD_DEBUG("$$$ Comb2d only [0] $$$\n");
			CVD_Set_comb2d_only(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state].reg_comb2d_only);
			*/
#endif
		}

		//	CVD_Force_Color_Kill(0);
#ifdef CVD_CH42_SKIP_WORKAROUND
		//141209 : PT NTSC C30 skip (philippine model)
		if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
		{
			CVD_Clamp_Current_Control(0);	// 1118 change clamp current to zero
		}
#endif

#if 0
#ifdef CVD_NTSC_NOISY_STABLE_VSYNC_WORKAROUND
		//For RF Signal
		if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
		{
			CVD_DEBUG("Status Noise [0x%x]\n", g_CVD_Status_3CS.status_noise);

			if( (g_CVD_Status_3CS.in_rf_mode == TRUE) \
					&& (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) && (g_CVD_Status_3CS.status_noise > 0x380 )
					&& (g_CVD_Status_3CS.cvd_chromalock_flag == 1) && (g_CVD_Status_3CS.h_lock_flag == 1) )
				CVD_Enable_LPF_en(1);
			else
				CVD_Enable_LPF_en(0);

			if ((g_CVD_Status_3CS.in_rf_mode == TRUE) )
				CVD_Hstart_Position_Compensator(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state]);
		}
#endif
#endif

#ifdef	CVD_STABLE_HSYNC_WORKAROUND //not used
		//For RF Signal
		if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
		{
			if( (g_CVD_Status_3CS.in_rf_mode == TRUE) \
					&& ( (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) || (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALm)) )
				CVD_Enable_Stable_Sync_Mode(1);		//for RF nosignal (dcrestore_lpf_en ON)
			else
				CVD_Enable_Stable_Sync_Mode(0);		//default state

			if ((g_CVD_Status_3CS.in_rf_mode == TRUE) )
				CVD_Hstart_Position_Compensator(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state]);
		}
#endif

#ifdef CVD_ENABLE_PALM_STABLE_SYNC_MODE //not used
		if ((g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) \
				&& (g_CVD_Status_3CS.in_atv_tunning == FALSE))
		{
			CVD_Set_PALm_Stable_HSync_Mode(1);
		}
#endif
#ifdef CVD_ENABLE_PALM_STABLE_SYNC_MODE //not used
		if ((g_CVD_Status_3CS.cvd_next_state != CVD_STATE_PALm) || (g_CVD_Status_3CS.in_rf_mode == FALSE) \
				|| (g_CVD_Status_3CS.in_atv_tunning == TRUE))
		{
			CVD_Set_PALm_Stable_VSync_Mode(0);
		}
#endif

		// Brazil color system change in menu !!!
#ifdef CVD_HSYNC_ENHANCEMENT
	CVD_Set_Hsync_Enhance(0);
#endif
#ifdef CVD_VSYNC_ENHANCEMENT
	CVD_Set_Vsync_Enhance(0);
#endif
		// IF signal_locked to same color system with previously locked color system, write PE params again
		if(1) {
			if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) {
				if(g_CVD_Status_3CS.in_rf_mode == TRUE)
					CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_M_RF);
				else
					CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_M);

				CVD_Set_PE_Param_Flag(0x1, 0x1, g_CVD_Status_3CS.in_rf_mode, 1);
			}
			else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALi) {
				if(g_CVD_Status_3CS.in_rf_mode == TRUE)
					CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_RF);
				else
					CVD_Set_PQ_Mode(LX_CVD_PQ_PAL);

				CVD_Set_PE_Param_Flag(0x1, 0x2, g_CVD_Status_3CS.in_rf_mode, 1);
			}
			else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_SECAM) {
				if(g_CVD_Status_3CS.in_rf_mode == TRUE)
					CVD_Set_PQ_Mode(LX_CVD_PQ_SECAM_RF);
				else
					CVD_Set_PQ_Mode(LX_CVD_PQ_SECAM);

				CVD_Set_PE_Param_Flag(0x1, 0x3, g_CVD_Status_3CS.in_rf_mode, 1);
			}
			else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC443) {
				if(g_CVD_Status_3CS.in_rf_mode == TRUE)
					CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_443_RF);
				else
					CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_443);

				CVD_Set_PE_Param_Flag(0x1, 0x4, g_CVD_Status_3CS.in_rf_mode, 1);
			}
			else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PAL60) {
				if(g_CVD_Status_3CS.in_rf_mode == TRUE)
					CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_60_RF);
				else
					CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_60);

				CVD_Set_PE_Param_Flag(0x1, 0x7, g_CVD_Status_3CS.in_rf_mode, 1);
			}
			else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALm) {
				if(g_CVD_Status_3CS.in_rf_mode == TRUE)
					CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_M_RF);
				else
					CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_M);

				CVD_Set_PE_Param_Flag(0x1, 0x5, g_CVD_Status_3CS.in_rf_mode, 1);
			}
			else if ( g_CVD_Status_3CS.cvd_next_state == CVD_STATE_PALCn) {
				if(g_CVD_Status_3CS.in_rf_mode == TRUE)
					CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_NC_RF);
				else
					CVD_Set_PQ_Mode(LX_CVD_PQ_PAL_NC);

				CVD_Set_PE_Param_Flag(0x1, 0x6, g_CVD_Status_3CS.in_rf_mode, 1);
			}
			else
				AFE_ERROR("ERROR Invalid Color system [%s][%d]\n", __func__, __LINE__);
		}
	}
	else
	{
		//
		CVD_Set_PE_Param_Flag(0x1, -1, g_CVD_Status_3CS.in_rf_mode, -1);
	}
	//Program_Color_System_Main_only_system_set(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state]);
	//SW reset is needed here???
	//CVD_SW_Reset(LX_CVD_MAIN);
	//gMainCVD_State = g_CVD_Status_3CS.cvd_next_state;
	return 0;
}

static int CVD_Setting_State_Change_to_No_Signal(void)
{
	_CVD_NoSignal_Time = jiffies_to_msecs(jiffies);
	/* Cpump Auto Stip to 0 : default for no signal white noise */
	/* Cpump_Auto_Stip should be '1' : White saturation on normal signal */
	//CVD_Set_Cpump_Auto_Stip_Value(0);

#ifdef CVD_CH42_SKIP_WORKAROUND
	CVD_Clamp_Current_Control(0x3);	// 1118 enlarge clamp current in no sigal state
#endif
	// Disable due to 33% sync level test
	/*
	   if ( (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.use_internal_demod) )	// if using internal demod
	   CVD_Set_Cpump_Auto_Stip_Mode(3);
	   */

#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	//			CVD_3DComb_Workaround(0);
#ifdef CVD_CDTO_CONTROL
	CVD_3DComb_Workaround(4);
#endif
#endif

	g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoNotReady;

#ifdef	CVD_VDCT_WA_FOR_FAST_VLINE_DETECTION
	CVD_Reset_vdct(1);
	//			OS_MsecSleep(5);
	CVD_Reset_vdct(0);
#endif

#ifdef CVD_COMB2D_ONLY_CONTROL
#if 0
	//120705 : Enable comb2d_only when no signal detected !!!
	CVD_DEBUG("### Comb2d only [1] [%s][%d] ###\n",__func__, __LINE__ );
	//CVD_Read_Buffer_Status(&rbuf1_empty, &rbuf2_empty, &rbuf3_empty, &rbuf4_empty, &wbuf_ful, &wbuf_empty);
	//CVD_DEBUG("### rbuf1_empty[%d], rbuf2_empty[%d], rbuf3_empty[%d], rbuf4_empty[%d], wbuf_ful[%d], wbuf_empty[%d] #### \n", rbuf1_empty, rbuf2_empty, rbuf3_empty, rbuf4_empty, wbuf_ful, wbuf_empty);
	CVD_Set_comb2d_only(1);
	CVD_Set_comb2d_only_md(1);
#endif
#endif

	//gogosing agc :121206
#ifdef CVD_ADAPTIVE_AGC_PEAK_EN_CONTROL
	//		CVD_AGC_Peak_En_Control(0, 0, 0); //force off peak_en
	//		CVD_agc_half_en_control(1);//gogosing agc
#endif

#ifdef CVD_HSYNC_ENHANCEMENT
	CVD_Set_Hsync_Enhance(0);
#endif
#ifdef CVD_VSYNC_ENHANCEMENT
	CVD_Set_Vsync_Enhance(0);
#endif

	CVD_Set_PE_Param_Flag(0x0, -1, g_CVD_Status_3CS.in_rf_mode, -1);

	CVD_Set_Nosignal_Vactive_Params();

	return 0;
}


static int CVD_Update_Status_Variables(void)
{
	//LX_AFE_CVD_PQ_MODE_T	cvd_pe_color_system;
	int loop, avg_tmp = 0;
	int	agc_gain_tmp = 0;
	int vline_625_sum = 0;
	static UINT16	vline_625_array[CVD_VFREQ_STABLE_COUNT] = {0,};
	static UINT16	status_noise_array[8] = {0,};
	static UINT16	status_agc_gain_array[8] = {0,};

	/* Read Status CVD Registers */
	CVD_Update_Status_Regs(&g_CVD_Status_3CS);

	/* Checking  Unlock Interrupt  */
	if(g_CVD_Status_3CS.no_signal_intr)
	{
		g_CVD_Status_3CS.no_signal_flag = 1;
		g_CVD_Status_3CS.no_signal_intr = 0;
		CVD_DEBUG("no signal intr !\n");
	}
	if(g_CVD_Status_3CS.h_unlock_intr)
	{
		g_CVD_Status_3CS.h_lock_flag = 0;
		g_CVD_Status_3CS.h_unlock_intr = 0;
		CVD_DEBUG("h-unlock intr !\n");
	}
	if(g_CVD_Status_3CS.v_unlock_intr)
	{
		g_CVD_Status_3CS.v_lock_flag = 0;
		g_CVD_Status_3CS.v_unlock_intr = 0;
		CVD_DEBUG("v-unlock intr !\n");
	}

	/*
	   if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
	   CVD_AGC_Bypass_Function((UINT32)g_CVD_Status_3CS.status_noise, (UINT32)g_CVD_Status_3CS.h_lock_flag, (UINT32)g_CVD_Status_3CS.no_signal_flag );
	 */

	for(loop = (CVD_VFREQ_STABLE_COUNT - 1) ;loop > 0;loop--) {
		vline_625_array[loop] = vline_625_array[loop-1] ;
		vline_625_sum += vline_625_array[loop];
	}
	vline_625_array[0] = g_CVD_Status_3CS.vline_625_reg;
	vline_625_sum += vline_625_array[0];

	if(vline_625_sum >= CVD_VFREQ_STABLE_COUNT )	// stable 625 line : 50Hz
		g_CVD_Status_3CS.vline_625_stable = 1;
	else if(vline_625_sum == 0 )	// stable 525 line : 60Hz
		g_CVD_Status_3CS.vline_625_stable = 0;

	AFE_TRACE("vline_625_reg[%d], vline_625_sum[%d] , vline_625_stable[%d] \n", g_CVD_Status_3CS.vline_625_reg, vline_625_sum, g_CVD_Status_3CS.vline_625_stable);

	for(loop = 7;loop > 0;loop--) {
		status_noise_array[loop] = status_noise_array[loop-1] ;
		avg_tmp += status_noise_array[loop];
	}
	status_noise_array[0] = g_CVD_Status_3CS.status_noise;
	avg_tmp += status_noise_array[0];

	g_CVD_Status_3CS.avg_status_noise = avg_tmp >> 3;

	for(loop = 7;loop > 0;loop--) {
		status_agc_gain_array[loop] = status_agc_gain_array[loop-1] ;
		agc_gain_tmp += status_agc_gain_array[loop];
	}
	status_agc_gain_array[0] = g_CVD_Status_3CS.status_agc_gain;
	agc_gain_tmp += status_agc_gain_array[0];

	g_CVD_Status_3CS.avg_status_agc_gain = agc_gain_tmp >> 3;

	return 0;
}

static int CVD_Workaround_Stable_Count_More_Than_20(void)
{
#ifdef CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC

	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)  && (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
		g_CVD_Status_3CS.gHstateMaxCounter++;
		if(CVD_Read_VCR_Detected() && (CVD_Get_Global_Motion_Value() > 0x10)  && (g_CVD_Status_3CS.hnon_standard_flag == 0) ) // When Global Motion Value is high
			g_CVD_Status_3CS.vcr_detect_count++;

		if(g_CVD_Status_3CS.gHstateMaxCounter >= 20)
		{
			if ( ( g_CVD_Status_3CS.vcr_detect_count >=  CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD ) && !g_CVD_Pattern_Detection_t.static_pattern_found)
			{
				if ( CVD_Get_Hstate_Max() > 3)
				{
					CVD_WA_DEBUG("VCR Detected [%d/%d] \n", g_CVD_Status_3CS.vcr_detect_count, g_CVD_Status_3CS.gHstateMaxCounter);
#ifdef CVD_HSYNC_ENHANCEMENT
					CVD_Set_Hsync_Enhance(0);
#endif
					CVD_Set_Hstate_Max(3);
					CVD_Set_Hstate_Fixed(0);
				}
				else
					CVD_WA_DEBUG("VCR Not Detected [%d/%d] \n", g_CVD_Status_3CS.vcr_detect_count, g_CVD_Status_3CS.gHstateMaxCounter);
			}
			// removed due to hsync unstable when vcr detected/not detected toggling
#if 0
			else if ( CVD_Get_Hstate_Max() < 5)
			{
				CVD_WA_DEBUG("VCR Not Detected [%d/%d] \n", g_CVD_Status_3CS.vcr_detect_count, g_CVD_Status_3CS.gHstateMaxCounter);
				CVD_Set_Hstate_Max(5);
			}
#endif

			g_CVD_Status_3CS.gHstateMaxCounter = 0;
			g_CVD_Status_3CS.vcr_detect_count = 0;
		}
	}
#endif

#ifdef CVD_ADAPTIVE_BURST_GATE_END_MODE
	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE)  )
	{
		if(g_CVD_Status_3CS.gAdaptive_Burst_Gate_Counter == 0)
		{
			if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
				g_CVD_Status_3CS.gVariance_Status_Cdto_Inc = CVD_Differential_Status_Cdto_Inc_Value();
				g_CVD_Status_3CS.gAccumulated_Cordic_Freq_Value = CVD_Read_Cordic_Freq_Value();
			}
			g_CVD_Status_3CS.gAdaptive_Burst_Gate_Counter++;
		}
		else if(g_CVD_Status_3CS.gAdaptive_Burst_Gate_Counter < CVD_ADAPTIVE_BURST_GATE_COUNT_ITERATION)
		{
			if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
				g_CVD_Status_3CS.gVariance_Status_Cdto_Inc += CVD_Differential_Status_Cdto_Inc_Value();
				g_CVD_Status_3CS.gAccumulated_Cordic_Freq_Value += CVD_Read_Cordic_Freq_Value();
			}
			g_CVD_Status_3CS.gAdaptive_Burst_Gate_Counter++;
		}
		else if(g_CVD_Status_3CS.gAdaptive_Burst_Gate_Counter >= CVD_ADAPTIVE_BURST_GATE_COUNT_ITERATION)
		{
			if((g_CVD_Status_3CS.gVariance_Status_Cdto_Inc >= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_0)&&(g_CVD_Status_3CS.gAccumulated_Cordic_Freq_Value >= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_1))
				g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable = 1;
			else if(g_CVD_Status_3CS.gVariance_Status_Cdto_Inc <= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_3)
				g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable = 0;
			else
				g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable = 2;

			if((g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable == g_CVD_Status_3CS.Prev_Adaptive_Burst_Gate_Enable)&&(g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable != 2))
			{
				CVD_Set_for_Burst_Gate_End_On_Noisy(pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALm].reg_burst_gate_end_new ,g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable);
				/* added to prevent unstable brightness */
				CVD_Set_Cpump_Auto_Stip_Noisy_Value(0);
#ifdef CVD_BYPASS_AGC_ON_ADAPTIVE_BURST_GATE_END_MODE
				CVD_AGC_Bypass(g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable);
#endif
			}
			g_CVD_Status_3CS.Prev_Adaptive_Burst_Gate_Enable = g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable;

			//AFE_PRINT("AVERAGE CDTO_INC[%x] CORDIC_FREQ[%d] RESULT[%d]\n", g_CVD_Status_3CS.gVariance_Status_Cdto_Inc, g_CVD_Status_3CS.gAccumulated_Cordic_Freq_Value, g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable );
			g_CVD_Status_3CS.gAdaptive_Burst_Gate_Counter = 0;
		}
	}
#endif
	/* On Brazil (PAL-M) weak RF Signal, AGC gain sometimes became high value result in white picture.
	   Disabling AGC is needed on this weak RF signal( No h-lock, high noise level )
	   */
	if( (g_CVD_Status_3CS.in_atv_tunning == FALSE) && (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm))
		CVD_AGC_Bypass_Function((UINT32)g_CVD_Status_3CS.avg_status_noise, (UINT32)g_CVD_Status_3CS.h_lock_flag, (UINT32)g_CVD_Status_3CS.no_signal_flag );

	return 0;
}

static int CVD_Workaround_Stable_Count_20(void)
{

#ifdef CVD_CH42_SKIP_WORKAROUND
	// protection code for clamp count/step for stable state
	if ( (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.use_internal_demod) )	// if using internal demod
		CVD_Clamp_Current_Control(0x0);
#endif

	// Disable due to 33% sync level test
	// 130911 : restore cpmup_auto_stip_mode to default value
	//CVD_Set_Cpump_Auto_Stip_Mode(2);

	/*
	   CVD_DEBUG("chromalock[%d], chromalock_count[%d]\n", g_CVD_Status_3CS.cvd_chromalock_flag, chromalock_count);
	   if( (g_CVD_Status_3CS.cvd_chromalock_flag) || (chromalock_count > 3))	// burst exist???
	   {
	   CVD_Program_Color_System_PostJob(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state]);
	   }
	   */
#ifdef CVD_FAST_3DCOMB_WORKAROUND
	//CVD_Set_HNon_Standard_Threshold(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3.cvd_color_system].reg_hnon_std_threshold);
	//Enable vf_nstd_en on same state 2
	//CVD_vf_nstd_control(1);	//default value when state changed
#endif
#ifdef CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
		if ( ( ( g_CVD_Status_3CS.vcr_detect_count >=  CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD ) || (CVD_Get_HDTO_difference() > 0x20000) ) \
			&& !g_CVD_Pattern_Detection_t.static_pattern_found)
		{
			CVD_WA_DEBUG("VCR Detected [%d] \n", g_CVD_Status_3CS.vcr_detect_count);
#ifdef CVD_HSYNC_ENHANCEMENT
			CVD_Set_Hsync_Enhance(0);
#endif
			CVD_Set_Hstate_Max(3);
			CVD_Set_Hstate_Fixed(0);
		}
		else {
			CVD_WA_DEBUG("VCR Not Detected [%d] \n", g_CVD_Status_3CS.vcr_detect_count);
			CVD_Set_Hstate_Max(5);
			CVD_Set_Hstate_Fixed(1);
		}
		g_CVD_Status_3CS.vcr_detect_count = 0;
		g_CVD_Status_3CS.gHstateMaxCounter = 0;
	}
#endif

	//				CVD_DEBUG("### CVD Same State Max 2 !!! ###\n");

#ifdef CVD_ADAPTIVE_BURST_GATE_END_MODE
	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
		if((g_CVD_Status_3CS.gVariance_Status_Cdto_Inc >= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_0)&&(g_CVD_Status_3CS.gAccumulated_Cordic_Freq_Value >= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_1))
			g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable = 1;
		else if(g_CVD_Status_3CS.gVariance_Status_Cdto_Inc <= CVD_ADAPTIVE_BURST_GATE_THRESHOLD_3)
			g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable = 0;
		else
			g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable = 2;

		if((g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable == g_CVD_Status_3CS.Prev_Adaptive_Burst_Gate_Enable)&&(g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable != 2))
		{
			CVD_Set_for_Burst_Gate_End_On_Noisy( pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALm].reg_burst_gate_end_new , g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable);
			/* added to prevent unstable brightness */
			CVD_Set_Cpump_Auto_Stip_Noisy_Value(0);
#ifdef CVD_BYPASS_AGC_ON_ADAPTIVE_BURST_GATE_END_MODE
			CVD_AGC_Bypass(g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable);
#endif
		}
		//AFE_PRINT("AVERAGE CDTO_INC[%x] CORDIC_FREQ[%d] RESULT[%d]\n", g_CVD_Status_3CS.gVariance_Status_Cdto_Inc, g_CVD_Status_3CS.gAccumulated_Cordic_Freq_Value, g_CVD_Status_3CS.Adaptive_Burst_Gate_Enable);
		g_CVD_Status_3CS.gAdaptive_Burst_Gate_Counter = 0;
	}
#endif
#ifdef CVD_ADAPTIVE_AGC_PEAK_EN_CONTROL
	//		CVD_AGC_Peak_En_Control(2, 0, 0);	// force on peak_en
#endif

#ifdef	CVD_STABLE_HSYNC_WORKAROUND //not used
	avg_noise_level = g_CVD_Status_3CS.cvd_noise_sum / (g_CVD_Status_3CS.cvd_lock_stable_count + 1);
	//Stable Hsync for NTSC RF Field Streams
	if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE))
	{
		CVD_DEBUG("### avg noise level[0x%x],burst mag[0x%x] at stable20 #\n", avg_noise_level, g_CVD_Status_3CS.cvd_burst_mag);
		if( (avg_noise_level > 0x240) && (g_CVD_Status_3CS.cvd_burst_mag > 0x1800) )	// for NS Home-shopping field stream
			CVD_Enable_Stable_Sync_Mode(3);
	}
#endif
#ifdef CVD_ENABLE_PALM_STABLE_SYNC_MODE //not used
	avg_noise_level = g_CVD_Status_3CS.cvd_noise_sum / (g_CVD_Status_3CS.cvd_lock_stable_count + 1);
	if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE)	\
			&& (avg_noise_level > 0x3F0))
	{

		CVD_DEBUG("### avg noise level at stable20 [0x%x]#\n", avg_noise_level);
		CVD_Set_PALm_Stable_VSync_Mode(1);
	}
	else
		CVD_Set_PALm_Stable_VSync_Mode(0);
#endif

#ifdef	CVD_PAL_STABLE_VSYNC_WORKAROUND// not used
	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi)&& (g_CVD_Status_3CS.in_rf_mode == TRUE)\
			&& (g_CVD_Status_3CS.in_atv_tunning == FALSE)) 
		CVD_Set_Vsync_Cntl(&pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALi], 2);	// PLL vsync
#endif

#ifdef CVD_HSYNC_ENHANCEMENT
	// hsync_enhance for pali is set in stable_count '1'
	// if hstate_max is '3' , vcr mode is detected and hsync enhance should be disabled
	if ( ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) || (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) || (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi))\
			&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE) && ( CVD_Get_Hstate_Max() != 3) )
	{
		if(g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)
			CVD_Set_Hsync_Enhance(1);
		else if(g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm)
			CVD_Set_Hsync_Enhance(2);
	}
	else
		CVD_Set_Hsync_Enhance(0);
#endif
#ifdef CVD_VSYNC_ENHANCEMENT
	if ( (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE))
	{
		if(g_CVD_Status_3CS.vline_625_reg)	//576i system
			CVD_Set_Vsync_Enhance(2);
		else
			CVD_Set_Vsync_Enhance(1);
	}
	else
		CVD_Set_Vsync_Enhance(0);
#endif

	g_CVD_Status_3CS.cvd_lock_stable_count++;

	AFE_PRINT("CVD Lock Stable : NO[%d],HL[%d],VL[%d],V625[%d],PAL[%d],SEC[%d],ChL[%d],cor_fr[%d],noi[%d],nobu[%d],c_state[%d],st_cnt[%d],hn[%d],vn[%d],tun[%d],rf[%d],no_cnt[%d]\n",g_CVD_Status_3CS.no_signal_flag, g_CVD_Status_3CS.h_lock_flag, g_CVD_Status_3CS.v_lock_flag, g_CVD_Status_3CS.vline_625_flag, g_CVD_Status_3CS.cvd_pal_flag, g_CVD_Status_3CS.cvd_secam_flag, g_CVD_Status_3CS.cvd_chromalock_flag, g_CVD_Status_3CS.cvd_cordic_freq, g_CVD_Status_3CS.status_noise, g_CVD_Status_3CS.no_burst_flag, g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cvd_lock_stable_count, g_CVD_Status_3CS.hnon_standard_flag, g_CVD_Status_3CS.vnon_standard_flag ,g_CVD_Status_3CS.in_atv_tunning, g_CVD_Status_3CS.in_rf_mode, g_CVD_Status_3CS.cvd_no_signal_count);

	return 0;
}

static int CVD_Workaround_Stable_Count_1(void)
{
	//150811 : suwon CH30 hsync unstable
	int hdto_diff = 0;

	hdto_diff = CVD_Get_HDTO_difference();

	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (hdto_diff > 0x20000) && !g_CVD_Pattern_Detection_t.static_pattern_found)
	{
		AFE_PRINT("NTSC Hsync Unstable : HDTO [0x%x], static pattern [%d]\n", hdto_diff , g_CVD_Pattern_Detection_t.static_pattern_found );

		// fix brazil US-D (pyuntaek) color unstable (reg_fixed_cstate to '1', reg_cstate to '7')
		if ( (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE) )
			CVD_Program_Color_System_PostJob(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system]);
	}

	CVD_Init_Level_Detector(g_CVD_Status_3CS.cvd_color_system);

#ifdef CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
	if ( (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE))	//150918 : Hstate_max to 3 for AV input(SS SV-7000W)
		CVD_Set_Hstate_Max(5);
#endif
#ifdef CVD_HSYNC_ENHANCEMENT
	if ( ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE) && ( CVD_Get_Hstate_Max() != 3) ) && (hdto_diff < 0x20000) )
		CVD_Set_Hsync_Enhance(1);	// for CH-17 NTCS gumi stream : setting hsync_enhance can shift picture
#endif
#ifdef CVD_HSYNC_ENHANCEMENT
	// PT EU-05 hsync unstable : TVHWQ-74000
	// if hstate_max is '3' , vcr mode is detected and hsync enhance should be disabled
	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi)\
			&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE) && ( CVD_Get_Hstate_Max() != 3) )
	{
		CVD_Set_Hsync_Enhance(3);
	}
#endif

#ifdef CVD_DONT_KILL_CHROMALOCK_ON_CLOCK_LOST
	/*
	   if( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
	   CVD_OnOff_Chromalock_Ckill(0);
	   */
#endif
#ifdef	CVD_STABLE_HSYNC_WORKAROUND //not used
	if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE))
	{
		CVD_Enable_Stable_Sync_Mode(2);
	}
#endif

	//121206
#ifdef CVD_ADAPTIVE_AGC_PEAK_EN_CONTROL
	/* agc_peak_en control moved to "Stable Count 1 + 2" */
	//CVD_AGC_Peak_En_Control(2, 0, 0); // force on peak_en //gogosing agc

	/* 131219 : disable agc half en control : dark video after channel change (from no signal)*/
	/*
	   if( g_CVD_Status_3CS.in_rf_mode == TRUE )
	   {
	   if(!g_CVD_Status_3CS.use_internal_demod)	// if using internal demod, agc_half_en should be '1'
	   CVD_agc_half_en_control(0);//gogosing agc
	   }
	   */
#endif
	//					CVD_DEBUG("### CVD Same State Max 1 !!! ###\n");

	//won.hur : added chip selection for L9B0
	//@2011.08.24
#ifdef CVD_FAST_3DCOMB_WORKAROUND
	// Disable vf_nstd_en on stable state.(WA for 3DComb buffer control error)
	CVD_vf_nstd_control(0);	//for fast 3DComb operation
	// Set hnon_std_threshold values on stable state.(WA for 3DComb buffer control error)
	CVD_Set_HNon_Standard_Threshold(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_hnon_std_threshold);
#endif

#ifdef CVD_CHANGE_FIELD_DETECT_MODE_ON_DONG_GO_DONG_RAK
	if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
		CVD_Set_for_Field_Detect_Mode(1);
#endif
	//CVD_Program_Color_System_PostJob(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state]);

#ifdef CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
	if ( ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) || (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi) )&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
		//150811 : suwon CH30 hsync unstable
		if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (hdto_diff > 0x20000) )
		{
//			AFE_PRINT("NTCS Hsync Unstable : HDTO [0x%x], static pattern [%d]\n", CVD_M14Bx_Get_HDTO_difference(), g_CVD_Pattern_Detection_t.static_pattern_found );
		}
		else
		{
			CVD_DEBUG("Set hstate_fixed value to 1 \n");
			CVD_Set_Hstate_Fixed(1);
		}
		if(g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)
		{	
			/* US-09 No-Burst Crosshatch shift problem after channel change */
			//CVD_Set_Hstate_Max(3);
			g_CVD_Status_3CS.vcr_detect_count = 0;
		}
	}
#endif
#ifdef CVD_ADAPTIVE_BURST_GATE_END_MODE
	if ((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
		g_CVD_Status_3CS.gVariance_Status_Cdto_Inc = CVD_Differential_Status_Cdto_Inc_Value();
		g_CVD_Status_3CS.gAccumulated_Cordic_Freq_Value = CVD_Read_Cordic_Freq_Value();
	}
#endif

	g_CVD_Status_3CS.cvd_lock_stable_count++;
#ifdef CVD_CH42_SKIP_WORKAROUND
	//CVD_Clamp_Current_Control(0);	// 1118 change clamp current to zero
#endif
	//120222 : setting agc_peak_en initial values
	// PALi & SECAM RF : initially off
	// NTSC & others : initially on
#ifdef CVD_ADAPTIVE_AGC_PEAK_EN_CONTROL
	//				CVD_AGC_Peak_En_Control(0, 0, 0);	//force off peak_en
#endif

#ifdef	CVD_PAL_STABLE_VSYNC_WORKAROUND// not used
	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi)&& (g_CVD_Status_3CS.in_rf_mode == TRUE)\
			&& (g_CVD_Status_3CS.in_atv_tunning == FALSE)) 
		CVD_Set_Vsync_Cntl(&pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALi], 1);	// vsync_l_cnt & vactive_start
#endif
	return 0;
}

static int CVD_Workaround_Stable_Count_Less_Than_20(void) 
{
	if( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_SECAM) && (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Adaptive_Burst_WA_for_SECAM == 1))
		CVD_Workaround_SECAM_Burst_Position();

	if(g_CVD_Status_3CS.cvd_lock_stable_count == 1)
	{
		_CVD_LockedStable_Time = jiffies_to_msecs(jiffies);
		CVD_DEBUG("CVD Locked Stable time from NoSignal [%d]msec, from Signal-Lock [%d]msec\n",\
				_CVD_LockedStable_Time - _CVD_NoSignal_Time, _CVD_LockedStable_Time - _CVD_SignalLocked_Time);
	}
#ifdef	CVD_3DCOMB_ERROR_WORKAROUND
	if(g_CVD_Status_3CS.cvd_lock_stable_count == 0)
	{
		CVD_Program_Color_System_Size(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system]);
		CVD_3DComb_Workaround(2);
		CVD_Program_Color_System_Size_md(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system]);
		CVD_3DComb_Workaround(3);
	}
#ifdef CVD_CDTO_CONTROL
	else if(g_CVD_Status_3CS.cvd_lock_stable_count == 1)
		CVD_3DComb_Workaround(4);
#endif
#endif

#ifdef CVD_ADAPTIVE_BURST_GATE_END_MODE
	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALm) && (g_CVD_Status_3CS.in_rf_mode == TRUE) ) {
		g_CVD_Status_3CS.gVariance_Status_Cdto_Inc += CVD_Differential_Status_Cdto_Inc_Value();
		g_CVD_Status_3CS.gAccumulated_Cordic_Freq_Value += CVD_Read_Cordic_Freq_Value();
	}
#endif
#ifdef CVD_HSTATE_FIXED_CONTROL_FOR_STABLE_SYNC
	if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
		if(CVD_Read_VCR_Detected() && (CVD_Get_Global_Motion_Value() > 0x10)  && (g_CVD_Status_3CS.hnon_standard_flag == 0) ) // When Global Motion Value is high
			g_CVD_Status_3CS.vcr_detect_count++;
	}

	if(g_CVD_Status_3CS.cvd_lock_stable_count == 10)
	{
		// CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD : 2=>4 
		if ( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)&& (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.in_atv_tunning == FALSE)) {
			if ( ( (g_CVD_Status_3CS.vcr_detect_count+1 >= CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD>>1) || (CVD_Get_HDTO_difference() > 0x20000) ) \
				&& !g_CVD_Pattern_Detection_t.static_pattern_found)
			{
				CVD_WA_DEBUG("VCR Detected [%d/%d] \n", g_CVD_Status_3CS.vcr_detect_count+1, CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD>>1);
				CVD_Set_Hstate_Max(3);
				CVD_Set_Hstate_Fixed(0);
#ifdef CVD_HSYNC_ENHANCEMENT
				CVD_Set_Hsync_Enhance(0);
#endif
			}
			else {
				CVD_WA_DEBUG("VCR Not Detected [%d/%d] \n", g_CVD_Status_3CS.vcr_detect_count+1, CVD_HSTATE_FIX_VCR_COUNT_THRESHOLD>>1);
				CVD_Set_Hstate_Max(5);
				CVD_Set_Hstate_Fixed(1);
			}
		}
	}

#endif
	if(g_CVD_Status_3CS.cvd_lock_stable_count > (CVD_STABLE_COUNT_1 + 1) )
	{
		/*
		   if( (CVD_Get_comb2d_only() == 0) && CVD_Get_comb2d_only_md() )
		   {
		   CVD_DEBUG("$$$ Comb2d only MD [0] : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
		   CVD_Set_comb2d_only_md(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state].reg_comb2d_only);
		   }
		   else if(g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag && g_CVD_Status_3CS.cvd_chromalock_flag && CVD_Get_comb2d_only()\
		   && (g_CVD_Status_3CS.hnon_standard_flag == 0) && (g_CVD_Status_3CS.vnon_standard_flag == 0) )
		   {
		   CVD_DEBUG("$$$ Comb2d only [0] : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
		   CVD_Set_comb2d_only(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state]->reg_comb2d_only);
		   }
		   */
		if(g_CVD_Status_3CS.h_lock_flag && g_CVD_Status_3CS.v_lock_flag && g_CVD_Status_3CS.cvd_chromalock_flag && CVD_Get_comb2d_only()\
				&& (g_CVD_Status_3CS.hnon_standard_flag == 0) && (g_CVD_Status_3CS.vnon_standard_flag == 0) )
		{
#if 0
#ifdef CVD_COMB2D_ONLY_CONTROL
			CVD_DEBUG("$$$ Comb2d only [0] : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
			CVD_Set_comb2d_only(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state].reg_comb2d_only);
			CVD_DEBUG("$$$ Comb2d only MD [0] : stable count[%d]$$$\n", g_CVD_Status_3CS.cvd_lock_stable_count);
			CVD_Set_comb2d_only_md(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state].reg_comb2d_only);
#endif
#ifdef CVD_FAST_3DCOMB_WORKAROUND
			// Disable vf_nstd_en on stable state.(WA for 3DComb buffer control error)
			CVD_vf_nstd_control(0);	//for fast 3DComb operation
			// Set hnon_std_threshold values on stable state.(WA for 3DComb buffer control error)
			CVD_Set_HNon_Standard_Threshold(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_hnon_std_threshold);
#endif
#endif
		}
	}

	// ELF E-808 green vertical noise (wrong 3DComb memory alignment due-to faster v-freq 59.98)
	if((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)&& (g_CVD_Status_3CS.in_rf_mode == FALSE)) 
	{
		if(g_CVD_Status_3CS.cvd_lock_stable_count == 1)
			g_CVD_Status_3CS.hdto_abnormal_count = 0;
		else if ((CVD_Get_HDTO_difference() > 0x50000) )
		{
				g_CVD_Status_3CS.hdto_abnormal_count++;
				CVD_WA_DEBUG("!!! hdct abnormal [%d/%d] \n", g_CVD_Status_3CS.hdto_abnormal_count, g_CVD_Status_3CS.cvd_lock_stable_count);
		}

		if ( g_CVD_Status_3CS.cvd_lock_stable_count == 10)
		{
			if ( g_CVD_Status_3CS.hdto_abnormal_count > 5 )
			{
				CVD_WA_DEBUG("hdct abnormal [%d/%d] : force vcr \n", g_CVD_Status_3CS.hdto_abnormal_count, g_CVD_Status_3CS.cvd_lock_stable_count);
				CVD_Set_force_vcr(1);
			}
		}
		else if ( g_CVD_Status_3CS.cvd_lock_stable_count == 19)
		{
			if ( g_CVD_Status_3CS.hdto_abnormal_count > 13 )
			{
				CVD_WA_DEBUG("hdct abnormal [%d/%d] : force vcr  \n", g_CVD_Status_3CS.hdto_abnormal_count, g_CVD_Status_3CS.cvd_lock_stable_count);
				CVD_Set_force_vcr(1);
			}
		}
	}

	g_CVD_Status_3CS.cvd_lock_stable_count++;

	return 0;
}

static int CVD_Workaround_Stable_Count_3(void)
{
	if((g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC)&& (g_CVD_Status_3CS.in_rf_mode == FALSE)) 
	{
		CVD_Set_vcr_auto_switch_en(1);
	}
#ifdef CVD_ADAPTIVE_AGC_PEAK_EN_CONTROL
	CVD_AGC_Peak_En_Control(2, 0, 0); // force on peak_en //gogosing agc

	/* 131219 : disable agc half en control : dark video after channel change (from no signal)*/
	/*
	   if( g_CVD_Status_3CS.in_rf_mode == TRUE )
	   {
	   if(!g_CVD_Status_3CS.use_internal_demod)	// if using internal demod, agc_half_en should be '1'
	   CVD_agc_half_en_control(0);//gogosing agc
	   }
	   */
#endif
	g_CVD_Status_3CS.cvd_lock_stable_count++;

	CVD_SetUnlockInterrupt(1);

	AFE_PRINT("CVD Lock : NO[%d],HL[%d],VL[%d],c_state[%d],st_cnt[%d]",g_CVD_Status_3CS.no_signal_flag, g_CVD_Status_3CS.h_lock_flag, g_CVD_Status_3CS.v_lock_flag ,g_CVD_Status_3CS.cvd_color_system, g_CVD_Status_3CS.cvd_lock_stable_count);

	return 0;
}

static int CVD_Workaround_Stable_Count_5(void)
{

#ifdef CVD_NTSC_NOISY_STABLE_VSYNC_WORKAROUND
	//For RF Signal
	if(g_CVD_Status_3CS.in_atv_tunning == FALSE)
	{
		CVD_DEBUG("Status Noise [0x%x]\n", g_CVD_Status_3CS.status_noise);

		if( (g_CVD_Status_3CS.in_rf_mode == TRUE) \
				&& (g_CVD_Status_3CS.cvd_next_state == CVD_STATE_NTSC) && (g_CVD_Status_3CS.status_noise > 0x380 )
				&& (g_CVD_Status_3CS.cvd_chromalock_flag == 1) && (g_CVD_Status_3CS.h_lock_flag == 1) )
			CVD_Enable_LPF_en(1);
		else
			CVD_Enable_LPF_en(0);

		if (g_CVD_Status_3CS.in_rf_mode == TRUE)
			CVD_Hstart_Position_Compensator(&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_next_state]);
	}
#endif

	g_CVD_Status_3CS.cvd_lock_stable_count++;

	return 0;
}

static int CVD_Workaround_Stable_Count_More_Than_1(void)
{
	static int prev_black_level = -1;

	CVD_Workaround_Low_Burst_Magnitude();

	if (( g_CVD_Pattern_Detection_t.bEnable == TRUE) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
		CVD_Pattern_Detection(&g_CVD_Pattern_Detection_t );
#if 1
	//gogosing burst mag status check for color burst level test (color 틀어짐 대응) 2011.06.11
	//Apply cagc control for NTSC(color 틀어짐 대응) 2011.10.14
	if( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_PALi) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
	{
		CVD_Workaround_PAL_RF_CGAC();
	}
	else if( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) )
	{
		CVD_Workaround_NTSC_RF_CGAC();
	}
	else if( (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == FALSE) )	// For NTSC AV
	{
		CVD_Workaround_NTSC_AV_CGAC();
	}
	else
	{
		/*
		   g_CVD_Status_3CS.burst_mag_prev=0;//pal 이외 시스템에서 초기화
		   g_CVD_Status_3CS.burst_mag_next=0;
		   */
	}

	if( g_CVD_Status_3CS.in_rf_mode == FALSE )	// For SCART Black Level Control
	{

		if(prev_black_level != g_CVD_Status_3CS.cvd_black_level)
		{
			CVD_DEBUG("SCART Black Level to [%d]\n", g_CVD_Status_3CS.cvd_black_level);

			if(g_CVD_Status_3CS.cvd_black_level == LX_AFE_CVD_BLACK_LEVEL_HIGH)
			{
				CVD_Set_SCART_CSC(1);
			}
			else if(g_CVD_Status_3CS.cvd_black_level == LX_AFE_CVD_BLACK_LEVEL_LOW)
			{
				CVD_Set_SCART_CSC(0);
			}
			else
			{
			}
			prev_black_level = g_CVD_Status_3CS.cvd_black_level;
		}
	}
#endif

	return 0;
}

static int CVD_Workaround_Low_Burst_Magnitude(void)
{
	// For NTSC RF(F1_8_579.00 : RGB Dot Noise)
	// Low Burst Magnitude
	if(g_CVD_Status_3CS.cvd_lock_stable_count < (CVD_STABLE_COUNT_1 + 3) )
	{
		// set to default
		_g_cagc_for_ntscj = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSCj].reg_cagc;
		_g_cagc_for_ntscm = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_cagc;
		_g_ntsc_rf_low_burst_mode = 0;
	}
	else if(g_CVD_Status_3CS.cvd_lock_stable_count < (CVD_STABLE_COUNT_1 + 6) )
	{
		if ( (g_CVD_Status_3CS.cvd_burst_mag < 0x280) && ( g_CVD_Pattern_Detection_t.pattern_found != 1) \
				&& (g_CVD_Status_3CS.cvd_cordic_freq > 160) && ( g_CVD_Pattern_Detection_t.static_pattern_found != 1) \
				&& (g_CVD_Status_3CS.cvd_color_system == CVD_STATE_NTSC) && (g_CVD_Status_3CS.in_rf_mode == TRUE) \
				&& (g_CVD_WA_Low_Burst_ATV_Noise == 1) )
		{
			CVD_WA_DEBUG("Low Burst Mode : burst_mag[0x%x], cordic_freq[%d], stable_count[%d] \n",g_CVD_Status_3CS.cvd_burst_mag,g_CVD_Status_3CS.cvd_cordic_freq, g_CVD_Status_3CS.cvd_lock_stable_count);
			_g_ntsc_rf_low_burst_mode = 1;
			_g_cagc_for_ntscj = 0x3a;
			_g_cagc_for_ntscm = 0x3a;
			CVD_Set_CVD_Saturation_Value(0xc0);	//default 0x80
		}
		else
			CVD_WA_DEBUG("burst_mag[0x%x], cordic_freq[%d], stable_count[%d] \n",g_CVD_Status_3CS.cvd_burst_mag,g_CVD_Status_3CS.cvd_cordic_freq, g_CVD_Status_3CS.cvd_lock_stable_count);
	}

	return 0;
}

static int CVD_Workaround_PAL_RF_CGAC(void)
{


	if( (g_CVD_Status_3CS.cvd_burst_mag > 0xbc0) \
				|| (g_CVD_Status_3CS.cvd_chromalock_flag == 0 ) )	//added to fix low cagc problem channel change from no burst signal
	{
		// Restore cagc value to default
		g_CVD_Status_3CS.burst_mag_prev = g_CVD_Status_3CS.burst_mag_next;
		g_CVD_Status_3CS.burst_mag_next = CVD_BURST_MAG_STATE_BIG;
	}
	else if(g_CVD_Status_3CS.avg_status_noise < 110)
	{
		g_CVD_Status_3CS.burst_mag_prev = g_CVD_Status_3CS.burst_mag_next;
		g_CVD_Status_3CS.burst_mag_next = CVD_Get_CVD_Burst_Mag_Flag(g_CVD_Status_3CS.cvd_color_system);
	}

	if(g_CVD_Status_3CS.burst_mag_next == CVD_BURST_MAG_STATE_SAME)
		g_CVD_Status_3CS.burst_mag_next = g_CVD_Status_3CS.burst_mag_prev;

	if (g_CVD_Status_3CS.burst_mag_next != g_CVD_Status_3CS.burst_mag_prev)
	{
		CVD_WA_DEBUG("burst_mag_prev = %d , burst_mag_next = %d \n",(int)g_CVD_Status_3CS.burst_mag_prev,(int)g_CVD_Status_3CS.burst_mag_next);
		CVD_Set_CVD_CAGC(g_CVD_Status_3CS.burst_mag_next,&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system], g_CVD_Status_3CS.cvd_color_system);

	}
	//O18 burst position test NG : +1.5u
#ifdef CVD_BURST_GATE_ADJUST_FOR_BURST_POSITION_SHIFT
	if( g_CVD_Pattern_Detection_t.pattern_found )
	{
		if( (g_CVD_Status_3CS.burst_mag_next == CVD_BURST_MAG_STATE_SMALL) && (g_CVD_Status_3CS.burst_gate_modified != 1))
		{
			CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new - 2, pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_end_new + 2);
			g_CVD_Status_3CS.burst_gate_modified = 1;
		}
		else if( (g_CVD_Status_3CS.burst_mag_next == CVD_BURST_MAG_STATE_VERY_SMALL) && (g_CVD_Status_3CS.burst_gate_modified != 2))
		{
			CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new - 4, pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_end_new + 4);
			g_CVD_Status_3CS.burst_gate_modified = 2;
		}
		else if( (g_CVD_Status_3CS.burst_mag_next == CVD_BURST_MAG_STATE_BIG) && (g_CVD_Status_3CS.burst_gate_modified != 0))
		{
			CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new, pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_end_new);
			g_CVD_Status_3CS.burst_gate_modified = 0;
		}
	}
#endif
	//PAL chromalock , but noburst condition
	if( (g_CVD_Low_Burst_PAL_WA == 1) && ( g_CVD_Pattern_Detection_t.pattern_found ) && (g_CVD_Status_3CS.cvd_chromalock_flag == 1 ) && (g_CVD_Status_3CS.no_burst_flag == 1) && (_g_pal_lowburst_chromalock_level_modified == 0) && (g_CVD_Status_3CS.cvd_burst_mag < 0x180) )
	{
		AFE_PRINT("PAL lowburst: modify chromalock level\n");
		CVD_chromalock_level_control(0x7);
		_g_pal_lowburst_chromalock_level_modified = 1;
	}
	else if( (_g_pal_lowburst_chromalock_level_modified == 1) && ( (g_CVD_Low_Burst_PAL_WA == 0) || (g_CVD_Status_3CS.no_burst_flag == 0) || (g_CVD_Status_3CS.cvd_burst_mag > 0x200) ) )
	{
		AFE_PRINT("PAL lowburst: set to initial chromalock level\n");
		CVD_chromalock_level_control(0x5);
		_g_pal_lowburst_chromalock_level_modified = 0;
	}


#ifdef CVD_COLORBAR_PARAMS_TEMP
	// TEMP Code for H15 without PE F/W
	if( g_CVD_Pattern_Detection_t.pattern_found )
	{
		CVD_Set_ColorBar_Params(1);
	}
	else 
	{
		CVD_Set_ColorBar_Params(0);
	}
#endif
	return 0;
}

static int CVD_Workaround_NTSC_RF_CGAC(void)
{
	int loop;
	//	g_CVD_Status_3CS.burst_mag_prev = g_CVD_Status_3CS.burst_mag_next;
	//	g_CVD_Status_3CS.burst_mag_next = CVD_Get_CVD_Burst_Mag_Flag(g_CVD_Status_3CS.cvd_color_system);

	// 121207 : FSC Motion Expand : Diagonal Line on Boundary of ColorBar Pattern when FSC shift(+/- 10Hz)
	if( g_CVD_Pattern_Detection_t.pattern_found )
	{
		CVD_Set_Motion_Expand(1);
		CVD_Set_CCR(0);
	}
	else 
	{
		CVD_Set_Motion_Expand(0);
		CVD_Set_CCR(1);
	}

	g_CVD_Status_3CS.burst_mag_sum = 0;

	for(loop = 9;loop > 0;loop--) {
		g_CVD_Status_3CS.burst_mag_array[loop] = g_CVD_Status_3CS.burst_mag_array[loop-1] ;
		g_CVD_Status_3CS.burst_mag_sum += g_CVD_Status_3CS.burst_mag_array[loop];
	}

	g_CVD_Status_3CS.burst_mag_array[0] = CVD_Get_CVD_Burst_Mag_Value();

	g_CVD_Status_3CS.burst_mag_sum += g_CVD_Status_3CS.burst_mag_array[0];

	g_CVD_Status_3CS.burst_mag_avg = g_CVD_Status_3CS.burst_mag_sum / 10;

#ifdef CVD_BURST_GATE_ADJUST_FOR_BURST_POSITION_SHIFT
	//250516 : burst_mag_avg threshold 0xA00 to 0x900, 0xA80 to 0x980 (http://jira.lge.com/issue/browse/SCDCR-7808)
	//130916 : sub carrier delay
	// Modify burst_gate_start/end 
	if (g_CVD_Status_3CS.avg_status_noise < 110) 
	{
		if( g_CVD_Pattern_Detection_t.pattern_found )
		{
			if ( (g_CVD_Status_3CS.burst_mag_avg < 0x600) && ( g_CVD_Status_3CS.burst_gate_modified != 2 ) )
			{
				CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new - 11,\
						pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_end_new + 10);	//internal demod , 0x49
				g_CVD_Status_3CS.burst_gate_modified = 2;
				CVD_WA_DEBUG("NTSC RF CAGC burst_gate_modified : %d\n", g_CVD_Status_3CS.burst_gate_modified);
			}
			else if ( (g_CVD_Status_3CS.burst_mag_avg > 0x680) && (g_CVD_Status_3CS.burst_mag_avg < 0x900 /*0xA00*/) && ( g_CVD_Status_3CS.burst_gate_modified == 2) )
			{
				CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new - 8,\
						pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_end_new + 5);	//internal demod , 0x49
				//CVD_Burst_Gate_Control(0x30, 0x49);
				g_CVD_Status_3CS.burst_gate_modified = 1;
				CVD_WA_DEBUG("NTSC RF CAGC burst_gate_modified : %d\n", g_CVD_Status_3CS.burst_gate_modified);
			}
			else if ( (g_CVD_Status_3CS.burst_mag_avg > 0x600) && (g_CVD_Status_3CS.burst_mag_avg < 0x900 /*0xA00*/) && ( g_CVD_Status_3CS.burst_gate_modified != 1) )
			{
				CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new - 8,\
						pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_end_new + 5);	//internal demod , 0x49
				//CVD_Burst_Gate_Control(0x30, 0x49);
				g_CVD_Status_3CS.burst_gate_modified = 1;
				CVD_WA_DEBUG("NTSC RF CAGC burst_gate_modified : %d\n", g_CVD_Status_3CS.burst_gate_modified);
			}
			else if ( (g_CVD_Status_3CS.burst_mag_avg > 0x980/*0xA80*/) && ( g_CVD_Status_3CS.burst_gate_modified != 0) )
			{
				CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new,\
						pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_end_new);

				g_CVD_Status_3CS.burst_gate_modified = 0;
				CVD_WA_DEBUG("NTSC RF CAGC burst_gate_modified : %d\n", g_CVD_Status_3CS.burst_gate_modified);
			}
		}
		else if( g_CVD_Status_3CS.burst_gate_modified ) {
			CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new,\
					pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_end_new);

			g_CVD_Status_3CS.burst_gate_modified = 0;
			CVD_WA_DEBUG("NTSC RF CAGC burst_gate_modified : %d\n", g_CVD_Status_3CS.burst_gate_modified);
		}
	}
#endif

	//120127 : modified by kd.park
	//120131 : if pattern not found do not adjust cagc register
#if 0
	if( (g_CVD_Status_3CS.burst_mag_avg > 0xbc0) )
#endif

		if( (g_CVD_Status_3CS.burst_mag_avg > 0xbc0) || ( g_CVD_Pattern_Detection_t.pattern_found != 1)
				|| (g_CVD_Status_3CS.cvd_chromalock_flag == 0 ) )
		{	// added for burst mag test (chroma unlock)
			g_CVD_Status_3CS.burst_mag_next = CVD_BURST_MAG_STATE_BIG;
			g_CVD_Status_3CS.prev_burst_mag_avg = 0xbc0;

			//121114 : why reg_saturation???
			//g_CVD_Status_3CS.cagc_target = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_saturation;
			//
			//

			if(g_CVD_Status_3CS.cvd_black_level == LX_AFE_CVD_BLACK_LEVEL_HIGH)	// NTSC-J
			{
				g_CVD_Status_3CS.cagc_target = _g_cagc_for_ntscj;

				if(CVD_Get_CAGC_Value() != _g_cagc_for_ntscj)
				{
					CVD_WA_DEBUG("NTSC-J Mode : Set CAGC to [0x%x]\n", _g_cagc_for_ntscj);
					CVD_Set_CAGC_Value(_g_cagc_for_ntscj);
					CVD_Black_Level_Control(LX_AFE_CVD_BLACK_LEVEL_HIGH, LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF);
				}
			}
			else if(g_CVD_Status_3CS.cvd_black_level == LX_AFE_CVD_BLACK_LEVEL_LOW)	// NTSC-M
			{
				g_CVD_Status_3CS.cagc_target = _g_cagc_for_ntscm;
				if(CVD_Get_CAGC_Value() != _g_cagc_for_ntscm)
				{
					CVD_WA_DEBUG("NTSC-M Mode : Set CAGC to [0x%x]\n", _g_cagc_for_ntscm);
					CVD_Set_CAGC_Value(_g_cagc_for_ntscm);
					CVD_Black_Level_Control(LX_AFE_CVD_BLACK_LEVEL_LOW, LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF);
				}
			}
			else
			{
				g_CVD_Status_3CS.cagc_target = _g_cagc_for_ntscm;
				if(CVD_Get_CAGC_Value() != _g_cagc_for_ntscm)
				{
					CVD_WA_DEBUG("Auto Mode : Set CAGC to [0x%x]\n", _g_cagc_for_ntscm);
					CVD_Set_CAGC_Value(_g_cagc_for_ntscm);
					CVD_Black_Level_Control(LX_AFE_CVD_BLACK_LEVEL_LOW, LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF);
				}
				//	CVD_WA_DEBUG("NTSC Auto Mode \n");
			}

		}
		else if( (g_CVD_Status_3CS.burst_mag_avg < 0x280) && \
				(g_CVD_Status_3CS.avg_status_noise < 110) )
		{
			g_CVD_Status_3CS.burst_mag_next = CVD_BURST_MAG_STATE_VERY_SMALL;
			g_CVD_Status_3CS.prev_burst_mag_avg = 0x280;
			g_CVD_Status_3CS.cagc_target = 0x20;
		}
		else if (g_CVD_Status_3CS.avg_status_noise < 110) {
			g_CVD_Status_3CS.burst_mag_next = (g_CVD_Status_3CS.burst_mag_avg / 0x17) + 0x5;
			if(g_CVD_Status_3CS.burst_mag_next > pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_saturation)
				g_CVD_Status_3CS.burst_mag_next = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_saturation;
			g_CVD_Status_3CS.cagc_target = g_CVD_Status_3CS.burst_mag_next;
		}
		else
		{
			CVD_THREAD_DEBUG("color bar pattern found,but noisy [%d]\n", g_CVD_Status_3CS.avg_status_noise);
		}

	//CVD_DEBUG("burst_mag = [0x%x], burst_mag_avg = [0x%x], prev_burst_mag_avg = [0x%x], burst_mag_next [0x%x], burst_mag_prev[0x%x] \n",g_CVD_Status_3CS.burst_mag_array[0], g_CVD_Status_3CS.burst_mag_avg, g_CVD_Status_3CS.prev_burst_mag_avg, g_CVD_Status_3CS.burst_mag_next, g_CVD_Status_3CS.burst_mag_prev);

	if ( ( ( (g_CVD_Status_3CS.burst_mag_next >= 0x5) && ( abs(g_CVD_Status_3CS.prev_burst_mag_avg - g_CVD_Status_3CS.burst_mag_avg) > 0x80) )  \
				||  ( ( g_CVD_Status_3CS.burst_mag_next < 5) && (g_CVD_Status_3CS.burst_mag_next != g_CVD_Status_3CS.burst_mag_prev) ) ) \
			&& (g_CVD_Status_3CS.cvd_lock_stable_count > (CVD_STABLE_COUNT_1 + 10 ))
			&& (_g_ntsc_rf_low_burst_mode == 0) )
	{
		CVD_WA_DEBUG("burst_mag_prev = 0x%x , burst_mag_next = 0x%x \n",g_CVD_Status_3CS.burst_mag_prev,g_CVD_Status_3CS.burst_mag_next);
		CVD_WA_DEBUG("burst_mag_avg = 0x%x\n",g_CVD_Status_3CS.burst_mag_avg);

		g_CVD_Status_3CS.cagc_written = CVD_Get_CAGC_Value();

		CVD_WA_DEBUG("cagc_written = 0x%x , cagc_target = 0x%x \n",g_CVD_Status_3CS.cagc_written,g_CVD_Status_3CS.cagc_target);

		if(g_CVD_Status_3CS.cagc_written > g_CVD_Status_3CS.cagc_target)
			g_CVD_Status_3CS.burst_mag_next = g_CVD_Status_3CS.cagc_written - 1;
		else if(g_CVD_Status_3CS.cagc_written < g_CVD_Status_3CS.cagc_target)
			g_CVD_Status_3CS.burst_mag_next = g_CVD_Status_3CS.cagc_written + 1;
		else {
			CVD_WA_DEBUG("CAGC Target Reached !!! [0x%x]\n",g_CVD_Status_3CS.cagc_written);
			g_CVD_Status_3CS.prev_burst_mag_avg = g_CVD_Status_3CS.burst_mag_avg;
			g_CVD_Status_3CS.burst_mag_prev = g_CVD_Status_3CS.burst_mag_next;
			g_CVD_Status_3CS.burst_mag_next = g_CVD_Status_3CS.cagc_written;
		}

		CVD_Set_CVD_CAGC(g_CVD_Status_3CS.burst_mag_next,&pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system], g_CVD_Status_3CS.cvd_color_system);
		//CVD_DEBUG("################# CAGC changed gogosing ############### \n");
	}

	if( ( g_CVD_Status_3CS.cvd_chromalock_flag == 0 ) && ( CVD_Get_Hue_Value() != 0 ) ){	// added for burst mag test (chroma unlock due to hue modified )
		CVD_WA_DEBUG("NTSC RF chroma unlock : set hue  [0x%x]\n", pSetColorSystem_3CS->Color_System_Params[CVD_STATE_Default].reg_hue);
		CVD_Set_Hue_Value(pSetColorSystem_3CS->Color_System_Params[CVD_STATE_Default].reg_hue);
	}
	else if ( ( g_CVD_Status_3CS.cvd_chromalock_flag == 1 ) && ( CVD_Get_Hue_Value() == 0 ) ) {
		CVD_WA_DEBUG("NTSC RF chroma LOCK : set hue  [0x%x]\n", pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_hue);
		CVD_Set_Hue_Value(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_hue);
	}

	return 0;
}

static int CVD_Workaround_NTSC_AV_CGAC(void)
{
	if(g_CVD_Status_3CS.cvd_black_level == LX_AFE_CVD_BLACK_LEVEL_HIGH)	// NTSC-J
	{
		g_CVD_Status_3CS.cagc_target = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSCj].reg_cagc_av;

		if(CVD_Get_CAGC_Value() != pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSCj].reg_cagc_av)
		{
			CVD_WA_DEBUG("NTSC-J Mode : Set CAGC to [0x%x]\n", pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSCj].reg_cagc_av);
			CVD_Set_CAGC_Value(pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSCj].reg_cagc_av);
			CVD_Black_Level_Control(LX_AFE_CVD_BLACK_LEVEL_HIGH, LX_CVD_INPUT_SOURCE_ATTRIBUTE_AV);
		}
	}
	else if(g_CVD_Status_3CS.cvd_black_level == LX_AFE_CVD_BLACK_LEVEL_LOW)	// NTSC-M
	{
		g_CVD_Status_3CS.cagc_target = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_cagc_av;
		if(CVD_Get_CAGC_Value() != pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_cagc_av)
		{
			CVD_WA_DEBUG("NTSC-M Mode : Set CAGC to [0x%x]\n", pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_cagc_av);
			CVD_Set_CAGC_Value(pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_cagc_av);
			CVD_Black_Level_Control(LX_AFE_CVD_BLACK_LEVEL_LOW, LX_CVD_INPUT_SOURCE_ATTRIBUTE_AV);
		}
	}
	else
	{
		//	CVD_WA_DEBUG("NTSC Auto Mode \n");
		g_CVD_Status_3CS.cagc_target = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_cagc_av;
	}

	return 0;
}

static int CVD_Workaround_SECAM_Burst_Position(void)
{
	static int secam_gate_modified = 0;
	int burst1_mag, burst2_mag, burst1_mag_sum, burst2_mag_sum;
	int loop;

	burst1_mag_sum = 0;
	burst2_mag_sum = 0;

	for(loop = 0; loop < 1; loop++)
	{
		CVD_Get_Burst_Mag_12(&burst1_mag, &burst2_mag);
		burst1_mag_sum += burst1_mag;
		burst2_mag_sum += burst2_mag;
	}

	_g_burst1_mag_sum += burst1_mag_sum ;
	_g_burst2_mag_sum += burst2_mag_sum ;

	CVD_WA_DEBUG("for SECAM stable[%d] burst1 mag sum[0x%x], burst2 mag sum[0x%x], burst1 mag[0x%x], burst2 mag[0x%x]\n",\
			g_CVD_Status_3CS.cvd_lock_stable_count, _g_burst1_mag_sum, _g_burst2_mag_sum, burst1_mag_sum, burst2_mag_sum);

	if(g_CVD_Status_3CS.cvd_lock_stable_count > 5) 
	{
		if( ( (_g_burst1_mag_sum * 2) > (_g_burst2_mag_sum * 3) ) && (burst1_mag_sum > 0x1a) && (secam_gate_modified == 0) )
		{
			AFE_PRINT("SECAM burst end abnormal : stable[%d] burst1 mag sum[0x%x] >  burst2 mag sum[0x%x] => modify burst/cordic gate end value \n",\
					g_CVD_Status_3CS.cvd_lock_stable_count, _g_burst1_mag_sum, _g_burst2_mag_sum);

			CVD_Burst_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_burst_gate_start_new, 0x5a);
			CVD_Cordic_Gate_Control(pSetColorSystem_3CS->Color_System_Params[g_CVD_Status_3CS.cvd_color_system].reg_cordic_gate_start_new, 0x5a);
			secam_gate_modified = 1;
		}
	}
	else
		secam_gate_modified = 0;

	return 0;
}
