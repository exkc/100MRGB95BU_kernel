#ifndef _SCRG_CTRL_EDPTX_REG_O26A0_H_
#define _SCRG_CTRL_EDPTX_REG_O26A0_H_

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
    0xC6BB_0000    crg_edptx000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_EDPTX_CRG_EDPTX000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_0004    crg_edptx001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_EDPTX_CRG_EDPTX001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_0008    crg_edptx002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_f_tcon_0__edptx_ipi0_clk_gate_en: 1,    //  0
    reg_adaprx_f_tcon_10__edptx_ipi0_clk_gate_en: 1,    //  1
    reg_adaprx_f_tcon_11__edptx_ipi1_clk_gate_en: 1,    //  2
    reg_adaprx_f_tcon_1__edptx_ipi1_clk_gate_en: 1,    //  3
    reg_adaprx_f_tcon_2__edptx_ipi0_clk_gate_en: 1,    //  4
    reg_adaprx_f_tcon_3__edptx_ipi1_clk_gate_en: 1,    //  5
    reg_adaprx_f_tcon_4__edptx_ipi0_clk_gate_en: 1,    //  6
    reg_adaprx_f_tcon_5__edptx_ipi1_clk_gate_en: 1,    //  7
    reg_adaprx_f_tcon_6__edptx_ipi0_clk_gate_en: 1,    //  8
    reg_adaprx_f_tcon_7__edptx_ipi1_clk_gate_en: 1,    //  9
    reg_adaprx_f_tcon_8__edptx_ipi0_clk_gate_en: 1,    //  10
    reg_adaprx_f_tcon_9__edptx_ipi1_clk_gate_en: 1,    //  11
    reg_adaptx_f_edptx_0__edptx_phy_clk_gate_en: 1,    //  12
    reg_edptx_apb_clk_gate_en :  1,    //     13
    reg_edptx_aux0_clk_gate_en:  1,    //     14
    reg_edptx_aux1_clk_gate_en:  1,    //     15
    reg_edptx_aux_clk_gate_en :  1,    //     16
    reg_edptx_ipi0_clk_gate_en:  1,    //     17
    reg_edptx_ipi1_clk_gate_en:  1,    //     18
    reg_edptx_ipi_clk_gate_en :  1,    //     19
    reg_edptx_link0_clk_gate_en: 1,    //     20
    reg_edptx_link1_clk_gate_en: 1,    //     21
    reg_edptx_link_clk_gate_en:  1,    //     22
    reg_edptx_patgen0_clk_gate_en: 1,    //   23
    reg_edptx_patgen1_clk_gate_en: 1,    //   24
    reg_edptx_phy0_clk_gate_en:  1,    //     25
    reg_edptx_phy1_clk_gate_en:  1,    //     26
    reg_edptx_phy_clk_gate_en :  1,    //     27
                              :  4;    //  31:28 reserved
}SCRG_CTRL_EDPTX_CRG_EDPTX002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_000C    crg_edptx003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_edptx_apb_n  :  1,    //      0
    reg_soft_rst_edptx_cmd0_n :  1,    //      1
    reg_soft_rst_edptx_cmd1_n :  1,    //      2
    reg_soft_rst_edptx_dout_n :  1,    //      3
    reg_soft_rst_edptx_link0_n:  1,    //      4
    reg_soft_rst_edptx_link1_n:  1,    //      5
    reg_soft_rst_edptx_patgen0_n: 1,    //     6
    reg_soft_rst_edptx_patgen1_n: 1,    //     7
    reg_soft_rst_f_edptx_0_edptx_dout_bnd_n: 1,    //  8
    reg_soft_rst_f_tcon_0_edptx_link0_bnd_n: 1,    //  9
    reg_soft_rst_f_tcon_10_edptx_link0_bnd_n: 1,    //  10
    reg_soft_rst_f_tcon_11_edptx_link1_bnd_n: 1,    //  11
    reg_soft_rst_f_tcon_1_edptx_link1_bnd_n: 1,    //  12
    reg_soft_rst_f_tcon_2_edptx_link0_bnd_n: 1,    //  13
    reg_soft_rst_f_tcon_3_edptx_link1_bnd_n: 1,    //  14
    reg_soft_rst_f_tcon_4_edptx_link0_bnd_n: 1,    //  15
    reg_soft_rst_f_tcon_5_edptx_link1_bnd_n: 1,    //  16
    reg_soft_rst_f_tcon_6_edptx_link0_bnd_n: 1,    //  17
    reg_soft_rst_f_tcon_7_edptx_link1_bnd_n: 1,    //  18
    reg_soft_rst_f_tcon_8_edptx_link0_bnd_n: 1,    //  19
    reg_soft_rst_f_tcon_9_edptx_link1_bnd_n: 1,    //  20
                              : 11;    //  31:21 reserved
}SCRG_CTRL_EDPTX_CRG_EDPTX003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_0010    crg_edptx004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edptx_ipi0_clk_sel    :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_edptx_ipi1_clk_sel    :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_edptx_ipi_clk_sel     :  3,    //  10: 8
                              :  1,    //     11 reserved
    reg_edptx_link0_clk_sel   :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_edptx_link1_clk_sel   :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_edptx_link_clk_sel    :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_edptx_patgen0_clk_sel :  3,    //  26:24
                              :  1,    //     27 reserved
    reg_edptx_patgen1_clk_sel :  3,    //  30:28
                              :  1;    //  31:31 reserved
}SCRG_CTRL_EDPTX_CRG_EDPTX004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_0014    crg_edptx005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edptx_phy0_clk_sel    :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_edptx_phy1_clk_sel    :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_edptx_phy_clk_sel     :  3,    //  10: 8
                              : 21;    //  31:11 reserved
}SCRG_CTRL_EDPTX_CRG_EDPTX005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_edptx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EDPTX_CRG_EDPTX000_O26A0_T    crg_edptx000;       // 0xC6BB_0000
    SCRG_CTRL_EDPTX_CRG_EDPTX001_O26A0_T    crg_edptx001;       // 0xC6BB_0004
    SCRG_CTRL_EDPTX_CRG_EDPTX002_O26A0_T    crg_edptx002;       // 0xC6BB_0008
    SCRG_CTRL_EDPTX_CRG_EDPTX003_O26A0_T    crg_edptx003;       // 0xC6BB_000C
    SCRG_CTRL_EDPTX_CRG_EDPTX004_O26A0_T    crg_edptx004;       // 0xC6BB_0010
    SCRG_CTRL_EDPTX_CRG_EDPTX005_O26A0_T    crg_edptx005;       // 0xC6BB_0014
}SCRG_CTRL_EDPTX_REG_O26A0_T;
/* 6 regs */

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

#define SCRG_CTRL_EDPTX_CRG_EDPTX000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_EDPTX_CRG_EDPTX001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_EDPTX_CRG_EDPTX002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_EDPTX_CRG_EDPTX003_O26A0_T_OFF            (BASEADDRESS+0x000C)
#define SCRG_CTRL_EDPTX_CRG_EDPTX004_O26A0_T_OFF            (BASEADDRESS+0x0010)
#define SCRG_CTRL_EDPTX_CRG_EDPTX005_O26A0_T_OFF            (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xC6BB_0000    crg_edptx000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_EDPTX_CRG_EDPTX000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_0004    crg_edptx001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_EDPTX_CRG_EDPTX001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_0008    crg_edptx002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_f_tcon_0__edptx_ipi0_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_f_tcon_10__edptx_ipi0_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_f_tcon_11__edptx_ipi1_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_f_tcon_1__edptx_ipi1_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_f_tcon_2__edptx_ipi0_clk_gate_en: 1;    //  4
    UINT32 reg_adaprx_f_tcon_3__edptx_ipi1_clk_gate_en: 1;    //  5
    UINT32 reg_adaprx_f_tcon_4__edptx_ipi0_clk_gate_en: 1;    //  6
    UINT32 reg_adaprx_f_tcon_5__edptx_ipi1_clk_gate_en: 1;    //  7
    UINT32 reg_adaprx_f_tcon_6__edptx_ipi0_clk_gate_en: 1;    //  8
    UINT32 reg_adaprx_f_tcon_7__edptx_ipi1_clk_gate_en: 1;    //  9
    UINT32 reg_adaprx_f_tcon_8__edptx_ipi0_clk_gate_en: 1;    //  10
    UINT32 reg_adaprx_f_tcon_9__edptx_ipi1_clk_gate_en: 1;    //  11
    UINT32 reg_adaptx_f_edptx_0__edptx_phy_clk_gate_en: 1;    //  12
    UINT32 reg_edptx_apb_clk_gate_en: 1;    //  13
    UINT32 reg_edptx_aux0_clk_gate_en: 1;    //  14
    UINT32 reg_edptx_aux1_clk_gate_en: 1;    //  15
    UINT32 reg_edptx_aux_clk_gate_en: 1;    //  16
    UINT32 reg_edptx_ipi0_clk_gate_en: 1;    //  17
    UINT32 reg_edptx_ipi1_clk_gate_en: 1;    //  18
    UINT32 reg_edptx_ipi_clk_gate_en: 1;    //  19
    UINT32 reg_edptx_link0_clk_gate_en: 1;    //  20
    UINT32 reg_edptx_link1_clk_gate_en: 1;    //  21
    UINT32 reg_edptx_link_clk_gate_en: 1;    //  22
    UINT32 reg_edptx_patgen0_clk_gate_en: 1;    //  23
    UINT32 reg_edptx_patgen1_clk_gate_en: 1;    //  24
    UINT32 reg_edptx_phy0_clk_gate_en: 1;    //  25
    UINT32 reg_edptx_phy1_clk_gate_en: 1;    //  26
    UINT32 reg_edptx_phy_clk_gate_en: 1;    //  27
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}SCRG_CTRL_EDPTX_CRG_EDPTX002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_000C    crg_edptx003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_edptx_apb_n: 1;    //  0
    UINT32 reg_soft_rst_edptx_cmd0_n: 1;    //  1
    UINT32 reg_soft_rst_edptx_cmd1_n: 1;    //  2
    UINT32 reg_soft_rst_edptx_dout_n: 1;    //  3
    UINT32 reg_soft_rst_edptx_link0_n: 1;    //  4
    UINT32 reg_soft_rst_edptx_link1_n: 1;    //  5
    UINT32 reg_soft_rst_edptx_patgen0_n: 1;    //  6
    UINT32 reg_soft_rst_edptx_patgen1_n: 1;    //  7
    UINT32 reg_soft_rst_f_edptx_0_edptx_dout_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_f_tcon_0_edptx_link0_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_f_tcon_10_edptx_link0_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_tcon_11_edptx_link1_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_tcon_1_edptx_link1_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_f_tcon_2_edptx_link0_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_f_tcon_3_edptx_link1_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_f_tcon_4_edptx_link0_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_f_tcon_5_edptx_link1_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_f_tcon_6_edptx_link0_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_f_tcon_7_edptx_link1_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_f_tcon_8_edptx_link0_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_f_tcon_9_edptx_link1_bnd_n: 1;    //  20
    UINT32 resvd00            : 11;    //  31:21 reserved
    };
}SCRG_CTRL_EDPTX_CRG_EDPTX003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_0010    crg_edptx004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edptx_ipi0_clk_sel: 3;    //  2:0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_edptx_ipi1_clk_sel: 3;    //  6:4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_edptx_ipi_clk_sel: 3;    //  10:8
    UINT32 resvd02            :  1;    //     11 reserved
    UINT32 reg_edptx_link0_clk_sel: 3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_edptx_link1_clk_sel: 3;    //  18:16
    UINT32 resvd04            :  1;    //     19 reserved
    UINT32 reg_edptx_link_clk_sel: 3;    //  22:20
    UINT32 resvd05            :  1;    //     23 reserved
    UINT32 reg_edptx_patgen0_clk_sel: 3;    //  26:24
    UINT32 resvd06            :  1;    //     27 reserved
    UINT32 reg_edptx_patgen1_clk_sel: 3;    //  30:28
    UINT32 resvd07            :  1;    //  31:31 reserved
    };
}SCRG_CTRL_EDPTX_CRG_EDPTX004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC6BB_0014    crg_edptx005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edptx_phy0_clk_sel: 3;    //  2:0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_edptx_phy1_clk_sel: 3;    //  6:4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_edptx_phy_clk_sel: 3;    //  10:8
    UINT32 resvd02            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_EDPTX_CRG_EDPTX005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_edptx Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_EDPTX_CRG_EDPTX000_O26A0_T    crg_edptx000;       // 0xC6BB_0000
    SCRG_CTRL_EDPTX_CRG_EDPTX001_O26A0_T    crg_edptx001;       // 0xC6BB_0004
    SCRG_CTRL_EDPTX_CRG_EDPTX002_O26A0_T    crg_edptx002;       // 0xC6BB_0008
    SCRG_CTRL_EDPTX_CRG_EDPTX003_O26A0_T    crg_edptx003;       // 0xC6BB_000C
    SCRG_CTRL_EDPTX_CRG_EDPTX004_O26A0_T    crg_edptx004;       // 0xC6BB_0010
    SCRG_CTRL_EDPTX_CRG_EDPTX005_O26A0_T    crg_edptx005;       // 0xC6BB_0014
}SCRG_CTRL_EDPTX_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_EDPTX_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

