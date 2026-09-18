/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @defgroup alsa_se
  * @{
  *
  * @brief
  * Sound engine module for ALSA
  *
  * @details
  *
  * @}
  */

/** @file
 * @ingroup alsa_se
 *
 * @brief
 * Sound engine module API header for ALSA
 *
 * @author      Youngwoo Jin ( youngwoo.jin@lge.com )
 * @version     1.0
 * @date        2020.09.04
 *
 */

#ifndef _ALSA_SE_H_
#define _ALSA_SE_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <sound/soc.h>

#include "block.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
typedef struct _alsa_se_info* alsa_se_handle_t;

enum alse_se_mode {
    ALSA_SE_MODE_INVALID,
    ALSA_SE_MODE_LGSE_ONLY,
    ALSA_SE_MODE_LGSE_ATMOS,
    ALSA_SE_MODE_LGSE_AISOUND_GEN1,
    ALSA_SE_MODE_LGSE_AISOUND_GEN2,
    ALSA_SE_MODE_LGSE_AISOUND_GEN1_GEN2,
    ALSA_SE_MODE_LGSE_AISOUND_BYPASS,
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/**
 * @brief
 * Destroy alsa se module
 *
 * @details
 * 지정된 alsa se module 을 파괴
 *
 * @param[in] handle alsa se module handle
 * @return result of function call
 * @see
 */
int alsa_se_destroy (alsa_se_handle_t handle);

/**
 * @brief
 * Set type for alsa se module
 *
 * @details
 * alsa se module 의 동작 type 변경
 *
 * @param[in] handle alsa se module handle
 * @param[in] name name of type
 * @return result of function call
 * @see
 */
int alsa_se_set_type (alsa_se_handle_t handle, const char *name);

/**
 * @brief
 * Set number of output channels for alsa se module
 *
 * @details
 * alsa se module 의 output channel 수 설정
 *
 * @param[in] handle alsa se module handle
 * @param[in] number number of output channels
 * @return result of function call
 * @see
 */
int alsa_se_set_number_of_output_channels (alsa_se_handle_t handle, unsigned int number);

#ifdef SUPPORT_SOUNDBAR
/**
 * @brief
 * Set output frequency for alsa se module
 *
 * @details
 * alsa se module 의 output frequency 설정
 *
 * @param[in] handle alsa se module handle
 * @param[in] output frequency
 * @return result of function call
 * @see
 */
int alsa_se_set_output_freq (alsa_se_handle_t handle, unsigned int freq);
#endif

/**
 * @brief
 * Get handle of alsa se module
 *
 * @details
 * 주어진 이름의 alsa se module hanle
 *
 * @param[in] name alsa se module name
 * @return handle of alsa se module
 * @see
 */
alsa_se_handle_t alsa_se_get_handle (const char *name);

/**
 * @brief
 * Get block info for specific output
 *
 * @details
 * 지정된 output 장치의 SE block info 를 획득
 *
 * @param[in] handle alsa se module handle
 * @return pointer of block info
 * @see
 */
struct aud_block_info* alsa_se_get_block (alsa_se_handle_t handle);

/**
 * @brief
 * Get se mode for specific output
 *
 * @details
 * 지정된 output 장치의 SE mode 를 획득
 *
 * @param[in] handle alsa se module handle
 * @return mode of se
 * @see
 */
enum alse_se_mode alsa_se_get_mode (alsa_se_handle_t handle);

/**
 * @brief
 * Set connect for alsa se module between se and output
 *
 * @details
 * alsa se의 pipeline 연결
 *
 * @param[in] handle alsa se module handle
 * @return result of function call
 * @see
 */
int alsa_se_connect_pipeline (alsa_se_handle_t handle);

int register_se_kcontrols (struct snd_soc_card *card);
#endif /* _ALSA_SE_H_ */
