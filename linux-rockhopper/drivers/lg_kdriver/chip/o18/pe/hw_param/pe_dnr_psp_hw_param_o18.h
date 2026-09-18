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

/** @file pe_dnr_psp_hw_param_o18.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_DNR_PSP_HW_PARAM_O18_H_
#define	_PE_DNR_PSP_HW_PARAM_O18_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"

#include "pe_dnrpsp_l_hd_default_o18.h"
#include "pe_dnrpsp_l_sd_default_o18.h"
#include "pe_dnrpsp_l_ud_default_o18.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/
/**
 *	dnr psp hw param reg type
 */
 
typedef struct {
	PE_O18_PSP_CTRL00_T                               psp_ctrl00;	//0x0000
	PE_O18_PSP_CTRL01_T                               psp_ctrl01;	//0x0004
	PE_O18_PSP_CTRL02_T                               psp_ctrl02;	//0x0008
	PE_O18_EDGE_TH_T                                  edge_th;	//0x000C
	PE_O18_FG_POSITION_T                              fg_position;	//0x0010
	PE_O18_PERSPECT_LUT_X0_T                          perspect_lut_x0;	//0x0014
	PE_O18_PERSPECT_LUT_X1_T                          perspect_lut_x1;	//0x0018
	PE_O18_PERSPECT_LUT_X2_T                          perspect_lut_x2;	//0x001C
	PE_O18_PERSPECT_LUT_X3_T                          perspect_lut_x3;	//0x0020
	PE_O18_PERSPECT_LUT_Y0_T                          perspect_lut_y0;	//0x0024
	PE_O18_PERSPECT_LUT_Y1_T                          perspect_lut_y1;	//0x0028
	PE_O18_PERSPECT_LUT_Y2_T                          perspect_lut_y2;	//0x002C
	PE_O18_PERSPECT_LUT_Y3_T                          perspect_lut_y3;	//0x0030
	PE_O18_PROB_MAP_T                                 prob_map;	//0x0034
	PE_O18_ELLIPS_MAP_T                               ellips_map;	//0x0038
	PE_O18_PROB_DIFF_MAP_T                            prob_diff_map;	//0x003C
	PE_O18_OBJECT_MAP_T                               object_map;	//0x0040
	PE_O18_BLUR_MAP_T                                 blur_map;	//0x0044
	PE_O18_DISPLAY_DEBUG_MAP_T                        display_debug_map;	//0x0048
	PE_O18_PSP_IIR_T                                  psp_iir;	//0x004C
	PE_O18_PSP_GAIN_T                                 psp_gain;	//0x0050
	PE_O18_VRTX_CPC_CTRL_T                            vrtx_cpc_ctrl;	//0x005C
	PE_O18_BLUR_HCOEF01_T                             blur_hcoef01;	//0x0060
	PE_O18_BLUR_HCOEF23_T                             blur_hcoef23;	//0x0064
	PE_O18_BLUR_HCOEFF45_T                            blur_hcoeff45;	//0x0068
	PE_O18_BLUR_HCOEFF67_T                            blur_hcoeff67;	//0x006C
	PE_O18_BLUR_HCOEF8_T                              blur_hcoef8;	//0x0070
	PE_O18_BLUR_VCOEF01_T                             blur_vcoef01;	//0x0074
	PE_O18_BLUR_VCOEF23_T                             blur_vcoef23;	//0x0078
	PE_O18_BLUR_VCOEF4_T                              blur_vcoef4;	//0x007C
}PE_DNR_PSP_HW_PARAM_REG_O18_T;

/**
 *	dnr psp hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_PSP_HW_PARAM_REG_O18_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_PSP_HW_PARAM_REG_O18_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_PSP_HW_PARAM_REG_O18_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_PSP_HW_PARAM_REG_O18_T *data;
	} reg_data;
} PE_DNR_PSP_HW_PARAM_DATA_O18_T;


/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNR_HW_PARAM_O18_H_ */
