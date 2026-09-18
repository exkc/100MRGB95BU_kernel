#ifndef _MIP_CTRL_HDMI_DPM_REG_O26A0_H_
#define _MIP_CTRL_HDMI_DPM_REG_O26A0_H_

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
    0xCA3A_4000    mip_hdmi_dpm00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_tx_det_bypass_mode:  5,    //   4: 0
                              : 27;    //   31:5 reserved
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_4004    mip_hdmi_dpm01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_tx_det_disable    :  5,    //   4: 0
                              : 27;    //   31:5 reserved
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_4008    mip_hdmi_dpm02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_tx_det_en         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_phy_mon_all_ch        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_phy_low_vsen          :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_phy_dpm_odt           :  1,    //     12
                              : 19;    //  31:13 reserved
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_400C    mip_hdmi_dpm03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy1_tx_det_out       :  1,    //      0
    reg_phy2_tx_det_out       :  1,    //      1
    reg_phy3_tx_det_out       :  1,    //      2
    reg_phy4_tx_det_out       :  1,    //      3
                              : 28;    //   31:4 reserved
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_4010    mip_hdmi_dpm04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dpm_tx_det_intr_status:  1,    //      0
                              : 31;    //   31:1 reserved
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_hdmi_dpm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM00_O26A0_T    mip_hdmi_dpm00;    // 0xCA3A_4000
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM01_O26A0_T    mip_hdmi_dpm01;    // 0xCA3A_4004
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM02_O26A0_T    mip_hdmi_dpm02;    // 0xCA3A_4008
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM03_O26A0_T    mip_hdmi_dpm03;    // 0xCA3A_400C
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM04_O26A0_T    mip_hdmi_dpm04;    // 0xCA3A_4010
}MIP_CTRL_HDMI_DPM_REG_O26A0_T;
/* 5 regs */

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

#define MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM00_O26A0_T_OFF        (BASEADDRESS+0x0000)
#define MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM01_O26A0_T_OFF        (BASEADDRESS+0x0004)
#define MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM02_O26A0_T_OFF        (BASEADDRESS+0x0008)
#define MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM03_O26A0_T_OFF        (BASEADDRESS+0x000C)
#define MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM04_O26A0_T_OFF        (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCA3A_4000    mip_hdmi_dpm00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_tx_det_bypass_mode: 5;    //  4:0
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_4004    mip_hdmi_dpm01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_tx_det_disable: 5;    //  4:0
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_4008    mip_hdmi_dpm02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_tx_det_en  :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_phy_mon_all_ch :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_phy_low_vsen   :  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_phy_dpm_odt    :  1;    //     12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_400C    mip_hdmi_dpm03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy1_tx_det_out:  1;    //      0
    UINT32 reg_phy2_tx_det_out:  1;    //      1
    UINT32 reg_phy3_tx_det_out:  1;    //      2
    UINT32 reg_phy4_tx_det_out:  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_4010    mip_hdmi_dpm04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dpm_tx_det_intr_status: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_hdmi_dpm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM00_O26A0_T    mip_hdmi_dpm00;    // 0xCA3A_4000
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM01_O26A0_T    mip_hdmi_dpm01;    // 0xCA3A_4004
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM02_O26A0_T    mip_hdmi_dpm02;    // 0xCA3A_4008
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM03_O26A0_T    mip_hdmi_dpm03;    // 0xCA3A_400C
    MIP_CTRL_HDMI_DPM_MIP_HDMI_DPM04_O26A0_T    mip_hdmi_dpm04;    // 0xCA3A_4010
}MIP_CTRL_HDMI_DPM_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MIP_CTRL_HDMI_DPM_REG_H_

/* from 'O26_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

