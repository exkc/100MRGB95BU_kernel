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
 *  @version	1.2
 *  @date	2025-07-07
 *  @note	Additional information.
 */

#include <linux/types.h>
#include <linux/module.h>
#include <lg1k/te/util.h>
#include "te_impl.h"
#include "ion_spi.h"
#include "ion_ci_reg.h"
#include "ion_io_reg.h"
#include <lg1k/te/ion.h>
#include "ion_debug.h"

//#define CG_ON_INIT

//TODO: move to ion_ci_reg if the clock is changed
#define SPI_CLK SPI_ION_DEFAULT_CLK

#define SMC_WRITE_LEN 7
#define SMC_READ_LEN 8
#define SMC_ACCESS_SIZE 4
#define SMC_READ_OFFSET (SMC_READ_LEN - SMC_ACCESS_SIZE)

#define CIREG_WRITE_LEN 5
#define CIREG_READ_LEN 7
#define CIREG_ACCESS_SIZE 2
#define CIREG_READ_OFFSET (CIREG_READ_LEN - CIREG_ACCESS_SIZE)

#define CAM_ATTR_WRITE_LEN 9
#define CAM_ATTR_READ_LEN 13
#define CAM_ATTR_ACCESS_SIZE 1
#define CAM_ATTR_READ_OFFSET (CAM_ATTR_READ_LEN - CAM_ATTR_ACCESS_SIZE)

#define CAM_IO_WRITE_LEN 9 //follow io only mode
#define CAM_IO_READ_LEN 9
#define CAM_IO_ACCESS_SIZE 1
#define CAM_IO_READ_OFFSET (CAM_IO_READ_LEN - CAM_IO_ACCESS_SIZE)

#define CAM_IO_LEGACY_DUMMY_SIZE 9
#define CAM_IO_LEGACY_PACKET_SIZE (CAM_IO_LEGACY_DUMMY_SIZE + CAM_IO_ACCESS_SIZE)
#define CAM_IO_FAST_DUMMY_SIZE 5
#define CAM_IO_FAST_PACKET_SIZE (CAM_IO_FAST_DUMMY_SIZE + CAM_IO_ACCESS_SIZE)
#define CAM_IO_MAX_BURST_SIZE 15 //for IO_FAST mode consider LEGACY

// [1:0] dst_address (max 16 bits)
// [2] option
// [6:3] value for write
int ion_ci_smc_write32(struct te_device *dev, u32 val, u32 addr)
{
	u8 txbuf[SMC_WRITE_LEN] = {0, };
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	// dst_address
	txbuf[1] = addr;

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_WRITE, MODE_SMC_ACCESS, 1);

	// value
	te_put32(txbuf + 3, val);

	rc = ion_spi_send_message(ion, txbuf, SMC_WRITE_LEN, 0);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	return 0;
}

// [1:0] dst_address (max 16 bits)
// [2] option
// [3] dummy
// [7:4] value for read
int ion_ci_smc_read32(struct te_device *dev, u32 *val, u8 addr)
{
	uint8_t txbuf[SMC_READ_LEN] = {0, };
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	CHECK_ERROR(!val, return -EFAULT, "val is NULL");

	// dst_address
	txbuf[1] = addr;

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_READ, MODE_SMC_ACCESS, 1);

	rc = ion_spi_send_message(ion, txbuf, SMC_READ_LEN, SMC_READ_OFFSET);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	// value
	*val = te_get32(txbuf + SMC_READ_OFFSET);
	return 0;
}

// [1:0] dst_address (max 16 bits)
// [2] option
// [4:3] value for write
int ion_ci_cireg_write16(struct te_device *dev, u16 val, u8 addr)
{
	u8 txbuf[CIREG_WRITE_LEN] = {0, };
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	// dst_address
	txbuf[1] = addr;

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_WRITE, MODE_REG_ACCESS, 1);

	// value
	te_put16(txbuf + 3, val);

	rc = ion_spi_send_message(ion, txbuf, CIREG_WRITE_LEN, 0);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	return 0;
}

// [1:0] dst_address (max 16 bits)
// [2] option
// [4:3] dummy
// [6:5] value for read
int ion_ci_cireg_read16(struct te_device *dev, u16 *val, u8 addr)
{
	uint8_t txbuf[CIREG_READ_LEN] = {0, };
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	CHECK_ERROR(!val, return -EFAULT, "val is NULL");

	// dst_address
	txbuf[1] = addr;

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_READ, MODE_REG_ACCESS, 1);

	rc = ion_spi_send_message(ion, txbuf, CIREG_READ_LEN,
				  CIREG_READ_OFFSET);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	// value
	*val = te_get16(txbuf + CIREG_READ_OFFSET);
	return 0;
}

// [1:0] dst_address (max 16 bits)
// [2] option
// [11:3] dummy
// [12] value for read
int ion_ci_read_attribute_mem(struct te_device *dev, u8 *val, u16 addr)
{
	u8 txbuf[CAM_ATTR_READ_LEN] = {0, };
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	CHECK_ERROR(!val, return -EFAULT, "val is NULL");

	// dst_address
	te_put16(txbuf, addr);

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_READ, MODE_ATTRIBUTE_MEM, 1);

	rc = ion_spi_send_message(ion, txbuf, CAM_ATTR_READ_LEN,
				  CAM_ATTR_READ_OFFSET);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	*val = txbuf[CAM_ATTR_READ_OFFSET];
	return 0;
}

// [1:0] dst_address (max 16 bits)
// [2] option
// [3] value for write
// [8:4] dummy
int ion_ci_write_attribute_mem(struct te_device *dev, u8 val, u16 addr)
{
	u8 txbuf[CAM_ATTR_WRITE_LEN] = {0, };
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	// dst_address
	te_put16(txbuf, addr);

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_WRITE, MODE_ATTRIBUTE_MEM, 1);

	// value
	txbuf[3] = val;

	rc = ion_spi_send_message(ion, txbuf, CAM_ATTR_WRITE_LEN, 0);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	return 0;
}

// [1:0] dst_address (max 16 bits)
// [2] option
// [7:3] dummy
// [8] value for read
int ion_ci_read_cam_control(struct te_device *dev, u8 *val, u8 addr)
{
	u8 txbuf[CAM_IO_READ_LEN] = {0, };
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	CHECK_ERROR(!val, return -EFAULT, "val is NULL");

	// dst_address
	txbuf[1] = addr;

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_READ, MODE_IO_FAST, 1);

	rc = ion_spi_send_message(ion, txbuf, CAM_IO_READ_LEN,
				  CAM_IO_READ_OFFSET);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	*val = txbuf[CAM_IO_READ_OFFSET];
	return 0;
}

// [1:0] dst_address (max 16 bits)
// [2] option
// [3] value for write
// [8:4] dummy
int ion_ci_write_cam_control(struct te_device *dev, u8 val, u8 addr)
{
	u8 txbuf[CAM_IO_WRITE_LEN] = {0, };
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	// dst_address
	txbuf[1] = addr;

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_WRITE, MODE_IO_FAST, 1);

	// value
	txbuf[3] = val;

	rc = ion_spi_send_message(ion, txbuf, CAM_IO_WRITE_LEN, 0);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	return 0;
}

static int read_cam_control_burst(struct te_dev_ion *ion, u8 *buf, u8 len)
{
	int i, rc;
	u8 txbuf[SPI_MESSAGE_MAX_LEN] = {0, };
	u32 buflen, read_ofs;

	buflen = SPI_CMD_SIZE + len * CAM_IO_FAST_PACKET_SIZE;
	read_ofs = SPI_CMD_SIZE + CAM_IO_FAST_DUMMY_SIZE;

	txbuf[2] = ion_spi_gen_option(DIRECTION_READ, MODE_IO_FAST, len);

	rc = ion_spi_send_message(ion, txbuf, buflen, read_ofs);
	CHECK_ERROR(rc < 0, return rc, "read failed len:%u %d", len, rc);

	for (i = 0; i < len; i++) {
		buf[i] = txbuf[read_ofs + i * CAM_IO_FAST_PACKET_SIZE];
	}

	return 0;
}

static int write_cam_control_burst(struct te_dev_ion *ion, u8 *buf, u8 len)
{
	int i, rc;
	u8 txbuf[SPI_MESSAGE_MAX_LEN] = {0, };
	u32 buflen, write_ofs;

	buflen = SPI_CMD_SIZE + len * CAM_IO_FAST_PACKET_SIZE;
	write_ofs = SPI_CMD_SIZE;

	txbuf[2] = ion_spi_gen_option(DIRECTION_WRITE, MODE_IO_FAST, len);

	for (i = 0; i < len; i++) {
		txbuf[write_ofs + i * CAM_IO_FAST_PACKET_SIZE] = buf[i];
	}

	rc = ion_spi_send_message(ion, txbuf, buflen, 0);
	CHECK_ERROR(rc < 0, return rc, "write failed len:%u %d", len, rc);

	return 0;
}

int ion_ci_read_io_data(struct te_device *dev, u8 *buf, u32 len)
{
	int rc = 0;
	u8 *p = buf;
	u8 l;
	struct te_dev_ion *ion = &dev->ion;

	while (len) {
		if (len >= CAM_IO_MAX_BURST_SIZE)
			l = CAM_IO_MAX_BURST_SIZE;
		else
			l = len;

		rc = read_cam_control_burst(ion, p, l);
		if (rc) {
			log_error("error @%ld", p - buf);
			return rc;
		}

		p += l;
		len -= l;
	}

	return 0;
}

int ion_ci_write_io_data(struct te_device *dev, u8 *buf, u32 len)
{
	int rc = 0;
	u8 *p = buf;
	u8 l;
	struct te_dev_ion *ion = &dev->ion;

	while (len) {
		if (len >= CAM_IO_MAX_BURST_SIZE)
			l = CAM_IO_MAX_BURST_SIZE;
		else
			l = len;

		rc = write_cam_control_burst(ion, p, l);
		if (rc) {
			log_error("error @%ld", p - buf);
			return rc;
		}

		p += l;
		len -= l;
	}

	return 0;
}

int ion_io_write32(struct te_device *dev, u8 ch, u32 val, u32 addr)
{
	return ion_io_reg_write(&dev->ion, ch, val, addr);
}

int ion_io_read32(struct te_device *dev, u8 ch, u32 *val, u32 addr)
{
	return ion_io_reg_read(&dev->ion, ch, val, addr);
}

static int set_tpi_enable(struct te_dev_ion *ion, u8 ext_num, bool en)
{
	int i, rc;

	for (i = 0; i < TE_ION_CH_NUM; i++) {
		rc = ion_io_reg_set_clock_gate(ion, i, ext_num, !en);
		if (rc < 0) {
			log_error("error in set_clock_gate(%d:%u:%s)", i,
				  ext_num, (en) ? "true" : "false");
			return -EFAULT;
		}
	}

	return 0;
}

//NOTE: not use yet (covered by tpi type setting)
int ion_io_enable_tpi(struct te_device *dev, u8 ext_num, bool en)
{
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_tpi *tpi;
	int rc = 0;

	if (ext_num >= TE_ION_TPI_NUM)
		return -EFAULT;

	tpi = &ion->tpi[ext_num];
	mutex_lock(&tpi->tpi_lock);

	if (en == tpi->en) // nothing to do
		goto exit;

	log_noti("%s tpi:%u", (en) ? "enable" : "disable", tpi->idx);
	rc = set_tpi_enable(ion, tpi->idx, en);
	if (rc) {
		log_error("set_tpi_enable fail %d", rc);
		goto exit;
	}

	tpi->en = en;

exit:
	mutex_unlock(&tpi->tpi_lock);
	return rc;
}

int ion_io_set_tp(struct te_device *dev, u8 ext_num, bool parallel)
{
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_tpi *tpi;
	int rc = 0;

	if (ext_num >= TE_ION_TPI_NUM)
		return -EFAULT;

	tpi = &ion->tpi[ext_num];
	log_noti("tpi:%u %s", tpi->idx, parallel ? "parallel" : "serial");
	mutex_lock(&tpi->tpi_lock);

	if (tpi->en && tpi->type == ION_TPI_TS) // already set; ignore
		goto exit;

	rc = set_tpi_enable(ion, tpi->idx, true);
	if (rc)
		goto exit;

	rc = ion_io_reg_set_tp(ion, ext_num, parallel);
	if (rc)
		goto exit;

	tpi->en = true;
	tpi->type = ION_TPI_TS;
	tpi->parallel = parallel;

exit:
	mutex_unlock(&tpi->tpi_lock);
	return rc;
}

int ion_io_set_tlv(struct te_device *dev, u8 ext_num, bool parallel)
{
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_tpi *tpi;
	int rc = 0;

	if (ext_num >= TE_ION_TPI_NUM)
		return -EFAULT;

	tpi = &ion->tpi[ext_num];
	log_noti("tpi:%u %s", tpi->idx, parallel ? "parallel" : "serial");
	mutex_lock(&tpi->tpi_lock);

	if (tpi->en && tpi->type == ION_TPI_TLV) // already set; ignore
		goto exit;

	rc = set_tpi_enable(ion, tpi->idx, true);
	if (rc)
		goto exit;

	rc = ion_io_reg_set_tlv(ion, ext_num, parallel);
	if (rc)
		goto exit;

	tpi->en = true;
	tpi->type = ION_TPI_TLV;
	tpi->parallel = parallel;

exit:
	mutex_unlock(&tpi->tpi_lock);
	return rc;
}

int ion_io_set_lgc(struct te_device *dev, u8 ext_num, bool parallel)
{
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_tpi *tpi;
	int rc = 0;

	if (ext_num >= TE_ION_TPI_NUM)
		return -EFAULT;

	tpi = &ion->tpi[ext_num];
	log_noti("tpi:%u %s", tpi->idx, parallel ? "parallel" : "serial");
	mutex_lock(&tpi->tpi_lock);

	if (tpi->en && tpi->type == ION_TPI_LGC) // NOTE: currently not possible
		goto exit;

	rc = set_tpi_enable(ion, tpi->idx, true);
	if (rc)
		goto exit;

	rc = ion_io_reg_set_lgc(ion, ext_num, parallel);
	if (rc)
		goto exit;

	tpi->en = true;
	tpi->type = ION_TPI_LGC;
	tpi->parallel = parallel;

exit:
	mutex_unlock(&tpi->tpi_lock);
	return rc;
}

int ion_init_device(struct te_device *dev)
{
	int i, ret;
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_tpi *tpi;

	ret = ion_io_reg_init(ion);
	if (ret) {
		log_error("ion_io_reg_init failed %d", ret);
		return ret;
	}

	ret = ion_ci_reg_init(ion);
	if (ret) {
		log_error("ion_ci_reg_init failed %d", ret);
		ion_io_reg_release(ion);
		return ret;
	}

	mutex_init(&ion->spi_lock);

	for (i = 0; i < TE_ION_TPI_NUM; i++) {
		tpi = &ion->tpi[i];

#ifdef CG_ON_INIT
		ret = set_tpi_enable(ion, i, false);
		if (ret) {
			log_error("set_tpi_enable(disable) error %d", ret);
			ion_ci_reg_release(ion);
			ion_io_reg_release(ion);
			return ret;
		}
#endif

		mutex_init(&tpi->tpi_lock);

		tpi->en = false;
		tpi->parallel = true;
		tpi->type = ION_TPI_TS;
		tpi->idx = i;
	}

	ret = ion_debug_init(dev);
	if (ret) {
		log_error("ion_debug_init failed %d", ret);
		ion_ci_reg_release(ion);
		ion_io_reg_release(ion);
		return ret;
	}

	log_noti("init done");

	return ret;
}

void ion_release_device(struct te_device *dev)
{
	struct te_dev_ion *ion = &dev->ion;

	ion_debug_release(dev);
	ion_ci_reg_release(ion);
	ion_io_reg_release(ion);
}

int ion_ci_init(struct te_device *dev)
{
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	log_noti("ion_ci init");

	rc = ion_spi_clk_config(ion, SPI_CLK);
	CHECK_ERROR(rc < 0, , "fail @ spi_clk_config %d", rc);

	rc = ion_ci_reg_hw_init(ion);
	CHECK_ERROR(rc < 0, return rc, "fail @ ion_ci_reg_init %d", rc);

	return rc;
}

/* HW ALL Reset */
int ion_ci_reset(struct te_device *dev)
{
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	rc = ion_ci_reg_hw_reset(ion);
	if (rc) {
		log_error("error %d in ion_ci_reg_hw_reset", rc);
		return rc;
	}

	return 0;
}

int ion_ci_init_tp_checker(struct te_device *dev, u16 pkt_cnt)
{
	return ion_ci_reg_init_tp_checker(&dev->ion, pkt_cnt);
}

int ion_ci_start_tp_checker(struct te_device *dev, u16 pkt_cnt)
{
	return ion_ci_reg_start_tp_checker(&dev->ion, pkt_cnt);
}

int ion_ci_reset_tp(struct te_device *dev)
{
	int rc;
	struct te_dev_ion *ion = &dev->ion;

	rc = ion_ci_reg_reset_tp(ion);
	if (rc) {
		log_error("error %d in ion_ci_reg_reset_tp", rc);
		return rc;
	}

	return 0;
}

int ion_io_hw_init(struct te_device *dev)
{
	int i, rc = 0;
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_tpi *tpi;

	for (i = 0; i < TE_ION_TPI_NUM; i++) {
		tpi = &ion->tpi[i];

		mutex_lock(&tpi->tpi_lock);

#ifdef CG_ON_INIT
		rc = set_tpi_enable(ion, i, false);
		if (rc)
			log_error("set_tpi_enable(disable) error %d", rc);

#endif
		mutex_unlock(&tpi->tpi_lock);
	}

	return rc;
}

int ion_io_hw_suspend(struct te_device *dev)
{
	int i, rc = 0;
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_tpi *tpi;

	// clock gating for TP/TLV
	log_noti("clock gate ION TP");

	for (i = 0; i < TE_ION_TPI_NUM; i++) {
		tpi = &ion->tpi[i];

		mutex_lock(&tpi->tpi_lock);

		rc = set_tpi_enable(ion, i, false);
		if (rc)
			log_error("set_tpi_enable(disable) error %d", rc);

		mutex_unlock(&tpi->tpi_lock);
	}

	return 0;
}

int ion_io_hw_resume(struct te_device *dev)
{
	int i, rc = 0;
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_tpi *tpi;

	// recover TPI setting
	log_noti("recover ION TP settings");

	for (i = 0; i < TE_ION_TPI_NUM; i++) {
		tpi = &ion->tpi[i];

		mutex_lock(&tpi->tpi_lock);

		if (!tpi->en) { // not enabled
			mutex_unlock(&tpi->tpi_lock);
			continue;
		}
		log_noti("TPI:%d type:%d", tpi->idx, tpi->type);

		rc = set_tpi_enable(ion, i, true);
		if (rc)
			log_error("set_tpi_enable(true) error %d", rc);

		switch (tpi->type) {
		case ION_TPI_TS:
		default:
			ion_io_reg_set_tp(ion, tpi->idx, tpi->parallel);
			break;

		case ION_TPI_TLV:
			ion_io_reg_set_tlv(ion, tpi->idx, tpi->parallel);
			break;

		case ION_TPI_LGC:
			ion_io_reg_set_lgc(ion, tpi->idx, tpi->parallel);
			break;
		}

		mutex_unlock(&tpi->tpi_lock);
	}

	return 0;
}
