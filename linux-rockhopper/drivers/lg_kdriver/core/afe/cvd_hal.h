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
 *  @author     wonsik.do
 *  @version    1.0
 *  @date       2012-05-04
 *  @note       Additional information.
 */

#ifndef	_CVD_HAL_H_
#define	_CVD_HAL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#include "cvd_module.h"
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
#define M16_CVD_INIT_OADJ_C 	// 2012.02.24 won.hur

#undef	M16P_STABLE_HSYNC_WORKAROUND			//not used
#define	M16P_HSYNC_ENHANCEMENT			//not used
#define	M16P_VSYNC_ENHANCEMENT			//not used

#define L9_DONT_KILL_CHROMALOCK_ON_CLOCK_LOST			//not used

#define M16P_NTSC_NOISY_STABLE_VSYNC_WORKAROUND
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int CVD_Hal_ClampAGC_OnOff(UINT8 on_off);
void CVD_Hal_Program_Color_System_Main_Multi(CVD_SET_SYSTEM_3CS_T *pSet_system_t);
void CVD_Hal_Program_Color_System_CS(CVD_SELECT_CDETECT_T cs_sel, CVD_SET_SYSTEM_3CS_T *pSet_system_t);
void CVD_Hal_Program_Color_System_PreJob(CVD_SET_SYSTEM_3CS_T *pSet_system_t);
void CVD_Hal_Program_Color_System_PreJob2(void);
void CVD_Hal_Program_Color_System_PostJob(CVD_SET_SYSTEM_3CS_T *pSet_system_t);
void CVD_Hal_Program_Color_System_PostJob2(void);
int CVD_Hal_Set_Scart_Overlay(BOOLEAN arg);
int CVD_Hal_Set_Scart_FB_En(int fb_en_ctrl);
UINT8 CVD_Hal_Get_FC_Flag(LX_AFE_CVD_SELECT_T select_main_sub);
UINT8 CVD_Hal_Get_CVD_Burst_Mag_Flag(CVD_STATE_T	color_system);
int CVD_Hal_Set_CVD_CAGC(UINT8 state,CVD_SET_SYSTEM_3CS_T *pSet_system_t, CVD_STATE_T	color_system);
UINT8 CVD_Hal_Get_Cordic_Freq(LX_AFE_CVD_SELECT_T select_main_sub);
UINT8 CVD_Hal_Get_Cordic_Freq_CS0(void);
UINT8 CVD_Hal_Get_FC_Flag_CS0(void);
UINT8 CVD_Hal_Get_Cordic_Freq_CS1(void);
UINT8 CVD_Hal_Get_FC_Flag_CS1(void);
int CVD_Hal_Get_FB_Status(LX_AFE_SCART_MODE_T *pScart_fb_mode);
int CVD_Hal_Get_Scart_AR(LX_AFE_SCART_AR_INFO_T	*pScart_ar_param);
void CVD_Hal_Print_Vport_Version(void);
int CVD_Hal_Get_No_Signal_Flag(void);
int CVD_Hal_Get_HLock_Flag(void);
int CVD_Hal_Get_VLock_Flag(void);
int CVD_Hal_Get_Vline_625_Flag(void);
int CVD_Hal_Get_Vdetect_Vcount_625_Flag(void);
int CVD_Hal_Get_PAL_Flag(void);
int CVD_Hal_Get_SECAM_Flag(void);
int CVD_Hal_Get_Chromalock_Flag(void);
int CVD_Hal_Get_PAL_Flag_CS0(void);
int CVD_Hal_Get_SECAM_Flag_CS0(void);
int CVD_Hal_Get_Chromalock_Flag_CS0(void);
int CVD_Hal_Get_PAL_Flag_CS1(void);
int CVD_Hal_Get_SECAM_Flag_CS1(void);
int CVD_Hal_Get_Chromalock_Flag_CS1(void);
int CVD_Hal_Get_Noise_Status(void);
int CVD_Hal_Get_NoBurst_Flag(void);
int CVD_Hal_Reset_vdct(int enable);
int CVD_Hal_Reset_hdct(int enable);
int CVD_Hal_Reset_cdct(int enable);
int CVD_Hal_Reset_Clampagc(void);
int CVD_Hal_Get_Vline_625_Reg(void);
int CVD_Hal_Set_PE_Params(CVD_REG_PARAM_T	*pCVD_PE_Param_t, UINT32 size, LX_AFE_CVD_PQ_MODE_T cvd_pq_mode);
int CVD_Hal_swrst_CS(CVD_SELECT_CDETECT_T cs_sel);
int CVD_Hal_Set_Hstate_Max(UINT32	hstate_max_value);
int CVD_Hal_Set_Hstate_Fixed(UINT32	value);
int CVD_Hal_AGC_Bypass(int Bypass_Enable);
int CVD_Hal_Set_dcrestore_accum_width(int value);
int CVD_Hal_Set_SCART_CSC(int black_level);
int CVD_Hal_Set_comb2d_only(int value);
int CVD_Hal_Set_Noise_Threshold(int value);
int CVD_Hal_Set_AGC_Peak_Nominal(UINT8	value);	// 7bit value
int CVD_Hal_Get_AGC_Peak_Nominal(void);
int CVD_Hal_Set_Contrast_Brightness(int contrast, int brightness);
int CVD_Hal_Set_Dcrestore_Gain(int value);
//set reg_agc_bypass & reg_dcrestore_gain to default value
void CVD_Hal_Set_for_Normal_Signal(void);
//set AGC to Bypass, and set DCrestore gain to 1/8 on weak RF signal ( status nois is max value 0x3FF);
void CVD_Hal_Set_for_Noisy_Signal(void);
int CVD_Hal_Get_Status_AGC_Gain(void);
int CVD_Hal_Set_AGC_Peak_En(int enable);
int CVD_Hal_Get_HNon_Standard_Flag(void);
int CVD_Hal_Get_VNon_Standard_Flag(void);
int CVD_Hal_Set_Noburst_Ckill(unsigned int value);
int CVD_Hal_Get_Global_Motion_Value(void);
/* This Function is workaround code for JOJO Gunpo stream (vsync unstable);*/
int CVD_Hal_Set_for_Stable_Vsync(UINT32	Enable);
/* This Function is used for workaround code as to fix dong-go-dong-rak */
int CVD_Hal_Set_for_Field_Detect_Mode(UINT32 mode);
/* This function is used for workaround code for brasil color instable issue */
int CVD_Hal_Set_for_Burst_Gate_End_On_Noisy(UINT8 original_value, UINT32 Enable);
/* This function is used for workaround code for brasil color instable issue */
UINT32 CVD_Hal_Differential_Status_Cdto_Inc_Value(void);
UINT32 CVD_Hal_Read_Cordic_Freq_Value(void);
int	CVD_Hal_Read_VCR_Detected(void);
int CVD_Hal_Get_CVD_Burst_Mag_Value(void);
int CVD_Hal_Set_CVD_Saturation_Value(int value);
int CVD_Hal_Get_CAGC_Value(void);
int CVD_Hal_Get_Saturation_Value(void);
int CVD_Hal_Get_AGC_Bypass_Value(void);
int CVD_Hal_Get_AGC_Peak_En_Value(void);
int CVD_Hal_Get_Vdetect_Vcount_Value(void);
int CVD_Hal_Get_oadj_c_coeff_value(void);
int CVD_Hal_OnOff_Chromalock_Ckill(BOOLEAN bonoff);
int CVD_Hal_Reset_mif(int enable);
int CVD_Hal_Set_HNon_Standard_Threshold(int value);
int CVD_Hal_Force_Color_Kill(UINT8 color_kill_enable);
int CVD_Hal_Get_Crunky_Status(LX_AFE_CVD_CK_T *pCK_Detection_t);
int CVD_Hal_Fast_Vline_625_Using_Vdetec_Vcount(void);
int CVD_Hal_Burst_Gate_Control(UINT32	gate_start, UINT32 gate_end);
int CVD_Hal_Read_Buffer_Status(UINT32 *rbuf1_empty, UINT32 *rbuf2_empty, UINT32 *rbuf3_empty, UINT32 *rbuf4_empty, UINT32 *wbuf_empty, UINT32 *wbuf_ful);
void CVD_Hal_Program_Color_System_buffer_only(CVD_SET_SYSTEM_3CS_T *pSet_system_t);
int CVD_Hal_vf_nstd_control(unsigned int value);
int CVD_Hal_Set_CAGC_Value(UINT32 cagc_value);
int CVD_Hal_Enable_Stable_Sync_Mode(int enable);
int CVD_Hal_Get_ColorBar_Level(UINT8 *Composite_Level);
int CVD_Hal_chromalock_level_control(unsigned int value);
int CVD_Hal_Set_SCART_Filter(void);
int CVD_Hal_agc_half_en_control(int enable);//gogosing
int CVD_Hal_Hstart_Position_Compensator(CVD_SET_SYSTEM_3CS_T *pSet_system_t);
int CVD_Hal_Set_Motion_Expand(int enable);
int CVD_Hal_Set_CCR(int ccr_value);
int CVD_Hal_Check_CVD_Memory(void);
int CVD_Hal_Set_PALm_Stable_HSync_Mode(int enable);
int CVD_Hal_Set_PALm_Stable_VSync_Mode(int enable);
int CVD_Hal_Set_comb2d_only_md(int value);
int CVD_Hal_Get_comb2d_only(void);
int CVD_Hal_Get_comb2d_only_md(void);
int CVD_Hal_3DComb_Workaround(int step);
void CVD_Hal_Program_Color_System_Size(CVD_SET_SYSTEM_3CS_T *pSet_system_t);
void CVD_Hal_Program_Color_System_Size_md(CVD_SET_SYSTEM_3CS_T *pSet_system_t);
int CVD_Hal_Set_Vsync_Cntl(CVD_SET_SYSTEM_3CS_T *pSet_system_t, int enable);
int CVD_Hal_CVD_Soft_Reset(void);
int CVD_Hal_Set_Blue_Mode(int blue);
int CVD_Hal_Set_OADJ(CVD_REG_PARAM_T	*pCVD_Black_Level_Param_t, UINT32 size);
int CVD_Hal_Init_Level_Detector(CVD_STATE_T color_system);
int CVD_Hal_Get_AFE_CVBS_status(UINT8 *cvbs_icon_value, UINT8 *cvbs_pdb_value, UINT8 *cvbs_cp_value, UINT8 *cvbs_insel_value, UINT8 *cvbs_pdbm_value);
int CVD_Hal_Set_Vactive_Params(int vline_625_stable);
int CVD_Hal_Set_Nosignal_Vactive_Params(void);
int CVD_Hal_Set_Cpump_Auto_Stip_Mode(int mode);
int CVD_Hal_Set_Blend_Ratio(int value);

int CVD_Hal_Set_PE_Param_Flag(int signal_lock, int color_system, int rf_av_mode, int write_done);
int CVD_Hal_Set_Hsync_Enhance(int enable);
int CVD_Hal_Set_Vsync_Enhance(int system);
int CVD_Hal_Get_Hstate_Max(void);
int CVD_Hal_Set_ycsep_Blend(int blend);
int CVD_Hal_Set_clampagc_updn(int updn_value);
int CVD_Hal_Get_status_clamp_updn(void);
int CVD_Hal_Set_dc_clamp_mode(int mode);
int CVD_Hal_Set_Cpump_Auto_Stip_Value(int value);
int CVD_Hal_Set_Cpump_Auto_Stip_Noisy_Value(int value);
int CVD_Hal_Set_ColorBar_Params(int enable);
int CVD_Hal_Set_Hue_Value(int value);
int CVD_Hal_Get_Hue_Value(void);
int CVD_Hal_Enable_LPF_en(int enable);
int CVD_Hal_Update_Status_Regs(CVD_STATUS_3CS_T	*pCVD_Status_3CS);
int CVD_Hal_Get_Reg_States_Detail(LX_AFE_CVD_STATES_DETAIL_T	*pcvd_states_detail_t);
int CVD_Hal_Get_HDTO_difference(void);
int CVD_Hal_Set_force_vcr(int value);
int CVD_Hal_Set_vcr_auto_switch_en(int value);
int CVD_Hal_Set_Burst_Gate_12(int burst1_start, int burst1_end, int burst2_start, int burst2_end);
int CVD_Hal_Get_Burst_Mag_12(int *pBurst1_mag, int *pBurst2_mag);
int CVD_Hal_Cordic_Gate_Control(UINT32 gate_start, UINT32 gate_end);
int CVD_Hal_Set_Clockgating(int value);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

