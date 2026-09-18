#ifndef _REG_DNE_MON_h
#define _REG_DNE_MON_h
//Header File for DNE_MON in \PQE\O22-A0_PQE_MON_reg_man.xls

#define REG_DNE_MON_CTRL_STAMP                                              (APB_DNE_MON_BASE+0x0000)
#define REG_DNE_MON_CTRL_TIMER_RESET                                        (APB_DNE_MON_BASE+0x0004)
#define REG_DNE_MON_CTRL_TIMER_RESET_PERIOD                                 (APB_DNE_MON_BASE+0x0008)
#define REG_DNE_MON_CTRL_MON_APB                                            (APB_DNE_MON_BASE+0x000C)
#define REG_DNE_MON_CTRL_MON_SYNC_P0_0                                      (APB_DNE_MON_BASE+0x0010)
#define REG_DNE_MON_CTRL_MON_SYNC_P0_1                                      (APB_DNE_MON_BASE+0x0014)
#define REG_DNE_MON_CTRL_MON_SYNC_P0_2                                      (APB_DNE_MON_BASE+0x0018)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PIXEL                                  (APB_DNE_MON_BASE+0x001C)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PARAM0                                 (APB_DNE_MON_BASE+0x0020)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PARAM1                                 (APB_DNE_MON_BASE+0x0024)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PARAM2                                 (APB_DNE_MON_BASE+0x0028)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PARAM3                                 (APB_DNE_MON_BASE+0x002C)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PARAM4                                 (APB_DNE_MON_BASE+0x0030)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PARAM5                                 (APB_DNE_MON_BASE+0x0034)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PARAM6                                 (APB_DNE_MON_BASE+0x0038)
#define REG_DNE_MON_INFO_MON_SYNC_P0_PARAM7                                 (APB_DNE_MON_BASE+0x003C)
#define REG_DNE_MON_CTRL_MON_SYNC_P1_0                                      (APB_DNE_MON_BASE+0x0040)
#define REG_DNE_MON_CTRL_MON_SYNC_P1_1                                      (APB_DNE_MON_BASE+0x0044)
#define REG_DNE_MON_INFO_MON_SYNC_P1_PIXEL                                  (APB_DNE_MON_BASE+0x004C)
#define REG_DNE_MON_APB_MASK_EN                                             (APB_DNE_MON_BASE+0x0050)
#define REG_DNE_MON_APB_MASK_LVL                                            (APB_DNE_MON_BASE+0x0054)
#define REG_DNE_MON_CTRL_MON_SYNC_P2_0                                      (APB_DNE_MON_BASE+0x0070)
#define REG_DNE_MON_CTRL_MON_SYNC_P2_1                                      (APB_DNE_MON_BASE+0x0074)
#define REG_DNE_MON_CTRL_CRC_NUM_16                                         (APB_DNE_MON_BASE+0x0078)
#define REG_DNE_MON_INFO_MON_SYNC_P2_PIXEL                                  (APB_DNE_MON_BASE+0x007C)
#define REG_DNE_MON_INFO_STAMP0_PRES_PIC_INIT                               (APB_DNE_MON_BASE+0x00A0)
#define REG_DNE_MON_INFO_STAMP0_PRES_PIC_START                              (APB_DNE_MON_BASE+0x00A4)
#define REG_DNE_MON_INFO_STAMP0_PRES_PIC_END                                (APB_DNE_MON_BASE+0x00A8)
#define REG_DNE_MON_INFO_STAMP0_PREV_PIC_INIT                               (APB_DNE_MON_BASE+0x00AC)
#define REG_DNE_MON_INFO_STAMP0_PREV_PIC_START                              (APB_DNE_MON_BASE+0x00B0)
#define REG_DNE_MON_INFO_STAMP0_PREV_PIC_END                                (APB_DNE_MON_BASE+0x00B4)
#define REG_DNE_MON_INFO_STAMP1_PRES_PIC_INIT                               (APB_DNE_MON_BASE+0x00B8)
#define REG_DNE_MON_INFO_STAMP1_PRES_PIC_START                              (APB_DNE_MON_BASE+0x00BC)
#define REG_DNE_MON_INFO_STAMP1_PRES_PIC_END                                (APB_DNE_MON_BASE+0x00C0)
#define REG_DNE_MON_INFO_STAMP1_PREV_PIC_INIT                               (APB_DNE_MON_BASE+0x00C4)
#define REG_DNE_MON_INFO_STAMP1_PREV_PIC_START                              (APB_DNE_MON_BASE+0x00C8)
#define REG_DNE_MON_INFO_STAMP1_PREV_PIC_END                                (APB_DNE_MON_BASE+0x00CC)
#define REG_DNE_MON_INFO_STAMP2_PRES_PIC_INIT                               (APB_DNE_MON_BASE+0x00D0)
#define REG_DNE_MON_INFO_STAMP2_PRES_PIC_START                              (APB_DNE_MON_BASE+0x00D4)
#define REG_DNE_MON_INFO_STAMP2_PRES_PIC_END                                (APB_DNE_MON_BASE+0x00D8)
#define REG_DNE_MON_INFO_STAMP2_PREV_PIC_INIT                               (APB_DNE_MON_BASE+0x00DC)
#define REG_DNE_MON_INFO_STAMP2_PREV_PIC_START                              (APB_DNE_MON_BASE+0x00E0)
#define REG_DNE_MON_INFO_STAMP2_PREV_PIC_END                                (APB_DNE_MON_BASE+0x00E4)
#define REG_DNE_MON_INFO_STAMP_PRES_SRC_SYNC                                (APB_DNE_MON_BASE+0x00E8)
#define REG_DNE_MON_INFO_STAMP_PREV_SRC_SYNC                                (APB_DNE_MON_BASE+0x00EC)
#define REG_DNE_MON_INFO_STAMP_PRES_DISP_SYNC                               (APB_DNE_MON_BASE+0x00F0)
#define REG_DNE_MON_INFO_STAMP_PREV_DISP_SYNC                               (APB_DNE_MON_BASE+0x00F4)
#define REG_DNE_MON_INFO_STATUS_MON_CLOCKS                                  (APB_DNE_MON_BASE+0x00F8)
#define REG_DNE_MON_INFO_STATUS_MON_APB                                     (APB_DNE_MON_BASE+0x00FC)

typedef union {
	UINT32 udata32;
	struct {						//0xCC880100 RW 0x0210_0000
	UINT32 reg_src_timer_en                 :1;	//(0,RW,0x00) //0 : OFF	1 : ON
	UINT32 reg_src_timer_rst_en             :1;	//(1,RW,0x00) //src_timer를 disp_sync에 맞춰서 reset 할지 말지 결정	0 : reset안함.	1 : src_sync 마다 timer reset
	UINT32 resvd0                           :2;
	UINT32 reg_disp_timer_en                :1;	//(4,RW,0x00) //0 : OFF	1 : ON
	UINT32 reg_disp_timer_rst_en            :1;	//(5,RW,0x00) //disp_timer를 disp_sync에 맞춰서 reset 할지 말지 결정	0 : reset안함.	1 : disp_sync마다 timer reset
	UINT32 resvd1                           :2;
	UINT32 reg_time_stamp_src_sel_src       :1;	//(8,RW,0x00) //0 : timer_src	1 : timer_disp
	UINT32 resvd2                           :3;
	UINT32 reg_time_stamp_src_sel_disp      :1;	//(12,RW,0x00) //0 : timer_src	1 : timer_disp
	UINT32 resvd3                           :2;
	UINT32 reg_info_stamp_sel               :1;	//(15,RW,0x00) //0 : 0x00A0 ~ 0x00DC는 INFO_CRC_0 ~ INFO_CRC_F로 사용 됩니다.	1 : 0x00A0 ~ 0x00DC는 INFO_STAMP0 ~ INFO_STAMP2로 사용 됩니다.
	UINT32 stamp0_idx_pic_init              :3;	//(18:16,RW,0x00) //0 : g0_pic_init/start/end	1 : g1_pic_init/start/end	2 : g2_pic_init/start/end	3 : g3_pic_init/start/end	4 : g4_pic_init/start/end	5 : g5_pic_init/start/end	6 : g6_pic_init/start/end	7 : g7_pic_init/start/end
	UINT32 stamp0_sel_src                   :1;	//(19,RW,0x00) //0 : timer_src	1 : timer_disp
	UINT32 stamp1_idx_pic_init              :3;	//(22:20,RW,0x01) //0 : g0_pic_init/start/end	1 : g1_pic_init/start/end	2 : g2_pic_init/start/end	3 : g3_pic_init/start/end	4 : g4_pic_init/start/end	5 : g5_pic_init/start/end	6 : g6_pic_init/start/end	7 : g7_pic_init/start/end
	UINT32 stamp1_sel_src                   :1;	//(23,RW,0x00) //0 : timer_src	1 : timer_disp
	UINT32 stamp2_idx_pic_init              :3;	//(26:24,RW,0x02) //0 : g0_pic_init/start/end	1 : g1_pic_init/start/end	2 : g2_pic_init/start/end	3 : g3_pic_init/start/end	4 : g4_pic_init/start/end	5 : g5_pic_init/start/end	6 : g6_pic_init/start/end	7 : g7_pic_init/start/end
	UINT32 stamp2_sel_src                   :1;	//(27,RW,0x00) //0 : timer_src	1 : timer_disp
	UINT32 resvd4                           :4;
	};
}REG_DNE_MON_CTRL_STAMP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880104 RW 0x0000_0000
	UINT32 reg_timer_reset_sw               :1;	//(0,RW,0x00) //AUTO CLEAR
	UINT32 resvd0                           :3;
	UINT32 reg_timer_reset_en               :1;	//(4,RW,0x00) //TIMER RESET ON/OFF	0 : OFF	1 : ON
	UINT32 reg_timer_reset_sync_en          :1;	//(5,RW,0x00) //timer를 어떤 SYNC든지 에 맞춰서 초기화를 하겠다.
	UINT32 resvd1                           :2;
	UINT32 idx_timer_reset_sync             :3;	//(10:8,RW,0x00) //0 : 	~	7 :
	UINT32 reg_timer_reset_sync_sel         :1;	//(11,RW,0x00) //0 : PSEUDO_SYNC (PERIOD는 0x8에서 Setting)	1 : SRC_SYNC/DISP_SYNC ( 0x4 [10:8] idx_timer_reset_sync에서 선택가능 )
	UINT32 reg_ctrl_mon_clk_sel             :4;	//(15:12,RW,0x00) //
	UINT32 reg_ctrl_mon_clk_en0             :16;	//(31:16,RW,0x0) //
	};
}REG_DNE_MON_CTRL_TIMER_RESET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880108 RW 0x0059_4390
	UINT32 reg_timer_reset_period           :32;	//(31:0,RW,0x0059_4390) //
	};
}REG_DNE_MON_CTRL_TIMER_RESET_PERIOD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88010C RW 0x0000_0000
	UINT32 reg_ctrl_apb_addr                :23;	//(22:0,RW,0x0000_0000) //특정주소를 ACCESS하는지 확인하고자 할때
	UINT32 resvd0                           :5;
	UINT32 reg_ctrl_apb_en                  :1;	//(28,RW,0x00) //ENABLE
	UINT32 reg_ctrl_apb_type                :1;	//(29,RW,0x00) //MONITOR SIGNAL의 모양을 변경함.	0 : PSEL이 있을 때, LEVEL바뀜.	1 : PSEL_RIS에 1이 되서 PREADY_RIS에서 0 되게 함.
	UINT32 resvd1                           :2;
	};
}REG_DNE_MON_CTRL_MON_APB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880110 RW 0x0000_0000
	UINT32 reg_ev_tpg_en                    :1;	//(0,RW,0x00) //TP ON/OFF
	UINT32 reg_ev_tpg_type                  :2;	//(2:1,RW,0x00) //TP Type 선택
	UINT32 resvd0                           :1;
	UINT32 reg_ev_tpg_match                 :1;	//(4,RW,0x00) //Match on/off
	UINT32 reg_ev_tpg_match_sel             :3;	//(7:5,RW,0x00) //[2] : BCB	[1] : GY	[0] : RCR
	UINT32 reg_od_tpg_en                    :1;	//(8,RW,0x00) //TP ON/OFF
	UINT32 reg_od_tpg_type                  :2;	//(10:9,RW,0x00) //TP Type 선택
	UINT32 resvd1                           :1;
	UINT32 reg_od_tpg_match                 :1;	//(12,RW,0x00) //Match on/off
	UINT32 reg_od_tpg_match_sel             :3;	//(15:13,RW,0x00) //[2] : BCB	[1] : GY	[0] : RCR
	UINT32 resvd2                           :4;
	UINT32 reg_param_src_sel                :1;	//(20,RW,0x00) //SYNC PARAM을 뽑고자 하는 PATH 선택	0 : EVEN	1 : ODD
	UINT32 resvd3                           :11;
	};
}REG_DNE_MON_CTRL_MON_SYNC_P0_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880114 RW 0x0000_0000
	UINT32 ypos                             :13;	//(12:0,RW,0x0) //좌표
	UINT32 resvd0                           :3;
	UINT32 xpos                             :13;	//(28:16,RW,0x0) //좌표
	UINT32 resvd1                           :2;
	UINT32 reg_pixel_picker_en              :1;	//(31,RW,0x00) //
	};
}REG_DNE_MON_CTRL_MON_SYNC_P0_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880118 RW 0x0000_0000
	UINT32 reg_info_mon_sync_px_sel         :4;	//(3:0,RW,0x0) //0 : P0	1 : P1	2 : P2
	UINT32 resvd                            :28;
	};
}REG_DNE_MON_CTRL_MON_SYNC_P0_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88011C RO 0x0000_0000
	UINT32 picked_bcb                       :10;	//(9:0,RO,0x00) //
	UINT32 picked_gy                        :10;	//(19:10,RO,0x00) //
	UINT32 picked_rcr                       :10;	//(29:20,RO,0x00) //
	UINT32 resvd                            :2;
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PIXEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880120 RO 0x0000_0000
	UINT32 vs                               :16;	//(15:0,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 VSYNC	1: P1 VSYNC	2: P2 VSYNC
	UINT32 vfp                              :16;	//(31:16,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 VFP	1: P1 VFP	2: P2 VFP
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PARAM0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880124 RO 0x0000_0000
	UINT32 va                               :16;	//(15:0,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 VACTIVE	1: P1 VACTIVE	2: P2 VACTIVE
	UINT32 vbp                              :16;	//(31:16,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 VBP	1: P1 VBP	2: P2 VBP
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880128 RO 0x0000_0000
	UINT32 hs                               :16;	//(15:0,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 HSYNC	1: P1 HSYNC	2: P2 HSYNC
	UINT32 hfp                              :16;	//(31:16,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 HFP	1: P1 HFP	2: P2 HFP
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88012C RO 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 HACTIVE	1: P1 HACTIHE	2: P2 HACTIHE
	UINT32 hbp                              :16;	//(31:16,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 HBP	1: P1 HBP	2: P2 HBP
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880130 RO 0x0000_0000
	UINT32 vtotal                           :16;	//(15:0,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 VTOTAL	1: P1 VTOTAL	2: P2 VTOTAL
	UINT32 htotal                           :16;	//(31:16,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0: P0 HTOTAL	1: P1 HTOTAL	2: P2 HTOTAL
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PARAM4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880134 RO 0x0000_0000
	UINT32 param_err_va                     :8;	//(7:0,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	UINT32 param_err_vbp                    :8;	//(15:8,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	UINT32 param_err_vs                     :8;	//(23:16,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	UINT32 param_err_vfp                    :8;	//(31:24,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PARAM5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880138 RO 0x0000_0000
	UINT32 param_err_ha                     :8;	//(7:0,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	UINT32 param_err_hbp                    :8;	//(15:8,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	UINT32 param_err_hs                     :8;	//(23:16,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	UINT32 param_err_hfp                    :8;	//(31:24,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PARAM6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88013C RO 0x0000_0000
	UINT32 v_ris_pos                        :16;	//(15:0,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	UINT32 h_ris_pos                        :16;	//(31:16,RO,0x0) //0x0018 CTRL_MON_SYNC_P0_2 [3:0] reg_info_mon_sync_px_sel	0 : P0	1 : P1	2 : P2
	};
}REG_DNE_MON_INFO_MON_SYNC_P0_PARAM7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880140 RW 0x0000_0000
	UINT32 reg_ev_tpg_en                    :1;	//(0,RW,0x00) //TP ON/OFF
	UINT32 reg_ev_tpg_type                  :2;	//(2:1,RW,0x00) //TP Type 선택
	UINT32 resvd0                           :1;
	UINT32 reg_ev_tpg_match                 :1;	//(4,RW,0x00) //Match on/off
	UINT32 reg_ev_tpg_match_sel             :3;	//(7:5,RW,0x00) //[2] : BCB	[1] : GY	[0] : RCR
	UINT32 reg_od_tpg_en                    :1;	//(8,RW,0x00) //TP ON/OFF
	UINT32 reg_od_tpg_type                  :2;	//(10:9,RW,0x00) //TP Type 선택
	UINT32 resvd1                           :1;
	UINT32 reg_od_tpg_match                 :1;	//(12,RW,0x00) //Match on/off
	UINT32 reg_od_tpg_match_sel             :3;	//(15:13,RW,0x00) //[2] : BCB	[1] : GY	[0] : RCR
	UINT32 resvd2                           :4;
	UINT32 reg_param_src_sel                :1;	//(20,RW,0x00) //SYNC PARAM을 뽑고자 하는 PATH 선택	0 : EVEN	1 : ODD
	UINT32 resvd3                           :11;
	};
}REG_DNE_MON_CTRL_MON_SYNC_P1_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880144 RW 0x0000_0000
	UINT32 ypos                             :13;	//(12:0,RW,0x0) //좌표
	UINT32 resvd0                           :3;
	UINT32 xpos                             :13;	//(28:16,RW,0x0) //좌표
	UINT32 resvd1                           :2;
	UINT32 reg_pixel_picker_en              :1;	//(31,RW,0x00) //
	};
}REG_DNE_MON_CTRL_MON_SYNC_P1_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88014C RO 0x0000_0000
	UINT32 picked_bcb                       :10;	//(9:0,RO,0x00) //
	UINT32 picked_gy                        :10;	//(19:10,RO,0x00) //
	UINT32 picked_rcr                       :10;	//(29:20,RO,0x00) //
	UINT32 resvd                            :2;
	};
}REG_DNE_MON_INFO_MON_SYNC_P1_PIXEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880150 RW 0x0000_0000
	UINT32 reg_apb_mask_en                  :32;	//(31:0,RW,0x00) //
	};
}REG_DNE_MON_APB_MASK_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880154 RO 0x0000_0000
	UINT32 reg_apb_mask_lvl                 :32;	//(31:0,RO,0x00) //
	};
}REG_DNE_MON_APB_MASK_LVL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880170 RW 0x0000_0000
	UINT32 reg_ev_tpg_en                    :1;	//(0,RW,0x00) //TP ON/OFF
	UINT32 reg_ev_tpg_type                  :2;	//(2:1,RW,0x00) //TP Type 선택
	UINT32 resvd0                           :1;
	UINT32 reg_ev_tpg_match                 :1;	//(4,RW,0x00) //Match on/off
	UINT32 reg_ev_tpg_match_sel             :3;	//(7:5,RW,0x00) //[2] : BCB	[1] : GY	[0] : RCR
	UINT32 reg_od_tpg_en                    :1;	//(8,RW,0x00) //TP ON/OFF
	UINT32 reg_od_tpg_type                  :2;	//(10:9,RW,0x00) //TP Type 선택
	UINT32 resvd1                           :1;
	UINT32 reg_od_tpg_match                 :1;	//(12,RW,0x00) //Match on/off
	UINT32 reg_od_tpg_match_sel             :3;	//(15:13,RW,0x00) //[2] : BCB	[1] : GY	[0] : RCR
	UINT32 resvd2                           :4;
	UINT32 reg_param_src_sel                :1;	//(20,RW,0x00) //SYNC PARAM을 뽑고자 하는 PATH 선택	0 : EVEN	1 : ODD
	UINT32 resvd3                           :11;
	};
}REG_DNE_MON_CTRL_MON_SYNC_P2_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880174 RW 0x0000_0000
	UINT32 ypos                             :13;	//(12:0,RW,0x0) //좌표
	UINT32 resvd0                           :3;
	UINT32 xpos                             :13;	//(28:16,RW,0x0) //좌표
	UINT32 resvd1                           :2;
	UINT32 reg_pixel_picker_en              :1;	//(31,RW,0x00) //
	};
}REG_DNE_MON_CTRL_MON_SYNC_P2_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880178 RW 0x0000_0000
	UINT32 crc_mux_dlatch                   :16;	//(15:0,RW,0x0) //[0] : vsync falling edge, pic_init	[1] : vsync rising edge, pic_end
	UINT32 crc_en                           :16;	//(31:16,RW,0x0) //CRC Enable
	};
}REG_DNE_MON_CTRL_CRC_NUM_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88017C RO 0x0000_0000
	UINT32 picked_bcb                       :10;	//(9:0,RO,0x00) //
	UINT32 picked_gy                        :10;	//(19:10,RO,0x00) //
	UINT32 picked_rcr                       :10;	//(29:20,RO,0x00) //
	UINT32 resvd                            :2;
	};
}REG_DNE_MON_INFO_MON_SYNC_P2_PIXEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801A0 RO 0x0000_0000
	UINT32 time_stamp0_pres_pic_init        :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_0 = (DNE0_RD_WGT0[127:64] ^ DNE0_RD_WGT0[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp0_pres_pic_init
	};
}REG_DNE_MON_INFO_STAMP0_PRES_PIC_INIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801A4 RO 0x0000_0000
	UINT32 time_stamp0_pres_pic_start       :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_1 = (DNE0_RD_WGT1[127:64] ^ DNE0_RD_WGT1[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp0_pres_pic_start
	};
}REG_DNE_MON_INFO_STAMP0_PRES_PIC_START_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801A8 RO 0x0000_0000
	UINT32 time_stamp0_pres_pic_end         :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_2 = (DNE0_RD_IFTR0[127:64] ^ DNE0_RD_IFTR0[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp0_pres_pic_end
	};
}REG_DNE_MON_INFO_STAMP0_PRES_PIC_END_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801AC RO 0x0000_0000
	UINT32 time_stamp0_prev_pic_init        :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_3 = (DNE0_RD_IFTR1[127:64] ^ DNE0_RD_IFTR1[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp0_prev_pic_init
	};
}REG_DNE_MON_INFO_STAMP0_PREV_PIC_INIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801B0 RO 0x0000_0000
	UINT32 time_stamp0_prev_pic_start       :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_4 = (DNE0_RD_IFTR2[127:64] ^ DNE0_RD_IFTR2[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp0_prev_pic_start
	};
}REG_DNE_MON_INFO_STAMP0_PREV_PIC_START_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801B4 RO 0x0000_0000
	UINT32 time_stamp0_prev_pic_end         :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_5 = (DNE0_RD_PRG[127:64] ^ DNE0_RD_PRG[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp0_prev_pic_end
	};
}REG_DNE_MON_INFO_STAMP0_PREV_PIC_END_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801B8 RO 0x0000_0000
	UINT32 time_stamp1_pres_pic_init        :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_6 = (DNE0_WD_OFTR0[127:64] ^ DNE0_WD_OFTR0[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp1_pres_pic_init
	};
}REG_DNE_MON_INFO_STAMP1_PRES_PIC_INIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801BC RO 0x0000_0000
	UINT32 time_stamp1_pres_pic_start       :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_7 = (DNE0_WD_OFTR1[127:64] ^ DNE0_WD_OFTR1[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp1_pres_pic_start
	};
}REG_DNE_MON_INFO_STAMP1_PRES_PIC_START_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801C0 RO 0x0000_0000
	UINT32 time_stamp1_pres_pic_end         :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_8 = (DNE1_RD_WGT0[127:64] ^ DNE1_RD_WGT0[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp1_pres_pic_end
	};
}REG_DNE_MON_INFO_STAMP1_PRES_PIC_END_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801C4 RO 0x0000_0000
	UINT32 time_stamp1_prev_pic_init        :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_9 = (DNE1_RD_WGT1[127:64] ^ DNE1_RD_WGT1[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp1_prev_pic_init
	};
}REG_DNE_MON_INFO_STAMP1_PREV_PIC_INIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801C8 RO 0x0000_0000
	UINT32 time_stamp1_prev_pic_start       :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_A = (DNE1_RD_IFTR0[127:64] ^ DNE1_RD_IFTR0[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp1_prev_pic_start
	};
}REG_DNE_MON_INFO_STAMP1_PREV_PIC_START_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801CC RO 0x0000_0000
	UINT32 time_stamp1_prev_pic_end         :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_B = (DNE1_RD_IFTR1[127:64] ^ DNE1_RD_IFTR1[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp1_prev_pic_end
	};
}REG_DNE_MON_INFO_STAMP1_PREV_PIC_END_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801D0 RO 0x0000_0000
	UINT32 time_stamp2_pres_pic_init        :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_C = (DNE1_RD_IFTR2[127:64] ^ DNE1_RD_IFTR2[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp2_pres_pic_init
	};
}REG_DNE_MON_INFO_STAMP2_PRES_PIC_INIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801D4 RO 0x0000_0000
	UINT32 time_stamp2_pres_pic_start       :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_D = (DNE1_RD_PRG[127:64] ^ DNE1_RD_PRG[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp2_pres_pic_start
	};
}REG_DNE_MON_INFO_STAMP2_PRES_PIC_START_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801D8 RO 0x0000_0000
	UINT32 time_stamp2_pres_pic_end         :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_E = (DNE1_WD_OFTR0[127:64] ^ DNE1_WD_OFTR0[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp2_pres_pic_end
	};
}REG_DNE_MON_INFO_STAMP2_PRES_PIC_END_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801DC RO 0x0000_0000
	UINT32 time_stamp2_prev_pic_init        :32;	//(31:0,RO,0x0000_0000) //CTRL_STAMP[15]==0 이면 	INFO_CRC_F = (DNE1_WD_OFTR1[127:64] ^ DNE1_WD_OFTR1[63:0])의 CRC 값	CTRL_STAMP[15]==1 이면 time_stamp2_prev_pic_init
	};
}REG_DNE_MON_INFO_STAMP2_PREV_PIC_INIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801E0 RO 0x0000_0000
	UINT32 time_stamp2_prev_pic_start       :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_DNE_MON_INFO_STAMP2_PREV_PIC_START_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801E4 RO 0x0000_0000
	UINT32 time_stamp2_prev_pic_end         :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_DNE_MON_INFO_STAMP2_PREV_PIC_END_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801E8 RO 0x0000_0000
	UINT32 time_stamp_pres_src_sync         :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_DNE_MON_INFO_STAMP_PRES_SRC_SYNC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801EC RO 0x0000_0000
	UINT32 time_stamp_prev_src_sync         :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_DNE_MON_INFO_STAMP_PREV_SRC_SYNC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801F0 RO 0x0000_0000
	UINT32 time_stamp_pres_disp_sync        :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_DNE_MON_INFO_STAMP_PRES_DISP_SYNC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801F4 RO 0x0000_0000
	UINT32 time_stamp_prev_disp_sync        :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_DNE_MON_INFO_STAMP_PREV_DISP_SYNC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801F8 RO 0x0000_0000
	UINT32 time_stamp_pres_disp_sync        :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_DNE_MON_INFO_STATUS_MON_CLOCKS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8801FC RO 0x0000_0000
	UINT32 time_stamp_prev_disp_sync        :32;	//(31:0,RO,0x0000_0000) //
	};
}REG_DNE_MON_INFO_STATUS_MON_APB_T;

typedef struct {
	REG_DNE_MON_CTRL_STAMP_T                                 ctrl_stamp;	//0xCC880100
	REG_DNE_MON_CTRL_TIMER_RESET_T                     ctrl_timer_reset;	//0xCC880104
	REG_DNE_MON_CTRL_TIMER_RESET_PERIOD_T       ctrl_timer_reset_period;	//0xCC880108
	REG_DNE_MON_CTRL_MON_APB_T                             ctrl_mon_apb;	//0xCC88010C
	REG_DNE_MON_CTRL_MON_SYNC_P0_0_T                 ctrl_mon_sync_p0_0;	//0xCC880110
	REG_DNE_MON_CTRL_MON_SYNC_P0_1_T                 ctrl_mon_sync_p0_1;	//0xCC880114
	REG_DNE_MON_CTRL_MON_SYNC_P0_2_T                 ctrl_mon_sync_p0_2;	//0xCC880118
	REG_DNE_MON_INFO_MON_SYNC_P0_PIXEL_T         info_mon_sync_p0_pixel;	//0xCC88011C
	REG_DNE_MON_INFO_MON_SYNC_P0_PARAM0_T       info_mon_sync_p0_param0;	//0xCC880120
	REG_DNE_MON_INFO_MON_SYNC_P0_PARAM1_T       info_mon_sync_p0_param1;	//0xCC880124
	REG_DNE_MON_INFO_MON_SYNC_P0_PARAM2_T       info_mon_sync_p0_param2;	//0xCC880128
	REG_DNE_MON_INFO_MON_SYNC_P0_PARAM3_T       info_mon_sync_p0_param3;	//0xCC88012C
	REG_DNE_MON_INFO_MON_SYNC_P0_PARAM4_T       info_mon_sync_p0_param4;	//0xCC880130
	REG_DNE_MON_INFO_MON_SYNC_P0_PARAM5_T       info_mon_sync_p0_param5;	//0xCC880134
	REG_DNE_MON_INFO_MON_SYNC_P0_PARAM6_T       info_mon_sync_p0_param6;	//0xCC880138
	REG_DNE_MON_INFO_MON_SYNC_P0_PARAM7_T       info_mon_sync_p0_param7;	//0xCC88013C
	REG_DNE_MON_CTRL_MON_SYNC_P1_0_T                 ctrl_mon_sync_p1_0;	//0xCC880140
	REG_DNE_MON_CTRL_MON_SYNC_P1_1_T                 ctrl_mon_sync_p1_1;	//0xCC880144
	UINT32                                                    reserved0;	//0xCC880148
	REG_DNE_MON_INFO_MON_SYNC_P1_PIXEL_T         info_mon_sync_p1_pixel;	//0xCC88014C
	REG_DNE_MON_APB_MASK_EN_T                               apb_mask_en;	//0xCC880150
	REG_DNE_MON_APB_MASK_LVL_T                             apb_mask_lvl;	//0xCC880154
	UINT32                                                    reserved1;	//0xCC880158
	UINT32                                                    reserved2;	//0xCC88015C
	UINT32                                                    reserved3;	//0xCC880160
	UINT32                                                    reserved4;	//0xCC880164
	UINT32                                                    reserved5;	//0xCC880168
	UINT32                                                    reserved6;	//0xCC88016C
	REG_DNE_MON_CTRL_MON_SYNC_P2_0_T                 ctrl_mon_sync_p2_0;	//0xCC880170
	REG_DNE_MON_CTRL_MON_SYNC_P2_1_T                 ctrl_mon_sync_p2_1;	//0xCC880174
	REG_DNE_MON_CTRL_CRC_NUM_16_T                       ctrl_crc_num_16;	//0xCC880178
	REG_DNE_MON_INFO_MON_SYNC_P2_PIXEL_T         info_mon_sync_p2_pixel;	//0xCC88017C
	UINT32                                                    reserved7;	//0xCC880180
	UINT32                                                    reserved8;	//0xCC880184
	UINT32                                                    reserved9;	//0xCC880188
	UINT32                                                   reserved10;	//0xCC88018C
	UINT32                                                   reserved11;	//0xCC880190
	UINT32                                                   reserved12;	//0xCC880194
	UINT32                                                   reserved13;	//0xCC880198
	UINT32                                                   reserved14;	//0xCC88019C
	REG_DNE_MON_INFO_STAMP0_PRES_PIC_INIT_T   info_stamp0_pres_pic_init;	//0xCC8801A0
	REG_DNE_MON_INFO_STAMP0_PRES_PIC_START_T info_stamp0_pres_pic_start;	//0xCC8801A4
	REG_DNE_MON_INFO_STAMP0_PRES_PIC_END_T     info_stamp0_pres_pic_end;	//0xCC8801A8
	REG_DNE_MON_INFO_STAMP0_PREV_PIC_INIT_T   info_stamp0_prev_pic_init;	//0xCC8801AC
	REG_DNE_MON_INFO_STAMP0_PREV_PIC_START_T info_stamp0_prev_pic_start;	//0xCC8801B0
	REG_DNE_MON_INFO_STAMP0_PREV_PIC_END_T     info_stamp0_prev_pic_end;	//0xCC8801B4
	REG_DNE_MON_INFO_STAMP1_PRES_PIC_INIT_T   info_stamp1_pres_pic_init;	//0xCC8801B8
	REG_DNE_MON_INFO_STAMP1_PRES_PIC_START_T info_stamp1_pres_pic_start;	//0xCC8801BC
	REG_DNE_MON_INFO_STAMP1_PRES_PIC_END_T     info_stamp1_pres_pic_end;	//0xCC8801C0
	REG_DNE_MON_INFO_STAMP1_PREV_PIC_INIT_T   info_stamp1_prev_pic_init;	//0xCC8801C4
	REG_DNE_MON_INFO_STAMP1_PREV_PIC_START_T info_stamp1_prev_pic_start;	//0xCC8801C8
	REG_DNE_MON_INFO_STAMP1_PREV_PIC_END_T     info_stamp1_prev_pic_end;	//0xCC8801CC
	REG_DNE_MON_INFO_STAMP2_PRES_PIC_INIT_T   info_stamp2_pres_pic_init;	//0xCC8801D0
	REG_DNE_MON_INFO_STAMP2_PRES_PIC_START_T info_stamp2_pres_pic_start;	//0xCC8801D4
	REG_DNE_MON_INFO_STAMP2_PRES_PIC_END_T     info_stamp2_pres_pic_end;	//0xCC8801D8
	REG_DNE_MON_INFO_STAMP2_PREV_PIC_INIT_T   info_stamp2_prev_pic_init;	//0xCC8801DC
	REG_DNE_MON_INFO_STAMP2_PREV_PIC_START_T info_stamp2_prev_pic_start;	//0xCC8801E0
	REG_DNE_MON_INFO_STAMP2_PREV_PIC_END_T     info_stamp2_prev_pic_end;	//0xCC8801E4
	REG_DNE_MON_INFO_STAMP_PRES_SRC_SYNC_T     info_stamp_pres_src_sync;	//0xCC8801E8
	REG_DNE_MON_INFO_STAMP_PREV_SRC_SYNC_T     info_stamp_prev_src_sync;	//0xCC8801EC
	REG_DNE_MON_INFO_STAMP_PRES_DISP_SYNC_T   info_stamp_pres_disp_sync;	//0xCC8801F0
	REG_DNE_MON_INFO_STAMP_PREV_DISP_SYNC_T   info_stamp_prev_disp_sync;	//0xCC8801F4
	REG_DNE_MON_INFO_STATUS_MON_CLOCKS_T         info_status_mon_clocks;	//0xCC8801F8
	REG_DNE_MON_INFO_STATUS_MON_APB_T               info_status_mon_apb;	//0xCC8801FC
}REG_DNE_MON_T;

extern volatile REG_DNE_MON_T*                     gpREG_DNE_MON;

#endif
