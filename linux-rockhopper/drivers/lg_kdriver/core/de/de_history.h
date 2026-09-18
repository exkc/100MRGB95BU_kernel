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
 *	History manager implementation for de and pe devices.
 *
 *
 *	author		arjun.purushothaman (arjun.purushothaman@lge.com)
 *	version		1.0
 *	date		2014.11.3
 *	note		Additional information.
 *
 *	@addtogroup lg1150_de
 *	@{
 */

#ifndef	_DE_HISTORY_H_
#define	_DE_HISTORY_H_

int DE_Push_Hist(unsigned int cmd, unsigned long arg );
int DE_Pop_Hist(unsigned int cmd, unsigned int index);

void DE_Populate_Fn_Table(void);


#endif
