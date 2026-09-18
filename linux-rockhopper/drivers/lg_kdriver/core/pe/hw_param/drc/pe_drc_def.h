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

/** @file pe_drc_def.h
 *
 *  driver header for picture enhance drc parameters. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2015.04.23
 *	@see		
 */

#ifndef	_PE_DRC_DEF_H_
#define	_PE_DRC_DEF_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_DRC_LUT_SIZE		1185
#define PE_DRC_LUT_ITEM_NUM		4
#define PE_DRC_CUV_SIZE		156
#define PE_DRC_CUV_ITEM_NUM		1


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
//extern const UINT32 pe_drc_lut[PE_DRC_LUT_ITEM_NUM][PE_DRC_LUT_SIZE];
//extern const UINT32 pe_drc_lut_f16[PE_DRC_LUT_ITEM_NUM][PE_DRC_LUT_SIZE];
//extern const UINT32 pe_drc_lut_oled[PE_DRC_LUT_ITEM_NUM][PE_DRC_LUT_SIZE];
extern const UINT32 pe_drc_lut_f20[PE_DRC_LUT_ITEM_NUM][5222];
extern const UINT32 pe_drc_lut_m16p[PE_DRC_LUT_ITEM_NUM][PE_DRC_LUT_SIZE];
extern const UINT32 pe_drc_lut_init[PE_DRC_CUV_ITEM_NUM][PE_DRC_CUV_SIZE];

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DRC_DEF_H_ */
