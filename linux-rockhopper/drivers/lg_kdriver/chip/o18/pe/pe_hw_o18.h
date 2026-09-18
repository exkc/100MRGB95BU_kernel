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

/** @file pe_hw_o18.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_HW_O18_H_
#define	_PE_HW_O18_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_cfg.h"
#include "pe_reg.h"
#include "pe_def.h"
#include "pe_etc.h"
#include "pe_fwi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
/* undef until protect overlap setting ready */
#undef PE_HW_O18_PROTECT_OVERLAP_SETTINGS
/* for pe hw bringup */
#define PE_HW_O18_BRINGUP
/* for pe hw use f/w src apl */
#define PE_HW_O18_USE_FW_SRC_APL

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_HW_O18_CHK_MULTI_PATH_OUT(_x)		\
	((_x)>=LX_PE_OUT_TB && (_x)<=LX_PE_OUT_DUAL_FULL)

#define PE_HW_O18_CHK_MULTI_PATH_FMT(_x)		\
	((_x)==LX_PE_FMT_UHD)

#define PE_HW_O18_CHK_UHD_FMT_N_3D_CASE(_x)		\
	(_x->fmt_type==LX_PE_FMT_UHD && \
	((_x->user_i_type==LX_PE_3D_IN_TB && _x->user_o_type==LX_PE_OUT_TB) || \
	(_x->user_i_type==LX_PE_3D_IN_SS && _x->user_o_type==LX_PE_OUT_SS)))

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

#endif /* _PE_HW_O18_H_ */
