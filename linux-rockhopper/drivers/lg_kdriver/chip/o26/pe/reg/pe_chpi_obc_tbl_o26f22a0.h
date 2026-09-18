#ifndef _PE_CHPI_OBC_TBL_O26F22A0_H_
#define _PE_CHPI_OBC_TBL_O26F22A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif
 
/*===============OBC====================*/
typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030800 RW 0x08700F00
	UINT32 reg_img_wid                      :13;	//(12:0,RW,0xF00) //horizontal resolution 3840
	UINT32 resvd0                           :3;
	UINT32 reg_img_hei                      :13;	//(28:16,RW,0x870) //vertical resolution   2160
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_HEAD_PSP_CTRL00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030804 RW 0x87F01010
	UINT32 reg_blk_wid                      :6;	//(5:0,RW,0x10) //Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//(13:8,RW,0x10) //Block size       16
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :8;	//(23:16,RW,0xF0) //Number of hblock 240
	UINT32 reg_l5_hei                       :8;	//(31:24,RW,0x87) //Number of vblock 135
	};
	};
}PE_O26F22_OBC_HEAD_PSP_CTRL01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030808 RW 0x00
	UINT32 reg_vs_inv                       :1;	//(0,RW,0x00) //vs inversion
	UINT32 reg_psp_en                       :1;	//(1,RW,0x00) //psp enable : 전체 enable
	UINT32 reg_hist_sel                     :2;	//(3:2,RW,0x00) //histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//(8:4,RW,0x00) //line 경계에서 repeat 시킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//(9,RW,0x00) //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//(14:10,RW,0x00) //frame 경계에서 repeat 시킬 v line 개수
	UINT32 reserved                         :1;	//(15,RW,0x00) //fg memory의 mee off
	UINT32 reg_margin_hei                   :8;	//(23:16,RW,0x00) //edge extraction의 V margin
	UINT32 reg_margin_wid                   :8;	//(31:24,RW,0x00) //edge extraction의 H margin
	};
	};
}PE_O26F22_OBC_HEAD_PSP_CTRL02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303080C RW 0x3F3F0000
	UINT32 y0_point                         :6;	//(5:0,NA,0x00) //control point of Y0
	UINT32 resvd0                           :2;
	UINT32 x0_point                         :6;	//(13:8,NA,0x00) //control point of X0
	UINT32 resvd1                           :2;
	UINT32 y1_point                         :6;	//(21:16,NA,0x3F) //control point of Y1
	UINT32 resvd2                           :2;
	UINT32 x1_point                         :6;	//(29:24,NA,0x3F) //control point of X1
	UINT32 resvd3                           :2;
	};
	};
}PE_O26F22_OBC_HEAD_L5_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030810 RW 0x3F3F3F3F
	UINT32 y2_point                         :6;	//(5:0,NA,0x3F) //control point of Y2
	UINT32 resvd0                           :2;
	UINT32 x2_point                         :6;	//(13:8,NA,0x3F) //control point of X2
	UINT32 resvd1                           :2;
	UINT32 y3_point                         :6;	//(21:16,NA,0x3F) //control point of Y3
	UINT32 resvd2                           :2;
	UINT32 x3_point                         :6;	//(29:24,NA,0x3F) //control point of X3
	UINT32 resvd3                           :2;
	};
	};
}PE_O26F22_OBC_HEAD_L5_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030848 RW 0x00000000
	UINT32 prefetch_init                    :2;	//(1:0,RW,0x0) //0 : vsync fal	1 : vactv fal	2 : refine_init_num
	UINT32 queue_init                       :2;	//(3:2,RW,0x0) //0 : vsync fal	1 : vactv fal	2 : fifo_init_num
	UINT32 reserved                         :2;	//(4,RW,0x0) //PE_O26F22_debug_test
	UINT32 resvd                            :2;
	UINT32 refine_init_num                  :12;	//(19:8,RW,0x0) //refine_init_num * 256
	UINT32 fifo_init_num                    :12;	//(31:20,RW,0x0) //fifo_init_num * 256
	};
	};
}PE_O26F22_OBC_HEAD_DISPLAY_DEBUG_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030870 RW 0x00000080
	UINT32 reg_refine_diff_luma_a           :8;	//(7:0,NA,0x80) //
	UINT32 reg_refine_diff_chroma_b         :8;	//(15:8,NA,0x00) //
	UINT32 debug_map                        :2;	//(17:16,NA,0x00) //0 : obj_refine	1 : sample_yy	2 : sample_cb	3 : sample_cr
	UINT32 debug_map_en                     :1;	//(18,NA,0x00) //0 : debug_map off	1 : debug_map on
	UINT32 sel_picinit                      :1;	//(19,NA,0x00) //0 : vactive falling	1 : vsync falling
	UINT32 reg_reset_cnt                    :12;	//(31:20,NA,0x00) //reset cnt 12bit(0~4095)
	};
	};
}PE_O26F22_OBC_HEAD_REFINE_CTRL0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030874 RW 0x20120400
	UINT32 reg_refine_weight_lux_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_lux_x1         :8;	//(15:8,NA,0x04) //
	UINT32 reg_refine_weight_lux_x2         :8;	//(23:16,NA,0x12) //
	UINT32 reg_refine_weight_lux_x3         :8;	//(31:24,NA,0x20) //
	};
	};
}PE_O26F22_OBC_HEAD_REFINE_CTRL1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030878 RW 0x021034FF
	UINT32 reg_refine_weight_lux_y0         :8;	//(7:0,NA,0xFF) //
	UINT32 reg_refine_weight_lux_y1         :8;	//(15:8,NA,0x34) //
	UINT32 reg_refine_weight_lux_y2         :8;	//(23:16,NA,0x10) //
	UINT32 reg_refine_weight_lux_y3         :8;	//(31:24,NA,0x02) //
	};
	};
}PE_O26F22_OBC_HEAD_REFINE_CTRL2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303087C RW 0xFF804000
	UINT32 reg_refine_post_lux_x0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_x1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_x2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_x3           :8;	//(31:24,NA,0xFF) //
	};
	};
}PE_O26F22_OBC_HEAD_REFINE_CTRL3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030880 RW 0xFF804000
	UINT32 reg_refine_post_lux_y0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_y1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_y2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_y3           :8;	//(31:24,NA,0xFF) //
	};
	};
}PE_O26F22_OBC_HEAD_REFINE_CTRL4_T;



typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030600 RW 0x08700F00
	UINT32 reg_img_wid                      :13;	//(12:0,RW,0xF00) //horizontal resolution 3840
	UINT32 resvd0                           :3;
	UINT32 reg_img_hei                      :13;	//(28:16,RW,0x870) //vertical resolution   2160
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_PSP_CTRL00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030604 RW 0x87F01010
	UINT32 reg_blk_wid                      :6;	//(5:0,RW,0x10) //Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//(13:8,RW,0x10) //Block size       16
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :8;	//(23:16,RW,0xF0) //Number of hblock 240
	UINT32 reg_l5_hei                       :8;	//(31:24,RW,0x87) //Number of vblock 135
	};
	};
}PE_O26F22_OBC_BODY_PSP_CTRL01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030608 RW 0x00
	UINT32 reg_vs_inv                       :1;	//(0,RW,0x00) //vs inversion
	UINT32 reg_psp_en                       :1;	//(1,RW,0x00) //psp enable : 전체 enable
	UINT32 reg_hist_sel                     :2;	//(3:2,RW,0x00) //histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//(8:4,RW,0x00) //line 경계에서 repeat 시킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//(9,RW,0x00) //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//(14:10,RW,0x00) //frame 경계에서 repeat 시킬 v line 개수
	UINT32 reserved                         :1;	//(15,RW,0x00) //fg memory의 mee off
	UINT32 reg_margin_hei                   :8;	//(23:16,RW,0x00) //edge extraction의 V margin
	UINT32 reg_margin_wid                   :8;	//(31:24,RW,0x00) //edge extraction의 H margin
	};
	};
}PE_O26F22_OBC_BODY_PSP_CTRL02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303060C RW 0x3F3F0000
	UINT32 y0_point                         :6;	//(5:0,NA,0x00) //control point of Y0
	UINT32 resvd0                           :2;
	UINT32 x0_point                         :6;	//(13:8,NA,0x00) //control point of X0
	UINT32 resvd1                           :2;
	UINT32 y1_point                         :6;	//(21:16,NA,0x3F) //control point of Y1
	UINT32 resvd2                           :2;
	UINT32 x1_point                         :6;	//(29:24,NA,0x3F) //control point of X1
	UINT32 resvd3                           :2;
	};
	};
}PE_O26F22_OBC_BODY_L5_GAIN_LUT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030610 RW 0x3F3F3F3F
	UINT32 y2_point                         :6;	//(5:0,NA,0x3F) //control point of Y2
	UINT32 resvd0                           :2;
	UINT32 x2_point                         :6;	//(13:8,NA,0x3F) //control point of X2
	UINT32 resvd1                           :2;
	UINT32 y3_point                         :6;	//(21:16,NA,0x3F) //control point of Y3
	UINT32 resvd2                           :2;
	UINT32 x3_point                         :6;	//(29:24,NA,0x3F) //control point of X3
	UINT32 resvd3                           :2;
	};
	};
}PE_O26F22_OBC_BODY_L5_GAIN_LUT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030648 RW 0x00000000
	UINT32 prefetch_init                    :2;	//(1:0,RW,0x0) //0 : vsync fal	1 : vactv fal	2 : refine_init_num
	UINT32 queue_init                       :2;	//(3:2,RW,0x0) //0 : vsync fal	1 : vactv fal	2 : fifo_init_num
	UINT32 reserved                         :2;	//(4,RW,0x0) //PE_O26F22_debug_test
	UINT32 resvd                            :2;
	UINT32 refine_init_num                  :12;	//(19:8,RW,0x0) //refine_init_num * 256
	UINT32 fifo_init_num                    :12;	//(31:20,RW,0x0) //fifo_init_num * 256
	};
	};
}PE_O26F22_OBC_BODY_DISPLAY_DEBUG_MAP_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030670 RW 0x00000080
	UINT32 reg_refine_diff_luma_a           :8;	//(7:0,NA,0x80) //
	UINT32 reg_refine_diff_chroma_b         :8;	//(15:8,NA,0x00) //
	UINT32 debug_map                        :2;	//(17:16,NA,0x00) //0 : obj_refine	1 : sample_yy	2 : sample_cb	3 : sample_cr
	UINT32 debug_map_en                     :1;	//(18,NA,0x00) //0 : debug_map off	1 : debug_map on
	UINT32 sel_picinit                      :1;	//(19,NA,0x00) //0 : vactive falling	1 : vsync falling
	UINT32 reg_reset_cnt                    :12;	//(31:20,NA,0x00) //reset cnt 12bit(0~4095)
	};
	};
}PE_O26F22_OBC_BODY_REFINE_CTRL0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030674 RW 0x20120400
	UINT32 reg_refine_weight_lux_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_lux_x1         :8;	//(15:8,NA,0x04) //
	UINT32 reg_refine_weight_lux_x2         :8;	//(23:16,NA,0x12) //
	UINT32 reg_refine_weight_lux_x3         :8;	//(31:24,NA,0x20) //
	};
	};
}PE_O26F22_OBC_BODY_REFINE_CTRL1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030678 RW 0x021034FF
	UINT32 reg_refine_weight_lux_y0         :8;	//(7:0,NA,0xFF) //
	UINT32 reg_refine_weight_lux_y1         :8;	//(15:8,NA,0x34) //
	UINT32 reg_refine_weight_lux_y2         :8;	//(23:16,NA,0x10) //
	UINT32 reg_refine_weight_lux_y3         :8;	//(31:24,NA,0x02) //
	};
	};
}PE_O26F22_OBC_BODY_REFINE_CTRL2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303067C RW 0xFF804000
	UINT32 reg_refine_post_lux_x0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_x1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_x2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_x3           :8;	//(31:24,NA,0xFF) //
	};
	};
}PE_O26F22_OBC_BODY_REFINE_CTRL3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030680 RW 0xFF804000
	UINT32 reg_refine_post_lux_y0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_y1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_y2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_y3           :8;	//(31:24,NA,0xFF) //
	};
	};
}PE_O26F22_OBC_BODY_REFINE_CTRL4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030690 RW 0x10E0_03C0
	UINT32 reg_rgn_gain_width               :13;	//(12:0,NA,960) //processing width (default : 3840/2 = 1920)
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_height              :13;	//(28:16,NA,4320) //processing height (default : 1080)
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030694 RW 0x0032_0096
	UINT32 reg_rgn_gain_position_x2         :13;	//(12:0,NA,150) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x1         :13;	//(28:16,NA,50) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030698 RW 0x013F_01AA
	UINT32 reg_rgn_gain_position_x4         :13;	//(12:0,NA,426) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x3         :13;	//(28:16,NA,319) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303069C RW 0x0214_028C
	UINT32 reg_rgn_gain_position_x6         :13;	//(12:0,NA,652) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x5         :13;	//(28:16,NA,532) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306A0 RW 0x0304_036F
	UINT32 reg_rgn_gain_position_x8         :13;	//(12:0,NA,879) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x7         :13;	//(28:16,NA,772) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306A4 RW 0x012C_0258
	UINT32 reg_rgn_gain_position_y2         :13;	//(12:0,NA,600) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y1         :13;	//(28:16,NA,300) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306A8 RW 0x0738_0A28
	UINT32 reg_rgn_gain_position_y4         :13;	//(12:0,NA,2600) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y3         :13;	//(28:16,NA,1948) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306AC RW 0x0E10_0FA0
	UINT32 reg_rgn_gain_position_y6         :13;	//(12:0,NA,4000) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y5         :13;	//(28:16,NA,3600) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306B0 RW 0x6464_6464
	UINT32 reg_rgn_gain_41                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_31                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_21                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_11                  :8;	//(31:24,NA,100) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306B4 RW 0x6464_6464
	UINT32 reg_rgn_gain_81                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_71                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_61                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_51                  :8;	//(31:24,NA,100) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306B8 RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_42                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_32                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_22                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_12                  :8;	//(31:24,NA,110) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306BC RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_82                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_72                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_62                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_52                  :8;	//(31:24,NA,110) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306C0 RW 0x8080_8080
	UINT32 reg_rgn_gain_43                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_33                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_23                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_13                  :8;	//(31:24,NA,128) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306C4 RW 0x8080_8080
	UINT32 reg_rgn_gain_83                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_73                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_63                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_53                  :8;	//(31:24,NA,128) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306C8 RW 0x8080_8080
	UINT32 reg_rgn_gain_44                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_34                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_24                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_14                  :8;	//(31:24,NA,128) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306CC RW 0x8080_8080
	UINT32 reg_rgn_gain_84                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_74                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_64                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_54                  :8;	//(31:24,NA,128) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306D0 RW 0x6464_6464
	UINT32 reg_rgn_gain_45                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_35                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_25                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_15                  :8;	//(31:24,NA,100) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306D4 RW 0x6464_6464
	UINT32 reg_rgn_gain_85                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_75                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_65                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_55                  :8;	//(31:24,NA,100) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306D8 RW 0x5050_5050
	UINT32 reg_rgn_gain_46                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_36                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_26                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_16                  :8;	//(31:24,NA,80) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306DC RW 0x5050_5050
	UINT32 reg_rgn_gain_86                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_76                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_66                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_56                  :8;	//(31:24,NA,80) //
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306E0 RW 0x0000_8001
	UINT32 reg_rgn_gain_en                  :1;	//(0:0,NA,1) //
	UINT32 resvd0                           :7;
	UINT32 reg_rgn_gain_bnd_gain            :8;	//(15:8,NA,128) //
	UINT32 resvd1                           :16;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306E4 RW 0x0000_03BF
	UINT32 reg_rgn_gain_bnd_x1              :13;	//(12:0,NA,959) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_x0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30306E8 RW 0x0000_10DF
	UINT32 reg_rgn_gain_bnd_y1              :13;	//(12:0,NA,4319) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_y0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
	};
}PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T;

/*===============OBE====================*/

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030200 RW 0x8310_0000
	UINT32 resvd0                           :16;
	UINT32 reg_debug_mode                   :4;	//(19:16,NA,0x0) //0: normal	1: RCE_P ( R,G,B )	2: RCE_L ( R,G,B )	3: head_gain (W = R&G&B )	4: body_gain (W = R&G&B ) 	5: txtr_bain (W = R&G&B ) 	6: FACE+BODY (R = head_gain , G = body gain, B = 0)	7: FACE+BODY+TXTR (R = head_gain , G = body gain, B = txtr_gain)	8:face_body_blend (W = R&G&B )	9:final_blend(W = R&G&B )
	UINT32 reg_out_winmode_dly_sel          :2;	//(21:20,NA,0x1) //0: 43T (DTM 23T)	1: 21T (DTM 1T)	2: 22T (DTM 2T)
	UINT32 resvd1                           :2;
	UINT32 reg_ocsc_en                      :1;	//(24,NA,0x1) //
	UINT32 reg_icsc_en                      :1;	//(25,NA,0x1) //
	UINT32 resvd2                           :5;
	UINT32 reg_obe_en                       :1;	//(31,NA,0x0) //
	};
	};
}PE_O26F22_OBE_CTRL_000_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030204 RW 0x1E00_10E0
	UINT32 reg_heigt                        :16;	//(15:0,NA,0x10E0) //4320
	UINT32 reg_width                        :16;	//(31:16,NA,0x1E00) //7680
	};
	};
}PE_O26F22_OBE_CTRL_001_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030208 RW 0x0000_0000
	UINT32 reg_bg_body_hist_th              :8;	//(7:0,NA,0x00) //
	UINT32 reg_bg_head_hist_th              :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_hist_th                 :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_hist_th                 :8;	//(31:24,NA,0x00) //
	};
	};
}PE_O26F22_OBE_CTRL_002_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303020C RW 0x0000_0000
	UINT32 resvd                            :16;
	UINT32 reg_bg_txtr_hist_th              :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_hist_th                 :8;	//(31:24,NA,0x00) //
	};
	};
}PE_O26F22_OBE_CTRL_003_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030210 RW 0x0000_0000
	UINT32 reg_sat_prsv_ratio               :8;	//(7:0,NA,0x00) //
	UINT32 reg_hue_prsv_ratio               :8;	//(15:8,NA,0x00) //
	UINT32 reg_sat_prsv_en                  :1;	//(16,NA,0x0) //
	UINT32 reg_hue_prsv_en                  :1;	//(17,NA,0x0) //
	UINT32 resvd                            :13;
	UINT32 reg_hsp_en                       :1;	//(31,NA,0x0) //
	};
	};
}PE_O26F22_OBE_CTRL_004_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030214 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,NA,0x0000_0000) //
	};
	};
}PE_O26F22_OBE_CTRL_005_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030264 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_txtr_master_gain             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x00) //
	};
	};
}PE_O26F22_OBE_CTRL_025_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030268 RW 0x0080_0080
	UINT32 reg_final_blend_lut_y2           :8;	//(7:0,NA,0x80) //
	UINT32 reg_final_blend_lut_x2           :8;	//(15:8,NA,0x00) //
	UINT32 reg_final_blend_lut_y3           :8;	//(23:16,NA,0x80) //
	UINT32 reg_final_blend_lut_x3           :8;	//(31:24,NA,0x00) //for RCE_P, RCE_L blending
	};
	};
}PE_O26F22_OBE_CTRL_026_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303026C RW 0x0080_0080
	UINT32 reg_final_blend_lut_y0           :8;	//(7:0,NA,0x80) //
	UINT32 reg_final_blend_lut_x0           :8;	//(15:8,NA,0x00) //
	UINT32 reg_final_blend_lut_y1           :8;	//(23:16,NA,0x80) //
	UINT32 reg_final_blend_lut_x1           :8;	//(31:24,NA,0x00) //for RCE_P, RCE_L blending
	};
	};
}PE_O26F22_OBE_CTRL_027_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030270 RW 0x0000_0000
	UINT32 reg_head_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_028_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030274 RW 0x0000_0000
	UINT32 reg_head_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_029_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030278 RW 0x0000_0000
	UINT32 reg_head_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_030_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303027C RW 0x0000_0000
	UINT32 reg_head_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_031_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030280 RW 0x0000_0000
	UINT32 reg_head_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_032_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030284 RW 0x0000_0000
	UINT32 reg_head_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_033_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030288 RW 0x0000_0000
	UINT32 reg_head_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_034_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303028C RW 0x0000_0000
	UINT32 reg_head_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_035_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030290 RW 0x0000_0000
	UINT32 reg_head_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_036_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030294 RW 0x0000_0000
	UINT32 reg_head_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_037_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030298 RW 0x0000_0000
	UINT32 reg_head_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_038_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303029C RW 0x0000_0000
	UINT32 reg_head_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_039_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302A0 RW 0x0000_0000
	UINT32 reg_head_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_040_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302A4 RW 0x0000_0000
	UINT32 reg_head_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_041_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302A8 RW 0x0000_0000
	UINT32 reg_head_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_042_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302AC RW 0x0000_0000
	UINT32 reg_head_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_043_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302B0 RW 0x0000_0000
	UINT32 reg_head_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_044_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302B4 RW 0x0000_0000
	UINT32 reg_head_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_045_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302B8 RW 0x0000_0000
	UINT32 reg_body_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_046_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302BC RW 0x0000_0000
	UINT32 reg_body_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_047_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302C0 RW 0x0000_0000
	UINT32 reg_body_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_048_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302C4 RW 0x0000_0000
	UINT32 reg_body_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_049_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302C8 RW 0x0000_0000
	UINT32 reg_body_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_050_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302CC RW 0x0000_0000
	UINT32 reg_body_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_051_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302D0 RW 0x0000_0000
	UINT32 reg_body_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_052_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302D4 RW 0x0000_0000
	UINT32 reg_body_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_053_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302D8 RW 0x0000_0000
	UINT32 reg_body_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_054_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302DC RW 0x0000_0000
	UINT32 reg_body_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_055_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302E0 RW 0x0000_0000
	UINT32 reg_body_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_056_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302E4 RW 0x0000_0000
	UINT32 reg_body_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_057_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302E8 RW 0x0000_0000
	UINT32 reg_body_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_058_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302EC RW 0x0000_0000
	UINT32 reg_body_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_059_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302F0 RW 0x0000_0000
	UINT32 reg_body_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_060_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302F4 RW 0x0000_0000
	UINT32 reg_body_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_061_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302F8 RW 0x0000_0000
	UINT32 reg_body_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_062_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30302FC RW 0x0000_0000
	UINT32 reg_body_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_063_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030348 RW 0x0000_0000
	UINT32 reg_head_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_gain_lut_x3             :8;	//(31:24,NA,0x00) //o26/f22 4pt
	};
	};
}PE_O26F22_OBE_CTRL_082_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303034C RW 0x0000_0000
	UINT32 reg_head_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_gain_lut_x1             :8;	//(31:24,NA,0x00) //o26/f22 4pt
	};
	};
}PE_O26F22_OBE_CTRL_083_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030350 RW 0x0000_0000
	UINT32 reg_body_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_gain_lut_x3             :8;	//(31:24,NA,0x00) //o26/f22 4pt
	};
	};
}PE_O26F22_OBE_CTRL_084_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030354 RW 0x0000_0000
	UINT32 reg_body_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_gain_lut_x1             :8;	//(31:24,NA,0x00) //o26/f22 4pt
	};
	};
}PE_O26F22_OBE_CTRL_085_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030358 RW 0x0000_0000
	UINT32 reg_body_head_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_head_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_head_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_head_lut_x3             :8;	//(31:24,NA,0x00) //body-head
	};
	};
}PE_O26F22_OBE_CTRL_086_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303035C RW 0x0000_0000
	UINT32 reg_body_head_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_head_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_head_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_head_lut_x1             :8;	//(31:24,NA,0x00) //
	};
	};
}PE_O26F22_OBE_CTRL_087_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030360 RW 0x0000_0000
	UINT32 reg_head_body_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_body_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_body_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_body_lut_x3             :8;	//(31:24,NA,0x00) //head-body
	};
	};
}PE_O26F22_OBE_CTRL_088_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030364 RW 0x0000_0000
	UINT32 reg_head_body_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_body_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_body_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_body_lut_x1             :8;	//(31:24,NA,0x00) //
	};
	};
}PE_O26F22_OBE_CTRL_089_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030368 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_090_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303036C RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_091_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030370 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_092_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030374 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_093_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030378 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_094_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303037C RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_095_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030380 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_096_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030384 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_097_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030388 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_098_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303038C RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_099_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030390 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_100_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030394 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_101_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030398 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_102_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303039C RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y1                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x1                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_103_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30303A0 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y2                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x2                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_104_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30303A4 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y3                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x3                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_105_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30303A8 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y4                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x4                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_106_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30303AC RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y5                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x5                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_OBE_CTRL_107_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30303F8 RW 0x0000_0000
	UINT32 reg_txtr_gain_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_txtr_gain_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x3             :8;	//(31:24,NA,0x00) //o26/f22 4pt
	};
	};
}PE_O26F22_OBE_CTRL_126_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30303FC RW 0x0000_0000
	UINT32 reg_txtr_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_txtr_gain_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x1             :8;	//(31:24,NA,0x00) //o26/f22 4pt
	};
	};
}PE_O26F22_OBE_CTRL_127_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030420 RW 0x0000_0000
	UINT32 reg_hist_body_gain_lut_y2        :8;	//(7:0,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x2        :8;	//(15:8,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_y3        :8;	//(23:16,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x3        :8;	//(31:24,NA,0x00) //o26/f22 4pt for hist
	};
	};
}PE_O26F22_OBE_CTRL_136_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030424 RW 0x0000_0000
	UINT32 reg_hist_body_gain_lut_y0        :8;	//(7:0,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x0        :8;	//(15:8,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_y1        :8;	//(23:16,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x1        :8;	//(31:24,NA,0x00) //o26/f22 4pt for hist
	};
	};
}PE_O26F22_OBE_CTRL_137_T;

/*===============AMG====================*/
typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D20 RW 0x0242_0242
	UINT32 reg_hist_coef0_hb                :3;	//(2:0,NA,2) //Histogram coefficient, 0 (HEAD/BODY)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_coef1_hb                :3;	//(6:4,NA,4) //Histogram coefficient, 1 (HEAD/BODY)
	UINT32 resvd1                           :1;
	UINT32 reg_hist_coef2_hb                :3;	//(10:8,NA,2) //Histogram coefficient, 2 (HEAD/BODY)
	UINT32 resvd2                           :5;
	UINT32 reg_hist_coef0_depth             :3;	//(18:16,NA,2) //Histogram coefficient, 0 (Depth)
	UINT32 resvd3                           :1;
	UINT32 reg_hist_coef1_depth             :3;	//(22:20,NA,4) //Histogram coefficient, 1 (Depth)
	UINT32 resvd4                           :1;
	UINT32 reg_hist_coef2_depth             :3;	//(26:24,NA,2) //Histogram coefficient, 2 (Depth)
	UINT32 resvd5                           :5;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D24 RW 0x0000_0000
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection	0: Y	1: Cb	2: Cr	3: Depth
	UINT32 resvd                            :30;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D28 RO 0x0000_0000
	UINT32 reg_read_hist_00_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 0)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_00_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 0)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D2C RO 0x0000_0000
	UINT32 reg_read_hist_01_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 1)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_01_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 1)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D30 RO 0x0000_0000
	UINT32 reg_read_hist_02_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 2)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_02_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 2)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D34 RO 0x0000_0000
	UINT32 reg_read_hist_03_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 3)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_03_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 3)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D38 RO 0x0000_0000
	UINT32 reg_read_hist_04_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 4)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_04_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 4)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D3C RO 0x0000_0000
	UINT32 reg_read_hist_05_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 5)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_05_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 5)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D40 RO 0x0000_0000
	UINT32 reg_read_hist_06_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 6)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_06_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 6)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D44 RO 0x0000_0000
	UINT32 reg_read_hist_07_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 7)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_07_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 7)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D48 RO 0x0000_0000
	UINT32 reg_read_hist_08_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 8)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_08_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 8)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D4C RO 0x0000_0000
	UINT32 reg_read_hist_09_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 9)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_09_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 9)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D50 RO 0x0000_0000
	UINT32 reg_read_hist_10_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 10)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_10_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 10)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D54 RO 0x0000_0000
	UINT32 reg_read_hist_11_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 11)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_11_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 11)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D58 RO 0x0000_0000
	UINT32 reg_read_hist_12_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 12)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_12_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 12)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D5C RO 0x0000_0000
	UINT32 reg_read_hist_13_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 13)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_13_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 13)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D60 RO 0x0000_0000
	UINT32 reg_read_hist_14_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 14)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_14_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 14)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D64 RO 0x0000_0000
	UINT32 reg_read_hist_15_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 15)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_15_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 15)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D68 RO 0x0000_0000
	UINT32 reg_read_hist_16_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 16)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_16_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 16)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D6C RO 0x0000_0000
	UINT32 reg_read_hist_17_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 17)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_17_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 17)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D70 RO 0x0000_0000
	UINT32 reg_read_hist_18_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 18)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_18_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 18)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D74 RO 0x0000_0000
	UINT32 reg_read_hist_19_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 19)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_19_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 19)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D78 RO 0x0000_0000
	UINT32 reg_read_hist_20_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 20)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_20_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 20)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D7C RO 0x0000_0000
	UINT32 reg_read_hist_21_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 21)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_21_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 21)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_21_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D80 RO 0x0000_0000
	UINT32 reg_read_hist_22_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 22)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_22_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 22)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_22_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D84 RO 0x0000_0000
	UINT32 reg_read_hist_23_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 23)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_23_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 23)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_23_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D88 RO 0x0000_0000
	UINT32 reg_read_hist_24_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 24)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_24_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 24)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_24_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D8C RO 0x0000_0000
	UINT32 reg_read_hist_25_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 25)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_25_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 25)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_25_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D90 RO 0x0000_0000
	UINT32 reg_read_hist_26_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 26)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_26_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 26)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_26_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D94 RO 0x0000_0000
	UINT32 reg_read_hist_27_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 27)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_27_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 27)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_27_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D98 RO 0x0000_0000
	UINT32 reg_read_hist_28_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 28)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_28_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 28)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_28_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011D9C RO 0x0000_0000
	UINT32 reg_read_hist_29_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 29)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_29_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 29)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_29_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DA0 RO 0x0000_0000
	UINT32 reg_read_hist_30_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 30)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_30_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 30)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_30_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DA4 RO 0x0000_0000
	UINT32 reg_read_hist_31_bg              :15;	//(14:0,NA,0) //Histogram read data (BG, bin 31)
	UINT32 resvd0                           :1;
	UINT32 reg_read_hist_31_fg              :15;	//(30:16,NA,0) //Histogram read data (FG, bin 31)
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_AMG0_HEAD_HISTOGRAM_STAT_31_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DB0 RW 0x0000_0101
	UINT32 reg_objt_map_en                  :1;	//(0:0,NA,1) //Object map enable
	UINT32 resvd0                           :3;
	UINT32 reg_dbg_map_ctrl                 :3;	//(6:4,NA,0) //Debug map selection	0: Probability map	1: Ellipse gain map	2: Probability map (FG)	3: Probability map (BG)	4: Probability map (diff)	5: Box map	6: Pixel data (Y)
	UINT32 resvd1                           :1;
	UINT32 reg_fg_mul_ellipse_en            :1;	//(8:8,NA,1) //Reflect ellipse gain enable
	UINT32 resvd2                           :3;
	UINT32 reg_out_mux_sel                  :2;	//(13:12,NA,0) //Object map output mux selection	0: HEAD/BODY	1: Blending	2: Depth only	3: Adding
	UINT32 resvd3                           :18;
	};
	};
}PE_O26F22_AMG0_HEAD_OBJT_MAP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DB4 RW 0x0055_0055
	UINT32 reg_fg_prob_factor               :7;	//(6:0,NA,85) //FG probability map factor
	UINT32 resvd0                           :9;
	UINT32 reg_bg_prob_factor               :7;	//(22:16,NA,85) //BG probability map factor
	UINT32 resvd1                           :9;
	};
	};
}PE_O26F22_AMG0_HEAD_OBJT_MAP_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DB8 RW 0x00C4_00C4
	UINT32 reg_fg_diff_mul                  :10;	//(9:0,NA,196) //FG factor for probability diff map (6.4bit)
	UINT32 resvd0                           :6;
	UINT32 reg_bg_diff_mul                  :10;	//(25:16,NA,196) //BG factor for probability diff map (6.4bit)
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG0_HEAD_OBJT_MAP_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DBC RW 0x0004_0004
	UINT32 reg_e_offset                     :8;	//(7:0,NA,4) //Ellipse gain offset
	UINT32 resvd0                           :8;
	UINT32 reg_p_offset                     :8;	//(23:16,NA,4) //Probability diff map offset
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG0_HEAD_OBJT_MAP_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DC0 RW 0x0000_0000
	UINT32 reg_box_fg_cand_en               :1;	//(0:0,NA,0) //FG candidate box set enable
	UINT32 resvd0                           :3;
	UINT32 reg_box0_add_set1_en             :1;	//(4:4,NA,0) //Additional box0 set1 enable
	UINT32 reg_box1_add_set1_en             :1;	//(5:5,NA,0) //Additional box1 set1 enable
	UINT32 reg_box2_add_set1_en             :1;	//(6:6,NA,0) //Additional box2 set1 enable
	UINT32 reg_box3_add_set1_en             :1;	//(7:7,NA,0) //Additional box3 set1 enable
	UINT32 reg_box0_add_set2_en             :1;	//(8:8,NA,0) //Additional box0 set2 enable
	UINT32 reg_box1_add_set2_en             :1;	//(9:9,NA,0) //Additional box1 set2 enable
	UINT32 reg_box2_add_set2_en             :1;	//(10:10,NA,0) //Additional box2 set2 enable
	UINT32 reg_box3_add_set2_en             :1;	//(11:11,NA,0) //Additional box3 set2 enable
	UINT32 reg_box0_opt_en                  :1;	//(12:12,NA,0) //Optional box0 set enable
	UINT32 reg_box1_opt_en                  :1;	//(13:13,NA,0) //Optional box1 set enable
	UINT32 reg_box2_opt_en                  :1;	//(14:14,NA,0) //Optional box2 set enable
	UINT32 reg_box3_opt_en                  :1;	//(15:15,NA,0) //Optional box3 set enable
	UINT32 reg_additional_box_en            :1;	//(16:16,NA,0) //Additional box enable	- 0: disable (default, replaced to optional box enable)	- 1: enable
	UINT32 resvd1                           :15;
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DC4 RW 0x0000_0000
	UINT32 reg_box_fg_cand_w1               :8;	//(7:0,NA,0) //Box (FG candidate) position, w, start
	UINT32 reg_box_fg_cand_w2               :8;	//(15:8,NA,0) //Box (FG candidate) position, w, end
	UINT32 reg_box_fg_cand_h1               :8;	//(23:16,NA,0) //Box (FG candidate) position, h, start
	UINT32 reg_box_fg_cand_h2               :8;	//(31:24,NA,0) //Box (FG candidate) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DC8 RW 0x0000_0000
	UINT32 reg_box0_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 1) position, w, start
	UINT32 reg_box0_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 1) position, w, end
	UINT32 reg_box0_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 1) position, h, start
	UINT32 reg_box0_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 1) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DCC RW 0x0000_0000
	UINT32 reg_box1_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 1) position, w, start
	UINT32 reg_box1_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 1) position, w, end
	UINT32 reg_box1_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 1) position, h, start
	UINT32 reg_box1_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 1) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DD0 RW 0x0000_0000
	UINT32 reg_box2_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 1) position, w, start
	UINT32 reg_box2_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 1) position, w, end
	UINT32 reg_box2_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 1) position, h, start
	UINT32 reg_box2_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 1) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DD4 RW 0x0000_0000
	UINT32 reg_box3_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 1) position, w, start
	UINT32 reg_box3_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 1) position, w, end
	UINT32 reg_box3_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 1) position, h, start
	UINT32 reg_box3_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 1) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DD8 RW 0x0000_0000
	UINT32 reg_box0_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 2) position, w, start
	UINT32 reg_box0_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 2) position, w, end
	UINT32 reg_box0_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 2) position, h, start
	UINT32 reg_box0_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 2) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DDC RW 0x0000_0000
	UINT32 reg_box1_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 2) position, w, start
	UINT32 reg_box1_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 2) position, w, end
	UINT32 reg_box1_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 2) position, h, start
	UINT32 reg_box1_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 2) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DE0 RW 0x0000_0000
	UINT32 reg_box2_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 2) position, w, start
	UINT32 reg_box2_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 2) position, w, end
	UINT32 reg_box2_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 2) position, h, start
	UINT32 reg_box2_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 2) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DE4 RW 0x0000_0000
	UINT32 reg_box3_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 2) position, w, start
	UINT32 reg_box3_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 2) position, w, end
	UINT32 reg_box3_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 2) position, h, start
	UINT32 reg_box3_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 2) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DE8 RW 0x0000_0000
	UINT32 reg_box0_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 0) position, w, start
	UINT32 reg_box0_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 0) position, w, end
	UINT32 reg_box0_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 0) position, h, start
	UINT32 reg_box0_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 0) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DEC RW 0x0000_0000
	UINT32 reg_box1_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 1) position, w, start
	UINT32 reg_box1_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 1) position, w, end
	UINT32 reg_box1_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 1) position, h, start
	UINT32 reg_box1_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 1) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DF0 RW 0x0000_0000
	UINT32 reg_box2_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 2) position, w, start
	UINT32 reg_box2_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 2) position, w, end
	UINT32 reg_box2_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 2) position, h, start
	UINT32 reg_box2_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 2) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011DF4 RW 0x0000_0000
	UINT32 reg_box3_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 3) position, w, start
	UINT32 reg_box3_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 3) position, w, end
	UINT32 reg_box3_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 3) position, h, start
	UINT32 reg_box3_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 3) position, h, end
	};
	};
}PE_O26F22_AMG0_HEAD_BOX_SET_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E00 RW 0x0000_0000
	UINT32 reg_fg_cand_e_mul_a              :9;	//(8:0,NA,0) //Ellipse (FG candidate) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_fg_cand_e_mul_b              :9;	//(24:16,NA,0) //Ellipse (FG candidate) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_fg_cand_ellipse_en           :1;	//(31:31,NA,0) //Ellipse (FG candidate) gain gen enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E04 RW 0x0000_0000
	UINT32 reg_fg_cand_ellipse_master       :8;	//(7:0,NA,0) //Ellipse (FG candidate) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_fg_cand_ellipse_offset       :8;	//(23:16,NA,0) //Ellipse (FG candidate) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E08 RW 0x002A_0026
	UINT32 reg_opt0_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 0) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 0) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 0) gain gen enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E0C RW 0x0040_00C0
	UINT32 reg_opt0_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 0) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt0_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 0) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E10 RW 0x00DE_0080
	UINT32 reg_opt0_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 0) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_sin_theta               :9;	//(24:16,NA,222) //Ellipse (optional box 0) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 0) rotation enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E14 RW 0x0000_0000
	UINT32 reg_opt0_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 0) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 0) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 0) manual box center position enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E18 RW 0x002A_0026
	UINT32 reg_opt1_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 1) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 1) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 1) gain gen enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E1C RW 0x0040_00C0
	UINT32 reg_opt1_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 1) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt1_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 1) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E20 RW 0x0122_0080
	UINT32 reg_opt1_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 1) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_sin_theta               :9;	//(24:16,NA,-222) //Ellipse (optional box 1) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 1) rotation enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E24 RW 0x0000_0000
	UINT32 reg_opt1_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 1) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 1) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 1) manual box center position enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E28 RW 0x002A_0026
	UINT32 reg_opt2_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 2) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 2) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 2) gain gen enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E2C RW 0x0040_00C0
	UINT32 reg_opt2_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 2) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt2_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 2) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E30 RW 0x00B5_00B5
	UINT32 reg_opt2_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 2) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_sin_theta               :9;	//(24:16,NA,181) //Ellipse (optional box 2) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 2) rotation enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E34 RW 0x0000_0000
	UINT32 reg_opt2_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 2) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 2) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 2) manual box center position enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E38 RW 0x002A_0026
	UINT32 reg_opt3_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 3) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 3) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 3) gain gen enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E3C RW 0x0040_00C0
	UINT32 reg_opt3_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 3) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt3_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 3) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E40 RW 0x014B_00B5
	UINT32 reg_opt3_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 3) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_sin_theta               :9;	//(24:16,NA,-181) //Ellipse (optional box 3) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 3) rotation enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E44 RW 0x0000_0000
	UINT32 reg_opt3_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 3) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 3) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 3) manual box center position enable
	};
	};
}PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E50 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y0              :8;	//(7:0,NA,255) //LUT (probability map) control point, y0
	UINT32 reg_lut_prob_map_x0              :8;	//(15:8,NA,255) //LUT (probability map) control point, x0
	UINT32 reg_lut_prob_map_y1              :8;	//(23:16,NA,255) //LUT (probability map) control point, y1
	UINT32 reg_lut_prob_map_x1              :8;	//(31:24,NA,255) //LUT (probability map) control point, x1
	};
	};
}PE_O26F22_AMG0_HEAD_LUT_PROB_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E54 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y2              :8;	//(7:0,NA,255) //LUT (probability map) control point, y2
	UINT32 reg_lut_prob_map_x2              :8;	//(15:8,NA,255) //LUT (probability map) control point, x2
	UINT32 reg_lut_prob_map_y3              :8;	//(23:16,NA,255) //LUT (probability map) control point, y3
	UINT32 reg_lut_prob_map_x3              :8;	//(31:24,NA,255) //LUT (probability map) control point, x3
	};
	};
}PE_O26F22_AMG0_HEAD_LUT_PROB_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E60 RW 0x0000_0000
	UINT32 reg_blur_en                      :1;	//(0:0,NA,0) //Blur filter enable
	UINT32 resvd                            :31;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E64 RW 0x0071_0071
	UINT32 reg_blur_hcoef0                  :10;	//(9:0,NA,113) //Blur filter coefficient, h0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef1                  :10;	//(25:16,NA,113) //Blur filter coefficient, h1
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E68 RW 0x0072_0072
	UINT32 reg_blur_hcoef2                  :10;	//(9:0,NA,114) //Blur filter coefficient, h2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef3                  :10;	//(25:16,NA,114) //Blur filter coefficient, h3
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E6C RW 0x0072_0074
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,116) //Blur filter coefficient, h4
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef5                  :10;	//(25:16,NA,114) //Blur filter coefficient, h5
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E70 RW 0x0071_0072
	UINT32 reg_blur_hcoef6                  :10;	//(9:0,NA,114) //Blur filter coefficient, h6
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef7                  :10;	//(25:16,NA,113) //Blur filter coefficient, h7
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E74 RW 0x0000_0071
	UINT32 reg_blur_hcoef8                  :10;	//(9:0,NA,113) //Blur filter coefficient, h8
	UINT32 resvd                            :22;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E78 RW 0x00CC_00CC
	UINT32 reg_blur_vcoef0                  :10;	//(9:0,NA,204) //Blur filter coefficient, v0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef1                  :10;	//(25:16,NA,204) //Blur filter coefficient, v1
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E7C RW 0x00CC_00D0
	UINT32 reg_blur_vcoef2                  :10;	//(9:0,NA,208) //Blur filter coefficient, v2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef3                  :10;	//(25:16,NA,204) //Blur filter coefficient, v3
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011E80 RW 0x0000_00CC
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,204) //Blur filter coefficient, v4
	UINT32 resvd                            :22;
	};
	};
}PE_O26F22_AMG0_HEAD_BLUR_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011F20 RW 0x0000_0010
	UINT32 reg_iir_en                       :1;	//(0:0,NA,0) //IIR filter enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_alpha_sel                :1;	//(4:4,NA,1) //Blending alpha selection	0: use manual value	1: use ABS diff value
	UINT32 resvd1                           :3;
	UINT32 reg_iir_alpha                    :8;	//(15:8,NA,0) //Blending alpha for IIR
	UINT32 reg_iir_gain_init                :1;	//(16:16,NA,0) //IIR gain init selection	0: use IIR result	1: use manual gain init value
	UINT32 resvd2                           :7;
	UINT32 reg_iir_gain_init_val            :8;	//(31:24,NA,0) //IIR gain init value
	};
	};
}PE_O26F22_AMG0_HEAD_IIR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011F24 RW 0x0018_0801
	UINT32 reg_iir_clipping_en              :1;	//(0:0,NA,1) //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_th_lower                 :8;	//(11:4,NA,128) //IIR value clipping lower threshold
	UINT32 reg_iir_th_upper                 :8;	//(19:12,NA,128) //IIR value clipping upper threshold
	UINT32 reg_iir_same_prot                :8;	//(27:20,NA,1) //IIR same value protection
	UINT32 resvd1                           :4;
	};
	};
}PE_O26F22_AMG0_HEAD_IIR_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011F30 RW 0x10DC_00F0
	UINT32 reg_lut_iir_map_y0               :8;	//(7:0,NA,240) //LUT (IIR gain) control point, y0
	UINT32 reg_lut_iir_map_x0               :8;	//(15:8,NA,0) //LUT (IIR gain) control point, x0
	UINT32 reg_lut_iir_map_y1               :8;	//(23:16,NA,220) //LUT (IIR gain) control point, y1
	UINT32 reg_lut_iir_map_x1               :8;	//(31:24,NA,16) //LUT (IIR gain) control point, x1
	};
	};
}PE_O26F22_AMG0_HEAD_LUT_IIR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011F34 RW 0x40B0_20C0
	UINT32 reg_lut_iir_map_y2               :8;	//(7:0,NA,192) //LUT (IIR gain) control point, y2
	UINT32 reg_lut_iir_map_x2               :8;	//(15:8,NA,32) //LUT (IIR gain) control point, x2
	UINT32 reg_lut_iir_map_y3               :8;	//(23:16,NA,176) //LUT (IIR gain) control point, y3
	UINT32 reg_lut_iir_map_x3               :8;	//(31:24,NA,64) //LUT (IIR gain) control point, x3
	};
	};
}PE_O26F22_AMG0_HEAD_LUT_IIR_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3011F38 RW 0x8080_60A0
	UINT32 reg_lut_iir_map_y4               :8;	//(7:0,NA,160) //LUT (IIR gain) control point, y4
	UINT32 reg_lut_iir_map_x4               :8;	//(15:8,NA,96) //LUT (IIR gain) control point, x4
	UINT32 reg_lut_iir_map_y5               :8;	//(23:16,NA,128) //LUT (IIR gain) control point, y5
	UINT32 reg_lut_iir_map_x5               :8;	//(31:24,NA,128) //LUT (IIR gain) control point, x5
	};
	};
}PE_O26F22_AMG0_HEAD_LUT_IIR_CTRL_02_T;


typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012020 RW 0x0242_0242
	UINT32 reg_hist_coef0_hb                :3;	//(2:0,NA,2) //Histogram coefficient, 0 (HEAD/BODY)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_coef1_hb                :3;	//(6:4,NA,4) //Histogram coefficient, 1 (HEAD/BODY)
	UINT32 resvd1                           :1;
	UINT32 reg_hist_coef2_hb                :3;	//(10:8,NA,2) //Histogram coefficient, 2 (HEAD/BODY)
	UINT32 resvd2                           :5;
	UINT32 reg_hist_coef0_depth             :3;	//(18:16,NA,2) //Histogram coefficient, 0 (Depth)
	UINT32 resvd3                           :1;
	UINT32 reg_hist_coef1_depth             :3;	//(22:20,NA,4) //Histogram coefficient, 1 (Depth)
	UINT32 resvd4                           :1;
	UINT32 reg_hist_coef2_depth             :3;	//(26:24,NA,2) //Histogram coefficient, 2 (Depth)
	UINT32 resvd5                           :5;
	};
	};
}PE_O26F22_AMG1_BODY_HISTOGRAM_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012024 RW 0x0000_0000
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection	0: Y	1: Cb	2: Cr	3: Depth
	UINT32 resvd                            :30;
	};
	};
}PE_O26F22_AMG1_BODY_HISTOGRAM_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120B0 RW 0x0000_1101
	UINT32 reg_objt_map_en                  :1;	//(0:0,NA,1) //Object map enable
	UINT32 resvd0                           :3;
	UINT32 reg_dbg_map_ctrl                 :3;	//(6:4,NA,0) //Debug map selection	0: Probability map	1: Ellipse gain map	2: Probability map (FG)	3: Probability map (BG)	4: Probability map (diff)	5: Box map	6: Pixel data (Y)
	UINT32 resvd1                           :1;
	UINT32 reg_fg_mul_ellipse_en            :1;	//(8:8,NA,1) //Reflect ellipse gain enable
	UINT32 resvd2                           :3;
	UINT32 reg_out_mux_sel                  :2;	//(13:12,NA,1) //Object map output mux selection	0: HEAD/BODY	1: Blending	2: Depth only	3: Adding
	UINT32 resvd3                           :18;
	};
	};
}PE_O26F22_AMG1_BODY_OBJT_MAP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120B4 RW 0x0055_0055
	UINT32 reg_fg_prob_factor               :7;	//(6:0,NA,85) //FG probability map factor
	UINT32 resvd0                           :9;
	UINT32 reg_bg_prob_factor               :7;	//(22:16,NA,85) //BG probability map factor
	UINT32 resvd1                           :9;
	};
	};
}PE_O26F22_AMG1_BODY_OBJT_MAP_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120B8 RW 0x00C4_00C4
	UINT32 reg_fg_diff_mul                  :10;	//(9:0,NA,196) //FG factor for probability diff map (6.4bit)
	UINT32 resvd0                           :6;
	UINT32 reg_bg_diff_mul                  :10;	//(25:16,NA,196) //BG factor for probability diff map (6.4bit)
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG1_BODY_OBJT_MAP_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120BC RW 0x0004_0004
	UINT32 reg_e_offset                     :8;	//(7:0,NA,4) //Ellipse gain offset
	UINT32 resvd0                           :8;
	UINT32 reg_p_offset                     :8;	//(23:16,NA,4) //Probability diff map offset
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG1_BODY_OBJT_MAP_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120C0 RW 0x0000_0000
	UINT32 reg_box_fg_cand_en               :1;	//(0:0,NA,0) //FG candidate box set enable
	UINT32 resvd0                           :3;
	UINT32 reg_box0_add_set1_en             :1;	//(4:4,NA,0) //Additional box0 set1 enable
	UINT32 reg_box1_add_set1_en             :1;	//(5:5,NA,0) //Additional box1 set1 enable
	UINT32 reg_box2_add_set1_en             :1;	//(6:6,NA,0) //Additional box2 set1 enable
	UINT32 reg_box3_add_set1_en             :1;	//(7:7,NA,0) //Additional box3 set1 enable
	UINT32 reg_box0_add_set2_en             :1;	//(8:8,NA,0) //Additional box0 set2 enable
	UINT32 reg_box1_add_set2_en             :1;	//(9:9,NA,0) //Additional box1 set2 enable
	UINT32 reg_box2_add_set2_en             :1;	//(10:10,NA,0) //Additional box2 set2 enable
	UINT32 reg_box3_add_set2_en             :1;	//(11:11,NA,0) //Additional box3 set2 enable
	UINT32 reg_box0_opt_en                  :1;	//(12:12,NA,0) //Optional box0 set enable
	UINT32 reg_box1_opt_en                  :1;	//(13:13,NA,0) //Optional box1 set enable
	UINT32 reg_box2_opt_en                  :1;	//(14:14,NA,0) //Optional box2 set enable
	UINT32 reg_box3_opt_en                  :1;	//(15:15,NA,0) //Optional box3 set enable
	UINT32 reg_additional_box_en            :1;	//(16:16,NA,0) //Additional box enable	- 0: disable (default, replaced to optional box enable)	- 1: enable
	UINT32 resvd1                           :15;
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120C4 RW 0x0000_0000
	UINT32 reg_box_fg_cand_w1               :8;	//(7:0,NA,0) //Box (FG candidate) position, w, start
	UINT32 reg_box_fg_cand_w2               :8;	//(15:8,NA,0) //Box (FG candidate) position, w, end
	UINT32 reg_box_fg_cand_h1               :8;	//(23:16,NA,0) //Box (FG candidate) position, h, start
	UINT32 reg_box_fg_cand_h2               :8;	//(31:24,NA,0) //Box (FG candidate) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120C8 RW 0x0000_0000
	UINT32 reg_box0_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 1) position, w, start
	UINT32 reg_box0_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 1) position, w, end
	UINT32 reg_box0_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 1) position, h, start
	UINT32 reg_box0_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 1) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120CC RW 0x0000_0000
	UINT32 reg_box1_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 1) position, w, start
	UINT32 reg_box1_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 1) position, w, end
	UINT32 reg_box1_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 1) position, h, start
	UINT32 reg_box1_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 1) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120D0 RW 0x0000_0000
	UINT32 reg_box2_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 1) position, w, start
	UINT32 reg_box2_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 1) position, w, end
	UINT32 reg_box2_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 1) position, h, start
	UINT32 reg_box2_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 1) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120D4 RW 0x0000_0000
	UINT32 reg_box3_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 1) position, w, start
	UINT32 reg_box3_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 1) position, w, end
	UINT32 reg_box3_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 1) position, h, start
	UINT32 reg_box3_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 1) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120D8 RW 0x0000_0000
	UINT32 reg_box0_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 2) position, w, start
	UINT32 reg_box0_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 2) position, w, end
	UINT32 reg_box0_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 2) position, h, start
	UINT32 reg_box0_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 2) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120DC RW 0x0000_0000
	UINT32 reg_box1_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 2) position, w, start
	UINT32 reg_box1_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 2) position, w, end
	UINT32 reg_box1_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 2) position, h, start
	UINT32 reg_box1_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 2) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120E0 RW 0x0000_0000
	UINT32 reg_box2_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 2) position, w, start
	UINT32 reg_box2_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 2) position, w, end
	UINT32 reg_box2_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 2) position, h, start
	UINT32 reg_box2_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 2) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120E4 RW 0x0000_0000
	UINT32 reg_box3_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 2) position, w, start
	UINT32 reg_box3_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 2) position, w, end
	UINT32 reg_box3_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 2) position, h, start
	UINT32 reg_box3_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 2) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120E8 RW 0x0000_0000
	UINT32 reg_box0_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 0) position, w, start
	UINT32 reg_box0_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 0) position, w, end
	UINT32 reg_box0_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 0) position, h, start
	UINT32 reg_box0_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 0) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120EC RW 0x0000_0000
	UINT32 reg_box1_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 1) position, w, start
	UINT32 reg_box1_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 1) position, w, end
	UINT32 reg_box1_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 1) position, h, start
	UINT32 reg_box1_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 1) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120F0 RW 0x0000_0000
	UINT32 reg_box2_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 2) position, w, start
	UINT32 reg_box2_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 2) position, w, end
	UINT32 reg_box2_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 2) position, h, start
	UINT32 reg_box2_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 2) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30120F4 RW 0x0000_0000
	UINT32 reg_box3_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 3) position, w, start
	UINT32 reg_box3_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 3) position, w, end
	UINT32 reg_box3_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 3) position, h, start
	UINT32 reg_box3_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 3) position, h, end
	};
	};
}PE_O26F22_AMG1_BODY_BOX_SET_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012100 RW 0x0000_0000
	UINT32 reg_fg_cand_e_mul_a              :9;	//(8:0,NA,0) //Ellipse (FG candidate) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_fg_cand_e_mul_b              :9;	//(24:16,NA,0) //Ellipse (FG candidate) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_fg_cand_ellipse_en           :1;	//(31:31,NA,0) //Ellipse (FG candidate) gain gen enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012104 RW 0x0000_0000
	UINT32 reg_fg_cand_ellipse_master       :8;	//(7:0,NA,0) //Ellipse (FG candidate) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_fg_cand_ellipse_offset       :8;	//(23:16,NA,0) //Ellipse (FG candidate) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012108 RW 0x002A_0026
	UINT32 reg_opt0_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 0) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 0) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 0) gain gen enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF301210C RW 0x0040_00C0
	UINT32 reg_opt0_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 0) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt0_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 0) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012110 RW 0x00DE_0080
	UINT32 reg_opt0_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 0) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_sin_theta               :9;	//(24:16,NA,222) //Ellipse (optional box 0) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 0) rotation enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012114 RW 0x0000_0000
	UINT32 reg_opt0_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 0) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 0) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 0) manual box center position enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012118 RW 0x002A_0026
	UINT32 reg_opt1_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 1) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 1) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 1) gain gen enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF301211C RW 0x0040_00C0
	UINT32 reg_opt1_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 1) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt1_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 1) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012120 RW 0x0122_0080
	UINT32 reg_opt1_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 1) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_sin_theta               :9;	//(24:16,NA,-222) //Ellipse (optional box 1) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 1) rotation enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012124 RW 0x0000_0000
	UINT32 reg_opt1_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 1) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 1) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 1) manual box center position enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012128 RW 0x002A_0026
	UINT32 reg_opt2_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 2) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 2) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 2) gain gen enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF301212C RW 0x0040_00C0
	UINT32 reg_opt2_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 2) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt2_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 2) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012130 RW 0x00B5_00B5
	UINT32 reg_opt2_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 2) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_sin_theta               :9;	//(24:16,NA,181) //Ellipse (optional box 2) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 2) rotation enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012134 RW 0x0000_0000
	UINT32 reg_opt2_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 2) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 2) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 2) manual box center position enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012138 RW 0x002A_0026
	UINT32 reg_opt3_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 3) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 3) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_en              :1;	//(31:31,NA,0) //Ellipse (optional box 3) gain gen enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF301213C RW 0x0040_00C0
	UINT32 reg_opt3_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 3) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt3_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 3) gain offset threshold
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012140 RW 0x014B_00B5
	UINT32 reg_opt3_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 3) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_sin_theta               :9;	//(24:16,NA,-181) //Ellipse (optional box 3) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 3) rotation enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012144 RW 0x0000_0000
	UINT32 reg_opt3_ellipse_cen_pos_x       :9;	//(8:0,NA,0) //Ellipse (optional box 3) manual box center position (H)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_ellipse_cen_pos_y       :9;	//(24:16,NA,0) //Ellipse (optional box 3) manual box center position (V)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 3) manual box center position enable
	};
	};
}PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012150 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y0              :8;	//(7:0,NA,255) //LUT (probability map) control point, y0
	UINT32 reg_lut_prob_map_x0              :8;	//(15:8,NA,255) //LUT (probability map) control point, x0
	UINT32 reg_lut_prob_map_y1              :8;	//(23:16,NA,255) //LUT (probability map) control point, y1
	UINT32 reg_lut_prob_map_x1              :8;	//(31:24,NA,255) //LUT (probability map) control point, x1
	};
	};
}PE_O26F22_AMG1_BODY_LUT_PROB_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012154 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y2              :8;	//(7:0,NA,255) //LUT (probability map) control point, y2
	UINT32 reg_lut_prob_map_x2              :8;	//(15:8,NA,255) //LUT (probability map) control point, x2
	UINT32 reg_lut_prob_map_y3              :8;	//(23:16,NA,255) //LUT (probability map) control point, y3
	UINT32 reg_lut_prob_map_x3              :8;	//(31:24,NA,255) //LUT (probability map) control point, x3
	};
	};
}PE_O26F22_AMG1_BODY_LUT_PROB_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012160 RW 0x0000_0000
	UINT32 reg_blur_en                      :1;	//(0:0,NA,0) //Blur filter enable
	UINT32 resvd                            :31;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012164 RW 0x0071_0071
	UINT32 reg_blur_hcoef0                  :10;	//(9:0,NA,113) //Blur filter coefficient, h0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef1                  :10;	//(25:16,NA,113) //Blur filter coefficient, h1
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012168 RW 0x0072_0072
	UINT32 reg_blur_hcoef2                  :10;	//(9:0,NA,114) //Blur filter coefficient, h2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef3                  :10;	//(25:16,NA,114) //Blur filter coefficient, h3
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF301216C RW 0x0072_0074
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,116) //Blur filter coefficient, h4
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef5                  :10;	//(25:16,NA,114) //Blur filter coefficient, h5
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012170 RW 0x0071_0072
	UINT32 reg_blur_hcoef6                  :10;	//(9:0,NA,114) //Blur filter coefficient, h6
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef7                  :10;	//(25:16,NA,113) //Blur filter coefficient, h7
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012174 RW 0x0000_0071
	UINT32 reg_blur_hcoef8                  :10;	//(9:0,NA,113) //Blur filter coefficient, h8
	UINT32 resvd                            :22;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012178 RW 0x00CC_00CC
	UINT32 reg_blur_vcoef0                  :10;	//(9:0,NA,204) //Blur filter coefficient, v0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef1                  :10;	//(25:16,NA,204) //Blur filter coefficient, v1
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF301217C RW 0x00CC_00D0
	UINT32 reg_blur_vcoef2                  :10;	//(9:0,NA,208) //Blur filter coefficient, v2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef3                  :10;	//(25:16,NA,204) //Blur filter coefficient, v3
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012180 RW 0x0000_00CC
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,204) //Blur filter coefficient, v4
	UINT32 resvd                            :22;
	};
	};
}PE_O26F22_AMG1_BODY_BLUR_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012190 RW 0x5014_0000
	UINT32 reg_lut_depth_map_y0             :8;	//(7:0,NA,0) //LUT (depth map) control point, y0
	UINT32 reg_lut_depth_map_x0             :8;	//(15:8,NA,0) //LUT (depth map) control point, x0
	UINT32 reg_lut_depth_map_y1             :8;	//(23:16,NA,20) //LUT (depth map) control point, y1
	UINT32 reg_lut_depth_map_x1             :8;	//(31:24,NA,80) //LUT (depth map) control point, x1
	};
	};
}PE_O26F22_AMG1_BODY_LUT_DEPTH_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012194 RW 0xFFFF_6E6E
	UINT32 reg_lut_depth_map_y2             :8;	//(7:0,NA,110) //LUT (depth map) control point, y2
	UINT32 reg_lut_depth_map_x2             :8;	//(15:8,NA,110) //LUT (depth map) control point, x2
	UINT32 reg_lut_depth_map_y3             :8;	//(23:16,NA,255) //LUT (depth map) control point, y3
	UINT32 reg_lut_depth_map_x3             :8;	//(31:24,NA,255) //LUT (depth map) control point, x3
	};
	};
}PE_O26F22_AMG1_BODY_LUT_DEPTH_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121A0 RW 0xC090_6030
	UINT32 reg_region_position_x1           :8;	//(7:0,NA,48) //Region gain position, x1
	UINT32 reg_region_position_x2           :8;	//(15:8,NA,96) //Region gain position, x2
	UINT32 reg_region_position_x3           :8;	//(23:16,NA,144) //Region gain position, x3
	UINT32 reg_region_position_x4           :8;	//(31:24,NA,192) //Region gain position, x4
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121A4 RW 0xEFEF_EFEF
	UINT32 reg_region_position_x5           :8;	//(7:0,NA,239) //Region gain position, x5
	UINT32 reg_region_position_x6           :8;	//(15:8,NA,239) //Region gain position, x6
	UINT32 reg_region_position_x7           :8;	//(23:16,NA,239) //Region gain position, x7
	UINT32 reg_region_position_x8           :8;	//(31:24,NA,239) //Region gain position, x8
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121A8 RW 0x7D73_5A28
	UINT32 reg_region_position_y1           :8;	//(7:0,NA,40) //Region gain position, y1
	UINT32 reg_region_position_y2           :8;	//(15:8,NA,90) //Region gain position, y2
	UINT32 reg_region_position_y3           :8;	//(23:16,NA,115) //Region gain position, y3
	UINT32 reg_region_position_y4           :8;	//(31:24,NA,125) //Region gain position, y4
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121AC RW 0x0000_8686
	UINT32 reg_region_position_y5           :8;	//(7:0,NA,134) //Region gain position, y5
	UINT32 reg_region_position_y6           :8;	//(15:8,NA,134) //Region gain position, y6
	UINT32 resvd                            :16;
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121B0 RW 0x0000_0000
	UINT32 reg_region_gain_en_11            :2;	//(1:0,NA,0) //Region gain enable, 11
	UINT32 reg_region_gain_en_21            :2;	//(3:2,NA,0) //Region gain enable, 21
	UINT32 reg_region_gain_en_31            :2;	//(5:4,NA,0) //Region gain enable, 31
	UINT32 reg_region_gain_en_41            :2;	//(7:6,NA,0) //Region gain enable, 41
	UINT32 reg_region_gain_en_51            :2;	//(9:8,NA,0) //Region gain enable, 51
	UINT32 reg_region_gain_en_61            :2;	//(11:10,NA,0) //Region gain enable, 61
	UINT32 reg_region_gain_en_71            :2;	//(13:12,NA,0) //Region gain enable, 71
	UINT32 reg_region_gain_en_81            :2;	//(15:14,NA,0) //Region gain enable, 81
	UINT32 reg_region_gain_en_12            :2;	//(17:16,NA,0) //Region gain enable, 12
	UINT32 reg_region_gain_en_22            :2;	//(19:18,NA,0) //Region gain enable, 22
	UINT32 reg_region_gain_en_32            :2;	//(21:20,NA,0) //Region gain enable, 32
	UINT32 reg_region_gain_en_42            :2;	//(23:22,NA,0) //Region gain enable, 42
	UINT32 reg_region_gain_en_52            :2;	//(25:24,NA,0) //Region gain enable, 52
	UINT32 reg_region_gain_en_62            :2;	//(27:26,NA,0) //Region gain enable, 62
	UINT32 reg_region_gain_en_72            :2;	//(29:28,NA,0) //Region gain enable, 72
	UINT32 reg_region_gain_en_82            :2;	//(31:30,NA,0) //Region gain enable, 82
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121B4 RW 0x0000_0000
	UINT32 reg_region_gain_en_13            :2;	//(1:0,NA,0) //Region gain enable, 13
	UINT32 reg_region_gain_en_23            :2;	//(3:2,NA,0) //Region gain enable, 23
	UINT32 reg_region_gain_en_33            :2;	//(5:4,NA,0) //Region gain enable, 33
	UINT32 reg_region_gain_en_43            :2;	//(7:6,NA,0) //Region gain enable, 43
	UINT32 reg_region_gain_en_53            :2;	//(9:8,NA,0) //Region gain enable, 53
	UINT32 reg_region_gain_en_63            :2;	//(11:10,NA,0) //Region gain enable, 63
	UINT32 reg_region_gain_en_73            :2;	//(13:12,NA,0) //Region gain enable, 73
	UINT32 reg_region_gain_en_83            :2;	//(15:14,NA,0) //Region gain enable, 83
	UINT32 reg_region_gain_en_14            :2;	//(17:16,NA,0) //Region gain enable, 14
	UINT32 reg_region_gain_en_24            :2;	//(19:18,NA,0) //Region gain enable, 24
	UINT32 reg_region_gain_en_34            :2;	//(21:20,NA,0) //Region gain enable, 34
	UINT32 reg_region_gain_en_44            :2;	//(23:22,NA,0) //Region gain enable, 44
	UINT32 reg_region_gain_en_54            :2;	//(25:24,NA,0) //Region gain enable, 54
	UINT32 reg_region_gain_en_64            :2;	//(27:26,NA,0) //Region gain enable, 64
	UINT32 reg_region_gain_en_74            :2;	//(29:28,NA,0) //Region gain enable, 74
	UINT32 reg_region_gain_en_84            :2;	//(31:30,NA,0) //Region gain enable, 84
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121B8 RW 0x0000_0000
	UINT32 reg_region_gain_en_15            :2;	//(1:0,NA,0) //Region gain enable, 15
	UINT32 reg_region_gain_en_25            :2;	//(3:2,NA,0) //Region gain enable, 25
	UINT32 reg_region_gain_en_35            :2;	//(5:4,NA,0) //Region gain enable, 35
	UINT32 reg_region_gain_en_45            :2;	//(7:6,NA,0) //Region gain enable, 45
	UINT32 reg_region_gain_en_55            :2;	//(9:8,NA,0) //Region gain enable, 55
	UINT32 reg_region_gain_en_65            :2;	//(11:10,NA,0) //Region gain enable, 65
	UINT32 reg_region_gain_en_75            :2;	//(13:12,NA,0) //Region gain enable, 75
	UINT32 reg_region_gain_en_85            :2;	//(15:14,NA,0) //Region gain enable, 85
	UINT32 reg_region_gain_en_16            :2;	//(17:16,NA,0) //Region gain enable, 16
	UINT32 reg_region_gain_en_26            :2;	//(19:18,NA,0) //Region gain enable, 26
	UINT32 reg_region_gain_en_36            :2;	//(21:20,NA,0) //Region gain enable, 36
	UINT32 reg_region_gain_en_46            :2;	//(23:22,NA,0) //Region gain enable, 46
	UINT32 reg_region_gain_en_56            :2;	//(25:24,NA,0) //Region gain enable, 56
	UINT32 reg_region_gain_en_66            :2;	//(27:26,NA,0) //Region gain enable, 66
	UINT32 reg_region_gain_en_76            :2;	//(29:28,NA,0) //Region gain enable, 76
	UINT32 reg_region_gain_en_86            :2;	//(31:30,NA,0) //Region gain enable, 86
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121BC RW 0x8080_8080
	UINT32 reg_region_gain_11               :8;	//(7:0,NA,128) //Region gain, 11
	UINT32 reg_region_gain_21               :8;	//(15:8,NA,128) //Region gain, 21
	UINT32 reg_region_gain_31               :8;	//(23:16,NA,128) //Region gain, 31
	UINT32 reg_region_gain_41               :8;	//(31:24,NA,128) //Region gain, 41
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121C0 RW 0x8080_8080
	UINT32 reg_region_gain_51               :8;	//(7:0,NA,128) //Region gain, 51
	UINT32 reg_region_gain_61               :8;	//(15:8,NA,128) //Region gain, 61
	UINT32 reg_region_gain_71               :8;	//(23:16,NA,128) //Region gain, 71
	UINT32 reg_region_gain_81               :8;	//(31:24,NA,128) //Region gain, 81
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121C4 RW 0x8080_8080
	UINT32 reg_region_gain_12               :8;	//(7:0,NA,128) //Region gain, 12
	UINT32 reg_region_gain_22               :8;	//(15:8,NA,128) //Region gain, 22
	UINT32 reg_region_gain_32               :8;	//(23:16,NA,128) //Region gain, 32
	UINT32 reg_region_gain_42               :8;	//(31:24,NA,128) //Region gain, 42
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121C8 RW 0x8080_8080
	UINT32 reg_region_gain_52               :8;	//(7:0,NA,128) //Region gain, 52
	UINT32 reg_region_gain_62               :8;	//(15:8,NA,128) //Region gain, 62
	UINT32 reg_region_gain_72               :8;	//(23:16,NA,128) //Region gain, 72
	UINT32 reg_region_gain_82               :8;	//(31:24,NA,128) //Region gain, 82
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121CC RW 0x8080_8080
	UINT32 reg_region_gain_13               :8;	//(7:0,NA,128) //Region gain, 13
	UINT32 reg_region_gain_23               :8;	//(15:8,NA,128) //Region gain, 23
	UINT32 reg_region_gain_33               :8;	//(23:16,NA,128) //Region gain, 33
	UINT32 reg_region_gain_43               :8;	//(31:24,NA,128) //Region gain, 43
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121D0 RW 0x8080_8080
	UINT32 reg_region_gain_53               :8;	//(7:0,NA,128) //Region gain, 53
	UINT32 reg_region_gain_63               :8;	//(15:8,NA,128) //Region gain, 63
	UINT32 reg_region_gain_73               :8;	//(23:16,NA,128) //Region gain, 73
	UINT32 reg_region_gain_83               :8;	//(31:24,NA,128) //Region gain, 83
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121D4 RW 0x8080_8080
	UINT32 reg_region_gain_14               :8;	//(7:0,NA,128) //Region gain, 14
	UINT32 reg_region_gain_24               :8;	//(15:8,NA,128) //Region gain, 24
	UINT32 reg_region_gain_34               :8;	//(23:16,NA,128) //Region gain, 34
	UINT32 reg_region_gain_44               :8;	//(31:24,NA,128) //Region gain, 44
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121D8 RW 0x8080_8080
	UINT32 reg_region_gain_54               :8;	//(7:0,NA,128) //Region gain, 54
	UINT32 reg_region_gain_64               :8;	//(15:8,NA,128) //Region gain, 64
	UINT32 reg_region_gain_74               :8;	//(23:16,NA,128) //Region gain, 74
	UINT32 reg_region_gain_84               :8;	//(31:24,NA,128) //Region gain, 84
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121DC RW 0x8080_8080
	UINT32 reg_region_gain_15               :8;	//(7:0,NA,128) //Region gain, 15
	UINT32 reg_region_gain_25               :8;	//(15:8,NA,128) //Region gain, 25
	UINT32 reg_region_gain_35               :8;	//(23:16,NA,128) //Region gain, 35
	UINT32 reg_region_gain_45               :8;	//(31:24,NA,128) //Region gain, 45
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121E0 RW 0x8080_8080
	UINT32 reg_region_gain_55               :8;	//(7:0,NA,128) //Region gain, 55
	UINT32 reg_region_gain_65               :8;	//(15:8,NA,128) //Region gain, 65
	UINT32 reg_region_gain_75               :8;	//(23:16,NA,128) //Region gain, 75
	UINT32 reg_region_gain_85               :8;	//(31:24,NA,128) //Region gain, 85
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_16_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121E4 RW 0x8080_8080
	UINT32 reg_region_gain_16               :8;	//(7:0,NA,128) //Region gain, 16
	UINT32 reg_region_gain_26               :8;	//(15:8,NA,128) //Region gain, 26
	UINT32 reg_region_gain_36               :8;	//(23:16,NA,128) //Region gain, 36
	UINT32 reg_region_gain_46               :8;	//(31:24,NA,128) //Region gain, 46
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_17_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121E8 RW 0x8080_8080
	UINT32 reg_region_gain_56               :8;	//(7:0,NA,128) //Region gain, 56
	UINT32 reg_region_gain_66               :8;	//(15:8,NA,128) //Region gain, 66
	UINT32 reg_region_gain_76               :8;	//(23:16,NA,128) //Region gain, 76
	UINT32 reg_region_gain_86               :8;	//(31:24,NA,128) //Region gain, 86
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_18_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121EC RW 0x8600_EF00
	UINT32 reg_region_bnd_x0                :8;	//(7:0,NA,0) //Region bound, x0
	UINT32 reg_region_bnd_x1                :8;	//(15:8,NA,239) //Region bound, x1
	UINT32 reg_region_bnd_y0                :8;	//(23:16,NA,0) //Region bound, y0
	UINT32 reg_region_bnd_y1                :8;	//(31:24,NA,134) //Region bound, y1
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_19_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121F0 RW 0x0000_0080
	UINT32 reg_region_bnd_gain              :8;	//(7:0,NA,128) //Region bound gain
	UINT32 resvd                            :24;
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_20_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30121F4 RW 0x0000_0110
	UINT32 reg_region_gain_offset0          :8;	//(7:0,NA,16) //Region gain offset0
	UINT32 reg_region_gain_offset1          :8;	//(15:8,NA,1) //Region gain offset1
	UINT32 resvd                            :16;
	};
	};
}PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_21_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012200 RW 0x40FF_00FF
	UINT32 reg_lut_depth_iir_u_y0           :8;	//(7:0,NA,255) //LUT (depth map IIR, up) control point, y0
	UINT32 reg_lut_depth_iir_u_x0           :8;	//(15:8,NA,0) //LUT (depth map IIR, up) control point, x0
	UINT32 reg_lut_depth_iir_u_y1           :8;	//(23:16,NA,255) //LUT (depth map IIR, up) control point, y1
	UINT32 reg_lut_depth_iir_u_x1           :8;	//(31:24,NA,64) //LUT (depth map IIR, up) control point, x1
	};
	};
}PE_O26F22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012204 RW 0xFFFF_80FF
	UINT32 reg_lut_depth_iir_u_y2           :8;	//(7:0,NA,255) //LUT (depth map IIR, up) control point, y2
	UINT32 reg_lut_depth_iir_u_x2           :8;	//(15:8,NA,128) //LUT (depth map IIR, up) control point, x2
	UINT32 reg_lut_depth_iir_u_y3           :8;	//(23:16,NA,255) //LUT (depth map IIR, up) control point, y3
	UINT32 reg_lut_depth_iir_u_x3           :8;	//(31:24,NA,255) //LUT (depth map IIR, up) control point, x3
	};
	};
}PE_O26F22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012208 RW 0x40FF_00FF
	UINT32 reg_lut_depth_iir_d_y0           :8;	//(7:0,NA,255) //LUT (depth map IIR, down) control point, y0
	UINT32 reg_lut_depth_iir_d_x0           :8;	//(15:8,NA,0) //LUT (depth map IIR, down) control point, x0
	UINT32 reg_lut_depth_iir_d_y1           :8;	//(23:16,NA,255) //LUT (depth map IIR, down) control point, y1
	UINT32 reg_lut_depth_iir_d_x1           :8;	//(31:24,NA,64) //LUT (depth map IIR, down) control point, x1
	};
	};
}PE_O26F22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF301220C RW 0xFFFF_80FF
	UINT32 reg_lut_depth_iir_d_y2           :8;	//(7:0,NA,255) //LUT (depth map IIR, down) control point, y2
	UINT32 reg_lut_depth_iir_d_x2           :8;	//(15:8,NA,128) //LUT (depth map IIR, down) control point, x2
	UINT32 reg_lut_depth_iir_d_y3           :8;	//(23:16,NA,255) //LUT (depth map IIR, down) control point, y3
	UINT32 reg_lut_depth_iir_d_x3           :8;	//(31:24,NA,255) //LUT (depth map IIR, down) control point, x3
	};
	};
}PE_O26F22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012210 RW 0x3FFF_00FF
	UINT32 reg_lut_depth_body_y0            :8;	//(7:0,NA,255) //LUT (depth body blend) control point (for depth>body), y0
	UINT32 reg_lut_depth_body_x0            :8;	//(15:8,NA,0) //LUT (depth body blend) control point (for depth>body), x0
	UINT32 reg_lut_depth_body_y1            :8;	//(23:16,NA,255) //LUT (depth body blend) control point (for depth>body), y1
	UINT32 reg_lut_depth_body_x1            :8;	//(31:24,NA,63) //LUT (depth body blend) control point (for depth>body), x1
	};
	};
}PE_O26F22_AMG1_BODY_LUT_BLD_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012214 RW 0xFFFF_7EFF
	UINT32 reg_lut_depth_body_y2            :8;	//(7:0,NA,255) //LUT (depth body blend) control point (for depth>body), y2
	UINT32 reg_lut_depth_body_x2            :8;	//(15:8,NA,126) //LUT (depth body blend) control point (for depth>body), x2
	UINT32 reg_lut_depth_body_y3            :8;	//(23:16,NA,255) //LUT (depth body blend) control point (for depth>body), y3
	UINT32 reg_lut_depth_body_x3            :8;	//(31:24,NA,255) //LUT (depth body blend) control point (for depth>body), x3
	};
	};
}PE_O26F22_AMG1_BODY_LUT_BLD_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012218 RW 0x3F20_0000
	UINT32 reg_lut_body_depth_y0            :8;	//(7:0,NA,0) //LUT (depth body blend) control point (for depth<=body), y0
	UINT32 reg_lut_body_depth_x0            :8;	//(15:8,NA,0) //LUT (depth body blend) control point (for depth<=body), x0
	UINT32 reg_lut_body_depth_y1            :8;	//(23:16,NA,32) //LUT (depth body blend) control point (for depth<=body), y1
	UINT32 reg_lut_body_depth_x1            :8;	//(31:24,NA,63) //LUT (depth body blend) control point (for depth<=body), x1
	};
	};
}PE_O26F22_AMG1_BODY_LUT_BLD_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF301221C RW 0xFF58_7E58
	UINT32 reg_lut_body_depth_y2            :8;	//(7:0,NA,88) //LUT (depth body blend) control point (for depth<=body), y2
	UINT32 reg_lut_body_depth_x2            :8;	//(15:8,NA,126) //LUT (depth body blend) control point (for depth<=body), x2
	UINT32 reg_lut_body_depth_y3            :8;	//(23:16,NA,88) //LUT (depth body blend) control point (for depth<=body), y3
	UINT32 reg_lut_body_depth_x3            :8;	//(31:24,NA,255) //LUT (depth body blend) control point (for depth<=body), x3
	};
	};
}PE_O26F22_AMG1_BODY_LUT_BLD_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012220 RW 0x0000_0010
	UINT32 reg_iir_en                       :1;	//(0:0,NA,0) //IIR filter enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_alpha_sel                :1;	//(4:4,NA,1) //Blending alpha selection	0: use manual value	1: use ABS diff value
	UINT32 resvd1                           :3;
	UINT32 reg_iir_alpha                    :8;	//(15:8,NA,0) //Blending alpha for IIR
	UINT32 reg_iir_gain_init                :1;	//(16:16,NA,0) //IIR gain init selection	0: use IIR result	1: use manual gain init value
	UINT32 resvd2                           :7;
	UINT32 reg_iir_gain_init_val            :8;	//(31:24,NA,0) //IIR gain init value
	};
	};
}PE_O26F22_AMG1_BODY_IIR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012224 RW 0x0018_0801
	UINT32 reg_iir_clipping_en              :1;	//(0:0,NA,1) //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_th_lower                 :8;	//(11:4,NA,128) //IIR value clipping lower threshold
	UINT32 reg_iir_th_upper                 :8;	//(19:12,NA,128) //IIR value clipping upper threshold
	UINT32 reg_iir_same_prot                :8;	//(27:20,NA,1) //IIR same value protection
	UINT32 resvd1                           :4;
	};
	};
}PE_O26F22_AMG1_BODY_IIR_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012230 RW 0x10DC_00F0
	UINT32 reg_lut_iir_map_y0               :8;	//(7:0,NA,240) //LUT (IIR gain) control point, y0
	UINT32 reg_lut_iir_map_x0               :8;	//(15:8,NA,0) //LUT (IIR gain) control point, x0
	UINT32 reg_lut_iir_map_y1               :8;	//(23:16,NA,220) //LUT (IIR gain) control point, y1
	UINT32 reg_lut_iir_map_x1               :8;	//(31:24,NA,16) //LUT (IIR gain) control point, x1
	};
	};
}PE_O26F22_AMG1_BODY_LUT_IIR_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012234 RW 0x40B0_20C0
	UINT32 reg_lut_iir_map_y2               :8;	//(7:0,NA,192) //LUT (IIR gain) control point, y2
	UINT32 reg_lut_iir_map_x2               :8;	//(15:8,NA,32) //LUT (IIR gain) control point, x2
	UINT32 reg_lut_iir_map_y3               :8;	//(23:16,NA,176) //LUT (IIR gain) control point, y3
	UINT32 reg_lut_iir_map_x3               :8;	//(31:24,NA,64) //LUT (IIR gain) control point, x3
	};
	};
}PE_O26F22_AMG1_BODY_LUT_IIR_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3012238 RW 0x8080_60A0
	UINT32 reg_lut_iir_map_y4               :8;	//(7:0,NA,160) //LUT (IIR gain) control point, y4
	UINT32 reg_lut_iir_map_x4               :8;	//(15:8,NA,96) //LUT (IIR gain) control point, x4
	UINT32 reg_lut_iir_map_y5               :8;	//(23:16,NA,128) //LUT (IIR gain) control point, y5
	UINT32 reg_lut_iir_map_x5               :8;	//(31:24,NA,128) //LUT (IIR gain) control point, x5
	};
	};
}PE_O26F22_AMG1_BODY_LUT_IIR_CTRL_02_T;

typedef struct
{	PE_O26F22_OBC_HEAD_PSP_CTRL00_T                                psp_ctrl00;	//0xF3030800
	PE_O26F22_OBC_HEAD_PSP_CTRL01_T                                psp_ctrl01;	//0xF3030804
	PE_O26F22_OBC_HEAD_PSP_CTRL02_T                                psp_ctrl02;	//0xF3030808
	PE_O26F22_OBC_HEAD_DISPLAY_DEBUG_MAP_T                       display_debug_map; //0xF3030848
 	PE_O26F22_OBC_HEAD_REFINE_CTRL0_T                            refine_ctrl0;	//0xF3030870
	PE_O26F22_OBC_HEAD_REFINE_CTRL1_T                            refine_ctrl1;	//0xF3030874
	PE_O26F22_OBC_HEAD_REFINE_CTRL2_T                            refine_ctrl2;	//0xF3030878
  	PE_O26F22_OBC_BODY_PSP_CTRL00_T                                body_psp_ctrl00;	//0xF3030600
	PE_O26F22_OBC_BODY_PSP_CTRL01_T                                body_psp_ctrl01;	//0xF3030604
	PE_O26F22_OBC_BODY_PSP_CTRL02_T                                body_psp_ctrl02;	//0xF3030608
	PE_O26F22_OBC_BODY_DISPLAY_DEBUG_MAP_T                       body_display_debug_map;//0xF3030648
 	PE_O26F22_OBC_BODY_REFINE_CTRL0_T                            body_refine_ctrl0;	//0xF3030670
	PE_O26F22_OBC_BODY_REFINE_CTRL1_T                            body_refine_ctrl1;	//0xF3030674
	PE_O26F22_OBC_BODY_REFINE_CTRL2_T                            body_refine_ctrl2;	//0xF3030678
 	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T obj_refine_body_gain_ctrl_00;	//0xF3030690
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T obj_refine_body_gain_ctrl_01;	//0xF3030694
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T obj_refine_body_gain_ctrl_02;	//0xF3030698
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T obj_refine_body_gain_ctrl_03;	//0xF303069C
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T obj_refine_body_gain_ctrl_04;	//0xF30306A0
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T obj_refine_body_gain_ctrl_05;	//0xF30306A4
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T obj_refine_body_gain_ctrl_06;	//0xF30306A8
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T obj_refine_body_gain_ctrl_07;	//0xF30306AC
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T obj_refine_body_gain_ctrl_08;	//0xF30306B0
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T obj_refine_body_gain_ctrl_09;	//0xF30306B4
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T obj_refine_body_gain_ctrl_10;	//0xF30306B8
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T obj_refine_body_gain_ctrl_11;	//0xF30306BC
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T obj_refine_body_gain_ctrl_12;	//0xF30306C0
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T obj_refine_body_gain_ctrl_13;	//0xF30306C4
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T obj_refine_body_gain_ctrl_14;	//0xF30306C8
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T obj_refine_body_gain_ctrl_15;	//0xF30306CC
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T obj_refine_body_gain_ctrl_16;	//0xF30306D0
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T obj_refine_body_gain_ctrl_17;	//0xF30306D4
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T obj_refine_body_gain_ctrl_18;	//0xF30306D8
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T obj_refine_body_gain_ctrl_19;	//0xF30306DC
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T obj_refine_body_gain_ctrl_20;	//0xF30306E0
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T obj_refine_body_gain_ctrl_21;	//0xF30306E4
	PE_O26F22_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T obj_refine_body_gain_ctrl_22;	//0xF30306E8
 }PE_CHPI_OBC_TBL_O26F22_T;

typedef struct
{
	PE_O26F22_OBE_CTRL_001_T                         reg_obe_ctrl_001;	//0xF3030204
	PE_O26F22_OBE_CTRL_002_T                         reg_obe_ctrl_002;	//0xF3030208
	PE_O26F22_OBE_CTRL_003_T                         reg_obe_ctrl_003;	//0xF303020C
	PE_O26F22_OBE_CTRL_004_T                         reg_obe_ctrl_004;	//0xF3030210
	PE_O26F22_OBE_CTRL_005_T                         reg_obe_ctrl_005;	//0xF3030214
	PE_O26F22_OBE_CTRL_025_T                         reg_obe_ctrl_025;	//0xF3030264
	PE_O26F22_OBE_CTRL_026_T                         reg_obe_ctrl_026;	//0xF3030268
	PE_O26F22_OBE_CTRL_027_T                         reg_obe_ctrl_027;	//0xF303026C
	PE_O26F22_OBE_CTRL_086_T                         reg_obe_ctrl_086;	//0xF3030358
	PE_O26F22_OBE_CTRL_087_T                         reg_obe_ctrl_087;	//0xF303035C
	PE_O26F22_OBE_CTRL_088_T                         reg_obe_ctrl_088;	//0xF3030360
	PE_O26F22_OBE_CTRL_089_T                         reg_obe_ctrl_089;	//0xF3030364
	PE_O26F22_OBE_CTRL_090_T                         reg_obe_ctrl_090;	//0xF3030368
	PE_O26F22_OBE_CTRL_091_T                         reg_obe_ctrl_091;	//0xF303036C
	PE_O26F22_OBE_CTRL_092_T                         reg_obe_ctrl_092;	//0xF3030370
	PE_O26F22_OBE_CTRL_093_T                         reg_obe_ctrl_093;	//0xF3030374
	PE_O26F22_OBE_CTRL_094_T                         reg_obe_ctrl_094;	//0xF3030378
	PE_O26F22_OBE_CTRL_095_T                         reg_obe_ctrl_095;	//0xF303037C
	PE_O26F22_OBE_CTRL_096_T                         reg_obe_ctrl_096;	//0xF3030380
	PE_O26F22_OBE_CTRL_097_T                         reg_obe_ctrl_097;	//0xF3030384
	PE_O26F22_OBE_CTRL_098_T                         reg_obe_ctrl_098;	//0xF3030388
	PE_O26F22_OBE_CTRL_099_T                         reg_obe_ctrl_099;	//0xF303038C
	PE_O26F22_OBE_CTRL_100_T                         reg_obe_ctrl_100;	//0xF3030390
	PE_O26F22_OBE_CTRL_101_T                         reg_obe_ctrl_101;	//0xF3030394
	PE_O26F22_OBE_CTRL_102_T                         reg_obe_ctrl_102;	//0xF3030398
	PE_O26F22_OBE_CTRL_103_T                         reg_obe_ctrl_103;	//0xF303039C
	PE_O26F22_OBE_CTRL_104_T                         reg_obe_ctrl_104;	//0xF30303A0
	PE_O26F22_OBE_CTRL_105_T                         reg_obe_ctrl_105;	//0xF30303A4
	PE_O26F22_OBE_CTRL_106_T                         reg_obe_ctrl_106;	//0xF30303A8
	PE_O26F22_OBE_CTRL_107_T                         reg_obe_ctrl_107;	//0xF30303AC
	PE_O26F22_OBE_CTRL_126_T                         reg_obe_ctrl_126;	//0xF30303F8
	PE_O26F22_OBE_CTRL_127_T                         reg_obe_ctrl_127;	//0xF30303FC
	PE_O26F22_OBE_CTRL_136_T                         reg_obe_ctrl_136;	//0xF3030420
	PE_O26F22_OBE_CTRL_137_T                         reg_obe_ctrl_137;	//0xF3030424
}PE_CHPI_OBE_TBL_O26F22_T;

typedef struct
{
	PE_O26F22_OBE_CTRL_028_T                         reg_obe_ctrl_028;	//0xF3030270
	PE_O26F22_OBE_CTRL_029_T                         reg_obe_ctrl_029;	//0xF3030274
	PE_O26F22_OBE_CTRL_030_T                         reg_obe_ctrl_030;	//0xF3030278
	PE_O26F22_OBE_CTRL_031_T                         reg_obe_ctrl_031;	//0xF303027C
	PE_O26F22_OBE_CTRL_032_T                         reg_obe_ctrl_032;	//0xF3030280
	PE_O26F22_OBE_CTRL_033_T                         reg_obe_ctrl_033;	//0xF3030284
	PE_O26F22_OBE_CTRL_034_T                         reg_obe_ctrl_034;	//0xF3030288
	PE_O26F22_OBE_CTRL_035_T                         reg_obe_ctrl_035;	//0xF303028C
	PE_O26F22_OBE_CTRL_036_T                         reg_obe_ctrl_036;	//0xF3030290
	PE_O26F22_OBE_CTRL_037_T                         reg_obe_ctrl_037;	//0xF3030294
	PE_O26F22_OBE_CTRL_038_T                         reg_obe_ctrl_038;	//0xF3030298
	PE_O26F22_OBE_CTRL_039_T                         reg_obe_ctrl_039;	//0xF303029C
	PE_O26F22_OBE_CTRL_040_T                         reg_obe_ctrl_040;	//0xF30302A0
	PE_O26F22_OBE_CTRL_041_T                         reg_obe_ctrl_041;	//0xF30302A4
	PE_O26F22_OBE_CTRL_042_T                         reg_obe_ctrl_042;	//0xF30302A8
	PE_O26F22_OBE_CTRL_043_T                         reg_obe_ctrl_043;	//0xF30302AC
	PE_O26F22_OBE_CTRL_044_T                         reg_obe_ctrl_044;	//0xF30302B0
	PE_O26F22_OBE_CTRL_045_T                         reg_obe_ctrl_045;	//0xF30302B4
	PE_O26F22_OBE_CTRL_046_T                         reg_obe_ctrl_046;	//0xF30302B8
	PE_O26F22_OBE_CTRL_047_T                         reg_obe_ctrl_047;	//0xF30302BC
	PE_O26F22_OBE_CTRL_048_T                         reg_obe_ctrl_048;	//0xF30302C0
	PE_O26F22_OBE_CTRL_049_T                         reg_obe_ctrl_049;	//0xF30302C4
	PE_O26F22_OBE_CTRL_050_T                         reg_obe_ctrl_050;	//0xF30302C8
	PE_O26F22_OBE_CTRL_051_T                         reg_obe_ctrl_051;	//0xF30302CC
	PE_O26F22_OBE_CTRL_052_T                         reg_obe_ctrl_052;	//0xF30302D0
	PE_O26F22_OBE_CTRL_053_T                         reg_obe_ctrl_053;	//0xF30302D4
	PE_O26F22_OBE_CTRL_054_T                         reg_obe_ctrl_054;	//0xF30302D8
	PE_O26F22_OBE_CTRL_055_T                         reg_obe_ctrl_055;	//0xF30302DC
	PE_O26F22_OBE_CTRL_056_T                         reg_obe_ctrl_056;	//0xF30302E0
	PE_O26F22_OBE_CTRL_057_T                         reg_obe_ctrl_057;	//0xF30302E4
	PE_O26F22_OBE_CTRL_058_T                         reg_obe_ctrl_058;	//0xF30302E8
	PE_O26F22_OBE_CTRL_059_T                         reg_obe_ctrl_059;	//0xF30302EC
	PE_O26F22_OBE_CTRL_060_T                         reg_obe_ctrl_060;	//0xF30302F0
	PE_O26F22_OBE_CTRL_061_T                         reg_obe_ctrl_061;	//0xF30302F4
	PE_O26F22_OBE_CTRL_062_T                         reg_obe_ctrl_062;	//0xF30302F8
	PE_O26F22_OBE_CTRL_063_T                         reg_obe_ctrl_063;	//0xF30302FC
	PE_O26F22_OBE_CTRL_082_T                         reg_obe_ctrl_082;	//0xF3030348
	PE_O26F22_OBE_CTRL_083_T                         reg_obe_ctrl_083;	//0xF303034C
	PE_O26F22_OBE_CTRL_084_T                         reg_obe_ctrl_084;	//0xF3030350
	PE_O26F22_OBE_CTRL_085_T                         reg_obe_ctrl_085;	//0xF3030354
}PE_CHPI_OBE_C_TBL_O26F22_T;

typedef struct
{
	PE_O26F22_AMG0_HEAD_HISTOGRAM_CTRL_00_T                 histogram_ctrl_00;	//0xF3011D20
	PE_O26F22_AMG0_HEAD_HISTOGRAM_CTRL_01_T                 histogram_ctrl_01;	//0xF3011D24
	PE_O26F22_AMG0_HEAD_OBJT_MAP_CTRL_00_T                   objt_map_ctrl_00;	//0xF3011DB0
	PE_O26F22_AMG0_HEAD_OBJT_MAP_CTRL_01_T                   objt_map_ctrl_01;	//0xF3011DB4
	PE_O26F22_AMG0_HEAD_OBJT_MAP_CTRL_02_T                   objt_map_ctrl_02;	//0xF3011DB8
	PE_O26F22_AMG0_HEAD_OBJT_MAP_CTRL_03_T                   objt_map_ctrl_03;	//0xF3011DBC
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_00_T                     ellipse_ctrl_00;	//0xF3011E00
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_01_T                     ellipse_ctrl_01;	//0xF3011E04
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_02_T                     ellipse_ctrl_02;	//0xF3011E08
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_03_T                     ellipse_ctrl_03;	//0xF3011E0C
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_04_T                     ellipse_ctrl_04;	//0xF3011E10
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_05_T                     ellipse_ctrl_05;	//0xF3011E14
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_06_T                     ellipse_ctrl_06;	//0xF3011E18
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_07_T                     ellipse_ctrl_07;	//0xF3011E1C
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_08_T                     ellipse_ctrl_08;	//0xF3011E20
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_09_T                     ellipse_ctrl_09;	//0xF3011E24
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_10_T                     ellipse_ctrl_10;	//0xF3011E28
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_11_T                     ellipse_ctrl_11;	//0xF3011E2C
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_12_T                     ellipse_ctrl_12;	//0xF3011E30
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_13_T                     ellipse_ctrl_13;	//0xF3011E34
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_14_T                     ellipse_ctrl_14;	//0xF3011E38
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_15_T                     ellipse_ctrl_15;	//0xF3011E3C
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_16_T                     ellipse_ctrl_16;	//0xF3011E40
	PE_O26F22_AMG0_HEAD_ELLIPSE_CTRL_17_T                     ellipse_ctrl_17;	//0xF3011E44
	PE_O26F22_AMG0_HEAD_LUT_PROB_CTRL_00_T                   lut_prob_ctrl_00;	//0xF3011E50
	PE_O26F22_AMG0_HEAD_LUT_PROB_CTRL_01_T                   lut_prob_ctrl_01;	//0xF3011E54
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_00_T                           blur_ctrl_00;	//0xF3011E60
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_01_T                           blur_ctrl_01;	//0xF3011E64
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_02_T                           blur_ctrl_02;	//0xF3011E68
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_03_T                           blur_ctrl_03;	//0xF3011E6C
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_04_T                           blur_ctrl_04;	//0xF3011E70
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_05_T                           blur_ctrl_05;	//0xF3011E74
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_06_T                           blur_ctrl_06;	//0xF3011E78
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_07_T                           blur_ctrl_07;	//0xF3011E7C
	PE_O26F22_AMG0_HEAD_BLUR_CTRL_08_T                           blur_ctrl_08;	//0xF3011E80
	PE_O26F22_AMG0_HEAD_IIR_CTRL_00_T                             iir_ctrl_00;	//0xF3011F20
	PE_O26F22_AMG0_HEAD_IIR_CTRL_01_T                             iir_ctrl_01;	//0xF3011F24
	PE_O26F22_AMG0_HEAD_LUT_IIR_CTRL_00_T                     lut_iir_ctrl_00;	//0xF3011F30
	PE_O26F22_AMG0_HEAD_LUT_IIR_CTRL_01_T                     lut_iir_ctrl_01;	//0xF3011F34
	PE_O26F22_AMG0_HEAD_LUT_IIR_CTRL_02_T                     lut_iir_ctrl_02;	//0xF3011F38
	PE_O26F22_AMG1_BODY_HISTOGRAM_CTRL_00_T                 body_histogram_ctrl_00;	//0xF3012020
	PE_O26F22_AMG1_BODY_HISTOGRAM_CTRL_01_T                 body_histogram_ctrl_01;	//0xF3012024
	PE_O26F22_AMG1_BODY_OBJT_MAP_CTRL_00_T                   body_objt_map_ctrl_00;	//0xF30120B0
	PE_O26F22_AMG1_BODY_OBJT_MAP_CTRL_01_T                   body_objt_map_ctrl_01;	//0xF30120B4
	PE_O26F22_AMG1_BODY_OBJT_MAP_CTRL_02_T                   body_objt_map_ctrl_02;	//0xF30120B8
	PE_O26F22_AMG1_BODY_OBJT_MAP_CTRL_03_T                   body_objt_map_ctrl_03;	//0xF30120BC
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_00_T                     body_ellipse_ctrl_00;	//0xF3012100
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_01_T                     body_ellipse_ctrl_01;	//0xF3012104
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_02_T                     body_ellipse_ctrl_02;	//0xF3012108
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_03_T                     body_ellipse_ctrl_03;	//0xF301210C
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_04_T                     body_ellipse_ctrl_04;	//0xF3012110
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_05_T                     body_ellipse_ctrl_05;	//0xF3012114
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_06_T                     body_ellipse_ctrl_06;	//0xF3012118
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_07_T                     body_ellipse_ctrl_07;	//0xF301211C
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_08_T                     body_ellipse_ctrl_08;	//0xF3012120
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_09_T                     body_ellipse_ctrl_09;	//0xF3012124
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_10_T                     body_ellipse_ctrl_10;	//0xF3012128
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_11_T                     body_ellipse_ctrl_11;	//0xF301212C
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_12_T                     body_ellipse_ctrl_12;	//0xF3012130
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_13_T                     body_ellipse_ctrl_13;	//0xF3012134
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_14_T                     body_ellipse_ctrl_14;	//0xF3012138
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_15_T                     body_ellipse_ctrl_15;	//0xF301213C
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_16_T                     body_ellipse_ctrl_16;	//0xF3012140
	PE_O26F22_AMG1_BODY_ELLIPSE_CTRL_17_T                     body_ellipse_ctrl_17;	//0xF3012144
	PE_O26F22_AMG1_BODY_LUT_PROB_CTRL_00_T                   body_lut_prob_ctrl_00;	//0xF3012150
	PE_O26F22_AMG1_BODY_LUT_PROB_CTRL_01_T                   body_lut_prob_ctrl_01;	//0xF3012154
	PE_O26F22_AMG1_BODY_BLUR_CTRL_00_T                           body_blur_ctrl_00;	//0xF3012160
	PE_O26F22_AMG1_BODY_BLUR_CTRL_01_T                           body_blur_ctrl_01;	//0xF3012164
	PE_O26F22_AMG1_BODY_BLUR_CTRL_02_T                           body_blur_ctrl_02;	//0xF3012168
	PE_O26F22_AMG1_BODY_BLUR_CTRL_03_T                           body_blur_ctrl_03;	//0xF301216C
	PE_O26F22_AMG1_BODY_BLUR_CTRL_04_T                           body_blur_ctrl_04;	//0xF3012170
	PE_O26F22_AMG1_BODY_BLUR_CTRL_05_T                           body_blur_ctrl_05;	//0xF3012174
	PE_O26F22_AMG1_BODY_BLUR_CTRL_06_T                           body_blur_ctrl_06;	//0xF3012178
	PE_O26F22_AMG1_BODY_BLUR_CTRL_07_T                           body_blur_ctrl_07;	//0xF301217C
	PE_O26F22_AMG1_BODY_BLUR_CTRL_08_T                           body_blur_ctrl_08;	//0xF3012180
	PE_O26F22_AMG1_BODY_LUT_DEPTH_CTRL_00_T                 body_lut_depth_ctrl_00;	//0xF3012190
	PE_O26F22_AMG1_BODY_LUT_DEPTH_CTRL_01_T                 body_lut_depth_ctrl_01;	//0xF3012194
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_00_T             body_region_gain_ctrl_00;	//0xF30121A0
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_01_T             body_region_gain_ctrl_01;	//0xF30121A4
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_02_T             body_region_gain_ctrl_02;	//0xF30121A8
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_03_T             body_region_gain_ctrl_03;	//0xF30121AC
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_04_T             body_region_gain_ctrl_04;	//0xF30121B0
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_05_T             body_region_gain_ctrl_05;	//0xF30121B4
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_06_T             body_region_gain_ctrl_06;	//0xF30121B8
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_07_T             body_region_gain_ctrl_07;	//0xF30121BC
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_08_T             body_region_gain_ctrl_08;	//0xF30121C0
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_09_T             body_region_gain_ctrl_09;	//0xF30121C4
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_10_T             body_region_gain_ctrl_10;	//0xF30121C8
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_11_T             body_region_gain_ctrl_11;	//0xF30121CC
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_12_T             body_region_gain_ctrl_12;	//0xF30121D0
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_13_T             body_region_gain_ctrl_13;	//0xF30121D4
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_14_T             body_region_gain_ctrl_14;	//0xF30121D8
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_15_T             body_region_gain_ctrl_15;	//0xF30121DC
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_16_T             body_region_gain_ctrl_16;	//0xF30121E0
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_17_T             body_region_gain_ctrl_17;	//0xF30121E4
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_18_T             body_region_gain_ctrl_18;	//0xF30121E8
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_19_T             body_region_gain_ctrl_19;	//0xF30121EC
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_20_T             body_region_gain_ctrl_20;	//0xF30121F0
	PE_O26F22_AMG1_BODY_REGION_GAIN_CTRL_21_T             body_region_gain_ctrl_21;	//0xF30121F4
	PE_O26F22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_00_T         body_lut_depth_iir_ctrl_00;	//0xF3012200
	PE_O26F22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_01_T         body_lut_depth_iir_ctrl_01;	//0xF3012204
	PE_O26F22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_02_T         body_lut_depth_iir_ctrl_02;	//0xF3012208
	PE_O26F22_AMG1_BODY_LUT_DEPTH_IIR_CTRL_03_T         body_lut_depth_iir_ctrl_03;	//0xF301220C
	PE_O26F22_AMG1_BODY_LUT_BLD_CTRL_00_T                     body_lut_bld_ctrl_00;	//0xF3012210
	PE_O26F22_AMG1_BODY_LUT_BLD_CTRL_01_T                     body_lut_bld_ctrl_01;	//0xF3012214
	PE_O26F22_AMG1_BODY_LUT_BLD_CTRL_02_T                     body_lut_bld_ctrl_02;	//0xF3012218
	PE_O26F22_AMG1_BODY_LUT_BLD_CTRL_03_T                     body_lut_bld_ctrl_03;	//0xF301221C
	PE_O26F22_AMG1_BODY_IIR_CTRL_00_T                             body_iir_ctrl_00;	//0xF3012220
	PE_O26F22_AMG1_BODY_IIR_CTRL_01_T                             body_iir_ctrl_01;	//0xF3012224
	PE_O26F22_AMG1_BODY_LUT_IIR_CTRL_00_T                     body_lut_iir_ctrl_00;	//0xF3012230
	PE_O26F22_AMG1_BODY_LUT_IIR_CTRL_01_T                     body_lut_iir_ctrl_01;	//0xF3012234
	PE_O26F22_AMG1_BODY_LUT_IIR_CTRL_02_T                     body_lut_iir_ctrl_02;	//0xF3012238
}PE_CHPI_AMG_TBL_O26F22_T;


//see PE_DDR_O26_DRC_CUV_T
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
}PE_CHPI_DRC_CUV_O26F22_T;
#endif
