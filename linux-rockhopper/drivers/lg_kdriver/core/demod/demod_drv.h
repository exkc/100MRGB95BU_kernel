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
 *  driver interface header for demod device. ( used only within kdriver )
 *	demod device will teach you how to make device driver with new platform.
 *
 *  @author		jeongpil.yun (jeongpil.yun@lge.com)
 *  @version	1.0
 *  @date		2009.12.30
 *
 *  @addtogroup lg1150_demod
 *	@{
 */

#ifndef	_DEMOD_DRV_H_
#define	_DEMOD_DRV_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "debug_util.h"
#include "demod_cfg.h"

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

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
extern	void 	DEMOD_PreInit(void);
extern	int     DEMOD_Init(void);
extern	void    DEMOD_Cleanup(void);

int  DEMOD_Mutex_Lock (const char * path, int line);
void DEMOD_Mutex_Unlock (const char * path, int line);

#define DEMOD_LockDevice()			{ if (RET_OK != DEMOD_Mutex_Lock(__FILE__, __LINE__)) { DEMOD_ERROR("failed LockDevice\n"); return RET_ERROR; } }
#define DEMOD_LockDevice_NoRet()	{ if (RET_OK != DEMOD_Mutex_Lock(__FILE__, __LINE__)) { DEMOD_ERROR("failed LockDevice\n"); return; } }
#define DEMOD_UnlockDevice()		{ DEMOD_Mutex_Unlock(__FILE__, __LINE__); }

void DEMOD_TASK_Open(void);
void DEMOD_TASK_Close(void);
int  DEMOD_TASK_OpenCount(void);

extern	void	DEMOD_PROC_Init(void);
extern	void	DEMOD_PROC_Cleanup(void);


/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern	int		g_demod_debug_fd;

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DEMOD_DRV_H_ */

/** @} */
