#ifndef _DRG_CTRL_REG_O24A0_H_
#define _DRG_CTRL_REG_O24A0_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  HEADER_2 : Use Another Header Structure 
---------------------------------------------------------------------------------------*/

#ifndef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0xCC93_2000    disp_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopllss_accuracy:  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_disp_aiopllss_dss     :  1,    //      3
    reg_disp_aiopllss_cih2    :  4,    //   7: 4
    reg_disp_aiopllss_cih     :  4,    //  11: 8
    reg_disp_aiopllss_nsc     :  4,    //  15:12
    reg_disp_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_disp_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}DRG_CTRL_DISP_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2004    disp_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopllss_out_div :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_disp_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_disp_aiopllss_updn_max:  7,    //  30:24
                              :  1;    //  31:31 reserved
}DRG_CTRL_DISP_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2008    disp_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopllss_fout1_en:  1,    //      0
    reg_disp_aiopllss_freq_update: 1,    //    1
    reg_disp_aiopllss_sync_on :  1,    //      2
    reg_disp_aiopllss_wake_bypass: 1,    //    3
    reg_disp_aiopllss_offset_mode: 1,    //    4
    reg_disp_aiopllss_fine_div:  1,    //      5
                              :  2,    //   7: 6 reserved
    reg_disp_aiopllss_fine_control: 3,    //  10:8
                              :  1,    //     11 reserved
    reg_disp_aiopllss_offset  :  8,    //  19:12
                              : 12;    //  31:20 reserved
}DRG_CTRL_DISP_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2010    oif_aiopll_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_oif_aiopll_fine_div   :  1,    //      1
    reg_oif_aiopll_dss        :  1,    //      2
    reg_oif_aiopll_accuracy   :  2,    //   4: 3
    reg_oif_aiopll_updn_max   :  7,    //  11: 5
    reg_oif_aiopll_mod_freq_max: 9,    //  20:12
    reg_oif_aiopll_m          :  6,    //  26:21
                              :  1,    //     27 reserved
    reg_oif_aiopll_cih        :  4;    //  31:28
}DRG_CTRL_OIF_AIOPLL_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2014    oif_aiopll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_oif_aiopll_offset_mode:  1,    //      4
    reg_oif_aiopll_fout3_post_od: 3,    //  7: 5
    reg_oif_aiopll_fout2_post_od: 3,    //  10:8
    reg_oif_aiopll_fout_od    :  2,    //  12:11
    reg_oif_aiopll_fout3_pre_od: 3,    //  15:13
    reg_oif_aiopll_fout2_pre_od: 3,    //  18:16
    reg_oif_aiopll_nsc        :  4,    //  22:19
    reg_oif_aiopll_npc        :  6,    //  28:23
    reg_oif_aiopll_fine_control: 3;    //  31:29
}DRG_CTRL_OIF_AIOPLL_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2018    oif_aiopll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_oif_aiopll_out_sel    :  1,    //      0
    reg_oif_aiopll_freq_update:  1,    //      1
    reg_oif_aiopll_sync_on    :  1,    //      2
    reg_oif_aiopll_in_sel     :  1,    //      3
                              : 18,    //  21: 4 reserved
    reg_oif_aiopll_wake_bypass:  1,    //     22
    reg_oif_aiopll_ddr_mode   :  1,    //     23
    reg_oif_aiopll_offset     :  8;    //  31:24
}DRG_CTRL_OIF_AIOPLL_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2020    pqe_frpll_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_pqe_frpll_in_divsel   :  1,    //      1
    reg_pqe_frpll_lpf_on      :  1,    //      2
    reg_pqe_frpll_fout2_en    :  1,    //      3
    reg_pqe_frpll_wakeup_bypass: 1,    //      4
    reg_pqe_frpll_divint      :  9,    //  13: 5
                              :  1,    //     14 reserved
    reg_pqe_frpll_dsmon       :  1,    //     15
    reg_pqe_frpll_auto_freq   :  1,    //     16
    reg_pqe_frpll_dsm_limit   :  1,    //     17
    reg_pqe_frpll_fin_sel     :  1,    //     18
    reg_pqe_frpll_icp         :  4,    //  22:19
    reg_pqe_frpll_out_div     :  9;    //  31:23
}DRG_CTRL_PQE_FRPLL_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2024    pqe_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_frpll_fout_en     :  1,    //      0
    reg_pqe_frpll_syncon      :  1,    //      1
    reg_pqe_frpll_m           :  6,    //   7: 2
    reg_pqe_frpll_fcw         : 24;    //  31: 8
}DRG_CTRL_PQE_FRPLL_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2028    pqe_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_pqe_frpll_out_div3    :  9,    //  13: 5
    reg_pqe_frpll_out_div2    :  9,    //  22:14
    reg_pqe_frpll_frequp      :  1,    //     23
    reg_pqe_frpll_a           :  6,    //  29:24
    reg_pqe_frpll_in_divrstb  :  1,    //     30
    reg_pqe_frpll_icp_g       :  1;    //     31
}DRG_CTRL_PQE_FRPLL_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_202C    pqe_frpll_sscg_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_frpll_updn_max    :  8,    //   7: 0
    reg_pqe_frpll_mod_speed_max: 9,    //  16: 8
                              :  7,    //  23:17 reserved
    reg_pqe_frpll_lock_cont   :  1,    //     24
    reg_pqe_frpll_dss         :  1,    //     25
                              :  5,    //  30:26 reserved
    reg_pqe_soft_reset_frpll_sscg: 1;    //   31
}DRG_CTRL_PQE_FRPLL_SSCG_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2030    pqe_frpll_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_divint_mux_sel    :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_pqe_fcw_mux_sel       :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}DRG_CTRL_PQE_FRPLL_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2060    crg_top_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_sel_disp735       :  1,    //      0
    reg_disp735_clk_gate_en   :  1,    //      1
    reg_pll_sel_din735        :  1,    //      2
    reg_din735_clk_gate_en    :  1,    //      3
    reg_clk_sel_oif           :  1,    //      4
    reg_oif_clk_gate_en       :  1,    //      5
                              : 26;    //   31:6 reserved
}DRG_CTRL_CRG_TOP_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2064    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_c4tx_smv     :  1,    //      0
                              : 31;    //   31:1 reserved
}DRG_CTRL_CRG_TOP_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2068    crg_top_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_drg_pll_mon_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}DRG_CTRL_CRG_TOP_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    drg_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    DRG_CTRL_DISP_AIOPLLSS_00_O24A0_T    disp_aiopllss_00;      // 0xCC93_2000
    DRG_CTRL_DISP_AIOPLLSS_01_O24A0_T    disp_aiopllss_01;      // 0xCC93_2004
    DRG_CTRL_DISP_AIOPLLSS_02_O24A0_T    disp_aiopllss_02;      // 0xCC93_2008
    UINT32                             _rsvd_00[1];             // 0xCC93_200C
    DRG_CTRL_OIF_AIOPLL_00_O24A0_T     oif_aiopll_00;           // 0xCC93_2010
    DRG_CTRL_OIF_AIOPLL_01_O24A0_T     oif_aiopll_01;           // 0xCC93_2014
    DRG_CTRL_OIF_AIOPLL_02_O24A0_T     oif_aiopll_02;           // 0xCC93_2018
    UINT32                             _rsvd_01[1];             // 0xCC93_201C
    DRG_CTRL_PQE_FRPLL_00_O24A0_T      pqe_frpll_00;            // 0xCC93_2020
    DRG_CTRL_PQE_FRPLL_01_O24A0_T      pqe_frpll_01;            // 0xCC93_2024
    DRG_CTRL_PQE_FRPLL_02_O24A0_T      pqe_frpll_02;            // 0xCC93_2028
    DRG_CTRL_PQE_FRPLL_SSCG_R00_O24A0_T    pqe_frpll_sscg_r00;    // 0xCC93_202C
    DRG_CTRL_PQE_FRPLL_03_O24A0_T      pqe_frpll_03;            // 0xCC93_2030
    UINT32                             _rsvd_02[11];            // 0xCC93_2034 ~ 0xCC93_205C
    DRG_CTRL_CRG_TOP_04_O24A0_T        crg_top_04 ;             // 0xCC93_2060
    DRG_CTRL_CRG_TOP_05_O24A0_T        crg_top_05 ;             // 0xCC93_2064
    DRG_CTRL_CRG_TOP_06_O24A0_T        crg_top_06 ;             // 0xCC93_2068
}DRG_CTRL_REG_O24A0_T;
/* 14 regs */

#ifdef __cplusplus
}
#endif

#endif

/*----------------------------------------------------------------------------------------
  Reference Header (Another Header Structure)
---------------------------------------------------------------------------------------*/

#ifdef HEADER_2

#ifdef __cplusplus
extern "C" {
#endif

#define BASEADDRESS 0

#define DRG_CTRL_DISP_AIOPLLSS_00_O24A0_T_OFF               (BASEADDRESS+0x0000)
#define DRG_CTRL_DISP_AIOPLLSS_01_O24A0_T_OFF               (BASEADDRESS+0x0004)
#define DRG_CTRL_DISP_AIOPLLSS_02_O24A0_T_OFF               (BASEADDRESS+0x0008)
#define DRG_CTRL_OIF_AIOPLL_00_O24A0_T_OFF                  (BASEADDRESS+0x0010)
#define DRG_CTRL_OIF_AIOPLL_01_O24A0_T_OFF                  (BASEADDRESS+0x0014)
#define DRG_CTRL_OIF_AIOPLL_02_O24A0_T_OFF                  (BASEADDRESS+0x0018)
#define DRG_CTRL_PQE_FRPLL_00_O24A0_T_OFF                   (BASEADDRESS+0x0020)
#define DRG_CTRL_PQE_FRPLL_01_O24A0_T_OFF                   (BASEADDRESS+0x0024)
#define DRG_CTRL_PQE_FRPLL_02_O24A0_T_OFF                   (BASEADDRESS+0x0028)
#define DRG_CTRL_PQE_FRPLL_SSCG_R00_O24A0_T_OFF             (BASEADDRESS+0x002C)
#define DRG_CTRL_PQE_FRPLL_03_O24A0_T_OFF                   (BASEADDRESS+0x0030)
#define DRG_CTRL_CRG_TOP_04_O24A0_T_OFF                     (BASEADDRESS+0x0060)
#define DRG_CTRL_CRG_TOP_05_O24A0_T_OFF                     (BASEADDRESS+0x0064)
#define DRG_CTRL_CRG_TOP_06_O24A0_T_OFF                     (BASEADDRESS+0x0068)

/*-----------------------------------------------------------------------------------------
    0xCC93_2000    disp_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_disp_aiopllss_dss: 1;    //     3
    UINT32 reg_disp_aiopllss_cih2: 4;    //  7:4
    UINT32 reg_disp_aiopllss_cih: 4;    //  11:8
    UINT32 reg_disp_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_disp_aiopllss_npc: 6;    //  21:16
    UINT32 resvd01            :  2;    //  23:22 reserved
    UINT32 reg_disp_aiopllss_m:  6;    //  29:24
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}DRG_CTRL_DISP_AIOPLLSS_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2004    disp_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_aiopllss_out_div: 7;    //  6:0
    UINT32 resvd00            :  5;    //  11: 7 reserved
    UINT32 reg_disp_aiopllss_mod_freq_max: 9;    //  20:12
    UINT32 resvd01            :  3;    //  23:21 reserved
    UINT32 reg_disp_aiopllss_updn_max: 7;    //  30:24
    UINT32 resvd02            :  1;    //  31:31 reserved
    };
}DRG_CTRL_DISP_AIOPLLSS_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2008    disp_aiopllss_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_aiopllss_fout1_en: 1;    //  0
    UINT32 reg_disp_aiopllss_freq_update: 1;    //  1
    UINT32 reg_disp_aiopllss_sync_on: 1;    //  2
    UINT32 reg_disp_aiopllss_wake_bypass: 1;    //  3
    UINT32 reg_disp_aiopllss_offset_mode: 1;    //  4
    UINT32 reg_disp_aiopllss_fine_div: 1;    //  5
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_disp_aiopllss_fine_control: 3;    //  10:8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_disp_aiopllss_offset: 8;    //  19:12
    UINT32 resvd02            : 12;    //  31:20 reserved
    };
}DRG_CTRL_DISP_AIOPLLSS_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2010    oif_aiopll_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_oif_aiopll_fine_div: 1;    //   1
    UINT32 reg_oif_aiopll_dss :  1;    //      2
    UINT32 reg_oif_aiopll_accuracy: 2;    //  4:3
    UINT32 reg_oif_aiopll_updn_max: 7;    //  11:5
    UINT32 reg_oif_aiopll_mod_freq_max: 9;    //  20:12
    UINT32 reg_oif_aiopll_m   :  6;    //  26:21
    UINT32 resvd01            :  1;    //     27 reserved
    UINT32 reg_oif_aiopll_cih :  4;    //  31:28
    };
}DRG_CTRL_OIF_AIOPLL_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2014    oif_aiopll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_oif_aiopll_offset_mode: 1;    //  4
    UINT32 reg_oif_aiopll_fout3_post_od: 3;    //  7:5
    UINT32 reg_oif_aiopll_fout2_post_od: 3;    //  10:8
    UINT32 reg_oif_aiopll_fout_od: 2;    //  12:11
    UINT32 reg_oif_aiopll_fout3_pre_od: 3;    //  15:13
    UINT32 reg_oif_aiopll_fout2_pre_od: 3;    //  18:16
    UINT32 reg_oif_aiopll_nsc :  4;    //  22:19
    UINT32 reg_oif_aiopll_npc :  6;    //  28:23
    UINT32 reg_oif_aiopll_fine_control: 3;    //  31:29
    };
}DRG_CTRL_OIF_AIOPLL_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2018    oif_aiopll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_oif_aiopll_out_sel: 1;    //    0
    UINT32 reg_oif_aiopll_freq_update: 1;    //  1
    UINT32 reg_oif_aiopll_sync_on: 1;    //    2
    UINT32 reg_oif_aiopll_in_sel: 1;    //     3
    UINT32 resvd00            : 18;    //  21: 4 reserved
    UINT32 reg_oif_aiopll_wake_bypass: 1;    //  22
    UINT32 reg_oif_aiopll_ddr_mode: 1;    //  23
    UINT32 reg_oif_aiopll_offset: 8;    //  31:24
    };
}DRG_CTRL_OIF_AIOPLL_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2020    pqe_frpll_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_pqe_frpll_in_divsel: 1;    //   1
    UINT32 reg_pqe_frpll_lpf_on: 1;    //      2
    UINT32 reg_pqe_frpll_fout2_en: 1;    //    3
    UINT32 reg_pqe_frpll_wakeup_bypass: 1;    //  4
    UINT32 reg_pqe_frpll_divint: 9;    //  13: 5
    UINT32 resvd01            :  1;    //     14 reserved
    UINT32 reg_pqe_frpll_dsmon:  1;    //     15
    UINT32 reg_pqe_frpll_auto_freq: 1;    //  16
    UINT32 reg_pqe_frpll_dsm_limit: 1;    //  17
    UINT32 reg_pqe_frpll_fin_sel: 1;    //    18
    UINT32 reg_pqe_frpll_icp  :  4;    //  22:19
    UINT32 reg_pqe_frpll_out_div: 9;    //  31:23
    };
}DRG_CTRL_PQE_FRPLL_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2024    pqe_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_frpll_fout_en: 1;    //     0
    UINT32 reg_pqe_frpll_syncon: 1;    //      1
    UINT32 reg_pqe_frpll_m    :  6;    //   7: 2
    UINT32 reg_pqe_frpll_fcw  : 24;    //  31: 8
    };
}DRG_CTRL_PQE_FRPLL_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2028    pqe_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  5;    //   4: 0 reserved
    UINT32 reg_pqe_frpll_out_div3: 9;    //  13:5
    UINT32 reg_pqe_frpll_out_div2: 9;    //  22:14
    UINT32 reg_pqe_frpll_frequp: 1;    //     23
    UINT32 reg_pqe_frpll_a    :  6;    //  29:24
    UINT32 reg_pqe_frpll_in_divrstb: 1;    //  30
    UINT32 reg_pqe_frpll_icp_g:  1;    //     31
    };
}DRG_CTRL_PQE_FRPLL_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_202C    pqe_frpll_sscg_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_frpll_updn_max: 8;    //  7:0
    UINT32 reg_pqe_frpll_mod_speed_max: 9;    //  16:8
    UINT32 resvd00            :  7;    //  23:17 reserved
    UINT32 reg_pqe_frpll_lock_cont: 1;    //  24
    UINT32 reg_pqe_frpll_dss  :  1;    //     25
    UINT32 resvd01            :  5;    //  30:26 reserved
    UINT32 reg_pqe_soft_reset_frpll_sscg: 1;    //  31
    };
}DRG_CTRL_PQE_FRPLL_SSCG_R00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2030    pqe_frpll_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_divint_mux_sel: 2;    //  1:0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_pqe_fcw_mux_sel:  2;    //   5: 4
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}DRG_CTRL_PQE_FRPLL_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2060    crg_top_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_sel_disp735:  1;    //      0
    UINT32 reg_disp735_clk_gate_en: 1;    //   1
    UINT32 reg_pll_sel_din735 :  1;    //      2
    UINT32 reg_din735_clk_gate_en: 1;    //    3
    UINT32 reg_clk_sel_oif    :  1;    //      4
    UINT32 reg_oif_clk_gate_en:  1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}DRG_CTRL_CRG_TOP_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2064    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rxclkdrv_c4tx_smv: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}DRG_CTRL_CRG_TOP_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC93_2068    crg_top_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_drg_pll_mon_en :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}DRG_CTRL_CRG_TOP_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    drg_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    DRG_CTRL_DISP_AIOPLLSS_00_O24A0_T    disp_aiopllss_00;      // 0xCC93_2000
    DRG_CTRL_DISP_AIOPLLSS_01_O24A0_T    disp_aiopllss_01;      // 0xCC93_2004
    DRG_CTRL_DISP_AIOPLLSS_02_O24A0_T    disp_aiopllss_02;      // 0xCC93_2008
    UINT32                             _rsvd_00[1];             // 0xCC93_200C
    DRG_CTRL_OIF_AIOPLL_00_O24A0_T     oif_aiopll_00;           // 0xCC93_2010
    DRG_CTRL_OIF_AIOPLL_01_O24A0_T     oif_aiopll_01;           // 0xCC93_2014
    DRG_CTRL_OIF_AIOPLL_02_O24A0_T     oif_aiopll_02;           // 0xCC93_2018
    UINT32                             _rsvd_01[1];             // 0xCC93_201C
    DRG_CTRL_PQE_FRPLL_00_O24A0_T      pqe_frpll_00;            // 0xCC93_2020
    DRG_CTRL_PQE_FRPLL_01_O24A0_T      pqe_frpll_01;            // 0xCC93_2024
    DRG_CTRL_PQE_FRPLL_02_O24A0_T      pqe_frpll_02;            // 0xCC93_2028
    DRG_CTRL_PQE_FRPLL_SSCG_R00_O24A0_T    pqe_frpll_sscg_r00;    // 0xCC93_202C
    DRG_CTRL_PQE_FRPLL_03_O24A0_T      pqe_frpll_03;            // 0xCC93_2030
    UINT32                             _rsvd_02[11];            // 0xCC93_2034 ~ 0xCC93_205C
    DRG_CTRL_CRG_TOP_04_O24A0_T        crg_top_04 ;             // 0xCC93_2060
    DRG_CTRL_CRG_TOP_05_O24A0_T        crg_top_05 ;             // 0xCC93_2064
    DRG_CTRL_CRG_TOP_06_O24A0_T        crg_top_06 ;             // 0xCC93_2068
}DRG_CTRL_REG_O24A0_T;
/* 14 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _DRG_CTRL_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

