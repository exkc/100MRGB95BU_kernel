/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022-2024 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_SOUNDENGINE_COMMON_H
#define _ALSA_EXT_SOUNDENGINE_COMMON_H

/**
 * @brief every lgse function got index to support corresponding sound output \n
 * @rst
 *
 * | For example, `FN000` function's index will start 0 for TV Speaker (:type:`LGSE_SPK`).
 * | And `FN000` function's index will start 10 for TV Speaker for BT Surround(`LGSE_SPK_BTSUR`).
 *
 * * For :type:`LGSE_SPK`: 0,1,2
 * * For :type:`LGSE_SPK_BTSUR`: 10,11,12
 *
 * if index is not supported, :type:`snd_hctl_find_elem` should return error.
 *
 * | Some of machines may not support specific :type:`lgse_index_ouptut_t` due to hw limitation.
 * | For the limitation case, BSP should confirm the exception cases before implementation.
 *
 * | For LGSE_DAP_HP_BT, currently there would be no LGSE/DAP or Sound Engine Common function call.
 * | It would be used only for matching sound engine index with related sound output.
 *
 * **LGSE Index of Output Capability for LGSE Version**
 *
 * ============================================= =============== ================= ================= =================
 * :type:`lgse_index_ouptut_t` \\ webOS Version  all (webOS4.5)  all (webOS5.0 ~)  all (webOS22 ~)   all (webOS25 ~)
 * ============================================= =============== ================= ================= =================
 * LGSE_SPK                                      O               O                 O                 O
 * LGSE_SPK_BTSUR                                O               O                 O                 O
 * LGSE_BT_BTSUR                                 O               O                 O                 O
 * LGSE_ARC                                      X               O                 O                 O
 * LGSE_BT                                       X               O                 O                 O
 * LGSE_SPK_ARC                                  X               X                 O                 O
 * LGSE_DAP_HP_BT                                X               X                 X                 O
 * LGSE_DAFC                                     X               X                 X                 O
 * ============================================= =============== ================= ================= =================
 *
 * @endrst
 */
typedef enum lgse_output_type {
    LGSE_SPK       = 0,  /**< Index for TV Speaker */
    LGSE_SPK_BTSUR = 10, /**< Index for SPK in BT Surround Mode */
    LGSE_BT_BTSUR  = 20, /**< Index for BT in BT Surround Mode */
    LGSE_ARC       = 30, /**< Index for ARC */
    LGSE_BT        = 40, /**< Index for BT */
    LGSE_SPK_ARC   = 50, /**< Index for TV Speaker in TVSPK + ARC (with Harmony) Mode */
    LGSE_DAP_HP_BT = 60, /**< Index for DAP Headphone BT Output */
    LGSE_DAFC      = 70, /**< Index for DAFC Output */
    LGSE_NONE      = 0xFF, /**< SE is not connected */
} lgse_index_ouptut_t;

/**
 * @brief parameter for "LGSE Index Output Capability"
 * @see LGSE_INDEX_OUTPUT_CAPABILITY
 */
struct LgseIndedxOutputCapInfo {
    int index_output; /**< index_output: see `lgse_index_ouptut_t` for other cases */
    int bSupported; /**< capability: supported(1), not-supported(0) */
};

/**
 * @deprecated
 *  Deprecated since webOS22, it will be removed from webOS 24
 * @brief Get LGSE Index of Output Capability
 * @li priority : 1
 *
 * Get LGSE Index of Output Capability
 * -# Put LGSE Index of Output Capability Information which user wants to know capability of
 * -# Get the capability of the specific index (bSupported)
 *
 *
 * e.g. To check if LGSE_SPK_BTSUR is supported
 * -# call put function `LGSE Index Output Capability` with [10]
 * -# call get function `LGSE Index Output Capability`
 *     -# will get [10, 1] if it is supported
 *     -# will get [10, 0] if it is not supported
 *
 * Some of machines may not support specific `lgse_index_ouptut_t` due to hw limitation
 * For the limitation case, BSP should confirm the exception cases before implementation
 *
 * @see lgse_index_ouptut_t
 *
 * **LGSE Index of Output Capability for LGSE Version**
 * @rst
 * ============================================= =============== ================= ================= =================
 * :type:`lgse_index_ouptut_t` \\ webOS Version  all (webOS4.5)  all (webOS5.0 ~)  all (webOS22 ~)   all (webOS25 ~)
 * ============================================= =============== ================= ================= =================
 * LGSE_SPK                                      O               O                 O                 O
 * LGSE_SPK_BTSUR                                O               O                 O                 O
 * LGSE_BT_BTSUR                                 O               O                 O                 O
 * LGSE_ARC                                      X               O                 O                 O
 * LGSE_BT                                       X               O                 O                 O
 * LGSE_SPK_ARC                                  X               X                 O                 O
 * LGSE_DAP_HP_BT                                X               X                 X                 O
 * LGSE_DAFC                                     X               X                 X                 O
 * ============================================= =============== ================= ================= =================
 * @endrst
 *
 * @b Pseudocode
 * @code
 * lgse_index_output_capability_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *
 *     int index_output = ucontrol->value.integer.value[0];
 *     // set LGSE Index of Output Capability Information
 * }
 *
 * lgse_index_output_capability_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get LGSE Index of Output Capability
 *     ucontrol->value.integer.value[0] = index_output;
 *     ucontrol->value.integer.value[1] = bSpported;
 * }
 * @endcode
 *
 * @param[in] index_output int
 * @param[out] index_output int (default: 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 *
 */
#define LGSE_INDEX_OUTPUT_CAPABILITY "LGSE Index Output Capability"

/**
 * @brief lgse_init_ext_type_t
 * set initial driver setting for sound engine
 */
typedef enum lgse_init_ext_type {
    LGSE_INIT_UNKNOWN         = 0, /**< Not Initialized */
    LGSE_INIT_LGSE_ONLY       = 1, /**< Use LGSE Only */
    LGSE_INIT_LGSE_VX         = 2, /**< Use LGSE & DTS Virtual X */
    LGSE_INIT_LGSE_ATMOS      = 3, /**< Use LGSE & DAP */
    LGSE_INIT_LGSE_VX_AISOUND = 4, /**< Use LGSE & DTS Virtual X & AI Sound */
    LGSE_INIT_LGSE_ATMOS_AISOUND = 5, /**< Use LGSE & DAP & AI Sound */
    LGSE_INIT_LGSE_AISOUND       = 6, /**< Use LGSE & AI Sound */
} lgse_se_init_ext_type_t;

/**
 * @brief lgse initial setting
 * @li priority : 1
 *
 * Set inital mode of LGSE Mode. This api would be called once With this api, \n
 * driver would know what kind of sound engines could work by calling "LGSE
 * SoundEngine Mode" \n
 * For example, if "LGSE_INIT_LGSE_ATMOS" is set, only lgse
 * and atmos(dap) can be set by calling
 *
 * @li "LGSE SoundEngine Mode" with LGSE_MODE_LGSE_ONLY: OK
 * @li "LGSE SoundEngine Mode" with LGSE_MODE_LGSE_ATMOS: OK
 * @li "LGSE SoundEngine Mode" with LGSE_MODE_LGSE_VX: ERROR
 * @li "LGSE SoundEngine Mode" with LGSE_MODE_LGSE_AISOUND: ERROR
 *
 * @b Pseudocode
 * @code
 * lgse_soundengine_init_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int mode = ucontrol->value.integer.value[0];
 *     // set mode param
 * }
 *
 * lgse_soundengine_init_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get mode param
 *     ucontrol->value.integer.value[0] = mode;
 * }
 * @endcode
 *
 * @param[in] int(lgse_init_ext_type_t) lgse_init,
 * @param[out] int(lgse_init_ext_type_t) lgse_init, (default : 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_SOUNDENGINE_INIT "LGSE SoundEngine Init"

/**
 * @brief lgse_mode_ext_type_t
 * set driver setting for sound engine
 */
typedef enum lgse_mode_ext_type {
    LGSE_MODE_UNKNOWN      = 0, /**< Mode is not initialized */
    LGSE_MODE_LGSE_ONLY    = 1, /**< Use LGSE Only */
    LGSE_MODE_LGSE_VX      = 2, /**< Use LGSE & DTS Virtual X */
    LGSE_MODE_LGSE_ATMOS   = 3, /**< Use DAP */
    LGSE_MODE_LGSE_AISOUND = 4, /**< Use AI Sound */
} lgse_se_mode_ext_type_t;

/**
 * @brief lgse setting
 * @li priority : 1
 *
 * Change LGSE Mode. This api would be called in run-time sound engine path
 * would be changed by this api. Possible enums of "LGSE SoundEngine Mode"
 * (lgse_se_mode_ext_type_t) are decided by "LGSE SoundEngine Init"
 *
 * Work of this function with "LGSE SoundEngine Init"
 * This api is called with lgse_index_ouptut_t,
 * and the api should work according to related sound output
 * @see `lgse_index_ouptut_t`
 *
 * @rst
 * ======================== ======= ========= ========== ======= ============
 * LGSE_INIT/LGSE_MODE      UNKNOWN LGSE_ONLY LGSE_ATMOS LGSE_VX LGSE_AISOUND
 * ======================== ======= ========= ========== ======= ============
 * INIT_UNKNOWN (DEFAULT)   O       X         X          X       X
 * INIT_LGSE_VX_AISOUND     X       O         X          O       O
 * INIT_LGSE_VX             X       O         X          O       X
 * INIT_LGSE_ONLY           X       O         X          X       X
 * INIT_LGSE_ATMOS_AISOUND  X       O         O          X       O
 * INIT_LGSE_ATMOS          X       O         O          X       X
 * INIT_LGSE_AISOUND        X       O         X          X       O
 * ======================== ======= ========= ========== ======= ============
 * @endrst
 * For X, please return error
 *
 * @b Pseudocode
 * @code
 * lgse_soundengine_mode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int mode = ucontrol->value.integer.value[0];
 *     // set mode param
 * }
 *
 * lgse_soundengine_mode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get mode param
 *     ucontrol->value.integer.value[0] = mode;
 * }
 * @endcode
 *
 * @param[in] int lgse_mode int:lgse_mode_ext_type_t
 * @param[out] int lgse_mode int:lgse_mode_ext_type_t, (default : 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_SOUNDENGINE_MODE "LGSE SoundEngine Mode"

/**
 * @brief lgse downmix
 * @li priority 1
 *
 * Set LGSE downmix on/off This api would be called in run-time downmix is done
 * by LGSE or decoder \n
 * If it is set as 1 (true), downmix is done by sound engine module \n
 * If it is set as 0 (false), downmix is done by below table \n
 * @rst
 * ============================ ========================== =========== =============
 * LGSE_MODE/Downmixer(module)  Decoder (or Pcm Renderer)  DAP         Sound Engine
 * ============================ ========================== =========== =============
 * UNKNOWN                      N/A
 * LGSE_ONLY                    O
 * LGSE_ATMOS                                              O
 * LGSE_VX                      O
 * LGSE_AISOUND                                                        O (always)
 * ============================ ========================== =========== =============
 * @endrst
 *
 * This api is called with lgse_index_ouptut_t, \n
 * and the api should work according to related sound output \n
 * @see `lgse_index_ouptut_t`
 *
 * @code
 * lgse_downmix_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int bEnable = ucontrol->value.integer.value[0];
 *     // set mode param
 * }
 *
 * lgse_downmix_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get mode param
 *     ucontrol->value.integer.value[0] = bEnable;
 * }
 * @endcode
 *
 * @param[in] bEnable int
 * @param[out] bEnable int
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_DOWNMIX "LGSE DownMix"

/**
 * @brief set/get Sound Engine Index matched Sound Output
 * @li priority : 1
 *
 * @rst
 * This setting would match :type:`lgse_index_ouptut_t` with each :type:`common_output_ext_type_t`\
 * For example,
 *
 * * If Sound Output is set as TV Speaker Only, this function would be called with :c:macro:`COMMON_SPK` :type:`LGSE_SPK`
 * * If Sound Output is set as BT (SE) Only, this function would be called with :c:macro:`COMMON_SE_BT` :type:`LGSE_BT`
 * * If Sound Output is set as TV Speaker + BT (SE) Surround , this function would be called two times with
 *   :c:macro:`COMMON_SPK` :type:`LGSE_SPK_BTSUR` and :c:macro:`COMMON_SE_BT` :type:`LGSE_BT_BTSUR`
 *
 * | For each sound output, default index is :type:`LGSE_NONE`.
 * | This function would be called only for :c:macro:`COMMON_SPK`, :c:macro:`COMMON_SE_BT`, :c:macro:`COMMON_SE_ARC`, :c:macro:`COMMON_DAP_HP_BT`, and :c:macro:`COMMON_DAFC`
 *
 * @endrst
 *
 * @b Pseudocode
 * @code
 * lgse_se_index_matched_output_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // set mode param
 *     int output = ucontrol->value.integer.value[0];
 *     int index = ucontrol->value.integer.value[1];
 * }
 *
 * lgse_se_index_matched_output_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get se index of output
 *     ucontrol->value.integer.value[0] = index_spk; // SE index of COMMON_SPK (default: LGSE_NONE)
 *     ucontrol->value.integer.value[1] = index_se_bt; // SE index of COMMON_SE_BT (default: LGSE_NONE)
 *     ucontrol->value.integer.value[2] = index_se_arc; // SE index of COMMON_SE_ARC (default: LGSE_NONE)
 *     ucontrol->value.integer.value[3] = index_se_dap_hp_bt; // SE index of COMMON_DAP_HP_BT (default: LGSE_NONE)
 *     ucontrol->value.integer.value[4] = index_se_dafc; // SE index of COMMON_DAFC (default: LGSE_NONE)
 * }
 * @endcode
 *
 *
 * @param[in] common_output_ext_type_t output,
 * @param[in] lgse_index_ouptut_t index
 * @param[out] lgse_index_ouptut_t index_spk,
 * @param[out] lgse_index_ouptut_t index_se_bt,
 * @param[out] lgse_index_ouptut_t index_se_arc,
 * @param[out] lgse_index_ouptut_t index_se_dap_hp_bt,
 * @param[out] lgse_index_ouptut_t index_se_dafc,
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_SE_INDEX_MATCHED_OUTPUT "LGSE SE Index Matched Output"

#endif // _ALSA_EXT_SOUNDENGINE_COMMON_H
