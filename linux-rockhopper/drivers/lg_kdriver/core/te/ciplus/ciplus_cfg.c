/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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

/** @file
 *
 *  main configuration file for ciplus device
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	0.1
 *  @date		2015-07-07
 *  @note		Additional information.
 */

#include "os_util.h"
#include "ciplus_impl.h"

static struct ciplus_config config_normal = {
	.num_dev	= 1,
	.num_ch		= 3,
	.num_pidf	= 32,

	.use_cinport	= 1,
	.use_pktcnt	= 1,
};

static struct ciplus_config *cfg;

void ciplus_cfg_init(void)
{
	// M16P3 ~
	cfg = &config_normal;
}

/**
********************************************************************************
* @brief
*	Get conf which is fit to chip revision
* @remarks
*  DETAIL INFORMATION
* @par requirements:
*
* @param
*
* @return
*  struct ciplus_config* : pointer of config structure
********************************************************************************
*/
struct ciplus_config *ciplus_get_config(void)
{
	return cfg;
}

/** @} */
