#ifndef _BND_CTRL_BMC_REG_O26A0_H_
#define _BND_CTRL_BMC_REG_O26A0_H_

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
    0xC8A3_2010    bmc_syn_4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_clk_inv_sel      :  1,    //      0
    reg_tadc_clk_inv_sel      :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_BMC_BMC_SYN_4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_2100    dbb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_dbb_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_dbb_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_BMC_DBB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_2104    dbb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_BMC_DBB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_2108    dbb_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_BMC_DBB_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_210C    dbb_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dbb_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_BMC_DBB_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_2110    admd ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_admd_pll_clk_gate_en  :  1,    //      0
    reg_admd_pll_clk_sel      :  1,    //      1
    reg_adc_output_mux_sel    :  4,    //   5: 2
                              : 26;    //   31:6 reserved
}BND_CTRL_BMC_ADMD_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[4];             // 0xC8A3_2000 ~ 0xC8A3_200C
    BND_CTRL_BMC_BMC_SYN_4_O26A0_T     bmc_syn_4  ;             // 0xC8A3_2010
    UINT32                             _rsvd_01[59];            // 0xC8A3_2014 ~ 0xC8A3_20FC
    BND_CTRL_BMC_DBB_MEM0_O26A0_T      dbb_mem0   ;             // 0xC8A3_2100
    BND_CTRL_BMC_DBB_MEM1_O26A0_T      dbb_mem1   ;             // 0xC8A3_2104
    BND_CTRL_BMC_DBB_MEM3_O26A0_T      dbb_mem3   ;             // 0xC8A3_2108
    BND_CTRL_BMC_DBB_MEM4_O26A0_T      dbb_mem4   ;             // 0xC8A3_210C
    BND_CTRL_BMC_ADMD_O26A0_T          admd       ;             // 0xC8A3_2110
}BND_CTRL_BMC_REG_O26A0_T;
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

#define BND_CTRL_BMC_BMC_SYN_4_O26A0_T_OFF                  (BASEADDRESS+0x0010)
#define BND_CTRL_BMC_DBB_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_BMC_DBB_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_BMC_DBB_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_BMC_DBB_MEM4_O26A0_T_OFF                   (BASEADDRESS+0x010C)
#define BND_CTRL_BMC_ADMD_O26A0_T_OFF                       (BASEADDRESS+0x0110)

/*-----------------------------------------------------------------------------------------
    0xC8A3_2010    bmc_syn_4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_clk_inv_sel: 1;    //      0
    UINT32 reg_tadc_clk_inv_sel: 1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_BMC_BMC_SYN_4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_2100    dbb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dbb_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_dbb_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_dbb_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_BMC_DBB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_2104    dbb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dbb_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_BMC_DBB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_2108    dbb_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dbb_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_BMC_DBB_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_210C    dbb_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dbb_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_BMC_DBB_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_2110    admd ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_admd_pll_clk_gate_en: 1;    //  0
    UINT32 reg_admd_pll_clk_sel: 1;    //      1
    UINT32 reg_adc_output_mux_sel: 4;    //  5:2
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}BND_CTRL_BMC_ADMD_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[4];             // 0xC8A3_2000 ~ 0xC8A3_200C
    BND_CTRL_BMC_BMC_SYN_4_O26A0_T     bmc_syn_4  ;             // 0xC8A3_2010
    UINT32                             _rsvd_01[59];            // 0xC8A3_2014 ~ 0xC8A3_20FC
    BND_CTRL_BMC_DBB_MEM0_O26A0_T      dbb_mem0   ;             // 0xC8A3_2100
    BND_CTRL_BMC_DBB_MEM1_O26A0_T      dbb_mem1   ;             // 0xC8A3_2104
    BND_CTRL_BMC_DBB_MEM3_O26A0_T      dbb_mem3   ;             // 0xC8A3_2108
    BND_CTRL_BMC_DBB_MEM4_O26A0_T      dbb_mem4   ;             // 0xC8A3_210C
    BND_CTRL_BMC_ADMD_O26A0_T          admd       ;             // 0xC8A3_2110
}BND_CTRL_BMC_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_BMC_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

