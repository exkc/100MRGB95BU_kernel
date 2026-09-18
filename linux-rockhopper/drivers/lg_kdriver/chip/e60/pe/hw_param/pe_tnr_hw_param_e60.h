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

/** @file pe_tnr_hw_param_e60.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_TNR_HW_PARAM_E60_H_
#define	_PE_TNR_HW_PARAM_E60_H_

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
/**
 *	tnr hw param reg type
 */
typedef struct {
	PE_E60_ND0_TNR_CTRL_00_T            	tnr_ctrl_00;              //0xC9018140
	PE_E60_ND0_TNR_CTRL_01_T            	tnr_ctrl_01;              //0xC9018144
	PE_E60_ND0_TNR_CTRL_02_T            	tnr_ctrl_02;              //0xC9018148
	PE_E60_ND0_TNR_CTRL_03_T            	tnr_ctrl_03;              //0xC901814C
	PE_E60_ND0_TNR_CTRL_04_T            	tnr_ctrl_04;              //0xC9018150
	PE_E60_ND0_TNR_CTRL_05_T            	tnr_ctrl_05;              //0xC9018154
	PE_E60_ND0_TNR_CTRL_06_T            	tnr_ctrl_06;              //0xC9018158
	PE_E60_ND0_TNR_CTRL_07_T            	tnr_ctrl_07;              //0xC901815C
	PE_E60_ND0_TNR_CTRL_08_T            	tnr_ctrl_08;              //0xC9018160
	PE_E60_ND0_TNR_CTRL_09_T            	tnr_ctrl_09;              //0xC9018164
	PE_E60_ND0_TNR_CTRL_10_T            	tnr_ctrl_10;              //0xC9018168
	PE_E60_ND0_TNR_CTRL_11_T            	tnr_ctrl_11;              //0xC901816C
	PE_E60_ND0_TNR_CTRL_12_T                tnr_ctrl_12;              //0xC9018170
	PE_E60_ND0_TNR_CTRL_13_T                tnr_ctrl_13;              //0xC9018174
	PE_E60_ND0_TNR_CTRL_14_T                tnr_ctrl_14;              //0xC9018178
	PE_E60_ND0_TNR_CTRL_15_T                tnr_ctrl_15;              //0xC901817C
	PE_E60_ND0_TNR_CTRL_16_T            	tnr_ctrl_16;              //0xC9018180
	PE_E60_ND0_TNR_CTRL_17_T            	tnr_ctrl_17;              //0xC9018184
	PE_E60_ND0_TNR_CTRL_18_T            	tnr_ctrl_18;              //0xC9018188
	PE_E60_ND0_TNR_CTRL_19_T            	tnr_ctrl_19;              //0xC901818C
	PE_E60_ND0_TNR_CTRL_20_T            	tnr_ctrl_20;              //0xC9018190
	PE_E60_ND0_TNR_CTRL_21_T            	tnr_ctrl_21;              //0xC9018194
	PE_E60_ND0_TNR_CTRL_22_T                tnr_ctrl_22;              //0xC9018198
	PE_E60_ND0_TNR_CTRL_23_T                tnr_ctrl_23;              //0xC901819C
	PE_E60_ND0_TNR_CTRL_24_T            	tnr_ctrl_24;              //0xC90181A0
	PE_E60_ND0_TNR_CTRL_25_T            	tnr_ctrl_25;              //0xC90181A4
	PE_E60_ND0_TNR_CTRL_26_T            	tnr_ctrl_26;              //0xC90181A8
	PE_E60_ND0_TNR_CTRL_27_T            	tnr_ctrl_27;              //0xC90181AC
	PE_E60_ND0_TNR_CTRL_28_T            	tnr_ctrl_28;              //0xC90181B0
	PE_E60_ND0_TNR_CTRL_29_T            	tnr_ctrl_29;              //0xC90181B4
	PE_E60_ND0_TNR_CTRL_30_T            	tnr_ctrl_30;              //0xC90181B8
	PE_E60_ND0_TNR_CTRL_31_T            	tnr_ctrl_31;              //0xC90181BC
	PE_E60_ND0_TNR_CTRL_32_T            	tnr_ctrl_32;              //0xC90181E0
	PE_E60_ND0_TNR_CTRL_33_T            	tnr_ctrl_33;              //0xC90181E4
	PE_E60_ND0_TNR_CTRL_34_T                tnr_ctrl_34;              //0xC90181E8
	PE_E60_ND0_TNR_CTRL_35_T                tnr_ctrl_35;              //0xC90181EC
	PE_E60_ND0_TNR_CTRL_36_T                tnr_ctrl_36;              //0xC90181F0
	PE_E60_ND0_TNR_CTRL_37_T                tnr_ctrl_37;              //0xC90181F4
	PE_E60_ND0_TNR_CTRL_38_T                tnr_ctrl_38;              //0xC90181F8
	PE_E60_ND0_TNR_CTRL_39_T                tnr_ctrl_39;              //0xC90181FC
	PE_E60_ND0_MMD_CTRL_T                   mmd_ctrl;	              //0x01E0
	PE_E60_ND0_TNR_CTRL_40_T            	tnr_ctrl_40;              //0xC90183D0
	PE_E60_ND0_TNR_CTRL_41_T            	tnr_ctrl_41;              //0xC90183D4
	PE_E60_ND0_TNR_CTRL_42_T            	tnr_ctrl_42;              //0xC90183D8
	PE_E60_ND0_TNR_CTRL_43_T            	tnr_ctrl_43;              //0xC90183DC
	PE_E60_ND0_TNR_CTRL_44_T            	tnr_ctrl_44;              //0xC90183E0
	PE_E60_ND0_TNR_CTRL_45_T            	tnr_ctrl_45;              //0xC90183E4
	PE_E60_ND0_TNR_CTRL_46_T            	tnr_ctrl_46;              //0xC90183E8
	PE_E60_ND0_TNR_CTRL_47_T            	tnr_ctrl_47;              //0xC90183EC
	PE_E60_ND0_TNR_CTRL_48_T            	tnr_ctrl_48;              //0xC90183F0
	PE_E60_ND0_TNR_ETC_CTRL_02_T            tnr_etc_ctrl_02;          //0xC9018498
	PE_E60_ND0_TNR_CTRL_56_T            	tnr_ctrl_56;              //0xC90184A0
	PE_E60_ND0_TNR_CTRL_57_T            	tnr_ctrl_57;              //0xC90184A4
	PE_E60_ND0_TNR_CTRL_58_T            	tnr_ctrl_58;              //0xC90184A8
	PE_E60_ND0_TNR_CTRL_59_T            	tnr_ctrl_59;              //0xC90184AC
	PE_E60_ND0_TNR_CTRL_60_T            	tnr_ctrl_60;              //0xC90184B0
	PE_E60_ND0_TNR_CTRL_61_T            	tnr_ctrl_61;              //0xC90184B4

}PE_TNR_HW_PARAM_REG_E60_T;
/**
 *	tnr2nd hw param reg type
 */
typedef struct {
	PE_E60_ND0_TNR_CTRL_00_T            	tnr_ctrl_00;              //0xC901A140
	PE_E60_ND0_TNR_CTRL_01_T            	tnr_ctrl_01;              //0xC901A144
	PE_E60_ND0_TNR_CTRL_02_T            	tnr_ctrl_02;              //0xC901A148
	PE_E60_ND0_TNR_CTRL_03_T            	tnr_ctrl_03;              //0xC901A14C
	PE_E60_ND0_TNR_CTRL_04_T            	tnr_ctrl_04;              //0xC901A150
	PE_E60_ND0_TNR_CTRL_05_T            	tnr_ctrl_05;              //0xC901A154
	PE_E60_ND0_TNR_CTRL_06_T            	tnr_ctrl_06;              //0xC901A158
	PE_E60_ND0_TNR_CTRL_07_T            	tnr_ctrl_07;              //0xC901A15C
	PE_E60_ND0_TNR_CTRL_08_T            	tnr_ctrl_08;              //0xC901A160
	PE_E60_ND0_TNR_CTRL_09_T            	tnr_ctrl_09;              //0xC901A164
	PE_E60_ND0_TNR_CTRL_10_T            	tnr_ctrl_10;              //0xC901A168
	PE_E60_ND0_TNR_CTRL_11_T            	tnr_ctrl_11;              //0xC901A16C
	PE_E60_ND0_TNR_CTRL_12_T                tnr_ctrl_12;              //0xC901A170
	PE_E60_ND0_TNR_CTRL_13_T                tnr_ctrl_13;              //0xC901A174
	PE_E60_ND0_TNR_CTRL_14_T                tnr_ctrl_14;              //0xC901A178
	PE_E60_ND0_TNR_CTRL_15_T                tnr_ctrl_15;              //0xC901A17C
	PE_E60_ND0_TNR_CTRL_16_T            	tnr_ctrl_16;              //0xC901A180
	PE_E60_ND0_TNR_CTRL_17_T            	tnr_ctrl_17;              //0xC901A184
	PE_E60_ND0_TNR_CTRL_18_T            	tnr_ctrl_18;              //0xC901A188
	PE_E60_ND0_TNR_CTRL_19_T            	tnr_ctrl_19;              //0xC901A18C
	PE_E60_ND0_TNR_CTRL_20_T            	tnr_ctrl_20;              //0xC901A190
	PE_E60_ND0_TNR_CTRL_21_T            	tnr_ctrl_21;              //0xC901A194
	PE_E60_ND0_TNR_CTRL_22_T                tnr_ctrl_22;              //0xC901A198
	PE_E60_ND0_TNR_CTRL_23_T                tnr_ctrl_23;              //0xC901A19C
	PE_E60_ND0_TNR_CTRL_24_T            	tnr_ctrl_24;              //0xC901A1A0
	PE_E60_ND0_TNR_CTRL_25_T            	tnr_ctrl_25;              //0xC901A1A4
	PE_E60_ND0_TNR_CTRL_26_T            	tnr_ctrl_26;              //0xC901A1A8
	PE_E60_ND0_TNR_CTRL_27_T            	tnr_ctrl_27;              //0xC901A1AC
	PE_E60_ND0_TNR_CTRL_28_T            	tnr_ctrl_28;              //0xC901A1B0
	PE_E60_ND0_TNR_CTRL_29_T            	tnr_ctrl_29;              //0xC901A1B4
	PE_E60_ND0_TNR_CTRL_30_T            	tnr_ctrl_30;              //0xC901A1B8
	PE_E60_ND0_TNR_CTRL_31_T            	tnr_ctrl_31;              //0xC901A1BC
	PE_E60_ND0_TNR_CTRL_32_T            	tnr_ctrl_32;              //0xC901A1E0
	PE_E60_ND0_TNR_CTRL_33_T            	tnr_ctrl_33;              //0xC901A1E4
	PE_E60_ND0_TNR_CTRL_34_T                tnr_ctrl_34;              //0xC901A1E8
	PE_E60_ND0_TNR_CTRL_35_T                tnr_ctrl_35;              //0xC901A1EC
	PE_E60_ND0_TNR_CTRL_36_T                tnr_ctrl_36;              //0xC901A1F0
	PE_E60_ND0_TNR_CTRL_37_T                tnr_ctrl_37;              //0xC901A1F4
	PE_E60_ND0_TNR_CTRL_38_T                tnr_ctrl_38;              //0xC901A1F8
	PE_E60_ND0_TNR_CTRL_39_T                tnr_ctrl_39;              //0xC901A1FC
	PE_E60_ND0_TNR_CTRL_40_T            	tnr_ctrl_40;              //0xC901A3D0
	PE_E60_ND0_TNR_CTRL_41_T            	tnr_ctrl_41;              //0xC901A3D4
	PE_E60_ND0_TNR_CTRL_42_T            	tnr_ctrl_42;              //0xC901A3D8
	PE_E60_ND0_TNR_CTRL_43_T            	tnr_ctrl_43;              //0xC901A3DC
	PE_E60_ND0_TNR_CTRL_44_T            	tnr_ctrl_44;              //0xC901A3E0
	PE_E60_ND0_TNR_CTRL_45_T            	tnr_ctrl_45;              //0xC901A3E4
	PE_E60_ND0_TNR_CTRL_46_T            	tnr_ctrl_46;              //0xC901A3E8
	PE_E60_ND0_TNR_CTRL_47_T            	tnr_ctrl_47;              //0xC901A3EC
	PE_E60_ND0_TNR_CTRL_48_T            	tnr_ctrl_48;              //0xC901A3F0
	PE_E60_ND0_TNR_ETC_CTRL_02_T            tnr_etc_ctrl_02;          //0xC901A498
	PE_E60_ND0_TNR_CTRL_56_T            	tnr_ctrl_56;              //0xC901A4A0
	PE_E60_ND0_TNR_CTRL_57_T            	tnr_ctrl_57;              //0xC901A4A4
	PE_E60_ND0_TNR_CTRL_58_T            	tnr_ctrl_58;              //0xC901A4A8
	PE_E60_ND0_TNR_CTRL_59_T            	tnr_ctrl_59;              //0xC901A4AC
	PE_E60_ND0_TNR_CTRL_60_T            	tnr_ctrl_60;              //0xC901A4B0
	PE_E60_ND0_TNR_CTRL_61_T            	tnr_ctrl_61;              //0xC901A4B4
}PE_TNR2ND_HW_PARAM_REG_E60_T;


/**
 *	tnr hw param reg type
 */
typedef struct {
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_00;          //0xC900E1DC 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_01;          //0xC900E1DC 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_02;          //0xC900E1DC 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_03;          //0xC900E1DC 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_04;          //0xC900E1DC 04. x5y5 x4y4 reg_p2_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_05;          //0xC900E1DC 05. x3y3 x2y2 reg_p2_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_06;          //0xC900E1DC 06. x1y1 x0y0 reg_p2_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_07;          //0xC900E1DC 07. x7y7 x6y6 reg_detail_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_08;          //0xC900E1DC 08. x5y5 x4y4 reg_detail_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_09;          //0xC900E1DC 09. x3y3 x2y2 reg_detail_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_10;          //0xC900E1DC 10. x1y1 x0y0 reg_detail_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_11;          //0xC900E1DC 11. x7y7 x6y6 reg_detail_cir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_12;          //0xC900E1DC 12. x5y5 x4y4 reg_detail_cir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_13;          //0xC900E1DC 13. x3y3 x2y2 reg_detail_cir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_14;          //0xC900E1DC 14. x1y1 x0y0 reg_detail_cir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_15;          //0xC900E1DC 15. x7y7 x6y6 reg_flat_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_16;          //0xC900E1DC 16. x5y5 x4y4 reg_flat_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_17;          //0xC900E1DC 17. x3y3 x2y2 reg_flat_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_18;          //0xC900E1DC 18. x1y1 x0y0 reg_flat_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_19;          //0xC900E1DC 19. x7y7 x6y6 reg_flat_cir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_20;          //0xC900E1DC 20. x5y5 x4y4 reg_flat_cir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_21;          //0xC900E1DC 21. x3y3 x2y2 reg_flat_cir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_22;          //0xC900E1DC 22. x1y1 x0y0 reg_flat_cir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_23;          //0xC900E1DC 23. x1y1 x0y0 reg_luma_gain_ctrl
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_24;          //0xC900E1DC 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_25;          //0xC900E1DC 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_26;          //0xC900E1DC 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_27;          //0xC900E1DC 27. x1y1 x0y0 reg_skin_motion_ctrl
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_28;          //0xC900E1DC 28. reg_detail_luma_ctrl
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_29;          //0xC900E1DC 29. x3y3 x2y2 reg_NLM_Protect
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_30;          //0xC900E1DC 30. x1y1 x0y0 reg_NLM_Protect
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_31;          //0xC900E1DC 31. x5y5 x4y4 reg_cc_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_32;          //0xC900E1DC 32. x3y3 x2y2 reg_cc_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_33;          //0xC900E1DC 33. x1y1 x0y0 reg_cc_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_34;          //0xC900E1DC 34. x5y5 x4y4 reg_ne_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_35;          //0xC900E1DC 35. x3y3 x2y2 reg_ne_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_36;          //0xC900E1DC 36. x1y1 x0y0 reg_ne_dist_max_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_37;          //0xC900E1DC 37. reg_skin_gain_ctrl_yy
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_38;          //0xC900E1DC 38. reg_skin_gain_ctrl_cb
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_39;          //0xC900E1DC 39. reg_skin_gain_ctrl_cr
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_40;          //0xC900E1DC 40. reg_skin_motion_ctrl
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_41;          //0xC900E1DC 39. x7y7 x6y6 reg_simple_ma_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_42;          //0xC900E1DC 40. x5y5 x4y4 reg_simple_ma_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_43;          //0xC900E1DC 41. x3y3 x2y2 reg_simple_ma_iir_pt
	PE_E60_ND0_TNR_MAIN_LUT_01_T        	tnr_lut_44;          //0xC900E1DC 42. x1y1 x0y0 reg_simple_ma_iir_pt
}PE_TNL_HW_PARAM_REG_E60_T;


/**
 *	tnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_TNR_HW_PARAM_REG_E60_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_TNR_HW_PARAM_REG_E60_T *data;
	} nd1_user;

	union {
		UINT32			*addr;
		PE_TNR_HW_PARAM_REG_E60_T *data;
	} nd1_mask;

	union {
		UINT32			 *addr;
		PE_TNR_HW_PARAM_REG_E60_T *data;
	} nd1_data;
} PE_TNR_HW_PARAM_DATA_E60_T;

/**
 *	tnr2nd hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_TNR2ND_HW_PARAM_REG_E60_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_TNR2ND_HW_PARAM_REG_E60_T *data;
	} nd1_user;

	union {
		UINT32			*addr;
		PE_TNR2ND_HW_PARAM_REG_E60_T *data;
	} nd1_mask;

	union {
		UINT32			 *addr;
		PE_TNR2ND_HW_PARAM_REG_E60_T *data;
	} nd1_data;
} PE_TNR2ND_HW_PARAM_DATA_E60_T;


/**
 *	tnr lut (tnl) hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_TNL_HW_PARAM_REG_E60_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_TNL_HW_PARAM_REG_E60_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_TNL_HW_PARAM_REG_E60_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_TNL_HW_PARAM_REG_E60_T *data;
	} reg_data;
} PE_TNL_HW_PARAM_DATA_E60_T;

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_TNR_HW_PARAM_M16p_H_ */
