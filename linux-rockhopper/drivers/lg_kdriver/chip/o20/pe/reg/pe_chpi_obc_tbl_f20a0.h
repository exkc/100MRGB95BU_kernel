#ifndef _PE_CHPI_OBC_TBL_F20A0_H_
#define _PE_CHPI_OBC_TBL_F20A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175300 RW
	UINT32 reg_img_wid                      :12;	//11:0	//horizontal resolution
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//27:16	//vertical resolution
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_VSD_OBC_OBJT_PSP_CTRL00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175304 RW
	UINT32 reg_blk_wid                      :6;	//5:0	//Block size
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//13:8	//Block size
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :7;	//22:16	//Number of hblock
	UINT32 resvd2                           :1;
	UINT32 reg_l5_hei                       :7;	//30:24	//Number of vblock
	UINT32 resvd3                           :1;
	};
	};
}PE_F20_VSD_OBC_OBJT_PSP_CTRL01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175308 RW
	UINT32 reg_vs_inv                       :1;	//0 //vs inversion
	UINT32 reg_psp_en                       :1;	//1 //psp enable : 전체 enable
	UINT32 reg_hist_sel                     :2;	//3:2	//histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//8:4	//line 경계에서 repeat 시킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//9 //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//14:10	//frame 경계에서 repeat 시킬 v line 개수
	UINT32 reserved                         :1;	//15 //fg memory의 mee off
	UINT32 reg_margin_hei                   :8;	//23:16	//edge extraction의 V margin
	UINT32 reg_margin_wid                   :8;	//31:24	//edge extraction의 H margin
	};
	};
}PE_F20_VSD_OBC_OBJT_PSP_CTRL02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017530C RW
	UINT32 reg_edge_th                      :13;	//12:0	//threshold value for edge  : Edge threshold difference
	UINT32 resvd                            :3;
	UINT32 reg_w_box_th                     :8;	//23:16	//threshold value for w box : 후보 box 영역에 대한 threshold
	UINT32 reg_h_box_th                     :8;	//31:24	//threshold value for h box : 후보 box 영역에 대한 threshold
	};
	};
}PE_F20_VSD_OBC_OBJT_EDGE_TH_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175310 RW
	UINT32 reg_force_w1_pos                 :7;	//6:0	//(w1, h1)
	UINT32 resvd0                           :1;
	UINT32 reg_force_h1_pos                 :7;	//14:8	//(w1, h1)
	UINT32 resvd1                           :1;
	UINT32 reg_force_w2_pos                 :7;	//22:16	//(w2, h2)
	UINT32 resvd2                           :1;
	UINT32 reg_force_h2_pos                 :7;	//30:24	//(w2, h2)
	UINT32 reg_force_pos_en                 :1;	//31 //forced FG box posotion
	};
	};
}PE_F20_VSD_OBC_OBJT_FG_POSITION_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175314 RW
	UINT32 reg_perspect_lut_x_0             :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_X0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175318 RW
	UINT32 reg_perspect_lut_x_1             :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_X1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017531C RW
	UINT32 reg_perspect_lut_x_2             :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_X2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175320 RW
	UINT32 reg_perspect_lut_x_3             :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_X3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175324 RW
	UINT32 reg_perspect_lut_y_0             :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_Y0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175328 RW
	UINT32 reg_perspect_lut_y_1             :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_Y1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017532C RW
	UINT32 reg_perspect_lut_y_2             :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_Y2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175330 RW
	UINT32 reg_perspect_lut_y_3             :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_Y3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175334 RW
	UINT32 reg_bg_prob_factor               :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_fg_prob_factor               :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_stat_flat_w_mul              :4;	//19:16	//
	UINT32 reg_stat_flat_h_mul              :4;	//23:20	//
	UINT32 resvd2                           :8;
	};
	};
}PE_F20_VSD_OBC_OBJT_PROB_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175338 RW
	UINT32 reg_ellipse_master               :8;	//7:0	//gain * master
	UINT32 reg_e_mul_a                      :9;	//16:8	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//28:20	//4.5bit
	UINT32 resvd1                           :1;
	UINT32 reg_ellipse_disable              :1;	//30 //ellipse_gain disable (1)
	UINT32 reg_fg_mul_ellipse_en            :1;	//31 //enable
	};
	};
}PE_F20_VSD_OBC_OBJT_ELLIPS_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017533C RW
	UINT32 reg_ellipse_offset               :8;	//7:0	//parameter of ellipse offset
	UINT32 reg_bg_diff_mul                  :10;	//17:8	//6.4bit
	UINT32 resvd0                           :2;
	UINT32 reg_fg_diff_mul                  :10;	//29:20	//6.4bit
	UINT32 resvd1                           :2;
	};
	};
}PE_F20_VSD_OBC_OBJT_PROB_DIFF_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175340 RW
	UINT32 reg_p_offset                     :8;	//7:0	//p offset (알고리즘 parameter)
	UINT32 reg_e_offset                     :8;	//15:8	//e offset (알고리즘 parameter)
	UINT32 reg_dbg_map_sel                  :3;	//18:16	//map selection	0 : prob_map	1 : ellips_gain	2 : prob_fg_map	3 : prob_bg_map	4 : prob_diff_map	5 : candidate box	6 : L5 image
	UINT32 resvd                            :13;
	};
	};
}PE_F20_VSD_OBC_OBJT_OBJECT_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175344 RW
	UINT32 reg_blur_en                      :1;	//0 //9x5 spatial filter enable
	UINT32 resvd                            :31;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175348 RW
	UINT32 reg_disp_gain_l0                 :1;	//0 //psp_make_L0_gain의 출력 중 psp_gain을 display로 전환
	UINT32 resvd0                           :3;
	UINT32 reg_disp_gain_vrtx               :1;	//4 //vertex cpc gain 적용
	UINT32 resvd1                           :3;
	UINT32 reg_bot_bnd_enable               :1;	//8 //bottom bound 를 enable
	UINT32 reg_left_bnd_disable             :1;	//9 //left bound 를 disable
	UINT32 reg_top_bnd_disable              :1;	//10 //top bound 를 disable
	UINT32 resvd2                           :1;
	UINT32 reg_fifo_detour                  :1;	//12 //debug
	UINT32 resvd3                           :2;
	UINT32 reg_pic_end_status               :1;	//15 //debug
	UINT32 reg_dst_valid_count              :3;	//18:16	//debug (SYNC_DLY + 4) (DNR 0x19, SHP 0x0)
	UINT32 resvd4                           :5;
	UINT32 valid_expand                     :1;	//24 //shp mode only (sync index)
	UINT32 reg_sync_ready_mode              :1;	//25 //VSD sync mode 0
	UINT32 resvd5                           :2;
	UINT32 reg_iir_test                     :1;	//28 //debug
	UINT32 resvd6                           :3;
	};
	};
}PE_F20_VSD_OBC_OBJT_DISPLAY_DEBUG_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017534C RW
	UINT32 reg_psp_iir_alpha                :6;	//5:0	//IIR Alpha blending rate (0 ~ 1) 	6bit 기준이고 3A = 90%
	UINT32 resvd                            :25;
	UINT32 reg_psp_gain_init                :1;	//31 //IIR initial시 사용( data reset)
	};
	};
}PE_F20_VSD_OBC_OBJT_PSP_IIR_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175350 RW
	UINT32 psp_gain                         :1;	//0 //no use
	UINT32 psp_gain_dbg                     :1;	//1 //no use
	UINT32 resvd                            :30;
	};
	};
}PE_F20_VSD_OBC_OBJT_PSP_GAIN_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017535C RW
	UINT32 reg_vrtx_gain_tl_i               :8;	//7:0	//
	UINT32 reg_vrtx_gain_tr_i               :8;	//15:8	//
	UINT32 reg_vrtx_gain_bl_i               :8;	//23:16	//
	UINT32 reg_vrtx_gain_br_i               :8;	//31:24	//
	};
	};
}PE_F20_VSD_OBC_OBJT_VRTX_CPC_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175360 RW
	UINT32 hcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_HCOEF01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175364 RW
	UINT32 hcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_HCOEF23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175368 RW
	UINT32 hcoef4                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef5                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_HCOEF45_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017536C RW
	UINT32 hcoef6                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef7                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_HCOEF67_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175370 RW
	UINT32 hcoef8                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_HCOEF8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175374 RW
	UINT32 vcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_VCOEF01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175378 RW
	UINT32 vcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_VCOEF23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017537C RW
	UINT32 vcoef4                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
	};
}PE_F20_VSD_OBC_OBJT_BLUR_VCOEF4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175400 RW
	UINT32 y0_point                         :6;	//5:0	//control point of Y0
	UINT32 resvd0                           :2;
	UINT32 x0_point                         :6;	//13:8	//control point of X0
	UINT32 resvd1                           :2;
	UINT32 y1_point                         :6;	//21:16	//control point of Y1
	UINT32 resvd2                           :2;
	UINT32 x1_point                         :6;	//29:24	//control point of X1
	UINT32 resvd3                           :2;
	};
	};
}PE_F20_VSD_OBC_OBJT_L5_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175404 RW
	UINT32 y2_point                         :6;	//5:0	//control point of Y2
	UINT32 resvd0                           :2;
	UINT32 x2_point                         :6;	//13:8	//control point of X2
	UINT32 resvd1                           :2;
	UINT32 y3_point                         :6;	//21:16	//control point of Y3
	UINT32 resvd2                           :2;
	UINT32 x3_point                         :6;	//29:24	//control point of X3
	UINT32 resvd3                           :2;
	};
	};
}PE_F20_VSD_OBC_OBJT_L5_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175408 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
	};
}PE_F20_VSD_OBC_OBJT_L0_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017540C RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
	};
}PE_F20_VSD_OBC_OBJT_L0_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175410 RW
	UINT32 h_str                            :12;	//11:0	//window start h position
	UINT32 resvd0                           :4;
	UINT32 h_end                            :12;	//27:16	//window end h position
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_VSD_OBC_OBJT_EDGE_WIN_H_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175414 RW
	UINT32 v_str                            :12;	//11:0	//window start v position
	UINT32 resvd0                           :4;
	UINT32 v_end                            :12;	//27:16	//window end v position
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_VSD_OBC_OBJT_EDGE_WIN_V_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175428 RW
	UINT32 cliping_en                       :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 th_lower                         :6;	//9:4	//threshold of lower
	UINT32 resvd1                           :2;
	UINT32 th_upper                         :6;	//17:12	//threshold of upper
	UINT32 resvd2                           :2;
	UINT32 prc_step                         :6;	//25:20	//same protection step
	UINT32 resvd3                           :6;
	};
	};
}PE_F20_VSD_OBC_OBJT_PSP_IIR1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017542C RW
	UINT32 bg_measure_en                    :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 h_num                            :4;	//7:4	//divide hsize
	UINT32 v_num                            :4;	//11:8	//divide vsize
	UINT32 obj_th0                          :6;	//17:12	//threshold of minimum gain
	UINT32 resvd1                           :2;
	UINT32 obj_th1                          :8;	//27:20	//threshold of bin counting
	UINT32 resvd2                           :4;
	};
	};
}PE_F20_VSD_OBC_OBJT_BG_MEASURE_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175444 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face_en                          :1;	//31 //
	};
	};
}PE_F20_VSD_OBC_OBJT_FACE0_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175448 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face_en                          :1;	//31 //
	};
	};
}PE_F20_VSD_OBC_OBJT_FACE1_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017544C RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face_en                          :1;	//31 //
	};
	};
}PE_F20_VSD_OBC_OBJT_FACE2_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175450 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face_en                          :1;	//31 //
	};
	};
}PE_F20_VSD_OBC_OBJT_FACE3_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175454 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_VSD_OBC_OBJT_ELLIPS0_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175458 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_VSD_OBC_OBJT_ELLIPS1_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017545C RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_VSD_OBC_OBJT_ELLIPS2_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175460 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_VSD_OBC_OBJT_ELLIPS3_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175500 RW
	UINT32 reg_img_wid                      :12;	//11:0	//horizontal resolution
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//27:16	//vertical resolution
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_VSD_OBC_FACE_PSP_CTRL00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175504 RW
	UINT32 reg_blk_wid                      :6;	//5:0	//Block size
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//13:8	//Block size
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :7;	//22:16	//Number of hblock
	UINT32 resvd2                           :1;
	UINT32 reg_l5_hei                       :7;	//30:24	//Number of vblock
	UINT32 resvd3                           :1;
	};
	};
}PE_F20_VSD_OBC_FACE_PSP_CTRL01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175508 RW
	UINT32 reg_vs_inv                       :1;	//0 //vs inversion
	UINT32 reg_psp_en                       :1;	//1 //psp enable : 전체 enable
	UINT32 reg_hist_sel                     :2;	//3:2	//histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//8:4	//line 경계에서 repeat 시킬 h pixel 개수
	UINT32 resvd                            :1;
	UINT32 reg_repeat_v_num                 :5;	//14:10	//frame 경계에서 repeat 시킬 v line 개수
	UINT32 reserved                         :1;	//15 //fg memory의 mee off
	UINT32 reg_margin_hei                   :8;	//23:16	//edge extraction의 V margin
	UINT32 reg_margin_wid                   :8;	//31:24	//edge extraction의 H margin
	};
	};
}PE_F20_VSD_OBC_FACE_PSP_CTRL02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017550C RW
	UINT32 reg_edge_th                      :13;	//12:0	//threshold value for edge  : Edge threshold difference
	UINT32 resvd                            :3;
	UINT32 reg_w_box_th                     :8;	//23:16	//threshold value for w box : 후보 box 영역에 대한 threshold
	UINT32 reg_h_box_th                     :8;	//31:24	//threshold value for h box : 후보 box 영역에 대한 threshold
	};
	};
}PE_F20_VSD_OBC_FACE_EDGE_TH_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175510 RW
	UINT32 reg_force_w1_pos                 :7;	//6:0	//(w1, h1)
	UINT32 resvd0                           :1;
	UINT32 reg_force_h1_pos                 :7;	//14:8	//(w1, h1)
	UINT32 resvd1                           :1;
	UINT32 reg_force_w2_pos                 :7;	//22:16	//(w2, h2)
	UINT32 resvd2                           :1;
	UINT32 reg_force_h2_pos                 :7;	//30:24	//(w2, h2)
	UINT32 reg_force_pos_en                 :1;	//31 //forced FG box posotion
	};
	};
}PE_F20_VSD_OBC_FACE_FG_POSITION_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175514 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_FACE_RESERVED0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175518 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_FACE_RESERVED1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017551C RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_FACE_RESERVED2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175520 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_FACE_RESERVED3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175524 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_FACE_RESERVED4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175528 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_FACE_RESERVED5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017552C RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_FACE_RESERVED6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175530 RW
	UINT32 reserved                         :32;	//31:0	//
	};
	};
}PE_F20_VSD_OBC_FACE_RESERVED7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175534 RW
	UINT32 reg_bg_prob_factor               :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_fg_prob_factor               :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_stat_flat_w_mul              :4;	//19:16	//
	UINT32 reg_stat_flat_h_mul              :4;	//23:20	//
	UINT32 resvd2                           :8;
	};
	};
}PE_F20_VSD_OBC_FACE_PROB_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175538 RW
	UINT32 reg_ellipse_master               :8;	//7:0	//gain * master
	UINT32 reg_e_mul_a                      :9;	//16:8	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//28:20	//4.5bit
	UINT32 resvd1                           :1;
	UINT32 reg_ellipse_disable              :1;	//30 //ellipse_gain disable (1)
	UINT32 reg_fg_mul_ellipse_en            :1;	//31 //enable
	};
	};
}PE_F20_VSD_OBC_FACE_ELLIPS_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017553C RW
	UINT32 reg_ellipse_offset               :8;	//7:0	//parameter of ellipse offset
	UINT32 reg_bg_diff_mul                  :10;	//17:8	//6.4bit
	UINT32 resvd0                           :2;
	UINT32 reg_fg_diff_mul                  :10;	//29:20	//6.4bit
	UINT32 resvd1                           :2;
	};
	};
}PE_F20_VSD_OBC_FACE_PROB_DIFF_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175540 RW
	UINT32 reg_p_offset                     :8;	//7:0	//p offset (알고리즘 parameter)
	UINT32 reg_e_offset                     :8;	//15:8	//e offset (알고리즘 parameter)
	UINT32 reg_dbg_map_sel                  :3;	//18:16	//map selection	0 : prob_map	1 : ellips_gain	2 : prob_fg_map	3 : prob_bg_map	4 : prob_diff_map	5 : candidate box	6 : L5 image
	UINT32 resvd                            :13;
	};
	};
}PE_F20_VSD_OBC_FACE_OBJECT_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175544 RW
	UINT32 reg_blur_en                      :1;	//0 //9x5 spatial filter enable
	UINT32 resvd                            :31;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175548 RW
	UINT32 reg_disp_gain_l0                 :1;	//0 //psp_make_L0_gain의 출력 중 psp_gain을 display로 전환
	UINT32 resvd0                           :3;
	UINT32 reg_disp_gain_vrtx               :1;	//4 //vertex cpc gain 적용
	UINT32 resvd1                           :3;
	UINT32 reg_bot_bnd_enable               :1;	//8 //bottom bound 를 enable
	UINT32 reg_left_bnd_disable             :1;	//9 //left bound 를 disable
	UINT32 reg_top_bnd_disable              :1;	//10 //top bound 를 disable
	UINT32 resvd2                           :1;
	UINT32 reg_fifo_detour                  :1;	//12 //debug
	UINT32 resvd3                           :2;
	UINT32 reg_pic_end_status               :1;	//15 //debug
	UINT32 reg_dst_valid_count              :8;	//23:16	//debug
	UINT32 valid_expand                     :1;	//24 //shp mode only (sync index)
	UINT32 reg_sync_ready_mode              :1;	//25 //VSD sync mode 0
	UINT32 resvd4                           :2;
	UINT32 reg_iir_test                     :1;	//28 //debug
	UINT32 resvd5                           :3;
	};
	};
}PE_F20_VSD_OBC_FACE_DISPLAY_DEBUG_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017554C RW
	UINT32 reg_psp_iir_alpha                :6;	//5:0	//IIR Alpha blending rate (0 ~ 1) 	6bit 기준이고 3A = 90%
	UINT32 resvd                            :25;
	UINT32 reg_psp_gain_init                :1;	//31 //IIR initial시 사용( data reset)
	};
	};
}PE_F20_VSD_OBC_FACE_PSP_IIR_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175550 RW
	UINT32 psp_gain                         :1;	//0 //no use
	UINT32 psp_gain_dbg                     :1;	//1 //no use
	UINT32 resvd                            :30;
	};
	};
}PE_F20_VSD_OBC_FACE_PSP_GAIN_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017555C RW
	UINT32 reg_vrtx_gain_tl_i               :8;	//7:0	//
	UINT32 reg_vrtx_gain_tr_i               :8;	//15:8	//
	UINT32 reg_vrtx_gain_bl_i               :8;	//23:16	//
	UINT32 reg_vrtx_gain_br_i               :8;	//31:24	//
	};
	};
}PE_F20_VSD_OBC_FACE_VRTX_CPC_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175560 RW
	UINT32 hcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_HCOEF01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175564 RW
	UINT32 hcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_HCOEF23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175568 RW
	UINT32 hcoef4                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef5                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_HCOEF45_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017556C RW
	UINT32 hcoef6                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef7                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_HCOEF67_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175570 RW
	UINT32 hcoef8                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_HCOEF8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175574 RW
	UINT32 vcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_VCOEF01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175578 RW
	UINT32 vcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_VCOEF23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017557C RW
	UINT32 vcoef4                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
	};
}PE_F20_VSD_OBC_FACE_BLUR_VCOEF4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175600 RW
	UINT32 y0_point                         :6;	//5:0	//control point of Y0
	UINT32 resvd0                           :2;
	UINT32 x0_point                         :6;	//13:8	//control point of X0
	UINT32 resvd1                           :2;
	UINT32 y1_point                         :6;	//21:16	//control point of Y1
	UINT32 resvd2                           :2;
	UINT32 x1_point                         :6;	//29:24	//control point of X1
	UINT32 resvd3                           :2;
	};
	};
}PE_F20_VSD_OBC_FACE_L5_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175604 RW
	UINT32 y2_point                         :6;	//5:0	//control point of Y2
	UINT32 resvd0                           :2;
	UINT32 x2_point                         :6;	//13:8	//control point of X2
	UINT32 resvd1                           :2;
	UINT32 y3_point                         :6;	//21:16	//control point of Y3
	UINT32 resvd2                           :2;
	UINT32 x3_point                         :6;	//29:24	//control point of X3
	UINT32 resvd3                           :2;
	};
	};
}PE_F20_VSD_OBC_FACE_L5_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175608 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
	};
}PE_F20_VSD_OBC_FACE_L0_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017560C RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
	};
}PE_F20_VSD_OBC_FACE_L0_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175610 RW
	UINT32 h_str                            :12;	//11:0	//window start h position
	UINT32 resvd0                           :4;
	UINT32 h_end                            :12;	//27:16	//window end h position
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_VSD_OBC_FACE_EDGE_WIN_H_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175614 RW
	UINT32 v_str                            :12;	//11:0	//window start v position
	UINT32 resvd0                           :4;
	UINT32 v_end                            :12;	//27:16	//window end v position
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_VSD_OBC_FACE_EDGE_WIN_V_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175628 RW
	UINT32 cliping_en                       :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 th_lower                         :6;	//9:4	//threshold of lower
	UINT32 resvd1                           :2;
	UINT32 th_upper                         :6;	//17:12	//threshold of upper
	UINT32 resvd2                           :2;
	UINT32 prc_step                         :6;	//25:20	//same protection step
	UINT32 resvd3                           :6;
	};
	};
}PE_F20_VSD_OBC_FACE_PSP_IIR1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017562C RW
	UINT32 bg_measure_en                    :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 h_num                            :4;	//7:4	//divide hsize
	UINT32 v_num                            :4;	//11:8	//divide vsize
	UINT32 obj_th0                          :6;	//17:12	//threshold of minimum gain
	UINT32 resvd1                           :2;
	UINT32 obj_th1                          :8;	//27:20	//threshold of bin counting
	UINT32 resvd2                           :4;
	};
	};
}PE_F20_VSD_OBC_FACE_BG_MEASURE_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175644 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//end H width
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//start H width
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//end V line
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//start V line
	UINT32 face_en                          :1;	//31 //
	};
	};
}PE_F20_VSD_OBC_FACE_FACE0_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175648 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face_en                          :1;	//31 //
	};
	};
}PE_F20_VSD_OBC_FACE_FACE1_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017564C RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face_en                          :1;	//31 //
	};
	};
}PE_F20_VSD_OBC_FACE_FACE2_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175650 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face_en                          :1;	//31 //
	};
	};
}PE_F20_VSD_OBC_FACE_FACE3_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175654 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_VSD_OBC_FACE_ELLIPS0_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175658 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_VSD_OBC_FACE_ELLIPS1_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017565C RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_VSD_OBC_FACE_ELLIPS2_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175660 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
	};
}PE_F20_VSD_OBC_FACE_ELLIPS3_SET_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175200 RW
	UINT32 reg_psp_en                       :1;	//0 //
	UINT32 reg_psp_debug_en                 :1;	//1 //
	UINT32 reg_chroma_protection_en         :1;	//2 //
	UINT32 reg_cbst_en                      :1;	//3 //
	UINT32 reg_sat_gain_en                  :1;	//4 //
	UINT32 reg_sat_gain_mode                :1;	//5 //
	UINT32 resvd                            :25;
	UINT32 reg_cg_disable                   :1;	//31 //1: Clock-gating disable
	};
	};
}PE_F20_RCE_OBJT_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175204 RW
	UINT32 reg_psp_map_master_gain          :8;	//7:0	//
	UINT32 resvd                            :24;
	};
	};
}PE_F20_RCE_OBJT_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175208 RW
	UINT32 reg_cb_offset_gain               :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_cr_offset_gain               :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017520C RW
	UINT32 reg_psp_lut0_y0                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x0                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175210 RW
	UINT32 reg_psp_lut0_y1                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x1                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175214 RW
	UINT32 reg_psp_lut0_y2                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x2                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175218 RW
	UINT32 reg_psp_lut0_y3                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x3                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017521C RW
	UINT32 reg_psp_lut0_y4                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x4                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175220 RW
	UINT32 reg_psp_lut0_y5                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x5                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175224 RW
	UINT32 reg_psp_lut0_y6                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x6                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175228 RW
	UINT32 reg_psp_lut0_y7                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x7                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017522C RW
	UINT32 reg_psp_lut1_y0                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x0                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175230 RW
	UINT32 reg_psp_lut1_y1                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x1                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175234 RW
	UINT32 reg_psp_lut1_y2                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x2                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175238 RW
	UINT32 reg_psp_lut1_y3                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x3                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017523C RW
	UINT32 reg_psp_lut1_y4                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x4                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175240 RW
	UINT32 reg_psp_lut1_y5                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x5                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175244 RW
	UINT32 reg_psp_lut1_y6                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x6                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175248 RW
	UINT32 reg_psp_lut1_y7                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x7                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017524C RW
	UINT32 reg_psp_gain_lut0_y0             :8;	//7:0	//
	UINT32 reg_psp_gain_lut0_x0             :8;	//15:8	//
	UINT32 reg_psp_gain_lut0_y1             :8;	//23:16	//
	UINT32 reg_psp_gain_lut0_x1             :8;	//31:24	//
	};
	};
}PE_F20_RCE_OBJT_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175250 RW
	UINT32 reg_psp_gain_lut1_y0             :8;	//7:0	//
	UINT32 reg_psp_gain_lut1_x0             :8;	//15:8	//
	UINT32 reg_psp_gain_lut1_y1             :8;	//23:16	//
	UINT32 reg_psp_gain_lut1_x1             :8;	//31:24	//
	};
	};
}PE_F20_RCE_OBJT_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175254 RW
	UINT32 reg_yy_lut_pts_x1                :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_yy_lut_pts_x0                :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175258 RW
	UINT32 reg_yy_lut_pts_x3                :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_yy_lut_pts_x2                :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_OBJT_CTRL_22_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017525C RW
	UINT32 reg_yy_lut_pts_y3                :8;	//7:0	//
	UINT32 reg_yy_lut_pts_y2                :8;	//15:8	//
	UINT32 reg_yy_lut_pts_y1                :8;	//23:16	//
	UINT32 reg_yy_lut_pts_y0                :8;	//31:24	//
	};
	};
}PE_F20_RCE_OBJT_CTRL_23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175260 RW
	UINT32 reg_cc_lut_pts_y1                :8;	//7:0	//
	UINT32 reg_cc_lut_pts_x1                :8;	//15:8	//
	UINT32 reg_cc_lut_pts_y0                :8;	//23:16	//
	UINT32 reg_cc_lut_pts_x0                :8;	//31:24	//
	};
	};
}PE_F20_RCE_OBJT_CTRL_24_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175264 RW
	UINT32 reg_cc_lut_pts_y3                :8;	//7:0	//
	UINT32 reg_cc_lut_pts_x3                :8;	//15:8	//
	UINT32 reg_cc_lut_pts_y2                :8;	//23:16	//
	UINT32 reg_cc_lut_pts_x2                :8;	//31:24	//
	};
	};
}PE_F20_RCE_OBJT_CTRL_25_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175268 RW
	UINT32 reg_cbst_lut_pts_y1              :8;	//7:0	//
	UINT32 reg_cbst_lut_pts_x1              :8;	//15:8	//
	UINT32 reg_cbst_lut_pts_y0              :8;	//23:16	//
	UINT32 reg_cbst_lut_pts_x0              :8;	//31:24	//
	};
	};
}PE_F20_RCE_OBJT_CTRL_26_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017526C RW
	UINT32 reg_cbst_lut_pts_y3              :8;	//7:0	//
	UINT32 reg_cbst_lut_pts_x3              :8;	//15:8	//
	UINT32 reg_cbst_lut_pts_y2              :8;	//23:16	//
	UINT32 reg_cbst_lut_pts_x2              :8;	//31:24	//
	};
	};
}PE_F20_RCE_OBJT_CTRL_27_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175270 RW
	UINT32 reg_win_w0_y0                    :12;	//11:0	//
	UINT32 resvd                            :4;
	UINT32 reg_win_w0_x0                    :12;	//27:16	//
	UINT32 reg_win_enable                   :1;	//28 //
	UINT32 reg_win0_enable                  :1;	//29 //
	UINT32 reg_win1_enable                  :1;	//30 //
	UINT32 reg_win_outside                  :1;	//31 //
	};
	};
}PE_F20_RCE_OBJT_CTRL_28_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175274 RW
	UINT32 reg_win_w0_y1                    :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_win_w0_x1                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_RCE_OBJT_CTRL_29_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175278 RW
	UINT32 reg_win_w1_y0                    :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_win_w1_x0                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_RCE_OBJT_CTRL_30_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017527C RW
	UINT32 reg_win_w1_y1                    :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_win_w1_x1                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
	};
}PE_F20_RCE_OBJT_CTRL_31_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175280 RW
	UINT32 reg_psp_en                       :1;	//0 //
	UINT32 reg_psp_debug_en                 :1;	//1 //
	UINT32 reg_chroma_protection_en         :1;	//2 //
	UINT32 reg_cbst_en                      :1;	//3 //
	UINT32 reg_sat_gain_en                  :1;	//4 //
	UINT32 reg_sat_gain_mode                :1;	//5 //
	UINT32 resvd                            :25;
	UINT32 reg_cg_disable                   :1;	//31 //1: Clock-gating disable
	};
	};
}PE_F20_RCE_FACE_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175284 RW
	UINT32 reg_psp_map_master_gain          :8;	//7:0	//
	UINT32 resvd                            :24;
	};
	};
}PE_F20_RCE_FACE_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175288 RW
	UINT32 reg_cb_offset_gain               :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_cr_offset_gain               :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017528C RW
	UINT32 reg_psp_lut0_y0                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x0                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175290 RW
	UINT32 reg_psp_lut0_y1                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x1                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175294 RW
	UINT32 reg_psp_lut0_y2                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x2                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF0175298 RW
	UINT32 reg_psp_lut0_y3                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x3                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF017529C RW
	UINT32 reg_psp_lut0_y4                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x4                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752A0 RW
	UINT32 reg_psp_lut0_y5                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x5                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752A4 RW
	UINT32 reg_psp_lut0_y6                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x6                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752A8 RW
	UINT32 reg_psp_lut0_y7                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut0_x7                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752AC RW
	UINT32 reg_psp_lut1_y0                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x0                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752B0 RW
	UINT32 reg_psp_lut1_y1                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x1                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752B4 RW
	UINT32 reg_psp_lut1_y2                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x2                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752B8 RW
	UINT32 reg_psp_lut1_y3                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x3                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752BC RW
	UINT32 reg_psp_lut1_y4                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x4                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752C0 RW
	UINT32 reg_psp_lut1_y5                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x5                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752C4 RW
	UINT32 reg_psp_lut1_y6                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x6                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752C8 RW
	UINT32 reg_psp_lut1_y7                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_psp_lut1_x7                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752CC RW
	UINT32 reg_psp_gain_lut0_y0             :8;	//7:0	//
	UINT32 reg_psp_gain_lut0_x0             :8;	//15:8	//
	UINT32 reg_psp_gain_lut0_y1             :8;	//23:16	//
	UINT32 reg_psp_gain_lut0_x1             :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752D0 RW
	UINT32 reg_psp_gain_lut1_y0             :8;	//7:0	//
	UINT32 reg_psp_gain_lut1_x0             :8;	//15:8	//
	UINT32 reg_psp_gain_lut1_y1             :8;	//23:16	//
	UINT32 reg_psp_gain_lut1_x1             :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752D4 RW
	UINT32 reg_yy_lut_pts_x1                :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_yy_lut_pts_x0                :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752D8 RW
	UINT32 reg_yy_lut_pts_x3                :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_yy_lut_pts_x2                :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_F20_RCE_FACE_CTRL_22_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752DC RW
	UINT32 reg_yy_lut_pts_y3                :8;	//7:0	//
	UINT32 reg_yy_lut_pts_y2                :8;	//15:8	//
	UINT32 reg_yy_lut_pts_y1                :8;	//23:16	//
	UINT32 reg_yy_lut_pts_y0                :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752E0 RW
	UINT32 reg_cc_lut_pts_y1                :8;	//7:0	//
	UINT32 reg_cc_lut_pts_x1                :8;	//15:8	//
	UINT32 reg_cc_lut_pts_y0                :8;	//23:16	//
	UINT32 reg_cc_lut_pts_x0                :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_24_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752E4 RW
	UINT32 reg_cc_lut_pts_y3                :8;	//7:0	//
	UINT32 reg_cc_lut_pts_x3                :8;	//15:8	//
	UINT32 reg_cc_lut_pts_y2                :8;	//23:16	//
	UINT32 reg_cc_lut_pts_x2                :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_25_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752E8 RW
	UINT32 reg_cbst_lut_pts_y1              :8;	//7:0	//
	UINT32 reg_cbst_lut_pts_x1              :8;	//15:8	//
	UINT32 reg_cbst_lut_pts_y0              :8;	//23:16	//
	UINT32 reg_cbst_lut_pts_x0              :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_26_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752EC RW
	UINT32 reg_cbst_lut_pts_y3              :8;	//7:0	//
	UINT32 reg_cbst_lut_pts_x3              :8;	//15:8	//
	UINT32 reg_cbst_lut_pts_y2              :8;	//23:16	//
	UINT32 reg_cbst_lut_pts_x2              :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_27_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752F0 RW
	UINT32 reg_face_objt_lut_y2             :8;	//7:0	//
	UINT32 reg_face_objt_lut_x2             :8;	//15:8	//
	UINT32 reg_face_objt_lut_y3             :8;	//23:16	//
	UINT32 reg_face_objt_lut_x3             :8;	//31:24	//face-objt
	};
	};
}PE_F20_RCE_FACE_CTRL_28_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752F4 RW
	UINT32 reg_face_objt_lut_y0             :8;	//7:0	//
	UINT32 reg_face_objt_lut_x0             :8;	//15:8	//
	UINT32 reg_face_objt_lut_y1             :8;	//23:16	//
	UINT32 reg_face_objt_lut_x1             :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_29_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752F8 RW
	UINT32 reg_objt_face_lut_y2             :8;	//7:0	//
	UINT32 reg_objt_face_lut_x2             :8;	//15:8	//
	UINT32 reg_objt_face_lut_y3             :8;	//23:16	//
	UINT32 reg_objt_face_lut_x3             :8;	//31:24	//objt-face
	};
	};
}PE_F20_RCE_FACE_CTRL_30_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF01752FC RW
	UINT32 reg_objt_face_lut_y0             :8;	//7:0	//
	UINT32 reg_objt_face_lut_x0             :8;	//15:8	//
	UINT32 reg_objt_face_lut_y1             :8;	//23:16	//
	UINT32 reg_objt_face_lut_x1             :8;	//31:24	//
	};
	};
}PE_F20_RCE_FACE_CTRL_31_T;

typedef struct
{
	PE_F20_VSD_OBC_OBJT_PSP_CTRL00_T                   psp_ctrl00;	//0xF0175300
	PE_F20_VSD_OBC_OBJT_PSP_CTRL01_T                   psp_ctrl01;	//0xF0175304
	PE_F20_VSD_OBC_OBJT_PSP_CTRL02_T                   psp_ctrl02;	//0xF0175308
	PE_F20_VSD_OBC_OBJT_EDGE_TH_T                         edge_th;	//0xF017530C
	PE_F20_VSD_OBC_OBJT_FG_POSITION_T                 fg_position;	//0xF0175310
	PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_X0_T         perspect_lut_x0;	//0xF0175314
	PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_X1_T         perspect_lut_x1;	//0xF0175318
	PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_X2_T         perspect_lut_x2;	//0xF017531C
	PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_X3_T         perspect_lut_x3;	//0xF0175320
	PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_Y0_T         perspect_lut_y0;	//0xF0175324
	PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_Y1_T         perspect_lut_y1;	//0xF0175328
	PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_Y2_T         perspect_lut_y2;	//0xF017532C
	PE_F20_VSD_OBC_OBJT_PERSPECT_LUT_Y3_T         perspect_lut_y3;	//0xF0175330
	PE_F20_VSD_OBC_OBJT_PROB_MAP_T                       prob_map;	//0xF0175334
	PE_F20_VSD_OBC_OBJT_ELLIPS_MAP_T                   ellips_map;	//0xF0175338
	PE_F20_VSD_OBC_OBJT_PROB_DIFF_MAP_T             prob_diff_map;	//0xF017533C
	PE_F20_VSD_OBC_OBJT_OBJECT_MAP_T                   object_map;	//0xF0175340
	PE_F20_VSD_OBC_OBJT_BLUR_MAP_T                       blur_map;	//0xF0175344
	PE_F20_VSD_OBC_OBJT_DISPLAY_DEBUG_MAP_T     display_debug_map;	//0xF0175348
	PE_F20_VSD_OBC_OBJT_PSP_IIR_T                         psp_iir;	//0xF017534C
	PE_F20_VSD_OBC_OBJT_PSP_GAIN_T                       psp_gain;	//0xF0175350
	PE_F20_VSD_OBC_OBJT_VRTX_CPC_CTRL_T             vrtx_cpc_ctrl;	//0xF017535C
	PE_F20_VSD_OBC_OBJT_BLUR_HCOEF01_T               blur_hcoef01;	//0xF0175360
	PE_F20_VSD_OBC_OBJT_BLUR_HCOEF23_T               blur_hcoef23;	//0xF0175364
	PE_F20_VSD_OBC_OBJT_BLUR_HCOEF45_T               blur_hcoef45;	//0xF0175368
	PE_F20_VSD_OBC_OBJT_BLUR_HCOEF67_T               blur_hcoef67;	//0xF017536C
	PE_F20_VSD_OBC_OBJT_BLUR_HCOEF8_T                 blur_hcoef8;	//0xF0175370
	PE_F20_VSD_OBC_OBJT_BLUR_VCOEF01_T               blur_vcoef01;	//0xF0175374
	PE_F20_VSD_OBC_OBJT_BLUR_VCOEF23_T               blur_vcoef23;	//0xF0175378
	PE_F20_VSD_OBC_OBJT_BLUR_VCOEF4_T                 blur_vcoef4;	//0xF017537C
	PE_F20_VSD_OBC_OBJT_L5_GAIN_LUT1_T               l5_gain_lut1;	//0xF0175400
	PE_F20_VSD_OBC_OBJT_L5_GAIN_LUT2_T               l5_gain_lut2;	//0xF0175404
	PE_F20_VSD_OBC_OBJT_L0_GAIN_LUT1_T               l0_gain_lut1;	//0xF0175408
	PE_F20_VSD_OBC_OBJT_L0_GAIN_LUT2_T               l0_gain_lut2;	//0xF017540C
	PE_F20_VSD_OBC_OBJT_EDGE_WIN_H_T                   edge_win_h;	//0xF0175410
	PE_F20_VSD_OBC_OBJT_EDGE_WIN_V_T                   edge_win_v;	//0xF0175414
	PE_F20_VSD_OBC_OBJT_PSP_IIR1_T                       psp_iir1;	//0xF0175428
	PE_F20_VSD_OBC_OBJT_BG_MEASURE_CTRL_T         bg_measure_ctrl;	//0xF017542C
	PE_F20_VSD_OBC_OBJT_FACE0_SET_T                     face0_set;	//0xF0175444
	PE_F20_VSD_OBC_OBJT_FACE1_SET_T                     face1_set;	//0xF0175448
	PE_F20_VSD_OBC_OBJT_FACE2_SET_T                     face2_set;	//0xF017544C
	PE_F20_VSD_OBC_OBJT_FACE3_SET_T                     face3_set;	//0xF0175450
	PE_F20_VSD_OBC_OBJT_ELLIPS0_SET_T                 ellips0_set;	//0xF0175454
	PE_F20_VSD_OBC_OBJT_ELLIPS1_SET_T                 ellips1_set;	//0xF0175458
	PE_F20_VSD_OBC_OBJT_ELLIPS2_SET_T                 ellips2_set;	//0xF017545C
	PE_F20_VSD_OBC_OBJT_ELLIPS3_SET_T                 ellips3_set;	//0xF0175460
}PE_CHPI_OBO_TBL_F20_T;

typedef struct
{
	PE_F20_VSD_OBC_FACE_PSP_CTRL00_T                   psp_ctrl00;	//0xF0175500
	PE_F20_VSD_OBC_FACE_PSP_CTRL01_T                   psp_ctrl01;	//0xF0175504
	PE_F20_VSD_OBC_FACE_PSP_CTRL02_T                   psp_ctrl02;	//0xF0175508
	PE_F20_VSD_OBC_FACE_EDGE_TH_T                         edge_th;	//0xF017550C
	PE_F20_VSD_OBC_FACE_FG_POSITION_T                 fg_position;	//0xF0175510
	PE_F20_VSD_OBC_FACE_RESERVED0_T                     reserved0;	//0xF0175514
	PE_F20_VSD_OBC_FACE_RESERVED1_T                     reserved1;	//0xF0175518
	PE_F20_VSD_OBC_FACE_RESERVED2_T                     reserved2;	//0xF017551C
	PE_F20_VSD_OBC_FACE_RESERVED3_T                     reserved3;	//0xF0175520
	PE_F20_VSD_OBC_FACE_RESERVED4_T                     reserved4;	//0xF0175524
	PE_F20_VSD_OBC_FACE_RESERVED5_T                     reserved5;	//0xF0175528
	PE_F20_VSD_OBC_FACE_RESERVED6_T                     reserved6;	//0xF017552C
	PE_F20_VSD_OBC_FACE_RESERVED7_T                     reserved7;	//0xF0175530
	PE_F20_VSD_OBC_FACE_PROB_MAP_T                       prob_map;	//0xF0175534
	PE_F20_VSD_OBC_FACE_ELLIPS_MAP_T                   ellips_map;	//0xF0175538
	PE_F20_VSD_OBC_FACE_PROB_DIFF_MAP_T             prob_diff_map;	//0xF017553C
	PE_F20_VSD_OBC_FACE_OBJECT_MAP_T                   object_map;	//0xF0175540
	PE_F20_VSD_OBC_FACE_BLUR_MAP_T                       blur_map;	//0xF0175544
	PE_F20_VSD_OBC_FACE_DISPLAY_DEBUG_MAP_T     display_debug_map;	//0xF0175548
	PE_F20_VSD_OBC_FACE_PSP_IIR_T                         psp_iir;	//0xF017554C
	PE_F20_VSD_OBC_FACE_PSP_GAIN_T                       psp_gain;	//0xF0175550
	PE_F20_VSD_OBC_FACE_VRTX_CPC_CTRL_T             vrtx_cpc_ctrl;	//0xF017555C
	PE_F20_VSD_OBC_FACE_BLUR_HCOEF01_T               blur_hcoef01;	//0xF0175560
	PE_F20_VSD_OBC_FACE_BLUR_HCOEF23_T               blur_hcoef23;	//0xF0175564
	PE_F20_VSD_OBC_FACE_BLUR_HCOEF45_T               blur_hcoef45;	//0xF0175568
	PE_F20_VSD_OBC_FACE_BLUR_HCOEF67_T               blur_hcoef67;	//0xF017556C
	PE_F20_VSD_OBC_FACE_BLUR_HCOEF8_T                 blur_hcoef8;	//0xF0175570
	PE_F20_VSD_OBC_FACE_BLUR_VCOEF01_T               blur_vcoef01;	//0xF0175574
	PE_F20_VSD_OBC_FACE_BLUR_VCOEF23_T               blur_vcoef23;	//0xF0175578
	PE_F20_VSD_OBC_FACE_BLUR_VCOEF4_T                 blur_vcoef4;	//0xF017557C
	PE_F20_VSD_OBC_FACE_L5_GAIN_LUT1_T               l5_gain_lut1;	//0xF0175600
	PE_F20_VSD_OBC_FACE_L5_GAIN_LUT2_T               l5_gain_lut2;	//0xF0175604
	PE_F20_VSD_OBC_FACE_L0_GAIN_LUT1_T               l0_gain_lut1;	//0xF0175608
	PE_F20_VSD_OBC_FACE_L0_GAIN_LUT2_T               l0_gain_lut2;	//0xF017560C
	PE_F20_VSD_OBC_FACE_EDGE_WIN_H_T                   edge_win_h;	//0xF0175610
	PE_F20_VSD_OBC_FACE_EDGE_WIN_V_T                   edge_win_v;	//0xF0175614
	PE_F20_VSD_OBC_FACE_PSP_IIR1_T                       psp_iir1;	//0xF0175628
	PE_F20_VSD_OBC_FACE_BG_MEASURE_CTRL_T         bg_measure_ctrl;	//0xF017562C
	PE_F20_VSD_OBC_FACE_FACE0_SET_T                     face0_set;	//0xF0175644
	PE_F20_VSD_OBC_FACE_FACE1_SET_T                     face1_set;	//0xF0175648
	PE_F20_VSD_OBC_FACE_FACE2_SET_T                     face2_set;	//0xF017564C
	PE_F20_VSD_OBC_FACE_FACE3_SET_T                     face3_set;	//0xF0175650
	PE_F20_VSD_OBC_FACE_ELLIPS0_SET_T                 ellips0_set;	//0xF0175654
	PE_F20_VSD_OBC_FACE_ELLIPS1_SET_T                 ellips1_set;	//0xF0175658
	PE_F20_VSD_OBC_FACE_ELLIPS2_SET_T                 ellips2_set;	//0xF017565C
	PE_F20_VSD_OBC_FACE_ELLIPS3_SET_T                 ellips3_set;	//0xF0175660
}PE_CHPI_OBF_TBL_F20_T;

typedef struct
{
	PE_F20_RCE_OBJT_CTRL_00_T            reg_rce_objt_ctrl_00;	//0xF0175200
	PE_F20_RCE_OBJT_CTRL_01_T            reg_rce_objt_ctrl_01;	//0xF0175204
	PE_F20_RCE_OBJT_CTRL_02_T            reg_rce_objt_ctrl_02;	//0xF0175208
	PE_F20_RCE_OBJT_CTRL_03_T            reg_rce_objt_ctrl_03;	//0xF017520C
	PE_F20_RCE_OBJT_CTRL_04_T            reg_rce_objt_ctrl_04;	//0xF0175210
	PE_F20_RCE_OBJT_CTRL_05_T            reg_rce_objt_ctrl_05;	//0xF0175214
	PE_F20_RCE_OBJT_CTRL_06_T            reg_rce_objt_ctrl_06;	//0xF0175218
	PE_F20_RCE_OBJT_CTRL_07_T            reg_rce_objt_ctrl_07;	//0xF017521C
	PE_F20_RCE_OBJT_CTRL_08_T            reg_rce_objt_ctrl_08;	//0xF0175220
	PE_F20_RCE_OBJT_CTRL_09_T            reg_rce_objt_ctrl_09;	//0xF0175224
	PE_F20_RCE_OBJT_CTRL_10_T            reg_rce_objt_ctrl_10;	//0xF0175228
	PE_F20_RCE_OBJT_CTRL_11_T            reg_rce_objt_ctrl_11;	//0xF017522C
	PE_F20_RCE_OBJT_CTRL_12_T            reg_rce_objt_ctrl_12;	//0xF0175230
	PE_F20_RCE_OBJT_CTRL_13_T            reg_rce_objt_ctrl_13;	//0xF0175234
	PE_F20_RCE_OBJT_CTRL_14_T            reg_rce_objt_ctrl_14;	//0xF0175238
	PE_F20_RCE_OBJT_CTRL_15_T            reg_rce_objt_ctrl_15;	//0xF017523C
	PE_F20_RCE_OBJT_CTRL_16_T            reg_rce_objt_ctrl_16;	//0xF0175240
	PE_F20_RCE_OBJT_CTRL_17_T            reg_rce_objt_ctrl_17;	//0xF0175244
	PE_F20_RCE_OBJT_CTRL_18_T            reg_rce_objt_ctrl_18;	//0xF0175248
	PE_F20_RCE_OBJT_CTRL_19_T            reg_rce_objt_ctrl_19;	//0xF017524C
	PE_F20_RCE_OBJT_CTRL_20_T            reg_rce_objt_ctrl_20;	//0xF0175250
	PE_F20_RCE_OBJT_CTRL_21_T            reg_rce_objt_ctrl_21;	//0xF0175254
	PE_F20_RCE_OBJT_CTRL_22_T            reg_rce_objt_ctrl_22;	//0xF0175258
	PE_F20_RCE_OBJT_CTRL_23_T            reg_rce_objt_ctrl_23;	//0xF017525C
	PE_F20_RCE_OBJT_CTRL_24_T            reg_rce_objt_ctrl_24;	//0xF0175260
	PE_F20_RCE_OBJT_CTRL_25_T            reg_rce_objt_ctrl_25;	//0xF0175264
	PE_F20_RCE_OBJT_CTRL_26_T            reg_rce_objt_ctrl_26;	//0xF0175268
	PE_F20_RCE_OBJT_CTRL_27_T            reg_rce_objt_ctrl_27;	//0xF017526C
	PE_F20_RCE_OBJT_CTRL_28_T            reg_rce_objt_ctrl_28;	//0xF0175270
	PE_F20_RCE_OBJT_CTRL_29_T            reg_rce_objt_ctrl_29;	//0xF0175274
	PE_F20_RCE_OBJT_CTRL_30_T            reg_rce_objt_ctrl_30;	//0xF0175278
	PE_F20_RCE_OBJT_CTRL_31_T            reg_rce_objt_ctrl_31;	//0xF017527C
}PE_CHPI_RCO_TBL_F20_T;

typedef struct
{
	PE_F20_RCE_FACE_CTRL_00_T            reg_rce_face_ctrl_00;	//0xF0175280
	PE_F20_RCE_FACE_CTRL_01_T            reg_rce_face_ctrl_01;	//0xF0175284
	PE_F20_RCE_FACE_CTRL_02_T            reg_rce_face_ctrl_02;	//0xF0175288
	PE_F20_RCE_FACE_CTRL_03_T            reg_rce_face_ctrl_03;	//0xF017528C
	PE_F20_RCE_FACE_CTRL_04_T            reg_rce_face_ctrl_04;	//0xF0175290
	PE_F20_RCE_FACE_CTRL_05_T            reg_rce_face_ctrl_05;	//0xF0175294
	PE_F20_RCE_FACE_CTRL_06_T            reg_rce_face_ctrl_06;	//0xF0175298
	PE_F20_RCE_FACE_CTRL_07_T            reg_rce_face_ctrl_07;	//0xF017529C
	PE_F20_RCE_FACE_CTRL_08_T            reg_rce_face_ctrl_08;	//0xF01752A0
	PE_F20_RCE_FACE_CTRL_09_T            reg_rce_face_ctrl_09;	//0xF01752A4
	PE_F20_RCE_FACE_CTRL_10_T            reg_rce_face_ctrl_10;	//0xF01752A8
	PE_F20_RCE_FACE_CTRL_11_T            reg_rce_face_ctrl_11;	//0xF01752AC
	PE_F20_RCE_FACE_CTRL_12_T            reg_rce_face_ctrl_12;	//0xF01752B0
	PE_F20_RCE_FACE_CTRL_13_T            reg_rce_face_ctrl_13;	//0xF01752B4
	PE_F20_RCE_FACE_CTRL_14_T            reg_rce_face_ctrl_14;	//0xF01752B8
	PE_F20_RCE_FACE_CTRL_15_T            reg_rce_face_ctrl_15;	//0xF01752BC
	PE_F20_RCE_FACE_CTRL_16_T            reg_rce_face_ctrl_16;	//0xF01752C0
	PE_F20_RCE_FACE_CTRL_17_T            reg_rce_face_ctrl_17;	//0xF01752C4
	PE_F20_RCE_FACE_CTRL_18_T            reg_rce_face_ctrl_18;	//0xF01752C8
	PE_F20_RCE_FACE_CTRL_19_T            reg_rce_face_ctrl_19;	//0xF01752CC
	PE_F20_RCE_FACE_CTRL_20_T            reg_rce_face_ctrl_20;	//0xF01752D0
	PE_F20_RCE_FACE_CTRL_21_T            reg_rce_face_ctrl_21;	//0xF01752D4
	PE_F20_RCE_FACE_CTRL_22_T            reg_rce_face_ctrl_22;	//0xF01752D8
	PE_F20_RCE_FACE_CTRL_23_T            reg_rce_face_ctrl_23;	//0xF01752DC
	PE_F20_RCE_FACE_CTRL_24_T            reg_rce_face_ctrl_24;	//0xF01752E0
	PE_F20_RCE_FACE_CTRL_25_T            reg_rce_face_ctrl_25;	//0xF01752E4
	PE_F20_RCE_FACE_CTRL_26_T            reg_rce_face_ctrl_26;	//0xF01752E8
	PE_F20_RCE_FACE_CTRL_27_T            reg_rce_face_ctrl_27;	//0xF01752EC
	PE_F20_RCE_FACE_CTRL_28_T            reg_rce_face_ctrl_28;	//0xF01752F0
	PE_F20_RCE_FACE_CTRL_29_T            reg_rce_face_ctrl_29;	//0xF01752F4
	PE_F20_RCE_FACE_CTRL_30_T            reg_rce_face_ctrl_30;	//0xF01752F8
	PE_F20_RCE_FACE_CTRL_31_T            reg_rce_face_ctrl_31;	//0xF01752FC
}PE_CHPI_RCF_TBL_F20_T;

//see PE_DDR_O20_DRC_CUV_T
typedef struct
{
	SINT32 global_apl[4];	///global_apl
	SINT32 local_apl[6];		///local_apl
	SINT32 cuv_gain_w;						///CURV white gain
	SINT32 cuv_gain_b;						///CURV black gain
	SINT32 n1p_trans_curv[6][6];	///n1p_trans_curv
	SINT32 n2p_trans_curv[6][6];	///n1p_trans_curv
	SINT32 n3p_trans_curv[6][6];	///n1p_trans_curv
	SINT32 n4p_trans_curv[6][6];	///n1p_trans_curv
}PE_CHPI_DRC_CUV_F20_T;


#endif
