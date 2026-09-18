/*
 * SoC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2024 by LG Electronics Inc.
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
 *  CI SPI Interface for ION hardware
 *
 *  @author	Ilkyu Kim
 *  @version	1.1
 *  @date	2024-07-08
 *  @note	Additional information.
 */
#include <linux/spi/spi.h>
#include "spi_drv.h"
#include "ion_spi.h"
#include "te_impl.h"

static int clk_config(struct te_dev_ion *dev, u32 clk)
{
	int rc;

	if (likely(dev->spi_clk == clk))
		return 0;

	log_noti("[%u] clk %u -> %u", dev->ci_spi_ch, dev->spi_clk, clk);

	rc = spi_config(dev->ci_spi_ch, SPI_MODE_0, clk);
	if (rc < 0)
		return rc;

	dev->spi_clk = clk;
	return 0;
}

int ion_spi_clk_config(struct te_dev_ion *dev, u32 clk)
{
	int ret;

	mutex_lock(&dev->spi_lock);

	ret = clk_config(dev, clk);

	mutex_unlock(&dev->spi_lock);

	return ret;
}

int ion_spi_send_message(struct te_dev_ion *dev, u8 *buf, u32 size, u32 cmdsize)
{
	int rc;

	CHECK_ERROR(size > SPI_MESSAGE_MAX_LEN, return -EINVAL,
		    "invalid message size(%u)", size);
	CHECK_ERROR(cmdsize >= size, return -EINVAL, "cmd(%u) >= size(%u)",
		    cmdsize, size);

	mutex_lock(&dev->spi_lock);

	rc = spi_send(dev->ci_spi_ch, buf, size, cmdsize);
	if (rc < 0)
		log_error("spi_send failed %d", rc);

	mutex_unlock(&dev->spi_lock);

	return rc;
}

// [2] option
//	burst_len	: 4, // 3:0
//	rw_direction	: 1, // 4
//	access_mode	: 3, // 7:5
static u8 gen_option(enum dvbci_rw_direction direction,
		     enum dvbci_access_mode mode, u8 len)
{
	u8 option;

	if (len == 1) // lower compatibilty
		len = 0;

	option = len;
	option |= (direction & 0x1) << 4;
	option |= (mode & 0x7) << 5;

	return option;
}

u8 ion_spi_gen_option(enum dvbci_rw_direction direction,
		     enum dvbci_access_mode mode, u8 len)
{
	return gen_option(direction, mode, len);
}

