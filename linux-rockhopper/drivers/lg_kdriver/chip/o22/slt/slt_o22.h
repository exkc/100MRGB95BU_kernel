/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  main configuration file for slt device
 *  slt device will teach you how to make device driver with new platform.
 *
 *  @author		wunseo.yeo@lge.com
 *  @version	1.0
 *  @date		2014.08
 *
 *  @addtogroup lg115x_slt
 *  @{
 */

#ifndef __SLT_O22_H__
#define __SLT_O22_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "slt_kapi.h"
#include <linux/completion.h>

#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */


/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
/*
| Error Code Definitions
*/
#define	RET_OK					0			///< success
#define RET_ERROR				-EIO		///< general error
#define RET_INVALID_PARAMS		-EINVAL		///< invalid paramter
#define RET_INVALID_IOCTL		-ENOTTY		///< invalid ioctl request
#define RET_OUT_OF_MEMORY		-ENOMEM		///< out ot memory
#define RET_TIMEOUT				-ETIME		///< timeout
#define RET_TRY_AGAIN			-EAGAIN		///< try again
#define RET_INTR_CALL			-EINTR		///< interrupted system call


/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/

/*
 * SLT_REG		: REAL Register 
 * SLT_REG_SHADOW	: SHADOW Register
 *
 * @def SLT_RdFL : Read  FLushing : Shadow <- Real
 * @def SLT_WrFL : Write FLushing : Shadow -> Real
 * @def SLT_Rd   : Read  whole register(UINT32) from Shadow register.
 * @def SLT_Wr   : Write whole register(UINT32) from Shadow register.
 */

#if 1
#define SLT_RdFL( _r )		( (SLT_REG_Shadow->_r) = (SLT_REG->_r) )
#define SLT_WrFL( _r )		( (SLT_REG->_r) = (SLT_REG_Shadow->_r) )

#define SLT_Rd( _r )		*((UINT32*)(&(SLT_REG_Shadow->_r)))
#define SLT_Wr( _r, _v)		((SLT_Rd(_r))=((UINT32)(_v)))
#else
#define SLT_RdFL( _r )		
#define SLT_WrFL( _r )

#define SLT_Rd( _r )		( *((volatile UINT32*)(&(SLT_REG->_r))) )                    
#define SLT_Wr( _r, _v)		( *((volatile UINT32*)(&(SLT_REG->_r))) ) = ((volatile UINT32)(_v))
#endif


/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

#include "crc_a0_reg.h"

//#define SLT_VSD
//
#define O22_SLT_REG_T		CRC_REG_O22_A0
#define O22_IRQ_SLT			(O22_IRQ_INTR_CRC_TOUT)
#define O22_SLT_BASE		(0xCC454000)


/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
SLT_HW_FUNC_T* SLT_O22_Init(void);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  global Functions
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/

static volatile O22_SLT_REG_T		*SLT_REG = NULL;
static volatile O22_SLT_REG_T		SLT_REG_Shadow[1];

#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* __SLT_O22_H__ */

