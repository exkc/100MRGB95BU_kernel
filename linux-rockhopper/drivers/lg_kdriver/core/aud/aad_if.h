/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

#ifndef _AAD_IF_H_
#define _AAD_IF_H_

#include "base_types.h"
#include "kaimc.h"
#include "module/adec_module_list.h"    ///< ADEC_CORE_ARM
#include "common/module/uid.h"  ///< AUD_MODID_REGISTRY ()
#include "block.h"
#include "block_manager.h"
#include "input.h"

/**
 * HAL AUDIO Country Type for initialize.
 * @SIF_TYPE_NONE: NONE
 * @SIF_ATSC_SELECT: TV Systems for A2 enabled in default ATSC system
 * @SIF_KOREA_A2_SELECT: TV Systems for A2 enabled in Korea A2 system
 * @SIF_BTSC_SELECT: TV Systems for BTSC enabled in ATSC(CO, CF) or DVB(Taiwan) system
 * @SIF_BTSC_BR_SELECT: TV Systems for BTSC enabled in ATSC(Brazil) system
 * @SIF_BTSC_US_SELECT: TV Systems for BTSC enabled in ATSC(US) system
 * @SIF_DVB_SELECT: TV Systems for EU in default DVB system
 * @SIF_DVB_ID_SELECT: TV Systems for ID(Indonesia) in DVB(PAL B/G) system
 * @SIF_DVB_IN_SELECT: TV Systems for IN(India) in DVB(PAL B) system
 * @SIF_DVB_CN_SELECT: TV Systems for CN(China, Hong Kone) in DVB system
 * @SIF_DVB_AJJA_SELECT: TV Systems for AJ(Asia JooDong), JA(JooAang Asia) ian DVB system
 * @SIF_TYPE_MAX: MAX
 */
typedef enum
{
    LX_AAD_TYPE_NONE           = 0x0000,
    LX_AAD_ATSC_SELECT         = 0x0001,
    LX_AAD_KOREA_A2_SELECT     = 0x0002,
    LX_AAD_BTSC_SELECT         = 0x0004,
    LX_AAD_BTSC_BR_SELECT      = 0x0008,
    LX_AAD_BTSC_US_SELECT      = 0x0010,
    LX_AAD_DVB_SELECT          = 0x0020,
    LX_AAD_DVB_ID_SELECT       = 0x0040,
    LX_AAD_DVB_IN_SELECT       = 0x0080,
    LX_AAD_DVB_CN_SELECT       = 0x0100,
    LX_AAD_DVB_AJJA_SELECT     = 0x0200,
    LX_AAD_TYPE_MAX            = 0xFFFF,
} LX_AAD_COUNTRY_EXT_TYPE_T;

/**
 * AAD Init Module Type.
 * AAD Init Module Type is defined.\n
 * If type is LX_AAD_INIT_TYPE_NONE, AAD is set to default mode.
 *
 */
typedef  enum
{
    LX_AAD_INIT_TYPE_NONE           = 0,        ///< INIT TYPE : NONE
    LX_AAD_INIT_ATSC_A2_SELECT      = 1,        ///< INIT TYPE : TV Systems for A2 enabled in ATSC system
    LX_AAD_INIT_ATSC_BTSC_SELECT    = 2,        ///< INIT TYPE : TV Systems for BTSC enabled in ATSC(US, Brazil, CO, CF) or DVB(Taiwan) system
    LX_AAD_INIT_DVB_SELECT          = 3,        ///< INIT TYPE : TV Systems for EU in DVB system
    LX_AAD_INIT_DVB_ID_SELECT       = 4,        ///< INIT TYPE : TV Systems for ID(Indonesia) in DVB(PAL B/G) system
    LX_AAD_INIT_DVB_IN_SELECT       = 5,        ///< INIT TYPE : TV Systems for IN(India) in DVB(PAL B) system
    LX_AAD_INIT_DVB_CN_SELECT       = 6,        ///< INIT TYPE : TV Systems for CN(China) in DVB system
    LX_AAD_INIT_DVB_AJJA_SELECT     = 7,        ///< INIT TYPE : TV Systems for AJJA in DVB(PAL, NTSC M/N) system
    LX_AAD_INIT_TYPE_MAX                        ///< INIT TYPE : MAX
} LX_AAD_INIT_TYPE_T;

/**
 * AAD SIF High Deviation Level.
 * This enumeration describes the SIF High Deviation Level for analog audio decoder.
 *
 */
typedef  enum
{
    LX_AAD_HIGH_DEV_LEVEL_OFF   = 0,        ///< High Deviation OFF(50KHz)
    LX_AAD_HIGH_DEV_LEVEL_1     = 1,        ///< High Deviation Level 1(100KHz)
    LX_AAD_HIGH_DEV_LEVEL_2     = 2,        ///< High Deviation Level 2(200KHz)
    LX_AAD_HIGH_DEV_LEVEL_3     = 3,        ///< High Deviation Level 3(384KHz)
    LX_AAD_HIGH_DEV_LEVEL_4     = 4         ///< High Deviation Level 4(540KHz)
} LX_AAD_HIGH_DEV_LEVEL_T;

/**
 * AAD SIF Sound System.
 * SIF Sound System is defined.
 *
 */
typedef  enum
{
    LX_AAD_SIF_SYSTEM_BG        = 0x00,     ///< BG
    LX_AAD_SIF_SYSTEM_I         = 0x01,     ///< I
    LX_AAD_SIF_SYSTEM_DK        = 0x02,     ///< DK
    LX_AAD_SIF_SYSTEM_L         = 0x03,     ///< L
    LX_AAD_SIF_SYSTEM_MN        = 0x04,     ///< MN
    LX_AAD_SIF_SYSTEM_UNKNOWN   = 0xF0,     ///< UNKNOWN
    LX_AAD_SIF_SYSTEM_ERROR     = 0xFF      ///< ERROR
} LX_AAD_SIF_SOUNDSYSTEM_T;

/**
 * AAD SIF Sound Standard.
 * SIF Sound Standard is defined.
 *
 */
typedef enum
{
    LX_AAD_SIF_MODE_DETECT      = 0,        ///< MODE DETECT
    LX_AAD_SIF_BG_NICAM         = 1,        ///< BG NICAM
    LX_AAD_SIF_BG_FM            = 2,        ///< BG FM
    LX_AAD_SIF_BG_A2            = 3,        ///< BG A2
    LX_AAD_SIF_I_NICAM          = 4,        ///< I NICAM
    LX_AAD_SIF_I_FM             = 5,        ///< I FM
    LX_AAD_SIF_DK_NICAM         = 6,        ///< DK NICAM
    LX_AAD_SIF_DK_FM            = 7,        ///< DK FM
    LX_AAD_SIF_DK1_A2           = 8,        ///< DK1 A2
    LX_AAD_SIF_DK2_A2           = 9,        ///< DK2 A2
    LX_AAD_SIF_DK3_A2           = 10,       ///< DK3 A2
    LX_AAD_SIF_L_NICAM          = 11,       ///< L NICAM
    LX_AAD_SIF_L_AM             = 12,       ///< L AM
    LX_AAD_SIF_MN_A2            = 13,       ///< MN A2
    LX_AAD_SIF_MN_BTSC          = 14,       ///< MN BTSC
    LX_AAD_SIF_MN_EIAJ          = 15,       ///< MN EIAJ
    LX_AAD_SIF_NUM_SOUND_STD    = 16        ///< NUMBER OF SOUND STANDARD
} LX_AAD_SIF_STANDARD_T;

/**
 * AAD SET SIF Analog Audio SAP(Secondary Audio Program) Mode.
 * This enumeration contains the setting parameters of analog audio SAP mode.
 *
 */
typedef enum
{
    LX_ATV_SET_PAL_MONO                 =   0x00,   ///< PAL Mono
    LX_ATV_SET_PAL_MONO_FORCED          =   0x01,   ///< PAL Mono Force Mono
    LX_ATV_SET_PAL_STEREO               =   0x02,   ///< PAL Stereo
    LX_ATV_SET_PAL_STEREO_FORCED        =   0x03,   ///< PAL Stereo Force Mono
    LX_ATV_SET_PAL_DUALI                =   0x04,   ///< PAL Dual I
    LX_ATV_SET_PAL_DUALII               =   0x05,   ///< PAL Dual II
    LX_ATV_SET_PAL_DUALI_II             =   0x06,   ///< PAL Dual I+II
    LX_ATV_SET_PAL_NICAM_MONO           =   0x07,   ///< PAL NICAM Mono
    LX_ATV_SET_PAL_NICAM_MONO_FORCED    =   0x08,   ///< PAL NICAM Mono Force Mono
    LX_ATV_SET_PAL_NICAM_STEREO         =   0x09,   ///< PAL NICAM Stereo
    LX_ATV_SET_PAL_NICAM_STEREO_FORCED  =   0x0A,   ///< PAL NICAM Stereo Force Mono
    LX_ATV_SET_PAL_NICAM_DUALI          =   0x0B,   ///< PAL NICAM Dual I
    LX_ATV_SET_PAL_NICAM_DUALII         =   0x0C,   ///< PAL NICAM Dual II
    LX_ATV_SET_PAL_NICAM_DUALI_II       =   0x0D,   ///< PAL NICAM Dual I+II
    LX_ATV_SET_PAL_NICAM_DUAL_FORCED    =   0x0E,   ///< PAL NICAM Dual Forced Mono(Not Supported)
    LX_ATV_SET_PAL_UNKNOWN              =   0x0F,   ///< PAL Unkown State
    LX_ATV_SET_NTSC_A2_MONO             =   0x10,   ///< NTSC(A2) Mono
    LX_ATV_SET_NTSC_A2_STEREO           =   0x11,   ///< NTSC(A2) Stereo
    LX_ATV_SET_NTSC_A2_SAP              =   0x12,   ///< NTSC(A2) SAP
    LX_ATV_SET_NTSC_A2_UNKNOWN          =   0x13,   ///< NTSC(A2) Unkown State
    LX_ATV_SET_NTSC_BTSC_MONO           =   0x14,   ///< NTSC(BTSC) Mono
    LX_ATV_SET_NTSC_BTSC_STEREO         =   0x15,   ///< NTSC(BTSC) Stereo
    LX_ATV_SET_NTSC_BTSC_SAP_MONO       =   0x16,   ///< NTSC(BTSC) SAP Mono
    LX_ATV_SET_NTSC_BTSC_SAP_STEREO     =   0x17,   ///< NTSC(BTSC) SAP Stereo
    LX_ATV_SET_NTSC_BTSC_UNKNOWN        =   0x18,   ///< NTSC(BTSC) Unkown State
    LX_ATV_SET_ERROR                    =   0x19    ///< ERROR
} LX_ATV_AUDIO_MODE_SET_T;

/**
 * AAD SIF Mono/Stereo/SAP Detection Threshold Value.
 * aad ioctl parameter.
 * @see AAD_IOW_SIF_SET_THRESHOLD_LEVEL, AAD_IOR_SIF_GET_THRESHOLD_LEVEL
*/
typedef struct LX_AAD_SIF_THRESHOLD{
    UINT8       stereoIDMagHigh;        ///< The high threshold of stereo ID magnitude
    UINT8       stereoIDMagLow;         ///< The low threshold of stereo ID magnitude
} LX_AAD_SIF_THRESHOLD_T;

/**
 * AAD SIF available Sound Standard at all and D/K system.
 * SIF available standard is defined.
 *
 */
typedef  enum
{
    LX_AAD_SIF_NICAM                    = 0,    ///< NICAM
    LX_AAD_SIF_A2                       = 1,    ///< A2(all system)
    LX_AAD_SIF_FM                       = 2,    ///< FM : Mono
    LX_AAD_SIF_DETECTING_AVALIBILITY    = 3,    ///< On detecting availability.
    LX_AAD_SIF_A2_DK1                   = 11,   ///< A2 in DK1 only(added for DDI_ADEC_SIF_CheckA2DK)
    LX_AAD_SIF_A2_DK2                   = 12,   ///< A2 in DK2 only(added for DDI_ADEC_SIF_CheckA2DK)
    LX_AAD_SIF_A2_DK3                   = 13,   ///< A2 in DK3 only(added for DDI_ADEC_SIF_CheckA2DK)
    LX_AAD_SIF_NOT_AVAILE               = 20    ///< Not Availe
} LX_AAD_SIF_AVAILE_STANDARD_T;

/**
 * AAD SIF Existence Info.
 * SIF existence information is defined..
 *
 */
typedef  enum
{
    LX_AAD_SIF_ABSENT               = 0,    ///< SIF is absent.
    LX_AAD_SIF_PRESENT              = 1,    ///< SIF is present.
    LX_AAD_SIF_DETECTING_EXSISTANCE = 2     ///< On detecting existence.
} LX_AAD_SIF_EXISTENCE_INFO_T;

/**
 * AAD GET SIF Analog Audio SAP(Secondary Audio Program) Mode.
 * This enumeration contains the current state of analog audio SAP mode.
 *
 */
typedef enum
{
    LX_ATV_GET_PAL_MONO             =   0x00,   ///< PAL Mono
    LX_ATV_GET_PAL_STEREO           =   0x01,   ///< PAL Stereo
    LX_ATV_GET_PAL_DUAL             =   0x02,   ///< PAL Dual
    LX_ATV_GET_PAL_NICAM_MONO       =   0x03,   ///< PAL NICAM Mono
    LX_ATV_GET_PAL_NICAM_STEREO     =   0x04,   ///< PAL NICAM Stereo
    LX_ATV_GET_PAL_NICAM_DUAL       =   0x05,   ///< PAL NICAM Dual
    LX_ATV_GET_PAL_UNKNOWN          =   0x06,   ///< PAL Unkown State
    LX_ATV_GET_NTSC_A2_MONO         =   0x10,   ///< NTSC(A2) Mono
    LX_ATV_GET_NTSC_A2_STEREO       =   0x11,   ///< NTSC(A2) Stereo
    LX_ATV_GET_NTSC_A2_SAP          =   0x12,   ///< NTSC(A2) SAP
    LX_ATV_GET_NTSC_A2_UNKNOWN      =   0x13,   ///< NTSC(A2) Unkown State
    LX_ATV_GET_NTSC_BTSC_MONO       =   0x14,   ///< NTSC(BTSC) Mono
    LX_ATV_GET_NTSC_BTSC_STEREO     =   0x15,   ///< NTSC(BTSC) Stereo
    LX_ATV_GET_NTSC_BTSC_SAP_MONO   =   0x16,   ///< NTSC(BTSC) SAP Mono
    LX_ATV_GET_NTSC_BTSC_SAP_STEREO =   0x17,   ///< NTSC(BTSC) SAP Stereo
    LX_ATV_GET_NTSC_BTSC_UNKNOWN    =   0x18    ///< NTSC(BTSC) Unkown State
} LX_ATV_AUDIO_MODE_GET_T;

/**
 * AAD SIF High Deviation Set Info.
 * aad ioctl parameter.
 * @see AAD_IOW_SIF_SET_HIGH_DEV_MODE
*/
typedef struct LX_AAD_HIGH_DEV_SET{
    BOOLEAN                     bHighDevOnOff;      ///< The Status of High Deviation to setted
    LX_AAD_HIGH_DEV_LEVEL_T     highDevLevel;       ///< The Level of High Deviation to set
} LX_AAD_HIGH_DEV_SET_T;

/**
 * AAD SIF Sound System Detect Info.
 * aad ioctl parameter.
 * @see AAD_IORW_SIF_GET_BAND_DETECT
*/
typedef struct LX_AAD_SIF_SYSTEM_INFO{
    LX_AAD_SIF_SOUNDSYSTEM_T    setSystem;          ///< The SIF Band(B/G, I, DK, L, M) to set
    BOOLEAN                     bManualMode;        ///< The status of manual mode to detect sound system
    LX_AAD_SIF_SOUNDSYSTEM_T    detectedSystem;     ///< The SIF Band(B/G, I, DK, L, M) to be detected
    UINT32                      bandStrength;       ///< The quality of input signal for Carrier1
    UINT32                      bandMagnitude;      ///< The magnitude of input signal for Carrier1
} LX_AAD_SIF_SYSTEM_INFO_T;

/**
 * AAD SIF Sound Standard Detect Info.
 * aad ioctl parameter.
 * @see AAD_IORW_SIF_CHECK_SOUND_MODE
*/
typedef struct LX_AAD_SIF_STANDARD_INFO{
    LX_AAD_SIF_AVAILE_STANDARD_T    setStandard;        ///< The SIF Mode(NICAM, FM, A2) to set
    LX_AAD_SIF_AVAILE_STANDARD_T    detectedStandard;   ///< The SIF Mode(NICAM, FM, A2) to be detected
    LX_AAD_SIF_EXISTENCE_INFO_T     availability;       ///< The SIF Existence Info.
} LX_AAD_SIF_STANDARD_INFO_T;


#define SIF_AAD_ATSC_A2_ALL_MASK    (LX_AAD_ATSC_SELECT | LX_AAD_KOREA_A2_SELECT)
#define SIF_AAD_BTSC_ALL_MASK       (LX_AAD_BTSC_SELECT | LX_AAD_BTSC_BR_SELECT | LX_AAD_BTSC_US_SELECT)

/**
 * Audio device information
*/
struct aud_dev_info
{
    int            dev;         // device id
};
typedef struct aud_dev_info AUD_DEV_INFO_T;

/**
 * SIF AUDIO Device Information.
 */
typedef struct
{
    BOOLEAN                     connected;

    LX_AAD_SIF_SOUNDSYSTEM_T    detectsoundsystem;
    LX_AAD_SIF_SOUNDSYSTEM_T    detectedsoundsystem;
    SINT32                      band_strength;

    LX_AAD_COUNTRY_EXT_TYPE_T   countryext;
    LX_AAD_SIF_SOUNDSYSTEM_T    soundsystem;

    LX_AAD_SIF_STANDARD_T       setsoundstandard;
    LX_AAD_SIF_STANDARD_T       getsoundstandard;

    LX_ATV_AUDIO_MODE_GET_T     getaudiomode;
    LX_ATV_AUDIO_MODE_SET_T     setaudiomode;

    SINT32                      sifstatus;

    SINT32                      hdevlevel;
    SINT32                      a2thdlevel;
} SIF_DEVICE_T;

/**
 * Analog Audio Decoder Information.
 */
struct aud_aad_info
{
    struct aud_block_info *input_info;
    int                   uid;
    int                   event_id;

    bool                  is_resumed;
};


SINT32 AUDIO_SuspendAad (void);
SINT32 AUDIO_ResumeAad (bool set_is_drop);
SINT32 AUDIO_RestartAad (bool set_audio_mode);
SIF_DEVICE_T *kcontrol_sif_open (void);
SINT32 kcontrol_sif_close (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_detectsoundsystem (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_bandsetup (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_standardsetup (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_getsoundstandard (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_curanalogmode (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_useranalogmode (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_sifexist (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_hdevlevel (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_a2thresholdlevel (SIF_DEVICE_T * sif_dev);
SINT32 kcontrol_sif_set_data_drop (SIF_DEVICE_T * sif_dev, bool on_off);

#endif /* _AAD_IF_H_ */
