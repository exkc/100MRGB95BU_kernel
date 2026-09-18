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
 *  OVI reg def header file for OVI device
 *
 *  author		dj911.kim@lge.com
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup OVI
 *	@{
 */

#ifndef _OVI_REG_DEF_M17_H_
#define _OVI_REG_DEF_M17_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define OVI_TCON_REG_M17A0_BASE	0xC90A0000
#define OVI_TCON_LODC_REG_M17A0_BASE	0xC90A9400
#define OVI_OIF_REG_M17A0_BASE	0xC90A9000
#define OVI_WPR_REG_M17A0_BASE	0xC90AA7F8

#define OVI_TCON_REG_M17C0_BASE	OVI_TCON_REG_M17A0_BASE
#define OVI_TCON_LODC_REG_M17C0_BASE	OVI_TCON_LODC_REG_M17A0_BASE
#define OVI_TCON_CAD_REG_M17C0_BASE	0xC90AC400
#define OVI_OIF_REG_M17C0_BASE	OVI_OIF_REG_M17A0_BASE
#define OVI_WPR_REG_M17C0_BASE	0xC90AA7F4
#define OVI_WPR_MPLUS_START_REG_M17C0_BASE	0xC90AA000
#define OVI_SIW_RGBW_START_REG_M17C0_BASE	0xC90AC000

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

#endif /* _OVI_REG_DEF_M17_H_ */

/** @} */






