/******************************************************************************
 *   TV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   Copyright(c) 2022 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work may be reproduced, stored in a
 *   retrieval system, or transmitted by any means without prior written
 *   permission of LG Electronics Inc.
 *****************************************************************************/

#ifndef _ALSA_EXT_COMMON_H
#define _ALSA_EXT_COMMON_H

/**
 * @brief sound output type
 *
 * @rst
 * please refer to :type:`common_output_ext_type_t`
 * @endrst
 *
 */
typedef int common_output_ext_type;

/**
 * @brief sound output type enum
 *
 * @rst
 *
 * | It is typedef of :type:`common_output_ext_type`
 * | Use this enum to set output setting (open/connect/disconnect/close/etc)
 * - :c:macro:`COMMON_NO_OUTPUT`
 * - :c:macro:`COMMON_SPK`
 * - :c:macro:`COMMON_OPTIC`
 * - :c:macro:`COMMON_OPTIC_LG`
 * - :c:macro:`COMMON_BLUETOOTH`
 * - :c:macro:`COMMON_HP`
 * - :c:macro:`COMMON_ARC`
 * - :c:macro:`COMMON_WISA`
 * - :c:macro:`COMMON_SE_BT`
 * - :c:macro:`COMMON_CAPTURE`
 * - :c:macro:`COMMON_SE_ARC`
 * - :c:macro:`COMMON_SE_BT_SUR`
 * - :c:macro:`COMMON_WOWCAST`
 * - :c:macro:`COMMON_DAP_HP_BT`
 * - :c:macro:`COMMON_LINE_OUT`
 * - :c:macro:`COMMON_DAFC`
 *
 * @endrst
 *
 */
typedef int common_output_ext_type_t;

#define COMMON_NO_OUTPUT 0x0000 /**< it means no soundout resource */
#define COMMON_SPK 0x0001       /**< it means speaker resource */
#define COMMON_OPTIC 0x0002     /**< it means spdif resource */
#define COMMON_OPTIC_LG 0x0004  /**< it means LG spdif resource */
#define COMMON_BLUETOOTH 0x0008 /**< it means capture device works for BT */
#define COMMON_HP 0x0010        /**< it means headphone resource */
#define COMMON_ARC 0x0020       /**< it means audio return channel resource */
#define COMMON_WISA 0x0040      /**< @rst \
                                     | it means audio return channel resource  \
                                     | if chip does not support wisa, it should be works as COMMON_OPTIC(PCM) \
                                     | And capture device works for WISA. \
                                     @endrst */
#define COMMON_SE_BT                                                           \
    0x0080 /**< it means se_bt resources. And capture device works for SE_BT */
#define COMMON_CAPTURE                                                         \
    0x0100 /**< it means capture device works for Mobile Device */
#define COMMON_SE_ARC                                                          \
    0x0200 /**< it means se_arc resource where sound passes through sound engine to arc */
#define COMMON_SE_BT_SUR                                                       \
    0x0400 /**< it means se_bt_sur resources. And capture device works for SE_BT_SUR */
#define COMMON_WOWCAST                                                       \
    0x0800 /**< it means wowcast resources. */
#define COMMON_DAP_HP_BT                                                     \
    0x1000 /**< it means DAP output, this output uses DAP headphone parameter for use Bluetooth or headphone */
#define COMMON_LINE_OUT                                                      \
    0x2000 /**< it means line out resource */
#define COMMON_DAFC                                                      \
    0x4000 /**< it means DAFC output */
#define COMMON_DAP_BT                                                                \
    0x8000 /**< it means DAP output, this output uses DAP TV Atmos parameter for use \
              Bluetooth Speaker output */
#define COMMON_MAX_OUTPUT 0x10000 /**< it means max soundout resource */

/**
 * @brief input type for soundout
 */
typedef enum common_input_ext_type {
    COMMON_NO_INPUT     = 0x0000,
    COMMON_INPUT_ADEC   = 0x0001, /**< Input is Adec */
    COMMON_INPUT_AMIXER = 0x0010, /**< Input is Amixer */
} common_input_ext_type_t;


/**
 * @brief sndout capture path
 */
typedef enum sndout_capture_path {
    SNDOUT_CAPTURE_PATH_DEFAULT     = 0, /**< Set capture path to default (for normal use setting like BT and WISA) */
    SNDOUT_CAPTURE_PATH_ADEC0       = 1, /**< Capture path point between ADEC0 and Mixer */
    SNDOUT_CAPTURE_PATH_ADEC1       = 2, /**< Capture path point between ADEC0 and Mixer */
    SNDOUT_CAPTURE_PATH_MIXER       = 3, /**< Capture path point between Mixer and SE (Sound Engine) */
    SNDOUT_CAPTURE_PATH_OUT_SPK     = 4, /**< Capture path point to COMMON_SPK (after SE) */
    SNDOUT_CAPTURE_PATH_OUT_OPTICAL = 5, /**< Capture path to COMMON_OPTIC */
    SNDOUT_CAPTURE_PATH_OUT_ARC     = 6, /**< Capture path to COMMON_ARC */
    SNDOUT_CAPTURE_PATH_OUT_HP      = 7, /**< Capture path to COMMON_HP */
    SNDOUT_CAPTURE_PATH_OUT_WOWCAST = 8, /**< Capture path to COMMON_WOWCAST */
    SNDOUT_CAPTURE_PATH_OUT_DAFC    = 9, /**< Capture path to COMMON_DAFC */
} sndout_capture_path_t;

#endif
