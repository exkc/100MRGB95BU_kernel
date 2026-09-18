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
 *  @date		2011-08-19
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/uaccess.h>
#include <linux/irq.h>
#include "afe_drv.h"
#include "linux/delay.h"

#include "sys_regs.h"
#include "os_util.h"

#include "cvd_module.h"
#include "cvd_hal.h"
#include "de_cvd_reg.h"

/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/
#define STANDARD_CDTO_INC_VALUE  0x21F07C1F

/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/
//#define VPORT_REG_DIRECT_ACCESS 0
#define	HSTART_SHIFT_DUE_TO_DE_CROP_WORKAROUND	1

//#define L9_SLOW_AGC_WORKAROUND
//#define L9_USE_SYNCTIP_ONLY_MODE
#define USE_NEW_GATE_VALUES

//#define CVD_REG_SATURATION_ADJUST
#define CVD_REG_OADJ_C_COEFF_ADJUST

/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_DEMOD
extern int DEMOD_ANALOG_Set_ClampingCtrl(UINT8 clampCount, UINT16 stepsize);
#endif


/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/
// shadow register
//extern volatile VPORT_L9B0_REG_T __iomem *gpRegVPORT_L9B0;
// real
//extern volatile VPORT_L9B0_REG_T __iomem *gpRealRegVPORT_L9B0;
// M16A0 CVD Register Access
extern volatile DE_CVD_REG_T __iomem *gpRegCVD;
extern volatile DE_CVD_REG_T __iomem *gpRealRegCVD; 

//extern int gEnableScartFB;
//extern BOOLEAN g_CVD_RF_Input_Mode;
extern CVD_ADAPTIVE_PEAK_NOMINAL_CONTROL_T g_CVD_AGC_Peak_Nominal_Control ;
extern CVD_PATTERN_DETECTION_T g_CVD_Pattern_Detection_t ;
//extern LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	g_CVD_Color_System_Support ;
extern CVD_STATUS_3CS_T	g_CVD_Status_3CS ;

extern CVD_COLOR_SYSTEM_ARRAY_3CS_T *pSetColorSystem_3CS;

extern BOOLEAN gCVD_2d_mode;
/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/
UINT32 g_CVD_HAL_REV = 0x25051600;

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/
#ifdef M16_CVD_INIT_OADJ_C
static UINT32 g_initial_c_coeff = 0x1050;
#else
static UINT32 g_initial_c_coeff = 0;
#endif


/*========================================================================================
  Implementation Group
  ========================================================================================*/
int CVD_Hal_ClampAGC_OnOff(UINT8 on_off)
{
	//JUHEE : no more supported in L9
#if 0
	if(on_off)
	{
		CVD_Reg_RdFL(iris_099);
		CVD_Reg_Wr01(iris_099, cvd_cvd1_clampagc_on, 0x1);
		CVD_Reg_WrFL(iris_099);
	}
	else
	{
		CVD_Reg_RdFL(iris_099);
		CVD_Reg_Wr01(iris_099, cvd_cvd1_clampagc_on, 0x0);
		CVD_Reg_WrFL(iris_099);
	}
#endif
	return 0;
}

int CVD_Hal_Force_Color_Kill(UINT8 color_kill_enable)
{
#if 0
	if(color_kill_enable)
	{
		CVD_Reg_RdFL(iris_096);
		CVD_Reg_Wr01(iris_096, reg_ckill, 0x0);
		CVD_Reg_WrFL(iris_096);
	}
	else
	{
		CVD_Reg_RdFL(iris_096);
		CVD_Reg_Wr01(iris_096, reg_ckill, 0x1c00);
		CVD_Reg_WrFL(iris_096);
	}
#endif
	if(color_kill_enable)
	{
		CVD_Reg_RdFL(iris_023);
		CVD_Reg_Wr01(iris_023, reg_user_ckill_mode, 0x1);
		CVD_Reg_WrFL(iris_023);
	}
	else
	{
		CVD_Reg_RdFL(iris_023);
		CVD_Reg_Wr01(iris_023, reg_user_ckill_mode, 0x0);
		CVD_Reg_WrFL(iris_023);
	}
	return 0;
}


void CVD_Hal_Program_Color_System_buffer_only(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	/*
	CVD_Reg_RdFL(iris_mif_gmau_001);
	CVD_Reg_Wr01(iris_mif_gmau_001, reg_comb3_buffer_size, pSet_system_t->reg_comb3_buffer_size);
	CVD_Reg_WrFL(iris_mif_gmau_001);
	*/
	CVD_Reg_RdFL(iris_mif_gmau_002);
	CVD_Reg_Wr01(iris_mif_gmau_002, reg_fld1_init_rd_pel, pSet_system_t->reg_fld1_init_rd_pel);
	CVD_Reg_WrFL(iris_mif_gmau_002);
	CVD_Reg_RdFL(iris_mif_gmau_003);
	CVD_Reg_Wr01(iris_mif_gmau_003, reg_fld2_init_rd_pel, pSet_system_t->reg_fld2_init_rd_pel);
	CVD_Reg_WrFL(iris_mif_gmau_003);
	CVD_Reg_RdFL(iris_mif_gmau_004);
	CVD_Reg_Wr01(iris_mif_gmau_004, reg_fld3_init_rd_pel, pSet_system_t->reg_fld3_init_rd_pel);
	CVD_Reg_WrFL(iris_mif_gmau_004);
	CVD_Reg_RdFL(iris_mif_gmau_005);
	CVD_Reg_Wr01(iris_mif_gmau_005, reg_fld4_init_rd_pel, pSet_system_t->reg_fld4_init_rd_pel);
	CVD_Reg_WrFL(iris_mif_gmau_005);

	CVD_Reg_RdFL(iris_013);
	CVD_Reg_Wr01(iris_013, reg_colour_mode, pSet_system_t->reg_colour_mode);
	CVD_Reg_WrFL(iris_013);
	/*
	CVD_Reg_RdFL(iris_013);
	CVD_Reg_Wr01(iris_013, reg_hpixel, pSet_system_t->reg_hpixel);
	CVD_Reg_WrFL(iris_013);

	CVD_Reg_RdFL(iris_029);
	CVD_Reg_Wr01(iris_029, reg_cdto_inc, pSet_system_t->reg_cdto_inc);
	CVD_Reg_WrFL(iris_029);
	*/
	return;
}
void CVD_Hal_Program_Color_System_Main_Multi(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
#ifndef CVD_3DCOMB_ERROR_WORKAROUND
	if(pSet_system_t->reg_comb3_buffer_size > 1)
	{
		CVD_Reg_RdFL(iris_mif_gmau_001);
		CVD_Reg_Wr01(iris_mif_gmau_001, reg_comb3_buffer_size, pSet_system_t->reg_comb3_buffer_size);
		CVD_Reg_WrFL(iris_mif_gmau_001);
		CVD_Reg_RdFL(iris_mif_gmau_002);
		CVD_Reg_Wr01(iris_mif_gmau_002, reg_fld1_init_rd_pel, pSet_system_t->reg_fld1_init_rd_pel);
		CVD_Reg_WrFL(iris_mif_gmau_002);
		CVD_Reg_RdFL(iris_mif_gmau_003);
		CVD_Reg_Wr01(iris_mif_gmau_003, reg_fld2_init_rd_pel, pSet_system_t->reg_fld2_init_rd_pel);
		CVD_Reg_WrFL(iris_mif_gmau_003);
		CVD_Reg_RdFL(iris_mif_gmau_004);
		CVD_Reg_Wr01(iris_mif_gmau_004, reg_fld3_init_rd_pel, pSet_system_t->reg_fld3_init_rd_pel);
		CVD_Reg_WrFL(iris_mif_gmau_004);
		CVD_Reg_RdFL(iris_mif_gmau_005);
		CVD_Reg_Wr01(iris_mif_gmau_005, reg_fld4_init_rd_pel, pSet_system_t->reg_fld4_init_rd_pel);
		CVD_Reg_WrFL(iris_mif_gmau_005);
	}
#endif


	// by Kim.min 2010/06/03
	CVD_Reg_RdFL(iris_013);
	CVD_Reg_Wr03(iris_013, reg_colour_mode, pSet_system_t->reg_colour_mode, reg_vline_625, pSet_system_t->reg_vline_625, reg_hpixel, pSet_system_t->reg_hpixel);
	CVD_Reg_WrFL(iris_013);
	CVD_Reg_RdFL(iris_014);
	CVD_Reg_Wr01(iris_014, reg_ped, pSet_system_t->reg_ped);
	CVD_Reg_WrFL(iris_014);
	//added 110411 by kim.min
	CVD_Reg_RdFL(iris_131);
	CVD_Reg_Wr01(iris_131, reg_adc_blank_level, pSet_system_t->reg_adc_blank_level);
	CVD_Reg_WrFL(iris_131);
	CVD_Reg_RdFL(iris_015);
	//120503 moved reg_hagc_en to Reg_Init Function
	CVD_Reg_Wr01(iris_015, reg_cagc_en, pSet_system_t->reg_cagc_en );
	CVD_Reg_WrFL(iris_015);

	CVD_Reg_RdFL(iris_017);
	CVD_Reg_Wr01(iris_017, reg_hagc, pSet_system_t->reg_hagc);
	CVD_Reg_WrFL(iris_017);
	//yc_delay setting is moved to CVD PQ
	//gVportRegBx->iris_019.reg_yc_delay = pSet_system_t->reg_yc_delay;
	//CVD_Reg_RdFL(iris_019);
	//CVD_Reg_Wr01(iris_019, reg_yc_delay, pSet_system_t->reg_yc_delay);
	//CVD_Reg_WrFL(iris_019);
	// need Reg debug
	//
	CVD_Reg_RdFL(iris_096);
#ifdef USE_NEW_GATE_VALUES
	CVD_Reg_Wr02(iris_096, reg_cagc_gate_start, pSet_system_t->reg_cagc_gate_start_new, reg_cagc_gate_end, pSet_system_t->reg_cagc_gate_end_new);
#else
	CVD_Reg_Wr02(iris_096, reg_cagc_gate_start, pSet_system_t->reg_cagc_gate_start, reg_cagc_gate_end, pSet_system_t->reg_cagc_gate_end);
#endif
	CVD_Reg_WrFL(iris_096);
	CVD_Reg_RdFL(iris_029);
	CVD_Reg_Wr01(iris_029, reg_cdto_inc, pSet_system_t->reg_cdto_inc);
	CVD_Reg_WrFL(iris_029);
	CVD_Reg_RdFL(iris_030);
	CVD_Reg_Wr01(iris_030, reg_hdto_inc, pSet_system_t->reg_hdto_inc);
	CVD_Reg_WrFL(iris_030);


		CVD_Reg_RdFL(iris_036);
		CVD_Reg_Wr01(iris_036, reg_hactive_start, pSet_system_t->reg_hactive_start_54M);
		CVD_Reg_Wr01(iris_036, reg_hactive_width, pSet_system_t->reg_hactive_width_54M);
		CVD_Reg_WrFL(iris_036);

	CVD_Reg_RdFL(iris_037);
	CVD_Reg_Wr02(iris_037, reg_vactive_start, pSet_system_t->reg_vactive_start, reg_vactive_height, pSet_system_t->reg_vactive_height);
//	CVD_Reg_Wr02(iris_036, reg_vactive_start, pSet_system_t->reg_vactive_start_L9B0, reg_vactive_height, pSet_system_t->reg_vactive_height);
	CVD_Reg_WrFL(iris_037);
	CVD_Reg_RdFL(iris_016);
	CVD_Reg_Wr01(iris_016, reg_ntsc443_mode, pSet_system_t->reg_ntsc443_mode);
	CVD_Reg_WrFL(iris_016);
	CVD_Reg_RdFL(iris_035);
	//CVD_Reg_Wr01(iris_034, reg_burst_gate_end, pSet_system_t->reg_burst_gate_end);
#ifdef USE_NEW_GATE_VALUES
	CVD_Reg_Wr02(iris_035, reg_burst_gate_start, pSet_system_t->reg_burst_gate_start_new, reg_burst_gate_end, pSet_system_t->reg_burst_gate_end_new);
#else
	CVD_Reg_Wr02(iris_035, reg_burst_gate_start, pSet_system_t->reg_burst_gate_start_3CS, reg_burst_gate_end, pSet_system_t->reg_burst_gate_end_3CS);
#endif
	CVD_Reg_WrFL(iris_035);

	// 110828: L9Bx moved to PE
	/*
	CVD_Reg_RdFL(iris_044);
	CVD_Reg_Wr01(iris_044, reg_secam_ybw, pSet_system_t->reg_secam_ybw);
	CVD_Reg_WrFL(iris_044);
	CVD_Reg_RdFL(iris_045);
	CVD_Reg_Wr01(iris_045, reg_auto_secam_level, pSet_system_t->reg_auto_secam_level);
	CVD_Reg_WrFL(iris_045);

	CVD_Reg_RdFL(iris_046);
	CVD_Reg_Wr01(iris_046, reg_lose_chromalock_mode, pSet_system_t->reg_lose_chromalock_mode);
	CVD_Reg_WrFL(iris_046);
	CVD_Reg_RdFL(iris_060);
	CVD_Reg_Wr06(iris_060, reg_noise_th, pSet_system_t->reg_noise_th, reg_noise_th_en, pSet_system_t->reg_noise_th_en, reg_lowfreq_vdiff_gain, pSet_system_t->reg_lowfreq_vdiff_gain, reg_chroma_vdiff_gain, pSet_system_t->reg_chroma_vdiff_gain, reg_horiz_diff_ygain, pSet_system_t->reg_horiz_diff_ygain, reg_horiz_diff_cgain, pSet_system_t->reg_horiz_diff_cgain);
	CVD_Reg_WrFL(iris_060);
	CVD_Reg_RdFL(iris_061);
	CVD_Reg_Wr04(iris_061, reg_y_noise_th_gain, pSet_system_t->reg_y_noise_th_gain, reg_c_noise_th_gain, pSet_system_t->reg_c_noise_th_gain, reg_burst_noise_th_gain, pSet_system_t->reg_burst_noise_th_gain, reg_vadap_burst_noise_th_gain, pSet_system_t->reg_vadap_burst_noise_th_gain);
	CVD_Reg_WrFL(iris_061);
	CVD_Reg_RdFL(iris_062);
	// 110623 : by kim.min adaptive_chroma_mode will be changed according to the input condition(RF or AV).
	//CVD_Reg_Wr02(iris_062, reg_motion_mode, pSet_system_t->reg_motion_mode, reg_adaptive_chroma_mode, pSet_system_t->reg_adaptive_chroma_mode);
	CVD_Reg_Wr01(iris_062, reg_motion_mode, pSet_system_t->reg_motion_mode);
	CVD_Reg_WrFL(iris_062);
	*/
#ifndef M16_COMB2D_ONLY_CONTROL
	CVD_Reg_RdFL(iris_064);
//	CVD_Reg_Wr02(iris_064, reg_comb2d_only, pSet_system_t->reg_comb2d_only, reg_fb_sync, pSet_system_t->reg_fb_sync);
	if(gCVD_2d_mode == FALSE)
		CVD_Reg_Wr01(iris_064, reg_comb2d_only, pSet_system_t->reg_comb2d_only);
	CVD_Reg_Wr01(iris_064, reg_fb_sync, pSet_system_t->reg_fb_sync);
	//CVD_Reg_Wr01(iris_064, reg_fb_sync, pSet_system_t->reg_fb_sync);
	CVD_Reg_WrFL(iris_064);

	//121025 : added for H13B0 revision support
	if(gCVD_2d_mode == FALSE)
	{
		CVD_Reg_RdFL(iris_066);
		CVD_Reg_Wr01(iris_066, reg_comb2d_only_md, pSet_system_t->reg_comb2d_only);
		CVD_Reg_WrFL(iris_066);
	}
#endif
	// 110828: L9Bx moved to PE 'reg_md_noise_th'

	CVD_Reg_RdFL(iris_069);
	CVD_Reg_Wr02(iris_069, reg_vactive_md_start, pSet_system_t->reg_vactive_md_start, reg_vactive_md_height, pSet_system_t->reg_vactive_md_height);
	CVD_Reg_WrFL(iris_069);

	CVD_Reg_RdFL(iris_090);
	// 110828: L9Bx "reg_motion_config" moved to PE
	CVD_Reg_Wr02(iris_090, reg_hactive_md_start, pSet_system_t->reg_hactive_md_start, reg_hactive_md_width, pSet_system_t->reg_hactive_md_width);
	CVD_Reg_WrFL(iris_090);
	// 110828: L9Bx "reg_status_motion_mode" moved to PE

	// kim.min 0622
	CVD_Reg_RdFL(iris_094);
#ifdef USE_NEW_GATE_VALUES
	CVD_Reg_Wr03(iris_094, reg_cordic_gate_end, pSet_system_t->reg_cordic_gate_end_new, reg_cordic_gate_start, pSet_system_t->reg_cordic_gate_start_new, reg_phase_offset_range, pSet_system_t->reg_phase_offset_range);
#else
	CVD_Reg_Wr03(iris_094, reg_cordic_gate_end, pSet_system_t->reg_cordic_gate_end_3CS, reg_cordic_gate_start, pSet_system_t->reg_cordic_gate_start_3CS, reg_phase_offset_range, pSet_system_t->reg_phase_offset_range);
#endif
	CVD_Reg_WrFL(iris_094);

	// kim.min 0716
	//	_iow(&gVportRegBx->iris_086, 8, 0, pSet_system_t->reg_tcomb_chroma_level);
	//	_iow(&gVportRegBx->iris_086, 8, 8, pSet_system_t->reg_hf_luma_chroma_offset);
	//	_iow(&gVportRegBx->iris_086, 8, 24, pSet_system_t->reg_chroma_level);
	//kim.min 1103
	// setting of below register is moved to _CVD_L9Ax_Set_Output_Range()
	//	gVportRegBx->iris_118.reg_oadj_y_offo = pSet_system_t->reg_oadj_y_offo;
	//kim.min 0906
	// setting of below register is moved to _CVD_L9Ax_Set_Output_Range()
	//	gVportRegBx->iris_119.reg_oadj_y_coeff = pSet_system_t->reg_oadj_y_coeff;
	CVD_Reg_RdFL(iris_016);
	CVD_Reg_Wr01(iris_016, reg_pal60_mode, pSet_system_t->reg_pal60_mode);
	CVD_Reg_WrFL(iris_016);
	//kim.min 0920
	CVD_Reg_RdFL(iris_027);
	CVD_Reg_Wr01(iris_027, reg_hstate_max, pSet_system_t->reg_hstate_max);
	CVD_Reg_WrFL(iris_027);

	//by dws : remove mdelay
	//mdelay(10); //0619
//	OS_MsecSleep(5);

	//No use
//	CVD_Reg_RdFL(top_005);
//	CVD_Reg_Wr01(top_005, swrst_irisyc, 0);
//	CVD_Reg_WrFL(top_005);
	//added 0212 for better 3dcomb operation on RF signal.
#ifndef CVD_FAST_3DCOMB_WORKAROUND
#ifndef	CVD_3DCOMB_ERROR_WORKAROUND
	CVD_Reg_RdFL(iris_024);
	CVD_Reg_Wr01(iris_024, reg_hnon_std_threshold, pSet_system_t->reg_hnon_std_threshold);
	CVD_Reg_WrFL(iris_024);
#else
	CVD_Reg_RdFL(iris_024);
	CVD_Reg_Wr01(iris_024, reg_hnon_std_threshold, 0x0);
	CVD_Reg_WrFL(iris_024);

	CVD_Reg_RdFL(iris_067);
	CVD_Reg_Wr01(iris_067, reg_vf_nstd_en, 0x0);	// default 0x1
	CVD_Reg_WrFL(iris_067);
#endif
#endif

	//added 110415 for Jo Jo Gunpo filed stream : no signal issue
	CVD_Reg_RdFL(iris_078);
	CVD_Reg_Wr01(iris_078, reg_vsync_signal_thresh, pSet_system_t->reg_vsync_signal_thresh);
	CVD_Reg_WrFL(iris_078);

   //added 110608 ( for PAL Test(Sub Carrier Pull in Range) reg_fixed_cstate : 1, reg_cstate : 7 )
	/*
	CVD_Reg_RdFL(iris_048);
	CVD_Reg_Wr02(iris_048, reg_fixed_cstate, pSet_system_t->reg_fixed_cstate, cstate, pSet_system_t->reg_cstate);
	CVD_Reg_WrFL(iris_048);
	*/
	// For proper color system detection, at first set cstate value to default.

#if 0
   //gogosing added 110610 (for russia ATV field stream color system issue)	// 이곳에 두면 재현 잘 됨
   		CVD_Reg_RdFL(iris_182);
		CVD_Reg_Wr01(iris_182, reg_cs_chroma_burst5or10, pSet_system_t->cs_chroma_burst5or10);
		CVD_Reg_WrFL(iris_182);

		CVD_Reg_RdFL(iris_193);
		CVD_Reg_Wr01(iris_193, reg_cs1_chroma_burst5or10, pSet_system_t->cs1_chroma_burst5or10);
		CVD_Reg_WrFL(iris_193);
#endif

   //kim.min 0906
	CVD_Reg_RdFL(iris_263);
	if(g_CVD_Status_3CS.in_rf_mode == TRUE)
		CVD_Reg_Wr02(iris_263, reg_hrs_ha_start, pSet_system_t->reg_rf_hrs_ha_start, reg_hrs_ha_width, pSet_system_t->reg_hrs_ha_width);
	else
		CVD_Reg_Wr02(iris_263, reg_hrs_ha_start, pSet_system_t->reg_hrs_ha_start, reg_hrs_ha_width, pSet_system_t->reg_hrs_ha_width);
	CVD_Reg_WrFL(iris_263);

	//110901 : Start RGB Initail settings.
	//110919 : Modified to Set H/V offset of SCART RGB for each color system.
	CVD_Reg_RdFL(fastblank_009);
	CVD_Reg_RdFL(fastblank_010);
	CVD_Reg_Wr01(fastblank_009, reg_fb_vstart_odd, pSet_system_t->reg_fb_vstart_odd);
	CVD_Reg_Wr01(fastblank_010, reg_fb_vstart_even, pSet_system_t->reg_fb_vstart_even);
	CVD_Reg_Wr01(fastblank_010, reg_fb_height_half, pSet_system_t->reg_fb_height_half);
	CVD_Reg_Wr01(fastblank_010, reg_fb_hstart, pSet_system_t->reg_fb_hstart);
	CVD_Reg_WrFL(fastblank_009);
	CVD_Reg_WrFL(fastblank_010);

	//111129 wonsik.do
	CVD_Reg_RdFL(iris_074);
	CVD_Reg_Wr01(iris_074, reg_dcrestore_accum_width, pSet_system_t->reg_dcrestore_accum_width);
	CVD_Reg_WrFL(iris_074);

	if(g_CVD_Status_3CS.in_rf_mode == TRUE) {

		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_hsync_mid, pSet_system_t->reg_dcrestore_hsync_mid);
		CVD_Reg_WrFL(iris_076);

		//111215 : added reg_contrast
		CVD_Reg_RdFL(iris_021);
		CVD_Reg_Wr01(iris_021, reg_contrast, pSet_system_t->reg_contrast);
		CVD_Reg_WrFL(iris_021);

		CVD_Reg_RdFL(iris_022);
		CVD_Reg_Wr01(iris_022, reg_cagc, pSet_system_t->reg_cagc);
		CVD_Reg_WrFL(iris_022);
	}
	else {	// AV mode

		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_hsync_mid, pSet_system_t->reg_dcrestore_hsync_mid_av);
		CVD_Reg_WrFL(iris_076);

		//111215 : added reg_contrast
		CVD_Reg_RdFL(iris_021);
		CVD_Reg_Wr01(iris_021, reg_contrast, pSet_system_t->reg_contrast_av);
		CVD_Reg_WrFL(iris_021);

		CVD_Reg_RdFL(iris_022);
		CVD_Reg_Wr01(iris_022, reg_cagc, pSet_system_t->reg_cagc_av);
		CVD_Reg_WrFL(iris_022);
	}

   //120105 : added reg_saturation
	CVD_Reg_RdFL(iris_021);
	CVD_Reg_Wr01(iris_021, reg_saturation, pSet_system_t->reg_saturation);
	CVD_Reg_WrFL(iris_021);

   //140115 : added reg_hue
	CVD_Reg_RdFL(iris_021);
	CVD_Reg_Wr01(iris_021, reg_hue, pSet_system_t->reg_hue);
	CVD_Reg_WrFL(iris_021);

	//121101 : added for H13B0
#ifndef CVD_3DCOMB_ERROR_WORKAROUND
	if(pSet_system_t->reg_comb3_buffer_size > 1)
	{
		CVD_Reg_RdFL(iris_mif_gmau_md_001);
		CVD_Reg_Wr01(iris_mif_gmau_md_001, reg_comb3_buffer_size_md, pSet_system_t->reg_comb3_buffer_size_md);
		CVD_Reg_WrFL(iris_mif_gmau_md_001);

		CVD_Reg_RdFL(iris_mif_gmau_md_002);
		CVD_Reg_Wr01(iris_mif_gmau_md_002, reg_fld1_init_rd_pel_md, pSet_system_t->reg_fld1_init_rd_pel_md);
		CVD_Reg_WrFL(iris_mif_gmau_md_002);
	}
#endif
}

void CVD_Hal_Program_Color_System_CS(CVD_SELECT_CDETECT_T cs_sel, CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{

	if (cs_sel == CVD_SEL_CS_CS0) // select cs0;
	{
		CVD_Reg_RdFL(iris_180);
#ifdef M14B0_BRINGUP
		CVD_Reg_Wr01(iris_180, reg_cs_adaptive_chroma_mode, pSet_system_t->reg_adaptive_chroma_mode);
#endif
		CVD_Reg_Wr01(iris_180, reg_cs_auto_secam_level, pSet_system_t->reg_auto_secam_level);
		CVD_Reg_WrFL(iris_180);

		CVD_Reg_RdFL(iris_181);
		//gogoging SECAM threshold for keeping PAL stable 20110613
		CVD_Reg_Wr01(iris_181, reg_cs_issecam_th, pSet_system_t->cs_issecam_th);
		CVD_Reg_Wr01(iris_181, reg_cs_phase_offset_range, pSet_system_t->reg_phase_offset_range);
		CVD_Reg_WrFL(iris_181);

		CVD_Reg_RdFL(iris_183);
		CVD_Reg_Wr01(iris_183, reg_cs_secam_ybw, pSet_system_t->reg_secam_ybw);
		CVD_Reg_Wr01(iris_183, reg_cs_adaptive_mode, pSet_system_t->reg_adaptive_mode);
		CVD_Reg_Wr01(iris_183, reg_cs_colour_mode, pSet_system_t->reg_colour_mode);
		CVD_Reg_Wr01(iris_183, reg_cs_ntsc443_mode, pSet_system_t->reg_ntsc443_mode);
		CVD_Reg_Wr01(iris_183, reg_cs_pal60_mode, pSet_system_t->reg_pal60_mode);
		//gogosing PAL에서 0x5c  설정 시 FSC position  테스트 시 secam, pal transition 지속됨 --> 326e 원복 110627
		//cs0, cs1 burst gate width reg. ready
		CVD_Reg_Wr01(iris_183, reg_cs_chroma_burst5or10, pSet_system_t->cs_chroma_burst5or10);
		CVD_Reg_Wr01(iris_183, reg_cs_cagc_en, pSet_system_t->reg_cagc_en);
		CVD_Reg_WrFL(iris_183);

		CVD_Reg_RdFL(iris_184);
		CVD_Reg_Wr01(iris_184, reg_cs_cagc, pSet_system_t->reg_cagc);
		CVD_Reg_WrFL(iris_184);

		CVD_Reg_RdFL(iris_185);
		CVD_Reg_Wr01(iris_185, reg_cs_chroma_bw_lo, pSet_system_t->reg_chroma_bw_lo);
		CVD_Reg_WrFL(iris_185);

		CVD_Reg_RdFL(iris_186);
		CVD_Reg_Wr01(iris_186, reg_cs_cdto_inc, pSet_system_t->reg_cdto_inc);
		CVD_Reg_WrFL(iris_186);

		CVD_Reg_RdFL(iris_187);
		CVD_Reg_Wr01(iris_187, reg_cs_lose_chromalock_mode, pSet_system_t->reg_lose_chromalock_mode);
		CVD_Reg_WrFL(iris_187);

		//added 110608 ( for PAL Test(Sub Carrier Pull in Range) reg_fixed_cstate : 1, reg_cstate : 7 )
		/*
		CVD_Reg_RdFL(iris_186);
		CVD_Reg_Wr02(iris_186, reg_cs_fixed_cstate, pSet_system_t->reg_fixed_cstate, reg_cs_cstate, pSet_system_t->reg_cstate);
		CVD_Reg_WrFL(iris_186);
		*/

		//added 110908
		CVD_Reg_RdFL(iris_272);
#ifdef USE_NEW_GATE_VALUES
		CVD_Reg_Wr02(iris_272, reg_burst1_gate_start, pSet_system_t->reg_burst_gate_start_new, reg_burst1_gate_end, pSet_system_t->reg_burst_gate_end_new);
#else
		CVD_Reg_Wr02(iris_272, reg_burst1_gate_start, pSet_system_t->reg_burst_gate_start_3CS, reg_burst1_gate_end, pSet_system_t->reg_burst_gate_end_3CS);
#endif
		CVD_Reg_WrFL(iris_272);

		CVD_Reg_RdFL(iris_273);
#ifdef USE_NEW_GATE_VALUES
		CVD_Reg_Wr02(iris_273, reg_cordic1_gate_start, pSet_system_t->reg_cordic_gate_start_new, reg_cordic1_gate_end, pSet_system_t->reg_cordic_gate_end_new);
#else
		CVD_Reg_Wr02(iris_273, reg_cordic1_gate_start, pSet_system_t->reg_cordic_gate_start_3CS, reg_cordic1_gate_end, pSet_system_t->reg_cordic_gate_end_3CS);
#endif
		CVD_Reg_WrFL(iris_273);
	}
	else	// cs1 selected
	{
		CVD_Reg_RdFL(iris_191);
#ifdef M14B0_BRINGUP
		CVD_Reg_Wr01(iris_191, reg_cs1_adaptive_chroma_mode, pSet_system_t->reg_adaptive_chroma_mode);
#endif
		CVD_Reg_Wr01(iris_191, reg_cs1_auto_secam_level, pSet_system_t->reg_auto_secam_level);
		CVD_Reg_WrFL(iris_191);

		CVD_Reg_RdFL(iris_192);
		CVD_Reg_Wr01(iris_192, reg_cs1_phase_offset_range, pSet_system_t->reg_phase_offset_range);
		CVD_Reg_WrFL(iris_192);

		CVD_Reg_RdFL(iris_194);
		CVD_Reg_Wr01(iris_194, reg_cs1_secam_ybw, pSet_system_t->reg_secam_ybw);
		CVD_Reg_Wr01(iris_194, reg_cs1_adaptive_mode, pSet_system_t->reg_adaptive_mode);
		CVD_Reg_Wr01(iris_194, reg_cs1_colour_mode, pSet_system_t->reg_colour_mode);
		CVD_Reg_Wr01(iris_194, reg_cs1_ntsc443_mode, pSet_system_t->reg_ntsc443_mode);
		CVD_Reg_Wr01(iris_194, reg_cs1_pal60_mode, pSet_system_t->reg_pal60_mode);
		//gogosing PAL에서 0x5c  설정 시 FSC position  테스트 시 secam, pal transition 지속됨 --> 326e 원복 110627
		//cs0, cs1 burst gate width reg. ready
		CVD_Reg_Wr01(iris_194, reg_cs1_chroma_burst5or10, pSet_system_t->cs1_chroma_burst5or10);
		CVD_Reg_Wr01(iris_194, reg_cs1_cagc_en, pSet_system_t->reg_cagc_en);
		CVD_Reg_WrFL(iris_194);

		CVD_Reg_RdFL(iris_195);
		CVD_Reg_Wr01(iris_195, reg_cs1_cagc, pSet_system_t->reg_cagc);
		CVD_Reg_WrFL(iris_195);

		CVD_Reg_RdFL(iris_196);
		CVD_Reg_Wr01(iris_196, reg_cs1_chroma_bw_lo, pSet_system_t->reg_chroma_bw_lo);
		CVD_Reg_WrFL(iris_196);

		CVD_Reg_RdFL(iris_197);
		CVD_Reg_Wr01(iris_197, reg_cs1_cdto_inc, pSet_system_t->reg_cdto_inc);
		CVD_Reg_WrFL(iris_197);

		CVD_Reg_RdFL(iris_198);
		CVD_Reg_Wr01(iris_198, reg_cs1_lose_chromalock_mode, pSet_system_t->reg_lose_chromalock_mode);
		CVD_Reg_WrFL(iris_198);

		//added 110608 ( for PAL Test(Sub Carrier Pull in Range) reg_fixed_cstate : 1, reg_cstate : 7 )
		/*
		CVD_Reg_RdFL(iris_197);
		CVD_Reg_Wr02(iris_197, reg_cs1_fixed_cstate, pSet_system_t->reg_fixed_cstate, reg_cs1_cstate, pSet_system_t->reg_cstate);
		CVD_Reg_WrFL(iris_197);
		*/

		//added 110908
		CVD_Reg_RdFL(iris_272);
#ifdef USE_NEW_GATE_VALUES
		CVD_Reg_Wr02(iris_272, reg_burst2_gate_start, pSet_system_t->reg_burst_gate_start_new, reg_burst2_gate_end, pSet_system_t->reg_burst_gate_end_new);
#else
		CVD_Reg_Wr02(iris_272, reg_burst2_gate_start, pSet_system_t->reg_burst_gate_start_3CS, reg_burst2_gate_end, pSet_system_t->reg_burst_gate_end_3CS);
#endif
		CVD_Reg_WrFL(iris_272);

		CVD_Reg_RdFL(iris_273);
#ifdef USE_NEW_GATE_VALUES
		CVD_Reg_Wr02(iris_273, reg_cordic2_gate_start, pSet_system_t->reg_cordic_gate_start_new, reg_cordic2_gate_end, pSet_system_t->reg_cordic_gate_end_new);
#else
		CVD_Reg_Wr02(iris_273, reg_cordic2_gate_start, pSet_system_t->reg_cordic_gate_start_3CS, reg_cordic2_gate_end, pSet_system_t->reg_cordic_gate_end_3CS);
#endif
		CVD_Reg_WrFL(iris_273);
	}

	return;
}

void CVD_Hal_Program_Color_System_PreJob(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	CVD_DEBUG("%s entered [%d][%d]\n",__func__, pSet_system_t->reg_fixed_cstate, pSet_system_t->reg_cstate);
	// For proper color system detection, at first set cstate value to default.
	CVD_Reg_RdFL(iris_049);
	CVD_Reg_Wr02(iris_049, reg_fixed_cstate, pSet_system_t->reg_fixed_cstate, reg_cstate, pSet_system_t->reg_cstate);
	CVD_Reg_WrFL(iris_049);
}

void CVD_Hal_Program_Color_System_PreJob2(void)
{
	CVD_DEBUG("%s entered \n",__func__);
   //added 111226 ( default register setting for fast 3Dcomb operation )
	// restore default values of reg_agc_half_en to '0', and reg_nstd_hysis to '7' for EBS field stream support.
	CVD_Reg_RdFL(iris_015);
	CVD_Reg_Wr01(iris_015, reg_agc_half_en, 0);
	CVD_Reg_WrFL(iris_015);
	CVD_Reg_RdFL(iris_024);
	CVD_Reg_Wr01(iris_024, reg_nstd_hysis, 7);
	CVD_Reg_WrFL(iris_024);


	//added 120114 for stable agc (restore default values)
	CVD_Reg_RdFL(iris_025);
	CVD_Reg_Wr01(iris_025, reg_agc_peak_cntl, 0x1);
	CVD_Reg_WrFL(iris_025);
	CVD_Reg_RdFL(iris_074);
	CVD_Reg_Wr01(iris_074, reg_dcrestore_gain, 0x0);
	CVD_Reg_WrFL(iris_074);
}

void CVD_Hal_Program_Color_System_PostJob(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	CVD_DEBUG("%s entered [%d][%d]\n",__func__, pSet_system_t->reg_fixed_cstate, pSet_system_t->reg_cstate);
   //added 110608 ( for PAL Test(Sub Carrier Pull in Range) reg_fixed_cstate : 1, reg_cstate : 7 )
	CVD_Reg_RdFL(iris_049);
	CVD_Reg_Wr02(iris_049, reg_fixed_cstate, pSet_system_t->reg_fixed_cstate, reg_cstate, pSet_system_t->reg_cstate);
	CVD_Reg_WrFL(iris_049);
}

void CVD_Hal_Program_Color_System_PostJob2(void)
{
//	CVD_DEBUG("%s entered \n",__func__);
   //added 111226 ( for EBS 060225_1636 stream , change reg_agc_half_en to '1', reg_nstd_hysis to '0' )
	CVD_Reg_RdFL(iris_015);
	CVD_Reg_Wr01(iris_015, reg_agc_half_en, 1);
	CVD_Reg_WrFL(iris_015);
	CVD_Reg_RdFL(iris_024);
	CVD_Reg_Wr01(iris_024, reg_nstd_hysis, 0);
	CVD_Reg_WrFL(iris_024);

	//added 120114 for stable agc
	CVD_Reg_RdFL(iris_025);
	CVD_Reg_Wr01(iris_025, reg_agc_peak_cntl, 0x0);
	CVD_Reg_WrFL(iris_025);
	CVD_Reg_RdFL(iris_074);
	CVD_Reg_Wr01(iris_074, reg_dcrestore_gain, 0x3);
	CVD_Reg_WrFL(iris_074);
}

int CVD_Hal_Set_Scart_Overlay(BOOLEAN arg)
{
	if(arg == TRUE)
	{
		// 110901 : L9B0 Scart RGB register setting.
		// Moved to Reg_Init
		/*
		CTOP_CTRL_L9B_RdFL(ctr26_reg_extclk_div_sel);
		CTOP_CTRL_L9B_Wr01(ctr26_reg_extclk_div_sel, reg_ch3pix_clk_sel, 0x1);
		CTOP_CTRL_L9B_WrFL(ctr26_reg_extclk_div_sel);
		*/

		//20111110 : modified not to directly set reg_fb_en register. reg_fb_en is set in ADC periodic task.
		//gEnableScartFB = 1;
		/*
		CVD_Reg_RdFL(fastblank_001);
		CVD_Reg_Wr01(fastblank_001, reg_fb_en, 0x1);
		CVD_Reg_WrFL(fastblank_001);
		*/
		// Following Register settings were move to CVD_L9Ax_Reg_Init
		/*
		   gVportRegBx->fastblank_001.reg_fb_2line_delay = 0x1;
		   gVportRegBx->fastblank_001.reg_fb_blend_ratio = 0x8;
		   gVportRegBx->fastblank_001.reg_fb3ch_delay = 0xC;
		   gVportRegBx->fastblank_001.reg_fb_latency = 0x16;
		 */
	}
	else
	{
		//20111110 : modified not to directly set reg_fb_en register. reg_fb_en is set in ADC periodic task.
		//gEnableScartFB = 0;
		//20111221 : scart FB enable should be disabled immediately (ADC periodic task can go to sleep state on AV/ATV input condition)
		//20120118 : If SCART Fast Blanking toggle, immediate call to Scart FB EN result in screen flickering.
	//	CVD_E60Ax_Set_Scart_FB_En(0);	// Disable FB_EN
		/*
		CVD_Reg_RdFL(fastblank_001);
		CVD_Reg_Wr01(fastblank_001, reg_fb_en, 0x0);
		CVD_Reg_WrFL(fastblank_001);
		*/
		//		gVportRegBx->fastblank_001.reg_fb_blend_ratio = 0x8;
	}
	return 0;
}

int CVD_Hal_Set_Scart_FB_En(int fb_en_ctrl)
{
	int ret = 0;
	static int fb_en_status = 0;

	// SCART RGB Bug in M16Ax Chip
	if (lx_chip_rev() < LX_CHIP_REV(M16, B0))
		return ret;

	if( (fb_en_ctrl > 0) && (fb_en_status == 0))  {
		CVD_Reg_RdFL(fastblank_001);
		CVD_Reg_Wr01(fastblank_001, reg_fb_en, 0x1);
		CVD_Reg_Wr01(fastblank_001, reg_fb_blend_ratio, 0x10);
		CVD_Reg_WrFL(fastblank_001);
		fb_en_status = 1;
	}
	else if ( (fb_en_ctrl == 0) && (fb_en_status > 0) ) {
		CVD_Reg_RdFL(fastblank_001);
		CVD_Reg_Wr01(fastblank_001, reg_fb_en, 0x0);
		// When Input Change from SCART RGB to AV/ATV, prevent CVD black screen 
		CVD_Reg_Wr01(fastblank_001, reg_fb_blend_ratio, 0x0);
		CVD_Reg_WrFL(fastblank_001);
		fb_en_status = 0;
	}
	else
		ret = -1;

	return ret;
}

UINT8 CVD_Hal_Get_FC_Flag(LX_AFE_CVD_SELECT_T select_main_sub)
{
	UINT8 cordic_freq_status = 0;

	CVD_Reg_RdFL(iris_008);
	CVD_Reg_Rd01(iris_008, reg_status_cordic_freq, cordic_freq_status);
	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);

	if(cordic_freq_status > FC_MORE_THRESHOLD)
		return CVD_FC_MORE_FLAG;
	else if(cordic_freq_status < FC_LESS_THRESHOLD)
		return CVD_FC_LESS_FLAG;
	else
		return CVD_FC_SAME_FLAG;
}

#if 1
//gogosing burst mag status check for color burst level test (color 틀어짐 대응) 2011.06.11
UINT8 CVD_Hal_Get_CVD_Burst_Mag_Flag(CVD_STATE_T	color_system)
{
	UINT16 burst_mag_status;
	CVD_Reg_RdFL(iris_004);
	CVD_Reg_Rd01(iris_004,reg_status_burst_mag,burst_mag_status);

	//111212 by kd.park for MBC low burst magnitude
	if(color_system == CVD_STATE_NTSC) {
		if (g_CVD_Pattern_Detection_t.pattern_found == 1 ) {	// New Pattern Detection using Global Motion Value
			if(burst_mag_status > 0x650)
				return CVD_BURST_MAG_STATE_BIG; // big : 3
			else if(burst_mag_status < 0x520 && burst_mag_status > 0x420)
				return CVD_BURST_MAG_STATE_SMALL; // small : 2
			else if(burst_mag_status < 0x240)
				return CVD_BURST_MAG_STATE_VERY_SMALL; //very small : 1
			else
				return CVD_BURST_MAG_STATE_SAME; // same : 0
		}
		else
			return CVD_BURST_MAG_STATE_BIG; // big : 3
	}
	else {
	// Pattern detection for PAL disabled
	//	if (g_CVD_AGC_Peak_Nominal_Control.pattern_found == 1 ) {	// PAL RF with test pattern detected ???
			if(burst_mag_status > 0x520)//0x620 --> 0x520
				return CVD_BURST_MAG_STATE_BIG; // big : 3
			else if(burst_mag_status < 0x420 && burst_mag_status > 0x320)
				return CVD_BURST_MAG_STATE_SMALL; // small : 2
			else if(burst_mag_status < 0x240)
				return CVD_BURST_MAG_STATE_VERY_SMALL; //very small : 1
			else
				return CVD_BURST_MAG_STATE_SAME; // same : 0
	//	}
	//	else
	//		return CVD_BURST_MAG_STATE_BIG; // big : 3
	}
}

int CVD_Hal_Set_CVD_CAGC(UINT8 state,CVD_SET_SYSTEM_3CS_T *pSet_system_t, CVD_STATE_T	color_system)
{
#ifdef CVD_REG_OADJ_C_COEFF_ADJUST
	int color_compensator_value;
	int oadj_c_coeff_value;
#endif
#ifdef CVD_REG_SATURATION_ADJUST
	int saturation_value;
#endif
	int initial_cagc_value;

	if(state==0)
 		return 0;//not changed

	if(g_CVD_Status_3CS.cvd_black_level == LX_AFE_CVD_BLACK_LEVEL_HIGH)	// NTSC-J
		initial_cagc_value = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSCj].reg_cagc;
	else
		initial_cagc_value = pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_cagc;

    switch(state)
	{
		case 3: //big
			CVD_Reg_RdFL(iris_022);
			if(g_CVD_Status_3CS.in_rf_mode == TRUE) {
				CVD_Reg_Wr01(iris_022, reg_cagc, pSet_system_t->reg_cagc);

				CVD_WA_DEBUG("Write CAGC Value[BIG](%d) : [0x%x]\n",__LINE__, pSet_system_t->reg_cagc);
				if(color_system == CVD_STATE_NTSC) {

#ifdef CVD_REG_OADJ_C_COEFF_ADJUST
					color_compensator_value = 0 ;
					oadj_c_coeff_value = color_compensator_value + g_initial_c_coeff;
					CVD_Reg_RdFL(iris_122);
					CVD_Reg_Wr01(iris_122, reg_oadj_c_coeff, oadj_c_coeff_value);
					// H13_BRINGUP
					CVD_Reg_Wr01(iris_122, reg_oadj_cr_coeff, oadj_c_coeff_value);
					CVD_Reg_WrFL(iris_122);
					CVD_WA_DEBUG("Saturation Value(oadj_c_coeff)(%d) : [0x%x]\n",__LINE__, oadj_c_coeff_value);
#endif
#ifdef CVD_REG_SATURATION_ADJUST
					saturation_value = pSet_system_t->reg_saturation ;
					CVD_Reg_RdFL(iris_021);
					CVD_Reg_Wr01(iris_021, reg_saturation, saturation_value);
					CVD_Reg_WrFL(iris_021);
//					CVD_WA_DEBUG("Saturation Value : [0x%x]\n", saturation_value);
#endif
				}
			}
			else
				CVD_Reg_Wr01(iris_022, reg_cagc, pSet_system_t->reg_cagc_av);
			CVD_Reg_WrFL(iris_022);
			break;

		case 2: // small
			CVD_Reg_RdFL(iris_022);
			if(color_system == CVD_STATE_NTSC) {
				if (g_CVD_AGC_Peak_Nominal_Control.pattern_found == 1 ) {	// NTSC RF with test pattern detected ???
					CVD_Reg_Wr01(iris_022, reg_cagc,0x50); //120109 by kd.park for test pattern
					CVD_WA_DEBUG("Write CAGC Value[NT/S](%d) : [0x%x]\n",__LINE__, 0x50);
				}
				else {
					CVD_Reg_Wr01(iris_022, reg_cagc,0x50); //111212 by kd.park for MBC low burst magnitude
					CVD_WA_DEBUG("Write CAGC Value[NT/S](%d) : [0x%x]\n",__LINE__, 0x50);
				}
			}
			else {
				CVD_Reg_Wr01(iris_022, reg_cagc,0x45); //0x45); color 수평 noise 대응 0x45 --> 0x2c
				CVD_WA_DEBUG("Write CAGC Value[PAL/S](%d) : [0x%x]\n",__LINE__, 0x45);
			}
			CVD_Reg_WrFL(iris_022);
			break;

		case 1: // very small
			CVD_Reg_RdFL(iris_022);

			if(color_system == CVD_STATE_NTSC) {
				CVD_Reg_Wr01(iris_022, reg_cagc,0x20); //120127 : by kd.park

				CVD_WA_DEBUG("Write CAGC Value[NT](%d) : [0x%x]\n",__LINE__, state);
#ifdef CVD_REG_OADJ_C_COEFF_ADJUST
				color_compensator_value = (initial_cagc_value - 0x20) * 0x20 ;
				oadj_c_coeff_value = color_compensator_value + g_initial_c_coeff;
				CVD_Reg_RdFL(iris_122);
				CVD_Reg_Wr01(iris_122, reg_oadj_c_coeff, oadj_c_coeff_value);
				// H13_BRINGUP
				CVD_Reg_Wr01(iris_122, reg_oadj_cr_coeff, oadj_c_coeff_value);
				CVD_Reg_WrFL(iris_122);
				CVD_WA_DEBUG("Saturation Value[NT](oadj_c_coeff) : [0x%x]\n", oadj_c_coeff_value);
#endif
#ifdef CVD_REG_SATURATION_ADJUST
				saturation_value = pSet_system_t->reg_saturation + (0x80 - 0x20);
				CVD_Reg_RdFL(iris_021);
				CVD_Reg_Wr01(iris_021, reg_saturation, saturation_value);
				CVD_Reg_WrFL(iris_021);
				//					CVD_DEBUG("Saturation Value : [0x%x]\n", saturation_value);
#endif
			}
			else
			{
				CVD_Reg_Wr01(iris_022, reg_cagc,0x2c); //0x45); color 수평 noise 대응 0x45 --> 0x2c
				CVD_WA_DEBUG("Write CAGC Value[PAL/S](%d) : [0x%x]\n",__LINE__, 0x2c);
			}

			CVD_Reg_WrFL(iris_022);
			break;

		default:
			if( (color_system == CVD_STATE_NTSC) && (state >= 20)) {

				if(state > initial_cagc_value)
					state = initial_cagc_value;

				CVD_Reg_RdFL(iris_022);

				CVD_Reg_Wr01(iris_022, reg_cagc, state);

				CVD_Reg_WrFL(iris_022);
				CVD_WA_DEBUG("Write CAGC Value[NT](%d) : [0x%x]\n",__LINE__, state);

#ifdef CVD_REG_OADJ_C_COEFF_ADJUST
					color_compensator_value = (initial_cagc_value - state) * 0x20 ;
					oadj_c_coeff_value = color_compensator_value + g_initial_c_coeff;
					CVD_Reg_RdFL(iris_122);
					CVD_Reg_Wr01(iris_122, reg_oadj_c_coeff, oadj_c_coeff_value);
					// H13_BRINGUP
					CVD_Reg_Wr01(iris_122, reg_oadj_cr_coeff, oadj_c_coeff_value);
					CVD_Reg_WrFL(iris_122);
					CVD_WA_DEBUG("Saturation Value[NT](oadj_c_coeff) : [0x%x]\n", oadj_c_coeff_value);
#endif
#ifdef CVD_REG_SATURATION_ADJUST
				saturation_value = pSet_system_t->reg_saturation + (0x80 - state);
				CVD_Reg_RdFL(iris_021);
				CVD_Reg_Wr01(iris_021, reg_saturation, saturation_value);
				CVD_Reg_WrFL(iris_021);

//				CVD_DEBUG("Saturation Value : [0x%x]\n", saturation_value);
#endif
			}

			break;
	}

	return 0;
}
#endif

UINT8 CVD_Hal_Get_Cordic_Freq(LX_AFE_CVD_SELECT_T select_main_sub)
{
	UINT8 cordic_freq_status = 0;

	CVD_Reg_RdFL(iris_008);
	CVD_Reg_Rd01(iris_008, reg_status_cordic_freq, cordic_freq_status);
	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);

	return cordic_freq_status;
}

UINT8 CVD_Hal_Get_Cordic_Freq_CS0(void)
{
	UINT8 cordic_freq_status;
	CVD_Reg_RdFL(iris_189);
	CVD_Reg_Rd01(iris_189, reg_cs_status_cordic_freq, cordic_freq_status);
	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);
	return cordic_freq_status;
}

UINT8 CVD_Hal_Get_FC_Flag_CS0(void)
{
	UINT8 cordic_freq_status;

	CVD_Reg_RdFL(iris_189);
	CVD_Reg_Rd01(iris_189, reg_cs_status_cordic_freq, cordic_freq_status);

	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);

	if(cordic_freq_status > FC_MORE_THRESHOLD)
		return CVD_FC_MORE_FLAG;
	else if(cordic_freq_status < FC_LESS_THRESHOLD)
		return CVD_FC_LESS_FLAG;
	else
		return CVD_FC_SAME_FLAG;
}

UINT8 CVD_Hal_Get_Cordic_Freq_CS1(void)
{
	UINT8 cordic_freq_status;
	CVD_Reg_RdFL(iris_200);
	CVD_Reg_Rd01(iris_200, reg_cs1_status_cordic_freq, cordic_freq_status);
	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);
	return cordic_freq_status;
}

UINT8 CVD_Hal_Get_FC_Flag_CS1(void)
{
	UINT8 cordic_freq_status;

	CVD_Reg_RdFL(iris_200);
	CVD_Reg_Rd01(iris_200, reg_cs1_status_cordic_freq, cordic_freq_status);

	cordic_freq_status = (UINT8)((SINT8)cordic_freq_status + 0x80);

	if(cordic_freq_status > FC_MORE_THRESHOLD)
		return CVD_FC_MORE_FLAG;
	else if(cordic_freq_status < FC_LESS_THRESHOLD)
		return CVD_FC_LESS_FLAG;
	else
		return CVD_FC_SAME_FLAG;
}

int CVD_Hal_Get_FB_Status(LX_AFE_SCART_MODE_T *pScart_fb_mode)
{
	UINT32					status_fb_in_cnt;

	// FB Status Register has Bug ( '0' '1' transition when fb signal exist)
	CVD_Reg_RdFL(iris_364);
	CVD_Reg_Rd01(iris_364, reg_status_fb_in_cnt, status_fb_in_cnt);

	if(status_fb_in_cnt > 0x32a00)	// 720*576 = 0x65400, 0x65400/2 = 0x32a00
		*pScart_fb_mode = LX_SCART_MODE_RGB;
	else
		*pScart_fb_mode = LX_SCART_MODE_CVBS;
#if 0
	UINT8	scart_fb_state;
	CVD_H14Ax_RdFL(fast_blank_status_001);
	CVD_H14Ax_Rd01(fast_blank_status_001, reg_fb_state, scart_fb_state);
	if(scart_fb_state > 0)
		*pScart_fb_mode = LX_SCART_MODE_RGB;
	else
		*pScart_fb_mode = LX_SCART_MODE_CVBS;
#endif 
	return 0;
}

int CVD_Hal_Get_Scart_AR(LX_AFE_SCART_AR_INFO_T	*pScart_ar_param)
{
	/*
	UINT8	sc1_sid1, sc1_sid2;

	   if(pScart_ar_param->Scart_Id == LX_SCART_ID_1)
	   {
	   BMC_REG_E60Ax_RdFL(videoafe_03);
	   BMC_REG_E60Ax_Rd02(videoafe_03, videoafe_sid1lvl, sc1_sid1, videoafe_sid2lvl, sc1_sid2);

	   if((sc1_sid2==0)&&(sc1_sid1==0))
	   pScart_ar_param->Scart_AR = LX_SCART_AR_INVALID;
	   else if((sc1_sid2==1)&&(sc1_sid1==1))
	   pScart_ar_param->Scart_AR = LX_SCART_AR_4_3;
	   else
	   pScart_ar_param->Scart_AR = LX_SCART_AR_16_9;
	   }
	   else 
	   return -1;
	   */

	pScart_ar_param->Scart_AR = LX_SCART_AR_INVALID;

	return 0;
}

void CVD_Hal_Print_Vport_Version(void)
{
	UINT32 vport_version = 0;
	CVD_Reg_RdFL(top_001);
	CVD_Reg_Rd01(top_001, iris_ver, vport_version);
	AFE_PRINT("Vport Version : [%x]\n", vport_version);
}

int CVD_Hal_Get_No_Signal_Flag(void)
{
	int ret;
	CVD_Reg_RdFL(iris_001);
	CVD_Reg_Rd01(iris_001, reg_no_signal, ret);
	return ret;
}

int CVD_Hal_Get_HLock_Flag(void)
{
	int ret;
	CVD_Reg_RdFL(iris_001);
	CVD_Reg_Rd01(iris_001, reg_hlock, ret);
	return ret;
}

int CVD_Hal_Get_VLock_Flag(void)
{
	int ret;
	CVD_Reg_RdFL(iris_001);
	CVD_Reg_Rd01(iris_001, reg_vlock, ret);
	return ret;
}

int CVD_Hal_Get_Vline_625_Flag(void)
{
	int ret;

	CVD_Reg_RdFL(iris_002);
	CVD_Reg_Rd01(iris_002, reg_vline_625_detected, ret);

	return ret;
}

int CVD_Hal_Fast_Vline_625_Using_Vdetec_Vcount(void)
{
	//return 1;
	static int wrong_vline_count = 0;
	static int vline_625_count = 0;
	static int vline_525_count = 0;
	int ret, vline_reg, vcount;

	CVD_Reg_RdFL(iris_002);
	CVD_Reg_Rd01(iris_002, reg_vline_625_detected, ret);

	//for fixed vfreq system, 50/60Hz detection is no use.
	if( (( g_CVD_Status_3CS.color_system_support & (LX_COLOR_SYSTEM_NTSC_M |LX_COLOR_SYSTEM_PAL_M | LX_COLOR_SYSTEM_NTSC_443 | LX_COLOR_SYSTEM_PAL_60)) == 0 ) || \
		( ( g_CVD_Status_3CS.color_system_support & (LX_COLOR_SYSTEM_PAL_G |LX_COLOR_SYSTEM_PAL_NC | LX_COLOR_SYSTEM_SECAM)) == 0 ) )
		return ret;

	CVD_Reg_RdFL(iris_013);
	CVD_Reg_Rd01(iris_013, reg_vline_625, vline_reg);

	CVD_Reg_RdFL(iris_274);
	CVD_Reg_Rd01(iris_274, reg_status_vdetect_vcount, vcount);

	if( (vline_reg == 0x1) && (ret == 0x1) && (vcount > 0x340) && (vcount < 0x350) && (CVD_Hal_Get_VLock_Flag() > 0) )			// 0x344
	{
		CVD_DEBUG("!525 line ???, vcount = [0x%x]\n", vcount);
		wrong_vline_count++;
	}
	else
		wrong_vline_count = 0;

	if( (vline_reg == 0x0) && (ret == 0x1) && (CVD_Hal_Get_VLock_Flag() > 0)  && ( vcount < 0x250) && (vcount > 0x230) )	// 0x23e
	{
		CVD_DEBUG("625 line ???, vcount = [0x%x]\n", vcount);
		vline_625_count++;
	}
	else
		vline_625_count = 0;

	if( (vline_reg == 0x1) && (ret == 0x0) && (CVD_Hal_Get_VLock_Flag() > 0))	// 0x23e
	{
		CVD_DEBUG("525 line ???, vcount = [0x%x]\n", vcount);
		vline_525_count++;
	}
	else
		vline_525_count = 0;

	if (wrong_vline_count > 1)
	{
		wrong_vline_count = 0;
		CVD_DEBUG("Force Set vline to 525 line\n");
		CVD_Reg_Wr01(iris_013, reg_vline_625, 0);
		CVD_Reg_WrFL(iris_013);
		CVD_Hal_Set_Nosignal_Vactive_Params();
	}
	else if( vline_625_count > 1)
	{
		vline_625_count = 0;
		CVD_DEBUG("Set vline to 625 line\n");
		CVD_Reg_Wr01(iris_013, reg_vline_625, 1);
		CVD_Reg_WrFL(iris_013);
		CVD_Hal_Set_Nosignal_Vactive_Params();
	}
	else if( vline_525_count > 1)
	{
		vline_525_count = 0;
		CVD_DEBUG("Set vline to 525 line\n");
		CVD_Reg_Wr01(iris_013, reg_vline_625, 0);
		CVD_Reg_WrFL(iris_013);
		CVD_Hal_Set_Nosignal_Vactive_Params();
	}

	return ret;
}

int CVD_Hal_Get_Vdetect_Vcount_625_Flag(void)
{
	//return 1;
	static int vline_625_flag = 0;
	int vcount;
	CVD_Reg_RdFL(iris_274);
	CVD_Reg_Rd01(iris_274, reg_status_vdetect_vcount, vcount);

	if( (vcount > 0x1FC) && (vcount < 0x21c))
		vline_625_flag = 0;
	else if( (vcount > 0x260) && (vcount < 0x280))
		vline_625_flag = 1;
	else
		CVD_DEBUG("vcount unstable [%d]\n", vcount);

	return vline_625_flag;
}


int CVD_Hal_Get_PAL_Flag(void)
{
	int ret;
	CVD_Reg_RdFL(iris_002);
	CVD_Reg_Rd01(iris_002, reg_pal_detected, ret);
	return ret;
}

int CVD_Hal_Get_SECAM_Flag(void)
{
	int ret;
	CVD_Reg_RdFL(iris_002);
	CVD_Reg_Rd01(iris_002, reg_secam_detected, ret);
	return ret;
}

int CVD_Hal_Get_Chromalock_Flag(void)
{
	int ret;
	CVD_Reg_RdFL(iris_001);
	CVD_Reg_Rd01(iris_001, reg_chromalock, ret);
	return ret;
}

int CVD_Hal_Get_PAL_Flag_CS0(void)
{
	int ret;
	CVD_Reg_RdFL(iris_190);
	CVD_Reg_Rd01(iris_190, reg_cs_pal_detected, ret);
	return ret;
}

int CVD_Hal_Get_SECAM_Flag_CS0(void)
{
	int ret;
	CVD_Reg_RdFL(iris_189);
	CVD_Reg_Rd01(iris_189, reg_cs_secam_detected, ret);
	return ret;
}

int CVD_Hal_Get_Chromalock_Flag_CS0(void)
{
	int ret;
	CVD_Reg_RdFL(iris_190);
	CVD_Reg_Rd01(iris_190, reg_cs_chromalock, ret);
	return ret;
}

int CVD_Hal_Get_PAL_Flag_CS1(void)
{
	int ret;
	CVD_Reg_RdFL(iris_201);
	CVD_Reg_Rd01(iris_201, reg_cs1_pal_detected, ret);
	return ret;
}

int CVD_Hal_Get_SECAM_Flag_CS1(void)
{
	int ret;
	CVD_Reg_RdFL(iris_200);
	CVD_Reg_Rd01(iris_200, reg_cs1_secam_detected, ret);
	return ret;
}

int CVD_Hal_Get_Chromalock_Flag_CS1(void)
{
	int ret;
	CVD_Reg_RdFL(iris_201);
	CVD_Reg_Rd01(iris_201, reg_cs1_chromalock, ret);
	return ret;
}

int CVD_Hal_Get_Noise_Status(void)
{
	int ret;
	CVD_Reg_RdFL(iris_009);
	CVD_Reg_Rd01(iris_009, reg_status_noise, ret);
	return ret;
}

int CVD_Hal_Get_NoBurst_Flag(void)
{
	int ret;
	CVD_Reg_RdFL(iris_002);
	CVD_Reg_Rd01(iris_002, reg_noburst_detected, ret);
	return ret;
}

int CVD_Hal_Reset_vdct(int enable)
{
	if(enable >0)
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, swrst_vdct, 1);
		CVD_Reg_WrFL(iris_175);
	}
	else
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, swrst_vdct, 0);
		CVD_Reg_WrFL(iris_175);
	}
	return 0;
}

int CVD_Hal_Reset_hdct(int enable)
{
	if(enable >0)
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, swrst_hdct, 1);
		CVD_Reg_WrFL(iris_175);
	}
	else
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, swrst_hdct, 0);
		CVD_Reg_WrFL(iris_175);
	}
	return 0;
}

int CVD_Hal_Reset_cdct(int enable)
{
	if(enable >0)
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, swrst_cdct, 1);
		CVD_Reg_WrFL(iris_175);
	}
	else
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, swrst_cdct, 0);
		CVD_Reg_WrFL(iris_175);
	}
	return 0;
}


int CVD_Hal_Reset_Clampagc(void)
{
	//ADC_DEBUG("Reset Clampagc Entered\n");
	CVD_Reg_RdFL(iris_175);
	CVD_Reg_Wr01(iris_175, iris_clampagc_v2, 0x1);
	CVD_Reg_WrFL(iris_175);
	//by dws : remove mdelay
	//mdelay(5);
//	OS_MsecSleep(5);
	CVD_Reg_RdFL(iris_175);
	CVD_Reg_Wr01(iris_175, iris_clampagc_v2, 0x0);
	CVD_Reg_WrFL(iris_175);
	return 0;
}

int CVD_Hal_Get_Vline_625_Reg(void)
{
	int ret;
	CVD_Reg_RdFL(iris_013);
	CVD_Reg_Rd01(iris_013, reg_vline_625, ret);
	return ret;
}

int CVD_Hal_Set_PE_Params(CVD_REG_PARAM_T	*pCVD_PE_Param_t, UINT32 size, LX_AFE_CVD_PQ_MODE_T cvd_pq_mode)
{
	int count;
	UINT32 value;
	UINT32 recvAddr;
	int blue_mode;

	CVD_DEBUG("%s \n", __func__);

	for(count=0; count < size;count++)
	{

		recvAddr = pCVD_PE_Param_t->cvd_phy_addr;
		value = pCVD_PE_Param_t->cvd_pe_value;
		/*
		   if		(recvAddr <= 0x2000) recvAddr += DTVSOC_DE_BASE;
		   else if (recvAddr <= 0xffff) recvAddr += DTVSOC_VIRT_PL301_BASE;
		 */
		//120201 : for NTSC CAGC adjust
		// H13_BRINGUP
		if(recvAddr == (0x2e8 + 0x600) /* 0x13e8*/ )
			g_initial_c_coeff = value & 0xFFFF;
		/*
		if(recvAddr == 0x4718)
			value = 0;
			*/
		if(recvAddr == (0x150+0x600) /*0x1250*/ )	// blue_mode register : not to overwrite 
		{
			CVD_Reg_RdFL(iris_020);
			CVD_Reg_Rd01(iris_020, reg_blue_mode, blue_mode);
			value = (value & 0xFFFFFCFF) | (blue_mode << 8);
		}

		//For IRIS_049 : reg_fixed_cstate & reg_cstate
		if(recvAddr != (0x1C4+0x600)  )
		{
			REG_WD((void *)((uintptr_t)recvAddr + (uintptr_t)gpRealRegCVD - (uintptr_t)0x600), value);
		}

	//	CVD_DEBUG("%s [0x%x:0x%x]\n", __func__, recvAddr, value);

		pCVD_PE_Param_t++;

	}

	return 0;
}

int CVD_Hal_swrst_CS(CVD_SELECT_CDETECT_T cs_sel)
{
	if (cs_sel == CVD_SEL_CS_CS0) // select cs0;
	{
		CVD_Reg_RdFL(iris_180);
		CVD_Reg_Wr01(iris_180,  reg_cs_sw_rst, 1);
		CVD_Reg_WrFL(iris_180);

//		OS_MsecSleep(5);

		CVD_Reg_RdFL(iris_180);
		CVD_Reg_Wr01(iris_180,  reg_cs_sw_rst, 0);
		CVD_Reg_WrFL(iris_180);
	}
	else if (cs_sel == CVD_SEL_CS_CS1) // select cs1;
	{
		CVD_Reg_RdFL(iris_191);
		CVD_Reg_Wr01(iris_191,  reg_cs1_sw_rst, 1);
		CVD_Reg_WrFL(iris_191);

//		OS_MsecSleep(5);

		CVD_Reg_RdFL(iris_191);
		CVD_Reg_Wr01(iris_191,  reg_cs1_sw_rst, 0);
		CVD_Reg_WrFL(iris_191);
	}
	else
		return -1;

	return 0;
}

int CVD_Hal_Set_Hstate_Max(UINT32	hstate_max_value)
{

	CVD_WA_DEBUG("%s entered :  %d \n",__func__, hstate_max_value);
//	CVD_DEBUG("%s entered :  %d \n",__func__, hstate_max_value);

	if(hstate_max_value > 5)
		return -1;

	CVD_Reg_RdFL(iris_027);
	CVD_Reg_Wr01(iris_027,  reg_hstate_max, hstate_max_value);
	CVD_Reg_WrFL(iris_027);

	return 0;
}

int CVD_Hal_Set_Hstate_Fixed(UINT32	value)
{

	CVD_WA_DEBUG("%s entered :  %d \n",__func__, value);
//	CVD_DEBUG("%s entered :  %d \n",__func__, value);

	value &= 0x1;

	CVD_Reg_RdFL(iris_027);
	CVD_Reg_Wr01(iris_027,  reg_hstate_fixed, value);
	CVD_Reg_WrFL(iris_027);

	return 0;
}


int CVD_Hal_AGC_Bypass(int Bypass_Enable)
{

	AFE_TRACE("%s entered :  %d \n",__func__, Bypass_Enable);

	if(Bypass_Enable == 1) {

		CVD_Reg_RdFL(iris_098);
		CVD_Reg_Wr01(iris_098,  reg_agc_bypass, 0x1);
		CVD_Reg_WrFL(iris_098);
	}
	else {
		CVD_Reg_RdFL(iris_098);
		CVD_Reg_Wr01(iris_098,  reg_agc_bypass, 0x0);
		CVD_Reg_WrFL(iris_098);
	}

	return 0;
}

int CVD_Hal_Set_dcrestore_accum_width(int value)
{

	CVD_DEBUG("%s entered :  %d \n",__func__, value);

	CVD_Reg_RdFL(iris_074);
	CVD_Reg_Wr01(iris_074, reg_dcrestore_accum_width, value);
	CVD_Reg_WrFL(iris_074);

	return 0;
}

int CVD_Hal_Set_SCART_CSC(int black_level)
{
	CVD_DEBUG("%s entered : black_level[%d]\n",__func__, black_level);

	CVD_Reg_RdFL(fastblank_002);
	CVD_Reg_RdFL(fastblank_003);
	CVD_Reg_RdFL(fastblank_004);
	CVD_Reg_RdFL(fastblank_005);
	CVD_Reg_RdFL(fastblank_006);
	CVD_Reg_RdFL(fastblank_007);
	CVD_Reg_RdFL(fastblank_008);
	CVD_Reg_RdFL(fastblank_009);

#if 0
	CVD_Reg_Wr02(fastblank_002, reg_fb_csc_coef0, 0x0810, reg_fb_csc_coef1, 0x0191 );
	CVD_Reg_Wr02(fastblank_003, reg_fb_csc_coef2, 0x041D, reg_fb_csc_coef3, 0x7B58 );
	CVD_Reg_Wr02(fastblank_004, reg_fb_csc_coef4, 0x0706, reg_fb_csc_coef5, 0x7DA2 );
	CVD_Reg_Wr02(fastblank_005, reg_fb_csc_coef6, 0x7A1D, reg_fb_csc_coef7, 0x7EDD );
	CVD_Reg_Wr01(fastblank_006, reg_fb_csc_coef8, 0x0706 );
	CVD_Reg_Wr02(fastblank_009, reg_fb_csc_ofst4, 0x202, reg_fb_csc_ofst5, 0x204 );
#endif
#if 1		//Ultra Black Support
	if(black_level)	//High
	{
		CVD_Reg_Wr02(fastblank_002, reg_fb_csc_coef0, 0x0898, reg_fb_csc_coef1, 0x019B );
		CVD_Reg_Wr02(fastblank_003, reg_fb_csc_coef2, 0x0437, reg_fb_csc_coef3, 0x7B22 );
		CVD_Reg_Wr02(fastblank_004, reg_fb_csc_coef4, 0x0757, reg_fb_csc_coef5, 0x7D87 );
		CVD_Reg_Wr02(fastblank_005, reg_fb_csc_coef6, 0x79E8, reg_fb_csc_coef7, 0x7ED3 );
		CVD_Reg_Wr01(fastblank_006, reg_fb_csc_coef8, 0x0745 );
		CVD_Reg_Wr02(fastblank_007, reg_fb_csc_ofst0, 0x0, reg_fb_csc_ofst1, 0x0 );
		CVD_Reg_Wr02(fastblank_008, reg_fb_csc_ofst2, 0x0, reg_fb_csc_ofst3, 0x02D );
		CVD_Reg_Wr02(fastblank_009, reg_fb_csc_ofst4, 0x204, reg_fb_csc_ofst5, 0x204 );
	}
	else			//Low
	{
		CVD_Reg_Wr02(fastblank_002, reg_fb_csc_coef0, 0x0927, reg_fb_csc_coef1, 0x01DF );
		CVD_Reg_Wr02(fastblank_003, reg_fb_csc_coef2, 0x04E7, reg_fb_csc_coef3, 0x7A55 );
		CVD_Reg_Wr02(fastblank_004, reg_fb_csc_coef4, 0x088B, reg_fb_csc_coef5, 0x7D20 );
		CVD_Reg_Wr02(fastblank_005, reg_fb_csc_coef6, 0x78EA, reg_fb_csc_coef7, 0x7EA0 );
		CVD_Reg_Wr01(fastblank_006, reg_fb_csc_coef8, 0x0876 );
		CVD_Reg_Wr02(fastblank_007, reg_fb_csc_ofst0, 0x0, reg_fb_csc_ofst1, 0x0 );
		CVD_Reg_Wr02(fastblank_008, reg_fb_csc_ofst2, 0x0, reg_fb_csc_ofst3, 0x7E6 );
		CVD_Reg_Wr02(fastblank_009, reg_fb_csc_ofst4, 0x204, reg_fb_csc_ofst5, 0x204 );
	}
#else
if(black_level)	//High
	{
		CVD_Reg_Wr02(fastblank_002, reg_fb_csc_coef0, 0x0862, reg_fb_csc_coef1, 0x0191 );
		CVD_Reg_Wr02(fastblank_003, reg_fb_csc_coef2, 0x041D, reg_fb_csc_coef3, 0x7B58 );
		CVD_Reg_Wr02(fastblank_004, reg_fb_csc_coef4, 0x0706, reg_fb_csc_coef5, 0x7DA2 );
		CVD_Reg_Wr02(fastblank_005, reg_fb_csc_coef6, 0x7A1D, reg_fb_csc_coef7, 0x7EDD );
		CVD_Reg_Wr01(fastblank_006, reg_fb_csc_coef8, 0x0706 );
		CVD_Reg_Wr02(fastblank_007, reg_fb_csc_ofst0, 0x0, reg_fb_csc_ofst1, 0x0 );
		CVD_Reg_Wr02(fastblank_008, reg_fb_csc_ofst2, 0x0, reg_fb_csc_ofst3, 0x02C );
		CVD_Reg_Wr02(fastblank_009, reg_fb_csc_ofst4, 0x200, reg_fb_csc_ofst5, 0x200 );
	}
	else			//Low
	{
		CVD_Reg_Wr02(fastblank_002, reg_fb_csc_coef0, 0x08EE, reg_fb_csc_coef1, 0x01D3 );
		CVD_Reg_Wr02(fastblank_003, reg_fb_csc_coef2, 0x04C9, reg_fb_csc_coef3, 0x7A93 );
		CVD_Reg_Wr02(fastblank_004, reg_fb_csc_coef4, 0x082D, reg_fb_csc_coef5, 0x7D3F );
		CVD_Reg_Wr02(fastblank_005, reg_fb_csc_coef6, 0x7927, reg_fb_csc_coef7, 0x7EAC );
		CVD_Reg_Wr01(fastblank_006, reg_fb_csc_coef8, 0x082D );
		CVD_Reg_Wr02(fastblank_007, reg_fb_csc_ofst0, 0x0, reg_fb_csc_ofst1, 0x0 );
		CVD_Reg_Wr02(fastblank_008, reg_fb_csc_ofst2, 0x0, reg_fb_csc_ofst3, 0x7E6 );
		CVD_Reg_Wr02(fastblank_009, reg_fb_csc_ofst4, 0x200, reg_fb_csc_ofst5, 0x200 );
	}
#endif

	CVD_Reg_WrFL(fastblank_002);
	CVD_Reg_WrFL(fastblank_003);
	CVD_Reg_WrFL(fastblank_004);
	CVD_Reg_WrFL(fastblank_005);
	CVD_Reg_WrFL(fastblank_006);
	CVD_Reg_WrFL(fastblank_007);
	CVD_Reg_WrFL(fastblank_008);
	CVD_Reg_WrFL(fastblank_009);

	return 0;
}

int CVD_Hal_Set_comb2d_only(int value)
{

	AFE_TRACE("%s entered :  %d \n",__func__, value);
	value &= 0x1;

	CVD_Reg_RdFL(iris_064);
	CVD_Reg_Wr01(iris_064, reg_comb2d_only, value);
	CVD_Reg_WrFL(iris_064);

	return 0;
}

int CVD_Hal_Set_comb2d_only_md(int value)
{

	AFE_TRACE("%s entered :  %d \n",__func__, value);
	value &= 0x1;

	//added 121217
	CVD_Reg_RdFL(iris_066);
	CVD_Reg_Wr01(iris_066, reg_comb2d_only_md, value);
	CVD_Reg_WrFL(iris_066);

	return 0;
}

int CVD_Hal_Get_comb2d_only(void)
{
	int value;

	CVD_Reg_RdFL(iris_064);
	CVD_Reg_Rd01(iris_064, reg_comb2d_only, value);

	return value;
}

int CVD_Hal_Get_comb2d_only_md(void)
{
	int value;

	CVD_Reg_RdFL(iris_066);
	CVD_Reg_Rd01(iris_066, reg_comb2d_only_md, value);

	return value;
}

int CVD_Hal_Set_Noise_Threshold(int value)
{

	AFE_TRACE("%s entered :  %d \n",__func__, value);

	CVD_Reg_RdFL(iris_017);
	CVD_Reg_Wr01(iris_017, reg_noise_thresh, value);	// default 0x32
	CVD_Reg_WrFL(iris_017);

	return 0;
}

int CVD_Hal_Set_AGC_Peak_Nominal(UINT8	value)	// 7bit value
{
	value &= 0x7F;

	CVD_Reg_RdFL(iris_025);
	CVD_Reg_Wr01(iris_025, reg_agc_peak_nominal, value);	//Default : 0x0A
	CVD_Reg_WrFL(iris_025);

	return 0;
}

int CVD_Hal_Get_AGC_Peak_Nominal(void)
{
	int ret;

	CVD_Reg_RdFL(iris_025);
	CVD_Reg_Rd01(iris_025, reg_agc_peak_nominal, ret);	//Default : 0x0A

	return ret;
}

int CVD_Hal_Set_Contrast_Brightness(int contrast, int brightness)
{
	CVD_Reg_RdFL(iris_021);
	CVD_Reg_Wr01(iris_021, reg_contrast, contrast);
	CVD_Reg_Wr01(iris_021, reg_brightness, brightness);
	CVD_Reg_WrFL(iris_021);

	return 0;
}

int CVD_Hal_Set_Dcrestore_Gain(int value)
{
	value &= 0x3;

	CVD_Reg_RdFL(iris_074);
	// Inital Value is '0'
	// Set reg_dcrestore_gain to '3' on weak RF signal for sync stability
	CVD_Reg_Wr01(iris_074, reg_dcrestore_gain, value);
	CVD_Reg_WrFL(iris_074);

	return 0;
}

//set reg_agc_bypass & reg_dcrestore_gain to default value
void CVD_Hal_Set_for_Normal_Signal(void)
{
	CVD_DEBUG("%s entered \n",__func__);
	CVD_Hal_AGC_Bypass(0x0);
//	CVD_Hal_Set_Dcrestore_Gain(0x0);
}

//set AGC to Bypass, and set DCrestore gain to 1/8 on weak RF signal ( status nois is max value 0x3FF)
void CVD_Hal_Set_for_Noisy_Signal(void)
{
	CVD_DEBUG("%s entered \n",__func__);
	CVD_Hal_AGC_Bypass(0x1);
//	CVD_Hal_Set_Dcrestore_Gain(0x3);
}

int CVD_Hal_Get_Status_AGC_Gain(void)
{
	int ret;

	CVD_Reg_RdFL(iris_007);
	CVD_Reg_Rd01(iris_007, reg_status_agc_gain, ret);

	return ret;
}

int CVD_Hal_Set_AGC_Peak_En(int enable)
{
	enable &= 0x1;

//	CVD_DEBUG("%s entered :  %d \n",__func__, enable);

	CVD_Reg_RdFL(iris_025);
	CVD_Reg_Wr01(iris_025, reg_agc_peak_en, enable);
	CVD_Reg_WrFL(iris_025);

	return 0;

}

int CVD_Hal_Get_HNon_Standard_Flag(void)
{
	int ret;

	CVD_Reg_RdFL(iris_002);
	CVD_Reg_Rd01(iris_002, reg_hnon_standard, ret);

	return ret;
}

int CVD_Hal_Get_VNon_Standard_Flag(void)
{
	int ret;

	CVD_Reg_RdFL(iris_002);
	CVD_Reg_Rd01(iris_002, reg_vnon_standard, ret);

	return ret;
}

int CVD_Hal_Set_Noburst_Ckill(unsigned int value)
{
	value &= 0x1;

//	CVD_DEBUG("%s entered :  %d \n",__func__, value);

	CVD_Reg_RdFL(iris_024);
	CVD_Reg_Wr01(iris_024, reg_noburst_ckill, value);
	CVD_Reg_WrFL(iris_024);

	return 0;

}

int CVD_Hal_Get_Global_Motion_Value(void)
{
	int ret;

	unsigned int value;

	CVD_Reg_RdFL(iris_266);
	CVD_Reg_Rd01(iris_266, reg_ycsep_3d_status0, value);

	ret = value & 0xFF;

	return ret;
}

/* This Function is workaround code for JOJO Gunpo stream (vsync unstable)*/
int CVD_Hal_Set_for_Stable_Vsync(UINT32	Enable)
{
//	CVD_DEBUG("%s entered :  %d \n",__func__, Enable);

	if(Enable == 1) {
		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042,  reg_vsync_cntl, 0x2);
		CVD_Reg_Wr01(iris_042,  reg_vsync_cntl_noisy, 0x1);
		CVD_Reg_WrFL(iris_042);

		CVD_Reg_RdFL(iris_043);
		CVD_Reg_Wr01(iris_043,  reg_vloop_tc, 0x3);
		CVD_Reg_WrFL(iris_043);
	}
	else if(Enable == 2)
	{
		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042,  reg_vsync_cntl, 0x3);
		CVD_Reg_WrFL(iris_042);
	}
	else if(Enable == 3)
	{
		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042,  reg_vsync_cntl, 0x0);
		CVD_Reg_WrFL(iris_042);

	}
	else {
		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042,  reg_vsync_cntl, 0x1);
		CVD_Reg_Wr01(iris_042,  reg_vsync_cntl_noisy, 0x0);
		CVD_Reg_WrFL(iris_042);

		CVD_Reg_RdFL(iris_043);
		CVD_Reg_Wr01(iris_043,  reg_vloop_tc, 0x2);
		CVD_Reg_WrFL(iris_043);
	}
	return 0;
}

/* This Function is used for workaround code as to fix dong-go-dong-rak */
int CVD_Hal_Set_for_Field_Detect_Mode(UINT32 mode)
{

	CVD_Reg_RdFL(iris_043);

	if(mode == 3) 		CVD_Reg_Wr01(iris_043,  reg_field_detect_mode, 0x3);
	else if(mode == 2)  CVD_Reg_Wr01(iris_043,  reg_field_detect_mode, 0x2);
	else if(mode == 1)  CVD_Reg_Wr01(iris_043,  reg_field_detect_mode, 0x1);
	else if(mode == 0)  CVD_Reg_Wr01(iris_043,  reg_field_detect_mode, 0x0);
	else CVD_Reg_Wr01(iris_043,  reg_field_detect_mode, 0x2);	// Go to default value

	CVD_Reg_WrFL(iris_043);

	return 0;
}

/* This function is used for workaround code for brasil color instable issue */
int CVD_Hal_Set_for_Burst_Gate_End_On_Noisy(UINT8 original_value, UINT32 Enable)
{
	if(Enable == 0)
	{
		CVD_Reg_RdFL(iris_035);
		CVD_Reg_Wr01(iris_035,  reg_burst_gate_end, original_value);
		CVD_Reg_WrFL(iris_035);
		//AFE_PRINT("BURST GATE END 0x51\n");
	}
	else
	{
		CVD_Reg_RdFL(iris_035);
		CVD_Reg_Wr01(iris_035,  reg_burst_gate_end, 0x61);
		CVD_Reg_WrFL(iris_035);
		//AFE_PRINT("BURST GATE END 0x61\n");
	}

	return 0;
}


/* This function is used for workaround code for brasil color instable issue */
UINT32 CVD_Hal_Differential_Status_Cdto_Inc_Value(void)
{
	int ret = 0;
	UINT32 Current_Inc_Value = 0;
	static UINT32 Prev_Inc_Value = STANDARD_CDTO_INC_VALUE;
	UINT32 Difference_Value = 0;


	CVD_Reg_RdFL(iris_006);
	CVD_Reg_Rd01(iris_006, reg_status_cdto_inc, Current_Inc_Value);

	Difference_Value = abs(Current_Inc_Value - Prev_Inc_Value);
	Prev_Inc_Value = Current_Inc_Value;

	//AFE_PRINT("CVD_CDTO : Variance[%d]\n", Difference_Value);

	ret = Difference_Value;
	return ret;
}


UINT32 CVD_Hal_Read_Cordic_Freq_Value(void)
{
	int ret = 0;
	UINT8 Cordic_Value = 0;


	CVD_Reg_RdFL(iris_008);
	CVD_Reg_Rd01(iris_008, reg_status_cordic_freq, Cordic_Value);

	Cordic_Value = (UINT8)((SINT8)Cordic_Value + 0x80);

	ret = Cordic_Value;
	return ret;
}


int	CVD_Hal_Read_VCR_Detected(void)
{
	int ret = 0;
	UINT32 VCR_Detected_Flag = 0;

	CVD_Reg_RdFL(iris_003);
	CVD_Reg_Rd01(iris_003, reg_vcr, VCR_Detected_Flag);

	if(VCR_Detected_Flag) ret = 1;
	else ret = 0;

	return ret;
}

int CVD_Hal_Get_CVD_Burst_Mag_Value(void)
{
	UINT16 burst_mag_status;
	CVD_Reg_RdFL(iris_004);
	CVD_Reg_Rd01(iris_004,reg_status_burst_mag,burst_mag_status);

	return (int)burst_mag_status;
}

int CVD_Hal_Set_CVD_Saturation_Value(int value)
{
	value &= 0xFF;

	CVD_Reg_RdFL(iris_021);
	CVD_Reg_Wr01(iris_021, reg_saturation, value);
	CVD_Reg_WrFL(iris_021);

	return 0;
}

int CVD_Hal_Get_CAGC_Value(void)
{
	int ret;

	CVD_Reg_RdFL(iris_022);
	CVD_Reg_Rd01(iris_022, reg_cagc, ret);

	return ret;
}

int CVD_Hal_Get_Saturation_Value(void)
{
	int ret;

	CVD_Reg_RdFL(iris_021);
	CVD_Reg_Rd01(iris_021, reg_saturation, ret);

	return ret;
}

int CVD_Hal_Get_AGC_Peak_En_Value(void)
{
	int ret;

	CVD_Reg_RdFL(iris_025);
	CVD_Reg_Rd01(iris_025, reg_agc_peak_en, ret);

	return ret;
}

int CVD_Hal_Get_AGC_Bypass_Value(void)
{
	int ret;

	CVD_Reg_RdFL(iris_098);
	CVD_Reg_Rd01(iris_098,  reg_agc_bypass, ret);

	return ret;
}
int CVD_Hal_Get_Vdetect_Vcount_Value(void)
{
	int vcount;
	CVD_Reg_RdFL(iris_274);
	CVD_Reg_Rd01(iris_274, reg_status_vdetect_vcount, vcount);

	return vcount;
}

int CVD_Hal_Get_oadj_c_coeff_value(void)
{
	int oadj_c_coeff_value;
	CVD_Reg_RdFL(iris_122);
	CVD_Reg_Rd01(iris_122, reg_oadj_c_coeff, oadj_c_coeff_value);

	return oadj_c_coeff_value;
}

int CVD_Hal_OnOff_Chromalock_Ckill(BOOLEAN bonoff)
{
	CVD_DEBUG("%s entered :  %d \n",__func__, bonoff);
	CVD_Reg_RdFL(iris_047);

	if(bonoff)
		CVD_Reg_Wr01(iris_047, reg_lose_chromalock_ckill, 0x1);
	else
		CVD_Reg_Wr01(iris_047, reg_lose_chromalock_ckill, 0x0);

	CVD_Reg_WrFL(iris_047);
	return 0;
}

int CVD_Hal_Reset_mif(int enable)
{
	if(enable >0)
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau, 1);
		CVD_Reg_WrFL(iris_175);
	}
	else
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau, 0);
		CVD_Reg_WrFL(iris_175);
	}
	return 0;
}

int CVD_Hal_Set_HNon_Standard_Threshold(int value)
{
	int threshold;
	CVD_Reg_RdFL(iris_024);
	CVD_Reg_Rd01(iris_024, reg_hnon_std_threshold, threshold);
	if(threshold != value) {
		CVD_DEBUG("HNon_Std_Threshold to [0x%x]\n", value);
		CVD_Reg_Wr01(iris_024, reg_hnon_std_threshold, value);
		CVD_Reg_WrFL(iris_024);
	}

	return 0;
}

int CVD_Hal_Get_Crunky_Status(LX_AFE_CVD_CK_T *pCK_Detection_t)
{
	if(CVD_Hal_Get_HLock_Flag() && CVD_Hal_Get_VLock_Flag())
	{
		CVD_Reg_RdFL(iris_001);
		CVD_Reg_Rd02(iris_001, reg_mv_vbi_detected, pCK_Detection_t->ck_vbi_detected , reg_mv_colourstripes, pCK_Detection_t->ck_colorstrip_detected);
	}
	else
	{
		pCK_Detection_t->ck_vbi_detected = 0;
		pCK_Detection_t->ck_colorstrip_detected = 0;
	}

	return 0;
}

/* This function is used for workaround code for no burst signal jitter issue */
int CVD_Hal_Burst_Gate_Control(UINT32	gate_start, UINT32 gate_end)
{
	CVD_DEBUG("CVD Burst Gate Control : Start[0x%x], End[0x%x]\n", gate_start, gate_end);

	CVD_Reg_RdFL(iris_035);
	CVD_Reg_Wr02(iris_035, reg_burst_gate_start, gate_start, reg_burst_gate_end, gate_end);
	CVD_Reg_WrFL(iris_035);

	return 0;
}

int CVD_Hal_Read_Buffer_Status(UINT32 *rbuf1_empty, UINT32 *rbuf2_empty, UINT32 *rbuf3_empty, UINT32 *rbuf4_empty, UINT32 *wbuf_empty, UINT32 *wbuf_ful)
{
	CVD_Reg_RdFL(iris_mif_gmau_mon_001);
	CVD_Reg_RdFL(iris_mif_gmau_mon_002);
	CVD_Reg_RdFL(iris_mif_gmau_mon_003);
	CVD_Reg_Rd02(iris_mif_gmau_mon_001, ro_rbuf1_empty, *rbuf1_empty , ro_rbuf2_empty, *rbuf2_empty);
	CVD_Reg_Rd02(iris_mif_gmau_mon_002, ro_rbuf3_empty, *rbuf3_empty , ro_rbuf4_empty, *rbuf4_empty);
	CVD_Reg_Rd02(iris_mif_gmau_mon_003, ro_wbuf_full, *wbuf_ful, ro_wbuf_empty, *wbuf_empty );

	return 0;
}

int CVD_Hal_vf_nstd_control(unsigned int value)
{
	CVD_Reg_RdFL(iris_067);
	CVD_Reg_Wr01(iris_067, reg_vf_nstd_en, value);	// default 0x1
	CVD_Reg_WrFL(iris_067);

	return 0;
}

int CVD_Hal_Set_CAGC_Value(UINT32 cagc_value)
{
	if(cagc_value > 0xff)
		return -1;

	CVD_Reg_RdFL(iris_022);
	CVD_Reg_Wr01(iris_022, reg_cagc, cagc_value);
	CVD_Reg_WrFL(iris_022);

	return 0;
}

int CVD_Hal_Enable_Stable_Sync_Mode(int enable)
{
	int lpf_on;

	CVD_DEBUG("%s entered :  %d \n",__func__, enable);

	if(enable == 3)	// for NTSC RF Signal (strong hsync filter)
	{
		//0x4774
		// falling/rising_phase
		CVD_Reg_RdFL(iris_347);
		//CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018102);
		CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018002);
		CVD_Reg_WrFL(iris_347);
		//0x4798
		CVD_Reg_RdFL(iris_356);
		CVD_Reg_Wr01(iris_356, reg_hdetect_nr_ctrl4, 0x09861a86);
		CVD_Reg_WrFL(iris_356);
		//0x4778
		// eq_phase
		CVD_Reg_RdFL(iris_348);
		//CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018102);
		CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018002);
		CVD_Reg_WrFL(iris_348);
		//0x479c
		CVD_Reg_RdFL(iris_357);
		CVD_Reg_Wr01(iris_357, reg_hdetect_nr_ctrl5, 0x00001a86);
		CVD_Reg_WrFL(iris_357);
		//0x477c
		// fine_phase
		CVD_Reg_RdFL(iris_349);
		//CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018102);
		CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018042);
		CVD_Reg_WrFL(iris_349);
		//0x47a0
		CVD_Reg_RdFL(iris_358);
		CVD_Reg_Wr01(iris_358, reg_hdetect_nr_ctrl6, 0x00001a86);
		CVD_Reg_WrFL(iris_358);
		//0x4780
		// phase_diff
		CVD_Reg_RdFL(iris_350);
		//CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x28018102);
		CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x28018002);
		CVD_Reg_WrFL(iris_350);
		//0x47a4
		CVD_Reg_RdFL(iris_359);
		CVD_Reg_Wr01(iris_359, reg_hdetect_nr_ctrl7, 0x40001a86);
		CVD_Reg_WrFL(iris_359);
		//reg_clampagc_syncs_lpf_on '1'
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on | 0x02);
		CVD_Reg_WrFL(iris_076);

	}
	else if(enable == 2)	// for NTSC RF Signal 
	{
		//0x4774
		// falling/rising_phase
		CVD_Reg_RdFL(iris_347);
		//CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018102);
		CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018000);
		CVD_Reg_WrFL(iris_347);
		//0x4798
		CVD_Reg_RdFL(iris_356);
		CVD_Reg_Wr01(iris_356, reg_hdetect_nr_ctrl4, 0x09861a86);
		CVD_Reg_WrFL(iris_356);
		//0x4778
		// eq_phase
		CVD_Reg_RdFL(iris_348);
		//CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018102);
		CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018002);
		CVD_Reg_WrFL(iris_348);
		//0x479c
		CVD_Reg_RdFL(iris_357);
		CVD_Reg_Wr01(iris_357, reg_hdetect_nr_ctrl5, 0x00001a86);
		CVD_Reg_WrFL(iris_357);
		//0x477c
		// fine_phase
		CVD_Reg_RdFL(iris_349);
		//CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018102);
		CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018080);
		CVD_Reg_WrFL(iris_349);
		//0x47a0
		CVD_Reg_RdFL(iris_358);
		CVD_Reg_Wr01(iris_358, reg_hdetect_nr_ctrl6, 0x00001a86);
		CVD_Reg_WrFL(iris_358);
		//0x4780
		// phase_diff
		CVD_Reg_RdFL(iris_350);
		//CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x28018102);
		CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x28018082);
		CVD_Reg_WrFL(iris_350);
		//0x47a4
		CVD_Reg_RdFL(iris_359);
		CVD_Reg_Wr01(iris_359, reg_hdetect_nr_ctrl7, 0x40001a86);
		CVD_Reg_WrFL(iris_359);
		//reg_clampagc_syncs_lpf_on '1'
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on | 0x02);
		CVD_Reg_WrFL(iris_076);

	}
	else if(enable == 1)	// for RF signal but not locked, enabled dcrestore_lpf_en.
	{
		//0x4774
		CVD_Reg_RdFL(iris_347);
		CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018000);
		CVD_Reg_WrFL(iris_347);
		//0x4798
		CVD_Reg_RdFL(iris_356);
		CVD_Reg_Wr01(iris_356, reg_hdetect_nr_ctrl4, 0x09861a86);
		CVD_Reg_WrFL(iris_356);
		//0x4778
		CVD_Reg_RdFL(iris_348);
		CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018000);
		CVD_Reg_WrFL(iris_348);
		//0x479c
		CVD_Reg_RdFL(iris_357);
		CVD_Reg_Wr01(iris_357, reg_hdetect_nr_ctrl5, 0x00001a86);
		CVD_Reg_WrFL(iris_357);
		//0x477c
		CVD_Reg_RdFL(iris_349);
		CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018080);
		CVD_Reg_WrFL(iris_349);
		//0x47a0
		CVD_Reg_RdFL(iris_358);
		CVD_Reg_Wr01(iris_358, reg_hdetect_nr_ctrl6, 0x00001a86);
		CVD_Reg_WrFL(iris_358);
		//0x4780
		CVD_Reg_RdFL(iris_350);
		CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x28018080);
		CVD_Reg_WrFL(iris_350);
		//0x47a4
		CVD_Reg_RdFL(iris_359);
		CVD_Reg_Wr01(iris_359, reg_hdetect_nr_ctrl7, 0x40001a86);
		CVD_Reg_WrFL(iris_359);
		//reg_clampagc_syncs_lpf_on '0'
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		//CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on & 0x1);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on | 0x02);
		CVD_Reg_WrFL(iris_076);
	}
	else // for Auto Programming and AV input mode, restoring default register values
	{
		//0x4774
		CVD_Reg_RdFL(iris_347);
		CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018100);
		CVD_Reg_WrFL(iris_347);
		//0x4798
		CVD_Reg_RdFL(iris_356);
		CVD_Reg_Wr01(iris_356, reg_hdetect_nr_ctrl4, 0x09861a86);
		CVD_Reg_WrFL(iris_356);
		//0x4778
		CVD_Reg_RdFL(iris_348);
		CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018100);
		CVD_Reg_WrFL(iris_348);
		//0x479c
		CVD_Reg_RdFL(iris_357);
		CVD_Reg_Wr01(iris_357, reg_hdetect_nr_ctrl5, 0x00001a86);
		CVD_Reg_WrFL(iris_357);
		//0x477c
		CVD_Reg_RdFL(iris_349);
		CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018100);
		CVD_Reg_WrFL(iris_349);
		//0x47a0
		CVD_Reg_RdFL(iris_358);
		CVD_Reg_Wr01(iris_358, reg_hdetect_nr_ctrl6, 0x00001a86);
		CVD_Reg_WrFL(iris_358);
		//0x4780
		CVD_Reg_RdFL(iris_350);
		CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x28018100);
		CVD_Reg_WrFL(iris_350);
		//0x47a4
		CVD_Reg_RdFL(iris_359);
		CVD_Reg_Wr01(iris_359, reg_hdetect_nr_ctrl7, 0x40001a86);
		CVD_Reg_WrFL(iris_359);
		//reg_clampagc_syncs_lpf_on '0'
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on & 0x1);
		CVD_Reg_WrFL(iris_076);
	}
	return 0;

}

int CVD_Hal_Enable_LPF_en(int enable)
{
	int lpf_on;

	CVD_DEBUG("%s entered :  %d \n",__func__, enable);

	if(enable > 0)	// for NTSC RF Signal
	{
		//reg_clampagc_syncs_lpf_on '1'
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on | 0x02);
		CVD_Reg_WrFL(iris_076);

	}
	else
	{
		//reg_clampagc_syncs_lpf_on '1'
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on & 0x01);
		CVD_Reg_WrFL(iris_076);

	}
	return 0;
}

int CVD_Hal_Hstart_Position_Compensator(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	int lpf_on;

	CVD_Reg_RdFL(iris_076);
	CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);

	if(lpf_on & 0x02)
	{
		CVD_Reg_RdFL(iris_263);
		CVD_Reg_Wr01(iris_263, reg_hrs_ha_start, pSet_system_t->reg_rf_hrs_ha_start - 5);
		CVD_Reg_WrFL(iris_263);
	}
	else
	{
		CVD_Reg_RdFL(iris_263);
		CVD_Reg_Wr01(iris_263, reg_hrs_ha_start, pSet_system_t->reg_rf_hrs_ha_start);
		CVD_Reg_WrFL(iris_263);
	}

	return 0;
}

int CVD_Hal_Init_Level_Detector(CVD_STATE_T color_system)
{
	CVD_DEBUG("%s entered :  %d \n",__func__, color_system);

	if(color_system == CVD_STATE_NTSC) {
		CVD_Reg_Wr01(lvl_001, reg_ycsep_lvl_ctrl0, 0x3);	// [1]:measure block height (0=64, 1=128), [0] : measure block width (0=8*4, 1=16*4)
		CVD_Reg_WrFL(lvl_001);
		CVD_Reg_Wr01(lvl_002, reg_ycsep_lvl_ctrl1, 0x04203b56);	// [0][1][2][3] hstart point
		CVD_Reg_WrFL(lvl_002);
		CVD_Reg_Wr01(lvl_003, reg_ycsep_lvl_ctrl2, 0x728da8c3);	// [4][5][6][7] hstart point
		CVD_Reg_WrFL(lvl_003);
		CVD_Reg_Wr01(lvl_006, reg_ycsep_lvl_ctrl5, 0x04203b56);	// [8][9][10][11] hstart point
		CVD_Reg_WrFL(lvl_006);
		CVD_Reg_Wr01(lvl_007, reg_ycsep_lvl_ctrl6, 0x728da8c3);	// [12][13][14][15] hstart point
		CVD_Reg_WrFL(lvl_007);
	}
	else if(color_system == CVD_STATE_PALi) {
		CVD_Reg_Wr01(lvl_001, reg_ycsep_lvl_ctrl0, 0x3);	// [1]:measure block height (0=64, 1=128), [0] : measure block width (0=8*4, 1=16*4)
		CVD_Reg_WrFL(lvl_001);
		CVD_Reg_Wr01(lvl_002, reg_ycsep_lvl_ctrl1, 0x0624425f);	// [0][1][2][3] hstart point
		CVD_Reg_WrFL(lvl_002);
		CVD_Reg_Wr01(lvl_003, reg_ycsep_lvl_ctrl2, 0x7d9ab8d5);	// [4][5][6][7] hstart point
		CVD_Reg_WrFL(lvl_003);
		CVD_Reg_Wr01(lvl_006, reg_ycsep_lvl_ctrl5, 0x0624425f);	// [8][9][10][11] hstart point
		CVD_Reg_WrFL(lvl_006);
		CVD_Reg_Wr01(lvl_007, reg_ycsep_lvl_ctrl6, 0x7d9ab8d5);	// [12][13][14][15] hstart point
		CVD_Reg_WrFL(lvl_007);
	}
	else if(color_system == CVD_STATE_PALm) {
		CVD_Reg_Wr01(lvl_001, reg_ycsep_lvl_ctrl0, 0x2);	// [1]:measure block height (0=64, 1=128), [0] : measure block width (0=8*4, 1=16*4)
		CVD_Reg_WrFL(lvl_001);
		CVD_Reg_Wr01(lvl_002, reg_ycsep_lvl_ctrl1, 0x041c344c);	// [0][1][2][3] hstart point
		CVD_Reg_WrFL(lvl_002);
		CVD_Reg_Wr01(lvl_003, reg_ycsep_lvl_ctrl2, 0x647c94ab);	// [4][5][6][7] hstart point
		CVD_Reg_WrFL(lvl_003);
		CVD_Reg_Wr01(lvl_006, reg_ycsep_lvl_ctrl5, 0x041c344c);	// [8][9][10][11] hstart point
		CVD_Reg_WrFL(lvl_006);
		CVD_Reg_Wr01(lvl_007, reg_ycsep_lvl_ctrl6, 0x647c94ab);	// [12][13][14][15] hstart point
		CVD_Reg_WrFL(lvl_007);
	}
	else if(color_system == CVD_STATE_PALCn) {
		CVD_Reg_Wr01(lvl_001, reg_ycsep_lvl_ctrl0, 0x2);	// [1]:measure block height (0=64, 1=128), [0] : measure block width (0=8*4, 1=16*4)
		CVD_Reg_WrFL(lvl_001);
		CVD_Reg_Wr01(lvl_002, reg_ycsep_lvl_ctrl1, 0x031c344c);	// [0][1][2][3] hstart point
		CVD_Reg_WrFL(lvl_002);
		CVD_Reg_Wr01(lvl_003, reg_ycsep_lvl_ctrl2, 0x647c94ac);	// [4][5][6][7] hstart point
		CVD_Reg_WrFL(lvl_003);
		CVD_Reg_Wr01(lvl_006, reg_ycsep_lvl_ctrl5, 0x031c344c);	// [8][9][10][11] hstart point
		CVD_Reg_WrFL(lvl_006);
		CVD_Reg_Wr01(lvl_007, reg_ycsep_lvl_ctrl6, 0x647c94ac);	// [12][13][14][15] hstart point
		CVD_Reg_WrFL(lvl_007);
	}

	return 0;
}

int CVD_Hal_Get_ColorBar_Level(UINT8 *Composite_Level)
{
	UINT32 level_7_4, level_3_0, level_15_12, level_11_8;

	CVD_Reg_RdFL(lvl_010);
	CVD_Reg_Rd01(lvl_010,  reg_status_ycsep_lvl0, level_7_4);
	AFE_TRACE("[7_4]th = [0x%x]\n", level_7_4);
	CVD_Reg_RdFL(lvl_011);
	CVD_Reg_Rd01(lvl_011,  reg_status_ycsep_lvl1, level_3_0);
	AFE_TRACE("[3_0]th = [0x%x]\n", level_3_0);

	CVD_Reg_RdFL(lvl_016);
	CVD_Reg_Rd01(lvl_016,  reg_status_ycsep_lvl6, level_15_12);
	AFE_TRACE("[15_12]th = [0x%x]\n", level_15_12);
	CVD_Reg_RdFL(lvl_017);
	CVD_Reg_Rd01(lvl_017,  reg_status_ycsep_lvl7, level_11_8);
	AFE_TRACE("[11_8]th = [0x%x]\n", level_11_8);

	Composite_Level[15] = (level_15_12 >> 24) & 0xFF;
	Composite_Level[14] = (level_15_12 >> 16) & 0xFF;
	Composite_Level[13] = (level_15_12 >> 8) & 0xFF;
	Composite_Level[12] = (level_15_12 >> 0) & 0xFF;

	Composite_Level[11] = (level_11_8 >> 24) & 0xFF;
	Composite_Level[10] = (level_11_8 >> 16) & 0xFF;
	Composite_Level[9] = (level_11_8 >> 8) & 0xFF;
	Composite_Level[8] = (level_11_8 >> 0) & 0xFF;

	Composite_Level[7] = (level_7_4 >> 24) & 0xFF;
	Composite_Level[6] = (level_7_4 >> 16) & 0xFF;
	Composite_Level[5] = (level_7_4 >> 8) & 0xFF;
	Composite_Level[4] = (level_7_4 >> 0) & 0xFF;

	Composite_Level[3] = (level_3_0 >> 24) & 0xFF;
	Composite_Level[2] = (level_3_0 >> 16) & 0xFF;
	Composite_Level[1] = (level_3_0 >> 8) & 0xFF;
	Composite_Level[0] = (level_3_0 >> 0) & 0xFF;

	return 0;
}

int CVD_Hal_chromalock_level_control(unsigned int value)
{
	CVD_Reg_RdFL(iris_047);
	CVD_Reg_Wr01(iris_047, reg_lose_chromalock_level, value);	// default 0x7
	CVD_Reg_WrFL(iris_047);

	return 0;
}

int CVD_Hal_Set_SCART_Filter(void)
{
	CVD_DEBUG("%s entered \n",__func__);
	CVD_Reg_RdFL(iris_360);
	CVD_Reg_RdFL(iris_361);
	CVD_Reg_RdFL(iris_362);
	CVD_Reg_RdFL(iris_363);
	CVD_Reg_Wr01(iris_360, reg_fb_clpf_ctrl0, 0x00010000 );
	CVD_Reg_Wr01(iris_361, reg_fb_clpf_ctrl1, 0x00000000 );
	CVD_Reg_Wr01(iris_362, reg_fb_clpf_ctrl2, 0x00000000 );
	CVD_Reg_Wr01(iris_363, reg_fb_clpf_ctrl3, 0x20004000 );
	CVD_Reg_WrFL(iris_360);
	CVD_Reg_WrFL(iris_361);
	CVD_Reg_WrFL(iris_362);
	CVD_Reg_WrFL(iris_363);
	return 0;
}

int CVD_Hal_agc_half_en_control(int enable) //gogosing agc
{
	// For faster agc speed at channel change, set hagc_field_mode value to '1'
	if(enable){
	CVD_Reg_RdFL(iris_015);
	CVD_Reg_Wr01(iris_015, reg_agc_half_en, 1); //gogosing
	CVD_Reg_WrFL(iris_015);
	}
	else{
	CVD_Reg_RdFL(iris_015);
	CVD_Reg_Wr01(iris_015, reg_agc_half_en, 0); //gogosing
	CVD_Reg_WrFL(iris_015);
	}
	return 0;
}

int CVD_Hal_Set_Motion_Expand(int enable)
{
	UINT32 tmp;
	static int	motion_expand_enabled = -1;

	if(motion_expand_enabled == enable)
		return 0;
	else
		motion_expand_enabled = enable;

	CVD_DEBUG("%s [%d] \n",__func__, enable);

	if(enable)
	{
		// 0x4570[8] = 1
		CVD_Reg_RdFL(iris_220);
		CVD_Reg_Rd01(iris_220, reg_ycsep_3d_ctrl0, tmp);
		tmp = tmp | 0x100;
		CVD_Reg_Wr01(iris_220, reg_ycsep_3d_ctrl0, tmp);
		CVD_Reg_WrFL(iris_220);

		// 0x4590[31:24] = 0
		CVD_Reg_RdFL(iris_228);
		CVD_Reg_Rd01(iris_228, reg_ycsep_st_ctrl0, tmp);
		tmp = tmp & 0x00FFFFFF;
		CVD_Reg_Wr01(iris_228, reg_ycsep_st_ctrl0, tmp);
		CVD_Reg_WrFL(iris_228);

	}
	else
	{
		// 0x4570[8] = 0
		CVD_Reg_RdFL(iris_220);
		CVD_Reg_Rd01(iris_220, reg_ycsep_3d_ctrl0, tmp);
		tmp = tmp & 0xFFFFFEFF;
		CVD_Reg_Wr01(iris_220, reg_ycsep_3d_ctrl0, tmp);
		CVD_Reg_WrFL(iris_220);

		// 0x4590[31:24] = 0x0C 
		CVD_Reg_RdFL(iris_228);
		CVD_Reg_Rd01(iris_228, reg_ycsep_st_ctrl0, tmp);
		tmp = tmp | 0x0C000000;
		CVD_Reg_Wr01(iris_228, reg_ycsep_st_ctrl0, tmp);
		CVD_Reg_WrFL(iris_228);

	}

	return 0;
}

//CCR off only when NTSC Color Bar
int CVD_Hal_Set_CCR(int ccr_value)
{
	UINT32 tmp;
	static int	prev_ccr_value = -1;

	if(prev_ccr_value == ccr_value)
		return 0;
	else
		prev_ccr_value = ccr_value;

	CVD_DEBUG("%s [%d] \n",__func__, ccr_value);

	if(ccr_value == 0)
	{
		// 0x4740[3:0] = 0
		CVD_Reg_RdFL(iris_334);
		CVD_Reg_Rd01(iris_334, reg_ycsep_2d_ctrl37, tmp);
		tmp = tmp & 0xFFFFFFFC;
		CVD_Reg_Wr01(iris_334, reg_ycsep_2d_ctrl37, tmp);
		CVD_Reg_WrFL(iris_334);
	}
	else
	{
		// 0x4740[3:0] = 0
		CVD_Reg_RdFL(iris_334);
		CVD_Reg_Rd01(iris_334, reg_ycsep_2d_ctrl37, tmp);
		tmp = (tmp & 0xFFFFFFFC) | 0x00000002;	// by choi :130129
		CVD_Reg_Wr01(iris_334, reg_ycsep_2d_ctrl37, tmp);
		CVD_Reg_WrFL(iris_334);
	}

	return 0;
}

int CVD_Hal_Check_CVD_Memory(void)
{
	UINT32 cnt_mx_lvl, req_cnt_mx_lvl, cnt_mx_lvl_md, req_cnt_mx_lvl_md;
	UINT32 blue_mode;

	CVD_Reg_RdFL(iris_mif_gmau_mon_004);
	CVD_Reg_RdFL(iris_mif_gmau_mon_007);
	CVD_Reg_RdFL(iris_020);

	CVD_Reg_Rd01(iris_mif_gmau_mon_004, ro_read0_svid_cnt_mx_lvl, cnt_mx_lvl);
	CVD_Reg_Rd01(iris_mif_gmau_mon_004, ro_wbuf_read_req_cnt_mx_lvl, req_cnt_mx_lvl);
	CVD_Reg_Rd01(iris_mif_gmau_mon_007, ro_read0_svid_cnt_mx_lvl_md, cnt_mx_lvl_md);
	CVD_Reg_Rd01(iris_mif_gmau_mon_007, ro_wbuf_read_req_cnt_mx_lvl_md, req_cnt_mx_lvl_md);
	CVD_Reg_Rd01(iris_020, reg_blue_mode, blue_mode);

	if( (cnt_mx_lvl) || (req_cnt_mx_lvl) || (cnt_mx_lvl_md) || (req_cnt_mx_lvl_md) || (blue_mode == 3))
	{
		CVD_Reg_RdFL(iris_mif_gmau_mon_001);
		CVD_Reg_RdFL(iris_mif_gmau_mon_002);
		CVD_Reg_RdFL(iris_mif_gmau_mon_003);
		CVD_Reg_RdFL(iris_mif_gmau_mon_005);
		CVD_Reg_RdFL(iris_mif_gmau_mon_006);

		AFE_PRINT("!!!!!!!!!!!!!!!!!!!!\n");
		AFE_PRINT("!!!!!!!!!!!!!!!!!!!!\n");
		AFE_PRINT("!!! CVD Memory ERROR !!!\n");
		AFE_PRINT("!!! CVD Memory ERROR !!!\n");
		AFE_PRINT("!!! CVD Memory ERROR !!!\n");
		AFE_PRINT("!!! CVD Memory ERROR !!!\n");
		AFE_PRINT("!!! CVD Memory ERROR !!!\n");
		AFE_PRINT("!!! CVD Memory ERROR !!!\n");
		AFE_PRINT("!!!!!!!!!!!!!!!!!!!!\n");
		AFE_PRINT("!!!!!!!!!!!!!!!!!!!!\n");
		AFE_PRINT("!!! GMUA1 = [0x%08x]\n", CVD_Reg_Rd(iris_mif_gmau_mon_001) );
		AFE_PRINT("!!! GMUA2 = [0x%08x]\n", CVD_Reg_Rd(iris_mif_gmau_mon_002) );
		AFE_PRINT("!!! GMUA3 = [0x%08x]\n", CVD_Reg_Rd(iris_mif_gmau_mon_003) );
		AFE_PRINT("!!! GMUA4 = [0x%08x]\n", CVD_Reg_Rd(iris_mif_gmau_mon_004) );
		AFE_PRINT("!!! GMUA5 = [0x%08x]\n", CVD_Reg_Rd(iris_mif_gmau_mon_005) );
		AFE_PRINT("!!! GMUA6 = [0x%08x]\n", CVD_Reg_Rd(iris_mif_gmau_mon_006) );
		AFE_PRINT("!!! GMUA7 = [0x%08x]\n", CVD_Reg_Rd(iris_mif_gmau_mon_007) );
		AFE_PRINT("!!!!!!!!!!!!!!!!!!!!\n");
		AFE_PRINT("!!!!!!!!!!!!!!!!!!!!\n");
	}

	return 0;
}

/* Enhanced Sync Stablity on PAL-M Weak RF signal */
int CVD_Hal_Set_PALm_Stable_HSync_Mode(int enable)
{
	CVD_DEBUG("%s entered :  %d \n",__func__, enable);

	if(enable)
	{
		//for Brazil Field Stream : NTSC_120912_00607
		CVD_Reg_RdFL(iris_031);
		CVD_Reg_Wr01(iris_031, reg_hsync_phase_offset, 0x28);
		CVD_Reg_WrFL(iris_031);
	}
	else
	{
		CVD_Reg_RdFL(iris_031);
		CVD_Reg_Wr01(iris_031, reg_hsync_phase_offset, 0x3e);	//default value
		CVD_Reg_WrFL(iris_031);
	}

	return 0;
}

/* Enhanced Sync Stablity on PAL-M Weak RF signal */
int CVD_Hal_Set_PALm_Stable_VSync_Mode(int enable)
{
	CVD_DEBUG("%s entered :  %d \n",__func__, enable);

	if(enable)
	{
		//for Brazil Field Stream : NTSC_120912_0442
		CVD_Reg_RdFL(iris_041);
		CVD_Reg_Wr01(iris_041, reg_vsync_l_cnt, 0x4);
		CVD_Reg_WrFL(iris_041);

		CVD_Reg_RdFL(iris_015);
		CVD_Reg_Wr01(iris_015, reg_agc_half_en, 1);
		CVD_Reg_WrFL(iris_015);
		CVD_Reg_RdFL(iris_024);
		CVD_Reg_Wr01(iris_024, reg_nstd_hysis, 2);
		CVD_Reg_WrFL(iris_024);

		//added 120114 for stable agc
		CVD_Reg_RdFL(iris_025);
		CVD_Reg_Wr01(iris_025, reg_agc_peak_cntl, 0x0);
		CVD_Reg_WrFL(iris_025);
		CVD_Reg_RdFL(iris_074);
		CVD_Reg_Wr01(iris_074, reg_dcrestore_gain, 0x3);
		CVD_Reg_WrFL(iris_074);

		CVD_Reg_RdFL(iris_054);
		CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_mode, 0x1);
		CVD_Reg_WrFL(iris_054);
	}
	else
	{
		CVD_Reg_RdFL(iris_041);
		CVD_Reg_Wr01(iris_041, reg_vsync_l_cnt, 0x0);	//default value
		CVD_Reg_WrFL(iris_041);

		CVD_Reg_RdFL(iris_015);
		CVD_Reg_Wr01(iris_015, reg_agc_half_en, 0);
		CVD_Reg_WrFL(iris_015);
		CVD_Reg_RdFL(iris_024);
		CVD_Reg_Wr01(iris_024, reg_nstd_hysis, 7);
		CVD_Reg_WrFL(iris_024);


		//added 120114 for stable agc (restore default values)
		CVD_Reg_RdFL(iris_025);
		CVD_Reg_Wr01(iris_025, reg_agc_peak_cntl, 0x1);
		CVD_Reg_WrFL(iris_025);
		CVD_Reg_RdFL(iris_074);
		CVD_Reg_Wr01(iris_074, reg_dcrestore_gain, 0x0);
		CVD_Reg_WrFL(iris_074);

		CVD_Reg_RdFL(iris_054);
		CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_mode, 0x2);
		CVD_Reg_WrFL(iris_054);
	}

	return 0;
}

int CVD_Hal_3DComb_Workaround(int step)
{
	int ret = 0;
#ifdef M16_CDTO_CONTROL
	UINT32 cdto_value;
#endif
	static int func_bypass = 0;

	CVD_WA_DEBUG("%s entered :  step[%d], bypass[%d] \n",__func__, step, func_bypass);

	if( (func_bypass == 1) && (step != 20) )
		return 0;

	CVD_LockDevice();

	if(step == 10)		// step 1 from CVD Channel Power Control(UI task)
	{
		func_bypass = 1;	// bypass workaround function (in other input source)
		step = 1;
	}
	else if(step == 20)	// back to CVD input source
	{
		func_bypass = 0;	// bypass workaround function (in other input source)
	}

	if(step == 1)
	{
#ifdef M16_CDTO_CONTROL
		CVD_Reg_RdFL(iris_029);
		CVD_Reg_Rd01(iris_029, reg_cdto_inc, cdto_value);
		cdto_value |= 0x80000000;
		CVD_Reg_Wr01(iris_029, reg_cdto_inc, cdto_value);
		CVD_Reg_WrFL(iris_029);
#endif

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau, 0x1);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_mif_gmau_008);
		CVD_Reg_Wr01(iris_mif_gmau_008, reg_mif_ctrl, 0x1f);
		CVD_Reg_WrFL(iris_mif_gmau_008);

		CVD_Reg_RdFL(iris_064);
		CVD_Reg_Wr01(iris_064, reg_comb2d_only, 0x1);
		CVD_Reg_WrFL(iris_064);

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau_md, 0x1);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_mif_gmau_md_010);
		CVD_Reg_Wr01(iris_mif_gmau_md_010, reg_mif_ctrl_md, 0x1f);
		CVD_Reg_WrFL(iris_mif_gmau_md_010);

		CVD_Reg_RdFL(iris_066);
		CVD_Reg_Wr01(iris_066, reg_comb2d_only_md, 0x1);
		CVD_Reg_WrFL(iris_066);
	}
	else if(step == 2)
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau, 0);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_mif_gmau_008);
		CVD_Reg_Wr01(iris_mif_gmau_008, reg_mif_ctrl, 0);
		CVD_Reg_WrFL(iris_mif_gmau_008);

		if(gCVD_2d_mode == FALSE)
		{
			CVD_Reg_RdFL(iris_064);
			CVD_Reg_Wr01(iris_064, reg_comb2d_only, 0);
			CVD_Reg_WrFL(iris_064);
		}

	}
	else if(step == 3)
	{
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau_md, 0x0);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_mif_gmau_md_010);
		CVD_Reg_Wr01(iris_mif_gmau_md_010, reg_mif_ctrl_md, 0x0);
		CVD_Reg_WrFL(iris_mif_gmau_md_010);

		if(gCVD_2d_mode == FALSE)
		{
			CVD_Reg_RdFL(iris_066);
			CVD_Reg_Wr01(iris_066, reg_comb2d_only_md, 0x0);
			CVD_Reg_WrFL(iris_066);
		}
	}
	else if(step == 4)
	{
#ifdef M16_CDTO_CONTROL
		CVD_Reg_RdFL(iris_029);
		CVD_Reg_Rd01(iris_029, reg_cdto_inc, cdto_value);
		cdto_value &= 0x7FFFFFFF;
		CVD_Reg_Wr01(iris_029, reg_cdto_inc, cdto_value);
		CVD_Reg_WrFL(iris_029);
#endif
	}
	else if(step == 0)
	{
#if 0
		CVD_Reg_RdFL(iris_029);
		CVD_Reg_Rd01(iris_029, reg_cdto_inc, cdto_value);
		cdto_value &= 0x7FFFFFFF;
		CVD_Reg_Wr01(iris_029, reg_cdto_inc, cdto_value);
		CVD_Reg_WrFL(iris_029);
#endif
		CVD_Reg_RdFL(iris_mif_gmau_008);
		CVD_Reg_Wr01(iris_mif_gmau_008, reg_mif_ctrl, 0);
		CVD_Reg_WrFL(iris_mif_gmau_008);

		CVD_Reg_RdFL(iris_mif_gmau_md_010);
		CVD_Reg_Wr01(iris_mif_gmau_md_010, reg_mif_ctrl_md, 0x0);
		CVD_Reg_WrFL(iris_mif_gmau_md_010);

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau, 0);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau_md, 0x0);
		CVD_Reg_WrFL(iris_175);

		if(gCVD_2d_mode == FALSE)
		{
			CVD_Reg_RdFL(iris_064);
			CVD_Reg_Wr01(iris_064, reg_comb2d_only, 0);
			CVD_Reg_WrFL(iris_064);

			CVD_Reg_RdFL(iris_066);
			CVD_Reg_Wr01(iris_066, reg_comb2d_only_md, 0x0);
			CVD_Reg_WrFL(iris_066);
		}
	}

	CVD_UnlockDevice();

	return ret;
}
/*
int CVD_Hal_3DComb_Workaround(int step)
{
	UINT32 cdto_value;

	AFE_PRINT("%s entered :  %d \n",__func__, step);

	if(step == 1)
	{
#if 0
		CVD_Reg_RdFL(iris_029);
		CVD_Reg_Rd01(iris_029, reg_cdto_inc, cdto_value);
		cdto_value |= 0x80000000;
		CVD_Reg_Wr01(iris_029, reg_cdto_inc, cdto_value);
		CVD_Reg_WrFL(iris_029);
#endif

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau, 0x1);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau_md, 0x1);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_mif_gmau_008);
		CVD_Reg_Wr01(iris_mif_gmau_008, reg_mif_ctrl, 0x1f);
		CVD_Reg_WrFL(iris_mif_gmau_008);

		CVD_Reg_RdFL(iris_mif_gmau_md_010);
		CVD_Reg_Wr01(iris_mif_gmau_md_010, reg_mif_ctrl_md, 0x1f);
		CVD_Reg_WrFL(iris_mif_gmau_md_010);

		CVD_Reg_RdFL(iris_064);
		CVD_Reg_Wr01(iris_064, reg_comb2d_only, 0x1);
		CVD_Reg_WrFL(iris_064);

		CVD_Reg_RdFL(iris_066);
		CVD_Reg_Wr01(iris_066, reg_comb2d_only_md, 0x1);
		CVD_Reg_WrFL(iris_066);
	}
	else if(step == 2)
	{
#if 0
		CVD_Reg_RdFL(iris_029);
		CVD_Reg_Rd01(iris_029, reg_cdto_inc, cdto_value);
		cdto_value |= 0x80000000;
		CVD_Reg_Wr01(iris_029, reg_cdto_inc, cdto_value);
		CVD_Reg_WrFL(iris_029);
#endif

		CVD_Reg_RdFL(iris_mif_gmau_008);
		CVD_Reg_Wr01(iris_mif_gmau_008, reg_mif_ctrl, 0);
		CVD_Reg_WrFL(iris_mif_gmau_008);

		CVD_Reg_RdFL(iris_mif_gmau_md_010);
		CVD_Reg_Wr01(iris_mif_gmau_md_010, reg_mif_ctrl_md, 0x0);
		CVD_Reg_WrFL(iris_mif_gmau_md_010);

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau, 0);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau_md, 0x0);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_064);
		CVD_Reg_Wr01(iris_064, reg_comb2d_only, 0);
		CVD_Reg_WrFL(iris_064);

		CVD_Reg_RdFL(iris_066);
		CVD_Reg_Wr01(iris_066, reg_comb2d_only_md, 0x0);
		CVD_Reg_WrFL(iris_066);
	}
	else if(step == 0)
	{
#if 0
		CVD_Reg_RdFL(iris_029);
		CVD_Reg_Rd01(iris_029, reg_cdto_inc, cdto_value);
		cdto_value &= 0x7FFFFFFF;
		CVD_Reg_Wr01(iris_029, reg_cdto_inc, cdto_value);
		CVD_Reg_WrFL(iris_029);
#endif
		CVD_Reg_RdFL(iris_mif_gmau_008);
		CVD_Reg_Wr01(iris_mif_gmau_008, reg_mif_ctrl, 0);
		CVD_Reg_WrFL(iris_mif_gmau_008);

		CVD_Reg_RdFL(iris_mif_gmau_md_010);
		CVD_Reg_Wr01(iris_mif_gmau_md_010, reg_mif_ctrl_md, 0x0);
		CVD_Reg_WrFL(iris_mif_gmau_md_010);

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau, 0);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_mif_gmau_md, 0x0);
		CVD_Reg_WrFL(iris_175);

		CVD_Reg_RdFL(iris_064);
		CVD_Reg_Wr01(iris_064, reg_comb2d_only, 0);
		CVD_Reg_WrFL(iris_064);

		CVD_Reg_RdFL(iris_066);
		CVD_Reg_Wr01(iris_066, reg_comb2d_only_md, 0x0);
		CVD_Reg_WrFL(iris_066);
	}

	return 0;
}
*/

void CVD_Hal_Program_Color_System_Size(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	CVD_CSD_DEBUG("Set CVD Buffer Size [0x%x]\n", pSet_system_t->reg_comb3_buffer_size);

	if(pSet_system_t->reg_comb3_buffer_size > 1)
	{
		CVD_Reg_RdFL(iris_mif_gmau_001);
		CVD_Reg_Wr01(iris_mif_gmau_001, reg_comb3_buffer_size, pSet_system_t->reg_comb3_buffer_size);
		CVD_Reg_WrFL(iris_mif_gmau_001);
		CVD_Reg_RdFL(iris_mif_gmau_002);
		CVD_Reg_Wr01(iris_mif_gmau_002, reg_fld1_init_rd_pel, pSet_system_t->reg_fld1_init_rd_pel);
		CVD_Reg_WrFL(iris_mif_gmau_002);
		CVD_Reg_RdFL(iris_mif_gmau_003);
		CVD_Reg_Wr01(iris_mif_gmau_003, reg_fld2_init_rd_pel, pSet_system_t->reg_fld2_init_rd_pel);
		CVD_Reg_WrFL(iris_mif_gmau_003);
		CVD_Reg_RdFL(iris_mif_gmau_004);
		CVD_Reg_Wr01(iris_mif_gmau_004, reg_fld3_init_rd_pel, pSet_system_t->reg_fld3_init_rd_pel);
		CVD_Reg_WrFL(iris_mif_gmau_004);
		CVD_Reg_RdFL(iris_mif_gmau_005);
		CVD_Reg_Wr01(iris_mif_gmau_005, reg_fld4_init_rd_pel, pSet_system_t->reg_fld4_init_rd_pel);
		CVD_Reg_WrFL(iris_mif_gmau_005);

		/*
		CVD_Reg_RdFL(iris_mif_gmau_md_001);
		CVD_Reg_Wr01(iris_mif_gmau_md_001, reg_comb3_buffer_size_md, pSet_system_t->reg_comb3_buffer_size_md);
		CVD_Reg_WrFL(iris_mif_gmau_md_001);

		CVD_Reg_RdFL(iris_mif_gmau_md_002);
		CVD_Reg_Wr01(iris_mif_gmau_md_002, reg_fld1_init_rd_pel_md, pSet_system_t->reg_fld1_init_rd_pel_md);
		CVD_Reg_WrFL(iris_mif_gmau_md_002);
		*/
	}
}

void CVD_Hal_Program_Color_System_Size_md(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	CVD_CSD_DEBUG("Set CVD Buffer Size MD [0x%x]\n", pSet_system_t->reg_comb3_buffer_size_md);

	if(pSet_system_t->reg_comb3_buffer_size > 1)
	{
		CVD_Reg_RdFL(iris_mif_gmau_md_001);
		CVD_Reg_Wr01(iris_mif_gmau_md_001, reg_comb3_buffer_size_md, pSet_system_t->reg_comb3_buffer_size_md);
		CVD_Reg_WrFL(iris_mif_gmau_md_001);

		CVD_Reg_RdFL(iris_mif_gmau_md_002);
		CVD_Reg_Wr01(iris_mif_gmau_md_002, reg_fld1_init_rd_pel_md, pSet_system_t->reg_fld1_init_rd_pel_md);
		CVD_Reg_WrFL(iris_mif_gmau_md_002);
	}
}

// for Indonesia Field Stream (PAL_120928_0331, PAL_121002_0306)
int CVD_Hal_Set_Vsync_Cntl(CVD_SET_SYSTEM_3CS_T *pSet_system_t, int enable)
{
	CVD_DEBUG("%s entered :  %d \n",__func__, enable);

	if(enable == 2)
	{
		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042,  reg_vsync_cntl, 0);	// PLL vsync
		CVD_Reg_WrFL(iris_042);
	}
	else if(enable == 1)
	{
		CVD_Reg_RdFL(iris_041);
		CVD_Reg_Wr01(iris_041,  reg_vsync_l_cnt, 2);	// default 0
		CVD_Reg_WrFL(iris_041);

		CVD_Reg_RdFL(iris_037);
		CVD_Reg_Wr01(iris_037, reg_vactive_start, pSet_system_t->reg_vactive_start - 2);
		CVD_Reg_WrFL(iris_037);
	}
	else
	{
		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042,  reg_vsync_cntl, 1);	// direct vsync
		CVD_Reg_WrFL(iris_042);

		CVD_Reg_RdFL(iris_041);
		CVD_Reg_Wr01(iris_041,  reg_vsync_l_cnt, 0);	// default 0
		CVD_Reg_WrFL(iris_041);

		CVD_Reg_RdFL(iris_037);
		CVD_Reg_Wr01(iris_037, reg_vactive_start, pSet_system_t->reg_vactive_start);
		CVD_Reg_WrFL(iris_037);
	}

	return 0;
}

int CVD_Hal_CVD_Soft_Reset(void)
{
	CVD_Reg_RdFL(iris_012);
	CVD_Reg_Wr01(iris_012, reg_cvd_soft_reset, 1);
	CVD_Reg_WrFL(iris_012);

//	OS_MsecSleep(5);

	CVD_Reg_RdFL(iris_012);
	CVD_Reg_Wr01(iris_012, reg_cvd_soft_reset, 0);
	CVD_Reg_WrFL(iris_012);

	return 0;
}

int CVD_Hal_Set_Blue_Mode(int blue)
{
	CVD_Reg_RdFL(iris_020);
	CVD_Reg_Wr01(iris_020, reg_blue_mode, blue);
	CVD_Reg_WrFL(iris_020);

	return 0;
}
int CVD_Hal_Set_OADJ(CVD_REG_PARAM_T	*pCVD_Black_Level_Param_t, UINT32 size)
{
	int count;
	UINT32 value;
	UINT32 recvAddr;
	CVD_DEBUG("%s \n", __func__);
	for(count=0; count < size;count++)
	{
		recvAddr = pCVD_Black_Level_Param_t->cvd_phy_addr;
		value = pCVD_Black_Level_Param_t->cvd_pe_value;
		REG_WD((void *)((uintptr_t)recvAddr + (uintptr_t)gpRealRegCVD - (uintptr_t)0x4100), value);
		pCVD_Black_Level_Param_t++;
	}
	return 0;
}

int CVD_Hal_Set_Vactive_Params(int vline_625_stable)
{
	static int vline_625_stable_prev = -1;

	if(vline_625_stable != vline_625_stable_prev)
	{
		vline_625_stable_prev = vline_625_stable;

		if(vline_625_stable \
			/*	&& ( ( g_CVD_Status_3CS.color_system_support & (LX_COLOR_SYSTEM_PAL_G |LX_COLOR_SYSTEM_PAL_NC | LX_COLOR_SYSTEM_SECAM)) == 0 )*/ )	// 50Hz system detected, and 60Hz only system supporting
		{
			CVD_Reg_RdFL(iris_037);
			//CVD_Reg_Wr02(iris_037, reg_vactive_start, g_SetColorSystem_3CS_M17A0.Color_System_Params[CVD_STATE_PALi].reg_vactive_start, reg_vactive_height, .Color_System_Params[CVD_STATE_PALi].reg_vactive_height);
			CVD_Reg_Wr01(iris_037, reg_vactive_height, pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALi].reg_vactive_height);
			CVD_Reg_WrFL(iris_037);
		}
		else if (vline_625_stable == 0 \
				/* && (( g_CVD_Status_3CS.color_system_support & (LX_COLOR_SYSTEM_NTSC_M |LX_COLOR_SYSTEM_PAL_M | LX_COLOR_SYSTEM_NTSC_443 | LX_COLOR_SYSTEM_PAL_60)) == 0 ) */ )				// 60Hz system detected, and 50Hz only system supporting
		{
			CVD_Reg_RdFL(iris_037);
			//CVD_Reg_Wr02(iris_037, reg_vactive_start, g_SetColorSystem_3CS_M17A0.Color_System_Params[CVD_STATE_NTSC].reg_vactive_start, reg_vactive_height, g_SetColorSystem_3CS_M17A0.Color_System_Params[CVD_STATE_NTSC].reg_vactive_height);
			CVD_Reg_Wr01(iris_037, reg_vactive_height, pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_vactive_height);
			CVD_Reg_WrFL(iris_037);
		}

	}


	return 0;
}

int CVD_Hal_Set_Nosignal_Vactive_Params(void)
{
	if( CVD_Hal_Get_Vline_625_Reg() )	// 50Hz setting
	{
		CVD_Reg_RdFL(iris_037);
		CVD_Reg_Wr02(iris_037, reg_vactive_start, pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALi].reg_vactive_start,\
				reg_vactive_height, pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALi].reg_vactive_height);
		CVD_Reg_WrFL(iris_037);
	}
	else
	{
		CVD_Reg_RdFL(iris_037);
		CVD_Reg_Wr02(iris_037, reg_vactive_start, pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_vactive_start,\
				reg_vactive_height, pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC].reg_vactive_height);
		CVD_Reg_WrFL(iris_037);
	}
	return 0;
}

int CVD_Hal_Set_Cpump_Auto_Stip_Mode(int mode)
{
		CVD_Reg_RdFL(iris_054);
		CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_mode, mode); // default : 0x2
		CVD_Reg_WrFL(iris_054);

		return 0;
}

int CVD_Hal_Set_Blend_Ratio(int value)
{

	CVD_DEBUG("%s entered :  %d \n",__func__, value);

	if(value > 0x10)
		return -1;

	CVD_Reg_RdFL(fastblank_001);
	CVD_Reg_Wr01(fastblank_001, reg_fb_blend_ratio, value);
	CVD_Reg_WrFL(fastblank_001);

	return 0;
}

/**
 * @brief Flags indication PE Param change, sync
 *
 * @param signal_lock : -1 if no change
 * @param color_system : -1 if no change
 * @param rf_av_mode : -1 if no change
 * @param write_done : -1 if no change
 *
 * @return 
 */
int CVD_Hal_Set_PE_Param_Flag(int signal_lock, int color_system, int rf_av_mode, int write_done)
{
	/*
	   0xC002_142C     
	   IRIS_139 [20] : signal_lock
	   IRIS_139 [16] : status_color_system[2]
	   IRIS_139 [12] : status_color_system[1]
	   IRIS_139  [8]   : status_color_system[0]
	   IRIS_139  [4]   : status_rf_av
	   IRIS_139  [0]   : pe_param_changed
	 */
	CVD_Reg_RdFL(iris_139);

	if(signal_lock >= 0)
		CVD_Reg_Wr01(iris_139, cpu2mcu_signal_lock_flag, signal_lock );

	if(color_system >= 0)
	{
		CVD_Reg_Wr01(iris_139, cpu2mcu_status_color_system_2, (color_system & 0x4)>>2 );
		CVD_Reg_Wr01(iris_139, cpu2mcu_status_color_system_1, (color_system & 0x2)>>1 );
		CVD_Reg_Wr01(iris_139, cpu2mcu_status_color_system_0, (color_system & 0x1) );
	}
	if(rf_av_mode >= 0)
		CVD_Reg_Wr01(iris_139, cpu2mcu_status_rf_av, rf_av_mode );
	if(write_done >= 0)
		CVD_Reg_Wr01(iris_139, cpu2mcu_pe_param_changed, write_done );
	CVD_Reg_WrFL(iris_139);

	return 0;
}

/**
 * @brief Vsync Enhancement for RF
 *
 * @param system (0:Off, 1:480 system, 2:567 system)
 *
 * @return 
 */
int CVD_Hal_Set_Vsync_Enhance(int system)
{
	CVD_WA_DEBUG("%s entered :  %d \n",__func__, system);

	if(system == 0)
	{
		CVD_Reg_RdFL(iris_047);
		CVD_Reg_Wr01(iris_047, reg_vslock_dly_ctrl, 0x0);
		CVD_Reg_Wr01(iris_047, reg_vslock_dly_cnt, 0x0);
		CVD_Reg_WrFL(iris_047);

		CVD_Reg_RdFL(iris_038);
		CVD_Reg_Wr01(iris_038, reg_vslock_ctrl, 0x0);
		CVD_Reg_Wr01(iris_038, reg_vslock_hscnt, 0x7);
		CVD_Reg_WrFL(iris_038);

		CVD_Reg_RdFL(iris_039);
		CVD_Reg_Wr01(iris_039, reg_vslock_onth, 0x10);
		CVD_Reg_Wr01(iris_039, reg_vslock_offth, 0x8);
		CVD_Reg_WrFL(iris_039);

		CVD_Reg_RdFL(iris_040);
		CVD_Reg_Wr01(iris_040, reg_vslock_vscnt_max, 0xff);
		CVD_Reg_Wr01(iris_040, reg_vslock_hscnt_margin, 0x10);
		CVD_Reg_WrFL(iris_040);

		CVD_Reg_RdFL(iris_037);
		CVD_Reg_Wr01(iris_037, reg_vslock_hscnt_th, 0x7);
		CVD_Reg_WrFL(iris_037);

		CVD_Reg_RdFL(iris_045);
		CVD_Reg_Wr01(iris_045, reg_vslock_hscnt_ictrl, 0x0);
		CVD_Reg_Wr01(iris_045, reg_vslock_hscnt_iir_alpha, 0x0);
		CVD_Reg_WrFL(iris_045);

		CVD_Reg_RdFL(iris_046);
		CVD_Reg_Wr01(iris_046, reg_vslock_init_th, 0x0);
		CVD_Reg_WrFL(iris_046);

		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042, reg_vsync_lockout_cnt, 0x50);
		CVD_Reg_Wr01(iris_042, reg_vsync_cntl, 0x1);
		CVD_Reg_WrFL(iris_042);

		/* done at color system setting */
		/*
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_hsync_mid, 0x1);
		CVD_Reg_WrFL(iris_076);
		*/

	}
	else if (system == 1)	// 480i system
	{
		CVD_Reg_RdFL(iris_047);
		CVD_Reg_Wr01(iris_047, reg_vslock_dly_ctrl, 0x1);
		CVD_Reg_Wr01(iris_047, reg_vslock_dly_cnt, 0x20);
		CVD_Reg_WrFL(iris_047);

		CVD_Reg_RdFL(iris_038);
		CVD_Reg_Wr01(iris_038, reg_vslock_ctrl, 0x9);
		CVD_Reg_Wr01(iris_038, reg_vslock_hscnt, 0x7);
		CVD_Reg_WrFL(iris_038);

		CVD_Reg_RdFL(iris_039);
		CVD_Reg_Wr01(iris_039, reg_vslock_onth, 0x10);
		CVD_Reg_Wr01(iris_039, reg_vslock_offth, 0x4);
		CVD_Reg_WrFL(iris_039);

		CVD_Reg_RdFL(iris_040);
		CVD_Reg_Wr01(iris_040, reg_vslock_vscnt_max, 0x20);
		CVD_Reg_Wr01(iris_040, reg_vslock_hscnt_margin, 0x20);
		CVD_Reg_WrFL(iris_040);

		CVD_Reg_RdFL(iris_037);
		CVD_Reg_Wr01(iris_037, reg_vslock_hscnt_th, 0x4);
		CVD_Reg_WrFL(iris_037);

		CVD_Reg_RdFL(iris_045);
		CVD_Reg_Wr01(iris_045, reg_vslock_hscnt_ictrl, 0x3);
		CVD_Reg_Wr01(iris_045, reg_vslock_hscnt_iir_alpha, 0x0);
		CVD_Reg_WrFL(iris_045);

		CVD_Reg_RdFL(iris_046);
		CVD_Reg_Wr01(iris_046, reg_vslock_init_th, 0x8);
		CVD_Reg_WrFL(iris_046);

		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042, reg_vsync_lockout_cnt, 0x4);
		CVD_Reg_Wr01(iris_042, reg_vsync_cntl, 0xa);
		CVD_Reg_WrFL(iris_042);

		/* done at color system setting */
		/*
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_hsync_mid, 0x1);
		CVD_Reg_WrFL(iris_076);
		*/

	}
	else
	{
		CVD_Reg_RdFL(iris_047);
		CVD_Reg_Wr01(iris_047, reg_vslock_dly_ctrl, 0x1);
		CVD_Reg_Wr01(iris_047, reg_vslock_dly_cnt, 0x20);
		CVD_Reg_WrFL(iris_047);

		CVD_Reg_RdFL(iris_038);
		CVD_Reg_Wr01(iris_038, reg_vslock_ctrl, 0x9);
		CVD_Reg_Wr01(iris_038, reg_vslock_hscnt, 0x39);
		CVD_Reg_WrFL(iris_038);

		CVD_Reg_RdFL(iris_039);
		CVD_Reg_Wr01(iris_039, reg_vslock_onth, 0x10);
		CVD_Reg_Wr01(iris_039, reg_vslock_offth, 0x4);
		CVD_Reg_WrFL(iris_039);

		CVD_Reg_RdFL(iris_040);
		CVD_Reg_Wr01(iris_040, reg_vslock_vscnt_max, 0x20);
		CVD_Reg_Wr01(iris_040, reg_vslock_hscnt_margin, 0x20);
		CVD_Reg_WrFL(iris_040);

		CVD_Reg_RdFL(iris_037);
		CVD_Reg_Wr01(iris_037, reg_vslock_hscnt_th, 0x4);
		CVD_Reg_WrFL(iris_037);

		CVD_Reg_RdFL(iris_045);
		CVD_Reg_Wr01(iris_045, reg_vslock_hscnt_ictrl, 0x3);
		CVD_Reg_Wr01(iris_045, reg_vslock_hscnt_iir_alpha, 0x0);
		CVD_Reg_WrFL(iris_045);

		CVD_Reg_RdFL(iris_046);
		CVD_Reg_Wr01(iris_046, reg_vslock_init_th, 0x8);
		CVD_Reg_WrFL(iris_046);

		CVD_Reg_RdFL(iris_042);
		CVD_Reg_Wr01(iris_042, reg_vsync_lockout_cnt, 0x4);
		CVD_Reg_Wr01(iris_042, reg_vsync_cntl, 0xa);
		CVD_Reg_WrFL(iris_042);

		/* done at color system setting */
		/*
		CVD_Reg_RdFL(iris_076);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_hsync_mid, 0x1);
		CVD_Reg_WrFL(iris_076);
		*/

	}
	return 0;
}

/**
 * @brief Hsync Enhancement for NTSC RF
 *
 * @param enable
 *
 * @return 
 */
int CVD_Hal_Set_Hsync_Enhance(int enable)
{
	int lpf_on;

	CVD_WA_DEBUG("%s entered :  %d \n",__func__, enable);

	if(enable == 2)		//PAL-M RF
	{
		//0xc0021774
		CVD_Reg_RdFL(iris_347);
		CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018000);
		CVD_Reg_WrFL(iris_347);
		//0xc0021798
		CVD_Reg_RdFL(iris_356);
		CVD_Reg_Wr01(iris_356, reg_hdetect_nr_ctrl4, 0x09861A80);
		CVD_Reg_WrFL(iris_356);
		//0xc0021778
		CVD_Reg_RdFL(iris_348);
		CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018000);
		CVD_Reg_WrFL(iris_348);
		//0xc002179c
		CVD_Reg_RdFL(iris_357);
		CVD_Reg_Wr01(iris_357, reg_hdetect_nr_ctrl5, 0x00001A80);
		CVD_Reg_WrFL(iris_357);
		//0xc002177c
		CVD_Reg_RdFL(iris_349);
		CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018040);
		CVD_Reg_WrFL(iris_349);
		//0xc00217A0
		CVD_Reg_RdFL(iris_358);
		CVD_Reg_Wr01(iris_358, reg_hdetect_nr_ctrl6, 0x00001A80);
		CVD_Reg_WrFL(iris_358);
		//0xc0021780
		CVD_Reg_RdFL(iris_350);
		//CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x2011A486);
		// taiwan stream (1904) hsync unstable 
		//CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x2021A486);
		// korean stream hsync unstable
		CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x20416206);		// for PAL-M RF : 120921_0442
		CVD_Reg_WrFL(iris_350);
		//0xc00217a4
		CVD_Reg_RdFL(iris_359);
		CVD_Reg_Wr01(iris_359, reg_hdetect_nr_ctrl7, 0x0020D450);
		CVD_Reg_WrFL(iris_359);
		//0xc0021330
		CVD_Reg_RdFL(iris_076);
		//CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, 0x1);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on | 0x01);
		CVD_Reg_WrFL(iris_076);
		//0xc0021284
		CVD_Reg_RdFL(iris_033);
		CVD_Reg_Wr01(iris_033, reg_phase_diff_noise_ctrl, 0x1);
		CVD_Reg_WrFL(iris_033);
	}
	else if(enable == 1)	// NTSC RF
	{
		//0xc0021774
		CVD_Reg_RdFL(iris_347);
		CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018000);
		CVD_Reg_WrFL(iris_347);
		//0xc0021798
		CVD_Reg_RdFL(iris_356);
		CVD_Reg_Wr01(iris_356, reg_hdetect_nr_ctrl4, 0x09861A80);
		CVD_Reg_WrFL(iris_356);
		//0xc0021778
		CVD_Reg_RdFL(iris_348);
		CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018000);
		CVD_Reg_WrFL(iris_348);
		//0xc002179c
		CVD_Reg_RdFL(iris_357);
		CVD_Reg_Wr01(iris_357, reg_hdetect_nr_ctrl5, 0x00001A80);
		CVD_Reg_WrFL(iris_357);
		//0xc002177c
		CVD_Reg_RdFL(iris_349);
		CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018040);
		CVD_Reg_WrFL(iris_349);
		//0xc00217A0
		CVD_Reg_RdFL(iris_358);
		CVD_Reg_Wr01(iris_358, reg_hdetect_nr_ctrl6, 0x00001A80);
		CVD_Reg_WrFL(iris_358);
		//0xc0021780
		CVD_Reg_RdFL(iris_350);
		//CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x2011A486);
		// taiwan stream (1904) hsync unstable 
		//CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x2021A486);
		// korean stream hsync unstable
		CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x20416806);
		CVD_Reg_WrFL(iris_350);
		//0xc00217a4
		CVD_Reg_RdFL(iris_359);
		CVD_Reg_Wr01(iris_359, reg_hdetect_nr_ctrl7, 0x0020D450);
		CVD_Reg_WrFL(iris_359);
		//0xc0021330
		CVD_Reg_RdFL(iris_076);
		//CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, 0x1);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on | 0x01);
		CVD_Reg_WrFL(iris_076);
		//0xc0021284
		CVD_Reg_RdFL(iris_033);
		CVD_Reg_Wr01(iris_033, reg_phase_diff_noise_ctrl, 0x1);
		CVD_Reg_WrFL(iris_033);
	}
	else if(enable == 3)	// PAL RF
	{
		//0xc0021774
		CVD_Reg_RdFL(iris_347);
		CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018000);
		CVD_Reg_WrFL(iris_347);
		//0xc0021798
		CVD_Reg_RdFL(iris_356);
		CVD_Reg_Wr01(iris_356, reg_hdetect_nr_ctrl4, 0x09861A80);
		CVD_Reg_WrFL(iris_356);
		//0xc0021778
		CVD_Reg_RdFL(iris_348);
		CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018000);
		CVD_Reg_WrFL(iris_348);
		//0xc002179c
		CVD_Reg_RdFL(iris_357);
		CVD_Reg_Wr01(iris_357, reg_hdetect_nr_ctrl5, 0x00001A80);
		CVD_Reg_WrFL(iris_357);
		//0xc002177c
		CVD_Reg_RdFL(iris_349);
		CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018040);
		CVD_Reg_WrFL(iris_349);
		//0xc00217A0
		CVD_Reg_RdFL(iris_358);
		CVD_Reg_Wr01(iris_358, reg_hdetect_nr_ctrl6, 0x00001A80);
		CVD_Reg_WrFL(iris_358);
		//0xc0021780
		CVD_Reg_RdFL(iris_350);
		// PT EU-05 hsync unstable : TVHWQ-74000
		CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x20416806);
		CVD_Reg_WrFL(iris_350);
		//0xc00217a4
		CVD_Reg_RdFL(iris_359);
		CVD_Reg_Wr01(iris_359, reg_hdetect_nr_ctrl7, 0x0020D450);
		CVD_Reg_WrFL(iris_359);
		//0xc0021330
		CVD_Reg_RdFL(iris_076);
		//CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, 0x1);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on | 0x01);
		CVD_Reg_WrFL(iris_076);
		//0xc0021284
		CVD_Reg_RdFL(iris_033);
		CVD_Reg_Wr01(iris_033, reg_phase_diff_noise_ctrl, 0x1);
		CVD_Reg_WrFL(iris_033);
	}
	else
	{
		//0xc0021774
		CVD_Reg_RdFL(iris_347);
		CVD_Reg_Wr01(iris_347, reg_hdetect_nr_ctrl0, 0x28018000);
		CVD_Reg_WrFL(iris_347);
		//0xc0021798
		CVD_Reg_RdFL(iris_356);
		CVD_Reg_Wr01(iris_356, reg_hdetect_nr_ctrl4, 0x09861a86);
		CVD_Reg_WrFL(iris_356);
		//0xc0021778
		CVD_Reg_RdFL(iris_348);
		CVD_Reg_Wr01(iris_348, reg_hdetect_nr_ctrl1, 0x28018000);
		CVD_Reg_WrFL(iris_348);
		//0xc002179c
		CVD_Reg_RdFL(iris_357);
		CVD_Reg_Wr01(iris_357, reg_hdetect_nr_ctrl5, 0x00001a86);
		CVD_Reg_WrFL(iris_357);
		//0xc002177c
		CVD_Reg_RdFL(iris_349);
		CVD_Reg_Wr01(iris_349, reg_hdetect_nr_ctrl2, 0x28018040);
		CVD_Reg_WrFL(iris_349);
		//0xc00217A0
		CVD_Reg_RdFL(iris_358);
		CVD_Reg_Wr01(iris_358, reg_hdetect_nr_ctrl6, 0x00001A86);
		CVD_Reg_WrFL(iris_358);
		//0xc0021780
		CVD_Reg_RdFL(iris_350);
		//CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x2011A484);
		// korean stream hsync unstable
		CVD_Reg_Wr01(iris_350, reg_hdetect_nr_ctrl3, 0x20416804);
		CVD_Reg_WrFL(iris_350);
		//0xc00217a4
		CVD_Reg_RdFL(iris_359);
		CVD_Reg_Wr01(iris_359, reg_hdetect_nr_ctrl7, 0x0020D450);
		CVD_Reg_WrFL(iris_359);
		//0xc0021330
		CVD_Reg_RdFL(iris_076);
		//CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, 0x1);
		CVD_Reg_Rd01(iris_076, reg_dcrestore_lpf_en, lpf_on);
		CVD_Reg_Wr01(iris_076, reg_dcrestore_lpf_en, lpf_on | 0x01);
		CVD_Reg_WrFL(iris_076);
		//0xc0021284
		CVD_Reg_RdFL(iris_033);
		CVD_Reg_Wr01(iris_033, reg_phase_diff_noise_ctrl, 0x1);
		CVD_Reg_WrFL(iris_033);
	}

	return 0;
}

int CVD_Hal_Get_Hstate_Max(void)
{

	int hstate_max_value;

	CVD_Reg_RdFL(iris_027);
	CVD_Reg_Rd01(iris_027,  reg_hstate_max, hstate_max_value);

	return hstate_max_value;
}

int CVD_Hal_Set_ycsep_Blend(int blend)
{
	int blend_value;
	blend &= 0xF;

	CVD_Reg_RdFL(iris_236);
	CVD_Reg_Rd01(iris_236,  reg_ycsep_blend_ctrl0, blend_value);

	blend_value = ( blend_value & 0xFFFFFFF0 ) | blend;

	CVD_Reg_Wr01(iris_236, reg_ycsep_blend_ctrl0, blend_value);
	CVD_Reg_WrFL(iris_236);

	return 0;
}

int CVD_Hal_Set_clampagc_updn(int updn_value)
{

	CVD_Reg_RdFL(iris_178);
	CVD_Reg_Wr01(iris_178, reg_clampagc_updn, updn_value);
	CVD_Reg_WrFL(iris_178);

	return 0;
}

int CVD_Hal_Get_status_clamp_updn(void)
{
	int status_updn;

	CVD_Reg_RdFL(iris_179);
	CVD_Reg_Rd01(iris_179,  reg_status_updn, status_updn);

	return status_updn;
}

int CVD_Hal_Set_dc_clamp_mode(int mode)
{
	CVD_Reg_RdFL(iris_015);
	// dc_clamp_mode : 0(auto), 1(backporch), 2(synctip), 3(off)
	CVD_Reg_Wr01(iris_015, reg_dc_clamp_mode, mode);
	CVD_Reg_WrFL(iris_015);

	return 0;
}

/**
 * @brief 0 = don't automatically use sync-tip DC-restore when input is noisy (default)
 		1 = automatically use sync-tip DC-restore when input is noisy
 *
 * @param value
 *
 * @return 
 */
int CVD_Hal_Set_Cpump_Auto_Stip_Value(int value)
{
	CVD_Reg_RdFL(iris_054);
	CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_noisy, value);
	CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_no_signal, value);
	CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_unlocked, value);
	CVD_Reg_WrFL(iris_054);

	return 0;
}

/**
 * @brief 0 = don't automatically use sync-tip DC-restore when input is noisy (default)
 		1 = automatically use sync-tip DC-restore when input is noisy
 *
 * @param value
 *
 * @return 
 */
int CVD_Hal_Set_Cpump_Auto_Stip_Noisy_Value(int value)
{
	CVD_Reg_RdFL(iris_054);
	CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_noisy, value);
	CVD_Reg_WrFL(iris_054);

	return 0;
}

int CVD_Hal_Set_Hue_Value(int value)
{
   //140819 : added reg_hue
	CVD_Reg_RdFL(iris_021);
	CVD_Reg_Wr01(iris_021, reg_hue, value);
	CVD_Reg_WrFL(iris_021);

	return 0;
}

int CVD_Hal_Get_Hue_Value(void)
{
	int value;
   //140819 : added reg_hue
	CVD_Reg_RdFL(iris_021);
	CVD_Reg_Rd01(iris_021, reg_hue, value);

	return value;
}

int CVD_Hal_Set_ColorBar_Params(int enable)
{
	//UINT32 tmp;
	static int	colorbar_params_enabled = -1;

	if( (colorbar_params_enabled == enable) || ( (colorbar_params_enabled == -1) && (enable == 0)) )
		return 0;
	else
		colorbar_params_enabled = enable;

	CVD_DEBUG("%s [%d] \n",__func__, enable);

#if 0
	if(enable)
	{
		//0xc8000a70[8] : 0=>1
		//0xc8000a70[0] : 0=>1
		CVD_Reg_RdFL(iris_220);
		CVD_Reg_Rd01(iris_220, reg_ycsep_3d_ctrl0, tmp);
		tmp = tmp | 0x101;
		CVD_Reg_Wr01(iris_220, reg_ycsep_3d_ctrl0, tmp);
		CVD_Reg_WrFL(iris_220);

		// 0xc8000a74[7:0] : 0x50
		CVD_Reg_RdFL(iris_221);
		CVD_Reg_Rd01(iris_221, reg_ycsep_3d_ctrl1, tmp);
		tmp = (tmp & 0xFFFFFF00) | 0x50;
		CVD_Reg_Wr01(iris_221, reg_ycsep_3d_ctrl1, tmp);
		CVD_Reg_WrFL(iris_221);

	}
	else
	{
		//0xc8000a70[8] : 0=>1
		//0xc8000a70[0] : 0=>1
		CVD_Reg_RdFL(iris_220);
		CVD_Reg_Rd01(iris_220, reg_ycsep_3d_ctrl0, tmp);
		tmp = tmp & 0xFFFFFEFE;
		CVD_Reg_Wr01(iris_220, reg_ycsep_3d_ctrl0, tmp);
		CVD_Reg_WrFL(iris_220);

		// 0xc8000a74[7:0] : 0x50
		CVD_Reg_RdFL(iris_221);
		CVD_Reg_Rd01(iris_221, reg_ycsep_3d_ctrl1, tmp);
		tmp = tmp & 0xFFFFFF00;
		CVD_Reg_Wr01(iris_221, reg_ycsep_3d_ctrl1, tmp);
		CVD_Reg_WrFL(iris_221);

	}
#endif

	return 0;
}

int CVD_Hal_Update_Status_Regs(CVD_STATUS_3CS_T	*pCVD_Status_3CS)
{

	/* Read Status CVD Registers */
	pCVD_Status_3CS->no_signal_flag = CVD_Hal_Get_No_Signal_Flag();
	pCVD_Status_3CS->h_lock_flag = CVD_Hal_Get_HLock_Flag();
	pCVD_Status_3CS->v_lock_flag = CVD_Hal_Get_VLock_Flag();
	// ORing hlock & vlock makes frequent state transition to NO_SIGNAL_STATE on noisy signal.
	pCVD_Status_3CS->vline_625_flag = CVD_Hal_Get_Vline_625_Flag();
	pCVD_Status_3CS->cvd_pal_flag = CVD_Hal_Get_PAL_Flag();
	pCVD_Status_3CS->cvd_secam_flag = CVD_Hal_Get_SECAM_Flag();//gogosing
	pCVD_Status_3CS->cvd_chromalock_flag = CVD_Hal_Get_Chromalock_Flag();
	pCVD_Status_3CS->status_noise = CVD_Hal_Get_Noise_Status();
	pCVD_Status_3CS->no_burst_flag = CVD_Hal_Get_NoBurst_Flag();
	pCVD_Status_3CS->cvd_fc_flag = CVD_Hal_Get_FC_Flag(LX_CVD_MAIN);
	pCVD_Status_3CS->cvd_cordic_freq = CVD_Hal_Get_Cordic_Freq(LX_CVD_MAIN);
	pCVD_Status_3CS->cvd_cordic_freq += CVD_Hal_Get_Cordic_Freq(LX_CVD_MAIN);
	pCVD_Status_3CS->cvd_cordic_freq += CVD_Hal_Get_Cordic_Freq(LX_CVD_MAIN);
	pCVD_Status_3CS->cvd_cordic_freq += CVD_Hal_Get_Cordic_Freq(LX_CVD_MAIN);
	pCVD_Status_3CS->cvd_cordic_freq = (pCVD_Status_3CS->cvd_cordic_freq>>2);
	//pCVD_Status_3CS->cvd_cordic_freq += CVD_Get_Cordic_Freq(LX_CVD_MAIN);
	//pCVD_Status_3CS->cvd_cordic_freq = pCVD_Status_3CS->cvd_cordic_freq /5;
	pCVD_Status_3CS->status_agc_gain = CVD_Hal_Get_Status_AGC_Gain();
	pCVD_Status_3CS->hnon_standard_flag = CVD_Hal_Get_HNon_Standard_Flag();
	pCVD_Status_3CS->vnon_standard_flag = CVD_Hal_Get_VNon_Standard_Flag();
	/*
	   if(pCVD_Status_3CS->in_atv_tunning == FALSE)
	   CVD_AGC_Bypass_Function((UINT32)pCVD_Status_3CS->status_noise, (UINT32)pCVD_Status_3CS->h_lock_flag, (UINT32)pCVD_Status_3CS->no_signal_flag );
	 */
	pCVD_Status_3CS->vline_625_reg = CVD_Hal_Get_Vline_625_Reg();

	pCVD_Status_3CS->cs0_pal_flag = CVD_Hal_Get_PAL_Flag_CS0();
	pCVD_Status_3CS->cs0_secam_flag = CVD_Hal_Get_SECAM_Flag_CS0();//gogosing
	pCVD_Status_3CS->cs0_chromalock_flag = CVD_Hal_Get_Chromalock_Flag_CS0();
	pCVD_Status_3CS->cs0_fc_flag = CVD_Hal_Get_FC_Flag_CS0();
	pCVD_Status_3CS->cs0_cordic_freq = CVD_Hal_Get_Cordic_Freq_CS0();
	pCVD_Status_3CS->cs0_cordic_freq += CVD_Hal_Get_Cordic_Freq_CS0();
	pCVD_Status_3CS->cs0_cordic_freq += CVD_Hal_Get_Cordic_Freq_CS0();
	pCVD_Status_3CS->cs0_cordic_freq += CVD_Hal_Get_Cordic_Freq_CS0();
	pCVD_Status_3CS->cs0_cordic_freq += CVD_Hal_Get_Cordic_Freq_CS0();
	pCVD_Status_3CS->cs0_cordic_freq = pCVD_Status_3CS->cs0_cordic_freq /5;

	pCVD_Status_3CS->cs1_pal_flag = CVD_Hal_Get_PAL_Flag_CS1();
	pCVD_Status_3CS->cs1_secam_flag = CVD_Hal_Get_SECAM_Flag_CS1();//gogosing
	pCVD_Status_3CS->cs1_chromalock_flag = CVD_Hal_Get_Chromalock_Flag_CS1();
	pCVD_Status_3CS->cs1_fc_flag = CVD_Hal_Get_FC_Flag_CS1();
	pCVD_Status_3CS->cs1_cordic_freq = CVD_Hal_Get_Cordic_Freq_CS1();
	pCVD_Status_3CS->cs1_cordic_freq += CVD_Hal_Get_Cordic_Freq_CS1();
	pCVD_Status_3CS->cs1_cordic_freq += CVD_Hal_Get_Cordic_Freq_CS1();
	pCVD_Status_3CS->cs1_cordic_freq += CVD_Hal_Get_Cordic_Freq_CS1();
	//pCVD_Status_3CS->cs1_cordic_freq += CVD_Hal_Get_Cordic_Freq_CS1();
	pCVD_Status_3CS->cs1_cordic_freq = (pCVD_Status_3CS->cs1_cordic_freq>>2);
	//pCVD_Status_3CS->cs1_cordic_freq = pCVD_Status_3CS->cs1_cordic_freq /5;
	pCVD_Status_3CS->cvd_burst_mag = CVD_Hal_Get_CVD_Burst_Mag_Value();

	pCVD_Status_3CS->cs0_secam_flag &= CVD_Hal_Get_SECAM_Flag_CS0();//130204

	return 0;
}

int CVD_Hal_Get_Reg_States_Detail(LX_AFE_CVD_STATES_DETAIL_T	*pcvd_states_detail_t)
{
	/* Read Status Registers */
	pcvd_states_detail_t->No_Signal_Flag = CVD_Hal_Get_No_Signal_Flag();
	pcvd_states_detail_t->HLock_Flag = CVD_Hal_Get_HLock_Flag();
	pcvd_states_detail_t->VLock_Flag = CVD_Hal_Get_VLock_Flag();
	pcvd_states_detail_t->VLine_625_Flag = CVD_Hal_Get_Vline_625_Flag();
	pcvd_states_detail_t->Pal_Flag = CVD_Hal_Get_PAL_Flag();
	pcvd_states_detail_t->Secam_Flag = CVD_Hal_Get_SECAM_Flag();
	pcvd_states_detail_t->Chromalock_Flag = CVD_Hal_Get_Chromalock_Flag();
	pcvd_states_detail_t->NoBurst_Flag = CVD_Hal_Get_NoBurst_Flag();
	pcvd_states_detail_t->FC_Flag = CVD_Hal_Get_FC_Flag(LX_CVD_MAIN);
	pcvd_states_detail_t->cvd_cordic_freq = CVD_Hal_Get_Cordic_Freq(LX_CVD_MAIN);
	pcvd_states_detail_t->status_noise = CVD_Hal_Get_Noise_Status();

	pcvd_states_detail_t->Pal_Flag_CS0 = CVD_Hal_Get_PAL_Flag_CS0();
	pcvd_states_detail_t->Secam_Flag_CS0 = CVD_Hal_Get_SECAM_Flag_CS0();
	pcvd_states_detail_t->Chromalock_Flag_CS0 = CVD_Hal_Get_Chromalock_Flag_CS0();
	pcvd_states_detail_t->FC_Flag_CS0 = CVD_Hal_Get_FC_Flag_CS0();
	pcvd_states_detail_t->cvd_cordic_freq_CS0 = CVD_Hal_Get_Cordic_Freq_CS0();

	pcvd_states_detail_t->Pal_Flag_CS1 = CVD_Hal_Get_PAL_Flag_CS1();
	pcvd_states_detail_t->Secam_Flag_CS1 = CVD_Hal_Get_SECAM_Flag_CS1();
	pcvd_states_detail_t->Chromalock_Flag_CS1 = CVD_Hal_Get_Chromalock_Flag_CS1();
	pcvd_states_detail_t->FC_Flag_CS1 = CVD_Hal_Get_FC_Flag_CS1();
	pcvd_states_detail_t->cvd_cordic_freq_CS1 = CVD_Hal_Get_Cordic_Freq_CS1();
	CVD_Get_PE0_Motion_Value(&pcvd_states_detail_t->tnr_x, &pcvd_states_detail_t->tnr_s, &pcvd_states_detail_t->s_status );
	pcvd_states_detail_t->motion_value = CVD_Hal_Get_Global_Motion_Value();
	pcvd_states_detail_t->agc_gain = CVD_Hal_Get_Status_AGC_Gain();
	pcvd_states_detail_t->cagc = CVD_Hal_Get_CAGC_Value();
	//pcvd_states_detail_t->saturation = CVD_E60Ax_Get_Saturation_Value();
	pcvd_states_detail_t->saturation = CVD_Hal_Get_oadj_c_coeff_value();
	pcvd_states_detail_t->hnon_standard = CVD_Hal_Get_HNon_Standard_Flag();
	pcvd_states_detail_t->vnon_standard = CVD_Hal_Get_VNon_Standard_Flag();
	pcvd_states_detail_t->burst_mag = CVD_Hal_Get_CVD_Burst_Mag_Value();
	pcvd_states_detail_t->vdetect_vcount = CVD_Hal_Get_Vdetect_Vcount_Value();
	pcvd_states_detail_t->agc_peak_en = CVD_Hal_Get_AGC_Peak_En_Value();
	pcvd_states_detail_t->agc_bypass = CVD_Hal_Get_AGC_Bypass_Value();
	pcvd_states_detail_t->no_color_detected = g_CVD_Status_3CS.no_color_detected;
	pcvd_states_detail_t->analog_demod_type = g_CVD_Status_3CS.use_internal_demod;
	pcvd_states_detail_t->status_clamp_updn = CVD_Hal_Get_status_clamp_updn();
	pcvd_states_detail_t->buf_ycm = (UINT8)0U;
	pcvd_states_detail_t->buf_sel1 = (UINT8)0U;
	pcvd_states_detail_t->buf_pdb1 = (UINT8)0U;
	pcvd_states_detail_t->vdac_pdb = (UINT8)0U;

//	CVD_E60Ax_ColorBar_Detector(&pcvd_states_detail_t->colorbar_diff, &pcvd_states_detail_t->colorbar_75_100);

	CVD_Get_AFE_CVBS_status(&pcvd_states_detail_t->cvbs_icon, &pcvd_states_detail_t->cvbs_pdb, &pcvd_states_detail_t->cvbs_cp, &pcvd_states_detail_t->cvbs_insel, &pcvd_states_detail_t->cvbs_pdbm);

	return 0;
}

int CVD_Hal_Get_HDTO_difference(void)
{
	int diff_value;
	UINT32 status_hdto_inc, reg_hdto_inc;

	CVD_Reg_RdFL(iris_005);
	CVD_Reg_Rd01(iris_005, reg_status_hdto_inc, status_hdto_inc);

	CVD_Reg_RdFL(iris_030);
	CVD_Reg_Rd01(iris_030, reg_hdto_inc, reg_hdto_inc);

	diff_value = (int)(status_hdto_inc & 0x3FFFFFFF) - (int)(reg_hdto_inc & 0x3FFFFFFF);

	CVD_DEBUG("%s status_hdto_inc[0x%x], reg_hdto_inc[0x%x], diff[%d]\n", __func__, status_hdto_inc, reg_hdto_inc, diff_value);

	return abs(diff_value);
}

int CVD_Hal_Set_force_vcr(int value)
{
	CVD_Reg_RdFL(iris_018);
	CVD_Reg_Wr01(iris_018, reg_force_vcr, value);
	CVD_Reg_WrFL(iris_018);

	if(value)
		CVD_DEBUG("%s [%d]\n", __func__, value);

	return 0;
}

int CVD_Hal_Set_vcr_auto_switch_en(int value)
{
	CVD_Reg_RdFL(iris_067);
	CVD_Reg_Wr01(iris_067, reg_vcr_auto_switch_en, value);
	CVD_Reg_WrFL(iris_067);

	CVD_DEBUG("%s [%d]\n", __func__, value);

	return 0;
}

int CVD_Hal_Set_Burst_Gate_12(int burst1_start, int burst1_end, int burst2_start, int burst2_end)
{

	CVD_Reg_RdFL(iris_374);
	CVD_Reg_Wr04(iris_374, reg_burst_gate1_start, burst1_start, reg_burst_gate1_end, burst1_end, reg_burst_gate2_start, burst2_start, reg_burst_gate2_end, burst2_end);
	CVD_Reg_WrFL(iris_374);

	return 0;
}

int CVD_Hal_Get_Burst_Mag_12(int *pBurst1_mag, int *pBurst2_mag)
{
	CVD_Reg_RdFL(iris_375);
	CVD_Reg_Rd02(iris_375, reg_status_burst1_mag, *pBurst1_mag, reg_status_burst2_mag, *pBurst2_mag);
	return 0;
}

int CVD_Hal_Cordic_Gate_Control(UINT32 gate_start, UINT32 gate_end)
{
	CVD_DEBUG("CVD Cordic Gate Control : Start[0x%x], End[0x%x]\n", gate_start, gate_end);

	CVD_Reg_RdFL(iris_094);
	CVD_Reg_Wr02(iris_094, reg_cordic_gate_end, gate_end, reg_cordic_gate_start, gate_start);
	CVD_Reg_WrFL(iris_094);

	return 0;
}

int CVD_Hal_Set_Clockgating(int value)
{
	int read_value;

	CVD_Reg_RdFL(iris_063);
	CVD_Reg_Wr01(iris_063, reg_cg_off, value);	// CVD clock gating on (default 0x18)
	CVD_Reg_WrFL(iris_063);

	OS_MsecSleep(10);

	CVD_Reg_RdFL(iris_063);
	CVD_Reg_Rd01(iris_063, reg_cg_off, read_value);
	AFE_PRINT("cg off read value [0x%x]\n", read_value);

	OS_MsecSleep(10);
	CVD_Reg_RdFL(iris_012);
	CVD_Reg_Wr01(iris_012, reg_cvd_soft_reset, 0);
	CVD_Reg_WrFL(iris_012);

//	CVD_Reg_RdFL(iris_063);
//	CVD_Reg_Wr01(iris_063, reg_cg_off, 0x18);	// CVD clock gating on (default 0x18)
//	CVD_Reg_WrFL(iris_063);

	OS_MsecSleep(10);
//	CVD_Reg_RdFL(iris_012);
//	CVD_Reg_Wr01(iris_012, reg_cvd_soft_reset, 1);
//	CVD_Reg_WrFL(iris_012);

	OS_MsecSleep(10);

	return 0;
}
