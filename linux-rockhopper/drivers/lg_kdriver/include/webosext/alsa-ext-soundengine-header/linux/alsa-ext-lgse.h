/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_LGSE_H
#define _ALSA_EXT_LGSE_H

/**
 * @brief LED lighting mode type
 */
typedef enum lgse_ll_mode_type {
    LGSE_LL_MODE_VU_METER    = 0, // default
    LGSE_LL_MODE_VOLUME_MODE = 1,
    LGSE_LL_MODE_LIGHT_FREQ  = 2,
    LGSE_LL_MODE_PEACEFUL1   = 3,
    LGSE_LL_MODE_PEACEFUL2   = 4,
    LGSE_LL_MODE_FREQ_VU     = 5,
    LGSE_LL_MODE_RESERVE1    = 6, // follow default until implementation
    LGSE_LL_MODE_RESERVE2    = 7, // follow default until implementation
    LGSE_LL_MODE_MAX         = 8
} lgse_ll_mode_type_t;

/**
 * @brief Get LGSE version for what driver use
 * @li priority : 1
 *
 * if driver use LGSE 7.0 return 70, and if driver use LGSE 8.2 return 82.
 *
 * @b Pseudocode
 * @code
 * lgse_version_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get version param
 *     ucontrol->value.integer.value[0] = version;
 * }
 * @endcode
 *
 * @param[out] mode int
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_VERSION "LGSE Version"

/**
 * @brief alsa bytes array max size
 */
#define LGSE_DATA_MAX_SIZE 512

/**
 * @brief Set LGSE Mode
 * @li priority : 3
 *
 * Set some mode flag for LGSE. If the parameter's size is bigger then
 * LGSE_COPY_DATA_SIZE, we should use index for sending a data.
 *
 * @b Pseudocode
 * @code
 * //LGSE_COPY_DATA_SIZE is defined by alsa-ext-lgse.h
 * lgse_mode_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     int mode = ucontrol->value.integer.value[0];
 *     int deq = ucontrol->value.integer.value[1];
 *     int peq = ucontrol->value.integer.value[2];
 *     // set mode param
 * }
 *
 * lgse_mode_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get mode param
 *     ucontrol->value.integer.value[0] = mode;
 *     ucontrol->value.integer.value[1] = peq;
 *     ucontrol->value.integer.value[2] = deq;
 * }
 * @endcode
 *
 * @param[in] mode int
 * @param[in] deq_mode int
 * @param[in] peq_mode int
 * @param[out] mode int (default : 0)
 * @param[out] deq_mode int (default : 0)
 * @param[out] peq_mode int (default : 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_MODE "LGSE Mode"

/**
 * @brief Set LGSE FNxxx
 * @li priority : 3
 *
 * Set Init / Var / Out Parameter value for FNxxx function. If the size of the
 * parameter is larger than LGSE_COPY_DATA_SIZE (512) bytes, add index to allow
 * the data to be transmitted. Implement a function for each String.
 * (LGSE_INIT_FN000, LGSE_VAR_FN000, LGSE_VAR_FN000_1) The values of NUM in
 * String Define refer to the Parameter Size of the above function.
 *
 * This format applies equally to all FNxxx functions.
 *
 * @b Pseudocode
 * @code
 * //LGSE_COPY_DATA_SIZE is defined by alsa-ext-lgse.h
 * lgse_fnxxx_init_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     memcpy(modes,ucontrol->value.bytes.data,LGSE_DATA_MAX_SIZE);
 *     // set mode param
 * }
 *
 * lgse_fnxxx_init_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get mode param
 *     memcpy(ucontrol->value.bytes.data, modes, LGSE_DATA_MAX_SIZE);
 * }
 * @endcode
 *
 * @param[in] param unsigned char[LGSE_INIT_FN000_NUM]
 * @param[out] param unsigned char[LGSE_INIT_FN000_NUM] param (default : 0)
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_INIT_MAIN "LGSE Init Main"
/**
 * @brief parameter for LGSE_INIT_MAIN
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_MAIN_NUM (10 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_MAIN "LGSE Var Main"
/**
 * @brief parameter for LGSE_VAR_MAIN
 * @see LGSE_VAR_MAIN
 */
#define LGSE_VAR_MAIN_NUM (3 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_MIXER_GAIN_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_MIXER_GAIN "LGSE Mixer Gain"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_MIXER_GAIN`
 * @endrst
 */
#define LGSE_MIXER_GAIN_NUM (350 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN000 "LGSE Init Fn000"
/**
 * @brief parameter for LGSE_INIT_FN000
 * @see LGSE_INIT_FN000
 */
#define LGSE_INIT_FN000_NUM (295 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN000 "LGSE Var Fn000"
/**
 * @brief parameter for LGSE_VAR_FN000
 * @see LGSE_VAR_FN000
 */
#define LGSE_VAR_FN000_NUM (1 * 4)

/**
 * @see LGSE_INIT_MAIN
 * For more than two channels input
 */
#define LGSE_VAR_FN000_1 "LGSE Var Fn000_1"

/**
 * @brief parameter for LGSE_VAR_FN000_1
 * @see LGSE_VAR_FN000_1
 */
#define LGSE_VAR_FN000_1_NUM (1 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN001 "LGSE Init Fn001"
/**
 * @brief parameter for LGSE_INIT_FN001
 * @see LGSE_INIT_FN001
 */
#define LGSE_INIT_FN001_NUM (21 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN001 "LGSE Var Fn001"
/**
 * @brief parameter for LGSE_VAR_FN001
 * @see LGSE_VAR_FN001
 */
#define LGSE_VAR_FN001_NUM (130 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN001_1 "LGSE Var Fn001_1"

/**
 * @brief parameter for LGSE_VAR_FN001_1
 * @see LGSE_VAR_FN001_1
 */
#define LGSE_VAR_FN001_1_NUM (130 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN001_2 "LGSE Var Fn001_2"

/**
 * @brief parameter for LGSE_VAR_FN001_2
 * @see LGSE_VAR_FN001_2
 */
#define LGSE_VAR_FN001_2_NUM (130 * 4)

/**
 * @see LGSE_INIT_MAIN
 * For more than two channels input
 */
#define LGSE_INIT_FN002 "LGSE Init Fn002"

/**
 * @brief parameter for LGSE_INIT_FN002
 * @see LGSE_INIT_FN002
 * For more than two channels input
 */
#define LGSE_INIT_FN002_NUM (20 * 4)

/**
 * @see LGSE_INIT_MAIN
 * For more than two channels input
 */
#define LGSE_VAR_FN002 "LGSE Var Fn002"

/**
 * @brief parameter for LGSE_VAR_FN002
 * @see LGSE_VAR_FN002
 */
#define LGSE_VAR_FN002_NUM (100 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN002_V83_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN002_V83 "LGSE Var Fn002 V83"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN002_V83`
 * @endrst
 */
#define LGSE_VAR_FN002_V83_NUM (200 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN002_1 "LGSE Var Fn002_1"

/**
 * @brief parameter for LGSE_VAR_FN002_1
 * @see LGSE_VAR_FN002_1
 */
#define LGSE_VAR_FN002_1_NUM (100 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN002_1_V83_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN002_1_V83 "LGSE Var Fn002_1 V83"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN002_1_V83`
 * @endrst
 */
#define LGSE_VAR_FN002_1_V83_NUM (200 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN003_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN003 "LGSE Var Fn003"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN003`
 * @endrst
 */
#define LGSE_VAR_FN003_NUM (20 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN003_1_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN003_1 "LGSE Var Fn003_1"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN003_1`
 * @endrst
 */
#define LGSE_VAR_FN003_1_NUM (60 * 4)
/**

 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN004 "LGSE Var Fn004"
/**
 * @brief parameter for LGSE_VAR_FN004
 * @see LGSE_VAR_FN004
 */
#define LGSE_VAR_FN004_NUM (25 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_INIT_FN004_V83_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_INIT_FN004_V83 "LGSE Init Fn004 V83"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_INIT_FN004_V83`
 * @endrst
 */
#define LGSE_INIT_FN004_V83_NUM (841 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN004_V83_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN004_V83 "LGSE Var Fn004 V83"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN004_V83`
 * @endrst
 */
#define LGSE_VAR_FN004_V83_NUM (842 * 4)

/**
 * @see LGSE_INIT_MAIN
 * For more than two channels input
 */
#define LGSE_VAR_FN004_1 "LGSE Var Fn004_1"

/**
 * @brief parameter for LGSE_VAR_FN004_1
 * @see LGSE_VAR_FN004_1
 */
#define LGSE_VAR_FN004_1_NUM (25 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN004_1_V83_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN004_1_V83 "LGSE Var Fn004_1 V83"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN004_1_V83`
 * @endrst
 */
#define LGSE_VAR_FN004_1_V83_NUM (842 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN005 "LGSE Var Fn005"
/**
 * @brief parameter for LGSE_VAR_FN005
 * @see LGSE_VAR_FN005
 */
#define LGSE_VAR_FN005_NUM (10 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN005_1 "LGSE Var Fn005_1"
/**
 * @brief parameter for LGSE_VAR_FN005_1
 * @see LGSE_VAR_FN005_1
 */
#define LGSE_VAR_FN005_1_NUM (50 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN008 "LGSE Init Fn008"
/**
 * @brief parameter for LGSE_INIT_FN008
 * @see LGSE_INIT_FN008
 */
#define LGSE_INIT_FN008_NUM (108 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN008 "LGSE Var Fn008"
/**
 * @brief parameter for LGSE_VAR_FN008
 * @see LGSE_VAR_FN008
 */
#define LGSE_VAR_FN008_NUM (11 * 4)

/**
 * @see LGSE_INIT_MAIN
 * For more than two channels input
 */
#define LGSE_VAR_FN008_1 "LGSE Var Fn008_1"

/**
 * @brief parameter for LGSE_VAR_FN008_1
 * @see LGSE_VAR_FN008_1
 */
#define LGSE_VAR_FN008_1_NUM (11 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN009 "LGSE Init Fn009"
/**
 * @brief parameter for LGSE_INIT_FN009
 * @see LGSE_INIT_FN009
 */
#define LGSE_INIT_FN009_NUM (10 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN009 "LGSE Var Fn009"
/**
 * @brief parameter for LGSE_VAR_FN009
 * @see LGSE_VAR_FN009
 */
#define LGSE_VAR_FN009_NUM (2 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN009_1_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN009_1 "LGSE Var Fn009_1"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN009_1`
 * @endrst
 */
#define LGSE_VAR_FN009_1_NUM (30 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN010 "LGSE Init Fn010"
/**
 * @brief parameter for LGSE_INIT_FN010
 * @see LGSE_INIT_FN010
 */
#define LGSE_INIT_FN010_NUM (10 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN010 "LGSE Var Fn010"
/**
 * @brief parameter for LGSE_VAR_FN010
 * @see LGSE_VAR_FN010
 */
#define LGSE_VAR_FN010_NUM (1 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_INIT_FN011_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_INIT_FN011 "LGSE Init Fn011"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_INIT_FN011`
 * @endrst
 */
#define LGSE_INIT_FN011_NUM (100 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN011_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN011 "LGSE Var Fn011"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN011`
 * @endrst
 */
#define LGSE_VAR_FN011_NUM (30 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN013 "LGSE Var Fn013"
/**
 * @brief parameter for LGSE_VAR_FN013
 * @see LGSE_VAR_FN013
 */
#define LGSE_VAR_FN013_NUM (22 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN014 "LGSE Init Fn014"
/**
 * @brief parameter for LGSE_INIT_FN014
 * @see LGSE_INIT_FN014
 */
#define LGSE_INIT_FN014_NUM (136 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN014 "LGSE Var Fn014"
/**
 * @brief parameter for LGSE_VAR_FN014
 * @see LGSE_VAR_FN014
 */
#define LGSE_VAR_FN014_NUM (1 * 4)
/**
 * Related to DNN (Dynamic Neural Network) of FN014
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN014_1 "LGSE Var Fn014_1"
/**
 * @brief parameter for LGSE_VAR_FN014_1
 * @see LGSE_VAR_FN014_1
 */
#define LGSE_VAR_FN014_1_NUM (10*4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN016 "LGSE Init Fn016"
/**
 * @brief parameter for LGSE_INIT_FN016
 * @see LGSE_INIT_FN016
 */
#define LGSE_INIT_FN016_NUM (50 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN016 "LGSE Var Fn016"
/**
 * @brief parameter for LGSE_VAR_FN016
 * @see LGSE_VAR_FN016
 */
#define LGSE_VAR_FN016_NUM (100 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN017 "LGSE Var Fn017"
/**
 * @brief parameter for LGSE_VAR_FN017
 * @see LGSE_VAR_FN017
 */
#define LGSE_VAR_FN017_NUM (162 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN017_2 "LGSE Var Fn017_2"

/**
 * @brief parameter for LGSE_VAR_FN017_2
 * @see LGSE_VAR_FN017_2
 */
#define LGSE_VAR_FN017_2_NUM (200 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN017_2_V83_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN017_2_V83 "LGSE Var Fn017_2 V83"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN017_2_V83`
 * @endrst
 */
#define LGSE_VAR_FN017_2_V83_NUM (280 * 4)

/**
 * @see LGSE_INIT_MAIN
 * For more than two channels input
 */
#define LGSE_VAR_FN017_3 "LGSE Var Fn017_3"

/**
 * @brief parameter for LGSE_VAR_FN017_3
 * @see LGSE_VAR_FN017_3
 */
#define LGSE_VAR_FN017_3_NUM (200 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN017_3_V83_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN017_3_V83 "LGSE Var Fn017_3 V83"

/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN017_3_V83`
 * @endrst
 */
#define LGSE_VAR_FN017_3_V83_NUM (280 * 4)

/**
 * @see LGSE_INIT_MAIN
 * @deprecated
 *  Deprecated since webOS22, it will be removed from webOS 24
 */
#define LGSE_INIT_FN019 "LGSE Init Fn019"
/**
 * @brief parameter for LGSE_INIT_FN019
 * @see LGSE_INIT_FN019
 */
#define LGSE_INIT_FN019_NUM (98 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN019 "LGSE Var Fn019"
/**
 * @brief parameter for LGSE_VAR_FN019
 * @see LGSE_VAR_FN019
 */
#define LGSE_VAR_FN019_NUM (4 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN019_1 "LGSE Var Fn019_1"

/**
 * @brief parameter for LGSE_VAR_FN019_1
 * @see LGSE_VAR_FN019_1
 */
#define LGSE_VAR_FN019_1_NUM (200 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN020 "LGSE Init Fn020"

/**
 * @brief parameter for LGSE_INIT_FN020
 * @see LGSE_INIT_FN020
 */
#define LGSE_INIT_FN020_NUM (45 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN020 "LGSE Var Fn020"

/**
 * @brief parameter for LGSE_VAR_FN020
 * @see LGSE_VAR_FN020
 */
#define LGSE_VAR_FN020_NUM (35 * 4)

/**
 * @see LGSE_INIT_MAIN
 * @deprecated
 *  Deprecated since webOS22, it will be removed from webOS 24
 */
#define LGSE_INIT_FN022 "LGSE Init Fn022"
/**
 * @brief parameter for LGSE_INIT_FN022
 * @see LGSE_INIT_FN022
 */
#define LGSE_INIT_FN022_NUM (6 * 4)
/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN022 "LGSE Var Fn022"
/**
 * @brief parameter for LGSE_VAR_FN022
 * @see LGSE_VAR_FN022
 */
#define LGSE_VAR_FN022_NUM (480 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN022_1 "LGSE Var Fn022_1"

/**
 * @brief parameter for LGSE_VAR_FN022_1
 * @see LGSE_VAR_FN022_1
 */
#define LGSE_VAR_FN022_1_NUM (500 * 4)

/**
 * @see LGSE_INIT_MAIN
 * For more than two channels input
 */
#define LGSE_VAR_FN022_2 "LGSE Var Fn022_2"

/**
 * @brief parameter for LGSE_VAR_FN022_2
 * @see LGSE_VAR_FN022_2
 */
#define LGSE_VAR_FN022_2_NUM (500 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN023 "LGSE Init Fn023"
/**
 * @brief parameter for LGSE_INIT_FN023
 * @see LGSE_INIT_FN023
 */
#define LGSE_INIT_FN023_NUM (188 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN024 "LGSE Init Fn024"
/**
 * @brief parameter for LGSE_INIT_FN024
 * @see LGSE_INIT_FN024
 */
#define LGSE_INIT_FN024_NUM (12 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN025 "LGSE Var Fn025"
/**
 * @brief parameter for LGSE_VAR_FN025
 * @see LGSE_VAR_FN025
 */
#define LGSE_VAR_FN025_NUM (100 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN025_1 "LGSE Var Fn025_1"
/**
 * @brief parameter for LGSE_VAR_FN025_1
 * @see LGSE_VAR_FN025_1
 */
#define LGSE_VAR_FN025_1_NUM (123 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN026 "LGSE Var Fn026"
/**
 * @brief parameter for LGSE_VAR_FN026
 * @see LGSE_VAR_FN026
 */
#define LGSE_VAR_FN026_NUM (200 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN028 "LGSE Var Fn028"
/**
 * @brief parameter for LGSE_VAR_FN028
 * @see LGSE_VAR_FN028
 */
#define LGSE_VAR_FN028_NUM (10 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN029 "LGSE Var Fn029"
/**
 * @brief parameter for LGSE_VAR_FN029
 * @see LGSE_VAR_FN029
 */
#define LGSE_VAR_FN029_NUM (200 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN030 "LGSE Init Fn030"

/**
 * @brief parameter for LGSE_INIT_FN030
 * @see LGSE_INIT_FN030
 */
#define LGSE_INIT_FN030_NUM (20 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN030 "LGSE Var Fn030"

/**
 * @brief parameter for LGSE_VAR_FN030
 * @see LGSE_VAR_FN030
 */
#define LGSE_VAR_FN030_NUM (50 * 4)

/**
 * @see LGSE_INIT_MAIN
 * @deprecated
 *  Deprecated since webOS22, it will be removed from webOS 24
 */
#define LGSE_OUT_FN030 "LGSE Out Fn030"

/**
 * @brief parameter for LGSE_OUT_FN030
 * @see LGSE_OUT_FN030
 */
#define LGSE_OUT_FN030_NUM (58 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_INIT_FN030_1 "LGSE Init Fn030_1"

/**
 * @brief parameter for LGSE_INIT_FN030_1
 * @see LGSE_INIT_FN030_1
 */
#define LGSE_INIT_FN030_1_NUM (20 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN030_1 "LGSE Var Fn030_1"

/**
 * @brief parameter for LGSE_VAR_FN030_1
 * @see LGSE_VAR_FN030_1
 */
#define LGSE_VAR_FN030_1_NUM (100 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN031 "LGSE Var Fn031"

/**
 * @brief parameter for LGSE_VAR_FN031
 * @see LGSE_VAR_FN031
 */
#define LGSE_VAR_FN031_NUM (100 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN032 "LGSE Var Fn032"

/**
 * @brief parameter for LGSE_VAR_FN032
 * @see LGSE_VAR_FN032
 */
#define LGSE_VAR_FN032_NUM (100 * 4)

/**
 * @see LGSE_INIT_MAIN
 */
#define LGSE_VAR_FN032_1 "LGSE Var Fn032_1"

/**
 * @brief parameter for LGSE_VAR_FN032
 * @see LGSE_VAR_FN032
 */
#define LGSE_VAR_FN032_1_NUM (100 * 4)

/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_INIT_FN034_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_INIT_FN034 "LGSE Init Fn034"
/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_INIT_FN034`
 * @endrst
 */
#define LGSE_INIT_FN034_NUM (50 * 4)
/**
 * @brief
 * @rst
 * This API is called with parameters whose number of parameters is :c:macro:`LGSE_VAR_FN034_NUM`
 * @endrst
 * @see
 * @rst
 * :c:macro:`LGSE_INIT_MAIN`
 * @endrst
 */
#define LGSE_VAR_FN034 "LGSE Var Fn034"
/**
 * @brief
 * @rst
 * number of parameters for :c:macro:`LGSE_VAR_FN034`
 * @endrst
 */
#define LGSE_VAR_FN034_NUM (50 * 4)

/**
 * @brief Get LGSE LED lighting algorithm version for what driver use
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   Get LGSE LED lighting algorithm version for what driver use
 *
 * Performance Requirements
 *   LL should not affect CPU performance
 *
 * Constraints
 *   TV requires LED Light
 * @endrst
 * @b Pseudocode
 * @code
 * lgse_ll_version_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get version param
 *     ucontrol->value.integer.value[0] = version;
 * }
 * @endcode
 *
 * @param[out] mode int
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_LL_VERSION "LGSE LL Version"

/**
 * @brief LGSE LED Lighting driver open
 * @li priority : 3
 * @rst
 * Functional Requirements
 *   It is an API to open LGSE LL (LED Lighting) driver.
 *   Before getting a value from the driver, you have to open it first.
 *
 * Performance Requirements
 *   LL should not affect CPU performance
 *
 * Constraints
 *   TV requires LED Light
 * @endrst
 * @b Pseudocode
 * @code
 * lgse_ll_open_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     open_status = true;
 * }
 *
 * lgse_ll_open_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     ucontrol->value.integer.value[0] = open_status;
 * }
 * @endcode

 * @param[out] open_status bool ( default: false )
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_LL_OPEN "LGSE LL Open"

/**
 * @brief LGSE LED Lighting driver close
 * @li priority : 3
 *
 * @rst
 * Functional Requirements
 *   It is an API to close LGSE LL (LED Lighting).
 *
 * Performance Requirements
 *   LL should not affect CPU performance
 *
 * Constraints
 *   TV requires LED Light
 * @endrst
 * @b Pseudocode
 * @code
 * lgse_ll_close_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     close_status = true;
 * }
 *
 * lgse_ll_close_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     ucontrol->value.integer.value[0] = close_status;
 * }
 * @endcode
 *
 *
 * @param[out] close_status bool ( default: true )
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_LL_CLOSE "LGSE LL Close"

/**
 * @brief LGSE LED Lighting driver start
 * @li priority : 3
 *
 * @rst
 * Functional Requirements
 *   It is an API to start LGSE LL (LED Lighting) driver.
 *   Before starting, open must be performed first.
 *
 * Performance Requirements
 *   LL should not affect CPU performance
 *
 * Constraints
 *   TV requires LED Light
 * @endrst
 * @b Pseudocode
 * @code
 * lgse_ll_start_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     start_status = true;
 * }
 *
 * lgse_ll_start_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     ucontrol->value.integer.value[0] = start_status;
 * }
 * @endcode
 *
 * @param[out] start_status bool ( default: false )
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_LL_START "LGSE LL Start"

/**
 * @brief LGSE LED Lighting mode stop
 * @li priority : 3
 *
 * @rst
 * Functional Requirements
 *   It is an API to stop LGSE LL (LED Lighting) driver.
 *
 * Performance Requirements
 *   LL should not affect CPU performance
 *
 * Constraints
 *   TV requires LED Light
 * @endrst
 * @b Pseudocode
 * @code
 * lgse_ll_stop_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     stop_status = true;
 * }
 *
 * lgse_ll_stop_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     ucontrol->value.integer.value[0] = stop_status;
 * }
 * @endcode

 * @param[out] stop_status bool ( default: true )
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_LL_STOP "LGSE LL Stop"

/**
 * @brief LGSE LED Lighting mode stting
 * @li priority : 3
 *
 * @rst
 * Functional Requirements
 *   It is an API to setting LGSE LL (LED Lighting) configurations.
 *   In order for the driver to operate normally, Mode, the number of leds,
 *   period, power and frequency bound informations are required.
 *
 * Performance Requirements
 *   LL should not affect CPU performance
 *   The response time of this function should be within period.
 *
 * Constraints
 *   TV requires LED Light
 * @endrst
 * @b Pseudocode
 * @code
 * lgse_ll_config_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     ll_mode           = ucontrol->value.integer.value[0]; // bar, sphere
 *     led_unit_num      = ucontrol->value.integer.value[1]; // max 200
 *     period            = ucontrol->value.integer.value[2]; // MAX 200ms
 *     max_power         = ucontrol->value.integer.value[3]; // max_power
 *     min_power         = ucontrol->value.integer.value[4]; // min_power
 *     upper_bound       = ucontrol->value.integer.value[5]; // upper bound frequency
 *     lower_bound       = ucontrol->value.integer.value[6]; // lower bound frequency
 * }
 *
 * lgse_ll_config_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * { // get LGSE ll status
 *     ucontrol->value.integer.value[0] = ll_mode;
 *     ucontrol->value.integer.value[1] = led_unit_num;
 *     ucontrol->value.integer.value[2] = period;
 *     ucontrol->value.integer.value[3] = max_power;
 *     ucontrol->value.integer.value[4] = min_power;
 *     ucontrol->value.integer.value[5] = upper_bound;
 *     ucontrol->value.integer.value[6] = lower_bound;
 * }
 * @endcode
 *
 * @param[in] ll_mode lgse_ll_mode_type_t
 * @param[in] led_unit_num int
 * @param[in] period int
 * @param[in] max_power int
 * @param[in] min_power int
 * @param[in] upper_bound int
 * @param[in] lower_bound int
 *
 * @param[out] ll_mode lgse_ll_mode_type_t ( default: LGSE_LL_MODE_BAR )    0 : VU METER, 1 : VOLUME MODE, 5 : FREQUENCY VOLUME
 * @param[out] led_unit_num int ( default: 40 )                             number of led units, it is 200 or less
 * @param[out] period int ( default: 100(ms) )                              period of capturing audio. It must be 200ms or less
 * @param[out] max_power int ( default: 3dB )                               upper bound of loudness during capture
 * @param[out] min_power int ( default: -20dB )                             lower bound of loudness during capture
 * @param[out] upper_bound int ( default: 20kHz )                           upper bound of frequency during capture it must be 20kHz or less, which is max frequency ofaudible frequency
 * @param[out] lower_bound int ( default: 0Hz )                             lower bound of frequency during capture
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_LL_CONFIG "LGSE LL Config"

/**
 * @brief Get the brightness information form LGSE LED lighting driver
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   It brings the values for a total of n LEDs,
 *   and 0~(n/2-1) represents Left sound data, and (n/2)~(n-1) represents Right sound data.
 *   In the case of VU meter mode, the larger the index of the array, the higher the decibel.
 *   For the brightness value, a value multiplied by 1000 is used to express a decimal point.
 *
 * Performance Requirements
 *   LL should not affect CPU performance
 *
 * Constraints
 *   TV requires LED Light
 * @endrst
 * @b Pseudocode
 * @code
 * lgse_ll_brightness_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // brightness for left captured sound
 *     ucontrol->value.integer.value[0] = brightness_LED[0];
 *     ...
 *     ucontrol->value.integer.value[n/2-1] = brightness_LED[n/2-1];
 *
 *     // brightness for right captured sound
 *     ucontrol->value.integer.value[n/2] = brightness_LED[n/2];
 *     ...
 *     ucontrol->value.integer.value[n-1] = brightness_LED[n-1];
 * }
 * @endcode
 *
 * @param[out] brightness for LED0~LEDn-1 int
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 */
#define LGSE_LL_BRIGHTNESS "LGSE LL Brightness"

/**
 * @brief Get the light frequency information from LGSE LED lighting driver
 * @li priority : 1
 *
 * @rst
 * Functional Requirements
 *   Get the light frequency information from LGSE LED lighting driver
 *
 * Performance Requirements
 *   LL should not affect CPU performance
 *
 * Constraints
 *   TV requires LED Light
 * @endrst
 * @b Pseudocode
 * @code
 * lgse_ll_light_frequency_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
 * {
 *     // get light frequency for each LED
 *     ucontrol->value.integer.value[0] = light_frequency for Left captured sound;
 *     ucontrol->value.integer.value[1] = light_frequency for Right captured sound;
 * }
 * @endcode
 *
 * @param[out] light_frequency for Left captured sound int
 * @param[out] light_frequency for Right captured sound int
 *
 * @return 0 if it success. Otherwise:
 * @li -EBUSY       Internal driver error happened
 * @li -EINVAL      Invalid argument
 * @li -EALREADY    Operation already in progress
 *
 */
#define LGSE_LL_LIGHT_FREQUENCY "LGSE LL Light Frequency"

#endif
