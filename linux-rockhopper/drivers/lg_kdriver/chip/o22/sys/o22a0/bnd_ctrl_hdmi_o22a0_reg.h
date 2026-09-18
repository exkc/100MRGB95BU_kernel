#ifndef _BND_CTRL_HDMI_REG_H_
#define _BND_CTRL_HDMI_REG_H_

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
    0xC897_2000    bnd_hdmi_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt1_cec_enable:  1,    //      0
    reg_hdmirx_prt2_cec_enable:  1,    //      1
    reg_hdmirx_prt3_cec_enable:  1,    //      2
    reg_hdmirx_prt4_cec_enable:  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_HDMI_SYN_BND_HDMI_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC897_2004    bnd_hdmi_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_monitor_sel_0         :  4,    //   3: 0
    reg_monitor_sel_1         :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}BND_CTRL_HDMI_SYN_BND_HDMI_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC897_2008    syn_hdmi_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi__crg_clk_rst_sel : 32;    //  31: 0
}BND_CTRL_HDMI_SYN_HDMI_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_HDMI_SYN_BND_HDMI_R00_O22A0_T      bnd_hdmi_r00;            // 0xC897_2000
    BND_CTRL_HDMI_SYN_BND_HDMI_R01_O22A0_T      bnd_hdmi_r01;            // 0xC897_2004
    BND_CTRL_HDMI_SYN_HDMI_R02_O22A0_T      syn_hdmi_r02;            // 0xC897_2008
}BND_CTRL_HDMI_REG_O22A0_T;
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

#define BND_CTRL_HDMI_SYN_BND_HDMI_R00_O22A0_T_OFF                   (BASEADDRESS+0x0000)
#define BND_CTRL_HDMI_SYN_BND_HDMI_R01_O22A0_T_OFF                   (BASEADDRESS+0x0004)
#define BND_CTRL_HDMI_SYN_HDMI_R02_O22A0_T_OFF                   (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xC897_2000    bnd_hdmi_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt1_cec_enable: 1;    //  0
    UINT32 reg_hdmirx_prt2_cec_enable: 1;    //  1
    UINT32 reg_hdmirx_prt3_cec_enable: 1;    //  2
    UINT32 reg_hdmirx_prt4_cec_enable: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_HDMI_SYN_BND_HDMI_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC897_2004    bnd_hdmi_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_monitor_sel_0  :  4;    //   3: 0
    UINT32 reg_monitor_sel_1  :  4;    //   7: 4
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_HDMI_SYN_BND_HDMI_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xC897_2008    syn_hdmi_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi__crg_clk_rst_sel: 32;    //  31:0
    };
}BND_CTRL_HDMI_SYN_HDMI_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_HDMI_SYN_BND_HDMI_R00_O22A0_T      bnd_hdmi_r00;            // 0xC897_2000
    BND_CTRL_HDMI_SYN_BND_HDMI_R01_O22A0_T      bnd_hdmi_r01;            // 0xC897_2004
    BND_CTRL_HDMI_SYN_HDMI_R02_O22A0_T      syn_hdmi_r02;            // 0xC897_2008
}BND_CTRL_HDMI_REG_O22A0_T;
/* 3 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_HDMI_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

