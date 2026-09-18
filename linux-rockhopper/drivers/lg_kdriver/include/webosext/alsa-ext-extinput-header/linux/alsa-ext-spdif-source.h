/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2023 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/
#ifndef _ALSA_EXT_SPDIF_SOURCE_H
#define _ALSA_EXT_SPDIF_SOURCE_H

/**
 * @brief SPDIF source device open
 *
 * priority:2
 *
 * @rst
 * Functional Requirements
 *   Open the SPDIF source driver.
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
 *     spdif_source_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     spdif_source_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
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
 *     spdif_source_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int open_status = ucontrol->value.integer.value[0]; // Open Spdif Source Resource
 *     }
 *     spdif_source_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get Spdif Source Open Status
 *         ucontrol->value.integer.value[0] = open_status;
 *     }
 *
 * @endrst
 */
#define SPDIF_SOURCE_OPEN "Spdif Source Open"

/**
 * @brief SPDIF Source device close
 *
 * priority : 2
 *
 * @rst
 *
 * Functional Requirements
 *  Close the SPDIF Source driver.
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
 *     // function
 *     //
 *     spdif_source_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     spdif_source_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
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
 *     spdif_source_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int close_status = ucontrol->value.integer.value[0]; // Close Spdif Source Resource
 *     }
 *     spdif_source_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get Spdif Source Close Status
 *         ucontrol->value.integer.value[0] = close_status;
 *     }
 *
 * @endrst
 */
#define SPDIF_SOURCE_CLOSE "Spdif Source Close"

/**
 * @brief SPDIF Source device Connect
 *
 * priority : 2
 *
 * @rst
 * Functional Requirements
 *   Connect the SPDIF Source driver.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   if we call "Spdif Source Close", this value should be default.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     //function
 *     //
 *     spdif_source_connect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     spdif_source_connect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //parameter
 *     struct snd_kcontrol{}
 *     struct snd_ctl_elem_value{}
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
 *     spdif_source_connect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int connect_hw_port = ucontrol->value.integer.value[0]; // Connect Spdif Source hw port
 *     }
 *     spdif_source_connect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get Spdif Source Connected Port
 *         ucontrol->value.integer.value[0] = connected_hw_port;
 *     }
 *
 * @endrst
 */
#define SPDIF_SOURCE_CONNECT "Spdif Source Connect"

/**
 * @brief SPDIF Source device disconnect
 *
 * priority : 2
 *
 * @rst
 * Functional Requirements
 *   Disconnect the SPDIF Source driver.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   if we call "Spdif Source Close", this value should be default.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // function
 *     //
 *     spdif_source_disconnect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     spdif_source_disconnect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value();
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
 * Example:
 *   .. code-block:: cpp
 *
 *     spdif_source_disconnect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int disconnect_status = ucontrol->value.integer.value[0]; // Disconnect Spdif Source hw port
 *     }
 *     spdif_source_disconnect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get Spdif Source disconnected status
 *         ucontrol->value.integer.value[0] = disconnect_status;
 *     }
 *
 * @endrst
 */
#define SPDIF_SOURCE_DISCONNECT "Spdif Source Disconnect"

/**
 * enum spdif_codec_ext_type - spdif audio type description.
 * This enum represent the spdif types.
 * Some types are not used.
 */
typedef enum spdif_type_ext_type {
    SPDIF_UNKNOWN          = 0x00, /**< Codec is unknown */
    SPDIF_PCM              = 0x01, /**< PCM Audio in SPDIF */

    SPDIF_AC3              = 0x10, /**< AC3 Audio in SPDIF */
    SPDIF_EAC3             = 0x11, /**< EAC3(DD+) Audio in SPDIF */
    SPDIF_MAT              = 0x15, /**< MAT Audio in SPDIF */
    SPDIF_AAC              = 0x19, /**< AAC Audio in SPDIF */

    SPDIF_DTS              = 0x30, /**< DTS Audio in SPDIF */
    SPDIF_DTS_HD           = 0x31, /**< DTS-HD Audio in SPDIF */

    SPDIF_DVI              = 0x40, /**< DVI Status */
    SPDIF_NO_AUDIO         = 0x41, /**< No Audio in SPDIF */
} spdif_type_ext_type_t;

/**
 * spdif_copyprotection_ext_type_t
 */
typedef enum spdif_copyprotection_ext_type {
    SPDIF_COPY_FREE    = 0, /**< cp-bit : 1, L-bit : 0 */
    SPDIF_COPY_NO_MORE = 1, /**< cp-bit : 0, L-bit : 1 */
    SPDIF_COPY_ONCE    = 2, /**< cp-bit : 0, L-bit : 0 */
    SPDIF_COPY_NEVER   = 3, /**< cp-bit : 0, L-bit : 1 */
} spdif_copyprotection_ext_type_t;

/**
 * @brief get Audio Codec from SPDIF
 * @li priority : 2
 *
 * @rst
 * Functional Requirements
 *   It is used to obtain status (SPDIF) and codec information from SPDIF
 *   The criterion for determining the PCM / Non-PCM of the SPDIF audio
 *   format is PCM / Non-PCM referring to the status bit 1 of IEC60958.
 *   @b Bit 1 "0 Main data field represents linear PCM samples. "1 Main data field
 *   used for purposes other purposes,
 *
 *   Then, in the case of non-PCM, it is judged to be Pc and Pd of IEC61937 (AC-3
 *   / DTS, etc.). For each port, change the number after the function port and
 *   call it. If it is impossible to control by port, parameter is called by
 *   SPDIF_SWITCH.
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
 * spdif_audiomode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *      // get spdif type
 *      ucontrol->value.integer.value[0] = audio_type;
 * }
 * @endcode
 *
 * @param[out] spdif_type spdif_type_ext_type_t (default:0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define SPDIF_SOURCE_AUDIOMODE "Spdif Source AudioMode"
/**
 * @see SPDIF_SOURCE_AUDIOMODE
 */

/**
 * @brief get spdif copyprotection for spdif source
 * @li priority : 4
 *
 * @rst
 * Functional Requirements
 *   It is used to obtain Copy Protection information of the signal from the SPDIF
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
 * spdif_copyprotectioninfo_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get copyprotectioninfo
 *     ucontrol->value.integer.value[0] = copy_protection_info;
 * }
 * @endcode
 *
 * @param[out] copyprotection_info spdif_copyprotection_ext_type_t (default:0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define SPDIF_SOURCE_COPYPROTECTIONINFO "Spdif Source CopyProtectionInfo"
/**
 * @see SPDIF_SOURCE_COPYPROTECTIONINFO
 */


#endif
