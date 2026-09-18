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

#define DEMOD_TAG "[L0.CM] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L0_CBUF_RAM.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <linux/kernel.h>	/**< printk() */

#include "os_util.h"
#include "debug_util.h"
#include "demod_impl.h"
#include "demod_module.h"

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)

#endif

static int _CBUF_Used(CBUF_RAM_T * cb) {
	return (cb->tail + cb->size - cb->head) % (cb->size);
}

static int _CBUF_UsedCont(CBUF_RAM_T * cb) {
	int used = (int)cb->size - (int)cb->head;
	int next = (cb->tail + used) % (cb->size);
	return next < used ? next : used;
}

static int _CBUF_Left(CBUF_RAM_T * cb) {
	//return ((int)cb->head - ((int)cb->tail + 4) + cb->size) % (cb->size);
	return cb->size - _CBUF_Used(cb);
}

static int _CBUF_LeftCont(CBUF_RAM_T * cb) {
	int left = ((int)cb->size) - ((int)cb->tail);
	int next = (cb->head + left) % (cb->size);
	return cb->tail >= cb->head ? left : next;
}

static int _CBUF_Reset(CBUF_RAM_T * cb) {
	cb->head = 0;
	cb->tail = 0;

	return NO_DEMOD_ERROR;
}

static int _CBUF_Status(CBUF_RAM_T * cb, char * dbglog) {
	return SPRINTF(
			dbglog,
			"head %d tail %d base %p size%d used%d left%d",
			cb->head, cb->tail, cb->base, cb->size, _CBUF_Used(cb), _CBUF_Left(cb));
}

static int _CBUF_Dump(CBUF_RAM_T * cb, char * dbglog) {
	int dbgidx = 0;

	dbgidx += SPRINTF(dbglog + dbgidx, "dump sz %d\n", cb->size);
	dbgidx += DEMOD_DUMP_WORD(dbglog + dbgidx, cb->base, cb->size);

	return dbgidx;
}

int DEMOD_L0_CBUF_RAM_Write(CBUF_RAM_T * cb, CBUF_RAM_H * phead, char * psrc) {
	int left;
	int cont;

	UINT32 dbg_tail;

	//int wlen = (len + 3) >> 2; // 4 bytes align, change to word length
	int alen = (phead->len + 3) & ~0x3; // 4 bytes align

	/* null check, if len > 0, ptr have to not null */
	if (cb == NULL || (psrc == NULL && phead->len > 0)) {
		DEMOD_ERROR("E:cw 1 of args inv %p %p %d\n", cb, psrc, phead->len);
		return -ERROR_DEMOD_CBUF_INV;
	}

	dbg_tail = cb->tail; /* for debugging log */

	left = _CBUF_Left(cb);
	cont = _CBUF_LeftCont(cb);

	if (left < (sizeof(CBUF_RAM_H) + alen)) {
		DEMOD_ERROR("E:cw rq %lu > left %d\n", sizeof(CBUF_RAM_H) + alen, left);
		return -ERROR_DEMOD_CBUF_FULL;
	}

	memcpy(((char *)cb->base + cb->tail), (char *)phead, sizeof(CBUF_RAM_H));
	cb->tail = (cb->tail + sizeof(CBUF_RAM_H)) % cb->size;

	/* write additional payloads */
	if (alen > 0) {
		cont = _CBUF_LeftCont(cb);

		if (alen < cont)
			cont = alen;

		memcpy(((char *)cb->base + cb->tail), (char *)psrc, cont);

		if (alen != cont) {
			memcpy((char *)cb->base, (char *)(psrc + cont), alen - cont);
		}

		cb->tail = (cb->tail + alen) % cb->size;
	}

	DEMOD_DEBUG("D:cw H%3d T%3d->%3d TW %d\n", cb->head, dbg_tail, cb->tail, sizeof(CBUF_RAM_H) + alen);
	return NO_DEMOD_ERROR;
}

int DEMOD_L0_CBUF_RAM_Read(CBUF_RAM_T * cb, CBUF_RAM_H * phead, char * pdst) {
	int used;
	int cont;

	UINT32 dbg_head; /* debuggin information */

	int alen; // aligned length

	if (cb == NULL || pdst == NULL) {
		DEMOD_ERROR("E:cw 1 of args inv %p %p\n", cb, pdst);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	dbg_head = cb->head; /* for debugging log */

	if (_CBUF_Used(cb) == 0) {
		DEMOD_ERROR("E:cr empty, H%3d T%3d\n", cb->head, cb->tail);
		return -ERROR_DEMOD_CBUF_EMPTY;
	}

	/* read head struct */
	memcpy(phead, ((char *)cb->base + cb->head), sizeof(CBUF_RAM_H));
	cb->head = (cb->head + sizeof(CBUF_RAM_H)) % cb->size;

	alen = (phead->len + 3) & ~0x3;

	if (alen > 0) {
		used = _CBUF_Used(cb);
		cont = _CBUF_UsedCont(cb);

		if (alen > used) {
			DEMOD_L0_CBUF_RAM_Status(cb, sdbglog);
			DEMOD_ERROR("E:cr inv param, %s\n", sdbglog);
			DEMOD_ERROR("E:cr inv param, cb H%d T%d az%d used%d, hdr typ%04Xseq%04Xlen%3u\n", cb->head, cb->tail, alen, used, phead->typ, phead->seq, phead->len);
			DEMOD_L0_CBUF_RAM_Dump(cb, sdbglog);
			DEMOD_ERROR("E:cr inv param, dump\n%s\n", sdbglog);
			cb->head = cb->tail;

			return -ERROR_DEMOD_CBUF_INV;
		}

		if (alen < cont)
			cont = alen;

		memcpy(pdst, ((char *)cb->base + cb->head), cont);

		if (alen != cont) {
			memcpy(pdst + cont, (char *)cb->base, alen - cont);
		}

		cb->head = (cb->head + alen) % cb->size;
	}

	DEMOD_DEBUG("D:cr H%3d->%3d T%3d len %d\n", dbg_head, cb->head, cb->tail, sizeof(CBUF_RAM_H) + alen);
	return NO_DEMOD_ERROR;
}

int DEMOD_L0_CBUF_RAM_Used(CBUF_RAM_T * cb) {
	int bsiz;

	if (cb == NULL) {
		DEMOD_ERROR("%s: cb is null\n", __FUNCTION__);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	bsiz = _CBUF_Used(cb);
	return bsiz;
}

int DEMOD_L0_CBUF_RAM_Left(CBUF_RAM_T * cb) {
	int bsiz;

	if (cb == NULL) {
		DEMOD_ERROR("%s: cb is null\n", __FUNCTION__);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	bsiz = _CBUF_Left(cb);
	return bsiz;
}

int DEMOD_L0_CBUF_RAM_Reset(CBUF_RAM_T * cb) {

	if (cb == NULL) {
		DEMOD_ERROR("%s: cb is null\n", __FUNCTION__);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	_CBUF_Reset(cb);

	return NO_DEMOD_ERROR;
}

int DEMOD_L0_CBUF_RAM_Status(CBUF_RAM_T * cb, char * dbglog) {
	if (cb == NULL) {
		DEMOD_ERROR("%s: cb is null\n", __FUNCTION__);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	return _CBUF_Status(cb, dbglog);
}

int DEMOD_L0_CBUF_RAM_Dump(CBUF_RAM_T * cb, char * dbglog) {
	int dbgidx = 0;

	if (cb == NULL) {
		DEMOD_ERROR("%s: cb is null\n", __FUNCTION__);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	return _CBUF_Dump(cb, dbglog + dbgidx);
}

