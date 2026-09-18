#ifndef _MIP_DIG_CTRL_REG_O26A0_H_
#define _MIP_DIG_CTRL_REG_O26A0_H_

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
    0xC8A3_7000    bmc_syn_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_mclk0_inv_sel         :  1,    //      1
    reg_aclk_mux_mip_dig_inv_sel: 1,    //     2
                              : 29;    //   31:3 reserved
}MIP_DIG_CTRL_BMC_SYN_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_7004    bmc_syn_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f1fs_clk_sel          :  1,    //      0
    reg_f64fs_clk_sel         :  1,    //      1
                              : 30;    //   31:2 reserved
}MIP_DIG_CTRL_BMC_SYN_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_7008    bmc_syn_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_auad            :  1,    //      0
    reg_swrst_auda_f256fs_clk0:  1,    //      1
    reg_swrst_auda_f256fs_clk1:  1,    //      2
                              : 29;    //   31:3 reserved
}MIP_DIG_CTRL_BMC_SYN_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_700C    bmc_syn_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f200_sel              :  1,    //      0
    reg_f50_sel               :  1,    //      1
    reg_f27_18_sel            :  1,    //      2
                              :  1,    //      3 reserved
    reg_sc_ext_sel            :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}MIP_DIG_CTRL_BMC_SYN_3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_dig_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_DIG_CTRL_BMC_SYN_0_O26A0_T     bmc_syn_0  ;             // 0xC8A3_7000
    MIP_DIG_CTRL_BMC_SYN_1_O26A0_T     bmc_syn_1  ;             // 0xC8A3_7004
    MIP_DIG_CTRL_BMC_SYN_2_O26A0_T     bmc_syn_2  ;             // 0xC8A3_7008
    MIP_DIG_CTRL_BMC_SYN_3_O26A0_T     bmc_syn_3  ;             // 0xC8A3_700C
}MIP_DIG_CTRL_REG_O26A0_T;
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

#define MIP_DIG_CTRL_BMC_SYN_0_O26A0_T_OFF                  (BASEADDRESS+0x0000)
#define MIP_DIG_CTRL_BMC_SYN_1_O26A0_T_OFF                  (BASEADDRESS+0x0004)
#define MIP_DIG_CTRL_BMC_SYN_2_O26A0_T_OFF                  (BASEADDRESS+0x0008)
#define MIP_DIG_CTRL_BMC_SYN_3_O26A0_T_OFF                  (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC8A3_7000    bmc_syn_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_mclk0_inv_sel  :  1;    //      1
    UINT32 reg_aclk_mux_mip_dig_inv_sel: 1;    //  2
    UINT32 resvd01            : 29;    //   31:3 reserved
    };
}MIP_DIG_CTRL_BMC_SYN_0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_7004    bmc_syn_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f1fs_clk_sel   :  1;    //      0
    UINT32 reg_f64fs_clk_sel  :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MIP_DIG_CTRL_BMC_SYN_1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_7008    bmc_syn_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_auad     :  1;    //      0
    UINT32 reg_swrst_auda_f256fs_clk0: 1;    //  1
    UINT32 reg_swrst_auda_f256fs_clk1: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MIP_DIG_CTRL_BMC_SYN_2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_700C    bmc_syn_3 ''
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
}MIP_DIG_CTRL_BMC_SYN_3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_dig_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_DIG_CTRL_BMC_SYN_0_O26A0_T     bmc_syn_0  ;             // 0xC8A3_7000
    MIP_DIG_CTRL_BMC_SYN_1_O26A0_T     bmc_syn_1  ;             // 0xC8A3_7004
    MIP_DIG_CTRL_BMC_SYN_2_O26A0_T     bmc_syn_2  ;             // 0xC8A3_7008
    MIP_DIG_CTRL_BMC_SYN_3_O26A0_T     bmc_syn_3  ;             // 0xC8A3_700C
}MIP_DIG_CTRL_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MIP_DIG_CTRL_REG_O26A0_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/


