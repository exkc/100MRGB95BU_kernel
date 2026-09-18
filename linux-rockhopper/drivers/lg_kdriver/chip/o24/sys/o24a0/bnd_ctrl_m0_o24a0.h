#ifndef _BND_CTRL_M0_REG_O24A0_H_
#define _BND_CTRL_M0_REG_O24A0_H_

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
    0xC4D3_2000    m0_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_cih            :  4,    //   3: 0
    reg_aiopll_fine_control   :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_aiopll_fine_div       :  1,    //      8
    reg_aiopll_fout_od        :  2,    //  10: 9
                              :  1,    //     11 reserved
    reg_aiopll_nsc            :  4,    //  15:12
    reg_aiopll_npc            :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_aiopll_m              :  6,    //  29:24
                              :  1,    //     30 reserved
    reg_gfm_lockd_en          :  1;    //     31
}BND_CTRL_M0_M0_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC4D3_2004    m0_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_mod_freq_max   :  9,    //   8: 0
                              :  3,    //  11: 9 reserved
    reg_aiopll_updn_max       :  7,    //  18:12
                              :  1,    //     19 reserved
    reg_aiopll_accuracy       :  2,    //  21:20
                              :  1,    //     22 reserved
    reg_aiopll_dss            :  1,    //     23
    reg_aiopll_offset         :  8;    //  31:24
}BND_CTRL_M0_M0_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC4D3_2008    m0_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_freq_update    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_aiopll_fout3_post_od  :  3,    //   6: 4
                              :  5,    //  11: 7 reserved
    reg_aiopll_fout3_pre_od   :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_aiopll_fout2_post_od  :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_aiopll_fout2_pre_od   :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_aiopll_sync_on        :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_aiopll_wake_bypass    :  1,    //     27
    reg_aiopll_offset_mode    :  1,    //     28
                              :  2,    //  30:29 reserved
    reg_aiopll_ddr_mode       :  1;    //     31
}BND_CTRL_M0_M0_SYN_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC4D3_200C    m0_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    mon_gfmrbgen_update_lockd :  1,    //      0
    mon_pll_lockd             :  1,    //      1
    mon_gfmrbgen_lockhold_lockd: 1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_M0_M0_SYN_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC4D3_2014    pll_mon ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_M0_PLL_MON_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_m0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_M0_M0_SYN_00_O24A0_T      m0_syn_00  ;             // 0xC4D3_2000
    BND_CTRL_M0_M0_SYN_01_O24A0_T      m0_syn_01  ;             // 0xC4D3_2004
    BND_CTRL_M0_M0_SYN_02_O24A0_T      m0_syn_02  ;             // 0xC4D3_2008
    BND_CTRL_M0_M0_SYN_03_O24A0_T      m0_syn_03  ;             // 0xC4D3_200C
    UINT32                             _rsvd_00[1];             // 0xC4D3_2010
    BND_CTRL_M0_PLL_MON_O24A0_T        pll_mon    ;             // 0xC4D3_2014
}BND_CTRL_M0_REG_O24A0_T;
/* 5 regs */

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

#define BND_CTRL_M0_M0_SYN_00_O24A0_T_OFF                   (BASEADDRESS+0x0000)
#define BND_CTRL_M0_M0_SYN_01_O24A0_T_OFF                   (BASEADDRESS+0x0004)
#define BND_CTRL_M0_M0_SYN_02_O24A0_T_OFF                   (BASEADDRESS+0x0008)
#define BND_CTRL_M0_M0_SYN_03_O24A0_T_OFF                   (BASEADDRESS+0x000C)
#define BND_CTRL_M0_PLL_MON_O24A0_T_OFF                     (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xC4D3_2000    m0_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aiopll_cih     :  4;    //   3: 0
    UINT32 reg_aiopll_fine_control: 3;    //  6:4
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_aiopll_fine_div:  1;    //      8
    UINT32 reg_aiopll_fout_od :  2;    //  10: 9
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 reg_aiopll_nsc     :  4;    //  15:12
    UINT32 reg_aiopll_npc     :  6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_aiopll_m       :  6;    //  29:24
    UINT32 resvd03            :  1;    //     30 reserved
    UINT32 reg_gfm_lockd_en   :  1;    //     31
    };
}BND_CTRL_M0_M0_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC4D3_2004    m0_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aiopll_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_aiopll_updn_max:  7;    //  18:12
    UINT32 resvd01            :  1;    //     19 reserved
    UINT32 reg_aiopll_accuracy:  2;    //  21:20
    UINT32 resvd02            :  1;    //     22 reserved
    UINT32 reg_aiopll_dss     :  1;    //     23
    UINT32 reg_aiopll_offset  :  8;    //  31:24
    };
}BND_CTRL_M0_M0_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC4D3_2008    m0_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aiopll_freq_update: 1;    //    0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_aiopll_fout3_post_od: 3;    //  6:4
    UINT32 resvd01            :  5;    //  11: 7 reserved
    UINT32 reg_aiopll_fout3_pre_od: 3;    //  14:12
    UINT32 resvd02            :  1;    //     15 reserved
    UINT32 reg_aiopll_fout2_post_od: 3;    //  18:16
    UINT32 resvd03            :  1;    //     19 reserved
    UINT32 reg_aiopll_fout2_pre_od: 3;    //  22:20
    UINT32 resvd04            :  1;    //     23 reserved
    UINT32 reg_aiopll_sync_on :  1;    //     24
    UINT32 resvd05            :  2;    //  26:25 reserved
    UINT32 reg_aiopll_wake_bypass: 1;    //   27
    UINT32 reg_aiopll_offset_mode: 1;    //   28
    UINT32 resvd06            :  2;    //  30:29 reserved
    UINT32 reg_aiopll_ddr_mode:  1;    //     31
    };
}BND_CTRL_M0_M0_SYN_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC4D3_200C    m0_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 mon_gfmrbgen_update_lockd: 1;    //  0
    UINT32 mon_pll_lockd      :  1;    //      1
    UINT32 mon_gfmrbgen_lockhold_lockd: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_M0_M0_SYN_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC4D3_2014    pll_mon ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_M0_PLL_MON_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_m0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_M0_M0_SYN_00_O24A0_T      m0_syn_00  ;             // 0xC4D3_2000
    BND_CTRL_M0_M0_SYN_01_O24A0_T      m0_syn_01  ;             // 0xC4D3_2004
    BND_CTRL_M0_M0_SYN_02_O24A0_T      m0_syn_02  ;             // 0xC4D3_2008
    BND_CTRL_M0_M0_SYN_03_O24A0_T      m0_syn_03  ;             // 0xC4D3_200C
    UINT32                             _rsvd_00[1];             // 0xC4D3_2010
    BND_CTRL_M0_PLL_MON_O24A0_T        pll_mon    ;             // 0xC4D3_2014
}BND_CTRL_M0_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_M0_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

