#ifndef _BND_CTRL_WOC_REG_O26A0_H_
#define _BND_CTRL_WOC_REG_O26A0_H_

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
    0xCA3A_6000    woc_syn_00 ''
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
}BND_CTRL_WOC_WOC_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6004    woc_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_i2c_edid_gating       :  5,    //   4: 0
                              :  3,    //   7: 5 reserved
    reg_i2c_link_gating       :  5,    //  12: 8
                              : 19;    //  31:13 reserved
}BND_CTRL_WOC_WOC_SYN_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6100    micom_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_ls              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_micom_ds              :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_micom_sd              :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_WOC_MICOM_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6104    micom_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_urf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_WOC_MICOM_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6108    micom_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_rom_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_WOC_MICOM_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_610C    micom_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_sra_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_WOC_MICOM_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6110    ephy_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ephy_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ephy_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_ephy_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_WOC_EPHY_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6114    ephy_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ephy_rf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_WOC_EPHY_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6118    edid_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_edid_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_edid_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_WOC_EDID_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_611C    edid_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_urf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_WOC_EDID_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6120    edid_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_rf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_WOC_EDID_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6124    mem6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_main_uart_sel2        :  4,    //   3: 0
    reg_main_uart_sel1        :  4,    //   7: 4
    reg_main_uart_sel0        :  4,    //  11: 8
    reg_main_jtag_sel3        :  4,    //  15:12
    reg_main_jtag_sel2        :  4,    //  19:16
    reg_main_jtag_sel1        :  4,    //  23:20
    reg_main_jtag_sel0        :  4,    //  27:24
                              :  4;    //  31:28 reserved
}BND_CTRL_WOC_MEM6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_WOC_WOC_SYN_00_O26A0_T    woc_syn_00 ;             // 0xCA3A_6000
    BND_CTRL_WOC_WOC_SYN_01_O26A0_T    woc_syn_01 ;             // 0xCA3A_6004
    UINT32                             _rsvd_00[62];            // 0xCA3A_6008 ~ 0xCA3A_60FC
    BND_CTRL_WOC_MICOM_MEM0_O26A0_T    micom_mem0 ;             // 0xCA3A_6100
    BND_CTRL_WOC_MICOM_MEM1_O26A0_T    micom_mem1 ;             // 0xCA3A_6104
    BND_CTRL_WOC_MICOM_MEM2_O26A0_T    micom_mem2 ;             // 0xCA3A_6108
    BND_CTRL_WOC_MICOM_MEM3_O26A0_T    micom_mem3 ;             // 0xCA3A_610C
    BND_CTRL_WOC_EPHY_MEM0_O26A0_T     ephy_mem0  ;             // 0xCA3A_6110
    BND_CTRL_WOC_EPHY_MEM1_O26A0_T     ephy_mem1  ;             // 0xCA3A_6114
    BND_CTRL_WOC_EDID_MEM0_O26A0_T     edid_mem0  ;             // 0xCA3A_6118
    BND_CTRL_WOC_EDID_MEM1_O26A0_T     edid_mem1  ;             // 0xCA3A_611C
    BND_CTRL_WOC_EDID_MEM2_O26A0_T     edid_mem2  ;             // 0xCA3A_6120
    BND_CTRL_WOC_MEM6_O26A0_T          mem6       ;             // 0xCA3A_6124
}BND_CTRL_WOC_REG_O26A0_T;
/* 12 regs */

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

#define BND_CTRL_WOC_WOC_SYN_00_O26A0_T_OFF                 (BASEADDRESS+0x0000)
#define BND_CTRL_WOC_WOC_SYN_01_O26A0_T_OFF                 (BASEADDRESS+0x0004)
#define BND_CTRL_WOC_MICOM_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x0100)
#define BND_CTRL_WOC_MICOM_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0104)
#define BND_CTRL_WOC_MICOM_MEM2_O26A0_T_OFF                 (BASEADDRESS+0x0108)
#define BND_CTRL_WOC_MICOM_MEM3_O26A0_T_OFF                 (BASEADDRESS+0x010C)
#define BND_CTRL_WOC_EPHY_MEM0_O26A0_T_OFF                  (BASEADDRESS+0x0110)
#define BND_CTRL_WOC_EPHY_MEM1_O26A0_T_OFF                  (BASEADDRESS+0x0114)
#define BND_CTRL_WOC_EDID_MEM0_O26A0_T_OFF                  (BASEADDRESS+0x0118)
#define BND_CTRL_WOC_EDID_MEM1_O26A0_T_OFF                  (BASEADDRESS+0x011C)
#define BND_CTRL_WOC_EDID_MEM2_O26A0_T_OFF                  (BASEADDRESS+0x0120)
#define BND_CTRL_WOC_MEM6_O26A0_T_OFF                       (BASEADDRESS+0x0124)

/*-----------------------------------------------------------------------------------------
    0xCA3A_6000    woc_syn_00 ''
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
}BND_CTRL_WOC_WOC_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6004    woc_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_i2c_edid_gating:  5;    //   4: 0
    UINT32 resvd00            :  3;    //   7: 5 reserved
    UINT32 reg_i2c_link_gating:  5;    //  12: 8
    UINT32 resvd01            : 19;    //  31:13 reserved
    };
}BND_CTRL_WOC_WOC_SYN_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6100    micom_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_ls       :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_micom_ds       :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_micom_sd       :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_WOC_MICOM_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6104    micom_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_WOC_MICOM_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6108    micom_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_rom_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_WOC_MICOM_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_610C    micom_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_WOC_MICOM_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6110    ephy_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ephy_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_ephy_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_ephy_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_WOC_EPHY_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6114    ephy_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ephy_rf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_WOC_EPHY_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6118    edid_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_edid_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_edid_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_WOC_EDID_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_611C    edid_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_WOC_EDID_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6120    edid_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_rf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_WOC_EDID_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_6124    mem6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_main_uart_sel2 :  4;    //   3: 0
    UINT32 reg_main_uart_sel1 :  4;    //   7: 4
    UINT32 reg_main_uart_sel0 :  4;    //  11: 8
    UINT32 reg_main_jtag_sel3 :  4;    //  15:12
    UINT32 reg_main_jtag_sel2 :  4;    //  19:16
    UINT32 reg_main_jtag_sel1 :  4;    //  23:20
    UINT32 reg_main_jtag_sel0 :  4;    //  27:24
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_WOC_MEM6_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_WOC_WOC_SYN_00_O26A0_T    woc_syn_00 ;             // 0xCA3A_6000
    BND_CTRL_WOC_WOC_SYN_01_O26A0_T    woc_syn_01 ;             // 0xCA3A_6004
    UINT32                             _rsvd_00[62];            // 0xCA3A_6008 ~ 0xCA3A_60FC
    BND_CTRL_WOC_MICOM_MEM0_O26A0_T    micom_mem0 ;             // 0xCA3A_6100
    BND_CTRL_WOC_MICOM_MEM1_O26A0_T    micom_mem1 ;             // 0xCA3A_6104
    BND_CTRL_WOC_MICOM_MEM2_O26A0_T    micom_mem2 ;             // 0xCA3A_6108
    BND_CTRL_WOC_MICOM_MEM3_O26A0_T    micom_mem3 ;             // 0xCA3A_610C
    BND_CTRL_WOC_EPHY_MEM0_O26A0_T     ephy_mem0  ;             // 0xCA3A_6110
    BND_CTRL_WOC_EPHY_MEM1_O26A0_T     ephy_mem1  ;             // 0xCA3A_6114
    BND_CTRL_WOC_EDID_MEM0_O26A0_T     edid_mem0  ;             // 0xCA3A_6118
    BND_CTRL_WOC_EDID_MEM1_O26A0_T     edid_mem1  ;             // 0xCA3A_611C
    BND_CTRL_WOC_EDID_MEM2_O26A0_T     edid_mem2  ;             // 0xCA3A_6120
    BND_CTRL_WOC_MEM6_O26A0_T          mem6       ;             // 0xCA3A_6124
}BND_CTRL_WOC_REG_O26A0_T;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_WOC_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

