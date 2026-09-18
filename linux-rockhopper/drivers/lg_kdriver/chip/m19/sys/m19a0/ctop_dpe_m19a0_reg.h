#ifndef _CTOP_DPE_M19A0_REG_H_
#define _CTOP_DPE_M19A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xC930_A008    ctop_dpe_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_lockn_sel          :  1,    //      0
    c4_vx1_lockn_frmain       :  1,    //      1
    c4_sel_fin                :  2,    //   3: 2
    c4_sel_plllock            :  1,    //      4
    c4_testlock_ctl           :  1,    //      5
    c4_lock_ext               :  1,    //      6
                              : 25;    //   31:7 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R02_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A00C    ctop_dpe_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_itune0                 :  3,    //   2: 0
    c4_itune1                 :  3,    //   5: 3
    c4_itune2                 :  3,    //   8: 6
    c4_itune3                 :  3,    //  11: 9
    c4_itune4                 :  3,    //  14:12
    c4_itune5                 :  3,    //  17:15
    c4_itune6                 :  3,    //  20:18
    c4_itune7                 :  3,    //  23:21
    c4_itune8                 :  3,    //  26:24
    c4_itune9                 :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R03_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A010    ctop_dpe_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_itune10                :  3,    //   2: 0
    c4_itune11                :  3,    //   5: 3
    c4_itune12                :  3,    //   8: 6
    c4_itune13                :  3,    //  11: 9
    c4_itune14                :  3,    //  14:12
    c4_itune15                :  3,    //  17:15
    c4_itune16                :  3,    //  20:18
    c4_itune17                :  3,    //  23:21
    c4_itune18                :  3,    //  26:24
    c4_itune19                :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R04_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A014    ctop_dpe_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_itune20                :  3,    //   2: 0
    c4_itune21                :  3,    //   5: 3
    c4_itune22                :  3,    //   8: 6
    c4_itune23                :  3,    //  11: 9
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R05_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A018    ctop_dpe_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_flip_en_ch0            :  1,    //      0
    c4_flip_en_ch1            :  1,    //      1
    c4_flip_en_ch2            :  1,    //      2
    c4_flip_en_ch3            :  1,    //      3
    c4_flip_en_ch4            :  1,    //      4
    c4_flip_en_ch5            :  1,    //      5
    c4_flip_en_ch6            :  1,    //      6
    c4_flip_en_ch7            :  1,    //      7
    c4_flip_en_ch8            :  1,    //      8
    c4_flip_en_ch9            :  1,    //      9
    c4_flip_en_ch10           :  1,    //     10
    c4_flip_en_ch11           :  1,    //     11
    c4_flip_en_ch12           :  1,    //     12
    c4_flip_en_ch13           :  1,    //     13
    c4_flip_en_ch14           :  1,    //     14
    c4_flip_en_ch15           :  1,    //     15
    c4_flip_en_ch16           :  1,    //     16
    c4_flip_en_ch17           :  1,    //     17
    c4_flip_en_ch18           :  1,    //     18
    c4_flip_en_ch19           :  1,    //     19
    c4_flip_en_ch20           :  1,    //     20
    c4_flip_en_ch21           :  1,    //     21
    c4_flip_en_ch22           :  1,    //     22
    c4_flip_en_ch23           :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R06_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A01C    ctop_dpe_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pemp_ch0               :  3,    //   2: 0
    c4_pemp_ch1               :  3,    //   5: 3
    c4_pemp_ch2               :  3,    //   8: 6
    c4_pemp_ch3               :  3,    //  11: 9
    c4_pemp_ch4               :  3,    //  14:12
    c4_pemp_ch5               :  3,    //  17:15
    c4_pemp_ch6               :  3,    //  20:18
    c4_pemp_ch7               :  3,    //  23:21
    c4_pemp_ch8               :  3,    //  26:24
    c4_pemp_ch9               :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R07_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A020    ctop_dpe_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pemp_ch10              :  3,    //   2: 0
    c4_pemp_ch11              :  3,    //   5: 3
    c4_pemp_ch12              :  3,    //   8: 6
    c4_pemp_ch13              :  3,    //  11: 9
    c4_pemp_ch14              :  3,    //  14:12
    c4_pemp_ch15              :  3,    //  17:15
    c4_pemp_ch16              :  3,    //  20:18
    c4_pemp_ch17              :  3,    //  23:21
    c4_pemp_ch18              :  3,    //  26:24
    c4_pemp_ch19              :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R08_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A024    ctop_dpe_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pemp_ch20              :  3,    //   2: 0
    c4_pemp_ch21              :  3,    //   5: 3
    c4_pemp_ch22              :  3,    //   8: 6
    c4_pemp_ch23              :  3,    //  11: 9
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R09_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A028    ctop_dpe_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_lock_samp_ctl          :  2,    //   1: 0
    c4_lock_div_ctl           :  2,    //   3: 2
    c4_sel_rstn               :  1,    //      4
    c4_sel_rstctl             :  1,    //      5
    c4_reg_rstn               :  1,    //      6
                              : 25;    //   31:7 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R10_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A02C    ctop_dpe_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link0_en               :  1,    //      0
    c4_link1_en               :  1,    //      1
    c4_link2_en               :  1,    //      2
    c4_link3_en               :  1,    //      3
    c4_link4_en               :  1,    //      4
    c4_link5_en               :  1,    //      5
    c4_link6_en               :  1,    //      6
    c4_link7_en               :  1,    //      7
    c4_link8_en               :  1,    //      8
    c4_link9_en               :  1,    //      9
    c4_link10_en              :  1,    //     10
    c4_link11_en              :  1,    //     11
    c4_link12_en              :  1,    //     12
    c4_link13_en              :  1,    //     13
    c4_link14_en              :  1,    //     14
    c4_link15_en              :  1,    //     15
    c4_link16_en              :  1,    //     16
    c4_link17_en              :  1,    //     17
    c4_link18_en              :  1,    //     18
    c4_link19_en              :  1,    //     19
    c4_link20_en              :  1,    //     20
    c4_link21_en              :  1,    //     21
    c4_link22_en              :  1,    //     22
    c4_link23_en              :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R11_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A030    ctop_dpe_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_epi_lvdsen             :  1,    //      0
    c4_bytemode               :  2,    //   2: 1
    c4_term_en                :  1,    //      3
    c4_adj_term               :  4,    //   7: 4
    c4_rf                     :  1,    //      8
    c4_sw_rext                :  1,    //      9
    c4_sel_lock               :  1,    //     10
    c4_sw_pud                 :  1,    //     11
    c4_epi10_en               :  1,    //     12
    c4_ctl_reg                :  2,    //  14:13
    c4_lp_en                  :  1,    //     15
                              : 16;    //  31:16 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R12_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A034    ctop_dpe_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_rstn_vtxlink1_en       :  1,    //      0
    c4_rstn_vtxlink2_en       :  1,    //      1
    c4_rstn_vtxlink3_en       :  1,    //      2
    c4_rstn_vtxlink4_en       :  1,    //      3
    c4_rstn_vtxlink5_en       :  1,    //      4
    c4_rstn_vtxlink6_en       :  1,    //      5
    c4_sel_clkpix1            :  3,    //   8: 6
    c4_sel_clkpix2            :  3,    //  11: 9
    c4_sel_clkpix3            :  3,    //  14:12
    c4_sel_clkpix4            :  3,    //  17:15
    c4_sel_clkpix5            :  3,    //  20:18
    c4_sel_clkpix6            :  3,    //  23:21
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R13_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A038    ctop_dpe_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_count_txlock1          : 13,    //  12: 0
    c4_count_txlock2          : 13,    //  25:13
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R14_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A03C    ctop_dpe_r15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_count_txlock3          : 13,    //  12: 0
    c4_count_txlock4          : 13,    //  25:13
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R15_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A040    ctop_dpe_r16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_count_txlock5          : 13,    //  12: 0
    c4_count_txlock6          : 13,    //  25:13
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R16_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A044    ctop_dpe_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_count_rxlock1          :  6,    //   5: 0
    c4_count_rxlock2          :  6,    //  11: 6
    c4_count_rxlock3          :  6,    //  17:12
    c4_count_rxlock4          :  6,    //  23:18
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R17_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A048    ctop_dpe_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_count_rxlock5          :  6,    //   5: 0
    c4_count_rxlock6          :  6,    //  11: 6
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R18_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A04C    ctop_dpe_r19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_read_address_offset1   :  2,    //   1: 0
    c4_read_address_offset2   :  2,    //   3: 2
    c4_read_address_offset3   :  2,    //   5: 4
    c4_read_address_offset4   :  2,    //   7: 6
    c4_read_address_offset5   :  2,    //   9: 8
    c4_read_address_offset6   :  2,    //  11:10
    c4_clk_pix1x_rf1          :  1,    //     12
    c4_clk_pix1x_rf2          :  1,    //     13
    c4_clk_pix1x_rf3          :  1,    //     14
    c4_clk_pix1x_rf4          :  1,    //     15
    c4_clk_pix1x_rf5          :  1,    //     16
    c4_clk_pix1x_rf6          :  1,    //     17
    c4_txlock_fixen1          :  2,    //  19:18
    c4_txlock_fixen2          :  2,    //  21:20
    c4_txlock_fixen3          :  2,    //  23:22
    c4_txlock_fixen4          :  2,    //  25:24
    c4_txlock_fixen5          :  2,    //  27:26
    c4_txlock_fixen6          :  2,    //  29:28
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R19_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A050    ctop_dpe_r20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_mode1             :  2,    //   1: 0
    c4_test_mode2             :  2,    //   3: 2
    c4_test_mode3             :  2,    //   5: 4
    c4_test_mode4             :  2,    //   7: 6
    c4_test_mode5             :  2,    //   9: 8
    c4_test_mode6             :  2,    //  11:10
    c4_read_lane_sel1         :  2,    //  13:12
    c4_read_lane_sel2         :  2,    //  15:14
    c4_read_lane_sel3         :  2,    //  17:16
    c4_read_lane_sel4         :  2,    //  19:18
    c4_read_lane_sel5         :  2,    //  21:20
    c4_read_lane_sel6         :  2,    //  23:22
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R20_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A054    ctop_dpe_r21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_read_tp_sel1           :  4,    //   3: 0
    c4_read_tp_sel2           :  4,    //   7: 4
    c4_read_tp_sel3           :  4,    //  11: 8
    c4_read_tp_sel4           :  4,    //  15:12
    c4_read_tp_sel5           :  4,    //  19:16
    c4_read_tp_sel6           :  4,    //  23:20
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R21_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A058    ctop_dpe_r22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_man_pattern_en     :  1,    //      0
    c4_vtx_man_pattern_sel    :  4,    //   4: 1
    c4_vtx_sync_inv           :  1,    //      5
    c4_vtx_sync_chk_clk_en    :  1,    //      6
    c4_vtx_sync_chk_rstb      :  1,    //      7
    c4_vtx_pattern_clk_en     :  1,    //      8
                              : 23;    //   31:9 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R22_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A05C    ctop_dpe_r23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_tvblank            : 12,    //  11: 0
    c4_vtx_tvact              : 12,    //  23:12
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R23_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A060    ctop_dpe_r24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_tvfp               : 11,    //  10: 0
    c4_vtx_tvpw               :  8,    //  18:11
                              : 13;    //  31:19 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R24_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A064    ctop_dpe_r25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_thblank            : 13,    //  12: 0
    c4_vtx_thact              : 13,    //  25:13
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R25_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A068    ctop_dpe_r26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_thfp               : 12,    //  11: 0
    c4_vtx_thpw               :  8,    //  19:12
                              : 12;    //  31:20 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R26_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A06C    ctop_dpe_r27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_vsync_gen_sel1     :  1,    //      0
    c4_vtx_vsync_gen_sel2     :  1,    //      1
    c4_vtx_vsync_gen_sel3     :  1,    //      2
    c4_vtx_vsync_gen_sel4     :  1,    //      3
    c4_vtx_vsync_gen_sel5     :  1,    //      4
    c4_vtx_vsync_gen_sel6     :  1,    //      5
    c4_vtx_sync_pol1          :  1,    //      6
    c4_vtx_sync_pol2          :  1,    //      7
    c4_vtx_sync_pol3          :  1,    //      8
    c4_vtx_sync_pol4          :  1,    //      9
    c4_vtx_sync_pol5          :  1,    //     10
    c4_vtx_sync_pol6          :  1,    //     11
    c4_vtx_stuck_en1          :  1,    //     12
    c4_vtx_stuck_en2          :  1,    //     13
    c4_vtx_stuck_en3          :  1,    //     14
    c4_vtx_stuck_en4          :  1,    //     15
    c4_vtx_stuck_en5          :  1,    //     16
    c4_vtx_stuck_en6          :  1,    //     17
    c4_vtx_vsgen_en1          :  1,    //     18
    c4_vtx_vsgen_en2          :  1,    //     19
    c4_vtx_vsgen_en3          :  1,    //     20
    c4_vtx_vsgen_en4          :  1,    //     21
    c4_vtx_vsgen_en5          :  1,    //     22
    c4_vtx_vsgen_en6          :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R27_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A070    ctop_dpe_r28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_input_stuck_en1    :  1,    //      0
    c4_vtx_input_stuck_en2    :  1,    //      1
    c4_vtx_input_stuck_en3    :  1,    //      2
    c4_vtx_input_stuck_en4    :  1,    //      3
    c4_vtx_input_stuck_en5    :  1,    //      4
    c4_vtx_input_stuck_en6    :  1,    //      5
    c4_vtx_input_stuck_val1   :  1,    //      6
    c4_vtx_input_stuck_val2   :  1,    //      7
    c4_vtx_input_stuck_val3   :  1,    //      8
    c4_vtx_input_stuck_val4   :  1,    //      9
    c4_vtx_input_stuck_val5   :  1,    //     10
    c4_vtx_input_stuck_val6   :  1,    //     11
    c4_vtx_den_mincnt1        :  2,    //  13:12
    c4_vtx_den_mincnt2        :  2,    //  15:14
    c4_vtx_den_mincnt3        :  2,    //  17:16
    c4_vtx_den_mincnt4        :  2,    //  19:18
    c4_vtx_den_mincnt5        :  2,    //  21:20
    c4_vtx_den_mincnt6        :  2,    //  23:22
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R28_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A074    ctop_dpe_r29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_vs_interval1       :  3,    //   2: 0
    c4_vtx_vs_interval2       :  3,    //   5: 3
    c4_vtx_vs_interval3       :  3,    //   8: 6
    c4_vtx_vs_interval4       :  3,    //  11: 9
    c4_vtx_vs_interval5       :  3,    //  14:12
    c4_vtx_vs_interval6       :  3,    //  17:15
                              : 14;    //  31:18 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R29_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A078    ctop_dpe_r30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_bist_en                :  1,    //      0
    c4_bist_clk_en            :  1,    //      1
    c4_err_inj_en             :  1,    //      2
    c4_err_inj_mode           :  1,    //      3
    c4_err_inj_ext            :  1,    //      4
    c4_err_inj_num            :  4,    //   8: 5
    c4_err_inj_per            :  4,    //  12: 9
    c4_err_inj_st_per         : 10,    //  22:13
                              :  9;    //  31:23 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R30_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A07C    ctop_dpe_r31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_ber_en0                :  1,    //      0
    c4_ber_en1                :  1,    //      1
    c4_ber_en2                :  1,    //      2
    c4_ber_en3                :  1,    //      3
    c4_ber_en4                :  1,    //      4
    c4_ber_en5                :  1,    //      5
    c4_ber_en6                :  1,    //      6
    c4_ber_en7                :  1,    //      7
    c4_ber_en8                :  1,    //      8
    c4_ber_en9                :  1,    //      9
    c4_ber_en10               :  1,    //     10
    c4_ber_en11               :  1,    //     11
    c4_ber_en12               :  1,    //     12
    c4_ber_en13               :  1,    //     13
    c4_ber_en14               :  1,    //     14
    c4_ber_en15               :  1,    //     15
    c4_ber_en16               :  1,    //     16
    c4_ber_en17               :  1,    //     17
    c4_ber_en18               :  1,    //     18
    c4_ber_en19               :  1,    //     19
    c4_ber_en20               :  1,    //     20
    c4_ber_en21               :  1,    //     21
    c4_ber_en22               :  1,    //     22
    c4_ber_en23               :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R31_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A080    ctop_dpe_r32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_ber_num_dat            :  2,    //   1: 0
    c4_ber_num_err            :  4,    //   5: 2
    c4_ber_rlt_sel            :  2,    //   7: 6
    c4_sch_period             :  4,    //  11: 8
    c4_sch_reserve            :  8,    //  19:12
    c4_retimer_bypass_en      :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R32_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A084    ctop_dpe_r33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    displl_fine_div           :  1,    //      1
    displl_dss                :  1,    //      2
    displl_accuracy           :  2,    //   4: 3
    displl_updn_max           :  7,    //  11: 5
    displl_mod_freq           :  9,    //  20:12
    displl_m                  :  6,    //  26:21
                              :  1,    //     27 reserved
    displl_cih                :  4;    //  31:28
}CTOP_CTRL_DPE_CTOP_DPE_R33_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A088    ctop_dpe_r34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    displl_ofs_mode           :  1,    //      4
    displl_fout3_od           :  3,    //   7: 5
    displl_fout2_od           :  3,    //  10: 8
    displl_fout_od            :  2,    //  12:11
    displl_pre_fout3_div      :  3,    //  15:13
    displl_pre_fout2_div      :  3,    //  18:16
    displl_nsc                :  4,    //  22:19
    displl_npc                :  6,    //  28:23
    displl_fine_control       :  3;    //  31:29
}CTOP_CTRL_DPE_CTOP_DPE_R34_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A08C    ctop_dpe_r35 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    displl_wakeup_bypass      :  1,    //     22
    displl_ddr_mode           :  1,    //     23
    displl_offset             :  8;    //  31:24
}CTOP_CTRL_DPE_CTOP_DPE_R35_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A090    ctop_dpe_r36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_gpio15_pd             :  1,    //      5
    reg_gpio14_pd             :  1,    //      6
                              :  1,    //      7 reserved
    reg_gpio13_pu             :  1,    //      8
    reg_gpio13_pd             :  1,    //      9
    reg_gpio12_pd             :  1,    //     10
    reg_gpio11_pd             :  1,    //     11
                              :  1,    //     12 reserved
    reg_gpio10_pu             :  1,    //     13
    reg_gpio10_pd             :  1,    //     14
    reg_gpio9_pd              :  1,    //     15
    reg_gpio8_pd              :  1,    //     16
    reg_gpio7_pd              :  1,    //     17
    reg_gpio6_pd              :  1,    //     18
    reg_gpio5_pd              :  1,    //     19
    reg_gpio4_pd              :  1,    //     20
    reg_gpio3_pd              :  1,    //     21
    reg_gpio2_pd              :  1,    //     22
    reg_gpio1_pd              :  1,    //     23
    reg_gpio0_pd              :  1,    //     24
    reg_uart0_txd_pu          :  1,    //     25
    reg_uart0_rxd_pu          :  1,    //     26
    reg_uart1_cts_pu          :  1,    //     27
    reg_uart1_rts_pu          :  1,    //     28
    reg_uart1_txd_pu          :  1,    //     29
    reg_uart1_rxd_pu          :  1,    //     30
    reg_iec958out_pu          :  1;    //     31
}CTOP_CTRL_DPE_CTOP_DPE_R36_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A094    ctop_dpe_r37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    mon_sr_en                 :  1,    //      2
    mon_led_en                :  1,    //      3
    mon_gsc_en                :  1,    //      4
    mon_gpu_en                :  1,    //      5
    mon_cco_en                :  1,    //      6
    mon_imx_en                :  1,    //      7
    mon_hdmi_en               :  1,    //      8
                              :  1,    //      9 reserved
    mon_fme1_en               :  1,    //     10
                              :  2,    //  12:11 reserved
    mon_aud_en                :  1,    //     13
    mon_tcon_en               :  1,    //     14
    mon_fmc_en                :  1,    //     15
    mon_cpu_en                :  1,    //     16
    mon_te_en                 :  1,    //     17
    mon_hdr_en                :  1,    //     18
    mon_aad_en                :  1,    //     19
    mon_vdec0_en              :  1,    //     20
    mon_fme0_en               :  1,    //     21
    mon_cvi_en                :  1,    //     22
                              :  9;    //  31:23 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R37_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A09C    ctop_dpe_r39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    reg_gpio24_pd             :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_gpio25_pd             :  1,    //      7
                              :  3,    //  10: 8 reserved
    reg_gpio26_pd             :  1,    //     11
                              :  3,    //  14:12 reserved
    reg_gpio27_pd             :  1,    //     15
                              :  3,    //  18:16 reserved
    reg_gpio28_pd             :  1,    //     19
                              :  3,    //  22:20 reserved
    reg_gpio29_pd             :  1,    //     23
                              :  3,    //  26:24 reserved
    reg_gpio30_pd             :  1,    //     27
                              :  3,    //  30:28 reserved
    reg_gpio31_pd             :  1;    //     31
}CTOP_CTRL_DPE_CTOP_DPE_R39_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0A0    ctop_dpe_r40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pdb                    :  1,    //      0
    c4_prbs_mode_sel          :  1,    //      1
    c4_rstn_vtxlink           :  1,    //      2
    c4_sel_bw                 :  1,    //      3
    c4_sel_lpf                :  1,    //      4
    c4_pll_ic                 :  2,    //   6: 5
    c4_prbs_out_sel           :  2,    //   8: 7
    c4_sc_ctl                 :  2,    //  10: 9
    c4_sel_mode               :  2,    //  12:11
    c4_cih                    :  3,    //  15:13
                              : 16;    //  31:16 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R40_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0A4    ctop_dpe_r41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_enc_off1               :  1,    //      0
    c4_enc_off2               :  1,    //      1
    c4_enc_off3               :  1,    //      2
    c4_enc_off4               :  1,    //      3
    c4_enc_off5               :  1,    //      4
    c4_enc_off6               :  1,    //      5
    c4_enc_rst1               :  1,    //      6
    c4_enc_rst2               :  1,    //      7
    c4_enc_rst3               :  1,    //      8
    c4_enc_rst4               :  1,    //      9
    c4_enc_rst5               :  1,    //     10
    c4_enc_rst6               :  1,    //     11
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R41_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0A8    ctop_dpe_r42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pdb_ch0                :  1,    //      0
    c4_pdb_ch1                :  1,    //      1
    c4_pdb_ch2                :  1,    //      2
    c4_pdb_ch3                :  1,    //      3
    c4_pdb_ch4                :  1,    //      4
    c4_pdb_ch5                :  1,    //      5
    c4_pdb_ch6                :  1,    //      6
    c4_pdb_ch7                :  1,    //      7
    c4_pdb_ch8                :  1,    //      8
    c4_pdb_ch9                :  1,    //      9
    c4_pdb_ch10               :  1,    //     10
    c4_pdb_ch11               :  1,    //     11
    c4_pdb_ch12               :  1,    //     12
    c4_pdb_ch13               :  1,    //     13
    c4_pdb_ch14               :  1,    //     14
    c4_pdb_ch15               :  1,    //     15
    c4_pdb_ch16               :  1,    //     16
    c4_pdb_ch17               :  1,    //     17
    c4_pdb_ch18               :  1,    //     18
    c4_pdb_ch19               :  1,    //     19
    c4_pdb_ch20               :  1,    //     20
    c4_pdb_ch21               :  1,    //     21
    c4_pdb_ch22               :  1,    //     22
    c4_pdb_ch23               :  1,    //     23
    c4_rf_lb_ckout1           :  1,    //     24
    c4_rf_lb_ckout2           :  1,    //     25
    c4_rf_lb_ckout3           :  1,    //     26
    c4_rf_lb_ckout4           :  1,    //     27
    c4_rf_lb_ckout5           :  1,    //     28
    c4_rf_lb_ckout6           :  1,    //     29
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R42_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0AC    ctop_dpe_r43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_rf_lb_desck0           :  1,    //      0
    c4_rf_lb_desck1           :  1,    //      1
    c4_rf_lb_desck2           :  1,    //      2
    c4_rf_lb_desck3           :  1,    //      3
    c4_rf_lb_desck4           :  1,    //      4
    c4_rf_lb_desck5           :  1,    //      5
    c4_rf_lb_desck6           :  1,    //      6
    c4_rf_lb_desck7           :  1,    //      7
    c4_rf_lb_desck8           :  1,    //      8
    c4_rf_lb_desck9           :  1,    //      9
    c4_rf_lb_desck10          :  1,    //     10
    c4_rf_lb_desck11          :  1,    //     11
    c4_rf_lb_desck12          :  1,    //     12
    c4_rf_lb_desck13          :  1,    //     13
    c4_rf_lb_desck14          :  1,    //     14
    c4_rf_lb_desck15          :  1,    //     15
    c4_rf_lb_desck16          :  1,    //     16
    c4_rf_lb_desck17          :  1,    //     17
    c4_rf_lb_desck18          :  1,    //     18
    c4_rf_lb_desck19          :  1,    //     19
    c4_rf_lb_desck20          :  1,    //     20
    c4_rf_lb_desck21          :  1,    //     21
    c4_rf_lb_desck22          :  1,    //     22
    c4_rf_lb_desck23          :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R43_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0B0    ctop_dpe_r44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    c4_scr_off1               :  1,    //     24
    c4_scr_off2               :  1,    //     25
    c4_scr_off3               :  1,    //     26
    c4_scr_off4               :  1,    //     27
    c4_scr_off5               :  1,    //     28
    c4_scr_off6               :  1,    //     29
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R44_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0B4    ctop_dpe_r45 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_scr_rst1               :  1,    //      0
    c4_scr_rst2               :  1,    //      1
    c4_scr_rst3               :  1,    //      2
    c4_scr_rst4               :  1,    //      3
    c4_scr_rst5               :  1,    //      4
    c4_scr_rst6               :  1,    //      5
                              : 26;    //   31:6 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R45_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0B8    ctop_dpe_r46 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_lb_ck_ctl0             :  2,    //   1: 0
    c4_lb_ck_ctl1             :  2,    //   3: 2
    c4_lb_ck_ctl2             :  2,    //   5: 4
    c4_lb_ck_ctl3             :  2,    //   7: 6
    c4_lb_ck_ctl4             :  2,    //   9: 8
    c4_lb_ck_ctl5             :  2,    //  11:10
    c4_lb_ck_ctl6             :  2,    //  13:12
    c4_lb_ck_ctl7             :  2,    //  15:14
    c4_lb_ck_ctl8             :  2,    //  17:16
    c4_lb_ck_ctl9             :  2,    //  19:18
    c4_lb_ck_ctl10            :  2,    //  21:20
    c4_lb_ck_ctl11            :  2,    //  23:22
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R46_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0BC    ctop_dpe_r47 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_lb_ck_ctl12            :  2,    //   1: 0
    c4_lb_ck_ctl13            :  2,    //   3: 2
    c4_lb_ck_ctl14            :  2,    //   5: 4
    c4_lb_ck_ctl15            :  2,    //   7: 6
    c4_lb_ck_ctl16            :  2,    //   9: 8
    c4_lb_ck_ctl17            :  2,    //  11:10
    c4_lb_ck_ctl18            :  2,    //  13:12
    c4_lb_ck_ctl19            :  2,    //  15:14
    c4_lb_ck_ctl20            :  2,    //  17:16
    c4_lb_ck_ctl21            :  2,    //  19:18
    c4_lb_ck_ctl22            :  2,    //  21:20
    c4_lb_ck_ctl23            :  2,    //  23:22
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R47_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0C0    ctop_dpe_r48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di1               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R48_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0C4    ctop_dpe_r49 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di2               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R49_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0C8    ctop_dpe_r50 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di3               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R50_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0CC    ctop_dpe_r51 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di4               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R51_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0D0    ctop_dpe_r52 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di5               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R52_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0D4    ctop_dpe_r53 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di6               : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R53_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0D8    ctop_dpe_r54 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    gpupll_fine_div           :  1,    //      1
    gpupll_dss                :  1,    //      2
    gpupll_accuracy           :  2,    //   4: 3
    gpupll_updn_max           :  7,    //  11: 5
    gpupll_mod_freq           :  9,    //  20:12
    gpupll_m                  :  6,    //  26:21
                              :  1,    //     27 reserved
    gpupll_cih                :  4;    //  31:28
}CTOP_CTRL_DPE_CTOP_DPE_R54_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0DC    ctop_dpe_r55 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    gpupll_ofs_mode           :  1,    //      4
    gpupll_fout3_od           :  3,    //   7: 5
    gpupll_fout2_od           :  3,    //  10: 8
    gpupll_fout_od            :  2,    //  12:11
    gpupll_pre_fout3_div      :  3,    //  15:13
    gpupll_pre_fout2_div      :  3,    //  18:16
    gpupll_nsc                :  4,    //  22:19
    gpupll_npc                :  6,    //  28:23
    gpupll_fine_control       :  3;    //  31:29
}CTOP_CTRL_DPE_CTOP_DPE_R55_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0E0    ctop_dpe_r56 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    gpupll_wakeup_bypass      :  1,    //     22
    gpupll_ddr_mode           :  1,    //     23
    gpupll_offset             :  8;    //  31:24
}CTOP_CTRL_DPE_CTOP_DPE_R56_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0E4    ctop_dpe_r57 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link_read_tp1          : 16,    //  15: 0
    c4_link_read_tp2          : 16;    //  31:16
}CTOP_CTRL_DPE_CTOP_DPE_R57_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0E8    ctop_dpe_r58 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link_read_tp3          : 16,    //  15: 0
    c4_link_read_tp4          : 16;    //  31:16
}CTOP_CTRL_DPE_CTOP_DPE_R58_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0EC    ctop_dpe_r59 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link_read_tp5          : 16,    //  15: 0
    c4_link_read_tp6          : 16;    //  31:16
}CTOP_CTRL_DPE_CTOP_DPE_R59_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0F0    ctop_dpe_r60 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_c4_ber_stable0          :  1,    //      0
    i_c4_ber_stable1          :  1,    //      1
    i_c4_ber_stable2          :  1,    //      2
    i_c4_ber_stable3          :  1,    //      3
    i_c4_ber_stable4          :  1,    //      4
    i_c4_ber_stable5          :  1,    //      5
    i_c4_ber_stable6          :  1,    //      6
    i_c4_ber_stable7          :  1,    //      7
    i_c4_ber_stable8          :  1,    //      8
    i_c4_ber_stable9          :  1,    //      9
    i_c4_ber_stable10         :  1,    //     10
    i_c4_ber_stable11         :  1,    //     11
    i_c4_ber_stable12         :  1,    //     12
    i_c4_ber_stable13         :  1,    //     13
    i_c4_ber_stable14         :  1,    //     14
    i_c4_ber_stable15         :  1,    //     15
    i_c4_ber_stable16         :  1,    //     16
    i_c4_ber_stable17         :  1,    //     17
    i_c4_ber_stable18         :  1,    //     18
    i_c4_ber_stable19         :  1,    //     19
    i_c4_ber_stable20         :  1,    //     20
    i_c4_ber_stable21         :  1,    //     21
    i_c4_ber_stable22         :  1,    //     22
    i_c4_ber_stable23         :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R60_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0F4    ctop_dpe_r61 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_c4_ber_chkdone0         :  1,    //      0
    i_c4_ber_chkdone1         :  1,    //      1
    i_c4_ber_chkdone2         :  1,    //      2
    i_c4_ber_chkdone3         :  1,    //      3
    i_c4_ber_chkdone4         :  1,    //      4
    i_c4_ber_chkdone5         :  1,    //      5
    i_c4_ber_chkdone6         :  1,    //      6
    i_c4_ber_chkdone7         :  1,    //      7
    i_c4_ber_chkdone8         :  1,    //      8
    i_c4_ber_chkdone9         :  1,    //      9
    i_c4_ber_chkdone10        :  1,    //     10
    i_c4_ber_chkdone11        :  1,    //     11
    i_c4_ber_chkdone12        :  1,    //     12
    i_c4_ber_chkdone13        :  1,    //     13
    i_c4_ber_chkdone14        :  1,    //     14
    i_c4_ber_chkdone15        :  1,    //     15
    i_c4_ber_chkdone16        :  1,    //     16
    i_c4_ber_chkdone17        :  1,    //     17
    i_c4_ber_chkdone18        :  1,    //     18
    i_c4_ber_chkdone19        :  1,    //     19
    i_c4_ber_chkdone20        :  1,    //     20
    i_c4_ber_chkdone21        :  1,    //     21
    i_c4_ber_chkdone22        :  1,    //     22
    i_c4_ber_chkdone23        :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R61_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0F8    ctop_dpe_r62 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_c4_ber_chkpass0         :  1,    //      0
    i_c4_ber_chkpass1         :  1,    //      1
    i_c4_ber_chkpass2         :  1,    //      2
    i_c4_ber_chkpass3         :  1,    //      3
    i_c4_ber_chkpass4         :  1,    //      4
    i_c4_ber_chkpass5         :  1,    //      5
    i_c4_ber_chkpass6         :  1,    //      6
    i_c4_ber_chkpass7         :  1,    //      7
    i_c4_ber_chkpass8         :  1,    //      8
    i_c4_ber_chkpass9         :  1,    //      9
    i_c4_ber_chkpass10        :  1,    //     10
    i_c4_ber_chkpass11        :  1,    //     11
    i_c4_ber_chkpass12        :  1,    //     12
    i_c4_ber_chkpass13        :  1,    //     13
    i_c4_ber_chkpass14        :  1,    //     14
    i_c4_ber_chkpass15        :  1,    //     15
    i_c4_ber_chkpass16        :  1,    //     16
    i_c4_ber_chkpass17        :  1,    //     17
    i_c4_ber_chkpass18        :  1,    //     18
    i_c4_ber_chkpass19        :  1,    //     19
    i_c4_ber_chkpass20        :  1,    //     20
    i_c4_ber_chkpass21        :  1,    //     21
    i_c4_ber_chkpass22        :  1,    //     22
    i_c4_ber_chkpass23        :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R62_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A0FC    ctr86_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_c4_ber_err_ofl0         :  1,    //      0
    i_c4_ber_err_ofl1         :  1,    //      1
    i_c4_ber_err_ofl2         :  1,    //      2
    i_c4_ber_err_ofl3         :  1,    //      3
    i_c4_ber_err_ofl4         :  1,    //      4
    i_c4_ber_err_ofl5         :  1,    //      5
    i_c4_ber_err_ofl6         :  1,    //      6
    i_c4_ber_err_ofl7         :  1,    //      7
    i_c4_ber_err_ofl8         :  1,    //      8
    i_c4_ber_err_ofl9         :  1,    //      9
    i_c4_ber_err_ofl10        :  1,    //     10
    i_c4_ber_err_ofl11        :  1,    //     11
    i_c4_ber_err_ofl12        :  1,    //     12
    i_c4_ber_err_ofl13        :  1,    //     13
    i_c4_ber_err_ofl14        :  1,    //     14
    i_c4_ber_err_ofl15        :  1,    //     15
    i_c4_ber_err_ofl16        :  1,    //     16
    i_c4_ber_err_ofl17        :  1,    //     17
    i_c4_ber_err_ofl18        :  1,    //     18
    i_c4_ber_err_ofl19        :  1,    //     19
    i_c4_ber_err_ofl20        :  1,    //     20
    i_c4_ber_err_ofl21        :  1,    //     21
    i_c4_ber_err_ofl22        :  1,    //     22
    i_c4_ber_err_ofl23        :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTR86_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A100    ctr87_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_c4_ber_din_ok0          :  1,    //      0
    i_c4_ber_din_ok1          :  1,    //      1
    i_c4_ber_din_ok2          :  1,    //      2
    i_c4_ber_din_ok3          :  1,    //      3
    i_c4_ber_din_ok4          :  1,    //      4
    i_c4_ber_din_ok5          :  1,    //      5
    i_c4_ber_din_ok6          :  1,    //      6
    i_c4_ber_din_ok7          :  1,    //      7
    i_c4_ber_din_ok8          :  1,    //      8
    i_c4_ber_din_ok9          :  1,    //      9
    i_c4_ber_din_ok10         :  1,    //     10
    i_c4_ber_din_ok11         :  1,    //     11
    i_c4_ber_din_ok12         :  1,    //     12
    i_c4_ber_din_ok13         :  1,    //     13
    i_c4_ber_din_ok14         :  1,    //     14
    i_c4_ber_din_ok15         :  1,    //     15
    i_c4_ber_din_ok16         :  1,    //     16
    i_c4_ber_din_ok17         :  1,    //     17
    i_c4_ber_din_ok18         :  1,    //     18
    i_c4_ber_din_ok19         :  1,    //     19
    i_c4_ber_din_ok20         :  1,    //     20
    i_c4_ber_din_ok21         :  1,    //     21
    i_c4_ber_din_ok22         :  1,    //     22
    i_c4_ber_din_ok23         :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTR87_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A104    ctr88_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_c4_ber_rlt1             : 10,    //   9: 0
    i_c4_ber_rlt2             : 10,    //  19:10
    i_c4_ber_rlt3             : 10,    //  29:20
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTR88_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A108    ctr89_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    i_c4_ber_rlt4             : 10,    //   9: 0
    i_c4_ber_rlt5             : 10,    //  19:10
    i_c4_ber_rlt6             : 10,    //  29:20
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTR89_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A10C    ctr90_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_ber_st1                :  2,    //   1: 0
    c4_ber_st2                :  2,    //   3: 2
    c4_ber_st3                :  2,    //   5: 4
    c4_ber_st4                :  2,    //   7: 6
    c4_ber_st5                :  2,    //   9: 8
    c4_ber_st6                :  2,    //  11:10
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTR90_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A110    ctr91_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_sch_rlt1               :  3,    //   2: 0
    c4_sch_rlt2               :  3,    //   5: 3
    c4_sch_rlt3               :  3,    //   8: 6
    c4_sch_rlt4               :  3,    //  11: 9
    c4_sch_rlt5               :  3,    //  14:12
    c4_sch_rlt6               :  3,    //  17:15
                              : 14;    //  31:18 reserved
}CTOP_CTRL_DPE_CTR91_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A114    ctr92_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_sch_flg_rlt1           :  8,    //   7: 0
    c4_sch_flg_rlt2           :  8,    //  15: 8
    c4_sch_flg_rlt3           :  8,    //  23:16
    c4_sch_flg_rlt4           :  8;    //  31:24
}CTOP_CTRL_DPE_CTR92_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A118    ctr93_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_sch_flg_rlt5           :  8,    //   7: 0
    c4_sch_flg_rlt6           :  8,    //  15: 8
    c4_bist_phy_in_ok1        :  1,    //     16
    c4_bist_phy_in_ok2        :  1,    //     17
    c4_bist_phy_in_ok3        :  1,    //     18
    c4_bist_phy_in_ok4        :  1,    //     19
    c4_bist_phy_in_ok5        :  1,    //     20
    c4_bist_phy_in_ok6        :  1,    //     21
                              : 10;    //  31:22 reserved
}CTOP_CTRL_DPE_CTR93_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A11C    ctr94_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link_tp1               :  1,    //      0
    c4_link_tp2               :  1,    //      1
    c4_link_tp3               :  1,    //      2
    c4_link_tp4               :  1,    //      3
    c4_link_tp5               :  1,    //      4
    c4_link_tp6               :  1,    //      5
                              :  1,    //      6 reserved
    c4_pll_lock               :  1,    //      7
    c4_vx1_lockn_tomain       :  1,    //      8
                              : 23;    //   31:9 reserved
}CTOP_CTRL_DPE_CTR94_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A120    ctr95_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_ber_match0             :  1,    //      0
    c4_ber_match1             :  1,    //      1
    c4_ber_match2             :  1,    //      2
    c4_ber_match3             :  1,    //      3
    c4_ber_match4             :  1,    //      4
    c4_ber_match5             :  1,    //      5
    c4_ber_match6             :  1,    //      6
    c4_ber_match7             :  1,    //      7
    c4_ber_match8             :  1,    //      8
    c4_ber_match9             :  1,    //      9
    c4_ber_match10            :  1,    //     10
    c4_ber_match11            :  1,    //     11
    c4_ber_match12            :  1,    //     12
    c4_ber_match13            :  1,    //     13
    c4_ber_match14            :  1,    //     14
    c4_ber_match15            :  1,    //     15
    c4_ber_match16            :  1,    //     16
    c4_ber_match17            :  1,    //     17
    c4_ber_match18            :  1,    //     18
    c4_ber_match19            :  1,    //     19
    c4_ber_match20            :  1,    //     20
    c4_ber_match21            :  1,    //     21
    c4_ber_match22            :  1,    //     22
    c4_ber_match23            :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTR95_RO_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A124    ctop_dpe_r73 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_bist_sch_en0           :  1,    //      0
    c4_bist_sch_en1           :  1,    //      1
    c4_bist_sch_en2           :  1,    //      2
    c4_bist_sch_en3           :  1,    //      3
    c4_bist_sch_en4           :  1,    //      4
    c4_bist_sch_en5           :  1,    //      5
    c4_bist_sch_en6           :  1,    //      6
    c4_bist_sch_en7           :  1,    //      7
    c4_bist_sch_en8           :  1,    //      8
    c4_bist_sch_en9           :  1,    //      9
    c4_bist_sch_en10          :  1,    //     10
    c4_bist_sch_en11          :  1,    //     11
    c4_bist_sch_en12          :  1,    //     12
    c4_bist_sch_en13          :  1,    //     13
    c4_bist_sch_en14          :  1,    //     14
    c4_bist_sch_en15          :  1,    //     15
    c4_bist_sch_en16          :  1,    //     16
    c4_bist_sch_en17          :  1,    //     17
    c4_bist_sch_en18          :  1,    //     18
    c4_bist_sch_en19          :  1,    //     19
    c4_bist_sch_en20          :  1,    //     20
    c4_bist_sch_en21          :  1,    //     21
    c4_bist_sch_en22          :  1,    //     22
    c4_bist_sch_en23          :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R73_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A128    ctop_dpe_r74 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_reserve                :  8,    //   7: 0
                              :  8,    //  15: 8 reserved
    c4_vtx_link_clk_sel       :  1,    //     16
    c4_vtx_dftoccreset        :  1,    //     17
    c4_vtx_dftoccbypass       :  1,    //     18
    c4_vtx_dftatspeeden       :  1,    //     19
    c4_bist_rstb              :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R74_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A12C    ctop_dpe_r75 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4tx_output_sel1      :  3,    //   2: 0
                              :  5,    //   7: 3 reserved
    reg_c4tx_output_sel       :  5,    //  12: 8
                              : 19;    //  31:13 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R75_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A130    rxclkdrv_dmd ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_c4tx_pdb     :  1,    //      0
    reg_rxclkdrv_c4tx_smv     :  1,    //      1
                              : 30;    //   31:2 reserved
}CTOP_CTRL_DPE_RXCLKDRV_DMD_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A134    displl_phase ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    disp_clk_p0_gate_en       :  1,    //      0
    disp_clk_ps_gate_en       :  1,    //      1
                              :  2,    //   3: 2 reserved
    phase_sel_disp_clk        :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    disp_clk_sel              :  1,    //      8
                              : 23;    //   31:9 reserved
}CTOP_CTRL_DPE_DISPLL_PHASE_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A138    ctop_dpe_r78 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_use_cpu_gpio_13_1     :  1,    //      1
    reg_use_cpu_gpio_13_2     :  1,    //      2
    reg_use_cpu_gpio_13_3     :  1,    //      3
    reg_use_cpu_gpio_13_4     :  1,    //      4
    reg_use_cpu_gpio_13_5     :  1,    //      5
    reg_use_cpu_gpio_13_6     :  1,    //      6
                              :  1,    //      7 reserved
    reg_use_i2c8_en           :  1,    //      8
    reg_en_eb_addr            :  1,    //      9
    reg_aud_sub_en            :  1,    //     10
    reg_use_crc_interrupt     :  1,    //     11
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R78_M19A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_A13C    ctop_dpe_r79 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pll_rst_g              :  1,    //      0
                              : 31;    //   31:1 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R79_M19A0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
UINT32                                                 _rsvd_00[   2] ;         // 0xC930_A000 ~ 0xC930_A004
CTOP_CTRL_DPE_CTOP_DPE_R02_M19A0_T           ctop_dpe_r02             ;         // 0xC930_A008
CTOP_CTRL_DPE_CTOP_DPE_R03_M19A0_T           ctop_dpe_r03             ;         // 0xC930_A00C
CTOP_CTRL_DPE_CTOP_DPE_R04_M19A0_T           ctop_dpe_r04             ;         // 0xC930_A010
CTOP_CTRL_DPE_CTOP_DPE_R05_M19A0_T           ctop_dpe_r05             ;         // 0xC930_A014
CTOP_CTRL_DPE_CTOP_DPE_R06_M19A0_T           ctop_dpe_r06             ;         // 0xC930_A018
CTOP_CTRL_DPE_CTOP_DPE_R07_M19A0_T           ctop_dpe_r07             ;         // 0xC930_A01C
CTOP_CTRL_DPE_CTOP_DPE_R08_M19A0_T           ctop_dpe_r08             ;         // 0xC930_A020
CTOP_CTRL_DPE_CTOP_DPE_R09_M19A0_T           ctop_dpe_r09             ;         // 0xC930_A024
CTOP_CTRL_DPE_CTOP_DPE_R10_M19A0_T           ctop_dpe_r10             ;         // 0xC930_A028
CTOP_CTRL_DPE_CTOP_DPE_R11_M19A0_T           ctop_dpe_r11             ;         // 0xC930_A02C
CTOP_CTRL_DPE_CTOP_DPE_R12_M19A0_T           ctop_dpe_r12             ;         // 0xC930_A030
CTOP_CTRL_DPE_CTOP_DPE_R13_M19A0_T           ctop_dpe_r13             ;         // 0xC930_A034
CTOP_CTRL_DPE_CTOP_DPE_R14_M19A0_T           ctop_dpe_r14             ;         // 0xC930_A038
CTOP_CTRL_DPE_CTOP_DPE_R15_M19A0_T           ctop_dpe_r15             ;         // 0xC930_A03C
CTOP_CTRL_DPE_CTOP_DPE_R16_M19A0_T           ctop_dpe_r16             ;         // 0xC930_A040
CTOP_CTRL_DPE_CTOP_DPE_R17_M19A0_T           ctop_dpe_r17             ;         // 0xC930_A044
CTOP_CTRL_DPE_CTOP_DPE_R18_M19A0_T           ctop_dpe_r18             ;         // 0xC930_A048
CTOP_CTRL_DPE_CTOP_DPE_R19_M19A0_T           ctop_dpe_r19             ;         // 0xC930_A04C
CTOP_CTRL_DPE_CTOP_DPE_R20_M19A0_T           ctop_dpe_r20             ;         // 0xC930_A050
CTOP_CTRL_DPE_CTOP_DPE_R21_M19A0_T           ctop_dpe_r21             ;         // 0xC930_A054
CTOP_CTRL_DPE_CTOP_DPE_R22_M19A0_T           ctop_dpe_r22             ;         // 0xC930_A058
CTOP_CTRL_DPE_CTOP_DPE_R23_M19A0_T           ctop_dpe_r23             ;         // 0xC930_A05C
CTOP_CTRL_DPE_CTOP_DPE_R24_M19A0_T           ctop_dpe_r24             ;         // 0xC930_A060
CTOP_CTRL_DPE_CTOP_DPE_R25_M19A0_T           ctop_dpe_r25             ;         // 0xC930_A064
CTOP_CTRL_DPE_CTOP_DPE_R26_M19A0_T           ctop_dpe_r26             ;         // 0xC930_A068
CTOP_CTRL_DPE_CTOP_DPE_R27_M19A0_T           ctop_dpe_r27             ;         // 0xC930_A06C
CTOP_CTRL_DPE_CTOP_DPE_R28_M19A0_T           ctop_dpe_r28             ;         // 0xC930_A070
CTOP_CTRL_DPE_CTOP_DPE_R29_M19A0_T           ctop_dpe_r29             ;         // 0xC930_A074
CTOP_CTRL_DPE_CTOP_DPE_R30_M19A0_T           ctop_dpe_r30             ;         // 0xC930_A078
CTOP_CTRL_DPE_CTOP_DPE_R31_M19A0_T           ctop_dpe_r31             ;         // 0xC930_A07C
CTOP_CTRL_DPE_CTOP_DPE_R32_M19A0_T           ctop_dpe_r32             ;         // 0xC930_A080
CTOP_CTRL_DPE_CTOP_DPE_R33_M19A0_T           ctop_dpe_r33             ;         // 0xC930_A084
CTOP_CTRL_DPE_CTOP_DPE_R34_M19A0_T           ctop_dpe_r34             ;         // 0xC930_A088
CTOP_CTRL_DPE_CTOP_DPE_R35_M19A0_T           ctop_dpe_r35             ;         // 0xC930_A08C
CTOP_CTRL_DPE_CTOP_DPE_R36_M19A0_T           ctop_dpe_r36             ;         // 0xC930_A090
CTOP_CTRL_DPE_CTOP_DPE_R37_M19A0_T           ctop_dpe_r37             ;         // 0xC930_A094
UINT32                                                 _rsvd_01[   1] ;         // 0xC930_A098
CTOP_CTRL_DPE_CTOP_DPE_R39_M19A0_T           ctop_dpe_r39             ;         // 0xC930_A09C
CTOP_CTRL_DPE_CTOP_DPE_R40_M19A0_T           ctop_dpe_r40             ;         // 0xC930_A0A0
CTOP_CTRL_DPE_CTOP_DPE_R41_M19A0_T           ctop_dpe_r41             ;         // 0xC930_A0A4
CTOP_CTRL_DPE_CTOP_DPE_R42_M19A0_T           ctop_dpe_r42             ;         // 0xC930_A0A8
CTOP_CTRL_DPE_CTOP_DPE_R43_M19A0_T           ctop_dpe_r43             ;         // 0xC930_A0AC
CTOP_CTRL_DPE_CTOP_DPE_R44_M19A0_T           ctop_dpe_r44             ;         // 0xC930_A0B0
CTOP_CTRL_DPE_CTOP_DPE_R45_M19A0_T           ctop_dpe_r45             ;         // 0xC930_A0B4
CTOP_CTRL_DPE_CTOP_DPE_R46_M19A0_T           ctop_dpe_r46             ;         // 0xC930_A0B8
CTOP_CTRL_DPE_CTOP_DPE_R47_M19A0_T           ctop_dpe_r47             ;         // 0xC930_A0BC
CTOP_CTRL_DPE_CTOP_DPE_R48_M19A0_T           ctop_dpe_r48             ;         // 0xC930_A0C0
CTOP_CTRL_DPE_CTOP_DPE_R49_M19A0_T           ctop_dpe_r49             ;         // 0xC930_A0C4
CTOP_CTRL_DPE_CTOP_DPE_R50_M19A0_T           ctop_dpe_r50             ;         // 0xC930_A0C8
CTOP_CTRL_DPE_CTOP_DPE_R51_M19A0_T           ctop_dpe_r51             ;         // 0xC930_A0CC
CTOP_CTRL_DPE_CTOP_DPE_R52_M19A0_T           ctop_dpe_r52             ;         // 0xC930_A0D0
CTOP_CTRL_DPE_CTOP_DPE_R53_M19A0_T           ctop_dpe_r53             ;         // 0xC930_A0D4
CTOP_CTRL_DPE_CTOP_DPE_R54_M19A0_T           ctop_dpe_r54             ;         // 0xC930_A0D8
CTOP_CTRL_DPE_CTOP_DPE_R55_M19A0_T           ctop_dpe_r55             ;         // 0xC930_A0DC
CTOP_CTRL_DPE_CTOP_DPE_R56_M19A0_T           ctop_dpe_r56             ;         // 0xC930_A0E0
CTOP_CTRL_DPE_CTOP_DPE_R57_M19A0_T           ctop_dpe_r57             ;         // 0xC930_A0E4
CTOP_CTRL_DPE_CTOP_DPE_R58_M19A0_T           ctop_dpe_r58             ;         // 0xC930_A0E8
CTOP_CTRL_DPE_CTOP_DPE_R59_M19A0_T           ctop_dpe_r59             ;         // 0xC930_A0EC
CTOP_CTRL_DPE_CTOP_DPE_R60_M19A0_T           ctop_dpe_r60             ;         // 0xC930_A0F0
CTOP_CTRL_DPE_CTOP_DPE_R61_M19A0_T           ctop_dpe_r61             ;         // 0xC930_A0F4
CTOP_CTRL_DPE_CTOP_DPE_R62_M19A0_T           ctop_dpe_r62             ;         // 0xC930_A0F8
CTOP_CTRL_DPE_CTR86_RO_M19A0_T               ctr86_ro                 ;         // 0xC930_A0FC
CTOP_CTRL_DPE_CTR87_RO_M19A0_T               ctr87_ro                 ;         // 0xC930_A100
CTOP_CTRL_DPE_CTR88_RO_M19A0_T               ctr88_ro                 ;         // 0xC930_A104
CTOP_CTRL_DPE_CTR89_RO_M19A0_T               ctr89_ro                 ;         // 0xC930_A108
CTOP_CTRL_DPE_CTR90_RO_M19A0_T               ctr90_ro                 ;         // 0xC930_A10C
CTOP_CTRL_DPE_CTR91_RO_M19A0_T               ctr91_ro                 ;         // 0xC930_A110
CTOP_CTRL_DPE_CTR92_RO_M19A0_T               ctr92_ro                 ;         // 0xC930_A114
CTOP_CTRL_DPE_CTR93_RO_M19A0_T               ctr93_ro                 ;         // 0xC930_A118
CTOP_CTRL_DPE_CTR94_RO_M19A0_T               ctr94_ro                 ;         // 0xC930_A11C
CTOP_CTRL_DPE_CTR95_RO_M19A0_T               ctr95_ro                 ;         // 0xC930_A120
CTOP_CTRL_DPE_CTOP_DPE_R73_M19A0_T           ctop_dpe_r73             ;         // 0xC930_A124
CTOP_CTRL_DPE_CTOP_DPE_R74_M19A0_T           ctop_dpe_r74             ;         // 0xC930_A128
CTOP_CTRL_DPE_CTOP_DPE_R75_M19A0_T           ctop_dpe_r75             ;         // 0xC930_A12C
CTOP_CTRL_DPE_RXCLKDRV_DMD_M19A0_T           rxclkdrv_dmd             ;         // 0xC930_A130
CTOP_CTRL_DPE_DISPLL_PHASE_M19A0_T           displl_phase             ;         // 0xC930_A134
CTOP_CTRL_DPE_CTOP_DPE_R78_M19A0_T           ctop_dpe_r78             ;         // 0xC930_A138
CTOP_CTRL_DPE_CTOP_DPE_R79_M19A0_T           ctop_dpe_r79             ;         // 0xC930_A13C
} CTOP_CTRL_DPE_REG_M19A0_T;
/* 77 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_DPE_M19A0_REG_H_ */

/* from 'M16P3_CTOP_Register_Manual_136.xlsm'  2018.4.18  KST by LGSiCRDV V2.2A*/

