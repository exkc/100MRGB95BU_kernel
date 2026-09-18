#ifndef _BND_CTRL_HDR_REG_H_
#define _BND_CTRL_HDR_REG_H_

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
    0xCCCF_3000    bnd_nd0_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    emmc_tmclk_en             :  1,    //      0
                              :  7,    //   7: 1 reserved
    emmc_tmclk_div            : 10,    //  17: 8
                              : 14;    //  31:18 reserved
}BND_CTRL_HDR_SYN_BND_ND0_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3008    bnd_hdmi_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_monitor_sel_0         :  4,    //   3: 0
    reg_monitor_sel_1         :  4,    //   7: 4
                              : 24;    //   31:8 reserved
}BND_CTRL_HDR_SYN_BND_HDMI_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_HDR_SYN_BND_ND0_R00_O22A0_T        bnd_nd0_r00;             // 0xCCCF_3000
    UINT32                             _rsvd_00[1];             // 0xCCCF_3004
    BND_CTRL_HDR_SYN_BND_HDMI_R01_O22A0_T       bnd_hdmi_r01;            // 0xCCCF_3008
}BND_CTRL_HDR_REG_O22A0_T;
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

#define BND_CTRL_HDR_SYN_BND_ND0_R00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define BND_CTRL_HDR_SYN_BND_HDMI_R01_O22A0_T_OFF                    (BASEADDRESS+0x0008)

/*-----------------------------------------------------------------------------------------
    0xCCCF_3000    bnd_nd0_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 emmc_tmclk_en      :  1;    //      0
    UINT32 resvd00            :  7;    //   7: 1 reserved
    UINT32 emmc_tmclk_div     : 10;    //  17: 8
    UINT32 resvd01            : 14;    //  31:18 reserved
    };
}BND_CTRL_HDR_SYN_BND_ND0_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCCCF_3008    bnd_hdmi_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_monitor_sel_0  :  4;    //   3: 0
    UINT32 reg_monitor_sel_1  :  4;    //   7: 4
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_HDR_SYN_BND_HDMI_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_hdr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_HDR_SYN_BND_ND0_R00_O22A0_T        bnd_nd0_r00;             // 0xCCCF_3000
    UINT32                             _rsvd_00[1];             // 0xCCCF_3004
    BND_CTRL_HDR_SYN_BND_HDMI_R01_O22A0_T       bnd_hdmi_r01;            // 0xCCCF_3008
}BND_CTRL_HDR_REG_O22A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_HDR_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

