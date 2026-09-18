#ifndef _BND_CTRL_LNX0_REG_O24A0_H_
#define _BND_CTRL_LNX0_REG_O24A0_H_

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
    0xCC9E_2000    bnd_lnx0_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_sel_inv_mclk0         :  1,    //      1
    reg_sel_inv_aclk_mux_mip_dig: 1,    //     2
                              : 29;    //   31:3 reserved
}BND_CTRL_LNX0_BND_LNX0_0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2004    bnd_lnx0_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f1fs_clk_sel          :  1,    //      0
    reg_f64fs_clk_sel         :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_LNX0_BND_LNX0_1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2008    bnd_lnx0_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_auad            :  1,    //      0
    reg_swrst_auda_f256fs_clk0:  1,    //      1
    reg_swrst_auda_f256fs_clk1:  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_LNX0_BND_LNX0_2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_200C    bnd_lnx0_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f200_sel              :  1,    //      0
    reg_f50_sel               :  1,    //      1
    reg_f27_18_sel            :  1,    //      2
                              :  1,    //      3 reserved
    reg_sc_ext_sel            :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}BND_CTRL_LNX0_BND_LNX0_3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2010    bnd_lnx0_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adc_output_mux_sel    :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_LNX0_BND_LNX0_4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2014    bnd_lnx0_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_md_drv_admd_pdb    :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_LNX0_BND_LNX0_5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2018    bnd_lnx0_6 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_drv_usb_wifi_pdb   :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_tx_lo_drv_usb_wifi_pdb:  1,    //      4
    reg_tx_lo_drv_usb_wifi_ck_div: 1,    //    5
                              : 26;    //   31:6 reserved
}BND_CTRL_LNX0_BND_LNX0_6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_lnx0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_LNX0_BND_LNX0_0_O24A0_T    bnd_lnx0_0;             // 0xCC9E_2000
    BND_CTRL_LNX0_BND_LNX0_1_O24A0_T    bnd_lnx0_1;             // 0xCC9E_2004
    BND_CTRL_LNX0_BND_LNX0_2_O24A0_T    bnd_lnx0_2;             // 0xCC9E_2008
    BND_CTRL_LNX0_BND_LNX0_3_O24A0_T    bnd_lnx0_3;             // 0xCC9E_200C
    BND_CTRL_LNX0_BND_LNX0_4_O24A0_T    bnd_lnx0_4;             // 0xCC9E_2010
    BND_CTRL_LNX0_BND_LNX0_5_O24A0_T    bnd_lnx0_5;             // 0xCC9E_2014
    BND_CTRL_LNX0_BND_LNX0_6_O24A0_T    bnd_lnx0_6;             // 0xCC9E_2018
}BND_CTRL_LNX0_REG_O24A0_T;
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

#define BND_CTRL_LNX0_BND_LNX0_0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define BND_CTRL_LNX0_BND_LNX0_1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define BND_CTRL_LNX0_BND_LNX0_2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define BND_CTRL_LNX0_BND_LNX0_3_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define BND_CTRL_LNX0_BND_LNX0_4_O24A0_T_OFF                (BASEADDRESS+0x0010)
#define BND_CTRL_LNX0_BND_LNX0_5_O24A0_T_OFF                (BASEADDRESS+0x0014)
#define BND_CTRL_LNX0_BND_LNX0_6_O24A0_T_OFF                (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xCC9E_2000    bnd_lnx0_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_sel_inv_mclk0  :  1;    //      1
    UINT32 reg_sel_inv_aclk_mux_mip_dig: 1;    //  2
    UINT32 resvd01            : 29;    //   31:3 reserved
    };
}BND_CTRL_LNX0_BND_LNX0_0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2004    bnd_lnx0_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f1fs_clk_sel   :  1;    //      0
    UINT32 reg_f64fs_clk_sel  :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_LNX0_BND_LNX0_1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2008    bnd_lnx0_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_auad     :  1;    //      0
    UINT32 reg_swrst_auda_f256fs_clk0: 1;    //  1
    UINT32 reg_swrst_auda_f256fs_clk1: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_LNX0_BND_LNX0_2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_200C    bnd_lnx0_3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f200_sel       :  1;    //      0
    UINT32 reg_f50_sel        :  1;    //      1
    UINT32 reg_f27_18_sel     :  1;    //      2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_sc_ext_sel     :  3;    //   6: 4
    UINT32 resvd01            : 25;    //   31:7 reserved
    };
}BND_CTRL_LNX0_BND_LNX0_3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2010    bnd_lnx0_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adc_output_mux_sel: 4;    //  3:0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_LNX0_BND_LNX0_4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2014    bnd_lnx0_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_md_drv_admd_pdb: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_LNX0_BND_LNX0_5_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_2018    bnd_lnx0_6 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_drv_usb_wifi_pdb: 1;    //   0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_tx_lo_drv_usb_wifi_pdb: 1;    //  4
    UINT32 reg_tx_lo_drv_usb_wifi_ck_div: 1;    //  5
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}BND_CTRL_LNX0_BND_LNX0_6_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_lnx0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_LNX0_BND_LNX0_0_O24A0_T    bnd_lnx0_0;             // 0xCC9E_2000
    BND_CTRL_LNX0_BND_LNX0_1_O24A0_T    bnd_lnx0_1;             // 0xCC9E_2004
    BND_CTRL_LNX0_BND_LNX0_2_O24A0_T    bnd_lnx0_2;             // 0xCC9E_2008
    BND_CTRL_LNX0_BND_LNX0_3_O24A0_T    bnd_lnx0_3;             // 0xCC9E_200C
    BND_CTRL_LNX0_BND_LNX0_4_O24A0_T    bnd_lnx0_4;             // 0xCC9E_2010
    BND_CTRL_LNX0_BND_LNX0_5_O24A0_T    bnd_lnx0_5;             // 0xCC9E_2014
    BND_CTRL_LNX0_BND_LNX0_6_O24A0_T    bnd_lnx0_6;             // 0xCC9E_2018
}BND_CTRL_LNX0_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_LNX0_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

