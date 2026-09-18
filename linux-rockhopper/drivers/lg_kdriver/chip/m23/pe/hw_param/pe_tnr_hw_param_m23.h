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

/** @file pe_tnr_hw_param_m23.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_TNR_HW_PARAM_M23_H_
#define	_PE_TNR_HW_PARAM_M23_H_

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
	PE_M23_TNR_CTRL_00_T            	tnr_ctrl_00;              //0xCC800140
	PE_M23_TNR_CTRL_01_T            	tnr_ctrl_01;              //0xCC800144
	PE_M23_TNR_CTRL_02_T            	tnr_ctrl_02;              //0xCC800148
	PE_M23_TNR_CTRL_03_T            	tnr_ctrl_03;              //0xCC80014C
	PE_M23_TNR_CTRL_04_T            	tnr_ctrl_04;              //0xCC800150
	PE_M23_TNR_CTRL_05_T            	tnr_ctrl_05;              //0xCC800154
	PE_M23_TNR_CTRL_06_T            	tnr_ctrl_06;              //0xCC800158
	PE_M23_TNR_CTRL_07_T            	tnr_ctrl_07;              //0xCC80015C
	PE_M23_TNR_CTRL_08_T            	tnr_ctrl_08;              //0xCC800160
	PE_M23_TNR_CTRL_09_T            	tnr_ctrl_09;              //0xCC800164
	PE_M23_TNR_CTRL_10_T            	tnr_ctrl_10;              //0xCC800168
	PE_M23_TNR_CTRL_11_T            	tnr_ctrl_11;              //0xCC80016C
	PE_M23_TNR_CTRL_12_T                tnr_ctrl_12;              //0xCC800170
	PE_M23_TNR_CTRL_13_T                tnr_ctrl_13;              //0xCC800174
	PE_M23_TNR_CTRL_14_T                tnr_ctrl_14;              //0xCC800178
	PE_M23_TNR_CTRL_15_T                tnr_ctrl_15;              //0xCC80017C
	PE_M23_TNR_CTRL_16_T            	tnr_ctrl_16;              //0xCC800180
	PE_M23_TNR_CTRL_17_T            	tnr_ctrl_17;              //0xCC800184
	PE_M23_TNR_CTRL_18_T            	tnr_ctrl_18;              //0xCC800188
	PE_M23_TNR_CTRL_19_T            	tnr_ctrl_19;              //0xCC80018C
	PE_M23_TNR_CTRL_20_T            	tnr_ctrl_20;              //0xCC800190
	PE_M23_TNR_CTRL_21_T            	tnr_ctrl_21;              //0xCC800194
	PE_M23_TNR_CTRL_22_T                tnr_ctrl_22;              //0xCC800198
	PE_M23_TNR_CTRL_23_T                tnr_ctrl_23;              //0xCC80019C
	PE_M23_TNR_CTRL_24_T            	tnr_ctrl_24;              //0xCC8001A0
	PE_M23_TNR_CTRL_25_T            	tnr_ctrl_25;              //0xCC8001A4
	PE_M23_TNR_CTRL_26_T            	tnr_ctrl_26;              //0xCC8001A8
	PE_M23_TNR_CTRL_27_T            	tnr_ctrl_27;              //0xCC8001AC
	PE_M23_TNR_CTRL_28_T            	tnr_ctrl_28;              //0xCC8001B0
	PE_M23_TNR_CTRL_29_T            	tnr_ctrl_29;              //0xCC8001B4
	PE_M23_TNR_CTRL_30_T            	tnr_ctrl_30;              //0xCC8001B8
	PE_M23_TNR_CTRL_31_T            	tnr_ctrl_31;              //0xCC8001BC
	PE_M23_TNR_CTRL_32_T            	tnr_ctrl_32;              //0xCC8001E0
	PE_M23_TNR_CTRL_33_T            	tnr_ctrl_33;              //0xCC8001E4
	PE_M23_TNR_CTRL_34_T                tnr_ctrl_34;              //0xCC8001E8
	PE_M23_TNR_CTRL_35_T                tnr_ctrl_35;              //0xCC8001EC
	PE_M23_TNR_CTRL_36_T                tnr_ctrl_36;              //0xCC8001F0
	PE_M23_TNR_CTRL_37_T                tnr_ctrl_37;              //0xCC8001F4
	PE_M23_TNR_CTRL_38_T                tnr_ctrl_38;              //0xCC8001F8
	PE_M23_TNR_CTRL_39_T                tnr_ctrl_39;              //0xCC8001FC
	PE_M23_MMD_CTRL_T                   mmd_ctrl;	              //0xCC8002E0
	PE_M23_TNR_CTRL_40_T            	tnr_ctrl_40;              //0xCC8003D0
	PE_M23_TNR_CTRL_41_T            	tnr_ctrl_41;              //0xCC8003D4
	PE_M23_TNR_CTRL_42_T            	tnr_ctrl_42;              //0xCC8003D8
	PE_M23_TNR_CTRL_43_T            	tnr_ctrl_43;              //0xCC8003DC
	PE_M23_TNR_CTRL_44_T            	tnr_ctrl_44;              //0xCC8003E0
	PE_M23_TNR_CTRL_45_T            	tnr_ctrl_45;              //0xCC8003E4
	PE_M23_TNR_CTRL_46_T            	tnr_ctrl_46;              //0xCC8003E8
	PE_M23_TNR_CTRL_47_T            	tnr_ctrl_47;              //0xCC8003EC
	PE_M23_TNR_CTRL_48_T            	tnr_ctrl_48;              //0xCC8003F0
	PE_M23_TNR_ETC_CTRL_02_T            tnr_etc_ctrl_02;          //0xCC800498
	PE_M23_TNR_CTRL_56_T                tnr_ctrl_56;              //0xCC8004A0
	PE_M23_TNR_CTRL_57_T                tnr_ctrl_57;              //0xCC8004A4
	PE_M23_TNR_CTRL_58_T                tnr_ctrl_58;              //0xCC8004A8
	PE_M23_TNR_CTRL_59_T                tnr_ctrl_59;              //0xCC8004AC
	PE_M23_TNR_CTRL_60_T                tnr_ctrl_60;              //0xCC8004B0
	PE_M23_TNR_CTRL_61_T                tnr_ctrl_61;              //0xCC8004B4

}PE_TNR_HW_PARAM_REG_M23_T;

/**
 *	tnr2nd hw param reg type
 */
typedef struct {
	PE_M23_TNR_CTRL_00_T            	tnr_ctrl_00;              //0xCC800140
	PE_M23_TNR_CTRL_01_T            	tnr_ctrl_01;              //0xCC800144
	PE_M23_TNR_CTRL_02_T            	tnr_ctrl_02;              //0xCC800148
	PE_M23_TNR_CTRL_03_T            	tnr_ctrl_03;              //0xCC80014C
	PE_M23_TNR_CTRL_04_T            	tnr_ctrl_04;              //0xCC800150
	PE_M23_TNR_CTRL_05_T            	tnr_ctrl_05;              //0xCC800154
	PE_M23_TNR_CTRL_06_T            	tnr_ctrl_06;              //0xCC800158
	PE_M23_TNR_CTRL_07_T            	tnr_ctrl_07;              //0xCC80015C
	PE_M23_TNR_CTRL_08_T            	tnr_ctrl_08;              //0xCC800160
	PE_M23_TNR_CTRL_09_T            	tnr_ctrl_09;              //0xCC800164
	PE_M23_TNR_CTRL_10_T            	tnr_ctrl_10;              //0xCC800168
	PE_M23_TNR_CTRL_11_T            	tnr_ctrl_11;              //0xCC80016C
	PE_M23_TNR_CTRL_12_T                tnr_ctrl_12;              //0xCC800170
	PE_M23_TNR_CTRL_13_T                tnr_ctrl_13;              //0xCC800174
	PE_M23_TNR_CTRL_14_T                tnr_ctrl_14;              //0xCC800178
	PE_M23_TNR_CTRL_15_T                tnr_ctrl_15;              //0xCC80017C
	PE_M23_TNR_CTRL_16_T            	tnr_ctrl_16;              //0xCC800180
	PE_M23_TNR_CTRL_17_T            	tnr_ctrl_17;              //0xCC800184
	PE_M23_TNR_CTRL_18_T            	tnr_ctrl_18;              //0xCC800188
	PE_M23_TNR_CTRL_19_T            	tnr_ctrl_19;              //0xCC80018C
	PE_M23_TNR_CTRL_20_T            	tnr_ctrl_20;              //0xCC800190
	PE_M23_TNR_CTRL_21_T            	tnr_ctrl_21;              //0xCC800194
	PE_M23_TNR_CTRL_22_T                tnr_ctrl_22;              //0xCC800198
	PE_M23_TNR_CTRL_23_T                tnr_ctrl_23;              //0xCC80019C
	PE_M23_TNR_CTRL_24_T            	tnr_ctrl_24;              //0xCC8001A0
	PE_M23_TNR_CTRL_25_T            	tnr_ctrl_25;              //0xCC8001A4
	PE_M23_TNR_CTRL_26_T            	tnr_ctrl_26;              //0xCC8001A8
	PE_M23_TNR_CTRL_27_T            	tnr_ctrl_27;              //0xCC8001AC
	PE_M23_TNR_CTRL_28_T            	tnr_ctrl_28;              //0xCC8001B0
	PE_M23_TNR_CTRL_29_T            	tnr_ctrl_29;              //0xCC8001B4
	PE_M23_TNR_CTRL_30_T            	tnr_ctrl_30;              //0xCC8001B8
	PE_M23_TNR_CTRL_31_T            	tnr_ctrl_31;              //0xCC8001BC
	PE_M23_TNR_CTRL_32_T            	tnr_ctrl_32;              //0xCC8001E0
	PE_M23_TNR_CTRL_33_T            	tnr_ctrl_33;              //0xCC8001E4
	PE_M23_TNR_CTRL_34_T                tnr_ctrl_34;              //0xCC8001E8
	PE_M23_TNR_CTRL_35_T                tnr_ctrl_35;              //0xCC8001EC
	PE_M23_TNR_CTRL_36_T                tnr_ctrl_36;              //0xCC8001F0
	PE_M23_TNR_CTRL_37_T                tnr_ctrl_37;              //0xCC8001F4
	PE_M23_TNR_CTRL_38_T                tnr_ctrl_38;              //0xCC8001F8
	PE_M23_TNR_CTRL_39_T                tnr_ctrl_39;              //0xCC8001FC
	PE_M23_TNR_CTRL_40_T            	tnr_ctrl_40;              //0xCC8003D0
	PE_M23_TNR_CTRL_41_T            	tnr_ctrl_41;              //0xCC8003D4
	PE_M23_TNR_CTRL_42_T            	tnr_ctrl_42;              //0xCC8003D8
	PE_M23_TNR_CTRL_43_T            	tnr_ctrl_43;              //0xCC8003DC
	PE_M23_TNR_CTRL_44_T            	tnr_ctrl_44;              //0xCC8003E0
	PE_M23_TNR_CTRL_45_T            	tnr_ctrl_45;              //0xCC8003E4
	PE_M23_TNR_CTRL_46_T            	tnr_ctrl_46;              //0xCC8003E8
	PE_M23_TNR_CTRL_47_T            	tnr_ctrl_47;              //0xCC8003EC
	PE_M23_TNR_CTRL_48_T            	tnr_ctrl_48;              //0xCC8003F0
	PE_M23_TNR_ETC_CTRL_02_T            tnr_etc_ctrl_02;          //0xCC800498
	PE_M23_TNR_CTRL_56_T                tnr_ctrl_56;              //0xCC8004A0
	PE_M23_TNR_CTRL_57_T                tnr_ctrl_57;              //0xCC8004A4
	PE_M23_TNR_CTRL_58_T                tnr_ctrl_58;              //0xCC8004A8
	PE_M23_TNR_CTRL_59_T                tnr_ctrl_59;              //0xCC8004AC
	PE_M23_TNR_CTRL_60_T                tnr_ctrl_60;              //0xCC8004B0
	PE_M23_TNR_CTRL_61_T                tnr_ctrl_61;              //0xCC8004B4
}PE_TNR2ND_HW_PARAM_REG_M23_T;


/**
 *	tnr hw param reg type
 */
typedef struct {
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_00;          //0xCC8001D4 00. x7y7 x6y6 reg_p2_blend_ctrl_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_01;          //0xCC8001D4 01. x5y5 x4y4 reg_p2_blend_ctrl_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_02;          //0xCC8001D4 02. x3y3 x2y2 reg_p2_blend_ctrl_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_03;          //0xCC8001D4 03. x1y1 x0y0 reg_p2_blend_ctrl_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_04;          //0xCC8001D4 04. x5y5 x4y4 reg_p2_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_05;          //0xCC8001D4 05. x3y3 x2y2 reg_p2_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_06;          //0xCC8001D4 06. x1y1 x0y0 reg_p2_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_07;          //0xCC8001D4 07. x7y7 x6y6 reg_detail_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_08;          //0xCC8001D4 08. x5y5 x4y4 reg_detail_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_09;          //0xCC8001D4 09. x3y3 x2y2 reg_detail_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_10;          //0xCC8001D4 10. x1y1 x0y0 reg_detail_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_11;          //0xCC8001D4 11. x7y7 x6y6 reg_detail_cir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_12;          //0xCC8001D4 12. x5y5 x4y4 reg_detail_cir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_13;          //0xCC8001D4 13. x3y3 x2y2 reg_detail_cir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_14;          //0xCC8001D4 14. x1y1 x0y0 reg_detail_cir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_15;          //0xCC8001D4 15. x7y7 x6y6 reg_flat_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_16;          //0xCC8001D4 16. x5y5 x4y4 reg_flat_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_17;          //0xCC8001D4 17. x3y3 x2y2 reg_flat_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_18;          //0xCC8001D4 18. x1y1 x0y0 reg_flat_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_19;          //0xCC8001D4 19. x7y7 x6y6 reg_flat_cir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_20;          //0xCC8001D4 20. x5y5 x4y4 reg_flat_cir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_21;          //0xCC8001D4 21. x3y3 x2y2 reg_flat_cir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_22;          //0xCC8001D4 22. x1y1 x0y0 reg_flat_cir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_23;          //0xCC8001D4 23. x1y1 x0y0 reg_luma_gain_ctrl
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_24;          //0xCC8001D4 24. x3x2 x1x0 reg_skin_gain_ctrl_yy
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_25;          //0xCC8001D4 25. x3x2 x1x0 reg_skin_gain_ctrl_cb
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_26;          //0xCC8001D4 26. x3x2 x1x0 reg_skin_gain_ctrl_cr
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_27;          //0xCC8001D4 27. x1y1 x0y0 reg_skin_motion_ctrl
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_28;          //0xCC8001D4 28. reg_detail_luma_ctrl
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_29;          //0xCC8001D4 29. x3y3 x2y2 reg_NLM_Protect
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_30;          //0xCC8001D4 30. x1y1 x0y0 reg_NLM_Protect
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_31;          //0xCC8001D4 31. x5y5 x4y4 reg_cc_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_32;          //0xCC8001D4 32. x3y3 x2y2 reg_cc_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_33;          //0xCC8001D4 33. x1y1 x0y0 reg_cc_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_34;          //0xCC8001D4 34. x5y5 x4y4 reg_ne_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_35;          //0xCC8001D4 35. x3y3 x2y2 reg_ne_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_36;          //0xCC8001D4 36. x1y1 x0y0 reg_ne_dist_max_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_37;          //0xCC8001D4 37. reg_skin_gain_ctrl_yy
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_38;          //0xCC8001D4 38. reg_skin_gain_ctrl_cb
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_39;          //0xCC8001D4 39. reg_skin_gain_ctrl_cr
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_40;          //0xCC8001D4 40. reg_skin_motion_ctrl
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_41;          //0xCC8001D4 41. x7y7 x6y6 reg_simple_ma_iir_pt
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_42;          //0xCC8001D4 42. 
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_43;          //0xCC8001D4 43. 
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_44;          //0xCC8001D4 44. 
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_45;          //0xCC8001D4 45. 
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_46;          //0xCC8001D4 46. 
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_47;          //0xCC8001D4 47. 
	PE_M23_TNR_MAIN_LUT_01_T        	tnr_lut_48;          //0xCC8001D4 48. 
}PE_TNL_HW_PARAM_REG_M23_T;


/**
 *	tnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_TNR_HW_PARAM_REG_M23_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_TNR_HW_PARAM_REG_M23_T *data;
	} nd1_user;

	union {
		UINT32			*addr;
		PE_TNR_HW_PARAM_REG_M23_T *data;
	} nd1_mask;

	union {
		UINT32			 *addr;
		PE_TNR_HW_PARAM_REG_M23_T *data;
	} nd1_data;
} PE_TNR_HW_PARAM_DATA_M23_T;

/**
 *	tnr2nd hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_TNR2ND_HW_PARAM_REG_M23_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_TNR2ND_HW_PARAM_REG_M23_T *data;
	} nd1_user;

	union {
		UINT32			*addr;
		PE_TNR2ND_HW_PARAM_REG_M23_T *data;
	} nd1_mask;

	union {
		UINT32			 *addr;
		PE_TNR2ND_HW_PARAM_REG_M23_T *data;
	} nd1_data;
} PE_TNR2ND_HW_PARAM_DATA_M23_T;


/**
 *	tnr lut (tnl) hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_TNL_HW_PARAM_REG_M23_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_TNL_HW_PARAM_REG_M23_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_TNL_HW_PARAM_REG_M23_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_TNL_HW_PARAM_REG_M23_T *data;
	} reg_data;
} PE_TNL_HW_PARAM_DATA_M23_T;

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
