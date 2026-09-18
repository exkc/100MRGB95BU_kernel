/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018~2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_EARC_H
#define _V4L2_EXT_EARC_H

#include <linux/v4l2-controls.h>

#define V4L2_EXT_DEV_NO_EARC 13

#define V4L2_EXT_DEV_PATH_EARC "/dev/earc0"

#define V4L2_CID_USER_EXT_EARC_BASE (V4L2_CID_USER_BASE + 0xB000)

/*eARC*/
/* Number of eARC capability bytes*/
#define V4L2_EXT_EARC_CAPABILITY_BYTES 256

/*eARC ERX_LATENCY_REQ Type*/
#define V4L2_EXT_EARC_ERX_LATENCY_REQ_MINIMIZE                                 \
  0 // 0: requeset to minimize eARC RX latency
#define V4L2_EXT_EARC_ERX_LATENCY_REQ_NON_SYNC                                 \
  254 // 254: No synchronization required
#define V4L2_EXT_EARC_ERX_LATENCY_REQ_UNKNOWN                                  \
  255 // 255: unknown eARC TX latency

enum v4l2_ext_earc_output_port {
  V4L2_EXT_EARC_OUTPUT_PORT_NONE = 0,
  V4L2_EXT_EARC_OUTPUT_PORT_1,
  V4L2_EXT_EARC_OUTPUT_PORT_2,
  V4L2_EXT_EARC_OUTPUT_PORT_3,
  V4L2_EXT_EARC_OUTPUT_PORT_4,
  V4L2_EXT_EARC_OUTPUT_PORT_ALL,
};

enum v4l2_ext_earc_enable {
  V4L2_EXT_EARC_DISABLE = 0,
  V4L2_EXT_EARC_ENABLE = 1,
};

struct v4l2_ext_earc {
  enum v4l2_ext_earc_output_port port;
  enum v4l2_ext_earc_enable earc_enable_state;
};

enum v4l2_ext_earc_status {
  V4L2_EXT_EARC_IDLE1 = 0,
  V4L2_EXT_EARC_IDLE2 = 1,
  V4L2_EXT_EARC_DISC1 = 2,
  V4L2_EXT_EARC_DISC2 = 3,
  V4L2_EXT_EARC_EARC = 4,
};
struct v4l2_ext_earc_connection_info {
  enum v4l2_ext_earc_output_port port;
  enum v4l2_ext_earc_status status;
  unsigned char capability[V4L2_EXT_EARC_CAPABILITY_BYTES]; // Short Audio
                                                            // Descriptor Max
                                                            // 256 byte
  unsigned char erx_latency_req;                            // 0~255
  unsigned char erx_latency;                                // 0~255
};

/* eARC class control IDs */
/**
 * @brief set eARC detection enable/disable.
 *
 * @rst
 * Functional Requirements
 *   This control handles eARC Discovery and Disconnection enable/disable
 *   controls.
 *
 *   Ports may be specified when setting eARC enable/disable, or they may be set
 *   without specifying. If you do not specify a specific port, set it to
 *   :c:macro:`V4L2_EXT_EARC_OUTPUT_PORT_NONE`.
 *   If set to :c:macro:`V4L2_EXT_EARC_OUTPUT_PORT_NONE`, the eARC driver must
 * set the eARC
 *   enable/disable on the port supporting eARC.
 *   When calling a Get, if the Port is
 * :c:macro:`V4L2_EXT_EARC_OUTPUT_PORT_NONE`,
 *   the driver must deliver the eARC supporting port and eARC enable/disable
 *   states.
 *   When set to :c:macro:`V4L2_EXT_EARC_OUTPUT_PORT_NONE`, the driver must
 * deliver the set
 *   port's eARC enable/disable state.
 *
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   The driver should support eARC.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set Control EARC
 *     VIDIOC_G_EXT_CTRLS      // Get Control EARC
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_EARC
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_earc_output_port {
 *          V4L2_EXT_EARC_OUTPUT_PORT_NONE = 0,
 *          V4L2_EXT_EARC_OUTPUT_PORT_1,
 *          V4L2_EXT_EARC_OUTPUT_PORT_2,
 *          V4L2_EXT_EARC_OUTPUT_PORT_3,
 *          V4L2_EXT_EARC_OUTPUT_PORT_4,
 *          V4L2_EXT_EARC_OUTPUT_PORT_ALL,
 *     };
 *     enum v4l2_ext_earc_enable {
 *          V4L2_EXT_EARC_DISABLE = 0,
 *          V4L2_EXT_EARC_ENABLE  = 1,
 *     };
 *
 *     struct v4l2_ext_earc {
 *           enum v4l2_ext_earc_output_port port;
 *           enum v4l2_ext_earc_enable earc_enable_state;
 *     };
 *
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   This control id supports both :c:macro:`VIDIOC_G_EXT_CTRLS` and
 * :c:macro:`VIDIOC_S_EXT_CTRLS`.
 *
 * Example
 *    .. code-block:: cpp
 *
 *      // Set eARC enable/disable for port2
 *      v4l2_ext_controls ext_controls = {};
 *      v4l2_ext_control ext_control = {};
 *      struct v4l2_ext_earc earc = {};
 *
 *      earc.port = V4L2_EXT_EARC_OUTPUT_PORT_2;
 *      earc.earc_enable_state= V4L2_EXT_EARC_ENABLE;
 *      //earc.earc_enable_stat = V4L2_EXT_EARC_DISABLE;
 *
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_EARC;
 *      ext_controls.controls->size = sizeof(struct v4l2_ext_earc_enable );
 *      ext_controls.controls->ptr = (void *)&earc;
 *
 *      ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *
 *      // Set eARC enable/disable for port to support eARC
 *      v4l2_ext_controls ext_controls = {};
 *      v4l2_ext_control ext_control = {};
 *      struct v4l2_ext_earc earc = {};
 *
 *      earc.port = V4L2_EXT_EARC_OUTPUT_PORT_NONE;
 *      earc.earc_enable_state= V4L2_EXT_EARC_ENABLE;
 *     //earc.earc_enable_stat = V4L2_EXT_EARC_DISABLE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_EARC;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_earc_enable );
 *     ext_controls.controls->ptr = (void *)&earc;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *
 *     // Get eARC enable/disable status for Port2
 *     v4l2_ext_controls ext_controls = {};
 *     v4l2_ext_control ext_control = {};
 *     struct v4l2_ext_earc earc = {};
 *
 *     earc.port = V4L2_EXT_EARC_OUTPUT_PORT_2;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_EARC;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_earc_enable );
 *     ext_controls.controls->ptr = (void *)&earc;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *
 *     // Get eARC port and enable/disable status
 *     v4l2_ext_controls ext_controls = {};
 *     v4l2_ext_control ext_control = {};
 *     struct v4l2_ext_earc earc = {};
 *
 *     earc.port = V4L2_EXT_EARC_OUTPUT_PORT_NONE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_EARC;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_earc_enable );
 *     ext_controls.controls->ptr = (void *)&earc;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_EARC (V4L2_CID_USER_EXT_EARC_BASE + 0)

/**
 * @brief Get eARC state, capability and RX latency.
 *
 * @rst
 * Functional Requirements
 *   This function transmits the connection status, capability and
 *   erx_latentity of the current eARC every time it is called.
 *   When the port is called with the :c:macro:`V4L2_EXT_EARC_OUTPUT_PORT_NONE`
 * setting,
 *   the lowest port information connected to the current eARC is transmitted.
 *   When the port is set to :c:macro:`V4L2_EXT_EARC_OUTPUT_PORT_NONE`,
 *   the set port eARC information is transmitted.
 *   When the :c:macro:`V4L2_CID_EXT_EARC` is set to disable, everything is
 * delivered to zero.
 *   If the eARC is connected and the capability and erx_latency are not ready,
 *   the capability and erx_latency are delivered to zero.
 *   erx_latentity_req delivers the currently set value. If not set, it delivers
 * 0.
 *   Driver should be implemented so that there is no problem even if it is
 *   called every 50ms.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 70 msec.
 *
 * Constraints
 *   The driver should support eARC.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get Control EARC
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_EARC_CONNECTION_INFO
 *
 *     //
 *     // parameter
 *     //
 *     #define V4L2_EXT_EARC_ERX_LATENCY_REQ_MINIMIZE 0
 *     // 0: requeset to minimize eARC RX latency
 *     #define V4L2_EXT_EARC_ERX_LATENCY_REQ_NON_SYNC 254
 *     // 254: No synchronization required
 *     #define V4L2_EXT_EARC_ERX_LATENCY_REQ_UNKNOWN  255
 *     // 255: unknown eARC TX latency
 *
 *     enum v4l2_ext_earc_output_port {
 *           V4L2_EXT_EARC_OUTPUT_PORT_NONE = 0,
 *           V4L2_EXT_EARC_OUTPUT_PORT_1,
 *           V4L2_EXT_EARC_OUTPUT_PORT_2,
 *           V4L2_EXT_EARC_OUTPUT_PORT_3,
 *           V4L2_EXT_EARC_OUTPUT_PORT_4,
 *           V4L2_EXT_EARC_OUTPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_earc_status {
 *          V4L2_EXT_EARC_IDLE1 = 0,
 *          V4L2_EXT_EARC_IDLE2 = 1,
 *          V4L2_EXT_EARC_DISC1 = 2,
 *          V4L2_EXT_EARC_DISC2 = 3,
 *          V4L2_EXT_EARC_EARC  = 4,
 *     };
 *
 *     struct v4l2_ext_earc_connection_info {
 *            enum v4l2_ext_earc_output_port port;
 *            enum v4l2_ext_earc_status status;
 *            unsigned char capability[V4L2_EXT_EARC_CAPABILITY_BYTES];
 *     //Short Audio Descriptor Max 256 byte
 *            unsigned char erx_latency_req;     //0~255
 *            unsigned char erx_latency;     //0~255
 *     };
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   This control id supports only :c:macro:`VIDIOC_G_EXT_CTRLS`.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      // Get eARC connection information for port2
 *      v4l2_ext_controls ext_controls = {};
 *      v4l2_ext_control ext_control = {};
 *      v4l2_ext_earc_connection_info earc_connection = {};
 *
 *      earc_connection.port = V4L2_EXT_EARC_OUTPUT_PORT_2;
 *
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_EARC_CONNECTION_INFO;
 *      ext_controls.controls->size = sizeof(struct
 * v4l2_ext_earc_connection_info );
 *      ext_controls.controls->ptr = (void *)&earc_connection;
 *
 *      ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *
 *      // Get eARC connection information for eARC port which is connected and
 * supported.
 *      v4l2_ext_controls ext_controls = {};
 *      v4l2_ext_control ext_control = {};
 *      v4l2_ext_earc_connection_info earc_connection = {};
 *
 *      earc_connection.port = V4L2_EXT_EARC_OUTPUT_PORT_NONE;
 *
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_EARC_CONNECTION_INFO;
 *      ext_controls.controls->size = sizeof(struct
 * v4l2_ext_earc_connection_info );
 *      ext_controls.controls->ptr = (void *)&earc_connection;
 *
 *      ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_EARC_CONNECTION_INFO (V4L2_CID_USER_EXT_EARC_BASE + 1)

/**
 * @brief Set ERX_LATENCY_REQ.
 *
 * @rst
 * Functional Requirements
 *   This function sets erx_latentity_req in the connection of eARC.
 *   erx_latentity_req is :c:macro:`ERX_LATENCY_REQ` defined
 *   in HDMI Specification 2.1 document 9.5.3.5 Audio Latency Control.
 *   The eARC RX sets the output audio display by referring to
 * :c:macro:`ERX_LATENCY_REQ`.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 15 msec.
 *
 * Constraints
 *   The driver should support eARC.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set Control EARC
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_earc_output_port {
 *            V4L2_EXT_EARC_OUTPUT_PORT_NONE = 0,
 *            V4L2_EXT_EARC_OUTPUT_PORT_1,
 *            V4L2_EXT_EARC_OUTPUT_PORT_2,
 *            V4L2_EXT_EARC_OUTPUT_PORT_3,
 *            V4L2_EXT_EARC_OUTPUT_PORT_4,
 *            V4L2_EXT_EARC_OUTPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_earc_connection_info {
 *            enum v4l2_ext_earc_output_port port;
 *            enum v4l2_ext_earc_status status;
 *            unsigned char capability[V4L2_EXT_EARC_CAPABILITY_BYTES];
 *      //Short Audio Descriptor Max 256 byte
 *            unsigned char erx_latency_req;     //0~255
 *            unsigned char erx_latency;     //0~255
 *     };
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   This control id supports only :c:macro:`VIDIOC_S_EXT_CTRLS`.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set eARC ERX_LATENCY_REQ as minmize delay for port2
 *     v4l2_ext_controls ext_controls = {};
 *     v4l2_ext_control ext_control = {};
 *     v4l2_ext_earc_connection_info earc_connection = {};
 *
 *     earc_connection.port = V4L2_EXT_EARC_OUTPUT_PORT_2;
 *     earc_connection.erx_latency_req = V4L2_EXT_EARC_ERX_LATENCY_REQ_MINIMIZE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_earc_connection_info
 * );
 *     ext_controls.controls->ptr = (void *)&earc_connection;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *
 *     // Set eARC ERX_LATENCY_REQ as 100ms delay for eARC port which is
 * connected and supported.
 *     v4l2_ext_controls ext_controls = {};
 *     v4l2_ext_control ext_control = {};
 *     v4l2_ext_earc_connection_info earc_connection = {};
 *
 *     earc_connection.port = V4L2_EXT_EARC_OUTPUT_PORT_NONE;
 *     earc_connection.erx_latency_req = 100;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_earc_connection_info
 * );
 *     ext_controls.controls->ptr = (void *)&earc_connection;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_EARC_SET_ERX_LATENCY_REQ (V4L2_CID_USER_EXT_EARC_BASE + 2)

/**
 * @brief Reset eARC HDMI_HPD bit reset
 *
 * @rst
 * Functional Requirements
 *   This function is to reset HDMI_bit during eARC connection status(TX eARC).
 *   LG TV(eARC TX) does use eARC HDMI_HPD bit reset to notify eARC RX of EDID
 *   update instead of Physical HPD reset.
 *   If Physical HPD reset is used for eARC connected HDMI Port, the connection
 *   and disconnection of eARC is infinitely repeated.
 *   If eARC HDMI_HPD bit is used for eARC connected HDMI Port, it is possible
 * to
 *   notify eARC RX of EDID update without  the infinite repetition connection
 *   disconnection.
 *   When LG MW call :c:macro:`V4L2_CID_EXT_EARC_RESET_HDMI_HPD_BIT`, driver
 * should check
 *   whether eARC connection status is TX eARC, and if the connection status is
 *   TX eARC, driver should reset  HDMI_HPD bit (Clear/Set), otherwise driver
 *   should do nothing.
 *   For backward compatibility, if
 * :c:macro:`V4L2_CID_EXT_EARC_RESET_HDMI_HPD_BIT` is not
 *   implemented in driver yet, when LG MW call
 *   :c:macro:`V4L2_CID_EXT_EARC_RESET_HDMI_HPD_BIT`, driver should do nothing
 * without any
 *   problem.
 *   HDMI_HPD bit is defined in HDMI Specification 2.1 document 9.5.3.4
 * Heartbeat
 *   Sequence and Status Bits and 9.5.3.6 eARC RX Capabilities Data Structure.
 *   All eARC V4L2 Driver Interfaces  should support multi instance.
 *
 *   HPD should be controlled only on one thread. Controlling HPD on two or more
 * threads may cause collision problems.
 *   In order to improve compatibility issues, do not arbitrarily adjust the
 * length of the low duration of the HPD.
 *   If driver need to change HPD low duration, LG's review is required to
 * change it.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 800 msec.
 *
 * Constraints
 *   The driver should support eARC.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set Control EARC
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_EARC_RESET_HDMI_HPD_BIT
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_earc_output_port {
 *            V4L2_EXT_EARC_OUTPUT_PORT_NONE = 0,
 *            V4L2_EXT_EARC_OUTPUT_PORT_1,
 *            V4L2_EXT_EARC_OUTPUT_PORT_2,
 *            V4L2_EXT_EARC_OUTPUT_PORT_3,
 *            V4L2_EXT_EARC_OUTPUT_PORT_4,
 *            V4L2_EXT_EARC_OUTPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_earc_connection_info {
 *            enum v4l2_ext_earc_output_port port;
 *            enum v4l2_ext_earc_status status;
 *            unsigned char capability[V4L2_EXT_EARC_CAPABILITY_BYTES];
 *     //Short Audio Descriptor Max 256 byte
 *            unsigned char erx_latency_req;     //0~255
 *            unsigned char erx_latency;     //0~255
 *     };
 *
 * Return Value
 *   On success 0 is returned. On error -1 and the errno variable is set
 *   appropriately. The generic error codes are described at the
 *   :ref:`gen_errors` chapter.
 *
 * Control Type
 *   This control id supports only :c:macro:`VIDIOC_S_EXT_CTRLS`.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      // Set eARC ERX_LATENCY_REQ as minmize delay for port2
 *      v4l2_ext_controls ext_controls = {};
 *      v4l2_ext_control ext_control = {};
 *      v4l2_ext_earc_connection_info earc_connection = {};
 *
 *      earc_connection.port = V4L2_EXT_EARC_OUTPUT_PORT_NONE;
 *
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_EARC_RESET_HDMI_HPD_BIT;
 *      ext_controls.controls->size = sizeof(struct
 * v4l2_ext_earc_connection_info );
 *      ext_controls.controls->ptr = (void *)&earc_connection;
 *
 *      ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_EARC_RESET_HDMI_HPD_BIT (V4L2_CID_USER_EXT_EARC_BASE + 3)

#endif /* _V4_2_EXT_EARC_H */
