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
 *	demod circular buffer for communication with mcu
 *
 *	@author 	samin.ryu
 *	@version	1.2
 *	@date		2020-03-17
 *	@note		sync FW & API
 */

#ifndef __DEMOD_L0_CBUF__
#define __DEMOD_L0_CBUF__

#define CBUF_DUMP_MAX	0x400	/* 1024 */

typedef struct {
	UINT32	magic;
	UINT8	len;
	UINT8	seq;
	UINT16	typ;
} CBUF_H;

/*
 * head : can update only reader
 * tail : can update only writer
 */

typedef struct {
	UINT16	head;
	UINT16	tail;
	UINT16	state;
	UINT16	debug;
} CBUF_R;

typedef struct {
	void *	chip;

	CBUF_R	regs;

	UINT32	head;
	UINT32	tail;

	UINT16	base;
	UINT16	size;

	UINT32	seq;
	UINT32	ovf;
	UINT32	tout;

} CBUF_T;

typedef enum {
	CBUF_STATE_UNKNOWN = -1,
	CBUF_STATE_INIT = 0,
	CBUF_STATE_START = 1,
	CBUF_STATE_INVALID = 2,
	CBUF_STATE_DONE = 3,
} cbuf_state;

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

int DEMOD_L0_CBUF_Init (CBUF_T * cb, UINT32 head, UINT32 tail, UINT32 state, UINT32 debug, UINT32 base, UINT32 size);

int DEMOD_L0_CBUF_Reset (CBUF_T * cb);
int DEMOD_L0_CBUF_Clear (CBUF_T * cb);

int DEMOD_L0_CBUF_Write (CBUF_T * cb, UINT32 typ, UINT32 seq, char * src, int len);
int DEMOD_L0_CBUF_Read (CBUF_T * cb, CBUF_H * phead, char *pdata);

int DEMOD_L0_CBUF_GetState (CBUF_T * cb, cbuf_state * pstate);

int DEMOD_L0_CBUF_Used (CBUF_T * cb);
int DEMOD_L0_CBUF_Left (CBUF_T * cb);

int DEMOD_L0_CBUF_Status (CBUF_T * cb, char * dbglog);

int DEMOD_L0_CBUF_Dump (CBUF_T * cb, char * dbglog);
int DEMOD_L0_CBUF_Show (CBUF_T * cb, char * dbglog);

#ifdef    __cplusplus
}
#endif /* __cplusplus */

#endif //__DEMOD_L0_CBUF__

