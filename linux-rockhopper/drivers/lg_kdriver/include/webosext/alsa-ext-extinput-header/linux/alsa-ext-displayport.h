/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2018-2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/
#ifndef _ALSA_EXT_DISPLAYPORT_H
#define _ALSA_EXT_DISPLAYPORT_H

/**
 * enum displayport audio type description.
 * This enum represent the displayport audio types.
 * Some types are not used.
 */
typedef enum displayport_ext_audio_type {
    DISPLAYPORT_AUDIO_UNKNOWN          = 0x00, /**< Codec is unknown */
    DISPLAYPORT_AUDIO_PCM              = 0x01, /**< PCM Audio in DisplayPort */

    DISPLAYPORT_AUDIO_AC3              = 0x10, /**< AC3 Audio in DisplayPort */
    DISPLAYPORT_AUDIO_EAC3             = 0x11, /**< EAC3(DD+) Audio in DisplayPort */
    DISPLAYPORT_AUDIO_MAT              = 0x15, /**< MAT Audio in DisplayPort */
    DISPLAYPORT_AUDIO_AAC              = 0x19, /**< AAC Audio in DisplayPort */

    DISPLAYPORT_AUDIO_DTS              = 0x30, /**< DTS Audio in DisplayPort */
    DISPLAYPORT_AUDIO_DTS_HD           = 0x31, /**< DTS-HD Audio in DisplayPort */

    DISPLAYPORT_AUDIO_NO_AUDIO         = 0x41, /**< No Audio in DisplayPort */
} displayport_ext_audio_type_t;

/**
 * displayport_ext_audio_copyprotection_type_t
 */
typedef enum displayport_ext_audio_copyprotection_type {
    DISPLAYPORT_AUDIO_COPY_FREE    = 0, /**< cp-bit : 1, L-bit : 0 */
    DISPLAYPORT_AUDIO_COPY_NO_MORE = 1, /**< cp-bit : 0, L-bit : 1 */
    DISPLAYPORT_AUDIO_COPY_ONCE    = 2, /**< cp-bit : 0, L-bit : 0 */
    DISPLAYPORT_AUDIO_COPY_NEVER   = 3, /**< cp-bit : 0, L-bit : 1 */
} displayport_ext_audio_copyprotection_type_t;

/**
 * @brief get Audio Codec from DisplayPort
 * @li priority : 2
 *
 * @rst
 * Functional Requirements
 *   It is used to obtain status and codec information from DisplayPort.
 *   The criterion for determining the PCM / Non-PCM of the DisplayPort audio
 *   format is PCM / Non-PCM referring to the status bit 1 of IEC60958.
 *   @b Bit 1 "0 Main data field represents linear PCM samples. "1 Main data field
 *   used for purposes other purposes,
 *
 *   Then, in the case of non-PCM, it is judged to be Pc and Pd of IEC61937 (AC-3
 *   / DTS, etc.). For each port, change the number after the function port and
 *   call it.
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
 * dp_port0_audiomode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *      // get displaytype type
 *      ucontrol->value.integer.value[0] = audio_type;
 * }
 * @endcode
 *
 * @param[out] dp_audio_type displayport_ext_audio_type_t (default:0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define DP_PORT0_AUDIOMODE "DP Port0 AudioMode"
/**
 * @see DISPLAYPORT_PORT0_AUDIOMODE
 */
#define DP_PORT1_AUDIOMODE "DP Port1 AudioMode"

/**
 * @brief get DisplayPort audio copyprotection for each port
 * @li priority : 4
 *
 * @rst
 * Functional Requirements
 *   It is used to obtain audio copy protection information of the signal from the DisplayPort
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
 * displayport_audio_port0_copyprotectioninfo_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get audio copy protection info
 *     ucontrol->value.integer.value[0] = copy_protection_info;
 * }
 * @endcode
 *
 * @param[out] copyprotection_info displayport_ext_audio_copyprotection_type_t (default:0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define DP_PORT0_COPYPROTECTIONINFO "DP Port0 CopyProtectionInfo"
/**
 * @see DP_PORT0_COPYPROTECTIONINFO
 */
#define DP_PORT1_COPYPROTECTIONINFO "DP Port1 CopyProtectionInfo"

#endif