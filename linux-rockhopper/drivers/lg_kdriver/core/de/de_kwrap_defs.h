/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file de_kwrap_defs.h
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     dongho7.park (dongho7.park@lge.com)
 *  @version    1.0
 *  @date       2010-02-07
 *  @note       Additional information.
 */

#ifndef	_DE_KWRAP_DEFS_H_
#define	_DE_KWRAP_DEFS_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "de_kapi.h"

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
/* debug message wrapper */


#define DE_CHECK_CODE(__checker,__if_action,fmt,args...)   \
						__CHECK_IF_ERROR(__checker, DE_ERROR, __if_action , fmt, ##args )

#define DE_BREAK_WRONG(arg)           { printf("[de_kadp]  %s : %d Wrong (0x%x)\n", __F__, __L__,arg); ret = RET_ERROR; break; }
//#define CHECK_NULL(ptr)  			if (!ptr) { DE_ERROR("[de_kadp] %s is Null\n", #ptr); return RET_ERROR; }
#define CHECK_DEV_FD(ptr) 		if (ptr<0) { DE_ERROR("[kadp_de] Don't open DE device\n"); return RET_ERROR; }


#define DE_WIN_BlANK_USE	// use winblank from DE F/W rev.25048
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

typedef struct
{
	int	dev_fd;
	void *dev_mtx;	 /* mutex(semaphore) for DE */
	void *dev_shmem; /* shared memory for DE */
	int	ref_cnt;	 /* refrence count */
}
lx_de_ctx_t;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DE_KADP_DEFS_H_ */

