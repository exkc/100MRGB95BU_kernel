#ifndef _V4L2_VT_H
#define _V4L2_VT_H
#if 0
// The number of capture video device is 60.

#define V4L2_EXT_DEV_PATH_CAPTURE   "/dev/video60"

/* User-class control Bases */
#define V4L2_CID_USER_EXT_CAPTURE_BASE (V4L2_CID_USER_BASE + 0x2100)

/* Capture class control IDs */
#define V4L2_CID_EXT_CAPTURE_CAPABILITY_INFO (V4L2_CID_USER_EXT_CAPTURE_BASE + 0)
#define V4L2_CID_EXT_CAPTURE_PLANE_INFO (V4L2_CID_USER_EXT_CAPTURE_BASE + 1)
#define V4L2_CID_EXT_CAPTURE_VIDEO_WIN_INFO (V4L2_CID_USER_EXT_CAPTURE_BASE + 2)
#define V4L2_CID_EXT_CAPTURE_PLANE_PROP (V4L2_CID_USER_EXT_CAPTURE_BASE + 3)
#define V4L2_CID_EXT_CAPTURE_FREEZE_MODE (V4L2_CID_USER_EXT_CAPTURE_BASE + 4)
#define V4L2_CID_EXT_CAPTURE_DONE_USER_PROCESSING (V4L2_CID_USER_EXT_CAPTURE_BASE + 5)

/* Capture class subscription IDs */
#define V4L2_CID_EXT_CAPTURE_SUBSCRIBE_FRAME_READY (V4L2_CID_USER_EXT_CAPTURE_BASE + 30)

/* Capture class subscription types */
#define V4L2_EVENT_PRIVATE_EXT_CAPTURE_BASE      ( V4L2_EVENT_PRIVATE_START + 0x2100 )
#define V4L2_EVENT_PRIVATE_EXT_CAPTURE_EVENT     ( V4L2_EVENT_PRIVATE_EXT_CAPTURE_BASE + 1 )
#endif
#define V4L2_EXT_DEV_NO_VT     60

#define __ALIGN_MASK_VT(x, mask)        (((x) + (mask)) & ~(mask))
#define __ALIGN_VT(x, a)           __ALIGN_MASK_VT(x, (typeof(x))(a) - 1)
#define ALIGN_X(width,x)          __ALIGN_VT(width, x)

int v4l2_vt_register(void *arg);
#endif //_V4L2_VT_H
