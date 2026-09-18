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


#include "de_kapi.h"
#include "pe_kapi.h"

//#define USE_HISTORY
#define NAME_MAX_SIZE 50
#define HIST_MAX_NUM 125

#define HIST_FILE_PATH "/tmp/history_push"
#define PRINT_FIELD( _ST_, _F_,_SEP_ )	printk( "\t\t%s [%d]%s", #_F_, _ST_->_F_,_SEP_ );
#define PRINT_FIELD_HEX( _ST_, _F_,_SEP_ )	printk( "\t\t%s [0x%x]%s", #_F_, _ST_->_F_,_SEP_ );

//PRINT_FIELD( st, edge_Y_filter_en );
//	edge_Y_filter_en : 10
//#define DBG_PRNT_LEN 1000
/*#define HIST_DE_MAX_NUM 20
#define HIST_PE_MAX_NUM 20*/

typedef struct {
	UINT32 sec;
	UINT32 msec;
	UINT32 usec;
} TIME_ST_T;

typedef struct {
	UINT32       c;     // ioctl cmd
	UINT32		pe_info;
	TIME_ST_T t;     // time stamp
	void        *p;     // param
} HIST_BUF_T;

typedef struct {
	UINT32	c;
	char	s[NAME_MAX_SIZE];  //
} FUNC_NAME_LIST_T;

int Push_Ioc_Hist(unsigned int cmd, unsigned long arg);
