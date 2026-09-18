#ifndef _CTOP_DPE_M17A0_REG_H_
#define _CTOP_DPE_M17A0_REG_H_

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
    0xC930_A400    ctop_dpe_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vx1_mode                  :  1,    //      0
    epi_mode                  :  1,    //      1
    c4_epi10_en               :  1,    //      2
    c4_sel_plllock            :  1,    //      3
    c4_sel_fin                :  2,    //   5: 4
    c4_sc_ctl                 :  2,    //   7: 6
    c4_epi_sel_mode           :  1,    //      8
    c4_sel_bw                 :  1,    //      9
    c4_sw_rext                :  1,    //     10
    c4_cih                    :  3,    //  13:11
    c4_pll_ic                 :  2,    //  15:14
    lvds_mode                 :  1,    //     16
                              :  1,    //     17 reserved
    c4_sel_lpf_v              :  1,    //     18
    c4_lock_div_ctl           :  2,    //  20:19
    c4_pdb                    :  1,    //     21
    c4_sel_lock               :  1,    //     22
    c4_rf                     :  1,    //     23
    c4_term_en                :  1,    //     24
    c4_adj_term               :  3,    //  27:25
    c4_vtx_rstn_en2           :  1,    //     28
    c4_sel_mode               :  2,    //  30:29
    c4_sw_pud                 :  1;    //     31
}CTOP_DPE_CTOP_DPE_R00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A404    ctop_dpe_r01 ''
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
                              :  3,    //  14:12 reserved
    c4_lock_samp_ctl          :  2,    //  16:15
    c4_scr_rst3               :  1,    //     17
    c4_scr_rst2               :  1,    //     18
    c4_scr_rst1               :  1,    //     19
                              :  1,    //     20 reserved
    c4_scr_off3               :  1,    //     21
    c4_scr_off2               :  1,    //     22
    c4_scr_off1               :  1,    //     23
                              :  1,    //     24 reserved
    c4_enc_rst3               :  1,    //     25
    c4_enc_rst2               :  1,    //     26
    c4_enc_rst1               :  1,    //     27
                              :  1,    //     28 reserved
    c4_enc_off3               :  1,    //     29
    c4_enc_off2               :  1,    //     30
    c4_enc_off1               :  1;    //     31
}CTOP_DPE_CTOP_DPE_R01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A408    ctop_dpe_r02 ''
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
                              :  4,    //  15:12 reserved
    c4_pdb_ch0                :  1,    //     16
    c4_pdb_ch1                :  1,    //     17
    c4_pdb_ch2                :  1,    //     18
    c4_pdb_ch3                :  1,    //     19
    c4_pdb_ch4                :  1,    //     20
    c4_pdb_ch5                :  1,    //     21
    c4_pdb_ch6                :  1,    //     22
    c4_pdb_ch7                :  1,    //     23
    c4_pdb_ch8                :  1,    //     24
    c4_pdb_ch9                :  1,    //     25
    c4_pdb_ch10               :  1,    //     26
    c4_pdb_ch11               :  1,    //     27
                              :  4;    //  31:28 reserved
}CTOP_DPE_CTOP_DPE_R02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A40C    ctop_dpe_r03 ''
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
}CTOP_DPE_CTOP_DPE_R03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A410    ctop_dpe_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    c4_test_mode3             :  2,    //   3: 2
    c4_test_mode2             :  2,    //   5: 4
    c4_test_mode1             :  2,    //   7: 6
    c4_itune8                 :  3,    //  10: 8
    c4_itune9                 :  3,    //  13:11
    c4_itune10                :  3,    //  16:14
    c4_itune11                :  3,    //  19:17
                              :  6,    //  25:20 reserved
    c4_pemp_ch10              :  3,    //  28:26
    c4_pemp_ch11              :  3;    //  31:29
}CTOP_DPE_CTOP_DPE_R04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A414    ctop_dpe_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    c4_itune0                 :  3,    //  10: 8
    c4_itune1                 :  3,    //  13:11
    c4_itune2                 :  3,    //  16:14
    c4_itune3                 :  3,    //  19:17
    c4_itune4                 :  3,    //  22:20
    c4_itune5                 :  3,    //  25:23
    c4_itune6                 :  3,    //  28:26
    c4_itune7                 :  3;    //  31:29
}CTOP_DPE_CTOP_DPE_R05_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A418    ctop_dpe_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    c4_txlock_fixen3          :  2,    //   3: 2
    c4_txlock_fixen2          :  2,    //   5: 4
    c4_txlock_fixen1          :  2,    //   7: 6
                              :  6,    //  13: 8 reserved
    c4_count_rxlock3          :  6,    //  19:14
    c4_count_rxlock2          :  6,    //  25:20
    c4_count_rxlock1          :  6;    //  31:26
}CTOP_DPE_CTOP_DPE_R06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A41C    ctop_dpe_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    c4_read_tp_sel3           :  4,    //   7: 4
    c4_read_tp_sel2           :  4,    //  11: 8
    c4_read_tp_sel1           :  4,    //  15:12
                              : 10,    //  25:16 reserved
    c4_read_lane_sel3         :  2,    //  27:26
    c4_read_lane_sel2         :  2,    //  29:28
    c4_read_lane_sel1         :  2;    //  31:30
}CTOP_DPE_CTOP_DPE_R07_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A420    ctop_dpe_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_sel_clkpix2            :  3,    //   2: 0
    c4_sel_clkpix1            :  3,    //   5: 3
    c4_count_txlock2_v        : 13,    //  18: 6
    c4_count_txlock1_v        : 13;    //  31:19
}CTOP_DPE_CTOP_DPE_R08_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A424    ctop_dpe_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    c4_sel_clkpix3            :  3,    //   5: 3
                              : 13,    //  18: 6 reserved
    c4_count_txlock3          : 13;    //  31:19
}CTOP_DPE_CTOP_DPE_R09_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A428    ctop_dpe_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_vtx_tvfp               : 11,    //  10: 0
                              :  6,    //  16:11 reserved
    c4_clk_pix1x_rf3          :  1,    //     17
    c4_clk_pix1x_rf2          :  1,    //     18
    c4_clk_pix1x_rf1          :  1,    //     19
                              :  2,    //  21:20 reserved
    c4_read_address_offset3   :  2,    //  23:22
    c4_read_address_offset2   :  2,    //  25:24
    c4_read_address_offset1   :  2,    //  27:26
                              :  1,    //     28 reserved
    c4_vtx_rstn_en3           :  1,    //     29
    c4_rstn_vtxlink           :  1,    //     30
    c4_vtx_rstn_en1           :  1;    //     31
}CTOP_DPE_CTOP_DPE_R10_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A42C    ctop_dpe_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di3               : 10,    //   9: 0
    c4_test_di2               : 10,    //  19:10
    c4_test_di1               : 10,    //  29:20
    c4_bytemode               :  2;    //  31:30
}CTOP_DPE_CTOP_DPE_R11_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A430    ctop_dpe_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    c4_vtx_pattern_clk_en     :  1,    //      3
    c4_vtx_sync_chk_rstb      :  1,    //      4
    c4_vtx_sync_chk_clk_en    :  1,    //      5
    c4_vtx_sync_inv           :  1,    //      6
    c4_vtx_man_pattern_en     :  1,    //      7
    c4_vtx_tvact              : 12,    //  19: 8
    c4_vtx_tvblank            : 12;    //  31:20
}CTOP_DPE_CTOP_DPE_R12_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A434    ctop_dpe_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    c4_vtx_man_pattern_sel    :  4,    //   5: 2
    c4_vtx_thact              : 13,    //  18: 6
    c4_vtx_thblank            : 13;    //  31:19
}CTOP_DPE_CTOP_DPE_R13_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A438    ctop_dpe_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_v                 :  1,    //      0
    c4_vtx_lockn_sel          :  1,    //      1
    c4_vx1_lockn_frmain       :  1,    //      2
    c4_lp_en                  :  1,    //      3
    c4_vtx_thpw               :  8,    //  11: 4
    c4_vtx_thfp               : 12,    //  23:12
    c4_vtx_tvpw               :  8;    //  31:24
}CTOP_DPE_CTOP_DPE_R14_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A43C    ctop_dpe_r15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 13,    //  12: 0 reserved
    c4_lock_ext               :  1,    //     13
    c4_testlock_ctl           :  1,    //     14
    c4_reg_rstn               :  1,    //     15
    c4_sel_rstctl             :  1,    //     16
    c4_sel_rstn               :  1,    //     17
    c4_ctl_reg                :  2,    //  19:18
    reg_sel_h                 :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_DPE_CTOP_DPE_R15_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A440    ctop_dpe_r16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    c4_epi10_en_h             :  1,    //      2
    c4_sel_plllock_h          :  1,    //      3
    c4_sel_fin_h              :  2,    //   5: 4
    c4_sc_ctl_h               :  2,    //   7: 6
    c4_epi_sel_mode_h         :  1,    //      8
    c4_sel_bw_h               :  1,    //      9
    c4_sw_rext_h              :  1,    //     10
    c4_cih_h                  :  3,    //  13:11
    c4_pll_ic_h               :  2,    //  15:14
                              :  1,    //     16 reserved
    c4_sel_prediv_h           :  1,    //     17
    c4_sel_lpf_h              :  1,    //     18
    c4_lock_ctl_h             :  2,    //  20:19
    c4_pdb_h                  :  1,    //     21
    c4_sel_lock_h             :  1,    //     22
    c4_rf_h                   :  1,    //     23
    c4_term_en_h              :  1,    //     24
    c4_adj_term_h             :  3,    //  27:25
    c4_vtx_rstn_en5           :  1,    //     28
    c4_sel_mode_h             :  2,    //  30:29
    c4_sw_pud_h               :  1;    //     31
}CTOP_DPE_CTOP_DPE_R16_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A444    ctop_dpe_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link12_en              :  1,    //      0
    c4_link13_en              :  1,    //      1
    c4_link14_en              :  1,    //      2
    c4_link15_en              :  1,    //      3
    c4_link16_en              :  1,    //      4
    c4_link17_en              :  1,    //      5
    c4_link18_en              :  1,    //      6
    c4_link19_en              :  1,    //      7
    c4_link20_en              :  1,    //      8
    c4_link21_en              :  1,    //      9
    c4_link22_en              :  1,    //     10
    c4_link23_en              :  1,    //     11
                              :  5,    //  16:12 reserved
    c4_scr_rst6               :  1,    //     17
    c4_scr_rst5               :  1,    //     18
    c4_scr_rst4               :  1,    //     19
                              :  1,    //     20 reserved
    c4_scr_off6               :  1,    //     21
    c4_scr_off5               :  1,    //     22
    c4_scr_off4               :  1,    //     23
                              :  1,    //     24 reserved
    c4_enc_rst6               :  1,    //     25
    c4_enc_rst5               :  1,    //     26
    c4_enc_rst4               :  1,    //     27
                              :  1,    //     28 reserved
    c4_enc_off6               :  1,    //     29
    c4_enc_off5               :  1,    //     30
    c4_enc_off4               :  1;    //     31
}CTOP_DPE_CTOP_DPE_R17_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A448    ctop_dpe_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_flip_en_ch12           :  1,    //      0
    c4_flip_en_ch13           :  1,    //      1
    c4_flip_en_ch14           :  1,    //      2
    c4_flip_en_ch15           :  1,    //      3
    c4_flip_en_ch16           :  1,    //      4
    c4_flip_en_ch17           :  1,    //      5
    c4_flip_en_ch18           :  1,    //      6
    c4_flip_en_ch19           :  1,    //      7
    c4_flip_en_ch20           :  1,    //      8
    c4_flip_en_ch21           :  1,    //      9
    c4_flip_en_ch22           :  1,    //     10
    c4_flip_en_ch23           :  1,    //     11
                              :  4,    //  15:12 reserved
    c4_pdb_ch12               :  1,    //     16
    c4_pdb_ch13               :  1,    //     17
    c4_pdb_ch14               :  1,    //     18
    c4_pdb_ch15               :  1,    //     19
    c4_pdb_ch16               :  1,    //     20
    c4_pdb_ch17               :  1,    //     21
    c4_pdb_ch18               :  1,    //     22
    c4_pdb_ch19               :  1,    //     23
    c4_pdb_ch20               :  1,    //     24
    c4_pdb_ch21               :  1,    //     25
    c4_pdb_ch22               :  1,    //     26
    c4_pdb_ch23               :  1,    //     27
                              :  4;    //  31:28 reserved
}CTOP_DPE_CTOP_DPE_R18_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A44C    ctop_dpe_r19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_pemp_ch12              :  3,    //   2: 0
    c4_pemp_ch13              :  3,    //   5: 3
    c4_pemp_ch14              :  3,    //   8: 6
    c4_pemp_ch15              :  3,    //  11: 9
    c4_pemp_ch16              :  3,    //  14:12
    c4_pemp_ch17              :  3,    //  17:15
    c4_pemp_ch18              :  3,    //  20:18
    c4_pemp_ch19              :  3,    //  23:21
    c4_pemp_ch20              :  3,    //  26:24
    c4_pemp_ch21              :  3,    //  29:27
                              :  2;    //  31:30 reserved
}CTOP_DPE_CTOP_DPE_R19_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A450    ctop_dpe_r20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    c4_test_mode6             :  2,    //   3: 2
    c4_test_mode5             :  2,    //   5: 4
    c4_test_mode4             :  2,    //   7: 6
    c4_itune20                :  3,    //  10: 8
    c4_itune21                :  3,    //  13:11
    c4_itune22                :  3,    //  16:14
    c4_itune23                :  3,    //  19:17
                              :  6,    //  25:20 reserved
    c4_pemp_ch22              :  3,    //  28:26
    c4_pemp_ch23              :  3;    //  31:29
}CTOP_DPE_CTOP_DPE_R20_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A454    ctop_dpe_r21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    c4_itune12                :  3,    //  10: 8
    c4_itune13                :  3,    //  13:11
    c4_itune14                :  3,    //  16:14
    c4_itune15                :  3,    //  19:17
    c4_itune16                :  3,    //  22:20
    c4_itune17                :  3,    //  25:23
    c4_itune18                :  3,    //  28:26
    c4_itune19                :  3;    //  31:29
}CTOP_DPE_CTOP_DPE_R21_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A458    ctop_dpe_r22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    c4_txlock_fixen6          :  2,    //   3: 2
    c4_txlock_fixen5          :  2,    //   5: 4
    c4_txlock_fixen4          :  2,    //   7: 6
                              :  6,    //  13: 8 reserved
    c4_count_rxlock6          :  6,    //  19:14
    c4_count_rxlock5          :  6,    //  25:20
    c4_count_rxlock4          :  6;    //  31:26
}CTOP_DPE_CTOP_DPE_R22_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A45C    ctop_dpe_r23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    c4_read_tp_sel6           :  4,    //   7: 4
    c4_read_tp_sel5           :  4,    //  11: 8
    c4_read_tp_sel4           :  4,    //  15:12
                              : 10,    //  25:16 reserved
    c4_read_lane_sel6         :  2,    //  27:26
    c4_read_lane_sel5         :  2,    //  29:28
    c4_read_lane_sel4         :  2;    //  31:30
}CTOP_DPE_CTOP_DPE_R23_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A460    ctop_dpe_r24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_sel_clkpix5            :  3,    //   2: 0
    c4_sel_clkpix4            :  3,    //   5: 3
    c4_count_txlock5          : 13,    //  18: 6
    c4_count_txlock4          : 13;    //  31:19
}CTOP_DPE_CTOP_DPE_R24_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A464    ctop_dpe_r25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  3,    //   2: 0 reserved
    c4_sel_clkpix6            :  3,    //   5: 3
                              : 13,    //  18: 6 reserved
    c4_count_txlock6          : 13;    //  31:19
}CTOP_DPE_CTOP_DPE_R25_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A468    ctop_dpe_r26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 17,    //  16: 0 reserved
    c4_clk_pix1x_rf6          :  1,    //     17
    c4_clk_pix1x_rf5          :  1,    //     18
    c4_clk_pix1x_rf4          :  1,    //     19
                              :  2,    //  21:20 reserved
    c4_read_address_offset6   :  2,    //  23:22
    c4_read_address_offset5   :  2,    //  25:24
    c4_read_address_offset4   :  2,    //  27:26
                              :  1,    //     28 reserved
    c4_vtx_rstn_en6           :  1,    //     29
                              :  1,    //     30 reserved
    c4_vtx_rstn_en4           :  1;    //     31
}CTOP_DPE_CTOP_DPE_R26_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A46C    ctop_dpe_r27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_test_di6               : 10,    //   9: 0
    c4_test_di5               : 10,    //  19:10
    c4_test_di4               : 10,    //  29:20
    c4_adj_term_3_            :  1,    //     30
    c4tx_b0_test_enb          :  1;    //     31
}CTOP_DPE_CTOP_DPE_R27_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A470    ctop_dpe_r28 ''
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
}CTOP_DPE_CTOP_DPE_R28_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A474    ctop_dpe_r29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    displl_freq_update        :  1,    //      0
    displl_sync_on            :  1,    //      1
                              :  2,    //   3: 2 reserved
    displl_ofs_mode           :  1,    //      4
    displl_fout3_od           :  3,    //   7: 5
    displl_fout2_od           :  3,    //  10: 8
    displl_fout_od            :  2,    //  12:11
    displl_pre_fout3_div      :  3,    //  15:13
    displl_pre_fout2_div      :  3,    //  18:16
    displl_nsc                :  4,    //  22:19
    displl_npc                :  6,    //  28:23
    displl_fine_control       :  3;    //  31:29
}CTOP_DPE_CTOP_DPE_R29_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A478    ctop_dpe_r30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 22,    //  21: 0 reserved
    displl_wakeup_bypass      :  1,    //     22
    displl_ddr_mode           :  1,    //     23
    displl_offset             :  8;    //  31:24
}CTOP_DPE_CTOP_DPE_R30_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A47C    ctop_dpe_r31 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_gpio15_pd             :  1,    //      5
    reg_gpio14_pd             :  1,    //      6
    reg_gpio13_ds             :  1,    //      7
    reg_gpio13_pu             :  1,    //      8
    reg_gpio13_pd             :  1,    //      9
    reg_gpio12_pd             :  1,    //     10
    reg_gpio11_pd             :  1,    //     11
    reg_gpio10_ds             :  1,    //     12
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
}CTOP_DPE_CTOP_DPE_R31_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A480    ctop_dpe_r32 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  7,    //   6: 0 reserved
    mon_imx_en                :  1,    //      7
    mon_hdmi_en               :  1,    //      8
    mon_gbs_en                :  1,    //      9
    mon_fme1_en               :  1,    //     10
    mon_venc_en               :  1,    //     11
    mon_c4tx_en               :  1,    //     12
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
                              :  3,    //  25:23 reserved
    gp13_1_mux_en             :  1,    //     26
    gp13_2_mux_en             :  1,    //     27
    gp13_3_mux_en             :  1,    //     28
    gp13_4_mux_en             :  1,    //     29
    gp13_5_mux_en             :  1,    //     30
    gp13_6_mux_en             :  1;    //     31
}CTOP_DPE_CTOP_DPE_R32_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A484    ctop_dpe_r33 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  2,    //   1: 0 reserved
    boe_enable_opt            :  1,    //      2
    disp594_clk_gate_en       :  1,    //      3
    gpu_clk_sel               :  1,    //      4
    lvds_boe_mode             :  1,    //      5
    i2c6_en                   :  1,    //      6
    mon_led_en                :  1,    //      7
    mon_sr_en                 :  1,    //      8
    mon_gpu_en                :  1,    //      9
    mon_cco_en                :  1,    //     10
    en_eb_addr_out            :  1,    //     11
    aud_sub_en                :  1,    //     12
                              :  4,    //  16:13 reserved
    rxclkdrv3_smv_normal      :  1,    //     17
    rxclkdrv3_outsel_normal   :  2,    //  19:18
    rxclkdrv3_pdb_normal      :  1,    //     20
                              : 11;    //  31:21 reserved
}CTOP_DPE_CTOP_DPE_R33_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A488    ctop_dpe_r34 ''
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
}CTOP_DPE_CTOP_DPE_R34_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A498    ctop_dpe_r40 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link_read_tp2          : 16,    //  15: 0
    c4_link_read_tp1          : 16;    //  31:16
}CTOP_DPE_CTOP_DPE_R40_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A49C    ctop_dpe_r41 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link_read_tp4          : 16,    //  15: 0
    c4_link_read_tp3          : 16;    //  31:16
}CTOP_DPE_CTOP_DPE_R41_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A4A0    ctop_dpe_r42 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    c4_link_read_tp6          : 16,    //  15: 0
    c4_link_read_tp5          : 16;    //  31:16
}CTOP_DPE_CTOP_DPE_R42_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A4A4    ctop_dpe_r43 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 23,    //  22: 0 reserved
    c4_link_tp6               :  1,    //     23
    c4_link_tp5               :  1,    //     24
    c4_link_tp4               :  1,    //     25
    c4_link_tp3               :  1,    //     26
    c4_link_tp2               :  1,    //     27
    c4_link_tp1               :  1,    //     28
    c4_vx1_lockn_frobmc       :  1,    //     29
    c4_epi_lock_frobmc        :  1,    //     30
    c4_pll_lock_frobmc        :  1;    //     31
}CTOP_DPE_CTOP_DPE_R43_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A4B0    ctop_dpe_r44 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    m16p_rev_num              : 32;    //  31: 0
}CTOP_DPE_CTOP_DPE_R44_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC930_A4B4    ctop_dpe_r45 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    m16p_chip_id              : 32;    //  31: 0
}CTOP_DPE_CTOP_DPE_R45_M17_A0;

/*-----------------------------------------------------------------------------------------
    ctop_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
CTOP_DPE_CTOP_DPE_R00_M17_A0                 ctop_dpe_r00             ;         // 0xC930_A400
CTOP_DPE_CTOP_DPE_R01_M17_A0                 ctop_dpe_r01             ;         // 0xC930_A404
CTOP_DPE_CTOP_DPE_R02_M17_A0                 ctop_dpe_r02             ;         // 0xC930_A408
CTOP_DPE_CTOP_DPE_R03_M17_A0                 ctop_dpe_r03             ;         // 0xC930_A40C
CTOP_DPE_CTOP_DPE_R04_M17_A0                 ctop_dpe_r04             ;         // 0xC930_A410
CTOP_DPE_CTOP_DPE_R05_M17_A0                 ctop_dpe_r05             ;         // 0xC930_A414
CTOP_DPE_CTOP_DPE_R06_M17_A0                 ctop_dpe_r06             ;         // 0xC930_A418
CTOP_DPE_CTOP_DPE_R07_M17_A0                 ctop_dpe_r07             ;         // 0xC930_A41C
CTOP_DPE_CTOP_DPE_R08_M17_A0                 ctop_dpe_r08             ;         // 0xC930_A420
CTOP_DPE_CTOP_DPE_R09_M17_A0                 ctop_dpe_r09             ;         // 0xC930_A424
CTOP_DPE_CTOP_DPE_R10_M17_A0                 ctop_dpe_r10             ;         // 0xC930_A428
CTOP_DPE_CTOP_DPE_R11_M17_A0                 ctop_dpe_r11             ;         // 0xC930_A42C
CTOP_DPE_CTOP_DPE_R12_M17_A0                 ctop_dpe_r12             ;         // 0xC930_A430
CTOP_DPE_CTOP_DPE_R13_M17_A0                 ctop_dpe_r13             ;         // 0xC930_A434
CTOP_DPE_CTOP_DPE_R14_M17_A0                 ctop_dpe_r14             ;         // 0xC930_A438
CTOP_DPE_CTOP_DPE_R15_M17_A0                 ctop_dpe_r15             ;         // 0xC930_A43C
CTOP_DPE_CTOP_DPE_R16_M17_A0                 ctop_dpe_r16             ;         // 0xC930_A440
CTOP_DPE_CTOP_DPE_R17_M17_A0                 ctop_dpe_r17             ;         // 0xC930_A444
CTOP_DPE_CTOP_DPE_R18_M17_A0                 ctop_dpe_r18             ;         // 0xC930_A448
CTOP_DPE_CTOP_DPE_R19_M17_A0                 ctop_dpe_r19             ;         // 0xC930_A44C
CTOP_DPE_CTOP_DPE_R20_M17_A0                 ctop_dpe_r20             ;         // 0xC930_A450
CTOP_DPE_CTOP_DPE_R21_M17_A0                 ctop_dpe_r21             ;         // 0xC930_A454
CTOP_DPE_CTOP_DPE_R22_M17_A0                 ctop_dpe_r22             ;         // 0xC930_A458
CTOP_DPE_CTOP_DPE_R23_M17_A0                 ctop_dpe_r23             ;         // 0xC930_A45C
CTOP_DPE_CTOP_DPE_R24_M17_A0                 ctop_dpe_r24             ;         // 0xC930_A460
CTOP_DPE_CTOP_DPE_R25_M17_A0                 ctop_dpe_r25             ;         // 0xC930_A464
CTOP_DPE_CTOP_DPE_R26_M17_A0                 ctop_dpe_r26             ;         // 0xC930_A468
CTOP_DPE_CTOP_DPE_R27_M17_A0                 ctop_dpe_r27             ;         // 0xC930_A46C
CTOP_DPE_CTOP_DPE_R28_M17_A0                 ctop_dpe_r28             ;         // 0xC930_A470
CTOP_DPE_CTOP_DPE_R29_M17_A0                 ctop_dpe_r29             ;         // 0xC930_A474
CTOP_DPE_CTOP_DPE_R30_M17_A0                 ctop_dpe_r30             ;         // 0xC930_A478
CTOP_DPE_CTOP_DPE_R31_M17_A0                 ctop_dpe_r31             ;         // 0xC930_A47C
CTOP_DPE_CTOP_DPE_R32_M17_A0                 ctop_dpe_r32             ;         // 0xC930_A480
CTOP_DPE_CTOP_DPE_R33_M17_A0                 ctop_dpe_r33             ;         // 0xC930_A484
CTOP_DPE_CTOP_DPE_R34_M17_A0                 ctop_dpe_r34             ;         // 0xC930_A488
UINT32                                                 _rsvd_00[   3] ;         // 0xC930_A48C ~ 0xC930_A494
CTOP_DPE_CTOP_DPE_R40_M17_A0                 ctop_dpe_r40             ;         // 0xC930_A498
CTOP_DPE_CTOP_DPE_R41_M17_A0                 ctop_dpe_r41             ;         // 0xC930_A49C
CTOP_DPE_CTOP_DPE_R42_M17_A0                 ctop_dpe_r42             ;         // 0xC930_A4A0
CTOP_DPE_CTOP_DPE_R43_M17_A0                 ctop_dpe_r43             ;         // 0xC930_A4A4
UINT32                                                 _rsvd_01[   2] ;         // 0xC930_A4A8 ~ 0xC930_A4AC
CTOP_DPE_CTOP_DPE_R44_M17_A0                 ctop_dpe_r44             ;         // 0xC930_A4B0
CTOP_DPE_CTOP_DPE_R45_M17_A0                 ctop_dpe_r45             ;         // 0xC930_A4B4
} CTOP_DPE_REG_M17_A0;
/* 41 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_DPE_M17A0_REG_H_ */

/* from 'M16PP_CTOP_Register_Manual_13.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

