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

/** @file pe_etc_hw.h
 *
 *  driver header for picture enhance etc functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.07.16
 *	@see		
 */

#ifndef	_PE_ETC_HW_H_
#define	_PE_ETC_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
/* the latest chip : the upper position */
#ifdef USE_PE_KDRV_CODES_FOR_O26
#include "pe_inf_o26.h"
#include "pe_tsk_o26.h"
#include "pe_fwi_o26.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_O24
#include "pe_inf_o24.h"
#include "pe_tsk_o24.h"
#include "pe_fwi_o24.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_M23
#include "pe_inf_m23.h"
#include "pe_tsk_m23.h"
#include "pe_fwi_m23.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_O22
#include "pe_inf_o22.h"
#include "pe_tsk_o22.h"
#include "pe_fwi_o22.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_E60
#include "pe_inf_e60.h"
#include "pe_tsk_e60.h"
#include "pe_fwi_e60.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_O20
#include "pe_inf_o20.h"
#include "pe_tsk_o20.h"
#include "pe_fwi_o20.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_O18
#include "pe_inf_o18.h"
#include "pe_tsk_o18.h"
#include "pe_fwi_o18.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_M17
#include "pe_inf_m17.h"
#include "pe_tsk_m17.h"
#include "pe_fwi_m17.h"
#include "pe_inf_m17c0.h"
#include "pe_tsk_m17c0.h"
#include "pe_fwi_m17c0.h"
#endif
#ifdef USE_PE_KDRV_CODES_FOR_M19
#include "pe_inf_m19.h"
#include "pe_tsk_m19.h"
#include "pe_fwi_m19.h"
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

#endif /* _PE_ETC_HW_H_ */

