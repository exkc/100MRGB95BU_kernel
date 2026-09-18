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

/** @file pe_cfg.h
 *
 *  configuration header for pe device. ( used only within kdriver )
 *
 *	@author
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
 *	@see
 */

#ifndef	_PE_CFG_H_
#define	_PE_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define	PE_MODULE			"pe"
#define PE_MAX_DEVICE		1

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_CH_MEM_FW_MAX	4

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	char*	db_name;	///< name
	UINT32	db_base;	///< base address
	UINT32	db_size;	///< size
}
PE_CH_MEM_T;

typedef struct
{
	PE_CH_MEM_T db[PE_CH_MEM_FW_MAX];
}
PE_MEM_CFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void PE_InitCfg ( void );

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern PE_MEM_CFG_T gMemCfgPe[];

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CFG_H_ */
