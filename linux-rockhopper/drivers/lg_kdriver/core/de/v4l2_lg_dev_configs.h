#ifndef _V4L2_LG_CONFIGS_H
#define _V4L2_LG_CONFIGS_H

#include <linux/videodev2.h>
#include <linux/version.h>


#define MAX_FRAME_INTER_CNT	1
#define MAX_FRAME_SIZE_CNT	1
#define MAX_FORMAT_CNT_MP   3 
#define MAX_FORMAT_CNT_SP	2
#define MAX_CAPTURE_DEVS	8
#define MAX_CNTRL_CNT		1
#define MAX_MENU_CNT		1

#define UNKNOWN_STR "UNKNOWN"
#define GPS_VIDEO_DEF_FORMAT		V4L2_PIX_FMT_YVU420

#define MAX_VT_BUF 	 5  /*Max buffers supported */
#define MIN_VT_BUF 	 1  /*Min buffers supported */

#define MAX_GPS_BUF  3  /* Max GPS buffers */
#define MIN_GPS_BUF  3  /* Min GPS buffers */
//#define MAX_GPS_BUF  2  /* Max GPS buffers */
//#define MIN_GPS_BUF  2  /* Min GPS buffers */

#define MAX_VT_PLANE 2  /* As of now only semiplaner is supported per buffer */

#define MAX_VT_PLANE_WIDTH	3840
#define MAX_VT_PLANE_HEIGHT	2160

#define MIN_VT_PLANE_WIDTH	320
#define MIN_VT_PLANE_HEIGHT	240

#define MAX_VT_BPP	1
#define MAX_VT_PLANE_STRIDE	(MAX_VT_PLANE_WIDTH * MAX_VT_BPP)

#define MAX_VTV_OUT_PLANE_WIDTH	1920
#define MAX_VTV_OUT_PLANE_HEIGHT 1080
#define MAX_VTV_OUT_PLANE_STRIDE	(MAX_VTV_OUT_PLANE_WIDTH * MAX_VT_BPP)
#define FAKE_ADDRESS 0xFFFFFFFFL

#define LG_MEM_STRIDE_STEP 64
/* 90 KHz clock */
#define LG_VDEC_CLOCK 90000

#define DEF_GPS_BUFS MAX_GPS_BUF
#define DEF_GPS_PLANES MAX_VT_PLANE
#define DEF_GPS_CAP_INPUT 	0
#define DEF_GPS_CAP_HEIGHT	1080
#define DEF_GPS_CAP_WIDTH	1920
#define DEF_GPS_CAP_FIELD_ORDER	V4L2_FIELD_NONE
#define DEF_GPS_CAP_COLORSPACE V4L2_COLORSPACE_SRGB
#define DEF_GPS_CAP_PLANES	2
#define DEF_GPS_CAP_FORMAT	V4L2_PIX_FMT_NV12M
#define DEF_GPS_CAP_COL_ENCODING V4L2_YCBCR_ENC_DEFAULT
#define DEF_GPS_CAP_QUATIZATION V4L2_QUANTIZATION_DEFAULT
#define DEF_GPS_CAP_XFER_FUN	V4L2_XFER_FUNC_DEFAULT

/* Extended control IDs */
//#define V4L2_CID_USER_EXT_GPSCALER_BASE   (V4L2_CID_USER_BASE + 0xA000)
//#define V4L2_CID_EXT_GPSCALER_MAX_FRAME_SIZE   (V4L2_CID_USER_EXT_GPSCALER_BASE + 0x01)

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#define GET_SYSCLOCK_FRM_PTS(PTS,timevalue) \
	{ timevalue = (PTS/LG_VDEC_CLOCK)*NSEC_PER_SEC + (((__u64)(PTS % LG_VDEC_CLOCK)*1000000)/LG_VDEC_CLOCK)*NSEC_PER_USEC;}
#else
#define GET_SYSCLOCK_FRM_PTS(PTS,sec,usec) \
	{ sec = PTS/LG_VDEC_CLOCK; usec = (((__u64)(PTS % LG_VDEC_CLOCK)*1000000))/LG_VDEC_CLOCK;}
#endif

struct format_info {
	__u32 stride;
	__u32 pixel_fmt;
	__u32 field_order;
	__u32 col_space;
	__u32 max_width;
	__u32 max_height;
	__u32 alloc_buf_width;
	__u32 alloc_buf_height;
	__u8  num_planes;
	__u8  num_buf;
	__u8  alpha;
	union {
		__u8 yCbCr_enc;
		__u8 hsv_enc;
		} encoding;
	__u8 quantization;
	__u8 xfer_fun;
};

enum gps_input {
	VDEC0,
	VDEC1,
	VDEC2,
	VDEC3,
};

struct frame_interval_info {
	__u32 type; //enum v4l2_frmivaltypes
	union {
		struct v4l2_fract disc_intrval;
		struct v4l2_frmival_stepwise step_interval;
	} interval;
};

struct frame_size_info {
	__u32 type; //enum v4l2_frmsize type
	union {
		struct v4l2_frmsize_discrete disc_frm;
		struct v4l2_frmsize_stepwise step_frm;
	} size;
	int frm_interval_index[MAX_FRAME_INTER_CNT];
};

struct pixel_format_info {
	__u32 pixel_format; //image format identifier
	__u8 desc[32];
	__u32 frame_size_indexes[MAX_FRAME_SIZE_CNT];
    __u8 num_planes;
};

struct capture_device_info {
	__u8 name[32];
	__u32 type;         // V4L2 input type [V4L2_INPUT_TYPE_CAMERA]
	v4l2_std_id std;    //video standards [OR all]
	__u32 status;       //Default V4L2_IN_ST_NO_POWER
	__u32 capabilities; // check input capability
	__u32 cap_format_indexes[MAX_FORMAT_CNT_MP];
};

#endif //_V4L2_LG_CONFIGS_H
