#ifndef _V4L2_VSC_EVENT_H
#define _V4L2_VSC_EVENT_H

#include "vp_kwrap.h"
#include "linux/v4l2-ext/v4l2-ext-vsc.h"

#ifndef V4L2_EXT_VSC_INPUT_SRC_FB
#define V4L2_EXT_VSC_INPUT_SRC_FB (V4L2_EXT_VSC_INPUT_SRC_JPEG+1)
#endif

enum vsc_feedback_position {
	FB_NONE,        // fb disable (ATV Rec.)
	FB_WITHOUT_OSD,
	FB_WITH_OSD,
	FB_OSD_ONLY,
	FB_DISP,
	FB_HIST
};

int vsc_init_config(void);

// start VIDIOC_S_EXT_CTRLS
int vsc_open_info(BOOLEAN flag, UINT8 win, UINT8 open_count);
int vsc_set_input(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_connect_info *p);
int vsc_set_win_info(BOOLEAN flag, UINT8 win, UINT8 ani, struct v4l2_ext_vsc_win_region *p);
int vsc_set_sub_mode(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_win_prop *p);
int vsc_set_zorder(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_zorder *p);
int vsc_set_zorder_info(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_zorder_info *p);
int vsc_set_latency_pattern(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_latency_pattern_info *p);
int vsc_set_vdo_mode(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_vdo_mode *p);
int vsc_set_read_frame_buffer(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_pixel_color_info *p);
int vsc_set_quad_mode(BOOLEAN flag, UINT8 win, unsigned int *p);

// start VIDIOC_S_CTRL
int vsc_set_mute(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_freeze(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_pattern(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_frame_delay(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_adaptives_stream(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_rgb444(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_hdr_ipc_type(UINT8 wid, UINT32 ipc_mode, UINT32 from);
int vsc_set_hdr_type(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_cvi_frz(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_sub_occupy(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_local_mute(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_ipc_mode(BOOLEAN flag, UINT8 win, UINT32 *p);

int vsc_set_read_cvi_pixel(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_pixel_color_info *p);
int v4l2_vsc_switchmcu(int id);
int v4l2_vsc_keep_submode(int flag);
void vsc_v4l2_vp_thread(void);
void vsc_v4l2_vp_init(void);
struct v4l2_ext_vsc_input_src_info  vsc_v4l2_get_input(UINT8 win);
int vsc_get_timinginfo(UINT8 win, kwrap_vp_timing_info_t *ti);
int vsc_check_vrr_freq(unsigned int *p);
int vsc_set_fbpos(enum vsc_feedback_position pos);
int vsc_set_orbit_policy(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_orbit_policy *p);
int vsc_set_orbit_window(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_orbit_window *p);
int vsc_set_orbit_move(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_orbit_move *p);
int vsc_check_csc_err(char *str);
int vsc_check_fw_err(char *str);
int vsc_check_cvi_err(char *str);
int vsc_handle_darc_event(void);
int vsc_set_aspectratio_policy(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_aspectratio_policy *p);
int vsc_set_scanmode(BOOLEAN flag, UINT8 win, SINT32 *p);
int vsc_set_pixeltopixel(BOOLEAN flag, UINT8 win, UINT32 *p);
int vsc_get_submode(unsigned int *sub_mode);
int vsc_get_dev_info(int win, int param);

#endif //_V4L2_VSC_EVENT_H
