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
 *  driver interface header for mjpeg device. ( used only within kdriver )
 *	MJPEG device will teach you how to make device driver with new platform.
 *
 *  @author		youngwoo.jin (youngwoo.jin@lge.com)
 *  @version	1.0
 *  @date		2011.04.09
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

#ifndef _MJPEG_DRV_H_
#define _MJPEG_DRV_H_

/*-----------------------------------------------------------------------------
        Control Constants
-----------------------------------------------------------------------------*/
#define MJPEG_USE_ENCODE_QUALITY_PARAM

/*-----------------------------------------------------------------------------
    File Inclusions
-----------------------------------------------------------------------------*/
#include "debug_util.h"
#include "logm.h"
#include "mjpeg_cfg.h"
#include "mjpeg_kapi.h"

/*-----------------------------------------------------------------------------
  Constant Definitions
  -----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
  Macro Definitions
  -----------------------------------------------------------------------------*/
#define MJPEG_ERROR(format, args...) logm_error(jpeg, format, ##args)
#define MJPEG_WARN(format, args...) logm_warning(jpeg, format, ##args)
#define MJPEG_NOTI(format, args...) logm_noti(jpeg, format, ##args)
#define MJPEG_INFO(format, args...) logm_info(jpeg, format, ##args)
#define MJPEG_DEBUG(format, args...) logm_debug(jpeg, format, ##args)
#define MJPEG_TRACE(format, args...) logm_trace(jpeg, format, ##args)
#define MJPEG_PRINT(format, args...) logm_trace(jpeg, format, ##args)

#define MJPEG_CHECK_ERROR(__checker, __if_action, fmt, args...)                \
	__CHECK_IF_ERROR(__checker, MJPEG_ERROR, __if_action, fmt, ##args)

/*-----------------------------------------------------------------------------
  Type Definitions
  -----------------------------------------------------------------------------*/
typedef enum {
	LX_MJPEG_PARTIAL_BUFFER0 = 0,
	LX_MJPEG_PARTIAL_BUFFER1 = 1,
	LX_MJPEG_PARTIAL_BUFFER2 = 2,
	LX_MJPEG_PARTIAL_BUFFER3 = 3,
} LX_MJPEG_PARTIAL_BUFFER_T;

typedef struct {
	struct list_head list_head;
	spinlock_t work_lock;
	struct work_struct work;

	struct workqueue_struct *WorkQueue;
} MJPEG_WORK_QUEUE_T;

typedef struct {
	struct list_head list;
	UINT32 val;
} MJPEG_LIST_T;

/*-----------------------------------------------------------------------------
  Extern Function Prototype Declaration
  -----------------------------------------------------------------------------*/
extern void MJPEG_PreInit(void);
extern int MJPEG_Init(void);
extern void MJPEG_Cleanup(void);

int MJPEG_AddNotify(UINT32 intr);
void MJPEG_WakeupNotify(void);

/*-----------------------------------------------------------------------------
  Extern Variables
  -----------------------------------------------------------------------------*/

#endif /* _MJPEG_DRV_H_ */

/** @} */
