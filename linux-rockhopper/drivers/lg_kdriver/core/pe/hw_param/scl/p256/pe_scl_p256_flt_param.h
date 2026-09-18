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

/** @file pe_scl_p256_flt_param.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2015.04.23
 *	@see		
 */

#ifndef	_PE_SCL_P256_FLT_PARAM_H_
#define	_PE_SCL_P256_FLT_PARAM_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"

#include "pe_scl_p256_12t_m_flt_0002.h"
#include "pe_scl_p256_12t_m_flt_0003.h"
#include "pe_scl_p256_12t_m_flt_0004.h"
#include "pe_scl_p256_12t_m_flt_0006.h"
#include "pe_scl_p256_12t_m_flt_0110.h"
#include "pe_scl_p256_12t_m_flt_0204.h"
#include "pe_scl_p256_12t_m_flt_0202.h"
#include "pe_scl_p256_12t_m_flt_0304.h"
#include "pe_scl_p256_12t_m_flt_0306.h"
#include "pe_scl_p256_12t_m_flt_0404.h"
#include "pe_scl_p256_12t_m_flt_0406.h"
#include "pe_scl_p256_12t_m_flt_0606.h"
#include "pe_scl_p256_12t_m_flt_0806.h"
#include "pe_scl_p256_12t_m_flt_1006.h"
#include "pe_scl_p256_12t_m_flt_1410.h"
#include "pe_scl_p256_12t_m_flt_0104.h"
#include "pe_scl_p256_12t_m_flt_1010.h"

//#include "pe_scl_p256_12t_s_flt_0508.h"
//#include "pe_scl_p256_12t_s_flt_0610.h"
//#include "pe_scl_p256_12t_s_flt_0708.h"
//#include "pe_scl_p256_12t_s_flt_1210.h"

#include "pe_scl_p256_04t_m_flt_0007.h"
#include "pe_scl_p256_04t_m_flt_0107.h"
#include "pe_scl_p256_04t_m_flt_0307.h"
#include "pe_scl_p256_04t_m_flt_0607.h"
#include "pe_scl_p256_04t_m_flt_0807.h"
#include "pe_scl_p256_04t_m_flt_1007.h"
#include "pe_scl_p256_04t_m_flt_1407.h"
#include "pe_scl_p256_04t_m_flt_1410.h"
#include "pe_scl_p256_04t_m_flt_1514.h"
#include "pe_scl_p256_04t_m_flt_1515.h"

//#include "pe_scl_p256_08t_m_flt_0006.h"
//#include "pe_scl_p256_08t_m_flt_0106.h"
//#include "pe_scl_p256_08t_m_flt_0306.h"
//#include "pe_scl_p256_08t_m_flt_0606.h"
//#include "pe_scl_p256_08t_m_flt_0806.h"
//#include "pe_scl_p256_08t_m_flt_1006.h"
//#include "pe_scl_p256_08t_m_flt_1406.h"
//#include "pe_scl_p256_08t_m_flt_1410.h"
//#include "pe_scl_p256_08t_m_flt_1514.h"
//#include "pe_scl_p256_08t_m_flt_1515.h"

#include "pe_scl_p256_12t_h_flt_0006.h"
#include "pe_scl_p256_12t_h_flt_0306.h"
#include "pe_scl_p256_08t_f_flt_0006.h"
#include "pe_scl_p256_08t_f_flt_0306.h"
#include "pe_scl_p256_08t_f_flt_0606.h"
#include "pe_scl_p256_08t_f_flt_0610.h"
#include "pe_scl_p256_08t_f_flt_0806.h"
#include "pe_scl_p256_08t_f_flt_1006.h"
#include "pe_scl_p256_08t_f_flt_1210.h"
#include "pe_scl_p256_08t_f_flt_1406.h"
#include "pe_scl_p256_08t_f_flt_1410.h"
#include "pe_scl_p256_08t_f_flt_1514.h"
#include "pe_scl_p256_08t_f_flt_1515.h"
#include "pe_scl_p256_08t_h_flt_0006.h"
#include "pe_scl_p256_08t_h_flt_0306.h"
#include "pe_scl_p256_08t_h_flt_0008.h"
#include "pe_scl_p256_04t_f_flt_0006.h"
#include "pe_scl_p256_04t_f_flt_0306.h"
#include "pe_scl_p256_04t_f_flt_0606.h"
#include "pe_scl_p256_04t_f_flt_0806.h"
#include "pe_scl_p256_04t_f_flt_1006.h"
#include "pe_scl_p256_04t_f_flt_1406.h"
#include "pe_scl_p256_04t_f_flt_1410.h"
#include "pe_scl_p256_04t_f_flt_1514.h"
#include "pe_scl_p256_04t_f_flt_1515.h"
#include "pe_scl_p256_04t_h_flt_0006.h"
#include "pe_scl_p256_04t_h_flt_0306.h"
#include "pe_scl_p256_04t_h_flt_0308.h"

#include "pe_scl_p256_12t_02t_flt_0006.h"
#include "pe_scl_p256_12t_02t_flt_1510.h"
#include "pe_scl_p256_12t_04t_flt_0006.h"
#include "pe_scl_p256_12t_04t_flt_0406.h"
#include "pe_scl_p256_12t_04t_flt_0606.h"
#include "pe_scl_p256_12t_04t_flt_0808.h"
#include "pe_scl_p256_12t_06t_flt_1510.h"
#include "pe_scl_p256_12t_06t_flt_0610.h"
#include "pe_scl_p256_12t_12t_flt_0006.h"
#include "pe_scl_p256_12t_12t_flt_0104.h"
#include "pe_scl_p256_12t_12t_flt_0306.h"
#include "pe_scl_p256_12t_12t_flt_0406.h"
#include "pe_scl_p256_12t_12t_flt_0606.h"
#include "pe_scl_p256_12t_12t_flt_0808.h"
#include "pe_scl_p256_12t_12t_flt_1006.h"
#include "pe_scl_p256_12t_12t_flt_1410.h"


#include "pe_scl_p256_12t_12t_flt_0004.h"
#include "pe_scl_p256_12t_12t_flt_0304.h"
#include "pe_scl_p256_12t_12t_flt_0404.h"
#include "pe_scl_p256_12t_12t_flt_0806.h"
#include "pe_scl_p256_12t_08t_flt_0004.h"
#include "pe_scl_p256_12t_08t_flt_0006.h"
#include "pe_scl_p256_12t_08t_flt_0104.h"
#include "pe_scl_p256_12t_08t_flt_0304.h"
#include "pe_scl_p256_12t_08t_flt_0306.h"
#include "pe_scl_p256_12t_08t_flt_0606.h"
#include "pe_scl_p256_12t_08t_flt_0806.h"
#include "pe_scl_p256_12t_08t_flt_1410.h"
#include "pe_scl_p256_12t_06t_flt_0306.h"
#include "pe_scl_p256_12t_06t_flt_0006.h"
#include "pe_scl_p256_12t_04t_flt_0308.h"
#include "pe_scl_p256_12t_04t_flt_0008.h"
#include "pe_scl_p256_12t_04t_flt_0910.h"
#include "pe_scl_p256_12t_04t_flt_1410.h"
#include "pe_scl_p256_12t_04t_flt_1510.h"
#include "pe_scl_p256_12t_04t_flt_0306.h"
#include "pe_scl_p256_12t_04t_flt_0610.h"
#include "pe_scl_p256_12t_04t_flt_repeat.h"
#include "pe_scl_p256_12t_02t_flt_0308.h"

#include "pe_scl_p256_08t_08t_flt_0004.h"
#include "pe_scl_p256_08t_08t_flt_0606.h"
#include "pe_scl_p256_08t_08t_flt_0610.h"
#include "pe_scl_p256_08t_08t_flt_1210.h"
#include "pe_scl_p256_08t_06t_flt_0306.h"
#include "pe_scl_p256_08t_06t_flt_0610.h"
#include "pe_scl_p256_08t_04t_flt_0306.h"
#include "pe_scl_p256_08t_04t_flt_0308.h"
#include "pe_scl_p256_08t_04t_flt_0008.h"
#include "pe_scl_p256_08t_04t_flt_0910.h"
#include "pe_scl_p256_08t_04t_flt_1410.h"
#include "pe_scl_p256_08t_04t_flt_1510.h"
#include "pe_scl_p256_08t_04t_flt_0610.h"
#include "pe_scl_p256_08t_02t_flt_0308.h"
#include "pe_scl_p256_04t_04t_flt_0308.h"
#include "pe_scl_p256_04t_04t_flt_0910.h"
#include "pe_scl_p256_04t_04t_flt_1410.h"
#include "pe_scl_p256_04t_04t_flt_1510.h"
#include "pe_scl_p256_04t_04t_flt_0610.h"
#include "pe_scl_p256_04t_04t_flt_0008.h"
#include "pe_scl_p256_04t_02t_flt_0308.h"

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

/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_SCL_P256_FLT_PARAM_H_ */

