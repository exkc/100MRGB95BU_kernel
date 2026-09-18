#ifndef _CTOP_CTRL_DPE_O20A0_REG_H_
#define _CTOP_CTRL_DPE_O20A0_REG_H_

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
    0xC930_F808    ctop_dpe_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_lockn_sel      :  1,    //      0
    reg_c4_vx1_lockn_frmain   :  1,    //      1
    reg_c4_sel_clk            :  1,    //      2
                              :  1,    //      3 reserved
    reg_c4_sel_plllock        :  1,    //      4
    reg_c4_testlock_ctl       :  1,    //      5
    reg_c4_lock_ext           :  1,    //      6
                              : 25;    //   31:7 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R02_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F80C    ctop_dpe_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_itune_ch0          :  3,    //   2: 0
    reg_c4_itune_ch1          :  3,    //   5: 3
    reg_c4_itune_ch2          :  3,    //   8: 6
    reg_c4_itune_ch3          :  3,    //  11: 9
    reg_c4_itune_ch4          :  3,    //  14:12
    reg_c4_itune_ch5          :  3,    //  17:15
    reg_c4_itune_ch6          :  3,    //  20:18
    reg_c4_itune_ch7          :  3,    //  23:21
    reg_c4_itune_ch8          :  3,    //  26:24
    reg_c4_itune_ch9          :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R03_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F810    ctop_dpe_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_itune_ch10         :  3,    //   2: 0
    reg_c4_itune_ch11         :  3,    //   5: 3
    reg_c4_itune_ch12         :  3,    //   8: 6
    reg_c4_itune_ch13         :  3,    //  11: 9
    reg_c4_itune_ch14         :  3,    //  14:12
    reg_c4_itune_ch15         :  3,    //  17:15
    reg_c4_itune_ch16         :  3,    //  20:18
    reg_c4_itune_ch17         :  3,    //  23:21
    reg_c4_itune_ch18         :  3,    //  26:24
    reg_c4_itune_ch19         :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R04_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F814    ctop_dpe_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_itune_ch20         :  3,    //   2: 0
    reg_c4_itune_ch21         :  3,    //   5: 3
    reg_c4_itune_ch22         :  3,    //   8: 6
    reg_c4_itune_ch23         :  3,    //  11: 9
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R05_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F818    ctop_dpe_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_flip_en_ch0        :  1,    //      0
    reg_c4_flip_en_ch1        :  1,    //      1
    reg_c4_flip_en_ch2        :  1,    //      2
    reg_c4_flip_en_ch3        :  1,    //      3
    reg_c4_flip_en_ch4        :  1,    //      4
    reg_c4_flip_en_ch5        :  1,    //      5
    reg_c4_flip_en_ch6        :  1,    //      6
    reg_c4_flip_en_ch7        :  1,    //      7
    reg_c4_flip_en_ch8        :  1,    //      8
    reg_c4_flip_en_ch9        :  1,    //      9
    reg_c4_flip_en_ch10       :  1,    //     10
    reg_c4_flip_en_ch11       :  1,    //     11
    reg_c4_flip_en_ch12       :  1,    //     12
    reg_c4_flip_en_ch13       :  1,    //     13
    reg_c4_flip_en_ch14       :  1,    //     14
    reg_c4_flip_en_ch15       :  1,    //     15
    reg_c4_flip_en_ch16       :  1,    //     16
    reg_c4_flip_en_ch17       :  1,    //     17
    reg_c4_flip_en_ch18       :  1,    //     18
    reg_c4_flip_en_ch19       :  1,    //     19
    reg_c4_flip_en_ch20       :  1,    //     20
    reg_c4_flip_en_ch21       :  1,    //     21
    reg_c4_flip_en_ch22       :  1,    //     22
    reg_c4_flip_en_ch23       :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R06_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F81C    ctop_dpe_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pemp_ch0           :  3,    //   2: 0
    reg_c4_pemp_ch1           :  3,    //   5: 3
    reg_c4_pemp_ch2           :  3,    //   8: 6
    reg_c4_pemp_ch3           :  3,    //  11: 9
    reg_c4_pemp_ch4           :  3,    //  14:12
    reg_c4_pemp_ch5           :  3,    //  17:15
    reg_c4_pemp_ch6           :  3,    //  20:18
    reg_c4_pemp_ch7           :  3,    //  23:21
    reg_c4_pemp_ch8           :  3,    //  26:24
    reg_c4_pemp_ch9           :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R07_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F820    ctop_dpe_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pemp_ch10          :  3,    //   2: 0
    reg_c4_pemp_ch11          :  3,    //   5: 3
    reg_c4_pemp_ch12          :  3,    //   8: 6
    reg_c4_pemp_ch13          :  3,    //  11: 9
    reg_c4_pemp_ch14          :  3,    //  14:12
    reg_c4_pemp_ch15          :  3,    //  17:15
    reg_c4_pemp_ch16          :  3,    //  20:18
    reg_c4_pemp_ch17          :  3,    //  23:21
    reg_c4_pemp_ch18          :  3,    //  26:24
    reg_c4_pemp_ch19          :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R08_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F824    ctop_dpe_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pemp_ch20          :  3,    //   2: 0
    reg_c4_pemp_ch21          :  3,    //   5: 3
    reg_c4_pemp_ch22          :  3,    //   8: 6
    reg_c4_pemp_ch23          :  3,    //  11: 9
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R09_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F828    ctop_dpe_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_lock_samp_ctl      :  2,    //   1: 0
    reg_c4_lock_div_ctl       :  2,    //   3: 2
                              : 12,    //  15: 4 reserved
    reg_c4_sel_rstb           :  1,    //     16
                              :  7,    //  23:17 reserved
    reg_c4_rstb_ext           :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_c4_pll_rstb_g         :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R10_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F82C    ctop_dpe_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link0_en           :  1,    //      0
    reg_c4_link1_en           :  1,    //      1
    reg_c4_link2_en           :  1,    //      2
    reg_c4_link3_en           :  1,    //      3
    reg_c4_link4_en           :  1,    //      4
    reg_c4_link5_en           :  1,    //      5
    reg_c4_link6_en           :  1,    //      6
    reg_c4_link7_en           :  1,    //      7
    reg_c4_link8_en           :  1,    //      8
    reg_c4_link9_en           :  1,    //      9
    reg_c4_link10_en          :  1,    //     10
    reg_c4_link11_en          :  1,    //     11
    reg_c4_link12_en          :  1,    //     12
    reg_c4_link13_en          :  1,    //     13
    reg_c4_link14_en          :  1,    //     14
    reg_c4_link15_en          :  1,    //     15
    reg_c4_link16_en          :  1,    //     16
    reg_c4_link17_en          :  1,    //     17
    reg_c4_link18_en          :  1,    //     18
    reg_c4_link19_en          :  1,    //     19
    reg_c4_link20_en          :  1,    //     20
    reg_c4_link21_en          :  1,    //     21
    reg_c4_link22_en          :  1,    //     22
    reg_c4_link23_en          :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R11_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F830    ctop_dpe_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_epi_lvds_drv_en    :  1,    //      0
    reg_c4_bytemode           :  2,    //   2: 1
    reg_c4_term_en            :  1,    //      3
    reg_c4_adj_term           :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_c4_rf                 :  1,    //      8
    reg_c4_sw_rext            :  1,    //      9
                              :  2,    //  11:10 reserved
    reg_c4_epi10_en           :  1,    //     12
                              :  2,    //  14:13 reserved
    reg_c4_lp_en              :  1,    //     15
                              : 16;    //  31:16 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R12_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F834    ctop_dpe_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_rstn_vtxlink0_en   :  1,    //      0
    reg_c4_rstn_vtxlink1_en   :  1,    //      1
    reg_c4_rstn_vtxlink2_en   :  1,    //      2
    reg_c4_rstn_vtxlink3_en   :  1,    //      3
    reg_c4_rstn_vtxlink4_en   :  1,    //      4
    reg_c4_rstn_vtxlink5_en   :  1,    //      5
    reg_c4_sel_clkpix0        :  3,    //   8: 6
    reg_c4_sel_clkpix1        :  3,    //  11: 9
    reg_c4_sel_clkpix2        :  3,    //  14:12
    reg_c4_sel_clkpix3        :  3,    //  17:15
    reg_c4_sel_clkpix4        :  3,    //  20:18
    reg_c4_sel_clkpix5        :  3,    //  23:21
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R13_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F838    ctop_dpe_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_count_txlock0      : 13,    //  12: 0
    reg_c4_count_txlock1      : 13,    //  25:13
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R14_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F83C    ctop_dpe_r15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_count_txlock2      : 13,    //  12: 0
    reg_c4_count_txlock3      : 13,    //  25:13
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R15_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F840    ctop_dpe_r16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_count_txlock4      : 13,    //  12: 0
    reg_c4_count_txlock5      : 13,    //  25:13
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R16_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F844    ctop_dpe_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_count_rxlock0      :  6,    //   5: 0
    reg_c4_count_rxlock1      :  6,    //  11: 6
    reg_c4_count_rxlock2      :  6,    //  17:12
    reg_c4_count_rxlock3      :  6,    //  23:18
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R17_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F848    ctop_dpe_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_count_rxlock4      :  6,    //   5: 0
    reg_c4_count_rxlock5      :  6,    //  11: 6
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R18_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F84C    ctop_dpe_r19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_read_address_offset0: 2,    //   1: 0
    reg_c4_read_address_offset1: 2,    //   3: 2
    reg_c4_read_address_offset2: 2,    //   5: 4
    reg_c4_read_address_offset3: 2,    //   7: 6
    reg_c4_read_address_offset4: 2,    //   9: 8
    reg_c4_read_address_offset5: 2,    //  11:10
    reg_c4_clk_pix1x_rf0      :  1,    //     12
    reg_c4_clk_pix1x_rf1      :  1,    //     13
    reg_c4_clk_pix1x_rf2      :  1,    //     14
    reg_c4_clk_pix1x_rf3      :  1,    //     15
    reg_c4_clk_pix1x_rf4      :  1,    //     16
    reg_c4_clk_pix1x_rf5      :  1,    //     17
    reg_c4_txlock_fixen0      :  2,    //  19:18
    reg_c4_txlock_fixen1      :  2,    //  21:20
    reg_c4_txlock_fixen2      :  2,    //  23:22
    reg_c4_txlock_fixen3      :  2,    //  25:24
    reg_c4_txlock_fixen4      :  2,    //  27:26
    reg_c4_txlock_fixen5      :  2,    //  29:28
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R19_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F850    ctop_dpe_r20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_mode0         :  2,    //   1: 0
    reg_c4_test_mode1         :  2,    //   3: 2
    reg_c4_test_mode2         :  2,    //   5: 4
    reg_c4_test_mode3         :  2,    //   7: 6
    reg_c4_test_mode4         :  2,    //   9: 8
    reg_c4_test_mode5         :  2,    //  11:10
    reg_c4_read_lane_sel0     :  2,    //  13:12
    reg_c4_read_lane_sel1     :  2,    //  15:14
    reg_c4_read_lane_sel2     :  2,    //  17:16
    reg_c4_read_lane_sel3     :  2,    //  19:18
    reg_c4_read_lane_sel4     :  2,    //  21:20
    reg_c4_read_lane_sel5     :  2,    //  23:22
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R20_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F854    ctop_dpe_r21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_read_tp_sel0       :  4,    //   3: 0
    reg_c4_read_tp_sel1       :  4,    //   7: 4
    reg_c4_read_tp_sel2       :  4,    //  11: 8
    reg_c4_read_tp_sel3       :  4,    //  15:12
    reg_c4_read_tp_sel4       :  4,    //  19:16
    reg_c4_read_tp_sel5       :  4,    //  23:20
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R21_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F858    ctop_dpe_r22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_man_pattern_en :  1,    //      0
    reg_c4_vtx_man_pattern_sel:  4,    //   4: 1
    reg_c4_vtx_sync_inv       :  1,    //      5
    reg_c4_vtx_sync_chk_clk_en:  1,    //      6
    reg_c4_vtx_sync_chk_rstb  :  1,    //      7
    reg_c4_vtx_pattern_clk_en :  1,    //      8
                              : 23;    //   31:9 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R22_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F85C    ctop_dpe_r23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_tvblank        : 12,    //  11: 0
    reg_c4_vtx_tvact          : 12,    //  23:12
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R23_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F860    ctop_dpe_r24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_tvfp           : 11,    //  10: 0
    reg_c4_vtx_tvpw           :  8,    //  18:11
                              : 13;    //  31:19 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R24_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F864    ctop_dpe_r25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_thblank        : 13,    //  12: 0
    reg_c4_vtx_thact          : 13,    //  25:13
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R25_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F868    ctop_dpe_r26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_thfp           : 12,    //  11: 0
    reg_c4_vtx_thpw           :  8,    //  19:12
                              : 12;    //  31:20 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R26_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F86C    ctop_dpe_r27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_vsync_gen_sel0 :  1,    //      0
    reg_c4_vtx_vsync_gen_sel1 :  1,    //      1
    reg_c4_vtx_vsync_gen_sel2 :  1,    //      2
    reg_c4_vtx_vsync_gen_sel3 :  1,    //      3
    reg_c4_vtx_vsync_gen_sel4 :  1,    //      4
    reg_c4_vtx_vsync_gen_sel5 :  1,    //      5
    reg_c4_vtx_sync_pol0      :  1,    //      6
    reg_c4_vtx_sync_pol1      :  1,    //      7
    reg_c4_vtx_sync_pol2      :  1,    //      8
    reg_c4_vtx_sync_pol3      :  1,    //      9
    reg_c4_vtx_sync_pol4      :  1,    //     10
    reg_c4_vtx_sync_pol5      :  1,    //     11
    reg_c4_vtx_stuck_en0      :  1,    //     12
    reg_c4_vtx_stuck_en1      :  1,    //     13
    reg_c4_vtx_stuck_en2      :  1,    //     14
    reg_c4_vtx_stuck_en3      :  1,    //     15
    reg_c4_vtx_stuck_en4      :  1,    //     16
    reg_c4_vtx_stuck_en5      :  1,    //     17
    reg_c4_vtx_vsgen_en0      :  1,    //     18
    reg_c4_vtx_vsgen_en1      :  1,    //     19
    reg_c4_vtx_vsgen_en2      :  1,    //     20
    reg_c4_vtx_vsgen_en3      :  1,    //     21
    reg_c4_vtx_vsgen_en4      :  1,    //     22
    reg_c4_vtx_vsgen_en5      :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R27_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F870    ctop_dpe_r28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_input_stuck_en0:  1,    //      0
    reg_c4_vtx_input_stuck_en1:  1,    //      1
    reg_c4_vtx_input_stuck_en2:  1,    //      2
    reg_c4_vtx_input_stuck_en3:  1,    //      3
    reg_c4_vtx_input_stuck_en4:  1,    //      4
    reg_c4_vtx_input_stuck_en5:  1,    //      5
    reg_c4_vtx_input_stuck_val0: 1,    //      6
    reg_c4_vtx_input_stuck_val1: 1,    //      7
    reg_c4_vtx_input_stuck_val2: 1,    //      8
    reg_c4_vtx_input_stuck_val3: 1,    //      9
    reg_c4_vtx_input_stuck_val4: 1,    //     10
    reg_c4_vtx_input_stuck_val5: 1,    //     11
    reg_c4_vtx_den_mincnt0    :  2,    //  13:12
    reg_c4_vtx_den_mincnt1    :  2,    //  15:14
    reg_c4_vtx_den_mincnt2    :  2,    //  17:16
    reg_c4_vtx_den_mincnt3    :  2,    //  19:18
    reg_c4_vtx_den_mincnt4    :  2,    //  21:20
    reg_c4_vtx_den_mincnt5    :  2,    //  23:22
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R28_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F874    ctop_dpe_r29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_vs_interval0   :  3,    //   2: 0
    reg_c4_vtx_vs_interval1   :  3,    //   5: 3
    reg_c4_vtx_vs_interval2   :  3,    //   8: 6
    reg_c4_vtx_vs_interval3   :  3,    //  11: 9
    reg_c4_vtx_vs_interval4   :  3,    //  14:12
    reg_c4_vtx_vs_interval5   :  3,    //  17:15
                              : 14;    //  31:18 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R29_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F878    ctop_dpe_r30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_bist_en            :  1,    //      0
    reg_c4_bist_clk_en        :  1,    //      1
    reg_c4_err_inj_en         :  1,    //      2
    reg_c4_err_inj_mode       :  1,    //      3
    reg_c4_err_inj_ext        :  1,    //      4
    reg_c4_err_inj_num        :  4,    //   8: 5
    reg_c4_err_inj_per        :  4,    //  12: 9
    reg_c4_err_inj_st_per     : 10,    //  22:13
                              :  9;    //  31:23 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R30_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F87C    ctop_dpe_r31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_en0            :  1,    //      0
    reg_c4_ber_en1            :  1,    //      1
    reg_c4_ber_en2            :  1,    //      2
    reg_c4_ber_en3            :  1,    //      3
    reg_c4_ber_en4            :  1,    //      4
    reg_c4_ber_en5            :  1,    //      5
    reg_c4_ber_en6            :  1,    //      6
    reg_c4_ber_en7            :  1,    //      7
    reg_c4_ber_en8            :  1,    //      8
    reg_c4_ber_en9            :  1,    //      9
    reg_c4_ber_en10           :  1,    //     10
    reg_c4_ber_en11           :  1,    //     11
    reg_c4_ber_en12           :  1,    //     12
    reg_c4_ber_en13           :  1,    //     13
    reg_c4_ber_en14           :  1,    //     14
    reg_c4_ber_en15           :  1,    //     15
    reg_c4_ber_en16           :  1,    //     16
    reg_c4_ber_en17           :  1,    //     17
    reg_c4_ber_en18           :  1,    //     18
    reg_c4_ber_en19           :  1,    //     19
    reg_c4_ber_en20           :  1,    //     20
    reg_c4_ber_en21           :  1,    //     21
    reg_c4_ber_en22           :  1,    //     22
    reg_c4_ber_en23           :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R31_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F880    ctop_dpe_r32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_num_dat        :  2,    //   1: 0
    reg_c4_ber_num_err        :  4,    //   5: 2
    reg_c4_ber_rlt_sel        :  2,    //   7: 6
    reg_c4_sch_period         :  4,    //  11: 8
                              :  8,    //  19:12 reserved
    reg_c4_retimer_bypass_en  :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R32_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F884    ctop_dpe_r33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_sch_stable_cnt0    :  4,    //   3: 0
    reg_c4_sch_stable_cnt1    :  4,    //   7: 4
    reg_c4_sch_stable_cnt2    :  4,    //  11: 8
    reg_c4_sch_stable_cnt3    :  4,    //  15:12
    reg_c4_sch_stable_cnt4    :  4,    //  19:16
    reg_c4_sch_stable_cnt5    :  4,    //  23:20
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R33_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F888    ctop_dpe_r34 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_sch_wait_cnt0      :  4,    //   3: 0
    reg_c4_sch_wait_cnt1      :  4,    //   7: 4
    reg_c4_sch_wait_cnt2      :  4,    //  11: 8
    reg_c4_sch_wait_cnt3      :  4,    //  15:12
    reg_c4_sch_wait_cnt4      :  4,    //  19:16
    reg_c4_sch_wait_cnt5      :  4,    //  23:20
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R34_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F88C    ctop_dpe_r35 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_man_lockn_en0  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_c4_vtx_man_lockn_en1  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_c4_vtx_man_lockn_en2  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_c4_vtx_man_lockn_en3  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_c4_vtx_man_lockn_en4  :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_c4_vtx_man_lockn_en5  :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R35_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F890    ctop_dpe_r36 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_vtx_man_lockn0     :  1,    //      0
    reg_c4_vtx_man_lockn1     :  1,    //      1
    reg_c4_vtx_man_lockn2     :  1,    //      2
    reg_c4_vtx_man_lockn3     :  1,    //      3
    reg_c4_vtx_man_lockn4     :  1,    //      4
    reg_c4_vtx_man_lockn5     :  1,    //      5
    reg_c4_vtx_man_lockn6     :  1,    //      6
    reg_c4_vtx_man_lockn7     :  1,    //      7
    reg_c4_vtx_man_lockn8     :  1,    //      8
    reg_c4_vtx_man_lockn9     :  1,    //      9
    reg_c4_vtx_man_lockn10    :  1,    //     10
    reg_c4_vtx_man_lockn11    :  1,    //     11
    reg_c4_vtx_man_lockn12    :  1,    //     12
    reg_c4_vtx_man_lockn13    :  1,    //     13
    reg_c4_vtx_man_lockn14    :  1,    //     14
    reg_c4_vtx_man_lockn15    :  1,    //     15
    reg_c4_vtx_man_lockn16    :  1,    //     16
    reg_c4_vtx_man_lockn17    :  1,    //     17
    reg_c4_vtx_man_lockn18    :  1,    //     18
    reg_c4_vtx_man_lockn19    :  1,    //     19
    reg_c4_vtx_man_lockn20    :  1,    //     20
    reg_c4_vtx_man_lockn21    :  1,    //     21
    reg_c4_vtx_man_lockn22    :  1,    //     22
    reg_c4_vtx_man_lockn23    :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R36_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F894    ctop_dpe_r37 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_dout_rvs0      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_c4_ber_dout_rvs1      :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_c4_ber_dout_rvs2      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_c4_ber_dout_rvs3      :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_c4_ber_dout_rvs4      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_c4_ber_dout_rvs5      :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R37_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F89C    ctop_dpe_r39 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_wd_en              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_c4_sel_reg_p2s        :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_c4_sel_reg_clk        :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_c4_sel_lock           :  1,    //     12
                              : 19;    //  31:13 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R39_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8A0    ctop_dpe_r40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pdb                :  1,    //      0
    reg_c4_prbs_mode_sel      :  1,    //      1
    reg_c4_rstn_vtxlink       :  1,    //      2
    reg_c4_hbw_en             :  1,    //      3
                              :  3,    //   6: 4 reserved
    reg_c4_prbs_out_sel       :  2,    //   8: 7
    reg_c4_sc_ctl             :  2,    //  10: 9
    reg_c4_sel_mode           :  2,    //  12:11
    reg_c4_cih                :  3,    //  15:13
                              :  4,    //  19:16 reserved
    reg_c4_reserve_pll        :  6,    //  25:20
                              :  6;    //  31:26 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R40_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8A4    ctop_dpe_r41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_enc_off0           :  1,    //      0
    reg_c4_enc_off1           :  1,    //      1
    reg_c4_enc_off2           :  1,    //      2
    reg_c4_enc_off3           :  1,    //      3
    reg_c4_enc_off4           :  1,    //      4
    reg_c4_enc_off5           :  1,    //      5
    reg_c4_enc_rst0           :  1,    //      6
    reg_c4_enc_rst1           :  1,    //      7
    reg_c4_enc_rst2           :  1,    //      8
    reg_c4_enc_rst3           :  1,    //      9
    reg_c4_enc_rst4           :  1,    //     10
    reg_c4_enc_rst5           :  1,    //     11
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R41_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8A8    ctop_dpe_r42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_pdb_ch0            :  1,    //      0
    reg_c4_pdb_ch1            :  1,    //      1
    reg_c4_pdb_ch2            :  1,    //      2
    reg_c4_pdb_ch3            :  1,    //      3
    reg_c4_pdb_ch4            :  1,    //      4
    reg_c4_pdb_ch5            :  1,    //      5
    reg_c4_pdb_ch6            :  1,    //      6
    reg_c4_pdb_ch7            :  1,    //      7
    reg_c4_pdb_ch8            :  1,    //      8
    reg_c4_pdb_ch9            :  1,    //      9
    reg_c4_pdb_ch10           :  1,    //     10
    reg_c4_pdb_ch11           :  1,    //     11
    reg_c4_pdb_ch12           :  1,    //     12
    reg_c4_pdb_ch13           :  1,    //     13
    reg_c4_pdb_ch14           :  1,    //     14
    reg_c4_pdb_ch15           :  1,    //     15
    reg_c4_pdb_ch16           :  1,    //     16
    reg_c4_pdb_ch17           :  1,    //     17
    reg_c4_pdb_ch18           :  1,    //     18
    reg_c4_pdb_ch19           :  1,    //     19
    reg_c4_pdb_ch20           :  1,    //     20
    reg_c4_pdb_ch21           :  1,    //     21
    reg_c4_pdb_ch22           :  1,    //     22
    reg_c4_pdb_ch23           :  1,    //     23
    reg_c4_rf_lb_ckout0       :  1,    //     24
    reg_c4_rf_lb_ckout1       :  1,    //     25
    reg_c4_rf_lb_ckout2       :  1,    //     26
    reg_c4_rf_lb_ckout3       :  1,    //     27
    reg_c4_rf_lb_ckout4       :  1,    //     28
    reg_c4_rf_lb_ckout5       :  1,    //     29
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R42_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8AC    ctop_dpe_r43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_rf_lb_desck0       :  1,    //      0
    reg_c4_rf_lb_desck1       :  1,    //      1
    reg_c4_rf_lb_desck2       :  1,    //      2
    reg_c4_rf_lb_desck3       :  1,    //      3
    reg_c4_rf_lb_desck4       :  1,    //      4
    reg_c4_rf_lb_desck5       :  1,    //      5
    reg_c4_rf_lb_desck6       :  1,    //      6
    reg_c4_rf_lb_desck7       :  1,    //      7
    reg_c4_rf_lb_desck8       :  1,    //      8
    reg_c4_rf_lb_desck9       :  1,    //      9
    reg_c4_rf_lb_desck10      :  1,    //     10
    reg_c4_rf_lb_desck11      :  1,    //     11
    reg_c4_rf_lb_desck12      :  1,    //     12
    reg_c4_rf_lb_desck13      :  1,    //     13
    reg_c4_rf_lb_desck14      :  1,    //     14
    reg_c4_rf_lb_desck15      :  1,    //     15
    reg_c4_rf_lb_desck16      :  1,    //     16
    reg_c4_rf_lb_desck17      :  1,    //     17
    reg_c4_rf_lb_desck18      :  1,    //     18
    reg_c4_rf_lb_desck19      :  1,    //     19
    reg_c4_rf_lb_desck20      :  1,    //     20
    reg_c4_rf_lb_desck21      :  1,    //     21
    reg_c4_rf_lb_desck22      :  1,    //     22
    reg_c4_rf_lb_desck23      :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R43_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8B0    ctop_dpe_r44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 24,    //  23: 0 reserved
    reg_c4_scr_off0           :  1,    //     24
    reg_c4_scr_off1           :  1,    //     25
    reg_c4_scr_off2           :  1,    //     26
    reg_c4_scr_off3           :  1,    //     27
    reg_c4_scr_off4           :  1,    //     28
    reg_c4_scr_off5           :  1,    //     29
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R44_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8B4    ctop_dpe_r45 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_scr_rst0           :  1,    //      0
    reg_c4_scr_rst1           :  1,    //      1
    reg_c4_scr_rst2           :  1,    //      2
    reg_c4_scr_rst3           :  1,    //      3
    reg_c4_scr_rst4           :  1,    //      4
    reg_c4_scr_rst5           :  1,    //      5
                              : 26;    //   31:6 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R45_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8B8    ctop_dpe_r46 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_lb_ck_ctl0         :  2,    //   1: 0
    reg_c4_lb_ck_ctl1         :  2,    //   3: 2
    reg_c4_lb_ck_ctl2         :  2,    //   5: 4
    reg_c4_lb_ck_ctl3         :  2,    //   7: 6
    reg_c4_lb_ck_ctl4         :  2,    //   9: 8
    reg_c4_lb_ck_ctl5         :  2,    //  11:10
    reg_c4_lb_ck_ctl6         :  2,    //  13:12
    reg_c4_lb_ck_ctl7         :  2,    //  15:14
    reg_c4_lb_ck_ctl8         :  2,    //  17:16
    reg_c4_lb_ck_ctl9         :  2,    //  19:18
    reg_c4_lb_ck_ctl10        :  2,    //  21:20
    reg_c4_lb_ck_ctl11        :  2,    //  23:22
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R46_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8BC    ctop_dpe_r47 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_lb_ck_ctl12        :  2,    //   1: 0
    reg_c4_lb_ck_ctl13        :  2,    //   3: 2
    reg_c4_lb_ck_ctl14        :  2,    //   5: 4
    reg_c4_lb_ck_ctl15        :  2,    //   7: 6
    reg_c4_lb_ck_ctl16        :  2,    //   9: 8
    reg_c4_lb_ck_ctl17        :  2,    //  11:10
    reg_c4_lb_ck_ctl18        :  2,    //  13:12
    reg_c4_lb_ck_ctl19        :  2,    //  15:14
    reg_c4_lb_ck_ctl20        :  2,    //  17:16
    reg_c4_lb_ck_ctl21        :  2,    //  19:18
    reg_c4_lb_ck_ctl22        :  2,    //  21:20
    reg_c4_lb_ck_ctl23        :  2,    //  23:22
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R47_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8C0    ctop_dpe_r48 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di0           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R48_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8C4    ctop_dpe_r49 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di1           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R49_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8C8    ctop_dpe_r50 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di2           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R50_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8CC    ctop_dpe_r51 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di3           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R51_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8D0    ctop_dpe_r52 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di4           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R52_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8D4    ctop_dpe_r53 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_test_di5           : 28,    //  27: 0
                              :  4;    //  31:28 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R53_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8D8    ctop_dpe_r54 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_phy_reserve0       :  8,    //   7: 0
    reg_c4_phy_reserve1       :  8,    //  15: 8
    reg_c4_phy_reserve2       :  8,    //  23:16
    reg_c4_phy_reserve3       :  8;    //  31:24
}CTOP_CTRL_DPE_CTOP_DPE_R54_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8DC    ctop_dpe_r55 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_phy_reserve4       :  8,    //   7: 0
    reg_c4_phy_reserve5       :  8,    //  15: 8
                              : 16;    //  31:16 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R55_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8E0    ctop_dpe_r56 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_sch_mat_comp_en0   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_c4_sch_mat_comp_en1   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_c4_sch_mat_comp_en2   :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_c4_sch_mat_comp_en3   :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_c4_sch_mat_comp_en4   :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_c4_sch_mat_comp_en5   :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R56_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8E4    ctop_dpe_r57 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link_read_tp1      : 16,    //  15: 0
    reg_c4_link_read_tp0      : 16;    //  31:16
}CTOP_CTRL_DPE_CTOP_DPE_R57_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8E8    ctop_dpe_r58 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link_read_tp3      : 16,    //  15: 0
    reg_c4_link_read_tp2      : 16;    //  31:16
}CTOP_CTRL_DPE_CTOP_DPE_R58_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8EC    ctop_dpe_r59 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link_read_tp5      : 16,    //  15: 0
    reg_c4_link_read_tp4      : 16;    //  31:16
}CTOP_CTRL_DPE_CTOP_DPE_R59_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8F0    ctop_dpe_r60 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_stable0        :  1,    //      0
    reg_c4_ber_stable1        :  1,    //      1
    reg_c4_ber_stable2        :  1,    //      2
    reg_c4_ber_stable3        :  1,    //      3
    reg_c4_ber_stable4        :  1,    //      4
    reg_c4_ber_stable5        :  1,    //      5
    reg_c4_ber_stable6        :  1,    //      6
    reg_c4_ber_stable7        :  1,    //      7
    reg_c4_ber_stable8        :  1,    //      8
    reg_c4_ber_stable9        :  1,    //      9
    reg_c4_ber_stable10       :  1,    //     10
    reg_c4_ber_stable11       :  1,    //     11
    reg_c4_ber_stable12       :  1,    //     12
    reg_c4_ber_stable13       :  1,    //     13
    reg_c4_ber_stable14       :  1,    //     14
    reg_c4_ber_stable15       :  1,    //     15
    reg_c4_ber_stable16       :  1,    //     16
    reg_c4_ber_stable17       :  1,    //     17
    reg_c4_ber_stable18       :  1,    //     18
    reg_c4_ber_stable19       :  1,    //     19
    reg_c4_ber_stable20       :  1,    //     20
    reg_c4_ber_stable21       :  1,    //     21
    reg_c4_ber_stable22       :  1,    //     22
    reg_c4_ber_stable23       :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R60_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8F4    ctop_dpe_r61 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_chkdone0       :  1,    //      0
    reg_c4_ber_chkdone1       :  1,    //      1
    reg_c4_ber_chkdone2       :  1,    //      2
    reg_c4_ber_chkdone3       :  1,    //      3
    reg_c4_ber_chkdone4       :  1,    //      4
    reg_c4_ber_chkdone5       :  1,    //      5
    reg_c4_ber_chkdone6       :  1,    //      6
    reg_c4_ber_chkdone7       :  1,    //      7
    reg_c4_ber_chkdone8       :  1,    //      8
    reg_c4_ber_chkdone9       :  1,    //      9
    reg_c4_ber_chkdone10      :  1,    //     10
    reg_c4_ber_chkdone11      :  1,    //     11
    reg_c4_ber_chkdone12      :  1,    //     12
    reg_c4_ber_chkdone13      :  1,    //     13
    reg_c4_ber_chkdone14      :  1,    //     14
    reg_c4_ber_chkdone15      :  1,    //     15
    reg_c4_ber_chkdone16      :  1,    //     16
    reg_c4_ber_chkdone17      :  1,    //     17
    reg_c4_ber_chkdone18      :  1,    //     18
    reg_c4_ber_chkdone19      :  1,    //     19
    reg_c4_ber_chkdone20      :  1,    //     20
    reg_c4_ber_chkdone21      :  1,    //     21
    reg_c4_ber_chkdone22      :  1,    //     22
    reg_c4_ber_chkdone23      :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R61_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8F8    ctop_dpe_r62 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_chkpass0       :  1,    //      0
    reg_c4_ber_chkpass1       :  1,    //      1
    reg_c4_ber_chkpass2       :  1,    //      2
    reg_c4_ber_chkpass3       :  1,    //      3
    reg_c4_ber_chkpass4       :  1,    //      4
    reg_c4_ber_chkpass5       :  1,    //      5
    reg_c4_ber_chkpass6       :  1,    //      6
    reg_c4_ber_chkpass7       :  1,    //      7
    reg_c4_ber_chkpass8       :  1,    //      8
    reg_c4_ber_chkpass9       :  1,    //      9
    reg_c4_ber_chkpass10      :  1,    //     10
    reg_c4_ber_chkpass11      :  1,    //     11
    reg_c4_ber_chkpass12      :  1,    //     12
    reg_c4_ber_chkpass13      :  1,    //     13
    reg_c4_ber_chkpass14      :  1,    //     14
    reg_c4_ber_chkpass15      :  1,    //     15
    reg_c4_ber_chkpass16      :  1,    //     16
    reg_c4_ber_chkpass17      :  1,    //     17
    reg_c4_ber_chkpass18      :  1,    //     18
    reg_c4_ber_chkpass19      :  1,    //     19
    reg_c4_ber_chkpass20      :  1,    //     20
    reg_c4_ber_chkpass21      :  1,    //     21
    reg_c4_ber_chkpass22      :  1,    //     22
    reg_c4_ber_chkpass23      :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R62_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F8FC    ctr86_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_err_ofl0       :  1,    //      0
    reg_c4_ber_err_ofl1       :  1,    //      1
    reg_c4_ber_err_ofl2       :  1,    //      2
    reg_c4_ber_err_ofl3       :  1,    //      3
    reg_c4_ber_err_ofl4       :  1,    //      4
    reg_c4_ber_err_ofl5       :  1,    //      5
    reg_c4_ber_err_ofl6       :  1,    //      6
    reg_c4_ber_err_ofl7       :  1,    //      7
    reg_c4_ber_err_ofl8       :  1,    //      8
    reg_c4_ber_err_ofl9       :  1,    //      9
    reg_c4_ber_err_ofl10      :  1,    //     10
    reg_c4_ber_err_ofl11      :  1,    //     11
    reg_c4_ber_err_ofl12      :  1,    //     12
    reg_c4_ber_err_ofl13      :  1,    //     13
    reg_c4_ber_err_ofl14      :  1,    //     14
    reg_c4_ber_err_ofl15      :  1,    //     15
    reg_c4_ber_err_ofl16      :  1,    //     16
    reg_c4_ber_err_ofl17      :  1,    //     17
    reg_c4_ber_err_ofl18      :  1,    //     18
    reg_c4_ber_err_ofl19      :  1,    //     19
    reg_c4_ber_err_ofl20      :  1,    //     20
    reg_c4_ber_err_ofl21      :  1,    //     21
    reg_c4_ber_err_ofl22      :  1,    //     22
    reg_c4_ber_err_ofl23      :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTR86_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F900    ctr87_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_din_ok0        :  1,    //      0
    reg_c4_ber_din_ok1        :  1,    //      1
    reg_c4_ber_din_ok2        :  1,    //      2
    reg_c4_ber_din_ok3        :  1,    //      3
    reg_c4_ber_din_ok4        :  1,    //      4
    reg_c4_ber_din_ok5        :  1,    //      5
    reg_c4_ber_din_ok6        :  1,    //      6
    reg_c4_ber_din_ok7        :  1,    //      7
    reg_c4_ber_din_ok8        :  1,    //      8
    reg_c4_ber_din_ok9        :  1,    //      9
    reg_c4_ber_din_ok10       :  1,    //     10
    reg_c4_ber_din_ok11       :  1,    //     11
    reg_c4_ber_din_ok12       :  1,    //     12
    reg_c4_ber_din_ok13       :  1,    //     13
    reg_c4_ber_din_ok14       :  1,    //     14
    reg_c4_ber_din_ok15       :  1,    //     15
    reg_c4_ber_din_ok16       :  1,    //     16
    reg_c4_ber_din_ok17       :  1,    //     17
    reg_c4_ber_din_ok18       :  1,    //     18
    reg_c4_ber_din_ok19       :  1,    //     19
    reg_c4_ber_din_ok20       :  1,    //     20
    reg_c4_ber_din_ok21       :  1,    //     21
    reg_c4_ber_din_ok22       :  1,    //     22
    reg_c4_ber_din_ok23       :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTR87_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F904    ctr88_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_rlt0           : 10,    //   9: 0
    reg_c4_ber_rlt1           : 10,    //  19:10
    reg_c4_ber_rlt2           : 10,    //  29:20
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTR88_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F908    ctr89_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_rlt3           : 10,    //   9: 0
    reg_c4_ber_rlt4           : 10,    //  19:10
    reg_c4_ber_rlt5           : 10,    //  29:20
                              :  2;    //  31:30 reserved
}CTOP_CTRL_DPE_CTR89_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F90C    ctr90_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_st0            :  2,    //   1: 0
    reg_c4_ber_st1            :  2,    //   3: 2
    reg_c4_ber_st2            :  2,    //   5: 4
    reg_c4_ber_st3            :  2,    //   7: 6
    reg_c4_ber_st4            :  2,    //   9: 8
    reg_c4_ber_st5            :  2,    //  11:10
                              : 20;    //  31:12 reserved
}CTOP_CTRL_DPE_CTR90_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F910    ctr91_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_sch_rlt0           :  3,    //   2: 0
    reg_c4_sch_rlt1           :  3,    //   5: 3
    reg_c4_sch_rlt2           :  3,    //   8: 6
    reg_c4_sch_rlt3           :  3,    //  11: 9
    reg_c4_sch_rlt4           :  3,    //  14:12
    reg_c4_sch_rlt5           :  3,    //  17:15
                              : 14;    //  31:18 reserved
}CTOP_CTRL_DPE_CTR91_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F914    ctr92_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_sch_flg_rlt0       :  8,    //   7: 0
    reg_c4_sch_flg_rlt1       :  8,    //  15: 8
    reg_c4_sch_flg_rlt2       :  8,    //  23:16
    reg_c4_sch_flg_rlt3       :  8;    //  31:24
}CTOP_CTRL_DPE_CTR92_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F918    ctr93_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_sch_flg_rlt4       :  8,    //   7: 0
    reg_c4_sch_flg_rlt5       :  8,    //  15: 8
    reg_c4_bist_phy_in_ok0    :  1,    //     16
    reg_c4_bist_phy_in_ok1    :  1,    //     17
    reg_c4_bist_phy_in_ok2    :  1,    //     18
    reg_c4_bist_phy_in_ok3    :  1,    //     19
    reg_c4_bist_phy_in_ok4    :  1,    //     20
    reg_c4_bist_phy_in_ok5    :  1,    //     21
                              : 10;    //  31:22 reserved
}CTOP_CTRL_DPE_CTR93_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F91C    ctr94_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link_tp0           :  1,    //      0
    reg_c4_link_tp1           :  1,    //      1
    reg_c4_link_tp2           :  1,    //      2
    reg_c4_link_tp3           :  1,    //      3
    reg_c4_link_tp4           :  1,    //      4
    reg_c4_link_tp5           :  1,    //      5
                              :  1,    //      6 reserved
    reg_c4_pll_lock           :  1,    //      7
                              : 24;    //   31:8 reserved
}CTOP_CTRL_DPE_CTR94_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F920    ctr95_ro ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_ber_match0         :  1,    //      0
    reg_c4_ber_match1         :  1,    //      1
    reg_c4_ber_match2         :  1,    //      2
    reg_c4_ber_match3         :  1,    //      3
    reg_c4_ber_match4         :  1,    //      4
    reg_c4_ber_match5         :  1,    //      5
    reg_c4_ber_match6         :  1,    //      6
    reg_c4_ber_match7         :  1,    //      7
    reg_c4_ber_match8         :  1,    //      8
    reg_c4_ber_match9         :  1,    //      9
    reg_c4_ber_match10        :  1,    //     10
    reg_c4_ber_match11        :  1,    //     11
    reg_c4_ber_match12        :  1,    //     12
    reg_c4_ber_match13        :  1,    //     13
    reg_c4_ber_match14        :  1,    //     14
    reg_c4_ber_match15        :  1,    //     15
    reg_c4_ber_match16        :  1,    //     16
    reg_c4_ber_match17        :  1,    //     17
    reg_c4_ber_match18        :  1,    //     18
    reg_c4_ber_match19        :  1,    //     19
    reg_c4_ber_match20        :  1,    //     20
    reg_c4_ber_match21        :  1,    //     21
    reg_c4_ber_match22        :  1,    //     22
    reg_c4_ber_match23        :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTR95_RO_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F924    ctop_dpe_r73 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_bist_sch_en0       :  1,    //      0
    reg_c4_bist_sch_en1       :  1,    //      1
    reg_c4_bist_sch_en2       :  1,    //      2
    reg_c4_bist_sch_en3       :  1,    //      3
    reg_c4_bist_sch_en4       :  1,    //      4
    reg_c4_bist_sch_en5       :  1,    //      5
    reg_c4_bist_sch_en6       :  1,    //      6
    reg_c4_bist_sch_en7       :  1,    //      7
    reg_c4_bist_sch_en8       :  1,    //      8
    reg_c4_bist_sch_en9       :  1,    //      9
    reg_c4_bist_sch_en10      :  1,    //     10
    reg_c4_bist_sch_en11      :  1,    //     11
    reg_c4_bist_sch_en12      :  1,    //     12
    reg_c4_bist_sch_en13      :  1,    //     13
    reg_c4_bist_sch_en14      :  1,    //     14
    reg_c4_bist_sch_en15      :  1,    //     15
    reg_c4_bist_sch_en16      :  1,    //     16
    reg_c4_bist_sch_en17      :  1,    //     17
    reg_c4_bist_sch_en18      :  1,    //     18
    reg_c4_bist_sch_en19      :  1,    //     19
    reg_c4_bist_sch_en20      :  1,    //     20
    reg_c4_bist_sch_en21      :  1,    //     21
    reg_c4_bist_sch_en22      :  1,    //     22
    reg_c4_bist_sch_en23      :  1,    //     23
                              :  8;    //  31:24 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R73_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F928    ctop_dpe_r74 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4tx_bist_out_sel_0   :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_c4tx_bist_out_sel_1   :  4,    //  11: 8
                              :  3,    //  14:12 reserved
    reg_c4_occ_test_mode      :  1,    //     15
                              :  4,    //  19:16 reserved
    reg_c4_bist_rstb          :  1,    //     20
                              :  6,    //  26:21 reserved
    reg_c4_dftoccreset        :  1,    //     27
    reg_c4_dftatspeeden_n     :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R74_O20A0_T;

typedef struct {
    UINT32
    reg_c4tx_bist_out_sel_0   :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_c4tx_bist_out_sel_1   :  4,    //  11: 8
                              :  3,    //  14:12 reserved
    reg_c4_occ_test_mode      :  1,    //     15
                              :  4,    //  19:16 reserved
    reg_c4_bist_rstb          :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_c4_vtx_link_bist_en   :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_c4_dftoccreset        :  1,    //     27
    reg_c4_dftatspeeden_n     :  1,    //     28
                              :  3;    //  31:29 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R74_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F92C    ctop_dpe_r75 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_link_reserve       :  8,    //   7: 0
                              : 24;    //   31:8 reserved
}CTOP_CTRL_DPE_CTOP_DPE_R75_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F930    ctop_dpe_r76 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_dc_cal_ch16        :  4,    //   3: 0
    reg_c4_dc_cal_ch17        :  4,    //   7: 4
    reg_c4_dc_cal_ch18        :  4,    //  11: 8
    reg_c4_dc_cal_ch19        :  4,    //  15:12
    reg_c4_dc_cal_ch20        :  4,    //  19:16
    reg_c4_dc_cal_ch21        :  4,    //  23:20
    reg_c4_dc_cal_ch22        :  4,    //  27:24
    reg_c4_dc_cal_ch23        :  4;    //  31:28
}CTOP_CTRL_DPE_CTOP_DPE_R76_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F934    ctop_dpe_r77 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_dc_cal_ch8         :  4,    //   3: 0
    reg_c4_dc_cal_ch9         :  4,    //   7: 4
    reg_c4_dc_cal_ch10        :  4,    //  11: 8
    reg_c4_dc_cal_ch11        :  4,    //  15:12
    reg_c4_dc_cal_ch12        :  4,    //  19:16
    reg_c4_dc_cal_ch13        :  4,    //  23:20
    reg_c4_dc_cal_ch14        :  4,    //  27:24
    reg_c4_dc_cal_ch15        :  4;    //  31:28
}CTOP_CTRL_DPE_CTOP_DPE_R77_O20B0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_F938    ctop_dpe_r78 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_c4_dc_cal_ch0         :  4,    //   3: 0
    reg_c4_dc_cal_ch1         :  4,    //   7: 4
    reg_c4_dc_cal_ch2         :  4,    //  11: 8
    reg_c4_dc_cal_ch3         :  4,    //  15:12
    reg_c4_dc_cal_ch4         :  4,    //  19:16
    reg_c4_dc_cal_ch5         :  4,    //  23:20
    reg_c4_dc_cal_ch6         :  4,    //  27:24
    reg_c4_dc_cal_ch7         :  4;    //  31:28
}CTOP_CTRL_DPE_CTOP_DPE_R78_O20B0_T;

/*-----------------------------------------------------------------------------------------
    ctop_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
UINT32                                                 _rsvd_00[   2] ;         // 0xC930_F800 ~ 0xC930_F804
CTOP_CTRL_DPE_CTOP_DPE_R02_O20A0_T           ctop_dpe_r02             ;         // 0xC930_F808
CTOP_CTRL_DPE_CTOP_DPE_R03_O20A0_T           ctop_dpe_r03             ;         // 0xC930_F80C
CTOP_CTRL_DPE_CTOP_DPE_R04_O20A0_T           ctop_dpe_r04             ;         // 0xC930_F810
CTOP_CTRL_DPE_CTOP_DPE_R05_O20A0_T           ctop_dpe_r05             ;         // 0xC930_F814
CTOP_CTRL_DPE_CTOP_DPE_R06_O20A0_T           ctop_dpe_r06             ;         // 0xC930_F818
CTOP_CTRL_DPE_CTOP_DPE_R07_O20A0_T           ctop_dpe_r07             ;         // 0xC930_F81C
CTOP_CTRL_DPE_CTOP_DPE_R08_O20A0_T           ctop_dpe_r08             ;         // 0xC930_F820
CTOP_CTRL_DPE_CTOP_DPE_R09_O20A0_T           ctop_dpe_r09             ;         // 0xC930_F824
CTOP_CTRL_DPE_CTOP_DPE_R10_O20A0_T           ctop_dpe_r10             ;         // 0xC930_F828
CTOP_CTRL_DPE_CTOP_DPE_R11_O20A0_T           ctop_dpe_r11             ;         // 0xC930_F82C
CTOP_CTRL_DPE_CTOP_DPE_R12_O20A0_T           ctop_dpe_r12             ;         // 0xC930_F830
CTOP_CTRL_DPE_CTOP_DPE_R13_O20A0_T           ctop_dpe_r13             ;         // 0xC930_F834
CTOP_CTRL_DPE_CTOP_DPE_R14_O20A0_T           ctop_dpe_r14             ;         // 0xC930_F838
CTOP_CTRL_DPE_CTOP_DPE_R15_O20A0_T           ctop_dpe_r15             ;         // 0xC930_F83C
CTOP_CTRL_DPE_CTOP_DPE_R16_O20A0_T           ctop_dpe_r16             ;         // 0xC930_F840
CTOP_CTRL_DPE_CTOP_DPE_R17_O20A0_T           ctop_dpe_r17             ;         // 0xC930_F844
CTOP_CTRL_DPE_CTOP_DPE_R18_O20A0_T           ctop_dpe_r18             ;         // 0xC930_F848
CTOP_CTRL_DPE_CTOP_DPE_R19_O20A0_T           ctop_dpe_r19             ;         // 0xC930_F84C
CTOP_CTRL_DPE_CTOP_DPE_R20_O20A0_T           ctop_dpe_r20             ;         // 0xC930_F850
CTOP_CTRL_DPE_CTOP_DPE_R21_O20A0_T           ctop_dpe_r21             ;         // 0xC930_F854
CTOP_CTRL_DPE_CTOP_DPE_R22_O20A0_T           ctop_dpe_r22             ;         // 0xC930_F858
CTOP_CTRL_DPE_CTOP_DPE_R23_O20A0_T           ctop_dpe_r23             ;         // 0xC930_F85C
CTOP_CTRL_DPE_CTOP_DPE_R24_O20A0_T           ctop_dpe_r24             ;         // 0xC930_F860
CTOP_CTRL_DPE_CTOP_DPE_R25_O20A0_T           ctop_dpe_r25             ;         // 0xC930_F864
CTOP_CTRL_DPE_CTOP_DPE_R26_O20A0_T           ctop_dpe_r26             ;         // 0xC930_F868
CTOP_CTRL_DPE_CTOP_DPE_R27_O20A0_T           ctop_dpe_r27             ;         // 0xC930_F86C
CTOP_CTRL_DPE_CTOP_DPE_R28_O20A0_T           ctop_dpe_r28             ;         // 0xC930_F870
CTOP_CTRL_DPE_CTOP_DPE_R29_O20A0_T           ctop_dpe_r29             ;         // 0xC930_F874
CTOP_CTRL_DPE_CTOP_DPE_R30_O20A0_T           ctop_dpe_r30             ;         // 0xC930_F878
CTOP_CTRL_DPE_CTOP_DPE_R31_O20A0_T           ctop_dpe_r31             ;         // 0xC930_F87C
CTOP_CTRL_DPE_CTOP_DPE_R32_O20A0_T           ctop_dpe_r32             ;         // 0xC930_F880
CTOP_CTRL_DPE_CTOP_DPE_R33_O20A0_T           ctop_dpe_r33             ;         // 0xC930_F884
CTOP_CTRL_DPE_CTOP_DPE_R34_O20A0_T           ctop_dpe_r34             ;         // 0xC930_F888
CTOP_CTRL_DPE_CTOP_DPE_R35_O20A0_T           ctop_dpe_r35             ;         // 0xC930_F88C
CTOP_CTRL_DPE_CTOP_DPE_R36_O20A0_T           ctop_dpe_r36             ;         // 0xC930_F890
CTOP_CTRL_DPE_CTOP_DPE_R37_O20A0_T           ctop_dpe_r37             ;         // 0xC930_F894
UINT32                                                 _rsvd_01[   1] ;         // 0xC930_F898
CTOP_CTRL_DPE_CTOP_DPE_R39_O20A0_T           ctop_dpe_r39             ;         // 0xC930_F89C
CTOP_CTRL_DPE_CTOP_DPE_R40_O20A0_T           ctop_dpe_r40             ;         // 0xC930_F8A0
CTOP_CTRL_DPE_CTOP_DPE_R41_O20A0_T           ctop_dpe_r41             ;         // 0xC930_F8A4
CTOP_CTRL_DPE_CTOP_DPE_R42_O20A0_T           ctop_dpe_r42             ;         // 0xC930_F8A8
CTOP_CTRL_DPE_CTOP_DPE_R43_O20A0_T           ctop_dpe_r43             ;         // 0xC930_F8AC
CTOP_CTRL_DPE_CTOP_DPE_R44_O20A0_T           ctop_dpe_r44             ;         // 0xC930_F8B0
CTOP_CTRL_DPE_CTOP_DPE_R45_O20A0_T           ctop_dpe_r45             ;         // 0xC930_F8B4
CTOP_CTRL_DPE_CTOP_DPE_R46_O20A0_T           ctop_dpe_r46             ;         // 0xC930_F8B8
CTOP_CTRL_DPE_CTOP_DPE_R47_O20A0_T           ctop_dpe_r47             ;         // 0xC930_F8BC
CTOP_CTRL_DPE_CTOP_DPE_R48_O20A0_T           ctop_dpe_r48             ;         // 0xC930_F8C0
CTOP_CTRL_DPE_CTOP_DPE_R49_O20A0_T           ctop_dpe_r49             ;         // 0xC930_F8C4
CTOP_CTRL_DPE_CTOP_DPE_R50_O20A0_T           ctop_dpe_r50             ;         // 0xC930_F8C8
CTOP_CTRL_DPE_CTOP_DPE_R51_O20A0_T           ctop_dpe_r51             ;         // 0xC930_F8CC
CTOP_CTRL_DPE_CTOP_DPE_R52_O20A0_T           ctop_dpe_r52             ;         // 0xC930_F8D0
CTOP_CTRL_DPE_CTOP_DPE_R53_O20A0_T           ctop_dpe_r53             ;         // 0xC930_F8D4
CTOP_CTRL_DPE_CTOP_DPE_R54_O20A0_T           ctop_dpe_r54             ;         // 0xC930_F8D8
CTOP_CTRL_DPE_CTOP_DPE_R55_O20A0_T           ctop_dpe_r55             ;         // 0xC930_F8DC
CTOP_CTRL_DPE_CTOP_DPE_R56_O20A0_T           ctop_dpe_r56             ;         // 0xC930_F8E0
CTOP_CTRL_DPE_CTOP_DPE_R57_O20A0_T           ctop_dpe_r57             ;         // 0xC930_F8E4
CTOP_CTRL_DPE_CTOP_DPE_R58_O20A0_T           ctop_dpe_r58             ;         // 0xC930_F8E8
CTOP_CTRL_DPE_CTOP_DPE_R59_O20A0_T           ctop_dpe_r59             ;         // 0xC930_F8EC
CTOP_CTRL_DPE_CTOP_DPE_R60_O20A0_T           ctop_dpe_r60             ;         // 0xC930_F8F0
CTOP_CTRL_DPE_CTOP_DPE_R61_O20A0_T           ctop_dpe_r61             ;         // 0xC930_F8F4
CTOP_CTRL_DPE_CTOP_DPE_R62_O20A0_T           ctop_dpe_r62             ;         // 0xC930_F8F8
CTOP_CTRL_DPE_CTR86_RO_O20A0_T               ctr86_ro                 ;         // 0xC930_F8FC
CTOP_CTRL_DPE_CTR87_RO_O20A0_T               ctr87_ro                 ;         // 0xC930_F900
CTOP_CTRL_DPE_CTR88_RO_O20A0_T               ctr88_ro                 ;         // 0xC930_F904
CTOP_CTRL_DPE_CTR89_RO_O20A0_T               ctr89_ro                 ;         // 0xC930_F908
CTOP_CTRL_DPE_CTR90_RO_O20A0_T               ctr90_ro                 ;         // 0xC930_F90C
CTOP_CTRL_DPE_CTR91_RO_O20A0_T               ctr91_ro                 ;         // 0xC930_F910
CTOP_CTRL_DPE_CTR92_RO_O20A0_T               ctr92_ro                 ;         // 0xC930_F914
CTOP_CTRL_DPE_CTR93_RO_O20A0_T               ctr93_ro                 ;         // 0xC930_F918
CTOP_CTRL_DPE_CTR94_RO_O20A0_T               ctr94_ro                 ;         // 0xC930_F91C
CTOP_CTRL_DPE_CTR95_RO_O20A0_T               ctr95_ro                 ;         // 0xC930_F920
CTOP_CTRL_DPE_CTOP_DPE_R73_O20A0_T           ctop_dpe_r73             ;         // 0xC930_F924
union {
CTOP_CTRL_DPE_CTOP_DPE_R74_O20A0_T           ctop_dpe_r74             ;         // 0xC930_F928
CTOP_CTRL_DPE_CTOP_DPE_R74_O20B0_T           ctop_dpe_r74_B0          ;         // 0xC930_F928
};
CTOP_CTRL_DPE_CTOP_DPE_R75_O20A0_T           ctop_dpe_r75             ;         // 0xC930_F92C
CTOP_CTRL_DPE_CTOP_DPE_R76_O20B0_T           ctop_dpe_r76_B0          ;         // 0xC930_F930
CTOP_CTRL_DPE_CTOP_DPE_R77_O20B0_T           ctop_dpe_r77_B0          ;         // 0xC930_F934
CTOP_CTRL_DPE_CTOP_DPE_R78_O20B0_T           ctop_dpe_r78_B0          ;         // 0xC930_F938
} CTOP_CTRL_DPE_REG_O20A0_T;
/* 73 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_CTRL_DPE_O20A0_REG_H_ */

/* from 'O20_CTOP_Register_Manual.xlsm'  2019.4.16  KST by LGSiCRDV V2.2B*/

