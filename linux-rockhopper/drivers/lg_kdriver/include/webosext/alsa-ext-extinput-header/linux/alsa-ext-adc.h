/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_ADC_H
#define _ALSA_EXT_ADC_H

/**
 * @brief ADC device open
 *
 * priority:2
 *
 * @rst
 * Functional Requirements
 *   Open the ADC driver.
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
 *     adc_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int open_status = ucontrol->value.integer.value[0]; // Open Adc Resource
 *     }
 *     adc_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get Adc Open Status
 *         ucontrol->value.integer.value[0] = open_status;
 *     }
 *
 * @endrst
 */
#define ADC_OPEN "Adc Open"

/**
 * @brief ADC device close
 *
 * priority : 2
 *
 * @rst
 *
 * Functional Requirements
 *  Close the ADC driver.
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
 *     adc_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     adc_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
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
 *     adc_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int close_status = ucontrol->value.integer.value[0]; // Close Adc Resource
 *     }
 *     adc_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get Adc Close Status
 *         ucontrol->value.integer.value[0] = close_status;
 *     }
 *
 * @endrst
 */
#define ADC_CLOSE "Adc Close"

/**
 * @brief ADC device Connect
 *
 * priority : 2
 *
 * @rst
 * Functional Requirements
 *   Connect the ADC driver.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   if we call "Adc Close", this value should be default.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     //function
 *     //
 *     adc_connect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     adc_connect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
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
 *     adc_connect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int connect_hw_port = ucontrol->value.integer.value[0]; // Connect Adc hw port
 *     }
 *     adc_connect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get Adc Connected Port
 *         ucontrol->value.integer.value[0] = connected_hw_port;
 *     }
 *
 * @endrst
 */
#define ADC_CONNECT "Adc Connect"

/**
 * @brief ADC device disconnect
 *
 * priority : 2
 *
 * @rst
 * Functional Requirements
 *   Disconnect the ADC driver.
 *
 * Performance Requirements
 *   The response time of this function should be within 10ms,
 *   if there are no special reasons.
 *
 * Constraints
 *   if we call "Adc Close", this value should be default.
 *
 * Functions & Parameters
 *   .. code-block:: cpp
 *
 *     //
 *     // function
 *     //
 *     adc_disconnect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 *     adc_disconnect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
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
 * Example
 *   .. code-block:: cpp
 *
 *     adc_disconnect_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         int disconnect_status = ucontrol->value.integer.value[0]; // Disconnect Adc hw port
 *     }
 *     adc_disconnect_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol) {
 *         // Get Adc disconnected status
 *         ucontrol->value.integer.value[0] = disconnect_status;
 *     }
 *
 * @endrst
 */
#define ADC_DISCONNECT "Adc Disconnect"

#endif
