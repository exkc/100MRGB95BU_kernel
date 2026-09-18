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

/** @defgroup se
  * @{
  *
  * @brief
  * Sound engine module for audio kernel driver
  *
  * @details
  *
  * @}
  */

/** @file
 * @ingroup se
 *
 * @brief
 * Sound engine module API header for audio kernel driver
 *
 * @author      Youngwoo Jin ( youngwoo.jin@lge.com )
 * @version     1.0
 * @date        2020.06.30
 *
 */

#ifndef _SE_H_
#define _SE_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
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

/**
 * @brief
 * Handler of se block
 *
 * @details
 * SE block 사용을 위한 hanlder
 */
typedef struct aud_block_info* se_handle_t;

/**
 * @brief
 * parameter info struct
 *
 * @details
 * SE parameters information
 */
struct se_param_info
{
    const char *name;
    unsigned int unit_size;
    int min_value;
    int max_value;
    int order;
    unsigned int size;
};

/**
 * @brief
 * parameter struct
 *
 * @details
 * SE parameters structure
 */
struct se_param
{
    unsigned int index;
    unsigned int size;
    unsigned char *data;
};

/**
 * @brief
 * mode information
 *
 * @details
 * SE mode information
 */
struct se_mode_info
{
    const char *name;
    int port;
    bool upmix;
};

/**
 * @brief
 * type of callback function
 *
 * @details
 * SE callback function
 */
typedef int (*se_callback_func) (void *param);

// LGSE LL cmd
enum {
    LL_CMD_SET_PARAM,
    LL_CMD_GET_PARAM,
    LL_CMD_GET_BRIGHTNESS,
    LL_CMD_GET_LIGHT_FREQ,
    LL_CMD_GET_VERSION,
    LL_CMD_START,
    LL_CMD_STOP,
    LL_CMD_MAX,
};


/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/**
 * @brief
 * Initialize SE block
 *
 * @details
 * SE block 을 초기화
 *
 * @param void
 * @return void
 * @see
 */
void se_initializer (void);

/**
 * @brief
 * Set callback function
 *
 * @details
 * sound endigne 에서 사용할 callback function 설정
 *
 * @param[in] se sound engine handler
 * @param[in] func callback function pointer
 * @param[in] param callback parameter
 * @return result of function call
 * @see
 */
int se_set_callback (se_handle_t se, se_callback_func cb_func, void *cb_param);

int se_make_func_list (void);

/**
 * @brief
 * Get se parameter list
 *
 * @details
 * Paramter 목록을 획득
 *
 * @param[in] name type name
 * @param[out] list pointer of list of parameters
 * @return number of parameters
 * @see
 */
int se_get_parameter_list (struct se_param_info **list);

/**
 * @brief
 * Get sound engine parameter
 *
 * @details
 * 해당 sound endigne 의 parameter 획득
 * Call 이전에 parameter 가 set 되지 않았더라도
 * valid parameter size 를 얻을 수 있음
 *
 * @param[in] se sound engine handler
 * @param[out] param parameters
 * @return result of function call
 * @see
 */
int se_get_param (se_handle_t se, struct se_param *param);

/**
 * @brief
 * Set sound engine parameter
 *
 * @details
 * 해당 sound endigne 의 parameter 설정
 *
 * @param[in] se sound engine handler
 * @param[in] param parameter
 * @return result of function call
 * @see
 */
int se_set_param (se_handle_t se, struct se_param *param);

/**
 * @brief
 * Set mode of sound engine
 *
 * @details
 * 해당 sound endigne mode 설정
 *
 * @param[in] se sound engine handler
 * @param[in] mode_info mode information
 * @return result of function call
 * @see
 */
int se_set_mode (se_handle_t se, struct se_mode_info *mode_info, char *type_name);

/**
 * @brief
 * Set number of output channels for alsa se module
 *
 * @details
 * 해당 sound endigne 의 output channel 수 설정
 *
 * @param[in] se sound engine handler
 * @param[in] number number of output channels
 * @return result of function call
 * @see
 */
int se_set_number_of_output_channels (se_handle_t se, unsigned int number);
#ifdef SUPPORT_SOUNDBAR
int se_set_output_freq (se_handle_t se, unsigned int freq);
#endif
int se_set_dap_output_device (se_handle_t se, unsigned int output_device);

int lgse_ll_get_param (struct aud_block_info *block, int cmd, int size, unsigned int *data);
int lgse_ll_set_param (struct aud_block_info *block, int cmd, int size, unsigned int *data);

#ifdef SUPPORT_DAFC
/**
 * @brief
 * Notify status dconf, sconf file and setting files
 *
 * @details
 * dafc config files들의 상태 및 설정을 위한 command를 내림
 *
 * @param[in] kcontrol->id.index (file status)
 * @param[in] dconf file path
 * @param[in] sconf file path
 * @return result of function call
 * @see
 */
int se_set_dafc_conf (se_handle_t se, const char* dconf_path, const char* sconf_path);
int se_set_dafc_center_extract_status (se_handle_t se, unsigned int status);
int se_set_dafc_by_handle (se_handle_t se, bool onoff);
#endif /* end of SUPPORT_DAFC */
#endif /* _SE_H_ */
