#ifndef _REG_DNE_CTRL_h
#define _REG_DNE_CTRL_h
//Header File for DNE_CTRL in \PQE\O22-A0_PQE_TopCTRL_reg_man.xls

#define REG_DNE_CTRL_PIC_INIT                                              (APB_DNE_CTRL_BASE+0x0000)
#define REG_DNE_CTRL_PIC_START                                             (APB_DNE_CTRL_BASE+0x0004)
#define REG_DNE_CTRL_CTRL_AUTO_INIT                                        (APB_DNE_CTRL_BASE+0x0008)
#define REG_DNE_CTRL_CTRL_INTR_PULSE                                       (APB_DNE_CTRL_BASE+0x000C)
#define REG_DNE_CTRL_INTR_REG                                              (APB_DNE_CTRL_BASE+0x0010)
#define REG_DNE_CTRL_INTR_MASK                                             (APB_DNE_CTRL_BASE+0x0014)
#define REG_DNE_CTRL_INTR_MUX                                              (APB_DNE_CTRL_BASE+0x0018)
#define REG_DNE_CTRL_INTR_EN                                               (APB_DNE_CTRL_BASE+0x001C)
#define REG_DNE_CTRL_CTRL_BLOCK2                                           (APB_DNE_CTRL_BASE+0x0080)
#define REG_DNE_CTRL_DNE1_CTRL_GMAU                                        (APB_DNE_CTRL_BASE+0x0084)
#define REG_DNE_CTRL_DNE0_CTRL_GMAU_BCH_ST                                 (APB_DNE_CTRL_BASE+0x0090)
#define REG_DNE_CTRL_DNE1_CTRL_GMAU_BCH_ST                                 (APB_DNE_CTRL_BASE+0x0094)
#define REG_DNE_CTRL_DNE0_CTRL_STATUS_GMAU_BCH_ST                          (APB_DNE_CTRL_BASE+0x0098)
#define REG_DNE_CTRL_DNE1_CTRL_STATUS_GMAU_BCH_ST                          (APB_DNE_CTRL_BASE+0x009C)
#define REG_DNE_CTRL_DNE0_CTRL_BLOCK                                       (APB_DNE_CTRL_BASE+0x00A0)
#define REG_DNE_CTRL_DNE0_CTRL_BLOCK1                                      (APB_DNE_CTRL_BASE+0x00A4)
#define REG_DNE_CTRL_DNE0_CTRL_CG_ON                                       (APB_DNE_CTRL_BASE+0x00A8)
#define REG_DNE_CTRL_DNE0_AXI_USER_DNE                                     (APB_DNE_CTRL_BASE+0x00AC)
#define REG_DNE_CTRL_DNE1_CTRL_BLOCK                                       (APB_DNE_CTRL_BASE+0x00B0)
#define REG_DNE_CTRL_DNE1_CTRL_BLOCK1                                      (APB_DNE_CTRL_BASE+0x00B4)
#define REG_DNE_CTRL_DNE1_CTRL_CG_ON                                       (APB_DNE_CTRL_BASE+0x00B8)
#define REG_DNE_CTRL_DNE1_AXI_USER_DNE                                     (APB_DNE_CTRL_BASE+0x00BC)
#define REG_DNE_CTRL_PIC_INIT_G0_TIMER                                     (APB_DNE_CTRL_BASE+0x00C0)
#define REG_DNE_CTRL_PIC_INIT_G1_TIMER                                     (APB_DNE_CTRL_BASE+0x00C4)
#define REG_DNE_CTRL_PIC_INIT_G2_TIMER                                     (APB_DNE_CTRL_BASE+0x00C8)
#define REG_DNE_CTRL_PIC_INIT_G3_TIMER                                     (APB_DNE_CTRL_BASE+0x00CC)
#define REG_DNE_CTRL_PIC_INIT_G4_TIMER                                     (APB_DNE_CTRL_BASE+0x00D0)
#define REG_DNE_CTRL_PIC_INIT_G5_TIMER                                     (APB_DNE_CTRL_BASE+0x00D4)
#define REG_DNE_CTRL_PIC_INIT_G6_TIMER                                     (APB_DNE_CTRL_BASE+0x00D8)
#define REG_DNE_CTRL_PIC_INIT_G7_TIMER                                     (APB_DNE_CTRL_BASE+0x00DC)
#define REG_DNE_CTRL_INFO_IX_INTR_PULSE                                    (APB_DNE_CTRL_BASE+0x00E0)
#define REG_DNE_CTRL_DBG_TIMER_RUN                                         (APB_DNE_CTRL_BASE+0x00E4)
#define REG_DNE_CTRL_GX_PIC_START_END_PROC                                 (APB_DNE_CTRL_BASE+0x00E8)
#define REG_DNE_CTRL_CTRL_MONITOR                                          (APB_DNE_CTRL_BASE+0x00EC)
#define REG_DNE_CTRL_CTRL_PIC_END                                          (APB_DNE_CTRL_BASE+0x00F0)
#define REG_DNE_CTRL_INFO_PIC_END                                          (APB_DNE_CTRL_BASE+0x00F4)
#define REG_DNE_CTRL_CTRL_GPIO                                             (APB_DNE_CTRL_BASE+0x00F8)
#define REG_DNE_CTRL_CTRL_GMAU                                             (APB_DNE_CTRL_BASE+0x00FC)

typedef union {
	UINT32 udata32;
	struct {						//0xCC880000 RW 0x0000_0000
	UINT32 g0_pic_init                      :1;	//(0,RW,0x00) //[FW PIC_INIT] DNE0 (1 core(1st) or 2 core serial)
	UINT32 g1_pic_init                      :1;	//(1,RW,0x00) //[FW PIC_INIT] DNE0 BCH
	UINT32 g2_pic_init                      :1;	//(2,RW,0x00) //[DEBUG][FW PIC_INIT] DNE0 gMAU BCH ST
	UINT32 g3_pic_init                      :1;	//(3,RW,0x00) //[NOT AVAILABLE][FW PIC_INIT]
	UINT32 g4_pic_init                      :1;	//(4,RW,0x00) //[FW PIC_INIT] DNE1 (1 core(2nd) or 2 core serial(?))
	UINT32 g5_pic_init                      :1;	//(5,RW,0x00) //[FW PIC_INIT] DNE1 BCH
	UINT32 g6_pic_init                      :1;	//(6,RW,0x00) //[DEBUG][FW PIC_INIT] DNE1 gMAU BCH ST
	UINT32 g7_pic_init                      :1;	//(7,RW,0x00) //[NOT AVAILABLE][FW PIC_INIT]
	UINT32 resvd                            :8;
	UINT32 g0_auto_init                     :1;	//(16,RW,0x00) //[AUTO PIC_INIT] DNE0 (1 core(1st) or 2 core serial)
	UINT32 g1_auto_init                     :1;	//(17,RW,0x00) //[AUTO PIC_INIT] DNE0 BCH
	UINT32 g2_auto_init                     :1;	//(18,RW,0x00) //[DEBUG][AUTO PIC_INIT] DNE0 gMAU BCH ST
	UINT32 g3_auto_init                     :1;	//(19,RW,0x00) //[NOT AVAILABLE][AUTO PIC_INIT]
	UINT32 g4_auto_init                     :1;	//(20,RW,0x00) //[AUTO PIC_INIT] DNE1 (1 core(2nd) or 2 core serial(?))
	UINT32 g5_auto_init                     :1;	//(21,RW,0x00) //[AUTO PIC_INIT] DNE1 BCH
	UINT32 g6_auto_init                     :1;	//(22,RW,0x00) //[DEBUG][AUTO PIC_INIT] DNE1 gMAU BCH ST
	UINT32 g7_auto_init                     :1;	//(23,RW,0x00) //[NOT AVAILABLE][AUTO PIC_INIT]
	UINT32 g0_pic_init_mask                 :1;	//(24,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g1_pic_init_mask                 :1;	//(25,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g2_pic_init_mask                 :1;	//(26,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g3_pic_init_mask                 :1;	//(27,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g4_pic_init_mask                 :1;	//(28,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g5_pic_init_mask                 :1;	//(29,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g6_pic_init_mask                 :1;	//(30,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	UINT32 g7_pic_init_mask                 :1;	//(31,RW,0x00) //[DEBUG][FW PIC_INIT MASK]
	};
}REG_DNE_CTRL_PIC_INIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880004 RW 0x0000_0000
	UINT32 g0_pic_start                     :1;	//(0,RW,0x00) //[FW PIC_START] DNE0 (1 core(1st) or 2 core serial)
	UINT32 g1_pic_start                     :1;	//(1,RW,0x00) //[FW PIC_START] DNE0 BCH
	UINT32 g2_pic_start                     :1;	//(2,RW,0x00) //[DEBUG][FW PIC_START] DNE0 gMAU BCH ST
	UINT32 g3_pic_start                     :1;	//(3,RW,0x00) //[NOT AVAILABLE][FW PIC_START]
	UINT32 g4_pic_start                     :1;	//(4,RW,0x00) //[FW PIC_START] DNE1 (1 core(2nd) or 2 core serial(?))
	UINT32 g5_pic_start                     :1;	//(5,RW,0x00) //[FW PIC_START] DNE1 BCH
	UINT32 g6_pic_start                     :1;	//(6,RW,0x00) //[DEBUG][FW PIC_START] DNE1 gMAU BCH ST
	UINT32 g7_pic_start                     :1;	//(7,RW,0x00) //[NOT AVAILABLE][FW PIC_START]
	UINT32 resvd                            :8;
	UINT32 g0_auto_half_en                  :1;	//(16,RW,0x00) //[AUTO_PIC_INIT HALF EN] DNE0 (1 core(1st) or 2 core serial)
	UINT32 g1_auto_half_en                  :1;	//(17,RW,0x00) //[AUTO_PIC_INIT HALF EN] DNE0 BCH
	UINT32 g2_auto_half_en                  :1;	//(18,RW,0x00) //[DEBUG][AUTO_PIC_INIT HALF EN] DNE0 gMAU BCH ST
	UINT32 g3_auto_half_en                  :1;	//(19,RW,0x00) //[NOT AVAILABLE][AUTO_PIC_INIT HALF EN]
	UINT32 g4_auto_half_en                  :1;	//(20,RW,0x00) //[AUTO_PIC_INIT HALF EN] DNE1 (1 core(2nd) or 2 core serial(?))
	UINT32 g5_auto_half_en                  :1;	//(21,RW,0x00) //[AUTO_PIC_INIT HALF EN] DNE1 BCH
	UINT32 g6_auto_half_en                  :1;	//(22,RW,0x00) //[DEBUG][AUTO_PIC_INIT HALF EN] DNE1 gMAU BCH ST
	UINT32 g7_auto_half_en                  :1;	//(23,RW,0x00) //[NOT AVAILABLE][AUTO_PIC_INIT HALF EN]
	UINT32 g0_pic_start_mask                :1;	//(24,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g1_pic_start_mask                :1;	//(25,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g2_pic_start_mask                :1;	//(26,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g3_pic_start_mask                :1;	//(27,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g4_pic_start_mask                :1;	//(28,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g5_pic_start_mask                :1;	//(29,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g6_pic_start_mask                :1;	//(30,RW,0x00) //[DEBUG][FW PIC_START MASK]
	UINT32 g7_pic_start_mask                :1;	//(31,RW,0x00) //[DEBUG][FW PIC_START MASK]
	};
}REG_DNE_CTRL_PIC_START_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880008 RW 0x7644_2200
	UINT32 idx_src_g0_auto_init             :3;	//(2:0,RW,0x00) //Source Selection of G0_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd0                           :1;
	UINT32 idx_src_g1_auto_init             :3;	//(6:4,RW,0x00) //Source Selection of G1_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd1                           :1;
	UINT32 idx_src_g2_auto_init             :3;	//(10:8,RW,0x02) //Source Selection of G2_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd2                           :1;
	UINT32 idx_src_g3_auto_init             :3;	//(14:12,RW,0x02) //Source Selection of G3_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd3                           :1;
	UINT32 idx_src_g4_auto_init             :3;	//(18:16,RW,0x04) //Source Selection of G4_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd4                           :1;
	UINT32 idx_src_g5_auto_init             :3;	//(22:20,RW,0x04) //Source Selection of G5_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd5                           :1;
	UINT32 idx_src_g6_auto_init             :3;	//(26:24,RW,0x06) //Source Selection of G6_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd6                           :1;
	UINT32 idx_src_g7_auto_init             :3;	//(30:28,RW,0x07) //Source Selection of G7_AUTO_INIT	 "000" := i0_intr_pulse	 "001"  = i1_intr_pulse	 "010"  = i2_intr_pulse	 "011"  = i3_intr_pulse	 "100"  = i4_intr_pulse	 "101"  = i5_intr_pulse	 "110"  = i6_intr_pulse	 "111"  = i7_intr_pulse
	UINT32 resvd7                           :1;
	};
}REG_DNE_CTRL_CTRL_AUTO_INIT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88000C RW 0xCA87_6420
	UINT32 idx_src_i0_intr_pulse            :3;	//(2:0,RW,0x00) //Source Selection of INTR_I0_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i0_intr_pulse            :1;	//(3,RW,0x00) //Source Selection of INTR_I0_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i1_intr_pulse            :3;	//(6:4,RW,0x02) //Source Selection of INTR_I1_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i1_intr_pulse            :1;	//(7,RW,0x00) //Source Selection of INTR_I1_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i2_intr_pulse            :3;	//(10:8,RW,0x04) //Source Selection of INTR_I2_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i2_intr_pulse            :1;	//(11,RW,0x00) //Source Selection of INTR_I2_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i3_intr_pulse            :3;	//(14:12,RW,0x06) //Source Selection of INTR_I3_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i3_intr_pulse            :1;	//(15,RW,0x00) //Source Selection of INTR_I3_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i4_intr_pulse            :3;	//(18:16,RW,0x07) //Source Selection of INTR_I4_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i4_intr_pulse            :1;	//(19,RW,0x00) //Source Selection of INTR_I4_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i5_intr_pulse            :3;	//(22:20,RW,0x00) //Source Selection of INTR_I5_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i5_intr_pulse            :1;	//(23,RW,0x01) //Source Selection of INTR_I5_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i6_intr_pulse            :3;	//(26:24,RW,0x02) //Source Selection of INTR_I6_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i6_intr_pulse            :1;	//(27,RW,0x01) //Source Selection of INTR_I6_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	UINT32 idx_src_i7_intr_pulse            :3;	//(30:28,RW,0x04) //Source Selection of INTR_I7_INTR_PULSE	 "000" := s0_src_pulse / mv_disp_pulse0	 "001"  = s1_src_pulse / mv_disp_pulse1	 "010"  = s2_src_pulse / so_disp_pulse0	 "011"  = s3_src_pulse / so_disp_pulse1	 "100"  = s4_src_pulse / sb_disp_pulse0	 "101"  = s5_src_pulse / sb_disp_pulse1	 "110"  = s6_src_pulse / NA	 "111"  = s7_src_pulse / NA
	UINT32 sel_src_i7_intr_pulse            :1;	//(31,RW,0x01) //Source Selection of INTR_I7_INTR_PULSE	 '0' := GROUP OF SRC  PULSE	 '1'  = GROUP OF DISP PULSE
	};
}REG_DNE_CTRL_CTRL_INTR_PULSE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880010 RW 0x0000_0000
	UINT32 intr_i0_intr_pulse               :1;	//(0,RW,0x00) //[SRC_PULSE] s0_src_pulse
	UINT32 intr_i1_intr_pulse               :1;	//(1,RW,0x00) //[SRC_PULSE] s2_src_pulse
	UINT32 intr_i2_intr_pulse               :1;	//(2,RW,0x00) //[SRC_PULSE] s4_src_pulse
	UINT32 intr_i3_intr_pulse               :1;	//(3,RW,0x00) //[SRC_PULSE] s6_src_pulse
	UINT32 intr_i4_intr_pulse               :1;	//(4,RW,0x00) //[SRC_PULSE] s7_src_pulse
	UINT32 intr_i5_intr_pulse               :1;	//(5,RW,0x00) //[SRC_PULSE] DISP_VA_FAL
	UINT32 intr_i6_intr_pulse               :1;	//(6,RW,0x00) //[SRC_PULSE] DISP_VA_FAL
	UINT32 intr_i7_intr_pulse               :1;	//(7,RW,0x00) //[SRC_PULSE] SOSD_VA_FAL
	UINT32 intr_g0_pic_end                  :1;	//(8,RW,0x00) //[FRAME_END] DNE0 (1 core(1st) or 2 core serial)
	UINT32 intr_g1_pic_end                  :1;	//(9,RW,0x00) //[FRAME_END]
	UINT32 intr_g2_pic_end                  :1;	//(10,RW,0x00) //[FRAME_END]
	UINT32 intr_g3_pic_end                  :1;	//(11,RW,0x00) //[FRAME_END]
	UINT32 intr_g4_pic_end                  :1;	//(12,RW,0x00) //[FRAME_END] DNE1 (1 core(2nd) or 2 core serial(?))
	UINT32 intr_g5_pic_end                  :1;	//(13,RW,0x00) //[FRAME_END]
	UINT32 intr_g6_pic_end                  :1;	//(14,RW,0x00) //[FRAME_END]
	UINT32 intr_g7_pic_end                  :1;	//(15,RW,0x00) //[FRAME_END]
	UINT32 intr_dne0_mif                    :1;	//(16,RW,0x00) //[MIF] DNE0 MIF
	UINT32 intr_dne1_mif                    :1;	//(17,RW,0x00) //[MIF] DNE1 MIF
	UINT32 intr_dne_mif_rd_fail_wgt0        :1;	//(18,RW,0x00) //[MIF] DNE MIF RD Fail Wgt0 ( DNE0 vs. DNE1 : CTRL_BLOCK[5] )
	UINT32 intr_dne_mif_rd_fail_wgt1        :1;	//(19,RW,0x00) //[MIF] DNE MIF RD Fail Wgt1
	UINT32 intr_dne_mif_rd_fail_ft0         :1;	//(20,RW,0x00) //[MIF] DNE MIF RD Fail Ft0
	UINT32 intr_dne_mif_rd_fail_ft1         :1;	//(21,RW,0x00) //[MIF] DNE MIF RD Fail Ft1
	UINT32 intr_dne_mif_rd_fail_ft2         :1;	//(22,RW,0x00) //[MIF] DNE MIF RD Fail Ft2
	UINT32 intr_dne_mif_rd_fail_prg         :1;	//(23,RW,0x00) //[MIF] DNE MIF RD Fail Prg
	UINT32 intr_dne_mif_wd_fail_ft0         :1;	//(24,RW,0x00) //[MIF] DNE MIF WD Fail Ft0
	UINT32 intr_dne_mif_wd_fail_ft1         :1;	//(25,RW,0x00) //[MIF] DNE MIF WD Fail Ft1
	UINT32 resvd                            :1;
	UINT32 intr_dne_err_oftr_infi           :1;	//(27,RW,0x00) //[CORE] DNE Output Feautre Infinity Error
	UINT32 intr_dne_err_iftr1_infi          :1;	//(28,RW,0x00) //[CORE] DNE Input Feautre 1 Infinity Error
	UINT32 intr_dne_err_iftr0_infi          :1;	//(29,RW,0x00) //[CORE] DNE Input Feautre 0 Infinity Error
	UINT32 intr_dne0_pslverr                :1;	//(30,RW,0x00) //DNE0 pslverr
	UINT32 intr_dne1_pslverr                :1;	//(31,RW,0x00) //DNE1 pslverr
	};
}REG_DNE_CTRL_INTR_REG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880014 RW 0xFFFF_FFFF
	UINT32 mask_i0_src_pulse                :1;	//(0,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i1_src_pulse                :1;	//(1,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i2_src_pulse                :1;	//(2,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i3_src_pulse                :1;	//(3,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i4_src_pulse                :1;	//(4,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i5_src_pulse                :1;	//(5,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i6_src_pulse                :1;	//(6,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_i7_src_pulse                :1;	//(7,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g0_pic_end                  :1;	//(8,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g1_pic_end                  :1;	//(9,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g2_pic_end                  :1;	//(10,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g3_pic_end                  :1;	//(11,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g4_pic_end                  :1;	//(12,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g5_pic_end                  :1;	//(13,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g6_pic_end                  :1;	//(14,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_g7_pic_end                  :1;	//(15,RW,0x01) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne0_mif                    :1;	//(16,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne1_mif                    :1;	//(17,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_mif_rd_fail_wgt0        :1;	//(18,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_mif_rd_fail_wgt1        :1;	//(19,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_mif_rd_fail_ft0         :1;	//(20,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_mif_rd_fail_ft1         :1;	//(21,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_mif_rd_fail_ft2         :1;	//(22,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_mif_rd_fail_prg         :1;	//(23,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_mif_wd_fail_ft0         :1;	//(24,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_mif_wd_fail_ft1         :1;	//(25,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 resvd                            :1;
	UINT32 mask_dne_err_oftr_infi           :1;	//(27,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_err_iftr1_infi          :1;	//(28,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne_err_iftr0_infi          :1;	//(29,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne0_pslverr                :1;	//(30,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	UINT32 mask_dne1_pslverr                :1;	//(31,RW,0x00) //interrupt mask	0  = unmask	1 := mask
	};
}REG_DNE_CTRL_INTR_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880018 RW 0x0000_0000
	UINT32 mux_i0_src_pulse                 :1;	//(0,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i1_src_pulse                 :1;	//(1,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i2_src_pulse                 :1;	//(2,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i3_src_pulse                 :1;	//(3,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i4_src_pulse                 :1;	//(4,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i5_src_pulse                 :1;	//(5,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i6_src_pulse                 :1;	//(6,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_i7_src_pulse                 :1;	//(7,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g0_pic_end                   :1;	//(8,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g1_pic_end                   :1;	//(9,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g2_pic_end                   :1;	//(10,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g3_pic_end                   :1;	//(11,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g4_pic_end                   :1;	//(12,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g5_pic_end                   :1;	//(13,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g6_pic_end                   :1;	//(14,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_g7_pic_end                   :1;	//(15,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne0_mif                     :1;	//(16,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne1_mif                     :1;	//(17,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_mif_rd_fail_wgt0         :1;	//(18,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_mif_rd_fail_wgt1         :1;	//(19,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_mif_rd_fail_ft0          :1;	//(20,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_mif_rd_fail_ft1          :1;	//(21,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_mif_rd_fail_ft2          :1;	//(22,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_mif_rd_fail_prg          :1;	//(23,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_mif_wd_fail_ft0          :1;	//(24,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_mif_wd_fail_ft1          :1;	//(25,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 resvd                            :1;
	UINT32 mux_dne_err_oftr_infi            :1;	//(27,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_err_iftr1_infi           :1;	//(28,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne_err_iftr0_infi           :1;	//(29,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne0_pslverr                 :1;	//(30,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	UINT32 mux_dne1_pslverr                 :1;	//(31,RW,0x00) //interrupt mux	0 := send interrupt to MCU	1  = send interrupt to CPU
	};
}REG_DNE_CTRL_INTR_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88001C RW 0xFFFF_FFFF
	UINT32 en_i0_src_pulse                  :1;	//(0,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i1_src_pulse                  :1;	//(1,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i2_src_pulse                  :1;	//(2,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i3_src_pulse                  :1;	//(3,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i4_src_pulse                  :1;	//(4,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i5_src_pulse                  :1;	//(5,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i6_src_pulse                  :1;	//(6,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_i7_src_pulse                  :1;	//(7,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g0_pic_end                    :1;	//(8,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g1_pic_end                    :1;	//(9,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g2_pic_end                    :1;	//(10,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g3_pic_end                    :1;	//(11,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g4_pic_end                    :1;	//(12,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g5_pic_end                    :1;	//(13,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g6_pic_end                    :1;	//(14,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_g7_pic_end                    :1;	//(15,RW,0x01) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne0_mif                      :1;	//(16,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne1_mif                      :1;	//(17,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_mif_rd_fail_wgt0          :1;	//(18,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_mif_rd_fail_wgt1          :1;	//(19,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_mif_rd_fail_ft0           :1;	//(20,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_mif_rd_fail_ft1           :1;	//(21,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_mif_rd_fail_ft2           :1;	//(22,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_mif_rd_fail_prg           :1;	//(23,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_mif_wd_fail_ft0           :1;	//(24,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_mif_wd_fail_ft1           :1;	//(25,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 resvd                            :1;
	UINT32 en_dne_err_oftr_infi             :1;	//(27,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_err_iftr1_infi            :1;	//(28,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne_err_iftr0_infi            :1;	//(29,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne0_pslverr                  :1;	//(30,RW,0x00) //interrupt enable	0  = disable	1 := enable
	UINT32 en_dne1_pslverr                  :1;	//(31,RW,0x00) //interrupt enable	0  = disable	1 := enable
	};
}REG_DNE_CTRL_INTR_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880080 RW 0x0000_0000
	UINT32 dne_vsd_mon_sync_level_sel       :1;	//(0,RW,0x00) //0 : DNE0, 1 : DNE1
	UINT32 timer_reset_src_disp_sel         :1;	//(1,RW,0x00) //ime_den_src/vsd_dne_disp_sync_level ( 0 : DNE0, 1 : DNE1 )
	UINT32 resvd0                           :2;
	UINT32 g_pic_end_info_sel               :1;	//(4,RW,0x00) //0 : DNE0(G0), 1 : DNE1(G4)
	UINT32 mif_fail_sel                     :1;	//(5,RW,0x00) //0 : DNE0, 1 : DNE1
	UINT32 resvd1                           :2;
	UINT32 g0_b_pic_end_en                  :8;	//(15:8,RW,0x00) //DNE0 b0~b7_pic_end ( 0 : b0~b7_pic_end_en, 1 : 8'b0 )
	UINT32 g4_b_pic_end_en                  :8;	//(23:16,RW,0x00) //DNE1 b0~b7_pic_end ( 0 : b0~b7_pic_end_en, 1 : 8'b0 )
	UINT32 resvd2                           :8;
	};
}REG_DNE_CTRL_CTRL_BLOCK2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880084 RW 0x0000_0000
	UINT32 ask_cmd_dly_cnt_r0               :4;	//(3:0,RW,0x00) //REG_SEL_MIF_CMD_DLY == '0' 일 때, 사용됨. 16배로 적용됨.
	UINT32 ask_cmd_dly_cnt_w0               :4;	//(7:4,RW,0x00) //REG_SEL_MIF_CMD_DLY == '0' 일 때, 사용됨. 16배로 적용됨.
	UINT32 resvd0                           :8;
	UINT32 ask_to_cnt                       :8;	//(23:16,RW,0x0) //x4되어서 적용됨.
	UINT32 resvd1                           :8;
	};
}REG_DNE_CTRL_DNE1_CTRL_GMAU_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880090 RW 0x0000_0000
	UINT32 reg_ctrl_gmau_bch_st             :32;	//(31:0,RW,0x00) //
	};
}REG_DNE_CTRL_DNE0_CTRL_GMAU_BCH_ST_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880094 RW 0x0000_0000
	UINT32 reg_ctrl_gmau_bch_st             :32;	//(31:0,RW,0x00) //
	};
}REG_DNE_CTRL_DNE1_CTRL_GMAU_BCH_ST_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880098 RO 0x0000_0000
	UINT32 reg_status_gmau_bch_st           :32;	//(31:0,RO,0x00) //
	};
}REG_DNE_CTRL_DNE0_CTRL_STATUS_GMAU_BCH_ST_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88009C RO 0x0000_0000
	UINT32 reg_status_gmau_bch_st           :32;	//(31:0,RO,0x00) //
	};
}REG_DNE_CTRL_DNE1_CTRL_STATUS_GMAU_BCH_ST_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800A0 RW 0x0220_3393
	UINT32 reg_path_reset_en_m1_y           :1;	//(0,RW,0x01) //[NA] AUTO RESET ENABLE FOR ASYNC_BRIDGE ON M0_Y	 '0' := DISABLE	 '1'  = RESET BY PIC_INIT
	UINT32 reg_path_reset_en_m1_c           :1;	//(1,RW,0x01) //[NA] AUTO RESET ENABLE FOR ASYNC_BRIDGE ON M0_C	 '0' := DISABLE	 '1'  = RESET BY PIC_INIT
	UINT32 reg_sel_mif_cmd_dly              :1;	//(2,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 dne_master_select                :1;	//(4,RW,0x01) //0 = reg updated by update signal disable 1 := reg written by mcu/HW
	UINT32 dne_reg_update_force_r           :1;	//(5,RW,0x00) //0 = read only reg update off 1 := read only reg update always on
	UINT32 dne_reg_update_force_w           :1;	//(6,RW,0x00) //0 = write reg update off 1 := write reg update always on
	UINT32 dne_reg_update_flag_r            :1;	//(7,RW,0x01) //0 = read only reg update off 1 := read only reg update on w/ pic_end
	UINT32 dne_reg_update_flag_w            :1;	//(8,RW,0x01) //0 = write reg update off 1 := write reg update on w/ pic_init
	UINT32 reg_update_ctrl_seg              :5;	//(13:9,RW,0x19) //DO NOT CARE
	UINT32 reg_sel_timer_reset_src          :3;	//(16:14,RW,0x00) //
	UINT32 reg_sel_timer_reset_disp         :3;	//(19:17,RW,0x00) //
	UINT32 resvd1                           :8;
	UINT32 reg_sel_mif_axuser               :4;	//(31:28,RW,0x00) //[NA] [3] DNE1 AWUSER	0 := MANUAL AWUSER w/ CTRL_BLOCK	1  = USE MIF AWUSER	[NA] [2] DNE1 ARUSER	0 := MANUAL ARUSER w/ CTRL_BLOCK	1  = USE MIF ARUSER	[1] DNE AWUSER	0 := MANUAL AWUSER w/ CTRL_BLOCK	1  = USE MIF AWUSER	[0] DNE ARUSER	0 := MANUAL ARUSER w/ CTRL_BLOCK	1  = USE MIF ARUSER
	};
}REG_DNE_CTRL_DNE0_CTRL_BLOCK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800A4 RW 0x0000_0000
	UINT32 reg_dne_mif_bd_ft0_done_mask     :4;	//(3:0,RW,0x00) //0 = dne_mif_bd_ft0_done_mask off	others = dne_mif_bd_ft0_done_mask on by dne_pic_init	[0] : dne_mif_bd_ft0_done_mask off by dne_pic_start	[1] : dne_mif_bd_ft0_done_mask off by dne_wd_ft0_ack	[2] : dne_mif_bd_ft0_done_mask off by dne_wd_ft0_done
	UINT32 reg_dne_mif_bd_ft1_done_mask     :4;	//(7:4,RW,0x00) //0 = dne_mif_bd_ft1_done_mask off	others = dne_mif_bd_ft1_done_mask on by dne_pic_init	[0] : dne_mif_bd_ft1_done_mask off by dne_pic_start	[1] : dne_mif_bd_ft1_done_mask off by dne_wd_ft1_ack	[2] : dne_mif_bd_ft1_done_mask off by dne_wd_ft1_done
	UINT32 resvd                            :24;
	};
}REG_DNE_CTRL_DNE0_CTRL_BLOCK1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800A8 RW 0x0000_0000
	UINT32 reg_dne_dne_clk_cg               :1;	//(0,RW,0x00) //DNE DNE Clock Gating ON	0 := Off	1 := On
	UINT32 reg_dne_tlt_clk_cg               :1;	//(1,RW,0x00) //DNE TLT DNE Clock Gating ON	0 := Off	1 := On
	UINT32 reg_dne_dw_clk_cg                :1;	//(2,RW,0x00) //DNE DW DNE Clock Gating ON	0 := Off	1 := On
	UINT32 resvd                            :29;
	};
}REG_DNE_CTRL_DNE0_CTRL_CG_ON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800AC RW 0x0000_2222
	UINT32 dne_aruser                       :4;	//(3:0,RW,0x02) //user [3]   : Urgency, PQE block priority[3]	user [2]   : Real Time	user [1:0] : PQE block priority[2:1]
	UINT32 dne_awuser                       :4;	//(7:4,RW,0x02) //user [3]   : Urgency, PQE block priority[3]	user [2]   : Real Time	user [1:0] : PQE block priority[2:1]
	UINT32 resvd                            :24;
	};
}REG_DNE_CTRL_DNE0_AXI_USER_DNE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800B0 RW 0x0220_3393
	UINT32 reg_path_reset_en_m1_y           :1;	//(0,RW,0x01) //[NA] AUTO RESET ENABLE FOR ASYNC_BRIDGE ON M0_Y	 '0' := DISABLE	 '1'  = RESET BY PIC_INIT
	UINT32 reg_path_reset_en_m1_c           :1;	//(1,RW,0x01) //[NA] AUTO RESET ENABLE FOR ASYNC_BRIDGE ON M0_C	 '0' := DISABLE	 '1'  = RESET BY PIC_INIT
	UINT32 reg_sel_mif_cmd_dly              :1;	//(2,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 dne_master_select                :1;	//(4,RW,0x01) //0 = reg updated by update signal disable 1 := reg written by mcu/HW
	UINT32 dne_reg_update_force_r           :1;	//(5,RW,0x00) //0 = read only reg update off 1 := read only reg update always on
	UINT32 dne_reg_update_force_w           :1;	//(6,RW,0x00) //0 = write reg update off 1 := write reg update always on
	UINT32 dne_reg_update_flag_r            :1;	//(7,RW,0x01) //0 = read only reg update off 1 := read only reg update on w/ pic_end
	UINT32 dne_reg_update_flag_w            :1;	//(8,RW,0x01) //0 = write reg update off 1 := write reg update on w/ pic_init
	UINT32 reg_update_ctrl_seg              :5;	//(13:9,RW,0x19) //DO NOT CARE
	UINT32 reg_sel_timer_reset_src          :3;	//(16:14,RW,0x00) //
	UINT32 reg_sel_timer_reset_disp         :3;	//(19:17,RW,0x00) //
	UINT32 resvd1                           :8;
	UINT32 reg_sel_mif_axuser               :4;	//(31:28,RW,0x00) //[NA] [3] DNE1 AWUSER	0 := MANUAL AWUSER w/ CTRL_BLOCK	1  = USE MIF AWUSER	[NA] [2] DNE1 ARUSER	0 := MANUAL ARUSER w/ CTRL_BLOCK	1  = USE MIF ARUSER	[1] DNE AWUSER	0 := MANUAL AWUSER w/ CTRL_BLOCK	1  = USE MIF AWUSER	[0] DNE ARUSER	0 := MANUAL ARUSER w/ CTRL_BLOCK	1  = USE MIF ARUSER
	};
}REG_DNE_CTRL_DNE1_CTRL_BLOCK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800B4 RW 0x0000_0000
	UINT32 reg_dne_mif_bd_ft0_done_mask     :4;	//(3:0,RW,0x00) //0 = dne_mif_bd_ft0_done_mask off	others = dne_mif_bd_ft0_done_mask on by dne_pic_init	[0] : dne_mif_bd_ft0_done_mask off by dne_pic_start	[1] : dne_mif_bd_ft0_done_mask off by dne_wd_ft0_ack	[2] : dne_mif_bd_ft0_done_mask off by dne_wd_ft0_done
	UINT32 reg_dne_mif_bd_ft1_done_mask     :4;	//(7:4,RW,0x00) //0 = dne_mif_bd_ft1_done_mask off	others = dne_mif_bd_ft1_done_mask on by dne_pic_init	[0] : dne_mif_bd_ft1_done_mask off by dne_pic_start	[1] : dne_mif_bd_ft1_done_mask off by dne_wd_ft1_ack	[2] : dne_mif_bd_ft1_done_mask off by dne_wd_ft1_done
	UINT32 resvd                            :24;
	};
}REG_DNE_CTRL_DNE1_CTRL_BLOCK1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800B8 RW 0x0000_0000
	UINT32 reg_dne_dne_clk_cg               :1;	//(0,RW,0x00) //DNE DNE Clock Gating ON	0 := Off	1 := On
	UINT32 reg_dne_tlt_clk_cg               :1;	//(1,RW,0x00) //DNE TLT DNE Clock Gating ON	0 := Off	1 := On
	UINT32 reg_dne_dw_clk_cg                :1;	//(2,RW,0x00) //DNE DW DNE Clock Gating ON	0 := Off	1 := On
	UINT32 resvd                            :29;
	};
}REG_DNE_CTRL_DNE1_CTRL_CG_ON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800BC RW 0x0000_2222
	UINT32 dne_aruser                       :4;	//(3:0,RW,0x02) //user [3]   : Urgency, PQE block priority[3]	user [2]   : Real Time	user [1:0] : PQE block priority[2:1]
	UINT32 dne_awuser                       :4;	//(7:4,RW,0x02) //user [3]   : Urgency, PQE block priority[3]	user [2]   : Real Time	user [1:0] : PQE block priority[2:1]
	UINT32 resvd                            :24;
	};
}REG_DNE_CTRL_DNE1_AXI_USER_DNE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800C0 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}REG_DNE_CTRL_PIC_INIT_G0_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800C4 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}REG_DNE_CTRL_PIC_INIT_G1_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800C8 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}REG_DNE_CTRL_PIC_INIT_G2_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800CC RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}REG_DNE_CTRL_PIC_INIT_G3_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800D0 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}REG_DNE_CTRL_PIC_INIT_G4_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800D4 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}REG_DNE_CTRL_PIC_INIT_G5_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800D8 RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}REG_DNE_CTRL_PIC_INIT_G6_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800DC RW 0x7000_0000
	UINT32 pic_init_timer                   :24;	//(23:0,RW,0x0000_0000) //지정된 count만큼 기다렸다가 pic_init신호를 내부 블록에 보낸다.
	UINT32 start_interval_mode_en           :1;	//(24,RW,0x00) //'1' := ENABLE	 '0'  = DISABLE
	UINT32 start_interval_mode              :3;	//(27:25,RW,0x00) //"000" :=    16	 "001"  =    64	 "010"  =   128	 "011"  =   256	 "100"  =  1024	 "101"  =  4096	 "110"  =  8192	 "111"  = GX_PIC_START_END_PROC
	UINT32 pic_init_width_mode_en           :1;	//(28,RW,0x01) //PIC_INIT의 WIDTH를 선택할 수 있는 Mode를 사용할지 말지를 선택함.	 '0' := DISABLE (1clk)	 '1'  = ENABLE
	UINT32 pic_init_width_mode              :2;	//(30:29,RW,0x03) //PIC_INIT의 WIDTH를 선택	 "00" := 2clk	 "01"  = 4clk	 "10"  = 8clk	 "11"  = 16clk
	UINT32 wait_pic_end_en                  :1;	//(31,RW,0x00) //PIC_END가 들어올 때까지 PIC_INIT/START를 출력하지 않고 기다리게 하는 모드	 '0' := DISABLE	 '1'  = ENABLE
	};
}REG_DNE_CTRL_PIC_INIT_G7_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800E0 RO 0x0000_0000
	UINT32 cnt_i0_intr_pulse                :4;	//(3:0,RO,0x00) //
	UINT32 cnt_i1_intr_pulse                :4;	//(7:4,RO,0x00) //
	UINT32 cnt_i2_intr_pulse                :4;	//(11:8,RO,0x00) //
	UINT32 cnt_i3_intr_pulse                :4;	//(15:12,RO,0x00) //
	UINT32 cnt_i4_intr_pulse                :4;	//(19:16,RO,0x00) //
	UINT32 cnt_i5_intr_pulse                :4;	//(23:20,RO,0x00) //
	UINT32 cnt_i6_intr_pulse                :4;	//(27:24,RO,0x00) //
	UINT32 cnt_i7_intr_pulse                :4;	//(31:28,RO,0x00) //
	};
}REG_DNE_CTRL_INFO_IX_INTR_PULSE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800E4 RW 0x0000_0000
	UINT32 info_timer_run                   :24;	//(23:0,RW,0x0000_0000) //Processing Timer 값 * 1024	60Hz frame = 1/60, clock = 396Mhz, 	frame clock 수 = 396M/60 = 6.6 M
	UINT32 idx_end_src                      :3;	//(26:24,RW,0x00) //0 := G0_PIC_END	 X  = GX_PIC_END
	UINT32 sel_end_src                      :1;	//(27,RW,0x00) //'0' := PIC_END_RIS	 '1'  = PIC_END_RIS & PIC_2ND
	UINT32 idx_start_src                    :3;	//(30:28,RW,0x00) //0 := G0_PIC_START/INIT	 X  = GX_PIC_START/INIT
	UINT32 sel_start_src                    :1;	//(31,RW,0x00) //'0' := PIC_START	 '1'  = PIC_INIT
	};
}REG_DNE_CTRL_DBG_TIMER_RUN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800E8 RW 0x0000_4000
	UINT32 rw_gx_pic_start_end              :1;	//(0:0,RW,0x0) //'0' := read	 '1'  = write
	UINT32 dly_gx_pic_start_end             :23;	//(23:1,RW,0x0000_2000) //idx_gx_pic_start_end = 0 ~ 7 이면	  dly_g0/~/g7_start = 0x2000 (0x4000/2)	idx_gx_pic_start_end = 8 ~ 15 이면	  dly_g0/~/g7_end_to = 0x00_192D ((396M/60*1)/1024)	idx_gx_pic_start_end = 16 ~ 23 이면	  dly_g0/~/g7_end_dly = 0x00_192D ((396M/60*1)/1024)
	UINT32 ctrl_gx_pic_start_end            :3;	//(26:24,RW,0x0) //idx_gx_pic_start_end = 0 ~ 7 이면	  ctrl_g0/~/g7_start ctrl[2:0]	idx_gx_pic_start_end = 8 ~ 15 이면	  ctrl_g0/~/g7_end[26] := pic end time out end pluse	  ctrl_g0/~/g7_end[25] := pic end time init sel '0' : master, '1' : delay init	  ctrl_g0/~/g7_end[24] := pic end time out en	idx_gx_pic_start_end = 16 ~ 23 이면	  ctrl_g0/~/g7_end[26] := pic end delay out end pluse	  ctrl_g0/~/g7_end[25] := pic end delay init sel '0' : master, '1' : delay init	  ctrl_g0/~/g7_end[24] := pic end delay en
	UINT32 idx_gx_pic_start_end             :5;	//(31:27,RW,0x0) //'0' ~ '7'  := g0_pic_start   ~ g7_pic_start	 '8' ~ '15' := g0_pic_end_to  ~ g7_pic_end_to	 '16'~ '23' := g0_pic_end_dly ~ g7_pic_end_dly
	};
}REG_DNE_CTRL_GX_PIC_START_END_PROC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800EC RW 0x0000_0000
	UINT32 ctrl_monitor                     :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_DNE_CTRL_CTRL_MONITOR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800F0 RW 0x0000_00FF
	UINT32 g0_pic_end_en                    :1;	//(0,RW,0x01) //[PIC END EN]G0_PIC_END_INTR를 ENABLE 하고 싶다.(DNE)
	UINT32 g1_pic_end_en                    :1;	//(1,RW,0x01) //[NOT AVAILABLE]
	UINT32 g2_pic_end_en                    :1;	//(2,RW,0x01) //[NOT AVAILABLE]
	UINT32 g3_pic_end_en                    :1;	//(3,RW,0x01) //[NOT AVAILABLE]
	UINT32 g4_pic_end_en                    :1;	//(4,RW,0x01) //[NOT AVAILABLE]
	UINT32 g5_pic_end_en                    :1;	//(5,RW,0x01) //[NOT AVAILABLE]
	UINT32 g6_pic_end_en                    :1;	//(6,RW,0x01) //[NOT AVAILABLE]
	UINT32 g7_pic_end_en                    :1;	//(7,RW,0x01) //[NOT AVAILABLE]
	UINT32 b0_pic_end_en                    :1;	//(8,RW,0x00) //[G0 PIC END] mif_dne_rd_wgt0_pic_end
	UINT32 b1_pic_end_en                    :1;	//(9,RW,0x00) //[G0 PIC END] mif_dne_rd_wgt1_pic_end
	UINT32 b2_pic_end_en                    :1;	//(10,RW,0x00) //[G0 PIC END] mif_dne_rd_ft0_pic_end
	UINT32 b3_pic_end_en                    :1;	//(11,RW,0x00) //[G0 PIC END] mif_dne_rd_ft1_pic_end
	UINT32 b4_pic_end_en                    :1;	//(12,RW,0x00) //[G0 PIC END] mif_dne_rd_ft2_pic_end
	UINT32 b5_pic_end_en                    :1;	//(13,RW,0x00) //[G0 PIC END] mif_dne_rd_prg_pic_end
	UINT32 b6_pic_end_en                    :1;	//(14,RW,0x00) //[G0 PIC END] mif_dne_rd_ft0_pic_end
	UINT32 b7_pic_end_en                    :1;	//(15,RW,0x00) //[G0 PIC END] mif_dne_wd_ft1_pic_end
	UINT32 pic_end_g0_force_en              :1;	//(16,RW,0x00) //
	UINT32 pic_end_g1_force_en              :1;	//(17,RW,0x00) //
	UINT32 pic_end_g2_force_en              :1;	//(18,RW,0x00) //
	UINT32 pic_end_g3_force_en              :1;	//(19,RW,0x00) //
	UINT32 pic_end_g4_force_en              :1;	//(20,RW,0x00) //
	UINT32 pic_end_g5_force_en              :1;	//(21,RW,0x00) //
	UINT32 pic_end_g6_force_en              :1;	//(22,RW,0x00) //
	UINT32 pic_end_g7_force_en              :1;	//(23,RW,0x00) //
	UINT32 pic_end_g0_force_value           :1;	//(24,RW,0x00) //
	UINT32 pic_end_g1_force_value           :1;	//(25,RW,0x00) //
	UINT32 pic_end_g2_force_value           :1;	//(26,RW,0x00) //
	UINT32 pic_end_g3_force_value           :1;	//(27,RW,0x00) //
	UINT32 pic_end_g4_force_value           :1;	//(28,RW,0x00) //
	UINT32 pic_end_g5_force_value           :1;	//(29,RW,0x00) //
	UINT32 pic_end_g6_force_value           :1;	//(30,RW,0x00) //
	UINT32 pic_end_g7_force_value           :1;	//(31,RW,0x00) //
	};
}REG_DNE_CTRL_CTRL_PIC_END_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800F4 RO 0x0000_0000
	UINT32 g0_pic_end                       :1;	//(0,RO,0x00) //[PIC END] DNE
	UINT32 g1_pic_end                       :1;	//(1,RO,0x00) //[NOT AVAILABLE]
	UINT32 g2_pic_end                       :1;	//(2,RO,0x00) //[NOT AVAILABLE]
	UINT32 g3_pic_end                       :1;	//(3,RO,0x00) //[NOT AVAILABLE]
	UINT32 g4_pic_end                       :1;	//(4,RO,0x00) //[NOT AVAILABLE]
	UINT32 g5_pic_end                       :1;	//(5,RO,0x00) //[NOT AVAILABLE]
	UINT32 g6_pic_end                       :1;	//(6,RO,0x00) //[NOT AVAILABLE]
	UINT32 g7_pic_end                       :1;	//(7,RO,0x00) //[NOT AVAILABLE]
	UINT32 b0_pic_end                       :1;	//(8,RO,0x00) //[G0 PIC END] mif_dne_rd_wgt0_pic_end
	UINT32 b1_pic_end                       :1;	//(9,RO,0x00) //[G0 PIC END] mif_dne_rd_wgt1_pic_end
	UINT32 b2_pic_end                       :1;	//(10,RO,0x00) //[G0 PIC END] mif_dne_rd_ft0_pic_end
	UINT32 b3_pic_end                       :1;	//(11,RO,0x00) //[G0 PIC END] mif_dne_rd_ft1_pic_end
	UINT32 b4_pic_end                       :1;	//(12,RO,0x00) //[G0 PIC END] mif_dne_rd_ft2_pic_end
	UINT32 b5_pic_end                       :1;	//(13,RO,0x00) //[G0 PIC END] mif_dne_rd_prg_pic_end
	UINT32 b6_pic_end                       :1;	//(14,RO,0x00) //[G0 PIC END] mif_dne_rd_ft0_pic_end
	UINT32 b7_pic_end                       :1;	//(15,RO,0x00) //[G0 PIC END] mif_dne_wd_ft1_pic_end
	UINT32 g0_pic_end_init                  :1;	//(16,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g1_pic_end_init                  :1;	//(17,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g2_pic_end_init                  :1;	//(18,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g3_pic_end_init                  :1;	//(19,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g4_pic_end_init                  :1;	//(20,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g5_pic_end_init                  :1;	//(21,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g6_pic_end_init                  :1;	//(22,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 g7_pic_end_init                  :1;	//(23,RO,0x00) //[PIC END] Clear by FW PIC_INIT
	UINT32 resvd                            :8;
	};
}REG_DNE_CTRL_INFO_PIC_END_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800F8 RW 0x0000_0000
	UINT32 rst_async_bridge_m0_y            :1;	//(0,RW,0x00) //
	UINT32 rst_async_bridge_m0_c            :1;	//(1,RW,0x00) //
	UINT32 resvd                            :30;
	};
}REG_DNE_CTRL_CTRL_GPIO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8800FC RW 0x0000_0000
	UINT32 ask_cmd_dly_cnt_r0               :4;	//(3:0,RW,0x00) //REG_SEL_MIF_CMD_DLY == '0' 일 때, 사용됨. 16배로 적용됨.
	UINT32 ask_cmd_dly_cnt_w0               :4;	//(7:4,RW,0x00) //REG_SEL_MIF_CMD_DLY == '0' 일 때, 사용됨. 16배로 적용됨.
	UINT32 resvd0                           :8;
	UINT32 ask_to_cnt                       :8;	//(23:16,RW,0x0) //x4되어서 적용됨.
	UINT32 resvd1                           :8;
	};
}REG_DNE_CTRL_CTRL_GMAU_T;

typedef struct {
	REG_DNE_CTRL_PIC_INIT_T                                    pic_init;	//0xCC880000
	REG_DNE_CTRL_PIC_START_T                                  pic_start;	//0xCC880004
	REG_DNE_CTRL_CTRL_AUTO_INIT_T                        ctrl_auto_init;	//0xCC880008
	REG_DNE_CTRL_CTRL_INTR_PULSE_T                      ctrl_intr_pulse;	//0xCC88000C
	REG_DNE_CTRL_INTR_REG_T                                    intr_reg;	//0xCC880010
	REG_DNE_CTRL_INTR_MASK_T                                  intr_mask;	//0xCC880014
	REG_DNE_CTRL_INTR_MUX_T                                    intr_mux;	//0xCC880018
	REG_DNE_CTRL_INTR_EN_T                                      intr_en;	//0xCC88001C
	UINT32                                                    reserved0;	//0xCC880020
	UINT32                                                    reserved1;	//0xCC880024
	UINT32                                                    reserved2;	//0xCC880028
	UINT32                                                    reserved3;	//0xCC88002C
	UINT32                                                    reserved4;	//0xCC880030
	UINT32                                                    reserved5;	//0xCC880034
	UINT32                                                    reserved6;	//0xCC880038
	UINT32                                                    reserved7;	//0xCC88003C
	UINT32                                                    reserved8;	//0xCC880040
	UINT32                                                    reserved9;	//0xCC880044
	UINT32                                                   reserved10;	//0xCC880048
	UINT32                                                   reserved11;	//0xCC88004C
	UINT32                                                   reserved12;	//0xCC880050
	UINT32                                                   reserved13;	//0xCC880054
	UINT32                                                   reserved14;	//0xCC880058
	UINT32                                                   reserved15;	//0xCC88005C
	UINT32                                                   reserved16;	//0xCC880060
	UINT32                                                   reserved17;	//0xCC880064
	UINT32                                                   reserved18;	//0xCC880068
	UINT32                                                   reserved19;	//0xCC88006C
	UINT32                                                   reserved20;	//0xCC880070
	UINT32                                                   reserved21;	//0xCC880074
	UINT32                                                   reserved22;	//0xCC880078
	UINT32                                                   reserved23;	//0xCC88007C
	REG_DNE_CTRL_CTRL_BLOCK2_T                              ctrl_block2;	//0xCC880080
	REG_DNE_CTRL_DNE1_CTRL_GMAU_T                        dne1_ctrl_gmau;	//0xCC880084
	UINT32                                                   reserved24;	//0xCC880088
	UINT32                                                   reserved25;	//0xCC88008C
	REG_DNE_CTRL_DNE0_CTRL_GMAU_BCH_ST_T          dne0_ctrl_gmau_bch_st;	//0xCC880090
	REG_DNE_CTRL_DNE1_CTRL_GMAU_BCH_ST_T          dne1_ctrl_gmau_bch_st;	//0xCC880094
	REG_DNE_CTRL_DNE0_CTRL_STATUS_GMAU_BCH_ST_T dne0_ctrl_status_gmau_bch_st;	//0xCC880098
	REG_DNE_CTRL_DNE1_CTRL_STATUS_GMAU_BCH_ST_T dne1_ctrl_status_gmau_bch_st;	//0xCC88009C
	REG_DNE_CTRL_DNE0_CTRL_BLOCK_T                      dne0_ctrl_block;	//0xCC8800A0
	REG_DNE_CTRL_DNE0_CTRL_BLOCK1_T                    dne0_ctrl_block1;	//0xCC8800A4
	REG_DNE_CTRL_DNE0_CTRL_CG_ON_T                      dne0_ctrl_cg_on;	//0xCC8800A8
	REG_DNE_CTRL_DNE0_AXI_USER_DNE_T                  dne0_axi_user_dne;	//0xCC8800AC
	REG_DNE_CTRL_DNE1_CTRL_BLOCK_T                      dne1_ctrl_block;	//0xCC8800B0
	REG_DNE_CTRL_DNE1_CTRL_BLOCK1_T                    dne1_ctrl_block1;	//0xCC8800B4
	REG_DNE_CTRL_DNE1_CTRL_CG_ON_T                      dne1_ctrl_cg_on;	//0xCC8800B8
	REG_DNE_CTRL_DNE1_AXI_USER_DNE_T                  dne1_axi_user_dne;	//0xCC8800BC
	REG_DNE_CTRL_PIC_INIT_G0_TIMER_T                  pic_init_g0_timer;	//0xCC8800C0
	REG_DNE_CTRL_PIC_INIT_G1_TIMER_T                  pic_init_g1_timer;	//0xCC8800C4
	REG_DNE_CTRL_PIC_INIT_G2_TIMER_T                  pic_init_g2_timer;	//0xCC8800C8
	REG_DNE_CTRL_PIC_INIT_G3_TIMER_T                  pic_init_g3_timer;	//0xCC8800CC
	REG_DNE_CTRL_PIC_INIT_G4_TIMER_T                  pic_init_g4_timer;	//0xCC8800D0
	REG_DNE_CTRL_PIC_INIT_G5_TIMER_T                  pic_init_g5_timer;	//0xCC8800D4
	REG_DNE_CTRL_PIC_INIT_G6_TIMER_T                  pic_init_g6_timer;	//0xCC8800D8
	REG_DNE_CTRL_PIC_INIT_G7_TIMER_T                  pic_init_g7_timer;	//0xCC8800DC
	REG_DNE_CTRL_INFO_IX_INTR_PULSE_T                info_ix_intr_pulse;	//0xCC8800E0
	REG_DNE_CTRL_DBG_TIMER_RUN_T                          dbg_timer_run;	//0xCC8800E4
	REG_DNE_CTRL_GX_PIC_START_END_PROC_T          gx_pic_start_end_proc;	//0xCC8800E8
	REG_DNE_CTRL_CTRL_MONITOR_T                            ctrl_monitor;	//0xCC8800EC
	REG_DNE_CTRL_CTRL_PIC_END_T                            ctrl_pic_end;	//0xCC8800F0
	REG_DNE_CTRL_INFO_PIC_END_T                            info_pic_end;	//0xCC8800F4
	REG_DNE_CTRL_CTRL_GPIO_T                                  ctrl_gpio;	//0xCC8800F8
	REG_DNE_CTRL_CTRL_GMAU_T                                  ctrl_gmau;	//0xCC8800FC
}REG_DNE_CTRL_T;

extern volatile REG_DNE_CTRL_T*                    gpREG_DNE_CTRL;

#endif
