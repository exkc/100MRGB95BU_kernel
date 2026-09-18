/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_DELAY_H
#define _ALSA_EXT_DELAY_H

#include <linux/alsa-ext/alsa-ext-common.h>

/**
 * @brief input source type for audio latency time
 */
typedef enum delay_input_src_type {
    DELAY_INPUT_SRC_UNKNOWN = 0, // DEFAULT
    DELAY_INPUT_SRC_TP      = 1,
    DELAY_INPUT_SRC_ADC     = 2,
    DELAY_INPUT_SRC_AAD     = 3,
    DELAY_INPUT_SRC_HDMI    = 4,
    DELAY_INPUT_SRC_MEDIA   = 5,
    DELAY_INPUT_SRC_MAX     = 6,
} delay_input_src_type_t;

typedef enum low_latency_mode_type {
    LOW_LATENCY_MODE_OFF            = 0, /**< Off, which is default value */
    LOW_LATENCY_MODE_BYPASS_FADER   = 1, /**< bypass of fader in audio path */
} low_latency_mode_type_t;

/**
 * @brief put/get delay input/output
 *
 * priority:3
 *
 * @rst
 * Functional Requirements
 *   Function that Delays Input Resource. In the case of ADEC or AMIXER which is
 *   shown in the description, it must be indicated for the open / connected
 *   input. The reason why the input is set with the output is to set them
 *   together to reduce the number of times since monophonic effect occurs when
 *   setting output or input deplay.
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
 *     delay_inputoutput_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // input_type common_input_ext_type_t
 *     // port_index int
 *     // input_delay int 0 ~ 250 ms
 *     // output_type common_output_ext_type_t
 *     // output_delay int 0 ~ 400 ms
 *
 *     //
 *     // Functions
 *     //
 *     delay_inputoutput_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // adec_port0_number int := 0 (if port is smaller than adec number of "Adec UserMaxCapacity", it should be 0xFF )
 *     // delay int (default:0)
 *     // adec_port1_number int := 1 (same as adec_port0_number)
 *     // delay int (default:0)
 *     // adec_port2_number int := 2 (same as adec_port0_number)
 *     // delay int (default:0)
 *     // adec_port3_number int := 3 (same as adec_port0_number)
 *     // delay int (default:0)
 *     // amixer0_port_index int := 0 (if port is smaller than amixer number of "Adec UserMaxCapacity", it should be 0xFF )
 *     // delay int (default:0)
 *     // amixer1_port_index int := 1 (same as amixer_port0_number)
 *     // delay int (default:0)
 *     // amixer2_port_index int := 2 (same as amixer_port0_number)
 *     // delay int (default:0)
 *     // amixer3_port_index int := 3 (same as amixer_port0_number)
 *     // delay int (default:0)
 *     // amixer4_port_index int := 4 (same as amixer_port0_number)
 *     // delay int (default:0)
 *     // amixer5_port_index int := 5 (same as amixer_port0_number)
 *     // delay int (default:0)
 *     // amixer6_port_index int := 6 (same as amixer_port0_number)
 *     // delay int (default:0)
 *     // amixer7_port_index int := 7 (same as amixer_port0_number)
 *     // delay int (default:0)
 *     // spk_delay int (default:0)
 *     // optic_delay int (default:0)
 *     // optic_lg_delay int (default:0)
 *     // bluetooth_delay int (default:0) (it will be not used)
 *     // hp_delay int (default:0)
 *     // arc_delay int (default:0)
 *     // wisa_delay int (default:0)
 *     // sebt_delay int (default:0) (it will be not used)
 *     // capture_delay int (default:0) (it will be not used)
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
 *     delay_inputoutput_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         input_type = ucontrol->value.integer.value[0];
 *         input_port_num = ucontrol->value.integer.value[1];
 *         delay = ucontrol->value.integer.value[2];
 *         output_type = ucontrol->value.integer.value[3];
 *         delay = ucontrol->value.integer.value[4];
 *         // set delay
 *     }
 *
 *     delay_inputoutput_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // get delay status
 *         ucontrol->value.integer.value[0] = 0 ; // := 0
 *         ucontrol->value.integer.value[1] = adec0_delay;
 *         ucontrol->value.integer.value[2] = 1 ; // := 1
 *         ucontrol->value.integer.value[3] = adec1_delay;
 *         ucontrol->value.integer.value[4] = 2 ; // := 2
 *         ucontrol->value.integer.value[5] = adec2_delay;
 *         ucontrol->value.integer.value[6] = 3 ; // := 3
 *         ucontrol->value.integer.value[7] = adec3_delay;
 *         ucontrol->value.integer.value[8] = 0; // := 0
 *         ucontrol->value.integer.value[9] = amixer0_delay;
 *         ucontrol->value.integer.value[10] = 1; // := 1
 *         ucontrol->value.integer.value[11] = amixer1_delay;
 *         ucontrol->value.integer.value[11] = 2; // := 2
 *         ucontrol->value.integer.value[12] = amixer2_delay;
 *         ucontrol->value.integer.value[13] = 3; // := 3
 *         ucontrol->value.integer.value[14] = amixer3_delay;
 *         ucontrol->value.integer.value[15] = 4; // := 4
 *         ucontrol->value.integer.value[16] = amixer4_delay;
 *         ucontrol->value.integer.value[17] = 5; // := 5
 *         ucontrol->value.integer.value[18] = amixer5_delay;
 *         ucontrol->value.integer.value[19] = 6; // := 6
 *         ucontrol->value.integer.value[20] = amixer6_delay;
 *         ucontrol->value.integer.value[21] = 7; // := 7
 *         ucontrol->value.integer.value[22] = amixer7_delay;
 *         ucontrol->value.integer.value[23] = spk_delay;
 *         ucontrol->value.integer.value[24] = optic_delay;
 *         ucontrol->value.integer.value[25] = optic_lg_delay;
 *         ucontrol->value.integer.value[26] = bluetooth_delay;
 *         ucontrol->value.integer.value[27] = hp_delay;
 *         ucontrol->value.integer.value[28] = arc_delay;
 *         ucontrol->value.integer.value[29] = wisa_delay;
 *         ucontrol->value.integer.value[30] = sebt_delay;
 *         ucontrol->value.integer.value[31] = capture_delay;
 *         ucontrol->value.integer.value[32] = se_arc_delay;
 *         ucontrol->value.integer.value[33] = se_bt_surround_delay;
 *         ucontrol->value.integer.value[34] = wowcast_delay;
 *         ucontrol->value.integer.value[35] = dap_bt_hp_delay;
 *         ucontrol->value.integer.value[36] = line_out_delay;
*          ucontrol->value.integer.value[37] = dafc_delay;
*          ucontrol->value.integer.value[38] = dap_bt_delay;
 *     }
 *
 * @endrst
 */
#define DELAY_INPUTOUTPUT "Delay InputOutput"

/**
 * @brief put/get audio letency time
 *
 * priority:3
 *
 * @rst
 * Functional Requirements
 *   This function gets the audio processing time that occurs on the audio path
 *   according to the set parameters. Since eARC is not added to the sound mode,
 *   when calling get on ARC, the value according to the currently set ARC/eARC
 *   mode is returned. Therefore, ARC / eARC setup must be completed before
 *   calling this function. The "Delay InputOutput" function should not affect
 *   this function. The returned audio latency uses the value defined inside the driver.
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
 *     audio_latency_time_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // input_type = ucontrol->value.integer.value[0];
 *     // port_index = ucontrol->value.integer.value[1];
 *     // input_source = ucontrol->value.integer.value[2];
 *     // output_type = ucontrol->value.integer.value[3];
 *     // reserved_0 = ucontrol->value.integer.value[4];
 *     // reserved_1 = ucontrol->value.integer.value[5];
 *     // reserved_2 = ucontrol->value.integer.value[6];
 *     // audio_latency_time = ucontrol->value.integer.value[7];
 *
 *     //
 *     // Functions
 *     //
 *     audio_latency_time_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // ucontrol->value.integer.value[0] = input_type;
 *     // ucontrol->value.integer.value[1] = port_index;
 *     // ucontrol->value.integer.value[2] = input_source;
 *     // ucontrol->value.integer.value[3] = output_type;
 *     // ucontrol->value.integer.value[4] = reserved_0;
 *     // ucontrol->value.integer.value[5] = reserved_1;
 *     // ucontrol->value.integer.value[6] = reserved_2;
 *     // ucontrol->value.integer.value[7] = audio_latency_time;
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
 *     audio_latency_time_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         input_type = ucontrol->value.integer.value[0];
 *         port_index = ucontrol->value.integer.value[1];
 *         input_source = ucontrol->value.integer.value[2];
 *         output_type = ucontrol->value.integer.value[3];
 *         reserved_0 = ucontrol->value.integer.value[4];
 *         reserved_1 = ucontrol->value.integer.value[5];
 *         reserved_2 = ucontrol->value.integer.value[6];
 *         audio_latency_time = ucontrol->value.integer.value[7];
 *     }
 *
 *
 *     audio_latency_time_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // get audio latency time
 *         ucontrol->value.integer.value[0] = input_type;
 *         ucontrol->value.integer.value[1] = port_index;
 *         ucontrol->value.integer.value[2] = input_source;
 *         ucontrol->value.integer.value[3] = output_type;
 *         ucontrol->value.integer.value[4] = reserved_0;
 *         ucontrol->value.integer.value[5] = reserved_1;
 *         ucontrol->value.integer.value[6] = reserved_2;
 *         ucontrol->value.integer.value[7] = audio_latency_time;
 *     }
 * @endrst
 */
#define AUDIO_LATENCY_TIME "Audio Latency Time"

/**
 * @brief low latency mode
 * @li priority 1
 *
 * Set low latency mode on/off. This API would be called in run-time \n
 * If low latency mode is on, bsp would minimize buffer of audio data path so that
 * audio is out as soon as possible
 * for example, audio fader in bsp could be turned off by this API
 * Detailed path in bsp audio for this API would not be described
 * If it is set as LOW_LATENCY_MODE_OFF, low latency mode is off \n
 * If it is set as LOW_LATENCY_MODE_BYPASS_FADER(1), low latency mode is on with fader bypass \n
 * Mode could be added with new requirement
 * input type and port info are needed to set specific path where low latency is set
 *
 * @code
 * low_latency_mode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     common_input_ext_type_t input_type = ucontrol->value.integer.value[0];
 *     int input_port_num = ucontrol->value.integer.value[1];
 *     low_latency_mode_type_t low_latency_mode = ucontrol->value.integer.value[2];
 *     // set mode param
 * }
 *
 * low_latency_mode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get low latency mode for each input
 *     ucontrol->value.integer.value[0] = 0 ; // := 0
 *     ucontrol->value.integer.value[1] = adec0_mode;
 *     ucontrol->value.integer.value[2] = 1 ; // := 1
 *     ucontrol->value.integer.value[3] = adec1_mode;
 *     ucontrol->value.integer.value[4] = 2 ; // := 2
 *     ucontrol->value.integer.value[5] = adec2_mode;
 *     ucontrol->value.integer.value[6] = 3 ; // := 3
 *     ucontrol->value.integer.value[7] = adec3_mode;
 *     ucontrol->value.integer.value[8] = 0; // := 0
 *     ucontrol->value.integer.value[9] = amixer0_mode;
 *     ucontrol->value.integer.value[10] = 1; // := 1
 *     ucontrol->value.integer.value[11] = amixer1_mode;
 *     ucontrol->value.integer.value[11] = 2; // := 2
 *     ucontrol->value.integer.value[12] = amixer2_mode;
 *     ucontrol->value.integer.value[13] = 3; // := 3
 *     ucontrol->value.integer.value[14] = amixer3_mode;
 *     ucontrol->value.integer.value[15] = 4; // := 4
 *     ucontrol->value.integer.value[16] = amixer4_mode;
 *     ucontrol->value.integer.value[17] = 5; // := 5
 *     ucontrol->value.integer.value[18] = amixer5_mode;
 *     ucontrol->value.integer.value[19] = 6; // := 6
 *     ucontrol->value.integer.value[20] = amixer6_mode;
 *     ucontrol->value.integer.value[21] = 7; // := 7
 *     ucontrol->value.integer.value[22] = amixer7_mode;
 * }
 * @endcode
 *
 * @param[in] input_type common_input_ext_type_t
 * @param[in] input_port_num int
 * @param[in] low_latency_mode low_latency_mode_type_t
 *
 * @param[out] adec_port0_number int := 0 (means adec0)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] adec_port1_number int := 1 (means adec1)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] adec_port2_number int := 2 (means adec2)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] adec_port3_number int := 3 (means adec3)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] amixer0_port_index int := 0 (means amixer0)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] amixer1_port_index int := 1 (means amixer1)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] amixer2_port_index int := 2 (means amixer2)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] amixer3_port_index int := 3 (means amixer3)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] amixer4_port_index int := 4 (means amixer4)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] amixer5_port_index int := 5 (means amixer5)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] amixer6_port_index int := 6 (means amixer6)
 * @param[out] mode low_latency_mode_type_t (default:0)
 * @param[out] amixer7_port_index int := 7 (means amixer7)
 * @param[out] mode low_latency_mode_type_t (default:0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LOW_LATENCY_MODE "Low Latency Mode"

#endif
