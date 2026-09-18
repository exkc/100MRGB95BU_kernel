#ifndef _SCRG_CTRL_FMS_REG_O26A0_H_
#define _SCRG_CTRL_FMS_REG_O26A0_H_

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
    0xCC31_0000    crg_fms000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_FMS_CRG_FMS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC31_0004    crg_fms001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_FMS_CRG_FMS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC31_0008    crg_fms002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaptx_f_fms_0__de_clk_gate_en: 1,    //  0
    reg_adaptx_x_fms_0__axi_fms_clk_gate_en: 1,    //  1
    reg_apb_fms_clk_gate_en   :  1,    //      2
    reg_axi_fms_clk_gate_en   :  1,    //      3
    reg_de_clk_gate_en        :  1,    //      4
    reg_fms_clk_gate_en       :  1,    //      5
                              : 26;    //   31:6 reserved
}SCRG_CTRL_FMS_CRG_FMS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC31_000C    crg_fms003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_fms_n    :  1,    //      0
    reg_soft_rst_axi_fms_n    :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_fms_0_de_bnd_n: 1,    //    3
    reg_soft_rst_fms_n        :  1,    //      4
    reg_soft_rst_p_fms_0_axi_bnd_n: 1,    //   5
    reg_soft_rst_x_fms_0_axi_n:  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_FMS_CRG_FMS003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC31_0010    crg_fms004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_fms_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_axi_fms_clk_sel       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_fms_clk_sel           :  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_FMS_CRG_FMS004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMS_CRG_FMS000_O26A0_T    crg_fms000;             // 0xCC31_0000
    SCRG_CTRL_FMS_CRG_FMS001_O26A0_T    crg_fms001;             // 0xCC31_0004
    SCRG_CTRL_FMS_CRG_FMS002_O26A0_T    crg_fms002;             // 0xCC31_0008
    SCRG_CTRL_FMS_CRG_FMS003_O26A0_T    crg_fms003;             // 0xCC31_000C
    SCRG_CTRL_FMS_CRG_FMS004_O26A0_T    crg_fms004;             // 0xCC31_0010
}SCRG_CTRL_FMS_REG_O26A0_T;
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

#define SCRG_CTRL_FMS_CRG_FMS000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_FMS_CRG_FMS001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_FMS_CRG_FMS002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_FMS_CRG_FMS003_O26A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_FMS_CRG_FMS004_O26A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC31_0000    crg_fms000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_FMS_CRG_FMS000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC31_0004    crg_fms001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_FMS_CRG_FMS001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC31_0008    crg_fms002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaptx_f_fms_0__de_clk_gate_en: 1;    //  0
    UINT32 reg_adaptx_x_fms_0__axi_fms_clk_gate_en: 1;    //  1
    UINT32 reg_apb_fms_clk_gate_en: 1;    //   2
    UINT32 reg_axi_fms_clk_gate_en: 1;    //   3
    UINT32 reg_de_clk_gate_en :  1;    //      4
    UINT32 reg_fms_clk_gate_en:  1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC31_000C    crg_fms003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_fms_n: 1;    //    0
    UINT32 reg_soft_rst_axi_fms_n: 1;    //    1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_fms_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_fms_n :  1;    //      4
    UINT32 reg_soft_rst_p_fms_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_fms_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC31_0010    crg_fms004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_fms_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_axi_fms_clk_sel:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_fms_clk_sel    :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_FMS_CRG_FMS004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fms Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMS_CRG_FMS000_O26A0_T    crg_fms000;             // 0xCC31_0000
    SCRG_CTRL_FMS_CRG_FMS001_O26A0_T    crg_fms001;             // 0xCC31_0004
    SCRG_CTRL_FMS_CRG_FMS002_O26A0_T    crg_fms002;             // 0xCC31_0008
    SCRG_CTRL_FMS_CRG_FMS003_O26A0_T    crg_fms003;             // 0xCC31_000C
    SCRG_CTRL_FMS_CRG_FMS004_O26A0_T    crg_fms004;             // 0xCC31_0010
}SCRG_CTRL_FMS_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_FMS_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

