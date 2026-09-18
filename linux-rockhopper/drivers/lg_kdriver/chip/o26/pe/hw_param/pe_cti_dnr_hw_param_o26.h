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

/** @file pe_cti_dnr_hw_param_o26.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_CTI_DNR_HW_PARAM_O26_H_
#define	_PE_CTI_DNR_HW_PARAM_O26_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"

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
/*-----------------------------------------------------------------------------
							 0xc901858cL cti_ctrl_0 							
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cti_en							   :1 , // 0 
	cti_clipping_mode				   :1 , // 1 
	cti_pre_flt_mode				   :1 , // 2 
	cti_tap 						   :2 , // 4:3
	reserved01						   :3 , // reserved
	cti_gain						   :8 , // 15:8
	cti_debug_mode					   :3 ; // 18:16
}PE_O26F22_REG_CTI_CTRL_0_T;
/*-----------------------------------------------------------------------------
							 0xc9018590L cti_ctrl_1 							
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cti_coring_th0					   :8 , // 7:0
	cti_coring_th1					   :8 , // 15:8
	cti_coring_smooth				   :3 , // 18:16
	reserved01						   :1 , // reserved
	reg_cti_tap2					   :2 ; // 21:20
}PE_O26F22_REG_CTI_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90187a0L reg_cti_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lti_en                         :1 ,	// 0 
	reg_lti_clipping_mode              :1 ,	// 1 
	reserved01                         :1 ,	// reserved
	reg_lti_tap                        :2 ,	// 4:3
	reserved02                         :3 ,	// reserved
	reg_lti_gain                       :8 ,	// 15:8
	reserved03                         :4 ,	// reserved
	reg_ycm_c_gain                     :4 ,	// 23:20
	reg_ycm_y_gain                     :4 ,	// 27:24
	reg_ycm_band_sel                   :3 ,	// 30:28
	reg_ycm_en                         :1 ;	// 31
}PE_O26F22_REG_CTI_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90187a4L reg_cti_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lti_coring_th0                 :8 ,	// 7:0
	reg_lti_coring_th1                 :8 ,	// 15:8
	reg_lti_coring_sm                  :3 ,	// 18:16
	reserved01                         :1 ,	// reserved
	reg_lti_tap2                       :2 ,	// 21:20
	reserved02                         :2 ,	// reserved
	reg_ycm_diff_th                    :8 ;	// 31:24
}PE_O26F22_REG_CTI_CTRL_3_T;
#if 0
/*-----------------------------------------------------------------------------
                             0xc900d550L shp_cti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cti_en                         :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_cti_filter_tap_size            :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	reg_cti_gain                       :8 ;	// 15:8
}PE_O26F22_SHP_CTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d554L shp_cti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cti_coring_th0                 :8 ,	// 7:0
	reg_cti_coring_th1                 :8 ,	// 15:8
	reg_cti_coring_map_filter          :3 ,	// 18:16
	reserved01                         :1 ,	// reserved
	reg_cti_coring_tap_size            :3 ,	// 22:20
	reserved02                         :1 ,	// reserved
	reg_cti_debug_mode                 :2 ;	// 25:24
}PE_O26F22_SHP_CTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d558L shp_cti_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cti_ycm_en                     :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_cti_ycm_band_sel               :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	reg_cti_ycm_diff_th                :8 ,	// 15:8
	reg_cti_ycm_y_gain                 :4 ,	// 19:16
	reg_cti_ycm_c_gain                 :4 ;	// 23:20
}PE_O26F22_SHP_CTI_CTRL_02_T;
#endif

typedef struct {
#ifdef PE_HW_O26_BRINGUP
	PE_O26_DNR0_CTI_CTRL_0_T                                    cti_ctrl_0;	//0xCCC6058C
	PE_O26_DNR0_CTI_CTRL_1_T                                    cti_ctrl_1;	//0xCCC60590
	PE_O26_DNR0_REG_CTI_CTRL_2_T                            reg_cti_ctrl_2;	//0xCCC607A0
	PE_O26_DNR0_REG_CTI_CTRL_3_T                            reg_cti_ctrl_3;	//0xCCC607A4
	PE_O26_VSD_SHP_CTI_CTRL_00_T                       shp_cti_ctrl_00;	//0xCCA22550
	PE_O26_VSD_SHP_CTI_CTRL_01_T                       shp_cti_ctrl_01;	//0xCCA22554
	PE_O26_VSD_SHP_CTI_CTRL_02_T                       shp_cti_ctrl_02;	//0xCCA22558
#endif
}PE_CTI_HW_PARAM_REG_O26_T;

/**
 *	cti_dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_O26_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_O26_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CTI_HW_PARAM_REG_O26_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CTI_HW_PARAM_REG_O26_T *data;
	} reg_data;
} PE_CTI_HW_PARAM_DATA_O26_T;


/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CTI_DNR_HW_PARAM_O26_H_ */
