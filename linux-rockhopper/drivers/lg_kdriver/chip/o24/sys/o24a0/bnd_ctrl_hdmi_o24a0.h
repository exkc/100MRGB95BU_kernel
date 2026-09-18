#ifndef _BND_CTRL_HDMI_REG_O24A0_H_
#define _BND_CTRL_HDMI_REG_O24A0_H_

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
    0xC8D7_2000    cvi_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt1_phy_wr_sel:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdmirx_prt2_phy_wr_sel:  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdmirx_prt3_phy_wr_sel:  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_hdmirx_prt4_phy_wr_sel:  1,    //     12
                              : 19;    //  31:13 reserved
}BND_CTRL_HDMI_CVI_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_2004    cvi_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earctx_apb_i2c_sel    :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_HDMI_CVI_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_HDMI_CVI_SYN_00_O24A0_T    cvi_syn_00;             // 0xC8D7_2000
    BND_CTRL_HDMI_CVI_SYN_01_O24A0_T    cvi_syn_01;             // 0xC8D7_2004
}BND_CTRL_HDMI_REG_O24A0_T;
/* 2 regs */

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

#define BND_CTRL_O24A0_HDMI_CVI_SYN_00_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define BND_CTRL_O24A0_HDMI_CVI_SYN_01_O24A0_T_OFF                (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xC8D7_2000    cvi_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt1_phy_wr_sel: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_hdmirx_prt2_phy_wr_sel: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_hdmirx_prt3_phy_wr_sel: 1;    //  8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_hdmirx_prt4_phy_wr_sel: 1;    //  12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}BND_CTRL_HDMI_CVI_SYN_00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8D7_2004    cvi_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earctx_apb_i2c_sel: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_HDMI_CVI_SYN_01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_HDMI_CVI_SYN_00_O24A0_T    cvi_syn_00;             // 0xC8D7_2000
    BND_CTRL_HDMI_CVI_SYN_01_O24A0_T    cvi_syn_01;             // 0xC8D7_2004
}BND_CTRL_HDMI_REG_O24A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _BND_CTRL_HDMI_REG_H_

/* from 'O24_CTOP_SYN_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

