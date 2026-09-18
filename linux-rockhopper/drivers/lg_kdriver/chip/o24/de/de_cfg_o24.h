/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author     jaemo.kim (jaemo.kim@lge.com)
 * version    1.0
 * date       2011.04.06
 * note       Additional information.
 *
 * @addtogroup lg1152_de
 * @{
 */

#ifndef  DE_CFG_O24_INC
#define  DE_CFG_O24_INC

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "de_model.h"
#include "de_ver_def.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define VIDEO_O24_FW_SHARED_OFST_VTM		(0)
#define VIDEO_O24_FW_SHARED_SIZE_VTM		(32*1024)
#define VIDEO_O24_FW_SHARED_OFST_VTV		(VIDEO_O24_FW_SHARED_OFST_VTM+VIDEO_O24_FW_SHARED_SIZE_VTM)
#define VIDEO_O24_FW_SHARED_SIZE_VTV		(32*1024)
#define VIDEO_O24_FW_SHARED_OFST_GPS		(VIDEO_O24_FW_SHARED_OFST_VTV+VIDEO_O24_FW_SHARED_SIZE_VTV)
#define VIDEO_O24_FW_SHARED_SIZE_GPS		(32*1024)
#define VIDEO_O24_FW_SHARED_OFST_DLY		(VIDEO_O24_FW_SHARED_OFST_GPS+VIDEO_O24_FW_SHARED_SIZE_GPS)
#define VIDEO_O24_FW_SHARED_SIZE_DLY		(32*1024)
#define VIDEO_O24_FW_SHARED_OFST_FPP		(VIDEO_O24_FW_SHARED_OFST_DLY+VIDEO_O24_FW_SHARED_SIZE_DLY)
#define VIDEO_O24_FW_SHARED_SIZE_FPP		(1*1024*1024)
#define VIDEO_O24_FW_SHARED_OFST_FPP_DNN	(VIDEO_O24_FW_SHARED_OFST_FPP+(32*1024))

#define VIDEO_O24_FW_SHARED_OFST_MVI		(VIDEO_O24_FW_SHARED_OFST_FPP+VIDEO_O24_FW_SHARED_SIZE_FPP)
#define VIDEO_O24_FW_SHARED_SIZE_MVI		(32*1024)

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
extern int de_cfg_o24_preinit(void);
extern int de_cfg_o24_init(void);
extern int de_cfg_o24_cleanup(void);
extern int de_cfg_o24_get_hw_opt(UINT32 *opt);
extern int de_cfg_o24_is_mcu_se_map(int mcu_idx);

#endif   /* ----- #ifndef DE_CFG_O24_INC  ----- */
/**  @} */
