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

#ifndef	_CVD_HW_O26A0_H_
#define	_CVD_HW_O26A0_H_

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
int CVD_O26Ax_Clamp_Current_Control(UINT8 value);
void CVD_O26Ax_Power_Down(LX_AFE_CVD_SELECT_T select_main_sub, BOOLEAN PowerOnOFF);
void CVD_O26Ax_Reg_Init(LX_AFE_CVD_SELECT_T select_main_sub);
int CVD_O26Ax_Set_Source_Type(LX_AFE_CVD_SET_INPUT_T	cvd_input_info);
int CVD_O26Ax_Channel_Power_Control(UINT32 on_off); 
int CVD_O26Ax_Bypass_Control(LX_AFE_CVD_BYPASS_CONTROL_T *cvd_bypass_control_t);
int CVD_O26Ax_OnOff_VDAC(BOOLEAN bonoff);
int CVD_O26Ax_Get_PE0_Motion_Value(int *p_tnr_x_avg_t, int *p_tnr_x_avg_s, int *p_tpd_s_status);
int CVD_O26Ax_VDAC_mute_control(int enable);
int CVD_O26Ax_Get_AFE_CVBS_status(UINT8 *cvbs_icon_value, UINT8 *cvbs_pdb_value, UINT8 *cvbs_cp_value, UINT8 *cvbs_insel_value, UINT8 *cvbs_pdbm_value);
int CVD_O26Ax_Set_Internal_Demod_Mode(BOOLEAN bInternal_Demod);
int CVD_O26Ax_OnOff_DMD_DAC(BOOLEAN bonoff);
int CVD_O26Ax_SetPqModeToDdr(volatile UINT32 *p_ddr_reg);
int CVD_O26Ax_Set_PQ_Mode(LX_AFE_CVD_PQ_MODE_T cvd_pq_mode);
int CVD_O26Ax_Black_Level_Control(LX_AFE_CVD_BLACK_LEVEL_T black_level, LX_AFE_CVD_SOURCE_ATTRIBUTE_T rf_av_mode);
int CVD_O26Ax_Set_Buffer_Base_Addr(phys_addr_t cvd_paddr);
int CVD_O26Ax_Get_Scart_FB_En(void);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

