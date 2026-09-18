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

#ifndef	_PE_TEST_H_
#define	_PE_TEST_H_

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
enum pe_test_handler_type
{
	pe_test_handler_type_init = 0,
	pe_test_handler_type_start,
	pe_test_handler_type_state,
	pe_test_handler_type_stop,
	pe_test_handler_type_max
};

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
struct pe_test_handler
{
	enum pe_test_handler_type type;
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
extern int pe_test_command(unsigned long arg,unsigned int flag);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_TEST_H_ */
