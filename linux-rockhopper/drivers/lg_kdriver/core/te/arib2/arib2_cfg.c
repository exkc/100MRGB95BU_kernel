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
 *  main configuration file for arib2 device
 *	arib2 device will teach you how to make device driver with new platform.
 *
 *  author		yeonju.lee
 *  version		1.0
 *  date		2017.11.21
 *  note		Additional information.
 *
 *	@{
 */

#include "os_util.h"
#include "arib2_impl.h"

static struct arib2_config config_normal = {
	.num_ch = 4,
	.num_tlvf = 32,
	.num_ipf = 3,
	.num_mmt_pidf = 32,
	.num_mmt_sif = 64,
	.num_mmt_avf = 32,
};

static struct arib2_config *config;

void arib2_cfg_init(void)
{
	// O20 ~
	config = &config_normal;
}

struct arib2_config *arib2_get_config(void)
{
	return config;
}

/** @} */
