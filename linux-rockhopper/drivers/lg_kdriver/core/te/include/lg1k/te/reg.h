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
 *  te device driver
 *
 *  @author	Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2015-02-09
 *  @note		Additional information.
 */

#ifndef	_LG1K_TE_REG_H_
#define	_LG1K_TE_REG_H_

#include <linux/types.h>

#include <lg1k/te/util.h>

#include "te_kapi.h"



void __iomem *TE_REG_GetBaseAddr(LX_TE_BLOCK_T block);
u32 TE_REG_GetSize(LX_TE_BLOCK_T block);
int TE_REG_SetValue(LX_TE_REG_T *param);
int TE_REG_GetValue(LX_TE_REG_T *param);


enum te_reg_log_bit {
	REG_LOG_TOP_BIT = 0,
	REG_LOG_TPI_BIT,
	REG_LOG_FE_BIT,
	REG_LOG_BE_BIT,
	REG_LOG_UPLOAD_BIT,
	REG_LOG_DSC_BIT,
	REG_LOG_CIPLUS_BIT,
	REG_LOG_CTOP_BIT,
	REG_LOG_ATSC3_BIT,
	REG_LOG_ARIB2_BIT,
	REG_LOG_DUMPER_BIT,
	REG_LOG_VERBOSE_BIT = 31,
};

#define REG_LOG_TOP_MASK	(0x1 << REG_LOG_TOP_BIT)
#define REG_LOG_TPI_MASK	(0x1 << REG_LOG_TPI_BIT)
#define REG_LOG_FE_MASK		(0x1 << REG_LOG_FE_BIT)
#define REG_LOG_BE_MASK		(0x1 << REG_LOG_BE_BIT)
#define	REG_LOG_UPLOAD_MASK	(0x1 << REG_LOG_UPLOAD_BIT)
#define	REG_LOG_DSC_MASK	(0x1 << REG_LOG_DSC_BIT)
#define	REG_LOG_CIPLUS_MASK	(0x1 << REG_LOG_CIPLUS_BIT)
#define	REG_LOG_CTOP_MASK	(0x1 << REG_LOG_CTOP_BIT)
#define	REG_LOG_ATSC3_MASK	(0x1 << REG_LOG_ATSC3_BIT)
#define	REG_LOG_ARIB2_MASK	(0x1 << REG_LOG_ARIB2_BIT)
#define	REG_LOG_DUMPER_MASK	(0x1 << REG_LOG_DUMPER_BIT)
#define	REG_LOG_VERBOSE_MASK	(0x1 << REG_LOG_VERBOSE_BIT)

int TE_REG_EnableLogMask(enum te_reg_log_bit bit);
int TE_REG_DisableLogMask(enum te_reg_log_bit bit);
int TE_REG_SetLogMask(u32 mask);
u32 TE_REG_GetLogMask(void);

void te_reg_dump(LX_TE_BLOCK_T block, printf_func_t prfn, void *arg);
#define te_reg_dump_seq_file(b,m) \
  te_reg_dump(b, (printf_func_t)seq_printf, m)


struct reg_bit_type_conv {
	u32 bit;
	u32 type;
};


u32 te_reg_type_to_bits(const struct reg_bit_type_conv *list, u32 size, u32 v);
u32 te_reg_bits_to_type(const struct reg_bit_type_conv *list, u32 size, u32 v);

#define reg_type_to_bits(l, v) te_reg_type_to_bits(l, ARRAY_SIZE(l), v)
#define reg_bits_to_type(l, v) te_reg_bits_to_type(l, ARRAY_SIZE(l), v)


enum te_reg_tpo_mode {
	TPO_FORMAT_SERIAL = 0,
	TPO_FORMAT_PARALLEL,
};

enum te_reg_tpi_port {
	TPI_INT_DEMOD = 0,
	TPI_EXT_DEMOD0,
	TPI_EXT_DEMOD1,
	TPI_EXT_DEMOD2,
	TPI_CAM_LOOP_BACK,
	TPI_CAM_INPUT,
	TPI_DISABLE,
	TPI_INVALID,
};

/******* CTOP *******/
enum te_reg_ci_input {
	CI_INPUT_SRC_NONE = 0,
	CI_INPUT_SRC_IN_DEMOD,
	CI_INPUT_SRC_EXT_INPUT0,
	CI_INPUT_SRC_EXT_INPUT1,
	CI_INPUT_SRC_TE,
	CI_INPUT_SRC_INVALID,
};

enum te_reg_port_dir {
	PORT_DIR_INPUT = 0,
	PORT_DIR_OUTPUT,
};

enum te_reg_uart_type {
	TE_UART_CPU = 0,
	TE_UART_MCU0,
	TE_UART_MCU1,
};

enum te_reg_jtag_type {
	TE_JTAG_CPU = 0,
	TE_JTAG_MCU0,
	TE_JTAG_MCU1,
};

enum te_reg_input_mux {
	TE_INPUT_MUX_NORMAL = 0,
	TE_INPUT_MUX_3_SERIAL,
};

enum te_reg_stcc_src {
	STCC_CLK_SRC_DCO = 0,
	STCC_CLK_SRC_FIXED,	/* 27Mhz */
};

enum te_reg_out_clk {
	OUTPUT_CLK_198MHZ = 0,
	OUTPUT_CLK_99MHZ,
	OUTPUT_CLK_66MHZ,
	OUTPUT_CLK_49MHZ,
	OUTPUT_CLK_33MHZ,
	OUTPUT_CLK_24MHZ,
	OUTPUT_CLK_12MHZ,
	OUTPUT_CLK_10MHZ,
	OUTPUT_CLK_8MHZ,
	OUTPUT_CLK_6MHZ,
	OUTPUT_CLK_4MHZ,
	OUTPUT_CLK_2MHZ,
	OUTPUT_CLK_INVALID,
};

int TE_REG_CTOP_Init(void);
int TE_REG_CTOP_SetInitValue(void);
int TE_REG_SetCiInput(enum te_reg_ci_input src);
int TE_REG_GetCiInput(enum te_reg_ci_input *src);
int TE_REG_SetCiOutClk(enum te_reg_out_clk clk);
int TE_REG_SetStccClockSource(u8 ch, enum te_reg_stcc_src src);
int TE_REG_SetInOutPort(enum te_reg_tpi_port port, enum te_reg_port_dir dir,
			enum te_reg_tpo_mode mode, enum te_reg_out_clk clk);
int TE_REG_GetDcoInputClock(u32 *freq);
int TE_REG_SelectUart(enum te_reg_uart_type uart);
int TE_REG_SelectJtag(enum te_reg_jtag_type jtag);
int TE_REG_SetGlitchFreeFilter(bool en);
int TE_REG_SetInputMux(enum te_reg_input_mux type);
int TE_REG_ClockGate(bool disable);

/************ TOP ************/
enum te_reg_top_intr_bit {
	TOP_INTR_FE_BIT = 0,
	TOP_INTR_TSBUF_BIT,
	TOP_INTR_STCC_BIT,
	TOP_INTR_UPLOAD0_BIT,
	TOP_INTR_UPLOAD1_BIT,
	TOP_INTR_DSC0_BIT,
	TOP_INTR_DSC1_BIT,
	TOP_INTR_BE_BIT,
	TOP_INTR_CIPLUS_BIT,
	TOP_INTR_A3_BIT,
	TOP_INTR_DUMPER_BIT,
	TOP_INTR_ARIB2_BIT,
	TOP_INTR_BIT_MAX,
};

/* BIT MASK VALUE */
#define TOP_INTR_FE		(0x1 << TOP_INTR_FE_BIT)
#define TOP_INTR_TSBUF		(0x1 << TOP_INTR_TSBUF_BIT)
#define TOP_INTR_STCC		(0x1 << TOP_INTR_STCC_BIT)
#define TOP_INTR_UPLOAD0	(0x1 << TOP_INTR_UPLOAD0_BIT)
#define TOP_INTR_UPLOAD1	(0x1 << TOP_INTR_UPLOAD1_BIT)
#define TOP_INTR_DSC0		(0x1 << TOP_INTR_DSC0_BIT)
#define TOP_INTR_DSC1		(0x1 << TOP_INTR_DSC1_BIT)
#define TOP_INTR_BE		(0x1 << TOP_INTR_BE_BIT)
#define TOP_INTR_CIPLUS		(0x1 << TOP_INTR_CIPLUS_BIT)
#define TOP_INTR_A3		(0x1 << TOP_INTR_A3_BIT)
#define TOP_INTR_DUMPER		(0x1 << TOP_INTR_DUMPER_BIT)
#define TOP_INTR_ARIB2		(0x1 << TOP_INTR_ARIB2_BIT)


enum te_reg_channel_src {
	CH_SRC_DISABLE = 0,
	CH_SRC_TPI_INT_DEMOD,
	CH_SRC_TPI_EXT_DEMOD0,
	CH_SRC_TPI_EXT_DEMOD1,
	CH_SRC_TPI_EXT_DEMOD2,
	CH_SRC_TPI_CAM_LOOP_BACK,
	CH_SRC_TPI_CAM_INPUT,
	CH_SRC_UPLOAD0,
	CH_SRC_UPLOAD1,
	CH_SRC_CIP_DEMUX0,
	CH_SRC_CIP_DEMUX1,
	CH_SRC_CIP_DEMUX2,
	CH_SRC_AUDIO_PES0,
	CH_SRC_AUDIO_PES1,
	CH_SRC_VIDEO_PES0,
	CH_SRC_VIDEO_PES1,
	CH_SRC_LGDEMOD,		/* it is used only for m16+ */
	CH_SRC_INVALID,
};

enum te_reg_upload_ready_src {
	UPLOAD_READY_SRC_TSBUF0 = 0,
	UPLOAD_READY_SRC_TSBUF1,
	UPLOAD_READY_SRC_TSBUF2,
	UPLOAD_READY_SRC_TSBUF3,
	UPLOAD_READY_SRC_SUB_TSBUF0,
	UPLOAD_READY_SRC_SUB_TSBUF1,
	UPLOAD_READY_SRC_TPO_BUF,
	UPLOAD_READY_SRC_A3_CH0,
	UPLOAD_READY_SRC_A3_CH1,
	UPLOAD_READY_SRC_A3_CH2,
	UPLOAD_READY_SRC_A3_CH3,
	UPLOAD_READY_ALWAYS,
};



enum te_reg_engine_mode {
	ENGINE_MODE_ATSC3 = 0,
	ENGINE_MODE_ARIB2,
	ENGINE_MODE_CI20,
	ENGINE_MODE_MAX,
};
int TE_REG_TOP_Init(void);
int TE_REG_SetIntrEnable(u32 val, bool en);
int TE_REG_ClearIntr(u32 val);
int TE_REG_GetIntrStatus(u32 *val);

int TE_REG_SetChannelSource(u8 ch, enum te_reg_channel_src src);
int TE_REG_GetChannelSource(u8 ch, enum te_reg_channel_src *src);
int TE_REG_SetUploadReadySel(u8 idx, enum te_reg_upload_ready_src src);
int TE_REG_SetOutputPort(enum te_reg_channel_src src, enum te_reg_tpo_mode mode,
			 bool clk_inv, bool en);

int TE_REG_SetDcoFcw(u32 val, u32 input_clock);
int TE_REG_SetUartMux(u32 val);
int TE_REG_SetEngineChannelSource(u8 ch, enum te_reg_channel_src src);
int TE_REG_GetEngineChannelSource(u8 ch, enum te_reg_channel_src *src);
int TE_REG_SetEngineMode(enum te_reg_engine_mode mode);
int TE_REG_GetEngineMode(enum te_reg_engine_mode *mode);

int te_reg_set_ci_input(enum te_reg_ci_input src);
int te_reg_get_ci_input(enum te_reg_ci_input *src);

const char *te_reg_channel_src_to_str(enum te_reg_channel_src src);
const char *te_reg_top_intr_bit_to_str(enum te_reg_top_intr_bit bit);
/************ TPI ************/
enum te_reg_tpi_mode {
	TPI_CONF_INPUT_SERIAL = 0,
	TPI_CONF_INPUT_PARALLEL,
};

enum te_reg_tpi_type {
	TPI_CONF_STREAM_TS = 0,
	TPI_CONF_STREAM_ATSC3,
	TPI_CONF_STREAM_ARIB2,
	TPI_CONF_STREAM_BYPASS,
};

enum te_reg_tpi_sync {		//Integrate all sync mode here
	TPI_SYNC_VALIDONLY = 0,
	TPI_SYNC_SOP,
	TPI_SYNC_SOP_FIRSTBIT,	//serial only

	TPI_SYNC_SYNCBYTE,	//MPEG2 TS only
	TPI_SYNC_SOP_SYNCBYTE,	//MPEG2 TS only

	TPI_SYNC_MAGIC,		//TLV, Bypass
	TPI_SYNC_SOP_MAGIC,	//TLV, Bypass
	TPI_SYNC_BYPASS,
};

struct te_reg_tpi_conf {
	bool enable;
	enum te_reg_tpi_type stream_type;	/* MPEG2 TS or ARIB2.0 TLV */
	u8 input_mode;
	u8 s2p_sync_mode;	/* serial to parallel sync mode */
	u8 sync_mode;		/* sync mode(only for parallel from M16P3) */

	u8 num_drop;
	u8 num_found;
};

struct te_reg_tpi_status {
	u8 stream_type;		/* M16P3 ~ */

	u8 enable;
	u8 input_mode;
	u8 sync_type;		/* TP synchonizer mode */
	u8 s2p_mode;		/* serial to paralle mode if input mode is serial */
	u8 fifo_full;

	u8 num_of_sync_found;	/* Numbfer of sync should be found for sync */
	u8 num_of_sync_drop;	/* Numbfer of sync should be dropped for sync */
	u8 sync_drop;		/* check sync drop was appeared or not */

	u32 pkt_count;		/* all packets from demod */
	u32 tei_count;		/* transport error indicator count */
	u8 tei_enable;

	u32 reg_value[3];
};

int TE_REG_TPI_Init(void);
int TE_REG_SetTpiConf(enum te_reg_tpi_port port, struct te_reg_tpi_conf *conf);
int TE_REG_SetTpiEnable(enum te_reg_tpi_port port, bool en);
int TE_REG_GetTpiStatus(enum te_reg_tpi_port port,
			struct te_reg_tpi_status *status);

int TE_REG_SetCiplusInput(u8 idx, enum te_reg_tpi_port port);
int TE_REG_GetCiplusInput(u8 idx, enum te_reg_tpi_port *port);
int TE_REG_SetCiInputTpi(enum te_reg_tpi_port port);
int TE_REG_GetCiInputTpi(enum te_reg_tpi_port *port);

const char *te_reg_tpi_port_to_str(enum te_reg_tpi_port port);

/************ FE TSBUF ************/
enum te_reg_tsbuf_intr_bit {
	TSBUF_PACKET_INTR_CH0_BIT = 0,
	TSBUF_PACKET_INTR_CH1_BIT,
	TSBUF_PACKET_INTR_CH2_BIT,
	TSBUF_PACKET_INTR_CH3_BIT,
	TSBUF_PACKET_INTR_SUB_CH0_BIT,
	TSBUF_PACKET_INTR_SUB_CH1_BIT,
	TSBUF_FULL_INTR_CH0_BIT,
	TSBUF_FULL_INTR_CH1_BIT,
	TSBUF_FULL_INTR_CH2_BIT,
	TSBUF_FULL_INTR_CH3_BIT,
	TSBUF_FULL_INTR_SUB_CH0_BIT,
	TSBUF_FULL_INTR_SUB_CH1_BIT,
	TSBUF_OVERFLOW_INTR_CH0_BIT,
	TSBUF_OVERFLOW_INTR_CH1_BIT,
	TSBUF_OVERFLOW_INTR_CH2_BIT,
	TSBUF_OVERFLOW_INTR_CH3_BIT,
	TSBUF_OVERFLOW_INTR_SUB_CH0_BIT,
	TSBUF_OVERFLOW_INTR_SUB_CH1_BIT,
};

#define TSBUF_PACKET_INTR_CH0		(0x1 << TSBUF_PACKET_INTR_CH0_BIT)
#define TSBUF_PACKET_INTR_CH1		(0x1 << TSBUF_PACKET_INTR_CH1_BIT)
#define TSBUF_PACKET_INTR_CH2		(0x1 << TSBUF_PACKET_INTR_CH2_BIT)
#define TSBUF_PACKET_INTR_CH3		(0x1 << TSBUF_PACKET_INTR_CH3_BIT)
#define TSBUF_PACKET_INTR_SUB_CH0	(0x1 << TSBUF_PACKET_INTR_SUB_CH0_BIT)
#define TSBUF_PACKET_INTR_SUB_CH1	(0x1 << TSBUF_PACKET_INTR_SUB_CH1_BIT)
#define TSBUF_FULL_INTR_CH0		(0x1 << TSBUF_FULL_INTR_CH0_BIT)
#define TSBUF_FULL_INTR_CH1		(0x1 << TSBUF_FULL_INTR_CH1_BIT)
#define TSBUF_FULL_INTR_CH2		(0x1 << TSBUF_FULL_INTR_CH2_BIT)
#define TSBUF_FULL_INTR_CH3		(0x1 << TSBUF_FULL_INTR_CH3_BIT)
#define TSBUF_FULL_INTR_SUB_CH0		(0x1 << TSBUF_FULL_INTR_SUB_CH0_BIT)
#define TSBUF_FULL_INTR_SUB_CH1		(0x1 << TSBUF_FULL_INTR_SUB_CH1_BIT)
#define TSBUF_OVERFLOW_INTR_CH0		(0x1 << TSBUF_OVERFLOW_INTR_CH0_BIT)
#define TSBUF_OVERFLOW_INTR_CH1		(0x1 << TSBUF_OVERFLOW_INTR_CH1_BIT)
#define TSBUF_OVERFLOW_INTR_CH2		(0x1 << TSBUF_OVERFLOW_INTR_CH2_BIT)
#define TSBUF_OVERFLOW_INTR_CH3		(0x1 << TSBUF_OVERFLOW_INTR_CH3_BIT)
#define TSBUF_OVERFLOW_INTR_SUB_CH0	(0x1 << TSBUF_OVERFLOW_INTR_SUB_CH0_BIT)
#define TSBUF_OVERFLOW_INTR_SUB_CH1	(0x1 << TSBUF_OVERFLOW_INTR_SUB_CH1_BIT)

#define TSBUF_PACKET_INTR_MASK \
  (TSBUF_PACKET_INTR_CH0 | TSBUF_PACKET_INTR_CH1 | \
   TSBUF_PACKET_INTR_CH2 | TSBUF_PACKET_INTR_CH3)

int TE_REG_FE_TSBUF_Init(void);
int TE_REG_ResetChannelInputBuffer(u8 ch);
int TE_REG_ResetPidFilter(u8 ch);
int TE_REG_GetChannelInputBufferWptr(u8 ch, u32 *wptr);
int TE_REG_SetTsBufIntrEnable(u32 val, bool en);
int TE_REG_GetTsBufIntrStatus(u32 *val);
int TE_REG_ClearTsBufIntr(u32 val);

/************ FE STCC ************/
enum te_reg_pes_dest {
	PES_DEST_VIDEO = 0x10,
	PES_DEST_VIDEO0 = 0x10,
	PES_DEST_VIDEO1 = 0x11,
	PES_DEST_AUDIO = 0x20,
	PES_DEST_AUDIO0 = 0x20,
	PES_DEST_AUDIO1 = 0x21,
};

enum te_reg_pcr_mode {
	PCR_MODE_ALWAYSCOPY = 0,	//Submode disabled always copy stcc
	PCR_MODE_AUTORATE,	//Submode enabled and HW controled
	PCR_MODE_MANUAL,	//Submode enabled and CPU can control rate(M16+ or later)
	PCR_MODE_GSTCCMODE,	//GSTCC mode (use GSTCC instead of stcc)
};

enum te_reg_gstcc_mode {
	GSTCC_MODE_EXTINCR = 0,
	GSTCC_MODE_UNITSTEP,
};

enum te_reg_fe_stcc_intr_bit {
	FE_STCC_INTR_CH0_PCR_BIT = 0,
	FE_STCC_INTR_CH1_PCR_BIT,
	FE_STCC_INTR_CH2_PCR_BIT,
	FE_STCC_INTR_CH3_PCR_BIT,
	FE_STCC_INTR_CH0_DISCONT_BIT,
	FE_STCC_INTR_CH1_DISCONT_BIT,
	FE_STCC_INTR_CH2_DISCONT_BIT,
	FE_STCC_INTR_CH3_DISCONT_BIT,
	FE_STCC_INTR_GTIMER0_BIT,
	FE_STCC_INTR_GTIMER1_BIT,
	/* M16A0 only */
	FE_STCC_INTR_CH0_BUFFULL_BIT,
	FE_STCC_INTR_CH1_BUFFULL_BIT,
	FE_STCC_INTR_CH2_BUFFULL_BIT,
	FE_STCC_INTR_CH3_BUFFULL_BIT,
	FE_STCC_INTR_SUBCH0_BUFFULL_BIT,
	FE_STCC_INTR_SUBCH1_BUFFULL_BIT,
};

#define FE_STCC_INTR_CH0_PCR		(0x1 << FE_STCC_INTR_CH0_PCR_BIT)
#define FE_STCC_INTR_CH1_PCR		(0x1 << FE_STCC_INTR_CH1_PCR_BIT)
#define FE_STCC_INTR_CH2_PCR		(0x1 << FE_STCC_INTR_CH2_PCR_BIT)
#define FE_STCC_INTR_CH3_PCR		(0x1 << FE_STCC_INTR_CH3_PCR_BIT)
#define FE_STCC_INTR_PCR_MASK \
  (FE_STCC_INTR_CH0_PCR | FE_STCC_INTR_CH1_PCR | \
   FE_STCC_INTR_CH2_PCR | FE_STCC_INTR_CH3_PCR)

#define FE_STCC_INTR_CH0_DISCONT	(0x1 << FE_STCC_INTR_CH0_DISCONT_BIT)
#define FE_STCC_INTR_CH1_DISCONT	(0x1 << FE_STCC_INTR_CH1_DISCONT_BIT)
#define FE_STCC_INTR_CH2_DISCONT	(0x1 << FE_STCC_INTR_CH2_DISCONT_BIT)
#define FE_STCC_INTR_CH3_DISCONT	(0x1 << FE_STCC_INTR_CH3_DISCONT_BIT)
#define FE_STCC_INTR_DISCONT_MASK \
  (FE_STCC_INTR_CH0_DISCONT | FE_STCC_INTR_CH1_DISCONT | \
   FE_STCC_INTR_CH2_DISCONT | FE_STCC_INTR_CH3_DISCONT)

#define FE_STCC_INTR_GTIMER0		(0x1 << FE_STCC_INTR_GTIMER0_BIT)
#define FE_STCC_INTR_GTIMER1		(0x1 << FE_STCC_INTR_GTIMER1_BIT)

/* M16A0 only */
#define FE_STCC_INTR_CH0_BUFFULL	(0x1 << FE_STCC_INTR_CH0_BUFFULL_BIT)
#define FE_STCC_INTR_CH1_BUFFULL	(0x1 << FE_STCC_INTR_CH1_BUFFULL_BIT)
#define FE_STCC_INTR_CH2_BUFFULL	(0x1 << FE_STCC_INTR_CH2_BUFFULL_BIT)
#define FE_STCC_INTR_CH3_BUFFULL	(0x1 << FE_STCC_INTR_CH3_BUFFULL_BIT)
#define FE_STCC_INTR_SUBCH0_BUFFULL	(0x1 << FE_STCC_INTR_SUBCH0_BUFFULL_BIT)
#define FE_STCC_INTR_SUBCH1_BUFFULL	(0x1 << FE_STCC_INTR_SUBCH1_BUFFULL_BIT)


int TE_REG_FE_STCC_Init(void);
int TE_REG_SetStccSource(enum te_reg_pes_dest dest, u8 src);
int TE_REG_SetPcrPid(u8 ch, u16 pid, bool en);
int TE_REG_EnableStcc(u8 ch, bool en);
int TE_REG_SetStccMain(u8 ch, bool main);
int TE_REG_SetStccSubMode(u8 ch, enum te_reg_pcr_mode pcr_mode);
int TE_REG_SetStccSubPcrUnitStep(u8 ch, int step);
int TE_REG_ResetStcc(u8 ch);
int TE_REG_SetStccEnableCopy(u8 ch);
int TE_REG_SetStccLatchEnable(u8 ch, bool en);
int TE_REG_SetPcrJitter(u8 ch, bool detection, u32 jitter);
int TE_REG_SetStcc(u8 ch, u32 base_32, u32 base_31_0);
int TE_REG_GetLiveStcc(u8 ch, u32 *base_32, u32 *base_31_0, u32 *ext);
int TE_REG_GetLatchedStcc(u8 ch, u32 *base_32, u32 *base_31_0, u32 *ext);
int TE_REG_GetLatchedPcr(u8 ch, u32 *base_32, u32 *base_31_0, u32 *ext);
int TE_REG_SetGstcc(u8 idx, u32 base_32, u32 base_31_0, u32 ext);
int TE_REG_ResetGstcc(u8 idx);
int TE_REG_SetGstccConf(u8 idx, u8 ext_incr, u32 ext_unit, u8 en);
int TE_REG_GetGstcc(u8 idx, u32 *base_32, u32 *base_31_0, u32 *ext);
int TE_REG_SetGstccMode(u8 idx, enum te_reg_gstcc_mode mode);
int TE_REG_SetGstccUnitStep(u8 idx, int step);
int TE_REG_GetLatchedGstcc(u8 idx, u32 *base_32, u32 *base_31_0, u32 *ext);

int TE_REG_SetFeIntrEnable(u32 val, bool en);
int TE_REG_GetFeIntrStatus(u32 *val);
int TE_REG_ClearFeIntr(u32 val);

int TE_REG_SetA3LatchEnable(u8 ch, u8 idx, bool en);
int TE_REG_SetGstccLatchSource(u8 a3_ch, u8 idx);

/************ FE PIDF ************/
enum te_reg_pidf_type {
	PIDF_TYPE_AUDIO = 0x0,
	PIDF_TYPE_VIDEO,
	PIDF_TYPE_SECTION,
	PIDF_TYPE_DATA,
	PIDF_TYPE_PIE,
	PIDF_TYPE_TSHEADER,
};

enum te_reg_pidf_bypass_type {
	PIDF_BYPASS_DISABLE = 0,
	PIDF_BYPASS_TYPE_188BYTE,
	PIDF_BYPASS_TYPE_192BYTE,
};

struct te_reg_pidf_conf {
	bool en;
	u16 pid;
	u8 ch;
	enum te_reg_pidf_type type;
	bool out_en;
	u8 out_idx;
	bool dn_en;
	bool temi_en;
};

struct te_reg_pidf_status {
	bool en;
	u16 pid;
	u8 ch;
	enum te_reg_pidf_type type;
	bool out_en;
	u8 out_idx;
	bool dn_en;
	bool temi_en;

	enum te_reg_pidf_bypass_type bypass_mode;

	u32 val;		//Read the register value
};

int TE_REG_FE_PIDF_Init(void);
int TE_REG_GetChannelPktCount(u8 ch, u32 *val);
int TE_REG_SetChannelDownloadIdx(u8 ch, u8 idx);
int TE_REG_SetPidFilter(u8 idx, struct te_reg_pidf_conf *conf);
int TE_REG_SetSubPidFilter(u8 idx, struct te_reg_pidf_conf *conf);
int TE_REG_ClearPidFilter(u8 idx);
int TE_REG_GetPidFilter(u8 idx, struct te_reg_pidf_status *s);
int TE_REG_GetSubPidFilter(u8 idx, struct te_reg_pidf_status *s);
int TE_REG_SetSubpidfBypass(u8 idx, enum te_reg_pidf_bypass_type type);
int TE_REG_SetPidfBypass(u8 ch, enum te_reg_pidf_bypass_type type);
int TE_REG_EnablePidFilter(u8 idx);
int TE_REG_DisablePidFilter(u8 idx);
int TE_REG_EnablePIDFDownload(u8 ch, bool en);

/************ BE ************/
enum te_reg_endian {
	TE_REG_BIG_ENDIAN = 0,
	TE_REG_LITTLE_ENDIAN,
};

#define BE_AXI_BIG_ENDIAN	TE_REG_BIG_ENDIAN
#define BE_AXI_LITTLE_ENDIAN	TE_REG_LITTLE_ENDIAN


enum te_reg_timestamp {
	TIMESTAMP_MODE_16BITS = 0,
	TIMESTAMP_MODE_32BITS,
};

enum te_reg_download_mode {
	DOWNLOAD_MODE_192BYTE = 0,
	DOWNLOAD_MODE_188BYTE,
};

enum te_reg_be_intr_bit {
	BE_INTR_SEGMENT_DN0_BIT = 0,
	BE_INTR_SEGMENT_DN1_BIT,
	BE_INTR_BE_DONE_BIT,
	BE_INTR_CLEAR_TSBUFFER_BIT,	// Single packet inside clear tsbuffer
	BE_INTR_PIE_DETECT_BIT,
	BE_INTR_CLEAR_TSBUFFER_FULL_BIT,
};

#define BE_INTR_SEGMENT_DN0		(0x1 << BE_INTR_SEGMENT_DN0_BIT)
#define BE_INTR_SEGMENT_DN1		(0x1 << BE_INTR_SEGMENT_DN1_BIT)
#define BE_INTR_BE_DONE			(0x1 << BE_INTR_BE_DONE_BIT)
#define BE_INTR_CLEAR_TSBUFFER		(0x1 << BE_INTR_CLEAR_TSBUFFER_BIT)
#define BE_INTR_PIE_DETECT		(0x1 << BE_INTR_PIE_DETECT_BIT)
#define BE_INTR_CLEAR_TSBUFFER_FULL	(0x1 << BE_INTR_CLEAR_TSBUFFER_FULL_BIT)


int TE_REG_BE_Init(void);
int TE_REG_SetChannelDownloadEnable(u8 idx, u8 dn_src, bool en);
int TE_REG_SetBeAxiEndian(enum te_reg_endian wr, enum te_reg_endian rd);
int TE_REG_SetDownloadTimeStampMode(enum te_reg_timestamp mode);
int TE_REG_SetHwPieEnable(bool en);
int TE_REG_SetHwDownloadEnable(bool en);
int TE_REG_GetHwDownloadEnable(bool *en);
int TE_REG_SetDownloadBuffer(u8 idx, u32 start, u32 end);
int TE_REG_GetDownloadWptr(u8 idx, u32 *wptr);
int TE_REG_SetDownloadRptr(u8 idx, u32 rptr);
int TE_REG_SetDownloadSegmentSize(u8 idx, u32 size);

int TE_REG_SetPieBuffer(u8 idx, u32 start, u32 end);
int TE_REG_GetPieWptr(u8 idx, u32 *wptr);
int TE_REG_SetPieRptr(u8 idx, u32 rptr);
int TE_REG_SetPieDetect(u8 idx, u8 num, u32 mask, u32 val, bool en);
int TE_REG_DisablePieDetect(u8 idx);
int TE_REG_SetPiePid(u8 idx, u16 pid);
int TE_REG_SetDownloadMode(u8 idx, enum te_reg_download_mode mode);

int TE_REG_SetBeIntrEnable(u32 val, bool en);
int TE_REG_GetBeIntrStatus(u32 *value);
int TE_REG_ClearBeIntr(u32 value);

/************ UPLOAD ************/
enum te_reg_up_intr_bit {
	UPLOAD_INTR_EMPTY_BIT = 0,	/* upload buffer empty */
};

#define UPLOAD_INTR_EMPTY	(0x1 << UPLOAD_INTR_EMPTY_BIT)

enum te_reg_up_trick_mode {
	UPLOAD_TRICK_MODE_NORMAL = 0,	/* x1 */
	UPLOAD_TRICK_MODE_2X,	/* x2 speed */
	UPLOAD_TRICK_MODE_1DIV2,	/* 1/2 speed */
	UPLOAD_TRICK_MODE_1DIV4,	/* 1/4 speed */
};

enum te_reg_up_wait_mode {
	UPLOAD_WAIT_MODE_WAIT_CYCLE = 0,
	UPLOAD_WAIT_MODE_TSD,	/* time stamp difference */
	UPLOAD_WAIT_MODE_TIMESTAMP,	/* 4 byte timestamp */
};

enum te_reg_up_pkt_type {
	UPLOAD_PKT_TYPE_188BYTE = 0,
	UPLOAD_PKT_TYPE_192BYTE
};

int TE_REG_UPLOAD_Init(void);
int TE_REG_SetUploadAutoCopyEn(u8 idx, bool en);
int TE_REG_SetUploadTrickMode(u8 idx, enum te_reg_up_trick_mode mode);
int TE_REG_SetUploadWaitMode(u8 idx, enum te_reg_up_wait_mode mode);
int TE_REG_SetUploadPacketType(u8 idx, enum te_reg_up_pkt_type type);
int TE_REG_ResetUpload(u8 idx);
int TE_REG_SetUploadEnable(u8 idx, bool en);
int TE_REG_SetUploadPause(u8 idx, bool en);
int TE_REG_SetUploadMaxJitter(u8 idx, u32 val);
int TE_REG_SetUploadWaitCycle(u8 idx, u32 val);
int TE_REG_SetUploadBuffer(u8 idx, u32 start, u32 end);
int TE_REG_SetUploadWptr(u8 idx, u32 wptr);
int TE_REG_GetUploadRptr(u8 idx, u32 *rptr);

int TE_REG_SetUploadIntrEnable(u8 idx, u32 val, bool en);
int TE_REG_GetUploadIntrStatus(u8 idx, u32 *val);
int TE_REG_ClearUploadIntr(u8 idx, u32 val);

int te_reg_upload_set_tlv_enable(u8 idx, bool en);
int te_reg_upload_set_tlv_mode(u8 idx, u8 syncbyte, u8 mask);

/************ CIPLUS ************/
enum te_reg_cip_src {
	CIP_SRC_DEMOD = 0,
	CIP_SRC_MCU = 1,
	CIP_SRC_INVALID,
};

enum te_reg_cip_dest {
	CIP_INPUT_DEST_HW = 0,
	CIP_INPUT_DEST_MCU = 1,
};

#if 0	// REMOVE if not use
enum {
	CIP_DEMUX_OUT0 = 0,
	CIP_DEMUX_OUT1 = 1,
	CIP_DEMUX_OUT2 = 2,
	CIP_DEMUX_NONE,		// TODO: check
	CIP_DEMUX_OUTMAX
};
#endif

enum te_reg_cip_endian {
	CIP_ENDIAN_NORMAL = 0,
	CIP_ENDIAN_BYTESWAP = 1,
	CIP_ENDIAN_WORDSWAP = 2,
	CIP_ENDIAN_MAX = 3,
};

enum te_reg_cip_dmx_dest {
	CIP_DEMUX_DEST_DISABLE = 0,
	CIP_DEMUX_DEST_HW = 1,
	CIP_DEMUX_DEST_MCU = 2,
	CIP_DEMUX_DEST_BOTH = 3,
	CIP_DEMUX_DEST_INVALID,
};

int TE_REG_CIPLUS_Init(void);
int TE_REG_SetCiplusDemuxDestination(u8 idx, enum te_reg_cip_dmx_dest dest);
int TE_REG_GetCiplusDemuxDestination(u8 idx, enum te_reg_cip_dmx_dest *dest);
int TE_REG_SetCiplusDemuxSyncbyte(u8 idx, u8 syncbyte);
int TE_REG_GetCiplusDemuxSyncbyte(u8 idx, u8 *syncbyte);
int TE_REG_ResetCiplusDemux(u8 ch);

int TE_REG_SetCiplusEndian(enum te_reg_cip_endian type);

int TE_REG_ResetCiplusInbuf(u8 ch);
int TE_REG_SetCiplusInbufSource(u8 ch, enum te_reg_cip_src src);
int TE_REG_SetCiplusInbufDestination(u8 ch, enum te_reg_cip_dest dest);
int TE_REG_SetCiplusInbufFullLevel(u8 ch, u8 full_level);
int TE_REG_SetCiplusInbufWidx(u8 ch, u8 wdx);

int TE_REG_ResetCiplusOutbuf(void);
int TE_REG_SetCiplusOutbufSource(enum te_reg_cip_src src);
int TE_REG_SetCiplusOutbufDestination(enum te_reg_cip_dest dest);
int TE_REG_SetCiplusOutbufFullLevel(u8 full_level);
int TE_REG_ResetCiplusInput(u8 ch);

int TE_REG_SetCiplusInputBypass(u8 ch, bool bypass_en);
int TE_REG_SetCiplusInputTeiDrop(u8 ch, bool en);
int TE_REG_SetCiplusInputSyncbyte(u8 ch, bool en, u8 syncbyte);
int TE_REG_SetCiplusQueueEnable(u8 ch, bool en);

int TE_REG_SetCiplusPIDF(u8 ch, u8 idx, u16 pid, bool en);
int TE_REG_GetCiplusTPOBitrate(u16 *bitrate);
int TE_REG_GetCiplusTPOPacketCnt(u32 *pkt_cnt);

/************ DUMPER ************/
enum te_reg_dumper_intr_bit {
	DUMPER_INTR_META_WRITE_CH0_BIT = 0,
	DUMPER_INTR_META_WRITE_CH1_BIT,
	DUMPER_INTR_META_WRITE_CH2_BIT,
	DUMPER_INTR_META_WRITE_CH3_BIT,
	DUMPER_INTR_META_UNIT_BUF_CH0_BIT,
	DUMPER_INTR_META_UNIT_BUF_CH1_BIT,
	DUMPER_INTR_META_UNIT_BUF_CH2_BIT,
	DUMPER_INTR_META_UNIT_BUF_CH3_BIT,
	DUMPER_INTR_META_AL_FULL_CH0_BIT,
	DUMPER_INTR_META_AL_FULL_CH1_BIT,
	DUMPER_INTR_META_AL_FULL_CH2_BIT,
	DUMPER_INTR_META_AL_FULL_CH3_BIT,
	DUMPER_INTR_DATA_UNIT_BUF_CH0_BIT,
	DUMPER_INTR_DATA_UNIT_BUF_CH1_BIT,
	DUMPER_INTR_DATA_UNIT_BUF_CH2_BIT,
	DUMPER_INTR_DATA_UNIT_BUF_CH3_BIT,
	DUMPER_INTR_DATA_AL_FULL_CH0_BIT,
	DUMPER_INTR_DATA_AL_FULL_CH1_BIT,
	DUMPER_INTR_DATA_AL_FULL_CH2_BIT,
	DUMPER_INTR_DATA_AL_FULL_CH3_BIT,
	DUMPER_INTR_TIMESTAMP_CH0_BIT,
	DUMPER_INTR_TIMESTAMP_CH1_BIT,
	DUMPER_INTR_TIMESTAMP_CH2_BIT,
	DUMPER_INTR_TIMESTAMP_CH3_BIT,
};

#define DUMPER_INTR_META_WRITE_CH0	(0x1 << DUMPER_INTR_META_WRITE_CH0_BIT)
#define DUMPER_INTR_META_WRITE_CH1	(0x1 << DUMPER_INTR_META_WRITE_CH1_BIT)
#define DUMPER_INTR_META_WRITE_CH2	(0x1 << DUMPER_INTR_META_WRITE_CH2_BIT)
#define DUMPER_INTR_META_WRITE_CH3	(0x1 << DUMPER_INTR_META_WRITE_CH3_BIT)
#define DUMPER_INTR_META_UNIT_BUF_CH0	(0x1 << DUMPER_INTR_META_UNIT_BUF_CH0_BIT)
#define DUMPER_INTR_META_UNIT_BUF_CH1	(0x1 << DUMPER_INTR_META_UNIT_BUF_CH1_BIT)
#define DUMPER_INTR_META_UNIT_BUF_CH2	(0x1 << DUMPER_INTR_META_UNIT_BUF_CH2_BIT)
#define DUMPER_INTR_META_UNIT_BUF_CH3	(0x1 << DUMPER_INTR_META_UNIT_BUF_CH3_BIT)
#define DUMPER_INTR_META_AL_FULL_CH0	(0x1 << DUMPER_INTR_META_AL_FULL_CH0_BIT)
#define DUMPER_INTR_META_AL_FULL_CH1	(0x1 << DUMPER_INTR_META_AL_FULL_CH1_BIT)
#define DUMPER_INTR_META_AL_FULL_CH2	(0x1 << DUMPER_INTR_META_AL_FULL_CH2_BIT)
#define DUMPER_INTR_META_AL_FULL_CH3	(0x1 << DUMPER_INTR_META_AL_FULL_CH3_BIT)
#define DUMPER_INTR_DATA_UNIT_BUF_CH0	(0x1 << DUMPER_INTR_DATA_UNIT_BUF_CH0_BIT)
#define DUMPER_INTR_DATA_UNIT_BUF_CH1	(0x1 << DUMPER_INTR_DATA_UNIT_BUF_CH1_BIT)
#define DUMPER_INTR_DATA_UNIT_BUF_CH2	(0x1 << DUMPER_INTR_DATA_UNIT_BUF_CH2_BIT)
#define DUMPER_INTR_DATA_UNIT_BUF_CH3	(0x1 << DUMPER_INTR_DATA_UNIT_BUF_CH3_BIT)
#define DUMPER_INTR_DATA_AL_FULL_CH0	(0x1 << DUMPER_INTR_DATA_AL_FULL_CH0_BIT)
#define DUMPER_INTR_DATA_AL_FULL_CH1	(0x1 << DUMPER_INTR_DATA_AL_FULL_CH1_BIT)
#define DUMPER_INTR_DATA_AL_FULL_CH2	(0x1 << DUMPER_INTR_DATA_AL_FULL_CH2_BIT)
#define DUMPER_INTR_DATA_AL_FULL_CH3	(0x1 << DUMPER_INTR_DATA_AL_FULL_CH3_BIT)
#define DUMPER_INTR_TIMESTAMP_CH0	(0x1 << DUMPER_INTR_TIMESTAMP_CH0_BIT)
#define DUMPER_INTR_TIMESTAMP_CH1	(0x1 << DUMPER_INTR_TIMESTAMP_CH1_BIT)
#define DUMPER_INTR_TIMESTAMP_CH2	(0x1 << DUMPER_INTR_TIMESTAMP_CH2_BIT)
#define DUMPER_INTR_TIMESTAMP_CH3	(0x1 << DUMPER_INTR_TIMESTAMP_CH3_BIT)
#define DUMPER_INTR_TIMESTAMP_MASK \
  (DUMPER_INTR_TIMESTAMP_CH0 | DUMPER_INTR_TIMESTAMP_CH1 | \
   DUMPER_INTR_TIMESTAMP_CH2 | DUMPER_INTR_TIMESTAMP_CH3)


enum te_reg_dumper_mode {
	DUMPER_MODE_TLV = 0,
	DUMPER_MODE_RAW,
	DUMPER_MODE_PVR,
	DUMPER_MODE_LGC,
	DUMPER_MODE_DISABLE,
};

struct te_reg_dumper_status {
	bool enable;
	enum te_reg_dumper_mode mode;
};

struct te_reg_dumper_pkt_mon {
	bool enable;
	bool sop_mode;	/* false: unit byte mode */
	u32 unit_byte;
};

enum te_reg_atsc3_layer {
	ATSC3_DECODER_LAYER_BYPASS = 0,
	ATSC3_DECODER_LAYER_LGC,
	ATSC3_DECODER_LAYER_BB,
	ATSC3_DECODER_LAYER_BB_PLP,
	ATSC3_DECODER_LAYER_ALP,
	ATSC3_DECODER_LAYER_TIME_LGC,
	ATSC3_DECODER_LAYER_MAX
};

enum te_reg_atsc3_demod_type {
	ATSC3_DEMOD_TYPE_A = 0,
	ATSC3_DEMOD_TYPE_B,
	ATSC3_DEMOD_TYPE_C,
};

enum te_reg_atsc3_timestamp_mode {
	ATSC3_TIMESTAMP_NONE = 0,
	ATSC3_TIMESTAMP_SEC_MSEC,
	ATSC3_TIMESTAMP_SEC_MSEC_USEC,
	ATSC3_TIMESTAMP_SEC_MSEC_USEC_NSEC,
};

struct te_reg_atsc3_timestamp {
	enum te_reg_atsc3_timestamp_mode mode;
	u32 sec;
	u16 msec;
	u16 usec;
	u16 nsec;
};

struct te_reg_arib2_ntp_info {
	u8 precision;
	u8 poll;
	u8 mode;
	u8 version;
	u8 leap_indicator;

	u32 sec;
	u32 fraction;
};

int te_reg_dumper_init(void);
int te_reg_dumper_set_init_value(void);
int te_reg_dumper_set_engine(enum te_reg_engine_mode mode);
int te_reg_dumper_get_engine(enum te_reg_engine_mode *mode);
int te_reg_dumper_set_intr_enable(u32 val, bool en);
int te_reg_dumper_get_intr_status(u32 *val);
int te_reg_dumper_clear_intr(u32 val);
int te_reg_dumper_set_latch_enable(u8 ch, bool en);
int te_reg_dumper_set_data_buf(u8 ch, u32 sptr, u32 eptr);
int te_reg_dumper_get_data_wptr(u8 ch, u32 *wptr);
int te_reg_dumper_set_data_rptr(u8 ch, u32 rptr);
int te_reg_dumper_set_meta_buf(u8 ch, u32 sptr, u32 eptr);
int te_reg_dumper_get_meta_wptr(u8 ch, u32 *wptr);
int te_reg_dumper_set_meta_rptr(u8 ch, u32 rptr);
int te_reg_dumper_set_data_almostfull_level(u8 ch, u32 level);
int te_reg_dumper_set_data_unitbuf_size(u8 ch, u32 size);
int te_reg_dumper_set_meta_almostfull_level(u8 ch, u32 level);
int te_reg_dumper_set_meta_unitbuf_size(u8 ch, u32 size);
int te_reg_dumper_set_channel_mode(u8 ch, enum te_reg_dumper_mode mode);
int te_reg_dumper_set_channel_enable(u8 ch, bool en);
int te_reg_dumper_get_channel_status(u8 ch, struct te_reg_dumper_status *s);
int te_reg_dumper_set_time_src(u8 ch, u8 src);
int te_reg_dumper_set_gmau_awuser(u8 val);
int te_reg_dumper_set_packet_monitor(u8 ch, struct te_reg_dumper_pkt_mon *conf);
int te_reg_dumper_get_packet_count(u8 ch, u32 *val);

int te_reg_atsc3_set_demod_type(u8 ch, enum te_reg_atsc3_demod_type type);
int te_reg_atsc3_set_decoder_layer(u8 ch, enum te_reg_atsc3_layer layer);
int te_reg_atsc3_set_plp_filter(u8 ch, bool en, u8 id);
int te_reg_atsc3_get_timestamp(u8 ch, struct te_reg_atsc3_timestamp *timestamp);

int te_reg_arib2_set_ntp_conf(u8 ch, bool len_check, bool swreset);
int te_reg_arib2_set_ntp_src_addr(u8 ch, u32 *val, u32 *mask);
int te_reg_arib2_set_ntp_dst_addr(u8 ch, u32 *val, u32 *mask);
int te_reg_arib2_set_udp_port_val(u8 ch, u32 src, u32 dst);
int te_reg_arib2_set_udp_port_mask(u8 ch, u32 src, u32 dst);
int te_reg_arib2_get_ntp_info(u8 ch, struct te_reg_arib2_ntp_info *info);

const char *te_reg_dumper_mode_to_str(enum te_reg_dumper_mode mode);
const char *te_reg_atsc3_layer_to_str(enum te_reg_atsc3_layer layer);

/************ DSC ************/
enum te_reg_dsc_crypto_type {
	DSC_CRYPTO_TYPE_BYPASS = 0,
	DSC_CRYPTO_TYPE_DES,
	DSC_CRYPTO_TYPE_TDES,
	DSC_CRYPTO_TYPE_AES,
	DSC_CRYPTO_TYPE_DVBCSA,
	DSC_CRYPTO_TYPE_MULTI2,
};

enum te_reg_dsc_blk_mode {
	DSC_BLK_MODE_ECB = 0,
	DSC_BLK_MODE_CBC,
	DSC_BLK_MODE_CTR,
	DSC_BLK_MODE_OMAC1,
};

enum te_reg_dsc_res_mode {
	DSC_RES_MODE_CLEAR = 0,
	DSC_RES_MODE_CTS,
	DSC_RES_MODE_OFB,
	DSC_RES_MODE_SCTE,
};

enum te_reg_dsc_format {
	DSC_FORMAT_DATA = 0,
	DSC_FORMAT_TS,
	DSC_FORMAT_TIMESTAMP_TS,
};

struct te_reg_dsc_config {
	bool scramble;
	enum te_reg_dsc_crypto_type type;
	enum te_reg_dsc_blk_mode blk_mode;
	enum te_reg_dsc_res_mode res_mode;
	u8 key_size;
};

struct te_reg_dsc_status {
	bool busy;
};

enum te_reg_dsc_iv_key {
	DSC_IV = 0,
	DSC_KEY,
	DSC_EVEN_IV,
	DSC_ODD_IV,
	DSC_EVEN_KEY,
	DSC_ODD_KEY,
	DSC_MULTI2_SKEY,
	DSC_MULTI2_IV,
};


enum te_reg_dsc_intr_bit {
	DSC_INTR_DMA_DONE_BIT = 0,
};

#define DSC_INTR_DMA_DONE	(0x1 << DSC_INTR_DMA_DONE_BIT)


int te_reg_dsc_init(void);

int te_reg_dsc_reset(u8 idx);
int te_reg_dsc_set_endian(u8 idx, bool big_endian);
int te_reg_dsc_set_config(u8 idx, struct te_reg_dsc_config *cfg);
int te_reg_dsc_set_odd_mode(u8 idx, bool odd);
int te_reg_dsc_set_iv_key(u8 idx, enum te_reg_dsc_iv_key type,
			  const u8 *val, u8 size);
int te_reg_dsc_set_multi2(u8 idx, enum te_reg_dsc_iv_key type,
			  const u8 *val, u8 size);

int te_reg_dsc_start(u8 idx, enum te_reg_dsc_format fmt, u32 src, u32 dst,
		     u32 size);
int te_reg_dsc_get_status(u8 idx, struct te_reg_dsc_status *s);

int te_reg_dsc_set_intr_enable(u8 idx, u32 val, bool en);
int te_reg_dsc_get_intr_status(u8 idx, u32 *val);
int te_reg_dsc_clear_intr(u8 idx, u32 val);


#endif				/* _LG1K_TE_REG_H_ */

/** @} */
