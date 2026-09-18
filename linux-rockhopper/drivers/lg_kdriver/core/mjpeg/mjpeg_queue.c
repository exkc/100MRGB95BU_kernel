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
 *  lg mjpeg decoder queue implementation.
 *
 *  author		Jihoon Lee (gaius.lee@lge.com)
 *  version		1.0
 *  date		2015.08.04
 *  note		Additional information.
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

/*-----------------------------------------------------------------------------
        Control Constants
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        File Inclusions
-----------------------------------------------------------------------------*/
#include <linux/delay.h>

#include "mjpeg_drv.h"
#include "mjpeg_queue.h"
#include "os_util.h"

/*-----------------------------------------------------------------------------
        Constant Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Macro Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Type Definitions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        External Function Prototype Declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        External Variables
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        global Functions
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        global Variables
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Static Function Prototypes Declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        Static Variables
-----------------------------------------------------------------------------*/

/*========================================================================================
        Implementation Group
========================================================================================*/

// Initialize Queue
void QueueInit(LXMJPEG_MSG_QUEUE_T *queue)
{
	MJPEG_PRINT("Init.\n");

	memset(queue, 0, sizeof(LXMJPEG_MSG_QUEUE_T));
	queue->head = -1;
	queue->tail = -1;
	queue->mutex = 0;
	queue->count = 0;
}

// Wait mutex
void QueueWait(LXMJPEG_MSG_QUEUE_T *queue)
{
	int cnt = 5;

	while (queue->mutex && cnt--) {
		MJPEG_PRINT("Mutex Wait..\n");
		msleep(1);
	}
}

// return  : TRUE  - Queue is empty.
//           FALSE - Queue is not empty.
BOOLEAN QueueIsEmpty(LXMJPEG_MSG_QUEUE_T *queue)
{
	QueueWait(queue);

	return (queue->head == queue->tail);
}

// Put into Queue.
// No mutex wait ( called in ISR() )
int MJPEG_QueuePush(LXMJPEG_MSG_QUEUE_T *queue, UINT32 val)
{
	int ret = RET_ERROR;

	queue->mutex = 1;

	MJPEG_PRINT(">>>> head[%d] tail[%d] val[%08x]\n", queue->head, queue->tail,
				val);

	if ((queue->tail - MSG_Q_SIZE) == queue->head) {
		MJPEG_ERROR("OverFlow!!\n");
		goto exit;
	}

	queue->tail++;
	queue->queue[queue->tail % MSG_Q_SIZE] = val;
	queue->count++;

	ret = RET_OK;

	MJPEG_PRINT("<<<< head[%d] tail[%d] count[%d]\n", queue->head, queue->tail,
				queue->count);
exit:
	queue->mutex = 0;
	return ret;
}

// Get from Queue.
// Mutex wait ( wait until isr() process whole interrupt.. )
UINT32 MJPEG_QueuePop(LXMJPEG_MSG_QUEUE_T *queue)
{
	UINT32 val = 0;

	QueueWait(queue);

	MJPEG_PRINT("head[%d] tail[%d] count[%d]\n", queue->head, queue->tail,
				queue->count);

	// Check for empty Queue
	if (QueueIsEmpty(queue)) {
		// Return 0 if queue is empty
		MJPEG_PRINT("Queue is Empty\n");
		goto exit;
	} else {
		queue->head++;
		val = queue->queue[queue->head % MSG_Q_SIZE];
	}
	queue->count--;
	MJPEG_PRINT("val = 0x%08x\n", val);

exit:
	return val;
}

// Get whole messgae from queue.
UINT32 MJPEG_QueuePopLoop(LXMJPEG_MSG_QUEUE_T *queue)
{
	UINT32 val = 0;

	while (!QueueIsEmpty(queue)) {
		val |= MJPEG_QueuePop(queue);
	}

	MJPEG_PRINT("val = 0x%08x\n", val);

	return val;
}
