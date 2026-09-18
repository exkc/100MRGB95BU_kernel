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
 *  main user interface for template device
 *
 *  author		author
 *  version		1.0
 *  date		20xx.xx.xx
 *
 *  @addtogroup lg115x_template
 *	@{
 */

#ifndef	_TEMPLATE_KAPI_H_
#define	_TEMPLATE_KAPI_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#include "base_types.h"

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define TEMPLATE_IOC_MAGIC       'X'
#define TEMPLATE_IOC_MAXNR		50

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	IO comand naming rule  : MODULE_IO[R][W]_COMMAND
----------------------------------------------------------------------------------------*/
#define	TEMPLATE_IO_TEST_RESET			_IO(TEMPLATE_IOC_MAGIC, 0)
#define TEMPLATE_IOR_TEST_READ			_IOR(TEMPLATE_IOC_MAGIC,1,UINT32)
#define TEMPLATE_IOW_TEST_WRITE			_IOW(TEMPLATE_IOC_MAGIC,2,UINT32)
#define TEMPLATE_IORW_TEST_READ_WRITE		_IOWR(TEMPLATE_IOC_MAGIC,3,UINT32)

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

#endif /* _TEMPLATE_KAPI_H_ */

/** @} */

