/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2023 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_HDMITX_H
#define _V4L2_EXT_HDMITX_H

#define V4L2_EXT_DEV_NO_HDMITX 15

#define V4L2_EXT_DEV_PATH_HDMITX "/dev/video15"

// User-class control Bases
#define V4L2_CID_USER_EXT_HDMITX_BASE (V4L2_CID_USER_BASE + 0xE000)

enum v4l2_ext_hdmitx_hdcp_auth_status {
    V4L2_EXT_HDMITX_HDCP_AUTH_STATUS_NONE_AUTH = 0,
    V4L2_EXT_HDMITX_HDCP_AUTH_STATUS_AUTH_DONE = 1,
    V4L2_EXT_HDMITX_HDCP_AUTH_STATUS_AUTH_IGNORE = 2,
};

enum v4l2_ext_hdmitx_hdcp_version {
  V4L2_EXT_HDMITX_HDCP_VERSION_14 = 0,
  V4L2_EXT_HDMITX_HDCP_VERSION_22,
  V4L2_EXT_HDMITX_HDCP_VERSION_RESERVED,
};

struct v4l2_ext_hdmitx_hdcp_topology_status {
    enum v4l2_ext_hdmitx_hdcp_version hdcp_version; // HDCP Verion. Information about whether the receiver connected to HDMITX is HDCP 1.4 or 2.2
    enum v4l2_ext_hdmitx_hdcp_auth_status auth_state; // Authenticated or not
    unsigned int topology_size; // Number of topologies. 
    unsigned short hdcp14_status; // Information Bstatus
    unsigned short hdcp22_status; // Information RXID
    unsigned char *topology; // KSV (5byte) X MAX Count (127)
};

/* =====================================================================================
LIST OF HDMITX APIs

#define V4L2_CID_EXT_HDMITX_HDCP_TOPOLOGY (V4L2_CID_USER_EXT_HDMITX_BASE + 50)

#define V4L2_CID_EXT_HDMITX_ (V4L2_CID_USER_EXT_HDMITX_BASE + 100)

===============================================================================================
*/

/**
 * @brief Set/Get HDMI TX HDCP Information
 *
 * @rst
 * Functional Requirements
 *   When the HDMITX module (platform) calls HDCP information via the V4L2 function,
 *   it sends the HDCP information of the currently connected source equipment to the OP-TEE.
 *
 * Responses to abnormal situations, including
 *   
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set HDMI TX timing output
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI TX timing output
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMITX_HDCP_TOPOLOGY
 *
 *     //
 *     // parameter
 *     //
 *
 *    struct v4l2_ext_hdmitx_hdcp_topology_status {
 *       enum v4l2_ext_hdmitx_hdcp_version hdcp_version; // HDCP Verion. Information about whether the receiver connected to HDMITX is HDCP 1.4 or 2.2
 *       enum v4l2_ext_hdmitx_hdcp_auth_status auth_state; // Authenticated or not
 *       unsigned int topology_size; // Number of topologies. 
 *       unsigned short hdcp14_status; // Information Bstatus
 *       unsigned short hdcp22_status; // Information RXID
 *       unsigned char *topology; // KSV (5byte) X MAX Count (127)
 *    };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set HDCP Repeater topology
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *
 *     struct v4l2_ext_hdmitx_hdcp_topology_status topology;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&topology, 0, sizeof(struct v4l2_ext_hdmitx_hdcp_topology_status));
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMITX_HDCP_TOPOLOGY;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmitx_hdcp_topology_status);
 *     ext_controls.controls->ptr = (void *)&topology;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 
 
 *     // Get HDCP Repeater topology
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     
 *     struct v4l2_ext_hdmitx_hdcp_topology_status topology;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&topology, 0, sizeof(struct v4l2_ext_hdmitx_hdcp_topology_status));
 *
 *     hdmi_avi.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMITX_HDCP_TOPOLOGY;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmitx_hdcp_topology_status);
 *     ext_controls.controls->ptr = (void *)&topology;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMITX_HDCP_TOPOLOGY (V4L2_CID_USER_EXT_HDMITX_BASE + 50)

#endif
