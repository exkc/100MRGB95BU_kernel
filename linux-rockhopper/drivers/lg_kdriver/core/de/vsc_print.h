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
 *  driver interface header for de device. ( used only within kdriver )
 *	de device will teach you how to make device driver with new platform.
 *
 *  @author
 *  @version
 *  @date
 *
 *  @addtogroup
 *	@{
 */

#ifndef	_VSC_PRINT_H_
#define	_VSC_PRINT_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

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
extern int vsc_print_init(void);
extern int vsc_oprint(const char *fmt, ...);
extern int vsc_oprint_enable(int onoff);
extern int vsc_oprint_set_size(int big);
extern int vsc_oprint_set_color(int r, int g, int b);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _VSC_PRINT_H_ */
