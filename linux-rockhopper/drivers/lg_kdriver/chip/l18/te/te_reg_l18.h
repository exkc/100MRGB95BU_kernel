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


/** @file
 *
 *  te chip reg functions
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2017-04-11
 *  @note		Additional information.
 */


#ifndef _TE_REG_L18_H_
#define _TE_REG_L18_H_


/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "te_kapi.h"
#include "te_reg.h"

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
/* CTOP */
int L18_TE_REG_CTOP_SetInitValue(void);
int L18_TE_REG_SetCiInput(UINT8 src);
int L18_TE_REG_GetCiInput(UINT8 *src);
int L18_TE_REG_SetCiOutClk(UINT8 clk);
int L18_TE_REG_SetStccClockSource(UINT8 ch, UINT8 src);
int L18_TE_REG_SetInOutPort(UINT8 port, UINT8 dir, UINT8 mode, UINT8 clk);
int L18_TE_REG_GetDcoInputClock(UINT32 *freq);
int L18_TE_REG_SelectUart(UINT8 uart);
int L18_TE_REG_SelectJtag(UINT8 jtag);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/




#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _TE_REG_L18_H_ */

/** @} */

