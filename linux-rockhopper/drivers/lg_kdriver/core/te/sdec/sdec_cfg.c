/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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
 *
 *  @author	Jihoon Lee
 *  @author	Jinhwan Bae
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#include "os_util.h"
#include "sdec_impl.h"

// *INDENT-OFF*
/* M16++, O18 */
static struct sdec_channel_info channel_info_normal[] = {
	[0] = {
		.num_pidf	= 64,	//* # of pid filter */
		.num_secf	= 64,	//* # of section filter */
	},
	[1] = {
		.num_pidf	= 64,	//* # of pid filter */
		.num_secf	= 64,	//* # of section filter */
	},
	[2] = {
		.num_pidf	= 64,	//* # of pid filter */
		.num_secf	= 64,	//* # of section filter */
	},
	[3] = {
		.num_pidf	= 64,	//* # of pid filter */
		.num_secf	= 64,	//* # of section filter */
	},
	/* sub channel*/
	[4] = {
		.num_pidf	= 1,	//* # of pid filter */
		.num_secf	= 1,	//* # of section filter */
		.is_sub_channel = 1,
		.sub_ch_num	= 0,
	},
	[5] = {
		.num_pidf	= 1,	//* # of pid filter */
		.num_secf	= 1,	//* # of section filter */
		.is_sub_channel = 1,
		.sub_ch_num	= 1,
	},
};
// *INDENT-ON*

static struct sdec_config config_normal = {
	.num_channel		= 6,
	.num_sub_channel	= 2,
	.num_vdec_out		= 2,
	.num_adec_out		= 2,
	.num_pid_filter		= 256,
	.num_stream_filter	= 256,
	.num_temi_filter	= 16,
	.fixup_pcr_latch_bug	= false,

	.input_dump_channel	= 4,
	.default_dump_clk	= LX_SDEC_DUMP_TIMESRC_GSTCC1,

	.ch_info		= channel_info_normal,
};

static struct sdec_config *config;

/*========================================================================================
	Implementation Group
========================================================================================*/

void sdec_cfg_init(void)
{
	// M16P3 ~
	config = &config_normal;

	switch (lx_chip()) {
	case LX_CHIP_E60:
	case LX_CHIP_O20:
		config_normal.fixup_pcr_latch_bug = true;
		break;

#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
#endif
	case LX_CHIP_O22:
	default:
		break;
	}
}

struct sdec_config *sdec_get_config(void)
{
	return config;
}

/** @} */
