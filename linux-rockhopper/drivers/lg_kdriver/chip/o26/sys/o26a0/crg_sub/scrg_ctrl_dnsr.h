#ifndef _SCRG_CTRL_DNSR_REG_O26A0_T
#define _SCRG_CTRL_DNSR_REG_O26A0_T

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
    0xCC49_0000    crg_dnsr000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DNSR_CRG_DNSR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC49_0004    crg_dnsr001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DNSR_CRG_DNSR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC49_0008    crg_dnsr002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_h_sre_0__sr_clk_gate_en: 1,    //  0
    reg_adaptx_h_dnsr_0__sr_clk_gate_en: 1,    //  1
    reg_adaptx_x_dnsr_0__axi_sr_clk_gate_en: 1,    //  2
    reg_dnsr_apb_sr_clk_gate_en: 1,    //     3
    reg_dnsr_axi_sr_clk_gate_en: 1,    //     4
    reg_dnsr_mem_sr_clk_gate_en: 1,    //     5
    reg_dnsr_sr_clk_gate_en  :  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_DNSR_CRG_DNSR002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC49_000C    crg_dnsr003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_sr_n     :  1,    //      0
    reg_soft_rst_axi_sr_n     :  1,    //      1
    reg_soft_rst_gmau_sr_n    :  1,    //      2
    reg_soft_rst_h_dnsr_0_sr_bnd_n: 1,    //  3
    reg_soft_rst_h_sre_0_sr_bnd_n: 1,    //    4
    reg_soft_rst_p_dnsr_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_sr_n         :  1,    //      6
    reg_soft_rst_x_dnsr_0_axi_n: 1,    //     7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_DNSR_CRG_DNSR003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC49_0010    crg_dnsr004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dnsr_apb_sr_clk_sel  :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_dnsr_axi_sr_clk_sel  :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_dnsr_mem_sr_clk_sel  :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_dnsr_sr_clk_sel      :  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_DNSR_CRG_DNSR004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNSR_CRG_DNSR000_O26A0_T    crg_dnsr000;         // 0xCC49_0000
    SCRG_CTRL_DNSR_CRG_DNSR001_O26A0_T    crg_dnsr001;         // 0xCC49_0004
    SCRG_CTRL_DNSR_CRG_DNSR002_O26A0_T    crg_dnsr002;         // 0xCC49_0008
    SCRG_CTRL_DNSR_CRG_DNSR003_O26A0_T    crg_dnsr003;         // 0xCC49_000C
    SCRG_CTRL_DNSR_CRG_DNSR004_O26A0_T    crg_dnsr004;         // 0xCC49_0010
}SCRG_CTRL_DNSR_REG_O26A0_T;
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

#define SCRG_CTRL_DNSR_CRG_DNSR000_O26A0_T_OFF             (BASEADDRESS+0x0000)
#define SCRG_CTRL_DNSR_CRG_DNSR001_O26A0_T_OFF             (BASEADDRESS+0x0004)
#define SCRG_CTRL_DNSR_CRG_DNSR002_O26A0_T_OFF             (BASEADDRESS+0x0008)
#define SCRG_CTRL_DNSR_CRG_DNSR003_O26A0_T_OFF             (BASEADDRESS+0x000C)
#define SCRG_CTRL_DNSR_CRG_DNSR004_O26A0_T_OFF             (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC49_0000    crg_dnsr000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DNSR_CRG_DNSR000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC49_0004    crg_dnsr001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DNSR_CRG_DNSR001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC49_0008    crg_dnsr002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_h_sre_0__sr_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_h_dnsr_0__sr_clk_gate_en: 1;    //  1
    UINT32 reg_adaptx_x_dnsr_0__axi_sr_clk_gate_en: 1;    //  2
    UINT32 reg_dnsr_apb_sr_clk_gate_en: 1;    //  3
    UINT32 reg_dnsr_axi_sr_clk_gate_en: 1;    //  4
    UINT32 reg_dnsr_mem_sr_clk_gate_en: 1;    //  5
    UINT32 reg_dnsr_sr_clk_gate_en: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC49_000C    crg_dnsr003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_sr_n: 1;    //     0
    UINT32 reg_soft_rst_axi_sr_n: 1;    //     1
    UINT32 reg_soft_rst_gmau_sr_n: 1;    //    2
    UINT32 reg_soft_rst_h_dnsr_0_sr_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_sre_0_sr_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_dnsr_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_sr_n  :  1;    //      6
    UINT32 reg_soft_rst_x_dnsr_0_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC49_0010    crg_dnsr004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dnsr_apb_sr_clk_sel: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_dnsr_axi_sr_clk_sel: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_dnsr_mem_sr_clk_sel: 1;    //  8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_dnsr_sr_clk_sel: 1;    //     12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNSR_CRG_DNSR000_O26A0_T       crg_dnsr000;            // 0xCC49_0000
    SCRG_CTRL_DNSR_CRG_DNSR001_O26A0_T       crg_dnsr001;            // 0xCC49_0004
    SCRG_CTRL_DNSR_CRG_DNSR002_O26A0_T       crg_dnsr002;            // 0xCC49_0008
    SCRG_CTRL_DNSR_CRG_DNSR003_O26A0_T       crg_dnsr003;            // 0xCC49_000C
    SCRG_CTRL_DNSR_CRG_DNSR004_O26A0_T       crg_dnsr004;            // 0xCC49_0010
}SCRG_CTRL_DNSR_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.4.9  KJH by LGSiCRDV V3.1C*/
