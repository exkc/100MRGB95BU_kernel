/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/*!
 * @file    jdec_reg.h
 * @brief   Header including definition.
 * @version V1.0
 * @date    15.SEP 2014
 * @author  hm.choi (hyomin.choi@lge.com)
 */

#ifndef LGJPEG_REG_H
#define LGJPEG_REG_H

#ifdef __cplusplus
extern "C" {

#endif /*                                                                      \
        */
enum {
	Intr_dec_done0 = 0x01 << 0, // 0x0001
	Intr_dec_done1 = 0x01 << 1, // 0x0002
	Intr_dec_done2 = 0x01 << 2, // 0x0004
	Intr_dec_done3 = 0x01 << 3, // 0x0008
	Intr_pic_done = 0x01 << 4, // 0x0010
	Intr_buffer_empty = 0x01 << 5, // 0x0020
	Intr_stream_err = 0x01 << 6, // 0x0040
	Intr_rmif_ready = 0x01 << 7, // 0x0080
	Intr_wmif_ready = 0x01 << 8, // 0x0100
	Intr_pic_done_err = 0x01 << 9, // 0x0200
	Intr_start_err = 0x01 << 10, // 0x0400
};
typedef struct {
	UINT32 intr_dec_done0 : 1, //     0
			intr_dec_done1 : 1, //     1
			intr_dec_done2 : 1, //     2
			intr_dec_done3 : 1, //     3
			intr_pic_done : 1, //     4
			intr_buffer_empty : 1, //     5
			intr_stream_err : 1, //     6
			intr_rmif_ready : 1, //     7
			intr_wmif_ready : 1, //     8
			intr_pic_done_err : 1, //     9
			intr_start_err : 1, //     10
			intr_time_out : 1, //     11
			intr_dc_error : 1; //     12
} INTERRRUPT;
typedef struct {
	UINT32 reg_dec_start : 1, //     0
			reg_dec_mode : 1, //     1
			reg_recon_ptr_ctrl_mode : 1, //     2
			____reserved01 : 1, //     3
			reg_recon_ptr_interval : 2, //     4: 5
			____reserved02 : 6, //     6:11
			reg_dpb_num_m1 : 2, //     12:13
			____reserved03 : 2, //     14:15
			reg_dec_line_num_div8 : 13, //     16:28
			reg_swreset : 1, //     29
			reg_swreset_ack_rmif : 1, //     30
			reg_swreset_ack_wmif : 1; //     31
} DEC_CTRL;
typedef struct {
	UINT32 cpb_base; // 31: 0
} CPB_BASE;
typedef struct {
	UINT32 cpb_end; // 31: 0
} CPB_END;
typedef struct {
	UINT32 reg_rmif_unit : 4, //     0:3
			reg_rmif_endian : 2; //     4:5
} RMIF_CTRL;
typedef struct {
	UINT32 reg_comp12_interleaving : 1, //     0
			____reserved01 : 3, //     1:3
			reg_wmif_endian : 2, //     4:5
			____reserved02 : 2, //     6:7
			rem_memchk : 1, //     8
			____reserved03 : 3, //     9:11
			rem_bvalid_chk : 1, //     12
			____reserved04 : 3, //     13:15
			reg_dpb0_clear : 1, //     16
			____reserved05 : 3, //     17:19
			reg_dpb1_clear : 1, //     20
			____reserved06 : 3, //     21:23
			reg_dpb2_clear : 1, //     24
			____reserved07 : 3, //     25:27
			reg_dpb3_clear : 1; //     28
} WMIF_CTRL;
typedef struct {
	UINT32 reg_pic_width : 16, //     0:15
			reg_pic_height : 16; //     16:31
} PICTURE_SIZE;
typedef struct {
	UINT32 reg_file_format : 3; //  [ 2: 0] //  0:YUV444, 1:YUV422, 2:YUV224,
			//  3:YUV420, 4:YUV400
	UINT32 reserved0 : 1; //  [3]
	UINT32 reg_auto_stride_en : 1; //  [4]
	// UINT32  reg_mcu_size_comp0      : 4;  //  [ 3: 0] //  0:8x8, 1:8x16,
	// 2:8x32, 3:16x8, 4:16x16, 5:16x32, 6:32x8, 7:32x16, 8:32x32, 9-15:N/A UINT32
	// reg_mcu_size_comp1      : 4;  //  [ 7: 4] //  0:8x8, 1:8x16, 2:8x32,
	// 3:16x8, 4:16x16, 5:16x32, 6:32x8, 7:32x16, 8:32x32, 9-15:N/A UINT32
	// reg_mcu_size_comp2      : 4;  //  [11: 8] //  0:8x8, 1:8x16, 2:8x32,
	// 3:16x8, 4:16x16, 5:16x32, 6:32x8, 7:32x16, 8:32x32, 9-15:N/A UINT32
	// reg_component_num       : 2;  //  [13:12] //  0x3   0/4: N/A
	UINT32 reserved1 : 11; //  [15:5]
	// UINT32  reserved0               : 2;  //  [15:14]
	UINT32 reg_htable_sel_comp0dc : 1; //  [16:16] //  huffman table selection for
			//  component 0 DC
	UINT32 reg_htable_sel_comp0ac : 1; //  [17:17] //  huffman table selection for
			//  component 0 AC
	UINT32 reg_htable_sel_comp1dc : 1; //  [18:18] //  huffman table selection for
			//  component 1 DC
	UINT32 reg_htable_sel_comp1ac : 1; //  [19:19] //  huffman table selection for
			//  component 1 AC
	UINT32 reg_htable_sel_comp2dc : 1; //  [20:20] //  huffman table selection for
			//  component 2 DC
	UINT32 reg_htable_sel_comp2ac : 1; //  [21:21] //  huffman table selection for
			//  component 2 AC
	UINT32 reserved2 : 2; //  [23:22]
	UINT32 reg_qtable_sel_comp0 : 2; //  [25:24] //  quantization table selection
			//  for component 0
	UINT32 reg_qtable_sel_comp1 : 2; //  [27:26] //  quantization table selection
			//  for component 1
	UINT32 reg_qtable_sel_comp2 : 2; //  [29:28] //  quantization table selection
			//  for component 2
} INPUT_FORMAT;
typedef struct {
	UINT32 reg_reset_pre_interval : 16; //[15: 0]
	UINT32 reg_reset_pred_en : 1; //[16:16]
	UINT32 reserved0 : 13; //[17:29]
	UINT32 stream_left_err_en : 1; //[30:30]
	UINT32 clipping_en : 1; //[31:31]
} RESET_PRED;
typedef struct {
	UINT32 reg_v_scale_f : 2; //  [ 1: 0] //  0:bypass, 1:1/2, 2:1/4, 3:1/8
	UINT32 reserved0 : 2; //  [ 3: 2]
	UINT32 reg_h_scale_f : 2; //  [ 5: 4] //  0:bypass, 1:1/2, 2:1/4, 3:1/8
	UINT32 reserved1 : 10; //  [15: 6]
	UINT32 reg_flip_dir : 2; //  [17:16] //  0: bypass, 1:Horizontal Flip,
			//  2:Vertical Flip, 3:N/A
	UINT32 reserved2 : 2; //  [19:18]
	UINT32 reg_rot_angle : 2; //  [21:20] //  0:bypass, 1:Right 90, 2:Right 180,
			//  3:Right 270
} PP_CTRL;
typedef struct {
	UINT32 reg_qtable_idx : 4; //  [ 3: 0] //  quantization table0 index for
			//  component 0
	UINT32 reserved0 : 4; //  [ 7: 4]
	UINT32 reg_qtable_idx_auto : 1; //  [ 8: 8] //  quantization table0 index auto
			//  increment
	UINT32 reserved1 : 7; //  [15: 9]
	UINT32 reg_qtable_sel : 2; //  [17:16] //  0: component0 qtable, 1: component1
			//  qtable, 2: component2 qtable
} QTABLE_IDX;
typedef struct {
	UINT32 reg_htable_idx : 6; //  [ 5: 0] //  huffman table0dc index
	UINT32 reserved0 : 2; //  [ 7: 6]
	UINT32 reg_htable_idx_auto : 1; //  [ 8: 8] //  huffman table0dc index auto
			//  increment
	UINT32 reserved1 : 7; //  [15: 9]
	UINT32 reg_htable_sel : 2; //  [17:16] //  0:dc0 table, 1:dc1 table, 2:ac0
			//  table, 3:ac1 table
	UINT32 reserved2 : 2; //  [19:18]
	UINT32 reg_htable_endian : 1; //  [20:20]
} HTABLE_IDX;
typedef struct {
	UINT32 reg_gmau0_cmd_pri2 : 2; // [ 1: 0]  //  command priority (2nd)
	UINT32 reg_gmau0_cmd_pri1 : 2; // [ 3: 2]  //  command priority (1st)
	UINT32 reg_gmau0_cmd_txid : 2; // [ 5: 4]  //  service ID
	UINT32 reserved : 10; // [15: 6]
	UINT32
	reg_gmau0_cmd_dly_cnt : 16; // [31:16] command interval for delay contrl
} GMAU_CONFIG;
typedef struct {
	UINT32 ro_mcu_y : 16; // [ 15: 0]  //
	UINT32 ro_mcu_x : 16; // [ 31: 16]  //
} MON_WMIF2;
typedef struct LGJDEC_HAL {
	INTERRRUPT intr_en; //<<  0x000
	INTERRRUPT intr_st; //<<  0x004
	INTERRRUPT intr_cl; //<<  0x008
	DEC_CTRL dec_ctrl; //<<  0x00C
	CPB_BASE cpb_base; //<<  0x010
	CPB_END cpb_end; //<<  0x014
	RMIF_CTRL rmif_ctrl; //<<  0x018
	WMIF_CTRL wmif_ctrl; //<<  0x01C
	PICTURE_SIZE picture_size; //<<  0x020
	UINT32 stride_comp0; //<<  0x024
	UINT32 stride_comp1; //<<  0x028
	UINT32 stride_comp2; //<<  0x02C
	INPUT_FORMAT input_format; //<<  0x030
	RESET_PRED reset_pred; //<<  0x0034
	UINT32 __rsvd_00[1]; //<<  0x0038
	UINT32 dec_time; //<<  0x003C
	UINT32 dpb0_base_comp0; //<<  0x0040
	UINT32 dpb0_base_comp1; //<<  0x0044
	UINT32 dpb0_base_comp2; //<<  0x0048
	UINT32 __rsvd_01[1]; //<<  0x004C
	UINT32 dpb1_base_comp0; //<<  0x0050
	UINT32 dpb1_base_comp1; //<<  0x0054
	UINT32 dpb1_base_comp2; //<<  0x0058
	UINT32 __rsvd_02[1]; //<<  0x005C
	UINT32 dpb2_base_comp0; //<<  0x0060
	UINT32 dpb2_base_comp1; //<<  0x0064
	UINT32 dpb2_base_comp2; //<<  0x0068
	UINT32 __rsvd_03[1]; //<<  0x006C
	UINT32 dpb3_base_comp0; //<<  0x0070
	UINT32 dpb3_base_comp1; //<<  0x0074
	UINT32 dpb3_base_comp2; //<<  0x0078
	UINT32 __rsvd_04[1]; //<<  0x007C
	PP_CTRL pp_ctrl; //<<  0x0080
	UINT32 __rsvd_05[3]; //<<  0x0084 ~ 0x008C
	QTABLE_IDX qtable_idx; //<<  0x0090
	UINT32 qtable_data; //<<  0x0094
	HTABLE_IDX htable_idx; //<<  0x0098
	UINT32 htable_data; //<<  0x009C
	GMAU_CONFIG gmau0_config; //<<  0x00A0
	GMAU_CONFIG gmau1_config; //<<  0x00A4
	GMAU_CONFIG gmau2_config; //<<  0x00A8
	GMAU_CONFIG gmau3_config; //<<  0x00AC
	UINT32 __rsvd_06[19]; //<<  0x00B0 ~ 0x00F8
	UINT32 mon_iqit4; //<<  0x00FC
	UINT32 mon_rmif0; //<<  0x0100
	UINT32 mon_rmif1; //<<  0x0104
	UINT32 mon_wmif0; //<<  0x0108
	UINT32 mon_wmif1; //<<  0x010c
	MON_WMIF2 mon_wmif2; //<<  0X0110
	UINT32 mon_iqit; //<<  0x0114
	UINT32 mon_iqit_mcu_cnt; //<<  0x0118
	UINT32 mon_iqit_du_tot_cnt; //<<  0x011C
} JDEC_REG;

// powerory for test
// JPEG HIF ADDRESS
#define AD_INTR_EN 0x000
#define AD_INTR_ST 0x004
#define AD_INTR_CL 0x008
#define AD_DEC_CTRL 0x00C
#define AD_CPB_BASE 0x010
#define AD_CPB_END 0x014
#define AD_RMIF_CTRL 0x018
#define AD_WMIF_CTRL 0x01C
#define AD_PICTURE_SIZE 0x020
#define AD_STRIDE_COMP0 0x024
#define AD_STRIDE_COMP1 0x028
#define AD_STRIDE_COMP2 0x02C
#define AD_INPUT_FORMAT 0x030
#define AD_RESET_PRED 0x034
#define AD_DEC_TIME 0x03C
#define AD_DPB0_BASE_COMP0 0x040
#define AD_DPB0_BASE_COMP1 0x044
#define AD_DPB0_BASE_COMP2 0x048
#define AD_DPB1_BASE_COMP0 0x050
#define AD_DPB1_BASE_COMP1 0x054
#define AD_DPB1_BASE_COMP2 0x058
#define AD_DPB2_BASE_COMP0 0x060
#define AD_DPB2_BASE_COMP1 0x064
#define AD_DPB2_BASE_COMP2 0x068
#define AD_DPB3_BASE_COMP0 0x070
#define AD_DPB3_BASE_COMP1 0x074
#define AD_DPB3_BASE_COMP2 0x078
#define AD_PP_CTRL 0x080
#define AD_QTABLE_IDX 0x090
#define AD_QTABLE_DATA 0x094
#define AD_HTABLE_IDX 0x098
#define AD_HTABLE_DATA 0x09C
#define AD_GMAU0_CONFIG 0x0A0
#define AD_GMAU1_CONFIG 0x0A4
#define AD_GMAU2_CONFIG 0x0A8
#define AD_GMAU3_CONFIG 0x0AC
#define AD_MON_IQIT4 0x0FC
#define AD_MON_RMIF0 0x100
#define AD_MON_RMIF1 0x104
#define AD_MON_WMIF0 0x108
#define AD_MON_WMIF1 0x10C
#define AD_MON_WMIF2 0x110
#define AD_MON_IQIT 0x114
//~powerory

/*
 * @{
 * Naming for register pointer.
 * gpRealRegLGJPEG : real register of mjpeg.
 * gpRegLGJPEG      : shadow register.
 *
 * @def LGJPEG_RdFL: Read  FLushing : Shadow <- Real.
 * @def LGJPEG_WrFL: Write FLushing : Shadow -> Real.
 * @def LGJPEG_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def LGJPEG_Wr  : Write whole register(UINT32) from Shadow register.
 * @def LGJPEG_Rd01 ~ LGJPEG_Rdnn: Read  given '01~nn' fields from Shadow
 * register.
 * @def LGJPEG_Wr01 ~ LGJPEG_Wrnn: Write given '01~nn' fields to     Shadow
 * register.
 * */

#define LGJPEG_RdFL(_r) ((gpRegLGJPEG->_r) = (gpRealRegLGJPEG->_r))
#define LGJPEG_WrFL(_r) ((gpRealRegLGJPEG->_r) = (gpRegLGJPEG->_r))

#define LGJPEG_LOG_TRACE()
#define LGJPEG_REG_LOG(_r)

#define LGJPEG_Rd(_r) *((UINT32 *)(&(gpRegLGJPEG->_r)))
#define LGJPEG_Wr(_r, _v) ((LGJPEG_Rd(_r)) = ((UINT32)(_v)))

#define LGJPEG_Rd01(_r, _f01, _v01) (_v01) = (gpRegLGJPEG->_r._f01)

#define LGJPEG_Rd02(_r, _f01, _v01, _f02, _v02)                                \
	do {                                                                       \
		(_v01) = (gpRegLGJPEG->_r._f01);                                       \
		(_v02) = (gpRegLGJPEG->_r._f02);                                       \
	} while (0)

#define LGJPEG_Rd03(_r, _f01, _v01, _f02, _v02, _f03, _v03)                    \
	do {                                                                       \
		(_v01) = (gpRegLGJPEG->_r._f01);                                       \
		(_v02) = (gpRegLGJPEG->_r._f02);                                       \
		(_v03) = (gpRegLGJPEG->_r._f03);                                       \
	} while (0)

#define LGJPEG_Rd04(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)        \
	do {                                                                       \
		(_v01) = (gpRegLGJPEG->_r._f01);                                       \
		(_v02) = (gpRegLGJPEG->_r._f02);                                       \
		(_v03) = (gpRegLGJPEG->_r._f03);                                       \
		(_v04) = (gpRegLGJPEG->_r._f04);                                       \
	} while (0)

#define LGJPEG_Wr01(_r, _f01, _v01) (gpRegLGJPEG->_r._f01) = (_v01)

#define LGJPEG_Wr02(_r, _f01, _v01, _f02, _v02)                                \
	do {                                                                       \
		(gpRegLGJPEG->_r._f01) = (_v01);                                       \
		(gpRegLGJPEG->_r._f02) = (_v02);                                       \
	} while (0)

#define LGJPEG_Wr03(_r, _f01, _v01, _f02, _v02, _f03, _v03)                    \
	do {                                                                       \
		(gpRegLGJPEG->_r._f01) = (_v01);                                       \
		(gpRegLGJPEG->_r._f02) = (_v02);                                       \
		(gpRegLGJPEG->_r._f03) = (_v03);                                       \
	} while (0)

#define LGJPEG_Wr04(_r, _f01, _v01, _f02, _v02, _f03, _v03, _f04, _v04)        \
	do {                                                                       \
		(gpRegLGJPEG->_r._f01) = (_v01);                                       \
		(gpRegLGJPEG->_r._f02) = (_v02);                                       \
		(gpRegLGJPEG->_r._f03) = (_v03);                                       \
		(gpRegLGJPEG->_r._f04) = (_v04);                                       \
	} while (0)

/* Indexed Register Access.
 *
 * There is in-direct field specified by 'index' field within a register.
 * Normally a register has only one meaning for a 'field_name', but indexed
 * register can hold several data for a 'field_name' specifed by 'index' field
 * of indexed register. When writing an 3rd data for given 'field_name'
 * register, you need to set 'rw' = 0, 'index' = 2, and 'load' = 0.
 *
 * ASSUMPTION
 * For Writing indexed register load bit
 *
 * parameter list
 * _r      : name of register
 * _lname : name of load  bit field : shall be 0 after macro executed.
 * _rwname: name of rw      bit field : shall be 0 after LGJPEG_Wind(), 1 for
 * LGJPEG_Rind() _iname : name of index bit field _ival  : index value _fname :
 * field name _fval  : field variable that field value shall be stored.
 *
 * LGJPEG_Rind : General indexed register Read.(
 * LGJPEG_Wind : General indexed register Read.
 *
 * LGJPEG_Ridx : For 'index', 'rw', 'load' field name
 * LGJPEG_Widx : For 'index', 'rw', 'load' field name and NO_LOAD.
 */
#define LGJPEG_Rind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)         \
	do {                                                                       \
		LGJPEG_Wr03(_r, _lname, 0, _rwname, 1, _iname, _ival);                 \
		LGJPEG_WrFL(_r);                                                       \
		LGJPEG_RdFL(_r);                                                       \
		LGJPEG_Rd01(_r, _fname, _fval);                                        \
	} while (0)

#define LGJPEG_Wind(_r, _lname, _rwname, _iname, _ival, _fname, _fval)         \
	LGJPEG_Wr04(_r, _lname, 0, _rwname, 0, _iname, _ival, _fname, _fval)

#define LGJPEG_Ridx(_r, _ival, _fname, _fval)                                  \
	LGJPEG_Rind(_r, load, rw, index, _ival, _fname, _fval)

#define LGJPEG_Widx(_r, _ival, _fname, _fval)                                  \
	LGJPEG_Wind(_r, load, rw, index, _ival, _fname, _fval)
#ifdef __cplusplus
}
#endif /*                                                                      \
        */

#endif /*                                                                      \
        */
