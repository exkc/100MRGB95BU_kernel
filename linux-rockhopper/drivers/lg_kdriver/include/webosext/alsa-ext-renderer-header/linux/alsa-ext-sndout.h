/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022-2024 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_SOUNDOUT_H
#define _ALSA_EXT_SOUNDOUT_H

#include <linux/alsa-ext/alsa-ext-common.h>

/**
 * @brief open sndout device
 *
 * priority : 1
 *
 * @rst
 * Functional Requirements
 *   Open / Connect / Disconnect / Close, Open and Close are called with specific
 *   output values. At this time, if it is open, it operates normally for an open
 *   output device and returns an error return for an open output device. The
 *   Output Device is generally capable of being opened together. (SPK + OPTIC)
 *   And it should be displayed on same time with "OR" operation.. for example,
 *   get "Sndout Open" value should be "3" if we open SPK and OPTIC.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //function
 *     sndout_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //parameter
 *     struct snd_kcontrol *kcontrol
 *     "SndOut Open"
 *
 *     struct snd_ctl_elem_value *ucontrol
 *     value[0]: output
 *        COMMON_NO_OUTPUT = 0x0000
 *        COMMON_SPK       = 0x0001
 *        COMMON_OPTIC     = 0x0002
 *        COMMON_OPTIC_LG  = 0x0004
 *        COMMON_BLUETOOTH = 0x0008
 *        COMMON_HP        = 0x0010
 *        COMMON_ARC       = 0x0020
 *        COMMON_WISA      = 0x0040
 *        COMMON_SE_BT     = 0x0080
 *        COMMON_CAPTURE   = 0x0100
 *        COMMON_SE_ARC    = 0x0200
 *        COMMON_SE_BT_SUR = 0x0400
 *        COMMON_WOWCAST   = 0x0800
 *        COMMON_DAP_HP_BT = 0x1000
 *        COMMON_LINE_OUT  = 0x2000
 *        COMMON_DAFC      = 0x4000
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``       Internal driver error happened
 *
 *   ``EINVAL``      Invalid argument
 *
 *   ``EALREADY``    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         int value = ucontrol->value.integer.value[0];
 *         // Open Resource
 *     }
 *     sndout_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get Opened Resource
 *         ucontrol->value.integer.value[0] = value;
 *     }
 *
 *     =========================== =============== ================
 *     Call Function with Prameter Sndout Open Get Sndout Close Get
 *     =========================== =============== ================
 *     "Sndout Open"  1            1               0
 *     "Sndout Open"  2            3               0
 *     "Sndout Open"  4            7               0
 *     "Sndout Close" 2            5               2
 *     "Sndout Close" 1            4               1
 *     "Sndout Close" 4            0               4
 *     =========================== =============== ================
 * @endrst
 */
#define SNDOUT_OPEN "Sndout Open"

/**
 * @brief close sndout device
 *
 * priority : 1
 *
 * @rst
 * Functional Requirements
 *   In case of SPDIF_ES, it plays the same role as SPDIF, and additional type is
 *   added by request of specific Soc chip. Therefore, SPDIF_ES is also called at
 *   the same time when SPDIF is called. Open / Connect / Disconnect / Close, Open
 *   and Close are called with specific output values.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     struct snd_kcontrol *kcontrol
 *     "Sndout Close"
 *     struct snd_ctl_elem_value{};
 *     value[0]: output
 *        COMMON_NO_OUTPUT = 0x0000
 *        COMMON_SPK       = 0x0001
 *        COMMON_OPTIC     = 0x0002
 *        COMMON_OPTIC_LG  = 0x0004
 *        COMMON_BLUETOOTH = 0x0008
 *        COMMON_HP        = 0x0010
 *        COMMON_ARC       = 0x0020
 *        COMMON_WISA      = 0x0040
 *        COMMON_SE_BT     = 0x0080
 *        COMMON_CAPTURE   = 0x0100
 *        COMMON_SE_ARC    = 0x0200
 *        COMMON_SE_BT_SUR = 0x0400
 *        COMMON_WOWCAST   = 0x0800
 *        COMMON_DAP_HP_BT = 0x1000
 *        COMMON_LINE_OUT  = 0x2000
 *        COMMON_DAFC      = 0x4000
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          int value = ucontrol->value.integer.value[0];
 *          // Close Resource
 *     }
 *
 *     sndout_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get Closed Resource
 *          ucontrol->value.integer.value[0] = value;
 *     }
 *
 * @endrst
 */
#define SNDOUT_CLOSE "Sndout Close"

/**
 * @brief connect sndout device with input
 *
 * priority : 1
 *
 * @rst
 * Functional Requirements
 *   In case of SPDIF_ES, it plays the same role as SPDIF, and additional type is
 *   added by request of specific Soc chip. So, SPDIF_ES is also called at the
 *   same time when calling SPDIF SNDOUT_OPTIC If there is a connection, remove
 *   the BarID. COMMON_OPTIC_LG_EXT_TYPE Sends a BarID to the
 *   SNDOUT_SB_SetOpticalIDData call at connect time.
 *
 *   Open / Connect / Disconnect / Close For example, if you connect to 8 input
 *   modules and you break 7 input modules, As a result, it is connected to one
 *   input module, so the sound should continue to be output.
 *
 *   This first get parameters also displayed same way with "Sndout Open"
 *   "connected_all_outputs" value should be displayed on same time with "OR"
 *   operation.. for example, get "Sndout Connect" first value should be "3" if we
 *   connect SPK and OPTIC with other inputs..
 *
 *   ========================= ============ ================= ================= ============
 *   Call Function with param  Sndout Open  Sndout Connect    Sndout Disconnect Sndout Close
 *   ========================= ============ ================= ================= ============
 *   "Sndout Open"       1     1            0,0,0,0,0,0,0,0,0 0,0,0             0
 *   "Sndout Open"       2     3            0,0,0,0,0,0,0,0,0 0,0,0             0
 *   "Sndout Connect"    1,1,0 3            1,1,0,0,0,0,0,0,0 0,0,0             0
 *   "Sndout Connect"    1,1,1 3            1,1,1,1,0,0,0,0,0 0,0,0             0
 *   "Sndout Connect"    2,1,0 3            3,1,0,1,1,1,0,0,0 0,0,0             0
 *   "Sndout Connect"    2,1,1 3            3,1,1,1,0,1,1,1,0 0,0,0             0
 *   "Sndout Close"      2     1            1,1,1,1,0,0,0,0,0 0,0,0             2
 *   "Sndout Disconnect" 1,1,1 1            1,1,0,0,0,0,0,0,0 1,1,1             2
 *   "Sndout Disconnect" 1,1,0 1            0,0,0,0,0,0,0,0,0 1,1,0             2
 *   ========================= ============ ================= ================= ============
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     adc_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     adc_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Connect"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0] = output
 *        COMMON_NO_OUTPUT = 0x0000
 *        COMMON_SPK       = 0x0001
 *        COMMON_OPTIC     = 0x0002
 *        COMMON_OPTIC_LG  = 0x0004
 *        COMMON_BLUETOOTH = 0x0008
 *        COMMON_HP        = 0x0010
 *        COMMON_ARC       = 0x0020
 *        COMMON_WISA      = 0x0040
 *        COMMON_SE_BT     = 0x0080
 *        COMMON_CAPTURE   = 0x0100
 *        COMMON_SE_ARC    = 0x0200
 *        COMMON_SE_BT_SUR = 0x0400
 *        COMMON_WOWCAST   = 0x0800
 *        COMMON_DAP_HP_BT = 0x1000
 *        COMMON_LINE_OUT  = 0x2000
 *        COMMON_DAFC      = 0x4000
 *     value[1] = input
 *        COMMON_NO_INPUT     = 0x0000
 *        COMMON_INPUT_ADEC   = 0x0001
 *        COMMON_INPUT_AMIXER = 0x0010
 *     value[2] = input_port
 *        Adec supports 0~1
 *        Amixer supports 0~9(8 : DAFC, 9 : ULTRA Sense)
 *        
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_connect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          int output = ucontrol->value.integer.value[0];
 *          int input = ucontrol->value.integer.value[1];
 *          int port_number = ucontrol->value.integer.value[2];
 *          // Connect Resource
 *     }
 *     sndout_connect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get Connected Resource Check details
 *          ucontrol->value.integer.value[0] = outputs;
 *          ucontrol->value.integer.value[1] = inputs;
 *          ucontrol->value.integer.value[2] = port_numbers;
 *          ucontrol->value.integer.value[3] = inputs;
 *          ucontrol->value.integer.value[4] = port_numbers;
 *          ucontrol->value.integer.value[5] = inputs;
 *          ucontrol->value.integer.value[6] = port_numbers;
 *          ucontrol->value.integer.value[7] = inputs;
 *          ucontrol->value.integer.value[8] = port_numbers;
 *     }
 *
 * @endrst
 */
#define SNDOUT_CONNECT "Sndout Connect"

/**
 * @brief disconnect sndout device
 *
 * priority : 1
 *
 *
 * @rst
 * Functional Requirements
 *   SoundOut Used to disconnect a specific output of the module.
 *
 *   In case of SPDIF_ES, it plays the same role as SPDIF, and additional type is
 *   added by request of specific Soc chip. Therefore, SPDIF_ES is also called at
 *   the same time when SPDIF is called.
 *
 *   In case of a COMMON_HP, it does not use a LG sound engine data-path.
 *   The sound output of COMMON_HP should not be controled by the mute status or changing volume
 *   of a lg sound engine.
 *
 *   The input resource is equal to the value shown in COMMON_INPUT_ext_type_t.
 *   COMMON_NO_INPUT_EXT_TYPE= 0x0000 COMMON_INPUT_ADEC_EXT_TYPE= 0x0001,
 *   COMMON_INPUT_AMIXER_EXT_TYPE= 0x0002,
 *
 *   Open / Connect / Disconnect / Close For example, if you connect to 8 input
 *   modules and you break 7 input modules, As a result, it is connected to one
 *   input module, so the sound should continue to be output. (Important: for
 *   SNDOUT_SNDOUT_Disconnect (COMMON_SPK_EXT_TYPE, COMMON_INPUT_SE) When the
 *   input resource is disconnected from ADEC0 to AMIX9, the same function and the
 *   same value above are called 10 times. You must implement it without problems.
 *
 *   In other words, connect SPK to SE_Connect / Disconnect and use SNDOUT_Connect
 *   / Disconnect for the rest of the output) For example, if you connect ADEC0
 *   and disconnect ADEC1, SNDOUT_Connect (COMMON_SPK_EXT_TYPE) and
 *   SNDOUT_Disconnect (COMMON_SPK_EXT_TYPE) will be called sequentially, but
 *   sound should come out because ADEC0 is connected.
 *
 *   When Soundoutput is changed, delay, gain, optic/arc/earc output type will be set.
 *   Total time of setting Sndout Open/Close, Connect/Disconnect, Delay, Gain,
 *   optic/arc/earc output type should be under 200ms
 *
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     /
 *     sndout_disconnect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_disconnect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Disconnect"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0] = output
 *        COMMON_NO_OUTPUT = 0x0000
 *        COMMON_SPK       = 0x0001
 *        COMMON_OPTIC     = 0x0002
 *        COMMON_OPTIC_LG  = 0x0004
 *        COMMON_BLUETOOTH = 0x0008
 *        COMMON_HP        = 0x0010
 *        COMMON_ARC       = 0x0020
 *        COMMON_WISA      = 0x0040
 *        COMMON_SE_BT     = 0x0080
 *        COMMON_CAPTURE   = 0x0100
 *        COMMON_SE_ARC    = 0x0200
 *        COMMON_SE_BT_SUR = 0x0400
 *        COMMON_WOWCAST   = 0x0800
 *        COMMON_DAP_HP_BT = 0x1000
 *     value[1] = common_input_ext_type_t input_type
 *        COMMON_NO_INPUT     = 0x0000
 *        COMMON_INPUT_ADEC   = 0x0001
 *        COMMON_INPUT_AMIXER = 0x0010
 *     value[2] = input_port
 *        Adec supports 0~1
 *        Amixer supports 0~9
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_disconnect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *          int output= ucontrol->value.integer.value[0];
 *          int input= ucontrol->value.integer.value[1];
 *          int input_port= ucontrol->value.integer.value[2];
 *          // Disconnect Resource
 *     }
 *     sndout_disconnect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get Disconnected Resource
 *          ucontrol->value.integer.value[0] = output;
 *          ucontrol->value.integer.value[1] = input_type;
 *          ucontrol->value.integer.value[2] = input_port;
 *     }
 *
 * @endrst
 */
#define SNDOUT_DISCONNECT "Sndout Disconnect"

/**
 * @brief put/get MainAudio Output
 *
 * priority : 1
 *
 * @rst
 * Functional Requirements
 *   If ADEC0 and ADEC1 are connected to SPDIF soundout, it is an API to set Main
 *   ADEC to output SPDIF ES.
 *
 *   If the setting by SNDOUT_SPDIF_SetOutputType is AUTO, the mixed ES should be
 *   output if SPDIF is possible, and the ES of ADEC specified by
 *   SNDOUT_SetMainDecoderOutput if impossible. When the setting by
 *   SNDOUT_SPDIF_SetOutputType is PCM, the PCM mixed output of ADEC0 and ADEC1
 *   should be output with SPDIF.
 *
 *   Store clock information of each audio resource to each different variables.
 *   By storing each audio resource information, it is possible to solve the problem of incorrectly using
 *   information of different input.
 *   When changing the input resource to be output to the main, each stored clock information may be used.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_mainaudio_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_mainaudio_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout MainAudio Output"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0] = common_input_ext_type_t input_type
 *        COMMON_NO_INPUT     = 0x0000
 *        COMMON_INPUT_ADEC   = 0x0001
 *        COMMON_INPUT_AMIXER = 0x0010
 *     value[1] = input_port
 *        Adec supports 0~1
 *        Amixer supports 0~7
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_mainaudio_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         int input_type= ucontrol->value.integer.value[0];
 *         int port_number= ucontrol->value.integer.value[1];
 *         // Set the Adec to Main Audio Output
 *     }
 *     sndout_mainaudio_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get Main Audio Output Adec Index
 *         ucontrol->value.integer.value[0] = input_type;
 *         ucontrol->value.integer.value[1] = input_port;
 *     }
 *
 * @endrst
 */
#define SNDOUT_MAINAUDIO_OUTPUT "Sndout MainAudio Output"

/**
 * sndout_optic_mode_ext_type_t
 */
typedef enum sndout_optic_mode_ext_type {
    SNDOUT_OPTIC_NONE = 0, /**< NONE */
    SNDOUT_OPTIC_PCM  = 1, /**< OPTIC Out is PCM only */
    SNDOUT_OPTIC_AUTO =
        2, /**< SPDIF Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_OPTIC_AUTO_AAC =
        3, /**< SPDIF Out is re-encoding after Mixing(TTS or effect sound), HDMI / DTV input is AAC, GST input is AC3 and others CODEC is PCM */
    SNDOUT_OPTIC_HALF_AUTO =
        4, /**< SPDIF Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_OPTIC_HALF_AUTO_AAC =
        5, /**< SPDIF Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_OPTIC_FORCED_AC3_5_1 =
        6, /**< fix DD 5.1 always out to DD5.1 although there is no data */
    SNDOUT_OPTIC_BYPASS =
        7, /**< SPDIF Out is bypassing withtout Mixing (TTS or effect sound) to reduce audio delay. It follows in/output table and Other codes are PCM output and mixed */
    SNDOUT_OPTIC_BYPASS_AAC =
        8, /**< SPDIF Out is bypassing withtout Mixing (TTS or effect sound) to reduce audio delay It follows in/output table others CODEC is PCM */
} sndout_optic_mode_ext_type_t;

/**
 * sndout_arc_mode_ext_type_t
 */
typedef enum sndout_arc_mode_ext_type {
    SNDOUT_ARC_NONE = 0, /**< NONE */
    SNDOUT_ARC_PCM  = 1, /**< ARC Out is PCM only */
    SNDOUT_ARC_AUTO =
        2, /**< ARC Out is re-encoding after Mixing(TTS or effect sound)
                                            others CODEC is PCM*/
    SNDOUT_ARC_AUTO_AAC =
        3, /**< ARC Out is re-encoding after Mixing(TTS or effect sound)
                                            HDMI / DTV input is AAC
                                            GST input is AC3
                                            others CODEC is PCM*/
    SNDOUT_ARC_AUTO_EAC3 =
        4, /**< ARC Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_ARC_AUTO_EAC3_AAC =
        5, /**< ARC Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_ARC_HALF_AUTO =
        6, /**< ARC Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_ARC_HALF_AUTO_AAC =
        7, /**< ARC Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_ARC_HALF_AUTO_EAC3 =
        8, /**< ARC Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_ARC_HALF_AUTO_EAC3_AAC =
        9, /**< ARC Out is re-encoding after Mixing(TTS or effect sound) and others CODEC is PCM */
    SNDOUT_ARC_FORCED_AC3 =
        10, /**< fix DD 5.1 always out to DD 5.1 although there is no data */
    SNDOUT_ARC_FORCED_EAC3 =
        11, /**< fix DD 5.1 always out to DD 5.1 although there is no data */
    SNDOUT_ARC_BYPASS =
        12, /**< fix DDP 5.1 always out to DDP 5.1 although there is no data but if Atmos data come in, have to change to DDP+Atmos */
    SNDOUT_ARC_BYPASS_AAC =
        13, /**< ARC Out is bypassing withtout Mixing (TTS or effect sound) to reduce audio delay. it follows in/output table and others CODEC is PCM */
    SNDOUT_ARC_BYPASS_EAC3 =
        14, /**< ARC Out is bypassing withtout Mixing (TTS or effect sound) to reduce audio delay. it follows in/output table and others CODEC is PCM */
    SNDOUT_ARC_BYPASS_EAC3_AAC =
        15, /**< ARC Out is bypassing withtout Mixing (TTS or effect sound) to reduce audio delay. it follows in/output table and others CODEC is PCM */
    SNDOUT_ARC_BYPASS_EAC3_MPEG4_AAC =
        16, /**< ARC Out is bypassing withtout Mixing (TTS or effect sound) to reduce audio delay. it follows in/output table and others CODEC is PCM. Support MPEG4 AAC(include LOAS & LATM) */
} sndout_arc_mode_ext_type_t;

/**
 * @brief put/get Spdif OutputType
 *
 * priority : 3
 *
 * @rst
 * Functional Requirements
 *   Set output type of SPDIF(IEC958) for optical sound output. When input codec
 *   is PCM, sound data path is decoder path.
 *
 *   If sound mode is "AUTO" and input codec is the one that AVR device can
 *   decode, sound output formot is same as input codec. If sound mode is "AUTO"
 *   and input codec is the one that AVR device cannot decode, sound output format
 *   is set based on in/out table. If sound mode is "SNDOUT_ARC_AUTO_AAC" and media
 *   AAC file plays, sound output is set as AC3.  The main purpose of
 *   "SNDOUT_SPDIF_BYPASS" and "SNDOUT_SPDIF_BYPASS_AAC" mode is to reduce an
 *   audio delay. (BSP should use minimum delay path)
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_spdif_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_spdif_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Spdif OutputType"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_optic_mode_ext_type_t optic_output_type
 *     value[1]: sndout_arc_mode_ext_type_t arc_output_type
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_spdif_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          sndout_optic_mode_ext_type_t optic_output_type = ucontrol->value.integer.value[0];
 *          sndout_arc_mode_ext_type_t arc_output_type = ucontrol->value.integer.value[1];
 *          // Set the Output type for optic and ARC
 *     }
 *     sndout_spdif_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get the Output type for optic and ARC
 *          ucontrol->value.integer.value[0] = optic_output_type;
 *          ucontrol->value.integer.value[1] = arc_output_type;
 *     }
 *
 * @endrst
 */
#define SNDOUT_SPDIF_OUTPUTTYPE "Sndout Spdif OutputType"

/**
 * sndout_optic_copyprotection_ext_type_t
 */
typedef enum sndout_optic_copyprotection_ext_type {
    SNDOUT_OPTIC_COPY_UNKNOWN = 0x00, /**< UNKNOWN */
    SNDOUT_OPTIC_COPY_FREE    = 0x01, /**< cp-bit : 1, L-bit : 0 */
    SNDOUT_OPTIC_COPY_NO_MORE = 0x02, /**< cp-bit : 0, L-bit : 1 */
    SNDOUT_OPTIC_COPY_ONCE    = 0x04, /**< cp-bit : 0, L-bit : 0 */
    SNDOUT_OPTIC_COPY_NEVER   = 0x08, /**< cp-bit : 0, L-bit : 1 */
} sndout_optic_copyprotection_ext_type_t;

/**
 * sndout_arc_copyprotection_ext_type_t
 */
typedef enum sndout_arc_copyprotection_ext_type {
    SNDOUT_ARC_COPY_UNKNOWN = 0x00, /**< UNKNOWN */
    SNDOUT_ARC_COPY_FREE    = 0x01, /**< cp-bit : 1, L-bit : 0 */
    SNDOUT_ARC_COPY_NO_MORE = 0x02, /**< cp-bit : 0, L-bit : 1 */
    SNDOUT_ARC_COPY_ONCE    = 0x04, /**< cp-bit : 0, L-bit : 0 */
    SNDOUT_ARC_COPY_NEVER   = 0x08, /**< cp-bit : 0, L-bit : 1 */
} sndout_arc_copyprotection_ext_type_t;

/**
 *
 * @brief put/get Spdif copy protection type
 *
 * priority : 3
 *
 * @rst
 * Functional Requirements
 *   It refers to all output in SPDIF (OPTIC & ARC), eARC, WOWCAST format and installs copy
 *   protection information in CSD (Channel Status Data) area of SPDIF/eARC/WOWCAST.
 *   When output is WOWCAST, WOWCAST use sndout_arc_copyprotection_t.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_copy_protection_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_copy_protection_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Spdif CopyProtectionInfo"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_optic_copyprotection_t optic_copyprotection
 *     value[1]: sndout_arc_copyprotection_t arc_copyprotection
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_copy_protection_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          sndout_optic_copyprotection_ext_type_t optic_category_code = ucontrol->value.integer.value[0];
 *          sndout_arc_copyprotection_ext_type_t arc_category_code = ucontrol->value.integer.value[1];
 *          // Set the Copy Protection for optic and ARC
 *     }
 *     sndout_copy_protection_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get the Copy Protection for optic and ARC
 *          ucontrol->value.integer.value[0] = optic_category_code;
 *          ucontrol->value.integer.value[1] = arc_category_code;
 *     }
 *
 * @endrst
 */
#define SNDOUT_SPDIF_COPYPROTECTIONINFO "Sndout Spdif CopyProtectionInfo"

/**
 * @brief put/get Spdif category
 *
 * priority : 3
 *
 * @rst
 * Functional Requirements
 *   Function to set Category bit in CSD (Channel Status Data) area of SPDIF
 *   (Optic & ARC) output.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_category_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_category_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Spdif CategoryCode"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: optic_category_type
 *     value[1]: arc_category_type
 *     atsc: 0x64
 *     dvb: 0x04
 *     arib: 0x0c
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_category_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          int optic_category_code = ucontrol->value.integer.value[0];
 *          int arc_category_code = ucontrol->value.integer.value[1];
 *          // Set the Output type for optic and ARC
 *     }
 *     sndout_category_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get the Output type for optic and ARC
 *          ucontrol->value.integer.value[0] = optic_category_code;
 *          ucontrol->value.integer.value[1] = arc_category_code;
 *     }
 *
 * @endrst
 */
#define SNDOUT_SPDIF_CATERGORYCODE "Sndout Spdif CategoryCode"

/**
 * @brief put/get Optic Light OnOff
 *
 * priority : 3
 *
 * @rst
 * Functional Requirements
 *   Function to turn on / off red light of optical output terminal of SPDIF
 *   output SetLightOnOff When the red light of the optical output terminal is
 *   turned off by Off, the initial value of Mute / Power bit of CSD command used
 *   for LG sound sync should be changed to off / on respectively.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_optic_light_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_optic_light_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Optic LightOnOff"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: lightOnOff (on: 1, off:0) (defalut: 0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_optic_light_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          int light_onoff = ucontrol->value.integer.value[0];
 *           // Set the light on or off
 *     }
 *     sndout_optic_light_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get the optic light status
 *          ucontrol->value.integer.value[0] = light_onoff ;
 *     }
 *
 * @endrst
 *
 */
#define SNDOUT_OPTIC_LIGHTONOFF "Sndout Optic LightOnOff"

/**
 * @brief put/get ARC OnOff
 *
 * priority : 3
 *
 * @rst
 * Functional Requirements
 *   The function of loading the audio signal of TV to external equipment through
 *   HDMI input port is called ARC, It performs on / off operation of ARC. So If
 *   "Sndout ARC OnOff" 1, ARC should be unmute physically and audio should be
 *   come out. And If "Sndout ARC OnOff" 0, ARC should be mute physically and
 *   audio should be muted. Speech data can be exported to SPDIF in unMute state.
 *
 *   As the ARC port is fixed, Port information is not transmitted.
 *
 *   ARC IP should be not enable before connecting ARC activation. Block outputting ARC by setting ARC Pin disable as default.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_arc_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_arc_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout ARC OnOff"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: arcOnOff (on:1, off:0)(default: 0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_arc_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          int light_onoff = ucontrol->value.integer.value[0];
 *          // Set arc on off
 *     }
 *     sndout_arc_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get arc on off status
 *          ucontrol->value.integer.value[0] = arcOnOff ;
 *     }
 *
 * @endrst
 */
#define SNDOUT_ARC_ONOFF "Sndout ARC OnOff"

/**
 * @brief put/get Sndout Command
 *
 * priority 3
 *
 * @rst
 * Functional Requirements
 *   LG SoundBar It is a function to control Volume, Mute, Power on / off between
 *   Optical output device and LG TV. CSD specific area of SPDIF must be modified
 *   for functional operation. And this function should be working while Sndout
 *   COMMON_OPTIC_LG opened.
 *
 *   AP will send mute and power on/off command to a driver through bMuteOnOff and
 *   bPowerOnOff boolean data. And ALSA driver should send a specific \<LG optical
 *   HEX data\> to LG sound bar through a spdif output.
 *   | ALSA param  | val | LG optical HEX data |
 *   | bMuteOnOff  |  0  | 0                   |
 *   | bMuteOnOff  |  1  | 1                   |
 *   | bPowerOnOff |  0  | 0xA1 (power off)    |
 *   | bPowerOnOff |  1  | 0x00 (power on)     |
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_optic_lg_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_optic_lg_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Optic LG"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: BarId 0xF048A6. if it want to SPDIF out with soundEngine on
 * LG SoundBar. 0xF048AB
 *     value[1]: volume,  0 ~ 100 (7th bit : mute(1), un-mute(0), 6~0th bit :
 * OSD volume)
 *     value[2]: muteOnOff (on:1, off:0)
 *     value[3]: powerOnOff (on:1, off:0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_optic_lg_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         UINT8 barID = ucontrol->value.integer.value[0];
 *         UINT8 volume = ucontrol->value.integer.value[1];
 *         UINT8 bMuteOnOff= ucontrol->value.integer.value[2];
 *         UINT8 bPowerOnOff= ucontrol->value.integer.value[2];
 *         // Send optic command
 *     }
 *     sndout_optic_lg_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get optic command status
 *         ucontrol->value.integer.value[0] = barID ;
 *         ucontrol->value.integer.value[1] = volume ;
 *         ucontrol->value.integer.value[2] = bMuteOnOff;
 *         ucontrol->value.integer.value[3] = bPowerOnOff;
 *         ucontrol->value.integer.value[4] = checksum;
 *     }
 *
 * @endrst
 *
 */
#define SNDOUT_OPTIC_LG "Sndout Optic LG"

/**
 * sndout_spk_output_ext_type_t
 */
typedef enum sndout_spk_output_ext_type {
    SNDOUT_SPK_OUTPUT_UNKNOWN =
        0, /**< Speaker output channel number is unknown */
    SNDOUT_SPK_OUTPUT_2CHANNEL =
        1, /**< Use 1 I2Ss to use 2 channels */
    SNDOUT_SPK_OUTPUT_4CHANNEL =
        2, /**< Use 2 I2Ss to use 4 channels */
    SNDOUT_SPK_OUTPUT_6CHANNEL =
        3, /**< Use 3 I2Ss to use 6 channels */
    SNDOUT_SPK_OUTPUT_8CHANNEL =
        4, /**< Use 4 I2Ss to use 8 channels */
    SNDOUT_SPK_OUTPUT_10CHANNEL =
        5, /**< Use 5 I2Ss to use 10 channels */
    SNDOUT_SPK_OUTPUT_12CHANNEL =
        6, /**< Use 6 I2Ss to use 12 channels */
    SNDOUT_SPK_OUTPUT_14CHANNEL =
        7, /**< Use 7 I2Ss to use 14 channels */
    SNDOUT_SPK_OUTPUT_16CHANNEL =
        8, /**< Use 8 I2Ss to use 16 channels */
    SNDOUT_SPK_OUTPUT_18CHANNEL =
        9, /**< Use 9 I2Ss to use 18 channels */
    SNDOUT_SPK_OUTPUT_20CHANNEL =
        10, /**< Use 10 I2Ss to use 20 channels */
} sndout_spk_output_ext_type_t;

/**
 * @brief I2S Output Channel number for 2 or 4 multi-channal
 *
 * priority:3
 *
 * @rst
 * Functional Requirements
 *   Set the speaker channel number to be used in the system and make I2S output.
 *   The LG TV MW transmits the speaker channel number required by the system
 *   through this function. The driver completes the setting according to the input value.
 *   If the requested value can not be performed due to insufficient capability of
 *   the driver, it returns NOT_OK. Currently, LG TV MW selects 1, 2, or 4 as the
 *   speaker channel number according to the requirements.
 *   If LG TV MW is set to 0, the I2S signal is halted.
 *   Since the SCLK(serial clock) of I2S is used as the MCLK(master clock) in the digital amp,
 *   I2S must be output when the function is called.
 *   I2S output should be output regardless of the currently connected output.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_spk_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // int spk_output_number = ucontrol->value.integer.value[0];
 *
 *     //
 *     // Functions
 *     //
 *     sndout_spk_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // ucontrol->value.integer.value[0] = spk_output_number;
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_spk_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          int spk_output_number = ucontrol->value.integer.value[0];
 *          // Set spk output number
 *     }
 *     sndout_spk_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get spk output number
 *          ucontrol->value.integer.value[0] = spk_output_number;
 *     }
 *
 * @endrst
 */
#define SNDOUT_SPK_OUTPUT "Sndout Spk Output"

/**
 * @brief if it's value is on(true), get NULL audio data from alsa capture
 *
 * priority 3
 *
 * @rst
 * Functional Requirements
 *   If Capture service want to disable capture, this function will called on
 *   "hw:0,10". Then driver will upload NULL(0) audio data to APP for all ALSA
 *   capture API's use cases. But PCM device for AENC("hw:0,11") and dsnoop("hw:0,12") will not affected
 *   for this function.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_capture_disable_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_capture_disable_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Capture Disable"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: capture_disable_onoff (on:1, off:0) (default:0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_capture_disable_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         int capture_disable = ucontrol->value.integer.value[0];
 *         // Set capture disable on/off
 *     }
 *     sndout_capture_disable_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get capture disable on/off
 *         ucontrol->value.integer.value[0] = capture_disable;
 *     }
 *
 * @endrst
 */
#define SNDOUT_CAPTURE_DISABLE "Sndout Capture Disable"

/**
 * @brief get inputTimeClock and inputBitrate for calculate Resampling value
 *        This function working with Sndout Open "COMMON_WISA"
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   Basically, this function is to calculate the data input speed of the input
 *   source. When two different types of devices are connected and data is
 *   exchanged, there is a performance difference between the two clocks, so the
 *   speed can not be exactly the same. This function gets the clock information
 *   used by the input source so that it can be used to find out how much
 *   difference between the speed the TV calculates and the speed the input device
 *   calculates. To calculate the time value based on the clock of the input
 *   source, we need the following two data.
 *   1. clock count of input source
 *   2. The clock rate of the input source In the user service, this function is
 *      called periodically, the count increment for a specific time interval is
 *      obtained, and then the time value is calculated by dividing by the bit
 *      rate.
 *
 *   this API should work for DTV / HDMI case.
 *
 *   In the DTV path, the system decoder continuously receives the PCR data from
 *   the broadcast signal and updates gstc. gstc continues to increase with the
 *   passage of time and PCR recovery operation. And it is the same concept as the
 *   clock counter to get through the API on the DTV path. The increasing rate of
 *   PCR data is 90Khz, which is equivalent to the clock rate to be obtained
 *   through the API in the DTV path.
 *
 *   The HDMI path may require different implementation depending on the platform.
 *   If there is a structure for receiving the clock signal of the HDMI input to
 *   the platform on which the API is to be implemented, the same can be applied
 *   as described above. If not, another alternative should be used. For example,
 *   assuming that there is an interrupt generation structure for processing input
 *   audio data, a register for counting the interrupt occurrence is created and
 *   assigned to the clock count. You can also use this method to calculate the
 *   frequency of interrupt occurrence and assign it to the clock rate value.
 *
 *   If there is a more efficient method than the example, it can be used after
 *   verification.
 *
 *   the API will be used int the user service as follow.
 *   1. 1st input_count_get, get ClockCount1, ClockRate1
 *   2. 2nd input_count_get, get ClockCount2, ClockRate2
 *   3. expect ClockRate1 = ClockRate2 = 90000
 *   4. t_in = (ClockCount2 - ClockCount1)*1000/ClockRate2 (in ms)
 *   5. t_self = (t2 - t1) (in ms)
 *   6. value to call reasmpler = 48000 * t_self / t_in
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_capture_input_count_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Capture Input TimeClock"
 *
 *     struct snd_ctl_elem_value{};
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_capture_input_count_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get TimeCount and Time Base
 *         ucontrol->value.integer.value[0] = ClockCount;
 *         ucontrol->value.integer.value[1] = ClockRate;
 *     }
 *
 * @endrst
 */
#define SNDOUT_CAPTURE_INPUT_TIMECLOCK "Sndout Capture Input TimeClock"

/**
 * @brief set Resampling frequency on runtime for WISA.
 *        This function working with Sndout Open "COMMON_WISA"
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   Basically, this function is used to fine tune the sample rate of the PCM
 *   audio data provided by the TV's audio driver.
 *
 *   When two devices are connected and data is exchanged, the client synchronizes
 *   to the clock speed of the host to exchange data.
 *
 *   When three devices are connected and data is exchanged, device2 is
 *   synchronized to device1 and device3 is synchronized to device2, which causes
 *   a problem in the overall data flow. (For example, "Blu-Ray player - TV -
 *   external speaker" is connected and sound is output)
 *
 *   Therefore, it is aimed to overcome the speed difference between device1 and
 *   device2 sync speed and device2 and device3 sync speed by finely adjusting
 *   data feeding speed by resampling device2 audio data.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_capture_output_resampling_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_capture_output_resampling_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Capture Output Resampling"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: outputFrequency(e.g 48000) (default:0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_capture_output_resampling_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         int outputFreq= ucontrol->value.integer.value[0];
 *         // Set resampling value
 *     }
 *     sndout_capture_output_resampling_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get resampling value
 *         ucontrol->value.integer.value[0] = outputFreq;
 *     }
 * @endrst
 */
#define SNDOUT_CAPTURE_OUTPUT_RESAMPLING "Sndout Capture Output Resampling"

/**
 * @brief put/get EARC OnOff
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   The function of loading the audio signal of TV to external equipment through
 *   HDMI input port is called eARC, It performs on / off operation of eARC. When
 *   eARC is on, driver should audio out as eARC Differential Mode Audio Channel
 *   which is defined in HDMISpecification 2.1 - 9.5.2. Even though ARC is on, if
 *   eARC is on, audio out should be eARC. So If "Sndout EARC OnOff" 1, ARC should
 *   be unmute physically and audio should be come out. And If "Sndout EARC OnOff"
 *   0, ARC should be mute physically and audio should be muted. Speech data can
 *   be exported to SPDIF in unMute state.
 *
 *   As the eARC port is fixed and same with ARC, Port information is not
 *   transmitted.
 *
 *   ARC IP should be not enable before connecting ARC activation. Block outputting ARC by setting ARC Pin disable as default.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_earc_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_earc_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout EARC OnOff"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: earcOnOff (on:1, off:0)(default:0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_earc_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          int earc_onoff = ucontrol->value.integer.value[0];
 *          // Set earc on off
 *     }
 *     sndout_earc_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get earc on off status
 *          ucontrol->value.integer.value[0] = earc_onoff ;
 *     }
 *
 * @endrst
 */
#define SNDOUT_EARC_ONOFF "Sndout EARC OnOff"

/**
 * @brief put/get WOWCAST OnOff
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   The function of transmitting the audio signal of TV to external equipment through
 *   Wifi is called WOWCAST, It performs on / off operation of WOWCAST. WOWCAST Audio data
 *   is captured in eARC output buffer. So, It support the audio codec that support in eARC.
 *   Ex) MAT2PCM, TrueHD, etc...
 *
 *   So If “Sndout WOWCAST OnOff” is 1, WOWCAST should be unmute physically and audio should be come out.
 *   And If “Sndout WOWCAST OnOff” is 0, WOWCAST should be mute physically and audio should be muted.
 *
 *   When output Audio data is PCM, PCM raw data is captured.
 *   When output Audio data is non-PCM, ES data(IEC-61937 format) is captured.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_wowcast_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_wowcast_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout WOWCAST OnOff"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: wowcastOnOff (on:1, off:0)(default:0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_wowcast_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          int wowcast_onoff = ucontrol->value.integer.value[0];
 *          // Set wowcast on off
 *     }
 *     sndout_wowcast_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get wowcast on off status
 *          ucontrol->value.integer.value[0] = wowcast_onoff ;
 *     }
 *
 * @endrst
 */
#define SNDOUT_WOWCAST_ONOFF "Sndout WOWCAST OnOff"

/**
 * sndout_earc_output_set_type_t
 */
typedef enum sndout_earc_output_set_type {
    SNDOUT_EARC_OUTPUT_SET_NONE = 0,
    SNDOUT_EARC_OUTPUT_SET_ORG  = 1,
    SNDOUT_EARC_OUTPUT_SET_USE  = 2,
} sndout_earc_output_set_type_t;

/**
 * sndout_earc_output_codec_type_t
 */
typedef enum sndout_earc_output_codec_type {
    SNDOUT_EARC_CODEC_PCM     = 1, /**< EARC Out type is PCM */
    SNDOUT_EARC_CODEC_AC3     = 2, /**< EARC Out type is AC3 */
    SNDOUT_EARC_CODEC_AAC     = 3, /**< EARC Out type is AAC */
    SNDOUT_EARC_CODEC_DTS     = 4, /**< EARC Out type is DTS */
    SNDOUT_EARC_CODEC_EAC3    = 5, /**< EARC Out type is EAC3 */
    SNDOUT_EARC_CODEC_TRUEHD  = 6, /**< EARC Out type is TRUEHD */
    SNDOUT_EARC_CODEC_MAT2PCM = 7, /**< EARC Out type is MAT2PCM */
    SNDOUT_EARC_CODEC_DTSHD   = 8, /**< EARC Out type is DTSHD */
    SNDOUT_EARC_CODEC_MPEG4_AAC =
        9, /**< EARC Out type is MPEG4 AAC(include LOAS & LATM) */
    SNDOUT_EARC_CODEC_DTSHD_MA = 10, /**< EARC Out type is DTSHD MA */
    SNDOUT_EARC_CODEC_DTSX_P1  = 11, /**< EARC Out type is DTS:X P1*/
} sndout_earc_output_codec_type_t;

/**
 * sndout_earc_output_channel_num_t
 */
typedef enum sndout_earc_output_channel_num {
    SNDOUT_EARC_CHNUM_NONE =
        0,                        /**< Maximum number of channel that can be output on Device considering Input audio */
    SNDOUT_EARC_CHNUM_MONO   = 1, /**< Mono */
    SNDOUT_EARC_CHNUM_STEREO = 2, /**< 2ch stereo */
    SNDOUT_EARC_CHNUM_3      = 3, /**< 3ch */
    SNDOUT_EARC_CHNUM_4      = 4, /**< 4ch */
    SNDOUT_EARC_CHNUM_5      = 5, /**< 5ch */
    SNDOUT_EARC_CHNUM_6      = 6, /**< 6ch */
    SNDOUT_EARC_CHNUM_7      = 7, /**< 7ch */
    SNDOUT_EARC_CHNUM_8      = 8, /**< 8ch */
} sndout_earc_output_channel_num_t;

/**
 * sndout_earc_output_sample_rate_t
 */
typedef enum sndout_earc_output_sample_rate {
    SNDOUT_EARC_SAMPLERATE_NONE =
        0, /**< Maximum sample rate that can be output on Device considering Input audio */
    SNDOUT_EARC_SAMPLERATE_32    = 32000,  /**< 32kHz */
    SNDOUT_EARC_SAMPLERATE_44_1  = 44100,  /**< 44.1kHz */
    SNDOUT_EARC_SAMPLERATE_48    = 48000,  /**< 48kHz */
    SNDOUT_EARC_SAMPLERATE_88_2  = 88200,  /**< 88.2kHz */
    SNDOUT_EARC_SAMPLERATE_96    = 96000,  /**< 96kHz */
    SNDOUT_EARC_SAMPLERATE_176_4 = 176400, /**< 176kHz */
    SNDOUT_EARC_SAMPLERATE_192   = 192000, /**< 192kHz */
} sndout_earc_output_sample_rate_t;

/**
 * sndout_earc_output_mix_option_t
 */
typedef enum sndout_earc_output_mix_option {
    SNDOUT_EARC_MIXOPTION_NONE =
        0, /**< Only output main audio without mixing any audio */
    SNDOUT_EARC_MIXOPTION_ALL =
        1, /**< mix main audio and others. When mixing audio, if the output is possible with defined output codec, output to PCM */
} sndout_earc_output_mix_option_t;

/**
 * sndout_output_set_type_t
 */
typedef enum {
    SNDOUT_OUTPUT_SET_NONE = 0, /**< It is not used */
    SNDOUT_OUTPUT_SET_ORG =
        1, /**< The output type is output the same as the input Audio type */
    SNDOUT_OUTPUT_SET_USE =
        2, /**< The output type is determined by the codec type, number of changel, sampling rate, and mix option */
} sndout_output_set_type_t;

/**
 * sndout_output_codec_type_t
 */
typedef enum {
    SNDOUT_CODEC_PCM     = 1, /**< Out type is PCM */
    SNDOUT_CODEC_AC3     = 2, /**< Out type is AC3 */
    SNDOUT_CODEC_AAC     = 3, /**< Out type is AAC */
    SNDOUT_CODEC_DTS     = 4, /**< Out type is DTS */
    SNDOUT_CODEC_EAC3    = 5, /**< Out type is EAC3 */
    SNDOUT_CODEC_TRUEHD  = 6, /**< Out type is TRUEHD */
    SNDOUT_CODEC_MAT2PCM = 7, /**< Out type is MAT2PCM */
    SNDOUT_CODEC_DTSHD   = 8, /**< Out type is DTSHD */
    SNDOUT_CODEC_MPEG4_AAC =
        9, /**< Out type is MPEG4 AAC(include LOAS & LATM) */
    SNDOUT_CODEC_DTSHD_MA = 10, /**< Out type is DTSHD MA */
    SNDOUT_CODEC_DTSX_P1  = 11, /**< Out type is DTS:X P1*/
} sndout_output_codec_type_t;

/**
 * sndout_output_channel_num_t
 */
typedef enum {
    SNDOUT_CHNUM_NONE =
        0,                   /**< Maximum number of channel that can be output on Device considering Input audio */
    SNDOUT_CHNUM_MONO   = 1, /**< Mono */
    SNDOUT_CHNUM_STEREO = 2, /**< 2ch stereo */
    SNDOUT_CHNUM_3      = 3, /**< 3ch */
    SNDOUT_CHNUM_4      = 4, /**< 4ch */
    SNDOUT_CHNUM_5      = 5, /**< 5ch */
    SNDOUT_CHNUM_6      = 6, /**< 6ch */
    SNDOUT_CHNUM_7      = 7, /**< 7ch */
    SNDOUT_CHNUM_8      = 8, /**< 8ch */
} sndout_output_channel_num_t;

/**
 * sndout_output_sample_rate_t
 */
typedef enum {
    SNDOUT_SAMPLERATE_NONE =
        0, /**< Maximum sample rate that can be output on Device considering Input audio */
    SNDOUT_SAMPLERATE_32    = 32000,  /**< 32kHz */
    SNDOUT_SAMPLERATE_44_1  = 44100,  /**< 44.1kHz */
    SNDOUT_SAMPLERATE_48    = 48000,  /**< 48kHz */
    SNDOUT_SAMPLERATE_88_2  = 88200,  /**< 88.2kHz */
    SNDOUT_SAMPLERATE_96    = 96000,  /**< 96kHz */
    SNDOUT_SAMPLERATE_176_4 = 176400, /**< 176kHz */
    SNDOUT_SAMPLERATE_192   = 192000, /**< 192kHz */
} sndout_output_sample_rate_t;

/**
 * sndout_output_mix_option_t
 */
typedef enum {
    SNDOUT_MIXOPTION_NONE =
        0, /**< Only output main audio without mixing any audio */
    SNDOUT_MIXOPTION_ALL =
        1, /**< mix main audio and others. When mixing audio, if the output is possible with defined output codec, output to PCM */
} sndout_output_mix_option_t;

/**
 * @brief put/get EARC Outputtype
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   :cpp:type:`sndout_output_set_type_t` tells you how to apply the output type
 *   parameter. The default setting value is :cpp:enumerator:`SNDOUT_OUTPUT_SET_NONE`.
 *
 *    - SNDOUT_OUTPUT_SET_NONE:
 *        - This value is not used after webOS22.
 *        - Output the same as the ARC output set by "Sndout Spdif OutputType".
 *        - Ignore entered parameters (codec type, number of changel, sampling
 *          rate and mix option)
 *    - SNDOUT_OUTPUT_SET_ORG:
 *        - Output with the same type as the input Audio type
 *        - Number of channel, sampling rate ignores settings and apply mix option
 *    - SNDOUT_OUTPUT_SET_USE:
 *        - Apply the set parameters (codec type, number of channel, sampling rate
 *          and mix option).
 *        - If the input audio type is changed during the eARC output, the output
 *          is discontinued and the output is output after the output is set after
 *          waiting for the "Sndout EARC Outputtype" call. The output codec type
 *          is set codec type. The default setting is :cpp:enumerator:`SNDOUT_CODEC_PCM`.
 *
 *   :cpp:type:`sndout_output_channel_num_t` sets output number of channel. The default
 *   setting value is :cpp:enumerator:`SNDOUT_CHNUM_NONE`.
 *
 *   :cpp:type:`sndout_output_sample_rate_t` sets the output sampling rate. The default
 *   setting value is :cpp:enumerator:`SNDOUT_SAMPLERATE_48`.
 *
 *   :cpp:type:`sndout_output_mix_option_t` sets the mix option. The default setting is
 *   :cpp:enumerator:`SNDOUT_MIXOPTION_NONE`.
 *
 *   If LG MW requests settings that Driver can not perform, the driver outputs
 *   the audio to the default.
 *
 *   If media set slow or fast playback speeds except default playback speed, the driver must set the output type to 2ch PCM.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     adc_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     adc_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout EARC Outputtype"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_output_set_type_t set_type (default: 0)
 *     value[1]: sndout_output_codec_type_t codec_type (default: 0)
 *     value[2]: sndout_output_channel_num_t channel_num (default: 0)
 *     value[3]: sndout_output_sample_rate_t sample_rete (default: 0)
 *     value[4]: sndout_output_mix_option_t mix_option (default: 0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_earc_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Set the Output type for eARC
 *         sndout_output_set_type_t set_type = ucontrol->value.integer.value[0];
 *         sndout_output_codec_type_t codec_type = ucontrol->value.integer.value[1];
 *         sndout_output_channel_num_t channel_num = ucontrol->value.integer.value[2];
 *         sndout_output_sample_rate_t sample_rate = ucontrol->value.integer.value[3];
 *         sndout_output_mix_option_t mix_option = ucontrol->value.integer.value[4];
 *     }
 *     sndout_earc_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get the Output type for eARC
 *         ucontrol->value.integer.value[0] = set_type;
 *         ucontrol->value.integer.value[1] = codec_type;
 *         ucontrol->value.integer.value[2] = channel_num;
 *         ucontrol->value.integer.value[3] = sample_rate;
 *         ucontrol->value.integer.value[4] = mix_option;
 *     }
 *
 * @endrst
 */
#define SNDOUT_EARC_OUTPUT_TYPE "Sndout EARC Outputtype"

/**
 * @brief put/get eAC3 ATMOS Encode OnOff
 *
 * priority 3
 *
 * @rst
 * Functional Requirements
 *   If on, driver should encode atmos for eARC/ARC out.
 *   And if off, driver should not encode atmos for eARC/ARC out.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_eac3_atmos_encode_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_eac3_atmos_encode_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout eAC3 ATMOS Encode OnOff"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: eac3_atmos_encode_onoff (on:1, off:0)(default:1)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_eac3_atmos_encode_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int open_status = ucontrol->value.integer.value[0]; // On/Off atmos encoder
 *     }
 *     sndout_eac3_atmos_encode_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get atmos encode status
 *         ucontrol->value.integer.value[0] = eac3_atmos_encode_onoff;
 *     }
 *
 * @endrst
 */
#define SNDOUT_EAC3_ATMOS_ENCODE_ONOFF "Sndout eAC3 ATMOS Encode OnOff"

/**
 * @brief put/get OPTIC Outputtype
 *
 * priority 3
 *
 * @rst
 * Functional Requirements
 *   :cpp:type:`sndout_output_set_type_t` tells you how to apply the output type
 *   parameter. The default setting value is :cpp:enumerator:`SNDOUT_OUTPUT_SET_NONE`.
 *
 *    - SNDOUT_OUTPUT_SET_NONE:
 *        - It is not used in "Sndout OPTIC Outputtype".
 *    - SNDOUT_OUTPUT_SET_ORG:
 *        - Output with the same type as the input Audio type
 *        - Number of channel, sampling rate ignores settings and apply mix option
 *    - SNDOUT_OUTPUT_SET_USE:
 *        - Apply the set parameters (codec type, number of channel, sampling rate
 *          and mix option).
 *        - If the input audio type is changed during the OPTIC output, the output
 *          is discontinued and the output is output after the output is set after
 *          waiting for the "Sndout OPTIC Outputtype" call. The output codec type
 *          is set codec type. The default setting is :cpp:enumerator:`SNDOUT_CODEC_PCM`.
 *
 *   :cpp:type:`sndout_output_codec_type_t` set output codec. Returns an error(Error code is "EINVAL") if the driver
 *   cannot support the output codec of the OPTIC or OPTIC output cannot support the output codec.
 *
 *   :cpp:type:`sndout_output_channel_num_t` sets output number of channel. The default
 *   setting value is :cpp:enumerator:`SNDOUT_CHNUM_NONE`.
 *
 *   :cpp:type:`sndout_output_sample_rate_t` sets the output sampling rate. The default
 *   setting value is :cpp:enumerator:`SNDOUT_SAMPLERATE_48`.
 *
 *   :cpp:type:`sndout_output_mix_option_t` sets the mix option. The default setting is
 *   :cpp:enumerator:`SNDOUT_MIXOPTION_NONE`.
 *
 * If media set slow or fast playback speeds except default playback speed, the driver must set the output type to 2ch PCM.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_optic_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_optic_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *      "Sndout EARC Outputtype"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_output_set_type_t set_type (default: 0)
 *     value[1]: sndout_output_codec_type_t codec_type (default: 0)
 *     value[2]: sndout_output_channel_num_t channel_num (default: 0)
 *     value[3]: sndout_output_sample_rate_t sample_rete (default: 0)
 *     value[4]: sndout_output_mix_option_t mix_option (default: 0)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_optic_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Set the Output type for OPTIC
 *         sndout_output_set_type_t set_type = ucontrol->value.integer.value[0];
 *         sndout_output_codec_type_t codec_type = ucontrol->value.integer.value[1];
 *         sndout_output_channel_num_t channel_num = ucontrol->value.integer.value[2];
 *         sndout_output_sample_rate_t sample_rate = ucontrol->value.integer.value[3];
 *         sndout_output_mix_option_t mix_option = ucontrol->value.integer.value[4];
 *     }
 *     sndout_optic_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get the Output type for OPTIC
 *         ucontrol->value.integer.value[0] = set_type;
 *         ucontrol->value.integer.value[1] = codec_type;
 *         ucontrol->value.integer.value[2] = channel_num;
 *         ucontrol->value.integer.value[3] = sample_rate;
 *         ucontrol->value.integer.value[4] = mix_option;
 *     }
 *
 * @endrst
 */
#define SNDOUT_OPTIC_OUTPUT_TYPE "Sndout OPTIC Outputtype"

/**
 *
 * @brief put/get ARC Outputtype
 *
 * priority 3
 *
 * @rst
 * Functional Requirements
 *   :cpp:type:`sndout_output_set_type_t` tells you how to apply the output type
 *   parameter. The default setting value is :cpp:enumerator:`SNDOUT_OUTPUT_SET_NONE`.
 *
 *    - SNDOUT_OUTPUT_SET_NONE:
 *        - It is not used in "Sndout ARC Outputtype".
 *    - SNDOUT_OUTPUT_SET_ORG:
 *        - Output with the same type as the input Audio type
 *        - Number of channel, sampling rate ignores settings and apply mix option
 *    - SNDOUT_OUTPUT_SET_USE:
 *        - Apply the set parameters (codec type, number of channel, sampling rate
 *          and mix option).
 *        - If the input audio type is changed during the ARC output, the output
 *          is discontinued and the output is output after the output is set after
 *          waiting for the "Sndout ARC Outputtype" call. The output codec type
 *          is set codec type. The default setting is :cpp:enumerator:`SNDOUT_CODEC_PCM`.
 *
 *   :cpp:type:`sndout_output_codec_type_t` set output codec. Returns an error(Error code is "EINVAL") if the driver
 *   cannot support the output codec of the ARC or ARC output cannot support the output codec.
 *
 *   :cpp:type:`sndout_output_channel_num_t` sets output number of channel. The default
 *   setting value is :cpp:enumerator:`SNDOUT_CHNUM_NONE`.
 *
 *   :cpp:type:`sndout_output_sample_rate_t` sets the output sampling rate. The default
 *   setting value is :cpp:enumerator:`SNDOUT_SAMPLERATE_48`.
 *
 *   :cpp:type:`sndout_output_mix_option_t` sets the mix option. The default setting is
 *   :cpp:enumerator:`SNDOUT_MIXOPTION_NONE`.
 *
 * If media set slow or fast playback speeds except default playback speed, the driver must set the output type to 2ch PCM.
 *
 * Performance Requirements
 *   | The response time of this function should be within 10ms,
 *   | if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_arc_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_arc_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *      "Sndout ARC Outputtype"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_output_set_type_t set_type (default: 0)
 *     value[1]: sndout_output_codec_type_t codec_type (default: 0)
 *     value[2]: sndout_output_channel_num_t channel_num (default: 0)
 *     value[3]: sndout_output_sample_rate_t sample_rete (default: 0)
 *     value[4]: sndout_output_mix_option_t mix_option (default: 0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_arc_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *        // Set the Output type for ARC
 *        sndout_output_set_type_t set_type = ucontrol->value.integer.value[0];
 *        sndout_output_codec_type_t codec_type = ucontrol->value.integer.value[1];
 *        sndout_output_channel_num_t channel_num = ucontrol->value.integer.value[2];
 *        sndout_output_sample_rate_t sample_rate = ucontrol->value.integer.value[3];
 *        sndout_output_mix_option_t mix_option = ucontrol->value.integer.value[4];
 *     }
 *     sndout_arc_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *        // Get the Output type for ARC
 *        ucontrol->value.integer.value[0] = set_type;
 *        ucontrol->value.integer.value[1] = codec_type;
 *        ucontrol->value.integer.value[2] = channel_num;
 *        ucontrol->value.integer.value[3] = sample_rate;
 *        ucontrol->value.integer.value[4] = mix_option;
 *     }
 *
 * @endrst
 */
#define SNDOUT_ARC_OUTPUT_TYPE "Sndout ARC Outputtype"

/**
 *
 * @brief put/get WOWCAST Outputtype
 *
 * priority 3
 *
 * @rst
 * Functional Requirements
 *   :cpp:type:`sndout_output_set_type_t` tells you how to apply the output type
 *   parameter. The default setting value is :cpp:enumerator:`SNDOUT_OUTPUT_SET_NONE`.
 *
 *    - SNDOUT_OUTPUT_SET_NONE:
 *        - It is not used in "Sndout WOWCAST Outputtype".
 *    - SNDOUT_OUTPUT_SET_ORG:
 *        - Output with the same type as the input Audio type
 *        - Number of channel, sampling rate ignores settings and apply mix option
 *    - SNDOUT_OUTPUT_SET_USE:
 *        - Apply the set parameters (codec type, number of channel, sampling rate
 *          and mix option).
 *        - If the input audio type is changed during the WOWCAST output, the output
 *          is discontinued and the output is output after the output is set after
 *          waiting for the "Sndout WOWCAST Outputtype" call. The output codec type
 *          is set codec type. The default setting is :cpp:enumerator:`SNDOUT_CODEC_PCM`.
 *
 *   :cpp:type:`sndout_output_codec_type_t` set output codec. Returns an error(Error code is "EINVAL") if the driver
 *   cannot support the output codec of the WOWCAST or WOWCAST output cannot support the output codec.
 *
 *   :cpp:type:`sndout_output_channel_num_t` sets output number of channel. The default
 *   setting value is :cpp:enumerator:`SNDOUT_CHNUM_NONE`.
 *
 *   :cpp:type:`sndout_output_sample_rate_t` sets the output sampling rate. The default
 *   setting value is :cpp:enumerator:`SNDOUT_SAMPLERATE_48`.
 *
 *   :cpp:type:`sndout_output_mix_option_t` sets the mix option. The default setting is
 *   :cpp:enumerator:`SNDOUT_MIXOPTION_NONE`.
 *
 * Performance Requirements
 *   | The response time of this function should be within 10ms,
 *   | if there are no special reasons.
 *
 * If media set slow or fast playback speeds except default playback speed, the driver must set the output type to 2ch PCM.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_wowcast_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_wowcast_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *      "Sndout WOWCAST Outputtype"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_output_set_type_t set_type (default: 0)
 *     value[1]: sndout_output_codec_type_t codec_type (default: 0)
 *     value[2]: sndout_output_channel_num_t channel_num (default: 0)
 *     value[3]: sndout_output_sample_rate_t sample_rete (default: 0)
 *     value[4]: sndout_output_mix_option_t mix_option (default: 0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_wowcast_outputtype_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *        // Set the Output type for WOWCAST
 *        sndout_output_set_type_t set_type = ucontrol->value.integer.value[0];
 *        sndout_output_codec_type_t codec_type = ucontrol->value.integer.value[1];
 *        sndout_output_channel_num_t channel_num = ucontrol->value.integer.value[2];
 *        sndout_output_sample_rate_t sample_rate = ucontrol->value.integer.value[3];
 *        sndout_output_mix_option_t mix_option = ucontrol->value.integer.value[4];
 *     }
 *     sndout_wowcast_outputtype_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *        // Get the Output type for WOWCAST
 *        ucontrol->value.integer.value[0] = set_type;
 *        ucontrol->value.integer.value[1] = codec_type;
 *        ucontrol->value.integer.value[2] = channel_num;
 *        ucontrol->value.integer.value[3] = sample_rate;
 *        ucontrol->value.integer.value[4] = mix_option;
 *     }
 *
 * @endrst
 */
#define SNDOUT_WOWCAST_OUTPUT_TYPE "Sndout WOWCAST Outputtype"

/**
 * @brief put/get capture path point
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   :type:`sndout_capture_path_t` tells the point where capture would be done
 *   after this function called, audio data would be recorded by "arecord" with below options
 *
 *   - port: hw:0,13
 *   - format: signed little endian 32bit
 *   - sample rate: 48,000 Hz
 *   - channels: 2
 *   - path: :type:`sndout_capture_path_t`
 *
 * Parameter (path point enum)
 *   The default setting value is :type:`SNDOUT_CAPTURE_PATH_DEFAULT`.
 *   refer to :type:`sndout_capture_path_t` to understand parameter
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_capture_path_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_capture_path_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Audio Capture Path"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_capture_path_t capture_path(default:0)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_capture_path_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Set capture path
 *         // if can't capture, then return fail and capture path setting to default path
 *         int capture_path = ucontrol->value.integer.value[0];
 *
 *     }
 *     sndout_capture_path_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get capture path info.
 *         // if setting fail or capturing path is not match with current status, return fail and capture path is default value(0)
 *         ucontrol->value.integer.value[0] = capture_path;
 *     }
 *
 * @endrst
 */
#define SNDOUT_CAPTURE_PATH_POINT "Sndout Audio Capture Path"


/**
 * @brief put/get EARC MS12 SP50 setting OnOff
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   SP50 is one of the system parameters of Dolby MS12 Multistream Decoder Implementation.
 *   SP50 is "Enforce single object audio element"
 *   Restricts the object audio metadata that is generated or transcoded in the PCM renderer
 *   to single object audio elements only.
 *   If set, custom downmix metadata is no longer encoded in the object audio metadata.
 *   Dolby MS12 SP50 setting for eARC MAT output : This setting support only above MS12 IIDK 2.6.x.
 *
 *   Using example.
 *   When outputting to eARC equipment that supports only MAT Profiles 1 and 2, the SP50 setting is set to '1'.
 *   When outputting to eARC equipment that supports all MAT Profiles 1 to 4, the SP50 setting is set to '0'.(0, Default)
 *
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   Dolby MS12 SP50 setting for eARC MAT output : This setting support only above MS12 IIDK 2.6.x.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_earc_ms12_sp50_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_earc_ms12_sp50_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout EARC MS12 SP50 OnOff"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: earc_ms12_sp50_OnOff (on:1, off:0)(default:0)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_earc_ms12_sp50_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Set earc ms12 sp50 on off
 *          int earc_mat_sp50_onoff = ucontrol->value.integer.value[0];
 *     }
 *     sndout_earc_ms12_sp50_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // Get earc ms12 sp50 on off status
 *          ucontrol->value.integer.value[0] = earc_ms12_sp50_onoff ;
 *     }
 *
 * @endrst
 */
#define SNDOUT_EARC_MS12_SP50_ONOFF "Sndout EARC MS12 SP50 OnOff"

/**
 * @brief get Dolby MS12 IIDK Version
 *
 * priority 3
 *
 * @rst
 * Functional Requirements
 *   To check Dolby MS12 IIDK Version of driver, this function returns major version and minor_version of dolby MS12 IIDK.
 *   This function will be used to set up different functions depending on the IIDK version.
 *   Dolby MS12 Multistream Decoder is consisted IIDK(Integration Implementation Developement Kit)
 *   and SDK(System Developement Kit).
 *   Examples of use this function
 *     1.Dolby MS12 SP50 setting for eARC MAT output : This setting support only above MS12 IIDK 2.6.x.
 *
 *   MS12 IIDK Version example V2.4.1 -> Major version is 2 and Minor version is 4. Other versions '1' (like bugfix release) is ignored.
 *   MS12 IIDK Version example V2.6.2 -> Major version is 2 and Minor version is 6. Other versions '2' (like bugfix release) is ignored.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   Dolby MS12 SP50 setting for eARC MAT output : This setting support only above MS12 IIDK 2.6.x.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     dolby_ms12_iidk_version_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *      "Dolby MS12 IIDK Version"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: int major_version (default: 0)
 *     value[1]: int minor_version (default: 0)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     dolby_ms12_iidk_version_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get the Version of Dolby MS12 IIDK
 *         ucontrol->value.integer.value[0] = major_version;
 *         ucontrol->value.integer.value[1] = minor_version;
 *     }
 *
 * @endrst
 */
#define DOLBY_MS12_IIDK_VERSION "Dolby MS12 IIDK Version"

/**
 * sndout_dafc_output_type_t
*/
typedef enum sndout_dafc_output_type_t{
    SNDOUT_DAFC_OUTPUT_NONE         = 0,  /**< default type which would not out audio data from DAFC capture path */
    SNDOUT_DAFC_OUTPUT_WIFI         = 1,  /**< captured data of DAFC is out through Wi-Fi such as DTS Play-Fi */
    SNDOUT_DAFC_OUTPUT_BT           = 2,  /**< captured data of DAFC is out through Bluetooth such as LE Audio */
    SNDOUT_DAFC_OUTPUT_MAX,               /**< maximum enum of DAFC output type */
}  sndout_dafc_output_type_t;

/**
 * @brief put/get DAFC output type
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   | :type:`sndout_dafc_output_type_t` tells which protocol would be used to transmit audio data from DAFC FlexRenderer
 *   | whth below setting, if this API is set, user could capture audio data from DAFC output by ALSA capture device hw:0,15
 *   | - sound output setting (open, connect) as :c:macro:`COMMON_DAFC`
 *   | Captured audio data would be transmitted to external speakers by Wifi or BT  protocol,
 *   | and be played to ALSA playback device hw:0,8 which would be out to TV SPK
 *   | To output audio data to TVSPK + Ext. Speakers, sound output setting for TV SPK (:c:macro:`COMMON_SPK`) should be done also.
 *   | According to the protocol which uses captured audio data, audio data for TV SPK and external speakers could be synchronized.
 *
 * Parameter (DAFC Output Type).
 *   Default value is :type:`SNDOUT_DAFC_OUTPUT_NONE` (0).
 *
 *   - :type:`SNDOUT_DAFC_OUTPUT_NONE` (0):
 *      - audio data from DAFC would not be transmitted to out of TV.
 *   - :type:`SNDOUT_DAFC_OUTPUT_WIFI` (1):
 *      - audio data from DAFC would be transmitted to Wi-Fi protocol such as DTS Play-Fi
 *      - audio data out Wi-Fi protocol would be passed to Ext. Speaker (with TV SPK if needed)
 *   - :type:`SNDOUT_DAFC_OUTPUT_BT` (2):
 *      - audio data from DAFC would be transmitted for Bluetooth protocol such as LE Audio
 *      - more info about Bluetooth protocol of DAFC is TBD
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_dafc_output_type_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_dafc_output_type_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout DAFC Output Type"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_dafc_output_type_t dafc_output_type (default:0)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_dafc_output_type_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Set DAFC Output Type
 *         int dafc_output_type = ucontrol->value.integer.value[0];
 *
 *     }
 *     sndout_dafc_output_type_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get DAFC Output Type
 *         ucontrol->value.integer.value[0] = dafc_output_type;
 *     }
 *
 * @endrst
 */
#define SNDOUT_DAFC_OUTPUT_TYPE "Sndout DAFC Output Type"


/**
 * @brief put/get Center Extraction Mode
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   | If this API is set, center part of audio output data would be extracted by input parameter (1 : on) and recovered by input parameter (0 : off)
 *   | This requirement was originally made for DAFC Calibration
 *   | But it could be used for other requirement for the future
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_center_extraction_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_center_extraction_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Center Extraction OnOff"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: onoff (on:1, off:0)(default:1)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_center_extraction_onoff_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int open_status = ucontrol->value.integer.value[0]; // On/Off center extraction
 *     }
 *     sndout_center_extraction_onoff_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get center extrcation status
 *         ucontrol->value.integer.value[0] = onoff;
 *     }
 *
 * @endrst
 */
#define SNDOUT_CENTER_EXTRACTION_ONOFF "Sndout Center Extraction OnOff"

/**
 * @brief put/get Input Downmix Enable
 * priority : 4
 *
 * @rst
 * Functional Requirements
 *   Function for downmix enable/disable of audio data from Input resource(ADEC, AMIXER)
 *   If the function is set to 1 with Input resource, the audio data from input source which set to 1
 *   should out wihtout downmix
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     input_downmix_enable_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     input_downmix_enable_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Input Downmix Enable"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: input_type
 *        COMMON_NO_INPUT     = 0x0000
 *        COMMON_INPUT_ADEC   = 0x0001
 *        COMMON_INPUT_AMIXER = 0x0010
 *     value[1]: input_port_num
 *        Adec supports 0~1
 *        Amixer supports 0~7
 *     value[2]: donwmix status (enable:1, disable:0) (default:1)
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     input_downmix_enable_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int input_type = ucontrol->value.integer.value[0]; // type (ADEC, AMIXER)
 *         int input_port_num = ucontrol->value.integer.value[1]; // port
 *         int downmix_status = ucontrol->value.integer.value[2]; // 0, 1 (Disable/Enable)
 *     }
 *
 *     input_downmix_enable_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // get status of input down mix enable
 *         ucontrol->value.integer.value[0] = 0 ; // := 0
 *         ucontrol->value.integer.value[1] = adec0_input_downmix_enable;
 *         ucontrol->value.integer.value[2] = 1 ; // := 1
 *         ucontrol->value.integer.value[3] = adec1_input_downmix_enable;
 *         ucontrol->value.integer.value[4] = 2 ; // := 2
 *         ucontrol->value.integer.value[5] = adec2_input_downmix_enable;
 *         ucontrol->value.integer.value[6] = 3 ; // := 3
 *         ucontrol->value.integer.value[7] = adec3_input_downmix_enable;
 *         ucontrol->value.integer.value[8] = 0; // := 0
 *         ucontrol->value.integer.value[9] = amixer0_input_downmix_enable;
 *         ucontrol->value.integer.value[10] = 1; // := 1
 *         ucontrol->value.integer.value[11] = amixer1_input_downmix_enable;
 *         ucontrol->value.integer.value[11] = 2; // := 2
 *         ucontrol->value.integer.value[12] = amixer2_input_downmix_enable;
 *         ucontrol->value.integer.value[13] = 3; // := 3
 *         ucontrol->value.integer.value[14] = amixer3_input_downmix_enable;
 *         ucontrol->value.integer.value[15] = 4; // := 4
 *         ucontrol->value.integer.value[16] = amixer4_input_downmix_enable;
 *         ucontrol->value.integer.value[17] = 5; // := 5
 *         ucontrol->value.integer.value[18] = amixer5_input_downmix_enable;
 *         ucontrol->value.integer.value[19] = 6; // := 6
 *         ucontrol->value.integer.value[20] = amixer6_input_downmix_enable;
 *         ucontrol->value.integer.value[21] = 7; // := 7
 *         ucontrol->value.integer.value[22] = amixer7_input_downmix_enable;
 *     }
 * @endrst
 */
#define INPUT_DOWNMIX_ENABLE "Input Downmix Enable"

/**
* @brief get HW buffer write time
* @li priority 1
*
* Get HW buffer write time.
* This function returns the GSTC (Global System Time Counter) value at the time when the first audio data is output to the speaker in ALSA DMA. 
* It is used to check the time when audio output starts.
*
* @code
* static int hw_buffer_write_time_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
* {
*    unsigned long long hwBufWriteTime = 0;
*
*    hwBufWriteTime = aud_hal_get_hw_buffer_write_time ();
*    ucontrol->value.integer64.value[0] = hwBufWriteTime;
*    info ("hwBufWriteTime %llu\n", hwBufWriteTime);
*
*    return 0;
* }
* @endcode
*
*
*
* @param[out] hw buffer write time integer64 := 0
*
* @return 0 if it success. Otherwise:
* @li -EBUSY       Internal driver error happened
* @li -EINVAL      Invalid argument
* @li -EALREADY    Operation already in progress
*/
#define HW_BUFFER_WRITE_TIME "HW Buffer Write Time"

/**
* @brief get Audio Buffer Latency
* @li priority 1
*
* Get Audio Buffer Size.
* This function returns the Audio DSP or Audio processor's buffer latency at the current time. 
* If audio data is put into the buffer at the current time, it will be delayed by this amount of time before being actually output.
*
* @code
* static int audio_buffer_latency_get (struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
* {
*    unsigned int audioBufferLatency = 0;
*
*    audioBufferLatency = aud_hal_get_audio_buffer_latency ();
*    ucontrol->value.integer.value[0] = audioBufferLatency;
*    info ("audioBufferLatency %d\n", audioBufferLatency);
*
*    return 0;
* }
* @endcode
*
*
*
* @param[out] audio buffer latency integer := 0
*
* @return 0 if it success. Otherwise:
* @li -EBUSY       Internal driver error happened
* @li -EINVAL      Invalid argument
* @li -EALREADY    Operation already in progress
*/
#define AUDIO_BUFFER_LATENCY "Audio Buffer Latency"

/**
 * @brief PLL Control Information
 * @li priority 1
 *
 * This function returns the Audio interrupt counter and GSTC (Global System Time Counter) at the current time.
 * It is used to calculate the sampling frequency of the audio currently being output.
 *
 * @code
 * static int pll_control_info_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *    long long intNum = 0;
 *    long long ckCnt = 0;
 *    long long reserve1 = 0;
 *    long long reserve2 = 0;
 *
 *    // Retrieve the information from DSP
 *    intNum = dsp_get_interrupt_number();
 *    ckCnt = dsp_get_clock_count();
 *    reserve1 = dsp_get_reserve1();
 *    reserve2 = dsp_get_reserve2();
 *
 *    ucontrol->value.integer64.value[0] = intNum;
 *    ucontrol->value.integer64.value[1] = ckCnt;
 *    ucontrol->value.integer64.value[2] = reserve1;
 *    ucontrol->value.integer64.value[3] = reserve2;
 *
 *    info("PLL Control Info - IntNum: %lld, CkCnt: %lld, Reserve1: %lld, Reserve2: %lld\n", intNum, ckCnt, reserve1, reserve2);
 *
 *    return 0;
 * }
 * @endcode
 *
 * @param[out] PLL control information integer64: [0] = intNum, [1] = ckCnt, [2] = reserve1, [3] = reserve2
 *
 * @return 0 if it succeeds. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define PLL_CONTROL_INFO "PLL Control Info"

/**
 * @brief Get STC System MICOM Clock Time
 * @li priority 1
 *
 * This function returns the current GSTC (Global System Time Counter) value, system time value, and MICOM clock time. 
 * It is used to synchronize the current GSTC, system time, and MICOM time.
 *
 * @code
 * static int sndout_stc_system_micom_clock_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *    unsigned long long gstc = 0;
 *    struct timespec64 m_timespec;
 *    unsigned long long micom = 0;
 *
 *    // Retrieve GSTC (Global System Time Counter)
 *    gstc = aud_hal_get_gstc_33bits();
 *    ucontrol->value.integer64.value[0] = gstc;
 *
 *    // Retrieve system time
 *    ktime_get_raw_ts64(&m_timespec);
 *    ucontrol->value.integer64.value[1] = m_timespec.tv_sec;
 *    ucontrol->value.integer64.value[2] = m_timespec.tv_nsec;
 *
 *    // Retrieve MICOM clock time
 *    MICOM_REG_READ(MICOM_CLOCK_REG, micom);
 *    ucontrol->value.integer64.value[3] = micom;
 *
 *    info("gstc %20llu\n", gstc);
 *    info("system %20llu.%09lu\n", m_timespec.tv_sec, m_timespec.tv_nsec);
 *    info("micom %llu\n", micom);
 *
 *    return 0;
 * }
 * @endcode
 *
 * @param[out] STC system and MICOM clock time integer64: [0] = gstc, [1] = m_timespec.tv_sec, [2] = m_timespec.tv_nsec, [3] = micom
 *
 * @return 0 if it succeeds. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 */
#define STC_SYSTEM_MICOM_CLOCK_TIME "STC SYSTEM MICOM Clock Time"

/**
 * dafc_micom_pin_mode_t
*/
typedef enum micom_pin_mode_t{
    MICOM_PIN_MODE_GPIO_INPUT = 0, /**< Set the property of the "WOL/WIFI_POWER_ON" pin to a general GPIO(input). */
    MICOM_PIN_MODE_INTERRUPT = 1,  /**< Set the property of the "WOL/WIFI_POWER_ON" pin to Interrupt. */
}  micom_pin_mode_t;

/**
 * @brief Put Micom Pin Mode
 * @li priority 4
 *
  * @rst
 * Functional Requirements
 *   WOWCAST3.0 uses two types of time information for time synchronization between speakers to synchronize audio: network TSF and system clock.
 *   The "WOL/WIFI_POWER_ON" pin is no longer used after the TV is turned on, so we change it to Interrupt mode and use it to get the system clock information.
 *   This API should be able to set the interrupt mode by setting the register of the "WOL/WIFI_POWER_ON" pin of the SoC.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms, if there are no special reasons.
 *   There should be no build issue in kdriver, hal-libs, kadaptor of webos4tv branch.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     micom_pin_mode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     micom_pin_mode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Micom Pin Mode"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: micom_pin_mode_t
 *        MICOM_PIN_MODE_GPIO_INPUT     = 0x0
 *        MICOM_PIN_MODE_INTERRUPT      = 0x1
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     micom_pin_mode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get Micom pin mode
 *         ucontrol->value.integer.value[0] = mode;
 *     }
 *
 *     micom_pin_mode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Set Micom pin mode
 *         int mode = ucontrol->value.integer.value[0];
 *
 *         // Set the register value to match the SoC.
 *         // If the SoC does not support WOWCAST3.0, this function will do nothing.
 *
 *         // Example) O22N3/O24N
 *         // If mode == MICOM_PIN_MODE_INTERRUPT, set the value as below
 *         // O22N3  ->  0xF0103400, [1] set '0'
 *         //            0xF0103404, [1] set '0'
 *         //            0xF0103408, [1] set '0'
 *         //            0xF010340C, [1] set '0'
 *         //            0xF0103410, [1] set '1'
 *         //            0xF010341C, [1] set '1'
 *         // O24N   ->  0xF0103400, [1] set '0'
 *         //            0xF0103404, [1] set '0'
 *         //            0xF0103408, [1] set '0'
 *         //            0xF010340C, [1] set '0'
 *         //            0xF0103410, [1] set '1'
 *         //            0xF010341C, [1] set '1'
 *
 *         // If mode == MICOM_PIN_MODE_GPIO_INPUT, set the value as below.
 *         // O22N3  ->  0xF0103400, [1] set '0'
 *         //            0xF0103410, [1] set '0'
 *         // O24N   ->  0xF0103400, [1] set '0'
 *         //            0xF0103410, [1] set '0'
 *     }
 * @endrst
 */
#define MICOM_PIN_MODE "Micom Pin Mode"

/**
 * sndout_spk_sampling_frequeny_type
*/
typedef enum sndout_spk_sampling_frequency_type_t{
    SNDOUT_SPK_SAMPLING_FREQUENCY_24KHZ     = 24000,  /**< 24kHz */
    SNDOUT_SPK_SAMPLING_FREQUENCY_48KHZ     = 48000,  /**< 48kHz */
    SNDOUT_SPK_SAMPLING_FREQUENCY_96KHZ     = 96000,  /**< 96kHz */
    SNDOUT_SPK_SAMPLING_FREQUENCY_192KHZ    = 192000,  /**< 192kHz */
}  sndout_spk_sampling_frequency_type_t;

/**
 * @brief put/get Speaker Sampling Frequencey
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   | :type:`sndout_spk_sampling_frequency_type_t` tells sampling frequency for speaker output
 *   | if :c:macro:`SNDOUT_SPK_SAMPLING_FREQUENCY` is called with :type:`sndout_spk_sampling_frequency_type_t`,
 *   | BSP would modify sampling frequency of audio data which would go through speakers connected
 *
 * Parameter (Speaker Sampling Frequencey Type).
 *   Default value is :type:`SNDOUT_SPK_SAMPLING_FREQUENCY_48KHZ` (48000).
 *   Enum could be modified if other frequency is required
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_spk_sampling_frequency_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_spk_sampling_frequency_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Spk Sampling Frequency"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: sndout_spk_sampling_frequency_type_t frequency (default:0)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_spk_sampling_frequency_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Set Speaker Sampling Frequency
 *         int frequency = ucontrol->value.integer.value[0];
 *
 *     }
 *     sndout_spk_sampling_frequency_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get Speaker Sampling Frequency
 *         ucontrol->value.integer.value[0] = frequency;
 *     }
 *
 * @endrst
 */
#define SNDOUT_SPK_SAMPLING_FREQUENCY "Sndout Spk Sampling Frequency"

/**
 * @brief speaker configuration enum
 */
typedef enum decoder_spk_configuration_type {
    DEC_SPK_CONF_LR                                     = 0, /**< "lr" */
    DEC_SPK_CONF_LR_LFE_LRE                             = 1, /**< "lr:lfe:lre" */
    DEC_SPK_CONF_LR_C_LFE                               = 2, /**< "lr:c:lfe" */
    DEC_SPK_CONF_LR_C_LFE_LRE                           = 3, /**< "lr:c:lfe:lre" */
    DEC_SPK_CONF_LR_C_LRS_LFE                           = 4, /**< "lr:c:lrs:lfe" */
    DEC_SPK_CONF_LR_C_LRS_LFE_LRE                       = 5, /**< "lr:c:lrs:lfe:lre" */
    DEC_SPK_CONF_LR_C_LRS_LRRS_LFE_LRE                  = 6, /**< "lr:c:lrs:lrrs:lfe:lre" */
    DEC_SPK_CONF_LR_C_LRS_LRRS_LFE_LRE_LRSE             = 7, /**< "lr:c:lrs:lrrs:lfe:lre:lrse" */
    DEC_SPK_CONF_LR_C_LRS_LRRS_LRW_LFE_LRE_LRSE         = 8, /**< "lr:c:lrs:lrrs:lrw:lfe:lre:lrse" */
    DEC_SPK_CONF_LR_C_LRS_LRRS_LRW_LFE_LRE_LRSE_LRRSE   = 9, /**< "lr:c:lrs:lrrs:lrw:lfe:lre:lrse:lrrse" */
    DEC_SPK_CONF_MAXIMUM,
} decoder_spk_configuration_type_t;


/**
 * @brief
 *
 * priority : 1
 *
 * @rst
 * Functional Requirements
 *   | Speaker configuration to notify to audio decoder
 *   | It would be set for dolby decoder to map decoder's output channel info to speakers channel info
 *   | 1) For DAFC output, FlexRenderer would make 7.1ch audio output and channel mapping would be done by FlexRenderer
 *   | 2) For Non-DAFC output, dolby decoder would make audio output channel according to :c:macro:`DECODER_SPK_CONFIGURATION`
 *   |    and sound engine's input/output also match channel info according to :c:macro:`DECODER_SPK_CONFIGURATION`
 *
 * Performance Requirements
 *   The response time of this function should be within 5ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //function
 *     decoder_spk_configuration_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     decoder_spk_configuration_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //parameter
 *     struct snd_kcontrol *kcontrol
 *     "Decoder Speaker Configuration"
 *
 *     struct snd_ctl_elem_value *ucontrol
 *     value[0]: decoder_spk_configuration_type_t
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``       Internal driver error happened
 *
 *   ``EINVAL``      Invalid argument
 *
 *   ``EALREADY``    Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     decoder_spk_configuration_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         decoder_spk_configuration_type_t value = ucontrol->value.integer.value[0];
 *         // set decoder speaker configuration
 *     }
 *     decoder_spk_configuration_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get decoder speaker configuration
 *         ucontrol->value.integer.value[0] = value;
 *     }
 *
 * @endrst
 */
#define DECODER_SPK_CONFIGURATION "Decoder Spk Configuration"

/**
 * @brief maximum channel number of local speakers
*/
#define SNDOUT_SPK_LOCAL_CHANNEL_MAX_NUM (16)

/**
 * @brief put/get Speaker Maximum Output Channel
 *
 * priority 4
 *
 * @rst
 * Functional Requirements
 *   | The function is called to set speakers channel mapping according to the board (or device)
 *   | Parameters would be sent as below
 *   | 1) number of total channels (local speakers + wireless speakers which could be connected by wireless protocol such as dafc)
 *   | 2) number of local speakers (if the board has 5.4.3, the number would be 12)
 *   |
 *   | Sound engine output channel information (e.g. 7.1) would be mapped by tuning process, so speaker mapping information would not be set
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // Functions
 *     //
 *     sndout_spk_max_output_channel_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     sndout_spk_max_output_channel_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Sndout Spk Max Output Channel"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: int totalOutputChannel
 *     value[1]: int localOutputChannel (larger than or equal 2, maximum: SNDOUT_SPK_LOCAL_CHANNEL_MAX_NUM)
 *
 *
 * Return Value
 *   On success 0 is returned.
 *
 *   On error:
 *
 *   ``EBUSY``  Internal driver error happened
 *
 *   ``EINVAL``  Invalid argument
 *
 *   ``EALREADY``  Operation already in progress
 *
 * Example
 *   .. code-block:: cpp
 *
 *     sndout_spk_max_output_channel_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Set Speaker Maximum Output Channel Info
 *         int totalOutputChannel = ucontrol->value.integer.value[0];
 *         int localOutputChannel = ucontrol->value.integer.value[1];
 *
 *     }
 *     sndout_spk_max_output_channel_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // Get Speaker Maximum Output Channel Info
 *         ucontrol->value.integer.value[0] = totalOutputChannel;
 *         ucontrol->value.integer.value[1] = localOutputChannel;
 *     }
 *
 * @endrst
 */
#define SNDOUT_SPK_MAX_OUTPUT_CHANNEL "Sndout Spk Max Output Channel"


#endif
