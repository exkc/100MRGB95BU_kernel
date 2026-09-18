/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2024 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

#ifndef __MODELOPT_H__
#define __MODELOPT_H__

/**
 *  Type of COUNTRY (HW OPTION)
 */
typedef enum
{
    MODELOPT_COUNTRY_AJ_JA = 0,
    MODELOPT_COUNTRY_TW_CO = 1,
    MODELOPT_COUNTRY_KR = 2,
    MODELOPT_COUNTRY_EU = 3,
    MODELOPT_COUNTRY_US = 4,
    MODELOPT_COUNTRY_BR = 5,
    MODELOPT_COUNTRY_JP = 6,
    MODELOPT_COUNTRY_CN_HK = 7,
    MODELOPT_COUNTRY_NONE = 8,
    MODELOPT_COUNTRY_MAX
} MODELOPT_COUNTRY_T;

/**
 *  Type of PANEL (HW OPTION)
 */
typedef enum
{
    MODELOPT_PANEL_TYPE_NONE = 0,
    MODELOPT_PANEL_V12 = 1,
    MODELOPT_PANEL_V13 = 2,
    MODELOPT_PANEL_V14 = 3,
    MODELOPT_PANEL_V14_32inch = 4,
    MODELOPT_PANEL_V15 = 5,
    MODELOPT_PANEL_V16 = 6,
    MODELOPT_PANEL_V17 = 7,
    MODELOPT_PANEL_MAX
} MODELOPT_PANEL_T;

/**
 *  Type of PANEL INTERFACE (HW OPTION)
 */
typedef enum
{
    MODELOPT_PANEL_INTERFACE_EPI = 0,
    MODELOPT_PANEL_INTERFACE_LVDS = 1,
    MODELOPT_PANEL_INTERFACE_VBYONE = 2,
    MODELOPT_PANEL_INTERFACE_CEDS = 3,
    MODELOPT_PANEL_INTERFACE_EPI_QSAC = 4,
    MODELOPT_PANEL_INTERFACE_EDP = 5,
    MODELOPT_PANEL_INTERFACE_MAX
} MODELOPT_PANEL_INTERFACE_T;

/**
 *  Type of PANEL BANDWIDTH (HW OPTION)
 */
typedef enum
{
    MODELOPT_PANEL_BW_NONE = 0,
    MODELOPT_PANEL_BW_1_5G = 1,
    MODELOPT_PANEL_BW_2_1G = 2,
    MODELOPT_PANEL_BW_3_0G = 3,
    MODELOPT_PANEL_BW_MAX
} MODELOPT_PANEL_BW_T;

/**
 *  Type of ATSC3.0 LEGACY BOX (HW OPTION)
 */
typedef enum
{
    MODELOPT_MICOM_VENDOR_NONE = 0,
    MODELOPT_MICOM_VENDOR_RENESAS,
    MODELOPT_MICOM_VENDOR_ABOV
} MODELOPT_MICOM_VENDOR_T;

/**
 *  Type of ATSC3.0 LEGACY BOX (HW OPTION)
 */
typedef enum
{
    MODELOPT_ATSC30_LEGACYBOX_NONE = 0,
    MODELOPT_ATSC30_LEGACYBOX_NOT_SUPPORT,
    MODELOPT_ATSC30_LEGACYBOX_SUPPORT
} MODELOPT_ATSC30_LEGACYBOX_T;

/**
 *  Type of PANEL RESOLUTION (HW OPTION)
 */
typedef enum
{
    MODELOPT_PANEL_RESOLUTION_HD = 0,
    MODELOPT_PANEL_RESOLUTION_FHD = 1,
    MODELOPT_PANEL_RESOLUTION_UD = 2,
    MODELOPT_PANEL_RESOLUTION_8K = 3,
    MODELOPT_PANEL_RESOLUTION_QHD = 4,
    MODELOPT_PANEL_RESOLUTION_WQHD = 5,
    MODELOPT_PANEL_RESOLUTION_MAX
} MODELOPT_PANEL_RESOLUTION_T;

/**
 *  Type of DDR SIZE (HW OPTION)
 */
typedef enum
{
    DDR_SIZE_768M = 0,
    DDR_SIZE_1G = 1,
    DDR_SIZE_1_25G = 2,
    DDR_SIZE_1_5G = 3,
    DDR_SIZE_2G = 4,
    DDR_SIZE_2_5G = 5,
    DDR_SIZE_3G = 6,
    DDR_SIZE_2G_ADV = 7,
    DDR_SIZE_2G_STD = 8,
    DDR_SIZE_4G = 9,
    DDR_SIZE_5G = 10,
    DDR_SIZE_3_5G = 11,
    DDR_SIZE_8G = 12, // reserved for test
    DDR_SIZE_MAX
} MODELOPT_DDR_SIZE_T;

typedef enum
{
    MODELOPT_DISPLAY_LCD = 0,
    MODELOPT_DISPLAY_OLED = 1,
    MODELOPT_DISPLAY_PDP = 2,
    MODELOPT_DISPLAY_MAX
} MODELOPT_DISPLAY_T;

typedef enum
{
    MODELOPT_FRC_NONE = 0,
    MODELOPT_FRC_INTERNAL,
    MODELOPT_FRC_URSA9,
    MODELOPT_FRC_URSA9_P,
    MODELOPT_FRC_URSA11,
    MODELOPT_FRC_URSA11_P = 5,
    MODELOPT_FRC_F16,
    MODELOPT_FRC_URSA17,
    MODELOPT_FRC_F20,
    MODELOPT_FRC_F22,
    MODELOPT_FRC_MAX
} MODELOPT_FRC_T;

typedef enum
{
    MODELOPT_DIVISION_NONE = 0,
    MODELOPT_DIVISION_2,
    MODELOPT_DIVISION_3,
    MODELOPT_DIVISION_4,
    MODELOPT_DIVISION_5,
    MODELOPT_DIVISION_MAX,
} MODELOPT_DIVISION_T;

typedef enum
{
    MODELOPT_GRAPHIC_1024X768 = 0,
    MODELOPT_GRAPHIC_1366X768 = 1,    // panel resolution == HD
    MODELOPT_GRAPHIC_1920X1080 = 2,    // panel resolution == FHD or panel resolution == UHD
    MODELOPT_GRAPHIC_2560X1080 = 3,    // panel resolution == WUHD
    MODELOPT_GRAPHIC_3840X2160 = 4,    // panel resolution == UHD
    MODELOPT_GRAPHIC_5120X2160 = 5,    // panel resolution == WUHD
    MODELOPT_GRAPHIC_1280X720 = 6,    // panel resolution == webOS Lite
    MODELOPT_GRAPHIC_1920X804 = 7,    // panel resolution == wide monitor
    MODELOPT_GRAPHIC_2560X1440 = 8,    // panel resolution == QHD
    MODELOPT_GRAPHIC_MAX
} MODELOPT_GRAPHIC_RESOLUTION_T;

typedef enum
{
    MODELOPT_ODT_46_OHM = 0,
    MODELOPT_ODT_55_OHM = 1
} MODELOPT_ODT_T;

typedef enum
{
    MODELOPT_MODULE_TYPE_NONE = 0,
    MODELOPT_MODULE_TYPE_RGB = 1,
    MODELOPT_MODULE_TYPE_RGBW = 2,
    MODELOPT_MODULE_TYPE_MPLUS = 3,
    MODELOPT_MODULE_TYPE_MAX
} MODELOPT_MODULE_T;

typedef enum
{
    MODELOPT_MHL_OPT_NONE = 0,
    MODELOPT_MHL_SUPPORT = 1,
    MODELOPT_MHL_NOT_SUPPORT = 2,
    MODELOPT_MHL_MAX
} MODELOPT_MHL_T;

typedef enum
{
    MODELOPT_SMHL_OPT_NONE = 0,
    MODELOPT_SMHL_SUPPORT = 1,
    MODELOPT_SMHL_NOT_SUPPORT = 2,
    MODELOPT_SMHL_MAX
} MODELOPT_SUPER_MHL_T;

typedef enum
{
    MODELOPT_TUNER_TYPE_NONE = 0,
    MODELOPT_TUNER_TYPE_Y15 = 1,
    MODELOPT_TUNER_TYPE_Y16 = 2,
    MODELOPT_TUNER_TYPE_MAX
} MODELOPT_TUNER_T;

typedef enum
{
    MODELOPT_AMP_GAIN_NONE = 0,
    MODELOPT_AMP_GAIN_4_3 = 1,
    MODELOPT_AMP_GAIN_1_5 = 2,
    MODELOPT_AMP_GAIN_MAX
} MODELOPT_AMP_GAIN_T;

typedef enum
{
    MODELOPT_MODELTYPE_NONE = 0,
    MODELOPT_MODELTYPE_W9,
    MODELOPT_MODELTYPE_G9,
    MODELOPT_MODELTYPE_R9,
    MODELOPT_MODELTYPE_WX,
    MODELOPT_MODELTYPE_RX,
    MODELOPT_MODELTYPE_M2,
    MODELOPT_MODELTYPE_ART90,
    MODELOPT_MODELTYPE_BENDABLE,
} MODELOPT_MODELTYPE_T;

typedef enum
{
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_60HZ = 0,
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_120HZ = 1,
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_144HZ = 2,
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_165HZ = 3,
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_240HZ = 4,
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_100HZ = 5,
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_180HZ = 6,
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_MAX = 0xff
} MODELOPT_PANEL_OUTPUT_FRAME_RATE_T;

typedef enum
{
    MODELOPT_SOC_OUTPUT_FRAME_RATE_60HZ = 0,
    MODELOPT_SOC_OUTPUT_FRAME_RATE_120HZ = 1,
    MODELOPT_SOC_OUTPUT_FRAME_RATE_144HZ = 2,
    MODELOPT_SOC_OUTPUT_FRAME_RATE_165HZ = 3,
    MODELOPT_SOC_OUTPUT_FRAME_RATE_240HZ = 4,
    MODELOPT_SOC_OUTPUT_FRAME_RATE_100HZ = 5,
    MODELOPT_SOC_OUTPUT_FRAME_RATE_180HZ = 6,
    MODELOPT_SOC_OUTPUT_FRAME_RATE_MAX = 0xff
} MODELOPT_SOC_OUTPUT_FRAME_RATE_T;

/* PMICType */
typedef enum
{
    MODELOPT_PMIC_SILICON_WORKS = 0,
    MODELOPT_PMIC_RICHTEK = 1,
    MODELOPT_PMIC_GMT = 2,
    MODELOPT_PMIC_DEFAULT = 3,
    MODELOPT_PMIC_ONECHIP = 4,
    MODELOPT_PMIC_PMIC_P_SUBPMIC = 5,
    MODELOPT_PMIC_PMIC_MAX,
} MODELOPT_PMIC_TYPE_T;

/**
 *  Type of Model
 */
typedef enum
{
    MODEL_TYPE_NON_BOX = 0,
    MODEL_TYPE_BBZ4 = 1,
    MODEL_TYPE_LX3Q = 2,
    MODEL_TYPE_M4 = 3,
    MODEL_TYPE_MEDIA_STA = 4,
    MODEL_TYPE_M4_TOLED = 5,
    MODEL_TYPE_INTELLI_FIT = 6,
    MODEL_TYPE_MAX
} MODEL_TYPE_T;

/**
* for special model
*
**/
typedef enum
{
    SPECIAL_MODEL_NONE = 0,
    SPECIAL_MODEL_WIRELESSAV = 1,
    SPECIAL_MODEL_MEDIA_STA = 2,
    SPECIAL_MODEL_TOLED = 3,
    SPECIAL_MODEL_INTELLI_FIT = 4,
} SPECIAL_MODEL_T;

///////////////////////////////////////////////////////////////////////////////////////////////////
// SIC extention
//
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum
{
    MODELOPT_SYS_BOARD = 0,    // default
    MODELOPT_SLT_BOARD,
    MODELOPT_FPGA_BOARD,
} MODELOPT_BOARD_T;

typedef enum
{
    MODELOPT_HDMI_OUTPUT_NONE = 0,
    MODELOPT_HDMI_OUTPUT_60HZ,
    MODELOPT_HDMI_OUTPUT_60HZ_FIXED,
} MODELOPT_HDMI_OUTPUT_T;

/* indent-ignore-start */

struct board_opts
{
    /* basic */
    MODELOPT_COUNTRY_T country_type;                    // opt[0]
    unsigned int support_5byte_vx1_mode;                // opt[1]
    MODELOPT_PANEL_INTERFACE_T panel_interface;         // opt[2]
    MODELOPT_PANEL_RESOLUTION_T panel_resolution;       // opt[3]
    unsigned int support_optic;                         // opt[4]
    MODELOPT_PANEL_T panel_type;                        // opt[5]
    unsigned int rsvd_a[2];
    unsigned int support_tuner;                         // opt[8]
    MODELOPT_PANEL_OUTPUT_FRAME_RATE_T panel_output_frame_rate; // opt[9]
    MODELOPT_DDR_SIZE_T ddr_size;                       // opt[10]
    unsigned int rsvd_b[3];
    MODELOPT_GRAPHIC_RESOLUTION_T graphic_resolution;   // opt[14]
    unsigned int rsvd_c[2];
    MODELOPT_FRC_T frc_type;                            // opt[17]

    /* extention */
    MODELOPT_HDMI_OUTPUT_T hdmi_output;
    MODELOPT_BOARD_T board_type;
    unsigned int rsvd_d[8];

    unsigned int official;

    struct
    {
        struct
        {
            uint32_t clock;     // unit: MHz
            uint32_t size;      // unit: MB
            uint32_t m0;        // unit: MB
            uint32_t m1;        // unit: MB
            uint32_t m2;        // unit: MB
        } ddr;

    } soc;
};
/* indent-ignore-end */

struct board_opts get_board_opts(void);

#endif                /* __MODELOPT_H__ */
