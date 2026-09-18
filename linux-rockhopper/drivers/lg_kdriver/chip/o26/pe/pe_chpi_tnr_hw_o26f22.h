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

/** @file pe_chpi_tnr_hw_o26f22.h
 *
 *  driver header for picture enhance sharpness. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CHPI_TNR_HW_O26F22_H_
#define	_PE_CHPI_TNR_HW_O26F22_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

#ifdef	__cplusplus
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
typedef enum
{
	PE_CHPI_TNR_O26F22_TNR_SD = 0,			///< sd i
	PE_CHPI_TNR_O26F22_TNR_HD_I,			///< hd i
	PE_CHPI_TNR_O26F22_TNR_HD_P,			///< hd p
	PE_CHPI_TNR_O26F22_TNR_UD,				///< ud
	PE_CHPI_TNR_O26F22_TNR_UD_8K,			///< 8k ud
	PE_CHPI_TNR_O26F22_TNR_NUM				///< max num
}
PE_CHPI_TNR_HW_O26F22_TNR_FMT;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int PE_CHPI_TNR_HW_O26F22_SetDefault(void);
extern int PE_CHPI_TNR_HW_O26F22_Init(PE_CFG_CTRL_T *pstParams);
extern int PE_CHPI_TNR_HW_O26F22_SetCtrl(void *pstParams);
extern int PE_CHPI_TNR_HW_O26F22_GetCtrl(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CHPI_TNR_HW_O26F22_H_ */
