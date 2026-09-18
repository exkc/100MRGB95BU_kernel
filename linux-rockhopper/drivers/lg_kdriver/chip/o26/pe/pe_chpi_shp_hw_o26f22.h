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

/** @file pe_chpi_shp_hw_o26f22.h
 *
 *  driver header for picture enhance sharpness. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.15
 *	@see		
 */

#ifndef	_PE_CHPI_SHP_HW_O26F22_H_
#define	_PE_CHPI_SHP_HW_O26F22_H_

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
	PE_CHPI_SHP_O26F22_RES_SD,				///< sd
	PE_CHPI_SHP_O26F22_RES_HD,				///< hd
	PE_CHPI_SHP_O26F22_RES_UHD,				///< uhd
	PE_CHPI_SHP_O26F22_RES_DTV_SD,			///< dtv sd 
	PE_CHPI_SHP_O26F22_RES_DTV_HD,			///< dtv hd
	PE_CHPI_SHP_O26F22_RES_SEEMLESS,		///< dtv hd
	PE_CHPI_SHP_O26F22_RES_UHD_8K,				///< uhd 8k
	PE_CHPI_SHP_O26F22_RES_NUM				///< max num
}
PE_CHPI_SHP_HW_O26F22_RES_FMT;

typedef enum
{
	PE_CHPI_SHP_O26F22_CTI_HD,				///< hd
	PE_CHPI_SHP_O26F22_CTI_SD,				///< sd
	PE_CHPI_SHP_O26F22_CTI_VR_360,				///< sd
	PE_CHPI_SHP_O26F22_CTI_ATV,				///< atv
	PE_CHPI_SHP_O26F22_CTI_NUM				///< max num
}
PE_CHPI_SHP_HW_O26F22_CTI_FMT;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int PE_CHPI_SHP_HW_O26F22_SetDefault(void);
extern int PE_CHPI_SHP_HW_O26F22_Init(PE_CFG_CTRL_T *pstParams);
extern int PE_CHPI_SHP_HW_O26F22_SetCtrl(void *pstParams);
extern int PE_CHPI_SHP_HW_O26F22_SetEnable(UINT32 *onoff);
extern int PE_CHPI_SHP_HW_O26F22_GetCtrl(void);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CHPI_SHP_HW_O26F22_H_ */
