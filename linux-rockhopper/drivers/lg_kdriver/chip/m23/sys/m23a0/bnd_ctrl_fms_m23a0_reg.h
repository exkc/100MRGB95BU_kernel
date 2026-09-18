#ifndef _BND_CTRL_FMS_M23A0_REG_H_
#define _BND_CTRL_FMS_M23A0_REG_H_

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
    0xCC99_2000    fms_bnd_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_hdmirx_prt3 :  1,    //      0
    reg_swrst_fly_hdmirx_prt4 :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_FMS_FMS_BND_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_2004    fms_bnd_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_tp          :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_FMS_FMS_BND_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_2008    fms_bnd_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt3_phy_wr_sel:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdmirx_prt4_phy_wr_sel:  1,    //      4
                              : 27;    //   31:5 reserved
}BND_CTRL_FMS_FMS_BND_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_FMS_FMS_BND_00_M23A0_T    fms_bnd_00 ;             // 0xCC99_2000
    BND_CTRL_FMS_FMS_BND_01_M23A0_T    fms_bnd_01 ;             // 0xCC99_2004
    BND_CTRL_FMS_FMS_BND_02_M23A0_T    fms_bnd_02 ;             // 0xCC99_2008
}BND_CTRL_FMS_REG_M23A0_T;
/* 3 regs */

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

#define BND_CTRL_FMS_FMS_BND_00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define BND_CTRL_FMS_FMS_BND_01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define BND_CTRL_FMS_FMS_BND_02_M23A0_T_OFF                 (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xCC99_2000    fms_bnd_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_hdmirx_prt3: 1;    //  0
    UINT32 reg_swrst_fly_hdmirx_prt4: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_FMS_FMS_BND_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_2004    fms_bnd_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_tp   :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_FMS_FMS_BND_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC99_2008    fms_bnd_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt3_phy_wr_sel: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_hdmirx_prt4_phy_wr_sel: 1;    //  4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}BND_CTRL_FMS_FMS_BND_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_FMS_FMS_BND_00_M23A0_T    fms_bnd_00 ;             // 0xCC99_2000
    BND_CTRL_FMS_FMS_BND_01_M23A0_T    fms_bnd_01 ;             // 0xCC99_2004
    BND_CTRL_FMS_FMS_BND_02_M23A0_T    fms_bnd_02 ;             // 0xCC99_2008
}BND_CTRL_FMS_REG_M23A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

