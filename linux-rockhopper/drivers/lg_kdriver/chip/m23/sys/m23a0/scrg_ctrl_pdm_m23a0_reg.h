#ifndef _SCRG_CTRL_PDM_M23A0_REG_H_
#define _SCRG_CTRL_PDM_M23A0_REG_H_

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
    0xF317_0000    crg_pdm00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_PDM_CRG_PDM00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF317_0004    crg_pdm01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_PDM_CRG_PDM01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF317_0008    crg_pdm02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pdm_bus_clk_gate_en   :  1,    //      0
    reg_pdm_pdm_clk_gate_en   :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_PDM_CRG_PDM02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF317_000C    crg_pdm03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_aud_2_axi_bnd_n: 1,    //   0
    reg_soft_rst_p_micom_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_pdm_0_axi_bnd_n: 1,    //   2
    reg_soft_rst_pdm_bus_n    :  1,    //      3
    reg_soft_rst_pdm_pdm_n    :  1,    //      4
    reg_soft_rst_x_aud_2_axi_n:  1,    //      5
    reg_soft_rst_x_micom_0_axi_n: 1,    //     6
    reg_soft_rst_x_pdm_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_x_pdm_0_axi_n:  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_PDM_CRG_PDM03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF317_0010    crg_pdm04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pdm_pdm_clk_sel       :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_PDM_CRG_PDM04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_pdm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_PDM_CRG_PDM00_M23A0_T    crg_pdm00  ;             // 0xF317_0000
    SCRG_CTRL_PDM_CRG_PDM01_M23A0_T    crg_pdm01  ;             // 0xF317_0004
    SCRG_CTRL_PDM_CRG_PDM02_M23A0_T    crg_pdm02  ;             // 0xF317_0008
    SCRG_CTRL_PDM_CRG_PDM03_M23A0_T    crg_pdm03  ;             // 0xF317_000C
    SCRG_CTRL_PDM_CRG_PDM04_M23A0_T    crg_pdm04  ;             // 0xF317_0010
}SCRG_CTRL_PDM_REG_M23A0_T;
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

#define SCRG_CTRL_PDM_CRG_PDM00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_PDM_CRG_PDM01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_PDM_CRG_PDM02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_PDM_CRG_PDM03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_PDM_CRG_PDM04_M23A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xF317_0000    crg_pdm00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_PDM_CRG_PDM00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF317_0004    crg_pdm01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_PDM_CRG_PDM01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF317_0008    crg_pdm02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pdm_bus_clk_gate_en: 1;    //   0
    UINT32 reg_pdm_pdm_clk_gate_en: 1;    //   1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_PDM_CRG_PDM02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF317_000C    crg_pdm03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_aud_2_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_p_micom_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_pdm_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_pdm_bus_n: 1;    //    3
    UINT32 reg_soft_rst_pdm_pdm_n: 1;    //    4
    UINT32 reg_soft_rst_x_aud_2_axi_n: 1;    //  5
    UINT32 reg_soft_rst_x_micom_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_x_pdm_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_pdm_0_axi_n: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_PDM_CRG_PDM03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF317_0010    crg_pdm04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pdm_pdm_clk_sel:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_PDM_CRG_PDM04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_pdm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_PDM_CRG_PDM00_M23A0_T    crg_pdm00  ;             // 0xF317_0000
    SCRG_CTRL_PDM_CRG_PDM01_M23A0_T    crg_pdm01  ;             // 0xF317_0004
    SCRG_CTRL_PDM_CRG_PDM02_M23A0_T    crg_pdm02  ;             // 0xF317_0008
    SCRG_CTRL_PDM_CRG_PDM03_M23A0_T    crg_pdm03  ;             // 0xF317_000C
    SCRG_CTRL_PDM_CRG_PDM04_M23A0_T    crg_pdm04  ;             // 0xF317_0010
}SCRG_CTRL_PDM_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

