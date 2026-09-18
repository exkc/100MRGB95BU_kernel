/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2025 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_TTV_H
#define _V4L2_EXT_TTV_H

#include <linux/v4l2-controls.h>

#define V4L2_EXT_DEV_NO_TTV 71
#define V4L2_CID_USER_EXT_TTV_BASE (V4L2_CID_USER_BASE + 0xA500)
#define V4L2_EXT_DEV_PATH_TTV "/dev/video71"

/* Texture to Video class control IDs */

/**
 * @brief Notify done processing to driver.
 *
 * @rst
 * Functional Requirements
 *   It is a command used in TTV to process the DMA buffer at the user level on
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
 *   None
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
 *     V4L2_CID_EXT_TTV_DONE_USER_PROCESSING
 *
 *     //
 *     // parameter
 *     //
 *     plane_index //This index means ttv DMA buffer index.
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
 *       control.id = V4L2_CID_EXT_TTV_DONE_USER_PROCESSING;
 *       control.value = plane_index;
 *       ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_TTV_DONE_USER_PROCESSING (V4L2_CID_USER_EXT_TTV_BASE + 0)

/**
 * @brief Set TTV output region
 *
 * @rst
 * It can set TTV output region
 *
 * Commands & Parameters
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
 *     V4L2_CID_EXT_TTV_OUT_REGION
 *
 *    //
 *    // parameter
 *    //
 *    struct v4l2_ext_video_rect;
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using v4l2_ext_controls and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      struct v4l2_ext_controls ext_controls = {0};
 *      struct v4l2_ext_control ext_control = {0};
 *      struct v4l2_ext_video_rect outRegion = {0, 0, 3840, 2160};
 *
 *      ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_TTV_OUT_REGION;
 *      ext_controls.controls->size = sizeof(v4l2_ext_video_rect);
 *      ext_controls.controls->ptr = (void *)(&outRegion);
 *
 *      ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * See also
 *   - :cpp:any:`v4l2_ext_video_rect`
 *
 * @endrst
 */
#define V4L2_CID_EXT_TTV_OUT_REGION (V4L2_CID_USER_EXT_TTV_BASE + 1)

#endif // _V4L2_EXT_TTV_H