#ifndef _SCRG_CTRL_DNSR_REG_H_
#define _SCRG_CTRL_DNSR_REG_H_

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
    0x35_0000    crg_dnsr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DNSR_CRG_DNSR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0004    crg_dnsr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DNSR_CRG_DNSR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0008    crg_dnsr02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_sr_clk_gate_en    :  1,    //      0
    reg_axi_sr_clk_gate_en    :  1,    //      1
    reg_mem_sr_clk_gate_en    :  1,    //      2
    reg_sr_clk_gate_en        :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_DNSR_CRG_DNSR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_000C    crg_dnsr03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_sr_n     :  1,    //      0
    reg_soft_rst_axi_sr_n     :  1,    //      1
    reg_soft_rst_gmau_sr_n    :  1,    //      2
    reg_soft_rst_h_dnsr_0_sr_bnd_n: 1,    //   3
    reg_soft_rst_h_sre_1_sr_bnd_n: 1,    //    4
    reg_soft_rst_p_dnsr_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_sr_n         :  1,    //      6
    reg_soft_rst_x_dnsr_0_axi_bnd_n: 1,    //  7
    reg_soft_rst_x_dnsr_0_axi_n: 1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNSR_CRG_DNSR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0010    crg_dnsr04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_sr_clk_sel        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_axi_sr_clk_sel        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_mem_sr_clk_sel        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_sr_clk_sel            :  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_DNSR_CRG_DNSR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0014    crg_dnsr05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_sr_clk_skip_ctrl  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNSR_CRG_DNSR05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0018    crg_dnsr06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi_sr_clk_skip_ctrl  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNSR_CRG_DNSR06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_001C    crg_dnsr07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mem_sr_clk_skip_ctrl  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNSR_CRG_DNSR07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0020    crg_dnsr08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sr_clk_skip_ctrl      :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNSR_CRG_DNSR08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNSR_CRG_DNSR00_O22A0_T        crg_dnsr00 ;             // 0x35_0000
    SCRG_CTRL_DNSR_CRG_DNSR01_O22A0_T        crg_dnsr01 ;             // 0x35_0004
    SCRG_CTRL_DNSR_CRG_DNSR02_O22A0_T        crg_dnsr02 ;             // 0x35_0008
    SCRG_CTRL_DNSR_CRG_DNSR03_O22A0_T        crg_dnsr03 ;             // 0x35_000C
    SCRG_CTRL_DNSR_CRG_DNSR04_O22A0_T        crg_dnsr04 ;             // 0x35_0010
    SCRG_CTRL_DNSR_CRG_DNSR05_O22A0_T        crg_dnsr05 ;             // 0x35_0014
    SCRG_CTRL_DNSR_CRG_DNSR06_O22A0_T        crg_dnsr06 ;             // 0x35_0018
    SCRG_CTRL_DNSR_CRG_DNSR07_O22A0_T        crg_dnsr07 ;             // 0x35_001C
    SCRG_CTRL_DNSR_CRG_DNSR08_O22A0_T        crg_dnsr08 ;             // 0x35_0020
}SCRG_CTRL_DNSR_REG_O22A0_T;
/* 9 regs */

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

#define SCRG_CTRL_DNSR_CRG_DNSR00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define SCRG_CTRL_DNSR_CRG_DNSR01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define SCRG_CTRL_DNSR_CRG_DNSR02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define SCRG_CTRL_DNSR_CRG_DNSR03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define SCRG_CTRL_DNSR_CRG_DNSR04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define SCRG_CTRL_DNSR_CRG_DNSR05_O22A0_T_OFF                     (BASEADDRESS+0x0014)
#define SCRG_CTRL_DNSR_CRG_DNSR06_O22A0_T_OFF                     (BASEADDRESS+0x0018)
#define SCRG_CTRL_DNSR_CRG_DNSR07_O22A0_T_OFF                     (BASEADDRESS+0x001C)
#define SCRG_CTRL_DNSR_CRG_DNSR08_O22A0_T_OFF                     (BASEADDRESS+0x0020)

/*-----------------------------------------------------------------------------------------
    0x35_0000    crg_dnsr00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DNSR_CRG_DNSR00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0004    crg_dnsr01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DNSR_CRG_DNSR01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0008    crg_dnsr02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_sr_clk_gate_en: 1;    //    0
    UINT32 reg_axi_sr_clk_gate_en: 1;    //    1
    UINT32 reg_mem_sr_clk_gate_en: 1;    //    2
    UINT32 reg_sr_clk_gate_en :  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_000C    crg_dnsr03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_sr_n: 1;    //     0
    UINT32 reg_soft_rst_axi_sr_n: 1;    //     1
    UINT32 reg_soft_rst_gmau_sr_n: 1;    //    2
    UINT32 reg_soft_rst_h_dnsr_0_sr_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_sre_1_sr_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_dnsr_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_sr_n  :  1;    //      6
    UINT32 reg_soft_rst_x_dnsr_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_dnsr_0_axi_n: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0010    crg_dnsr04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_sr_clk_sel :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_axi_sr_clk_sel :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_mem_sr_clk_sel :  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_sr_clk_sel     :  1;    //     12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0014    crg_dnsr05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_sr_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0018    crg_dnsr06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi_sr_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_001C    crg_dnsr07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mem_sr_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x35_0020    crg_dnsr08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sr_clk_skip_ctrl: 9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNSR_CRG_DNSR08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_dnsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNSR_CRG_DNSR00_O22A0_T        crg_dnsr00 ;             // 0x35_0000
    SCRG_CTRL_DNSR_CRG_DNSR01_O22A0_T        crg_dnsr01 ;             // 0x35_0004
    SCRG_CTRL_DNSR_CRG_DNSR02_O22A0_T        crg_dnsr02 ;             // 0x35_0008
    SCRG_CTRL_DNSR_CRG_DNSR03_O22A0_T        crg_dnsr03 ;             // 0x35_000C
    SCRG_CTRL_DNSR_CRG_DNSR04_O22A0_T        crg_dnsr04 ;             // 0x35_0010
    SCRG_CTRL_DNSR_CRG_DNSR05_O22A0_T        crg_dnsr05 ;             // 0x35_0014
    SCRG_CTRL_DNSR_CRG_DNSR06_O22A0_T        crg_dnsr06 ;             // 0x35_0018
    SCRG_CTRL_DNSR_CRG_DNSR07_O22A0_T        crg_dnsr07 ;             // 0x35_001C
    SCRG_CTRL_DNSR_CRG_DNSR08_O22A0_T        crg_dnsr08 ;             // 0x35_0020
}SCRG_CTRL_DNSR_REG_O22A0_T;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

