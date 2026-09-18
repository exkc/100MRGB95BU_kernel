/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 1999 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file vp_kwrap_bbd.h
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

#ifndef	_VP_KWRAP_BBD_H_
#define	_VP_KWRAP_BBD_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
//#include "de_kapi.h"
//#include "hdmi_kapi.h"
//#include "afe_kapi.h"

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
#ifdef V4L2_VSC_BBD_USE_PRIV
#else
typedef struct
{
	UINT16		x;	/**< horizontal Start Position in pixel [0,].*/
	UINT16		y;	/**< vertical	Start Position in pixel [0,].*/
	UINT16		w;	/**< horizontal Size(Width)    in pixel [0,].*/
	UINT16		h;	/**< vertical	Size(Height)   in pixel [0,].*/
} kwrap_vp_video_rect_t;

typedef struct
{
	kwrap_vp_video_rect_t org;
	kwrap_vp_video_rect_t act;
} kwrap_vp_active_video_window_t;

typedef struct {
	UINT32 reg_cnt;									///< register counter
	UINT32 step;									///< step
	UINT32 skip;									///< skip
	UINT32 addr[2];									///< addr : [0]ipp,[1]resv
	UINT32 data[2];									///< data : [0]ipp,[1]resv
	UINT32 abno[3];									///< abnormal : [0]x,[1]y,[2]resv
	UINT32 update;									///< update
	UINT32 enable;									///< enable
	UINT32 frame_cnt;								///< frame cnt
	UINT32 cnt_th;									///< cnt th
	UINT32 diff_th;									///< diff_th
	kwrap_vp_timing_info_t timing;					///< pBufTiming
	UINT32 bbd_pos;									///< bbd_position, 0:input,1:middle
	kwrap_vp_video_rect_t cur_bbd;					///< cur_bbd, x0,y0,x1,y1
	kwrap_vp_video_rect_t pre_bbd;					///< pre_bbd, x0,y0,x1,y1
	kwrap_vp_video_rect_t ret_bbd;					///< ret_bbd, result x0,y0,x1,y1
	kwrap_vp_video_rect_t dif_bbd;					///< dif_bbd, x0,y0,x1,y1
	UINT32 same_cnt;								///< same_cnt
	UINT32 same_mask;								///< same_mask
	kwrap_vp_video_rect_t pre_act[VP_PRE_ACT_NUM];	///< pre_act(from t-4 to t-1)
	kwrap_vp_video_rect_t pre_cb;					///< pre_callback
	kwrap_vp_active_video_window_t pre;				///< pre
	kwrap_vp_active_video_window_t cur;				///< cur
} kwrap_vp_active_info_t;

typedef void (*PFN_VP_ACTIVE_VIDEO_WINDOW_T) (UINT32 wId, kwrap_vp_active_video_window_t *window);
#endif

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int vp_kwrap_adjustpcauto_hsize(LX_AFE_ADJ_PC_T *pPCAdjust_Hsize_t);
int vp_kwrap_adjustpcauto_phase(LX_AFE_ADJ_PC_T *pPCAdjust_Phase_t);
int vp_kwrap_adjustpcauto_position(LX_AFE_ADJ_PC_T *pPCAdjust_Position_t);
int vp_kwrap_adjustpcauto_all(LX_AFE_ADJ_PC_T *pPCAdjust_t);

int vp_kwrap_getcvioffset(UINT32 *pXOffset, UINT32 *pYOffset);
int vp_kwrap_setcvioffset(UINT32 XOffset, UINT32 YOffset);
int vp_kwrap_setcvioffset_csample(UINT32 XOffset, UINT32 YOffset, LX_DE_SCALER_CSAMPLE_T c_sample);

#ifdef V4L2_VSC_BBD_USE_PRIV
#else
int vp_kwrap_initactivewin(void);
int vp_kwrap_uninitactivewin(void);
int vp_kwrap_getactivevideowindowcallback(void);
int vp_kwrap_registeractivevideowindowcallback(UINT32 vpSrcId, PFN_VP_ACTIVE_VIDEO_WINDOW_T callback);
int vp_kwrap_checkactivevideowindowmain(UINT32 vpSrcId, kwrap_vp_timing_info_t *pBufTiming);
int vp_kwrap_checkactivevideowindowsub(UINT32 vpSrcId, kwrap_vp_timing_info_t *pBufTiming);
void vp_kwrap_setactivevideowindbg(int dbg_level);
int vp_kwrap_getactivevideowindbg(void);
#endif

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

