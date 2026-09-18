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
 *  measure hardware format detection 
 *	
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.07.10
 *  note		Additional information.
 *
 *  @addtogroup APR
 *	@{
 */

#ifndef _APR_HFD_H_
#define _APR_HFD_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */
	
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*refactored code*/
typedef struct
{
	int corr_th;
	int third_cor_th;
	int final_corr_th; 
	int mean_tolerance_th;
	int var_th;
	int var_valid_blk;
	int candi_blk_thaw;
	int cross_corr_en;
	int cross_corr_th0;
	int cross_corr_th1;
	int dom_seg_chk_en;
	int dom_seg_chk_th0;
	int dom_seg_chk_th1;
	int blk_mean_chk_en;
}APR_IMG_CLASS_VAR_T;


typedef struct
{
	int cnt_ss ;
	int cnt_tb ;
	int cnt1_ss ;
	int cnt1_tb ;
	int cnt2_ss ;
	int cnt2_tb ;
	int cnt_idx;
	int sum_ss;
	int sum_tb;
	int final_corr;
	int change_segment;
	
}APR_BASIC_ALGOPARAM_T;



/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int APR_FD3_Detect3D(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _APR_HFD_H_ */

/** @} */






