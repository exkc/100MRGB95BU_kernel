/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018~2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_HDMI_H
#define _V4L2_EXT_HDMI_H

#include <linux/v4l2-controls.h>
#include <linux/v4l2-ext/v4l2-ext-picturequality.h> /* It defines v4l2_ext_hdr_mode */
#include <linux/v4l2-ext/v4l2-ext-vsc.h> /* It defines v4l2_ext_video_rect */

#define V4L2_EXT_DEV_NO_HDMI 12

#define V4L2_EXT_DEV_PATH_HDMI "/dev/video12"

#define V4L2_CID_USER_EXT_HDMI_BASE (V4L2_CID_USER_BASE + 0x5000)

#define V4L2_EXT_HDMI_PACKET_DATA_LENGTH 28
#define V4L2_EXT_HDMI_INFOFRAME_PACKET_LEN 28
#define V4L2_EXT_HDMI_VENDOR_SPECIFIC_REGID_LEN 3
#define V4L2_EXT_HDMI_VENDOR_SPECIFIC_PAYLOAD_LEN                              \
  (V4L2_EXT_HDMI_INFOFRAME_PACKET_LEN - V4L2_EXT_HDMI_VENDOR_SPECIFIC_REGID_LEN)

#define V4L2_EXT_HDMI_SPD_IF_VENDOR_LEN 8
#define V4L2_EXT_HDMI_SPD_IF_DESC_LEN 16
#define V4L2_EXT_HDMI_TMDS_CH_NUM 4

enum v4l2_ext_hdmi_input_port {
  V4L2_EXT_HDMI_INPUT_PORT_NONE = 0, /**< enum value none */
  V4L2_EXT_HDMI_INPUT_PORT_1,        /**< enum value port1 */
  V4L2_EXT_HDMI_INPUT_PORT_2,        /**< enum value port2 */
  V4L2_EXT_HDMI_INPUT_PORT_3,        /**< enum value port3 */
  V4L2_EXT_HDMI_INPUT_PORT_4,        /**< enum value port4 */
  V4L2_EXT_HDMI_INPUT_PORT_5,        /**< enum value port5 */
  V4L2_EXT_HDMI_INPUT_PORT_ALL,      /**< enum value all */
};

enum v4l2_ext_hdmi_mode {
  V4L2_EXT_HDMI_MODE_DVI = 0, /**< enum value dvi */
  V4L2_EXT_HDMI_MODE_HDMI,    /**< enum value hdmi */
};

enum v4l2_ext_hdmi_color_depth {
  V4L2_EXT_HDMI_COLOR_DEPTH_8BIT = 0, /**< enum value 8bit */
  V4L2_EXT_HDMI_COLOR_DEPTH_10BIT,    /**< enum value 10bit */
  V4L2_EXT_HDMI_COLOR_DEPTH_12BIT,    /**< enum value 12bit  */
  V4L2_EXT_HDMI_COLOR_DEPTH_16BIT,    /**< enum value 16bit  */
  V4L2_EXT_HDMI_COLOR_DEPTH_RESERVED  /**< enum value reserved */
};

struct v4l2_ext_hdmi_timing_info {
  enum v4l2_ext_hdmi_input_port port;
  unsigned short h_freq;
  unsigned short v_vreq;
  unsigned short h_total;
  unsigned short v_total;
  unsigned short h_porch;
  unsigned short v_porch;
  struct v4l2_ext_video_rect active;
  unsigned short scan_type;
  enum v4l2_ext_hdmi_mode dvi_hdmi;
  enum v4l2_ext_hdmi_color_depth color_depth;
  unsigned char allm_mode;
};

enum v4l2_ext_hdmi_override_eotf {
  V4L2_EXT_HDMI_OVERRIDE_EOTF_SDR_LUMINANCE_RANGE = 0,
  V4L2_EXT_HDMI_OVERRIDE_EOTF_HDR_LUMINANCE_RANGE,
  V4L2_EXT_HDMI_OVERRIDE_EOTF_SMPTE_ST_2084,
  V4L2_EXT_HDMI_OVERRIDE_EOTF_HLG,
  V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_4,
  V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_5,
  V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_6,
  V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_7,
  V4L2_EXT_HDMI_OVERRIDE_EOTF_AUTO,
};

struct v4l2_ext_hdmi_override_drm_info {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_override_eotf override_eotf;
};

enum v4l2_ext_hdmi_drm_eotf {
  V4L2_EXT_HDMI_DRM_EOTF_SDR_LUMINANCE_RANGE =
      0, /**< enum value sdr luminance range */
  V4L2_EXT_HDMI_DRM_EOTF_HDR_LUMINANCE_RANGE, /**< enum value hdr luminance
                                                 range */
  V4L2_EXT_HDMI_DRM_EOTF_SMPTE_ST_2084,       /**< enum value smpte st 2084 */
  V4L2_EXT_HDMI_DRM_EOTF_HLG,                 /**< enum value hlg */
  V4L2_EXT_HDMI_DRM_EOTF_RESERVED_4,          /**< enum value reserved */
  V4L2_EXT_HDMI_DRM_EOTF_RESERVED_5,          /**< enum value reserved */
  V4L2_EXT_HDMI_DRM_EOTF_RESERVED_6,          /**< enum value reserved */
  V4L2_EXT_HDMI_DRM_EOTF_RESERVED_7,          /**< enum value reserved */
};

enum v4l2_ext_hdmi_drm_meta_desc {
  V4L2_EXT_HDMI_DRM_META_DESC_TYPE1 = 0,
  V4L2_EXT_HDMI_DRM_META_DESC_RESERVED1,
  V4L2_EXT_HDMI_DRM_META_DESC_RESERVED2,
  V4L2_EXT_HDMI_DRM_META_DESC_RESERVED3,
  V4L2_EXT_HDMI_DRM_META_DESC_RESERVED4,
  V4L2_EXT_HDMI_DRM_META_DESC_RESERVED5,
  V4L2_EXT_HDMI_DRM_META_DESC_RESERVED6,
  V4L2_EXT_HDMI_DRM_META_DESC_RESERVED7,
};

struct v4l2_ext_hdmi_drm_info {
  enum v4l2_ext_hdmi_input_port port;
  unsigned char version;
  unsigned char length;
  enum v4l2_ext_hdmi_drm_eotf eotf_type;
  enum v4l2_ext_hdmi_drm_meta_desc meta_desc;
  unsigned short display_primaries_x0;
  unsigned short display_primaries_y0;
  unsigned short display_primaries_x1;
  unsigned short display_primaries_y1;
  unsigned short display_primaries_x2;
  unsigned short display_primaries_y2;
  unsigned short white_point_x;
  unsigned short white_point_y;
  unsigned short max_display_mastering_luminance;
  unsigned short min_display_mastering_luminance;
  unsigned short maximum_content_light_level;
  unsigned short maximum_frame_average_light_level;
};

struct v4l2_ext_hdmi_hpd_low_duration_dc_on {
  enum v4l2_ext_hdmi_input_port port;
  int hpd_low_duration;
};

enum v4l2_ext_hdmi_vsi_video_format {
  V4L2_EXT_HDMI_VSI_VIDEO_FORMAT_NO_ADDITIONAL_FORMAT = 0,
  V4L2_EXT_HDMI_VSI_VIDEO_FORMAT_EXTENDED_RESOLUTION_FORMAT,
  V4L2_EXT_HDMI_VSI_VIDEO_FORMAT_3D_FORMAT,
};

enum v4l2_ext_hdmi_vsi_3d_structure {
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_FRAME_PACKING = 0,
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_FIELD_ALTERNATIVE,
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_LINE_ALTERNATIVE,
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_FULL,
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_L_DEPTH,
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_L_DEPTH_GRAPHICS,
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_TOP_BOTTOM,
  /*reserved 7*/
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_HALF = 0x08,
  V4L2_EXT_HDMI_VSI_3D_STRUCTURE_TOP_BOTTOM_DIRECTV = 0x09,
};

enum v4l2_ext_hdmi_vsi_3d_ext_data {
  V4L2_EXT_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_0 = 0,
  V4L2_EXT_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_1,
  V4L2_EXT_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_2,
  V4L2_EXT_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_3,
  V4L2_EXT_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_0,
  V4L2_EXT_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_1,
  V4L2_EXT_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_2,
  V4L2_EXT_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_3,
};

enum v4l2_ext_hdmi_vsi_vic {
  V4L2_EXT_HDMI_VSI_VIC_RESERVED = 0,
  V4L2_EXT_HDMI_VSI_VIC_4K2K_30HZ,
  V4L2_EXT_HDMI_VSI_VIC_4K2K_25HZ,
  V4L2_EXT_HDMI_VSI_VIC_4K2K_24HZ,
  V4L2_EXT_HDMI_VSI_VIC_4K2K_24HZ_SMPTE,
};

enum v4l2_ext_hdmi_packet_status {
  V4L2_EXT_HDMI_PACKET_STATUS_NOT_RECEIVED = 0,
  V4L2_EXT_HDMI_PACKET_STATUS_STOPPED,
  V4L2_EXT_HDMI_PACKET_STATUS_UPDATED,
};

struct v4l2_ext_hdmi_in_packet {
  unsigned char type;
  unsigned char version;
  unsigned char length;
  unsigned char data_bytes[V4L2_EXT_HDMI_PACKET_DATA_LENGTH];
};

struct v4l2_ext_hdmi_vsi_info {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_vsi_video_format video_format;
  enum v4l2_ext_hdmi_vsi_3d_structure st_3d;
  enum v4l2_ext_hdmi_vsi_3d_ext_data ext_data_3d;
  enum v4l2_ext_hdmi_vsi_vic vic;
  unsigned char regid[V4L2_EXT_HDMI_VENDOR_SPECIFIC_REGID_LEN];
  unsigned char payload[V4L2_EXT_HDMI_VENDOR_SPECIFIC_PAYLOAD_LEN];
  enum v4l2_ext_hdmi_packet_status packet_status;
  struct v4l2_ext_hdmi_in_packet packet;
};

struct v4l2_ext_hdmi_spd_info {
  enum v4l2_ext_hdmi_input_port port;
  unsigned char vendor_name[V4L2_EXT_HDMI_SPD_IF_VENDOR_LEN + 1];
  unsigned char product_description[V4L2_EXT_HDMI_SPD_IF_DESC_LEN + 1];
  unsigned char source_device_info;
  enum v4l2_ext_hdmi_packet_status packet_status;
  struct v4l2_ext_hdmi_in_packet packet;
};

enum v4l2_ext_hdmi_avi_csc {
  V4L2_EXT_HDMI_AVI_CSC_RGB = 0,
  V4L2_EXT_HDMI_AVI_CSC_YCBCR422,
  V4L2_EXT_HDMI_AVI_CSC_YCBCR444,
  V4L2_EXT_HDMI_AVI_CSC_YCBCR420,
};

enum v4l2_ext_hdmi_avi_active_info {
  V4L2_EXT_HDMI_AVI_ACTIVE_INFO_INVALID = 0,
  V4L2_EXT_HDMI_AVI_ACTIVE_INFO_VALID,
};

enum v4l2_ext_hdmi_avi_bar_info {
  V4L2_EXT_HDMI_AVI_BAR_INFO_INVALID = 0,
  V4L2_EXT_HDMI_AVI_BAR_INFO_VERTICALVALID,
  V4L2_EXT_HDMI_AVI_BAR_INFO_HORIZVALID,
  V4L2_EXT_HDMI_AVI_BAR_INFO_VERTHORIZVALID,
};

enum v4l2_ext_hdmi_avi_scan_info {
  V4L2_EXT_HDMI_AVI_SCAN_INFO_NODATA = 0,
  V4L2_EXT_HDMI_AVI_SCAN_INFO_OVERSCANNED,
  V4L2_EXT_HDMI_AVI_SCAN_INFO_UNDERSCANNED,
  V4L2_EXT_HDMI_AVI_SCAN_INFO_FUTURE,
};

enum v4l2_ext_hdmi_avi_colorimetry {
  V4L2_EXT_HDMI_AVI_COLORIMETRY_NODATA = 0,
  V4L2_EXT_HDMI_AVI_COLORIMETRY_SMPTE170,
  V4L2_EXT_HDMI_AVI_COLORIMETRY_ITU709,
  V4L2_EXT_HDMI_AVI_COLORIMETRY_FUTURE,
  V4L2_EXT_HDMI_AVI_COLORIMETRY_EXTENDED = V4L2_EXT_HDMI_AVI_COLORIMETRY_FUTURE,

};

enum v4l2_ext_hdmi_avi_picture_arc {
  V4L2_EXT_HDMI_AVI_PICTURE_ARC_NODATA = 0,
  V4L2_EXT_HDMI_AVI_PICTURE_ARC_4_3,
  V4L2_EXT_HDMI_AVI_PICTURE_ARC_16_9,
  V4L2_EXT_HDMI_AVI_PICTURE_ARC_FUTURE,
};

enum v4l2_ext_hdmi_avi_active_format_arc {
  V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_PICTURE = 8,
  V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_4_3CENTER = 9,
  V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_16_9CENTER = 10,
  V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_14_9CENTER = 11,
  V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_OTHER = 0,
};

enum v4l2_ext_hdmi_avi_scaling {
  V4L2_EXT_HDMI_AVI_SCALING_NOSCALING = 0,
  V4L2_EXT_HDMI_AVI_SCALING_HSCALING,
  V4L2_EXT_HDMI_AVI_SCALING_VSCALING,
  V4L2_EXT_HDMI_AVI_SCALING_HVSCALING,
};

enum v4l2_ext_hdmi_avi_it_content {
  V4L2_EXT_HDMI_AVI_IT_CONTENT_NODATA = 0,
  V4L2_EXT_HDMI_AVI_IT_CONTENT_ITCONTENT,
};

enum v4l2_ext_hdmi_avi_ext_colorimetry {
  V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_XVYCC601 = 0,
  V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_XVYCC709,
  V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_SYCC601,
  V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_ADOBEYCC601,
  V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_ADOBERGB,
  V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_BT2020_YCCBCCRC,
  V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_BT2020_RGBORYCBCR,
  V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_XVRESERED,
};

enum v4l2_ext_hdmi_avi_rgb_quantization_range {
  V4L2_EXT_HDMI_AVI_RGB_QUANTIZATION_RANGE_DEFAULT = 0,
  V4L2_EXT_HDMI_AVI_RGB_QUANTIZATION_RANGE_LIMITEDRANGE,
  V4L2_EXT_HDMI_AVI_RGB_QUANTIZATION_RANGE_FULLRANGE,
  V4L2_EXT_HDMI_AVI_RGB_QUANTIZATION_RANGE_RESERVED,
};

enum v4l2_ext_hdmi_avi_ycc_quantization_range {
  V4L2_EXT_HDMI_AVI_YCC_QUANTIZATION_RANGE_LIMITEDRANGE = 0,
  V4L2_EXT_HDMI_AVI_YCC_QUANTIZATION_RANGE_FULLRANGE,
  V4L2_EXT_HDMI_AVI_YCC_QUANTIZATION_RANGE_RESERVED,
};

enum v4l2_ext_hdmi_avi_content_type {
  V4L2_EXT_HDMI_AVI_CONTENT_TYPE_GRAPHICS = 0,
  V4L2_EXT_HDMI_AVI_CONTENT_TYPE_PHOTO,
  V4L2_EXT_HDMI_AVI_CONTENT_TYPE_CINEMA,
  V4L2_EXT_HDMI_AVI_CONTENT_TYPE_GAME,
};

enum v4l2_ext_hdmi_avi_additional_colorimetry {
  V4L2_EXT_HDMI_AVI_ADDITIONAL_COLORIMETRY_DCI_P3_D65 = 0,
  V4L2_EXT_HDMI_AVI_ADDITIONAL_COLORIMETRY_DCI_P3_THEATER,
  V4L2_EXT_HDMI_AVI_ADDITIONAL_COLORIMETRY_RESERVED,
};

struct v4l2_ext_hdmi_avi_info {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_mode mode;

  enum v4l2_ext_hdmi_avi_csc pixel_encoding;
  enum v4l2_ext_hdmi_avi_active_info active_info;
  enum v4l2_ext_hdmi_avi_bar_info bar_info;
  enum v4l2_ext_hdmi_avi_scan_info scan_info;
  enum v4l2_ext_hdmi_avi_colorimetry colorimetry;
  enum v4l2_ext_hdmi_avi_picture_arc picture_aspect_ratio;
  enum v4l2_ext_hdmi_avi_active_format_arc active_format_aspect_ratio;
  enum v4l2_ext_hdmi_avi_scaling scaling;

  unsigned char vic;
  unsigned char pixel_repeat;

  enum v4l2_ext_hdmi_avi_it_content it_content;
  enum v4l2_ext_hdmi_avi_ext_colorimetry extended_colorimetry;
  enum v4l2_ext_hdmi_avi_rgb_quantization_range rgb_quantization_range;
  enum v4l2_ext_hdmi_avi_ycc_quantization_range ycc_quantization_range;
  enum v4l2_ext_hdmi_avi_content_type content_type;
  enum v4l2_ext_hdmi_avi_additional_colorimetry additional_colorimetry;

  unsigned short top_bar_end_line_number;
  unsigned short bottom_bar_start_line_number;
  unsigned short left_bar_end_pixel_number;
  unsigned short right_bar_end_pixel_number;

  enum v4l2_ext_hdmi_packet_status packet_status;
  struct v4l2_ext_hdmi_in_packet packet;
};

struct v4l2_ext_hdmi_packet_info {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_mode mode;
  struct v4l2_ext_hdmi_avi_info avi;
  struct v4l2_ext_hdmi_spd_info spd;
  struct v4l2_ext_hdmi_vsi_info vsi;
};

enum v4l2_ext_hdmi_dolby_hdr_type {
  V4L2_EXT_HDMI_DOLBY_HDR_TYPE_SDR = 0,
  V4L2_EXT_HDMI_DOLBY_HDR_TYPE_STANDARD_VSIF_1,
  V4L2_EXT_HDMI_DOLBY_HDR_TYPE_STANDARD_VSIF_2,
  V4L2_EXT_HDMI_DOLBY_HDR_TYPE_LOW_LATENCY,
  V4L2_EXT_HDMI_DOLBY_HDR_TYPE_DOLBY_VISION_PC,
};

struct v4l2_ext_hdmi_dolby_hdr {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_dolby_hdr_type type;
};

enum v4l2_ext_hdmi_edid_size {
  V4L2_EXT_HDMI_EDID_SIZE_128 = 0,
  V4L2_EXT_HDMI_EDID_SIZE_256,
  V4L2_EXT_HDMI_EDID_SIZE_512,
};

struct v4l2_ext_hdmi_edid {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_edid_size size;
  union {
    unsigned char *pData;
    unsigned int compat_data;
    unsigned long long sizer;
  };
};

struct v4l2_ext_hdmi_connection_state {
  enum v4l2_ext_hdmi_input_port port;
  unsigned char state;
};

enum v4l2_ext_hdmi_hpd_state {
  V4L2_EXT_HDMI_HPD_DISABLE = 0,
  V4L2_EXT_HDMI_HPD_ENABLE,
  V4L2_EXT_HDMI_HPD_RESTART,
};

struct v4l2_ext_hdmi_hpd {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_hpd_state hpd_state;
};

enum v4l2_ext_hdmi_hdcp_version {
  V4L2_EXT_HDMI_HDCP_VERSION_14 = 0,
  V4L2_EXT_HDMI_HDCP_VERSION_22,
  V4L2_EXT_HDMI_HDCP_VERSION_RESERVED,
};

struct v4l2_ext_hdmi_hdcp_key {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_hdcp_version version;
  unsigned int key_size;
  union {
    unsigned char *pData;
    unsigned int compat_data;
    unsigned long long sizer;
  };
};

struct v4l2_ext_hdmi_vrr_frequency {
  enum v4l2_ext_hdmi_input_port port;
  unsigned short frequency;
};

enum v4l2_ext_hdmi_emp_type {
  V4L2_EXT_HDMI_EMP_TYPE_UNDEFINED = 0,
  V4L2_EXT_HDMI_EMP_TYPE_VSEM,
  V4L2_EXT_HDMI_EMP_TYPE_DYNAMICHDREM,
  V4L2_EXT_HDMI_EMP_TYPE_VTEM,
  V4L2_EXT_HDMI_EMP_TYPE_CVTEM
};

struct v4l2_ext_hdmi_emp_info {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_emp_type type;
  unsigned short current_packet_index;
  unsigned short total_packet_number;
  unsigned char data[31];
};

struct v4l2_ext_hdmi_hdcp_repeater {
  enum v4l2_ext_hdmi_input_port port;
  unsigned char repeater_mode;
  unsigned char receiver_id[5];
  unsigned char repeater_hpd;
};

struct v4l2_ext_hdmi_hdcp_repeater_topology {
  enum v4l2_ext_hdmi_input_port port; // HDMI port number
  unsigned char repeater_mode;        // 0 : receiver, 1 : repeater
  unsigned char count;                // Number of devices
  unsigned char depth;                // Depth of connected device
  unsigned char receiver_id[32][5];   // RX IO of connected device
  unsigned char repeater_hpd;         // HPD control
  unsigned int msg_id; // Increase by 1 when it changes any value(init value =0,
                       // default set value = 1)
};

enum v4l2_ext_hdmi_hdcp_repeater_stream_manage_transmit {
  STREAM_MANAGE_TRANSMIT_ALLOW,
  STREAM_MANAGE_TRANSMIT_DENY,
  STREAM_MANAGE_RESERVED,
};

struct v4l2_ext_hdmi_hdcp_repeater_stream_manage {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_hdcp_repeater_stream_manage_transmit
      value; // 0 or 1 or reserved
};

// HDMI Capabilities Flags
// The HDMI device supports HDCP1.4 Key. So, need to write HDCP1.4 key to
// driver.
#define V4L2_EXT_HDMI_HDCP14                                                   \
  ((unsigned long long)0x1 << 0) // 0x0000000000000001
// HDCP1.4 Key is OTP on Soc. So, No need to download HDCP1.4 Key to secure
// storage.
#define V4L2_EXT_HDMI_HDCP14_KEY_OTP                                           \
  ((unsigned long long)0x1 << 1) // 0x0000000000000002

// The HDMI device supports HDCP2.3 key. So, need to write HDCP2.3 key to
// driver.
// HDCP2.2 key is include in HDCP2.3 key.
#define V4L2_EXT_HDMI_HDCP23                                                   \
  ((unsigned long long)0x1 << 2) // 0x0000000000000004
// HDCP2.3(HDCP2.2) Key is OTP on Soc. So, No need to download HDCP2.3(HDCP2.2)
// Key to secure storage.
#define V4L2_EXT_HDMI_HDCP23_KEY_OTP                                           \
  ((unsigned long long)0x1 << 3) // 0x0000000000000008

// The HDMI device supports HDMI1.4 Specification
#define V4L2_EXT_HDMI_HDMI14                                                   \
  ((unsigned long long)0x1 << 12) // 0x0000000000001000
// The HDMI device supports HDMI2.0 Specification
#define V4L2_EXT_HDMI_HDMI20                                                   \
  ((unsigned long long)0x1 << 13) // 0x0000000000002000
// The HDMI device supports HDMI2.1 Specification.
// Set this flag even if the device supports one feature in the HDMI2.1
// specification.
#define V4L2_EXT_HDMI_HDMI21                                                   \
  ((unsigned long long)0x1 << 14) // 0x0000000000004000

// The HDMI device supports TMDS 3.4Gbps per Channel
#define V4L2_EXT_HDMI_TMDS_3G                                                  \
  ((unsigned long long)0x1 << 20) // 0x0000000000100000
// The HDMI device supports TMDS 6.0Gbps per Channel
#define V4L2_EXT_HDMI_TMDS_6G                                                  \
  ((unsigned long long)0x1 << 21) // 0x0000000000200000
// The HDMI device supports FRL 3Gbps per Lane on 3 Lanes(0,1, and 2)
#define V4L2_EXT_HDMI_FRL_3L_3G                                                \
  ((unsigned long long)0x1 << 22) // 0x0000000000400000
// The HDMI device supports FRL 6Gbps per Lane on 3 Lanes(0,1, and 2)
#define V4L2_EXT_HDMI_FRL_3L_6G                                                \
  ((unsigned long long)0x1 << 23) // 0x0000000000800000
// The HDMI device supports FRL 6Gbps per Lane on 4 Lanes(0,1, 2, and 3)
#define V4L2_EXT_HDMI_FRL_4L_6G                                                \
  ((unsigned long long)0x1 << 24) // 0x0000000001000000
// The HDMI device supports FRL 8Gbps per Lane on 4 Lanes(0,1, 2, and 3)
#define V4L2_EXT_HDMI_FRL_4L_8G                                                \
  ((unsigned long long)0x1 << 25) // 0x0000000002000000
// The HDMI device supports FRL 10Gbps per Lane on 4 Lanes(0,1, 2, and 3)
#define V4L2_EXT_HDMI_FRL_4L_10G                                               \
  ((unsigned long long)0x1 << 26) // 0x0000000004000000
// The HDMI device supports FRL 12Gbps per Lane on 4 Lanes(0,1, 2, and 3)
#define V4L2_EXT_HDMI_FRL_4L_12G                                               \
  ((unsigned long long)0x1 << 27) // 0x0000000008000000

// The HDMI device supports background timing detection.
// It means that driver can get HDMI signal information(timing, SPD, AVI,
// etc...) without watching HDMI port.
// If the HDMI device supports background timing detection, it also support fast
// switching between HDMI ports.
#define V4L2_EXT_HDMI_BACKGROUND_TIMING_DETECT                                 \
  ((unsigned long long)0x1 << 28) // 0x0000000010000000

// The HDMI device supports FVA
#define V4L2_EXT_HDMI_FVA ((unsigned long long)0x1 << 29) // 0x0000000020000000
// The HDMI device supports VRR
#define V4L2_EXT_HDMI_VRR ((unsigned long long)0x1 << 30) // 0x0000000040000000
// The HDMI device supports CinemaVRR
#define V4L2_EXT_HDMI_CINEMAVRR                                                \
  ((unsigned long long)0x1 << 31) // 0x0000000080000000

// The HDMI device supports  Dolby vision
#define V4L2_EXT_HDMI_DOLBY_VISION                                             \
  ((unsigned long long)0x1 << 32) // 0x0000000100000000
// The HDMI device supports  Dolby vision low latency mode
#define V4L2_EXT_HDMI_DOLBY_VISION_LL                                          \
  ((unsigned long long)0x1 << 33) // 0x0000000200000000
// The HDMI device supports  Dolby vision on HDMI2.1
#define V4L2_EXT_HDMI_DOLBY_VISION_HDMI21                                      \
  ((unsigned long long)0x1 << 34) // 0x0000000400000000
// The HDMI device supports 512bytes EDID
#define V4L2_EXT_HDMI_512BYTE_EDID                                             \
  ((unsigned long long)0x1 << 35) // 0x0000000800000000
// The HDMI device supports EMPACKET
#define V4L2_EXT_HDMI_EMPACKET                                                 \
  ((unsigned long long)0x1 << 36) // 0x0000001000000000
// The HDMI device supports HDCP Repeater
#define V4L2_EXT_HDMI_HDCP_REPEATER                                            \
  ((unsigned long long)0x1 << 37) // 0x0000002000000000
// The HDMI device supports DSC
#define V4L2_EXT_HDMI_DSC ((unsigned long long)0x1 << 38) // 0x0000004000000000

struct v4l2_ext_hdmi_capability {
  unsigned char chip[16];          // chip name. for example "e60"
  unsigned int version;            // linuxtv header version
  unsigned long long capabilities; // HDMI Capabilities Flags
  unsigned long long reserved[3];
};

struct v4l2_ext_hdmi_querycap {
  enum v4l2_ext_hdmi_input_port port;
  struct v4l2_ext_hdmi_capability hdmi_capability;
};

enum v4l2_ext_hdmi_sleep_mode {
  V4L2_EXT_HDMI_SLEEP_MODE = 0,
  V4L2_EXT_HDMI_WAKEUP_MODE,
};

struct v4l2_ext_hdmi_sleep {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_sleep_mode mode;
};

enum v4l2_ext_hdmi_dpms_mode {
  V4L2_EXT_HDMI_DPMS_MODE_DISABLE = 0,
  V4L2_EXT_HDMI_DPMS_MODE_ENABLE,
  V4L2_EXT_HDMI_DPMS_MODE_ENABLE_DATA_CLK,
};

struct v4l2_ext_hdmi_dpms {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_dpms_mode mode;
};

/* HDMI DIAGNOSTICS */
enum v4l2_ext_hdmi_link_type {
  V4L2_EXT_HDMI_LINK_TYPE_TMDS = 0,
  V4L2_EXT_HDMI_LINK_TYPE_FRL,
};

enum v4l2_ext_hdmi_link_lane_number {
  V4L2_EXT_HDMI_LINK_LANE_NUMBER_3 = 3,
  V4L2_EXT_HDMI_LINK_LANE_NUMBER_4 = 4,
};

enum v4l2_ext_hdmi_link_rate {
  V4L2_EXT_HDMI_LINK_RATE_3G = 3,
  V4L2_EXT_HDMI_LINK_RATE_6G = 6,
  V4L2_EXT_HDMI_LINK_RATE_8G = 8,
  V4L2_EXT_HDMI_LINK_RATE_10G = 10,
  V4L2_EXT_HDMI_LINK_RATE_12G = 12,

};

struct v4l2_ext_hdmi_phy_status {
  enum v4l2_ext_hdmi_input_port port;
  unsigned char lock_status;
  unsigned int tmds_clk_khz;

  enum v4l2_ext_hdmi_link_type link_type;
  enum v4l2_ext_hdmi_link_lane_number link_lane;
  enum v4l2_ext_hdmi_link_rate link_rate;

  unsigned int ctle_eq_min_range[V4L2_EXT_HDMI_TMDS_CH_NUM];
  unsigned int ctle_eq_max_range[V4L2_EXT_HDMI_TMDS_CH_NUM];
  unsigned int ctle_eq_result[V4L2_EXT_HDMI_TMDS_CH_NUM];
  unsigned int error[V4L2_EXT_HDMI_TMDS_CH_NUM];
};

enum v4l2_ext_hdmi_audio_format {
  V4L2_EXT_HDMI_AUDIO_FORMAT_UNKNOWN = 0x00,
  V4L2_EXT_HDMI_AUDIO_FORMAT_PCM = 0x01,
  V4L2_EXT_HDMI_AUDIO_FORMAT_AC3 = 0x10,
  V4L2_EXT_HDMI_AUDIO_FORMAT_EAC3 = 0x11,
  V4L2_EXT_HDMI_AUDIO_FORMAT_EAC3_ATMOS = 0x12,
  V4L2_EXT_HDMI_AUDIO_FORMAT_MAT = 0x15,
  V4L2_EXT_HDMI_AUDIO_FORMAT_MAT_ATMOS = 0x16,
  V4L2_EXT_HDMI_AUDIO_FORMAT_TRUEHD = 0x17,
  V4L2_EXT_HDMI_AUDIO_FORMAT_TRUEHD_ATMOS = 0x18,
  V4L2_EXT_HDMI_AUDIO_FORMAT_AAC = 0x19,
  V4L2_EXT_HDMI_AUDIO_FORMAT_MPEG = 0x20,
  V4L2_EXT_HDMI_AUDIO_FORMAT_DTS = 0x30,
  V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_HD_MA = 0x31,
  V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_EXPRESS = 0x32,
  V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_CD = 0x33,
  V4L2_EXT_HDMI_AUDIO_FORMAT_NOAUDIO = 0x41,
};

struct v4l2_ext_hdmi_link_status {
  enum v4l2_ext_hdmi_input_port port;
  unsigned char hpd;
  unsigned char hdmi_5v;
  unsigned char rx_sense;
  unsigned int frame_rate_x100_hz;
  enum v4l2_ext_hdmi_mode dvi_hdmi_mode;

  unsigned short video_width;
  unsigned short video_height;
  enum v4l2_ext_hdmi_avi_csc color_space;
  unsigned char color_depth;
  enum v4l2_ext_hdmi_avi_colorimetry colorimetry;
  enum v4l2_ext_hdmi_avi_ext_colorimetry ext_colorimetry;
  enum v4l2_ext_hdmi_avi_additional_colorimetry additional_colorimetry;
  enum v4l2_ext_hdr_mode hdr_type;

  enum v4l2_ext_hdmi_audio_format audio_format;
  unsigned int audio_sampling_freq;
  unsigned char audio_channel_number;
};

struct v4l2_ext_hdmi_video_status {
  enum v4l2_ext_hdmi_input_port port;
  unsigned short video_width_real;
  unsigned short video_htotal_real;
  unsigned short video_height_real;
  unsigned short video_vtotal_real;
  unsigned int pixel_clock_khz;
  unsigned int current_vrr_refresh_rate;
};

struct v4l2_ext_hdmi_audio_status {
  enum v4l2_ext_hdmi_input_port port;
  unsigned int pcm_N;
  unsigned int pcm_CTS;
  unsigned char LayoutBitValue;
  unsigned char ChannelStatusBits;
};

enum v4l2_ext_hdmi_hdcp_auth_status {
  V4L2_EXT_HDMI_HDCP_AUTH_STATUS_NO_TX_CONNECTED = 0,
  V4L2_EXT_HDMI_HDCP_AUTH_STATUS_UNAUTHENTICATED = 1,
  V4L2_EXT_HDMI_HDCP_AUTH_STATUS_IN_PROGRESS = 2,
  V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED = 3,
};

struct v4l2_ext_hdmi_hdcp14_status {
  enum v4l2_ext_hdmi_input_port port;
  unsigned char An[8];
  unsigned char Aksv[5];
  unsigned char Bksv[5];
  unsigned char Ri[2];
  unsigned char Bcaps;
  unsigned char Bstatus[2];
};

struct v4l2_ext_hdmi_hdcp22_status {
  enum v4l2_ext_hdmi_input_port port;
  unsigned short ake_init_count_since_5v;
  unsigned short reauth_req_count_since_5v;
};

struct v4l2_ext_hdmi_hdcp_status {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_hdcp_version hdcp_version;
  enum v4l2_ext_hdmi_hdcp_auth_status auth_status;
  unsigned char encEn;
  struct v4l2_ext_hdmi_hdcp14_status hdcp14_status;
  struct v4l2_ext_hdmi_hdcp22_status hdcp22_status;
};

struct v4l2_ext_hdmi_scdc_status {
  enum v4l2_ext_hdmi_input_port port;
  unsigned char source_version;
  unsigned char sink_version;

  unsigned char rsed_update;
  unsigned char flt_update;
  unsigned char frl_start;
  unsigned char source_test_update;
  unsigned char rr_test;
  unsigned char ced_update;
  unsigned char status_update;

  unsigned char tmds_bit_clock_ratio;
  unsigned char scrambling_enable;
  unsigned char tmds_scrambler_status;

  unsigned char flt_no_retrain;
  unsigned char rr_enable;
  unsigned char ffe_levels;
  unsigned char frl_rate;

  unsigned char dsc_decode_fail;
  unsigned char flt_ready;
  unsigned char clk_detect;
  unsigned char ch0_locked;
  unsigned char ch1_locked;
  unsigned char ch2_locked;
  unsigned char ch3_locked;

  unsigned char lane0_ltp_request;
  unsigned char lane1_ltp_request;
  unsigned char lane2_ltp_request;
  unsigned char lane3_ltp_request;

  unsigned char ch0_ced_valid;
  unsigned char ch1_ced_valid;
  unsigned char ch2_ced_valid;
  unsigned char ch3_ced_valid;
  unsigned int ch0_ced;
  unsigned int ch1_ced;
  unsigned int ch2_ced;
  unsigned int ch3_ced;
  unsigned char rs_correction_valid;
  unsigned int rs_correcton_count;
};

struct v4l2_ext_hdmi_diagnostics_status {
  enum v4l2_ext_hdmi_input_port port;
  struct v4l2_ext_hdmi_link_status link_status;
  struct v4l2_ext_hdmi_phy_status phy_status;
  struct v4l2_ext_hdmi_video_status video_status;
  struct v4l2_ext_hdmi_audio_status audio_status;
  struct v4l2_ext_hdmi_hdcp_status hdcp_status;
  struct v4l2_ext_hdmi_scdc_status scdc_status;
};

enum v4l2_ext_hdmi_error_type {
  V4L2_EXT_HDMI_ERROR_TYPE_NONE = 0x0000,
  V4L2_EXT_HDMI_ERROR_TYPE_GCP_ERROR = 0x0001,
  V4L2_EXT_HDMI_ERROR_TYPE_HDCP22_REAUTH = 0x0002,
  V4L2_EXT_HDMI_ERROR_TYPE_TMDS_ERROR = 0x0004,
  V4L2_EXT_HDMI_ERROR_TYPE_PHY_LOW_RANGE = 0x0008,
  V4L2_EXT_HDMI_ERROR_TYPE_PHY_ABNORMAL = 0x0010,
  V4L2_EXT_HDMI_ERROR_TYPE_CED_ERROR = 0x0020,
  V4L2_EXT_HDMI_ERROR_TYPE_AUDIO_BUFFER = 0x0040,
  V4L2_EXT_HDMI_ERROR_TYPE_UNSTABLE_SYNC = 0x0080,
  V4L2_EXT_HDMI_ERROR_TYPE_BCH = 0x0100,
  V4L2_EXT_HDMI_ERROR_TYPE_FLT = 0x0200,
  V4L2_EXT_HDMI_ERROR_TYPE_FAILED = 0xFFFFFFFE,
};

struct v4l2_ext_hdmi_error_status {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_error_type error;
  unsigned int param1;
  unsigned int param2;
};

enum v4l2_ext_hdmi_expert_setting_type {
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_HPD_LOW_DURATION = 0,

  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_MODE,
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH0,
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH1,
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH2,
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH3,
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_EQ_PERIOD,

  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_VIDEO_STABLE_COUNT,
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_AUDIO_STABLE_COUNT,

  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_DISABLE_HDCP22,
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_REAUTH_HDCP22,

  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_ON_TO_RXSENSE_TIME,
  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_RXSENSE_TO_HPD_TIME,

  V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_PCB_SERIAL_RESISTOR
};

enum v4l2_ext_hdmi_pcb_serial_resistor {
  V4L2_EXT_HDMI_PCB_SERIAL_RESISTOR_WITH_0_OHM = 0,
  V4L2_EXT_HDMI_PCB_SERIAL_RESISTOR_WITH_5_OHM,
  V4L2_EXT_HDMI_PCB_SERIAL_RESISTOR_DEFAULT =
      V4L2_EXT_HDMI_PCB_SERIAL_RESISTOR_WITH_5_OHM
};

struct v4l2_ext_hdmi_expert_setting {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_expert_setting_type type;
  unsigned int param1;
  unsigned int param2;
  unsigned int param3;
};

enum v4l2_ext_hdmi_hdcp_hdmiout_auth_state {
	V4L2_EXT_HDMI_HDCP_HDMIOUT_AUTH_STATUS_NONE_AUTH = 0,
	V4L2_EXT_HDMI_HDCP_HDMIOUT_AUTH_STATUS_AUTH_DONE,
	V4L2_EXT_HDMI_HDCP_HDMIOUT_AUTH_STATUS_AUTH_IGNORE,
};

struct v4l2_ext_hdmi_hdcp_topology_status {
	enum v4l2_ext_hdmi_input_port port;
	enum v4l2_ext_hdmi_hdcp_version hdcp_version;
	enum v4l2_ext_hdmi_hdcp_hdmiout_auth_state auth_state;
	unsigned int topology_size;
	unsigned short hdcp14_status;
	unsigned short hdcp22_status;
	unsigned char *topology;
};

enum v4l2_ext_hdmi_edid_access_mode {
    V4L2_EXT_HDMI_EDID_ENABLE = 0,
    V4L2_EXT_HDMI_EDID_DISABLE,
};

struct v4l2_ext_hdmi_edid_access {
  enum v4l2_ext_hdmi_input_port port;
  enum v4l2_ext_hdmi_edid_access_mode mode;
};

//
// HDMI class control IDs
//

/**
 * @brief Get HDMI video timing info
 *
 * @rst
 * Functional Requirements
 *   This function gets HDMI video timing information to each port.
 *   When the V frequency is 0, other fields must be transferred as an initial
 * value.
 *
 *   When it supports HDMI2.1 VRR, BSP should support both TMDS and FRL for
 * FreeSync. When the FRL FreeSync signal is received, it should be displayed
 * without any problems.
 *
 *   For HDMI2.1 FRL signal, BSP shall be able to detect signal changes without
 * performing FRL link training again.
 *   For example, this may happen when the frame rate is changed from 50Hz to
 * 60Hz on RTX3080 PC. Most source devices cut off and output signal when
 * resolution changes.
 *   But RTX3080 PC outputs signal without blocking signal when pixel clock
 * remains the same. BSP should  detect signal change with  detecting VIC
 * fluctuations.
 *
 *   In HDMI2.1 VRR signal, v_freq value of v4l2_ext_hdmi_timing_info should use
 * base refresh rate instead of instant refresh rate.
 *
 * Responses to abnormal situations, including
 *   If SoC could detect video timing for the input signal, it should return the
 * information even if SoC could not hanldle the format.
 *   The H/V frequency boundary and the associated Enum for the HFR signal shall
 * be checked for problems.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Correct video timing information must be delivered independently for each
 * HDMI port in background mode.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI Timinginfo
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_TIMING_INFO
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
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
 *     enum v4l2_ext_hdmi_mode
 *     {
 *         V4L2_EXT_HDMI_MODE_DVI = 0,
 *         V4L2_EXT_HDMI_MODE_HDMI,
 *     };
 *
 *     enum v4l2_ext_hdmi_color_depth
 *     {
 *         V4L2_EXT_HDMI_COLOR_DEPTH_8BIT = 0,
 *         V4L2_EXT_HDMI_COLOR_DEPTH_10BIT,
 *         V4L2_EXT_HDMI_COLOR_DEPTH_12BIT,
 *         V4L2_EXT_HDMI_COLOR_DEPTH_16BIT,
 *         V4L2_EXT_HDMI_COLOR_DEPTH_RESERVED
 *     };
 *
 *     struct v4l2_ext_hdmi_timing_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned short h_freq;
 *         unsigned short v_freq;
 *         unsigned short h_total;
 *         unsigned short v_total;
 *         unsigned short h_porch;
 *         unsigned short v_porch;
 *         struct v4l2_ext_video_rect active;
 *         unsigned short scan_type;
 *         enum v4l2_ext_hdmi_mode dvi_hdmi;
 *         enum v4l2_ext_hdmi_color_depth color_depth;
 *         unsigned char allm_mode;
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
 *     // Get Video Timing Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_timing_info hdmi_timing_info;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdmi_timing_info, 0, sizeof(struct v4l2_ext_hdmi_timing_info));
 *
 *     hdmi_timing_info.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_TIMING_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_timing_info);
 *     ext_controls.controls->ptr = (void *)&hdmi_timing_info;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_TIMING_INFO (V4L2_CID_USER_EXT_HDMI_BASE + 0)

/**
 * @brief Get HDMI DRM info
 *
 * @rst
 * Functional Requirements
 *   This function returns DynamicRange & Metadata Infoframe data for HDR.
 *
 * Responses to abnormal situations, including
 *   If HDMI clock is unstable or vertical frequency is 0,
 * v4l2_ext_hdmi_drm_info should be cleared.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   webOS checks eotf_type, version and length field to know if it is valid.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI DRMInfo
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_DRM_INFO
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_drm_eotf
 *     {
 *         V4L2_EXT_HDMI_DRM_EOTF_SDR_LUMINANCE_RANGE = 0,
 *         V4L2_EXT_HDMI_DRM_EOTF_HDR_LUMINANCE_RANGE,
 *         V4L2_EXT_HDMI_DRM_EOTF_SMPTE_ST_2084,
 *         V4L2_EXT_HDMI_DRM_EOTF_HLG,
 *         V4L2_EXT_HDMI_DRM_EOTF_RESERVED_4,
 *         V4L2_EXT_HDMI_DRM_EOTF_RESERVED_5,
 *         V4L2_EXT_HDMI_DRM_EOTF_RESERVED_6,
 *         V4L2_EXT_HDMI_DRM_EOTF_RESERVED_7,
 *     };
 *
 *     enum v4l2_ext_hdmi_drm_meta_desc
 *     {
 *         V4L2_EXT_HDMI_DRM_META_DESC_TYPE1 = 0,
 *         V4L2_EXT_HDMI_DRM_META_DESC_RESERVED1,
 *         V4L2_EXT_HDMI_DRM_META_DESC_RESERVED2,
 *         V4L2_EXT_HDMI_DRM_META_DESC_RESERVED3,
 *         V4L2_EXT_HDMI_DRM_META_DESC_RESERVED4,
 *         V4L2_EXT_HDMI_DRM_META_DESC_RESERVED5,
 *         V4L2_EXT_HDMI_DRM_META_DESC_RESERVED6,
 *         V4L2_EXT_HDMI_DRM_META_DESC_RESERVED7,
 *     };
 *
 *     struct v4l2_ext_hdmi_drm_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char version;
 *         unsigned char length;
 *         enum v4l2_ext_hdmi_drm_eotf eotf_type;
 *         enum v4l2_ext_hdmi_drm_meta_desc meta_desc;
 *         unsigned short display_primaries_x0;
 *         unsigned short display_primaries_y0;
 *         unsigned short display_primaries_x1;
 *         unsigned short display_primaries_y1;
 *         unsigned short display_primaries_x2;
 *         unsigned short display_primaries_y2;
 *         unsigned short white_point_x;
 *         unsigned short white_point_y;
 *         unsigned short max_display_mastering_luminance;
 *         unsigned short min_display_mastering_luminance;
 *         unsigned short maximum_content_light_level;
 *         unsigned short maximum_frame_average_light_level;
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
 *     // Get DRM Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_drm_info hdmi_drm_info;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdmi_drm_info, 0, sizeof(struct v4l2_ext_hdmi_drm_info));
 *
 *     hdmi_drm_info.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_DRM_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_drm_info);
 *     ext_controls.controls->ptr = (void *)&hdmi_drm_info;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_DRM_INFO (V4L2_CID_USER_EXT_HDMI_BASE + 1)

/**
 * @brief Get HDMI VSI info
 *
 * @rst
 * Functional Requirements
 *   This function gets VSI infoframe.
 *
 * Responses to abnormal situations, including
 *  If HDMI clock is unstable or vertical frequency is 0, Infoframe packet
 should be cleared.
 *
 *  When ALLM= 1 in the HF-VSIF, source device may stop transmitting HF-VSIF
 suddenly without changing ALLM=0.
 *  BSP should handle this by resetting HF-VSIF infoframe if it is not received
 for 120 msec.
 *
 * Performance Requirements
 *  It should be returned within 10 msec.
 *
 * Constraints
 *  BSP should handle multiple VSIFs.
 *  WebOS expects BSP would handle four VSIF at the same time.
 *  WebOS supports HDMI14 VSIF, HF-VSIF and Dolby VSIF.

 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI VSI Info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_VSI_INFO
 *
 *     //
 *     // parameter
 *     //
 *
 *     #define V4L2_HDMI_PACKET_DATA_LENGTH 28
 *     #define V4L2_HDMI_INFOFRAME_PACKET_LEN 28
 *     #define V4L2_HDMI_VENDOR_SPECIFIC_REGID_LEN 3
 *     #define V4L2_HDMI_VENDOR_SPECIFIC_PAYLOAD_LEN \
 *          (V4L2_HDMI_INFOFRAME_PACKET_LEN -
 V4L2_HDMI_VENDOR_SPECIFIC_REGID_LEN)
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_vsi_video_format {
 *         V4L2_EXT_HDMI_VSI_VIDEO_FORMAT_NO_ADDITIONAL_FORMAT = 0,
 *         V4L2_EXT_HDMI_VSI_VIDEO_FORMAT_EXTENDED_RESOLUTION_FORMAT,
 *         V4L2_EXT_HDMI_VSI_VIDEO_FORMAT_3D_FORMAT,
 *     };
 *
 *     enum v4l2_ext_hdmi_vsi_3d_structure
 *     {
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_FRAME_PACKING = 0,
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_FIELD_ALTERNATIVE,
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_LINE_ALTERNATIVE,
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_FULL,
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_L_DEPTH,
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_L_DEPTH_GRAPHICS,
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_TOP_BOTTOM,
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_HALF    = 0x08,
 *         V4L2_EXT_HDMI_VSI_3D_STRUCTURE_TOP_BOTTOM_DIRECTV = 0x09,
 *     };
 *
 *     enum v4l2_ext_hdmi_vsi_3d_ext_data
 *     {
 *         V4L2_EXT_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_0 = 0,
 *         V4L2_EXT_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_1,
 *         V4L2_EXT_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_2,
 *         V4L2_EXT_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_3,
 *         V4L2_EXT_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_0,
 *         V4L2_EXT_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_1,
 *         V4L2_EXT_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_2,
 *         V4L2_EXT_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_3,
 *     };
 *
 *     enum v4l2_ext_hdmi_vsi_vic
 *     {
 *         V4L2_EXT_HDMI_VSI_VIC_RESERVED = 0,
 *         V4L2_EXT_HDMI_VSI_VIC_4K2K_30HZ,
 *         V4L2_EXT_HDMI_VSI_VIC_4K2K_25HZ,
 *         V4L2_EXT_HDMI_VSI_VIC_4K2K_24HZ,
 *         V4L2_EXT_HDMI_VSI_VIC_4K2K_24HZ_SMPTE,
 *     };
 *
 *     enum v4l2_ext_hdmi_packet_status
 *     {
 *         V4L2_EXT_HDMI_PACKET_STATUS_NOT_RECEIVED = 0,
 *         V4L2_EXT_HDMI_PACKET_STATUS_STOPPED,
 *         V4L2_EXT_HDMI_PACKET_STATUS_UPDATED,
 *     };
 *
 *     struct v4l2_ext_hdmi_in_packet
 *     {
 *         unsigned char type;
 *         unsigned char version;
 *         unsigned char length;
 *         unsigned char data_bytes[V4L2_EXT_HDMI_PACKET_DATA_LENGTH];
 *     };
 *
 *     struct v4l2_ext_hdmi_vsi_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_vsi_video_format video_format;
 *         enum v4l2_ext_hdmi_vsi_3d_structure st_3d;
 *         enum v4l2_ext_hdmi_vsi_3d_ext_data ext_data_3d;
 *         enum v4l2_ext_hdmi_vsi_vic vic;
 *         unsigned char regid[V4L2_EXT_HDMI_VENDOR_SPECIFIC_REGID_LEN];
 *         unsigned char payload[V4L2_EXT_HDMI_VENDOR_SPECIFIC_PAYLOAD_LEN];
 *         enum v4l2_ext_hdmi_packet_status packet_status;
 *         struct v4l2_ext_hdmi_in_packet packet;
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
 *     // Get VSI Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_vsi_info hdmi_vsi;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdmi_vsi, 0, sizeof(struct v4l2_ext_hdmi_vsi_info));
 *
 *     hdmi_vsi.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_VSI_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_vsi_info);
 *     ext_controls.controls->ptr = (void *)&hdmi_vsi;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_VSI_INFO (V4L2_CID_USER_EXT_HDMI_BASE + 2)

/**
 * @brief Get HDMI SPD info
 *
 * @rst
 * Functional Requirements
 *   This function get SPD infoframe.
 *
 *   If only SPD information changes without signal changes, the changed
 * information should be updated.
 *
 *   When forwarding AMD VSIF using SPD InfoFrame,
 *   AMD FreeSync requires that it changes to VRR mode when the FreeSync status
 * is Enabled or Active.
 *   When the FreeSync state goes back and forth between Enabled and Active, the
 * following behavior should not occur:
 *       #. Flicker shall not occur.
 *       #. Signal Detect shall not occur.
 *       #. Mute shall not occur.
 *
 * Responses to abnormal situations, including
 *   In CEA-861, recommended SPD packet interval is 1 seconds.
 *   Driver should keep previous SPD packet even if the packet is not received
 * for more than 1 second as long as signal keeps valid.
 *   It means V4L2_CID_EXT_HDMI_SPD_INFO always returns valid SPD data if it is
 * received at least once after valid video timing.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   When processing SPD Info packet, checksum should be verified.
 *   If the checksum value is not correct, the SPD info packet is not delivered.
 *   If HDMI clock is unstable or Vertical Frequency is 0, Infoframe packet
 * should be cleared.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI SPD Info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_SPD_INFO
 *
 *     //
 *     // parameter
 *     //
 *
 *     #define V4L2_HDMI_PACKET_DATA_LENGTH 28
 *     #define V4L2_HDMI_SPD_IF_VENDOR_LEN      8
 *     #define V4L2_HDMI_SPD_IF_DESC_LEN       16
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_packet_status
 *     {
 *         V4L2_EXT_HDMI_PACKET_STATUS_NOT_RECEIVED = 0,
 *         V4L2_EXT_HDMI_PACKET_STATUS_STOPPED,
 *         V4L2_EXT_HDMI_PACKET_STATUS_UPDATED,
 *     };
 *
 *     struct v4l2_ext_hdmi_in_packet
 *     {
 *         unsigned char type;
 *         unsigned char version;
 *         unsigned char length;
 *         unsigned char data_bytes[V4L2_EXT_HDMI_PACKET_DATA_LENGTH];
 *     };
 *
 *     struct v4l2_ext_hdmi_spd_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char vendor_name[V4L2_EXT_HDMI_SPD_IF_VENDOR_LEN + 1];
 *         unsigned char product_description[V4L2_EXT_HDMI_SPD_IF_DESC_LEN + 1];
 *         unsigned char source_device_info;
 *         enum v4l2_ext_hdmi_packet_status packet_status;
 *         struct v4l2_ext_hdmi_in_packet packet;
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
 *     // Get SPD Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_spd_info hdmi_spd;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdmi_spd, 0, sizeof(struct v4l2_ext_hdmi_spd_info));
 *
 *     hdmi_spd.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_SPD_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_spd_info);
 *     ext_controls.controls->ptr = (void *)&hdmi_spd;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_SPD_INFO (V4L2_CID_USER_EXT_HDMI_BASE + 3)

/**
 * @brief Get HDMI AVI info
 *
 * @rst
 * Functional Requirements
 *   This function get AVI infoframe.
 *
 *   If the Source Device sends only SET_AVMUTE without sending CLEAR_AVMUTE,
 * the previous Mute state should be cleared when the signal is detected again.
 *
 *   FRL signal input should be properly updated in AVI Packet information. ex)
 * Pixel Format.
 *
 *   If the IT content(v4l2_ext_hdmi_avi_it_content) is 0 in the AVI Packet, the
 * IT content type(v4l2_ext_hdmi_avi_content_type) must be 0, which is the
 * default value.
 *
 * Responses to abnormal situations, including
 *   If HDMI clock is unstable or Vertical Frequency is 0, Infoframe packet
 * should be cleared.
 *
 * Performance Requirements
 *   None
 *
 * Constraints
 *   We will update the content soon.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI AVI Info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_AVI_INFO
 *
 *     //
 *     // parameter
 *     //
 *
 *     #define V4L2_HDMI_PACKET_DATA_LENGTH 28
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_csc
 *     {
 *         V4L2_EXT_HDMI_AVI_CSC_RGB = 0,
 *         V4L2_EXT_HDMI_AVI_CSC_YCBCR422,
 *         V4L2_EXT_HDMI_AVI_CSC_YCBCR444,
 *         V4L2_EXT_HDMI_AVI_CSC_YCBCR420,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_active_info
 *     {
 *         V4L2_EXT_HDMI_AVI_ACTIVE_INFO_INVALID = 0,
 *         V4L2_EXT_HDMI_AVI_ACTIVE_INFO_VALID,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_bar_info
 *     {
 *         V4L2_EXT_HDMI_AVI_BAR_INFO_INVALID = 0,
 *         V4L2_EXT_HDMI_AVI_BAR_INFO_VERTICALVALID,
 *         V4L2_EXT_HDMI_AVI_BAR_INFO_HORIZVALID,
 *         V4L2_EXT_HDMI_AVI_BAR_INFO_VERTHORIZVALID,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_scan_info
 *     {
 *         V4L2_EXT_HDMI_AVI_SCAN_INFO_NODATA = 0,
 *         V4L2_EXT_HDMI_AVI_SCAN_INFO_OVERSCANNED,
 *         V4L2_EXT_HDMI_AVI_SCAN_INFO_UNDERSCANNED,
 *         V4L2_EXT_HDMI_AVI_SCAN_INFO_FUTURE,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_colorimetry
 *     {
 *         V4L2_EXT_HDMI_AVI_COLORIMETRY_NODATA = 0,
 *         V4L2_EXT_HDMI_AVI_COLORIMETRY_SMPTE170,
 *         V4L2_EXT_HDMI_AVI_COLORIMETRY_ITU709,
 *         V4L2_EXT_HDMI_AVI_COLORIMETRY_FUTURE,
 *         V4L2_EXT_HDMI_AVI_COLORIMETRY_EXTENDED =
 * V4L2_EXT_HDMI_AVI_COLORIMETRY_FUTURE,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_picture_arc
 *     {
 *         V4L2_EXT_HDMI_AVI_PICTURE_ARC_NODATA = 0,
 *         V4L2_EXT_HDMI_AVI_PICTURE_ARC_4_3,
 *         V4L2_EXT_HDMI_AVI_PICTURE_ARC_16_9,
 *         V4L2_EXT_HDMI_AVI_PICTURE_ARC_FUTURE,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_active_format_arc
 *     {
 *         V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_PICTURE = 8,
 *         V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_4_3CENTER = 9,
 *         V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_16_9CENTER = 10,
 *         V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_14_9CENTER = 11,
 *         V4L2_EXT_HDMI_AVI_ACTIVE_FORMAT_ARC_OTHER = 0,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_scaling
 *     {
 *         V4L2_EXT_HDMI_AVI_SCALING_NOSCALING = 0,
 *         V4L2_EXT_HDMI_AVI_SCALING_HSCALING,
 *         V4L2_EXT_HDMI_AVI_SCALING_VSCALING,
 *         V4L2_EXT_HDMI_AVI_SCALING_HVSCALING,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_it_content
 *     {
 *         V4L2_EXT_HDMI_AVI_IT_CONTENT_NODATA = 0,
 *         V4L2_EXT_HDMI_AVI_IT_CONTENT_ITCONTENT,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_ext_colorimetry
 *     {
 *         V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_XVYCC601 = 0,
 *         V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_XVYCC709,
 *         V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_SYCC601,
 *         V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_ADOBEYCC601,
 *         V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_ADOBERGB,
 *         V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_BT2020_YCCBCCRC,
 *         V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_BT2020_RGBORYCBCR,
 *         V4L2_EXT_HDMI_AVI_EXT_COLORIMETRY_XVRESERED,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_rgb_quantization_range
 *     {
 *         V4L2_EXT_HDMI_AVI_RGB_QUANTIZATION_RANGE_DEFAULT = 0,
 *         V4L2_EXT_HDMI_AVI_RGB_QUANTIZATION_RANGE_LIMITEDRANGE,
 *         V4L2_EXT_HDMI_AVI_RGB_QUANTIZATION_RANGE_FULLRANGE,
 *         V4L2_EXT_HDMI_AVI_RGB_QUANTIZATION_RANGE_RESERVED,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_ycc_quantization_range
 *     {
 *         V4L2_EXT_HDMI_AVI_YCC_QUANTIZATION_RANGE_LIMITEDRANGE = 0,
 *         V4L2_EXT_HDMI_AVI_YCC_QUANTIZATION_RANGE_FULLRANGE,
 *         V4L2_EXT_HDMI_AVI_YCC_QUANTIZATION_RANGE_RESERVED,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_content_type
 *     {
 *         V4L2_EXT_HDMI_AVI_CONTENT_TYPE_GRAPHICS = 0,
 *         V4L2_EXT_HDMI_AVI_CONTENT_TYPE_PHOTO,
 *         V4L2_EXT_HDMI_AVI_CONTENT_TYPE_CINEMA,
 *         V4L2_EXT_HDMI_AVI_CONTENT_TYPE_GAME,
 *     };
 *
 *     enum v4l2_ext_hdmi_avi_additional_colorimetry
 *     {
 *         V4L2_EXT_HDMI_AVI_ADDITIONAL_COLORIMETRY_DCI_P3_D65 = 0,
 *         V4L2_EXT_HDMI_AVI_ADDITIONAL_COLORIMETRY_DCI_P3_THEATER,
 *         V4L2_EXT_HDMI_AVI_ADDITIONAL_COLORIMETRY_RESERVED,
 *     };
 *
 *     enum v4l2_ext_hdmi_packet_status
 *     {
 *         V4L2_EXT_HDMI_PACKET_STATUS_NOT_RECEIVED = 0,
 *         V4L2_EXT_HDMI_PACKET_STATUS_STOPPED,
 *         V4L2_EXT_HDMI_PACKET_STATUS_UPDATED,
 *     };
 *
 *     struct v4l2_ext_hdmi_in_packet
 *     {
 *         unsigned char type;
 *         unsigned char version;
 *         unsigned char length;
 *         unsigned char data_bytes[V4L2_EXT_HDMI_PACKET_DATA_LENGTH];
 *     };
 *
 *     struct v4l2_ext_hdmi_avi_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_mode mode;
 *
 *         enum v4l2_ext_hdmi_avi_csc pixel_encoding;
 *         enum v4l2_ext_hdmi_avi_active_info active_info;
 *         enum v4l2_ext_hdmi_avi_bar_info bar_info;
 *         enum v4l2_ext_hdmi_avi_scan_info scan_info;
 *         enum v4l2_ext_hdmi_avi_colorimetry colorimetry;
 *         enum v4l2_ext_hdmi_avi_picture_arc picture_aspect_ratio;
 *         enum v4l2_ext_hdmi_avi_active_format_arc active_format_aspect_ratio;
 *         enum v4l2_ext_hdmi_avi_scaling scaling;
 *
 *         unsigned char vic;
 *         unsigned char pixel_repeat;
 *
 *         enum v4l2_ext_hdmi_avi_it_content it_content;
 *         enum v4l2_ext_hdmi_avi_ext_colorimetry extended_colorimetry;
 *         enum v4l2_ext_hdmi_avi_rgb_quantization_range rgb_quantization_range;
 *         enum v4l2_ext_hdmi_avi_ycc_quantization_range ycc_quantization_range;
 *         enum v4l2_ext_hdmi_avi_content_type content_type;
 *         enum v4l2_ext_hdmi_avi_additional_colorimetry additional_colorimetry;
 *
 *         unsigned short top_bar_end_line_number;
 *         unsigned short bottom_bar_start_line_number;
 *         unsigned short left_bar_end_pixel_number;
 *         unsigned short right_bar_end_pixel_number;
 *
 *         enum v4l2_ext_hdmi_packet_status packet_status;
 *         struct v4l2_ext_hdmi_in_packet packet;
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
 *     // Get AVI Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_avi_info hdmi_avi;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdmi_avi, 0, sizeof(struct v4l2_ext_hdmi_avi_info));
 *
 *     hdmi_avi.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_AVI_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_avi_info);
 *     ext_controls.controls->ptr = (void *)&hdmi_avi;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_AVI_INFO (V4L2_CID_USER_EXT_HDMI_BASE + 4)

/**
 * @brief Get HDMI Packet info
 *
 * @rst
 * Functional Requirements
 *   This function gets HDMI packet(AVI,SPD,VSI) information.
 *
 * Responses to abnormal situations, including
 *   If HDMI clock is unstable or vertical frequency is 0, Infoframe packet
 * should be cleared.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   This function is deprecated.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI ALL Packet Info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_PACKET_INFO
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_mode
 *     {
 *         V4L2_EXT_HDMI_MODE_DVI = 0,
 *         V4L2_EXT_HDMI_MODE_HDMI,
 *     };
 *
 *     struct v4l2_ext_hdmi_avi_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_mode mode;
 *
 *         enum v4l2_ext_hdmi_avi_csc pixel_encoding;
 *         enum v4l2_ext_hdmi_avi_active_info active_info;
 *         enum v4l2_ext_hdmi_avi_bar_info bar_info;
 *         enum v4l2_ext_hdmi_avi_scan_info scan_info;
 *         enum v4l2_ext_hdmi_avi_colorimetry colorimetry;
 *         enum v4l2_ext_hdmi_avi_picture_arc picture_aspect_ratio;
 *         enum v4l2_ext_hdmi_avi_active_format_arc active_format_aspect_ratio;
 *         enum v4l2_ext_hdmi_avi_scaling scaling;
 *
 *         unsigned char vic;
 *         unsigned char pixel_repeat;
 *
 *         enum v4l2_ext_hdmi_avi_it_content it_content;
 *         enum v4l2_ext_hdmi_avi_ext_colorimetry extended_colorimetry;
 *         enum v4l2_ext_hdmi_avi_rgb_quantization_range rgb_quantization_range;
 *         enum v4l2_ext_hdmi_avi_ycc_quantization_range ycc_quantization_range;
 *         enum v4l2_ext_hdmi_avi_content_type content_type;
 *         enum v4l2_ext_hdmi_avi_additional_colorimetry additional_colorimetry;
 *
 *         unsigned short top_bar_end_line_number;
 *         unsigned short bottom_bar_start_line_number;
 *         unsigned short left_bar_end_pixel_number;
 *         unsigned short right_bar_end_pixel_number;
 *
 *         enum v4l2_ext_hdmi_packet_status packet_status;
 *         struct v4l2_ext_hdmi_in_packet packet;
 *     };
 *
 *     struct v4l2_ext_hdmi_spd_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char vendor_name[V4L2_EXT_HDMI_SPD_IF_VENDOR_LEN + 1];
 *         unsigned char product_description[V4L2_EXT_HDMI_SPD_IF_DESC_LEN + 1];
 *         unsigned char source_device_info;
 *         enum v4l2_ext_hdmi_packet_status packet_status;
 *         struct v4l2_ext_hdmi_in_packet packet;
 *     };
 *
 *     struct v4l2_ext_hdmi_vsi_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_vsi_video_format video_format;
 *         enum v4l2_ext_hdmi_vsi_3d_structure st_3d;
 *         enum v4l2_ext_hdmi_vsi_3d_ext_data ext_data_3d;
 *         enum v4l2_ext_hdmi_vsi_vic vic;
 *         unsigned char regid[V4L2_EXT_HDMI_VENDOR_SPECIFIC_REGID_LEN];
 *         unsigned char payload[V4L2_EXT_HDMI_VENDOR_SPECIFIC_PAYLOAD_LEN];
 *         enum v4l2_ext_hdmi_packet_status packet_status;
 *         struct v4l2_ext_hdmi_in_packet packet;
 *     };
 *
 *     struct v4l2_ext_hdmi_packet_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_mode mode;
 *         struct v4l2_ext_hdmi_avi_info avi;
 *         struct v4l2_ext_hdmi_spd_info spd;
 *         struct v4l2_ext_hdmi_vsi_info vsi;
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
 *     // Get Packet Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_packet_info hdmi_packet;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdmi_packet, 0, sizeof(struct v4l2_ext_hdmi_packet_info));
 *
 *     hdmi_packet.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_PACKET_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_packet_info);
 *     ext_controls.controls->ptr = (void *)&hdmi_packet;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_PACKET_INFO (V4L2_CID_USER_EXT_HDMI_BASE + 5)

/**
 * @brief Get Dolby HDR Type
 *
 * @rst
 * Functional Requirements
 *   This returns Dolby HDR Type.
 *
 * Responses to abnormal situations, including
 *   If HDMI clock is unstable or Vertical Frequency is 0, Infoframe packet
 * should be cleared.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   If it does not support DolbyVision, it should return -1.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI Dolby HDR Type
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_DOLBY_HDR
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_dolby_hdr_type
 *     {
 *         V4L2_EXT_HDMI_DOLBY_HDR_TYPE_SDR = 0,
 *         V4L2_EXT_HDMI_DOLBY_HDR_TYPE_STANDARD_VSIF_1,
 *         V4L2_EXT_HDMI_DOLBY_HDR_TYPE_STANDARD_VSIF_2,
 *         V4L2_EXT_HDMI_DOLBY_HDR_TYPE_LOW_LATENCY,
 *         V4L2_EXT_HDMI_DOLBY_HDR_TYPE_DOLBY_VISION_PC,
 *     };
 *
 *     struct v4l2_ext_hdmi_dolby_hdr
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_dolby_hdr_type type;
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
 *     // Get Dolby HDR Type
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_dolby_hdr dolby_hdr;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&dolby_hdr, 0, sizeof(struct v4l2_ext_hdmi_dolby_hdr));
 *
 *     dolby_hdr.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_DOLBY_HDR;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_dolby_hdr);
 *     ext_controls.controls->ptr = (void *)&dolby_hdr;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_DOLBY_HDR (V4L2_CID_USER_EXT_HDMI_BASE + 6)

/**
 * @brief Get/Set HDMI EDID
 *
 * @rst
 * Functional Requirements
 *   This control write or read EDID.
 *   It could be read and written at any time. There're many scenarios that EDID
 * is changed.
 *
 * Responses to abnormal situations, including
 *   EDID should be accessible by the source device even when the TV is in the
 * standby mode.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   BSP behavior should not depend on the EDID written.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI EDID
 *     VIDIOC_S_EXT_CTRLS      // Set HDMI EDID
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_EDID
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_edid_size
 *     {
 *         V4L2_EXT_HDMI_EDID_SIZE_128 = 0,
 *         V4L2_EXT_HDMI_EDID_SIZE_256,
 *         V4L2_EXT_HDMI_EDID_SIZE_512,
 *     };
 *
 *     struct v4l2_ext_hdmi_edid
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_edid_size size;
 *         union
 *         {
 *             unsigned char *pData;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
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
 *     // Set EDID Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_edid edid;
 *     unsigned char data[256] = {1,2,3,4,5, };
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&edid, 0, sizeof(struct v4l2_ext_hdmi_edid));
 *
 *     edid.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     edid.size = V4L2_EXT_HDMI_EDID_SIZE_256;
 *     edid.pData = &data;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_EDID;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_edid);
 *     ext_controls.controls->ptr = (void *)&edid;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Get EDID Data
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_edid edid;
 *     unsigned char data[256] = {0, };
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&dolby_hdr, 0, sizeof(struct v4l2_ext_hdmi_edid));
 *
 *     edid.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     edid.size = V4L2_EXT_HDMI_EDID_SIZE_128;
 *     edid.pData = &data;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_EDID;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_edid);
 *     ext_controls.controls->ptr = (void *)&edid;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_EDID (V4L2_CID_USER_EXT_HDMI_BASE + 7)

/**
 * @brief Get Port Connection Status
 *
 * @rst
 * Functional Requirements
 *   This control returns HDMI 5V information.
 *   HDMI 5V information is enable when HDMI device connect each ports.
 *   The value of the state in the v4l2_ext_hdmi_connection_state would be 1 if
 * there's 5V. Otherwise it would be 0.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   MHL is deprecated.
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
 *     V4L2_CID_EXT_HDMI_CONNECTION_STATE
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_hdmi_connection_state
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char state;
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
 *     // Get HDMI 5V state
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_connection_state hdmi_port_state;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdmi_port_state, 0, sizeof(struct
 * v4l2_ext_hdmi_connection_state));
 *
 *     hdmi_port_state.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_CONNECTION_STATE;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_hdmi_connection_state);
 *     ext_controls.controls->ptr = (void *)&hdmi_port_state;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_CONNECTION_STATE (V4L2_CID_USER_EXT_HDMI_BASE + 8)

/**
 * @brief Set/Get Port HPD Control
 *
 * @rst
 * Functional Requirements
 *   This control handles HPD controls. (Enable / Disable / Restart)
 *   Enable and Disable does not mean changing HPD state to high or low.
 *   Initial valule should be Disable and BSP should not change HPD value to
 * high at this state.
 *   After webOS call Enable state, BSP could change HPD value to high or low.
 *   webOS does not control HPD value for itself.
 *   webOS calls Restart state to change EDID or reset connection. At this time
 * BSP should handle HPD and RxSense, too.
 *   It should have the same effect with plugging out and in the HDMI cable. HPD
 * low duration in the Restart mode should be 700 msec.
 *   The internal mute operation should be performed when HPD is restarted, not
 * when the EDID is changed.
 *
 *   When entering the Suspend mode, the time of the HPD low duration is set by
 * "V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON"
 *   and this value should be applied when Resume. The default is 100ms.
 *
 * Responses to abnormal situations, including
 *   If V4L2_EXT_HDMI_HPD_RESTART is called before V4L2_EXT_HDMI_HPD_ENABLE, it
 * should be ignored.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   HPD should be controlled only on one thread. Controlling HPD on two or more
 * threads may cause collision problems.
 *   In order to improve compatibility issues, do not arbitrarily adjust the
 * length of the low duration of the HPD.
 *   If driver need to change HPD low duration, LG's review is required to
 * change it.
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
 *     V4L2_CID_EXT_HDMI_HPD
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_hpd_state
 *     {
 *         V4L2_EXT_HDMI_HPD_DISABLE = 0,
 *         V4L2_EXT_HDMI_HPD_ENABLE,
 *         V4L2_EXT_HDMI_HPD_RESTART,
 *     };
 *
 *     struct v4l2_ext_hdmi_hpd
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_hpd_state hpd_state;
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
 *     // Set Control HPD
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hpd hpd;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hpd, 0, sizeof(struct v4l2_ext_hdmi_hpd));
 *
 *     hpd.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     hpd.eHPDControl = V4L2_HDMI_HPD_CONTROL_DISABLE;
 *     //hpd.eHPDControl = V4L2_HDMI_HPD_CONTROL_ENABLE;
 *     //hpd.eHPDControl = V4L2_HDMI_HPD_CONTROL_RESTART;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HPD;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_hpd);
 *     ext_controls.controls->ptr = (void *)&hpd;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Get Control HPD
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hpd hpd;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hpd, 0, sizeof(struct v4l2_ext_hdmi_hpd));
 *
 *     hpd.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HPD;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_hpd);
 *     ext_controls.controls->ptr = (void *)&hpd;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_HPD (V4L2_CID_USER_EXT_HDMI_BASE + 9)

/**
 * @brief Set Power Off
 *
 * @rst
 * Functional Requirements
 *   In standby or suspend mode, EDID should be accessible even though we don't
 * use external eeprom to save EDID.
 *   And SoC HDMI block may goes to power down mode to maintain EDID data. This
 * function let hdmi driver know that
 *   tv goes to standby mode even when QSM is off. When QSM is off, TV does not
 * follow normal suspend routine.
 *   It is called when it goes to cold standby mode so that driver knows it is
 * going to cold standby mode and
 *   turns on 'always on module' inside HDMI SoC.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   If this notification is not required in the SoC,  it may just return 0.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL       // Set Power Off
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_POWER_OFF
 *
 *     //
 *     // control value
 *     //
 *     0 (Ignore), 1 (Set Power Off)
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
 *     // Set Power off mode
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_HDMI_POWER_OFF;
 *     control.value = 1;      // power off mode
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_POWER_OFF (V4L2_CID_USER_EXT_HDMI_BASE + 10)

/**
 * @brief Write HDMI HDCP key
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
 *   For models that do not support HDCP 2.2, HDCP 2.2 engine should be disabled
 * by BSP driver.
 *   HDCP 2.3 raw key should not be exposed to linux user space.
 *   BSP should internally encrypt the key or read from the secure storage
 * directly and ignore V4L2_CID_EXT_HDMI_HDCP_KEY call.
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
 *     V4L2_CID_EXT_HDMI_HDCP_KEY
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_hdcp_version
 *     {
 *         V4L2_EXT_HDMI_HDCP_VERSION_14 = 0,
 *         V4L2_EXT_HDMI_HDCP_VERSION_22,
 *         V4L2_EXT_HDMI_HDCP_VERSION_RESERVED,
 *     };
 *
 *     struct v4l2_ext_hdmi_hdcp_key
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_hdcp_version version;
 *         unsigned int key_size;
 *         union {
 *             unsigned char *pData;
 *             unsigned int compat_data;
 *             unsigned long long sizer;
 *         };
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
 *     // Write HDCP Key
 *     #define HDCP14_KEY_SIZE 288
 *
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hdcp_key hdcp_key;
 *     unsigned char key[HDCP14_KEY_SIZE] = {1,2,3,4,5,};
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hdcp_key, 0, sizeof(struct v4l2_ext_hdmi_hdcp_key));
 *
 *     hdcp_key.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     hdcp_key.pData = &key;
 *     hdcp_key.version = V4L2_EXT_HDMI_HDCP_VERSION_14;
 *     hdcp_key.key_size = HDCP14_KEY_SIZE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HDCP_KEY;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_hdcp_key);
 *     ext_controls.controls->ptr = (void *)&hdcp_key;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_HDCP_KEY (V4L2_CID_USER_EXT_HDMI_BASE + 11)

/**
 * @brief Dissconnect HDMI Port
 *
 * @rst
 * Functional Requirements
 *   Disconnect HDMI port.
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
 *     VIDIOC_S_CTRL       // Disconnect HDMI Port
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_DISCONNECT
 *
 *     //
 *     // control value
 *     //
 *     enum v4l2_hdmi_input_port
 *     {
 *         HDMI_INPUT_PORT_NONE = 0, //HDMI_INPUT_PORT_NONE means "HDMI
 * Disconnect".
 *         // The below enum values mean "HDMI Connect".
 *         HDMI_INPUT_PORT1,
 *         HDMI_INPUT_PORT2,
 *         HDMI_INPUT_PORT3,
 *         HDMI_INPUT_PORT4,
 *         HDMI_INPUT_PORT_ALL,
 *         HDMI_INPUT_PORT_MAX,
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
 *   This control id supports VIDIOC_S_CTRL only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Disconnect HDMI Port
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_HDMI_DISCONNECT;
 *     control.value = (int)HDMI_INPUT_PORT1;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_DISCONNECT (V4L2_CID_USER_EXT_HDMI_BASE + 12)

/**
 * @brief Get HDMI VRR Frequency
 *
 * @rst
 * Functional Requirements
 *   This control returns VRR frequency.
 *   This spec is added from HDMI2.1 and frequency unit is Hz*100 (59.98hz →
 * 5998, 120hz → 12000).
 *
 * Responses to abnormal situations, including
 *   This is required when the product supports HDMI2.1. Otherwise it would
 * return -1.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   It should return instantaneous frame rate calculated by BSP.
 *   It should work for both TMDS and FRL signal.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI VRR Frequency
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_VRR_FREQUENCY
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_hdmi_vrr_frequency
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned short frequency;
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
 *     // Get HDMI VRR Frequency
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_vrr_frequency freq;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&freq, 0, sizeof(struct v4l2_ext_hdmi_vrr_frequency));
 *
 *     freq.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_VRR_FREQUENCY;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_vrr_frequency);
 *     ext_controls.controls->ptr = (void *)&freq;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_VRR_FREQUENCY (V4L2_CID_USER_EXT_HDMI_BASE + 13)

/**
 * @brief Get HDMI EMPacket Info
 *
 * @rst
 * Functional Requirements
 *   This control returns Extended Metadata Packet information. This spec is
 * added from HDMI2.1.
 *   As soon as getting EMP data from a device, BSP should send the EMP data to
 * LG MW.
 *
 * Responses to abnormal situations, including
 *   If HDMI clock is unstable or Vertical Frequency is 0, Infoframe packet
 * should be cleared.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   VTEM type EM packet should be updated within the similar time with other
 * infoframes.
 *   Otherwise it would cause video flickering switching to other hdmi port.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI EMPacket Info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_EMP_INFO
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_emp_type
 *     {
 *         V4L2_EXT_HDMI_EMP_TYPE_UNDEFINED = 0,
 *         V4L2_EXT_HDMI_EMP_TYPE_VSEM,
 *         V4L2_EXT_HDMI_EMP_TYPE_DYNAMICHDREM,
 *         V4L2_EXT_HDMI_EMP_TYPE_VTEM,
 *         V4L2_EXT_HDMI_EMP_TYPE_CVTEM
 *     };
 *
 *     struct v4l2_ext_hdmi_emp_info
 *     {
 *         enum v4l2_ext_hdmi_input_port port; // in
 *         enum v4l2_ext_hdmi_emp_type type; // in
 *         unsigned short current_packet_index; // in
 *         unsigned short total_packet_number; // out
 *         unsigned char data[31]; // out
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
 *     // Get HDMI EMPacket Info
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_emp_info emp;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&emp, 0, sizeof(struct v4l2_ext_hdmi_emp_info));
 *
 *     emp.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     emp.type = V4L2_EXT_HDMI_EMP_TYPE_VTEM;
 *     emp.current_packet_index = 1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_EMP_INFO;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_emp_info);
 *     ext_controls.controls->ptr = (void *)&emp;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_EMP_INFO (V4L2_CID_USER_EXT_HDMI_BASE + 14)

/**
 * @brief Set/Get HDCP Repeater
 *
 * @rst
 * Functional Requirements
 *   This control sets value about HDCP repeater. Setting values are related
 * with video back end.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   No need to impment unless it is requested explicitly.
 *   If it is not supported return -1;
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS        // Set HDCP Repeater
 *     VIDIOC_G_EXT_CTRLS        // Get HDCP Repeater
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_HDCP_REPEATER
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_hdmi_hdcp_repeater
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char repeater_mode;
 *         unsigned char receiver_id[5];
 *         unsigned char repeater_hpd;
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
 *     // Get HDCP Repeater
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hdcp_repeater repeater;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&repeater, 0, sizeof(struct v4l2_ext_hdmi_hdcp_repeater));
 *
 *     repeater.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     repeater.repeater_mode = 1;
 *     repeater.receiver_id[0] = 1;
 *     repeater.receiver_hpd =1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HDCP_REPEATER;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_hdcp_repeater);
 *     ext_controls.controls->ptr = (void *)&repeater;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *     // Set HDCP Repeater
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hdcp_repeater repeater;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&repeater, 0, sizeof(struct v4l2_ext_hdmi_hdcp_repeater));
 *
 *     repeater.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HDCP_REPEATER;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_hdcp_repeater);
 *     ext_controls.controls->ptr = (void *)&repeater;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_HDCP_REPEATER (V4L2_CID_USER_EXT_HDMI_BASE + 15)

/**
 * @brief Set EOTF value to BSP
 *
 * @rst
 * Functional Requirements
 *   This function is used to force EOTF values to be set to BSP by webOS.
 *   If webOS delivers certain eotf values through this function,
 *   the BSP must change the BSP information to the value delivered by LG,
 *   not the eotf value of the actual drm packet(V4L2_CID_EXT_HDMI_DRM_INFO).
 *   This value must be applied to the HDMI BSP area referenced by PQ or SCALER
 * BSP.
 *   PQ/SCALER BSP must operate with the eotf value set by LG.
 *   If override_eotf value is AUTO, set the EOTF value from the actual DRM
 * PACKET.
 *   If override_eotf value is not AUTO, set the EOTF value to SETTING from
 * webOS.
 *
 * Responses to abnormal situations, including
 *   when webOS set the V4L2_EXT_HDMI_OVERRIDE_EOTF_SMPTE_ST_2084 or
 *   V4L2_EXT_HDMI_OVERRIDE_EOTF_HLG, BSP must set the version of drm info as 1.
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
 *     V4L2_CID_EXT_HDMI_OVERRIDE_EOTF
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_hdmi_override_eotf {
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_SDR_LUMINANCE_RANGE = 0,
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_HDR_LUMINANCE_RANGE,
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_SMPTE_ST_2084,
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_HLG,
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_4,
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_5,
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_6,
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_RESERVED_7,
 *         V4L2_EXT_HDMI_OVERRIDE_EOTF_AUTO,
 *     };
 *     struct v4l2_ext_hdmi_override_drm_info {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_override_eotf override_eotf;
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
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set override EOTF value.
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_override_drm_info status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_override_drm_info));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     status.override_eotf = V4L2_CID_EXT_HDMI_OVERRIDE_HLG;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_OVERRIDE_EOTF;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_hdmi_override_drm_info);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_OVERRIDE_EOTF (V4L2_CID_USER_EXT_HDMI_BASE + 16)

/**
 * @brief Get HDMI capabilities from HDMI Device
 *
 * @rst
 * Functional Requirements
 *   This function get HDMI capabilities information about each port.
 *   It is used to identify HDMI device compatible with this specification and
 * to obtain information about driver and each HDMI port capabilities.
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
 *     VIDIOC_G_EXT_CTRLS        // Get HDMI capabilities
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_QUERYCAP
 *
 *     //
 *     // parameter
 *     //
 *
 *     // HDMI Capabilities Flags
 *     //  The HDMI device supports HDCP1.4 Key. So, need to write HDCP1.4 key
 * to driver.
 *     #define V4L2_EXT_HDMI_HDCP14                      0x0000000000000001  //
 * (0x1 << 0)
 *     //  HDCP1.4 Key is OTP on Soc. So, No need to download HDCP1.4 Key to
 * secure storage.
 *     #define V4L2_EXT_HDMI_HDCP14_KEY_OTP              0x0000000000000002  //
 * (0x1 << 1)
 *
 *     //  The HDMI device supports HDCP2.3 key. So, need to write HDCP2.3 key
 * to driver.
 *     //  HDCP2.2 key is include in HDCP2.3 key.
 *     #define V4L2_EXT_HDMI_HDCP23                      0x0000000000000004  //
 * (0x1 << 2)
 *     //  HDCP2.3(HDCP2.2) Key is OTP on Soc. So, No need to download
 * HDCP2.3(HDCP2.2) Key to secure storage.
 *     #define V4L2_EXT_HDMI_HDCP23_KEY_OTP              0x0000000000000008  //
 * (0x1 << 3)
 *
 *     //  The HDMI device supports HDMI1.4 Specification
 *     #define V4L2_EXT_HDMI_HDMI14                      0x0000000000001000  //
 * (0x1 << 12)
 *     //  The HDMI device supports HDMI2.0 Specification
 *     #define V4L2_EXT_HDMI_HDMI20                      0x0000000000002000  //
 * (0x1 << 13)
 *     // The HDMI device supports HDMI2.1 Specification.
 *     // Set this flag even if the device supports one feature in the HDMI2.1
 * specification.
 *     #define V4L2_EXT_HDMI_HDMI21                      0x0000000000004000  //
 * (0x1 << 14)
 *
 *     //  The HDMI device supports TMDS 3.4Gbps per Channel
 *     #define V4L2_EXT_HDMI_TMDS_3G                     0x0000000000100000  //
 * (0x1 << 20)
 *     //  The HDMI device supports TMDS 6.0Gbps per Channel
 *     #define V4L2_EXT_HDMI_TMDS_6G                     0x0000000000200000  //
 * (0x1 << 21)
 *     // The HDMI device supports FRL 3Gbps per Lane on 3 Lanes(0,1, and 2)
 *     #define V4L2_EXT_HDMI_FRL_3L_3G                   0x0000000000400000  //
 * (0x1 << 22)
 *     // The HDMI device supports FRL 6Gbps per Lane on 3 Lanes(0,1, and 2)
 *     #define V4L2_EXT_HDMI_FRL_3L_6G                   0x0000000000800000  //
 * (0x1 << 23)
 *     // The HDMI device supports FRL 6Gbps per Lane on 4 Lanes(0,1, 2, and 3)
 *     #define V4L2_EXT_HDMI_FRL_4L_6G                   0x0000000001000000  //
 * (0x1 << 24)
 *     // The HDMI device supports FRL 8Gbps per Lane on 4 Lanes(0,1, 2, and 3)
 *     #define V4L2_EXT_HDMI_FRL_4L_8G                   0x0000000002000000  //
 * (0x1 << 25)
 *     // The HDMI device supports FRL 10Gbps per Lane on 4 Lanes(0,1, 2, and 3)
 *     #define V4L2_EXT_HDMI_FRL_4L_10G                  0x0000000004000000  //
 * (0x1 << 26)
 *     // The HDMI device supports FRL 12Gbps per Lane on 4 Lanes(0,1, 2, and 3)
 *     #define V4L2_EXT_HDMI_FRL_4L_12G                  0x0000000008000000  //
 * (0x1 << 27)
 *
 *
 *     //  The HDMI device supports background timing detection.
 *     //  It means that driver can get HDMI signal information(timing, SPD,
 * AVI, etc...) without watching HDMI port.
 *     //  If the HDMI device supports background timing detection, it also
 * support fast switching between HDMI ports.
 *     #define V4L2_EXT_HDMI_BACKGROUND_TIMING_DETECT    0x0000000010000000  //
 * (0x1 << 28)
 *
 *     //  The HDMI device supports FVA
 *     #define V4L2_EXT_HDMI_FVA                         0x0000000020000000  //
 * (0x1 << 29)
 *     //  The HDMI device supports VRR
 *     #define V4L2_EXT_HDMI_VRR                         0x0000000040000000  //
 * (0x1 << 30)
 *     // The HDMI device supports CinemaVRR
 *     #define V4L2_EXT_HDMI_CINEMAVRR                   0x0000000080000000  //
 * (0x1 << 31)
 *
 *     //  The HDMI device supports  Dolby vision
 *     #define V4L2_EXT_HDMI_DOLBY_VISION                0x0000000100000000  //
 * (0x1 << 32)
 *     // The HDMI device supports  Dolby vision low latency mode
 *     #define V4L2_EXT_HDMI_DOLBY_VISION_LL             0x0000000200000000  //
 * (0x1 << 33)
 *     // The HDMI device supports  Dolby vision on HDMI2.1
 *     #define V4L2_EXT_HDMI_DOLBY_VISION_HDMI21         0x0000000400000000  //
 * (0x1 << 34)
 *     //  The HDMI device supports 512bytes EDID
 *     #define V4L2_EXT_HDMI_512BYTE_EDID                0x0000000800000000  //
 * (0x1 << 35)
 *     //  The HDMI device supports EMPACKET
 *     #define V4L2_EXT_HDMI_EMPACKET                    0x0000001000000000  //
 * (0x1 << 36)
 *     //  The HDMI device supports HDCP Repeater
 *     #define V4L2_EXT_HDMI_HDCP_REPEATER               0x0000002000000000  //
 * (0x1 << 37)
 *     //  The HDMI device supports DSC
 *     #define V4L2_EXT_HDMI_DSC                         0x0000004000000000  //
 * (0x1 << 38)
 *
 *     struct v4l2_ext_hdmi_capability {
 *         uint8_t chip[16]; // chip name. for example "e60"
 *         uint32_t version; // linuxtv header version
 *         uint64_t capabilities; // HDMI Capabilities Flags
 *         uint64_t reserved[3];
 *     };
 *
 *     struct v4l2_ext_hdmi_querycap {
 *         enum v4l2_ext_hdmi_input_port port;
 *         struct v4l2_ext_hdmi_capability hdmi_capability;
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
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // get HDMI capability
 *     v4l2_ext_controls ext_controls = {};
 *     v4l2_ext_control ext_control = {};
 *     struct v4l2_ext_hdmi_querycap hdmi_querycap = {};
 *
 *     hdmi_querycap.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_QUERYCAP;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_querycap);
 *     ext_controls.controls->ptr = (void *)&hdmi_querycap;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_QUERYCAP (V4L2_CID_USER_EXT_HDMI_BASE + 17)

/**
 * @brief Set HPD low Duration to each HDMI port for DC on case.
 *
 * @rst
 * Functional Requirements
 *   This function set the low duration of the HPD during DC on to reduce the
 *time to display video.
 *   HPD low duration refers to the time from the HPD low to the HPD high when
 *DC on.
 *   The unit of HPD low duraition sent by webOS is milli second.
 *   It should be possible to set for each port.
 *   When DC on, BSP should store the existing values of EDID and HDCP without
 *EDID, HDCP download API by LG.
 *   When the set time is reached, HPD should be changed from low to high.
 *
 * Responses to abnormal situations, including
 *   If the value has never been set by webOS, the default 700ms is used.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   The restart hpd time should not be changed. This should be fixed at 700ms.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *     VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_hdmi_hpd_low_duration_dc_on {
 *	       enum v4l2_ext_hdmi_input_port port;
 *	       int  hpd_low_duration;
 *     }
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
 *     // Set HPD low duration for DC ON case
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hpd_low_duration_dc_on status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(v4l2_ext_hdmi_hpd_low_duration_dc_on));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     status.hpd_low_duration = 200;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON;
 *     ext_controls.controls->size = sizeof(struct
 *v4l2_ext_hdmi_hpd_low_duration_dc_on);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &control);
 *
 *     // Get current HPD low duration info for DC ON case
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hpd_low_duration_dc_on hpd_low_duration
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&hpd_low_duration, 0, sizeof(struct
 *v4l2_ext_hdmi_hpd_low_duration_dc_on));
 *
 *     hpd_low_duration.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON;
 *     ext_controls.controls->size = sizeof(struct
 *v4l2_ext_hdmi_hpd_low_duration_dc_on);
 *     ext_controls.controls->ptr = (void *)&hpd_low_duration;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *
 * @endrst
 */

#define V4L2_CID_EXT_HDMI_HPD_LOW_DURATION_DC_ON                               \
  (V4L2_CID_USER_EXT_HDMI_BASE + 18)

/**
 * @brief Set Topology for multiple repeater device.
 *
 * @rst
 * Functional Requirements
 *   For Miracast TX, the Topology of the Device connected to the TV is
 * delivered to the BSP
 *   This function actions are required from BSP to implement Miracast TX in
 * webOS
 *   and the function that passes the RX ID of the device connected to Miracast
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   No need to impment unless it is requested explicitly.
 *   If it is not supported, return -1;
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
 *    V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_hdmi_hdcp_repeater_topology {
 *         enum v4l2_ext_hdmi_input_port port;     // HDMI port number
 *         unsigned char repeater_mode;            // 0 : receiver, 1 : repeater
 *         unsigned char count;                    // Number of devices
 *         unsigned char depth;                    // Depth of connected device
 *         unsigned char receiver_id[32][5];       // RX IO of connected device
 *         unsigned char repeater_hpd;             // HPD control
 *         unsigned int msg_id;                     // Increase by 1 when it
 * changes any value(init value =0, default set value = 1)
 *      };
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
 *     // Set HDCP Repeater topology
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_repeater_topology topology;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&topology, 0, sizeof(struct
 * v4l2_ext_hdmi_hdcp_repeater_topology));
 *
 *     topology.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_hdmi_hdcp_repeater_topology);
 *     ext_controls.controls->ptr = (void *)&topology;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */

#define V4L2_CID_EXT_HDMI_HDCP_REPEATER_TOPOLOGY                               \
  (V4L2_CID_USER_EXT_HDMI_BASE + 19)

/**
 * brief Get Stream Manage value from connected device
 *
 * @rst
 * Functional Requirements
 *   Pass the Stream Manage value of the device connected to the TV to Miracast.
 *   This function actions are required from BSP to implement Miracast TX in
 * webOS
 *   and the function  is the Stream Manage value of the device connected to the
 * HDMI Port on TV.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   No need to impment unless it is requested explicitly.
 *   If it is not supported, return -1;
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
 *     V4L2_CID_EXT_HDMI_HDCP_REPEATER_STREAM_MANAGE
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_hdmi_hdcp_repeater_stream_manage {
 *          enum v4l2_ext_hdmi_input_port port;
 *          v4l2_ext_hdmi_hdcp_repeater_stream_manage_transmit value;     // 0
 * or 1 or reserved
 *     };
 *
 *     enum v4l2_ext_hdmi_hdcp_repeater_stream_manage_transmit{
 *          STREAM_MANAGE_TRANSMIT_ALLOW,
 *          STREAM_MANAGE_TRANSMIT_DENY,
 *          STREAM_MANAGE_RESERVED,
 *     };
 *
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
 *     // Get stream manage type for repeater
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_repeater_stream_manage stream_manage;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&stream_manage, 0, sizeof(struct
 * v4l2_ext_hdmi_repeater_stream_manage));
 *
 *     stream_manage.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_REPEATER_STREAM_MANAGE;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_hdmi_repeater_stream_manage);
 *     ext_controls.controls->ptr = (void *)&stream_manage;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *
 * @endrst
 */

#define V4L2_CID_EXT_HDMI_HDCP_REPEATER_STREAM_MANAGE                          \
  (V4L2_CID_USER_EXT_HDMI_BASE + 20)

/**
 * @brief Set sleep mode for always ready function.
 *
 * @rst
 * Functional Requirements
 *   New power state called always ready is added.
 *   In this power state, one hdmi port will be running and other ports would be
 * powered down as suspend mode.
 *   webOS will let driver know which port should be running and which port
 * should be powered down.
 *   But V4L2_CID_EXT_HDMI_SLEEP would not be called during AC ON.
 *   Running port :
 *   - webOS would not check video timing because some SOC does not allow this.
 *   - But make sure hdmi phy and link is running in this mode and hdcp should
 * remain as auth state.
 *   - When it goes back to active mode, there should be no hpd reset, reauth
 * and retraining.
 *   - It should work for both TMDS and FRL.
 *   - when cable is plugged out and in again, it should receive signal again
 * and start HDCP auth again.
 *
 *   Sleeping port:
 *   - Not working at all.
 *   - Standby EDID should be supported in this mode, so HPD will remains as
 * high.
 *   - HPD will be reset when it goes to active mode.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   This is introduced to reduce booting time to show video in the HDMI input.
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
 *     V4L2_CID_EXT_HDMI_SLEEP
 *
 *     //
 *     // parameter
 *     //
 *     struct v4l2_ext_hdmi_sleep {
 *          enum v4l2_ext_hdmi_input_port port;
 *          enum v4l2_ext_hdmi_sleep_mode mode;
 *     };
 *
 *     enum v4l2_ext_hdmi_sleep_mode{
 *          V4L2_EXT_HDMI_SLEEP_MODE,
 *          V4L2_EXT_HDMI_WAKEUP_MODE,
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
 *     // Set sleep mode
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_sleep sleep_mode;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&sleep_mode, 0, sizeof(struct v4l2_ext_hdmi_sleep));
 *
 *     sleep_mode.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     sleep_mode.mode = V4L2_EXT_HDMI_SLEEP_MODE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_SLEEP;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_sleep);
 *     ext_controls.controls->ptr = (void *)&sleep_mode;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */

#define V4L2_CID_EXT_HDMI_SLEEP (V4L2_CID_USER_EXT_HDMI_BASE + 21)

/**
 * @brief Set DPMS mode for DPMS function.
 *
 * @rst
 * Functional Requirements
 *   TV power will automatically turn off when HDMI no signal status continues
 * for more than a certain period of time.
 *   After that, when the HDMI signal is detected again, the TV will power on.
 *   It is called DPMS function.
 *   This command sets the DPMS mode when the TV is powered off.
 *   When DPMS mode is enable and the power is turned off, The HDMI Phy should
 * detect the HDMI clock.
 *
 * Responses to abnormal situations, including
 *   Because the result of the clock detection may not be trustworthy, webOS
 * will check video timing again during the DC on time.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Result of clock detection in the HDMI Phy will be informed to micom.
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
 *     V4L2_CID_EXT_HDMI_DPMS
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_hdmi_dpms_mode{
 *          V4L2_EXT_HDMI_DPMS_MODE_DISABLE,
 *          V4L2_EXT_HDMI_DPMS_MODE_ENABLE,
 *          V4L2_EXT_HDMI_DPMS_MODE_ENABLE_DATA_CLK,
 *     };
 *
 *     struct v4l2_ext_hdmi_dpms {
 *          enum v4l2_ext_hdmi_input_port port;
 *          enum v4l2_ext_hdmi_dpms_mode mode;
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
 *     // Set dpms mode
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_dpms dpms_mode;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&dpms_mode, 0, sizeof(struct v4l2_ext_hdmi_dpms));
 *
 *     dpms_mode.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     dpms_mode.mode = V4L2_EXT_HDMI_DPMS_MODE_ENABLE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_DPMS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_dpms);
 *     ext_controls.controls->ptr = (void *)&dpms_mode;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */

#define V4L2_CID_EXT_HDMI_DPMS (V4L2_CID_USER_EXT_HDMI_BASE + 22)

/**
 * @brief Set/Get HDCP Repeater Mode
 *
 * @rst
 * Functional Requirements
 *  If this API is called, driver sets REPEATER bit in internal space.
 * This REPEATER bit is provided to source device for HDCP communication.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   No need to implement unless it is requested explicitly.
 *   If it is not supported return -1;
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS        // Set HDCP Repeater Mode
 *     VIDIOC_G_EXT_CTRLS        // Get HDCP Repeater Mode
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_HDCP_REPEATER_MODE
 *
 *     //
 *     // parameter
 *     //
 *     unsigned char mode : [0 : sink mode, 1 : repeater mode]
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
 *     // Get HDCP Repeater mode
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     unsigned char repeater_mode;
 *
 *     std::memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     std::memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     repeater_mode = 0;
 *
 *     ext_controls.ctrl_class  = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count               = 1;
 *     ext_controls.controls            = &ext_control;
 *     ext_controls.controls->id        = V4L2_CID_EXT_HDMI_HDCP_REPEATER_MODE;
 *     ext_controls.controls->size = sizeof(unsigned char);
 *     ext_controls.controls->ptr  = (void *)&repeater_mode;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *     // Set HDCP Repeater mode
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     unsigned char repeater_mode;
 *
 *     std::memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     std::memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     repeater_mode = 1;
 *
 *     ext_controls.ctrl_class  = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count               = 1;
 *     ext_controls.controls            = &ext_control;
 *     ext_controls.controls->id        = V4L2_CID_EXT_HDMI_HDCP_REPEATER_MODE;
 *     ext_controls.controls->size = sizeof(unsigned char);
 *     ext_controls.controls->ptr  = (void *)&repeater_mode;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */

#define V4L2_CID_EXT_HDMI_HDCP_REPEATER_MODE	(V4L2_CID_USER_EXT_HDMI_BASE + 23)

/**
 * @brief Set HDCP Topology info
 *
 * @rst
 * Functional Requirements
 *  If this API is called, driver sets below information in internal space.
 * LGE should send the below information on downstream, key list, rxinfo for HDCP2.2(rxstatus for HDCP1.4)
 * and these value should be used in HDCP communication when the source requests HDCP.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   No need to impment unless it is requested explicitly.
 *   If it is not supported return -1;
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS        // Set HDCP Topology info
 *     VIDIOC_G_EXT_CTRLS        // Set HDCP Topology info
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_HDCP_TOPOLOGY
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *     enum v4l2_ext_hdmi_hdcp_hdmiout_auth_state {
 *         V4L2_EXT_HDMI_HDCP_HDMIOUT_AUTH_STATUS_NONE_AUTH = 0,
 *         V4L2_EXT_HDMI_HDCP_HDMIOUT_AUTH_STATUS_NONE_DONE,
 *         V4L2_EXT_HDMI_HDCP_HDMIOUT_AUTH_STATUS_NONE_IGNORE,
 *     };
 *     struct v4l2_ext_hdmi_hdcp_topology_status {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_hdcp_version hdcp_version;
 *         enum v4l2_ext_hdmi_hdcp_hdmiout_auth_state auth_state;
 *         unsigned int topology_size;
 *         unsigned short hdcp14_statue;
 *         unsigned short hdcp22_statue;
 *         unsigned char *topology;
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
 * Example
 *   .. code-block:: cpp
 *
 *     // Get HDMI HDCP Topology
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hdcp_topology_status topology;
 *
 *     std::memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     std::memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     std::memset(&topology, 0, sizeof(struct v4l2_ext_hdmi_hdcp_topology_status));
 *
 *     ext_controls.ctrl_class  = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count               = 1;
 *     ext_controls.controls            = &ext_control;
 *     ext_controls.controls->id        = V4L2_CID_EXT_HDMI_HDCP_TOPOLOGY;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_hdcp_topology_status);
 *     ext_controls.controls->ptr  = (void *)&topology;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 *     // Set HDMI HDCP Topology
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hdcp_topology_status topology;
 *
 *     std::memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     std::memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     std::memset(&topology, 0, sizeof(struct v4l2_ext_hdmi_hdcp_topology_status));
 *
 *     topology.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     topology.hdcp_version = V4L2_EXT_HDMI_HDCP_VERSION_14;
 *     topology.auth_state = V4L2_EXT_HDMI_HDCP_HDMIOUT_AUTH_STATUS_NONE_DONE;
 *     topology.topology_size = 256;
 *     topology.hdcp14_status = 1;
 *	   topology.hdcp22_status = 1;
 * 	   topology.topology = NULL; 
 *
 *     ext_controls.ctrl_class  = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count               = 1;
 *     ext_controls.controls            = &ext_control;
 *     ext_controls.controls->id        = V4L2_CID_EXT_HDMI_HDCP_TOPOLOGY;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_hdcp_topology_status);
 *     ext_controls.controls->ptr  = (void *)&topology;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_HDCP_TOPOLOGY 		(V4L2_CID_USER_EXT_HDMI_BASE + 24)

/**
 * @brief Set/Get HDMI EDID Access Control
 *
 * @rst
 * Functional Requirements
 *   This control handles HDMI EDID access mode.
 *   When HDMI EDID acceess disabled, source device can not access EDID by HDMI DDC path.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   BSP behavior should not depend on the EDID written.
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
 *     V4L2_CID_EXT_HDMI_EDID_ACCESS
 *
 *     //
 *     // parameter
 *     //
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_edid_access_mode
 *     {
 *         V4L2_EXT_HDMI_EDID_ENABLE = 0, // default
 *         V4L2_EXT_HDMI_EDID_DISABLE,
 *     };
 *
 *     struct v4l2_ext_hdmi_edid_access {
 *          enum v4l2_ext_hdmi_input_port port;
 *          enum v4l2_ext_hdmi_edid_access_mode mode;
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
 *     // Set HDMI EDID access
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_edid_access edid_access;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&edid_access, 0, sizeof(struct v4l2_ext_hdmi_edid_access));
 *
 *     edid_access.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     edid_access.mode = V4L2_EXT_HDMI_EDID_DISABLE;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_EDID_ACCESS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_edid_access);
 *     ext_controls.controls->ptr = (void *)&edid_access;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_EDID_ACCESS (V4L2_CID_USER_EXT_HDMI_BASE + 25)

/* HDMI diagnostics class control IDs */
#define V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE (V4L2_CID_USER_EXT_HDMI_BASE + 0x100)

/**
 * @brief Get HDMI Diagnostics status
 *
 * @rst
 * Functional Requirements
 *   This control returns various HDMI related status and information supported
 * to display in HDMI diagnostics screen.
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
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI Diagnostics status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_DIAGNOSTICS_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_hdmi_diagnostics_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         struct v4l2_ext_hdmi_link_status link_status;
 *         struct v4l2_ext_hdmi_phy_status phy_status;
 *         struct v4l2_ext_hdmi_video_status video_status;
 *         struct v4l2_ext_hdmi_audio_status audio_status;
 *         struct v4l2_ext_hdmi_hdcp_status hdcp_status;
 *         struct v4l2_ext_hdmi_scdc_status scdc_status;
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
 *     // Get HDMI Diagnostics status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_diagnostics_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_diagnostics_status));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_DIAGNOSTICS_STATUS;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_hdmi_diagnostics_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_DIAGNOSTICS_STATUS                                   \
  (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 0)

/**
 * @brief Get HDMI PHY status
 *
 * @rst
 * Functional Requirements
 *   This control returns HDMI PHY status. this information used for HDMI host
 * diagnostics.
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
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI PHY status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_PHY_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_link_type
 *     {
 *         V4L2_EXT_HDMI_LINK_TYPE_TMDS = 0,
 *         V4L2_EXT_HDMI_LINK_TYPE_FRL,
 *     };
 *
 *     enum v4l2_ext_hdmi_link_lane_number
 *     {
 *         V4L2_EXT_HDMI_LINK_LANE_NUMBER_3 = 3,
 *         V4L2_EXT_HDMI_LINK_LANE_NUMBER_4 = 4,
 *     };
 *
 *     enum v4l2_ext_hdmi_link_rate
 *     {
 *         V4L2_EXT_HDMI_LINK_RATE_6G  = 6,
 *         V4L2_EXT_HDMI_LINK_RATE_8G  = 8,
 *         V4L2_EXT_HDMI_LINK_RATE_10G = 10,
 *         V4L2_EXT_HDMI_LINK_RATE_12G = 12,
 *     };
 *
 *     struct v4l2_ext_hdmi_phy_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char lock_status;
 *         unsigned int tmds_clk_khz;
 *
 *         enum v4l2_ext_hdmi_link_type link_type;
 *         enum v4l2_ext_hdmi_link_lane_number link_lane;
 *         enum v4l2_ext_hdmi_link_rate link_rate;
 *
 *         unsigned int ctle_eq_min_range[V4L2_EXT_HDMI_TMDS_CH_NUM];
 *         unsigned int ctle_eq_max_range[V4L2_EXT_HDMI_TMDS_CH_NUM];
 *         unsigned int ctle_eq_result[V4L2_EXT_HDMI_TMDS_CH_NUM];
 *         unsigned int error[V4L2_EXT_HDMI_TMDS_CH_NUM];
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
 *     // Get HDMI PHY status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_phy_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_phy_status));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_PHY_STATUS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_phy_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_PHY_STATUS (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 1)

/**
 * @brief Get HDMI Link status
 *
 * @rst
 * Functional Requirements
 *   This control returns HDMI Link status. this information used for HDMI host
 * diagnostics.
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
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI Link status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_LINK_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_audio_format
 *     {
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_UNKNOWN      = 0x00,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_PCM          = 0x01,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_AC3          = 0x10,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_EAC3         = 0x11,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_EAC3_ATMOS   = 0x12,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_MAT          = 0x15,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_MAT_ATMOS    = 0x16,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_TRUEHD       = 0x17,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_TRUEHD_ATMOS = 0x18,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_AAC          = 0x19,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_MPEG         = 0x20,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_DTS          = 0x30,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_HD_MA    = 0x31,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_EXPRESS  = 0x32,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_DTS_CD       = 0x33,
 *         V4L2_EXT_HDMI_AUDIO_FORMAT_NOAUDIO      = 0x41,
 *     };
 *
 *     struct v4l2_ext_hdmi_link_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char hpd;
 *         unsigned char hdmi_5v;
 *         unsigned char rx_sense;
 *         unsigned int frame_rate_x100_hz;
 *         enum v4l2_ext_hdmi_mode dvi_hdmi_mode;
 *
 *         unsigned short video_width;
 *         unsigned short video_height;
 *         enum v4l2_ext_hdmi_avi_csc color_space;
 *         unsigned char color_depth;
 *         enum v4l2_ext_hdmi_avi_colorimetry colorimetry;
 *         enum v4l2_ext_hdmi_avi_ext_colorimetry ext_colorimetry;
 *         enum v4l2_ext_hdmi_avi_additional_colorimetry additional_colorimetry;
 *         enum v4l2_ext_hdr_mode hdr_type;
 *
 *         enum v4l2_ext_hdmi_audio_format audio_format;
 *         unsigned int audio_sampling_freq;
 *         unsigned char audio_channel_number;
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
 *     // Get HDMI Link status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_link_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_link_status));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_LINK_STATUS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_link_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_LINK_STATUS (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 2)

/**
 * @brief Get HDMI Video status
 *
 * @rst
 * Functional Requirements
 *   This control returns HDMI Video status. this information used for HDMI host
 * diagnostics.
 *   Pixel_clock_khz is TMDS character rate.
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
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI Video status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_VIDEO_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_hdmi_video_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned short video_width_real;
 *         unsigned short video_htotal_real;
 *         unsigned short video_height_real;
 *         unsigned short video_vtotal_real;
 *         unsigned int pixel_clock_khz;
 *         unsigned int current_vrr_refresh_rate;
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
 *     // Get HDMI Video status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_video_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_video_status));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_VIDEO_STATUS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_video_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_VIDEO_STATUS (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 3)

/**
 * @brief Get HDMI Audio status
 *
 * @rst
 * Functional Requirements
 *   This control returns HDMI Audio status. this information used for HDMI host
 * diagnostics.
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
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI Audio status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_AUDIO_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_hdmi_audio_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned int pcm_N;
 *         unsigned int pcm_CTS;
 *         unsigned char LayoutBitValue;
 *         unsigned char ChannelStatusBits;
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
 *     // Get HDMI Audio status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_audio_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_audio_status));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_AUDIO_STATUS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_audio_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_AUDIO_STATUS (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 4)

/**
 * @brief Get HDMI HDCP status
 *
 * @rst
 * Functional Requirements
 *   This control returns HDMI HDCP status. this information used for HDMI host
 * diagnostics.
 *
 *   If the DVI Mode does not support Enhanced Encryption Status Signaling
 * (EESS), Bit1 (ENABLE_1.1_FEATURES) of Ainfo (0x15) and Bcaps (0x40) must be
 * changed to 0.
 *
 * Responses to abnormal situations, including
 *   If HDCP status is not authenticated or off, hdcp_version should be set to
 * V4L2_EXT_HDMI_HDCP_VERSION_RESERVED.
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
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI HDCP status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_HDCP_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_hdcp_auth_status
 *     {
 *         V4L2_EXT_HDMI_HDCP_AUTH_STATUS_NO_TX_CONNECTED = 0,
 *         V4L2_EXT_HDMI_HDCP_AUTH_STATUS_UNAUTHENTICATED = 1,
 *         V4L2_EXT_HDMI_HDCP_AUTH_STATUS_IN_PROGRESS     = 2,
 *         V4L2_EXT_HDMI_HDCP_AUTH_STATUS_AUTHENTICATED   = 3,
 *     };
 *
 *     struct v4l2_ext_hdmi_hdcp14_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char An[8];
 *         unsigned char Aksv[5];
 *         unsigned char Bksv[5];
 *         unsigned char Ri[2];
 *         unsigned char Bcaps;
 *         unsigned char Bstatus[2];
 *     };
 *
 *     struct v4l2_ext_hdmi_hdcp22_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned short ake_init_count_since_5v;
 *         unsigned short reauth_req_count_since_5v;
 *     };
 *
 *     struct v4l2_ext_hdmi_hdcp_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_hdcp_version hdcp_version;
 *         enum v4l2_ext_hdmi_hdcp_auth_status auth_status;
 *         unsigned char encEn;
 *         struct v4l2_ext_hdmi_hdcp14_status hdcp14_status;
 *         struct v4l2_ext_hdmi_hdcp22_status hdcp22_status;
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
 *     // Get HDMI HDCP status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_hdcp_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_hdcp_status));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_HDCP_STATUS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_hdcp_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_HDCP_STATUS (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 5)

/**
 * @brief Get HDMI SCDC status
 *
 * @rst
 * Functional Requirements
 *   This control returns HDMI SCDC status. this information used for HDMI host
 * diagnostics.
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
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI SCDC status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_SCDC_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     struct v4l2_ext_hdmi_scdc_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         unsigned char source_version;
 *         unsigned char sink_version;
 *
 *         unsigned char rsed_update;
 *         unsigned char flt_update;
 *         unsigned char frl_start;
 *         unsigned char source_test_update;
 *         unsigned char rr_test;
 *         unsigned char ced_update;
 *         unsigned char status_update;
 *
 *         unsigned char tmds_bit_clock_ratio;
 *         unsigned char scrambling_enable;
 *         unsigned char tmds_scrambler_status;
 *
 *         unsigned char flt_no_retrain;
 *         unsigned char rr_enable;
 *         unsigned char ffe_levels;
 *         unsigned char frl_rate;
 *
 *         unsigned char dsc_decode_fail;
 *         unsigned char flt_ready;
 *         unsigned char clk_detect;
 *         unsigned char ch0_locked;
 *         unsigned char ch1_locked;
 *         unsigned char ch2_locked;
 *         unsigned char ch3_locked;
 *
 *         unsigned char lane0_ltp_request;
 *         unsigned char lane1_ltp_request;
 *         unsigned char lane2_ltp_request;
 *         unsigned char lane3_ltp_request;
 *
 *         unsigned char ch0_ced_valid;
 *         unsigned char ch1_ced_valid;
 *         unsigned char ch2_ced_valid;
 *         unsigned char ch3_ced_valid;
 *         unsigned int ch0_ced;
 *         unsigned int ch1_ced;
 *         unsigned int ch2_ced;
 *         unsigned int ch3_ced;
 *         unsigned char rs_correction_valid;
 *         unsigned int rs_correcton_count;
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
 *     // Get HDMI SCDC status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_scdc_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_scdc_status));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_SCDC_STATUS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_scdc_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_SCDC_STATUS (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 6)

/**
 * @brief Get HDMI ERROR status
 *
 * @rst
 * Functional Requirements
 *   This function returns HDMI error from the currently selected Port. This
 * information used for HDMI host diagnostics.
 *   This function is called at regular intervals. Maintain if an error occurs
 * before a function is called.
 *   Clear the error after returning the function when it is called.
 *   For example, If a GCP error and a TMDS error occur simultaneously, the
 * value is returned as follows : 0x00000005
 *   If a HDCP 2.2 Reauth error and a Audio Buffer error occur simultaneously,
 * the value is returned as follows : 0x00000042
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
 *     VIDIOC_G_EXT_CTRLS      // Get HDMI ERROR status
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_ERROR_STATUS
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_error_type
 *     {
 *         V4L2_EXT_HDMI_ERROR_TYPE_NONE          = 0x0000,
 *         V4L2_EXT_HDMI_ERROR_TYPE_GCP_ERROR     = 0x0001,
 *         V4L2_EXT_HDMI_ERROR_TYPE_HDCP22_REAUTH = 0x0002,
 *         V4L2_EXT_HDMI_ERROR_TYPE_TMDS_ERROR    = 0x0004,
 *         V4L2_EXT_HDMI_ERROR_TYPE_PHY_LOW_RANGE = 0x0008,
 *         V4L2_EXT_HDMI_ERROR_TYPE_PHY_ABNORMAL  = 0x0010,
 *         V4L2_EXT_HDMI_ERROR_TYPE_CED_ERROR     = 0x0020,
 *         V4L2_EXT_HDMI_ERROR_TYPE_AUDIO_BUFFER  = 0x0040,
 *         V4L2_EXT_HDMI_ERROR_TYPE_UNSTABLE_SYNC = 0x0080,
 *         V4L2_EXT_HDMI_ERROR_TYPE_BCH           = 0x0100,
 *         V4L2_EXT_HDMI_ERROR_TYPE_FLT           = 0x0200,
 *         V4L2_EXT_HDMI_ERROR_TYPE_FAILED        = 0xFFFFFFFE,
 *     };
 *
 *     struct v4l2_ext_hdmi_error_status
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_error_type error;
 *         unsigned int param1;
 *         unsigned int param2;
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
 *     // Get HDMI ERROR status
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_error_status status;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&status, 0, sizeof(struct v4l2_ext_hdmi_error_status));
 *
 *     status.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_ERROR_STATUS;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_hdmi_error_status);
 *     ext_controls.controls->ptr = (void *)&status;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_ERROR_STATUS (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 7)

/**
 * @brief Set HDMI Expert setting
 *
 * @rst
 * Functional Requirements
 *   This function is used to change various HDMI BSP parameters
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
 *     VIDIOC_S_EXT_CTRLS      // Set HDMI Expert setting
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_HDMI_EXPERT_SETTING
 *
 *     //
 *     // parameter
 *     //
 *
 *     enum v4l2_ext_hdmi_input_port
 *     {
 *         V4L2_EXT_HDMI_INPUT_PORT_NONE = 0,
 *         V4L2_EXT_HDMI_INPUT_PORT_1,
 *         V4L2_EXT_HDMI_INPUT_PORT_2,
 *         V4L2_EXT_HDMI_INPUT_PORT_3,
 *         V4L2_EXT_HDMI_INPUT_PORT_4,
 *         V4L2_EXT_HDMI_INPUT_PORT_5,
 *         V4L2_EXT_HDMI_INPUT_PORT_ALL,
 *     };
 *
 *     enum v4l2_ext_hdmi_expert_setting_type
 *     {
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_HPD_LOW_DURATION = 0,
 *
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_MODE,
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH0,
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH1,
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH2,
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH3,
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_EQ_PERIOD,
 *
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_VIDEO_STABLE_COUNT,
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_AUDIO_STABLE_COUNT,
 *
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_DISABLE_HDCP22,
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_REAUTH_HDCP22,
 *
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_ON_TO_RXSENSE_TIME,
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_RXSENSE_TO_HPD_TIME,
 *
 *         // For ODM PCB without serial resistor, configure soc internal
 * resistor to match impedance.
 *         V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_PCB_SERIAL_RESISTOR
 *     };
 *
 *     struct v4l2_ext_hdmi_expert_setting
 *     {
 *         enum v4l2_ext_hdmi_input_port port;
 *         enum v4l2_ext_hdmi_expert_setting_type type;
 *         unsigned int param1;
 *         unsigned int param2; // (for future)
 *         unsigned int param3; // (for future)
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
 *   This control id supports VIDIOC_S_EXT_CTRLS only.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set HDMI Expert Setting
 *     v4l2_ext_controls ext_controls;
 *     v4l2_ext_control ext_control;
 *     struct v4l2_ext_hdmi_expert_setting setting;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&setting, 0, sizeof(struct v4l2_ext_hdmi_expert_setting));
 *
 *     setting.port = V4L2_EXT_HDMI_INPUT_PORT_1;
 *     setting.type = V4L2_EXT_HDMI_EXPERT_SETTING_TYPE_TMDS_MANUAL_EQ_CH0;
 *     setting.param1 = 7;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_HDMI_EXPERT_SETTING;
 *     ext_controls.controls->size = sizeof(struct
 * v4l2_ext_hdmi_expert_setting);
 *     ext_controls.controls->ptr = (void *)&setting;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_HDMI_EXPERT_SETTING                                       \
  (V4L2_CID_EXT_HDMI_DIAGNOSTICS_BASE + 8)

#endif /* _V4L2_EXT_HDMI_H */
