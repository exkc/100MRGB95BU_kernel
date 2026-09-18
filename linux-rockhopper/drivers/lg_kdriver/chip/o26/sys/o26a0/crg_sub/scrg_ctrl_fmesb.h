#ifndef _SCRG_CTRL_FMESB_REG_O26A0_H_
#define _SCRG_CTRL_FMESB_REG_O26A0_H_

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
    0xCCD0_0000    crg_fmesb000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_FMESB_CRG_FMESB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD0_0004    crg_fmesb001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_FMESB_CRG_FMESB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD0_0008    crg_fmesb002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_axi_884_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_FMESB_CRG_FMESB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD0_000C    crg_fmesb003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_async_axi_884_n: 1,    //     0
    reg_soft_rst_p_fmesb_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_rx_me0_0_conv_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_rx_me0_1_conv_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_rx_me1_0_conv_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_tx_me0_0_conv_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_tx_me0_1_conv_axi_bnd_n: 1,    //  6
    reg_soft_rst_p_tx_me1_0_conv_axi_bnd_n: 1,    //  7
    reg_soft_rst_x_rx_me0_0_conv_axi_bnd_n: 1,    //  8
    reg_soft_rst_x_rx_me0_1_conv_axi_bnd_n: 1,    //  9
    reg_soft_rst_x_rx_me1_0_conv_axi_bnd_n: 1,    //  10
    reg_soft_rst_x_tx_me0_0_conv_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_tx_me0_1_conv_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_tx_me1_0_conv_axi_bnd_n: 1,    //  13
                              : 18;    //  31:14 reserved
}SCRG_CTRL_FMESB_CRG_FMESB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fmesb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMESB_CRG_FMESB000_O26A0_T    crg_fmesb000;       // 0xCCD0_0000
    SCRG_CTRL_FMESB_CRG_FMESB001_O26A0_T    crg_fmesb001;       // 0xCCD0_0004
    SCRG_CTRL_FMESB_CRG_FMESB002_O26A0_T    crg_fmesb002;       // 0xCCD0_0008
    SCRG_CTRL_FMESB_CRG_FMESB003_O26A0_T    crg_fmesb003;       // 0xCCD0_000C
}SCRG_CTRL_FMESB_REG_O26A0_T;
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

#define SCRG_CTRL_FMESB_CRG_FMESB000_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define SCRG_CTRL_FMESB_CRG_FMESB001_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define SCRG_CTRL_FMESB_CRG_FMESB002_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define SCRG_CTRL_FMESB_CRG_FMESB003_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCCD0_0000    crg_fmesb000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_FMESB_CRG_FMESB000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD0_0004    crg_fmesb001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_FMESB_CRG_FMESB001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD0_0008    crg_fmesb002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_axi_884_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_FMESB_CRG_FMESB002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCD0_000C    crg_fmesb003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_async_axi_884_n: 1;    //  0
    UINT32 reg_soft_rst_p_fmesb_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_rx_me0_0_conv_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_rx_me0_1_conv_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_rx_me1_0_conv_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_tx_me0_0_conv_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_tx_me0_1_conv_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_tx_me1_0_conv_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_rx_me0_0_conv_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_x_rx_me0_1_conv_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_rx_me1_0_conv_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_x_tx_me0_0_conv_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_tx_me0_1_conv_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_tx_me1_0_conv_axi_bnd_n: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}SCRG_CTRL_FMESB_CRG_FMESB003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_fmesb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_FMESB_CRG_FMESB000_O26A0_T    crg_fmesb000;       // 0xCCD0_0000
    SCRG_CTRL_FMESB_CRG_FMESB001_O26A0_T    crg_fmesb001;       // 0xCCD0_0004
    SCRG_CTRL_FMESB_CRG_FMESB002_O26A0_T    crg_fmesb002;       // 0xCCD0_0008
    SCRG_CTRL_FMESB_CRG_FMESB003_O26A0_T    crg_fmesb003;       // 0xCCD0_000C
}SCRG_CTRL_FMESB_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_FMESB_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

