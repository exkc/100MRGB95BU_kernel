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
 *  sci device driver
 *
 *  @author	Yeonju Lee
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#ifndef _SCI_REG_H_
#define _SCI_REG_H_

#include <asm/io.h>
//#include "sys_reg_base.h"

#include "sci_kapi.h"
#include "sci_impl.h"

enum sci_reg_pwr {
	SCI_REG_POWER_HIGH = 0,
	SCI_REG_POWER_LOW,
};

enum sci_reg_status {
	SCI_REG_STATUS_READY = 0,
	SCI_REG_STATUS_DETECTED,
	SCI_REG_STATUS_ACTIVE,
	SCI_REG_STATUS_FAILED,
};

enum sci_reg_parity {
	SCI_REG_PARITY_EVEN = 0,
	SCI_REG_PARITY_ODD,
};

enum sci_reg_endian {
	SCI_REG_BIG_ENDIAN = 0,
	SCI_REG_LITTLE_ENDIAN,
};

enum sci_reg_err_intr_bit {
	SCI_REG_ERR_INTR_PHY_BIT = 0,
	SCI_REG_ERR_INTR_BYTE_BIT,
	SCI_REG_ERR_INTR_WWT_BIT,
	SCI_REG_ERR_INTR_CWT_BIT,
	SCI_REG_ERR_INTR_BWT_BIT,
	SCI_REG_ERR_INTR_BLOCK_BIT,
};

#define SCI_ERR_INTR_PHY	(0x1 << SCI_REG_ERR_INTR_PHY_BIT)
#define SCI_ERR_INTR_BYTE	(0x1 << SCI_REG_ERR_INTR_BYTE_BIT)
#define SCI_ERR_INTR_WWT	(0x1 << SCI_REG_ERR_INTR_WWT_BIT)
#define SCI_ERR_INTR_CWT	(0x1 << SCI_REG_ERR_INTR_CWT_BIT)
#define SCI_ERR_INTR_BWT	(0x1 << SCI_REG_ERR_INTR_BWT_BIT)
#define SCI_ERR_INTR_BLOCK	(0x1 << SCI_REG_ERR_INTR_BLOCK_BIT)

enum sci_reg_status_bit {
	SCI_REG_STAT_RX_ON_BIT = 0,
	SCI_REG_STAT_TX_ON_BIT,
	SCI_REG_STAT_OK_BIT,
	SCI_REG_STAT_BP_BIT,
};

#define SCI_STAT_RX_ON		(0x1 << SCI_REG_STAT_RX_ON_BIT)
#define SCI_STAT_TX_ON		(0x1 << SCI_REG_STAT_TX_ON_BIT)
#define SCI_STAT_OK		(0x1 << SCI_REG_STAT_OK_BIT)
#define SCI_STAT_BP		(0x1 << SCI_REG_STAT_BP_BIT)

#define IF_MOD_7816_3_COMPLIANT 0
#define IF_MOD_TDA8004          1

#define CLK_PREDIV_1            0
#define CLK_PREDIV_2            1

enum sci_reg_voltage {
	SCI_REG_VOLTAGE_3V = 0,
	SCI_REG_VOLTAGE_5V,
};

#define SCI_REG_DISABLE 0
#define SCI_REG_ENABLE 1

#define BGT_DLY_22_ETU          0
#define BGT_DLY_16_ETU          1

#define PAR_DUR_ETU_1_0         0
#define PAR_DUR_ETU_1_2         1
#define PAR_DUR_ETU_1_4         2
#define PAR_DUR_ETU_1_6         3
#define PAR_DUR_ETU_1_8         4
#define PAR_DUR_ETU_2_0         5

// MODE
#define LBE_BIG_BIT_ENDIAN      0
#define LBE_LITTLE_BIT_ENDIAN   1

#define CONV_REVERSE            0
#define CONV_DIRECT             1

#define EDC_LRC                 0
#define EDC_CRC                 1

enum {
	SCI_REG_BYTE_MODE = 0,
	SCI_REG_BLOCK_MODE,
};

// DLY
#define RST_DUR_40_000_PERIOS   0
#define RST_DUR_43_200_PERIOS   1
#define RST_DUR_46_400_PERIOS   2
#define RST_DUR_49_600_PERIOS   3

#define CLK_DIV_2               0
#define CLK_DIV_4               1
#define CLK_DIV_6               2
#define CLK_DIV_8               3
#define CLK_DIV_12              4
#define CLK_DIV_16              5
#define CLK_DIV_24              6
#define CLK_DIV_32              7

#define CMD_NULL		0
#define CMD_RX_EN		(0x1 << 0)
#define CMD_TX_EN		(0x1 << 1)
#define CMD_POWER_ON		(0x1 << 3)
#define CMD_POWER_OFF		(0x1 << 4)
#define CMD_RESET		(0x1 << 5)	/* Soft Reset */
#define CMD_CLR_FR		(0x1 << 6)	/* Clear Receiver FIFO */
#define CMD_CLR_FT		(0x1 << 7)	/* Clear Transmitter FIFO */

#define REG_STATUS_RX_ON	(0x1 << 0)
#define REG_STATUS_TX_ON	(0x1 << 1)
#define REG_STATUS_OK		(0x1 << 2)
#define REG_STATUS_BP		(0x1 << 3)
#define REG_STATUS_CARD		(0x3 << 4)

struct block_frame_header {
	u8 nad;
	u8 pcb;
	u8 len;
};

/*-----------------------------------------------------------------------------
	0x1a00 sci_data ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 data:8,		//  0: 7
	 rsvd:24;		//  8:31
} SCI_DATA;

/*-----------------------------------------------------------------------------
	0x1a04 sci_nad ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 nad:8,			//  0: 7
	 rsvd:24;		//  8:31
} SCI_NAD;

/*-----------------------------------------------------------------------------
	0x1a08 sci_pcb ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 pcb:8,			//  0: 7
	 rsvd:24;		//  8:31
} SCI_PCB;

/*-----------------------------------------------------------------------------
	0x1a0c sci_len ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 len:8,			//  0: 7
	 rsvd:24;		//  8:31
} SCI_LEN;

/*-----------------------------------------------------------------------------
	0x1a10 sci_edc1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 edc1:8,		//  0: 7
	 rsvd:24;		//  8:31
} SCI_EDC1;

/*-----------------------------------------------------------------------------
	0x1a14 sci_edc2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 edc2:8,		//  0: 7
	 rsvd:24;		//  8:31
} SCI_EDC2;

/*-----------------------------------------------------------------------------
	0x1a18 sci_err ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 phy:1,			//     0
	 byte:1,		//     1
	 wwt:1,			//     2
	 cwt:1,			//     3
	 bwt:1,			//     4
	 block:1,		//     5
	 rsvd:26;		//  6:31
} SCI_ERR;

/*-----------------------------------------------------------------------------
	0x1a1c sci_stat ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 rx_on:1,		//     0
	 tx_on:1,		//     1
	 ok:1,			//     2
	 bp:1,			//     3
	 card:2,		//  4: 5
	 rsvd:26;		//  6:31
} SCI_STAT;

/*-----------------------------------------------------------------------------
	0x1a20 sci_intr_stat ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 frf:1,			//     0
	 frne:1,		//     1
	 ftf:1,			//     2
	 fte:1,			//     3
	 eor:1,			//     4
	 eot:1,			//     5
	 err:1,			//     6
	 cd_pwr:1,		//     7
	 rsvd:24;		//  8:31
} SCI_INTR_STAT;

/*-----------------------------------------------------------------------------
	0x1a24 sci_cmd ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 rx_en:1,		//     0
	 tx_en:1,		//     1
	 rsvd1:1,		//     2
	 pwr_on:1,		//     3
	 pwr_off:1,		//     4
	 reset:1,		//     5
	 clr_fr:1,		//     6
	 clr_ft:1,		//     7
	 rsvd:24;		//  8:31
} SCI_CMD;

/*-----------------------------------------------------------------------------
	0x1a28 sci_fc ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 t_fc_en:1,		//     0
	 r_fc_en:1,		//     1
	 par_retry:3,		//  2: 4
	 rsvd:27;		//  5:31
} SCI_FC;

/*-----------------------------------------------------------------------------
	0x1a2c sci_ext ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 if_mod:1,		//     0
	 p_mon_dly:1,		//     1
	 rsvd:30;		//  2:31
} SCI_EXT;

/*-----------------------------------------------------------------------------
	0x1a40 sci_dds ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 pwr_dly:2,		//  0: 1
	 clk_prediv:1,		//     2
	 vcc_hi:1,		//     3
	 det_hi:1,		//     4
	 p_mon_hi:1,		//     5
	 reset_low:1,		//     6
	 reset_type:1,		//     7
	 rsvd:24;		//  8:31
} SCI_DDS;

/*-----------------------------------------------------------------------------
	0x1a44 sci_set ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 par_dur:3,		//  0: 2
	 bgt_dly:1,		//     3
	 poe:1,			//     4
	 vcc_sel:1,		//     5
	 crc_dir:1,		//     6
	 par_crc:1,		//     7
	 rsvd:24;		//  8:31
} SCI_SET;

/*-----------------------------------------------------------------------------
	0x1a48 sci_conf ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 t_par_en:1,		//     0
	 r_par_en:1,		//     1
	 ato_en:1,		//     2
	 t1_en:1,		//     3
	 deac_en:1,		//     4
	 ts_en:1,		//     5
	 abrt_en:1,		//     6
	 edc_en:1,		//     7
	 rsvd:24;		//  8:31
} SCI_CONF;

/*-----------------------------------------------------------------------------
	0x1a4c sci_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 t:1,			//     0
	 edc:1,			//     1
	 max_rpt:3,		//  2: 4
	 conv:1,		//     5
	 lbe:1,			//     6
	 tx_to_rx:1,		//     7
	 rsvd:24;		//  8:31
} SCI_MODE;

/*-----------------------------------------------------------------------------
	0x1a50 sci_di ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 di:4,			//  0: 3
	 rsvd:28;		//  4:31
} SCI_DI;

/*-----------------------------------------------------------------------------
	0x1a54 sci_tos ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 cwi:4,			//  0: 3
	 bwi:4,			//  4: 7
	 rsvd:24;		//  8:31
} SCI_TOS;

/*-----------------------------------------------------------------------------
	0x1a58 sci_br ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 br:8,			//  0: 7
	 rsvd:24;		//  8:31
} SCI_BR;

/*-----------------------------------------------------------------------------
	0x1a5c sci_ft ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 ft:4,			//  0: 3
	 rsvd:28;		//  4:31
} SCI_FT;

/*-----------------------------------------------------------------------------
	0x1a60 sci_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 frf:1,			//     0
	 frne:1,		//     1
	 ftf:1,			//     2
	 fte:1,			//     3
	 eor:1,			//     4
	 eot:1,			//     5
	 err:1,			//     6
	 cd_pwr:1,		//     7
	 rsvd:24;		//  8:31
} SCI_INTR_MASK;

/*-----------------------------------------------------------------------------
	0x1a64 sci_agt ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 agt:8,			//  0: 7
	 rsvd:24;		//  8:31
} SCI_AGT;

/*-----------------------------------------------------------------------------
	0x1a68 sci_wi ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 wi:7,			//  0: 6
	 rsvd:25;		//  7:31
} SCI_WI;

/*-----------------------------------------------------------------------------
	0x1a6c sci_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 clk_div:3,		//  0: 2
	 rst_dur:2,		//  3: 4
	 rsvd:27;		//  5:31
} SCI_DLY;

/*-----------------------------------------------------------------------------
	0x1a70 sci_pol_crc_l ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 pol_crc_l:8,		//  0: 7
	 rsvd:24;		//  8:31
} SCI_POL_CRC_L;

/*-----------------------------------------------------------------------------
	0x1a74 sci_pol_crc_h ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 pol_crc_h:8,		//  0: 7
	 rsvd:24;		//  8:31
} SCI_POL_CRC_H;

/*-----------------------------------------------------------------------------
	0x1a78 sci_rf_depth ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 rf_depth:6,		//  0: 5
	 rsvd:26;		//  6:31
} SCI_RF_DEPTH;

/*-----------------------------------------------------------------------------
	0x1a7c sci_tf_depth ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	 tf_depth:5,		//  0: 4
	 rsvd:27;		//  5:31
} SCI_TF_DEPTH;

typedef struct {
	SCI_DATA sci_data;	// 0x00 : ''
	SCI_NAD sci_nad;	// 0x04 : ''
	SCI_PCB sci_pcb;	// 0x08 : ''
	SCI_LEN sci_len;	// 0x0C : ''
	SCI_EDC1 sci_edc1;	// 0x10 : ''
	SCI_EDC2 sci_edc2;	// 0x14 : ''
	SCI_ERR sci_err;	// 0x18 : ''
	SCI_STAT sci_stat;	// 0x1C : ''
	SCI_INTR_STAT sci_intr_stat;	// 0x20 : ''
	SCI_CMD sci_cmd;	// 0x24 : ''
	SCI_FC sci_fc;		// 0x28 : ''
	SCI_EXT sci_ext;	// 0x2C : ''
	u32 rsvd[4];		// 0x30~3C : ''
	SCI_DDS sci_dds;	// 0x40 : ''
	SCI_SET sci_set;	// 0x44 : ''
	SCI_CONF sci_conf;	// 0x48 : ''
	SCI_MODE sci_mode;	// 0x4C : ''
	SCI_DI sci_di;		// 0x50 : ''
	SCI_TOS sci_tos;	// 0x54 : ''
	SCI_BR sci_br;		// 0x58 : ''
	SCI_FT sci_ft;		// 0x5C : ''
	SCI_INTR_MASK sci_intr_mask;	// 0x60 : ''
	SCI_AGT sci_agt;	// 0x64 : ''
	SCI_WI sci_wi;		// 0x68 : ''
	SCI_DLY sci_dly;	// 0x6C : ''
	SCI_POL_CRC_L sci_pol_crc_l;	// 0x70 : ''
	SCI_POL_CRC_H sci_pol_crc_h;	// 0x74 : ''
	SCI_RF_DEPTH sci_rf_depth;	// 0x78 : ''
	SCI_TF_DEPTH sci_tf_depth;	// 0x7C : ''
} SCI_REG_T;
/* 29 regs, 29 types */

struct sci_reg_ctrl {
	union {
		u32 *addr;
		SCI_REG_T *reg;
	} shdw;
	union {
		volatile u32 __iomem *addr;
		volatile SCI_REG_T *reg;
	} phys;
	u32 size;
};

/* Reg Access */
#define SCI_REG_SHDW			(g_sci_reg_ctrl.shdw.reg)
#define SCI_REG_PHYS			(g_sci_reg_ctrl.phys.reg)

/* For direct access */
#define SCI_REG_READ32(_r)		__raw_readl((void __iomem *)&(SCI_REG_PHYS->_r))
#define SCI_REG_WRITE32(_r,_v)		__raw_writel(_v, (void __iomem *)&(SCI_REG_PHYS->_r))

#define SCI_RdFL(_r)			((SCI_REG_SHDW->_r)=(SCI_REG_PHYS->_r))
#define SCI_WrFL(_r)			((SCI_REG_PHYS->_r)=(SCI_REG_SHDW->_r))

#define SCI_Rd(_r)			*((volatile u32*)(&(SCI_REG_SHDW->_r)))
#define SCI_Wr(_r,_v)			((SCI_Rd(_r))=((volatile u32)(_v)))


#define SCI_Rd01(_r,_f01,_v01)	\
	do{ (_v01) = (SCI_REG_SHDW->_r._f01); } while(0)
#define SCI_Wr01(_r,_f01,_v01)	\
	do{ (SCI_REG_SHDW->_r._f01) = (_v01); } while(0)


void sci_reg_dump(printf_func_t prfn, void *arg);
#define sci_reg_dump_seq_file(m)	\
	sci_reg_dump((printf_func_t)seq_printf, m);

extern struct sci_reg_ctrl g_sci_reg_ctrl;

void sci_reg_cleanup(void);
int sci_reg_init(void);
void sci_reg_set_default_value(void);
void sci_reg_write(u32 offset, u32 value);
void sci_reg_read_data(u8 *data, u8 len);
void sci_reg_write_data(u8 *data, u8 len);
void sci_reg_set_block_frame_header(u8 nad, u8 pcb, u8 len);
void sci_reg_get_block_frame_header(u8 *nad, u8 *pcb, u8 *len);
u8 sci_reg_get_error_status(void);
u8 sci_reg_get_status(void);
u8 sci_reg_get_card_status(void);
u8 sci_reg_get_interrupt_status(void);
void sci_reg_command(u8 cmd);
void sci_reg_set_flow_control(u8 parity, u8 rx, u8 tx);
void sci_reg_set_ext_sc_chip_if(u8 flag);
void sci_reg_reset_low(u8 flag);
void sci_reg_set_bgt_delay(u8 value);
void sci_reg_set_parity(enum sci_reg_parity poe);
void sci_reg_set_voltage(enum sci_reg_voltage val);
enum sci_reg_voltage sci_reg_get_voltage(void);
void sci_reg_set_mode(u8 flag);
void sci_reg_set_edc(u8 value);
void sci_reg_set_max_repetition(u8 value);
void sci_reg_set_conversion(u8 value);
void sci_reg_set_endian(enum sci_reg_endian endian);
void sci_reg_set_rx_change(bool en);
void sci_reg_set_di(u8 diValue);
void sci_reg_set_timeout(u8 bwi, u8 cwi);
void sci_reg_set_baud(u8 bv, u8 fv);
void sci_reg_enable_interrupt(u8 mask);
void sci_reg_disable_interrupt(u8 mask);
void sci_reg_set_interrupt(u8 mask);
u8 sci_reg_get_interrupt_mask(void);
void sci_reg_set_agt(u8 guard_time);
u8 sci_reg_get_clkdiv(void);
void sci_reg_set_delay(u8 duration, u8 div);
void sci_reg_set_rxfifo_depth(u8 depth);
void sci_reg_set_txfifo_depth(u8 depth);
void sci_reg_power_mon(enum sci_reg_pwr value);
void sci_reg_set_log_mask(int en);
u32 sci_reg_get_log_mask(void);

#endif				/* _SCI_REG_H_  */

/** @} */
