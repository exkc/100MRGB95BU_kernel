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
 *  main driver implementation for ucom device.
 *	ucom device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_ucom
 */


#ifndef	_UCOM_DRV_H_
#define	_UCOM_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "debug_util.h"
#include "ucom_cfg.h"
#include "ucom_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	KDRV_UCOM_PRINT(format, args...)		DBG_PRINT( g_ucom_debug_fd, UCOM_MSG_NOTI, format, ##args)
#define	KDRV_UCOM_TRACE(format, args...)		DBG_PRINT( g_ucom_debug_fd, UCOM_MSG_TRACE, format, ##args)
#define	KDRV_UCOM_DEBUG(format, args...)		DBG_PRINT( g_ucom_debug_fd, UCOM_MSG_DEBUG, format, ##args)
#define	KDRV_UCOM_ERROR(format, args...)		DBG_PRINT( g_ucom_debug_fd, UCOM_MSG_ERROR, format, ##args)
#define	KDRV_UCOM_NOTI(format, args...)		DBG_PRINT( g_ucom_debug_fd, UCOM_MSG_NOTI, format, ##args)


#define UCOM_CHECK_CODE(__checker,__if_action,fmt,args...)   \
			 __CHECK_IF_ERROR(__checker, KDRV_UCOM_ERROR, __if_action , fmt, ##args )

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum {
	UCOM_MSG_ERROR = LX_LOGM_LEVEL_ERROR,
	UCOM_MSG_WARN = LX_LOGM_LEVEL_WARNING,
	UCOM_MSG_NOTI = LX_LOGM_LEVEL_NOTI,
	UCOM_MSG_INFO = LX_LOGM_LEVEL_INFO,
	UCOM_MSG_DEBUG = LX_LOGM_LEVEL_DEBUG,
	UCOM_MSG_TRACE = LX_LOGM_LEVEL_TRACE,
	UCOM_MSG_NORMAL = (LX_LOGM_LEVEL_TRACE + 1),	// print
	UCOM_MSG_VSYNC = (LX_LOGM_LEVEL_TRACE + 2),		// vsync
	UCOM_MSG_TIMER = (LX_LOGM_LEVEL_TRACE + 3),		// timer
	UCOM_MSG_INTER = (LX_LOGM_LEVEL_TRACE + 4),		// interrupt

	UCOM_MSG_INDEX_COUNT
} UCOM_MSG_TYPE_T;

#define UCOM_CHECK_ERROR(__checker,__if_action,fmt,args...)   \
		                            __CHECK_IF_ERROR(__checker, KDRV_UCOM_ERROR, __if_action , fmt, ##args )



typedef struct
{
	void			(*init)				(void);
	int				(*ioctl)			(unsigned int cmd, unsigned long arg, struct file *file);
	int				(*suspend)			(void);
	int				(*resume)			(void);
	struct file * (*getfp)			(void);
	int				(*spiread) ( UINT8 * addr,  UINT8 * data , UINT8  num );
	int				(*spiwrite) ( UINT8 * addr,  UINT8 * data , UINT8  num );
} ucom_driver_t;

typedef struct
{
	void			(*init)		(void);
	void			(*cleanup)	(void);
} ucom_proc_t;

extern struct file *g_ucomfp;
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void     UCOM_PreInit(void);
extern	int      UCOM_Init(void);
extern	void     UCOM_Cleanup(void);
int		UCOM_Init(void);
void	UCOM_Cleanup(void);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_ucom_debug_fd;
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _UCOM_DRV_H_ */

/** @} */
