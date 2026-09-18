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

/** @file pe_chpi_obc_hw_o22f22.h
 *
 *  driver header for picture enhance sharpness. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CHPI_OBC_HW_O22F22_H_
#define	_PE_CHPI_OBC_HW_O22F22_H_

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
	PE_CHPI_OBC_O22F22_OBC_HD,				///< hd
	PE_CHPI_OBC_O22F22_OBC_SD,				///< sd
	PE_CHPI_OBC_O22F22_OBC_UD,				///< ud
	PE_CHPI_OBC_O22F22_OBC_NUM				///< max num
}
PE_CHPI_OBC_HW_O22F22_OBC_FMT;

typedef enum
{
	PE_CHPI_OBC_O22F22_OBE_HD,				///< hd
	PE_CHPI_OBC_O22F22_OBE_SD,				///< sd
	PE_CHPI_OBC_O22F22_OBE_UD,				///< ud
	PE_CHPI_OBC_O22F22_OBE_NUM				///< max num
}
PE_CHPI_OBC_HW_O22F22_OBE_FMT;

typedef enum
{
	PE_CHPI_OBC_O22F22_AMG_HD,				///< hd
	PE_CHPI_OBC_O22F22_AMG_SD,				///< sd
	PE_CHPI_OBC_O22F22_AMG_UD,				///< ud
	PE_CHPI_OBC_O22F22_AMG_NUM				///< max num
}
PE_CHPI_OBC_HW_O22F22_AMG_FMT;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int PE_CHPI_OBC_HW_O22F22_SetDefault(void);
extern int PE_CHPI_OBC_HW_O22F22_Init(PE_CFG_CTRL_T *pstParams);
extern int PE_CHPI_OBC_HW_O22F22_SetCtrl(void *pstParams);
extern int PE_CHPI_OBC_HW_O22F22_SetLUT(void *pstParams);
extern int PE_CHPI_OBC_HW_O22F22_SetEnable(UINT32 *onoff);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CHPI_OBC_HW_O22F22_H_ */
