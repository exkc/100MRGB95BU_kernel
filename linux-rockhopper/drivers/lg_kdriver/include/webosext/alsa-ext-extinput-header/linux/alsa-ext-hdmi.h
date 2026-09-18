/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/
#ifndef _ALSA_EXT_HDMI_H
#define _ALSA_EXT_HDMI_H

/**
 * enum ahdmi_codec_ext_type - hdmi audio type description.
 * This enum represent the hdmi types.
 * Some types are not used.
 */
typedef enum ahdmi_type_ext_type {
    AHDMI_UNKNOWN          = 0x00, /**< Codec is unknown */
    AHDMI_PCM              = 0x01, /**< PCM Audio in HDMI */

    AHDMI_AC3              = 0x10, /**< AC3 Audio in HDMI */
    AHDMI_EAC3             = 0x11, /**< EAC3(DD+) Audio in HDMI */
    AHDMI_MAT              = 0x15, /**< MAT Audio in HDMI */
    AHDMI_AAC              = 0x19, /**< AAC Audio in HDMI */

    AHDMI_DTS              = 0x30, /**< DTS Audio in HDMI */
    AHDMI_DTS_HD           = 0x31, /**< DTS-HD Audio in HDMI */

    AHDMI_DVI              = 0x40, /**< DVI Status */
    AHDMI_NO_AUDIO         = 0x41, /**< No Audio in HDMI */
} ahdmi_type_ext_type_t;

/**
 * ahdmi_copyprotection_ext_type_t
 */
typedef enum ahdmi_copyprotection_ext_type {
    AHDMI_COPY_FREE    = 0, /**< cp-bit : 1, L-bit : 0 */
    AHDMI_COPY_NO_MORE = 1, /**< cp-bit : 0, L-bit : 1 */
    AHDMI_COPY_ONCE    = 2, /**< cp-bit : 0, L-bit : 0 */
    AHDMI_COPY_NEVER   = 3, /**< cp-bit : 0, L-bit : 1 */
} ahdmi_copyprotection_ext_type_t;

/**
 * @brief get Audio Codec from HDMI0
 * @li priority : 2
 *
 * @rst
 * Functional Requirements
 *   It is used to obtain status (HDMI / DVI) and codec information from HDMI
 *   Port. The criterion for determining the PCM / Non-PCM of the HDMI audio
 *   format is PCM / Non-PCM referring to the status bit 1 of IEC60958.
 *   @b Bit 1 "0 Main data field represents linear PCM samples. "1 Main data field
 *   used for purposes other purposes,
 *
 *   Then, in the case of non-PCM, it is judged to be Pc and Pd of IEC61937 (AC-3
 *   / DTS, etc.). For each port, change the number after the function port and
 *   call it. If it is impossible to control by port, parameter is called by
 *   AHDMI_SWITCH.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 * @endrst
 *
 * @b Pseudocode
 * @code
 * ahmdi_port0_audiomode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *      // get hdmi type
 *      ucontrol->value.integer.value[0] = audio_type;
 * }
 * @endcode
 *
 * @param[out] ahdmi_type ahdmi_type_ext_type_t (default:0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define AHDMI_PORT0_AUDIOMODE "Ahdmi Port0 AudioMode"
/**
 * @see AHDMI_PORT0_AUDIOMODE
 */
#define AHDMI_PORT1_AUDIOMODE "Ahdmi Port1 AudioMode"
/**
 * @see AHDMI_PORT0_AUDIOMODE
 */
#define AHDMI_PORT2_AUDIOMODE "Ahdmi Port2 AudioMode"
/**
 * @see AHDMI_PORT0_AUDIOMODE
 */
#define AHDMI_PORT3_AUDIOMODE "Ahdmi Port3 AudioMode"

/**
 * @brief get hdmi copyprotection for each hdmi port0
 * @li priority : 4
 *
 * @rst
 * Functional Requirements
 *   It is used to obtain Copy Protection information of the signal from the HDMI
 *   Port.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 * @endrst
 *
 * @b Pseudocode
 * @code
 * ahmdi_port0_copyprotectioninfo_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get copyprotectioninfo
 *     ucontrol->value.integer.value[0] = copy_protection_info;
 * }
 * @endcode
 *
 * @param[out] copyprotection_info ahdmi_copyprotection_ext_type_t (default:0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define AHDMI_PORT0_COPYPROTECTIONINFO "Ahdmi Port0 CopyProtectionInfo"
/**
 * @see AHDMI_PORT0_COPYPROTECTIONINFO
 */
#define AHDMI_PORT1_COPYPROTECTIONINFO "Ahdmi Port1 CopyProtectionInfo"
/**
 * @see AHDMI_PORT0_COPYPROTECTIONINFO
 */
#define AHDMI_PORT2_COPYPROTECTIONINFO "Ahdmi Port2 CopyProtectionInfo"
/**
 * @see AHDMI_PORT0_COPYPROTECTIONINFO
 */
#define AHDMI_PORT3_COPYPROTECTIONINFO "Ahdmi Port3 CopyProtectionInfo"

#endif
