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
 *	demod circular buffer for mcu internal communication
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-11-07
 *	@note
 */

#ifndef __DEMOD_L0_CBUF_RAM__
#define __DEMOD_L0_CBUF_RAM__

typedef struct {
	UINT8	len;
	UINT8	seq;
	UINT16	typ;
} CBUF_RAM_H;

typedef struct cbuf {
	UINT32	head;
	UINT32	tail;

	UINT32*	base;
	UINT32	size;
} CBUF_RAM_T;

int DEMOD_L0_CBUF_RAM_Reset(CBUF_RAM_T * cb);

int DEMOD_L0_CBUF_RAM_Write(CBUF_RAM_T * cb, CBUF_RAM_H * phead, char * psrc);
int DEMOD_L0_CBUF_RAM_Read(CBUF_RAM_T * cb, CBUF_RAM_H * phead, char * pdst);

int DEMOD_L0_CBUF_RAM_Used(CBUF_RAM_T * cb);
int DEMOD_L0_CBUF_RAM_Left(CBUF_RAM_T * cb);

int DEMOD_L0_CBUF_RAM_Status(CBUF_RAM_T * cb, char * dbglog);

int DEMOD_L0_CBUF_RAM_Dump(CBUF_RAM_T * cb, char * dbglog);
int DEMOD_L0_CBUF_RAM_Show(CBUF_RAM_T * cb, char * dbglog);

#endif //__DEMOD_L0_CBUF_RAM__
