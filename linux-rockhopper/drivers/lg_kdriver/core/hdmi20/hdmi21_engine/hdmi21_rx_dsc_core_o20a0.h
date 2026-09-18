/* SIC I2C Reg CSV File to Header File transfer scripte by won.hur(won.hur@lge.com) */ 
/* Version = 0.70 */ 
/* File Build Date : Thu, 27 Jun 2019 05:32:53 +0000  */

/* dsc_core_reg_0000_O20A0 */
#define	dsc_core_reg_0000_O20A0_REG_ADDR	0x0000

/* dsc_core_reg_0010_O20A0 */
#define	dsc_core_reg_0010_O20A0_REG_ADDR	0x0010

/* dsc_core_reg_0014_O20A0 */
#define	dsc_core_reg_0014_O20A0_REG_ADDR	0x0014

/* dsc_core_reg_0030_O20A0 */
#define	dsc_core_reg_0030_O20A0_REG_ADDR	0x0030

/* dsc_core_reg_0034_O20A0 */
#define	dsc_core_reg_0034_O20A0_REG_ADDR	0x0034

/* dsc_core_reg_0038_O20A0 */
#define	dsc_core_reg_0038_O20A0_REG_ADDR	0x0038

/* dsc_core_reg_003c_O20A0 */
#define	dsc_core_reg_003c_O20A0_REG_ADDR	0x003c

/* dsc_core_reg_0040_O20A0 */
#define	dsc_core_reg_0040_O20A0_REG_ADDR	0x0040

/* dsc_core_reg_0044_O20A0 */
#define	dsc_core_reg_0044_O20A0_REG_ADDR	0x0044

/* dsc_core_reg_0048_O20A0 */
#define	dsc_core_reg_0048_O20A0_REG_ADDR	0x0048

/* dsc_core_reg_004c_O20A0 */
#define	dsc_core_reg_004c_O20A0_REG_ADDR	0x004c

/* dsc_core_reg_0050_O20A0 */
#define	dsc_core_reg_0050_O20A0_REG_ADDR	0x0050

/* dsc_core_reg_0054_O20A0 */
#define	dsc_core_reg_0054_O20A0_REG_ADDR	0x0054

/* dsc_core_reg_0058_O20A0 */
#define	dsc_core_reg_0058_O20A0_REG_ADDR	0x0058

/* dsc_core_reg_005c_O20A0 */
#define	dsc_core_reg_005c_O20A0_REG_ADDR	0x005c

/* dsc_core_reg_0060_O20A0 */
#define	dsc_core_reg_0060_O20A0_REG_ADDR	0x0060

/* dsc_core_reg_0064_O20A0 */
#define	dsc_core_reg_0064_O20A0_REG_ADDR	0x0064

/* dsc_core_reg_0068_O20A0 */
#define	dsc_core_reg_0068_O20A0_REG_ADDR	0x0068

/* dsc_core_reg_006c_O20A0 */
#define	dsc_core_reg_006c_O20A0_REG_ADDR	0x006c

/* dsc_core_reg_0070_O20A0 */
#define	dsc_core_reg_0070_O20A0_REG_ADDR	0x0070

/* dsc_core_reg_0074_O20A0 */
#define	dsc_core_reg_0074_O20A0_REG_ADDR	0x0074

/* dsc_core_reg_0078_O20A0 */
#define	dsc_core_reg_0078_O20A0_REG_ADDR	0x0078

/* dsc_core_reg_007c_O20A0 */
#define	dsc_core_reg_007c_O20A0_REG_ADDR	0x007c

/* dsc_core_reg_0080_O20A0 */
#define	dsc_core_reg_0080_O20A0_REG_ADDR	0x0080

/* dsc_core_reg_0084_O20A0 */
#define	dsc_core_reg_0084_O20A0_REG_ADDR	0x0084

/* dsc_core_reg_0088_O20A0 */
#define	dsc_core_reg_0088_O20A0_REG_ADDR	0x0088

/* dsc_core_reg_008c_O20A0 */
#define	dsc_core_reg_008c_O20A0_REG_ADDR	0x008c

/* dsc_core_reg_0090_O20A0 */
#define	dsc_core_reg_0090_O20A0_REG_ADDR	0x0090

/* dsc_core_reg_0094_O20A0 */
#define	dsc_core_reg_0094_O20A0_REG_ADDR	0x0094

/* dsc_core_reg_0098_O20A0 */
#define	dsc_core_reg_0098_O20A0_REG_ADDR	0x0098

/* END OF ADDR DEFINITION */


typedef struct
{
	UINT32
		b_rsvd1:7,		// 6:0
		num_of_ss:3,		// 9:7
		b_rsvd2:8,		// 17:10
		rb_max_addr:14;		// 31:18
} dsc_core_reg_0000_O20A0_T;



typedef struct
{
	UINT32
		initial_tc:4,		// 3:0
		hsync_delay:14,		// 17:4
		ib_max_addr:14;		// 31:18
} dsc_core_reg_0010_O20A0_T;



typedef struct
{
	UINT32
		initial_tc:4,		// 3:0
		hsync_delay:14,		// 17:4
		ib_max_addr:14;		// 31:18
} dsc_core_reg_0014_O20A0_T;



typedef struct
{
	UINT32
		bits_per_component:4,		// 3:0
		convert_rgb:1,		// 4:4
		simple_422:1,		// 5:5
		linebuf_depth:4,		// 9:6
		bits_per_pixel:10,		// 19:10
		_block_pred_enable:1,		// 20:20
		native_420:1,		// 21:21
		native_422:1,		// 22:22
		b_rsvd1:5,		// 27:23
		dsc_version_minor:4;	// 31:28
} dsc_core_reg_0030_O20A0_T;



typedef struct
{
	UINT32
		pic_width:16,		// 15:0
		pic_height:16;		// 31:16
} dsc_core_reg_0034_O20A0_T;



typedef struct
{
	UINT32
		slice_width:16,		// 15:0
		slice_height:16;		// 31:16
} dsc_core_reg_0038_O20A0_T;



typedef struct
{
	UINT32
		chunk_size:16,		// 15:0
		padd_rsvd:16;		// 31:16
} dsc_core_reg_003c_O20A0_T;



typedef struct
{
	UINT32
		initial_xmit_delay:10,		// 9:0
		b_rsvd1:6,		// 15:10
		initial_dec_delay:16;		// 31:16
} dsc_core_reg_0040_O20A0_T;



typedef struct
{
	UINT32
		initial_scale_value:6,		// 5:0
		padd_rsvd:26;		// 31:6
} dsc_core_reg_0044_O20A0_T;



typedef struct
{
	UINT32
		scale_increment_interval:16,		// 15:0
		scale_decrement_interval:12,		// 27:16
		padd_rsvd:4;		// 31:28
} dsc_core_reg_0048_O20A0_T;



typedef struct
{
	UINT32
		first_line_bpg_offset:5,		// 4:0
		second_line_bpg_offset:5,		// 9:5
		padd_rsvd:22;		// 31:10
} dsc_core_reg_004c_O20A0_T;



typedef struct
{
	UINT32
		nfl_bpg_offset:16,		// 15:0
		slice_bpg_offset:16;		// 31:16
} dsc_core_reg_0050_O20A0_T;



typedef struct
{
	UINT32
		initial_offset:16,		// 15:0
		final_offset:16;		// 31:16
} dsc_core_reg_0054_O20A0_T;



typedef struct
{
	UINT32
		nsl_bpg_offset:16,		// 15:0
		second_line_offset_adj:16;		// 31:16
} dsc_core_reg_0058_O20A0_T;



typedef struct
{
	UINT32
		flatness_min_qp:5,		// 4:0
		flatness_max_qp:5,		// 9:5
		flatness_det_thresh:8,		// 17:10
		padd_rsvd:14;		// 31:18
} dsc_core_reg_005c_O20A0_T;



typedef struct
{
	UINT32
		rc_model_size:16,		// 15:0
		padd_rsvd:16;		// 31:16
} dsc_core_reg_0060_O20A0_T;



typedef struct
{
	UINT32
		rc_edge_factor:4,		// 3:0
		b_rsvd1:4,		// 7:4
		rc_quant_incr_limit0:5,		// 12:8
		rc_quant_incr_limit1:5,		// 17:13
		b_rsvd2:2,		// 19:18
		rc_tgt_offset_hi:4,		// 23:20
		rc_tgt_offset_lo:4,		// 27:24
		padd_rsvd:4;		// 31:28
} dsc_core_reg_0064_O20A0_T;



typedef struct
{
	UINT32
		rc_buf_thresh_0:8,		// 7:0
		rc_buf_thresh_1:8,		// 15:8
		rc_buf_thresh_2:8,		// 23:16
		rc_buf_thresh_3:8;		// 31:24
} dsc_core_reg_0068_O20A0_T;



typedef struct
{
	UINT32
		rc_buf_thresh_4:8,		// 7:0
		rc_buf_thresh_5:8,		// 15:8
		rc_buf_thresh_6:8,		// 23:16
		rc_buf_thresh_7:8;		// 31:24
} dsc_core_reg_006c_O20A0_T;



typedef struct
{
	UINT32
		rc_buf_thresh_8:8,		// 7:0
		rc_buf_thresh_9:8,		// 15:8
		rc_buf_thresh_10:8,		// 23:16
		rc_buf_thresh_11:8;		// 31:24
} dsc_core_reg_0070_O20A0_T;



typedef struct
{
	UINT32
		rc_buf_thresh_12:8,		// 7:0
		rc_buf_thresh_13:8,		// 15:8
		padd_rsvd:16;		// 31:16
} dsc_core_reg_0074_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_0_range_min_qp:5,		// 4:0
		rc_range_parameters_1_range_min_qp:5,		// 9:5
		rc_range_parameters_2_range_min_qp:5,		// 14:10
		rc_range_parameters_3_range_min_qp:5,		// 19:15
		rc_range_parameters_4_range_min_qp:5,		// 24:20
		padd_rsvd:7;		// 31:25
} dsc_core_reg_0078_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_5_range_min_qp:5,		// 4:0
		rc_range_parameters_6_range_min_qp:5,		// 9:5
		rc_range_parameters_7_range_min_qp:5,		// 14:10
		rc_range_parameters_8_range_min_qp:5,		// 19:15
		rc_range_parameters_9_range_min_qp:5,		// 24:20
		padd_rsvd:7;		// 31:25
} dsc_core_reg_007c_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_10_range_min_qp:5,		// 4:0
		rc_range_parameters_11_range_min_qp:5,		// 9:5
		rc_range_parameters_12_range_min_qp:5,		// 14:10
		rc_range_parameters_13_range_min_qp:5,		// 19:15
		rc_range_parameters_14_range_min_qp:5,		// 24:20
		padd_rsvd:7;		// 31:25
} dsc_core_reg_0080_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_0_range_max_qp:5,		// 4:0
		rc_range_parameters_1_range_max_qp:5,		// 9:5
		rc_range_parameters_2_range_max_qp:5,		// 14:10
		rc_range_parameters_3_range_max_qp:5,		// 19:15
		rc_range_parameters_4_range_max_qp:5,		// 24:20
		padd_rsvd:7;		// 31:25
} dsc_core_reg_0084_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_5_range_max_qp:5,		// 4:0
		rc_range_parameters_6_range_max_qp:5,		// 9:5
		rc_range_parameters_7_range_max_qp:5,		// 14:10
		rc_range_parameters_8_range_max_qp:5,		// 19:15
		rc_range_parameters_9_range_max_qp:5,		// 24:20
		padd_rsvd:7;		// 31:25
} dsc_core_reg_0088_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_10_range_max_qp:5,		// 4:0
		rc_range_parameters_11_range_max_qp:5,		// 9:5
		rc_range_parameters_12_range_max_qp:5,		// 14:10
		rc_range_parameters_13_range_max_qp:5,		// 19:15
		rc_range_parameters_14_range_max_qp:5,		// 24:20
		padd_rsvd:7;		// 31:25
} dsc_core_reg_008c_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_0_range_bpg_offset:6,		// 5:0
		rc_range_parameters_1_range_bpg_offset:6,		// 11:6
		rc_range_parameters_2_range_bpg_offset:6,		// 17:12
		rc_range_parameters_3_range_bpg_offset:6,		// 23:18
		rc_range_parameters_4_range_bpg_offset:6,		// 29:24
		padd_rsvd:2;		// 31:30
} dsc_core_reg_0090_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_5_range_bpg_offset:6,		// 5:0
		rc_range_parameters_6_range_bpg_offset:6,		// 11:6
		rc_range_parameters_7_range_bpg_offset:6,		// 17:12
		rc_range_parameters_8_range_bpg_offset:6,		// 23:18
		rc_range_parameters_9_range_bpg_offset:6,		// 29:24
		padd_rsvd:2;		// 31:30
} dsc_core_reg_0094_O20A0_T;



typedef struct
{
	UINT32
		rc_range_parameters_10_range_bpg_offset:6,		// 5:0
		rc_range_parameters_11_range_bpg_offset:6,		// 11:6
		rc_range_parameters_12_range_bpg_offset:6,		// 17:12
		rc_range_parameters_13_range_bpg_offset:6,		// 23:18
		rc_range_parameters_14_range_bpg_offset:6,		// 29:24
		padd_rsvd:2;		// 31:30
} dsc_core_reg_0098_O20A0_T;


typedef struct {
	dsc_core_reg_0000_O20A0_T		dsc_core_reg_0000;
	dsc_core_reg_0010_O20A0_T		dsc_core_reg_0010;
	dsc_core_reg_0014_O20A0_T		dsc_core_reg_0014;
	dsc_core_reg_0030_O20A0_T		dsc_core_reg_0030;
	dsc_core_reg_0034_O20A0_T		dsc_core_reg_0034;
	dsc_core_reg_0038_O20A0_T		dsc_core_reg_0038;
	dsc_core_reg_003c_O20A0_T		dsc_core_reg_003c;
	dsc_core_reg_0040_O20A0_T		dsc_core_reg_0040;
	dsc_core_reg_0044_O20A0_T		dsc_core_reg_0044;
	dsc_core_reg_0048_O20A0_T		dsc_core_reg_0048;
	dsc_core_reg_004c_O20A0_T		dsc_core_reg_004c;
	dsc_core_reg_0050_O20A0_T		dsc_core_reg_0050;
	dsc_core_reg_0054_O20A0_T		dsc_core_reg_0054;
	dsc_core_reg_0058_O20A0_T		dsc_core_reg_0058;
	dsc_core_reg_005c_O20A0_T		dsc_core_reg_005c;
	dsc_core_reg_0060_O20A0_T		dsc_core_reg_0060;
	dsc_core_reg_0064_O20A0_T		dsc_core_reg_0064;
	dsc_core_reg_0068_O20A0_T		dsc_core_reg_0068;
	dsc_core_reg_006c_O20A0_T		dsc_core_reg_006c;
	dsc_core_reg_0070_O20A0_T		dsc_core_reg_0070;
	dsc_core_reg_0074_O20A0_T		dsc_core_reg_0074;
	dsc_core_reg_0078_O20A0_T		dsc_core_reg_0078;
	dsc_core_reg_007c_O20A0_T		dsc_core_reg_007c;
	dsc_core_reg_0080_O20A0_T		dsc_core_reg_0080;
	dsc_core_reg_0084_O20A0_T		dsc_core_reg_0084;
	dsc_core_reg_0088_O20A0_T		dsc_core_reg_0088;
	dsc_core_reg_008c_O20A0_T		dsc_core_reg_008c;
	dsc_core_reg_0090_O20A0_T		dsc_core_reg_0090;
	dsc_core_reg_0094_O20A0_T		dsc_core_reg_0094;
	dsc_core_reg_0098_O20A0_T		dsc_core_reg_0098;
} HDMI21_DSC_CORE_REG_O20A0_T;




