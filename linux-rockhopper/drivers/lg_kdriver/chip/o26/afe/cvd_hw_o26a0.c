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
#if defined(INCLUDE_KDRV_PE) && defined(INCLUDE_O26_PE_REG)
#include "pe_hal.h"
#include "../pe/reg/pe_ddr_reg_o26.h"
#endif

#include "cvd_module.h"
#include "cvd_hw_o26a0.h"
#include "de_cvd_reg.h"
#include "cvd_hal.h"

#include "cvd_pe_o26a0/CVD_L_AV_NTSC_443_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_AV_NTSC_M_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_AV_PAL60_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_AV_PALI_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_AV_PALM_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_AV_PALNc_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_AV_SECAM_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_RF_NTSC_M_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_RF_PALI_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_RF_PALM_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_RF_PALNc_default_o26.h"
#include "cvd_pe_o26a0/CVD_L_RF_SECAM_default_o26.h"

#include "cvd_pe_o26a0/CVD_L_RF_NTSC_M_Black_Level_High.h"
#include "cvd_pe_o26a0/CVD_L_RF_NTSC_M_Black_Level_Low.h"
#include "cvd_pe_o26a0/CVD_L_AV_NTSC_M_Black_Level_High.h"
#include "cvd_pe_o26a0/CVD_L_AV_NTSC_M_Black_Level_Low.h"
/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/

//#define L9_SLOW_AGC_WORKAROUND
//#define L9_USE_SYNCTIP_ONLY_MODE

//moved to cvd_hal.h
//#define M16_CVD_INIT_OADJ_C 	// 2012.02.24 won.hur

//#define CVD_REG_SATURATION_ADJUST
#define M16_IRIS_CLAMPAGC_V2_CONTROL_WA_FOR_CVD_UNLOCK

#undef M16_CVBSAFE_BUG_WOKAROUND
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
//extern LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	g_CVD_Color_System_Support ;
extern CVD_STATUS_3CS_T	g_CVD_Status_3CS ;

#ifdef INCLUDE_KDRV_VBI
extern int gEnableTTXTestPatch;
extern int gStatusTTXTestPatch;
#endif
extern BOOLEAN gCVD_2d_mode;
extern BOOLEAN g_CVD_USE_TE_SHARED_POOL;
/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/
UINT32 g_O26_CVD_HW_DRV_REV = 0x25042000;

CVD_COLOR_SYSTEM_ARRAY_3CS_T g_SetColorSystem_3CS_O26A0 =
{ 
	{
		// new L9Bx 3DComb Buffer Value 						cvd1_clampagc_on    colour_mode    ped  	   cagc_en	 dc_clamp			adaptive_mode	hagc  					cdto_inc	hdtc_inc  	vactive_start		cagc   	cagc_av    	 	 lose_chromalock  	comb2d_only		  			hactive_md_s/w	hstate_max		hactive_start_54M	  vsync_signal_thr			cs/cs1_chroma_burst5or10	cordic_gate_s/e_3CS							fb_hstart								burst_gate_s/e				  contrast_av  			cs_issecam_th					rf_hrs				dcrestore_hsync_mid
		//																phase_offset	 vline_625		adc_blank_level		  hagc_field 		 adaptive_3d	  yc_delay											vactive_height	  		  secam_ybw			motion_mode		 fb_sync									 dcrestore_accum_width		hnon_std_thr	fixed_cstate				hrs_ha_start					burst_gate_s/e_3CS					cagc_gate_s/e									dcrestore_hsync_mid		  saturation		buffer_size_md
		//																	  ispal_th		  hpixel				agc_half_en		chroma_bw_lo		pal60			cagc_gate_s/e									  ntsc443					auto_secam_level adaptive_chroma	vactive_md_s/h										  hactive_width_54M				 	cstate						hrs_ha_width							fb_vstart_o/e						cordic_gate_s/e							contrast	fb_height_half						rd_pel_md			//hue
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// default																																																																																																																																			//default
		{955500, 	716625, 	477750, 	238875, 	0x0, 	0x0, 	0x20, 0x1f, 0x0, 0x0, 0x0, 0x1, 0x3c0, 0x1, 0x1, 0x0, 0x0, 	0x0, 	0x0, 0x1, 	0, 	0xDD, 0x0, 	0x32, 0x50, 0x21F07C1F, 0x20000000, 0x23,	0x61, 0x0, 	0x8A,	0x8a, 0x0, 	0x0, 0x3, 	0x0, 0x0, 	0x0, 0x0, 	0x23, 0x61, 	0x6E, 0x50, 	0x3, 0x1b, 		0x84, 0x50,		0x06, 0x0, 		0x0,	0x5, 	0x0, 0x0,	0x82,	0x50,	0x3c, 0x6e,		0x32, 0x46,		0x13, 0x14,	0x82,	0x32, 0x50, 	0x3c, 0x6e, 	0x32, 0x46,		0xFE,	0x80, 0x80, 0x60, 0x80,		0x08,	0x074a34,	0x03a6e3,	0x82	,0x0	,	0xFE},
	//NTSC-M																							   			   	   	   		 				 	   	   	   	 									                        // 1113                                                                                                                                                                                                                                 /* afn red face : gate s/e shifted(0x36,0x49) and hue modified */                                                                            			  	         	//NTSC M                
		{0xE946A, 	0xAF83B, 	0x74DC5, 	0x3AE05, 	0x38F, 	0x1, 	0x80, 0x18, 0x0, 0x0, 0x0, 0x0, 0x3c0, 0x1, 0x0, 0x0, 0x0, 	0x0, 	0x0, 0x1, 	0, 	0xDD, 0x0, 	0x32, 0x50, 0x21F07C1F, 0x20000000, 0x27,	0x61, 0x0, 	0x8a,	0x8a, 0x0, 	0x0, 0x3, 	0x0, 0x1, 	0x0, 0x0, 	0x27, 0x61, 	0x86, 0x50, 	0x3, 0x1b,		0x86, 0x50,		0x18, 0x10,		0x1,	0x7, 	0x0, 0x0,	0x61,	0x50,	0x32, 0x46,		0x32, 0x4b,		0x08, 0x09,	0x8c,	0x3D, 0x50, 	0x3D, 0x50, 	0x3D, 0x50,		0xF7,	0x82, 0x80, 0x60, 0x80,		0x08,	0x074a34,	0x03a6ee,	0x60	,0xE8	,	0xF7},
	//NTSC-J,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      			  	         	//NTSC J                                                
		{0xE946A, 	0xAE83B, 	0x74DC5, 	0x3AE05, 	0x71D, 	0x1, 	0x80, 0x18, 0x0, 0x0, 0x0, 0x0, 0x3c0, 0x1, 0x0, 0x0, 0x0, 	0x0, 	0x0, 0x1, 	0, 	0xCD, 0x0, 	0x32, 0x50, 0x21F07C1F, 0x20000000, 0x27,	0x61, 0x0, 	0x80,	0x80, 0x0, 	0x0, 0x3, 	0x0, 0x1, 	0x0, 0x0, 	0x27, 0x61, 	0x86, 0x50, 	0x3, 0x25,		0x86, 0x50,		0x18, 0x10,		0x1,	0x7, 	0x0, 0x0,	0x61,	0x50,	0x32, 0x46,		0x32, 0x46,		0x08, 0x09,	0x8c,	0x32, 0x45, 	0x32, 0x45, 	0x32, 0x45,		0xFE,	0x82, 0x80, 0x60, 0x80,		0x08,	0x074a34,	0x03a6ee,	0x60	,0x0	,	0xFE},
	//NTSC-443,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    			  	         	//NTSC 443                                              
		{1 , 		1 , 		1 , 		1 , 		1 , 	0x1, 	0x80, 0x18, 0x0, 0x0, 0x0, 0x0, 0x3c0, 0x1, 0x0, 0x0, 0x0, 	0x0, 	0x0, 0x0, 	0, 	0xDD, 0x0, 	0x32, 0x50, 0x2A098ACB, 0x20000000, 0x27,	0x61, 0x1, 	0x80,	0x8a, 0x0, 	0x0, 0x3, 	0x0, 0x1, 	0x1, 0x0, 	0x27, 0x61, 	0x7c, 0x50, 	0x3, 0x25,		0x7c, 0x50,		0x18, 0x10,		0x1,	0x7, 	0x0, 0x0,	0x4C,	0x50,	0x32, 0x46,		0x32, 0x46,		0x08, 0x09,	0x8c,	0x34, 0x42, 	0x34, 0x42, 	0x34, 0x42,		0xFE,	0x82, 0x80, 0x60, 0x80,		0x08,	1,			1   	,	0x4C	,0x0	,	0xFE},
	//PAL-I,B,G,H,D,                                                                                                                                                                                         	                                                                                                                                                                                                                                                                                                                     			  	         	//PAL i                                             
		{0x2B4C0A, 	0x207D79, 	0x15AA76,	0xAD773, 	0x470, 	0x1, 	0x80, 0x18, 0x1, 0x1, 0x1, 0x0, 0x3f0, 0x1, 0x0, 0x0, 0x0, 	0x0, 	0x2, 0x1, 	0, 	0xDC, 0x3, 	0x32, 0x50, 0x2A098ACB, 0x20000000, 0x2d,	0xC1, 0x0, 	0x80,	0x8a, 0x0, 	0x0, 0x3, 	0x0, 0x1, 	0x0, 0x0, 	0x2d, 0xC1, 	0x88, 0x50, 	0x3, 0x25,		0x88, 0x50,		0x18, 0x10, 	0x1,	0x7, 	0x0, 0x0,	0x5a,	0x50,	0x32, 0x5e,		0x32, 0x6E,		0x08, 0x08,	0x92,	0x34, 0x4a, 	0x34, 0x4a, 	0x34, 0x4a,		0xFE,	0x7B, 0x80, 0x6e, 0x80,		0x08,	0x0ad301,	0x56bc5 ,	0x5c	,0x0	,	0xFE},
	//PAL_N,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       			  	         	//PAL N                                                 
		{0x2B4C0A, 	0x207D79, 	0x15AA76,	0xAD773, 	0x470, 	0x1, 	0x80, 0x18, 0x1, 0x1, 0x1, 0x0, 0x3c0, 0x1, 0x0, 0x0, 0x0, 	0x0, 	0x2, 0x1, 	0, 	0xDD, 0x3, 	0x32, 0x50, 0x2A098ACB, 0x20000000, 0x2d,	0xC1, 0x0, 	0x80,	0x8a, 0x0, 	0x0, 0x3, 	0x0, 0x1, 	0x0, 0x0, 	0x2d, 0xC1, 	0x88, 0x50, 	0x3, 0x25,		0x88, 0x50,		0x18, 0x10, 	0x1,	0x7, 	0x0, 0x0,	0x5a,	0x50,	0x32, 0x6e,		0x32, 0x46,		0x08, 0x08,	0x92,	0x34, 0x4a, 	0x34, 0x4a, 	0x34, 0x4a,		0xFE,	0x7B, 0x80, 0x6e, 0x80,		0x08,	0x0ad301,	0x56bc5 ,	0x5c	,0x0	,	0xFE},
	//PAL-M,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            /*vsync*/  			  	         	// PAL M                                                
		{0x1D20A2,	0x15DC09,	0xE93E0, 	0x74BB7, 	0x38E, 	0x1, 	0x80, 0x18, 0x2, 0x0, 0x0, 0x0, 0x3c0, 0x1, 0x0, 0x0, 0x0, 	0x0, 	0x2, 0x1, 	0, 	0xDD, 0x3, 	0x32, 0x50, 0x21E6EFA4, 0x20000000, 0x27,	0x61, 0x0, 	0x8a,	0x8a, 0x0, 	0x0, 0x3, 	0x0, 0x1, 	0x0, 0x0, 	0x27, 0x61, 	0x88, 0x50, 	0x3, 0x25,		0x88, 0x50,		0x30, 0x10, 	0x1,	0x7, 	0x0, 0x0,	0x62,	0x50,	0x32, 0x46,		0x32, 0x46,		0x08, 0x09,	0x8c,	0x34, 0x51, 	0x34, 0x51, 	0x34, 0x51,		0xF2,	0x82, 0x80, 0x60, 0x80,		0x08,	0x08ab3b,	0x166ad ,	0x63	,0x0	,	0xFE},
	//PAL-CN,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      			  	         	// PAL CN                                               
		{0x22FB22, 	0x1A3FF1,	0x118128,	0x8C25F, 	0x396, 	0x1, 	0x80, 0x18, 0x3, 0x1, 0x1, 0x0, 0x3c0, 0x1, 0x0, 0x0, 0x0, 	0x0, 	0x2, 0x1, 	0, 	0xDC, 0x3, 	0x32, 0x50, 0x21f69446, 0x20000000, 0x2d,	0xC1, 0x0, 	0x80,	0x8a, 0x0, 	0x0, 0x3, 	0x0, 0x1, 	0x0, 0x0, 	0x2d, 0xC1, 	0x92, 0x4a, 	0x3, 0x25,		0x92, 0x4a,		0x18, 0x10, 	0x0,	0x5, 	0x0, 0x0,	0x6e,	0x50,	0x32, 0x6e,		0x32, 0x46,		0x08, 0x08,	0x92,	0x34, 0x4f, 	0x34, 0x4f, 	0x34, 0x4f,		0xFE,	0x7B, 0x80, 0x6e, 0x80,		0x08,	0x08bec7,	0x4613b ,	0x6e	,0x0	,	0xFE},	
	//PAL-60,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      			  	         	// PAL 60                                               
		{1 , 		1 ,	 		1 , 		1 , 		1 , 	0x1, 	0x80, 0x18, 0x1, 0x0, 0x0, 0x0, 0x3f0, 0x1, 0x0, 0x0, 0x0, 	0x0, 	0x2, 0x0, 	1, 	0xDD, 0x3, 	0x32, 0x50, 0x2A098ACB, 0x20000000, 0x27,	0x61, 0x0, 	0x80,	0x8a, 0x0, 	0x0, 0x3, 	0x0, 0x1, 	0x1, 0x0, 	0x27, 0x61, 	0x7D, 0x50, 	0x3, 0x25,		0x7D, 0x50,		0x18, 0x10,		0x1,	0x7, 	0x0, 0x0,	0x4F,	0x50,	0x32, 0x46,		0x32, 0x46,		0x08, 0x09,	0x8c,	0x34, 0x4a, 	0x34, 0x4a, 	0x34, 0x4a,		0xFE,	0x7B, 0x80, 0x60, 0x80,		0x08,	1,			1  ,		0x4f	,0x0	,	0xFE},
	//SECAM,                                                                                                                   	     	          	   	           	                                                       	               //110809                                                                                                                                                                                                                                                                                  			  	         	// SECAM                                            
		{1 , 		1 , 		1 , 		1 , 		1 , 	0x1, 	0x80, 0x18, 0x4, 0x1, 0x1, 0x0, 0x3f0, 0x0, 0x0, 0x0, 0x0, 	0x0, 	0x0, 0x0, 	0, 	0xDC, 0x5, 	0x32, 0x50, 0x28A33BB2, 0x20000000, 0x2b,	0xC1, 0x0, 	0x80,	0x8a, 0x1, 	0x1, 0x3, 	0x0, 0x1, 	0x1, 0x0, 	0x2b, 0xC1, 	0x8D, 0x50, 	0x3, 0x25,		0x8D, 0x50,		0x18, 0x10,		0x0,	0x2, 	0x0, 0x0,	0x48,	0x50,	0x32, 0x60,		0x32, 0x6E,		0x08, 0x08,	0x92,	0x32, 0x50, 	0x32, 0x60, 	0x32, 0x6e,		0xFE,	0x80, 0x80, 0x6e, 0x78,		0x20,	1,			1  		,	0x47	,0x0	,	0xFE},
																																																																																																																																				  //130118
	}
}; 		

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/


/*========================================================================================
  Implementation Group
  ========================================================================================*/

int CVD_O26Ax_Clamp_Current_Control(UINT8 value)
{
	int clamp_ctrl_retry_count;

	CVD_DEBUG("Clamp Current Ctrl [%d] RF[%d] internal demod[%d] tunning[%d] \n", \
			value, g_CVD_Status_3CS.in_rf_mode, g_CVD_Status_3CS.use_internal_demod, g_CVD_Status_3CS.in_atv_tunning);

	if(value <= 0x3)
	{
		if ( (g_CVD_Status_3CS.in_rf_mode == TRUE) && (g_CVD_Status_3CS.use_internal_demod) )	// if using internal demod
		{
			if(value > 0)
			{
				if(g_CVD_Status_3CS.in_atv_tunning == TRUE) {	// ATV Auto Scan
					// ABB RC Clamp Control (clamp count:0xa, step size :0xf)
					for( clamp_ctrl_retry_count = 0; clamp_ctrl_retry_count < 3; clamp_ctrl_retry_count++)
					{
#ifdef INCLUDE_KDRV_DEMOD
						if( DEMOD_ANALOG_Set_ClampingCtrl(0xA, 0xF) == RET_OK )
							break;
#endif
						OS_MsecSleep(10);
						AFE_ERROR("###### [%s][%d] DEMOD_ANALOG_Set_ClampingCtrl RETURN ERROR count[%d] ##### !!!!!\n", __func__, __LINE__, clamp_ctrl_retry_count);
					}
					/*
					// When Auto Scan , use default value to prevent channel skip
					CVD_Reg_RdFL(iris_057);
					CVD_Reg_Wr01(iris_057, reg_cpump_up_diff_max, 0x08);		
					CVD_Reg_Wr01(iris_057, reg_cpump_dn_diff_max, 0x08);
					CVD_Reg_WrFL(iris_057);
					*/
				}
				else {	// Channel Change or No Signal
					// ABB RC Clamp Control (clamp count:0xa, step size :0xf)
					for( clamp_ctrl_retry_count = 0; clamp_ctrl_retry_count < 3; clamp_ctrl_retry_count++)
					{
#ifdef INCLUDE_KDRV_DEMOD
						if( DEMOD_ANALOG_Set_ClampingCtrl(0xA, 0xF) == RET_OK )
							break;
#endif
						OS_MsecSleep(10);
						AFE_ERROR("###### [%s][%d] DEMOD_ANALOG_Set_ClampingCtrl RETURN ERROR count[%d] ##### !!!!!\n", __func__, __LINE__, clamp_ctrl_retry_count);
					}
					/*
					// for fast h-locking, inlarge the value to 0x20(from 0x08)
					// 0x7f : unlocking problem with cross hatch
					CVD_Reg_RdFL(iris_057);
					CVD_Reg_Wr01(iris_057, reg_cpump_up_diff_max, 0x08);		
					CVD_Reg_Wr01(iris_057, reg_cpump_dn_diff_max, 0x08);
					//CVD_Reg_Wr01(iris_057, reg_cpump_up_diff_max, 0x20);		
					//CVD_Reg_Wr01(iris_057, reg_cpump_dn_diff_max, 0x20);
					CVD_Reg_WrFL(iris_057);
					*/
				}
			}
			else
			{	// ATV Locked 
				// ABB RC Clamp Control (clamp count:0x3f, step size :0x1)
				for( clamp_ctrl_retry_count = 0; clamp_ctrl_retry_count < 3; clamp_ctrl_retry_count++)
				{
#ifdef INCLUDE_KDRV_DEMOD
					if(DEMOD_ANALOG_Set_ClampingCtrl(0x3F, 0x1) == RET_OK )
						break;
#endif
					OS_MsecSleep(10);
					AFE_ERROR("###### [%s][%d] DEMOD_ANALOG_Set_ClampingCtrl RETURN ERROR count[%d] ##### !!!!!\n", __func__, __LINE__, clamp_ctrl_retry_count);
				}
				/*
				CVD_Reg_RdFL(iris_057);
				CVD_Reg_Wr01(iris_057, reg_cpump_up_diff_max, 0x08);		//for 33% sync level test
				CVD_Reg_Wr01(iris_057, reg_cpump_dn_diff_max, 0x08);
				//CVD_Reg_Wr01(iris_057, reg_cpump_up_diff_max, 0x02);		//for 33% sync level test
				//CVD_Reg_Wr01(iris_057, reg_cpump_dn_diff_max, 0x02);
				CVD_Reg_WrFL(iris_057);
				 */
			}
		}
		else
		{
			/*
			CVD_Reg_RdFL(iris_057);
			CVD_Reg_Wr01(iris_057, reg_cpump_up_diff_max, 0x08);		//for fast h-locking, inlarge the value to 0x20(from 0x08)
			CVD_Reg_Wr01(iris_057, reg_cpump_dn_diff_max, 0x08);
			CVD_Reg_WrFL(iris_057);
			*/

#ifdef M16_CVBSAFE_BUG_WOKAROUND
			// clamp current to max 
			if (lx_chip_rev() <= LX_CHIP_REV(M16, A0))
				value = 3;
#endif
			CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
			CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_iclp, value);
			CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);

			/* M17 ATV Full White Unlocking : adc gain to 0 when unlock, 2 is written by default parameter ==> disabled */

			/*
			if(value > 0)
			{
				CVD_Reg_RdFL(iris_123);
				CVD_Reg_Wr01(iris_123, reg_adc_unity_gain_value, 0x0);
				CVD_Reg_WrFL(iris_123);
			}
			*/
		}
		return 0;
	}
	return -1;
}

// BOOLEAN PowerOnOff
// TRUE : Power Down
// FALSE : Power Up
void CVD_O26Ax_Power_Down(LX_AFE_CVD_SELECT_T select_main_sub, BOOLEAN PowerOnOFF)
{
	if(select_main_sub == LX_CVD_MAIN)
	{
		if(PowerOnOFF==FALSE) // from cvd_test.cmm
		{
			// O22 cvbs_pdbm control is done by bootcode, and should be '1' for 27Mhz clock 
//			CTOP_CTRL_O22Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc05, reg_cvbsafe_adc_pdbm, 0x1);
		}
		else
		{
			//CVD off
		}
	}
	else
	{
	}
}

void CVD_O26Ax_Reg_Init(LX_AFE_CVD_SELECT_T select_main_sub)
{


#if 0
	// No regulator in O26
	// SICDTV-10202 : 210805
	CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc07);
	CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc07, reg_cvbsafe_adc_regsel, 3); // 2 to 3
	CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc07);

	// SICDTV-10202 : 210825
	CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
	CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_cmlfsel, 4); // 3 to 4
	CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);
#endif

	//M16+ register change
	CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
	CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_cksel, 1);
	CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);

	CVD_Reg_RdFL(iris_063);
	CVD_Reg_Wr01(iris_063, reg_cg_off, 0x1f);	// CVD clock gating on (default 0x18)
	CVD_Reg_WrFL(iris_063);

	// CTop CVD Clock Settings
	// H13_BRINGUP
	/*
	   CTOP_CTRL_M16A0_RdFL(ctr25);
	   CTOP_CTRL_M16A0_Wr01(ctr25, reg_swrst_cvd54, 0x0);
	   CTOP_CTRL_M16A0_Wr01(ctr25, reg_swrst_cvd27, 0x0);
	   CTOP_CTRL_M16A0_Wr01(ctr25, reg_swrst_vbi, 0x0);
	   CTOP_CTRL_M16A0_Wr01(ctr25, reg_swrst_scart, 0x0);
	   CTOP_CTRL_M16A0_WrFL(ctr25);
	 */

	// 110901 : L9B0 Scart RGB register setting.
	// H13_BRINGUP : no reg_ch3pix_clk_sel register
	/*
	   CTOP_CTRL_M16A0_RdFL(ctr26_reg_extclk_div_sel);
	   CTOP_CTRL_M16A0_Wr01(ctr26_reg_extclk_div_sel, reg_ch3pix_clk_sel, 0x1);
	   CTOP_CTRL_M16A0_WrFL(ctr26_reg_extclk_div_sel);
	 */

	// 3D Comb memory mapping
	if(g_CVD_USE_TE_SHARED_POOL)
	{
		AFE_PRINT("CVD use te_shared pool\n");
	}
	else if(gpCvdMemCfg->memory_base == 0)
	{
		AFE_ERROR("###### Error Wrong Memory Base Address : gCVD_2d_mode enabled ##### !!!!!!!!!!!!!!!!!!!!!!!\n");
		gCVD_2d_mode = TRUE;
	}
	else {
		AFE_PRINT("### CVD Buffer Memory Base [0x%x]\n", gpCvdMemCfg->memory_base);
		CVD_Reg_RdFL(iris_mif_gmau_007);
		CVD_Reg_Wr01(iris_mif_gmau_007, reg_gmau_cmd_base, gpCvdMemCfg->memory_base);
		CVD_Reg_WrFL(iris_mif_gmau_007);

		CVD_Reg_RdFL(iris_mif_gmau_md_007);
		CVD_Reg_Wr01(iris_mif_gmau_md_007, reg_gmau_cmd_base_md, gpCvdMemCfg->memory_base + 0x420000);
		CVD_Reg_WrFL(iris_mif_gmau_md_007);
	}

	CVD_Reg_RdFL(iris_020);
	CVD_Reg_Wr01(iris_020, reg_blue_mode, 0x0);	// from 0x0 atv no-signal free-run
	CVD_Reg_WrFL(iris_020);
	// 0909 by kim.min(same setting with FPGA)

	CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
	CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_lpf, 1);
	CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_bw, 0);
	CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_dcatt, 1);
	CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);

	// 1210 Invert Odd/Even Field on B0 Revision(H/W Change or DE Firmware Change?)
	// But This has problem on CC data slicing.
	//gVportRegBx->iris_044.reg_flip_field = 1;
	// Initial Register Setting For Scart Fast Blanking.
	CVD_Reg_RdFL(fastblank_001);
	// Blend Ratio 0x08 is for test only
	//CVD_Reg_Wr04(fastblank_001, reg_fb_2line_delay, 0x1, reg_fb_blend_ratio, 0x08, reg_fb3ch_delay, 0xC, reg_fb_latency, 0x16);

	// CVD_H13_BRINGUP : SCART FB Changed !!!!
	//	reg_fb3ch_delay removed, reg_fb_2line_delay removed, reg_fb_lmflag_off added.
	//CVD_Reg_Wr04(fastblank_001, reg_fb_2line_delay, 0x1, reg_fb_blend_ratio, 0x10, reg_fb3ch_delay, 0xC, reg_fb_latency, 0x16);
	CVD_Reg_Wr02(fastblank_001, reg_fb_blend_ratio, 0x10, reg_fb_latency, 0x16);
	CVD_Reg_WrFL(fastblank_001);
	//For Test, Mix CVBS & RGB signal
	//gVportRegBx->fastblank_001.reg_fb_blend_ratio = 0x10;
	// For Faster 3D Comb lock(kim.min 20110110)
	// But, This produced 3D-Comb Lock-Unlocking problem on NTSC RF Signal
	// Setting reg_hnon_std_threshold to 0x0c(0x06) solve lock-unlock problem(20110221)
	CVD_Reg_RdFL(iris_024);
	//111007 by kim.min
	//CVD_Reg_Wr01(iris_024, reg_nstd_hysis, 0x3);
	//CVD_Reg_Wr01(iris_024, reg_nstd_hysis, 0x9);
	//111121 by kim.min
	//CVD_Reg_Wr01(iris_024, reg_nstd_hysis, 0x7);
	// 121226
	CVD_Reg_Wr01(iris_024, reg_nstd_hysis, 0x7);
	CVD_Reg_WrFL(iris_024);

	//111122 by gogosing
	CVD_Reg_RdFL(iris_064);
	CVD_Reg_Wr01(iris_064, reg_field_latency, 0x0);		//130111 : no hw reset	//0x5	//from default value 0x3
	CVD_Reg_WrFL(iris_064);
	//added 121217
	CVD_Reg_RdFL(iris_066);
	CVD_Reg_Wr01(iris_066, reg_field_latency_md, 0x0);	//130111 : no hw reset	//from default value 0x3
	CVD_Reg_WrFL(iris_066);

	// 110823 by kim.min
	CVD_Reg_RdFL(iris_074);
	//CVD_Reg_Wr02(iris_073, reg_syncmid_filter_en, 0x1, reg_dcrestore_accum_width, 0x1b);
	// 111102 by kim.min : for brazil PAL-M weak RF
	//CVD_Reg_Wr06(iris_073, reg_dcrestore_gain, 0x3, reg_syncmid_nobp_en, 0x1, reg_dcrestore_kill_enable, 0x1, reg_dcrestore_no_bad_bp, 0x1, reg_syncmid_filter_en, 0x1, reg_dcrestore_accum_width, 0x25);
	// 111114 by kim.min : modified reg_dcrestore_gain to 0x1(from 0x3, default 0x0) to fix H/V unlock problem on full white pattern.
	// 111121 by kim.min : modified reg_dcrestore_gain to 0x0(from 0x3, default 0x0)
	// 111121 by kim.min : modified reg_syncmid_nobp_en to 0x0(from 0x1, default 0x0)
	//CVD_Reg_Wr06(iris_073, reg_dcrestore_gain, 0x0, reg_syncmid_nobp_en, 0x0, reg_dcrestore_kill_enable, 0x1, reg_dcrestore_no_bad_bp, 0x1, reg_syncmid_filter_en, 0x1, reg_dcrestore_accum_width, 0x25);
	//111129 wonsik.do : dcrestore_accum_width is need to changed by color system
	CVD_Reg_Wr05(iris_074, reg_dcrestore_gain, 0x0, reg_syncmid_nobp_en, 0x0, reg_dcrestore_kill_enable, 0x1, reg_dcrestore_no_bad_bp, 0x1, reg_syncmid_filter_en, 0x1);
	CVD_Reg_WrFL(iris_074);

	// 111102 by kim.min : for brazil PAL-M weak RF
	CVD_Reg_RdFL(iris_071);
	CVD_Reg_Wr01(iris_071, reg_cagc_tc_ismall, 0x2);
	CVD_Reg_WrFL(iris_071);
	CVD_Reg_RdFL(iris_072);
	CVD_Reg_Wr02(iris_072, reg_cagc_tc_ibig, 0x1, reg_cagc_tc_p, 0x3);
	CVD_Reg_WrFL(iris_072);
	CVD_Reg_RdFL(iris_184);
	CVD_Reg_Wr03(iris_184, reg_cs_cagc_tc_ismall, 0x2, reg_cs_cagc_tc_ibig, 0x1, reg_cs_cagc_tc_p, 0x3);
	CVD_Reg_WrFL(iris_184);
	CVD_Reg_RdFL(iris_195);
	CVD_Reg_Wr03(iris_195, reg_cs1_cagc_tc_ismall, 0x2, reg_cs1_cagc_tc_ibig, 0x1, reg_cs1_cagc_tc_p, 0x3);
	CVD_Reg_WrFL(iris_195);


	// 110929 wonsik.do : restore to default value(agc_peak), for AWC test
	// Fast AGC operation : 110729
#ifdef L9_SLOW_AGC_WORKAROUND
	CVD_Reg_RdFL(iris_025);
	CVD_Reg_Wr01(iris_025, reg_agc_peak_nominal, 0x7F);	//Default : 0x0A
	CVD_Reg_Wr01(iris_025, reg_agc_peak_cntl, 0x0);		//Default : 0x1
	CVD_Reg_WrFL(iris_055);
#endif

	// At first, VDAC power should be turned off to hide transient artifact : 110803
	CVD_O26Ax_OnOff_VDAC(FALSE);

#if 0
	// by gogosing
	// Use fixed syncmid point, to enhance sync stability on weak RF signal.
	CVD_Reg_RdFL(iris_054);
	CVD_Reg_Wr01(iris_054, reg_cpump_fixed_syncmid, 0x1);
	// always reset accumulators when no-signal// gogosing ���� as default 0x01
	//CVD_Reg_Wr01(iris_054, reg_cpump_accum_mode, 0x0);
	CVD_Reg_WrFL(iris_054);
#else
	CVD_Reg_RdFL(iris_055);
	CVD_Reg_Wr01(iris_055, reg_cpump_fixed_syncmid, 0x0);
	CVD_Reg_Wr01(iris_055, reg_cpump_accum_mode, 0x0);
	CVD_Reg_WrFL(iris_055);
#endif

	// #### iris_014 Register Settings From Program_Color_System_Main_Multi ####
	//CVD_Reg_RdFL(iris_015);
	// For faster agc speed at channel change, set agc_half_en value to '0'
	//CVD_Reg_Wr01(iris_015, reg_agc_half_en, 0);
	// For faster agc speed at channel change, set hagc_field_mode value to '1'
	//CVD_Reg_Wr01(iris_014, reg_hagc_field_mode, 1);
	//CVD_Reg_WrFL(iris_015);

#ifdef L9_USE_SYNCTIP_ONLY_MODE
	//gogosing reg_hmgc 0x40 --> 0x60 with sync tip mode clamp
	CVD_Reg_RdFL(iris_076);
	CVD_Reg_Wr01(iris_076, reg_hmgc, 0x60);
	CVD_Reg_WrFL(iris_076);

	CVD_Reg_RdFL(iris_015);
	// dc_clamp_mode : 0(auto), 1(backporch), 2(synctip), 3(off)
	CVD_Reg_Wr01(iris_015, reg_dc_clamp_mode, 0x2);
	CVD_Reg_WrFL(iris_015);
#else
	CVD_Reg_RdFL(iris_076);
	CVD_Reg_Wr01(iris_076, reg_hmgc, 0x60);
	CVD_Reg_WrFL(iris_076);

	CVD_Reg_RdFL(iris_015);
	// dc_clamp_mode : 0(auto), 1(backporch), 2(synctip), 3(off)
	CVD_Reg_Wr01(iris_015, reg_dc_clamp_mode, 0x0);
	CVD_Reg_WrFL(iris_015);
#endif

	//110823 : New setting values by kim.min
	/* Cpump_Auto_Stip should be '1' : White saturation on normal signal */
	CVD_Reg_RdFL(iris_054);
	CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_noisy, 0x1);
	CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_no_signal, 0x1);
	CVD_Reg_Wr01(iris_054, reg_cpump_auto_stip_unlocked, 0x1);
	CVD_Reg_WrFL(iris_054);

	//0906 : filed inversion is needed ???
	//0909 : CVD filed inversion
	CVD_Reg_RdFL(iris_043);
	//CVD_Reg_Wr01(iris_043, reg_field_polarity, 0x1);	// setting to '1' inverts CVD odd/even field
	CVD_Reg_Wr01(iris_043, reg_field_polarity, 0x0);	// setting to '1' inverts CVD odd/even field
	CVD_Reg_WrFL(iris_043);

	//111104 by kim.min : picture blinking on weak RF signal
	CVD_Reg_RdFL(iris_017);
	CVD_Reg_Wr01(iris_017, reg_noise_thresh, 0x80);	// default 0x32
	CVD_Reg_WrFL(iris_017);

	//111121 kim.min : modified SCART RGB CSC.
	// Initial black level low
	CVD_Hal_Set_SCART_CSC(0);

	CVD_Hal_Set_SCART_Filter();

	//111221 by kim.min for better color standard detection performance
	CVD_Reg_RdFL(iris_188);
	CVD_Reg_Wr01(iris_188, reg_cs_chroma_sel, 0x1);	// default 0x0
	CVD_Reg_WrFL(iris_188);
	CVD_Reg_RdFL(iris_199);
	CVD_Reg_Wr01(iris_199, reg_cs1_chroma_sel, 0x1);	// default 0x0
	CVD_Reg_WrFL(iris_199);

#ifdef M16_CVD_INIT_OADJ_C
	CVD_Reg_RdFL(iris_121);
	CVD_Reg_Wr01(iris_121, reg_oadj_c_offi, 0x600);	// 2012.02.24 won.hur
	CVD_Reg_Wr01(iris_121, reg_oadj_c_offo, 0x200);	// 2012.02.24 won.hur
	CVD_Reg_WrFL(iris_121);

	// H13_BRINGUP
	CVD_Reg_RdFL(iris_123);
	CVD_Reg_Wr01(iris_123, reg_oadj_cr_offi, 0x600);	
	CVD_Reg_Wr01(iris_123, reg_oadj_cr_offo, 0x200);
	CVD_Reg_WrFL(iris_123);

	CVD_Reg_RdFL(iris_122);
	CVD_Reg_Wr01(iris_122, reg_oadj_c_coeff, 0x1000);	// 2012.02.24 won.hur
	// H13_BRINGUP
	CVD_Reg_Wr01(iris_122, reg_oadj_cr_coeff, 0x1000);
	CVD_Reg_WrFL(iris_122);
#endif


#ifdef L9_FAST_3DCOMB_WORKAROUND
	//120218 for fast 3D Comb operation
	CVD_Reg_RdFL(iris_067);
	CVD_Reg_Wr01(iris_067, reg_vf_nstd_en, 0x0);	// default 0x1
	CVD_Reg_WrFL(iris_067);
#endif
#ifdef CVD_FAST_3DCOMB_WORKAROUND
	//120803 : WA for 3DComb buffer error
	CVD_Reg_RdFL(iris_067);
	CVD_Reg_Wr01(iris_067, reg_vf_nstd_en, 0x1);	// default 0x1
	CVD_Reg_WrFL(iris_067);
#endif
	CVD_Reg_RdFL(iris_015);
	CVD_Reg_Wr01(iris_015, reg_hagc_en, 0x1);
	CVD_Reg_WrFL(iris_015);

	CVD_Reg_RdFL(iris_019);
	CVD_Reg_Wr01(iris_019, reg_adc_updn_swap, 0x1);
	CVD_Reg_WrFL(iris_019);

	//121119 : for Fast Chroma Lock/Unlocking !!!
	CVD_Reg_RdFL(iris_047);
	CVD_Reg_Wr01(iris_047, reg_lose_chromalock_level, 0x5);	//default 0x7
	CVD_Reg_WrFL(iris_047);

	//121205 : Fast H/V Locking on channel change
	CVD_Reg_RdFL(iris_015);
	CVD_Reg_Wr01(iris_015, reg_agc_half_en, 1);
	CVD_Reg_WrFL(iris_015);

	//130123 : new cordic setting
	CVD_Reg_RdFL(iris_344);
	CVD_Reg_RdFL(iris_345);
	CVD_Reg_RdFL(iris_346);
	CVD_Reg_Wr01(iris_344, reg_cordic_ctrl0, 		0x80000003);
	CVD_Reg_Wr01(iris_345, reg_cs_cordic_ctrl0, 	0x80000003);
	CVD_Reg_Wr01(iris_346, reg_cs1_cordic_ctrl0, 	0x80000003);
	CVD_Reg_WrFL(iris_344);
	CVD_Reg_WrFL(iris_345);
	CVD_Reg_WrFL(iris_346);

//	CVD_Hal_Init_Level_Detector();

#ifdef CVD_HSYNC_ENHANCEMENT
	CVD_Hal_Set_Hsync_Enhance(0);
#endif
#ifdef CVD_VSYNC_ENHANCEMENT
	CVD_Hal_Set_Vsync_Enhance(0);
#endif

	/* M16 Enable SCART Fast Blanking */
	CVD_Reg_RdFL(fastblank_001);
	CVD_Reg_Wr01(fastblank_001, reg_fb_pin, 0x1);
	CVD_Reg_WrFL(fastblank_001);

	/* M16 11bit truncation */

	/* M16 SCART out currnet setting */

	/* M16 cvbs_iclp2 : 0x3 */
	CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
	CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_iclp2, 0x3);	//160120 : iclp2
	CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);

	/* M16P CVBS Gain : 0dB */
	/* M16+ Full White ATV H Unlocking : gain to 0 when unlock state */
	/* O18/M16++ Full White ATV H Unlocking : gain to 0 (70% gain) : 171016 */
	CVD_Reg_RdFL(iris_123);
	CVD_Reg_Wr01(iris_123, reg_adc_unity_gain_value, 0x0);
	CVD_Reg_WrFL(iris_123);

	/* M16+ Full White ATV H Unlocking */
	CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
	CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_dcsel, 0x1);  //211005 : o22 PRODTESTH-1125 0x1(0.9V) //190522 O20 : 12n 0x3(1.0V)  //160919 : DC reference level 0.8V -> 1.0V
	CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);

	/* For SECAM auto burst position */
	CVD_Hal_Set_Burst_Gate_12(0x32, 0x3a, 0x62, 0x6a);

	CVD_Reg_RdFL(iris_375);
	CVD_Reg_Wr01(iris_375, reg_burst_mag_ctrl, 0x70);
	CVD_Reg_WrFL(iris_375);


	return;
}

int CVD_O26Ax_Set_Source_Type(LX_AFE_CVD_SET_INPUT_T	cvd_input_info)
{
	//120118 : first disable SCART FB at source change
	CVD_Hal_Set_Scart_FB_En(0);
	//gEnableScartFB = 0;

	if(cvd_input_info.cvd_input_source_type == LX_CVD_INPUT_SOURCE_CVBS) // for composite
	{

		//			AFE_PRINT("Composite input\n");
		// Only Composite Input : no need to set reg_yc_src
		/*
		CVD_Reg_RdFL(iris_013);
		CVD_Reg_Wr01(iris_013, reg_yc_src, 0);
		CVD_Reg_WrFL(iris_013);
		*/
		CVD_DEBUG("Input source = [%d]\n", cvd_input_info.cvbs_input_port);
		//gVportRegBx->top_002.reg_exta_sel = 0;	// from cvd_test.cmm
		//gVportRegBx->top_002.reg_extb_sel = 0;	// from cvd_test.cmm
		switch(cvd_input_info.cvbs_input_port)
		{
			case LX_AFE_CVBS_IN1:
				CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
				CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_insel, 0x0);
				CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_shield_on, 0x1);
				CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);
				break;
			case LX_AFE_CVBS_IN2:
				CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
				CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_insel, 0x1);
				CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_shield_on, 0x2);
				CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);
				break;
			case LX_AFE_CVBS_IN3:
			case LX_AFE_CVBS_IN4:
			case LX_AFE_CVBS_IN5:
			case LX_AFE_CVBS_IN6:
			default:
				AFE_ERROR("No [%d] port supported !!!! [%s][%d]\n", cvd_input_info.cvbs_input_port, __func__, __LINE__ );
				break;
		}

		if (cvd_input_info.cvd_input_source_attribute != LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF)
		{
			CVD_DEBUG("Not RF set abb_mux_sel to 1\n");
			CVD_O26Ax_Set_Internal_Demod_Mode(0);
			CVD_Hal_agc_half_en_control(0);	// to prevent random VLOCK!
#ifdef M16_CVBSAFE_BUG_WOKAROUND
			if (lx_chip_rev() <= LX_CHIP_REV(M16, A0))
			{
				//1 : Select IN2(SCART path)
				ACE_REG_O26A0_RdFL(videoafe18);
				ACE_REG_O26A0_Wr01(videoafe18, reg_cvbsafe_adc_insel, 0x1);
				ACE_REG_O26A0_WrFL(videoafe18);

				//2 : invert CVD clamping
				CVD_Reg_RdFL(iris_019);
				CVD_Reg_Wr01(iris_019, reg_adc_updn_swap, 0x0);
				CVD_Reg_WrFL(iris_019);
			}
#endif
		}
		else
		{
			CVD_DEBUG("RF Mode : set abb_mux_sel to 0\n");
			//ACE_REG_M17A0_RdFL(abb_02);
			if(g_CVD_Status_3CS.use_internal_demod)	// if using internal demod
				CVD_O26Ax_Set_Internal_Demod_Mode(1);
			else
				CVD_O26Ax_Set_Internal_Demod_Mode(0);

			CVD_Hal_agc_half_en_control(1);	// default value

#ifdef M16_CVBSAFE_BUG_WOKAROUND
			if (lx_chip_rev() <= LX_CHIP_REV(M16, A0))
			{
				//1 :  CVD clamping
				CVD_Reg_RdFL(iris_019);
				CVD_Reg_Wr01(iris_019, reg_adc_updn_swap, 0x1);
				CVD_Reg_WrFL(iris_019);
			}
#endif
		}

	}
	else // for S-Video
	{
		AFE_ERROR("S-Video is not supported.\n");
	}
	//Current_State = CVD_STATE_VideoNotReady;
	//Next_State = CVD_STATE_VideoNotReady;
	return 0;
}

int CVD_O26Ax_Get_Scart_FB_En(void)
{
	int ret;
	CVD_Reg_RdFL(fastblank_001);
	CVD_Reg_Rd01(fastblank_001, reg_fb_en, ret);
	return ret;
}

// won.hur : This function needs to be changed!!!
// This is because L9B0 has no ghslvdstx2
// This part is disabled!!
int CVD_O26Ax_Channel_Power_Control(UINT32 on_off)
{
	UINT8	/*dr3p_pdb_status, */ cvbs_pdbm_status, cvbs_pdb_status, cvbs_cp_status, cvd_soft_reset;

	CVD_DEBUG("%s entered :  %d \n",__func__, on_off);

	if(on_off)	// power ON
	{
		//OS_MsecSleep(5);
		usleep_range(10000, 15000);

		// Normal condition
		//ACE_REG_M17A0_RdFL(main_pll_4);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
		CTOP_CTRL_O26Ax_Rd01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_pdbm, cvbs_pdbm_status);
		CTOP_CTRL_O26Ax_Rd01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_pdb, cvbs_pdb_status);
		//ACE_REG_M17A0_Rd01(main_pll_4, dr3p_pdb, dr3p_pdb_status);
		CTOP_CTRL_O26Ax_Rd01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_clp, cvbs_cp_status);

		CVD_Reg_RdFL(iris_012);
		CVD_Reg_Rd01(iris_012, reg_cvd_soft_reset, cvd_soft_reset);

		if(cvbs_pdbm_status && cvbs_pdb_status && cvbs_cp_status && (~cvd_soft_reset) )	// all cvd power is already on !!@!!
		{
			CVD_DEBUG("%s : CVD Power Already ON !!!\n",__func__);
			return 0;
		}

		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_pdbm, 0x1);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_pdb, 0x1);
#if 0	//no regulator in O26
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc05, reg_cvbsafe_adc_reg_pdb, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);
#endif
		//ACE_REG_M17A0_Wr01(main_pll_4, dr3p_pdb, 0x1);

		//added 110622 : by tommy.lee to disable clamp control on power down condition
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_clp, 1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);
		//ACE_REG_M17A0_WrFL(main_pll_4);
#ifdef M16_IRIS_CLAMPAGC_V2_CONTROL_WA_FOR_CVD_UNLOCK
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_clampagc_v2, 0);
		CVD_Reg_WrFL(iris_175);
#endif
		//OS_MsecSleep(20);
		usleep_range(20000, 25000);
		//by dws : remove mdelay
		//mdelay(5);
		//OS_MsecSleep(5);

		//121210 : cvd soft reset during ADC Power down condition
		CVD_Reg_RdFL(iris_012);
		CVD_Reg_Wr01(iris_012, reg_cvd_soft_reset, 0);
		CVD_Reg_WrFL(iris_012);

/*
		ACE_REG_M17A0_RdFL(soft_reset_5);
		ACE_REG_M17A0_Wr01(soft_reset_5, swrst_f54m, 0);
		ACE_REG_M17A0_Wr01(soft_reset_5, swrst_cvbs, 0);
		ACE_REG_M17A0_WrFL(soft_reset_5);
		*/

#ifdef CVD_3DCOMB_ERROR_WORKAROUND
		CVD_Hal_3DComb_Workaround(20); // enable  workaround function
#endif

		/* reset cvd27 clock to apply register settings during cvbs_pdb down */

#ifdef _SCRG_CTRL_CVI_REG_O26A0_H_
		CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_CVI, crg_cvi003);
		CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CVI, crg_cvi003, reg_soft_rst_cvd27_n, 0x1);
		CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_CVI, crg_cvi003);

		CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_CVI, crg_cvi003);
		CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CVI, crg_cvi003, reg_soft_rst_cvd27_n, 0x0);
		CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_CVI, crg_cvi003);
#endif
	}
	else	// power off
	{
#ifdef CVD_3DCOMB_ERROR_WORKAROUND
		CVD_Hal_3DComb_Workaround(10); // Memory Reset & bypass workaround function
#endif
		//OS_MsecSleep(5);
		usleep_range(5000, 10000);

		//121210 : cvd soft reset during ADC Power down condition
		CVD_Reg_RdFL(iris_012);
		CVD_Reg_Wr01(iris_012, reg_cvd_soft_reset, 1);
		CVD_Reg_WrFL(iris_012);

		//OS_MsecSleep(20);
		usleep_range(10000, 15000);

#ifdef M16_IRIS_CLAMPAGC_V2_CONTROL_WA_FOR_CVD_UNLOCK
		CVD_Reg_RdFL(iris_175);
		CVD_Reg_Wr01(iris_175, iris_clampagc_v2, 1);
		CVD_Reg_WrFL(iris_175);
#endif
#if 0 // won.hur
		//L9A_DIE TX to L9D_DIE off
		ACE_REG_M19A0_RdFL(hslvdstx2_0);
		ACE_REG_M19A0_RdFL(hslvdstx2_1);
		ACE_REG_M19A0_Wr01(hslvdstx2_0, pdb3, 0);
		ACE_REG_M19A0_Wr01(hslvdstx2_1, ch_en3, 0);
		ACE_REG_M19A0_WrFL(hslvdstx2_0);
		ACE_REG_M19A0_WrFL(hslvdstx2_1);
#endif // won.hur

		// Power down
		/*
		   ACE_REG_M17A0_RdFL(soft_reset_5);
		   ACE_REG_M17A0_Wr01(soft_reset_5, swrst_f54m, 0x1);
		   ACE_REG_M17A0_Wr01(soft_reset_5, swrst_cvbs, 0x1);
		   ACE_REG_M17A0_WrFL(soft_reset_5);
		 */

		//Do Not Turn Off CVBS_PDBM, to enable clock  for DENC
		//gafe_cvbs_1.cvbs_pdbm = 0;

		//M16Ax Still have problem on DTV SCART out when cvbs_pdb is OFF
//		if (lx_chip_rev() >= LX_CHIP_REV(M14, B0))
//			ACE_REG_M17A0_Wr01(videoafe_12, cvbs_pdb, 0);
//
//		// M16+ B1 : Component Noise when CVBS PDB is On : 161013
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_pdb, 0);
#if 0	//no regulator in O26
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_reg_pdb, 0x0);
#endif

		//added 110622 : by tommy.lee to disable clamp control on power down condition
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_clp, 0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_CVBSAFE, mip_adc06);

#ifdef M16_COMB2D_ONLY_CONTROL
		//120705 : Enable comb2d_only mode when CVBS ADC is in power down mode.
		CVD_DEBUG("### Comb2d only [1] [%s][%d] ###\n",__func__, __LINE__ );
		CVD_Hal_Set_comb2d_only(1);
		CVD_Hal_Set_comb2d_only_md(1);
#endif
		//OS_MsecSleep(5);
		usleep_range(5000, 10000);

	}

	return 0;
}

int CVD_O26Ax_Bypass_Control(LX_AFE_CVD_BYPASS_CONTROL_T *cvd_bypass_control_t)
{
	CVD_DEBUG("%s entered :  buf1[%d] buf2[%d] src[%d]\n",__func__, cvd_bypass_control_t->buf_out_1_sel, cvd_bypass_control_t->buf_out_2_sel, cvd_bypass_control_t->cvbs_source_sel);

	switch(cvd_bypass_control_t->buf_out_1_sel)
	{
		case CVD_BYPASS_DAC:
	//		ACE_REG_M17A0_Wr01(afe_vbuf_3, bufclp_vref, 0x0);

			break;

		case CVD_BYPASS_CVBS_WITH_CLAMPING:

			break;

		case CVD_BYPASS_CVBS_WITH_CLAMPING_AV:

			break;

		case CVD_BYPASS_CVBS_WITHOUT_CLAMPING:

			break;

		case CVD_BYPASS_CVBS_BUF_CLAMPING_ON:
//			ACE_REG_M17A0_Wr01(afe_vbuf_1, buf_pdb1, 0x1);	//SCART PDB On
			break;

		case CVD_BYPASS_CVBS_BUF_CLAMPING_OFF:	// CVD PDB & Clamping ON
//			ACE_REG_M17A0_Wr01(afe_vbuf_1, buf_pdb1, 0x1);	//SCART PDB On
			break;

		case CVD_BYPASS_ABB:	// same with BYPASS_DAC except abb_dmd_cvbsdac_sel = '1'
			break;

		case CVD_BYPASS_ABB_RC:	// CVD PDB & Clamping ON
			break;

		default:
			break;
	}

	switch(cvd_bypass_control_t->buf_out_2_sel)
	{
		case CVD_BYPASS_DAC:
			break;

		case CVD_BYPASS_CVBS_WITH_CLAMPING:
			break;

		case CVD_BYPASS_CVBS_WITHOUT_CLAMPING:
			break;

		default:
			break;
	}


	return 0;
}

int CVD_O26Ax_OnOff_VDAC(BOOLEAN bonoff)
{

	CVD_DEBUG("%s entered :  %d \n",__func__, bonoff);


	return 0;
}

int CVD_O26Ax_VDAC_mute_control(int enable)
{

	return 0;
}

int CVD_O26Ax_Get_PE0_Motion_Value(int *p_tnr_x_avg_t, int *p_tnr_x_avg_s, int *p_tpd_s_status)
{
	/* w_apl_motion <= ma_motion <= X_Avg_T, w_apl_val <= ma_var <= X_Avg_S */
	/* s_status <= TPD_S : to be changed */
#if defined(INCLUDE_KDRV_PE) && defined(INCLUDE_O26_PE_REG)
	UINT32 data[3];

	if (!p_tnr_x_avg_t)		return -1;
	if (!p_tnr_x_avg_s)		return -1;
	if (!p_tpd_s_status)	return -1;

	if (0 == pe_hal_get_status(data, 3))
	{
		*p_tnr_x_avg_t = data[0];
		*p_tnr_x_avg_s = data[1];
		*p_tpd_s_status = data[2];
	}
#endif
	return 0;
}

int CVD_O26Ax_Get_AFE_CVBS_status(UINT8 *cvbs_icon_value, UINT8 *cvbs_pdb_value, UINT8 *cvbs_cp_value, UINT8 *cvbs_insel_value, UINT8 *cvbs_pdbm_value)
{
	CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_CVBSAFE, mip_adc06);
	CTOP_CTRL_O26Ax_Rd01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_iclp, *cvbs_icon_value);
	CTOP_CTRL_O26Ax_Rd01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_pdb, *cvbs_pdb_value);
	CTOP_CTRL_O26Ax_Rd01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_clp, *cvbs_cp_value);
	CTOP_CTRL_O26Ax_Rd01(MIP_CTRL_CVBSAFE, mip_adc06, reg_cvbsafe_adc_insel, *cvbs_insel_value);

	return 0;
}

int CVD_O26Ax_Set_Internal_Demod_Mode(BOOLEAN bInternal_Demod)
{
	CVD_DEBUG("%s entered :  %d \n",__func__, bInternal_Demod);

	if(bInternal_Demod)
	{	
		// Disable due to 33% sync level test
		// 130712 : kim.min fixed full white pattern unloking
		//CVD_Hal_Set_Cpump_Auto_Stip_Mode(3);

		//CVD_Reg_RdFL(iris_057);
		//CVD_Reg_Wr01(iris_057, reg_cpump_up_diff_max, 0x20);		//for fast h-locking, inlarge the value to 0x20(from 0x08)
		//CVD_Reg_Wr01(iris_057, reg_cpump_dn_diff_max, 0x20);
		//CVD_Reg_WrFL(iris_057);

	}
	else
	{
		//CVD_Hal_Set_Cpump_Auto_Stip_Mode(2);

		//CVD_Reg_RdFL(iris_057);
		//CVD_Reg_Wr01(iris_057, reg_cpump_up_diff_max, 0x08);		//for fast h-locking, inlarge the value to 0x20(from 0x08)
		//CVD_Reg_Wr01(iris_057, reg_cpump_dn_diff_max, 0x08);
		//CVD_Reg_WrFL(iris_057);

	}

	return 0;
}

int CVD_O26Ax_OnOff_DMD_DAC(BOOLEAN bonoff)
{

	//VBUF_PDB3 was deleted
	CVD_DEBUG("%s entered :  %d \n",__func__, bonoff);

	if(bonoff)	// power on
	{
	}
	else	// power off
	{
	}

	return 0;
}

#if defined(INCLUDE_KDRV_PE) && defined(INCLUDE_O26_PE_REG)
#define CVD_O26Ax_CHK_DFLT_SIZE(_x)		\
	if (PE_DDR_O26_CVD_DFLT_SIZE != (sizeof(_x)/sizeof(CVD_REG_PARAM_T)))\
	{AFE_ERROR("%s size is wrong\n", #_x); ret=RET_ERROR;break;}

int CVD_O26Ax_SetPqModeToDdr(volatile UINT32 *p_ddr_reg)
{
	int ret = RET_OK;
	UINT32 i;
	UINT32 base_dflt[PE_DDR_O26_CVD_DFLT_ITEM_NUM];
	do{
		if (!p_ddr_reg)	{ AFE_ERROR("p_ddr_reg is Null\n"); ret=RET_ERROR;break; }
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_av_ntsc_m_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_rf_ntsc_m_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_av_pali_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_rf_pali_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_av_secam_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_rf_secam_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_av_ntsc_443_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_av_pal60_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_av_palm_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_rf_palm_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_av_palnc_l_default_o26);
		CVD_O26Ax_CHK_DFLT_SIZE(cvd_rf_palnc_l_default_o26);
		base_dflt[0] = 0;
		for (i=1; i<PE_DDR_O26_CVD_DFLT_ITEM_NUM; i++)
		{
			base_dflt[i] = base_dflt[i-1]+PE_DDR_O26_CVD_DFLT_SIZE;
		}
		for (i=0; i<PE_DDR_O26_CVD_DFLT_SIZE; i++)
		{
			p_ddr_reg[base_dflt[0]+i] = cvd_av_ntsc_m_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[1]+i] = cvd_rf_ntsc_m_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[2]+i] = cvd_av_pali_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[3]+i] = cvd_rf_pali_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[4]+i] = cvd_av_secam_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[5]+i] = cvd_rf_secam_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[6]+i] = cvd_av_ntsc_443_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[7]+i] = cvd_av_pal60_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[8]+i]  = cvd_av_palm_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[9]+i]  = cvd_rf_palm_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[10]+i] = cvd_av_palnc_l_default_o26[i].cvd_pe_value;
			p_ddr_reg[base_dflt[11]+i] = cvd_rf_palnc_l_default_o26[i].cvd_pe_value;
		}
	}while (0);
	return ret;
}
#endif

int CVD_O26Ax_Set_PQ_Mode(LX_AFE_CVD_PQ_MODE_T cvd_pq_mode)
{
	CVD_REG_PARAM_T	*pCVD_PE_Param_t;
	UINT32	size;
	static LX_AFE_CVD_PQ_MODE_T prev_cvd_pq_mode = LX_CVD_PQ_DEFAULT;

	CVD_DEBUG("@@@@@ CVD Set PQ Mode to [%d]@@@@@\n", cvd_pq_mode);

	/*
	   if(prev_cvd_pq_mode ==cvd_pq_mode) {
	   CVD_DEBUG("SAME CVD PE Param, bypass PE settings !\n");
	   return -1;
	   }
	 */

	switch(cvd_pq_mode)
	{
		case LX_CVD_PQ_NTSC_M:		// AV NTSC
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_ntsc_m_l_default_o26;
			size	= sizeof(cvd_av_ntsc_m_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_NTSC_M_RF:	// RF NTSC
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_rf_ntsc_m_l_default_o26;
			size	= sizeof(cvd_rf_ntsc_m_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_PAL:			// AV PAL
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_pali_l_default_o26;
			size	= sizeof(cvd_av_pali_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_PAL_RF:		// RF PAL
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_rf_pali_l_default_o26;
			size	= sizeof(cvd_rf_pali_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_SECAM:		// AV SECAM
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_secam_l_default_o26;
			size	= sizeof(cvd_av_secam_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_SECAM_RF:	// RF SECAM
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_rf_secam_l_default_o26;
			size	= sizeof(cvd_rf_secam_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_NTSC_443:		// AV NTSC 443
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_ntsc_443_l_default_o26;
			size	= sizeof(cvd_av_ntsc_443_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_NTSC_443_RF:	// RF NTSC 443
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_ntsc_443_l_default_o26;
			size	= sizeof(cvd_av_ntsc_443_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_PAL_60:			// AV PAL 60
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_pal60_l_default_o26;
			size	= sizeof(cvd_av_pal60_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_PAL_60_RF:		// RF PAL 60
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_pal60_l_default_o26;
			size	= sizeof(cvd_av_pal60_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_PAL_M:		// AV PAL M
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_palm_l_default_o26;
			size	= sizeof(cvd_av_palm_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_PAL_M_RF:	// RF PAL M
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_rf_palm_l_default_o26;
			size	= sizeof(cvd_rf_palm_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_PAL_NC:		// AV PAL NC
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_av_palnc_l_default_o26;
			size	= sizeof(cvd_av_palnc_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		case LX_CVD_PQ_PAL_NC_RF:	// RF PAL NC
			pCVD_PE_Param_t = (CVD_REG_PARAM_T *)cvd_rf_palnc_l_default_o26;
			size	= sizeof(cvd_rf_palnc_l_default_o26) / sizeof(CVD_REG_PARAM_T) ;
			break;
		default:
			AFE_PRINT("@@@ ERROR unknown color system [%d] @@@\n", cvd_pq_mode);
			return -1;
	}

	prev_cvd_pq_mode = cvd_pq_mode;

	// CVD_M14B0_Bringup
	// B0 PE Parameter is Needed !!!!
	CVD_Hal_Set_PE_Params(pCVD_PE_Param_t, size, cvd_pq_mode);


	/* Restore TTX Setting to Default Value */
	/* lpf_0_en is set by Set_PE_Params function */


	if ( ( gEnableTTXTestPatch == 1) && (gStatusTTXTestPatch == 1) )
	{
		CVD_DEBUG("!!! TTX Test Mode Disabled !!!\n");

		gStatusTTXTestPatch = 0;

		CVD_Reg_RdFL(vbi_036);
		CVD_Reg_Wr(vbi_036, 0x01181113);	//reg_ttx_iir_mode_sel to "1"
		CVD_Reg_WrFL(vbi_036);

		//180622 : Added for eye height 45%
		CVD_Reg_RdFL(vbi_017);
		CVD_Reg_Wr01(vbi_017, reg_vbi_tele_lpfil_acq_gain, 0x8);	//"0x8" (default)
		CVD_Reg_Wr01(vbi_017, reg_vbi_tele_lpfil_track_gain, 0x4);	//to "0x4" (default)
		CVD_Reg_WrFL(vbi_017);
	}

	return 0;

}

int CVD_O26Ax_Black_Level_Control(LX_AFE_CVD_BLACK_LEVEL_T black_level, LX_AFE_CVD_SOURCE_ATTRIBUTE_T rf_av_mode)
{
	CVD_REG_PARAM_T	*pCVD_Black_Level_Param_t;
	UINT32	size;

	CVD_DEBUG("@@@@@ CVD Set Black Level to black_level[%d], rf_av_mode[%d]@@@@@\n", black_level, rf_av_mode);

	if( (black_level == LX_AFE_CVD_BLACK_LEVEL_HIGH) && (rf_av_mode == LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF) )
	{
			pCVD_Black_Level_Param_t = (CVD_REG_PARAM_T *)cvd_rf_ntsc_m_black_level_high;
			size	= sizeof(cvd_rf_ntsc_m_black_level_high) / sizeof(CVD_REG_PARAM_T) ;
	}
	else if( (black_level == LX_AFE_CVD_BLACK_LEVEL_HIGH) && (rf_av_mode != LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF) )
	{
			pCVD_Black_Level_Param_t = (CVD_REG_PARAM_T *)cvd_av_ntsc_m_black_level_high;
			size	= sizeof(cvd_av_ntsc_m_black_level_high) / sizeof(CVD_REG_PARAM_T) ;
	}
	else if( (black_level == LX_AFE_CVD_BLACK_LEVEL_LOW) && (rf_av_mode == LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF) )
	{
			pCVD_Black_Level_Param_t = (CVD_REG_PARAM_T *)cvd_rf_ntsc_m_black_level_low;
			size	= sizeof(cvd_rf_ntsc_m_black_level_low) / sizeof(CVD_REG_PARAM_T) ;
	}
	else if( (black_level == LX_AFE_CVD_BLACK_LEVEL_LOW) && (rf_av_mode != LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF) )
	{
			pCVD_Black_Level_Param_t = (CVD_REG_PARAM_T *)cvd_av_ntsc_m_black_level_low;
			size	= sizeof(cvd_av_ntsc_m_black_level_low) / sizeof(CVD_REG_PARAM_T) ;
	}
	else
	{
		AFE_ERROR("!!!!!!!!!!! WRONG black_level[%d], rf_av_mode[%d]@@@@@\n", black_level, rf_av_mode);
		return -1;
	}

	CVD_Hal_Set_OADJ(pCVD_Black_Level_Param_t, size);

	return 0;

}

int CVD_O26Ax_Set_Buffer_Base_Addr(phys_addr_t cvd_paddr)
{
	if(cvd_paddr == 0)
		return -1;

	AFE_PRINT("### CVD Buffer Memory Base [%#llx]\n", (unsigned long long)cvd_paddr);
	CVD_Reg_RdFL(iris_mif_gmau_007);
	CVD_Reg_Wr01(iris_mif_gmau_007, reg_gmau_cmd_base, cvd_paddr);
	CVD_Reg_WrFL(iris_mif_gmau_007);

	CVD_Reg_RdFL(iris_mif_gmau_md_007);
	CVD_Reg_Wr01(iris_mif_gmau_md_007, reg_gmau_cmd_base_md, cvd_paddr + 0x420000);
	CVD_Reg_WrFL(iris_mif_gmau_md_007);

	return 0;
}

