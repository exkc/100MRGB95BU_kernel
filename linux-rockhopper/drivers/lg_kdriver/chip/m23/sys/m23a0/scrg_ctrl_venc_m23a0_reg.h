#ifndef _SCRG_CTRL_VENC_M23A0_REG_H_
#define _SCRG_CTRL_VENC_M23A0_REG_H_

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
    0xCEC8_0000    crg_venc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VENC_CRG_VENC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_0004    crg_venc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VENC_CRG_VENC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_0008    crg_venc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ve_apb_clk_gate_en    :  1,    //      0
    reg_ve_clk_gate_en        :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_VENC_CRG_VENC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_000C    crg_venc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_f_teipw_4_ve_apb_bnd_n: 1,    //  0
    reg_soft_rst_f_teipw_5_ve_apb_bnd_n: 1,    //  1
    reg_soft_rst_p_venc_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_ve_apb_n     :  1,    //      3
    reg_soft_rst_ve_n         :  1,    //      4
    reg_soft_rst_x_venc_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_venc_0_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_VENC_CRG_VENC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VENC_CRG_VENC00_M23A0_T    crg_venc00;            // 0xCEC8_0000
    SCRG_CTRL_VENC_CRG_VENC01_M23A0_T    crg_venc01;            // 0xCEC8_0004
    SCRG_CTRL_VENC_CRG_VENC02_M23A0_T    crg_venc02;            // 0xCEC8_0008
    SCRG_CTRL_VENC_CRG_VENC03_M23A0_T    crg_venc03;            // 0xCEC8_000C
}SCRG_CTRL_VENC_REG_M23A0_T;
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

#define SCRG_CTRL_VENC_CRG_VENC00_M23A0_T_OFF               (BASEADDRESS+0x0000)
#define SCRG_CTRL_VENC_CRG_VENC01_M23A0_T_OFF               (BASEADDRESS+0x0004)
#define SCRG_CTRL_VENC_CRG_VENC02_M23A0_T_OFF               (BASEADDRESS+0x0008)
#define SCRG_CTRL_VENC_CRG_VENC03_M23A0_T_OFF               (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCEC8_0000    crg_venc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VENC_CRG_VENC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_0004    crg_venc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VENC_CRG_VENC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_0008    crg_venc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ve_apb_clk_gate_en: 1;    //    0
    UINT32 reg_ve_clk_gate_en :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCEC8_000C    crg_venc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_f_teipw_4_ve_apb_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_f_teipw_5_ve_apb_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_venc_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_ve_apb_n: 1;    //     3
    UINT32 reg_soft_rst_ve_n  :  1;    //      4
    UINT32 reg_soft_rst_x_venc_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_venc_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VENC_CRG_VENC00_M23A0_T    crg_venc00;            // 0xCEC8_0000
    SCRG_CTRL_VENC_CRG_VENC01_M23A0_T    crg_venc01;            // 0xCEC8_0004
    SCRG_CTRL_VENC_CRG_VENC02_M23A0_T    crg_venc02;            // 0xCEC8_0008
    SCRG_CTRL_VENC_CRG_VENC03_M23A0_T    crg_venc03;            // 0xCEC8_000C
}SCRG_CTRL_VENC_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

