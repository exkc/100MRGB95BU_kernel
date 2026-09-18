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
 *  @author	Ilkyu Kim
 *  @version	1.1
 *  @date	2025-07-07
 *  @note	Additional information.
 */

#include <linux/types.h>
#include <lg1k/te/util.h>
#include "ion_ci_reg_ctrl.h"
#include "ion_reg_ctrl.h"
#include "te_impl.h"
#include "ion_spi.h"
#include "ion_ci_reg.h"
#ifdef INCLUDE_O26_CHIP_KDRV
#include "o26/ion/ion_reg_o26.h"
#endif

#ifdef CONFIG_ION_MASTER_SLAVE
#include "ion_ci_reg_slave.h"
#endif

#define ION_WRITE_LEN 7
#define ION_READ_LEN 8
#define ION_ACCESS_SIZE 4
#define ION_READ_OFFSET (ION_READ_LEN - ION_ACCESS_SIZE)

#if CONFIG_LX_BOARD_FPGA
#define NO_CTOP
#endif

struct ctop_func_list {
	int (*rx_init)(void);
	int (*rx_reset)(void);
	int (*rx_reset_tp)(bool);
	int (*rx_checker_init)(u16 pkt_cnt);
	int (*rx_checker_start)(u16 pkt_cnt, u16 *pkt, u16 *err);
};

//NOTE: consider manage channer number by cfg
#define O24_SPI_CH 0
#define O26_SPI_CH 2

#ifdef INCLUDE_O26_CHIP_KDRV
static const struct ctop_func_list o26_ctop_func = {
	.rx_init = O26_ION_CI_REG_SetInitValue,
	.rx_reset = O26_ION_CI_Reset,
	.rx_reset_tp = O26_ION_CI_Reset_TP,
	.rx_checker_init = O26_ION_CI_Init_TP_Checker,
	.rx_checker_start = O26_ION_CI_Start_TP_Checker
};
#endif

static const struct ctop_func_list *ctop_func;

struct ion_reg_ctrl g_ci_ion;
static struct ion_reg_ctrl *get_reg_ctrl(void)
{
	return &g_ci_ion;
}

static int ion_write(struct te_dev_ion *dev, u32 val, u16 addr)
{
	u8 txbuf[ION_WRITE_LEN] = {0, };
	int rc;

	log_debug("ch:%u val:0x%08x addr:0x%04x", dev->ci_spi_ch, val, addr);

	// dst_address
	te_put16(txbuf, addr);

	// option
	txbuf[2] = ion_spi_gen_option(DIRECTION_WRITE, MODE_ION_REG, 1);

	// value
	te_put32(txbuf + 3, val);

	rc = ion_spi_send_message(dev, txbuf, ION_WRITE_LEN, 0);
	CHECK_ERROR(rc < 0, return rc, "fail ch:%u addr:%04x %d",
		    dev->ci_spi_ch, addr, rc);

	return 0;
}

static int ion_read(struct te_dev_ion *dev, u32 *val, u16 addr)
{
	u8 txbuf[ION_READ_LEN] = {0, };
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

	log_debug("ch:%u val:0x%04x addr:0x%02x", dev->ci_spi_ch, *val, addr);
	return 0;
}

static int rx_reg_write(struct te_dev_ion *dev, u32 val, u16 addr)
{
#ifndef CONFIG_ION_MASTER_SLAVE
	return -EFAULT;
#else
	return ion_ci_slave_reg_write(dev, val, addr);
#endif
}

static int rx_reg_read(struct te_dev_ion *dev, u32 *val, u16 addr)
{
#ifndef CONFIG_ION_MASTER_SLAVE
	return -EFAULT;
#else
	return ion_ci_slave_reg_read(dev, val, addr);
#endif
}

int ion_ci_reg_write(struct te_dev_ion *dev, u8 ch, u32 val, u16 addr)
{
	if (ch == 1)
		return rx_reg_write(dev, val, addr);

	return ion_write(dev, val, addr);
}

int ion_ci_reg_read(struct te_dev_ion *dev, u8 ch, u32 *val, u16 addr)
{
	if (ch == 1)
		return rx_reg_read(dev, val, addr);

	return ion_read(dev, val, addr);
}

static void tx_ahb_init(struct te_dev_ion *dev)
{
	//0x70731, 0x9020
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_8, reg_clkx2_en, 1);
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_8, reg_update_phase, 1);
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_8, reg_load_phase, 1);
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_8, reg_dummy_size, 7);
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_8, reg_rd_cnt, 7);
	TX_SPI_TO_AHB_WrFL(dev, spi_to_ahb_8);

	//0x2727, 0x9028
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_10, reg_ci_rd_mem_rd_dummy, 0x27);
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_10, reg_ci_rd_mem_update_cnt, 0x27);
	TX_SPI_TO_AHB_WrFL(dev, spi_to_ahb_10);

	//0x2727, 0x9034
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_13, reg_ci_rd_cam_ctrl_rd_dummy,
			   0x27);
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_13, reg_ci_rd_cam_ctrl_update_cnt,
			   0x27);
	TX_SPI_TO_AHB_WrFL(dev, spi_to_ahb_13);

	//0xf0f, 0x903c
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_16, reg_ci_rd16_rd_dummy, 0xf);
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_16, reg_ci_rd16_update_cnt, 0xf);
	TX_SPI_TO_AHB_WrFL(dev, spi_to_ahb_16);

	//0x707, 0x9040
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_17, reg_smc_rd32_rd_dummy, 0x7);
	TX_SPI_TO_AHB_Wr01(dev, spi_to_ahb_17, reg_smc_rd32_update_cnt, 0x7);
	TX_SPI_TO_AHB_WrFL(dev, spi_to_ahb_17);
}

static void tx_scrg_init(struct te_dev_ion *dev)
{
	// 0x11100011, 0x5010
	TX_SCRG_Wr01(dev, scrg_ion4, reg_ci25_clk_sel, 1);
	TX_SCRG_Wr01(dev, scrg_ion4, reg_ci50_clk_sel, 1);
	TX_SCRG_Wr01(dev, scrg_ion4, reg_skew_ff_sd0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion4, reg_skew_ff_sd1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion4, reg_skew_ff_sd2_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion4, reg_skew_ff_sd3_clk_sel, 1);
	TX_SCRG_Wr01(dev, scrg_ion4, reg_skew_ff_sd4_clk_sel, 1);
	TX_SCRG_Wr01(dev, scrg_ion4, reg_skew_ff_sd5_clk_sel, 1);
	TX_SCRG_WrFL(dev, scrg_ion4);

	// 0x00001100, 0x5014
	TX_SCRG_Wr01(dev, scrg_ion5, reg_skew_ff_sd6_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_skew_ff_sd7_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_sd_rx0_clk_sel, 1);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_sd_rx1_clk_sel, 1);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_sd_tx0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_sd_tx1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_tp_rx0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_tp_rx1_clk_sel, 0);
	TX_SCRG_WrFL(dev, scrg_ion5);

	// 0x00000004, 0x5018
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_12to3_tp_tx0_clk_sel, 4);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_12to3_tp_tx1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_32to1_sd_rx0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_32to1_sd_rx1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_32to1_sd_tx0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_32to1_sd_tx1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_tpi_clk_ext1_out_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_tpi_clk_ext2_out_sel, 0);
	TX_SCRG_WrFL(dev, scrg_ion6);

	// 0x00000001, 0x501C
	TX_SCRG_Wr01(dev, scrg_ion7, reg_tpi_clk_ext3_out_sel, 1);
	TX_SCRG_WrFL(dev, scrg_ion7);
}

static void tx_mcrg_init(struct te_dev_ion *dev)
{
	// 0x00000001, 0x3040
	TX_MCRG_Wr01(dev, mcrg_ctrl5, reg_tpi_ext2_cam_clk_sel, 1);
	TX_MCRG_WrFL(dev, mcrg_ctrl5);

	// 0x00000000, 0x3048
	TX_MCRG_Wr01(dev, mcrg_ctrl7, reg_tpi_ext2_clk_sel, 0);
	TX_MCRG_WrFL(dev, mcrg_ctrl7);
}

static void tx_ctop_init(struct te_dev_ion *dev)
{
	// 0x0000000f, 0x0020
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_i_sel_tu_io_sd07, 1);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_c_sel_tu_io_sd07, 1);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_i_sel_tu_io_sd06, 1);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_c_sel_tu_io_sd06, 1);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_i_sel_tu_io_sd05, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_c_sel_tu_io_sd05, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_i_sel_tu_io_sd04, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_c_sel_tu_io_sd04, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_i_sel_tu_io_sd03, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_c_sel_tu_io_sd03, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_i_sel_tu_io_sd02, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_c_sel_tu_io_sd02, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_i_sel_tu_io_sd01, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_c_sel_tu_io_sd01, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_i_sel_tu_io_sd00, 0);
	TX_TOP_Wr01(dev, crg_ctrl_1, reg_c_sel_tu_io_sd00, 0);
	TX_TOP_WrFL(dev, crg_ctrl_1);
}

static void tx_iomux_ctrl_init(struct te_dev_ion *dev)
{
#ifndef CONFIG_ION_MASTER_SLAVE
	// 0x33333333, 0x8000
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio07_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio05_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio04_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio03_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio02_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio01_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio00_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_cicam_clk_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_00);
#else
	// 0x38888333, 0x8000
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio07_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio05_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio04_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio03_mux_sel, 8);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio02_mux_sel, 8);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio01_mux_sel, 8);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_gpio00_mux_sel, 8);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_00, reg_pad_cicam_clk_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_00);
#endif

	// 0x33333333, 0x8004
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_01, reg_pad_hdmi_1_scl_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_01, reg_pad_hdmi_1_hpd_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_01, reg_pad_hdmi_det1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_01, reg_pad_hdmi_1_5v_in_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_01, reg_pad_gpio11_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_01, reg_pad_gpio10_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_01, reg_pad_gpio09_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_01, reg_pad_gpio08_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_01);

	// 0x33333333, 0x8008
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_02, reg_pad_hdmi_det3_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_02, reg_pad_hdmi_3_5v_in_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_02, reg_pad_hdmi_2_sda_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_02, reg_pad_hdmi_2_scl_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_02, reg_pad_hdmi_2_hpd_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_02, reg_pad_hdmi_det2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_02, reg_pad_hdmi_2_5v_in_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_02, reg_pad_hdmi_1_sda_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_02);

	// 0x33333333, 0x800c
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_03, reg_pad_hdmi_4_sda_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_03, reg_pad_hdmi_4_scl_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_03, reg_pad_hdmi_4_hpd_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_03, reg_pad_hdmi_det4_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_03, reg_pad_hdmi_4_5v_in_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_03, reg_pad_hdmi_3_sda_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_03, reg_pad_hdmi_3_scl_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_03, reg_pad_hdmi_3_hpd_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_03);

	// 0x33333333, 0x8010
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_04, reg_pad_sda1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_04, reg_pad_sda0_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_04, reg_pad_scl5_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_04, reg_pad_scl4_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_04, reg_pad_scl3_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_04, reg_pad_scl2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_04, reg_pad_scl1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_04, reg_pad_scl0_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_04);

	// 0x33333333, 0x8014
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_05, reg_pad_tpi_data0_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_05, reg_pad_tpi_data0_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_05, reg_pad_tpi_clk_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_05, reg_pad_tpi_clk_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_05, reg_pad_sda5_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_05, reg_pad_sda4_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_05, reg_pad_sda3_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_05, reg_pad_sda2_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_05);

	// 0x33333333, 0x8018
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_06, reg_pad_tpi_data4_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_06, reg_pad_tpi_data4_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_06, reg_pad_tpi_data3_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_06, reg_pad_tpi_data3_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_06, reg_pad_tpi_data2_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_06, reg_pad_tpi_data2_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_06, reg_pad_tpi_data1_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_06, reg_pad_tpi_data1_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_06);

	// 0x33333333, 0x801c
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_07, reg_pad_tpi_sop_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_07, reg_pad_tpi_sop_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_07, reg_pad_tpi_data7_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_07, reg_pad_tpi_data7_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_07, reg_pad_tpi_data6_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_07, reg_pad_tpi_data6_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_07, reg_pad_tpi_data5_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_07, reg_pad_tpi_data5_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_07);

	// 0x03333333, 0x8020
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_08, reg_pad_tu_io_sd03_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_08, reg_pad_tu_io_sd02_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_08, reg_pad_tu_io_sd01_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_08, reg_pad_tu_io_sd00_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_08, reg_pad_tu_io_clk_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_08, reg_pad_tpi_val_ext2_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_08, reg_pad_tpi_val_ext1_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_08);

	// 0x33330000, 0x8024
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_09, reg_pad_tu_io_spi_do_mux_sel, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_09, reg_pad_tu_io_spi_di_mux_sel, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_09, reg_pad_tu_io_spi_cs_mux_sel, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_09, reg_pad_tu_io_spi_clk_mux_sel, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_09, reg_pad_tu_io_sd07_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_09, reg_pad_tu_io_sd06_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_09, reg_pad_tu_io_sd05_mux_sel, 3);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_09, reg_pad_tu_io_sd04_mux_sel, 3);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_09);

	// 0x44444444, 0x8030
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd07__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd07__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd07__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd06__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd06__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd06__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd05__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd05__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd05__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd04__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd04__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd04__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd03__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd03__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd03__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd02__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd02__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd02__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd01__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd01__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd01__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd00__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd00__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_10, reg_pad_tu_io_sd00__DS, 1);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_10);

	// 0x04444444, 0x8034
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_pores_n__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_pores_n__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_pores_n__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_cicam_clk__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_cicam_clk__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_cicam_clk__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_clk__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_clk__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_clk__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_do__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_do__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_do__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_di__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_di__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_di__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_cs__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_cs__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_cs__DS, 1);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_clk__IE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_clk__PE, 0);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_11, reg_pad_tu_io_spi_clk__DS, 1);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_11);

#ifdef CONFIG_ION_MASTER_SLAVE
	// 0x01082010, 0x8050
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_16, reg_tu_io_sd00_in_mux_sel, 0x10);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_16, reg_tu_io_sd01_in_mux_sel, 0x20);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_16, reg_tu_io_sd02_in_mux_sel, 0x08);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_16, reg_tu_io_sd03_in_mux_sel, 0x01);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_16);

	// 0x80400204, 0x8054
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_17, reg_tu_io_sd04_in_mux_sel, 0x04);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_17, reg_tu_io_sd05_in_mux_sel, 0x02);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_17, reg_tu_io_sd06_in_mux_sel, 0x40);
	TX_IOMUX_CTRL_Wr01(dev, pad_ion_17, reg_tu_io_sd07_out_mux_sel, 0x80);
	TX_IOMUX_CTRL_WrFL(dev, pad_ion_17);
#endif
}

static void tx_srds12to3_init(struct te_dev_ion *dev)
{
#ifdef CONFIG_ION_MASTER_SLAVE
	//0x0c03bbbb, 0x6008
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_time1, 0xbb);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_time0, 0xbb);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_en1, 0x1);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_en0, 0x1);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_check_sop1, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_check_sop0, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_delete_sop1, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_delete_sop0, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_invert_valid1, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_invert_valid0, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_fifo1_bypass, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_fifo0_bypass, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_piso1_gate_en, 0x1);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_piso0_gate_en, 0x1);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_sipo1, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_sipo0, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_piso1, 0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_piso0, 0);
	TX_SRDS12TO3_WrFL(dev, align_cfg0);
#endif

	//0x00111100, 0x6004
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo1_sd_in, 0);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo0_sd_in, 0);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso1_sd_out, 1);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso0_sd_out, 1);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo1_tp_out, 1);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo0_tp_out, 1);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso1_tp_in, 0);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso0_tp_in, 0);
	TX_SRDS12TO3_WrFL(dev, mux);

	//0x00000000, 0x6014
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk1_mode, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk1_en, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk0_mode, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk0_en, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_ptg1_en, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_ptg0_en, 0);
	//TX_SRDS12TO3_Wr01(dev, ptg_cfg, result_valid1, 0);
	//TX_SRDS12TO3_Wr01(dev, ptg_cfg, result_valid0, 0);
	TX_SRDS12TO3_WrFL(dev, ptg_cfg);

	//0x000000bb, 0x6018
	TX_SRDS12TO3_Wr01(dev, ptg_pkt0, reg_tp_pkt_size, 0xbb); // 187
	TX_SRDS12TO3_WrFL(dev, ptg_pkt0);

	//0x08002828, 0x6008
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_time1, 0x28);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_time0, 0x28);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_en1, 0x0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_en0, 0x0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_piso1_gate_en, 0x0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_piso0_gate_en, 0x1);
	TX_SRDS12TO3_WrFL(dev, align_cfg0);
}

int ion_ci_set_tpo_mode(struct te_dev_ion *dev, u8 is_serial)
{
	if (!dev)
		return -EFAULT;

	TX_SRDS12TO3_RdFL(dev, align_cfg0);

	if (is_serial) {
		TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_sipo1, 0);
		TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_sipo0, 1);
		TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_piso1, 1);
		TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_piso0, 0);
	} else {
		TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_sipo1, 0);
		TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_sipo0, 0);
		TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_piso1, 0);
		TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_piso0, 0);
	}

	TX_SRDS12TO3_WrFL(dev, align_cfg0);

	return 0;
}

/* HW Reset(ALL) for ION1 (abnormal or intentional operation(SLT))*/
int ion_ci_reg_hw_reset(struct te_dev_ion *dev)
{
	if (ctop_func && ctop_func->rx_reset)
		return ctop_func->rx_reset();
	else
		return -ENODEV;
}

static void tx_checker_scrg_init(struct te_dev_ion *dev)
{
	// 0x02000000, 0x5014
	TX_SCRG_Wr01(dev, scrg_ion5, reg_skew_ff_sd6_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_skew_ff_sd7_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_sd_rx0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_sd_rx1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_sd_tx0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_sd_tx1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_tp_rx0_clk_sel, 2);
	TX_SCRG_Wr01(dev, scrg_ion5, reg_srds_12to3_tp_rx1_clk_sel, 0);
	TX_SCRG_WrFL(dev, scrg_ion5);

	// 0x00000022, 0x5018
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_12to3_tp_tx0_clk_sel, 2);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_12to3_tp_tx1_clk_sel, 2);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_32to1_sd_rx0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_32to1_sd_rx1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_32to1_sd_tx0_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_srds_32to1_sd_tx1_clk_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_tpi_clk_ext1_out_sel, 0);
	TX_SCRG_Wr01(dev, scrg_ion6, reg_tpi_clk_ext2_out_sel, 0);
	TX_SCRG_WrFL(dev, scrg_ion6);
}

static void tx_checker_srds12to3_init(struct te_dev_ion *dev)
{
	// SW REG Clear
	//0x000020c0, 0x6000 (reset)
	TX_SRDS12TO3_RdFL(dev, swrst);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_sipo0_sd, 1);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_sipo0_tp, 1);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_fifo0, 1);
	TX_SRDS12TO3_WrFL(dev, swrst);

	//0x00000000, 0x6000 (reset de-assert)
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_sipo0_sd, 0);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_sipo0_tp, 0);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_fifo0, 0);
	TX_SRDS12TO3_WrFL(dev, swrst);

	// PTG Reset
	//0x00000000, 0x6014
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk1_mode, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk1_en, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk0_mode, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk0_en, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_ptg1_en, 0);
	TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_ptg0_en, 0);
	TX_SRDS12TO3_WrFL(dev, ptg_cfg);

	// Check SOP Setting
	//0x080c2828, 0x6008
	TX_SRDS12TO3_RdFL(dev, align_cfg0);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_check_sop1, 1);
	TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_check_sop0, 1);
	TX_SRDS12TO3_WrFL(dev, align_cfg0);

	// PISO0/1 path set
	//0x02400100, 0x6004
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo1_sd_in, 0);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo0_sd_in, 0);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso1_sd_out, 1); // normal
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso0_sd_out, 0);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo1_tp_out, 0);
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo0_tp_out, 4); // pd_out to to PISO1 pd_in, 0:0
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso1_tp_in, 2); // sd_out to SIPO0 sd_in, 0:0
	TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso0_tp_in, 0);
	TX_SRDS12TO3_WrFL(dev, mux);
}

static void tx_checker_init(struct te_dev_ion *dev)
{
	tx_checker_scrg_init(dev);
	tx_checker_srds12to3_init(dev);
}

int ion_ci_reg_init_tp_checker(struct te_dev_ion *dev, u16 pkt_cnt)
{
	int rc;

	if (!ctop_func || !ctop_func->rx_checker_init) {
		log_error("NO CTOP func");
		return -ENODEV;
	}

	rc = ctop_func->rx_checker_init(pkt_cnt);
	if (rc) {
		log_error("rx_checker_init failed %d", rc);
		return rc;
	}

	tx_checker_init(dev);

	return 0;
}

int ion_ci_reg_start_tp_checker(struct te_dev_ion *dev, u16 pkt_cnt)
{
	int rc;
	u16 rx_pkt, err_pkt;

	if (!ctop_func || !ctop_func->rx_checker_start) {
		log_error("NO CTOP func");
		return -ENODEV;
	}

	rc = ctop_func->rx_checker_start(pkt_cnt, &rx_pkt, &err_pkt);
	if (rc) {
		log_error("rx_checker_start failed %d", rc);
		return rc;
	}

	log_debug("pkt[%u] -> rx[%u], err[%u]", pkt_cnt, rx_pkt, err_pkt);

	if (pkt_cnt != rx_pkt) {
		log_error("pkt[%u] -> rx[%u], err[%u]", pkt_cnt, rx_pkt,
			  err_pkt);
		return -EIO;
	}

	return 0;
}

static void tx_reset_tp(struct te_dev_ion *dev, bool assert)
{
	u8 v = (assert) ? 1 : 0;

	TX_SRDS12TO3_RdFL(dev, swrst);

	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_sipo1_sd, v);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_sipo1_tp, v);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_sipo0_sd, v);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_sipo0_tp, v);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_piso1_sd, v);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_piso1_tp, v);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_piso0_sd, v);
	TX_SRDS12TO3_Wr01(dev, swrst, reg_swrst_piso0_tp, v);

	TX_SRDS12TO3_WrFL(dev, swrst); //swrst assert
}

/* Reset ion1 TP if the TP sync has been completely lost
 * Async control & no need to delay (considering spi propagation delay) */
int ion_ci_reg_reset_tp(struct te_dev_ion *dev)
{
	if (!dev)
		return -EFAULT;
	if (!ctop_func || !ctop_func->rx_reset_tp)
		return -ENODEV;

	/* Reset Sequence
	   RX TP reset assert -> TX TP reset assert ->
	   TX TP reset deassert -> RX TP reset deassert */
	ctop_func->rx_reset_tp(true);
	tx_reset_tp(dev, true);

	tx_reset_tp(dev, false);
	ctop_func->rx_reset_tp(false);

	return 0;
}

static int reg_init(void)
{
	struct ion_reg_ctrl *c;

	c = get_reg_ctrl(); // Only TX will use below macro

	INIT_REG_CTRL(c->top, 0, CTOP_BASE_ADDRESS, CTOP_REG_SIZE);
	INIT_REG_CTRL(c->sadc[0], 0, SARADC0_BASE_ADDRESS, SARADC0_REG_SIZE);
	INIT_REG_CTRL(c->sadc[1], 0, SARADC1_BASE_ADDRESS, SARADC1_REG_SIZE);
	INIT_REG_CTRL(c->mcrg, 0, ION_MCRG_BASE_ADDRESS, ION_MCRG_REG_SIZE);
	INIT_REG_CTRL(c->bnd, 0, ION_BND_BASE_ADDRESS, ION_BND_REG_SIZE);
	INIT_REG_CTRL(c->scrg, 0, ION_SCRG_BASE_ADDRESS, ION_SCRG_REG_SIZE);
	INIT_REG_CTRL(c->srds12to3, 0, SRDS12TO3_BASE_ADDRESS,
		      SRDS12TO3_REG_SIZE);
	INIT_REG_CTRL(c->srds32to1[0], 0, SRDS32TO1_0_BASE_ADDRESS,
		      SRDS32TO1_0_REG_SIZE);
	INIT_REG_CTRL(c->iomux_ctrl, 0, IOMUX_CTRL_BASE_ADDRESS,
		      IOMUX_CTRL_REG_SIZE);
	INIT_REG_CTRL(c->spi_to_ahb, 0, SPI_TO_AHB_BASE_ADDRESS,
		      SPI_TO_AHB_REG_SIZE);
	INIT_REG_CTRL(c->srds32to1[1], 0, SRDS32TO1_1_BASE_ADDRESS,
		      SRDS32TO1_1_REG_SIZE);
	c->en = true;

	return 0;
}

static int ctop_init(void)
{
#ifdef NO_CTOP
	return 0;
#endif

#ifndef CONFIG_ION_MASTER_SLAVE
	switch (lx_chip()) {
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
		ctop_func = &o26_ctop_func;
		break;
#endif
	default:
		ctop_func = NULL;
		WARN_ON(1);
	}

	return 0;
#else
	ctop_func = NULL;
	return 0;
#endif // CONFIG_ION_MASTER_SLAVE
}

int ion_ci_reg_init(struct te_dev_ion *dev)
{
	int rc;

	switch (lx_chip()) {
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
		dev->ci_spi_ch = O24_SPI_CH;
		break;
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
		dev->ci_spi_ch = O26_SPI_CH;
		break;
#endif
	default:
		WARN_ON(1);
		return -ENODEV;
	}

	rc = reg_init();
	if (rc) {
		log_error("reg_init fail %d", rc);
		return rc;
	}

	ctop_init();

	return 0;
}

void ion_ci_reg_release(struct te_dev_ion *dev)
{
	struct ion_reg_ctrl *c = get_reg_ctrl();

	if (!c->en)
		return;

	UNINIT_REG_CTRL(c->top);
	UNINIT_REG_CTRL(c->sadc[0]);
	UNINIT_REG_CTRL(c->sadc[1]);
	UNINIT_REG_CTRL(c->mcrg);
	UNINIT_REG_CTRL(c->bnd);
	UNINIT_REG_CTRL(c->scrg);
	UNINIT_REG_CTRL(c->srds12to3);
	UNINIT_REG_CTRL(c->srds32to1[0]);
	UNINIT_REG_CTRL(c->iomux_ctrl);
	UNINIT_REG_CTRL(c->spi_to_ahb);
	UNINIT_REG_CTRL(c->srds32to1[1]);
}

int ion_ci_reg_hw_init(struct te_dev_ion *dev)
{
#ifndef CONFIG_ION_MASTER_SLAVE
	if (ctop_func && ctop_func->rx_init)
		ctop_func->rx_init();
#endif

	/* LDO clock propagation needs 1.2 ~ 1.4 ms to ION TX */
	log_noti("tx wait for 3 ms");
	usleep_range(1000 * 3, 1000 * 3);

	tx_ahb_init(dev);
	tx_scrg_init(dev);
	tx_mcrg_init(dev);
	tx_ctop_init(dev);
	tx_iomux_ctrl_init(dev);

#ifndef CONFIG_ION_MASTER_SLAVE

	tx_srds12to3_init(dev);

#else
	usleep_range(5000, 5000); //wait for clock deliver to slave (5 ms)

	ion_ci_slave_ctop_init(dev);
	ion_ci_slave_iomux_ctrl_init(dev);
	ion_ci_slave_mcrg_init(dev);
	ion_ci_slave_scrg_init(dev);

	tx_srds12to3_init(dev);

	ion_ci_slave_srds12to3_init(dev);
#endif
	return 0;
}
