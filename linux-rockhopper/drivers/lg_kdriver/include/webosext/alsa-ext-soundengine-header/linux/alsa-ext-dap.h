/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_DAP_H
#define _ALSA_EXT_DAP_H

/**
 * @brief lgse_postproc_mode_ext_type
 * values for DAP & LGSE Mode
 */

typedef enum lgse_postproc_mode_ext_type {
    LGSE_POSTPROC_LGSE_MODE =
        0, /**< LGSE is used for the post process regardless of audio type */
    LGSE_POSTPROC_DAP_LGSE_MODE =
        1, /**< DAP or LGSE can be used, it depends on audio type. LG MW can define the audio type which should be processed with DAP */
    LGSE_POSTPROC_DAP_MODE =
        2 /**< DAP is used for the post process regardless of audio type */
} lgse_postproc_mode_ext_type_t;

/**
 * @brief Put/Get Audio Post Processing mode.
 * @li priority : 4
 *
 * Select & get Audio Post Processing mode
 * Default value is that  lgse_postproc_mode_ext_type_t is disable.
 *
 * @code
 * lgse_dap_PostProcess_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int ePostProcMode = ucontrol->value.integer.value[0];
 *     // set gain param
 * }
 *
 * lgse_dap_PostProcess_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = ePostProcMode;
 * }
 * @endcode
 *
 * @param[in] int(lgse_postproc_mode_ext_type_t) ePostProcMode,
 * @param[out] int(lgse_postproc_mode_ext_type_t) ePostProcMode, (default: 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_POSTPROCESS "LGSE PostProcess"

/**
 * @brief lgse_dap_surround_virutalizer_mode
 */
typedef enum lgse_dap_surround_virtualizer_mode {
    LGSE_DAP_SURROUND_VIRTUALIZER_OFF =
        0, /**< Virtualizer off(defalut) : process
 mode-DAP_CPDP_PROCESS_2 and mix_matrix-NULL */
    LGSE_DAP_SURROUND_VIRTUALIZER_ON =
        1, /**< Virtualizer on: When input content is
 stereo, process mode-DAP_CPDP_PROCESS_5_1_SPEAKER and
 mix_matrix-speaker_5_1_2_to_2_0_mix_matrix. \n When input content is 5.1
 or 5.1.2(ATMOS), process mode-DAP_CPDP_PROCESS_5_1_2_SPEAKER and
 mix_matrix-speaker_5_1_2_to_2_0_mix_matrix */
    LGSE_DAP_SURROUND_VIRTUALIZER_AUTO =
        2, /**< Virtualizer Auto: When input content is
 5.1.2(ATMOS),  process mode-DAP_CPDP_PROCESS_5_1_2_SPEAKER and
 mix_matrix-speaker_5_1_2_to_2_0_mix_matrix. \n When input content is
 Non ATMOS, process mode-DAP_CPDP_PROCESS_2 and mix_matrix-NULL */
    LGSE_DAP_SURROUND_VIRTUALIZER_ON_2_0_2 =
        3, /**< Virtualizer on 2.0.2 : When input
 content is stereo, process mode-DAP_CPDP_PROCESS_5_1_SPEAKER and
 mix_matrix-speaker_5_1_2_to_2_0_2_mix_matrix \n When input
 content is 5.1 or 5.1.2(ATMOS), process mode-DAP_CPDP_PROCESS_5_1_2_SPEAKER and
 mix_matrix-speaker_5_1_2_to_2_0_2_mix_matrix */
} lgse_dap_surround_virtualizer_mode_t;

/**
 * @brief Put/Get Audio Post Processing mode.
 * @li priority : 4
 *
 * Set DAP surround virtualizer mode
 *
 * @code
 * lgse_dap_SurroundVirtualizerMode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int pstSurroundVirtualizerMode = ucontrol->value.integer.value[0];
 *     // set gain param
 * }
 *
 * lgse_dap_SurroundVirtualizerMode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = pstSurroundVirtualizerMode;
 * }
 * @endcode
 *
 * @param[in] pstSurroundVirtualizerMode lgse_dap_surround_virtualizer_mode_t
 * @param[out] pstSurroundVirtualizerMode lgse_dap_surround_virtualizer_mode_t
 * (default: 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_SURROUNDVIRTUALIZERMODE "LGSE DAP SurroundVirtualizerMode"

/**
 * @brief parameter for "LGSE DAP DialogueEnhancer"
 * @see LGSE_DAP_DIALOGUEENHANCER
 */
struct DialogEnhancerParam {
    int bIsDialogueEnhancerEnable; /**< Enables or disables the Dialogue
 * Enhancer feature 0(disabled), !0(enabled) */
    int dialogueEnhancerAmount;    /**< Determines the strength of the
 * Dialogue Enhancer effect for inputs other than Dolby AC-4 0 to 16 */
    int ducking;                   /**<  When dialog is detected, Dialog Enhancer also
 * supports attenuating channels which are not the source of the dialog 0 to 16 */
};

/**
 * @brief Put/Get DAP dialogue enhancer
 * @li priority : 4
 *
 * Set DAP dialogue enhancer
 *
 * @code
 * lgse_dap_DialogueEnhancer_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsDialogueEnhancerEnable = ucontrol->value.integer.value[0];
 *     int dialogueEnhancerAmount = ucontrol->value.integer.value[1];
 *     int ducking = ucontrol->value.integer.value[2];
 *     // set gain param
 * }
 *
 * lgse_dap_DialogueEnhancer_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bIsDialogueEnhancerEnable ;
 *     ucontrol->value.integer.value[1] = dialogueEnhancerAmount ;
 *     ucontrol->value.integer.value[2] = ducking ;
 * }
 * @endcode
 *
 * @param[in] DialogEnhancerParam struct
 * @param[out] DialogEnhancerParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_DIALOGUEENHANCER "LGSE DAP DialogueEnhancer"

/**
 * @brief parameter for "LGSE DAP VolumeLeveler"
 * @see LGSE_DAP_VOLUMELEVELER
 */
struct VolumeLevelerParam {
    int bIsVolumeLevelerEnable; /**< Enables or disables the Volume Leveler
 * 0(off), 1(on) */
    int volumeLevelerAmount; /**< Specifies how aggressive the leveler is
 * in attempting to reach the output target level 0 to 10 */
    int inputTargetLevel;    /**< Specifies the average loudness level of the
 * incoming audio specified according to a K loudness weighting -640 to 0 */
    int outputTargetLevel;   /**<  Specifies the average loudness level which
 * the audio should be moved to. -640 to 0 */
};

/**
 * @brief Put/Get DAP volume leveler
 * @li priority : 4
 * Set DAP volume leveler
 *
 * @code
 * lgse_dap_VolumeLeveler_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsVolumeLevelerEnable = ucontrol->value.integer.value[0];
 *     int volumeLevelerAmount = ucontrol->value.integer.value[1];
 *     int inputTargetLevel = ucontrol->value.integer.value[2];
 *     int outputTargetLevel = ucontrol->value.integer.value[3];
 *     // set gain param
 * }
 *
 * lgse_dap_VolumeLeveler_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bIsVolumeLevelerEnable  ;
 *     ucontrol->value.integer.value[1] = volumeLevelerAmount ;
 *     ucontrol->value.integer.value[2] = inputTargetLevel ;
 *     ucontrol->value.integer.value[3] = outputTargetLevel ;
 * }
 * @endcode
 *
 * @param[in] VolumeLevelerParam struct
 * @param[out] VolumeLevelerParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_VOLUMELEVELER "LGSE DAP VolumeLeveler"

/**
 * @brief parameter for "LGSE DAP VolumeModeler"
 * @see LGSE_DAP_VOLUMEMODELER
 */
struct VolumeModelerParam {
    int bEnable; /**< Enables or disables the Volume Modeler 0(off), 1(on) */
    int calibration; /**< Used to fine-tune the manufacturer calibrated
 * reference level to the listening environment -320 to 320 */
};

/**
 * @brief Put/Get DAP volume Modeler
 * @li priority : 4
 * Set DAP volume modeler
 *
 * @code
 * lgse_dap_VolumeModeler_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bEnable = ucontrol->value.integer.value[0];
 *     int calibration= ucontrol->value.integer.value[1];
 *     // set gain param
 * }
 *
 * lgse_dap_VolumeModeler_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bEnable ;
 *     ucontrol->value.integer.value[1] = calibration;
 * }
 * @endcode
 *
 * @param[in] VolumeModelerParam struct
 * @param[out] VolumeModelerParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_VOLUMEMODELER "LGSE DAP VolumeModeler"

/**
 * @brief Put/Get DAP volume maximizer
 * @li priority : 4
 *
 * Set DAP volume maximizer
 *
 * @code
 * lgse_dap_volume_maximizer_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int boost = ucontrol->value.integer.value[0];
 *     // set gain param
 * }
 *
 * lgse_dap_volume_maximizer_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = boost ;
 * }
 * @endcode
 *
 * @param[in] boost int Controls the amount of gain applied by the Volume
 * Maximizer while the Volume Leveler is enabled. 0 to 192
 * @param[out] boost int Controls the amount of gain applied by the Volume
 * Maximizer while the Volume Leveler is enabled. 0 to 192 (default: 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_VOLUMEMAXIMIZER "LGSE DAP VolumeMaximizer"

/**
 * @brief parameter for "LGSE DAP Optimizer"
 * @see LGSE_DAP_OPTIMIZER
 */
struct OptimizerParam {
    int bIsEnable; /**< enable or disable */
    int bandCount; /**< Band count: 1-20 */
    int freqs[20]; /**< frequencies to be set gain in DAP functions:
 * 20-20,000 Hz */
    int gains[8][20]; /** gains matched with freqs and set in DAP functions
 *                          number of channels is LGSE_DAP_MAX_CHANNEL_COUNT,
 *                          it means that even if optimizer function only one
 *                          channel, gains of other channels should be set (as 0)*/
};

/**
 * @brief Put/Get DAP Optimizer
 * @li priority : 4
 *
 * Set DAP Optimizer This function should be set more 128 parameters. It means
 * the kcontrol can't handle the whole parameters on 0 index. So it should be
 * use 0 and 1 index for support whole parameters.
 *
 * @code
 * lgse_dap_Optimizer_put0(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsEnable = ucontrol->value.integer.value[0];
 *     int badCount = ucontrol->value.integer.value[1];
 *     int freqs00 = ucontrol->value.integer.value[2];
 *     ...
 *     int freqs19 = ucontrol->value.integer.value[21];
 *     int gains0000 = ucontrol->value.integer.value[22];
 *     ...
 *     int gains0019 = ucontrol->value.integer.value[42];
 *     ...
 *     int gains0119 = ucontrol->value.integer.value[62];
 *     ...
 *     int gains0219 = ucontrol->value.integer.value[82];
 *     ...
 *     int gains0319 = ucontrol->value.integer.value[102];
 *     ...
 *     int gains0419 = ucontrol->value.integer.value[122];
 *     ...
 *     int gains0500 = ucontrol->value.integer.value[123];
 *     int gains0504 = ucontrol->value.integer.value[127];
 *     // set gain param
 * }
 * lgse_dap_Optimizer_put1(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int gains0505 = ucontrol->value.integer.value[0];
 *     ...
 *     int gains0519 = ucontrol->value.integer.value[14];
 *     ...
 *     int gains0619 = ucontrol->value.integer.value[34];
 *     ...
 *     int gains0719 = ucontrol->value.integer.value[54];
 *     // set gain param
 * }
 * @endcode
 *
 * @param[in] OptimizerParam struct
 * @param[out] OptimizerParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_OPTIMIZER "LGSE DAP Optimizer"

/**
 * @deprecated
 *  Deprecated since webOS22, it will be removed from webOS 24
 *  And it is controlled by BSP
 * @brief parameter for "LGSE DAP ProcessOptimizer"
 * @see LGSE_DAP_PROCESSOPTIMIZER
 */
struct ProcessOptimizerParam {
    int bIsEnableProcess; /**< Enables or disables the Audio Optimizer 0
 * (disabled), !0 (enabled)*/
    int bandCount; /**< Band count: 1-20 */
    int freq[20]; /**< frequencies to be set gain in DAP functions:
 * 20-20,000 Hz */
    int gains[8][20]; /**< gains matched with freqs and set in DAP functions
 *                         number of channels is LGSE_DAP_MAX_CHANNEL_COUNT,
 *                         it means that even if optimizer function only one
 *                         channel, gains of other channels should be set (as 0) */
};

/**
 * @brief Put/Get DAP process Optimizer
 * @li priority : 4
 *
 * Set DAP process Optimizer This function should be set more 128 parameters. It
 * means the kcontrol can't handle the whole parameters on 0 index. So it should
 * be use 0 and 1 index for support whole parameters.
 *
 * @code
 * lgse_dap_process_optimizer_put0(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsEnableProcess = ucontrol->value.integer.value[0];
 *     int badCount = ucontrol->value.integer.value[1];
 *     int freqs00 = ucontrol->value.integer.value[2];
 *     ...
 *     int freqs19 = ucontrol->value.integer.value[21];
 *     int gains0000 = ucontrol->value.integer.value[22];
 *     ...
 *     int gains0019 = ucontrol->value.integer.value[42];
 *
 *     ...
 *
 *     int gains0119 = ucontrol->value.integer.value[62];
 *     ...
 *
 *     int gains0219 = ucontrol->value.integer.value[82];
 *
 *     ...
 *
 *     int gains0319 = ucontrol->value.integer.value[102];
 *
 *     ...
 *
 *     int gains0419 = ucontrol->value.integer.value[122];
 *     ...
 *
 *     int gains0500 = ucontrol->value.integer.value[123];
 *     int gains0504 = ucontrol->value.integer.value[127];
 * }
 * lgse_dap_process_optimizer_put1(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int gains0505 = ucontrol->value.integer.value[0];
 *     ...
 *     int gains0519 = ucontrol->value.integer.value[14];
 *     ...
 *     int gains0619 = ucontrol->value.integer.value[34];
 *     ...
 *     int gains0719 = ucontrol->value.integer.value[54];
 *     // set gain param
 * }
 * lgse_dap_process_optimizer_get0(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bIsEnable ;
 *     ucontrol->value.integer.value[1] = badCount ;
 *     ucontrol->value.integer.value[2] = freqs00 ;
 *     ...
 *     ucontrol->value.integer.value[21] = freqs19 ;
 *     ucontrol->value.integer.value[22] = gains0000 ;
 *     ...
 *     ucontrol->value.integer.value[42] = gains0019 ;
 *     ...
 *     ucontrol->value.integer.value[62] = gains0119 ;
 *     ...
 *     ucontrol->value.integer.value[82] = gains0219 ;
 *     ...
 *     ucontrol->value.integer.value[102] = gains0319 ;
 *     ...
 *     ucontrol->value.integer.value[122] = gains0419 ;
 *     ...
 *     ucontrol->value.integer.value[123] = gains0500 ;
 *     ...
 *     ucontrol->value.integer.value[127] = gains0504 ;
 * }
 *
 *
 * lgse_dap_process_optimizer_get1(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = gains0505 ;
 *     ...
 *     ucontrol->value.integer.value[14] = gains0519  ;
 *     ...
 *     ucontrol->value.integer.value[34] = gains0619 ;
 *     ...
 *     ucontrol->value.integer.value[54] = gains0719;
 * }
 * @endcode
 *
 * @param[in] ProcessOptimizerParam struct
 * @param[out] ProcessOptimizerParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_PROCESSOPTIMIZER "LGSE DAP ProcessOptimizer"

/**
 * @brief Put/Get DAP surround decoder
 * @li priority : 4
 *
 * @code
 * lgse_dap_surround_decode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bEnable= ucontrol->value.integer.value[0];
 *     // set gain param
 * }
 *
 * lgse_dap_surround_decode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bEnable;
 * }
 * @endcode
 *
 * @param[in] bEnable int Enables or disables the Surround Decoder 0(off),
 * 1(on)
 * @param[out] bEnable int Enables or disables the Surround Decoder 0(off),
 * 1(on) (default: 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_SURROUNDDECODER "LGSE DAP SurroundDecoder"

/**
 * @brief Put/Get DAP surround compressor
 * @li priority : 4
 *
 * @code
 * lgse_dap_surround_compressor_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int boost= ucontrol->value.integer.value[0];
 *     // set gain param
 * }
 *
 * lgse_dap_surround_compressor_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = boost;
 * }
 * @endcode
 *
 * @param[in] boost int The maximum amount of gain which can be applied to a
 * surround channel by the Surround Compressor feature 0 to 96
 * @param[out] boost int The maximum amount of gain which can be applied to a
 * surround channel by the Surround Compressor feature 0 to 96 (default: 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_SURROUNDCOMPRESSOR "LGSE DAP SurroundCompressor"

/**
 * @brief parameter of "LGSE DAP VirtualizerSpeakerAngle"
 * @see LGSE_DAP_VIRTUALIZERSPEAKERANGLE
 */
struct VirtualizerSpeakerAngleParam {
    int frontSpeakerAngle; /**< Virtualization parameters for the left and
 * right channels 1 to 30 */
    int surroundSpeakerAngle; /**< Virtualization parameters for the left
 * and right surround channels 1 to 30 */
    int heightSpeakerAngle;   /**< Virtualization parameters for the left and
 * right height channels 1 to 30 */
};

/**
 * @brief Put/Get DAP virtualizer speaker angle
 * @li priority : 4
 *
 * @code
 * lgse_dap_virtualizer_speaker_angle_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int frontSpeakerAngle= ucontrol->value.integer.value[0];
 *     int surroundSpeakerAngle= ucontrol->value.integer.value[1];
 *     int heightSpeakerAngle= ucontrol->value.integer.value[2];
 *     // set stVirtualizerSpeakerAngle param
 * }
 *
 * lgse_dap_virtualizer_speaker_angle_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get stVirtualizerSpeakerAngle param
 *     ucontrol->value.integer.value[0] = frontSpeakerAngle;
 *     ucontrol->value.integer.value[1] = surroundSpeakerAngle;
 *     ucontrol->value.integer.value[2] = heightSpeakerAngle;
 * }
 * @endcode
 *
 * @param[in] VirtualizerSpeakerAngleParam struct
 * @param[out] VirtualizerSpeakerAngleParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_VIRTUALIZERSPEAKERANGLE "LGSE DAP VirtualizerSpeakerAngle"

/**
 * @brief parameter for "LGSE DAP IntelligenceEQ"
 * @see LGSE_DAP_INTELLIGENCEEQ
 */
struct IntelligenceEQParam {
    int bIsEnable; /**< Enables or disables the Intelligence EQ settings 0(disabled), !0(enabled) */
    int bandCount; /**< Band count: 1-20 */
    int freqs
        [20]; /**< frequencies to be set gain in DAP functions: 20-20,000 Hz */
    int gains[20]; /**< gains matched with freqs and set in DAP functions */
    int strength;  /**< strength */
};

/**
 * @brief Put/Get intelligence EQ
 * @li priority : 4
 *
 * @code
 * lgse_dap_intelligence_eq_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsEnable = ucontrol->value.integer.value[0];
 *     int bandCount = ucontrol->value.integer.value[1];
 *     int freqs00 = ucontrol->value.integer.value[2];
 *     ...
 *     int freqs19 = ucontrol->value.integer.value[21];
 *     int gains00 = ucontrol->value.integer.value[22];
 *     ...
 *     int gains19 = ucontrol->value.integer.value[41];
 *     int strength = ucontrol->value.integer.value[42];
 *     // set gain param
 * }
 *
 * lgse_dap_intelligence_eq_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bIsEnable ;
 *     ucontrol->value.integer.value[1] = bandCount;
 *     ucontrol->value.integer.value[2] = freqs00 ;
 *     ...
 *     ucontrol->value.integer.value[21] = freqs19;
 *     ucontrol->value.integer.value[22] = gains00 ;
 *     ...
 *     ucontrol->value.integer.value[41] = gains19 ;
 *     ucontrol->value.integer.value[42] = strength ;
 * }
 * @endcode
 *
 * @param[in] IntelligenceEQParam struct
 * @param[out] IntelligenceEQParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_INTELLIGENCEEQ "LGSE DAP IntelligenceEQ"

/**
 * @brief parameter for "LGSE DAP MediaIntelligence"
 * @see LGSE_DAP_MEIDAINTELLIGENCE
 */
struct MediaIntelligenceParam {
    int bIsEnable;                   /**< Enables or disables the Media Intelligence settings
 0(disabled), !0(enabled) */
    int bIsEqualizerEnable;          /**< If this parameter is enabled, Intelligent
 Equalizer uses information from Media Intelligence to improve the quality of
 the processing. 0(disabled), !0 (enabled) */
    int bIsVolumeLevelerEnable;      /**< If this parameter is enabled, Volume
 Leveler uses information from Media Intelligence to improve the quality of the
 processing. 0(disabled), !0 (enabled) */
    int bIsDialogueEnhancerEnable;   /**< If this parameter is enabled,
 Dialogue Enhancer uses information from Media Intelligence to improve the
 quality of the processing. 0(disabled), !0(enabled) */
    int bIsSurroundCompressorEnable; /**< The Surround Compressor is used
 only when the headphone or speaker virtualizer is enabled. If this parameter is
 enabled, Surround Compressor will use information from Media Intelligence to
 improve the quality of the processing. 0(disabled), !0(enabled) */
};

/**
 * @brief Put/Get media intelligence
 * @li priority : 4
 *
 * @code
 * lgse_dap_mediaIntelligence_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsEnable = ucontrol->value.integer.value[0];
 *     int bIsEqualizerEnable = ucontrol->value.integer.value[1];
 *     int bIsVolumeLevelerEnable = ucontrol->value.integer.value[2];
 *     int bIsDialogueEnhancerEnable = ucontrol->value.integer.value[3];
 *     int bIsSurroundCompressorEnable = ucontrol->value.integer.value[4];
 *     // set gain param
 * }
 *
 * lgse_dap_mediaIntelligence_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = stMediaIntelligence ;
 *     ucontrol->value.integer.value[1] = bIsEqualizerEnable ;
 *     ucontrol->value.integer.value[2] = bIsVolumeLevelerEnable ;
 *     ucontrol->value.integer.value[3] = bIsDialogueEnhancerEnable ;
 *     ucontrol->value.integer.value[4] = bIsSurroundCompressorEnable ;
 * }
 * @endcode
 *
 * @param[in] MediaIntelligenceParam struct
 * @param[out] MediaIntelligenceParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_MEIDAINTELLIGENCE "LGSE DAP MediaIntelligence"

/**
 * @brief parameter of "LGSE DAP GraphicalEQ"
 * @see LGSE_DAP_GRAPHICALEQ
 */
struct GraphicalEQParam {
    int bIsEnable; /**< Enables or disables the Graphical Equalizer 0
 * (disabled), !0 (enabled) */
    int bandCount; /**< Band count: 1-20 */
    int freq[20]; /**< frequencies to be set gain in DAP functions:
 * 20-20,000 Hz */
    int gains[20]; /**< gains matched with freqs and set in DAP functions */
};

/**
 * @brief Put/Get graphical EQ
 * @li priority : 4
 *
 * @code
 * lgse_dap_graphical_eq_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsEnable = ucontrol->value.integer.value[0];
 *     int bandCount = ucontrol->value.integer.value[1];
 *     int freqs00 = ucontrol->value.integer.value[2];
 *     ...
 *     int freqs19 = ucontrol->value.integer.value[21];
 *
 *     int gains00 = ucontrol->value.integer.value[22];
 *     ...
 *     int gains19 = ucontrol->value.integer.value[41];
 *     // set gain param
 * }
 *
 * lgse_dap_graphical_eq_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = strength ;
 *     ucontrol->value.integer.value[1] = bandCount;
 *     ucontrol->value.integer.value[2] = freqs00 ;
 *     ...
 *     ucontrol->value.integer.value[21] = freqs19;
 *     ucontrol->value.integer.value[22] = gains00 ;
 *     ...
 *     ucontrol->value.integer.value[41] = gains19 ;
 * }
 * @endcode
 *
 * @param[in] GraphicalEQParam struct
 * @param[out] GraphicalEQParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_GRAPHICALEQ "LGSE DAP GraphicalEQ"

/**
 * @brief lgse_dap_perceptual_height_filter_mode_ext_type
 */
typedef enum lgse_dap_perceptual_height_filter_mode_ext_type {
    LGSE_DAP_HEIGHT_FILTER_DISABLED = 0, /**< Height filter is disabled */
    LGSE_DAP_HEIGHT_FILTER_FIRING =
        1, /**< Height filter configured for front firing speakers */
    LGSE_DAP_HEIGHT_FILTER_UP_FIRING =
        2, /**< Height filter configured for up firing speakers */
} lgse_dap_perceptual_height_filter_mode_ext_type_t;

/**
 * @brief Put/Get perceptual height filter
 * @li priority : 4
 *
 * @code
 * lgse_dap_perceptual_height_filter_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int stPerceptualHeightFilter = ucontrol->value.integer.value[0];
 *     // set gain param
 * }
 *
 * lgse_dap_perceptual_height_filter_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = stPerceptualHeightFilter;
 * }
 * @endcode
 *
 * @param[in] int(lgse_dap_perceptual_height_filter_ext_type_t)
 * stPerceptualHeightFilter,
 * @param[out] int(lgse_dap_perceptual_height_filter_ext_type_t)
 * stPerceptualHeightFilter, (default: 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_PERCEPTUALHEIGHTFILTER "LGSE DAP PerceptualHeightFilter"

/**
 * @brief parameter of "LGSE DAP BassEnhancer"
 * @see LGSE_DAP_BASSENHANCER
 */
struct BassEnhancerParam {
    int bIsEnable; /**< Enables or disables the Bass Enhancer 0(disabled),
 * !0(enabled) */
    int boost; /**< Sets the amount of bass boost applied by the Bass
 * Enhancer   0-24 dB */
    int cutoffFreq; /**<  Sets the cutoff frequency used by the Bass
 * Enhancer 20-2,000 Hz*/
    int width; /**< Sets the width of the bass enhancement boost curve used
 * by the Bass Enhancer, in units of octaves below the cutoff frequency 0.125-4
 * octaves */
};

/**
 * @brief Put/Get BassEnhancer
 * @li priority : 4
 *
 * @code
 * lgse_dap_bassenhancer_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsEnable= ucontrol->value.integer.value[0];
 *     int boost= ucontrol->value.integer.value[1];
 *     int cutoffFreq= ucontrol->value.integer.value[2];
 *     int width= ucontrol->value.integer.value[3];
 *     // set gain param
 * }
 *
 * lgse_dap_bassenhancer_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bIsEnable;
 *     ucontrol->value.integer.value[1] = boost;
 *     ucontrol->value.integer.value[2] = cutoffFreq;
 *     ucontrol->value.integer.value[3] = width;
 * }
 * @endcode
 *
 * @param[in] BassEnhancerParam struct
 * @param[out] BassEnhancerParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_BASSENHANCER "LGSE DAP BassEnhancer"

/**
 * @brief parameter for "LGSE DAP BassExtraction"
 * @see LGSE_DAP_BASSEXTRACTION
 */
struct BassExtractionParam {
    int bIsEnable; /**< Enables or disables the Bass Extraction
 * 0(disabled), !0(enabled) */
    int cutoffFreq; /**< Specifies the filter cutoff frequency used for
 * Bass Extraction 45(u)-200(u) Hz */
};

/**
 * @brief Put/Get BassExtraction
 * @li priority : 4
 *
 * @code
 * lgse_dap_bassextraction_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsEnable= ucontrol->value.integer.value[0];
 *     int cutoffFreq= ucontrol->value.integer.value[1];
 *     // set gain param
 * }
 *
 * lgse_dap_bassenhancer_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = bIsEnable;
 *     ucontrol->value.integer.value[1] = cutoffFreq;
 * }
 * @endcode
 *
 * @param[in] BassExtractionParam struct
 * @param[out] BassExtractionParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_BASSEXTRACTION "LGSE DAP BassExtraction"

/**
 * @brief lgse_dap_virtual_bass_mode_ext_type_t
 */
typedef enum lgse_dap_virtual_bass_mode_ext_type {
    LGSE_DAP_VIRTUAL_BASS_MODE_DELAYONLY = 0, /**< Delay only */
    LGSE_DAP_SYS_PARAM_VIRTUAL_BASS_MODE_2ND_ORDER =
        1, /**< Second-order harmonics */
    LGSE_DAP_SYS_PARAM_VIRTUAL_BASS_MODE_3RD_ORDER =
        2, /**< Second- and third-order harmonics */
    LGSE_DAP_SYS_PARAM_VIRTUAL_BASS_MODE_4TH_ORDER =
        3, /**< Second-, third-, and fourth-order  harmonics */
} lgse_dap_virtual_bass_mode_ext_type_t;

/**
 * @brief patameter for "LGSE DAP VirtualBass"
 * @see LGSE_DAP_VIRTUALBASS
 */
struct VirtualBassParam {
    lgse_dap_virtual_bass_mode_ext_type_t enMode; /**< Determines the
 * harmonics for Virtual Bass processing
 *             0 : Delay only
 *             1 : Second-order harmonics
 *             2 : Second- and third-order harmonics
 *             3 : second-, third-, and fourth-order  harmonics */
    int lowSrcFreqRange;                          /**< Defines the lowest frequency of the source to
 * be transposed 30-90 Hz (default 35 Hz) */
    int highSrcFreqRange;                         /**< Defines the highest frequency of the source
 * to be transposed 90-270 Hz (default 160 Hz) */
    int overallGain;                              /**< Defines the overall gain applied to the output of
 * the Virtual Bass transposer -480 to 0 (-30 to 0 dB) (default 0) */
    int slopeGain;                                /**< used to adjust the envelope of the transposer
 * output -3 to 0 (-3 to 0 dB) (default 0) */
    int num;                                      /**< default: 3 */
    int subgain[20];                              /**< -480 to 0 */
    int lowMixedFreqBoundaries;                   /**< Defines the lower boundary of the
 * frequency range in which transposed harmonics are mixed 0-375 Hz */
    int highMixedFreqBoundaries;                  /**< Defines the upper boundary of the
 * frequency range in which transposed harmonics are mixed 281-938 Hz */
};

/**
 * @brief Put/Get VirtualBass
 * @li priority : 4
 *
 * @code
 * lgse_dap_virtual_bass_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int enMode = ucontrol->value.integer.value[0];
 *     int lowSrcFreqRange = ucontrol->value.integer.value[1];
 *     int highSrcFreqRange= ucontrol->value.integer.value[2];
 *     int overallGain = ucontrol->value.integer.value[3];
 *     int slopeGain= ucontrol->value.integer.value[4];
 *     int num= ucontrol->value.integer.value[5];
 *     int subgains00= ucontrol->value.integer.value[6];
 *     ...
 *     int subgains19= ucontrol->value.integer.value[25];
 *     int lowMixedFreqBoundaries= ucontrol->value.integer.value[26];
 *     int highMixedFreqBoundaries= ucontrol->value.integer.value[27];
 *     // set gain param
 * }
 *
 * lgse_dap_virtual_bass_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get gain param
 *     ucontrol->value.integer.value[0] = enMode ;
 *     ucontrol->value.integer.value[1] = lowSrcFreqRange;
 *     ucontrol->value.integer.value[2] = highSrcFreqRange;
 *     ucontrol->value.integer.value[3] = overallGain ;
 *     ucontrol->value.integer.value[4] = slopeGain;
 *     ucontrol->value.integer.value[5] = num;
 *     ucontrol->value.integer.value[6] = subgains00;
 *     ...
 *     ucontrol->value.integer.value[25] = subgains19;
 *     ucontrol->value.integer.value[27] = lowMixedFreqBoundaries;
 *     ucontrol->value.integer.value[28] = highMixedFreqBoundaries;
 * }
 * @endcode
 *
 * @param[in] VirtualBassParam struct
 * @param[out] VirtualBassParam struct
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_VIRTUALBASS "LGSE DAP VirtualBass"

/**
 * @brief lgse_dap_regulator_mode_ext_type_t
 */
typedef enum lgse_dap_regulator_mode_ext_type {
    LGSE_DAP_VIRTUALBASS_MODE_PEAK_PROTECTION =
        0, /**< 0 : Peak Protection mode: The Audio Regulator has the same operating characteristics for each bank */
    LGSE_DAP_SYSPARAM_VIRTUALBASS_MODE_SPEAKER_DISTOTION =
        1, /**< !0: Speaker Distortion mode: The tuning configuration supplied by dap_cpdp_regulator_tuning_configure and dap_cpdp_regulator_overdrive_set is used to give the Audio Regulator per-band operating characteristics*/
} lgse_dap_regulator_mode_ext_type_t;

/**
 * @brief Provides the Audio Regulator with tuning coefficients. These coefficients are
 * only used when the Audio Regulator is operating in Speaker Distortion mode.
 * @see LGSE_DAP_REGULATOR
 */
struct RegulatorParam {
    int bIsEnable; /**< Enables or disables the Audio Regulator 0
 * (disabled), !0 (enabled) */
    int bands;              /**< nb_bands: 1-20 */
    int bandCenters[20];    /**< p_band_centers: 20-20,000 Hz */
    int lowThresholds[20];  /**< p_low_thresholds: -130 to 0 dB */
    int highThresholds[20]; /**< p_high_thresholds: -130 to 0 */
    int bBandIsolateFlag[20]; /**< Band isolation flag: 0(band is not
 * isolated), 1(band is isolated) */
    int overdrive;                /**< Sets the boost to be applied to all of the tuned
 * low and high thresholds (as set by dap_cpdp_regulator_tuning_configure) when
 * the Audio Regulator is operating in speaker distortion mode 0-12 dB */
    int timbrePreservationSetter; /**< Sets the timbre preservation amount
 * for the Audio Regulator, in both operating modes Values close to zero
 * maximize loudness; values close to one maximize the preservation of signal
 * tonality. 0.0-1.0 */
    int distortionRelaxationAmount; /**< Sets the Audio Regulator
 * distortion relaxation amount 0-9 dB */
    lgse_dap_regulator_mode_ext_type_t enOperatingMode; /**< Sets the
 * operating mode of the Audio Regulator:
 *  - Peak Protection mode: The Audio Regulator has the same operating characteristics
 * for each band.
 *   - Speaker Distortion mode: The tuning configuration supplied by
 *     dap_cpdp_regulator_tuning_configure and dap_cpdp_regulator_overdrive_set is used to
 *     give the Audio Regulator per-band operating characteristics.
 *       0  : Peak Protection mode
 *       !0 : Speaker Distortion mode */
};

/**
 * @brief Put/Get Regulator
 * @li priority : 4
 *
 * Provides the Audio Regulator with tuning coefficients. These coefficients are
 * only used when the Audio Regulator is operating in Speaker Distortion mode.
 *
 * @code
 * lgse_dap_regulator_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bIsEnable = ucontrol->value.integer.value[0];
 *     int bands = ucontrol->value.integer.value[1];
 *     int bandCenters00 = ucontrol->value.integer.value[2];
 *     ...
 *     int bandCenters19 = ucontrol->value.integer.value[21];
 *     int lowThresholds00 = ucontrol->value.integer.value[22];
 *     ...
 *     int lowThresholds19 = ucontrol->value.integer.value[41];
 *     int highThresholds00 = ucontrol->value.integer.value[42];
 *     ...
 *     int highThresholds19 = ucontrol->value.integer.value[61];
 *     int bBandIsolateFlag00 = ucontrol->value.integer.value[62];
 *     ...
 *     int bBandIsolateFlag19 = ucontrol->value.integer.value[81];
 *     int overdrive= ucontrol->value.integer.value[82];
 *     int timbrePreservationSetter= ucontrol->value.integer.value[83];
 *     int distortionRelaxationAmount= ucontrol->value.integer.value[94];
 *     int enOperatingMode= ucontrol->value.integer.value[85];
 *     // set stRegulator param
 * }
 *
 * lgse_dap_regulator_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get stRegulator param
 *     ucontrol->value.integer.value[0] = bIsEnable ;
 *     ucontrol->value.integer.value[1] = bands ;
 *     ucontrol->value.integer.value[2] = bandCenters00 ;
 *     ...
 *     ucontrol->value.integer.value[21] = bandCenters19 ;
 *     ucontrol->value.integer.value[22] = lowThresholds00 ;
 *     ...
 *     ucontrol->value.integer.value[41] = lowThresholds19;
 *     ucontrol->value.integer.value[42] = highThresholds00 ;
 *     ...
 *     ucontrol->value.integer.value[61] = highThresholds19 ;
 *     ucontrol->value.integer.value[62] = bBandIsolateFlag00;
 *     ...
 *     ucontrol->value.integer.value[81] = bBandIsolateFlag19;
 *     ucontrol->value.integer.value[82] = stRegulator;
 *     ucontrol->value.integer.value[83] = timbrePreservationSetter;
 *     ucontrol->value.integer.value[84] = distortionRelaxationAmount;
 *     ucontrol->value.integer.value[85] = enOperatingMode;
 * }
 * @endcode
 *
 * @param[in] enOperatingMode lgse_dap_regulator_mode_ext_type_t
 * @param[out] enOperatingMode lgse_dap_regulator_mode_ext_type_t
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DAP_REGULATOR "LGSE DAP Regulator"

/**
 * @brief path to read/write DAFC Flex Configs (sconf)
 *
 * @rst
 * | This path would be used to read/write DAFC Flex Configs
 * | If :type:`SOUNDENGINE_DAFC_FLEX_CONFIGS_STATUS` is called with :type:`soundengine_dafc_flex_configs_status_t`,
 * | BSP should copy this sconf data from defined path
 * @endrst
 */
#define DAFC_FLEX_CONFIGS_SCONF_PATH "/mnt/lg/cmn_data/dafc/calibration.sconf"

/**
 * @brief path to read/write DAFC Flex Configs (dconf)
 *
 * @rst
 * | This path would be used to read/write DAFC Flex Configs
 * | If :type:`SOUNDENGINE_DAFC_FLEX_CONFIGS_STATUS` is called with :type:`soundengine_dafc_flex_configs_status_t`,
 * | BSP should copy this dconf data from defined path
 * @endrst
 */
#define DAFC_FLEX_CONFIGS_DCONF_PATH "/mnt/lg/cmn_data/dafc/calibration.dconf"

/**
 * @brief soundengine_dafc_flex_configs_status_t
 *
 * @rst
 * enum of DAFC Flex Configs Status to set :c:macro:`SOUNDENGINE_DAFC_FLEX_CONFIGS_STATUS`
 * @endrst
 */
typedef enum soundengine_dafc_flex_configs_status {
    FLEX_CONFIGS_STATUS_NONE               = 0,  /**< DAFC flex configs has not been updated yet */
    FLEX_CONFIGS_STATUS_TUNING             = 1,  /**< DAFC flex configs would be updated after tuning, so be ready to update sconf/dconf data */
    FLEX_CONFIGS_STATUS_UPDATE_REQUESTED   = 2,  /**< DAFC flex configs files are modified so BSP needs to read sconf/dconf data to apply for  FlexRenderer */
    FLEX_CONFIGS_STATUS_UPDATING           = 3,  /**< BSP is reading and updating sconf/dconf data. user should not read/write the data files */
    FLEX_CONFIGS_STATUS_UPDATE_DONE        = 4,  /**< The latest DAFC flex configs files are applied to FlexRenderer */
} soundengine_dafc_flex_configs_status_t;

/**
 * @brief set/get DAFC Flex Configs Status
 * @li priority : 1
 *
 * @rst
 * This setting would set/get of :type:`soundengine_dafc_flex_configs_status_t`
 *
 * Below status could be set only for setting by user
 *
 * | * If :cpp:enumerator:`FLEX_CONFIGS_STATUS_TUNING` is set, it means that DAFC flex configs would be updated after tuning, so be ready to update sconf/dconf data
 * | * If :cpp:enumerator:`FLEX_CONFIGS_STATUS_UPDATE_REQUESTED` is set, it means that DAFC flex configs files are modified so BSP needs to read sconf/dconf data to apply for FlexRenderer
 *
 *
 * Below status is not for setting, but only for getting
 *
 * | * If its get value is :cpp:enumerator:`FLEX_CONFIGS_STATUS_NONE`, it means that DAFC flex configs has not been updated yet. :cpp:enumerator:`FLEX_CONFIGS_STATUS_NONE` is a default status
 * | * If its get value is :cpp:enumerator:`FLEX_CONFIGS_STATUS_UPDATING`, it means that BSP is reading and updating sconf/dconf data.
 * |   User should not read/write the data files.
 * |   If user (mw) tries to set this API at this status, BSP should return error and status should not be changed.
 * | * If its get value is :cpp:enumerator:`FLEX_CONFIGS_STATUS_UPDATE_DONE`, it means that the latest DAFC flex configs files are applied to FlexRenderer
 *
 * @endrst
 *
 * @b Usage
 * @code
 * // 0) If DAFC flex configs has not been updated yet, current status would be none.
 * amixer -c 0 get name="SoundEngine DAFC Flex Configs Status"
 * => 0 (FLEX_CONFIGS_STATUS_NONE)
 *
 * // 1) sconf/dconf data is on tuning (currently FlexRenderer uses old sconf/dconf data).
 * amixer -c 0 cset name="SoundEngine DAFC Flex Configs Status" 1
 *
 * // 2) tuning is done, so sconf/dconf file is modified, BSP needs to read sconf/dconf data to apply to FlexRenderer.
 * amixer -c 0 cset name="SoundEngine DAFC Flex Configs Status" 2
 *
 * // 3) BSP should update this status to notify that BSP is reading and updating sconf/dconf data.
 * // User should not read/write the data files.
 * // If user (mw) tries to set this API at this status, BSP should return error and status should not be changed.
 * amixer -c 0 get name="SoundEngine DAFC Flex Configs Status"
 * => 3 (FLEX_CONFIGS_STATUS_UPDATING)
 *
 * // 4) BSP should update this status to notify that the latest DAFC flex configs files are applied to FlexRenderer
 * amixer -c 0 get name="SoundEngine DAFC Flex Configs Status"
 * => 4 (FLEX_CONFIGS_STATUS_UPDATE_DONE)
 * @endcode
 *
 * @b Pseudocode
 * @code
 * soundengine_dafc_flex_configs_status_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // set DAFC Flex Confgis Status
 *     int status = ucontrol->value.integer.value[0];
 * }
 *
 * soundengine_dafc_flex_configs_status_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get current DAFC Flex Configs Status
 *     ucontrol->value.integer.value[0] = status;
 * }
 * @endcode
 *
 *
 * @param[in] soundengine_dafc_flex_configs_status_t status,
 * @param[out] soundengine_dafc_flex_configs_status_t status,
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define SOUNDENGINE_DAFC_FLEX_CONFIGS_STATUS "SoundEngine DAFC Flex Configs Status"

#endif // _ALSA_EXT_DAP_H
