#ifndef _BND_CTRL_CVI_M23A0_REG_H_
#define _BND_CTRL_CVI_M23A0_REG_H_

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
    0xCC75_2000    cvi_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_emmc_tmclk_en         :  1,    //      0
                              :  7,    //   7: 1 reserved
    reg_emmc_tmclk_div        : 10,    //  17: 8
                              : 14;    //  31:18 reserved
}BND_CTRL_CVI_CVI_SYN_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_2004    cvi_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_drv_cvi_pdb        :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_CVI_CVI_SYN_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_2008    cvi_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt1_phy_wr_sel:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdmirx_prt2_phy_wr_sel:  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_CVI_CVI_SYN_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_200C    cvi_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earctx_apb_i2c_sel    :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_CVI_CVI_SYN_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_CVI_CVI_SYN_00_M23A0_T    cvi_syn_00 ;             // 0xCC75_2000
    BND_CTRL_CVI_CVI_SYN_01_M23A0_T    cvi_syn_01 ;             // 0xCC75_2004
    BND_CTRL_CVI_CVI_SYN_02_M23A0_T    cvi_syn_02 ;             // 0xCC75_2008
    BND_CTRL_CVI_CVI_SYN_03_M23A0_T    cvi_syn_03 ;             // 0xCC75_200C
}BND_CTRL_CVI_REG_M23A0_T;
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

#define BND_CTRL_CVI_CVI_SYN_00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define BND_CTRL_CVI_CVI_SYN_01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define BND_CTRL_CVI_CVI_SYN_02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define BND_CTRL_CVI_CVI_SYN_03_M23A0_T_OFF                 (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCC75_2000    cvi_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_emmc_tmclk_en  :  1;    //      0
    UINT32 resvd00            :  7;    //   7: 1 reserved
    UINT32 reg_emmc_tmclk_div : 10;    //  17: 8
    UINT32 resvd01            : 14;    //  31:18 reserved
    };
}BND_CTRL_CVI_CVI_SYN_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_2004    cvi_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_drv_cvi_pdb :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_CVI_CVI_SYN_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_2008    cvi_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt1_phy_wr_sel: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_hdmirx_prt2_phy_wr_sel: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_CVI_CVI_SYN_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC75_200C    cvi_syn_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earctx_apb_i2c_sel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_CVI_CVI_SYN_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_CVI_CVI_SYN_00_M23A0_T    cvi_syn_00 ;             // 0xCC75_2000
    BND_CTRL_CVI_CVI_SYN_01_M23A0_T    cvi_syn_01 ;             // 0xCC75_2004
    BND_CTRL_CVI_CVI_SYN_02_M23A0_T    cvi_syn_02 ;             // 0xCC75_2008
    BND_CTRL_CVI_CVI_SYN_03_M23A0_T    cvi_syn_03 ;             // 0xCC75_200C
}BND_CTRL_CVI_REG_M23A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

