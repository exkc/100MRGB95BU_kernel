/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022-2025 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_GPSC_H
#define _V4L2_EXT_GPSC_H

#include <linux/v4l2-controls.h>

/* Common */
#define V4L2_EXT_DEV_NO_VDOGAV 27
#define V4L2_EXT_DEV_NO_GPSCALER 70
#define V4L2_EXT_DEV_PATH_VDOGAV "/dev/video27"
#define V4L2_EXT_DEV_PATH_GPSCALER "/dev/video70"

//
// User-class control Bases
//

#define V4L2_CID_USER_EXT_GPSCALER_BASE (V4L2_CID_USER_BASE + 0xA000)

/* Gpscaler class control IDs */
/**
 * @brief Set GPSCALER MAX FRAME SIZE
 *
 * @rst
 * Functional Requirements
 *   This interface can set MAX frame size per GP Scaler instance to manage
 * memory usage well. After setting MAX frame size, any frame size up to MAX
 * frame size can be controlled at any time by VIDIOC_S_FMT for each GP Scaler
 * instance.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the
 *   :ref:`Generic Error Codes <gen-errors>` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 100ms, if there are no
 * special reasons.
 *
 * Constraints
 *   There are no contraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_GPSCALER_MAX_FRAME_SIZE
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_control_
 *     {
 *         __u32 id;   //Identifies the control, set by the application.
 *         __s32 value;//max width(up to 1920):upper 16bit
 *                     //max height(up to 1080):lower 16bit
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control ctrl_arg;
 *
 *     ctrl_arg.id = V4L2_CID_EXT_GPSCALER_MAX_FRAME_SIZE;
 *     ctrl_arg.value = MAX_WIDTH << 16 | MAX_HEIGHT;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_GPSCALER_MAX_FRAME_SIZE                                   \
  (V4L2_CID_USER_EXT_GPSCALER_BASE + 1)

/**
 * @brief Get GPSCALER INPUT FRAME SIZE
 *
 * @rst
 * Functional Requirements
 *   This interface can get input frame size per GP Scaler instance to support
 * adaptive streaming.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the
 *   :ref:`Generic Error Codes <gen-errors>` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 100ms, if there are no
 * special reasons.
 *
 * Constraints
 *   There are no contraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_GPSCALER_INPUT_FRAME_SIZE
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_control_
 *     {
 *         __u32 id;   //Identifies the control, set by the application.
 *         __s32 value;//Input width:upper 16bit/Input height:lower 16bit
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control ctrl_arg;
 *     int in_width, in_height;
 *
 *     ctrl_arg.id = V4L2_CID_EXT_GPSCALER_INPUT_FRAME_SIZE;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 *
 *     in_width = (ctrl_arg.value >> 16) & 0xffff;
 *     in_height = ctrl_arg.value & 0xffff;
 *
 * @endrst
 */
#define V4L2_CID_EXT_GPSCALER_INPUT_FRAME_SIZE                                 \
  (V4L2_CID_USER_EXT_GPSCALER_BASE + 2)

/**
 * @brief Set GPSCALER ACTIVE REGION DETECTION MODE
 *
 * @rst
 * Functional Requirements
 *   This interface can set enable/disable active region detection function.
 * This ioctl should be called after VIDIOC_S_INPUT when set active region
 * detection mode on.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the
 *   :ref:`Generic Error Codes <gen-errors>` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 100ms, if there are no
 * special reasons.
 *
 * Constraints
 *   There are no contraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_MODE
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_control_
 *     {
 *         __u32 id;   //Identifies the control, set by the application.
 *         __s32 value;//1:enable/0:disable
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control ctrl_arg;
 *
 *     //Set active region detection mode on
 *     ctrl_arg.id = V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_MODE;
 *     ctrl_arg.value = 1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 *     //Set active region detection mode off
 *     ctrl_arg.id = V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_MODE;
 *     ctrl_arg.value = 0;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_MODE                     \
  (V4L2_CID_USER_EXT_GPSCALER_BASE + 3)

/**
 * @brief Get GPSCALER ACTIVE REGION DETECTION INFO HORIZONTAL
 *
 * @rst
 * Functional Requirements
 *   This interface can get active region detection horizontal result. This
 * ioctl should be called after active region detection mode on.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the
 *   :ref:`Generic Error Codes <gen-errors>` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 100ms, if there are no
 * special reasons.
 *
 * Constraints
 *   There are no contraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_H
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_control_
 *     {
 *         __u32 id;   //Identifies the control, set by the application.
 *         __s32 value;//x result:upper 16bit/width result:lower 16bit
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control ctrl_arg;
 *     int ard_x, ard_width;
 *
 *     //Get active region detection x and width result
 *     ctrl_arg.id = V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_H;
 *     ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 *
 *     ard_x = (ctrl_arg.value << 16) & 0xffff;
 *     ard_width = ctrl_arg.value & 0xffff;
 *
 * @endrst
 */
#define V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_H                   \
  (V4L2_CID_USER_EXT_GPSCALER_BASE + 4)

/**
 * @brief Get GPSCALER ACTIVE REGION DETECTION INFO VERTICAL
 *
 * @rst
 * Functional Requirements
 *   This interface can get active region detection vertical result. This ioctl
 * should be called after active region detection mode on.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the
 *   :ref:`Generic Error Codes <gen-errors>` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 100ms, if there are no
 * special reasons.
 *
 * Constraints
 *   There are no contraints.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_V
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_control_
 *     {
 *         __u32 id;   //Identifies the control, set by the application.
 *         __s32 value;//y result:upper 16bit/height result:lower 16bit
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     v4l2_control ctrl_arg;
 *     int ard_y, ard_height;
 *
 *     //Get active region detection y and height result
 *     ctrl_arg.id = V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_V;
 *     ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 *
 *     ard_y = (ctrl_arg.value << 16) & 0xffff;
 *     ard_height = ctrl_arg.value & 0xffff;
 *
 * @endrst
 */
#define V4L2_CID_EXT_GPSCALER_ACTIVE_REGION_DETECTION_INFO_V                   \
  (V4L2_CID_USER_EXT_GPSCALER_BASE + 5)

/**
 * @brief Set and get GPSCALER SOURCE ATTRIBUTE
 *
 * @rst
 * Functional Requirements
 *   This interface can set and get attribute of gpscaler sourcea. set ioctl
 * should be called before stream on.
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the
 *   :ref:`Generic Error Codes <gen-errors>` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 100ms, if there are no
 * special reasons.
 *
 * Constraints
 *   There are no contraints.
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
 *     V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_gpscaler_source_attribute_type {
 *         V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_NONE = 0,   // Default
 *         V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_INTERLACE,
 *         V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_MJPEG,
 *         V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_MAX,
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *   Application can get data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     //Set source attribute
 *     v4l2_control ctrl_s;
 *
 *     ctrl_s.id = V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE;
 *     ctrl_s.value = V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_INTERLACE;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &ctrl_s);
 *
 *     //Get source attribute
 *     v4l2_control ctrl_g;
 *     enum v4l2_ext_gpscaler_source_attribute_type attr;
 *
 *     ctrl_g.id = V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &ctrl_g);
 *
 *     attr = ctrl_g.value;
 *
 * @endrst
 */
#define V4L2_CID_EXT_GPSCALER_SOURCE_ATTRIBUTE                                 \
  (V4L2_CID_USER_EXT_GPSCALER_BASE + 6)

enum v4l2_ext_gpscaler_source_attribute_type {
  V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_NONE = 0, // Default
  V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_INTERLACE,
  V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_MJPEG,
  V4L2_EXT_GPSCALER_SOURCE_ATTRIBUTE_TYPE_MAX,
};

/**
 * @brief Set and get GPSCALER EXTERNAL INPUT
 *
 * @rst
 * Functional Requirements
 *   This interface can set and get the mapping information for the scaler port
 * and external input port. set ioctl should be called before stream on.
 * To distinguish it from media GAV, external input gav instance does not call
 * VIDIOC_S(G)_INPUT.
 * And media instance does not call this API(V4L2_CID_EXT_GPSCALER_EXTERNAL_INPUT).
 *
 * Responses to abnormal situations, including
 *   If abnormal data is set, the driver should return an error.
 *   The generic error codes are described at the
 *   :ref:`Generic Error Codes <gen-errors>` chapter.
 *
 * Performance Requirements
 *   The response time of this function should be within 100ms, if there are no
 * special reasons.
 *
 * Constraints
 *   There are no contraints.
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
 *     V4L2_CID_EXT_GPSCALER_EXTERNAL_INPUT
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_gpscaler_external_input {
 *       int externalInputPort;   // ex) HDMI Port Number: 1, 2, 3, ...
 *       int scalerPort;          // 0: Main, 1: Sub0, 2: Sub1, 3: Sub2...
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
 *     // Set External Input Mapping Info
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_gpscaler_external_input gpscExtInput{0};
 *
 *     // Mapping HDMI1 to Main
 *     gpscExtInput.externalInputPort = 1;
 *     gpscExtInput.scalerPort        = 0;
 *
 *     // Mapping HDMI3 to Sub0
 *     gpscExtInput.externalInputPort = 3;
 *     gpscExtInput.scalerPort        = 1;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_GPSCALER_EXTERNAL_INPUT;
 *     ext_controls.controls->ptr = (void *)&gpscExtInput;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *
 *     // Get External Input Mapping Info
 *     struct v4l2_ext_controls ext_controls{0};
 *     struct v4l2_ext_control ext_control{0};
 *     struct v4l2_ext_gpscaler_external_input gpscExtInput{0};
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_GPSCALER_EXTERNAL_INPUT;
 *     ext_controls.controls->ptr = (void *)&gpscExtInput;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_GPSCALER_EXTERNAL_INPUT                                   \
  (V4L2_CID_USER_EXT_GPSCALER_BASE + 7)

struct v4l2_ext_gpscaler_external_input {
  int externalInputPort; // ex) HDMI Port Number: 1, 2, 3, ...
  int scalerPort;        // 0: Main, 1: Sub0, 2: Sub1, 3: Sub2...
};

#endif // _V4L2_EXT_GPSC_H
