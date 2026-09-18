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

#ifndef	_DE_TEST_H_
#define	_DE_TEST_H_

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
enum de_test_handler_type
{
	de_test_handler_type_init = 0,
	de_test_handler_type_start,
	de_test_handler_type_state,
	de_test_handler_type_stop,
	de_test_handler_type_max
};

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
struct de_test_handler
{
	enum de_test_handler_type type;
	void* cmd;
	char* str;
};

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern int de_test_command(unsigned long arg,unsigned int flag);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_TEST_H_ */
