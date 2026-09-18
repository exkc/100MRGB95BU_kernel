/* SIC I2C Reg CSV File to Header File transfer scripte by won.hur(won.hur@lge.com) */ 
/* Version = 0.70 */ 
/* File Build Date : Thu, 27 Jun 2019 05:14:27 +0000  */

/* ENABLE_O20A0 */
#define	enable_O20A0_REG_ADDR	0x0000

/* HDMI_CFG_0_O20A0 */
#define	hdmi_cfg_0_O20A0_REG_ADDR	0x0010

/* DSC_CORE_REG_CFG_0_O20A0 */
#define	dsc_core_reg_cfg_0_O20A0_REG_ADDR	0x0020

/* DSC_CVI_SIG_GEN_0_O20A0 */
#define	dsc_cvi_sig_gen_0_O20A0_REG_ADDR	0x0100

/* DSC_CVI_SIG_GEN_2_O20A0 */
#define	dsc_cvi_sig_gen_2_O20A0_REG_ADDR	0x0108

/* DSC_CVI_SIG_GEN_4_O20A0 */
#define	dsc_cvi_sig_gen_4_O20A0_REG_ADDR	0x0110

/* DSC_CVI_SIG_GEN_5_O20A0 */
#define	dsc_cvi_sig_gen_5_O20A0_REG_ADDR	0x0114

/* DSC_CVI_SIG_GEN_6_O20A0 */
#define	dsc_cvi_sig_gen_6_O20A0_REG_ADDR	0x0118

/* FEC_CVI_SIG_GEN_0_O20A0 */
#define	fec_cvi_sig_gen_0_O20A0_REG_ADDR	0x0200

/* FEC_CVI_SIG_GEN_2_O20A0 */
#define	fec_cvi_sig_gen_2_O20A0_REG_ADDR	0x0208

/* FEC_CVI_SIG_GEN_4_O20A0 */
#define	fec_cvi_sig_gen_4_O20A0_REG_ADDR	0x0210

/* DSC_IN_CTRL_0_O20A0 */
#define	dsc_in_ctrl_0_O20A0_REG_ADDR	0x0300

/* HDMI_IN_CTRL_0_O20A0 */
#define	hdmi_in_ctrl_0_O20A0_REG_ADDR	0x0340

/* INTR_STATUS_CPU_O20A0 */
#define	intr_status_cpu_O20A0_REG_ADDR	0x0400

/* INTR_ENABLE_CPU_O20A0 */
#define	intr_enable_cpu_O20A0_REG_ADDR	0x0404

/* INTR_STATUS_MCU_O20A0 */
#define	intr_status_mcu_O20A0_REG_ADDR	0x0410

/* INTR_ENABLE_MCU_O20A0 */
#define	intr_enable_mcu_O20A0_REG_ADDR	0x0414

/* MONITOR_DSC_0_O20A0 */
#define	monitor_dsc_0_O20A0_REG_ADDR	0x0420

/* MONITOR_DSC_1_O20A0 */
#define	monitor_dsc_1_O20A0_REG_ADDR	0x0424

/* MONITOR_FEC_0_O20A0 */
#define	monitor_fec_0_O20A0_REG_ADDR	0x0428

/* MONITOR_HDMI_0_O20A0 */
#define	monitor_hdmi_0_O20A0_REG_ADDR	0x0440

/* MONITOR_HDMI_1_O20A0 */
#define	monitor_hdmi_1_O20A0_REG_ADDR	0x0444

/* MONITOR_HDMI_2_O20A0 */
#define	monitor_hdmi_2_O20A0_REG_ADDR	0x0448

/* MONITOR_HDMI_3_O20A0 */
#define	monitor_hdmi_3_O20A0_REG_ADDR	0x044c

/* MONITOR_HDMI_4_O20A0 */
#define	monitor_hdmi_4_O20A0_REG_ADDR	0x0450

/* END OF ADDR DEFINITION */


typedef struct
{
	UINT32
		dsc_cvi_formater_en:1,		// 0:0
		dsc_core_en:1,		// 1:1
		dsc_hdmi_fifo_en:1,		// 2:2
		b_rsvd1:5,		// 7:3
		fec_cvi_formater_en:1,		// 8:8
		fec_encoder_en:1,		// 9:9
		fec_hdmi_fifo_en:1,		// 10:10
		padd_rsvd:21;		// 31:11
} ENABLE_O20A0_T;



typedef struct
{
	UINT32
		hdmi_port_sel:6,		// 5:0
		reserved0:10,		// 15:6
		hdmi_in_byte_swap:1,		// 16:16
		reserved1:3,		// 19:17
		fec_fifo_byte_swap:1,		// 20:20
		fec_fifo_word_swap:1,		// 21:21
		dsc_fifo_byte_swap:1,		// 22:22
		dsc_fifo_word_swap:1,		// 23:23
		reserved2:8;		// 31:24
} HDMI_CFG_0_O20A0_T;



typedef struct
{
	UINT32
		dsc_decoder_register_upate_request:1,		// 0:0
		dsc_decoder_register_upate_done:1,		// 1:1
		reserved:30;		// 31:2
} DSC_CORE_REG_CFG_0_O20A0_T;



typedef struct
{
	UINT32
		dsc_cvi_formatter_vsync_pulse_width:15,		// 14:0
		reserved:1,		// 15:15
		dsc_cvi_formatter_vsync_delay:14,		// 29:16
		reserved1:2;		// 31:30
} DSC_CVI_SIG_GEN_0_O20A0_T;



typedef struct
{
	UINT32
		dsc_cvi_formatter_hsync_pulse_width:10,		// 9:0
		b_rsvd1:6,		// 15:10
		dsc_cvi_formatter_hsync_delay:14,		// 29:16
		padd_rsvd:2;		// 31:30
} DSC_CVI_SIG_GEN_2_O20A0_T;



typedef struct
{
	UINT32
		dsc_cvi_formatter_de_total_num_per_line:14,		// 13:0
		b_rsvd1:2,		// 15:14
		dsc_cvi_formatter_de_start_fifo_cnt:11,		// 26:16
		padd_rsvd:5;		// 31:27
} DSC_CVI_SIG_GEN_4_O20A0_T;



typedef struct
{
	UINT32
		dsc_cvi_dsc_video_bpc:4,		// 3:0
		b_rsvd1:4,		// 7:4
		dsc_cvi_dsc_video_format:3,		// 10:8
		padd_rsvd:21;		// 31:11
} DSC_CVI_SIG_GEN_5_O20A0_T;



typedef struct
{
	UINT32
		dsc_cvi_formatter_output_iamge_shifted_cnt:14,		// 13:0
		padd_rsvd:18;		// 31:14
} DSC_CVI_SIG_GEN_6_O20A0_T;



typedef struct
{
	UINT32
		reserved:15,		// 14:0
		fec_cvi_ctrl_cvi_8bit_10bit_sel:1,		// 15:15, 2021/04/26 : This only exists from O22
		fec_cvi_formatter_vsync_delay_num_cvi_clk:14,		// 29:16
		fec_cvi_formatter_word_swap:1,		// 30:30
		fec_cvi_formatter_cvi_channel_4_2:1;		// 31:31
} FEC_CVI_SIG_GEN_0_O20A0_T;



typedef struct
{
	UINT32
		fec_cvi_formatter_hsync_pulse_width:10,		// 9:0
		b_rsvd1:6,		// 15:10
		fec_cvi_formatter_hsync_delay:14,		// 29:16
		padd_rsvd:2;		// 31:30
} FEC_CVI_SIG_GEN_2_O20A0_T;



typedef struct
{
	UINT32
		fec_cvi_formatter_de_total_num_per_line:14,		// 13:0
		b_rsvd1:2,		// 15:14
		fec_cvi_formatter_de_start_fifo_cnt:11,		// 26:16
		padd_rsvd:5;		// 31:27
} FEC_CVI_SIG_GEN_4_O20A0_T;



typedef struct
{
	UINT32
		dsc_in_ctrl_v_active_width:13,		// 12:0
		b_rsvd1:3,		// 15:13
		dsc_in_ctrl_h_active_de_width:14,		// 29:16
		dsc_in_ctrl_num_of_active_dsc_core:2;		// 31:30
} DSC_IN_CTRL_0_O20A0_T;



typedef struct
{
	UINT32
		hdmi_in_hsync_polarity_inv:1,		// 0:0
		hdmi_in_vsync_polarity_inv:1,		// 1:1
		padd_rsvd:30;		// 31:2
} HDMI_IN_CTRL_0_O20A0_T;



typedef struct
{
	UINT32
		intr_st_dsc_core0_error0:1,		// 0:0
		intr_st_dsc_core0_error1:1,		// 1:1
		intr_st_dsc_core0_error2:1,		// 2:2
		intr_st_dsc_core0_error3:1,		// 3:3
		intr_st_dsc_core1_error0:1,		// 4:4
		intr_st_dsc_core1_error1:1,		// 5:5
		intr_st_dsc_core1_error2:1,		// 6:6
		intr_st_dsc_core1_error3:1,		// 7:7
		intr_st_dsc_core_rb_underflow:1,		// 8:8
		intr_st_dsc_cvi_fifo_underflow:1,		// 9:9
		intr_st_dsc_cvi_fifo_overflow:1,		// 10:10
		intr_st_dsc_cvi_image_shifted:1,		// 11:11
		intr_st_fec_cvi_fifo_underflow:1,		// 12:12
		intr_st_fec_cvi_fifo_overflow:1,		// 13:13
		b_rsvd1:17,		// 30:14
		intr_st_all:1;		// 31:31
} INTR_STATUS_CPU_O20A0_T;



typedef struct
{
	UINT32
		b_rsvd1:31,		// 30:0
		intr_en_cpu:1;		// 31:31
} INTR_ENABLE_CPU_O20A0_T;



typedef struct
{
	UINT32
		intr_st_dsc_core0_error0:1,		// 0:0
		intr_st_dsc_core0_error1:1,		// 1:1
		intr_st_dsc_core0_error2:1,		// 2:2
		intr_st_dsc_core0_error3:1,		// 3:3
		intr_st_dsc_core1_error0:1,		// 4:4
		intr_st_dsc_core1_error1:1,		// 5:5
		intr_st_dsc_core1_error2:1,		// 6:6
		intr_st_dsc_core1_error3:1,		// 7:7
		intr_st_dsc_core_rb_underflow:1,		// 8:8
		intr_st_dsc_cvi_fifo_underflow:1,		// 9:9
		intr_st_dsc_cvi_fifo_overflow:1,		// 10:10
		intr_st_dsc_cvi_image_shifted:1,		// 11:11
		intr_st_fec_cvi_fifo_underflow:1,		// 12:12
		intr_st_fec_cvi_fifo_overflow:1,		// 13:13
		b_rsvd1:17,		// 30:14
		intr_st_all:1;		// 31:31
} INTR_STATUS_MCU_O20A0_T;



typedef struct
{
	UINT32
		b_rsvd1:31,		// 30:0
		intr_en_mcu:1;		// 31:31
} INTR_ENABLE_MCU_O20A0_T;



typedef struct
{
	UINT32
		dsc_core0_error0:4,		// 3:0
		dsc_core0_error1:4,		// 7:4
		dsc_core0_error2:4,		// 11:8
		dsc_core0_error3:4,		// 15:12
		dsc_core1_error0:4,		// 19:16
		dsc_core1_error1:4,		// 23:20
		dsc_core1_error2:4,		// 27:24
		dsc_core1_error3:4;		// 31:28
} MONITOR_DSC_0_O20A0_T;



typedef struct
{
	UINT32
		dsc_core_mode:6,		// 5:0
		padd_rsvd:26;		// 31:6
} MONITOR_DSC_1_O20A0_T;



typedef struct
{
	UINT32
		fec_cvi_formatter_hsync_low_cnt:16,		// 15:0
		fec_cvi_formatter_hsync_high_cnt:16;		// 31:16
} MONITOR_FEC_0_O20A0_T;



typedef struct
{
	UINT32
		hdmi_monitor_enable:1,		// 0:0
		padd_rsvd:31;		// 31:1
} MONITOR_HDMI_0_O20A0_T;



typedef struct
{
	UINT32
		vsync_low:24,		// 23:0
		padd_rsvd:8;		// 31:24
} MONITOR_HDMI_1_O20A0_T;



typedef struct
{
	UINT32
		vsync_hi:24,		// 23:0
		padd_rsvd:8;		// 31:24
} MONITOR_HDMI_2_O20A0_T;



typedef struct
{
	UINT32
		hsync_low:24,		// 23:0
		padd_rsvd:8;		// 31:24
} MONITOR_HDMI_3_O20A0_T;



typedef struct
{
	UINT32
		hsync_hi:24,		// 23:0
		padd_rsvd:8;		// 31:24
} MONITOR_HDMI_4_O20A0_T;


typedef struct {
	ENABLE_O20A0_T					enable;
	HDMI_CFG_0_O20A0_T				hdmi_cfg_0;
	DSC_CORE_REG_CFG_0_O20A0_T		dsc_core_reg_cfg_0;
	DSC_CVI_SIG_GEN_0_O20A0_T		dsc_cvi_sig_gen_0;
	DSC_CVI_SIG_GEN_2_O20A0_T		dsc_cvi_sig_gen_2;
	DSC_CVI_SIG_GEN_4_O20A0_T		dsc_cvi_sig_gen_4;
	DSC_CVI_SIG_GEN_5_O20A0_T		dsc_cvi_sig_gen_5;
	DSC_CVI_SIG_GEN_6_O20A0_T		dsc_cvi_sig_gen_6;
	FEC_CVI_SIG_GEN_0_O20A0_T		fec_cvi_sig_gen_0;
	FEC_CVI_SIG_GEN_2_O20A0_T		fec_cvi_sig_gen_2;
	FEC_CVI_SIG_GEN_4_O20A0_T		fec_cvi_sig_gen_4;
	DSC_IN_CTRL_0_O20A0_T		dsc_in_ctrl_0;
	HDMI_IN_CTRL_0_O20A0_T		hdmi_in_ctrl_0;
	INTR_STATUS_CPU_O20A0_T		intr_status_cpu;
	INTR_ENABLE_CPU_O20A0_T		intr_enable_cpu;
	INTR_STATUS_MCU_O20A0_T		intr_status_mcu;
	INTR_ENABLE_MCU_O20A0_T		intr_enable_mcu;
	MONITOR_DSC_0_O20A0_T		monitor_dsc_0;
	MONITOR_DSC_1_O20A0_T		monitor_dsc_1;
	MONITOR_FEC_0_O20A0_T		monitor_fec_0;
	MONITOR_HDMI_0_O20A0_T		monitor_hdmi_0;
	MONITOR_HDMI_1_O20A0_T		monitor_hdmi_1;
	MONITOR_HDMI_2_O20A0_T		monitor_hdmi_2;
	MONITOR_HDMI_3_O20A0_T		monitor_hdmi_3;
	MONITOR_HDMI_4_O20A0_T		monitor_hdmi_4;
} HDMI21_DSC_TOP_REG_O20A0_T;
