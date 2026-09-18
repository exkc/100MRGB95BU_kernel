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
#include "ion_io_reg.h"

#ifdef INCLUDE_O26_CHIP_KDRV
#include "o26/ion/ion_reg_o26.h"
#endif

#ifdef CONFIG_ION_MASTER_SLAVE
#include "ion_io_reg_slave.h"
#endif

#define ION_TP_PKT_SIZE 0xbb

//#define SUPPORT_ION_TP_CG

#if CONFIG_LX_BOARD_FPGA
#define NO_CTOP
#endif

struct ctop_func_list {
	int (*set_clockgate)(u8 idx, u8 v);
	int (*reset)(u8 idx);
	int (*set_mux)(u8 tpi_num);
	int (*set_ptg_cfg)(void);
	int (*set_ptg_pkt0)(u8 tpi_num);
	int (*set_align_cfg0)(u8 tpi_num, u8 is_serial, u8 check_sop);
	int (*set_start_code)(u8 tpi_num, u8 tlv_en, u8 code);
};

static const struct ctop_func_list *ctop_func;

struct ion_reg_ctrl g_io_ion;
static struct ion_reg_ctrl *get_reg_ctrl(void)
{
	return &g_io_ion;
}

/* FIXME: below prototype is used for test */
#ifdef INCLUDE_O24_CHIP_KDRV
#if 0
extern int o24_ucom_spi_read(UINT8 *addr, UINT8 *data, UINT8 num);
extern int o24_ucom_spi_write(UINT8 *addr, UINT8 *data, UINT8 num);
extern UINT32 o24_ucom_spi_read32(UINT32 addr);
extern int o24_ucom_spi_write32(UINT32 addr, UINT32 val);
#else
static inline int o24_ucom_spi_read(UINT8 *addr, UINT8 *data, UINT8 num)
{
	log_error("not supported");
	return -ENOTSUPP;
}
static inline int o24_ucom_spi_write(UINT8 *addr, UINT8 *data, UINT8 num)
{
	log_error("not supported");
	return -ENOTSUPP;
}
static inline UINT32 o24_ucom_spi_read32(UINT32 addr)
{
	log_error("not supported");
	return -ENOTSUPP;
}
static inline int o24_ucom_spi_write32(UINT32 addr, UINT32 val)
{
	log_error("not supported");
	return -ENOTSUPP;
}
#endif

static u32 o24_ion_io_read(u32 addr)
{
	return o24_ucom_spi_read32(addr);
}
static int o24_ion_io_write(u32 addr, u32 val)
{
	return o24_ucom_spi_write32(addr, val);
}

static const struct te_dev_ion_ucom_func o24_ucom_func = {
	.read = o24_ion_io_read,
	.write = o24_ion_io_write,
};
#endif //INCLUDE_O24_CHIP_KDRV

#ifdef INCLUDE_O26_CHIP_KDRV
static const struct te_dev_ion_ucom_func o26_ucom_func = {
	.read = O26_ION_IO_reg_read,
	.write = O26_ION_IO_reg_write,
};

static const struct ctop_func_list o26_ctop_func = {
	.set_clockgate = O26_ION_IO_Set_ClockGate,
	.reset = O26_ION_IO_Reset,
	.set_mux = O26_ION_IO_Set_mux,
	.set_ptg_cfg = O26_ION_IO_Set_ptg_cfg,
	.set_ptg_pkt0 = O26_ION_IO_Set_ptg_pkt0,
	.set_align_cfg0 = O26_ION_IO_Set_align_cfg0,
	.set_start_code = O26_ION_IO_Set_start_code
};
#endif //INCLUDE_O26_CHIP_KDRV

static int rx_reg_write(struct te_dev_ion *dev, u32 val, u16 addr)
{
#ifndef CONFIG_ION_MASTER_SLAVE
	return -EFAULT;
#else
	return ion_io_slave_reg_write(dev, val, addr);
#endif
}

static int rx_reg_read(struct te_dev_ion *dev, u32 *val, u16 addr)
{
#ifndef CONFIG_ION_MASTER_SLAVE
	return -EFAULT;
#else
	return ion_io_slave_reg_read(dev, val, addr);
#endif
}

int ion_io_reg_write(struct te_dev_ion *dev, u8 ch, u32 val, u32 addr)
{
	const struct te_dev_ion_ucom_func *ucom_func = dev->ucom_func;

	if (ch == 1) {
		return rx_reg_write(dev, val, (u16)(addr & 0xFF));
	} else if (ucom_func && ucom_func->write) {
		if (addr < ION_BASE_ADDRESS)
			addr += ION_BASE_ADDRESS;

		return ucom_func->write(addr, val);
	} else {
		return -ENODEV;
	}
}

int ion_io_reg_read(struct te_dev_ion *dev, u8 ch, u32 *val, u32 addr)
{
	const struct te_dev_ion_ucom_func *ucom_func = dev->ucom_func;

	if (ch == 1) {
		return rx_reg_read(dev, val, (u16)(addr & 0xFF));
	} else if (ucom_func && ucom_func->read) {
		if (addr < ION_BASE_ADDRESS)
			addr += ION_BASE_ADDRESS;

		*val = ucom_func->read(addr);
	} else {
		return -ENODEV;
	}

	return 0;
}

static int set_clock_gate(struct te_dev_ion *dev, u8 ch, u8 idx, bool en)
{
#ifdef SUPPORT_ION_TP_CG
	const u8 v = (en) ? 1 : 0;

	if (ch == 0) {
		TX_SCRG_RdFL(dev, scrg_ion2);
		if (idx == 0) {
			TX_SCRG_Wr01(dev, scrg_ion2,
				     reg_srds_12to3_sd_rx0_clk_gate_en, v);
			TX_SCRG_Wr01(dev, scrg_ion2,
				     reg_srds_12to3_sd_tx0_clk_gate_en, v);
			TX_SCRG_Wr01(dev, scrg_ion2,
				     reg_srds_12to3_tp_rx0_clk_gate_en, v);
			TX_SCRG_Wr01(dev, scrg_ion2,
				     reg_srds_12to3_tp_tx0_clk_gate_en, v);
		} else {
			TX_SCRG_Wr01(dev, scrg_ion2,
				     reg_srds_12to3_sd_rx1_clk_gate_en, v);
			TX_SCRG_Wr01(dev, scrg_ion2,
				     reg_srds_12to3_sd_tx1_clk_gate_en, v);
			TX_SCRG_Wr01(dev, scrg_ion2,
				     reg_srds_12to3_tp_rx1_clk_gate_en, v);
			TX_SCRG_Wr01(dev, scrg_ion2,
				     reg_srds_12to3_tp_tx1_clk_gate_en, v);
		}
		TX_SCRG_WrFL(dev, scrg_ion2);
	} else {
#ifndef CONFIG_ION_MASTER_SLAVE /* O26 */
		if (ctop_func && ctop_func->set_clockgate)
			return ctop_func->set_clockgate(idx, v);
#else
		return ion_io_slave_set_clock_gate(dev, idx, en);
#endif // CONFIG_ION_MASTER_SLAVE
	}
#endif // SUPPORT_ION_TP_CG
	return 0;
}

int ion_io_reg_set_clock_gate(struct te_dev_ion *dev, u8 ch, u8 idx, bool en)
{
	int ret;

	if (ch >= TE_ION_CH_NUM || idx >= TE_ION_TPI_NUM) {
		log_error("invalid param; ch:%u idx:%u", ch, idx);
		return -EINVAL;
	}
	log_noti("ch:%u idx:%u en:%s", ch, idx, (en) ? "true" : "false");

	ret = set_clock_gate(dev, ch, idx, en);
	if (ret < 0) {
		log_error("error %d in set_clock_gate", ret);
		return ret;
	}

	return 0;
}

static int do_reset(struct te_dev_ion *dev, u8 ch, u8 idx)
{
	if (ch == 0) {
		TX_SCRG_RdFL(dev, scrg_ion3);
		if (idx == 0) {
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_sd_rx0_n, 1);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_sd_tx0_n, 1);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_tp_rx0_n, 1);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_tp_tx0_n, 1);
		} else { // idx == 1
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_sd_rx1_n, 1);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_sd_tx1_n, 1);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_tp_rx1_n, 1);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_tp_tx1_n, 1);
		}
		TX_SCRG_WrFL(dev, scrg_ion3);

		if (idx == 0) {
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_sd_rx0_n, 0);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_sd_tx0_n, 0);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_tp_rx0_n, 0);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_tp_tx0_n, 0);
		} else { // idx == 1
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_sd_rx1_n, 0);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_sd_tx1_n, 0);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_tp_rx1_n, 0);
			TX_SCRG_Wr01(dev, scrg_ion3,
				     reg_soft_rst_srds_12to3_tp_tx1_n, 0);
		}
		TX_SCRG_WrFL(dev, scrg_ion3);
	} else { // ch == 1
#ifndef CONFIG_ION_MASTER_SLAVE /* O26 */
		if (ctop_func && ctop_func->reset)
			return ctop_func->reset(idx);
#else
		return ion_io_slave_do_reset(dev, idx);
#endif
	}
	return 0;
}

static int set_mux(struct te_dev_ion *dev, u8 ch, u8 ext_num)
{
	if (ch == 0) {
		TX_SRDS12TO3_RdFL(dev, mux);
		TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo1_sd_in, 0);
		TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo0_sd_in, 0);
		if (ext_num == 0)
			TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso0_sd_out, 1);
		else
			TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso1_sd_out, 1);
		TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo0_tp_out, 0);
		TX_SRDS12TO3_Wr01(dev, mux, reg_sel_sipo1_tp_out, 0);
		TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso1_tp_in, 0);
		TX_SRDS12TO3_Wr01(dev, mux, reg_sel_piso0_tp_in, 0);
		TX_SRDS12TO3_WrFL(dev, mux);
	} else {
#ifndef CONFIG_ION_MASTER_SLAVE /* O26 */
		if (ctop_func && ctop_func->set_mux)
			return ctop_func->set_mux(ext_num);
#else
		return ion_io_slave_set_mux(dev, ext_num);
#endif
	}

	return 0;
}

static int set_ptg_cfg(struct te_dev_ion *dev, u8 ch)
{
	if (ch == 0) {
		TX_SRDS12TO3_RdFL(dev, ptg_cfg);
		TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk1_mode, 0);
		TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk1_en, 0);
		TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk0_mode, 0);
		TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_chk0_en, 0);
		TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_ptg1_en, 0);
		TX_SRDS12TO3_Wr01(dev, ptg_cfg, reg_ptg0_en, 0);
		TX_SRDS12TO3_Wr01(dev, ptg_cfg, result_valid1, 0);
		TX_SRDS12TO3_Wr01(dev, ptg_cfg, result_valid0, 0);
		TX_SRDS12TO3_WrFL(dev, ptg_cfg);
	} else {
#ifndef CONFIG_ION_MASTER_SLAVE /* O26 */
		if (ctop_func && ctop_func->set_ptg_cfg)
			return ctop_func->set_ptg_cfg();
#else
		return ion_io_slave_set_ptg_cfg(dev);
#endif
	}

	return 0;
}

static int set_ptg_pkt0(struct te_dev_ion *dev, u8 ch, u8 ext_num)
{
	if (ch == 0) {
		TX_SRDS12TO3_RdFL(dev, ptg_pkt0);
		TX_SRDS12TO3_Wr01(dev, ptg_pkt0, reg_tp_pkt_size,
				  ION_TP_PKT_SIZE);
		TX_SRDS12TO3_WrFL(dev, ptg_pkt0);
	} else { // ch == 1
#ifndef CONFIG_ION_MASTER_SLAVE /* O26 */
		if (ctop_func && ctop_func->set_ptg_pkt0)
			return ctop_func->set_ptg_pkt0(ext_num);
#else
		return ion_io_slave_set_ptg_pkt0(dev);
#endif
	}

	return 0;
}

static int set_align_cfg(struct te_dev_ion *dev, u8 ch, u8 ext_num,
			 enum ion_io_type type, bool parallel)
{
	u8 v;
	if (ch == 0) {
		TX_SRDS12TO3_RdFL(dev, align_cfg0);
		if (ext_num == 0) {
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_time0,
					  ION_TP_PKT_SIZE);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_en0,
					  0);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_delete_sop0, 0);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_invert_valid0,
					  0);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_fifo0_bypass, 1);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_piso0_gate_en,
					  0);

			v = (type == ION_IO_TYPE_TS) ? 0 : 1;
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_check_sop0, v);

			v = (parallel) ? 0 : 1;
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_sipo0, v);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_piso0, v);
		} else {
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_time1,
					  ION_TP_PKT_SIZE);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_idle_init_en1,
					  0);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_delete_sop1, 0);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_invert_valid1,
					  0);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_fifo1_bypass, 1);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_piso1_gate_en,
					  0);

			v = (type == ION_IO_TYPE_TS) ? 0 : 1;
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_check_sop1, v);

			v = (parallel) ? 0 : 1;
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_sipo1, v);
			TX_SRDS12TO3_Wr01(dev, align_cfg0, reg_mode_piso1, v);
		}
		TX_SRDS12TO3_WrFL(dev, align_cfg0);
	} else { // ch == 1
#ifndef CONFIG_ION_MASTER_SLAVE
		u8 check_sop, is_serial;

		check_sop = (type == ION_IO_TYPE_TS) ? 0 : 1;
		is_serial = (parallel) ? 0 : 1;

		if (ctop_func && ctop_func->set_align_cfg0)
			return ctop_func->set_align_cfg0(ext_num, is_serial,
							 check_sop);
#else
		return ion_io_slave_set_align_cfg(dev, ext_num, type, parallel);
#endif
	}

	return 0;
}

static int set_start_code(struct te_dev_ion *dev, u8 ch, u8 ext_num,
			  enum ion_io_type type)
{
	const u8 code = (type == ION_IO_TYPE_TS) ? 0x47 : 0x7F;
	const u8 v = (type == ION_IO_TYPE_TLV) ? 1 : 0;

	if (ch == 0) {
		TX_SRDS12TO3_RdFL(dev, start_code);
		if (ext_num == 0) {
			TX_SRDS12TO3_Wr01(dev, start_code, reg_start_code0_ext0,
					  code);
		} else {
			TX_SRDS12TO3_Wr01(dev, start_code, reg_start_code0_ext1,
					  code);
		}
		TX_SRDS12TO3_WrFL(dev, start_code);

		TX_SRDS12TO3_RdFL(dev, st_code23_en);
		if (ext_num == 0) {
			TX_SRDS12TO3_Wr01(dev, st_code23_en, reg_tlv_en_ext0,
					  v);
			TX_SRDS12TO3_Wr01(dev, st_code23_en,
					  reg_st_code2_en_ext0, 0);
			TX_SRDS12TO3_Wr01(dev, st_code23_en,
					  reg_st_code3_en_ext0, 0);
		} else {
			TX_SRDS12TO3_Wr01(dev, st_code23_en, reg_tlv_en_ext1,
					  v);
			TX_SRDS12TO3_Wr01(dev, st_code23_en,
					  reg_st_code2_en_ext1, 0);
			TX_SRDS12TO3_Wr01(dev, st_code23_en,
					  reg_st_code3_en_ext1, 0);
		}
		TX_SRDS12TO3_WrFL(dev, st_code23_en);
	} else {
#ifndef CONFIG_ION_MASTER_SLAVE
		if (ctop_func && ctop_func->set_start_code)
			return ctop_func->set_start_code(ext_num, v, code);
#else
		return ion_io_slave_set_start_code(dev, ext_num, type);
#endif
	}

	return 0;
}

static int reg_set_io(struct te_dev_ion *dev, u8 ext_num, enum ion_io_type type,
		      bool parallel)
{
	int i;
	int rc;

	for (i = 0; i < TE_ION_CH_NUM; i++) {
		rc = do_reset(dev, i, ext_num);
		if (rc < 0) {
			log_error("error %d in do_reset", rc);
			goto error;
		}

		rc = set_mux(dev, i, ext_num);
		if (rc < 0) {
			log_error("error %d in set_mux", rc);
			goto error;
		}

		rc = set_ptg_cfg(dev, i);
		if (rc < 0) {
			log_error("error %d in set_ptg_cfg", rc);
			goto error;
		}

		rc = set_ptg_pkt0(dev, i, ext_num);
		if (rc < 0) {
			log_error("error %d in set_ptg_pkt0", rc);
			goto error;
		}

		rc = set_start_code(dev, i, ext_num, type);
		if (rc < 0) {
			log_error("error %d in set_start_code", rc);
			goto error;
		}

		rc = set_align_cfg(dev, i, ext_num, type, parallel);
		if (rc < 0) {
			log_error("error %d in set_align_cfg", rc);
			goto error;
		}
	}

	return 0;

error:
	return rc;
}

int ion_io_reg_set_tp(struct te_dev_ion *dev, u8 ext_num, bool parallel)
{
	int rc;
	log_noti("set_tp(%u:%s)", ext_num, (parallel) ? "parallel" : "serial");

	if (ext_num >= TE_ION_TPI_NUM) {
		log_error("invalid port:%u", ext_num);
		return -EINVAL;
	}

	rc = reg_set_io(dev, ext_num, ION_IO_TYPE_TS, parallel);
	if (rc) {
		log_error("error %d in reg_set_io", rc);
		return rc;
	}

	return 0;
}

int ion_io_reg_set_tlv(struct te_dev_ion *dev, u8 ext_num, bool parallel)
{
	int rc;
	log_noti("set_tlv(%u:%s)", ext_num, (parallel) ? "parallel" : "serial");

	if (!parallel) {
		log_error("critical error; tlv serial not supported");
		return -EPERM;
	}

	if (ext_num >= TE_ION_TPI_NUM) {
		log_error("invalid port:%u", ext_num);
		return -EINVAL;
	}

	rc = reg_set_io(dev, ext_num, ION_IO_TYPE_TLV, parallel);
	if (rc) {
		log_error("error %d in reg_set_io", rc);
		return rc;
	}

	return 0;
}

int ion_io_reg_set_lgc(struct te_dev_ion *dev, u8 ext_num, bool parallel)
{
	log_noti("set_lgc(%u:%s)", ext_num, (parallel) ? "parallel" : "serial");
	log_error("critical error; lgc not supported");
	return -EPERM;
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

int ion_io_reg_init(struct te_dev_ion *dev)
{
	int rc;
#ifdef NO_CTOP
	return 0;
#endif

	switch (lx_chip()) {
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
		dev->ucom_func = &o24_ucom_func;
		ctop_func = NULL;
		break;
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
		dev->ucom_func = &o26_ucom_func;
		ctop_func = &o26_ctop_func;
		break;
#endif
	default:
		dev->ucom_func = NULL;
		ctop_func = NULL;
		WARN_ON(1);
		return -ENODEV;
	}

	rc = reg_init();
	if (rc) {
		log_error("reg_init fail %d", rc);
		return rc;
	}

	return 0;
}

void ion_io_reg_release(struct te_dev_ion *dev)
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
