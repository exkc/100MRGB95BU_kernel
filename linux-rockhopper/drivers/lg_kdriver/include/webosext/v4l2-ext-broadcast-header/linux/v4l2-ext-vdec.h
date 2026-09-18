/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_VDEC_H
#define _V4L2_EXT_VDEC_H

#include <linux/v4l2-controls.h>

#ifndef _UAPI__LINUX_VIDEODEV2_H
#include <linux/videodev2.h>
#endif

#define V4L2_EXT_DEV_NO_VDEC 20
#define V4L2_EXT_DEV_NO_VDA 21
#define V4L2_EXT_DEV_NO_VEA 24
#define V4L2_EXT_DEV_PATH_VDEC "/dev/video20"
#define V4L2_EXT_DEV_PATH_VDA "/dev/video21"
#define V4L2_EXT_DEV_PATH_VEA "/dev/video24"

/* VDEC class control IDs */
#define V4L2_CID_USER_EXT_VDEC_BASE (V4L2_CID_USER_BASE + 0x8000)
#define V4L2_CID_EXT_VDEC_BASE (V4L2_CID_USER_EXT_VDEC_BASE + 0x0)

/* VDEC class control values V4L2_CID_EXT_VDEC_DECODING_SPEED*/

/**
 * @brief Pauses PVR playback
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_DECODING_SPEED_PAUSE 0
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_DECODING_SPEED_PAUSE 0

/**
 * @brief Half speed of PVR playback
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_DECODING_SPEED_SLOW 500
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_DECODING_SPEED_SLOW 500

/**
 * @brief Default PVR playback speed
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_DECODING_SPEED_NORMAL 1000
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_DECODING_SPEED_NORMAL 1000

/**
 * @brief 2x playback speed
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_DECODING_SPEED_2x 2000
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_DECODING_SPEED_2x 2000

/* VDEC class control values V4L2_CID_EXT_VDEC_DECODE_MODE */

/**
 * @brief  Decoding I-Frame Only
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_DECODE_I_FRAME (1)
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_DECODE_I_FRAME (1)

/**
 * @brief  Decoding I-Frame and P-Frame Only
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_DECODE_IP_FRAME (2)
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_DECODE_IP_FRAME (2)

/**
 * @brief  Decoding Every Frame(I/B/P)
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_DECODE_IP_FRAME (2)
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_DECODE_ALL_FRAME (3)

/* VDEC State for v4l2_ext_decoder_status vdecState*/

/**
 * @brief  Default value of UNINIT
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_STATE_UNINIT (0)
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_STATE_UNINIT (0)

/**
 * @brief  Initialized status of VDEC
 *
 * At least a fd is opened.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_STATE_INIT (1)
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_STATE_INIT (1)

/**
 * @brief  VDEC is decoding some frames.
 *
 * VDEC got STREAM_ON commands.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_STATE_PLAYING (2)
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_STATE_PLAYING (2)

/**
 * @brief  VDEC is stopped.
 *
 * VDEC got STREAM_OFF commands.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_STATE_PLAYING (2)
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_STATE_STOPPED (3)

/**
 * @brief  Freeze displaying
 *
 * VDEC got V4L2_CID_EXT_VDEC_FREEZE_MODE command. But decoding is working.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     #define V4L2_EXT_VDEC_STATE_PLAYING (2)
 *
 * @endrst
 */
#define V4L2_EXT_VDEC_STATE_FREEZED (4)

/* VDEC class control values for V4L2_CID_EXT_VDEC_VIDEO_INFO */

/**
 * @brief  Struct for VDEC Video information
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     enum v4l2_ext_vdec_video_info {
 *       VDEC_V_SIZE = 0, // Horizontal size
 *       VDEC_H_SIZE,     // Vertical size
 *       VDEC_VIDEO_FORMAT,
 *       VDEC_FRAME_RATE,
 *       VDEC_ASPECT_RATIO,
 *       VDEC_BIT_RATE,
 *       VDEC_PROGRESSIVE_SEQUENCE
 *     };
 *
 *   +---------------------------+-------------------------------------------------+
 *   | v4l2_control id           | Return Value                                    |
 *   +===========================+=================================================+
 *   | VDEC_ASPECT_RATIO         | Video aspect ratio                              |
 *   |                           |                                                 |
 *   |                           | - forbidden : 0                                 |
 *   |                           | - 4:3 : 1                                       |
 *   |                           | - 14:9 : 2                                      |
 *   |                           | - 16:9 : 3                                      |
 *   +---------------------------+-------------------------------------------------+
 *   | VDEC_V_SIZE               | Video Vertical size                             |
 *   +---------------------------+-------------------------------------------------+
 *   | VDEC_H_SIZE               | Video Horizontal size                           |
 *   +---------------------------+-------------------------------------------------+
 *   | VDEC_FRAME_RATE           | Frame rate * 10                                 |
 *   +---------------------------+-------------------------------------------------+
 *   | VDEC_PROGRESSIVE_SEQUENCE | Video scan type                                 |
 *   |                           |                                                 |
 *   |                           | - Interlace: 0                                  |
 *   |                           | - Progressive: 1                                |
 *   +---------------------------+-------------------------------------------------+
 * @endrst
 */
enum v4l2_ext_vdec_video_info
{
    VDEC_V_SIZE = 0,
    VDEC_H_SIZE,
    VDEC_VIDEO_FORMAT,
    VDEC_FRAME_RATE,
    VDEC_ASPECT_RATIO,
    VDEC_BIT_RATE,
    VDEC_PROGRESSIVE_SEQUENCE
};

/* VDEC class control values for V4L2_CID_EXT_VDEC_DECODER_INFO */

/**
 * @brief  Struct for VDEC Status
 *
 * @rst
 * +------------------------+-------------------------------------------------+
 * | Variable               | Return Value                                    |
 * +========================+=================================================+
 * | vdec_state             | - :c:macro:`V4L2_EXT_VDEC_STATE_UNINIT`         |
 * |                        | - :c:macro:`V4L2_EXT_VDEC_STATE_INIT`           |
 * |                        | - :c:macro:`V4L2_EXT_VDEC_STATE_PLAYING`        |
 * |                        | - :c:macro:`V4L2_EXT_VDEC_STATE_STOPPED`        |
 * |                        | - :c:macro:`V4L2_EXT_VDEC_STATE_FREEZED`        |
 * +------------------------+-------------------------------------------------+
 * | still_picture          | - 0: Not a still picture,                       |
 * |                        | - 1: Still picture                              |
 * +------------------------+-------------------------------------------------+
 * | pts_matched            | STC-PTS is matched: 1, else 0                   |
 * +------------------------+-------------------------------------------------+
 * | mb_dec_error_count     | Error MB count (in latest decoded Frame)        |
 * +------------------------+-------------------------------------------------+
 * | es_data_size           | ES data size (in CPB)                           |
 * +------------------------+-------------------------------------------------+
 * | drip_decoding          | drip decoding setting value, On:1, Off:0        |
 * +------------------------+-------------------------------------------------+
 * | decoded_pic_num        | Decoded Picture number (in DPB)                 |
 * +------------------------+-------------------------------------------------+
 * | codec_type             | 0, Not used value, This will be deprecated      |
 * +------------------------+-------------------------------------------------+
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_decoder_status {
 *         __u8 vdec_state;          // VDEC driver current state
 *         __u8 codec_type;          // VDEC driver codec setting type
 *         __u8 av_libsync;          // AV sync On : Ture, Freerun : False
 *         __u8 still_picture;       // Still picture setting On/Off state
 *         __u8 drip_decoding;       // Dripdecoding setting On/Off state
 *         __u32 es_data_size;       // ES Data size in ES buffer
 *         __u32 decoded_pic_num;    // Decoded picture number in DPB
 *         __u32 mb_dec_error_count; // MB(Macro Block) decoding error count
 *         __u32 pts_matched;        // PTS of Dequeued Picture From DPB is matched with STC or not
 *     };
 *
 * @endrst
 */
struct v4l2_ext_decoder_status
{
    /** VDEC driver current state */
    __u8 vdec_state;
    /** VDEC driver codec setting type */
    __u8 codec_type;
    /** AV sync On : Ture, Freerun : False */
    __u8 av_libsync;
    /** Still picture setting On/Off state */
    __u8 still_picture;
    /** Dripdecoding setting On/Off state */
    __u8 drip_decoding;
    /** ES Data size in ES buffer */
    __u32 es_data_size;
    /** Decoded picture number in DPB */
    __u32 decoded_pic_num;
    /** MB(Macro Block) decoding error count */
    __u32 mb_dec_error_count;
    /** PTS of Dequeued Picture From DPB is matched with STC or not */
    __u32 pts_matched;
};

/* VDEC class control values for V4L2_CID_EXT_VDEC_STREAM_INFO */

/**
 * @brief  Struct for VDEC Stream info
 *
 * This structure don't used because V4L2_CID_EXT_VDEC_STREAM_INFO CID is deprecated.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_stream_info {
 *         __u32 v_size;       // vertical size
 *         __u32 h_size;       // horizontal size
 *         __u32 video_format; // video format
 *         __u32 frame_rate;   // frame rate
 *         __u32 aspect_ratio; // aspect_ratio
 *         __u32 bit_rate;     // bit rate
 *         __u32 sequence_header_scan_type; // scan type of sequence header (I, P)
 *         __u32 frame_scan_type; // scan type of frame (I, P)
 *         __u32 picture_type;    // picture type(I, P, B)
 *         __u32 temporal_reference; // temporal reference
 *         __u32 picture_struct;  // Picture struct(Top Field, Bottom Field, Frame)
 *         __u32 top_field_first; // top field first
 *         __u32 repeat_field_first; // repeat_field_first
 *     };
 *
 * @endrst
 */
struct v4l2_ext_stream_info
{
    /** vertical size                                  */
    __u32 v_size;
    /** horizontal size                                */
    __u32 h_size;
    /** video format                                   */
    __u32 video_format;
    /** frame rate                                     */
    __u32 frame_rate;
    /** aspect_ratio                                   */
    __u32 aspect_ratio;
    /** bit rate                                       */
    __u32 bit_rate;
    /** scan type of sequence header (I, P) */
    __u32 sequence_header_scan_type;
    /** scan type of frame (I, P)                      */
    __u32 frame_scan_type;
    /** picture type(I, P, B)                          */
    __u32 picture_type;
    /** temporal reference */
    __u32 temporal_reference;
    /** Picture struct(Top Field, Bottom Field, Frame) */
    __u32 picture_struct;
    /** top field first                                */
    __u32 top_field_first;
    /** repeat_field_first */
    __u32 repeat_field_first;
};

/* VDEC class control values for V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA */

/**
 * @brief  Struct for V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA
 *
 * This is deprecated.
 *
 * SEI and VUI variables are H.264/HEVC Only.
 */
struct v4l2_ext_picinfo_msg
{
    __u8 version; // picture info msg version
    __u8 channel; // VDEC driver channel info

    __u16 frame_rate;        // Frame rate numerator
    __u16 aspect_ratio;      // Aspect ratio
    __u16 h_size;            // Luminance resolution h size
    __u16 v_size;            // Luminance resolution v size
    __u16 bitrate;           // Input Bitrate
    __u8 afd;                // Active_format
    __u16 progressive_seq;   // GOP Scan type(Progressive/interlace)
    __u16 progressive_frame; // Frame Scan type(Progressive/interlace)
    __u16 active_x;          // Active x stard point
    __u16 active_y;          // Active y stard point
    __u16 active_w;          // Active width
    __u16 active_h;          // Active height
    __u16 display_h_size;    // Display H size
    __u16 display_v_size;    // Display V size
    __u8 aspect_ratio_idc;   // VUI info, aspect_ratio_idc
    __u32 sar_width;         // VUI info, sar_width
    __u32 sar_height;        // VUI info, sar_height

    __u8 three_d_info; // 3D info

    __u32 colour_primaries;      // VUI info, colour_primaries
    __u32 transfer_chareristics; // VUI info, transfer_characteristics
    __u32 matrix_coeffs;         // VUI info, matrix_coeffcients
    __u32 display_primaries_x0;  // SEI info, display_primaries_x0
    __u32 display_primaries_y0;  // SEI info, display_primaries_y0
    __u32 display_primaries_x1;  // SEI info, display_primaries_x1
    __u32 display_primaries_y1;  // SEI info, display_primaries_y1
    __u32 display_primaries_x2;  // SEI info, display_primaries_x2
    __u32 display_primaries_y2;  // SEI info, display_primaries_y2
    __u32 white_point_x;         // SEI info, white_point_x
    __u32 white_point_y;         // SEI info, white_point_y
    __u32
        max_display_mastering_luminance; // SEI info, max_display_mastering_luminance
    __u32
        min_display_mastering_luminance; // SEI info, min_display_mastering_luminance
    __u8 overscan_appropriate;           // VUI info, overscan_appropriate_flag
    __u32 video_full_range_flag;         // VUI info, video_full_range_flag
    __u32
        hdr_transfer_characteristic_idc; // SEI info, preferred_transfer_characteristics
};

/* VDEC class control values for V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA_EXT */

/**
 * @brief  Struct for V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA_EXT
 *
 * @rst
 * .. code-block:: cpp
 *
 *    struct v4l2_ext_picinfo_msg_ext {
 *       __u8 channel;
 *       __u16 aspect_ratio;
 *       __u16 h_size;
 *       __u16 v_size;
 *       __u16 bitrate;
 *       __u8 afd;
 *       __u16 progressive_seq;
 *       __u16 progressive_frame;
 *       __u16 active_x;
 *       __u16 active_y;
 *       __u16 active_w;
 *       __u16 active_h;
 *       __u16 display_h_size;
 *       __u16 display_v_size;
 *       __u8 aspect_ratio_idc;
 *       __u32 sar_width;
 *       __u32 sar_height;
 *
 *       __u8 three_d_info;
 *
 *       __u32 colour_primaries;
 *       __u32 transfer_chareristics;
 *       __u32 matrix_coeffs;
 *       __u32 display_primaries_x0;
 *       __u32 display_primaries_y0;
 *       __u32 display_primaries_x1;
 *       __u32 display_primaries_y1;
 *       __u32 display_primaries_x2;
 *       __u32 display_primaries_y2;
 *       __u32 white_point_x;
 *       __u32 white_point_y;
 *       __u32 max_display_mastering_luminance;
 *       __u32 min_display_mastering_luminance;
 *       __u8 overscan_appropriate;
 *       __u32 video_full_range_flag;
 *       __u32 hdr_transfer_characteristic_idc;
 *
 *       truct v4l2_fract frame_rate;
 *    };
 *
 *@endrst
 */
struct v4l2_ext_picinfo_msg_ext
{
    /** VDEC driver channel number                   */
    __u8 channel;
    /** Aspect ratio                                 */
    __u16 aspect_ratio;
    /** Luminance resolution h size                  */
    __u16 h_size;
    /** Luminance resolution v size                  */
    __u16 v_size;
    /** Input Bitrate                                */
    __u16 bitrate;
    /** Active_format                                */
    __u8 afd;
    /** GOP Scan type(Progressive/interlace)         */
    __u16 progressive_seq;
    /** Frame Scan type(Progressive/interlace)       */
    __u16 progressive_frame;
    /** Active x stard point                         */
    __u16 active_x;
    /** Active y stard point                         */
    __u16 active_y;
    /** Active width                                 */
    __u16 active_w;
    /** Active height                                */
    __u16 active_h;
    /** Display H size                               */
    __u16 display_h_size;
    /** Display V size                               */
    __u16 display_v_size;
    /** VUI info, aspect_ratio_idc                   */
    __u8 aspect_ratio_idc;
    /** VUI info, sar_width                          */
    __u32 sar_width;
    /** VUI info, sar_height                         */
    __u32 sar_height;

    /** 3D info                                      */
    __u8 three_d_info;

    /** VUI info, colour_primaries                   */
    __u32 colour_primaries;
    /** VUI info, transfer_characteristics */
    __u32 transfer_chareristics;
    /** VUI info, matrix_coeffcients                 */
    __u32 matrix_coeffs;
    /** SEI info, display_primaries_x0 */
    __u32 display_primaries_x0;
    /** SEI info, display_primaries_y0 */
    __u32 display_primaries_y0;
    /** SEI info, display_primaries_x1 */
    __u32 display_primaries_x1;
    /** SEI info, display_primaries_y1 */
    __u32 display_primaries_y1;
    /** SEI info, display_primaries_x2 */
    __u32 display_primaries_x2;
    /** SEI info, display_primaries_y2 */
    __u32 display_primaries_y2;
    /** SEI info, white_point_x                      */
    __u32 white_point_x;
    /** SEI info, white_point_y                      */
    __u32 white_point_y;
    /** SEI info, max_display_mastering_luminance */
    __u32 max_display_mastering_luminance;
    /** SEI info, min_display_mastering_luminance */
    __u32 min_display_mastering_luminance;
    /** VUI info, overscan_appropriate_flag */
    __u8 overscan_appropriate;
    /** VUI info, video_full_range_flag */
    __u32 video_full_range_flag;
    /** SEI info, preferred_transfer_characteristics */
    __u32 hdr_transfer_characteristic_idc;

    /** Frame rate */
    struct v4l2_fract frame_rate;
};

/* VDEC class control values for V4L2_CID_EXT_VDO_VDEC_CONNECTING */

/**
 * @brief  Struct for V4L2_CID_EXT_VDO_VDEC_CONNECTING
 *
 * For SEETV 2.0
 *
 */
struct v4l2_ext_vdec_vdo_connection
{
    /**  Target VDO Number */
    __u32 vdo_port;
    /**  Target VDEC Number */
    __u32 vdec_port;
};

/* VDEC class control values for v4l2_ext_decoded_picture_buffer */

/**
 * @brief  Struct for controlling the VDEC Decoded Picture Buffer
 *
 * Set control commands for VDEC Decoded Picture Buffer
 * Set 33 bits target PTS for VDEC Freeze
 * Get Info whether the VDEC is frozen or not
 * Get Info the Hash value of the frozen video frame
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_decoded_picture_buffer{
 *         __u32 command;    // control commands for VDEC Decoded Picture Buffer
 *                           // 0: Unfreeze the frozen VDEC
 *                           // 1: Freeze VDEC based on target PTS
 *                           // 2: Enable  the Hash/CRC generation whenever the
 *                           //    FrameType Event occurs
 *                           // 3: Disable the Hash/CRC generation
 *         __u64 target_pts; // 33 bits target PTS
 *         __u32 bFrozen;    // current VDEC is frozen or not
 *         __u32 hashValue;  // unique value which represents the video pattern of
 *                           // the frozen video frame
 *     };
 *
 * @endrst
 */
struct v4l2_ext_decoded_picture_buffer
{
    /** control commands for VDEC Decoded Picture Buffer */
    __u32 command;
    /** 33 bits target PTS */
    __u64 target_pts;
    /** current VDEC is frozen or not */
    __u32 bFrozen;
    /** unique value which represents the video pattern of the frozen video frame */
    __u32 hashValue;
};

/* VDEC class control values for V4L2_CID_EXT_VDEC_GET_PTS */

/**
 * @brief Struct for getting VDEC pts
 *
 * @rst
 * +------------------------+-------------------------------------------------+
 * | Variable               | Return Value                                    |
 * +========================+=================================================+
 * | decoding_picture_pts   | PTS of current decoding picture                 |
 * +------------------------+-------------------------------------------------+
 * | display_picture_pts    | PTS of current displaying picture               |
 * +------------------------+-------------------------------------------------+
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_picture_pts {
 *         __u64 decoding_picture_pts;	// PTS of current decoding picture
 *         __u64 display_picture_pts;	// PTS of current displaying picture
 *     };
 * @endrst
 */
struct v4l2_ext_picture_pts
{
    /** PTS of current decoding picture */
    __u64 decoding_picture_pts;
    /** PTS of current displaying picture */
    __u64 display_picture_pts;
};

/**
 * @brief Set the VDEC Port where FD will be used
 *
 * @rst
 * Functional Requirements
 *   It is a control ID that sets the ioctl function to use a specific VDEC
 *   instance for fd obtained through V4L2 open. When the VDEC instance is set,
 *   variables and settings for that instance must be initialized, and the
 *   resource allocation required for the VDEC instance must be done. It should be
 *   failed if called on fd not returned by open. The relationship between fd and
 *   VDEC instance should be managed in a 1: 1 relationship. If the control ID has
 *   been called for the fd already set to another VDEC instance, or for a VDEC
 *   instance already set to another fd, it must be failed. If the fd is closed,
 *   the connection to fd and VDEC instance is released, and then the VDEC
 *   instance can be connected to another fd. The value set in the value of the
 *   corresponding control ID is the number of the VDEC instance, which can have a
 *   value from 0 to the number of VDEC instances supported by the driver - 1. The
 *   number of instances of VDEC is 2 at the current time when the document is
 *   modified, and can be extended to a maximum of 256 in the future.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_CHANNEL
 *
 *     //
 *     // control value
 *     //
 *     0~N (VDEC Port Number)
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      int fd = -1;
 *      int vdec_port = 0;
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VDEC, O_RDWR);
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_CHANNEL;
 *      ctrl_arg.value = vdec_port;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_CHANNEL (V4L2_CID_EXT_VDEC_BASE + 1)

/**
 * @brief Connect VDEC to VTP
 *
 * @deprecated
 *  Deprecated since webOS 5.0, it will be removed from webOS 24.
 *
 *  VIDIOC_S_INPUT is used instead of this command.
 */
#define V4L2_CID_EXT_VDEC_VTP_PORT \
    (V4L2_CID_EXT_VDEC_BASE + 2) // Deprecated CID

/**
 * @brief Reset the VDEC
 *
 * @rst
 * Functional Requirements
 *   The control ID initializes and reset all VDEC instance settings for fd
 *   assigned VDEC instance, and flushes buffers related to decoding such as CPB
 *   (Coded Picture Buffer) and DPB (Decoded Picture Buffer). When the
 *   corresponding control ID is called, ES data corresponding to the decoded
 *   frame should be processed so as to prevent malfunction after reset. The value
 *   set in the value of the corresponding control ID don't need to set.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_RESETTING
 *
 *     //
 *     // control value
 *     //
 *     Any value
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_RESETTING;
 *      ctrl_arg.value = 1; // Don't care.
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_RESETTING (V4L2_CID_EXT_VDEC_BASE + 3)

/**
 * @brief Connect VDO to VDEC
 *
 * @deprecated
 *  Deprecated since webOS 5.0, it will be removed from webOS 24.
 *
 *  V4L2_CID_EXT_VDO_VDEC_CONNECTING / V4L2_CID_EXT_VDO_VDEC_DISCONNECTING is
 *  used instead of this command.
 */
#define V4L2_CID_EXT_VDEC_VDO_PORT \
    (V4L2_CID_EXT_VDEC_BASE +      \
     4) // Deprecated CID

/**
 * @brief Video sync control
 *
 * @rst
 * Functional Requirements
 *   It is control ID that turns on / off AV sync Logic for fd where VDEC instance
 *   is set. The default setting is On. If the PTS (Presentation Time Stamp) of
 *   the decoded picture is within the video sync threshold (default 5sec)
 *   difference based on the STC (System Timing Clock) in the On state, Picture
 *   data should be transferred to the VSC if it gets bigger or falls within 1sec
 *   / frame rate difference. When it is off, it operates as Freerun and picture
 *   data should be transferred to VSC at 1sec / frame rate. Video sync logic is
 *   logic for transmitting picture data to VSC module based on STC and PTS value.
 *   If the difference between STC and PTS is more than the set threshold (default
 *   5 seconds), it operates as Freerun and displays to display every 1sec / frame
 *   rate. If STC has a large PTS, it drops the picture. If the STC is less than
 *   the PTS and the threshold (default 5 sec), it should maintain the picture
 *   currently displayed until the difference decreases within 1 sec / frame rate.
 *   The values set in the value of the control ID can be 0 and 1, 1 means On, 0
 *   means Off.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_AV_SYNC
 *
 *     //
 *     // control value
 *     //
 *     0: Disable , 1: Enable
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_AV_SYNC;
 *      ctrl_arg.value = 1; // On : 1, Off : 0
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_AV_SYNC (V4L2_CID_EXT_VDEC_BASE + 5)

/**
 * @brief Control Frame advanced mode for PVR
 *
 * @rst
 * Functional Requirements
 *   It is a control ID that turns on / off the frame advance mode for fd in which
 *   VDEC instance is set. After VIDIOC_STREAMON, V4L2_CID_EXT_VDEC_FRAME_ADVANCE
 *   can be called. The default setting is Off. Each time Frame advance mode On is
 *   called, a frame is decoded and the data of the next picture to be displayed
 *   is repeatedly transmitted to VSC. When Frame advance mode is Off, frame
 *   decoding and transmission of picture data to VSC are resumed without frame
 *   drop. Frame advance mode is a mode for decoding and displaying frame by frame
 *   when you press the pause button two or more times. When the corresponding
 *   control ID is called, the value set to value can be 0 or 1, 1 means On, 0
 *   means Off.
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
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_FRAME_ADVANCE
 *
 *     //
 *     // control value
 *     //
 *     0: Disable , 1: Enable
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and this
 *   control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and this
 *   control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_FRAME_ADVANCE;
 *      ctrl_arg.value = 1; // On : 1, Off : 0
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_FRAME_ADVANCE (V4L2_CID_EXT_VDEC_BASE + 6)

/**
 * @brief Control decoding speed
 *
 * @rst
 * Functional Requirements
 *   It is a control ID for setting the decoding speed for fd in which VDEC
 *   instance is set. Decoding and displaying is performed at a speed
 *   corresponding to 1/1000 of the set value. The value set in the value of the
 *   control ID is the speed to be decoded, and is set by multiplying the
 *   specified speed by 1000.
 *   (Ex : Normal speed : 1000, 2x : 2000, 4x : 4000, 64x : 64000, 0.5x  : 500 )
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_DECODING_SPEED
 *
 *     //
 *     // control value
 *     //
 *     V4L2_EXT_VDEC_DECODING_SPEED_PAUSE 0
 *     V4L2_EXT_VDEC_DECODING_SPEED_SLOW 500
 *     V4L2_EXT_VDEC_DECODING_SPEED_NORMAL 1000
 *     V4L2_EXT_VDEC_DECODING_SPEED_2x 2000
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_DECODING_SPEED;
 *      ctrl_arg.value = V4L2_EXT_VDEC_DECODING_SPEED_SLOW
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DECODING_SPEED (V4L2_CID_EXT_VDEC_BASE + 7)

/**
 * @brief Set decode mode
 *
 * @rst
 * Functional Requirements
 *   It is a control ID that sets Decoding Mode for fd where VDEC instance is set.
 *   The DTV stream consists of one complete frame I frame, a P frame with only
 *   difference data referring to the other frame, and a B frame with only
 *   difference data referring to two frames. Set the Frame to be decoded by the
 *   corresponding control ID call. When the corresponding control ID is called,
 *   the value set in value means Decode Mode and can be 1 ~ 3. The value of each
 *   value is 1, decoding only for I frame, 2, decoding for I and P frames, 3,
 *   decoding for all frames, default value is 3.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_DECODE_MODE
 *
 *     //
 *     // control value
 *     //
 *     #define V4L2_EXT_VDEC_DECODE_I_FRAME   ( 1 )
 *     #define V4L2_EXT_VDEC_DECODE_IP_FRAME  ( 2 )
 *     #define V4L2_EXT_VDEC_DECODE_ALL_FRAME ( 3 )
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_DECODE_MODE;
 *      ctrl_arg.value = V4L2_EXT_VDEC_DECODE_ALL_FRAME;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DECODE_MODE (V4L2_CID_EXT_VDEC_BASE + 8)

/**
 * @brief Control displaying Video output
 *
 * @rst
 * Functional Requirements
 *   It is a control ID that turns on / off Freeze Mode for fd in which VDEC
 *   instance is set. After VIDIOC_STREAMON, V4L2_CID_EXT_VDEC_FREEZE_MODE can be
 *   called. When Freeze Mode is On, decoding should continue to operate in
 *   decoding mode, and the decoded picture is dropped and the picture displayed
 *   before the freeze mode is maintained. When a picture is dropped, it is
 *   necessary to prevent video stop symptom at the time of releasing the freeze
 *   mode by referring to DTS or PTS. DTS is information about the time when a
 *   frame is to be decoded. It is a value to operate so that the corresponding
 *   frame can be decoded when STC reaches DTS. When the corresponding control ID
 *   is called, the value set to value can be 0 or 1, 1 means On, 0 means Off.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_FREEZE_MODE
 *
 *     //
 *     // control value
 *     //
 *     0: Disable freeze mode, 1:Enable freeze mode
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_FREEZE_MODE;
 *      ctrl_arg.value = 1;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_FREEZE_MODE (V4L2_CID_EXT_VDEC_BASE + 9)

#define V4L2_CID_EXT_VDEC_DECODER_VERSION (V4L2_CID_EXT_VDEC_BASE + 10)
#define V4L2_CID_EXT_VDEC_KR_DUAL_3D_MODE \
    (V4L2_CID_EXT_VDEC_BASE + 11) // Deprecated

/**
 * @brief Control displaying Video output
 *
 * @rst
 * Functional Requirements
 *   It is a control ID that turns on / off STC Mode for fd in which VDEC instance
 *   is set. Before VIDIOC_STREAMON, V4L2_CID_EXT_VDEC_STC_MODE can be called. Set
 *   whether to use the STC generated based on the PCR in the demux as the
 *   reference value of AV sync logic and decode time. The values set in the value
 *   of the control ID can be 0 and 1, 1 means On, 0 means Off. The default value
 *   is 1, which is the On state.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_STC_MODE
 *
 *     //
 *     // control value
 *     //
 *     // 0: Off, 1:On
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_STC_MODE;
 *      ctrl_arg.value = 0;//Off
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_STC_MODE (V4L2_CID_EXT_VDEC_BASE + 12)

/**
 * @brief Set the audio port for AV sync logic
 *
 * @rst
 * Functional Requirements
 *   It is a control ID for setting an audio channel to be used as an audio master
 *   for fd in which VDEC instance is set. Before VIDIOC_STREAMON,
 *   V4L2_CID_EXT_VDEC_AUDIO_CHANNEL can be called. It is used to set the audio
 *   master of a specific ADEC channel to be used as a reference of AV sync logic.
 *   The value set in the value of the control ID is the number of the ADEC
 *   channel, and can have a value from 0 to the number of ADECs supported by the
 *   driver - 1 '.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_AUDIO_CHANNEL
 *
 *     //
 *     // control value
 *     //
 *     0~N (Audio Port)
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_AUDIO_CHANNEL;
 *      ctrl_arg.value = 0;//Audio channel
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_AUDIO_CHANNEL (V4L2_CID_EXT_VDEC_BASE + 13)

/**
 * @brief Set the displaying delay
 *
 * @rst
 * Functional Requirements
 *   It is a control ID for setting the display delay for the fd in which the VDEC
 *   instance is set or checking the total display delay set.
 *   After VDEC instance is opened, before VIDIOC_STREAMON is invoked,
 *   V4L2_CID_EXT_VDEC_DISPLAY_DELAY is invoked once. so, the display delay
 *   setting should be kept even after being invoked VIDIOC_STREAMOFF.
 *   When this CID is invoked using VIDIOC_S_CTRL, driver should be delay the
 *   delivery of picture data to VSC by adding delay in units of msec in the AV
 *   sync logic. In this time, the additional delay should not be repeatedly
 *   added with the corresponding Control ID call. Only the display delay which
 *   is setting lastly is applied.
 *   When this CID is invoked using VIDIOC_G_CTRL, driver should return total
 *   display delay set on 'value'.
 *   When this CID is invoked using VIDIOC_S_CTRL, the value set in 'value' is
 *   the display delay value in msec. When this CID is invoked using
 *   VIDIOC_G_CTRL, the delay value in 'value' must be set to msec.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_DISPLAY_DELAY
 *
 *     //
 *     // control value
 *     //
 *
 *     // 0~N (ms)
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_DISPLAY_DELAY;
 *      ctrl_arg.value = 50;//50ms
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DISPLAY_DELAY (V4L2_CID_EXT_VDEC_BASE + 14)

/**
 * @rst
 * Functional Requirements
 *     This is the control ID that sets the Lipsync master for the fd where VDEC
 *   instance is set. Before VIDIOC_STREAMON, V4L2_CID_EXT_VDEC_LIPSYNC_MASTER can
 *   be called. It is used to set whether to use ADEC master or VDEC master for
 *   video sync logic operation. The value to be set to value when calling the
 *   corresponding control ID can be 0 ~ 2, 0 means no lipsync master, 1 means use
 *   ADEC master, 2 means use VDEC master. The default value is 0.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_LIPSYNC_MASTER
 *
 *     //
 *     // control value
 *     //
 *     0  Use Demux(PCR), Default
 *     1  ADEC master
 *     2  VDEC master
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_LIPSYNC_MASTER;
 *      ctrl_arg.value = 1; //Audio master
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_LIPSYNC_MASTER (V4L2_CID_EXT_VDEC_BASE + 15)

/**
 * @rst
 * Functional Requirements
 *   It is the control ID that sets the AV sync threshold for fd which VDEC
 *   instance is set. Before VIDIOC_STREAMON, V4L2_CID_EXT_VDEC_VSYNC_THRESHOLD
 *   can be called. In AV sync logic, it is called to set the reference value for
 *   Freerun operation. The default value is 5000, 5 seconds in msec. The value
 *   set in the value of the control ID call is set to the AV sync threshold value
 *   in msec. (Ex : 5sec: 5000, 3sec : 3000 )
 *
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_VSYNC_THRESHOLD
 *
 *     //
 *     // control value
 *     //
 *     0~N (VSync Threashold)
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_VSYNC_THRESHOLD;
 *      ctrl_arg.value = 5000; //max 5s
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_VSYNC_THRESHOLD (V4L2_CID_EXT_VDEC_BASE + 16)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID that turns on / off PVR mode for fd in which VDEC instance
 *   is set. Before VIDIOC_STREAMON, V4L2_CID_EXT_VDEC_PVR_MODE can be called.  It
 *   is set to notify that VDEC is used for PVR application. At this time, VDEC
 *   should be set to match the PVR operation. The values set in the value of the
 *   control ID can be 0 and 1, 1 means On, 0 means Off. The default value is 0,
 *   which is Off.
 *
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_PVR_MODE
 *
 *     //
 *     // control value
 *     //
 *     0: Off, 1: On
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_PVR_MODE;
 *      ctrl_arg.value = 1; //PVR mode on
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_PVR_MODE (V4L2_CID_EXT_VDEC_BASE + 17)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID that turns on / off Fast I Frame mode for fd in which VDEC
 *   instance is set. Before VIDIOC_STREAMON, V4L2_CID_EXT_VDEC_FAST_IFRAME_MODE
 *   can be called. It is set to notify that VDEC is used for supporting specific
 *   SO(System Operator) channel.
 *   The values set in the value of the
 *   control ID can be 0 and 1, 1 means On, 0 means Off. The default value is 0,
 *   which is Off.
 *   If Fast I frame mode set On, after invoking VIDIOC_STREAMON, only the first
 *   I frame immediately transfers picture data to VSC without waiting that STC
 *   becomes equal to PTS by following AV sync logic.
 *   By enabling this feature, customers can enjoy seeing earlier the video of
 *   the next channel but the early video will usually keep to be frozen for a
 *   while.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_FAST_IFRAME_MODE
 *
 *     //
 *     // control value
 *     //
 *     0: Off, 1: On
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_FAST_IFRAME_MODE;
 *      ctrl_arg.value = 1; //On : 1, Off : 0
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_FAST_IFRAME_MODE (V4L2_CID_EXT_VDEC_BASE + 18)

/**
 * @rst
 * Functional Requirements
 *   It is the control ID that sets the type for the HFR channel for the fd in
 *   which the VDEC instance is set.
 *
 *   Before :c:func:`v4l-dvb-apis:VIDIOC_STREAMON`, V4L2_CID_EXT_VDEC_HFR_TYPE can
 *   be called. HFR (High Frame Rate) is a function to support frame rate up to
 *   120Hz for sharper and smoother image. The corresponding control ID should be
 *   set and called before the ioctl VIDIOC_STREAMON, and should be set to 0,
 *   which is the default value if not invoked. It should also be reset to the
 *   default value after the ioctl :c:func:`v4l-dvb-apis:VIDIOC_STREAMOFF` call.
 *
 *   There are HFR 1PID stream and HFR 2PID stream. In addition, since the SI
 *   information of HFR stream is not well configured, it is possible to need to do
 *   auto-detect & setting operation where the resolution or the frame rate is
 *   unclear.
 *
 *   ES data of HFR stream is divided into BL (Base Layer) and EL (Enhence layer).
 *   if the PID of the EL & BL is different, than it is called HFR 2PID. and, if
 *   the PID of the EL & BL is the same, than it is called HFR 1PID.
 *
 *   When the control ID is called, the value can be set to 0 ~ 4. The default
 *   value is 0, meaning SFR. The meanings of the remaining values are shown in
 *   the table below. If decoder performance cannot support for each setting, it
 *   should be failed.
 *
 *   For HFR 2PID (0x02, 0x03), UHD HFR 1PID (0x04), the 60Hz model should return
 *   fail. In the case of the HFR 2PID case, VDEC element set only the Main PID,
 *   and the VDEC driver should decode only the Main PID.
 *
 *   In the case of UHD 1PID with temporal scalability case, VDEC element is set
 *   to the next higher layer with :c:macro:`V4L2_CID_EXT_VDEC_TEMPORAL_ID_MAX`,
 *   the driver should drop the top layer and decode it to the others layer.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_HFR_TYPE
 *
 *     //
 *     // control value
 *     //
 *
 *   +------------------------------+-------+-----------------------------------------------------+
 *   | Type                         | Value | Description                                         |
 *   +==============================+=======+=====================================================+
 *   | SFR(Default)                 | 0x00  | | Equivalent to HEVC channel operation              |
 *   |                              |       | | before introduction of HFR function               |
 *   +------------------------------+-------+-----------------------------------------------------+
 *   | | SFR/HFR unclear or         | 0x01  | | Don't need to support SFR / HFR seamless change.  |
 *   | | HFR & Resolution unclear   |       | | Driver need to support HFR auto detect & setting. |
 *   +------------------------------+-------+-----------------------------------------------------+
 *   | UHD HFR 2PID                 | 0x02  | | Don't need HFR auto detect & setting.             |
 *   |                              |       | | need to support SFR / HFR seamless change.        |
 *   +------------------------------+-------+-----------------------------------------------------+
 *   | | HFR 2PID,                  | 0x03  | | Don't need to support SFR / HFR seamless change.  |
 *   | | Resolution unclear         |       | | Driver need to support HFR auto detect & setting. |
 *   +------------------------------+-------+-----------------------------------------------------+
 *   | UHD HFR 1PID                 | 0x04  | | Don't need HFR auto detect & setting.             |
 *   |                              |       | | If the stream have temporal scalability,          |
 *   |                              |       | | need to support SFR / HFR seamless change.        |
 *   +------------------------------+-------+-----------------------------------------------------+
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_HFR_TYPE;
 *      ctrl_arg.value = 0; //SFR , Default value
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_HFR_TYPE (V4L2_CID_EXT_VDEC_BASE + 19)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID that sets Temporal_id_max value for fd where VDEC instance
 *   is set. Before VIDIOC_STREAMON, V4L2_CID_EXT_VDEC_TEMPORAL_ID_MAX can be
 *   called. Frames with a layer higher than Temporal_id_max should be dropped
 *   before decoding. Each frame of the ES stream can be layered and the entire
 *   image can be constructed so that it is decoded as a reference to a frame
 *   belonging to itself or to its subordinate, where the value of the highest
 *   layer is temporal_id_max. When calling the corresponding control ID, the
 *   value can be a value between -1 and 6, and the default value is -1. -1 value
 *   mean 'not set'. Other values mean temporal_id_max value.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_TEMPORAL_ID_MAX
 *
 *     //
 *     // control value
 *     //
 *     -1 (Default), Not set
 *     value range: -1~6
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and this
 *   control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and this
 *   control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_TEMPORAL_ID_MAX;
 *      ctrl_arg.value = 0; //Temporal ID Max is 0
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_TEMPORAL_ID_MAX (V4L2_CID_EXT_VDEC_BASE + 20)

/**
 * @brief Set Direct Mode
 *
 * @deprecated
 *  Deprecated since webOS 5.0, it will be removed from webOS 25.
 *
 * @rst
 * Functional Requirements
 *   It is a control ID that sets Direct Mode for fd in which VDEC instance is
 *   set. In case of holding ES data or obtaining ES data through another path,
 *   the mode can be changed to one that can directly input. The value set to the
 *   value of the control ID call is "Don't care".
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_DIRECT_MODE
 *
 *     //
 *     // control value
 *     //
 *
 *     // Don't care
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_DIRECT_MODE;
 *      ctrl_arg.value = 1; //Don't care
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DIRECT_MODE (V4L2_CID_EXT_VDEC_BASE + 21) // Deprecated CID

/**
 * @rst
 * Functional Requirements
 *   Value of V4L2_CID_EXT_VDEC_DRIPDEC_MODE indicates the decoding status. 0 is
 *   the default. 0 means decoder should decode all frames(I/B/P frames). 1 means
 *   decoder should decoder I-Frame only. VIDIOC_S_FMT must be set before
 *   V4L2_CID_EXT_VDEC_DRIPDEC_MODE setting.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *     VIDIOC_G_CTRL       // Get
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_DRIPDEC_MODE
 *
 *     //
 *     // control value
 *     //
 *     0 = Default, non-Drip Decoding mode
 *     1 =  Drip Decoding mode
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_DRIPDEC_MODE;
 *      ctrl_arg.value = 1; // Decoding I frame only.
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DRIPDEC_MODE \
    (V4L2_CID_EXT_VDEC_BASE + 22) // To support MHEG certification

/**
 * @rst
 * Functional Requirements
 *   This command is used to tell VDEC to update ECP related information. The
 *   ioctl is only called, and there is no information passed by REE. Effective
 *   information is managed by TEE. Therefore, communication with TEE is required.
 *   Calls V4L2_CID_EXT_VDEC_ECP_INFO_NOTI after VIDIOC_S_FMT is called.
 *   VIDIOC_STREAMON Ensures that Decoder can check whether ECP mode is applied
 *   before calling. This is because a coded picture buffer (CPB) is allocated
 *   after VIDIOC_STREAMON.  If V4L2_CID_EXT_VDEC_CHANNEL is not set in fd, it
 *   returns error. In case of VIDIOC_STREAMOFF, it is ECP Protection off to
 *   restore to default.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDEC_ECP_INFO_NOTI
 *
 *     //
 *     // control value
 *     //
 *
 *     // Don't care
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
 *   Application can set data using :c:func:`v4l-dvb-apis:VIDIOC_S_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_ECP_INFO_NOTI;
 *      ctrl_arg.value = 0;
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_ECP_INFO_NOTI \
    (V4L2_CID_EXT_VDEC_BASE + 23) // To support DVB - ECP set

/**
 * @rst
 * Functional Requirements
 *   It is a command to receive Offset of ECP processed CPB. The default value is
 *   0, which is the return of the ECP Off case.
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
 *     V4L2_CID_EXT_VDEC_ECP_OFFSET
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
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_ECP_OFFSET;
 *      ctrl_arg.value = 0;
 *
 *      ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_ECP_OFFSET \
    (V4L2_CID_EXT_VDEC_BASE + 24) // To support DVB - ECP get

/**
 * @rst
 * Functional Requirements
 *   It is a command to receive Size of ECP processed CPB. The default value is 0,
 *   which is the return of the ECP Off case.
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
 *     V4L2_CID_EXT_VDEC_ECP_SIZE
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
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_CTRL` and
 *   this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      ctrl_arg.id = V4L2_CID_EXT_VDEC_ECP_SIZE;
 *      ctrl_arg.value = 0;
 *
 *      ioctl(fd, VIDIOC_G_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_ECP_SIZE \
    (V4L2_CID_EXT_VDEC_BASE + 25) // To support DVB - ECP get

/* VDEC class EXT control IDs */

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for receiving Userdata parsed by the driver from the
 *   driver when a Userdata event occurs for fd in which VDEC instance is set.
 *
 *   Userdata refers to 603 type closed caption, rating data, DVS 157 type closed
 *   caption data, and rating data. User data event occurs when there is
 *   corresponding data in ES data entered in VDEC drvier. When the Userdata event
 *   is registered with the ioctl VIDIOC_SUBSCRIBE_EVENT, the VDEC driver shall
 *   record the occurrence of the event in the event queue and manage the event
 *   occurrence information to check the occurrence of the event through the ioctl
 *   DQEVENT.
 *
 *   Also, userdata should be managed in a separate space so that userdata for the
 *   event can be taken with ioctl :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` . If
 *   the userdata in the VDEC element is copied to the ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`, the corresponding data can be
 *   discarded.
 *
 *   When a Userdata event occurs, the size of userdata must be stored by using 4
 *   bytes of the data array of struct v4l2_event. At the same time, picType,
 *   isRepeatFieldFirst, isTopFieldFirst, temporalReference, and pts should be
 *   uploaded using the data array of struct v4l2_event. Based on this, the VDEC
 *   element allocate a memory space and calls ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`.
 *
 *   If a userdata event is detected by calling ioctl DQEVENT on the VDEC
 *   instance, allocate memory space to take userdata, and set size and ptr to
 *   call ioctl :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`. The VDEC driver must
 *   copy userdata to the memory space pointed to by ptr and return it. When
 *   calling the corresponding control ID, the value set to size is the size of
 *   the memory space, and the value set in ptr is the memory space address of the
 *   user space.
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
 *     V4L2_CID_EXT_VDEC_USER_EVENT_DATA
 *
 *     //
 *     // Parameters
 *     //
 *     struct v4l2_event {
 *      __u32 type;                          //Type of the event
 *
 *      union {
 *         struct v4l2_event_vsync vsync;
 *         struct v4l2_event_ctrl ctrl;
 *         struct v4l2_event_frame_sync frame_sync;
 *         struct v4l2_event_motion_det motion_det;
 *         struct v4l2_event_src_change src_change;
 *         __u8 data[64];                  // Userdata event case
 *                                         // data[0] ~ data[3] : Userdata size
 *                                         // data[4] : Picture type (I Picture : 1, P Picture : 2, B Picture : 3)
 *                                         // data[5] : Repeat Field First (Yes : 1, No : 0)
 *                                         // data[6] : Top Field First (Yes : 1, No : 0)
 *                                         // data[7] : Temporal reference of the picture
 *                                         // data[8] ~ data[11] : PTS
 *      } u;
 *      __u32 pending;                     //Number of pending events excluding this one.
 *      __u32 sequence;                    //Event sequence number.
 *      struct timespec timestamp;         //Event timestamp.
 *      __u32 id;                          //The ID associated with the event source.
 *      __u32 reserved[8];                 //Reserved for future extensions.
 *     };
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
 *      pollfd poll_fd;
 *      struct v4l2_event evt_arg;
 *
 *      typedef struct {
 *          uint8_t     picType;            //Picture type (I Picture : 1, P Picture : 2, B Picture : 3)
 *          uint8_t     isRepeatFieldFirst; //Repeat Field First (Yes : 1, No : 0)
 *          uint8_t     isTopFieldFirst;    //Top Field First (Yes : 1, No : 0)
 *          uint8_t     temporalReference;  //Temporal reference of the picture
 *          uint32_t    pts;
 *          void        *pUserdata;
 *          int32_t     size;               //Userdata size
 *      } USERDATA_EVENT_T;
 *
 *      while(1) {
 *         poll_fd.fd = fd;
 *         poll_fd.event = POLLPRI; // POLLPRI is defined in linux spec
 *         poll_fd.revents = 0;
 *         while(0 < poll(&poll_fd, 1, 50)) {
 *            ioctl(fd, VIDIOC_DQEVENT, &evt_arg);
 *
 *
 *            if(V4L2_SUB_EXT_VDEC_USERDATA == evt_arg.id) {
 *               struct v4l2_ext_controls ext_ctrls_arg;
 *               struct v4l2_ext_control ext_ctrl_arg;
 *               USERDATA_EVENT_T userdataInfo = {0, };
 *
 *               ext_ctrls_arg.count = 1;
 *               ext_ctrls_arg.controls = &ext_ctrl_arg;
 *
 *               memcpy(&userdataInfo.size, &evt_arg.u.data[0], 4);
 *               memcpy(&userdataInfo.picType, &evt_arg.u.data[4], 1);
 *               memcpy(&userdataInfo.isRepeatFieldFirst, &evt_arg.u.data[5], 1);
 *               memcpy(&userdataInfo.isTopFieldFirst, &evt_arg.u.data[6], 1);
 *               memcpy(&userdataInfo.temporalReference, &evt_arg.u.data[7], 1);
 *               memcpy(&userdataInfo.pts, &evt_arg.u.data[8], 4);
 *
 *               userdataInfo.pUserdata = (void *)malloc(userdataInfo.size);
 *
 *               ext_ctrl_arg.id = V4L2_CID_EXT_VDEC_USER_EVENT_DATA;
 *               ext_ctrl_arg.size = userdataInfo.size;
 *               ext_ctrl_arg.ptr = userdataInfo.pUserdata;
 *
 *               ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 *
 *               //send userdata from userdata_ptr to subtitle module.
 *
 *               free(userdataInfo.pUserdata);
 *            }
 *
 *
 *            if(0 == event_arg.pending) {
 *               break;
 *            }
 *         }
 *      }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_USER_EVENT_DATA (V4L2_CID_EXT_VDEC_BASE + 101)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for receiving Picture info data from the driver when a
 *   Picture info event occurs for fd in which VDEC instance is set. Picture info
 *   event is an event that takes place when VSC takes picture data through VDO.
 *
 *   It is an event to register information related to picture delivered at VDEC
 *   element from VDEC element. The VDEC driver should record the event occurrence
 *   in the event queue after registering the Picture info event and manage the
 *   event occurrence information to check the occurrence of the event through
 *   ioctl DQEVENT.
 *
 *   Also, Picture info data should be managed in a separate space so that Picture
 *   info data for the event can be taken with ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`. If the Picture info data in the
 *   VDEC element is moved to the ioctl :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`,
 *   the corresponding data can be discarded.
 *
 *   If a picture info event is detected by calling ioctl DQEVENT on the VDEC
 *   instance, allocate memory space to take picture info data, and set size and
 *   ptr to call ioctl :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` . The VDEC driver
 *   must copy picture info data to the memory space pointed to by ptr and return
 *   it. When calling the corresponding control ID, the value set to size is the
 *   size of the memory space, and the value set in ptr is the memory space
 *   address of the user space.
 *
 *   Picture info event is an event that occurs when VSC takes picture data
 *   through VDO if picture info data is different from previous picture info.
 *   Because VDEC MW should get Picture info from VDEC driver, Picture info event
 *   is registered to VDEC driver.
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
 *     V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA
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
 *      pollfd poll_fd;
 *      struct v4l2_event evt_arg;
 *
 *      struct v4l2_ext_picinfo_msg picinfo_msg;
 *
 *      while(1) {
 *         poll_fd.fd = fd;
 *         poll_fd.event = POLLPRI; //POLLPRI is defined in linux spec
 *         poll_fd.revent = 0;
 *         while(0 < poll(&poll_fd, 1, 50)) {
 *            ioctl(fd, VIDIOC_DQEVENT, &evt_arg);
 *
 *
 *            if(V4L2_SUB_EXT_VDEC_PICINFO == evt_arg.id) {
 *               struct v4l2_ext_controls ext_ctrls_arg;
 *               struct v4l2_ext_control ext_ctrl_arg;
 *
 *               ext_ctrls_arg.count = 1;
 *               ext_ctrls_arg.controls = &ext_ctrl_arg;
 *
 *               ext_ctrl_arg.id = V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA;
 *               ext_ctrl_arg.size = sizeof(struct v4l2_ext_picinfo_msg);
 *               ext_ctrl_arg.ptr = &picinfo_msg;
 *
 *               ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 *
 *               //update picinfo data
 *            }
 *
 *            if(0 == event_arg.pending) {
 *               break;
 *            }
 *         }
 *      }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA (V4L2_CID_EXT_VDEC_BASE + 102)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID to obtain the decoder status to obtain the current state
 *   of the VDEC decoder driver for the fd in which the VDEC instance is set. When
 *   calling the corresponding control ID, set it in the
 *   :cpp:any:`v4l2_ext_decoder_status` structure that returns the state value of
 *   the driver and return it.
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
 *     V4L2_CID_EXT_VDEC_DECODER_STATUS
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
 *      struct v4l2_ext_controls ext_ctrls_arg;
 *      struct v4l2_ext_control ext_ctrl_arg;
 *      struct v4l2_ext_decoder_status decoder_status;
 *
 *      ext_ctrls_arg.count = 1;
 *      ext_ctrls_arg.controls = &ext_ctrl_arg;
 *
 *      ext_ctrl_arg.id = V4L2_CID_EXT_VDEC_DECODER_STATUS;
 *      ext_ctrl_arg.size = sizeof(struct v4l2_ext_decoder_status);
 *      ext_ctrl_arg.ptr = &decoder_status;
 *
 *      ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 *
 * See also
 *   - :cpp:any:`v4l2_ext_decoder_status`
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DECODER_STATUS (V4L2_CID_EXT_VDEC_BASE + 103)

/**
 * @brief Get current decoding stream info
 *
 * @deprecated
 *  Deprecated since webOS 5.0, it will be removed from webOS 24.
 *
 *  V4L2_CID_EXT_VDEC_STREAM_INFO is replaced to V4L2_CID_EXT_VDEC_VIDEO_INFO.
 *
 * @rst
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
 *     V4L2_CID_EXT_VDEC_STREAM_INFO
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
 *      struct v4l2_ext_controls ext_ctrls_arg;
 *      struct v4l2_ext_control ext_ctrl_arg;
 *      struct v4l2_ext_stream_info ext_stream_info;
 *
 *      ext_ctrls_arg.count = 1;
 *      ext_ctrls_arg.controls = &ext_ctrl_arg;
 *
 *      ext_ctrl_arg.id = V4L2_CID_EXT_VDEC_STREAM_INFO;
 *      ext_ctrl_arg.size = sizeof(struct v4l2_ext_stream_info);
 *      ext_ctrl_arg.ptr = &ext_stream_info;
 *
 *      ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_STREAM_INFO (V4L2_CID_EXT_VDEC_BASE + 104) // Deprecated CID

/**
 * @brief Feed ES data
 *
 * @deprecated
 *  Deprecated since webOS 5.0, it will be removed from webOS 25.
 *
 * @rst
 * Functional Requirements
 *   It is the control ID that is to directly feed ES data on the fd that is set
 *   with VDEC instance. It can be run in Direct Mode, and Direct Mode changes
 *   through the call of V4L2_CID_EXT_VDEC_DIRECT_MODE. When calling the control
 *   ID, put the size of ES data and OFFSET value to size and ptr.
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
 *     V4L2_CID_EXT_VDEC_DIRECT_ESDATA
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
 *      struct v4l2_ext_controls ext_ctrls_arg;
 *      struct v4l2_ext_control ext_ctrl_arg;
 *
 *      ext_ctrls_arg.count = 1;
 *      ext_ctrls_arg.controls = &ext_ctrl_arg;
 *
 *      struct v4l2_format format_arg = {0, };
 *
 *      format_arg.fmt.pix.pixelformat = v4l2_fourcc('H', 'E', 'V', 'C'); //HEVC codec type setting
 *
 *      ioctl(fd, VIDIOC_S_FMT, &format_arg);
 *
 *      int type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
 *      ioctl(fd, VIDIOC_STREAMON, &type); // Ready for feeding
 *
 *      ext_ctrl_arg.id = V4L2_CID_EXT_VDEC_DIRECT_ESDATA;
 *
 *      ext_ctrl_arg.size = SIZE4DATA;
 *      ext_ctrl_arg.ptr = OFFSET4DATA;
 *
 *      ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_ctrls_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DIRECT_ESDATA (V4L2_CID_EXT_VDEC_BASE + 105) // Deprecated CID

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for obtaining video information of the current image with
 *   respect to fd in which VDEC instance is set. After VIDIOC_STREAMON,
 *   V4L2_CID_EXT_VDEC_VIDEO_INFO will be called. In VDEC MW, the
 *   v4l2_ext_vdec_video_info ENUM value corresponding to the video info to be
 *   checked in the 'value' value is set and the
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` is called. Therefore, the
 *   corresponding video info should be set to 'value' and returned. Please
 *   refrain from BSP implementation before Linuxtv-ext-header CCC is completed on
 *   JCL4TV and internal review.
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
 *     V4L2_CID_EXT_VDEC_VIDEO_INFO
 *
 *     //
 *     // control value
 *     //
 *
 *   See :cpp:enum:`v4l2_ext_vdec_video_info`
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
 *      struct v4l2_ext_controls ext_ctrls_arg = {0, };
 *      struct v4l2_ext_control ext_ctrl_cid   = {0, };
 *      struct v4l2_control get_param;
 *
 *      memset(&ext_ctrls_arg , 0, sizeof(struct v4l2_ext_controls));
 *      memset(&ext_ctrl_cid   ,  0, sizeof(struct v4l2_ext_control));
 *      memset(&get_param,    0, sizeof(struct v4l2_control));
 *
 *      ext_ctrls_arg.count = 1
 *      ext_ctrls_arg.controls = &ext_ctrl_cid;
 *
 *      ext_ctrl_arg.id = V4L2_CID_EXT_VDEC_VIDEO_INFO;
 *      ext_ctrl_arg.size = sizeof(struct v4l2_control);
 *      ext_ctrl_arg.ptr = &get_param;
 *      get_param.id = VDEC_PROGRESSIVE_SEQUENCE;
 *      get_param.value = 0; //initialize
 *
 *      ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg );
 *
 *      int frame_rate = get_param.value;
 *
 *  See also
 *    - :cpp:enum:`v4l2_ext_vdec_video_info`
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_VIDEO_INFO (V4L2_CID_EXT_VDEC_BASE + 106)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for receiving Picture info data from the driver when a
 *   Picture info event occurs for fd in which VDEC instance is set. Picture info
 *   event is an event that takes place when VSC takes picture data through VDO.
 *   It is an event to register information related to picture delivered at VDEC
 *   element from VDEC element. The VDEC driver should record the event occurrence
 *   in the event queue after registering the Picture info event and manage the
 *   event occurrence information to check the occurrence of the event through
 *   ioctl DQEVENT. Also, Picture info data should be managed in a separate space
 *   so that Picture info data for the event can be taken with ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` . If the Picture info data in the
 *   VDEC element is moved to the ioctl :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`
 *   , the corresponding data can be discarded. If a picture info event is
 *   detected by calling ioctl DQEVENT on the VDEC instance, allocate memory space
 *   to take picture info data, and set size and ptr to call ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` . The VDEC driver must copy picture
 *   info data to the memory space pointed to by ptr and return it. When calling
 *   the corresponding control ID, the value set to size is the size of the memory
 *   space, and the value set in ptr is the memory space address of the user
 *   space.
 *
 *   Picture info event is an event that occurs when VSC takes picture data
 *   through VDO if picture info data is different from previous picture info.
 *   Because VDEC MW should get Picture info from VDEC driver, Picture info event
 *   is registered to VDEC driver.
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
 *     V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA_EXT
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
 *      pollfd poll_fd;
 *      struct v4l2_event evt_arg;
 *
 *      struct v4l2_ext_picinfo_msg_ext picinfo_msg;
 *
 *      while(1) {
 *         poll_fd.fd = fd;
 *         poll_fd.event = POLLPRI; //POLLPRI is defined in linux spec
 *         poll_fd.revent = 0;
 *         while(0 < poll(&poll_fd, 1, 50)) {
 *            ioctl(fd, VIDIOC_DQEVENT, &evt_arg);
 *
 *
 *            if(V4L2_SUB_EXT_VDEC_PICINFO == evt_arg.id) {
 *               struct v4l2_ext_controls ext_ctrls_arg;
 *               struct v4l2_ext_control ext_ctrl_arg;
 *
 *               ext_ctrls_arg.count = 1;
 *               ext_ctrls_arg.controls = &ext_ctrl_arg;
 *
 *               ext_ctrl_arg.id = V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA_EXT;
 *               ext_ctrl_arg.size = sizeof(struct v4l2_ext_picinfo_msg);
 *               ext_ctrl_arg.ptr = &picinfo_msg;
 *
 *               ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 *
 *               //update picinfo data
 *            }
 *
 *            if(0 == event_arg.pending) {
 *               break;
 *            }
 *         }
 *      }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA_EXT \
    (V4L2_CID_EXT_VDEC_BASE + 107) // To support HFR, frame rate fraction type
                                   // structure is added. and useless member
                                   // variable is deleted.

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for receiving Picture info data from the driver when a
 *   Picture info event occurs for fd in which VDEC instance is set. Picture info
 *   event is an event that takes place when VSC takes picture data through VDO.
 *   It is an event to register information related to picture delivered at VDEC
 *   element from VDEC element. The VDEC driver should record the event occurrence
 *   in the event queue after registering the Picture info event and manage the
 *   event occurrence information to check the occurrence of the event through
 *   ioctl DQEVENT. Also, Picture info data should be managed in a separate space
 *   so that Picture info data for the event can be taken with ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` . If the Picture info data in the
 *   VDEC element is moved to the ioctl :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`
 *   , the corresponding data can be discarded. If a picture info event is
 *   detected by calling ioctl DQEVENT on the VDEC instance, allocate memory space
 *   to take picture info data, and set size and ptr to call ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` . The VDEC driver must copy picture
 *   info data to the memory space pointed to by ptr and return it. When calling
 *   the corresponding control ID, the value set to size is the size of the memory
 *   space, and the value set in ptr is the memory space address of the user
 *   space.
 *
 *   Picture info event is an event that occurs when VSC takes picture data
 *   through VDO if picture info data is different from previous picture info.
 *   Because VDEC MW should get Picture info from VDEC driver, Picture info event
 *   is registered to VDEC driver.
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
 *     V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA_EXT
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
 *      pollfd poll_fd;
 *      struct v4l2_event evt_arg;
 *
 *      struct v4l2_ext_picinfo_msg_ext picinfo_msg;
 *
 *      while(1) {
 *         poll_fd.fd = fd;
 *         poll_fd.event = POLLPRI; //POLLPRI is defined in linux spec
 *         poll_fd.revent = 0;
 *         while(0 < poll(&poll_fd, 1, 50)) {
 *            ioctl(fd, VIDIOC_DQEVENT, &evt_arg);
 *
 *
 *            if(V4L2_SUB_EXT_VDEC_PICINFO == evt_arg.id) {
 *               struct v4l2_ext_controls ext_ctrls_arg;
 *               struct v4l2_ext_control ext_ctrl_arg;
 *
 *               ext_ctrls_arg.count = 1;
 *               ext_ctrls_arg.controls = &ext_ctrl_arg;
 *
 *               ext_ctrl_arg.id = V4L2_CID_EXT_VDEC_PICINFO_EVENT_DATA_EXT;
 *               ext_ctrl_arg.size = sizeof(struct v4l2_ext_picinfo_msg_ext);
 *               ext_ctrl_arg.ptr = &picinfo_msg;
 *
 *               ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 *
 *               //update picinfo data
 *            }
 *
 *            if(0 == event_arg.pending) {
 *               break;
 *            }
 *         }
 *      }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DRIPDEC_PICTURE \
    (V4L2_CID_EXT_VDEC_BASE +             \
     108) // To support MHEG certification, Pass I-frame buffer information

/**
 * @rst
 * Functional Requirements
 *   In the case when this ioctl is used for set,
 *   the moment when a Video Frame whose PTS is larger or same with the PTS given
 *   by LGE mw is displayed on TV Screen. The Video Frame is freezed on TV Screen.
 *   Enable or Disable the Hash/CRC generation whenever the FrameType Event occurs.
 *   In the case when this ioctl is used for get,
 *   this API returns the information whether the VDEC is frozen or not,
 *   if the VDEC is currently frozen,
 *   it also returns a hash value of the frozen video frame.
 *   The hash value should be so unique that it can represent the video pattern
 *   of the frozen video frame.
 *   The best algorithm should be found by Soc vendor.
 *   For example, the value can be calculated by simply summing all pixel values of one frozen video frame
 *   or it can be CRC value of one frozen video frame.
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
 *     V4L2_CID_EXT_VDEC_DECODED_PICTURE_BUFFER
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
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_S_EXT_CTRLS`
 *   and this control id.
 *   Application can get data using :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_decoded_picture_buffer{
 *         __u32 command;    // control commands for VDEC Decoded Picture Buffer
 *                           // 0: Unfreeze the frozen VDEC
 *                           // 1: Freeze VDEC based on target PTS and Generate Hash/CRC
 *                           // 3: Enable  the Hash/CRC generation whenever the
 *                           //    PictureType event occurs
 *                           // 0: Disable the Hash/CRC generation whenever the
 *                           //    PcitureType event occurs
 *         __u64 target_pts; // 33 bits target PTS
 *         __u32 bFrozen;    // current VDEC is frozen or not
 *         __u32 hashValue;  // unique value which represents the video
 *                           // pattern of the frozen video frame
 *     };
 *
 *      int LGE_API_IsVdecFrozen( int *bFrozen, int *pHash)
 *      {
 *          int rc;
 *
 *          struct v4l2_ext_decoded_picture_buffer vdecCont      = {0, };
 *          struct v4l2_ext_controls               ext_ctrls_arg = {0,};
 *          struct v4l2_ext_control                ext_ctrl_arg  = {0,};
 *
 *          ext_ctrls_arg.count    = 1;
 *          ext_ctrls_arg.controls = &ext_ctrl_arg;
 *
 *          ext_ctrl_arg.id        = V4L2_CID_EXT_VDEC_DECODED_PICTURE_BUFFER;
 *          ext_ctrl_arg.size      = sizeof(v4l2_ext_decoded_picture_buffer);
 *          ext_ctrl_arg.ptr       = &vdecCont;
 *
 *          rc                     = ioctl(vdec_fd, VIDIOC_G_EXT_CTRLS, &ext_ctrls_arg);
 *          *bFrozen               = vdecCont.bFrozen;
 *          // If vdec is currently bFrozen,     *bFrozen = 1
 *          // If vdec is currently not bFrozen, *bFrozen = 0
 *
 *          *pHash                 = vdecCont.hashValue;
 *          // Hash value of the Video Frame
 *          printf("Hash value of this frame is %d \n", *pHash);
 *
 *          return rc;
 *      }
 *
 *      struct v4l2_ext_decoded_picture_buffer vdecCont = {0, };
 *      vdecCont.target_pts    = 0x12345...;
 *      vdecCont.command       = 1; // 0:UnFreeze(Melt), 1:Freeze
 *      ext_ctrl_arg.id        = V4L2_CID_EXT_VDEC_DECODED_PICTURE_BUFFER;
 *      ext_ctrls_arg.ptr      = &vdecCont;
 *
 *      rc                     = ioctl(vdec_fd, VIDIOC_S_EXT_CTRLS, &ext_ctrls_arg);
 *
 *      int bFreeze = 0;
 *      int HashVal = 0;
 *      while(1)
 *      {
 *          rc = LGE_API_IsVdecFreezed(&bFrozen, &HashVal);
 *          // About LGE_API_IsVdecFreezed, Refer to the abvoe description
 *          if (bFrozen == 1)
 *          {
 *              printf("Video Freeze occur !! HashVal=%d \n", HashVal);
 *
 *              // Method 1
 *              if (HashVal == TARGET_VALUE)
 *                  printf("Test is OK\n");
 *              else
 *                  printf("Test is NG\n");
 *
 *              // Method 2
 *              Testing mw captures the TV Screen and compare the captured
 *              video and the target Picture
 *              Judge current video is ok or not
 *
 *              // unfreeze the Video
 *              vdecCont.command = 0; // 0:UnFreeze(Melt), 1:Freeze
 *              rc = ioctl(vdec_fd, VIDIOC_S_EXT_CTRLS, &ext_ctrls_arg);
 *              break;
 *           }
 *           delay(100msec);
 *      }
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_DECODED_PICTURE_BUFFER (V4L2_CID_EXT_VDEC_BASE + 109)

/**
 * @rst
 * Functional Requirements
 *  Get video pts value of current decoded/displayed picture.
 *  Used only when a DTV stream is playing.
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
 *     V4L2_CID_EXT_VDEC_GET_PTS
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_picture_pts {
 *         unsigned int decoding_picture_pts;
 *         unsigned int display_picture_pts;
 *     };
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Video framedrop should not occur during get video pts
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
 *      struct v4l2_ext_controls ext_controls = {0};
 *      struct v4l2_ext_control ext_control = {0};
 *      struct v4l2_ext_picture_pts pts = {0};
 *
 *      ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_VDEC_GET_PTS;
 *      ext_controls.controls->size = sizeof(v4l2_ext_picture_pts);
 *      ext_controls.controls->ptr = (void *)(&pts);
 *
 *      ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDEC_GET_PTS (V4L2_CID_EXT_VDEC_BASE + 110)

/* VDEC class subscription types */
#define V4L2_EVENT_PRIVATE_EXT_VDEC_BASE (V4L2_EVENT_PRIVATE_START + 0x8000)

/**
 * @rst
 * Functional Requirements
 *   V4L2 Subscription Type for VDEC
 * @endrst
 */
#define V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT (V4L2_EVENT_PRIVATE_EXT_VDEC_BASE + 1)

/* VDEC class subscription event IDs */
#define V4L2_SUB_EXT_VDEC_BASE (0x8000)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for subscribing or unsubscribing Frame Type event for fd
 *   in which VDEC instance is set. Before VIDIOC_STREAMON,
 *   V4L2_SUB_EXT_VDEC_FRAME can be subscribed. Frame Type event is an event that
 *   occurs when frame decoding is completed in the VDEC decoder drvier. The Frame
 *   Type event is registered to take the information of the decoded frame to the
 *   VDEC element. The VDEC driver should record the event occurrence in the event
 *   queue after registering the Frame Type event, and should manage event
 *   occurrence information to check the occurrence of the event through ioctl
 *   DQEVENT. To retrieve the Frame Type data for the event, ioctl DQEVENT must
 *   return information about the picture type and PTS data in the u.data array of
 *   the v4l2_event structure. In the u.data[0], picture type data should be
 *   stored.(SeqHeader : 0, I Frame : 1, P Frame : 2, B Frame : 3). In the
 *   u.data[1] ~ u.data[5], PTS data should be stored.
 *
 *   The value set as the type when the corresponding control ID is called is
 *   registered as V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT which means VDEC related
 *   event.
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
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT, VIDIOC_UNSUBSCRIBE_EVENT // Get
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_event_subscription subscription_arg;
 *
 *      subscription_arg.type = V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT;
 *      subscription_arg.id = V4L2_SUB_EXT_VDEC_FRAME;
 *
 *      ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &subscription_arg); // Subscribe frame decoding event
 *
 *      ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &subscription_arg); // Unsubscribe frame decoding event
 *
 *      //When Frame Type event is occurred, in the event thread, Frame type info is detected.
 *      pollfd poll_fd;
 *      struct v4l2_event evt_arg;
 *
 *      while(1) {
 *         poll_fd.fd = fd;
 *         poll_fd.event = POLLPRI; //POLLPRI is defined in linux spec
 *         poll_fd.revent = 0;
 *
 *         while(0 < poll(&poll_fd, 1, 50)) {
 *            ioctl(fd, VIDIOC_DQEVENT, &evt_arg);
 *
 *
 *            if(V4L2_SUB_EXT_VDEC_FRAME == evt_arg.id) {
 *               uint32_t frame_type = evt_arg.u.data[0];
 *               uint64_t pts = 0;
 *
 *
 *               memcpy(&(evt_arg.u.data[1]), &pts, 5);
 *            }
 *
 *            if(0 == event_arg.pending) {
 *               break;
 *            }
 *         }
 *      }
 *
 * @endrst
 */
#define V4L2_SUB_EXT_VDEC_FRAME (V4L2_SUB_EXT_VDEC_BASE + 1)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for subscribing or unsubscribing Picture info event for fd
 *   in which VDEC instance is set. Before VIDIOC_STREAMON,
 *   V4L2_SUB_EXT_VDEC_PICINFO can be subscribed. Picture info event is an event
 *   that always occurs when VSC takes picture data through VDO. It is an event to
 *   register information related to picture delivered at this time in order to
 *   take VDEC element. The VDEC driver should record the event occurrence in the
 *   event queue after registering the Picture info event and manage the event
 *   occurrence information to check the occurrence of the event through ioctl
 *   DQEVENT. Also, Picture info data should be managed in a separate space so
 *   that Picture info data for the event can be taken with ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` . If the Picture info data in the
 *   VDEC element is moved to the ioctl :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS`
 *   , the corresponding data can be discarded. The value set as the type when the
 *   corresponding control ID is called is registered as
 *   V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT which means VDEC related event.
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
 *      subscription_arg.type = V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT;
 *      subscription_arg.id = V4L2_SUB_EXT_VDEC_PICINFO;
 *
 *      ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &subscription_arg); // Subscribe picture info event
 *
 *      ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &subscription_arg); // Unsubscribe picture info event
 *
 * @endrst
 */
#define V4L2_SUB_EXT_VDEC_PICINFO (V4L2_SUB_EXT_VDEC_BASE + 2)

/**
 * @rst
 * Functional Requirements
 *   It is a control ID for subscribing or unsubscribing Userdata event for fd in
 *   which VDEC instance is set. Before VIDIOC_STREAMON,
 *   V4L2_SUB_EXT_VDEC_USERDATA can be subscribed. Userdata refers to 603 type
 *   closed caption, rating data, DVS 157 type closed caption data, and rating
 *   data. Userdata event occurs when there is userdata in ES data entered in VDEC
 *   drvier. The VDEC driver should record the event occurrence in the event queue
 *   after registering the Userdata event and manage the event occurrence
 *   information to check the occurrence of the event through ioctl DQEVENT. Also,
 *   userdata should be managed in a separate space so that userdata for the event
 *   can be taken with ioctl :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` . If the
 *   userdata in the VDEC element is moved to the ioctl
 *   :c:func:`v4l-dvb-apis:VIDIOC_G_EXT_CTRLS` , the corresponding data can be
 *   discarded. The value set as the type when the corresponding control ID is
 *   called is registered as V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT which means VDEC
 *   related event.
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
 *      int ret = -1;
 *
 *      subscription_arg.type = V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT;
 *      subscription_arg.id = V4L2_SUB_EXT_VDEC_USERDATA;
 *
 *      ret = ioctl(fd, VIDIOC_SUBSCRIBE_EVENT, &subscription_arg); // Subscribe userdata event
 *
 *
 *      subscription_arg.type = V4L2_EVENT_PRIVATE_EXT_VDEC_EVENT;
 *      subscription_arg.id = V4L2_SUB_EXT_VDEC_USERDATA;
 *
 *      ret = ioctl(fd, VIDIOC_UNSUBSCRIBE_EVENT, &subscription_arg); // Unsubscribe userdata event
 *
 * @endrst
 */
#define V4L2_SUB_EXT_VDEC_USERDATA (V4L2_SUB_EXT_VDEC_BASE + 3)

/* VDO class control ID */
#define V4L2_CID_EXT_VDO_BASE (V4L2_CID_USER_EXT_VDEC_BASE + 0x500)

/**
 * @rst
 * Functional Requirements
 *   This is the control ID for connecting / disconnecting VDO to VDEC by
 *   specifying VDEC channel through fd opened by V4L2 in VDO device minor number.
 *   VDO is a path for transmitting the decoded picture to the VSC. In addition,
 *   VSC is a module that receives decoded picture and performs enlargement /
 *   reduction function. When the control ID is called, the value set to value is
 *   the number of the VDEC channel, and when set to -1, it means disconnect.
 *
 *   VDO Connecting method for webOS 5.0
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
 *     V4L2_CID_EXT_VDO_VDEC_PORT
 *
 *     //
 *     // control value
 *     //
 *
 *     // 0~N (Target port number to be connected)
 *     // -1 (Disconnect)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_control ctrl_arg;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VDO0, O_RDWR);
 *      ctrl_arg.id = V4L2_CID_EXT_VDO_VDEC_PORT;
 *      ctrl_arg.value = 0; // When you doing Connect, you need to set value argument as vdec channel num.
 *
 *      ioctl(fd, VIDIOC_S_CTRL, &ctrl_arg);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDO_VDEC_PORT (V4L2_CID_EXT_VDO_BASE + 1)

/**
 * @rst
 * Functional Requirements
 *   This is control ID for connecting VDO to VDEC through fd opened by V4L2 in
 *   VDO device minor number. VDO channel is set in 'vdo_port', and VDEC channel
 *   is set in 'vdec_port', the VDO channel is connected to the VDEC channel
 *   after invoking this CID.
 *   Picture data is transferred to VSC only when VDO is connected to VDEC.
 *   Therefore, Picture info event should not occur if VDO disconnected to VDEC.
 *   Even after fd is closed, you should keep the last setting.
 *
 *   VDO Connecting method for webOS 6.0
 *
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *      VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDO_VDEC_CONNECTING
 *
 *     //
 *     // control value
 *     //
 *     struct v4l2_ext_vdec_vdo_connection {
 *       __u32 vdo_port;
 *       __u32 vdec_port;
 *     };
 *     vdo_port =  0~1, VDO Port number, 0: VDO0 , 1: VDO1
 *     vdec_port = 0 ~ N , VDEC Port number
 *     // Get a fd from /dev/video28 to controll VDO0 and VDO1
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
 *   Application can get data using  :c:func:`v4l-dvb-apis:VIDIOC_S_EXT_CTRLS`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_ext_controls ext_controls;
 *      v4l2_ext_control ext_control;
 *      v4l2_ext_vdec_vdo_connection vdo_con;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VDO0, O_RDWR);
 *
 *      memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *      memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *      memset(&vdo_con, 0, sizeof(struct v4l2_ext_vdec_vdo_connection));
 *      vdo_con.vdo_port = 0; //vdo port number
 *      vdo_con.vdec_port = 0 ; //vdec port number
 *
 *      ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_VDO_VDEC_CONNECTING;
 *      ext_controls.controls->ptr = (void*) &vdo_mode;
 *
 *      ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDO_VDEC_CONNECTING (V4L2_CID_EXT_VDO_BASE + 2)

/**
 * @rst
 * Functional Requirements
 *   This is control ID for disconnecting VDO to VDEC through fd opened by V4L2 in
 *   VDO device minor number. VDO channel is set in 'vdo_port', and VDEC channel
 *   is set in 'vdec_port', the VDO channel is disconnected to the VDEC channel
 *   after invoking this CID.
 *   Picture data is transferred to VSC only when VDO is connected to VDEC. if
 *   VDO don't connected to VDEC, Picture data is dropped when STC becomes the
 *   same as the PTS. Therefore, Picture info event should not occur if VDO
 *   disconnected to VDEC.
 *   Even after fd is closed, you should keep the last setting.
 *
 *   VDO Connecting method for webOS 6.0
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *      VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VDO_VDEC_DISCONNECTING
 *
 *     //
 *     // control value
 *     //
 *     struct v4l2_ext_vdec_vdo_connection {
 *       __u32 vdo_port;
 *       __u32 vdec_port;
 *     };
 *     vdo_port = 0;  // 0~1, VDO Port number, 0: VDO0 , 1: VDO1
 *     vdec_port = 0; // don't care.
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
 *   Application can get data using  :c:func:`v4l-dvb-apis:VIDIOC_S_EXT_CTRLS`
 *   and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      v4l2_ext_controls ext_controls;
 *      v4l2_ext_control ext_control;
 *      v4l2_ext_vdec_vdo_connection vdo_con;
 *
 *      fd = open(V4L2_EXT_DEV_PATH_VDO0, O_RDWR);
 *      memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *      memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *      memset(&vdo_con, 0, sizeof(struct v4l2_ext_vdec_vdo_connection));
 *
 *      vdo_con.vdo_port = 0; //vdo port number
 *      vdo_con.vdec_port = 0 ; //vdec port number
 *
 *      ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_VDO_VDEC_DISCONNECTING;
 *      ext_controls.controls->ptr = (void*) &vdo_mode;
 *
 *      ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VDO_VDEC_DISCONNECTING (V4L2_CID_EXT_VDO_BASE + 3)

#endif // #ifndef _V4L2_EXT_VDEC_H
