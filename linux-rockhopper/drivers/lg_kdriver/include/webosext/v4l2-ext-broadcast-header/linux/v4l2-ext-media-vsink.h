#ifndef _MEDIA_VSINK_EXT_H
#define _MEDIA_VSINK_EXT_H

#ifndef __LINUX_V4L2_CONTROLS_H
#include <linux/v4l2-controls.h>
#endif

#ifndef _UAPI__LINUX_VIDEODEV2_H
#include <linux/videodev2.h>
#endif

#ifndef V4L2_EXT_DEV_PATH_VSINK
#define V4L2_EXT_DEV_PATH_VSINK "/dev/video22"
#endif

/* Media video sink class control IDs */
#define V4L2_CID_USER_EXT_MEDIA_VSINK_BASE (V4L2_CID_USER_BASE + 0x8800)
#define V4L2_CID_EXT_MEDIA_VSINK_BASE (V4L2_CID_USER_EXT_MEDIA_VSINK_BASE + 0x0)

/* Media video sink class subscription types */
#define V4L2_EVENT_PRIVATE_EXT_MEDIA_VSINK_BASE (V4L2_EVENT_PRIVATE_START + 0x8800)


/**
 * @rst
 * Functional Requirements
 *   V4L2 Subscription Type for Media video sink
 * @endrst
 */
#define V4L2_EVENT_PRIVATE_EXT_MEDIA_VSINK_EVENT (V4L2_EVENT_PRIVATE_EXT_MEDIA_VSINK_BASE + 1)

/* Media video sink class subscription event IDs */
#define V4L2_SUB_EXT_MEDIA_VSINK_BASE (0x8800)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_CLOCK_SOURCE_TYPE */

/**
 * @rst
 * Functional Requirements
 *   It is a control id for setting clock source.
 *   Unless the clock source value source is specified, SYSTEM_CLOCK is default value.
 *   When the clock source is ATSC3_WALL_CLOCK, vsink should use ATSC3.0 wall clock for rendering synchronization. See ATSC3.0 specification document in references section for details.
 *   When the value is JP4K_NETWORK_TIME_PROTOCOL, it uses NTP timestamp of IETF RFC 5905 which is mentioned in Japan UHD Specification. Please refer Japan UHD documentation of references section.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_CLOCK_SOURCE_TYPE
 *
 *     //
 *     // control value
 *     //
 *     SYSTEM_CLOCK(default value), ATSC3_WALL_CLOCK, JP4K_NETWORK_TIME_PROTOCOL
 *     (See enum v4l2_ext_media_clock_source_type)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_CLOCK_SOURCE_TYPE;
 *      ctrl_arg.value = ATSC3_WALL_CLOCK;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_CLOCK_SOURCE_TYPE (V4L2_CID_EXT_MEDIA_VSINK_BASE + 3)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_CONSTANT_OUTPUT_DELAY */

/**
 * @rst
 * Functional Requirements
 *   This is a control id for controlling queue size of video sink.
 *   Video sink try to maintain the number of decoded video frame with the value set by this control id.
 *   So it can operates in adaptive free run mode.
 *   Note that Adaptive freerun means the behavior that maintain display queue count for preventing video under run
 *   So it can provide stable QoS.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_CONSTANT_OUTPUT_DELAY
 *
 *     //
 *     // control value
 *     //
 *
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_CONSTANT_OUTPUT_DELAY;
 *      ctrl_arg.value = 7;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_CONSTANT_OUTPUT_DELAY (V4L2_CID_EXT_MEDIA_VSINK_BASE + 4)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_CURRENT_PTS */

/**
 * @rst
 * Functional Requirements
 *   This is a control id for getting the pts of video frame which is rendering now.
 *   Note that this CID is for debug only.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_CURRENT_PTS
 *
 *     //
 *     // control value
 *     //
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *          struct v4l2_ext_controls ext_ctrls;
 *          struct v4l2_ext_control ext_ctrl;
 *          memset(&ext_ctrls, 0, sizeof(ext_ctrls));
 *          memset(&ext_ctrl, 0, sizeof(ext_ctrl));
 *
 *          ext_ctrls.count    = 1;
 *          ext_ctrls.controls = &ext_ctrl;
 *
 *          ext_ctrl.id        = V4L2_CID_EXT_MEDIA_CURRENT_PTS;
 *          ext_ctrl.size      = sizeof(struct v4l2_ext_control);
 *
 *          rc                 = ioctl(vsink_fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 *          ...
 *
 *          return ext_ctrl.value64;
 *
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_CURRENT_PTS (V4L2_CID_EXT_MEDIA_VSINK_BASE + 5)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_FRAME_DROP_THRESHOLD */

/**
 * @rst
 * Functional Requirements
 *   This is a control id for adjust the threshold of buffer drop in video sink buffer.
 *   When the number of decoded frame is reached over the threshold value, video sink should start dropping frame.
 *   video sink should stop dropping frame when post decoded queue contains only one frame.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_FRAME_DROP_THRESHOLD
 *
 *     //
 *     // control value
 *     //
 *     -
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_FRAME_DROP_THRESHOLD;
 *      ctrl_arg.value = 8;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *      }
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_FRAME_DROP_THRESHOLD (V4L2_CID_EXT_MEDIA_VSINK_BASE + 6)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_RENDER_BUFFER_LENGTH */

/**
 * @rst
 * Functional Requirements
 *   This is a control id for checking the number of frame which is queued in video sink
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_RENDER_BUFFER_LENGTH
 *
 *     //
 *     // control value
 *     //
 *     -
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_RENDER_BUFFER_LENGTH;
 *
 *      ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 *      }
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_RENDER_BUFFER_LENGTH (V4L2_CID_EXT_MEDIA_VSINK_BASE + 7)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_DISPLAY_PREROLL */

/**
 * @rst
 * Functional Requirements
 *   This is a control id that controls whether display frame which is delivered as preroll frame.
 *   When the value of this control id is false, video frame which is delivered as preroll should not be delivered to VDO.
 *   In this case, When you are in the time after seek and before play, you can observe the video frame before seek.
 *   When the value of this control id is true, vvideo frame which is devliered as preroll should be shown.
 *   Note that the default value of this CID is on.
 *   Therefore, the video sink should deliver preroll video frame to VDO so that it can be displayed.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_DISPLAY_PREROLL
 *
 *     //
 *     // control value
 *     //
 *     0 (off)
 *     1 (on)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_DISPLAY_PREROLL;
 *      ctrl_arg.value = 0;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_DISPLAY_PREROLL (V4L2_CID_EXT_MEDIA_VSINK_BASE + 9)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_DROPPED_FRAMES */

/**
 * @rst
 * Functional Requirements
 *   This is a control id for checking the number of dropped frame.
 *   Please note that the number of dropped frame is updated every second.
 *   The return value of this CID must be initialized to 0 when the following conditions are met.
 *   - When the pipeline is created
 *   - When the flush occurs
 *   - When the user read the value by using this CID
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_DROPPED_FRAMES
 *
 *     //
 *     // control value
 *     //
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_DROPPED_FRAMES;
 *
 *      ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_DROPPED_FRAMES (V4L2_CID_EXT_MEDIA_VSINK_BASE + 10)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_VIDEO_DISPLAY_DELAY_OFFSET */

/**
 * @rst
 * Functional Requirements
 *   This is a control id for controlling offset value of A/V Sync.
 *   Please note that you should only pass positive value.
 *   Video sink should delay the delivery of video frame with given amount of value set by this control id.
 *   Note that the unit of this CID's value is ms.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_VIDEO_DISPLAY_DELAY_OFFSET
 *
 *     //
 *     // control value
 *     //
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_VIDEO_DISPLAY_DELAY_OFFSET;
 *      ctrl_arg.id = 100;
 *
 *      ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VIDEO_DISPLAY_DELAY_OFFSET (V4L2_CID_EXT_MEDIA_VSINK_BASE + 11)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_LOW_DELAY */

/**
 * @rst
 * Functional Requirements
 *   This is a control id which enables low delay mode.
 *   When the low delay mode is on, video sink delivers the buffer without rendering synchronization.
 *   This CID is used for gaming mode.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_LOW_DELAY
 *
 *     //
 *     // control value
 *     //
 *     0 (off)
 *     1 (on)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_LOW_DELAY;
 *
 *      ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_LOW_DELAY (V4L2_CID_EXT_MEDIA_VSINK_BASE + 12)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_NON_FLUSHABLE_DISPLAYED_FRAMES */

/**
 * @rst
 * Functional Requirements
 *   This is a control id for checking the number of non flushable displayed frames.
 *   This cid is for youtube requirements which is related to total video frame count of W3C media-playback-quality standard.
 *   The accumulated value should be the number of displayed frames between the time when the pipeline is created and the time when the pipeline is destructed regardless of flush.
 *   In other words, the value of this CID should be accumulated between open() ~ close().
 *   Note that the value of this CID should be initialized to 0 when the following conditions are met.
 *   - When the pipeline is created (In persepctive of driver, it is open())
 *   - When the value of this CID is read by application (In other words, VIDIOC_G_CTRL is called)
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_NON_FLUSHABLE_DISPLAYED_FRAMES
 *
 *     //
 *     // control value
 *     //
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_NON_FLUSHABLE_DISPLAYED_FRAMES;
 *
 *      ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_NON_FLUSHABLE_DISPLAYED_FRAMES (V4L2_CID_EXT_MEDIA_VSINK_BASE + 13)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_NON_FLUSHABLE_DROPPED_FRAMES */

/**
 * @rst
 * Functional Requirements
 *   It is a control id that get the number of non flushable dropped frames
 *   Please note that this cid is not same with V4L2_CID_EXT_MEDIA_DROPPED_FRAMES.
 *   This cid is for youtube requirements which is related to dropped video frame count of W3C media-playback-quality standard.
 *   The accumulated value should be the number of dropped frames between the time when the pipeline is created and the time when the pipeline is destructed regradless of flush.
 *   In other words, the value of this CID should be accumulated between open() ~ close().
 *   Note that the value of this CID should be initialized to 0 when the following conditions are met.
 *   - When the pipeline is created (In persepctive of driver, it is open())
 *   - When the value of this CID is read by application (In other words, VIDIOC_G_CTRL is called)
 *   You should be aware that the value of this CID is not initialized to 0 even though the flush occurs.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_NON_FLUSHABLE_DROPPED_FRAMES
 *
 *     //
 *     // control value
 *     //
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_NON_FLUSHABLE_DROPPED_FRAMES;
 *
 *      ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_NON_FLUSHABLE_DROPPED_FRAMES (V4L2_CID_EXT_MEDIA_VSINK_BASE + 14)

/* Media video sink class class control values V4L2_CID_EXT_MEDIA_INFO */

/**
 * @rst
 * Functional Requirements
 *   This is a control id for checking the information of media.
 *   To configure H/W backend and display window, video decoded information is required for the first initial preroll frame from video sink.
 *   Thus, video sink shall post 'media-info' structure which includes video decoded information.
 *   After that, LG player set the window and unmute video and audio in order to show video and audio appropriately.
 *   Also, the 'media-info' shall be posted whenever any values are changed such as resolution is changed.
 *   Driver will post V4L2_SUB_EXT_MEDIA_INFO_READY V4L2 event when application can get valid media info data by this cid.
 *   If application read the data by this CID before the event triggered, it does not gurantee the validness of data returned.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_INFO
 *
 *     //
 *     // control value
 *     //
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *          struct v4l2_ext_media_info media_info;
 *          struct v4l2_ext_controls ext_ctrls;
 *          struct v4l2_ext_control ext_ctrl;
 *          memset(&media_info, 0, sizeof(struct v4l2_ext_media_info));
 *          memset(&ext_ctrls, 0, sizeof(ext_ctrls));
 *          memset(&ext_ctrl, 0, sizeof(ext_ctrl));
 *
 *          ...
 *
 *          ext_ctrls.count    = 1;
 *          ext_ctrls.controls = &ext_ctrl;
 *
 *          ext_ctrl.id        = V4L2_CID_EXT_MEDIA_INFO;
 *          ext_ctrl.size      = sizeof(struct v4l2_ext_media_info);
 *          ext_ctrl.ptr       = &media_info;
 *
 *          rc                 = ioctl(vsink_fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_INFO (V4L2_CID_EXT_MEDIA_VSINK_BASE + 15)

/* Media video sink class class control values V4L2_CID_EXT_MEDIA_VSINK_SVP */

/**
 * @rst
 * Functional Requirements
 *   It is a control id for using Secure Video Path(SVP) for video sink.
 *   You can also check whether the video sink is currently using SVP by getting a value from this control id.
 *   When the value of this CID is true, the buffer management of vide sink should be handled in secure region.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_VSINK_SVP
 *
 *     //
 *     // control value
 *     //
 *     0 (Disable)
 *     1 (Enable)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_VSINK_SVP;
 *      ctrl_arg.value = 0;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VSINK_SVP (V4L2_CID_EXT_MEDIA_VSINK_BASE + 16)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_VSINK_RES_INFO */

/**
 * @rst
 * Functional Requirements
 *   After acquisition of H/W resource is completed, Allocated resource information must be set.
 *   This is a control id used to set the allocated resource information.
 *   Also, you can check the allocated resource information by getting a value from this control id.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS       // Get
 *     VIDIOC_S_EXT_CTRLS       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_VSINK_RES_INFO
 *
 *     //
 *     // control value
 *     //
 *     -
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_EXT_CTRLS`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int LGE_API_SetResInfo()
 *      {
 *          int rc;
 *
 *          struct v4l2_ext_media_sink_resource_info res_info;
 *          struct v4l2_ext_controls ext_ctrls;
 *          struct v4l2_ext_control ext_ctrl;
 *          memset(&res_info, 0, sizeof(res_info));
 *          memset(&ext_ctrls, 0, sizeof(ext_ctrls));
 *          memset(&ext_ctrl, 0, sizeof(ext_ctrl));
 *
 *          ...
 *
 *          ext_ctrls.count    = 1;
 *          ext_ctrls.controls = &ext_ctrl;
 *
 *          ext_ctrl.id        = V4L2_CID_EXT_MEDIA_VSINK_RES_INFO;
 *          ext_ctrl.size      = sizeof(v4l2_ext_media_sink_resource_info);
 *          ext_ctrl.ptr       = &res_info;
 *
 *          rc                 = ioctl(vsink_fd, VIDIOC_S_EXT_CTRLS, &ext_ctrls_arg);
 *
 *          return rc;
 *      }
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VSINK_RES_INFO (V4L2_CID_EXT_MEDIA_VSINK_BASE + 17)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_VSINK_APP_TYPE */

/**
 * @rst
 * Functional Requirements
 *   Set the app type. Also, you can check the app type currently set by using this control id.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_VSINK_APP_TYPE
 *
 *     //
 *     // control value
 *     //
 *     (See enum v4l2_ext_media_vsink_app_type)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_VSINK_APP_TYPE;
 *      ctrl_arg.value = SEAMLESS;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VSINK_APP_TYPE (V4L2_CID_EXT_MEDIA_VSINK_BASE + 18)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION */

/**
 * @rst
 * Functional Requirements
 *   It is a control id for allowing user to indicate the current stream status as a dolby vision.
 *   If the value of this control id is true, it means that the current stream is a dolby vision stream.
 *   So Video sink must process the buffer data so that it can be properly rendered based on Dolby Vision specification.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION
 *
 *     //
 *     // control value
 *     //
 *     0 (false, Current stream is not a dolby vision stream)
 *     1 (true Current stream is a dolby vision stream)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_MEDIA_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION;
 *      ctrl_arg.value = 0;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION (V4L2_CID_EXT_MEDIA_VSINK_BASE + 19)

/* Media video sink class control values V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION_PROFILE */

/**
 * @rst
 * Functional Requirements
 *   It is a control id for allowing user to indicate the profile of the current dolby vision stream.
 *   Media V4L2 Video Sink device must handle the data as a dolby vision stream when V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION is true and the profile data is given through this cid.
 *   For control value, please refer to enumeration v4l2_ext_media_vsink_dolby_vision_profile.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_CTRL       // Get
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION_PROFILE
 *
 *     //
 *     // control value
 *     //
 *     0 (false)
 *     1 (true)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL`
 *   and this control id.
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_MEDIA_VSINK, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION_PROFILE;
 *      ctrl_arg.value = MEDIA_VSINK_DOLBY_VISION_PROFILE_5; // Current stream is a Dolby vision profile 5 stream
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION_PROFILE (V4L2_CID_EXT_MEDIA_VSINK_BASE + 20)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for subscribing or unsubscribing video underrun event for fd
 *   Given device should record the event occurrence in the event queue after registering the video underrun event and manage the event
 *   occurrence information to check the occurrence of the event through ioctl DQEVENT.
 *   The value set as the type when the corresponding control ID is called is registered as
 *   V4L2_SUB_EXT_MEDIA_VSINK_BASE which means media vsink related event.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT, VIDIOC_UNSUBSCRIBE_EVENT
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_DQEVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_event_subscription subscription_arg;
 *
 *      subscription_arg.type = V4L2_EVENT_PRIVATE_EXT_MEDIA_VSINK_EVENT;
 *      subscription_arg.id = V4L2_SUB_EXT_MEDIA_VIDEO_UNDERRUN;
 *
 *      ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &subscription_arg); // Subscribe video underrun event
 *
 *      ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &subscription_arg); // Unsubscribe video underrun event
 *
 *      // When vidoe underrun event is occured, count the number of event occurence.
 *      pollfd poll_fd;
 *      struct v4l2_event evt_arg;
 *      memset(&evt_arg, 0, sizeoof(evt_arg));
 *
 *      long video_underrun_count = 0;
 *      while(true) {
 *          poll_fd.fd = fd;
 *          poll_fd.event = POLLPRI;
 *          poll_fd.revent = 0;
 *
 *          while(0 < poll(&poll_fd, 1, 50)) {
 *              ioctl(fd, VIDIOC_DQ_EVENT, &evt_arg);
 *
 *              if (evt_arg.id == V4L2_SUB_EXT_MEDIA_VIDEO_UNDERRUN) video_underrun_count++;
 *
 *              if(0 == event_arg.pending) {
 *                  break;
 *              }
 *      }
 * }
 * @endrst
 */
#define V4L2_SUB_EXT_MEDIA_VIDEO_UNDERRUN (V4L2_SUB_EXT_MEDIA_VSINK_BASE + 1)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for subscribing or unsubscribing the media info ready event.
 *   Driver must sent the media info ready event to the application when the media info is ready.
 *   Media info ready event is used to notify the application that the media info is ready so that the application can get valid media info by the V4L2_CID_EXT_MEDIA_INFO.
 *   Given device should record the event occurrence in the event queue after registering the media info ready event and manage the event
 *   occurrence information to check the occurrence of the event through ioctl DQEVENT.
 *   The value set as the type when the corresponding control ID is called is registered as
 *   V4L2_SUB_EXT_MEDIA_VSINK_BASE which means media vsink related event.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT, VIDIOC_UNSUBSCRIBE_EVENT
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 100ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_DQEVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_event_subscription subscription_arg;
 *
 *      subscription_arg.type = V4L2_EVENT_PRIVATE_EXT_MEDIA_VSINK_EVENT;
 *      subscription_arg.id = V4L2_SUB_EXT_MEDIA_INFO_READY;
 *
 *      ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &subscription_arg); // Subscribe video underrun event
 *
 *      ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &subscription_arg); // Unsubscribe video underrun event
 *
 *      // When vidoe underrun event is occured, count the number of event occurence.
 *      pollfd poll_fd;
 *      struct v4l2_event evt_arg;
 *      memset(&evt_arg, 0, sizeoof(evt_arg));
 *
 *      while(true) {
 *          poll_fd.fd = fd;
 *          poll_fd.event = POLLPRI;
 *          poll_fd.revent = 0;
 *
 *          while(0 < poll(&poll_fd, 1, 50)) {
 *              ioctl(fd, VIDIOC_DQ_EVENT, &evt_arg);
 *
 *              if (evt_arg.id == V4L2_SUB_EXT_MEDIA_INFO_READY) getMeidaInfo();
 *          }
 *      }
 * @endrst
 */
#define V4L2_SUB_EXT_MEDIA_INFO_READY (V4L2_SUB_EXT_MEDIA_VSINK_BASE + 2)

/* Media Vsink class control values for V4L2_CID_EXT_MEDIA_CLOCK_SOURCE_TYPE */

/**
 * @brief  Enumeration for clock source type information
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum v4l2_ext_media_clock_source_type {
 *       SYSTEM_CLOCK = 0,           // Note that this is default value.
 *       ATSC3_WALL_CLOCK = 1,       // MEDIA_VIDEO_H265 and Adaptive SeamlessPlay
 *       JP4K_NETWORK_TIME_PROTOCOL = 2
 *     };
 *
 * @endrst
 */
enum v4l2_ext_media_clock_source_type
{
    SYSTEM_CLOCK = 0,
    ATSC3_WALL_CLOCK = 1,
    JP4K_NETWORK_TIME_PROTOCOL = 2
};

/* Media video sink class control values for V4L2_CID_EXT_MEDIA_VSINK_APP_TYPE */

/**
 * @brief  Enumeration for App type information
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum v4l2_ext_media_vsink_app_type {
 *       SINK_APP_UNKNOWN = 0,     // A case that app type is not defined. Note that this is default value.
 *       SINK_APP_SEAMLESS,       // MEDIA_VIDEO_H265 and Adaptive SeamlessPlay
 *       SINK_APP_CHROME,         // PLATFORM_RTK and Chrome
 *       SINK_APP_JP4K,          // MEDIA_TRANS_JAPAN_4K PLAYER
 *       SINK_APP_SYE,           // (PLATFORM_REALTEK or PLATFORM_MTK) and Amazon
 *       SINK_APP_DIRECTMEDIA,   // Direct Media Player
 *       SINK_APP_RTC           // Miracast application type
 *     };
 *
 * @endrst
 */
enum v4l2_ext_media_vsink_app_type
{
    SINK_APP_UNKNOWN = 0,
    SINK_APP_SEAMLESS,
    SINK_APP_CHROME,
    SINK_APP_JP4K,
    SINK_APP_SYE,
    SINK_APP_DIRECTMEDIA,
    SINK_APP_RTC
};

/* Media video sink enumeration values for hdr type information field of V4L2_EXT_MEDIA_INFO structure */

/**
 * @brief  Enumeration for HDR type information
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum v4l2_ext_hdr_type {
 *       NONE = 0,     // Note that this is default value
 *       HDR10,
 *       HLG,
 *       PRIME,
 *       DOLBY
 *     };
 *
 * @endrst
 */
enum v4l2_ext_media_hdr_type
{
    NONE = 0,
    HDR10,
    HLG,
    PRIME,
    DOLBY
};

/* Media video sink class control values for V4L2_CID_EXT_MEDIA_VSINK_DOLBY_VISION_PROFILE */

/**
 * @brief  Enumeration for Dolby vision profile information
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum v4l2_ext_media_vdec_dolby_vision_profile {
 *       MEDIA_VSINK_DOLBY_VISION_PROFILE_NONE = 0, // Note that this is default value. This indicates taht the current stream is not a dolby vision stream.
 *       MEDIA_VSINK_DOLBY_VISION_PROFILE_4 = 4,    // Dolby Vision profile 4
 *       MEDIA_VSINK_DOLBY_VISION_PROFILE_5 = 5,    // Dolby Vision profile 5
 *       MEDIA_VSINK_DOLBY_VISION_PROFILE_7 = 7,    // Dolby Vision profile 7
 *       MEDIA_VSINK_DOLBY_VISION_PROFILE_8 = 8,    // Dolby Vision profile 8
 *       MEDIA_VSINK_DOLBY_VISION_PROFILE_9 = 9,    // Dolby Vision profile 9
 *       MEDIA_VSINK_DOLBY_VISION_PROFILE_10 = 10,  // Dolby Vision profile 10
 *     };
 *
 * @endrst
 */
enum v4l2_ext_media_vsink_dolby_vision_profile
{
    MEDIA_VSINK_DOLBY_VISION_PROFILE_NONE = 0, // Note that this is default value. This indicates that the current stream is not a dolby vision stream.
    MEDIA_VSINK_DOLBY_VISION_PROFILE_4 = 4,    // Dolby Vision profile 4
    MEDIA_VSINK_DOLBY_VISION_PROFILE_5 = 5,    // Dolby Vision profile 5
    MEDIA_VSINK_DOLBY_VISION_PROFILE_7 = 7,    // Dolby Vision profile 7
    MEDIA_VSINK_DOLBY_VISION_PROFILE_8 = 8,    // Dolby Vision profile 8
    MEDIA_VSINK_DOLBY_VISION_PROFILE_9 = 9,    // Dolby Vision profile 9
    MEDIA_VSINK_DOLBY_VISION_PROFILE_10 = 10,  // Dolby Vision profile 10
};

/**
 * @brief  Struct for Media info
 *
 * @rst
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | Variable                       | Return Value                                                                |
 * +================================+=============================================================================+
 * | pixel_aspect                   | Pixel Aspect ratio.Note taht numerator is width and denominator is height   |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | framerate                      | Framerate of Media                                                          |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | afd                            | Active Format Description                                                   |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | vdec_ch                        | Video Decoder Channel Number from VSM                                       |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | video                          | Resolution of video                                                         |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | scan_type                      | Scan type                                                                   |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | crop_left                      | The informations of crop left                                               |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | crop_right                     | The informations of crop right                                              |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | crop_top                       | The informations of crop top                                                |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | crop_bottom                    | The informations of crop bottom                                             |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | transfer_characteristics       | color transfer characteristics of media                                     |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | color_primaries                | color primaries of media                                                    |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | matrix_coeffs                  | matrix coeffcients of media                                                 |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | video_full_range_flag          | video full range flag of media                                              |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | display_primaries_x0           | display_primaries_x0 of media                                               |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | display_primaries_x1           | display_primaries_x1 of media                                               |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | display_primaries_x2           | display_primaries_x2 of media                                               |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | display_primaries_y0           | display_primaries_y0 of media                                               |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | display_primaries_y1           | display_primaries_y1 of media                                               |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | display_primaries_y2           | display_primaries_y2 of media                                               |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | white_point_x                  | white_point_x of media                                                      |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | white_point_y                  | white_point_y of media                                                      |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | max_display_mastering_luminance| max_display_mastering_luminance of media                                    |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | min_display_mastering_luminance| min_display_mastering_luminance of media                                    |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | max_content_light_level        | max_content_light_level of media                                            |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | max_pic_average_light_level    | max_pic_average_light_level of media                                        |
 * +--------------------------------+-----------------------------------------------------------------------------+
 * | hdr_type                       | hdr type of media                                                           |
 * +--------------------------------+-----------------------------------------------------------------------------+
 *
 *
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_media_info {
 *         struct v4l2_fract pixel_aspect; //  Pixel Aspect ratio. Note taht numerator is width and denominator is height
 *         struct v4l2_fract framerate; // Frame rate of media
 *         __u32 afd; // Active Format Description
 *         __s32 vdec_ch; // Video decoder channel number from VSM
 *         struct v4l2_rect video; // width and height of video
 *         enum v4l2_field scan_type; // scan_type
 *         __u32 crop_left; // The informations of crop left
 *         __u32 crop_right; // The informations of crop right
 *         __u32 crop_top; // The informations of crop top
 *         __u32 crop_bottom; // The informations of crop bottom
 *         __u32 transfer_characteristics; // color transfer characteristics of media
 *         __u32 color_primaries; // color primaries of media
 *         __u32 matrix_coeffs; // matrix coeffcients of media
 *         __u8 video_full_range_flag; // video full range flag of media
 *         __u32 display_primaries_x0; // display_primaries_x0 of media
 *         __u32 display_primaries_x1; // display_primaries_x1 of media
 *         __u32 display_primaries_x2; // display_primaries_x2 of media
 *         __u32 display_primaries_y0; // display_primaries_y0 of media
 *         __u32 display_primaries_y1; // display_primaries_y1 of media
 *         __u32 display_primaries_y2; // display_primaries_y2 of media
 *         __u32 white_point_x; // white_point_x of media
 *         __u32 white_point_y; // white_point_y of media
 *         __u32 max_display_mastering_luminance; // max_display_mastering_luminance of media
 *         __u32 min_display_mastering_luminance; // min_display_mastering_luminance of media
 *         __s32 max_content_light_level; // max_content_light_level of media
 *         __s32 max_pic_average_light_level; // max_pic_average_light_level of media
 *         enum v4l2_ext_media_hdr_type hdr_type; // hdr type of media
 *      };
 *
 * @endrst
 */
struct v4l2_ext_media_info {
    struct v4l2_fract pixel_aspect; // Pixel Aspect ratio. Note that numerator is width and denominator is height
    struct v4l2_fract framerate;
    __u32 afd; // Active Format Description
    __s32 vdec_ch; // Video decoder channel number from VSM
    struct v4l2_rect video; // Width and height of video
    enum v4l2_field scan_type; // Scan type of media
    __u32 crop_left; // The informations of crop left
    __u32 crop_right; // The informations of crop right
    __u32 crop_top; // The informations of crop top
    __u32 crop_bottom; // The informations of crop bottom
    __u32 transfer_characteristics; // color transfer characteristics of media
    __u32 color_primaries; // color primaries of media
    __u32 matrix_coeffs; // matrix coeffcients of media
    __u8 video_full_range_flag; // video full range flag of media
    __u32 display_primaries_x0; // display_primaries_x0 of media
    __u32 display_primaries_x1; // display_primaries_x1 of media
    __u32 display_primaries_x2; // display_primaries_x2 of media
    __u32 display_primaries_y0; // display_primaries_y0 of media
    __u32 display_primaries_y1; // display_primaries_y1 of media
    __u32 display_primaries_y2; // display_primaries_y2 of media
    __u32 white_point_x; // white_point_x of media
    __u32 white_point_y; // white_point_y of media
    __u32 max_display_mastering_luminance; // max_display_mastering_luminance of media
    __u32 min_display_mastering_luminance; // min_display_mastering_luminance of media
    __s32 max_content_light_level; // max_content_light_level of media
    __s32 max_pic_average_light_level; // max_pic_average_light_level of media
    enum v4l2_ext_media_hdr_type hdr_type; // hdr type of media
};

/**
 * @brief  Struct for Resource info
 *
 * @rst
 * +------------------------+-----------------------------------------------------------------------------+
 * | Variable               | Return Value                                                                |
 * +========================+=============================================================================+
 * | core_type              | Allocated decoder core name. Note that the length is fixed with 32 bytes    |
 * +------------------------+-----------------------------------------------------------------------------+
 * | video_port             | The number of video decoder port                                            |
 * +------------------------+-----------------------------------------------------------------------------+
 * | max_width              | Maximum value of width which is used for adaptive case                      |
 * +------------------------+-----------------------------------------------------------------------------+
 * | max_height             | Maximum value of height which is used for adaptive case                     |
 * +------------------------+-----------------------------------------------------------------------------+
 * | max_frame_rate         | Maximum value of frame rate which is used for adaptive case                 |
 * +------------------------+-----------------------------------------------------------------------------+
 * | hfr                    | Whether the current video is high frame rate video                          |
 * +------------------------+-----------------------------------------------------------------------------+
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_media_sink_resource_info {
 *         __u8 core_type[32];         // Allocated decoder core name
 *         __u32 video_port;             // The number of video decoder port
 *         __u32 max_width;              // Maximum value of width which is used for adaptive case
 *         __u32 max_height;             // Maximum value of height which is used for adaptive case
 *         struct v4l2_fract max_frame_rate;  // Maximum value of frame rate which is used for adaptive case
 *         __u8 hfr; // Whether the current video is high frame rate video
 *     };
 *
 * @endrst
 */
struct v4l2_ext_media_sink_resource_info
{
    /** Allocated decoder core name */
    __u8 core_type[32];
    /** the number of VDEC port */
    __u32 video_port;
    /** Maximum value of width which is used for adaptive case */
    __u32 max_width;
    /** Maximum value of height which is used for adaptive case */
    __u32 max_height;
    /** Maximum value of frame rate which is used for adaptive case */
    struct v4l2_fract max_frame_rate;
    /** Whether the current video is high frame rate video */
    __u8 hfr;
};

#endif