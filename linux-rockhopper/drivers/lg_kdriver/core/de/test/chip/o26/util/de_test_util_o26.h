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
 *  driver interface header for vsc test. ( used only within kdriver )
 *
 *  @author
 *  @version
 *  @date
 *
 *  @addtogroup
 *	@{
 */

#ifndef	_DE_TEST_UTIL_O26_H_
#define	_DE_TEST_UTIL_O26_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#define DE_TEST_NOT_READY 100

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
extern int de_test_util_o26_input_open(char *src_name,char *src_size,char *out_size);
extern int de_test_util_o26_input_close(void);
extern int de_test_util_o26_cvi_pat_on(char *name);
extern int de_test_util_o26_cvi_pat_off(void);
extern int de_test_util_o26_check_cvi_i_pixel(char *name, UINT32 pos_x, UINT32 pos_y);
extern int de_test_util_o26_check_cvi_o_pixel(char *name, UINT32 pos_x, UINT32 pos_y);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_TEST_UTIL_O26_H_ */
