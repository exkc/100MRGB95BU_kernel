#ifndef _SCRG_CTRL_CVBSB_M23A0_REG_H_
#define _SCRG_CTRL_CVBSB_M23A0_REG_H_

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
    0xCC5E_0000    crg_sb_cvd00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CVBSB_CRG_SB_CVD00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5E_0004    crg_sb_cvd01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CVBSB_CRG_SB_CVD01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5E_0008    crg_sb_cvd02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sb_axi_cvd_400_clk_gate_en: 1,    //   0
    reg_sb_axi_cvd_480_clk_gate_en: 1,    //   1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_CVBSB_CRG_SB_CVD02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5E_000C    crg_sb_cvd03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_sb_axi_cvd_400_bnd_n: 1,    //  0
    reg_soft_rst_sb_axi_cvd_400_n: 1,    //    1
    reg_soft_rst_sb_axi_cvd_480_n: 1,    //    2
                              : 29;    //   31:3 reserved
}SCRG_CTRL_CVBSB_CRG_SB_CVD03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cvbsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CVBSB_CRG_SB_CVD00_M23A0_T    crg_sb_cvd00;       // 0xCC5E_0000
    SCRG_CTRL_CVBSB_CRG_SB_CVD01_M23A0_T    crg_sb_cvd01;       // 0xCC5E_0004
    SCRG_CTRL_CVBSB_CRG_SB_CVD02_M23A0_T    crg_sb_cvd02;       // 0xCC5E_0008
    SCRG_CTRL_CVBSB_CRG_SB_CVD03_M23A0_T    crg_sb_cvd03;       // 0xCC5E_000C
}SCRG_CTRL_CVBSB_REG_M23A0_T;
/* 4 regs */

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

#define SCRG_CTRL_CVBSB_CRG_SB_CVD00_M23A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_CVBSB_CRG_SB_CVD01_M23A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_CVBSB_CRG_SB_CVD02_M23A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_CVBSB_CRG_SB_CVD03_M23A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC5E_0000    crg_sb_cvd00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CVBSB_CRG_SB_CVD00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5E_0004    crg_sb_cvd01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CVBSB_CRG_SB_CVD01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5E_0008    crg_sb_cvd02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sb_axi_cvd_400_clk_gate_en: 1;    //  0
    UINT32 reg_sb_axi_cvd_480_clk_gate_en: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_CVBSB_CRG_SB_CVD02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC5E_000C    crg_sb_cvd03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_sb_axi_cvd_400_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_sb_axi_cvd_400_n: 1;    //  1
    UINT32 reg_soft_rst_sb_axi_cvd_480_n: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}SCRG_CTRL_CVBSB_CRG_SB_CVD03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cvbsb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CVBSB_CRG_SB_CVD00_M23A0_T    crg_sb_cvd00;       // 0xCC5E_0000
    SCRG_CTRL_CVBSB_CRG_SB_CVD01_M23A0_T    crg_sb_cvd01;       // 0xCC5E_0004
    SCRG_CTRL_CVBSB_CRG_SB_CVD02_M23A0_T    crg_sb_cvd02;       // 0xCC5E_0008
    SCRG_CTRL_CVBSB_CRG_SB_CVD03_M23A0_T    crg_sb_cvd03;       // 0xCC5E_000C
}SCRG_CTRL_CVBSB_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

