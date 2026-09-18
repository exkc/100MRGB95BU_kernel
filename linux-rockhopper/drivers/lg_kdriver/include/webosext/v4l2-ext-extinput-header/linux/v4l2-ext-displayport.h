/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_DISPLAYPORT_H
#define _V4L2_EXT_DISPLAYPORT_H

#define V4L2_EXT_DEV_NO_DISPLAYPORT 14

#define V4L2_EXT_DEV_PATH_DISPLAYPORT "/dev/video14"

// User-class control Bases
#define V4L2_CID_USER_EXT_DISPLAYPORT_BASE (V4L2_CID_USER_BASE + 0xD000)

// DisplayPort BSP Capabilities Flags
// The device supports HDCP1.4 Key. So, need to write HDCP1.4 key to driver.
#define V4L2_EXT_DISPLAYPORT_HDCP14 ((unsigned long long)0x1 << 0)
// HDCP1.4 Key is OTP on Soc. So, No need to download HDCP1.4 Key to secure
// storage.
#define V4L2_EXT_DISPLAYPORT_HDCP14_KEY_OTP ((unsigned long long)0x1 << 1)

// The device supports HDCP2.3 key. So, need to write HDCP2.3 key to driver.
// HDCP2.3 key is include in HDCP2.3 key.
#define V4L2_EXT_DISPLAYPORT_HDCP23 ((unsigned long long)0x1 << 2)
// HDCP2.3 Key is OTP on Soc. So, No need to download HDCP2.3 Key to secure
// storage.
#define V4L2_EXT_DISPLAYPORT_HDCP23_KEY_OTP ((unsigned long long)0x1 << 3)

// The  DisplayPort device supports DP1.2 Specification
#define V4L2_EXT_DISPLAYPORT_DP12 ((unsigned long long)0x1 << 4)
// The  DisplayPort device supports DP1.4 Specification
#define V4L2_EXT_DISPLAYPORT_DP14 ((unsigned long long)0x1 << 5)
// The  DisplayPort device supports DP2.0 Specification.
#define V4L2_EXT_DISPLAYPORT_DP20 ((unsigned long long)0x1 << 6)
// The  DisplayPort device supports DP2.X future specification.
#define V4L2_EXT_DISPLAYPORT_DP2X ((unsigned long long)0x1 << 7)

// The  DisplayPort device supports 1 Lane mode
#define V4L2_EXT_DISPLAYPORT_LANE_NUMBER_1 ((unsigned long long)0x1 << 8)
// The  DisplayPort device supports 2 Lane mode
#define V4L2_EXT_DISPLAYPORT_LANE_NUMBER_2 ((unsigned long long)0x1 << 9)
// The  DisplayPort device supports 4 Lane mode
#define V4L2_EXT_DISPLAYPORT_LANE_NUMBER_4 ((unsigned long long)0x1 << 10)

// The DisplayPort device supports FreeSync
#define V4L2_EXT_DISPLAYPORT_FREESYNC ((unsigned long long)0x1 << 12)
// The  DisplayPort device supports Adaptive Sync
#define V4L2_EXT_DISPLAYPORT_ADAPTIVESYNC ((unsigned long long)0x1 << 13)
// The DisplayPort device supports 512bytes EDID
#define V4L2_EXT_DISPLAYPORT_512BYTE_EDID ((unsigned long long)0x1 << 14)
// The DisplayPort device supports DSC
#define V4L2_EXT_DISPLAYPORT_DSC ((unsigned long long)0x1 << 15)
// The DisplayPort device supports Source-led DolbyVision
#define V4L2_EXT_DISPLAYPORT_DOLBY_VISION ((unsigned long long)0x1 << 16)

// The DisplayPort device supports background timing detection.
// It means that driver can get DisplayPort signal information(timing, SPD, AVI,
// etc...) without watching DP port.
// If the DisplayPort device supports background timing detection, it also
// support fast switching between DP ports.
#define V4L2_EXT_DISPLAYPORT_BACKGROUND_TIMING_DETECT                          \
  ((unsigned long long)0x1 << 17)

// This is set when the port works as USB Type C DP Alt Mode.
#define V4L2_EXT_DISPLAYPORT_USB_TYPE_C_DP_ALT_MODE                            \
  ((unsigned long long)0x1 << 18)

enum v4l2_ext_displayport_input_port {
  V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0, /**< enum value none */
  V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,        /**< enum value port1 */
  V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,        /**< enum value port2 */
  V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,        /**< enum value port3 */
  V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,        /**< enum value port4 */
};

struct v4l2_ext_displayport_capability {
  enum v4l2_ext_displayport_input_port port;
  unsigned char chip_name[16];     // ex "o22"
  unsigned int major_version;      // header major version
  unsigned int minor_version;      // header minor version
  unsigned long long capabilities; // Displayport capabilities flags
  unsigned long long reserved[3];
};

enum v4l2_ext_displayport_scan_type {
  V4L2_EXT_DISPLAYPORT_SCAN_TYPE_INTERLACED = 0, /**< enum value interlaced */
  V4L2_EXT_DISPLAYPORT_SCAN_TYPE_PROGRESSIVE,    /**< enum value progressive */
};

enum v4l2_ext_displayport_color_depth {
  V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_6BIT = 0, /**< enum value 6bit */
  V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_8BIT,     /**< enum value 8bit */
  V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_10BIT,    /**< enum value 10bit */
  V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_12BIT,    /**< enum value 12bit  */
  V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_16BIT,    /**< enum value 16bit  */
  V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_RESERVED  /**< enum value reserved */
};

/* video timing */
struct v4l2_ext_displayport_video_timing {
  enum v4l2_ext_displayport_input_port port;
  unsigned short h_freq; /**< kHz x 10 */
  unsigned short v_freq; /**<  Hz x 10 */
  unsigned short h_total;
  unsigned short v_total;
  unsigned short h_porch;
  unsigned short v_porch;
  unsigned short active_width;
  unsigned short active_height;
  enum v4l2_ext_displayport_scan_type scan_type;
  enum v4l2_ext_displayport_color_depth color_depth;
};

enum v4l2_ext_displayport_audio_format {
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_UNKNOWN = 0x00,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_PCM = 0x01,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_AC3 = 0x10,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_EAC3 = 0x11,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_EAC3_ATMOS = 0x12,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_MAT = 0x15,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_MAT_ATMOS = 0x16,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_TRUEHD = 0x17,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_TRUEHD_ATMOS = 0x18,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_AAC = 0x19,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_MPEG = 0x20,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_DTS = 0x30,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_DTS_HD_MA = 0x31,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_DTS_EXPRESS = 0x32,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_DTS_CD = 0x33,
  V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_NOAUDIO = 0x41,
};

enum v4l2_ext_displayport_audio_copy_protection {
  V4L2_EXT_DISPLAYPORT_AUDIO_COPY_FREE = 0,
  V4L2_EXT_DISPLAYPORT_AUDIO_COPY_NO_MORE = 1,
  V4L2_EXT_DISPLAYPORT_AUDIO_COPY_ONCE = 2,
  V4L2_EXT_DISPLAYPORT_AUDIO_COPY_NEVER = 3,
};

/* audio timing */
struct v4l2_ext_displayport_audio_timing {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_audio_format format;
  unsigned int sampling_freq_hz;
  unsigned char channel_number;
  enum v4l2_ext_displayport_audio_copy_protection copy_protection;
};

/* main stream attribute */
struct v4l2_ext_displayport_msa {
  enum v4l2_ext_displayport_input_port port;
  unsigned int mvid;
  unsigned int nvid;
  unsigned short htotal;
  unsigned short vtotal;
  unsigned short hstart;
  unsigned short vstart;
  unsigned char hsync_polarity;
  unsigned char vsync_polarity;
  unsigned short hsync_width;
  unsigned short vsync_width;
  unsigned short hwidth;
  unsigned short vwidth;
  unsigned char misc0;
  unsigned char misc1;
  unsigned int reserved;
};

/* seconday data packet */
#define V4L2_EXT_DISPLAYPORT_SDP_HEADER_LENGTH 4
#define V4L2_EXT_DISPLAYPORT_SDP_DATA_LENGTH 32
#define V4L2_EXT_DISPLAYPORT_LONG_SDP_DATA_LENGTH 256

enum v4l2_ext_displayport_sdp_type {
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_TIMESTAMP = 0x01,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_STREAM = 0x02,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_EXTENSION = 0x04, /* application specific */
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_COPYMANAGEMENT =
      0x05, /* application specific */
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_ISRC =
      0x06, /* recording code, application specific */
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC = 0x07, /* 3D, colorimetry */
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_PPS = 0x10,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC_EXT_VESA = 0x20, /* video metadata  <=2KB */
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC_EXT_CTA = 0x21,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_ADAPTIVE_SYNC = 0x22,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_BASE = 0x80,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_VSI = 0x81,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_AVI = 0x82,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_SPD = 0x83,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_AUDIO = 0x84,
  V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_DRM = 0x87,
};

struct v4l2_ext_displayport_sdp {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_sdp_type type;
  unsigned int param; // OUI
  unsigned char header[V4L2_EXT_DISPLAYPORT_SDP_HEADER_LENGTH];
  unsigned char data[V4L2_EXT_DISPLAYPORT_SDP_DATA_LENGTH];
};

// packet0 has DB[0~255], packet1 has DB[256~511], ..
struct v4l2_ext_displayport_sdp_long {
  enum v4l2_ext_displayport_input_port port;                     // in
  enum v4l2_ext_displayport_sdp_type type;                       // in
  unsigned int param;                                            // in
  unsigned char header[V4L2_EXT_DISPLAYPORT_SDP_HEADER_LENGTH];  // out
  unsigned short current_packet_index;                           // in
  unsigned short total_packet_number;                            // out
  unsigned char data[V4L2_EXT_DISPLAYPORT_LONG_SDP_DATA_LENGTH]; // out
};

enum v4l2_ext_displayport_edid_size {
  V4L2_EXT_DISPLAYPORT_EDID_SIZE_128 = 128,
  V4L2_EXT_DISPLAYPORT_EDID_SIZE_256 = 256,
  V4L2_EXT_DISPLAYPORT_EDID_SIZE_512 = 512,
  V4L2_EXT_DISPLAYPORT_EDID_SIZE_384 = 384,
};

struct v4l2_ext_displayport_edid {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_edid_size size;
  union {
    unsigned char *pData;
    unsigned int compat_data;
    unsigned long long sizer;
  };
};

enum v4l2_ext_displayport_source_connection_state {
  V4L2_EXT_DISPLAYPORT_SOURCE_NOT_CONNECTED = 0,
  V4L2_EXT_DISPLAYPORT_SOURCE_CONNECTED,
};

struct v4l2_ext_displayport_source_connection {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_source_connection_state state;
};

enum v4l2_ext_displayport_hpd_state {
  V4L2_EXT_DISPLAYPORT_HPD_DISABLE = 0,
  V4L2_EXT_DISPLAYPORT_HPD_ENABLE,
  V4L2_EXT_DISPLAYPORT_HPD_RESTART,
};

struct v4l2_ext_displayport_hpd {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_hpd_state hpd_state;
};

enum v4l2_ext_displayport_hdcp_version {
  V4L2_EXT_DISPLAYPORT_HDCP_VERSION_14 = 0,
  V4L2_EXT_DISPLAYPORT_HDCP_VERSION_22,
  V4L2_EXT_DISPLAYPORT_HDCP_VERSION_RESERVED,
};

struct v4l2_ext_displayport_hdcp_key {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_hdcp_version version;
  unsigned int key_size;
  union {
    unsigned char *pData;
    unsigned int compat_data;
    unsigned long long sizer;
  };
};

struct v4l2_ext_displayport_adaptive_sync_frequency {
  enum v4l2_ext_displayport_input_port port;
  unsigned short frequency;
};

enum v4l2_ext_displayport_override_eotf {
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_SDR_LUMINANCE_RANGE = 0,
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_HDR_LUMINANCE_RANGE,
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_SMPTE_ST_2084,
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_HLG,
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_RESERVED_4,
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_RESERVED_5,
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_RESERVED_6,
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_RESERVED_7,
  V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_AUTO,
};

struct v4l2_ext_displayport_override_drm_info {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_override_eotf override_eotf;
};

enum v4l2_ext_displayport_dpms_mode {
  V4L2_EXT_DISPLAYPORT_DPMS_MODE_DISABLE = 0,
  V4L2_EXT_DISPLAYPORT_DPMS_MODE_ENABLE,
};

struct v4l2_ext_displayport_dpms {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_dpms_mode mode;
};

struct v4l2_ext_displayport_dpcd {
  enum v4l2_ext_displayport_input_port port;
  unsigned int address;
  unsigned char data;
};

/* DISPLAYPORT DIAGNOSTICS */

enum v4l2_ext_displayport_link_lane_number {
  V4L2_EXT_DISPLAYPORT_LINK_LANE_NUMBER_1 = 1,
  V4L2_EXT_DISPLAYPORT_LINK_LANE_NUMBER_2 = 2,
  V4L2_EXT_DISPLAYPORT_LINK_LANE_NUMBER_4 = 4,
};

enum v4l2_ext_displayport_link_rate {
  V4L2_EXT_DISPLAYPORT_LINK_RATE_RBR = 16,
  V4L2_EXT_DISPLAYPORT_LINK_RATE_HBR = 27,
  V4L2_EXT_DISPLAYPORT_LINK_RATE_HBR2 = 54,
  V4L2_EXT_DISPLAYPORT_LINK_RATE_HBR3 = 81,
  V4L2_EXT_DISPLAYPORT_LINK_RATE_UHBR10 = 100,
  V4L2_EXT_DISPLAYPORT_LINK_RATE_UHBR13 = 135,
  V4L2_EXT_DISPLAYPORT_LINK_RATE_UHBR20 = 200,
};

enum v4l2_ext_displayport_mode {
  V4L2_EXT_DISPLAYPORT_MODE_STANDARD = 0, /**< enum value standard mode */
  V4L2_EXT_DISPLAYPORT_MODE_ALT_MODE,     /**< enum value USB Type C Alt mode */
};

#define V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT 4

struct v4l2_ext_displayport_phy_status {
  enum v4l2_ext_displayport_input_port port;
  unsigned char lock_status;
  unsigned int stream_clock_khz;

  enum v4l2_ext_displayport_mode mode;
  enum v4l2_ext_displayport_link_lane_number lane_number;
  enum v4l2_ext_displayport_link_rate link_rate;

  unsigned int ctle_eq_min_range[V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT];
  unsigned int ctle_eq_max_range[V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT];
  unsigned int ctle_eq_result[V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT];
  unsigned int error[V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT];
};

struct v4l2_ext_displayport_link_status {
  enum v4l2_ext_displayport_input_port port;
  unsigned char hpd;
  unsigned char source_detection;
  unsigned char rx_sense;
  unsigned int frame_rate_x100_hz;

  unsigned short video_htotal_measured;
  unsigned short video_vtotal_measured;

  unsigned short video_width_measured;
  unsigned short video_height_measured;
};

enum v4l2_ext_displayport_hdcp_auth_status {
  V4L2_EXT_DISPLAYPORT_HDCP_AUTH_STATUS_NO_TX_CONNECTED = 0,
  V4L2_EXT_DISPLAYPORT_HDCP_AUTH_STATUS_UNAUTHENTICATED = 1,
  V4L2_EXT_DISPLAYPORT_HDCP_AUTH_STATUS_IN_PROGRESS = 2,
  V4L2_EXT_DISPLAYPORT_HDCP_AUTH_STATUS_AUTHENTICATED = 3,
};

struct v4l2_ext_displayport_hdcp14_status {
  enum v4l2_ext_displayport_input_port port;
  unsigned char An[8];
  unsigned char Aksv[5];
  unsigned char Bksv[5];
  unsigned char Ri[2];
  unsigned char Bcaps;
  unsigned char Bstatus[2];
};

struct v4l2_ext_displayport_hdcp_status {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_hdcp_version hdcp_version;
  enum v4l2_ext_displayport_hdcp_auth_status auth_status;
  unsigned char encEn;
  struct v4l2_ext_displayport_hdcp14_status hdcp14_status;
};

enum v4l2_ext_displayport_expert_setting_type {
  V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_MANUAL_EQ_MODE,
  V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_DISABLE_HDCP14,
  V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_DISABLE_HDCP22,
  V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_REAUTH_HDCP22,
  V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_MAXIMUM
};

struct v4l2_ext_displayport_expert_setting {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_expert_setting_type type;
  unsigned int param1;
  unsigned int param2;
  unsigned int param3;
};

enum v4l2_ext_displayport_external_dpcd_setting_type {
  V4L2_EXT_DISPLAYPORT_EXTERNAL_DPCD_SETTING_TYPE_GSYNC,
  V4L2_EXT_DISPLAYPORT_EXTERNAL_DPCD_SETTING_TYPE_MAXIMUM
};

struct v4l2_ext_displayport_external_dpcd_setting {
  enum v4l2_ext_displayport_input_port port;
  enum v4l2_ext_displayport_external_dpcd_setting_type type;
  unsigned int param1;
  unsigned int param2;
  unsigned int param3;
};

/* =====================================================================================
LIST OF DisplayPort APIs

open
close
s_input

epoll
subscribe (video_timing, audio_timing, msa, sp, sdp_long, source_connection,
hpd)
unsubscribe
dqevent

#define V4L2_CID_EXT_DISPLAYPORT_CAPABILITY (V4L2_CID_USER_EXT_DISPLAYPORT_BASE
+ 0)
#define V4L2_CID_EXT_DISPLAYPORT_VIDEO_TIMING
(V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 1)
#define V4L2_CID_EXT_DISPLAYPORT_AUDIO_TIMING
(V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 2)
#define V4L2_CID_EXT_DISPLAYPORT_MSA   (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 3)
#define V4L2_CID_EXT_DISPLAYPORT_SDP  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 4)
#define V4L2_CID_EXT_DISPLAYPORT_SDP_LONG (V4L2_CID_USER_EXT_DISPLAYPORT_BASE +
5)

#define V4L2_CID_EXT_DISPLAYPORT_SOURCE_CONNECTION
(V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 6)
#define V4L2_CID_EXT_DISPLAYPORT_HPD (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 7)
#define V4L2_CID_EXT_DISPLAYPORT_EDID (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 8)
#define V4L2_CID_EXT_DISPLAYPORT_HDCP_KEY (V4L2_CID_USER_EXT_DISPLAYPORT_BASE +
9)
#define V4L2_CID_EXT_DISPLAYPORT_DPMS (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 10)

#define V4L2_CID_EXT_DISPLAYPORT_DISCONNECT (V4L2_CID_USER_EXT_DISPLAYPORT_BASE
+ 11)

#define V4L2_CID_EXT_DISPLAYPORT_ADAPTIVE_SYNC_FREQUENCY
(V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 12)
#define V4L2_CID_EXT_DISPLAYPORT_OVERRIDE_EOTF
(V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 13)
#define V4L2_CID_EXT_DISPLAYPORT_DPCD (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 14)

#define V4L2_CID_EXT_DISPLAYPORT_PHY_STATUS (V4L2_CID_USER_EXT_DISPLAYPORT_BASE
+ 100)
#define V4L2_CID_EXT_DISPLAYPORT_LINK_STATUS (V4L2_CID_USER_EXT_DISPLAYPORT_BASE
+ 101)
#define V4L2_CID_EXT_DISPLAYPORT_HDCP_STATUS (V4L2_CID_USER_EXT_DISPLAYPORT_BASE
+ 102)
#define V4L2_CID_EXT_DISPLAYPORT_EXPERT_SETTING
(V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 103)

===============================================================================================
*/

/**
 * @brief Get DisplayPort capabilities from BSP
 *
 * @rst
 * Functional Requirements
 *   This function get DisplayPort capabilities in each port.
 *   It is used to identify DisplayPort device compatible with this
 * specification and to obtain information about driver and each DisplayPort
 * port capabilities.
 *   The ioctl takes a pointer to a struct which is filled by the driver.
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
 *     VIDIOC_G_EXT_CTRLS        // Get DisplayPort capabilities
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_CAPABILITY
 *
 *     //
 *     // parameter
 *     //
 *
 *     // DisplayPort BSP Capabilities Flags
 *     // The device supports HDCP1.4 Key. So, need to write HDCP1.4 key to
 * driver.
 *     #define V4L2_EXT_DISPLAYPORT_HDCP14 \
 *         ((unsigned long long)0x1 << 0)
 *     // HDCP1.4 Key is OTP on Soc. So, No need to download HDCP1.4 Key to
 * secure storage.
 *     #define V4L2_EXT_DISPLAYPORT_HDCP14_KEY_OTP \
 *         ((unsigned long long)0x1 << 1)
 *
 *     // The DisplayPort device supports HDCP2.3 key. So, need to write HDCP2.3
 * key to driver.
 *     // HDCP2.3 key is include in HDCP2.3 key.
 *     #define V4L2_EXT_DISPLAYPORT_HDCP23 \
 *         ((unsigned long long)0x1 << 2)
 *     // HDCP2.3 Key is OTP on Soc. So, No need to download HDCP2.3 Key to
 * secure storage.
 *     #define V4L2_EXT_DISPLAYPORT_HDCP23_KEY_OTP \
 *         ((unsigned long long)0x1 << 3)
 *
 *     // The DisplayPort device supports DP1.2 Specification
 *     #define V4L2_EXT_DISPLAYPORT_DP12 \
 *         ((unsigned long long)0x1 << 4)
 *     // The DisplayPort device supports DP1.4 Specification
 *     #define V4L2_EXT_DISPLAYPORT_DP14 \
 *         ((unsigned long long)0x1 << 5)
 *     // The DisplayPort device supports DP2.0 Specification.
 *     #define V4L2_EXT_DISPLAYPORT_DP20 \
 *         ((unsigned long long)0x1 << 6)
 *     // The DisplayPort device supports DP2.X future specification.
 *     #define V4L2_EXT_DISPLAYPORT_DP2X \
 *         ((unsigned long long)0x1 << 7)
 *
 *     // The DisplayPort device supports 1 Lane mode
 *     #define V4L2_EXT_DISPLAYPORT_LANE_NUMBER_1 \
 *         ((unsigned long long)0x1 << 8)
 *     // The DisplayPort device supports 2 Lane mode
 *     #define V4L2_EXT_DISPLAYPORT_LANE_NUMBER_2 \
 *         ((unsigned long long)0x1 << 9)
 *     // The DisplayPort device supports 4 Lane mode
 *     #define V4L2_EXT_DISPLAYPORT_LANE_NUMBER_4 \
 *         ((unsigned long long)0x1 << 10)
 *
 *     // The DisplayPort device supports FreeSync
 *     #define V4L2_EXT_DISPLAYPORT_FREESYNC \
 *         ((unsigned long long)0x1 << 12)
 *     // The DisplayPort device supports Adaptive Sync
 *     #define V4L2_EXT_DISPLAYPORT_ADAPTIVESYNC \
 *         ((unsigned long long)0x1 << 13)
 *     // The DisplayPort device supports 512bytes EDID
 *     #define V4L2_EXT_DISPLAYPORT_512BYTE_EDID \
 *         ((unsigned long long)0x1 << 14)
 *     // The DisplayPort device supports DSC
 *     #define V4L2_EXT_DISPLAYPORT_DSC \
 *         ((unsigned long long)0x1 << 15)
 *     // The DisplayPort device supports Source-led DolbyVision
 *     #define V4L2_EXT_DISPLAYPORT_DOLBY_VISION \
 *         ((unsigned long long)0x1 << 16)
 *
 *     struct v4l2_ext_displayport_capability
 *     {
 *        enum v4l2_ext_displayport_input_port port;
 *        unsigned char chip_name[16];          // ex "o22"
 *        unsigned int major_version;            // header major version
 *        unsigned int minor_version;            // header minor version
 *        unsigned long long capabilities; // Displayport capabilities flags
 *        unsigned long long reserved[3];
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // get DisplayPort capability
 *     v4l2_ext_controls ext_controls = {};
 *     v4l2_ext_control ext_control = {};
 *     struct v4l2_ext_displayport_capability caps = {};
 *
 *     caps.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_CAPABILITY;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_capability);
 *     ext_controls.controls->ptr = (void *)&caps;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_CAPABILITY                                    \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 0)

/**
 * @brief Get DisplayPort video timing
 *
 * @rst
 * Functional Requirements
 *   This function gets DisplayPort video timing data calculated in the BSP.
 *   When the V frequency is 0, other fields must be transferred as an initial
 * value.
 *
 * Responses to abnormal situations, including
 *   If SoC could detect video timing for the input signal, it should return the
 * information even if SoC could not handle the format.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Correct video timing data must be delivered independently for each
 * DisplayPort port in background mode.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get DisplayPort Video Timing
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_VIDEO_TIMING
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_color_depth
 *     {
 *         V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_6BIT = 0,
 *         V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_8BIT,
 *         V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_10BIT,
 *         V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_12BIT,
 *         V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_16BIT,
 *         V4L2_EXT_DISPLAYPORT_COLOR_DEPTH_RESERVED
 *     };
 *
 *     struct v4l2_ext_displayport_video_timing
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         unsigned short h_freq;
 *         unsigned short v_freq;
 *         unsigned short h_total;
 *         unsigned short v_total;
 *         unsigned short h_porch;
 *         unsigned short v_porch;
 *         unsigned short active_width;
 *         unsigned short active_height;
 *         unsigned short scan_type;
 *         enum v4l2_ext_displayport_color_depth color_depth;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Video Timing
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_video_timing video_timing;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&video_timing, 0, sizeof(struct
 * v4l2_ext_displayport_video_timing));
 *
 *     video_timing.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_VIDEO_TIMING;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_video_timing);
 *     ext_controls.controls->ptr = (void *)&video_timing;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_VIDEO_TIMING                                  \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 1)

/**
 * @brief Get DisplayPort audio timing
 *
 * @rst
 * Functional Requirements
 *   This function gets DisplayPort audio timing data.
 *
 * Responses to abnormal situations, including
 *   NA
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Correct audio timing data must be delivered independently for each
 * DisplayPort port in background mode.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get DisplayPort audio timing
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_AUDIO_TIMING
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_audio_format
 *     {
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_UNKNOWN      = 0x00,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_PCM          = 0x01,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_AC3          = 0x10,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_EAC3         = 0x11,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_EAC3_ATMOS   = 0x12,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_MAT          = 0x15,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_MAT_ATMOS    = 0x16,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_TRUEHD       = 0x17,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_TRUEHD_ATMOS = 0x18,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_AAC          = 0x19,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_MPEG         = 0x20,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_DTS          = 0x30,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_DTS_HD_MA    = 0x31,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_DTS_EXPRESS  = 0x32,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_DTS_CD       = 0x33,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_FORMAT_NOAUDIO      = 0x41,
 *     };
 *
 *     enum v4l2_ext_displayport_audio_copy_protection
 *     {
 *         V4L2_EXT_DISPLAYPORT_AUDIO_COPY_FREE    = 0,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_COPY_NO_MORE = 1,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_COPY_ONCE    = 2,
 *         V4L2_EXT_DISPLAYPORT_AUDIO_COPY_NEVER   = 3,
 *     };
 *
 *     struct v4l2_ext_displayport_audio_timing
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         enum v4l2_ext_displayport_audio_format audio_format;
 *         unsigned int audio_sampling_freq_hz;
 *         unsigned char audio_channel_number;
 *         v4l2_ext_displayport_audio_copy_protection copy_protection;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error,, -1 and the errno variable is set appropriately. The generic
 * error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Audio Timing
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_audio_timing audio_timing;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&audio_timing, 0, sizeof(struct
 * v4l2_ext_displayport_audio_timing));
 *
 *     audio_timing.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_AUDIO_TIMING;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_audio_timing);
 *     ext_controls.controls->ptr = (void *)&audio_timing;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_AUDIO_TIMING                                  \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 2)

/**
 * @brief Get DisplayPort MSA(main stream attribute) data
 *
 * @rst
 * Functional Requirements
 *   This function gets DisplayPort MSA data.
 *
 * Responses to abnormal situations, including
 *   If Displayport signal is unstable or Vertical Frequency is 0, SDP packet
 * should be cleared.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Correct video timing information must be delivered independently for each
 * DisplayPort port in background mode.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get DisplayPort MSA data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_MSA
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     struct v4l2_ext_displayport_msa
 *     {
 *        enum v4l2_ext_displayport_input_port port; // in
 *        unsigned int mvid;
 *        unsigned int nvid;
 *        unsigned short htotal;
 *        unsigned short vtotal;
 *        unsigned short hstart;
 *        unsigned short vstart;
 *        unsigned char hsync_polarity;
 *        unsigned char vsync_polarity;
 *        unsigned short hsync_width;
 *        unsigned short vsync_width;
 *        unsigned short hwidth;
 *        unsigned short vwidth;
 *        unsigned char misc0;
 *        unsigned char misc1;
 *        unsigned int reserved;
 *      };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get Video Timing Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_msa msa_data;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&msa_data, 0, sizeof(struct v4l2_ext_displayport_msa));
 *
 *     msa_data.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_MSA;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_msa);
 *     ext_controls.controls->ptr = (void *)&msa_data;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_MSA (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 3)

/**
 * @brief Get DisplayPort SDP PACKET
 *
 * @rst
 * Functional Requirements
 *   This function get SDP(secondary data packet) data which has 32 data bytes
 * or less.
 *
 *   V4L2_CID_EXT_DISPLAYPORT_SDP can be used for VSC, ADAPTIVE_SYNC, AVI,VSI,
 * SPD DRnM infoframes.
 *
 * Responses to abnormal situations, including
 *   If Displayport signal is unstable or Vertical Frequency is 0, SDP packet
 * should be cleared.
 *
 * Performance Requirements
 *   None
 *
 * Constraints
 *   This CID is used to get 32 bytes SDP or shorter data only.
 *   For CTA Vendor Specific Infoframes, OUI Id will be proviede to param
 * argument. BSP should support at least four VSIs simultaneously.
 *   For CTA DRnM Infoframe, webOS checks eotf_type, version and length field to
 * decide if it is valid.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get specified SDP packet which has equal or
 * less than 32 data bytes.
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_SDP
 *
 *     //
 *     // parameter
 *     //
 *
 *     #define V4L2_EXT_DISPLAYPORT_SDP_HEADER_LENGTH 4
 *     #define V4L2_EXT_DISPLAYPORT_SDP_DATA_LENGTH 32
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_sdp_type {
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_TIMESTAMP = 0x01,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_STREAM = 0x02,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_EXTENSION = 0x04,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_COPYMANAGEMENT = 0x05,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_ISRC = 0x06,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC = 0x07,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_PPS = 0x10,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC_EXT_VESA = 0x20,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC_EXT_CTA = 0x21,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_ADAPTIVE_SYNC = 0x22,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_BASE = 0x80,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_VSI = 0x81,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_AVI = 0x82,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_SPD = 0x83,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_AUDIO = 0x84,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_DRM = 0x87,
 *     };
 *
 *     struct v4l2_ext_displayport_sdp
 *     {
 *         enum v4l2_ext_displayport_input_port port; // in
 *         enum v4l2_ext_displayport_sdp_type type; // in
 *         unsigned int param; // in
 *         unsigned char header[V4L2_EXT_DISPLAYPORT_SDP_HEADER_LENGTH]; // out
 *         unsigned char data[V4L2_EXT_DISPLAYPORT_SDP_DATA_LENGTH]; // out
 *     }
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get AVI Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_sdp sdp;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&sdp, 0, sizeof(struct v4l2_ext_displayport_sdp));
 *
 *     sdp.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_SDP;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_sdp);
 *     ext_controls.controls->ptr = (void *)&sdp;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_SDP (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 4)

/**
 * @brief Get DisplayPort Long SDP packet
 *
 * @rst
 * Functional Requirements
 *   This control returns long SDP packet data.
 *
 *   For SDP which has larger data bytes, use V4L2_CID_EXT_DISPLAYPORT_SDP_LONG.
 *
 *   V4L2_CID_EXT_DISPLAYPORT_SDP_LONG can be used for PPS, VSC_EXT_VESA,
 VSC_EXT_CTA.
 *
 *   As soon as getting long SDP packet data, BSP should return the SDP packet
 data to webOS.
 *
 * Responses to abnormal situations, including
 *   If DisplayPort clock is unstable or Vertical Frequency is 0, SDP packet
 should be cleared.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   long SDP packet should be updated within the similar time with other SDP.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get long SDP packet
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_SDP_LONG
 *
 *     //
 *     // parameter
 *     //
 *
 *     #define V4L2_EXT_DISPLAYPORT_SDP_HEADER_LENGTH 4
 *     #define V4L2_EXT_DISPLAYPORT_SDP_DATA_LENGTH 32
 *     #define V4L2_EXT_DISPLAYPORT_LONG_SDP_DATA_LENGTH 256

 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_sdp_type {
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_TIMESTAMP = 0x01,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_STREAM = 0x02,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_EXTENSION = 0x04,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_AUDIO_COPYMANAGEMENT = 0x05,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_ISRC = 0x06,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC = 0x07,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_PPS = 0x10,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC_EXT_VESA = 0x20,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_VSC_EXT_CTA = 0x21,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_ADAPTIVE_SYNC = 0x22,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_BASE = 0x80,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_VSI = 0x81,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_AVI = 0x82,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_SPD = 0x83,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_AUDIO = 0x84,
 *         V4L2_EXT_DISPLAYPORT_SDP_TYPE_INFOFRAME_DRM = 0x87,
 *     };
 *
 *     struct v4l2_ext_displayport_sdp_long
 *     {
 *         enum v4l2_ext_displayport_input_port port; // in
 *         enum v4l2_ext_displayport_sdp_type type; // in
 *         unsigned int param; // in
 *         unsigned char header[V4L2_EXT_DISPLAYPORT_SDP_HEADER_LENGTH]; // out
 *         unsigned short current_packet_index; // in
 *         unsigned short total_packet_number; // out
 *         unsigned char data[V4L2_EXT_DISPLAYPORT_LONG_SDP_DATA_LENGTH]; // out
 *     }
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get long SDP packet
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_sdp_long sdp_long;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&sdp_long, 0, sizeof(struct v4l2_ext_displayport_sdp_long));
 *
 *     sdp_long.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     sdp_long.type = V4L2_EXT_DISPLAYPORT_SDP_TYPE_PPS;
 *     sdp_long.current_packet_index = 0;
 *
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_SDP_LONG;
 *     ext_controls.controls->size = sizeof(struct
 v4l2_ext_displayport_sdp_long);
 *     ext_controls.controls->ptr = (void *)&sdp_long;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_SDP_LONG                                      \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 5)

/**
 * @brief Get DisplayPort Source Device Connection Status
 *
 * @rst
 * Functional Requirements
 *   This control returns source device connection state.
 *   DisplayPort provides upstream device detection with AUX_CH line DC voltage
 level.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   NA
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get Port Connection Status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_SOURCE_CONNECTION
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_source_connection_state
 *     {
 *         V4L2_EXT_DISPLAYPORT_SOURCE_NOT_CONNECTED = 0,
 *         V4L2_EXT_DISPLAYPORT_SOURCE_CONNECTED,
 *     };

 *     struct v4l2_ext_displayport_source_connection
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         v4l2_ext_displayport_source_connection_state state;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get DisplayPort source device connection state
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_source_connection source_connection;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&source_connection, 0, sizeof(struct
 v4l2_ext_displayport_source_connection));
 *
 *     source_connection.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_SOURCE_CONNECTION;
 *     ext_controls.controls->size = sizeof(struct
 v4l2_ext_displayport_source_connection);
 *     ext_controls.controls->ptr = (void *)&source_connection;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_SOURCE_CONNECTION                             \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 6)

/**
 * @brief Set/Get Port HPD Control
 *
 * @rst
 * Functional Requirements
 *   This control handles HPD controls. (Enable / Disable / Restart)
 *   Enable and Disable does not mean changing HPD state to high or low.
 *   Initial value should be 'Disable' and BSP should not change HPD value to
 * high at this time.
 *   After webOS call 'Enable' state, BSP could change HPD value to high or low.
 *   webOS does not control HPD value itself.
 *   webOS calls Restart state to change EDID or reset connection. At this time
 * BSP should handle HPD and RxSense together.
 *   It should have the same effect with plugging out and in the cable.
 *   The internal video mute operation should be performed when HPD is
 * restarted, not when the EDID is changed.
 *
 *   webOS does not control or read interrupt request feature with HPD.
 *
 * Responses to abnormal situations, including
 *   If V4L2_EXT_DISPLAYPORT_HPD_RESTART is called before
 * V4L2_EXT_DISPLAYPORT_HPD_ENABLE, it should be ignored.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   HPD should be controlled only inside one thread. Controlling HPD in two or
 * more threads may cause collision problems.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set Control HPD
 *     VIDIOC_G_EXT_CTRLS      // Get Control HPD
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_HPD
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_hpd_state
 *     {
 *         V4L2_EXT_DISPLAYPORT_HPD_DISABLE = 0,
 *         V4L2_EXT_DISPLAYPORT_HPD_ENABLE,
 *         V4L2_EXT_DISPLAYPORT_HPD_RESTART,
 *     };
 *
 *     struct v4l2_ext_displayport_hpd
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         enum v4l2_ext_displayport_hpd_state hpd_state;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
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
 *     // Set Control HPD
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_hpd hpd;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hpd, 0, sizeof(struct v4l2_ext_displayport_hpd));
 *
 *     hpd.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     hpd.eHPDControl = V4L2_DISPLAYPORT_HPD_CONTROL_DISABLE;
 *     //hpd.eHPDControl = V4L2_DISPLAYPORT_HPD_CONTROL_ENABLE;
 *     //hpd.eHPDControl = V4L2_DISPLAYPORT_HPD_CONTROL_RESTART;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_HPD;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_hpd);
 *     ext_controls.controls->ptr = (void *)&hpd;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Get Control HPD
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_hpd hpd;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hpd, 0, sizeof(struct v4l2_ext_displayport_hpd));
 *
 *     hpd.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_HPD;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_hpd);
 *     ext_controls.controls->ptr = (void *)&hpd;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_HPD (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 7)

/**
 * @brief Get/Set DisplayPort EDID
 *
 * @rst
 * Functional Requirements
 *   This control write or read EDID.
 *   It could be read and written at any time. There're many scenarios that EDID
 * is changed.
 *   Instead of EDID, DisplayID could be used.
 *
 * Responses to abnormal situations, including
 *   EDID should be accessible by the source device even when the TV is in the
 * standby mode.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   BSP behavior should not depend on the EDID data written.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get DisplayPort EDID
 *     VIDIOC_S_EXT_CTRLS      // Set DisplayPort EDID
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_EDID
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_edid_size
 *     {
 *         V4L2_EXT_DISPLAYPORT_EDID_SIZE_128 = 0,
 *         V4L2_EXT_DISPLAYPORT_EDID_SIZE_256,
 *         V4L2_EXT_DISPLAYPORT_EDID_SIZE_512,
 *     };
 *
 *     struct v4l2_ext_displayport_edid
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         enum v4l2_ext_displayport_edid_size size;
 *         union
 *         {
 *             unsigned char *pData;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set EDID Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_edid edid;
 *     unsigned char data[256] = {1,2,3,4,5, };
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&edid, 0, sizeof(struct v4l2_ext_displayport_edid));
 *
 *     edid.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     edid.size = V4L2_EXT_DISPLAYPORT_EDID_SIZE_256;
 *     edid.pData = &data;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_EDID;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_edid);
 *     ext_controls.controls->ptr = (void *)&edid;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Get EDID Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_edid edid;
 *     unsigned char data[256] = {0, };
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&edid, 0, sizeof(struct v4l2_ext_displayport_edid));
 *
 *     edid.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     edid.size = V4L2_EXT_DISPLAYPORT_EDID_SIZE_256;
 *     edid.pData = &data;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_EDID;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_edid);
 *     ext_controls.controls->ptr = (void *)&edid;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_EDID (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 8)

/**
 * @brief Write DisplayPort HDCP key
 *
 * @rst
 * Functional Requirements
 *   This control writes HDCP1.4 and HDCP2.3 key.
 *   If HDCP1.4 key is OTPed, webOS will only write HDCP2.3 key.
 *
 * Responses to abnormal situations, including
 *   If a temporary HDCP key is used during Bring up, it must be deleted before
 * the test event starts.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   The HDCP key for testing should not be included in the software.
 *   For models that do not support HDCP 2.3, HDCP 2.3 engine should be disabled
 * by BSP driver.
 *   HDCP 2.3 raw key should not be exposed to linux user space.
 *   BSP should internally encrypt the key or read from the secure storage
 * directly and ignore V4L2_CID_EXT_DISPLAYPORT_HDCP_KEY call.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set HDCP Key data
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_HDCP_KEY
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_hdcp_version
 *     {
 *         V4L2_EXT_DISPLAYPORT_HDCP_VERSION_14 = 0,
 *         V4L2_EXT_DISPLAYPORT_HDCP_VERSION_22,
 *         V4L2_EXT_DISPLAYPORT_HDCP_VERSION_RESERVED,
 *     };
 *
 *     struct v4l2_ext_displayport_hdcp_key
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         enum v4l2_ext_displayport_hdcp_version version;
 *         unsigned int key_size;
 *         union {
 *             unsigned char *pData;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Write HDCP Key
 *     #define HDCP14_KEY_SIZE 288
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_hdcp_key hdcp_key;
 *     unsigned char key[HDCP14_KEY_SIZE] = {1,2,3,4,5,};
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdcp_key, 0, sizeof(struct v4l2_ext_displayport_hdcp_key));
 *
 *     hdcp_key.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     hdcp_key.pData = &key;
 *     hdcp_key.version = V4L2_EXT_DISPLAYPORT_HDCP_VERSION_14;
 *     hdcp_key.key_size = HDCP14_KEY_SIZE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_HDCP_KEY;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_hdcp_key);
 *     ext_controls.controls->ptr = (void *)&hdcp_key;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_HDCP_KEY                                      \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 9)

/**
 * @brief Set mode for DPMS function.
 *
 * @rst
 * Functional Requirements
 *   TV power will automatically turn off when DISPLAYPORT no signal status
 * continues for more than a certain period of time.
 *   After that, when the DisplayPort signal is detected again, the TV will
 * power on.
 *   It is called DPMS function.
 *   This command sets the DPMS mode when the TV is powered off.
 *   When DPMS mode is V4L2_EXT_DISPLAYPORT_DPMS_MODE_ENABLE and the power is
 * turned off, The DisplayPort Phy should check the source request via AUX_CH.
 *
 * Responses to abnormal situations, including
 *   Because the result of the AUX_CH may not be trustworthy, webOS will check
 * video timing again during the DC on time.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Result of Power On request from source device in AUX_CH will be informed to
 * micom.
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
 *     V4L2_CID_EXT_DISPLAYPORT_DPMS
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_displayport_dpms_mode{
 *          V4L2_EXT_DISPLAYPORT_DPMS_MODE_DISABLE,
 *          V4L2_EXT_DISPLAYPORT_DPMS_MODE_ENABLE,
 *     };
 *
 *     struct v4l2_ext_displayport_dpms {
 *          enum v4l2_ext_displayport_input_port port;
 *          enum v4l2_ext_displayport_dpms_mode mode;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set dpms mode
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_dpms dpms_mode;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&dpms_mode, 0, sizeof(struct v4l2_ext_displayport_dpms));
 *
 *     dpms_mode.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     dpms_mode.mode = V4L2_EXT_DISPLAYPORT_DPMS_MODE_ENABLE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_DPMS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_dpms);
 *     ext_controls.controls->ptr = (void *)&dpms_mode;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_DPMS (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 10)

/**
 * @brief Disconnect DisplayPort Port
 *
 * @rst
 * Functional Requirements
 *   Disconnect specific DisplayPort connected.
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
 *     VIDIOC_S_CTRL       // Disconnect DisplayPort Port
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_DISCONNECT
 *
 *     //
 *     // control value
 *     //
 *     enum v4l2_displayport_input_port
 *     {
 *         DISPLAYPORT_INPUT_PORT_NONE = 0, //DISPLAYPORT_INPUT_PORT_NONE means
 * "DISPLAYPORT Disconnect".
 *         // The below enum values mean "DISPLAYPORT Connect".
 *         DISPLAYPORT_INPUT_PORT1,
 *         DISPLAYPORT_INPUT_PORT2,
 *         DISPLAYPORT_INPUT_PORT3,
 *         DISPLAYPORT_INPUT_PORT4,
 *         DISPLAYPORT_INPUT_PORT_ALL,
 *         DISPLAYPORT_INPUT_PORT_MAX,
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_CTRL and this control id.
 *   This control id supports VIDIOC_S_CTRL only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Disconnet DisplayPort Port
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_DISPLAYPORT_DISCONNECT;
 *     control.value = (int)DISPLAYPORT_INPUT_PORT1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_DISCONNECT                                    \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 11)

/**
 * @brief Get DisplayPort Adaptive Sync Frequency
 *
 * @rst
 * Functional Requirements
 *   This control returns Adaptive Sync frequency.
 *   Frequency unit is Hz*100 (59.98hz → 5998, 120hz → 12000).
 *
 * Responses to abnormal situations, including
 *   This is required when the product supports Adaptive Sync feature. Otherwise
 * it would return -1.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   It should return instantaneous frame rate calulated by BSP.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get DisplayPort Adaptive Sync Frequency
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_ADAPTIVE_SYNC_FREQUENCY
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     struct v4l2_ext_displayport_adaptive_sync_frequency
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         unsigned short frequency;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get DisplayPort Adaptive Sync Frequency
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_adaptive_sync_frequency freq;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&freq, 0, sizeof(struct
 * v4l2_ext_displayport_adaptive_sync_frequency));
 *
 *     freq.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id =
 * V4L2_CID_EXT_DISPLAYPORT_ADAPTIVE_SYNC_FREQUENCY;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_adaptive_sync_frequency);
 *     ext_controls.controls->ptr = (void *)&freq;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_ADAPTIVE_SYNC_FREQUENCY                       \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 12)

/**
 * @brief Set EOTF value to BSP
 *
 * @rst
 * Functional Requirements
 *   This function is used to force EOTF values to be set to BSP by webOS.
 *   If webOS deliver certain EOTF values through this function,
 *   EOTF value frome the surce device should be ignored and BSP set the values
 * sent by webOS,
 *   This value must be applied to the BSP modules referenced by pq or scaler
 * BSP.
 *   PQ and SCALER BSP must operate with the EOTF value set by webOS.
 *   If override_eotf value is AUTO, set the EOTF value from the actual DRM
 * PACKET.
 *   If override_eotf value is not AUTO, set the EOTF value to SETTING from
 * webOS.
 *
 * Responses to abnormal situations, including
 *   when webOS set the V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_SMPTE_ST_2084 or
 *   V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_HLG, BSP must set the version of drm
 * info as 1.
 *   webOS do not recognize HDR or HLG if the version of drm info is not 1.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   webOS will only call the function once if the EOTF value is changed.
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
 *     V4L2_CID_EXT_DISPLAYPORT_OVERRIDE_EOTF
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_displayport_override_eotf {
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_SDR_LUMINANCE_RANGE = 0,
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_HDR_LUMINANCE_RANGE,
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_SMPTE_ST_2084,
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_HLG,
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_RESERVED_4,
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_RESERVED_5,
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_RESERVED_6,
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_RESERVED_7,
 *         V4L2_EXT_DISPLAYPORT_OVERRIDE_EOTF_AUTO,
 *     };
 *     struct v4l2_ext_displayport_override_drm_info {
 *         enum v4l2_ext_displayport_input_port port;
 *         enum v4l2_ext_displayport_override_eotf override_eotf;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set override EOTF value.
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_override_drm_info status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct
 * v4l2_ext_displayport_override_drm_info));
 *
 *     status.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     status.override_eotf = V4L2_CID_EXT_DISPLAYPORT_OVERRIDE_HLG;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_OVERRIDE_EOTF;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_override_drm_info);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_OVERRIDE_EOTF                                 \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 13)

/**
 * @brief Get or Set DisplayPort DPCD status
 *
 * @rst
 * Functional Requirements
 *   This control set or get DisplayPort DPCD value.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   From webOS23, it should be returned within 10 msec.
 *
 * Constraints
 *   During the normal operation, webOS would not set DPCD value. BSP should
 * handle correct values.
 *   webOS will set DPCD for debugging purpose only.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS
 *     VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_DPCD
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     struct v4l2_ext_displayport_dpcd
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         unsigned char address; // in
 *         unsigned char data;  // out
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get DisplayPort DPCD value
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_dpcd dpcd;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&dpcd, 0, sizeof(struct v4l2_ext_displayport_dpcd));
 *
 *     dpcd.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     dpcd.address = 0x100;
 *     dpcd.data = 0;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_DPCD;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_dpcd);
 *     ext_controls.controls->ptr = (void *)&dpcd;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *     // Set DisplayPort DPCD value
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_dpcd dpcd;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&dpcd, 0, sizeof(struct v4l2_ext_displayport_dpcd));
 *
 *     dpcd.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     dpcd.data = 0x10;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_DPCD;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_dpcd);
 *     ext_controls.controls->ptr = (void *)&dpcd;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_DPCD (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 14)

/**
 * @brief Get DisplayPort PHY status
 *
 * @rst
 * Functional Requirements
 *   This control returns DisplayPort PHY status. This information is used in
 * DisplayPort diagnostics menu.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   From webOS23, it should be returned within 10 msec.
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
 *     VIDIOC_G_EXT_CTRLS      // Get DisplayPort PHY status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_PHY_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_mode {
 *         V4L2_EXT_DISPLAYPORT_MODE_STANDARD = 0,
 *         V4L2_EXT_DISPLAYPORT_MODE_ALT_MODE,
 *     };
 *
 *     enum v4l2_ext_displayport_link_lane_number
 *     {
 *         V4L2_EXT_DISPLAYPORT_LINK_LANE_NUMBER_1 = 1,
 *         V4L2_EXT_DISPLAYPORT_LINK_LANE_NUMBER_2 = 2,
 *         V4L2_EXT_DISPLAYPORT_LINK_LANE_NUMBER_4 = 4,
 *     };
 *
 *     enum v4l2_ext_displayport_link_rate
 *     {
 *         V4L2_EXT_DISPLAYPORT_LINK_RATE_HBR    = 27,
 *         V4L2_EXT_DISPLAYPORT_LINK_RATE_HBR2   = 54,
 *         V4L2_EXT_DISPLAYPORT_LINK_RATE_HBR3   = 81,
 *         V4L2_EXT_DISPLAYPORT_LINK_RATE_UHBR10 = 100,
 *         V4L2_EXT_DISPLAYPORT_LINK_RATE_UHBR13 = 135,
 *         V4L2_EXT_DISPLAYPORT_LINK_RATE_UHBR20 = 200,
 *     };
 *
 *     #define V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT 4
 *
 *     struct v4l2_ext_displayport_phy_status
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         unsigned char lock_status;
 *         unsigned int stream_clock_khz;
 *
 *         enum v4l2_ext_displayport_mode mode;
 *         enum v4l2_ext_displayport_link_lane_number lane_number;
 *         enum v4l2_ext_displayport_link_rate link_rate;
 *
 *         unsigned int ctle_eq_min_range[V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT];
 *         unsigned int ctle_eq_max_range[V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT];
 *         unsigned int ctle_eq_result[V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT];
 *         unsigned int error[V4L2_EXT_DISPLAYPORT_MAX_LANE_COUNT];
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get DisplayPort PHY status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_phy_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_displayport_phy_status));
 *
 *     status.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_PHY_STATUS;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_phy_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_PHY_STATUS                                    \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 100)

/**
 * @brief Get DisplayPort Link status
 *
 * @rst
 * Functional Requirements
 *   This control returns DisplayPort Link status. This information is used in
 * DisplayPort diagnostics menu.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   From webOS23, it should be returned within 10 msec.
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
 *     VIDIOC_G_EXT_CTRLS      // Get DISPLAYPORT Link status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_LINK_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     struct v4l2_ext_displayport_link_status
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         unsigned char hpd;
 *         unsigned char source_detection;
 *         unsigned char rx_sense;
 *         unsigned int frame_rate_x100_hz;
 *
 *         unsigned short video_htotal_measured;
 *         unsigned short video_vtotal_measured;
 *
 *         unsigned short video_width_measured;
 *         unsigned short video_height_measured;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get DisplayPort Link status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_link_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_displayport_link_status));
 *
 *     status.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_LINK_STATUS;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_link_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_LINK_STATUS                                   \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 101)

/**
 * @brief Get DisplayPort HDCP status
 *
 * @rst
 * Functional Requirements
 *   This control returns DisplayPort HDCP status. This information is used in
 * DisplayPort diagnostics menu.
 *
 * Responses to abnormal situations, including
 *   If HDCP status is not authenticated or off, hdcp_version should be set to
 * V4L2_EXT_DISPLAYPORT_HDCP_VERSION_RESERVED.
 *
 * Performance Requirements
 *   From webOS23, it should be returned within 10 msec.
 *
 * Constraints
 *   HDCP behavior on disabled ports should not affect Active Port and other
 * ports.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get DisplayPort HDCP status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_HDCP_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port
 *     {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_hdcp_auth_status
 *     {
 *         V4L2_EXT_DISPLAYPORT_HDCP_AUTH_STATUS_NO_TX_CONNECTED = 0,
 *         V4L2_EXT_DISPLAYPORT_HDCP_AUTH_STATUS_UNAUTHENTICATED = 1,
 *         V4L2_EXT_DISPLAYPORT_HDCP_AUTH_STATUS_IN_PROGRESS     = 2,
 *         V4L2_EXT_DISPLAYPORT_HDCP_AUTH_STATUS_AUTHENTICATED   = 3,
 *     };
 *
 *     struct v4l2_ext_displayport_hdcp14_status
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         unsigned char An[8];
 *         unsigned char Aksv[5];
 *         unsigned char Bksv[5];
 *         unsigned char Ri[2];
 *         unsigned char Bcaps;
 *         unsigned char Bstatus[2];
 *     };
 *
 *     struct v4l2_ext_displayport_hdcp_status
 *     {
 *         enum v4l2_ext_displayport_input_port port;
 *         enum v4l2_ext_displayport_hdcp_version hdcp_version;
 *         enum v4l2_ext_displayport_hdcp_auth_status auth_status;
 *         unsigned char encEn;
 *         struct v4l2_ext_displayport_hdcp14_status hdcp14_status;
 *     };
 *
 * Return Value
 *   On success, 0 is returned.
 *
 *   On error, -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *   This control id supports VIDIOC_G_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Get DisplayPort HDCP status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_hdcp_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_displayport_hdcp_status));
 *
 *     status.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_HDCP_STATUS;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_hdcp_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_HDCP_STATUS                                   \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 102)

/**
 * @brief Set DisplayPort Expert setting
 *
 * @rst
 * Functional Requirements
 *   This function is used to change various DisplayPort BSP parameters
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   From webOS23, it should be returned within 10 msec.
 *
 * Constraints
 *   If this function is not called, BSP must operate at its default value.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set DisplayPort Expert setting
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_EXPERT_SETTING
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_expert_setting_type {
 *         V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_MANUAL_EQ_MODE,
 *         V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_DISABLE_HDCP14,
 *         V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_DISABLE_HDCP22,
 *         V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_REAUTH_HDCP22,
 *     };
 *
 *     struct v4l2_ext_displayport_expert_setting {
 *         enum v4l2_ext_displayport_input_port port;
 *         enum v4l2_ext_displayport_expert_setting_type type;
 *         unsigned int param1;
 *         unsigned int param2;
 *         unsigned int param3;
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
 *   Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set DisplayPort Expert Setting
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_expert_setting setting;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&setting, 0, sizeof(struct v4l2_ext_displayport_expert_setting));
 *
 *     setting.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     setting.type = V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_MANUAL_EQ_MODE;
 *     setting.param1 = 1;   1 means true and 0 means false
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_EXPERT_SETTING;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_expert_setting);
 *     ext_controls.controls->ptr = (void *)&setting;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
  *     // Get DisplayPort Expert Setting
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_expert_setting setting;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&setting, 0, sizeof(struct v4l2_ext_displayport_expert_setting));
 *
 *     setting.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     setting.type = V4L2_EXT_DISPLAYPORT_EXPERT_SETTING_TYPE_MANUAL_EQ_MODE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_EXPERT_SETTING;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_displayport_expert_setting);
 *     ext_controls.controls->ptr = (void *)&setting;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */

#define V4L2_CID_EXT_DISPLAYPORT_EXPERT_SETTING                                \
  (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 103)

/**
 * @brief Set DisplayPort External DPCD setting
 *
 * @rst
 * Functional Requirements
 *   This function is enables/disables Gsync on source device.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   From webOS24, it should be returned within 10 msec.
 *   If this function controls Gsync, it must control source device.
 *
 * Constraints
 *   After disabling/enabling adaptive sync by this function, it requires setting HPD Low/High again to take effect.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS      // Set DisplayPort External DPCD setting
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_DISPLAYPORT_EXTERNAL_DPCD_SETTING
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_displayport_input_port {
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_1,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_2,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_3,
 *         V4L2_EXT_DISPLAYPORT_INPUT_PORT_4,
 *     };
 *
 *     enum v4l2_ext_displayport_external_dpcd_setting_type {
 *         V4L2_EXT_DISPLAYPORT_EXTERNAL_DPCD_SETTING_TYPE_GSYNC,
 *         V4L2_EXT_DISPLAYPORT_EXTERNAL_DPCD_SETTING_TYPE_MAXIMUM
 *     };
 *
 *     struct v4l2_ext_displayport_external_dpcd_setting {
 *         enum v4l2_ext_displayport_input_port port;
 *         enum v4l2_ext_displayport_external_dpcd_setting_type type;
 *         unsigned int param1;
 *         unsigned int param2;
 *         unsigned int param3;
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
 * Example
 *   .. code-block:: cpp
 *
 *     // Set DisplayPort External DPCD Setting
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_displayport_external_dpcd setting setting;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&setting, 0, sizeof(struct v4l2_ext_displayport_external_dpcd_setting));
 *
 *     setting.port = V4L2_EXT_DISPLAYPORT_INPUT_PORT_1;
 *     setting.type = V4L2_EXT_DISPLAYPORT_EXTERNAL_DPCD_SETTING_TYPE_GSYNC;
 *     setting.param1 = 1;   1 means true and 0 means false
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_DISPLAYPORT_EXTERNAL_DPCD_SETTING;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_displayport_external_dpcd_setting);
 *     ext_controls.controls->ptr = (void *)&setting;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_DISPLAYPORT_EXTERNAL_DPCD_SETTING (V4L2_CID_USER_EXT_DISPLAYPORT_BASE + 104)

#endif
