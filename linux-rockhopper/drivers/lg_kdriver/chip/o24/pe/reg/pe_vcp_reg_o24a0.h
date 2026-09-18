#ifndef _PE_VCP_REG_O24A0_H_
#define _PE_VCP_REG_O24A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCCA23F00 RW 0x0000_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_O24_VSD0_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA23F04 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VSD0_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA23F08 RW 0x0000_0000
	UINT32 enable							:1; //0 //
	UINT32 resvd0							:3;
	UINT32 brightness						:10;	//13:4	//
	UINT32 resvd1							:2;
	UINT32 contrast 						:10;	//25:16 //
	UINT32 resvd2							:6;
	};
}PE_O24_VSD0_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA23F0C RW 0x0000_0000
	UINT32 saturation_en				:1; //0 //
	UINT32 resvd0							:7;
	UINT32 saturation						:8; //15:8	//
	UINT32 brightness						:10;	//25:16 //
	UINT32 resvd1							:6;
	};
}PE_O24_VSD0_VERI_SYS_VERI_3_T;


typedef struct {
	PE_O24_VSD0_VERI_SYS_VERI_0_T                          vsd_veri_vsp0_0;	//0xCCA23F00
	PE_O24_VSD0_VERI_SYS_VERI_1_T                          vsd_veri_vsp0_1;	//0xCCA23F04
	PE_O24_VSD0_VERI_SYS_VERI_2_T                          vsd_veri_vsp1_0;	//0xCCA23F08
	PE_O24_VSD0_VERI_SYS_VERI_3_T                          vsd_veri_vsp1_1;	//0xCCA23F0C
}PE_VSD0_VERI_REG_O24_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCCA21400 RW 0x3FFF_3FFF
	UINT32 mask_pic_init_y_mux_u0_cdc       :1;	//(0,RW,0x01) //
	UINT32 mask_pic_init_c_mux_u0_cdc       :1;	//(1,RW,0x01) //
	UINT32 mask_pic_init_y_mux_u1_cdc       :1;	//(2,RW,0x01) //
	UINT32 mask_pic_init_c_mux_u1_cdc       :1;	//(3,RW,0x01) //
	UINT32 mask_pic_init_y_mux_u2_cdc       :1;	//(4,RW,0x01) //
	UINT32 mask_pic_init_c_mux_u2_cdc       :1;	//(5,RW,0x01) //
	UINT32 mask_pic_init_y_mux_u3_cdc       :1;	//(6,RW,0x01) //
	UINT32 mask_pic_init_c_mux_u3_cdc       :1;	//(7,RW,0x01) //
	UINT32 resvd0                           :4;
	UINT32 mask_pic_init_y_mux_m_wcp        :1;	//(12,RW,0x01) //
	UINT32 mask_pic_init_c_mux_m_wcp        :1;	//(13,RW,0x01) //
	UINT32 resvd1                           :2;
	UINT32 mask_pic_start_y_mux_u0_cdc      :1;	//(16,RW,0x01) //
	UINT32 mask_pic_start_c_mux_u0_cdc      :1;	//(17,RW,0x01) //
	UINT32 mask_pic_start_y_mux_u1_cdc      :1;	//(18,RW,0x01) //
	UINT32 mask_pic_start_c_mux_u1_cdc      :1;	//(19,RW,0x01) //
	UINT32 mask_pic_start_y_mux_u2_cdc      :1;	//(20,RW,0x01) //
	UINT32 mask_pic_start_c_mux_u2_cdc      :1;	//(21,RW,0x01) //
	UINT32 mask_pic_start_y_mux_u3_cdc      :1;	//(22,RW,0x01) //
	UINT32 mask_pic_start_c_mux_u3_cdc      :1;	//(23,RW,0x01) //
	UINT32 resvd2                           :4;
	UINT32 mask_pic_start_y_mux_m_wcp       :1;	//(28,RW,0x01) //
	UINT32 mask_pic_start_c_mux_m_wcp       :1;	//(29,RW,0x01) //
	UINT32 resvd3                           :2;
	};
}PE_O24_VCP_DISP_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21404 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_DISP_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21408 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 vcp_u1_disp_clk_cg               :1;	//(1,RW,0x00) //VCP U1 Disp Clock Gating ON	0 := Off	1 := On
	UINT32 resvd1                           :2;
	UINT32 wcp_m_mix_enable                 :2;	//(5:4,RW,0x00) //for debugging	"00" := main default.	"01" = PIP/R2 full video
	UINT32 resvd2                           :2;
	UINT32 en_bypass_sync_my                :1;	//(8,RW,0x00) //
	UINT32 resvd3                           :23;
	};
}PE_O24_VCP_DISP_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2140C RO 0x2022_0301
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_DISP_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21410 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_CDC_MV_SYNC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21414 RW 0x0000_0000
	UINT32 u0_cdc_y_disp_sreset             :1;	//(0,RW,0x00) //CDC_DISP sreset
	UINT32 u0_cdc_c_disp_sreset             :1;	//(1,RW,0x00) //CDC_DISP sreset
	UINT32 u1_cdc_y_disp_sreset             :1;	//(2,RW,0x00) //CDC_DISP sreset
	UINT32 u1_cdc_c_disp_sreset             :1;	//(3,RW,0x00) //CDC_DISP sreset
	UINT32 u2_cdc_y_disp_sreset             :1;	//(4,RW,0x00) //CDC_DISP sreset
	UINT32 u2_cdc_c_disp_sreset             :1;	//(5,RW,0x00) //CDC_DISP sreset
	UINT32 u3_cdc_y_disp_sreset             :1;	//(6,RW,0x00) //CDC_DISP sreset
	UINT32 u3_cdc_c_disp_sreset             :1;	//(7,RW,0x00) //CDC_DISP sreset
	UINT32 resvd                            :24;
	};
}PE_O24_VCP_CDC_MV_RST_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21420 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y                  :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x                  :13;	//(28:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_U0_WIN_O_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21424 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y                 :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x                 :13;	//(28:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_U0_WIN_O_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21428 RW 0x0000_0000
	UINT32 dbg_size                         :1;	//(0,RW,0x00) //0
	UINT32 resvd0                           :3;
	UINT32 ramp_pat_en                      :2;	//(5:4,RW,0x00) //"00" := bypass	"01" = diagonal
	UINT32 mpg_o_color_sel                  :2;	//(7:6,RW,0x00) //"00" := YC	"01" = Y ONLY	"10" = C ONLY	"11" = peaking
	UINT32 pg_box_bla_en                    :1;	//(8,RW,0x0) //white
	UINT32 pg_box_blu_en                    :1;	//(9,RW,0x0) //white
	UINT32 pg_box_red_en                    :1;	//(10,RW,0x0) //white
	UINT32 pg_box_mag_en                    :1;	//(11,RW,0x0) //white
	UINT32 pg_box_gre_en                    :1;	//(12,RW,0x0) //white
	UINT32 pg_box_cya_en                    :1;	//(13,RW,0x0) //white
	UINT32 pg_box_yel_en                    :1;	//(14,RW,0x0) //white
	UINT32 pg_box_whi_en                    :1;	//(15,RW,0x0) //white
	UINT32 peaking_en                       :1;	//(16,RW,0x00) //peaking control enable
	UINT32 peak_min_max_clip                :1;	//(17,RW,0x00) //min max clipping
	UINT32 resvd1                           :2;
	UINT32 peak_even_odd_sel                :1;	//(20,RW,0x00) //even odd sel
	UINT32 reg_odd_size_dbg                 :1;	//(21,RW,0x00) //boundary process of odd size
	UINT32 resvd2                           :2;
	UINT32 peak_gain                        :8;	//(31:24,RW,0x00) //0x00~0xFF (0 is bypass)
	};
}PE_O24_VCP_U0_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2142C RW 0x0000_0780
	UINT32 peak_hsize                       :12;	//(11:0,RW,0x780) //cdc_win_o_size_x/2 round-up  2P
	UINT32 peak_offset                      :1;	//(12,RW,0x0) //cdc_win_o_pos_x[0]
	UINT32 resvd0                           :2;
	UINT32 peak_manual                      :1;	//(15,RW,0x0) //auto position release for debug
	UINT32 resvd1                           :16;
	};
}PE_O24_VCP_U0_PG_PEAK_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21430 RW 0x0830_0000
	UINT32 cdc_voffset                      :5;	//(4:0,RW,0x0) //CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//(5,RW,0x00) //
	UINT32 cdc_auto_v_half                  :1;	//(6,RW,0x00) //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//(7,RW,0x00) //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//(10:8,RW,0x00) //V repeat scaler mode : extension lines' colors are only "Black"	"000" := all line ready processing.	"001" = x2 : 2^1 th line ready processing.	"010" = x4 : 2^2 th line ready processing.	"011" = x8 : 2^3 th line ready processing.	"100" = x16 : 2^4 th line ready processing.	"101" = x32 : 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//(11,RW,0x00) //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//(14:12,RW,0x00) //"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG	"011" = L scan for FPR_L (normal V-scan)	"100" = R scan for FPR_R (normal V-scan)	"101" = L scan for FPR_L (reverse V-scan)	"110" = R scan for FPR_R (reverse V-scan)
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//(18:16,RW,0x00) //H repeat scaler mode : extension pixels are repeated.	"000" := all pixel ready processing.	"001" = x2 : 2^1 th pixel ready processing.	"010" = x4 : 2^2 th pixel ready processing.	"011" = x8 : 2^3 th pixel ready processing.	"100" = x16 : 2^4 th pixel ready processing.	"101" = x32 : 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//(19,RW,0x00) //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x03) //"11" := 2CH	"10" = 4CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 resvd2                           :4;
	};
}PE_O24_VCP_U0_CDC_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21434 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_U0_CDC_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21438 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_u0_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_u0_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_O24_VCP_U0_CDC_Y_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2143C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_U0_CDC_Y_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21440 RW 0x0830_0000
	UINT32 cdc_voffset                      :5;	//(4:0,RW,0x0) //CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//(5,RW,0x00) //
	UINT32 cdc_auto_v_half                  :1;	//(6,RW,0x00) //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//(7,RW,0x00) //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//(10:8,RW,0x00) //V repeat scaler mode : extension lines' colors are only "Black"	"000" := all line ready processing.	"001" = x2 : 2^1 th line ready processing.	"010" = x4 : 2^2 th line ready processing.	"011" = x8 : 2^3 th line ready processing.	"100" = x16 : 2^4 th line ready processing.	"101" = x32 : 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//(11,RW,0x00) //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//(14:12,RW,0x00) //"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG	"011" = L scan for FPR_L (normal V-scan)	"100" = R scan for FPR_R (normal V-scan)	"101" = L scan for FPR_L (reverse V-scan)	"110" = R scan for FPR_R (reverse V-scan)
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//(18:16,RW,0x00) //H repeat scaler mode : extension pixels are repeated.	"000" := all pixel ready processing.	"001" = x2 : 2^1 th pixel ready processing.	"010" = x4 : 2^2 th pixel ready processing.	"011" = x8 : 2^3 th pixel ready processing.	"100" = x16 : 2^4 th pixel ready processing.	"101" = x32 : 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//(19,RW,0x00) //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x03) //"11" := 2CH	"10" = 4CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 resvd2                           :4;
	};
}PE_O24_VCP_U0_CDC_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21444 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_U0_CDC_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21448 RW 0x0000_0000
	UINT32 set_pic_init_c_mux_u0_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_u0_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_O24_VCP_U0_CDC_C_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2144C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_U0_CDC_C_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21450 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y                  :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x                  :13;	//(28:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_U1_WIN_O_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21454 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y                 :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x                 :13;	//(28:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_U1_WIN_O_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21458 RW 0x0000_0000
	UINT32 dbg_size                         :1;	//(0,RW,0x00) //0
	UINT32 resvd0                           :3;
	UINT32 ramp_pat_en                      :2;	//(5:4,RW,0x00) //"00" := bypass	"01" = diagonal
	UINT32 mpg_o_color_sel                  :2;	//(7:6,RW,0x00) //"00" := YC	"01" = Y ONLY	"10" = C ONLY	"11" = peaking
	UINT32 resvd1                           :8;
	UINT32 peaking_en                       :1;	//(16,RW,0x00) //peaking control enable
	UINT32 peak_min_max_clip                :1;	//(17,RW,0x00) //min max clipping
	UINT32 resvd2                           :2;
	UINT32 peak_even_odd_sel                :1;	//(20,RW,0x00) //even odd sel
	UINT32 reg_odd_size_dbg                 :1;	//(21,RW,0x00) //boundary process of odd size
	UINT32 resvd3                           :2;
	UINT32 peak_gain                        :8;	//(31:24,RW,0x00) //0x00~0xFF (0 is bypass)
	};
}PE_O24_VCP_U1_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2145C RW 0x0000_0780
	UINT32 peak_hsize                       :12;	//(11:0,RW,0x780) //cdc_win_o_size_x/2 round-up  2P
	UINT32 peak_offset                      :1;	//(12,RW,0x0) //cdc_win_o_pos_x[0]
	UINT32 resvd0                           :2;
	UINT32 peak_manual                      :1;	//(15,RW,0x0) //auto position release for debug
	UINT32 resvd1                           :16;
	};
}PE_O24_VCP_U1_PG_PEAK_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21460 RW 0x0830_0000
	UINT32 cdc_voffset                      :5;	//(4:0,RW,0x0) //CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//(5,RW,0x00) //
	UINT32 cdc_auto_v_half                  :1;	//(6,RW,0x00) //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//(7,RW,0x00) //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//(10:8,RW,0x00) //"000" := all line ready processing.	"001" = 2^1 th line ready processing.	"010" = 2^2 th line ready processing.	"011" = 2^3 th line ready processing.	"100" = 2^4 th line ready processing.	"101" = 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//(11,RW,0x00) //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//(14:12,RW,0x00) //"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//(18:16,RW,0x00) //"000" := all pixel ready processing.	"001" = 2^1 th pixel ready processing.	"010" = 2^2 th pixel ready processing.	"011" = 2^3 th pixel ready processing.	"100" = 2^4 th pixel ready processing.	"101" = 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//(19,RW,0x00) //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x03) //"11" := 2CH	"10" = 4CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	"0010" = video R2(T3C).	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 resvd2                           :4;
	};
}PE_O24_VCP_U1_CDC_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21464 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_U1_CDC_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21468 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_u1_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_u1_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0010" = pic_start_y_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_O24_VCP_U1_CDC_Y_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2146C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_U1_CDC_Y_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21470 RW 0x0830_0000
	UINT32 cdc_voffset                      :5;	//(4:0,RW,0x0) //CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//(5,RW,0x00) //
	UINT32 cdc_auto_v_half                  :1;	//(6,RW,0x00) //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//(7,RW,0x00) //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//(10:8,RW,0x00) //"000" := all line ready processing.	"001" = 2^1 th line ready processing.	"010" = 2^2 th line ready processing.	"011" = 2^3 th line ready processing.	"100" = 2^4 th line ready processing.	"101" = 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//(11,RW,0x00) //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//(14:12,RW,0x00) //"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//(18:16,RW,0x00) //"000" := all pixel ready processing.	"001" = 2^1 th pixel ready processing.	"010" = 2^2 th pixel ready processing.	"011" = 2^3 th pixel ready processing.	"100" = 2^4 th pixel ready processing.	"101" = 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//(19,RW,0x00) //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x03) //"11" := 2CH	"10" = 4CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 resvd2                           :4;
	};
}PE_O24_VCP_U1_CDC_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21474 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_U1_CDC_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21478 RW 0x0000_0000
	UINT32 set_pic_init_c_mux_u1_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_u1_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0010" = pic_start_c_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_O24_VCP_U1_CDC_C_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2147C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_U1_CDC_C_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21480 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y_aux              :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x_aux              :13;	//(28:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_U0_WIN_O_POS_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21484 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y_aux             :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x_aux             :13;	//(28:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :2;
	UINT32 cdc_win_aux_auto                 :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_U0_WIN_O_SIZE_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21488 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y_aux              :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x_aux              :13;	//(28:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_U1_WIN_O_POS_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2148C RW 0x0F00_0870
	UINT32 cdc_win_o_size_y_aux             :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x_aux             :13;	//(28:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :2;
	UINT32 cdc_win_aux_auto                 :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_U1_WIN_O_SIZE_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2150C RW 0x0000_0000
	UINT32 h_cnt                            :16;	//(15:0,RW,0x0) //
	UINT32 v_cnt                            :16;	//(31:16,RW,0x0) //
	};
}PE_O24_VCP_SG_MVY_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21510 RW 0x0008_000A
	UINT32 vsync                            :16;	//(15:0,RW,0xA) //10
	UINT32 vfp                              :16;	//(31:16,RW,0x8) //8
	};
}PE_O24_VCP_SG_MVY_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21514 RW 0x0048_0870
	UINT32 va                               :16;	//(15:0,RW,0x870) //2160
	UINT32 vbp                              :16;	//(31:16,RW,0x48) //72
	};
}PE_O24_VCP_SG_MVY_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21518 RW 0x0058_002C
	UINT32 hsync                            :16;	//(15:0,RW,0x2C) //88/2=44 for dual channel(E,O)
	UINT32 hfp                              :16;	//(31:16,RW,0x58) //176/2=88 for dual channel(E,O)
	};
}PE_O24_VCP_SG_MVY_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2151C RW 0x0094_0780
	UINT32 ha                               :16;	//(15:0,RW,0x780) //3840/2=1920 for dual channel(E,O)
	UINT32 hbp                              :16;	//(31:16,RW,0x94) //296/2=148 for dual channel(E,O)
	};
}PE_O24_VCP_SG_MVY_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21520 RW 0x0000_0000
	UINT32 line_start_pos                   :16;	//(15:0,RW,0x0) //should be set to (HFP value+8)
	UINT32 sync_i_h_sel                     :1;	//(16,RW,0x00) //
	UINT32 sync_i_v_sel                     :1;	//(17,RW,0x00) //
	UINT32 sync_i_inv_ha                    :1;	//(18,RW,0x00) //
	UINT32 sync_i_inv_va                    :1;	//(19,RW,0x00) //
	UINT32 sync_o_sel_ha                    :1;	//(20,RW,0x00) //
	UINT32 sync_o_sel_va                    :1;	//(21,RW,0x00) //
	UINT32 sync_o_sel_hs                    :1;	//(22,RW,0x00) //
	UINT32 sync_o_sel_vs                    :1;	//(23,RW,0x00) //
	UINT32 tp_update_hv_zero                :1;	//(24,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 manual_cnt_h_value_en            :1;	//(28,RW,0x00) //
	UINT32 manual_cnt_v_value_en            :1;	//(29,RW,0x00) //
	UINT32 resvd1                           :1;
	UINT32 update_force                     :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_SG_MVY_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21524 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_O24_VCP_SG_MVY_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21528 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_O24_VCP_SG_MVY_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2152C RW 0x0002_8010
	UINT32 auto_ha_delay                    :15;	//(14:0,RW,0x10) //
	UINT32 auto_general_en                  :1;	//(15,RW,0x1) //general delay block enable
	UINT32 auto_va_delay                    :15;	//(30:16,RW,0x2) //
	UINT32 auto_seamless                    :1;	//(31,RW,0x0) //
	};
}PE_O24_VCP_SG_MVY_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21530 RW 0x0002_8010
	UINT32 auto_hs_delay                    :15;	//(14:0,RW,0x10) //
	UINT32 auto_general_en                  :1;	//(15,RW,0x1) //general delay block enable
	UINT32 auto_vs_delay                    :15;	//(30:16,RW,0x2) //
	UINT32 auto_seamless                    :1;	//(31,RW,0x0) //
	};
}PE_O24_VCP_SG_MVY_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21534 RW 0x0000_0000
	UINT32 resvd                            :31;
	UINT32 sync_out_disable                 :1;	//(31,RW,0x0000_0000) //
	};
}PE_O24_VCP_SG_MVY_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215B8 RW 0x0780_0870
	UINT32 pg1ch_win_o_size_y               :14;	//(13:0,RW,0x870) //0x870(2160) for UD, 0x438(1080) for FHD.
	UINT32 resvd0                           :2;
	UINT32 pg1ch_win_o_size_x               :13;	//(28:16,RW,0x780) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_WCP_M_DISP_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215BC RW 0x0000_0000
	UINT32 lattice_pat_en                   :1;	//(0,RW,0x00) //main video 와 blending되어 출력된다.
	UINT32 resvd0                           :3;
	UINT32 ramp_pat_en                      :2;	//(5:4,RW,0x00) //"00" := bypass	"01" = diagonal	"10" = horizontal	"11" = vertical
	UINT32 mpg_o_color_sel                  :2;	//(7:6,RW,0x00) //"00" := YC	"01" = Y ONLY	"10" = C ONLY
	UINT32 border_sel                       :4;	//(11:8,RW,0x00) //"0000" := bypass	"0001" = border w/ white	"0010" = border w/ black	"0011" = border w/ red	"0100" = border w/ green	"0101" = border w/ blue
	UINT32 resvd1                           :3;
	UINT32 status_bar_en                    :1;	//(15,RW,0x00) //lm status monitor
	UINT32 resvd2                           :4;
	UINT32 status0_00_src_sel               :2;	//(21:20,RW,0x00) //"00" := U0Y lm status	"01" = U0C lm status	"10" = U1Y lm status	"11" = U1C lm status
	UINT32 status0_01_src_sel               :2;	//(23:22,RW,0x00) //"00" := U0Y lm status	"01" = U0C lm status	"10" = U1Y lm status	"11" = U1C lm status
	UINT32 status0_02_src_sel               :2;	//(25:24,RW,0x00) //"00" := U0Y lm status	"01" = U0C lm status	"10" = U1Y lm status	"11" = U1C lm status
	UINT32 status0_03_src_sel               :2;	//(27:26,RW,0x00) //"00" := U0Y lm status	"01" = U0C lm status	"10" = U1Y lm status	"11" = U1C lm status
	UINT32 cg_disable                       :1;	//(28,RW,0x00) //0 : Clock gating, 1 : disable CG
	UINT32 resvd3                           :2;
	UINT32 mean_fil_en                      :1;	//(31,RW,0x00) //when 422to 444 , mean_filter_enable	0 := repeated pixel	1  = mean pixel
	};
}PE_O24_VCP_WCP_M_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215C8 RW 0x0000_0000
	UINT32 rd_pel_pos_y                     :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 rd_pel_pos_x                     :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 rd_pel_pat_en                    :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_M_PIXEL_READ_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215CC RW 0x0000_0000
	UINT32 rd_pel_pos_y                     :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 rd_pel_pos_x                     :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 rd_pel_pat_en                    :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215D0 RW 0x0000_0000
	UINT32 even_line_cr                     :8;	//(7:0,RW,0x0) //
	UINT32 even_line_cb                     :8;	//(15:8,RW,0x0) //
	UINT32 even_line_y                      :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 even_line_pat_en                 :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_M_LINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215D4 RW 0x0000_0000
	UINT32 odd_line_cr                      :8;	//(7:0,RW,0x0) //
	UINT32 odd_line_cb                      :8;	//(15:8,RW,0x0) //
	UINT32 odd_line_y                       :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 odd_line_pat_en                  :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_M_LINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215E0 RW 0x0000_0000
	UINT32 rec0_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec0_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec0_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215E4 RW 0x0000_0000
	UINT32 rec0_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec0_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec0_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215E8 RW 0x0000_0000
	UINT32 rec1_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec1_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec1_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215EC RW 0x0000_0000
	UINT32 rec1_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec1_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec1_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_WCP_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215F4 RW 0x8080_8080
	UINT32 w1_clr_dark_cr                   :4;	//(3:0,RW,0x80) //we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 resvd                            :4;
	UINT32 w0_clr_dark_cr                   :8;	//(15:8,RW,0x80) //we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 clr_nac_cr                       :8;	//(23:16,RW,0x80) //U0와 blending 되는 바탕색	we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 clr_bdr_cr                       :8;	//(31:24,RW,0x80) //Border 색지정	we can get 0x200(512) by setting lsb 2bits to "00" internally.
	};
}PE_O24_VCP_WCP_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215F8 RW 0x1080_1080
	UINT32 clr_nac_cb                       :8;	//(7:0,RW,0x80) //U0와 blending 되는 바탕색	we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 clr_nac_y                        :8;	//(15:8,RW,0x10) //U0와 blending 되는 바탕색	we can get 0x40(64) by setting lsb 2bits to "00" internally.
	UINT32 clr_bdr_cb                       :8;	//(23:16,RW,0x80) //Border 색지정	we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 clr_bdr_y                        :8;	//(31:24,RW,0x10) //Border 색 지정	we can get 0x40(64) by setting lsb 2bits to "00" internally.
	};
}PE_O24_VCP_WCP_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA215FC RW 0x1080_1080
	UINT32 w1_clr_dark_cb                   :8;	//(7:0,RW,0x80) //we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 w1_clr_dark_y                    :8;	//(15:8,RW,0x10) //we can get 0x40(64) by setting lsb 2bits to "00" internally.
	UINT32 w0_clr_dark_cb                   :8;	//(23:16,RW,0x80) //we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 w0_clr_dark_y                    :8;	//(31:24,RW,0x10) //we can get 0x40(64) by setting lsb 2bits to "00" internally.
	};
}PE_O24_VCP_WCP_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21600 RW 0x1088_1088
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_WCP_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21604 RW 0x0000_0000
	UINT32 set_w0_imux_ctrl                 :3;	//(2:0,RW,0x00) //"000" := vid0 (U0)	"001" = vid1 (U1)	"010" = vid2 (U2)	"011" = vid3 (U3)
	UINT32 set_w0_dark_en                   :1;	//(3,RW,0x00) //
	UINT32 set_w1_imux_ctrl                 :3;	//(6:4,RW,0x00) //"000" := vid0 (U0)	"001" = vid1 (U1)	"010" = vid2 (U2)	"011" = vid3 (U3)
	UINT32 set_w1_dark_en                   :1;	//(7,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 set_lparity_w0_imux_en           :1;	//(16,RW,0x00) //
	UINT32 set_lparity_w0_imux              :1;	//(17,RW,0x00) //
	UINT32 cg_disable                       :1;	//(18,RW,0x00) //0 : Clock gating, 1 : disable CG  (w0,w1,a0,a1)
	UINT32 resvd1                           :1;
	UINT32 set_lparity_w1_imux_en           :1;	//(20,RW,0x00) //
	UINT32 set_lparity_w1_imux              :1;	//(21,RW,0x00) //
	UINT32 resvd2                           :2;
	UINT32 set_lparity_sync_c               :3;	//(26:24,RW,0x00) //
	UINT32 resvd3                           :1;
	UINT32 set_lparity_sync_y               :3;	//(30:28,RW,0x00) //
	UINT32 resvd4                           :1;
	};
}PE_O24_VCP_WCP_M_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21608 RW 0x0000_0066
	UINT32 y_mod_num                        :3;	//(2:0,RW,0x06) //mod 8%
	UINT32 resvd0                           :1;
	UINT32 c_mod_num                        :3;	//(6:4,RW,0x06) //mod 8%
	UINT32 resvd1                           :9;
	UINT32 last_pixel_padding               :1;	//(16,RW,0x00) //
	UINT32 resvd2                           :15;
	};
}PE_O24_VCP_WCP_M_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2160C RW 0x0000_0000
	UINT32 set_w0_abr_en                    :2;	//(1:0,RW,0x00) //"00" := blend out	"01" = nactive color (DN)	"10" = window0 (UP)	"11" = alpha output
	UINT32 set_w1_abr_en                    :2;	//(3:2,RW,0x00) //"00" := blend out	"01" = nactive color (DN)	"10" = window0 (UP)	"11" = alpha output
	UINT32 resvd0                           :8;
	UINT32 set_w0_awb_cr                    :1;	//(12,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 set_w0_awb_cb                    :1;	//(13,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 set_w0_awb_y                     :1;	//(14,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 resvd1                           :1;
	UINT32 set_w1_awb_cr                    :1;	//(16,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 set_w1_awb_cb                    :1;	//(17,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 set_w1_awb_y                     :1;	//(18,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 resvd2                           :12;
	UINT32 last_pixel_padding_old           :1;	//(31,RW,0x00) //debug
	};
}PE_O24_VCP_WCP_M_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21610 RW 0x0000_0000
	UINT32 w0_clr_alpha                     :8;	//(7:0,RW,0x0) //0x00 : DN (w0_clr_alpha window)	0xFF : UP (Window 1)
	UINT32 w1_clr_alpha                     :8;	//(15:8,RW,0x0) //0x00 : DN (w0_clr_alpha window)	0xFF : UP (Window 1)
	UINT32 resvd                            :16;
	};
}PE_O24_VCP_WCP_M_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21614 RW 0x0000_0000
	UINT32 set_ha_o_mux_ctrl                :4;	//(3:0,RW,0x00) //"0000" := display hactive	"0001" = w0 hactive	"0010" = w1 hactive
	UINT32 set_va_o_mux_ctrl                :4;	//(7:4,RW,0x00) //"0000" := display vactive	"0001" = w0 vactive	"0010" = w1 vactive
	UINT32 set_de_o_mux_ctrl                :4;	//(11:8,RW,0x00) //DE processing for SOSD ONLY	"0000" := display de	"0001" = w0_va&w0_ha	"0010" = w1_va&w1_ha	"0101" = (w0_va&w0_ha) | (w1_va&w1_ha)	"1000" = ~(w0_va&w0_ha)	"1001" = ~(w1_va&w1_ha)	"1100" = ~((w0_va&w0_ha) | (w1_va&w1_ha))
	UINT32 reg4_alpha                       :8;	//(19:12,RW,0x0) //0x00 background or U0   bottom	0xFF U0             or U1   top
	UINT32 resvd                            :3;
	UINT32 w1_clr_alpha_nac_en              :1;	//(23,RW,0x00) //
	UINT32 w1_clr_alpha_nac                 :8;	//(31:24,RW,0x0) //
	};
}PE_O24_VCP_WCP_M_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21618 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_m_wcp         :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_m_wcp        :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 set_pic_init_c_mux_m_wcp         :4;	//(11:8,RW,0x00) //"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_m_wcp        :4;	//(15:12,RW,0x00) //"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 resvd                            :16;
	};
}PE_O24_VCP_WCP_M_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21620 RW 0x0000_0000
	UINT32 pattern_y_pos                    :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pattern_x_pos                    :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_WCP_M_PG_PAT_POS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21624 RW 0x0000_0000
	UINT32 pattern_y_size                   :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pattern_x_size                   :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_WCP_M_PG_PAT_SIZE_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21628 RW 0x0000_0000
	UINT32 pattern_y_pos                    :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pattern_x_pos                    :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_WCP_M_PG_PAT_POS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2162C RW 0x0000_0000
	UINT32 pattern_y_size                   :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pattern_x_size                   :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_WCP_M_PG_PAT_SIZE_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21630 RW 0x0010_8080
	UINT32 blanck_cr                        :8;	//(7:0,RW,0x80) //
	UINT32 blank_cb                         :8;	//(15:8,RW,0x80) //
	UINT32 blank_y                          :8;	//(23:16,RW,0x10) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_PG_PAT_COLOR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21650 RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_O24_VCP_WCP_M_PIXEL_READ_DATA_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21654 RO 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_WCP_M_PIXEL_READ_DATA_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21658 RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_O24_VCP_WCP_M_PIXEL_READ_DATA_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2165C RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_O24_VCP_WCP_M_PIXEL_READ_DATA_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21660 RW 0x0000_0000
	UINT32 win_pos_y0_auto                  :14;	//(13:0,RW,0x0) //Y start position of window.
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0_auto                  :13;	//(28:16,RW,0x0) //X start position of window.
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V0_PARAM_POS_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21664 RW 0x8000_0000
	UINT32 win_size_y_auto                  :14;	//(13:0,RW,0x0) //Y-size of window.
	UINT32 resvd0                           :2;
	UINT32 win_size_x_auto                  :13;	//(28:16,RW,0x0) //X-size of window.
	UINT32 resvd1                           :1;
	UINT32 win_enable_4ch_auto              :1;	//(30,RW,0x00) //1' = 4ch pos/size control	'0' := 2ch pos/size control
	UINT32 win_enable_auto                  :1;	//(31,RW,0x01) //1' := auto pos/size control	'0' = manual pos/size control
	};
}PE_O24_VCP_SG_BDR_V0_PARAM_SIZE_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21668 RW 0x0000_0000
	UINT32 win_pos_y0_auto                  :14;	//(13:0,RW,0x0) //Y start position of window.
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0_auto                  :13;	//(28:16,RW,0x0) //X start position of window.
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V1_PARAM_POS_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2166C RW 0x8000_0000
	UINT32 win_size_y_auto                  :14;	//(13:0,RW,0x0) //Y-size of window.
	UINT32 resvd0                           :2;
	UINT32 win_size_x_auto                  :13;	//(28:16,RW,0x0) //X-size of window.
	UINT32 resvd1                           :1;
	UINT32 win_enable_4ch_auto              :1;	//(30,RW,0x00) //1' = 4ch pos/size control	'0' := 2ch pos/size control
	UINT32 win_enable_auto                  :1;	//(31,RW,0x01) //1' := auto pos/size control	'0' = manual pos/size control
	};
}PE_O24_VCP_SG_BDR_V1_PARAM_SIZE_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21690 RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V0_0_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21694 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V0_0_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21698 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :26;
	};
}PE_O24_VCP_SG_BDR_V0_0_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2169C RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V0_1_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA216A0 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V0_1_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA216A4 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :26;
	};
}PE_O24_VCP_SG_BDR_V0_1_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA216C0 RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V1_0_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA216C4 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V1_0_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA216C8 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :26;
	};
}PE_O24_VCP_SG_BDR_V1_0_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA216CC RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V1_1_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA216D0 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V1_1_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA216D4 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :26;
	};
}PE_O24_VCP_SG_BDR_V1_1_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21720 RW 0x0000_0000
	UINT32 win_border_width_down            :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_up              :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_SG_BDR_V0_0_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21724 RW 0x0000_0000
	UINT32 win_border_width_right           :13;	//(12:0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 win_border_width_left            :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V0_0_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21728 RW 0x0000_0000
	UINT32 win_border_width_down            :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_up              :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_SG_BDR_V0_1_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2172C RW 0x0000_0000
	UINT32 win_border_width_right           :13;	//(12:0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 win_border_width_left            :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V0_1_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21730 RW 0x0000_0000
	UINT32 win_border_width_down            :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_up              :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_SG_BDR_V1_0_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21734 RW 0x0000_0000
	UINT32 win_border_width_right           :13;	//(12:0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 win_border_width_left            :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V1_0_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21738 RW 0x0000_0000
	UINT32 win_border_width_down            :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_up              :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_SG_BDR_V1_1_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2173C RW 0x0000_0000
	UINT32 win_border_width_right           :13;	//(12:0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 win_border_width_left            :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_VCP_SG_BDR_V1_1_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21780 RW 0x0000_0000
	UINT32 rec5_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec5_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec5_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC5_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21784 RW 0x0000_0000
	UINT32 rec5_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec5_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec5_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC5_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21788 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC5_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2178C RW 0x0000_0000
	UINT32 rec6_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec6_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec6_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC6_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21790 RW 0x0000_0000
	UINT32 rec6_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec6_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec6_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC6_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21794 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC6_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21798 RW 0x0000_0000
	UINT32 rec7_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec7_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec7_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC7_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2179C RW 0x0000_0000
	UINT32 rec7_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec7_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec7_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC7_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217A0 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC7_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217A4 RW 0x0000_0000
	UINT32 rec8_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec8_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec8_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC8_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217A8 RW 0x0000_0000
	UINT32 rec8_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec8_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec8_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC8_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217AC RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC8_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217B0 RW 0x0000_0000
	UINT32 rec9_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec9_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec9_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC9_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217B4 RW 0x0000_0000
	UINT32 rec9_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec9_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec9_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC9_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217B8 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC9_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217C0 RW 0x0000_0000
	UINT32 reg0_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg0_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg0_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg0_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG0_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217C4 RW 0x0000_0000
	UINT32 reg0_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg0_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG0_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217C8 RW 0x0000_0000
	UINT32 reg1_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg1_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg1_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg1_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG1_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217CC RW 0x0000_0000
	UINT32 reg1_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg1_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG1_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217D0 RW 0x0000_0000
	UINT32 reg2_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg2_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg2_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg2_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG2_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217D4 RW 0x0000_0000
	UINT32 reg2_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg2_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG2_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217D8 RW 0x0000_0000
	UINT32 reg3_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg3_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg3_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg3_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG3_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217DC RW 0x0000_0000
	UINT32 reg3_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg3_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG3_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217E0 RW 0x0000_0000
	UINT32 reg4_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg4_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg4_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg4_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG4_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217E4 RW 0x0000_0000
	UINT32 reg4_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg4_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG4_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217E8 RW 0x0000_0000
	UINT32 reg0_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg0_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg0_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg0_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG0_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217EC RW 0x0000_0000
	UINT32 reg0_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg0_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG0_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217F0 RW 0x0000_0000
	UINT32 reg1_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg1_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg1_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg1_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG1_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217F4 RW 0x0000_0000
	UINT32 reg1_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg1_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG1_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217F8 RW 0x0000_0000
	UINT32 reg2_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg2_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg2_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg2_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG2_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA217FC RW 0x0000_0000
	UINT32 reg2_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg2_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG2_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21800 RW 0x0000_0000
	UINT32 reg3_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg3_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg3_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg3_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG3_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21804 RW 0x0000_0000
	UINT32 reg3_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg3_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG3_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21808 RW 0x0000_0000
	UINT32 reg4_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg4_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg4_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg4_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG4_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2180C RW 0x0000_0000
	UINT32 reg4_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg4_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG4_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21810 RW 0x8000_0000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 clr_lsb_cr_reg0                  :4;	//(15:12,RW,0x0) //Cr [3:0]
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 clr_msb_cr_reg0                  :4;	//(31:28,RW,0x8) //Cr [7:4]
	};
}PE_O24_VCP_WCP_REG0_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21814 RW 0x8000_8000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 clr_lsb_cr_reg1                  :4;	//(15:12,RW,0x8) //Cr [3:0]
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 clr_msb_cr_reg1                  :4;	//(31:28,RW,0x8) //Cr [7:4]
	};
}PE_O24_VCP_WCP_REG1_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21818 RW 0x2000_C000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 clr_lsb_cr_reg2                  :4;	//(15:12,RW,0xC) //Cr [3:0]
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 clr_msb_cr_reg2                  :4;	//(31:28,RW,0x2) //Cr [7:4]
	};
}PE_O24_VCP_WCP_REG2_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2181C RW 0x3000_4000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 clr_lsb_cr_reg3                  :4;	//(15:12,RW,0x4) //Cr [3:0]
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 clr_msb_cr_reg3                  :4;	//(31:28,RW,0x3) //Cr [7:4]
	};
}PE_O24_VCP_WCP_REG3_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21820 RW 0x0000_0000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O24_VCP_WCP_REG4_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21824 RW 0xB480_A82C
	UINT32 clr_cb_reg1                      :8;	//(7:0,RW,0x2C) //
	UINT32 clr_yy_reg1                      :8;	//(15:8,RW,0xA8) //
	UINT32 clr_cb_reg0                      :8;	//(23:16,RW,0x80) //
	UINT32 clr_yy_reg0                      :8;	//(31:24,RW,0xB4) //
	};
}PE_O24_VCP_WCP_REG5_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21828 RW 0x9193_853F
	UINT32 clr_cb_reg3                      :8;	//(7:0,RW,0x3F) //
	UINT32 clr_yy_reg3                      :8;	//(15:8,RW,0x85) //
	UINT32 clr_cb_reg2                      :8;	//(23:16,RW,0x93) //
	UINT32 clr_yy_reg2                      :8;	//(31:24,RW,0x91) //
	};
}PE_O24_VCP_WCP_REG6_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2182C RW 0x336D_D400
	UINT32 w0_bdr_en                        :1;	//(0,RW,0x0) //
	UINT32 w1_bdr_en                        :1;	//(1,RW,0x0) //
	UINT32 resvd                            :6;
	UINT32 clr_cr_reg4                      :8;	//(15:8,RW,0xD4) //
	UINT32 clr_cb_reg4                      :8;	//(23:16,RW,0x6D) //
	UINT32 clr_yy_reg4                      :8;	//(31:24,RW,0x33) //
	};
}PE_O24_VCP_WCP_REG7_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21830 RW 0x0000_0000
	UINT32 reg0_alpha                       :8;	//(7:0,RW,0x0) //0x00 background or U0   bottom	0xFF U0             or U1   top
	UINT32 reg1_alpha                       :8;	//(15:8,RW,0x0) //
	UINT32 reg2_alpha                       :8;	//(23:16,RW,0x0) //
	UINT32 reg3_alpha                       :8;	//(31:24,RW,0x0) //
	};
}PE_O24_VCP_WCP_REG_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21834 RW 0x0000_0000
	UINT32 rec2_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec2_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec2_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC2_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21838 RW 0x0000_0000
	UINT32 rec2_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec2_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec2_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC2_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2183C RW 0x0000_0000
	UINT32 rec3_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec3_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec3_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21840 RW 0x0000_0000
	UINT32 rec3_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec3_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec3_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21844 RW 0x0000_0000
	UINT32 rec4_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec4_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec4_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O24_VCP_WCP_M_REC4_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21848 RW 0x0000_0000
	UINT32 rec4_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec4_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec4_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O24_VCP_WCP_M_REC4_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2184C RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC0_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21850 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC1_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21854 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC2_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21858 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC3_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2185C RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_VCP_WCP_M_REC4_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21860 RW 0x0200_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_O24_VCP_VSP_U0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21864 RW 0x0200_8000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VCP_VSP_U0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21868 RW 0x0200_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :7;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VCP_VSP_U1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2186C RW 0x0200_8000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VCP_VSP_U1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21870 RW 0x0000_00C0
	UINT32 crc_enable                       :1;	//(0,RW,0x00) //
	UINT32 crc_reset                        :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 auto_reset_disable               :1;	//(3,RW,0x00) //
	UINT32 vs_level                         :1;	//(4,RW,0x00) //
	UINT32 hs_level                         :1;	//(5,RW,0x00) //
	UINT32 vs_mask                          :1;	//(6,RW,0x01) //
	UINT32 hs_mask                          :1;	//(7,RW,0x01) //
	UINT32 resvd1                           :24;
	};
}PE_O24_VCP_CRC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21874 RW 0xFFFF_FFFF
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_CRC_DATA_MASK0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21878 RW 0xFFFF_FFFF
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_CRC_DATA_MASK1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21884 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_CRC_OUT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21888 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_VCP_CRC_OUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21890 RW 0x0200_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_O24_VCP_VSP_U2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21894 RW 0x0200_8000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VCP_VSP_U2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21898 RW 0x0200_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :7;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VCP_VSP_U3_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2189C RW 0x0200_8000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_VCP_VSP_U3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218D0 RW 0x0000_0000
	UINT32 reg4_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg4_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg4_en                          :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG4_V2_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218D4 RW 0x0000_0000
	UINT32 reg4_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg4_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG4_V2_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218D8 RW 0x0000_0000
	UINT32 reg0_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg0_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg0_en                          :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG0_V3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218DC RW 0x0000_0000
	UINT32 reg0_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg0_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG0_V3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218E0 RW 0x0000_0000
	UINT32 reg1_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg1_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg1_en                          :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG1_V3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218E4 RW 0x0000_0000
	UINT32 reg1_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg1_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG1_V3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218E8 RW 0x0000_0000
	UINT32 reg2_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg2_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg2_en                          :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG2_V3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218EC RW 0x0000_0000
	UINT32 reg2_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg2_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG2_V3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218F0 RW 0x0000_0000
	UINT32 reg3_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg3_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg3_en                          :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG3_V3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218F4 RW 0x0000_0000
	UINT32 reg3_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg3_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG3_V3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218F8 RW 0x0000_0000
	UINT32 reg4_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg4_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg4_en                          :1;	//(31,RW,0x00) //
	};
}PE_O24_VCP_WCP_REG4_V3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA218FC RW 0x0000_0000
	UINT32 reg4_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg4_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_WCP_REG4_V3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21900 RW 0x01CF_11CF
	UINT32 vcp_mv_y_disp_intr0_mask         :1;	//(0,RW,0x01) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_disp_intr1_mask         :1;	//(1,RW,0x01) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_w0_intr_mask            :1;	//(2,RW,0x01) //vcp main display window0 vactive falling
	UINT32 vcp_mv_y_w1_intr_mask            :1;	//(3,RW,0x01) //vcp main display window1 vactive falling
	UINT32 resvd                            :12;
	UINT32 vcp_mv_c_disp_intr0_mask         :1;	//(16,RW,0x01) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_disp_intr1_mask         :1;	//(17,RW,0x01) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_w0_intr_mask            :1;	//(18,RW,0x01) //vcp main display window0 vactive falling
	UINT32 vcp_mv_c_w1_intr_mask            :1;	//(19,RW,0x01) //vcp main display window1 vactive falling
	UINT32 sync_gen_trk_fal_mask            :1;	//(20,RW,0x01) //long period VRR
	UINT32 sync_gen_trk_ris_mask            :1;	//(21,RW,0x01) //long period VRR
	UINT32 sync_gen_trk2_ris_mask           :1;	//(22,RW,0x01) //wait VFP VRR
	UINT32 sync_gen_trk2_fal_mask           :1;	//(23,RW,0x01) //wait VFP VRR
	UINT32 sync_gen_h_seamless_ris_mask     :1;	//(24,RW,0x01) //h total change line delay  seamless
	UINT32 sync_gen_h_seamless_fal_mask     :1;	//(25,RW,0x01) //h total change line delay  seamless
	UINT32 sync_gen_disp_vsync_fal_mask     :1;	//(26,RW,0x01) //
	UINT32 sync_gen_cvi_vactive_fal_mask    :1;	//(27,RW,0x01) //
	UINT32 sync_gen_pvsync_fal_mask         :1;	//(28,RW,0x01) //
	UINT32 sync_gen_cvi_v_dly_fal_mask      :1;	//(29,RW,0x01) //
	UINT32 sync_gen_cvi_vsync_fal_mask      :1;	//(30,RW,0x01) //
	UINT32 sync_gen_vsync_fal_mask          :1;	//(31,RW,0x01) //
	};
}PE_O24_VCP_DISP_INTR_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21904 RW 0x0000_0000
	UINT32 vcp_mv_y_disp_intr0_clear        :1;	//(0,RW,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_disp_intr1_clear        :1;	//(1,RW,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_w0_intr_clear           :1;	//(2,RW,0x00) //vcp main display window0 vactive falling
	UINT32 vcp_mv_y_w1_intr_clear           :1;	//(3,RW,0x00) //vcp main display window1 vactive falling
	UINT32 resvd                            :12;
	UINT32 vcp_mv_c_disp_intr0_clear        :1;	//(16,RW,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_disp_intr1_clear        :1;	//(17,RW,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_w0_intr_clear           :1;	//(18,RW,0x00) //vcp main display window0 vactive falling
	UINT32 vcp_mv_c_w1_intr_clear           :1;	//(19,RW,0x00) //vcp main display window1 vactive falling
	UINT32 sync_gen_trk_fal_clear           :1;	//(20,RW,0x01) //long period VRR
	UINT32 sync_gen_trk_ris_clear           :1;	//(21,RW,0x01) //long period VRR
	UINT32 sync_gen_trk2_ris_clear          :1;	//(22,RW,0x01) //wait VFP VRR
	UINT32 sync_gen_trk2_fal_clear          :1;	//(23,RW,0x01) //wait VFP VRR
	UINT32 sync_gen_h_seamless_ris_clear    :1;	//(24,RW,0x01) //h total change line delay  seamless
	UINT32 sync_gen_h_seamless_fal_clear    :1;	//(25,RW,0x01) //h total change line delay  seamless
	UINT32 sync_gen_disp_vsync_fal_clear    :1;	//(26,RW,0x01) //
	UINT32 sync_gen_cvi_vactive_fal_clear   :1;	//(27,RW,0x01) //
	UINT32 sync_gen_pvsync_fal_clear        :1;	//(28,RW,0x01) //
	UINT32 sync_gen_cvi_v_dly_fal_clear     :1;	//(29,RW,0x01) //
	UINT32 sync_gen_cvi_vsync_fal_clear     :1;	//(30,RW,0x01) //
	UINT32 sync_gen_vsync_fal_clear         :1;	//(31,RW,0x01) //
	};
}PE_O24_VCP_DISP_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21908 RO 0x0000_0000
	UINT32 vcp_mv_y_disp_intr0_status       :1;	//(0,RO,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_disp_intr1_status       :1;	//(1,RO,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_w0_intr_status          :1;	//(2,RO,0x00) //vcp main display window0 vactive falling
	UINT32 vcp_mv_y_w1_intr_status          :1;	//(3,RO,0x00) //vcp main display window1 vactive falling
	UINT32 resvd                            :12;
	UINT32 vcp_mv_c_disp_intr0_status       :1;	//(16,RO,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_disp_intr1_status       :1;	//(17,RO,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_w0_intr_status          :1;	//(18,RO,0x00) //vcp main display window0 vactive falling
	UINT32 vcp_mv_c_w1_intr_status          :1;	//(19,RO,0x00) //vcp main display window1 vactive falling
	UINT32 sync_gen_trk_fal_status          :1;	//(20,RO,0x01) //long period VRR
	UINT32 sync_gen_trk_ris_status          :1;	//(21,RO,0x01) //long period VRR
	UINT32 sync_gen_trk2_ris_status         :1;	//(22,RO,0x01) //wait VFP VRR
	UINT32 sync_gen_trk2_fal_status         :1;	//(23,RO,0x01) //wait VFP VRR
	UINT32 sync_gen_h_seamless_ris_status   :1;	//(24,RO,0x01) //h total change line delay  seamless
	UINT32 sync_gen_h_seamless_fal_status   :1;	//(25,RO,0x01) //h total change line delay  seamless
	UINT32 sync_gen_disp_vsync_fal_status   :1;	//(26,RO,0x01) //
	UINT32 sync_gen_cvi_vactive_fal_status  :1;	//(27,RO,0x01) //
	UINT32 sync_gen_pvsync_fal_status       :1;	//(28,RO,0x01) //
	UINT32 sync_gen_cvi_v_dly_fal_status    :1;	//(29,RO,0x01) //
	UINT32 sync_gen_cvi_vsync_fal_status    :1;	//(30,RO,0x01) //
	UINT32 sync_gen_vsync_fal_status        :1;	//(31,RO,0x01) //
	};
}PE_O24_VCP_DISP_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2190C RW 0x0000_0000
	UINT32 vcp_mv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_DISP_INTR0_POS_MV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21910 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_DISP_INTR1_POS_MV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21914 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_DISP_INTR0_POS_MV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21918 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_DISP_INTR1_POS_MV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2191C RW 0x0000_0000
	UINT32 vcp_sv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_DISP_INTR0_POS_SV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21920 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_DISP_INTR1_POS_SV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21924 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_DISP_INTR0_POS_SV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21928 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_VCP_DISP_INTR1_POS_SV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2192C RW 0x0000_0000
	UINT32 vcp_intr_mv_y_v_src              :1;	//(0,RW,0x00) //0' := vsync	'1' = vactive
	UINT32 vcp_intr_mv_y_h_src              :1;	//(1,RW,0x00) //0' := hsync	'1' = hactive
	UINT32 resvd0                           :1;
	UINT32 vcp_intr_mv_y_enable             :1;	//(3,RW,0x00) //
	UINT32 vcp_intr_mv_c_v_src              :1;	//(4,RW,0x00) //0' := vsync	'1' = vactive
	UINT32 vcp_intr_mv_c_h_src              :1;	//(5,RW,0x00) //0' := hsync	'1' = hactive
	UINT32 resvd1                           :1;
	UINT32 vcp_intr_mv_c_enable             :1;	//(7,RW,0x00) //
	UINT32 vcp_intr_sv_y_v_src              :1;	//(8,RW,0x00) //0' := vsync	'1' = vactive
	UINT32 vcp_intr_sv_y_h_src              :1;	//(9,RW,0x00) //0' := hsync	'1' = hactive
	UINT32 resvd2                           :1;
	UINT32 vcp_intr_sv_y_enable             :1;	//(11,RW,0x00) //
	UINT32 vcp_intr_sv_c_v_src              :1;	//(12,RW,0x00) //0' := vsync	'1' = vactive
	UINT32 vcp_intr_sv_c_h_src              :1;	//(13,RW,0x00) //0' := hsync	'1' = hactive
	UINT32 resvd3                           :1;
	UINT32 vcp_intr_sv_c_enable             :1;	//(15,RW,0x00) //
	UINT32 vcp_intr_lcount                  :14;	//(29:16,RO,0x00) //when vcp_intr_mv_y_enable = 1, 	read line count of manin sync (vsync_falling, lcount = 0,)
	UINT32 resvd4                           :2;
	};
}PE_O24_VCP_DISP_INTR_SRC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21930 RW 0x0000_0000
	UINT32 resvd0                           :3;
	UINT32 vcp_422_mean_filter_en           :1;	//(3,RW,0x00) //1 : enable (odd pixel is changing to mean of even pixels)	0 : bypass
	UINT32 vcp_maunal_size                  :1;	//(4,RW,0x00) //1 : enable vcp_422_mean_filter_last_pixel	0 : vcp_sg_bdr_v0_param_size
	UINT32 resvd1                           :3;
	UINT32 vcp_422_mean_filter_last_pixel   :13;	//(20:8,RW,0x00) //size of mean filter	real size 3840 => 1920 setting size(dual pixel)
	UINT32 resvd2                           :11;
	};
}PE_O24_VCP_U0_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21934 RW 0x129F_7C98
	UINT32 vcp_csc_coefficient1             :15;	//(14:0,RW,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient0             :15;	//(30:16,RW,0x129F) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_U1_CSC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21938 RW 0x7775_129F
	UINT32 vcp_csc_coefficient3             :15;	//(14:0,RW,0x129F) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient2             :15;	//(30:16,RW,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_U1_CSC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2193C RW 0x21D7_0000
	UINT32 vcp_csc_coefficient5             :15;	//(14:0,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient4             :15;	//(30:16,RW,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_U1_CSC_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21940 RW 0x129F_0000
	UINT32 vcp_csc_coefficient7             :15;	//(14:0,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient6             :15;	//(30:16,RW,0x129F) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_U1_CSC_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21944 RW 0x1CB0_07C0
	UINT32 vcp_csc_offset0                  :11;	//(10:0,RW,0x7C0) //Pre add offset a	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_coefficient8             :15;	//(30:16,RW,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_VCP_U1_CSC_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21948 RW 0x0600_0600
	UINT32 vcp_csc_offset2                  :11;	//(10:0,RW,0x600) //Pre add offset c	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_offset1                  :11;	//(26:16,RW,0x600) //Pre add offset b	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_O24_VCP_U1_CSC_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA2194C RW 0x0000_0000
	UINT32 vcp_csc_offset4                  :11;	//(10:0,RW,0x00) //Post add offset y	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_offset3                  :11;	//(26:16,RW,0x00) //Post add offset x	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_O24_VCP_U1_CSC_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21950 RW 0x0000_0002
	UINT32 vcp_csc_coeff_load               :1;	//(0,WO,0x00) //this bit is auto cleared
	UINT32 vcp_csc_en                       :1;	//(1,RW,0x1) //csc enable
	UINT32 vcp_csc_pcg_off                  :1;	//(2,RW,0x00) //power clock gating off
	UINT32 vcp_422_mean_filter_en           :1;	//(3,RW,0x00) //1 : enable (odd pixel is changing to mean of even pixels)	0 : bypass
	UINT32 vcp_maunal_size                  :1;	//(4,RW,0x00) //1 : enable vcp_422_mean_filter_last_pixel	0 : vcp_sg_bdr_v1_param_size
	UINT32 reg_debug                        :3;	//(7:5,RW,0x00) //
	UINT32 vcp_422_mean_filter_last_pixel   :13;	//(20:8,RW,0x00) //size of mean filter	real size 3840 => 1920 setting size(dual pixel)
	UINT32 vcp_csc_offset5                  :11;	//(31:21,RW,0x00) //Post add offset z	Range -1024~1023
	};
}PE_O24_VCP_U1_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA21954 RW 0x0000_0000
	UINT32 vcp_active_line_cnt_en           :1;	//(0,RW,0x00) //0 : disable	1 : enable
	UINT32 vcp_cnt_ref                      :1;	//(1,RW,0x00) //0 : vsync rising	1 : vsync falling
	UINT32 vcp_active_line_cnt              :15;	//(16:2,RW,0x00) //
	UINT32 resvd                            :15;
	};
}PE_O24_VCP_ACTIVE_LINE_CNT_T;

typedef struct {
	PE_O24_VCP_DISP_CTRL0_T                        vcp_disp_ctrl0;	//0xCCA21400
	PE_O24_VCP_DISP_CTRL1_T                        vcp_disp_ctrl1;	//0xCCA21404
	PE_O24_VCP_DISP_CTRL2_T                        vcp_disp_ctrl2;	//0xCCA21408
	PE_O24_VCP_DISP_CTRL3_T                        vcp_disp_ctrl3;	//0xCCA2140C
	PE_O24_VCP_CDC_MV_SYNC_CTRL_T            vcp_cdc_mv_sync_ctrl;	//0xCCA21410
	PE_O24_VCP_CDC_MV_RST_CTRL_T              vcp_cdc_mv_rst_ctrl;	//0xCCA21414
	UINT32                                                    reserved0;	//0xCCA21418
	UINT32                                                    reserved1;	//0xCCA2141C
	PE_O24_VCP_U0_WIN_O_POS_T                    vcp_u0_win_o_pos;	//0xCCA21420
	PE_O24_VCP_U0_WIN_O_SIZE_T                  vcp_u0_win_o_size;	//0xCCA21424
	PE_O24_VCP_U0_PG_PAT_CTRL_T                vcp_u0_pg_pat_ctrl;	//0xCCA21428
	PE_O24_VCP_U0_PG_PEAK_SIZE_T              vcp_u0_pg_peak_size;	//0xCCA2142C
	PE_O24_VCP_U0_CDC_Y_CTRL0_T                vcp_u0_cdc_y_ctrl0;	//0xCCA21430
	PE_O24_VCP_U0_CDC_Y_CTRL1_T                vcp_u0_cdc_y_ctrl1;	//0xCCA21434
	PE_O24_VCP_U0_CDC_Y_CTRL2_T                vcp_u0_cdc_y_ctrl2;	//0xCCA21438
	PE_O24_VCP_U0_CDC_Y_STATUS_T              vcp_u0_cdc_y_status;	//0xCCA2143C
	PE_O24_VCP_U0_CDC_C_CTRL0_T                vcp_u0_cdc_c_ctrl0;	//0xCCA21440
	PE_O24_VCP_U0_CDC_C_CTRL1_T                vcp_u0_cdc_c_ctrl1;	//0xCCA21444
	PE_O24_VCP_U0_CDC_C_CTRL2_T                vcp_u0_cdc_c_ctrl2;	//0xCCA21448
	PE_O24_VCP_U0_CDC_C_STATUS_T              vcp_u0_cdc_c_status;	//0xCCA2144C
	PE_O24_VCP_U1_WIN_O_POS_T                    vcp_u1_win_o_pos;	//0xCCA21450
	PE_O24_VCP_U1_WIN_O_SIZE_T                  vcp_u1_win_o_size;	//0xCCA21454
	PE_O24_VCP_U1_PG_PAT_CTRL_T                vcp_u1_pg_pat_ctrl;	//0xCCA21458
	PE_O24_VCP_U1_PG_PEAK_SIZE_T              vcp_u1_pg_peak_size;	//0xCCA2145C
	PE_O24_VCP_U1_CDC_Y_CTRL0_T                vcp_u1_cdc_y_ctrl0;	//0xCCA21460
	PE_O24_VCP_U1_CDC_Y_CTRL1_T                vcp_u1_cdc_y_ctrl1;	//0xCCA21464
	PE_O24_VCP_U1_CDC_Y_CTRL2_T                vcp_u1_cdc_y_ctrl2;	//0xCCA21468
	PE_O24_VCP_U1_CDC_Y_STATUS_T              vcp_u1_cdc_y_status;	//0xCCA2146C
	PE_O24_VCP_U1_CDC_C_CTRL0_T                vcp_u1_cdc_c_ctrl0;	//0xCCA21470
	PE_O24_VCP_U1_CDC_C_CTRL1_T                vcp_u1_cdc_c_ctrl1;	//0xCCA21474
	PE_O24_VCP_U1_CDC_C_CTRL2_T                vcp_u1_cdc_c_ctrl2;	//0xCCA21478
	PE_O24_VCP_U1_CDC_C_STATUS_T              vcp_u1_cdc_c_status;	//0xCCA2147C
	PE_O24_VCP_U0_WIN_O_POS_AUX_T            vcp_u0_win_o_pos_aux;	//0xCCA21480
	PE_O24_VCP_U0_WIN_O_SIZE_AUX_T          vcp_u0_win_o_size_aux;	//0xCCA21484
	PE_O24_VCP_U1_WIN_O_POS_AUX_T            vcp_u1_win_o_pos_aux;	//0xCCA21488
	PE_O24_VCP_U1_WIN_O_SIZE_AUX_T          vcp_u1_win_o_size_aux;	//0xCCA2148C
	UINT32                                                    reserved2;	//0xCCA21490
	UINT32                                                    reserved3;	//0xCCA21494
	UINT32                                                    reserved4;	//0xCCA21498
	UINT32                                                    reserved5;	//0xCCA2149C
	UINT32                                                    reserved6;	//0xCCA214A0
	UINT32                                                    reserved7;	//0xCCA214A4
	UINT32                                                    reserved8;	//0xCCA214A8
	UINT32                                                    reserved9;	//0xCCA214AC
	UINT32                                                   reserved10;	//0xCCA214B0
	UINT32                                                   reserved11;	//0xCCA214B4
	UINT32                                                   reserved12;	//0xCCA214B8
	UINT32                                                   reserved13;	//0xCCA214BC
	UINT32                                                   reserved14;	//0xCCA214C0
	UINT32                                                   reserved15;	//0xCCA214C4
	UINT32                                                   reserved16;	//0xCCA214C8
	UINT32                                                   reserved17;	//0xCCA214CC
	UINT32                                                   reserved18;	//0xCCA214D0
	UINT32                                                   reserved19;	//0xCCA214D4
	UINT32                                                   reserved20;	//0xCCA214D8
	UINT32                                                   reserved21;	//0xCCA214DC
	UINT32                                                   reserved22;	//0xCCA214E0
	UINT32                                                   reserved23;	//0xCCA214E4
	UINT32                                                   reserved24;	//0xCCA214E8
	UINT32                                                   reserved25;	//0xCCA214EC
	UINT32                                                   reserved26;	//0xCCA214F0
	UINT32                                                   reserved27;	//0xCCA214F4
	UINT32                                                   reserved28;	//0xCCA214F8
	UINT32                                                   reserved29;	//0xCCA214FC
	UINT32                                                   reserved30;	//0xCCA21500
	UINT32                                                   reserved31;	//0xCCA21504
	UINT32                                                   reserved32;	//0xCCA21508
	PE_O24_VCP_SG_MVY_CTRL_A_T                  vcp_sg_mvy_ctrl_a;	//0xCCA2150C
	PE_O24_VCP_SG_MVY_CTRL_0_T                  vcp_sg_mvy_ctrl_0;	//0xCCA21510
	PE_O24_VCP_SG_MVY_CTRL_1_T                  vcp_sg_mvy_ctrl_1;	//0xCCA21514
	PE_O24_VCP_SG_MVY_CTRL_2_T                  vcp_sg_mvy_ctrl_2;	//0xCCA21518
	PE_O24_VCP_SG_MVY_CTRL_3_T                  vcp_sg_mvy_ctrl_3;	//0xCCA2151C
	PE_O24_VCP_SG_MVY_CTRL_4_T                  vcp_sg_mvy_ctrl_4;	//0xCCA21520
	PE_O24_VCP_SG_MVY_CTRL_5_T                  vcp_sg_mvy_ctrl_5;	//0xCCA21524
	PE_O24_VCP_SG_MVY_CTRL_6_T                  vcp_sg_mvy_ctrl_6;	//0xCCA21528
	PE_O24_VCP_SG_MVY_CTRL_7_T                  vcp_sg_mvy_ctrl_7;	//0xCCA2152C
	PE_O24_VCP_SG_MVY_CTRL_8_T                  vcp_sg_mvy_ctrl_8;	//0xCCA21530
	PE_O24_VCP_SG_MVY_CTRL_9_T                  vcp_sg_mvy_ctrl_9;	//0xCCA21534
	UINT32                                                   reserved33;	//0xCCA21538
	UINT32                                                   reserved34;	//0xCCA2153C
	UINT32                                                   reserved35;	//0xCCA21540
	UINT32                                                   reserved36;	//0xCCA21544
	UINT32                                                   reserved37;	//0xCCA21548
	UINT32                                                   reserved38;	//0xCCA2154C
	UINT32                                                   reserved39;	//0xCCA21550
	UINT32                                                   reserved40;	//0xCCA21554
	UINT32                                                   reserved41;	//0xCCA21558
	UINT32                                                   reserved42;	//0xCCA2155C
	UINT32                                                   reserved43;	//0xCCA21560
	UINT32                                                   reserved44;	//0xCCA21564
	UINT32                                                   reserved45;	//0xCCA21568
	UINT32                                                   reserved46;	//0xCCA2156C
	UINT32                                                   reserved47;	//0xCCA21570
	UINT32                                                   reserved48;	//0xCCA21574
	UINT32                                                   reserved49;	//0xCCA21578
	UINT32                                                   reserved50;	//0xCCA2157C
	UINT32                                                   reserved51;	//0xCCA21580
	UINT32                                                   reserved52;	//0xCCA21584
	UINT32                                                   reserved53;	//0xCCA21588
	UINT32                                                   reserved54;	//0xCCA2158C
	UINT32                                                   reserved55;	//0xCCA21590
	UINT32                                                   reserved56;	//0xCCA21594
	UINT32                                                   reserved57;	//0xCCA21598
	UINT32                                                   reserved58;	//0xCCA2159C
	UINT32                                                   reserved59;	//0xCCA215A0
	UINT32                                                   reserved60;	//0xCCA215A4
	UINT32                                                   reserved61;	//0xCCA215A8
	UINT32                                                   reserved62;	//0xCCA215AC
	UINT32                                                   reserved63;	//0xCCA215B0
	UINT32                                                   reserved64;	//0xCCA215B4
	PE_O24_VCP_WCP_M_DISP_SIZE_T              vcp_wcp_m_disp_size;	//0xCCA215B8
	PE_O24_VCP_WCP_M_PG_PAT_CTRL_T          vcp_wcp_m_pg_pat_ctrl;	//0xCCA215BC
	UINT32                                                   reserved65;	//0xCCA215C0
	UINT32                                                   reserved66;	//0xCCA215C4
	PE_O24_VCP_WCP_M_PIXEL_READ_CTRL_T  vcp_wcp_m_pixel_read_ctrl;	//0xCCA215C8
	PE_O24_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T vcp_wcp_m_pixel_read_ctrl_aux;	//0xCCA215CC
	PE_O24_VCP_WCP_M_LINE_CTRL0_T            vcp_wcp_m_line_ctrl0;	//0xCCA215D0
	PE_O24_VCP_WCP_M_LINE_CTRL1_T            vcp_wcp_m_line_ctrl1;	//0xCCA215D4
	UINT32                                                   reserved67;	//0xCCA215D8
	UINT32                                                   reserved68;	//0xCCA215DC
	PE_O24_VCP_WCP_M_REC0_POS_X_T            vcp_wcp_m_rec0_pos_x;	//0xCCA215E0
	PE_O24_VCP_WCP_M_REC0_POS_Y_T            vcp_wcp_m_rec0_pos_y;	//0xCCA215E4
	PE_O24_VCP_WCP_M_REC1_POS_X_T            vcp_wcp_m_rec1_pos_x;	//0xCCA215E8
	PE_O24_VCP_WCP_M_REC1_POS_Y_T            vcp_wcp_m_rec1_pos_y;	//0xCCA215EC
	PE_O24_VCP_WCP_M_CTRL_0_T                    vcp_wcp_m_ctrl_0;	//0xCCA215F0
	PE_O24_VCP_WCP_M_CTRL_1_T                    vcp_wcp_m_ctrl_1;	//0xCCA215F4
	PE_O24_VCP_WCP_M_CTRL_2_T                    vcp_wcp_m_ctrl_2;	//0xCCA215F8
	PE_O24_VCP_WCP_M_CTRL_3_T                    vcp_wcp_m_ctrl_3;	//0xCCA215FC
	PE_O24_VCP_WCP_M_CTRL_4_T                    vcp_wcp_m_ctrl_4;	//0xCCA21600
	PE_O24_VCP_WCP_M_CTRL_5_T                    vcp_wcp_m_ctrl_5;	//0xCCA21604
	PE_O24_VCP_WCP_M_CTRL_6_T                    vcp_wcp_m_ctrl_6;	//0xCCA21608
	PE_O24_VCP_WCP_M_CTRL_7_T                    vcp_wcp_m_ctrl_7;	//0xCCA2160C
	PE_O24_VCP_WCP_M_CTRL_8_T                    vcp_wcp_m_ctrl_8;	//0xCCA21610
	PE_O24_VCP_WCP_M_CTRL_9_T                    vcp_wcp_m_ctrl_9;	//0xCCA21614
	PE_O24_VCP_WCP_M_CTRL_10_T                  vcp_wcp_m_ctrl_10;	//0xCCA21618
	UINT32                                                   reserved69;	//0xCCA2161C
	PE_O24_VCP_WCP_M_PG_PAT_POS_0_T        vcp_wcp_m_pg_pat_pos_0;	//0xCCA21620
	PE_O24_VCP_WCP_M_PG_PAT_SIZE_0_T      vcp_wcp_m_pg_pat_size_0;	//0xCCA21624
	PE_O24_VCP_WCP_M_PG_PAT_POS_1_T        vcp_wcp_m_pg_pat_pos_1;	//0xCCA21628
	PE_O24_VCP_WCP_M_PG_PAT_SIZE_1_T      vcp_wcp_m_pg_pat_size_1;	//0xCCA2162C
	PE_O24_VCP_WCP_M_PG_PAT_COLOR_T        vcp_wcp_m_pg_pat_color;	//0xCCA21630
	UINT32                                                   reserved70;	//0xCCA21634
	UINT32                                                   reserved71;	//0xCCA21638
	UINT32                                                   reserved72;	//0xCCA2163C
	UINT32                                                   reserved73;	//0xCCA21640
	UINT32                                                   reserved74;	//0xCCA21644
	UINT32                                                   reserved75;	//0xCCA21648
	UINT32                                                   reserved76;	//0xCCA2164C
	PE_O24_VCP_WCP_M_PIXEL_READ_DATA_0_T vcp_wcp_m_pixel_read_data_0;	//0xCCA21650
	PE_O24_VCP_WCP_M_PIXEL_READ_DATA_1_T vcp_wcp_m_pixel_read_data_1;	//0xCCA21654
	PE_O24_VCP_WCP_M_PIXEL_READ_DATA_2_T vcp_wcp_m_pixel_read_data_2;	//0xCCA21658
	PE_O24_VCP_WCP_M_PIXEL_READ_DATA_3_T vcp_wcp_m_pixel_read_data_3;	//0xCCA2165C
	PE_O24_VCP_SG_BDR_V0_PARAM_POS_M_T  vcp_sg_bdr_v0_param_pos_m;	//0xCCA21660
	PE_O24_VCP_SG_BDR_V0_PARAM_SIZE_M_T vcp_sg_bdr_v0_param_size_m;	//0xCCA21664
	PE_O24_VCP_SG_BDR_V1_PARAM_POS_M_T  vcp_sg_bdr_v1_param_pos_m;	//0xCCA21668
	PE_O24_VCP_SG_BDR_V1_PARAM_SIZE_M_T vcp_sg_bdr_v1_param_size_m;	//0xCCA2166C
	UINT32                                                   reserved77;	//0xCCA21670
	UINT32                                                   reserved78;	//0xCCA21674
	UINT32                                                   reserved79;	//0xCCA21678
	UINT32                                                   reserved80;	//0xCCA2167C
	UINT32                                                   reserved81;	//0xCCA21680
	UINT32                                                   reserved82;	//0xCCA21684
	UINT32                                                   reserved83;	//0xCCA21688
	UINT32                                                   reserved84;	//0xCCA2168C
	PE_O24_VCP_SG_BDR_V0_0_M_CTRL_0_T    vcp_sg_bdr_v0_0_m_ctrl_0;	//0xCCA21690
	PE_O24_VCP_SG_BDR_V0_0_M_CTRL_1_T    vcp_sg_bdr_v0_0_m_ctrl_1;	//0xCCA21694
	PE_O24_VCP_SG_BDR_V0_0_M_CTRL_2_T    vcp_sg_bdr_v0_0_m_ctrl_2;	//0xCCA21698
	PE_O24_VCP_SG_BDR_V0_1_M_CTRL_0_T    vcp_sg_bdr_v0_1_m_ctrl_0;	//0xCCA2169C
	PE_O24_VCP_SG_BDR_V0_1_M_CTRL_1_T    vcp_sg_bdr_v0_1_m_ctrl_1;	//0xCCA216A0
	PE_O24_VCP_SG_BDR_V0_1_M_CTRL_2_T    vcp_sg_bdr_v0_1_m_ctrl_2;	//0xCCA216A4
	UINT32                                                   reserved85;	//0xCCA216A8
	UINT32                                                   reserved86;	//0xCCA216AC
	UINT32                                                   reserved87;	//0xCCA216B0
	UINT32                                                   reserved88;	//0xCCA216B4
	UINT32                                                   reserved89;	//0xCCA216B8
	UINT32                                                   reserved90;	//0xCCA216BC
	PE_O24_VCP_SG_BDR_V1_0_M_CTRL_0_T    vcp_sg_bdr_v1_0_m_ctrl_0;	//0xCCA216C0
	PE_O24_VCP_SG_BDR_V1_0_M_CTRL_1_T    vcp_sg_bdr_v1_0_m_ctrl_1;	//0xCCA216C4
	PE_O24_VCP_SG_BDR_V1_0_M_CTRL_2_T    vcp_sg_bdr_v1_0_m_ctrl_2;	//0xCCA216C8
	PE_O24_VCP_SG_BDR_V1_1_M_CTRL_0_T    vcp_sg_bdr_v1_1_m_ctrl_0;	//0xCCA216CC
	PE_O24_VCP_SG_BDR_V1_1_M_CTRL_1_T    vcp_sg_bdr_v1_1_m_ctrl_1;	//0xCCA216D0
	PE_O24_VCP_SG_BDR_V1_1_M_CTRL_2_T    vcp_sg_bdr_v1_1_m_ctrl_2;	//0xCCA216D4
	UINT32                                                   reserved91;	//0xCCA216D8
	UINT32                                                   reserved92;	//0xCCA216DC
	UINT32                                                   reserved93;	//0xCCA216E0
	UINT32                                                   reserved94;	//0xCCA216E4
	UINT32                                                   reserved95;	//0xCCA216E8
	UINT32                                                   reserved96;	//0xCCA216EC
	UINT32                                                   reserved97;	//0xCCA216F0
	UINT32                                                   reserved98;	//0xCCA216F4
	UINT32                                                   reserved99;	//0xCCA216F8
	UINT32                                                  reserved100;	//0xCCA216FC
	UINT32                                                  reserved101;	//0xCCA21700
	UINT32                                                  reserved102;	//0xCCA21704
	UINT32                                                  reserved103;	//0xCCA21708
	UINT32                                                  reserved104;	//0xCCA2170C
	UINT32                                                  reserved105;	//0xCCA21710
	UINT32                                                  reserved106;	//0xCCA21714
	UINT32                                                  reserved107;	//0xCCA21718
	UINT32                                                  reserved108;	//0xCCA2171C
	PE_O24_VCP_SG_BDR_V0_0_M_CTRL_3_T    vcp_sg_bdr_v0_0_m_ctrl_3;	//0xCCA21720
	PE_O24_VCP_SG_BDR_V0_0_M_CTRL_4_T    vcp_sg_bdr_v0_0_m_ctrl_4;	//0xCCA21724
	PE_O24_VCP_SG_BDR_V0_1_M_CTRL_3_T    vcp_sg_bdr_v0_1_m_ctrl_3;	//0xCCA21728
	PE_O24_VCP_SG_BDR_V0_1_M_CTRL_4_T    vcp_sg_bdr_v0_1_m_ctrl_4;	//0xCCA2172C
	PE_O24_VCP_SG_BDR_V1_0_M_CTRL_3_T    vcp_sg_bdr_v1_0_m_ctrl_3;	//0xCCA21730
	PE_O24_VCP_SG_BDR_V1_0_M_CTRL_4_T    vcp_sg_bdr_v1_0_m_ctrl_4;	//0xCCA21734
	PE_O24_VCP_SG_BDR_V1_1_M_CTRL_3_T    vcp_sg_bdr_v1_1_m_ctrl_3;	//0xCCA21738
	PE_O24_VCP_SG_BDR_V1_1_M_CTRL_4_T    vcp_sg_bdr_v1_1_m_ctrl_4;	//0xCCA2173C
	UINT32                                                  reserved109;	//0xCCA21740
	UINT32                                                  reserved110;	//0xCCA21744
	UINT32                                                  reserved111;	//0xCCA21748
	UINT32                                                  reserved112;	//0xCCA2174C
	UINT32                                                  reserved113;	//0xCCA21750
	UINT32                                                  reserved114;	//0xCCA21754
	UINT32                                                  reserved115;	//0xCCA21758
	UINT32                                                  reserved116;	//0xCCA2175C
	UINT32                                                  reserved117;	//0xCCA21760
	UINT32                                                  reserved118;	//0xCCA21764
	UINT32                                                  reserved119;	//0xCCA21768
	UINT32                                                  reserved120;	//0xCCA2176C
	UINT32                                                  reserved121;	//0xCCA21770
	UINT32                                                  reserved122;	//0xCCA21774
	UINT32                                                  reserved123;	//0xCCA21778
	UINT32                                                  reserved124;	//0xCCA2177C
	PE_O24_VCP_WCP_M_REC5_POS_X_T            vcp_wcp_m_rec5_pos_x;	//0xCCA21780
	PE_O24_VCP_WCP_M_REC5_POS_Y_T            vcp_wcp_m_rec5_pos_y;	//0xCCA21784
	PE_O24_VCP_WCP_M_REC5_CLR_T                vcp_wcp_m_rec5_clr;	//0xCCA21788
	PE_O24_VCP_WCP_M_REC6_POS_X_T            vcp_wcp_m_rec6_pos_x;	//0xCCA2178C
	PE_O24_VCP_WCP_M_REC6_POS_Y_T            vcp_wcp_m_rec6_pos_y;	//0xCCA21790
	PE_O24_VCP_WCP_M_REC6_CLR_T                vcp_wcp_m_rec6_clr;	//0xCCA21794
	PE_O24_VCP_WCP_M_REC7_POS_X_T            vcp_wcp_m_rec7_pos_x;	//0xCCA21798
	PE_O24_VCP_WCP_M_REC7_POS_Y_T            vcp_wcp_m_rec7_pos_y;	//0xCCA2179C
	PE_O24_VCP_WCP_M_REC7_CLR_T                vcp_wcp_m_rec7_clr;	//0xCCA217A0
	PE_O24_VCP_WCP_M_REC8_POS_X_T            vcp_wcp_m_rec8_pos_x;	//0xCCA217A4
	PE_O24_VCP_WCP_M_REC8_POS_Y_T            vcp_wcp_m_rec8_pos_y;	//0xCCA217A8
	PE_O24_VCP_WCP_M_REC8_CLR_T                vcp_wcp_m_rec8_clr;	//0xCCA217AC
	PE_O24_VCP_WCP_M_REC9_POS_X_T            vcp_wcp_m_rec9_pos_x;	//0xCCA217B0
	PE_O24_VCP_WCP_M_REC9_POS_Y_T            vcp_wcp_m_rec9_pos_y;	//0xCCA217B4
	PE_O24_VCP_WCP_M_REC9_CLR_T                vcp_wcp_m_rec9_clr;	//0xCCA217B8
	UINT32                                                  reserved125;	//0xCCA217BC
	PE_O24_VCP_WCP_REG0_V0_POS_X_T          vcp_wcp_reg0_v0_pos_x;	//0xCCA217C0
	PE_O24_VCP_WCP_REG0_V0_POS_Y_T          vcp_wcp_reg0_v0_pos_y;	//0xCCA217C4
	PE_O24_VCP_WCP_REG1_V0_POS_X_T          vcp_wcp_reg1_v0_pos_x;	//0xCCA217C8
	PE_O24_VCP_WCP_REG1_V0_POS_Y_T          vcp_wcp_reg1_v0_pos_y;	//0xCCA217CC
	PE_O24_VCP_WCP_REG2_V0_POS_X_T          vcp_wcp_reg2_v0_pos_x;	//0xCCA217D0
	PE_O24_VCP_WCP_REG2_V0_POS_Y_T          vcp_wcp_reg2_v0_pos_y;	//0xCCA217D4
	PE_O24_VCP_WCP_REG3_V0_POS_X_T          vcp_wcp_reg3_v0_pos_x;	//0xCCA217D8
	PE_O24_VCP_WCP_REG3_V0_POS_Y_T          vcp_wcp_reg3_v0_pos_y;	//0xCCA217DC
	PE_O24_VCP_WCP_REG4_V0_POS_X_T          vcp_wcp_reg4_v0_pos_x;	//0xCCA217E0
	PE_O24_VCP_WCP_REG4_V0_POS_Y_T          vcp_wcp_reg4_v0_pos_y;	//0xCCA217E4
	PE_O24_VCP_WCP_REG0_V1_POS_X_T          vcp_wcp_reg0_v1_pos_x;	//0xCCA217E8
	PE_O24_VCP_WCP_REG0_V1_POS_Y_T          vcp_wcp_reg0_v1_pos_y;	//0xCCA217EC
	PE_O24_VCP_WCP_REG1_V1_POS_X_T          vcp_wcp_reg1_v1_pos_x;	//0xCCA217F0
	PE_O24_VCP_WCP_REG1_V1_POS_Y_T          vcp_wcp_reg1_v1_pos_y;	//0xCCA217F4
	PE_O24_VCP_WCP_REG2_V1_POS_X_T          vcp_wcp_reg2_v1_pos_x;	//0xCCA217F8
	PE_O24_VCP_WCP_REG2_V1_POS_Y_T          vcp_wcp_reg2_v1_pos_y;	//0xCCA217FC
	PE_O24_VCP_WCP_REG3_V1_POS_X_T          vcp_wcp_reg3_v1_pos_x;	//0xCCA21800
	PE_O24_VCP_WCP_REG3_V1_POS_Y_T          vcp_wcp_reg3_v1_pos_y;	//0xCCA21804
	PE_O24_VCP_WCP_REG4_V1_POS_X_T          vcp_wcp_reg4_v1_pos_x;	//0xCCA21808
	PE_O24_VCP_WCP_REG4_V1_POS_Y_T          vcp_wcp_reg4_v1_pos_y;	//0xCCA2180C
	PE_O24_VCP_WCP_REG0_BDR_T                    vcp_wcp_reg0_bdr;	//0xCCA21810
	PE_O24_VCP_WCP_REG1_BDR_T                    vcp_wcp_reg1_bdr;	//0xCCA21814
	PE_O24_VCP_WCP_REG2_BDR_T                    vcp_wcp_reg2_bdr;	//0xCCA21818
	PE_O24_VCP_WCP_REG3_BDR_T                    vcp_wcp_reg3_bdr;	//0xCCA2181C
	PE_O24_VCP_WCP_REG4_BDR_T                    vcp_wcp_reg4_bdr;	//0xCCA21820
	PE_O24_VCP_WCP_REG5_BDR_T                    vcp_wcp_reg5_bdr;	//0xCCA21824
	PE_O24_VCP_WCP_REG6_BDR_T                    vcp_wcp_reg6_bdr;	//0xCCA21828
	PE_O24_VCP_WCP_REG7_BDR_T                    vcp_wcp_reg7_bdr;	//0xCCA2182C
	PE_O24_VCP_WCP_REG_ALPHA_T                  vcp_wcp_reg_alpha;	//0xCCA21830
	PE_O24_VCP_WCP_M_REC2_POS_X_T            vcp_wcp_m_rec2_pos_x;	//0xCCA21834
	PE_O24_VCP_WCP_M_REC2_POS_Y_T            vcp_wcp_m_rec2_pos_y;	//0xCCA21838
	PE_O24_VCP_WCP_M_REC3_POS_X_T            vcp_wcp_m_rec3_pos_x;	//0xCCA2183C
	PE_O24_VCP_WCP_M_REC3_POS_Y_T            vcp_wcp_m_rec3_pos_y;	//0xCCA21840
	PE_O24_VCP_WCP_M_REC4_POS_X_T            vcp_wcp_m_rec4_pos_x;	//0xCCA21844
	PE_O24_VCP_WCP_M_REC4_POS_Y_T            vcp_wcp_m_rec4_pos_y;	//0xCCA21848
	PE_O24_VCP_WCP_M_REC0_CLR_T                vcp_wcp_m_rec0_clr;	//0xCCA2184C
	PE_O24_VCP_WCP_M_REC1_CLR_T                vcp_wcp_m_rec1_clr;	//0xCCA21850
	PE_O24_VCP_WCP_M_REC2_CLR_T                vcp_wcp_m_rec2_clr;	//0xCCA21854
	PE_O24_VCP_WCP_M_REC3_CLR_T                vcp_wcp_m_rec3_clr;	//0xCCA21858
	PE_O24_VCP_WCP_M_REC4_CLR_T                vcp_wcp_m_rec4_clr;	//0xCCA2185C
	PE_O24_VCP_VSP_U0_CTRL_00_T                vcp_vsp_u0_ctrl_00;	//0xCCA21860
	PE_O24_VCP_VSP_U0_CTRL_01_T                vcp_vsp_u0_ctrl_01;	//0xCCA21864
	PE_O24_VCP_VSP_U1_CTRL_00_T                vcp_vsp_u1_ctrl_00;	//0xCCA21868
	PE_O24_VCP_VSP_U1_CTRL_01_T                vcp_vsp_u1_ctrl_01;	//0xCCA2186C
	PE_O24_VCP_CRC_CTRL_T                            vcp_crc_ctrl;	//0xCCA21870
	PE_O24_VCP_CRC_DATA_MASK0_T                vcp_crc_data_mask0;	//0xCCA21874
	PE_O24_VCP_CRC_DATA_MASK1_T                vcp_crc_data_mask1;	//0xCCA21878
	UINT32                                                  reserved126;	//0xCCA2187C
	UINT32                                                  reserved127;	//0xCCA21880
	PE_O24_VCP_CRC_OUT0_T                            vcp_crc_out0;	//0xCCA21884
	PE_O24_VCP_CRC_OUT1_T                            vcp_crc_out1;	//0xCCA21888
	UINT32                                                  reserved128;	//0xCCA2188C
	PE_O24_VCP_VSP_U2_CTRL_00_T                vcp_vsp_u2_ctrl_00;	//0xCCA21890
	PE_O24_VCP_VSP_U2_CTRL_01_T                vcp_vsp_u2_ctrl_01;	//0xCCA21894
	PE_O24_VCP_VSP_U3_CTRL_00_T                vcp_vsp_u3_ctrl_00;	//0xCCA21898
	PE_O24_VCP_VSP_U3_CTRL_01_T                vcp_vsp_u3_ctrl_01;	//0xCCA2189C
	UINT32                                                  reserved129;	//0xCCA218A0
	UINT32                                                  reserved130;	//0xCCA218A4
	UINT32                                                  reserved131;	//0xCCA218A8
	UINT32                                                  reserved132;	//0xCCA218AC
	UINT32                                                  reserved133;	//0xCCA218B0
	UINT32                                                  reserved134;	//0xCCA218B4
	UINT32                                                  reserved135;	//0xCCA218B8
	UINT32                                                  reserved136;	//0xCCA218BC
	UINT32                                                  reserved137;	//0xCCA218C0
	UINT32                                                  reserved138;	//0xCCA218C4
	UINT32                                                  reserved139;	//0xCCA218C8
	UINT32                                                  reserved140;	//0xCCA218CC
	PE_O24_VCP_WCP_REG4_V2_POS_X_T          vcp_wcp_reg4_v2_pos_x;	//0xCCA218D0
	PE_O24_VCP_WCP_REG4_V2_POS_Y_T          vcp_wcp_reg4_v2_pos_y;	//0xCCA218D4
	PE_O24_VCP_WCP_REG0_V3_POS_X_T          vcp_wcp_reg0_v3_pos_x;	//0xCCA218D8
	PE_O24_VCP_WCP_REG0_V3_POS_Y_T          vcp_wcp_reg0_v3_pos_y;	//0xCCA218DC
	PE_O24_VCP_WCP_REG1_V3_POS_X_T          vcp_wcp_reg1_v3_pos_x;	//0xCCA218E0
	PE_O24_VCP_WCP_REG1_V3_POS_Y_T          vcp_wcp_reg1_v3_pos_y;	//0xCCA218E4
	PE_O24_VCP_WCP_REG2_V3_POS_X_T          vcp_wcp_reg2_v3_pos_x;	//0xCCA218E8
	PE_O24_VCP_WCP_REG2_V3_POS_Y_T          vcp_wcp_reg2_v3_pos_y;	//0xCCA218EC
	PE_O24_VCP_WCP_REG3_V3_POS_X_T          vcp_wcp_reg3_v3_pos_x;	//0xCCA218F0
	PE_O24_VCP_WCP_REG3_V3_POS_Y_T          vcp_wcp_reg3_v3_pos_y;	//0xCCA218F4
	PE_O24_VCP_WCP_REG4_V3_POS_X_T          vcp_wcp_reg4_v3_pos_x;	//0xCCA218F8
	PE_O24_VCP_WCP_REG4_V3_POS_Y_T          vcp_wcp_reg4_v3_pos_y;	//0xCCA218FC
	PE_O24_VCP_DISP_INTR_MASK_T                vcp_disp_intr_mask;	//0xCCA21900
	PE_O24_VCP_DISP_INTR_CLEAR_T              vcp_disp_intr_clear;	//0xCCA21904
	PE_O24_VCP_DISP_INTR_STATUS_T            vcp_disp_intr_status;	//0xCCA21908
	PE_O24_VCP_DISP_INTR0_POS_MV_Y_T      vcp_disp_intr0_pos_mv_y;	//0xCCA2190C
	PE_O24_VCP_DISP_INTR1_POS_MV_Y_T      vcp_disp_intr1_pos_mv_y;	//0xCCA21910
	PE_O24_VCP_DISP_INTR0_POS_MV_C_T      vcp_disp_intr0_pos_mv_c;	//0xCCA21914
	PE_O24_VCP_DISP_INTR1_POS_MV_C_T      vcp_disp_intr1_pos_mv_c;	//0xCCA21918
	PE_O24_VCP_DISP_INTR0_POS_SV_Y_T      vcp_disp_intr0_pos_sv_y;	//0xCCA2191C
	PE_O24_VCP_DISP_INTR1_POS_SV_Y_T      vcp_disp_intr1_pos_sv_y;	//0xCCA21920
	PE_O24_VCP_DISP_INTR0_POS_SV_C_T      vcp_disp_intr0_pos_sv_c;	//0xCCA21924
	PE_O24_VCP_DISP_INTR1_POS_SV_C_T      vcp_disp_intr1_pos_sv_c;	//0xCCA21928
	PE_O24_VCP_DISP_INTR_SRC_SEL_T          vcp_disp_intr_src_sel;	//0xCCA2192C
	PE_O24_VCP_U0_CSC_CTRL7_T                    vcp_u0_csc_ctrl7;	//0xCCA21930
	PE_O24_VCP_U1_CSC_CTRL0_T                    vcp_u1_csc_ctrl0;	//0xCCA21934
	PE_O24_VCP_U1_CSC_CTRL1_T                    vcp_u1_csc_ctrl1;	//0xCCA21938
	PE_O24_VCP_U1_CSC_CTRL2_T                    vcp_u1_csc_ctrl2;	//0xCCA2193C
	PE_O24_VCP_U1_CSC_CTRL3_T                    vcp_u1_csc_ctrl3;	//0xCCA21940
	PE_O24_VCP_U1_CSC_CTRL4_T                    vcp_u1_csc_ctrl4;	//0xCCA21944
	PE_O24_VCP_U1_CSC_CTRL5_T                    vcp_u1_csc_ctrl5;	//0xCCA21948
	PE_O24_VCP_U1_CSC_CTRL6_T                    vcp_u1_csc_ctrl6;	//0xCCA2194C
	PE_O24_VCP_U1_CSC_CTRL7_T                    vcp_u1_csc_ctrl7;	//0xCCA21950
	PE_O24_VCP_ACTIVE_LINE_CNT_T              vcp_active_line_cnt;	//0xCCA21954
}PE_VCP_DISP_REG_O24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461400 RW 0x1E00_10E0
	UINT32 reg_height                       :16;	//(15:00,NA,0x10E0) //Output width : default 4320
	UINT32 reg_width                        :16;	//(31:16,NA,0x1E00) //Output width : default 7680
	};
}PE_O24_OLB_PIC_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461404 RW 0x3F00_0000
//	UINT32 reg_ptn_en1                      :5;	//(04:00,NA,0x0) //C Channel Pattern Generation Enable Bit	[00] : OSC0 C Input  Pattern Generation Enable	[01] : OSC1 C Input  Pattern Generation Enable	[02] : OSC2 C Input  Pattern Generation Enable	[03] : OSC3 C Input  Pattern Generation Enable	[04] : OLB  C Output Pattern Generation Enable
	UINT32 reg_ptn_en1_osc0                 :1;	//[00] : OSC0 C Input  Pattern Generation Enable
	UINT32 reg_ptn_en1_osc1                 :1;	//[01] : OSC1 C Input  Pattern Generation Enable		
	UINT32 reg_ptn_en1_osc2                 :1;	//[02] : OSC2 C Input  Pattern Generation Enable
	UINT32 reg_ptn_en1_osc3                 :1;	//[03] : OSC3 C Input  Pattern Generation Enable
	UINT32 reg_ptn_en1_olb                  :1;	//[04] : OLB  C Output Pattern Generation Enable
	UINT32 resvd0                           :3;
//	UINT32 reg_ptn_en0                      :5;	//(12:08,NA,0x0) //Y Channel Pattern Generation Enable Bit	[08] : OSC0 Y Input  Pattern Generation Enable	[09] : OSC1 Y Input  Pattern Generation Enable	[10] : OSC2 Y Input  Pattern Generation Enable	[11] : OSC3 Y Input  Pattern Generation Enable	[12] : OLB  Y Output Pattern Generation Enable
	UINT32 reg_ptn_en0_osc0                 :1;	//[08] : OSC0 Y Input  Pattern Generation Enable
	UINT32 reg_ptn_en0_osc1                 :1;	//[09] : OSC1 Y Input  Pattern Generation Enable		
	UINT32 reg_ptn_en0_osc2                 :1;	//[10] : OSC2 Y Input  Pattern Generation Enable
	UINT32 reg_ptn_en0_osc3                 :1;	//[11] : OSC3 Y Input  Pattern Generation Enable
	UINT32 reg_ptn_en0_olb                  :1;	//[12] : OLB  Y Output Pattern Generation Enable
	UINT32 resvd1                           :3;
	UINT32 reg_olb_mux                      :5;	//(20:16,NA,0x0) //OLB Layer Merge Sequence (06, 07, 13, 14, 22, 23, 30, 31) not supported	00 : OSC0 - OSC1 - OSC2 - OSC3	01 : OSC0 - OSC1 - OSC3 - OSC2	02 : OSC0 - OSC2 - OSC1 - OSC3	03 : OSC0 - OSC2 - OSC3 - OSC1	04 : OSC0 - OSC3 - OSC1 - OSC2	05 : OSC0 - OSC3 - OSC2 - OSC1	08 : OSC1 - OSC0 - OSC2 - OSC3	09 : OSC1 - OSC0 - OSC3 - OSC2	10 : OSC1 - OSC2 - OSC0 - OSC3	11 : OSC1 - OSC2 - OSC3 - OSC0	12 : OSC1 - OSC3 - OSC0 - OSC2	13 : OSC1 - OSC3 - OSC2 - OSC0	16 : OSC2 - OSC0 - OSC1 - OSC3	17 : OSC2 - OSC0 - OSC3 - OSC1	18 : OSC2 - OSC1 - OSC0 - OSC3	19 : OSC2 - OSC1 - OSC3 - OSC0	20 : OSC2 - OSC3 - OSC0 - OSC1	21 : OSC2 - OSC3 - OSC1 - OSC0	24 : OSC3 - OSC0 - OSC1 - OSC2	25 : OSC3 - OSC0 - OSC2 - OSC1	26 : OSC3 - OSC1 - OSC0 - OSC2	27 : OSC3 - OSC1 - OSC2 - OSC0	28 : OSC3 - OSC2 - OSC0 - OSC1	29 : OSC3 - OSC2 - OSC1 - OSC0
	UINT32 resvd2                           :3;
//	UINT32 reg_olb_enable                   :4;	//(27:24,NA,0xF) //[24] : OSC0 Enable Bit	[25] : OSC1 Enable Bit	[26] : OSC2 Enable Bit	[27] : OSC3 Enable Bit
	UINT32 reg_olb_osc0_enable              :1;	//[24] : OSC0 Enable Bit
	UINT32 reg_olb_osc1_enable              :1;	//[25] : OSC1 Enable Bit
	UINT32 reg_olb_osc2_enable              :1;	//[26] : OSC2 Enable Bit
	UINT32 reg_olb_osc3_enable              :1;	//[27] : OSC3 Enable Bit
	UINT32 reg_olb_cs                       :2;	//(29:28,NA,0x3) //2 : color space YC422	3 : color space YC444	0/1 : color space YC420 (not supported)
	UINT32 reg_buf_bypass_en                :1;	//(30:30,NA,0x0) //0 : OSC Line Blend Enabled w/ buffer bypass	1 : OSC Line Blend Disabled (OSC0 output detoured)	(Automatically disabled when reg_detour_en is on)
	UINT32 reg_detour_en                    :1;	//(31:31,NA,0x0) //0 : OSC Line Blend Enabled	1 : OSC Line Blend Disabled (OSC0 output detoured)
	};
}PE_O24_OLB_TOP_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461408 RW 0x0000_0000
	UINT32 reg_yy_bg_color                  :10;	//(09:00,NA,0x000) //Y Channel Background Colour
	UINT32 resvd                            :22;
	};
}PE_O24_OLB_TOP_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46140C RW 0x0200_0200
	UINT32 reg_cr_bg_color                  :10;	//(09:00,NA,0x200) //Cr Channel Background Colour
	UINT32 resvd0                           :6;
	UINT32 reg_cb_bg_color                  :10;	//(25:16,NA,0x200) //Cb Channel Background Colour
	UINT32 resvd1                           :6;
	};
}PE_O24_OLB_TOP_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461410 RW 0x0000_0000
	UINT32 reg_yy_alpha_l3                  :8;	//(07:00,NA,0x00) //Y  Channel Layer 3 Alpha value
	UINT32 reg_yy_alpha_l2                  :8;	//(15:08,NA,0x00) //Y  Channel Layer 2 Alpha value
	UINT32 reg_yy_alpha_l1                  :8;	//(23:16,NA,0x00) //Y  Channel Layer 1 Alpha value
	UINT32 reg_yy_alpha_l0                  :8;	//(31:24,NA,0x00) //Y  Channel Layer 0 Alpha value
	};
}PE_O24_OLB_TOP_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461414 RW 0x0000_0000
	UINT32 reg_cb_alpha_l3                  :8;	//(07:00,NA,0x00) //Cb Channel Layer 3 Alpha value
	UINT32 reg_cb_alpha_l2                  :8;	//(15:08,NA,0x00) //Cb Channel Layer 2 Alpha value
	UINT32 reg_cb_alpha_l1                  :8;	//(23:16,NA,0x00) //Cb Channel Layer 1 Alpha value
	UINT32 reg_cb_alpha_l0                  :8;	//(31:24,NA,0x00) //Cb Channel Layer 0 Alpha value
	};
}PE_O24_OLB_TOP_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461418 RW 0x0000_0000
	UINT32 reg_cr_alpha_l3                  :8;	//(07:00,NA,0x00) //Cr Channel Layer 3 Alpha value
	UINT32 reg_cr_alpha_l2                  :8;	//(15:08,NA,0x00) //Cr Channel Layer 2 Alpha value
	UINT32 reg_cr_alpha_l1                  :8;	//(23:16,NA,0x00) //Cr Channel Layer 1 Alpha value
	UINT32 reg_cr_alpha_l0                  :8;	//(31:24,NA,0x00) //Cr Channel Layer 0 Alpha value
	};
}PE_O24_OLB_TOP_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461420 RW 0x0000_1DFF
	UINT32 reg_osc0_x_ed                    :16;	//(15:00,NA,0x1DFF) //OSC0 Horizontal End   Position
	UINT32 reg_osc0_x_st                    :16;	//(31:16,NA,0x00000) //OSC0 Horizontal Start Position
	};
}PE_O24_OLB_OSC0_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461424 RW 0x0000_10DF
	UINT32 reg_osc0_y_ed                    :16;	//(15:00,NA,0x10DF) //OSC0 Vertical   End   Position
	UINT32 reg_osc0_y_st                    :16;	//(31:16,NA,0x00000) //OSC0 Vertical   Start Position
	};
}PE_O24_OLB_OSC0_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461428 RW 0x0000_1DFF
	UINT32 reg_osc1_x_ed                    :16;	//(15:00,NA,0x1DFF) //OSC1 Horizontal End   Position
	UINT32 reg_osc1_x_st                    :16;	//(31:16,NA,0x00000) //OSC1 Horizontal Start Position
	};
}PE_O24_OLB_OSC1_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46142C RW 0x0000_10DF
	UINT32 reg_osc1_y_ed                    :16;	//(15:00,NA,0x10DF) //OSC1 Vertical   End   Position
	UINT32 reg_osc1_y_st                    :16;	//(31:16,NA,0x00000) //OSC1 Vertical   Start Position
	};
}PE_O24_OLB_OSC1_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461430 RW 0x0000_1DFF
	UINT32 reg_osc2_x_ed                    :16;	//(15:00,NA,0x1DFF) //OSC2 Horizontal End   Position
	UINT32 reg_osc2_x_st                    :16;	//(31:16,NA,0x00000) //OSC2 Horizontal Start Position
	};
}PE_O24_OLB_OSC2_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461434 RW 0x0000_10DF
	UINT32 reg_osc2_y_ed                    :16;	//(15:00,NA,0x10DF) //OSC2 Vertical   End   Position
	UINT32 reg_osc2_y_st                    :16;	//(31:16,NA,0x00000) //OSC2 Vertical   Start Position
	};
}PE_O24_OLB_OSC2_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461438 RW 0x0000_1DFF
	UINT32 reg_osc3_x_ed                    :16;	//(15:00,NA,0x1DFF) //OSC3 Horizontal End   Position
	UINT32 reg_osc3_x_st                    :16;	//(31:16,NA,0x00000) //OSC3 Horizontal Start Position
	};
}PE_O24_OLB_OSC3_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46143C RW 0x0000_10DF
	UINT32 reg_osc3_y_ed                    :16;	//(15:00,NA,0x10DF) //OSC3 Vertical   End   Position
	UINT32 reg_osc3_y_st                    :16;	//(31:16,NA,0x00000) //OSC3 Vertical   Start Position
	};
}PE_O24_OLB_OSC3_CTRL1_T;

typedef struct {
	PE_O24_OLB_PIC_SIZE_T                                olb_pic_size;	//0xCC461400
	PE_O24_OLB_TOP_CTRL0_T                               olb_top_ctrl0;	//0xCC461404
	PE_O24_OLB_TOP_CTRL1_T                               olb_top_ctrl1;	//0xCC461408
	PE_O24_OLB_TOP_CTRL2_T                               olb_top_ctrl2;	//0xCC46140C
	PE_O24_OLB_TOP_CTRL3_T                               olb_top_ctrl3;	//0xCC461410
	PE_O24_OLB_TOP_CTRL4_T                               olb_top_ctrl4;	//0xCC461414
	PE_O24_OLB_TOP_CTRL5_T                               olb_top_ctrl5;	//0xCC461418
	UINT32                                                    reserved0;	//0xCC46141C
	PE_O24_OLB_OSC0_CTRL0_T                             olb_osc0_ctrl0;	//0xCC461420
	PE_O24_OLB_OSC0_CTRL1_T                             olb_osc0_ctrl1;	//0xCC461424
	PE_O24_OLB_OSC1_CTRL0_T                             olb_osc1_ctrl0;	//0xCC461428
	PE_O24_OLB_OSC1_CTRL1_T                             olb_osc1_ctrl1;	//0xCC46142C
	PE_O24_OLB_OSC2_CTRL0_T                             olb_osc2_ctrl0;	//0xCC461430
	PE_O24_OLB_OSC2_CTRL1_T                             olb_osc2_ctrl1;	//0xCC461434
	PE_O24_OLB_OSC3_CTRL0_T                             olb_osc3_ctrl0;	//0xCC461438
	PE_O24_OLB_OSC3_CTRL1_T                             olb_osc3_ctrl1;	//0xCC46143C
}PE_OLB_REG_O24_T;


#endif
