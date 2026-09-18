/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file hdr_v4l2_cmn.h
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author	harish.singh (harish.singh@lge.com)
 *  @version    1.0
 *  @date       2019-05-01
 *  @note       It maintains V4L2 related definitions for Dolby HDR
 *			Internal to SIC implementation.
 */

#ifndef	_HDR_V4L2_CMN_H_
#define	_HDR_V4L2_CMN_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/videodev2.h>
#include <linux/v4l2-controls.h>
#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "linux/v4l2-ext/v4l2-ext-panel.h"
//#include "linux/v4l2-ext/v4l2-ext-pq.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"
#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

#ifdef HDR_HW5_SUPPORT
#define K_DOVI_SW_MAJOR_NUM 32
#define K_DOVI_SW_MINOR_NUM 32
#else
#define K_DOVI_SW_MAJOR_NUM 28
#define K_DOVI_SW_MINOR_NUM 12
#endif
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

typedef enum HDR_MOVIE_MODES{
	HDR_MOVIE_VIVID = 0,
	HDR_MOVIE_BRIGHT,
	HDR_MOVIE_DARK,
	HDR_MOVIE_STANDARD,
	HDR_MOVIE_GAME,
	HDR_MOVIE_NONE
} E_HDR_MOVIE_MODES;

typedef enum _ePQMode{
	MOVIE_DARK=0,
	MOVIE_BRIGHTNESS,
	VIVID_MODE,
	STANDRD_MODE,
	GAME_MODE,
	NONE_PQ
}ePQMode;
typedef struct __dolby_dbg_data
{
	UINT8 ucwinId;
	UINT8 ucDbgValue;
	UINT8 ucDolbyEnable;
	UINT8 ucMode;
	UINT8 ucconfigpath[255];
	UINT8 funcnum;
	UINT8 ucEnbestpq;
	int nMDDumpEnd;
}DOLBY_DBG_DATA_T;
typedef struct _S_DOLBY_Level_11_MD {
	UINT8 content_type;
	UINT8 desired_white_point;
	UINT8 wp_valid;
	UINT8 L11_byte2;
	UINT8 L11_byte3;
}DOLBY_LEVEL_L11_DATA_T;

#define V4L2_EXT_DEV_PATH_DHDR "/dev/video240"

#define V4L2_CID_USER_EXT_DOLBY_BASE (V4L2_CID_USER_BASE + 0x10000)
	/* Start and stop event */
#define V4L2_CID_EXT_VSC_SUBSCRIBE_DHDR_START (V4L2_CID_USER_BASE + 1)
#define V4L2_CID_EXT_VSC_SUBSCRIBE_DHDR_STOP (V4L2_CID_USER_BASE + 2)
	/* PQ Related Events */
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_DHDR_PQ_INIT (V4L2_CID_USER_BASE + 3)
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_DHDR_PQ_MODE (V4L2_CID_USER_BASE + 4)
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_DHDR_PQ_SUBMODE (V4L2_CID_USER_BASE + 5)
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_DHDR_PQ_AMBIENT (V4L2_CID_USER_BASE + 6)
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_DHDR_PQ_GDDELAY (V4L2_CID_USER_BASE + 7)
	/* Config,GD Events */
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_DHDR_CONFIG (V4L2_CID_USER_BASE + 8)
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_DHDR_GD_DELAY (V4L2_CID_USER_BASE + 9)
	/* Get timing Info CID */
#define V4L2_CID_EXT_VSC_GET_TIMING_INFO (V4L2_CID_USER_BASE + 10)
	/* Debug Event  */
#define V4L2_CID_EXT_DOLBY_SUBSCRIBE_DHDR_DEBUG (V4L2_CID_USER_BASE + 11)
#define V4L2_CID_EXT_DHDR_INIT (V4L2_CID_USER_BASE + 12)
#define V4L2_CID_EXT_DHDR_UNINIT (V4L2_CID_USER_BASE + 13)
#define V4L2_CID_EXT_DHDR_GET_HDMI_MD (V4L2_CID_USER_BASE + 14)
#define V4L2_CID_EXT_DHDR_GET_OTT_MD_INTERRUPT (V4L2_CID_USER_BASE + 15)
#define V4L2_CID_EXT_DHDR_MD_UNBLOCK (V4L2_CID_USER_BASE + 16)
#define V4L2_CID_EXT_VPQ_SUBSCRIBE_DHDR_PQ_PD (V4L2_CID_USER_BASE + 17)
/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _HDR_V4L2_CMN_H_ */

