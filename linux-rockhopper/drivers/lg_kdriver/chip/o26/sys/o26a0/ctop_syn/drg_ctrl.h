#ifndef _DRG_CTRL_REG_O26A0_H_
#define _DRG_CTRL_REG_O26A0_H_

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
    0xCC97_5000    disp_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopllss_accuracy:  2,    //   1: 0
                              :  1,    //      2 reserved
    reg_disp_aiopllss_dss     :  1,    //      3
                              :  4,    //   7: 4 reserved
    reg_disp_aiopllss_cih     :  4,    //  11: 8
    reg_disp_aiopllss_nsc     :  4,    //  15:12
    reg_disp_aiopllss_npc     :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_disp_aiopllss_m       :  6,    //  29:24
                              :  2;    //  31:30 reserved
}DRG_CTRL_DISP_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5004    disp_aiopllss_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_disp_aiopllss_out_div :  7,    //   6: 0
                              :  5,    //  11: 7 reserved
    reg_disp_aiopllss_mod_freq_max: 9,    //  20:12
                              :  3,    //  23:21 reserved
    reg_disp_aiopllss_updn_max:  7,    //  30:24
                              :  1;    //  31:31 reserved
}DRG_CTRL_DISP_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5008    disp_aiopllss_02 ''
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
}DRG_CTRL_DISP_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5010    oif_aiopll_00 ''
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
}DRG_CTRL_OIF_AIOPLL_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5014    oif_aiopll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_oif_aiopll_offset_mode:  1,    //      0
    reg_oif_aiopll_fout3_od   :  7,    //   7: 1
    reg_oif_aiopll_fout2_od   :  7,    //  14: 8
    reg_oif_aiopll_fout1_od   :  7,    //  21:15
    reg_oif_aiopll_nsc        :  4,    //  25:22
    reg_oif_aiopll_npc        :  6;    //  31:26
}DRG_CTRL_OIF_AIOPLL_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5018    oif_aiopll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_oif_aiopll_freq_update:  1,    //      1
    reg_oif_aiopll_sync_on    :  1,    //      2
    reg_oif_aiopll_in_sel     :  1,    //      3
    reg_oif_aiopll_fine_control: 3,    //   6: 4
    reg_oif_aiopll_fout3_en   :  1,    //      7
    reg_oif_aiopll_fout2_en   :  1,    //      8
    reg_oif_aiopll_fout1_en   :  1,    //      9
    reg_oif_aiopll_lbenl      :  1,    //     10
    reg_oif_aiopll_vco_bypass :  1,    //     11
                              : 10,    //  21:12 reserved
    reg_oif_aiopll_wake_bypass:  1,    //     22
                              :  1,    //     23 reserved
    reg_oif_aiopll_offset     :  8;    //  31:24
}DRG_CTRL_OIF_AIOPLL_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5020    pqe_frpll_00 ''
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
}DRG_CTRL_PQE_FRPLL_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5024    pqe_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_frpll_fout_en     :  1,    //      0
    reg_pqe_frpll_syncon      :  1,    //      1
    reg_pqe_frpll_m           :  6,    //   7: 2
    reg_pqe_frpll_fcw         : 24;    //  31: 8
}DRG_CTRL_PQE_FRPLL_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5028    pqe_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_frpll_fb_out      :  1,    //      0
                              :  4,    //   4: 1 reserved
    reg_pqe_frpll_out_div3    :  9,    //  13: 5
    reg_pqe_frpll_out_div2    :  9,    //  22:14
    reg_pqe_frpll_frequp      :  1,    //     23
    reg_pqe_frpll_a           :  6,    //  29:24
    reg_pqe_frpll_in_divrstb  :  1,    //     30
    reg_pqe_frpll_icp_g       :  1;    //     31
}DRG_CTRL_PQE_FRPLL_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_502C    pqe_frpll_sscg_r00 ''
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
}DRG_CTRL_PQE_FRPLL_SSCG_R00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5030    pqe_frpll_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_divint_mux_sel    :  2,    //   1: 0
                              :  2,    //   3: 2 reserved
    reg_pqe_fcw_mux_sel       :  2,    //   5: 4
                              : 26;    //   31:6 reserved
}DRG_CTRL_PQE_FRPLL_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5060    crg_top_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_sel_disp780       :  1,    //      0
    reg_pll_sel_xtal          :  1,    //      1
    reg_disp780_clk_gate_en   :  1,    //      2
    reg_din780_clk_gate_en    :  1,    //      3
    reg_oif_clk_gate_en       :  1,    //      4
                              : 27;    //   31:5 reserved
}DRG_CTRL_CRG_TOP_04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5064    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_c4tx_smv     :  1,    //      0
                              : 31;    //   31:1 reserved
}DRG_CTRL_CRG_TOP_05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5068    crg_top_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_drg_pll_mon_en        :  1,    //      0
                              : 31;    //   31:1 reserved
}DRG_CTRL_CRG_TOP_06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_506C    rxclkdrv_md_usb ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_md_usb_pdb   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_md_usb_div2_enb: 1,    //     4
                              : 27;    //   31:5 reserved
}DRG_CTRL_RXCLKDRV_MD_USB_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5070    rxclkdrv_drg ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txclkdrv_drg_pdb      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_drg_div2_enb :  1,    //      4
                              : 27;    //   31:5 reserved
}DRG_CTRL_RXCLKDRV_DRG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    drg_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    DRG_CTRL_DISP_AIOPLLSS_00_O26A0_T    disp_aiopllss_00;      // 0xCC97_5000
    DRG_CTRL_DISP_AIOPLLSS_01_O26A0_T    disp_aiopllss_01;      // 0xCC97_5004
    DRG_CTRL_DISP_AIOPLLSS_02_O26A0_T    disp_aiopllss_02;      // 0xCC97_5008
    UINT32                             _rsvd_00[1];             // 0xCC97_500C
    DRG_CTRL_OIF_AIOPLL_00_O26A0_T     oif_aiopll_00;           // 0xCC97_5010
    DRG_CTRL_OIF_AIOPLL_01_O26A0_T     oif_aiopll_01;           // 0xCC97_5014
    DRG_CTRL_OIF_AIOPLL_02_O26A0_T     oif_aiopll_02;           // 0xCC97_5018
    UINT32                             _rsvd_01[1];             // 0xCC97_501C
    DRG_CTRL_PQE_FRPLL_00_O26A0_T      pqe_frpll_00;            // 0xCC97_5020
    DRG_CTRL_PQE_FRPLL_01_O26A0_T      pqe_frpll_01;            // 0xCC97_5024
    DRG_CTRL_PQE_FRPLL_02_O26A0_T      pqe_frpll_02;            // 0xCC97_5028
    DRG_CTRL_PQE_FRPLL_SSCG_R00_O26A0_T    pqe_frpll_sscg_r00;    // 0xCC97_502C
    DRG_CTRL_PQE_FRPLL_03_O26A0_T      pqe_frpll_03;            // 0xCC97_5030
    UINT32                             _rsvd_02[11];            // 0xCC97_5034 ~ 0xCC97_505C
    DRG_CTRL_CRG_TOP_04_O26A0_T        crg_top_04 ;             // 0xCC97_5060
    DRG_CTRL_CRG_TOP_05_O26A0_T        crg_top_05 ;             // 0xCC97_5064
    DRG_CTRL_CRG_TOP_06_O26A0_T        crg_top_06 ;             // 0xCC97_5068
    DRG_CTRL_RXCLKDRV_MD_USB_O26A0_T    rxclkdrv_md_usb;        // 0xCC97_506C
    DRG_CTRL_RXCLKDRV_DRG_O26A0_T      rxclkdrv_drg;            // 0xCC97_5070
}DRG_CTRL_REG_O26A0_T;
/* 16 regs */

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

#define DRG_CTRL_DISP_AIOPLLSS_00_O26A0_T_OFF               (BASEADDRESS+0x0000)
#define DRG_CTRL_DISP_AIOPLLSS_01_O26A0_T_OFF               (BASEADDRESS+0x0004)
#define DRG_CTRL_DISP_AIOPLLSS_02_O26A0_T_OFF               (BASEADDRESS+0x0008)
#define DRG_CTRL_OIF_AIOPLL_00_O26A0_T_OFF                  (BASEADDRESS+0x0010)
#define DRG_CTRL_OIF_AIOPLL_01_O26A0_T_OFF                  (BASEADDRESS+0x0014)
#define DRG_CTRL_OIF_AIOPLL_02_O26A0_T_OFF                  (BASEADDRESS+0x0018)
#define DRG_CTRL_PQE_FRPLL_00_O26A0_T_OFF                   (BASEADDRESS+0x0020)
#define DRG_CTRL_PQE_FRPLL_01_O26A0_T_OFF                   (BASEADDRESS+0x0024)
#define DRG_CTRL_PQE_FRPLL_02_O26A0_T_OFF                   (BASEADDRESS+0x0028)
#define DRG_CTRL_PQE_FRPLL_SSCG_R00_O26A0_T_OFF             (BASEADDRESS+0x002C)
#define DRG_CTRL_PQE_FRPLL_03_O26A0_T_OFF                   (BASEADDRESS+0x0030)
#define DRG_CTRL_CRG_TOP_04_O26A0_T_OFF                     (BASEADDRESS+0x0060)
#define DRG_CTRL_CRG_TOP_05_O26A0_T_OFF                     (BASEADDRESS+0x0064)
#define DRG_CTRL_CRG_TOP_06_O26A0_T_OFF                     (BASEADDRESS+0x0068)
#define DRG_CTRL_RXCLKDRV_MD_USB_O26A0_T_OFF                (BASEADDRESS+0x006C)
#define DRG_CTRL_RXCLKDRV_DRG_O26A0_T_OFF                   (BASEADDRESS+0x0070)

/*-----------------------------------------------------------------------------------------
    0xCC97_5000    disp_aiopllss_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_disp_aiopllss_accuracy: 2;    //  1:0
    UINT32 resvd00            :  1;    //      2 reserved
    UINT32 reg_disp_aiopllss_dss: 1;    //     3
    UINT32 resvd01            :  4;    //   7: 4 reserved
    UINT32 reg_disp_aiopllss_cih: 4;    //  11:8
    UINT32 reg_disp_aiopllss_nsc: 4;    //  15:12
    UINT32 reg_disp_aiopllss_npc: 6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_disp_aiopllss_m:  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}DRG_CTRL_DISP_AIOPLLSS_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5004    disp_aiopllss_01 ''
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
}DRG_CTRL_DISP_AIOPLLSS_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5008    disp_aiopllss_02 ''
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
}DRG_CTRL_DISP_AIOPLLSS_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5010    oif_aiopll_00 ''
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
}DRG_CTRL_OIF_AIOPLL_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5014    oif_aiopll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_oif_aiopll_offset_mode: 1;    //  0
    UINT32 reg_oif_aiopll_fout3_od: 7;    //  7:1
    UINT32 reg_oif_aiopll_fout2_od: 7;    //  14:8
    UINT32 reg_oif_aiopll_fout1_od: 7;    //  21:15
    UINT32 reg_oif_aiopll_nsc :  4;    //  25:22
    UINT32 reg_oif_aiopll_npc :  6;    //  31:26
    };
}DRG_CTRL_OIF_AIOPLL_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5018    oif_aiopll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_oif_aiopll_freq_update: 1;    //  1
    UINT32 reg_oif_aiopll_sync_on: 1;    //    2
    UINT32 reg_oif_aiopll_in_sel: 1;    //     3
    UINT32 reg_oif_aiopll_fine_control: 3;    //  6:4
    UINT32 reg_oif_aiopll_fout3_en: 1;    //   7
    UINT32 reg_oif_aiopll_fout2_en: 1;    //   8
    UINT32 reg_oif_aiopll_fout1_en: 1;    //   9
    UINT32 reg_oif_aiopll_lbenl: 1;    //     10
    UINT32 reg_oif_aiopll_vco_bypass: 1;    //  11
    UINT32 resvd01            : 10;    //  21:12 reserved
    UINT32 reg_oif_aiopll_wake_bypass: 1;    //  22
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_oif_aiopll_offset: 8;    //  31:24
    };
}DRG_CTRL_OIF_AIOPLL_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5020    pqe_frpll_00 ''
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
}DRG_CTRL_PQE_FRPLL_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5024    pqe_frpll_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_frpll_fout_en: 1;    //     0
    UINT32 reg_pqe_frpll_syncon: 1;    //      1
    UINT32 reg_pqe_frpll_m    :  6;    //   7: 2
    UINT32 reg_pqe_frpll_fcw  : 24;    //  31: 8
    };
}DRG_CTRL_PQE_FRPLL_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5028    pqe_frpll_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_frpll_fb_out: 1;    //      0
    UINT32 resvd00            :  4;    //   4: 1 reserved
    UINT32 reg_pqe_frpll_out_div3: 9;    //  13:5
    UINT32 reg_pqe_frpll_out_div2: 9;    //  22:14
    UINT32 reg_pqe_frpll_frequp: 1;    //     23
    UINT32 reg_pqe_frpll_a    :  6;    //  29:24
    UINT32 reg_pqe_frpll_in_divrstb: 1;    //  30
    UINT32 reg_pqe_frpll_icp_g:  1;    //     31
    };
}DRG_CTRL_PQE_FRPLL_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_502C    pqe_frpll_sscg_r00 ''
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
}DRG_CTRL_PQE_FRPLL_SSCG_R00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5030    pqe_frpll_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pqe_divint_mux_sel: 2;    //  1:0
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_pqe_fcw_mux_sel:  2;    //   5: 4
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}DRG_CTRL_PQE_FRPLL_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5060    crg_top_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_sel_disp780:  1;    //      0
    UINT32 reg_pll_sel_xtal   :  1;    //      1
    UINT32 reg_disp780_clk_gate_en: 1;    //   2
    UINT32 reg_din780_clk_gate_en: 1;    //    3
    UINT32 reg_oif_clk_gate_en:  1;    //      4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}DRG_CTRL_CRG_TOP_04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5064    crg_top_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rxclkdrv_c4tx_smv: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}DRG_CTRL_CRG_TOP_05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5068    crg_top_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_drg_pll_mon_en :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}DRG_CTRL_CRG_TOP_06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_506C    rxclkdrv_md_usb ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_md_usb_pdb: 1;    //   0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_md_usb_div2_enb: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}DRG_CTRL_RXCLKDRV_MD_USB_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_5070    rxclkdrv_drg ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txclkdrv_drg_pdb: 1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_drg_div2_enb: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}DRG_CTRL_RXCLKDRV_DRG_O26A0_T;

/*-----------------------------------------------------------------------------------------
    drg_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    DRG_CTRL_DISP_AIOPLLSS_00_O26A0_T    disp_aiopllss_00;      // 0xCC97_5000
    DRG_CTRL_DISP_AIOPLLSS_01_O26A0_T    disp_aiopllss_01;      // 0xCC97_5004
    DRG_CTRL_DISP_AIOPLLSS_02_O26A0_T    disp_aiopllss_02;      // 0xCC97_5008
    UINT32                             _rsvd_00[1];             // 0xCC97_500C
    DRG_CTRL_OIF_AIOPLL_00_O26A0_T     oif_aiopll_00;           // 0xCC97_5010
    DRG_CTRL_OIF_AIOPLL_01_O26A0_T     oif_aiopll_01;           // 0xCC97_5014
    DRG_CTRL_OIF_AIOPLL_02_O26A0_T     oif_aiopll_02;           // 0xCC97_5018
    UINT32                             _rsvd_01[1];             // 0xCC97_501C
    DRG_CTRL_PQE_FRPLL_00_O26A0_T      pqe_frpll_00;            // 0xCC97_5020
    DRG_CTRL_PQE_FRPLL_01_O26A0_T      pqe_frpll_01;            // 0xCC97_5024
    DRG_CTRL_PQE_FRPLL_02_O26A0_T      pqe_frpll_02;            // 0xCC97_5028
    DRG_CTRL_PQE_FRPLL_SSCG_R00_O26A0_T    pqe_frpll_sscg_r00;    // 0xCC97_502C
    DRG_CTRL_PQE_FRPLL_03_O26A0_T      pqe_frpll_03;            // 0xCC97_5030
    UINT32                             _rsvd_02[11];            // 0xCC97_5034 ~ 0xCC97_505C
    DRG_CTRL_CRG_TOP_04_O26A0_T        crg_top_04 ;             // 0xCC97_5060
    DRG_CTRL_CRG_TOP_05_O26A0_T        crg_top_05 ;             // 0xCC97_5064
    DRG_CTRL_CRG_TOP_06_O26A0_T        crg_top_06 ;             // 0xCC97_5068
    DRG_CTRL_RXCLKDRV_MD_USB_O26A0_T    rxclkdrv_md_usb;        // 0xCC97_506C
    DRG_CTRL_RXCLKDRV_DRG_O26A0_T      rxclkdrv_drg;            // 0xCC97_5070
}DRG_CTRL_REG_O26A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_DRG_CTRL_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

