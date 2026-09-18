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

/** @file pe_chpi_obc_hw_e60f20.h
 *
 *  driver header for picture enhance sharpness. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CHPI_OBC_HW_E60F20_H_
#define	_PE_CHPI_OBC_HW_E60F20_H_

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
	PE_CHPI_OBC_E60F20_OBF_HD,				///< hd
	PE_CHPI_OBC_E60F20_OBF_SD,				///< sd
	PE_CHPI_OBC_E60F20_OBF_UD,				///< ud
	PE_CHPI_OBC_E60F20_OBF_NUM				///< max num
}
PE_CHPI_OBC_HW_E60F20_OBF_FMT;

typedef enum
{
	PE_CHPI_OBC_E60F20_OBO_HD,				///< hd
	PE_CHPI_OBC_E60F20_OBO_SD,				///< sd
	PE_CHPI_OBC_E60F20_OBO_UD,				///< ud
	PE_CHPI_OBC_E60F20_OBO_NUM				///< max num
}
PE_CHPI_OBC_HW_E60F20_OBO_FMT;

typedef enum
{
	PE_CHPI_OBC_E60F20_RCF_HD,				///< hd
	PE_CHPI_OBC_E60F20_RCF_SD,				///< sd
	PE_CHPI_OBC_E60F20_RCF_UD,				///< ud
	PE_CHPI_OBC_E60F20_RCF_NUM				///< max num
}
PE_CHPI_OBC_HW_E60F20_RCF_FMT;

typedef enum
{
	PE_CHPI_OBC_E60F20_RCO_HD,				///< hd
	PE_CHPI_OBC_E60F20_RCO_SD,				///< sd
	PE_CHPI_OBC_E60F20_RCO_UD,				///< ud
	PE_CHPI_OBC_E60F20_RCO_NUM				///< max num
}
PE_CHPI_OBC_HW_E60F20_RCO_FMT;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int PE_CHPI_OBC_HW_E60F20_SetDefault(void);
extern int PE_CHPI_OBC_HW_E60F20_Init(PE_CFG_CTRL_T *pstParams);
extern int PE_CHPI_OBC_HW_E60F20_SetCtrl(void *pstParams);
extern int PE_CHPI_OBC_HW_E60F20_SetLUT(void *pstParams);
extern int PE_CHPI_OBC_HW_E60F20_SetEnable(UINT32 *onoff);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CHPI_OBC_HW_E60F20_H_ */
