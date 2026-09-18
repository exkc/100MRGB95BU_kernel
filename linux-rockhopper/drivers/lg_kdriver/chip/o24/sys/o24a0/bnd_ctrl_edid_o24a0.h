#ifndef _BND_CTRL_EDID_REG_O24A0_H_
#define _BND_CTRL_EDID_REG_O24A0_H_

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
    0xC886_2000    edid_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hpd_out_prt1_edid     :  1,    //      0
    reg_hpd_out_prt2_edid     :  1,    //      1
    reg_hpd_out_prt3_edid     :  1,    //      2
    reg_hpd_out_prt4_edid     :  1,    //      3
    reg_hpd_out_prt1          :  1,    //      4
    reg_hpd_out_prt2          :  1,    //      5
    reg_hpd_out_prt3          :  1,    //      6
    reg_hpd_out_prt4          :  1,    //      7
    reg_hpd_out_prt1_polarity_ctrl: 1,    //   8
    reg_hpd_out_prt2_polarity_ctrl: 1,    //   9
    reg_hpd_out_prt3_polarity_ctrl: 1,    //  10
    reg_hpd_out_prt4_polarity_ctrl: 1,    //  11
    reg_hpd_sel               :  2,    //  13:12
                              : 18;    //  31:14 reserved
}BND_CTRL_EDID_EDID_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2004    edid_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i2c_edid_gating       :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_i2c_link_gating       :  5,    //  12: 8
                              : 19;    //  31:13 reserved
}BND_CTRL_EDID_EDID_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2008    edid_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tx_lo_drv_intr_pdm_pdb:  1,    //      0
    reg_tx_lo_drv_intr_pdm_ck_div: 1,    //    1
                              :  2,    //   3: 2 reserved
    reg_tx_lo_drv_intr_wol_pdb:  1,    //      4
    reg_tx_lo_drv_intr_wol_ck_div: 1,    //    5
                              : 26;    //   31:6 reserved
}BND_CTRL_EDID_EDID_SYN_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2010    edid_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ephy_shutdown         :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EDID_SYN_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2014    edid_syn_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_txp_clkdrv_bot_pdb    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txp_clkdrv_bot_icon   :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_txp_clkdrv_top_pdb    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_txp_clkdrv_top_icon   :  2,    //  13:12
                              : 18;    //  31:14 reserved
}BND_CTRL_EDID_EDID_SYN_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2018    edid_syn_05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auto_clk_gate_en      :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EDID_SYN_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_201C    edid_syn_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_md_drv_pdb_ephy    :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_EDID_EDID_SYN_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EDID_EDID_SYN_00_O24A0_T    edid_syn_00;           // 0xC886_2000
    BND_CTRL_EDID_EDID_SYN_01_O24A0_T    edid_syn_01;           // 0xC886_2004
    BND_CTRL_EDID_EDID_SYN_02_O24A0_T    edid_syn_02;           // 0xC886_2008
    UINT32                             _rsvd_00[1];             // 0xC886_200C
    BND_CTRL_EDID_EDID_SYN_03_O24A0_T    edid_syn_03;           // 0xC886_2010
    BND_CTRL_EDID_EDID_SYN_04_O24A0_T    edid_syn_04;           // 0xC886_2014
    BND_CTRL_EDID_EDID_SYN_05_O24A0_T    edid_syn_05;           // 0xC886_2018
    BND_CTRL_EDID_EDID_SYN_06_O24A0_T    edid_syn_06;           // 0xC886_201C
}BND_CTRL_EDID_REG_O24A0_T;
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

#define BND_CTRL_EDID_EDID_SYN_00_O24A0_T_OFF               (BASEADDRESS+0x0000)
#define BND_CTRL_EDID_EDID_SYN_01_O24A0_T_OFF               (BASEADDRESS+0x0004)
#define BND_CTRL_EDID_EDID_SYN_02_O24A0_T_OFF               (BASEADDRESS+0x0008)
#define BND_CTRL_EDID_EDID_SYN_03_O24A0_T_OFF               (BASEADDRESS+0x0010)
#define BND_CTRL_EDID_EDID_SYN_04_O24A0_T_OFF               (BASEADDRESS+0x0014)
#define BND_CTRL_EDID_EDID_SYN_05_O24A0_T_OFF               (BASEADDRESS+0x0018)
#define BND_CTRL_EDID_EDID_SYN_06_O24A0_T_OFF               (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0xC886_2000    edid_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hpd_out_prt1_edid: 1;    //     0
    UINT32 reg_hpd_out_prt2_edid: 1;    //     1
    UINT32 reg_hpd_out_prt3_edid: 1;    //     2
    UINT32 reg_hpd_out_prt4_edid: 1;    //     3
    UINT32 reg_hpd_out_prt1   :  1;    //      4
    UINT32 reg_hpd_out_prt2   :  1;    //      5
    UINT32 reg_hpd_out_prt3   :  1;    //      6
    UINT32 reg_hpd_out_prt4   :  1;    //      7
    UINT32 reg_hpd_out_prt1_polarity_ctrl: 1;    //  8
    UINT32 reg_hpd_out_prt2_polarity_ctrl: 1;    //  9
    UINT32 reg_hpd_out_prt3_polarity_ctrl: 1;    //  10
    UINT32 reg_hpd_out_prt4_polarity_ctrl: 1;    //  11
    UINT32 reg_hpd_sel        :  2;    //  13:12
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}BND_CTRL_EDID_EDID_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2004    edid_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_i2c_edid_gating:  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_i2c_link_gating:  5;    //  12: 8
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}BND_CTRL_EDID_EDID_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2008    edid_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tx_lo_drv_intr_pdm_pdb: 1;    //  0
    UINT32 reg_tx_lo_drv_intr_pdm_ck_div: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 reg_tx_lo_drv_intr_wol_pdb: 1;    //  4
    UINT32 reg_tx_lo_drv_intr_wol_ck_div: 1;    //  5
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}BND_CTRL_EDID_EDID_SYN_02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2010    edid_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ephy_shutdown  :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_EDID_EDID_SYN_03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2014    edid_syn_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_txp_clkdrv_bot_pdb: 1;    //    0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txp_clkdrv_bot_icon: 2;    //  5:4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_txp_clkdrv_top_pdb: 1;    //    8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_txp_clkdrv_top_icon: 2;    //  13:12
    UINT32 resvd03            : 18;    //  31:14 reserved
    };
}BND_CTRL_EDID_EDID_SYN_04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_2018    edid_syn_05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auto_clk_gate_en: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_EDID_EDID_SYN_05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC886_201C    edid_syn_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_md_drv_pdb_ephy: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_EDID_EDID_SYN_06_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_edid Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_EDID_EDID_SYN_00_O24A0_T    edid_syn_00;           // 0xC886_2000
    BND_CTRL_EDID_EDID_SYN_01_O24A0_T    edid_syn_01;           // 0xC886_2004
    BND_CTRL_EDID_EDID_SYN_02_O24A0_T    edid_syn_02;           // 0xC886_2008
    UINT32                             _rsvd_00[1];             // 0xC886_200C
    BND_CTRL_EDID_EDID_SYN_03_O24A0_T    edid_syn_03;           // 0xC886_2010
    BND_CTRL_EDID_EDID_SYN_04_O24A0_T    edid_syn_04;           // 0xC886_2014
    BND_CTRL_EDID_EDID_SYN_05_O24A0_T    edid_syn_05;           // 0xC886_2018
    BND_CTRL_EDID_EDID_SYN_06_O24A0_T    edid_syn_06;           // 0xC886_201C
}BND_CTRL_EDID_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_EDID_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

