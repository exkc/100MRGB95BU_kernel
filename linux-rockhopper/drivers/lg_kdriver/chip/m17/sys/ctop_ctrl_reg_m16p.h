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
 * Register access for CTOP
 *
 * author     hwanwook lee (hwanwook.lee@lge.com)
 * version    1.0
 * date       2016.04.20
 * note       Additional information.
 *
 * @addtogroup lg13xx_sys
 * @{
 */

#ifndef  __CTOP_CTRL_REG_M16P_H__
#define  __CTOP_CTRL_REG_M16P_H__

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "sys_reg_base.h"


#include "ctop_ctrl_reg_m17.h"


/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/* M16PA0 */

#define CTOP_M16PA0_SHDW        CTOP_M17A0_SHDW
#define CTOP_M16PA0_PHYS        CTOP_M17A0_PHYS

#define CTOP_CTRL_M16PA0_RdFL   CTOP_CTRL_M17A0_RdFL
#define CTOP_CTRL_M16PA0_WrFL   CTOP_CTRL_M17A0_WrFL

#define CTOP_CTRL_M16PA0_Rd     CTOP_CTRL_M17A0_Rd
#define CTOP_CTRL_M16PA0_Wr     CTOP_CTRL_M17A0_Wr


#define CTOP_CTRL_M16PA0_RdFd   CTOP_CTRL_M17A0_RdFd
#define CTOP_CTRL_M16PA0_Rd01   CTOP_CTRL_M17A0_Rd01
#define CTOP_CTRL_M16PA0_Rd02   CTOP_CTRL_M17A0_Rd02
#define CTOP_CTRL_M16PA0_Rd03   CTOP_CTRL_M17A0_Rd03


#define CTOP_CTRL_M16PA0_Wr01   CTOP_CTRL_M17A0_Wr01
#define CTOP_CTRL_M16PA0_Wr02   CTOP_CTRL_M17A0_Wr02
#define CTOP_CTRL_M16PA0_Wr03   CTOP_CTRL_M17A0_Wr03

/* M16PP = M16P,C0 */

#define CTOP_M16PC0_SHDW        CTOP_M17A0_SHDW
#define CTOP_M16PC0_PHYS        CTOP_M17A0_PHYS

#define CTOP_CTRL_M16PC0_RdFL   CTOP_CTRL_M17A0_RdFL
#define CTOP_CTRL_M16PC0_WrFL   CTOP_CTRL_M17A0_WrFL

#define CTOP_CTRL_M16PC0_Rd     CTOP_CTRL_M17A0_Rd
#define CTOP_CTRL_M16PC0_Wr     CTOP_CTRL_M17A0_Wr


#define CTOP_CTRL_M16PC0_RdFd   CTOP_CTRL_M17A0_RdFd
#define CTOP_CTRL_M16PC0_Rd01   CTOP_CTRL_M17A0_Rd01
#define CTOP_CTRL_M16PC0_Rd02   CTOP_CTRL_M17A0_Rd02
#define CTOP_CTRL_M16PC0_Rd03   CTOP_CTRL_M17A0_Rd03


#define CTOP_CTRL_M16PC0_Wr01   CTOP_CTRL_M17A0_Wr01
#define CTOP_CTRL_M16PC0_Wr02   CTOP_CTRL_M17A0_Wr02
#define CTOP_CTRL_M16PC0_Wr03   CTOP_CTRL_M17A0_Wr03


#define CTOP_CTRL_M16PC0_READ   CTOP_CTRL_M17A0_READ
#define CTOP_CTRL_M16PC0_WRITE  CTOP_CTRL_M17A0_WRITE



/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
#endif
/**  @} */
