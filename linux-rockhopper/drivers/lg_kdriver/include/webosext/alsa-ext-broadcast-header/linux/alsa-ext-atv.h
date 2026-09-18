/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_ATV_H
#define _ALSA_EXT_ATV_H

/**
 * @brief AAD device open
 *
 * @rst
 * Functional Requirements
 *   priority : 2
 *
 *   This function opens the AAD (ATV) to be used in the PATH. After opening, it
 *   can be connected to ATV by "Sif Connect". An opened AAD can be connected to
 *   ADEC by the "Sif Connect" function and become an ADEC input. If you try to
 *   open an already opened AAD without closing it, it returns NOT_OK without
 *   action.
 *
 * Functions & Parameters
 *   param[in] notUsed int (dummy),
 *
 *   param[out] openStatus int return open status (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Sif Open
 *      }

 *      sif_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Get Sif Open Status
 *          ucontrol->value.integer.value[1] = OnOff;
 *      }
 *
 * @endrst
 */
#define SIF_OPEN "Sif Open"

/**
 * @brief AAD device close
 *
 * @rst
 *
 * Functional Requirements
 *   priority : 2
 *
 *   If this function is called when the AAD is not open or in the connect state,
 *   it returns NOT_OK without action.
 *
 *
 * Functions & Parameters
 *   param[in] notUsed int, (dummy)
 *
 *   param[out] closeStatus int return close status (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value
 *      *ucontrol)
 *      {
 *           // Sif Close
 *      }
 *
 *      sif_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value
 *      *ucontrol)
 *      {
 *           // Get Sif Close Status
 *           ucontrol->value.integer.value[1] = OnOff;
 *      }
 *
 * @endrst
 */
#define SIF_CLOSE "Sif Close"

/**
 * @brief AAD device connect
 * @rst
 *
 * Functional Requirements
 *   priority : 2
 *
 *   Connect AAD to ADEC to supply data. The connected AAD is disconnected by "Sif
 *   Disconnect".
 *
 * Functions & Parameters
 *   param[in] default:1, 0 is atv internal demod, 1 is atv external demod
 *
 *   param[out] connectStatus int return connect status (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_connect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *           // Sif Connect
 *      }
 *      sif_connect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *           // Get Sif Connect Status
 *           ucontrol->value.integer.value[1] = OnOff;
 *      }
 *
 * @endrst
 */
#define SIF_CONNECT "Sif Connect"

/**
 * @brief AAD device disconnect
 * @rst
 *
 * Functional Requirements
 *   priority : 2
 *
 *   Disconnect the AAD associated with ADEC. If disconnect is attempted without a
 *   connection, NOT_OK should be returned.
 *
 * Functions & Parameters
 *   param[in] notUsed int (dummy),
 *
 *   param[out] disconnectStatus int return disconnect status (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_disconnect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *           // Sif Connect
 *      }
 *      sif_disconnect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *           // Get Sif Connect Status
 *           ucontrol->value.integer.value[1] = OnOff;
 *      }
 *
 *
 * @endrst
 */
#define SIF_DISCONNECT "Sif Disconnect"

/**
 * sif soundsystem
 */
typedef enum sif_soundsystem_ext_type
{
    SIF_SYSTEM_UNKNOWN = 0x0000, /**< Can't found the Sound System */
    SIF_SYSTEM_BG = 0x0001,      /**< Sound System BG */
    SIF_SYSTEM_I = 0x0002,       /**< Sound System I */
    SIF_SYSTEM_DK = 0x0004,      /**< Sound System DK */
    SIF_SYSTEM_L = 0x0008,       /**< Sound System L */
    SIF_SYSTEM_MN = 0x0010,      /**< Sound System MN */
} sif_soundsystem_ext_type_t;

/**
 * @brief AAD detect sound system
 * @rst
 *
 * Functional Requirements
 *   priority : 2
 *
 *   Specifies the range of the sound system currently set in the input signal.
 *   Chip will automatically detect and set the system within the range. When
 *   calling the Get function, return the Detected Sound System to check the
 *   applied sound system.
 *
 *   For DetectSoundSystem_put, instead of actually setting the SoundSystem, it
 *   specifies the scope of the SoundSystem_get that will be returned. The
 *   boundary can be defined by | operations. And this function only works for
 *   DVB.
 *
 *   Flow -> Put : set soundsystem_boundary(ex SIF_SYSTEM_BG|SIF_SYSTEM_DK) -> Get
 *   : check sat sound system exist or not.
 *
 *   If the detected soundsystem, in the soundsystem_boundary, is under the driver
 *   threshold, then return SIF_SYSTEM_UNKNOWN. If not, return detected
 *   soundsystem.
 *
 * Functions & Parameters
 *   param[in] soundsystem_boundary sif_soundsystem_ext_type_t
 *
 *   param[out] check_soundsystem_exist sif_soundsystem_ext_type_t (default:0)
 *
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_detectsoundsystem_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Get sound system info
 *          sound_system = ucontrol->value.integer.value[0];
 *      }
 *      sif_detectsoundsystem_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Get sound system info
 *          ucontrol->value.integer.value[0] = sound_system;
 *      }
 *
 * @endrst
 */
#define SIF_DETECTSOUNDSYSTEM "Sif DetectSoundSystem"

/**
 * @brief Get Strength of Given Sound System.
 * @rst
 *
 * Functional Requirements
 *   priority : 2
 *
 * Functions & Parameters
 *   put_param sif_soundsystem_ext_type_t soundsystem (ex SIF_SYSTEM_BG),
 *   default_get 0,0
 *
 *   get_param sif_soundsystem_ext_type_t soundsystem,
 *   get_param int strength,
 *
 *   soundsystem of get_param should be same with soundsystem of put_param for error check
 *   minimum strength value is 0
 *
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 310ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * @endrst
 */
#define SIF_SOUNDSYSTEMSTRENGTH "Sif SoundSystemStrength"

/**
 * AUDIO Country Type for initialize.
 */
typedef enum sif_country_ext_type
{
    SIF_TYPE_NONE = 0x0000, /**< NONE */
    SIF_ATSC_SELECT =
        0x0001, /**< TV Systems for A2 enabled in default ATSC system */
    SIF_KOREA_A2_SELECT =
        0x0002, /**< TV Systems for A2 enabled in Korea A2 system */
    SIF_BTSC_SELECT =
        0x0004, /**< TV Systems for BTSC enabled in ATSC(CO, CF) or DVB(Taiwan) system */
    SIF_BTSC_BR_SELECT =
        0x0008, /**< TV Systems for BTSC enabled in ATSC(Brazil) system */
    SIF_BTSC_US_SELECT =
        0x0010,              /**< TV Systems for BTSC enabled in ATSC(US) system */
    SIF_DVB_SELECT = 0x0020, /**< TV Systems for EU in default DVB system */
    SIF_DVB_ID_SELECT =
        0x0040, /**< TV Systems for ID(Indonesia) in DVB(PAL B/G) system */
    SIF_DVB_IN_SELECT =
        0x0080, /**< TV Systems for IN(India) in DVB(PAL B) system */
    SIF_DVB_CN_SELECT =
        0x0100, /**< TV Systems for CN(China, Hong Kone) in DVB system */
    SIF_DVB_AJJA_SELECT =
        0x0200,            /**< TV Systems for AJ(Asia JooDong), JA(JooAang Asia) in DVB system */
    SIF_TYPE_MAX = 0xFFFF, /**< MAX */
} sif_country_ext_type_t;

/**
 * @brief AAD band setup
 * @rst
 * Functional Requirements
 *   priority : 2
 *
 *   Sets the sound system of the current channel. It is set at channel switching.
 *   It is set to M for ATSC. In case of DVB, it is set to system determined by
 *   "Sif DetectSoundSystem" at tuning.
 *
 *   At SetBandSetup
 *   1. Initialize Audio System and clear Audio Standard.
 *   2. When the SetStandardSetup function is called, the second carrier analog
 *      mode setting and the ATV std set are performed
 *
 *   If sif_country_ext_type_t is SIF_DVB_IN_SELECT(for India): FM Mono-Only, High
 *   Deviation Setting (540kHz).
 *
 * Functions & Parameters
 *  param[in] contry_type sif_country_ext_type_t
 *
 *  param[in] soundsystem_type sif_soundsystem_ext_type_t
 *
 *  param[out] contry_type sif_country_ext_type_t (default:0)
 *
 *  param[out] soundsystem_type sif_soundsystem_ext_type_t (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_bandsetup_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          sif_country = ucontrol->value.integer.value[0];
 *          sif_soundsystem = ucontrol->value.integer.value[1];
 *          // Set SIF Bandsetup
 *      }
 *      sif_bandsetup_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Get sat Sif bandsetup Info
 *          ucontrol->value.integer.value[0] = sif_country ;
 *          ucontrol->value.integer.value[1] = sif_soundsystem;
 *      }
 *
 * @endrst
 */
#define SIF_BANDSETUP "Sif BandSetup"

/**
 * sif_standard_ext_type_t is showing sif mode.
 */
typedef enum sif_standard_ext_type
{
    SIF_STANDARD_DETECT, /**< Detecting */
    SIF_BG_NICAM,        /**< BG NICAM */
    SIF_BG_FM,           /**< BG FM */
    SIF_BG_A2,           /**< BG A2 */
    SIF_I_NICAM,         /**< I NICAM */
    SIF_I_FM,            /**< I FM */
    SIF_DK_NICAM,        /**< DK NICAM */
    SIF_DK_FM,           /**< DK FM */
    SIF_DK1_A2,          /**< DK1 A2 */
    SIF_DK2_A2,          /**< DK2 A2 */
    SIF_DK3_A2,          /**< DK3 A2*/
    SIF_L_NICAM,         /**< L NICMA */
    SIF_L_AM,            /**< L AM */
    SIF_MN_A2,           /**< MN A2 */
    SIF_MN_BTSC,         /**< MN BTSC */
    SIF_MN_EIAJ,         /**< EIAJ */
    SIF_NUM_SOUND_STD,   /**< Number of sound standard */
} sif_standard_ext_type_t;

/**
 * @brief AAD standard mode setup
 * @rst
 * Functional Requirements
 *   priority : 2
 *
 *   Set the SIF Standard. After switching channels, set NICAM, A2 and FM
 *   repeatedly until the standard is detected.
 *
 *   When the SetStandardSetup function is called
 *   1. second carrier analog mode setting, and ATV std set.
 *   2. If ATV std set is set and SetStandardSetup is called, no action is taken
 *   3. The ATV std set is then stored until SetBandSetup is called. If BandSetup
 *      is MN and the country is US or KR, Sif StandardSetup should be working.
 *
 *   This put parameter has no meaning for auto 2nd carrier detect task. But If
 *   the "Sif Bandsetup" Country parameter is 0x1F ( ATSC, KOREA_A2, BTSC,
 *   BTSC_BR, BTSC_US ), then driver should use this standard_type value.
 *
 * Functions & Parameters
 *   param[in] standard_type sif_standard_ext_type_t
 *
 *   param[out] standard_type sif_standard_ext_type_t (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_standardsetup_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          sif_standard = ucontrol->value.integer.value[0];
 *          // Set SIF StandardSetup
 *      }
 *      sif_standardsetup_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Get sat Sif StandardSetup Info
 *          ucontrol->value.integer.value[0] = sif_standard ;
 *      }
 *
 * @endrst
 */
#define SIF_STANDARDSETUP "Sif StandardSetup"

/**
 * SIF Analog Audio Getting Parameter.
 */

typedef enum sif_mode_ext_type
{
    SIF_PAL_UNKNOWN = 0x00,          /**< PAL Unknown State */
    SIF_PAL_MONO = 0x01,             /**< PAL Mono */
    SIF_PAL_STEREO = 0x02,           /**< PAL Stereo */
    SIF_PAL_DUAL = 0x03,             /**< PAL Dual */
    SIF_PAL_NICAM_MONO = 0x04,       /**< PAL NICAM Mono */
    SIF_PAL_NICAM_STEREO = 0x05,     /**< PAL NICAM Stereo */
    SIF_PAL_NICAM_DUAL = 0x06,       /**< PAL NICAM Dual */
    SIF_NTSC_A2_UNKNOWN = 0x10,      /**< NTSC(A2) Unknown State */
    SIF_NTSC_A2_MONO = 0x11,         /**< NTSC(A2) Mono */
    SIF_NTSC_A2_STEREO = 0x12,       /**< NTSC(A2) Stereo */
    SIF_NTSC_A2_SAP = 0x13,          /**< NTSC(A2) SAP */
    SIF_NTSC_BTSC_UNKNOWN = 0x14,    /**< NTSC(BTSC) Unknown State */
    SIF_NTSC_BTSC_MONO = 0x15,       /**< NTSC(BTSC) Mono */
    SIF_NTSC_BTSC_STEREO = 0x16,     /**< NTSC(BTSC) Stereo */
    SIF_NTSC_BTSC_SAP_MONO = 0x17,   /**< NTSC(BTSC) SAP Mono */
    SIF_NTSC_BTSC_SAP_STEREO = 0x18, /**< NTSC(BTSC) SAP Stereo */
} sif_mode_ext_type_t;

/**
 * @brief return detected analog_mode
 * @rst
 * Functional Requirements
 *   priority : 2
 *
 *   And informs the audio multiplexing information of the currently received
 *   channel. The LG MW periodically calls the function to monitor the voice
 *   multipath information.
 *
 * Functions & Parameters
 *   param[in] not_used int
 *
 *   param[out] sif_mode sif_mode_ext_type_t (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_curanalogmode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *           // Get current analog mode
 *           ucontrol->value.integer.value[0] = cur_analog_mode;
 *      }
 *
 * @endrst
 */
#define SIF_CUR_ANALOGMODE "Sif CurAnalogMode"

/**
 * SIF Analog Audio User Parameter.
 */

typedef enum sif_mode_user_ext_type
{
    SIF_USER_PAL_UNKNOWN = 0x00,             /**< PAL Unknown */
    SIF_USER_PAL_MONO = 0x01,                /**< PAL Mono */
    SIF_USER_PAL_MONO_FORCED = 0x02,         /**< PAL Mono forced */
    SIF_USER_PAL_STEREO = 0x03,              /**< PAL Stereo */
    SIF_USER_PAL_STEREO_FORCED = 0x04,       /**< PAL Stereo forced */
    SIF_USER_PAL_DUALI = 0x05,               /**< PAL dual 1 */
    SIF_USER_PAL_DUALII = 0x06,              /**< PAL dual 2 */
    SIF_USER_PAL_DUALI_II = 0x07,            /**< PAL dual 1 & 2 */
    SIF_USER_PAL_NICAM_MONO = 0x08,          /**< NICAM Mono */
    SIF_USER_PAL_NICAM_MONO_FORCED = 0x09,   /**< NICAM Mono forced */
    SIF_USER_PAL_NICAM_STEREO = 0x0A,        /**< NICAM Stereo */
    SIF_USER_PAL_NICAM_STEREO_FORCED = 0x0B, /**< NICAM Stereo forced */
    SIF_USER_PAL_NICAM_DUALI = 0x0C,         /**< NICAM Dual 1 */
    SIF_USER_PAL_NICAM_DUALII = 0x0D,        /**< NICAM Dual 2 */
    SIF_USER_PAL_NICAM_DUALI_II = 0x0E,      /**< NICAM Dual 1 & 2 */
    SIF_USER_PAL_NICAM_DUAL_FORCED = 0x0F,   /**< NICAM Dual foreced */
    SIF_USER_NTSC_A2_UNKNOWN = 0x10,         /**< NTSC A2 UNKNOWN */
    SIF_USER_NTSC_A2_MONO = 0x11,            /**< NTSC A2 Mono */
    SIF_USER_NTSC_A2_STEREO = 0x12,          /**< NTSC A2 Stereo */
    SIF_USER_NTSC_A2_SAP = 0x13,             /**< NTSC A2 SAP */
    SIF_USER_NTSC_BTSC_UNKNOWN = 0x14,       /**< BTSC Unknown */
    SIF_USER_NTSC_BTSC_MONO = 0x15,          /**< BTSC Unknown */
    SIF_USER_NTSC_BTSC_STEREO = 0x16,        /**< BTSC Unknown */
    SIF_USER_NTSC_BTSC_SAP_MONO = 0x17,      /**< BTSC Unknown */
    SIF_USER_NTSC_BTSC_SAP_STEREO = 0x18,    /**< BTSC SAP stereo */
} sif_mode_user_ext_type_t;

/**
 * @brief put/get user analog mode
 * @rst
 *
 * Functional Requirements
 *   priority : 2
 *
 *   Set the voice multiplexed value set by the user.
 *
 * Functions & Parameters
 *  param[in] sif_mode sif_mode_user_ext_type_t
 *
 *  param[out] sif_mode sif_mode_user_ext_type_t (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_useranalogmode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *           // Set user_analog_mode
 *           user_analog_mode = ucontrol->value.integer.value[0];
 *      }
 *      sif_detectsoundsystem_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *           // Get user_analog_mode
 *           ucontrol->value.integer.value[0] = user_analog_mode;
 *      }
 *
 * @endrst
 */
#define SIF_USER_ANALOGMODE "Sif UserAnalogMode"

/**
 * sif_existence_info_ext_type_t is just showing SIF Singal exist or not
 */

typedef enum sif_existence_info_ext_type
{
    SIF_ABSENT,               /**< There is no singal */
    SIF_PRESENT,              /**<  There is sif signal */
    SIF_DETECTION_EXISTENCE, /**<  There is sif signal */
} sif_existence_info_ext_type_t;

/**
 * @brief check sif signal exist or not.
 * @rst
 *
 * Functional Requirements
 *   priority : 2
 *
 *   It indicates whether the SIF carrier exists in the input signal.
 *
 * Functions & Parameters
 *   param[in] not_used int
 *
 *   param[out] sif_exist sif_existence_info_ext_type_t (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_sifexist_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *           // Get Sif signal check
 *           ucontrol->value.integer.value[0] = sif_signal_exist ;
 *      }
 *
 *
 * @endrst
 */
#define SIF_SIFEXIST "Sif SifExist"

/**
 * @brief put/get hdev on_off
 * @rst
 *
 * Functional Requirements
 *   priority : 2
 *
 *   Set the High Deviation Level. It will be On only in certain countries and
 *   will be set at boot time. The country level should be set to the spec by HW
 *   measurement. Background and notice
 *
 *   1. In India, because of noisy TV viewing environment, it is difficult to
 *      listen to TV speaker through general volume setting
 *   2. As a result, Indian broadcasters intentionally over-modulated the signal
 *      to increase the volume
 *   3. The TV performs a function called High Deviation (HDEV) mode to process
 *      these signals.
 *   4. The volume of the signal decreases during the operation of the
 *      corresponding function (may vary by platform)
 *   5. To compensate for this, mw is set to input gain for live TV, and + 12dB
 *      for aenc gain for recording (maintained at webOS 3.5)
 *   6. This gives a guide to set the gain on the platform so that the volume
 *      reduced at 4 can be compensated at 5
 *   7. From webOS4.0, remove 5 and set the volume down to 4dB at 0dB to guide it
 *      to input gain (or aenc gain)
 *
 * Functions & Parameters
 *   param[in] hdev_onoff int
 *
 *   param[out] hdev_onoff int (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_sifexist_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          hdev_on_off = ucontrol->value.integer.value[0] ;
 *          // set hdev onoff
 *      }
 *      sif_sifexist_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Get hdev onoff status
 *          ucontrol->value.integer.value[0] = hdev_on_off  ;
 *      }
 *
 * @endrst
 */
#define SIF_HDEV "Sif HDev"

/**
 * @brief put/get a2threshold level
 * @rst
 *
 * Functional Requirements
 *   priority : 4
 *
 *   In general, a pilot carrier is an indicator of mono/stereo sound.
 *   If there is a pilot carrier, the receiver will demodulate wider bandwidth
 *   to handle stereo sound.
 *
 *   Especially for the A2 standard,
 *   fine-tuning of the pilot carrier detection is required for accurate mono/stereo processing.
 *   LG sets the standard value for the mono/stereo judgment of the pilot carrier in AAD HW.
 *
 *   Currently, the default value is 11. However, the value may change depending on the HW test result.
 *   When the strength of the pilot carrier is in the range of 0% to 100%,
 *   the threshold value corresponds to a percentage value.
 *
 *   If pilot carriers above the threshold value should be treated as stereo,
 *   otherwise it should be treated as mono.
 *
 *
 * Functions & Parameters
 *   param[in] A2ThresholdLevel int
 *
 *   param[out] A2ThresholdLevel int (default:0)
 *
 * Responses to abnormal situations, including
 *   None
 *
 * Performance Requirements
 *   Function elapsed time should be less than 10ms.
 *
 * Constraints
 *   None
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   Otherwise:
 *
 *     EBUSY       Internal driver error happened
 *
 *     EINVAL      Invalid argument
 *
 *     EALREADY    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *      sif_a2thresholdlevel_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Set a2threshold level
 *          a2thresholdlevel= ucontrol->value.integer.value[0];
 *      }
 *
 *      sif_a2thresholdlevel_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *      {
 *          // Get a2threshold level
 *          ucontrol->value.integer.value[0] = a2thresholdlevel;
 *      }
 *
 *
 * @endrst
 */
#define SIF_A2THERESHOLDLEVEL "Sif A2ThresholdLevel"

#endif
