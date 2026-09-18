#ifndef _BND_CTRL_M0_REG_H_
#define _BND_CTRL_M0_REG_H_

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
    0xC67F_2000    aiopllss_m0_o22_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    o22_reg_aiopll_cih        :  4,    //   3: 0
    o22_reg_aiopll_fine_control: 3,    //   6: 4
                              :  1,    //      7 reserved
    o22_reg_aiopll_fine_div   :  1,    //      8
    o22_reg_aiopll_fout_od    :  2,    //  10: 9
                              :  1,    //     11 reserved
    o22_reg_aiopll_nsc        :  4,    //  15:12
    o22_reg_aiopll_npc        :  6,    //  21:16
                              :  2,    //  23:22 reserved
    o22_reg_aiopll_m          :  6,    //  29:24
                              :  2;    //  31:30 reserved
}BND_CTRL_M0_AIOPLLSS_M0_O22_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2004    aiopllss_m0_o22_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    o22_reg_aiopll_mod_freq_max: 9,    //   8: 0
                              :  3,    //  11: 9 reserved
    o22_reg_aiopll_updn_max   :  7,    //  18:12
                              :  1,    //     19 reserved
    o22_reg_aiopll_accuracy   :  2,    //  21:20
                              :  1,    //     22 reserved
    o22_reg_aiopll_dss        :  1,    //     23
    o22_reg_aiopll_offset     :  8;    //  31:24
}BND_CTRL_M0_AIOPLLSS_M0_O22_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2008    aiopllss_m0_o22_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    o22_reg_aiopll_freq_update:  1,    //      0
                              :  3,    //   3: 1 reserved
    o22_reg_aiopll_fout3_post_od: 3,    //  6: 4
                              :  5,    //  11: 7 reserved
    o22_reg_aiopll_fout3_pre_od: 3,    //  14:12
                              :  1,    //     15 reserved
    o22_reg_aiopll_fout2_post_od: 3,    //  18:16
                              :  1,    //     19 reserved
    o22_reg_aiopll_fout2_pre_od: 3,    //  22:20
                              :  1,    //     23 reserved
    o22_reg_aiopll_sync_on    :  1,    //     24
                              :  2,    //  26:25 reserved
    o22_reg_aiopll_wake_bypass:  1,    //     27
    o22_reg_aiopll_offset_mode:  1,    //     28
                              :  2,    //  30:29 reserved
    o22_reg_aiopll_ddr_mode   :  1;    //     31
}BND_CTRL_M0_AIOPLLSS_M0_O22_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2010    aiopllss_m0_f22_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    f22_reg_aiopll_cih        :  4,    //   3: 0
    f22_reg_aiopll_fine_control: 3,    //   6: 4
                              :  1,    //      7 reserved
    f22_reg_aiopll_fine_div   :  1,    //      8
    f22_reg_aiopll_fout_od    :  2,    //  10: 9
                              :  1,    //     11 reserved
    f22_reg_aiopll_nsc        :  4,    //  15:12
    f22_reg_aiopll_npc        :  6,    //  21:16
                              :  2,    //  23:22 reserved
    f22_reg_aiopll_m          :  6,    //  29:24
                              :  2;    //  31:30 reserved
}BND_CTRL_M0_AIOPLLSS_M0_F22_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2014    aiopllss_m0_f22_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    f22_reg_aiopll_mod_freq_max: 9,    //   8: 0
                              :  3,    //  11: 9 reserved
    f22_reg_aiopll_updn_max   :  7,    //  18:12
                              :  1,    //     19 reserved
    f22_reg_aiopll_accuracy   :  2,    //  21:20
                              :  1,    //     22 reserved
    f22_reg_aiopll_dss        :  1,    //     23
    f22_reg_aiopll_offset     :  8;    //  31:24
}BND_CTRL_M0_AIOPLLSS_M0_F22_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2018    aiopllss_m0_f22_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    f22_reg_aiopll_freq_update:  1,    //      0
                              :  3,    //   3: 1 reserved
    f22_reg_aiopll_fout3_post_od: 3,    //  6: 4
                              :  5,    //  11: 7 reserved
    f22_reg_aiopll_fout3_pre_od: 3,    //  14:12
                              :  1,    //     15 reserved
    f22_reg_aiopll_fout2_post_od: 3,    //  18:16
                              :  1,    //     19 reserved
    f22_reg_aiopll_fout2_pre_od: 3,    //  22:20
                              :  1,    //     23 reserved
    f22_reg_aiopll_sync_on    :  1,    //     24
                              :  2,    //  26:25 reserved
    f22_reg_aiopll_wake_bypass:  1,    //     27
    f22_reg_aiopll_offset_mode:  1,    //     28
                              :  2,    //  30:29 reserved
    f22_reg_aiopll_ddr_mode   :  1;    //     31
}BND_CTRL_M0_AIOPLLSS_M0_F22_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2020    pll_mon00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    mon_gfmrbgen_update_lockd :  1,    //      0
    mon_pll_lockd             :  1,    //      1
    mon_gfmrbgen_lockhold_lockd: 1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_M0_PLL_MON00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2024    pll_mon01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_gfm_lockd_en          :  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_M0_PLL_MON01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_m0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_M0_AIOPLLSS_M0_O22_R00_O22A0_T    aiopllss_m0_o22_r00;    // 0xC67F_2000
    BND_CTRL_M0_AIOPLLSS_M0_O22_R01_O22A0_T    aiopllss_m0_o22_r01;    // 0xC67F_2004
    BND_CTRL_M0_AIOPLLSS_M0_O22_R02_O22A0_T    aiopllss_m0_o22_r02;    // 0xC67F_2008
    UINT32                             _rsvd_00[1];             // 0xC67F_200C
    BND_CTRL_M0_AIOPLLSS_M0_F22_R00_O22A0_T    aiopllss_m0_f22_r00;    // 0xC67F_2010
    BND_CTRL_M0_AIOPLLSS_M0_F22_R01_O22A0_T    aiopllss_m0_f22_r01;    // 0xC67F_2014
    BND_CTRL_M0_AIOPLLSS_M0_F22_R02_O22A0_T    aiopllss_m0_f22_r02;    // 0xC67F_2018
    UINT32                             _rsvd_01[1];             // 0xC67F_201C
    BND_CTRL_M0_PLL_MON00_O22A0_T           pll_mon00  ;             // 0xC67F_2020
    BND_CTRL_M0_PLL_MON01_O22A0_T           pll_mon01  ;             // 0xC67F_2024
}BND_CTRL_M0_REG_O22A0_T;
/* 8 regs */

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

#define BND_CTRL_M0_AIOPLLSS_M0_O22_R00_O22A0_T_OFF              (BASEADDRESS+0x0000)
#define BND_CTRL_M0_AIOPLLSS_M0_O22_R01_O22A0_T_OFF              (BASEADDRESS+0x0004)
#define BND_CTRL_M0_AIOPLLSS_M0_O22_R02_O22A0_T_OFF              (BASEADDRESS+0x0008)
#define BND_CTRL_M0_AIOPLLSS_M0_F22_R00_O22A0_T_OFF              (BASEADDRESS+0x0010)
#define BND_CTRL_M0_AIOPLLSS_M0_F22_R01_O22A0_T_OFF              (BASEADDRESS+0x0014)
#define BND_CTRL_M0_AIOPLLSS_M0_F22_R02_O22A0_T_OFF              (BASEADDRESS+0x0018)
#define BND_CTRL_M0_PLL_MON00_O22A0_T_OFF                        (BASEADDRESS+0x0020)
#define BND_CTRL_M0_PLL_MON01_O22A0_T_OFF                        (BASEADDRESS+0x0024)

/*-----------------------------------------------------------------------------------------
    0xC67F_2000    aiopllss_m0_o22_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 o22_reg_aiopll_cih :  4;    //   3: 0
    UINT32 o22_reg_aiopll_fine_control: 3;    //  6:4
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 o22_reg_aiopll_fine_div: 1;    //   8
    UINT32 o22_reg_aiopll_fout_od: 2;    //  10:9
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 o22_reg_aiopll_nsc :  4;    //  15:12
    UINT32 o22_reg_aiopll_npc :  6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 o22_reg_aiopll_m   :  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}BND_CTRL_M0_AIOPLLSS_M0_O22_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2004    aiopllss_m0_o22_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 o22_reg_aiopll_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 o22_reg_aiopll_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 o22_reg_aiopll_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 o22_reg_aiopll_dss :  1;    //     23
    UINT32 o22_reg_aiopll_offset: 8;    //  31:24
    };
}BND_CTRL_M0_AIOPLLSS_M0_O22_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2008    aiopllss_m0_o22_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 o22_reg_aiopll_freq_update: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 o22_reg_aiopll_fout3_post_od: 3;    //  6:4
    UINT32 resvd01            :  5;    //  11: 7 reserved
    UINT32 o22_reg_aiopll_fout3_pre_od: 3;    //  14:12
    UINT32 resvd02            :  1;    //     15 reserved
    UINT32 o22_reg_aiopll_fout2_post_od: 3;    //  18:16
    UINT32 resvd03            :  1;    //     19 reserved
    UINT32 o22_reg_aiopll_fout2_pre_od: 3;    //  22:20
    UINT32 resvd04            :  1;    //     23 reserved
    UINT32 o22_reg_aiopll_sync_on: 1;    //   24
    UINT32 resvd05            :  2;    //  26:25 reserved
    UINT32 o22_reg_aiopll_wake_bypass: 1;    //  27
    UINT32 o22_reg_aiopll_offset_mode: 1;    //  28
    UINT32 resvd06            :  2;    //  30:29 reserved
    UINT32 o22_reg_aiopll_ddr_mode: 1;    //  31
    };
}BND_CTRL_M0_AIOPLLSS_M0_O22_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2010    aiopllss_m0_f22_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 f22_reg_aiopll_cih :  4;    //   3: 0
    UINT32 f22_reg_aiopll_fine_control: 3;    //  6:4
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 f22_reg_aiopll_fine_div: 1;    //   8
    UINT32 f22_reg_aiopll_fout_od: 2;    //  10:9
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 f22_reg_aiopll_nsc :  4;    //  15:12
    UINT32 f22_reg_aiopll_npc :  6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 f22_reg_aiopll_m   :  6;    //  29:24
    UINT32 resvd03            :  2;    //  31:30 reserved
    };
}BND_CTRL_M0_AIOPLLSS_M0_F22_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2014    aiopllss_m0_f22_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 f22_reg_aiopll_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 f22_reg_aiopll_updn_max: 7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 f22_reg_aiopll_accuracy: 2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 f22_reg_aiopll_dss :  1;    //     23
    UINT32 f22_reg_aiopll_offset: 8;    //  31:24
    };
}BND_CTRL_M0_AIOPLLSS_M0_F22_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2018    aiopllss_m0_f22_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 f22_reg_aiopll_freq_update: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 f22_reg_aiopll_fout3_post_od: 3;    //  6:4
    UINT32 resvd01            :  5;    //  11: 7 reserved
    UINT32 f22_reg_aiopll_fout3_pre_od: 3;    //  14:12
    UINT32 resvd02            :  1;    //     15 reserved
    UINT32 f22_reg_aiopll_fout2_post_od: 3;    //  18:16
    UINT32 resvd03            :  1;    //     19 reserved
    UINT32 f22_reg_aiopll_fout2_pre_od: 3;    //  22:20
    UINT32 resvd04            :  1;    //     23 reserved
    UINT32 f22_reg_aiopll_sync_on: 1;    //   24
    UINT32 resvd05            :  2;    //  26:25 reserved
    UINT32 f22_reg_aiopll_wake_bypass: 1;    //  27
    UINT32 f22_reg_aiopll_offset_mode: 1;    //  28
    UINT32 resvd06            :  2;    //  30:29 reserved
    UINT32 f22_reg_aiopll_ddr_mode: 1;    //  31
    };
}BND_CTRL_M0_AIOPLLSS_M0_F22_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2020    pll_mon00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 mon_gfmrbgen_update_lockd: 1;    //  0
    UINT32 mon_pll_lockd      :  1;    //      1
    UINT32 mon_gfmrbgen_lockhold_lockd: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_M0_PLL_MON00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC67F_2024    pll_mon01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_gfm_lockd_en   :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_M0_PLL_MON01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_m0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_M0_AIOPLLSS_M0_O22_R00_O22A0_T    aiopllss_m0_o22_r00;    // 0xC67F_2000
    BND_CTRL_M0_AIOPLLSS_M0_O22_R01_O22A0_T    aiopllss_m0_o22_r01;    // 0xC67F_2004
    BND_CTRL_M0_AIOPLLSS_M0_O22_R02_O22A0_T    aiopllss_m0_o22_r02;    // 0xC67F_2008
    UINT32                             _rsvd_00[1];             // 0xC67F_200C
    BND_CTRL_M0_AIOPLLSS_M0_F22_R00_O22A0_T    aiopllss_m0_f22_r00;    // 0xC67F_2010
    BND_CTRL_M0_AIOPLLSS_M0_F22_R01_O22A0_T    aiopllss_m0_f22_r01;    // 0xC67F_2014
    BND_CTRL_M0_AIOPLLSS_M0_F22_R02_O22A0_T    aiopllss_m0_f22_r02;    // 0xC67F_2018
    UINT32                             _rsvd_01[1];             // 0xC67F_201C
    BND_CTRL_M0_PLL_MON00_O22A0_T           pll_mon00  ;             // 0xC67F_2020
    BND_CTRL_M0_PLL_MON01_O22A0_T           pll_mon01  ;             // 0xC67F_2024
}BND_CTRL_M0_REG_O22A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_M0_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

