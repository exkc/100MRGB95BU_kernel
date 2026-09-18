#ifndef _MIP_CTRL_DPM_M23A0_REG_H_
#define _MIP_CTRL_DPM_M23A0_REG_H_

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
    0xF351_6000    mip_hdmi_dpm00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_tx_det_bypass_mode:  5,    //   4: 0
                              : 27;    //   31:5 reserved
}MIP_HDMI_DPM00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_6004    mip_hdmi_dpm01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_phy_tx_det_disable    :  5,    //   4: 0
                              : 27;    //   31:5 reserved
}MIP_HDMI_DPM01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_6008    mip_hdmi_dpm02 ''
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
}MIP_HDMI_DPM02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_600C    mip_hdmi_dpm03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  8,    //   7: 0 reserved
    reg_phy3_tx_det_out       :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_phy4_tx_det_out       :  1,    //     12
                              : 19;    //  31:13 reserved
}MIP_HDMI_DPM03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_6010    mip_hdmi_dpm04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dpm_tx_det_intr_status:  1,    //      0
                              : 31;    //   31:1 reserved
}MIP_HDMI_DPM04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_dpm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_HDMI_DPM00_M23A0_T    mip_hdmi_dpm00;     // 0xF351_6000
    MIP_HDMI_DPM01_M23A0_T    mip_hdmi_dpm01;     // 0xF351_6004
    MIP_HDMI_DPM02_M23A0_T    mip_hdmi_dpm02;     // 0xF351_6008
    MIP_HDMI_DPM03_M23A0_T    mip_hdmi_dpm03;     // 0xF351_600C
    MIP_HDMI_DPM04_M23A0_T    mip_hdmi_dpm04;     // 0xF351_6010
}MIP_CTRL_DPM_REG_M23A0_T;
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

#define MIP_HDMI_DPM00_M23A0_T_OFF            (BASEADDRESS+0x0000)
#define MIP_HDMI_DPM01_M23A0_T_OFF            (BASEADDRESS+0x0004)
#define MIP_HDMI_DPM02_M23A0_T_OFF            (BASEADDRESS+0x0008)
#define MIP_HDMI_DPM03_M23A0_T_OFF            (BASEADDRESS+0x000C)
#define MIP_HDMI_DPM04_M23A0_T_OFF            (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xF351_6000    mip_hdmi_dpm00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_tx_det_bypass_mode: 5;    //  4:0
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}MIP_HDMI_DPM00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_6004    mip_hdmi_dpm01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_phy_tx_det_disable: 5;    //  4:0
    UINT32 resvd00            : 27;    //   31:5 reserved
    };
}MIP_HDMI_DPM01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_6008    mip_hdmi_dpm02 ''
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
}MIP_HDMI_DPM02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_600C    mip_hdmi_dpm03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  8;    //   7: 0 reserved
    UINT32 reg_phy3_tx_det_out:  1;    //      8
    UINT32 resvd01            :  3;    //  11: 9 reserved
    UINT32 reg_phy4_tx_det_out:  1;    //     12
    UINT32 resvd02            : 19;    //  31:13 reserved
    };
}MIP_HDMI_DPM03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_6010    mip_hdmi_dpm04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dpm_tx_det_intr_status: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MIP_HDMI_DPM04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_dpm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_HDMI_DPM00_M23A0_T    mip_hdmi_dpm00;     // 0xF351_6000
    MIP_HDMI_DPM01_M23A0_T    mip_hdmi_dpm01;     // 0xF351_6004
    MIP_HDMI_DPM02_M23A0_T    mip_hdmi_dpm02;     // 0xF351_6008
    MIP_HDMI_DPM03_M23A0_T    mip_hdmi_dpm03;     // 0xF351_600C
    MIP_HDMI_DPM04_M23A0_T    mip_hdmi_dpm04;     // 0xF351_6010
}MIP_CTRL_DPM_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

