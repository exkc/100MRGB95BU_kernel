#ifndef _BND_CTRL_M0_REG_O26A0_H_
#define _BND_CTRL_M0_REG_O26A0_H_

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
    0xC493_2000    m0_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_cih            :  4,    //   3: 0
    reg_aiopll_fine_control   :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_aiopll_fine_div       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_aiopll_nsc            :  4,    //  15:12
    reg_aiopll_npc            :  6,    //  21:16
                              :  2,    //  23:22 reserved
    reg_aiopll_m              :  6,    //  29:24
                              :  1,    //     30 reserved
    reg_gfm_lockd_en          :  1;    //     31
}BND_CTRL_M0_M0_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2004    m0_syn_01 ''
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
}BND_CTRL_M0_M0_SYN_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2008    m0_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_freq_update    :  1,    //      0
                              : 23,    //  23: 1 reserved
    reg_aiopll_sync_on        :  1,    //     24
                              :  2,    //  26:25 reserved
    reg_aiopll_wake_bypass    :  1,    //     27
    reg_aiopll_offset_mode    :  1,    //     28
                              :  3;    //  31:29 reserved
}BND_CTRL_M0_M0_SYN_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_200C    m0_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    mon_gfmrbgen_update_lockd :  1,    //      0
    mon_pll_lockd             :  1,    //      1
    mon_gfmrbgen_lockhold_lockd: 1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_M0_M0_SYN_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2010    pll_mon ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pll_mon_en            :  1,    //      0
    reg_aiopll_vco_bypass     :  1,    //      1
    reg_aiopll_lbenl          :  1,    //      2
    reg_aiopll_fout3_od       :  7,    //   9: 3
    reg_aiopll_fout3_en       :  1,    //     10
    reg_aiopll_fout2_od       :  7,    //  17:11
    reg_aiopll_fout2_en       :  1,    //     18
    reg_aiopll_fout1_od       :  7,    //  25:19
    reg_aiopll_fout1_en       :  1,    //     26
    pl_div2_enb_ddrphy        :  1,    //     27
    pl_pdb_ddrphy             :  1,    //     28
    plmd_pdb_ddrphy           :  1,    //     29
                              :  2;    //  31:30 reserved
}BND_CTRL_M0_PLL_MON_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2100    m0_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_m0_ls                 :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_m0_ds                 :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_m0_sd                 :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_M0_M0_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2104    m0_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_m0_urf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_M0_M0_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_m0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_M0_M0_SYN_00_O26A0_T      m0_syn_00  ;             // 0xC493_2000
    BND_CTRL_M0_M0_SYN_01_O26A0_T      m0_syn_01  ;             // 0xC493_2004
    BND_CTRL_M0_M0_SYN_02_O26A0_T      m0_syn_02  ;             // 0xC493_2008
    BND_CTRL_M0_M0_SYN_03_O26A0_T      m0_syn_03  ;             // 0xC493_200C
    BND_CTRL_M0_PLL_MON_O26A0_T        pll_mon    ;             // 0xC493_2010
    UINT32                             _rsvd_00[59];            // 0xC493_2014 ~ 0xC493_20FC
    BND_CTRL_M0_M0_MEM0_O26A0_T        m0_mem0    ;             // 0xC493_2100
    BND_CTRL_M0_M0_MEM1_O26A0_T        m0_mem1    ;             // 0xC493_2104
}BND_CTRL_M0_REG_O26A0_T;
/* 7 regs */

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

#define BND_CTRL_M0_M0_SYN_00_O26A0_T_OFF                   (BASEADDRESS+0x0000)
#define BND_CTRL_M0_M0_SYN_01_O26A0_T_OFF                   (BASEADDRESS+0x0004)
#define BND_CTRL_M0_M0_SYN_02_O26A0_T_OFF                   (BASEADDRESS+0x0008)
#define BND_CTRL_M0_M0_SYN_03_O26A0_T_OFF                   (BASEADDRESS+0x000C)
#define BND_CTRL_M0_PLL_MON_O26A0_T_OFF                     (BASEADDRESS+0x0010)
#define BND_CTRL_M0_M0_MEM0_O26A0_T_OFF                     (BASEADDRESS+0x0100)
#define BND_CTRL_M0_M0_MEM1_O26A0_T_OFF                     (BASEADDRESS+0x0104)

/*-----------------------------------------------------------------------------------------
    0xC493_2000    m0_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aiopll_cih     :  4;    //   3: 0
    UINT32 reg_aiopll_fine_control: 3;    //  6:4
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 reg_aiopll_fine_div:  1;    //      8
    UINT32 resvd01            :  3;    //  11: 9 reserved
    UINT32 reg_aiopll_nsc     :  4;    //  15:12
    UINT32 reg_aiopll_npc     :  6;    //  21:16
    UINT32 resvd02            :  2;    //  23:22 reserved
    UINT32 reg_aiopll_m       :  6;    //  29:24
    UINT32 resvd03            :  1;    //     30 reserved
    UINT32 reg_gfm_lockd_en   :  1;    //     31
    };
}BND_CTRL_M0_M0_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2004    m0_syn_01 ''
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
}BND_CTRL_M0_M0_SYN_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2008    m0_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aiopll_freq_update: 1;    //    0
    UINT32 resvd00            : 23;    //  23: 1 reserved
    UINT32 reg_aiopll_sync_on :  1;    //     24
    UINT32 resvd01            :  2;    //  26:25 reserved
    UINT32 reg_aiopll_wake_bypass: 1;    //   27
    UINT32 reg_aiopll_offset_mode: 1;    //   28
    UINT32 resvd02            :  3;    //  31:29 reserved
    };
}BND_CTRL_M0_M0_SYN_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_200C    m0_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 mon_gfmrbgen_update_lockd: 1;    //  0
    UINT32 mon_pll_lockd      :  1;    //      1
    UINT32 mon_gfmrbgen_lockhold_lockd: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_M0_M0_SYN_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2010    pll_mon ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pll_mon_en     :  1;    //      0
    UINT32 reg_aiopll_vco_bypass: 1;    //     1
    UINT32 reg_aiopll_lbenl   :  1;    //      2
    UINT32 reg_aiopll_fout3_od:  7;    //   9: 3
    UINT32 reg_aiopll_fout3_en:  1;    //     10
    UINT32 reg_aiopll_fout2_od:  7;    //  17:11
    UINT32 reg_aiopll_fout2_en:  1;    //     18
    UINT32 reg_aiopll_fout1_od:  7;    //  25:19
    UINT32 reg_aiopll_fout1_en:  1;    //     26
    UINT32 pl_div2_enb_ddrphy :  1;    //     27
    UINT32 pl_pdb_ddrphy      :  1;    //     28
    UINT32 plmd_pdb_ddrphy    :  1;    //     29
    UINT32 resvd00            :  2;    //  31:30 reserved
    };
}BND_CTRL_M0_PLL_MON_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2100    m0_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_m0_ls          :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_m0_ds          :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_m0_sd          :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_M0_M0_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC493_2104    m0_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_m0_urf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_M0_M0_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_m0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_M0_M0_SYN_00_O26A0_T      m0_syn_00  ;             // 0xC493_2000
    BND_CTRL_M0_M0_SYN_01_O26A0_T      m0_syn_01  ;             // 0xC493_2004
    BND_CTRL_M0_M0_SYN_02_O26A0_T      m0_syn_02  ;             // 0xC493_2008
    BND_CTRL_M0_M0_SYN_03_O26A0_T      m0_syn_03  ;             // 0xC493_200C
    BND_CTRL_M0_PLL_MON_O26A0_T        pll_mon    ;             // 0xC493_2010
    UINT32                             _rsvd_00[59];            // 0xC493_2014 ~ 0xC493_20FC
    BND_CTRL_M0_M0_MEM0_O26A0_T        m0_mem0    ;             // 0xC493_2100
    BND_CTRL_M0_M0_MEM1_O26A0_T        m0_mem1    ;             // 0xC493_2104
}BND_CTRL_M0_REG_O26A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_M0_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

