/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2013 by LG Electronics Inc.

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
 *  mjpeg queue header.
 *
 *  @author		Jihoon Lee (gaius.lee@lge.com)
 *  @version	1.0
 *  @date		2015.08.04
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

#ifndef _MJPEG_QUEUE_H_
#define _MJPEG_QUEUE_H_

/*-----------------------------------------------------------------------------
        Control Constants
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    File Inclusions
-----------------------------------------------------------------------------*/
#include "base_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*-----------------------------------------------------------------------------
        Constant Definitions
-----------------------------------------------------------------------------*/

#define MSG_Q_SIZE 12

/*-----------------------------------------------------------------------------
        Macro Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    Type Definitions
-----------------------------------------------------------------------------*/

typedef struct {
	UINT32 queue[MSG_Q_SIZE];
	int head;
	int tail;
	int count;
	int mutex;
} LXMJPEG_MSG_QUEUE_T;

/*-----------------------------------------------------------------------------
        Generic Usage Functions
-----------------------------------------------------------------------------*/

void QueueInit(LXMJPEG_MSG_QUEUE_T *queue);
void QueueWait(LXMJPEG_MSG_QUEUE_T *queue);
BOOLEAN QueueIsEmpty(LXMJPEG_MSG_QUEUE_T *queue);
int MJPEG_QueuePush(LXMJPEG_MSG_QUEUE_T *queue, UINT32 val);
UINT32 MJPEG_QueuePop(LXMJPEG_MSG_QUEUE_T *queue);
UINT32 MJPEG_QueuePopLoop(LXMJPEG_MSG_QUEUE_T *queue);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MJPEG_QUEUE_H_ */

/** @} */
