/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

/** @file v4l2-lge-hdmi.h
 *
 *  It is the header file for controling v4l2 hdmi driver.
 *
 *  @author     Yusun Lee(yusun85.lee@lge.com)
 *  @version    1.0
 *  @date       2018.05.17
 *  @note
 *  @see
 */

#ifndef _V4L2_LGE_HDMI_H
#define _V4L2_LGE_HDMI_H

//#include <linux/linuxtv-ext-ver.h>
#include <linux/v4l2-controls.h>

// clang-format off
#define V4L2_CID_USER_HDMI_BASE             (V4L2_CID_USER_BASE + 0x5000)
#define V4L2_CID_HDMI_G_TIMINGINFO          (V4L2_CID_USER_HDMI_BASE + 0)
#define V4L2_CID_HDMI_G_DRMINFO             (V4L2_CID_USER_HDMI_BASE + 1)
#define V4L2_CID_HDMI_G_VSIINFO             (V4L2_CID_USER_HDMI_BASE + 2)
#define V4L2_CID_HDMI_G_SPDINFO             (V4L2_CID_USER_HDMI_BASE + 3)
#define V4L2_CID_HDMI_G_AVIINFO             (V4L2_CID_USER_HDMI_BASE + 4)
#define V4L2_CID_HDMI_G_PACKETINFO          (V4L2_CID_USER_HDMI_BASE + 5)
#define V4L2_CID_HDMI_EDID                  (V4L2_CID_USER_HDMI_BASE + 6)
#define V4L2_CID_HDMI_G_CONNECTION_STATE    (V4L2_CID_USER_HDMI_BASE + 7)
#define V4L2_CID_HDMI_CONTROL_HPD           (V4L2_CID_USER_HDMI_BASE + 8)
#define V4L2_CID_HDMI_POWEROFF              (V4L2_CID_USER_HDMI_BASE + 9)

#define V4L2_HDMI_PACKET_DATA_LENGTH          28
#define V4L2_HDMI_INFOFRAME_PACKET_LEN        28
#define V4L2_HDMI_VENDOR_SPECIFIC_REGID_LEN    3
#define V4L2_HDMI_VENDOR_SPECIFIC_PAYLOAD_LEN \
    (V4L2_HDMI_INFOFRAME_PACKET_LEN - V4L2_HDMI_VENDOR_SPECIFIC_REGID_LEN)

#define V4L2_HDMI_SPD_IF_VENDOR_LEN    8
#define V4L2_HDMI_SPD_IF_DESC_LEN      16
// clang-format on

/*
    VIDIOC_S_INPUT
    VIDIOC_G_INPUT
*/
enum v4l2_hdmi_input_port {
    /**** HDMI_INPUT_PORT_NONE means "HDMI Disconnect". ****/
    HDMI_INPUT_PORT_NONE = 0,
    /**** The below enum values mean "HDMI Connect". ****/
    HDMI_INPUT_PORT1,
    HDMI_INPUT_PORT2,
    HDMI_INPUT_PORT3,
    HDMI_INPUT_PORT4,
    HDMI_INPUT_PORT_ALL,
    HDMI_INPUT_PORT_MAX,
};

/*
    V4L2_CID_HDMI_G_TIMINGINFO
*/
struct v4l2_hdmi_rect {
    unsigned short x; /**< horizontal Start Position in pixel [0,].*/
    unsigned short y; /**< vertical   Start Position in pixel [0,].*/
    unsigned short w; /**< horizontal Size(Width)    in pixel [0,].*/
    unsigned short h; /**< vertical   Size(Height)   in pixel [0,].*/
};

enum v4l2_hdmi_dolby_hdr_type {
    V4L2_HDMI_DOLBY_HDR_TYPE_SDR             = 0,
    V4L2_HDMI_DOLBY_HDR_TYPE_STANDARD_VSIF_1 = 1,
    V4L2_HDMI_DOLBY_HDR_TYPE_STANDARD_VSIF_2 = 2,
    V4L2_HDMI_DOLBY_HDR_TYPE_LOW_LATENCY     = 3,
};

struct v4l2_hdmi_timing_info {
    enum v4l2_hdmi_input_port port;
    unsigned short hFreq;         /**< ... */
    unsigned short vFreq;         /**< ... */
    unsigned short hTotal;        /**< ... */
    unsigned short vTotal;        /**< ... */
    unsigned short hPorch;        /**< ... */
    unsigned short vPorch;        /**< ... */
    struct v4l2_hdmi_rect active; /**< ... */
    unsigned short scanType;      /**< ... */
    unsigned char isDolbyHDR;
    enum v4l2_hdmi_dolby_hdr_type eDolbyHDRType;
};

/*
    V4L2_CID_HDMI_G_DRMINFO
*/
enum v4l2_hdmi_drm_eotf {
    V4L2_HDMI_DRM_EOTF_SDR_LUMINANCE_RANGE,
    V4L2_HDMI_DRM_EOTF_HDR_LUMINANCE_RANGE,
    V4L2_HDMI_DRM_EOTF_SMPTE_ST_2084,
    V4L2_HDMI_DRM_EOTF_HLG,
    V4L2_HDMI_DRM_EOTF_RESERVED_4,
    V4L2_HDMI_DRM_EOTF_RESERVED_5,
    V4L2_HDMI_DRM_EOTF_RESERVED_6,
    V4L2_HDMI_DRM_EOTF_RESERVED_7,
    V4L2_HDMI_DRM_EOTF_MAX,
};

enum v4l2_hdmi_drm_meta_desc {
    V4L2_HDMI_DRM_META_TYPE1,
    V4L2_HDMI_DRM_META_RESERVED1,
    V4L2_HDMI_DRM_META_RESERVED2,
    V4L2_HDMI_DRM_META_RESERVED3,
    V4L2_HDMI_DRM_META_RESERVED4,
    V4L2_HDMI_DRM_META_RESERVED5,
    V4L2_HDMI_DRM_META_RESERVED6,
    V4L2_HDMI_DRM_META_RESERVED7,
};

struct v4l2_hdmi_drm_info {
    enum v4l2_hdmi_input_port port;
    unsigned char nVersion;
    unsigned char nLength;
    enum v4l2_hdmi_drm_eotf eEOTFtype;
    enum v4l2_hdmi_drm_meta_desc eMeta_Desc;
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

/*
    V4L2_CID_HDMI_G_VSIINFO
*/
enum v4l2_hdmi_vsi_video_format {
    V4L2_HDMI_VSI_VIDEO_FORMAT_NO_ADDITIONAL_FORMAT, // 2D
    V4L2_HDMI_VSI_VIDEO_FORMAT_EXTENDED_RESOLUTION_FORMAT,
    V4L2_HDMI_VSI_VIDEO_FORMAT_3D_FORMAT,
};

enum v4l2_hdmi_vsi_3d_structure {
    V4L2_HDMI_VSI_3D_STRUCTURE_FRAME_PACKING, //*0

    V4L2_HDMI_VSI_3D_STRUCTURE_FIELD_ALTERNATIVE, //*1
    V4L2_HDMI_VSI_3D_STRUCTURE_LINE_ALTERNATIVE,  //*2
    V4L2_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_FULL,   //*3
    V4L2_HDMI_VSI_3D_STRUCTURE_L_DEPTH,           //*4
    V4L2_HDMI_VSI_3D_STRUCTURE_L_DEPTH_GRAPHICS,  //*5

    V4L2_HDMI_VSI_3D_STRUCTURE_TOP_BOTTOM, //*6
    /*reserved 7*/
    V4L2_HDMI_VSI_3D_STRUCTURE_SIDEBYSIDE_HALF    = 0x08,
    V4L2_HDMI_VSI_3D_STRUCTURE_TOP_BOTTOM_DIRECTV = 0x09,

};

enum v4l2_hdmi_vsi_3d_ext_data {
    V4L2_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_0,
    V4L2_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_1,
    V4L2_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_2,
    V4L2_HDMI_VSI_3D_EXT_DATA_HOR_SUB_SAMPL_3,

    V4L2_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_0 = 0x04,
    V4L2_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_1,
    V4L2_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_2,
    V4L2_HDMI_VSI_3D_EXT_DATA_QUINCUNX_MATRIX_3,

};

enum v4l2_hdmi_vsi_vic {
    V4L2_HDMI_RESERVED,
    V4L2_HDMI_VSI_VIC_4K2K_30HZ,
    V4L2_HDMI_VSI_VIC_4K2K_25HZ,
    V4L2_HDMI_VSI_VIC_4K2K_24HZ,
    V4L2_HDMI_VSI_VIC_4K2K_24HZ_SMPTE,
};

enum v4l2_hdmi_packet_status {
    V4L2_HDMI_PACKET_STATUS_NOT_RECEIVED = 0, /**< HDMI packet status */
    V4L2_HDMI_PACKET_STATUS_STOPPED,          /**< HDMI packet status */
    V4L2_HDMI_PACKET_STATUS_UPDATED,          /**< HDMI packet status */
    V4L2_HDMI_PACKET_STATUS_MAX               /**< HDMI packet status */
};

struct v4l2_hdmi_in_packet {
    unsigned char type;    /**< packet type */
    unsigned char version; /**< packet version */
    unsigned char length;  /**< packet length */
    unsigned char dataBytes[V4L2_HDMI_PACKET_DATA_LENGTH]; /**< packet data */
};

struct v4l2_hdmi_vsi {
    enum v4l2_hdmi_input_port port;
    enum v4l2_hdmi_vsi_video_format eVideoFormat; /**< HDMI VSI info */
    enum v4l2_hdmi_vsi_3d_structure e3DStructure; /**< HDMI VSI info */
    enum v4l2_hdmi_vsi_3d_ext_data e3DExtData;    /**< HDMI VSI info */

    enum v4l2_hdmi_vsi_vic eVSiVIC; /**< HDMI VSI info */

    unsigned char
        IEERegId[V4L2_HDMI_VENDOR_SPECIFIC_REGID_LEN]; /**< HDMI VSI info */
    unsigned char
        PayLoad[V4L2_HDMI_VENDOR_SPECIFIC_PAYLOAD_LEN]; /**< HDMI VSI info */
    enum v4l2_hdmi_packet_status packetStatus;          /**< HDMI VSI info */
    struct v4l2_hdmi_in_packet packet;                  /**< HDMI VSI info */
};

/*
    V4L2_CID_HDMI_G_SPDINFO
*/
struct v4l2_hdmi_spd {
    enum v4l2_hdmi_input_port port;
    unsigned char
        VendorName[V4L2_HDMI_SPD_IF_VENDOR_LEN + 1]; /** add space for NULL */
    unsigned char ProductDescription[V4L2_HDMI_SPD_IF_DESC_LEN + 1];
    unsigned char SourceDeviceInfo;
    enum v4l2_hdmi_packet_status packetStatus; /**< HDMI VSI info */
    struct v4l2_hdmi_in_packet packet;         /**< HDMI VSI info */
};

/*
    V4L2_CID_HDMI_G_AVIINFO
*/
enum v4l2_hdmi_mode {
    V4L2_HDMI_DVI,  /**< DVI signal */
    V4L2_HDMI_HDMI, /**< HDMI signal */
};

enum v4l2_hdmi_avi_csc {
    V4L2_HDMI_AVI_CSC_RGB = 0,  /**< HDMI CSC info */
    V4L2_HDMI_AVI_CSC_YCBCR422, /**< HDMI CSC info */
    V4L2_HDMI_AVI_CSC_YCBCR444, /**< HDMI CSC info */
    V4L2_HDMI_AVI_CSC_YCBCR420  /**< HDMI CSC info */
};

enum v4l2_hdmi_avi_active_info {
    V4L2_HDMI_AVI_ACTIVE_INFO_INVALID = 0, /**< HDMI info */
    V4L2_HDMI_AVI_ACTIVE_INFO_VALID        /**< HDMI info */
};

enum v4l2_hdmi_avi_bar_info {
    V4L2_HDMI_AVI_BAR_INFO_INVALID,       /**< HDMI info */
    V4L2_HDMI_AVI_BAR_INFO_VERTICALVALID, /**< HDMI info */
    V4L2_HDMI_AVI_BAR_INFO_HORIZVALID,    /**< HDMI info */
    V4L2_HDMI_AVI_BAR_INFO_VERTHORIZVALID /**< HDMI info */
};

enum v4l2_hdmi_avi_scan_info {
    V4L2_HDMI_AVI_SCAN_INFO_NODATA,       /**< HDMI info */
    V4L2_HDMI_AVI_SCAN_INFO_OVERSCANNED,  /**< HDMI info */
    V4L2_HDMI_AVI_SCAN_INFO_UNDERSCANNED, /**< HDMI info */
    V4L2_HDMI_AVI_SCAN_INFO_FUTURE = 3
};

enum v4l2_hdmi_avi_colorimetry {
    V4L2_HDMI_AVI_COLORIMETRY_NODATA = 0, /**< HDMI info */
    V4L2_HDMI_AVI_COLORIMETRY_SMPTE170,   /**< HDMI info */
    V4L2_HDMI_AVI_COLORIMETRY_ITU709,     /**< HDMI info */
    V4L2_HDMI_AVI_COLORIMETRY_FUTURE,     /**< HDMI info */
    V4L2_HDMI_AVI_COLORIMETRY_EXTENDED = V4L2_HDMI_AVI_COLORIMETRY_FUTURE

};

enum v4l2_hdmi_avi_picture_arc {
    V4L2_HDMI_AVI_PICTURE_ARC_NODATA = 0, /**< HDMI info */
    V4L2_HDMI_AVI_PICTURE_ARC_4_3,        /**< HDMI info */
    V4L2_HDMI_AVI_PICTURE_ARC_16_9,       /**< HDMI info */
    V4L2_HDMI_AVI_PICTURE_ARC_FUTURE      /**< HDMI info */
};

enum v4l2_hdmi_avi_active_format_arc {
    V4L2_HDMI_AVI_ACTIVE_FORMAT_ARC_PICTURE    = 8,  /**< HDMI info */
    V4L2_HDMI_AVI_ACTIVE_FORMAT_ARC_4_3CENTER  = 9,  /**< HDMI info */
    V4L2_HDMI_AVI_ACTIVE_FORMAT_ARC_16_9CENTER = 10, /**< HDMI info */
    V4L2_HDMI_AVI_ACTIVE_FORMAT_ARC_14_9CENTER = 11, /**< HDMI info */
    V4L2_HDMI_AVI_ACTIVE_FORMAT_ARC_OTHER      = 0   /**< HDMI info */
};

enum v4l2_hdmi_avi_scaling {
    V4L2_HDMI_AVI_SCALING_NOSCALING = 0, /**< HDMI info */
    V4L2_HDMI_AVI_SCALING_HSCALING,      /**< HDMI info */
    V4L2_HDMI_AVI_SCALING_VSCALING,      /**< HDMI info */
    V4L2_HDMI_AVI_SCALING_HVSCALING      /**< HDMI info */
};

enum v4l2_hdmi_avi_it_content {
    V4L2_HDMI_AVI_IT_CONTENT_NODATA    = 0, /**< HDMI info */
    V4L2_HDMI_AVI_IT_CONTENT_ITCONTENT = 1  /**< HDMI info */
};

enum v4l2_hdmi_avi_ext_colorimetry {
    V4L2_HDMI_AVI_EXT_COLORIMETRY_XVYCC601 = 0,
    V4L2_HDMI_AVI_EXT_COLORIMETRY_XVYCC709,
    V4L2_HDMI_AVI_EXT_COLORIMETRY_SYCC601,           // add sYCC 601
    V4L2_HDMI_AVI_EXT_COLORIMETRY_ADOBEYCC601,       // add Adobe YCC 601
    V4L2_HDMI_AVI_EXT_COLORIMETRY_ADOBERGB,          // add Adobe RGB
    V4L2_HDMI_AVI_EXT_COLORIMETRY_BT2020_YCCBCCRC,   // add BT 2020 CL
    V4L2_HDMI_AVI_EXT_COLORIMETRY_BT2020_RGBORYCBCR, // add BT 2020 NCL
    V4L2_HDMI_AVI_EXT_COLORIMETRY_XVRESERED
};

enum v4l2_hdmi_avi_rgb_quantization_range {
    V4L2_HDMI_AVI_RGB_QUANTIZATION_RANGE_DEFAULT      = 0, /**< HDMI info */
    V4L2_HDMI_AVI_RGB_QUANTIZATION_RANGE_LIMITEDRANGE = 1, /**< HDMI info */
    V4L2_HDMI_AVI_RGB_QUANTIZATION_RANGE_FULLRANGE    = 2, /**< HDMI info */
    V4L2_HDMI_AVI_RGB_QUANTIZATION_RANGE_RESERVED     = 3  /**< HDMI info */
};

enum v4l2_hdmi_avi_ycc_quantization_range {
    V4L2_HDMI_AVI_YCC_QUANTIZATION_RANGE_LIMITEDRANGE = 0, /**< HDMI info */
    V4L2_HDMI_AVI_YCC_QUANTIZATION_RANGE_FULLRANGE    = 1, /**< HDMI info */
    V4L2_HDMI_AVI_YCC_QUANTIZATION_RANGE_RESERVED     = 2  /**< HDMI info */
};

enum v4l2_hdmi_avi_content_type {
    V4L2_HDMI_AVI_CONTENT_TYPE_GRAPHICS = 0,
    V4L2_HDMI_AVI_CONTENT_TYPE_PHOTO,
    V4L2_HDMI_AVI_CONTENT_TYPE_CINEMA,
    V4L2_HDMI_AVI_CONTENT_TYPE_GAME,
    V4L2_HDMI_AVI_CONTENT_TYPE_MAX
};

struct v4l2_hdmi_avi {
    enum v4l2_hdmi_input_port port;
    enum v4l2_hdmi_mode eHDMIMode; /**< HDMI info */

    enum v4l2_hdmi_avi_csc ePixelEncoding; /**< HDMI info */
    enum v4l2_hdmi_avi_active_info eActiveInfo; /**< HDMI info */  /* A0 */
    enum v4l2_hdmi_avi_bar_info eBarInfo; /**< HDMI info */        /* B1B0 */
    enum v4l2_hdmi_avi_scan_info eScanInfo; /**< HDMI info */      /* S1S0 */
    enum v4l2_hdmi_avi_colorimetry eColorimetry; /**< HDMI info */ /* C1C0 */
    enum v4l2_hdmi_avi_picture_arc ePictureAspectRatio;
    /**< HDMI info */ /* M1M0 */
    enum v4l2_hdmi_avi_active_format_arc eActiveFormatAspectRatio;
    /**< HDMI info */                                      /* R3R0 */
    enum v4l2_hdmi_avi_scaling eScaling; /**< HDMI info */ /* SC1SC0 */

    unsigned char VideoIdCode; /**< HDMI info */ /* VICn */
    unsigned char PixelRepeat;                   /**< HDMI info */

    enum v4l2_hdmi_avi_it_content eITContent; /**< HDMI info */ /* ITC */
    enum v4l2_hdmi_avi_ext_colorimetry eExtendedColorimetry;
    /**< HDMI info */ /* EC2EC1EC0 */
    enum v4l2_hdmi_avi_rgb_quantization_range eRGBQuantizationRange;
    /**< HDMI info */ /* Q1Q0 */
    enum v4l2_hdmi_avi_ycc_quantization_range eYCCQuantizationRange;
    /**< HDMI info */ /* YQ1YQ0 */
    enum v4l2_hdmi_avi_content_type eContentType;
    /**< HDMI info */ /* Contents Type */

    /* bar info */
    unsigned short TopBarEndLineNumber;      /**< HDMI info */
    unsigned short BottomBarStartLineNumber; /**< HDMI info */
    unsigned short LeftBarEndPixelNumber;    /**< HDMI info */
    unsigned short RightBarEndPixelNumber;   /**< HDMI info */

    enum v4l2_hdmi_packet_status packetStatus; /**< HDMI info */

    struct v4l2_hdmi_in_packet packet; /**< HDMI info */
};

/*
    V4L2_CID_HDMI_G_PACKETINFO
*/
struct v4l2_hdmi_all_packet {
    enum v4l2_hdmi_input_port port;
    enum v4l2_hdmi_mode eHDMIMode; /**< HDMI info */
    struct v4l2_hdmi_avi stAVI;    /**< HDMI AVI info */
    struct v4l2_hdmi_spd stSPD;    /**< HDMI SPD info */
    struct v4l2_hdmi_vsi stVSI;    /**< HDMI VSI info */
};

/*
    V4L2_CID_HDMI_EDID
*/
enum v4l2_hdmi_edid_size {
    V4L2_HDMI_EDID_SIZE_128 = 0, /**< HDMI EDID Size 128 bytes */
    V4L2_HDMI_EDID_SIZE_256,     /**< HDMI EDID Size 256 bytes */
    V4L2_HDMI_EDID_SIZE_512,     /**< HDMI EDID Size 512 bytes */
    V4L2_HDMI_EDID_SIZE_MAX,
};

struct v4l2_hdmi_edid {
    enum v4l2_hdmi_input_port port;
    enum v4l2_hdmi_edid_size size;
    unsigned char *pData;
};

/*
    V4L2_CID_HDMI_G_CONNECTION_STATE
*/
struct v4l2_hdmi_port_state {
    enum v4l2_hdmi_input_port port;
    unsigned char hdmi5v_state;
};

/*
    V4L2_CID_HDMI_CONTROL_HPD
*/
enum v4l2_hdmi_hpd_control {
    V4L2_HDMI_HPD_CONTROL_DISABLE = 0,
    V4L2_HDMI_HPD_CONTROL_ENABLE,
    V4L2_HDMI_HPD_CONTROL_RESTART
};

struct v4l2_hdmi_hpd {
    enum v4l2_hdmi_input_port port;
    enum v4l2_hdmi_hpd_control eHPDControl;
};

/*
    V4L2_CID_HDMI_POWEROFF
*/
// NONE

void v4l2_hdmi20_header_ver_print(struct seq_file *m);
int v4l2_hdmi20_device_init(void);

#endif /* _V4L2_LGE_HDMI_H */
