/*
 * SoC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
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
 *  dumper register access API
 *
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-02-06
 *  @note	Additional information.
 */

#include <linux/types.h>
#include "ion_io_reg_ctrl.h"
#include "ion_reg_ctrl.h"
#include "te_impl.h"
#include "ion_io_reg_slave.h"

#define ION_TP_PKT_SIZE 0xbb

int ion_io_slave_reg_write(struct te_dev_ion *dev, u32 val, u16 addr)
{
	u32 dummy; //for removing dummy value;
	u8 v[4]; //value
	u8 a[2]; //address
	int i;
	const struct te_dev_ion_ucom_func *ucom_func = dev->ucom_func;

	if (!ucom_func || !ucom_func->write || !ucom_func->read)
		return -ENODEV;

	te_put16(a, addr);
	te_put32(v, val);

	//ucom_func->write(addr, val);
	ucom_func->write(0x0050, 0x00000000);
	ucom_func->write(0xB004, 0x00000000);
	ucom_func->write(0xB000, 0x00002007);
	ucom_func->write(0xB004, 0x00000002);
	ucom_func->write(0xB010, 0x00000002);

	for (i = 0; i < 2; i++)
		ucom_func->write(0xB008, a[i]);
	ucom_func->write(0xB008, 0x000000E0);
	for (i = 0; i < 4; i++)
		ucom_func->write(0xB008, v[i]);
	for (i = 0; i < 7; i++)
		dummy = ucom_func->read(0xB008);

	ucom_func->write(0x0050, 0x00000001);

	return 0;
}

int ion_io_slave_reg_read(struct te_dev_ion *dev, u32 *val, u16 addr)
{
	u32 dummy, value;
	u8 a[2]; //address
	u8 v[4]; //value
	int i;
	const struct te_dev_ion_ucom_func *ucom_func = dev->ucom_func;

	if (!ucom_func || !ucom_func->write || !ucom_func->read)
		return -ENODEV;

	te_put16(a, addr);

	ucom_func->write(0x0050, 0x00000000);
	ucom_func->write(0xB004, 0x00000000);
	ucom_func->write(0xB000, 0x00002007);
	ucom_func->write(0xB004, 0x00000002);
	ucom_func->write(0xB010, 0x00000002);

	for (i = 0; i < 2; i++)
		ucom_func->write(0xB008, a[i]);
	ucom_func->write(0xB008, 0x000000F0);
	for (i = 0; i < 5; i++)
		ucom_func->write(0xB008, 0x00); //dummy for write
	for (i = 0; i < 4; i++)
		dummy = ucom_func->read(0xB008); //dummy for read

	for (i = 0; i < 4; i++) {
		value = ucom_func->read(0xB008);
		v[i] = (value & 0xFF);
	}

	//value
	*val = te_get32(v);

	ucom_func->write(0x0050, 0x00000001);

	return 0;
}

int ion_io_slave_set_clock_gate(struct te_dev_ion *dev, u8 idx, bool en)
{
	union {
		SCRG_ION2 scrg_ion2;
		u32 val;
	} reg;
	const u16 addr = GET_ION_SCRG_ADDR(scrg_ion2); // 0x5008
	const u8 v = (en) ? 1 : 0;

	ion_io_slave_reg_read(dev, &reg.val, addr);

	if (idx == 0) {
		reg.scrg_ion2.reg_srds_12to3_sd_rx0_clk_gate_en = v;
		reg.scrg_ion2.reg_srds_12to3_sd_tx0_clk_gate_en = v;
		reg.scrg_ion2.reg_srds_12to3_tp_rx0_clk_gate_en = v;
		reg.scrg_ion2.reg_srds_12to3_tp_tx0_clk_gate_en = v;
	} else { // idx == 1
		reg.scrg_ion2.reg_srds_12to3_sd_rx1_clk_gate_en = v;
		reg.scrg_ion2.reg_srds_12to3_sd_tx1_clk_gate_en = v;
		reg.scrg_ion2.reg_srds_12to3_tp_rx1_clk_gate_en = v;
		reg.scrg_ion2.reg_srds_12to3_tp_tx1_clk_gate_en = v;
	}

	return ion_io_slave_reg_write(dev, reg.val, addr);
}

int ion_io_slave_do_reset(struct te_dev_ion *dev, u8 idx)
{
	int rc;
	union {
		SCRG_ION3 scrg_ion3;
		u32 val;
	} reg;
	const u16 addr = GET_ION_SCRG_ADDR(scrg_ion3);

	ion_io_slave_reg_read(dev, &reg.val, addr);

	/* reset assert */
	if (idx == 0) {
		reg.scrg_ion3.reg_soft_rst_srds_12to3_sd_rx0_n = 1;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_sd_tx0_n = 1;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_tp_rx0_n = 1;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_tp_tx0_n = 1;
	} else { // idx == 1
		reg.scrg_ion3.reg_soft_rst_srds_12to3_sd_rx1_n = 1;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_sd_tx1_n = 1;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_tp_rx1_n = 1;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_tp_tx1_n = 1;
	}
	rc = ion_io_slave_reg_write(dev, reg.val, addr);
	if (rc < 0) {
		log_error("error %d in reset assert", rc);
		return rc;
	}

	/* reset de-assert */
	if (idx == 0) {
		reg.scrg_ion3.reg_soft_rst_srds_12to3_sd_rx0_n = 0;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_sd_tx0_n = 0;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_tp_rx0_n = 0;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_tp_tx0_n = 0;
	} else { // idx == 1
		reg.scrg_ion3.reg_soft_rst_srds_12to3_sd_rx1_n = 0;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_sd_tx1_n = 0;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_tp_rx1_n = 0;
		reg.scrg_ion3.reg_soft_rst_srds_12to3_tp_tx1_n = 0;
	}

	rc = ion_io_slave_reg_write(dev, reg.val, addr);
	if (rc < 0) {
		log_error("error %d in reset de-assert", rc);
		return rc;
	}

	return 0;
}

int ion_io_slave_set_mux(struct te_dev_ion *dev, u8 ext_num)
{
	union {
		SRDS12TO3_MUX mux;
		u32 val;
	} reg;
	const u16 addr = GET_SRDS12TO3_ADDR(mux);

	ion_io_slave_reg_read(dev, &reg.val, addr);

	reg.mux.reg_sel_sipo1_sd_in = 0;
	reg.mux.reg_sel_sipo0_sd_in = 0;

	reg.mux.reg_sel_piso0_sd_out = 0;
	reg.mux.reg_sel_piso1_sd_out = 0;
	if (ext_num == 0)
		reg.mux.reg_sel_sipo0_tp_out = 1;
	else
		reg.mux.reg_sel_sipo1_tp_out = 1;

	reg.mux.reg_sel_piso1_tp_in = 0;
	reg.mux.reg_sel_piso0_tp_in = 0;

	return ion_io_slave_reg_write(dev, reg.val, addr);
}

int ion_io_slave_set_ptg_cfg(struct te_dev_ion *dev)
{
	union {
		SRDS12TO3_PTG_CFG ptg_cfg;
		u32 val;
	} reg;
	const u16 addr = GET_SRDS12TO3_ADDR(ptg_cfg);

	reg.val = 0; // all clear
	reg.ptg_cfg.reg_chk1_mode = 0;
	reg.ptg_cfg.reg_chk1_en = 0;
	reg.ptg_cfg.reg_chk0_mode = 0;
	reg.ptg_cfg.reg_chk0_en = 0;
	reg.ptg_cfg.reg_ptg1_en = 0;
	reg.ptg_cfg.reg_ptg0_en = 0;
	reg.ptg_cfg.result_valid1 = 0;
	reg.ptg_cfg.result_valid0 = 0;

	return ion_io_slave_reg_write(dev, reg.val, addr);
}

int ion_io_slave_set_ptg_pkt0(struct te_dev_ion *dev)
{
	union {
		SRDS12TO3_PTG_PKT0 ptg_pkt0;
		u32 val;
	} reg;
	const u16 addr = GET_SRDS12TO3_ADDR(ptg_pkt0);

	reg.val = 0; //all clear
	reg.ptg_pkt0.reg_tp_pkt_size = ION_TP_PKT_SIZE;

	return ion_io_slave_reg_write(dev, reg.val, addr);
}

int ion_io_slave_set_align_cfg(struct te_dev_ion *dev, u8 ext_num,
			       enum ion_io_type type, bool parallel)
{
	union {
		SRDS12TO3_ALIGN_CFG0 align_cfg0;
		u32 val;
	} reg;
	const u16 addr = GET_SRDS12TO3_ADDR(align_cfg0);

	ion_io_slave_reg_read(dev, &reg.val, addr);
	if (ext_num == 0) {
		reg.align_cfg0.reg_idle_init_time0 = ION_TP_PKT_SIZE;
		reg.align_cfg0.reg_idle_init_en0 = 0;
		reg.align_cfg0.reg_delete_sop0 = 0;
		reg.align_cfg0.reg_invert_valid0 = 0;
		reg.align_cfg0.reg_fifo0_bypass = 1;
		reg.align_cfg0.reg_piso0_gate_en = 0;
		if (type == ION_IO_TYPE_TS) {
			reg.align_cfg0.reg_check_sop0 = 0;
		} else { // ION_IO_TYPE_TLV
			reg.align_cfg0.reg_check_sop0 = 1;
		}
		if (parallel == true) {
			reg.align_cfg0.reg_mode_sipo0 = 0;
			reg.align_cfg0.reg_mode_piso0 = 0;
		} else {
			reg.align_cfg0.reg_mode_sipo0 = 1;
			reg.align_cfg0.reg_mode_piso0 = 1;
		}
	} else {
		reg.align_cfg0.reg_idle_init_time1 = ION_TP_PKT_SIZE;
		reg.align_cfg0.reg_idle_init_en1 = 0;
		reg.align_cfg0.reg_delete_sop1 = 0;
		reg.align_cfg0.reg_invert_valid1 = 0;
		reg.align_cfg0.reg_fifo1_bypass = 1;
		reg.align_cfg0.reg_piso1_gate_en = 0;
		if (type == ION_IO_TYPE_TS) {
			reg.align_cfg0.reg_check_sop1 = 0;
		} else { // ION_IO_TYPE_TLV
			reg.align_cfg0.reg_check_sop1 = 1;
		}
		if (parallel == true) {
			reg.align_cfg0.reg_mode_sipo1 = 0;
			reg.align_cfg0.reg_mode_piso1 = 0;
		} else {
			reg.align_cfg0.reg_mode_sipo1 = 1;
			reg.align_cfg0.reg_mode_piso1 = 1;
		}
	}

	return ion_io_slave_reg_write(dev, reg.val, addr);
}

int ion_io_slave_set_start_code(struct te_dev_ion *dev, u8 ext_num,
				enum ion_io_type type)
{
	const u8 code = (type == ION_IO_TYPE_TS) ? 0x47 : 0x7F;
	union {
		SRDS12TO3_START_CODE start_code;
		SRDS12TO3_ST_CODE23_EN st_code23_en;
		u32 val;
	} reg;
	u16 addr;
	int rc;

	addr = GET_SRDS12TO3_ADDR(start_code);
	ion_io_slave_reg_read(dev, &reg.val, addr);

	if (ext_num == 0)
		reg.start_code.reg_start_code0_ext0 = code;
	else
		reg.start_code.reg_start_code0_ext1 = code;

	rc = ion_io_slave_reg_write(dev, reg.val, addr);
	if (rc < 0) {
		log_error("error %d in start_code", rc);
		return rc;
	}

	addr = GET_SRDS12TO3_ADDR(st_code23_en);
	ion_io_slave_reg_read(dev, &reg.val, addr);

	if (ext_num == 0) {
		reg.st_code23_en.reg_tlv_en_ext0 =
			(type == ION_IO_TYPE_TLV) ? 1 : 0;
		reg.st_code23_en.reg_st_code2_en_ext0 = 0;
		reg.st_code23_en.reg_st_code3_en_ext0 = 0;
	} else {
		reg.st_code23_en.reg_tlv_en_ext1 =
			(type == ION_IO_TYPE_TLV) ? 1 : 0;
		reg.st_code23_en.reg_st_code2_en_ext1 = 0;
		reg.st_code23_en.reg_st_code3_en_ext1 = 0;
	}

	rc = ion_io_slave_reg_write(dev, reg.val, addr);
	if (rc < 0) {
		log_error("error %d in st_code23_en", rc);
		return rc;
	}

	return 0;
}
