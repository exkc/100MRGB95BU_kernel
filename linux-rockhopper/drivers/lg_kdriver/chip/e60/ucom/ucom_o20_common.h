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
 *  main driver implementation for micom device.
 *	micom device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2017.04.13
 *  note			Additional information.
 *
 *  @addtogroup
 */


#ifndef	_PM_O20_COMMON_H_
#define	_PM_O20_COMMON_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "ucom_cfg.h"
#include "ucom_kapi.h"
#include "ucom_drv.h"

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
#define MAILBOX(m)	((m) << 5) //64byte
#define REG(n)	((n) << 2)

#define ENABLE_IOREMAP_IPC /* enable:  l18f asic ,  disable: m16+ ucom test*/

#ifndef ENABLE_IOREMAP_IPC
/* enable micom emulation task as ucom ipc receiver */
#define ENABLE_MICOM_EMUL_TASK
#endif

//#define ENABLE_NVRAM_RW_BY_MICOM_REQ


typedef struct
{
	void  			(*init)(void);
	int				(*getstatus)(void);
	int				(*write)(LX_UCOM_PARAM_T * param);
	int				(*read)(LX_UCOM_PARAM_T * param);


} ucom_o20_func_t;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
ucom_proc_t* get_o20_ucom_proc(void);
ucom_o20_func_t* get_o20_ucom_func(void);
ucom_driver_t* get_o20_ucom_driver(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PM_DRV_H_ */

/** @} */
