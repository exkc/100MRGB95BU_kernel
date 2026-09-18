#ifndef _MEDIA_VDEC_VENC_EXT_H
#define _MEDIA_VDEC_VENC_EXT_H

#include <linux/v4l2-controls.h>

#ifndef _UAPI__LINUX_VIDEODEV2_H
#include <linux/videodev2.h>
#endif

#ifndef V4L2_EXT_DEV_PATH_MEDIA_VDEC 
#define V4L2_EXT_DEV_PATH_MEDIA_VDEC "/dev/video21"
#endif

#ifndef V4L2_EXT_DEV_PATH_MEDIA_VENC 
#define V4L2_EXT_DEV_PATH_MEDIA_VENC "/dev/video24"
#endif

/* Media VDEC/VENC class control IDs */
#define V4L2_CID_USER_EXT_MEDIA_VDEC_VENC_BASE (V4L2_CID_USER_BASE + 0x8700)
#define V4L2_CID_EXT_MEDIA_VDEC_VENC_BASE (V4L2_CID_USER_EXT_MEDIA_VDEC_VENC_BASE + 0x0)

/* Media VDEC/VENC class subscription types */
#define V4L2_EVENT_PRIVATE_EXT_MEDIA_VDEC_VENC_BASE (V4L2_EVENT_PRIVATE_START + 0x8700)

/**
 * @rst
 * Functional Requirements
 *   V4L2 Subscription Type for Media VDEC/VENC
 * @endrst
 */
#define V4L2_EVENT_PRIVATE_EXT_MEDIA_VDEC_VENC_EVENT (V4L2_EVENT_PRIVATE_EXT_MEDIA_VDEC_VENC_BASE + 1)

/* Media VDEC/VENC class subscription event IDs */
#define V4L2_SUB_EXT_MEDIA_VDEC_VENC_BASE (0x8700)

/* Media VDEC/VENC class control values V4L2_CID_EXT_MEDIA_RES_INFO */

/**
 * @rst
 * Functional Requirements
 *   After acquisition of H/W resource is completed, Allocated resource information must be set.
 *   This is a control id used to set the allocated resource information.
 *   Also, you can check the allocated resource information by getting a value from this control id.
 *   Based on this information, Media VDEC must prepare resource.
 *   For example, In max-width, max-height case, it is used for adaptive streaming case.
 *   In adaptive streaming case, Media VDEC must prepare buffer for this resolution stream input so that it can be displayed seamlessly even if the resolution changes.
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
 *     V4L2_CID_EXT_RES_INFO
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
 *          struct v4l2_ext_resource_info res_info;
 *          struct v4l2_ext_controls ext_ctrls;
 *          struct v4l2_ext_control ext_ctrl;
 *          memset(&res_info, 0, sizeof(res_info));
 *          memset(&ext_ctrls, 0, sizeof(ext_ctrls));
 *          memset(&ext_ctrl, 0, sizeof(ext_ctrl));
 * 
 *          strcpy(res_info.core_name, "G1_H264");
 *          res_info.video_port = 1;
 *          ...
 * 
 *          ext_ctrls.count    = 1;
 *          ext_ctrls.controls = &ext_ctrl;
 *
 *          ext_ctrl.id        = V4L2_CID_EXT_MEDIA_RES_INFO;
 *          ext_ctrl.size      = sizeof(v4l2_ext_resource_info);
 *          ext_ctrl.ptr       = &res_info;
 *
 *          rc                 = ioctl(media_vdec_fd, VIDIOC_S_EXT_CTRLS, &ext_ctrls_arg);
 *          
 *          return rc;
 *      }
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_RES_INFO (V4L2_CID_EXT_MEDIA_VDEC_VENC_BASE + 1)

/* Media VDEC/VENC class control values V4L2_CID_EXT_MEDIA_SVP */

/**
 * @rst
 * Functional Requirements
 *   It is a control id for using Secure Video Path(SVP). 
 *   You can also check whether the decoder is currently using SVP by getting a value from this control id.
 *   When this CID value is true, Video Decoder must allocated memory to secure region.
 *   Also the decoding process must be executed in secure area.
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
 *     V4L2_CID_EXT_MEDIA_SVP
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
 *      fd = open(V4L2_EXT_DEV_PATH_MEDIA_VDEC, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_SVP;
 *      ctrl_arg.value = 0;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_SVP (V4L2_CID_EXT_MEDIA_VDEC_VENC_BASE + 3)

/* Media VDEC/VENC class control values V4L2_CID_EXT_MEDIA_VDEC_APP_TYPE */

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
 *     V4L2_CID_EXT_MEDIA_VDEC_APP_TYPE
 *
 *     //
 *     // control value
 *     //
 *     SEAMLESS, CHROME, JP4K, SYE, DIRECTMEDIA, RTC
 *     (See enum v4l2_ext_app_type)
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
 *      fd = open(V4L2_EXT_DEV_PATH_MEDIA_VDEC, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_VDEC_APP_TYPE;
 *      ctrl_arg.value = SEAMLESS;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VDEC_APP_TYPE (V4L2_CID_EXT_MEDIA_VDEC_VENC_BASE + 4)

/* Media VDEC/VENC class control values V4L2_CID_EXT_MEDIA_DECODED_SIZE */

/**
 * @rst
 * Functional Requirements
 *   Get the size of decoder element's decoded video es
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
 *     V4L2_CID_EXT_MEDIA_DECODED_SIZE
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
 *      __u64 LGE_API_GetDecodedSize()
 *      {
 *          int rc;
 *
 *          struct v4l2_ext_controls ext_ctrls;
 *          struct v4l2_ext_control ext_ctrl;
 *          memset(&ext_ctrls, 0, sizeof(ext_ctrls));
 *          memset(&ext_ctrl, 0, sizeof(ext_ctrl));
 *
 *          ext_ctrls.count    = 1;
 *          ext_ctrls.controls = &ext_ctrl;
 *
 *          ext_ctrl.id        = V4L2_CID_EXT_MEDIA_DECODED_SIZE;
 *          ext_ctrl.size      = 0;
 *
 *          rc                 = ioctl(meida_vdec_fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 * 
 *          if (rc < 0) return rc;
 *          
 *          return (__u64) ext_ctrl.__s64;
 *      }
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_DECODED_SIZE (V4L2_CID_EXT_MEDIA_VDEC_VENC_BASE + 8)

/* Media VDEC/VENC class control values V4L2_CID_EXT_MEDIA_UNDECODED_SIZE */

/**
 * @rst
 * Functional Requirements
 *   Get the size of decoder element's undecoded video es
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
 *     V4L2_CID_EXT_MEDIA_UNDECODED_SIZE
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
 *      __u64 LGE_API_GetUnDecodedSize()
 *      {
 *          int rc;
 *
 *          struct v4l2_ext_controls ext_ctrls;
 *          struct v4l2_ext_control ext_ctrl;
 *          memset(&ext_ctrls, 0, sizeof(ext_ctrls));
 *          memset(&ext_ctrl, 0, sizeof(ext_ctrl));
 *
 *          ext_ctrls.count    = 1;
 *          ext_ctrls.controls = &ext_ctrl;
 *
 *          ext_ctrl.id        = V4L2_CID_EXT_MEDIA_UNDECODED_SIZE;
 *          ext_ctrl.size      = 0;
 *
 *          rc                 = ioctl(media_vdec_Fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 * 
 *          if (rc < 0) return rc;
 *          
 *          return (__u64) ext_ctrl.__s64;
 *      }
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_UNDECODED_SIZE (V4L2_CID_EXT_MEDIA_VDEC_VENC_BASE + 9)

/* Media VDEC/VENC class control values V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION */

/**
 * @rst
 * Functional Requirements
 *   It is a control id for allowing user to indicate the current stream status as a dolby vision.
 *   If the value of this control id is true, it means that the current stream is a dolby vision stream.
 *   So Decoder must decode it properly based on dolby vision specification.
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
 *     V4L2_CID_EXT_MEDIA_DOLBY_VISION
 *
 *     //
 *     // control value
 *     //
 *     0 (false, Current stream is not a dolby vision stream)
 *     1 (true, Current stream is a dolby vision stream)
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
 *      fd = open(V4L2_EXT_DEV_PATH_MEDIA_VDEC, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION;
 *      ctrl_arg.value = 0;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION (V4L2_CID_EXT_MEDIA_VDEC_VENC_BASE + 10)

/* Media VDEC/VENC class control values V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION_PROFILE */

/**
 * @rst
 * Functional Requirements
 *   It is a control id for allowing user to indicate the profile of the current dolby vision stream.
 *   Media V4L2 Video Decoder must handle the data as a dolby vision stream when V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION is true and the profile data is given through this cid.
 *   For control value, please refer to enumeration v4l2_ext_media_vdec_dolby_vision_profile.
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
 *     V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION_PROFILE
 *
 *     //
 *     // control value
 *     //
 *     See enum v4l2_ext_media_vdec_dolby_vision_profile
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
 *      fd = open(V4L2_EXT_DEV_PATH_MEDIA_VDEC, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION_PROFILE;
 *      ctrl_arg.value = MEDIA_VDEC_DOLBY_VISION_PROFILE_5; // Current stream is a Dolby vision profile 5 stream
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 * @endrst
 */
#define V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION_PROFILE (V4L2_CID_EXT_MEDIA_VDEC_VENC_BASE + 11)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for subscribing or unsubscribing Corrupted frame event for fd
 *   Given device should record the event occurrence in the event queue after registering the Corrupted frame event and manage the event
 *   occurrence information to check the occurrence of the event through ioctl
 *   DQEVENT. The value set as the type when the corresponding control ID is called is registered as
 *   V4L2_EVENT_PRIVATE_EXT_MEDIA_VDEC_VENC_EVENT which means meadia vdec/venc related event.
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
 *      subscription_arg.type = V4L2_EVENT_PRIVATE_EXT_MEDIA_VDEC_VENC_EVENT;
 *      subscription_arg.id = V4L2_SUB_EXT_MEDIA_VDEC_CORRUPTED_FRAME;
 *
 *      ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &subscription_arg); // Subscribe corrupted frame event
 *
 *      ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &subscription_arg); // Unsubscribe corrupted frame event
 * 
 *      // When Corrupted frame event is occured, count the number of event occurence.
 *      pollfd poll_fd;
 *      struct v4l2_event evt_arg;
 *      memset(&evt_arg, 0, sizeoof(evt_arg));
 * 
 *      long corrupted_frame_cnt;
 *      while(true) {
 *          poll_fd.fd = fd;
 *          poll_fd.event = POLLPRI;
 *          poll_fd.revent = 0;
 * 
 *          while(0 < poll(&poll_fd, 1, 50)) {
 *              ioctl(fd, VIDIOC_DQ_EVENT, &evt_arg);
 * 
 *              if (evt_arg.id == V4L2_SUB_EXT_VDEC_CORRUPTED_FRAME) corrupted_frame_cnt++;
 *
 *              if(0 == event_arg.pending) {
 *                  break;
 *              }
 *      }
 * }
 * @endrst
 */
#define V4L2_SUB_EXT_MEDIA_VDEC_CORRUPTED_FRAME (V4L2_SUB_EXT_MEDIA_VDEC_VENC_BASE + 1)

/* Media VDEC/VENC class control values for V4L2_CID_EXT_MEDIA_VDEC_APP_TYPE */

/**
 * @brief  Enumeration for App type information
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum v4l2_ext_media_vdec_app_type {
 *       UNKNOWN = 0,     // A case that app type is not defined. Note that this is default value.
 *       SEAMLESS,       // MEDIA_VIDEO_H265 and Adaptive SeamlessPlay
 *       CHROME,         // PLATFORM_RTK and Chrome
 *       JP4K,          // MEDIA_TRANS_JAPAN_4K PLAYER
 *       SYE,           // (PLATFORM_REALTEK or PLATFORM_MTK) and Amazon
 *       DIRECTMEDIA,   // Direct Media Player
 *       RTC,          // Miracast application type
 *     };
 * 
 * @endrst
 */
enum v4l2_ext_media_vdec_app_type
{
    UNKNOWN = 0,
    SEAMLESS,
    CHROME,
    JP4K,
    SYE,
    DIRECTMEDIA,
    RTC
};

/* Media VDEC/VENC class control values for V4L2_CID_EXT_MEDIA_VDEC_DOLBY_VISION_PROFILE */

/**
 * @brief  Enumeration for Dolby vision profile information
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum v4l2_ext_media_vdec_dolby_vision_profile {
 *       MEDIA_VDEC_DOLBY_VISION_PROFILE_NONE = 0, // Note that this is default value. This indicates taht the current stream is not a dolby vision stream.
 *       MEDIA_VDEC_DOLBY_VISION_PROFILE_4 = 4,    // Dolby Vision profile 4
 *       MEDIA_VDEC_DOLBY_VISION_PROFILE_5 = 5,    // Dolby Vision profile 5
 *       MEDIA_VDEC_DOLBY_VISION_PROFILE_7 = 7,    // Dolby Vision profile 7
 *       MEDIA_VDEC_DOLBY_VISION_PROFILE_8 = 8,    // Dolby Vision profile 8
 *       MEDIA_VDEC_DOLBY_VISION_PROFILE_9 = 9,    // Dolby Vision profile 9
 *       MEDIA_VDEC_DOLBY_VISION_PROFILE_10 = 10,  // Dolby Vision profile 10
 *     };
 *
 * @endrst
 */
enum v4l2_ext_media_vdec_dolby_vision_profile
{
    MEDIA_VDEC_DOLBY_VISION_PROFILE_NONE = 0, // Note that this is default value. This indicates that the current stream is not a dolby vision stream.
    MEDIA_VDEC_DOLBY_VISION_PROFILE_4 = 4,    // Dolby Vision profile 4
    MEDIA_VDEC_DOLBY_VISION_PROFILE_5 = 5,    // Dolby Vision profile 5
    MEDIA_VDEC_DOLBY_VISION_PROFILE_7 = 7,    // Dolby Vision profile 7
    MEDIA_VDEC_DOLBY_VISION_PROFILE_8 = 8,    // Dolby Vision profile 8
    MEDIA_VDEC_DOLBY_VISION_PROFILE_9 = 9,    // Dolby Vision profile 9
    MEDIA_VDEC_DOLBY_VISION_PROFILE_10 = 10,  // Dolby Vision profile 10
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
 *     struct v4l2_ext_media_resource_info {
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
struct v4l2_ext_media_resource_info
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

#endif // #ifndef _MEDIA_VDEC_VENC_EXT_H