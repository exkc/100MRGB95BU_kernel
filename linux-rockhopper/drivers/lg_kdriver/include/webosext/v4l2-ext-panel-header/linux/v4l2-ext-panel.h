/*
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018~2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 */

#ifndef _V4L2_EXT_PANEL_H
#define _V4L2_EXT_PANEL_H

#include <linux/v4l2-controls.h>

#define V4L2_EXT_DEV_NO_BACKEND 40

//
// User-class control Bases
//

#define V4L2_CID_USER_EXT_VBE_BASE (V4L2_CID_USER_BASE + 0x4000)
#define V4L2_CID_USER_EXT_ID_VBE_BASE (V4L2_CID_USER_EXT_VBE_BASE + 0xA00)
#define V4L2_EXT_DEV_PATH_BACKEND "/dev/video40"

/* VBE */
enum v4l2_ext_vbe_panel_inch {
  V4L2_EXT_VBE_PANEL_INCH_22 = 0,
  V4L2_EXT_VBE_PANEL_INCH_23,
  V4L2_EXT_VBE_PANEL_INCH_24,
  V4L2_EXT_VBE_PANEL_INCH_26,
  V4L2_EXT_VBE_PANEL_INCH_27,
  V4L2_EXT_VBE_PANEL_INCH_28,
  V4L2_EXT_VBE_PANEL_INCH_32,
  V4L2_EXT_VBE_PANEL_INCH_39,
  V4L2_EXT_VBE_PANEL_INCH_40,
  V4L2_EXT_VBE_PANEL_INCH_42,
  V4L2_EXT_VBE_PANEL_INCH_43,
  V4L2_EXT_VBE_PANEL_INCH_47,
  V4L2_EXT_VBE_PANEL_INCH_49,
  V4L2_EXT_VBE_PANEL_INCH_50,
  V4L2_EXT_VBE_PANEL_INCH_55,
  V4L2_EXT_VBE_PANEL_INCH_58,
  V4L2_EXT_VBE_PANEL_INCH_60,
  V4L2_EXT_VBE_PANEL_INCH_65,
  V4L2_EXT_VBE_PANEL_INCH_70,
  V4L2_EXT_VBE_PANEL_INCH_75,
  V4L2_EXT_VBE_PANEL_INCH_77,
  V4L2_EXT_VBE_PANEL_INCH_79,
  V4L2_EXT_VBE_PANEL_INCH_84,
  V4L2_EXT_VBE_PANEL_INCH_86,
  V4L2_EXT_VBE_PANEL_INCH_98,
  V4L2_EXT_VBE_PANEL_INCH_105,
  V4L2_EXT_VBE_PANEL_INCH_48, // 17Y Added
  V4L2_EXT_VBE_PANEL_INCH_MAX
};

enum v4l2_ext_vbe_panel_maker {
  V4L2_EXT_VBE_PANEL_MAKER_LGD = 0,
  V4L2_EXT_VBE_PANEL_MAKER_AUO,
  V4L2_EXT_VBE_PANEL_MAKER_SHARP,
  V4L2_EXT_VBE_PANEL_MAKER_BOE,
  V4L2_EXT_VBE_PANEL_MAKER_CSOT,
  V4L2_EXT_VBE_PANEL_MAKER_INNOLUX,
  V4L2_EXT_VBE_PANEL_MAKER_LGD_M,
  V4L2_EXT_VBE_PANEL_MAKER_ODM_B,
  V4L2_EXT_VBE_PANEL_MAKER_BOE_TPV,
  V4L2_EXT_VBE_PANEL_MAKER_HKC,
  V4L2_EXT_VBE_PANEL_MAKER_MAX
};

/**
 * Panel interface
 */
enum v4l2_ext_vbe_panel_interface {
  V4L2_EXT_VBE_PANEL_EPI = 0,
  V4L2_EXT_VBE_PANEL_LVDS,
  V4L2_EXT_VBE_PANEL_Vx1,
  V4L2_EXT_VBE_PANEL_CEDS,
  V4L2_EXT_VBE_PANEL_EPI_QSAC,
  V4L2_EXT_VBE_PANEL_EDP,
  V4L2_EXT_VBE_PANEL_RESERVED1,
  V4L2_EXT_VBE_PANEL_INTERFACE_MAX
};

/**
  * Panel Resolution
  */
enum v4l2_ext_vbe_panel_resolution {
  V4L2_EXT_VBE_PANEL_RESOLUTION_1024X768 = 0,
  V4L2_EXT_VBE_PANEL_RESOLUTION_1280X720,
  V4L2_EXT_VBE_PANEL_RESOLUTION_1366X768,
  V4L2_EXT_VBE_PANEL_RESOLUTION_1920X1080,
  V4L2_EXT_VBE_PANEL_RESOLUTION_2560X1080,
  V4L2_EXT_VBE_PANEL_RESOLUTION_3840X2160,
  V4L2_EXT_VBE_PANEL_RESOLUTION_5120X2160,
  V4L2_EXT_VBE_PANEL_RESOLUTION_7680X4320,
  V4L2_EXT_VBE_PANEL_RESOLUTION_2560X1440,
  V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED1,
  V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED2,
  V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED3,
  V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED4,
  V4L2_EXT_VBE_PANEL_RESOLUTION_MAX
};

/**
* Panel version
*/
enum v4l2_ext_vbe_panel_version {
  V4L2_EXT_VBE_PANEL_NONE = 0,
  V4L2_EXT_VBE_PANEL_V12,
  V4L2_EXT_VBE_PANEL_V13,
  V4L2_EXT_VBE_PANEL_V14,
  V4L2_EXT_VBE_PANEL_V15,
  V4L2_EXT_VBE_PANEL_V16,
  V4L2_EXT_VBE_PANEL_V17,
  V4L2_EXT_VBE_PANEL_V18,
  V4L2_EXT_VBE_PANEL_MAX
};

/**
* Panel Framerate
*/
enum v4l2_ext_vbe_panel_framerate {
  V4L2_EXT_VBE_PANEL_FRAMERATE_60HZ,
  V4L2_EXT_VBE_PANEL_FRAMERATE_120HZ,
  V4L2_EXT_VBE_PANEL_FRAMERATE_144HZ,
  V4L2_EXT_VBE_PANEL_FRAMERATE_165HZ,
  V4L2_EXT_VBE_PANEL_FRAMERATE_240HZ,
  V4L2_EXT_VBE_PANEL_FRAMERATE_100HZ,
  V4L2_EXT_VBE_PANEL_FRAMERATE_180HZ,
  V4L2_EXT_VBE_PANEL_FRAMERATE_MAX
};

/**
 * Backlight Type Enum  related with Tool OPT
*/
enum v4l2_ext_vbe_panel_backlight_type {
  V4L2_EXT_VBE_PANEL_BL_DIRECT_L = 0,
  V4L2_EXT_VBE_PANEL_BL_EDGE_LED,
  V4L2_EXT_VBE_PANEL_BL_OLED,
  V4L2_EXT_VBE_PANEL_BL_DIRECT_VI,
  V4L2_EXT_VBE_PANEL_BL_DIRECT_SKY,
  V4L2_EXT_VBE_PANEL_BL_MAX
};

/**
* Panel Led_bar Type Enum inidicates number of blocks.
*/
enum v4l2_ext_vbe_panel_led_bar_type {
  V4L2_EXT_VBE_PANEL_LED_BAR_6 = 0,
  V4L2_EXT_VBE_PANEL_LED_BAR_12,
  V4L2_EXT_VBE_PANEL_LED_BAR_36,
  V4L2_EXT_VBE_PANEL_LED_BAR_40,
  V4L2_EXT_VBE_PANEL_LED_BAR_48,
  V4L2_EXT_VBE_PANEL_LED_BAR_50,
  V4L2_EXT_VBE_PANEL_LED_BAR_96,
  V4L2_EXT_VBE_PANEL_LED_BAR_MAX
};

/**
* Panel Cell type
*/
enum v4l2_ext_vbe_panel_cell_type {
  V4L2_EXT_VBE_PANEL_CELL_TYPE_RGB = 0,
  V4L2_EXT_VBE_PANEL_CELL_TYPE_RGBW, // M+
  V4L2_EXT_VBE_PANEL_CELL_TYPE_MAX
};

/**
* Display Output Lane Bandwidth.
*/
enum v4l2_ext_vbe_panel_bandwidth {
  V4L2_EXT_VBE_PANEL_BANDWIDTH_DEFAULT = 0,
  V4L2_EXT_VBE_PANEL_BANDWIDTH_1_5G,
  V4L2_EXT_VBE_PANEL_BANDWIDTH_2_1G,
  V4L2_EXT_VBE_PANEL_BANDWIDTH_3_0G,
  V4L2_EXT_VBE_PANEL_BANDWIDTH_MAX
};

/**
* FRC Chip type
*/
enum v4l2_ext_vbe_frc_chip {
  V4L2_EXT_VBE_FRC_CHIP_NONE = 0,  // No FRC
  V4L2_EXT_VBE_FRC_CHIP_INTERNAL,  // Use internal FRC
  V4L2_EXT_VBE_FRC_CHIP_EXTERNAL1, // Reserved1
  V4L2_EXT_VBE_FRC_CHIP_EXTERNAL2, // Reserved2
  V4L2_EXT_VBE_FRC_CHIP_TYPE_MAX
};

/**
 * LVDS bit depth.
*/
enum v4l2_ext_vbe_lvds_colordepth {
  V4L2_EXT_VBE_LVDS_COLOR_DEPTH_8BIT,
  V4L2_EXT_VBE_LVDS_COLOR_DEPTH_10BIT,
  V4L2_EXT_VBE_LVDS_COLOR_DEPTH_MAX
};

/**
 * LVDS type.
*/
enum v4l2_ext_vbe_lvds_type {
  V4L2_EXT_VBE_LVDS_TYPE_VESA,
  V4L2_EXT_VBE_LVDS_TYPE_JEIDA,
  V4L2_EXT_VBE_LVDS_TYPE_MAX
};

/**
* Display User Option
*/
union v4l2_ext_vbe_user_option {
  unsigned int all; // All flags enabled
  struct _flags {
    unsigned int SocOptionBIT0 : 1, SocOptionBIT1 : 1, SocOptionBIT2 : 1,
        SocOptionBIT3 : 1, SocOptionBIT4 : 1, SocOptionBIT5 : 1,
        SocOptionBIT6 : 1, SocOptionBIT7 : 1, SocOptionBIT8 : 1,
        SocOptionBIT9 : 1, SocOptionBIT10 : 1, SocOptionBIT11 : 1,
        SocOptionBIT12 : 1, SocOptionBIT13 : 1, SocOptionBIT14 : 1,
        SocOptionBIT15 : 1, SocOptionBIT16 : 1, SocOptionBIT17 : 1,
        SocOptionBIT18 : 1, SocOptionBIT19 : 1, SocOptionBIT20 : 1,
        SocOptionBIT21 : 1, SocOptionBIT22 : 1, SocOptionBIT23 : 1,
        SocOptionBIT24 : 1, SocOptionBIT25 : 1, SocOptionBIT26 : 1,
        SocOptionBIT27 : 1, SocOptionBIT28 : 1, SocOptionBIT29 : 1,
        SocOptionBIT30 : 1, SocOptionBIT31 : 1;
  } flags;
};

// clang-format off
/**
 * @brief  Struct for panel information
 *
 * Used by V4L2_CID_EXT_VBE_INIT
 *
 * Panel information is shared to v4l2 driver.
 * But no speicific setting is not required with this information.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *      struct v4l2_ext_vbe_panel_info {
 *          enum v4l2_ext_vbe_panel_inch panelInch;               // Panel Inch
 *          enum v4l2_ext_vbe_panel_maker panelMaker;             // Panel maker
 *          enum v4l2_ext_vbe_panel_interface panelInterface;     // Panel Interface
 *          enum v4l2_ext_vbe_panel_resolution panelResolution;   // Panel Resolution
 *          enum v4l2_ext_vbe_panel_version panelVersion;         // Panel Version
 *          enum v4l2_ext_vbe_panel_framerate panelFrameRate;     // Panel Frame Rate
 *          enum v4l2_ext_vbe_panel_led_bar_type panelLedBarType; // LED bar type
 *          enum v4l2_ext_vbe_panel_backlight_type
 *              panelBacklightType;                            // LED Backlight type
 *          enum v4l2_ext_vbe_panel_cell_type panelCellType;   // Panel Cell type
 *          enum v4l2_ext_vbe_panel_bandwidth dispOutLaneBW;   // Output lane bandwidth
 *          enum v4l2_ext_vbe_frc_chip frcType;                // FRC type
 *          enum v4l2_ext_vbe_lvds_colordepth lvdsColorDepth;  // LVDS Color depth
 *          enum v4l2_ext_vbe_lvds_type lvdsType;              // LVDS Type
 *          union v4l2_ext_vbe_user_option userSpecificOption; // Reserved Options
 *      };
 *
 * @endrst
 */
// clang-format on
struct v4l2_ext_vbe_panel_info {
  enum v4l2_ext_vbe_panel_inch panelInch;               // Panel Inch
  enum v4l2_ext_vbe_panel_maker panelMaker;             // Panel maker
  enum v4l2_ext_vbe_panel_interface panelInterface;     // Panel Interface
  enum v4l2_ext_vbe_panel_resolution panelResolution;   // Panel Resolution
  enum v4l2_ext_vbe_panel_version panelVersion;         // Panel Version
  enum v4l2_ext_vbe_panel_framerate panelFrameRate;     // Panel Frame Rate
  enum v4l2_ext_vbe_panel_led_bar_type panelLedBarType; // LED bar type
  enum v4l2_ext_vbe_panel_backlight_type
      panelBacklightType;                            // LED Backlight type
  enum v4l2_ext_vbe_panel_cell_type panelCellType;   // Panel Cell type
  enum v4l2_ext_vbe_panel_bandwidth dispOutLaneBW;   // Output lane bandwidth
  enum v4l2_ext_vbe_frc_chip frcType;                // FRC type
  enum v4l2_ext_vbe_lvds_colordepth lvdsColorDepth;  // LVDS Color depth
  enum v4l2_ext_vbe_lvds_type lvdsType;              // LVDS Type
  union v4l2_ext_vbe_user_option userSpecificOption; // Reserved Options
};

// clang-format off
/**
 * @brief  Struct for spread spectrum control
 *
 * Used by V4L2_CID_EXT_VBE_SSC
 *
 * Fixed as on_off=on, percent=1, period=1
 * If percent is 11, driver set SSC percent as 1.1 %.
 * If Period is 253, driver set SSC frequency as 25.3 KHz.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *      struct v4l2_ext_vbe_ssc {
 *          unsigned int on_off;    //enable or disable spread spectrum
 *          unsigned short percent; // unit 0.1%
 *         unsigned short period;   // unit 0.1khz
 *      };
 *
 * @endrst
 */
// clang-format on
struct v4l2_ext_vbe_ssc {
  unsigned int on_off;
  unsigned short percent;
  unsigned short period;
};

// clang-format off
/**
 * @brief  Struct for mirror mode setting
 *
 * Used by V4L2_CID_EXT_VBE_MIRROR
 * Called at AC ON or DC ON time.
 * Specific model may request this feature.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_vbe_mirror {
 *         unsigned int bIsH; // Horizontal reversed
 *         unsigned int bIsV; // Vertical reversed
 *     };
 *
 * @endrst
 */
// clang-format on
struct v4l2_ext_vbe_mirror {
  unsigned int bIsH;
  unsigned int bIsV;
};

enum v4l2_ext_vbe_mplus_mode {
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE0 =
      0,                           // V4L2_EXT_VBE_MPLUS_HIGH_LUM1_MSE_ON = 0,
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE1,  // V4L2_EXT_VBE_MPLUS_HIGH_LUM2,
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE2,  // V4L2_EXT_VBE_MPLUS_LOW_POWER1,
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE3,  // V4L2_EXT_VBE_MPLUS_MLE_MODE_OFF,
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE4,  // V4L2_EXT_VBE_MPLUS_HIGH_LUM1_MSE_OFF,
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE5,  // V4L2_EXT_VBE_MPLUS_LOW_POWER2,
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE6,  // V4L2_EXT_VBE_MPLUS_LOW_POWER2_SC_OFF,
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE7,  // MHE Mode1 09/20/2018
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE8,  // MHE Mode2 09/20/2018
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE9,  // MHE Mode3 09/20/2018
  V4L2_EXT_VBE_MPLUS_MPLUS_MODE10, // MHE Mode4 09/20/2018
  V4L2_EXT_VBE_MPLUS_MPLUS_MODEMAX
};

// clang-format off
/**
 * @brief  Struct for Digital Gamma Adjust setting in embedded TCON
 *
 * Used by V4L2_CID_EXT_VBE_DGA4CH
 * Called at AC ON or DC ON time.
 * When EPI or CEDS interface with embedded TCON is used, this is called.
 *
 * This function is used for RGB model and RGBW model.
 * Digital Gamma(DGA) 4CH(R,G,B,W) setting in TCON Block.
 * The data counts are 1024 each channel. The data resolution is 10bit.
 * If RGB model, The all data of pWhiteGammaTable is discarded.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_vbe_mirror {
 *         unsigned int bIsH; // Horizontal reversed
 *         unsigned int bIsV; // Vertical reversed
 *     };
 *
 * @endrst
 */
// clang-format on
struct v4l2_ext_vbe_dga4ch {
  union {
    unsigned int *pRedGammaTable;
    unsigned int compat_data_red;
    unsigned long long sizer_red;
  };
  union {
    unsigned int *pGreenGammaTable;
    unsigned int compat_data_green;
    unsigned long long sizer_green;
  };
  union {
    unsigned int *pBlueGammaTable;
    unsigned int compat_data_blue;
    unsigned long long sizer_blue;
  };
  union {
    unsigned int *pWhiteGammaTable;
    unsigned int compat_data_white;
    unsigned long long sizer_white;
  };
};

/**
 * @brief  Struct for Mplus parameter
 *
 * Used by V4L2_CID_EXT_VBE_MPLUS_PARAM
 *
 * Deprecated
 * @endrst
 */
struct v4l2_ext_vbe_mplus_param {
  unsigned short nFrameGainLimit;
  unsigned short nPixelGainLimit;
};

/**
 * @brief  Struct for internal pattern
 *
 * Used by V4L2_CID_EXT_VBE_INNER_PATTERN
 *
 * @endrst
 */
struct v4l2_ext_vbe_inner_pattern {
  unsigned char bOnOff;
  unsigned char ip;
  unsigned char type;
};

// clang-format off
/**
 * @brief  Struct for TSCIC data
 *
 * Used by V4L2_CID_EXT_VBE_TSCIC
 * It is supported in the LGD EPI panel only
 *
 * This function is for setting TSCIC function of embedded TCON.
 * It will load an TSCIC data to embedded TCON.
 * TSCIC means Time Sharing Clear Image Creation
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_vbe_panel_tscic {
 *         union {
 *            unsigned char *u8pControlTbl;
 *            unsigned int compat_data_ctrl;
 *            unsigned long long sizer_ctrl;
 *         };
 *         unsigned int u32Ctrlsize;
 *         union {
 *            unsigned int *u32pTSCICTbl;
 *            unsigned int compat_data_tscic;
 *            unsigned long long sizer_tscic;
 *         };
 *         unsigned int u32Tscicsize;
 *     };
 *
 * @endrst
 */
// clang-format on
struct v4l2_ext_vbe_panel_tscic {
  union {
    unsigned char *u8pControlTbl;
    unsigned int compat_data_ctrl;
    unsigned long long sizer_ctrl;
  };
  unsigned int u32Ctrlsize;
  union {
    unsigned int *u32pTSCICTbl;
    unsigned int compat_data_tscic;
    unsigned long long sizer_tscic;
  };
  unsigned int u32Tscicsize;
};

/**
 * @brief  Struct for LGD and BOE M+ panel register
 *
 * Used by V4L2_CID_EXT_VBE_MPLUS_DATA
 * Deprecated
  * @endrst
 */
struct v4l2_ext_vbe_mplus_data {
  union {
    void *pRegisterSet;
    unsigned int compat_data;
    unsigned long long sizer;
  };
  unsigned char nPanelMaker;
};

/**
 * @brief  Enum for PWM device pin number
 *
 * Used by v4l2_ext_vbe_pwm_param struct
 * The total number of pin may be different from that of supported device.
 * @endrst
 */
enum v4l2_ext_vbe_pwm_pin_sel {
  V4L2_EXT_VBE_PWM_DEV_PIN0 = 0,    // PWM device pin 0
  V4L2_EXT_VBE_PWM_DEV_PIN1,        // PWM device pin 1
  V4L2_EXT_VBE_PWM_DEV_PIN2,        // PWM device pin 2
  V4L2_EXT_VBE_PWM_DEV_PIN3,        // PWM device pin 3
  V4L2_EXT_VBE_PWM_DEV_PIN4,        // PWM device pin 4
  V4L2_EXT_VBE_PWM_DEV_MAX,         // Max
  V4L2_EXT_VBE_PWM_DEV_NONE = 0xFF, // Not used
};

// clang-format off
/**
 * @brief  Struct for adaptive frequency mode and each frequency information of PWM
 *
 * Used by v4l2_ext_vbe_pwm_param
 * This structure describes the adaptive frequency mode and each frequency information.
 * The adaptive frequency mode is that the pwm frequency should be followed by vsync output frequency.
 * If the pwm_adapt_freq_enable is TURE, refer to pwmfreq_40nHz, pwmfreq_50nHz and pwmfreq_60nHz.
 *
 * pwm_adapt_freq_enable:
 *    The adaptive frequency mode
 *    Enable or disable the adaptive frequency mode.
 *    If it is disable, pwm driver set the frequency with the "pwm_frequency" member of v4l2_ext_vbe_pwm_param_data.
 *    If it is enable, pwm driver doesn't set frequency with the "pwm_frequency" member of v4l2_ext_vbe_pwm_param_data.
 *    Driver should use the parameters(pwmfreq_48nHz, pwmfreq_50nHz, pwmfreq_60nHz) for setting frequency.
 *    When there is changes for video output frame rate, pwm driver should change the frequency using the parameters(pwmfreq_48nHz, pwmfreq_50nHz, pwmfreq_60nHz) by itself.
 * pwmfreq_48nHz:
 *    PWM frequency 48xN Hz
 *    This value will be 48 or 96 or 48xN Hz.
 *    If the video output frame rate is 48xN Hz, use this member for setting pwm frequency.
 * pwmfreq_50nHz:
 *    PWM frequency 50xN Hz
 *    This value will be 50 or 100 or 50xN Hz.
 *    If the video output frame rate is 50xN Hz, use this member for setting pwm frequency.
 * pwmfreq_60nHz:
 *    PWM frequency 60xN Hz
 *    This value will be 60 or 120 or 60xN Hz.
 *    If the video output frame rate is 60xN Hz, use this member for setting pwm frequency.
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     struct v4l2_ext_vbe_pwm_adapt_freq_param {
 *        unsigned int pwm_adapt_freq_enable;
 *        unsigned int pwmfreq_48nHz; // PWM frequency 48xN Hz from DB table
 *        unsigned int pwmfreq_50nHz; // PWM frequency 50xN Hz from DB table
 *        unsigned int pwmfreq_60nHz; // PWM frequency 60xN Hz from DB table
 *     };
 *
 * @endrst
 */
// clang-format on
struct v4l2_ext_vbe_pwm_adapt_freq_param {
  unsigned int pwm_adapt_freq_enable;
  unsigned int pwmfreq_48nHz; // PWM frequency 48xN Hz from DB table
  unsigned int pwmfreq_50nHz; // PWM frequency 50xN Hz from DB table
  unsigned int pwmfreq_60nHz; // PWM frequency 60xN Hz from DB table
};

// clang-format off
/**
 * @brief  Struct for pwm parameter
 *
 * Used by v4l2_ext_vbe_pwm_param struct
 *
 * pwm_enable:
 *     Enables or disables PWM
 * pwm_duty:
 *      PWM dutycycle. The range is from 0 to 255.
 * pwm_frequency:
 *      Frequency for no adaptive frequency mode.
 *      If the `pwm_adapt_freq_enable` of `v4l2_ext_vbe_pwm_adapt_freq_param` is false, pwm driver should set the frequency with this parameter.
 *      Also, driver doesn't need to follow video output frame rate.
 * pwm_adapt_freq_param:
 *      Parameter for the adpative frequency mode.
 *      Refer to the 'v4l2_ext_vbe_pwm_adapt_freq_param' description.
 * pwm_lock:
 *      Enables or disables PWM vsync alignment.
 *      true means PWM frequency is locking automatically for input Vsync ( EX: input Vfreq is 60, PWM is 120Hz for LCD 120HZ model )
 *      false =>  PWM frequency is set by   pwm_frequency parameter.
 * pwm_pos_start:
 *      This means how much the phase will be shift. The range of this value is 0 to 255.
 *      0 means no shift. 255 means the signal has 360 degree phase shift.
 * pwm_scanning_enable:
 *      If it needs phase shift mode, This will be enabled.
 *      If you can support pwm_pos_start, you don't use this flag.
 * pwm_low_power_mode:
 *      This set low power mode and used in the old lg soc.
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *    struct v4l2_ext_vbe_pwm_param_data {
 *        unsigned int pwm_enable;
 *        unsigned int pwm_duty;
 *        unsigned int pwm_frequency; // When pwm_adapt_freq_enable is TRUE, this is ignored
 *        struct v4l2_ext_vbe_pwm_adapt_freq_param pwm_adapt_freq_param;
 *        unsigned int pwm_lock;
 *        unsigned int pwm_pos_start;
 *        unsigned int pwm_scanning_enable;
 *        unsigned int pwm_low_power_enable; // It has been used to set low power mode
 *                                           // for M16P only until now, 170210.
 *    };

 * @endrst
 */
// clang-format on
struct v4l2_ext_vbe_pwm_param_data {
  unsigned int pwm_enable;
  unsigned int pwm_duty;
  unsigned int pwm_frequency; // If pwm_adapt_freq_enable == TRUE, ignored
  struct v4l2_ext_vbe_pwm_adapt_freq_param pwm_adapt_freq_param;
  unsigned int pwm_lock;
  unsigned int pwm_pos_start;
  unsigned int pwm_scanning_enable;
  unsigned int pwm_low_power_enable; // It has been used to set low power mode
                                     // for M16P only until now, 170210.
};

// clang-format off
/**
 * @brief  Enum for PWM device pin selection
 *
 * Used by V4L2_CID_EXT_VBE_PWM_APPLY_PARAM
 *
 * This function is for setting TSCIC function of embedded TCON.
 * It will load an TSCIC data to embedded TCON.
 * TSCIC means Time Sharing Clear Image Creation
 *
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *      enum v4l2_ext_vbe_pwm_pin_sel_mask {
 *          V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK = 1
 *                                  << V4L2_EXT_VBE_PWM_DEV_PIN0,   // Mask for PWM device pin 0
 *          V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK = 1
 *                                  << V4L2_EXT_VBE_PWM_DEV_PIN1,   // Mask for PWM device pin 1
 *          V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK = 1
 *                                  << V4L2_EXT_VBE_PWM_DEV_PIN2,   // Mask for PWM device pin 2
 *          V4L2_EXT_VBE_PWM_DEV_PIN_3_MASK = 1
 *                                  << V4L2_EXT_VBE_PWM_DEV_PIN3,   // Mask for PWM device pin 3
 *          V4L2_EXT_VBE_PWM_DEV_PIN_4_MASK = 1
 *                                  << V4L2_EXT_VBE_PWM_DEV_PIN4,   // Mask for PWM device pin 4
 *
 *         V4L2_EXT_VBE_PWM_DEV_PIN_0_1_MASK =
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK |
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK,   // Mask for PWM device pin 0 and 1
 *         V4L2_EXT_VBE_PWM_DEV_PIN_0_2_MASK =
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK |
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK,   // Mask for PWM device pin 0 and 2
 *         V4L2_EXT_VBE_PWM_DEV_PIN_1_2_MASK =
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK |
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK,   // Mask for PWM device pin 1 and 2
 *
 *         //
 *         V4L2_EXT_VBE_PWM_DEV_PIN_ALL_MASK =
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK |
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_3_MASK |
 *                               V4L2_EXT_VBE_PWM_DEV_PIN_4_MASK,   // Mask for all PWM pins
 *
 *         V4L2_EXT_VBE_PWM_DEV_PIN_DEFAULT_MASK // Depend on pwmIndex setting of V4L2_CID_EXT_VBE_PWM_APPLY_PARAM command
 *      };
 *
 * @endrst
 */
// clang-format on
enum v4l2_ext_vbe_pwm_pin_sel_mask {
  V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK =
      1 << V4L2_EXT_VBE_PWM_DEV_PIN0, // Mask for PWM device pin 0
  V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK =
      1 << V4L2_EXT_VBE_PWM_DEV_PIN1, // Mask for PWM device pin 1
  V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK =
      1 << V4L2_EXT_VBE_PWM_DEV_PIN2, // Mask for PWM device pin 2
  V4L2_EXT_VBE_PWM_DEV_PIN_3_MASK =
      1 << V4L2_EXT_VBE_PWM_DEV_PIN3, // Mask for PWM device pin 3
  V4L2_EXT_VBE_PWM_DEV_PIN_4_MASK =
      1 << V4L2_EXT_VBE_PWM_DEV_PIN4, // Mask for PWM device pin 4

  V4L2_EXT_VBE_PWM_DEV_PIN_0_1_MASK =
      V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK |
      V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK, // Mask for PWM device pin 0 and 1
  V4L2_EXT_VBE_PWM_DEV_PIN_0_2_MASK =
      V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK |
      V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK, // Mask for PWM device pin 0 and 2
  V4L2_EXT_VBE_PWM_DEV_PIN_1_2_MASK =
      V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK |
      V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK, // Mask for PWM device pin 1 and 2

  /* If necessary, add case */
  V4L2_EXT_VBE_PWM_DEV_PIN_ALL_MASK =
      V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK |
      V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_3_MASK |
      V4L2_EXT_VBE_PWM_DEV_PIN_4_MASK, // Mask for all PWM pins

  V4L2_EXT_VBE_PWM_DEV_PIN_DEFAULT_MASK // Depend on pwmIndex setting of
                                        // V4L2_CID_EXT_VBE_PWM_APPLY_PARAM
                                        // command */
};

/**
 * @brief  Struct for pwm parameter
 *
 * Used by V4L2_CID_EXT_VBE_PWM_PARAM
 *
 * This is for each PWM device pin. The each PWM device pin will have their own
 * parameter.
 *
 * @endrst
 */
struct v4l2_ext_vbe_pwm_param {
  enum v4l2_ext_vbe_pwm_pin_sel pwmIndex;
  union {
    struct v4l2_ext_vbe_pwm_param_data *pstPWMParam;
    unsigned int compat_data;
    unsigned long long sizer;
  };
};

/**
 * pwm parameter to set pwm duty only
 **/
struct v4l2_ext_vbe_pwm_duty {
  enum v4l2_ext_vbe_pwm_pin_sel_mask pwmIndex;
  unsigned int pwm_duty;
};

/**
 * draw vcom pattern
 **/

// clang-format off
/**
 * @brief  Struct for VCOM pattern draw
 *
 * Used by V4L2_CID_EXT_VBE_VCOM_PAT_DRAW
 * This function used to drawing VCOM pattern.
 * It will be used for adjustment in the factory.
 * It will be used only one time when drawing pattern, not turn on the display.
 * It will be displayed by V4L2_CID_EXT_VBE_VCOM_PAT_CTRL with (VCOM_PAT_CTRL_ON);
 * The level of each pixel will not be different, ex) an pattern have 127 gray for all of pixels.
 *
 * The SoC should implement Vcom pattern generator in the TCON block.
 * vcomPattern:
 *    It is 96 subpixel array data
 *    = 8 pixels x 4 line
 *    = 8 x 3(r,g,b subpixel) x 4 line
 * nSize:
 *     size is 96
 * @rst
 * Commands & Parameters
 *   .. code-block:: cpp
 *    struct v4l2_ext_vbe_vcom_pat_draw {
 *        union {
 *            unsigned short *vcomPattern;
 *            unsigned int compat_data;
 *            unsigned long long sizer;
 *        };
 *        unsigned short nSize; //96
 *    };
 * @endrst
 */
// clang-format on
struct v4l2_ext_vbe_vcom_pat_draw {
  union {
    unsigned short *vcomPattern;
    unsigned int compat_data;
    unsigned long long sizer;
  };
  unsigned short nSize;
};

/**
 * VCOM Pattern Control
 **/
enum v4l2_ext_vbe_vcom_pat_ctrl {
  V4L2_EXT_VBE_VCOM_PAT_CTRL_OFF = 0, // Mandatory
  V4L2_EXT_VBE_VCOM_PAT_CTRL_ON,      // Mandatory
  V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM1,   // Optional, PGEN_VCOM1 and CTRL_ON
  V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM2,   // Optional, PGEN_VCOM2 and CTRL_ON
  V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM3,   // Optional, PGEN_VCOM3 and CTRL_ON
  V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM4,   // Optional, PGEN_VCOM4 and CTRL_ON
  V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM5,   // Optional, PGEN_VCOM5 and CTRL_ON
  V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM6,   // Optional, PGEN_VCOM6 and CTRL_ON
  V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM7,   // Optional, PGEN_VCOM7 and CTRL_ON
  V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM8,   // Optional, PGEN_VCOM8 and CTRL_ON
  V4L2_EXT_VBE_VCOM_PAT_CTRL_MAX      // Limit to control.
};

/**
 * @brief  Enum for oled mode
 *
 * Used by struct v4l2_ext_vbe_panel_orbit_info
 * Deprecated
 * @endrst
 */
enum v4l2_ext_vbe_panel_orbit_mode {
  V4L2_EXT_VBE_PANEL_ORBIT_JUSTSCAN_MODE = 0,
  V4L2_EXT_VBE_PANEL_ORBIT_AUTO_MODE,
  V4L2_EXT_VBE_PANEL_ORBIT_STORE_MODE,
  V4L2_EXT_VBE_PANEL_OREBIT_MODE_MAX
};

/**
 * @brief  Struct for oled orbit mode control
 *
 * Used by V4L2_CID_EXT_VBE_ORBIT
 * Deprecated
 * @endrst
 */
struct v4l2_ext_vbe_panel_orbit_info {
  unsigned int on_off;
  enum v4l2_ext_vbe_panel_orbit_mode orbitmode;
};

/**
 * LSR mode setting
 **/
enum v4l2_ext_vbe_panel_lsr_mode {
  V4L2_EXT_VBE_PANEL_LSR_OFF = 0,
  V4L2_EXT_VBE_PANEL_LSR_LIGHT_VIVID,
  V4L2_EXT_VBE_PANEL_LSR_LIGHT_EXPERT2,
  V4L2_EXT_VBE_PANEL_LSR_LIGHT_HDRCINEMA,
  V4L2_EXT_VBE_PANEL_LSR_STRONG_VIVID,
  V4L2_EXT_VBE_PANEL_LSR_STRONG_EXPERT2,
  V4L2_EXT_VBE_PANEL_LSR_STRONG_HDRCINEMA,
  V4L2_EXT_VBE_PANEL_LSR_STRONG_OTHERS,
  V4L2_EXT_VBE_PANEL_LSR_LIGHT_OTHERS,
  V4L2_EXT_VBE_PANEL_LSR_MAX
};

/**
 * LSR mode ctrl
 **/
struct v4l2_ext_vbe_panel_lsr_info {
  union {
    unsigned int *pLsrTable;
    unsigned int compat_data_lsrtable;
    unsigned long long sizer_lsrtable;
  };
  enum v4l2_ext_vbe_panel_lsr_mode lsrstep;
};

/**
 * GSR setting tbl
 **/
struct v4l2_ext_vbe_panel_gsr_info {
  union {
    unsigned int *pGsrTable;
    unsigned int compat_data_gsrtable;
    unsigned long long sizer_gsrtable;
  };
};

/**
 * OSD_RGB GAIN setting ctrl
 **/
struct v4l2_ext_vbe_panel_osd_gain_info {
  union {
    unsigned int *levelval; // OSD area will be black when the level is 0xff)
    unsigned int compat_data_levelval;
    unsigned long long sizer_levelval;
  };
  unsigned int on_off;
  unsigned int size; // size in byte; 4 byte fixed
};

/**
 * OSD_Alpha val ctrl
 **/
struct v4l2_ext_vbe_panel_alpha_osd_info {
  union {
    unsigned int *alphaTable;
    unsigned int compat_data_alphatable;
    unsigned long long sizer_alphatable;
  };
  unsigned int size; // size in byte
};

/**
 * Demura Data
**/
struct v4l2_ext_vbe_panel_demura {
  unsigned int enable; // 0: disable, 1: enable
  union {
    unsigned char *config;
    unsigned int compat_data_ctrl;
    unsigned long long sizer_ctrl;
  };
  unsigned int configsize;
  unsigned int configcrc;
  union {
    unsigned char *data;
    unsigned int compat_data_demura;
    unsigned long long sizer_demura;
  };
  unsigned int datasize;
  unsigned int datacrc;
};

/**
 * PCLRC Data
**/

/**
 * @brief  Struct for PCLRC data
 *
 * Used by V4L2_CID_EXT_VBE_PCLRC
 * It is supported in embedded TCON with SiliconWorks IP.
 * @endrst
 */
struct v4l2_ext_vbe_panel_pclrc {
  unsigned int enable; // 0: disable, 1: enable
  unsigned int
      positionAfterLineOD; // Signal Path 0 : PCLRC -> LOD, 1 : LOD -> PCLRC
  union {
    unsigned char *data; // It should write to 8192 to 12543 in SRAM LUT.
    unsigned int compat_data_pclrc;
    unsigned long long sizer_pclrc;
  };
  unsigned int datasize;
};

/**
 * GSR2 setting tbl
 **/
struct v4l2_ext_vbe_panel_second_gsr_info {
  union {
    unsigned int *pGsrTable;
    unsigned int compat_data_gsrtable;
    unsigned long long sizer_gsrtable;
  };
};

/**
 * GSR2 setting tbl
 **/
struct v4l2_ext_vbe_panel_irr_info {
  union {
    unsigned int *pIrrlum;
    unsigned int compat_data_irr;
    unsigned long long sizer_irr;
  };
};

/**
 * TPC Recovery param setting tbl
 **/
struct v4l2_ext_vbe_panel_tpc_recovery_param_info {
  union {
    unsigned int *pParamTable;
    unsigned int compat_data_paramtable;
    unsigned long long sizer_paramtable;
  };
  unsigned int table_size;
};

/**
 * TPC Recovery status tbl
 **/
struct v4l2_ext_vbe_panel_tpc_recovery_status_info {
  union {
    unsigned int *tpcStatusTable;
    unsigned int compat_data_statustable;
    unsigned long long sizer_statustable;
  };
  unsigned int table_size;
};

/**
 * TPC APL Info tbl
**/
struct v4l2_ext_vbe_panel_tpc_apl_info {
  union {
    unsigned int *tpcAplInfoTable;
    unsigned int compat_data_statustable;
    unsigned long long sizer_statustable;
  };
  unsigned int table_size;
};

/**
 * OLED APL Ctrl Param tbl
**/
struct v4l2_ext_vbe_panel_apl_control_param_info {
  union {
    unsigned int *pParamTable;
    unsigned int compat_data_paramtable;
    unsigned long long sizer_paramtable;
  };
  unsigned int table_size;
};

/**
 * CSPI P-Gamma CTRL Setting tbl
 **/
struct v4l2_ext_vbe_cspi_pgamma_control_param {
  union {
    unsigned int *pCtrlData;
    unsigned int compat_data_cspipgamma;
    unsigned long long sizer_cspipgamma;
  };
  unsigned int ctrlDataCount;
};

enum v4l2_ext_vbe_dclk_mode {
  V4L2_EXT_VBE_DCLK_MODE_BASIC, // DCLK when power on (ex: 74.25MHz for 120Hz
                                // module or 84.24MHz for 144Hz module)
  V4L2_EXT_VBE_DCLK_MODE_165HZ, // for 165Hz
  V4L2_EXT_VBE_DCLK_MODE_144HZ, // for 144Hz  
  V4L2_EXT_VBE_DCLK_MODE_MAX
};

/**
 * Gamma Table for VDF
 **/
struct v4l2_ext_vbe_vdf_gamma_curve {
  union {
    unsigned int *pRtbl; // for R table, 12bit datas
    unsigned int compat_data_R;
    unsigned long long sizer_R;
  };
  union {
    unsigned int *pGtbl; // for G table, 12bit datas
    unsigned int compat_data_G;
    unsigned long long sizer_G;
  };
  union {
    unsigned int *pBtbl; // for B table, 12bit datas
    unsigned int compat_data_B;
    unsigned long long sizer_B;
  };
  unsigned int table_size; // each table size
};

/**
 * Gamma Curve Param for VDF
 **/
struct v4l2_ext_vbe_vdf_gamma_param {
  unsigned char isOn;                                     // 0:off, 1:on
  struct v4l2_ext_vbe_vdf_gamma_curve lowFrameRateTable;  // for low frequency
  struct v4l2_ext_vbe_vdf_gamma_curve highFrameRateTable; // for high frequency
  union {
    unsigned int *vdfGammaControlParam; // Not defined(in current, no use this
                                        // param), just be added for further
                                        // extension of control
    unsigned int compat_vdfGammaControlParam;
    unsigned long long sizer_vdfGammaControlParam;
  };
};

/**
 * Frequency Mode Change
 **/
enum v4l2_ext_vbe_frequency_mode {
  V4L2_EXT_VBE_FREQUENCY_MODE_240Hz, // for normal output(240Hz)
  V4L2_EXT_VBE_FREQUENCY_MODE_120Hz, // for 120Hz output
  V4L2_EXT_VBE_FREQUENCY_MODE_60Hz,  // for 60Hz output
  V4L2_EXT_VBE_FREQUENCY_MODE_MAX
};

/**
 * Panel Output Timing Data
 **/
struct v4l2_ext_vbe_output_timing {
  int frameRate;
  int hTotal;
  int vTotal;
  int hSyncWidth;
  int vSyncWidth;
  int hBlank;
  int vBlank;
  int hBackPorch;
  int vBackPorch;
  int hResolution;
  int vResolution;
  int minVTotal;
  int maxVTotal;
};

enum v4l2_ext_vbe_outputsetting_type {
  V4L2_EXT_VBE_OUTPUT_SET_TIMING_TYPE = 0, // set only output timing parameters
  V4L2_EXT_VBE_OUTPUT_INIT_ALLTCONBINDATA_TYPE, // save the full(combined)
                                                // tcon.bin data
  V4L2_EXT_VBE_OUTPUT_SELECT_ONETCONDATA_TYPE,  // set a tcon data among full
                                                // tcon.bin for selected timing
                                                // info
  V4L2_EXT_VBE_OUTPUT_SET_TIMING_NOTCONBIN_TYPE, // set output timing parameters
                                                 // for no use tcon.bin case
  V4L2_EXT_VBE_OUTPUT_TYPE_MAX
};

struct v4l2_ext_vbe_output_settingdata {
  enum v4l2_ext_vbe_outputsetting_type setType;
  union {
    struct v4l2_ext_vbe_output_timing *pTimingParam;
    unsigned int compat_data_timingParam;
    unsigned long long sizer_timingParam;
  };
  union {
    void *extraInfo;
    unsigned int compat_data_extraInfo;
    unsigned long long sizer_extraInfo;
  };
};

/**
 * Local Dimming AI detected apl map data for external LD IC
 **/

enum v4l2_ext_vbe_object_detection_id {
  V4L2_EXT_VBE_OBJECT_DETECTION_ID_FACE = 0x01,
  V4L2_EXT_VBE_OBJECT_DETECTION_ID_DEPTH = 0x02,
  V4L2_EXT_VBE_OBJECT_DETECTION_ID_LIGHT = 0x04,
  V4L2_EXT_VBE_OBJECT_DETECTION_ID_LOGO = 0x08,
};

struct v4l2_ext_vbe_object_apl_gain {
  enum v4l2_ext_vbe_object_detection_id id;
  unsigned char enable;
  unsigned char master_gain;
  unsigned char gain_x[4];
  unsigned char gain_y[4];
};

struct v4l2_ext_vbe_object_apl {
  unsigned int
      detection_flag; // bitwise values of v4l2_ext_vbe_object_detection_id
  unsigned char apl[80][40];
};

// clang-format off

/* VBE class control IDs */

#define V4L2_CID_EXT_VBE_BASE (V4L2_CID_USER_EXT_VBE_BASE)

/**
 * @brief Init VBE when cold on
 *
 * @rst
 * Functional Requirements
 *   Initialize VBE panel controller driver module.
 *   Provides panel information but no specific setting is required with this information.
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   This function should return within 10ms.
 *
 * Constraints
 *   None
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *    //
 *    // ioctl command
 *    //
 *    VIDIOC_S_EXT_CTRLS
 *
 *    //
 *    // control id
 *    //
 *    // You have to make the new control id as the below.
 *    V4L2_CID_EXT_VBE_INIT
 *
 *    //
 *    // parameter
 *    //
 *    // VBE
 *	  enum v4l2_ext_vbe_panel_inch {
 *		 V4L2_EXT_VBE_PANEL_INCH_22 = 0,
 *		 V4L2_EXT_VBE_PANEL_INCH_23,
 *		 V4L2_EXT_VBE_PANEL_INCH_24,
 *		 V4L2_EXT_VBE_PANEL_INCH_26,
 *		 V4L2_EXT_VBE_PANEL_INCH_27,
 *		 V4L2_EXT_VBE_PANEL_INCH_28,
 *		 V4L2_EXT_VBE_PANEL_INCH_32,
 *		 V4L2_EXT_VBE_PANEL_INCH_39,
 *		 V4L2_EXT_VBE_PANEL_INCH_40,
 *		 V4L2_EXT_VBE_PANEL_INCH_42,
 *		 V4L2_EXT_VBE_PANEL_INCH_43,
 *		 V4L2_EXT_VBE_PANEL_INCH_47,
 *		 V4L2_EXT_VBE_PANEL_INCH_49,
 *		 V4L2_EXT_VBE_PANEL_INCH_50,
 *		 V4L2_EXT_VBE_PANEL_INCH_55,
 *		 V4L2_EXT_VBE_PANEL_INCH_58,
 *		 V4L2_EXT_VBE_PANEL_INCH_60,
 *		 V4L2_EXT_VBE_PANEL_INCH_65,
 *		 V4L2_EXT_VBE_PANEL_INCH_70,
 *		 V4L2_EXT_VBE_PANEL_INCH_75,
 *		 V4L2_EXT_VBE_PANEL_INCH_77,
 *		 V4L2_EXT_VBE_PANEL_INCH_79,
 *		 V4L2_EXT_VBE_PANEL_INCH_84,
 *		 V4L2_EXT_VBE_PANEL_INCH_86,
 *		 V4L2_EXT_VBE_PANEL_INCH_98,
 *		 V4L2_EXT_VBE_PANEL_INCH_105,
 *		 V4L2_EXT_VBE_PANEL_INCH_48, // 17Y Added
 *		 V4L2_EXT_VBE_PANEL_INCH_MAX
 *    };
 *
 *	  enum v4l2_ext_vbe_panel_maker {
 *		 V4L2_EXT_VBE_PANEL_MAKER_LGD = 0,
 *		 V4L2_EXT_VBE_PANEL_MAKER_AUO,
 *		 V4L2_EXT_VBE_PANEL_MAKER_SHARP,
 *		 V4L2_EXT_VBE_PANEL_MAKER_BOE,
 *		 V4L2_EXT_VBE_PANEL_MAKER_CSOT,
 *		 V4L2_EXT_VBE_PANEL_MAKER_INNOLUX,
 *		 V4L2_EXT_VBE_PANEL_MAKER_LGD_M,
 *		 V4L2_EXT_VBE_PANEL_MAKER_ODM_B,
 *		 V4L2_EXT_VBE_PANEL_MAKER_BOE_TPV,
 *		 V4L2_EXT_VBE_PANEL_MAKER_HKC,
 *		 V4L2_EXT_VBE_PANEL_MAKER_MAX
 *	  };
 *
 *    //Panel interface
 *	  enum v4l2_ext_vbe_panel_interface {
 *		 V4L2_EXT_VBE_PANEL_EPI = 0,
 *		 V4L2_EXT_VBE_PANEL_LVDS,
 *		 V4L2_EXT_VBE_PANEL_Vx1,
 *		 V4L2_EXT_VBE_PANEL_CEDS,
 *		 V4L2_EXT_VBE_PANEL_EPI_QSAC,
 *		 V4L2_EXT_VBE_PANEL_RESERVED1,
 *		 V4L2_EXT_VBE_PANEL_RESERVED2,
 *		 V4L2_EXT_VBE_PANEL_INTERFACE_MAX
 *	  };
 *
 *	  // Panel Resolution
 *	  enum v4l2_ext_vbe_panel_resolution {
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_1024X768 = 0,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_1280X720,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_1366X768,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_1920X1080,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_2560X1080,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_3840X2160,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_5120X2160,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_7680X4320,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED1,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED2,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED3,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED4,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_RESERVED5,
 *		 V4L2_EXT_VBE_PANEL_RESOLUTION_MAX
 *    };
 *
 * 	  //Panel version
 *	  enum v4l2_ext_vbe_panel_version {
 *		 V4L2_EXT_VBE_PANEL_NONE = 0,
 *		 V4L2_EXT_VBE_PANEL_V12,
 *		 V4L2_EXT_VBE_PANEL_V13,
 *		 V4L2_EXT_VBE_PANEL_V14,
 *		 V4L2_EXT_VBE_PANEL_V15,
 *		 V4L2_EXT_VBE_PANEL_V16,
 *		 V4L2_EXT_VBE_PANEL_V17,
 *		 V4L2_EXT_VBE_PANEL_V18,
 *		 V4L2_EXT_VBE_PANEL_MAX
 *	  };
 *
 * 	  //Panel Framerate
 *	  enum v4l2_ext_vbe_panel_framerate {
 *		 V4L2_EXT_VBE_PANEL_FRAMERATE_60HZ,
 *		 V4L2_EXT_VBE_PANEL_FRAMERATE_120HZ,
 *		 V4L2_EXT_VBE_PANEL_FRAMERATE_MAX
 *	  };
 *
 *	  //Backlight Type Enum  related with Tool OPT
 *	  enum v4l2_ext_vbe_panel_backlight_type {
 *		 V4L2_EXT_VBE_PANEL_BL_DIRECT_L = 0,
 *		 V4L2_EXT_VBE_PANEL_BL_EDGE_LED,
 *		 V4L2_EXT_VBE_PANEL_BL_OLED,
 *		 V4L2_EXT_VBE_PANEL_BL_DIRECT_VI,
 *		 V4L2_EXT_VBE_PANEL_BL_DIRECT_SKY,
 *		 V4L2_EXT_VBE_PANEL_BL_MAX
 *	  };
 *
 *	  //Panel Led_bar Type Enum	related with Tool OPT
 *	  enum v4l2_ext_vbe_panel_led_bar_type {
 *		 V4L2_EXT_VBE_PANEL_LED_BAR_6 = 0,
 *		 V4L2_EXT_VBE_PANEL_LED_BAR_12,
 *		 V4L2_EXT_VBE_PANEL_LED_BAR_36,
 *		 V4L2_EXT_VBE_PANEL_LED_BAR_40,
 *		 V4L2_EXT_VBE_PANEL_LED_BAR_48,
 *		 V4L2_EXT_VBE_PANEL_LED_BAR_50,
 *		 V4L2_EXT_VBE_PANEL_LED_BAR_96,
 *	 	 V4L2_EXT_VBE_PANEL_LED_BAR_MAX
 *	  };
 *
 *	  //Panel Cell type
 *	  enum v4l2_ext_vbe_panel_cell_type {
 *		 V4L2_EXT_VBE_PANEL_CELL_TYPE_RGB = 0,
 *		 V4L2_EXT_VBE_PANEL_CELL_TYPE_RGBW,
 *		 V4L2_EXT_VBE_PANEL_CELL_TYPE_MAX
 *	  };
 *
 *	  //Display Output Lane Bandwidth.
 *	  enum v4l2_ext_vbe_panel_bandwidth {
 *		 V4L2_EXT_VBE_PANEL_BANDWIDTH_DEFAULT = 0,
 *		 V4L2_EXT_VBE_PANEL_BANDWIDTH_1_5G,
 *		 V4L2_EXT_VBE_PANEL_BANDWIDTH_2_1G,
 *		 V4L2_EXT_VBE_PANEL_BANDWIDTH_3_0G,
 *		 V4L2_EXT_VBE_PANEL_BANDWIDTH_MAX
 *	  };
 *
 *	  //FRC Chip type
 *	  enum v4l2_ext_vbe_frc_chip {
 *		 V4L2_EXT_VBE_FRC_CHIP_NONE = 0,
 *		 V4L2_EXT_VBE_FRC_CHIP_INTERNAL,
 *		 V4L2_EXT_VBE_FRC_CHIP_EXTERNAL1, // Reserved1
 *		 V4L2_EXT_VBE_FRC_CHIP_EXTERNAL2, // Reserved2
 *		 V4L2_EXT_VBE_FRC_CHIP_TYPE_MAX
 *	  };
 *
 *	  // LVDS bit depth.
 *	  enum v4l2_ext_vbe_lvds_colordepth {
 *		 V4L2_EXT_VBE_LVDS_COLOR_DEPTH_8BIT,
 *		 V4L2_EXT_VBE_LVDS_COLOR_DEPTH_10BIT,
 *		 V4L2_EXT_VBE_LVDS_COLOR_DEPTH_MAX
 *	  };
 *
 *	  // LVDS type.
 *	  enum v4l2_ext_vbe_lvds_type {
 *		 V4L2_EXT_VBE_LVDS_TYPE_VESA,
 *		 V4L2_EXT_VBE_LVDS_TYPE_JEIDA,
 *		 V4L2_EXT_VBE_LVDS_TYPE_MAX
 *	  };
 *
 *    //Display User Option
 *    union v4l2_ext_vbe_user_option {
 *       unsigned int all;
 *       struct _flags {
 *           unsigned int SocOptionBIT0 : 1, SocOptionBIT1 : 1, SocOptionBIT2 : 1,
 *               SocOptionBIT3 : 1, SocOptionBIT4 : 1, SocOptionBIT5 : 1,
 *               SocOptionBIT6 : 1, SocOptionBIT7 : 1, SocOptionBIT8 : 1,
 *               SocOptionBIT9 : 1, SocOptionBIT10 : 1, SocOptionBIT11 : 1,
 *               SocOptionBIT12 : 1, SocOptionBIT13 : 1, SocOptionBIT14 : 1,
 *               SocOptionBIT15 : 1, SocOptionBIT16 : 1, SocOptionBIT17 : 1,
 *               SocOptionBIT18 : 1, SocOptionBIT19 : 1, SocOptionBIT20 : 1,
 *               SocOptionBIT21 : 1, SocOptionBIT22 : 1, SocOptionBIT23 : 1,
 *               SocOptionBIT24 : 1, SocOptionBIT25 : 1, SocOptionBIT26 : 1,
 *               SocOptionBIT27 : 1, SocOptionBIT28 : 1, SocOptionBIT29 : 1,
 *               SocOptionBIT30 : 1, SocOptionBIT31 : 1;
 *       } flags;
 *    };
 *
 *    //Panel information
 *    struct v4l2_ext_vbe_panel_info {
 *        enum v4l2_ext_vbe_panel_inch panelInch;                    // Panel Inch
 *        enum v4l2_ext_vbe_panel_maker panelMaker;                  // Panel maker
 *        enum v4l2_ext_vbe_panel_interface panelInterface;          // Panel Interface
 *        enum v4l2_ext_vbe_panel_resolution panelResolution;        // Panel Resolution
 *        enum v4l2_ext_vbe_panel_version panelVersion;              // Panel Version
 *        enum v4l2_ext_vbe_panel_framerate panelFrameRate;          // Panel Frame Rate: 60/120/144hz
 *        enum v4l2_ext_vbe_panel_led_bar_type panelLedBarType;      // LED bar type
 *        enum v4l2_ext_vbe_panel_backlight_type panelBacklightType; // LED Backlight type
 *        enum v4l2_ext_vbe_panel_cell_type panelCellType;           // Panel Cell type: RGB/RGBW
 *        enum v4l2_ext_vbe_panel_bandwidth dispOutLaneBW;           // Output lane bandwidth
 *        enum v4l2_ext_vbe_frc_chip frcType;                        // FRC type
 *        enum v4l2_ext_vbe_lvds_colordepth lvdsColorDepth;          // LVDS Color depth
 *        enum v4l2_ext_vbe_lvds_type lvdsType;                      // LVDS Type
 *        union v4l2_ext_vbe_user_option userSpecificOption;         // Reserved Options
 *    };
 *
 * Return Value
 *       On success 0 is returned.
 *
 *       On error -1 and the errno variable is set appropriately. The generic error
 *       codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *       Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *       .. code-block:: cpp
 *
 *         // VBE Initialize
 *         struct v4l2_ext_controls ext_controls;
 *         struct v4l2_ext_control ext_control;
 *         struct v4l2_ext_vbe_panel_info panelInfo;
 *
 *         memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *         memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *         memset(&panelInfo, 0, sizeof(struct v4l2_ext_vbe_panel_info ));
 *
 *         panelInfo.panelInch = V4L2_EXT_VBE_PANEL_INCH_65;                       // Panel Inch
 *         panelInfo.panelMaker = V4L2_EXT_VBE_PANEL_MAKER_LGD;                    // Panel maker
 *         panelInfo.panelInterface = V4L2_EXT_VBE_PANEL_EPI;                      // Panel Interface
 *         panelInfo.panelResolution = V4L2_EXT_VBE_PANEL_RESOLUTION_3840X2160;    // Panel Resolution
 *         panelInfo.panelVersion = V4L2_EXT_VBE_PANEL_V18;                        // Panel Version
 *         panelInfo.panelFrameRate = V4L2_EXT_VBE_PANEL_FRAMERATE_120HZ;          // Panel Frame Rate
 *         panelInfo.panelLedBarType = V4L2_EXT_VBE_PANEL_LED_BAR_6;               // LED bar type
 *         panelInfo.panelBacklightType = V4L2_EXT_VBE_PANEL_BL_EDGE_LED;          // LED Backlight type
 *         panelInfo.panelCellType = V4L2_EXT_VBE_PANEL_CELL_TYPE_RGB;             // Panel Cell type
 *         panelInfo.dispOutLaneBW = V4L2_EXT_VBE_PANEL_BANDWIDTH_1_5G;            // Output lane bandwidth
 *         panelInfo.frcType = V4L2_EXT_VBE_FRC_CHIP_INTERNAL;                     // FRC type
 *         panelInfo.lvdsColorDepth = V4L2_EXT_VBE_LVDS_COLOR_DEPTH_10BIT;         // LVDS Color depth
 *         panelInfo.lvdsType = V4L2_EXT_VBE_LVDS_TYPE_VESA;                       // LVDS Type
 *         panelInfo.userSpecificOption.flags.userSpecificOption = 0;              // Reserved Option
 *
 *         ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *         ext_controls.count = 1;
 *         ext_controls.controls = &ext_control;
 *         ext_controls.controls->id = V4L2_CID_EXT_VBE_INIT;
 *         ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_info);
 *         ext_controls.controls->ptr = (void *)&panelInfo;
 *
 *         ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_INIT (V4L2_CID_EXT_VBE_BASE + 0)
 /**
 * @brief Init VBE when DC on(QSM+ on)
 *
 * @rst
 * Functional Requirements
 *   This function can set resume VBE
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_RESUME
 *
 *	   //
 *	   // parameter
 *	   //
 *	   Sams as V4L2_CID_EXT_VBE_INIT
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // VBE Resume
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_info panelInfo;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&panelInfo, 0, sizeof(struct v4l2_ext_vbe_panel_info ));
 *
 *     panelInfo.panelInch = V4L2_EXT_VBE_PANEL_INCH_65;                       // Panel Inch
 *     panelInfo.panelMaker = V4L2_EXT_VBE_PANEL_MAKER_LGD;                    // Panel maker
 *     panelInfo.panelInterface = V4L2_EXT_VBE_PANEL_EPI;                      // Panel Interface
 *     panelInfo.panelResolution = V4L2_EXT_VBE_PANEL_RESOLUTION_3840X2160;    // Panel Resolution
 *     panelInfo.panelVersion = V4L2_EXT_VBE_PANEL_V18;                        // Panel Version
 *     panelInfo.panelFrameRate = V4L2_EXT_VBE_PANEL_FRAMERATE_120HZ;          // Panel Frame Rate
 *     panelInfo.panelLedBarType = V4L2_EXT_VBE_PANEL_LED_BAR_6;               // LED bar type
 *     panelInfo.panelBacklightType = V4L2_EXT_VBE_PANEL_BL_EDGE_LED;          // LED Backlight type
 *     panelInfo.panelCellType = V4L2_EXT_VBE_PANEL_CELL_TYPE_RGB;             // Panel Cell type
 *     panelInfo.dispOutLaneBW = V4L2_EXT_VBE_PANEL_BANDWIDTH_1_5G;            // Output lane bandwidth
 *     panelInfo.frcType = V4L2_EXT_VBE_FRC_CHIP_INTERNAL;                     // FRC type
 *     panelInfo.lvdsColorDepth = V4L2_EXT_VBE_LVDS_COLOR_DEPTH_10BIT;         // LVDS Color depth
 *     panelInfo.lvdsType = V4L2_EXT_VBE_LVDS_TYPE_VESA;                       // LVDS Type
 *     panelInfo.userSpecificOption.flags.userSpecificOption = 0;              // Reserved Option
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_RESUME;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_info);
 *     ext_controls.controls->ptr = (void *)&panelInfo;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_RESUME (V4L2_CID_EXT_VBE_BASE + 1)
/**
 * @brief Set display output
 *
 * @rst
 * Functional Requirements
 *   This function controls LVDS, EPI and VbyOne signal output to the panel.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_DISPLAYOUTPUT
 *
 *	   //
 *	   // parameter
 *	   //
 *	   control value
 *       0 : Start to transmit video sigal to the panel
 *       1 : Stop to transmit video signal to the panel
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // Set displayOutput
 *	   v4l2_control control;
 *
 *	   control.id = V4L2_CID_EXT_VBE_DISPLAYOUTPUT;
 *	   control.value = 1; 	 // On
 *
 *	   ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_DISPLAYOUTPUT (V4L2_CID_EXT_VBE_BASE + 2)
/**
 * @brief Set screen mute
 *
 * @rst
 * Functional Requirements
 *   This function can set screen mute or screen unmute.
 *   Video including OSD is muted or unmuted with this function.
 *
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Panel power should not be controlled with this CID.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_MUTE
 *
 *	   //
 *	   // parameter
 *	   //
 *	   0 (Off), 1 (On)
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set screen mute
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBE_MUTE;
 *     control.value = 1; 	 // On
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_MUTE (V4L2_CID_EXT_VBE_BASE + 3)
/**
 * @brief Set spread spectrum
 *
 * @rst
 * Functional Requirements
 *   This function can set spread spectrum
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_SSC
 *
 *	   //
 *	   // parameter
 *	   //
 *     //spread spectrum control
 *     struct v4l2_ext_vbe_ssc {
 *       unsigned int on_off;
 *       unsigned short percent;
 *       unsigned short period;
 *     };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_ssc sscType;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&sscType, 0, sizeof(struct v4l2_ext_vbe_ssc));
 *
 *     sscType.on_off  = bEnable;
 *     sscType.percent = u16Percent;
 *     sscType.period  = u16Period;
 *
 *     ext_controls.ctrl_class       = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count            = 1;
 *     ext_controls.controls         = &ext_control;
 *     ext_controls.controls->id     = V4L2_CID_EXT_VBE_SSC;
 *     ext_controls.controls->size   = sizeof(struct v4l2_ext_vbe_ssc);
 *     ext_controls.controls->string = (char *)&sscType;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_SSC (V4L2_CID_EXT_VBE_BASE + 4)
/**
 * @brief Set mirror mode
 *
 * @rst
 * Functional Requirements
 *   This function can set video mirror mode
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_MIRROR
 *
 *	   //
 *	   // parameter
 *	   //
 *	   0 (Off), 1 (On)
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // Set video mirror mode
 *	   v4l2_control control;
 *
 *	   control.id = V4L2_CID_EXT_VBE_MIRROR;
 *	   control.value = 1; 	 // On
 *
 *	   ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_MIRROR (V4L2_CID_EXT_VBE_BASE + 5)
/**
 * @brief Set SetRGBWBypass
 *
 * @rst
 * Functional Requirements
 *   This function is used for only RGBW model.
 *   The BOE M+ IP in SoC is bypassed for BOE panel.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_MPLUS_BOEBYPASS
 *
 *	   //
 *	   // parameter
 *	   //
 *	   0 (Off), 1 (On)
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // BOE Bypass
 *	   v4l2_control control;
 *
 *	   control.id = V4L2_CID_EXT_VBE_MPLUS_BOEBYPASS;
 *	   control.value = 1; 	 // Bypass On
 *
 *	   ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_MPLUS_BOEBYPASS (V4L2_CID_EXT_VBE_BASE + 6)
/**
 * @brief Set MLE Mode
 *
 * @rst
 * Functional Requirements
 *   This function is used for only RGBW model.
 *   The LGD M+ IP will be contolled by each mode.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_MPLUS_MODE
 *
 *	   //
 *	   // parameter
 *	   //
 *      enum v4l2_ext_vbe_mplus_mode {
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE0 = 0, //
 *       V4L2_EXT_VBE_MPLUS_HIGH_LUM1_MSE_ON = 0,
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE1,  // V4L2_EXT_VBE_MPLUS_HIGH_LUM2,
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE2,  // V4L2_EXT_VBE_MPLUS_LOW_POWER1,
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE3,  // V4L2_EXT_VBE_MPLUS_MLE_MODE_OFF,
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE4,  //
 *       V4L2_EXT_VBE_MPLUS_HIGH_LUM1_MSE_OFF,
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE5,  // V4L2_EXT_VBE_MPLUS_LOW_POWER2,
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE6,  //
 *       V4L2_EXT_VBE_MPLUS_LOW_POWER2_SC_OFF,
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE7,  // MHE Mode1 09/20/2018
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE8,  // MHE Mode2 09/20/2018
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE9,  // MHE Mode3 09/20/2018
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODE10, // MHE Mode4 09/20/2018
 *     	 V4L2_EXT_VBE_MPLUS_MPLUS_MODEMAX
 *      };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // LGD M+ Mode
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     enum v4l2_ext_vbe_mplus_mode mplusMode;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&mplusMode, 0, sizeof(enum v4l2_ext_vbe_mplus_mode));
 *
 *     mplusMode = V4L2_EXT_VBE_MPLUS_MPLUS_MODE1;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_MPLUS_MODE;
 *     ext_controls.controls->size = sizeof(enum v4l2_ext_vbe_mplus_mode);
 *     ext_controls.controls->ptr = (void *)&mplusMode;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_MPLUS_MODE (V4L2_CID_EXT_VBE_BASE + 7)
/**
 * @brief Set DGA4CH
 *
 * @rst
 * Functional Requirements
 *   This function is used for RGB model and RGBW model.
 *   Digital Gamma(DGA) 4CH(R,G,B,W) setting in TCON Block.
 *   The data counts are 1024 each channel. The data resolution is 10bit.
 *   If RGB model, The all data of pWhiteGammaTable is discarded.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_DGA4CH
 *
 *	   //
 *	   // parameter
 *	   //
 *       struct v4l2_ext_vbe_dga4ch {
 *       	union {
 *      		 unsigned int *pRedGammaTable;
 *      		 unsigned int compat_data_red;
 *      		 unsigned long long sizer_red;
 *      	 };
 *      	 union {
 *      		 unsigned int *pGreenGammaTable;
 *      		 unsigned int compat_data_green;
 *      		 unsigned long long sizer_green;
 *      	 };
 *     	  union {
 *      		 unsigned int *pBlueGammaTable;
 *      		 unsigned int compat_data_blue;
 *      		 unsigned long long sizer_blue;
 *     	  };
 *    	   union {
 *      		 unsigned int *pWhiteGammaTable;
 *      		 unsigned int compat_data_white;
 *     			 unsigned long long sizer_white;
 *     	  };
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_dga4ch dga4chdata;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&dga4chdata, 0, sizeof(struct v4l2_ext_vbe_dga4ch));
 *
 *     dga4chdata.pRedGammaTable   = pRedGammaTable;
 *     dga4chdata.pGreenGammaTable = pGreenGammaTable;
 *     dga4chdata.pBlueGammaTable  = pBlueGammaTable;
 *     dga4chdata.pWhiteGammaTable = pWhiteGammaTable; // If RGB model,
 *                                                     // The all data of pWhiteGammaTable is discarded.
 *
 *     ext_controls.ctrl_class     = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count          = 1;
 *     ext_controls.controls       = &ext_control;
 *     ext_controls.controls->id   = V4L2_CID_EXT_VBE_DGA4CH;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_dga4ch);
 *     ext_controls.controls->ptr  = (void *)&dga4chdata;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_DGA4CH (V4L2_CID_EXT_VBE_BASE + 8)
/**
 * @brief setFrameGainLimit/ VBE GetFrameGainLimit/ VBE SetPixelGainLimit/ VBE GetPixelGainLimit
 *
 * @rst
 * Functional Requirements
 *   This function is used for only RGBW model.
 *   It control the LGD M+ parameters.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *	   VIDIOC_G_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_MPLUS_PARAM
 *
 *	   //
 *	   // parameter
 *	   //
 *       struct v4l2_ext_vbe_mplus_param {
 *      	 unsigned short nFrameGainLimit;
 *      	 unsigned short nPixelGainLimit;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Mplus Parameter
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_mplus_param mplusParam;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&mplusParam, 0, sizeof(struct v4l2_ext_vbe_mplus_param));
 *
 *     mplusParam.nFrameGainLimit = 0x2000;
 *     mplusParam.nPixelGainLimit= 0x0800;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_MPLUS_PARAM;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_mplus_param);
 *     ext_controls.controls->ptr = (void *)&mplusParam;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_MPLUS_PARAM (V4L2_CID_EXT_VBE_BASE + 9)

/**
 * @brief Set Inner Pattern
 *
 * @rst
 * Functional Requirements
 *   Output pattern image of several video blocks inside SoC.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Used for debugging purpose.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_INNER_PATTERN
 *
 *	   //
 *	   // parameter
 *	   //
 *       struct v4l2_ext_vbe_inner_pattern {
 *       	 unsigned char bOnOff;
 *       	 unsigned char ip;
 *       	 unsigned char type;
 *        };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set Inner Pattern
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_inner_pattern innerPattern;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&mplusParam, 0, sizeof(struct v4l2_ext_vbe_inner_pattern));
 *
 *     innerPattern.bOnOff= 1; // 1:On, 0:Off
 *     innerPattern.ip = 3; //0:CE, 1:CO, 2:DPE, 3:TCON
 *     innerPattern.type= 8; //0:0ff,1:Black,2:White, 3:HV Bar, 4:H 16Gray, 5:H 64Gray, 6:H 256Gray, 7:H1024 Gray, 8:V 16 Gray
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_INNER_PATTERN;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_inner_pattern);
 *     ext_controls.controls->ptr = (void *)&innerPattern;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_INNER_PATTERN (V4L2_CID_EXT_VBE_BASE + 10)
/**
 * @brief Set TSCIC Load
 *
 * @rst
 * Functional Requirements
 *   This function is for setting TSCIC function of SOC TCON blocks
 *   It will load an TSCIC data to SoC TCON Block.
 *   TSCIC : Time Sharing Clear Image Creation
 *   Requirement 1. Do not skip SoCTS
 *   Requirement 2. Do not clock disable when error return
 *   Requirement 3. Do not use kmalloc
 *   Requirement 4. Keep data setting sequence( ex. first data set, second enable function)
 *   Requirement 5. It can control disable when set u32Ctrlsize=0 or u32Tscicsize =0
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_TSCIC
 *
 *	   //
 *	   // parameter
 *	   //
 *       // TSCIC data structure
 *       struct v4l2_ext_vbe_panel_tscic {
 *      	 union {
 *      		 unsigned char *u8pControlTbl;
 *      		 unsigned int compat_data_ctrl;
 *      		 unsigned long long sizer_ctrl;
 *      	 };
 *      	 unsigned int u32Ctrlsize;
 *      	 union {
 *      		 unsigned int *u32pTSCICTbl;
 *      		 unsigned int compat_data_tscic;
 *      		 unsigned long long sizer_tscic;
 *      	 };
 *      	 unsigned int u32Tscicsize;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // TSCIC Load
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_tscic tscicData;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&tscicData, 0, sizeof(struct v4l2_ext_vbe_panel_tscic));
 *
 *     tscicData.u8pControlTbl = tscicctrldata
 *     tscicData.u32Ctrlsize =  TSCIC_CTRL_SIZE // 43 , if size is 0 then tscic disalbe
 *     tscicData.u32pTSCICTbl=  tscicdata
 *     tscicData.u32Tscicsize=  TSCIC_DATA_SIZE // 0x170C3, if size is 0 then tscic disable
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_TSCIC;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_tscic);
 *     ext_controls.controls->ptr = (void *)&tscicData;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_TSCIC (V4L2_CID_EXT_VBE_BASE + 11)
/**
 * @brief Set EPI Data scramble on/off
 *
 * @rst
 * Functional Requirements
 *   This function can set EPI Data scramble on/off
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_EPI_SCRAMBLE
 *
 *	   //
 *	   // parameter
 *	   //
 *	   0 (Off), 1 (On)
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // Set EPI Data scramble
 *	   v4l2_control control;
 *
 *	   control.id = V4L2_CID_EXT_VBE_EPI_SCRAMBLE;
 *	   control.value = 1; 	 // On
 *
 *	   ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_EPI_SCRAMBLE (V4L2_CID_EXT_VBE_BASE + 12)
/**
 * @brief Set EPI Advanced 10 bit on/off
 *
 * @rst
 * Functional Requirements
 *   This function can set EPI Advanced 10 bit on/off
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_EPI_10BIT
 *
 *	   //
 *	   // parameter
 *	   //
 *	   0 (Off), 1 (On)
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // Set EPI Advanced 10 bit on/off
 *	   v4l2_control control;
 *
 *	   control.id = V4L2_CID_EXT_VBE_EPI_10BIT;
 *	   control.value = 1; 	 // On
 *
 *	   ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_EPI_10BIT (V4L2_CID_EXT_VBE_BASE + 13)
/**
 * @brief Set/Get MplusData
 *
 * @rst
 * Functional Requirements
 *   This function is for LGD and BOE M+ register set function.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_MPLUS_DATA
 *
 *	   //
 *	   // parameter
 *	   //
 *       // Mplus data
 *       struct v4l2_ext_vbe_mplus_data {
 *      	 union {
 *      		 void *pRegisterSet;
 *      		 unsigned int compat_data;
 *      		 unsigned long long sizer;
 *      	 };
 *      	 unsigned char nPanelMaker;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // MPLUS Data
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_mplus_data mplusData;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&mplusData, 0, sizeof(struct v4l2_ext_vbe_mplus_data));
 *
 *     mplusData.pRegisterSet = gMplus_65UM63_LGD_RGBW
 *     mplusData.nPanelMaker= MODULE_LGD
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_MPLUS_DATA;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_mplus_data);
 *     ext_controls.controls->ptr = (void *)&mplusData;
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_MPLUS_DATA (V4L2_CID_EXT_VBE_BASE + 14)
/**
 * @brief Apply PWM params
 *
 * @rst
 * Functional Requirements
 *   This function can Apply PWM params
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_PWM_APPLY_PARAM
 *
 *	   //
 *	   // parameter
 *       //
 *       // type definition about PWM device's index mask
 *       enum v4l2_ext_vbe_pwm_pin_sel_mask {
 *       V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN0, // PWM# 0
 *       V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN1, // PWM# 1
 *       V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN2, // PWM# 2
 *       V4L2_EXT_VBE_PWM_DEV_PIN_3_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN3, // PWM# 3
 *       V4L2_EXT_VBE_PWM_DEV_PIN_4_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN4, // PWM# 4
 *       V4L2_EXT_VBE_PWM_DEV_PIN_0_1_MASK =  V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK |
 *                                        V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK, // PWM# 0/1
 *       V4L2_EXT_VBE_PWM_DEV_PIN_0_2_MASK =  V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK |
 *                                        V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK, // PWM# 0/2
 *       V4L2_EXT_VBE_PWM_DEV_PIN_1_2_MASK =  V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK |
 *                                        V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK, // PWM# 1/2
 *       // If necessary, add case
 *       V4L2_EXT_VBE_PWM_DEV_PIN_ALL_MASK =
 *                                      	V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK |
 *                                        V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK |
 *                                     	  V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK |
 *                                        V4L2_EXT_VBE_PWM_DEV_PIN_3_MASK |
 *                                     	  V4L2_EXT_VBE_PWM_DEV_PIN_4_MASK, // PWM# 0/1/2/3/4
 *       V4L2_EXT_VBE_PWM_DEV_PIN_DEFAULT_MASK // depended on pwmIndex setting of HAL_PWM_SetParam function
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set Apply PWM Param
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     enum v4l2_ext_vbe_pwm_pin_sel_mask pwmApplyParm;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pwmApplyParm, 0, sizeof(enum v4l2_ext_vbe_pwm_pin_sel_mask));
 *
 *     pwmApplyParm = V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_PWM_APPLY_PARAM;
 *     ext_controls.controls->size = sizeof(enum v4l2_ext_vbe_pwm_pin_sel_mask);
 *     ext_controls.controls->ptr = (void *)&pwmApplyParm;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_PWM_APPLY_PARAM (V4L2_CID_EXT_VBE_BASE + 15)
/**
 * @brief Set PWM param
 *
 * @rst
 * Functional Requirements
 *   This function can set PWM param
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *       VIDIOC_G_EXT_CTRLS
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_PWM_PARAM
 *
 *	   //
 *	   // parameter
 *	   //
 *	   //type definition about PWM device's index
 *	   enum v4l2_ext_vbe_pwm_pin_sel {
 *		 V4L2_EXT_VBE_PWM_DEV_PIN0 = 0,    // < PWM# 0
 *		 V4L2_EXT_VBE_PWM_DEV_PIN1, 	     // < PWM# 1
 *		 V4L2_EXT_VBE_PWM_DEV_PIN2, 	     // < PWM# 2
 *		 V4L2_EXT_VBE_PWM_DEV_PIN3, 	     // < PWM# 3
 *		 V4L2_EXT_VBE_PWM_DEV_PIN4, 	     // < PWM# 4
 *		 V4L2_EXT_VBE_PWM_DEV_MAX,	       // < PWM# MAX
 *		 V4L2_EXT_VBE_PWM_DEV_NONE = 0xFF, // < PWM# Not used
 *		};
 *
 *		//PWM Frequency Parameter
 *		struct v4l2_ext_vbe_pwm_adapt_freq_param {
 *		 unsigned int pwm_adapt_freq_enable;
 *		 unsigned int pwmfreq_48nHz; // PWM frequency 48xN Hz from DB table
 *		 unsigned int pwmfreq_50nHz; // PWM frequency 50xN Hz from DB table
 *		 unsigned int pwmfreq_60nHz; // PWM frequency 60xN Hz from DB table
 *		 };
 *
 *		//PWM Setting Parameter
 *		struct v4l2_ext_vbe_pwm_param_data {
 *		 unsigned int pwm_enable;
 *		 unsigned int pwm_duty;
 *		 unsigned int pwm_frequency; // If pwm_adapt_freq_enable == TRUE, ignored
 *		 struct v4l2_ext_vbe_pwm_adapt_freq_param pwm_adapt_freq_param;
 *		 unsigned int pwm_lock;
 *		 unsigned int pwm_pos_start;
 *		 unsigned int pwm_scanning_enable;
 *		 unsigned int pwm_low_power_enable; // It has been used to set low power mode
 *											                  // for M16P only until now, 170210.
 *		};
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set PWM Param
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_pwm_param pwmParam;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&pwmParam, 0, sizeof(struct v4l2_ext_vbe_pwm_param));
 *
 *     pwmParam.pwmIndex = pwmIndex;       //v4l2_ext_vbe_pwm_pin_sel pwmIndex is input parameter
 *     pwmParam.pstPWMParam = pstPWMParam; //v4l2_ext_vbe_pwm_param pstPWMParam is input parameter
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_PWM_PARAM;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_pwm_param);
 *     ext_controls.controls->string = (void *)&pwmParam;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     // Get PWM Param
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_pwm_param pwmParam;
 *     struct v4l2_ext_vbe_pwm_param_data stPWMParam;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&pwmParam, 0, sizeof(struct v4l2_ext_vbe_pwm_param));
 *
 *     pwmParam.pwmIndex    = pwmIndex;
 *     pwmParam.pstPWMParam = &stPWMParam;
 *
 *     ext_controls.ctrl_class       = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count            = 1;
 *     ext_controls.controls         = &ext_control;
 *     ext_controls.controls->id     = V4L2_CID_EXT_VBE_PWM_PARAM;
 *     ext_controls.controls->size   = sizeof(struct v4l2_ext_vbe_pwm_param);
 *     ext_controls.controls->string = (void *)&pwmParam;
 *
 *     ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_VBE_PWM_PARAM (V4L2_CID_EXT_VBE_BASE + 16)
/**
 * @brief Init PWM
 *
 * @rst
 * Functional Requirements
 *   This function can Init PWM
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_PWM_INIT
 *
 *	   //
 *	   // parameter
 *	   //
 *	   void
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // Init PWM
 *	   v4l2_control control;
 *
 *	   control.id = V4L2_CID_EXT_VBE_PWM_INIT;
 *	   ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_PWM_INIT (V4L2_CID_EXT_VBE_BASE + 17)
/**
 * @brief Set VCOM Pattern draw
 *
 * @rst
 * Functional Requirements
 *   This function used to drawing VCOM pattern. It will be used for adjustment in the factory.
 *   It will be used only one time when drawing pattern, not turn on the display.
 *   It will be displayed by HAL_VBE_DISP_VCOMPatternCtrl(VCOM_PAT_CTRL_ON).
 *   The level of each pixel will not different, ex) an pattern have 127 gray for all of pixels.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_VCOM_PAT_DRAW
 *
 *	   //
 *	   // parameter
 *	   //
 *       // draw vcom pattern
 *       struct v4l2_ext_vbe_vcom_pat_draw {
 *      	 union {
 *      		 unsigned short *vcomPattern;
 *      		 unsigned int compat_data;
 *      		 unsigned long long sizer;
 *      	 };
 *      	 unsigned short nSize;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Draw VCOM Pattern
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_vcom_pat_draw vcompat;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&vcompat, 0, sizeof(struct v4l2_ext_vbe_vcom_pat_draw));
 *
 *     vcompat.vcomPattern = vcomPattern;
 *     vcompat.nSize = 96;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_VCOM_PAT_DRAW;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_vcom_pat_draw);
 *     ext_controls.controls->ptr = (void *)&vcompat;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_VCOM_PAT_DRAW (V4L2_CID_EXT_VBE_BASE + 18)
/**
 * @brief Set VCOM Pattern ctrl
 *
 * @rst
 * Functional Requirements
 *   This function turn on/off vcom pattern.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_VCOM_PAT_CTRL
 *
 *	   //
 *	   // parameter
 *	   //
 *       // VCOM Pattern Control
 *       enum v4l2_ext_vbe_vcom_pat_ctrl {
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_OFF = 0, // Mandatory
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_ON, 	   // Mandatory
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM1,   // Optional, PGEN_VCOM1 and CTRL_ON
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM2,   // Optional, PGEN_VCOM2 and CTRL_ON
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM3,   // Optional, PGEN_VCOM2 and CTRL_ON
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM4,   // Optional, PGEN_VCOM2 and CTRL_ON
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM5,   // Optional, PGEN_VCOM2 and CTRL_ON
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM6,   // Optional, PGEN_VCOM2 and CTRL_ON
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM7,   // Optional, PGEN_VCOM2 and CTRL_ON
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_VCOM8,   // Optional, PGEN_VCOM2 and CTRL_ON
 *      	 V4L2_EXT_VBE_VCOM_PAT_CTRL_MAX      // Limit  to control.
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Draw VCOM Pattern
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_vcom_pat_draw vcompat;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&vcompat, 0, sizeof(struct v4l2_ext_vbe_vcom_pat_draw));
 *
 *     vcompat.vcomPattern = vcomPattern;
 *     vcompat.nSize = 96;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_VCOM_PAT_DRAW;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_vcom_pat_draw);
 *     ext_controls.controls->ptr = (void *)&vcompat;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_VCOM_PAT_CTRL (V4L2_CID_EXT_VBE_BASE + 19)
/**
 * @brief Set PWM Duty
 *
 * @rst
 * Functional Requirements
 *   This function can set  PWM Duty
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRL
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBE_PWM_SET_DUT
 *     //
 *     // parameter
 *     //
 *       // type definition about PWM device's index mask
 *       enum v4l2_ext_vbe_pwm_pin_sel_mask {
 *           V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN0, // < PWM# 0
 *           V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN1, // < PWM# 1
 *           V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN2, // PWM# 2
 *           V4L2_EXT_VBE_PWM_DEV_PIN_3_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN3, // PWM# 3
 *           V4L2_EXT_VBE_PWM_DEV_PIN_4_MASK = 1 << V4L2_EXT_VBE_PWM_DEV_PIN4, // PWM# 4
 *           V4L2_EXT_VBE_PWM_DEV_PIN_0_1_MASK =  V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK, // PWM# 0/1
 *           V4L2_EXT_VBE_PWM_DEV_PIN_0_2_MASK =  V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK, // PWM# 0/2
 *           V4L2_EXT_VBE_PWM_DEV_PIN_1_2_MASK =  V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK, // PWM# 1/2
 *           // If necessary, add case
 *           V4L2_EXT_VBE_PWM_DEV_PIN_ALL_MASK =
 *                   V4L2_EXT_VBE_PWM_DEV_PIN_0_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK |
 *                   V4L2_EXT_VBE_PWM_DEV_PIN_2_MASK | V4L2_EXT_VBE_PWM_DEV_PIN_3_MASK |
 *                   V4L2_EXT_VBE_PWM_DEV_PIN_4_MASK, // PWM# 0/1/2/3/4
 *           V4L2_EXT_VBE_PWM_DEV_PIN_DEFAULT_MASK    // depends on pwmIndex setting of HAL_PWM_SetParam function
 *     }
 *     // pwm parameter to set pwm duty only
 *     struct v4l2_ext_vbe_pwm_duty {
 *         enum v4l2_ext_vbe_pwm_pin_sel_mask pwmIndex;
 *         unsigned int pwm_duty;
 *     };
 *
 * Return Value
 *       On success 0 is returned.
 *
 *       On error -1 and the errno variable is set appropriately. The generic error
 *       codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *       Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     // Set PWM duty
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_pwm_duty pwmDutyParam;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pwmDutyParam, 0, sizeof(struct v4l2_ext_vbe_pwm_duty ));
 *
 *     stPWMdutyParam.pwmIndex = V4L2_EXT_VBE_PWM_DEV_PIN_1_MASK;
 *     stPWMdutyParam.pwm_duty = 200;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_PWM_SET_DUTY;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_pwm_duty );
 *     ext_controls.controls->ptr = (void *)&pwmDutyParam;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_PWM_SET_DUTY (V4L2_CID_EXT_VBE_BASE + 20)
/**
 * @brief Set Orbit
 *
 * @rst
 * Functional Requirements
 *   This function can set Orbit
 *   Deprecated since webOS6.0.
 *   Orbit runs in videoOutptutD service.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_ORBIT
 *
 *	   //
 *	   // parameter
 *       //
 *       // ORBIT mode setting
 *       enum v4l2_ext_vbe_panel_orbit_mode {
 *      	 V4L2_EXT_VBE_PANEL_ORBIT_JUSTSCAN_MODE = 0,
 *      	 V4L2_EXT_VBE_PANEL_ORBIT_AUTO_MODE,
 *      	 V4L2_EXT_VBE_PANEL_ORBIT_STORE_MODE,
 *      	 V4L2_EXT_VBE_PANEL_OREBIT_MODE_MAX
 *       };
 *
 *       // ORBIT mode ctrl
 *       struct v4l2_ext_vbe_panel_orbit_info {
 *      	 unsigned int on_off;
 *      	 enum v4l2_ext_vbe_panel_orbit_mode orbitmode;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set Orbit
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_orbit_info orbitInfo;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&orbitInfo, 0, sizeof(struct v4l2_ext_vbe_panel_orbit_info ));
 *
 *     orbitInfo.on_off = (bOnOff == TRUE) ? 1 : 0;
 *     orbitInfo.orbitmode = V4L2_EXT_VBE_PANEL_ORBIT_AUTO_MODE;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_ORBIT;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_orbit_info);
 *     ext_controls.controls->string = (void *)&orbitInfo;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_ORBIT (V4L2_CID_EXT_VBE_BASE + 21)
/**
 * @brief Set LSR
 *
 * @rst
 * Functional Requirements
 *   This function is LSR ctrl for sticky reduction(OLED only)
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_LSR
 *
 *	   //
 *	   // parameter
 *       //
 *       // LSR mode setting
 *       enum v4l2_ext_vbe_panel_lsr_mode {
 *       V4L2_EXT_VBE_PANEL_LSR_OFF = 0,
 *       V4L2_EXT_VBE_PANEL_LSR_LIGHT_VIVID,
 *       V4L2_EXT_VBE_PANEL_LSR_LIGHT_EXPERT2,
 *       V4L2_EXT_VBE_PANEL_LSR_LIGHT_HDRCINEMA,
 *       V4L2_EXT_VBE_PANEL_LSR_STRONG_VIVID,
 *       V4L2_EXT_VBE_PANEL_LSR_STRONG_EXPERT2,
 *       V4L2_EXT_VBE_PANEL_LSR_STRONG_HDRCINEMA,
 *       V4L2_EXT_VBE_PANEL_LSR_STRONG_OTHERS,
 *       V4L2_EXT_VBE_PANEL_LSR_LIGHT_OTHERS,
 *       V4L2_EXT_VBE_PANEL_LSR_MAX
 *       };
 *
 *       // LSR info
 *       struct v4l2_ext_vbe_panel_lsr_info{
 *       unsigned int *pLsrTable;
 *       enum v4l2_ext_vbe_panel_lsr_mode lsrstep;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set LSR
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_lsr_info lsrinfo;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&lsrinfo, 0, sizeof(struct v4l2_ext_vbe_panel_lsr_info));
 *
 *     lsrinfo.pLsrTable = LSRTbl;
 *     lsrinfo.lsrstep = nStep; // UI val or Idx ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_LSR;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_lsr_info);
 *     ext_controls.controls->string = (void *)&lsrinfo;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_LSR (V4L2_CID_EXT_VBE_BASE + 22)
/**
 * @brief Set CPC
 *
 * @rst
 * Functional Requirements
 *   This function is for CPC hw ip control by LG SIC drv support only(OLED
 *only)
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_CPC
 *
 *	   //
 *	   // parameter
 *	   //
 *	   guint8 u8data
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set CPC
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBE_CPC;
 *     control.value = u8data;	  // On
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_CPC (V4L2_CID_EXT_VBE_BASE + 23)
/**
 * @brief Set GSR
 *
 * @rst
 * Functional Requirements
 *   This function is ctrl of global sticky reduction for video area(OLED only).
 *   In case of LGE chip, the GSR operation is performed in the internal BSP FW.
 *   OS chip(other chip vendor), the GSR is handled using the kernel module "libosr" library
 *   as shown in the figure below.
 *   In the library, the local apl (ex, 60*34) value and Bypass RGBgain value at the chip level
 *   are input parameters, and the final GSRgain output value is applied to the screen
 *   through the formula in the library.
 *
 *   Implement for OS chip
 *
 *   .. image:: /panel/resources/vbe-V4L2_CID_EXT_VBE_GSR.png
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_GSR
 *
 *	   //
 *	   // parameter
 *       //
 *       // GSR setting tbl
 *       struct v4l2_ext_vbe_panel_gsr_info{
 *           unsigned int *pGsrTable;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set GSR
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_gsr_info gsrinfo;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&gsrinfo, 0, sizeof(struct v4l2_ext_vbe_panel_gsr_info));
 *
 *     gsrinfo.pGsrTable = TblIdx;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_GSR;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_gsr_info);
 *     ext_controls.controls->string = (void *)&gsrinfo;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls)
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_GSR (V4L2_CID_EXT_VBE_BASE + 24)
/**
 * @brief Set OSDRGBlvl
 *
 * @rst
 * Functional Requirements
 *   This function is for OSD RGB gain ctrl (OLED only)
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_OSD_GAIN
 *
 *	   //
 *	   // parameter
 *       //
 *       // OSD_RGB GAIN setting ctrl
 *       struct v4l2_ext_vbe_panel_osd_gain_info{
 *       unsigned int on_off;
 *       unsigned int *levelval;
 *       unsigned int size; 		  // 4byte size fix for SIC
 *       };
 *
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set OSD RGB gain
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_osd_gain_info osdgaininfo;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&osdgaininfo, 0, sizeof(struct v4l2_ext_vbe_panel_osd_gain_info));
 *
 *     osdgaininfo.on_off = (bOnOff == TRUE) ? 1 : 0;
 *     osdgaininfo.levelval = &u32RGBlevel; //check the val_ originally tbl val
 *     osdgaininfo.size = 4; //4byte fix by chip_vendor data_size
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_OSD_GAIN;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_osd_gain_info);
 *     ext_controls.controls->string = (void *)&osdgaininfo;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_OSD_GAIN (V4L2_CID_EXT_VBE_BASE + 25)
/**
 * @brief getOSDAlphaAPL
 *
 * @rst
 * Functional Requirements
 *   This gets OSD layer alpha value.
 *   4x4 size
 *   When there's no OSD in the screen, average alpah value should be 0.
 *   Where there is OSD in the screen, average alpha value should be updated within 100ms.
 *   Alpha values for a total of 16 blocks by dividing the entire screen into 4x4.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_G_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_ALPHA_OSD
 *
 *	   //
 *	   // parameter
 *     //
 *     //  OSD_Alpha val ctrl
 *     struct v4l2_ext_vbe_panel_alpha_osd_info{
 *       unsigned int *alphaTable;
 *       unsigned int size; 	 // 64byte size fix for SIC
 *     };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Get OSD Alpha Val
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_alpha_osd_info alphaosdinfo;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&alphaosdinfo, 0, sizeof(struct v4l2_ext_vbe_panel_alpha_osd_info));
 *
 *     alphaosdinfo.alphaTable = u32Alpha_apl; // check the val_ originally tbl val
 *     alphaosdinfo.size       = 64;           // 64ea fix by SIC request_Alpha_sic_data_size
 *
 *     ext_controls.ctrl_class       = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count            = 1;
 *     ext_controls.controls         = &ext_control;
 *     ext_controls.controls->id     = V4L2_CID_EXT_VBE_ALPHA_OSD;
 *     ext_controls.controls->size   = sizeof(struct v4l2_ext_vbe_panel_alpha_osd_info);
 *     ext_controls.controls->string = (char *)&alphaosdinfo;
 *
 *     ioctl(_gFdVBE, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_ALPHA_OSD (V4L2_CID_EXT_VBE_BASE + 26)
/**
 * @brief Get GSR Status
 *
 * @rst
 * Functional Requirements
 *   This function is which get GSR func ctrl running status from BSP by LG SIC
 *drv support only(OLED only)
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_G_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_GSR_STATUS
 *
 *	   //
 *	   // parameter
 *	   //
 *	   0 (disable), 1 (enable)
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // GSR Status
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_VBE_GSR_STATUS;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_GSR_STATUS (V4L2_CID_EXT_VBE_BASE + 27)
/**
 * @brief Get Lock Status
 *
 * @rst
 * Functional Requirements
 *   This function is used to get video siganl lock status in the VbyOne interface.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_G_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_LOCK_STATUS
 *
 *	   //
 *	   // parameter
 *	   //
 *	   0 (Unlock), 1 (Lock)
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // Get video signal lock status
 *     struct v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBE_LOCK_STATUS;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_LOCK_STATUS (V4L2_CID_EXT_VBE_BASE + 28)

/**
 * @brief Load Demura data
 *
 * @rst
 * Functional Requirements
 *   It purpose to load the demura data.
 *   It was implemented for SiliconWorks TCON IP
 *   8bit config and data
 *   Requirement 1. Do not skip SoCTS
 *   Requirement 2. Do not clock disable when error return
 *   Requirement 3. Do not use kmalloc
 *   Requirement 4. Keep data setting sequence( ex. first data set, second enable function)
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *	   VIDIOC_G_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBE_DEMURA
 *
 *	   //
 *	   // parameter
 *	   //
 *     // Demura data structure
 *       struct v4l2_ext_vbe_panel_demura {
 *      	 union {
 *      		 unsigned char *config;
 *      		 unsigned int compat_data_ctrl;
 *      		 unsigned long long sizer_ctrl;
 *      	 };
 *      	 unsigned int configsize;
 *      	 unsigned int configcrc;
 *      	 union {
 *      		 unsigned char *data;
 *      		 unsigned int compat_data_demura;
 *      		 unsigned long long sizer_demura;
 *      	 };
 *      	 unsigned int datasize;
 *      	 unsigned int datacrc;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *	 Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Demura Load
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_demura demuraData;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&demuraData, 0, sizeof(struct v4l2_ext_vbe_panel_demura));
 *
 *     demuraData.enable = 1;
 *     demuraData.config = demuraCfgData;
 *     demuraData.configsize =  DEMURA_CFG_SIZE; // 22
 *     demuraData.configcrc = demuraCfgCrc;      //CRC16 2byte
 *
 *     demuraData.data = demuraData;
 *     demuraData.datasize =  DEMURA_DATA_SIZE; // 0x05EEC4
 *     demuraData.datacrc = demuraDataCrc;      //CRC16 2byte
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_DEMURA;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_demura);
 *     ext_controls.controls->ptr = (void *)&demuraData;
 *
 *     //Data Load to registers.
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     //Data Read form registers.
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_DEMURA (V4L2_CID_EXT_VBE_BASE + 29)

/**
 * @brief Load PCLRC Data
 *
 * @rst
 * Functional Requirements
 *   It purpose to load the pclrc data.
 *   It was implemented for SiliconWorks TCON IP
 *   8bit data
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *	   VIDIOC_G_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBE_PCLRC
 *
 *	   //
 *	   // parameter
 *	   //
 *     // pclrc data structure
 *       struct v4l2_ext_vbe_panel_pclrc {
 *      	 unsigned int enable; // 0: disable, 1: enable
 *      	 unsigned int positionAfterLineOD; // 0: before LineOD, 1: after LineOD
 *      	 union {
 *      		 unsigned char *data;
 *      		 unsigned int compat_data_pclrc;
 *      		 unsigned long long sizer_pclrc;
 *      	 };
 *      	 unsigned int datasize;  //4352
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *	 Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Pclrc Load
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_pclrc pclrcData;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&pclrcData, 0, sizeof(struct v4l2_ext_vbe_panel_pclrc));
 *
 *     pclrcData.positionAfterLineOD = 1; // Signal Path 0 : PCLRC -> LOD, 1 : LOD -> PCLRC
 *     pclrcData.data = pclrcData;  //It should write to 8192 to 12543 in SRAM LUT.
 *     pclrcData.datasize =  PCLRC_DATA_SIZE; // 4352
 *     pclrcData.enable = 1;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_PCLRC;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_pclrc);
 *     ext_controls.controls->ptr = (void *)&pclrcData;
 *
 *     //Data Load to registers.
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     //Data Read form registers.
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_PCLRC (V4L2_CID_EXT_VBE_BASE + 30)

/**
 * @brief Set displayoutput 5060Hz
 *
 * @rst
 * Functional Requirements
 *   This function can set displayoutput 5060Hz
 *
 *   This is called when HDMI input video timing is 50hz or 60hz with 120hz panel.
 *   By reducing output frame rate to 50hz or 60hz, video input lag will be improved.
 *
 *   When input signal has 30hz frame rate,
 *   If it is enabled, it would output 60hz.
 *   If it is disabled, it would output 120hz.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   Support models with high frame rate like 100hz or 120hz.
 *   It is reset to the default frame rate after dc power off.
 *
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ
 *
 *	   //
 *	   // parameter
 *	   //
 *	   control value
 *      0 : Normal output of 4K100hz or 4K120Hz to the panel
 *      1 : 4K50Hz or 4K60Hz video output to the panel
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // Set displayoutput 5060Hz
 *	   v4l2_control control;
 *
 *	   control.id = V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ;
 *	   control.value = 1; 	 // On
 *
 *	   ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_DISPLAYOUTPUT_5060HZ (V4L2_CID_EXT_VBE_BASE + 31)

//
// GSR_STRESS_COUNT control ID
//
/**
 * @brief Get GSR_STRESS_COUNT
 *
 * @rst
 * Functional Requirements
 *   This function is when there are more than a few stop areas usng the GSR detect block
 *   (threshold ex: 100) after Power ON,
 *   the time is counted accumulated for 10 minutes (spec), and the counting value is delivered.
 *   Operability of the FW (BSP) : Normalized for frame rate variation based on output frame rate
 *   domain.
 *   (ex,24/25/30hz based on input considering all input timing, In case of 120hz input,
 *   when the worst img input 120frame comes, count 1 is accumulated.)
 *   Accumulated val must be maintained until suspend or cold pwr state.
 *   In case of OS chip, LG_GSR_StressCount symbol value in Libosr is transferred through the
 *   v4l2_GetGSRStressCount function.
 *
 *   USE case
 *
 *   .. image:: /panel/resources/panel/vbe-V4L2_CID_EXT_VBE_GSR_STRESS_COUNT.png
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_G_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_GSR_STRESS_COUNT
 *
 *	   //
 *	   // parameter
 *	   //
 *	   unsigned int;
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // GSR_STRESS_COUNT
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_VBE_GSR_STRESS_COUNT;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_GSR_STRESS_COUNT (V4L2_CID_EXT_VBE_BASE + 32)

//
// SET GSR2 control ID
//
/**
 * @brief Set GSR2
 *
 * @rst
 * Functional Requirements
 *   This function is ctrl of GSR2 (global sticky reduction 2) for video area(OLED only).
 *   Reduces the luminance per pixel, which has a high risk of afterimages of high
 *   luminance/high color, not the overall luminance reduction.
 *
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_GSR2
 *
 *	   //
 *	   // parameter
 *     //
 *     // GSR setting tbl
 *       struct v4l2_ext_vbe_panel_second_gsr_info{
 *              unsigned int *pGsrTable;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set GSR2
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_panel_second_gsr_info gsr2info;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&gsr2info, 0, sizeof(struct v4l2_ext_vbe_panel_second_gsr_info));
 *
 *     gsr2info.pGsrTable = Tbl;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_GSR2;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_second_gsr_info);
 *     ext_controls.controls->string = (void *)&gsr2info;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls)
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_GSR2 (V4L2_CID_EXT_VBE_BASE + 33)

//
// SET IRRAdaptedLum control ID
//
/**
 * @brief Set IrrAdaptedLum
 *
 * @rst
 * Functional Requirements
 *   This function is set of Image retention risk for luminance (OLED SIC chip only).
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_IRR_ADAPTEDLUM
 *
 *	   //
 *	   // parameter
 *     //
 *     // PQ luminance setting factor(PLC portion)
 *       struct v4l2_ext_vbe_panel_irr_info{
 *              unsigned int *pIrrlum;
 *       };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set GSR2
 *       struct v4l2_ext_controls ext_controls;
 *       struct v4l2_ext_control ext_control;
 *       struct v4l2_ext_vbe_panel_irr_info irr;
 *
 *       memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *       memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *       memset(&irr, 0, sizeof(struct v4l2_ext_vbe_panel_irr_info));
 *
 *       irr.pIrrlum = Lumdata;
 *
 *       ext_controls.ctrl_class       = V4L2_CTRL_CLASS_USER;
 *       ext_controls.count            = 1;
 *       ext_controls.controls         = &ext_control;
 *       ext_controls.controls->id     = V4L2_CID_EXT_VBE_IRR_ADAPTEDLUM;
 *       ext_controls.controls->size   = sizeof(struct v4l2_ext_vbe_panel_irr_info);
 *       ext_controls.controls->string = (char *)&irr;
 *
 *     ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls)
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_IRR_ADAPTEDLUM (V4L2_CID_EXT_VBE_BASE + 34)

//
// GET IRR RISK control ID
//
/**
 * @brief Get GetIrrResult
 *
 * @rst
 * Functional Requirements
 *  This function is getter of IRR risk when using the AI image retention risk detect block.
 *  (OLED SIC chip only).
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_G_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_IRR_RESULT
 *
 *	   //
 *	   // parameter
 *	   //
 *	   unsigned int;
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *	   // Image Retention Risk
 *     v4l2_control control;
 *     control.id = V4L2_CID_EXT_VBE_IRR_RESULT;
 *
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_IRR_RESULT (V4L2_CID_EXT_VBE_BASE + 35)

//
// SET TPC Recovery Param control ID
//
/**
 * @brief SetTpcRecoveryParam
 *
 * @rst
 * This function is set of TPC Recovery parameter table for New TPC (OLED SIC chip only).
 *
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *      //
 *      // ioctl command
 *      //
 *      VIDIOC_S_EXT_CTRLS
 *
 *      //
 *      // control id
 *      //
 *      // You have to make the new control id as the below.
 *      V4L2_CID_EXT_VBE_TPC_RECOVERY_PARAM
 *
 *      //
 *      // parameter
 *      //
 *      // setting tbl
 *      struct v4l2_ext_vbe_panel_tpc_recovery_param_info {
 *          union {
 *              unsigned int *pParamTable;
 *              unsigned int compat_data_paramtable;
 *              unsigned long long sizer_paramtable;
 *          };
 *          unsigned int table_size;
 *      };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      // Set TPC Recovery Param
 *      struct v4l2_ext_controls ext_controls;
 *      struct v4l2_ext_control ext_control;
 *      struct v4l2_ext_vbe_panel_tpc_recovery_param_info tpcinfo;
 *
 *      memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *      memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *      memset(&tpcinfo, 0, sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_param_info));
 *
 *      tpcinfo.pParamTable = Tbl;
 *      tpcinfo.table_size = 64; // 4byte * 16EA data
 *
 *      ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_VBE_TPC_RECOVERY_PARAM;
 *      ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_param_info);
 *      ext_controls.controls->string = (char *)&tpcinfo;
 *
 *      ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls)
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_TPC_RECOVERY_PARAM (V4L2_CID_EXT_VBE_BASE + 36)

//
// GET TPC Recovery Status control ID
//
/**
 * @brief GetTpcRecoveryStatus
 *
 * @rst
 * This function is getter of calc result for decide if TPC dimming need to recover or not
 * (OLED SIC chip only).
 *
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *      //
 *      // ioctl command
 *      //
 *      VIDIOC_G_CTRL
 *
 *      //
 *      // control id
 *      //
 *      // You have to make the new control id as the below.
 *      V4L2_CID_EXT_VBE_TPC_RECOVERY_STATUS
 *
 *      //
 *      // parameter
 *      //
 *      // Get TPC Recovery Status
 *      struct v4l2_ext_vbe_panel_tpc_recovery_status_info {
 *          union {
 *              unsigned int *tpcStatusTable;
 *              unsigned int compat_data_statustable;
 *              unsigned long long sizer_statustable;
 *          };
 *          unsigned int table_size;
 *      };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      // Get TPC Recovery Status
 *      struct v4l2_ext_controls ext_controls;
 *      struct v4l2_ext_control ext_control;
 *      struct v4l2_ext_vbe_panel_tpc_recovery_status_info tpcstatus;
 *
 *      memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *      memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *      memset(&tpcstatus, 0, sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_status_info));
 *
 *      tpcstatus.tpcStatusTable = Tbl;
 *      tpcstatus.table_size = 16; // 4byte * 4EA data
 *
 *      ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_VBE_TPC_RECOVERY_STATUS;
 *      ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_tpc_recovery_status_info);
 *      ext_controls.controls->string = (char *)&tpcstatus;
 *
 *      ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls)
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_TPC_RECOVERY_STATUS (V4L2_CID_EXT_VBE_BASE + 37)

//
// GET VBE APL ID
//
/**
 * @brief Get VbeApl
 *
 * @rst
 * This function is getter of apl values for decide if TPC dimming is needed or not
 * (OLED SIC chip only).
 *
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_G_C
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBE_GET_APL_FOR_
 *     //
 *     // parameter
 *     //
 *     // Get VBE APL
 *     struct v4l2_ext_vbe_panel_tpc_apl_info {
 *         union {
 *             unsigned int *tpcAplInfoTable;
 *             unsigned int compat_data_statustable;
 *             unsigned long long sizer_statustable;
 *         };
 *         unsigned int table_size;
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set data using VIDIOC_G_CTRL and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      // Get VBE APL Info
 *      struct v4l2_ext_controls ext_controls;
 *      struct v4l2_ext_control ext_control;
 *      struct v4l2_ext_vbe_panel_tpc_apl_info tpcApl;
 *
 *      memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *      memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *      memset(&tpcApl, 0, sizeof(struct v4l2_ext_vbe_panel_tpc_apl_info));
 *
 *      tpcApl.tpcAplInfoTable = Tbl;
 *      tpcApl.table_size = 16; // 4byte * 4EA data
 *
 *      ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_VBE_GET_APL_FOR_TPC;
 *      ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_tpc_apl_info);
 *      ext_controls.controls->string = (char *)&tpcApl;
 *
 *      ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls)
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_GET_APL_FOR_TPC (V4L2_CID_EXT_VBE_BASE + 38)

//
// VAC(Viewing Angle Compensation) param ID
//
/**
 * @brief Load Viewing Angle Compensation param
 *
 * @rst
 * Functional Requirements
 *   It purpose to load and get the parameters for VAC(Viewing Angle Compensation).
 *   It was implemented to set a special block of SoC for VAC effects.
 *   It is not included to enable and disable this VAC effect.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *    .. code-block:: cpp
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
 *     // You have to make the new control id as the below
 *     V4L2_CID_EXT_VBE_VAC_PARAM
 *
 *     //
 *     // parameter
 *     //
 *     // The VAC parameter structure is different from each SoC.
 *     // Thus, it can not be defined as a fixed structure.
 *     // Each SoC driver should receive the void pointer and typecast as SoC's
 *     // own VAC structure.
 *
 * Return Value
 *    On success 0 is returned.
 *
 *    On error -1 and the errno variable is set appropriately.
 *
 *    The generic error codes are described at the :ref:`gen_errors` chapter
 *
 * Control Type
 *    Application can set/get parameter using VIDIOC_S_EXT_CTRLS and this control id
 *
 * Example
 *    .. code-block:: cpp
 *
 *     int fd = _gFdVBE;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_VAC_PARAM;
 *     ext_controls.controls->ptr = (void *)vacParam;
 *
 *     //Send VAC Parameters to SoC
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     //Read VAC Parameters from SoC
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_VAC_PARAM (V4L2_CID_EXT_VBE_BASE + 39)

//
// VAC(Viewing Angle Compensation) On Off Control ID
//
/**
 * @brief Enable and Disable VAC(Viewing Angle Compensation) function
 *
 * @rst
 * Functional Requirements
 *    This function can set to Enable/Disable VAC(Viewing Angle Compensation)
 *
 * Responses to abnormal situations, including
 *    None.
 *
 * Performance Requirements
 *    It should be returned within 10 msec.
 *
 * Constraints
 *    None.
 *
 * Functions & Parameters
 *    .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_CTRL
 *     VIDIOC_G_CTRL
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below.
 *     V4L2_CID_EXT_VBE_VAC_CONTROL
 *
 *     //
 *     // parameter
 *     //
 *     0 (Off), 1 (On)
 *
 * Return Value
 *    On success 0 is returned.
 *
 *    On error -1 and the errno variable is set appropriately.
 *
 *    The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *    Application can set/get parameter using VIDIOC_S_CTRL and this control id
 *
 * Example
 *    .. code-block:: cpp
 *
 *     // Enable/Disable the Viewing Angle Compensation function
 *     int fd = _gFdVBE;
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBE_VAC_CONTROL;
 *
 *     //Send Parameter to SoC
 *     control.value = 1; 	 // 1:On, 0:Off
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 *     //Read Parameter from SoC
 *     ioctl(fd, VIDIOC_G_CTRL, &control);
 * @endrst
 */
#define V4L2_CID_EXT_VBE_VAC_CONTROL (V4L2_CID_EXT_VBE_BASE + 40)

//
// SET OLED APL CTRL Param control ID
//
/**
 * @brief SetOledAplCtrlParam
 *
 * @rst
 * This function is set of OLED APL control parameter table (OLED SIC chip only).
 *
 *
 * Commands & Parameters
 *   .. code-block:: cpp
 *
 *      //
 *      // ioctl command
 *      //
 *      VIDIOC_S_EXT_CTRLS
 *
 *      //
 *      // control id
 *      //
 *      // You have to make the new control id as the below.
 *      V4L2_CID_EXT_VBE_OLED_APL_CTRL_PARAM
 *
 *      //
 *      // parameter
 *      //
 *      // setting tbl
 *      struct v4l2_ext_vbe_panel_apl_control_param_info {
 *          union {
 *              unsigned int *pParamTable;
 *              unsigned int compat_data_paramtable;
 *              unsigned long long sizer_paramtable;
 *          };
 *          unsigned int table_size;
 *      };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *
 *      // Set OLED APL control Param
 *      struct v4l2_ext_controls ext_controls;
 *      struct v4l2_ext_control ext_control;
 *      struct v4l2_ext_vbe_panel_apl_control_param_info oledAplinfo;
 *
 *      memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *      memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *      memset(&oledAplinfo, 0, sizeof(struct v4l2_ext_vbe_panel_apl_control_param_info));
 *
 *      oledAplinfo.pParamTable = Tbl;
 *      oledAplinfo.table_size = 64; // 4byte * 16EA data
 *
 *      ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count = 1;
 *      ext_controls.controls = &ext_control;
 *      ext_controls.controls->id = V4L2_CID_EXT_VBE_OLED_APL_CTRL_PARAM;
 *      ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_panel_apl_control_param_info);
 *      ext_controls.controls->string = (char *)&oledAplinfo;
 *
 *      ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls)
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_OLED_APL_CTRL_PARAM (V4L2_CID_EXT_VBE_BASE + 41)

//
// CSPI P-Gamma param ID
//
/**
 * @brief Set P-Gamma ctrl data for CSPI(Configurable Serial Peripheral Interface)
 *
 * @rst
 * Functional Requirements
 *   It purpose to load the parameters for P-Gamma ctrl data for CSPI.
 *   It was implemented to set a special block of P-Gamma ctrl data for CSPI.
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
 *    .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below
 *     V4L2_CID_EXT_VBE_CSPI_PGAMMA_CONTROL
 *
 *     //
 *     // parameter
 *     //
 *     //  setting tbl
 *     struct v4l2_ext_vbe_cspi_pgamma_control_param {
 *         union {
 *             unsigned int *pCtrlData;
 *             unsigned int compat_data_cspipgamma;
 *             unsigned long long sizer_cspipgamma;
 *         };
 *         unsigned int ctrlDataCount;
 *     };
 *
 * Return Value
 *    On success 0 is returned.
 *
 *    On error -1 and the errno variable is set appropriately.
 *
 *    The generic error codes are described at the :ref:`gen_errors` chapter
 *
 * Control Type
 *    Application can set parameter using VIDIOC_S_EXT_CTRLS and this control id
 *
 * Example
 *    .. code-block:: cpp
 *
 *     int fd = _gFdVBE;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_cspi_pgamma_control_param cspiPgammaData;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&cspiPgammaData, 0, sizeof(struct v4l2_ext_vbe_cspi_pgamma_control_param));
 *
 *     cspiPgammaData.pCtrlData = Tbl;
 *     cspiPgammaData.ctrlDataCount = 14;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_CSPI_PGAMMA_CONTROL;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_cspi_pgamma_control_param);
 *     ext_controls.controls->ptr = (void *)cspiPgammaData;
 *
 *     //Send PGamma Parameters to SoC
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_CSPI_PGAMMA_CONTROL (V4L2_CID_EXT_VBE_BASE + 42)

//
// VDF(VRR De Flicker) param ID
//
/**
 * @brief Set VDF(VRR De Flicker) ctrl data
 *
 * @rst
 * Functional Requirements
 *   It purpose to load the parameters for VDF(VRR De Flicker).
 *   It was implemented to set a special block of SoC or PMIC for VDF.
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
 *    .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below
 *     V4L2_CID_EXT_VBE_VDF_CONTROL
 *
 *     //
 *     // parameter
 *     //
 *     // The VDF parameter structure is different from each SoC.
 *     // Thus, it can not be defined as a fixed structure.
 *     // Each SoC driver should receive the void pointer and typecast as SoC's
 *     // own VDF structure define.
 *
 * Return Value
 *    On success 0 is returned.
 *
 *    On error -1 and the errno variable is set appropriately.
 *
 *    The generic error codes are described at the :ref:`gen_errors` chapter
 *
 * Control Type
 *    Application can set parameter using VIDIOC_S_EXT_CTRLS and this control id
 *
 * Example
 *    .. code-block:: cpp
 *
 *     int fd = _gFdVBE;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_VDF_CONTROL;
 *     ext_controls.controls->ptr = (void *)vdfParam;
 *
 *     //Send VDF Parameters to SoC
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_VDF_CONTROL (V4L2_CID_EXT_VBE_BASE + 43)

/**
 * @brief Set Soc output dclk
 *
 * @rst
 * Functional Requirements
 *   This function is used to change SoC output dclk.
 *   The SoC output dclk setting will be contolled by one of v4l2_ext_vbe_dclk_mode.
 *   The function is called after OLED Tcon frame rate setting is completed.
 *   The function is called when input signal is VRR or input timing is 165Hz in hdmi input.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   None.
 *
 * Constraints
 *   OLED only.
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_EXT_CTRLS
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_DCLK_MODE
 *
 *	   //
 *	   // parameter
 *	   //
 *      enum v4l2_ext_vbe_dclk_mode {
 *     	 V4L2_EXT_VBE_DCLK_MODE_BASIC, // V4L2_EXT_VBE_DCLK_MODE_BASIC = 0
 *     	 V4L2_EXT_VBE_DCLK_MODE_165HZ, // V4L2_EXT_VBE_DCLK_MODE_165HZ,
 *     	 V4L2_EXT_VBE_DCLK_MODE_MAX
 *      };
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     enum v4l2_ext_vbe_dclk_mode dclkmode;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&dclkmode, 0, sizeof(enum v4l2_ext_vbe_dclk_mode));
 *
 *     dclkmode = V4L2_EXT_VBE_DCLK_MODE_165HZ;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_DCLK_MODE;
 *     ext_controls.controls->size = sizeof(enum v4l2_ext_vbe_dclk_mode);
 *     ext_controls.controls->ptr = (void *)&dclkmode;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_DCLK_MODE (V4L2_CID_EXT_VBE_BASE + 44)

//
// VDF Gamma Table Setting ID
//
/**
 * @brief Set Digital Gamma Curve Parameters for VDF(VRR De Flicker)
 *
 * @rst
 * Functional Requirements
 *   It purpose is to load the r,g,b curve parameter of different gamma blocks for VDF.
 *
 *   And SoC does a combination of output from some gamma blocks.
 *
 *   It was implemented to reduce VRR flicker.
 *
 * Constraints
 *   It needs some digital gamma blocks(at least 2 blocks) at SoC.
 *
 * Functions & Parameters
 *    .. code-block:: cpp
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
 *     // You have to make the new control id as the below
 *     V4L2_CID_EXT_VBE_VDF_GAMMA_PARAM
 *
 *     //
 *     // parameter
 *     //
 *     //  setting tbl
 *     struct v4l2_ext_vbe_vdf_gamma_curve {
 *         union {
 *             unsigned int *pRtbl; // data is 12bit
 *             unsigned int compat_data_R;
 *             unsigned long long sizer_R;
 *         };
 *         union {
 *             unsigned int *pGtbl; // data is 12bit
 *             unsigned int compat_data_G;
 *             unsigned long long sizer_G;
 *         };
 *         union {
 *             unsigned int *pBtbl; // data is 12bit
 *             unsigned int compat_data_B;
 *             unsigned long long sizer_B;
 *         };
 *         unsigned int table_size; // each table size
 *     };
 *     struct v4l2_ext_vbe_vdf_gamma_param {
 *         unsigned char isOn; // 0:off, 1:on
 *         struct v4l2_ext_vbe_vdf_gamma_curve lowFrameRateTable; // for low frequency
 *         struct v4l2_ext_vbe_vdf_gamma_curve highFrameRateTable; // for high frequency
 *         union {
 *             unsigned int *vdfGammaControlParam; // Not defined (in current, no use this param)
 *             unsigned int compat_vdfGammaControlParam;
 *             unsigned long long sizer_vdfGammaControlParam;
 *         };
 *     };
 *
 * Return Value
 *    On success 0 is returned.
 *
 *    On error -1 and the errno variable is set appropriately.
 *
 *    The generic error codes are described at the :ref:`gen_errors` chapter
 *
 * Control Type
 *    Application can set parameter using VIDIOC_S_EXT_CTRLS and this control id.
 *    Application can get parameter using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *    .. code-block:: cpp
 *
 *     int fd = _gFdVBE;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_vdf_gamma_param vdfGammaParam;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&vdfGammaParam, 0, sizeof(struct v4l2_ext_vbe_vdf_gamma_param));
 *
 *     vdfGammaParam.isOn = 1;
 *
 *     vdfGammaParam.lowFrameRateTable.pRtbl = Low_Tbl_R;
 *     vdfGammaParam.lowFrameRateTable.pGtbl = Low_Tbl_G;
 *     vdfGammaParam.lowFrameRateTable.pBtbl = Low_Tbl_B;
 *     vdfGammaParam.lowFrameRateTable.table_size = 1024;
 *
 *     vdfGammaParam.highFrameRateTable.pRtbl = High_Tbl_R;
 *     vdfGammaParam.highFrameRateTable.pGtbl = High_Tbl_G;
 *     vdfGammaParam.highFrameRateTable.pBtbl = High_Tbl_B;
 *     vdfGammaParam.highFrameRateTable.table_size = 1024;
 *
 *     vdfGammaParam.vdfGammaControlParam = tempVdfGammaControlParamArray;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_VDF_GAMMA_PARAM;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_vdf_gamma_param);
 *     ext_controls.controls->ptr = (void *)vdfGammaParam;
 *
 *     //Send Gamma Parameters for VDF to SoC
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *     //Read Gamma Parameters for VDF from SoC
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_VDF_GAMMA_PARAM (V4L2_CID_EXT_VBE_BASE + 45)

 /**
 * @brief Set SoC Output Frequency Mode
 *
 * @rst
 * Functional Requirements
 *   This function is used to change SoC Frequency Mode.
 *   The SoC Output Dclk will be contolled by each mode define.
 *   The function is called after OLED Tcon frame rate setting is completed.
 *   The function is called when full screen((x, y, w, h)=(0, 0, resoution_W, resoution_H) is displayed,
 *   and input timing is 60Hz/120Hz/240Hz in hdmi or usb-c or DP input
 *
 * Functions & Parameters
 *     .. code-block:: cpp
 *
 *       //
 *       // ioctl command
 *       //
 *       VIDIOC_S_EXT_CTRLS
 *
 *       //
 *       // control id
 *       //
 *       // You have to make the new control id as the below.
 *       V4L2_CID_EXT_VBE_FREQUENCY_MODE
 *
 *       //
 *       // parameter
 *       //
 *      enum v4l2_ext_vbe_frequency_mode {
 *        V4L2_EXT_VBE_FREQUENCY_MODE_240Hz,  // for normal output(240Hz)
 *        V4L2_EXT_VBE_FREQUENCY_MODE_120Hz,  // for 120Hz output
 *        V4L2_EXT_VBE_FREQUENCY_MODE_60Hz,   // for 60Hz output
 *        V4L2_EXT_VBE_FREQUENCY_MODE_MAX
 *       };
 *
 * Return Value
 *     On success 0 is returned.
 *
 *     On error -1 and the errno variable is set appropriately. The generic
 *error
 *     codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *     Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *     .. code-block:: cpp
 *
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     enum v4l2_ext_vbe_frequency_mode frequency_mode;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&frequency_mode, 0, sizeof(enum v4l2_ext_vbe_frequency_mode));
 *
 *     frequency_mode = V4L2_EXT_VBE_FREQUENCY_MODE_120Hz;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_FREQUENCY_MODE;
 *     ext_controls.controls->size = sizeof(enum v4l2_ext_vbe_frequency_mode);
 *     ext_controls.controls->ptr = (void *)&frequency_mode;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */

#define V4L2_CID_EXT_VBE_FREQUENCY_MODE (V4L2_CID_EXT_VBE_BASE + 46)


/**
 * @brief
 *   Defines the Control ID to subscribe vsync event for OLED liner DPC.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used to subscribe vsync event for oled linear dpc.
 *   - Details of Feature
 *      Driver should make the event of file handler whenever video vsync happens.
 *      When "V4L2_CID_EXT_VBE_SUBSCRIBE_DPC" event is subscribed by "VIDIOC_SUBSCRIBE_EVENT" call in driver,
 *      driver should generate "V4L2_CID_EXT_VBE_SUBSCRIBE_DPC" event for each vbe vsync.
 *      Driver should implement epoll() operation so that user application can get the kernel event from epoll().
 *   - Target Hardware Block
 *      NA
 *   - Call frequency and timing
 *      It is subscribed when linear DPC is turned on.
 *      It is unsubscribed when linear DPC is turned off.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *     VIDIOC_DQEVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_VSYNC
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VBE_SUBSCRIBE_DPC
 *
 *     //
 *     // Parameter
 *     //
 *     // Use data[64] in the struct v4l2_event in videodev2.h
 *     // This struct is used by VIDIOC_DQEVENT.
 *     struct v4l2_event {
 *         __u32               type;
 *         union {
 *             struct v4l2_event_vsync     vsync;
 *             struct v4l2_event_ctrl      ctrl;
 *             struct v4l2_event_frame_sync    frame_sync;
 *             struct v4l2_event_src_change    src_change;
 *             struct v4l2_event_motion_det    motion_det;
 *             __u8                data[64];
 *         } u;
 *         __u32               pending;
 *         __u32               sequence;
 *         struct timespec         timestamp;
 *         __u32               id;
 *         __u32               reserved[8];
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     vbe_fd=open(V4L2_EXT_DEV_PATH_BACKEND, O_RDWR);
 *
 *     // Subscribe event
 *     struct v4l2_event_subscription event{0};
 *     event.type = V4L2_EVENT_VSYNC;
 *     event.id = V4L2_CID_EXT_VBE_SUBSCRIBE_DPC;
 *     ioctl(vbe_fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *     // Unsubscribe event
 *     struct v4l2_event_subscription event{0};
 *     event.type = V4L2_EVENT_VSYNC;
 *     event.id = V4L2_CID_EXT_VBE_SUBSCRIBE_DPC;
 *     ioctl(vbe_fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 *     // Wait epoll event
 *     epoll_fd = epoll_create1(0);
 *
 *     struct epoll_event event{};
 *     event.events  = EPOLLIN | EPOLLPRI;
 *     event.data.fd = vbe_fd;
 *     epoll_ctl(epoll_fd, EPOLL_CTL_ADD, vbe_fd, &event);
 *
 *     struct epoll_event event_data[MAX_EPOLL_EVENT]{};
 *     epoll_wait(epoll_fd, event_data, MAX_EPOLL_EVENT, EPOLL_TIMEOUT);
 *
 *     if (event_data[i].data.fd == vbe_fd)
 *         if (event_data[i].events & (EPOLLIN | EPOLLPRI))
 *             panel_event_handler();
 *
 *     // Dequeue event in panel_event_handler()
 *     struct v4l2_event ev{0};
 *     ioctl(vbe_fd, VIDIOC_DQEVENT, &ev);
 *
 *     if(ev.id == V4L2_CID_EXT_VBE_SUBSCRIBE_DPC)
 *     {
 *         get_apl();
 *         set_pwm_duty();
 *     }
 *
 *     // Stop epoll event
 *     epoll_ctl(epoll_fd, EPOLL_CTL_DEL, vbe_fd, NULL);
 *     close(epoll_fd);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_SUBSCRIBE_DPC (V4L2_CID_EXT_VBE_BASE + 47)

/**
 * @brief
 *   Defines the Control ID to subscribe general vsync event.
 *
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used to subscribe general vsync event.
 *   - Details of Feature
 *      Driver should make the event of file handler whenever video vsync happens.
 *      When "V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC" event is subscribed by "VIDIOC_SUBSCRIBE_EVENT" call in driver,
 *      driver should generate "V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC" event for each vbe vsync.
 *      Driver should implement epoll() operation so that user application can get the kernel event from epoll().
 *   - Target Hardware Block
 *      NA
 *   - Call frequency and timing
 *      It is subscribed when webOS want to get vsync timing.
 *      It is unsubscribed when webOS don't want to get vsync timing.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_SUBSCRIBE_EVENT
 *     VIDIOC_UNSUBSCRIBE_EVENT
 *     VIDIOC_DQEVENT
 *
 *     //
 *     // v4l2_event_subscription type
 *     //
 *     V4L2_EVENT_VSYNC
 *
 *     //
 *     // v4l2_event_subscription id
 *     //
 *     // You have to make the new v4l2_event_subscription id as the below.
 *     V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC
 *
 *     //
 *     // Parameter
 *     //
 *     // Use data[64] in the struct v4l2_event in videodev2.h
 *     // This struct is used by VIDIOC_DQEVENT.
 *     struct v4l2_event {
 *         __u32               type;
 *         union {
 *             struct v4l2_event_vsync     vsync;
 *             struct v4l2_event_ctrl      ctrl;
 *             struct v4l2_event_frame_sync    frame_sync;
 *             struct v4l2_event_src_change    src_change;
 *             struct v4l2_event_motion_det    motion_det;
 *             __u8                data[64];
 *         } u;
 *         __u32               pending;
 *         __u32               sequence;
 *         struct timespec         timestamp;
 *         __u32               id;
 *         __u32               reserved[8];
 *     };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately. The generic error
 *   codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set event using
 *   VIDIOC_SUBSCRIBE_EVENT/VIDIOC_UNSUBSCRIBE_EVENT.
 *
 * Example
 *   .. code-block:: cpp
 *
 *     vbe_fd=open(V4L2_EXT_DEV_PATH_BACKEND, O_RDWR);
 *
 *     // Subscribe event
 *     struct v4l2_event_subscription event{0};
 *     event.type = V4L2_EVENT_VSYNC;
 *     event.id = V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC;
 *     ioctl(vbe_fd, VIDIOC_SUBSCRIBE_EVENT, &event);
 *
 *     // Unsubscribe event
 *     struct v4l2_event_subscription event{0};
 *     event.type = V4L2_EVENT_VSYNC;
 *     event.id = V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC;
 *     ioctl(vbe_fd, VIDIOC_UNSUBSCRIBE_EVENT, &event);
 *
 *     // Wait epoll event
 *     epoll_fd = epoll_create1(0);
 *
 *     struct epoll_event event{};
 *     event.events  = EPOLLIN | EPOLLPRI;
 *     event.data.fd = vbe_fd;
 *     epoll_ctl(epoll_fd, EPOLL_CTL_ADD, vbe_fd, &event);
 *
 *     struct epoll_event event_data[MAX_EPOLL_EVENT]{};
 *     epoll_wait(epoll_fd, event_data, MAX_EPOLL_EVENT, EPOLL_TIMEOUT);
 *
 *     if (event_data[i].data.fd == vbe_fd)
 *         if (event_data[i].events & (EPOLLIN | EPOLLPRI))
 *             panel_event_handler();
 *
 *     // Dequeue event in panel_event_handler()
 *     struct v4l2_event ev{0};
 *     ioctl(vbe_fd, VIDIOC_DQEVENT, &ev);
 *
 *     if(ev.id == V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC)
 *     {
 *         start_graphic_rendering_cycle();
 *     }
 *
 *     // Stop epoll event
 *     epoll_ctl(epoll_fd, EPOLL_CTL_DEL, vbe_fd, NULL);
 *     close(epoll_fd);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_SUBSCRIBE_VSYNC (V4L2_CID_EXT_VBE_BASE + 48)

/**
 * @brief enable / disable PCCE(Power Constrained Contrast Enhancement)
 *
 * @rst
 * Functional Requirements
 *   This function can enable PCCE algorithm
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   None.
 *
 * Constraints
 *   It is enabled by PSM and MEMC UI conditions.
 *   SIC O26 Only
 *
 * Functions & Parameters
 *	 .. code-block:: cpp
 *
 *	   //
 *	   // ioctl command
 *	   //
 *	   VIDIOC_S_CTRL
 *
 *	   //
 *	   // control id
 *	   //
 *	   // You have to make the new control id as the below.
 *	   V4L2_CID_EXT_VBE_PCCE
 *
 *	   //
 *	   // parameter
 *	   //
 *	   0 (Off), 1 (On)
 *
 * Return Value
 *	 On success 0 is returned.
 *
 *	 On error -1 and the errno variable is set appropriately. The generic
 *error
 *	 codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using VIDIOC_S_CTRL and this control id.
 *
 * Example
 *	 .. code-block:: cpp
 *
 *     // Set screen mute
 *     v4l2_control control;
 *
 *     control.id = V4L2_CID_EXT_VBE_PCCE;
 *     control.value = 1; 	 // On
 *
 *     ioctl(fd, VIDIOC_S_CTRL, &control);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_PCCE (V4L2_CID_EXT_VBE_BASE + 49)

//
// OUTPUT TIMING DATA param ID
//
/**
* @brief Set OUTPUT Timing related data
*
 * @rst
 * Functional Requirements
 *   - Purpose
 *      This Control ID is used to send the command and parameters to set output timing related block.
 *   - Details of Feature
 *      When setType is V4L2_EXT_VBE_OUTPUT_SET_TIMING_TYPE, Driver change output timing block with *pTimingParam.
 *      When setType is V4L2_EXT_VBE_OUTPUT_INIT_ALLTCONBINDATA_TYPE, Driver should save the full combined tcon.bin
 *      data from *extraInfo which has a address and size of the full combined tcon.bin data.
 *      When setType is V4L2_EXT_VBE_OUTPUT_SELECT_ONETCONDATA_TYPE, Driver should select a single tcon data among the
 *      full combined tcon.bin datas, and change output blocks with the selected single tcon data.
 *   - Target Hardware Block
 *      output timing setting blocks
 *   - Call frequency and timing
 *      If setType is V4L2_EXT_VBE_OUTPUT_INIT_ALLTCONBINDATA_TYPE, it is called only one time at ac power on flow.
 *      It setType is other cases, it is called when input timing is changed between normal timing and special timing
 *      which needs to be set with different timing parameters.
 *
 * Responses to abnormal situations, including
 *   See the Return Value.
 *
 * Constraints
 *   It could be only used to model which is applied with tcon.bin file.
 *
 * Functions & Parameters
 *    .. code-block:: cpp
 *
 *     //
 *     // ioctl command
 *     //
 *     VIDIOC_S_EXT_CTRLS
 *
 *     //
 *     // control id
 *     //
 *     // You have to make the new control id as the below
 *     V4L2_CID_EXT_VBE_OUTPUT_TIMING
 *
 *     //
 *     // parameter
 *     //
 *     //  setting tbl
 *     struct v4l2_ext_vbe_output_settingdata {
 *         enum v4l2_ext_vbe_outputsetting_type setType;
 *         union {
 *             v4l2_ext_vbe_output_timing *pTimingParam;
 *             unsigned int compat_data_timingParam;
 *             unsigned long long sizer_timingParam;
 *         };
 *         union {
 *             void *extraInfo;
 *             unsigned int compat_data_extraInfo;
 *             unsigned long long sizer_extraInfo;
 *         };
 *     };
 *
 * Return Value
 *    On success 0 is returned.
 *
 *    On error -1 and the errno variable is set appropriately.
 *
 *    On error -20 when mis-matching data issue happens if setType is
 *                  V4L2_EXT_VBE_OUTPUT_SELECT_ONETCONDATA_TYPE case
 *
 *    The generic error codes are described at the :ref:`gen_errors` chapter
 *
 * Control Type
 *    Application can set parameter using VIDIOC_S_EXT_CTRLS and this control id
 *    Application can get parameter using VIDIOC_G_EXT_CTRLS and this control id
 *
 * Example
 *    .. code-block:: cpp
 *
 *     int fd = _gFdVBE;
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     struct v4l2_ext_vbe_output_timing outputTimingTbl = { 288, 0, 0, 0, 0, 0, 0, 0, 0, 3840, 1080, 0, 0};
 *     struct v4l2_ext_vbe_output_settingdata settingData;
 *
 *     memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(struct v4l2_ext_control));
 *     memset(&settingData, 0, sizeof(struct v4l2_ext_vbe_output_settingdata));
 *
 *     settingData.setTypeInfo = (v4l2_ext_vbe_outputsetting_type)V4L2_EXT_VBE_OUTPUT_SELECT_ONETCONDATA_TYPE;
 *     settingData.pTimingParam = &outputTimingTbl;
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_OUTPUT_TIMING;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_output_settingdata);
 *     ext_controls.controls->ptr = (void *)settingData;
 *
 *     //Send Output setting data to SoC
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_OUTPUT_TIMING (V4L2_CID_EXT_VBE_BASE + 50)

 /**
 * @brief Set AI Detection Object APL Gain for Local Dimming
 *
 * @rst
 * Functional Requirements
 *   This function is used to set apl gain setting of mixed AI Objects.
 *   The SoC supports face, depth, light, logo object detection.
 *   Those objects are mixed to create one APL map.
 *   The APL map is used for high contrast BPL in local dimming.
 *   Because RGB local dimming ic is located outside SoC,
 *   the apl map should be read from SoC and then transmitted to RGB local dimming ic.
 *
 * Functions & Parameters
 *     .. code-block:: cpp
 *
 *       //
 *       // ioctl command
 *       //
 *       VIDIOC_G_EXT_CTRLS/VIDIOC_S_EXT_CTRLS
 *
 *       //
 *       // control id
 *       //
 *       V4L2_CID_EXT_VBE_OBJECT_APL_GAIN
 *
 *       //
 *       // parameter
 *       //
 *       enum v4l2_ext_vbe_object_detection_id {
 *           V4L2_EXT_VBE_OBJECT_DETECTION_ID_FACE = 0x01,
 *           V4L2_EXT_VBE_OBJECT_DETECTION_ID_DEPTH = 0x02,
 *           V4L2_EXT_VBE_OBJECT_DETECTION_ID_LIGHT = 0x04,
 *           V4L2_EXT_VBE_OBJECT_DETECTION_ID_LOGO = 0x08,
 *       };
 *
 *       struct v4l2_ext_vbe_object_apl_gain {
 *           v4l2_ext_vbe_object_detection_id id;
 *           unsigned char enable;
 *           unsigned char master_gain;
 *           unsigned char gain_x[4];
 *           unsigned char gain_y[4];
 *       };
 *
 * Return Value
 *     On success 0 is returned.
 *     On error -1 and the errno is set appropriately. The generic error
 *     codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *     Application can set data using VIDIOC_S_EXT_CTRLS and this control id.
 *
 * Example
 *     .. code-block:: cpp
 *
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     v4l2_ext_vbe_object_apl_gain apl_gain;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&apl_gain, 0, sizeof(struct v4l2_ext_vbe_object_apl_gain));
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_OBJECT_APL_GAIN;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_object_apl_gain);
 *     ext_controls.controls->ptr = (void *)&apl_gain;
 *
 *     ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */
#define V4L2_CID_EXT_VBE_OBJECT_APL_GAIN  (V4L2_CID_EXT_VBE_BASE + 51)


 /**
 * @brief Get mixed AI Object APL map for Local Dimming
 *
 * @rst
 * Functional Requirements
 *   This function is used to get apl map of mixed AI Objects.
 *   The SoC supports face, depth, light, logo object detection.
 *   Those objects are mixed to create one APL map.
 *   The APL map is used for high contrast BPL in local dimming.
 *   Because RGB local dimming ic is located outside SoC,
 *   the apl map should be read from SoC and then transmitted to RGB local dimming ic.
 *
 * Functions & Parameters
 *     .. code-block:: cpp
 *
 *       //
 *       // ioctl command
 *       //
 *       VIDIOC_G_EXT_CTRLS
 *
 *       //
 *       // control id
 *       //
 *       // You have to make the new control id as the below.
 *       V4L2_CID_EXT_VBE_OBJECT_APL
 *
 *       //
 *       // parameter
 *       //
 *       enum v4l2_ext_vbe_object_detection_id {
 *           V4L2_EXT_VBE_OBJECT_DETECTION_ID_FACE = 0x01,
 *           V4L2_EXT_VBE_OBJECT_DETECTION_ID_DEPTH = 0x02,
 *           V4L2_EXT_VBE_OBJECT_DETECTION_ID_LIGHT = 0x04,
 *           V4L2_EXT_VBE_OBJECT_DETECTION_ID_LOGO = 0x08,
 *       };
 *
 *       struct v4l2_ext_vbe_object_apl {
 *         unsigned int detection_flag; // bitwise values of v4l2_ext_vbe_object_detection_id
 *         unsigned char apl[80][40];
 *       };
 *
 * Return Value
 *     On success 0 is returned.
 *     On error -1 and the errno is set appropriately. The generic error
 *     codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *     Application can get data using VIDIOC_G_EXT_CTRLS and this control id.
 *
 * Example
 *     .. code-block:: cpp
 *
 *     struct v4l2_ext_controls ext_controls;
 *     struct v4l2_ext_control ext_control;
 *     v4l2_ext_vbe_object_apl apl;
 *
 *     memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *     memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *     memset(&apl, 0, sizeof(struct v4l2_ext_vbe_object_apl));
 *
 *     ext_controls.ctrl_class = V4L2_CTRL_CLASS_USER;
 *     ext_controls.count = 1;
 *     ext_controls.controls = &ext_control;
 *     ext_controls.controls->id = V4L2_CID_EXT_VBE_OBJECT_APL;
 *     ext_controls.controls->size = sizeof(struct v4l2_ext_vbe_object_apl);
 *     ext_controls.controls->ptr = (void *)&apl;
 *
 *     ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 *
 * @endrst
 */

#define V4L2_CID_EXT_VBE_OBJECT_APL (V4L2_CID_EXT_VBE_BASE + 52)


#define V4L2_CID_EXT_ID_VBE_BASE (V4L2_CID_USER_EXT_ID_VBE_BASE)

struct v4l2_ext_vbe_ucr_lut
{
	unsigned int on_off; // 1: on 0: off
	union {
		unsigned short *posData; // position data
		unsigned int compat_data;
		unsigned long long sizer_data;
	};
	unsigned int poSize; // 2*16 position data size
	union {
		unsigned short *rgbTbl; // RGB table data
		unsigned int compat_data_tlb;
		unsigned long long sizer_tlb;
	};
	unsigned int tblSize;   // 2*24*16*16 RGB table data size
};

/**
 * output framerate control tbl
**/
struct v4l2_ext_vbe_frame_rate {

	unsigned int on_off; 	 /*- 0 : freeRun Off
							   - 1 : freeRun On
							   - 10 ~ 130 : Variable Value (+-1% of 60 Hz)
							   - 10 : 59.40 Hz
							   - 11 : 59.41 Hz
							   - ...
							   - 69 : 59.99Hz
							   - 70 : 60 Hz
							   - 71 : 60.01Hz
							   - ...
							   - 130 : 60.60Hz
							   */
    unsigned char frameRate; //50Hz or 60Hz etc.
};

/**
 *  GENLOCK set
**/
struct v4l2_ext_set_vbe_genlock {
unsigned int genlock;    // [BIT 0] Genlock 0 = Off, 1 = On
                         // [BIT 1~12] Phase Shift  (0x0 ~ 0xFFF)
};

// when Genlock:Off, Phase Shift: 0         -> Off
// when Genlock:Off, Phase shift: 1~0xfff    -> On
// when Genlock:On,  Phase shift: 0            -> On
// when Genlock:On,  Phase shift: 1~0xfff    -> On


/**
 * GENLOCK get
**/
struct v4l2_ext_get_vbe_genlock {
unsigned int genlock_status;
// [BIT 0~3] :   V4L2_EXT_VBE_GENLOCK_SYNC_STATUS
// [BIT 4~7] :   V4L2_EXT_VBE_GENLOCK_FRAMERATE
// [BIT 8~19]: genlock_Status_Phase (0~4095) (4095 = 1 Frame diff, 2047 = 0.5 Frame)
};

enum V4L2_EXT_VBE_GENLOCK_SYNC_STATUS {
  V4L2_EXT_VBE_GENLOCK_OFF,
  V4L2_EXT_VBE_GENLOCK_NO_SYNC,    // No Signal
  V4L2_EXT_VBE_GENLOCK_ON_SYNC,    // On Signal
  V4L2_EXT_VBE_GENLOCK_LOCK_DONE,  // Lock is done
  V4L2_EXT_VBE_GENLOCK_FREERUN,
  V4L2_EXT_VBE_GENLOCK_STATUS_RESERVED_1,
  V4L2_EXT_VBE_GENLOCK_STATUS_RESERVED_2,
  V4L2_EXT_VBE_GENLOCK_STATUS_MAX,
};

enum V4L2_EXT_VBE_GENLOCK_FRAMERATE {
  V4L2_EXT_VBE_GENLOCK_24,
  V4L2_EXT_VBE_GENLOCK_25,
  V4L2_EXT_VBE_GENLOCK_30,
  V4L2_EXT_VBE_GENLOCK_50,
  V4L2_EXT_VBE_GENLOCK_60,
  V4L2_EXT_VBE_GENLOCK_100,
  V4L2_EXT_VBE_GENLOCK_120,
  V4L2_EXT_VBE_GENLOCK_UNKNOWN,
  V4L2_EXT_VBE_GENLOCK_FRAMERATE_MAX,
};

/* UCR */
/* control uniformity compensatiion block for V4L2_CID_EXT_ID_VBE_UCR_DATA */

/**
 * @brief Struct for uniformity compensatiion block info
 *
 * @rst
 * Functional Requirements
 *   For signage.
 *   This function is used to control uniformity compensatiion block.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *
 *   +------------------------+-------------------------------------------------+
 *   | Variable               | Return Value                                    |
 *   +========================+=================================================+
 *   | on_off                 | - 0: Off(bypass ucr block)                      |
 *   |                        | - 1: On(use ucr block)                          |
 *   +------------------------+-------------------------------------------------+
 *   | posData                | position data                                   |
 *   +------------------------+-------------------------------------------------+
 *   | compat_data            | match to other data                             |
 *   +------------------------+-------------------------------------------------+
 *   | sizer_data             | match to other data                             |
 *   +------------------------+-------------------------------------------------+
 *   | poSize                 | position data size                              |
 *   +------------------------+-------------------------------------------------+
 *   | rgbTbl                 | RGB table data                                  |
 *   +------------------------+-------------------------------------------------+
 *   | compat_data_tlb        | match to other data                             |
 *   +------------------------+-------------------------------------------------+
 *   | sizer_tlb              | match to other data                             |
 *   +------------------------+-------------------------------------------------+
 *   | tblSize                | RGB table data size                             |
 *   +------------------------+-------------------------------------------------+
 *
 *   .. code-block:: cpp
 *
 *      //
 *      // ioctl command
 *      //
 *      VIDIOC_S_EXT_CTRLS
 *
 *      //
 *      // control id
 *      //
 *      // You have to make the new control id as the below.
 *      V4L2_CID_EXT_ID_VBE_UCR_DATA
 *
 *      //
 *      // parameter
 *      //
 *      struct v4l2_ext_vbe_ucr_lut {
 *      unsigned int on_off; // 1: on 0: off
 *      union {
 *        unsigned short *posData; // position data
 *        unsigned int compat_data;
 *        unsigned long long sizer_data;
 *      };
 *      unsigned int poSize; // 2*16 position data size
 *      union {
 *        unsigned short *rgbTbl; // RGB table data
 *        unsigned int compat_data_tlb;
 *        unsigned long long sizer_tlb;
 *      };
 *      unsigned int tblSize;	 // 2*24*16*16 RGB table data size
 *      };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *	 Application can set data using v4l2_ext_controls and this control id.
 *
 * Example
 *   .. code-block:: c
 *
 *      struct v4l2_ext_vbe_ucr_lut ucrData;
 *
 *      ucrData.on_off = bOnOff;
 *      ucrData.posData = &uUcrData[0];
 *      ucrData.poSize = UCR_POSITION_SIZE;
 *      ucrData.rgbTbl = &uUcrData[UCR_POSITION_SIZE];
 *      ucrData.tblSize = UCR_LUT_SIZE;
 *
 *      struct v4l2_ext_vbe_cmn_data pqData;
 *
 *      pqData.version = 1;
 *      pqData.length = sizeof(struct v4l2_ext_vbe_ucr_lut);
 *      pqData.wid = 0;	 // main
 *      pqData.p_data = (unsigned char*)&ucrData;
 *
 *      ret = (TVCO_RESULT_T)pq_v4l2_setExtCtrls(V4L2_CID_EXT_ID_VBE_UCR_DATA, (void *)&pqData);
 *
 * See also
 *   - :cpp:any:`v4l2_ext_vbe_ucr_lut`
 *
 * @endrst
 */
#define V4L2_CID_EXT_ID_VBE_UCR_DATA (V4L2_CID_EXT_ID_VBE_BASE + 0)

//
// framerate control ID
//
/**
 * @brief
 *   Commercial TV has models for broadcast stations.
 *   To fix the problem of screen dripping when shooting the display with a station camera.
 *   To change the output resolution to match the camera frequency in FreeRun mode.
 *
 * @rst
 * Functional Requirements
 *   This function is for setting freerun/lock mode and fine tuning V frequency.
 *   frameRate setting should only work if free-run mode is set to on.
 *   Once set, framerate output changes should be persisted.
 *   (In first implementation, the output changed depending on the external input frequency.)
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *    //
 *    // ioctl command
 *    //
 *    VIDIOC_S_EXT_CTRLS
 *    VIDIOC_G_EXT_CTRLS
 *
 *    //
 *    // control id
 *    //
 *    // You have to make the new control id as the below.
 *    V4L2_CID_EXT_ID_VBE_FRAME_RATE
 *
 *    //
 *    // parameter
 *    //
 *    struct v4l2_ext_vbe_frame_rate {
 *   unsigned int on_off;
 *   unsigned char frameRate;  //50Hz or 60Hz etc.
 *		};
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *   Application can set parameter using VIDIOC_S_EXT_CTRLS and this control
 *   Application can get parameter using VIDIOC_G_EXT_CTRLS and this control
 *
 * Example
 *   .. code-block:: cpp
 *
 *    int fd = _gFdVBE;
 *		struct v4l2_ext_controls ext_controls;
 *		struct v4l2_ext_vbe_frame_rate frame_rate_data;
 *
 *		memset(&ext_controls, 0, sizeof(struct v4l2_ext_controls));
 *		memset(&frame_rate_data, 0, sizeof(struct v4l2_ext_vbe_frame_rate));
 *
 *		frame_rate_data.on_off  = isFroceFreenRun;
 *		frame_rate_data.frameRate= frameRate;
 *
 *		ext_controls.ctrl_class       = V4L2_CTRL_CLASS_USER;
 *		ext_controls.count            = 1;
 *		ext_controls.controls         = &ext_control;
 *		ext_controls.controls->id     = V4L2_CID_EXT_ID_VBE_FRAME_RATE;
 *		ext_controls.controls->size   = sizeof(struct v4l2_ext_vbe_frame_rate);
 *		ext_controls.controls->string = (char *)&frame_rate_data;
 *
 *		//Send Parameter to SoC
 *		ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *		//Read Parameter from SoC
 *		ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_ID_VBE_FRAME_RATE (V4L2_CID_EXT_ID_VBE_BASE + 1)

//
// Set Genlock / Get Genlock Status
//
/**
 * @brief
 *   Virture Production Model Only.
 *   Genlock is used to synchronize videooutput with other sources.
 *
 * @rst
 * Functional Requirements
 *   V4L2_CID_EXT_ID_VBE_SET_GENLOCK
 *     This function is used to set genlock & phaseshift.
 *   V4L2_CID_EXT_ID_VBE_GET_GENLOCK
 *     This function is used to get genlock status, framerate, frame diff.
 *
 * Responses to abnormal situations, including
 *   None.
 *
 * Performance Requirements
 *   It should be returned within 10 msec.
 *
 * Constraints
 *   None.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *       //
 *       // ioctl command
 *       //
 *       VIDIOC_S_EXT_CTRLS
 *          - V4L2_CID_EXT_ID_VBE_SET_GENLOCK
 *       VIDIOC_G_EXT_CTRLS
 *          - V4L2_CID_EXT_ID_VBE_GET_GENLOCK
 *
 *       //
 *       // control id
 *       //
 *       // You have to make the new control id as the below.
 *       V4L2_CID_EXT_ID_VBE_SET_GENLOCK
 *       V4L2_CID_EXT_ID_VBE_GET_GENLOCK
 *
 *      //
 *      // parameter
 *      //
 *      struct v4l2_ext_set_vbe_genlock {
 *          unsigned int genlock;   // [BIT 0] Genlock 0 = Off, 1 = On
 *                                  // [BIT 1~12] Phase Shift  (0x0 ~ 0xFFF)
 *      };
 *      struct v4l2_ext_get_vbe_genlock {
 *          unsigned int genlock_status;
 *                  // [BIT 0~3] :   V4L2_EXT_VBE_GENLOCK_SYNC_STATUS
 *                  // [BIT 4~7] :   V4L2_EXT_VBE_GENLOCK_FRAMERATE
 *                  // [BIT 8~19]: genlock_Status_Phase (0~4095) (4095 = 1 Frame diff, 2047 = 0.5 Frame)
 *      };
 *      enum V4L2_EXT_VBE_GENLOCK_SYNC_STATUS {
 *          V4L2_EXT_VBE_GENLOCK_OFF,
 *          V4L2_EXT_VBE_GENLOCK_NO_SYNC,    // No Signal
 *          V4L2_EXT_VBE_GENLOCK_ON_SYNC,    // On Signal
 *          V4L2_EXT_VBE_GENLOCK_LOCK_DONE,  // Lock is done
 *          V4L2_EXT_VBE_GENLOCK_FREERUN,
 *          V4L2_EXT_VBE_GENLOCK_STATUS_RESERVED_1,
 *          V4L2_EXT_VBE_GENLOCK_STATUS_RESERVED_2,
 *          V4L2_EXT_VBE_GENLOCK_STATUS_MAX,
 *      };
 *      enum V4L2_EXT_VBE_GENLOCK_FRAMERATE {
 *          V4L2_EXT_VBE_GENLOCK_24,
 *          V4L2_EXT_VBE_GENLOCK_25,
 *          V4L2_EXT_VBE_GENLOCK_30,
 *          V4L2_EXT_VBE_GENLOCK_50,
 *          V4L2_EXT_VBE_GENLOCK_60,
 *          V4L2_EXT_VBE_GENLOCK_100,
 *          V4L2_EXT_VBE_GENLOCK_120,
 *          V4L2_EXT_VBE_GENLOCK_UNKNOWN,
 *          V4L2_EXT_VBE_GENLOCK_FRAMERATE_MAX,
 *      };
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error -1 and the errno variable is set appropriately.
 *   The generic error codes are described at the :ref:`gen_errors` chapter.
 *
 * Control Type
 *       Application can set data using v4l2_ext_controls and this control id.
 *
 * Example
 *   .. code-block:: cpp
 *   *V4L2_CID_EXT_ID_VBE_SET_GENLOCK
 *      struct v4l2_ext_controls ext_controls;
 *      struct v4l2_ext_control ext_control;
 *      struct v4l2_ext_set_vbe_genlock vbe_genlock;
 *
 *      memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *      memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *      memset(&vbe_genlock, 0, sizeof(struct v4l2_ext_set_vbe_genlock ));
 *
 *      vbe_genlock.genlock  = (123 << 1) | 1; //phase shift : 123, genlock on
 *
 *      ext_controls.ctrl_class       = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count            = 1;
 *      ext_controls.controls         = &ext_control;
 *      ext_controls.controls->id     = V4L2_CID_EXT_ID_VBE_SET_GENLOCK;
 *      ext_controls.controls->size   = sizeof(struct v4l2_ext_set_vbe_genlock);
 *      ext_controls.controls->string = (char *)&vbe_genlock;
 *
 *      ret = ioctl(fd, VIDIOC_S_EXT_CTRLS, &ext_controls);
 *
 *   *V4L2_CID_EXT_ID_VBE_GET_GENLOCK
 *      struct v4l2_ext_controls ext_controls;
 *      struct v4l2_ext_control ext_control;
 *      struct v4l2_ext_get_vbe_genlock vbe_genlock;
 *
 *      memset(&ext_controls, 0, sizeof(v4l2_ext_controls));
 *      memset(&ext_control, 0, sizeof(v4l2_ext_control));
 *      memset(&vbe_genlock, 0, sizeof(struct v4l2_ext_get_vbe_genlock ));
 *
 *      ext_controls.ctrl_class       = V4L2_CTRL_CLASS_USER;
 *      ext_controls.count            = 1;
 *      ext_controls.controls         = &ext_control;
 *      ext_controls.controls->id     = V4L2_CID_EXT_ID_VBE_GET_GENLOCK;
 *      ext_controls.controls->size   = sizeof(struct v4l2_ext_get_vbe_genlock);
 *      ext_controls.controls->string = (char *)&vbe_genlock;
 *
 *      ret = ioctl(fd, VIDIOC_G_EXT_CTRLS, &ext_controls);
 * @endrst
 */
#define V4L2_CID_EXT_ID_VBE_SET_GENLOCK (V4L2_CID_EXT_ID_VBE_BASE + 2)
#define V4L2_CID_EXT_ID_VBE_GET_GENLOCK (V4L2_CID_EXT_ID_VBE_BASE + 3)

// clang-format on
#endif // _V4L2_EXT_PANEL_H
