/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022-2025 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_SOUNDENGINE_LITE_H
#define _ALSA_EXT_SOUNDENGINE_LITE_H

/**
 * @brief set/get GEQ
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *  | It is an API to setting GEQ (graphical equalizer) by adjusting center frequency and decibel level.
 *
 * Performance Requirements
 *  | The response time of this function should be within 10ms, if here are no special reasons.
 *  | Share CPU/Memory Usage for functionality with limitation.
 *  | Share DSP profiling result for functionality with worst case
 *
 * Constraints
 *  There are no special constraints on this API function.
 * @endrst
 *
 * @code
 * sound_engine_lite_geq_param_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     //set geq state to on/off
 *     int geqstate = ucontrol->value.integer.value[0];
 *     // Set GEQ Param
 *     int num_of_band = ucontrol->value.integer.value[1];
 *     int band1_freq = ucontrol->value.integer.value[2];
 *     int band1_decibel = ucontrol->value.integer.value[3];
 *     int band2_freq = ucontrol->value.integer.value[4];
 *     int band2_decibel = ucontrol->value.integer.value[5];
 *     int band3_freq = ucontrol->value.integer.value[6];
 *     int band3_decibel = ucontrol->value.integer.value[7];
 *     int band4_freq = ucontrol->value.integer.value[8];
 *     int band4_decibel = ucontrol->value.integer.value[9];
 *     int band5_freq = ucontrol->value.integer.value[10];
 *     int band5_decibel = ucontrol->value.integer.value[11];
 *     int band6_freq = ucontrol->value.integer.value[12];
 *     int band6_decibel = ucontrol->value.integer.value[13];
 *     int band7_freq = ucontrol->value.integer.value[14];
 *     int band7_decibel = ucontrol->value.integer.value[15];
 *     int band8_freq = ucontrol->value.integer.value[16];
 *     int band8_decibel = ucontrol->value.integer.value[17];
 *     int band9_freq = ucontrol->value.integer.value[18];
 *     int band9_decibel = ucontrol->value.integer.value[19];
 *     int band10_freq = ucontrol->value.integer.value[20];
 *     int band10_decibel = ucontrol->value.integer.value[21];
 * }
 *
 * sound_engine_lite_geq_param_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get geq state
 *     ucontrol->value.integer.value[0] = geqstate;
 *     // Get GEQ Param
 *     ucontrol->value.integer.value[1] = num_of_band;
 *     ucontrol->value.integer.value[2] = band1_freq;
 *     ucontrol->value.integer.value[3] = band1_decibel;
 *     ucontrol->value.integer.value[4] = band2_freq
 *     ucontrol->value.integer.value[5] = band2_decibel;
 *     ucontrol->value.integer.value[6] = band3_freq;
 *     ucontrol->value.integer.value[7] = band3_decibel;
 *     ucontrol->value.integer.value[8] = band4_freq;
 *     ucontrol->value.integer.value[9] = band4_decibel;
 *     ucontrol->value.integer.value[10] = band5_freq;
 *     ucontrol->value.integer.value[11] = band5_decibel;
 *     ucontrol->value.integer.value[12] = band6_freq;
 *     ucontrol->value.integer.value[13] = band6_decibel;
 *     ucontrol->value.integer.value[14] = band7_freq;
 *     ucontrol->value.integer.value[15] = band7_decibel;
 *     ucontrol->value.integer.value[16] = band8_freq;
 *     ucontrol->value.integer.value[17] = band8_decibel;
 *     ucontrol->value.integer.value[18] = band9_freq;
 *     ucontrol->value.integer.value[19] = band9_decibel;
 *     ucontrol->value.integer.value[20] = band10_freq;
 *     ucontrol->value.integer.value[21] = band10_decibel;
 * }
 * @endcode
 *
 * @param[in] geqstate    int
 * @param[in] num_of_band int
 * @param[in] freq        int
 * @param[in] decibel     int
 *
 * @param[out] geqstate    int  (0 or 1. 1 is geq on)           number of bands
 * @param[out] num_of_band int  (5 ~ 10. default: 5)            number of bands
 * @param[out] freq        int  (20Hz ~ 20,000Hz. default: 0)   center frequency
 * @param[out] decibel     int  (-10dB ~ +10dB. default: 0)     decibel level
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define SOUND_ENGINE_LITE_GEQ_PARAM "Sound Engine Lite GEQ Param"

/**
 * @brief set/get Volume
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *  | It is an API to setting Volume
 *  | The input parameter is a linear scale converted from decibel (dB) volume for gain adjustment.
 *  | The gain value is converted in the same way as the "Gain Input" API.
 *
 * Performance Requirements
 *  | The response time of this function should be within 10ms, if here are no special reasons.
 *  | Share CPU/Memory Usage for functionality with limitation.
 *  | Share DSP profiling result for functionality with worst case
 *
 * Constraints
 *  There are no special constraints on this API function.
 * @endrst
 *
 * @code
 * sound_engine_lite_volume_param_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     uint32_t volume = ucontrol->value.integer.value[0];
 *     // Set Volume Param
 * }
 * sound_engine_lite_volume_param_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Get volume Param
 *     ucontrol->value.integer.value[0] = volume;
 * }
 * @endcode
 *
 * @param[in] volume integer        Volume parameter is a linear scale which is converted from decibel volume for gain adjustment
 * @param[out] volume integer
 *
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define SOUND_ENGINE_LITE_VOLUME_PARAM "Sound Engine Lite Volume Param"

/**
 * @brief set/get Auto Volume
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *  | It is an API to setting auto volume.
 *  | Input signal gain should be adjust close to the agc_target gain from (input signal gain + gain_limit_min) to (input signal gain + gain_limit_max)
 *  | For example, agc_target gain is -26dB, gain_limit_max is 5dB and gain_limit_min is -12dB.
 *  | If input signal gain is -39dB, then you can adjust this gain from -51dB(-39 + -12) to -34dB(-39 + 5).
 *  | So input signal gain should be adjust to -34dB.
 *  | If input signal gain is -22dB, then you can adjust this gain from -34dB(-22 + -12) to -17dB(-22 + 5).
 *  | So input signal gain should be adjust to -26dB.
 *
 * Performance Requirements
 *  | The response time of this function should be within 10ms, if here are no special reasons.
 *  | Share CPU/Memory Usage for functionality with limitation.
 *  | Share DSP profiling result for functionality with worst case
 *
 * Constraints
 *  There are no special constraints on this API function.
 * @endrst
 *
 *
 * @code
 * sound_engine_lite_auto_volume_param_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Set Auto Volume Parameter setting
 *     bool avl_enable = ucontrol->value.boolean.value[0];
 *     int agc_target = ucontrol->value.integer.value[1];
 *     int gain_limit_min = ucontrol->value.integer.value[2];
 *     int gain_limit_max == ucontrol->value.integer.value[3];
 *     int reserve0 = ucontrol->value.integer.value[4];
 *     int reserve1 = ucontrol->value.integer.value[5];
 * }
 *
 * sound_engine_lite_auto_volume_param_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // Get Auto volume Params
 *     ucontrol->value.boolean.value[0] = avl_enable;
 *     ucontrol->value.integer.value[1] = agc_target;
 *     ucontrol->value.integer.value[2] = gain_limit_min;
 *     ucontrol->value.integer.value[3] = gain_limit_max;
 *     ucontrol->value.integer.value[4] = reserve0;
 *     ucontrol->value.integer.value[5] = reserve1;
 * }
 * @endcode
 *
 * @param[in] avl_enable       bool
 * @param[in] agc_target       int    // Target volume (dB)     default : -26
 * @param[in] gain_limit_min   int    // default : -12
 * @param[in] gain_limit_max   int    // default : 5
 * @param[in] reserve0         int
 * @param[in] reserve1         int
 *
 * @param[out] avl_enable      bool   // (true/false. default: false)    Enable the auto volume.
 * @param[out] agc_target      int    // Target volume (dB)
 * @param[out] gain_limit_min  int    // dB
 * @param[out] gain_limit_max  int    // dB
 * @param[out] reserve0        int    // (default: 0)
 * @param[out] reserve1        int    // (default: 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define SOUND_ENGINE_LITE_AUTO_VOLUME_PARAM "Sound Engine Lite Auto Volume Param"

#endif // _ALSA_EXT_SOUNDENGINE_LITE_H
