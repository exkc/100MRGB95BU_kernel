/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_ADEC_H
#define _ALSA_EXT_ADEC_H

/**
 * @brief ADEC device open
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   It is an API to open ADEC (Audio Decoder). Opened ADEC can be connected to
 *   input sources such as ATP, AAD, ADC, HDMI by ADEC_ADEC_Connect. You can not
 *   open duplicates for already opened ADEC.
 *
 *   Due to the nature of ALSA, the number of parameters of Get and Put must
 *   match.
 *
 *   In this case, when the Get function is called, the ADEC indexes that have
 *   been opened with Put are transmitted. At this time, if only one ADEC is
 *   opened, the index is opened as the first argument, and the rest is filled
 *   with 0xFFFF. If two are opened, the first and second arguments are filled
 *   with the corresponding Index and the rest are filled with 0xFFFF. The
 *   following ADEC0 and ADEC1 are sequentially stored according to the opened
 *   order. When ADEC Close operation is performed, the Get index below is
 *   initialized and the first argument is rearranged.
 *
 * .. code-block:: bash
 *
 *   // examples for parameter.
 *   amixer -c 0 cset "Adec Open" 0 → get {0,1,1,0,0xFFFF,0,0xFFFF,0}
 *   amixer -c 0 cset "Adec Open" 1 → get {0,1,1,1,0xFFFF,0,0xFFFF,0}
 *   amixer -c 0 cset "Adec Open" 2 → get {0,1,1,1,0xFFFF,0,0xFFFF,0}
 *   amixer -c 0 cset "Adec Close" 0 → get "Adec Open" {0,0,1,1,0xFFFF,0,0xFFFF,0}
 *   // get "Adec Close" {0,1,1,0,2,0,3,0}
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
 * adec_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0]; // Open Adec Resource
 * }
 * adec_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get Adec Open Status
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_open_status;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_open_status;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_open_status;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_open_status;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec_port0_status int opened adec0 status
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec_port1_status int opened adec1 status
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec_port2_status int opened adec2 status
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec_port3_status int opened adec3 status
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_OPEN "Adec Open"

/**
 * @brief ADEC device close
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   This function closes ADEC. If this function is called when ADEC is not open
 *   or in the connect state, it returns NOT_OK without action.
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
 * adec_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     // Close Adec Resource
 * }
 * adec_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get Adec Close Status
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_close_status;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_close_status;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_close_status;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_close_status;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec_port0_status int closed adec0 status
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec_port1_status int closed adec1 status
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec_port2_status int closed adec2 status
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec_port3_status int closed adec3 status
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_CLOSE "Adec Close"

/**
 * input ports for adec
 * HDMI Ports are used for Multi View Implementation
 */
typedef enum adec_src_port_index_ext_type {
    ADEC_SRC_UNKNOWN      = 0x00, /**< Source is Unknown */
    ADEC_SRC_ATP0         = 0x01, /**< ATP port 0 */
    ADEC_SRC_ATP1         = 0x02, /**< ATP port 1 */
    ADEC_SRC_ADC          = 0x03, /**< ADC */
    ADEC_SRC_AAD          = 0x04, /**< AAD */
    ADEC_SRC_HDMI_PORT0   = 0x05, /**< HDMI Port 0 */
    ADEC_SRC_HDMI_PORT1   = 0x06, /**< HDMI Port 1 */
    ADEC_SRC_HDMI_PORT2   = 0x07, /**< HDMI Port 2 */
    ADEC_SRC_HDMI_PORT3   = 0x08, /**< HDMI Port 3 */
    ADEC_SRC_DISPLAYPORT0 = 0x09, /**< DP Port 0 */
    ADEC_SRC_DISPLAYPORT1 = 0x0a, /**< DP Port 1 */
    ADEC_SRC_SPDIF        = 0x0b, /**< SPDIF Source */
    ADEC_SRC_I2S          = 0x0c, /**< I2S Source (eARC ext chip -> SoC) */
    ADEC_SRC_HDMI_DEFAULT = 0xff, /**< HDMI DEFAULT ( manage by a chip ) */
} adec_src_port_index_ext_type_t;

/**
 * @brief ADEC device connect with input port
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   Connect ADEC with the resource that will be the input of ADEC. ATP, AAD, ADC,
 *   HDMI, etc. can be input to ADEC. Only one input can be connected to one ADEC.
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
 * adec_connect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     int adec_src_port_index_ext_type = ucontrol->value.integer.value[1];
 *     // connectAdec Resource
 * }
 * adec_connect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get Adec connect Status
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_connect_port;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_connect_port;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_connect_port;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_connect_port;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] input_port adec_src_port_index_ext_type_t input port number
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec_port0_connected_input adec_src_port_index_ext_type_t
 *             connected input port number for adec0
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec_port1_connected_input adec_src_port_index_ext_type_t
 *             connected input port number for adec1
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec_port2_connected_input adec_src_port_index_ext_type_t
 *             connected input port number for adec2
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec_port3_connected_input adec_src_port_index_ext_type_t
 *             connected input port number for adec3
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_CONNECT "Adec Connect"

/**
 * @brief ADEC device disconnect with input port
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   Disconnect from connected resource with ADEC input. If attempting to
 *   disconnect an unconnected adec index, you should return NOT_OK.
 *
 *   Disconnect-> Close is a general sequence, but the function must also work in
 *   the Close-> Disconnect sequence.
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
 * adec_disconnect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     // Disconnect Adec Resource
 * }
 *
 * adec_disconnect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get Adec Disconnected Status
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_disconnect_status;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_disconnect_status;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_disconnect_status;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_disconnect_status;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] input_port adec_src_port_index_ext_type_t input port number
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec_port0_disconnected_input int disconnected input port number
 * for adec0
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec_port1_disconnected_input int disconnected input port number
 * for adec1
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec_port2_disconnected_input int disconnected input port number
 * for adec2
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec_port3_disconnected_input int disconnected input port number
 * for adec3
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_DISCONNECT "Adec Disconnect"

/**
 * adec_src_codec_ext_type_t is showing codec types
 */
typedef enum adec_src_codec_ext_type {
    ADEC_SRC_CODEC_UNKNOWN = 0x00, /**< Codec is UNKNOWN */
    ADEC_SRC_CODEC_PCM     = 0x01, /**< Codec is PCM */
    ADEC_SRC_CODEC_AUTO    = 0x02, /**< Codec is Auto for I2S input */

    ADEC_SRC_CODEC_AC3          = 0x10, /**< Codec is AC3 */
    ADEC_SRC_CODEC_EAC3         = 0x11, /**< Codec is EAC3 */
    ADEC_SRC_CODEC_EAC3_ATMOS   = 0x12, /**< Codec is EAC3 ATMOS */
    ADEC_SRC_CODEC_AC4          = 0x13, /**< Codec is (Non ATMOS) AC4 */
    ADEC_SRC_CODEC_AC4_ATMOS    = 0x14, /**< Codec is AC4 ATMOS */
    ADEC_SRC_CODEC_MAT          = 0x15, /**< Codec is MAT */
    ADEC_SRC_CODEC_MAT_ATMOS    = 0x16, /**< Codec is MAT ATMOS */
    ADEC_SRC_CODEC_TRUEHD       = 0x17, /**< Codec is True HD */
    ADEC_SRC_CODEC_TRUEHD_ATMOS = 0x18, /**< Codec is True HD ATMOS */
    ADEC_SRC_CODEC_AAC          = 0x19, /**< Codec is AAC */
    ADEC_SRC_CODEC_HEAAC        = 0x1a, /**< Codec is HEAAC */

    ADEC_SRC_CODEC_MPEG   = 0x20, /**< Codec is MPEG */
    ADEC_SRC_CODEC_MPEG_H = 0x21, /**< Codec is MPEG H */
    ADEC_SRC_CODEC_DRA    = 0x22, /**< Codec is DRA */

    ADEC_SRC_CODEC_DTS         = 0x30, /**< Codec is DTS */
    ADEC_SRC_CODEC_DTS_HD_MA   = 0x31, /**< Codec is DTS HD MA */
    ADEC_SRC_CODEC_DTS_EXPRESS = 0x32, /**< Codec is DTS EXPRESS */
    ADEC_SRC_CODEC_DTS_HD      = 0x33, /**< Codec is DTS HD */
    ADEC_SRC_CODEC_DTS_X_P1    = 0x34, /**< Codec is DTS:X P1 */
    ADEC_SRC_CODEC_DTS_X_P2    = 0x35, /**< Codec is DTS:X P2 */

    ADEC_SRC_CODEC_SIF      = 0x40, /**< For ATV */
    ADEC_SRC_CODEC_SIF_BTSC = 0x41, /**< For ATV (BTSC system) */
    ADEC_SRC_CODEC_SIF_A2   = 0x42  /**< For ATV (A2 system) */
} adec_src_codec_ext_type_t;

/**
 * @brief Set Codec to ADEC port
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   Function to allocate resources according to codec before ADEC Start. Must be
 *   called before Start.
 *
 *   In the following cases, return NOT_OK without any action.
 *
 *   If ADEC is not open. If ADEC is not connected to Input If the input parameter
 *   audiotype does not match the inuput audio data type input by the actual ADEC
 *
 *   Switching between Atmos <-> Non-Atmos is performed by the driver itself.
 *   Start can be called with Atmos or Non-Atmos for Atmos contents. If the driver
 *   itself is Atmos, it will decode it with Atmos.
 *
 *   For example: EAC3 Atmos Contents: Codec (EAC3) or Codec (EAC3_Atmos) can be
 *   called. AC4 Atmos Contents: Codec (AC4) or Codec (AC4_Atmos) can be called.
 *   MAT Atmos Contents: Codec (MAT) or Codec (MAT_Atmos) can be called.
 *
 *   when Aenc is starting, if Codec which need dual decoder is decoding, decoder
 *   which decode codec(need dual decoder) will be stopped by driver or remove
 *   atmos effect from codec.
 *
 *   For example(if aenc are executed)
 *
 *   ac3 atmos → ac3, eac3 atmos → eac3, ac4 atmos → ac4, ture hd/mat/truehd
 *   atmos/mat atmos → stop
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
 * adec_codec_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     // Start decoding Adec Resource with codec information
 * }
 * adec_codec_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * { // Get Recently started adec and codec
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_codec_status;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_codec_status;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_codec_status;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_codec_status;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] audio_codec adec_src_codec_ext_type_t audio codec number
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec_port0_codec adec_src_codec_ext_type_t codec for adec0
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec_port1_codec adec_src_codec_ext_type_t codec for adec1
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec_port2_codec adec_src_codec_ext_type_t codec for adec2
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec_port3_codec adec_src_codec_ext_type_t codec for adec3
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_CODEC "Adec Codec"

/**
 * @brief ADEC device start decoding
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   ======================== ===================================================
 *   Kcontrol function        string Setting content
 *   ======================== ===================================================
 *   Adec Connect             Output that needs to be sent to soundout from ADEC
 *   Sndout Spdif OutputType  SPDIF/ARC output type
 *   Adec SyncMode            Whether AV Sycn is needed
 *   Gain Input               Decoder input volume
 *   Delay Input              Decoder input delay
 *   Mute Input               Decoder input mute
 *   Adec TrickMode           Audio trick state
 *   Adec DolbyDRCMode        Dolby DRC(Line, RF) Mode
 *   Adec DownMixMode         Downmix(LoRo, LtRt) Mode|
 *   Adec DualMonoOutMode     Set daulmono mode of ADEC out (LR, LL, RR, MIX)
 *   ======================== ===================================================
 *
 *   The above setting can be changed dynamically during start operation, and ADEC
 *   decoding should work well according to the change. In other words, LG MW does
 *   not stop decoding or start separately for the above setting change.
 *
 *   Depending on the state of the input output connection of ADEC, it may be
 *   required to output ES and PCM at the same time, and the output may be
 *   required after transcoding if necessary. For example, if the audio input is
 *   DD + and the SPDIF Output Type is AUTO (see ADEC_SPDIF_SetOutputType guide),
 *   the SPDIF output should be output as DD as shown below. If there is a
 *   statement in the input stream during normal decoding, data should not be
 *   output when data of the wrong audiotype is input, and data should be output
 *   when it is normally recovered. There should be no noise in this process.
 *
 *   In the following cases, return NOT_OK without any action.
 *
 *   If ADEC is not open If ADEC is not connected to Input If the input parameter
 *   audiotype does not match the inuput audio data type input by the actual ADEC
 *   If ADEC's codec is not set in advance
 *
 *   At this time, when the ATMOS or non-ATMOS is confirmed, the corresponding
 *   information is updated to "Adec Info" so that the MW can determine the
 *   corresponding information.
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
 * adec_start_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     // Start decoding Adec Resource with codec information
 * }
 * adec_start_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *     // Get Recently started adec and codec
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_start_status;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_start_status;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_start_status;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_start_status;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec_port0_start_status int start status of adec0
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec_port1_start_status int start status of adec1
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec_port2_start_status int start status of adec2
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec_port3_start_status int start status of adec3
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_START "Adec Start"

/**
 * @brief ADEC device stop decoding
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   When this function is called, ADEC decoding of the input adecIndex is
 *   stopped.
 *
 *   If this function is called without decoding, it returns NOT_OK without any
 *   action.
 *
 *   When ADEC decoding stops, ADEC stops decoding and does not output data, which
 *   does not mean that the flow of data on the PATH stops. For example, if the
 *   decoding of ADEC0 is stopped, the flow of the other inputs (ADEC1, AMIXER)
 *   will continue, and the data already flowing before ADEC0 stop will be
 *   processed by each module.
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
 * adec_stop_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int adec_index = ucontrol->value.integer.value[0];
 *     // Stop Decoding for Adec Resource
 * }
 *
 * adec_stop_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Get Recently stopped adec index
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_start_status;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_start_status;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_start_status;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_start_status;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 *
 * @param[out] adec_port0_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF
 * @param[out] adec_port0_stop_status int stop status of adec0
 * @param[out] adec_port1_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:1)
 * @param[out] adec_port1_stop_status int stop status of adec1
 * @param[out] adec_port2_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:2)
 * @param[out] adec_port2_stop_status int stop status of adec2
 * @param[out] adec_port3_number int if port is smaller than adec number of
 *             "Adec UserMaxCapacity", it should be 0xFF (default:3)
 * @param[out] adec_port3_stop_status int stop status of adec3
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_STOP "Adec Stop"

/**
 * @brief ADEC and AMIXER Capacity
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   We can get maximum adec capacity from driver.
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
 * adec_MaxCapacity_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Return how many adec driver got.
 *     ucontrol->value.integer.value[0] = get_adec_max_capacity;
 *     ucontrol->value.integer.value[1] = get_adec_max_capacity;
 * }
 * @endcode
 *
 * @param[out] adec_max_cap int Return how many adec can be used by driver.
 * @param[out] amixer_max_cap int Return how many amixer can be used by driver.
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 */
#define ADEC_MAXCAPACITY "Adec MaxCapacity"

/**
 * @brief ADEC and AMIXER User Capacity
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   We can decide how many adec we use.
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
 * adec_UserMaxCapacity_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Set how many adec driver user uses.
 *     userMaxCapacity_for_adec = ucontrol->value.integer.value[0];
 *     userMaxCapacity_for_amixer = ucontrol->value.integer.value[0];
 * }
 *
 * adec_UserMaxCapacity_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Return how many adec driver got.
 *     ucontrol->value.integer.value[0] = userMaxCapacity_for_adec;
 *     ucontrol->value.integer.value[0] = userMaxCapacity_for_amixer;
 * }
 * @endcode
 *
 * @param[in] user_adec_max_cap int Set how many adec we use
 * @param[in] user_amixer_max_cap int Set how many amixer we use
 *
 * @param[out] user_adec_max_cap int Return how many adec we use by user.
 *             (default:adec_max_cap, amixer_max_cap for "Adec MaxCapacity")
 * @param[out] user_amixer_max_cap int Return how many amixer we use by user.
 *             (default:adec_max_cap, amixer_max_cap for "Adec MaxCapacity")
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_USERMAXCAPACITY "Adec UserMaxCapacity"

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
 * @rst
 * Functional Requirements
 *   In case of DTV input, it sends L + L, L + R, R + R information to one Audio
 *   PID for Japanese or some Sphere Japanese incense, for example, is usually
 *   sent to the L channel by sending it to the Japanese R channel, so that two
 *   languages can be heard.
 *
 *   If you select Japanese in the UI at this time, ADEC_DUALMONO_MODE_LL is set
 *   to allow you to listen to Japanese sound.
 *
 *   If you select Japanese + English, you can listen Japanese with Left Speaker
 *   and English with Right Speaker. In external input (AV or Component),
 *   ADEC_DUALMONO_MODE_LRis called to ALSA if you try to listen only to the L
 *   terminal of the actual L / R terminal.
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
 * @rst
 * Functional Requirements
 *   API to set the Sync mode Sync mode When On, video and sync are synchronized.
 *   If Off, video and sync are not synchronized.
 *
 *   1. "Adec SyncMode" (On) is called for adec port where audio start is done
 *      e.g.
 *   @li Channel is changed to AD channel with AD (Off): "Adec SyncMode"(On) is
 *   called for main adec port
 *   @li AD(Off => On) on AD channel: adec stop => audio start and "Adec
 *   SyncMode"(On) will be called for main and AD adec ports
 *   @li AD(On => Off) on AD channel: adec stop for AD adec port (no "Adec
 *   SyncMode"call)
 *
 *   2. "Adec SyncMode" can be called repeatably
 *
 *   3. timing of calling "Adec SyncMode" might be not fixed (can be after/before
 *      adec start)
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
 * @rst
 * Functional Requirements
 *   API for setting Dolby DRC (Line, RF) mode.
 *
 *   LG MW is set to RF mode for DVB and to Line mode for other cases. LG MW
 *   TVService uses "Adec DolbyDRCMode" as necessary to inform DRC mode to driver
 *   to be set.
 *
 *   However, if Gstreamer OMX uses ADEC, ADEC_DOLBYDRCMODE is not used. In this
 *   case, driver itself should be set to Line Mode.
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
 * @rst
 * Functional Requirements
 *   API for setting default PRL.
 *
 *   TVService uses "Adec DefaultPRL" as necessary to inform default PRL to driver to be set.
 *   If the PRL value is not included in the Audio ES Stream, audio decoder must refer to
 *   this default PRL value.
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
 * @rst
 * Functional Requirements
 *   API for setting Downmix (LoRo, LtRt) mode.
 *
 *   LG MW is set to AAC for LtRt when the audio codec type is AC3, EAC3, PCM, or
 *   LoRo for HEAAC. LG MW TVService uses "Adec DownMixMode" according to the
 *   audio codec type to allow the driver to change the DownMixMode.
 *
 *   However, since GStreamer OMX does not use "Adec DownMixMode" when using ADEC,
 *   driver should set LtRt / LoRo according to the above condition according to
 *   audio codec type.
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
 * @rst
 * Functional Requirements
 *   API to set ADEC play speed in DVR Playback mode Change the Trick state of
 *   ADEC during DVR Trick Play such as Pause / Resume.
 *
 *   At the time of development, it implements the audio play back speed required
 *   by the operation product.
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
 * @brief get information for adec X
 * @li priority : 3
 *
 * @rst
 * Functional Requirements
 *   When this function is called, the information of Adec is returned.
 *
 *   The codec information is returned as SRC_CODEC_UNKNOWN (0x00)
 *   immediately after the Adec Start, and when final codec information should be updated
 *   when the right codec information is recognized by ADEC's decoding.
 *
 *   If Adec can not check the codec information, set
 *   both of sourceAdecForamt and curAdecFormat to ADEC_SRC_CODEC_UNKNOWN to notify that the codec
 *   information has not yet been checked by Adec.
 *
 *   Actual codec in input audio siganl and decoded codec by ADEC can be different each other.
 *   The examples are like below,
 *   The actual codec can be AAC but the decoded codec can be HEAAC and vice versa.
 *   The actual codec can be MAT but the decoded codec can be MAT_ATMOS and vice versa
 *   The actual codec can be AC4 but the decoded codec can be AC4_ATMOS and vice versa
 *   The actual codec can be EAC3 but the decoded codec can be EAC3_ATMOS and vice versa
 *   The actual codec can be DTS-HD but the decoded codec can be DTS:X and vice versa
 *   The codec type of the actual source is updated in the sourceAdecFormat
 *   whereas the codec being decoded is updated in curAdecFormat so that they can be
 *   distinguished from each other.
 *   Be careful that no other combinations of the actual codec and the decoded codec is allowed
 *
 *   Since the "Adec start" is called, the exact time moment when the "Adec info" begins to return a valid audio codec information
 *   should be the time when the first decoded audio frame is delivered from ADEC's decoded buffer to a next audio modules.
 *   Before this time, the "Adec info" should keep returning ADEC_SRC_CODEC_UNKNOWN.
 *   In DTV input, this time should be the time when the audio PTS(presentation time stamp) and the STC(system time clock) becomes
 *   matched each other.
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
 * adec0_info_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 * // Get information for adec
 *     ucontrol->value.integer.value[0] = adec_port_number;
 *     ucontrol->value.integer.value[1] = bAdecStart;
 *     ucontrol->value.integer.value[2] = userAdecFormat;    // codecSet
 *     ucontrol->value.integer.value[3] = curAdecFormat;     // codecDecoded
 *     ucontrol->value.integer.value[4] = sourceAdecFormat;  // codecSrc
 *     ucontrol->value.integer.value[5] = curAdecInputPort;
 *     ucontrol->value.integer.value[6] = prevAdecInputPort;
 *     ucontrol->value.integer.value[7] = curAdecDualMonoMode;
 *     ucontrol->value.integer.value[8] = IsEsExist;
 *     ucontrol->value.integer.value[9] = audioMode;
 *     ucontrol->value.integer.value[10] = heaac_version;
 *     ucontrol->value.integer.value[11] = heaac_trasmissionformat;
 *     ucontrol->value.integer.value[12] = heeac_channelNum;
 *     ucontrol->value.integer.value[13] = mpeg_bitrate;
 *     ucontrol->value.integer.value[14] = mpeg_sampleRate;
 *     ucontrol->value.integer.value[15] = mpeg_layer;
 *     ucontrol->value.integer.value[16] = mpeg_channelNum;
 *     ucontrol->value.integer.value[17] = ac3_bitrate;
 *     ucontrol->value.integer.value[18] = ac3_sampleRate;
 *     ucontrol->value.integer.value[19] = ac3_channelnum;
 *     ucontrol->value.integer.value[20] = ac3_EAC3;
 * }
 * @endcode
 *
 * @param[out] adec_port_number int adec port num
 * @param[out] bAdecStart int
 * @param[out] userAdecFormat adec_src_codec_ext_type_t what user set
 *             Using LGE's terminology, The userAdecFormat is called as "codecSet"
 * @param[out] curAdecFormat adec_src_codec_ext_type_t actual current codec           \n
 *             info by driver                                                         \n
 *             Using LGE's terminology, The curAdecFormat is called as "codecDecoded" \n
 *             The curAdecFormat means the audio codec which the ADEC                 \n
 *             really and currently decodes.                                          \n
 *                                                                                    \n
 *             Case-1 :                                                               \n
 *                      If the parsed information of the Input type (HDMI) is         \n
 *                          EAC3_ATMOS      or                                        \n
 *                          AC4_ATMOS       or                                        \n
 *                          MAT_ATMOS       or                                        \n
 *                          TRUEHD_ATMOS,                                             \n
 *                      and the real audio input is also                              \n
 *                          EAC3_ATMOS      or                                        \n
 *                          AC4_ATMOS       or                                        \n
 *                          MAT_ATMOS       or                                        \n
 *                          TRUEHD_ATMOS,                                             \n
 *                      in this case, the adec will be started with                   \n
 *                          EAC3_ATMOS      or                                        \n
 *                          AC4_ATMOS       or                                        \n
 *                          MAT_ATMOS       or                                        \n
 *                          TRUEHD_ATMOS,                                             \n
 *                      in other case, if the soc-bsp has some problems so that       \n
 *                      the ATMOS effect cannot be expressed,                         \n
 *                      in this case, the curAdecFormat should be                     \n
 *                          EAC3 or                                                   \n
 *                          AC4  or                                                   \n
 *                          MAT  or                                                   \n
 *                          TRUEHD.                                                   \n
 *                                                                                    \n
 *             Case-2 :                                                               \n
 *                      If the parsed information of the Input type (HDMI) is         \n
 *                          EAC3            or                                        \n
 *                          AC4             or                                        \n
 *                          MAT             or                                        \n
 *                          TRUEHD,                                                   \n
 *                      and the real audio input is also                              \n
 *                          EAC3_ATMOS      or                                        \n
 *                          AC4_ATMOS       or                                        \n
 *                          MAT_ATMOS       or                                        \n
 *                          TRUEHD_ATMOS,                                             \n
 *                      in this case, the adec will be started with                   \n
 *                          EAC3            or                                        \n
 *                          AC4             or                                        \n
 *                          MAT             or                                        \n
 *                          TRUEHD,                                                   \n
 *                      in this case, the curAdecFormat should be                     \n
 *                          EAC3_ATMOS      or                                        \n
 *                          AC4_ATMOS       or                                        \n
 *                          MAT_ATMOS       or                                        \n
 *                          TRUEHD_ATMOS.                                             \n
 *                      in other case, if  the soc-bsp has some problems so that      \n
 *                      the ATMOS effect cannot be expressed,                         \n
 *                      in this case, the curAdecFormat should be                     \n
 *                          EAC3            or                                        \n
 *                          AC4             or                                        \n
 *                          MAT             or                                        \n
 *                          TRUEHD.                                                   \n
 *                                                                                    \n
 *             When channel is changed or input is changed, the webOS mw uses this    \n
 *             information for judging whether the ADEC produces the decoded audio    \n
 *             or not.If this information is SRC_CODEC_UNKNOWN, the webOS mw          \n
 *             considers that the ADEC does not produce any decoded Audio.            \n
 *             If the information is other codec except SRC_CODEC_UNKNOWN,            \n
 *             the webOS mw considers that the ADEC is now producing some             \n
 *             decoded Audio. According to this principle, the timing when            \n
 *             this information is changed from SRC_CODEC_UNKNOWN to other            \n
 *             valid codec should be the time when Audio PTS and                      \n
 *             STC are matched each other.                                            \n
 * @endcode
 * @param[out] sourceAdecFormat adec_src_codec_ext_type_t actual source codec
 *             info by driver
 *             Using LGE's terminology, The sourceAdecFormat is called as "codecSrc"
 *             The sourceAdecFormat means the audio codec of the real audio input
 *             which is currently being supplied to the ADEC input.                       \n
 *                                                                                        \n
 *             Case-1 :                                                                   \n
 *                      If the parsed information of the SI (DTV) is AAC,  \n
 *                      but its real audio input is HEAAC,                 \n
 *                      in this case, the adec will be started with AAC,   \n
 *                      but the sourceAdecFormat should be HEAAC.          \n
 *             Case-2 :                                                    \n
 *                      If the parsed information of the SI (DTV) is HEAAC,\n
 *                      but its real audio input is AAC,                   \n
 *                      in this case, the adec will be started with HEAAC, \n
 *                      but the sourceAdecFormat should be AAC.            \n
 *             Case-3 :                                                                   \n
 *                      If the parsed information of the Input type (HDMI) is             \n
 *                          EAC3            or                                            \n
 *                          AC4             or                                            \n
 *                          MAT             or                                            \n
 *                          TRUEHD,                                                       \n
 *                      but its real audio input is                                       \n
 *                          EAC3_ATMOS      or                                            \n
 *                          AC4_ATMOS       or                                            \n
 *                          MAT_ATMOS       or                                            \n
 *                          TRUEHD_ATMOS,                                                 \n
 *                     in this case, the adec will be started with                        \n
 *                          EAC3 or                                                       \n
 *                          AC4 or                                                        \n
 *                          MAT or                                                        \n
 *                          TRUEHD,                                                       \n
 *                     but the sourceAdecFormat should be                                 \n
 *                          EAC3_ATMOS      or                                            \n
 *                          AC4_ATMOS       or                                            \n
 *                          MAT_ATMOS       or                                            \n
 *                          TRUEHD_ATMOS.                                                 \n
 *             Case-4 :                                                                   \n
 *                     If the parsed information of the Input type (HDMI) is              \n
 *                          EAC3_ATMOS      or                                            \n
 *                          AC4_ATMOS       or                                            \n
 *                          MAT_ATMOS       or                                            \n
 *                          TRUEHD_ATMOS,                                                 \n
 *                     but its real audio input is                                        \n
 *                          EAC3            or                                            \n
 *                          AC4             or                                            \n
 *                          MAT             or                                            \n
 *                          TRUEHD,                                                       \n
 *                     in this case, the adec will be started with                        \n
 *                          EAC3_ATMOS      or                                            \n
 *                          AC4_ATMOS       or                                            \n
 *                          MAT_ATMOS       or                                            \n
 *                          TRUEHD_ATMOS,                                                 \n
 *                     but the sourceAdecFormat should be                                 \n
 *                          EAC3            or                                            \n
 *                          AC4             or                                            \n
 *                          MAT             or                                            \n
 *                          TRUEHD.                                                       \n
 * @param[out] curAdecInputPort adec_src_port_index_ext_type_t
 * @param[out] prevAdecInputPort adec_src_port_index_ext_type_t
 * @param[out] curAdecDualMonoMode adec_dualmono_mode_ext_type_t
 * @param[out] IsEsExist int
 * @param[out] audioMode adec_tp_mode_ext_type_t
 * @param[out] heaac_version int AAC=0x0, HE-AACv1=0x1, HE-AACv2=0x2
 * @param[out] heaac_trasmissionformat int LOAS/LATM=0x0, ADTS=0x1
 * @param[out] heeac_channelNum int Audio Channel number
 * @param[out] mpeg_bitrate int Bit rate
 * @param[out] mpeg_sampleRate int Sampling rate
 * @param[out] mpeg_layer int MPEG audio layer
 * @param[out] mpeg_channelNum int Audio Channel Number
 * @param[out] ac3_bitrate int Bit rate
 * @param[out] ac3_sampleRate int Sampling rate
 * @param[out] ac3_channelnum int Audio channel number
 * @param[out] ac3_EAC3 int AC3=0x0, EAC3=0x1
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress

 */
#define ADEC0_INFO "Adec0 Info"

/**
 * @see ADEC0_INFO
 */
#define ADEC1_INFO "Adec1 Info"

/**
 * @see ADEC0_INFO
 */
#define ADEC2_INFO "Adec2 Info"

/**
 * @see ADEC0_INFO
 */
#define ADEC3_INFO "Adec3 Info"

/**
 * @brief Audio Description On/Off
 * @li priority : 4
 *
 * @rst
 * Functional Requirements
 *   API that sets AudioDescription on / off The Dolby AC-4 Decoder supports two
 *   presentation selection mode : a preference-based selection and an index-based
 *   selection. This function used on an a preference-based selection mode.
 *
 *   If you can not mix SPDIF ES, you should only output ES of ADEC set to main
 *   audio. This API does not call when Audio Description is off, and when Audio
 *   Description changes from on to off, bOnOff parameter is set to OFF Call to
 *   inform driver that AD is off. Also, when AD is on, the bOnOff parameter of
 *   the API is called ON. For example, if AD is set to 1 in Main Audio and AD
 *   audio ADEC is set to 0 in Port
 *
 *   Main ADEC refers to the value set in "Sndout MainAudio Output". Driver should
 *   be used for AD Volume or AD Pan / Fade application by internally managing the
 *   port where AD audio is used through this API.
 *
 *   This function must be called before both the Main ADEC and ADEC for Audio
 *   Description are started.
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
 * @rst
 * Functional Requirements
 *   When this function is called, it tells the PTS of the currently decoded
 *   audio.
 *
 *   32bit of the most significant bit (MSB) of 33bit of PTS is transmitted as
 *   output parameter pPts.
 *
 *   LG MW is used to display the progress time of Audio PTS obtained through this
 *   function during playback of Radio Channel recordings. (Using Video PTS for
 *   recordings with video)
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
 * @rst
 * Functional Requirements
 *   The Dolby AC-4 Decoder supports two presentation selection mode : a
 *   preference-based selection and an index-based selection.
 *
 *   This function used on an a preference-based selection mode. This is the API
 *   to set the first language of AC-4 decoder. (See "Selection using system-level
 *   preferences" of "Dolby MS12 Multistream Decoder Implementation integration
 *   manual") adecIndex determines which decoder to set the First Language.
 *   enCodeType determines whether to pass the firstLang value as a 2byte ISO639-1
 *   type or as a 3byte ISO639-2 type.
 *
 *   @li firstLang sets the first language of the AC-4 decoder.
 *   @li firstLang is passed as the upper 2 bytes of UINT32 if enCodeType is ISO
 *   639-1 type, and 0 as the remaining lower 2 bytes. example: 'e''n'00
 *   @li firstLang is passed in the upper 3 bytes of UINT32 if the enCodeType is
 *   ISO 639-2 type and 0 in the last 1 byte. example: 'e''n''g'0
 *
 *   When several languages are delivered to one ES in AC-4, first language
 *   selected in First Language is selected and output.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   Because this API is used only on platforms that support AC-4, on platforms
 *   that do not support AC-4, configure the API with dummy.
 * @endrst
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
 * @rst
 * Functional Requirements
 *   The Dolby AC-4 Decoder supports two presentation selection mode : a
 *   preference-based selection and an index-based selection.
 *
 *   This function used on an a preference-based selection mode. This is the API
 *   for setting the Second Language of AC-4 decoder. (See "Selection using
 *   system-level preferences" of "Dolby MS12 Multistream Decoder Implementation
 *   integration manual") adecIndex determines which decoder will set Second
 *   Language. enCodeType determines whether to pass the value of secondLang as
 *   2byte ISO639-1 type or as 3byte ISO639-2 type.
 *
 *   @li secondLang sets the Second Language of the AC-4 decoder.
 *   @li secondLang is passed to upper two bytes of UINT32 if enCodeType is ISO
 *   639-1 type, and to 0 for the remaining lower 2 bytes. example: 'e''n'00
 *   @li secondLang is passed as the upper 3 bytes of UINT32 if the enCodeType is
 *   ISO 639-2 type, and 0 as the last 1 byte. example: 'e''n''g'0
 *
 *   If several languages are delivered to one ES in AC-4, if there is no language
 *   selected in First Language, Second Language is selected and decoded first.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   Because this API is used only on platforms that support AC-4, on platforms
 *   that do not support AC-4, configure the API with dummy.
 * @endrst
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
 * @rst
 * Functional Requirements
 *   The Dolby AC-4 Decoder supports two presentation selection mode : a
 *   preference-based selection and an index-based selection. This function used
 *   on an a preference-based selection mode. This is an API to set the Audio
 *   Description (AD) Type of AC-4 decoder. (See "Selection using system-level
 *   preferences" of "Dolby MS12 Multistream Decoder Implementation integration
 *   manual")
 *
 *   adecIndex determines which decoder the AD type is set to. enADType is entered
 *   as adec_ac4_ad_ext_type_t .
 *
 *   Currently, LG MW uses only ADEC_AC4_AD_TYPE_NONE and ADEC_AC4_AD_TYPE_VI, and
 *   the remaining define is for future use. ADEC_AC4_AD_TYPE_NONE means AD off.
 *   ADEC_AC4_AD_TYPE_VI means AD on for Visually Impaired (VI). Unlike
 *   conventional AD, which uses dual decoding implemented in DVB, AC-4 can
 *   transmit Main Audio and AD Audio to one ES.
 *
 *   In case that Main Audio and AD Audio exist together in one ES in AC-4, if AD
 *   Type is set to ADEC_AC4_AD_TYPE_VI, Main Audio and AD Audio are decoded
 *   together and output.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   Because this API is used only on platforms that support AC-4, on platforms
 *   that do not support AC-4, configure the API with dummy.
 * @endrst
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
 * @rst
 * Functional Requirements
 *   The Dolby AC-4 Decoder supports two presentation selection mode : a
 *   preference-based selection and an index-based selection. This function used
 *   on an a preference-based selection mode. It is an API to set priority between
 *   Language and Audio Description (AD) when Presentation is selected in AC-4
 *   decoder. (See "Selection using system-level preferences" of "Dolby MS12
 *   Multistream Decoder Implementation integration manual")
 *
 *   In other words, do you prefer AD to select presentation? It is an API that
 *   decides whether to set the language first.
 *
 *   For example, if Presentation is configured as follows, Presentation 1 will be
 *   selected if PrioritizeADType is TRUE even if First-Language is set to German.
 *   @li Presentation 1: English + AD
 *   @li Presentation 2: German Non AD
 *
 *   adecIndex determines which decoder the AD type is set to.
 *   @li If bIsEnable is TRUE, set Presentation to AD first.
 *   @li If bIsEnable is FALSE, set the presentation with Language (First, Second
 *   Language setting) as priority. (See 3.3.3.48 and 3.3.3.49)
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   Because this API is used only on platforms that support AC-4, on platforms
 *   that do not support AC-4, configure the API with dummy.
 * @endrst
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
 * @rst
 * Functional Requirements
 *   Enable or disable TruSurround:X Height upmix for non-immersive channel layout
 *   (= inputs without discrete height channels)
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
 * @rst
 * Functional Requirements
 *   The Dolby AC-4 Decoder supports two presentation selection mode : a
 *   preference-based selection and an index-based selection. This function used
 *   on an a preference-based selection mode. It is an API to set Audio
 *   Description (AD)  Enable or Disable when Presentation is selected in AC-4
 *   decoder.(See "Selection using system-level preferences" of "Dolby MS12
 *   Multistream Decoder Implementation integration manual")
 *
 *   Using Adec AC4 AutoADType" set AUDIO_AC4AD_TYPE_NONE, and  "Adec AC4
 *   AutoADMixing" set to FALSE. AD On - Adec AC4 AutoADType" set
 *   AUDIO_AC4AD_TYPE_VI, and  "Adec AC4 AutoADMixing" set to TRUE.
 *
 *   For example, if Presentation is configured as follows, Presentation 2 will be
 *   selected if AutoADMixing is TRUE. Presentation 1 will be selected if
 *   AutoADMixing is FALSE.
 *   @li Presentation 1: English
 *   @li Presentation 2: English + AD
 *
 *   adecIndex determines which decoder the AD type is set to.
 *   @li If bIsEnable is TRUE, set Presentation to AD.
 *   @li If bIsEnable is FALSE, set the presentation to non AD.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   Because this API is used only on platforms that support AC-4, on platforms
 *   that do not support AC-4, configure the API with dummy.
 * @endrst
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
 * @rst
 * Functional Requirements
 *   This is the API to set Presentation Group Index of AC-4 decoder. (See
 *   "Presentation selection" of "Dolby MS12 Multistream Decoder Implementation
 *   integration manual") The Dolby AC-4 Decoder supports two presentation
 *   selection mode : a preference-based selection and an index-based selection.
 *
 *   This function used on an index-based selection mode. adecIndex determines
 *   which decoder to set presentation selection mode. adec_ac4_pres_group_idx
 *   sets the Presentation Group Index(PGI) of the AC-4 decoder.
 *
 *   A range of adec_ac4_pres_group_idx is 0 ~ 0x20. Max Value is 0x20. This value
 *   means not select Presentation Group Index(). When Presentation Group Index()
 *   is not select, decoder select and play on a preference-based selection.
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
 * @brief gain value for AC4 Dialogue Enhancement Gain.
 * @li priority : 4
 *
 * @rst
 * Functional Requirements
 *   Set OTT mode and ATMOS Locking for Netflix. Netflix wants OTT mode and ATMOS
 *   Locking.  Refer to IIDK MS12 1.3.2(2.2.1) or later.
 *   @li When Netflix App start, LGE MW enable OTTMode.
 *   @li When Netflix App is finished, LGE MW Disable OTTMode with this API.
 *   @li When Netflix App want to set ATMOS Locking, LGE MW will enable/disable
 *   ATMOSLocking with this API.
 *
 *   ATMOS Locking can work after OTT mode is enabled.
 *
 *   Default is bIsOTTEnable=FALSE and bIsATMOSLockingEnable=FALSE.
 *
 *   If LGE MW call with bIsOTTEnable=FALSE and bIsATMOSLockingEnable=TRUE, the
 *   API should  returen FALSE without any action. This API can called in
 *   duplicate and BSP set and remain state as bIsOTTEnable and
 *   bIsATMOSLockingEnable.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 * @endrst
 *
 * @code
 * //Example
 * amixer -c 0 cset name="Adec Dolby OTTMode" 1,0 //returen OK (OTT mode is enabled, ATMOSLocking is disabled)
 * amixer -c 0 cset name="Adec Dolby OTTMode" 1,1 //returen OK (OTT mode is enabled, ATMOSLocking is enabled)
 *
 * amixer -c 0 cset name="Adec Dolby OTTMode" 1,0 //reture OK (OTT mode is enabled, ATMOSLocking is disabled)
 * amixer -c 0 cset name="Adec Dolby OTTMode" 0,1 //reture NOT_OK (No Action)
 *
 * amixer -c 0 cset name="Adec Dolby OTTMode" 0,0 //reture OK (OTT mode is disabled, ATMOSLocking is disabled)
 * @endcode
 *
 * Netflix App will control ATMOS Locking through LGE MW This feature is only
 * supported on IIDK MS12 1.3.2 (MS12 2.2.1) or later. If the BSP is using less
 * than MS12 1.3.2 (MS12 2.2.1), make dummy function that return NOT_OK.
 *
 * This API must support from Y19 Model (webOS4.5). This API should be supported
 * on also Y18 model(webOS4.0) supporing TV ATMOS but ATMOS Locking will be not
 * used for Y18 model.
 *
 * @b Pseudocode
 * @code
 * adec_dolby_ottmode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     UINT32 bIsOTTEnable= ucontrol->value.integer.value[0];
 *     UINT32 bIsATMOSLockingEnable= ucontrol->value.integer.value[1];
 *     // set ott param
 * }
 *
 * adec_dolby_ottmode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bIsOTTEnable;
 *     ucontrol->value.integer.value[1] = bIsATMOSLockingEnable;
 * }
 * @endcode
 *
 * @param[in] bIsOTTEnable int Enable/Disable OTTmode
 * @param[in] bIsATMOSLockingEnable int Enable/Disable ATMOSLocking
 *
 * @param[out] bIsOTTEnable int OTTmode status
 * @param[out] bIsATMOSLockingEnable int ATMOS Locking Status
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_DOLBY_OTTMODE "Adec Dolby OTTMode"

/**
 * @brief return the status of ADEC buffer
 * @li priority : 4
 *
 * @rst
 * Functional Requirements
 *   When this function called, it should be return buffer status for Adec.
 *
 *   This function called when saved radio ts data play on Dasy.
 *
 *   Dasy will check the max and freesize for decide how much ts data push to
 *   sdec.
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
 * @rst
 * Functional Requirements
 *   When this function called, it should be control associated audio mixer balance
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

/**
 * @brief adec lipsync offset
 * @li priority : 5
 *
 * @rst
 * Functional Requirements
 *   When this function called, it should be control Audio PTS offset
 *   This function is called before "Adec Start".
 *   And audio pts offset is applied after called "Adec Start".
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms, if there are no special reasons.
 *
 * Constraints
 *   When video pts lead audio pts less than 500ms,
 *   adjust 500ms offset will cause video keep drop
 *   This function is called after "Adec Master SyncMode".
 * @endrst
 *
 * @b Pseudocode
 * @code
 * adec_lipsync_offset_put(struct snd_kcontrol *kcontrol, struct
 *     snd_ctl_elem_value *ucontrol) {
 *     int adec_port_num = ucontrol->value.integer.value[0];
 *     int offset_time = ucontrol->value.integer.value[1];
 * }
 *
 * adec_lipsync_offset_get(struct snd_kcontrol *kcontrol, struct
 *     snd_ctl_elem_value *ucontrol) { // Get adec lipsync offset
 *     ucontrol->value.integer.value[0] = 0; // if "Adec UserMaxCapacity" value
 *     is smaller then this value, it should be 0xff
 *     ucontrol->value.integer.value[1] = adec0_lipsyc_offset;
 *     ucontrol->value.integer.value[2] = 1; // if "Adec UserMaxCapacity" value
 *     is smaller then this value, it should be 0xff
 *     ucontrol->value.integer.value[3] = adec1_lipsyc_offset;
 *     ucontrol->value.integer.value[4] = 2; // if "Adec UserMaxCapacity" value
 *     is smaller then this value, it should be 0xff
 *     ucontrol->value.integer.value[5] = adec2_lipsyc_offset;
 *     ucontrol->value.integer.value[6] = 3; // if "Adec UserMaxCapacity" value
 *     is smaller then this value, it should be 0xff
 *     ucontrol->value.integer.value[7] = adec3_lipsyc_offset;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int
 * @param[in] offset_time int 0 ~ 500 ms
 *
 * @param[out] adec_port0_number int := 0 (if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec0_lipsyc_offset int
 * @param[out] adec_port1_number int := 1 (if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec1_lipsyc_offset int
 * @param[out] adec_port2_number int := 2 (if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec2_lipsyc_offset int
 * @param[out] adec_port3_number int := 3 (if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec3_lipsyc_offset int
 *
 * @return 0 if it success. exception values if it fails.
 * @li -EBUSY Internal driver error happened
 * @li -EINVAL Invalid argument
 * @li -EALREADY Operation already in progress
 */
#define ADEC_LIPSYNC_OFFSET "Adec Lipsync Offset"

/**
 * @brief adec master syncmode on/off.
 * @li priority : 5
 *
 * @rst
 * Functional Requirements
 *   API to set the Master Sync mode When On, video and sync are synchronized by adec.
 *   If Off, video and sync are not synchronized.
 *   "Adec Master SyncMode" (On) is called for adec port where audio start is not done.
 *   "Adec Master SyncMode" can be called repeatably.
 *   Timing of calling "Adec Master SyncMode" might be called before adec start.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms, if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 * @endrst
 *
 * @b Pseudocode
 * @code 
 * adec_master_syncmode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol){
 *     int adec_index = ucontrol->value.integer.value[0];
 *     BOOLEAN OnOff = ucontrol->value.integer.value[1];
 *     // set syncmode on adec master.
 * }
 *
 * adec_master_syncmode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol){
 *     ucontrol->value.integer.value[0] = 0;
 *     ucontrol->value.integer.value[1] = adec0_master_syncmode;
 *     ucontrol->value.integer.value[2] = 1;
 *     ucontrol->value.integer.value[3] = adec1_master_syncmode;
 *     ucontrol->value.integer.value[4] = 2;
 *     ucontrol->value.integer.value[5] = adec2_master_syncmode;
 *     ucontrol->value.integer.value[6] = 3;
 *     ucontrol->value.integer.value[7] = adec3_master_syncmode;
 * }
 * @endcode
 *
 * @param[in] adec_port_num int adec port number
 * @param[in] adec_master_syncmode on/off
 *
 * @param[out] adec_port0_number int := 0 (if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec0_master_syncmode int
 * @param[out] adec_port1_number int := 1 (if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec1_master_syncmode int
 * @param[out] adec_port2_number int := 2 (if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec2_master_syncmode int
 * @param[out] adec_port3_number int := 3 (if port is smaller than adec number
 * of "Adec UserMaxCapacity", it should be 0xFF )
 * @param[out] adec3_master_syncmode int
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_MASTER_SYNCMODE "Adec Master SyncMode"

/**
 * adec_i2s_audio_type_ext_type_t is showing audio types to be used in I2S MCU.
 */
typedef enum adec_i2s_audio_type_ext_type {
    ADEC_I2S_AUDIO_TYPE_UNKNOWN = 0x00, /**< Audio Type is UNKNOWN */
    ADEC_I2S_AUDIO_TYPE_PCM          = 0x01, /**< Audio Type is PCM */
    ADEC_I2S_AUDIO_TYPE_AUTO       = 0x02, /**< Audio Type is Auto for I2S input (Check in BSP) */
    ADEC_I2S_AUDIO_TYPE_HBR       = 0x03, /**< Audio Type is HBR for I2S input (Check in BSP) */
} adec_i2s_audio_type_ext_type_t;

/**
 * adec_i2s_sample_frequency_ext_type_t is showing the sample frequency to be used in I2S MCU.
 */
typedef enum adec_i2s_sample_frequency_ext_type {
    ADEC_I2S_SAMPLE_FREQUENCY_UNKNOWN = 0x00, /**< Sample Frequency is UNKNOWN */
    ADEC_I2S_SAMPLE_FREQUENCY_32K = 32000, /**< 32 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_44_1K = 44100, /**< 44.1 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_48K = 48000, /**< 48 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_64K = 64000, /**< 64 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_88_2K = 88200, /**< 88.2 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_96K = 96000, /**< 96 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_128K = 128000, /**< 128 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_176_4K = 176400, /**< 176.4 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_192K = 192000, /**< 192 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_256K = 256000, /**< 256 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_352K = 352000, /**< 352 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_384K = 384000, /**< 384 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_512K = 512000, /**< 512 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_705K = 705000, /**< 705 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_768K = 768000, /**< 768 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_1024K = 1024000, /**< 1024 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_1411K = 1411000, /**< 1411 kHz */
    ADEC_I2S_SAMPLE_FREQUENCY_1536K = 1536000, /**< 1536 kHz */
} adec_i2s_sample_frequency_ext_type_t;

/**
 * @brief Set/Get Audio Type, Channel Number, Sample Frequency to I2S MCU
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   Function to set audio type, channel number, sample frequency for use in I2S MCU .
 *   The actual setting is handled by the I2S MCU
 *
 *   In the following cases, return ADEC_I2S_AUDIO_TYPE_PCM, 0, ADEC_I2S_SAMPLE_FREQUENCY_UNKNOWN without any action.
 *
 *   HDMI Cable not connected to HDMI ARC port.
 *   Audio codec information, sample frequency cannot be verified.
 *
 *   For example:
 *   PCM Contents, 2ch, 32 khz: ADEC_I2S_SRC_CODEC_PCM, 2, ADEC_I2S_SAMPLE_FREQUENCY_32K
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
 * adec_i2s_control_set(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int index = ucontrol->value.integer.value[0];
 *     i2s_audio_type = ucontrol->value.integer.value[1];
 *     i2s_channel_number = ucontrol->value.integer.value[2];
 *     i2s_sample_frequency = ucontrol->value.integer.value[3];
 * }
 * adec_i2s_control_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * { // Get Recently started ARC adec and codec
 *     ucontrol->value.integer.value[0] = index;
 *     ucontrol->value.integer.value[1] = i2s_audio_type;
 *     ucontrol->value.integer.value[2] = i2s_channel_number;
 *     ucontrol->value.integer.value[3] = i2s_sample_frequency;
 * }
 * @endcode
 *
 * @param[in] index int
 * @param[in] i2s_audio_type adec_i2s_audio_type_ext_type_t
 * @param[in] i2s_channel_number int
 * @param[in] i2s_sample_frequency adec_arc_codec_ext_type_t

 *
 * @param[out] index int
 * @param[out] i2s_audio_type adec_i2s_audio_type_ext_type_t
 * @param[out] i2s_channel_number int
 * @param[out] i2s_sample_frequency adec_arc_codec_ext_type_t
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_I2S_CONTROL "Adec I2S Control"

/**
 * @brief put/get Audio Input Drop Enable setting OnOff.
 * @li priority : 4
 *
 * @rst
 * Functional Requirements
 *   When audio switching occurs in hbbTV, incorrect audio tones are sometimes output.
 *   To address this, BSP needs to be able to identify if the current input is in hbbTV mode.
 *   Therefore, a new ALSA API is needed created for this purpose.
 *
 *   Using example.
 *   When current input is hbbTV, webOS sets Audio Input Drop Enable to '0'.
 *   When current input is not hbbTV, webOS sets Audio Input Drop Enable to '1'(default).
 *
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   There are no special constraints on this API function.
 * @endrst
 *
 * @code
 * //Example
 * amixer -c 0 cset name="Adec Audio Drop Enable" 1 //returen OK (Audio input drop setting is enabled)
 * amixer -c 0 cset name="Adec Audio Drop Enable" 0 //returen OK (Audio input drop setting is disabled)
 *
 * @endcode
 *
 * @b Pseudocode
 * @code
 * adec_audio_input_drop_enable_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     UINT32 bIsAdecAudioInputDropEnable= ucontrol->value.integer.value[0];
 *     // set audio input drop enable param
 * }
 *
 * adec_audio_input_drop_enable_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get audio input drop enable param
 *     ucontrol->value.integer.value[0] = bIsAdecAudioInputDropEnable;
 * }
 * @endcode
 *
 * @param[in] bIsAdecAudioInputDropEnable int Enable/Disable Audio input drop
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define ADEC_AUDIO_DROP_ENABLE "Adec Audio Drop Enable"

#endif
