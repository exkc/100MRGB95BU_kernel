/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2025 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_SCREENCAPTURE_H
#define _V4L2_EXT_SCREENCAPTURE_H

#include <linux/v4l2-controls.h>

#define V4L2_EXT_DEV_NO_CAPTURE 60
#define V4L2_CID_USER_EXT_CAPTURE_BASE (V4L2_CID_USER_BASE + 0x2100)
#define V4L2_EXT_DEV_PATH_CAPTURE "/dev/video60"

enum v4l2_ext_capture_video_frame_buffer_pixel_format {
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_PLANAR = 0,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_SEMI_PLANAR,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_INTERLEAVED,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_PLANAR,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_SEMI_PLANAR,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_INTERLEAVED,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_PLANAR,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_SEMI_PLANAR,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_INTERLEAVED,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_RGB,
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_ARGB
};

enum v4l2_ext_capture_video_frame_buffer_plane_num {
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PLANE_INTERLEAVED =
        1, // INTERLEAVED has one plane.
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PLANE_SEMI_PLANAR, // SEMI PLANAR has
                                                           // two plane.
    V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PLANE_PLANAR // PLANAR has three plane.
};

struct v4l2_ext_capture_rect {
    unsigned short x;
    unsigned short y;
    unsigned short w;
    unsigned short h;
};

struct v4l2_ext_capture_capability_info {
    unsigned int flags;
    unsigned int scale_up_limit_w;
    unsigned int scale_up_limit_h;
    unsigned int scale_down_limit_w;
    unsigned int scale_down_limit_h;
    unsigned int num_video_frame_buffer;
    struct v4l2_ext_capture_rect max_res;
    enum v4l2_ext_capture_video_frame_buffer_plane_num num_plane;
    enum v4l2_ext_capture_video_frame_buffer_pixel_format pixel_format;
};

/* Flags for the 'flags' field in struct v4l2_ext_capture_capability_info. */
#define V4L2_EXT_CAPTURE_CAP_INPUT_VIDEO_DEINTERLACE 0x0001
#define V4L2_EXT_CAPTURE_CAP_DISPLAY_VIDEO_DEINTERLACE 0x0002
#define V4L2_EXT_CAPTURE_CAP_SCALE_UP 0x0004
#define V4L2_EXT_CAPTURE_CAP_SCALE_DOWN 0x0008
#define V4L2_EXT_CAPTURE_CAP_DIVIDE_FRAMERATE 0x0010
#define V4L2_EXT_CAPTURE_CAP_VIDEOTOVIDEO 0x0020

struct v4l2_ext_capture_plane_info {
    unsigned int stride;
    struct v4l2_ext_capture_rect plane_region;
    struct v4l2_ext_capture_rect active_region;
};

enum v4l2_ext_capture_video_scan_type {
    V4L2_EXT_CAPTURE_VIDEO_INTERLACED = 0,
    V4L2_EXT_CAPTURE_VIDEO_PROGRESSIVE
};

struct v4l2_ext_capture_video_win_info {
    enum v4l2_ext_capture_video_scan_type type;
    struct v4l2_ext_capture_rect in;
    struct v4l2_ext_capture_rect out;
    struct v4l2_ext_capture_rect panel;
};

enum v4l2_ext_capture_location {
    V4L2_EXT_CAPTURE_SCALER_INPUT = 0, // for VTV - before de-interlace
    V4L2_EXT_CAPTURE_SCALER_OUTPUT,
    V4L2_EXT_CAPTURE_DISPLAY_OUTPUT,
    V4L2_EXT_CAPTURE_BLENDED_OUTPUT,
    V4L2_EXT_CAPTURE_OSD_OUTPUT,
    V4L2_EXT_CAPTURE_SUB_SCALER_OUTPUT
};

enum v4l2_ext_capture_buf_location {
    V4L2_EXT_CAPTURE_INPUT_BUF = 0,
    V4L2_EXT_CAPTURE_OUTPUT_BUF
};

struct v4l2_ext_capture_plane_prop {
    enum v4l2_ext_capture_location l;
    struct v4l2_ext_capture_rect plane;
    int buf_count;
};

struct v4l2_ext_capture_freeze_mode {
    int plane_index;
    unsigned char val;
};

struct v4l2_ext_capture_physical_memory_info {
    int buf_index;
    union {
        unsigned int *y;
        unsigned int compat_y_data;
        unsigned long long y_sizer;
    };

    union {
        unsigned int *c;
        unsigned int compat_c_data;
        unsigned long long c_sizer;
    };
    enum v4l2_ext_capture_buf_location buf_location;
};

struct v4l2_ext_histogram_data {
    unsigned int areaId; // id of the area this histogram was computed.
    unsigned short r[256];
    unsigned short g[256];
    unsigned short b[256];
};

//
// videotexture class control IDs
//

/**
 * @brief Get the capabilities.
 *
 * @rst
 * Functional Requirements
 *   It is a command to obtain Capture related Limitation and Capability
 *   information inherent to SoC after a video device is opened. Recommend
 *   V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_SEMI_PLANAR or
 *   V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_SEMI_PLANAR for
 *   v4l2_ext_capture_video_frame_buffer_pixel_format type, and
 *   V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PLANE_SEMI_PLANAR for
 *   v4l2_ext_capture_video_frame_buffer_plane_num.
 *
 *   Explanation for flags
 *     * State 1 : While the interlace signal comes in the SoC.
 *     * State 2 : the frame size is 1280x720i@120hz(fps)
 *     * State 3 : the size of one field is 540.
 *     * State 4 : when user client captures some frame.
 *
 *   #define V4L2_EXT_CAPTURE_CAP_INPUT_VIDEO_DEINTERLACE 0x0001
 *
 *   - If the scan type of captured frame on V4L2_EXT_CAPTURE_SCALER_OUTPUT is
 *     progressive, you should set this bit in the variable of flags. The frame
 *     size of height is 720.
 *   - If the scan type of captured frame on V4L2_EXT_CAPTURE_SCALER_OUTPUT is
 *     still interlace because the H/W block of capture position is located before
 *     the H/W block of de-interlace, you should unset this bit in the variable of
 *     flags. The frame size of height is 360.
 *
 *   #define V4L2_EXT_CAPTURE_CAP_DISPLAY_VIDEO_DEINTERLACE 0x0002
 *
 *   - If the scan type of captured frame on V4L2_EXT_CAPTURE_DISPLAY_OUTPUT is
 *     progressive, you should set this bit in the variable of flags. The frame
 *     size of height is 720.
 *   - If the scan type of captured frame on V4L2_EXT_CAPTURE_DISPLAY_OUTPUT is
 *     still interlace because the H/W block of capture position is located before
 *     the H/W block of de-interlace, you should unset this bit in the variable of
 *     flags. The frame size of height is 360.
 *
 *   #define V4L2_EXT_CAPTURE_CAP_SCALE_UP 0x0004
 *
 *   - When user client request the size of capture frame with 1920x1080, if the
 *     vendor can capture those size after up-scaling, you should set this nit in
 *     the variable of flags.
 *
 *   #define V4L2_EXT_CAPTURE_CAP_SCALE_DOWN 0x0008
 *
 *   - When user client request the size of capture frame with 640x480, if the
 *     vendor can capture those size after down-scaling, you should set this nit
 *     in the variable of flags.
 *
 *   #define V4L2_EXT_CAPTURE_CAP_DIVIDE_FRAMERATE 0x0010
 *
 *   - When user client request to divide the fps of capture frame to 60hz or
 *     30hz, if the vendor can do dividing the fps, you should set this nit in the
 *     variable of flags.
 *
 *   #define V4L2_EXT_CAPTURE_CAP_VIDEOTOVIDEO 0x0020
 *
 *   - If the driver supports the feature of VTV, please set this bit to '1'.
 *     Currently LG chip only supports the VTV feature in the model specification
 *     on webOS5.0 of LG product. In case of other vendors, please set this bit to
 *     '0'.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   The scale up/down and the dividing framerate must be supported.
 *   V4L2_EXT_CAPTURE_CAP_VIDEOTOVIDEO only needs to be supported by LG SoC.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_CAPABILITY_INFO
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_capture_video_frame_buffer_pixel_format
 *     {
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_PLANAR = 0,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_SEMI_PLANAR,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV420_INTERLEAVED,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_PLANAR,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_SEMI_PLANAR,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV422_INTERLEAVED,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_PLANAR,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_SEMI_PLANAR,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_YUV444_INTERLEAVED,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_RGB,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PIXEL_FORMAT_ARGB
 *     };
 *
 *     enum v4l2_ext_capture_video_frame_buffer_plane_num
 *     {
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PLANE_INTERLEAVED = 1,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PLANE_SEMI_PLANAR,
 *         V4L2_EXT_CAPTURE_VIDEO_FRAME_BUFFER_PLANE_PLANAR
 *     };
 *
 *     struct v4l2_ext_capture_rect
 *     {
 *         unsigned short x; // horizontal start position
 *         unsigned short y; // vertical start position
 *         unsigned short w; // horizontal size(width)
 *         unsigned short h; // vertical size(height)
 *     };
 *
 *     struct v4l2_ext_capture_capability_info
 *     {
 *         unsigned int flags;
 *         unsigned int scale_up_limit_w;
 *         unsigned int scale_up_limit_h;
 *         unsigned int scale_down_limit_w;
 *         unsigned int scale_down_limit_h;
 *         unsigned int num_video_frame_buffer;
 *         struct v4l2_ext_capture_rect max_res;
 *         enum v4l2_ext_capture_video_frame_buffer_plane_num num_plane;
 *         enum v4l2_ext_capture_video_frame_buffer_pixel_format pixel_format;
 *     };
 *
 *     // Flags for the 'flags' field in struct v4l2_ext_capture_capability_info
 *     #define V4L2_EXT_CAPTURE_CAP_INPUT_VIDEO_DEINTERLACE 0x0001
 *     #define V4L2_EXT_CAPTURE_CAP_DISPLAY_VIDEO_DEINTERLACE 0x0002
 *     #define V4L2_EXT_CAPTURE_CAP_SCALE_UP 0x0004
 *     #define V4L2_EXT_CAPTURE_CAP_SCALE_DOWN 0x0008
 *     #define V4L2_EXT_CAPTURE_CAP_DIVIDE_FRAMERATE 0x0010
 *     #define V4L2_EXT_CAPTURE_CAP_VIDEOTOVIDEO 0x0020
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_capture_capability_info vt_capability_info;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&vt_capability_info, 0, sizeof(struct v4l2_ext_capture_capability_info));
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count      = 1;
 *     ext_controls.controls   = &ext_control;
 *
 *     ext_controls.controls->id = V4L2_CID_EXT_CAPTURE_CAPABILITY_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_capture_capability_info);
 *     ext_controls.controls->ptr = (void*)&vt_capability_info;
 *     ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_CAPABILITY_INFO                                   \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 0)

/**
 * @brief Get plane information.
 *
 * @rst
 * Functional Requirements
 *   This is a command for obtaining information on a plane (VFOD (Video Frame
 *   Output Device)). Basic plane size information and frame size information
 *   stored in the plane are returned. This command can be used at any time in the
 *   user client without any command or dependency when the VT Video Device is
 *   open.
 *
 *   1. unsigned int stride;
 *    - This value should be same with width or bigger than height.
 *
 *   2. struct v4l2_ext_capture_rect plane_region;
 *    - Plane size in driver side. The value of x and y are always '0'.
 *
 *   3. struct v4l2_ext_capture_rect active_region;
 *    - This values are current active size in plane.
 *      a. If plane size is 3840x2160 and the active size in plane buffer
 *      1920x540(interlace), you should return 1920x540 also x, y.
 *      b. If plane size is 3840x2160 and the active size in plane buffer
 *      1920x1080(progressive), you should return 1920x1080 also x, y.
 *      c. The status is that plane size is 3840x2160 and source input size is
 *      1920x1080(progressive) or 1920x540(interlace) and aspect ratio 4:3.
 *        - If the active size in plane buffer be calculated by applying a ratio
 *          of 4:3, you should return the calculated value.
 *        - If the active size in plane buffer is not related to aspect ratio,
 *          you should return the active size in plane buffer
 *          1920x1080(progressive) or 1920x540(interlace) also x, y.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_PLANE_INFO
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_capture_rect
 *     {
 *         unsigned short x; // horizontal start position
 *         unsigned short y; // vertical start position
 *         unsigned short w; // horizontal size(width)
 *         unsigned short h; // vertical size(height)
 *     };
 *
 *    struct v4l2_ext_capture_plane_info
 *    {
 *        unsigned int stride;
 *        struct v4l2_ext_capture_rect plane_region;
 *        struct v4l2_ext_capture_rect active_region;
 *    };
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_capture_plane_info vt_palne_info;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     int ret;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *
 *     ext_controls.ctrl_class     = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count          = 1;
 *     ext_controls.controls       = &ext_control;
 *     ext_controls.controls->id   = V4L2_CID_EXT_CAPTURE_PLANE_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_capture_plane_info);
 *     ext_controls.controls->ptr  = (void *)&vt_palne_info;
 *
 *     ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_PLANE_INFO (V4L2_CID_USER_EXT_CAPTURE_BASE + 1)

/**
 * @brief Set video window.
 *
 * @rst
 * Functional Requirements
 *   This is a command for obtaining information on the current input, output
 *   video, and panel size. This command can be used at any time in the User
 *   Client without any command or dependency when the VT Video Device is open.
 *   User client can read(VIDIOC_G_EXT_CTLRS) only when user client set the
 *   capture location to V4L2_EXT_CAPTURE_SCALER_OUTPUT or
 *   V4L2_EXT_CAPTURE_DISPLAY_OUTPUT. In this case, the values of the structure
 *   are used as shown below.
 *
 *   1. struct v4l2_ext_capture_rect in;
 *    - Current input resolution of scaler.
 *    - Read only
 *
 *   2. struct v4l2_ext_capture_rect out;
 *    - Current output resolution of scaler.
 *    - Read only
 *
 *   3. struct v4l2_ext_capture_rect panel;
 *    - The size of panel
 *    - Read only
 *
 *   User client can read(VIDIOC_G_EXT_CTLRS) 'in' and 'out', 'panel',
 *   set(VIDIOC_S_EXT_CTLRS) the value of 'out' when user client set the capture
 *   location to V4L2_EXT_CAPTURE_SCALER_INPUT(VTV). In this case, the values of
 *   the structure are used as shown below.
 *
 *   1. struct v4l2_ext_capture_rect in;
 *    - Current input resolution of scaler.
 *    - Read only
 *
 *   2. struct v4l2_ext_capture_rect out;
 *    - Current output size of vt output buffer.
 *    - Read, Write
 *
 *   3. struct v4l2_ext_capture_rect panel;
 *    - The size of panel
 *    - Read only
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS (LG chip is only supported.)
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_VIDEO_WIN_INFO
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_capture_rect
 *     {
 *         unsigned short x; // horizontal start position
 *         unsigned short y; // vertical start position
 *         unsigned short w; // horizontal size(width)
 *         unsigned short h; // vertical size(height)
 *     };
 *
 *     enum v4l2_ext_capture_video_scan_type
 *     {
 *         V4L2_EXT_CAPTURE_VIDEO_INTERLACED = 0,
 *         V4L2_EXT_CAPTURE_VIDEO_PROGRESSIVE
 *     };
 *
 *     struct v4l2_ext_capture_video_win_info
 *     {
 *         enum v4l2_ext_capture_video_scan_type type;
 *         struct v4l2_ext_capture_rect in;
 *         struct v4l2_ext_capture_rect out;
 *         struct v4l2_ext_capture_rect panel;
 *     };
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   LG chip only supports the command of VIDIOC_S_EXT_CTRLS.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_capture_plane_info vt_palne_info;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     int ret;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *
 *     ext_controls.ctrl_class     = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count          = 1;
 *     ext_controls.controls       = &ext_control;
 *     ext_controls.controls->id   = V4L2_CID_EXT_CAPTURE_PLANE_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_capture_plane_info);
 *     ext_controls.controls->ptr  = (void *)&vt_palne_info;
 *
 *     ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_VIDEO_WIN_INFO (V4L2_CID_USER_EXT_CAPTURE_BASE + 2)

/**
 * @brief Set/get properties.
 *
 * @rst
 * Functional Requirements
 *   This command is used to set the position to be captured. The struct
 *   v4l2_ext_capture_rect plane and int buf_count are not referenced as reserved
 *   areas. The LG chip only uses the value of struct v4l2_ext_capture_rect plane
 *   and int buf_count. Capture position uses the following structure defined by
 *   user.
 *
 *   Each position follows the following H / W block.
 *     .. image:: /renderer/resources/video-texture-V4L2_CID_EXT_CAPTURE_PLANE_PROP_v2.png
 *   1. V4L2_EXT_CAPTURE_SCALER_INPUT
 *     - LG uses this location only when VTV mode.
 *     - If not supported, the ioctl should be returned -1 and the errno variable should be set to ENOTSUP.
 *   2. V4L2_EXT_CAPTURE_SCALER_OUTPUT
 *     - Recommend location
 *         - Before PQ processing, after de-interlace block
 *         - The frame is a progressive type.
 *     - Alternative location due to chip limitation
 *         - Before PQ processing, before de-interlace block
 *         - The frame is an interlace type.
 *   3. V4L2_EXT_CAPTURE_DISPLAY_OUTPUT
 *     - Capture a video after PQ processing and before OSD blending.
 *     - The frame size calculated with ARC applied.
 *   4. V4L2_EXT_CAPTURE_BLENDED_OUTPUT
 *     - Capture a video after OSD blending.
 *     - If not supported, the ioctl should be returned -1 and the errno variable should be set to ENOTSUP.
 *   5. V4L2_EXT_CAPTURE_OSD_OUTPUT
 *     - Capture a OSD output.
 *     - If not supported, the ioctl should be returned -1 and the errno variable should be set to ENOTSUP.
 *   6. V4L2_EXT_CAPTURE_SUB_SCALER_OUTPUT
 *     - Capture a video from a sub-scaler output.
 *     - If not supported, the ioctl should be returned -1 and the errno variable should be set to ENOTSUP.
 *
 *   Struct
 *     .. code-block:: cpp
 *
 *       enum v4l2_ext_capture_location
 *       {
 *           V4L2_EXT_CAPTURE_SCALER_INPUT = 0, // for VTV - before de-interlace
 *           V4L2_EXT_CAPTURE_SCALER_OUTPUT,
 *           V4L2_EXT_CAPTURE_DISPLAY_OUTPUT,
 *           V4L2_EXT_CAPTURE_BLENDED_OUTPUT,
 *           V4L2_EXT_CAPTURE_OSD_OUTPUT,
 *           V4L2_EXT_CAPTURE_SUB_SCALER_OUTPUT
 *       };
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 200ms, unless there is a special reason.
 *
 * Constraints
 *   V4L2_EXT_CAPTURE_SCALER_INPUT only needs to be supported by LG SoC.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTLRS
 *     VIDIOC_S_EXT_CTLRS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_PLANE_PROP
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_capture_rect
 *     {
 *         unsigned short x; // horizontal start position
 *         unsigned short y; // vertical start position
 *         unsigned short w; // horizontal size(width)
 *         unsigned short h; // vertical size(height)
 *     };
 *
 *     enum v4l2_ext_capture_location
 *     {
 *         V4L2_EXT_CAPTURE_SCALER_INPUT = 0, // for VTV - before de-interlace
 *         V4L2_EXT_CAPTURE_SCALER_OUTPUT,
 *         V4L2_EXT_CAPTURE_DISPLAY_OUTPUT,
 *         V4L2_EXT_CAPTURE_BLENDED_OUTPUT,
 *         V4L2_EXT_CAPTURE_OSD_OUTPUT,
 *         V4L2_EXT_CAPTURE_SUB_SCALER_OUTPUT
 *     };
 *
 *     struct v4l2_ext_capture_plane_prop
 *     {
 *         enum v4l2_ext_capture_location l;
 *         struct v4l2_ext_capture_rect plane;
 *         int buf_count;
 *     };
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS/VIDIOC_S_EXT_CTRLS and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_capture_plane_prop p;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     int ret;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&p, 0, sizeof(struct v4l2_ext_capture_plane_prop));
 *
 *     p.l = V4L2_EXT_CAPTURE_SCALER_OUTPUT;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_CAPTURE_PLANE_PROP;
 *     ext_controls.controls->ptr = (void *)&p;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_PLANE_PROP (V4L2_CID_USER_EXT_CAPTURE_BASE + 3)

/**
 * @brief Set/get freeze.
 *
 * @rst
 * Functional Requirements
 *   It is a freeze command to temporarily stop updating video frames in the
 *   capture buffer.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTLRS
 *     VIDIOC_G_EXT_CTLRS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_FREEZE_MODE
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_capture_freeze_mode
 *     {
 *         int plane_index; //buffer index
 *         unsigned char val;
 *     }
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is
 *   set appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_S_EXT_CTRLS/VIDIOC_G_EXT_CTRLS and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_capture_freeze_mode m;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&m, 0, sizeof(struct v4l2_ext_capture_freeze_mode));
 *
 *     m.plane_index = index; m.val = 1; //on
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_CAPTURE_FREEZE_MODE;
 *     ext_controls.controls->ptr = (void *)&m;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_FREEZE_MODE (V4L2_CID_USER_EXT_CAPTURE_BASE + 4)

/**
 * @brief Notify done processing to driver.
 *
 * @rst
 * Functional Requirements
 *   It is a command used in VTV to process the dumped frame at the user level on
 *   the platfom side and inform the completion of the processing.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   This is only available when V4L2_EXT_CAPTURE_CAP_VIDEOTOVIDEO is supported.
 *   This is only available when the capture location of V4L2_CID_EXT_CAPTURE_PLANE_PROP is set V4L2_EXT_CAPTURE_SCALER_INPUT.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_DONE_USER_PROCESSING (LG chip is only supported.)
 *
 *     //
 *     // parameter
 *     //
 *     plane_index //This index means vt output buffer index.
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is
 *   set appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *       struct  v4l2_control control;
 *       control.id = V4L2_CID_EXT_CAPTURE_DONE_USER_PROCESSING;
 *       control.value = plane_index;
 *       ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_DONE_USER_PROCESSING                              \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 5)

/**
 * @brief Get physical memory
 *
 * @rst
 * Functional Requirements
 *   It is a command to read the physical address of the buffer through the buffer
 *   index. If the user client sets the buffer index to the driver, the driver
 *   sets the physical address to each of  ``y`` and ``c``. User client uses
 *   V4L2_EXT_CAPTURE_INPUT_BUF to get the physical memory of input buffer when
 *   VTG and VTV. In case of V4L2_EXT_CAPTURE_OUTPUT_BUF, user client uses that to
 *   get the physical memory of input buffer when VTV. So if the vendor does not
 *   support the feature of VTV, the vendor does not need to implement about
 *   V4L2_EXT_CAPTURE_OUTPUT_BUF.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTLRS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_PHYSICAL_MEMORY_INFO
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_capture_buf_location
 *     {
 *         V4L2_EXT_CAPTURE_INPUT_BUF = 0,
 *         V4L2_EXT_CAPTURE_OUTPUT_BUF
 *     };
 *
 *     struct v4l2_ext_capture_physical_memory_info
 *     {
 *         int buf_index;
 *         union {
 *             unsigned int *y;
 *             unsigned int compat_y_data;
 *             unsigned long long y_sizer;
 *         };
 *
 *         union {
 *             unsigned int *c;
 *             unsigned int compat_c_data;
 *             unsigned long long c_sizer;
 *         };
 *         enum v4l2_ext_capture_buf_location buf_location;
 *     };
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *       struct v4l2_ext_controls ext_controls;
 *       struct v4l2_ext_control ext_control;
 *       struct v4l2_ext_capture_physical_memory_info info;
 *
 *       memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *       memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *       memset(&info, 0, sizeof(struct v4l2_ext_capture_physical_memory_info));
 *
 *       info.buf_index = index;
 *       info.y = malloc(sizeof(unsigned int));
 *       info.c = malloc(sizeof(unsigned int));
 *
 *       ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *       ext_controls.count = 1;
 *       ext_controls.controls = &ext_control;
 *       ext_controls.controls->id = V4L2_CID_EXT_CAPTURE_PHYSICAL_MEMORY_INFO;
 *       ext_controls.controls->ptr = (void *)&info;
 *
 *       ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_PHYSICAL_MEMORY_INFO                              \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 6)

/**
 * @brief Get output frame rate.
 *
 * @rst
 * Functional Requirements
 *   It is a command for obtaining the output frame rate data of the buffer from
 *   the user client.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_OUTPUT_FRAMERATE
 *
 *     //
 *     // parameter
 *     //
 *     frame rate (30 or 50 or 60 or 120 or etc..)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *       struct v4l2_control control;
 *       control.id = V4L2_CID_EXT_CAPTURE_OUTPUT_FRAMERATE;
 *       ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_OUTPUT_FRAMERATE                                  \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 7)

/**
 * @brief Divide output frame rate.
 *
 * @rst
 * Functional Requirements
 *   This function adjusts the output frame rate of the buffer. The default value
 *   is 1; if the function is not supported, an error is returned. Below is an
 *   example of using this command.
 *     - When the output buffer frame rate of the current buffer is 60Hz and the user
 *       client sets the DIVIDE_FRAMERATE value to 2, the final buffer output frame
 *       rate is 30Hz (60Hz / 2).
 *     - When the output buffer frame rate of current buffer is 120Hz and the user
 *       client sets DIVIDE_FRAMERATE value to 4, the final buffer output frame
 *       rate is 30Hz (120Hz / 4).
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL
 *     VIDIOC_S_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_CAPTURE_DIVIDE_FRAMERATE
 *
 *     //
 *     // parameter
 *     //
 *     divide value
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_S_CTRL/VIDIOC_G_CTRL and this control
 *   id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *       struct v4l2_control control;
 *       control.id = V4L2_CID_EXT_CAPTURE_DIVIDE_FRAMERATE;
 *       control.value = 2;
 *       ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_CAPTURE_DIVIDE_FRAMERATE                                  \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 8)


/**********************************************
* videotexture class control IDs for histogram
***********************************************/

/**
 * @brief Activate the histogram mode.
 *
 * @rst
 * Functional Requirements
 *   This command initializes the histogram capture function.
 *   When this function called,
 *   the VT driver ready to resource for secure capture(for TA) and initialize some values.
 *   If the function is not supported, an error is returned.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTLRS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HISTOGRAM_START
 *
 *     //
 *     // parameter
 *     //
 *     None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *
 *     struct v4l2_ext_control ext_control = {};
 *     ext_control.id = V4L2_CID_EXT_HISTOGRAM_START;
 *     ext_control.value = 0;
 *
 *     struct v4l2_ext_controls ext_controls = {};
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HISTOGRAM_START                                           \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 20)

/**
 * @brief Set the histogram preset mode value.
 *
 * @rst
 * Functional Requirements
 *   This command sets the histogram preset mode.
 *   We have predefined four kinds of preset mode.
 *   Please refer sample data below.
 *
 *   Preset Mode
 *     .. code-block:: cpp
 *
 *       // (0,0) being the top left corner of the image
 *       // 0: Video no bb:
 *       [
 *           {id:0, left_top_xy: (0.25, 0.0), right_bottom_xy: (0.75, 1.0)},
 *           {id:1, left_top_xy: (0.2, 0.8), right_bottom_xy: (0.8, 1.0)},
 *           {id:2, left_top_xy: (0.3, 0.3), right_bottom_xy: (0.7, 0.7)},
 *           {id:3, left_top_xy: (0.1, 0.0), right_bottom_xy: (0.4, 0.2)},
 *           {id:4, left_top_xy: (0.0, 0.0), right_bottom_xy: (0.5, 1.0)},
 *           {id:5, left_top_xy: (0.0, 0.67), right_bottom_xy: (0.29, 1.0)},
 *           {id:6, left_top_xy: (0.0, 0.24), right_bottom_xy: (0.2, 0.76)},
 *           {id:7, left_top_xy: (0.0, 0.0), right_bottom_xy: (0.3, 0.375)},
 *           {id:8, left_top_xy: (0.5, 0.0), right_bottom_xy: (1.0, 1.0)},
 *           {id:9, left_top_xy: (0.7, 0.67), right_bottom_xy: (1.0, 1.0)},
 *           {id:10, left_top_xy: (0.8, 0.24), right_bottom_xy: (1.0, 0.76)},
 *           {id:11, left_top_xy: (0.35, 0.0), right_bottom_xy: (0.65, 0.2)},
 *           {id:12, left_top_xy: (0.6, 0.0), right_bottom_xy: (0.9, 0.2)},
 *           {id:13, left_top_xy: (0.7, 0.0), right_bottom_xy: (1.0, 0.375)},
 *           {id:14, left_top_xy: (0.3, 0.0), right_bottom_xy: (0.7, 0.1265)},
 *           {id:15, left_top_xy: (0.0, 0.3), right_bottom_xy: (0.13, 0.7)}
 *       ]
 *
 *       // 1: Video with top/bottom bb avoidance
 *       [
 *           {id:0, left_top_xy: (x:0.25, y:0.1265), right_bottom_xy: (x:0.75, y:0.8735)},
 *           {id:1, left_top_xy: (x:0.2, y:0.7241), right_bottom_xy: (x:0.8, y:0.8735)},
 *           {id:2, left_top_xy: (x:0.3, y:0.3506), right_bottom_xy: (x:0.7, y:0.6494)},
 *           {id:3, left_top_xy: (x:0.1, y:0.1265), right_bottom_xy: (x:0.4, y:0.2759)},
 *           {id:4, left_top_xy: (x:0.0, y:0.1265), right_bottom_xy: (x:0.5, y:0.8735)},
 *           {id:5, left_top_xy: (x:0.0, y:0.62699), right_bottom_xy: (x:0.29, y:0.8735)},
 *           {id:6, left_top_xy: (x:0.0, y:0.30578), right_bottom_xy: (x:0.2, y:0.69422)},
 *           {id:7, left_top_xy: (x:0.0, y:0.1265), right_bottom_xy: (x:0.3, y:0.406625)},
 *           {id:8, left_top_xy: (x:0.5, y:0.1265), right_bottom_xy: (x:1.0, y:0.8735)},
 *           {id:9, left_top_xy: (x:0.7, y:0.62699), right_bottom_xy: (x:1.0, y:0.8735)},
 *           {id:10, left_top_xy: (x:0.8, y:0.30578), right_bottom_xy: (x:1.0, y:0.69422)},
 *           {id:11, left_top_xy: (x:0.35, y:0.1265), right_bottom_xy: (x:0.65, y:0.2759)},
 *           {id:12, left_top_xy: (x:0.6, y:0.1265), right_bottom_xy: (x:0.9, y:0.2759)},
 *           {id:13, left_top_xy: (x:0.7, y:0.1265), right_bottom_xy: (x:1.0, y:0.406625)},
 *           {id:14, left_top_xy: (0.3, 0.0), right_bottom_xy: (0.7, 0.1265)},
 *           {id:15, left_top_xy: (0.0, 0.3), right_bottom_xy: (0.13, 0.7)}
 *       ]
 *
 *       // 2: Video with left/right bb avoidance
 *       [
 *           {id:0, left_top_xy: (x:0.315, y:0.0), right_bottom_xy: (x:0.685, y:1.0)},
 *           {id:1, left_top_xy: (x:0.278, y:0.8), right_bottom_xy: (x:0.722, y:1.0)},
 *           {id:2, left_top_xy: (x:0.352, y:0.3), right_bottom_xy: (x:0.648, y:0.7)},
 *           {id:3, left_top_xy: (x:0.204, y:0.0), right_bottom_xy: (x:0.426, y:0.2)},
 *           {id:4, left_top_xy: (x:0.13, y:0.0), right_bottom_xy: (x:0.5, y:1.0)},
 *           {id:5, left_top_xy: (x:0.13, y:0.67), right_bottom_xy: (x:0.3446, y:1.0)},
 *           {id:6, left_top_xy: (x:0.13, y:0.24), right_bottom_xy: (x:0.278, y:0.76)},
 *           {id:7, left_top_xy: (x:0.13, y:0.0), right_bottom_xy: (x:0.352, y:0.375)},
 *           {id:8, left_top_xy: (x:0.5, y:0.0), right_bottom_xy: (x:0.87, y:1.0)},
 *           {id:9, left_top_xy: (x:0.648, y:0.67), right_bottom_xy: (x:0.87, y:1.0)},
 *           {id:10, left_top_xy: (x:0.722, y:0.24), right_bottom_xy: (x:0.87, y:0.76)},
 *           {id:11, left_top_xy: (x:0.389, y:0.0), right_bottom_xy: (x:0.611, y:0.2)},
 *           {id:12, left_top_xy: (x:0.574, y:0.0), right_bottom_xy: (x:0.796, y:0.2)},
 *           {id:13, left_top_xy: (x:0.648, y:0.0), right_bottom_xy: (x:0.87, y:0.375)},
 *           {id:14, left_top_xy: (0.3, 0.0), right_bottom_xy: (0.7, 0.1265)},
 *           {id:15, left_top_xy: (0.0, 0.3), right_bottom_xy: (0.13, 0.7)}
 *       ]
 *
 *       // 3: Games
 *       [
 *           {id:0, left_top_xy: (0.5, 0.1), right_bottom_xy: (1.0, 0.9)},
 *           {id:1, left_top_xy: (0.3, 0.0), right_bottom_xy: (0.7, 1.0)},
 *           {id:2, left_top_xy: (0.0, 0.1), right_bottom_xy: (0.5, 0.9)},
 *           {id:3, left_top_xy: (0.33, 0.3), right_bottom_xy: (0.67, 0.67)},
 *           {id:4, left_top_xy: (0.23, 0.74), right_bottom_xy: (0.77, 1.0)},
 *           {id:5, left_top_xy: (0.66, 0.62), right_bottom_xy: (1.0, 1.0)},
 *           {id:6, left_top_xy: (0.74, 0.27), right_bottom_xy: (1.0, 0.73)},
 *           {id:7, left_top_xy: (0.7, 0.0), right_bottom_xy: (1.0, 0.375)},
 *           {id:8, left_top_xy: (0.6, 0.0), right_bottom_xy: (0.9, 0.2)},
 *           {id:9, left_top_xy: (0.35, 0.0), right_bottom_xy: (0.65, 0.2)},
 *           {id:10, left_top_xy: (0.1, 0.0), right_bottom_xy: (0.4, 0.2)},
 *           {id:11, left_top_xy: (0.0, 0.0), right_bottom_xy: (0.3, 0.375)},
 *           {id:12, left_top_xy: (0.0, 0.27), right_bottom_xy: (0.26, 0.73)},
 *           {id:13, left_top_xy: (0.0, 0.62), right_bottom_xy: (0.34, 1.0)}
 *       ]
 *
 *   If the function is not supported, an error is returned.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTLRS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HISTOGRAM_PRESET
 *
 *     //
 *     // parameter
 *     //
 *     preset mode value (0~3)
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *
 *     struct v4l2_ext_control ext_control = {};
 *     ext_control.id = V4L2_CID_EXT_HISTOGRAM_PRESET;
 *     ext_control.value = 0; // preset mode(0~3)
 *
 *     struct v4l2_ext_controls ext_controls = {};
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HISTOGRAM_PRESET                                          \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 21)

/**
 * @brief Get histogram data from the selected area.
 *
 * @rst
 * Functional Requirements
 *   This command gets for histogram data from selected area.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   Response time must be within 15FPS.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTLRS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HISTOGRAM_DATA
 *
 *     //
 *     // parameter
 *     //
 *
 *     struct v4l2_ext_histogram_data
 *     {
 *         unsigned int areaId; // id of the area this histogram was computed.
 *         unsigned short r[256];
 *         unsigned short g[256];
 *         unsigned short b[256];
 *     };
 *
 *   Each preset mode has 14 or 16 area IDs.
 *   Therefore, the user must declare a histogram array equal to the number of IDs,
 *   and set the "areaId" value in each structure to 0~max area ID.
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // init output histogram
 *     // "m_maxHistogramCnt" is the number of areas for the selected preset mode.
 *     struct v4l2_ext_histogram_data output_histogram[m_maxHistogramCnt];
 *     memset(output_histogram, 0, sizeof(struct v4l2_ext_histogram_data) * m_maxHistogramCnt);
 *     for (int i=0; i<m_maxHistogramCnt; ++i)
 *         output_histogram[i].areaId = i;
 *
 *     int ret = -1;
 *
 *     struct v4l2_ext_control ext_control = {};
 *     ext_control.id = V4L2_CID_EXT_HISTOGRAM_DATA;
 *     ext_control.ptr = (void *)&output_histogram;
 *
 *     struct v4l2_ext_controls ext_controls = {};
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *
 *     ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HISTOGRAM_DATA                                            \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 22)

/**
 * @brief Deactivate the histogram mode.
 *
 * @rst
 * Functional Requirements
 *   This command finalize the histogram capture function.
 *   When this function called,
 *   the VT driver release all of resource for secure capture (for TA)
 *   and initialize some values.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time must respond within 10ms, unless there is a special reason.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTLRS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HISTOGRAM_STOP
 *
 *     //
 *     // parameter
 *     //
 *     None
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     int ret = -1;
 *
 *     struct v4l2_ext_control ext_control = {};
 *     ext_control.id = V4L2_CID_EXT_HISTOGRAM_STOP;
 *     ext_control.value = 0;
 *
 *     struct v4l2_ext_controls ext_controls = {};
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HISTOGRAM_STOP                                            \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 23)


/* Capture class subscription IDs */
#define V4L2_CID_EXT_CAPTURE_SUBSCRIBE_FRAME_READY                             \
    (V4L2_CID_USER_EXT_CAPTURE_BASE + 30)

/* Capture class subscription types */
#define V4L2_EVENT_PRIVATE_EXT_CAPTURE_BASE (V4L2_EVENT_PRIVATE_START + 0x2100)
#define V4L2_EVENT_PRIVATE_EXT_CAPTURE_EVENT                                   \
    (V4L2_EVENT_PRIVATE_EXT_CAPTURE_BASE + 1)

#endif
