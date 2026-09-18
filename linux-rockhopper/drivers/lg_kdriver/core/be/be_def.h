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
 *  definition header file for BE device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.03.05
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

#ifndef _BE_DEF_H_
#define _BE_DEF_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "be_proc.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef CHECK_NULL
#define CHECK_NULL(ptr)  if(!ptr) { printk("%s: %s is null\n", __F__, #ptr); ret = RET_ERROR; break; }
#endif
#ifndef CHECK_KNULL
#define CHECK_KNULL(ptr) if(!ptr) { ffprintk("%s is null\n", #ptr); ret = RET_ERROR; break; }
#endif
#ifndef BREAK_WRONG
#define BREAK_WRONG(val) { printk("%s(%d): break wrong %s(0x%x)\n", __F__, __L__, #val, val); ret = RET_ERROR; break; }
#endif
#ifndef BREAK_RETRY
#define BREAK_RETRY(val) { printk("%s: wait & retry %s(0x%x)\n", __F__, #val, val); ret = RET_TRY_AGAIN; break; }
#endif

#if 1

#ifndef ffprintk
#define ffprintk(format, arg...)    BE_ERROR(format , ## arg)
#endif
#ifndef ffprintq
#define ffprintq(format, arg...)    BE_ERROR(format , ## arg)
#endif
#ifndef ffprintf
#define ffprintf(format, arg...)    BE_ERROR(format , ## arg)
#endif

#else // old macro
#define ffprintk(format, arg...)    printk("%s:%d:%s;" format , __FILE__ , __LINE__ , __FUNCTION__, ## arg)
#define ffprintq(format, arg...)    printk("%s:%d:%s;" format , __FILE__ , __LINE__ , __FUNCTION__, ## arg)
#define ffprintf(format, arg...)    printf("%s:%d:%s;" format , __FILE__ , __LINE__ , __FUNCTION__, ## arg)
#endif

#ifndef TO_STR
#define TO_STR(x)	#x
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/


#endif /* _BE_DEF_H_ */

/** @} */




