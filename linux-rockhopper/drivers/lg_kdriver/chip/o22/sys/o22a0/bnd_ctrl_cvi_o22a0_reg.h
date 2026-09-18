#ifndef _BND_CTRL_CVI_REG_H_
#define _BND_CTRL_CVI_REG_H_

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
    0xCC87_3000    bnd_cvi_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_flush_en__s0_cvi      :  1,    //      0
    reg_bus_r_access_gating__s0_cvi: 1,    //  1
    reg_bus_w_access_gating__s0_cvi: 1,    //  2
                              :  5,    //   7: 3 reserved
    reg_flush_done__s0_cvi    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_bus_r_data_access_in_gating__s0_cvi: 1,    //  12
    reg_bus_r_cmd_access_in_gating__s0_cvi: 1,    //  13
    reg_bus_w_data_access_in_gating__s0_cvi: 1,    //  14
    reg_bus_w_cmd_access_in_gating__s0_cvi: 1,    //  15
                              : 16;    //  31:16 reserved
}BND_CTRL_CVI_SYN_BND_CVI_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_3004    bnd_cvi_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_flush_en__s1_hdmirx   :  1,    //      0
    reg_bus_r_access_gating__s1_hdmirx: 1,    //  1
    reg_bus_w_access_gating__s1_hdmirx: 1,    //  2
                              :  5,    //   7: 3 reserved
    reg_flush_done__s1_hdmirx :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_bus_r_data_access_in_gating__s1_hdmirx: 1,    //  12
    reg_bus_r_cmd_access_in_gating__s1_hdmirx: 1,    //  13
    reg_bus_w_data_access_in_gating__s1_hdmirx: 1,    //  14
    reg_bus_w_cmd_access_in_gating__s1_hdmirx: 1,    //  15
                              : 16;    //  31:16 reserved
}BND_CTRL_CVI_SYN_BND_CVI_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_3008    bnd_cvi_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi__hdmirx_prt_pix_data_sel: 1,    //  0
                              : 31;    //   31:1 reserved
}BND_CTRL_CVI_SYN_BND_CVI_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_300C    bnd_cvi_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_isol_apb_en           :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_CVI_SYN_BND_CVI_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_3010    bnd_cvi_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_hdmi_3_dsc  :  1,    //      0
    reg_swrst_fly_hdmi_2_dsc  :  1,    //      1
    reg_swrst_fly_hdmi_1_dsc  :  1,    //      2
    reg_swrst_fly_hdmi_0_dsc  :  1,    //      3
    reg_swrst_fly_hdmi_3_cvi  :  1,    //      4
    reg_swrst_fly_hdmi_2_cvi  :  1,    //      5
    reg_swrst_fly_hdmi_1_cvi  :  1,    //      6
    reg_swrst_fly_hdmi_0_cvi  :  1,    //      7
                              : 24;    //   31:8 reserved
}BND_CTRL_CVI_SYN_BND_CVI_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_3014    bnd_cvi_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_fly_hdmi_3      :  1,    //      0
    reg_swrst_fly_hdmi_2      :  1,    //      1
    reg_swrst_fly_hdmi_1      :  1,    //      2
    reg_swrst_fly_hdmi_0      :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_CVI_SYN_BND_CVI_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_CVI_SYN_BND_CVI_R00_O22A0_T        bnd_cvi_r00;             // 0xCC87_3000
    BND_CTRL_CVI_SYN_BND_CVI_R01_O22A0_T        bnd_cvi_r01;             // 0xCC87_3004
    BND_CTRL_CVI_SYN_BND_CVI_R02_O22A0_T        bnd_cvi_r02;             // 0xCC87_3008
    BND_CTRL_CVI_SYN_BND_CVI_R03_O22A0_T        bnd_cvi_r03;             // 0xCC87_300C
    BND_CTRL_CVI_SYN_BND_CVI_R04_O22A0_T        bnd_cvi_r04;             // 0xCC87_3010
    BND_CTRL_CVI_SYN_BND_CVI_R05_O22A0_T        bnd_cvi_r05;             // 0xCC87_3014
}BND_CTRL_CVI_REG_O22A0_T;
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

#define BND_CTRL_CVI_SYN_BND_CVI_R00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define BND_CTRL_CVI_SYN_BND_CVI_R01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define BND_CTRL_CVI_SYN_BND_CVI_R02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define BND_CTRL_CVI_SYN_BND_CVI_R03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define BND_CTRL_CVI_SYN_BND_CVI_R04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define BND_CTRL_CVI_SYN_BND_CVI_R05_O22A0_T_OFF                     (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCC87_3000    bnd_cvi_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_flush_en__s0_cvi: 1;    //      0
    UINT32 reg_bus_r_access_gating__s0_cvi: 1;    //  1
    UINT32 reg_bus_w_access_gating__s0_cvi: 1;    //  2
    UINT32 resvd00            :  5;    //   7: 3 reserved
    UINT32 reg_flush_done__s0_cvi: 1;    //    8
    UINT32 resvd01            :  3;    //  11: 9 reserved
    UINT32 reg_bus_r_data_access_in_gating__s0_cvi: 1;    //  12
    UINT32 reg_bus_r_cmd_access_in_gating__s0_cvi: 1;    //  13
    UINT32 reg_bus_w_data_access_in_gating__s0_cvi: 1;    //  14
    UINT32 reg_bus_w_cmd_access_in_gating__s0_cvi: 1;    //  15
    UINT32 resvd02            : 16;    //  31:16 reserved
    };
}BND_CTRL_CVI_SYN_BND_CVI_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_3004    bnd_cvi_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_flush_en__s1_hdmirx: 1;    //   0
    UINT32 reg_bus_r_access_gating__s1_hdmirx: 1;    //  1
    UINT32 reg_bus_w_access_gating__s1_hdmirx: 1;    //  2
    UINT32 resvd00            :  5;    //   7: 3 reserved
    UINT32 reg_flush_done__s1_hdmirx: 1;    //  8
    UINT32 resvd01            :  3;    //  11: 9 reserved
    UINT32 reg_bus_r_data_access_in_gating__s1_hdmirx: 1;    //  12
    UINT32 reg_bus_r_cmd_access_in_gating__s1_hdmirx: 1;    //  13
    UINT32 reg_bus_w_data_access_in_gating__s1_hdmirx: 1;    //  14
    UINT32 reg_bus_w_cmd_access_in_gating__s1_hdmirx: 1;    //  15
    UINT32 resvd02            : 16;    //  31:16 reserved
    };
}BND_CTRL_CVI_SYN_BND_CVI_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_3008    bnd_cvi_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi__hdmirx_prt_pix_data_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_CVI_SYN_BND_CVI_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_300C    bnd_cvi_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_isol_apb_en    :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_CVI_SYN_BND_CVI_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_3010    bnd_cvi_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_hdmi_3_dsc: 1;    //  0
    UINT32 reg_swrst_fly_hdmi_2_dsc: 1;    //  1
    UINT32 reg_swrst_fly_hdmi_1_dsc: 1;    //  2
    UINT32 reg_swrst_fly_hdmi_0_dsc: 1;    //  3
    UINT32 reg_swrst_fly_hdmi_3_cvi: 1;    //  4
    UINT32 reg_swrst_fly_hdmi_2_cvi: 1;    //  5
    UINT32 reg_swrst_fly_hdmi_1_cvi: 1;    //  6
    UINT32 reg_swrst_fly_hdmi_0_cvi: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}BND_CTRL_CVI_SYN_BND_CVI_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC87_3014    bnd_cvi_r05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_fly_hdmi_3: 1;    //      0
    UINT32 reg_swrst_fly_hdmi_2: 1;    //      1
    UINT32 reg_swrst_fly_hdmi_1: 1;    //      2
    UINT32 reg_swrst_fly_hdmi_0: 1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}BND_CTRL_CVI_SYN_BND_CVI_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_CVI_SYN_BND_CVI_R00_O22A0_T        bnd_cvi_r00;             // 0xCC87_3000
    BND_CTRL_CVI_SYN_BND_CVI_R01_O22A0_T        bnd_cvi_r01;             // 0xCC87_3004
    BND_CTRL_CVI_SYN_BND_CVI_R02_O22A0_T        bnd_cvi_r02;             // 0xCC87_3008
    BND_CTRL_CVI_SYN_BND_CVI_R03_O22A0_T        bnd_cvi_r03;             // 0xCC87_300C
    BND_CTRL_CVI_SYN_BND_CVI_R04_O22A0_T        bnd_cvi_r04;             // 0xCC87_3010
    BND_CTRL_CVI_SYN_BND_CVI_R05_O22A0_T        bnd_cvi_r05;             // 0xCC87_3014
}BND_CTRL_CVI_REG_O22A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_CVI_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

