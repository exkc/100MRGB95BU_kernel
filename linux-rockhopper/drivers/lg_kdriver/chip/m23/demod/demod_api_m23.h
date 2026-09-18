/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013-2019 by LG Electronics Inc.
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


/*  @file
 *
 *	demod m23 api
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-06-13
 *	@note
 */

#ifndef __DEMOD_M23_API__
#define __DEMOD_M23_API__

int DEMOD_M23_API_Suspend (void);
int DEMOD_M23_API_Status(char * pDbglog, int * pDbgidx);
int DEMOD_M23_API_Dump(char * pDbglog, int * pDbgidx);


#endif //__DEMOD_M23_API__


