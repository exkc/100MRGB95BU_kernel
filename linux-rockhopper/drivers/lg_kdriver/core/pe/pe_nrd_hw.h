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

/** @file pe_nrd_hw.h
 *
 *  driver header for picture enhance noise reduction parameters. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.03.14
 *	@see		
 */

#ifndef	_PE_NRD_HW_H_
#define	_PE_NRD_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
/* the latest chip : the upper position */
#ifdef USE_PE_KDRV_CODES_FOR_O26
#include "pe_nrd_hw_o26.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_O24
#include "pe_nrd_hw_o24.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_M23
#include "pe_nrd_hw_m23.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_O22
#include "pe_nrd_hw_o22.h"
#include "pe_chpi_tnr_hw_o22f22.h"
#include "pe_chpi_dnr_hw_o22f22.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_E60
#include "pe_nrd_hw_e60.h"
#include "pe_chpi_tnr_hw_e60f20.h"
#include "pe_chpi_dnr_hw_e60f20.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_O20
#include "pe_nrd_hw_o20.h"
#include "pe_chpi_tnr_hw_f20.h"
#include "pe_chpi_dnr_hw_f20.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_O18
#include "pe_nrd_hw_o18.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_M17
#include "pe_nrd_hw_m17.h"
#include "pe_nrd_hw_m17c0.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_M19
#include "pe_nrd_hw_m19.h"
#endif

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

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_NRD_HW_H_ */
