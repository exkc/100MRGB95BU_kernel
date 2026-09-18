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
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-03-31
 *  @note	Additional information.
 */

#include <linux/types.h>
#include <lg1k/te/util.h>
#include "ion_ci_reg_ctrl.h"
#include "ion_reg_ctrl.h"
#include "te_impl.h"
#include "ion_spi.h"
#include "ion_ci_reg_slave.h"

#define ION_WRITE_LEN 7
#define ION_READ_LEN 8
#define ION_ACCESS_SIZE 4
#define ION_READ_OFFSET (ION_READ_LEN - ION_ACCESS_SIZE)

static int ion_write(struct te_dev_ion *dev, u8 ch, u32 val, u16 addr)
{
	u8 txbuf[ION_WRITE_LEN] = {
		0,
	};
	int rc;

	log_debug("ch:%d val:0x%08x addr:0x%04x", ch, val, addr);

	// dst_address
	te_put16(txbuf, addr);

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_WRITE, MODE_ION_REG, 1);

	// value
	te_put32(txbuf + 3, val);

	rc = ion_spi_send_message(dev, txbuf, ION_WRITE_LEN, 0);
	CHECK_ERROR(rc < 0, return rc, "fail ch%u addr:%04x %d", ch, addr, rc);

	return 0;
}

static int ion_read(struct te_dev_ion *dev, u8 ch, u32 *val, u16 addr)
{
	u8 txbuf[ION_READ_LEN] = {
		0,
	};
	int rc;

	CHECK_ERROR(!val, return -EFAULT, "val is NULL");

	// dst_address
	te_put16(txbuf, addr);

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_READ, MODE_ION_REG, 1);

	rc = ion_spi_send_message(dev, txbuf, ION_READ_LEN, ION_READ_OFFSET);
	CHECK_ERROR(rc < 0, return rc, "fail addr:%02x %d", addr, rc);

	// value
	*val = te_get32(txbuf + ION_READ_OFFSET);

	log_debug("ch:%d val:0x%04x addr:0x%02x", ch, *val, addr);
	return 0;
}

int ion_ci_slave_reg_write(struct te_dev_ion *dev, u32 val, u16 addr)
{
	u32 dummy; //for removing dummy value;
	u8 v[4]; //value
	u8 a[2]; //address
	int i;

	te_put16(a, addr);
	te_put32(v, val);

	ion_write(dev, 0, 0x00000000, 0x0050);
	ion_write(dev, 0, 0x00000000, 0xB004);
	ion_write(dev, 0, 0x00002007, 0xB000);
	ion_write(dev, 0, 0x00000002, 0xB004);
	ion_write(dev, 0, 0x00000002, 0xB010);

	for (i = 0; i < 2; i++)
		ion_write(dev, 0, a[i], 0xB008);
	ion_write(dev, 0, 0xE0, 0xB008);
	for (i = 0; i < 4; i++)
		ion_write(dev, 0, v[i], 0xB008);
	for (i = 0; i < 7; i++)
		ion_read(dev, 0, &dummy, 0xB008);

	ion_write(dev, 0, 0x00000001, 0x0050);

	return 0;
}

int ion_ci_slave_reg_read(struct te_dev_ion *dev, u32 *val, u16 addr)
{
	u32 dummy, value;
	u8 a[2]; //address
	u8 v[4]; //value
	int i;

	te_put16(a, addr);

	ion_write(dev, 0, 0x00000000, 0x0050);
	ion_write(dev, 0, 0x00000000, 0xB004);
	ion_write(dev, 0, 0x00002007, 0xB000);
	ion_write(dev, 0, 0x00000002, 0xB004);
	ion_write(dev, 0, 0x00000002, 0xB010);

	for (i = 0; i < 2; i++)
		ion_write(dev, 0, a[i], 0xB008);
	ion_write(dev, 0, 0xF0, 0xB008);
	for (i = 0; i < 5; i++)
		ion_write(dev, 0, 0x00, 0xB008); //dummy for write
	for (i = 0; i < 4; i++)
		ion_read(dev, 0, &dummy, 0xB008); //dummy for read
	for (i = 0; i < 4; i++) {
		ion_read(dev, 0, &value, 0xB008);
		v[i] = (value & 0xFF);
	}

	//value
	*val = te_get32(v);

	ion_write(dev, 0, 0x00000001, 0x0050);

	return 0;
}

void ion_ci_slave_ctop_init(struct te_dev_ion *dev)
{
	union {
		CRG_CTRL_1 crg_ctrl_1;
		u32 val;
	} reg;
	u16 addr;

	// 0x0000000f, 0x0020
	addr = GET_CTOP_ADDR(crg_ctrl_1);
	reg.val = 0;
	reg.crg_ctrl_1.reg_i_sel_tu_io_sd07 = 1;
	reg.crg_ctrl_1.reg_c_sel_tu_io_sd07 = 1;
	reg.crg_ctrl_1.reg_i_sel_tu_io_sd06 = 1;
	reg.crg_ctrl_1.reg_c_sel_tu_io_sd06 = 1;

	ion_ci_slave_reg_write(dev, reg.val, addr);
}

void ion_ci_slave_iomux_ctrl_init(struct te_dev_ion *dev)
{
	union {
		PAD_ION_00 pad_ion_00; // IOMUX
		PAD_ION_01 pad_ion_01;
		PAD_ION_02 pad_ion_02;
		PAD_ION_03 pad_ion_03;
		PAD_ION_04 pad_ion_04;
		PAD_ION_05 pad_ion_05;
		PAD_ION_06 pad_ion_06;
		PAD_ION_07 pad_ion_07;
		PAD_ION_08 pad_ion_08;
		PAD_ION_09 pad_ion_09;
		PAD_ION_10 pad_ion_10;
		PAD_ION_11 pad_ion_11;
		PAD_ION_16 pad_ion_16;
		PAD_ION_17 pad_ion_17;
		u32 val;
	} reg;
	u16 addr;

	// 0x44444444, 0x8000
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_00);
	reg.val = 0;
	reg.pad_ion_00.reg_pad_gpio07_mux_sel = 4;
	reg.pad_ion_00.reg_pad_gpio05_mux_sel = 4;
	reg.pad_ion_00.reg_pad_gpio04_mux_sel = 4;
	reg.pad_ion_00.reg_pad_gpio03_mux_sel = 4;
	reg.pad_ion_00.reg_pad_gpio02_mux_sel = 4;
	reg.pad_ion_00.reg_pad_gpio01_mux_sel = 4;
	reg.pad_ion_00.reg_pad_gpio00_mux_sel = 4;
	reg.pad_ion_00.reg_pad_cicam_clk_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44444444, 0x8004
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_01);
	reg.val = 0;
	reg.pad_ion_01.reg_pad_hdmi_1_scl_mux_sel = 4;
	reg.pad_ion_01.reg_pad_hdmi_1_hpd_mux_sel = 4;
	reg.pad_ion_01.reg_pad_hdmi_det1_mux_sel = 4;
	reg.pad_ion_01.reg_pad_hdmi_1_5v_in_mux_sel = 4;
	reg.pad_ion_01.reg_pad_gpio11_mux_sel = 4;
	reg.pad_ion_01.reg_pad_gpio10_mux_sel = 4;
	reg.pad_ion_01.reg_pad_gpio09_mux_sel = 4;
	reg.pad_ion_01.reg_pad_gpio08_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44444444, 0x8008
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_02);
	reg.val = 0;
	reg.pad_ion_02.reg_pad_hdmi_det3_mux_sel = 4;
	reg.pad_ion_02.reg_pad_hdmi_3_5v_in_mux_sel = 4;
	reg.pad_ion_02.reg_pad_hdmi_2_sda_mux_sel = 4;
	reg.pad_ion_02.reg_pad_hdmi_2_scl_mux_sel = 4;
	reg.pad_ion_02.reg_pad_hdmi_2_hpd_mux_sel = 4;
	reg.pad_ion_02.reg_pad_hdmi_det2_mux_sel = 4;
	reg.pad_ion_02.reg_pad_hdmi_2_5v_in_mux_sel = 4;
	reg.pad_ion_02.reg_pad_hdmi_1_sda_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44444444, 0x800c
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_03);
	reg.val = 0;
	reg.pad_ion_03.reg_pad_hdmi_4_sda_mux_sel = 4;
	reg.pad_ion_03.reg_pad_hdmi_4_scl_mux_sel = 4;
	reg.pad_ion_03.reg_pad_hdmi_4_hpd_mux_sel = 4;
	reg.pad_ion_03.reg_pad_hdmi_det4_mux_sel = 4;
	reg.pad_ion_03.reg_pad_hdmi_4_5v_in_mux_sel = 4;
	reg.pad_ion_03.reg_pad_hdmi_3_sda_mux_sel = 4;
	reg.pad_ion_03.reg_pad_hdmi_3_scl_mux_sel = 4;
	reg.pad_ion_03.reg_pad_hdmi_3_hpd_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44444444, 0x8010
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_04);
	reg.val = 0;
	reg.pad_ion_04.reg_pad_sda1_mux_sel = 4;
	reg.pad_ion_04.reg_pad_sda0_mux_sel = 4;
	reg.pad_ion_04.reg_pad_scl5_mux_sel = 4;
	reg.pad_ion_04.reg_pad_scl4_mux_sel = 4;
	reg.pad_ion_04.reg_pad_scl3_mux_sel = 4;
	reg.pad_ion_04.reg_pad_scl2_mux_sel = 4;
	reg.pad_ion_04.reg_pad_scl1_mux_sel = 4;
	reg.pad_ion_04.reg_pad_scl0_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44444444, 0x8014
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_05);
	reg.val = 0;
	reg.pad_ion_05.reg_pad_tpi_data0_ext2_mux_sel = 4;
	reg.pad_ion_05.reg_pad_tpi_data0_ext1_mux_sel = 4;
	reg.pad_ion_05.reg_pad_tpi_clk_ext2_mux_sel = 4;
	reg.pad_ion_05.reg_pad_tpi_clk_ext1_mux_sel = 4;
	reg.pad_ion_05.reg_pad_sda5_mux_sel = 4;
	reg.pad_ion_05.reg_pad_sda4_mux_sel = 4;
	reg.pad_ion_05.reg_pad_sda3_mux_sel = 4;
	reg.pad_ion_05.reg_pad_sda2_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44444444, 0x8018
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_06);
	reg.val = 0;
	reg.pad_ion_06.reg_pad_tpi_data4_ext2_mux_sel = 4;
	reg.pad_ion_06.reg_pad_tpi_data4_ext1_mux_sel = 4;
	reg.pad_ion_06.reg_pad_tpi_data3_ext2_mux_sel = 4;
	reg.pad_ion_06.reg_pad_tpi_data3_ext1_mux_sel = 4;
	reg.pad_ion_06.reg_pad_tpi_data2_ext2_mux_sel = 4;
	reg.pad_ion_06.reg_pad_tpi_data2_ext1_mux_sel = 4;
	reg.pad_ion_06.reg_pad_tpi_data1_ext2_mux_sel = 4;
	reg.pad_ion_06.reg_pad_tpi_data1_ext1_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44444444, 0x801c
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_07);
	reg.val = 0;
	reg.pad_ion_07.reg_pad_tpi_sop_ext2_mux_sel = 4;
	reg.pad_ion_07.reg_pad_tpi_sop_ext1_mux_sel = 4;
	reg.pad_ion_07.reg_pad_tpi_data7_ext2_mux_sel = 4;
	reg.pad_ion_07.reg_pad_tpi_data7_ext1_mux_sel = 4;
	reg.pad_ion_07.reg_pad_tpi_data6_ext2_mux_sel = 4;
	reg.pad_ion_07.reg_pad_tpi_data6_ext1_mux_sel = 4;
	reg.pad_ion_07.reg_pad_tpi_data5_ext2_mux_sel = 4;
	reg.pad_ion_07.reg_pad_tpi_data5_ext1_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x04444444, 0x8020
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_08);
	reg.val = 0;
	reg.pad_ion_08.reg_pad_tu_io_sd03_mux_sel = 4;
	reg.pad_ion_08.reg_pad_tu_io_sd02_mux_sel = 4;
	reg.pad_ion_08.reg_pad_tu_io_sd01_mux_sel = 4;
	reg.pad_ion_08.reg_pad_tu_io_sd00_mux_sel = 4;
	reg.pad_ion_08.reg_pad_tu_io_clk_mux_sel = 4;
	reg.pad_ion_08.reg_pad_tpi_val_ext2_mux_sel = 4;
	reg.pad_ion_08.reg_pad_tpi_val_ext1_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44440000, 0x8024
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_09);
	reg.val = 0;
	reg.pad_ion_09.reg_pad_tu_io_spi_do_mux_sel = 0;
	reg.pad_ion_09.reg_pad_tu_io_spi_di_mux_sel = 0;
	reg.pad_ion_09.reg_pad_tu_io_spi_cs_mux_sel = 0;
	reg.pad_ion_09.reg_pad_tu_io_spi_clk_mux_sel = 0;
	reg.pad_ion_09.reg_pad_tu_io_sd07_mux_sel = 4;
	reg.pad_ion_09.reg_pad_tu_io_sd06_mux_sel = 4;
	reg.pad_ion_09.reg_pad_tu_io_sd05_mux_sel = 4;
	reg.pad_ion_09.reg_pad_tu_io_sd04_mux_sel = 4;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x44444444, 0x8030
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_10);
	reg.val = 0;
	reg.pad_ion_10.reg_pad_tu_io_sd07__DS = 1;
	reg.pad_ion_10.reg_pad_tu_io_sd06__DS = 1;
	reg.pad_ion_10.reg_pad_tu_io_sd05__DS = 1;
	reg.pad_ion_10.reg_pad_tu_io_sd04__DS = 1;
	reg.pad_ion_10.reg_pad_tu_io_sd03__DS = 1;
	reg.pad_ion_10.reg_pad_tu_io_sd02__DS = 1;
	reg.pad_ion_10.reg_pad_tu_io_sd01__DS = 1;
	reg.pad_ion_10.reg_pad_tu_io_sd00__DS = 1;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x04444444, 0x8034
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_11);
	reg.val = 0;
	reg.pad_ion_11.reg_pad_tu_io_pores_n__DS = 1;
	reg.pad_ion_11.reg_pad_cicam_clk__DS = 1;
	reg.pad_ion_11.reg_pad_tu_io_clk__DS = 1;
	reg.pad_ion_11.reg_pad_tu_io_spi_do__DS = 1;
	reg.pad_ion_11.reg_pad_tu_io_spi_di__DS = 1;
	reg.pad_ion_11.reg_pad_tu_io_spi_cs__DS = 1;
	reg.pad_ion_11.reg_pad_tu_io_spi_clk__DS = 1;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x08040201, 0x8050
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_16);
	reg.val = 0;
	reg.pad_ion_16.reg_tu_io_sd00_in_mux_sel = 0x01;
	reg.pad_ion_16.reg_tu_io_sd01_in_mux_sel = 0x02;
	reg.pad_ion_16.reg_tu_io_sd02_in_mux_sel = 0x04;
	reg.pad_ion_16.reg_tu_io_sd03_in_mux_sel = 0x08;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x80402010, 0x8054
	addr = GET_IOMUX_CTRL_ADDR(pad_ion_17);
	reg.val = 0;
	reg.pad_ion_17.reg_tu_io_sd04_in_mux_sel = 0x10;
	reg.pad_ion_17.reg_tu_io_sd05_in_mux_sel = 0x20;
	reg.pad_ion_17.reg_tu_io_sd06_in_mux_sel = 0x40;
	reg.pad_ion_17.reg_tu_io_sd07_out_mux_sel = 0x80;
	ion_ci_slave_reg_write(dev, reg.val, addr);
}

void ion_ci_slave_mcrg_init(struct te_dev_ion *dev)
{
	union {
		MCRG_CTRL5 mcrg_ctrl5;
		MCRG_CTRL7 mcrg_ctrl7;
		u32 val;
	} reg;
	u16 addr;

	// 0x00000001, 0x3040
	addr = GET_ION_MCRG_ADDR(mcrg_ctrl5);
	reg.val = 0;
	reg.mcrg_ctrl5.reg_tpi_ext2_cam_clk_sel = 1;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x00000000, 0x3048
	addr = GET_ION_MCRG_ADDR(mcrg_ctrl7);
	reg.val = 0;
	reg.mcrg_ctrl7.reg_tpi_ext2_clk_sel = 0;
	ion_ci_slave_reg_write(dev, reg.val, addr);
}

void ion_ci_slave_scrg_init(struct te_dev_ion *dev)
{
	union {
		SCRG_ION4 scrg_ion4;
		SCRG_ION5 scrg_ion5;
		SCRG_ION6 scrg_ion6;
		SCRG_ION7 scrg_ion7;
		u32 val;
	} reg;
	u16 addr;

	// 0x11100000, 0x5010
	addr = GET_ION_SCRG_ADDR(scrg_ion4);
	reg.val = 0;
	reg.scrg_ion4.reg_skew_ff_sd3_clk_sel = 1;
	reg.scrg_ion4.reg_skew_ff_sd4_clk_sel = 1;
	reg.scrg_ion4.reg_skew_ff_sd5_clk_sel = 1;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x22001100, 0x5014
	addr = GET_ION_SCRG_ADDR(scrg_ion5);
	reg.val = 0;
	reg.scrg_ion5.reg_srds_12to3_sd_rx0_clk_sel = 1;
	reg.scrg_ion5.reg_srds_12to3_sd_rx1_clk_sel = 1;
	reg.scrg_ion5.reg_srds_12to3_tp_rx0_clk_sel = 2;
	reg.scrg_ion5.reg_srds_12to3_tp_rx1_clk_sel = 2;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x20000004, 0x5018
	addr = GET_ION_SCRG_ADDR(scrg_ion6);
	reg.val = 0;
	reg.scrg_ion6.reg_srds_12to3_tp_tx0_clk_sel = 4;
	reg.scrg_ion6.reg_tpi_clk_ext2_out_sel = 2;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	// 0x00000006, 0x501C
	addr = GET_ION_SCRG_ADDR(scrg_ion7);
	reg.val = 0;
	reg.scrg_ion7.reg_tpi_clk_ext3_out_sel = 6;
	ion_ci_slave_reg_write(dev, reg.val, addr);
}

void ion_ci_slave_srds12to3_init(struct te_dev_ion *dev)
{
	union {
		SRDS12TO3_MUX mux;
		SRDS12TO3_ALIGN_CFG0 align_cfg0;
		SRDS12TO3_PTG_CFG ptg_cfg;
		SRDS12TO3_PTG_PKT0 ptg_pkt0;
		u32 val;
	} reg;
	u16 addr;

	//0x0c03bbbb, 0x6008
	addr = GET_SRDS12TO3_ADDR(align_cfg0);
	reg.val = 0;
	reg.align_cfg0.reg_idle_init_time1 = 0xbb;
	reg.align_cfg0.reg_idle_init_time0 = 0xbb;
	reg.align_cfg0.reg_idle_init_en1 = 0x1;
	reg.align_cfg0.reg_idle_init_en0 = 0x1;
	reg.align_cfg0.reg_piso1_gate_en = 0x1;
	reg.align_cfg0.reg_piso0_gate_en = 0x1;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	//0x00111100, 0x6004
	addr = GET_SRDS12TO3_ADDR(mux);
	reg.val = 0;
	reg.mux.reg_sel_piso1_sd_out = 0x1;
	reg.mux.reg_sel_piso0_sd_out = 0x1;
	reg.mux.reg_sel_sipo1_tp_out = 0x1;
	reg.mux.reg_sel_sipo0_tp_out = 0x1;
	ion_ci_slave_reg_write(dev, reg.val, addr);

	//0x00000000, 0x6014
	addr = GET_SRDS12TO3_ADDR(ptg_cfg);
	reg.val = 0;
	// All set to zero (see ptg_cfg structure in ion_reg_db.h)
	ion_ci_slave_reg_write(dev, reg.val, addr);

	//0x000000bb, 0x6018
	addr = GET_SRDS12TO3_ADDR(ptg_pkt0);
	reg.val = 0;
	reg.ptg_pkt0.reg_tp_pkt_size = 0xbb; // 187
	ion_ci_slave_reg_write(dev, reg.val, addr);

	//0x04002828, 0x6008
	addr = GET_SRDS12TO3_ADDR(align_cfg0);
	reg.val = 0;
	reg.align_cfg0.reg_idle_init_time1 = 0x28;
	reg.align_cfg0.reg_idle_init_time0 = 0x28;
	reg.align_cfg0.reg_idle_init_en1 = 0;
	reg.align_cfg0.reg_idle_init_en0 = 0;
	reg.align_cfg0.reg_check_sop1 = 0;
	reg.align_cfg0.reg_check_sop0 = 0;
	reg.align_cfg0.reg_fifo1_bypass = 0;
	reg.align_cfg0.reg_fifo0_bypass = 0;
	reg.align_cfg0.reg_piso1_gate_en = 1;
	reg.align_cfg0.reg_piso0_gate_en = 0;
	ion_ci_slave_reg_write(dev, reg.val, addr);
}