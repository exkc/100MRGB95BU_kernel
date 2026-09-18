#ifndef _BND_CTRL_BMC_M23A0_REG_H_
#define _BND_CTRL_BMC_M23A0_REG_H_

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
    0xC615_2000    bnd_bmc_0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_inv_mclk1         :  1,    //      0
    reg_sel_inv_mclk0         :  1,    //      1
    reg_sel_inv_aclk_mux_mip_dig: 1,    //     2
                              : 29;    //   31:3 reserved
}BND_CTRL_BMC_BND_BMC_0_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_2004    bnd_bmc_1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f1fs_clk_sel          :  1,    //      0
    reg_f64fs_clk_sel         :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_BMC_BND_BMC_1_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_2008    bnd_bmc_2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_auad            :  1,    //      0
    reg_swrst_auda_f256fs_clk0:  1,    //      1
    reg_swrst_auda_f256fs_clk1:  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_BMC_BND_BMC_2_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_200C    bnd_bmc_3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_f200_sel              :  1,    //      0
    reg_f50_sel               :  1,    //      1
    reg_f27_18_sel            :  1,    //      2
                              :  1,    //      3 reserved
    reg_sc_ext_sel            :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}BND_CTRL_BMC_BND_BMC_3_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_2010    bnd_bmc_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adc_output_mux_sel    :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}BND_CTRL_BMC_BND_BMC_4_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_2014    bnd_bmc_5 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_md_drv_bmc_pdb     :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_BMC_BND_BMC_5_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_BMC_BND_BMC_0_M23A0_T     bnd_bmc_0  ;             // 0xC615_2000
    BND_CTRL_BMC_BND_BMC_1_M23A0_T     bnd_bmc_1  ;             // 0xC615_2004
    BND_CTRL_BMC_BND_BMC_2_M23A0_T     bnd_bmc_2  ;             // 0xC615_2008
    BND_CTRL_BMC_BND_BMC_3_M23A0_T     bnd_bmc_3  ;             // 0xC615_200C
    BND_CTRL_BMC_BND_BMC_4_M23A0_T     bnd_bmc_4  ;             // 0xC615_2010
    BND_CTRL_BMC_BND_BMC_5_M23A0_T     bnd_bmc_5 ;             // 0xC615_2014
}BND_CTRL_BMC_REG_M23A0_T;
/* 6 regs */

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

#define BND_CTRL_BMC_BND_BMC_0_M23A0_T_OFF                  (BASEADDRESS+0x0000)
#define BND_CTRL_BMC_BND_BMC_1_M23A0_T_OFF                  (BASEADDRESS+0x0004)
#define BND_CTRL_BMC_BND_BMC_2_M23A0_T_OFF                  (BASEADDRESS+0x0008)
#define BND_CTRL_BMC_BND_BMC_3_M23A0_T_OFF                  (BASEADDRESS+0x000C)
#define BND_CTRL_BMC_BND_BMC_4_M23A0_T_OFF                  (BASEADDRESS+0x0010)
#define BND_CTRL_BMC_BND_BMC_5_M23A0_T_OFF                  (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xC615_2000    bnd_bmc_0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel_inv_mclk1  :  1;    //      0
    UINT32 reg_sel_inv_mclk0  :  1;    //      1
    UINT32 reg_sel_inv_aclk_mux_mip_dig: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_BMC_BND_BMC_0_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_2004    bnd_bmc_1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_f1fs_clk_sel   :  1;    //      0
    UINT32 reg_f64fs_clk_sel  :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_BMC_BND_BMC_1_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_2008    bnd_bmc_2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_auad     :  1;    //      0
    UINT32 reg_swrst_auda_f256fs_clk0: 1;    //  1
    UINT32 reg_swrst_auda_f256fs_clk1: 1;    //  2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_BMC_BND_BMC_2_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_200C    bnd_bmc_3 ''
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
}BND_CTRL_BMC_BND_BMC_3_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_2010    bnd_bmc_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adc_output_mux_sel: 4;    //  3:0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_BMC_BND_BMC_4_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_2014    bnd_bmc_5 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_md_drv_bmc_pdb: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_BMC_BND_BMC_5_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_BMC_BND_BMC_0_M23A0_T     bnd_bmc_0  ;             // 0xC615_2000
    BND_CTRL_BMC_BND_BMC_1_M23A0_T     bnd_bmc_1  ;             // 0xC615_2004
    BND_CTRL_BMC_BND_BMC_2_M23A0_T     bnd_bmc_2  ;             // 0xC615_2008
    BND_CTRL_BMC_BND_BMC_3_M23A0_T     bnd_bmc_3  ;             // 0xC615_200C
    BND_CTRL_BMC_BND_BMC_4_M23A0_T     bnd_bmc_4  ;             // 0xC615_2010
    BND_CTRL_BMC_BND_BMC_5_M23A0_T     bnd_bmc_5 ;             // 0xC615_2014
}BND_CTRL_BMC_REG_M23A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

