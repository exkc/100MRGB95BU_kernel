/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_DTV_H
#define _ALSA_EXT_DTV_H


#if 0
/**
 * adec_dualmono_mode_ext_type_t show dualmono mode
 */
typedef enum adec_dualmono_mode_ext_type {
    ADEC_DUALMONO_MODE_LR  = 0, /**< L Out + R Out */
    ADEC_DUALMONO_MODE_LL  = 1, /**< L Out */
    ADEC_DUALMONO_MODE_RR  = 2, /**< R Out */
    ADEC_DUALMONO_MODE_MIX = 3, /**< L+R Mix and Out */
} adec_dualmono_mode_ext_type_t;

/**
 * @brief set dual_mono mode to adec port
 * @li priority : 3
 *
 * In case of DTV input, it sends L + L, L + R, R + R information to one Audio
 * PID for Japanese or some Sphere Japanese incense, for example, is usually
 * sent to the L channel by sending it to the Japanese R channel, so that two
 * languages can be heard.
 *
 * If you select Japanese in the UI at this time, ADEC_DUALMONO_MODE_LL is set
 * to allow you to listen to Japanese sound.
 *
 * If you select Japanese + English, you can listen Japanese with Left Speaker
 * and English with Right Speaker. In external input (AV or Component),
 * ADEC_DUALMONO_MODE_LRis called to ALSA if you try to listen only to the L
 * terminal of the actual L / R terminal.
 *
 * @b Pseudocode
 * @code
 * adec_OutputMode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     adec_dualmono_mode_t DualMonoMode = ucontrol->value.integer.value[1];
 *     // set trick mode on adec.
 * }
 *
 * adec_OutputMode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * { // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_dual_mono_mode;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_dual_mono_mode;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_dual_mono_mode;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_dual_mono_mode;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] dualmono_mode adec_dualmono_mode_ext_type_t dualmono_mode
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec0_dualmono_mode adec_dualmono_mode_ext_type_t adec0's
 * dualmono mode
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec1_dualmono_mode adec_dualmono_mode_ext_type_t adec1's
 * dualmono mode
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec2_dualmono_mode adec_dualmono_mode_ext_type_t adec2's
 * dualmono mode
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec3_dualmono_mode adec_dualmono_mode_ext_type_t adec3's
 * dualmono mode
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_TP_DECODER_OUTPUTMODE "Adec TP Decoder OutputMode"

/**
 * @brief adec syncmode on/off
 * @li priority : 3
 *
 * API to set the Sync mode Sync mode When On, video and sync are synchronized.
 * If Off, video and sync are not synchronized.
 *
 * 1. "Adec SyncMode" (On) is called for adec port where audio start is done
 *    e.g.
 * @li Channel is changed to AD channel with AD (Off): "Adec SyncMode"(On) is
 * called for main adec port
 * @li AD(Off => On) on AD channel: adec stop => audio start and "Adec
 * SyncMode"(On) will be called for main and AD adec ports
 * @li AD(On => Off) on AD channel: adec stop for AD adec port (no "Adec
 * SyncMode"call)
 *
 * 2. "Adec SyncMode" can be called repeatably
 *
 * 3. timing of calling "Adec SyncMode" might be not fixed (can be after/before
 *    adec start)
 *
 * @b Pseudocode
 * @code
 * adec_syncmode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     BOOLEAN OnOff = ucontrol->value.integer.value[1];
 *     // set syncmode on adec.
 * }
 * adec_syncmode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get syncmode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_syncmode;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_syncmode;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_syncmode;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_syncmode;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] dualmono_mode adec_dualmono_mode_ext_type_t dualmono_mode
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] onoff int syncmode on/off value
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] onoff int syncmode on/off value
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] onoff int syncmode on/off value
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] onoff int syncmode on/off value
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_SYNCMODE "Adec SyncMode"

/**
 * drc mode setting values
 */
typedef enum adec_dolbydrc_mode_ext_type {
    ADEC_DOLBY_LINE_MODE = 0, /**< Line mode */
    ADEC_DOLBY_RF_MODE   = 1, /**< RF mode */
    ADEC_DOLBY_DRC_OFF   = 2, /**< OFF */
} adec_dolbydrc_mode_ext_type_t;

/**
 * @brief set adec dolby drc
 * @li priority : 3
 *
 * API for setting Dolby DRC (Line, RF) mode.
 *
 * LG MW is set to RF mode for DVB and to Line mode for other cases. LG MW
 * TVService uses "Adec DolbyDRCMode" as necessary to inform DRC mode to driver
 * to be set.
 *
 * However, if Gstreamer OMX uses ADEC, ADEC_DOLBYDRCMODE is not used. In this
 * case, driver itself should be set to Line Mode.
 *
 * @b Pseudocode
 * @code
 * adec_dolbydrcmode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     adec_dolbydrc_mode_ext_type_t DolbyDRCMode = ucontrol->value.integer.value[1];
 *     // set DolbyDRCMode on adec.
 * }
 * adec_dolbydrcmode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get DolbyDRCMode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_dolby_drc_mode;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_dolby_drc_mode;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_dolby_drc_mode;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_dolby_drc_mode;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] adec_dolbydrc_mode adec_dolbydrc_mode_ext_type_t dolbydrc mode
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec0_dolbydrc_mode adec_dolbydrc_mode_ext_type_t adec0's
 * dolbydrc mode
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec1_dolbydrc_mode adec_dolbydrc_mode_ext_type_t adec1's
 * dolbydrc mode
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec2_dolbydrc_mode adec_dolbydrc_mode_ext_type_t adec2's
 * dolbydrc mode
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec3_dolbydrc_mode adec_dolbydrc_mode_ext_type_t adec3's
 * dolbydrc mode
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_DOLBYDRCMODE "Adec DolbyDRCMode"

/**
 * @brief set adec default PRL
 * @li priority : 3
 *
 * API for setting default PRL.
 *
 * TVService uses "Adec DefaultPRL" as necessary to inform default PRL to driver to be set.
 * If the PRL value is not included in the Audio ES Stream, audio decoder must refer to
 * this default PRL value.
 *
 * @b Pseudocode
 * @code
 * adec_defaultprl_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     int DefaultPRL = ucontrol->value.integer.value[1];
 *     // set DefaultPRL on adec.
 * }
 * adec_defaultprl_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get DefaultPRL status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_default_prl;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_default_prl;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_default_prl;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_default_prl;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] adec_default_PRL int default PRL
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] int adec0_defaultPRL, adec0's default PRL
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] int adec1_defaultPRL, adec1's default PRL
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] int adec2_defaultPRL, adec2's default PRL
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] int adec3_defaultPRL, adec3's default PRL
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_DEFAULTPRL "Adec DefaultPRL"

/**
 * downmix mode setting values
 */
typedef enum adec_downmix_mode_ext_type {
    ADEC_LORO_MODE = 0, /**< LORO(Stereo) */
    ADEC_LTRT_MODE = 1, /**< LTRT(Stereo) */
} adec_downmix_mode_ext_type_t;

/**
 * @brief set adec dolby drc
 * @li priority : 3
 *
 * API for setting Downmix (LoRo, LtRt) mode.
 *
 * LG MW is set to AAC for LtRt when the audio codec type is AC3, EAC3, PCM, or
 * LoRo for HEAAC. LG MW TVService uses "Adec DownMixMode" according to the
 * audio codec type to allow the driver to change the DownMixMode.
 *
 * However, since GStreamer OMX does not use "Adec DownMixMode" when using ADEC,
 * driver should set LtRt / LoRo according to the above condition according to
 * audio codec type.
 *
 * @b Pseudocode
 * @code
 * adec_dolbydrcmode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     adec_dolbydrc_mode_ext_type_t DolbyDRCMode = ucontrol->value.integer.value[1];
 *     // set DolbyDRCMode on adec.
 * }
 * adec_dolbydrcmode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get DolbyDRCMode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_dolby_drc_mode;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_dolby_drc_mode;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_dolby_drc_mode;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_dolby_drc_mode;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] dualmono_mode adec_downmix_mode_ext_type_t dualmono_mode
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec0_dolbydrc_mode adec_downmix_mode_ext_type_t adec0's
 * dolbydrc mode
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec1_dolbydrc_mode adec_downmix_mode_ext_type_t adec1's
 * dolbydrc mode
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec2_dolbydrc_mode adec_downmix_mode_ext_type_t adec2's
 * dolbydrc mode
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec3_dolbydrc_mode adec_downmix_mode_ext_type_t adec3's
 * dolbydrc mode
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_DOWNMIXMODE "Adec DownMixMode"

/**
 * trick mode values
 */
typedef enum adec_trick_mode_ext_type {
    ADEC_TRICK_NONE               = 0, /**< This is currently not used  */
    ADEC_TRICK_PAUSE              = 1, /**< Pause, DVR & LMF Play rate */
    ADEC_TRICK_NORMAL_PLAY        = 2, /**< 1.00 Play rate */
    ADEC_TRICK_SLOW_MOTION_OP25X  = 3, /**< 0.25 Play rate */
    ADEC_TRICK_SLOW_MOTION_OP50X  = 4, /**< 0.50 Play rate */
    ADEC_TRICK_SLOW_MOTION_OP80X  = 5, /**< 0.80 Play rate */
    ADEC_TRICK_FAST_FORWARD_1P20X = 6, /**< 1.20 Play rate */
    ADEC_TRICK_FAST_FORWARD_1P50X = 7, /**< 1.50 Play rate */
    ADEC_TRICK_FAST_FORWARD_2P00X = 8, /**< 2.00 Play rate */
} adec_trick_mode_ext_type_t;

/**
 * @brief set trick mode to adec port
 * @li priority : 3
 *
 * API to set ADEC play speed in DVR Playback mode Change the Trick state of
 * ADEC during DVR Trick Play such as Pause / Resume.
 *
 * At the time of development, it implements the audio play back speed required
 * by the operation product.
 *
 * @b Pseudocode
 * @code
 * adec_trickmode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     adec_downmix_mode_ext_type_tDownMixMode = ucontrol->value.integer.value[1];
 *     // set trick mode on adec.
 * }
 * adec_trickmode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_trick_mode;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_trick_mode;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_trick_mode;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_trick_mode;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] trick_mode adec_trick_mode_ext_type_t trick mode
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec0_trick_mode adec_trick_mode_ext_type_t adec0's trick mode
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec1_trick_mode adec_trick_mode_ext_type_t adec1's trick mode
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec2_trick_mode adec_trick_mode_ext_type_t adec2's trick mode
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec3_trick_mode adec_trick_mode_ext_type_t adec3's trick mode
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_TRICKMODE "Adec TrickMode"

/**
 * TP Mode Information
 */
typedef enum adec_tp_mode_ext_type {
    ADEC_TP_MODE_MONO,                   /**< MONO */
    ADEC_TP_MODE_JOINT_STEREO,           /**< JOINT_STEREO */
    ADEC_TP_MODE_STEREO,                 /**< STEREO */
    ADEC_TP_MODE_DUALMONO,               /**< DUALMONO */
    ADEC_TP_MODE_MULTI,                  /**< MULTI */
    ADEC_TP_MODE_UNKNOWN,                /**< UNKNOWN */
    ADEC_TP_MODE_2_1_FL_FR_LFE,          /**< For China DRA Codec */
    ADEC_TP_MODE_3_0_FL_FR_RC,           /**< For China DRA Codec */
    ADEC_TP_MODE_3_1_FL_FR_RC_LFE,       /**< For China DRA Codec */
    ADEC_TP_MODE_4_0_FL_FR_RL_RR,        /**< For China DRA Codec */
    ADEC_TP_MODE_4_1_FL_FR_RL_RR_LFE,    /**< For China DRA Codec */
    ADEC_TP_MODE_5_0_FL_FR_FC_RL_RR,     /**< For China DRA Codec */
    ADEC_TP_MODE_5_1_FL_FR_FC_RL_RR_LFE, /**< For China DRA Codec */
} adec_tp_mode_ext_type_t;

/**
 * @brief Audio Description On/Off
 * @li priority : 4
 *
 * API that sets AudioDescription on / off The Dolby AC-4 Decoder supports two
 * presentation selection mode : a preference-based selection and an index-based
 * selection. This function used on an a preference-based selection mode.
 *
 * If you can not mix SPDIF ES, you should only output ES of ADEC set to main
 * audio. This API does not call when Audio Description is off, and when Audio
 * Description changes from on to off, bOnOff parameter is set to OFF Call to
 * inform driver that AD is off. Also, when AD is on, the bOnOff parameter of
 * the API is called ON. For example, if AD is set to 1 in Main Audio and AD
 * audio ADEC is set to 0 in Port
 *
 * Main ADEC refers to the value set in "Sndout MainAudio Output". Driver should
 * be used for AD Volume or AD Pan / Fade application by internally managing the
 * port where AD audio is used through this API.
 *
 * This function must be called before both the Main ADEC and ADEC for Audio
 * Description are started.
 *
 * @b Pseudocode
 * @code
 * adec_TP_AD_AudioDescription_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     Boolean on_off= ucontrol->value.integer.value[0];
 *     // set trick mode on adec.
 * }
 * adec_TP_AudioDescription_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = bOnOff;
 * }
 * @endcode
 *
 * @param[in,out] ADAdecPort int (default 0)
 * @param[in,out] OnOff int (default 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_TP_AUDIODESCRIPTION "Adec TP AudioDescription"

/**
 * @brief show current pts value for adec port
 * @li priority : 4
 *
 * When this function is called, it tells the PTS of the currently decoded
 * audio.
 *
 * 32bit of the most significant bit (MSB) of 33bit of PTS is transmitted as
 * output parameter pPts.
 *
 * LG MW is used to display the progress time of Audio PTS obtained through this
 * function during playback of Radio Channel recordings. (Using Video PTS for
 * recordings with video)
 *
 * @b Pseudocode
 * @code
 * adec0_audiopts_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = pts;
 * }
 * @endcode
 *
 * @param[out] adec_portX_pts int adec portX pts
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC0_TP_PTS "Adec0 TP AudioPTS"
/**
 * @see ADEC0_TP_PTS
 */
#define ADEC1_TP_PTS "Adec1 TP AudioPTS"
/**
 * @see ADEC0_TP_PTS
 */
#define ADEC2_TP_PTS "Adec2 TP AudioPTS"
/**
 * @see ADEC0_TP_PTS
 */
#define ADEC3_TP_PTS "Adec3 TP AudioPTS"

/**
 * language code type
 */
typedef enum adec_ac4_lang_code_ext_type {
    ADEC_AC4_LANG_CODE_ISO639_1 =
        0, /**< ISO639_1 Language Code 2bytes example:'e''n'00 */
    ADEC_AC4_LANG_CODE_ISO639_2 =
        1, /**< ISO639_2 Language Code 3bytes example:'e''n''g'0 */
} adec_ac4_lang_code_ext_type_t;

/**
 * @brief put/get ac4 first language code for each decoder
 * @li priority : 4
 *
 * The Dolby AC-4 Decoder supports two presentation selection mode : a
 * preference-based selection and an index-based selection.
 *
 * This function used on an a preference-based selection mode. This is the API
 * to set the first language of AC-4 decoder. (See "Selection using system-level
 * preferences" of "Dolby MS12 Multistream Decoder Implementation integration
 * manual") adecIndex determines which decoder to set the First Language.
 * enCodeType determines whether to pass the firstLang value as a 2byte ISO639-1
 * type or as a 3byte ISO639-2 type.
 *
 * @li firstLang sets the first language of the AC-4 decoder.
 * @li firstLang is passed as the upper 2 bytes of UINT32 if enCodeType is ISO
 * 639-1 type, and 0 as the remaining lower 2 bytes. example: 'e''n'00
 * @li firstLang is passed in the upper 3 bytes of UINT32 if the enCodeType is
 * ISO 639-2 type and 0 in the last 1 byte. example: 'e''n''g'0
 *
 * When several languages are delivered to one ES in AC-4, first language
 * selected in First Language is selected and output.
 *
 * Because this API is used only on platforms that support AC-4, on platforms
 * that do not support AC-4, configure the API with dummy.
 *
 * @b Pseudocode
 * @code
 * adec_ac4_1stlang_Output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int adec_port_num = ucontrol->value.integer.value[0];
 *     adec_ac4_lang_code_ext_type_t type= ucontrol->value.integer.value[1];
 *     UINT32 firstLang, = ucontrol->value.integer.value[2];
 *     // set trick mode on adec.
 * }
 * adec_ac4_1stlang_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_ac4_lang_type;
 *     ucontrol->value.integer.value[2] = adec0_firstlang;
 *     ucontrol->value.integer.value[3] = 1;
 *     ucontrol->value.integer.value[4] = adec1_ac4_lang_type;
 *     ucontrol->value.integer.value[5] = adec1_firstlang;
 *     ucontrol->value.integer.value[6] = 2;
 *     ucontrol->value.integer.value[7] = adec2_ac4_lang_type;
 *     ucontrol->value.integer.value[8] = adec2_firstlang;
 *     ucontrol->value.integer.value[9] = 3;
 *     ucontrol->value.integer.value[10] = adec3_ac4_lang_type;
 *     ucontrol->value.integer.value[11] = adec3_firstlang;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int port number
 * @param[in] language_code_tyep adec_ac4_lang_code_ext_type_t Language Code
 * Type
 * @param[in] firstLang int Language Code
 *
 * @param[out] adec_port0_number int := 0( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port0_lang_code_type adec_ac4_lang_code_ext_type_t language
 * code type
 * @param[out] firstLang int Language Code for adec0
 * @param[out] adec_port1_number int := 1( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port1_lang_code_type adec_ac4_lang_code_ext_type_t language
 * code type
 * @param[out] firstLang int Language Code for adec1
 * @param[out] adec_port2_number int := 2( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port2_lang_code_type adec_ac4_lang_code_ext_type_t language
 * code type
 * @param[out] firstLang int Language Code for adec2
 * @param[out] adec_port3_number int := 3( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port3_lang_code_type adec_ac4_lang_code_ext_type_t language
 * code type
 * @param[out] firstLang int Language Code for adec3
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AC4_AUTO1STLANG "Adec AC4 Auto1stLang"

/**
 * @brief put/get ac4 second language code for each decoder
 * @li priority : 4
 *
 * The Dolby AC-4 Decoder supports two presentation selection mode : a
 * preference-based selection and an index-based selection.
 *
 * This function used on an a preference-based selection mode. This is the API
 * for setting the Second Language of AC-4 decoder. (See "Selection using
 * system-level preferences" of "Dolby MS12 Multistream Decoder Implementation
 * integration manual") adecIndex determines which decoder will set Second
 * Language. enCodeType determines whether to pass the value of secondLang as
 * 2byte ISO639-1 type or as 3byte ISO639-2 type.
 *
 * @li secondLang sets the Second Language of the AC-4 decoder.
 * @li secondLang is passed to upper two bytes of UINT32 if enCodeType is ISO
 * 639-1 type, and to 0 for the remaining lower 2 bytes. example: 'e''n'00
 * @li secondLang is passed as the upper 3 bytes of UINT32 if the enCodeType is
 * ISO 639-2 type, and 0 as the last 1 byte. example: 'e''n''g'0
 *
 * If several languages are delivered to one ES in AC-4, if there is no language
 * selected in First Language, Second Language is selected and decoded first.
 *
 * Because this API is used only on platforms that support AC-4, on platforms
 * that do not support AC-4, configure the API with dummy.
 *
 * @b Pseudocode
 * @code
 * adec_ac4_2ndlang_Output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int adec_port_num = ucontrol->value.integer.value[0];
 *     adec_ac4_lang_code_ext_type_t type= ucontrol->value.integer.value[1];
 *     UINT32 firstLang, = ucontrol->value.integer.value[2];
 *     // set trick mode on adec.
 * }
 * adec_ac4_2ndlang_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_ac4_lang_type;
 *     ucontrol->value.integer.value[2] = adec0_firstlang;
 *     ucontrol->value.integer.value[3] = 1;
 *     ucontrol->value.integer.value[4] = adec1_ac4_lang_type;
 *     ucontrol->value.integer.value[5] = adec1_firstlang;
 *     ucontrol->value.integer.value[6] = 2;
 *     ucontrol->value.integer.value[7] = adec2_ac4_lang_type;
 *     ucontrol->value.integer.value[8] = adec2_firstlang;
 *     ucontrol->value.integer.value[9] = 3;
 *     ucontrol->value.integer.value[10] = adec3_ac4_lang_type;
 *     ucontrol->value.integer.value[11] = adec3_firstlang;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int port number
 * @param[in] language_code_tyep adec_ac4_lang_code_ext_type_t Language Code
 * Type
 * @param[in] secondlang int Language Code
 *
 * @param[out] adec_port0_number int := 0( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port0_lang_code_type adec_ac4_lang_code_ext_type_t language
 * code type
 * @param[out] secondlang int Language Code for adec0
 * @param[out] adec_port1_number int := 1( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port1_lang_code_type adec_ac4_lang_code_ext_type_t language
 * code type
 * @param[out] secondlang int Language Code for adec1
 * @param[out] adec_port2_number int := 2( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port2_lang_code_type adec_ac4_lang_code_ext_type_t language
 * code type
 * @param[out] secondlang int Language Code for adec2
 * @param[out] adec_port2_number int := 3( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port3_lang_code_type adec_ac4_lang_code_ext_type_t language
 * code type
 * @param[out] secondlang int Language Code for adec3
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AC4_AUTO2NDLANG "Adec AC4 Auto2ndLang"

/**
 * ac4 audio description type
 */
typedef enum adec_ac4_ad_ext_type {
    ADEC_AC4_AD_TYPE_NONE = 0, /**< None - Default */
    ADEC_AC4_AD_TYPE_VI   = 1, /**< Visually Impaired (VI) */
    ADEC_AC4_AD_TYPE_HI   = 2, /**< Hearing Impaired (HI) */
    ADEC_AC4_AD_TYPE_C    = 3, /**< Commentary (C) */
    ADEC_AC4_AD_TYPE_E    = 4, /**< Emergency (E) */
    ADEC_AC4_AD_TYPE_VO   = 5, /**< Voice Over (VO) */
} adec_ac4_ad_ext_type_t;

/**
 * @brief set AC4 decoder's Audio Description Type
 * @li priority : 4
 *
 * The Dolby AC-4 Decoder supports two presentation selection mode : a
 * preference-based selection and an index-based selection. This function used
 * on an a preference-based selection mode. This is an API to set the Audio
 * Description (AD) Type of AC-4 decoder. (See "Selection using system-level
 * preferences" of "Dolby MS12 Multistream Decoder Implementation integration
 * manual")
 *
 * adecIndex determines which decoder the AD type is set to. enADType is entered
 * as adec_ac4_ad_ext_type_t .
 *
 * Currently, LG MW uses only ADEC_AC4_AD_TYPE_NONE and ADEC_AC4_AD_TYPE_VI, and
 * the remaining define is for future use. ADEC_AC4_AD_TYPE_NONE means AD off.
 * ADEC_AC4_AD_TYPE_VI means AD on for Visually Impaired (VI). Unlike
 * conventional AD, which uses dual decoding implemented in DVB, AC-4 can
 * transmit Main Audio and AD Audio to one ES.
 *
 * In case that Main Audio and AD Audio exist together in one ES in AC-4, if AD
 * Type is set to ADEC_AC4_AD_TYPE_VI, Main Audio and AD Audio are decoded
 * together and output. Because this API is used only on platforms that support
 * AC-4, on platforms that do not support AC-4, configure the API with dummy.
 *
 * @b Pseudocode
 * @code
 * adec_ac4_ADType_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     adec_ac4_lang_code_ext_type_t type= ucontrol->value.integer.value[1];
 *     // set trick mode on adec.
 * }
 * adec_ac4_ADType_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_adtype;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_adtype;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_adtype;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_adtype;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int port number
 * @param[in] enADtype adec_ac4_ad_ext_type_t AC4 AD type
 *
 * @param[out] adec_port0_number int := 0( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port0_enADtype adec_ac4_ad_ext_type_t AC-4 AD Type
 * @param[out] adec_port1_number int := 1( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port1_enADtype adec_ac4_ad_ext_type_t AC-4 AD Type
 * @param[out] adec_port2_number int := 2( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port2_enADtype adec_ac4_ad_ext_type_t AC-4 AD Type
 * @param[out] adec_port3_number int := 3( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_port3_enADtype adec_ac4_ad_ext_type_t AC-4 AD Type
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AC4_AUTO_ADTYPE "Adec AC4 AutoADType"

/**
 * @brief choose which AD or Language has higher priority.
 * @li priority : 4
 *
 * The Dolby AC-4 Decoder supports two presentation selection mode : a
 * preference-based selection and an index-based selection. This function used
 * on an a preference-based selection mode. It is an API to set priority between
 * Language and Audio Description (AD) when Presentation is selected in AC-4
 * decoder. (See "Selection using system-level preferences" of "Dolby MS12
 * Multistream Decoder Implementation integration manual")
 *
 * In other words, do you prefer AD to select presentation? It is an API that
 * decides whether to set the language first.
 *
 * For example, if Presentation is configured as follows, Presentation 1 will be
 * selected if PrioritizeADType is TRUE even if First-Language is set to German.
 * @li Presentation 1: English + AD
 * @li Presentation 2: German Non AD
 *
 * adecIndex determines which decoder the AD type is set to.
 * @li If bIsEnable is TRUE, set Presentation to AD first.
 * @li If bIsEnable is FALSE, set the presentation with Language (First, Second
 * Language setting) as priority. (See 3.3.3.48 and 3.3.3.49)
 *
 * Because this API is used only on platforms that support AC-4, on platforms
 * that do not support AC-4, configure the API with dummy.
 *
 * @b Pseudocode
 * @code
 * adec_ac4_PriorityADType_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     adec_ac4_lang_code_ext_type_t type= ucontrol->value.integer.value[1];
 *     // set trick mode on adec.
 * }
 * adec_ac4_PriorityADType_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_adtype;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_adtype;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_adtype;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_adtype;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int port number
 * @param[in] bIsEnable int TRUE : AD, FALSE : Language
 *
 * @param[out] adec_port0_number int := 0( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] bIsEnable int TRUE : AD, FALSE : Language
 * @param[out] adec_port1_number int := 1( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] bIsEnable int TRUE : AD, FALSE : Language
 * @param[out] adec_port2_number int := 2( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] bIsEnable int TRUE : AD, FALSE : Language
 * @param[out] adec_port3_number int := 3( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] bIsEnable int TRUE : AD, FALSE : Language
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AC4_AUTO_PRIORITIZE_ADTYPE "Adec AC4 AutoPrioritizeADType"

/**
 * @brief gain value for AC4 Dialogue Enhancement Gain.
 * @li priority : 4
 *
 * Enable or disable TruSurround:X Height upmix for non-immersive channel layout
 * (= inputs without discrete height channels)
 *
 * @b Pseudocode
 * @code
 * adec_ac4_DialogEnhanceGain_put(struct snd_kcontrol *kcontrol, struct
 *     snd_ctl_elem_value *ucontrol) {int port_index=
 *     ucontrol->value.integer.value[0]; int dialEnhanceGain =
 *     ucontrol->value.integer.value[1]; // set gain param
 * }
 *
 * adec_ac4_DialogEnhanceGain_get(struct snd_kcontrol *kcontrol, struct
 *     snd_ctl_elem_value *ucontrol) {// get gain param
 *     ucontrol->value.integer.value[0] = adec0_port_index;
 *     ucontrol->value.integer.value[1] = adec0_dialEnhanceGain;
 *     ucontrol->value.integer.value[2] = adec1_port_index;
 *     ucontrol->value.integer.value[3] = adec1_dialEnhanceGain;
 *     ucontrol->value.integer.value[4] = adec2_port_index;
 *     ucontrol->value.integer.value[5] = adec2_dialEnhanceGain;
 *     ucontrol->value.integer.value[6] = adec3_port_index;
 *     ucontrol->value.integer.value[7] = adec3_dialEnhanceGain;
 * }
 * @endcode
 *
 * @param[in] adec_port_index int
 * @param[in] dialEnhanceGain int 0 ~ 12 in dB
 *
 * @param[out] adec_port0_number int := 0( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] dialEnhanceGain int
 * @param[out] adec_port1_number int := 1( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] dialEnhanceGain int
 * @param[out] adec_port2_number int := 2( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] dialEnhanceGain int
 * @param[out] adec_port3_number int := 3( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] dialEnhanceGain int
 *
 * @return 0 if it success. exception values if it fails.
 *
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AC4_DIALOGENHANCEGAIN "Adec AC4 DialogEnhanceGain"

/**
 * @brief set AC4 ADMixing Enable or Disable.
 * @li priority : 4
 *
 * The Dolby AC-4 Decoder supports two presentation selection mode : a
 * preference-based selection and an index-based selection. This function used
 * on an a preference-based selection mode. It is an API to set Audio
 * Description (AD)  Enable or Disable when Presentation is selected in AC-4
 * decoder.(See "Selection using system-level preferences" of "Dolby MS12
 * Multistream Decoder Implementation integration manual")
 *
 * Using Adec AC4 AutoADType" set AUDIO_AC4AD_TYPE_NONE, and  "Adec AC4
 * AutoADMixing" set to FALSE. AD On - Adec AC4 AutoADType" set
 * AUDIO_AC4AD_TYPE_VI, and  "Adec AC4 AutoADMixing" set to TRUE.
 *
 * For example, if Presentation is configured as follows, Presentation 2 will be
 * selected if AutoADMixing is TRUE. Presentation 1 will be selected if
 * AutoADMixing is FALSE.
 * @li Presentation 1: English
 * @li Presentation 2: English + AD
 *
 * adecIndex determines which decoder the AD type is set to.
 * @li If bIsEnable is TRUE, set Presentation to AD.
 * @li If bIsEnable is FALSE, set the presentation to non AD.
 *
 * Because this API is used only on platforms that support AC-4, on platforms
 * that do not support AC-4, configure the API with dummy.
 *
 * @b Pseudocode
 * @code
 * adec_ac4_PriorityADMixing_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     int admixing_on_off = ucontrol->value.integer.value[1];
 *     // set trick mode on adec.
 * }
 * adec_ac4_PriorityADMixing_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_admixing_on_off;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_admixing_on_off;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_admixing_on_off;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_admixing_on_off;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int port number
 * @param[in] on_off int AC4 ADMixing Enable or Disable
 *
 * @param[out] adec_port0_number int := 0( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec0_enAD_on_off int AC4 ADMixing Enable or Disable
 * @param[out] adec_port1_number int := 1( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec1_enAD_on_off int AC4 ADMixing Enable or Disable
 * @param[out] adec_port2_number int := 2( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec2_enAD_on_off int AC4 ADMixing Enable or Disable
 * @param[out] adec_port3_number int := 3( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec3_enAD_on_off int AC4 ADMixing Enable or Disable
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AC4_AUTO_ADMIXING "Adec AC4 AutoADMixing"

/**
 * @brief put/get ac4 Presentation Group Index for each decoder
 * @li priority : 4
 *
 * This is the API to set Presentation Group Index of AC-4 decoder. (See
 * "Presentation selection" of "Dolby MS12 Multistream Decoder Implementation
 * integration manual") The Dolby AC-4 Decoder supports two presentation
 * selection mode : a preference-based selection and an index-based selection.
 *
 * This function used on an index-based selection mode. adecIndex determines
 * which decoder to set presentation selection mode. adec_ac4_pres_group_idx
 * sets the Presentation Group Index(PGI) of the AC-4 decoder.
 *
 * A range of adec_ac4_pres_group_idx is 0 ~ 0x20. Max Value is 0x20. This value
 * means not select Presentation Group Index(). When Presentation Group Index()
 * is not select, decoder select and play on a preference-based selection.
 *
 * @b Pseudocode
 * @code
 * adec_ac4_PresGroupIdx_Output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int adec_port_num = ucontrol->value.integer.value[0];
 *     int adec_ac4_pres_group_idx= ucontrol->value.integer.value[1];
 * }
 * adec_ac4_PresGroupIdx_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get Presentation Grouup Index
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec_ac4_pres_group_idx;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec_ac4_pres_group_idx;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec_ac4_pres_group_idx;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec_ac4_pres_group_idx;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int port number
 * @param[in] adec_ac4_pres_group_idx int AC-4 Presentation Group Index
 *
 * @param[out] adec_port0_number int := 0( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_ac4_pres_group_idx int AC-4 Presentation Group Index
 * @param[out] adec_port1_number int := 1( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_ac4_pres_group_idx int AC-4 Presentation Group Index
 * @param[out] adec_port2_number int := 2( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_ac4_pres_group_idx int AC-4 Presentation Group Index
 * @param[out] adec_port3_number int := 3( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec_ac4_pres_group_idx unsigned int AC-4 Presentation Group
 * Index
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AC4_PRES_GROUP_IDX "Adec AC4 PresGroupIdx"

/**
 * @brief return the status of ADEC buffer
 * @li priority : 4
 *
 * When this function called, it should be return buffer status for Adec.
 *
 * This function called when saved radio ts data play on Dasy.
 *
 * Dasy will check the max and freesize for decide how much ts data push to
 * sdec.
 *
 * @b Pseudocode
 * @code
 * adec_bufferstatus_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Get trick mode status from recently modified. Please check the Parameter descriptions
 *     ucontrol->value.integer.value[0] = MaxSize;
 *     ucontrol->value.integer.value[1] = FreeSize;
 * }
 * @endcode
 *
 * @param[out] MaxSize int Adec max buffer size (default:Defined by driver)
 * @param[out] FreeSize int Adec max free size (default:Defined by driver)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC0_TP_BUFFERSTATUS "Adec0 TP BufferStatus"

/**
 * @see ADEC0_TP_BUFFERSTATUS
 */
#define ADEC1_TP_BUFFERSTATUS "Adec1 TP BufferStatus"

/**
 * @see ADEC0_TP_BUFFERSTATUS
 */
#define ADEC2_TP_BUFFERSTATUS "Adec2 TP BufferStatus"

/**
 * @see ADEC0_TP_BUFFERSTATUS
 */
#define ADEC3_TP_BUFFERSTATUS "Adec3 TP BufferStatus"

/**
 * @brief Determines the balance between main and associated audio in the mixed output for AC4.
 * @li priority : 4
 *
 * When this function called, it should be control associated audio mixer balance
 *
 * @b Pseudocode
 * @code
 * adec_ac4_AssociateAudioVolume_put(struct snd_kcontrol *kcontrol, struct
 *     snd_ctl_elem_value *ucontrol) {
 *     int port_index = ucontrol->value.integer.value[0];
 *     int mixing_gain = ucontrol->value.integer.value[1]; // -32~+32
 * }
 *
 * adec_ac4_AssociateAudioVolume_get(struct snd_kcontrol *kcontrol, struct
 *     snd_ctl_elem_value *ucontrol) {// get gain param
 *     ucontrol->value.integer.value[0] = adec0_port_index;
 *     ucontrol->value.integer.value[1] = adec0_associatedAudioMixerBalance;
 *     ucontrol->value.integer.value[2] = adec1_port_index;
 *     ucontrol->value.integer.value[3] = adec1_associatedAudioMixerBalance;
 *     ucontrol->value.integer.value[4] = adec2_port_index;
 *     ucontrol->value.integer.value[5] = adec2_associatedAudioMixerBalance;
 *     ucontrol->value.integer.value[6] = adec3_port_index;
 *     ucontrol->value.integer.value[7] = adec3_associatedAudioMixerBalance;
 * }
 * @endcode
 *
 * @param[in] adec_port_index int
 * @param[in] associatedAudioMixerBalance int -32 ~ +32 in dB
 *
 * @param[out] adec_port0_number int := 0( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] associatedAudioMixerBalance int
 * @param[out] adec_port1_number int := 1( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] associatedAudioMixerBalance int
 * @param[out] adec_port2_number int := 2( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] associatedAudioMixerBalance int
 * @param[out] adec_port3_number int := 3( if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] associatedAudioMixerBalance int
 *
 * @return 0 if it success. exception values if it fails.
 *
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AC4_ASSOCIATE_AUDIO_VOLUME "Adec AC4 AssociateAudioVolume"

#endif
#endif
