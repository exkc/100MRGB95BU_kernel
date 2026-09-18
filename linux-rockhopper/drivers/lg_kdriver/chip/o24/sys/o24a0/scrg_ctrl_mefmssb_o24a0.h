#ifndef _SCRG_CTRL_MEFMSSB_REG_O24A0_H_
#define _SCRG_CTRL_MEFMSSB_REG_O24A0_H_

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
    0xCC9A_0000    crg_sb_mefms0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9A_0004    crg_sb_mefms1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9A_0008    crg_sb_mefms2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_async_axi_884_clk_gate_en: 1,    //    0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9A_000C    crg_sb_mefms3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_async_axi_884_n: 1,    //     0
    reg_soft_rst_p_mefmssb_0_axi_bnd_n: 1,    //  1
    reg_soft_rst_p_rx_fms_0_conv_axi_bnd_n: 1,    //  2
    reg_soft_rst_p_rx_me0_0_conv_axi_bnd_n: 1,    //  3
    reg_soft_rst_p_rx_me0_1_conv_axi_bnd_n: 1,    //  4
    reg_soft_rst_p_rx_me1_0_conv_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_rx_mefmssb_0_axi_n: 1,    //  6
    reg_soft_rst_p_tx_fms_0_conv_axi_bnd_n: 1,    //  7
    reg_soft_rst_p_tx_me0_0_conv_axi_bnd_n: 1,    //  8
    reg_soft_rst_p_tx_me0_1_conv_axi_bnd_n: 1,    //  9
    reg_soft_rst_p_tx_me1_0_conv_axi_bnd_n: 1,    //  10
    reg_soft_rst_p_tx_mefmssb_0_axi_n: 1,    //  11
    reg_soft_rst_x_rx_fms_0_conv_axi_bnd_n: 1,    //  12
    reg_soft_rst_x_rx_me0_0_conv_axi_bnd_n: 1,    //  13
    reg_soft_rst_x_rx_me0_1_conv_axi_bnd_n: 1,    //  14
    reg_soft_rst_x_rx_me1_0_conv_axi_bnd_n: 1,    //  15
    reg_soft_rst_x_rx_mefmssb_0_axi_n: 1,    //  16
    reg_soft_rst_x_tx_fms_0_conv_axi_bnd_n: 1,    //  17
    reg_soft_rst_x_tx_me0_0_conv_axi_bnd_n: 1,    //  18
    reg_soft_rst_x_tx_me0_1_conv_axi_bnd_n: 1,    //  19
    reg_soft_rst_x_tx_me1_0_conv_axi_bnd_n: 1,    //  20
    reg_soft_rst_x_tx_mefmssb_0_axi_n: 1,    //  21
                              : 10;    //  31:22 reserved
}SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_mefmssb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS0_O24A0_T    crg_sb_mefms0;    // 0xCC9A_0000
    SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS1_O24A0_T    crg_sb_mefms1;    // 0xCC9A_0004
    SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS2_O24A0_T    crg_sb_mefms2;    // 0xCC9A_0008
    SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS3_O24A0_T    crg_sb_mefms3;    // 0xCC9A_000C
}SCRG_CTRL_MEFMSSB_REG_O24A0_T;
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

#define SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS0_O24A0_T_OFF         (BASEADDRESS+0x0000)
#define SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS1_O24A0_T_OFF         (BASEADDRESS+0x0004)
#define SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS2_O24A0_T_OFF         (BASEADDRESS+0x0008)
#define SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS3_O24A0_T_OFF         (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC9A_0000    crg_sb_mefms0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9A_0004    crg_sb_mefms1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9A_0008    crg_sb_mefms2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_async_axi_884_clk_gate_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9A_000C    crg_sb_mefms3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_async_axi_884_n: 1;    //  0
    UINT32 reg_soft_rst_p_mefmssb_0_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_rx_fms_0_conv_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_rx_me0_0_conv_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_rx_me0_1_conv_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_rx_me1_0_conv_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_rx_mefmssb_0_axi_n: 1;    //  6
    UINT32 reg_soft_rst_p_tx_fms_0_conv_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_tx_me0_0_conv_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_tx_me0_1_conv_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_p_tx_me1_0_conv_axi_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_p_tx_mefmssb_0_axi_n: 1;    //  11
    UINT32 reg_soft_rst_x_rx_fms_0_conv_axi_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_x_rx_me0_0_conv_axi_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_x_rx_me0_1_conv_axi_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_x_rx_me1_0_conv_axi_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_x_rx_mefmssb_0_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_tx_fms_0_conv_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_x_tx_me0_0_conv_axi_bnd_n: 1;    //  18
    UINT32 reg_soft_rst_x_tx_me0_1_conv_axi_bnd_n: 1;    //  19
    UINT32 reg_soft_rst_x_tx_me1_0_conv_axi_bnd_n: 1;    //  20
    UINT32 reg_soft_rst_x_tx_mefmssb_0_axi_n: 1;    //  21
    UINT32 resvd00            : 10;    //  31:22 reserved
    };
}SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_mefmssb Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS0_O24A0_T    crg_sb_mefms0;    // 0xCC9A_0000
    SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS1_O24A0_T    crg_sb_mefms1;    // 0xCC9A_0004
    SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS2_O24A0_T    crg_sb_mefms2;    // 0xCC9A_0008
    SCRG_CTRL_MEFMSSB_CRG_SB_MEFMS3_O24A0_T    crg_sb_mefms3;    // 0xCC9A_000C
}SCRG_CTRL_MEFMSSB_REG_O24A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_MEFMSSB_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

