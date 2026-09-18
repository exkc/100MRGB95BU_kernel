#ifndef _PE_VCP_REG_M23A0_H_
#define _PE_VCP_REG_M23A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1400 RW 0x1F0F_1F0F
	UINT32 mask_pic_init_y_mux_u0_cdc       :1;	//(0,RW,0x01) //
	UINT32 mask_pic_init_c_mux_u0_cdc       :1;	//(1,RW,0x01) //
	UINT32 mask_pic_init_y_mux_u1_cdc       :1;	//(2,RW,0x01) //
	UINT32 mask_pic_init_c_mux_u1_cdc       :1;	//(3,RW,0x01) //
	UINT32 resvd0                           :4;
	UINT32 mask_pic_init_y_mux_m_wcp        :1;	//(8,RW,0x01) //
	UINT32 mask_pic_init_c_mux_m_wcp        :1;	//(9,RW,0x01) //
	UINT32 reserved0                        :2;	//(10,RW,0x01) //
	UINT32 mask_pic_init_y_mux_ms_wcp       :1;	//(12,RW,0x01) //
	UINT32 mask_pic_init_c_mux_ms_wcp       :1;	//(13,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 mask_pic_start_y_mux_u0_cdc      :1;	//(16,RW,0x01) //
	UINT32 mask_pic_start_c_mux_u0_cdc      :1;	//(17,RW,0x01) //
	UINT32 mask_pic_start_y_mux_u1_cdc      :1;	//(18,RW,0x01) //
	UINT32 mask_pic_start_c_mux_u1_cdc      :1;	//(19,RW,0x01) //
	UINT32 resvd2                           :4;
	UINT32 mask_pic_start_y_mux_m_wcp       :1;	//(24,RW,0x01) //
	UINT32 mask_pic_start_c_mux_m_wcp       :1;	//(25,RW,0x01) //
	UINT32 reserved1                        :2;	//(26,RW,0x01) //
	UINT32 resvd3                           :4;
	};
}PE_M23_VCP_DISP_VCP_DISP_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1404 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_DISP_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1408 RW 0x0000_0000
	UINT32 set_inverse_3d_lr                :1;	//(0,RW,0x00) //
	UINT32 vcp_u1_disp_clk_cg               :1;	//(1,RW,0x00) //VCP U1 Disp Clock Gating ON	0 := Off	1 := On
	UINT32 resvd0                           :2;
	UINT32 wcp_m_mix_enable                 :2;	//(5:4,RW,0x00) //for debugging	"00" := main default.	"01" = PIP/R2 full video
	UINT32 cg_disable                       :1;	//(6,RW,0x00) //0 : Clock gating, 1 : disable CG
	UINT32 resvd1                           :1;
	UINT32 en_bypass_sync_my                :1;	//(8,RW,0x00) //
	UINT32 en_bypass_sync_mc                :1;	//(9,RW,0x00) //
	UINT32 en_bypass_sync_sy                :1;	//(10,RW,0x00) //
	UINT32 en_bypass_sync_sc                :1;	//(11,RW,0x00) //
	UINT32 resvd2                           :20;
	};
}PE_M23_VCP_DISP_VCP_DISP_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F140C RO 0x2018_0715
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_DISP_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1410 RW 0x0000_0000
	UINT32 u0_cdc_y_sync_sel                :2;	//(1:0,RW,0x00) //"00" := main display sync	"01" = sub display sync
	UINT32 u0_cdc_c_sync_sel                :2;	//(3:2,RW,0x00) //"00" := main display sync	"01" = sub display sync
	UINT32 u1_cdc_y_sync_sel                :2;	//(5:4,RW,0x00) //"00" := main display sync	"01" = sub display sync
	UINT32 u1_cdc_c_sync_sel                :2;	//(7:6,RW,0x00) //"00" := main display sync	"01" = sub display sync
	UINT32 resvd0                           :8;
	UINT32 mon_u0_cdc_y_pi_ps_pos_sel       :2;	//(17:16,RW,0x00) //"00" := disable monitor	"01" = enable monitor for main display sync	"10" = enable monitor for sub display sync	"11" = enable monitor for SR sync
	UINT32 mon_u0_cdc_c_pi_ps_pos_sel       :2;	//(19:18,RW,0x00) //"00" := disable monitor	"01" = enable monitor for main display sync	"10" = enable monitor for sub display sync
	UINT32 mon_u1_cdc_y_pi_ps_pos_sel       :2;	//(21:20,RW,0x00) //"00" := disable monitor	"01" = enable monitor for main display sync	"10" = enable monitor for sub display sync
	UINT32 mon_u1_cdc_c_pi_ps_pos_sel       :2;	//(23:22,RW,0x00) //"00" := disable monitor	"01" = enable monitor for main display sync	"10" = enable monitor for sub display sync
	UINT32 resvd1                           :8;
	};
}PE_M23_VCP_DISP_VCP_CDC_MV_SYNC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1414 RW 0x0000_0000
	UINT32 u0_cdc_y_disp_sreset             :1;	//(0,RW,0x00) //CDC_DISP sreset
	UINT32 u0_cdc_c_disp_sreset             :1;	//(1,RW,0x00) //CDC_DISP sreset
	UINT32 u1_cdc_y_disp_sreset             :1;	//(2,RW,0x00) //CDC_DISP sreset
	UINT32 u1_cdc_c_disp_sreset             :1;	//(3,RW,0x00) //CDC_DISP sreset
	UINT32 resvd                            :28;
	};
}PE_M23_VCP_DISP_VCP_CDC_MV_RST_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1420 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y                  :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x                  :13;	//(28:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_U0_WIN_O_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1424 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y                 :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x                 :13;	//(28:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_U0_WIN_O_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1428 RW 0x0000_0000
	UINT32 resvd0                           :4;
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
}PE_M23_VCP_DISP_VCP_U0_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F142C RW 0x0000_0780
	UINT32 peak_hsize                       :12;	//(11:0,RW,0x780) //cdc_win_o_size_x/2 round-up  2P
	UINT32 peak_offset                      :1;	//(12,RW,0x0) //cdc_win_o_pos_x[0]
	UINT32 resvd0                           :2;
	UINT32 peak_manual                      :1;	//(15,RW,0x0) //auto position release for debug
	UINT32 resvd1                           :16;
	};
}PE_M23_VCP_DISP_VCP_U0_PG_PEAK_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1430 RW 0x0820_0000
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
	UINT32 cdc_lsb_omode                    :4;	//(31:28,RW,0x00) //"0000" := even/odd lsb 2bits native.	"0001" = even/odd lsb 2bits "00".	"0010" = even/odd lsb 2bits "11"	'0011" = even lsb 2bits "00", odd lsb 2bits native.	"0100" = even lsb 2bits native, odd lsb 2bits "00".	"0101" = even lsb 2bits "11", odd lsb 2bits native.	"0110" = even lsb 2bits native, odd lsb 2bits "11".	"0111" = even/odd lsb 2bits native.
	};
}PE_M23_VCP_DISP_VCP_U0_CDC_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1434 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_U0_CDC_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1438 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_u0_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_u0_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_M23_VCP_DISP_VCP_U0_CDC_Y_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F143C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_U0_CDC_Y_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1440 RW 0x0820_0000
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
	UINT32 cdc_lsb_omode                    :4;	//(31:28,RW,0x00) //"0000" := even/odd lsb 2bits native.	"0001" = even/odd lsb 2bits "00".	"0010" = even/odd lsb 2bits "11"	'0011" = even lsb 2bits "00", odd lsb 2bits native.	"0100" = even lsb 2bits native, odd lsb 2bits "00".	"0101" = even lsb 2bits "11", odd lsb 2bits native.	"0110" = even lsb 2bits native, odd lsb 2bits "11".	"0111" = even/odd lsb 2bits native.
	};
}PE_M23_VCP_DISP_VCP_U0_CDC_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1444 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_U0_CDC_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1448 RW 0x0000_0000
	UINT32 set_pic_init_c_mux_u0_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_u0_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_M23_VCP_DISP_VCP_U0_CDC_C_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F144C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_U0_CDC_C_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1450 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y                  :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x                  :13;	//(28:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_U1_WIN_O_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1454 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y                 :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x                 :13;	//(28:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_U1_WIN_O_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1458 RW 0x0000_0000
	UINT32 resvd0                           :4;
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
}PE_M23_VCP_DISP_VCP_U1_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F145C RW 0x0000_0780
	UINT32 peak_hsize                       :12;	//(11:0,RW,0x780) //cdc_win_o_size_x/2 round-up  2P
	UINT32 peak_offset                      :1;	//(12,RW,0x0) //cdc_win_o_pos_x[0]
	UINT32 resvd0                           :2;
	UINT32 peak_manual                      :1;	//(15,RW,0x0) //auto position release for debug
	UINT32 resvd1                           :16;
	};
}PE_M23_VCP_DISP_VCP_U1_PG_PEAK_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1460 RW 0x0820_0000
	UINT32 cdc_voffset                      :5;	//(4:0,RW,0x0) //CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//(5,RW,0x00) //
	UINT32 cdc_auto_v_half                  :1;	//(6,RW,0x00) //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//(7,RW,0x00) //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//(10:8,RW,0x00) //"000" := all line ready processing.	"001" = 2^1 th line ready processing.	"010" = 2^2 th line ready processing.	"011" = 2^3 th line ready processing.	"100" = 2^4 th line ready processing.	"101" = 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//(11,RW,0x00) //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//(14:12,RW,0x00) //"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG	"011" = L scan for FPR_L (normal V-scan)	"100" = R scan for FPR_R (normal V-scan)	"101" = L scan for FPR_L (reverse V-scan)	"110" = R scan for FPR_R (reverse V-scan)
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//(18:16,RW,0x00) //"000" := all pixel ready processing.	"001" = 2^1 th pixel ready processing.	"010" = 2^2 th pixel ready processing.	"011" = 2^3 th pixel ready processing.	"100" = 2^4 th pixel ready processing.	"101" = 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//(19,RW,0x00) //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x02) //"11" := 4CH	"10" = 2CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	"0010" = video R2(T3C).	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 cdc_lsb_omode                    :4;	//(31:28,RW,0x00) //"0000" := even/odd lsb 2bits native.	"0001" = even/odd lsb 2bits "00".	"0010" = even/odd lsb 2bits "11"	'0011" = even lsb 2bits "00", odd lsb 2bits native.	"0100" = even lsb 2bits native, odd lsb 2bits "00".	"0101" = even lsb 2bits "11", odd lsb 2bits native.	"0110" = even lsb 2bits native, odd lsb 2bits "11".	"0111" = even/odd lsb 2bits native.
	};
}PE_M23_VCP_DISP_VCP_U1_CDC_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1464 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_U1_CDC_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1468 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_u1_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_u1_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0010" = pic_start_y_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_M23_VCP_DISP_VCP_U1_CDC_Y_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F146C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_U1_CDC_Y_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1470 RW 0x0820_0000
	UINT32 cdc_voffset                      :5;	//(4:0,RW,0x0) //CDC_VMODE start line position can be set by 0~31 lne interval offset.
	UINT32 cdc_rdy_ctrl                     :1;	//(5,RW,0x00) //
	UINT32 cdc_auto_v_half                  :1;	//(6,RW,0x00) //0' := disable auto v half mode	'1' = enable auto v half mode
	UINT32 cdc_black_mask                   :1;	//(7,RW,0x00) //0' := disable black center masking for 2Dto3D 2DTB mode	'1' = enable black center masking for 2Dto3D 2DTB mode
	UINT32 cdc_vmode                        :3;	//(10:8,RW,0x00) //"000" := all line ready processing.	"001" = 2^1 th line ready processing.	"010" = 2^2 th line ready processing.	"011" = 2^3 th line ready processing.	"100" = 2^4 th line ready processing.	"101" = 2^5 th line ready processing.
	UINT32 cdc_vmode_cnt_sel                :1;	//(11,RW,0x00) //0' := video line count	'1' = window line count
	UINT32 cdc_scan_type                    :3;	//(14:12,RW,0x00) //"000" := just full scan	"001" = even line active for PG	"010" = odd line active for PG	"011" = L scan for FPR_L (normal V-scan)	"100" = R scan for FPR_R (normal V-scan)	"101" = L scan for FPR_L (reverse V-scan)	"110" = R scan for FPR_R (reverse V-scan)
	UINT32 resvd0                           :1;
	UINT32 cdc_hmode                        :3;	//(18:16,RW,0x00) //"000" := all pixel ready processing.	"001" = 2^1 th pixel ready processing.	"010" = 2^2 th pixel ready processing.	"011" = 2^3 th pixel ready processing.	"100" = 2^4 th pixel ready processing.	"101" = 2^5 th pixel ready processing.
	UINT32 cdc_hmode_cnt_sel                :1;	//(19,RW,0x00) //0' := video pixel count	'1' = window pixel count
	UINT32 cdc_ch                           :2;	//(21:20,RW,0x02) //"11" := 4CH	"10" = 2CH
	UINT32 cdc_de_mode                      :1;	//(22,RW,0x00) //0' := window DE for MV
	UINT32 resvd1                           :1;
	UINT32 cdc_format                       :4;	//(27:24,RW,0x08) //"0000" := video full.	"0001" = video window.	'0011" = video PIP.	"0101" = video mute.	"1000" = video CDC off.
	UINT32 cdc_lsb_omode                    :4;	//(31:28,RW,0x00) //"0000" := even/odd lsb 2bits native.	"0001" = even/odd lsb 2bits "00".	"0010" = even/odd lsb 2bits "11"	'0011" = even lsb 2bits "00", odd lsb 2bits native.	"0100" = even lsb 2bits native, odd lsb 2bits "00".	"0101" = even lsb 2bits "11", odd lsb 2bits native.	"0110" = even lsb 2bits native, odd lsb 2bits "11".	"0111" = even/odd lsb 2bits native.
	};
}PE_M23_VCP_DISP_VCP_U1_CDC_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1474 RW 0x0010_8080
	UINT32 nactive_color_cr                 :8;	//(7:0,RW,0x80) //
	UINT32 nactive_color_cb                 :8;	//(15:8,RW,0x80) //
	UINT32 nactive_color_y                  :8;	//(23:16,RW,0x10) //
	UINT32 nactive_window_end_ctrl          :3;	//(26:24,RW,0x00) //"000" := non-masking	"001" = even end non_active.	"010" = odd end non_active.	"011" = even/odd end non_active.
	UINT32 resvd                            :1;
	UINT32 nactive_window_start_ctrl        :3;	//(30:28,RW,0x00) //"000" := non-masking	"101" = even start non_active.	"110" = odd start non_active.	"111" = even/odd start non_active.
	UINT32 nactive_color_enable             :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_U1_CDC_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1478 RW 0x0000_0000
	UINT32 set_pic_init_c_mux_u1_cdc        :4;	//(3:0,RW,0x00) //"0000" := none	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_u1_cdc       :4;	//(7:4,RW,0x00) //"0000" := none	"0010" = pic_start_c_u1_disp
	UINT32 sel_de_type                      :2;	//(9:8,RW,0x0) //for dubug
	UINT32 sel_de_type_manual               :1;	//(10,RW,0x0) //for debug
	UINT32 resvd0                           :5;
	UINT32 cdc_xpos_end                     :14;	//(29:16,RW,0x0) //for debug
	UINT32 resvd1                           :1;
	UINT32 en_sel_cdc_xpos_end              :1;	//(31,RW,0x0) //for debug
	};
}PE_M23_VCP_DISP_VCP_U1_CDC_C_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F147C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_U1_CDC_C_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1480 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y_aux              :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x_aux              :13;	//(28:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_U0_WIN_O_POS_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1484 RW 0x0F00_0870
	UINT32 cdc_win_o_size_y_aux             :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x_aux             :13;	//(28:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :2;
	UINT32 cdc_win_aux_auto                 :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_U0_WIN_O_SIZE_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1488 RW 0x0000_0000
	UINT32 cdc_win_o_pos_y_aux              :14;	//(13:0,RW,0x0) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_pos_x_aux              :13;	//(28:16,RW,0x0) //min:0, max:3840
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_U1_WIN_O_POS_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F148C RW 0x0F00_0870
	UINT32 cdc_win_o_size_y_aux             :14;	//(13:0,RW,0x870) //min:0, max:2160
	UINT32 resvd0                           :2;
	UINT32 cdc_win_o_size_x_aux             :13;	//(28:16,RW,0xF00) //min:0, max:3840
	UINT32 resvd1                           :2;
	UINT32 cdc_win_aux_auto                 :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_U1_WIN_O_SIZE_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F14E0 RW 0x0008_000A
	UINT32 vsync                            :16;	//(15:0,RW,0xA) //10
	UINT32 vfp                              :16;	//(31:16,RW,0x8) //8
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F14E4 RW 0x0048_0870
	UINT32 va                               :16;	//(15:0,RW,0x870) //2160
	UINT32 vbp                              :16;	//(31:16,RW,0x48) //72
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F14E8 RW 0x0058_002C
	UINT32 hsync                            :16;	//(15:0,RW,0x2C) //88/2=44 for dual channel(E,O)
	UINT32 hfp                              :16;	//(31:16,RW,0x58) //176/2=88 for dual channel(E,O)
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F14EC RW 0x0094_0780
	UINT32 ha                               :16;	//(15:0,RW,0x780) //3840/2=1920 for dual channel(E,O)
	UINT32 hbp                              :16;	//(31:16,RW,0x94) //296/2=148 for dual channel(E,O)
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F14F0 RW 0x0000_0000
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
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F14F4 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F14F8 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F14FC RW 0x0000_0000
	UINT32 auto_ha_delay                    :15;	//(14:0,RW,0x0) //
	UINT32 auto_general_en                  :1;	//(15,RW,0x0) //general delay block enable
	UINT32 auto_va_delay                    :15;	//(30:16,RW,0x0) //
	UINT32 auto_seamless                    :1;	//(31,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1500 RW 0x0000_0000
	UINT32 auto_hs_delay                    :15;	//(14:0,RW,0x0) //
	UINT32 auto_general_en                  :1;	//(15,RW,0x0) //general delay block enable
	UINT32 auto_vs_delay                    :15;	//(30:16,RW,0x0) //
	UINT32 auto_seamless                    :1;	//(31,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1504 RW 0x0000_0000
	UINT32 resvd                            :31;
	UINT32 sync_out_disable                 :1;	//(31,RW,0x0000_0000) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1510 RW 0x0008_000A
	UINT32 vsync                            :16;	//(15:0,RW,0xA) //10
	UINT32 vfp                              :16;	//(31:16,RW,0x8) //8
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1514 RW 0x0048_0870
	UINT32 va                               :16;	//(15:0,RW,0x870) //2160
	UINT32 vbp                              :16;	//(31:16,RW,0x48) //72
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1518 RW 0x0058_002C
	UINT32 hsync                            :16;	//(15:0,RW,0x2C) //88/2=44 for dual channel(E,O)
	UINT32 hfp                              :16;	//(31:16,RW,0x58) //176/2=88 for dual channel(E,O)
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F151C RW 0x0094_0780
	UINT32 ha                               :16;	//(15:0,RW,0x780) //3840/2=1920 for dual channel(E,O)
	UINT32 hbp                              :16;	//(31:16,RW,0x94) //296/2=148 for dual channel(E,O)
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1520 RW 0x0000_0000
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
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1524 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1528 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F152C RW 0x0000_0000
	UINT32 auto_ha_delay                    :15;	//(14:0,RW,0x0) //
	UINT32 auto_general_en                  :1;	//(15,RW,0x0) //general delay block enable
	UINT32 auto_va_delay                    :15;	//(30:16,RW,0x0) //
	UINT32 auto_seamless                    :1;	//(31,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1530 RW 0x0000_0000
	UINT32 auto_hs_delay                    :15;	//(14:0,RW,0x0) //
	UINT32 auto_general_en                  :1;	//(15,RW,0x0) //general delay block enable
	UINT32 auto_vs_delay                    :15;	//(30:16,RW,0x0) //
	UINT32 auto_seamless                    :1;	//(31,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1534 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1538 RO 0x0000_0000
	UINT32 vcp_u0y_pic_init_hpos            :16;	//(15:0,RO,0x0) //
	UINT32 vcp_u0y_pic_init_vpos            :16;	//(31:16,RO,0x0) //
	};
}PE_M23_VCP_DISP_MON_VCP_U0Y_PIC_INIT_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F153C RO 0x0000_0000
	UINT32 vcp_u0y_pic_start_hpos           :16;	//(15:0,RO,0x0) //
	UINT32 vcp_u0y_pic_start_vpos           :16;	//(31:16,RO,0x0) //
	};
}PE_M23_VCP_DISP_MON_VCP_U0Y_PIC_START_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1540 RO 0x0000_0000
	UINT32 vcp_u0c_pic_init_hpos            :16;	//(15:0,RO,0x0) //
	UINT32 vcp_u0c_pic_init_vpos            :16;	//(31:16,RO,0x0) //
	};
}PE_M23_VCP_DISP_MON_VCP_U0C_PIC_INIT_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1544 RO 0x0000_0000
	UINT32 vcp_u0c_pic_start_hpos           :16;	//(15:0,RO,0x0) //
	UINT32 vcp_u0c_pic_start_vpos           :16;	//(31:16,RO,0x0) //
	};
}PE_M23_VCP_DISP_MON_VCP_U0C_PIC_START_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1548 RO 0x0000_0000
	UINT32 vcp_u1y_pic_init_hpos            :16;	//(15:0,RO,0x0) //
	UINT32 vcp_u1y_pic_init_vpos            :16;	//(31:16,RO,0x0) //
	};
}PE_M23_VCP_DISP_MON_VCP_U1Y_PIC_INIT_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F154C RO 0x0000_0000
	UINT32 vcp_u1y_pic_start_hpos           :16;	//(15:0,RO,0x0) //
	UINT32 vcp_u1y_pic_start_vpos           :16;	//(31:16,RO,0x0) //
	};
}PE_M23_VCP_DISP_MON_VCP_U1Y_PIC_START_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1550 RO 0x0000_0000
	UINT32 vcp_u1c_pic_init_hpos            :16;	//(15:0,RO,0x0) //
	UINT32 vcp_u1c_pic_init_vpos            :16;	//(31:16,RO,0x0) //
	};
}PE_M23_VCP_DISP_MON_VCP_U1C_PIC_INIT_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1554 RO 0x0000_0000
	UINT32 vcp_u1c_pic_start_hpos           :16;	//(15:0,RO,0x0) //
	UINT32 vcp_u1c_pic_start_vpos           :16;	//(31:16,RO,0x0) //
	};
}PE_M23_VCP_DISP_MON_VCP_U1C_PIC_START_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15B8 RW 0x0780_0870
	UINT32 pg1ch_win_o_size_y               :14;	//(13:0,RW,0x870) //0x870(2160) for UD, 0x438(1080) for FHD.
	UINT32 resvd0                           :2;
	UINT32 pg1ch_win_o_size_x               :13;	//(28:16,RW,0x780) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_DISP_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15BC RW 0x0000_0000
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
}PE_M23_VCP_DISP_VCP_WCP_M_PG_PAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15C8 RW 0x0000_0000
	UINT32 rd_pel_pos_y                     :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 rd_pel_pos_x                     :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 rd_pel_pat_en                    :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15CC RW 0x0000_0000
	UINT32 rd_pel_pos_y                     :14;	//(13:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 rd_pel_pos_x                     :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 rd_pel_pat_en                    :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15D0 RW 0x0000_0000
	UINT32 even_line_cr                     :8;	//(7:0,RW,0x0) //
	UINT32 even_line_cb                     :8;	//(15:8,RW,0x0) //
	UINT32 even_line_y                      :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 even_line_pat_en                 :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_M_LINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15D4 RW 0x0000_0000
	UINT32 odd_line_cr                      :8;	//(7:0,RW,0x0) //
	UINT32 odd_line_cb                      :8;	//(15:8,RW,0x0) //
	UINT32 odd_line_y                       :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 odd_line_pat_en                  :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_M_LINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15E0 RW 0x0000_0000
	UINT32 rec0_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec0_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec0_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15E4 RW 0x0000_0000
	UINT32 rec0_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec0_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec0_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15E8 RW 0x0000_0000
	UINT32 rec1_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec1_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec1_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC1_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15EC RW 0x0000_0000
	UINT32 rec1_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec1_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec1_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC1_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15F0 RW 0x0000_0000
	UINT32 repeat_odd_1st_pix_y             :1;	//(0,RW,0x00) //Main Window 에만 해당하며 오른쪽으로 밀림 offset이 홀수 일 경우 odd pixel을 pre-even pixel로 repeat 함
	UINT32 repeat_even_1st_pix_y            :1;	//(1,RW,0x00) //Main Window 에만 해당하며 오른쪽으로 밀림 offset이 짝수 일 경우 even pixel을 pre-even pixel로 repeat 함
	UINT32 repeat_odd_end_pix_y             :1;	//(2,RW,0x00) //Main Window 에만 해당하며 왼쪽으로 당겨짐 offset이 홀수 일 경우 even pixel을 post-odd pixel로 repeat 함
	UINT32 repeat_even_end_pix_y            :1;	//(3,RW,0x00) //Main Window 에만 해당하며 왼쪽으로 당겨짐 offset이 짝수 일 경우 odd pixel을 post-odd pixel로 repeat 함
	UINT32 repeat_odd_1st_pix_c             :1;	//(4,RW,0x00) //Main Window 에만 해당하며 오른쪽으로 밀림 offset이 홀수 일 경우 odd pixel을 pre-even pixel로 repeat 함
	UINT32 repeat_even_1st_pix_c            :1;	//(5,RW,0x00) //Main Window 에만 해당하며 오른쪽으로 밀림 offset이 짝수 일 경우 even pixel을 pre-even pixel로 repeat 함
	UINT32 repeat_odd_end_pix_c             :1;	//(6,RW,0x00) //Main Window 에만 해당하며 왼쪽으로 당겨짐 offset이 홀수 일 경우 even pixel을 post-odd pixel로 repeat 함
	UINT32 repeat_even_end_pix_c            :1;	//(7,RW,0x00) //Main Window 에만 해당하며 왼쪽으로 당겨짐 offset이 짝수 일 경우 odd pixel을 post-odd pixel로 repeat 함
	UINT32 last_pixel_padding               :1;	//(8,RW,0x00) //1 last pixel padding
	UINT32 resvd0                           :15;
	UINT32 compare_lr_diff_sel              :2;	//(25:24,RW,0x00) //
	UINT32 compare_lr_sync_sel              :1;	//(26,RW,0x00) //
	UINT32 compare_lr_mark_org_nac          :1;	//(27,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 compare_lr_en                    :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15F4 RW 0x0000_0000
	UINT32 compare_lr_th_c                  :8;	//(7:0,RW,0x0) //
	UINT32 compare_lr_th_y                  :8;	//(15:8,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15F8 RW 0x1088_1088
	UINT32 clr_nac_cr                       :4;	//(3:0,RW,0x08) //we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 clr_nac_cb                       :4;	//(7:4,RW,0x08) //we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 clr_nac_y                        :8;	//(15:8,RW,0x10) //we can get 0x40(64) by setting lsb 2bits to "00" internally.
	UINT32 clr_bdr_cr                       :4;	//(19:16,RW,0x08) //we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 clr_bdr_cb                       :4;	//(23:20,RW,0x08) //we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 clr_bdr_y                        :8;	//(31:24,RW,0x10) //we can get 0x40(64) by setting lsb 2bits to "00" internally.
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F15FC RW 0x1088_1088
	UINT32 w1_clr_dark_cr                   :4;	//(3:0,RW,0x08) //we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 w1_clr_dark_cb                   :4;	//(7:4,RW,0x08) //we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 w1_clr_dark_y                    :8;	//(15:8,RW,0x10) //we can get 0x40(64) by setting lsb 2bits to "00" internally.
	UINT32 w0_clr_dark_cr                   :4;	//(19:16,RW,0x08) //we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 w0_clr_dark_cb                   :4;	//(23:20,RW,0x08) //we can get 0x200(512) by setting lsb 6bits to "00_0000" internally.
	UINT32 w0_clr_dark_y                    :8;	//(31:24,RW,0x10) //we can get 0x40(64) by setting lsb 2bits to "00" internally.
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1604 RW 0x0000_0000
	UINT32 set_w0_imux_ctrl                 :3;	//(2:0,RW,0x00) //"000" := vid0 (U0)	"001" = vid1 (U1)
	UINT32 set_w0_dark_en                   :1;	//(3,RW,0x00) //
	UINT32 set_w1_imux_ctrl                 :3;	//(6:4,RW,0x00) //"000" := vid0 (U0)	"001" = vid1 (U1)
	UINT32 set_w1_dark_en                   :1;	//(7,RW,0x00) //
	UINT32 cg_disable                       :1;	//(8,RW,0x00) //0 : Clock gating, 1 : disable CG  (w0,w1,a0,a1)
	UINT32 resvd0                           :7;
	UINT32 set_lparity_w0_imux_en           :1;	//(16,RW,0x00) //
	UINT32 set_lparity_w0_imux              :1;	//(17,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 set_lparity_w1_imux_en           :1;	//(20,RW,0x00) //
	UINT32 set_lparity_w1_imux              :1;	//(21,RW,0x00) //
	UINT32 resvd2                           :2;
	UINT32 set_lparity_sync_c               :3;	//(26:24,RW,0x00) //
	UINT32 resvd3                           :1;
	UINT32 set_lparity_sync_y               :3;	//(30:28,RW,0x00) //
	UINT32 resvd4                           :1;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1608 RW 0x00AA_00BB
	UINT32 set_a0_c_imux_ctrl               :3;	//(2:0,RW,0x03) //"000" := N/A	"001" = N/A
	UINT32 set_a0_c_constant_en             :1;	//(3,RW,0x01) //set by 0x610 alpha.	'0' := constant alpha disable.	'1'= constant alpha enable.
	UINT32 set_a1_c_imux_ctrl               :3;	//(6:4,RW,0x03) //"000" := N/A	"001" = N/A	"100" = region model alpha
	UINT32 set_a1_c_constant_en             :1;	//(7,RW,0x01) //set by 0x610 alpha.	'0' := constant alpha disable.	'1'= constant alpha enable.
	UINT32 resvd0                           :8;
	UINT32 set_a0_y_imux_ctrl               :3;	//(18:16,RW,0x02) //"000" := N/A	"001" = N/A
	UINT32 set_a0_y_constant_en             :1;	//(19,RW,0x01) //set by 0x610 alpha.	'0' := constant alpha disable.	'1'= constant alpha enable.
	UINT32 set_a1_y_imux_ctrl               :3;	//(22:20,RW,0x02) //"000" := N/A	"001" = N/A	"100" = region model alpha
	UINT32 set_a1_y_constant_en             :1;	//(23,RW,0x01) //set by 0x610 alpha.	'0' := constant alpha disable.	'1'= constant alpha enable.
	UINT32 resvd1                           :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F160C RW 0x0000_0000
	UINT32 set_w0_abr_en                    :2;	//(1:0,RW,0x00) //"00" := blend out	"01" = nactive color (DN)	"10" = window0 (UP)	"11" = alpha output
	UINT32 set_w1_abr_en                    :2;	//(3:2,RW,0x00) //"00" := blend out	"01" = nactive color (DN)	"10" = window0 (UP)	"11" = alpha output
	UINT32 resvd0                           :4;
	UINT32 set_w0_awb_cr                    :1;	//(8,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 set_w0_awb_cb                    :1;	//(9,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 set_w0_awb_y                     :1;	//(10,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 resvd1                           :1;
	UINT32 set_w1_awb_cr                    :1;	//(12,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 set_w1_awb_cb                    :1;	//(13,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 set_w1_awb_y                     :1;	//(14,RW,0x00) //0' := dnMiunsUp	'1' = dn
	UINT32 resvd2                           :8;
	UINT32 w1_clr_alpha_nac_en              :1;	//(23,RW,0x00) //
	UINT32 w1_clr_alpha_nac                 :8;	//(31:24,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1610 RW 0x0000_0000
	UINT32 w0_clr_alpha                     :8;	//(7:0,RW,0x0) //0x00 : DN (non active clolor)	0xFF : UP (Window 0)
	UINT32 w1_clr_alpha                     :8;	//(15:8,RW,0x0) //0x00 : DN (w0_clr_alpha window)	0xFF : UP (Window 1)
	UINT32 reg4_alpha                       :8;	//(23:16,RW,0x0) //0x00 : DN (background)	0xFF : UP (bypass)
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1614 RW 0x0000_0000
	UINT32 set_ha_o_mux_ctrl                :4;	//(3:0,RW,0x00) //"0000" := display hactive	"0001" = w0 hactive	"0010" = w1 hactive
	UINT32 set_va_o_mux_ctrl                :4;	//(7:4,RW,0x00) //"0000" := display vactive	"0001" = w0 vactive	"0010" = w1 vactive
	UINT32 set_de_o_mux_ctrl                :4;	//(11:8,RW,0x00) //DE processing for SOSD ONLY	"0000" := display de	"0001" = w0_va&w0_ha	"0010" = w1_va&w1_ha	"0101" = (w0_va&w0_ha) | (w1_va&w1_ha)	"1000" = ~(w0_va&w0_ha)	"1001" = ~(w1_va&w1_ha)	"1100" = ~((w0_va&w0_ha) | (w1_va&w1_ha))
	UINT32 resvd                            :20;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1618 RW 0x0000_0000
	UINT32 set_pic_init_y_mux_m_wcp         :4;	//(3:0,RW,0x00) //"0000" := none	"0001" = pic_init_y_u0_disp	"0010" = pic_init_y_u1_disp
	UINT32 set_pic_start_y_mux_m_wcp        :4;	//(7:4,RW,0x00) //"0000" := none	"0001" = pic_start_y_u0_disp	"0010" = pic_start_y_u1_disp
	UINT32 set_pic_init_c_mux_m_wcp         :4;	//(11:8,RW,0x00) //"0000" := none	"0001" = pic_init_c_u0_disp	"0010" = pic_init_c_u1_disp
	UINT32 set_pic_start_c_mux_m_wcp        :4;	//(15:12,RW,0x00) //"0000" := none	"0001" = pic_start_c_u0_disp	"0010" = pic_start_c_u1_disp
	UINT32 resvd                            :16;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1650 RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1654 RO 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1658 RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F165C RO 0x0000_0000
	UINT32 msb8_rd_pel_cr                   :8;	//(7:0,RO,0x0) //
	UINT32 msb8_rd_pel_cb                   :8;	//(15:8,RO,0x0) //
	UINT32 msb8_rd_pel_y                    :8;	//(23:16,RO,0x0) //
	UINT32 lsb2_rd_pel_cr                   :2;	//(25:24,RO,0x00) //
	UINT32 lsb2_rd_pel_cb                   :2;	//(27:26,RO,0x00) //
	UINT32 lsb2_rd_pel_y                    :2;	//(29:28,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1660 RW 0x0000_0000
	UINT32 win_pos_y0_auto                  :14;	//(13:0,RW,0x0) //Y start position of window.
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0_auto                  :13;	//(28:16,RW,0x0) //X start position of window.
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V0_PARAM_POS_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1664 RW 0x8000_0000
	UINT32 win_size_y_auto                  :14;	//(13:0,RW,0x0) //Y-size of window.
	UINT32 resvd0                           :2;
	UINT32 win_size_x_auto                  :13;	//(28:16,RW,0x0) //X-size of window.
	UINT32 resvd1                           :1;
	UINT32 win_enable_4ch_auto              :1;	//(30,RW,0x00) //1' = 4ch pos/size control	'0' := 2ch pos/size control
	UINT32 win_enable_auto                  :1;	//(31,RW,0x01) //1' := auto pos/size control	'0' = manual pos/size control
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V0_PARAM_SIZE_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1668 RW 0x0000_0000
	UINT32 win_pos_y0_auto                  :14;	//(13:0,RW,0x0) //Y start position of window.
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0_auto                  :13;	//(28:16,RW,0x0) //X start position of window.
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V1_PARAM_POS_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F166C RW 0x8000_0000
	UINT32 win_size_y_auto                  :14;	//(13:0,RW,0x0) //Y-size of window.
	UINT32 resvd0                           :2;
	UINT32 win_size_x_auto                  :13;	//(28:16,RW,0x0) //X-size of window.
	UINT32 resvd1                           :1;
	UINT32 win_enable_4ch_auto              :1;	//(30,RW,0x00) //1' = 4ch pos/size control	'0' := 2ch pos/size control
	UINT32 win_enable_auto                  :1;	//(31,RW,0x01) //1' := auto pos/size control	'0' = manual pos/size control
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V1_PARAM_SIZE_M_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1680 RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1684 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1688 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//(19:16,RW,0x00) //
	UINT32 win_border_width_left            :4;	//(23:20,RW,0x00) //
	UINT32 win_border_width_down            :4;	//(27:24,RW,0x00) //
	UINT32 win_border_width_up              :4;	//(31:28,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1690 RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1694 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1698 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//(19:16,RW,0x00) //
	UINT32 win_border_width_left            :4;	//(23:20,RW,0x00) //
	UINT32 win_border_width_down            :4;	//(27:24,RW,0x00) //
	UINT32 win_border_width_up              :4;	//(31:28,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F16C0 RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F16C4 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F16C8 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//(19:16,RW,0x00) //
	UINT32 win_border_width_left            :4;	//(23:20,RW,0x00) //
	UINT32 win_border_width_down            :4;	//(27:24,RW,0x00) //
	UINT32 win_border_width_up              :4;	//(31:28,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F16D0 RW 0x0000_0000
	UINT32 win_pos_y0                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x0                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F16D4 RW 0x0000_0000
	UINT32 win_pos_y1                       :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 win_pos_x1                       :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F16D8 RW 0x0000_0020
	UINT32 sync_ha_sub_sel                  :1;	//(0,RW,0x00) //
	UINT32 sync_ha_sub_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 num_ch                           :2;	//(5:4,RW,0x02) //"11" = 4-ch	"10" := 2-ch
	UINT32 resvd1                           :10;
	UINT32 win_border_width_right           :4;	//(19:16,RW,0x00) //
	UINT32 win_border_width_left            :4;	//(23:20,RW,0x00) //
	UINT32 win_border_width_down            :4;	//(27:24,RW,0x00) //
	UINT32 win_border_width_up              :4;	//(31:28,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1780 RW 0x0000_0000
	UINT32 rec5_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec5_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec5_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC5_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1784 RW 0x0000_0000
	UINT32 rec5_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec5_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec5_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC5_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1788 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC5_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F178C RW 0x0000_0000
	UINT32 rec6_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec6_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec6_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC6_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1790 RW 0x0000_0000
	UINT32 rec6_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec6_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec6_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC6_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1794 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC6_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1798 RW 0x0000_0000
	UINT32 rec7_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec7_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec7_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC7_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F179C RW 0x0000_0000
	UINT32 rec7_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec7_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec7_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC7_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17A0 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC7_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17A4 RW 0x0000_0000
	UINT32 rec8_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec8_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec8_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC8_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17A8 RW 0x0000_0000
	UINT32 rec8_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec8_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec8_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC8_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17AC RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC8_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17B0 RW 0x0000_0000
	UINT32 rec9_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec9_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec9_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC9_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17B4 RW 0x0000_0000
	UINT32 rec9_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec9_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec9_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC9_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17B8 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC9_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17F0 RW 0x0000_0000
	UINT32 reg0_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg0_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg0_en                          :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_REG0_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17F4 RW 0x0000_0000
	UINT32 reg0_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg0_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_WCP_REG0_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17F8 RW 0x0000_0000
	UINT32 reg1_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg1_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg1_en                          :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_REG1_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F17FC RW 0x0000_0000
	UINT32 reg1_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg1_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_WCP_REG1_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1800 RW 0x0000_0000
	UINT32 reg2_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg2_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg2_en                          :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_REG2_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1804 RW 0x0000_0000
	UINT32 reg2_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg2_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_WCP_REG2_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1808 RW 0x0000_0000
	UINT32 reg3_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg3_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg3_en                          :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_REG3_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F180C RW 0x0000_0000
	UINT32 reg3_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg3_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_WCP_REG3_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1810 RW 0x0000_0000
	UINT32 reg4_e_pos_x                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg4_s_pos_x                     :15;	//(30:16,RW,0x0) //
	UINT32 reg4_en                          :1;	//(31,RW,0x00) //
	};
}PE_M23_VCP_DISP_VCP_WCP_REG4_V0_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1814 RW 0x0000_0000
	UINT32 reg4_e_pos_y                     :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg4_s_pos_y                     :15;	//(30:16,RW,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_WCP_REG4_V0_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1830 RW 0x0000_0000
	UINT32 reg0_alpha                       :8;	//(7:0,RW,0x0) //
	UINT32 reg1_alpha                       :8;	//(15:8,RW,0x0) //
	UINT32 reg2_alpha                       :8;	//(23:16,RW,0x0) //
	UINT32 reg3_alpha                       :8;	//(31:24,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_WCP_PE_M23_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1834 RW 0x0000_0000
	UINT32 rec2_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec2_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec2_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC2_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1838 RW 0x0000_0000
	UINT32 rec2_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec2_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec2_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC2_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F183C RW 0x0000_0000
	UINT32 rec3_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec3_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec3_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC3_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1840 RW 0x0000_0000
	UINT32 rec3_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec3_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec3_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC3_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1844 RW 0x0000_0000
	UINT32 rec4_e_pos_x                     :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 rec4_s_pos_x                     :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 rec4_en                          :1;	//(31,RW,0x00) //line draw
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC4_POS_X_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1848 RW 0x0000_0000
	UINT32 rec4_e_pos_y                     :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 rec4_s_pos_y                     :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 rec4_fill_en                     :1;	//(31,RW,0x00) //box fill
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC4_POS_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F184C RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC0_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1850 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC1_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1854 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC2_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1858 RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC3_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F185C RW 0x0000_0000
	UINT32 clr_cr                           :8;	//(7:0,RW,0x0) //
	UINT32 clr_cb                           :8;	//(15:8,RW,0x0) //
	UINT32 clr_y                            :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_M23_VCP_DISP_VCP_WCP_M_REC4_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1860 RW 0x0200_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_M23_VCP_DISP_VCP_VSP_U0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1864 RW 0x0200_8000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_M23_VCP_DISP_VCP_VSP_U0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1868 RW 0x0200_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :7;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_M23_VCP_DISP_VCP_VSP_U1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F186C RW 0x0200_8000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_M23_VCP_DISP_VCP_VSP_U1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1870 RW 0x0000_00C0
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
}PE_M23_VCP_DISP_VCP_CRC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1874 RW 0xFFFF_FFFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_CRC_DATA_MASK0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1878 RW 0xFFFF_FFFF
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_CRC_DATA_MASK1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1884 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_CRC_OUT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1888 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_VCP_DISP_VCP_CRC_OUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F18A0 RW 0x0000_0000
	UINT32 h_cnt                            :16;	//(15:0,RW,0x0) //
	UINT32 v_cnt                            :16;	//(31:16,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F18A4 RW 0x0000_0000
	UINT32 h_cnt                            :16;	//(15:0,RW,0x0) //
	UINT32 v_cnt                            :16;	//(31:16,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F18A8 RW 0x0000_0000
	UINT32 h_cnt                            :16;	//(15:0,RW,0x0) //
	UINT32 v_cnt                            :16;	//(31:16,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_SVY_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F18AC RW 0x0000_0000
	UINT32 h_cnt                            :16;	//(15:0,RW,0x0) //
	UINT32 v_cnt                            :16;	//(31:16,RW,0x0) //
	};
}PE_M23_VCP_DISP_VCP_SG_SVC_CTRL_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1900 RW 0x01CF_11CF
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
}PE_M23_VCP_DISP_VCP_DISP_INTR_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1904 RW 0x0000_0000
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
}PE_M23_VCP_DISP_VCP_DISP_INTR_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1908 RO 0x0000_0000
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
}PE_M23_VCP_DISP_VCP_DISP_INTR_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F190C RW 0x0000_0000
	UINT32 vcp_mv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_DISP_INTR0_POS_MV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1910 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_DISP_INTR1_POS_MV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1914 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_DISP_INTR0_POS_MV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1918 RW 0x0000_0000
	UINT32 vcp_mv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_mv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_DISP_INTR1_POS_MV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F191C RW 0x0000_0000
	UINT32 vcp_sv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_DISP_INTR0_POS_SV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1920 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_DISP_INTR1_POS_SV_Y_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1924 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr0_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr0_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_DISP_INTR0_POS_SV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1928 RW 0x0000_0000
	UINT32 vcp_sv_disp_intr1_pos_x          :14;	//(13:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 vcp_sv_disp_intr1_pos_y          :14;	//(29:16,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_M23_VCP_DISP_VCP_DISP_INTR1_POS_SV_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F192C RW 0x0000_0000
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
}PE_M23_VCP_DISP_VCP_DISP_INTR_SRC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1930 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 vcp_422_mean_filter_en           :1;	//(4,RW,0x00) //1 : enable (odd pixel is changing to mean of even pixels)	0 : bypass
	UINT32 vcp_maunal_size                  :1;	//(5,RW,0x00) //1 : enable vcp_422_mean_filter_last_pixel	0 : vcp_sg_bdr_v0_param_size
	UINT32 resvd1                           :2;
	UINT32 vcp_422_mean_filter_last_pixel   :13;	//(20:8,RW,0x00) //size of mean filter	real size 3840 => 1920 setting size(dual pixel)
	UINT32 resvd2                           :11;
	};
}PE_M23_VCP_DISP_VCP_U0_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1934 RW 0x129F_7C98
	UINT32 vcp_csc_coefficient1             :15;	//(14:0,RW,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient0             :15;	//(30:16,RW,0x129F) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_U1_CSC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1938 RW 0x7775_129F
	UINT32 vcp_csc_coefficient3             :15;	//(14:0,RW,0x129F) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient2             :15;	//(30:16,RW,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_U1_CSC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F193C RW 0x21D7_0000
	UINT32 vcp_csc_coefficient5             :15;	//(14:0,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient4             :15;	//(30:16,RW,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_U1_CSC_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1940 RW 0x129F_0000
	UINT32 vcp_csc_coefficient7             :15;	//(14:0,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 vcp_csc_coefficient6             :15;	//(30:16,RW,0x129F) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_U1_CSC_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1944 RW 0x1CB0_07C0
	UINT32 vcp_csc_offset0                  :11;	//(10:0,RW,0x7C0) //Pre add offset a	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_coefficient8             :15;	//(30:16,RW,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_VCP_DISP_VCP_U1_CSC_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1948 RW 0x0600_0600
	UINT32 vcp_csc_offset2                  :11;	//(10:0,RW,0x600) //Pre add offset c	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_offset1                  :11;	//(26:16,RW,0x600) //Pre add offset b	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_M23_VCP_DISP_VCP_U1_CSC_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F194C RW 0x0000_0000
	UINT32 vcp_csc_offset4                  :11;	//(10:0,RW,0x00) //Post add offset y	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 vcp_csc_offset3                  :11;	//(26:16,RW,0x00) //Post add offset x	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_M23_VCP_DISP_VCP_U1_CSC_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1950 RW 0x0000_0002
	UINT32 vcp_csc_coeff_load               :1;	//(0,WO,0x00) //this bit is auto cleared
	UINT32 vcp_csc_en                       :1;	//(1,RW,0x1) //csc enable
	UINT32 vcp_csc_pcg_off                  :1;	//(2,RW,0x00) //power clock gating off
	UINT32 resvd0                           :1;
	UINT32 vcp_422_mean_filter_en           :1;	//(4,RW,0x00) //1 : enable (odd pixel is changing to mean of even pixels)	0 : bypass
	UINT32 vcp_maunal_size                  :1;	//(5,RW,0x00) //1 : enable vcp_422_mean_filter_last_pixel	0 : vcp_sg_bdr_v1_param_size
	UINT32 resvd1                           :2;
	UINT32 vcp_422_mean_filter_last_pixel   :13;	//(20:8,RW,0x00) //size of mean filter	real size 3840 => 1920 setting size(dual pixel)
	UINT32 vcp_csc_offset5                  :11;	//(31:21,RW,0x00) //Post add offset z	Range -1024~1023
	};
}PE_M23_VCP_DISP_VCP_U1_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4F1954 RW 0x0000_0000
	UINT32 vcp_active_line_cnt_en           :1;	//(0,RW,0x00) //0 : disable	1 : enable
	UINT32 vcp_cnt_ref                      :1;	//(1,RW,0x00) //0 : vsync rising	1 : vsync falling
	UINT32 vcp_active_line_cnt              :15;	//(16:2,RW,0x00) //
	UINT32 resvd                            :15;
	};
}PE_M23_VCP_DISP_VCP_ACTIVE_LINE_CNT_T;

typedef struct {
	PE_M23_VCP_DISP_VCP_DISP_CTRL0_T                        vcp_disp_ctrl0;	//0xCC4F1400
	PE_M23_VCP_DISP_VCP_DISP_CTRL1_T                        vcp_disp_ctrl1;	//0xCC4F1404
	PE_M23_VCP_DISP_VCP_DISP_CTRL2_T                        vcp_disp_ctrl2;	//0xCC4F1408
	PE_M23_VCP_DISP_VCP_DISP_CTRL3_T                        vcp_disp_ctrl3;	//0xCC4F140C
	PE_M23_VCP_DISP_VCP_CDC_MV_SYNC_CTRL_T            vcp_cdc_mv_sync_ctrl;	//0xCC4F1410
	PE_M23_VCP_DISP_VCP_CDC_MV_RST_CTRL_T              vcp_cdc_mv_rst_ctrl;	//0xCC4F1414
	UINT32                                                    reserved0;	//0xCC4F1418
	UINT32                                                    reserved1;	//0xCC4F141C
	PE_M23_VCP_DISP_VCP_U0_WIN_O_POS_T                    vcp_u0_win_o_pos;	//0xCC4F1420
	PE_M23_VCP_DISP_VCP_U0_WIN_O_SIZE_T                  vcp_u0_win_o_size;	//0xCC4F1424
	PE_M23_VCP_DISP_VCP_U0_PG_PAT_CTRL_T                vcp_u0_pg_pat_ctrl;	//0xCC4F1428
	PE_M23_VCP_DISP_VCP_U0_PG_PEAK_SIZE_T              vcp_u0_pg_peak_size;	//0xCC4F142C
	PE_M23_VCP_DISP_VCP_U0_CDC_Y_CTRL0_T                vcp_u0_cdc_y_ctrl0;	//0xCC4F1430
	PE_M23_VCP_DISP_VCP_U0_CDC_Y_CTRL1_T                vcp_u0_cdc_y_ctrl1;	//0xCC4F1434
	PE_M23_VCP_DISP_VCP_U0_CDC_Y_CTRL2_T                vcp_u0_cdc_y_ctrl2;	//0xCC4F1438
	PE_M23_VCP_DISP_VCP_U0_CDC_Y_STATUS_T              vcp_u0_cdc_y_status;	//0xCC4F143C
	PE_M23_VCP_DISP_VCP_U0_CDC_C_CTRL0_T                vcp_u0_cdc_c_ctrl0;	//0xCC4F1440
	PE_M23_VCP_DISP_VCP_U0_CDC_C_CTRL1_T                vcp_u0_cdc_c_ctrl1;	//0xCC4F1444
	PE_M23_VCP_DISP_VCP_U0_CDC_C_CTRL2_T                vcp_u0_cdc_c_ctrl2;	//0xCC4F1448
	PE_M23_VCP_DISP_VCP_U0_CDC_C_STATUS_T              vcp_u0_cdc_c_status;	//0xCC4F144C
	PE_M23_VCP_DISP_VCP_U1_WIN_O_POS_T                    vcp_u1_win_o_pos;	//0xCC4F1450
	PE_M23_VCP_DISP_VCP_U1_WIN_O_SIZE_T                  vcp_u1_win_o_size;	//0xCC4F1454
	PE_M23_VCP_DISP_VCP_U1_PG_PAT_CTRL_T                vcp_u1_pg_pat_ctrl;	//0xCC4F1458
	PE_M23_VCP_DISP_VCP_U1_PG_PEAK_SIZE_T              vcp_u1_pg_peak_size;	//0xCC4F145C
	PE_M23_VCP_DISP_VCP_U1_CDC_Y_CTRL0_T                vcp_u1_cdc_y_ctrl0;	//0xCC4F1460
	PE_M23_VCP_DISP_VCP_U1_CDC_Y_CTRL1_T                vcp_u1_cdc_y_ctrl1;	//0xCC4F1464
	PE_M23_VCP_DISP_VCP_U1_CDC_Y_CTRL2_T                vcp_u1_cdc_y_ctrl2;	//0xCC4F1468
	PE_M23_VCP_DISP_VCP_U1_CDC_Y_STATUS_T              vcp_u1_cdc_y_status;	//0xCC4F146C
	PE_M23_VCP_DISP_VCP_U1_CDC_C_CTRL0_T                vcp_u1_cdc_c_ctrl0;	//0xCC4F1470
	PE_M23_VCP_DISP_VCP_U1_CDC_C_CTRL1_T                vcp_u1_cdc_c_ctrl1;	//0xCC4F1474
	PE_M23_VCP_DISP_VCP_U1_CDC_C_CTRL2_T                vcp_u1_cdc_c_ctrl2;	//0xCC4F1478
	PE_M23_VCP_DISP_VCP_U1_CDC_C_STATUS_T              vcp_u1_cdc_c_status;	//0xCC4F147C
	PE_M23_VCP_DISP_VCP_U0_WIN_O_POS_AUX_T            vcp_u0_win_o_pos_aux;	//0xCC4F1480
	PE_M23_VCP_DISP_VCP_U0_WIN_O_SIZE_AUX_T          vcp_u0_win_o_size_aux;	//0xCC4F1484
	PE_M23_VCP_DISP_VCP_U1_WIN_O_POS_AUX_T            vcp_u1_win_o_pos_aux;	//0xCC4F1488
	PE_M23_VCP_DISP_VCP_U1_WIN_O_SIZE_AUX_T          vcp_u1_win_o_size_aux;	//0xCC4F148C
	UINT32                                                    reserved2;	//0xCC4F1490
	UINT32                                                    reserved3;	//0xCC4F1494
	UINT32                                                    reserved4;	//0xCC4F1498
	UINT32                                                    reserved5;	//0xCC4F149C
	UINT32                                                    reserved6;	//0xCC4F14A0
	UINT32                                                    reserved7;	//0xCC4F14A4
	UINT32                                                    reserved8;	//0xCC4F14A8
	UINT32                                                    reserved9;	//0xCC4F14AC
	UINT32                                                   reserved10;	//0xCC4F14B0
	UINT32                                                   reserved11;	//0xCC4F14B4
	UINT32                                                   reserved12;	//0xCC4F14B8
	UINT32                                                   reserved13;	//0xCC4F14BC
	UINT32                                                   reserved14;	//0xCC4F14C0
	UINT32                                                   reserved15;	//0xCC4F14C4
	UINT32                                                   reserved16;	//0xCC4F14C8
	UINT32                                                   reserved17;	//0xCC4F14CC
	UINT32                                                   reserved18;	//0xCC4F14D0
	UINT32                                                   reserved19;	//0xCC4F14D4
	UINT32                                                   reserved20;	//0xCC4F14D8
	UINT32                                                   reserved21;	//0xCC4F14DC
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_0_T                  vcp_sg_mvy_ctrl_0;	//0xCC4F14E0
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_1_T                  vcp_sg_mvy_ctrl_1;	//0xCC4F14E4
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_2_T                  vcp_sg_mvy_ctrl_2;	//0xCC4F14E8
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_3_T                  vcp_sg_mvy_ctrl_3;	//0xCC4F14EC
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_4_T                  vcp_sg_mvy_ctrl_4;	//0xCC4F14F0
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_5_T                  vcp_sg_mvy_ctrl_5;	//0xCC4F14F4
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_6_T                  vcp_sg_mvy_ctrl_6;	//0xCC4F14F8
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_7_T                  vcp_sg_mvy_ctrl_7;	//0xCC4F14FC
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_8_T                  vcp_sg_mvy_ctrl_8;	//0xCC4F1500
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_9_T                  vcp_sg_mvy_ctrl_9;	//0xCC4F1504
	UINT32                                                   reserved22;	//0xCC4F1508
	UINT32                                                   reserved23;	//0xCC4F150C
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_0_T                  vcp_sg_mvc_ctrl_0;	//0xCC4F1510
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_1_T                  vcp_sg_mvc_ctrl_1;	//0xCC4F1514
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_2_T                  vcp_sg_mvc_ctrl_2;	//0xCC4F1518
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_3_T                  vcp_sg_mvc_ctrl_3;	//0xCC4F151C
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_4_T                  vcp_sg_mvc_ctrl_4;	//0xCC4F1520
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_5_T                  vcp_sg_mvc_ctrl_5;	//0xCC4F1524
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_6_T                  vcp_sg_mvc_ctrl_6;	//0xCC4F1528
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_7_T                  vcp_sg_mvc_ctrl_7;	//0xCC4F152C
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_8_T                  vcp_sg_mvc_ctrl_8;	//0xCC4F1530
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_9_T                  vcp_sg_mvc_ctrl_9;	//0xCC4F1534
	PE_M23_VCP_DISP_MON_VCP_U0Y_PIC_INIT_POS_T    mon_vcp_u0y_pic_init_pos;	//0xCC4F1538
	PE_M23_VCP_DISP_MON_VCP_U0Y_PIC_START_POS_T  mon_vcp_u0y_pic_start_pos;	//0xCC4F153C
	PE_M23_VCP_DISP_MON_VCP_U0C_PIC_INIT_POS_T    mon_vcp_u0c_pic_init_pos;	//0xCC4F1540
	PE_M23_VCP_DISP_MON_VCP_U0C_PIC_START_POS_T  mon_vcp_u0c_pic_start_pos;	//0xCC4F1544
	PE_M23_VCP_DISP_MON_VCP_U1Y_PIC_INIT_POS_T    mon_vcp_u1y_pic_init_pos;	//0xCC4F1548
	PE_M23_VCP_DISP_MON_VCP_U1Y_PIC_START_POS_T  mon_vcp_u1y_pic_start_pos;	//0xCC4F154C
	PE_M23_VCP_DISP_MON_VCP_U1C_PIC_INIT_POS_T    mon_vcp_u1c_pic_init_pos;	//0xCC4F1550
	PE_M23_VCP_DISP_MON_VCP_U1C_PIC_START_POS_T  mon_vcp_u1c_pic_start_pos;	//0xCC4F1554
	UINT32                                                   reserved24;	//0xCC4F1558
	UINT32                                                   reserved25;	//0xCC4F155C
	UINT32                                                   reserved26;	//0xCC4F1560
	UINT32                                                   reserved27;	//0xCC4F1564
	UINT32                                                   reserved28;	//0xCC4F1568
	UINT32                                                   reserved29;	//0xCC4F156C
	UINT32                                                   reserved30;	//0xCC4F1570
	UINT32                                                   reserved31;	//0xCC4F1574
	UINT32                                                   reserved32;	//0xCC4F1578
	UINT32                                                   reserved33;	//0xCC4F157C
	UINT32                                                   reserved34;	//0xCC4F1580
	UINT32                                                   reserved35;	//0xCC4F1584
	UINT32                                                   reserved36;	//0xCC4F1588
	UINT32                                                   reserved37;	//0xCC4F158C
	UINT32                                                   reserved38;	//0xCC4F1590
	UINT32                                                   reserved39;	//0xCC4F1594
	UINT32                                                   reserved40;	//0xCC4F1598
	UINT32                                                   reserved41;	//0xCC4F159C
	UINT32                                                   reserved42;	//0xCC4F15A0
	UINT32                                                   reserved43;	//0xCC4F15A4
	UINT32                                                   reserved44;	//0xCC4F15A8
	UINT32                                                   reserved45;	//0xCC4F15AC
	UINT32                                                   reserved46;	//0xCC4F15B0
	UINT32                                                   reserved47;	//0xCC4F15B4
	PE_M23_VCP_DISP_VCP_WCP_M_DISP_SIZE_T              vcp_wcp_m_disp_size;	//0xCC4F15B8
	PE_M23_VCP_DISP_VCP_WCP_M_PG_PAT_CTRL_T          vcp_wcp_m_pg_pat_ctrl;	//0xCC4F15BC
	UINT32                                                   reserved48;	//0xCC4F15C0
	UINT32                                                   reserved49;	//0xCC4F15C4
	PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_CTRL_T  vcp_wcp_m_pixel_read_ctrl;	//0xCC4F15C8
	PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T vcp_wcp_m_pixel_read_ctrl_aux;	//0xCC4F15CC
	PE_M23_VCP_DISP_VCP_WCP_M_LINE_CTRL0_T            vcp_wcp_m_line_ctrl0;	//0xCC4F15D0
	PE_M23_VCP_DISP_VCP_WCP_M_LINE_CTRL1_T            vcp_wcp_m_line_ctrl1;	//0xCC4F15D4
	UINT32                                                   reserved50;	//0xCC4F15D8
	UINT32                                                   reserved51;	//0xCC4F15DC
	PE_M23_VCP_DISP_VCP_WCP_M_REC0_POS_X_T            vcp_wcp_m_rec0_pos_x;	//0xCC4F15E0
	PE_M23_VCP_DISP_VCP_WCP_M_REC0_POS_Y_T            vcp_wcp_m_rec0_pos_y;	//0xCC4F15E4
	PE_M23_VCP_DISP_VCP_WCP_M_REC1_POS_X_T            vcp_wcp_m_rec1_pos_x;	//0xCC4F15E8
	PE_M23_VCP_DISP_VCP_WCP_M_REC1_POS_Y_T            vcp_wcp_m_rec1_pos_y;	//0xCC4F15EC
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_0_T                    vcp_wcp_m_ctrl_0;	//0xCC4F15F0
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_1_T                    vcp_wcp_m_ctrl_1;	//0xCC4F15F4
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_2_T                    vcp_wcp_m_ctrl_2;	//0xCC4F15F8
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_3_T                    vcp_wcp_m_ctrl_3;	//0xCC4F15FC
	UINT32                                                   reserved52;	//0xCC4F1600
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_5_T                    vcp_wcp_m_ctrl_5;	//0xCC4F1604
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_6_T                    vcp_wcp_m_ctrl_6;	//0xCC4F1608
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_7_T                    vcp_wcp_m_ctrl_7;	//0xCC4F160C
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_8_T                    vcp_wcp_m_ctrl_8;	//0xCC4F1610
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_9_T                    vcp_wcp_m_ctrl_9;	//0xCC4F1614
	PE_M23_VCP_DISP_VCP_WCP_M_CTRL_10_T                  vcp_wcp_m_ctrl_10;	//0xCC4F1618
	UINT32                                                   reserved53;	//0xCC4F161C
	UINT32                                                   reserved54;	//0xCC4F1620
	UINT32                                                   reserved55;	//0xCC4F1624
	UINT32                                                   reserved56;	//0xCC4F1628
	UINT32                                                   reserved57;	//0xCC4F162C
	UINT32                                                   reserved58;	//0xCC4F1630
	UINT32                                                   reserved59;	//0xCC4F1634
	UINT32                                                   reserved60;	//0xCC4F1638
	UINT32                                                   reserved61;	//0xCC4F163C
	UINT32                                                   reserved62;	//0xCC4F1640
	UINT32                                                   reserved63;	//0xCC4F1644
	UINT32                                                   reserved64;	//0xCC4F1648
	UINT32                                                   reserved65;	//0xCC4F164C
	PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_0_T vcp_wcp_m_pixel_read_data_0;	//0xCC4F1650
	PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_1_T vcp_wcp_m_pixel_read_data_1;	//0xCC4F1654
	PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_2_T vcp_wcp_m_pixel_read_data_2;	//0xCC4F1658
	PE_M23_VCP_DISP_VCP_WCP_M_PIXEL_READ_DATA_3_T vcp_wcp_m_pixel_read_data_3;	//0xCC4F165C
	PE_M23_VCP_DISP_VCP_SG_BDR_V0_PARAM_POS_M_T  vcp_sg_bdr_v0_param_pos_m;	//0xCC4F1660
	PE_M23_VCP_DISP_VCP_SG_BDR_V0_PARAM_SIZE_M_T vcp_sg_bdr_v0_param_size_m;	//0xCC4F1664
	PE_M23_VCP_DISP_VCP_SG_BDR_V1_PARAM_POS_M_T  vcp_sg_bdr_v1_param_pos_m;	//0xCC4F1668
	PE_M23_VCP_DISP_VCP_SG_BDR_V1_PARAM_SIZE_M_T vcp_sg_bdr_v1_param_size_m;	//0xCC4F166C
	UINT32                                                   reserved66;	//0xCC4F1670
	UINT32                                                   reserved67;	//0xCC4F1674
	UINT32                                                   reserved68;	//0xCC4F1678
	UINT32                                                   reserved69;	//0xCC4F167C
	PE_M23_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_0_T    vcp_sg_bdr_v0_0_m_ctrl_0;	//0xCC4F1680
	PE_M23_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_1_T    vcp_sg_bdr_v0_0_m_ctrl_1;	//0xCC4F1684
	PE_M23_VCP_DISP_VCP_SG_BDR_V0_0_M_CTRL_2_T    vcp_sg_bdr_v0_0_m_ctrl_2;	//0xCC4F1688
	UINT32                                                   reserved70;	//0xCC4F168C
	PE_M23_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_0_T    vcp_sg_bdr_v0_1_m_ctrl_0;	//0xCC4F1690
	PE_M23_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_1_T    vcp_sg_bdr_v0_1_m_ctrl_1;	//0xCC4F1694
	PE_M23_VCP_DISP_VCP_SG_BDR_V0_1_M_CTRL_2_T    vcp_sg_bdr_v0_1_m_ctrl_2;	//0xCC4F1698
	UINT32                                                   reserved71;	//0xCC4F169C
	UINT32                                                   reserved72;	//0xCC4F16A0
	UINT32                                                   reserved73;	//0xCC4F16A4
	UINT32                                                   reserved74;	//0xCC4F16A8
	UINT32                                                   reserved75;	//0xCC4F16AC
	UINT32                                                   reserved76;	//0xCC4F16B0
	UINT32                                                   reserved77;	//0xCC4F16B4
	UINT32                                                   reserved78;	//0xCC4F16B8
	UINT32                                                   reserved79;	//0xCC4F16BC
	PE_M23_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_0_T    vcp_sg_bdr_v1_0_m_ctrl_0;	//0xCC4F16C0
	PE_M23_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_1_T    vcp_sg_bdr_v1_0_m_ctrl_1;	//0xCC4F16C4
	PE_M23_VCP_DISP_VCP_SG_BDR_V1_0_M_CTRL_2_T    vcp_sg_bdr_v1_0_m_ctrl_2;	//0xCC4F16C8
	UINT32                                                   reserved80;	//0xCC4F16CC
	PE_M23_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_0_T    vcp_sg_bdr_v1_1_m_ctrl_0;	//0xCC4F16D0
	PE_M23_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_1_T    vcp_sg_bdr_v1_1_m_ctrl_1;	//0xCC4F16D4
	PE_M23_VCP_DISP_VCP_SG_BDR_V1_1_M_CTRL_2_T    vcp_sg_bdr_v1_1_m_ctrl_2;	//0xCC4F16D8
	UINT32                                                   reserved81;	//0xCC4F16DC
	UINT32                                                   reserved82;	//0xCC4F16E0
	UINT32                                                   reserved83;	//0xCC4F16E4
	UINT32                                                   reserved84;	//0xCC4F16E8
	UINT32                                                   reserved85;	//0xCC4F16EC
	UINT32                                                   reserved86;	//0xCC4F16F0
	UINT32                                                   reserved87;	//0xCC4F16F4
	UINT32                                                   reserved88;	//0xCC4F16F8
	UINT32                                                   reserved89;	//0xCC4F16FC
	UINT32                                                   reserved90;	//0xCC4F1700
	UINT32                                                   reserved91;	//0xCC4F1704
	UINT32                                                   reserved92;	//0xCC4F1708
	UINT32                                                   reserved93;	//0xCC4F170C
	UINT32                                                   reserved94;	//0xCC4F1710
	UINT32                                                   reserved95;	//0xCC4F1714
	UINT32                                                   reserved96;	//0xCC4F1718
	UINT32                                                   reserved97;	//0xCC4F171C
	UINT32                                                   reserved98;	//0xCC4F1720
	UINT32                                                   reserved99;	//0xCC4F1724
	UINT32                                                  reserved100;	//0xCC4F1728
	UINT32                                                  reserved101;	//0xCC4F172C
	UINT32                                                  reserved102;	//0xCC4F1730
	UINT32                                                  reserved103;	//0xCC4F1734
	UINT32                                                  reserved104;	//0xCC4F1738
	UINT32                                                  reserved105;	//0xCC4F173C
	UINT32                                                  reserved106;	//0xCC4F1740
	UINT32                                                  reserved107;	//0xCC4F1744
	UINT32                                                  reserved108;	//0xCC4F1748
	UINT32                                                  reserved109;	//0xCC4F174C
	UINT32                                                  reserved110;	//0xCC4F1750
	UINT32                                                  reserved111;	//0xCC4F1754
	UINT32                                                  reserved112;	//0xCC4F1758
	UINT32                                                  reserved113;	//0xCC4F175C
	UINT32                                                  reserved114;	//0xCC4F1760
	UINT32                                                  reserved115;	//0xCC4F1764
	UINT32                                                  reserved116;	//0xCC4F1768
	UINT32                                                  reserved117;	//0xCC4F176C
	UINT32                                                  reserved118;	//0xCC4F1770
	UINT32                                                  reserved119;	//0xCC4F1774
	UINT32                                                  reserved120;	//0xCC4F1778
	UINT32                                                  reserved121;	//0xCC4F177C
	PE_M23_VCP_DISP_VCP_WCP_M_REC5_POS_X_T            vcp_wcp_m_rec5_pos_x;	//0xCC4F1780
	PE_M23_VCP_DISP_VCP_WCP_M_REC5_POS_Y_T            vcp_wcp_m_rec5_pos_y;	//0xCC4F1784
	PE_M23_VCP_DISP_VCP_WCP_M_REC5_CLR_T                vcp_wcp_m_rec5_clr;	//0xCC4F1788
	PE_M23_VCP_DISP_VCP_WCP_M_REC6_POS_X_T            vcp_wcp_m_rec6_pos_x;	//0xCC4F178C
	PE_M23_VCP_DISP_VCP_WCP_M_REC6_POS_Y_T            vcp_wcp_m_rec6_pos_y;	//0xCC4F1790
	PE_M23_VCP_DISP_VCP_WCP_M_REC6_CLR_T                vcp_wcp_m_rec6_clr;	//0xCC4F1794
	PE_M23_VCP_DISP_VCP_WCP_M_REC7_POS_X_T            vcp_wcp_m_rec7_pos_x;	//0xCC4F1798
	PE_M23_VCP_DISP_VCP_WCP_M_REC7_POS_Y_T            vcp_wcp_m_rec7_pos_y;	//0xCC4F179C
	PE_M23_VCP_DISP_VCP_WCP_M_REC7_CLR_T                vcp_wcp_m_rec7_clr;	//0xCC4F17A0
	PE_M23_VCP_DISP_VCP_WCP_M_REC8_POS_X_T            vcp_wcp_m_rec8_pos_x;	//0xCC4F17A4
	PE_M23_VCP_DISP_VCP_WCP_M_REC8_POS_Y_T            vcp_wcp_m_rec8_pos_y;	//0xCC4F17A8
	PE_M23_VCP_DISP_VCP_WCP_M_REC8_CLR_T                vcp_wcp_m_rec8_clr;	//0xCC4F17AC
	PE_M23_VCP_DISP_VCP_WCP_M_REC9_POS_X_T            vcp_wcp_m_rec9_pos_x;	//0xCC4F17B0
	PE_M23_VCP_DISP_VCP_WCP_M_REC9_POS_Y_T            vcp_wcp_m_rec9_pos_y;	//0xCC4F17B4
	PE_M23_VCP_DISP_VCP_WCP_M_REC9_CLR_T                vcp_wcp_m_rec9_clr;	//0xCC4F17B8
	UINT32                                                  reserved122;	//0xCC4F17BC
	UINT32                                                  reserved123;	//0xCC4F17C0
	UINT32                                                  reserved124;	//0xCC4F17C4
	UINT32                                                  reserved125;	//0xCC4F17C8
	UINT32                                                  reserved126;	//0xCC4F17CC
	UINT32                                                  reserved127;	//0xCC4F17D0
	UINT32                                                  reserved128;	//0xCC4F17D4
	UINT32                                                  reserved129;	//0xCC4F17D8
	UINT32                                                  reserved130;	//0xCC4F17DC
	UINT32                                                  reserved131;	//0xCC4F17E0
	UINT32                                                  reserved132;	//0xCC4F17E4
	UINT32                                                  reserved133;	//0xCC4F17E8
	UINT32                                                  reserved134;	//0xCC4F17EC
	PE_M23_VCP_DISP_VCP_WCP_REG0_V0_POS_X_T          vcp_wcp_reg0_v0_pos_x;	//0xCC4F17F0
	PE_M23_VCP_DISP_VCP_WCP_REG0_V0_POS_Y_T          vcp_wcp_reg0_v0_pos_y;	//0xCC4F17F4
	PE_M23_VCP_DISP_VCP_WCP_REG1_V0_POS_X_T          vcp_wcp_reg1_v0_pos_x;	//0xCC4F17F8
	PE_M23_VCP_DISP_VCP_WCP_REG1_V0_POS_Y_T          vcp_wcp_reg1_v0_pos_y;	//0xCC4F17FC
	PE_M23_VCP_DISP_VCP_WCP_REG2_V0_POS_X_T          vcp_wcp_reg2_v0_pos_x;	//0xCC4F1800
	PE_M23_VCP_DISP_VCP_WCP_REG2_V0_POS_Y_T          vcp_wcp_reg2_v0_pos_y;	//0xCC4F1804
	PE_M23_VCP_DISP_VCP_WCP_REG3_V0_POS_X_T          vcp_wcp_reg3_v0_pos_x;	//0xCC4F1808
	PE_M23_VCP_DISP_VCP_WCP_REG3_V0_POS_Y_T          vcp_wcp_reg3_v0_pos_y;	//0xCC4F180C
	PE_M23_VCP_DISP_VCP_WCP_REG4_V0_POS_X_T          vcp_wcp_reg4_v0_pos_x;	//0xCC4F1810
	PE_M23_VCP_DISP_VCP_WCP_REG4_V0_POS_Y_T          vcp_wcp_reg4_v0_pos_y;	//0xCC4F1814
	UINT32                                                  reserved135;	//0xCC4F1818
	UINT32                                                  reserved136;	//0xCC4F181C
	UINT32                                                  reserved137;	//0xCC4F1820
	UINT32                                                  reserved138;	//0xCC4F1824
	UINT32                                                  reserved139;	//0xCC4F1828
	UINT32                                                  reserved140;	//0xCC4F182C
	PE_M23_VCP_DISP_VCP_WCP_PE_M23_ALPHA_T                  vcp_wcp_reg_alpha;	//0xCC4F1830
	PE_M23_VCP_DISP_VCP_WCP_M_REC2_POS_X_T            vcp_wcp_m_rec2_pos_x;	//0xCC4F1834
	PE_M23_VCP_DISP_VCP_WCP_M_REC2_POS_Y_T            vcp_wcp_m_rec2_pos_y;	//0xCC4F1838
	PE_M23_VCP_DISP_VCP_WCP_M_REC3_POS_X_T            vcp_wcp_m_rec3_pos_x;	//0xCC4F183C
	PE_M23_VCP_DISP_VCP_WCP_M_REC3_POS_Y_T            vcp_wcp_m_rec3_pos_y;	//0xCC4F1840
	PE_M23_VCP_DISP_VCP_WCP_M_REC4_POS_X_T            vcp_wcp_m_rec4_pos_x;	//0xCC4F1844
	PE_M23_VCP_DISP_VCP_WCP_M_REC4_POS_Y_T            vcp_wcp_m_rec4_pos_y;	//0xCC4F1848
	PE_M23_VCP_DISP_VCP_WCP_M_REC0_CLR_T                vcp_wcp_m_rec0_clr;	//0xCC4F184C
	PE_M23_VCP_DISP_VCP_WCP_M_REC1_CLR_T                vcp_wcp_m_rec1_clr;	//0xCC4F1850
	PE_M23_VCP_DISP_VCP_WCP_M_REC2_CLR_T                vcp_wcp_m_rec2_clr;	//0xCC4F1854
	PE_M23_VCP_DISP_VCP_WCP_M_REC3_CLR_T                vcp_wcp_m_rec3_clr;	//0xCC4F1858
	PE_M23_VCP_DISP_VCP_WCP_M_REC4_CLR_T                vcp_wcp_m_rec4_clr;	//0xCC4F185C
	PE_M23_VCP_DISP_VCP_VSP_U0_CTRL_00_T                vcp_vsp_u0_ctrl_00;	//0xCC4F1860
	PE_M23_VCP_DISP_VCP_VSP_U0_CTRL_01_T                vcp_vsp_u0_ctrl_01;	//0xCC4F1864
	PE_M23_VCP_DISP_VCP_VSP_U1_CTRL_00_T                vcp_vsp_u1_ctrl_00;	//0xCC4F1868
	PE_M23_VCP_DISP_VCP_VSP_U1_CTRL_01_T                vcp_vsp_u1_ctrl_01;	//0xCC4F186C
	PE_M23_VCP_DISP_VCP_CRC_CTRL_T                            vcp_crc_ctrl;	//0xCC4F1870
	PE_M23_VCP_DISP_VCP_CRC_DATA_MASK0_T                vcp_crc_data_mask0;	//0xCC4F1874
	PE_M23_VCP_DISP_VCP_CRC_DATA_MASK1_T                vcp_crc_data_mask1;	//0xCC4F1878
	UINT32                                                  reserved141;	//0xCC4F187C
	UINT32                                                  reserved142;	//0xCC4F1880
	PE_M23_VCP_DISP_VCP_CRC_OUT0_T                            vcp_crc_out0;	//0xCC4F1884
	PE_M23_VCP_DISP_VCP_CRC_OUT1_T                            vcp_crc_out1;	//0xCC4F1888
	UINT32                                                  reserved143;	//0xCC4F188C
	UINT32                                                  reserved144;	//0xCC4F1890
	UINT32                                                  reserved145;	//0xCC4F1894
	UINT32                                                  reserved146;	//0xCC4F1898
	UINT32                                                  reserved147;	//0xCC4F189C
	PE_M23_VCP_DISP_VCP_SG_MVY_CTRL_A_T                  vcp_sg_mvy_ctrl_a;	//0xCC4F18A0
	PE_M23_VCP_DISP_VCP_SG_MVC_CTRL_A_T                  vcp_sg_mvc_ctrl_a;	//0xCC4F18A4
	PE_M23_VCP_DISP_VCP_SG_SVY_CTRL_A_T                  vcp_sg_svy_ctrl_a;	//0xCC4F18A8
	PE_M23_VCP_DISP_VCP_SG_SVC_CTRL_A_T                  vcp_sg_svc_ctrl_a;	//0xCC4F18AC
	UINT32                                                  reserved148;	//0xCC4F18B0
	UINT32                                                  reserved149;	//0xCC4F18B4
	UINT32                                                  reserved150;	//0xCC4F18B8
	UINT32                                                  reserved151;	//0xCC4F18BC
	UINT32                                                  reserved152;	//0xCC4F18C0
	UINT32                                                  reserved153;	//0xCC4F18C4
	UINT32                                                  reserved154;	//0xCC4F18C8
	UINT32                                                  reserved155;	//0xCC4F18CC
	UINT32                                                  reserved156;	//0xCC4F18D0
	UINT32                                                  reserved157;	//0xCC4F18D4
	UINT32                                                  reserved158;	//0xCC4F18D8
	UINT32                                                  reserved159;	//0xCC4F18DC
	UINT32                                                  reserved160;	//0xCC4F18E0
	UINT32                                                  reserved161;	//0xCC4F18E4
	UINT32                                                  reserved162;	//0xCC4F18E8
	UINT32                                                  reserved163;	//0xCC4F18EC
	UINT32                                                  reserved164;	//0xCC4F18F0
	UINT32                                                  reserved165;	//0xCC4F18F4
	UINT32                                                  reserved166;	//0xCC4F18F8
	UINT32                                                  reserved167;	//0xCC4F18FC
	PE_M23_VCP_DISP_VCP_DISP_INTR_MASK_T                vcp_disp_intr_mask;	//0xCC4F1900
	PE_M23_VCP_DISP_VCP_DISP_INTR_CLEAR_T              vcp_disp_intr_clear;	//0xCC4F1904
	PE_M23_VCP_DISP_VCP_DISP_INTR_STATUS_T            vcp_disp_intr_status;	//0xCC4F1908
	PE_M23_VCP_DISP_VCP_DISP_INTR0_POS_MV_Y_T      vcp_disp_intr0_pos_mv_y;	//0xCC4F190C
	PE_M23_VCP_DISP_VCP_DISP_INTR1_POS_MV_Y_T      vcp_disp_intr1_pos_mv_y;	//0xCC4F1910
	PE_M23_VCP_DISP_VCP_DISP_INTR0_POS_MV_C_T      vcp_disp_intr0_pos_mv_c;	//0xCC4F1914
	PE_M23_VCP_DISP_VCP_DISP_INTR1_POS_MV_C_T      vcp_disp_intr1_pos_mv_c;	//0xCC4F1918
	PE_M23_VCP_DISP_VCP_DISP_INTR0_POS_SV_Y_T      vcp_disp_intr0_pos_sv_y;	//0xCC4F191C
	PE_M23_VCP_DISP_VCP_DISP_INTR1_POS_SV_Y_T      vcp_disp_intr1_pos_sv_y;	//0xCC4F1920
	PE_M23_VCP_DISP_VCP_DISP_INTR0_POS_SV_C_T      vcp_disp_intr0_pos_sv_c;	//0xCC4F1924
	PE_M23_VCP_DISP_VCP_DISP_INTR1_POS_SV_C_T      vcp_disp_intr1_pos_sv_c;	//0xCC4F1928
	PE_M23_VCP_DISP_VCP_DISP_INTR_SRC_SEL_T          vcp_disp_intr_src_sel;	//0xCC4F192C
	PE_M23_VCP_DISP_VCP_U0_CSC_CTRL7_T                    vcp_u0_csc_ctrl7;	//0xCC4F1930
	PE_M23_VCP_DISP_VCP_U1_CSC_CTRL0_T                    vcp_u1_csc_ctrl0;	//0xCC4F1934
	PE_M23_VCP_DISP_VCP_U1_CSC_CTRL1_T                    vcp_u1_csc_ctrl1;	//0xCC4F1938
	PE_M23_VCP_DISP_VCP_U1_CSC_CTRL2_T                    vcp_u1_csc_ctrl2;	//0xCC4F193C
	PE_M23_VCP_DISP_VCP_U1_CSC_CTRL3_T                    vcp_u1_csc_ctrl3;	//0xCC4F1940
	PE_M23_VCP_DISP_VCP_U1_CSC_CTRL4_T                    vcp_u1_csc_ctrl4;	//0xCC4F1944
	PE_M23_VCP_DISP_VCP_U1_CSC_CTRL5_T                    vcp_u1_csc_ctrl5;	//0xCC4F1948
	PE_M23_VCP_DISP_VCP_U1_CSC_CTRL6_T                    vcp_u1_csc_ctrl6;	//0xCC4F194C
	PE_M23_VCP_DISP_VCP_U1_CSC_CTRL7_T                    vcp_u1_csc_ctrl7;	//0xCC4F1950
	PE_M23_VCP_DISP_VCP_ACTIVE_LINE_CNT_T              vcp_active_line_cnt;	//0xCC4F1954
}PE_VCP_DISP_REG_M23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC463F00 RW 0x0000_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_M23_VSD0_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC463F04 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_M23_VSD0_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC463F08 RW 0x0000_0000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 cg_disable                       :1;	//(4,RW,0x00) //0 : Clock gating, 1 : disable CG  (VSP, vcp_pg_pat_ctrl)
	UINT32 resvd1                           :3;
	UINT32 center_position                  :8;	//(15:8,RW,0x0) //
	UINT32 contrast                         :10;	//(25:16,RW,0x0200) //
	UINT32 resvd2                           :6;
	};
}PE_M23_VSD0_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC463F0C RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//(15:8,RW,0x80) //
	UINT32 brightness                       :10;	//(25:16,RW,0x0200) //
	UINT32 resvd1                           :6;
	};
}PE_M23_VSD0_VERI_SYS_VERI_3_T;

typedef struct {
	PE_M23_VSD0_VERI_SYS_VERI_0_T                          vsd_veri_vsp0_0;	//0xCC463F00
	PE_M23_VSD0_VERI_SYS_VERI_1_T                          vsd_veri_vsp0_1;	//0xCC463F04
	PE_M23_VSD0_VERI_SYS_VERI_2_T                          vsd_veri_vsp1_0;	//0xCC463F08
	PE_M23_VSD0_VERI_SYS_VERI_3_T                          vsd_veri_vsp1_1;	//0xCC463F0C
}PE_VSD0_VERI_REG_M23_T;

#endif
