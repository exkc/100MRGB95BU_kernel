/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018~2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_VBI_H
#define _V4L2_EXT_VBI_H

#include <linux/v4l2-controls.h>

#define V4L2_EXT_DEV_NO_VBI 1

#define V4L2_EXT_DEV_PATH_VBI "/dev/vbi1"

#define V4L2_CID_USER_EXT_VBI_BASE (V4L2_CID_USER_BASE + 0xC000)

/* VBI */
/* CGMS copy protection enum */
enum v4l2_ext_vbi_cgms {
  V4L2_EXT_VBI_CGMS_PERMIT = 0,
  V4L2_EXT_VBI_CGMS_ONCE,
  V4L2_EXT_VBI_CGMS_RESERVED,
  V4L2_EXT_VBI_CGMS_NO_PERMIT,
};

/* APS copy protection enum */
enum v4l2_ext_vbi_aps {
  V4L2_EXT_VBI_APS_OFF = 0,
  V4L2_EXT_VBI_APS_ON_BURST_OFF,
  V4L2_EXT_VBI_APS_ON_BURST_2,
  V4L2_EXT_VBI_APS_ON_BURST_4,
};

/* MACROVISION copy protection enum */
enum v4l2_ext_vbi_macrovision {
  V4L2_EXT_VBI_MACROVISION_PSP_OFF = 0,
  V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_OFF,
  V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_2,
  V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_4,
};

struct v4l2_ext_vbi_copy_protection {
  enum v4l2_ext_vbi_cgms cgms_cp_info;
  enum v4l2_ext_vbi_aps aps_cp_info;
  enum v4l2_ext_vbi_macrovision macrovision_cp_info;
};

//
// VBI class control IDs
//

/**
 * @brief Get VBI Copy Protection info
 *
 * @rst
 * Functional Requirements
 *   This function returns the copy protection informaion of current analog
 * video
 *   signal.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
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
 *     VIDIOC_G_EXT_CTRLS      // Get VBI Copy Protection info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBI_COPY_PROTECTION_INFO
 *
 *     //
 *     // parameter
 *     //
 *
 *     // CGMS copy protection enum
 *     enum v4l2_ext_vbi_cgms
 *     {
 *         V4L2_EXT_VBI_CGMS_PERMIT = 0,
 *         V4L2_EXT_VBI_CGMS_ONCE,
 *         V4L2_EXT_VBI_CGMS_RESERVED,
 *         V4L2_EXT_VBI_CGMS_NO_PERMIT,
 *     };
 *
 *     // APS copy protection enum
 *     enum v4l2_ext_vbi_aps
 *     {
 *         V4L2_EXT_VBI_APS_OFF = 0,
 *         V4L2_EXT_VBI_APS_ON_BURST_OFF,
 *         V4L2_EXT_VBI_APS_ON_BURST_2,
 *         V4L2_EXT_VBI_APS_ON_BURST_4,
 *     };
 *
 *     // MACROVISION copy protection enum
 *     enum v4l2_ext_vbi_macrovision
 *     {
 *         V4L2_EXT_VBI_MACROVISION_PSP_OFF = 0,
 *         V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_OFF,
 *         V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_2,
 *         V4L2_EXT_VBI_MACROVISION_PSP_ON_BURST_4,
 *     };
 *
 *
 *     struct v4l2_ext_vbi_copy_protection
 *     {
 *         enum v4l2_ext_vbi_cgms        cgms_cp_info;
 *         enum v4l2_ext_vbi_aps         aps_cp_info;
 *         enum v4l2_ext_vbi_macrovision macrovision_cp_info;
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
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get VBI Copy Protection info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbi_copy_protection copy_protention_info;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&copy_protention_info, 0, sizeof(struct
 * v4l2_ext_vbi_copy_protection));
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBI_COPY_PROTECTION_INFO;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_vbi_copy_protection);
 *     ext_controls.controls->ptr = (void *)&copy_protention_info;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBI_COPY_PROTECTION_INFO (V4L2_CID_USER_EXT_VBI_BASE + 0)

/**
 * @brief Flush VBI data
 *
 * @rst
 * Functional Requirements
 *   This function erases all VBI data which remain inside the VBI Buffer. The
 *   VBI-Buffer includes the driver-side-VBI-Buffer. Driver empty buffer for
 * given
 *   V4L2 VBI Services by control.value. For example, if control.value is
 *   V4L2_SLICED_VBI_625, erase Teletext and WSS data. If control.value is
 *   V4L2_SLICED_CAPTION_525, erase Closed caption data.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
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
 *     VIDIOC_S_CTRL      // Flush VBI data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBI_FLUSH
 *
 *     //
 *     // control value
 *     //
 *
 *     // Sliced VBI services from V4L2 standard
 *     // Please see
 * https://linuxtv.org/downloads/v4l-dvb-apis/uapi/v4l/dev-sliced-vbi.html#sliced-vbi-services
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *   This control id supports VIDIOC_S_CTRL only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Flush Closed Caption vbi data
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBI_FLUSH;
 *     control.value = V4L2_SLICED_CAPTION_525;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *     // Flush PAL TTX and WSS vbi data
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBI_FLUSH;
 *     control.value = V4L2_SLICED_VBI_625;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBI_FLUSH (V4L2_CID_USER_EXT_VBI_BASE + 1)

/**
 * @brief Enable VBI Slicer
 *
 * @rst
 * Functional Requirements
 *   This function enables VBI slicer for current analog video signal.
 *   VBI slicer is a function that extracts data, such as caption/teletext,
 * included in analog videos.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
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
 *     VIDIOC_S_CTRL      // Enable VBI Slicer
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBI_SLICER_ENABLE
 *
 *     //
 *     // control value
 *     //
 *
 *     // Sliced VBI services from V4L2 standard
 *     // Please see
 * https://linuxtv.org/downloads/v4l-dvb-apis/uapi/v4l/dev-sliced-vbi.html#sliced-vbi-services
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *   This control id supports VIDIOC_S_CTRL only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Enable VBI Slicer
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBI_SLICER_ENABLE;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBI_SLICER_ENABLE (V4L2_CID_USER_EXT_VBI_BASE + 2)

/**
 * @brief Disable VBI Slicer
 *
 * @rst
 * Functional Requirements
 *   This function disables VBI slicer for current analog video signal.
 *   VBI slicer is a function that extracts data, such as caption/teletext,
 * included in analog videos.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
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
 *     VIDIOC_S_CTRL      // Disable VBI Slicer
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBI_SLICER_DISABLE
 *
 *     //
 *     // control value
 *     //
 *
 *     // Sliced VBI services from V4L2 standard
 *     // Please see
 * https://linuxtv.org/downloads/v4l-dvb-apis/uapi/v4l/dev-sliced-vbi.html#sliced-vbi-services
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *   This control id supports VIDIOC_S_CTRL only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Disable VBI Slicer
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBI_SLICER_DISABLE;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBI_SLICER_DISABLE (V4L2_CID_USER_EXT_VBI_BASE + 3)

#endif /* _V4L2_EXT_VBI_H */