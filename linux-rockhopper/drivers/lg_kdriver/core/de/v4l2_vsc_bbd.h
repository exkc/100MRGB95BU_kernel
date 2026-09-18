/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file v4l2_vsc_bbd.h
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     sh.myoung (sh.myoung@lge.com)
 *  @version    1.0
 *  @date       2012-05-01
 *  @note       Additional information.
 *  @note	Mapped to kernel space for SEE TV (harish.singh@lge.com)
 */

#ifndef	_V4L2_VSC_BBD_H_
#define	_V4L2_VSC_BBD_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
extern void v4l2_vsc_bbd_proc_init(struct proc_dir_entry *entry);
extern int v4l2_vsc_bbd_init(void);
extern int v4l2_vsc_bbd_update_info(int wid,void *fh);
extern int v4l2_vsc_bbd_update_subscribe(int wid, unsigned int id, int flag, void *fh);
extern int v4l2_vsc_bbd_check_subscribed(int wid);
extern int v4l2_vsc_bbd_noti_poll(int wid);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _V4L2_VSC_BBD_H_ */