/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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

/** @file
 *
 *  sdec driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-02-02
 *  @note		Additional information.
 */

#ifndef _IPC_CORE_H_
#define _IPC_CORE_H_

#include "ipc.h"

struct ipc *_TE_IPC_Create(void);
void _TE_IPC_Destroy(struct ipc *ipc);
int _TE_IPC_Init(struct ipc *ipc);

int _TE_IPC_Send(struct ipc *ipc, u16 type, const void *data, u32 size);

#endif				/* _IPC_CORE_H_ */
