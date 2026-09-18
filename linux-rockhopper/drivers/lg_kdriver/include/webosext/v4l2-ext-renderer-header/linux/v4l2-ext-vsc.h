/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018~2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_VSC_H
#define _V4L2_EXT_VSC_H

#include <linux/v4l2-controls.h>
/* FIXME: gstreamer-good uses uapi/linux/videodev2.h,
 * so add to check _UAPI_XX to prevent redefinition error
 */
#ifndef _UAPI__LINUX_VIDEODEV2_H
#include <linux/videodev2.h>
#endif

/**
 * @brief VDO(VIDEO DISPLAY OUTPUT) 0
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_DEV_NO_VDO0 28
 *
 * @endrst
 */
#define V4L2_EXT_DEV_NO_VDO0 28

/**
 * @brief VDO(VIDEO DISPLAY OUTPUT) 1
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_DEV_NO_VDO0 29
 *
 * @endrst
 */
#define V4L2_EXT_DEV_NO_VDO1 29
#define V4L2_EXT_DEV_NO_SCALER0 30
#define V4L2_EXT_DEV_NO_SCALER1 31
#define V4L2_EXT_DEV_NO_SCALER2 32
#define V4L2_EXT_DEV_NO_SCALER3 33

/**
 * @brief VDO(VIDEO DISPLAY OUTPUT) 0 Path
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_DEV_PATH_VDO0 "/dev/video28"
 *
 * @endrst
 */
#define V4L2_EXT_DEV_PATH_VDO0 "/dev/video28"

/**
 * @brief VDO(VIDEO DISPLAY OUTPUT) 1 Path
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_DEV_PATH_VDO0 "/dev/video29"
 *
 * @endrst
 */

#define V4L2_EXT_DEV_PATH_VDO1 "/dev/video29"
#define V4L2_EXT_DEV_PATH_SCALER0 "/dev/video30"
#define V4L2_EXT_DEV_PATH_SCALER1 "/dev/video31"
#define V4L2_EXT_DEV_PATH_SCALER2 "/dev/video32"
#define V4L2_EXT_DEV_PATH_SCALER3 "/dev/video33"

struct v4l2_ext_video_rect {
  unsigned short x;
  unsigned short y;
  unsigned short w;
  unsigned short h;
};

enum v4l2_ext_vsc_input_src {
  V4L2_EXT_VSC_INPUT_SRC_NONE = 0, /**< enum value none */
  V4L2_EXT_VSC_INPUT_SRC_AVD,      /**< enum value avd */
  V4L2_EXT_VSC_INPUT_SRC_ADC,      /**< enum value adc */
  V4L2_EXT_VSC_INPUT_SRC_HDMI,     /**< enum value hdmi */
  V4L2_EXT_VSC_INPUT_SRC_VDEC,     /**< enum value vdec */
  V4L2_EXT_VSC_INPUT_SRC_JPEG,     /**< enum value jpeg */
  V4L2_EXT_VSC_INPUT_SRC_FB,       /**< enum value fb */
  V4L2_EXT_VSC_INPUT_SRC_DP,       /**< enum value display port */
  V4L2_EXT_VSC_INPUT_SRC_TEXTURE   /**< enum value texture - TTV output */
};

enum v4l2_ext_vsc_dest {
  V4L2_EXT_VSC_DEST_NONE = 0, /**< enum value none */
  V4L2_EXT_VSC_DEST_DISPLAY,  /**< enum value display */
  V4L2_EXT_VSC_DEST_VENC,     /**< enum value venc */
  V4L2_EXT_VSC_DEST_MEMORY,   /**< enum value memory */
  V4L2_EXT_VSC_DEST_AVE       /**< enum value ave */
};

struct v4l2_ext_vsc_input_src_info {
  enum v4l2_ext_vsc_input_src src;
  unsigned char index;
  unsigned char attr;
};

struct v4l2_ext_vsc_connect_info {
  struct v4l2_ext_vsc_input_src_info in;
  enum v4l2_ext_vsc_dest out;
};

enum v4l2_ext_vsc_vdo_port {
  V4L2_EXT_VSC_VDO_PORT_NONE = 0,
  V4L2_EXT_VSC_VDO_PORT_0,
  V4L2_EXT_VSC_VDO_PORT_1
};

struct v4l2_ext_vsc_vdo_mode {
  enum v4l2_ext_vsc_vdo_port vdo_port;
  unsigned short vdec_port;
};

enum v4l2_ext_vsc_win_color {
  V4L2_EXT_VSC_WIN_COLOR_NORMAL = 0,
  V4L2_EXT_VSC_WIN_COLOR_BLACK,
  V4L2_EXT_VSC_WIN_COLOR_BLUE,
  V4L2_EXT_VSC_WIN_COLOR_GRAY
};

enum v4l2_ext_vsc_rotation {
  V4L2_EXT_VSC_ROTATE_0 = 0,
  V4L2_EXT_VSC_ROTATE_90,
  V4L2_EXT_VSC_ROTATE_180,
  V4L2_EXT_VSC_ROTATE_270,
  V4L2_EXT_VSC_ROTATE_HFLIP,
  V4L2_EXT_VSC_ROTATE_HFLIP_90,
  V4L2_EXT_VSC_ROTATE_HFLIP_180,
  V4L2_EXT_VSC_ROTATE_HFLIP_270,
  V4L2_EXT_VSC_ROTATE_VFLIP
};

struct v4l2_ext_vsc_input_region {
  struct v4l2_ext_video_rect crop;
  struct v4l2_ext_video_rect res;
};

struct v4l2_ext_vsc_win_region {
  struct v4l2_ext_vsc_input_region in;
  struct v4l2_ext_video_rect out;
  enum v4l2_ext_vsc_rotation rotation;
  struct v4l2_ext_video_rect punch;
};

struct v4l2_ext_vsc_orbit_window {
  struct v4l2_ext_video_rect osd_input;
  struct v4l2_ext_video_rect video_input;
  struct v4l2_ext_video_rect osd_output;
  struct v4l2_ext_video_rect video_output;
};

struct v4l2_ext_vsc_orbit_move {
  struct v4l2_ext_video_rect osd_input;
  struct v4l2_ext_video_rect video_input;
  struct v4l2_ext_video_rect osd_output;
  struct v4l2_ext_video_rect video_output;
};

struct v4l2_ext_vsc_orbit_position {
  struct v4l2_ext_vsc_orbit_window orbit_window;
  struct v4l2_ext_vsc_orbit_move orbit_move;
};

enum v4l2_ext_vsc_orbit_on_off {
  V4L2_EXT_VSC_ORBIT_OFF = 0,
  V4L2_EXT_VSC_ORBIT_ON
};
struct v4l2_ext_vsc_orbit_size {
  unsigned short x;
  unsigned short y;
};

struct v4l2_ext_vsc_orbit_region {
  struct v4l2_ext_vsc_orbit_size video_size;
  unsigned short video_scan;
  struct v4l2_ext_vsc_orbit_size osd_size;
  unsigned short osd_scan;
};

struct v4l2_ext_vsc_orbit_policy {
  enum v4l2_ext_vsc_orbit_on_off orbit_on_off;
  struct v4l2_ext_video_rect osd_resolution;
  struct v4l2_ext_video_rect panel_resolution;
  struct v4l2_ext_vsc_orbit_region region;
  struct v4l2_ext_vsc_orbit_size video_step;
  struct v4l2_ext_vsc_orbit_size osd_step;
};

enum v4l2_ext_vsc_win_mode {
  V4L2_EXT_VSC_WIN_MODE_NONE = 0,
  V4L2_EXT_VSC_WIN_MODE_PIP,
  V4L2_EXT_VSC_WIN_MODE_PBP
};

enum v4l2_ext_vsc_mirror_mode {
  V4L2_EXT_VSC_MIRROR_MODE_NONE = 0,
  V4L2_EXT_VSC_MIRROR_MODE_ON,
  V4L2_EXT_VSC_MIRROR_MODE_OFF
};

enum v4l2_ext_vsc_memory_type {
  V4L2_EXT_VSC_MEMORY_TYPE_NONE = 0,
  V4L2_EXT_VSC_MEMORY_TYPE_SINGLE,
  V4L2_EXT_VSC_MEMORY_TYPE_MULTI
};

struct v4l2_ext_vsc_win_prop {
  enum v4l2_ext_vsc_win_mode win_mode;
  enum v4l2_ext_vsc_mirror_mode mirror_mode;
  enum v4l2_ext_vsc_memory_type mem_type;
};

struct v4l2_ext_vsc_zorder {
  unsigned char zorder;
  unsigned char alpha;
};

struct v4l2_ext_vsc_scaler_ratio {
  int h_scaleup_ratio;
  int v_scaleup_ratio;
  int h_scaledown_ratio;
  int v_scaledown_ratio;
};

enum v4l2_ext_vsc_latency_pattern {
  V4L2_EXT_VSC_PATTERN_BLACK = 0,
  V4L2_EXT_VSC_PATTERN_WHITE
};

struct v4l2_ext_vsc_latency_pattern_info {
  struct v4l2_ext_video_rect r;
  enum v4l2_ext_vsc_latency_pattern p;
};

struct v4l2_ext_vsc_active_win_info {
  struct v4l2_ext_video_rect original;
  struct v4l2_ext_video_rect active;
};

struct v4l2_ext_vsc_color_pixel_data {
  unsigned int y;  /* standard pixel color Y */
  unsigned int cb; /* standard pixel color Cb */
  unsigned int cr; /* standard pixel color Cr */
};

enum v4l2_ext_vsc_color_pixel_format {
  V4L2_EXT_VSC_COLOR_PIXEL_FORMAT_YUV = 0,
  V4L2_EXT_VSC_COLOR_PIXEL_FORMAT_RGB
};

enum v4l2_ext_vsc_color_pixel_depth {
  V4L2_EXT_VSC_COLOR_PIXEL_8BIT = 0,
  V4L2_EXT_VSC_COLOR_PIXEL_10BIT
};

struct v4l2_ext_vsc_pixel_color_info {
  struct v4l2_ext_video_rect r;
  union {
    struct v4l2_ext_vsc_color_pixel_data *p_data;
    unsigned int compat_data;
    unsigned long long sizer;
  };
  enum v4l2_ext_vsc_color_pixel_format format;
  enum v4l2_ext_vsc_color_pixel_depth depth;
};

struct v4l2_ext_vsc_zoom_data {
  unsigned short h_ratio;
  unsigned short v_ratio;
  unsigned short h_position;
  unsigned short v_position;
};

struct v4l2_ext_system_policy {
  struct v4l2_ext_video_rect panel;
  unsigned short country_grp;
  unsigned short content_type;
  unsigned short source_index;
};

struct v4l2_ext_setting_policy {
  struct v4l2_ext_vsc_zoom_data zoom_data;
  unsigned short just_scan;
  unsigned short aspect_ratio;
  unsigned short rotate;
  unsigned short orbit_over_scan;
  unsigned short screen_position;
  unsigned short media_afd_property;
  unsigned short overscan_appropriate_flag;
  unsigned short scan_type;
};

struct v4l2_ext_vsc_aspectratio_policy {
  struct v4l2_ext_video_rect out;              // Output region to display video
  struct v4l2_ext_system_policy system_policy; // webOS policy of system
  struct v4l2_ext_setting_policy setting_policy; // webOS policy of setting
  struct v4l2_ext_video_rect punch;            // punch size for the callback
};

struct v4l2_ext_vsc_device_capability {
  int num_planes;
};

enum v4l2_ext_vsc_scan_mode {
    V4L2_EXT_VSC_SCAN_MODE_FIELD_MERGE = 0, // deinterlace
    V4L2_EXT_VSC_SCAN_MODE_LINE_DOUBLER = 1,
    V4L2_EXT_VSC_SCAN_MODE_INTER_FIELD = 2,
};

struct v4l2_ext_vsc_zorder_info {
  int length;
  // length: Number of output scaler.
  // length is the same value as num_planes used in V4L2_CID_EXT_VSC_DEVICE_CAPABILITY.
  // length is always the same value and is the valid size of the structure pointer.
  union {
    struct v4l2_ext_vsc_zorder *z; // An structure pointer of v4l2_ext_vsc_zorder.
    unsigned long long sizer; // To ensure 64bit compatibility.
  };
};

#define V4L2_CID_USER_EXT_VSC_BASE (V4L2_CID_USER_BASE + 0x2000)

//
// Scaler class control IDs
//

/**
 * @brief Set video window
 *
 * @rst
 * Functional Requirements
 *   This will use when video window set. (VSC SetIntputOutputRegion) It will
 *   replace previous HAL function, that is, RotateVideo, SetInputRegion,
 *   SetOutputRegion.
 *
 *   It is a function that will replace by integrating the existing
 *   RotateVideo/SetInputRegion/SetOutputRegion features.
 *
 *   Below conditions should be satisfied to implement this function.
 *
 *   1. SetOutputRegion, this function is used for setting video window size. LG
 *      will provide the window position and size (pOutputRegion). Driver should
 *      draw window of the fd.
 *
 *   2. SetInputRegion, this function is used for cropping video. LG will
 *      provide
 *      original video size (originalInput) and cropped size (inRegion). Driver
 *      should use the provided values to calculate ratio only. And calculate
 *      actual cropped size with original video size transmitted from VDEC
 *      driver
 *      by the ratio. This calculation is performed for synchronization with the
 *      value passed from the VDEC driver.
 *
 *   3. RotateVideo, this function is used for rotating video to 90', 180',
 *      270', 0', horizontal reverse(H flip), vertical reverse(V flip). 
 *      This should be rotated by clockwise. LG will provide rotate info(rotation) and rotated
 *      window size (pOutputRegion). Driver should draw the rotated video. LG does
 *      not support V flip, only H flip (as of webOS23).
 *
 *   To reduce window setting time, we’ll integrate previous HAL functions. To
 *   avoid garbage, driver should apply the above settings during v blank. To
 *   meet setting time, driver can have to skip many previous window size settings
 *   within 1 vsync and apply only latest command.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_WIN_REGION-1.png
 *
 *   Skip window size setting about 1,2,3 commands. Only apply window size
 *   setting about 4 command. (the above picture ppt file)
 *
 *   Driver operation status according to user client parameter value. You must
 *   operate according to the table below.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_WIN_REGION-2.png
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 200ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_WIN_REGION
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_vsc_rotation
 *     {
 *         V4L2_EXT_VSC_ROTATE_0 = 0,
 *         V4L2_EXT_VSC_ROTATE_90,
 *         V4L2_EXT_VSC_ROTATE_180,
 *         V4L2_EXT_VSC_ROTATE_270,
 *         V4L2_EXT_VSC_ROTATE_HFLIP,
 *         V4L2_EXT_VSC_ROTATE_HFLIP_90,
 *         V4L2_EXT_VSC_ROTATE_HFLIP_180,
 *         V4L2_EXT_VSC_ROTATE_HFLIP_270,
 *         V4L2_EXT_VSC_ROTATE_VFLIP
 *     };
 *
 *     struct v4l2_ext_video_rect
 *     {
 *         unsigned short x;   // horizontal start position
 *         unsigned short y;   // vertical start position
 *         unsigned short w;   // horizontal size(width)
 *         unsigned short h;   // vertical size(height)
 *     };
 *
 *     struct v4l2_ext_vsc_input_region
 *     {
 *         struct v4l2_ext_video_rect  crop; // video input crop size to set
 *         struct v4l2_ext_video_rect  res;  // original source resolution
 *     };
 *
 *     struct v4l2_ext_vsc_win_region
 *     {
 *         struct v4l2_ext_vsc_input_region in;
 *         struct v4l2_ext_video_rect out;         // video output size to set
 *         enum v4l2_ext_vsc_rotation rotation;    // rotation information
 *         struct v4l2_ext_video_rect punch;       // punch size for the callback
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Window Info
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_win_region win{0};
 *
 *     // original input resolution
 *     win.in.res.x = in.res.x;
 *     win.in.res.y = in.res.y;
 *     win.in.res.w = in.res.w;
 *     win.in.res.h = in.res.h;
 *
 *     // cropped input size
 *     win.in.crop.x = in.crop.x;
 *     win.in.crop.y = in.crop.y;
 *     win.in.crop.w = in.crop.w;
 *     win.in.crop.h = in.crop.h;
 *
 *     // output size
 *     win.out.x = out.x;
 *     win.out.y = out.y;
 *     win.out.w = out.w;
 *     win.out.h = out.h;
 *
 *     // rotation info
 *     win.rotation = V4L2_EXT_VSC_ROTATE_0;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_WIN_REGION;
 *     ext_controls.controls->ptr = (void *)&win_info;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *
 *     // Get Window Info
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_win_region win{0};
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_WIN_REGION;
 *     ext_controls.controls->ptr = (void *)&win;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_WIN_REGION (V4L2_CID_USER_EXT_VSC_BASE + 0)

/**
 * @brief freezes or unfreezes the specified video window
 *
 * @rst
 * Functional Requirements
 *   This function freezes or unfreezes the specified video window of
 *   video_device. (VSC SetWinFreeze) Freezing means that the last frame is
 *   continuously displayed on the specified video window of video_device.
 *
 * .. important::
 *   Decoding for input source should be kept continuously and
 *   SetInputOutputRegion should also be worked after this function is done.
 *   This function should be frozen after DI H/W block.
 *
 *   This function freezes or unfreezes the video window of specific video
 *   device.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set Window Freeze
 *     VIDIOC_G_CTRL       // Get Window Freeze Status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_FREEZE
 *
 *     //
 *     // control value
 *     //
 *     0 (Off), 1 (On)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set VSC Freeze
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_FREEZE;
 *     control.value = 1;      // On
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *
 *     // Get Video Window Color
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_VSC_FREEZE;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_FREEZE (V4L2_CID_USER_EXT_VSC_BASE + 1)

/**
 * @brief Set sub window mode
 *
 * @rst
 * Functional Requirements
 *   The mode of sub window set for displaying setting. (VSC SetSubWinModeEx)
 *   Please refer to the below contents for parameters.
 *
 *   1. V4L2_EXT_VSC_MEMORY_TYPE_SINGLE in enum v4l2_ext_vsc_memory_type
 *     - This parameter is optional for that sub video is partial for
 *       main video. You don’t need to allocate memory for sub window.
 *       You can get video data from main video for sub. If you have
 *       enough memory, you don`t need this mode.
 *
 *   2. V4L2_EXT_VSC_MEMORY_TYPE_MULTI in enum v4l2_ext_vsc_memory_type
 *     - This parameter is mandatory for that main video is partial for
 *       sub video. You can’t get video data from main window for sub.
 *       You have to allocate memory for sub window.
 *
 *   3. V4L2_EXT_VSC_MIRROR_MODE_ON in enum v4l2_ext_vsc_mirror_mode
 *     - sub window is the same as main input.
 *
 *   4. V4L2_EXT_VSC_MIRROR_MODE_OFF in enum v4l2_ext_vsc_mirror_mode
 *     - It’s different input source between main and sub.
 *
 *   5. V4L2_EXT_VSC_WIN_MODE_PIP in enum v4l2_ext_vsc_win_mode
 *     - Picture in picture,  sub window is overlapped main window.
 *
 *   6. V4L2_EXT_VSC_WIN_MODE_PBP in enum v4l2_ext_vsc_win_mode
 *     - Picture by picture, sub window isn’t overlapped main window.
 *
 *   .. code-block:: cpp
 *
 *     // The parameters of Multi-view Case
 *     subWinMode.mem_type     = V4L2_EXT_VSC_MEMORY_TYPE_MULTI;
 *     subWinMode.mirror_mode  = V4L2_EXT_VSC_MIRROR_MODE_OFF;
 *     subWinMode.win_mode     = V4L2_EXT_VSC_WIN_MODE_PBP;
 *
 *     // The parameters of Overlay Miracast Case
 *     subWinMode.mem_type     = V4L2_EXT_VSC_MEMORY_TYPE_MULTI;
 *     subWinMode.mirror_mode  = V4L2_EXT_VSC_MIRROR_MODE_OFF;
 *     subWinMode.win_mode     = V4L2_EXT_VSC_WIN_MODE_PIP;
 *
 *     // The parameters of Youtube dual video Case
 *     subWinMode.mem_type     = V4L2_EXT_VSC_MEMORY_TYPE_MULTI;
 *     subWinMode.mirror_mode  = V4L2_EXT_VSC_MIRROR_MODE_OFF;
 *     subWinMode.win_mode     = V4L2_EXT_VSC_WIN_MODE_PIP;
 *
 *     // The parameters of Magnifier
 *     subWinMode.mem_type     = V4L2_EXT_VSC_MEMORY_TYPE_SINGLE;
 *     subWinMode.mirror_mode  = V4L2_EXT_VSC_MIRROR_MODE_ON;
 *     subWinMode.win_mode     = V4L2_EXT_VSC_WIN_MODE_PIP;
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_WIN_PROP
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_vsc_win_mode
 *     {
 *
 *         V4L2_EXT_VSC_WIN_MODE_NONE = 0,
 *         V4L2_EXT_VSC_WIN_MODE_PIP,
 *         V4L2_EXT_VSC_WIN_MODE_PBP
 *     };
 *     // *This is for composition window.
 *     // Initial value of driver should be VSC_SUB_MODE_NONE.
 *
 *     enum v4l2_ext_vsc_mirror_mode
 *     {
 *         V4L2_EXT_VSC_MIRROR_MODE_NONE = 0,
 *         V4L2_EXT_VSC_MIRROR_MODE_ON,
 *         V4L2_EXT_VSC_MIRROR_MODE_OFF
 *     };
 *     // *This is for which source connect to sub window.
 *     // Initial value of driver should be VSC_SUB_CONNECT_NONE.
 *
 *     enum v4l2_ext_vsc_memory_type
 *     {
 *         V4L2_EXT_VSC_MEMORY_TYPE_NONE = 0,
 *         V4L2_EXT_VSC_MEMORY_TYPE_SINGLE,
 *         V4L2_EXT_VSC_MEMORY_TYPE_MULTI
 *     };
 *
 *     struct v4l2_ext_vsc_win_prop
 *     {
 *         enum v4l2_ext_vsc_win_mode win_mode;
 *         enum v4l2_ext_vsc_mirror_mode mirror_mode;
 *         enum v4l2_ext_vsc_memory_type mem_type;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Sub Window mode
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_win_prop win_prop{0};
 *
 *     win_prop.memoryType = VSC_SUB_MEMORY_USE_SINGLE;
 *     win_prop.connectType = VSC_SUB_CONNECT_TYPE_NON_MIRROR;
 *     win_prop.modeType = VSC_SUB_MODE_PBP;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_WIN_PROP;
 *     ext_controls.controls->ptr = (void *)&win_prop;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Get Sub Window mode
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_win_prop win_prop{0};
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_WIN_PROP;
 *     ext_controls.controls->ptr = (void *)&win_prop;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_WIN_PROP (V4L2_CID_USER_EXT_VSC_BASE + 2)

/**
 * @brief Set pattern mode
 *
 * @rst
 * Functional Requirements
 *   This function shows video internal pattern from designated block.(VSC SetPattern)
 *   1. MUX: after Frontend(AVD/ADC/HDMI/VDEC), before video processing(DI/NR)
 *   2. DI/NR: after mux, before scaler
 *   3. Scaler: after video processing(DI/NR), before MEMC
 *   4. MEMC: after scaling, before mixing video with OSD
 *   5. Display: after mixing video with OSD
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_PATTERN.png
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_PATTERN
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_vsc_pattern
 *     {
 *         V4L2_EXT_VSC_PATTERN_OFF = 0,
 *         V4L2_EXT_VSC_PATTERN_MUX,
 *         V4L2_EXT_VSC_PATTERN_DI_NR,
 *         V4L2_EXT_VSC_PATTERN_SCALER,
 *         V4L2_EXT_VSC_PATTERN_MEMC,
 *         V4L2_EXT_VSC_PATTERN_DISPLAY,
 *         V4L2_EXT_VSC_PATTERN_RESERVED0,
 *         V4L2_EXT_VSC_PATTERN_RESERVED1,
 *         V4L2_EXT_VSC_PATTERN_RESERVED2,
 *         V4L2_EXT_VSC_PATTERN_RESERVED3
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set pattern
 *     struct v4l2_control control{0};
 *
 *     control.id = V4L2_CID_EXT_VSC_PATTERN;
 *     control.value = V4L2_EXT_VSC_PATTERN_SCALER;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *     // Get pattern
 *     struct v4l2_control control{0};
 *
 *     control.id = V4L2_CID_EXT_VSC_PATTERN;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_PATTERN (V4L2_CID_USER_EXT_VSC_BASE + 3)
enum v4l2_ext_vsc_pattern {
  V4L2_EXT_VSC_PATTERN_OFF = 0,
  V4L2_EXT_VSC_PATTERN_MUX,
  V4L2_EXT_VSC_PATTERN_DI_NR,
  V4L2_EXT_VSC_PATTERN_SCALER,
  V4L2_EXT_VSC_PATTERN_MEMC,
  V4L2_EXT_VSC_PATTERN_DISPLAY,
  V4L2_EXT_VSC_PATTERN_RESERVED0,
  V4L2_EXT_VSC_PATTERN_RESERVED1,
  V4L2_EXT_VSC_PATTERN_RESERVED2,
  V4L2_EXT_VSC_PATTERN_RESERVED3
};

/**
 * @brief Set frame delay
 *
 * @rst
 * Functional Requirements
 *   This function sets delay buffer. Video buffer has to be added to set delay
 *   buffer. This is needed to adjust audio lip sync. (VSC SetDelayBuffer)
 *
 * Exception as Low delay Mode
 *   If low delay mode and frame delay mode operate simultaneously, a conflict may occur between the two flows.
 *
 *   To resolve this, different operations are performed for each low delay mode on/off.
 *
 *   1. The frame delay value must be set to 0 when operating in low delay mode.
 *   If the bGameMode parameter value of V4L2_CID_EXT_VPQ_LOW_DELAY_MODE is TRUE, low delay mode is enabled.
 *
 *   2. The frame delay value must be returns to its original value when low delay mode is turned off.
 *   If the bGameMode parameter value of V4L2_CID_EXT_VPQ_LOW_DELAY_MODE is FALSE, low delay mode is disabled.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_FRAME_DELAY.png
 *
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_FRAME_DELAY
 *
 *     //
 *     // parameter
 *     //
 *     int delay
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Pseudo Code
 *   .. code-block:: cpp
 *
 *     {
 *       CHECK the input parameter value of V4L2_CID_EXT_VPQ_LOW_DELAY_MODE
 *       IF bGameMode == TRUE THEN
 *           Set frame delay to 0
 *       ELSE
 *           Set frame delay to delay of input parameter value
 *
 *       IF any error has occurred THEN
 *           RETURN NOT_OK
 *       RETURN OK
 *     }
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set pattern
 *     struct v4l2_control control{0};
 *
 *     control.id = V4L2_CID_EXT_VSC_FRAME_DELAY;
 *     control.value = 2;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *     // Get pattern
 *     struct v4l2_control control{0};
 *
 *     control.id = V4L2_CID_EXT_VSC_FRAME_DELAY;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_FRAME_DELAY (V4L2_CID_USER_EXT_VSC_BASE + 4)

/**
 * @brief (Not Used from webOS26) Set zOrder mode
 *
 * @rst
 * Functional Requirements
 *   (Not Used from webOS26) This function sets Z order. (VSC SetZorder) The user client ensures that the
 *   v4l2 main device and the v4l2 sub device have the zorder value set
 *   sequentially. In the SoC vendor, after setting zorder value of v4l2 main
 *   device, when zorder value of v4l2 sub device is set, actually apply zorder of
 *   main path and sub path. Even if the device is disconnected, the zorder setting
 *   must be applied. The zorder setting must be applied to all devices
 *   regardless of whether the device is connected or not.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ZORDER-1.png
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ZORDER-2.png
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     // (Not Used from webOS26)
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_ZORDER
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vsc_zorder
 *     {
 *         unsigned char zorder;   // 0: bottom, 1: bottom+1,..
 *         unsigned char alpha;    // 0 ~ 255
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // (Not Used from webOS26) Set zOrder
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_zorder z1{0};
 *     struct v4l2_ext_vsc_zorder z2{0};
 *
 *     // v4l2_ext_vsc_zorder for main device
 *     z1.zorder= 1;
 *     z1.alpha= 45;
 *
 *     // v4l2_ext_vsc_zorder for sub device
 *     z2.zorder= 0;
 *     z2.alpha= 255;
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_ZORDER;
 *
 *     // Set zOrder for main device
 *     ext_controls.controls->ptr = (void *)&z1;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Set zOrder for sub device
 *     ext_controls.controls->ptr = (void *)&z2;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // (Not Used from webOS26) Get zOrder
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_zorder z{0};
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_ZORDER;
 *     ext_controls.controls->ptr = (void *)&z;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_ZORDER (V4L2_CID_USER_EXT_VSC_BASE + 5)

/**
 * @brief Set pattern mode
 *
 * @rst
 * Functional Requirements
 *   We want to know the scaler performance for window setting. (VSC
 *   GetLimitedWindow) If SOC can support any video size(there isn’t any
 *   limitation in window setting), this function Just returns 0x0. If SOC has
 *   some limitation, this function returns the limited value. This function gets
 *   the Min/Max that can be scaling setting.
 *
 *   Example)
 *   if Scaler can down scaling by 1/32(horizontal), 1/64(vertical)
 *   And Scaler can up scaling by 24(horizontal), 48(vertical),
 *   h_scalerdown_ratio = 32, v_scalerdown_ratio = 64, h_scaleup_ratio = 24,
 *   v_scaleup_ratio = 48 in VSC_SCALER_RATIO_T structure.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
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
 *     V4L2_CID_VSC_LIMITED_WIN_INFO
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vsc_scaler_ratio
 *     {
 *         int h_scaleup_ratio;
 *         int v_scaleup_ratio;
 *         int h_scaledown_ratio;
 *         int v_scaledown_ratio;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get limited window
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_scaler_ratio ratio{0};
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_VSC_LIMITED_WIN_INFO;
 *     ext_controls.controls->ptr = (void *)&ratio;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_LIMITED_WIN_RATIO (V4L2_CID_USER_EXT_VSC_BASE + 6)

/**
 * @brief Set pattern mode
 *
 * @rst
 * Functional Requirements
 *   This function is for measurement of video latency using SoC internal pattern and GPIO port.
 *   (VSC SetVideoLatencyPattern)
 *   How to measure video latency is like below by using this function.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_LATENCY_PATTERN-1.png
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_LATENCY_PATTERN-2.png
 *
 *   1. Generate white/black pattern which is located on video input.
 *   2. The pattern is overlaid on original video scene. Display pattern and video on same time.
 *   3. The pattern is repeated black and white, and synchronized by v-sync
 *   4. A GPIO port generate pulse which is synchronized by v-sync and changed
 * by the pattern color. ex) When the pattern is black the pulse is low, when
 * the pattern is white the pulse is changed to high synchronized by v-sync.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_LATENCY_PATTERN
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vsc_zorder
 *     {
 *         unsigned char zorder;   // 0: bottom, 1: bottom+1,..
 *         unsigned char alpha;    // 0 ~ 255
 *     };
 *     struct v4l2_ext_video_rect
 *     {
 *         unsigned short x;
 *         unsigned short y;
 *         unsigned short w;
 *         unsigned short h;
 *     };
 *
 *     enum v4l2_ext_vsc_latency_pattern
 *     {
 *         V4L2_EXT_VSC_PATTERN_BLACK = 0,
 *         V4L2_EXT_VSC_PATTERN_WHITE
 *     };
 *
 *     struct v4l2_ext_vsc_latency_pattern_info
 *     {
 *         struct v4l2_ext_video_rect r;
 *         enum v4l2_ext_vsc_latency_pattern p;
 *     };
 *
 *     //
 *     // On/Off
 *     //
 *     // On - w and h are not '0'.
 *     info.r.x = 100;
 *     info.r.y = 100;
 *     info.r.w = 300;
 *     info.r.h = 300;
 *
 *     // Off - w or h is '0'.
 *     info.r.x = 0;
 *     info.r.y = 0;
 *     info.r.w = 0;
 *     info.r.h = 0;
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // On latency pattern
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_vsc_latency_pattern_info info{0};
 *
 *     info.p = V4L2_EXT_VSC_PATTERN_WHITE;
 *     info.r.x = 100;
 *     info.r.y = 100;
 *     info.r.w = 300;
 *     info.r.h = 300;
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_LATENCY_PATTERN;
 *     ext_controls.controls->ptr = (void *)&info;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Off latency pattern
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_vsc_latency_pattern_info info{0};
 *
 *     info.p = V4L2_EXT_VSC_PATTERN_WHITE;
 *     info.r.x = 0;
 *     info.r.y = 0;
 *     info.r.w = 0;
 *     info.r.h = 0;
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_LATENCY_PATTERN;
 *     ext_controls.controls->ptr = (void *)&info;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_LATENCY_PATTERN (V4L2_CID_USER_EXT_VSC_BASE + 7)

/**
 * @brief set adaptive stream or airplay
 *
 * @rst
 * Functional Requirements
 *   This function sets '1' when video content is a adaptive stream to work
 *   seamless change in SOC driver. (VSC SetAdaptiveStream)
 *
 *   This function sets '2' when running airplay to change seamless output region in SOC driver.
 *
 *   **Air play mode '2'**
 *
 *   When change source resolution seamlessly,
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ADAPTIVE_STREAM-1.png
 *
 *   Change output region to the same AR seamlessly.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ADAPTIVE_STREAM-2.png
 *
 *   **Calculate Output Region**
 *
 *   When adaptive is 2, app will set the output region to 16x9 size. BSP change
 *   output region to the correct AR.
 *
 *   * ex1) app output region (0, 0, 3840, 2160), source resolution (0, 0, 1080,
 *     1920) => final output region (1312, 0, 1215, 2160)
 *
 *     * w = (2160 / 1920) x 1080 = 1215
 *     * h = 2160
 *     * x = 0 + (3840 - 1215) / 2 = 1312
 *     * y = 0
 *
 *   * ex2) app output region (100, 100, 1920, 1080), source resolution (0, 0,
 *     1080, 1080) => final output region (520, 100, 1080, 1080)
 *
 *     * w = 1080
 *     * h = 1080
 *     * x = 100 + (1920 - 1080) / 2 = 520
 *     * y = 100
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ADAPTIVE_STREAM-3.png
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_ADAPTIVE_STREAM
 *
 *     //
 *     // control value
 *     //
 *     0 (Off), 1 (On), 2 (Air play mode)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Adaptive Stream Mode
 *     struct v4l2_control control{0};
 *
 *     control.id = V4L2_CID_EXT_VSC_ADAPTIVE_STREAM;
 *     control.value = 1;      // On
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *
 *     // Get Adaptive Stream Mode
 *     struct v4l2_control control{0};
 *
 *     control.id = V4L2_CID_EXT_VSC_ADAPTIVE_STREAM;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_ADAPTIVE_STREAM (V4L2_CID_USER_EXT_VSC_BASE + 8)

/**
 * @brief sets RGB 444 Mode
 *
 * @rst
 * Functional Requirements
 *   This function sets RGB 444 Mode. This should be bypassed for RGB/YUV444
 *   format losslessly. (VSC SetRGB444)
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_RGB444
 *
 *     //
 *     // control value
 *     //
 *     0 (Off), 1 (On)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set RGB444 Mode
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_RGB444;
 *     control.value = 1;      // On
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *
 *     // Get RGB444 Mode
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_RGB444;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_RGB444 (V4L2_CID_USER_EXT_VSC_BASE + 9)

/**
 * @brief Sets SDR/HDR Type
 *
 * @rst
 * Functional Requirements
 *   This is a function that sets SDR/HDR type. It operates as HDR_Disconnect
 *   when HDR type is SDR, and operates as HDR_Connect when HDR type is others.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   see :cpp:any:`v4l2_ext_vsc_hdr_type`.
 *
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VSC_HDR_TYPE
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_vsc_hdr_type
 *     {
 *         V4L2_EXT_VSC_HDR_TYPE_SDR = 0,
 *         V4L2_EXT_VSC_HDR_TYPE_HDR10,
 *         V4L2_EXT_VSC_HDR_TYPE_DOLBY,
 *         V4L2_EXT_VSC_HDR_TYPE_HLG,
 *         V4L2_EXT_VSC_HDR_TYPE_PRIME,
 *         V4L2_EXT_VSC_HDR_TYPE_DOLBY_LL,
 *         V4L2_EXT_VSC_HDR_TYPE_DOLBY_RF,
 *         V4L2_EXT_VSC_HDR_TYPE_HDR_RESERVED2,
 *         V4L2_EXT_VSC_HDR_TYPE_HDR_RESERVED3
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set HDR Type
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_HDR_TYPE;
 *     control.value = V4L2_EXT_VSC_HDR_TYPE_HDR10;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *
 *     // Get HDR Type
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_HDR_TYPE;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_HDR_TYPE (V4L2_CID_USER_EXT_VSC_BASE + 11)

enum v4l2_ext_vsc_hdr_type {
  V4L2_EXT_VSC_HDR_TYPE_SDR = 0,
  V4L2_EXT_VSC_HDR_TYPE_HDR10,
  V4L2_EXT_VSC_HDR_TYPE_DOLBY,
  V4L2_EXT_VSC_HDR_TYPE_HLG,
  V4L2_EXT_VSC_HDR_TYPE_PRIME,
  V4L2_EXT_VSC_HDR_TYPE_DOLBY_LL,
  V4L2_EXT_VSC_HDR_TYPE_DOLBY_RF,
  V4L2_EXT_VSC_HDR_TYPE_HDR_RESERVED2,
  V4L2_EXT_VSC_HDR_TYPE_HDR_RESERVED3
};

/**
 * @brief Connects video front end and video output
 *
 * @rst
 * Functional Requirements
 *   This function connects VFE module by input and sets output
 *   mode for a scaler and disconnects VFE module by input and releases output
 *   mode for a scaler. (VSC Connect / VSC Disconnect)
 *   Black image should be displayed when input type is
 *   :cpp:any:`V4L2_EXT_VSC_INPUT_SRC_NONE` or output type is
 *   :cpp:any:`V4L2_EXT_VSC_DEST_NONE`.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *   It is guaranteed that disconnect occurs first before 'vsc close(ex.pm
 * suspend)'
 *   for normal operation. However, when disconnect occurs after 'vsc close'
 *   as an exception, system problems(ex. kernel panic) should not occur.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_CONNECT_INFO
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vsc_connect_info
 *     {
 *         struct v4l2_ext_vsc_input_src_info in;
 *         enum v4l2_ext_vsc_dest out;
 *     };
 *
 *     struct v4l2_ext_vsc_input_src_info
 *     {
 *         enum v4l2_ext_vsc_input_src src;
 *         unsigned char index;
 *         unsigned char attr;  //ATV : attr = 0, AV : attr = 1
 *     };
 *
 *     enum v4l2_ext_vsc_input_src
 *     {
 *         // V4L2_EXT_VSC_INPUT_SRC_NONE means "VSC Disconnect".
 *         V4L2_EXT_VSC_INPUT_SRC_NONE = 0,
 *         // The below enum values mean "VSC Connect".
 *         V4L2_EXT_VSC_INPUT_SRC_AVD,    //ATV : attr = 0, AV : attr = 1
 *         V4L2_EXT_VSC_INPUT_SRC_ADC,
 *         V4L2_EXT_VSC_INPUT_SRC_HDMI,
 *         V4L2_EXT_VSC_INPUT_SRC_VDEC,
 *         V4L2_EXT_VSC_INPUT_SRC_JPEG
 *         V4L2_EXT_VSC_INPUT_SRC_FB,     //Miracast TX
 *         V4L2_EXT_VSC_INPUT_SRC_DP,     //Display Port, USB C Port
 *         V4L2_EXT_VSC_INPUT_SRC_TEXTURE //Texture - TTV Ouput
 *     };
 *
 *     enum v4l2_ext_vsc_dest
 *     {
 *         // V4L2_EXT_VSC_DEST_NONE means "VSC Disconnect".
 *         V4L2_EXT_VSC_DEST_NONE = 0,
 *         // The below enum values mean "VSC Connect".
 *         V4L2_EXT_VSC_DEST_DISPLAY,  // DISPLAY (ex. PIP, Live Zoom)
 *         V4L2_EXT_VSC_DEST_VENC,     // VENC (ex. Analog Recording)
 *         V4L2_EXT_VSC_DEST_MEMORY,   // MEMORY (ex. Capture)
 *         V4L2_EXT_VSC_DEST_AVE
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using :cpp:any:`VIDIOC_S_EXT_CTRLS` and this control id.
 *
 *   Application can get data using :cpp:any:`VIDIOC_G_EXT_CTRLS` and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Connect
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_connect_info info{0};
 *
 *     info.in.src = V4L2_VSC_EXT_INPUT_SRC_HDMI;
 *     info.in.index = 2;
 *     info.out_mode = V4L2_EXT_VSC_DEST_DISPLAY;
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_CONNECT_INFO;
 *     ext_controls.controls->ptr = (void *)&info;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *
 *     // Disconnect
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_connect_info info{0};
 *
 *     info.in.src = V4L2_VSC_EXT_INPUT_SRC_NONE;
 *     info.out = V4L2_EXT_VSC_DEST_NONE;
 *
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_CONNECT_INFO;
 *     ext_controls.controls->ptr = (void *)&info;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_VSC_CONNECT_INFO (V4L2_CID_USER_EXT_VSC_BASE + 12)

/**
 * @brief Get active window data
 *
 * @rst
 * Functional Requirements
 *   This function registers active video window callback function. (VSC
 *   RegisterActiveWindowCallback) The video window dimension is an output frame
 *   from video decoder and is not cropped. Active video window means area with
 *   real video area from pillar box or letter box video image which includes
 *   black bars. Usually, active area might be 16:9,16:10,4:3 or 90 degree
 *   rotated of them. But it is acceptable to return dimension that does not fit
 *   this aspect ratio. LG Application will detect aspect ratio and rotation
 *   using the active area size. This is a function that register Active Video Window
 
 *   Callback.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO.png
 *
 *   When there are two video objects like above picture, that is, red circle
 *   and yellow rectangle, Original video window is black rectangle. Active video
 *   window detected will be blue rectangle. To calculate active area, assume
 *   that inactive area is filled with black color. It should not be assumed that
 *   active area is center aligned in the screen. If there's a performance
 *   issue,assume active window's height is the same with video window height.
 *
 *   - Driver should implement epoll() operation for this flow. You need to
 *     implement the feature of epoll() in driver side. User client gets the
 *     kernel event from epoll().
 *
 *   - This command works in pairs with V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN.
 *     Please refer to the command of V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS
 *     VIDIOC_DQEVENT
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vsc_active_win_info
 *     {
 *         struct v4l2_ext_video_rect original;
 *         struct v4l2_ext_video_rect active;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // After epoll event occurs
 *     struct v4l2_event ev{0};
 *
 *     ioctl(fd, VIDIOC_DQEVENT, &ev);
 *
 *     if(ev.id == V4L2_CID_VSC_SUBSCRIBE_MUTE_OFF)
 *     {
 *         struct v4l2_ext_controls ext_controls{0};
 *         struct v4l2_ext_control ext_control{0};
 *         struct v4l2_ext_vsc_active_win_info info{0};
 *
 *         ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *         ext_controls.count = 1;
 *         ext_controls.controls = &ext_control;
 *         ext_controls.controls->id = V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO;
 *         ext_controls.controls->ptr = (void *)&info;
 *
 *         ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *     }
 * @endrst
 */
#define V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO (V4L2_CID_USER_EXT_VSC_BASE + 13)

/**
 * @brief Control freeze mode
 *
 * @rst
 * Functional Requirements
 *   This function freezes or unfreezes Input video frame buffer for getting video data.
 *   (VSC_FreezeVideoFrameBuffer)
 *   This is used by ADC & Self-Diagnostics and video data should be frozen before start ADC & Self-Diagnostics.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VSC_FREEZE_FRAME_BUFFER
 *
 *     //
 *     // parameter
 *     //
 *     0 (Off), 1 (On);
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set Freeze Buffer
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_FREEZE_FRAME_BUFFER;
 *     control.value = 1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *
 *     // Get Freeze Buffer
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_FREEZE_FRAME_BUFFER;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_FREEZE_FRAME_BUFFER (V4L2_CID_USER_EXT_VSC_BASE + 14)

/**
 * @brief Read frame information
 *
 * @rst
 * Functional Requirements
 *   This function reads input video frame buffer for checking video data. This is
 *   used by ADC & Self-Diagnostics.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
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
 *     V4L2_CID_EXT_VSC_READ_FRAME_BUFFER_INFO
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_video_rect
 *     {
 *         unsigned short x;
 *         unsigned short y;
 *         unsigned short w;
 *         unsigned short h;
 *     };
 *     struct v4l2_ext_vsc_color_pixel_data
 *     {
 *         unsigned int y;    // standard pixel color Y
 *         unsigned int cb;   // standard pixel color Cb
 *         unsigned int cr;   // standard pixel color Cr
 *     };
 *
 *     enum v4l2_ext_vsc_color_pixel_format
 *     {
 *         V4L2_EXT_VSC_COLOR_PIXEL_FORMAT_YUV = 0,
 *         V4L2_EXT_VSC_COLOR_PIXEL_FORMAT_RGB
 *     };
 *
 *     enum v4l2_ext_vsc_color_pixel_depth
 *     {
 *         V4L2_EXT_VSC_COLOR_PIXEL_8BIT = 0,
 *         V4L2_EXT_VSC_COLOR_PIXEL_10BIT
 *     };
 *
 *     struct v4l2_ext_vsc_pixel_color_info
 *     {
 *         struct v4l2_ext_video_rect r;
 *         union {
 *             struct v4l2_ext_vsc_color_pixel_data *p_data;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *         enum v4l2_ext_vsc_color_pixel_format format;
 *         enum v4l2_ext_vsc_color_pixel_depth depth;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Color Pixel info
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_pixel_color_info info{0};
 *
 *     info.p_data = (struct v4l2_ext_vsc_color_pixel_data*)malloc  \
 *                   (GRAB_SIZE * sizeof(struct v4l2_ext_vsc_color_pixel_data));
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_READ_FRAME_BUFFER_INFO;
 *     ext_controls.controls->ptr = (void *)&info;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_VSC_READ_FRAME_BUFFER_INFO (V4L2_CID_USER_EXT_VSC_BASE + 15)

/**
 * @brief Set occupation of another path
 *
 * @rst
 * Functional Requirements
 *   This function is used to send HFR information to soc. Some of SoC need to use
 *   2 video path for displaying HFR source(over 2K resolution). We'll enable HFR
 *   mode when we detect HFR mode. (VDEC/Gstreamer will send HFR information to
 *   VSC.)
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   This control id is used for the video device(#30) of main scaler only.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER
 *
 *     //
 *     // parameter
 *     //
 *     0 (Off)
 *     1 (On) : Use 2 video path (both main and sub) for displaying HFR source.
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set data
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER;
 *     control.value = 1 or 0; // 1 : on, 0 : off
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *
 *     // Get data
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_OCCUPATION_SUB_SCALER (V4L2_CID_USER_EXT_VSC_BASE + 16)

/**
 * @brief Set video/OSD input crop window and output window region for Orbit
 *
 * @rst
 * Functional Requirements
 *   This function is used to send input crop, output window size information for Orbit.
 *   When this is called, driver needs to do:
 *
 *   * | Crop video/OSD input window properly by given input crop window information.
 *   * | Scale up or down cropped video/OSD to given output window size.
 *     | Note that this output window size is not just displayed on the screen,
 *     | but the actual display area will be determined by the :c:macro:`V4L2_CID_EXT_VSC_ORBIT_MOVE`.
 *   * | Parameters
 *     | video_input/osd_input : crop size of original input source.
 *     | video_output/osd_output : scaling size of video_crop/osd_crop.
 *   * | Return error when driver can't do above for some reasons such as Bandwidth, HW limitation.
 *
 *   To distinguish Orbit justscan and overscan modes, driver can use crop/output window size values.
 *
 *   Orbit justscan case :
 *
 *   * | video_input/osd_input(crop sizes) are same with original sources.
 *     | And output window sizes will be same as screen(panel) size.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ORBIT-1.png
 *
 *   Orbit overscan case :
 *
 *   * | video_input is smaller than original source.
 *     | video_input is bigger than crop of :c:macro:`V4L2_CID_EXT_VSC_WIN_REGION`.
 *     | osd_input is smaller than original source.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ORBIT-3.png
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ORBIT-4.png
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   * | Video windows(usually called Main/Sub) will be distinguished by device fd,
 *     | :c:macro:`V4L2_EXT_DEV_PATH_SCALER0` and :c:macro:`V4L2_EXT_DEV_PATH_SCALER1`.
 *   * | OSD will be controlled by only :c:macro:`V4L2_EXT_DEV_PATH_SCALER0`.
 *     | Driver should ignore any OSD related parameters given in other device fd.
 *   * | Driver ignore parameters with the same value as previous,
 *     | except when new :c:macro:`V4L2_CID_EXT_VSC_WIN_REGION` is called.
 *     | For example, if OSD input crop window is same but video input crop window is changed,
 *     | driver needs to ignore OSD parameters and only change video crop window.
 *   * | This should be called together with new :c:macro:`V4L2_CID_EXT_VSC_WIN_REGION`.
 *     | If Orbit feature is on in current machine.
 *   * | Width and height value should be even number always.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VSC_ORBIT_WINDOW
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_video_rect
 *     {
 *         unsigned short x;
 *         unsigned short y;
 *         unsigned short w;
 *         unsigned short h;
 *     };
 *
 *     struct v4l2_ext_vsc_orbit_window {
 *         struct v4l2_ext_video_rect osd_input;
 *         struct v4l2_ext_video_rect video_input;
 *         struct v4l2_ext_video_rect osd_output;
 *         struct v4l2_ext_video_rect video_output;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Orbit justscan
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_orbit_window orbit_window{0};
 *
 *     osd_input.x = 0;
 *     osd_input.y = 0;
 *     osd_input.w = 1920;
 *     osd_input.h = 1080;
 *
 *     video_input.x = 0;
 *     video_input.y = 0;
 *     video_input.w = 1920;
 *     video_input.h = 1080;
 *
 *     osd_output.x = 0;
 *     osd_output.y = 0;
 *     osd_output.w = 3840;
 *     osd_output.h = 2160;
 *
 *     video_output.x = 0;
 *     video_output.y = 0;
 *     video_output.w = 3840;
 *     video_output.h = 2160;
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count         = 1;
 *     ext_controls.controls      = &ext_control;
 *     ext_controls.controls->id  = V4L2_CID_EXT_VSC_ORBIT_WINDOW;
 *     ext_controls.controls->ptr = (void *)&orbit_window;
 *
 *     // Orbit overscan
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_orbit_window orbit_window{0};
 *
 *     osd_input.x = 0;
 *     osd_input.y = 0;
 *     osd_input.w = 1908;
 *     osd_input.h = 1074;
 *
 *     video_input.x = 0;
 *     video_input.y = 0;
 *     video_input.w = 1860;
 *     video_input.h = 1044;
 *
 *     osd_output.x = 0;
 *     osd_output.y = 0;
 *     osd_output.w = 3860;
 *     osd_output.h = 2170;
 *
 *     video_output.x = 0;
 *     video_output.y = 0;
 *     video_output.w = 3872;
 *     video_output.h = 2176;
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count         = 1;
 *     ext_controls.controls      = &ext_control;
 *     ext_controls.controls->id  = V4L2_CID_EXT_VSC_ORBIT_WINDOW;
 *     ext_controls.controls->ptr = (void *)&orbit_window;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_ORBIT_WINDOW (V4L2_CID_USER_EXT_VSC_BASE + 17)

/**
 * @brief Set video/OSD input crop window and output window region for Orbit
 *
 * @rst
 * Functional Requirements
 *   This function is used to send display window information for Orbit.
 *   When this is called, driver needs to do:
 *
 * .. important::
 *   * | Move display window on the scaled input window corresponding to given parameters.
 *   * | Parameters
 *     | video_input/osd_input : the part of video/OSD area to be actually displayed
 *     | of video_scale/osd_scale set by :c:macro:`V4L2_EXT_DEV_PATH_SCALER0`.
 *     | video_output/osd_output : the position and width/height where
 *     | video_input/osd_input will be shown on the screen(panel).
 *   * | Return error when driver can't do above for some reasons such as Bandwidth, HW limitation.
 *
 *   Orbit justscan case :
 *
 *     * | Scaled video/OSD is moving on the screen.
 *     * | As Orbit moves, some lines of scaled input can be out of screen(panel).
 *     * | As Orbit moves, some lines of screen can be blank and filled with black video.
 *     * | Check below sample images as examples.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ORBIT-1.png
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ORBIT-2.png
 *
 *   Orbit overscan case :
 *
 *     * | Display area moves on the scaled input video/OSD.
 *     * | As Orbit moves, input video/OSD area will be changed.
 *     * | There is no blank area in screen, always full size will be shown.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ORBIT-3.png
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ORBIT-4.png
 *
 * .. important::
 *   * | Video and OSD can be moved at the same time or at different times.
 *     | Because they can have different time period for their each step.
 *   * | Driver ignore parameters with the same value as previous,
 *     | For example, if only video is moving in current step, OSD parameters will be the same as previous.
 *   * | OSD will be controlled by only :c:macro:`V4L2_EXT_DEV_PATH_SCALER0`.
 *     | Driver should ignore any OSD related parameters given in other device fd.
 *   * | Driver does not scale up/down by this CID.
 *     | If displaying area is not enough to show video/OSD,
 *     | driver should cut the video or OSD out of display area rather than scaling up/down.
 *     | Check 'Orbit justscan case' as an example.
 *   * | Width and height value should be even number always.
 *   * | :c:macro:`V4L2_CID_EXT_VSC_ORBIT_WINDOW` should be called before this.

 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VSC_ORBIT_MOVE
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_video_rect
 *     {
 *         unsigned short x;
 *         unsigned short y;
 *         unsigned short w;
 *         unsigned short h;
 *     };
 *
 *     struct v4l2_ext_vsc_orbit_move {
 *         struct v4l2_ext_video_rect osd_input;
 *         struct v4l2_ext_video_rect video_input;
 *         struct v4l2_ext_video_rect osd_output;
 *         struct v4l2_ext_video_rect video_output;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Orbit move
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_orbit_move orbit_move{0};
 *
 *     osd_input.x = 0;
 *     osd_input.y = 0;
 *     osd_input.w = 3839;
 *     osd_input.h = 2159;
 *
 *     video_input.x = 0;
 *     video_input.y = 0;
 *     video_input.w = 3839;
 *     video_input.h = 2159;
 *
 *     osd_output.x = 1;
 *     osd_output.y = 1;
 *     osd_output.w = 3839;
 *     osd_output.h = 2159;
 *
 *     video_output.x = 1;
 *     video_output.y = 1;
 *     video_output.w = 3839;
 *     video_output.h = 2159;
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count         = 1;
 *     ext_controls.controls      = &ext_control;
 *     ext_controls.controls->id  = V4L2_CID_EXT_VSC_ORBIT_MOVE;
 *     ext_controls.controls->ptr = (void *)&orbit_move;
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_ORBIT_MOVE (V4L2_CID_USER_EXT_VSC_BASE + 18)

//
// VSC class subscription IDs
//

/**
 * @brief Notify mute off
 *
 * @rst
 * Functional Requirements
 *   This function is used to check time that internal mute is turned off. (VSC
 *   RegisterMuteOffCallBack) Driver should make the EVENT of file_handler when
 *   driver internal mute is turned off. This relatives with "V4L2_CID_BG_COLOR".
 *   This is a function that registers callback function to know the driver side
 *   internal mute off time.
 *
 *   - After the event of "V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF" is registered by
 *     the command of "VIDIOC_SUBSCRIBE_EVENT" in driver, driver should generate
 *     the event of "V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF" whenever the internal
 *     mute is turned off.
 *
 *   - Driver should implement epoll() operation for this flow. You need to
 *     implement the feature of epoll() in driver side. User client gets the
 *     kernel event from epoll().
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_CTRL
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set subscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF;
 *
 *     ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *     // Set unsubscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF;
 *
 *     ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_SUBSCRIBE_MUTE_OFF (V4L2_CID_USER_EXT_VSC_BASE + 30)

/**
 * @brief Register/Unregister active window event
 *
 * @rst
 * Functional Requirements
 *   This function registers active video window callback function. (VSC
 *   RegisterActiveWindowCallback) The video window dimension is an output frame
 *   from video decoder and is not cropped. Active video window means area with
 *   real video area from pillar box or letter box video image which includes
 *   black bars. Usually, active area might be 16:9,16:10,4:3 or 90 degree
 *   rotated of them. But it is acceptable to return dimension that does not fit
 *   this aspect ratio. LG Application will detect aspect ratio and rotation using
 *   the active area size. This is a function that register Active Video Window
 *   Callback.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO.png
 *
 *   When there are two video objects like above picture, that is, red circle
 *   and yellow rectangle, Original video window is black rectangle. Active video
 *   window detected will be blue rectangle. To calculate active area, assume that
 *   inactive area is filled with black color. It should not be assumed that
 *   active area is center aligned in the screen. If there's a performance issue,
 *   assume active window's height is the same with video window height.
 *
 *   - Driver should implement epoll() operation for this flow. You need to
 *     implement the feature of epoll() in driver side. User client gets the
 *     kernel event from epoll().
 *
 *   - This command works in pairs with V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO.
 *     Please refer to the command of V4L2_CID_EXT_VSC_ACTIVE_WIN_INFO.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_CTRL
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set subscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN;
 *
 *     ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *     // Set unsubscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN;
 *
 *     ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_SUBSCRIBE_ACTIVE_WIN (V4L2_CID_USER_EXT_VSC_BASE + 32)

/**
 * @brief Get video size and delay
 *
 * @rst
 * Functional Requirements
 *   Delay occurs due to video buffers which exist to enhance the picture quality
 *   on a video path. The video is shown slower than the OSD border due to the
 *   delay. We cannot perfectly remove video delay to match between video and OSD,
 *   so we will add the delay to OSD punch out. To add the delay to OSD punch out,
 *   application need to know the video delay size. Driver should send the delay
 *   time between scaling and OSD mixing to webOS thru this callback function.
 *   For a requirement, we will add the delay to OSD punch out to match between
 *   video and OSD. To add the delay to OSD punch out, application need to know
 *   the video delay size. (HAL_VSC_RegisterWindowSettingDelayCallback()). The
 *   registered kernel event should be generated when driver apply window setting
 *   physically to H/W as shown below. (EX, 4 and 5 setting of purple color).
 *
 *   - Driver should implement epoll() operation for this flow. You need to
 *     implement the feature of epoll() in driver side. User client gets the
 *     kernel event from epoll().
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION-1.png
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION-2.png
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *     VIDIOC_DQEVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_CTRL
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION
 *
 *     //
 *     // Parameter
 *     //
 *     // Use data[64] in the struct v4l2_event in videodev2.h
 *     // This struct is used by VIDIOC_DQEVENT.
 *     struct v4l2_event {
 *         __u32               type;
 *         union {
 *             struct v4l2_event_vsync     vsync;
 *             struct v4l2_event_ctrl      ctrl;
 *             struct v4l2_event_frame_sync    frame_sync;
 *             struct v4l2_event_src_change    src_change;
 *             struct v4l2_event_motion_det    motion_det;
 *             __u8                data[64];
 *         } u;
 *         __u32               pending;
 *         __u32               sequence;
 *         struct timespec         timestamp;
 *         __u32               id;
 *         __u32               reserved[8];
 *     };
 *
 *     // data[0] - window id
 *     // data[1~2] - the position of x
 *     // data[3~4] - the position of y
 *     // data[5~6] - the size of w
 *     // data[7~8] - the size of h
 *     // data[9~10] - delay time
 *     // data[11~12] - the punch position of x
 *     // data[13~14] - the punch position of y
 *     // data[15~16] - the punch size of w
 *     // data[17~18] - the punch size of h
 *     // Please refer to the shown table with [Table-1] Data type and data order
 *
 * [Table-1] Data type and data order
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION-3.png
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT/VIDIOC_DQEVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set subscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION;
 *
 *     ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *     // Set unsubscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION;
 *
 *     ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 *     // Get data
 *     ioctl(fd, VIDIOC_DQEVENT, &ev);
 *
 *      if(ev.id == V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION)
 *      {
 *          // get information
 *          // ev.u.data[0] ~ ev.u.data[10];
 *      }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_SUBSCRIBE_APPLYING_DONE_WINDOW_REGION (V4L2_CID_USER_EXT_VSC_BASE + 34)

/**
 * @brief Send the aspect ratio policy values to vsc driver.
 *
 * @rst
 * Functional Requirements
 *   To get calculated window values for aspect ratio thru aspectratiodrv ibrary, need the aspect ratio policy values.
 *   videooutputd will send the aspect ratio policy values to vsc driver thru this control id.
 *
 *   1) out : Output region to display video. This is a App policy for aspect ratio.
 *   2) system_policy : webOS policy of system for aspect ratio.
 *   3) setting_policy : webOS policy of setting for aspect ratio.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   vsc driver should use aspectratiodrv.ko.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_video_rect
 *     {
 *         unsigned short x;   // horizontal start position
 *         unsigned short y;   // vertical start position
 *         unsigned short w;   // horizontal size(width)
 *         unsigned short h;   // vertical size(height)
 *     };
 *
 *     struct v4l2_ext_vsc_zoom_data
 *     {
 *         unsigned short h_ratio;
 *         unsigned short v_ratio;
 *         unsigned short h_position;
 *         unsigned short v_position;
 *     };
 *
 *     struct v4l2_ext_system_policy
 *     {
 *         struct v4l2_ext_video_rect  panel;
 *         unsigned short              country_grp;
 *         unsigned short              content_type;
 *         unsigned short              source_index;
 *     };
 *
 *     struct v4l2_ext_setting_policy
 *     {
 *         struct v4l2_ext_vsc_zoom_data   zoom_data;
 *         unsigned short                  just_scan;
 *         unsigned short                  aspect_ratio;
 *         unsigned short                  rotate;
 *         unsigned short                  orbit_over_scan;
 *         unsigned short                  screen_position;
 *         unsigned short                  media_afd_property;
 *         unsigned short                  overscan_appropriate_flag;
 *         unsigned short                  scan_type;
 *     };
 *
 *     struct v4l2_ext_vsc_aspectratio_policy
 *     {
 *         struct v4l2_ext_video_rect       out;            // Output region to display video
 *         struct v4l2_ext_system_policy    system_policy;  // webOS policy of system
 *         struct v4l2_ext_setting_policy   setting_policy; // webOS policy of setting
 *         struct v4l2_ext_video_rect       punch;          // punch size for the callback
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     #include "export_vsc_adapter.h"
 *     #include "videodev2-ext.h"
 *
 *     struct v4l2_ext_vsc_aspectratio_policy aspectratio_policy; // policy from videooutputd thru V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY
 *
 *     struct v4l2_ext_video_rect source_rect;                    // Resolution from input source
 *     unsigned short wss_afd;                                    // AFD or WSS from input source
 *     unsigned short par_width;                                  // PAR width from input source
 *     unsigned short par_height;                                 // PAR height from input source
 *
 *     struct v4l2_ext_video_rect calculated_input_rect;  // calculated crop region for input source
 *     struct v4l2_ext_video_rect calculated_output_rect; // calculated output region to display video
 *
 *     ioctl
 *     {
 *         switch (controls->id)
 *         {
 *             case V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY :
 *                 aspectratio_policy.out = controls->ptr->out;
 *                 aspectratio_policy.system_policy = controls->ptr->system_policy;
 *                 aspectratio_policy.setting_policy = controls->ptr->setting_policy;
 *         }
 *     }
 *
 *
 *     dynamic_aspectratio
 *     {
 *         int ret;
 *
 *         if (vsc_getAspectratioCallbackFp->pfnAspectratiodrvCalculate != NULL)
 *         {
 *             ret = vsc_getAspectratioCallbackFp->pfnAspectratiodrvCalculate(
 *                 source_rect,                    // Resolution of input source
 *                 aspectratio_policy.out,        // Output region to display video
 *                 wss_afd,                        // AFD or WSS of input source
 *                 par_width,                      // PAR width of input source
 *                 par_height,                     // PAR height of input source
 *                 aspectratio_policy.system_policy,   // webOS policy of system
 *                 aspectratio_policy.setting_policy, // webOS policy of setting
 *
 *                 &calculated_input_rect, // calculated crop region for input source
 *                 &calculated_output_rect // calculated output region to display video
 *                 );
 *         }
 *     }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_ASPECTRATIO_POLICY (V4L2_CID_USER_EXT_VSC_BASE + 35)

/**
 * @brief Get bsp error
 *
 * @rst
 * Functional Requirements
 *   To get error information whenever BSP Scaler driver detect error status for
 *   debugging
 *
 *     - Driver should implement epoll() operation for this flow. You need to
 *       implement the feature of epoll() in driver side. User client gets the
 *       kernel event from epoll().
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *     VIDIOC_DQEVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_CTRL
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR
 *
 *     //
 *     // Parameter
 *     //
 *     // Use data[64] in the struct v4l2_event in videodev2.h
 *     // This struct is used by VIDIOC_DQEVENT.
 *     struct v4l2_event {
 *         __u32               type;
 *         union {
 *             struct v4l2_event_vsync     vsync;
 *             struct v4l2_event_ctrl      ctrl;
 *             struct v4l2_event_frame_sync    frame_sync;
 *             struct v4l2_event_src_change    src_change;
 *             struct v4l2_event_motion_det    motion_det;
 *             __u8                data[64];
 *         } u;
 *         __u32               pending;
 *         __u32               sequence;
 *         struct timespec         timestamp;
 *         __u32               id;
 *         __u32               reserved[8];
 *     };
 *
 *     data[64] - error description string(Maximum string size 63)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT/VIDIOC_DQEVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set subscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR
 *
 *     ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *     // Set unsubscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR
 *
 *     ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 *     // Get data
 *     ioctl(fd, VIDIOC_DQEVENT, &ev);
 *
 *      if(ev.id == V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR)
 *      {
 *          // get error description string data[64];
 *      }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_SUBSCRIBE_BSP_ERROR (V4L2_CID_USER_EXT_VSC_BASE + 36)

/**
 * @brief get actual video delay from scaler input to SoC output
 *
 * @rst
 * Functional Requirements
 *   LG want to get video delay value from scaler input to SoC output whenever video delay value is changed.
 *
 *     - Driver should implement epoll() operation for this flow. You need to
 *       implement the feature of epoll() in driver side. User client gets the
 *       kernel event from epoll().
 *
 *   If delay value is often or always changed because comparing value is small.
 *   So this behavior can be affected to CPU performance. You can adjust the comparing value.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *     VIDIOC_DQEVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_CTRL
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY
 *
 *     //
 *     // Parameter
 *     //
 *     // Use data[64] in the struct v4l2_event in videodev2.h
 *     // This struct is used by VIDIOC_DQEVENT.
 *     struct v4l2_event {
 *         __u32               type;
 *         union {
 *             struct v4l2_event_vsync     vsync;
 *             struct v4l2_event_ctrl      ctrl;
 *             struct v4l2_event_frame_sync    frame_sync;
 *             struct v4l2_event_src_change    src_change;
 *             struct v4l2_event_motion_det    motion_det;
 *             __u8                data[64];
 *         } u;
 *         __u32               pending;
 *         __u32               sequence;
 *         struct timespec         timestamp;
 *         __u32               id;
 *         __u32               reserved[8];
 *     };
 *
 *     // data[0] - window id
 * 					decimal, 7~0bit(LSB)
 *					0 : #define V4L2_EXT_DEV_PATH_SCALER0 "/dev/video30"
 *          1 : #define V4L2_EXT_DEV_PATH_SCALER1 "/dev/video31"
 *          2 : #define V4L2_EXT_DEV_PATH_SCALER2 "/dev/video32"
 *          3 : #define V4L2_EXT_DEV_PATH_SCALER3 "/dev/video33"
 * 		//data[1] - delay time
 *					decimal , lower 8bits, 7~0bit(LSB)
 *		//data[2] - delay time
 *					decimal , upper 8bits , (MSB)15~8bit
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set subscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY;
 *
 *     ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *		// thread control part
 *		struct v4l2_event ev;
 *		// Create thread that handles each event
 *		for (;;)
 *		{
 *			int16 delay_time = 0;
 *			epoll();
 *			ioctl(fd, VIDIOC_DQEVENT, &ev);
 *		    if(ev.id == V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY)
 *		    {
 *		        // get information
 *		        window_id = ev.u.data[0];
 *		        delay_time = ev.u.data[1] + (ev.u.data[2] << 8);
 *		    }
 *   	}
 *
 *     // Set unsubscribe
 *     struct v4l2_event_subscription event{0};
 *
 *     event.type = V4L2_EVENT_CTRL;
 *     event.id = V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY;
 *
 *     ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_SUBSCRIBE_VIDEO_DELAY (V4L2_CID_USER_EXT_VSC_BASE + 37)


/**
 * @brief get capability of scaler device
 *
 * @rst
 * Functional Requirements
 *   LG want to get information about scaler device at initialized time.
 *
 *     - Driver should provide information about scaler divice. For example,
 *       number of outputscalers, HW planes on which differenct video output
 *       data can be drawn.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
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
 *     V4L2_CID_EXT_VSC_DEVICE_CAPABILITY
 *
 *     //
 *     // Parameter
 *     //
 *     struct v4l2_ext_vsc_device_capability
 *     {
 *         int num_planes;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get device capability
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_device_capability {0};
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_DEVICE_CAPABILITY;
 *     ext_controls.controls->ptr = (void *)&ratio;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_DEVICE_CAPABILITY (V4L2_CID_USER_EXT_VSC_BASE + 38)

/**
 * @brief Set scan mode(deinterlace)
 *
 * @rst
 * Functional Requirements
 *   This function controls scan mode.
 * 
 *   It should be supported on interlace input.
 * 
 *   - field merge :  display deinterlaced video. combine top and bottom field data of interlaced video. (default)
 * 
 *   - line doubler : display double repeated each field data of interlaced video.
 * 
 *   - inter field : display only double repeated top field data of interlaced video.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_SCAN_MODE
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_vsc_scan_mode {
 *     {
 *      V4L2_EXT_VSC_SCAN_MODE_FIELD_MERGE = 0, // deinterlace
 *      V4L2_EXT_VSC_SCAN_MODE_LINE_DOUBLER = 1,
 *      V4L2_EXT_VSC_SCAN_MODE_INTER_FIELD = 2,
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set pattern
 *     struct v4l2_control control{0};
 *
 *     control.id = V4L2_CID_EXT_VSC_SCAN_MODE;
 *     control.value = V4L2_EXT_VSC_SCAN_MODE_FIELD_MERGE;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_SCAN_MODE (V4L2_CID_USER_EXT_VSC_BASE + 39)

/**
 * @brief Controls window region scaling option
 *
 * @rst
 * Functional Requirements
 *   This function controls window region scaling option.
 * 
 *   It should be supported on external HDMI input.
 * 
 *   - Pixel to Pixel Off (default)
 *      Normal scaling screnario. window reigon controlled by V4L2_CID_EXT_VSC_WIN_REGION
 * 
 *   - Pixel to Pixel On
 *      Check the size of the crop and output region.
 *      If the output is the same size as the crop, it is output as is without scaling(1:1).
 *      If the output is a 1:N integer multiple of the crop, upscale with pixel repeat
 *      In other cases, it operates as Pixel to Pixel Off.
 * 
 *   - Call Sequence
 *      * this should be called before :c:macro:`V4L2_CID_EXT_VSC_WIN_REGION`.
 * 
 *   - Supported Resolutions
 *      It works on only predefined resolution
 * 
 *      +------------+-------------+
 *      | Format     | Resolution  |
 *      +============+=============+
 *      | SD NTSC    | 720 X 480   |
 *      +------------+-------------+
 *      | SD NTSC D1 | 720 X 486   |
 *      +------------+-------------+
 *      | SD PAL     | 720 X 576   |
 *      +------------+-------------+
 *      | HD 720     | 1280 X 720  |
 *      +------------+-------------+
 *      | HD 1080    | 1920 X 1080 |
 *      +------------+-------------+
 *      | DCI 2K     | 2048 X 1080 |
 *      +------------+-------------+
 *      | UHD        | 3840 X 2160 |
 *      +------------+-------------+
 *      | DCI 4K     | 4096 X 2160 |
 *      +------------+-------------+
 *      | 8K UHD     | 7680 X 4320 |
 *      +------------+-------------+
 *      | DCI 8K     | 8192 X 4320 |
 *      +------------+-------------+
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_PIXEL_TO_PIXEL
 *
 *     //
 *     // parameter
 *     //
 *     true : pixel to pixel on
 *     false : pixel to pixel off
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct v4l2_control control{0};
 *
 *     control.id = V4L2_CID_EXT_VSC_PIXEL_TO_PIXEL;
 *     control.value = true;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_PIXEL_TO_PIXEL (V4L2_CID_USER_EXT_VSC_BASE + 40)

/**
 * @brief Set zOrder mode of all windows at once
 *
 * @rst
 * Functional Requirements
 *   This function sets Z order mode of all windows at once. (VSC SetZorder) The user client ensures that the
 *   v4l2 main device and the v4l2 sub device have the zorder and alpha value set
 *   sequentially. In the SoC vendor, after setting zorder and alpha value of v4l2 main
 *   device, when zorder and alpha value of v4l2 sub device is set, actually apply zorder and alpha of
 *   main path and sub path. Even if the device is disconnected, the zorder setting
 *   must be applied. The zorder setting must be applied to all devices
 *   regardless of whether the device is connected or not.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ZORDER-1.png
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ZORDER-2.png
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There is no constraint.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VSC_ALPHA_ZORDER
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vsc_zorder_info
 *     {
 *         int length;
 *         // length: Number of output scaler.
 *         // length is the same value as num_planes used in V4L2_CID_EXT_VSC_DEVICE_CAPABILITY.
 *         // length is always the same value and is the valid size of the structure pointer.
 *         union {
 *           struct v4l2_ext_vsc_zorder *z; // An structure pointer of v4l2_ext_vsc_zorder.
 *           unsigned long long sizer; // To ensure 64bit compatibility.
 *         };
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set zOrder
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_zorder_info z_info;
 *     memset(&z_info, 0, sizeof(z_info));
 *
 *     z_info.length = 2;
 *     z_info.z = (struct v4l2_ext_vsc_zorder *)malloc(sizeof(struct v4l2_ext_vsc_zorder) * z_info.length);
 *
 *     if (z_info.z != nullptr) {
 *         // v4l2_ext_vsc_zorder for main device
 *         z_info.z[0].zorder= 1;
 *         z_info.z[0].alpha= 45;
 *
 *         // v4l2_ext_vsc_zorder for sub device
 *         z_info.z[1].zorder= 0;
 *         z_info.z[1].alpha= 255;
 *
 *         ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *         ext_controls.count = 1;
 *         ext_controls.controls = &ext_control;
 *         ext_controls.controls->id = V4L2_CID_EXT_VSC_ALPHA_ZORDER;
 *
 *         // Set zOrder for all windows at once.
 *         ext_controls.controls->ptr = (void *)&z_info;
 *         ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *         free(z_info.z);
 *     }
 *
 *     // Get zOrder
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_vsc_zorder_info z_info{0};
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_ALPHA_ZORDER;
 *     ext_controls.controls->ptr = (void *)&z_info;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_ALPHA_ZORDER (V4L2_CID_USER_EXT_VSC_BASE + 41)

/**
 * @brief Send the orbit policy values to vsc driver.
 *
 * @rst
 * Functional Requirements
 *   To get calculated orbit position values for orbit through orbit-calculator kdriver ibrary, need the orbit policy values.
 *   orbitcontroller will send the orbit policy values to vsc driver through this control id.
 *
 *   .. image:: /renderer/resources/scaler-V4L2_CID_EXT_VSC_ORBIT_POLICY.png
 *
 *   1) orbit_onOff: orbit enable value of setting UI
 *   2) osd_resolution: resolution of graphic driver
 *   3) panel_resolution: resolution of TV panel
 *   4) region: webOS policy of setting for calculating orbit position.
 *   5) video_step: orbit move step for video
 *   6) osd_step: orbit move step for osd
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   vsc driver should use orbit-calculator.ko.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_G_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     V4L2_CID_EXT_VSC_ORBIT_POLICY
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_vsc_orbit_position
 *     {
 *        struct v4l2_ext_vsc_orbit_window orbit_window;
 *        struct v4l2_ext_vsc_orbit_move orbit_move;
 *     };
 *
 *     enum v4l2_ext_vsc_orbit_on_off
 *     {
 *        V4L2_EXT_VSC_ORBIT_OFF = 0,
 *        V4L2_EXT_VSC_ORBIT_ON
 *     };
 *
 *     struct v4l2_ext_vsc_orbit_size
 *     {
 *        unsigned short x;
 *        unsigned short y;
 *     };
 *
 *     struct v4l2_ext_vsc_orbit_region
 *     {
 *        struct v4l2_ext_vsc_orbit_size video_size;
 *        unsigned short video_scan;
 *        struct v4l2_ext_vsc_orbit_size osd_size;
 *        unsigned short osd_scan;
 *     };
 *     struct v4l2_ext_vsc_orbit_policy
 *     {
 *        enum v4l2_ext_vsc_orbit_on_off orbit_on_off;
 *        struct v4l2_ext_video_rect osd_resolution;
 *        struct v4l2_ext_video_rect panel_resolution;
 *        struct v4l2_ext_vsc_orbit_region region;
 *        struct v4l2_ext_vsc_orbit_size video_step;
 *        struct v4l2_ext_vsc_orbit_size osd_step;
 *     };
 *
 *
 * Return Value
 *   On success 0 is returned.
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the Generic Error Codes chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // example of set/get orbit policy value to VSC from nyx
 *     // set orbit policy
 *     struct v4l2_ext_vsc_orbit_policy orbit_policy;
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *
 *     if (orbit_policy != nullptr) {
 *
 *         orbit_policy.orbit_on_off = V4L2_EXT_VSC_ORBIT_ON;
 *         orbit_policy.osd_resolution = {0, 0, 1920, 1080};
 *         orbit_policy.panel_resolution = {0, 0, 3840, 2160};
 *         orbit_policy.region.video_size = {32, 16};
 *         orbit_policy.region.osd_size   = {20, 10};
 *         orbit_policy.region.video_scan = 1; //over scan
 *         orbit_policy.region.osd_scan   = 0; //just scan
 *
 *         orbit_policy.video_step = {0,0};
 *         orbit_policy.osd_step   = {0,0};
 *
 *         ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *         ext_controls.count = 1;
 *         ext_controls.controls = &ext_control;
 *         ext_controls.controls->id = V4L2_CID_EXT_VSC_ORBIT_POLICY;
 *
 *         // Set orbit policy
 *         ext_controls.controls->ptr = (void *)&orbit_policy;
 *         ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     }
 *
 *     // get orbit policy
 *     struct v4l2_ext_vsc_orbit_policy orbit_policy;
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *
 *
 *     ext_controls.ctrl_class    = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VSC_ORBIT_POLICY;
 *     ext_controls.controls->ptr = (void *)&orbit_policy;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *
 *     // example of registering call back function pointer of orbit-calculator.ko
 *     #include "export_vsc_orbit_adapter.h"
 *     #include "videodev2-ext.h"
 *
 *     struct v4l2_ext_vsc_orbit_policy orbit_policy; // policy from orbitcontroller through V4L2_CID_EXT_VSC_ORBIT_POLICY
 *
 *     struct v4l2_ext_video_rect source;                   // Resolution from source region
 *     struct v4l2_ext_video_rect input;                    // Resolution from crop region
 *     struct v4l2_ext_video_rect output;                   // Resolution from output region
 *
 *     struct v4l2_ext_vsc_orbit_position *calculated_orbitPosition  // calculated orbit position for orbit window/move
 *
 *     // driver store the orbit policy value when platform set the value with V4L2_CID_EXT_VSC_ORBIT_POLICY
 *     {
 *         switch (controls->id)
 *         {
 *             case V4L2_CID_EXT_VSC_ORBIT_POLICY :
 *                 orbit_policy.orbitOnOff = controls->ptr->orbitOnOff;
 *                 orbit_policy.osdResolution = controls->ptr->osdResolution;
 *                 orbit_policy.panelResolution = controls->ptr->panelResolution;
 *                 orbit_policy.region = controls->ptr->region;
 *                 orbit_policy.videoStep = controls->ptr->videoStep;
 *                 orbit_policy.osdStep = controls->ptr->osdStep;
 *         }
 *     }
 *
 *
 *     // driver should calculate the orbit position using orbit-calculator.ko
 *     {
 *
 *         if (vsc_getOrbitCallbackFp->pfnCalculateOrbitPosition != NULL)
 *         {
 *                 vsc_getOrbitCallbackFp->pfnCalculateOrbitPosition(
 *                 // Input Parameter
 *                 struct v4l2_ext_video_rect source,             // Resolution from source region
 *                 struct v4l2_ext_video_rect input,              // Resolution from crop region
 *                 struct v4l2_ext_video_rect output,             // Resolution from output region
 *                 struct v4l2_ext_vsc_orbit_policy orbit_policy, // policy from orbitcontroller through V4L2_CID_EXT_VSC_ORBIT_POLICY
 *                 // Output Parameter
 *                 struct v4l2_ext_vsc_orbit_position *calculated_orbit_position // calculated orbit position for orbit window/move
 *                 );
 *         }
 *     }
 *
 *
 * @endrst
 */
#define V4L2_CID_EXT_VSC_ORBIT_POLICY (V4L2_CID_USER_EXT_VSC_BASE + 42)

//
// VSC class subscription types
//

#define V4L2_EVENT_PRIVATE_EXT_VSC_BASE (V4L2_EVENT_PRIVATE_START + 0x2000)

#endif // _V4L2_EXT_VSC_H
