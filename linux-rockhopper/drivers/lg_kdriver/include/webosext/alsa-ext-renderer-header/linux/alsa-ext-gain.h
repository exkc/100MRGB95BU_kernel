/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_GAIN_H
#define _ALSA_EXT_GAIN_H

#include <linux/alsa-ext/alsa-ext-common.h>

/**
 * @brief put/get gain value for input with duration
 *
 * priority:3
 *
 * @rst
 * Functional Requirements
 *   The Function set/get input gains on input resources with a duration
 *   Input gain is changes from a previous input gain
 *   to a new input gain during duration
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
 *     gain_input_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // input_type = ucontrol->value.integer.value[0];
 *     // input_port_num = ucontrol->value.integer.value[1];
 *     // gain = ucontrol->value.integer.value[2]; // set gain
 *     // duration = ucontrol->value.integer.value[3] // set duration
 *
 *     //
 *     // Functions
 *     //
 *     gain_input_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // ucontrol->value.integer.value[0] = 0 ; // := 0
 *     // ucontrol->value.integer.value[1] = adec0_gain;
 *     // ucontrol->value.integer.value[3] = adec0_duration;
 *     // ucontrol->value.integer.value[4] = 1 ; // := 1
 *     // ucontrol->value.integer.value[5] = adec1_gain;
 *     // ucontrol->value.integer.value[6] = adec1_duration;
 *     // ucontrol->value.integer.value[7] = 2 ; // := 2
 *     // ucontrol->value.integer.value[8] = adec2_gain;
 *     // ucontrol->value.integer.value[9] = adec2_duration;
 *     // ucontrol->value.integer.value[10] = 3; // := 3
 *     // ucontrol->value.integer.value[11] = adec3_gain;
 *     // ucontrol->value.integer.value[12] = adec3_duration;
 *     // ucontrol->value.integer.value[13] = 0; // := 0
 *     // ucontrol->value.integer.value[14] = amixer0_gain;
 *     // ucontrol->value.integer.value[15] = amixer0_duration;
 *     // ucontrol->value.integer.value[16] = 1; // := 1
 *     // ucontrol->value.integer.value[17] = amixer1_gain;
 *     // ucontrol->value.integer.value[18] = amixer1_duration;
 *     // ucontrol->value.integer.value[19] = 2; // := 2
 *     // ucontrol->value.integer.value[20] = amixer2_gain;
 *     // ucontrol->value.integer.value[21] = amixer2_duration;
 *     // ucontrol->value.integer.value[22] = 3; // := 3
 *     // ucontrol->value.integer.value[23] = amixer3_gain;
 *     // ucontrol->value.integer.value[24] = amixer3_duration;
 *     // ucontrol->value.integer.value[22] = 4; // := 4
 *     // ucontrol->value.integer.value[25] = amixer4_gain;
 *     // ucontrol->value.integer.value[26] = amixer4_duration;
 *     // ucontrol->value.integer.value[22] = 5; // := 5
 *     // ucontrol->value.integer.value[27] = amixer5_gain;
 *     // ucontrol->value.integer.value[28] = amixer5_duration;
 *     // ucontrol->value.integer.value[22] = 6; // := 6
 *     // ucontrol->value.integer.value[29] = amixer6_gain;
 *     // ucontrol->value.integer.value[30] = amixer6_duration;
 *     // ucontrol->value.integer.value[31] = 7; // := 7
 *     // ucontrol->value.integer.value[32] = amixer7_gain;
 *     // ucontrol->value.integer.value[33] = amixer7_duration;
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
 *     gain_input_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         input_type = ucontrol->value.integer.value[0];
 *         input_port_num = ucontrol->value.integer.value[1];
 *         gain = ucontrol->value.integer.value[2]; // set gain
 *         duration = ucontrol->value.integer.value[3] // set duration
 *         //gain is changed from a previous input gain to new input gain during duration
 *     }
 *
 *     gain_input_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     { // get GAIN status
 *         ucontrol->value.integer.value[0] = 0 ; // := 0
 *         ucontrol->value.integer.value[1] = adec0_gain;
 *         ucontrol->value.integer.value[3] = adec0_duration;
 *         ucontrol->value.integer.value[4] = 1 ; // := 1
 *         ucontrol->value.integer.value[5] = adec1_gain;
 *         ucontrol->value.integer.value[6] = adec1_duration;
 *         ucontrol->value.integer.value[7] = 2 ; // := 2
 *         ucontrol->value.integer.value[8] = adec2_gain;
 *         ucontrol->value.integer.value[9] = adec2_duration;
 *         ucontrol->value.integer.value[10] = 3; // := 3
 *         ucontrol->value.integer.value[11] = adec3_gain;
 *         ucontrol->value.integer.value[12] = adec3_duration;
 *         ucontrol->value.integer.value[13] = 0; // := 0
 *         ucontrol->value.integer.value[14] = amixer0_gain;
 *         ucontrol->value.integer.value[15] = amixer0_duration;
 *         ucontrol->value.integer.value[16] = 1; // := 1
 *         ucontrol->value.integer.value[17] = amixer1_gain;
 *         ucontrol->value.integer.value[18] = amixer1_duration;
 *         ucontrol->value.integer.value[19] = 2; // := 2
 *         ucontrol->value.integer.value[20] = amixer2_gain;
 *         ucontrol->value.integer.value[21] = amixer2_duration;
 *         ucontrol->value.integer.value[22] = 3; // := 3
 *         ucontrol->value.integer.value[23] = amixer3_gain;
 *         ucontrol->value.integer.value[24] = amixer3_duration;
 *         ucontrol->value.integer.value[22] = 4; // := 4
 *         ucontrol->value.integer.value[25] = amixer4_gain;
 *         ucontrol->value.integer.value[26] = amixer4_duration;
 *         ucontrol->value.integer.value[22] = 5; // := 5
 *         ucontrol->value.integer.value[27] = amixer5_gain;
 *         ucontrol->value.integer.value[28] = amixer5_duration;
 *         ucontrol->value.integer.value[22] = 6; // := 6
 *         ucontrol->value.integer.value[29] = amixer6_gain;
 *         ucontrol->value.integer.value[30] = amixer6_duration;
 *         ucontrol->value.integer.value[31] = 7; // := 7
 *         ucontrol->value.integer.value[32] = amixer7_gain;
 *         ucontrol->value.integer.value[33] = amixer7_duration;
 *     }
 * @endrst
 */
#define GAIN_INPUT_DURATION "Gain Input Duration"


/**
 * @brief put/get gain value for input.
 *
 * priority:3
 *
 * @rst
 * Functional Requirements
 *   Functions that put GAIN on Input Resource In the case of ADEC or AMIXER which
 *   is shown in the description, it must be indicated for the open / connected
 *   input.
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
 *     gain_input_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // input_type = ucontrol->value.integer.value[0];
 *     // input_port_num = ucontrol->value.integer.value[1];
 *     // gain = ucontrol->value.integer.value[2]; // set gain
 *
 *     //
 *     // Functions
 *     //
 *     gain_input_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // ucontrol->value.integer.value[0] = 0 ; // := 0
 *     // ucontrol->value.integer.value[1] = adec0_gain;
 *     // ucontrol->value.integer.value[2] = 1 ; // := 1
 *     // ucontrol->value.integer.value[3] = adec1_gain;
 *     // ucontrol->value.integer.value[4] = 2 ; // := 2
 *     // ucontrol->value.integer.value[5] = adec2_gain;
 *     // ucontrol->value.integer.value[6] = 3 ; // := 3
 *     // ucontrol->value.integer.value[7] = adec3_gain;
 *     // ucontrol->value.integer.value[8] = 0; // := 0
 *     // ucontrol->value.integer.value[9] = amixer0_gain;
 *     // ucontrol->value.integer.value[10] = 1; // := 1
 *     // ucontrol->value.integer.value[11] = amixer1_gain;
 *     // ucontrol->value.integer.value[11] = 2; // := 2
 *     // ucontrol->value.integer.value[12] = amixer2_gain;
 *     // ucontrol->value.integer.value[13] = 3; // := 3
 *     // ucontrol->value.integer.value[14] = amixer3_gain;
 *     // ucontrol->value.integer.value[15] = 4; // := 4
 *     // ucontrol->value.integer.value[16] = amixer4_gain;
 *     // ucontrol->value.integer.value[17] = 5; // := 5
 *     // ucontrol->value.integer.value[18] = amixer5_gain;
 *     // ucontrol->value.integer.value[19] = 6; // := 6
 *     // ucontrol->value.integer.value[20] = amixer6_gain;
 *     // ucontrol->value.integer.value[21] = 7; // := 7
 *     // ucontrol->value.integer.value[22] = amixer7_gain;
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
 *     gain_input_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         input_type = ucontrol->value.integer.value[0];
 *         input_port_num = ucontrol->value.integer.value[1];
 *         gain = ucontrol->value.integer.value[2]; // set gain
 *     }
 *
 *     gain_input_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     { // get GAIN status
 *         ucontrol->value.integer.value[0] = 0 ; // := 0
 *         ucontrol->value.integer.value[1] = adec0_gain;
 *         ucontrol->value.integer.value[2] = 1 ; // := 1
 *         ucontrol->value.integer.value[3] = adec1_gain;
 *         ucontrol->value.integer.value[4] = 2 ; // := 2
 *         ucontrol->value.integer.value[5] = adec2_gain;
 *         ucontrol->value.integer.value[6] = 3 ; // := 3
 *         ucontrol->value.integer.value[7] = adec3_gain;
 *         ucontrol->value.integer.value[8] = 0; // := 0
 *         ucontrol->value.integer.value[9] = amixer0_gain;
 *         ucontrol->value.integer.value[10] = 1; // := 1
 *         ucontrol->value.integer.value[11] = amixer1_gain;
 *         ucontrol->value.integer.value[11] = 2; // := 2
 *         ucontrol->value.integer.value[12] = amixer2_gain;
 *         ucontrol->value.integer.value[13] = 3; // := 3
 *         ucontrol->value.integer.value[14] = amixer3_gain;
 *         ucontrol->value.integer.value[15] = 4; // := 4
 *         ucontrol->value.integer.value[16] = amixer4_gain;
 *         ucontrol->value.integer.value[17] = 5; // := 5
 *         ucontrol->value.integer.value[18] = amixer5_gain;
 *         ucontrol->value.integer.value[19] = 6; // := 6
 *         ucontrol->value.integer.value[20] = amixer6_gain;
 *         ucontrol->value.integer.value[21] = 7; // := 7
 *         ucontrol->value.integer.value[22] = amixer7_gain;
 *     }
 *
 * @endrst
 */
#define GAIN_INPUT "Gain Input"

/**
 * @brief gain value for Audio description.
 *
 * priority:3
 *
 * @rst
 * Functional Requirements
 *   Functions that put GAIN on Output Resource Normally we don't use gain for
 *   optic in this function. MW use "Sndout Optic LG" function, if we need to
 *   change the optic volumes.
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
 *     gain_audiodescription_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // ad_gain = ucontrol->value.integer.value[1];
 *
 *     //
 *     // Functions
 *     //
 *     // gain_audiodescription_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // ucontrol->value.integer.value[0] = ad_GAIN;
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
 *     gain_audiodescription_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         ad_gain = ucontrol->value.integer.value[1];
 *         // set GAIN
 *     }
 *
 *     gain_audiodescription_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // get GAIN status
 *         ucontrol->value.integer.value[0] = ad_GAIN;
 *     }
 *
 * @endrst
 */
#define GAIN_AUDIODESCRIPTION "Gain AudioDescription"

/**
 * @brief gain value for output.
 *
 * priority:3
 *
 * @rst
 * Functional Requirements
 *   Functions that put GAIN on Output Resource Normally we don't use gain for
 *   optic in this function. MW use "Sndout Optic LG" function, if we need to
 *   change the optic volumes.
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
 *     gain_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // output_type = ucontrol->value.integer.value[0];
 *     // gain = ucontrol->value.integer.value[1];
 *
 *     //
 *     // Functions
 *     //
 *     gain_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *     struct snd_kcontrol{};
 *     struct snd_ctl_elem_value{};
 *
 *     // ucontrol->value.integer.value[0] = spk_GAIN;
 *     // ucontrol->value.integer.value[1] = optic_GAIN;
 *     // ucontrol->value.integer.value[2] = optic_lg_GAIN;
 *     // ucontrol->value.integer.value[3] = bluetooth_GAIN;
 *     // ucontrol->value.integer.value[4] = hp_GAIN;
 *     // ucontrol->value.integer.value[5] = arc_GAIN;
 *     // ucontrol->value.integer.value[6] = wisa_GAIN;
 *     // ucontrol->value.integer.value[7] = se_bt_GAIN;
 *     // ucontrol->value.integer.value[8] = capture_GAIN;
 *     // ucontrol->value.integer.value[9] = se_arc_GAIN;
 *     // ucontrol->value.integer.value[10] = se_bt_surround_GAIN;
 *     // ucontrol->value.integer.value[11] = wowcast_GAIN;
 *     // ucontrol->value.integer.value[12] = dap_bt_hp_GAIN;
 *     // ucontrol->value.integer.value[13] = line_out_GAIN;
 *     // ucontrol->value.integer.value[14] = dafc_GAIN;
 *     // ucontrol->value.integer.value[15] = dap_bt_GAIN;
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
 *     gain_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          output_type = ucontrol->value.integer.value[0];
 *          gain = ucontrol->value.integer.value[1];
 *          // set GAIN
 *     }
 *     gain_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *          // get GAIN status
 *          ucontrol->value.integer.value[0] = spk_GAIN;
 *          ucontrol->value.integer.value[1] = optic_GAIN;
 *          ucontrol->value.integer.value[2] = optic_lg_GAIN;
 *          ucontrol->value.integer.value[3] = bluetooth_GAIN;
 *          ucontrol->value.integer.value[4] = hp_GAIN;
 *          ucontrol->value.integer.value[5] = arc_GAIN;
 *          ucontrol->value.integer.value[6] = wisa_GAIN;
 *          ucontrol->value.integer.value[7] = se_bt_GAIN;
 *          ucontrol->value.integer.value[8] = capture_GAIN;
 *          ucontrol->value.integer.value[9] = se_arc_GAIN;
 *          ucontrol->value.integer.value[10] = se_bt_surround_GAIN;
 *          ucontrol->value.integer.value[11] = wowcast_GAIN;
 *          ucontrol->value.integer.value[12] = dap_bt_hp_GAIN;
 *          ucontrol->value.integer.value[13] = line_out_GAIN;
 *          ucontrol->value.integer.value[14] = dafc_GAIN;
 *          ucontrol->value.integer.value[15] = dap_bt_GAIN;
 *     }
 *
 * @endrst
 */
#define GAIN_OUTPUT "Gain Output"

#endif
