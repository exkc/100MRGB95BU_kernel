#ifndef _ION_REG_DB_H_
#define _ION_REG_DB_H_

#include <linux/stddef.h>
#include <linux/types.h>

#define O26_ION0_REG_BASE 0xCA330000
#define O26_ION1_REG_BASE 0xC4670000

#define ION_BASE_ADDRESS 0x10000

#define CTOP_BASE_ADDRESS 0x0000
#define CTOP_REG_SIZE 0x54

#define SARADC0_BASE_ADDRESS 0x1000
#define SARADC0_REG_SIZE 0x5C

#define SARADC1_BASE_ADDRESS 0x2000
#define SARADC1_REG_SIZE 0x5C

#define ION_MCRG_BASE_ADDRESS 0x3000
#define ION_MCRG_REG_SIZE 0x4C

#define ION_BND_BASE_ADDRESS 0x4000
#define ION_BND_REG_SIZE 0x0C

#define ION_SCRG_BASE_ADDRESS 0x5000
#define ION_SCRG_REG_SIZE 0x20

#define SRDS12TO3_BASE_ADDRESS 0x6000
#define SRDS12TO3_REG_SIZE 0x3C

#define SRDS32TO1_0_BASE_ADDRESS 0x7000
#define SRDS32TO1_0_REG_SIZE 0x100

#define IOMUX_CTRL_BASE_ADDRESS 0x8000
#define IOMUX_CTRL_REG_SIZE 0x58

#define SPI_TO_AHB_BASE_ADDRESS 0x9000
#define SPI_TO_AHB_REG_SIZE 0x88

#define SRDS32TO1_1_BASE_ADDRESS 0xA000
#define SRDS32TO1_1_REG_SIZE 0x100


/*
 * CTOP
 */
/*-----------------------------------------------------------------------------
	0x0000 reg33to18_trim ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_REG33TO18_LV_D18		: 4;	//  3: 0
} REG33TO18_TRIM;

/*-----------------------------------------------------------------------------
	0x0004 reg33to18_rstb ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_POR_RSTB_OUT_REG		: 1;	//  0
} REG33TO18_RSTRB;

/*-----------------------------------------------------------------------------
	0x0010 ci_intr ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_intr			: 1;	//  0
} CI_INTR;

/*-----------------------------------------------------------------------------
	0x0014 ci_intr_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_intr_sel			: 1;	//  0
} CI_INTR_SEL;

/*-----------------------------------------------------------------------------
	0x0018 srds_intr ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_intr_tstmp_err0		: 1,	//  0
					: 3,	//  3: 1
	reg_intr_tstmp_err1		: 1;	//  4
} SRDS_INTR;

/*-----------------------------------------------------------------------------
	0x0020 crg_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_i_sel_tu_io_sd07		: 1,	//  0
	reg_c_sel_tu_io_sd07		: 1,	//  1
	reg_i_sel_tu_io_sd06		: 1,	//  2
	reg_c_sel_tu_io_sd06		: 1,	//  3
	reg_i_sel_tu_io_sd05		: 1,	//  4
	reg_c_sel_tu_io_sd05		: 1,	//  5
	reg_i_sel_tu_io_sd04		: 1,	//  6
	reg_c_sel_tu_io_sd04		: 1,	//  7
	reg_i_sel_tu_io_sd03		: 1,	//  8
	reg_c_sel_tu_io_sd03		: 1,	//  9
	reg_i_sel_tu_io_sd02		: 1,	// 10
	reg_c_sel_tu_io_sd02		: 1,	// 11
	reg_i_sel_tu_io_sd01		: 1,	// 12
	reg_c_sel_tu_io_sd01		: 1,	// 13
	reg_i_sel_tu_io_sd00		: 1,	// 14
	reg_c_sel_tu_io_sd00		: 1;	// 15
} CRG_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0024 crg_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_main_clk_sel		: 1,	//  0
					: 3,	//  3: 1
	reg_cicam_clk_sel		: 1;	//  4
} CRG_CTRL_2;

/*-----------------------------------------------------------------------------
	0x0030 rev_id_ion_a0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_rev_id_out00		: 1,	//  0
	reg_rev_id_out01		: 1,	//  1
	reg_rev_id_out02		: 1,	//  2
	reg_rev_id_out03		: 1,	//  3
	reg_rev_id_out04		: 1,	//  4
	reg_rev_id_out05		: 1,	//  5
	reg_rev_id_out06		: 1,	//  6
	reg_rev_id_out07		: 1;	//  7
} REV_ID_ION_A0;

/*-----------------------------------------------------------------------------
	0x0040 ion_id ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ion_id			: 32;	// 31: 0
} ION_ID;

/*-----------------------------------------------------------------------------
	0x0044 ion_test_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_reg_test			: 32;	// 31: 0
} ION_TEST_REG;

/*-----------------------------------------------------------------------------
	0x0050 ion_ssp_cs_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ssp_cs_control		: 32;	// 31: 0
} ION_SSP_CS_REG;


typedef struct {
	REG33TO18_TRIM				reg33to18_trim;	// 0x0000: ''
	REG33TO18_RSTRB				reg33to18_rstrb;// 0x0004: ''
	u32					__rsvd__0[2];	// 0x0008 ~ 0x000C
	CI_INTR					ci_intr;	// 0x0010: ''
	CI_INTR_SEL				ci_intr_sel;	// 0x0014: ''
	SRDS_INTR				srds_intr;	// 0x0018: ''
	u32					__rsvd__1;	// 0x001C: ''
	CRG_CTRL_1				crg_ctrl_1;	// 0x0020: ''
	CRG_CTRL_2				crg_ctrl_2;	// 0x0024: ''
	u32					__rsvd__2[2];	// 0x0028 ~ 0x002C
	REV_ID_ION_A0				rev_id_ion_a0;	// 0x0030: ''
	u32					__rsvd__3[3];	// 0x0034 ~ 0x003C
	ION_ID					ion_id;		// 0x0040: ''
	ION_TEST_REG				ion_test_reg;	// 0x0044: ''
	u32					__rsvd__4[2];	// 0x0048 ~ 0x004C
	ION_SSP_CS_REG				ion_ssp_cs_reg;	// 0x0050: ''
} CTOP_REG_T;

#define GET_CTOP_ADDR(member) \
	(CTOP_BASE_ADDRESS + offsetof(CTOP_REG_T, member))

/*
 * SADC_0/1_CTRL
 */
/*-----------------------------------------------------------------------------
	0x0000 sadc_rst ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pdb				: 1;	//  0
} SADC_RST;

/*-----------------------------------------------------------------------------
	0x0004 sadc_drv_setup ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ch				: 6,	//  5: 0
					: 2,	//  7: 6
	reg_glitch_free_en		: 1,	//  8
	reg_manual_en			: 1,	//  9
					: 6,	// 15:10
	reg_data_mask			: 8,	// 23:16
	reg_max_cap			: 3;	// 26:24
} SADC_DRV_SETUP;

/*-----------------------------------------------------------------------------
	0x0008 sadc_drv_period_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_T1				: 16,	// 15: 0
	reg_T2				: 16;	// 31:16
} SADC_DRV_PERIOD_0;

/*-----------------------------------------------------------------------------
	0x000c sadc_drv_period_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_T4				: 16;	// 15: 0
} SADC_DRV_PERIOD_1;

/*-----------------------------------------------------------------------------
	0x0010 sadc_drv_period_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_T5_1			: 16,	// 15: 0
	reg_T5_2			: 16;	// 31:16
} SADC_DRV_PERIOD_2;

/*-----------------------------------------------------------------------------
	0x0014 sadc_start_manual_cap ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_start_cap			: 1;	//  0
} SADC_START_MANUAL_CAP;

/*-----------------------------------------------------------------------------
	0x0018 sadc_data_ch0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sadc_data_ch0_d3		: 8,	//  7: 0
	sadc_data_ch0_d2		: 8,	// 15: 8
	sadc_data_ch0_d1		: 8,	// 23:16
	sadc_data_ch0			: 8;	// 31:24
} SADC_DATA_CH0;

/*-----------------------------------------------------------------------------
	0x001C sadc_data_ch1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sadc_data_ch1_d3		: 8,	//  7: 0
	sadc_data_ch1_d2		: 8,	// 15: 8
	sadc_data_ch1_d1		: 8,	// 23:16
	sadc_data_ch1			: 8;	// 31:24
} SADC_DATA_CH1;

/*-----------------------------------------------------------------------------
	0x0020 sadc_data_ch2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sadc_data_ch2_d3		: 8,	//  7: 0
	sadc_data_ch2_d2		: 8,	// 15: 8
	sadc_data_ch2_d1		: 8,	// 23:16
	sadc_data_ch2			: 8;	// 31:24
} SADC_DATA_CH2;

/*-----------------------------------------------------------------------------
	0x0024 sadc_data_ch3 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sadc_data_ch3_d3		: 8,	//  7: 0
	sadc_data_ch3_d2		: 8,	// 15: 8
	sadc_data_ch3_d1		: 8,	// 23:16
	sadc_data_ch3			: 8;	// 31:24
} SADC_DATA_CH3;

/*-----------------------------------------------------------------------------
	0x0028 sadc_data_ch4 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sadc_data_ch4_d3		: 8,	//  7: 0
	sadc_data_ch4_d2		: 8,	// 15: 8
	sadc_data_ch4_d1		: 8,	// 23:16
	sadc_data_ch4			: 8;	// 31:24
} SADC_DATA_CH4;

/*-----------------------------------------------------------------------------
	0x002C sadc_data_ch5 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sadc_data_ch5_d3		: 8,	//  7: 0
	sadc_data_ch5_d2		: 8,	// 15: 8
	sadc_data_ch5_d1		: 8,	// 23:16
	sadc_data_ch5			: 8;	// 31:24
} SADC_DATA_CH5;

/*-----------------------------------------------------------------------------
	0x0030 gf_data_ch0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	glitch_free_data_ch0		: 8;	//  7: 0
} GF_DATA_CH0;

/*-----------------------------------------------------------------------------
	0x0034 gf_data_ch1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	glitch_free_data_ch1		: 8;	//  7: 0
} GF_DATA_CH1;

/*-----------------------------------------------------------------------------
	0x0038 gf_data_ch2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	glitch_free_data_ch2		: 8;	//  7: 0
} GF_DATA_CH2;

/*-----------------------------------------------------------------------------
	0x003C gf_data_ch3 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	glitch_free_data_ch3		: 8;	//  7: 0
} GF_DATA_CH3;

/*-----------------------------------------------------------------------------
	0x0040 gf_data_ch4 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	glitch_free_data_ch4		: 8;	//  7: 0
} GF_DATA_CH4;

/*-----------------------------------------------------------------------------
	0x0044 gf_data_ch5 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	glitch_free_data_ch5		: 8;	//  7: 0
} GF_DATA_CH5;

/*-----------------------------------------------------------------------------
	0x0048 sadc_intr ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_intr			: 7;	//  6: 0
} SADC_INTR;

/*-----------------------------------------------------------------------------
	0x004C sadc_intr_clear ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_intr_clear			: 7;	//  6: 0
} SADC_INTR_CLEAR;

/*-----------------------------------------------------------------------------
	0x0050 sadc_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_intr_mask			: 7;	//  6: 0
} SADC_INTR_MASK;

/*-----------------------------------------------------------------------------
	0x0054 sadc_mon ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sadc_eoc			: 1;	//  0
} SADC_MON;

/*-----------------------------------------------------------------------------
	0x0058 sadc_config ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sadc_cc				: 3,	//  2: 0
					: 5,	//  7: 3
	sadc_pc				: 3,	// 10: 8
					: 5,	// 15:11
	sadc_isel			: 3;	// 18:16
} SADC_CONFIG;

typedef struct {
	SADC_RST			sadc_rst;		// 0x0000: ''
	SADC_DRV_SETUP			sadc_drv_setup;		// 0x0004: ''
	SADC_DRV_PERIOD_0		sadc_drv_period_0;	// 0x0008: ''
	SADC_DRV_PERIOD_1		sadc_drv_period_1;	// 0x000C: ''
	SADC_DRV_PERIOD_2		sadc_drv_period_2;	// 0x0010: ''
	SADC_START_MANUAL_CAP		sadc_start_manual_cap;	// 0x0014: ''
	SADC_DATA_CH0			sadc_data_ch0;		// 0x0018: ''
	SADC_DATA_CH1			sadc_data_ch1;		// 0x001C: ''
	SADC_DATA_CH2			sadc_data_ch2;		// 0x0020: ''
	SADC_DATA_CH3			sadc_data_ch3;		// 0x0024: ''
	SADC_DATA_CH4			sadc_data_ch4;		// 0x0028: ''
	SADC_DATA_CH5			sadc_data_ch5;		// 0x002C: ''
	GF_DATA_CH0			gf_data_ch0;		// 0x0030: ''
	GF_DATA_CH1			gf_data_ch1;		// 0x0034: ''
	GF_DATA_CH2			gf_data_ch2;		// 0x0038: ''
	GF_DATA_CH3			gf_data_ch3;		// 0x003C: ''
	GF_DATA_CH4			gf_data_ch4;		// 0x0040: ''
	GF_DATA_CH5			gf_data_ch5;		// 0x0044: ''
	SADC_INTR			sadc_intr;		// 0X0048: ''
	SADC_INTR_CLEAR			sadc_intr_clear;	// 0X004C: ''
	SADC_INTR_MASK			sadc_intr_mask;		// 0x0050: ''
	SADC_MON			sadc_mon;		// 0x0054: ''
	SADC_CONFIG			sadc_config;		// 0x0058: ''
} SADC_REG_T;

/*
 * ION_MCRG (ion_syn)
 */

/*-----------------------------------------------------------------------------
	0x0000 mcrg_main_ion0
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	test_reserved			: 32;	// 31: 0
} MCRG_MAIN_ION0;

/*-----------------------------------------------------------------------------
	0x0004 mcrg_main_ion1
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	test_reserved_ro		: 32;	// 31: 0
} MCRG_MAIN_ION1;

/*-----------------------------------------------------------------------------
	0x0008 mcrg_main_ion2
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ion_ipw_clk_gate_en		: 1;	//  0
} MCRG_MAIN_ION2;

/*-----------------------------------------------------------------------------
	0x000C mcrg_main_ion3
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	swrst_i_rst_cpuav_i_ion		: 1,	//  0
	swrst_i_rst_cpuav_i_ion_d100	: 1;	//  1
} MCRG_MAIN_ION3;

/*-----------------------------------------------------------------------------
	0x0010 mcrg_main_ion4
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext1_clk_bypass		: 1;	//  0
} MCRG_MAIN_ION4;

/*-----------------------------------------------------------------------------
	0x0014 mcrg_main_ion5
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext1_clk_flt_margin	: 2;	//  1: 0
} MCRG_MAIN_ION5;

/*-----------------------------------------------------------------------------
	0x0018 mcrg_main_ion6
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext1_clk_flt_sel	: 1;	//  0
} MCRG_MAIN_ION6;

/*-----------------------------------------------------------------------------
	0x001C mcrg_main_ion7
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext1_clk_flt_invsel	: 1;	//  0
} MCRG_MAIN_ION7;

/*-----------------------------------------------------------------------------
	0x0020 mcrg_main_ion8
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext2_clk_bypass		: 1;	//  0
} MCRG_MAIN_ION8;

/*-----------------------------------------------------------------------------
	0x0024 mcrg_main_ion9
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext2_clk_flt_margin	: 2;	//  1: 0
} MCRG_MAIN_ION9;

/*-----------------------------------------------------------------------------
	0x0028 mcrg_main_ion10
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext2_clk_flt_sel	: 1;	//  0
} MCRG_MAIN_ION10;

/*-----------------------------------------------------------------------------
	0x002C mcrg_main_ion11
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext2_clk_flt_invsel	: 1;	//  0
} MCRG_MAIN_ION11;

/*-----------------------------------------------------------------------------
	0x0030 mcrg_ctrl2
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_saradc_outclk_en		: 1;	//  0
} MCRG_CTRL2;

/*-----------------------------------------------------------------------------
	0x0034 mcrg_ctrl3
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_saradc_outclk_div		: 10;	//  9: 0
} MCRG_CTRL3;

/*-----------------------------------------------------------------------------
	0x0038 mcrg_ctrl4
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_saradc_outclk_stable	: 1;	//  0
} MCRG_CTRL4;

/*-----------------------------------------------------------------------------
	0x0040 mcrg_ctrl5
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext2_cam_clk_sel	: 1;	//  0
} MCRG_CTRL5;

/*-----------------------------------------------------------------------------
	0x0044 mcrg_ctrl6
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext1_clk_sel		: 1;	//  0
} MCRG_CTRL6;

/*-----------------------------------------------------------------------------
	0x0048 mcrg_ctrl7
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_ext2_clk_sel		: 1;	//  0
} MCRG_CTRL7;

typedef struct {
	MCRG_MAIN_ION0				mcrg_main_ion0;	// 0x0000
	MCRG_MAIN_ION1				mcrg_main_ion1;	// 0x0004
	MCRG_MAIN_ION2				mcrg_main_ion2;	// 0x0008
	MCRG_MAIN_ION3				mcrg_main_ion3;	// 0x000C
	MCRG_MAIN_ION4				mcrg_main_ion4;	// 0x0010
	MCRG_MAIN_ION5				mcrg_main_ion5;	// 0x0014
	MCRG_MAIN_ION6				mcrg_main_ion6;	// 0x0018
	MCRG_MAIN_ION7				mcrg_main_ion7;	// 0x001C
	MCRG_MAIN_ION8				mcrg_main_ion8;	// 0x0020
	MCRG_MAIN_ION9				mcrg_main_ion9;	// 0x0024
	MCRG_MAIN_ION10				mcrg_main_ion10;// 0x0028
	MCRG_MAIN_ION11				mcrg_main_ion11;// 0x002C
	MCRG_CTRL2				mcrg_ctrl2;	// 0x0030
	MCRG_CTRL3				mcrg_ctrl3;	// 0x0034
	MCRG_CTRL4				mcrg_ctrl4;	// 0x0038
	u32					__rsvd__0;	// 0x003C
	MCRG_CTRL5				mcrg_ctrl5;	// 0x0040
	MCRG_CTRL6				mcrg_ctrl6;	// 0x0044
	MCRG_CTRL7				mcrg_ctrl7;	// 0x0048
} ION_MCRG_REG_T;

#define GET_ION_MCRG_ADDR(member) \
	(ION_MCRG_BASE_ADDRESS + offsetof(ION_MCRG_REG_T, member))

/*
 * BND
 */
/*-----------------------------------------------------------------------------
	0x0000 crg_bnd_ion0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	test_reserved			: 32;	// 31: 0
} CRG_BND_ION0;

/*-----------------------------------------------------------------------------
	0x0004 crg_bnd_ion1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	test_reserved_ro		: 32;	// 31: 0
} CRG_BND_ION1;

/*-----------------------------------------------------------------------------
	0x0008 crg_bnd_ion2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_soft_rst_apb_ipw_ion_n	: 1;	//  0
} CRG_BND_ION2;

typedef struct {
	CRG_BND_ION0			crg_bnd_ion0;	// 0x0000
	CRG_BND_ION1			crg_bnd_ion1;	// 0x0004
	CRG_BND_ION2			crg_bnd_ion2;	// 0x0008
 } BND_REG_T;

/*
 * ION_SCRG (ion_syn)
 */
/*-----------------------------------------------------------------------------
	0x0000 scrg_ion0
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	test_reserved			: 32;	// 31: 0
} SCRG_ION0;

/*-----------------------------------------------------------------------------
	0x0004 scrg_ion1
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	test_reserved_ro		: 32;	// 31: 0
} SCRG_ION1;

/*-----------------------------------------------------------------------------
	0x0008 scrg_ion2
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci25_clk_gate_en			: 1, //  0
	reg_ci50_clk_gate_en			: 1, //  1
	reg_cicam_bus_clk_gate_en		: 1, //  2
	reg_cicam_bus_clk_n_gate_en		: 1, //  3
	reg_saradc_bus_clk_gate_en		: 1, //  4
	reg_saradc_clk_gate_en			: 1, //  5
	reg_skew_ff_sd0_clk_gate_en		: 1, //  6
	reg_skew_ff_sd1_clk_gate_en		: 1, //  7
	reg_skew_ff_sd2_clk_gate_en		: 1, //  8
	reg_skew_ff_sd3_clk_gate_en		: 1, //  9
	reg_skew_ff_sd4_clk_gate_en		: 1, // 10
	reg_skew_ff_sd5_clk_gate_en		: 1, // 11
	reg_skew_ff_sd6_clk_gate_en		: 1, // 12
	reg_skew_ff_sd7_clk_gate_en		: 1, // 13
	reg_srds_12to3_sd_rx0_clk_gate_en	: 1, // 14
	reg_srds_12to3_sd_rx1_clk_gate_en	: 1, // 15
	reg_srds_12to3_sd_tx0_clk_gate_en	: 1, // 16
	reg_srds_12to3_sd_tx1_clk_gate_en	: 1, // 17
	reg_srds_12to3_tp_rx0_clk_gate_en	: 1, // 18
	reg_srds_12to3_tp_rx1_clk_gate_en	: 1, // 19
	reg_srds_12to3_tp_tx0_clk_gate_en	: 1, // 20
	reg_srds_12to3_tp_tx1_clk_gate_en	: 1, // 21
	reg_srds_32to1_sd_rx0_clk_gate_en	: 1, // 22
	reg_srds_32to1_sd_rx1_clk_gate_en	: 1, // 23
	reg_srds_32to1_sd_tx0_clk_gate_en	: 1, // 24
	reg_srds_32to1_sd_tx1_clk_gate_en	: 1, // 25
	reg_tpi_clk_ext1_out_gate_en		: 1, // 26
	reg_tpi_clk_ext2_out_gate_en		: 1, // 27
	reg_tpi_clk_ext3_out_gate_en		: 1; // 28
} SCRG_ION2;

/*-----------------------------------------------------------------------------
	0x000C scrg_ion3
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_soft_rst_bus_n			: 1, //  0
	reg_soft_rst_ci25_n			: 1, //  1
	reg_soft_rst_ci50_n			: 1, //  2
	reg_soft_rst_cicam_bus_n		: 1, //  3
	reg_soft_rst_saradc_bus_n		: 1, //  4
	reg_soft_rst_skew_ff_sd0_n		: 1, //  5
	reg_soft_rst_skew_ff_sd1_n		: 1, //  6
	reg_soft_rst_skew_ff_sd2_n		: 1, //  7
	reg_soft_rst_skew_ff_sd3_n		: 1, //  8
	reg_soft_rst_skew_ff_sd4_n		: 1, //  9
	reg_soft_rst_skew_ff_sd5_n		: 1, // 10
	reg_soft_rst_skew_ff_sd6_n		: 1, // 11
	reg_soft_rst_skew_ff_sd7_n		: 1, // 12
	reg_soft_rst_srds_12to3_sd_rx0_n	: 1, // 13
	reg_soft_rst_srds_12to3_sd_rx1_n	: 1, // 14
	reg_soft_rst_srds_12to3_sd_tx0_n	: 1, // 15
	reg_soft_rst_srds_12to3_sd_tx1_n	: 1, // 16
	reg_soft_rst_srds_12to3_tp_rx0_n	: 1, // 17
	reg_soft_rst_srds_12to3_tp_rx1_n	: 1, // 18
	reg_soft_rst_srds_12to3_tp_tx0_n	: 1, // 19
	reg_soft_rst_srds_12to3_tp_tx1_n	: 1, // 20
	reg_soft_rst_srds_32to1_sd_rx0_n	: 1, // 21
	reg_soft_rst_srds_32to1_sd_rx1_n	: 1, // 22
	reg_soft_rst_srds_32to1_sd_tx0_n	: 1, // 23
	reg_soft_rst_srds_32to1_sd_tx1_n	: 1; // 24
} SCRG_ION3;

/*-----------------------------------------------------------------------------
	0x0010 scrg_ion4
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci25_clk_sel		: 2,	//  1: 0
					: 2,	//  3: 2
	reg_ci50_clk_sel		: 2,	//  5: 4
					: 2,	//  7: 6
	reg_skew_ff_sd0_clk_sel		: 1,	//  8
					: 3,	// 11: 9
	reg_skew_ff_sd1_clk_sel		: 1,	// 12
					: 3,	// 15:13
	reg_skew_ff_sd2_clk_sel		: 2,	// 17:16
					: 2,	// 19:18
	reg_skew_ff_sd3_clk_sel		: 2,	// 21:20
					: 2,	// 23:22
	reg_skew_ff_sd4_clk_sel		: 1,	// 24
					: 3,	// 27:25
	reg_skew_ff_sd5_clk_sel		: 1;	// 28
} SCRG_ION4;

/*-----------------------------------------------------------------------------
	0x0014 scrg_ion5
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_skew_ff_sd6_clk_sel		: 1,	//  0
					: 3,	//  3: 1
	reg_skew_ff_sd7_clk_sel		: 1,	//  4
					: 3,	//  7: 5
	reg_srds_12to3_sd_rx0_clk_sel	: 1,	//  8
					: 3,	// 11: 9
	reg_srds_12to3_sd_rx1_clk_sel	: 1,	// 12
					: 3,	// 15:13
	reg_srds_12to3_sd_tx0_clk_sel	: 1,	// 16
					: 3,	// 19:17
	reg_srds_12to3_sd_tx1_clk_sel	: 1,	// 20
					: 3,	// 23:21
	reg_srds_12to3_tp_rx0_clk_sel	: 3,	// 26:24
					: 1,	// 27
	reg_srds_12to3_tp_rx1_clk_sel	: 3;	// 30:28
} SCRG_ION5;

/*-----------------------------------------------------------------------------
	0x0018 scrg_ion6
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_srds_12to3_tp_tx0_clk_sel	: 3,	//  2: 0
					: 1,	//  3
	reg_srds_12to3_tp_tx1_clk_sel	: 3,	//  6: 4
					: 1,	//  7
	reg_srds_32to1_sd_rx0_clk_sel	: 1,	//  8
					: 3,	// 11: 9
	reg_srds_32to1_sd_rx1_clk_sel	: 1,	// 12
					: 3,	// 15:13
	reg_srds_32to1_sd_tx0_clk_sel	: 1,	// 16
					: 3,	// 19:17
	reg_srds_32to1_sd_tx1_clk_sel	: 1,	// 20
					: 3,	// 23:21
	reg_tpi_clk_ext1_out_sel	: 3,	// 26:24
					: 1,	// 27
	reg_tpi_clk_ext2_out_sel	: 3;	// 30:28
} SCRG_ION6;

/*-----------------------------------------------------------------------------
	0x001C scrg_ion7
  ------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tpi_clk_ext3_out_sel	: 3;	//  2: 0
} SCRG_ION7;

typedef struct {
	SCRG_ION0				scrg_ion0;	// 0x0000
	SCRG_ION1				scrg_ion1;	// 0x0004
	SCRG_ION2				scrg_ion2;	// 0x0008
	SCRG_ION3				scrg_ion3;	// 0x000C
	SCRG_ION4				scrg_ion4;	// 0x0010
	SCRG_ION5				scrg_ion5;	// 0x0014
	SCRG_ION6				scrg_ion6;	// 0x0018
	SCRG_ION7				scrg_ion7;	// 0x001C
} ION_SCRG_REG_T;

#define GET_ION_SCRG_ADDR(member) \
	(ION_SCRG_BASE_ADDRESS + offsetof(ION_SCRG_REG_T, member))

/*
 * SRDS12TO3
 */
/*-----------------------------------------------------------------------------
	0x0000 swrst ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_swrst_chk1			: 1,	//  0
	reg_swrst_chk0			: 1,	//  1
	reg_swrst_ptg1			: 1,	//  2
	reg_swrst_ptg0			: 1,	//  3
	reg_swrst_sipo1_sd		: 1,	//  4
	reg_swrst_sipo1_tp		: 1,	//  5
	reg_swrst_sipo0_sd		: 1,	//  6
	reg_swrst_sipo0_tp		: 1,	//  7
	reg_swrst_piso1_sd		: 1,	//  8
	reg_swrst_piso1_tp		: 1,	//  9
	reg_swrst_piso0_sd		: 1,	// 10
	reg_swrst_piso0_tp		: 1,	// 11
	reg_swrst_fifo1			: 1,	// 12
	reg_swrst_fifo0			: 1;	// 13
} SRDS12TO3_SWRST;

/*-----------------------------------------------------------------------------
	0x0004 mux ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_sel_sipo1_sd_in		: 1,	//  0
					: 3,	//  3: 1
	reg_sel_sipo0_sd_in		: 1,	//  4
					: 3,	//  7: 5
	reg_sel_piso1_sd_out		: 2,	//  9: 8
					: 2,	// 11:10
	reg_sel_piso0_sd_out		: 2,	// 13:12
					: 2,	// 15:14
	reg_sel_sipo1_tp_out		: 2,	// 17:16
					: 2,	// 19:18
	reg_sel_sipo0_tp_out		: 3,	// 22:20
					: 1,	// 23
	reg_sel_piso1_tp_in		: 2,	// 25:24
					: 2,	// 27:26
	reg_sel_piso0_tp_in		: 1;	// 28
} SRDS12TO3_MUX;

/*-----------------------------------------------------------------------------
	0x0008 align_cfg0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_idle_init_time1		: 8,	//  7: 0
	reg_idle_init_time0		: 8,	// 15: 8
	reg_idle_init_en1		: 1,	// 16
	reg_idle_init_en0		: 1,	// 17
	reg_check_sop1			: 1,	// 18
	reg_check_sop0			: 1,	// 19
	reg_delete_sop1			: 1,	// 20
	reg_delete_sop0			: 1,	// 21
	reg_invert_valid1		: 1,	// 22
	reg_invert_valid0		: 1,	// 23
	reg_fifo1_bypass		: 1,	// 24
	reg_fifo0_bypass		: 1,	// 25
	reg_piso1_gate_en		: 1,	// 26
	reg_piso0_gate_en		: 1,	// 27
	reg_mode_sipo1			: 1,	// 28
	reg_mode_sipo0			: 1,	// 29
	reg_mode_piso1			: 1,	// 30
	reg_mode_piso0			: 1;	// 31
} SRDS12TO3_ALIGN_CFG0;

/*-----------------------------------------------------------------------------
	0x000C start_code ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_start_code0_ext0		: 8,	//  7: 0
					: 8,	// 15: 8
	reg_start_code0_ext1		: 8;	// 23:16
} SRDS12TO3_START_CODE;

/*-----------------------------------------------------------------------------
	0x0010 st_code23_en ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_st_code2_en_ext0		: 1,	//  0
	reg_st_code3_en_ext0		: 1,	//  1
	reg_tlv_en_ext0			: 1,	//  2
					: 1,	//  3
	reg_st_code2_en_ext1		: 1,	//  4
	reg_st_code3_en_ext1		: 1,	//  5
	reg_tlv_en_ext1			: 1;	//  6
} SRDS12TO3_ST_CODE23_EN;

/*-----------------------------------------------------------------------------
	0x0014 ptg_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_chk1_mode			: 1,	//  0
	reg_chk1_en			: 1,	//  1
					: 2,	//  3: 2
	reg_chk0_mode			: 1,	//  4
	reg_chk0_en			: 1,	//  5
					: 2,	//  7: 6
	reg_ptg1_en			: 1,	//  8
	reg_ptg0_en			: 1,	//  9
					: 2,	// 11:10
	result_valid1			: 1,	// 12
	result_valid0			: 1;	// 13
} SRDS12TO3_PTG_CFG;

/*-----------------------------------------------------------------------------
	0x0018 ptg_pkt0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tp_pkt_size			: 8;	//  7: 0
} SRDS12TO3_PTG_PKT0;

/*-----------------------------------------------------------------------------
	0x001C ptg_pkt1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tp_pkt_spacing		: 16,	// 15: 0
	reg_tp_pkt_num			: 16;	// 31:16
} SRDS12TO3_PTG_PKT1;

/*-----------------------------------------------------------------------------
	0x0020 chk_tm0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_chk0_timer			: 32;	// 31: 0
} SRDS12TO3_CHK_TM0;

/*-----------------------------------------------------------------------------
	0x0024 chk_tm1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_chk1_timer			: 32;	// 31: 0
} SRDS12TO3_CHK_TM1;

/*-----------------------------------------------------------------------------
	0x0028 chk_cnt0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	err_pkt_cnt0			: 16,	// 15: 0
	rx_pkt_cnt0			: 16;	// 31:16
} SRDS12TO3_CHK_CNT0;

/*-----------------------------------------------------------------------------
	0x002C chk_cnt1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	err_pkt_cnt1			: 16,	// 15: 0
	rx_pkt_cnt1			: 16;	// 31:16
} SRDS12TO3_CHK_CNT1;

typedef struct {
	SRDS12TO3_SWRST				swrst;		// 0x0000: ''
	SRDS12TO3_MUX				mux;		// 0x0004: ''
	SRDS12TO3_ALIGN_CFG0			align_cfg0;	// 0x0008: ''
	SRDS12TO3_START_CODE			start_code;	// 0x000C: ''
	SRDS12TO3_ST_CODE23_EN			st_code23_en;	// 0x0010: ''
	SRDS12TO3_PTG_CFG			ptg_cfg;	// 0x0014: ''
	SRDS12TO3_PTG_PKT0			ptg_pkt0;	// 0x0018: ''
	SRDS12TO3_PTG_PKT1			ptg_pkt1;	// 0x001C: ''
	SRDS12TO3_CHK_TM0			chk_tm0;	// 0x0020: ''
	SRDS12TO3_CHK_TM1			chk_tm1;	// 0x0024: ''
	SRDS12TO3_CHK_CNT0			chk_cnt0;	// 0x0028: ''
	SRDS12TO3_CHK_CNT1			chk_cnt1;	// 0x002C: ''
} SRDS12TO3_REG_T;

#define GET_SRDS12TO3_ADDR(member) \
	(SRDS12TO3_BASE_ADDRESS + offsetof(SRDS12TO3_REG_T, member))

/*
 * SRDS32TO1
 */
/*-----------------------------------------------------------------------------
	0x0000 swrst ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
					: 6,	//  5: 0
	reg_swrst_sipo0_fst		: 1,	//  6
	reg_swrst_sipo0_slo		: 1,	//  7
					: 2,	//  9: 8
	reg_swrst_piso0_fst		: 1,	// 10
	reg_swrst_piso0_slo		: 1,	// 11
					: 1,	// 12
	reg_swrst_dan0			: 1,	// 13
					: 1,	// 14
	reg_swrst_dap0			: 1;	// 15
} SRDS32TO1_SWRST;

/*-----------------------------------------------------------------------------
	0x0004 mux ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
					: 4,	//  3: 0
	reg_sel_sipo0_sd_in		: 1,	//  4
					: 7,	// 11: 5
	reg_sel_piso0_sd_out		: 2,	// 13:12
					: 6,	// 19:14
	reg_sel_sipo0_tp_out		: 2,	// 21:20
					: 6,	// 27:22
	reg_sel_piso0_tp_in		: 1;	// 28
} SRDS32TO1_MUX;

/*-----------------------------------------------------------------------------
	0x0008 align_cfg0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_sw_dap_stop0		: 1,	//  0
					: 3,	//  3: 1
	reg_sw_dap_en0			: 1,	//  4
					: 3,	//  7: 5
	reg_sw_da_en0			: 1,	//  8
					: 3,	// 11: 9
	reg_sw_piso0_ivalid0		: 1,	// 12
	reg_sw_sipo0_ivalid0		: 1,	// 13
					: 2,	// 15:14
	reg_sipo_out_dbgen0		: 1,	// 16
	reg_piso_in_dbgen0		: 1,	// 17
					: 2,	// 19:18
	align_ok0			: 1,	// 20
					: 3,	// 23:21
	dap_complete0			: 1,	// 24
					: 3,	// 27:25
	reg_mode			: 2,	// 29:28
	reg_tr_2nd			: 1;	// 30
} SRDS32TO1_ALIGN_CFG0;

/*-----------------------------------------------------------------------------
	0x000C align_cfg1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	sipo_out_dbg0;				// 31: 0
} SRDS32TO1_ALIGN_CFG1;

/*-----------------------------------------------------------------------------
	0x0010 align_cfg2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	piso_in_dbg0;				// 31: 0
} SRDS32TO1_ALIGN_CFG2;

/*-----------------------------------------------------------------------------
	0x0028 tstmp_err ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	err_tstmp_status		: 1,	//  0
					: 3,	//  3: 1
	reg_err_tstmp_en		: 1,	//  4
					: 3,	//  7: 5
	reg_err_tstmp_clr		: 1,	//  8
					: 7,	// 15: 9
	err_tstmp_cur			: 8,	// 23:16
	err_tstmp_pre			: 8;	// 31:24
} SRDS32TO1_TSTMP_ERR;

/*-----------------------------------------------------------------------------
	0x002C intr_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	intr_tstmp_err			: 1,	//  0
					: 3,	//  3: 1
	reg_intr_en			: 1,	//  4
	reg_intr_clear			: 1,	//  5
	reg_intr_edge_en		: 1,	//  6
	reg_intr_polar_high_en		: 1;	//  7
} SRDS32TO1_INTR_CFG;

/*-----------------------------------------------------------------------------
	0x0030 pd_igate_en0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_gate_en0;			// 31: 0
} SRDS32TO1_PD_IGATE_EN0;

/*-----------------------------------------------------------------------------
	0x0034 pd_igate_dat0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_gate_dat0;			// 31: 0
} SRDS32TO1_PD_IGATE_DAT0;

/*-----------------------------------------------------------------------------
	0x0038 pd_ogate_en0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_out_gate_en0;			// 31: 0
} SRDS32TO1_PD_OGATE_EN0;

/*-----------------------------------------------------------------------------
	0x003C pd_ogate_dat0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_out_gate_dat0;			// 31: 0
} SRDS32TO1_PD_OGATE_DAT0;

/*-----------------------------------------------------------------------------
	0x0040 scl_hold0_en ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold0_en		: 10;	//  9: 0
} SRDS32TO1_SCL_HOLD0_EN;

/*-----------------------------------------------------------------------------
	0x0044 pd_i2c_en0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pullup_en;			// 31: 0
} SRDS32TO1_PD_I2C_EN0;

/*-----------------------------------------------------------------------------
	0x0048 pd_piso0_dly0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_piso_dly0;			// 31: 0
} SRDS32TO1_PD_PISO0_DLY0;

/*-----------------------------------------------------------------------------
	0x004C pd_piso0_dly1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_piso_dly1;			// 31: 0
} SRDS32TO1_PD_PISO0_DLY1;

/*-----------------------------------------------------------------------------
	0x0050 pd_sipo0_dly0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_sipo_dly0;			// 31: 0
} SRDS32TO1_PD_SIPO0_DLY0;

/*-----------------------------------------------------------------------------
	0x0054 pd_sipo0_dly1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_sipo_dly1;			// 31: 0
} SRDS32TO1_PD_SIPO0_DLY1;

/*-----------------------------------------------------------------------------
	0x0058 tstmp_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	tstmp_piso			: 8,	//  7: 0
	reg_tstmp_piso_en		: 1,	//  8
	reg_autostop_tstmp_piso		: 1,	//  9
					: 2,	// 11:10
	reg_reset_stmp_piso		: 1,	// 12
					: 3,	// 15:13
	tstmp_sipo			: 8,	// 23:16
	reg_tstmp_sipo_en		: 1,	// 24
					: 3,	// 27:25
	reg_reset_stmp_sipo		: 1;	// 28
} SRDS32TO1_TSTMP_CTRL;

/*-----------------------------------------------------------------------------
	0x005C chg_tstmp ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_chg_tstmp_piso		: 8,	//  7: 0
					: 8,	// 15: 8
	reg_chg_tstmp_sipo		: 8;	// 23:16
} SRDS32TO1_CHG_TSTMP;

/*-----------------------------------------------------------------------------
	0x0060 chg_mode ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_chg_mode_piso		: 1,	//  0
					:15,	// 15: 1
	reg_chg_mode_sipo		: 1,	// 16
					: 3,	// 19:17
	mode_chged_ok			: 1;	// 20
} SRDS32TO1_CHG_MODE;

/*-----------------------------------------------------------------------------
	0x0068 pd_i2c_chg ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_piso_i2c_chg		:10,	//  9: 0
					: 6,	// 15:10
	reg_pd_sipo_i2c_chg		:10;	// 25:16
} SRDS32TO1_PD_I2C_CHG;

/*-----------------------------------------------------------------------------
	0x006C pd_debnc_en ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_en;			// 31: 0
} SRDS32TO1_PD_DEBNC_EN;

/*-----------------------------------------------------------------------------
	0x0070 pd_debnc_len7 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_len28		: 6,	//  5: 0
					: 2,	//  7: 6
	reg_pd_in_debnc_len29		: 6,	// 13: 8
					: 2,	// 15:14
	reg_pd_in_debnc_len30		: 6,	// 21:16
					: 2,	// 23:22
	reg_pd_in_debnc_len31		: 6;	// 29:24
} SRDS32TO1_PD_DEBNC_LEN7;

/*-----------------------------------------------------------------------------
	0x0074 pd_debnc_len6 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_len24		: 6,	//  5: 0
					: 2,	//  7: 6
	reg_pd_in_debnc_len25		: 6,	// 13: 8
					: 2,	// 15:14
	reg_pd_in_debnc_len26		: 6,	// 21:16
					: 2,	// 23:22
	reg_pd_in_debnc_len27		: 6;	// 29:24
} SRDS32TO1_PD_DEBNC_LEN6;

/*-----------------------------------------------------------------------------
	0x0078 pd_debnc_len5 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_len20		: 6,	//  5: 0
					: 2,	//  7: 6
	reg_pd_in_debnc_len21		: 6,	// 13: 8
					: 2,	// 15:14
	reg_pd_in_debnc_len22		: 6,	// 21:16
					: 2,	// 23:22
	reg_pd_in_debnc_len23		: 6;	// 29:24
} SRDS32TO1_PD_DEBNC_LEN5;

/*-----------------------------------------------------------------------------
	0x007C pd_debnc_len4 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_len16		: 6,	//  5: 0
					: 2,	//  7: 6
	reg_pd_in_debnc_len17		: 6,	// 13: 8
					: 2,	// 15:14
	reg_pd_in_debnc_len18		: 6,	// 21:16
					: 2,	// 23:22
	reg_pd_in_debnc_len19		: 6;	// 29:24
} SRDS32TO1_PD_DEBNC_LEN4;

/*-----------------------------------------------------------------------------
	0x0080 pd_debnc_len3 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_len12		: 6,	//  5: 0
					: 2,	//  7: 6
	reg_pd_in_debnc_len13		: 6,	// 13: 8
					: 2,	// 15:14
	reg_pd_in_debnc_len14		: 6,	// 21:16
					: 2,	// 23:22
	reg_pd_in_debnc_len15		: 6;	// 29:24
} SRDS32TO1_PD_DEBNC_LEN3;

/*-----------------------------------------------------------------------------
	0x0084 pd_debnc_len2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_len8		: 6,	//  5: 0
					: 2,	//  7: 6
	reg_pd_in_debnc_len9		: 6,	// 13: 8
					: 2,	// 15:14
	reg_pd_in_debnc_len10		: 6,	// 21:16
					: 2,	// 23:22
	reg_pd_in_debnc_len11		: 6;	// 29:24
} SRDS32TO1_PD_DEBNC_LEN2;

/*-----------------------------------------------------------------------------
	0x0088 pd_debnc_len1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_len4		: 6,	//  5: 0
					: 2,	//  7: 6
	reg_pd_in_debnc_len5		: 6,	// 13: 8
					: 2,	// 15:14
	reg_pd_in_debnc_len6		: 6,	// 21:16
					: 2,	// 23:22
	reg_pd_in_debnc_len7		: 6;	// 29:24
} SRDS32TO1_PD_DEBNC_LEN1;

/*-----------------------------------------------------------------------------
	0x008C pd_debnc_len0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pd_in_debnc_len0		: 6,	//  5: 0
					: 2,	//  7: 6
	reg_pd_in_debnc_len1		: 6,	// 13: 8
					: 2,	// 15:14
	reg_pd_in_debnc_len2		: 6,	// 21:16
					: 2,	// 23:22
	reg_pd_in_debnc_len3		: 6;	// 29:24
} SRDS32TO1_PD_DEBNC_LEN0;

/*-----------------------------------------------------------------------------
	0x0090 pd_pu_dly7 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pu_dly28		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pu_dly29		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pu_dly30		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pu_dly31		: 5;	// 28:24
} SRDS32TO1_PD_PU_DLY7;

/*-----------------------------------------------------------------------------
	0x0094 pd_pu_dly6 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pu_dly24		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pu_dly25		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pu_dly26		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pu_dly27		: 5;	// 28:24
} SRDS32TO1_PD_PU_DLY6;

/*-----------------------------------------------------------------------------
	0x0098 pd_pu_dly5 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pu_dly20		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pu_dly21		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pu_dly22		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pu_dly23		: 5;	// 28:24
} SRDS32TO1_PD_PU_DLY5;

/*-----------------------------------------------------------------------------
	0x009C pd_pu_dly4 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pu_dly16		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pu_dly17		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pu_dly18		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pu_dly19		: 5;	// 28:24
} SRDS32TO1_PD_PU_DLY4;

/*-----------------------------------------------------------------------------
	0x00A0 pd_pu_dly3 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pu_dly12		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pu_dly13		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pu_dly14		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pu_dly15		: 5;	// 28:24
} SRDS32TO1_PD_PU_DLY3;

/*-----------------------------------------------------------------------------
	0x00A4 pd_pu_dly2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pu_dly8		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pu_dly9		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pu_dly10		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pu_dly11		: 5;	// 28:24
} SRDS32TO1_PD_PU_DLY2;

/*-----------------------------------------------------------------------------
	0x00A8 pd_pu_dly1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pu_dly4		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pu_dly5		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pu_dly6		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pu_dly7		: 5;	// 28:24
} SRDS32TO1_PD_PU_DLY1;

/*-----------------------------------------------------------------------------
	0x00AC pd_pu_dly0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pu_dly0		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pu_dly1		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pu_dly2		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pu_dly3		: 5;	// 28:24
} SRDS32TO1_PD_PU_DLY0;

/*-----------------------------------------------------------------------------
	0x00B0 scl_low_cnt9 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt9		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt9		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT9;

/*-----------------------------------------------------------------------------
	0x00B4 scl_low_cnt8 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt8		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt8		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT8;

/*-----------------------------------------------------------------------------
	0x00B8 scl_low_cnt7 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt7		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt7		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT7;

/*-----------------------------------------------------------------------------
	0x00BC scl_low_cnt6 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt6		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt6		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT6;

/*-----------------------------------------------------------------------------
	0x00C0 scl_low_cnt5 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt5		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt5		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT5;

/*-----------------------------------------------------------------------------
	0x00C4 scl_low_cnt4 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt4		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt4		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT4;

/*-----------------------------------------------------------------------------
	0x00C8 scl_low_cnt3 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt3		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt3		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT3;

/*-----------------------------------------------------------------------------
	0x00CC scl_low_cnt2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt2		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt2		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT2;

/*-----------------------------------------------------------------------------
	0x00D0 scl_low_cnt1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt1		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt1		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT1;

/*-----------------------------------------------------------------------------
	0x00D4 scl_low_cnt0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_scl_hold_cnt0		: 7,	//  6: 0
					: 9,	// 15: 7
	reg_scl_low_cnt0		:10;	// 25:16
} SRDS32TO1_SCL_LOW_CNT0;

/*-----------------------------------------------------------------------------
	0x00E0 pd_pd_dly7 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pd_dly28		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pd_dly29		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pd_dly30		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pd_dly31		: 5;	// 28:24
} SRDS32TO1_PD_PD_DLY7;

/*-----------------------------------------------------------------------------
	0x00E4 pd_pd_dly6 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pd_dly24		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pd_dly25		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pd_dly26		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pd_dly27		: 5;	// 28:24
} SRDS32TO1_PD_PD_DLY6;

/*-----------------------------------------------------------------------------
	0x00E8 pd_pd_dly5 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pd_dly20		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pd_dly21		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pd_dly22		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pd_dly23		: 5;	// 28:24
} SRDS32TO1_PD_PD_DLY5;

/*-----------------------------------------------------------------------------
	0x00EC pd_pd_dly4 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pd_dly16		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pd_dly17		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pd_dly18		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pd_dly19		: 5;	// 28:24
} SRDS32TO1_PD_PD_DLY4;

/*-----------------------------------------------------------------------------
	0x00F0 pd_pd_dly3 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pd_dly12		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pd_dly13		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pd_dly14		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pd_dly15		: 5;	// 28:24
} SRDS32TO1_PD_PD_DLY3;

/*-----------------------------------------------------------------------------
	0x00F4 pd_pd_dly2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pd_dly8		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pd_dly9		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pd_dly10		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pd_dly11		: 5;	// 28:24
} SRDS32TO1_PD_PD_DLY2;

/*-----------------------------------------------------------------------------
	0x00F8 pd_pd_dly1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pd_dly4		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pd_dly5		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pd_dly6		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pd_dly7		: 5;	// 28:24
} SRDS32TO1_PD_PD_DLY1;

/*-----------------------------------------------------------------------------
	0x00FC pd_pd_dly0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_test_pd_dly0		: 5,	//  4: 0
					: 3,	//  7: 5
	reg_test_pd_dly1		: 5,	// 12: 8
					: 3,	// 15:13
	reg_test_pd_dly2		: 5,	// 20:16
					: 3,	// 23:21
	reg_test_pd_dly3		: 5;	// 28:24
} SRDS32TO1_PD_PD_DLY0;

typedef struct {
	SRDS32TO1_SWRST		swrst;		// 0x0000: ''
	SRDS32TO1_MUX		mux;		// 0x0004: ''
	SRDS32TO1_ALIGN_CFG0	align_cfg0;	// 0x0008: ''
	SRDS32TO1_ALIGN_CFG1	align_cfg1;	// 0x000C: ''
	SRDS32TO1_ALIGN_CFG2	align_cfg2;	// 0x0010: ''
	u32			__rsvd__0[5];	// 0x0014 ~ 0x0024
	SRDS32TO1_TSTMP_ERR	tstmp_err;	// 0x0028: ''
	SRDS32TO1_INTR_CFG	intr_cfg;	// 0x002C: ''
	SRDS32TO1_PD_IGATE_EN0	pd_igate_en0;	// 0x0030: ''
	SRDS32TO1_PD_IGATE_DAT0	pd_igate_dat0;	// 0x0034: ''
	SRDS32TO1_PD_OGATE_EN0	pd_ogate_en0;	// 0x0038: ''
	SRDS32TO1_PD_OGATE_DAT0	pd_ogate_dat0;	// 0x003C: ''
	SRDS32TO1_SCL_HOLD0_EN	scl_hold0_en;	// 0x0040: ''
	SRDS32TO1_PD_I2C_EN0	pd_i2c_en0;	// 0x0044: ''
	SRDS32TO1_PD_PISO0_DLY0	pd_piso0_dly0;	// 0x0048: ''
	SRDS32TO1_PD_PISO0_DLY1	pd_piso0_dly1;	// 0x004C: ''
	SRDS32TO1_PD_SIPO0_DLY0	pd_sipo0_dly0;	// 0x0050: ''
	SRDS32TO1_PD_SIPO0_DLY1	pd_sipo0_dly1;	// 0x0054: ''
	SRDS32TO1_TSTMP_CTRL	tstmp_ctrl;	// 0x0058: ''
	SRDS32TO1_CHG_TSTMP	chg_tstmp;	// 0x005C: ''
	SRDS32TO1_CHG_MODE	chg_mode;	// 0x0060: ''
	u32			__rsvd__1;	// 0x0064: ''
	SRDS32TO1_PD_I2C_CHG	pd_i2c_chg;	// 0x0068: ''
	SRDS32TO1_PD_DEBNC_EN	pd_debnc_en;	// 0x006C: ''
	SRDS32TO1_PD_DEBNC_LEN7	pd_debnc_len7;	// 0x0070: ''
	SRDS32TO1_PD_DEBNC_LEN6	pd_debnc_len6;	// 0x0074: ''
	SRDS32TO1_PD_DEBNC_LEN5	pd_debnc_len5;	// 0x0078: ''
	SRDS32TO1_PD_DEBNC_LEN4	pd_debnc_len4;	// 0x007C: ''
	SRDS32TO1_PD_DEBNC_LEN3	pd_debnc_len3;	// 0x0080: ''
	SRDS32TO1_PD_DEBNC_LEN2	pd_debnc_len2;	// 0x0084: ''
	SRDS32TO1_PD_DEBNC_LEN1	pd_debnc_len1;	// 0x0088: ''
	SRDS32TO1_PD_DEBNC_LEN0	pd_debnc_len0;	// 0x008C: ''
	SRDS32TO1_PD_PU_DLY7	pd_pu_dly7;	// 0x0090: ''
	SRDS32TO1_PD_PU_DLY6	pd_pu_dly6;	// 0x0094: ''
	SRDS32TO1_PD_PU_DLY5	pd_pu_dly5;	// 0x0098: ''
	SRDS32TO1_PD_PU_DLY4	pd_pu_dly4;	// 0x009C: ''
	SRDS32TO1_PD_PU_DLY3	pd_pu_dly3;	// 0x00A0: ''
	SRDS32TO1_PD_PU_DLY2	pd_pu_dly2;	// 0x00A4: ''
	SRDS32TO1_PD_PU_DLY1	pd_pu_dly1;	// 0x00A8: ''
	SRDS32TO1_PD_PU_DLY0	pd_pu_dly0;	// 0x00AC: ''
	SRDS32TO1_SCL_LOW_CNT9	scl_low_cnt9;	// 0x00B0: ''
	SRDS32TO1_SCL_LOW_CNT8	scl_low_cnt8;	// 0x00B4: ''
	SRDS32TO1_SCL_LOW_CNT7	scl_low_cnt7;	// 0x00B8: ''
	SRDS32TO1_SCL_LOW_CNT6	scl_low_cnt6;	// 0x00BC: ''
	SRDS32TO1_SCL_LOW_CNT5	scl_low_cnt5;	// 0x00C0: ''
	SRDS32TO1_SCL_LOW_CNT4	scl_low_cnt4;	// 0x00C4: ''
	SRDS32TO1_SCL_LOW_CNT3	scl_low_cnt3;	// 0x00C8: ''
	SRDS32TO1_SCL_LOW_CNT2	scl_low_cnt2;	// 0x00CC: ''
	SRDS32TO1_SCL_LOW_CNT1	scl_low_cnt1;	// 0x00D0: ''
	SRDS32TO1_SCL_LOW_CNT0	scl_low_cnt0;	// 0x00D4: ''
	u32			__rsvd__2[2];	// 0x00D8 ~ 0x00DC
	SRDS32TO1_PD_PD_DLY7	pd_pd_dly7;	// 0x00E0: ''
	SRDS32TO1_PD_PD_DLY6	pd_pd_dly6;	// 0x00E4: ''
	SRDS32TO1_PD_PD_DLY5	pd_pd_dly5;	// 0x00E8: ''
	SRDS32TO1_PD_PD_DLY4	pd_pd_dly4;	// 0x00EC: ''
	SRDS32TO1_PD_PD_DLY3	pd_pd_dly3;	// 0x00F0: ''
	SRDS32TO1_PD_PD_DLY2	pd_pd_dly2;	// 0x00F4: ''
	SRDS32TO1_PD_PD_DLY1	pd_pd_dly1;	// 0x00F8: ''
	SRDS32TO1_PD_PD_DLY0	pd_pd_dly0;	// 0x00FC: ''
} SRDS32TO1_REG_T;

//u32					__rsvd__0;
/*
 * IOMUX_CTRL
 */
/*-----------------------------------------------------------------------------
	0x0000 pad_ion_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_gpio07_mux_sel		: 4,	//  3: 0
	reg_pad_gpio05_mux_sel		: 4,	//  7: 4
	reg_pad_gpio04_mux_sel		: 4,	// 11: 8
	reg_pad_gpio03_mux_sel		: 4,	// 15:12
	reg_pad_gpio02_mux_sel		: 4,	// 19:16
	reg_pad_gpio01_mux_sel		: 4,	// 23:20
	reg_pad_gpio00_mux_sel		: 4,	// 27:24
	reg_pad_cicam_clk_mux_sel	: 4;	// 31:28
} PAD_ION_00;

/*-----------------------------------------------------------------------------
	0x0004 pad_ion_01
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_hdmi_1_scl_mux_sel	: 4,	//  3: 0
	reg_pad_hdmi_1_hpd_mux_sel	: 4,	//  7: 4
	reg_pad_hdmi_det1_mux_sel	: 4,	// 11: 8
	reg_pad_hdmi_1_5v_in_mux_sel	: 4,	// 15:12
	reg_pad_gpio11_mux_sel		: 4,	// 19:16
	reg_pad_gpio10_mux_sel		: 4,	// 23:20
	reg_pad_gpio09_mux_sel		: 4,	// 27:24
	reg_pad_gpio08_mux_sel		: 4;	// 31:28
} PAD_ION_01;

/*-----------------------------------------------------------------------------
	0x0008 pad_ion_02
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_hdmi_det3_mux_sel	: 4,	//  3: 0
	reg_pad_hdmi_3_5v_in_mux_sel	: 4,	//  7: 4
	reg_pad_hdmi_2_sda_mux_sel	: 4,	// 11: 8
	reg_pad_hdmi_2_scl_mux_sel	: 4,	// 15:12
	reg_pad_hdmi_2_hpd_mux_sel	: 4,	// 19:16
	reg_pad_hdmi_det2_mux_sel	: 4,	// 23:20
	reg_pad_hdmi_2_5v_in_mux_sel	: 4,	// 27:24
	reg_pad_hdmi_1_sda_mux_sel	: 4;	// 31:28
} PAD_ION_02;

/*-----------------------------------------------------------------------------
	0x000C pad_ion_03
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_hdmi_4_sda_mux_sel	: 4,	//  3: 0
	reg_pad_hdmi_4_scl_mux_sel	: 4,	//  7: 4
	reg_pad_hdmi_4_hpd_mux_sel	: 4,	// 11: 8
	reg_pad_hdmi_det4_mux_sel	: 4,	// 15:12
	reg_pad_hdmi_4_5v_in_mux_sel	: 4,	// 19:16
	reg_pad_hdmi_3_sda_mux_sel	: 4,	// 23:20
	reg_pad_hdmi_3_scl_mux_sel	: 4,	// 27:24
	reg_pad_hdmi_3_hpd_mux_sel	: 4;	// 31:28
} PAD_ION_03;

/*-----------------------------------------------------------------------------
	0x0010 pad_ion_04
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_sda1_mux_sel		: 4,	//  3: 0
	reg_pad_sda0_mux_sel		: 4,	//  7: 4
	reg_pad_scl5_mux_sel		: 4,	// 11: 8
	reg_pad_scl4_mux_sel		: 4,	// 15:12
	reg_pad_scl3_mux_sel		: 4,	// 19:16
	reg_pad_scl2_mux_sel		: 4,	// 23:20
	reg_pad_scl1_mux_sel		: 4,	// 27:24
	reg_pad_scl0_mux_sel		: 4;	// 31:28
} PAD_ION_04;

/*-----------------------------------------------------------------------------
	0x0014 pad_ion_05
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_tpi_data0_ext2_mux_sel	: 4,	//  3: 0
	reg_pad_tpi_data0_ext1_mux_sel	: 4,	//  7: 4
	reg_pad_tpi_clk_ext2_mux_sel	: 4,	// 11: 8
	reg_pad_tpi_clk_ext1_mux_sel	: 4,	// 15:12
	reg_pad_sda5_mux_sel		: 4,	// 19:16
	reg_pad_sda4_mux_sel		: 4,	// 23:20
	reg_pad_sda3_mux_sel		: 4,	// 27:24
	reg_pad_sda2_mux_sel		: 4;	// 31:28
} PAD_ION_05;

/*-----------------------------------------------------------------------------
	0x0018 pad_ion_06
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_tpi_data4_ext2_mux_sel	: 4,	//  3: 0
	reg_pad_tpi_data4_ext1_mux_sel	: 4,	//  7: 3
	reg_pad_tpi_data3_ext2_mux_sel	: 4,	// 11: 8
	reg_pad_tpi_data3_ext1_mux_sel	: 4,	// 15:12
	reg_pad_tpi_data2_ext2_mux_sel	: 4,	// 19:16
	reg_pad_tpi_data2_ext1_mux_sel	: 4,	// 23:20
	reg_pad_tpi_data1_ext2_mux_sel	: 4,	// 27:24
	reg_pad_tpi_data1_ext1_mux_sel	: 4;	// 31:28
} PAD_ION_06;

/*-----------------------------------------------------------------------------
	0x001C pad_ion_07
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_tpi_sop_ext2_mux_sel	: 4,	//  3: 0
	reg_pad_tpi_sop_ext1_mux_sel	: 4,	//  7: 3
	reg_pad_tpi_data7_ext2_mux_sel	: 4,	// 11: 8
	reg_pad_tpi_data7_ext1_mux_sel	: 4,	// 15:12
	reg_pad_tpi_data6_ext2_mux_sel	: 4,	// 19:16
	reg_pad_tpi_data6_ext1_mux_sel	: 4,	// 23:20
	reg_pad_tpi_data5_ext2_mux_sel	: 4,	// 27:24
	reg_pad_tpi_data5_ext1_mux_sel	: 4;	// 31:28
} PAD_ION_07;

/*-----------------------------------------------------------------------------
	0x0020 pad_ion_08
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_tu_io_sd03_mux_sel	: 4,	//  3: 0
	reg_pad_tu_io_sd02_mux_sel	: 4,	//  7: 4
	reg_pad_tu_io_sd01_mux_sel	: 4,	// 11: 8
	reg_pad_tu_io_sd00_mux_sel	: 4,	// 15:12
	reg_pad_tu_io_clk_mux_sel	: 4,	// 19:16
	reg_pad_tpi_val_ext2_mux_sel	: 4,	// 23:20
	reg_pad_tpi_val_ext1_mux_sel	: 4;	// 27:24
} PAD_ION_08;

/*-----------------------------------------------------------------------------
	0x0024 pad_ion_09
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_tu_io_spi_do_mux_sel	: 4,	//  3: 0
	reg_pad_tu_io_spi_di_mux_sel	: 4,	//  7: 4
	reg_pad_tu_io_spi_cs_mux_sel	: 4,	// 11: 8
	reg_pad_tu_io_spi_clk_mux_sel	: 4,	// 15:12
	reg_pad_tu_io_sd07_mux_sel	: 4,	// 19:16
	reg_pad_tu_io_sd06_mux_sel	: 4,	// 23:20
	reg_pad_tu_io_sd05_mux_sel	: 4,	// 27:24
	reg_pad_tu_io_sd04_mux_sel	: 4;	// 31:28
} PAD_ION_09;

/*-----------------------------------------------------------------------------
	0x0030 pad_ion_10
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_tu_io_sd07__IE		: 1,	//  0
	reg_pad_tu_io_sd07__PE		: 1,	//  1
	reg_pad_tu_io_sd07__DS		: 1,	//  2
					: 1,	//  3
	reg_pad_tu_io_sd06__IE		: 1,	//  4
	reg_pad_tu_io_sd06__PE		: 1,	//  5
	reg_pad_tu_io_sd06__DS		: 1,	//  6
					: 1,	//  7
	reg_pad_tu_io_sd05__IE		: 1,	//  8
	reg_pad_tu_io_sd05__PE		: 1,	//  9
	reg_pad_tu_io_sd05__DS		: 1,	// 10
					: 1,	// 11
	reg_pad_tu_io_sd04__IE		: 1,	// 12
	reg_pad_tu_io_sd04__PE		: 1,	// 13
	reg_pad_tu_io_sd04__DS		: 1,	// 14
					: 1,	// 15
	reg_pad_tu_io_sd03__IE		: 1,	// 16
	reg_pad_tu_io_sd03__PE		: 1,	// 17
	reg_pad_tu_io_sd03__DS		: 1,	// 18
					: 1,	// 19
	reg_pad_tu_io_sd02__IE		: 1,	// 20
	reg_pad_tu_io_sd02__PE		: 1,	// 21
	reg_pad_tu_io_sd02__DS		: 1,	// 22
					: 1,	// 23
	reg_pad_tu_io_sd01__IE		: 1,	// 24
	reg_pad_tu_io_sd01__PE		: 1,	// 25
	reg_pad_tu_io_sd01__DS		: 1,	// 26
					: 1,	// 27
	reg_pad_tu_io_sd00__IE		: 1,	// 28
	reg_pad_tu_io_sd00__PE		: 1,	// 29
	reg_pad_tu_io_sd00__DS		: 1;	// 30
} PAD_ION_10;

/*-----------------------------------------------------------------------------
	0x0034 pad_ion_11
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_pad_tu_io_pores_n__IE	: 1,	//  0
	reg_pad_tu_io_pores_n__PE	: 1,	//  1
	reg_pad_tu_io_pores_n__DS	: 1,	//  2
					: 1,	//  3
	reg_pad_cicam_clk__IE		: 1,	//  4
	reg_pad_cicam_clk__PE		: 1,	//  5
	reg_pad_cicam_clk__DS		: 1,	//  6
					: 1,	//  7
	reg_pad_tu_io_clk__IE		: 1,	//  8
	reg_pad_tu_io_clk__PE		: 1,	//  9
	reg_pad_tu_io_clk__DS		: 1,	// 10
					: 1,	// 11
	reg_pad_tu_io_spi_do__IE	: 1,	// 12
	reg_pad_tu_io_spi_do__PE	: 1,	// 13
	reg_pad_tu_io_spi_do__DS	: 1,	// 14
					: 1,	// 15
	reg_pad_tu_io_spi_di__IE	: 1,	// 16
	reg_pad_tu_io_spi_di__PE	: 1,	// 17
	reg_pad_tu_io_spi_di__DS	: 1,	// 18
					: 1,	// 19
	reg_pad_tu_io_spi_cs__IE	: 1,	// 20
	reg_pad_tu_io_spi_cs__PE	: 1,	// 21
	reg_pad_tu_io_spi_cs__DS	: 1,	// 22
					: 1,	// 23
	reg_pad_tu_io_spi_clk__IE	: 1,	// 24
	reg_pad_tu_io_spi_clk__PE	: 1,	// 25
	reg_pad_tu_io_spi_clk__DS	: 1;	// 26
} PAD_ION_11;

/*-----------------------------------------------------------------------------
	0x0040 pad_ion_12
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_gpio_oen_00			: 1,	//  0
	reg_gpio_oen_01			: 1,	//  1
	reg_gpio_oen_02			: 1,	//  2
	reg_gpio_oen_03			: 1,	//  3
	reg_gpio_oen_04			: 1,	//  4
	reg_gpio_oen_05			: 1,	//  5
	reg_gpio_oen_07			: 1,	//  6
	reg_gpio_oen_08			: 1,	//  7
	reg_gpio_oen_09			: 1,	//  8
	reg_gpio_oen_10			: 1,	//  9
	reg_gpio_oen_11			: 1;	// 10
} PAD_ION_12;

/*-----------------------------------------------------------------------------
	0x0044 pad_ion_13
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_bypass_gpio00_oen_toExtDevice	: 1,	//  0
	reg_bypass_gpio01_oen_toExtDevice	: 1,	//  1
	reg_bypass_gpio02_oen_toExtDevice	: 1,	//  2
	reg_bypass_gpio03_oen_toExtDevice	: 1,	//  3
	reg_bypass_gpio04_oen_toExtDevice	: 1,	//  4
	reg_bypass_gpio05_oen_toExtDevice	: 1,	//  5
	reg_bypass_gpio06_oen_toExtDevice	: 1,	//  6
	reg_bypass_gpio07_oen_toExtDevice	: 1;	//  7
} PAD_ION_13;

/*-----------------------------------------------------------------------------
	0x0048 pad_ion_14
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_bypass_gpio00_oen_toO26	: 1,	//  0
	reg_bypass_gpio01_oen_toO26	: 1,	//  1
	reg_bypass_gpio02_oen_toO26	: 1,	//  2
	reg_bypass_gpio03_oen_toO26	: 1,	//  3
	reg_bypass_gpio04_oen_toO26	: 1,	//  4
	reg_bypass_gpio05_oen_toO26	: 1,	//  5
	reg_bypass_gpio06_oen_toO26	: 1,	//  6
	reg_bypass_gpio07_oen_toO26	: 1;	//  7
} PAD_ION_14;

/*-----------------------------------------------------------------------------
	0x004C pad_ion_15
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_aux_gpio00_oen		: 1,	//  0
	reg_aux_gpio01_oen		: 1,	//  1
	reg_aux_gpio02_oen		: 1,	//  2
	reg_aux_gpio03_oen		: 1,	//  3
	reg_aux_gpio04_oen		: 1,	//  4
	reg_aux_gpio05_oen		: 1,	//  5
	reg_aux_gpio06_oen		: 1,	//  6
	reg_aux_gpio07_oen		: 1,	//  7
	reg_aux_gpio08_oen		: 1,	//  8
	reg_aux_gpio09_oen		: 1,	//  9
	reg_aux_gpio10_oen		: 1,	// 10
	reg_aux_gpio11_oen		: 1,	// 11
	reg_aux_gpio12_oen		: 1,	// 12
	reg_aux_gpio13_oen		: 1,	// 13
	reg_aux_gpio14_oen		: 1,	// 14
	reg_aux_gpio15_oen		: 1,	// 15
	reg_aux_gpio16_oen		: 1,	// 16
	reg_aux_gpio17_oen		: 1,	// 17
	reg_aux_gpio18_oen		: 1,	// 18
	reg_aux_gpio19_oen		: 1,	// 19
	reg_aux_gpio20_oen		: 1,	// 20
	reg_aux_gpio21_oen		: 1;	// 21
} PAD_ION_15;

/*-----------------------------------------------------------------------------
	0x0050 pad_ion_16
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tu_io_sd00_in_mux_sel	: 8,	//  7: 0
	reg_tu_io_sd01_in_mux_sel	: 8,	// 15: 8
	reg_tu_io_sd02_in_mux_sel	: 8,	// 23:16
	reg_tu_io_sd03_in_mux_sel	: 8;	// 31:24
} PAD_ION_16;

/*-----------------------------------------------------------------------------
	0x0054 pad_ion_17
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_tu_io_sd04_in_mux_sel	: 8,	//  7: 0
	reg_tu_io_sd05_in_mux_sel	: 8,	// 15: 8
	reg_tu_io_sd06_in_mux_sel	: 8,	// 23:16
	reg_tu_io_sd07_out_mux_sel	: 8;	// 31:24
} PAD_ION_17;

typedef struct {
	PAD_ION_00				pad_ion_00;	// 0x0000: ''
	PAD_ION_01				pad_ion_01;	// 0x0004: ''
	PAD_ION_02				pad_ion_02;	// 0x0008: ''
	PAD_ION_03				pad_ion_03;	// 0x000C: ''
	PAD_ION_04				pad_ion_04;	// 0x0010: ''
	PAD_ION_05				pad_ion_05;	// 0x0014: ''
	PAD_ION_06				pad_ion_06;	// 0x0018: ''
	PAD_ION_07				pad_ion_07;	// 0x001C: ''
	PAD_ION_08				pad_ion_08;	// 0x0020: ''
	PAD_ION_09				pad_ion_09;	// 0x0024: ''
	u32					__rsvd__0[2];	// 0x0028 ~ 0x002C
	PAD_ION_10				pad_ion_10;	// 0x0030: ''
	PAD_ION_11				pad_ion_11;	// 0x0034: ''
	u32					__rsvd__1[2];	// 0x0038 ~ 0x003C
	PAD_ION_12				pad_ion_12;	// 0x0040: ''
	PAD_ION_13				pad_ion_13;	// 0x0044: ''
	PAD_ION_14				pad_ion_14;	// 0x0048: ''
	PAD_ION_15				pad_ion_15;	// 0x004C: ''
	PAD_ION_16				pad_ion_16;	// 0x0050: ''
	PAD_ION_17				pad_ion_17;	// 0x0054: ''
} IOMUX_CTRL_REG_T;

#define GET_IOMUX_CTRL_ADDR(member) \
	(IOMUX_CTRL_BASE_ADDRESS + offsetof(IOMUX_CTRL_REG_T, member))

/*
 * SPI_TO_AHB
 */
/*-----------------------------------------------------------------------------
	0x0000 spi_to_ahb_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_cpol_mosi			: 1,	//  0
					: 3,	//  3: 1
	reg_cpha_mosi			: 1,	//  4
					: 3,	//  7: 5
	reg_cpha_miso			: 1,	//  8
					: 3,	// 11: 9
	reg_cpol_miso			: 1,	// 12
					: 3,	// 15:13
	reg_rd_mode			: 1,	// 16
					: 3,	// 19:17
	reg_cs_e_rst_en			: 1;	// 20
} SPI_TO_AHB_0;

/*-----------------------------------------------------------------------------
	0x0004 spi_to_ahb_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_int_en			: 1;	//  0
} SPI_TO_AHB_1;

/*-----------------------------------------------------------------------------
	0x0008 spi_to_ahb_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_int_clr			: 1;	//  0
} SPI_TO_AHB_2;

/*-----------------------------------------------------------------------------
	0x000c spi_to_ahb_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_int				: 1;	//  0
} SPI_TO_AHB_3;

/*-----------------------------------------------------------------------------
	0x0020 spi_to_ahb_8 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_clkx2_en			: 1,	//  0
					: 3,	//  3: 1
	reg_update_phase		: 1,	//  4
	reg_load_phase			: 1,	//  5
					: 2,	//  7: 6
	reg_dummy_size			: 8,	// 15: 8
	reg_rd_cnt			: 8;	// 23:16
} SPI_TO_AHB_8;

/*-----------------------------------------------------------------------------
	0x0024 spi_to_ahb_9 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_rd_mem_wr1_cnt		: 8,	//  7: 0
	reg_ci_rd_mem_wr2_cnt		: 8,	// 15: 8
	reg_ci_rd_mem_wr2_wait		: 8;	// 23:16
} SPI_TO_AHB_9;

/*-----------------------------------------------------------------------------
	0x0028 spi_to_ahb_10 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_rd_mem_rd_dummy		: 8,	//  7: 0
	reg_ci_rd_mem_update_cnt	: 8;	// 15: 8
} SPI_TO_AHB_10;

/*-----------------------------------------------------------------------------
	0x002c spi_to_ahb_11 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_wr_mem_wr1_cnt		: 8,	//  7: 0
	reg_ci_wr_mem_wr2_cnt		: 8,	// 15: 8
	reg_ci_wr_mem_wr2_wait		: 8,	// 23:16
	reg_ci_wr_mem_wr_dummy		: 8;	// 31:24
} SPI_TO_AHB_11;

/*-----------------------------------------------------------------------------
	0x0030 spi_to_ahb_12 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_rd_cam_ctrl_wr1_cnt	: 8,	//  7: 0
	reg_ci_rd_cam_ctrl_wr2_cnt	: 8,	// 15: 8
	reg_ci_rd_cam_ctrl_wr2_wait	: 8;	// 23:16
} SPI_TO_AHB_12;

/*-----------------------------------------------------------------------------
	0x0034 spi_to_ahb_13 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_rd_cam_ctrl_rd_dummy	: 8,	//  7: 0
	reg_ci_rd_cam_ctrl_update_cnt	: 8;	// 15: 8
} SPI_TO_AHB_13;

/*-----------------------------------------------------------------------------
	0x0038 spi_to_ahb_14 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_wr_cam_ctrl_wr1_cnt	: 8,	//  7: 0
	reg_ci_wr_cam_ctrl_wr2_cnt	: 8,	// 15: 8
	reg_ci_wr_cam_ctrl_wr2_wait	: 8,	// 23:16
	reg_ci_wr_cam_ctrl_wr_dummy	: 8;	// 31:24
} SPI_TO_AHB_14;

/*-----------------------------------------------------------------------------
	0x003C spi_to_ahb_16 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_rd16_rd_dummy		: 8,	//  7: 0
	reg_ci_rd16_update_cnt		: 8;	// 15: 8
} SPI_TO_AHB_16;

/*-----------------------------------------------------------------------------
	0x0040 spi_to_ahb_17 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_smc_rd32_rd_dummy		: 8,	//  7: 0
	reg_smc_rd32_update_cnt		: 8;	// 15: 8
} SPI_TO_AHB_17;

/*-----------------------------------------------------------------------------
	0x0044 spi_to_ahb_17_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_ci_rd_cam_ctrl_single_rd_dummy	: 8,	//  7: 0
	reg_ci_rd_cam_ctrl_single_update_cnt	: 8,	// 15: 8
	reg_ci_wr_cam_ctrl_single_wr_dummy	: 8;	// 23:16
} SPI_TO_AHB_17_1;

/*-----------------------------------------------------------------------------
	0x0060 spi_to_ahb_18 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_status_0			: 32;	// 31: 0
} SPI_TO_AHB_18;

/*-----------------------------------------------------------------------------
	0x0064 spi_to_ahb_19 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_status_1			: 32;	// 31: 0
} SPI_TO_AHB_19;

/*-----------------------------------------------------------------------------
	0x0070 spi_to_ahb_20 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_protect_en			: 2;	//  1: 0
} SPI_TO_AHB_20;

/*-----------------------------------------------------------------------------
	0x0074 spi_to_ahb_21 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_range0			: 32;	// 31: 0
} SPI_TO_AHB_21;

/*-----------------------------------------------------------------------------
	0x0078 spi_to_ahb_22 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_range1			: 32;	// 31: 0
} SPI_TO_AHB_22;

/*-----------------------------------------------------------------------------
	0x007C spi_to_ahb_23 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_range2			: 32;	// 31: 0
} SPI_TO_AHB_23;

/*-----------------------------------------------------------------------------
	0x0080 spi_to_ahb_24 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_range3			: 32;	// 31: 0
} SPI_TO_AHB_24;

/*-----------------------------------------------------------------------------
	0x0084 spi_to_ahb_25 ''
------------------------------------------------------------------------------*/
typedef struct {
	u32
	reg_range4			: 32;	// 31: 0
} SPI_TO_AHB_25;

typedef struct {
	SPI_TO_AHB_0				spi_to_ahb_0;	// 0x0000 : ''
	SPI_TO_AHB_1				spi_to_ahb_1;	// 0x0004 : ''
	SPI_TO_AHB_2				spi_to_ahb_2;	// 0x0008 : ''
	SPI_TO_AHB_3				spi_to_ahb_3;	// 0x000c : ''
	u32					__rsvd__0[4];	// 0x0010 ~ 0x001C
	SPI_TO_AHB_8				spi_to_ahb_8;	// 0x0020 : ''
	SPI_TO_AHB_9				spi_to_ahb_9;	// 0x0024 : ''
	SPI_TO_AHB_10				spi_to_ahb_10;	// 0x0028 : ''
	SPI_TO_AHB_11				spi_to_ahb_11;	// 0x002c : ''
	SPI_TO_AHB_12				spi_to_ahb_12;	// 0x0030 : ''
	SPI_TO_AHB_13				spi_to_ahb_13;	// 0x0034 : ''
	SPI_TO_AHB_14				spi_to_ahb_14;	// 0x0038 : ''
	SPI_TO_AHB_16				spi_to_ahb_16;	// 0x003c : ''
	SPI_TO_AHB_17				spi_to_ahb_17;	// 0x0040 : ''
	SPI_TO_AHB_17_1				spi_to_ahb_17_1;// 0x0044 : ''
	u32					__rsvd__1[6];	// 0x0048 ~ 0x005C
	SPI_TO_AHB_18				spi_to_ahb_18;	// 0x0060 : ''
	SPI_TO_AHB_19				spi_to_ahb_19;	// 0x0064 : ''
	u32					__rsvd__2[2];	// 0x0068 ~ 0x006C
	SPI_TO_AHB_20				spi_to_ahb_20;	// 0x0070 : ''
	SPI_TO_AHB_21				spi_to_ahb_21;	// 0x0074 : ''
	SPI_TO_AHB_22				spi_to_ahb_22;	// 0x0078 : ''
	SPI_TO_AHB_23				spi_to_ahb_23;	// 0x007C : ''
	SPI_TO_AHB_24				spi_to_ahb_24;	// 0x0080 : ''
	SPI_TO_AHB_25				spi_to_ahb_25;	// 0x0084 : ''
} SPI_TO_AHB_REG_T;

#define GET_AHB_ADDR(member) \
	(SPI_TO_AHB_BASE_ADDRESS + offsetof(SPI_TO_AHB_REG_T, member))

#endif	/* _ION_REG_DB_H_ */
