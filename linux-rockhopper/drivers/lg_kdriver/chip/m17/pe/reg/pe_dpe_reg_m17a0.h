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

#ifndef _PE_DPE_REG_M17A0_H_
#define _PE_DPE_REG_M17A0_H_

/*-----------------------------------------------------------------------------
		0xc8020540L ad_rp_hv_pos ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rp_v_pos                           : 12;  // 11: 0     
	UINT32                                    : 4 ;  // 15:12     reserved
	UINT32 rp_h_pos                           : 12;  // 27:16     
} PE_LED_M17_AD_RP_HV_POS_T;

/*-----------------------------------------------------------------------------
		0xc8020544L ad_rp_make_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mark_en                            : 1 ;  //     0     
} PE_LED_M17_AD_RP_MAKE_EN_T;

/*-----------------------------------------------------------------------------
		0xc8020548L ad_rp_r_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_r                         : 14;  // 13: 0     
} PE_LED_M17_AD_RP_R_VALUE_T;

/*-----------------------------------------------------------------------------
		0xc802054cL ad_rp_g_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_g                         : 14;  // 13: 0     
} PE_LED_M17_AD_RP_G_VALUE_T;

/*-----------------------------------------------------------------------------
		0xc8020550L ad_rp_b_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_b                         : 14;  // 13: 0     
} PE_LED_M17_AD_RP_B_VALUE_T;

typedef struct {
	PE_LED_M17_AD_RP_HV_POS_T            	ad_rp_hv_pos;                 //0xc8020540L
	PE_LED_M17_AD_RP_MAKE_EN_T           	ad_rp_make_en;                //0xc8020544L
	PE_LED_M17_AD_RP_R_VALUE_T           	ad_rp_r_value;                //0xc8020548L
	PE_LED_M17_AD_RP_G_VALUE_T           	ad_rp_g_value;                //0xc802054cL
	PE_LED_M17_AD_RP_B_VALUE_T           	ad_rp_b_value;                //0xc8020550L
}PE_LED_RP_REG_M17_T;
#endif

