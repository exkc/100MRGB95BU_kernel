#ifndef _PE_SRE_REG_E60A0_H_
#define _PE_SRE_REG_E60A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC901D400 RW
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//4:4	//SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//5:5	//SHP core bypass enable
	UINT32 resvd1                           :6;
	UINT32 reg_top_mode_3d                  :1;	//12:12	//Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd2                           :19;
	};
}REG_SHC_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D404 RW
	UINT32 reg_top_width                    :12;	//11:0	//processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//27:16	//processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D408 RW
	UINT32 reg_top_use_extern_valid         :1;	//0:0	//Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//1:1	//Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//31:16	//Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}REG_SHC_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D800 RW
	UINT32 reg_cdj_edf_en                   :1;	//0:0	//edge-directional de-jagging enable
	UINT32 reg_cdj_hv_filter_en             :1;	//1:1	//H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_cdj_edge_adaptive_en         :1;	//3:3	//edge adaptive filter enable
	UINT32 reg_cdj_line_variation_mode      :1;	//4:4	//0: sum of (cur - center)	1:  sum of adjacent pixel difference
	UINT32 reg_cdj_l_type_protection        :1;	//5:5	//L-type protection
	UINT32 reg_cdj_soft_en                  :1;	//6:6	//Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_cdj_count_diff_th            :5;	//12:8	//matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_cdj_output_mux               :3;	//18:16	//000: normal display	001: direction map	010: g0: feature (matchness)	011: g0 : gain	100: g1 : gain (protection)	101: final gain	110: blur coring map( used for blur-filtering)
	UINT32 reg_cdj_buffer_detour_en         :1;	//19:19	//dj buffer detour enable
	UINT32 reg_cdj_center_blur_mode         :2;	//21:20	//center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_cdj_n_avg_mode               :1;	//22:22	//neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_cdj_detour_en                :1;	//23:23	//dejagging detour enable
	UINT32 reg_cdj_line_variation_diff_th   :8;	//31:24	//line-variation threshold for edge-direction decision
	};
}REG_SHC_SHP_CDJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D804 RW
	UINT32 reg_cdj_level_th                 :8;	//7:0	//g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_cdj_n_avg_gain               :8;	//23:16	//neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}REG_SHC_SHP_CDJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D808 RW
	UINT32 reg_cdj_g0_cnt_min               :5;	//4:0	//g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_cdj_g0_mul                   :5;	//12:8	//g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}REG_SHC_SHP_CDJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D80C RW
	UINT32 reg_cdj_g1_protect_min           :8;	//7:0	//g1: Min diff th - LR Diff
	UINT32 reg_cdj_g1_mul                   :7;	//14:8	//g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_cdj_edge_min                 :8;	//23:16	//edge adaptive filter min value
	UINT32 reg_cdj_edge_mul                 :8;	//31:24	//edge adaptive filter multiplication value
	};
}REG_SHC_SHP_CDJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D810 RW
	UINT32 reg_cdj_dir_sel_c1               :1;	//0:0	//DJ core directional sel, 1
	UINT32 reg_cdj_dir_sel_c2               :1;	//1:1	//DJ core directional sel, 2
	UINT32 reg_cdj_dir_sel_c3               :1;	//2:2	//DJ core directional sel, 3
	UINT32 reg_cdj_dir_sel_c4               :1;	//3:3	//DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}REG_SHC_SHP_CDJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D814 RW
	UINT32 reg_cdj_pattern0_0_00            :2;	//1:0	//DJ protect pattern0 [0][0]
	UINT32 reg_cdj_pattern0_0_01            :2;	//3:2	//DJ protect pattern0 [0][1]
	UINT32 reg_cdj_pattern0_0_02            :2;	//5:4	//DJ protect pattern0 [0][2]
	UINT32 reg_cdj_pattern0_0_03            :2;	//7:6	//DJ protect pattern0 [0][3]
	UINT32 reg_cdj_pattern0_0_04            :2;	//9:8	//DJ protect pattern0 [0][4]
	UINT32 reg_cdj_pattern0_0_05            :2;	//11:10	//DJ protect pattern0 [0][5]
	UINT32 reg_cdj_pattern0_0_06            :2;	//13:12	//DJ protect pattern0 [0][6]
	UINT32 reg_cdj_pattern0_0_07            :2;	//15:14	//DJ protect pattern0 [0][7]
	UINT32 reg_cdj_pattern0_0_08            :2;	//17:16	//DJ protect pattern0 [0][8]
	UINT32 reg_cdj_pattern0_0_09            :2;	//19:18	//DJ protect pattern0 [0][9]
	UINT32 reg_cdj_pattern0_0_10            :2;	//21:20	//DJ protect pattern0 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D818 RW
	UINT32 reg_cdj_pattern0_1_00            :2;	//1:0	//DJ protect pattern0 [1][0]
	UINT32 reg_cdj_pattern0_1_01            :2;	//3:2	//DJ protect pattern0 [1][1]
	UINT32 reg_cdj_pattern0_1_02            :2;	//5:4	//DJ protect pattern0 [1][2]
	UINT32 reg_cdj_pattern0_1_03            :2;	//7:6	//DJ protect pattern0 [1][3]
	UINT32 reg_cdj_pattern0_1_04            :2;	//9:8	//DJ protect pattern0 [1][4]
	UINT32 reg_cdj_pattern0_1_05            :2;	//11:10	//DJ protect pattern0 [1][5]
	UINT32 reg_cdj_pattern0_1_06            :2;	//13:12	//DJ protect pattern0 [1][6]
	UINT32 reg_cdj_pattern0_1_07            :2;	//15:14	//DJ protect pattern0 [1][7]
	UINT32 reg_cdj_pattern0_1_08            :2;	//17:16	//DJ protect pattern0 [1][8]
	UINT32 reg_cdj_pattern0_1_09            :2;	//19:18	//DJ protect pattern0 [1][9]
	UINT32 reg_cdj_pattern0_1_10            :2;	//21:20	//DJ protect pattern0 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D81C RW
	UINT32 reg_cdj_pattern0_2_00            :2;	//1:0	//DJ protect pattern0 [2][0]
	UINT32 reg_cdj_pattern0_2_01            :2;	//3:2	//DJ protect pattern0 [2][1]
	UINT32 reg_cdj_pattern0_2_02            :2;	//5:4	//DJ protect pattern0 [2][2]
	UINT32 reg_cdj_pattern0_2_03            :2;	//7:6	//DJ protect pattern0 [2][3]
	UINT32 reg_cdj_pattern0_2_04            :2;	//9:8	//DJ protect pattern0 [2][4]
	UINT32 reg_cdj_pattern0_2_05            :2;	//11:10	//DJ protect pattern0 [2][5]
	UINT32 reg_cdj_pattern0_2_06            :2;	//13:12	//DJ protect pattern0 [2][6]
	UINT32 reg_cdj_pattern0_2_07            :2;	//15:14	//DJ protect pattern0 [2][7]
	UINT32 reg_cdj_pattern0_2_08            :2;	//17:16	//DJ protect pattern0 [2][8]
	UINT32 reg_cdj_pattern0_2_09            :2;	//19:18	//DJ protect pattern0 [2][9]
	UINT32 reg_cdj_pattern0_2_10            :2;	//21:20	//DJ protect pattern0 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D820 RW
	UINT32 reg_cdj_pattern0_3_00            :2;	//1:0	//DJ protect pattern0 [3][0]
	UINT32 reg_cdj_pattern0_3_01            :2;	//3:2	//DJ protect pattern0 [3][1]
	UINT32 reg_cdj_pattern0_3_02            :2;	//5:4	//DJ protect pattern0 [3][2]
	UINT32 reg_cdj_pattern0_3_03            :2;	//7:6	//DJ protect pattern0 [3][3]
	UINT32 reg_cdj_pattern0_3_04            :2;	//9:8	//DJ protect pattern0 [3][4]
	UINT32 reg_cdj_pattern0_3_05            :2;	//11:10	//DJ protect pattern0 [3][5]
	UINT32 reg_cdj_pattern0_3_06            :2;	//13:12	//DJ protect pattern0 [3][6]
	UINT32 reg_cdj_pattern0_3_07            :2;	//15:14	//DJ protect pattern0 [3][7]
	UINT32 reg_cdj_pattern0_3_08            :2;	//17:16	//DJ protect pattern0 [3][8]
	UINT32 reg_cdj_pattern0_3_09            :2;	//19:18	//DJ protect pattern0 [3][9]
	UINT32 reg_cdj_pattern0_3_10            :2;	//21:20	//DJ protect pattern0 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D824 RW
	UINT32 reg_cdj_pattern0_4_00            :2;	//1:0	//DJ protect pattern0 [4][0]
	UINT32 reg_cdj_pattern0_4_01            :2;	//3:2	//DJ protect pattern0 [4][1]
	UINT32 reg_cdj_pattern0_4_02            :2;	//5:4	//DJ protect pattern0 [4][2]
	UINT32 reg_cdj_pattern0_4_03            :2;	//7:6	//DJ protect pattern0 [4][3]
	UINT32 reg_cdj_pattern0_4_04            :2;	//9:8	//DJ protect pattern0 [4][4]
	UINT32 reg_cdj_pattern0_4_05            :2;	//11:10	//DJ protect pattern0 [4][5]
	UINT32 reg_cdj_pattern0_4_06            :2;	//13:12	//DJ protect pattern0 [4][6]
	UINT32 reg_cdj_pattern0_4_07            :2;	//15:14	//DJ protect pattern0 [4][7]
	UINT32 reg_cdj_pattern0_4_08            :2;	//17:16	//DJ protect pattern0 [4][8]
	UINT32 reg_cdj_pattern0_4_09            :2;	//19:18	//DJ protect pattern0 [4][9]
	UINT32 reg_cdj_pattern0_4_10            :2;	//21:20	//DJ protect pattern0 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D828 RW
	UINT32 reg_cdj_pattern0_5_00            :2;	//1:0	//DJ protect pattern0 [5][0]
	UINT32 reg_cdj_pattern0_5_01            :2;	//3:2	//DJ protect pattern0 [5][1]
	UINT32 reg_cdj_pattern0_5_02            :2;	//5:4	//DJ protect pattern0 [5][2]
	UINT32 reg_cdj_pattern0_5_03            :2;	//7:6	//DJ protect pattern0 [5][3]
	UINT32 reg_cdj_pattern0_5_04            :2;	//9:8	//DJ protect pattern0 [5][4]
	UINT32 reg_cdj_pattern0_5_05            :2;	//11:10	//DJ protect pattern0 [5][5]
	UINT32 reg_cdj_pattern0_5_06            :2;	//13:12	//DJ protect pattern0 [5][6]
	UINT32 reg_cdj_pattern0_5_07            :2;	//15:14	//DJ protect pattern0 [5][7]
	UINT32 reg_cdj_pattern0_5_08            :2;	//17:16	//DJ protect pattern0 [5][8]
	UINT32 reg_cdj_pattern0_5_09            :2;	//19:18	//DJ protect pattern0 [5][9]
	UINT32 reg_cdj_pattern0_5_10            :2;	//21:20	//DJ protect pattern0 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D82C RW
	UINT32 reg_cdj_pattern0_6_00            :2;	//1:0	//DJ protect pattern0 [6][0]
	UINT32 reg_cdj_pattern0_6_01            :2;	//3:2	//DJ protect pattern0 [6][1]
	UINT32 reg_cdj_pattern0_6_02            :2;	//5:4	//DJ protect pattern0 [6][2]
	UINT32 reg_cdj_pattern0_6_03            :2;	//7:6	//DJ protect pattern0 [6][3]
	UINT32 reg_cdj_pattern0_6_04            :2;	//9:8	//DJ protect pattern0 [6][4]
	UINT32 reg_cdj_pattern0_6_05            :2;	//11:10	//DJ protect pattern0 [6][5]
	UINT32 reg_cdj_pattern0_6_06            :2;	//13:12	//DJ protect pattern0 [6][6]
	UINT32 reg_cdj_pattern0_6_07            :2;	//15:14	//DJ protect pattern0 [6][7]
	UINT32 reg_cdj_pattern0_6_08            :2;	//17:16	//DJ protect pattern0 [6][8]
	UINT32 reg_cdj_pattern0_6_09            :2;	//19:18	//DJ protect pattern0 [6][9]
	UINT32 reg_cdj_pattern0_6_10            :2;	//21:20	//DJ protect pattern0 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D830 RW
	UINT32 reg_cdj_pattern0_flip0_h         :1;	//0:0	//DJ protect pattern0 flip0, H
	UINT32 reg_cdj_pattern0_flip0_v         :1;	//1:1	//DJ protect pattern0 flip0, V
	UINT32 reg_cdj_pattern0_flip1_h         :1;	//2:2	//DJ protect pattern0 flip1, H
	UINT32 reg_cdj_pattern0_flip1_v         :1;	//3:3	//DJ protect pattern0 flip1, V
	UINT32 reg_cdj_pattern0_flip2_h         :1;	//4:4	//DJ protect pattern0 flip2, H
	UINT32 reg_cdj_pattern0_flip2_v         :1;	//5:5	//DJ protect pattern0 flip2, V
	UINT32 reg_cdj_pattern0_flip3_h         :1;	//6:6	//DJ protect pattern0 flip3, H
	UINT32 reg_cdj_pattern0_flip3_v         :1;	//7:7	//DJ protect pattern0 flip3, V
	UINT32 resvd                            :24;
	};
}REG_SHC_SHP_CDJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D834 RW
	UINT32 reg_cdj_pattern1_0_00            :2;	//1:0	//DJ protect pattern1 [0][0]
	UINT32 reg_cdj_pattern1_0_01            :2;	//3:2	//DJ protect pattern1 [0][1]
	UINT32 reg_cdj_pattern1_0_02            :2;	//5:4	//DJ protect pattern1 [0][2]
	UINT32 reg_cdj_pattern1_0_03            :2;	//7:6	//DJ protect pattern1 [0][3]
	UINT32 reg_cdj_pattern1_0_04            :2;	//9:8	//DJ protect pattern1 [0][4]
	UINT32 reg_cdj_pattern1_0_05            :2;	//11:10	//DJ protect pattern1 [0][5]
	UINT32 reg_cdj_pattern1_0_06            :2;	//13:12	//DJ protect pattern1 [0][6]
	UINT32 reg_cdj_pattern1_0_07            :2;	//15:14	//DJ protect pattern1 [0][7]
	UINT32 reg_cdj_pattern1_0_08            :2;	//17:16	//DJ protect pattern1 [0][8]
	UINT32 reg_cdj_pattern1_0_09            :2;	//19:18	//DJ protect pattern1 [0][9]
	UINT32 reg_cdj_pattern1_0_10            :2;	//21:20	//DJ protect pattern1 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D838 RW
	UINT32 reg_cdj_pattern1_1_00            :2;	//1:0	//DJ protect pattern1 [1][0]
	UINT32 reg_cdj_pattern1_1_01            :2;	//3:2	//DJ protect pattern1 [1][1]
	UINT32 reg_cdj_pattern1_1_02            :2;	//5:4	//DJ protect pattern1 [1][2]
	UINT32 reg_cdj_pattern1_1_03            :2;	//7:6	//DJ protect pattern1 [1][3]
	UINT32 reg_cdj_pattern1_1_04            :2;	//9:8	//DJ protect pattern1 [1][4]
	UINT32 reg_cdj_pattern1_1_05            :2;	//11:10	//DJ protect pattern1 [1][5]
	UINT32 reg_cdj_pattern1_1_06            :2;	//13:12	//DJ protect pattern1 [1][6]
	UINT32 reg_cdj_pattern1_1_07            :2;	//15:14	//DJ protect pattern1 [1][7]
	UINT32 reg_cdj_pattern1_1_08            :2;	//17:16	//DJ protect pattern1 [1][8]
	UINT32 reg_cdj_pattern1_1_09            :2;	//19:18	//DJ protect pattern1 [1][9]
	UINT32 reg_cdj_pattern1_1_10            :2;	//21:20	//DJ protect pattern1 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D83C RW
	UINT32 reg_cdj_pattern1_2_00            :2;	//1:0	//DJ protect pattern1 [2][0]
	UINT32 reg_cdj_pattern1_2_01            :2;	//3:2	//DJ protect pattern1 [2][1]
	UINT32 reg_cdj_pattern1_2_02            :2;	//5:4	//DJ protect pattern1 [2][2]
	UINT32 reg_cdj_pattern1_2_03            :2;	//7:6	//DJ protect pattern1 [2][3]
	UINT32 reg_cdj_pattern1_2_04            :2;	//9:8	//DJ protect pattern1 [2][4]
	UINT32 reg_cdj_pattern1_2_05            :2;	//11:10	//DJ protect pattern1 [2][5]
	UINT32 reg_cdj_pattern1_2_06            :2;	//13:12	//DJ protect pattern1 [2][6]
	UINT32 reg_cdj_pattern1_2_07            :2;	//15:14	//DJ protect pattern1 [2][7]
	UINT32 reg_cdj_pattern1_2_08            :2;	//17:16	//DJ protect pattern1 [2][8]
	UINT32 reg_cdj_pattern1_2_09            :2;	//19:18	//DJ protect pattern1 [2][9]
	UINT32 reg_cdj_pattern1_2_10            :2;	//21:20	//DJ protect pattern1 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D840 RW
	UINT32 reg_cdj_pattern1_3_00            :2;	//1:0	//DJ protect pattern1 [3][0]
	UINT32 reg_cdj_pattern1_3_01            :2;	//3:2	//DJ protect pattern1 [3][1]
	UINT32 reg_cdj_pattern1_3_02            :2;	//5:4	//DJ protect pattern1 [3][2]
	UINT32 reg_cdj_pattern1_3_03            :2;	//7:6	//DJ protect pattern1 [3][3]
	UINT32 reg_cdj_pattern1_3_04            :2;	//9:8	//DJ protect pattern1 [3][4]
	UINT32 reg_cdj_pattern1_3_05            :2;	//11:10	//DJ protect pattern1 [3][5]
	UINT32 reg_cdj_pattern1_3_06            :2;	//13:12	//DJ protect pattern1 [3][6]
	UINT32 reg_cdj_pattern1_3_07            :2;	//15:14	//DJ protect pattern1 [3][7]
	UINT32 reg_cdj_pattern1_3_08            :2;	//17:16	//DJ protect pattern1 [3][8]
	UINT32 reg_cdj_pattern1_3_09            :2;	//19:18	//DJ protect pattern1 [3][9]
	UINT32 reg_cdj_pattern1_3_10            :2;	//21:20	//DJ protect pattern1 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D844 RW
	UINT32 reg_cdj_pattern1_4_00            :2;	//1:0	//DJ protect pattern1 [4][0]
	UINT32 reg_cdj_pattern1_4_01            :2;	//3:2	//DJ protect pattern1 [4][1]
	UINT32 reg_cdj_pattern1_4_02            :2;	//5:4	//DJ protect pattern1 [4][2]
	UINT32 reg_cdj_pattern1_4_03            :2;	//7:6	//DJ protect pattern1 [4][3]
	UINT32 reg_cdj_pattern1_4_04            :2;	//9:8	//DJ protect pattern1 [4][4]
	UINT32 reg_cdj_pattern1_4_05            :2;	//11:10	//DJ protect pattern1 [4][5]
	UINT32 reg_cdj_pattern1_4_06            :2;	//13:12	//DJ protect pattern1 [4][6]
	UINT32 reg_cdj_pattern1_4_07            :2;	//15:14	//DJ protect pattern1 [4][7]
	UINT32 reg_cdj_pattern1_4_08            :2;	//17:16	//DJ protect pattern1 [4][8]
	UINT32 reg_cdj_pattern1_4_09            :2;	//19:18	//DJ protect pattern1 [4][9]
	UINT32 reg_cdj_pattern1_4_10            :2;	//21:20	//DJ protect pattern1 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D848 RW
	UINT32 reg_cdj_pattern1_5_00            :2;	//1:0	//DJ protect pattern1 [5][0]
	UINT32 reg_cdj_pattern1_5_01            :2;	//3:2	//DJ protect pattern1 [5][1]
	UINT32 reg_cdj_pattern1_5_02            :2;	//5:4	//DJ protect pattern1 [5][2]
	UINT32 reg_cdj_pattern1_5_03            :2;	//7:6	//DJ protect pattern1 [5][3]
	UINT32 reg_cdj_pattern1_5_04            :2;	//9:8	//DJ protect pattern1 [5][4]
	UINT32 reg_cdj_pattern1_5_05            :2;	//11:10	//DJ protect pattern1 [5][5]
	UINT32 reg_cdj_pattern1_5_06            :2;	//13:12	//DJ protect pattern1 [5][6]
	UINT32 reg_cdj_pattern1_5_07            :2;	//15:14	//DJ protect pattern1 [5][7]
	UINT32 reg_cdj_pattern1_5_08            :2;	//17:16	//DJ protect pattern1 [5][8]
	UINT32 reg_cdj_pattern1_5_09            :2;	//19:18	//DJ protect pattern1 [5][9]
	UINT32 reg_cdj_pattern1_5_10            :2;	//21:20	//DJ protect pattern1 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D84C RW
	UINT32 reg_cdj_pattern1_6_00            :2;	//1:0	//DJ protect pattern1 [6][0]
	UINT32 reg_cdj_pattern1_6_01            :2;	//3:2	//DJ protect pattern1 [6][1]
	UINT32 reg_cdj_pattern1_6_02            :2;	//5:4	//DJ protect pattern1 [6][2]
	UINT32 reg_cdj_pattern1_6_03            :2;	//7:6	//DJ protect pattern1 [6][3]
	UINT32 reg_cdj_pattern1_6_04            :2;	//9:8	//DJ protect pattern1 [6][4]
	UINT32 reg_cdj_pattern1_6_05            :2;	//11:10	//DJ protect pattern1 [6][5]
	UINT32 reg_cdj_pattern1_6_06            :2;	//13:12	//DJ protect pattern1 [6][6]
	UINT32 reg_cdj_pattern1_6_07            :2;	//15:14	//DJ protect pattern1 [6][7]
	UINT32 reg_cdj_pattern1_6_08            :2;	//17:16	//DJ protect pattern1 [6][8]
	UINT32 reg_cdj_pattern1_6_09            :2;	//19:18	//DJ protect pattern1 [6][9]
	UINT32 reg_cdj_pattern1_6_10            :2;	//21:20	//DJ protect pattern1 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D850 RW
	UINT32 reg_cdj_pattern1_flip0_h         :1;	//0:0	//DJ protect pattern1 flip0, H
	UINT32 reg_cdj_pattern1_flip0_v         :1;	//1:1	//DJ protect pattern1 flip0, V
	UINT32 reg_cdj_pattern1_flip1_h         :1;	//2:2	//DJ protect pattern1 flip1, H
	UINT32 reg_cdj_pattern1_flip1_v         :1;	//3:3	//DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}REG_SHC_SHP_CDJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D854 RW
	UINT32 reg_cdj_pattern2_0_00            :2;	//1:0	//DJ protect pattern2 [0][0]
	UINT32 reg_cdj_pattern2_0_01            :2;	//3:2	//DJ protect pattern2 [0][1]
	UINT32 reg_cdj_pattern2_0_02            :2;	//5:4	//DJ protect pattern2 [0][2]
	UINT32 reg_cdj_pattern2_0_03            :2;	//7:6	//DJ protect pattern2 [0][3]
	UINT32 reg_cdj_pattern2_0_04            :2;	//9:8	//DJ protect pattern2 [0][4]
	UINT32 reg_cdj_pattern2_0_05            :2;	//11:10	//DJ protect pattern2 [0][5]
	UINT32 reg_cdj_pattern2_0_06            :2;	//13:12	//DJ protect pattern2 [0][6]
	UINT32 reg_cdj_pattern2_0_07            :2;	//15:14	//DJ protect pattern2 [0][7]
	UINT32 reg_cdj_pattern2_0_08            :2;	//17:16	//DJ protect pattern2 [0][8]
	UINT32 reg_cdj_pattern2_0_09            :2;	//19:18	//DJ protect pattern2 [0][9]
	UINT32 reg_cdj_pattern2_0_10            :2;	//21:20	//DJ protect pattern2 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D858 RW
	UINT32 reg_cdj_pattern2_1_00            :2;	//1:0	//DJ protect pattern2 [1][0]
	UINT32 reg_cdj_pattern2_1_01            :2;	//3:2	//DJ protect pattern2 [1][1]
	UINT32 reg_cdj_pattern2_1_02            :2;	//5:4	//DJ protect pattern2 [1][2]
	UINT32 reg_cdj_pattern2_1_03            :2;	//7:6	//DJ protect pattern2 [1][3]
	UINT32 reg_cdj_pattern2_1_04            :2;	//9:8	//DJ protect pattern2 [1][4]
	UINT32 reg_cdj_pattern2_1_05            :2;	//11:10	//DJ protect pattern2 [1][5]
	UINT32 reg_cdj_pattern2_1_06            :2;	//13:12	//DJ protect pattern2 [1][6]
	UINT32 reg_cdj_pattern2_1_07            :2;	//15:14	//DJ protect pattern2 [1][7]
	UINT32 reg_cdj_pattern2_1_08            :2;	//17:16	//DJ protect pattern2 [1][8]
	UINT32 reg_cdj_pattern2_1_09            :2;	//19:18	//DJ protect pattern2 [1][9]
	UINT32 reg_cdj_pattern2_1_10            :2;	//21:20	//DJ protect pattern2 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D85C RW
	UINT32 reg_cdj_pattern2_2_00            :2;	//1:0	//DJ protect pattern2 [2][0]
	UINT32 reg_cdj_pattern2_2_01            :2;	//3:2	//DJ protect pattern2 [2][1]
	UINT32 reg_cdj_pattern2_2_02            :2;	//5:4	//DJ protect pattern2 [2][2]
	UINT32 reg_cdj_pattern2_2_03            :2;	//7:6	//DJ protect pattern2 [2][3]
	UINT32 reg_cdj_pattern2_2_04            :2;	//9:8	//DJ protect pattern2 [2][4]
	UINT32 reg_cdj_pattern2_2_05            :2;	//11:10	//DJ protect pattern2 [2][5]
	UINT32 reg_cdj_pattern2_2_06            :2;	//13:12	//DJ protect pattern2 [2][6]
	UINT32 reg_cdj_pattern2_2_07            :2;	//15:14	//DJ protect pattern2 [2][7]
	UINT32 reg_cdj_pattern2_2_08            :2;	//17:16	//DJ protect pattern2 [2][8]
	UINT32 reg_cdj_pattern2_2_09            :2;	//19:18	//DJ protect pattern2 [2][9]
	UINT32 reg_cdj_pattern2_2_10            :2;	//21:20	//DJ protect pattern2 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D860 RW
	UINT32 reg_cdj_pattern2_3_00            :2;	//1:0	//DJ protect pattern2 [3][0]
	UINT32 reg_cdj_pattern2_3_01            :2;	//3:2	//DJ protect pattern2 [3][1]
	UINT32 reg_cdj_pattern2_3_02            :2;	//5:4	//DJ protect pattern2 [3][2]
	UINT32 reg_cdj_pattern2_3_03            :2;	//7:6	//DJ protect pattern2 [3][3]
	UINT32 reg_cdj_pattern2_3_04            :2;	//9:8	//DJ protect pattern2 [3][4]
	UINT32 reg_cdj_pattern2_3_05            :2;	//11:10	//DJ protect pattern2 [3][5]
	UINT32 reg_cdj_pattern2_3_06            :2;	//13:12	//DJ protect pattern2 [3][6]
	UINT32 reg_cdj_pattern2_3_07            :2;	//15:14	//DJ protect pattern2 [3][7]
	UINT32 reg_cdj_pattern2_3_08            :2;	//17:16	//DJ protect pattern2 [3][8]
	UINT32 reg_cdj_pattern2_3_09            :2;	//19:18	//DJ protect pattern2 [3][9]
	UINT32 reg_cdj_pattern2_3_10            :2;	//21:20	//DJ protect pattern2 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D864 RW
	UINT32 reg_cdj_pattern2_4_00            :2;	//1:0	//DJ protect pattern2 [4][0]
	UINT32 reg_cdj_pattern2_4_01            :2;	//3:2	//DJ protect pattern2 [4][1]
	UINT32 reg_cdj_pattern2_4_02            :2;	//5:4	//DJ protect pattern2 [4][2]
	UINT32 reg_cdj_pattern2_4_03            :2;	//7:6	//DJ protect pattern2 [4][3]
	UINT32 reg_cdj_pattern2_4_04            :2;	//9:8	//DJ protect pattern2 [4][4]
	UINT32 reg_cdj_pattern2_4_05            :2;	//11:10	//DJ protect pattern2 [4][5]
	UINT32 reg_cdj_pattern2_4_06            :2;	//13:12	//DJ protect pattern2 [4][6]
	UINT32 reg_cdj_pattern2_4_07            :2;	//15:14	//DJ protect pattern2 [4][7]
	UINT32 reg_cdj_pattern2_4_08            :2;	//17:16	//DJ protect pattern2 [4][8]
	UINT32 reg_cdj_pattern2_4_09            :2;	//19:18	//DJ protect pattern2 [4][9]
	UINT32 reg_cdj_pattern2_4_10            :2;	//21:20	//DJ protect pattern2 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D868 RW
	UINT32 reg_cdj_pattern2_5_00            :2;	//1:0	//DJ protect pattern2 [5][0]
	UINT32 reg_cdj_pattern2_5_01            :2;	//3:2	//DJ protect pattern2 [5][1]
	UINT32 reg_cdj_pattern2_5_02            :2;	//5:4	//DJ protect pattern2 [5][2]
	UINT32 reg_cdj_pattern2_5_03            :2;	//7:6	//DJ protect pattern2 [5][3]
	UINT32 reg_cdj_pattern2_5_04            :2;	//9:8	//DJ protect pattern2 [5][4]
	UINT32 reg_cdj_pattern2_5_05            :2;	//11:10	//DJ protect pattern2 [5][5]
	UINT32 reg_cdj_pattern2_5_06            :2;	//13:12	//DJ protect pattern2 [5][6]
	UINT32 reg_cdj_pattern2_5_07            :2;	//15:14	//DJ protect pattern2 [5][7]
	UINT32 reg_cdj_pattern2_5_08            :2;	//17:16	//DJ protect pattern2 [5][8]
	UINT32 reg_cdj_pattern2_5_09            :2;	//19:18	//DJ protect pattern2 [5][9]
	UINT32 reg_cdj_pattern2_5_10            :2;	//21:20	//DJ protect pattern2 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D86C RW
	UINT32 reg_cdj_pattern2_6_00            :2;	//1:0	//DJ protect pattern2 [6][0]
	UINT32 reg_cdj_pattern2_6_01            :2;	//3:2	//DJ protect pattern2 [6][1]
	UINT32 reg_cdj_pattern2_6_02            :2;	//5:4	//DJ protect pattern2 [6][2]
	UINT32 reg_cdj_pattern2_6_03            :2;	//7:6	//DJ protect pattern2 [6][3]
	UINT32 reg_cdj_pattern2_6_04            :2;	//9:8	//DJ protect pattern2 [6][4]
	UINT32 reg_cdj_pattern2_6_05            :2;	//11:10	//DJ protect pattern2 [6][5]
	UINT32 reg_cdj_pattern2_6_06            :2;	//13:12	//DJ protect pattern2 [6][6]
	UINT32 reg_cdj_pattern2_6_07            :2;	//15:14	//DJ protect pattern2 [6][7]
	UINT32 reg_cdj_pattern2_6_08            :2;	//17:16	//DJ protect pattern2 [6][8]
	UINT32 reg_cdj_pattern2_6_09            :2;	//19:18	//DJ protect pattern2 [6][9]
	UINT32 reg_cdj_pattern2_6_10            :2;	//21:20	//DJ protect pattern2 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHC_SHP_CDJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D870 RW
	UINT32 reg_cdj_pattern2_flip0_h         :1;	//0:0	//DJ protect pattern2 flip0, H
	UINT32 reg_cdj_pattern2_flip0_v         :1;	//1:1	//DJ protect pattern2 flip0, V
	UINT32 reg_cdj_pattern2_flip1_h         :1;	//2:2	//DJ protect pattern2 flip1, H
	UINT32 reg_cdj_pattern2_flip1_v         :1;	//3:3	//DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}REG_SHC_SHP_CDJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D874 RW
	UINT32 reg_cdj_soft_g0_mul              :6;	//5:0	//Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g0_offset           :5;	//12:8	//Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g0_max              :8;	//23:16	//Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}REG_SHC_SHP_CDJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D878 RW
	UINT32 reg_cdj_soft_g1_mul              :6;	//5:0	//Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g1_offset           :5;	//12:8	//Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g1_max              :8;	//23:16	//Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}REG_SHC_SHP_CDJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D87C RW
	UINT32 reg_cdj_soft_g2_mul              :6;	//5:0	//Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_cdj_soft_g2_offset           :5;	//12:8	//Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_cdj_soft_g2_max              :8;	//23:16	//Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}REG_SHC_SHP_CDJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D880 RW
	UINT32 reg_cdj_soft_base                :8;	//7:0	//Soft DJ base
	UINT32 reg_cdj_soft_sel_1357_gain       :8;	//15:8	//Soft DJ 1357 gain penalty
	UINT32 reg_cdj_soft_single_match_en     :1;	//16:16	//Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}REG_SHC_SHP_CDJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D890 RW
	UINT32 reg_cdir_blur_detour             :1;	//0:0	//dir blur enable
	UINT32 resvd0                           :3;
	UINT32 reg_cdir_blur_buf_detour         :1;	//4:4	//dir blur buffer detour enable
	UINT32 resvd1                           :3;
	UINT32 reg_cdir_blur_en                 :1;	//8:8	//dir blur enable
	UINT32 resvd2                           :23;
	};
}REG_SHC_SHP_CDIR_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D894 RW
	UINT32 reg_cdir_blur_base               :8;	//7:0	//dir blur base
	UINT32 resvd0                           :8;
	UINT32 reg_cdir_blur_gain               :8;	//23:16	//dir blur gain
	UINT32 resvd1                           :8;
	};
}REG_SHC_SHP_CDIR_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D8A0 RW
	UINT32 reg_win_cdj_win0_en              :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_cdj_win1_en              :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_cdj_win01_en             :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_cdj_win_outside          :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_cdj_win_en               :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_cdj_bdr_alpha            :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_cdj_bdr_wid              :2;	//14:13	//border width
	UINT32 reg_win_cdj_bdr_en               :1;	//15:15	//border enable
	UINT32 reg_win_cdj_cr5                  :5;	//20:16	//border color: cr5
	UINT32 reg_win_cdj_cb5                  :5;	//25:21	//border color: cb5
	UINT32 reg_win_cdj_yy6                  :6;	//31:26	//border color: yy6
	};
}REG_SHC_SHP_CDJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D8A4 RW
	UINT32 reg_win_cdj_win_w0_x0            :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w0_y0            :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CDJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D8A8 RW
	UINT32 reg_win_cdj_win_w0_x1            :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w0_y1            :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CDJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D8AC RW
	UINT32 reg_win_cdj_win_w1_x0            :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w1_y0            :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CDJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901D8B0 RW
	UINT32 reg_win_cdj_win_w1_x1            :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_cdj_win_w1_y1            :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CDJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DA00 RO
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//11:0	//Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//27:16	//Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DA04 RO
	UINT32 reg_mon_in_vert_cnt              :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DA08 RO
	UINT32 reg_mon_out_vert_cnt             :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DA0C RO
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}REG_SHC_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DA10 RO
	UINT32 reg_mon_shp_i_sucfail            :32;	//31:0	//Input success/fail monitoring register
	};
}REG_SHC_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DA14 RO
	UINT32 reg_mon_shp_o_sucfail            :32;	//31:0	//Output success/fail monitoring register
	};
}REG_SHC_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DAF0 RW
	UINT32 tdata0                           :32;
	};
}REG_SHC_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DAF4 RW
	UINT32 tdata0                           :32;
	};
}REG_SHC_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DAF8 RW
	UINT32 tdata0                           :32;
	};
}REG_SHC_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901DAFC RW
	UINT32 tdata0                           :32;
	};
}REG_SHC_SHP_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B800 RW
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//4:4	//SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//5:5	//SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//8:8	//0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//12:12	//Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}REG_SHY_4K_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B804 RW
	UINT32 reg_top_width                    :12;	//11:0	//processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//27:16	//processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B808 RW
	UINT32 reg_top_use_extern_valid         :1;	//0:0	//Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//1:1	//Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//31:16	//Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}REG_SHY_4K_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B80C RW
	UINT32 reg_top_prefetch_cnt             :12;	//11:0	//Pre-fetch counter
	UINT32 resvd0                           :4;
	UINT32 reg_top_flush_cnt                :12;	//27:16	//Flush counter
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B840 RW
	UINT32 reg_pat_en                       :1;	//0:0	//pattern enable
	UINT32 reg_pat_thickness                :2;	//2:1	//pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//15:8	//pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}REG_SHY_4K_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B8F0 RW
	UINT32 reg_dp_debug_display             :4;	//3:0	//0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map
	UINT32 reg_dp_detour_en                 :1;	//4:4	//dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//8:8	//dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}REG_SHY_4K_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B900 RW
	UINT32 reg_fd_a_map_h_size              :2;	//1:0	//A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//8:8	//post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//18:16	//pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//20:19	//pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//23:21	//pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}REG_SHY_4K_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B904 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B908 RW
	UINT32 reg_fd_detail_beta_mul           :8;	//7:0	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//15:8	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//23:16	//get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//31:24	//get_t_map (alpha*t_map - beta*a_map)
	};
}REG_SHY_4K_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B90C RW
	UINT32 reg_fd_a_lut_edge_y0             :8;	//7:0	//A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//15:8	//A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//23:16	//A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//31:24	//A-map edge LUT, x1
	};
}REG_SHY_4K_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B910 RW
	UINT32 reg_fd_a_lut_detail_y0           :8;	//7:0	//A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//15:8	//A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//23:16	//A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//31:24	//A-map detail LUT, x1
	};
}REG_SHY_4K_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B914 RW
	UINT32 reg_fd_t_lut_edge_y0             :8;	//7:0	//T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//15:8	//T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//23:16	//T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//31:24	//T-map edge LUT, x1
	};
}REG_SHY_4K_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B918 RW
	UINT32 reg_fd_t_lut_detail_y0           :8;	//7:0	//T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//15:8	//T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//23:16	//T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//31:24	//T-map detail LUT, x1
	};
}REG_SHY_4K_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B91C RW
	UINT32 reg_fd_edge_minmax_y0            :8;	//7:0	//Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//15:8	//Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//23:16	//Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//31:24	//Final edge LUT, x1
	};
}REG_SHY_4K_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B920 RW
	UINT32 reg_fd_edge_minmax_y2            :8;	//7:0	//Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//15:8	//Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//23:16	//Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//31:24	//Final edge LUT, x3
	};
}REG_SHY_4K_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B924 RW
	UINT32 reg_fd_detail_minmax_y0          :8;	//7:0	//Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//15:8	//Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//23:16	//Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//31:24	//Final detail LUT, x1
	};
}REG_SHY_4K_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B928 RW
	UINT32 reg_fd_detail_minmax_y2          :8;	//7:0	//Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//15:8	//Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//23:16	//Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//31:24	//Final detail LUT, x3
	};
}REG_SHY_4K_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B92C RW
	UINT32 reg_fd_mnr_gain_e_en             :1;	//0:0	//edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//1:1	//texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//5:4	//s1 h expand
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B930 RW
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//7:0	//s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//23:16	//s1 ratio max
	UINT32 resvd1                           :8;
	};
}REG_SHY_4K_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B934 RW
	UINT32 reg_fd_mnr_gain_x0               :8;	//7:0	//MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//15:8	//MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//23:16	//MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//31:24	//MNR gain LUT, y1
	};
}REG_SHY_4K_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B938 RW
	UINT32 reg_fd_dct_t_lut_y0              :8;	//7:0	//DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//15:8	//DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//23:16	//DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//31:24	//DCT T-map LUT, x1
	};
}REG_SHY_4K_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B93C RW
	UINT32 reg_fd_dct_t_lut_y2              :8;	//7:0	//DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//15:8	//DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//23:16	//DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//31:24	//DCT T-map LUT, x3
	};
}REG_SHY_4K_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B940 RW
	UINT32 reg_fd_dct_t_lut_y4              :8;	//7:0	//DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//15:8	//DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//23:16	//DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//31:24	//DCT T-map LUT, x5
	};
}REG_SHY_4K_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B944 RW
	UINT32 reg_fd_soft_gain_e_en            :1;	//0:0	//Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//1:1	//Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}REG_SHY_4K_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B948 RW
	UINT32 reg_fd_soft_ratio                :8;	//7:0	//Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//15:8	//Soft edge offset
	UINT32 resvd                            :16;
	};
}REG_SHY_4K_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B94C RW
	UINT32 reg_fd_soft_score_x0             :8;	//7:0	//Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//15:8	//Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//23:16	//Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//31:24	//Soft edge score, x3
	};
}REG_SHY_4K_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B950 RW
	UINT32 reg_fd_soft_score_y0             :6;	//5:0	//Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//13:8	//Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//21:16	//Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//29:24	//Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}REG_SHY_4K_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B954 RW
	UINT32 reg_fd_flat_input_sel            :2;	//1:0	//input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//4:4	//1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//8:8	//1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}REG_SHY_4K_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B958 RW
	UINT32 reg_fd_flat_lut_y0               :8;	//7:0	//Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//15:8	//Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//23:16	//Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//31:24	//Flat region LUT, x1
	};
}REG_SHY_4K_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B960 RW
	UINT32 reg_mp_shp_en                    :1;	//0:0	//MP enable
	UINT32 resvd                            :31;
	};
}REG_SHY_4K_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B964 RW
	UINT32 reg_mp_im_os_gain                :7;	//6:0	//im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//14:8	//im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//23:16	//im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//31:24	//im gain v
	};
}REG_SHY_4K_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B968 RW
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 resvd1                           :16;
	};
}REG_SHY_4K_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B96C RW
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//7:4	//Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//11:8	//Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//15:12	//Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//23:20	//Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//27:24	//Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//31:28	//Laplacian gain h 3
	};
}REG_SHY_4K_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B970 RW
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//11:8	//display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}REG_SHY_4K_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B974 RW
	UINT32 reg_mp_gb_en                     :1;	//0:0	//0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//4:4	//delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//15:8	//gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 resvd2                           :8;
	};
}REG_SHY_4K_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B978 RW
	UINT32 reg_mp_gb_x2                     :8;	//7:0	//gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//15:8	//gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 resvd                            :8;
	};
}REG_SHY_4K_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B97C RW
	UINT32 reg_mp_lum1_x_l0                 :8;	//7:0	//level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//15:8	//level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//23:16	//level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//31:24	//level-balancing, lum1_x_H1
	};
}REG_SHY_4K_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B980 RW
	UINT32 reg_mp_lum1_y0                   :8;	//7:0	//level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//15:8	//level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//23:16	//level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//31:24	//level-balancing, lum2_x_L0
	};
}REG_SHY_4K_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B984 RW
	UINT32 reg_mp_lum2_x_l1                 :8;	//7:0	//level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//15:8	//level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//23:16	//level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//31:24	//level-balancing, lum2_y0
	};
}REG_SHY_4K_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B988 RW
	UINT32 reg_mp_lum2_y1                   :8;	//7:0	//level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//15:8	//level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}REG_SHY_4K_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B98C RW
	UINT32 reg_mp_coring_en                 :1;	//0:0	//[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//2:1	//[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B990 RW
	UINT32 reg_mp_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_4K_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B994 RW
	UINT32 reg_apl_iir_en                   :1;	//0:0	//APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//15:8	//APL gain
	UINT32 resvd1                           :16;
	};
}REG_SHY_4K_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9A0 RW
	UINT32 reg_lc_shp_en                      :1 ;	// 0:0
	UINT32 reserved01                         :3 ;	// reserved
	UINT32 reg_lc_gb_en                       :1 ;	// 4:4
	UINT32 reserved02                         :3 ;	// reserved
	UINT32 reg_lc_center_target             :8;	//15:8	//center target
	UINT32 reg_lc_center_gain               :8;	//23:16	//center gain
	UINT32 reg_lc_local_gain                :8;	//31:24	//local gain
	};
}REG_SHY_4K_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9A4 RW
	UINT32 reg_lc_gb_y2                     :8;	//7:0	//gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//15:8	//gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//31:24	//gain balancing, x1
	};
}REG_SHY_4K_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9A8 RW
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//31:24	//gain balancing, x3
	};
}REG_SHY_4K_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9AC RW
	UINT32 reg_lc_coring_en                 :1;	//0:0	//[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//2:1	//[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9B0 RW
	UINT32 reg_lc_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_4K_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9C0 RW
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//13:8	//reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//21:16	//reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//30:24	//reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//31:31	//reg_th_manual_en
	};
}REG_SHY_4K_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9C4 RW
	UINT32 reg_derh_bflt_tap_size           :3;	//2:0	//bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//24:24	//reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//27:26	//edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//31:31	//edge_Y_filter en
	};
}REG_SHY_4K_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9C8 RW
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//13:8	//edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//21:16	//edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}REG_SHY_4K_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9CC RW
	UINT32 reg_derv_en                      :1;	//0:0	//der-v enable
	UINT32 resvd0                           :2;
	UINT32 reg_derv_bif_en                  :1;	//3:3	//0: disable BiF	1: enable BiF
	UINT32 reg_derv_output_mux              :4;	//7:4	//0xxx: normal display	1000: vertical ringing measure	1001: gain adjusted by curve mapping	101x: bilateral filter output	o.w : not used
	UINT32 reg_derv_bif_manual_th           :8;	//15:8	//bilateral filter threshold
	UINT32 reg_derv_th_gain                 :6;	//21:16	//auto threshold gain, th = th_gain * A
	UINT32 resvd1                           :2;
	UINT32 reg_derv_th_mode                 :1;	//24:24	//th mode	0: auto(A-map)	1: manual
	UINT32 resvd2                           :7;
	};
}REG_SHY_4K_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9D0 RW
	UINT32 reg_derv_csft_gain               :6;	//5:0	//center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//8:8	//center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}REG_SHY_4K_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9D4 RW
	UINT32 reg_derv_gain_b                  :7;	//6:0	//gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//14:8	//gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}REG_SHY_4K_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9D8 RW
	UINT32 reg_der_a_lut_y0                 :8;	//7:0	//A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//15:8	//A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//23:16	//A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//31:24	//A-map for der LUT, x1
	};
}REG_SHY_4K_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9DC RW
	UINT32 reg_der_a_lut_y2                 :8;	//7:0	//A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//15:8	//A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//23:16	//A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//31:24	//A-map for de-rining LUT, x3
	};
}REG_SHY_4K_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9E0 RW
	UINT32 reg_sp_shp_en                    :1;	//0:0	//SP enable
	UINT32 resvd                            :31;
	};
}REG_SHY_4K_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9E4 RW
	UINT32 reg_sp_im_os_gain                :7;	//6:0	//im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//14:8	//im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//23:16	//im gain h
	UINT32 resvd2                           :8;
	};
}REG_SHY_4K_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9E8 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 resvd1                           :16;
	};
}REG_SHY_4K_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9EC RW
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//23:20	//Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//27:24	//Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//31:28	//Laplacian gain h 3
	};
}REG_SHY_4K_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9F0 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//11:8	//display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}REG_SHY_4K_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9F4 RW
	UINT32 reg_sp_gb_en                     :1;	//0:0	//0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//4:4	//delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//15:8	//gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 resvd2                           :8;
	};
}REG_SHY_4K_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9F8 RW
	UINT32 reg_sp_gb_x2                     :8;	//7:0	//gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//15:8	//gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 resvd                            :8;
	};
}REG_SHY_4K_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B9FC RW
	UINT32 reg_sp_lum1_x_l0                 :8;	//7:0	//level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//15:8	//level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//23:16	//level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//31:24	//level-balancing, lum1_x_H1
	};
}REG_SHY_4K_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA00 RW
	UINT32 reg_sp_lum1_y0                   :8;	//7:0	//level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//15:8	//level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//23:16	//level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//31:24	//level-balancing, lum2_x_L0
	};
}REG_SHY_4K_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA04 RW
	UINT32 reg_sp_lum2_x_l1                 :8;	//7:0	//level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//15:8	//level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//23:16	//level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//31:24	//level-balancing, lum2_y0
	};
}REG_SHY_4K_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA08 RW
	UINT32 reg_sp_lum2_y1                   :8;	//7:0	//level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//15:8	//level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}REG_SHY_4K_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA0C RW
	UINT32 reg_sp_coring_en                 :1;	//0:0	//[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//2:1	//[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA10 RW
	UINT32 reg_sp_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_4K_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA20 RW
	UINT32 reg_ptiv_enable                  :1;	//0:0	//PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//3:2	//mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//5:4	//avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//6:6	//ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//15:8	//master gain
	UINT32 resvd2                           :16;
	};
}REG_SHY_4K_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA24 RW
	UINT32 reg_ptih_enable                  :1;	//0:0	//PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//3:2	//mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//5:4	//avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//6:6	//ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//15:8	//master gain
	UINT32 resvd2                           :16;
	};
}REG_SHY_4K_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA28 RW
	UINT32 reg_pti_coring_en                :1;	//0:0	//[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//2:1	//[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA2C RW
	UINT32 reg_pti_coring_gain_e_b          :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_4K_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA30 RW
	UINT32 reg_sti_enable                   :1;	//0:0	//STI enable
	UINT32 reg_sti_debug_map_en             :1;	//1:1	//debug map enable
	UINT32 reg_sti_mm_tap_size              :2;	//3:2	//mm tap size
	UINT32 reg_sti_avg_tap_size             :2;	//5:4	//avg tap size
	UINT32 reg_sti_ti_mode                  :1;	//6:6	//ti mode
	UINT32 resvd                            :1;
	UINT32 reg_sti_master_gain              :8;	//15:8	//master gain
	UINT32 reg_sti_texture_gain             :8;	//23:16	//texture gain
	UINT32 reg_sti_edge_gain                :8;	//31:24	//edge gain
	};
}REG_SHY_4K_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA40 RW
	UINT32 reg_tgen_on_off                  :1;	//0:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_initial_seed_mode       :1;	//4:4	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_dbg_en                  :1;	//8:8	//
	UINT32 resvd2                           :7;
	UINT32 reg_tgen_table_sel               :4;	//19:16	//
	UINT32 resvd3                           :4;
	UINT32 reg_tgen_master_gain             :8;	//31:24	//
	};
}REG_SHY_4K_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA44 RW
	UINT32 reg_tgen_delta_h_bound           :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//26:24	//
	UINT32 resvd3                           :5;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA48 RW
	UINT32 reg_tgen_rnd_th                  :8;	//7:0	//
	UINT32 reg_tgen_delta_wcurr             :4;	//11:8	//
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//21:16	//
	UINT32 resvd1                           :10;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA4C RW
	UINT32 reg_tgen_rand_init_val_c0        :32;	//31:0	//
	};
}REG_SHY_4K_SHP_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA50 RW
	UINT32 reg_tgen_rand_init_val_c1        :32;	//31:0	//
	};
}REG_SHY_4K_SHP_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA54 RW
	UINT32 reg_tgen_dr_ratio                :3;	//2:0	//
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//13:8	//
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//20:16	//
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//25:24	//
	UINT32 resvd3                           :6;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA58 RW
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//20:16	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//28:24	//
	UINT32 resvd2                           :3;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA5C RW
	UINT32 reg_tgen_blur_coef_x2            :6;	//5:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//13:8	//
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA60 RW
	UINT32 reg_tgen_blur_coef_y2            :6;	//5:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//13:8	//
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA64 RW
	UINT32 reg_tgen_map_edge_gain           :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//23:16	//
	UINT32 reg_tgen_gs_noise                :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA68 RW
	UINT32 reg_tgen_gain7                   :4;	//3:0	//
	UINT32 reg_tgen_gain6                   :4;	//7:4	//
	UINT32 reg_tgen_gain5                   :4;	//11:8	//
	UINT32 reg_tgen_gain4                   :4;	//15:12	//
	UINT32 reg_tgen_gain3                   :4;	//19:16	//
	UINT32 reg_tgen_gain2                   :4;	//23:20	//
	UINT32 reg_tgen_gain1                   :4;	//27:24	//
	UINT32 reg_tgen_gain0                   :4;	//31:28	//
	};
}REG_SHY_4K_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA6C RW
	UINT32 reg_tgen_coring_en               :1;	//0:0	//[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//2:1	//[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA70 RW
	UINT32 reg_tgen_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_4K_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA74 RW
	UINT32 reg_snr_blur_en                  :1;	//0:0	//SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//5:4	//filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//15:8	//Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//18:16	//SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}REG_SHY_4K_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA80 RW
	UINT32 reg_dctp_en                      :1;	//0:0	//DCT peaking enable
	UINT32 resvd                            :31;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA84 RW
	UINT32 reg_dctp_filt0_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA88 RW
	UINT32 reg_dctp_filt0_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA8C RW
	UINT32 reg_dctp_filt0_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA90 RW
	UINT32 reg_dctp_filt0_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA94 RW
	UINT32 reg_dctp_filt1_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA98 RW
	UINT32 reg_dctp_filt1_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BA9C RW
	UINT32 reg_dctp_filt1_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAA0 RW
	UINT32 reg_dctp_filt1_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAA4 RW
	UINT32 reg_dctp_filt2_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAA8 RW
	UINT32 reg_dctp_filt2_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAAC RW
	UINT32 reg_dctp_filt2_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAB0 RW
	UINT32 reg_dctp_filt2_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAB4 RW
	UINT32 reg_dctp_filt3_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAB8 RW
	UINT32 reg_dctp_filt3_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BABC RW
	UINT32 reg_dctp_filt3_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAC0 RW
	UINT32 reg_dctp_filt3_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAC4 RW
	UINT32 reg_dctp_filt4_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAC8 RW
	UINT32 reg_dctp_filt4_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BACC RW
	UINT32 reg_dctp_filt4_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAD0 RW
	UINT32 reg_dctp_filt4_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAD4 RW
	UINT32 reg_dctp_filt5_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAD8 RW
	UINT32 reg_dctp_filt5_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BADC RW
	UINT32 reg_dctp_filt5_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAE0 RW
	UINT32 reg_dctp_filt5_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAE4 RW
	UINT32 reg_dctp_text_lut_x0             :8;	//7:0	//DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//15:8	//DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//23:16	//DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//31:24	//DCT peaking texture LUT point, x3
	};
}REG_SHY_4K_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAE8 RW
	UINT32 reg_dctp_text_lut_x4             :8;	//7:0	//DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//15:8	//DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAEC RW
	UINT32 reg_dctp_edge_lut_y0             :8;	//7:0	//DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//15:8	//DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//23:16	//DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//31:24	//DCT peaking edge LUT point, x1
	};
}REG_SHY_4K_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAF0 RW
	UINT32 reg_dctp_edge_lut_y2             :8;	//7:0	//DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//15:8	//DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//23:16	//DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//31:24	//DCT peaking edge LUT point, x3
	};
}REG_SHY_4K_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAF4 RW
	UINT32 reg_dctp_gain                    :8;	//7:0	//DCT peaking master gain
	UINT32 resvd                            :24;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAF8 RW
	UINT32 reg_dctp_coring_en               :1;	//0:0	//[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//2:1	//[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BAFC RW
	UINT32 reg_dctp_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_4K_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB00 RW
	UINT32 reg_nntg_en                      :1;	//0:0	//4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//5:4	//4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB04 RW
	UINT32 reg_nntg_lsfr_init_1st_c0        :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB08 RW
	UINT32 reg_nntg_lsfr_init_2nd_c0        :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB0C RW
	UINT32 reg_nntg_lsfr_init_3rd_c0        :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB10 RW
	UINT32 reg_nntg_lsfr_init_4th_c0        :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB14 RW
	UINT32 reg_nntg_lsfr_init_5th_c0        :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB18 RW
	UINT32 reg_nntg_lsfr_init_1st_c1        :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB1C RW
	UINT32 reg_nntg_lsfr_init_2nd_c1        :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB20 RW
	UINT32 reg_nntg_lsfr_init_3rd_c1        :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB24 RW
	UINT32 reg_nntg_lsfr_init_4th_c1        :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB28 RW
	UINT32 reg_nntg_lsfr_init_5th_c1        :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
}REG_SHY_4K_SHP_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB2C RW
	UINT32 reg_nntg_rand_ratio              :8;	//7:0	//4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//14:8	//4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//23:16	//4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}REG_SHY_4K_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB30 RW
	UINT32 reg_nntg_rand_coef_g00           :4;	//3:0	//4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//7:4	//4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//11:8	//4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//19:16	//4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//23:20	//4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//27:24	//4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB34 RW
	UINT32 reg_nntg_rand_coef_g20           :4;	//3:0	//4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//7:4	//4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//11:8	//4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//19:16	//4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//23:20	//4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//27:24	//4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB38 RW
	UINT32 reg_nntg_nano_coef_g10           :4;	//3:0	//4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//7:4	//4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//11:8	//4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//19:16	//4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//23:20	//4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//27:24	//4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB3C RW
	UINT32 reg_nntg_diff_lut_y0             :8;	//7:0	//4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//15:8	//4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//23:16	//4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//31:24	//4K nano-noise diff LUT point, x1
	};
}REG_SHY_4K_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB40 RW
	UINT32 reg_nntg_diff_lut_y2             :8;	//7:0	//4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//15:8	//4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//23:16	//4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//31:24	//4K nano-noise diff LUT point, x3
	};
}REG_SHY_4K_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB44 RW
	UINT32 reg_nntg_edge_lut_y0             :8;	//7:0	//4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//15:8	//4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//23:16	//4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//31:24	//4K nano-noise edge LUT point, x1
	};
}REG_SHY_4K_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB48 RW
	UINT32 reg_nntg_edge_lut_y2             :8;	//7:0	//4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//15:8	//4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//23:16	//4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//31:24	//4K nano-noise edge LUT point, x3
	};
}REG_SHY_4K_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB4C RW
	UINT32 reg_nntg_random_gain             :8;	//7:0	//4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//15:8	//4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//23:16	//4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//31:24	//4K nano-noise denoise gain
	};
}REG_SHY_4K_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB50 RW
	UINT32 reg_nntg_coring_en               :1;	//0:0	//[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//2:1	//[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_4K_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB54 RW
	UINT32 reg_nntg_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_4K_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB60 RW
	UINT32 reg_dp_sum_gain                  :8;	//7:0	//DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//9:8	//0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}REG_SHY_4K_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB64 RW
	UINT32 reg_dp_sum_lut_y0                :8;	//7:0	//dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//15:8	//dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//23:16	//dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//31:24	//dp_sum LUT for delta control, x1
	};
}REG_SHY_4K_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BB68 RW
	UINT32 reg_dp_sum_lut_y2                :8;	//7:0	//dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//15:8	//dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//23:16	//dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//31:24	//dp_sum LUT for delta control, x3
	};
}REG_SHY_4K_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBA0 RW
	UINT32 reg_win_dp_win0_en               :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_dp_win1_en               :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_dp_win01_en              :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dp_win_outside           :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_dp_win_en                :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_dp_bdr_alpha             :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_dp_bdr_wid               :2;	//14:13	//border width
	UINT32 reg_win_dp_bdr_en                :1;	//15:15	//border enable
	UINT32 reg_win_dp_cr5                   :5;	//20:16	//border color: cr5
	UINT32 reg_win_dp_cb5                   :5;	//25:21	//border color: cb5
	UINT32 reg_win_dp_yy6                   :6;	//31:26	//border color: yy6
	};
}REG_SHY_4K_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBA4 RW
	UINT32 reg_win_dp_win_w0_x0             :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBA8 RW
	UINT32 reg_win_dp_win_w0_x1             :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBAC RW
	UINT32 reg_win_dp_win_w1_x0             :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBB0 RW
	UINT32 reg_win_dp_win_w1_x1             :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBC0 RW
	UINT32 reg_region_text_en               :1;	//0:0	//region texture enable
	UINT32 resvd0                           :3;
	UINT32 reg_region_text_cutres           :3;	//6:4	//
	UINT32 resvd1                           :1;
	UINT32 reg_region_text_add_offset       :8;	//15:8	//
	UINT32 reg_region_text_add_max          :8;	//23:16	//
	UINT32 reg_region_text_cuthif           :3;	//26:24	//
	UINT32 resvd2                           :5;
	};
}REG_SHY_4K_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBC4 RW
	UINT32 reg_region_text_lut_y0           :8;	//7:0	//region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//15:8	//region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//23:16	//region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//31:24	//region texture LUT , x1
	};
}REG_SHY_4K_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBC8 RW
	UINT32 reg_region_text_lut_y2           :8;	//7:0	//region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//15:8	//region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//23:16	//region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//31:24	//region texture LUT , x3
	};
}REG_SHY_4K_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBCC RW
	UINT32 reg_tmap_temp_iir_en             :1;	//0:0	//TMAP temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//4:4	//TMAP temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//15:8	//TMAP temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//24:24	//TMAP temporal process status selection	0 : original tmap status	1 : iir tmap status
	UINT32 resvd3                           :7;
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBD0 RW
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//7:0	//tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//15:8	//tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//23:16	//tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//31:24	//tmap temporal previous blend LUT , x1
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBD4 RW
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//7:0	//tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//15:8	//tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//23:16	//tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//31:24	//tmap temporal previous blend LUT , x3
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBD8 RW
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//7:0	//tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//15:8	//tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//23:16	//tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//31:24	//tmap temporal iir positive LUT , x1
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBDC RW
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//7:0	//tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//15:8	//tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//23:16	//tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//31:24	//tmap temporal iir positive LUT , x3
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBE0 RW
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//7:0	//tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//15:8	//tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//23:16	//tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//31:24	//tmap temporal iir positive LUT , x5
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBE4 RW
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//7:0	//tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//15:8	//tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//23:16	//tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//31:24	//tmap temporal iir negative LUT , x1
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBE8 RW
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//7:0	//tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//15:8	//tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//23:16	//tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//31:24	//tmap temporal iir negative LUT , x3
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBEC RW
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//7:0	//tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//15:8	//tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//23:16	//tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//31:24	//tmap temporal iir negative LUT , x5
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBF0 RW
	UINT32 reg_tmap_stat_win0_start_x       :12;	//11:0	//tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//27:16	//tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBF4 RW
	UINT32 reg_tmap_stat_win0_end_x         :12;	//11:0	//tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//27:16	//tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBF8 RW
	UINT32 reg_tmap_stat_win1_start_x       :12;	//11:0	//tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//27:16	//tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BBFC RW
	UINT32 reg_tmap_stat_win1_end_x         :12;	//11:0	//tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//27:16	//tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC00 RW
	UINT32 reg_dj_edf_en                    :1;	//0:0	//edge-directional de-jagging enable
	UINT32 reg_dj_hv_filter_en              :1;	//1:1	//H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_dj_edge_adaptive_en          :1;	//3:3	//edge adaptive filter enable
	UINT32 reg_dj_line_variation_mode       :1;	//4:4	//0: sum of (cur - center)	1:  sum of adjacent pixel difference
	UINT32 reg_dj_l_type_protection         :1;	//5:5	//L-type protection
	UINT32 reg_dj_soft_en                   :1;	//6:6	//Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_dj_count_diff_th             :5;	//12:8	//matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_dj_output_mux                :3;	//18:16	//000: normal display	001: direction map	010: g0: feature (matchness)	011: g0 : gain	100: g1 : gain (protection)	101: final gain	110: blur coring map( used for blur-filtering)
	UINT32 reg_dj_buffer_detour_en          :1;	//19:19	//dj buffer detour enable
	UINT32 reg_dj_center_blur_mode          :2;	//21:20	//center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_dj_n_avg_mode                :1;	//22:22	//neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_dj_detour_en                 :1;	//23:23	//dejagging detour enable
	UINT32 reg_dj_line_variation_diff_th    :8;	//31:24	//line-variation threshold for edge-direction decision
	};
}REG_SHY_4K_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC04 RW
	UINT32 reg_dj_level_th                  :8;	//7:0	//g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//23:16	//neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}REG_SHY_4K_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC08 RW
	UINT32 reg_dj_g0_cnt_min                :5;	//4:0	//g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//12:8	//g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}REG_SHY_4K_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC0C RW
	UINT32 reg_dj_g1_protect_min            :8;	//7:0	//g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//14:8	//g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//23:16	//edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//31:24	//edge adaptive filter multiplication value
	};
}REG_SHY_4K_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC10 RW
	UINT32 reg_dj_dir_sel_c1                :1;	//0:0	//DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//1:1	//DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//2:2	//DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//3:3	//DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}REG_SHY_4K_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC14 RW
	UINT32 reg_dj_pattern0_0_00             :2;	//1:0	//DJ protect pattern0 [0][0]
	UINT32 reg_dj_pattern0_0_01             :2;	//3:2	//DJ protect pattern0 [0][1]
	UINT32 reg_dj_pattern0_0_02             :2;	//5:4	//DJ protect pattern0 [0][2]
	UINT32 reg_dj_pattern0_0_03             :2;	//7:6	//DJ protect pattern0 [0][3]
	UINT32 reg_dj_pattern0_0_04             :2;	//9:8	//DJ protect pattern0 [0][4]
	UINT32 reg_dj_pattern0_0_05             :2;	//11:10	//DJ protect pattern0 [0][5]
	UINT32 reg_dj_pattern0_0_06             :2;	//13:12	//DJ protect pattern0 [0][6]
	UINT32 reg_dj_pattern0_0_07             :2;	//15:14	//DJ protect pattern0 [0][7]
	UINT32 reg_dj_pattern0_0_08             :2;	//17:16	//DJ protect pattern0 [0][8]
	UINT32 reg_dj_pattern0_0_09             :2;	//19:18	//DJ protect pattern0 [0][9]
	UINT32 reg_dj_pattern0_0_10             :2;	//21:20	//DJ protect pattern0 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC18 RW
	UINT32 reg_dj_pattern0_1_00             :2;	//1:0	//DJ protect pattern0 [1][0]
	UINT32 reg_dj_pattern0_1_01             :2;	//3:2	//DJ protect pattern0 [1][1]
	UINT32 reg_dj_pattern0_1_02             :2;	//5:4	//DJ protect pattern0 [1][2]
	UINT32 reg_dj_pattern0_1_03             :2;	//7:6	//DJ protect pattern0 [1][3]
	UINT32 reg_dj_pattern0_1_04             :2;	//9:8	//DJ protect pattern0 [1][4]
	UINT32 reg_dj_pattern0_1_05             :2;	//11:10	//DJ protect pattern0 [1][5]
	UINT32 reg_dj_pattern0_1_06             :2;	//13:12	//DJ protect pattern0 [1][6]
	UINT32 reg_dj_pattern0_1_07             :2;	//15:14	//DJ protect pattern0 [1][7]
	UINT32 reg_dj_pattern0_1_08             :2;	//17:16	//DJ protect pattern0 [1][8]
	UINT32 reg_dj_pattern0_1_09             :2;	//19:18	//DJ protect pattern0 [1][9]
	UINT32 reg_dj_pattern0_1_10             :2;	//21:20	//DJ protect pattern0 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC1C RW
	UINT32 reg_dj_pattern0_2_00             :2;	//1:0	//DJ protect pattern0 [2][0]
	UINT32 reg_dj_pattern0_2_01             :2;	//3:2	//DJ protect pattern0 [2][1]
	UINT32 reg_dj_pattern0_2_02             :2;	//5:4	//DJ protect pattern0 [2][2]
	UINT32 reg_dj_pattern0_2_03             :2;	//7:6	//DJ protect pattern0 [2][3]
	UINT32 reg_dj_pattern0_2_04             :2;	//9:8	//DJ protect pattern0 [2][4]
	UINT32 reg_dj_pattern0_2_05             :2;	//11:10	//DJ protect pattern0 [2][5]
	UINT32 reg_dj_pattern0_2_06             :2;	//13:12	//DJ protect pattern0 [2][6]
	UINT32 reg_dj_pattern0_2_07             :2;	//15:14	//DJ protect pattern0 [2][7]
	UINT32 reg_dj_pattern0_2_08             :2;	//17:16	//DJ protect pattern0 [2][8]
	UINT32 reg_dj_pattern0_2_09             :2;	//19:18	//DJ protect pattern0 [2][9]
	UINT32 reg_dj_pattern0_2_10             :2;	//21:20	//DJ protect pattern0 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC20 RW
	UINT32 reg_dj_pattern0_3_00             :2;	//1:0	//DJ protect pattern0 [3][0]
	UINT32 reg_dj_pattern0_3_01             :2;	//3:2	//DJ protect pattern0 [3][1]
	UINT32 reg_dj_pattern0_3_02             :2;	//5:4	//DJ protect pattern0 [3][2]
	UINT32 reg_dj_pattern0_3_03             :2;	//7:6	//DJ protect pattern0 [3][3]
	UINT32 reg_dj_pattern0_3_04             :2;	//9:8	//DJ protect pattern0 [3][4]
	UINT32 reg_dj_pattern0_3_05             :2;	//11:10	//DJ protect pattern0 [3][5]
	UINT32 reg_dj_pattern0_3_06             :2;	//13:12	//DJ protect pattern0 [3][6]
	UINT32 reg_dj_pattern0_3_07             :2;	//15:14	//DJ protect pattern0 [3][7]
	UINT32 reg_dj_pattern0_3_08             :2;	//17:16	//DJ protect pattern0 [3][8]
	UINT32 reg_dj_pattern0_3_09             :2;	//19:18	//DJ protect pattern0 [3][9]
	UINT32 reg_dj_pattern0_3_10             :2;	//21:20	//DJ protect pattern0 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC24 RW
	UINT32 reg_dj_pattern0_4_00             :2;	//1:0	//DJ protect pattern0 [4][0]
	UINT32 reg_dj_pattern0_4_01             :2;	//3:2	//DJ protect pattern0 [4][1]
	UINT32 reg_dj_pattern0_4_02             :2;	//5:4	//DJ protect pattern0 [4][2]
	UINT32 reg_dj_pattern0_4_03             :2;	//7:6	//DJ protect pattern0 [4][3]
	UINT32 reg_dj_pattern0_4_04             :2;	//9:8	//DJ protect pattern0 [4][4]
	UINT32 reg_dj_pattern0_4_05             :2;	//11:10	//DJ protect pattern0 [4][5]
	UINT32 reg_dj_pattern0_4_06             :2;	//13:12	//DJ protect pattern0 [4][6]
	UINT32 reg_dj_pattern0_4_07             :2;	//15:14	//DJ protect pattern0 [4][7]
	UINT32 reg_dj_pattern0_4_08             :2;	//17:16	//DJ protect pattern0 [4][8]
	UINT32 reg_dj_pattern0_4_09             :2;	//19:18	//DJ protect pattern0 [4][9]
	UINT32 reg_dj_pattern0_4_10             :2;	//21:20	//DJ protect pattern0 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC28 RW
	UINT32 reg_dj_pattern0_5_00             :2;	//1:0	//DJ protect pattern0 [5][0]
	UINT32 reg_dj_pattern0_5_01             :2;	//3:2	//DJ protect pattern0 [5][1]
	UINT32 reg_dj_pattern0_5_02             :2;	//5:4	//DJ protect pattern0 [5][2]
	UINT32 reg_dj_pattern0_5_03             :2;	//7:6	//DJ protect pattern0 [5][3]
	UINT32 reg_dj_pattern0_5_04             :2;	//9:8	//DJ protect pattern0 [5][4]
	UINT32 reg_dj_pattern0_5_05             :2;	//11:10	//DJ protect pattern0 [5][5]
	UINT32 reg_dj_pattern0_5_06             :2;	//13:12	//DJ protect pattern0 [5][6]
	UINT32 reg_dj_pattern0_5_07             :2;	//15:14	//DJ protect pattern0 [5][7]
	UINT32 reg_dj_pattern0_5_08             :2;	//17:16	//DJ protect pattern0 [5][8]
	UINT32 reg_dj_pattern0_5_09             :2;	//19:18	//DJ protect pattern0 [5][9]
	UINT32 reg_dj_pattern0_5_10             :2;	//21:20	//DJ protect pattern0 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC2C RW
	UINT32 reg_dj_pattern0_6_00             :2;	//1:0	//DJ protect pattern0 [6][0]
	UINT32 reg_dj_pattern0_6_01             :2;	//3:2	//DJ protect pattern0 [6][1]
	UINT32 reg_dj_pattern0_6_02             :2;	//5:4	//DJ protect pattern0 [6][2]
	UINT32 reg_dj_pattern0_6_03             :2;	//7:6	//DJ protect pattern0 [6][3]
	UINT32 reg_dj_pattern0_6_04             :2;	//9:8	//DJ protect pattern0 [6][4]
	UINT32 reg_dj_pattern0_6_05             :2;	//11:10	//DJ protect pattern0 [6][5]
	UINT32 reg_dj_pattern0_6_06             :2;	//13:12	//DJ protect pattern0 [6][6]
	UINT32 reg_dj_pattern0_6_07             :2;	//15:14	//DJ protect pattern0 [6][7]
	UINT32 reg_dj_pattern0_6_08             :2;	//17:16	//DJ protect pattern0 [6][8]
	UINT32 reg_dj_pattern0_6_09             :2;	//19:18	//DJ protect pattern0 [6][9]
	UINT32 reg_dj_pattern0_6_10             :2;	//21:20	//DJ protect pattern0 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC30 RW
	UINT32 reg_dj_pattern0_flip0_h          :1;	//0:0	//DJ protect pattern0 flip0, H
	UINT32 reg_dj_pattern0_flip0_v          :1;	//1:1	//DJ protect pattern0 flip0, V
	UINT32 reg_dj_pattern0_flip1_h          :1;	//2:2	//DJ protect pattern0 flip1, H
	UINT32 reg_dj_pattern0_flip1_v          :1;	//3:3	//DJ protect pattern0 flip1, V
	UINT32 reg_dj_pattern0_flip2_h          :1;	//4:4	//DJ protect pattern0 flip2, H
	UINT32 reg_dj_pattern0_flip2_v          :1;	//5:5	//DJ protect pattern0 flip2, V
	UINT32 reg_dj_pattern0_flip3_h          :1;	//6:6	//DJ protect pattern0 flip3, H
	UINT32 reg_dj_pattern0_flip3_v          :1;	//7:7	//DJ protect pattern0 flip3, V
	UINT32 resvd                            :24;
	};
}REG_SHY_4K_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC34 RW
	UINT32 reg_dj_pattern1_0_00             :2;	//1:0	//DJ protect pattern1 [0][0]
	UINT32 reg_dj_pattern1_0_01             :2;	//3:2	//DJ protect pattern1 [0][1]
	UINT32 reg_dj_pattern1_0_02             :2;	//5:4	//DJ protect pattern1 [0][2]
	UINT32 reg_dj_pattern1_0_03             :2;	//7:6	//DJ protect pattern1 [0][3]
	UINT32 reg_dj_pattern1_0_04             :2;	//9:8	//DJ protect pattern1 [0][4]
	UINT32 reg_dj_pattern1_0_05             :2;	//11:10	//DJ protect pattern1 [0][5]
	UINT32 reg_dj_pattern1_0_06             :2;	//13:12	//DJ protect pattern1 [0][6]
	UINT32 reg_dj_pattern1_0_07             :2;	//15:14	//DJ protect pattern1 [0][7]
	UINT32 reg_dj_pattern1_0_08             :2;	//17:16	//DJ protect pattern1 [0][8]
	UINT32 reg_dj_pattern1_0_09             :2;	//19:18	//DJ protect pattern1 [0][9]
	UINT32 reg_dj_pattern1_0_10             :2;	//21:20	//DJ protect pattern1 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC38 RW
	UINT32 reg_dj_pattern1_1_00             :2;	//1:0	//DJ protect pattern1 [1][0]
	UINT32 reg_dj_pattern1_1_01             :2;	//3:2	//DJ protect pattern1 [1][1]
	UINT32 reg_dj_pattern1_1_02             :2;	//5:4	//DJ protect pattern1 [1][2]
	UINT32 reg_dj_pattern1_1_03             :2;	//7:6	//DJ protect pattern1 [1][3]
	UINT32 reg_dj_pattern1_1_04             :2;	//9:8	//DJ protect pattern1 [1][4]
	UINT32 reg_dj_pattern1_1_05             :2;	//11:10	//DJ protect pattern1 [1][5]
	UINT32 reg_dj_pattern1_1_06             :2;	//13:12	//DJ protect pattern1 [1][6]
	UINT32 reg_dj_pattern1_1_07             :2;	//15:14	//DJ protect pattern1 [1][7]
	UINT32 reg_dj_pattern1_1_08             :2;	//17:16	//DJ protect pattern1 [1][8]
	UINT32 reg_dj_pattern1_1_09             :2;	//19:18	//DJ protect pattern1 [1][9]
	UINT32 reg_dj_pattern1_1_10             :2;	//21:20	//DJ protect pattern1 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC3C RW
	UINT32 reg_dj_pattern1_2_00             :2;	//1:0	//DJ protect pattern1 [2][0]
	UINT32 reg_dj_pattern1_2_01             :2;	//3:2	//DJ protect pattern1 [2][1]
	UINT32 reg_dj_pattern1_2_02             :2;	//5:4	//DJ protect pattern1 [2][2]
	UINT32 reg_dj_pattern1_2_03             :2;	//7:6	//DJ protect pattern1 [2][3]
	UINT32 reg_dj_pattern1_2_04             :2;	//9:8	//DJ protect pattern1 [2][4]
	UINT32 reg_dj_pattern1_2_05             :2;	//11:10	//DJ protect pattern1 [2][5]
	UINT32 reg_dj_pattern1_2_06             :2;	//13:12	//DJ protect pattern1 [2][6]
	UINT32 reg_dj_pattern1_2_07             :2;	//15:14	//DJ protect pattern1 [2][7]
	UINT32 reg_dj_pattern1_2_08             :2;	//17:16	//DJ protect pattern1 [2][8]
	UINT32 reg_dj_pattern1_2_09             :2;	//19:18	//DJ protect pattern1 [2][9]
	UINT32 reg_dj_pattern1_2_10             :2;	//21:20	//DJ protect pattern1 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC40 RW
	UINT32 reg_dj_pattern1_3_00             :2;	//1:0	//DJ protect pattern1 [3][0]
	UINT32 reg_dj_pattern1_3_01             :2;	//3:2	//DJ protect pattern1 [3][1]
	UINT32 reg_dj_pattern1_3_02             :2;	//5:4	//DJ protect pattern1 [3][2]
	UINT32 reg_dj_pattern1_3_03             :2;	//7:6	//DJ protect pattern1 [3][3]
	UINT32 reg_dj_pattern1_3_04             :2;	//9:8	//DJ protect pattern1 [3][4]
	UINT32 reg_dj_pattern1_3_05             :2;	//11:10	//DJ protect pattern1 [3][5]
	UINT32 reg_dj_pattern1_3_06             :2;	//13:12	//DJ protect pattern1 [3][6]
	UINT32 reg_dj_pattern1_3_07             :2;	//15:14	//DJ protect pattern1 [3][7]
	UINT32 reg_dj_pattern1_3_08             :2;	//17:16	//DJ protect pattern1 [3][8]
	UINT32 reg_dj_pattern1_3_09             :2;	//19:18	//DJ protect pattern1 [3][9]
	UINT32 reg_dj_pattern1_3_10             :2;	//21:20	//DJ protect pattern1 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC44 RW
	UINT32 reg_dj_pattern1_4_00             :2;	//1:0	//DJ protect pattern1 [4][0]
	UINT32 reg_dj_pattern1_4_01             :2;	//3:2	//DJ protect pattern1 [4][1]
	UINT32 reg_dj_pattern1_4_02             :2;	//5:4	//DJ protect pattern1 [4][2]
	UINT32 reg_dj_pattern1_4_03             :2;	//7:6	//DJ protect pattern1 [4][3]
	UINT32 reg_dj_pattern1_4_04             :2;	//9:8	//DJ protect pattern1 [4][4]
	UINT32 reg_dj_pattern1_4_05             :2;	//11:10	//DJ protect pattern1 [4][5]
	UINT32 reg_dj_pattern1_4_06             :2;	//13:12	//DJ protect pattern1 [4][6]
	UINT32 reg_dj_pattern1_4_07             :2;	//15:14	//DJ protect pattern1 [4][7]
	UINT32 reg_dj_pattern1_4_08             :2;	//17:16	//DJ protect pattern1 [4][8]
	UINT32 reg_dj_pattern1_4_09             :2;	//19:18	//DJ protect pattern1 [4][9]
	UINT32 reg_dj_pattern1_4_10             :2;	//21:20	//DJ protect pattern1 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC48 RW
	UINT32 reg_dj_pattern1_5_00             :2;	//1:0	//DJ protect pattern1 [5][0]
	UINT32 reg_dj_pattern1_5_01             :2;	//3:2	//DJ protect pattern1 [5][1]
	UINT32 reg_dj_pattern1_5_02             :2;	//5:4	//DJ protect pattern1 [5][2]
	UINT32 reg_dj_pattern1_5_03             :2;	//7:6	//DJ protect pattern1 [5][3]
	UINT32 reg_dj_pattern1_5_04             :2;	//9:8	//DJ protect pattern1 [5][4]
	UINT32 reg_dj_pattern1_5_05             :2;	//11:10	//DJ protect pattern1 [5][5]
	UINT32 reg_dj_pattern1_5_06             :2;	//13:12	//DJ protect pattern1 [5][6]
	UINT32 reg_dj_pattern1_5_07             :2;	//15:14	//DJ protect pattern1 [5][7]
	UINT32 reg_dj_pattern1_5_08             :2;	//17:16	//DJ protect pattern1 [5][8]
	UINT32 reg_dj_pattern1_5_09             :2;	//19:18	//DJ protect pattern1 [5][9]
	UINT32 reg_dj_pattern1_5_10             :2;	//21:20	//DJ protect pattern1 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC4C RW
	UINT32 reg_dj_pattern1_6_00             :2;	//1:0	//DJ protect pattern1 [6][0]
	UINT32 reg_dj_pattern1_6_01             :2;	//3:2	//DJ protect pattern1 [6][1]
	UINT32 reg_dj_pattern1_6_02             :2;	//5:4	//DJ protect pattern1 [6][2]
	UINT32 reg_dj_pattern1_6_03             :2;	//7:6	//DJ protect pattern1 [6][3]
	UINT32 reg_dj_pattern1_6_04             :2;	//9:8	//DJ protect pattern1 [6][4]
	UINT32 reg_dj_pattern1_6_05             :2;	//11:10	//DJ protect pattern1 [6][5]
	UINT32 reg_dj_pattern1_6_06             :2;	//13:12	//DJ protect pattern1 [6][6]
	UINT32 reg_dj_pattern1_6_07             :2;	//15:14	//DJ protect pattern1 [6][7]
	UINT32 reg_dj_pattern1_6_08             :2;	//17:16	//DJ protect pattern1 [6][8]
	UINT32 reg_dj_pattern1_6_09             :2;	//19:18	//DJ protect pattern1 [6][9]
	UINT32 reg_dj_pattern1_6_10             :2;	//21:20	//DJ protect pattern1 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC50 RW
	UINT32 reg_dj_pattern1_flip0_h          :1;	//0:0	//DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//1:1	//DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//2:2	//DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//3:3	//DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}REG_SHY_4K_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC54 RW
	UINT32 reg_dj_pattern2_0_00             :2;	//1:0	//DJ protect pattern2 [0][0]
	UINT32 reg_dj_pattern2_0_01             :2;	//3:2	//DJ protect pattern2 [0][1]
	UINT32 reg_dj_pattern2_0_02             :2;	//5:4	//DJ protect pattern2 [0][2]
	UINT32 reg_dj_pattern2_0_03             :2;	//7:6	//DJ protect pattern2 [0][3]
	UINT32 reg_dj_pattern2_0_04             :2;	//9:8	//DJ protect pattern2 [0][4]
	UINT32 reg_dj_pattern2_0_05             :2;	//11:10	//DJ protect pattern2 [0][5]
	UINT32 reg_dj_pattern2_0_06             :2;	//13:12	//DJ protect pattern2 [0][6]
	UINT32 reg_dj_pattern2_0_07             :2;	//15:14	//DJ protect pattern2 [0][7]
	UINT32 reg_dj_pattern2_0_08             :2;	//17:16	//DJ protect pattern2 [0][8]
	UINT32 reg_dj_pattern2_0_09             :2;	//19:18	//DJ protect pattern2 [0][9]
	UINT32 reg_dj_pattern2_0_10             :2;	//21:20	//DJ protect pattern2 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC58 RW
	UINT32 reg_dj_pattern2_1_00             :2;	//1:0	//DJ protect pattern2 [1][0]
	UINT32 reg_dj_pattern2_1_01             :2;	//3:2	//DJ protect pattern2 [1][1]
	UINT32 reg_dj_pattern2_1_02             :2;	//5:4	//DJ protect pattern2 [1][2]
	UINT32 reg_dj_pattern2_1_03             :2;	//7:6	//DJ protect pattern2 [1][3]
	UINT32 reg_dj_pattern2_1_04             :2;	//9:8	//DJ protect pattern2 [1][4]
	UINT32 reg_dj_pattern2_1_05             :2;	//11:10	//DJ protect pattern2 [1][5]
	UINT32 reg_dj_pattern2_1_06             :2;	//13:12	//DJ protect pattern2 [1][6]
	UINT32 reg_dj_pattern2_1_07             :2;	//15:14	//DJ protect pattern2 [1][7]
	UINT32 reg_dj_pattern2_1_08             :2;	//17:16	//DJ protect pattern2 [1][8]
	UINT32 reg_dj_pattern2_1_09             :2;	//19:18	//DJ protect pattern2 [1][9]
	UINT32 reg_dj_pattern2_1_10             :2;	//21:20	//DJ protect pattern2 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC5C RW
	UINT32 reg_dj_pattern2_2_00             :2;	//1:0	//DJ protect pattern2 [2][0]
	UINT32 reg_dj_pattern2_2_01             :2;	//3:2	//DJ protect pattern2 [2][1]
	UINT32 reg_dj_pattern2_2_02             :2;	//5:4	//DJ protect pattern2 [2][2]
	UINT32 reg_dj_pattern2_2_03             :2;	//7:6	//DJ protect pattern2 [2][3]
	UINT32 reg_dj_pattern2_2_04             :2;	//9:8	//DJ protect pattern2 [2][4]
	UINT32 reg_dj_pattern2_2_05             :2;	//11:10	//DJ protect pattern2 [2][5]
	UINT32 reg_dj_pattern2_2_06             :2;	//13:12	//DJ protect pattern2 [2][6]
	UINT32 reg_dj_pattern2_2_07             :2;	//15:14	//DJ protect pattern2 [2][7]
	UINT32 reg_dj_pattern2_2_08             :2;	//17:16	//DJ protect pattern2 [2][8]
	UINT32 reg_dj_pattern2_2_09             :2;	//19:18	//DJ protect pattern2 [2][9]
	UINT32 reg_dj_pattern2_2_10             :2;	//21:20	//DJ protect pattern2 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC60 RW
	UINT32 reg_dj_pattern2_3_00             :2;	//1:0	//DJ protect pattern2 [3][0]
	UINT32 reg_dj_pattern2_3_01             :2;	//3:2	//DJ protect pattern2 [3][1]
	UINT32 reg_dj_pattern2_3_02             :2;	//5:4	//DJ protect pattern2 [3][2]
	UINT32 reg_dj_pattern2_3_03             :2;	//7:6	//DJ protect pattern2 [3][3]
	UINT32 reg_dj_pattern2_3_04             :2;	//9:8	//DJ protect pattern2 [3][4]
	UINT32 reg_dj_pattern2_3_05             :2;	//11:10	//DJ protect pattern2 [3][5]
	UINT32 reg_dj_pattern2_3_06             :2;	//13:12	//DJ protect pattern2 [3][6]
	UINT32 reg_dj_pattern2_3_07             :2;	//15:14	//DJ protect pattern2 [3][7]
	UINT32 reg_dj_pattern2_3_08             :2;	//17:16	//DJ protect pattern2 [3][8]
	UINT32 reg_dj_pattern2_3_09             :2;	//19:18	//DJ protect pattern2 [3][9]
	UINT32 reg_dj_pattern2_3_10             :2;	//21:20	//DJ protect pattern2 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC64 RW
	UINT32 reg_dj_pattern2_4_00             :2;	//1:0	//DJ protect pattern2 [4][0]
	UINT32 reg_dj_pattern2_4_01             :2;	//3:2	//DJ protect pattern2 [4][1]
	UINT32 reg_dj_pattern2_4_02             :2;	//5:4	//DJ protect pattern2 [4][2]
	UINT32 reg_dj_pattern2_4_03             :2;	//7:6	//DJ protect pattern2 [4][3]
	UINT32 reg_dj_pattern2_4_04             :2;	//9:8	//DJ protect pattern2 [4][4]
	UINT32 reg_dj_pattern2_4_05             :2;	//11:10	//DJ protect pattern2 [4][5]
	UINT32 reg_dj_pattern2_4_06             :2;	//13:12	//DJ protect pattern2 [4][6]
	UINT32 reg_dj_pattern2_4_07             :2;	//15:14	//DJ protect pattern2 [4][7]
	UINT32 reg_dj_pattern2_4_08             :2;	//17:16	//DJ protect pattern2 [4][8]
	UINT32 reg_dj_pattern2_4_09             :2;	//19:18	//DJ protect pattern2 [4][9]
	UINT32 reg_dj_pattern2_4_10             :2;	//21:20	//DJ protect pattern2 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC68 RW
	UINT32 reg_dj_pattern2_5_00             :2;	//1:0	//DJ protect pattern2 [5][0]
	UINT32 reg_dj_pattern2_5_01             :2;	//3:2	//DJ protect pattern2 [5][1]
	UINT32 reg_dj_pattern2_5_02             :2;	//5:4	//DJ protect pattern2 [5][2]
	UINT32 reg_dj_pattern2_5_03             :2;	//7:6	//DJ protect pattern2 [5][3]
	UINT32 reg_dj_pattern2_5_04             :2;	//9:8	//DJ protect pattern2 [5][4]
	UINT32 reg_dj_pattern2_5_05             :2;	//11:10	//DJ protect pattern2 [5][5]
	UINT32 reg_dj_pattern2_5_06             :2;	//13:12	//DJ protect pattern2 [5][6]
	UINT32 reg_dj_pattern2_5_07             :2;	//15:14	//DJ protect pattern2 [5][7]
	UINT32 reg_dj_pattern2_5_08             :2;	//17:16	//DJ protect pattern2 [5][8]
	UINT32 reg_dj_pattern2_5_09             :2;	//19:18	//DJ protect pattern2 [5][9]
	UINT32 reg_dj_pattern2_5_10             :2;	//21:20	//DJ protect pattern2 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC6C RW
	UINT32 reg_dj_pattern2_6_00             :2;	//1:0	//DJ protect pattern2 [6][0]
	UINT32 reg_dj_pattern2_6_01             :2;	//3:2	//DJ protect pattern2 [6][1]
	UINT32 reg_dj_pattern2_6_02             :2;	//5:4	//DJ protect pattern2 [6][2]
	UINT32 reg_dj_pattern2_6_03             :2;	//7:6	//DJ protect pattern2 [6][3]
	UINT32 reg_dj_pattern2_6_04             :2;	//9:8	//DJ protect pattern2 [6][4]
	UINT32 reg_dj_pattern2_6_05             :2;	//11:10	//DJ protect pattern2 [6][5]
	UINT32 reg_dj_pattern2_6_06             :2;	//13:12	//DJ protect pattern2 [6][6]
	UINT32 reg_dj_pattern2_6_07             :2;	//15:14	//DJ protect pattern2 [6][7]
	UINT32 reg_dj_pattern2_6_08             :2;	//17:16	//DJ protect pattern2 [6][8]
	UINT32 reg_dj_pattern2_6_09             :2;	//19:18	//DJ protect pattern2 [6][9]
	UINT32 reg_dj_pattern2_6_10             :2;	//21:20	//DJ protect pattern2 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_4K_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC70 RW
	UINT32 reg_dj_pattern2_flip0_h          :1;	//0:0	//DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//1:1	//DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//2:2	//DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//3:3	//DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}REG_SHY_4K_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC74 RW
	UINT32 reg_dj_soft_g0_mul               :6;	//5:0	//Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//12:8	//Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//23:16	//Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}REG_SHY_4K_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC78 RW
	UINT32 reg_dj_soft_g1_mul               :6;	//5:0	//Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//12:8	//Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//23:16	//Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}REG_SHY_4K_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC7C RW
	UINT32 reg_dj_soft_g2_mul               :6;	//5:0	//Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//12:8	//Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//23:16	//Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}REG_SHY_4K_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC80 RW
	UINT32 reg_dj_soft_base                 :8;	//7:0	//Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//15:8	//Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//16:16	//Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}REG_SHY_4K_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC90 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BC94 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BCA0 RW
	UINT32 reg_win_dj_win0_en               :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_dj_win1_en               :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_dj_win01_en              :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dj_win_outside           :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_dj_win_en                :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_dj_bdr_alpha             :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_dj_bdr_wid               :2;	//14:13	//border width
	UINT32 reg_win_dj_bdr_en                :1;	//15:15	//border enable
	UINT32 reg_win_dj_cr5                   :5;	//20:16	//border color: cr5
	UINT32 reg_win_dj_cb5                   :5;	//25:21	//border color: cb5
	UINT32 reg_win_dj_yy6                   :6;	//31:26	//border color: yy6
	};
}REG_SHY_4K_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BCA4 RW
	UINT32 reg_win_dj_win_w0_x0             :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BCA8 RW
	UINT32 reg_win_dj_win_w0_x1             :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BCAC RW
	UINT32 reg_win_dj_win_w1_x0             :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BCB0 RW
	UINT32 reg_win_dj_win_w1_x1             :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE00 RO
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//11:0	//Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//27:16	//Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE04 RO
	UINT32 reg_mon_in_vert_cnt              :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE08 RO
	UINT32 reg_mon_out_vert_cnt             :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE0C RO
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}REG_SHY_4K_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE10 RO
	UINT32 reg_mon_shp_i_sucfail            :32;	//31:0	//Input success/fail monitoring register
	};
}REG_SHY_4K_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE14 RO
	UINT32 reg_mon_shp_o_sucfail            :32;	//31:0	//Output success/fail monitoring register
	};
}REG_SHY_4K_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE60 RO
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE64 RO
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE68 RO
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BE6C RO
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BF00 RO
	UINT32 ro_tmap_status_window0           :32;	//31:0	//
	};
}REG_SHY_4K_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BF04 RO
	UINT32 ro_tmap_status_window1           :32;	//31:0	//
	};
}REG_SHY_4K_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BF08 RO
	UINT32 ro_tmap_status_0                 :16;	//15:0	//
	UINT32 ro_tmap_status_1                 :16;	//31:16	//
	};
}REG_SHY_4K_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BF0C RO
	UINT32 ro_tmap_status_2                 :16;	//15:0	//
	UINT32 ro_tmap_status_3                 :16;	//31:16	//
	};
}REG_SHY_4K_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BF10 RO
	UINT32 ro_tmap_status_4                 :16;	//15:0	//
	UINT32 ro_tmap_status_5                 :16;	//31:16	//
	};
}REG_SHY_4K_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BF14 RO
	UINT32 ro_tmap_status_6                 :16;	//15:0	//
	UINT32 ro_tmap_status_7                 :16;	//31:16	//
	};
}REG_SHY_4K_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BF18 RO
	UINT32 ro_tmap_status_8                 :16;	//15:0	//
	UINT32 ro_tmap_status_9                 :16;	//31:16	//
	};
}REG_SHY_4K_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BF1C RO
	UINT32 ro_tmap_status_10                :16;	//15:0	//
	UINT32 ro_tmap_status_11                :16;	//31:16	//
	};
}REG_SHY_4K_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BFF0 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BFF4 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BFF8 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901BFFC RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_4K_SHP_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901AF00 RW
	UINT32 resvd0                           :4;
	UINT32 reg_top_core_detour              :1;	//4:4	//SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//5:5	//SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//8:8	//0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//12:12	//Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :19;
	};
}REG_SHY_2K_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901AF04 RW
	UINT32 reg_top_width                    :12;	//11:0	//processing width (default : 1920)
	UINT32 resvd0                           :4;
	UINT32 reg_top_height                   :12;	//27:16	//processing height (default : 1080)
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901AF08 RW
	UINT32 reg_top_use_extern_valid         :1;	//0:0	//Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//1:1	//Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//31:16	//Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}REG_SHY_2K_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901AF0C RW
	UINT32 reg_top_prefetch_cnt             :12;	//11:0	//Pre-fetch counter
	UINT32 resvd0                           :4;
	UINT32 reg_top_flush_cnt                :12;	//27:16	//Flush counter
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901AF40 RW
	UINT32 reg_pat_en                       :1;	//0:0	//pattern enable
	UINT32 reg_pat_thickness                :2;	//2:1	//pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd0                           :5;
	UINT32 reg_pat_pix_val_yy               :8;	//15:8	//pattern pixel value (Y)
	UINT32 resvd1                           :16;
	};
}REG_SHY_2K_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901AFF0 RW
	UINT32 reg_dp_debug_display             :4;	//3:0	//0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map
	UINT32 reg_dp_detour_en                 :1;	//4:4	//dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//8:8	//dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}REG_SHY_2K_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B000 RW
	UINT32 reg_fd_a_map_h_size              :2;	//1:0	//A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//8:8	//post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//18:16	//pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//20:19	//pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//23:21	//pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}REG_SHY_2K_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B004 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B008 RW
	UINT32 reg_fd_detail_beta_mul           :8;	//7:0	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//15:8	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//23:16	//get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//31:24	//get_t_map (alpha*t_map - beta*a_map)
	};
}REG_SHY_2K_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B00C RW
	UINT32 reg_fd_a_lut_edge_y0             :8;	//7:0	//A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//15:8	//A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//23:16	//A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//31:24	//A-map edge LUT, x1
	};
}REG_SHY_2K_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B010 RW
	UINT32 reg_fd_a_lut_detail_y0           :8;	//7:0	//A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//15:8	//A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//23:16	//A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//31:24	//A-map detail LUT, x1
	};
}REG_SHY_2K_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B014 RW
	UINT32 reg_fd_t_lut_edge_y0             :8;	//7:0	//T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//15:8	//T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//23:16	//T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//31:24	//T-map edge LUT, x1
	};
}REG_SHY_2K_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B018 RW
	UINT32 reg_fd_t_lut_detail_y0           :8;	//7:0	//T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//15:8	//T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//23:16	//T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//31:24	//T-map detail LUT, x1
	};
}REG_SHY_2K_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B01C RW
	UINT32 reg_fd_edge_minmax_y0            :8;	//7:0	//Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//15:8	//Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//23:16	//Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//31:24	//Final edge LUT, x1
	};
}REG_SHY_2K_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B020 RW
	UINT32 reg_fd_edge_minmax_y2            :8;	//7:0	//Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//15:8	//Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//23:16	//Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//31:24	//Final edge LUT, x3
	};
}REG_SHY_2K_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B024 RW
	UINT32 reg_fd_detail_minmax_y0          :8;	//7:0	//Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//15:8	//Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//23:16	//Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//31:24	//Final detail LUT, x1
	};
}REG_SHY_2K_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B028 RW
	UINT32 reg_fd_detail_minmax_y2          :8;	//7:0	//Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//15:8	//Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//23:16	//Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//31:24	//Final detail LUT, x3
	};
}REG_SHY_2K_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B02C RW
	UINT32 reg_fd_mnr_gain_e_en             :1;	//0:0	//edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//1:1	//texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//5:4	//s1 h expand
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B030 RW
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//7:0	//s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//23:16	//s1 ratio max
	UINT32 resvd1                           :8;
	};
}REG_SHY_2K_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B034 RW
	UINT32 reg_fd_mnr_gain_x0               :8;	//7:0	//MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//15:8	//MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//23:16	//MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//31:24	//MNR gain LUT, y1
	};
}REG_SHY_2K_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B038 RW
	UINT32 reg_fd_dct_t_lut_y0              :8;	//7:0	//DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//15:8	//DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//23:16	//DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//31:24	//DCT T-map LUT, x1
	};
}REG_SHY_2K_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B03C RW
	UINT32 reg_fd_dct_t_lut_y2              :8;	//7:0	//DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//15:8	//DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//23:16	//DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//31:24	//DCT T-map LUT, x3
	};
}REG_SHY_2K_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B040 RW
	UINT32 reg_fd_dct_t_lut_y4              :8;	//7:0	//DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//15:8	//DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//23:16	//DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//31:24	//DCT T-map LUT, x5
	};
}REG_SHY_2K_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B044 RW
	UINT32 reg_fd_soft_gain_e_en            :1;	//0:0	//Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//1:1	//Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}REG_SHY_2K_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B048 RW
	UINT32 reg_fd_soft_ratio                :8;	//7:0	//Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//15:8	//Soft edge offset
	UINT32 resvd                            :16;
	};
}REG_SHY_2K_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B04C RW
	UINT32 reg_fd_soft_score_x0             :8;	//7:0	//Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//15:8	//Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//23:16	//Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//31:24	//Soft edge score, x3
	};
}REG_SHY_2K_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B050 RW
	UINT32 reg_fd_soft_score_y0             :6;	//5:0	//Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//13:8	//Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//21:16	//Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//29:24	//Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}REG_SHY_2K_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B054 RW
	UINT32 reg_fd_flat_input_sel            :2;	//1:0	//input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//4:4	//1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//8:8	//1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}REG_SHY_2K_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B058 RW
	UINT32 reg_fd_flat_lut_y0               :8;	//7:0	//Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//15:8	//Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//23:16	//Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//31:24	//Flat region LUT, x1
	};
}REG_SHY_2K_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B060 RW
	UINT32 reg_mp_shp_en                    :1;	//0:0	//MP enable
	UINT32 resvd                            :31;
	};
}REG_SHY_2K_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B064 RW
	UINT32 reg_mp_im_os_gain                :7;	//6:0	//im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//14:8	//im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//23:16	//im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//31:24	//im gain v
	};
}REG_SHY_2K_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B068 RW
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 resvd1                           :16;
	};
}REG_SHY_2K_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B06C RW
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//7:4	//Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//11:8	//Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//15:12	//Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//23:20	//Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//27:24	//Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//31:28	//Laplacian gain h 3
	};
}REG_SHY_2K_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B070 RW
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//11:8	//display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}REG_SHY_2K_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B074 RW
	UINT32 reg_mp_gb_en                     :1;	//0:0	//0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//4:4	//delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//15:8	//gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 resvd2                           :8;
	};
}REG_SHY_2K_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B078 RW
	UINT32 reg_mp_gb_x2                     :8;	//7:0	//gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//15:8	//gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 resvd                            :8;
	};
}REG_SHY_2K_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B07C RW
	UINT32 reg_mp_lum1_x_l0                 :8;	//7:0	//level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//15:8	//level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//23:16	//level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//31:24	//level-balancing, lum1_x_H1
	};
}REG_SHY_2K_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B080 RW
	UINT32 reg_mp_lum1_y0                   :8;	//7:0	//level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//15:8	//level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//23:16	//level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//31:24	//level-balancing, lum2_x_L0
	};
}REG_SHY_2K_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B084 RW
	UINT32 reg_mp_lum2_x_l1                 :8;	//7:0	//level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//15:8	//level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//23:16	//level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//31:24	//level-balancing, lum2_y0
	};
}REG_SHY_2K_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B088 RW
	UINT32 reg_mp_lum2_y1                   :8;	//7:0	//level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//15:8	//level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}REG_SHY_2K_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B08C RW
	UINT32 reg_mp_coring_en                 :1;	//0:0	//[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//2:1	//[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B090 RW
	UINT32 reg_mp_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_2K_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B094 RW
	UINT32 reg_apl_iir_en                   :1;	//0:0	//APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//15:8	//APL gain
	UINT32 resvd1                           :16;
	};
}REG_SHY_2K_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0A0 RW
	UINT32 reg_lc_shp_en                      :1 ;	// 0:0
	UINT32 reserved01                         :3 ;	// reserved
	UINT32 reg_lc_gb_en                       :1 ;	// 4:4
	UINT32 reserved02                         :3 ;	// reserved
	UINT32 reg_lc_center_target             :8;	//15:8	//center target
	UINT32 reg_lc_center_gain               :8;	//23:16	//center gain
	UINT32 reg_lc_local_gain                :8;	//31:24	//local gain
	};
}REG_SHY_2K_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0A4 RW
	UINT32 reg_lc_gb_y2                     :8;	//7:0	//gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//15:8	//gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//31:24	//gain balancing, x1
	};
}REG_SHY_2K_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0A8 RW
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//31:24	//gain balancing, x3
	};
}REG_SHY_2K_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0AC RW
	UINT32 reg_lc_coring_en                 :1;	//0:0	//[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//2:1	//[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0B0 RW
	UINT32 reg_lc_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_2K_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0C0 RW
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//13:8	//reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//21:16	//reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//30:24	//reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//31:31	//reg_th_manual_en
	};
}REG_SHY_2K_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0C4 RW
	UINT32 reg_derh_bflt_tap_size           :3;	//2:0	//bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//24:24	//reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//27:26	//edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//31:31	//edge_Y_filter en
	};
}REG_SHY_2K_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0C8 RW
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//13:8	//edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//21:16	//edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}REG_SHY_2K_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0CC RW
	UINT32 reg_derv_en                      :1;	//0:0	//der-v enable
	UINT32 resvd0                           :2;
	UINT32 reg_derv_bif_en                  :1;	//3:3	//0: disable BiF	1: enable BiF
	UINT32 reg_derv_output_mux              :4;	//7:4	//0xxx: normal display	1000: vertical ringing measure	1001: gain adjusted by curve mapping	101x: bilateral filter output	o.w : not used
	UINT32 reg_derv_bif_manual_th           :8;	//15:8	//bilateral filter threshold
	UINT32 reg_derv_th_gain                 :6;	//21:16	//auto threshold gain, th = th_gain * A
	UINT32 resvd1                           :2;
	UINT32 reg_derv_th_mode                 :1;	//24:24	//th mode	0: auto(A-map)	1: manual
	UINT32 resvd2                           :7;
	};
}REG_SHY_2K_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0D0 RW
	UINT32 reg_derv_csft_gain               :6;	//5:0	//center-shift gain (1.5u)
	UINT32 resvd0                           :2;
	UINT32 reg_derv_csft_mode               :1;	//8:8	//center-shift mode	0: auto	1: do not apply center-shift
	UINT32 resvd1                           :23;
	};
}REG_SHY_2K_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0D4 RW
	UINT32 reg_derv_gain_b                  :7;	//6:0	//gain(b): 2.5u
	UINT32 resvd0                           :1;
	UINT32 reg_derv_gain_w                  :7;	//14:8	//gain(w): 2.5u
	UINT32 resvd1                           :17;
	};
}REG_SHY_2K_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0D8 RW
	UINT32 reg_der_a_lut_y0                 :8;	//7:0	//A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//15:8	//A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//23:16	//A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//31:24	//A-map for der LUT, x1
	};
}REG_SHY_2K_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0DC RW
	UINT32 reg_der_a_lut_y2                 :8;	//7:0	//A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//15:8	//A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//23:16	//A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//31:24	//A-map for de-rining LUT, x3
	};
}REG_SHY_2K_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0E0 RW
	UINT32 reg_sp_shp_en                    :1;	//0:0	//SP enable
	UINT32 resvd                            :31;
	};
}REG_SHY_2K_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0E4 RW
	UINT32 reg_sp_im_os_gain                :7;	//6:0	//im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//14:8	//im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//23:16	//im gain h
	UINT32 resvd2                           :8;
	};
}REG_SHY_2K_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0E8 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 resvd1                           :16;
	};
}REG_SHY_2K_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0EC RW
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//23:20	//Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//27:24	//Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//31:28	//Laplacian gain h 3
	};
}REG_SHY_2K_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0F0 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//11:8	//display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}REG_SHY_2K_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0F4 RW
	UINT32 reg_sp_gb_en                     :1;	//0:0	//0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//4:4	//delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//15:8	//gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 resvd2                           :8;
	};
}REG_SHY_2K_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0F8 RW
	UINT32 reg_sp_gb_x2                     :8;	//7:0	//gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//15:8	//gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 resvd                            :8;
	};
}REG_SHY_2K_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B0FC RW
	UINT32 reg_sp_lum1_x_l0                 :8;	//7:0	//level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//15:8	//level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//23:16	//level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//31:24	//level-balancing, lum1_x_H1
	};
}REG_SHY_2K_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B100 RW
	UINT32 reg_sp_lum1_y0                   :8;	//7:0	//level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//15:8	//level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//23:16	//level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//31:24	//level-balancing, lum2_x_L0
	};
}REG_SHY_2K_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B104 RW
	UINT32 reg_sp_lum2_x_l1                 :8;	//7:0	//level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//15:8	//level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//23:16	//level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//31:24	//level-balancing, lum2_y0
	};
}REG_SHY_2K_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B108 RW
	UINT32 reg_sp_lum2_y1                   :8;	//7:0	//level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//15:8	//level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}REG_SHY_2K_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B10C RW
	UINT32 reg_sp_coring_en                 :1;	//0:0	//[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//2:1	//[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B110 RW
	UINT32 reg_sp_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_2K_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B120 RW
	UINT32 reg_ptiv_enable                  :1;	//0:0	//PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//3:2	//mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//5:4	//avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//6:6	//ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//15:8	//master gain
	UINT32 resvd2                           :16;
	};
}REG_SHY_2K_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B124 RW
	UINT32 reg_ptih_enable                  :1;	//0:0	//PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//3:2	//mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//5:4	//avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//6:6	//ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//15:8	//master gain
	UINT32 resvd2                           :16;
	};
}REG_SHY_2K_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B128 RW
	UINT32 reg_pti_coring_en                :1;	//0:0	//[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//2:1	//[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B12C RW
	UINT32 reg_pti_coring_gain_e_b          :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_2K_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B130 RW
	UINT32 reg_sti_enable                   :1;	//0:0	//STI enable
	UINT32 reg_sti_debug_map_en             :1;	//1:1	//debug map enable
	UINT32 reg_sti_mm_tap_size              :2;	//3:2	//mm tap size
	UINT32 reg_sti_avg_tap_size             :2;	//5:4	//avg tap size
	UINT32 reg_sti_ti_mode                  :1;	//6:6	//ti mode
	UINT32 resvd                            :1;
	UINT32 reg_sti_master_gain              :8;	//15:8	//master gain
	UINT32 reg_sti_texture_gain             :8;	//23:16	//texture gain
	UINT32 reg_sti_edge_gain                :8;	//31:24	//edge gain
	};
}REG_SHY_2K_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B140 RW
	UINT32 reg_tgen_on_off                  :1;	//0:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_initial_seed_mode       :1;	//4:4	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_dbg_en                  :1;	//8:8	//
	UINT32 resvd2                           :7;
	UINT32 reg_tgen_table_sel               :4;	//19:16	//
	UINT32 resvd3                           :4;
	UINT32 reg_tgen_master_gain             :8;	//31:24	//
	};
}REG_SHY_2K_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B144 RW
	UINT32 reg_tgen_delta_h_bound           :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//26:24	//
	UINT32 resvd3                           :5;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B148 RW
	UINT32 reg_tgen_rnd_th                  :8;	//7:0	//
	UINT32 reg_tgen_delta_wcurr             :4;	//11:8	//
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//21:16	//
	UINT32 resvd1                           :10;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B14C RW
	UINT32 reg_tgen_rand_x0                 :32;	//31:0	//
	};
}REG_SHY_2K_SHP_TGEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B154 RW
	UINT32 reg_tgen_dr_ratio                :3;	//2:0	//
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//13:8	//
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//20:16	//
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//25:24	//
	UINT32 resvd3                           :6;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B158 RW
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//20:16	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//28:24	//
	UINT32 resvd2                           :3;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B15C RW
	UINT32 reg_tgen_blur_coef_x2            :6;	//5:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//13:8	//
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B160 RW
	UINT32 reg_tgen_blur_coef_y2            :6;	//5:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//13:8	//
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B164 RW
	UINT32 reg_tgen_map_edge_gain           :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//23:16	//
	UINT32 reg_tgen_gs_noise                :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B168 RW
	UINT32 reg_tgen_gain7                   :4;	//3:0	//
	UINT32 reg_tgen_gain6                   :4;	//7:4	//
	UINT32 reg_tgen_gain5                   :4;	//11:8	//
	UINT32 reg_tgen_gain4                   :4;	//15:12	//
	UINT32 reg_tgen_gain3                   :4;	//19:16	//
	UINT32 reg_tgen_gain2                   :4;	//23:20	//
	UINT32 reg_tgen_gain1                   :4;	//27:24	//
	UINT32 reg_tgen_gain0                   :4;	//31:28	//
	};
}REG_SHY_2K_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B16C RW
	UINT32 reg_tgen_coring_en               :1;	//0:0	//[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//2:1	//[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B170 RW
	UINT32 reg_tgen_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_2K_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B174 RW
	UINT32 reg_snr_blur_en                  :1;	//0:0	//SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//5:4	//filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//15:8	//Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//18:16	//SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}REG_SHY_2K_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B180 RW
	UINT32 reg_dctp_en                      :1;	//0:0	//DCT peaking enable
	UINT32 resvd                            :31;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B184 RW
	UINT32 reg_dctp_filt0_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B188 RW
	UINT32 reg_dctp_filt0_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B18C RW
	UINT32 reg_dctp_filt0_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B190 RW
	UINT32 reg_dctp_filt0_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B194 RW
	UINT32 reg_dctp_filt1_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B198 RW
	UINT32 reg_dctp_filt1_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B19C RW
	UINT32 reg_dctp_filt1_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1A0 RW
	UINT32 reg_dctp_filt1_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1A4 RW
	UINT32 reg_dctp_filt2_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1A8 RW
	UINT32 reg_dctp_filt2_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1AC RW
	UINT32 reg_dctp_filt2_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1B0 RW
	UINT32 reg_dctp_filt2_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1B4 RW
	UINT32 reg_dctp_filt3_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1B8 RW
	UINT32 reg_dctp_filt3_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1BC RW
	UINT32 reg_dctp_filt3_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1C0 RW
	UINT32 reg_dctp_filt3_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1C4 RW
	UINT32 reg_dctp_filt4_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1C8 RW
	UINT32 reg_dctp_filt4_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1CC RW
	UINT32 reg_dctp_filt4_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1D0 RW
	UINT32 reg_dctp_filt4_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1D4 RW
	UINT32 reg_dctp_filt5_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1D8 RW
	UINT32 reg_dctp_filt5_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1DC RW
	UINT32 reg_dctp_filt5_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1E0 RW
	UINT32 reg_dctp_filt5_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1E4 RW
	UINT32 reg_dctp_text_lut_x0             :8;	//7:0	//DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//15:8	//DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//23:16	//DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//31:24	//DCT peaking texture LUT point, x3
	};
}REG_SHY_2K_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1E8 RW
	UINT32 reg_dctp_text_lut_x4             :8;	//7:0	//DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//15:8	//DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1EC RW
	UINT32 reg_dctp_edge_lut_y0             :8;	//7:0	//DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//15:8	//DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//23:16	//DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//31:24	//DCT peaking edge LUT point, x1
	};
}REG_SHY_2K_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1F0 RW
	UINT32 reg_dctp_edge_lut_y2             :8;	//7:0	//DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//15:8	//DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//23:16	//DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//31:24	//DCT peaking edge LUT point, x3
	};
}REG_SHY_2K_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1F4 RW
	UINT32 reg_dctp_gain                    :8;	//7:0	//DCT peaking master gain
	UINT32 resvd                            :24;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1F8 RW
	UINT32 reg_dctp_coring_en               :1;	//0:0	//[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//2:1	//[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B1FC RW
	UINT32 reg_dctp_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_2K_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B200 RW
	UINT32 reg_nntg_en                      :1;	//0:0	//4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//5:4	//4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B204 RW
	UINT32 reg_nntg_lsfr_init_1st           :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
}REG_SHY_2K_SHP_NNTG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B208 RW
	UINT32 reg_nntg_lsfr_init_2nd           :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
}REG_SHY_2K_SHP_NNTG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B20C RW
	UINT32 reg_nntg_lsfr_init_3rd           :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
}REG_SHY_2K_SHP_NNTG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B210 RW
	UINT32 reg_nntg_lsfr_init_4th           :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
}REG_SHY_2K_SHP_NNTG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B214 RW
	UINT32 reg_nntg_lsfr_init_5th           :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
}REG_SHY_2K_SHP_NNTG_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B22C RW
	UINT32 reg_nntg_rand_ratio              :8;	//7:0	//4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//14:8	//4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//23:16	//4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}REG_SHY_2K_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B230 RW
	UINT32 reg_nntg_rand_coef_g00           :4;	//3:0	//4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//7:4	//4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//11:8	//4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//19:16	//4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//23:20	//4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//27:24	//4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B234 RW
	UINT32 reg_nntg_rand_coef_g20           :4;	//3:0	//4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//7:4	//4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//11:8	//4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//19:16	//4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//23:20	//4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//27:24	//4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B238 RW
	UINT32 reg_nntg_nano_coef_g10           :4;	//3:0	//4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//7:4	//4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//11:8	//4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//19:16	//4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//23:20	//4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//27:24	//4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B23C RW
	UINT32 reg_nntg_diff_lut_y0             :8;	//7:0	//4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//15:8	//4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//23:16	//4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//31:24	//4K nano-noise diff LUT point, x1
	};
}REG_SHY_2K_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B240 RW
	UINT32 reg_nntg_diff_lut_y2             :8;	//7:0	//4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//15:8	//4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//23:16	//4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//31:24	//4K nano-noise diff LUT point, x3
	};
}REG_SHY_2K_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B244 RW
	UINT32 reg_nntg_edge_lut_y0             :8;	//7:0	//4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//15:8	//4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//23:16	//4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//31:24	//4K nano-noise edge LUT point, x1
	};
}REG_SHY_2K_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B248 RW
	UINT32 reg_nntg_edge_lut_y2             :8;	//7:0	//4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//15:8	//4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//23:16	//4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//31:24	//4K nano-noise edge LUT point, x3
	};
}REG_SHY_2K_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B24C RW
	UINT32 reg_nntg_random_gain             :8;	//7:0	//4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//15:8	//4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//23:16	//4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//31:24	//4K nano-noise denoise gain
	};
}REG_SHY_2K_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B250 RW
	UINT32 reg_nntg_coring_en               :1;	//0:0	//[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//2:1	//[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}REG_SHY_2K_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B254 RW
	UINT32 reg_nntg_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}REG_SHY_2K_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B260 RW
	UINT32 reg_dp_sum_gain                  :8;	//7:0	//DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//9:8	//0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}REG_SHY_2K_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B264 RW
	UINT32 reg_dp_sum_lut_y0                :8;	//7:0	//dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//15:8	//dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//23:16	//dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//31:24	//dp_sum LUT for delta control, x1
	};
}REG_SHY_2K_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B268 RW
	UINT32 reg_dp_sum_lut_y2                :8;	//7:0	//dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//15:8	//dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//23:16	//dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//31:24	//dp_sum LUT for delta control, x3
	};
}REG_SHY_2K_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2A0 RW
	UINT32 reg_win_dp_win0_en               :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_dp_win1_en               :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_dp_win01_en              :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dp_win_outside           :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_dp_win_en                :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_dp_bdr_alpha             :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_dp_bdr_wid               :2;	//14:13	//border width
	UINT32 reg_win_dp_bdr_en                :1;	//15:15	//border enable
	UINT32 reg_win_dp_cr5                   :5;	//20:16	//border color: cr5
	UINT32 reg_win_dp_cb5                   :5;	//25:21	//border color: cb5
	UINT32 reg_win_dp_yy6                   :6;	//31:26	//border color: yy6
	};
}REG_SHY_2K_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2A4 RW
	UINT32 reg_win_dp_win_w0_x0             :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y0             :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2A8 RW
	UINT32 reg_win_dp_win_w0_x1             :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w0_y1             :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2AC RW
	UINT32 reg_win_dp_win_w1_x0             :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y0             :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2B0 RW
	UINT32 reg_win_dp_win_w1_x1             :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dp_win_w1_y1             :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2C0 RW
	UINT32 reg_region_text_en               :1;	//0:0	//region texture enable
	UINT32 resvd0                           :3;
	UINT32 reg_region_text_cutres           :3;	//6:4	//
	UINT32 resvd1                           :1;
	UINT32 reg_region_text_add_offset       :8;	//15:8	//
	UINT32 reg_region_text_add_max          :8;	//23:16	//
	UINT32 reg_region_text_cuthif           :3;	//26:24	//
	UINT32 resvd2                           :5;
	};
}REG_SHY_2K_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2C4 RW
	UINT32 reg_region_text_lut_y0           :8;	//7:0	//region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//15:8	//region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//23:16	//region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//31:24	//region texture LUT , x1
	};
}REG_SHY_2K_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2C8 RW
	UINT32 reg_region_text_lut_y2           :8;	//7:0	//region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//15:8	//region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//23:16	//region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//31:24	//region texture LUT , x3
	};
}REG_SHY_2K_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2CC RW
	UINT32 reg_tmap_temp_iir_en             :1;	//0:0	//TMAP temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//4:4	//TMAP temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//15:8	//TMAP temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//24:24	//TMAP temporal process status selection	0 : original tmap status	1 : iir tmap status
	UINT32 resvd3                           :7;
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2D0 RW
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//7:0	//tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//15:8	//tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//23:16	//tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//31:24	//tmap temporal previous blend LUT , x1
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2D4 RW
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//7:0	//tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//15:8	//tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//23:16	//tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//31:24	//tmap temporal previous blend LUT , x3
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2D8 RW
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//7:0	//tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//15:8	//tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//23:16	//tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//31:24	//tmap temporal iir positive LUT , x1
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2DC RW
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//7:0	//tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//15:8	//tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//23:16	//tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//31:24	//tmap temporal iir positive LUT , x3
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2E0 RW
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//7:0	//tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//15:8	//tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//23:16	//tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//31:24	//tmap temporal iir positive LUT , x5
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2E4 RW
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//7:0	//tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//15:8	//tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//23:16	//tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//31:24	//tmap temporal iir negative LUT , x1
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2E8 RW
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//7:0	//tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//15:8	//tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//23:16	//tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//31:24	//tmap temporal iir negative LUT , x3
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2EC RW
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//7:0	//tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//15:8	//tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//23:16	//tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//31:24	//tmap temporal iir negative LUT , x5
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2F0 RW
	UINT32 reg_tmap_stat_win0_start_x       :12;	//11:0	//tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//27:16	//tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2F4 RW
	UINT32 reg_tmap_stat_win0_end_x         :12;	//11:0	//tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//27:16	//tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2F8 RW
	UINT32 reg_tmap_stat_win1_start_x       :12;	//11:0	//tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//27:16	//tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B2FC RW
	UINT32 reg_tmap_stat_win1_end_x         :12;	//11:0	//tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//27:16	//tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B300 RW
	UINT32 reg_dj_edf_en                    :1;	//0:0	//edge-directional de-jagging enable
	UINT32 reg_dj_hv_filter_en              :1;	//1:1	//H/V de-jagging enable
	UINT32 resvd0                           :1;
	UINT32 reg_dj_edge_adaptive_en          :1;	//3:3	//edge adaptive filter enable
	UINT32 reg_dj_line_variation_mode       :1;	//4:4	//0: sum of (cur - center)	1:  sum of adjacent pixel difference
	UINT32 reg_dj_l_type_protection         :1;	//5:5	//L-type protection
	UINT32 reg_dj_soft_en                   :1;	//6:6	//Soft DJ enable
	UINT32 resvd1                           :1;
	UINT32 reg_dj_count_diff_th             :5;	//12:8	//matchness threshold for edge-direction decision
	UINT32 resvd2                           :3;
	UINT32 reg_dj_output_mux                :3;	//18:16	//000: normal display	001: direction map	010: g0: feature (matchness)	011: g0 : gain	100: g1 : gain (protection)	101: final gain	110: blur coring map( used for blur-filtering)
	UINT32 reg_dj_buffer_detour_en          :1;	//19:19	//dj buffer detour enable
	UINT32 reg_dj_center_blur_mode          :2;	//21:20	//center-pixel averaging for edge-direction calculation	0: use original pixel	1: use avg. pixel
	UINT32 reg_dj_n_avg_mode                :1;	//22:22	//neighbor-pixel averaging : mode for dual edges	0: use 12 direction results	1: use 36 direction results
	UINT32 reg_dj_detour_en                 :1;	//23:23	//dejagging detour enable
	UINT32 reg_dj_line_variation_diff_th    :8;	//31:24	//line-variation threshold for edge-direction decision
	};
}REG_SHY_2K_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B304 RW
	UINT32 reg_dj_level_th                  :8;	//7:0	//g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//23:16	//neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}REG_SHY_2K_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B308 RW
	UINT32 reg_dj_g0_cnt_min                :5;	//4:0	//g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//12:8	//g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}REG_SHY_2K_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B30C RW
	UINT32 reg_dj_g1_protect_min            :8;	//7:0	//g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//14:8	//g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//23:16	//edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//31:24	//edge adaptive filter multiplication value
	};
}REG_SHY_2K_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B310 RW
	UINT32 reg_dj_dir_sel_c1                :1;	//0:0	//DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//1:1	//DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//2:2	//DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//3:3	//DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}REG_SHY_2K_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B314 RW
	UINT32 reg_dj_pattern0_0_00             :2;	//1:0	//DJ protect pattern0 [0][0]
	UINT32 reg_dj_pattern0_0_01             :2;	//3:2	//DJ protect pattern0 [0][1]
	UINT32 reg_dj_pattern0_0_02             :2;	//5:4	//DJ protect pattern0 [0][2]
	UINT32 reg_dj_pattern0_0_03             :2;	//7:6	//DJ protect pattern0 [0][3]
	UINT32 reg_dj_pattern0_0_04             :2;	//9:8	//DJ protect pattern0 [0][4]
	UINT32 reg_dj_pattern0_0_05             :2;	//11:10	//DJ protect pattern0 [0][5]
	UINT32 reg_dj_pattern0_0_06             :2;	//13:12	//DJ protect pattern0 [0][6]
	UINT32 reg_dj_pattern0_0_07             :2;	//15:14	//DJ protect pattern0 [0][7]
	UINT32 reg_dj_pattern0_0_08             :2;	//17:16	//DJ protect pattern0 [0][8]
	UINT32 reg_dj_pattern0_0_09             :2;	//19:18	//DJ protect pattern0 [0][9]
	UINT32 reg_dj_pattern0_0_10             :2;	//21:20	//DJ protect pattern0 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B318 RW
	UINT32 reg_dj_pattern0_1_00             :2;	//1:0	//DJ protect pattern0 [1][0]
	UINT32 reg_dj_pattern0_1_01             :2;	//3:2	//DJ protect pattern0 [1][1]
	UINT32 reg_dj_pattern0_1_02             :2;	//5:4	//DJ protect pattern0 [1][2]
	UINT32 reg_dj_pattern0_1_03             :2;	//7:6	//DJ protect pattern0 [1][3]
	UINT32 reg_dj_pattern0_1_04             :2;	//9:8	//DJ protect pattern0 [1][4]
	UINT32 reg_dj_pattern0_1_05             :2;	//11:10	//DJ protect pattern0 [1][5]
	UINT32 reg_dj_pattern0_1_06             :2;	//13:12	//DJ protect pattern0 [1][6]
	UINT32 reg_dj_pattern0_1_07             :2;	//15:14	//DJ protect pattern0 [1][7]
	UINT32 reg_dj_pattern0_1_08             :2;	//17:16	//DJ protect pattern0 [1][8]
	UINT32 reg_dj_pattern0_1_09             :2;	//19:18	//DJ protect pattern0 [1][9]
	UINT32 reg_dj_pattern0_1_10             :2;	//21:20	//DJ protect pattern0 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B31C RW
	UINT32 reg_dj_pattern0_2_00             :2;	//1:0	//DJ protect pattern0 [2][0]
	UINT32 reg_dj_pattern0_2_01             :2;	//3:2	//DJ protect pattern0 [2][1]
	UINT32 reg_dj_pattern0_2_02             :2;	//5:4	//DJ protect pattern0 [2][2]
	UINT32 reg_dj_pattern0_2_03             :2;	//7:6	//DJ protect pattern0 [2][3]
	UINT32 reg_dj_pattern0_2_04             :2;	//9:8	//DJ protect pattern0 [2][4]
	UINT32 reg_dj_pattern0_2_05             :2;	//11:10	//DJ protect pattern0 [2][5]
	UINT32 reg_dj_pattern0_2_06             :2;	//13:12	//DJ protect pattern0 [2][6]
	UINT32 reg_dj_pattern0_2_07             :2;	//15:14	//DJ protect pattern0 [2][7]
	UINT32 reg_dj_pattern0_2_08             :2;	//17:16	//DJ protect pattern0 [2][8]
	UINT32 reg_dj_pattern0_2_09             :2;	//19:18	//DJ protect pattern0 [2][9]
	UINT32 reg_dj_pattern0_2_10             :2;	//21:20	//DJ protect pattern0 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B320 RW
	UINT32 reg_dj_pattern0_3_00             :2;	//1:0	//DJ protect pattern0 [3][0]
	UINT32 reg_dj_pattern0_3_01             :2;	//3:2	//DJ protect pattern0 [3][1]
	UINT32 reg_dj_pattern0_3_02             :2;	//5:4	//DJ protect pattern0 [3][2]
	UINT32 reg_dj_pattern0_3_03             :2;	//7:6	//DJ protect pattern0 [3][3]
	UINT32 reg_dj_pattern0_3_04             :2;	//9:8	//DJ protect pattern0 [3][4]
	UINT32 reg_dj_pattern0_3_05             :2;	//11:10	//DJ protect pattern0 [3][5]
	UINT32 reg_dj_pattern0_3_06             :2;	//13:12	//DJ protect pattern0 [3][6]
	UINT32 reg_dj_pattern0_3_07             :2;	//15:14	//DJ protect pattern0 [3][7]
	UINT32 reg_dj_pattern0_3_08             :2;	//17:16	//DJ protect pattern0 [3][8]
	UINT32 reg_dj_pattern0_3_09             :2;	//19:18	//DJ protect pattern0 [3][9]
	UINT32 reg_dj_pattern0_3_10             :2;	//21:20	//DJ protect pattern0 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B324 RW
	UINT32 reg_dj_pattern0_4_00             :2;	//1:0	//DJ protect pattern0 [4][0]
	UINT32 reg_dj_pattern0_4_01             :2;	//3:2	//DJ protect pattern0 [4][1]
	UINT32 reg_dj_pattern0_4_02             :2;	//5:4	//DJ protect pattern0 [4][2]
	UINT32 reg_dj_pattern0_4_03             :2;	//7:6	//DJ protect pattern0 [4][3]
	UINT32 reg_dj_pattern0_4_04             :2;	//9:8	//DJ protect pattern0 [4][4]
	UINT32 reg_dj_pattern0_4_05             :2;	//11:10	//DJ protect pattern0 [4][5]
	UINT32 reg_dj_pattern0_4_06             :2;	//13:12	//DJ protect pattern0 [4][6]
	UINT32 reg_dj_pattern0_4_07             :2;	//15:14	//DJ protect pattern0 [4][7]
	UINT32 reg_dj_pattern0_4_08             :2;	//17:16	//DJ protect pattern0 [4][8]
	UINT32 reg_dj_pattern0_4_09             :2;	//19:18	//DJ protect pattern0 [4][9]
	UINT32 reg_dj_pattern0_4_10             :2;	//21:20	//DJ protect pattern0 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B328 RW
	UINT32 reg_dj_pattern0_5_00             :2;	//1:0	//DJ protect pattern0 [5][0]
	UINT32 reg_dj_pattern0_5_01             :2;	//3:2	//DJ protect pattern0 [5][1]
	UINT32 reg_dj_pattern0_5_02             :2;	//5:4	//DJ protect pattern0 [5][2]
	UINT32 reg_dj_pattern0_5_03             :2;	//7:6	//DJ protect pattern0 [5][3]
	UINT32 reg_dj_pattern0_5_04             :2;	//9:8	//DJ protect pattern0 [5][4]
	UINT32 reg_dj_pattern0_5_05             :2;	//11:10	//DJ protect pattern0 [5][5]
	UINT32 reg_dj_pattern0_5_06             :2;	//13:12	//DJ protect pattern0 [5][6]
	UINT32 reg_dj_pattern0_5_07             :2;	//15:14	//DJ protect pattern0 [5][7]
	UINT32 reg_dj_pattern0_5_08             :2;	//17:16	//DJ protect pattern0 [5][8]
	UINT32 reg_dj_pattern0_5_09             :2;	//19:18	//DJ protect pattern0 [5][9]
	UINT32 reg_dj_pattern0_5_10             :2;	//21:20	//DJ protect pattern0 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B32C RW
	UINT32 reg_dj_pattern0_6_00             :2;	//1:0	//DJ protect pattern0 [6][0]
	UINT32 reg_dj_pattern0_6_01             :2;	//3:2	//DJ protect pattern0 [6][1]
	UINT32 reg_dj_pattern0_6_02             :2;	//5:4	//DJ protect pattern0 [6][2]
	UINT32 reg_dj_pattern0_6_03             :2;	//7:6	//DJ protect pattern0 [6][3]
	UINT32 reg_dj_pattern0_6_04             :2;	//9:8	//DJ protect pattern0 [6][4]
	UINT32 reg_dj_pattern0_6_05             :2;	//11:10	//DJ protect pattern0 [6][5]
	UINT32 reg_dj_pattern0_6_06             :2;	//13:12	//DJ protect pattern0 [6][6]
	UINT32 reg_dj_pattern0_6_07             :2;	//15:14	//DJ protect pattern0 [6][7]
	UINT32 reg_dj_pattern0_6_08             :2;	//17:16	//DJ protect pattern0 [6][8]
	UINT32 reg_dj_pattern0_6_09             :2;	//19:18	//DJ protect pattern0 [6][9]
	UINT32 reg_dj_pattern0_6_10             :2;	//21:20	//DJ protect pattern0 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B330 RW
	UINT32 reg_dj_pattern0_flip0_h          :1;	//0:0	//DJ protect pattern0 flip0, H
	UINT32 reg_dj_pattern0_flip0_v          :1;	//1:1	//DJ protect pattern0 flip0, V
	UINT32 reg_dj_pattern0_flip1_h          :1;	//2:2	//DJ protect pattern0 flip1, H
	UINT32 reg_dj_pattern0_flip1_v          :1;	//3:3	//DJ protect pattern0 flip1, V
	UINT32 reg_dj_pattern0_flip2_h          :1;	//4:4	//DJ protect pattern0 flip2, H
	UINT32 reg_dj_pattern0_flip2_v          :1;	//5:5	//DJ protect pattern0 flip2, V
	UINT32 reg_dj_pattern0_flip3_h          :1;	//6:6	//DJ protect pattern0 flip3, H
	UINT32 reg_dj_pattern0_flip3_v          :1;	//7:7	//DJ protect pattern0 flip3, V
	UINT32 resvd                            :24;
	};
}REG_SHY_2K_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B334 RW
	UINT32 reg_dj_pattern1_0_00             :2;	//1:0	//DJ protect pattern1 [0][0]
	UINT32 reg_dj_pattern1_0_01             :2;	//3:2	//DJ protect pattern1 [0][1]
	UINT32 reg_dj_pattern1_0_02             :2;	//5:4	//DJ protect pattern1 [0][2]
	UINT32 reg_dj_pattern1_0_03             :2;	//7:6	//DJ protect pattern1 [0][3]
	UINT32 reg_dj_pattern1_0_04             :2;	//9:8	//DJ protect pattern1 [0][4]
	UINT32 reg_dj_pattern1_0_05             :2;	//11:10	//DJ protect pattern1 [0][5]
	UINT32 reg_dj_pattern1_0_06             :2;	//13:12	//DJ protect pattern1 [0][6]
	UINT32 reg_dj_pattern1_0_07             :2;	//15:14	//DJ protect pattern1 [0][7]
	UINT32 reg_dj_pattern1_0_08             :2;	//17:16	//DJ protect pattern1 [0][8]
	UINT32 reg_dj_pattern1_0_09             :2;	//19:18	//DJ protect pattern1 [0][9]
	UINT32 reg_dj_pattern1_0_10             :2;	//21:20	//DJ protect pattern1 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B338 RW
	UINT32 reg_dj_pattern1_1_00             :2;	//1:0	//DJ protect pattern1 [1][0]
	UINT32 reg_dj_pattern1_1_01             :2;	//3:2	//DJ protect pattern1 [1][1]
	UINT32 reg_dj_pattern1_1_02             :2;	//5:4	//DJ protect pattern1 [1][2]
	UINT32 reg_dj_pattern1_1_03             :2;	//7:6	//DJ protect pattern1 [1][3]
	UINT32 reg_dj_pattern1_1_04             :2;	//9:8	//DJ protect pattern1 [1][4]
	UINT32 reg_dj_pattern1_1_05             :2;	//11:10	//DJ protect pattern1 [1][5]
	UINT32 reg_dj_pattern1_1_06             :2;	//13:12	//DJ protect pattern1 [1][6]
	UINT32 reg_dj_pattern1_1_07             :2;	//15:14	//DJ protect pattern1 [1][7]
	UINT32 reg_dj_pattern1_1_08             :2;	//17:16	//DJ protect pattern1 [1][8]
	UINT32 reg_dj_pattern1_1_09             :2;	//19:18	//DJ protect pattern1 [1][9]
	UINT32 reg_dj_pattern1_1_10             :2;	//21:20	//DJ protect pattern1 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B33C RW
	UINT32 reg_dj_pattern1_2_00             :2;	//1:0	//DJ protect pattern1 [2][0]
	UINT32 reg_dj_pattern1_2_01             :2;	//3:2	//DJ protect pattern1 [2][1]
	UINT32 reg_dj_pattern1_2_02             :2;	//5:4	//DJ protect pattern1 [2][2]
	UINT32 reg_dj_pattern1_2_03             :2;	//7:6	//DJ protect pattern1 [2][3]
	UINT32 reg_dj_pattern1_2_04             :2;	//9:8	//DJ protect pattern1 [2][4]
	UINT32 reg_dj_pattern1_2_05             :2;	//11:10	//DJ protect pattern1 [2][5]
	UINT32 reg_dj_pattern1_2_06             :2;	//13:12	//DJ protect pattern1 [2][6]
	UINT32 reg_dj_pattern1_2_07             :2;	//15:14	//DJ protect pattern1 [2][7]
	UINT32 reg_dj_pattern1_2_08             :2;	//17:16	//DJ protect pattern1 [2][8]
	UINT32 reg_dj_pattern1_2_09             :2;	//19:18	//DJ protect pattern1 [2][9]
	UINT32 reg_dj_pattern1_2_10             :2;	//21:20	//DJ protect pattern1 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B340 RW
	UINT32 reg_dj_pattern1_3_00             :2;	//1:0	//DJ protect pattern1 [3][0]
	UINT32 reg_dj_pattern1_3_01             :2;	//3:2	//DJ protect pattern1 [3][1]
	UINT32 reg_dj_pattern1_3_02             :2;	//5:4	//DJ protect pattern1 [3][2]
	UINT32 reg_dj_pattern1_3_03             :2;	//7:6	//DJ protect pattern1 [3][3]
	UINT32 reg_dj_pattern1_3_04             :2;	//9:8	//DJ protect pattern1 [3][4]
	UINT32 reg_dj_pattern1_3_05             :2;	//11:10	//DJ protect pattern1 [3][5]
	UINT32 reg_dj_pattern1_3_06             :2;	//13:12	//DJ protect pattern1 [3][6]
	UINT32 reg_dj_pattern1_3_07             :2;	//15:14	//DJ protect pattern1 [3][7]
	UINT32 reg_dj_pattern1_3_08             :2;	//17:16	//DJ protect pattern1 [3][8]
	UINT32 reg_dj_pattern1_3_09             :2;	//19:18	//DJ protect pattern1 [3][9]
	UINT32 reg_dj_pattern1_3_10             :2;	//21:20	//DJ protect pattern1 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B344 RW
	UINT32 reg_dj_pattern1_4_00             :2;	//1:0	//DJ protect pattern1 [4][0]
	UINT32 reg_dj_pattern1_4_01             :2;	//3:2	//DJ protect pattern1 [4][1]
	UINT32 reg_dj_pattern1_4_02             :2;	//5:4	//DJ protect pattern1 [4][2]
	UINT32 reg_dj_pattern1_4_03             :2;	//7:6	//DJ protect pattern1 [4][3]
	UINT32 reg_dj_pattern1_4_04             :2;	//9:8	//DJ protect pattern1 [4][4]
	UINT32 reg_dj_pattern1_4_05             :2;	//11:10	//DJ protect pattern1 [4][5]
	UINT32 reg_dj_pattern1_4_06             :2;	//13:12	//DJ protect pattern1 [4][6]
	UINT32 reg_dj_pattern1_4_07             :2;	//15:14	//DJ protect pattern1 [4][7]
	UINT32 reg_dj_pattern1_4_08             :2;	//17:16	//DJ protect pattern1 [4][8]
	UINT32 reg_dj_pattern1_4_09             :2;	//19:18	//DJ protect pattern1 [4][9]
	UINT32 reg_dj_pattern1_4_10             :2;	//21:20	//DJ protect pattern1 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B348 RW
	UINT32 reg_dj_pattern1_5_00             :2;	//1:0	//DJ protect pattern1 [5][0]
	UINT32 reg_dj_pattern1_5_01             :2;	//3:2	//DJ protect pattern1 [5][1]
	UINT32 reg_dj_pattern1_5_02             :2;	//5:4	//DJ protect pattern1 [5][2]
	UINT32 reg_dj_pattern1_5_03             :2;	//7:6	//DJ protect pattern1 [5][3]
	UINT32 reg_dj_pattern1_5_04             :2;	//9:8	//DJ protect pattern1 [5][4]
	UINT32 reg_dj_pattern1_5_05             :2;	//11:10	//DJ protect pattern1 [5][5]
	UINT32 reg_dj_pattern1_5_06             :2;	//13:12	//DJ protect pattern1 [5][6]
	UINT32 reg_dj_pattern1_5_07             :2;	//15:14	//DJ protect pattern1 [5][7]
	UINT32 reg_dj_pattern1_5_08             :2;	//17:16	//DJ protect pattern1 [5][8]
	UINT32 reg_dj_pattern1_5_09             :2;	//19:18	//DJ protect pattern1 [5][9]
	UINT32 reg_dj_pattern1_5_10             :2;	//21:20	//DJ protect pattern1 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B34C RW
	UINT32 reg_dj_pattern1_6_00             :2;	//1:0	//DJ protect pattern1 [6][0]
	UINT32 reg_dj_pattern1_6_01             :2;	//3:2	//DJ protect pattern1 [6][1]
	UINT32 reg_dj_pattern1_6_02             :2;	//5:4	//DJ protect pattern1 [6][2]
	UINT32 reg_dj_pattern1_6_03             :2;	//7:6	//DJ protect pattern1 [6][3]
	UINT32 reg_dj_pattern1_6_04             :2;	//9:8	//DJ protect pattern1 [6][4]
	UINT32 reg_dj_pattern1_6_05             :2;	//11:10	//DJ protect pattern1 [6][5]
	UINT32 reg_dj_pattern1_6_06             :2;	//13:12	//DJ protect pattern1 [6][6]
	UINT32 reg_dj_pattern1_6_07             :2;	//15:14	//DJ protect pattern1 [6][7]
	UINT32 reg_dj_pattern1_6_08             :2;	//17:16	//DJ protect pattern1 [6][8]
	UINT32 reg_dj_pattern1_6_09             :2;	//19:18	//DJ protect pattern1 [6][9]
	UINT32 reg_dj_pattern1_6_10             :2;	//21:20	//DJ protect pattern1 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B350 RW
	UINT32 reg_dj_pattern1_flip0_h          :1;	//0:0	//DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//1:1	//DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//2:2	//DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//3:3	//DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}REG_SHY_2K_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B354 RW
	UINT32 reg_dj_pattern2_0_00             :2;	//1:0	//DJ protect pattern2 [0][0]
	UINT32 reg_dj_pattern2_0_01             :2;	//3:2	//DJ protect pattern2 [0][1]
	UINT32 reg_dj_pattern2_0_02             :2;	//5:4	//DJ protect pattern2 [0][2]
	UINT32 reg_dj_pattern2_0_03             :2;	//7:6	//DJ protect pattern2 [0][3]
	UINT32 reg_dj_pattern2_0_04             :2;	//9:8	//DJ protect pattern2 [0][4]
	UINT32 reg_dj_pattern2_0_05             :2;	//11:10	//DJ protect pattern2 [0][5]
	UINT32 reg_dj_pattern2_0_06             :2;	//13:12	//DJ protect pattern2 [0][6]
	UINT32 reg_dj_pattern2_0_07             :2;	//15:14	//DJ protect pattern2 [0][7]
	UINT32 reg_dj_pattern2_0_08             :2;	//17:16	//DJ protect pattern2 [0][8]
	UINT32 reg_dj_pattern2_0_09             :2;	//19:18	//DJ protect pattern2 [0][9]
	UINT32 reg_dj_pattern2_0_10             :2;	//21:20	//DJ protect pattern2 [0][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B358 RW
	UINT32 reg_dj_pattern2_1_00             :2;	//1:0	//DJ protect pattern2 [1][0]
	UINT32 reg_dj_pattern2_1_01             :2;	//3:2	//DJ protect pattern2 [1][1]
	UINT32 reg_dj_pattern2_1_02             :2;	//5:4	//DJ protect pattern2 [1][2]
	UINT32 reg_dj_pattern2_1_03             :2;	//7:6	//DJ protect pattern2 [1][3]
	UINT32 reg_dj_pattern2_1_04             :2;	//9:8	//DJ protect pattern2 [1][4]
	UINT32 reg_dj_pattern2_1_05             :2;	//11:10	//DJ protect pattern2 [1][5]
	UINT32 reg_dj_pattern2_1_06             :2;	//13:12	//DJ protect pattern2 [1][6]
	UINT32 reg_dj_pattern2_1_07             :2;	//15:14	//DJ protect pattern2 [1][7]
	UINT32 reg_dj_pattern2_1_08             :2;	//17:16	//DJ protect pattern2 [1][8]
	UINT32 reg_dj_pattern2_1_09             :2;	//19:18	//DJ protect pattern2 [1][9]
	UINT32 reg_dj_pattern2_1_10             :2;	//21:20	//DJ protect pattern2 [1][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B35C RW
	UINT32 reg_dj_pattern2_2_00             :2;	//1:0	//DJ protect pattern2 [2][0]
	UINT32 reg_dj_pattern2_2_01             :2;	//3:2	//DJ protect pattern2 [2][1]
	UINT32 reg_dj_pattern2_2_02             :2;	//5:4	//DJ protect pattern2 [2][2]
	UINT32 reg_dj_pattern2_2_03             :2;	//7:6	//DJ protect pattern2 [2][3]
	UINT32 reg_dj_pattern2_2_04             :2;	//9:8	//DJ protect pattern2 [2][4]
	UINT32 reg_dj_pattern2_2_05             :2;	//11:10	//DJ protect pattern2 [2][5]
	UINT32 reg_dj_pattern2_2_06             :2;	//13:12	//DJ protect pattern2 [2][6]
	UINT32 reg_dj_pattern2_2_07             :2;	//15:14	//DJ protect pattern2 [2][7]
	UINT32 reg_dj_pattern2_2_08             :2;	//17:16	//DJ protect pattern2 [2][8]
	UINT32 reg_dj_pattern2_2_09             :2;	//19:18	//DJ protect pattern2 [2][9]
	UINT32 reg_dj_pattern2_2_10             :2;	//21:20	//DJ protect pattern2 [2][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B360 RW
	UINT32 reg_dj_pattern2_3_00             :2;	//1:0	//DJ protect pattern2 [3][0]
	UINT32 reg_dj_pattern2_3_01             :2;	//3:2	//DJ protect pattern2 [3][1]
	UINT32 reg_dj_pattern2_3_02             :2;	//5:4	//DJ protect pattern2 [3][2]
	UINT32 reg_dj_pattern2_3_03             :2;	//7:6	//DJ protect pattern2 [3][3]
	UINT32 reg_dj_pattern2_3_04             :2;	//9:8	//DJ protect pattern2 [3][4]
	UINT32 reg_dj_pattern2_3_05             :2;	//11:10	//DJ protect pattern2 [3][5]
	UINT32 reg_dj_pattern2_3_06             :2;	//13:12	//DJ protect pattern2 [3][6]
	UINT32 reg_dj_pattern2_3_07             :2;	//15:14	//DJ protect pattern2 [3][7]
	UINT32 reg_dj_pattern2_3_08             :2;	//17:16	//DJ protect pattern2 [3][8]
	UINT32 reg_dj_pattern2_3_09             :2;	//19:18	//DJ protect pattern2 [3][9]
	UINT32 reg_dj_pattern2_3_10             :2;	//21:20	//DJ protect pattern2 [3][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B364 RW
	UINT32 reg_dj_pattern2_4_00             :2;	//1:0	//DJ protect pattern2 [4][0]
	UINT32 reg_dj_pattern2_4_01             :2;	//3:2	//DJ protect pattern2 [4][1]
	UINT32 reg_dj_pattern2_4_02             :2;	//5:4	//DJ protect pattern2 [4][2]
	UINT32 reg_dj_pattern2_4_03             :2;	//7:6	//DJ protect pattern2 [4][3]
	UINT32 reg_dj_pattern2_4_04             :2;	//9:8	//DJ protect pattern2 [4][4]
	UINT32 reg_dj_pattern2_4_05             :2;	//11:10	//DJ protect pattern2 [4][5]
	UINT32 reg_dj_pattern2_4_06             :2;	//13:12	//DJ protect pattern2 [4][6]
	UINT32 reg_dj_pattern2_4_07             :2;	//15:14	//DJ protect pattern2 [4][7]
	UINT32 reg_dj_pattern2_4_08             :2;	//17:16	//DJ protect pattern2 [4][8]
	UINT32 reg_dj_pattern2_4_09             :2;	//19:18	//DJ protect pattern2 [4][9]
	UINT32 reg_dj_pattern2_4_10             :2;	//21:20	//DJ protect pattern2 [4][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B368 RW
	UINT32 reg_dj_pattern2_5_00             :2;	//1:0	//DJ protect pattern2 [5][0]
	UINT32 reg_dj_pattern2_5_01             :2;	//3:2	//DJ protect pattern2 [5][1]
	UINT32 reg_dj_pattern2_5_02             :2;	//5:4	//DJ protect pattern2 [5][2]
	UINT32 reg_dj_pattern2_5_03             :2;	//7:6	//DJ protect pattern2 [5][3]
	UINT32 reg_dj_pattern2_5_04             :2;	//9:8	//DJ protect pattern2 [5][4]
	UINT32 reg_dj_pattern2_5_05             :2;	//11:10	//DJ protect pattern2 [5][5]
	UINT32 reg_dj_pattern2_5_06             :2;	//13:12	//DJ protect pattern2 [5][6]
	UINT32 reg_dj_pattern2_5_07             :2;	//15:14	//DJ protect pattern2 [5][7]
	UINT32 reg_dj_pattern2_5_08             :2;	//17:16	//DJ protect pattern2 [5][8]
	UINT32 reg_dj_pattern2_5_09             :2;	//19:18	//DJ protect pattern2 [5][9]
	UINT32 reg_dj_pattern2_5_10             :2;	//21:20	//DJ protect pattern2 [5][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B36C RW
	UINT32 reg_dj_pattern2_6_00             :2;	//1:0	//DJ protect pattern2 [6][0]
	UINT32 reg_dj_pattern2_6_01             :2;	//3:2	//DJ protect pattern2 [6][1]
	UINT32 reg_dj_pattern2_6_02             :2;	//5:4	//DJ protect pattern2 [6][2]
	UINT32 reg_dj_pattern2_6_03             :2;	//7:6	//DJ protect pattern2 [6][3]
	UINT32 reg_dj_pattern2_6_04             :2;	//9:8	//DJ protect pattern2 [6][4]
	UINT32 reg_dj_pattern2_6_05             :2;	//11:10	//DJ protect pattern2 [6][5]
	UINT32 reg_dj_pattern2_6_06             :2;	//13:12	//DJ protect pattern2 [6][6]
	UINT32 reg_dj_pattern2_6_07             :2;	//15:14	//DJ protect pattern2 [6][7]
	UINT32 reg_dj_pattern2_6_08             :2;	//17:16	//DJ protect pattern2 [6][8]
	UINT32 reg_dj_pattern2_6_09             :2;	//19:18	//DJ protect pattern2 [6][9]
	UINT32 reg_dj_pattern2_6_10             :2;	//21:20	//DJ protect pattern2 [6][10]
	UINT32 resvd                            :10;
	};
}REG_SHY_2K_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B370 RW
	UINT32 reg_dj_pattern2_flip0_h          :1;	//0:0	//DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//1:1	//DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//2:2	//DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//3:3	//DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}REG_SHY_2K_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B374 RW
	UINT32 reg_dj_soft_g0_mul               :6;	//5:0	//Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//12:8	//Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//23:16	//Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}REG_SHY_2K_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B378 RW
	UINT32 reg_dj_soft_g1_mul               :6;	//5:0	//Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//12:8	//Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//23:16	//Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}REG_SHY_2K_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B37C RW
	UINT32 reg_dj_soft_g2_mul               :6;	//5:0	//Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//12:8	//Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//23:16	//Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}REG_SHY_2K_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B380 RW
	UINT32 reg_dj_soft_base                 :8;	//7:0	//Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//15:8	//Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//16:16	//Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}REG_SHY_2K_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B390 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B394 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B3A0 RW
	UINT32 reg_win_dj_win0_en               :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_win_dj_win1_en               :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_win_dj_win01_en              :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_dj_win_outside           :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_win_dj_win_en                :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_win_dj_bdr_alpha             :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_win_dj_bdr_wid               :2;	//14:13	//border width
	UINT32 reg_win_dj_bdr_en                :1;	//15:15	//border enable
	UINT32 reg_win_dj_cr5                   :5;	//20:16	//border color: cr5
	UINT32 reg_win_dj_cb5                   :5;	//25:21	//border color: cb5
	UINT32 reg_win_dj_yy6                   :6;	//31:26	//border color: yy6
	};
}REG_SHY_2K_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B3A4 RW
	UINT32 reg_win_dj_win_w0_x0             :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y0             :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B3A8 RW
	UINT32 reg_win_dj_win_w0_x1             :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w0_y1             :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B3AC RW
	UINT32 reg_win_dj_win_w1_x0             :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y0             :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B3B0 RW
	UINT32 reg_win_dj_win_w1_x1             :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_win_dj_win_w1_y1             :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B500 RO
	UINT32 reg_mon_core_fin_out_vert_cnt    :12;	//11:0	//Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_mon_core_fin_in_vert_cnt     :12;	//27:16	//Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B504 RO
	UINT32 reg_mon_in_vert_cnt              :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_in_hori_cnt              :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B508 RO
	UINT32 reg_mon_out_vert_cnt             :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_out_hori_cnt             :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B50C RO
	UINT32 reg_mon_fin_out_vert_cnt         :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_mon_fin_in_vert_cnt          :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}REG_SHY_2K_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B510 RO
	UINT32 reg_mon_shp_i_sucfail            :32;	//31:0	//Input success/fail monitoring register
	};
}REG_SHY_2K_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B514 RO
	UINT32 reg_mon_shp_o_sucfail            :32;	//31:0	//Output success/fail monitoring register
	};
}REG_SHY_2K_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B560 RO
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B564 RO
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B568 RO
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B56C RO
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B600 RO
	UINT32 ro_tmap_status_window0           :32;	//31:0	//
	};
}REG_SHY_2K_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B604 RO
	UINT32 ro_tmap_status_window1           :32;	//31:0	//
	};
}REG_SHY_2K_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B608 RO
	UINT32 ro_tmap_status_0                 :16;	//15:0	//
	UINT32 ro_tmap_status_1                 :16;	//31:16	//
	};
}REG_SHY_2K_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B60C RO
	UINT32 ro_tmap_status_2                 :16;	//15:0	//
	UINT32 ro_tmap_status_3                 :16;	//31:16	//
	};
}REG_SHY_2K_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B610 RO
	UINT32 ro_tmap_status_4                 :16;	//15:0	//
	UINT32 ro_tmap_status_5                 :16;	//31:16	//
	};
}REG_SHY_2K_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B614 RO
	UINT32 ro_tmap_status_6                 :16;	//15:0	//
	UINT32 ro_tmap_status_7                 :16;	//31:16	//
	};
}REG_SHY_2K_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B618 RO
	UINT32 ro_tmap_status_8                 :16;	//15:0	//
	UINT32 ro_tmap_status_9                 :16;	//31:16	//
	};
}REG_SHY_2K_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B61C RO
	UINT32 ro_tmap_status_10                :16;	//15:0	//
	UINT32 ro_tmap_status_11                :16;	//31:16	//
	};
}REG_SHY_2K_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B6F0 RW
	UINT32 cvd_pattern_detect               :1 ;	//reserved
	UINT32 color_bar                        :1 ;	//reserved
	UINT32 vfy_glb_en                       :1 ;	//VFILTER_CTRL_01, reg_glb_vflt_en
	UINT32 resvd0                           :29;
	};
}REG_SHY_2K_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B6F4 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B6F8 RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901B6FC RW
	UINT32 tdata0                           :32;
	};
}REG_SHY_2K_SHP_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C900 RW
	UINT32 reg_sr_merge_en                  :1;	//0:0	//0 : core bypass	1 : SR_MERGE enable
	UINT32 resvd0                           :3;
	UINT32 reg_sr_merge_demo_mode_en        :1;	//4:4	//0 : demo mode off	1 : demo mode on
	UINT32 reg_sr_merge_demo_mode           :1;	//5:5	//0 : inside window - SR 	1 : outsie window - SR
	UINT32 resvd1                           :2;
	UINT32 reg_sr_merge_master_gain         :8;	//15:8	//final alpha blending weight 	255 : result = input scale-up image	0   : result = SR_MERGE blended image
	UINT32 reg_sr_merge_ti_en               :1;	//16:16	//0 : TI processing off 	1 : TI processing on
	UINT32 resvd2                           :11;
	UINT32 reg_sr_merge_debug_mode          :3;	//30:28	//0 : SR_MERGE result (default)	1 : mmd blending gain	2 : NR gain	3 : TI gain 	4 : sobel gain 	5 : input residual image	6 : (SR_MERGE output - Scale_Up image)
	UINT32 resvd3                           :1;
	};
}REG_MERG_SR_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C904 RW
	UINT32 reg_sr_merge_width               :16;	//15:0	//input image width (default : 7680)
	UINT32 reg_sr_merge_height              :16;	//31:16	//input image height (default : 4320)
	};
}REG_MERG_SR_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C910 RW
	UINT32 reg_sr_merge_core0_width         :16;	//15:0	//input image width (default : 1920+64*2)
	UINT32 reg_sr_merge_core0_height        :16;	//31:16	//input image height (default : 4320 - for 8K)
	};
}REG_MERG_SR_MERGE_CORE0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C914 RW
	UINT32 reg_sr_merge_core1_width         :16;	//15:0	//input image width (default : 1920+64*2)
	UINT32 reg_sr_merge_core1_height        :16;	//31:16	//input image height (default : 4320 - for 8K)
	};
}REG_MERG_SR_MERGE_CORE1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C918 RW
	UINT32 reg_sr_merge_core2_width         :16;	//15:0	//input image width (default : 1920+64*2)
	UINT32 reg_sr_merge_core2_height        :16;	//31:16	//input image height (default : 4320 - for 8K)
	};
}REG_MERG_SR_MERGE_CORE2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C91C RW
	UINT32 reg_sr_merge_core3_width         :16;	//15:0	//input image width (default : 1920+64*2)
	UINT32 reg_sr_merge_core3_height        :16;	//31:16	//input image height (default : 4320 - for 8K)
	};
}REG_MERG_SR_MERGE_CORE3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C920 RW
	UINT32 reg_sr_merge_demo_core0_start_pts_x0 :16;	//15:0	//window start point (for demo mode)- only even value
	UINT32 reg_sr_merge_demo_core0_start_pts_y0 :16;	//31:16	//window start point (for demo mode)
	};
}REG_MERG_SR_MERGE_CORE0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C924 RW
	UINT32 reg_sr_merge_demo_core0_end_pts_x1 :16;	//15:0	//window end point (for demo mode) - only odd value
	UINT32 reg_sr_merge_demo_core0_end_pts_y1 :16;	//31:16	//window end point (for demo mode)
	};
}REG_MERG_SR_MERGE_CORE0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C928 RW
	UINT32 reg_sr_merge_demo_core1_start_pts_x0 :16;	//15:0	//window start point (for demo mode)- only even value
	UINT32 reg_sr_merge_demo_core1_start_pts_y0 :16;	//31:16	//window start point (for demo mode)
	};
}REG_MERG_SR_MERGE_CORE1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C92C RW
	UINT32 reg_sr_merge_demo_core1_end_pts_x1 :16;	//15:0	//window end point (for demo mode) - only odd value
	UINT32 reg_sr_merge_demo_core1_end_pts_y1 :16;	//31:16	//window end point (for demo mode)
	};
}REG_MERG_SR_MERGE_CORE1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C930 RW
	UINT32 reg_sr_merge_demo_core2_start_pts_x0 :16;	//15:0	//window start point (for demo mode)- only even value
	UINT32 reg_sr_merge_demo_core2_start_pts_y0 :16;	//31:16	//window start point (for demo mode)
	};
}REG_MERG_SR_MERGE_CORE2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C934 RW
	UINT32 reg_sr_merge_demo_core2_end_pts_x1 :16;	//15:0	//window end point (for demo mode) - only odd value
	UINT32 reg_sr_merge_demo_core2_end_pts_y1 :16;	//31:16	//window end point (for demo mode)
	};
}REG_MERG_SR_MERGE_CORE2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C938 RW
	UINT32 reg_sr_merge_demo_core3_start_pts_x0 :16;	//15:0	//window start point (for demo mode)- only even value
	UINT32 reg_sr_merge_demo_core3_start_pts_y0 :16;	//31:16	//window start point (for demo mode)
	};
}REG_MERG_SR_MERGE_CORE3_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C93C RW
	UINT32 reg_sr_merge_demo_core3_end_pts_x1 :16;	//15:0	//window end point (for demo mode) - only odd value
	UINT32 reg_sr_merge_demo_core3_end_pts_y1 :16;	//31:16	//window end point (for demo mode)
	};
}REG_MERG_SR_MERGE_CORE3_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C940 RW
	UINT32 reg_ups_split_pmode_out          :3;	//2:0	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd0                           :1;
	UINT32 reg_ups_split_pmode_in           :3;	//6:4	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd1                           :1;
	UINT32 reg_ups_split_split_mode         :2;	//9:8	//Split Configuation Select	0 := (S0 + 2GB) + (GB+S1+GB) + (GB+S2+GB) + (2GB+S3)	2 = (S0 + GB) + (GB+S1+GB) + (GB+S2+GB) + (GB+S3)	3 = (S0 + 0) + (GB+S1+0) + (GB+S2+0) + (GB+S3)
	UINT32 resvd2                           :2;
	UINT32 reg_ups_split_sync_mode          :1;	//12 //0:= ready-valid mode	1 = sync_mode
	UINT32 resvd3                           :3;
	UINT32 reg_ups_split_hsize              :13;	//28:16	//
	UINT32 resvd4                           :3;
	};
}REG_MERG_SR_MERGE_UPS_SPLIT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C944 RW
	UINT32 reg_ups_split_split_size         :13;	//12:0	//split size ( size in unit pixels)	ex) split-4 case	reg_split_size = reg_hsize / 4
	UINT32 resvd0                           :3;
	UINT32 reg_ups_split_guardband          :13;	//28:16	//guardband (size in unit pixels)
	UINT32 resvd1                           :3;
	};
}REG_MERG_SR_MERGE_UPS_SPLIT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C948 RW
	UINT32 reg_ups_split_split_ctrl_02      :32;	//31:0	//reserved
	};
}REG_MERG_SR_MERGE_UPS_SPLIT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C94C RW
	UINT32 reg_ups_split_split_ctrl_03      :32;	//31:0	//reserved
	};
}REG_MERG_SR_MERGE_UPS_SPLIT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C950 RW
	UINT32 reg_res_split_pmode_out          :3;	//2:0	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd0                           :1;
	UINT32 reg_res_split_pmode_in           :3;	//6:4	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd1                           :1;
	UINT32 reg_res_split_split_mode         :2;	//9:8	//Split Configuation Select	0 := (S0 + 2GB) + (GB+S1+GB) + (GB+S2+GB) + (2GB+S3)	2 = (S0 + GB) + (GB+S1+GB) + (GB+S2+GB) + (GB+S3)	3 = (S0 + 0) + (GB+S1+0) + (GB+S2+0) + (GB+S3)
	UINT32 resvd2                           :2;
	UINT32 reg_res_split_sync_mode          :1;	//12 //0:= ready-valid mode	1 = sync_mode
	UINT32 resvd3                           :3;
	UINT32 reg_res_split_hsize              :13;	//28:16	//
	UINT32 resvd4                           :3;
	};
}REG_MERG_SR_MERGE_RES_SPLIT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C954 RW
	UINT32 reg_res_split_split_size         :13;	//12:0	//split size ( size in unit pixels)	ex) split-4 case	reg_split_size = reg_hsize / 4
	UINT32 resvd0                           :3;
	UINT32 reg_res_split_guardband          :13;	//28:16	//guardband (size in unit pixels)
	UINT32 resvd1                           :3;
	};
}REG_MERG_SR_MERGE_RES_SPLIT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C958 RW
	UINT32 reg_res_split_split_ctrl_02      :32;	//31:0	//reserved
	};
}REG_MERG_SR_MERGE_RES_SPLIT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C95C RW
	UINT32 reg_res_split_split_ctrl_03      :32;	//31:0	//reserved
	};
}REG_MERG_SR_MERGE_RES_SPLIT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C9F0 RW
	UINT32 reg_merge_pmode_out              :3;	//2:0	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd0                           :1;
	UINT32 reg_merge_pmode_in               :3;	//6:4	//Pixel mode for input (pixels for clock)	It is used for understanding reg_hsize in unit pixels	0 = 1p	1 = 2p	2 = 4p	3 := 8p	4 = 16p
	UINT32 resvd1                           :1;
	UINT32 reg_merge_split_mode             :2;	//9:8	//Split Configuation Select	0 := (S0 + 2GB) + (GB+S1+GB) + (GB+S2+GB) + (2GB+S3)	2 = (S0 + GB) + (GB+S1+GB) + (GB+S2+GB) + (GB+S3)	3 = (S0 + 0) + (GB+S1+0) + (GB+S2+0) + (GB+S3)
	UINT32 resvd2                           :2;
	UINT32 reg_merge_sync_mode              :1;	//12 //0:= ready-valid mode	1 = sync_mode
	UINT32 resvd3                           :3;
	UINT32 reg_merge_hsize                  :13;	//28:16	//
	UINT32 resvd4                           :3;
	};
}REG_MERG_SR_MERGE_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C9F4 RW
	UINT32 reg_merge_split_size             :13;	//12:0	//split size ( size in unit pixels)	ex) split-4 case	reg_split_size = reg_hsize / 4
	UINT32 resvd0                           :3;
	UINT32 reg_merge_guardband              :13;	//28:16	//guardband (size in unit pixels)
	UINT32 resvd1                           :3;
	};
}REG_MERG_SR_MERGE_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C9F8 RW
	UINT32 reg_merge_fifo_th                :9;	//8:0	//Merge begins on the line basis satifying following condition	fifo_status[reg_fifo_sel] >= reg_fifo_th
	UINT32 resvd0                           :7;
	UINT32 reg_merge_fifo_sel               :3;	//18:16	//0 := fifo 0	1 = fifo 1	2 = fifo 2	3 = fifo 3	4 = fifo 4	5 = fifo 5	6 = fifo 6	7 = fifo 7
	UINT32 resvd1                           :13;
	};
}REG_MERG_SR_MERGE_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901C9FC RW
	UINT32 reg_merge_ctrl_03                :32;	//31:0	//reserved
	};
}REG_MERG_SR_MERGE_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA00 RW
	UINT32 reg_residual_blur_en             :1;	//0:0	//0 : spatial filter off - use input residual data	1 : spatial filter on - use spatial filter result
	UINT32 resvd                            :31;
	};
}REG_MERG_SR_MERGE_SPATIAL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA04 RW
	UINT32 reg_residual_blur_filt_00        :4;	//3:0	//blur filter coefficient
	UINT32 reg_residual_blur_filt_01        :4;	//7:4	//blur filter coefficient
	UINT32 reg_residual_blur_filt_02        :4;	//11:8	//blur filter coefficient
	UINT32 reg_residual_blur_filt_10        :4;	//15:12	//blur filter coefficient
	UINT32 reg_residual_blur_filt_11        :4;	//19:16	//blur filter coefficient
	UINT32 reg_residual_blur_filt_12        :4;	//23:20	//blur filter coefficient
	UINT32 resvd                            :8;
	};
}REG_MERG_SR_MERGE_SPATIAL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA10 RW
	UINT32 resvd0                           :4;
	UINT32 reg_mmd_tap_size                 :4;	//7:4	//mmd tap size	0 : 3x3	1 : 5x5
	UINT32 resvd1                           :24;
	};
}REG_MERG_SR_MERGE_MMD_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA14 RW
	UINT32 reg_mmd_diff_lut_y0              :8;	//7:0	//mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x0              :8;	//15:8	//mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y1              :8;	//23:16	//mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x1              :8;	//31:24	//mmd diff lut x position
	};
}REG_MERG_SR_MERGE_MMD_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA18 RW
	UINT32 reg_mmd_diff_lut_y2              :8;	//7:0	//mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x2              :8;	//15:8	//mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y3              :8;	//23:16	//mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x3              :8;	//31:24	//mmd diff lut x position
	};
}REG_MERG_SR_MERGE_MMD_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA1C RW
	UINT32 reg_mmd_diff_lut_y4              :8;	//7:0	//mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x4              :8;	//15:8	//mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y5              :8;	//23:16	//mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x5              :8;	//31:24	//mmd diff lut x position
	};
}REG_MERG_SR_MERGE_MMD_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA20 RW
	UINT32 reg_mmd_diff_lut_y6              :8;	//7:0	//mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x6              :8;	//15:8	//mmd diff lut x position
	UINT32 reg_mmd_diff_lut_y7              :8;	//23:16	//mmd diff lut y position
	UINT32 reg_mmd_diff_lut_x7              :8;	//31:24	//mmd diff lut x position
	};
}REG_MERG_SR_MERGE_MMD_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA24 RW
	UINT32 reg_ti_gain_lut_y0               :8;	//7:0	//ti gain lut y position
	UINT32 reg_ti_gain_lut_x0               :8;	//15:8	//ti gain lut x position
	UINT32 reg_ti_gain_lut_y1               :8;	//23:16	//ti gain lut y position
	UINT32 reg_ti_gain_lut_x1               :8;	//31:24	//ti gain lut x position
	};
}REG_MERG_SR_MERGE_MMD_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA28 RW
	UINT32 reg_ti_gain_lut_y2               :8;	//7:0	//ti gain lut y position
	UINT32 reg_ti_gain_lut_x2               :8;	//15:8	//ti gain lut x position
	UINT32 reg_ti_gain_lut_y3               :8;	//23:16	//ti gain lut y position
	UINT32 reg_ti_gain_lut_x3               :8;	//31:24	//ti gain lut x position
	};
}REG_MERG_SR_MERGE_MMD_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA30 RW
	UINT32 reg_sobel_mode                   :4;	//3:0	//sobel mode selection 	0: 3x3 	1: 5x5	2: 7x7	3: (7x7 - 3x3) : (default)
	UINT32 resvd                            :28;
	};
}REG_MERG_SR_MERGE_SOBEL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA34 RW
	UINT32 reg_sobel_lut_y0                 :8;	//7:0	//sobel lut y position
	UINT32 reg_sobel_lut_x0                 :8;	//15:8	//sobel lut x position
	UINT32 reg_sobel_lut_y1                 :8;	//23:16	//sobel lut y position
	UINT32 reg_sobel_lut_x1                 :8;	//31:24	//sobel lut x position
	};
}REG_MERG_SR_MERGE_SOBEL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA38 RW
	UINT32 reg_sobel_lut_y2                 :8;	//7:0	//sobel lut y position
	UINT32 reg_sobel_lut_x2                 :8;	//15:8	//sobel lut x position
	UINT32 reg_sobel_lut_y3                 :8;	//23:16	//sobel lut y position
	UINT32 reg_sobel_lut_x3                 :8;	//31:24	//sobel lut x position
	};
}REG_MERG_SR_MERGE_SOBEL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA40 RW
	UINT32 reg_nr_gain_en                   :1;	//0:0	//NR Gain enable
	UINT32 resvd0                           :3;
	UINT32 reg_nr_gain_th                   :10;	//13:4	//NR gain threshold
	UINT32 resvd1                           :18;
	};
}REG_MERG_SR_MERGE_NR_GAIN_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA44 RW
	UINT32 reg_nr_gain_lut_y0               :8;	//7:0	//nr_gain lut y position
	UINT32 reg_nr_gain_lut_x0               :8;	//15:8	//nr_gain lut x position
	UINT32 reg_nr_gain_lut_y1               :8;	//23:16	//nr_gain lut y position
	UINT32 reg_nr_gain_lut_x1               :8;	//31:24	//nr_gain lut x position
	};
}REG_MERG_SR_MERGE_NR_GAIN_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA48 RW
	UINT32 reg_nr_gain_lut_y2               :8;	//7:0	//nr_gain lut y position
	UINT32 reg_nr_gain_lut_x2               :8;	//15:8	//nr_gain lut x position
	UINT32 reg_nr_gain_lut_y3               :8;	//23:16	//nr_gain lut y position
	UINT32 reg_nr_gain_lut_x3               :8;	//31:24	//nr_gain lut x position
	};
}REG_MERG_SR_MERGE_NR_GAIN_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA50 RW
	UINT32 reg_blend_lut_en                 :1;	//0:0	//blend lut en
	UINT32 resvd                            :19;
	UINT32 reg_blend_amp_weight             :12;	//31:20	//blend weight ('d16: x1, 'd32:x2)
	};
}REG_MERG_SR_MERGE_BLEND_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA54 RW
	UINT32 reg_blend_lut_y1                 :10;	//9:0	//blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x1                 :10;	//25:16	//blend lut x position
	UINT32 resvd1                           :6;
	};
}REG_MERG_SR_MERGE_BLEND_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA58 RW
	UINT32 reg_blend_lut_y0                 :10;	//9:0	//blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x0                 :10;	//25:16	//blend lut x position
	UINT32 resvd1                           :6;
	};
}REG_MERG_SR_MERGE_BLEND_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA5C RW
	UINT32 reg_blend_lut_y3                 :10;	//9:0	//blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x3                 :10;	//25:16	//blend lut x position
	UINT32 resvd1                           :6;
	};
}REG_MERG_SR_MERGE_BLEND_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CA60 RW
	UINT32 reg_blend_lut_y2                 :10;	//9:0	//blend lut y position
	UINT32 resvd0                           :6;
	UINT32 reg_blend_lut_x2                 :10;	//25:16	//blend lut x position
	UINT32 resvd1                           :6;
	};
}REG_MERG_SR_MERGE_BLEND_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB00 RO
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB04 RO
	UINT32 reg_mon_core_in_vert_cnt         :16;	//15:0	//Input vertical counter
	UINT32 reg_mon_core_in_hori_cnt         :16;	//31:16	//Input horizontal counter
	};
}REG_MERG_SR_MERGE_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB08 RO
	UINT32 reg_mon_core_out_vert_cnt        :16;	//15:0	//Output vertical counter
	UINT32 reg_mon_core_out_hori_cnt        :16;	//31:16	//Output horizontal counter
	};
}REG_MERG_SR_MERGE_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB0C RO
	UINT32 reg_mon_core_fin_out_vert_cnt    :16;	//15:0	//Output previous frame vertical counter
	UINT32 reg_mon_core_fin_in_vert_cnt     :16;	//31:16	//Input previous frame vertical counter
	};
}REG_MERG_SR_MERGE_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB10 RO
	UINT32 reg_mon_core_shp_i_sucfail       :32;	//31:0	//Input success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB14 RO
	UINT32 reg_mon_core_shp_o_sucfail       :32;	//31:0	//Output success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB18 RO
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_CORE0_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB1C RO
	UINT32 reg_mon_core0_in_vert_cnt        :16;	//15:0	//Input vertical counter
	UINT32 reg_mon_core0_in_hori_cnt        :16;	//31:16	//Input horizontal counter
	};
}REG_MERG_SR_MERGE_CORE0_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB20 RO
	UINT32 reg_mon_core0_out_vert_cnt       :16;	//15:0	//Output vertical counter
	UINT32 reg_mon_core0_out_hori_cnt       :16;	//31:16	//Output horizontal counter
	};
}REG_MERG_SR_MERGE_CORE0_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB24 RO
	UINT32 reg_mon_core0_fin_out_vert_cnt   :16;	//15:0	//Output previous frame vertical counter
	UINT32 reg_mon_core0_fin_in_vert_cnt    :16;	//31:16	//Input previous frame vertical counter
	};
}REG_MERG_SR_MERGE_CORE0_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB28 RO
	UINT32 reg_mon_core0_shp_i_sucfail      :32;	//31:0	//Input success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE0_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB2C RO
	UINT32 reg_mon_core0_shp_o_sucfail      :32;	//31:0	//Output success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE0_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB30 RO
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_CORE1_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB34 RO
	UINT32 reg_mon_core1_in_vert_cnt        :16;	//15:0	//Input vertical counter
	UINT32 reg_mon_core1_in_hori_cnt        :16;	//31:16	//Input horizontal counter
	};
}REG_MERG_SR_MERGE_CORE1_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB38 RO
	UINT32 reg_mon_core1_out_vert_cnt       :16;	//15:0	//Output vertical counter
	UINT32 reg_mon_core1_out_hori_cnt       :16;	//31:16	//Output horizontal counter
	};
}REG_MERG_SR_MERGE_CORE1_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB3C RO
	UINT32 reg_mon_core1_fin_out_vert_cnt   :16;	//15:0	//Output previous frame vertical counter
	UINT32 reg_mon_core1_fin_in_vert_cnt    :16;	//31:16	//Input previous frame vertical counter
	};
}REG_MERG_SR_MERGE_CORE1_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB40 RO
	UINT32 reg_mon_core1_shp_i_sucfail      :32;	//31:0	//Input success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE1_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB44 RO
	UINT32 reg_mon_core1_shp_o_sucfail      :32;	//31:0	//Output success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE1_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB48 RO
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_CORE2_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB4C RO
	UINT32 reg_mon_core2_in_vert_cnt        :16;	//15:0	//Input vertical counter
	UINT32 reg_mon_core2_in_hori_cnt        :16;	//31:16	//Input horizontal counter
	};
}REG_MERG_SR_MERGE_CORE2_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB50 RO
	UINT32 reg_mon_core2_out_vert_cnt       :16;	//15:0	//Output vertical counter
	UINT32 reg_mon_core2_out_hori_cnt       :16;	//31:16	//Output horizontal counter
	};
}REG_MERG_SR_MERGE_CORE2_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB54 RO
	UINT32 reg_mon_core2_fin_out_vert_cnt   :16;	//15:0	//Output previous frame vertical counter
	UINT32 reg_mon_core2_fin_in_vert_cnt    :16;	//31:16	//Input previous frame vertical counter
	};
}REG_MERG_SR_MERGE_CORE2_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB58 RO
	UINT32 reg_mon_core2_shp_i_sucfail      :32;	//31:0	//Input success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE2_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB5C RO
	UINT32 reg_mon_core2_shp_o_sucfail      :32;	//31:0	//Output success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE2_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB60 RO
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_CORE3_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB64 RO
	UINT32 reg_mon_core3_in_vert_cnt        :16;	//15:0	//Input vertical counter
	UINT32 reg_mon_core3_in_hori_cnt        :16;	//31:16	//Input horizontal counter
	};
}REG_MERG_SR_MERGE_CORE3_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB68 RO
	UINT32 reg_mon_core3_out_vert_cnt       :16;	//15:0	//Output vertical counter
	UINT32 reg_mon_core3_out_hori_cnt       :16;	//31:16	//Output horizontal counter
	};
}REG_MERG_SR_MERGE_CORE3_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB6C RO
	UINT32 reg_mon_core3_fin_out_vert_cnt   :16;	//15:0	//Output previous frame vertical counter
	UINT32 reg_mon_core3_fin_in_vert_cnt    :16;	//31:16	//Input previous frame vertical counter
	};
}REG_MERG_SR_MERGE_CORE3_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB70 RO
	UINT32 reg_mon_core3_shp_i_sucfail      :32;	//31:0	//Input success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE3_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CB74 RO
	UINT32 reg_mon_core3_shp_o_sucfail      :32;	//31:0	//Output success/fail monitoring register
	};
}REG_MERG_SR_MERGE_CORE3_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CC00 RW
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CC04 RW
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CC08 RW
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901CC0C RW
	UINT32 tdata0                           :32;
	};
}REG_MERG_SR_MERGE_FSW_CTRL_03_T;

typedef struct {
	REG_SHC_SHP_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0xC901D400
	REG_SHC_SHP_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0xC901D404
	REG_SHC_SHP_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0xC901D408
	UINT32                                                    reserved0;	//0xC901D40C
	UINT32                                                    reserved1;	//0xC901D410
	UINT32                                                    reserved2;	//0xC901D414
	UINT32                                                    reserved3;	//0xC901D418
	UINT32                                                    reserved4;	//0xC901D41C
	UINT32                                                    reserved5;	//0xC901D420
	UINT32                                                    reserved6;	//0xC901D424
	UINT32                                                    reserved7;	//0xC901D428
	UINT32                                                    reserved8;	//0xC901D42C
	UINT32                                                    reserved9;	//0xC901D430
	UINT32                                                   reserved10;	//0xC901D434
	UINT32                                                   reserved11;	//0xC901D438
	UINT32                                                   reserved12;	//0xC901D43C
	UINT32                                                   reserved13;	//0xC901D440
	UINT32                                                   reserved14;	//0xC901D444
	UINT32                                                   reserved15;	//0xC901D448
	UINT32                                                   reserved16;	//0xC901D44C
	UINT32                                                   reserved17;	//0xC901D450
	UINT32                                                   reserved18;	//0xC901D454
	UINT32                                                   reserved19;	//0xC901D458
	UINT32                                                   reserved20;	//0xC901D45C
	UINT32                                                   reserved21;	//0xC901D460
	UINT32                                                   reserved22;	//0xC901D464
	UINT32                                                   reserved23;	//0xC901D468
	UINT32                                                   reserved24;	//0xC901D46C
	UINT32                                                   reserved25;	//0xC901D470
	UINT32                                                   reserved26;	//0xC901D474
	UINT32                                                   reserved27;	//0xC901D478
	UINT32                                                   reserved28;	//0xC901D47C
	UINT32                                                   reserved29;	//0xC901D480
	UINT32                                                   reserved30;	//0xC901D484
	UINT32                                                   reserved31;	//0xC901D488
	UINT32                                                   reserved32;	//0xC901D48C
	UINT32                                                   reserved33;	//0xC901D490
	UINT32                                                   reserved34;	//0xC901D494
	UINT32                                                   reserved35;	//0xC901D498
	UINT32                                                   reserved36;	//0xC901D49C
	UINT32                                                   reserved37;	//0xC901D4A0
	UINT32                                                   reserved38;	//0xC901D4A4
	UINT32                                                   reserved39;	//0xC901D4A8
	UINT32                                                   reserved40;	//0xC901D4AC
	UINT32                                                   reserved41;	//0xC901D4B0
	UINT32                                                   reserved42;	//0xC901D4B4
	UINT32                                                   reserved43;	//0xC901D4B8
	UINT32                                                   reserved44;	//0xC901D4BC
	UINT32                                                   reserved45;	//0xC901D4C0
	UINT32                                                   reserved46;	//0xC901D4C4
	UINT32                                                   reserved47;	//0xC901D4C8
	UINT32                                                   reserved48;	//0xC901D4CC
	UINT32                                                   reserved49;	//0xC901D4D0
	UINT32                                                   reserved50;	//0xC901D4D4
	UINT32                                                   reserved51;	//0xC901D4D8
	UINT32                                                   reserved52;	//0xC901D4DC
	UINT32                                                   reserved53;	//0xC901D4E0
	UINT32                                                   reserved54;	//0xC901D4E4
	UINT32                                                   reserved55;	//0xC901D4E8
	UINT32                                                   reserved56;	//0xC901D4EC
	UINT32                                                   reserved57;	//0xC901D4F0
	UINT32                                                   reserved58;	//0xC901D4F4
	UINT32                                                   reserved59;	//0xC901D4F8
	UINT32                                                   reserved60;	//0xC901D4FC
	UINT32                                                   reserved61;	//0xC901D500
	UINT32                                                   reserved62;	//0xC901D504
	UINT32                                                   reserved63;	//0xC901D508
	UINT32                                                   reserved64;	//0xC901D50C
	UINT32                                                   reserved65;	//0xC901D510
	UINT32                                                   reserved66;	//0xC901D514
	UINT32                                                   reserved67;	//0xC901D518
	UINT32                                                   reserved68;	//0xC901D51C
	UINT32                                                   reserved69;	//0xC901D520
	UINT32                                                   reserved70;	//0xC901D524
	UINT32                                                   reserved71;	//0xC901D528
	UINT32                                                   reserved72;	//0xC901D52C
	UINT32                                                   reserved73;	//0xC901D530
	UINT32                                                   reserved74;	//0xC901D534
	UINT32                                                   reserved75;	//0xC901D538
	UINT32                                                   reserved76;	//0xC901D53C
	UINT32                                                   reserved77;	//0xC901D540
	UINT32                                                   reserved78;	//0xC901D544
	UINT32                                                   reserved79;	//0xC901D548
	UINT32                                                   reserved80;	//0xC901D54C
	UINT32                                                   reserved81;	//0xC901D550
	UINT32                                                   reserved82;	//0xC901D554
	UINT32                                                   reserved83;	//0xC901D558
	UINT32                                                   reserved84;	//0xC901D55C
	UINT32                                                   reserved85;	//0xC901D560
	UINT32                                                   reserved86;	//0xC901D564
	UINT32                                                   reserved87;	//0xC901D568
	UINT32                                                   reserved88;	//0xC901D56C
	UINT32                                                   reserved89;	//0xC901D570
	UINT32                                                   reserved90;	//0xC901D574
	UINT32                                                   reserved91;	//0xC901D578
	UINT32                                                   reserved92;	//0xC901D57C
	UINT32                                                   reserved93;	//0xC901D580
	UINT32                                                   reserved94;	//0xC901D584
	UINT32                                                   reserved95;	//0xC901D588
	UINT32                                                   reserved96;	//0xC901D58C
	UINT32                                                   reserved97;	//0xC901D590
	UINT32                                                   reserved98;	//0xC901D594
	UINT32                                                   reserved99;	//0xC901D598
	UINT32                                                  reserved100;	//0xC901D59C
	UINT32                                                  reserved101;	//0xC901D5A0
	UINT32                                                  reserved102;	//0xC901D5A4
	UINT32                                                  reserved103;	//0xC901D5A8
	UINT32                                                  reserved104;	//0xC901D5AC
	UINT32                                                  reserved105;	//0xC901D5B0
	UINT32                                                  reserved106;	//0xC901D5B4
	UINT32                                                  reserved107;	//0xC901D5B8
	UINT32                                                  reserved108;	//0xC901D5BC
	UINT32                                                  reserved109;	//0xC901D5C0
	UINT32                                                  reserved110;	//0xC901D5C4
	UINT32                                                  reserved111;	//0xC901D5C8
	UINT32                                                  reserved112;	//0xC901D5CC
	UINT32                                                  reserved113;	//0xC901D5D0
	UINT32                                                  reserved114;	//0xC901D5D4
	UINT32                                                  reserved115;	//0xC901D5D8
	UINT32                                                  reserved116;	//0xC901D5DC
	UINT32                                                  reserved117;	//0xC901D5E0
	UINT32                                                  reserved118;	//0xC901D5E4
	UINT32                                                  reserved119;	//0xC901D5E8
	UINT32                                                  reserved120;	//0xC901D5EC
	UINT32                                                  reserved121;	//0xC901D5F0
	UINT32                                                  reserved122;	//0xC901D5F4
	UINT32                                                  reserved123;	//0xC901D5F8
	UINT32                                                  reserved124;	//0xC901D5FC
	UINT32                                                  reserved125;	//0xC901D600
	UINT32                                                  reserved126;	//0xC901D604
	UINT32                                                  reserved127;	//0xC901D608
	UINT32                                                  reserved128;	//0xC901D60C
	UINT32                                                  reserved129;	//0xC901D610
	UINT32                                                  reserved130;	//0xC901D614
	UINT32                                                  reserved131;	//0xC901D618
	UINT32                                                  reserved132;	//0xC901D61C
	UINT32                                                  reserved133;	//0xC901D620
	UINT32                                                  reserved134;	//0xC901D624
	UINT32                                                  reserved135;	//0xC901D628
	UINT32                                                  reserved136;	//0xC901D62C
	UINT32                                                  reserved137;	//0xC901D630
	UINT32                                                  reserved138;	//0xC901D634
	UINT32                                                  reserved139;	//0xC901D638
	UINT32                                                  reserved140;	//0xC901D63C
	UINT32                                                  reserved141;	//0xC901D640
	UINT32                                                  reserved142;	//0xC901D644
	UINT32                                                  reserved143;	//0xC901D648
	UINT32                                                  reserved144;	//0xC901D64C
	UINT32                                                  reserved145;	//0xC901D650
	UINT32                                                  reserved146;	//0xC901D654
	UINT32                                                  reserved147;	//0xC901D658
	UINT32                                                  reserved148;	//0xC901D65C
	UINT32                                                  reserved149;	//0xC901D660
	UINT32                                                  reserved150;	//0xC901D664
	UINT32                                                  reserved151;	//0xC901D668
	UINT32                                                  reserved152;	//0xC901D66C
	UINT32                                                  reserved153;	//0xC901D670
	UINT32                                                  reserved154;	//0xC901D674
	UINT32                                                  reserved155;	//0xC901D678
	UINT32                                                  reserved156;	//0xC901D67C
	UINT32                                                  reserved157;	//0xC901D680
	UINT32                                                  reserved158;	//0xC901D684
	UINT32                                                  reserved159;	//0xC901D688
	UINT32                                                  reserved160;	//0xC901D68C
	UINT32                                                  reserved161;	//0xC901D690
	UINT32                                                  reserved162;	//0xC901D694
	UINT32                                                  reserved163;	//0xC901D698
	UINT32                                                  reserved164;	//0xC901D69C
	UINT32                                                  reserved165;	//0xC901D6A0
	UINT32                                                  reserved166;	//0xC901D6A4
	UINT32                                                  reserved167;	//0xC901D6A8
	UINT32                                                  reserved168;	//0xC901D6AC
	UINT32                                                  reserved169;	//0xC901D6B0
	UINT32                                                  reserved170;	//0xC901D6B4
	UINT32                                                  reserved171;	//0xC901D6B8
	UINT32                                                  reserved172;	//0xC901D6BC
	UINT32                                                  reserved173;	//0xC901D6C0
	UINT32                                                  reserved174;	//0xC901D6C4
	UINT32                                                  reserved175;	//0xC901D6C8
	UINT32                                                  reserved176;	//0xC901D6CC
	UINT32                                                  reserved177;	//0xC901D6D0
	UINT32                                                  reserved178;	//0xC901D6D4
	UINT32                                                  reserved179;	//0xC901D6D8
	UINT32                                                  reserved180;	//0xC901D6DC
	UINT32                                                  reserved181;	//0xC901D6E0
	UINT32                                                  reserved182;	//0xC901D6E4
	UINT32                                                  reserved183;	//0xC901D6E8
	UINT32                                                  reserved184;	//0xC901D6EC
	UINT32                                                  reserved185;	//0xC901D6F0
	UINT32                                                  reserved186;	//0xC901D6F4
	UINT32                                                  reserved187;	//0xC901D6F8
	UINT32                                                  reserved188;	//0xC901D6FC
	UINT32                                                  reserved189;	//0xC901D700
	UINT32                                                  reserved190;	//0xC901D704
	UINT32                                                  reserved191;	//0xC901D708
	UINT32                                                  reserved192;	//0xC901D70C
	UINT32                                                  reserved193;	//0xC901D710
	UINT32                                                  reserved194;	//0xC901D714
	UINT32                                                  reserved195;	//0xC901D718
	UINT32                                                  reserved196;	//0xC901D71C
	UINT32                                                  reserved197;	//0xC901D720
	UINT32                                                  reserved198;	//0xC901D724
	UINT32                                                  reserved199;	//0xC901D728
	UINT32                                                  reserved200;	//0xC901D72C
	UINT32                                                  reserved201;	//0xC901D730
	UINT32                                                  reserved202;	//0xC901D734
	UINT32                                                  reserved203;	//0xC901D738
	UINT32                                                  reserved204;	//0xC901D73C
	UINT32                                                  reserved205;	//0xC901D740
	UINT32                                                  reserved206;	//0xC901D744
	UINT32                                                  reserved207;	//0xC901D748
	UINT32                                                  reserved208;	//0xC901D74C
	UINT32                                                  reserved209;	//0xC901D750
	UINT32                                                  reserved210;	//0xC901D754
	UINT32                                                  reserved211;	//0xC901D758
	UINT32                                                  reserved212;	//0xC901D75C
	UINT32                                                  reserved213;	//0xC901D760
	UINT32                                                  reserved214;	//0xC901D764
	UINT32                                                  reserved215;	//0xC901D768
	UINT32                                                  reserved216;	//0xC901D76C
	UINT32                                                  reserved217;	//0xC901D770
	UINT32                                                  reserved218;	//0xC901D774
	UINT32                                                  reserved219;	//0xC901D778
	UINT32                                                  reserved220;	//0xC901D77C
	UINT32                                                  reserved221;	//0xC901D780
	UINT32                                                  reserved222;	//0xC901D784
	UINT32                                                  reserved223;	//0xC901D788
	UINT32                                                  reserved224;	//0xC901D78C
	UINT32                                                  reserved225;	//0xC901D790
	UINT32                                                  reserved226;	//0xC901D794
	UINT32                                                  reserved227;	//0xC901D798
	UINT32                                                  reserved228;	//0xC901D79C
	UINT32                                                  reserved229;	//0xC901D7A0
	UINT32                                                  reserved230;	//0xC901D7A4
	UINT32                                                  reserved231;	//0xC901D7A8
	UINT32                                                  reserved232;	//0xC901D7AC
	UINT32                                                  reserved233;	//0xC901D7B0
	UINT32                                                  reserved234;	//0xC901D7B4
	UINT32                                                  reserved235;	//0xC901D7B8
	UINT32                                                  reserved236;	//0xC901D7BC
	UINT32                                                  reserved237;	//0xC901D7C0
	UINT32                                                  reserved238;	//0xC901D7C4
	UINT32                                                  reserved239;	//0xC901D7C8
	UINT32                                                  reserved240;	//0xC901D7CC
	UINT32                                                  reserved241;	//0xC901D7D0
	UINT32                                                  reserved242;	//0xC901D7D4
	UINT32                                                  reserved243;	//0xC901D7D8
	UINT32                                                  reserved244;	//0xC901D7DC
	UINT32                                                  reserved245;	//0xC901D7E0
	UINT32                                                  reserved246;	//0xC901D7E4
	UINT32                                                  reserved247;	//0xC901D7E8
	UINT32                                                  reserved248;	//0xC901D7EC
	UINT32                                                  reserved249;	//0xC901D7F0
	UINT32                                                  reserved250;	//0xC901D7F4
	UINT32                                                  reserved251;	//0xC901D7F8
	UINT32                                                  reserved252;	//0xC901D7FC
	REG_SHC_SHP_CDJ_CTRL_00_T                           shp_cdj_ctrl_00;	//0xC901D800
	REG_SHC_SHP_CDJ_CTRL_01_T                           shp_cdj_ctrl_01;	//0xC901D804
	REG_SHC_SHP_CDJ_CTRL_02_T                           shp_cdj_ctrl_02;	//0xC901D808
	REG_SHC_SHP_CDJ_CTRL_03_T                           shp_cdj_ctrl_03;	//0xC901D80C
	REG_SHC_SHP_CDJ_CTRL_04_T                           shp_cdj_ctrl_04;	//0xC901D810
	REG_SHC_SHP_CDJ_CTRL_05_T                           shp_cdj_ctrl_05;	//0xC901D814
	REG_SHC_SHP_CDJ_CTRL_06_T                           shp_cdj_ctrl_06;	//0xC901D818
	REG_SHC_SHP_CDJ_CTRL_07_T                           shp_cdj_ctrl_07;	//0xC901D81C
	REG_SHC_SHP_CDJ_CTRL_08_T                           shp_cdj_ctrl_08;	//0xC901D820
	REG_SHC_SHP_CDJ_CTRL_09_T                           shp_cdj_ctrl_09;	//0xC901D824
	REG_SHC_SHP_CDJ_CTRL_0A_T                           shp_cdj_ctrl_0a;	//0xC901D828
	REG_SHC_SHP_CDJ_CTRL_0B_T                           shp_cdj_ctrl_0b;	//0xC901D82C
	REG_SHC_SHP_CDJ_CTRL_0C_T                           shp_cdj_ctrl_0c;	//0xC901D830
	REG_SHC_SHP_CDJ_CTRL_0D_T                           shp_cdj_ctrl_0d;	//0xC901D834
	REG_SHC_SHP_CDJ_CTRL_0E_T                           shp_cdj_ctrl_0e;	//0xC901D838
	REG_SHC_SHP_CDJ_CTRL_0F_T                           shp_cdj_ctrl_0f;	//0xC901D83C
	REG_SHC_SHP_CDJ_CTRL_10_T                           shp_cdj_ctrl_10;	//0xC901D840
	REG_SHC_SHP_CDJ_CTRL_11_T                           shp_cdj_ctrl_11;	//0xC901D844
	REG_SHC_SHP_CDJ_CTRL_12_T                           shp_cdj_ctrl_12;	//0xC901D848
	REG_SHC_SHP_CDJ_CTRL_13_T                           shp_cdj_ctrl_13;	//0xC901D84C
	REG_SHC_SHP_CDJ_CTRL_14_T                           shp_cdj_ctrl_14;	//0xC901D850
	REG_SHC_SHP_CDJ_CTRL_15_T                           shp_cdj_ctrl_15;	//0xC901D854
	REG_SHC_SHP_CDJ_CTRL_16_T                           shp_cdj_ctrl_16;	//0xC901D858
	REG_SHC_SHP_CDJ_CTRL_17_T                           shp_cdj_ctrl_17;	//0xC901D85C
	REG_SHC_SHP_CDJ_CTRL_18_T                           shp_cdj_ctrl_18;	//0xC901D860
	REG_SHC_SHP_CDJ_CTRL_19_T                           shp_cdj_ctrl_19;	//0xC901D864
	REG_SHC_SHP_CDJ_CTRL_1A_T                           shp_cdj_ctrl_1a;	//0xC901D868
	REG_SHC_SHP_CDJ_CTRL_1B_T                           shp_cdj_ctrl_1b;	//0xC901D86C
	REG_SHC_SHP_CDJ_CTRL_1C_T                           shp_cdj_ctrl_1c;	//0xC901D870
	REG_SHC_SHP_CDJ_CTRL_1D_T                           shp_cdj_ctrl_1d;	//0xC901D874
	REG_SHC_SHP_CDJ_CTRL_1E_T                           shp_cdj_ctrl_1e;	//0xC901D878
	REG_SHC_SHP_CDJ_CTRL_1F_T                           shp_cdj_ctrl_1f;	//0xC901D87C
	REG_SHC_SHP_CDJ_CTRL_20_T                           shp_cdj_ctrl_20;	//0xC901D880
	UINT32                                                  reserved253;	//0xC901D884
	UINT32                                                  reserved254;	//0xC901D888
	UINT32                                                  reserved255;	//0xC901D88C
	REG_SHC_SHP_CDIR_BLUR_CTRL_00_T               shp_cdir_blur_ctrl_00;	//0xC901D890
	REG_SHC_SHP_CDIR_BLUR_CTRL_01_T               shp_cdir_blur_ctrl_01;	//0xC901D894
	UINT32                                                  reserved256;	//0xC901D898
	UINT32                                                  reserved257;	//0xC901D89C
	REG_SHC_SHP_CDJ_WIN_CTRL_00_T                   shp_cdj_win_ctrl_00;	//0xC901D8A0
	REG_SHC_SHP_CDJ_WIN_CTRL_01_T                   shp_cdj_win_ctrl_01;	//0xC901D8A4
	REG_SHC_SHP_CDJ_WIN_CTRL_02_T                   shp_cdj_win_ctrl_02;	//0xC901D8A8
	REG_SHC_SHP_CDJ_WIN_CTRL_03_T                   shp_cdj_win_ctrl_03;	//0xC901D8AC
	REG_SHC_SHP_CDJ_WIN_CTRL_04_T                   shp_cdj_win_ctrl_04;	//0xC901D8B0
	UINT32                                                  reserved258;	//0xC901D8B4
	UINT32                                                  reserved259;	//0xC901D8B8
	UINT32                                                  reserved260;	//0xC901D8BC
	UINT32                                                  reserved261;	//0xC901D8C0
	UINT32                                                  reserved262;	//0xC901D8C4
	UINT32                                                  reserved263;	//0xC901D8C8
	UINT32                                                  reserved264;	//0xC901D8CC
	UINT32                                                  reserved265;	//0xC901D8D0
	UINT32                                                  reserved266;	//0xC901D8D4
	UINT32                                                  reserved267;	//0xC901D8D8
	UINT32                                                  reserved268;	//0xC901D8DC
	UINT32                                                  reserved269;	//0xC901D8E0
	UINT32                                                  reserved270;	//0xC901D8E4
	UINT32                                                  reserved271;	//0xC901D8E8
	UINT32                                                  reserved272;	//0xC901D8EC
	UINT32                                                  reserved273;	//0xC901D8F0
	UINT32                                                  reserved274;	//0xC901D8F4
	UINT32                                                  reserved275;	//0xC901D8F8
	UINT32                                                  reserved276;	//0xC901D8FC
	UINT32                                                  reserved277;	//0xC901D900
	UINT32                                                  reserved278;	//0xC901D904
	UINT32                                                  reserved279;	//0xC901D908
	UINT32                                                  reserved280;	//0xC901D90C
	UINT32                                                  reserved281;	//0xC901D910
	UINT32                                                  reserved282;	//0xC901D914
	UINT32                                                  reserved283;	//0xC901D918
	UINT32                                                  reserved284;	//0xC901D91C
	UINT32                                                  reserved285;	//0xC901D920
	UINT32                                                  reserved286;	//0xC901D924
	UINT32                                                  reserved287;	//0xC901D928
	UINT32                                                  reserved288;	//0xC901D92C
	UINT32                                                  reserved289;	//0xC901D930
	UINT32                                                  reserved290;	//0xC901D934
	UINT32                                                  reserved291;	//0xC901D938
	UINT32                                                  reserved292;	//0xC901D93C
	UINT32                                                  reserved293;	//0xC901D940
	UINT32                                                  reserved294;	//0xC901D944
	UINT32                                                  reserved295;	//0xC901D948
	UINT32                                                  reserved296;	//0xC901D94C
	UINT32                                                  reserved297;	//0xC901D950
	UINT32                                                  reserved298;	//0xC901D954
	UINT32                                                  reserved299;	//0xC901D958
	UINT32                                                  reserved300;	//0xC901D95C
	UINT32                                                  reserved301;	//0xC901D960
	UINT32                                                  reserved302;	//0xC901D964
	UINT32                                                  reserved303;	//0xC901D968
	UINT32                                                  reserved304;	//0xC901D96C
	UINT32                                                  reserved305;	//0xC901D970
	UINT32                                                  reserved306;	//0xC901D974
	UINT32                                                  reserved307;	//0xC901D978
	UINT32                                                  reserved308;	//0xC901D97C
	UINT32                                                  reserved309;	//0xC901D980
	UINT32                                                  reserved310;	//0xC901D984
	UINT32                                                  reserved311;	//0xC901D988
	UINT32                                                  reserved312;	//0xC901D98C
	UINT32                                                  reserved313;	//0xC901D990
	UINT32                                                  reserved314;	//0xC901D994
	UINT32                                                  reserved315;	//0xC901D998
	UINT32                                                  reserved316;	//0xC901D99C
	UINT32                                                  reserved317;	//0xC901D9A0
	UINT32                                                  reserved318;	//0xC901D9A4
	UINT32                                                  reserved319;	//0xC901D9A8
	UINT32                                                  reserved320;	//0xC901D9AC
	UINT32                                                  reserved321;	//0xC901D9B0
	UINT32                                                  reserved322;	//0xC901D9B4
	UINT32                                                  reserved323;	//0xC901D9B8
	UINT32                                                  reserved324;	//0xC901D9BC
	UINT32                                                  reserved325;	//0xC901D9C0
	UINT32                                                  reserved326;	//0xC901D9C4
	UINT32                                                  reserved327;	//0xC901D9C8
	UINT32                                                  reserved328;	//0xC901D9CC
	UINT32                                                  reserved329;	//0xC901D9D0
	UINT32                                                  reserved330;	//0xC901D9D4
	UINT32                                                  reserved331;	//0xC901D9D8
	UINT32                                                  reserved332;	//0xC901D9DC
	UINT32                                                  reserved333;	//0xC901D9E0
	UINT32                                                  reserved334;	//0xC901D9E4
	UINT32                                                  reserved335;	//0xC901D9E8
	UINT32                                                  reserved336;	//0xC901D9EC
	UINT32                                                  reserved337;	//0xC901D9F0
	UINT32                                                  reserved338;	//0xC901D9F4
	UINT32                                                  reserved339;	//0xC901D9F8
	UINT32                                                  reserved340;	//0xC901D9FC
	REG_SHC_SHP_CORE_STAT_00_T                         shp_core_stat_00;	//0xC901DA00
	REG_SHC_SHP_CORE_STAT_01_T                         shp_core_stat_01;	//0xC901DA04
	REG_SHC_SHP_CORE_STAT_02_T                         shp_core_stat_02;	//0xC901DA08
	REG_SHC_SHP_CORE_STAT_03_T                         shp_core_stat_03;	//0xC901DA0C
	REG_SHC_SHP_CORE_STAT_04_T                         shp_core_stat_04;	//0xC901DA10
	REG_SHC_SHP_CORE_STAT_05_T                         shp_core_stat_05;	//0xC901DA14
	UINT32                                                  reserved341;	//0xC901DA18
	UINT32                                                  reserved342;	//0xC901DA1C
	UINT32                                                  reserved343;	//0xC901DA20
	UINT32                                                  reserved344;	//0xC901DA24
	UINT32                                                  reserved345;	//0xC901DA28
	UINT32                                                  reserved346;	//0xC901DA2C
	UINT32                                                  reserved347;	//0xC901DA30
	UINT32                                                  reserved348;	//0xC901DA34
	UINT32                                                  reserved349;	//0xC901DA38
	UINT32                                                  reserved350;	//0xC901DA3C
	UINT32                                                  reserved351;	//0xC901DA40
	UINT32                                                  reserved352;	//0xC901DA44
	UINT32                                                  reserved353;	//0xC901DA48
	UINT32                                                  reserved354;	//0xC901DA4C
	UINT32                                                  reserved355;	//0xC901DA50
	UINT32                                                  reserved356;	//0xC901DA54
	UINT32                                                  reserved357;	//0xC901DA58
	UINT32                                                  reserved358;	//0xC901DA5C
	UINT32                                                  reserved359;	//0xC901DA60
	UINT32                                                  reserved360;	//0xC901DA64
	UINT32                                                  reserved361;	//0xC901DA68
	UINT32                                                  reserved362;	//0xC901DA6C
	UINT32                                                  reserved363;	//0xC901DA70
	UINT32                                                  reserved364;	//0xC901DA74
	UINT32                                                  reserved365;	//0xC901DA78
	UINT32                                                  reserved366;	//0xC901DA7C
	UINT32                                                  reserved367;	//0xC901DA80
	UINT32                                                  reserved368;	//0xC901DA84
	UINT32                                                  reserved369;	//0xC901DA88
	UINT32                                                  reserved370;	//0xC901DA8C
	UINT32                                                  reserved371;	//0xC901DA90
	UINT32                                                  reserved372;	//0xC901DA94
	UINT32                                                  reserved373;	//0xC901DA98
	UINT32                                                  reserved374;	//0xC901DA9C
	UINT32                                                  reserved375;	//0xC901DAA0
	UINT32                                                  reserved376;	//0xC901DAA4
	UINT32                                                  reserved377;	//0xC901DAA8
	UINT32                                                  reserved378;	//0xC901DAAC
	UINT32                                                  reserved379;	//0xC901DAB0
	UINT32                                                  reserved380;	//0xC901DAB4
	UINT32                                                  reserved381;	//0xC901DAB8
	UINT32                                                  reserved382;	//0xC901DABC
	UINT32                                                  reserved383;	//0xC901DAC0
	UINT32                                                  reserved384;	//0xC901DAC4
	UINT32                                                  reserved385;	//0xC901DAC8
	UINT32                                                  reserved386;	//0xC901DACC
	UINT32                                                  reserved387;	//0xC901DAD0
	UINT32                                                  reserved388;	//0xC901DAD4
	UINT32                                                  reserved389;	//0xC901DAD8
	UINT32                                                  reserved390;	//0xC901DADC
	UINT32                                                  reserved391;	//0xC901DAE0
	UINT32                                                  reserved392;	//0xC901DAE4
	UINT32                                                  reserved393;	//0xC901DAE8
	UINT32                                                  reserved394;	//0xC901DAEC
	REG_SHC_SHP_FSW_CTRL_00_T                           shp_fsw_ctrl_00;	//0xC901DAF0
	REG_SHC_SHP_FSW_CTRL_01_T                           shp_fsw_ctrl_01;	//0xC901DAF4
	REG_SHC_SHP_FSW_CTRL_02_T                           shp_fsw_ctrl_02;	//0xC901DAF8
	REG_SHC_SHP_FSW_CTRL_03_T                           shp_fsw_ctrl_03;	//0xC901DAFC
}PE_SR_CHR_SHP_REG_E60_T;

typedef struct {
	REG_SHY_4K_SHP_CORE_CTRL_00_T                      shp_core_ctrl_00;	//0xC901B800
	REG_SHY_4K_SHP_CORE_CTRL_01_T                      shp_core_ctrl_01;	//0xC901B804
	REG_SHY_4K_SHP_CORE_CTRL_02_T                      shp_core_ctrl_02;	//0xC901B808
	REG_SHY_4K_SHP_CORE_CTRL_03_T                      shp_core_ctrl_03;	//0xC901B80C
	UINT32                                                    reserved0;	//0xC901B810
	UINT32                                                    reserved1;	//0xC901B814
	UINT32                                                    reserved2;	//0xC901B818
	UINT32                                                    reserved3;	//0xC901B81C
	UINT32                                                    reserved4;	//0xC901B820
	UINT32                                                    reserved5;	//0xC901B824
	UINT32                                                    reserved6;	//0xC901B828
	UINT32                                                    reserved7;	//0xC901B82C
	UINT32                                                    reserved8;	//0xC901B830
	UINT32                                                    reserved9;	//0xC901B834
	UINT32                                                   reserved10;	//0xC901B838
	UINT32                                                   reserved11;	//0xC901B83C
	REG_SHY_4K_SHP_PAT_GEN_CTRL_00_T                shp_pat_gen_ctrl_00;	//0xC901B840
	UINT32                                                   reserved12;	//0xC901B844
	UINT32                                                   reserved13;	//0xC901B848
	UINT32                                                   reserved14;	//0xC901B84C
	UINT32                                                   reserved15;	//0xC901B850
	UINT32                                                   reserved16;	//0xC901B854
	UINT32                                                   reserved17;	//0xC901B858
	UINT32                                                   reserved18;	//0xC901B85C
	UINT32                                                   reserved19;	//0xC901B860
	UINT32                                                   reserved20;	//0xC901B864
	UINT32                                                   reserved21;	//0xC901B868
	UINT32                                                   reserved22;	//0xC901B86C
	UINT32                                                   reserved23;	//0xC901B870
	UINT32                                                   reserved24;	//0xC901B874
	UINT32                                                   reserved25;	//0xC901B878
	UINT32                                                   reserved26;	//0xC901B87C
	UINT32                                                   reserved27;	//0xC901B880
	UINT32                                                   reserved28;	//0xC901B884
	UINT32                                                   reserved29;	//0xC901B888
	UINT32                                                   reserved30;	//0xC901B88C
	UINT32                                                   reserved31;	//0xC901B890
	UINT32                                                   reserved32;	//0xC901B894
	UINT32                                                   reserved33;	//0xC901B898
	UINT32                                                   reserved34;	//0xC901B89C
	UINT32                                                   reserved35;	//0xC901B8A0
	UINT32                                                   reserved36;	//0xC901B8A4
	UINT32                                                   reserved37;	//0xC901B8A8
	UINT32                                                   reserved38;	//0xC901B8AC
	UINT32                                                   reserved39;	//0xC901B8B0
	UINT32                                                   reserved40;	//0xC901B8B4
	UINT32                                                   reserved41;	//0xC901B8B8
	UINT32                                                   reserved42;	//0xC901B8BC
	UINT32                                                   reserved43;	//0xC901B8C0
	UINT32                                                   reserved44;	//0xC901B8C4
	UINT32                                                   reserved45;	//0xC901B8C8
	UINT32                                                   reserved46;	//0xC901B8CC
	UINT32                                                   reserved47;	//0xC901B8D0
	UINT32                                                   reserved48;	//0xC901B8D4
	UINT32                                                   reserved49;	//0xC901B8D8
	UINT32                                                   reserved50;	//0xC901B8DC
	UINT32                                                   reserved51;	//0xC901B8E0
	UINT32                                                   reserved52;	//0xC901B8E4
	UINT32                                                   reserved53;	//0xC901B8E8
	UINT32                                                   reserved54;	//0xC901B8EC
	REG_SHY_4K_SHP_DP_CTRL_00_T                          shp_dp_ctrl_00;	//0xC901B8F0
	UINT32                                                   reserved55;	//0xC901B8F4
	UINT32                                                   reserved56;	//0xC901B8F8
	UINT32                                                   reserved57;	//0xC901B8FC
	REG_SHY_4K_SHP_FD_CTRL_00_T                          shp_fd_ctrl_00;	//0xC901B900
	REG_SHY_4K_SHP_FD_CTRL_01_T                          shp_fd_ctrl_01;	//0xC901B904
	REG_SHY_4K_SHP_FD_CTRL_02_T                          shp_fd_ctrl_02;	//0xC901B908
	REG_SHY_4K_SHP_FD_CTRL_03_T                          shp_fd_ctrl_03;	//0xC901B90C
	REG_SHY_4K_SHP_FD_CTRL_04_T                          shp_fd_ctrl_04;	//0xC901B910
	REG_SHY_4K_SHP_FD_CTRL_05_T                          shp_fd_ctrl_05;	//0xC901B914
	REG_SHY_4K_SHP_FD_CTRL_06_T                          shp_fd_ctrl_06;	//0xC901B918
	REG_SHY_4K_SHP_FD_CTRL_07_T                          shp_fd_ctrl_07;	//0xC901B91C
	REG_SHY_4K_SHP_FD_CTRL_08_T                          shp_fd_ctrl_08;	//0xC901B920
	REG_SHY_4K_SHP_FD_CTRL_09_T                          shp_fd_ctrl_09;	//0xC901B924
	REG_SHY_4K_SHP_FD_CTRL_0A_T                          shp_fd_ctrl_0a;	//0xC901B928
	REG_SHY_4K_SHP_FD_CTRL_0B_T                          shp_fd_ctrl_0b;	//0xC901B92C
	REG_SHY_4K_SHP_FD_CTRL_0C_T                          shp_fd_ctrl_0c;	//0xC901B930
	REG_SHY_4K_SHP_FD_CTRL_0D_T                          shp_fd_ctrl_0d;	//0xC901B934
	REG_SHY_4K_SHP_FD_CTRL_0E_T                          shp_fd_ctrl_0e;	//0xC901B938
	REG_SHY_4K_SHP_FD_CTRL_0F_T                          shp_fd_ctrl_0f;	//0xC901B93C
	REG_SHY_4K_SHP_FD_CTRL_10_T                          shp_fd_ctrl_10;	//0xC901B940
	REG_SHY_4K_SHP_FD_CTRL_11_T                          shp_fd_ctrl_11;	//0xC901B944
	REG_SHY_4K_SHP_FD_CTRL_12_T                          shp_fd_ctrl_12;	//0xC901B948
	REG_SHY_4K_SHP_FD_CTRL_13_T                          shp_fd_ctrl_13;	//0xC901B94C
	REG_SHY_4K_SHP_FD_CTRL_14_T                          shp_fd_ctrl_14;	//0xC901B950
	REG_SHY_4K_SHP_FD_CTRL_15_T                          shp_fd_ctrl_15;	//0xC901B954
	REG_SHY_4K_SHP_FD_CTRL_16_T                          shp_fd_ctrl_16;	//0xC901B958
	UINT32                                                   reserved58;	//0xC901B95C
	REG_SHY_4K_SHP_MP_CTRL_00_T                          shp_mp_ctrl_00;	//0xC901B960
	REG_SHY_4K_SHP_MP_CTRL_01_T                          shp_mp_ctrl_01;	//0xC901B964
	REG_SHY_4K_SHP_MP_CTRL_02_T                          shp_mp_ctrl_02;	//0xC901B968
	REG_SHY_4K_SHP_MP_CTRL_03_T                          shp_mp_ctrl_03;	//0xC901B96C
	REG_SHY_4K_SHP_MP_CTRL_04_T                          shp_mp_ctrl_04;	//0xC901B970
	REG_SHY_4K_SHP_MP_CTRL_05_T                          shp_mp_ctrl_05;	//0xC901B974
	REG_SHY_4K_SHP_MP_CTRL_06_T                          shp_mp_ctrl_06;	//0xC901B978
	REG_SHY_4K_SHP_MP_CTRL_07_T                          shp_mp_ctrl_07;	//0xC901B97C
	REG_SHY_4K_SHP_MP_CTRL_08_T                          shp_mp_ctrl_08;	//0xC901B980
	REG_SHY_4K_SHP_MP_CTRL_09_T                          shp_mp_ctrl_09;	//0xC901B984
	REG_SHY_4K_SHP_MP_CTRL_0A_T                          shp_mp_ctrl_0a;	//0xC901B988
	REG_SHY_4K_SHP_MP_CTRL_0B_T                          shp_mp_ctrl_0b;	//0xC901B98C
	REG_SHY_4K_SHP_MP_CTRL_0C_T                          shp_mp_ctrl_0c;	//0xC901B990
	REG_SHY_4K_SHP_APL_CTRL_00_T                        shp_apl_ctrl_00;	//0xC901B994
	UINT32                                                   reserved59;	//0xC901B998
	UINT32                                                   reserved60;	//0xC901B99C
	REG_SHY_4K_SHP_LC_CTRL_00_T                          shp_lc_ctrl_00;	//0xC901B9A0
	REG_SHY_4K_SHP_LC_CTRL_01_T                          shp_lc_ctrl_01;	//0xC901B9A4
	REG_SHY_4K_SHP_LC_CTRL_02_T                          shp_lc_ctrl_02;	//0xC901B9A8
	REG_SHY_4K_SHP_LC_CTRL_03_T                          shp_lc_ctrl_03;	//0xC901B9AC
	REG_SHY_4K_SHP_LC_CTRL_04_T                          shp_lc_ctrl_04;	//0xC901B9B0
	UINT32                                                   reserved61;	//0xC901B9B4
	UINT32                                                   reserved62;	//0xC901B9B8
	UINT32                                                   reserved63;	//0xC901B9BC
	REG_SHY_4K_SHP_DER_CTRL_00_T                        shp_der_ctrl_00;	//0xC901B9C0
	REG_SHY_4K_SHP_DER_CTRL_01_T                        shp_der_ctrl_01;	//0xC901B9C4
	REG_SHY_4K_SHP_DER_CTRL_02_T                        shp_der_ctrl_02;	//0xC901B9C8
	REG_SHY_4K_SHP_DER_CTRL_03_T                        shp_der_ctrl_03;	//0xC901B9CC
	REG_SHY_4K_SHP_DER_CTRL_04_T                        shp_der_ctrl_04;	//0xC901B9D0
	REG_SHY_4K_SHP_DER_CTRL_05_T                        shp_der_ctrl_05;	//0xC901B9D4
	REG_SHY_4K_SHP_DER_CTRL_06_T                        shp_der_ctrl_06;	//0xC901B9D8
	REG_SHY_4K_SHP_DER_CTRL_07_T                        shp_der_ctrl_07;	//0xC901B9DC
	REG_SHY_4K_SHP_SP_CTRL_00_T                          shp_sp_ctrl_00;	//0xC901B9E0
	REG_SHY_4K_SHP_SP_CTRL_01_T                          shp_sp_ctrl_01;	//0xC901B9E4
	REG_SHY_4K_SHP_SP_CTRL_02_T                          shp_sp_ctrl_02;	//0xC901B9E8
	REG_SHY_4K_SHP_SP_CTRL_03_T                          shp_sp_ctrl_03;	//0xC901B9EC
	REG_SHY_4K_SHP_SP_CTRL_04_T                          shp_sp_ctrl_04;	//0xC901B9F0
	REG_SHY_4K_SHP_SP_CTRL_05_T                          shp_sp_ctrl_05;	//0xC901B9F4
	REG_SHY_4K_SHP_SP_CTRL_06_T                          shp_sp_ctrl_06;	//0xC901B9F8
	REG_SHY_4K_SHP_SP_CTRL_07_T                          shp_sp_ctrl_07;	//0xC901B9FC
	REG_SHY_4K_SHP_SP_CTRL_08_T                          shp_sp_ctrl_08;	//0xC901BA00
	REG_SHY_4K_SHP_SP_CTRL_09_T                          shp_sp_ctrl_09;	//0xC901BA04
	REG_SHY_4K_SHP_SP_CTRL_0A_T                          shp_sp_ctrl_0a;	//0xC901BA08
	REG_SHY_4K_SHP_SP_CTRL_0B_T                          shp_sp_ctrl_0b;	//0xC901BA0C
	REG_SHY_4K_SHP_SP_CTRL_0C_T                          shp_sp_ctrl_0c;	//0xC901BA10
	UINT32                                                   reserved64;	//0xC901BA14
	UINT32                                                   reserved65;	//0xC901BA18
	UINT32                                                   reserved66;	//0xC901BA1C
	REG_SHY_4K_SHP_PTI_CTRL_00_T                        shp_pti_ctrl_00;	//0xC901BA20
	REG_SHY_4K_SHP_PTI_CTRL_01_T                        shp_pti_ctrl_01;	//0xC901BA24
	REG_SHY_4K_SHP_PTI_CTRL_02_T                        shp_pti_ctrl_02;	//0xC901BA28
	REG_SHY_4K_SHP_PTI_CTRL_03_T                        shp_pti_ctrl_03;	//0xC901BA2C
	REG_SHY_4K_SHP_STI_CTRL_00_T                        shp_sti_ctrl_00;	//0xC901BA30
	UINT32                                                   reserved67;	//0xC901BA34
	UINT32                                                   reserved68;	//0xC901BA38
	UINT32                                                   reserved69;	//0xC901BA3C
	REG_SHY_4K_SHP_TGEN_CTRL_00_T                      shp_tgen_ctrl_00;	//0xC901BA40
	REG_SHY_4K_SHP_TGEN_CTRL_01_T                      shp_tgen_ctrl_01;	//0xC901BA44
	REG_SHY_4K_SHP_TGEN_CTRL_02_T                      shp_tgen_ctrl_02;	//0xC901BA48
	REG_SHY_4K_SHP_TGEN_CTRL_03_C0_T                shp_tgen_ctrl_03_c0;	//0xC901BA4C
	REG_SHY_4K_SHP_TGEN_CTRL_03_C1_T                shp_tgen_ctrl_03_c1;	//0xC901BA50
	REG_SHY_4K_SHP_TGEN_CTRL_04_T                      shp_tgen_ctrl_04;	//0xC901BA54
	REG_SHY_4K_SHP_TGEN_CTRL_05_T                      shp_tgen_ctrl_05;	//0xC901BA58
	REG_SHY_4K_SHP_TGEN_CTRL_06_T                      shp_tgen_ctrl_06;	//0xC901BA5C
	REG_SHY_4K_SHP_TGEN_CTRL_07_T                      shp_tgen_ctrl_07;	//0xC901BA60
	REG_SHY_4K_SHP_TGEN_CTRL_08_T                      shp_tgen_ctrl_08;	//0xC901BA64
	REG_SHY_4K_SHP_TGEN_CTRL_09_T                      shp_tgen_ctrl_09;	//0xC901BA68
	REG_SHY_4K_SHP_TGEN_CTRL_0A_T                      shp_tgen_ctrl_0a;	//0xC901BA6C
	REG_SHY_4K_SHP_TGEN_CTRL_0B_T                      shp_tgen_ctrl_0b;	//0xC901BA70
	REG_SHY_4K_SHP_SNR_CTRL_00_T                        shp_snr_ctrl_00;	//0xC901BA74
	UINT32                                                   reserved70;	//0xC901BA78
	UINT32                                                   reserved71;	//0xC901BA7C
	REG_SHY_4K_SHP_DCTP_CTRL_00_T                      shp_dctp_ctrl_00;	//0xC901BA80
	REG_SHY_4K_SHP_DCTP_CTRL_01_T                      shp_dctp_ctrl_01;	//0xC901BA84
	REG_SHY_4K_SHP_DCTP_CTRL_02_T                      shp_dctp_ctrl_02;	//0xC901BA88
	REG_SHY_4K_SHP_DCTP_CTRL_03_T                      shp_dctp_ctrl_03;	//0xC901BA8C
	REG_SHY_4K_SHP_DCTP_CTRL_04_T                      shp_dctp_ctrl_04;	//0xC901BA90
	REG_SHY_4K_SHP_DCTP_CTRL_05_T                      shp_dctp_ctrl_05;	//0xC901BA94
	REG_SHY_4K_SHP_DCTP_CTRL_06_T                      shp_dctp_ctrl_06;	//0xC901BA98
	REG_SHY_4K_SHP_DCTP_CTRL_07_T                      shp_dctp_ctrl_07;	//0xC901BA9C
	REG_SHY_4K_SHP_DCTP_CTRL_08_T                      shp_dctp_ctrl_08;	//0xC901BAA0
	REG_SHY_4K_SHP_DCTP_CTRL_09_T                      shp_dctp_ctrl_09;	//0xC901BAA4
	REG_SHY_4K_SHP_DCTP_CTRL_0A_T                      shp_dctp_ctrl_0a;	//0xC901BAA8
	REG_SHY_4K_SHP_DCTP_CTRL_0B_T                      shp_dctp_ctrl_0b;	//0xC901BAAC
	REG_SHY_4K_SHP_DCTP_CTRL_0C_T                      shp_dctp_ctrl_0c;	//0xC901BAB0
	REG_SHY_4K_SHP_DCTP_CTRL_0D_T                      shp_dctp_ctrl_0d;	//0xC901BAB4
	REG_SHY_4K_SHP_DCTP_CTRL_0E_T                      shp_dctp_ctrl_0e;	//0xC901BAB8
	REG_SHY_4K_SHP_DCTP_CTRL_0F_T                      shp_dctp_ctrl_0f;	//0xC901BABC
	REG_SHY_4K_SHP_DCTP_CTRL_10_T                      shp_dctp_ctrl_10;	//0xC901BAC0
	REG_SHY_4K_SHP_DCTP_CTRL_11_T                      shp_dctp_ctrl_11;	//0xC901BAC4
	REG_SHY_4K_SHP_DCTP_CTRL_12_T                      shp_dctp_ctrl_12;	//0xC901BAC8
	REG_SHY_4K_SHP_DCTP_CTRL_13_T                      shp_dctp_ctrl_13;	//0xC901BACC
	REG_SHY_4K_SHP_DCTP_CTRL_14_T                      shp_dctp_ctrl_14;	//0xC901BAD0
	REG_SHY_4K_SHP_DCTP_CTRL_15_T                      shp_dctp_ctrl_15;	//0xC901BAD4
	REG_SHY_4K_SHP_DCTP_CTRL_16_T                      shp_dctp_ctrl_16;	//0xC901BAD8
	REG_SHY_4K_SHP_DCTP_CTRL_17_T                      shp_dctp_ctrl_17;	//0xC901BADC
	REG_SHY_4K_SHP_DCTP_CTRL_18_T                      shp_dctp_ctrl_18;	//0xC901BAE0
	REG_SHY_4K_SHP_DCTP_CTRL_19_T                      shp_dctp_ctrl_19;	//0xC901BAE4
	REG_SHY_4K_SHP_DCTP_CTRL_1A_T                      shp_dctp_ctrl_1a;	//0xC901BAE8
	REG_SHY_4K_SHP_DCTP_CTRL_1B_T                      shp_dctp_ctrl_1b;	//0xC901BAEC
	REG_SHY_4K_SHP_DCTP_CTRL_1C_T                      shp_dctp_ctrl_1c;	//0xC901BAF0
	REG_SHY_4K_SHP_DCTP_CTRL_1D_T                      shp_dctp_ctrl_1d;	//0xC901BAF4
	REG_SHY_4K_SHP_DCTP_CTRL_1E_T                      shp_dctp_ctrl_1e;	//0xC901BAF8
	REG_SHY_4K_SHP_DCTP_CTRL_1F_T                      shp_dctp_ctrl_1f;	//0xC901BAFC
	REG_SHY_4K_SHP_NNTG_CTRL_00_T                      shp_nntg_ctrl_00;	//0xC901BB00
	REG_SHY_4K_SHP_NNTG_CTRL_01_C0_T                shp_nntg_ctrl_01_c0;	//0xC901BB04
	REG_SHY_4K_SHP_NNTG_CTRL_02_C0_T                shp_nntg_ctrl_02_c0;	//0xC901BB08
	REG_SHY_4K_SHP_NNTG_CTRL_03_C0_T                shp_nntg_ctrl_03_c0;	//0xC901BB0C
	REG_SHY_4K_SHP_NNTG_CTRL_04_C0_T                shp_nntg_ctrl_04_c0;	//0xC901BB10
	REG_SHY_4K_SHP_NNTG_CTRL_05_C0_T                shp_nntg_ctrl_05_c0;	//0xC901BB14
	REG_SHY_4K_SHP_NNTG_CTRL_01_C1_T                shp_nntg_ctrl_01_c1;	//0xC901BB18
	REG_SHY_4K_SHP_NNTG_CTRL_02_C1_T                shp_nntg_ctrl_02_c1;	//0xC901BB1C
	REG_SHY_4K_SHP_NNTG_CTRL_03_C1_T                shp_nntg_ctrl_03_c1;	//0xC901BB20
	REG_SHY_4K_SHP_NNTG_CTRL_04_C1_T                shp_nntg_ctrl_04_c1;	//0xC901BB24
	REG_SHY_4K_SHP_NNTG_CTRL_05_C1_T                shp_nntg_ctrl_05_c1;	//0xC901BB28
	REG_SHY_4K_SHP_NNTG_CTRL_06_T                      shp_nntg_ctrl_06;	//0xC901BB2C
	REG_SHY_4K_SHP_NNTG_CTRL_07_T                      shp_nntg_ctrl_07;	//0xC901BB30
	REG_SHY_4K_SHP_NNTG_CTRL_08_T                      shp_nntg_ctrl_08;	//0xC901BB34
	REG_SHY_4K_SHP_NNTG_CTRL_09_T                      shp_nntg_ctrl_09;	//0xC901BB38
	REG_SHY_4K_SHP_NNTG_CTRL_0A_T                      shp_nntg_ctrl_0a;	//0xC901BB3C
	REG_SHY_4K_SHP_NNTG_CTRL_0B_T                      shp_nntg_ctrl_0b;	//0xC901BB40
	REG_SHY_4K_SHP_NNTG_CTRL_0C_T                      shp_nntg_ctrl_0c;	//0xC901BB44
	REG_SHY_4K_SHP_NNTG_CTRL_0D_T                      shp_nntg_ctrl_0d;	//0xC901BB48
	REG_SHY_4K_SHP_NNTG_CTRL_0E_T                      shp_nntg_ctrl_0e;	//0xC901BB4C
	REG_SHY_4K_SHP_NNTG_CTRL_0F_T                      shp_nntg_ctrl_0f;	//0xC901BB50
	REG_SHY_4K_SHP_NNTG_CTRL_10_T                      shp_nntg_ctrl_10;	//0xC901BB54
	UINT32                                                   reserved72;	//0xC901BB58
	UINT32                                                   reserved73;	//0xC901BB5C
	REG_SHY_4K_SHP_DP_SUM_CTRL_00_T                  shp_dp_sum_ctrl_00;	//0xC901BB60
	REG_SHY_4K_SHP_DP_SUM_CTRL_01_T                  shp_dp_sum_ctrl_01;	//0xC901BB64
	REG_SHY_4K_SHP_DP_SUM_CTRL_02_T                  shp_dp_sum_ctrl_02;	//0xC901BB68
	UINT32                                                   reserved74;	//0xC901BB6C
	UINT32                                                   reserved75;	//0xC901BB70
	UINT32                                                   reserved76;	//0xC901BB74
	UINT32                                                   reserved77;	//0xC901BB78
	UINT32                                                   reserved78;	//0xC901BB7C
	UINT32                                                   reserved79;	//0xC901BB80
	UINT32                                                   reserved80;	//0xC901BB84
	UINT32                                                   reserved81;	//0xC901BB88
	UINT32                                                   reserved82;	//0xC901BB8C
	UINT32                                                   reserved83;	//0xC901BB90
	UINT32                                                   reserved84;	//0xC901BB94
	UINT32                                                   reserved85;	//0xC901BB98
	UINT32                                                   reserved86;	//0xC901BB9C
	REG_SHY_4K_SHP_DP_WIN_CTRL_00_T                  shp_dp_win_ctrl_00;	//0xC901BBA0
	REG_SHY_4K_SHP_DP_WIN_CTRL_01_T                  shp_dp_win_ctrl_01;	//0xC901BBA4
	REG_SHY_4K_SHP_DP_WIN_CTRL_02_T                  shp_dp_win_ctrl_02;	//0xC901BBA8
	REG_SHY_4K_SHP_DP_WIN_CTRL_03_T                  shp_dp_win_ctrl_03;	//0xC901BBAC
	REG_SHY_4K_SHP_DP_WIN_CTRL_04_T                  shp_dp_win_ctrl_04;	//0xC901BBB0
	UINT32                                                   reserved87;	//0xC901BBB4
	UINT32                                                   reserved88;	//0xC901BBB8
	UINT32                                                   reserved89;	//0xC901BBBC
	REG_SHY_4K_SHP_FD_REGION_TEXT_00_T            shp_fd_region_text_00;	//0xC901BBC0
	REG_SHY_4K_SHP_FD_REGION_TEXT_01_T            shp_fd_region_text_01;	//0xC901BBC4
	REG_SHY_4K_SHP_FD_REGION_TEXT_02_T            shp_fd_region_text_02;	//0xC901BBC8
	REG_SHY_4K_SHP_FD_TMAP_TEMP_00_T                shp_fd_tmap_temp_00;	//0xC901BBCC
	REG_SHY_4K_SHP_FD_TMAP_TEMP_01_T                shp_fd_tmap_temp_01;	//0xC901BBD0
	REG_SHY_4K_SHP_FD_TMAP_TEMP_02_T                shp_fd_tmap_temp_02;	//0xC901BBD4
	REG_SHY_4K_SHP_FD_TMAP_TEMP_03_T                shp_fd_tmap_temp_03;	//0xC901BBD8
	REG_SHY_4K_SHP_FD_TMAP_TEMP_04_T                shp_fd_tmap_temp_04;	//0xC901BBDC
	REG_SHY_4K_SHP_FD_TMAP_TEMP_05_T                shp_fd_tmap_temp_05;	//0xC901BBE0
	REG_SHY_4K_SHP_FD_TMAP_TEMP_06_T                shp_fd_tmap_temp_06;	//0xC901BBE4
	REG_SHY_4K_SHP_FD_TMAP_TEMP_07_T                shp_fd_tmap_temp_07;	//0xC901BBE8
	REG_SHY_4K_SHP_FD_TMAP_TEMP_08_T                shp_fd_tmap_temp_08;	//0xC901BBEC
	REG_SHY_4K_SHP_FD_TMAP_TEMP_09_T                shp_fd_tmap_temp_09;	//0xC901BBF0
	REG_SHY_4K_SHP_FD_TMAP_TEMP_0A_T                shp_fd_tmap_temp_0a;	//0xC901BBF4
	REG_SHY_4K_SHP_FD_TMAP_TEMP_0B_T                shp_fd_tmap_temp_0b;	//0xC901BBF8
	REG_SHY_4K_SHP_FD_TMAP_TEMP_0C_T                shp_fd_tmap_temp_0c;	//0xC901BBFC
	REG_SHY_4K_SHP_DJ_CTRL_00_T                          shp_dj_ctrl_00;	//0xC901BC00
	REG_SHY_4K_SHP_DJ_CTRL_01_T                          shp_dj_ctrl_01;	//0xC901BC04
	REG_SHY_4K_SHP_DJ_CTRL_02_T                          shp_dj_ctrl_02;	//0xC901BC08
	REG_SHY_4K_SHP_DJ_CTRL_03_T                          shp_dj_ctrl_03;	//0xC901BC0C
	REG_SHY_4K_SHP_DJ_CTRL_04_T                          shp_dj_ctrl_04;	//0xC901BC10
	REG_SHY_4K_SHP_DJ_CTRL_05_T                          shp_dj_ctrl_05;	//0xC901BC14
	REG_SHY_4K_SHP_DJ_CTRL_06_T                          shp_dj_ctrl_06;	//0xC901BC18
	REG_SHY_4K_SHP_DJ_CTRL_07_T                          shp_dj_ctrl_07;	//0xC901BC1C
	REG_SHY_4K_SHP_DJ_CTRL_08_T                          shp_dj_ctrl_08;	//0xC901BC20
	REG_SHY_4K_SHP_DJ_CTRL_09_T                          shp_dj_ctrl_09;	//0xC901BC24
	REG_SHY_4K_SHP_DJ_CTRL_0A_T                          shp_dj_ctrl_0a;	//0xC901BC28
	REG_SHY_4K_SHP_DJ_CTRL_0B_T                          shp_dj_ctrl_0b;	//0xC901BC2C
	REG_SHY_4K_SHP_DJ_CTRL_0C_T                          shp_dj_ctrl_0c;	//0xC901BC30
	REG_SHY_4K_SHP_DJ_CTRL_0D_T                          shp_dj_ctrl_0d;	//0xC901BC34
	REG_SHY_4K_SHP_DJ_CTRL_0E_T                          shp_dj_ctrl_0e;	//0xC901BC38
	REG_SHY_4K_SHP_DJ_CTRL_0F_T                          shp_dj_ctrl_0f;	//0xC901BC3C
	REG_SHY_4K_SHP_DJ_CTRL_10_T                          shp_dj_ctrl_10;	//0xC901BC40
	REG_SHY_4K_SHP_DJ_CTRL_11_T                          shp_dj_ctrl_11;	//0xC901BC44
	REG_SHY_4K_SHP_DJ_CTRL_12_T                          shp_dj_ctrl_12;	//0xC901BC48
	REG_SHY_4K_SHP_DJ_CTRL_13_T                          shp_dj_ctrl_13;	//0xC901BC4C
	REG_SHY_4K_SHP_DJ_CTRL_14_T                          shp_dj_ctrl_14;	//0xC901BC50
	REG_SHY_4K_SHP_DJ_CTRL_15_T                          shp_dj_ctrl_15;	//0xC901BC54
	REG_SHY_4K_SHP_DJ_CTRL_16_T                          shp_dj_ctrl_16;	//0xC901BC58
	REG_SHY_4K_SHP_DJ_CTRL_17_T                          shp_dj_ctrl_17;	//0xC901BC5C
	REG_SHY_4K_SHP_DJ_CTRL_18_T                          shp_dj_ctrl_18;	//0xC901BC60
	REG_SHY_4K_SHP_DJ_CTRL_19_T                          shp_dj_ctrl_19;	//0xC901BC64
	REG_SHY_4K_SHP_DJ_CTRL_1A_T                          shp_dj_ctrl_1a;	//0xC901BC68
	REG_SHY_4K_SHP_DJ_CTRL_1B_T                          shp_dj_ctrl_1b;	//0xC901BC6C
	REG_SHY_4K_SHP_DJ_CTRL_1C_T                          shp_dj_ctrl_1c;	//0xC901BC70
	REG_SHY_4K_SHP_DJ_CTRL_1D_T                          shp_dj_ctrl_1d;	//0xC901BC74
	REG_SHY_4K_SHP_DJ_CTRL_1E_T                          shp_dj_ctrl_1e;	//0xC901BC78
	REG_SHY_4K_SHP_DJ_CTRL_1F_T                          shp_dj_ctrl_1f;	//0xC901BC7C
	REG_SHY_4K_SHP_DJ_CTRL_20_T                          shp_dj_ctrl_20;	//0xC901BC80
	UINT32                                                   reserved90;	//0xC901BC84
	UINT32                                                   reserved91;	//0xC901BC88
	UINT32                                                   reserved92;	//0xC901BC8C
	REG_SHY_4K_SHP_DB_CTRL_00_T                          shp_db_ctrl_00;	//0xC901BC90
	REG_SHY_4K_SHP_DB_CTRL_01_T                          shp_db_ctrl_01;	//0xC901BC94
	UINT32                                                   reserved93;	//0xC901BC98
	UINT32                                                   reserved94;	//0xC901BC9C
	REG_SHY_4K_SHP_DJ_WIN_CTRL_00_T                  shp_dj_win_ctrl_00;	//0xC901BCA0
	REG_SHY_4K_SHP_DJ_WIN_CTRL_01_T                  shp_dj_win_ctrl_01;	//0xC901BCA4
	REG_SHY_4K_SHP_DJ_WIN_CTRL_02_T                  shp_dj_win_ctrl_02;	//0xC901BCA8
	REG_SHY_4K_SHP_DJ_WIN_CTRL_03_T                  shp_dj_win_ctrl_03;	//0xC901BCAC
	REG_SHY_4K_SHP_DJ_WIN_CTRL_04_T                  shp_dj_win_ctrl_04;	//0xC901BCB0
	UINT32                                                   reserved95;	//0xC901BCB4
	UINT32                                                   reserved96;	//0xC901BCB8
	UINT32                                                   reserved97;	//0xC901BCBC
	UINT32                                                   reserved98;	//0xC901BCC0
	UINT32                                                   reserved99;	//0xC901BCC4
	UINT32                                                  reserved100;	//0xC901BCC8
	UINT32                                                  reserved101;	//0xC901BCCC
	UINT32                                                  reserved102;	//0xC901BCD0
	UINT32                                                  reserved103;	//0xC901BCD4
	UINT32                                                  reserved104;	//0xC901BCD8
	UINT32                                                  reserved105;	//0xC901BCDC
	UINT32                                                  reserved106;	//0xC901BCE0
	UINT32                                                  reserved107;	//0xC901BCE4
	UINT32                                                  reserved108;	//0xC901BCE8
	UINT32                                                  reserved109;	//0xC901BCEC
	UINT32                                                  reserved110;	//0xC901BCF0
	UINT32                                                  reserved111;	//0xC901BCF4
	UINT32                                                  reserved112;	//0xC901BCF8
	UINT32                                                  reserved113;	//0xC901BCFC
	UINT32                                                  reserved114;	//0xC901BD00
	UINT32                                                  reserved115;	//0xC901BD04
	UINT32                                                  reserved116;	//0xC901BD08
	UINT32                                                  reserved117;	//0xC901BD0C
	UINT32                                                  reserved118;	//0xC901BD10
	UINT32                                                  reserved119;	//0xC901BD14
	UINT32                                                  reserved120;	//0xC901BD18
	UINT32                                                  reserved121;	//0xC901BD1C
	UINT32                                                  reserved122;	//0xC901BD20
	UINT32                                                  reserved123;	//0xC901BD24
	UINT32                                                  reserved124;	//0xC901BD28
	UINT32                                                  reserved125;	//0xC901BD2C
	UINT32                                                  reserved126;	//0xC901BD30
	UINT32                                                  reserved127;	//0xC901BD34
	UINT32                                                  reserved128;	//0xC901BD38
	UINT32                                                  reserved129;	//0xC901BD3C
	UINT32                                                  reserved130;	//0xC901BD40
	UINT32                                                  reserved131;	//0xC901BD44
	UINT32                                                  reserved132;	//0xC901BD48
	UINT32                                                  reserved133;	//0xC901BD4C
	UINT32                                                  reserved134;	//0xC901BD50
	UINT32                                                  reserved135;	//0xC901BD54
	UINT32                                                  reserved136;	//0xC901BD58
	UINT32                                                  reserved137;	//0xC901BD5C
	UINT32                                                  reserved138;	//0xC901BD60
	UINT32                                                  reserved139;	//0xC901BD64
	UINT32                                                  reserved140;	//0xC901BD68
	UINT32                                                  reserved141;	//0xC901BD6C
	UINT32                                                  reserved142;	//0xC901BD70
	UINT32                                                  reserved143;	//0xC901BD74
	UINT32                                                  reserved144;	//0xC901BD78
	UINT32                                                  reserved145;	//0xC901BD7C
	UINT32                                                  reserved146;	//0xC901BD80
	UINT32                                                  reserved147;	//0xC901BD84
	UINT32                                                  reserved148;	//0xC901BD88
	UINT32                                                  reserved149;	//0xC901BD8C
	UINT32                                                  reserved150;	//0xC901BD90
	UINT32                                                  reserved151;	//0xC901BD94
	UINT32                                                  reserved152;	//0xC901BD98
	UINT32                                                  reserved153;	//0xC901BD9C
	UINT32                                                  reserved154;	//0xC901BDA0
	UINT32                                                  reserved155;	//0xC901BDA4
	UINT32                                                  reserved156;	//0xC901BDA8
	UINT32                                                  reserved157;	//0xC901BDAC
	UINT32                                                  reserved158;	//0xC901BDB0
	UINT32                                                  reserved159;	//0xC901BDB4
	UINT32                                                  reserved160;	//0xC901BDB8
	UINT32                                                  reserved161;	//0xC901BDBC
	UINT32                                                  reserved162;	//0xC901BDC0
	UINT32                                                  reserved163;	//0xC901BDC4
	UINT32                                                  reserved164;	//0xC901BDC8
	UINT32                                                  reserved165;	//0xC901BDCC
	UINT32                                                  reserved166;	//0xC901BDD0
	UINT32                                                  reserved167;	//0xC901BDD4
	UINT32                                                  reserved168;	//0xC901BDD8
	UINT32                                                  reserved169;	//0xC901BDDC
	UINT32                                                  reserved170;	//0xC901BDE0
	UINT32                                                  reserved171;	//0xC901BDE4
	UINT32                                                  reserved172;	//0xC901BDE8
	UINT32                                                  reserved173;	//0xC901BDEC
	UINT32                                                  reserved174;	//0xC901BDF0
	UINT32                                                  reserved175;	//0xC901BDF4
	UINT32                                                  reserved176;	//0xC901BDF8
	UINT32                                                  reserved177;	//0xC901BDFC
	REG_SHY_4K_SHP_CORE_STAT_00_T                      shp_core_stat_00;	//0xC901BE00
	REG_SHY_4K_SHP_CORE_STAT_01_T                      shp_core_stat_01;	//0xC901BE04
	REG_SHY_4K_SHP_CORE_STAT_02_T                      shp_core_stat_02;	//0xC901BE08
	REG_SHY_4K_SHP_CORE_STAT_03_T                      shp_core_stat_03;	//0xC901BE0C
	REG_SHY_4K_SHP_CORE_STAT_04_T                      shp_core_stat_04;	//0xC901BE10
	REG_SHY_4K_SHP_CORE_STAT_05_T                      shp_core_stat_05;	//0xC901BE14
	UINT32                                                  reserved178;	//0xC901BE18
	UINT32                                                  reserved179;	//0xC901BE1C
	UINT32                                                  reserved180;	//0xC901BE20
	UINT32                                                  reserved181;	//0xC901BE24
	UINT32                                                  reserved182;	//0xC901BE28
	UINT32                                                  reserved183;	//0xC901BE2C
	UINT32                                                  reserved184;	//0xC901BE30
	UINT32                                                  reserved185;	//0xC901BE34
	UINT32                                                  reserved186;	//0xC901BE38
	UINT32                                                  reserved187;	//0xC901BE3C
	UINT32                                                  reserved188;	//0xC901BE40
	UINT32                                                  reserved189;	//0xC901BE44
	UINT32                                                  reserved190;	//0xC901BE48
	UINT32                                                  reserved191;	//0xC901BE4C
	UINT32                                                  reserved192;	//0xC901BE50
	UINT32                                                  reserved193;	//0xC901BE54
	UINT32                                                  reserved194;	//0xC901BE58
	UINT32                                                  reserved195;	//0xC901BE5C
	REG_SHY_4K_SHP_CORE_FD_STAT_00_T                shp_core_fd_stat_00;	//0xC901BE60
	REG_SHY_4K_SHP_CORE_FD_STAT_01_T                shp_core_fd_stat_01;	//0xC901BE64
	REG_SHY_4K_SHP_CORE_FD_STAT_02_T                shp_core_fd_stat_02;	//0xC901BE68
	REG_SHY_4K_SHP_CORE_FD_STAT_03_T                shp_core_fd_stat_03;	//0xC901BE6C
	UINT32                                                  reserved196;	//0xC901BE70
	UINT32                                                  reserved197;	//0xC901BE74
	UINT32                                                  reserved198;	//0xC901BE78
	UINT32                                                  reserved199;	//0xC901BE7C
	UINT32                                                  reserved200;	//0xC901BE80
	UINT32                                                  reserved201;	//0xC901BE84
	UINT32                                                  reserved202;	//0xC901BE88
	UINT32                                                  reserved203;	//0xC901BE8C
	UINT32                                                  reserved204;	//0xC901BE90
	UINT32                                                  reserved205;	//0xC901BE94
	UINT32                                                  reserved206;	//0xC901BE98
	UINT32                                                  reserved207;	//0xC901BE9C
	UINT32                                                  reserved208;	//0xC901BEA0
	UINT32                                                  reserved209;	//0xC901BEA4
	UINT32                                                  reserved210;	//0xC901BEA8
	UINT32                                                  reserved211;	//0xC901BEAC
	UINT32                                                  reserved212;	//0xC901BEB0
	UINT32                                                  reserved213;	//0xC901BEB4
	UINT32                                                  reserved214;	//0xC901BEB8
	UINT32                                                  reserved215;	//0xC901BEBC
	UINT32                                                  reserved216;	//0xC901BEC0
	UINT32                                                  reserved217;	//0xC901BEC4
	UINT32                                                  reserved218;	//0xC901BEC8
	UINT32                                                  reserved219;	//0xC901BECC
	UINT32                                                  reserved220;	//0xC901BED0
	UINT32                                                  reserved221;	//0xC901BED4
	UINT32                                                  reserved222;	//0xC901BED8
	UINT32                                                  reserved223;	//0xC901BEDC
	UINT32                                                  reserved224;	//0xC901BEE0
	UINT32                                                  reserved225;	//0xC901BEE4
	UINT32                                                  reserved226;	//0xC901BEE8
	UINT32                                                  reserved227;	//0xC901BEEC
	UINT32                                                  reserved228;	//0xC901BEF0
	UINT32                                                  reserved229;	//0xC901BEF4
	UINT32                                                  reserved230;	//0xC901BEF8
	UINT32                                                  reserved231;	//0xC901BEFC
	REG_SHY_4K_SHP_CORE_TMAP_STAT_00_T            shp_core_tmap_stat_00;	//0xC901BF00
	REG_SHY_4K_SHP_CORE_TMAP_STAT_01_T            shp_core_tmap_stat_01;	//0xC901BF04
	REG_SHY_4K_SHP_CORE_TMAP_STAT_02_T            shp_core_tmap_stat_02;	//0xC901BF08
	REG_SHY_4K_SHP_CORE_TMAP_STAT_03_T            shp_core_tmap_stat_03;	//0xC901BF0C
	REG_SHY_4K_SHP_CORE_TMAP_STAT_04_T            shp_core_tmap_stat_04;	//0xC901BF10
	REG_SHY_4K_SHP_CORE_TMAP_STAT_05_T            shp_core_tmap_stat_05;	//0xC901BF14
	REG_SHY_4K_SHP_CORE_TMAP_STAT_06_T            shp_core_tmap_stat_06;	//0xC901BF18
	REG_SHY_4K_SHP_CORE_TMAP_STAT_07_T            shp_core_tmap_stat_07;	//0xC901BF1C
	UINT32                                                  reserved232;	//0xC901BF20
	UINT32                                                  reserved233;	//0xC901BF24
	UINT32                                                  reserved234;	//0xC901BF28
	UINT32                                                  reserved235;	//0xC901BF2C
	UINT32                                                  reserved236;	//0xC901BF30
	UINT32                                                  reserved237;	//0xC901BF34
	UINT32                                                  reserved238;	//0xC901BF38
	UINT32                                                  reserved239;	//0xC901BF3C
	UINT32                                                  reserved240;	//0xC901BF40
	UINT32                                                  reserved241;	//0xC901BF44
	UINT32                                                  reserved242;	//0xC901BF48
	UINT32                                                  reserved243;	//0xC901BF4C
	UINT32                                                  reserved244;	//0xC901BF50
	UINT32                                                  reserved245;	//0xC901BF54
	UINT32                                                  reserved246;	//0xC901BF58
	UINT32                                                  reserved247;	//0xC901BF5C
	UINT32                                                  reserved248;	//0xC901BF60
	UINT32                                                  reserved249;	//0xC901BF64
	UINT32                                                  reserved250;	//0xC901BF68
	UINT32                                                  reserved251;	//0xC901BF6C
	UINT32                                                  reserved252;	//0xC901BF70
	UINT32                                                  reserved253;	//0xC901BF74
	UINT32                                                  reserved254;	//0xC901BF78
	UINT32                                                  reserved255;	//0xC901BF7C
	UINT32                                                  reserved256;	//0xC901BF80
	UINT32                                                  reserved257;	//0xC901BF84
	UINT32                                                  reserved258;	//0xC901BF88
	UINT32                                                  reserved259;	//0xC901BF8C
	UINT32                                                  reserved260;	//0xC901BF90
	UINT32                                                  reserved261;	//0xC901BF94
	UINT32                                                  reserved262;	//0xC901BF98
	UINT32                                                  reserved263;	//0xC901BF9C
	UINT32                                                  reserved264;	//0xC901BFA0
	UINT32                                                  reserved265;	//0xC901BFA4
	UINT32                                                  reserved266;	//0xC901BFA8
	UINT32                                                  reserved267;	//0xC901BFAC
	UINT32                                                  reserved268;	//0xC901BFB0
	UINT32                                                  reserved269;	//0xC901BFB4
	UINT32                                                  reserved270;	//0xC901BFB8
	UINT32                                                  reserved271;	//0xC901BFBC
	UINT32                                                  reserved272;	//0xC901BFC0
	UINT32                                                  reserved273;	//0xC901BFC4
	UINT32                                                  reserved274;	//0xC901BFC8
	UINT32                                                  reserved275;	//0xC901BFCC
	UINT32                                                  reserved276;	//0xC901BFD0
	UINT32                                                  reserved277;	//0xC901BFD4
	UINT32                                                  reserved278;	//0xC901BFD8
	UINT32                                                  reserved279;	//0xC901BFDC
	UINT32                                                  reserved280;	//0xC901BFE0
	UINT32                                                  reserved281;	//0xC901BFE4
	UINT32                                                  reserved282;	//0xC901BFE8
	UINT32                                                  reserved283;	//0xC901BFEC
	REG_SHY_4K_SHP_FSW_CTRL_00_T                        shp_fsw_ctrl_00;	//0xC901BFF0
	REG_SHY_4K_SHP_FSW_CTRL_01_T                        shp_fsw_ctrl_01;	//0xC901BFF4
	REG_SHY_4K_SHP_FSW_CTRL_02_T                        shp_fsw_ctrl_02;	//0xC901BFF8
	REG_SHY_4K_SHP_FSW_CTRL_03_T                        shp_fsw_ctrl_03;	//0xC901BFFC
}PE_SR_4K_SHP_REG_E60_T;

typedef struct {
	REG_SHY_2K_SHP_CORE_CTRL_00_T                      shp_core_ctrl_00;	//0xC901AF00
	REG_SHY_2K_SHP_CORE_CTRL_01_T                      shp_core_ctrl_01;	//0xC901AF04
	REG_SHY_2K_SHP_CORE_CTRL_02_T                      shp_core_ctrl_02;	//0xC901AF08
	REG_SHY_2K_SHP_CORE_CTRL_03_T                      shp_core_ctrl_03;	//0xC901AF0C
	UINT32                                                    reserved0;	//0xC901AF10
	UINT32                                                    reserved1;	//0xC901AF14
	UINT32                                                    reserved2;	//0xC901AF18
	UINT32                                                    reserved3;	//0xC901AF1C
	UINT32                                                    reserved4;	//0xC901AF20
	UINT32                                                    reserved5;	//0xC901AF24
	UINT32                                                    reserved6;	//0xC901AF28
	UINT32                                                    reserved7;	//0xC901AF2C
	UINT32                                                    reserved8;	//0xC901AF30
	UINT32                                                    reserved9;	//0xC901AF34
	UINT32                                                   reserved10;	//0xC901AF38
	UINT32                                                   reserved11;	//0xC901AF3C
	REG_SHY_2K_SHP_PAT_GEN_CTRL_00_T                shp_pat_gen_ctrl_00;	//0xC901AF40
	UINT32                                                   reserved12;	//0xC901AF44
	UINT32                                                   reserved13;	//0xC901AF48
	UINT32                                                   reserved14;	//0xC901AF4C
	UINT32                                                   reserved15;	//0xC901AF50
	UINT32                                                   reserved16;	//0xC901AF54
	UINT32                                                   reserved17;	//0xC901AF58
	UINT32                                                   reserved18;	//0xC901AF5C
	UINT32                                                   reserved19;	//0xC901AF60
	UINT32                                                   reserved20;	//0xC901AF64
	UINT32                                                   reserved21;	//0xC901AF68
	UINT32                                                   reserved22;	//0xC901AF6C
	UINT32                                                   reserved23;	//0xC901AF70
	UINT32                                                   reserved24;	//0xC901AF74
	UINT32                                                   reserved25;	//0xC901AF78
	UINT32                                                   reserved26;	//0xC901AF7C
	UINT32                                                   reserved27;	//0xC901AF80
	UINT32                                                   reserved28;	//0xC901AF84
	UINT32                                                   reserved29;	//0xC901AF88
	UINT32                                                   reserved30;	//0xC901AF8C
	UINT32                                                   reserved31;	//0xC901AF90
	UINT32                                                   reserved32;	//0xC901AF94
	UINT32                                                   reserved33;	//0xC901AF98
	UINT32                                                   reserved34;	//0xC901AF9C
	UINT32                                                   reserved35;	//0xC901AFA0
	UINT32                                                   reserved36;	//0xC901AFA4
	UINT32                                                   reserved37;	//0xC901AFA8
	UINT32                                                   reserved38;	//0xC901AFAC
	UINT32                                                   reserved39;	//0xC901AFB0
	UINT32                                                   reserved40;	//0xC901AFB4
	UINT32                                                   reserved41;	//0xC901AFB8
	UINT32                                                   reserved42;	//0xC901AFBC
	UINT32                                                   reserved43;	//0xC901AFC0
	UINT32                                                   reserved44;	//0xC901AFC4
	UINT32                                                   reserved45;	//0xC901AFC8
	UINT32                                                   reserved46;	//0xC901AFCC
	UINT32                                                   reserved47;	//0xC901AFD0
	UINT32                                                   reserved48;	//0xC901AFD4
	UINT32                                                   reserved49;	//0xC901AFD8
	UINT32                                                   reserved50;	//0xC901AFDC
	UINT32                                                   reserved51;	//0xC901AFE0
	UINT32                                                   reserved52;	//0xC901AFE4
	UINT32                                                   reserved53;	//0xC901AFE8
	UINT32                                                   reserved54;	//0xC901AFEC
	REG_SHY_2K_SHP_DP_CTRL_00_T                          shp_dp_ctrl_00;	//0xC901AFF0
	UINT32                                                   reserved55;	//0xC901AFF4
	UINT32                                                   reserved56;	//0xC901AFF8
	UINT32                                                   reserved57;	//0xC901AFFC
	REG_SHY_2K_SHP_FD_CTRL_00_T                          shp_fd_ctrl_00;	//0xC901B000
	REG_SHY_2K_SHP_FD_CTRL_01_T                          shp_fd_ctrl_01;	//0xC901B004
	REG_SHY_2K_SHP_FD_CTRL_02_T                          shp_fd_ctrl_02;	//0xC901B008
	REG_SHY_2K_SHP_FD_CTRL_03_T                          shp_fd_ctrl_03;	//0xC901B00C
	REG_SHY_2K_SHP_FD_CTRL_04_T                          shp_fd_ctrl_04;	//0xC901B010
	REG_SHY_2K_SHP_FD_CTRL_05_T                          shp_fd_ctrl_05;	//0xC901B014
	REG_SHY_2K_SHP_FD_CTRL_06_T                          shp_fd_ctrl_06;	//0xC901B018
	REG_SHY_2K_SHP_FD_CTRL_07_T                          shp_fd_ctrl_07;	//0xC901B01C
	REG_SHY_2K_SHP_FD_CTRL_08_T                          shp_fd_ctrl_08;	//0xC901B020
	REG_SHY_2K_SHP_FD_CTRL_09_T                          shp_fd_ctrl_09;	//0xC901B024
	REG_SHY_2K_SHP_FD_CTRL_0A_T                          shp_fd_ctrl_0a;	//0xC901B028
	REG_SHY_2K_SHP_FD_CTRL_0B_T                          shp_fd_ctrl_0b;	//0xC901B02C
	REG_SHY_2K_SHP_FD_CTRL_0C_T                          shp_fd_ctrl_0c;	//0xC901B030
	REG_SHY_2K_SHP_FD_CTRL_0D_T                          shp_fd_ctrl_0d;	//0xC901B034
	REG_SHY_2K_SHP_FD_CTRL_0E_T                          shp_fd_ctrl_0e;	//0xC901B038
	REG_SHY_2K_SHP_FD_CTRL_0F_T                          shp_fd_ctrl_0f;	//0xC901B03C
	REG_SHY_2K_SHP_FD_CTRL_10_T                          shp_fd_ctrl_10;	//0xC901B040
	REG_SHY_2K_SHP_FD_CTRL_11_T                          shp_fd_ctrl_11;	//0xC901B044
	REG_SHY_2K_SHP_FD_CTRL_12_T                          shp_fd_ctrl_12;	//0xC901B048
	REG_SHY_2K_SHP_FD_CTRL_13_T                          shp_fd_ctrl_13;	//0xC901B04C
	REG_SHY_2K_SHP_FD_CTRL_14_T                          shp_fd_ctrl_14;	//0xC901B050
	REG_SHY_2K_SHP_FD_CTRL_15_T                          shp_fd_ctrl_15;	//0xC901B054
	REG_SHY_2K_SHP_FD_CTRL_16_T                          shp_fd_ctrl_16;	//0xC901B058
	UINT32                                                   reserved58;	//0xC901B05C
	REG_SHY_2K_SHP_MP_CTRL_00_T                          shp_mp_ctrl_00;	//0xC901B060
	REG_SHY_2K_SHP_MP_CTRL_01_T                          shp_mp_ctrl_01;	//0xC901B064
	REG_SHY_2K_SHP_MP_CTRL_02_T                          shp_mp_ctrl_02;	//0xC901B068
	REG_SHY_2K_SHP_MP_CTRL_03_T                          shp_mp_ctrl_03;	//0xC901B06C
	REG_SHY_2K_SHP_MP_CTRL_04_T                          shp_mp_ctrl_04;	//0xC901B070
	REG_SHY_2K_SHP_MP_CTRL_05_T                          shp_mp_ctrl_05;	//0xC901B074
	REG_SHY_2K_SHP_MP_CTRL_06_T                          shp_mp_ctrl_06;	//0xC901B078
	REG_SHY_2K_SHP_MP_CTRL_07_T                          shp_mp_ctrl_07;	//0xC901B07C
	REG_SHY_2K_SHP_MP_CTRL_08_T                          shp_mp_ctrl_08;	//0xC901B080
	REG_SHY_2K_SHP_MP_CTRL_09_T                          shp_mp_ctrl_09;	//0xC901B084
	REG_SHY_2K_SHP_MP_CTRL_0A_T                          shp_mp_ctrl_0a;	//0xC901B088
	REG_SHY_2K_SHP_MP_CTRL_0B_T                          shp_mp_ctrl_0b;	//0xC901B08C
	REG_SHY_2K_SHP_MP_CTRL_0C_T                          shp_mp_ctrl_0c;	//0xC901B090
	REG_SHY_2K_SHP_APL_CTRL_00_T                        shp_apl_ctrl_00;	//0xC901B094
	UINT32                                                   reserved59;	//0xC901B098
	UINT32                                                   reserved60;	//0xC901B09C
	REG_SHY_2K_SHP_LC_CTRL_00_T                          shp_lc_ctrl_00;	//0xC901B0A0
	REG_SHY_2K_SHP_LC_CTRL_01_T                          shp_lc_ctrl_01;	//0xC901B0A4
	REG_SHY_2K_SHP_LC_CTRL_02_T                          shp_lc_ctrl_02;	//0xC901B0A8
	REG_SHY_2K_SHP_LC_CTRL_03_T                          shp_lc_ctrl_03;	//0xC901B0AC
	REG_SHY_2K_SHP_LC_CTRL_04_T                          shp_lc_ctrl_04;	//0xC901B0B0
	UINT32                                                   reserved61;	//0xC901B0B4
	UINT32                                                   reserved62;	//0xC901B0B8
	UINT32                                                   reserved63;	//0xC901B0BC
	REG_SHY_2K_SHP_DER_CTRL_00_T                        shp_der_ctrl_00;	//0xC901B0C0
	REG_SHY_2K_SHP_DER_CTRL_01_T                        shp_der_ctrl_01;	//0xC901B0C4
	REG_SHY_2K_SHP_DER_CTRL_02_T                        shp_der_ctrl_02;	//0xC901B0C8
	REG_SHY_2K_SHP_DER_CTRL_03_T                        shp_der_ctrl_03;	//0xC901B0CC
	REG_SHY_2K_SHP_DER_CTRL_04_T                        shp_der_ctrl_04;	//0xC901B0D0
	REG_SHY_2K_SHP_DER_CTRL_05_T                        shp_der_ctrl_05;	//0xC901B0D4
	REG_SHY_2K_SHP_DER_CTRL_06_T                        shp_der_ctrl_06;	//0xC901B0D8
	REG_SHY_2K_SHP_DER_CTRL_07_T                        shp_der_ctrl_07;	//0xC901B0DC
	REG_SHY_2K_SHP_SP_CTRL_00_T                          shp_sp_ctrl_00;	//0xC901B0E0
	REG_SHY_2K_SHP_SP_CTRL_01_T                          shp_sp_ctrl_01;	//0xC901B0E4
	REG_SHY_2K_SHP_SP_CTRL_02_T                          shp_sp_ctrl_02;	//0xC901B0E8
	REG_SHY_2K_SHP_SP_CTRL_03_T                          shp_sp_ctrl_03;	//0xC901B0EC
	REG_SHY_2K_SHP_SP_CTRL_04_T                          shp_sp_ctrl_04;	//0xC901B0F0
	REG_SHY_2K_SHP_SP_CTRL_05_T                          shp_sp_ctrl_05;	//0xC901B0F4
	REG_SHY_2K_SHP_SP_CTRL_06_T                          shp_sp_ctrl_06;	//0xC901B0F8
	REG_SHY_2K_SHP_SP_CTRL_07_T                          shp_sp_ctrl_07;	//0xC901B0FC
	REG_SHY_2K_SHP_SP_CTRL_08_T                          shp_sp_ctrl_08;	//0xC901B100
	REG_SHY_2K_SHP_SP_CTRL_09_T                          shp_sp_ctrl_09;	//0xC901B104
	REG_SHY_2K_SHP_SP_CTRL_0A_T                          shp_sp_ctrl_0a;	//0xC901B108
	REG_SHY_2K_SHP_SP_CTRL_0B_T                          shp_sp_ctrl_0b;	//0xC901B10C
	REG_SHY_2K_SHP_SP_CTRL_0C_T                          shp_sp_ctrl_0c;	//0xC901B110
	UINT32                                                   reserved64;	//0xC901B114
	UINT32                                                   reserved65;	//0xC901B118
	UINT32                                                   reserved66;	//0xC901B11C
	REG_SHY_2K_SHP_PTI_CTRL_00_T                        shp_pti_ctrl_00;	//0xC901B120
	REG_SHY_2K_SHP_PTI_CTRL_01_T                        shp_pti_ctrl_01;	//0xC901B124
	REG_SHY_2K_SHP_PTI_CTRL_02_T                        shp_pti_ctrl_02;	//0xC901B128
	REG_SHY_2K_SHP_PTI_CTRL_03_T                        shp_pti_ctrl_03;	//0xC901B12C
	REG_SHY_2K_SHP_STI_CTRL_00_T                        shp_sti_ctrl_00;	//0xC901B130
	UINT32                                                   reserved67;	//0xC901B134
	UINT32                                                   reserved68;	//0xC901B138
	UINT32                                                   reserved69;	//0xC901B13C
	REG_SHY_2K_SHP_TGEN_CTRL_00_T                      shp_tgen_ctrl_00;	//0xC901B140
	REG_SHY_2K_SHP_TGEN_CTRL_01_T                      shp_tgen_ctrl_01;	//0xC901B144
	REG_SHY_2K_SHP_TGEN_CTRL_02_T                      shp_tgen_ctrl_02;	//0xC901B148
	REG_SHY_2K_SHP_TGEN_CTRL_03_T                      shp_tgen_ctrl_03;	//0xC901B14C
	UINT32                                                   reserved70;	//0xC901B150
	REG_SHY_2K_SHP_TGEN_CTRL_04_T                      shp_tgen_ctrl_04;	//0xC901B154
	REG_SHY_2K_SHP_TGEN_CTRL_05_T                      shp_tgen_ctrl_05;	//0xC901B158
	REG_SHY_2K_SHP_TGEN_CTRL_06_T                      shp_tgen_ctrl_06;	//0xC901B15C
	REG_SHY_2K_SHP_TGEN_CTRL_07_T                      shp_tgen_ctrl_07;	//0xC901B160
	REG_SHY_2K_SHP_TGEN_CTRL_08_T                      shp_tgen_ctrl_08;	//0xC901B164
	REG_SHY_2K_SHP_TGEN_CTRL_09_T                      shp_tgen_ctrl_09;	//0xC901B168
	REG_SHY_2K_SHP_TGEN_CTRL_0A_T                      shp_tgen_ctrl_0a;	//0xC901B16C
	REG_SHY_2K_SHP_TGEN_CTRL_0B_T                      shp_tgen_ctrl_0b;	//0xC901B170
	REG_SHY_2K_SHP_SNR_CTRL_00_T                        shp_snr_ctrl_00;	//0xC901B174
	UINT32                                                   reserved71;	//0xC901B178
	UINT32                                                   reserved72;	//0xC901B17C
	REG_SHY_2K_SHP_DCTP_CTRL_00_T                      shp_dctp_ctrl_00;	//0xC901B180
	REG_SHY_2K_SHP_DCTP_CTRL_01_T                      shp_dctp_ctrl_01;	//0xC901B184
	REG_SHY_2K_SHP_DCTP_CTRL_02_T                      shp_dctp_ctrl_02;	//0xC901B188
	REG_SHY_2K_SHP_DCTP_CTRL_03_T                      shp_dctp_ctrl_03;	//0xC901B18C
	REG_SHY_2K_SHP_DCTP_CTRL_04_T                      shp_dctp_ctrl_04;	//0xC901B190
	REG_SHY_2K_SHP_DCTP_CTRL_05_T                      shp_dctp_ctrl_05;	//0xC901B194
	REG_SHY_2K_SHP_DCTP_CTRL_06_T                      shp_dctp_ctrl_06;	//0xC901B198
	REG_SHY_2K_SHP_DCTP_CTRL_07_T                      shp_dctp_ctrl_07;	//0xC901B19C
	REG_SHY_2K_SHP_DCTP_CTRL_08_T                      shp_dctp_ctrl_08;	//0xC901B1A0
	REG_SHY_2K_SHP_DCTP_CTRL_09_T                      shp_dctp_ctrl_09;	//0xC901B1A4
	REG_SHY_2K_SHP_DCTP_CTRL_0A_T                      shp_dctp_ctrl_0a;	//0xC901B1A8
	REG_SHY_2K_SHP_DCTP_CTRL_0B_T                      shp_dctp_ctrl_0b;	//0xC901B1AC
	REG_SHY_2K_SHP_DCTP_CTRL_0C_T                      shp_dctp_ctrl_0c;	//0xC901B1B0
	REG_SHY_2K_SHP_DCTP_CTRL_0D_T                      shp_dctp_ctrl_0d;	//0xC901B1B4
	REG_SHY_2K_SHP_DCTP_CTRL_0E_T                      shp_dctp_ctrl_0e;	//0xC901B1B8
	REG_SHY_2K_SHP_DCTP_CTRL_0F_T                      shp_dctp_ctrl_0f;	//0xC901B1BC
	REG_SHY_2K_SHP_DCTP_CTRL_10_T                      shp_dctp_ctrl_10;	//0xC901B1C0
	REG_SHY_2K_SHP_DCTP_CTRL_11_T                      shp_dctp_ctrl_11;	//0xC901B1C4
	REG_SHY_2K_SHP_DCTP_CTRL_12_T                      shp_dctp_ctrl_12;	//0xC901B1C8
	REG_SHY_2K_SHP_DCTP_CTRL_13_T                      shp_dctp_ctrl_13;	//0xC901B1CC
	REG_SHY_2K_SHP_DCTP_CTRL_14_T                      shp_dctp_ctrl_14;	//0xC901B1D0
	REG_SHY_2K_SHP_DCTP_CTRL_15_T                      shp_dctp_ctrl_15;	//0xC901B1D4
	REG_SHY_2K_SHP_DCTP_CTRL_16_T                      shp_dctp_ctrl_16;	//0xC901B1D8
	REG_SHY_2K_SHP_DCTP_CTRL_17_T                      shp_dctp_ctrl_17;	//0xC901B1DC
	REG_SHY_2K_SHP_DCTP_CTRL_18_T                      shp_dctp_ctrl_18;	//0xC901B1E0
	REG_SHY_2K_SHP_DCTP_CTRL_19_T                      shp_dctp_ctrl_19;	//0xC901B1E4
	REG_SHY_2K_SHP_DCTP_CTRL_1A_T                      shp_dctp_ctrl_1a;	//0xC901B1E8
	REG_SHY_2K_SHP_DCTP_CTRL_1B_T                      shp_dctp_ctrl_1b;	//0xC901B1EC
	REG_SHY_2K_SHP_DCTP_CTRL_1C_T                      shp_dctp_ctrl_1c;	//0xC901B1F0
	REG_SHY_2K_SHP_DCTP_CTRL_1D_T                      shp_dctp_ctrl_1d;	//0xC901B1F4
	REG_SHY_2K_SHP_DCTP_CTRL_1E_T                      shp_dctp_ctrl_1e;	//0xC901B1F8
	REG_SHY_2K_SHP_DCTP_CTRL_1F_T                      shp_dctp_ctrl_1f;	//0xC901B1FC
	REG_SHY_2K_SHP_NNTG_CTRL_00_T                      shp_nntg_ctrl_00;	//0xC901B200
	REG_SHY_2K_SHP_NNTG_CTRL_01_T                      shp_nntg_ctrl_01;	//0xC901B204
	REG_SHY_2K_SHP_NNTG_CTRL_02_T                      shp_nntg_ctrl_02;	//0xC901B208
	REG_SHY_2K_SHP_NNTG_CTRL_03_T                      shp_nntg_ctrl_03;	//0xC901B20C
	REG_SHY_2K_SHP_NNTG_CTRL_04_T                      shp_nntg_ctrl_04;	//0xC901B210
	REG_SHY_2K_SHP_NNTG_CTRL_05_T                      shp_nntg_ctrl_05;	//0xC901B214
	UINT32                                                   reserved73;	//0xC901B218
	UINT32                                                   reserved74;	//0xC901B21C
	UINT32                                                   reserved75;	//0xC901B220
	UINT32                                                   reserved76;	//0xC901B224
	UINT32                                                   reserved77;	//0xC901B228
	REG_SHY_2K_SHP_NNTG_CTRL_06_T                      shp_nntg_ctrl_06;	//0xC901B22C
	REG_SHY_2K_SHP_NNTG_CTRL_07_T                      shp_nntg_ctrl_07;	//0xC901B230
	REG_SHY_2K_SHP_NNTG_CTRL_08_T                      shp_nntg_ctrl_08;	//0xC901B234
	REG_SHY_2K_SHP_NNTG_CTRL_09_T                      shp_nntg_ctrl_09;	//0xC901B238
	REG_SHY_2K_SHP_NNTG_CTRL_0A_T                      shp_nntg_ctrl_0a;	//0xC901B23C
	REG_SHY_2K_SHP_NNTG_CTRL_0B_T                      shp_nntg_ctrl_0b;	//0xC901B240
	REG_SHY_2K_SHP_NNTG_CTRL_0C_T                      shp_nntg_ctrl_0c;	//0xC901B244
	REG_SHY_2K_SHP_NNTG_CTRL_0D_T                      shp_nntg_ctrl_0d;	//0xC901B248
	REG_SHY_2K_SHP_NNTG_CTRL_0E_T                      shp_nntg_ctrl_0e;	//0xC901B24C
	REG_SHY_2K_SHP_NNTG_CTRL_0F_T                      shp_nntg_ctrl_0f;	//0xC901B250
	REG_SHY_2K_SHP_NNTG_CTRL_10_T                      shp_nntg_ctrl_10;	//0xC901B254
	UINT32                                                   reserved78;	//0xC901B258
	UINT32                                                   reserved79;	//0xC901B25C
	REG_SHY_2K_SHP_DP_SUM_CTRL_00_T                  shp_dp_sum_ctrl_00;	//0xC901B260
	REG_SHY_2K_SHP_DP_SUM_CTRL_01_T                  shp_dp_sum_ctrl_01;	//0xC901B264
	REG_SHY_2K_SHP_DP_SUM_CTRL_02_T                  shp_dp_sum_ctrl_02;	//0xC901B268
	UINT32                                                   reserved80;	//0xC901B26C
	UINT32                                                   reserved81;	//0xC901B270
	UINT32                                                   reserved82;	//0xC901B274
	UINT32                                                   reserved83;	//0xC901B278
	UINT32                                                   reserved84;	//0xC901B27C
	UINT32                                                   reserved85;	//0xC901B280
	UINT32                                                   reserved86;	//0xC901B284
	UINT32                                                   reserved87;	//0xC901B288
	UINT32                                                   reserved88;	//0xC901B28C
	UINT32                                                   reserved89;	//0xC901B290
	UINT32                                                   reserved90;	//0xC901B294
	UINT32                                                   reserved91;	//0xC901B298
	UINT32                                                   reserved92;	//0xC901B29C
	REG_SHY_2K_SHP_DP_WIN_CTRL_00_T                  shp_dp_win_ctrl_00;	//0xC901B2A0
	REG_SHY_2K_SHP_DP_WIN_CTRL_01_T                  shp_dp_win_ctrl_01;	//0xC901B2A4
	REG_SHY_2K_SHP_DP_WIN_CTRL_02_T                  shp_dp_win_ctrl_02;	//0xC901B2A8
	REG_SHY_2K_SHP_DP_WIN_CTRL_03_T                  shp_dp_win_ctrl_03;	//0xC901B2AC
	REG_SHY_2K_SHP_DP_WIN_CTRL_04_T                  shp_dp_win_ctrl_04;	//0xC901B2B0
	UINT32                                                   reserved93;	//0xC901B2B4
	UINT32                                                   reserved94;	//0xC901B2B8
	UINT32                                                   reserved95;	//0xC901B2BC
	REG_SHY_2K_SHP_FD_REGION_TEXT_00_T            shp_fd_region_text_00;	//0xC901B2C0
	REG_SHY_2K_SHP_FD_REGION_TEXT_01_T            shp_fd_region_text_01;	//0xC901B2C4
	REG_SHY_2K_SHP_FD_REGION_TEXT_02_T            shp_fd_region_text_02;	//0xC901B2C8
	REG_SHY_2K_SHP_FD_TMAP_TEMP_00_T                shp_fd_tmap_temp_00;	//0xC901B2CC
	REG_SHY_2K_SHP_FD_TMAP_TEMP_01_T                shp_fd_tmap_temp_01;	//0xC901B2D0
	REG_SHY_2K_SHP_FD_TMAP_TEMP_02_T                shp_fd_tmap_temp_02;	//0xC901B2D4
	REG_SHY_2K_SHP_FD_TMAP_TEMP_03_T                shp_fd_tmap_temp_03;	//0xC901B2D8
	REG_SHY_2K_SHP_FD_TMAP_TEMP_04_T                shp_fd_tmap_temp_04;	//0xC901B2DC
	REG_SHY_2K_SHP_FD_TMAP_TEMP_05_T                shp_fd_tmap_temp_05;	//0xC901B2E0
	REG_SHY_2K_SHP_FD_TMAP_TEMP_06_T                shp_fd_tmap_temp_06;	//0xC901B2E4
	REG_SHY_2K_SHP_FD_TMAP_TEMP_07_T                shp_fd_tmap_temp_07;	//0xC901B2E8
	REG_SHY_2K_SHP_FD_TMAP_TEMP_08_T                shp_fd_tmap_temp_08;	//0xC901B2EC
	REG_SHY_2K_SHP_FD_TMAP_TEMP_09_T                shp_fd_tmap_temp_09;	//0xC901B2F0
	REG_SHY_2K_SHP_FD_TMAP_TEMP_0A_T                shp_fd_tmap_temp_0a;	//0xC901B2F4
	REG_SHY_2K_SHP_FD_TMAP_TEMP_0B_T                shp_fd_tmap_temp_0b;	//0xC901B2F8
	REG_SHY_2K_SHP_FD_TMAP_TEMP_0C_T                shp_fd_tmap_temp_0c;	//0xC901B2FC
	REG_SHY_2K_SHP_DJ_CTRL_00_T                          shp_dj_ctrl_00;	//0xC901B300
	REG_SHY_2K_SHP_DJ_CTRL_01_T                          shp_dj_ctrl_01;	//0xC901B304
	REG_SHY_2K_SHP_DJ_CTRL_02_T                          shp_dj_ctrl_02;	//0xC901B308
	REG_SHY_2K_SHP_DJ_CTRL_03_T                          shp_dj_ctrl_03;	//0xC901B30C
	REG_SHY_2K_SHP_DJ_CTRL_04_T                          shp_dj_ctrl_04;	//0xC901B310
	REG_SHY_2K_SHP_DJ_CTRL_05_T                          shp_dj_ctrl_05;	//0xC901B314
	REG_SHY_2K_SHP_DJ_CTRL_06_T                          shp_dj_ctrl_06;	//0xC901B318
	REG_SHY_2K_SHP_DJ_CTRL_07_T                          shp_dj_ctrl_07;	//0xC901B31C
	REG_SHY_2K_SHP_DJ_CTRL_08_T                          shp_dj_ctrl_08;	//0xC901B320
	REG_SHY_2K_SHP_DJ_CTRL_09_T                          shp_dj_ctrl_09;	//0xC901B324
	REG_SHY_2K_SHP_DJ_CTRL_0A_T                          shp_dj_ctrl_0a;	//0xC901B328
	REG_SHY_2K_SHP_DJ_CTRL_0B_T                          shp_dj_ctrl_0b;	//0xC901B32C
	REG_SHY_2K_SHP_DJ_CTRL_0C_T                          shp_dj_ctrl_0c;	//0xC901B330
	REG_SHY_2K_SHP_DJ_CTRL_0D_T                          shp_dj_ctrl_0d;	//0xC901B334
	REG_SHY_2K_SHP_DJ_CTRL_0E_T                          shp_dj_ctrl_0e;	//0xC901B338
	REG_SHY_2K_SHP_DJ_CTRL_0F_T                          shp_dj_ctrl_0f;	//0xC901B33C
	REG_SHY_2K_SHP_DJ_CTRL_10_T                          shp_dj_ctrl_10;	//0xC901B340
	REG_SHY_2K_SHP_DJ_CTRL_11_T                          shp_dj_ctrl_11;	//0xC901B344
	REG_SHY_2K_SHP_DJ_CTRL_12_T                          shp_dj_ctrl_12;	//0xC901B348
	REG_SHY_2K_SHP_DJ_CTRL_13_T                          shp_dj_ctrl_13;	//0xC901B34C
	REG_SHY_2K_SHP_DJ_CTRL_14_T                          shp_dj_ctrl_14;	//0xC901B350
	REG_SHY_2K_SHP_DJ_CTRL_15_T                          shp_dj_ctrl_15;	//0xC901B354
	REG_SHY_2K_SHP_DJ_CTRL_16_T                          shp_dj_ctrl_16;	//0xC901B358
	REG_SHY_2K_SHP_DJ_CTRL_17_T                          shp_dj_ctrl_17;	//0xC901B35C
	REG_SHY_2K_SHP_DJ_CTRL_18_T                          shp_dj_ctrl_18;	//0xC901B360
	REG_SHY_2K_SHP_DJ_CTRL_19_T                          shp_dj_ctrl_19;	//0xC901B364
	REG_SHY_2K_SHP_DJ_CTRL_1A_T                          shp_dj_ctrl_1a;	//0xC901B368
	REG_SHY_2K_SHP_DJ_CTRL_1B_T                          shp_dj_ctrl_1b;	//0xC901B36C
	REG_SHY_2K_SHP_DJ_CTRL_1C_T                          shp_dj_ctrl_1c;	//0xC901B370
	REG_SHY_2K_SHP_DJ_CTRL_1D_T                          shp_dj_ctrl_1d;	//0xC901B374
	REG_SHY_2K_SHP_DJ_CTRL_1E_T                          shp_dj_ctrl_1e;	//0xC901B378
	REG_SHY_2K_SHP_DJ_CTRL_1F_T                          shp_dj_ctrl_1f;	//0xC901B37C
	REG_SHY_2K_SHP_DJ_CTRL_20_T                          shp_dj_ctrl_20;	//0xC901B380
	UINT32                                                   reserved96;	//0xC901B384
	UINT32                                                   reserved97;	//0xC901B388
	UINT32                                                   reserved98;	//0xC901B38C
	REG_SHY_2K_SHP_DB_CTRL_00_T                          shp_db_ctrl_00;	//0xC901B390
	REG_SHY_2K_SHP_DB_CTRL_01_T                          shp_db_ctrl_01;	//0xC901B394
	UINT32                                                   reserved99;	//0xC901B398
	UINT32                                                  reserved100;	//0xC901B39C
	REG_SHY_2K_SHP_DJ_WIN_CTRL_00_T                  shp_dj_win_ctrl_00;	//0xC901B3A0
	REG_SHY_2K_SHP_DJ_WIN_CTRL_01_T                  shp_dj_win_ctrl_01;	//0xC901B3A4
	REG_SHY_2K_SHP_DJ_WIN_CTRL_02_T                  shp_dj_win_ctrl_02;	//0xC901B3A8
	REG_SHY_2K_SHP_DJ_WIN_CTRL_03_T                  shp_dj_win_ctrl_03;	//0xC901B3AC
	REG_SHY_2K_SHP_DJ_WIN_CTRL_04_T                  shp_dj_win_ctrl_04;	//0xC901B3B0
	UINT32                                                  reserved101;	//0xC901B3B4
	UINT32                                                  reserved102;	//0xC901B3B8
	UINT32                                                  reserved103;	//0xC901B3BC
	UINT32                                                  reserved104;	//0xC901B3C0
	UINT32                                                  reserved105;	//0xC901B3C4
	UINT32                                                  reserved106;	//0xC901B3C8
	UINT32                                                  reserved107;	//0xC901B3CC
	UINT32                                                  reserved108;	//0xC901B3D0
	UINT32                                                  reserved109;	//0xC901B3D4
	UINT32                                                  reserved110;	//0xC901B3D8
	UINT32                                                  reserved111;	//0xC901B3DC
	UINT32                                                  reserved112;	//0xC901B3E0
	UINT32                                                  reserved113;	//0xC901B3E4
	UINT32                                                  reserved114;	//0xC901B3E8
	UINT32                                                  reserved115;	//0xC901B3EC
	UINT32                                                  reserved116;	//0xC901B3F0
	UINT32                                                  reserved117;	//0xC901B3F4
	UINT32                                                  reserved118;	//0xC901B3F8
	UINT32                                                  reserved119;	//0xC901B3FC
	UINT32                                                  reserved120;	//0xC901B400
	UINT32                                                  reserved121;	//0xC901B404
	UINT32                                                  reserved122;	//0xC901B408
	UINT32                                                  reserved123;	//0xC901B40C
	UINT32                                                  reserved124;	//0xC901B410
	UINT32                                                  reserved125;	//0xC901B414
	UINT32                                                  reserved126;	//0xC901B418
	UINT32                                                  reserved127;	//0xC901B41C
	UINT32                                                  reserved128;	//0xC901B420
	UINT32                                                  reserved129;	//0xC901B424
	UINT32                                                  reserved130;	//0xC901B428
	UINT32                                                  reserved131;	//0xC901B42C
	UINT32                                                  reserved132;	//0xC901B430
	UINT32                                                  reserved133;	//0xC901B434
	UINT32                                                  reserved134;	//0xC901B438
	UINT32                                                  reserved135;	//0xC901B43C
	UINT32                                                  reserved136;	//0xC901B440
	UINT32                                                  reserved137;	//0xC901B444
	UINT32                                                  reserved138;	//0xC901B448
	UINT32                                                  reserved139;	//0xC901B44C
	UINT32                                                  reserved140;	//0xC901B450
	UINT32                                                  reserved141;	//0xC901B454
	UINT32                                                  reserved142;	//0xC901B458
	UINT32                                                  reserved143;	//0xC901B45C
	UINT32                                                  reserved144;	//0xC901B460
	UINT32                                                  reserved145;	//0xC901B464
	UINT32                                                  reserved146;	//0xC901B468
	UINT32                                                  reserved147;	//0xC901B46C
	UINT32                                                  reserved148;	//0xC901B470
	UINT32                                                  reserved149;	//0xC901B474
	UINT32                                                  reserved150;	//0xC901B478
	UINT32                                                  reserved151;	//0xC901B47C
	UINT32                                                  reserved152;	//0xC901B480
	UINT32                                                  reserved153;	//0xC901B484
	UINT32                                                  reserved154;	//0xC901B488
	UINT32                                                  reserved155;	//0xC901B48C
	UINT32                                                  reserved156;	//0xC901B490
	UINT32                                                  reserved157;	//0xC901B494
	UINT32                                                  reserved158;	//0xC901B498
	UINT32                                                  reserved159;	//0xC901B49C
	UINT32                                                  reserved160;	//0xC901B4A0
	UINT32                                                  reserved161;	//0xC901B4A4
	UINT32                                                  reserved162;	//0xC901B4A8
	UINT32                                                  reserved163;	//0xC901B4AC
	UINT32                                                  reserved164;	//0xC901B4B0
	UINT32                                                  reserved165;	//0xC901B4B4
	UINT32                                                  reserved166;	//0xC901B4B8
	UINT32                                                  reserved167;	//0xC901B4BC
	UINT32                                                  reserved168;	//0xC901B4C0
	UINT32                                                  reserved169;	//0xC901B4C4
	UINT32                                                  reserved170;	//0xC901B4C8
	UINT32                                                  reserved171;	//0xC901B4CC
	UINT32                                                  reserved172;	//0xC901B4D0
	UINT32                                                  reserved173;	//0xC901B4D4
	UINT32                                                  reserved174;	//0xC901B4D8
	UINT32                                                  reserved175;	//0xC901B4DC
	UINT32                                                  reserved176;	//0xC901B4E0
	UINT32                                                  reserved177;	//0xC901B4E4
	UINT32                                                  reserved178;	//0xC901B4E8
	UINT32                                                  reserved179;	//0xC901B4EC
	UINT32                                                  reserved180;	//0xC901B4F0
	UINT32                                                  reserved181;	//0xC901B4F4
	UINT32                                                  reserved182;	//0xC901B4F8
	UINT32                                                  reserved183;	//0xC901B4FC
	REG_SHY_2K_SHP_CORE_STAT_00_T                      shp_core_stat_00;	//0xC901B500
	REG_SHY_2K_SHP_CORE_STAT_01_T                      shp_core_stat_01;	//0xC901B504
	REG_SHY_2K_SHP_CORE_STAT_02_T                      shp_core_stat_02;	//0xC901B508
	REG_SHY_2K_SHP_CORE_STAT_03_T                      shp_core_stat_03;	//0xC901B50C
	REG_SHY_2K_SHP_CORE_STAT_04_T                      shp_core_stat_04;	//0xC901B510
	REG_SHY_2K_SHP_CORE_STAT_05_T                      shp_core_stat_05;	//0xC901B514
	UINT32                                                  reserved184;	//0xC901B518
	UINT32                                                  reserved185;	//0xC901B51C
	UINT32                                                  reserved186;	//0xC901B520
	UINT32                                                  reserved187;	//0xC901B524
	UINT32                                                  reserved188;	//0xC901B528
	UINT32                                                  reserved189;	//0xC901B52C
	UINT32                                                  reserved190;	//0xC901B530
	UINT32                                                  reserved191;	//0xC901B534
	UINT32                                                  reserved192;	//0xC901B538
	UINT32                                                  reserved193;	//0xC901B53C
	UINT32                                                  reserved194;	//0xC901B540
	UINT32                                                  reserved195;	//0xC901B544
	UINT32                                                  reserved196;	//0xC901B548
	UINT32                                                  reserved197;	//0xC901B54C
	UINT32                                                  reserved198;	//0xC901B550
	UINT32                                                  reserved199;	//0xC901B554
	UINT32                                                  reserved200;	//0xC901B558
	UINT32                                                  reserved201;	//0xC901B55C
	REG_SHY_2K_SHP_CORE_FD_STAT_00_T                shp_core_fd_stat_00;	//0xC901B560
	REG_SHY_2K_SHP_CORE_FD_STAT_01_T                shp_core_fd_stat_01;	//0xC901B564
	REG_SHY_2K_SHP_CORE_FD_STAT_02_T                shp_core_fd_stat_02;	//0xC901B568
	REG_SHY_2K_SHP_CORE_FD_STAT_03_T                shp_core_fd_stat_03;	//0xC901B56C
	UINT32                                                  reserved202;	//0xC901B570
	UINT32                                                  reserved203;	//0xC901B574
	UINT32                                                  reserved204;	//0xC901B578
	UINT32                                                  reserved205;	//0xC901B57C
	UINT32                                                  reserved206;	//0xC901B580
	UINT32                                                  reserved207;	//0xC901B584
	UINT32                                                  reserved208;	//0xC901B588
	UINT32                                                  reserved209;	//0xC901B58C
	UINT32                                                  reserved210;	//0xC901B590
	UINT32                                                  reserved211;	//0xC901B594
	UINT32                                                  reserved212;	//0xC901B598
	UINT32                                                  reserved213;	//0xC901B59C
	UINT32                                                  reserved214;	//0xC901B5A0
	UINT32                                                  reserved215;	//0xC901B5A4
	UINT32                                                  reserved216;	//0xC901B5A8
	UINT32                                                  reserved217;	//0xC901B5AC
	UINT32                                                  reserved218;	//0xC901B5B0
	UINT32                                                  reserved219;	//0xC901B5B4
	UINT32                                                  reserved220;	//0xC901B5B8
	UINT32                                                  reserved221;	//0xC901B5BC
	UINT32                                                  reserved222;	//0xC901B5C0
	UINT32                                                  reserved223;	//0xC901B5C4
	UINT32                                                  reserved224;	//0xC901B5C8
	UINT32                                                  reserved225;	//0xC901B5CC
	UINT32                                                  reserved226;	//0xC901B5D0
	UINT32                                                  reserved227;	//0xC901B5D4
	UINT32                                                  reserved228;	//0xC901B5D8
	UINT32                                                  reserved229;	//0xC901B5DC
	UINT32                                                  reserved230;	//0xC901B5E0
	UINT32                                                  reserved231;	//0xC901B5E4
	UINT32                                                  reserved232;	//0xC901B5E8
	UINT32                                                  reserved233;	//0xC901B5EC
	UINT32                                                  reserved234;	//0xC901B5F0
	UINT32                                                  reserved235;	//0xC901B5F4
	UINT32                                                  reserved236;	//0xC901B5F8
	UINT32                                                  reserved237;	//0xC901B5FC
	REG_SHY_2K_SHP_CORE_TMAP_STAT_00_T            shp_core_tmap_stat_00;	//0xC901B600
	REG_SHY_2K_SHP_CORE_TMAP_STAT_01_T            shp_core_tmap_stat_01;	//0xC901B604
	REG_SHY_2K_SHP_CORE_TMAP_STAT_02_T            shp_core_tmap_stat_02;	//0xC901B608
	REG_SHY_2K_SHP_CORE_TMAP_STAT_03_T            shp_core_tmap_stat_03;	//0xC901B60C
	REG_SHY_2K_SHP_CORE_TMAP_STAT_04_T            shp_core_tmap_stat_04;	//0xC901B610
	REG_SHY_2K_SHP_CORE_TMAP_STAT_05_T            shp_core_tmap_stat_05;	//0xC901B614
	REG_SHY_2K_SHP_CORE_TMAP_STAT_06_T            shp_core_tmap_stat_06;	//0xC901B618
	REG_SHY_2K_SHP_CORE_TMAP_STAT_07_T            shp_core_tmap_stat_07;	//0xC901B61C
	UINT32                                                  reserved238;	//0xC901B620
	UINT32                                                  reserved239;	//0xC901B624
	UINT32                                                  reserved240;	//0xC901B628
	UINT32                                                  reserved241;	//0xC901B62C
	UINT32                                                  reserved242;	//0xC901B630
	UINT32                                                  reserved243;	//0xC901B634
	UINT32                                                  reserved244;	//0xC901B638
	UINT32                                                  reserved245;	//0xC901B63C
	UINT32                                                  reserved246;	//0xC901B640
	UINT32                                                  reserved247;	//0xC901B644
	UINT32                                                  reserved248;	//0xC901B648
	UINT32                                                  reserved249;	//0xC901B64C
	UINT32                                                  reserved250;	//0xC901B650
	UINT32                                                  reserved251;	//0xC901B654
	UINT32                                                  reserved252;	//0xC901B658
	UINT32                                                  reserved253;	//0xC901B65C
	UINT32                                                  reserved254;	//0xC901B660
	UINT32                                                  reserved255;	//0xC901B664
	UINT32                                                  reserved256;	//0xC901B668
	UINT32                                                  reserved257;	//0xC901B66C
	UINT32                                                  reserved258;	//0xC901B670
	UINT32                                                  reserved259;	//0xC901B674
	UINT32                                                  reserved260;	//0xC901B678
	UINT32                                                  reserved261;	//0xC901B67C
	UINT32                                                  reserved262;	//0xC901B680
	UINT32                                                  reserved263;	//0xC901B684
	UINT32                                                  reserved264;	//0xC901B688
	UINT32                                                  reserved265;	//0xC901B68C
	UINT32                                                  reserved266;	//0xC901B690
	UINT32                                                  reserved267;	//0xC901B694
	UINT32                                                  reserved268;	//0xC901B698
	UINT32                                                  reserved269;	//0xC901B69C
	UINT32                                                  reserved270;	//0xC901B6A0
	UINT32                                                  reserved271;	//0xC901B6A4
	UINT32                                                  reserved272;	//0xC901B6A8
	UINT32                                                  reserved273;	//0xC901B6AC
	UINT32                                                  reserved274;	//0xC901B6B0
	UINT32                                                  reserved275;	//0xC901B6B4
	UINT32                                                  reserved276;	//0xC901B6B8
	UINT32                                                  reserved277;	//0xC901B6BC
	UINT32                                                  reserved278;	//0xC901B6C0
	UINT32                                                  reserved279;	//0xC901B6C4
	UINT32                                                  reserved280;	//0xC901B6C8
	UINT32                                                  reserved281;	//0xC901B6CC
	UINT32                                                  reserved282;	//0xC901B6D0
	UINT32                                                  reserved283;	//0xC901B6D4
	UINT32                                                  reserved284;	//0xC901B6D8
	UINT32                                                  reserved285;	//0xC901B6DC
	UINT32                                                  reserved286;	//0xC901B6E0
	UINT32                                                  reserved287;	//0xC901B6E4
	UINT32                                                  reserved288;	//0xC901B6E8
	UINT32                                                  reserved289;	//0xC901B6EC
	REG_SHY_2K_SHP_FSW_CTRL_00_T                        shp_fsw_ctrl_00;	//0xC901B6F0
	REG_SHY_2K_SHP_FSW_CTRL_01_T                        shp_fsw_ctrl_01;	//0xC901B6F4
	REG_SHY_2K_SHP_FSW_CTRL_02_T                        shp_fsw_ctrl_02;	//0xC901B6F8
	REG_SHY_2K_SHP_FSW_CTRL_03_T                        shp_fsw_ctrl_03;	//0xC901B6FC
}PE_SR_2K_SHP_REG_E60_T;

typedef struct {
	REG_MERG_SR_MERGE_CTRL_00_T                        sr_merge_ctrl_00;	//0xC901C900
	REG_MERG_SR_MERGE_CTRL_01_T                        sr_merge_ctrl_01;	//0xC901C904
	UINT32                                                    reserved0;	//0xC901C908
	UINT32                                                    reserved1;	//0xC901C90C
	REG_MERG_SR_MERGE_CORE0_CTRL_01_T            sr_merge_core0_ctrl_01;	//0xC901C910
	REG_MERG_SR_MERGE_CORE1_CTRL_01_T            sr_merge_core1_ctrl_01;	//0xC901C914
	REG_MERG_SR_MERGE_CORE2_CTRL_01_T            sr_merge_core2_ctrl_01;	//0xC901C918
	REG_MERG_SR_MERGE_CORE3_CTRL_01_T            sr_merge_core3_ctrl_01;	//0xC901C91C
	REG_MERG_SR_MERGE_CORE0_CTRL_02_T            sr_merge_core0_ctrl_02;	//0xC901C920
	REG_MERG_SR_MERGE_CORE0_CTRL_03_T            sr_merge_core0_ctrl_03;	//0xC901C924
	REG_MERG_SR_MERGE_CORE1_CTRL_02_T            sr_merge_core1_ctrl_02;	//0xC901C928
	REG_MERG_SR_MERGE_CORE1_CTRL_03_T            sr_merge_core1_ctrl_03;	//0xC901C92C
	REG_MERG_SR_MERGE_CORE2_CTRL_02_T            sr_merge_core2_ctrl_02;	//0xC901C930
	REG_MERG_SR_MERGE_CORE2_CTRL_03_T            sr_merge_core2_ctrl_03;	//0xC901C934
	REG_MERG_SR_MERGE_CORE3_CTRL_02_T            sr_merge_core3_ctrl_02;	//0xC901C938
	REG_MERG_SR_MERGE_CORE3_CTRL_03_T            sr_merge_core3_ctrl_03;	//0xC901C93C
	REG_MERG_SR_MERGE_UPS_SPLIT_CTRL_00_T    sr_merge_ups_split_ctrl_00;	//0xC901C940
	REG_MERG_SR_MERGE_UPS_SPLIT_CTRL_01_T    sr_merge_ups_split_ctrl_01;	//0xC901C944
	REG_MERG_SR_MERGE_UPS_SPLIT_CTRL_02_T    sr_merge_ups_split_ctrl_02;	//0xC901C948
	REG_MERG_SR_MERGE_UPS_SPLIT_CTRL_03_T    sr_merge_ups_split_ctrl_03;	//0xC901C94C
	REG_MERG_SR_MERGE_RES_SPLIT_CTRL_00_T    sr_merge_res_split_ctrl_00;	//0xC901C950
	REG_MERG_SR_MERGE_RES_SPLIT_CTRL_01_T    sr_merge_res_split_ctrl_01;	//0xC901C954
	REG_MERG_SR_MERGE_RES_SPLIT_CTRL_02_T    sr_merge_res_split_ctrl_02;	//0xC901C958
	REG_MERG_SR_MERGE_RES_SPLIT_CTRL_03_T    sr_merge_res_split_ctrl_03;	//0xC901C95C
	UINT32                                                    reserved2;	//0xC901C960
	UINT32                                                    reserved3;	//0xC901C964
	UINT32                                                    reserved4;	//0xC901C968
	UINT32                                                    reserved5;	//0xC901C96C
	UINT32                                                    reserved6;	//0xC901C970
	UINT32                                                    reserved7;	//0xC901C974
	UINT32                                                    reserved8;	//0xC901C978
	UINT32                                                    reserved9;	//0xC901C97C
	UINT32                                                   reserved10;	//0xC901C980
	UINT32                                                   reserved11;	//0xC901C984
	UINT32                                                   reserved12;	//0xC901C988
	UINT32                                                   reserved13;	//0xC901C98C
	UINT32                                                   reserved14;	//0xC901C990
	UINT32                                                   reserved15;	//0xC901C994
	UINT32                                                   reserved16;	//0xC901C998
	UINT32                                                   reserved17;	//0xC901C99C
	UINT32                                                   reserved18;	//0xC901C9A0
	UINT32                                                   reserved19;	//0xC901C9A4
	UINT32                                                   reserved20;	//0xC901C9A8
	UINT32                                                   reserved21;	//0xC901C9AC
	UINT32                                                   reserved22;	//0xC901C9B0
	UINT32                                                   reserved23;	//0xC901C9B4
	UINT32                                                   reserved24;	//0xC901C9B8
	UINT32                                                   reserved25;	//0xC901C9BC
	UINT32                                                   reserved26;	//0xC901C9C0
	UINT32                                                   reserved27;	//0xC901C9C4
	UINT32                                                   reserved28;	//0xC901C9C8
	UINT32                                                   reserved29;	//0xC901C9CC
	UINT32                                                   reserved30;	//0xC901C9D0
	UINT32                                                   reserved31;	//0xC901C9D4
	UINT32                                                   reserved32;	//0xC901C9D8
	UINT32                                                   reserved33;	//0xC901C9DC
	UINT32                                                   reserved34;	//0xC901C9E0
	UINT32                                                   reserved35;	//0xC901C9E4
	UINT32                                                   reserved36;	//0xC901C9E8
	UINT32                                                   reserved37;	//0xC901C9EC
	REG_MERG_SR_MERGE_MERGE_CTRL_00_T            sr_merge_merge_ctrl_00;	//0xC901C9F0
	REG_MERG_SR_MERGE_MERGE_CTRL_01_T            sr_merge_merge_ctrl_01;	//0xC901C9F4
	REG_MERG_SR_MERGE_MERGE_CTRL_02_T            sr_merge_merge_ctrl_02;	//0xC901C9F8
	REG_MERG_SR_MERGE_MERGE_CTRL_03_T            sr_merge_merge_ctrl_03;	//0xC901C9FC
	REG_MERG_SR_MERGE_SPATIAL_00_T                  sr_merge_spatial_00;	//0xC901CA00
	REG_MERG_SR_MERGE_SPATIAL_01_T                  sr_merge_spatial_01;	//0xC901CA04
	UINT32                                                   reserved38;	//0xC901CA08
	UINT32                                                   reserved39;	//0xC901CA0C
	REG_MERG_SR_MERGE_MMD_00_T                          sr_merge_mmd_00;	//0xC901CA10
	REG_MERG_SR_MERGE_MMD_01_T                          sr_merge_mmd_01;	//0xC901CA14
	REG_MERG_SR_MERGE_MMD_02_T                          sr_merge_mmd_02;	//0xC901CA18
	REG_MERG_SR_MERGE_MMD_03_T                          sr_merge_mmd_03;	//0xC901CA1C
	REG_MERG_SR_MERGE_MMD_04_T                          sr_merge_mmd_04;	//0xC901CA20
	REG_MERG_SR_MERGE_MMD_05_T                          sr_merge_mmd_05;	//0xC901CA24
	REG_MERG_SR_MERGE_MMD_06_T                          sr_merge_mmd_06;	//0xC901CA28
	UINT32                                                   reserved40;	//0xC901CA2C
	REG_MERG_SR_MERGE_SOBEL_00_T                      sr_merge_sobel_00;	//0xC901CA30
	REG_MERG_SR_MERGE_SOBEL_01_T                      sr_merge_sobel_01;	//0xC901CA34
	REG_MERG_SR_MERGE_SOBEL_02_T                      sr_merge_sobel_02;	//0xC901CA38
	UINT32                                                   reserved41;	//0xC901CA3C
	REG_MERG_SR_MERGE_NR_GAIN_00_T                  sr_merge_nr_gain_00;	//0xC901CA40
	REG_MERG_SR_MERGE_NR_GAIN_01_T                  sr_merge_nr_gain_01;	//0xC901CA44
	REG_MERG_SR_MERGE_NR_GAIN_02_T                  sr_merge_nr_gain_02;	//0xC901CA48
	UINT32                                                   reserved42;	//0xC901CA4C
	REG_MERG_SR_MERGE_BLEND_00_T                      sr_merge_blend_00;	//0xC901CA50
	REG_MERG_SR_MERGE_BLEND_01_T                      sr_merge_blend_01;	//0xC901CA54
	REG_MERG_SR_MERGE_BLEND_02_T                      sr_merge_blend_02;	//0xC901CA58
	REG_MERG_SR_MERGE_BLEND_03_T                      sr_merge_blend_03;	//0xC901CA5C
	REG_MERG_SR_MERGE_BLEND_04_T                      sr_merge_blend_04;	//0xC901CA60
	UINT32                                                   reserved43;	//0xC901CA64
	UINT32                                                   reserved44;	//0xC901CA68
	UINT32                                                   reserved45;	//0xC901CA6C
	UINT32                                                   reserved46;	//0xC901CA70
	UINT32                                                   reserved47;	//0xC901CA74
	UINT32                                                   reserved48;	//0xC901CA78
	UINT32                                                   reserved49;	//0xC901CA7C
	UINT32                                                   reserved50;	//0xC901CA80
	UINT32                                                   reserved51;	//0xC901CA84
	UINT32                                                   reserved52;	//0xC901CA88
	UINT32                                                   reserved53;	//0xC901CA8C
	UINT32                                                   reserved54;	//0xC901CA90
	UINT32                                                   reserved55;	//0xC901CA94
	UINT32                                                   reserved56;	//0xC901CA98
	UINT32                                                   reserved57;	//0xC901CA9C
	UINT32                                                   reserved58;	//0xC901CAA0
	UINT32                                                   reserved59;	//0xC901CAA4
	UINT32                                                   reserved60;	//0xC901CAA8
	UINT32                                                   reserved61;	//0xC901CAAC
	UINT32                                                   reserved62;	//0xC901CAB0
	UINT32                                                   reserved63;	//0xC901CAB4
	UINT32                                                   reserved64;	//0xC901CAB8
	UINT32                                                   reserved65;	//0xC901CABC
	UINT32                                                   reserved66;	//0xC901CAC0
	UINT32                                                   reserved67;	//0xC901CAC4
	UINT32                                                   reserved68;	//0xC901CAC8
	UINT32                                                   reserved69;	//0xC901CACC
	UINT32                                                   reserved70;	//0xC901CAD0
	UINT32                                                   reserved71;	//0xC901CAD4
	UINT32                                                   reserved72;	//0xC901CAD8
	UINT32                                                   reserved73;	//0xC901CADC
	UINT32                                                   reserved74;	//0xC901CAE0
	UINT32                                                   reserved75;	//0xC901CAE4
	UINT32                                                   reserved76;	//0xC901CAE8
	UINT32                                                   reserved77;	//0xC901CAEC
	UINT32                                                   reserved78;	//0xC901CAF0
	UINT32                                                   reserved79;	//0xC901CAF4
	UINT32                                                   reserved80;	//0xC901CAF8
	UINT32                                                   reserved81;	//0xC901CAFC
	REG_MERG_SR_MERGE_CORE_STAT_00_T              sr_merge_core_stat_00;	//0xC901CB00
	REG_MERG_SR_MERGE_CORE_STAT_01_T              sr_merge_core_stat_01;	//0xC901CB04
	REG_MERG_SR_MERGE_CORE_STAT_02_T              sr_merge_core_stat_02;	//0xC901CB08
	REG_MERG_SR_MERGE_CORE_STAT_03_T              sr_merge_core_stat_03;	//0xC901CB0C
	REG_MERG_SR_MERGE_CORE_STAT_04_T              sr_merge_core_stat_04;	//0xC901CB10
	REG_MERG_SR_MERGE_CORE_STAT_05_T              sr_merge_core_stat_05;	//0xC901CB14
	REG_MERG_SR_MERGE_CORE0_STAT_00_T            sr_merge_core0_stat_00;	//0xC901CB18
	REG_MERG_SR_MERGE_CORE0_STAT_01_T            sr_merge_core0_stat_01;	//0xC901CB1C
	REG_MERG_SR_MERGE_CORE0_STAT_02_T            sr_merge_core0_stat_02;	//0xC901CB20
	REG_MERG_SR_MERGE_CORE0_STAT_03_T            sr_merge_core0_stat_03;	//0xC901CB24
	REG_MERG_SR_MERGE_CORE0_STAT_04_T            sr_merge_core0_stat_04;	//0xC901CB28
	REG_MERG_SR_MERGE_CORE0_STAT_05_T            sr_merge_core0_stat_05;	//0xC901CB2C
	REG_MERG_SR_MERGE_CORE1_STAT_00_T            sr_merge_core1_stat_00;	//0xC901CB30
	REG_MERG_SR_MERGE_CORE1_STAT_01_T            sr_merge_core1_stat_01;	//0xC901CB34
	REG_MERG_SR_MERGE_CORE1_STAT_02_T            sr_merge_core1_stat_02;	//0xC901CB38
	REG_MERG_SR_MERGE_CORE1_STAT_03_T            sr_merge_core1_stat_03;	//0xC901CB3C
	REG_MERG_SR_MERGE_CORE1_STAT_04_T            sr_merge_core1_stat_04;	//0xC901CB40
	REG_MERG_SR_MERGE_CORE1_STAT_05_T            sr_merge_core1_stat_05;	//0xC901CB44
	REG_MERG_SR_MERGE_CORE2_STAT_00_T            sr_merge_core2_stat_00;	//0xC901CB48
	REG_MERG_SR_MERGE_CORE2_STAT_01_T            sr_merge_core2_stat_01;	//0xC901CB4C
	REG_MERG_SR_MERGE_CORE2_STAT_02_T            sr_merge_core2_stat_02;	//0xC901CB50
	REG_MERG_SR_MERGE_CORE2_STAT_03_T            sr_merge_core2_stat_03;	//0xC901CB54
	REG_MERG_SR_MERGE_CORE2_STAT_04_T            sr_merge_core2_stat_04;	//0xC901CB58
	REG_MERG_SR_MERGE_CORE2_STAT_05_T            sr_merge_core2_stat_05;	//0xC901CB5C
	REG_MERG_SR_MERGE_CORE3_STAT_00_T            sr_merge_core3_stat_00;	//0xC901CB60
	REG_MERG_SR_MERGE_CORE3_STAT_01_T            sr_merge_core3_stat_01;	//0xC901CB64
	REG_MERG_SR_MERGE_CORE3_STAT_02_T            sr_merge_core3_stat_02;	//0xC901CB68
	REG_MERG_SR_MERGE_CORE3_STAT_03_T            sr_merge_core3_stat_03;	//0xC901CB6C
	REG_MERG_SR_MERGE_CORE3_STAT_04_T            sr_merge_core3_stat_04;	//0xC901CB70
	REG_MERG_SR_MERGE_CORE3_STAT_05_T            sr_merge_core3_stat_05;	//0xC901CB74
	UINT32                                                   reserved82;	//0xC901CB78
	UINT32                                                   reserved83;	//0xC901CB7C
	UINT32                                                   reserved84;	//0xC901CB80
	UINT32                                                   reserved85;	//0xC901CB84
	UINT32                                                   reserved86;	//0xC901CB88
	UINT32                                                   reserved87;	//0xC901CB8C
	UINT32                                                   reserved88;	//0xC901CB90
	UINT32                                                   reserved89;	//0xC901CB94
	UINT32                                                   reserved90;	//0xC901CB98
	UINT32                                                   reserved91;	//0xC901CB9C
	UINT32                                                   reserved92;	//0xC901CBA0
	UINT32                                                   reserved93;	//0xC901CBA4
	UINT32                                                   reserved94;	//0xC901CBA8
	UINT32                                                   reserved95;	//0xC901CBAC
	UINT32                                                   reserved96;	//0xC901CBB0
	UINT32                                                   reserved97;	//0xC901CBB4
	UINT32                                                   reserved98;	//0xC901CBB8
	UINT32                                                   reserved99;	//0xC901CBBC
	UINT32                                                  reserved100;	//0xC901CBC0
	UINT32                                                  reserved101;	//0xC901CBC4
	UINT32                                                  reserved102;	//0xC901CBC8
	UINT32                                                  reserved103;	//0xC901CBCC
	UINT32                                                  reserved104;	//0xC901CBD0
	UINT32                                                  reserved105;	//0xC901CBD4
	UINT32                                                  reserved106;	//0xC901CBD8
	UINT32                                                  reserved107;	//0xC901CBDC
	UINT32                                                  reserved108;	//0xC901CBE0
	UINT32                                                  reserved109;	//0xC901CBE4
	UINT32                                                  reserved110;	//0xC901CBE8
	UINT32                                                  reserved111;	//0xC901CBEC
	UINT32                                                  reserved112;	//0xC901CBF0
	UINT32                                                  reserved113;	//0xC901CBF4
	UINT32                                                  reserved114;	//0xC901CBF8
	UINT32                                                  reserved115;	//0xC901CBFC
	REG_MERG_SR_MERGE_FSW_CTRL_00_T                sr_merge_fsw_ctrl_00;	//0xC901CC00
	REG_MERG_SR_MERGE_FSW_CTRL_01_T                sr_merge_fsw_ctrl_01;	//0xC901CC04
	REG_MERG_SR_MERGE_FSW_CTRL_02_T                sr_merge_fsw_ctrl_02;	//0xC901CC08
	REG_MERG_SR_MERGE_FSW_CTRL_03_T                sr_merge_fsw_ctrl_03;	//0xC901CC0C
}PE_SR_MERG_REG_E60_T;

#if 0
/*-----------------------------------------------------------------------------
                             0xc9009800L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_core_detour                :1 ,	// 4:4
	reg_top_core_bypass                :1 ,	// 5:5
	reserved02                         :6 ,	// reserved
	reg_top_mode_3d                    :1 ;	// 12:12
}PE_E60_SHP_CHR_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009804L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_E60_SHP_CHR_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009808L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_E60_SHP_CHR_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c00L shp_cdj_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_edf_en                     :1 ,	// 0:0
	reg_cdj_hv_filter_en               :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_cdj_edge_adaptive_en           :1 ,	// 3:3
	reg_cdj_line_variation_mode        :1 ,	// 4:4
	reg_cdj_l_type_protection          :1 ,	// 5:5
	reg_cdj_soft_en                    :1 ,	// 6:6
	reserved02                         :1 ,	// reserved
	reg_cdj_count_diff_th              :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_cdj_output_mux                 :3 ,	// 18:16
	reg_cdj_buffer_detour_en           :1 ,	// 19:19
	reg_cdj_center_blur_mode           :2 ,	// 21:20
	reg_cdj_n_avg_mode                 :1 ,	// 22:22
	reg_cdj_detour_en                  :1 ,	// 23:23
	reg_cdj_line_variation_diff_th     :8 ;	// 31:24
}PE_E60_SHP_CDJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c04L shp_cdj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_level_th                   :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_cdj_n_avg_gain                 :8 ;	// 23:16
}PE_E60_SHP_CDJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c08L shp_cdj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_g0_cnt_min                 :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_cdj_g0_mul                     :5 ;	// 12:8
}PE_E60_SHP_CDJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c0cL shp_cdj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_g1_protect_min             :8 ,	// 7:0
	reg_cdj_g1_mul                     :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_cdj_edge_min                   :8 ,	// 23:16
	reg_cdj_edge_mul                   :8 ;	// 31:24
}PE_E60_SHP_CDJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009c10L shp_cdj_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_dir_sel_c1                 :1 ,	// 0:0
	reg_cdj_dir_sel_c2                 :1 ,	// 1:1
	reg_cdj_dir_sel_c3                 :1 ,	// 2:2
	reg_cdj_dir_sel_c4                 :1 ;	// 3:3
}PE_E60_SHP_CDJ_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009c14L shp_cdj_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_0_00              :2 ,	// 1:0
	reg_cdj_pattern0_0_01              :2 ,	// 3:2
	reg_cdj_pattern0_0_02              :2 ,	// 5:4
	reg_cdj_pattern0_0_03              :2 ,	// 7:6
	reg_cdj_pattern0_0_04              :2 ,	// 9:8
	reg_cdj_pattern0_0_05              :2 ,	// 11:10
	reg_cdj_pattern0_0_06              :2 ,	// 13:12
	reg_cdj_pattern0_0_07              :2 ,	// 15:14
	reg_cdj_pattern0_0_08              :2 ,	// 17:16
	reg_cdj_pattern0_0_09              :2 ,	// 19:18
	reg_cdj_pattern0_0_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009c18L shp_cdj_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_1_00              :2 ,	// 1:0
	reg_cdj_pattern0_1_01              :2 ,	// 3:2
	reg_cdj_pattern0_1_02              :2 ,	// 5:4
	reg_cdj_pattern0_1_03              :2 ,	// 7:6
	reg_cdj_pattern0_1_04              :2 ,	// 9:8
	reg_cdj_pattern0_1_05              :2 ,	// 11:10
	reg_cdj_pattern0_1_06              :2 ,	// 13:12
	reg_cdj_pattern0_1_07              :2 ,	// 15:14
	reg_cdj_pattern0_1_08              :2 ,	// 17:16
	reg_cdj_pattern0_1_09              :2 ,	// 19:18
	reg_cdj_pattern0_1_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9009c1cL shp_cdj_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_2_00              :2 ,	// 1:0
	reg_cdj_pattern0_2_01              :2 ,	// 3:2
	reg_cdj_pattern0_2_02              :2 ,	// 5:4
	reg_cdj_pattern0_2_03              :2 ,	// 7:6
	reg_cdj_pattern0_2_04              :2 ,	// 9:8
	reg_cdj_pattern0_2_05              :2 ,	// 11:10
	reg_cdj_pattern0_2_06              :2 ,	// 13:12
	reg_cdj_pattern0_2_07              :2 ,	// 15:14
	reg_cdj_pattern0_2_08              :2 ,	// 17:16
	reg_cdj_pattern0_2_09              :2 ,	// 19:18
	reg_cdj_pattern0_2_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9009c20L shp_cdj_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_3_00              :2 ,	// 1:0
	reg_cdj_pattern0_3_01              :2 ,	// 3:2
	reg_cdj_pattern0_3_02              :2 ,	// 5:4
	reg_cdj_pattern0_3_03              :2 ,	// 7:6
	reg_cdj_pattern0_3_04              :2 ,	// 9:8
	reg_cdj_pattern0_3_05              :2 ,	// 11:10
	reg_cdj_pattern0_3_06              :2 ,	// 13:12
	reg_cdj_pattern0_3_07              :2 ,	// 15:14
	reg_cdj_pattern0_3_08              :2 ,	// 17:16
	reg_cdj_pattern0_3_09              :2 ,	// 19:18
	reg_cdj_pattern0_3_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9009c24L shp_cdj_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_4_00              :2 ,	// 1:0
	reg_cdj_pattern0_4_01              :2 ,	// 3:2
	reg_cdj_pattern0_4_02              :2 ,	// 5:4
	reg_cdj_pattern0_4_03              :2 ,	// 7:6
	reg_cdj_pattern0_4_04              :2 ,	// 9:8
	reg_cdj_pattern0_4_05              :2 ,	// 11:10
	reg_cdj_pattern0_4_06              :2 ,	// 13:12
	reg_cdj_pattern0_4_07              :2 ,	// 15:14
	reg_cdj_pattern0_4_08              :2 ,	// 17:16
	reg_cdj_pattern0_4_09              :2 ,	// 19:18
	reg_cdj_pattern0_4_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9009c28L shp_cdj_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_5_00              :2 ,	// 1:0
	reg_cdj_pattern0_5_01              :2 ,	// 3:2
	reg_cdj_pattern0_5_02              :2 ,	// 5:4
	reg_cdj_pattern0_5_03              :2 ,	// 7:6
	reg_cdj_pattern0_5_04              :2 ,	// 9:8
	reg_cdj_pattern0_5_05              :2 ,	// 11:10
	reg_cdj_pattern0_5_06              :2 ,	// 13:12
	reg_cdj_pattern0_5_07              :2 ,	// 15:14
	reg_cdj_pattern0_5_08              :2 ,	// 17:16
	reg_cdj_pattern0_5_09              :2 ,	// 19:18
	reg_cdj_pattern0_5_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9009c2cL shp_cdj_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_6_00              :2 ,	// 1:0
	reg_cdj_pattern0_6_01              :2 ,	// 3:2
	reg_cdj_pattern0_6_02              :2 ,	// 5:4
	reg_cdj_pattern0_6_03              :2 ,	// 7:6
	reg_cdj_pattern0_6_04              :2 ,	// 9:8
	reg_cdj_pattern0_6_05              :2 ,	// 11:10
	reg_cdj_pattern0_6_06              :2 ,	// 13:12
	reg_cdj_pattern0_6_07              :2 ,	// 15:14
	reg_cdj_pattern0_6_08              :2 ,	// 17:16
	reg_cdj_pattern0_6_09              :2 ,	// 19:18
	reg_cdj_pattern0_6_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9009c30L shp_cdj_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern0_flip0_h           :1 ,	// 0:0
	reg_cdj_pattern0_flip0_v           :1 ,	// 1:1
	reg_cdj_pattern0_flip1_h           :1 ,	// 2:2
	reg_cdj_pattern0_flip1_v           :1 ,	// 3:3
	reg_cdj_pattern0_flip2_h           :1 ,	// 4:4
	reg_cdj_pattern0_flip2_v           :1 ,	// 5:5
	reg_cdj_pattern0_flip3_h           :1 ,	// 6:6
	reg_cdj_pattern0_flip3_v           :1 ;	// 7:7
}PE_E60_SHP_CDJ_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9009c34L shp_cdj_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_0_00              :2 ,	// 1:0
	reg_cdj_pattern1_0_01              :2 ,	// 3:2
	reg_cdj_pattern1_0_02              :2 ,	// 5:4
	reg_cdj_pattern1_0_03              :2 ,	// 7:6
	reg_cdj_pattern1_0_04              :2 ,	// 9:8
	reg_cdj_pattern1_0_05              :2 ,	// 11:10
	reg_cdj_pattern1_0_06              :2 ,	// 13:12
	reg_cdj_pattern1_0_07              :2 ,	// 15:14
	reg_cdj_pattern1_0_08              :2 ,	// 17:16
	reg_cdj_pattern1_0_09              :2 ,	// 19:18
	reg_cdj_pattern1_0_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9009c38L shp_cdj_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_1_00              :2 ,	// 1:0
	reg_cdj_pattern1_1_01              :2 ,	// 3:2
	reg_cdj_pattern1_1_02              :2 ,	// 5:4
	reg_cdj_pattern1_1_03              :2 ,	// 7:6
	reg_cdj_pattern1_1_04              :2 ,	// 9:8
	reg_cdj_pattern1_1_05              :2 ,	// 11:10
	reg_cdj_pattern1_1_06              :2 ,	// 13:12
	reg_cdj_pattern1_1_07              :2 ,	// 15:14
	reg_cdj_pattern1_1_08              :2 ,	// 17:16
	reg_cdj_pattern1_1_09              :2 ,	// 19:18
	reg_cdj_pattern1_1_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc9009c3cL shp_cdj_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_2_00              :2 ,	// 1:0
	reg_cdj_pattern1_2_01              :2 ,	// 3:2
	reg_cdj_pattern1_2_02              :2 ,	// 5:4
	reg_cdj_pattern1_2_03              :2 ,	// 7:6
	reg_cdj_pattern1_2_04              :2 ,	// 9:8
	reg_cdj_pattern1_2_05              :2 ,	// 11:10
	reg_cdj_pattern1_2_06              :2 ,	// 13:12
	reg_cdj_pattern1_2_07              :2 ,	// 15:14
	reg_cdj_pattern1_2_08              :2 ,	// 17:16
	reg_cdj_pattern1_2_09              :2 ,	// 19:18
	reg_cdj_pattern1_2_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9009c40L shp_cdj_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_3_00              :2 ,	// 1:0
	reg_cdj_pattern1_3_01              :2 ,	// 3:2
	reg_cdj_pattern1_3_02              :2 ,	// 5:4
	reg_cdj_pattern1_3_03              :2 ,	// 7:6
	reg_cdj_pattern1_3_04              :2 ,	// 9:8
	reg_cdj_pattern1_3_05              :2 ,	// 11:10
	reg_cdj_pattern1_3_06              :2 ,	// 13:12
	reg_cdj_pattern1_3_07              :2 ,	// 15:14
	reg_cdj_pattern1_3_08              :2 ,	// 17:16
	reg_cdj_pattern1_3_09              :2 ,	// 19:18
	reg_cdj_pattern1_3_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9009c44L shp_cdj_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_4_00              :2 ,	// 1:0
	reg_cdj_pattern1_4_01              :2 ,	// 3:2
	reg_cdj_pattern1_4_02              :2 ,	// 5:4
	reg_cdj_pattern1_4_03              :2 ,	// 7:6
	reg_cdj_pattern1_4_04              :2 ,	// 9:8
	reg_cdj_pattern1_4_05              :2 ,	// 11:10
	reg_cdj_pattern1_4_06              :2 ,	// 13:12
	reg_cdj_pattern1_4_07              :2 ,	// 15:14
	reg_cdj_pattern1_4_08              :2 ,	// 17:16
	reg_cdj_pattern1_4_09              :2 ,	// 19:18
	reg_cdj_pattern1_4_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9009c48L shp_cdj_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_5_00              :2 ,	// 1:0
	reg_cdj_pattern1_5_01              :2 ,	// 3:2
	reg_cdj_pattern1_5_02              :2 ,	// 5:4
	reg_cdj_pattern1_5_03              :2 ,	// 7:6
	reg_cdj_pattern1_5_04              :2 ,	// 9:8
	reg_cdj_pattern1_5_05              :2 ,	// 11:10
	reg_cdj_pattern1_5_06              :2 ,	// 13:12
	reg_cdj_pattern1_5_07              :2 ,	// 15:14
	reg_cdj_pattern1_5_08              :2 ,	// 17:16
	reg_cdj_pattern1_5_09              :2 ,	// 19:18
	reg_cdj_pattern1_5_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9009c4cL shp_cdj_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_6_00              :2 ,	// 1:0
	reg_cdj_pattern1_6_01              :2 ,	// 3:2
	reg_cdj_pattern1_6_02              :2 ,	// 5:4
	reg_cdj_pattern1_6_03              :2 ,	// 7:6
	reg_cdj_pattern1_6_04              :2 ,	// 9:8
	reg_cdj_pattern1_6_05              :2 ,	// 11:10
	reg_cdj_pattern1_6_06              :2 ,	// 13:12
	reg_cdj_pattern1_6_07              :2 ,	// 15:14
	reg_cdj_pattern1_6_08              :2 ,	// 17:16
	reg_cdj_pattern1_6_09              :2 ,	// 19:18
	reg_cdj_pattern1_6_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9009c50L shp_cdj_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern1_flip0_h           :1 ,	// 0:0
	reg_cdj_pattern1_flip0_v           :1 ,	// 1:1
	reg_cdj_pattern1_flip1_h           :1 ,	// 2:2
	reg_cdj_pattern1_flip1_v           :1 ;	// 3:3
}PE_E60_SHP_CDJ_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9009c54L shp_cdj_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_0_00              :2 ,	// 1:0
	reg_cdj_pattern2_0_01              :2 ,	// 3:2
	reg_cdj_pattern2_0_02              :2 ,	// 5:4
	reg_cdj_pattern2_0_03              :2 ,	// 7:6
	reg_cdj_pattern2_0_04              :2 ,	// 9:8
	reg_cdj_pattern2_0_05              :2 ,	// 11:10
	reg_cdj_pattern2_0_06              :2 ,	// 13:12
	reg_cdj_pattern2_0_07              :2 ,	// 15:14
	reg_cdj_pattern2_0_08              :2 ,	// 17:16
	reg_cdj_pattern2_0_09              :2 ,	// 19:18
	reg_cdj_pattern2_0_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9009c58L shp_cdj_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_1_00              :2 ,	// 1:0
	reg_cdj_pattern2_1_01              :2 ,	// 3:2
	reg_cdj_pattern2_1_02              :2 ,	// 5:4
	reg_cdj_pattern2_1_03              :2 ,	// 7:6
	reg_cdj_pattern2_1_04              :2 ,	// 9:8
	reg_cdj_pattern2_1_05              :2 ,	// 11:10
	reg_cdj_pattern2_1_06              :2 ,	// 13:12
	reg_cdj_pattern2_1_07              :2 ,	// 15:14
	reg_cdj_pattern2_1_08              :2 ,	// 17:16
	reg_cdj_pattern2_1_09              :2 ,	// 19:18
	reg_cdj_pattern2_1_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9009c5cL shp_cdj_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_2_00              :2 ,	// 1:0
	reg_cdj_pattern2_2_01              :2 ,	// 3:2
	reg_cdj_pattern2_2_02              :2 ,	// 5:4
	reg_cdj_pattern2_2_03              :2 ,	// 7:6
	reg_cdj_pattern2_2_04              :2 ,	// 9:8
	reg_cdj_pattern2_2_05              :2 ,	// 11:10
	reg_cdj_pattern2_2_06              :2 ,	// 13:12
	reg_cdj_pattern2_2_07              :2 ,	// 15:14
	reg_cdj_pattern2_2_08              :2 ,	// 17:16
	reg_cdj_pattern2_2_09              :2 ,	// 19:18
	reg_cdj_pattern2_2_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9009c60L shp_cdj_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_3_00              :2 ,	// 1:0
	reg_cdj_pattern2_3_01              :2 ,	// 3:2
	reg_cdj_pattern2_3_02              :2 ,	// 5:4
	reg_cdj_pattern2_3_03              :2 ,	// 7:6
	reg_cdj_pattern2_3_04              :2 ,	// 9:8
	reg_cdj_pattern2_3_05              :2 ,	// 11:10
	reg_cdj_pattern2_3_06              :2 ,	// 13:12
	reg_cdj_pattern2_3_07              :2 ,	// 15:14
	reg_cdj_pattern2_3_08              :2 ,	// 17:16
	reg_cdj_pattern2_3_09              :2 ,	// 19:18
	reg_cdj_pattern2_3_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9009c64L shp_cdj_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_4_00              :2 ,	// 1:0
	reg_cdj_pattern2_4_01              :2 ,	// 3:2
	reg_cdj_pattern2_4_02              :2 ,	// 5:4
	reg_cdj_pattern2_4_03              :2 ,	// 7:6
	reg_cdj_pattern2_4_04              :2 ,	// 9:8
	reg_cdj_pattern2_4_05              :2 ,	// 11:10
	reg_cdj_pattern2_4_06              :2 ,	// 13:12
	reg_cdj_pattern2_4_07              :2 ,	// 15:14
	reg_cdj_pattern2_4_08              :2 ,	// 17:16
	reg_cdj_pattern2_4_09              :2 ,	// 19:18
	reg_cdj_pattern2_4_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9009c68L shp_cdj_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_5_00              :2 ,	// 1:0
	reg_cdj_pattern2_5_01              :2 ,	// 3:2
	reg_cdj_pattern2_5_02              :2 ,	// 5:4
	reg_cdj_pattern2_5_03              :2 ,	// 7:6
	reg_cdj_pattern2_5_04              :2 ,	// 9:8
	reg_cdj_pattern2_5_05              :2 ,	// 11:10
	reg_cdj_pattern2_5_06              :2 ,	// 13:12
	reg_cdj_pattern2_5_07              :2 ,	// 15:14
	reg_cdj_pattern2_5_08              :2 ,	// 17:16
	reg_cdj_pattern2_5_09              :2 ,	// 19:18
	reg_cdj_pattern2_5_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc9009c6cL shp_cdj_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_6_00              :2 ,	// 1:0
	reg_cdj_pattern2_6_01              :2 ,	// 3:2
	reg_cdj_pattern2_6_02              :2 ,	// 5:4
	reg_cdj_pattern2_6_03              :2 ,	// 7:6
	reg_cdj_pattern2_6_04              :2 ,	// 9:8
	reg_cdj_pattern2_6_05              :2 ,	// 11:10
	reg_cdj_pattern2_6_06              :2 ,	// 13:12
	reg_cdj_pattern2_6_07              :2 ,	// 15:14
	reg_cdj_pattern2_6_08              :2 ,	// 17:16
	reg_cdj_pattern2_6_09              :2 ,	// 19:18
	reg_cdj_pattern2_6_10              :2 ;	// 21:20
}PE_E60_SHP_CDJ_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc9009c70L shp_cdj_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_pattern2_flip0_h           :1 ,	// 0:0
	reg_cdj_pattern2_flip0_v           :1 ,	// 1:1
	reg_cdj_pattern2_flip1_h           :1 ,	// 2:2
	reg_cdj_pattern2_flip1_v           :1 ;	// 3:3
}PE_E60_SHP_CDJ_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc9009c74L shp_cdj_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_g0_mul                :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_cdj_soft_g0_offset             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_cdj_soft_g0_max                :8 ;	// 23:16
}PE_E60_SHP_CDJ_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc9009c78L shp_cdj_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_g1_mul                :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_cdj_soft_g1_offset             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_cdj_soft_g1_max                :8 ;	// 23:16
}PE_E60_SHP_CDJ_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc9009c7cL shp_cdj_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_g2_mul                :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_cdj_soft_g2_offset             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_cdj_soft_g2_max                :8 ;	// 23:16
}PE_E60_SHP_CDJ_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9009c80L shp_cdj_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdj_soft_base                  :8 ,	// 7:0
	reg_cdj_soft_sel_1357_gain         :8 ,	// 15:8
	reg_cdj_soft_single_match_en       :1 ;	// 16:16
}PE_E60_SHP_CDJ_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9009c90L shp_cdir_blur_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdir_blur_detour               :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_cdir_blur_buf_detour           :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_cdir_blur_en                   :1 ;	// 8:8
}PE_E60_SHP_CDIR_BLUR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c94L shp_cdir_blur_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdir_blur_base                 :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_cdir_blur_gain                 :8 ;	// 23:16
}PE_E60_SHP_CDIR_BLUR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca0L shp_cdj_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win0_en                :1 ,	// 0:0
	reg_win_cdj_win1_en                :1 ,	// 1:1
	reg_win_cdj_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_cdj_win_outside            :1 ,	// 6:6
	reg_win_cdj_win_en                 :1 ,	// 7:7
	reg_win_cdj_bdr_alpha              :5 ,	// 12:8
	reg_win_cdj_bdr_wid                :2 ,	// 14:13
	reg_win_cdj_bdr_en                 :1 ,	// 15:15
	reg_win_cdj_cr5                    :5 ,	// 20:16
	reg_win_cdj_cb5                    :5 ,	// 25:21
	reg_win_cdj_yy6                    :6 ;	// 31:26
}PE_E60_SHP_CDJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca4L shp_cdj_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w0_y0              :12;	// 27:16
}PE_E60_SHP_CDJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca8L shp_cdj_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w0_y1              :12;	// 27:16
}PE_E60_SHP_CDJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009cacL shp_cdj_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w1_y0              :12;	// 27:16
}PE_E60_SHP_CDJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009cb0L shp_cdj_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_cdj_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_cdj_win_w1_y1              :12;	// 27:16
}PE_E60_SHP_CDJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009e00L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_E60_SHP_CHR_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009e04L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_E60_SHP_CHR_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009e08L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_E60_SHP_CHR_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009e0cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_E60_SHP_CHR_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009e10L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_E60_SHP_CHR_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009e14L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_E60_SHP_CHR_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_CHR_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_CHR_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009ef8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_CHR_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009efcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_CHR_FSW_CTRL_03_T;


/*-----------------------------------------------------------------------------
                             0xc9008700L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_core_detour                :1 ,	// 4:4
	reg_top_core_bypass                :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_top_protocol_type              :1 ,	// 8:8
	reserved03                         :3 ,	// reserved
	reg_top_mode_3d                    :1 ;	// 12:12
}PE_E60_SHP_2K_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008704L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_E60_SHP_2K_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008708L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_E60_SHP_2K_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900870cL shp_core_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_prefetch_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_flush_cnt                  :12;	// 27:16
}PE_E60_SHP_2K_CORE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008740L shp_pat_gen_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pat_en                         :1 ,	// 0:0
	reg_pat_thickness                  :2 ,	// 2:1
	reserved01                         :5 ,	// reserved
	reg_pat_pix_val_yy                 :8 ;	// 15:8
}PE_E60_SHP_2K_PAT_GEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90087f0L shp_dp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_debug_display               :4 ,	// 3:0
	reg_dp_detour_en                   :1 ,	// 4:4
	reserved01                         :3 ,	// reserved
	reg_dp_buffer_detour_en            :1 ;	// 8:8
}PE_E60_SHP_2K_DP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008800L shp_fd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_map_h_size                :2 ,	// 1:0
	reg_fd_a_nomalize_en               :1 ,	// 2:2
	reg_fd_t_nomalize_en               :1 ,	// 3:3
	reg_fd_t_cut_resolution            :2 ,	// 5:4
	reserved01                         :2 ,	// reserved
	reg_fd_a_map_post_filter_en        :1 ,	// 8:8
	reg_fd_t_cross_check               :1 ,	// 9:9
	reserved02                         :6 ,	// reserved
	reg_fd_pre_a_map_h_size            :3 ,	// 18:16
	reg_fd_pre_a_map_v_size            :2 ,	// 20:19
	reg_fd_pre_a_cut_resolution        :3 ,	// 23:21
	reg_fd_cross_th                    :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008804L shp_fd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mul_base_t                  :8 ,	// 7:0
	reg_fd_mul_base_e                  :8 ;	// 15:8
}PE_E60_SHP_2K_FD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008808L shp_fd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_beta_mul             :8 ,	// 7:0
	reg_fd_detail_alpha_mul            :8 ,	// 15:8
	reg_fd_edge_beta_mul               :8 ,	// 23:16
	reg_fd_edge_alpha_mul              :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900880cL shp_fd_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_edge_y0               :8 ,	// 7:0
	reg_fd_a_lut_edge_x0               :8 ,	// 15:8
	reg_fd_a_lut_edge_y1               :8 ,	// 23:16
	reg_fd_a_lut_edge_x1               :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008810L shp_fd_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_detail_y0             :8 ,	// 7:0
	reg_fd_a_lut_detail_x0             :8 ,	// 15:8
	reg_fd_a_lut_detail_y1             :8 ,	// 23:16
	reg_fd_a_lut_detail_x1             :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008814L shp_fd_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_edge_y0               :8 ,	// 7:0
	reg_fd_t_lut_edge_x0               :8 ,	// 15:8
	reg_fd_t_lut_edge_y1               :8 ,	// 23:16
	reg_fd_t_lut_edge_x1               :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008818L shp_fd_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_detail_y0             :8 ,	// 7:0
	reg_fd_t_lut_detail_x0             :8 ,	// 15:8
	reg_fd_t_lut_detail_y1             :8 ,	// 23:16
	reg_fd_t_lut_detail_x1             :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900881cL shp_fd_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y0              :8 ,	// 7:0
	reg_fd_edge_minmax_x0              :8 ,	// 15:8
	reg_fd_edge_minmax_y1              :8 ,	// 23:16
	reg_fd_edge_minmax_x1              :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008820L shp_fd_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y2              :8 ,	// 7:0
	reg_fd_edge_minmax_x2              :8 ,	// 15:8
	reg_fd_edge_minmax_y3              :8 ,	// 23:16
	reg_fd_edge_minmax_x3              :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008824L shp_fd_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y0            :8 ,	// 7:0
	reg_fd_detail_minmax_x0            :8 ,	// 15:8
	reg_fd_detail_minmax_y1            :8 ,	// 23:16
	reg_fd_detail_minmax_x1            :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008828L shp_fd_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y2            :8 ,	// 7:0
	reg_fd_detail_minmax_x2            :8 ,	// 15:8
	reg_fd_detail_minmax_y3            :8 ,	// 23:16
	reg_fd_detail_minmax_x3            :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900882cL shp_fd_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_e_en               :1 ,	// 0:0
	reg_fd_mnr_gain_t_en               :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_fd_mnr_s1_h_expand             :2 ;	// 5:4
}PE_E60_SHP_2K_FD_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008830L shp_fd_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_s1_mmd_min              :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_fd_mnr_s2_ratio_max            :8 ;	// 23:16
}PE_E60_SHP_2K_FD_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008834L shp_fd_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_x0                 :8 ,	// 7:0
	reg_fd_mnr_gain_x1                 :8 ,	// 15:8
	reg_fd_mnr_gain_y0                 :8 ,	// 23:16
	reg_fd_mnr_gain_y1                 :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9008838L shp_fd_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y0                :8 ,	// 7:0
	reg_fd_dct_t_lut_x0                :8 ,	// 15:8
	reg_fd_dct_t_lut_y1                :8 ,	// 23:16
	reg_fd_dct_t_lut_x1                :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900883cL shp_fd_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y2                :8 ,	// 7:0
	reg_fd_dct_t_lut_x2                :8 ,	// 15:8
	reg_fd_dct_t_lut_y3                :8 ,	// 23:16
	reg_fd_dct_t_lut_x3                :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9008840L shp_fd_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y4                :8 ,	// 7:0
	reg_fd_dct_t_lut_x4                :8 ,	// 15:8
	reg_fd_dct_t_lut_y5                :8 ,	// 23:16
	reg_fd_dct_t_lut_x5                :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008844L shp_fd_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_gain_e_en              :1 ,	// 0:0
	reg_fd_soft_gain_t_en              :1 ;	// 1:1
}PE_E60_SHP_2K_FD_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9008848L shp_fd_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_ratio                  :8 ,	// 7:0
	reg_fd_soft_offset                 :8 ;	// 15:8
}PE_E60_SHP_2K_FD_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900884cL shp_fd_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_score_x0               :8 ,	// 7:0
	reg_fd_soft_score_x1               :8 ,	// 15:8
	reg_fd_soft_score_x2               :8 ,	// 23:16
	reg_fd_soft_score_x3               :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9008850L shp_fd_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_score_y0               :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_fd_soft_score_y1               :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_fd_soft_score_y2               :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_fd_soft_score_y3               :6 ;	// 29:24
}PE_E60_SHP_2K_FD_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9008854L shp_fd_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_flat_input_sel              :2 ,	// 1:0
	reserved01                         :2 ,	// reserved
	reg_fd_flat_protect_e_en           :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_fd_flat_protect_t_en           :1 ;	// 8:8
}PE_E60_SHP_2K_FD_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9008858L shp_fd_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_flat_lut_y0                 :8 ,	// 7:0
	reg_fd_flat_lut_x0                 :8 ,	// 15:8
	reg_fd_flat_lut_y1                 :8 ,	// 23:16
	reg_fd_flat_lut_x1                 :8 ;	// 31:24
}PE_E60_SHP_2K_FD_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9008860L shp_mp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_shp_en                      :1 ;	// 0:0
}PE_E60_SHP_2K_MP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008864L shp_mp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mp_im_gain_h                   :8 ,	// 23:16
	reg_mp_im_gain_v                   :8 ;	// 31:24
}PE_E60_SHP_2K_MP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008868L shp_mp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_lap_weight                  :8 ;	// 15:8
}PE_E60_SHP_2K_MP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900886cL shp_mp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_mp_lap_gain_v_7                :4 ,	// 7:4
	reg_mp_lap_gain_v_5                :4 ,	// 11:8
	reg_mp_lap_gain_v_3                :4 ,	// 15:12
	reserved02                         :4 ,	// reserved
	reg_mp_lap_gain_h_7                :4 ,	// 23:20
	reg_mp_lap_gain_h_5                :4 ,	// 27:24
	reg_mp_lap_gain_h_3                :4 ;	// 31:28
}PE_E60_SHP_2K_MP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008870L shp_mp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_dbg_sel                     :4 ;	// 11:8
}PE_E60_SHP_2K_MP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008874L shp_mp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_mp_gb_mode                     :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_mp_gb_x1                       :8 ,	// 15:8
	reg_mp_gb_y1                       :8 ;	// 23:16
}PE_E60_SHP_2K_MP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008878L shp_mp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_x2                       :8 ,	// 7:0
	reg_mp_gb_y2                       :8 ,	// 15:8
	reg_mp_gb_y3                       :8 ;	// 23:16
}PE_E60_SHP_2K_MP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900887cL shp_mp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_x_l0                   :8 ,	// 7:0
	reg_mp_lum1_x_l1                   :8 ,	// 15:8
	reg_mp_lum1_x_h0                   :8 ,	// 23:16
	reg_mp_lum1_x_h1                   :8 ;	// 31:24
}PE_E60_SHP_2K_MP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008880L shp_mp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_y0                     :8 ,	// 7:0
	reg_mp_lum1_y1                     :8 ,	// 15:8
	reg_mp_lum1_y2                     :8 ,	// 23:16
	reg_mp_lum2_x_l0                   :8 ;	// 31:24
}PE_E60_SHP_2K_MP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008884L shp_mp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_x_l1                   :8 ,	// 7:0
	reg_mp_lum2_x_h0                   :8 ,	// 15:8
	reg_mp_lum2_x_h1                   :8 ,	// 23:16
	reg_mp_lum2_y0                     :8 ;	// 31:24
}PE_E60_SHP_2K_MP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008888L shp_mp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_y1                     :8 ,	// 7:0
	reg_mp_lum2_y2                     :8 ;	// 15:8
}PE_E60_SHP_2K_MP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900888cL shp_mp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_coring_en                   :1 ,	// 0:0
	reg_mp_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_mp_coring_input_sel            :2 ;	// 5:4
}PE_E60_SHP_2K_MP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008890L shp_mp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mp_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mp_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_mp_coring_gain_t_w             :7 ;	// 30:24
}PE_E60_SHP_2K_MP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008894L shp_apl_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_apl_iir_en                     :1 ,	// 0:0
	reserved01                         :7 ,	// reserved
	reg_apl_iir_gain                   :8 ;	// 15:8
}PE_E60_SHP_2K_APL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90088a0L shp_lc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_shp_en                      :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_lc_gb_en                       :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_lc_center_target               :8 ,	// 15:8
	reg_lc_center_gain                 :8 ,	// 23:16
	reg_lc_local_gain                  :8 ;	// 31:24
}PE_E60_SHP_2K_LC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90088a4L shp_lc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gb_y2                       :8 ,	// 7:0
	reg_lc_gb_x2                       :8 ,	// 15:8
	reg_lc_gb_y1                       :8 ,	// 23:16
	reg_lc_gb_x1                       :8 ;	// 31:24
}PE_E60_SHP_2K_LC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90088a8L shp_lc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_lc_lap_weight                  :8 ,	// 15:8
	reg_lc_gb_y3                       :8 ,	// 23:16
	reg_lc_gb_x3                       :8 ;	// 31:24
}PE_E60_SHP_2K_LC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90088acL shp_lc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_en                   :1 ,	// 0:0
	reg_lc_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_lc_coring_input_sel            :2 ;	// 5:4
}PE_E60_SHP_2K_LC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90088b0L shp_lc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_lc_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_lc_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_lc_coring_gain_t_w             :7 ;	// 30:24
}PE_E60_SHP_2K_LC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90088c0L shp_der_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_csft_gain                 :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_th_gain_edge              :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_derh_th_manual_th              :7 ,	// 30:24
	reg_derh_th_manual_en              :1 ;	// 31:31
}PE_E60_SHP_2K_DER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90088c4L shp_der_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derh_bflt_tap_size             :3 ,	// 2:0
	reserved01                         :21,	// reserved
	reg_derh_amean_en                  :1 ,	// 24:24
	reserved02                         :1 ,	// reserved
	reg_derh_edge_filter_v_tap         :2 ,	// 27:26
	reserved03                         :3 ,	// reserved
	reg_derh_edge_y_filter_en          :1 ;	// 31:31
}PE_E60_SHP_2K_DER_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90088c8L shp_der_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_edge_filter_gain_w        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_edge_filter_gain_b        :6 ;	// 21:16
}PE_E60_SHP_2K_DER_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90088ccL shp_der_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_en                        :1 ,	// 0:0
	reserved01                         :2 ,	// reserved
	reg_derv_bif_en                    :1 ,	// 3:3
	reg_derv_output_mux                :4 ,	// 7:4
	reg_derv_bif_manual_th             :8 ,	// 15:8
	reg_derv_th_gain                   :6 ,	// 21:16
	reserved02                         :2 ,	// reserved
	reg_derv_th_mode                   :1 ;	// 24:24
}PE_E60_SHP_2K_DER_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90088d0L shp_der_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_csft_gain                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_derv_csft_mode                 :1 ;	// 8:8
}PE_E60_SHP_2K_DER_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90088d4L shp_der_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_gain_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_derv_gain_w                    :7 ;	// 14:8
}PE_E60_SHP_2K_DER_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90088d8L shp_der_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y0                   :8 ,	// 7:0
	reg_der_a_lut_x0                   :8 ,	// 15:8
	reg_der_a_lut_y1                   :8 ,	// 23:16
	reg_der_a_lut_x1                   :8 ;	// 31:24
}PE_E60_SHP_2K_DER_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90088dcL shp_der_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y2                   :8 ,	// 7:0
	reg_der_a_lut_x2                   :8 ,	// 15:8
	reg_der_a_lut_y3                   :8 ,	// 23:16
	reg_der_a_lut_x3                   :8 ;	// 31:24
}PE_E60_SHP_2K_DER_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90088e0L shp_sp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_shp_en                      :1 ;	// 0:0
}PE_E60_SHP_2K_SP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90088e4L shp_sp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_im_gain_h                   :8 ;	// 23:16
}PE_E60_SHP_2K_SP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90088e8L shp_sp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_lap_weight                  :8 ;	// 15:8
}PE_E60_SHP_2K_SP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90088ecL shp_sp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :20,	// reserved
	reg_sp_lap_gain_h_7                :4 ,	// 23:20
	reg_sp_lap_gain_h_5                :4 ,	// 27:24
	reg_sp_lap_gain_h_3                :4 ;	// 31:28
}PE_E60_SHP_2K_SP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90088f0L shp_sp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_dbg_sel                     :4 ;	// 11:8
}PE_E60_SHP_2K_SP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90088f4L shp_sp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_sp_gb_mode                     :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_sp_gb_x1                       :8 ,	// 15:8
	reg_sp_gb_y1                       :8 ;	// 23:16
}PE_E60_SHP_2K_SP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90088f8L shp_sp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_x2                       :8 ,	// 7:0
	reg_sp_gb_y2                       :8 ,	// 15:8
	reg_sp_gb_y3                       :8 ;	// 23:16
}PE_E60_SHP_2K_SP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90088fcL shp_sp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_x_l0                   :8 ,	// 7:0
	reg_sp_lum1_x_l1                   :8 ,	// 15:8
	reg_sp_lum1_x_h0                   :8 ,	// 23:16
	reg_sp_lum1_x_h1                   :8 ;	// 31:24
}PE_E60_SHP_2K_SP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008900L shp_sp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_y0                     :8 ,	// 7:0
	reg_sp_lum1_y1                     :8 ,	// 15:8
	reg_sp_lum1_y2                     :8 ,	// 23:16
	reg_sp_lum2_x_l0                   :8 ;	// 31:24
}PE_E60_SHP_2K_SP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008904L shp_sp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_x_l1                   :8 ,	// 7:0
	reg_sp_lum2_x_h0                   :8 ,	// 15:8
	reg_sp_lum2_x_h1                   :8 ,	// 23:16
	reg_sp_lum2_y0                     :8 ;	// 31:24
}PE_E60_SHP_2K_SP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008908L shp_sp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_y1                     :8 ,	// 7:0
	reg_sp_lum2_y2                     :8 ;	// 15:8
}PE_E60_SHP_2K_SP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900890cL shp_sp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_coring_en                   :1 ,	// 0:0
	reg_sp_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_sp_coring_input_sel            :2 ;	// 5:4
}PE_E60_SHP_2K_SP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008910L shp_sp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_sp_coring_gain_t_w             :7 ;	// 30:24
}PE_E60_SHP_2K_SP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008920L shp_pti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptiv_enable                    :1 ,	// 0:0
	reg_ptiv_debug_map_en              :1 ,	// 1:1
	reg_ptiv_mm_tap_size               :2 ,	// 3:2
	reg_ptiv_avg_tap_size              :2 ,	// 5:4
	reg_ptiv_ti_mode                   :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_ptiv_master_gain               :8 ;	// 15:8
}PE_E60_SHP_2K_PTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008924L shp_pti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptih_enable                    :1 ,	// 0:0
	reg_ptih_debug_map_en              :1 ,	// 1:1
	reg_ptih_mm_tap_size               :2 ,	// 3:2
	reg_ptih_avg_tap_size              :2 ,	// 5:4
	reg_ptih_ti_mode                   :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_ptih_master_gain               :8 ;	// 15:8
}PE_E60_SHP_2K_PTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008928L shp_pti_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pti_coring_en                  :1 ,	// 0:0
	reg_pti_coring_mode                :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_pti_coring_input_sel           :2 ;	// 5:4
}PE_E60_SHP_2K_PTI_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900892cL shp_pti_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pti_coring_gain_e_b            :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_pti_coring_gain_e_w            :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_pti_coring_gain_t_b            :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_pti_coring_gain_t_w            :7 ;	// 30:24
}PE_E60_SHP_2K_PTI_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008930L shp_sti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sti_enable                     :1 ,	// 0:0
	reg_sti_debug_map_en               :1 ,	// 1:1
	reg_sti_mm_tap_size                :2 ,	// 3:2
	reg_sti_avg_tap_size               :2 ,	// 5:4
	reg_sti_ti_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_sti_master_gain                :8 ,	// 15:8
	reg_sti_texture_gain               :8 ,	// 23:16
	reg_sti_edge_gain                  :8 ;	// 31:24
}PE_E60_SHP_2K_STI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008940L shp_tgen_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_on_off                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_tgen_initial_seed_mode         :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_tgen_dbg_en                    :1 ,	// 8:8
	reserved03                         :7 ,	// reserved
	reg_tgen_table_sel                 :4 ,	// 19:16
	reserved04                         :4 ,	// reserved
	reg_tgen_master_gain               :8 ;	// 31:24
}PE_E60_SHP_2K_TGEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008944L shp_tgen_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_delta_h_bound             :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_tgen_delta_l_bound             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_tgen_delta_max                 :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgen_delta_scale               :3 ;	// 26:24
}PE_E60_SHP_2K_TGEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008948L shp_tgen_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rnd_th                    :8 ,	// 7:0
	reg_tgen_delta_wcurr               :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_tgen_lc_ldr_th                 :6 ;	// 21:16
}PE_E60_SHP_2K_TGEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900894cL shp_tgen_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rand_x0;	// 31:0
}PE_E60_SHP_2K_TGEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008954L shp_tgen_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_dr_ratio                  :3 ,	// 2:0
	reserved01                         :5 ,	// reserved
	reg_tgen_dr_th                     :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_tgen_mm_offset                 :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	reg_tgen_mm_sel_mode               :2 ;	// 25:24
}PE_E60_SHP_2K_TGEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008958L shp_tgen_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_tgen_gs_rnd                    :5 ,	// 20:16
	reserved02                         :3 ,	// reserved
	reg_tgen_gs_mm                     :5 ;	// 28:24
}PE_E60_SHP_2K_TGEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900895cL shp_tgen_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_x2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_x1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_x0              :6 ;	// 29:24
}PE_E60_SHP_2K_TGEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008960L shp_tgen_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_y2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_y1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_y0              :6 ;	// 29:24
}PE_E60_SHP_2K_TGEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008964L shp_tgen_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_map_edge_gain             :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_tgen_map_detail_gain           :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_tgen_map_offset                :8 ,	// 23:16
	reg_tgen_gs_noise                  :6 ;	// 29:24
}PE_E60_SHP_2K_TGEN_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008968L shp_tgen_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_gain7                     :4 ,	// 3:0
	reg_tgen_gain6                     :4 ,	// 7:4
	reg_tgen_gain5                     :4 ,	// 11:8
	reg_tgen_gain4                     :4 ,	// 15:12
	reg_tgen_gain3                     :4 ,	// 19:16
	reg_tgen_gain2                     :4 ,	// 23:20
	reg_tgen_gain1                     :4 ,	// 27:24
	reg_tgen_gain0                     :4 ;	// 31:28
}PE_E60_SHP_2K_TGEN_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900896cL shp_tgen_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_coring_en                 :1 ,	// 0:0
	reg_tgen_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_tgen_coring_input_sel          :2 ;	// 5:4
}PE_E60_SHP_2K_TGEN_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9008970L shp_tgen_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_tgen_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_tgen_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgen_coring_gain_t_w           :7 ;	// 30:24
}PE_E60_SHP_2K_TGEN_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008974L shp_snr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_snr_blur_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_snr_blur_sel                   :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_snr_bilateral_th               :8 ,	// 15:8
	reg_snr_blur_mode                  :3 ;	// 18:16
}PE_E60_SHP_2K_SNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008980L shp_dctp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_en                        :1 ;	// 0:0
}PE_E60_SHP_2K_DCTP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008984L shp_dctp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_1              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008988L shp_dctp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_3              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900898cL shp_dctp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_5              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008990L shp_dctp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_7              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008994L shp_dctp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_1              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008998L shp_dctp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_3              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900899cL shp_dctp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_5              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90089a0L shp_dctp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_7              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90089a4L shp_dctp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_1              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90089a8L shp_dctp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_3              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc90089acL shp_dctp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_5              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90089b0L shp_dctp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_7              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90089b4L shp_dctp_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_1              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc90089b8L shp_dctp_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_3              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc90089bcL shp_dctp_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_5              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90089c0L shp_dctp_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_7              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90089c4L shp_dctp_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_1              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90089c8L shp_dctp_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_3              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90089ccL shp_dctp_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_5              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90089d0L shp_dctp_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_7              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90089d4L shp_dctp_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_1              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90089d8L shp_dctp_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_3              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90089dcL shp_dctp_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_5              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90089e0L shp_dctp_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_7              :12;	// 27:16
}PE_E60_SHP_2K_DCTP_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90089e4L shp_dctp_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x0               :8 ,	// 7:0
	reg_dctp_text_lut_x1               :8 ,	// 15:8
	reg_dctp_text_lut_x2               :8 ,	// 23:16
	reg_dctp_text_lut_x3               :8 ;	// 31:24
}PE_E60_SHP_2K_DCTP_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90089e8L shp_dctp_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x4               :8 ,	// 7:0
	reg_dctp_text_lut_x5               :8 ;	// 15:8
}PE_E60_SHP_2K_DCTP_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc90089ecL shp_dctp_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y0               :8 ,	// 7:0
	reg_dctp_edge_lut_x0               :8 ,	// 15:8
	reg_dctp_edge_lut_y1               :8 ,	// 23:16
	reg_dctp_edge_lut_x1               :8 ;	// 31:24
}PE_E60_SHP_2K_DCTP_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc90089f0L shp_dctp_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y2               :8 ,	// 7:0
	reg_dctp_edge_lut_x2               :8 ,	// 15:8
	reg_dctp_edge_lut_y3               :8 ,	// 23:16
	reg_dctp_edge_lut_x3               :8 ;	// 31:24
}PE_E60_SHP_2K_DCTP_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc90089f4L shp_dctp_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_gain                      :8 ;	// 7:0
}PE_E60_SHP_2K_DCTP_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc90089f8L shp_dctp_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_coring_en                 :1 ,	// 0:0
	reg_dctp_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_dctp_coring_input_sel          :2 ;	// 5:4
}PE_E60_SHP_2K_DCTP_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc90089fcL shp_dctp_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_dctp_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_dctp_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_dctp_coring_gain_t_w           :7 ;	// 30:24
}PE_E60_SHP_2K_DCTP_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9008a00L shp_nntg_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_en                        :1 ,	// 0:0
	reserved01                         :3 , // reserved
	reg_nntg_debug_mode                :2 ;	// 5:4
}PE_E60_SHP_2K_NNTG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008a04L shp_nntg_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_1st;	// 31:0
}PE_E60_SHP_2K_NNTG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008a08L shp_nntg_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_2nd;	// 31:0
}PE_E60_SHP_2K_NNTG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008a0cL shp_nntg_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_3rd;	// 31:0
}PE_E60_SHP_2K_NNTG_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008a10L shp_nntg_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_4th;	// 31:0
}PE_E60_SHP_2K_NNTG_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008a14L shp_nntg_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_5th;	// 31:0
}PE_E60_SHP_2K_NNTG_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008a2cL shp_nntg_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_ratio                :8 ,	// 7:0
	reg_nntg_rand_max                  :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_nntg_rand_sum_max              :8 ;	// 23:16
}PE_E60_SHP_2K_NNTG_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008a30L shp_nntg_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_coef_g00             :4 ,	// 3:0
	reg_nntg_rand_coef_g01             :4 ,	// 7:4
	reg_nntg_rand_coef_g02             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_rand_coef_g10             :4 ,	// 19:16
	reg_nntg_rand_coef_g11             :4 ,	// 23:20
	reg_nntg_rand_coef_g12             :4 ;	// 27:24
}PE_E60_SHP_2K_NNTG_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008a34L shp_nntg_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_coef_g20             :4 ,	// 3:0
	reg_nntg_rand_coef_g21             :4 ,	// 7:4
	reg_nntg_rand_coef_g22             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_nano_coef_g00             :4 ,	// 19:16
	reg_nntg_nano_coef_g01             :4 ,	// 23:20
	reg_nntg_nano_coef_g02             :4 ;	// 27:24
}PE_E60_SHP_2K_NNTG_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008a38L shp_nntg_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_nano_coef_g10             :4 ,	// 3:0
	reg_nntg_nano_coef_g11             :4 ,	// 7:4
	reg_nntg_nano_coef_g12             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_nano_coef_g20             :4 ,	// 19:16
	reg_nntg_nano_coef_g21             :4 ,	// 23:20
	reg_nntg_nano_coef_g22             :4 ;	// 27:24
}PE_E60_SHP_2K_NNTG_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008a3cL shp_nntg_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y0               :8 ,	// 7:0
	reg_nntg_diff_lut_x0               :8 ,	// 15:8
	reg_nntg_diff_lut_y1               :8 ,	// 23:16
	reg_nntg_diff_lut_x1               :8 ;	// 31:24
}PE_E60_SHP_2K_NNTG_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9008a40L shp_nntg_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y2               :8 ,	// 7:0
	reg_nntg_diff_lut_x2               :8 ,	// 15:8
	reg_nntg_diff_lut_y3               :8 ,	// 23:16
	reg_nntg_diff_lut_x3               :8 ;	// 31:24
}PE_E60_SHP_2K_NNTG_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008a44L shp_nntg_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y0               :8 ,	// 7:0
	reg_nntg_edge_lut_x0               :8 ,	// 15:8
	reg_nntg_edge_lut_y1               :8 ,	// 23:16
	reg_nntg_edge_lut_x1               :8 ;	// 31:24
}PE_E60_SHP_2K_NNTG_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008a48L shp_nntg_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y2               :8 ,	// 7:0
	reg_nntg_edge_lut_x2               :8 ,	// 15:8
	reg_nntg_edge_lut_y3               :8 ,	// 23:16
	reg_nntg_edge_lut_x3               :8 ;	// 31:24
}PE_E60_SHP_2K_NNTG_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9008a4cL shp_nntg_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_random_gain               :8 ,	// 7:0
	reg_nntg_pattern_gain              :8 ,	// 15:8
	reg_nntg_local_gain                :8 ,	// 23:16
	reg_nntg_denoise_gain              :8 ;	// 31:24
}PE_E60_SHP_2K_NNTG_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc9008a50L shp_nntg_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_coring_en                 :1 ,	// 0:0
	reg_nntg_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_nntg_coring_input_sel          :2 ;	// 5:4
}PE_E60_SHP_2K_NNTG_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9008a54L shp_nntg_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_nntg_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_nntg_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_nntg_coring_gain_t_w           :7 ;	// 30:24
}PE_E60_SHP_2K_NNTG_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008a60L shp_dp_sum_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_gain                    :8 ,	// 7:0
	reg_dp_sum_lut_mode                :2 ;	// 9:8
}PE_E60_SHP_2K_DP_SUM_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008a64L shp_dp_sum_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_lut_y0                  :8 ,	// 7:0
	reg_dp_sum_lut_x0                  :8 ,	// 15:8
	reg_dp_sum_lut_y1                  :8 ,	// 23:16
	reg_dp_sum_lut_x1                  :8 ;	// 31:24
}PE_E60_SHP_2K_DP_SUM_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008a68L shp_dp_sum_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_lut_y2                  :8 ,	// 7:0
	reg_dp_sum_lut_x2                  :8 ,	// 15:8
	reg_dp_sum_lut_y3                  :8 ,	// 23:16
	reg_dp_sum_lut_x3                  :8 ;	// 31:24
}PE_E60_SHP_2K_DP_SUM_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008aa0L shp_dp_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win0_en                 :1 ,	// 0:0
	reg_win_dp_win1_en                 :1 ,	// 1:1
	reg_win_dp_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dp_win_outside             :1 ,	// 6:6
	reg_win_dp_win_en                  :1 ,	// 7:7
	reg_win_dp_bdr_alpha               :5 ,	// 12:8
	reg_win_dp_bdr_wid                 :2 ,	// 14:13
	reg_win_dp_bdr_en                  :1 ,	// 15:15
	reg_win_dp_cr5                     :5 ,	// 20:16
	reg_win_dp_cb5                     :5 ,	// 25:21
	reg_win_dp_yy6                     :6 ;	// 31:26
}PE_E60_SHP_2K_DP_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008aa4L shp_dp_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y0               :12;	// 27:16
}PE_E60_SHP_2K_DP_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008aa8L shp_dp_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y1               :12;	// 27:16
}PE_E60_SHP_2K_DP_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008aacL shp_dp_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y0               :12;	// 27:16
}PE_E60_SHP_2K_DP_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008ab0L shp_dp_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y1               :12;	// 27:16
}PE_E60_SHP_2K_DP_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008ac0L shp_fd_region_text_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_en                 :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_region_text_cutres             :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	reg_region_text_add_offset         :8 ,	// 15:8
	reg_region_text_add_max            :8 ,	// 23:16
	reg_region_text_cuthif             :3 ;	// 26:24
}PE_E60_SHP_2K_FD_REGION_TEXT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008ac4L shp_fd_region_text_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_lut_y0             :8 ,	// 7:0
	reg_region_text_lut_x0             :8 ,	// 15:8
	reg_region_text_lut_y1             :8 ,	// 23:16
	reg_region_text_lut_x1             :8 ;	// 31:24
}PE_E60_SHP_2K_FD_REGION_TEXT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ac8L shp_fd_region_text_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_lut_y2             :8 ,	// 7:0
	reg_region_text_lut_x2             :8 ,	// 15:8
	reg_region_text_lut_y3             :8 ,	// 23:16
	reg_region_text_lut_x3             :8 ;	// 31:24
}PE_E60_SHP_2K_FD_REGION_TEXT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008accL shp_fd_tmap_temp_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_en               :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_tmap_temp_init_en              :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_tmap_temp_init_val             :8 ,	// 15:8
	reserved03                         :8 ,	// reserved
	reg_tmap_stat_sel                  :1 ;	// 24:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008ad0L shp_fd_tmap_temp_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_prev_lut_y0          :8 ,	// 7:0
	reg_tmap_temp_prev_lut_x0          :8 ,	// 15:8
	reg_tmap_temp_prev_lut_y1          :8 ,	// 23:16
	reg_tmap_temp_prev_lut_x1          :8 ;	// 31:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ad4L shp_fd_tmap_temp_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_prev_lut_y2          :8 ,	// 7:0
	reg_tmap_temp_prev_lut_x2          :8 ,	// 15:8
	reg_tmap_temp_prev_lut_y3          :8 ,	// 23:16
	reg_tmap_temp_prev_lut_x3          :8 ;	// 31:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008ad8L shp_fd_tmap_temp_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y0       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x0       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y1       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x1       :8 ;	// 31:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008adcL shp_fd_tmap_temp_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y2       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x2       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y3       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x3       :8 ;	// 31:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008ae0L shp_fd_tmap_temp_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y4       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x4       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y5       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x5       :8 ;	// 31:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008ae4L shp_fd_tmap_temp_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y0       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x0       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y1       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x1       :8 ;	// 31:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008ae8L shp_fd_tmap_temp_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y2       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x2       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y3       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x3       :8 ;	// 31:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008aecL shp_fd_tmap_temp_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y4       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x4       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y5       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x5       :8 ;	// 31:24
}PE_E60_SHP_2K_FD_TMAP_TEMP_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008af0L shp_fd_tmap_temp_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win0_start_x         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win0_start_y         :12;	// 27:16
}PE_E60_SHP_2K_FD_TMAP_TEMP_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008af4L shp_fd_tmap_temp_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win0_end_x           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win0_end_y           :12;	// 27:16
}PE_E60_SHP_2K_FD_TMAP_TEMP_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9008af8L shp_fd_tmap_temp_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win1_start_x         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win1_start_y         :12;	// 27:16
}PE_E60_SHP_2K_FD_TMAP_TEMP_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008afcL shp_fd_tmap_temp_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win1_end_x           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win1_end_y           :12;	// 27:16
}PE_E60_SHP_2K_FD_TMAP_TEMP_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008b00L shp_dj_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_edf_en                      :1 ,	// 0:0
	reg_dj_hv_filter_en                :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_dj_edge_adaptive_en            :1 ,	// 3:3
	reg_dj_line_variation_mode         :1 ,	// 4:4
	reg_dj_l_type_protection           :1 ,	// 5:5
	reg_dj_soft_en                     :1 ,	// 6:6
	reserved02                         :1 ,	// reserved
	reg_dj_count_diff_th               :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_dj_output_mux                  :3 ,	// 18:16
	reg_dj_buffer_detour_en            :1 ,	// 19:19
	reg_dj_center_blur_mode            :2 ,	// 21:20
	reg_dj_n_avg_mode                  :1 ,	// 22:22
	reg_dj_detour_en                   :1 ,	// 23:23
	reg_dj_line_variation_diff_th      :8 ;	// 31:24
}PE_E60_SHP_2K_DJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008b04L shp_dj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_level_th                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dj_n_avg_gain                  :8 ;	// 23:16
}PE_E60_SHP_2K_DJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008b08L shp_dj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g0_cnt_min                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_dj_g0_mul                      :5 ;	// 12:8
}PE_E60_SHP_2K_DJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008b0cL shp_dj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g1_protect_min              :8 ,	// 7:0
	reg_dj_g1_mul                      :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_dj_edge_min                    :8 ,	// 23:16
	reg_dj_edge_mul                    :8 ;	// 31:24
}PE_E60_SHP_2K_DJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008b10L shp_dj_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_dir_sel_c1                  :1 ,	// 0:0
	reg_dj_dir_sel_c2                  :1 ,	// 1:1
	reg_dj_dir_sel_c3                  :1 ,	// 2:2
	reg_dj_dir_sel_c4                  :1 ;	// 3:3
}PE_E60_SHP_2K_DJ_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008b14L shp_dj_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_0_00               :2 ,	// 1:0
	reg_dj_pattern0_0_01               :2 ,	// 3:2
	reg_dj_pattern0_0_02               :2 ,	// 5:4
	reg_dj_pattern0_0_03               :2 ,	// 7:6
	reg_dj_pattern0_0_04               :2 ,	// 9:8
	reg_dj_pattern0_0_05               :2 ,	// 11:10
	reg_dj_pattern0_0_06               :2 ,	// 13:12
	reg_dj_pattern0_0_07               :2 ,	// 15:14
	reg_dj_pattern0_0_08               :2 ,	// 17:16
	reg_dj_pattern0_0_09               :2 ,	// 19:18
	reg_dj_pattern0_0_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008b18L shp_dj_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_1_00               :2 ,	// 1:0
	reg_dj_pattern0_1_01               :2 ,	// 3:2
	reg_dj_pattern0_1_02               :2 ,	// 5:4
	reg_dj_pattern0_1_03               :2 ,	// 7:6
	reg_dj_pattern0_1_04               :2 ,	// 9:8
	reg_dj_pattern0_1_05               :2 ,	// 11:10
	reg_dj_pattern0_1_06               :2 ,	// 13:12
	reg_dj_pattern0_1_07               :2 ,	// 15:14
	reg_dj_pattern0_1_08               :2 ,	// 17:16
	reg_dj_pattern0_1_09               :2 ,	// 19:18
	reg_dj_pattern0_1_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008b1cL shp_dj_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_2_00               :2 ,	// 1:0
	reg_dj_pattern0_2_01               :2 ,	// 3:2
	reg_dj_pattern0_2_02               :2 ,	// 5:4
	reg_dj_pattern0_2_03               :2 ,	// 7:6
	reg_dj_pattern0_2_04               :2 ,	// 9:8
	reg_dj_pattern0_2_05               :2 ,	// 11:10
	reg_dj_pattern0_2_06               :2 ,	// 13:12
	reg_dj_pattern0_2_07               :2 ,	// 15:14
	reg_dj_pattern0_2_08               :2 ,	// 17:16
	reg_dj_pattern0_2_09               :2 ,	// 19:18
	reg_dj_pattern0_2_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008b20L shp_dj_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_3_00               :2 ,	// 1:0
	reg_dj_pattern0_3_01               :2 ,	// 3:2
	reg_dj_pattern0_3_02               :2 ,	// 5:4
	reg_dj_pattern0_3_03               :2 ,	// 7:6
	reg_dj_pattern0_3_04               :2 ,	// 9:8
	reg_dj_pattern0_3_05               :2 ,	// 11:10
	reg_dj_pattern0_3_06               :2 ,	// 13:12
	reg_dj_pattern0_3_07               :2 ,	// 15:14
	reg_dj_pattern0_3_08               :2 ,	// 17:16
	reg_dj_pattern0_3_09               :2 ,	// 19:18
	reg_dj_pattern0_3_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008b24L shp_dj_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_4_00               :2 ,	// 1:0
	reg_dj_pattern0_4_01               :2 ,	// 3:2
	reg_dj_pattern0_4_02               :2 ,	// 5:4
	reg_dj_pattern0_4_03               :2 ,	// 7:6
	reg_dj_pattern0_4_04               :2 ,	// 9:8
	reg_dj_pattern0_4_05               :2 ,	// 11:10
	reg_dj_pattern0_4_06               :2 ,	// 13:12
	reg_dj_pattern0_4_07               :2 ,	// 15:14
	reg_dj_pattern0_4_08               :2 ,	// 17:16
	reg_dj_pattern0_4_09               :2 ,	// 19:18
	reg_dj_pattern0_4_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008b28L shp_dj_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_5_00               :2 ,	// 1:0
	reg_dj_pattern0_5_01               :2 ,	// 3:2
	reg_dj_pattern0_5_02               :2 ,	// 5:4
	reg_dj_pattern0_5_03               :2 ,	// 7:6
	reg_dj_pattern0_5_04               :2 ,	// 9:8
	reg_dj_pattern0_5_05               :2 ,	// 11:10
	reg_dj_pattern0_5_06               :2 ,	// 13:12
	reg_dj_pattern0_5_07               :2 ,	// 15:14
	reg_dj_pattern0_5_08               :2 ,	// 17:16
	reg_dj_pattern0_5_09               :2 ,	// 19:18
	reg_dj_pattern0_5_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9008b2cL shp_dj_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_6_00               :2 ,	// 1:0
	reg_dj_pattern0_6_01               :2 ,	// 3:2
	reg_dj_pattern0_6_02               :2 ,	// 5:4
	reg_dj_pattern0_6_03               :2 ,	// 7:6
	reg_dj_pattern0_6_04               :2 ,	// 9:8
	reg_dj_pattern0_6_05               :2 ,	// 11:10
	reg_dj_pattern0_6_06               :2 ,	// 13:12
	reg_dj_pattern0_6_07               :2 ,	// 15:14
	reg_dj_pattern0_6_08               :2 ,	// 17:16
	reg_dj_pattern0_6_09               :2 ,	// 19:18
	reg_dj_pattern0_6_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9008b30L shp_dj_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_flip0_h            :1 ,	// 0:0
	reg_dj_pattern0_flip0_v            :1 ,	// 1:1
	reg_dj_pattern0_flip1_h            :1 ,	// 2:2
	reg_dj_pattern0_flip1_v            :1 ,	// 3:3
	reg_dj_pattern0_flip2_h            :1 ,	// 4:4
	reg_dj_pattern0_flip2_v            :1 ,	// 5:5
	reg_dj_pattern0_flip3_h            :1 ,	// 6:6
	reg_dj_pattern0_flip3_v            :1 ;	// 7:7
}PE_E60_SHP_2K_DJ_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9008b34L shp_dj_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_0_00               :2 ,	// 1:0
	reg_dj_pattern1_0_01               :2 ,	// 3:2
	reg_dj_pattern1_0_02               :2 ,	// 5:4
	reg_dj_pattern1_0_03               :2 ,	// 7:6
	reg_dj_pattern1_0_04               :2 ,	// 9:8
	reg_dj_pattern1_0_05               :2 ,	// 11:10
	reg_dj_pattern1_0_06               :2 ,	// 13:12
	reg_dj_pattern1_0_07               :2 ,	// 15:14
	reg_dj_pattern1_0_08               :2 ,	// 17:16
	reg_dj_pattern1_0_09               :2 ,	// 19:18
	reg_dj_pattern1_0_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9008b38L shp_dj_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_1_00               :2 ,	// 1:0
	reg_dj_pattern1_1_01               :2 ,	// 3:2
	reg_dj_pattern1_1_02               :2 ,	// 5:4
	reg_dj_pattern1_1_03               :2 ,	// 7:6
	reg_dj_pattern1_1_04               :2 ,	// 9:8
	reg_dj_pattern1_1_05               :2 ,	// 11:10
	reg_dj_pattern1_1_06               :2 ,	// 13:12
	reg_dj_pattern1_1_07               :2 ,	// 15:14
	reg_dj_pattern1_1_08               :2 ,	// 17:16
	reg_dj_pattern1_1_09               :2 ,	// 19:18
	reg_dj_pattern1_1_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc9008b3cL shp_dj_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_2_00               :2 ,	// 1:0
	reg_dj_pattern1_2_01               :2 ,	// 3:2
	reg_dj_pattern1_2_02               :2 ,	// 5:4
	reg_dj_pattern1_2_03               :2 ,	// 7:6
	reg_dj_pattern1_2_04               :2 ,	// 9:8
	reg_dj_pattern1_2_05               :2 ,	// 11:10
	reg_dj_pattern1_2_06               :2 ,	// 13:12
	reg_dj_pattern1_2_07               :2 ,	// 15:14
	reg_dj_pattern1_2_08               :2 ,	// 17:16
	reg_dj_pattern1_2_09               :2 ,	// 19:18
	reg_dj_pattern1_2_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9008b40L shp_dj_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_3_00               :2 ,	// 1:0
	reg_dj_pattern1_3_01               :2 ,	// 3:2
	reg_dj_pattern1_3_02               :2 ,	// 5:4
	reg_dj_pattern1_3_03               :2 ,	// 7:6
	reg_dj_pattern1_3_04               :2 ,	// 9:8
	reg_dj_pattern1_3_05               :2 ,	// 11:10
	reg_dj_pattern1_3_06               :2 ,	// 13:12
	reg_dj_pattern1_3_07               :2 ,	// 15:14
	reg_dj_pattern1_3_08               :2 ,	// 17:16
	reg_dj_pattern1_3_09               :2 ,	// 19:18
	reg_dj_pattern1_3_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008b44L shp_dj_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_4_00               :2 ,	// 1:0
	reg_dj_pattern1_4_01               :2 ,	// 3:2
	reg_dj_pattern1_4_02               :2 ,	// 5:4
	reg_dj_pattern1_4_03               :2 ,	// 7:6
	reg_dj_pattern1_4_04               :2 ,	// 9:8
	reg_dj_pattern1_4_05               :2 ,	// 11:10
	reg_dj_pattern1_4_06               :2 ,	// 13:12
	reg_dj_pattern1_4_07               :2 ,	// 15:14
	reg_dj_pattern1_4_08               :2 ,	// 17:16
	reg_dj_pattern1_4_09               :2 ,	// 19:18
	reg_dj_pattern1_4_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9008b48L shp_dj_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_5_00               :2 ,	// 1:0
	reg_dj_pattern1_5_01               :2 ,	// 3:2
	reg_dj_pattern1_5_02               :2 ,	// 5:4
	reg_dj_pattern1_5_03               :2 ,	// 7:6
	reg_dj_pattern1_5_04               :2 ,	// 9:8
	reg_dj_pattern1_5_05               :2 ,	// 11:10
	reg_dj_pattern1_5_06               :2 ,	// 13:12
	reg_dj_pattern1_5_07               :2 ,	// 15:14
	reg_dj_pattern1_5_08               :2 ,	// 17:16
	reg_dj_pattern1_5_09               :2 ,	// 19:18
	reg_dj_pattern1_5_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9008b4cL shp_dj_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_6_00               :2 ,	// 1:0
	reg_dj_pattern1_6_01               :2 ,	// 3:2
	reg_dj_pattern1_6_02               :2 ,	// 5:4
	reg_dj_pattern1_6_03               :2 ,	// 7:6
	reg_dj_pattern1_6_04               :2 ,	// 9:8
	reg_dj_pattern1_6_05               :2 ,	// 11:10
	reg_dj_pattern1_6_06               :2 ,	// 13:12
	reg_dj_pattern1_6_07               :2 ,	// 15:14
	reg_dj_pattern1_6_08               :2 ,	// 17:16
	reg_dj_pattern1_6_09               :2 ,	// 19:18
	reg_dj_pattern1_6_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9008b50L shp_dj_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_flip0_h            :1 ,	// 0:0
	reg_dj_pattern1_flip0_v            :1 ,	// 1:1
	reg_dj_pattern1_flip1_h            :1 ,	// 2:2
	reg_dj_pattern1_flip1_v            :1 ;	// 3:3
}PE_E60_SHP_2K_DJ_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9008b54L shp_dj_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_0_00               :2 ,	// 1:0
	reg_dj_pattern2_0_01               :2 ,	// 3:2
	reg_dj_pattern2_0_02               :2 ,	// 5:4
	reg_dj_pattern2_0_03               :2 ,	// 7:6
	reg_dj_pattern2_0_04               :2 ,	// 9:8
	reg_dj_pattern2_0_05               :2 ,	// 11:10
	reg_dj_pattern2_0_06               :2 ,	// 13:12
	reg_dj_pattern2_0_07               :2 ,	// 15:14
	reg_dj_pattern2_0_08               :2 ,	// 17:16
	reg_dj_pattern2_0_09               :2 ,	// 19:18
	reg_dj_pattern2_0_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9008b58L shp_dj_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_1_00               :2 ,	// 1:0
	reg_dj_pattern2_1_01               :2 ,	// 3:2
	reg_dj_pattern2_1_02               :2 ,	// 5:4
	reg_dj_pattern2_1_03               :2 ,	// 7:6
	reg_dj_pattern2_1_04               :2 ,	// 9:8
	reg_dj_pattern2_1_05               :2 ,	// 11:10
	reg_dj_pattern2_1_06               :2 ,	// 13:12
	reg_dj_pattern2_1_07               :2 ,	// 15:14
	reg_dj_pattern2_1_08               :2 ,	// 17:16
	reg_dj_pattern2_1_09               :2 ,	// 19:18
	reg_dj_pattern2_1_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9008b5cL shp_dj_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_2_00               :2 ,	// 1:0
	reg_dj_pattern2_2_01               :2 ,	// 3:2
	reg_dj_pattern2_2_02               :2 ,	// 5:4
	reg_dj_pattern2_2_03               :2 ,	// 7:6
	reg_dj_pattern2_2_04               :2 ,	// 9:8
	reg_dj_pattern2_2_05               :2 ,	// 11:10
	reg_dj_pattern2_2_06               :2 ,	// 13:12
	reg_dj_pattern2_2_07               :2 ,	// 15:14
	reg_dj_pattern2_2_08               :2 ,	// 17:16
	reg_dj_pattern2_2_09               :2 ,	// 19:18
	reg_dj_pattern2_2_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9008b60L shp_dj_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_3_00               :2 ,	// 1:0
	reg_dj_pattern2_3_01               :2 ,	// 3:2
	reg_dj_pattern2_3_02               :2 ,	// 5:4
	reg_dj_pattern2_3_03               :2 ,	// 7:6
	reg_dj_pattern2_3_04               :2 ,	// 9:8
	reg_dj_pattern2_3_05               :2 ,	// 11:10
	reg_dj_pattern2_3_06               :2 ,	// 13:12
	reg_dj_pattern2_3_07               :2 ,	// 15:14
	reg_dj_pattern2_3_08               :2 ,	// 17:16
	reg_dj_pattern2_3_09               :2 ,	// 19:18
	reg_dj_pattern2_3_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9008b64L shp_dj_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_4_00               :2 ,	// 1:0
	reg_dj_pattern2_4_01               :2 ,	// 3:2
	reg_dj_pattern2_4_02               :2 ,	// 5:4
	reg_dj_pattern2_4_03               :2 ,	// 7:6
	reg_dj_pattern2_4_04               :2 ,	// 9:8
	reg_dj_pattern2_4_05               :2 ,	// 11:10
	reg_dj_pattern2_4_06               :2 ,	// 13:12
	reg_dj_pattern2_4_07               :2 ,	// 15:14
	reg_dj_pattern2_4_08               :2 ,	// 17:16
	reg_dj_pattern2_4_09               :2 ,	// 19:18
	reg_dj_pattern2_4_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9008b68L shp_dj_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_5_00               :2 ,	// 1:0
	reg_dj_pattern2_5_01               :2 ,	// 3:2
	reg_dj_pattern2_5_02               :2 ,	// 5:4
	reg_dj_pattern2_5_03               :2 ,	// 7:6
	reg_dj_pattern2_5_04               :2 ,	// 9:8
	reg_dj_pattern2_5_05               :2 ,	// 11:10
	reg_dj_pattern2_5_06               :2 ,	// 13:12
	reg_dj_pattern2_5_07               :2 ,	// 15:14
	reg_dj_pattern2_5_08               :2 ,	// 17:16
	reg_dj_pattern2_5_09               :2 ,	// 19:18
	reg_dj_pattern2_5_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc9008b6cL shp_dj_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_6_00               :2 ,	// 1:0
	reg_dj_pattern2_6_01               :2 ,	// 3:2
	reg_dj_pattern2_6_02               :2 ,	// 5:4
	reg_dj_pattern2_6_03               :2 ,	// 7:6
	reg_dj_pattern2_6_04               :2 ,	// 9:8
	reg_dj_pattern2_6_05               :2 ,	// 11:10
	reg_dj_pattern2_6_06               :2 ,	// 13:12
	reg_dj_pattern2_6_07               :2 ,	// 15:14
	reg_dj_pattern2_6_08               :2 ,	// 17:16
	reg_dj_pattern2_6_09               :2 ,	// 19:18
	reg_dj_pattern2_6_10               :2 ;	// 21:20
}PE_E60_SHP_2K_DJ_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc9008b70L shp_dj_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_flip0_h            :1 ,	// 0:0
	reg_dj_pattern2_flip0_v            :1 ,	// 1:1
	reg_dj_pattern2_flip1_h            :1 ,	// 2:2
	reg_dj_pattern2_flip1_v            :1 ;	// 3:3
}PE_E60_SHP_2K_DJ_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc9008b74L shp_dj_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g0_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g0_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g0_max                 :8 ;	// 23:16
}PE_E60_SHP_2K_DJ_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc9008b78L shp_dj_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g1_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g1_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g1_max                 :8 ;	// 23:16
}PE_E60_SHP_2K_DJ_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc9008b7cL shp_dj_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g2_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g2_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g2_max                 :8 ;	// 23:16
}PE_E60_SHP_2K_DJ_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc9008b80L shp_dj_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_base                   :8 ,	// 7:0
	reg_dj_soft_sel_1357_gain          :8 ,	// 15:8
	reg_dj_soft_single_match_en        :1 ;	// 16:16
}PE_E60_SHP_2K_DJ_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9008b90L shp_db_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_detour                :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_dir_blur_buf_detour            :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_dir_blur_en                    :1 ;	// 8:8
}PE_E60_SHP_2K_DB_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008b94L shp_db_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_base                  :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dir_blur_gain                  :8 ;	// 23:16
}PE_E60_SHP_2K_DB_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ba0L shp_dj_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win0_en                 :1 ,	// 0:0
	reg_win_dj_win1_en                 :1 ,	// 1:1
	reg_win_dj_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dj_win_outside             :1 ,	// 6:6
	reg_win_dj_win_en                  :1 ,	// 7:7
	reg_win_dj_bdr_alpha               :5 ,	// 12:8
	reg_win_dj_bdr_wid                 :2 ,	// 14:13
	reg_win_dj_bdr_en                  :1 ,	// 15:15
	reg_win_dj_cr5                     :5 ,	// 20:16
	reg_win_dj_cb5                     :5 ,	// 25:21
	reg_win_dj_yy6                     :6 ;	// 31:26
}PE_E60_SHP_2K_DJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008ba4L shp_dj_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y0               :12;	// 27:16
}PE_E60_SHP_2K_DJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ba8L shp_dj_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y1               :12;	// 27:16
}PE_E60_SHP_2K_DJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008bacL shp_dj_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y0               :12;	// 27:16
}PE_E60_SHP_2K_DJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008bb0L shp_dj_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y1               :12;	// 27:16
}PE_E60_SHP_2K_DJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008d00L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_E60_SHP_2K_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008d04L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_E60_SHP_2K_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008d08L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_E60_SHP_2K_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008d0cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_E60_SHP_2K_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008d10L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_E60_SHP_2K_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008d14L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_E60_SHP_2K_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008d60L shp_core_fd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_2K_CORE_FD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008d64L shp_core_fd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_2K_CORE_FD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008d68L shp_core_fd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_2K_CORE_FD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008d6cL shp_core_fd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_2K_CORE_FD_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008e00L shp_core_tmap_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_window0;	// 31:0
}PE_E60_SHP_2K_CORE_TMAP_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008e04L shp_core_tmap_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_window1;	// 31:0
}PE_E60_SHP_2K_CORE_TMAP_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008e08L shp_core_tmap_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_0                   :16,	// 15:0
	ro_tmap_status_1                   :16;	// 31:16
}PE_E60_SHP_2K_CORE_TMAP_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008e0cL shp_core_tmap_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_2                   :16,	// 15:0
	ro_tmap_status_3                   :16;	// 31:16
}PE_E60_SHP_2K_CORE_TMAP_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008e10L shp_core_tmap_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_4                   :16,	// 15:0
	ro_tmap_status_5                   :16;	// 31:16
}PE_E60_SHP_2K_CORE_TMAP_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008e14L shp_core_tmap_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_6                   :16,	// 15:0
	ro_tmap_status_7                   :16;	// 31:16
}PE_E60_SHP_2K_CORE_TMAP_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008e18L shp_core_tmap_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_8                   :16,	// 15:0
	ro_tmap_status_9                   :16;	// 31:16
}PE_E60_SHP_2K_CORE_TMAP_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008e1cL shp_core_tmap_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_10                  :16,	// 15:0
	ro_tmap_status_11                  :16;	// 31:16
}PE_E60_SHP_2K_CORE_TMAP_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008ef0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cvd_pattern_detect                 :1 ,	//reserved
	color_bar                          :1 ,	//reserved
	vfy_glb_en                         :1 ;	//VFILTER_CTRL_01, reg_glb_vflt_en
}PE_E60_SHP_2K_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008ef4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_2K_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008ef8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_2K_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008efcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_E60_SHP_2K_FSW_CTRL_03_T;


/*-----------------------------------------------------------------------------
                             0xc9009c00L sr_merge_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sr_merge_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_sr_merge_demo_mode_en          :1 ,	// 4:4
	reg_sr_merge_demo_mode             :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_sr_merge_master_gain           :8 ,	// 15:8
	reg_sr_merge_ti_en                 :1 ,	// 16:16
	reserved03                         :3 ,	// reserved
	reg_sr_merge_ti_gain               :8 ,	// 27:20
	reg_sr_merge_debug_mode            :3 ;	// 30:28
}SRE_E60_SR_MERGE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c04L sr_merge_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sr_merge_width                 :16,	// 15:0
	reg_sr_merge_height                :16;	// 31:16
}SRE_E60_SR_MERGE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c08L sr_merge_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sr_merge_demo_start_pts_x0     :16,	// 15:0
	reg_sr_merge_demo_start_pts_y0     :16;	// 31:16
}SRE_E60_SR_MERGE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c0cL sr_merge_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sr_merge_demo_end_pts_x1       :16,	// 15:0
	reg_sr_merge_demo_end_pts_y1       :16;	// 31:16
}SRE_E60_SR_MERGE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009c10L sr_merge_spatial_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_residual_blur_en               :1 ;	// 0:0
}SRE_E60_SR_MERGE_SPATIAL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c14L sr_merge_spatial_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_residual_blur_filt_00          :4 ,	// 3:0
	reg_residual_blur_filt_01          :4 ,	// 7:4
	reg_residual_blur_filt_02          :4 ,	// 11:8
	reg_residual_blur_filt_10          :4 ,	// 15:12
	reg_residual_blur_filt_11          :4 ,	// 19:16
	reg_residual_blur_filt_12          :4 ;	// 23:20
}SRE_E60_SR_MERGE_SPATIAL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c20L sr_merge_mmd_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_en                         :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_mmd_tap_size                   :4 ;	// 7:4
}SRE_E60_SR_MERGE_MMD_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c24L sr_merge_mmd_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_diff_lut_y0                :8 ,	// 7:0
	reg_mmd_diff_lut_x0                :8 ,	// 15:8
	reg_mmd_diff_lut_y1                :8 ,	// 23:16
	reg_mmd_diff_lut_x1                :8 ;	// 31:24
}SRE_E60_SR_MERGE_MMD_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c28L sr_merge_mmd_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_diff_lut_y2                :8 ,	// 7:0
	reg_mmd_diff_lut_x2                :8 ,	// 15:8
	reg_mmd_diff_lut_y3                :8 ,	// 23:16
	reg_mmd_diff_lut_x3                :8 ;	// 31:24
}SRE_E60_SR_MERGE_MMD_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c2cL sr_merge_mmd_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_diff_lut_y4                :8 ,	// 7:0
	reg_mmd_diff_lut_x4                :8 ,	// 15:8
	reg_mmd_diff_lut_y5                :8 ,	// 23:16
	reg_mmd_diff_lut_x5                :8 ;	// 31:24
}SRE_E60_SR_MERGE_MMD_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009c30L sr_merge_mmd_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_diff_lut_y6                :8 ,	// 7:0
	reg_mmd_diff_lut_x6                :8 ,	// 15:8
	reg_mmd_diff_lut_y7                :8 ,	// 23:16
	reg_mmd_diff_lut_x7                :8 ;	// 31:24
}SRE_E60_SR_MERGE_MMD_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009c34L sr_merge_mmd_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ti_gain_lut_y0                 :8 ,	// 7:0
	reg_ti_gain_lut_x0                 :8 ,	// 15:8
	reg_ti_gain_lut_y1                 :8 ,	// 23:16
	reg_ti_gain_lut_x1                 :8 ;	// 31:24
}SRE_E60_SR_MERGE_MMD_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009c38L sr_merge_mmd_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ti_gain_lut_y2                 :8 ,	// 7:0
	reg_ti_gain_lut_x2                 :8 ,	// 15:8
	reg_ti_gain_lut_y3                 :8 ,	// 23:16
	reg_ti_gain_lut_x3                 :8 ;	// 31:24
}SRE_E60_SR_MERGE_MMD_06_T;
/*-----------------------------------------------------------------------------
                             0xc9009c50L sr_merge_sobel_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sobel_mode                     :4 ;	// 3:0
}SRE_E60_SR_MERGE_SOBEL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c54L sr_merge_sobel_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sobel_lut_y0                   :8 ,	// 7:0
	reg_sobel_lut_x0                   :8 ,	// 15:8
	reg_sobel_lut_y1                   :8 ,	// 23:16
	reg_sobel_lut_x1                   :8 ;	// 31:24
}SRE_E60_SR_MERGE_SOBEL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c58L sr_merge_sobel_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sobel_lut_y2                   :8 ,	// 7:0
	reg_sobel_lut_x2                   :8 ,	// 15:8
	reg_sobel_lut_y3                   :8 ,	// 23:16
	reg_sobel_lut_x3                   :8 ;	// 31:24
}SRE_E60_SR_MERGE_SOBEL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c70L sr_merge_nr_gain_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nr_gain_en                     :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_nr_gain_th                     :10;	// 13:4
}SRE_E60_SR_MERGE_NR_GAIN_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c74L sr_merge_nr_gain_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nr_gain_lut_y0                 :8 ,	// 7:0
	reg_nr_gain_lut_x0                 :8 ,	// 15:8
	reg_nr_gain_lut_y1                 :8 ,	// 23:16
	reg_nr_gain_lut_x1                 :8 ;	// 31:24
}SRE_E60_SR_MERGE_NR_GAIN_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c78L sr_merge_nr_gain_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nr_gain_lut_y2                 :8 ,	// 7:0
	reg_nr_gain_lut_x2                 :8 ,	// 15:8
	reg_nr_gain_lut_y3                 :8 ,	// 23:16
	reg_nr_gain_lut_x3                 :8 ;	// 31:24
}SRE_E60_SR_MERGE_NR_GAIN_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c90L sr_merge_blend_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_en                   :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_blend_flat_threshold           :4 ,	// 7:4
	reserved02                         :12,	// reserved
	reg_blend_amp_weight               :12;	// 31:20
}SRE_E60_SR_MERGE_BLEND_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009c94L sr_merge_blend_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_y1                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_blend_lut_x1                   :10;	// 25:16
}SRE_E60_SR_MERGE_BLEND_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009c98L sr_merge_blend_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_y0                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_blend_lut_x0                   :10;	// 25:16
}SRE_E60_SR_MERGE_BLEND_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009c9cL sr_merge_blend_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_y3                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_blend_lut_x3                   :10;	// 25:16
}SRE_E60_SR_MERGE_BLEND_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009ca0L sr_merge_blend_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_lut_y2                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_blend_lut_x2                   :10;	// 25:16
}SRE_E60_SR_MERGE_BLEND_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009d00L sr_merge_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_E60_SR_MERGE_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009d04L sr_merge_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :16,	// 15:0
	reg_mon_in_hori_cnt                :16;	// 31:16
}SRE_E60_SR_MERGE_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009d08L sr_merge_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :16,	// 15:0
	reg_mon_out_hori_cnt               :16;	// 31:16
}SRE_E60_SR_MERGE_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009d0cL sr_merge_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :16,	// 15:0
	reg_mon_fin_in_vert_cnt            :16;	// 31:16
}SRE_E60_SR_MERGE_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9009d10L sr_merge_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}SRE_E60_SR_MERGE_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9009d14L sr_merge_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}SRE_E60_SR_MERGE_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9009df0L sr_merge_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_E60_SR_MERGE_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9009df4L sr_merge_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_E60_SR_MERGE_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9009df8L sr_merge_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_E60_SR_MERGE_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9009dfcL sr_merge_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}SRE_E60_SR_MERGE_FSW_CTRL_03_T;

typedef struct
{ 
	PE_E60_SHP_CHR_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_E60_SHP_CHR_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_E60_SHP_CHR_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	UINT32                                            reserved3[253];	//0xc-0x3fc
	PE_E60_SHP_CDJ_CTRL_00_T                          shp_cdj_ctrl_00;	//0x0400
	PE_E60_SHP_CDJ_CTRL_01_T                          shp_cdj_ctrl_01;	//0x0404
	PE_E60_SHP_CDJ_CTRL_02_T                          shp_cdj_ctrl_02;	//0x0408
	PE_E60_SHP_CDJ_CTRL_03_T                          shp_cdj_ctrl_03;	//0x040C
	PE_E60_SHP_CDJ_CTRL_04_T                          shp_cdj_ctrl_04;	//0x0410
	PE_E60_SHP_CDJ_CTRL_05_T                          shp_cdj_ctrl_05;	//0x0414
	PE_E60_SHP_CDJ_CTRL_06_T                          shp_cdj_ctrl_06;	//0x0418
	PE_E60_SHP_CDJ_CTRL_07_T                          shp_cdj_ctrl_07;	//0x041C
	PE_E60_SHP_CDJ_CTRL_08_T                          shp_cdj_ctrl_08;	//0x0420
	PE_E60_SHP_CDJ_CTRL_09_T                          shp_cdj_ctrl_09;	//0x0424
	PE_E60_SHP_CDJ_CTRL_0A_T                          shp_cdj_ctrl_0a;	//0x0428
	PE_E60_SHP_CDJ_CTRL_0B_T                          shp_cdj_ctrl_0b;	//0x042C
	PE_E60_SHP_CDJ_CTRL_0C_T                          shp_cdj_ctrl_0c;	//0x0430
	PE_E60_SHP_CDJ_CTRL_0D_T                          shp_cdj_ctrl_0d;	//0x0434
	PE_E60_SHP_CDJ_CTRL_0E_T                          shp_cdj_ctrl_0e;	//0x0438
	PE_E60_SHP_CDJ_CTRL_0F_T                          shp_cdj_ctrl_0f;	//0x043C
	PE_E60_SHP_CDJ_CTRL_10_T                          shp_cdj_ctrl_10;	//0x0440
	PE_E60_SHP_CDJ_CTRL_11_T                          shp_cdj_ctrl_11;	//0x0444
	PE_E60_SHP_CDJ_CTRL_12_T                          shp_cdj_ctrl_12;	//0x0448
	PE_E60_SHP_CDJ_CTRL_13_T                          shp_cdj_ctrl_13;	//0x044C
	PE_E60_SHP_CDJ_CTRL_14_T                          shp_cdj_ctrl_14;	//0x0450
	PE_E60_SHP_CDJ_CTRL_15_T                          shp_cdj_ctrl_15;	//0x0454
	PE_E60_SHP_CDJ_CTRL_16_T                          shp_cdj_ctrl_16;	//0x0458
	PE_E60_SHP_CDJ_CTRL_17_T                          shp_cdj_ctrl_17;	//0x045C
	PE_E60_SHP_CDJ_CTRL_18_T                          shp_cdj_ctrl_18;	//0x0460
	PE_E60_SHP_CDJ_CTRL_19_T                          shp_cdj_ctrl_19;	//0x0464
	PE_E60_SHP_CDJ_CTRL_1A_T                          shp_cdj_ctrl_1a;	//0x0468
	PE_E60_SHP_CDJ_CTRL_1B_T                          shp_cdj_ctrl_1b;	//0x046C
	PE_E60_SHP_CDJ_CTRL_1C_T                          shp_cdj_ctrl_1c;	//0x0470
	PE_E60_SHP_CDJ_CTRL_1D_T                          shp_cdj_ctrl_1d;	//0x0474
	PE_E60_SHP_CDJ_CTRL_1E_T                          shp_cdj_ctrl_1e;	//0x0478
	PE_E60_SHP_CDJ_CTRL_1F_T                          shp_cdj_ctrl_1f;	//0x047C
	PE_E60_SHP_CDJ_CTRL_20_T                          shp_cdj_ctrl_20;	//0x0480
	UINT32                                            reserved36[3];	//0x484-0x48c
	PE_E60_SHP_CDIR_BLUR_CTRL_00_T                    shp_cdir_blur_ctrl_00;	//0x0490
	PE_E60_SHP_CDIR_BLUR_CTRL_01_T                    shp_cdir_blur_ctrl_01;	//0x0494
	UINT32                                            reserved38[2];	//0x498-0x49c
	PE_E60_SHP_CDJ_WIN_CTRL_00_T                      shp_cdj_win_ctrl_00;	//0x04A0
	PE_E60_SHP_CDJ_WIN_CTRL_01_T                      shp_cdj_win_ctrl_01;	//0x04A4
	PE_E60_SHP_CDJ_WIN_CTRL_02_T                      shp_cdj_win_ctrl_02;	//0x04A8
	PE_E60_SHP_CDJ_WIN_CTRL_03_T                      shp_cdj_win_ctrl_03;	//0x04AC
	PE_E60_SHP_CDJ_WIN_CTRL_04_T                      shp_cdj_win_ctrl_04;	//0x04B0
	UINT32                                            reserved43[83];	//0x4b4-0x5fc
	PE_E60_SHP_CHR_CORE_STAT_00_T                         shp_core_stat_00;	//0x0600
	PE_E60_SHP_CHR_CORE_STAT_01_T                         shp_core_stat_01;	//0x0604
	PE_E60_SHP_CHR_CORE_STAT_02_T                         shp_core_stat_02;	//0x0608
	PE_E60_SHP_CHR_CORE_STAT_03_T                         shp_core_stat_03;	//0x060C
	PE_E60_SHP_CHR_CORE_STAT_04_T                         shp_core_stat_04;	//0x0610
	PE_E60_SHP_CHR_CORE_STAT_05_T                         shp_core_stat_05;	//0x0614
	UINT32                                            reserved49[54];	//0x618-0x6ec
	PE_E60_SHP_CHR_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x06F0
	PE_E60_SHP_CHR_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x06F4
	PE_E60_SHP_CHR_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x06F8
	PE_E60_SHP_CHR_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x06FC
}PE_SR_CHR_SHP_REG_E60_T;

typedef struct
{ 
	PE_E60_SHP_2K_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_E60_SHP_2K_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_E60_SHP_2K_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	PE_E60_SHP_2K_CORE_CTRL_03_T                         shp_core_ctrl_03;	//0x000C
	UINT32                                            reserved4[12];	//0x10-0x3c
	PE_E60_SHP_2K_PAT_GEN_CTRL_00_T                      shp_pat_gen_ctrl_00;	//0x0040
	UINT32                                            reserved5[43];	//0x44-0xec
	PE_E60_SHP_2K_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x00F0
	UINT32                                            reserved6[3];	//0xf4-0xfc
	PE_E60_SHP_2K_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0100
	PE_E60_SHP_2K_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0104
	PE_E60_SHP_2K_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0108
	PE_E60_SHP_2K_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x010C
	PE_E60_SHP_2K_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0110
	PE_E60_SHP_2K_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0114
	PE_E60_SHP_2K_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0118
	PE_E60_SHP_2K_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x011C
	PE_E60_SHP_2K_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0120
	PE_E60_SHP_2K_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0124
	PE_E60_SHP_2K_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0128
	PE_E60_SHP_2K_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x012C
	PE_E60_SHP_2K_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0130
	PE_E60_SHP_2K_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0134
	PE_E60_SHP_2K_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0138
	PE_E60_SHP_2K_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x013C
	PE_E60_SHP_2K_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0140
	PE_E60_SHP_2K_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0144
	PE_E60_SHP_2K_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0148
	PE_E60_SHP_2K_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_E60_SHP_2K_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_E60_SHP_2K_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_E60_SHP_2K_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	UINT32                                            reserved29;	//0x15c
	PE_E60_SHP_2K_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_E60_SHP_2K_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_E60_SHP_2K_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_E60_SHP_2K_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_E60_SHP_2K_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_E60_SHP_2K_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_E60_SHP_2K_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_E60_SHP_2K_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_E60_SHP_2K_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_E60_SHP_2K_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_E60_SHP_2K_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_E60_SHP_2K_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_E60_SHP_2K_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_E60_SHP_2K_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	UINT32                                            reserved43[2];	//0x198-0x19c
	PE_E60_SHP_2K_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_E60_SHP_2K_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_E60_SHP_2K_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_E60_SHP_2K_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_E60_SHP_2K_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	UINT32                                            reserved48[3];	//0x1b4-0x1bc
	PE_E60_SHP_2K_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_E60_SHP_2K_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_E60_SHP_2K_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_E60_SHP_2K_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_E60_SHP_2K_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_E60_SHP_2K_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_E60_SHP_2K_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_E60_SHP_2K_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_E60_SHP_2K_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_E60_SHP_2K_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_E60_SHP_2K_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_E60_SHP_2K_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_E60_SHP_2K_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_E60_SHP_2K_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_E60_SHP_2K_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_E60_SHP_2K_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_E60_SHP_2K_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_E60_SHP_2K_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_E60_SHP_2K_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_E60_SHP_2K_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_E60_SHP_2K_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	UINT32                                            reserved69[3];	//0x214-0x21c
	PE_E60_SHP_2K_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_E60_SHP_2K_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_E60_SHP_2K_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_E60_SHP_2K_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_E60_SHP_2K_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	UINT32                                            reserved74[3];	//0x234-0x23c
	PE_E60_SHP_2K_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_E60_SHP_2K_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_E60_SHP_2K_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_E60_SHP_2K_TGEN_CTRL_03_T                         shp_tgen_ctrl_03;	//0x024C
	UINT32                                            reserved78;	//0x250
	PE_E60_SHP_2K_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_E60_SHP_2K_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_E60_SHP_2K_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_E60_SHP_2K_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_E60_SHP_2K_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_E60_SHP_2K_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_E60_SHP_2K_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_E60_SHP_2K_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_E60_SHP_2K_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	UINT32                                            reserved87[2];	//0x278-0x27c
	PE_E60_SHP_2K_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_E60_SHP_2K_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_E60_SHP_2K_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_E60_SHP_2K_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_E60_SHP_2K_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_E60_SHP_2K_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_E60_SHP_2K_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_E60_SHP_2K_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_E60_SHP_2K_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_E60_SHP_2K_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_E60_SHP_2K_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_E60_SHP_2K_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_E60_SHP_2K_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_E60_SHP_2K_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_E60_SHP_2K_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_E60_SHP_2K_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_E60_SHP_2K_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_E60_SHP_2K_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_E60_SHP_2K_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_E60_SHP_2K_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_E60_SHP_2K_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_E60_SHP_2K_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_E60_SHP_2K_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_E60_SHP_2K_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_E60_SHP_2K_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_E60_SHP_2K_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_E60_SHP_2K_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_E60_SHP_2K_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_E60_SHP_2K_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_E60_SHP_2K_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_E60_SHP_2K_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_E60_SHP_2K_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_E60_SHP_2K_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_E60_SHP_2K_NNTG_CTRL_01_T                         shp_nntg_ctrl_01;	//0x0304
	PE_E60_SHP_2K_NNTG_CTRL_02_T                         shp_nntg_ctrl_02;	//0x0308
	PE_E60_SHP_2K_NNTG_CTRL_03_T                         shp_nntg_ctrl_03;	//0x030C
	PE_E60_SHP_2K_NNTG_CTRL_04_T                         shp_nntg_ctrl_04;	//0x0310
	PE_E60_SHP_2K_NNTG_CTRL_05_T                         shp_nntg_ctrl_05;	//0x0314
	UINT32                                            reserved125[5];	//0x318-0x328
	PE_E60_SHP_2K_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_E60_SHP_2K_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_E60_SHP_2K_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_E60_SHP_2K_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_E60_SHP_2K_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_E60_SHP_2K_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_E60_SHP_2K_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_E60_SHP_2K_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_E60_SHP_2K_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_E60_SHP_2K_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_E60_SHP_2K_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	UINT32                                            reserved136[2];	//0x358-0x35c
	PE_E60_SHP_2K_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_E60_SHP_2K_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_E60_SHP_2K_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	UINT32                                            reserved139[13];	//0x36c-0x39c
	PE_E60_SHP_2K_DP_WIN_CTRL_00_T                       shp_dp_win_ctrl_00;	//0x03A0
	PE_E60_SHP_2K_DP_WIN_CTRL_01_T                       shp_dp_win_ctrl_01;	//0x03A4
	PE_E60_SHP_2K_DP_WIN_CTRL_02_T                       shp_dp_win_ctrl_02;	//0x03A8
	PE_E60_SHP_2K_DP_WIN_CTRL_03_T                       shp_dp_win_ctrl_03;	//0x03AC
	PE_E60_SHP_2K_DP_WIN_CTRL_04_T                       shp_dp_win_ctrl_04;	//0x03B0
	UINT32                                            reserved144[3];	//0x3b4-0x3bc
	PE_E60_SHP_2K_FD_REGION_TEXT_00_T                    shp_fd_region_text_00;	//0x03C0
	PE_E60_SHP_2K_FD_REGION_TEXT_01_T                    shp_fd_region_text_01;	//0x3C4
	PE_E60_SHP_2K_FD_REGION_TEXT_02_T                    shp_fd_region_text_02;	//0x3C8
	PE_E60_SHP_2K_FD_TMAP_TEMP_00_T                      shp_fd_tmap_temp_00;	//0x03CC
	PE_E60_SHP_2K_FD_TMAP_TEMP_01_T                      shp_fd_tmap_temp_01;	//0x3D0
	PE_E60_SHP_2K_FD_TMAP_TEMP_02_T                      shp_fd_tmap_temp_02;	//0x3D4
	PE_E60_SHP_2K_FD_TMAP_TEMP_03_T                      shp_fd_tmap_temp_03;	//0x3D8
	PE_E60_SHP_2K_FD_TMAP_TEMP_04_T                      shp_fd_tmap_temp_04;	//0x3DC
	PE_E60_SHP_2K_FD_TMAP_TEMP_05_T                      shp_fd_tmap_temp_05;	//0x3E0
	PE_E60_SHP_2K_FD_TMAP_TEMP_06_T                      shp_fd_tmap_temp_06;	//0x3E4
	PE_E60_SHP_2K_FD_TMAP_TEMP_07_T                      shp_fd_tmap_temp_07;	//0x3E8
	PE_E60_SHP_2K_FD_TMAP_TEMP_08_T                      shp_fd_tmap_temp_08;	//0x3EC
	PE_E60_SHP_2K_FD_TMAP_TEMP_09_T                      shp_fd_tmap_temp_09;	//0x03F0
	PE_E60_SHP_2K_FD_TMAP_TEMP_0A_T                      shp_fd_tmap_temp_0a;	//0x03F4
	PE_E60_SHP_2K_FD_TMAP_TEMP_0B_T                      shp_fd_tmap_temp_0b;	//0x03F8
	PE_E60_SHP_2K_FD_TMAP_TEMP_0C_T                      shp_fd_tmap_temp_0c;	//0x03FC
	PE_E60_SHP_2K_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_E60_SHP_2K_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_E60_SHP_2K_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_E60_SHP_2K_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_E60_SHP_2K_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_E60_SHP_2K_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_E60_SHP_2K_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_E60_SHP_2K_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_E60_SHP_2K_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_E60_SHP_2K_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_E60_SHP_2K_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_E60_SHP_2K_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_E60_SHP_2K_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_E60_SHP_2K_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_E60_SHP_2K_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_E60_SHP_2K_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_E60_SHP_2K_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_E60_SHP_2K_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_E60_SHP_2K_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_E60_SHP_2K_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_E60_SHP_2K_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_E60_SHP_2K_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_E60_SHP_2K_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_E60_SHP_2K_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_E60_SHP_2K_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_E60_SHP_2K_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_E60_SHP_2K_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_E60_SHP_2K_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_E60_SHP_2K_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_E60_SHP_2K_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_E60_SHP_2K_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_E60_SHP_2K_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_E60_SHP_2K_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	UINT32                                            reserved193[3];	//0x484-0x48c
	PE_E60_SHP_2K_DB_CTRL_00_T                           shp_db_ctrl_00;	//0x0490
	PE_E60_SHP_2K_DB_CTRL_01_T                           shp_db_ctrl_01;	//0x0494
	UINT32                                            reserved195[2];	//0x498-0x49c
	PE_E60_SHP_2K_DJ_WIN_CTRL_00_T                       shp_dj_win_ctrl_00;	//0x04A0
	PE_E60_SHP_2K_DJ_WIN_CTRL_01_T                       shp_dj_win_ctrl_01;	//0x04A4
	PE_E60_SHP_2K_DJ_WIN_CTRL_02_T                       shp_dj_win_ctrl_02;	//0x04A8
	PE_E60_SHP_2K_DJ_WIN_CTRL_03_T                       shp_dj_win_ctrl_03;	//0x04AC
	PE_E60_SHP_2K_DJ_WIN_CTRL_04_T                       shp_dj_win_ctrl_04;	//0x04B0
	UINT32                                            reserved200[83];	//0x4b4-0x5fc
	PE_E60_SHP_2K_CORE_STAT_00_T                         shp_core_stat_00;	//0x0600
	PE_E60_SHP_2K_CORE_STAT_01_T                         shp_core_stat_01;	//0x0604
	PE_E60_SHP_2K_CORE_STAT_02_T                         shp_core_stat_02;	//0x0608
	PE_E60_SHP_2K_CORE_STAT_03_T                         shp_core_stat_03;	//0x060C
	PE_E60_SHP_2K_CORE_STAT_04_T                         shp_core_stat_04;	//0x0610
	PE_E60_SHP_2K_CORE_STAT_05_T                         shp_core_stat_05;	//0x0614
	UINT32                                            reserved206[18];	//0x618-0x65c
	PE_E60_SHP_2K_CORE_FD_STAT_00_T                      shp_core_fd_stat_00;	//0x0660
	PE_E60_SHP_2K_CORE_FD_STAT_01_T                      shp_core_fd_stat_01;	//0x0664
	PE_E60_SHP_2K_CORE_FD_STAT_02_T                      shp_core_fd_stat_02;	//0x0668
	PE_E60_SHP_2K_CORE_FD_STAT_03_T                      shp_core_fd_stat_03;	//0x066C
	UINT32                                            reserved210[36];	//0x670-0x6fc
	PE_E60_SHP_2K_CORE_TMAP_STAT_00_T                    shp_core_tmap_stat_00;	//0x0700
	PE_E60_SHP_2K_CORE_TMAP_STAT_01_T                    shp_core_tmap_stat_01;	//0x0704
	PE_E60_SHP_2K_CORE_TMAP_STAT_02_T                    shp_core_tmap_stat_02;	//0x0708
	PE_E60_SHP_2K_CORE_TMAP_STAT_03_T                    shp_core_tmap_stat_03;	//0x070C
	PE_E60_SHP_2K_CORE_TMAP_STAT_04_T                    shp_core_tmap_stat_04;	//0x0710
	PE_E60_SHP_2K_CORE_TMAP_STAT_05_T                    shp_core_tmap_stat_05;	//0x0714
	PE_E60_SHP_2K_CORE_TMAP_STAT_06_T                    shp_core_tmap_stat_06;	//0x0718
	PE_E60_SHP_2K_CORE_TMAP_STAT_07_T                    shp_core_tmap_stat_07;	//0x071C
	UINT32                                            reserved218[52];	//0x720-0x7ec
	PE_E60_SHP_2K_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x07F0
	PE_E60_SHP_2K_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x07F4
	PE_E60_SHP_2K_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x07F8
	PE_E60_SHP_2K_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x07FC
}PE_SR_2K_SHP_REG_E60_T;

typedef struct
{ 
	SRE_E60_SR_MERGE_CTRL_00_T                        sr_merge_ctrl_00;	//0x0000
	SRE_E60_SR_MERGE_CTRL_01_T                        sr_merge_ctrl_01;	//0x0004
	SRE_E60_SR_MERGE_CTRL_02_T                        sr_merge_ctrl_02;	//0x0008
	SRE_E60_SR_MERGE_CTRL_03_T                        sr_merge_ctrl_03;	//0x000C
	SRE_E60_SR_MERGE_SPATIAL_00_T                     sr_merge_spatial_00;	//0x0010
	SRE_E60_SR_MERGE_SPATIAL_01_T                     sr_merge_spatial_01;	//0x0014
	UINT32                                            reserved6[2];	//0x18-0x1c
	SRE_E60_SR_MERGE_MMD_00_T                         sr_merge_mmd_00;	//0x0020
	SRE_E60_SR_MERGE_MMD_01_T                         sr_merge_mmd_01;	//0x0024
	SRE_E60_SR_MERGE_MMD_02_T                         sr_merge_mmd_02;	//0x0028
	SRE_E60_SR_MERGE_MMD_03_T                         sr_merge_mmd_03;	//0x002C
	SRE_E60_SR_MERGE_MMD_04_T                         sr_merge_mmd_04;	//0x0030
	SRE_E60_SR_MERGE_MMD_05_T                         sr_merge_mmd_05;	//0x0034
	SRE_E60_SR_MERGE_MMD_06_T                         sr_merge_mmd_06;	//0x0038
	UINT32                                            reserved13[5];	//0x3c-0x4c
	SRE_E60_SR_MERGE_SOBEL_00_T                       sr_merge_sobel_00;	//0x0050
	SRE_E60_SR_MERGE_SOBEL_01_T                       sr_merge_sobel_01;	//0x0054
	SRE_E60_SR_MERGE_SOBEL_02_T                       sr_merge_sobel_02;	//0x0058
	UINT32                                            reserved16[5];	//0x5c-0x6c
	SRE_E60_SR_MERGE_NR_GAIN_00_T                     sr_merge_nr_gain_00;	//0x0070
	SRE_E60_SR_MERGE_NR_GAIN_01_T                     sr_merge_nr_gain_01;	//0x0074
	SRE_E60_SR_MERGE_NR_GAIN_02_T                     sr_merge_nr_gain_02;	//0x0078
	UINT32                                            reserved19[5];	//0x7c-0x8c
	SRE_E60_SR_MERGE_BLEND_00_T                       sr_merge_blend_00;	//0x0090
	SRE_E60_SR_MERGE_BLEND_01_T                       sr_merge_blend_01;	//0x0094
	SRE_E60_SR_MERGE_BLEND_02_T                       sr_merge_blend_02;	//0x0098
	SRE_E60_SR_MERGE_BLEND_03_T                       sr_merge_blend_03;	//0x009C
	SRE_E60_SR_MERGE_BLEND_04_T                       sr_merge_blend_04;	//0x00A0
	UINT32                                            reserved24[23];	//0xa4-0xfc
	SRE_E60_SR_MERGE_CORE_STAT_00_T                   sr_merge_core_stat_00;	//0x0100
	SRE_E60_SR_MERGE_CORE_STAT_01_T                   sr_merge_core_stat_01;	//0x0104
	SRE_E60_SR_MERGE_CORE_STAT_02_T                   sr_merge_core_stat_02;	//0x0108
	SRE_E60_SR_MERGE_CORE_STAT_03_T                   sr_merge_core_stat_03;	//0x010C
	SRE_E60_SR_MERGE_CORE_STAT_04_T                   sr_merge_core_stat_04;	//0x0110
	SRE_E60_SR_MERGE_CORE_STAT_05_T                   sr_merge_core_stat_05;	//0x0114
	UINT32                                            reserved30[54];	//0x118-0x1ec
	SRE_E60_SR_MERGE_FSW_CTRL_00_T                    sr_merge_fsw_ctrl_00;	//0x01F0
	SRE_E60_SR_MERGE_FSW_CTRL_01_T                    sr_merge_fsw_ctrl_01;	//0x01F4
	SRE_E60_SR_MERGE_FSW_CTRL_02_T                    sr_merge_fsw_ctrl_02;	//0x01F8
	SRE_E60_SR_MERGE_FSW_CTRL_03_T                    sr_merge_fsw_ctrl_03;	//0x01FC
}PE_SR_MERG_REG_E60_T;
#endif
#endif
