#ifndef _PE_VCP_REG_O26A0_H_
#define _PE_VCP_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC953F00 RW 0x0000_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_O26_VSD_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC953F04 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC953F08 RW 0x0000_0000
	UINT32 enable                           :1; //0 //
	UINT32 resvd0                           :3;
	UINT32 brightness                        :10;	//13:4	//
	UINT32 resvd1                           :2;
	UINT32 contrast                         :10;	//25:16 //
	UINT32 resvd2                           :6;
	};
}PE_O26_VSD_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC953F0C RW 0x0000_0000
	UINT32 saturation_en                    :1; //0 //
	UINT32 resvd0                           :7;
	UINT32 saturation                       :8; //15:8	//
	UINT32 brightness                       :10;	//25:16 //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_VERI_SYS_VERI_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC953F10 RW 0x0000_0000
	UINT32 reg_sys_veri_4                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_VSD_VERI_SYS_VERI_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC953F14 RW 0x0000_0000
	UINT32 reg_sys_veri_5                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_VSD_VERI_SYS_VERI_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC953F18 RW 0x0000_0000
	UINT32 reg_sys_veri_6                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_VSD_VERI_SYS_VERI_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC953F1C RW 0x0000_0000
	UINT32 reg_sys_veri_7                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_VSD_VERI_SYS_VERI_7_T;

typedef struct {
	PE_O26_VSD_VERI_SYS_VERI_0_T                                vsd_veri_vsp0_0;	//0xCC953F00
	PE_O26_VSD_VERI_SYS_VERI_1_T                                vsd_veri_vsp0_1;	//0xCC953F04
	PE_O26_VSD_VERI_SYS_VERI_2_T                                vsd_veri_vsp1_0;	//0xCC953F08
	PE_O26_VSD_VERI_SYS_VERI_3_T                                vsd_veri_vsp1_1;	//0xCC953F0C
	PE_O26_VSD_VERI_SYS_VERI_4_T                                sys_veri_4;	//0xCC953F10
	PE_O26_VSD_VERI_SYS_VERI_5_T                                sys_veri_5;	//0xCC953F14
	PE_O26_VSD_VERI_SYS_VERI_6_T                                sys_veri_6;	//0xCC953F18
	PE_O26_VSD_VERI_SYS_VERI_7_T                                sys_veri_7;	//0xCC953F1C
}PE_VSD_VERI_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951400 RW 0x3FFF_3FFF
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
}PE_O26_VCP_DISP_VCP_DISP_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951404 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_DISP_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951408 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 vcp_u1_disp_clk_cg               :1;	//(1,RW,0x00) //VCP U1 Disp Clock Gating ON	0 := Off	1 := On
	UINT32 resvd1                           :2;
	UINT32 wcp_m_mix_enable                 :2;	//(5:4,RW,0x00) //for debugging	"00" := main default.	"01" = PIP/R2 full video
	UINT32 resvd2                           :2;
	UINT32 en_bypass_sync_my                :1;	//(8,RW,0x00) //
	UINT32 resvd3                           :23;
	};
}PE_O26_VCP_DISP_VCP_DISP_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95140C RO 0x2026_0101
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_DISP_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951414 RW 0x0000_0000
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
}PE_O26_VCP_DISP_VCP_CDC_MV_RST_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951420 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y                  :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x                  :14;	//(29:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_U0_WIN_O_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951424 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y                 :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x                 :14;	//(29:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_U0_WIN_O_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951428 RW 0x0000_0000
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
}PE_O26_VCP_DISP_VCP_U0_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95142C RW 0x0000_0780
	UINT32 peak_hsize                       :12;	//(11:0,RW,0x780) //cdc_win_o_size_x/2 round-up  2P
	UINT32 peak_offset                      :1;	//(12,RW,0x0) //cdc_win_o_pos_x[0]
	UINT32 resvd0                           :2;
	UINT32 peak_manual                      :1;	//(15,RW,0x0) //auto position release for debug
	UINT32 resvd1                           :16;
	};
}PE_O26_VCP_DISP_VCP_U0_PG_PEAK_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951430 RW 0x0820_0000
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
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x02) //"11" := 4CH	"10" = 2CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 resvd2                           :4;
	};
}PE_O26_VCP_DISP_VCP_U0_CDC_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951434 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_U0_CDC_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951438 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_u0_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_u0_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_O26_VCP_DISP_VCP_U0_CDC_Y_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95143C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_U0_CDC_Y_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951440 RW 0x0820_0000
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
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x02) //"11" := 4CH	"10" = 2CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 resvd2                           :4;
	};
}PE_O26_VCP_DISP_VCP_U0_CDC_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951444 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_U0_CDC_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951448 RW 0x0000_0000
	UINT32 set_pic_init_c_mux_u0_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_u0_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_O26_VCP_DISP_VCP_U0_CDC_C_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95144C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_U0_CDC_C_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951450 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y                  :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x                  :14;	//(29:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_U1_WIN_O_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951454 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y                 :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x                 :14;	//(29:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_U1_WIN_O_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951458 RW 0x0000_0000
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
}PE_O26_VCP_DISP_VCP_U1_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95145C RW 0x0000_0780
	UINT32 peak_hsize                       :12;	//(11:0,RW,0x780) //cdc_win_o_size_x/2 round-up  2P
	UINT32 peak_offset                      :1;	//(12,RW,0x0) //cdc_win_o_pos_x[0]
	UINT32 resvd0                           :2;
	UINT32 peak_manual                      :1;	//(15,RW,0x0) //auto position release for debug
	UINT32 resvd1                           :16;
	};
}PE_O26_VCP_DISP_VCP_U1_PG_PEAK_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951460 RW 0x0820_0000
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
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x02) //"11" := 2CH	"10" = 4CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	"0010" = video R2(T3C).	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 resvd2                           :4;
	};
}PE_O26_VCP_DISP_VCP_U1_CDC_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951464 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_U1_CDC_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951468 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_u1_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_u1_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0010" = pic_start_y_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_O26_VCP_DISP_VCP_U1_CDC_Y_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95146C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_U1_CDC_Y_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951470 RW 0x0820_0000
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
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x02) //"11" := 2CH	"10" = 4CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 resvd2                           :4;
	};
}PE_O26_VCP_DISP_VCP_U1_CDC_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951474 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_U1_CDC_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951478 RW 0x0000_0000
	UINT32 set_pic_init_c_mux_u1_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_u1_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0010" = pic_start_c_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_O26_VCP_DISP_VCP_U1_CDC_C_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95147C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_U1_CDC_C_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951480 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y_aux              :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x_aux              :14;	//(29:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_U0_WIN_O_POS_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951484 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y_aux             :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x_aux             :14;	//(29:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :1;
	UINT32 cdc_win_aux_auto                 :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_U0_WIN_O_SIZE_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951488 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y_aux              :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x_aux              :14;	//(29:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_U1_WIN_O_POS_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95148C RW 0x0F00_0870
	UINT32 cdc_win_o_size_y_aux             :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x_aux             :14;	//(29:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :1;
	UINT32 cdc_win_aux_auto                 :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_U1_WIN_O_SIZE_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9514E0 RW 0x0008_000A
	UINT32 vsync                            :16;	//(15:0,RW,0xA) //10
	UINT32 vfp                              :16;	//(31:16,RW,0x8) //8
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9514E4 RW 0x0048_0870
	UINT32 va                               :16;	//(15:0,RW,0x870) //2160
	UINT32 vbp                              :16;	//(31:16,RW,0x48) //72
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9514E8 RW 0x0058_002C
	UINT32 hsync                            :16;	//(15:0,RW,0x2C) //88/2=44 for dual channel(E,O)
	UINT32 hfp                              :16;	//(31:16,RW,0x58) //176/2=88 for dual channel(E,O)
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9514EC RW 0x0094_0780
	UINT32 ha                               :16;	//(15:0,RW,0x780) //3840/2=1920 for dual channel(E,O)
	UINT32 hbp                              :16;	//(31:16,RW,0x94) //296/2=148 for dual channel(E,O)
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9514F0 RW 0x0000_0000
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
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9514F4 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9514F8 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9514FC RW 0x0002_8010
	UINT32 auto_ha_delay                    :15;	//(14:0,RW,0x10) //
	UINT32 auto_general_en                  :1;	//(15,RW,0x1) //general delay block enable
	UINT32 auto_va_delay                    :15;	//(30:16,RW,0x2) //
	UINT32 auto_seamless                    :1;	//(31,RW,0x0) //
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951500 RW 0x0002_8010
	UINT32 auto_hs_delay                    :15;	//(14:0,RW,0x10) //
	UINT32 auto_general_en                  :1;	//(15,RW,0x1) //general delay block enable
	UINT32 auto_vs_delay                    :15;	//(30:16,RW,0x2) //
	UINT32 auto_seamless                    :1;	//(31,RW,0x0) //
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951504 RW 0x0000_0000
	UINT32 resvd                            :31;
	UINT32 sync_out_disable                 :1;	//(31,RW,0x0000_0000) //
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515B8 RW 0x0780_0870
	UINT32 pg1ch_win_o_size_y               :14;	//(13:0,RW,0x870) //0x870(2160) for UD, 0x438(1080) for FHD.
	UINT32 resvd0                           :2;
	UINT32 pg1ch_win_o_size_x               :14;	//(29:16,RW,0x780) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_DISP_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515BC RW 0x0000_0000
	UINT32 lattice_pat_en                   :1;	//(0,RW,0x00) //main video 와 blending되어 출력된다.
	UINT32 resvd0                           :3;
	UINT32 ramp_pat_en                      :2;	//(5:4,RW,0x00) //"00" := bypass	"01" = diagonal	"10" = horizontal	"11" = vertical
	UINT32 mpg_o_color_sel                  :2;	//(7:6,RW,0x00) //"00" := YC	"01" = Y ONLY	"10" = C ONLY
	UINT32 border_sel                       :4;	//(11:8,RW,0x00) //"0000" := bypass	"0001" = border w/ white	"0010" = border w/ black	"0011" = border w/ red	"0100" = border w/ green	"0101" = border w/ blue
	UINT32 resvd1                           :2;
	UINT32 vcp_wcp_m_rec_en                 :1;	//(14,RW,0x00) //1 : rectangle box enable
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
}PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515C8 RW 0x0000_0000
	UINT32 rd_pel_pos_y                     :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 rd_pel_pos_x                     :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :1;
	UINT32 rd_pel_pat_en                    :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515CC RW 0x0000_0000
	UINT32 rd_pel_pos_y                     :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 rd_pel_pos_x                     :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :1;
	UINT32 rd_pel_pat_en                    :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515D0 RW 0x0000_0000
	UINT32 even_line_cr                     :8;	//(7:0,RW,0x0) //
	UINT32 even_line_cb                     :8;	//(15:8,RW,0x0) //
	UINT32 even_line_y                      :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 even_line_pat_en                 :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_M_LINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515D4 RW 0x0000_0000
	UINT32 odd_line_cr                      :8;	//(7:0,RW,0x0) //
	UINT32 odd_line_cb                      :8;	//(15:8,RW,0x0) //
	UINT32 odd_line_y                       :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 odd_line_pat_en                  :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_M_LINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515E0 RW 0x0000_0000
	UINT32 rec0_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec0_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec0_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515E4 RW 0x0000_0000
	UINT32 rec0_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec0_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec0_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515E8 RW 0x0000_0000
	UINT32 rec1_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec1_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec1_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515EC RW 0x0000_0000
	UINT32 rec1_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec1_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec1_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515F4 RW 0x8080_8080
	UINT32 w1_clr_dark_cr                   :8;	//(7:0,RW,0x80) //we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 w0_clr_dark_cr                   :8;	//(15:8,RW,0x80) //we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 clr_nac_cr                       :8;	//(23:16,RW,0x80) //U0와 blending 되는 바탕색	we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 clr_bdr_cr                       :8;	//(31:24,RW,0x80) //Border 색지정	we can get 0x200(512) by setting lsb 2bits to "00" internally.
	};
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515F8 RW 0x1080_1080
	UINT32 clr_nac_cb                       :8;	//(7:0,RW,0x80) //U0와 blending 되는 바탕색	we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 clr_nac_y                        :8;	//(15:8,RW,0x10) //U0와 blending 되는 바탕색	we can get 0x40(64) by setting lsb 2bits to "00" internally.
	UINT32 clr_bdr_cb                       :8;	//(23:16,RW,0x80) //Border 색지정	we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 clr_bdr_y                        :8;	//(31:24,RW,0x10) //Border 색 지정	we can get 0x40(64) by setting lsb 2bits to "00" internally.
	};
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9515FC RW 0x1080_1080
	UINT32 w1_clr_dark_cb                   :8;	//(7:0,RW,0x80) //we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 w1_clr_dark_y                    :8;	//(15:8,RW,0x10) //we can get 0x40(64) by setting lsb 2bits to "00" internally.
	UINT32 w0_clr_dark_cb                   :8;	//(23:16,RW,0x80) //we can get 0x200(512) by setting lsb 2bits to "00" internally.
	UINT32 w0_clr_dark_y                    :8;	//(31:24,RW,0x10) //we can get 0x40(64) by setting lsb 2bits to "00" internally.
	};
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951604 RW 0x0000_0000
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
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951608 RW 0x0000_0066
	UINT32 y_mod_num                        :3;	//(2:0,RW,0x06) //mod 8%
	UINT32 resvd0                           :1;
	UINT32 c_mod_num                        :3;	//(6:4,RW,0x06) //mod 8%
	UINT32 resvd1                           :9;
	UINT32 last_pixel_padding               :1;	//(16,RW,0x00) //
	UINT32 resvd2                           :15;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95160C RW 0x0000_0000
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
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951610 RW 0x0000_0000
	UINT32 w0_clr_alpha                     :8;	//(7:0,RW,0x0) //0x00 : DN (w0_clr_alpha window)	0xFF : UP (Window 1)
	UINT32 w1_clr_alpha                     :8;	//(15:8,RW,0x0) //0x00 : DN (w0_clr_alpha window)	0xFF : UP (Window 1)
	UINT32 resvd                            :16;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951614 RW 0x0000_0000
	UINT32 set_ha_o_mux_ctrl                :4;	//(3:0,RW,0x00) //"0000" := display hactive	"0001" = w0 hactive	"0010" = w1 hactive
	UINT32 set_va_o_mux_ctrl                :4;	//(7:4,RW,0x00) //"0000" := display vactive	"0001" = w0 vactive	"0010" = w1 vactive
	UINT32 set_de_o_mux_ctrl                :4;	//(11:8,RW,0x00) //DE processing for SOSD ONLY	"0000" := display de	"0001" = w0_va&w0_ha	"0010" = w1_va&w1_ha	"0101" = (w0_va&w0_ha) | (w1_va&w1_ha)	"1000" = ~(w0_va&w0_ha)	"1001" = ~(w1_va&w1_ha)	"1100" = ~((w0_va&w0_ha) | (w1_va&w1_ha))
	UINT32 reg4_alpha                       :8;	//(19:12,RW,0x0) //0x00 background or U0   bottom	0xFF U0             or U1   top
	UINT32 resvd                            :3;
	UINT32 w1_clr_alpha_nac_en              :1;	//(23,RW,0x00) //
	UINT32 w1_clr_alpha_nac                 :8;	//(31:24,RW,0x0) //
	};
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951618 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_m_wcp         :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_m_wcp        :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 set_pic_init_c_mux_m_wcp         :4;	//(11:8,RW,0x00) //"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_m_wcp        :4;	//(15:12,RW,0x00) //"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 resvd                            :16;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951620 RW 0x0000_0000
	UINT32 pattern_y_pos                    :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pattern_x_pos                    :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_POS_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951624 RW 0x0000_0000
	UINT32 pattern_y_size                   :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pattern_x_size                   :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_SIZE_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951628 RW 0x0000_0000
	UINT32 pattern_y_pos                    :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pattern_x_pos                    :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_POS_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95162C RW 0x0000_0000
	UINT32 pattern_y_size                   :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 pattern_x_size                   :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_SIZE_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951630 RW 0x0010_8080
	UINT32 blanck_cr                        :8;	//(7:0,RW,0x80) //
	UINT32 blank_cb                         :8;	//(15:8,RW,0x80) //
	UINT32 blank_y                          :8;	//(23:16,RW,0x10) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_COLOR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951650 RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951654 RO 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951658 RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95165C RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951660 RW 0x0000_0000
	UINT32 win_pos_y0_auto                  :14;	//(13:0,RW,0x0) //Y start position of window.
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0_auto                  :14;	//(29:16,RW,0x0) //X start position of window.
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_PARAM_POS_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951664 RW 0x8000_0000
	UINT32 win_size_y_auto                  :14;	//(13:0,RW,0x0) //Y-size of window.
	UINT32 resvd                            :2;
	UINT32 win_size_x_auto                  :14;	//(29:16,RW,0x0) //X-size of window.
	UINT32 win_enable_4ch_auto              :1;	//(30,RW,0x00) //1' = 4ch pos/size control	'0' := 2ch pos/size control
	UINT32 win_enable_auto                  :1;	//(31,RW,0x01) //1' := auto pos/size control	'0' = manual pos/size control
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_PARAM_SIZE_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951668 RW 0x0000_0000
	UINT32 win_pos_y0_auto                  :14;	//(13:0,RW,0x0) //Y start position of window.
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0_auto                  :14;	//(29:16,RW,0x0) //X start position of window.
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_PARAM_POS_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95166C RW 0x8000_0000
	UINT32 win_size_y_auto                  :14;	//(13:0,RW,0x0) //Y-size of window.
	UINT32 resvd                            :2;
	UINT32 win_size_x_auto                  :14;	//(29:16,RW,0x0) //X-size of window.
	UINT32 win_enable_4ch_auto              :1;	//(30,RW,0x00) //1' = 4ch pos/size control	'0' := 2ch pos/size control
	UINT32 win_enable_auto                  :1;	//(31,RW,0x01) //1' := auto pos/size control	'0' = manual pos/size control
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_PARAM_SIZE_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951690 RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951694 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951698 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :26;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95169C RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9516A0 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9516A4 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :26;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9516C0 RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9516C4 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9516C8 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :26;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9516CC RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9516D0 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9516D4 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :26;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951720 RW 0x0000_0000
	UINT32 win_border_width_down            :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_up              :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951724 RW 0x0000_0000
	UINT32 win_border_width_right           :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_left            :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951728 RW 0x0000_0000
	UINT32 win_border_width_down            :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_up              :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95172C RW 0x0000_0000
	UINT32 win_border_width_right           :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_left            :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951730 RW 0x0000_0000
	UINT32 win_border_width_down            :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_up              :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951734 RW 0x0000_0000
	UINT32 win_border_width_right           :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_left            :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951738 RW 0x0000_0000
	UINT32 win_border_width_down            :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_up              :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95173C RW 0x0000_0000
	UINT32 win_border_width_right           :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 win_border_width_left            :14;	//(29:16,RW,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951780 RW 0x0000_0000
	UINT32 rec5_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec5_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec5_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC5_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951784 RW 0x0000_0000
	UINT32 rec5_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec5_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec5_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC5_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951788 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC5_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95178C RW 0x0000_0000
	UINT32 rec6_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec6_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec6_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC6_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951790 RW 0x0000_0000
	UINT32 rec6_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec6_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec6_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC6_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951794 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC6_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951798 RW 0x0000_0000
	UINT32 rec7_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec7_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec7_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC7_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95179C RW 0x0000_0000
	UINT32 rec7_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec7_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec7_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC7_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517A0 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC7_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517A4 RW 0x0000_0000
	UINT32 rec8_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec8_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec8_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC8_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517A8 RW 0x0000_0000
	UINT32 rec8_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec8_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec8_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC8_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517AC RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC8_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517B0 RW 0x0000_0000
	UINT32 rec9_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec9_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec9_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC9_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517B4 RW 0x0000_0000
	UINT32 rec9_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec9_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec9_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC9_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517B8 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC9_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517C0 RW 0x0000_0000
	UINT32 reg0_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg0_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg0_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg0_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG0_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517C4 RW 0x0000_0000
	UINT32 reg0_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg0_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG0_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517C8 RW 0x0000_0000
	UINT32 reg1_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg1_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg1_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg1_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG1_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517CC RW 0x0000_0000
	UINT32 reg1_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg1_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG1_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517D0 RW 0x0000_0000
	UINT32 reg2_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg2_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg2_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg2_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG2_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517D4 RW 0x0000_0000
	UINT32 reg2_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg2_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG2_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517D8 RW 0x0000_0000
	UINT32 reg3_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg3_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg3_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg3_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG3_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517DC RW 0x0000_0000
	UINT32 reg3_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg3_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG3_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517E0 RW 0x0000_0000
	UINT32 reg4_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg4_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg4_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg4_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG4_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517E4 RW 0x0000_0000
	UINT32 reg4_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg4_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG4_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517E8 RW 0x0000_0000
	UINT32 reg0_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg0_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg0_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg0_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG0_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517EC RW 0x0000_0000
	UINT32 reg0_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg0_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG0_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517F0 RW 0x0000_0000
	UINT32 reg1_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg1_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg1_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg1_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG1_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517F4 RW 0x0000_0000
	UINT32 reg1_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg1_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG1_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517F8 RW 0x0000_0000
	UINT32 reg2_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg2_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg2_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg2_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG2_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9517FC RW 0x0000_0000
	UINT32 reg2_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg2_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG2_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951800 RW 0x0000_0000
	UINT32 reg3_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg3_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg3_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg3_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG3_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951804 RW 0x0000_0000
	UINT32 reg3_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg3_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG3_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951808 RW 0x0000_0000
	UINT32 reg4_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 reg4_u1_en                       :1;	//(15,RW,0x00) //
	UINT32 reg4_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg4_u0_en                       :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG4_V1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95180C RW 0x0000_0000
	UINT32 reg4_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg4_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG4_V1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951810 RW 0x8000_0000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 clr_lsb_cr_reg0                  :4;	//(15:12,RW,0x0) //Cr [3:0]
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 clr_msb_cr_reg0                  :4;	//(31:28,RW,0x8) //Cr [7:4]
	};
}PE_O26_VCP_DISP_VCP_WCP_REG0_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951814 RW 0x8000_8000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 clr_lsb_cr_reg1                  :4;	//(15:12,RW,0x8) //Cr [3:0]
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 clr_msb_cr_reg1                  :4;	//(31:28,RW,0x8) //Cr [7:4]
	};
}PE_O26_VCP_DISP_VCP_WCP_REG1_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951818 RW 0x2000_C000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 clr_lsb_cr_reg2                  :4;	//(15:12,RW,0xC) //Cr [3:0]
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 clr_msb_cr_reg2                  :4;	//(31:28,RW,0x2) //Cr [7:4]
	};
}PE_O26_VCP_DISP_VCP_WCP_REG2_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95181C RW 0x3000_4000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 clr_lsb_cr_reg3                  :4;	//(15:12,RW,0x4) //Cr [3:0]
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 clr_msb_cr_reg3                  :4;	//(31:28,RW,0x3) //Cr [7:4]
	};
}PE_O26_VCP_DISP_VCP_WCP_REG3_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951820 RW 0x0000_0000
	UINT32 x_width                          :12;	//(11:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 y_height                         :12;	//(27:16,RW,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_VCP_DISP_VCP_WCP_REG4_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951824 RW 0xB480_A82C
	UINT32 clr_cb_reg1                      :8;	//(7:0,RW,0x2C) //
	UINT32 clr_yy_reg1                      :8;	//(15:8,RW,0xA8) //
	UINT32 clr_cb_reg0                      :8;	//(23:16,RW,0x80) //
	UINT32 clr_yy_reg0                      :8;	//(31:24,RW,0xB4) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG5_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951828 RW 0x9193_853F
	UINT32 clr_cb_reg3                      :8;	//(7:0,RW,0x3F) //
	UINT32 clr_yy_reg3                      :8;	//(15:8,RW,0x85) //
	UINT32 clr_cb_reg2                      :8;	//(23:16,RW,0x93) //
	UINT32 clr_yy_reg2                      :8;	//(31:24,RW,0x91) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG6_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95182C RW 0x336D_D400
	UINT32 w0_bdr_en                        :1;	//(0,RW,0x0) //
	UINT32 w1_bdr_en                        :1;	//(1,RW,0x0) //
	UINT32 resvd                            :6;
	UINT32 clr_cr_reg4                      :8;	//(15:8,RW,0xD4) //
	UINT32 clr_cb_reg4                      :8;	//(23:16,RW,0x6D) //
	UINT32 clr_yy_reg4                      :8;	//(31:24,RW,0x33) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG7_BDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951830 RW 0x0000_0000
	UINT32 reg0_alpha                       :8;	//(7:0,RW,0x0) //0x00 background or U0   bottom	0xFF U0             or U1   top
	UINT32 reg1_alpha                       :8;	//(15:8,RW,0x0) //
	UINT32 reg2_alpha                       :8;	//(23:16,RW,0x0) //
	UINT32 reg3_alpha                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_VCP_DISP_VCP_WCP_REG_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951834 RW 0x0000_0000
	UINT32 rec2_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec2_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec2_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC2_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951838 RW 0x0000_0000
	UINT32 rec2_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 rec2_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec2_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC2_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95183C RW 0x0000_0000
	UINT32 rec3_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec3_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec3_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951840 RW 0x0000_0000
	UINT32 rec3_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 rec3_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec3_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951844 RW 0x0000_0000
	UINT32 rec4_e_pos_x                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec4_s_pos_x                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec4_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC4_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951848 RW 0x0000_0000
	UINT32 rec4_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 rec4_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec4_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC4_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95184C RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC0_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951850 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC1_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951854 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC2_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951858 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC3_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95185C RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_VCP_DISP_VCP_WCP_M_REC4_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951860 RW 0x0200_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_O26_VCP_DISP_VCP_VSP_U0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951864 RW 0x0200_8000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VCP_DISP_VCP_VSP_U0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951868 RW 0x0200_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :7;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VCP_DISP_VCP_VSP_U1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95186C RW 0x0200_8000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VCP_DISP_VCP_VSP_U1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951870 RW 0x0000_00C0
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
}PE_O26_VCP_DISP_VCP_CRC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951874 RW 0xFFFF_FFFF
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_CRC_DATA_MASK0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951878 RW 0xFFFF_FFFF
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_CRC_DATA_MASK1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951884 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_CRC_OUT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951888 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VCP_DISP_VCP_CRC_OUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9518A0 RW 0x0000_0000
	UINT32 h_cnt                            :16;	//(15:0,RW,0x0) //
	UINT32 v_cnt                            :16;	//(31:16,RW,0x0) //
	};
}PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951900 RW 0xFFFF_FFFF
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
}PE_O26_VCP_DISP_VCP_DISP_INTR_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951904 RW 0x0000_0000
	UINT32 vcp_mv_y_disp_intr0_clear        :1;	//(0,RW,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_disp_intr1_clear        :1;	//(1,RW,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_w0_intr_clear           :1;	//(2,RW,0x00) //vcp main display window0 vactive falling
	UINT32 vcp_mv_y_w1_intr_clear           :1;	//(3,RW,0x00) //vcp main display window1 vactive falling
	UINT32 resvd                            :12;
	UINT32 vcp_mv_c_disp_intr0_clear        :1;	//(16,RW,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_disp_intr1_clear        :1;	//(17,RW,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_w0_intr_clear           :1;	//(18,RW,0x00) //vcp main display window0 vactive falling
	UINT32 vcp_mv_c_w1_intr_clear           :1;	//(19,RW,0x00) //vcp main display window1 vactive falling
	UINT32 sync_gen_trk_fal_clear           :1;	//(20,RW,0x00) //long period VRR
	UINT32 sync_gen_trk_ris_clear           :1;	//(21,RW,0x00) //long period VRR
	UINT32 sync_gen_trk2_ris_clear          :1;	//(22,RW,0x00) //wait VFP VRR
	UINT32 sync_gen_trk2_fal_clear          :1;	//(23,RW,0x00) //wait VFP VRR
	UINT32 sync_gen_h_seamless_ris_clear    :1;	//(24,RW,0x00) //h total change line delay  seamless
	UINT32 sync_gen_h_seamless_fal_clear    :1;	//(25,RW,0x00) //h total change line delay  seamless
	UINT32 sync_gen_disp_vsync_fal_clear    :1;	//(26,RW,0x00) //
	UINT32 sync_gen_cvi_vactive_fal_clear   :1;	//(27,RW,0x00) //
	UINT32 sync_gen_pvsync_fal_clear        :1;	//(28,RW,0x00) //
	UINT32 sync_gen_cvi_v_dly_fal_clear     :1;	//(29,RW,0x00) //
	UINT32 sync_gen_cvi_vsync_fal_clear     :1;	//(30,RW,0x00) //
	UINT32 sync_gen_vsync_fal_clear         :1;	//(31,RW,0x00) //
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951908 RO 0x0000_0000
	UINT32 vcp_mv_y_disp_intr0_status       :1;	//(0,RO,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_disp_intr1_status       :1;	//(1,RO,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_y_w0_intr_status          :1;	//(2,RO,0x00) //vcp main display window0 vactive falling
	UINT32 vcp_mv_y_w1_intr_status          :1;	//(3,RO,0x00) //vcp main display window1 vactive falling
	UINT32 resvd                            :12;
	UINT32 vcp_mv_c_disp_intr0_status       :1;	//(16,RO,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_disp_intr1_status       :1;	//(17,RO,0x00) //vcp main display vsync variable position control
	UINT32 vcp_mv_c_w0_intr_status          :1;	//(18,RO,0x00) //vcp main display window0 vactive falling
	UINT32 vcp_mv_c_w1_intr_status          :1;	//(19,RO,0x00) //vcp main display window1 vactive falling
	UINT32 sync_gen_trk_fal_status          :1;	//(20,RO,0x00) //long period VRR
	UINT32 sync_gen_trk_ris_status          :1;	//(21,RO,0x00) //long period VRR
	UINT32 sync_gen_trk2_ris_status         :1;	//(22,RO,0x00) //wait VFP VRR
	UINT32 sync_gen_trk2_fal_status         :1;	//(23,RO,0x00) //wait VFP VRR
	UINT32 sync_gen_h_seamless_ris_status   :1;	//(24,RO,0x00) //h total change line delay  seamless
	UINT32 sync_gen_h_seamless_fal_status   :1;	//(25,RO,0x00) //h total change line delay  seamless
	UINT32 sync_gen_disp_vsync_fal_status   :1;	//(26,RO,0x00) //
	UINT32 sync_gen_cvi_vactive_fal_status  :1;	//(27,RO,0x00) //
	UINT32 sync_gen_pvsync_fal_status       :1;	//(28,RO,0x00) //
	UINT32 sync_gen_cvi_v_dly_fal_status    :1;	//(29,RO,0x00) //
	UINT32 sync_gen_cvi_vsync_fal_status    :1;	//(30,RO,0x00) //
	UINT32 sync_gen_vsync_fal_status        :1;	//(31,RO,0x00) //
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95190C RW 0x0000_0000
	UINT32 vcp_mv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR0_POS_MV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951910 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR1_POS_MV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951914 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR0_POS_MV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951918 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR1_POS_MV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95191C RW 0x0000_0000
	UINT32 vcp_sv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR0_POS_SV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951920 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR1_POS_SV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951924 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR0_POS_SV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951928 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VCP_DISP_VCP_DISP_INTR1_POS_SV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95192C RW/RO 0x0000_0000
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
}PE_O26_VCP_DISP_VCP_DISP_INTR_SRC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951930 RW 0x0000_0000
	UINT32 resvd0                           :3;
	UINT32 vcp_422_mean_filter_en           :1;	//(3,RW,0x00) //1 : enable (odd pixel is changing to mean of even pixels)	0 : bypass
	UINT32 vcp_maunal_size                  :1;	//(4,RW,0x00) //1 : enable vcp_422_mean_filter_last_pixel	0 : vcp_sg_bdr_v0_param_size
	UINT32 resvd1                           :3;
	UINT32 vcp_422_mean_filter_last_pixel   :13;	//(20:8,RW,0x00) //size of mean filter	real size 3840 => 1920 setting size(dual pixel)
	UINT32 resvd2                           :11;
	};
}PE_O26_VCP_DISP_VCP_U0_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951934 RW 0x129F_7C98
	UINT32 vcp_csc_coefficient1             :15;	//(14:0,RW,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient0             :15;	//(30:16,RW,0x129F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_U1_CSC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951938 RW 0x7775_129F
	UINT32 vcp_csc_coefficient3             :15;	//(14:0,RW,0x129F) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient2             :15;	//(30:16,RW,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_U1_CSC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95193C RW 0x21D7_0000
	UINT32 vcp_csc_coefficient5             :15;	//(14:0,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient4             :15;	//(30:16,RW,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_U1_CSC_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951940 RW 0x129F_0000
	UINT32 vcp_csc_coefficient7             :15;	//(14:0,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient6             :15;	//(30:16,RW,0x129F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_U1_CSC_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951944 RW 0x1CB0_07C0
	UINT32 vcp_csc_offset0                  :11;	//(10:0,RW,0x7C0) //Pre add offset a	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_coefficient8             :15;	//(30:16,RW,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VCP_DISP_VCP_U1_CSC_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951948 RW 0x0600_0600
	UINT32 vcp_csc_offset2                  :11;	//(10:0,RW,0x600) //Pre add offset c	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_offset1                  :11;	//(26:16,RW,0x600) //Pre add offset b	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_O26_VCP_DISP_VCP_U1_CSC_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95194C RW 0x0000_0000
	UINT32 vcp_csc_offset4                  :11;	//(10:0,RW,0x00) //Post add offset y	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_offset3                  :11;	//(26:16,RW,0x00) //Post add offset x	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_O26_VCP_DISP_VCP_U1_CSC_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951950 RW/WO 0x0000_0000
	UINT32 vcp_csc_coeff_load               :1;	//(0,WO,0x00) //this bit is auto cleared
	UINT32 vcp_csc_en                       :1;	//(1,RW,0x0) //csc enable
	UINT32 vcp_csc_pcg_off                  :1;	//(2,RW,0x00) //power clock gating off
	UINT32 vcp_422_mean_filter_en           :1;	//(3,RW,0x00) //1 : enable (odd pixel is changing to mean of even pixels)	0 : bypass
	UINT32 vcp_maunal_size                  :1;	//(4,RW,0x00) //1 : enable vcp_422_mean_filter_last_pixel	0 : vcp_sg_bdr_v1_param_size
	UINT32 reg_debug                        :3;	//(7:5,RW,0x00) //
	UINT32 vcp_422_mean_filter_last_pixel   :13;	//(20:8,RW,0x00) //size of mean filter	real size 3840 => 1920 setting size(dual pixel)
	UINT32 vcp_csc_offset5                  :11;	//(31:21,RW,0x00) //Post add offset z	Range -1024~1023
	};
}PE_O26_VCP_DISP_VCP_U1_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951954 RW 0x0000_0000
	UINT32 vcp_active_line_cnt_en           :1;	//(0,RW,0x00) //0 : disable	1 : enable
	UINT32 vcp_cnt_ref                      :1;	//(1,RW,0x00) //0 : vsync rising	1 : vsync falling
	UINT32 vcp_active_line_cnt              :15;	//(16:2,RW,0x00) //
	UINT32 resvd                            :15;
	};
}PE_O26_VCP_DISP_VCP_ACTIVE_LINE_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951960 RW 0x0000_0040
	UINT32 read_en                          :1;	//(0,RW,0x0) //pixel read enable (8 pixel)
	UINT32 read_line                        :1;	//(1,RW,0x0) //cross hatch enable of pixel read start position
	UINT32 reg_patt_en                      :1;	//(2,RW,0x0) //rectangle pattern enable
	UINT32 reg_patt_fill                    :1;	//(3,RW,0x0) //rectangle pattern full fill enable
	UINT32 reg_line_alt                     :1;	//(4,RW,0x0) //line alternative pattern enable
	UINT32 reg_one_dot                      :1;	//(5,RW,0x0) //One Dot pattern enable
	UINT32 reg_pix_mode                     :2;	//(7:6,RW,0x1) //pixel mode	0 : 1p	1 : 2p	2 :=4p (fix)
	UINT32 reg_pattern_read                 :1;	//(8,RW,0x0) //0 := no use	1 :  read value = reg_yg/cb/cr_data8
	UINT32 resvd                            :23;
	};
}PE_O26_VCP_DISP_PIX_PAT_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951964 RW 0x0000_0000
	UINT32 reg_cb_white                     :12;	//(11:0,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_yg_white                     :12;	//(27:16,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd1                           :4;
	};
}PE_O26_VCP_DISP_PIX_PAT_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951968 RW 0x0000_0000
	UINT32 reg_yg_black                     :12;	//(11:0,RW,0x0000) //2nd color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_cr_white                     :12;	//(27:16,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd1                           :4;
	};
}PE_O26_VCP_DISP_PIX_PAT_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95196C RW 0x0000_0000
	UINT32 reg_cr_black                     :12;	//(11:0,RW,0x0000) //2nd color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_cb_black                     :12;	//(27:16,RW,0x0000) //2nd color of one dot
	UINT32 resvd1                           :4;
	};
}PE_O26_VCP_DISP_PIX_PAT_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951970 RW 0x0000_0000
	UINT32 y_size                           :16;	//(15:0,RW,0x0000) //input vertical   size
	UINT32 x_size                           :16;	//(31:16,RW,0x0000) //input horizontal size	actual hsize / 2
	};
}PE_O26_VCP_DISP_PIX_PAT_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951974 RW 0x0000_0000
	UINT32 y_read_pos                       :16;	//(15:0,RW,0x0000) //vertical read position
	UINT32 x_read_pos                       :16;	//(31:16,RW,0x0000) //horizontal read position
	};
}PE_O26_VCP_DISP_PIX_PAT_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951978 RW 0x0000_0000
	UINT32 x_pat_pos_end                    :16;	//(15:0,RW,0x0000) //rectangle patten's horizontal end position
	UINT32 x_pat_pos_str                    :16;	//(31:16,RW,0x0000) //rectangle patten's horizontal start position
	};
}PE_O26_VCP_DISP_PIX_PAT_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95197C RW 0x0000_0000
	UINT32 y_pat_pos_end                    :16;	//(15:0,RW,0x0000) //rectangle patten's vertical end position
	UINT32 y_pat_pos_str                    :16;	//(31:16,RW,0x0000) //rectangle patten's vertical start position
	};
}PE_O26_VCP_DISP_PIX_PAT_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951980 RO 0x0000_0000
	UINT32 pix0_cr_read                     :10;	//(9:0,RO,0x0000) //
	UINT32 pix0_cb_read                     :10;	//(19:10,RO,0x0000) //
	UINT32 pix0_yg_read                     :10;	//(29:20,RO,0x0000) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_PIX_READ0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951984 RO 0x0000_0000
	UINT32 pix1_cr_read                     :10;	//(9:0,RO,0x0000) //
	UINT32 pix1_cb_read                     :10;	//(19:10,RO,0x0000) //
	UINT32 pix1_yg_read                     :10;	//(29:20,RO,0x0000) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_PIX_READ1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951988 RO 0x0000_0000
	UINT32 pix2_cr_read                     :10;	//(9:0,RO,0x0000) //
	UINT32 pix2_cb_read                     :10;	//(19:10,RO,0x0000) //
	UINT32 pix2_yg_read                     :10;	//(29:20,RO,0x0000) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_PIX_READ2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95198C RO 0x0000_0000
	UINT32 pix3_cr_read                     :10;	//(9:0,RO,0x0000) //
	UINT32 pix3_cb_read                     :10;	//(19:10,RO,0x0000) //
	UINT32 pix3_yg_read                     :10;	//(29:20,RO,0x0000) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_PIX_READ3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951990 RO 0x0000_0000
	UINT32 pix4_cr_read                     :10;	//(9:0,RO,0x0000) //
	UINT32 pix4_cb_read                     :10;	//(19:10,RO,0x0000) //
	UINT32 pix4_yg_read                     :10;	//(29:20,RO,0x0000) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_PIX_READ4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951994 RO 0x0000_0000
	UINT32 pix5_cr_read                     :10;	//(9:0,RO,0x0000) //
	UINT32 pix5_cb_read                     :10;	//(19:10,RO,0x0000) //
	UINT32 pix5_yg_read                     :10;	//(29:20,RO,0x0000) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_PIX_READ5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC951998 RO 0x0000_0000
	UINT32 pix6_cr_read                     :10;	//(9:0,RO,0x0000) //
	UINT32 pix6_cb_read                     :10;	//(19:10,RO,0x0000) //
	UINT32 pix6_yg_read                     :10;	//(29:20,RO,0x0000) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_PIX_READ6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95199C RO 0x0000_0000
	UINT32 pix7_cr_read                     :10;	//(9:0,RO,0x0000) //
	UINT32 pix7_cb_read                     :10;	//(19:10,RO,0x0000) //
	UINT32 pix7_yg_read                     :10;	//(29:20,RO,0x0000) //
	UINT32 resvd                            :2;
	};
}PE_O26_VCP_DISP_PIX_READ7_T;

typedef struct {
	PE_O26_VCP_DISP_VCP_DISP_CTRL0_T                        vcp_disp_ctrl0;	//0xCC951400
	PE_O26_VCP_DISP_VCP_DISP_CTRL1_T                        vcp_disp_ctrl1;	//0xCC951404
	PE_O26_VCP_DISP_VCP_DISP_CTRL2_T                        vcp_disp_ctrl2;	//0xCC951408
	PE_O26_VCP_DISP_VCP_DISP_CTRL3_T                        vcp_disp_ctrl3;	//0xCC95140C
	UINT32                                                       reserved0;	//0xCC951410
	PE_O26_VCP_DISP_VCP_CDC_MV_RST_CTRL_T              vcp_cdc_mv_rst_ctrl;	//0xCC951414
	UINT32                                                       reserved1;	//0xCC951418
	UINT32                                                       reserved2;	//0xCC95141C
	PE_O26_VCP_DISP_VCP_U0_WIN_O_POS_T                    vcp_u0_win_o_pos;	//0xCC951420
	PE_O26_VCP_DISP_VCP_U0_WIN_O_SIZE_T                  vcp_u0_win_o_size;	//0xCC951424
	PE_O26_VCP_DISP_VCP_U0_PG_PAT_CTRL_T                vcp_u0_pg_pat_ctrl;	//0xCC951428
	PE_O26_VCP_DISP_VCP_U0_PG_PEAK_SIZE_T              vcp_u0_pg_peak_size;	//0xCC95142C
	PE_O26_VCP_DISP_VCP_U0_CDC_Y_CTRL0_T                vcp_u0_cdc_y_ctrl0;	//0xCC951430
	PE_O26_VCP_DISP_VCP_U0_CDC_Y_CTRL1_T                vcp_u0_cdc_y_ctrl1;	//0xCC951434
	PE_O26_VCP_DISP_VCP_U0_CDC_Y_CTRL2_T                vcp_u0_cdc_y_ctrl2;	//0xCC951438
	PE_O26_VCP_DISP_VCP_U0_CDC_Y_STATUS_T              vcp_u0_cdc_y_status;	//0xCC95143C
	PE_O26_VCP_DISP_VCP_U0_CDC_C_CTRL0_T                vcp_u0_cdc_c_ctrl0;	//0xCC951440
	PE_O26_VCP_DISP_VCP_U0_CDC_C_CTRL1_T                vcp_u0_cdc_c_ctrl1;	//0xCC951444
	PE_O26_VCP_DISP_VCP_U0_CDC_C_CTRL2_T                vcp_u0_cdc_c_ctrl2;	//0xCC951448
	PE_O26_VCP_DISP_VCP_U0_CDC_C_STATUS_T              vcp_u0_cdc_c_status;	//0xCC95144C
	PE_O26_VCP_DISP_VCP_U1_WIN_O_POS_T                    vcp_u1_win_o_pos;	//0xCC951450
	PE_O26_VCP_DISP_VCP_U1_WIN_O_SIZE_T                  vcp_u1_win_o_size;	//0xCC951454
	PE_O26_VCP_DISP_VCP_U1_PG_PAT_CTRL_T                vcp_u1_pg_pat_ctrl;	//0xCC951458
	PE_O26_VCP_DISP_VCP_U1_PG_PEAK_SIZE_T              vcp_u1_pg_peak_size;	//0xCC95145C
	PE_O26_VCP_DISP_VCP_U1_CDC_Y_CTRL0_T                vcp_u1_cdc_y_ctrl0;	//0xCC951460
	PE_O26_VCP_DISP_VCP_U1_CDC_Y_CTRL1_T                vcp_u1_cdc_y_ctrl1;	//0xCC951464
	PE_O26_VCP_DISP_VCP_U1_CDC_Y_CTRL2_T                vcp_u1_cdc_y_ctrl2;	//0xCC951468
	PE_O26_VCP_DISP_VCP_U1_CDC_Y_STATUS_T              vcp_u1_cdc_y_status;	//0xCC95146C
	PE_O26_VCP_DISP_VCP_U1_CDC_C_CTRL0_T                vcp_u1_cdc_c_ctrl0;	//0xCC951470
	PE_O26_VCP_DISP_VCP_U1_CDC_C_CTRL1_T                vcp_u1_cdc_c_ctrl1;	//0xCC951474
	PE_O26_VCP_DISP_VCP_U1_CDC_C_CTRL2_T                vcp_u1_cdc_c_ctrl2;	//0xCC951478
	PE_O26_VCP_DISP_VCP_U1_CDC_C_STATUS_T              vcp_u1_cdc_c_status;	//0xCC95147C
	PE_O26_VCP_DISP_VCP_U0_WIN_O_POS_AUX_T            vcp_u0_win_o_pos_aux;	//0xCC951480
	PE_O26_VCP_DISP_VCP_U0_WIN_O_SIZE_AUX_T          vcp_u0_win_o_size_aux;	//0xCC951484
	PE_O26_VCP_DISP_VCP_U1_WIN_O_POS_AUX_T            vcp_u1_win_o_pos_aux;	//0xCC951488
	PE_O26_VCP_DISP_VCP_U1_WIN_O_SIZE_AUX_T          vcp_u1_win_o_size_aux;	//0xCC95148C
	UINT32                                                       reserved3;	//0xCC951490
	UINT32                                                       reserved4;	//0xCC951494
	UINT32                                                       reserved5;	//0xCC951498
	UINT32                                                       reserved6;	//0xCC95149C
	UINT32                                                       reserved7;	//0xCC9514A0
	UINT32                                                       reserved8;	//0xCC9514A4
	UINT32                                                       reserved9;	//0xCC9514A8
	UINT32                                                      reserved10;	//0xCC9514AC
	UINT32                                                      reserved11;	//0xCC9514B0
	UINT32                                                      reserved12;	//0xCC9514B4
	UINT32                                                      reserved13;	//0xCC9514B8
	UINT32                                                      reserved14;	//0xCC9514BC
	UINT32                                                      reserved15;	//0xCC9514C0
	UINT32                                                      reserved16;	//0xCC9514C4
	UINT32                                                      reserved17;	//0xCC9514C8
	UINT32                                                      reserved18;	//0xCC9514CC
	UINT32                                                      reserved19;	//0xCC9514D0
	UINT32                                                      reserved20;	//0xCC9514D4
	UINT32                                                      reserved21;	//0xCC9514D8
	UINT32                                                      reserved22;	//0xCC9514DC
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_0_T                  vcp_sg_mvy_ctrl_0;	//0xCC9514E0
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_1_T                  vcp_sg_mvy_ctrl_1;	//0xCC9514E4
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_2_T                  vcp_sg_mvy_ctrl_2;	//0xCC9514E8
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_3_T                  vcp_sg_mvy_ctrl_3;	//0xCC9514EC
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_4_T                  vcp_sg_mvy_ctrl_4;	//0xCC9514F0
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_5_T                  vcp_sg_mvy_ctrl_5;	//0xCC9514F4
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_6_T                  vcp_sg_mvy_ctrl_6;	//0xCC9514F8
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_7_T                  vcp_sg_mvy_ctrl_7;	//0xCC9514FC
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_8_T                  vcp_sg_mvy_ctrl_8;	//0xCC951500
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_9_T                  vcp_sg_mvy_ctrl_9;	//0xCC951504
	UINT32                                                      reserved23;	//0xCC951508
	UINT32                                                      reserved24;	//0xCC95150C
	UINT32                                                      reserved25;	//0xCC951510
	UINT32                                                      reserved26;	//0xCC951514
	UINT32                                                      reserved27;	//0xCC951518
	UINT32                                                      reserved28;	//0xCC95151C
	UINT32                                                      reserved29;	//0xCC951520
	UINT32                                                      reserved30;	//0xCC951524
	UINT32                                                      reserved31;	//0xCC951528
	UINT32                                                      reserved32;	//0xCC95152C
	UINT32                                                      reserved33;	//0xCC951530
	UINT32                                                      reserved34;	//0xCC951534
	UINT32                                                      reserved35;	//0xCC951538
	UINT32                                                      reserved36;	//0xCC95153C
	UINT32                                                      reserved37;	//0xCC951540
	UINT32                                                      reserved38;	//0xCC951544
	UINT32                                                      reserved39;	//0xCC951548
	UINT32                                                      reserved40;	//0xCC95154C
	UINT32                                                      reserved41;	//0xCC951550
	UINT32                                                      reserved42;	//0xCC951554
	UINT32                                                      reserved43;	//0xCC951558
	UINT32                                                      reserved44;	//0xCC95155C
	UINT32                                                      reserved45;	//0xCC951560
	UINT32                                                      reserved46;	//0xCC951564
	UINT32                                                      reserved47;	//0xCC951568
	UINT32                                                      reserved48;	//0xCC95156C
	UINT32                                                      reserved49;	//0xCC951570
	UINT32                                                      reserved50;	//0xCC951574
	UINT32                                                      reserved51;	//0xCC951578
	UINT32                                                      reserved52;	//0xCC95157C
	UINT32                                                      reserved53;	//0xCC951580
	UINT32                                                      reserved54;	//0xCC951584
	UINT32                                                      reserved55;	//0xCC951588
	UINT32                                                      reserved56;	//0xCC95158C
	UINT32                                                      reserved57;	//0xCC951590
	UINT32                                                      reserved58;	//0xCC951594
	UINT32                                                      reserved59;	//0xCC951598
	UINT32                                                      reserved60;	//0xCC95159C
	UINT32                                                      reserved61;	//0xCC9515A0
	UINT32                                                      reserved62;	//0xCC9515A4
	UINT32                                                      reserved63;	//0xCC9515A8
	UINT32                                                      reserved64;	//0xCC9515AC
	UINT32                                                      reserved65;	//0xCC9515B0
	UINT32                                                      reserved66;	//0xCC9515B4
	PE_O26_VCP_DISP_VCP_WCP_M_DISP_SIZE_T              vcp_wcp_m_disp_size;	//0xCC9515B8
	PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_CTRL_T          vcp_wcp_m_pg_pat_ctrl;	//0xCC9515BC
	UINT32                                                      reserved67;	//0xCC9515C0
	UINT32                                                      reserved68;	//0xCC9515C4
	PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_CTRL_T  vcp_wcp_m_pixel_read_ctrl;	//0xCC9515C8
	PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T vcp_wcp_m_pixel_read_ctrl_aux;	//0xCC9515CC
	PE_O26_VCP_DISP_VCP_WCP_M_LINE_CTRL0_T            vcp_wcp_m_line_ctrl0;	//0xCC9515D0
	PE_O26_VCP_DISP_VCP_WCP_M_LINE_CTRL1_T            vcp_wcp_m_line_ctrl1;	//0xCC9515D4
	UINT32                                                      reserved69;	//0xCC9515D8
	UINT32                                                      reserved70;	//0xCC9515DC
	PE_O26_VCP_DISP_VCP_WCP_M_REC0_POS_X_T            vcp_wcp_m_rec0_pos_x;	//0xCC9515E0
	PE_O26_VCP_DISP_VCP_WCP_M_REC0_POS_Y_T            vcp_wcp_m_rec0_pos_y;	//0xCC9515E4
	PE_O26_VCP_DISP_VCP_WCP_M_REC1_POS_X_T            vcp_wcp_m_rec1_pos_x;	//0xCC9515E8
	PE_O26_VCP_DISP_VCP_WCP_M_REC1_POS_Y_T            vcp_wcp_m_rec1_pos_y;	//0xCC9515EC
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_0_T                    vcp_wcp_m_ctrl_0;	//0xCC9515F0
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_1_T                    vcp_wcp_m_ctrl_1;	//0xCC9515F4
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_2_T                    vcp_wcp_m_ctrl_2;	//0xCC9515F8
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_3_T                    vcp_wcp_m_ctrl_3;	//0xCC9515FC
	UINT32                                                      reserved71;	//0xCC951600
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_5_T                    vcp_wcp_m_ctrl_5;	//0xCC951604
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_6_T                    vcp_wcp_m_ctrl_6;	//0xCC951608
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_7_T                    vcp_wcp_m_ctrl_7;	//0xCC95160C
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_8_T                    vcp_wcp_m_ctrl_8;	//0xCC951610
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_9_T                    vcp_wcp_m_ctrl_9;	//0xCC951614
	PE_O26_VCP_DISP_VCP_WCP_M_CTRL_10_T                  vcp_wcp_m_ctrl_10;	//0xCC951618
	UINT32                                                      reserved72;	//0xCC95161C
	PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_POS_0_T        vcp_wcp_m_pg_pat_pos_0;	//0xCC951620
	PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_SIZE_0_T      vcp_wcp_m_pg_pat_size_0;	//0xCC951624
	PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_POS_1_T        vcp_wcp_m_pg_pat_pos_1;	//0xCC951628
	PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_SIZE_1_T      vcp_wcp_m_pg_pat_size_1;	//0xCC95162C
	PE_O26_VCP_DISP_VCP_WCP_M_PG_PAT_COLOR_T        vcp_wcp_m_pg_pat_color;	//0xCC951630
	UINT32                                                      reserved73;	//0xCC951634
	UINT32                                                      reserved74;	//0xCC951638
	UINT32                                                      reserved75;	//0xCC95163C
	UINT32                                                      reserved76;	//0xCC951640
	UINT32                                                      reserved77;	//0xCC951644
	UINT32                                                      reserved78;	//0xCC951648
	UINT32                                                      reserved79;	//0xCC95164C
	PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_0_T vcp_wcp_m_pixel_read_data_0;	//0xCC951650
	PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_1_T vcp_wcp_m_pixel_read_data_1;	//0xCC951654
	PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_2_T vcp_wcp_m_pixel_read_data_2;	//0xCC951658
	PE_O26_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_3_T vcp_wcp_m_pixel_read_data_3;	//0xCC95165C
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_PARAM_POS_M_T  vcp_sg_bdr_v0_param_pos_m;	//0xCC951660
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_PARAM_SIZE_M_T vcp_sg_bdr_v0_param_size_m;	//0xCC951664
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_PARAM_POS_M_T  vcp_sg_bdr_v1_param_pos_m;	//0xCC951668
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_PARAM_SIZE_M_T vcp_sg_bdr_v1_param_size_m;	//0xCC95166C
	UINT32                                                      reserved80;	//0xCC951670
	UINT32                                                      reserved81;	//0xCC951674
	UINT32                                                      reserved82;	//0xCC951678
	UINT32                                                      reserved83;	//0xCC95167C
	UINT32                                                      reserved84;	//0xCC951680
	UINT32                                                      reserved85;	//0xCC951684
	UINT32                                                      reserved86;	//0xCC951688
	UINT32                                                      reserved87;	//0xCC95168C
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_0_T    vcp_sg_bdr_v0_0_m_ctrl_0;	//0xCC951690
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_1_T    vcp_sg_bdr_v0_0_m_ctrl_1;	//0xCC951694
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_2_T    vcp_sg_bdr_v0_0_m_ctrl_2;	//0xCC951698
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_0_T    vcp_sg_bdr_v0_1_m_ctrl_0;	//0xCC95169C
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_1_T    vcp_sg_bdr_v0_1_m_ctrl_1;	//0xCC9516A0
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_2_T    vcp_sg_bdr_v0_1_m_ctrl_2;	//0xCC9516A4
	UINT32                                                      reserved88;	//0xCC9516A8
	UINT32                                                      reserved89;	//0xCC9516AC
	UINT32                                                      reserved90;	//0xCC9516B0
	UINT32                                                      reserved91;	//0xCC9516B4
	UINT32                                                      reserved92;	//0xCC9516B8
	UINT32                                                      reserved93;	//0xCC9516BC
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_0_T    vcp_sg_bdr_v1_0_m_ctrl_0;	//0xCC9516C0
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_1_T    vcp_sg_bdr_v1_0_m_ctrl_1;	//0xCC9516C4
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_2_T    vcp_sg_bdr_v1_0_m_ctrl_2;	//0xCC9516C8
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_0_T    vcp_sg_bdr_v1_1_m_ctrl_0;	//0xCC9516CC
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_1_T    vcp_sg_bdr_v1_1_m_ctrl_1;	//0xCC9516D0
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_2_T    vcp_sg_bdr_v1_1_m_ctrl_2;	//0xCC9516D4
	UINT32                                                      reserved94;	//0xCC9516D8
	UINT32                                                      reserved95;	//0xCC9516DC
	UINT32                                                      reserved96;	//0xCC9516E0
	UINT32                                                      reserved97;	//0xCC9516E4
	UINT32                                                      reserved98;	//0xCC9516E8
	UINT32                                                      reserved99;	//0xCC9516EC
	UINT32                                                     reserved100;	//0xCC9516F0
	UINT32                                                     reserved101;	//0xCC9516F4
	UINT32                                                     reserved102;	//0xCC9516F8
	UINT32                                                     reserved103;	//0xCC9516FC
	UINT32                                                     reserved104;	//0xCC951700
	UINT32                                                     reserved105;	//0xCC951704
	UINT32                                                     reserved106;	//0xCC951708
	UINT32                                                     reserved107;	//0xCC95170C
	UINT32                                                     reserved108;	//0xCC951710
	UINT32                                                     reserved109;	//0xCC951714
	UINT32                                                     reserved110;	//0xCC951718
	UINT32                                                     reserved111;	//0xCC95171C
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_3_T    vcp_sg_bdr_v0_0_m_ctrl_3;	//0xCC951720
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_4_T    vcp_sg_bdr_v0_0_m_ctrl_4;	//0xCC951724
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_3_T    vcp_sg_bdr_v0_1_m_ctrl_3;	//0xCC951728
	PE_O26_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_4_T    vcp_sg_bdr_v0_1_m_ctrl_4;	//0xCC95172C
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_3_T    vcp_sg_bdr_v1_0_m_ctrl_3;	//0xCC951730
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_4_T    vcp_sg_bdr_v1_0_m_ctrl_4;	//0xCC951734
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_3_T    vcp_sg_bdr_v1_1_m_ctrl_3;	//0xCC951738
	PE_O26_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_4_T    vcp_sg_bdr_v1_1_m_ctrl_4;	//0xCC95173C
	UINT32                                                     reserved112;	//0xCC951740
	UINT32                                                     reserved113;	//0xCC951744
	UINT32                                                     reserved114;	//0xCC951748
	UINT32                                                     reserved115;	//0xCC95174C
	UINT32                                                     reserved116;	//0xCC951750
	UINT32                                                     reserved117;	//0xCC951754
	UINT32                                                     reserved118;	//0xCC951758
	UINT32                                                     reserved119;	//0xCC95175C
	UINT32                                                     reserved120;	//0xCC951760
	UINT32                                                     reserved121;	//0xCC951764
	UINT32                                                     reserved122;	//0xCC951768
	UINT32                                                     reserved123;	//0xCC95176C
	UINT32                                                     reserved124;	//0xCC951770
	UINT32                                                     reserved125;	//0xCC951774
	UINT32                                                     reserved126;	//0xCC951778
	UINT32                                                     reserved127;	//0xCC95177C
	PE_O26_VCP_DISP_VCP_WCP_M_REC5_POS_X_T            vcp_wcp_m_rec5_pos_x;	//0xCC951780
	PE_O26_VCP_DISP_VCP_WCP_M_REC5_POS_Y_T            vcp_wcp_m_rec5_pos_y;	//0xCC951784
	PE_O26_VCP_DISP_VCP_WCP_M_REC5_CLR_T                vcp_wcp_m_rec5_clr;	//0xCC951788
	PE_O26_VCP_DISP_VCP_WCP_M_REC6_POS_X_T            vcp_wcp_m_rec6_pos_x;	//0xCC95178C
	PE_O26_VCP_DISP_VCP_WCP_M_REC6_POS_Y_T            vcp_wcp_m_rec6_pos_y;	//0xCC951790
	PE_O26_VCP_DISP_VCP_WCP_M_REC6_CLR_T                vcp_wcp_m_rec6_clr;	//0xCC951794
	PE_O26_VCP_DISP_VCP_WCP_M_REC7_POS_X_T            vcp_wcp_m_rec7_pos_x;	//0xCC951798
	PE_O26_VCP_DISP_VCP_WCP_M_REC7_POS_Y_T            vcp_wcp_m_rec7_pos_y;	//0xCC95179C
	PE_O26_VCP_DISP_VCP_WCP_M_REC7_CLR_T                vcp_wcp_m_rec7_clr;	//0xCC9517A0
	PE_O26_VCP_DISP_VCP_WCP_M_REC8_POS_X_T            vcp_wcp_m_rec8_pos_x;	//0xCC9517A4
	PE_O26_VCP_DISP_VCP_WCP_M_REC8_POS_Y_T            vcp_wcp_m_rec8_pos_y;	//0xCC9517A8
	PE_O26_VCP_DISP_VCP_WCP_M_REC8_CLR_T                vcp_wcp_m_rec8_clr;	//0xCC9517AC
	PE_O26_VCP_DISP_VCP_WCP_M_REC9_POS_X_T            vcp_wcp_m_rec9_pos_x;	//0xCC9517B0
	PE_O26_VCP_DISP_VCP_WCP_M_REC9_POS_Y_T            vcp_wcp_m_rec9_pos_y;	//0xCC9517B4
	PE_O26_VCP_DISP_VCP_WCP_M_REC9_CLR_T                vcp_wcp_m_rec9_clr;	//0xCC9517B8
	UINT32                                                     reserved128;	//0xCC9517BC
	PE_O26_VCP_DISP_VCP_WCP_REG0_V0_POS_X_T          vcp_wcp_reg0_v0_pos_x;	//0xCC9517C0
	PE_O26_VCP_DISP_VCP_WCP_REG0_V0_POS_Y_T          vcp_wcp_reg0_v0_pos_y;	//0xCC9517C4
	PE_O26_VCP_DISP_VCP_WCP_REG1_V0_POS_X_T          vcp_wcp_reg1_v0_pos_x;	//0xCC9517C8
	PE_O26_VCP_DISP_VCP_WCP_REG1_V0_POS_Y_T          vcp_wcp_reg1_v0_pos_y;	//0xCC9517CC
	PE_O26_VCP_DISP_VCP_WCP_REG2_V0_POS_X_T          vcp_wcp_reg2_v0_pos_x;	//0xCC9517D0
	PE_O26_VCP_DISP_VCP_WCP_REG2_V0_POS_Y_T          vcp_wcp_reg2_v0_pos_y;	//0xCC9517D4
	PE_O26_VCP_DISP_VCP_WCP_REG3_V0_POS_X_T          vcp_wcp_reg3_v0_pos_x;	//0xCC9517D8
	PE_O26_VCP_DISP_VCP_WCP_REG3_V0_POS_Y_T          vcp_wcp_reg3_v0_pos_y;	//0xCC9517DC
	PE_O26_VCP_DISP_VCP_WCP_REG4_V0_POS_X_T          vcp_wcp_reg4_v0_pos_x;	//0xCC9517E0
	PE_O26_VCP_DISP_VCP_WCP_REG4_V0_POS_Y_T          vcp_wcp_reg4_v0_pos_y;	//0xCC9517E4
	PE_O26_VCP_DISP_VCP_WCP_REG0_V1_POS_X_T          vcp_wcp_reg0_v1_pos_x;	//0xCC9517E8
	PE_O26_VCP_DISP_VCP_WCP_REG0_V1_POS_Y_T          vcp_wcp_reg0_v1_pos_y;	//0xCC9517EC
	PE_O26_VCP_DISP_VCP_WCP_REG1_V1_POS_X_T          vcp_wcp_reg1_v1_pos_x;	//0xCC9517F0
	PE_O26_VCP_DISP_VCP_WCP_REG1_V1_POS_Y_T          vcp_wcp_reg1_v1_pos_y;	//0xCC9517F4
	PE_O26_VCP_DISP_VCP_WCP_REG2_V1_POS_X_T          vcp_wcp_reg2_v1_pos_x;	//0xCC9517F8
	PE_O26_VCP_DISP_VCP_WCP_REG2_V1_POS_Y_T          vcp_wcp_reg2_v1_pos_y;	//0xCC9517FC
	PE_O26_VCP_DISP_VCP_WCP_REG3_V1_POS_X_T          vcp_wcp_reg3_v1_pos_x;	//0xCC951800
	PE_O26_VCP_DISP_VCP_WCP_REG3_V1_POS_Y_T          vcp_wcp_reg3_v1_pos_y;	//0xCC951804
	PE_O26_VCP_DISP_VCP_WCP_REG4_V1_POS_X_T          vcp_wcp_reg4_v1_pos_x;	//0xCC951808
	PE_O26_VCP_DISP_VCP_WCP_REG4_V1_POS_Y_T          vcp_wcp_reg4_v1_pos_y;	//0xCC95180C
	PE_O26_VCP_DISP_VCP_WCP_REG0_BDR_T                    vcp_wcp_reg0_bdr;	//0xCC951810
	PE_O26_VCP_DISP_VCP_WCP_REG1_BDR_T                    vcp_wcp_reg1_bdr;	//0xCC951814
	PE_O26_VCP_DISP_VCP_WCP_REG2_BDR_T                    vcp_wcp_reg2_bdr;	//0xCC951818
	PE_O26_VCP_DISP_VCP_WCP_REG3_BDR_T                    vcp_wcp_reg3_bdr;	//0xCC95181C
	PE_O26_VCP_DISP_VCP_WCP_REG4_BDR_T                    vcp_wcp_reg4_bdr;	//0xCC951820
	PE_O26_VCP_DISP_VCP_WCP_REG5_BDR_T                    vcp_wcp_reg5_bdr;	//0xCC951824
	PE_O26_VCP_DISP_VCP_WCP_REG6_BDR_T                    vcp_wcp_reg6_bdr;	//0xCC951828
	PE_O26_VCP_DISP_VCP_WCP_REG7_BDR_T                    vcp_wcp_reg7_bdr;	//0xCC95182C
	PE_O26_VCP_DISP_VCP_WCP_REG_ALPHA_T                  vcp_wcp_reg_alpha;	//0xCC951830
	PE_O26_VCP_DISP_VCP_WCP_M_REC2_POS_X_T            vcp_wcp_m_rec2_pos_x;	//0xCC951834
	PE_O26_VCP_DISP_VCP_WCP_M_REC2_POS_Y_T            vcp_wcp_m_rec2_pos_y;	//0xCC951838
	PE_O26_VCP_DISP_VCP_WCP_M_REC3_POS_X_T            vcp_wcp_m_rec3_pos_x;	//0xCC95183C
	PE_O26_VCP_DISP_VCP_WCP_M_REC3_POS_Y_T            vcp_wcp_m_rec3_pos_y;	//0xCC951840
	PE_O26_VCP_DISP_VCP_WCP_M_REC4_POS_X_T            vcp_wcp_m_rec4_pos_x;	//0xCC951844
	PE_O26_VCP_DISP_VCP_WCP_M_REC4_POS_Y_T            vcp_wcp_m_rec4_pos_y;	//0xCC951848
	PE_O26_VCP_DISP_VCP_WCP_M_REC0_CLR_T                vcp_wcp_m_rec0_clr;	//0xCC95184C
	PE_O26_VCP_DISP_VCP_WCP_M_REC1_CLR_T                vcp_wcp_m_rec1_clr;	//0xCC951850
	PE_O26_VCP_DISP_VCP_WCP_M_REC2_CLR_T                vcp_wcp_m_rec2_clr;	//0xCC951854
	PE_O26_VCP_DISP_VCP_WCP_M_REC3_CLR_T                vcp_wcp_m_rec3_clr;	//0xCC951858
	PE_O26_VCP_DISP_VCP_WCP_M_REC4_CLR_T                vcp_wcp_m_rec4_clr;	//0xCC95185C
	PE_O26_VCP_DISP_VCP_VSP_U0_CTRL_00_T                vcp_vsp_u0_ctrl_00;	//0xCC951860
	PE_O26_VCP_DISP_VCP_VSP_U0_CTRL_01_T                vcp_vsp_u0_ctrl_01;	//0xCC951864
	PE_O26_VCP_DISP_VCP_VSP_U1_CTRL_00_T                vcp_vsp_u1_ctrl_00;	//0xCC951868
	PE_O26_VCP_DISP_VCP_VSP_U1_CTRL_01_T                vcp_vsp_u1_ctrl_01;	//0xCC95186C
	PE_O26_VCP_DISP_VCP_CRC_CTRL_T                            vcp_crc_ctrl;	//0xCC951870
	PE_O26_VCP_DISP_VCP_CRC_DATA_MASK0_T                vcp_crc_data_mask0;	//0xCC951874
	PE_O26_VCP_DISP_VCP_CRC_DATA_MASK1_T                vcp_crc_data_mask1;	//0xCC951878
	UINT32                                                     reserved129;	//0xCC95187C
	UINT32                                                     reserved130;	//0xCC951880
	PE_O26_VCP_DISP_VCP_CRC_OUT0_T                            vcp_crc_out0;	//0xCC951884
	PE_O26_VCP_DISP_VCP_CRC_OUT1_T                            vcp_crc_out1;	//0xCC951888
	UINT32                                                     reserved131;	//0xCC95188C
	UINT32                                                     reserved132;	//0xCC951890
	UINT32                                                     reserved133;	//0xCC951894
	UINT32                                                     reserved134;	//0xCC951898
	UINT32                                                     reserved135;	//0xCC95189C
	PE_O26_VCP_DISP_VCP_SG_MVY_CTRL_A_T                  vcp_sg_mvy_ctrl_a;	//0xCC9518A0
	UINT32                                                     reserved136;	//0xCC9518A4
	UINT32                                                     reserved137;	//0xCC9518A8
	UINT32                                                     reserved138;	//0xCC9518AC
	UINT32                                                     reserved139;	//0xCC9518B0
	UINT32                                                     reserved140;	//0xCC9518B4
	UINT32                                                     reserved141;	//0xCC9518B8
	UINT32                                                     reserved142;	//0xCC9518BC
	UINT32                                                     reserved143;	//0xCC9518C0
	UINT32                                                     reserved144;	//0xCC9518C4
	UINT32                                                     reserved145;	//0xCC9518C8
	UINT32                                                     reserved146;	//0xCC9518CC
	UINT32                                                     reserved147;	//0xCC9518D0
	UINT32                                                     reserved148;	//0xCC9518D4
	UINT32                                                     reserved149;	//0xCC9518D8
	UINT32                                                     reserved150;	//0xCC9518DC
	UINT32                                                     reserved151;	//0xCC9518E0
	UINT32                                                     reserved152;	//0xCC9518E4
	UINT32                                                     reserved153;	//0xCC9518E8
	UINT32                                                     reserved154;	//0xCC9518EC
	UINT32                                                     reserved155;	//0xCC9518F0
	UINT32                                                     reserved156;	//0xCC9518F4
	UINT32                                                     reserved157;	//0xCC9518F8
	UINT32                                                     reserved158;	//0xCC9518FC
	PE_O26_VCP_DISP_VCP_DISP_INTR_MASK_T                vcp_disp_intr_mask;	//0xCC951900
	PE_O26_VCP_DISP_VCP_DISP_INTR_CLEAR_T              vcp_disp_intr_clear;	//0xCC951904
	PE_O26_VCP_DISP_VCP_DISP_INTR_STATUS_T            vcp_disp_intr_status;	//0xCC951908
	PE_O26_VCP_DISP_VCP_DISP_INTR0_POS_MV_Y_T      vcp_disp_intr0_pos_mv_y;	//0xCC95190C
	PE_O26_VCP_DISP_VCP_DISP_INTR1_POS_MV_Y_T      vcp_disp_intr1_pos_mv_y;	//0xCC951910
	PE_O26_VCP_DISP_VCP_DISP_INTR0_POS_MV_C_T      vcp_disp_intr0_pos_mv_c;	//0xCC951914
	PE_O26_VCP_DISP_VCP_DISP_INTR1_POS_MV_C_T      vcp_disp_intr1_pos_mv_c;	//0xCC951918
	PE_O26_VCP_DISP_VCP_DISP_INTR0_POS_SV_Y_T      vcp_disp_intr0_pos_sv_y;	//0xCC95191C
	PE_O26_VCP_DISP_VCP_DISP_INTR1_POS_SV_Y_T      vcp_disp_intr1_pos_sv_y;	//0xCC951920
	PE_O26_VCP_DISP_VCP_DISP_INTR0_POS_SV_C_T      vcp_disp_intr0_pos_sv_c;	//0xCC951924
	PE_O26_VCP_DISP_VCP_DISP_INTR1_POS_SV_C_T      vcp_disp_intr1_pos_sv_c;	//0xCC951928
	PE_O26_VCP_DISP_VCP_DISP_INTR_SRC_SEL_T          vcp_disp_intr_src_sel;	//0xCC95192C
	PE_O26_VCP_DISP_VCP_U0_CSC_CTRL7_T                    vcp_u0_csc_ctrl7;	//0xCC951930
	PE_O26_VCP_DISP_VCP_U1_CSC_CTRL0_T                    vcp_u1_csc_ctrl0;	//0xCC951934
	PE_O26_VCP_DISP_VCP_U1_CSC_CTRL1_T                    vcp_u1_csc_ctrl1;	//0xCC951938
	PE_O26_VCP_DISP_VCP_U1_CSC_CTRL2_T                    vcp_u1_csc_ctrl2;	//0xCC95193C
	PE_O26_VCP_DISP_VCP_U1_CSC_CTRL3_T                    vcp_u1_csc_ctrl3;	//0xCC951940
	PE_O26_VCP_DISP_VCP_U1_CSC_CTRL4_T                    vcp_u1_csc_ctrl4;	//0xCC951944
	PE_O26_VCP_DISP_VCP_U1_CSC_CTRL5_T                    vcp_u1_csc_ctrl5;	//0xCC951948
	PE_O26_VCP_DISP_VCP_U1_CSC_CTRL6_T                    vcp_u1_csc_ctrl6;	//0xCC95194C
	PE_O26_VCP_DISP_VCP_U1_CSC_CTRL7_T                    vcp_u1_csc_ctrl7;	//0xCC951950
	PE_O26_VCP_DISP_VCP_ACTIVE_LINE_CNT_T              vcp_active_line_cnt;	//0xCC951954
	UINT32                                                     reserved159;	//0xCC951958
	UINT32                                                     reserved160;	//0xCC95195C
	PE_O26_VCP_DISP_PIX_PAT_CTRL0_T                          pix_pat_ctrl0;	//0xCC951960
	PE_O26_VCP_DISP_PIX_PAT_CTRL1_T                          pix_pat_ctrl1;	//0xCC951964
	PE_O26_VCP_DISP_PIX_PAT_CTRL2_T                          pix_pat_ctrl2;	//0xCC951968
	PE_O26_VCP_DISP_PIX_PAT_CTRL3_T                          pix_pat_ctrl3;	//0xCC95196C
	PE_O26_VCP_DISP_PIX_PAT_CTRL4_T                          pix_pat_ctrl4;	//0xCC951970
	PE_O26_VCP_DISP_PIX_PAT_CTRL5_T                          pix_pat_ctrl5;	//0xCC951974
	PE_O26_VCP_DISP_PIX_PAT_CTRL6_T                          pix_pat_ctrl6;	//0xCC951978
	PE_O26_VCP_DISP_PIX_PAT_CTRL7_T                          pix_pat_ctrl7;	//0xCC95197C
	PE_O26_VCP_DISP_PIX_READ0_T                                  pix_read0;	//0xCC951980
	PE_O26_VCP_DISP_PIX_READ1_T                                  pix_read1;	//0xCC951984
	PE_O26_VCP_DISP_PIX_READ2_T                                  pix_read2;	//0xCC951988
	PE_O26_VCP_DISP_PIX_READ3_T                                  pix_read3;	//0xCC95198C
	PE_O26_VCP_DISP_PIX_READ4_T                                  pix_read4;	//0xCC951990
	PE_O26_VCP_DISP_PIX_READ5_T                                  pix_read5;	//0xCC951994
	PE_O26_VCP_DISP_PIX_READ6_T                                  pix_read6;	//0xCC951998
	PE_O26_VCP_DISP_PIX_READ7_T                                  pix_read7;	//0xCC95199C
}PE_VCP_DISP_REG_O26_T;



typedef union {
	UINT32 udata32;
	struct {						//0xCCC72200 RW 0x0000_0000
	UINT32 reg_imux_sel                     :5;	//(4:0,NA,0x0) //// =======================================================; // reg_imux_sel| layer 0 | layer 1 | layer 2 | layer 3 ; // =======================================================; // 00 (00000) | 0 | 1 | 2 | 3 | = default mode; // 01 (00001) | 0 | 1 | 3 | 2 | ; // 02 (00010) | 0 | 2 | 1 | 3 | ; // 03 (00011) | 0 | 2 | 3 | 1 | ; // 04 (00100) | 0 | 3 | 1 | 2 | ; // 05 (00101) | 0 | 3 | 2 | 1 | ; // 06 (00110) | 0 | 1 | 2 | 3 | = same as 00 (don't use); // 07 (00111) | 0 | 1 | 2 | 3 | = same as 00 (don't use); // 08 (01000) | 1 | 0 | 2 | 3 | ; // 09 (01001) | 1 | 0 | 3 | 2 | ; // 10 (01010) | 1 | 2 | 0 | 3 | ; // 11 (01011) | 1 | 2 | 3 | 0 | ; // 12 (01100) | 1 | 3 | 0 | 2 | ; // 13 (01101) | 1 | 3 | 2 | 0 | ; // 14 (01110) | 1 | 0 | 2 | 3 | = same as 08 (don't use); // 15 (01111) | 1 | 0 | 2 | 3 | = same as 08 (don't use); // 16 (10000) | 2 | 0 | 1 | 3 | ; // 17 (10001) | 2 | 0 | 3 | 1 | ; // 18 (10010) | 2 | 1 | 0 | 3 | ; // 19 (10011) | 2 | 1 | 3 | 0 | ; // 20 (10100) | 2 | 3 | 0 | 1 | ; // 21 (10101) | 2 | 3 | 1 | 0 | ; // 22 (10110) | 2 | 0 | 1 | 3 | = same as 16 (don't use); // 23 (10111) | 2 | 0 | 1 | 3 | = same as 16 (don't use); // 24 (11000) | 3 | 0 | 1 | 2 | ; // 25 (11001) | 3 | 0 | 2 | 1 | ; // 26 (11010) | 3 | 1 | 0 | 2 | ; // 27 (11011) | 3 | 1 | 2 | 0 | ; // 28 (11100) | 3 | 2 | 0 | 1 | ; // 29 (11101) | 3 | 2 | 1 | 0 | ; // 30 (11110) | 3 | 0 | 1 | 2 | = same as 24 (don't use); // 31 (11111) | 3 | 0 | 1 | 2 | = same as 24 (don't use); // =======================================================
	UINT32 reg_out_mask_off                 :1;	//(5,NA,0x0) //
	UINT32 reg_inp_mask_off                 :1;	//(6,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_l3_en                        :1;	//(10,NA,0x0) //use layer3
	UINT32 reg_l2_en                        :1;	//(11,NA,0x0) //use layer2
	UINT32 reg_l1_en                        :1;	//(12,NA,0x0) //use layer1
	UINT32 reg_l0_en                        :1;	//(13,NA,0x0) //use layer0
	UINT32 reg_pa_l3_en                     :1;	//(14,NA,0x0) //use pixel alpha of layer3
	UINT32 reg_pa_l2_en                     :1;	//(15,NA,0x0) //use pixel alpha of layer2
	UINT32 reg_pa_l1_en                     :1;	//(16,NA,0x0) //use pixel alpha of layer1
	UINT32 reg_pa_l0_en                     :1;	//(17,NA,0x0) //use pixel alpha of layer0
	UINT32 reg_ga_3_en                      :1;	//(18,NA,0x0) //use global alpha 3
	UINT32 reg_ga_2_en                      :1;	//(19,NA,0x0) //use global alpha 2
	UINT32 reg_ga_1_en                      :1;	//(20,NA,0x0) //use global alpha 1
	UINT32 reg_ga_0_en                      :1;	//(21,NA,0x0) //use global alpha 0
	UINT32 reg_bg_en                        :1;	//(22,NA,0x0) //use bg
	UINT32 reg_rv_merg_4_en                 :1;	//(23,NA,0x0) //out channel merge
	UINT32 reg_rv_merg_3_en                 :1;	//(24,NA,0x0) //in3 channel merge
	UINT32 reg_rv_merg_2_en                 :1;	//(25,NA,0x0) //in2 channel merge
	UINT32 reg_rv_merg_1_en                 :1;	//(26,NA,0x0) //in1 channel merge
	UINT32 reg_rv_merg_0_en                 :1;	//(27,NA,0x0) //in0 channel merge
	UINT32 reg_sel_detour                   :2;	//(29:28,NA,0x0) //0: in0, 1: in1, 2: in2, 3: in3
	UINT32 reg_detour_core_en               :1;	//(30,NA,0x0) //core detour
	UINT32 resvd1                           :1;
	};
}PE_O26_VLB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72204 RW 0x0F00_0870
	UINT32 reg_img_heigt                    :14;	//(13:0,NA,0x870) //canvas height
	UINT32 resvd                            :2;
	UINT32 reg_img_width                    :14;	//(29:16,NA,0xF00) //canvas width
	UINT32 reg_cs_type                      :2;	//(31:30,NA,0x0) //0: 444, 1: 422, 3: 420
	};
}PE_O26_VLB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72208 RW 0x0000_0000
	UINT32 reg_bg_val_rr                    :10;	//(9:0,NA,0x0) //background value
	UINT32 reg_bg_val_bb                    :10;	//(19:10,NA,0x0) //background value
	UINT32 reg_bg_val_gy                    :10;	//(29:20,NA,0x0) //background value
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7220C RW 0x3FF0_0000
	UINT32 resvd0                           :20;
	UINT32 reg_ga_0                         :10;	//(29:20,NA,0x3FF) //layer0 global alpha
	UINT32 resvd1                           :2;
	};
}PE_O26_VLB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72210 RW 0x2008_0200
	UINT32 reg_ga_3                         :10;	//(9:0,NA,0x200) //layer3 global alpha
	UINT32 reg_ga_2                         :10;	//(19:10,NA,0x200) //layer2 global alpha
	UINT32 reg_ga_1                         :10;	//(29:20,NA,0x200) //layer1 global alpha
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72214 RW 0x0F00_0F00
	UINT32 reg_rbuf_width_c                 :14;	//(13:0,NA,0xF00) //VLB(C)
	UINT32 resvd                            :2;
	UINT32 reg_rbuf_width_y                 :14;	//(29:16,NA,0xF00) //VLB(Y), GLB(ARGB)
	UINT32 reg_rbuf_c_detour_en             :1;	//(30,NA,0x0) //
	UINT32 reg_rbuf_y_detour_en             :1;	//(31,NA,0x0) //
	};
}PE_O26_VLB_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72218 RW 0x0000_0000
	UINT32 reg_vlb_ctrl_06_rsvd             :32;	//(31:0,NA,0x0) //
	};
}PE_O26_VLB_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7221C RW 0x0000_0F00
	UINT32 reg_l0_ep_x                      :13;	//(12:0,NA,0xF00) //end position x
	UINT32 resvd0                           :3;
	UINT32 reg_l0_sp_x                      :13;	//(28:16,NA,0x000) //start position x
	UINT32 resvd1                           :3;
	};
}PE_O26_VLB_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72220 RW 0x0000_0870
	UINT32 reg_l0_ep_y                      :13;	//(12:0,NA,0x870) //end position y
	UINT32 resvd0                           :3;
	UINT32 reg_l0_sp_y                      :13;	//(28:16,NA,0x000) //start position y
	UINT32 resvd1                           :3;
	};
}PE_O26_VLB_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72224 RW 0x0000_0000
	UINT32 reg_l1_ep_x                      :13;	//(12:0,NA,0x0) //end position x
	UINT32 resvd0                           :3;
	UINT32 reg_l1_sp_x                      :13;	//(28:16,NA,0x0) //start position x
	UINT32 resvd1                           :3;
	};
}PE_O26_VLB_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72228 RW 0x0000_0000
	UINT32 reg_l1_ep_y                      :13;	//(12:0,NA,0x0) //end position y
	UINT32 resvd0                           :3;
	UINT32 reg_l1_sp_y                      :13;	//(28:16,NA,0x0) //start position y
	UINT32 resvd1                           :3;
	};
}PE_O26_VLB_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7222C RW 0x0000_0000
	UINT32 reg_l2_ep_x                      :13;	//(12:0,NA,0x0) //end position x
	UINT32 resvd0                           :3;
	UINT32 reg_l2_sp_x                      :13;	//(28:16,NA,0x0) //start position x
	UINT32 resvd1                           :3;
	};
}PE_O26_VLB_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72230 RW 0x0000_0000
	UINT32 reg_l2_ep_y                      :13;	//(12:0,NA,0x0) //end position y
	UINT32 resvd0                           :3;
	UINT32 reg_l2_sp_y                      :13;	//(28:16,NA,0x0) //start position y
	UINT32 resvd1                           :3;
	};
}PE_O26_VLB_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72234 RW 0x0000_0000
	UINT32 reg_l3_ep_x                      :13;	//(12:0,NA,0x0) //end position x
	UINT32 resvd0                           :3;
	UINT32 reg_l3_sp_x                      :13;	//(28:16,NA,0x0) //start position x
	UINT32 resvd1                           :3;
	};
}PE_O26_VLB_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72238 RW 0x0000_0000
	UINT32 reg_l3_ep_y                      :13;	//(12:0,NA,0x0) //end position y
	UINT32 resvd0                           :3;
	UINT32 reg_l3_sp_y                      :13;	//(28:16,NA,0x0) //start position y
	UINT32 resvd1                           :3;
	};
}PE_O26_VLB_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7223C RW 0x0000_0000
	UINT32 reg_ckey_l0_bb_lo                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l0_gy_hi                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l0_gy_lo                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ckey_l0_en                   :1;	//(31,NA,0x0) //
	};
}PE_O26_VLB_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72240 RW 0x0000_0000
	UINT32 reg_ckey_l0_rr_hi                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l0_rr_lo                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l0_bb_hi                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72244 RW 0x0000_0000
	UINT32 reg_ckey_l0_bg_val_rr            :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l0_bg_val_bb            :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l0_bg_val_gy            :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72248 RW 0x0000_0000
	UINT32 resvd0                           :20;
	UINT32 reg_ckey_l0_bg_alpha             :10;	//(29:20,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VLB_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7224C RW 0x0000_0000
	UINT32 reg_ckey_l1_bb_lo                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l1_gy_hi                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l1_gy_lo                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ckey_l1_en                   :1;	//(31,NA,0x0) //
	};
}PE_O26_VLB_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72250 RW 0x0000_0000
	UINT32 reg_ckey_l1_rr_hi                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l1_rr_lo                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l1_bb_hi                :10;	//(29:20,NA,0x0) //
	UINT32 resvd							:2; //(31:30,NA,0x0)
	};
}PE_O26_VLB_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72254 RW 0x0000_0000
	UINT32 reg_ckey_l1_bg_val_rr            :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l1_bg_val_bb            :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l1_bg_val_gy            :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72258 RW 0x0000_0000
	UINT32 resvd0                           :20;
	UINT32 reg_ckey_l1_bg_alpha             :10;	//(29:20,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VLB_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7225C RW 0x0000_0000
	UINT32 reg_ckey_l2_bb_lo                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l2_gy_hi                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l2_gy_lo                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ckey_l2_en                   :1;	//(31,NA,0x0) //
	};
}PE_O26_VLB_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72260 RW 0x0000_0000
	UINT32 reg_ckey_l2_rr_hi                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l2_rr_lo                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l2_bb_hi                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72264 RW 0x0000_0000
	UINT32 reg_ckey_l2_bg_val_rr            :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l2_bg_val_bb            :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l2_bg_val_gy            :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72268 RW 0x0000_0000
	UINT32 resvd0                           :20;
	UINT32 reg_ckey_l2_bg_alpha             :10;	//(29:20,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VLB_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7226C RW 0x0000_0000
	UINT32 reg_ckey_l3_bb_lo                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l3_gy_hi                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l3_gy_lo                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ckey_l3_en                   :1;	//(31,NA,0x0) //
	};
}PE_O26_VLB_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72270 RW 0x0000_0000
	UINT32 reg_ckey_l3_rr_hi                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l3_rr_lo                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l3_bb_hi                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72274 RW 0x0000_0000
	UINT32 reg_ckey_l3_bg_val_rr            :10;	//(9:0,NA,0x0) //
	UINT32 reg_ckey_l3_bg_val_bb            :10;	//(19:10,NA,0x0) //
	UINT32 reg_ckey_l3_bg_val_gy            :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72278 RW 0x0000_0000
	UINT32 resvd0                           :20;
	UINT32 reg_ckey_l3_bg_alpha             :10;	//(29:20,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VLB_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7227C RW 0x0000_0000
	UINT32 resvd0                           :20;
	UINT32 reg_force_vld_en                 :1;	//(20,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_ptn_mode                     :1;	//(24,NA,0x0) //0: hv_ramp, 1: h_ramp
	UINT32 resvd2                           :3;
	UINT32 reg_ptn_gen_en                   :1;	//(28,NA,0x0) //
	UINT32 resvd3                           :3;
	};
}PE_O26_VLB_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72280 RW 0x0000_0000
	UINT32 reg_mute_aa                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :10;
	UINT32 reg_mute_en                      :1;	//(20,NA,0x0) //
	UINT32 resvd1                           :11;
	};
}PE_O26_VLB_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72284 RW 0x0008_0200
	UINT32 reg_mute_rr                      :10;	//(9:0,NA,0x200) //
	UINT32 reg_mute_bb                      :10;	//(19:10,NA,0x200) //
	UINT32 reg_mute_gy                      :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_VLB_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC72288 RW 0x0000_0000
	UINT32 reg_comm_stat_en                 :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_comm_stat_sel                :5;	//(8:4,NA,0x0) //
	UINT32 resvd1                           :23;
	};
}PE_O26_VLB_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC722A0 RO 0x0000_0000
	UINT32 reg_rbuf_y_mem_emty              :1;	//(0,NA,0x0) //
	UINT32 reg_rbuf_y_mem_full              :1;	//(1,NA,0x0) //
	UINT32 reg_rbuf_c_mem_emty              :1;	//(2,NA,0x0) //
	UINT32 reg_rbuf_c_mem_full              :1;	//(3,NA,0x0) //
	UINT32 resvd                            :28;
	};
}PE_O26_VLB_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC722A4 RO 0x0000_0000
	UINT32 reg_comm_stat_vcnt_max           :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_comm_stat_hcnt_max           :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_VLB_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC722A8 RO 0x0000_0000
	UINT32 reg_comm_stat_vcnt_live          :14;	//(13:0,NA,0x0) //
	UINT32 resvd                            :18;
	};
}PE_O26_VLB_STAT_02_T;

typedef struct {
	PE_O26_VLB_CTRL_00_T                           reg_vlb_ctrl_00;	//0xCCC72200
	PE_O26_VLB_CTRL_01_T                           reg_vlb_ctrl_01;	//0xCCC72204
	PE_O26_VLB_CTRL_02_T                           reg_vlb_ctrl_02;	//0xCCC72208
	PE_O26_VLB_CTRL_03_T                           reg_vlb_ctrl_03;	//0xCCC7220C
	PE_O26_VLB_CTRL_04_T                           reg_vlb_ctrl_04;	//0xCCC72210
	PE_O26_VLB_CTRL_05_T                           reg_vlb_ctrl_05;	//0xCCC72214
	PE_O26_VLB_CTRL_06_T                           reg_vlb_ctrl_06;	//0xCCC72218
	PE_O26_VLB_CTRL_07_T                           reg_vlb_ctrl_07;	//0xCCC7221C
	PE_O26_VLB_CTRL_08_T                           reg_vlb_ctrl_08;	//0xCCC72220
	PE_O26_VLB_CTRL_09_T                           reg_vlb_ctrl_09;	//0xCCC72224
	PE_O26_VLB_CTRL_10_T                           reg_vlb_ctrl_10;	//0xCCC72228
	PE_O26_VLB_CTRL_11_T                           reg_vlb_ctrl_11;	//0xCCC7222C
	PE_O26_VLB_CTRL_12_T                           reg_vlb_ctrl_12;	//0xCCC72230
	PE_O26_VLB_CTRL_13_T                           reg_vlb_ctrl_13;	//0xCCC72234
	PE_O26_VLB_CTRL_14_T                           reg_vlb_ctrl_14;	//0xCCC72238
	PE_O26_VLB_CTRL_15_T                           reg_vlb_ctrl_15;	//0xCCC7223C
	PE_O26_VLB_CTRL_16_T                           reg_vlb_ctrl_16;	//0xCCC72240
	PE_O26_VLB_CTRL_17_T                           reg_vlb_ctrl_17;	//0xCCC72244
	PE_O26_VLB_CTRL_18_T                           reg_vlb_ctrl_18;	//0xCCC72248
	PE_O26_VLB_CTRL_19_T                           reg_vlb_ctrl_19;	//0xCCC7224C
	PE_O26_VLB_CTRL_20_T                           reg_vlb_ctrl_20;	//0xCCC72250
	PE_O26_VLB_CTRL_21_T                           reg_vlb_ctrl_21;	//0xCCC72254
	PE_O26_VLB_CTRL_22_T                           reg_vlb_ctrl_22;	//0xCCC72258
	PE_O26_VLB_CTRL_23_T                           reg_vlb_ctrl_23;	//0xCCC7225C
	PE_O26_VLB_CTRL_24_T                           reg_vlb_ctrl_24;	//0xCCC72260
	PE_O26_VLB_CTRL_25_T                           reg_vlb_ctrl_25;	//0xCCC72264
	PE_O26_VLB_CTRL_26_T                           reg_vlb_ctrl_26;	//0xCCC72268
	PE_O26_VLB_CTRL_27_T                           reg_vlb_ctrl_27;	//0xCCC7226C
	PE_O26_VLB_CTRL_28_T                           reg_vlb_ctrl_28;	//0xCCC72270
	PE_O26_VLB_CTRL_29_T                           reg_vlb_ctrl_29;	//0xCCC72274
	PE_O26_VLB_CTRL_30_T                           reg_vlb_ctrl_30;	//0xCCC72278
	PE_O26_VLB_CTRL_31_T                           reg_vlb_ctrl_31;	//0xCCC7227C
	PE_O26_VLB_CTRL_32_T                           reg_vlb_ctrl_32;	//0xCCC72280
	PE_O26_VLB_CTRL_33_T                           reg_vlb_ctrl_33;	//0xCCC72284
	PE_O26_VLB_CTRL_34_T                           reg_vlb_ctrl_34;	//0xCCC72288
	UINT32                                                    reserved0;	//0xCCC7228C
	UINT32                                                    reserved1;	//0xCCC72290
	UINT32                                                    reserved2;	//0xCCC72294
	UINT32                                                    reserved3;	//0xCCC72298
	UINT32                                                    reserved4;	//0xCCC7229C
	PE_O26_VLB_STAT_00_T                           reg_vlb_stat_00;	//0xCCC722A0
	PE_O26_VLB_STAT_01_T                           reg_vlb_stat_01;	//0xCCC722A4
	PE_O26_VLB_STAT_02_T                           reg_vlb_stat_02;	//0xCCC722A8
}PE_VLB_REG_O26_T;

#endif
