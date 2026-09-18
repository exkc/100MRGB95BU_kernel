/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_MUTE_H
#define _ALSA_EXT_MUTE_H

#include <linux/alsa-ext/alsa-ext-common.h>

/**
 * @brief mute value for input.
 * priority : 3
 *
 * @rst
 * Functional Requirements
 *   Function for Mute Input Resource In the case of ADEC or AMIXER, each port
 *   number exists. When the specific ADEC is opened and the state where the Mute
 *   can be set, Get "Mute Input" will show the port number of the specific ADEC
 *   and indicate Default Mute Status. If Mute is operated via put, it should be
 *   able to check whether the corresponding Mute has been operated normally via
 *   Get.
 *   When ARC/eARC soundoutput with passthrough mode is connected with Adec or Amixer
 *   driver should not send data to arc/earc if Adec or Amixer connected with ARC/eARC
 *   is set "Mute Input" true
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
 *     mute_input_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     mute_input_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Mute Input"
 *
 *     struct snd_ctl_elem_value{};
 *     value[0]: input_type
 *        COMMON_NO_INPUT     = 0x0000
 *        COMMON_INPUT_ADEC   = 0x0001
 *        COMMON_INPUT_AMIXER = 0x0010
 *     value[1]: input_port_num
 *        Adec supports 0~1
 *        Amixer supports 0~7
 *     value[2]: muteOnOff (on:1, off:0) (default:0)
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
 *     mute_input_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         input_type = ucontrol->value.integer.value[0];
 *         input_port_num = ucontrol->value.integer.value[1];
 *         mute_status = ucontrol->value.integer.value[2];
 *         // set mute
 *     }
 *
 *     mute_input_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // get mute status
 *         ucontrol->value.integer.value[0] = 0 ; // := 0
 *         ucontrol->value.integer.value[1] = adec0_mute_status;
 *         ucontrol->value.integer.value[2] = 1 ; // := 1
 *         ucontrol->value.integer.value[3] = adec1_mute_status;
 *         ucontrol->value.integer.value[4] = 2 ; // := 2
 *         ucontrol->value.integer.value[5] = adec2_mute_status;
 *         ucontrol->value.integer.value[6] = 3 ; // := 3
 *         ucontrol->value.integer.value[7] = adec3_mute_status;
 *         ucontrol->value.integer.value[8] = 0; // := 0
 *         ucontrol->value.integer.value[9] = amixer0_mute_status;
 *         ucontrol->value.integer.value[10] = 1; // := 1
 *         ucontrol->value.integer.value[11] = amixer1_mute_status;
 *         ucontrol->value.integer.value[11] = 2; // := 2
 *         ucontrol->value.integer.value[12] = amixer2_mute_status;
 *         ucontrol->value.integer.value[13] = 3; // := 3
 *         ucontrol->value.integer.value[14] = amixer3_mute_status;
 *         ucontrol->value.integer.value[15] = 4; // := 4
 *         ucontrol->value.integer.value[16] = amixer4_mute_status;
 *         ucontrol->value.integer.value[17] = 5; // := 5
 *         ucontrol->value.integer.value[18] = amixer5_mute_status;
 *         ucontrol->value.integer.value[19] = 6; // := 6
 *         ucontrol->value.integer.value[20] = amixer6_mute_status;
 *         ucontrol->value.integer.value[21] = 7; // := 7
 *         ucontrol->value.integer.value[22] = amixer7_mute_status;
 *     }
 *
 * @endrst
 */
#define MUTE_INPUT "Mute Input"

/**
 * @brief mute value for output.
 * priority : 3
 *
 * @rst
 * Functional Requirements
 *   Function to Mute Output Resource As with the input, the mute state of each
 *   output source is checked and updated when the Get function is executed. You
 *   must be able to mute and unbind each output type during the Put operation.
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
 *     mute_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     mute_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *
 *     //
 *     // parameter
 *     //
 *	   struct snd_kcontrol{};
 *     "Mute Output"
 *
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
 *        COMMON_DAP_BT    = 0x8000

 *     value[1]: muteOnOff (on:1, off:0) (defalut: 1)
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
 *     mute_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         output_type = ucontrol->value.integer.value[0];
 *         mute_status = ucontrol->value.integer.value[1];
 *         // set mute
 *     }
 *
 *     mute_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     {
 *         // get mute status
 *         ucontrol->value.integer.value[0] = spk_mute_status;
 *         ucontrol->value.integer.value[1] = optic_mute_status;
 *         ucontrol->value.integer.value[2] = optic_lg_mute_status;
 *         ucontrol->value.integer.value[3] = bluetooth_mute_status;
 *         ucontrol->value.integer.value[4] = hp_mute_status;
 *         ucontrol->value.integer.value[5] = arc_mute_status;
 *         ucontrol->value.integer.value[6] = wisa_mute_status;
 *         ucontrol->value.integer.value[7] = se_bt_mute_status;
 *         ucontrol->value.integer.value[8] = capture_mute_status;
 *         ucontrol->value.integer.value[9] = se_arc_mute_status;
 *         ucontrol->value.integer.value[10] = se_bt_surround_mute_status;
 *         ucontrol->value.integer.value[11] = wowcast_mute_status;
 *         ucontrol->value.integer.value[12] = dap_hp_bt_mute_status;
 *         ucontrol->value.integer.value[13] = line_out_mute_status;
 *         ucontrol->value.integer.value[14] = dafc_mute_status;
 *         ucontrol->value.integer.value[15] = dap_bt_mute_status;
 *     }
 * @endrst
 */
#define MUTE_OUTPUT "Mute Output"

#endif
