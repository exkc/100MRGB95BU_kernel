#ifndef _SCRG_CTRL_MICOM_REG_H_
#define _SCRG_CTRL_MICOM_REG_H_

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
    0x5C_0000    crg_micom00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_MICOM_CRG_MICOM00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0004    crg_micom01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_MICOM_CRG_MICOM01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0008    crg_micom02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_sync_clk_gate_en  :  1,    //      0
    reg_micom_bus_clk_gate_en :  1,    //      1
    reg_micom_cm0p_clk_gate_en:  1,    //      2
    reg_micom_peri_clk_gate_en:  1,    //      3
    reg_micom_rtc_ir_clk_gate_en: 1,    //     4
                              : 27;    //   31:5 reserved
}SCRG_CTRL_MICOM_CRG_MICOM02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_000C    crg_micom03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_sync_n   :  1,    //      0
    reg_soft_rst_micom_bus_n  :  1,    //      1
    reg_soft_rst_micom_cm0p_n :  1,    //      2
    reg_soft_rst_micom_peri_n :  1,    //      3
    reg_soft_rst_micom_rtc_ir_n: 1,    //      4
    reg_soft_rst_p_cpu_3_axi_bnd_n: 1,    //   5
    reg_soft_rst_p_micom_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_p_micom_1_axi_bnd_n: 1,    //  7
    reg_soft_rst_p_micom_2_axi_bnd_n: 1,    //  8
    reg_soft_rst_x_aud_0_axi_n:  1,    //      9
    reg_soft_rst_x_cpu_3_axi_n:  1,    //     10
    reg_soft_rst_x_micom_0_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_micom_0_axi_n: 1,    //    12
    reg_soft_rst_x_micom_1_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_micom_1_axi_n: 1,    //    14
    reg_soft_rst_x_micom_2_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_micom_2_axi_n: 1,    //    16
                              : 15;    //  31:17 reserved
}SCRG_CTRL_MICOM_CRG_MICOM03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0010    crg_micom04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_sync_clk_sel      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_apb_ipw_clk_sel       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_micom_bus_clk_sel     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_micom_cm0p_clk_sel    :  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_MICOM_CRG_MICOM04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0014    crg_micom05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_bus_clk_skip_ctrl: 9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_MICOM_CRG_MICOM05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0018    crg_micom06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_cm0p_clk_skip_ctrl: 9,    //  8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_MICOM_CRG_MICOM06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_micom Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_MICOM_CRG_MICOM00_O22A0_T      crg_micom00;             // 0x5C_0000
    SCRG_CTRL_MICOM_CRG_MICOM01_O22A0_T      crg_micom01;             // 0x5C_0004
    SCRG_CTRL_MICOM_CRG_MICOM02_O22A0_T      crg_micom02;             // 0x5C_0008
    SCRG_CTRL_MICOM_CRG_MICOM03_O22A0_T      crg_micom03;             // 0x5C_000C
    SCRG_CTRL_MICOM_CRG_MICOM04_O22A0_T      crg_micom04;             // 0x5C_0010
    SCRG_CTRL_MICOM_CRG_MICOM05_O22A0_T      crg_micom05;             // 0x5C_0014
    SCRG_CTRL_MICOM_CRG_MICOM06_O22A0_T      crg_micom06;             // 0x5C_0018
}SCRG_CTRL_MICOM_REG_O22A0_T;
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

#define SCRG_CTRL_MICOM_CRG_MICOM00_O22A0_T_OFF                   (BASEADDRESS+0x0000)
#define SCRG_CTRL_MICOM_CRG_MICOM01_O22A0_T_OFF                   (BASEADDRESS+0x0004)
#define SCRG_CTRL_MICOM_CRG_MICOM02_O22A0_T_OFF                   (BASEADDRESS+0x0008)
#define SCRG_CTRL_MICOM_CRG_MICOM03_O22A0_T_OFF                   (BASEADDRESS+0x000C)
#define SCRG_CTRL_MICOM_CRG_MICOM04_O22A0_T_OFF                   (BASEADDRESS+0x0010)
#define SCRG_CTRL_MICOM_CRG_MICOM05_O22A0_T_OFF                   (BASEADDRESS+0x0014)
#define SCRG_CTRL_MICOM_CRG_MICOM06_O22A0_T_OFF                   (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x5C_0000    crg_micom00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_MICOM_CRG_MICOM00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0004    crg_micom01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_MICOM_CRG_MICOM01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0008    crg_micom02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_sync_clk_gate_en: 1;    //  0
    UINT32 reg_micom_bus_clk_gate_en: 1;    //  1
    UINT32 reg_micom_cm0p_clk_gate_en: 1;    //  2
    UINT32 reg_micom_peri_clk_gate_en: 1;    //  3
    UINT32 reg_micom_rtc_ir_clk_gate_en: 1;    //  4
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}SCRG_CTRL_MICOM_CRG_MICOM02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_000C    crg_micom03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_sync_n: 1;    //   0
    UINT32 reg_soft_rst_micom_bus_n: 1;    //  1
    UINT32 reg_soft_rst_micom_cm0p_n: 1;    //  2
    UINT32 reg_soft_rst_micom_peri_n: 1;    //  3
    UINT32 reg_soft_rst_micom_rtc_ir_n: 1;    //  4
    UINT32 reg_soft_rst_p_cpu_3_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_micom_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_micom_1_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_micom_2_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_x_aud_0_axi_n: 1;    //  9
    UINT32 reg_soft_rst_x_cpu_3_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_micom_0_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_micom_0_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_micom_1_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_micom_1_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_micom_2_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_micom_2_axi_n: 1;    //  16
    UINT32 resvd00            : 15;    //  31:17 reserved
    };
}SCRG_CTRL_MICOM_CRG_MICOM03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0010    crg_micom04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_sync_clk_sel: 1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_apb_ipw_clk_sel:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_micom_bus_clk_sel: 1;    //     8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_micom_cm0p_clk_sel: 1;    //   12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_MICOM_CRG_MICOM04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0014    crg_micom05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_bus_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_MICOM_CRG_MICOM05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5C_0018    crg_micom06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_cm0p_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_MICOM_CRG_MICOM06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_micom Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_MICOM_CRG_MICOM00_O22A0_T      crg_micom00;             // 0x5C_0000
    SCRG_CTRL_MICOM_CRG_MICOM01_O22A0_T      crg_micom01;             // 0x5C_0004
    SCRG_CTRL_MICOM_CRG_MICOM02_O22A0_T      crg_micom02;             // 0x5C_0008
    SCRG_CTRL_MICOM_CRG_MICOM03_O22A0_T      crg_micom03;             // 0x5C_000C
    SCRG_CTRL_MICOM_CRG_MICOM04_O22A0_T      crg_micom04;             // 0x5C_0010
    SCRG_CTRL_MICOM_CRG_MICOM05_O22A0_T      crg_micom05;             // 0x5C_0014
    SCRG_CTRL_MICOM_CRG_MICOM06_O22A0_T      crg_micom06;             // 0x5C_0018
}SCRG_CTRL_MICOM_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

