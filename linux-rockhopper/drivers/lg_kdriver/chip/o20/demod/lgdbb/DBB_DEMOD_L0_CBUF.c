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
 *	demod circular buff for communication with mcu
 *
 *	@author 	samin.ryu
 *	@version	1.2
 *	@date		2020-03-17
 *	@note		sync FW & API
 */

#define DEMOD_TAG "[L0.CB] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include "DBB_DEMOD_L0_API.h"
#include "DBB_DEMOD_L0_CBUF.h"
#include "DBB_DEMOD_L0_Regmap.h"

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

//#define DEMOD_TEST_IPC_RETRANSMIT
//#define DEMOD_TEST_IPC_INV_MAGIC

#if defined(DEMOD_TEST_IPC_RETRANSMIT)
int test_count_retx = 0;
#endif

#if defined(DEMOD_TEST_IPC_INV_MAGIC)
int test_count_inv_magic = 0;
#endif

static int _CBUF_Used(CBUF_T * cb) {
	return (cb->tail + cb->size - cb->head) % (cb->size);
}

static int _CBUF_UsedCont(CBUF_T * cb) {
	int used = (int)cb->size - (int)cb->head;
	int next = (cb->tail + used) % (cb->size);
	return next < used ? next : used;
}

static int _CBUF_Left(CBUF_T * cb) {
	//return ((int)cb->head - ((int)cb->tail + 4) + cb->size) % (cb->size);
	return cb->size - _CBUF_Used(cb);
}

static int _CBUF_LeftCont(CBUF_T * cb) {
//	int left = ((int)cb->size) - 4 - ((int)cb->tail);
//	int next = (cb->head + left) % (cb->size);
//	return next <= left ? next : (left + 4);
	int left = ((int)cb->size) - ((int)cb->tail);
	int next = (cb->head + left) % (cb->size);
	return cb->tail >= cb->head ? left : next;
}

static int _CBUF_Sync(CBUF_T * cb) {
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->regs.head, 4, &cb->head))
		return -ERROR_DEMOD_READ;
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->regs.tail, 4, &cb->tail))
		return -ERROR_DEMOD_READ;

	return NO_DEMOD_ERROR;
}

static int _CBUF_UpdateHead(CBUF_T * cb) {
	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->regs.head, 4, &cb->head))
		return -ERROR_DEMOD_WRITE;

	return NO_DEMOD_ERROR;
}

static int _CBUF_UpdateTail(CBUF_T * cb) {
	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->regs.tail, 4, &cb->tail))
		return -ERROR_DEMOD_WRITE;

	return NO_DEMOD_ERROR;
}

static int _CBUF_Update(CBUF_T * cb) {
	int ret = NO_DEMOD_ERROR;

	ret = _CBUF_UpdateHead(cb);
	if (ret != NO_DEMOD_ERROR)
		return ret;

	ret = _CBUF_UpdateTail(cb);
	if (ret != NO_DEMOD_ERROR)
		return ret;

	return NO_DEMOD_ERROR;
}

static int _CBUF_SetState(CBUF_T * cb, cbuf_state state) {
	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->regs.state, 4, &state))
		return -ERROR_DEMOD_WRITE;
	return NO_DEMOD_ERROR;
}

static int _CBUF_GetState(CBUF_T * cb, cbuf_state * pstate) {
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->regs.state, 4, pstate))
		return -ERROR_DEMOD_READ;

	return NO_DEMOD_ERROR;
}

static int _CBUF_Reset(CBUF_T * cb) {
	cb->head = 0;
	cb->tail = 0;

	return _CBUF_Update(cb);
}

static int _CBUF_Clear(CBUF_T * cb) {
	UINT32 wtemp = 0;
	int i;

	for (i = cb->base; i < cb->size; i += 4) {
		//DEMOD_MEM_Write(i, 0);
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, i, 4, &wtemp))
			return -ERROR_DEMOD_WRITE;
	}
	return NO_DEMOD_ERROR;
}

static int _CBUF_Status(CBUF_T * cb, char * dbglog) {
	return SPRINTF(	dbglog,
			"H %3d(@x%04x), T %3d(@x%04x), seq %3d, size %3d, used %3d, left %3d, base @x%4X\n",
			cb->head, cb->regs.head, cb->tail, cb->regs.tail, cb->seq, cb->size, _CBUF_Used(cb), _CBUF_Left(cb),
			cb->base);
}

static int _CBUF_Dump(CBUF_T * cb, char * dbglog) {
	static char btmp[CBUF_DUMP_MAX];
	int bsiz = DEMOD_REGMAP_SIZE;
	int dbgidx = 0;

	UINT32 * wptr = (UINT32 *)btmp;

	if (bsiz > CBUF_DUMP_MAX) {
		DEMOD_ERROR("DEMOD_MEM_DUMP_MAX(%d) is not enough to dump memory (%d)\n", CBUF_DUMP_MAX, bsiz);
		bsiz = CBUF_DUMP_MAX;
	}

	memset(btmp, 0, bsiz);
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base, cb->size, wptr))
		return -ERROR_DEMOD_READ;

	dbgidx += SPRINTF(dbglog + dbgidx, "memory dump sz %d\n", cb->size);

	dbgidx += DEMOD_DUMP_WORD(dbglog + dbgidx, wptr, cb->size);

	DEMOD_DEBUG("sz %d, seq %d\n", cb->size, cb->seq);

	return dbgidx;
}

int DEMOD_L0_CBUF_Init(CBUF_T * cb, UINT32 head, UINT32 tail, UINT32 state, UINT32 debug, UINT32 base, UINT32 size) {
	memset(cb, 0, sizeof(CBUF_T));

	cb->regs.head = head;
	cb->regs.tail = tail;
	cb->regs.state = state;
	cb->regs.debug = debug;
	cb->head = 0;
	cb->tail = 0;
	cb->base = base;
	cb->size = size;

	return NO_DEMOD_ERROR;
}

int DEMOD_L0_CBUF_Is_Full(CBUF_T * cb) {
	if (cb == NULL) {
		DEMOD_ERROR("null pointer : cb %p\n", cb);
		return -ERROR_DEMOD_CBUF_NULL;
	}
	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_Sync(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	if (_CBUF_Left(cb) == 0)
		return TRUE;
	else
		return FALSE;
}

int DEMOD_L0_CBUF_Is_Empty(CBUF_T * cb) {
	if (cb == NULL) {
		DEMOD_ERROR("null pointer : cb %p\n", cb);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_Sync(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	if (_CBUF_Used(cb) == 0)
		return TRUE;
	else
		return FALSE;
}

int DEMOD_L0_CBUF_Write(CBUF_T * cb, UINT32 typ, UINT32 seq, char *src, int len) {
	CBUF_H head;

	int left;
	int cont;

	int dbg_tail; /* debuggin information */

	int alen = (len + 3) & ~0x3; // 4 bytes align

	/* null check, if len > 0, ptr have to not null */
	if (cb == NULL || (src == NULL && len > 0)) {
		DEMOD_ERROR("cbuf_wr: one of args are invalid. cb null == %p or ptr %p == null && len %d > 0\n", cb, src, len);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_SetState(cb, CBUF_STATE_INIT);

	_CBUF_Sync(cb);
	//DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	dbg_tail = cb->tail; /* for debugging log */

	left = _CBUF_Left(cb);
	cont = _CBUF_LeftCont(cb);

	if (left < (sizeof(CBUF_H) + alen)) {
		DEMOD_ERROR("cbuf_wr: not enough, request %lu, but only left %d\n", sizeof(CBUF_H) + alen, left);
		DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
		return -ERROR_DEMOD_CBUF_FULL;
	}

	DEMOD_DEBUG("cbuf_wr: head %3d, tail %3d, size %3d, avail %3d, cont %3d, len %3d, alen %3d\n",
		cb->head, cb->tail, cb->size, left, cont, len, alen);

	/* write CBUF_H struct (4 bytes) */
	memset(&head, 0, sizeof(CBUF_H));
	head.magic = DEMOD_MAGIC_CODE;
	head.typ = typ;
	head.seq = seq;
	head.len = len;

#if defined(DEMOD_TEST_IPC_INV_MAGIC)
	test_count_inv_magic++;
	if ((test_count_inv_magic & 0x3F) == 0x0F) {
		head.magic = 0x12345678;
		DEMOD_ERROR("cbuf_wr: test send inv magic, typ %04X, seq %3u, len %3u\n", typ, seq, len);
	}
#endif

	DEMOD_DEBUG("cbuf_wr: buff wr head, %02d-%02d\n",
			cb->base + cb->tail, cb->base + cb->tail + sizeof(CBUF_H));

	//DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	//DEMOD_MEM_Write_Buff(cb->base + cb->tail, (UINT32 *)&head, sizeof(CBUF_H));
	if (sizeof(CBUF_H) < cont)
		cont = sizeof(CBUF_H);

	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base + cb->tail, cont, &head)) {
		DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
		return -ERROR_DEMOD_WRITE;
	}

	if (sizeof(CBUF_H) != cont) {
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base, sizeof(CBUF_H) - cont, (char *)&head + cont)) {
			DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
			return -ERROR_DEMOD_WRITE;
		}
	}
	cb->tail = (cb->tail + sizeof(CBUF_H)) % cb->size;

	/* write additional payloads */
	if (alen > 0) {
		cont = _CBUF_LeftCont(cb);

		DEMOD_DEBUG("cbuf_write: add payloads tail %3d, left %3d, cont %3d, len %3d, alen %3d\n",
			cb->tail, left, cont, len, alen);

		if (alen < cont)
			cont = alen;

		/* start of debugging information log */
		if (alen == cont) {
			DEMOD_DEBUG("cbuf_wr: buff wr len %d->aligned %d, single %02d-%02d\n",
					len, alen, cb->base + cb->tail, cb->base + cb->tail + alen);
		} else {
			DEMOD_DEBUG("cbuf_wr: buff wr len %d->aligned %d, split %02d-%02d, %02d-%02d\n",
					len, alen, cb->base + cb->tail, cb->base + cb->tail + cont, cb->base, cb->base + (alen - cont));
		}
		/* end of debugging information log */

		//DEMOD_MEM_Write_Buff(cb->base + cb->tail, (UINT32 *)src, cont);
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base + cb->tail, cont, src)) {
			DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
			return -ERROR_DEMOD_WRITE;
		}

		if (alen != cont) {
			//DEMOD_MEM_Write_Buff(cb->base, (UINT32 *)(src + cont), alen - cont);
			if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base, alen - cont, src + cont)) {
				DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
				return -ERROR_DEMOD_WRITE;
			}
		}

		cb->tail = (cb->tail + alen) % cb->size;
	}

	cb->seq++;

	/* tail update */
	_CBUF_UpdateTail(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	DEMOD_DEBUG("cbuf_wr: done, head %3d, tail %3d -> %3d, total write %d, seq %d\n", cb->head, dbg_tail, cb->tail, sizeof(CBUF_H) + alen, cb->seq);

	return NO_DEMOD_ERROR;
}

int DEMOD_L0_CBUF_Read(CBUF_T * cb, CBUF_H * phead, char * pdata) {
	int retc;
	int used;
	int cont;

	int dbg_head; /* debuggin information */

	int alen; // aligned length

	if (cb == NULL || pdata == NULL) {
		DEMOD_ERROR("cbuf_rd: one of args are null. %p %p\n", cb, pdata);
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_Sync(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	dbg_head = cb->head; /* for debugging log */

	if (_CBUF_Used(cb) == 0) {
		DEMOD_ERROR("cbuf_rd: empty, head %3d tail %3d\n", cb->head, cb->tail);
		return -ERROR_DEMOD_CBUF_EMPTY;
	}

	DEMOD_DEBUG("cbuf_rd: buff rd head, %02d-%02d\n",
			cb->base + cb->head, cb->base + cb->head + sizeof(CBUF_H));

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_SetState(cb, CBUF_STATE_START);
	/* read head struct */
	//DEMOD_MEM_Read_Buff(cb->base + cb->head, (UINT32 *)phead, sizeof(CBUF_H));
	cont = _CBUF_UsedCont(cb);
	if (sizeof(CBUF_H) < cont)
		cont = sizeof(CBUF_H);

	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base + cb->head, cont, (char *)phead)) {
		goto cbuf_read_error;
	}

	if (sizeof(CBUF_H) != cont) {
		//DEMOD_MEM_Read_Buff(cb->base, (UINT32 *)(pdata + cont), alen - cont);
		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base, sizeof(CBUF_H) - cont, (char *)phead + cont)) {
			goto cbuf_read_error;
		}
	}

	if (phead->magic != DEMOD_MAGIC_CODE) {
		goto cbuf_read_error_with_dump;
	}

	cb->head = (cb->head + sizeof(CBUF_H)) % cb->size;

	alen = (phead->len + 3) & ~0x3;

	if (alen > 0) {
		used = _CBUF_Used(cb);
		cont = _CBUF_UsedCont(cb);

		if (alen > used) {
			goto cbuf_read_error_with_dump;
		}

#if defined(DEMOD_IPC_RETRANSMIT_TEST)
		test_count_retx++;
		if (((test_count_retx & 0x1F) == 0x1F) || ((test_count_retx & 0x3F) == 0x3E)) {
			DEMOD_ERROR("cbuf_rd: discard (%04X, %3u, %3u) for retransmit test\n", phead->typ, phead->seq, phead->len);

			cb->head = cb->tail;
			_CBUF_UpdateHead(cb);

 			_CBUF_SetState(cb, CBUF_STATE_INVALID);

			return -ERROR_DEMOD_CBUF_IPC_FALUT;
		}
#endif

		DEMOD_DEBUG("cbuf_read: get payloads head %3d, used %3d, cont %3d, len %3d, alen %3d\n",
			cb->head, used, cont, phead->len, alen);

		if (alen < cont)
			cont = alen;

		/* start of debugging information log */
		if (alen == cont) {
			DEMOD_DEBUG("cbuf_rd: buff rd len %d->aligned %d, single %02d-%02d\n",
					phead->len, alen, cb->base + cb->head, cb->base + cb->head + alen);
		} else {
			DEMOD_DEBUG("cbuf_rd: buff rd len %d->aligned %d, split %02d-%02d, %02d-%02d\n",
					phead->len, alen, cb->base + cb->head, cb->base + cb->head + cont, cb->base, cb->base + (alen - cont));
		}
		/* end of debugging information log */

		//DEMOD_MEM_Read_Buff(cb->base + cb->head, (UINT32 *)pdata, cont);
		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base + cb->head, cont, pdata)) {
			goto cbuf_read_error_with_dump;
		}

		if (alen != cont) {
			//DEMOD_MEM_Read_Buff(cb->base, (UINT32 *)(pdata + cont), alen - cont);
			if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base, alen - cont, pdata + cont)) {
				goto cbuf_read_error_with_dump;
			}
		}
		cb->head = (cb->head + alen) % cb->size;
	}

	cb->seq++;

	/* head update */
	retc = _CBUF_UpdateHead(cb);
	_CBUF_SetState(cb, CBUF_STATE_DONE);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	DEMOD_DEBUG("cbuf_rd: done, head %3d->%3d, tail %3d, total read %d\n", dbg_head, cb->head, cb->tail, sizeof(CBUF_T) + alen);

	return retc;

cbuf_read_error_with_dump:
	cb->head = dbg_head;
	DEMOD_L0_CBUF_Show(cb, sdbglog);
	DEMOD_DEBUG("cbuf_rd: err, %s\n", sdbglog);
	DEMOD_ERROR("cbuf_rd: err, H%3u T%3ud, head x%8X x%04X %3u %3u, a%3d u%3d\n", cb->head, cb->tail, phead->magic, phead->typ, phead->seq, phead->len, alen, used);

cbuf_read_error:
	cb->head = cb->tail;
	_CBUF_UpdateHead(cb);

	_CBUF_SetState(cb, CBUF_STATE_INVALID);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	return -ERROR_DEMOD_READ;
}

int DEMOD_L0_CBUF_GetState (CBUF_T * cb, cbuf_state * pstate) {
	int ret = NO_DEMOD_ERROR;

	if (cb == NULL) {
		DEMOD_ERROR("cb is null\n");
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	ret = _CBUF_GetState(cb, pstate);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	return ret;
}

int DEMOD_L0_CBUF_Used(CBUF_T * cb) {
	int bsiz;

	if (cb == NULL) {
		DEMOD_ERROR("cb is null\n");
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_Sync(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	bsiz = _CBUF_Used(cb);
	return bsiz;
}

int DEMOD_L0_CBUF_Left(CBUF_T * cb) {
	int bsiz;

	if (cb == NULL) {
		DEMOD_ERROR("cb is null\n");
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_Sync(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	bsiz = _CBUF_Left(cb);
	return bsiz;
}

int DEMOD_L0_CBUF_Reset(CBUF_T * cb) {
	int ret = NO_DEMOD_ERROR;

	if (cb == NULL) {
		DEMOD_ERROR("cb is null\n");
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	ret = _CBUF_Reset(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	return ret;
}

int DEMOD_L0_CBUF_Clear(CBUF_T * cb) {
	int ret = NO_DEMOD_ERROR;
	
	if (cb == NULL) {
		DEMOD_ERROR("cb is null\n");
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	ret = _CBUF_Clear(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	return ret;
}

int DEMOD_L0_CBUF_Status(CBUF_T * cb, char * dbglog) {
	if (cb == NULL) {
		DEMOD_ERROR("cb is null\n");
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_Sync(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	return _CBUF_Status(cb, dbglog);
}

int DEMOD_L0_CBUF_Dump(CBUF_T * cb, char * dbglog) {
	int dbgidx = 0;

	if (cb == NULL) {
		DEMOD_ERROR("cb is null\n");
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_Sync(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	return _CBUF_Dump(cb, dbglog + dbgidx);
}

int DEMOD_L0_CBUF_Show(CBUF_T * cb, char * dbglog) {
/*
	CBUF_H head;

	int pos;
	int alen;
	int cnt = 0;
	int left = 0;

	INT32 buff[64];
*/
	int dbgidx = 0;



	if (cb == NULL) {
		DEMOD_ERROR("cb is null\n");
		return -ERROR_DEMOD_CBUF_NULL;
	}

	DEMOD_L0_Lock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);
	_CBUF_Sync(cb);
	DEMOD_L0_Unlock_CommDevice((LX_DEMOD_L0_Context *)cb->chip);

	dbgidx += _CBUF_Status(cb, dbglog + dbgidx);
	dbgidx += _CBUF_Dump(cb, dbglog + dbgidx);
/*
	pos = cb->head;
	left = (cb->tail + cb->size - pos) % (cb->size);

	while (pos != cb->tail && left > 0) {
		alen = 0;

		//DEMOD_MEM_Read_Buff(cb->base + pos, (UINT32 *)&head, sizeof(CBUF_H));
		if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base + pos, sizeof(CBUF_H), &head))
			return -ERROR_DEMOD_READ;
		dbgidx += SPRINTF(dbglog + dbgidx, "%3d] head x%08x, seq %3u, typ x%04X, len %3u\n", cnt, head.word, head.seq, head.typ, head.len);
		pos += sizeof(CBUF_H);

		alen = (head.len + 3) & ~0x3;
		if (alen> 0) {
			memset(&buff[0], 0, sizeof(buff));
			//DEMOD_MEM_Read_Buff(cb->base + pos, &buff[0], alen);
			if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock((LX_DEMOD_L0_Context *)cb->chip, cb->base + pos, alen, &buff[0]))
				return -ERROR_DEMOD_READ;
			DEMOD_DEBUG("     len %d, alen %d, buff %08x ...\n", head.len, alen, buff[0]);
			dbgidx += SPRINTF(dbglog + dbgidx, "     len %d, alen %d, buff %08x ...\n", head.len, alen, buff[0]);
		}

		pos = (pos + alen) % (cb->size);
		left = (cb->tail + cb->size - pos) % (cb->size);
		cnt++;
	}

	if (cnt == 0)
		dbgidx += SPRINTF(dbglog + dbgidx, "empty");
*/
	return dbgidx;
}


