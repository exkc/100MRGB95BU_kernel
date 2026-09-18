#ifndef _BND_CTRL_ME0_REG_H_
#define _BND_CTRL_ME0_REG_H_

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
    0xCC9F_3000    bnd_nd0_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_md_drv_pdb         :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_pl_md_drv_usb_pdb     :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_tx_lo_drv_usb_pdb     :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_tx_lo_drv_usb_ck_div  :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_tx_lo_drv_pdb         :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_tx_lo_drv_ck_div      :  1,    //     20
                              : 11;    //  31:21 reserved
}BND_CTRL_ME0_SYN_BND_ND0_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9F_3100    bnd_nd0_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_flush_en__s0_usb3     :  1,    //      0
    reg_bus_r_access_gating__s0_usb3: 1,    //  1
    reg_bus_w_access_gating__s0_usb3: 1,    //  2
                              :  1,    //      3 reserved
    reg_flush_done__s0_usb3   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_bus_r_data_access_in_gating__s0_usb3: 1,    //  8
    reg_bus_r_cmd_access_in_gating__s0_usb3: 1,    //  9
    reg_bus_w_data_access_in_gating__s0_usb3: 1,    //  10
    reg_bus_w_cmd_access_in_gating__s0_usb3: 1,    //  11
                              : 20;    //  31:12 reserved
}BND_CTRL_ME0_SYN_BND_ND0_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9F_3104    bnd_me0_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_flush_en__s1_usb3     :  1,    //      0
    reg_bus_r_access_gating__s1_usb3: 1,    //  1
    reg_bus_w_access_gating__s1_usb3: 1,    //  2
                              :  1,    //      3 reserved
    reg_flush_done__s1_usb3   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_bus_r_data_access_in_gating__s1_usb3: 1,    //  8
    reg_bus_r_cmd_access_in_gating__s1_usb3: 1,    //  9
    reg_bus_w_data_access_in_gating__s1_usb3: 1,    //  10
    reg_bus_w_cmd_access_in_gating__s1_usb3: 1,    //  11
                              : 20;    //  31:12 reserved
}BND_CTRL_ME0_SYN_BND_ME0_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9F_3108    bnd_me0_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_flush_en__s2_usb2     :  1,    //      0
    reg_bus_r_access_gating__s2_usb2: 1,    //  1
    reg_bus_w_access_gating__s2_usb2: 1,    //  2
                              :  1,    //      3 reserved
    reg_flush_done__s2_usb2   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_bus_r_data_access_in_gating__s2_usb2: 1,    //  8
    reg_bus_r_cmd_access_in_gating__s2_usb2: 1,    //  9
    reg_bus_w_data_access_in_gating__s2_usb2: 1,    //  10
    reg_bus_w_cmd_access_in_gating__s2_usb2: 1,    //  11
                              : 20;    //  31:12 reserved
}BND_CTRL_ME0_SYN_BND_ME0_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9F_310C    bnd_me0_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_flush_en__s3_usb3     :  1,    //      0
    reg_bus_r_access_gating__s3_usb3: 1,    //  1
    reg_bus_w_access_gating__s3_usb3: 1,    //  2
                              :  1,    //      3 reserved
    reg_flush_done__s3_usb3   :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_bus_r_data_access_in_gating__s3_usb3: 1,    //  8
    reg_bus_r_cmd_access_in_gating__s3_usb3: 1,    //  9
    reg_bus_w_data_access_in_gating__s3_usb3: 1,    //  10
    reg_bus_w_cmd_access_in_gating__s3_usb3: 1,    //  11
                              : 20;    //  31:12 reserved
}BND_CTRL_ME0_SYN_BND_ME0_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_ME0_SYN_BND_ND0_R00_O22A0_T        bnd_nd0_r00;             // 0xCC9F_3000
    UINT32                             _rsvd_00[63];            // 0xCC9F_3004 ~ 0xCC9F_30FC
    BND_CTRL_ME0_SYN_BND_ND0_R01_O22A0_T        bnd_nd0_r01;             // 0xCC9F_3100
    BND_CTRL_ME0_SYN_BND_ME0_R02_O22A0_T        bnd_me0_r02;             // 0xCC9F_3104
    BND_CTRL_ME0_SYN_BND_ME0_R03_O22A0_T        bnd_me0_r03;             // 0xCC9F_3108
    BND_CTRL_ME0_SYN_BND_ME0_R04_O22A0_T        bnd_me0_r04;             // 0xCC9F_310C
}BND_CTRL_ME0_REG_O22A0_T;
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

#define BND_CTRL_ME0_SYN_BND_ND0_R00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define BND_CTRL_ME0_SYN_BND_ND0_R01_O22A0_T_OFF                     (BASEADDRESS+0x0100)
#define BND_CTRL_ME0_SYN_BND_ME0_R02_O22A0_T_OFF                     (BASEADDRESS+0x0104)
#define BND_CTRL_ME0_SYN_BND_ME0_R03_O22A0_T_OFF                     (BASEADDRESS+0x0108)
#define BND_CTRL_ME0_SYN_BND_ME0_R04_O22A0_T_OFF                     (BASEADDRESS+0x010C)

/*-----------------------------------------------------------------------------------------
    0xCC9F_3000    bnd_nd0_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_md_drv_pdb  :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_pl_md_drv_usb_pdb: 1;    //     4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_tx_lo_drv_usb_pdb: 1;    //     8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_tx_lo_drv_usb_ck_div: 1;    //  12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_tx_lo_drv_pdb  :  1;    //     16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_tx_lo_drv_ck_div: 1;    //     20
    UINT32 resvd05            : 11;    //  31:21 reserved
    };
}BND_CTRL_ME0_SYN_BND_ND0_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9F_3100    bnd_nd0_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_flush_en__s0_usb3: 1;    //     0
    UINT32 reg_bus_r_access_gating__s0_usb3: 1;    //  1
    UINT32 reg_bus_w_access_gating__s0_usb3: 1;    //  2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_flush_done__s0_usb3: 1;    //   4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_bus_r_data_access_in_gating__s0_usb3: 1;    //  8
    UINT32 reg_bus_r_cmd_access_in_gating__s0_usb3: 1;    //  9
    UINT32 reg_bus_w_data_access_in_gating__s0_usb3: 1;    //  10
    UINT32 reg_bus_w_cmd_access_in_gating__s0_usb3: 1;    //  11
    UINT32 resvd02            : 20;    //  31:12 reserved
    };
}BND_CTRL_ME0_SYN_BND_ND0_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9F_3104    bnd_me0_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_flush_en__s1_usb3: 1;    //     0
    UINT32 reg_bus_r_access_gating__s1_usb3: 1;    //  1
    UINT32 reg_bus_w_access_gating__s1_usb3: 1;    //  2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_flush_done__s1_usb3: 1;    //   4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_bus_r_data_access_in_gating__s1_usb3: 1;    //  8
    UINT32 reg_bus_r_cmd_access_in_gating__s1_usb3: 1;    //  9
    UINT32 reg_bus_w_data_access_in_gating__s1_usb3: 1;    //  10
    UINT32 reg_bus_w_cmd_access_in_gating__s1_usb3: 1;    //  11
    UINT32 resvd02            : 20;    //  31:12 reserved
    };
}BND_CTRL_ME0_SYN_BND_ME0_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9F_3108    bnd_me0_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_flush_en__s2_usb2: 1;    //     0
    UINT32 reg_bus_r_access_gating__s2_usb2: 1;    //  1
    UINT32 reg_bus_w_access_gating__s2_usb2: 1;    //  2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_flush_done__s2_usb2: 1;    //   4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_bus_r_data_access_in_gating__s2_usb2: 1;    //  8
    UINT32 reg_bus_r_cmd_access_in_gating__s2_usb2: 1;    //  9
    UINT32 reg_bus_w_data_access_in_gating__s2_usb2: 1;    //  10
    UINT32 reg_bus_w_cmd_access_in_gating__s2_usb2: 1;    //  11
    UINT32 resvd02            : 20;    //  31:12 reserved
    };
}BND_CTRL_ME0_SYN_BND_ME0_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9F_310C    bnd_me0_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_flush_en__s3_usb3: 1;    //     0
    UINT32 reg_bus_r_access_gating__s3_usb3: 1;    //  1
    UINT32 reg_bus_w_access_gating__s3_usb3: 1;    //  2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_flush_done__s3_usb3: 1;    //   4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_bus_r_data_access_in_gating__s3_usb3: 1;    //  8
    UINT32 reg_bus_r_cmd_access_in_gating__s3_usb3: 1;    //  9
    UINT32 reg_bus_w_data_access_in_gating__s3_usb3: 1;    //  10
    UINT32 reg_bus_w_cmd_access_in_gating__s3_usb3: 1;    //  11
    UINT32 resvd02            : 20;    //  31:12 reserved
    };
}BND_CTRL_ME0_SYN_BND_ME0_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_me0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_ME0_SYN_BND_ND0_R00_O22A0_T        bnd_nd0_r00;             // 0xCC9F_3000
    UINT32                             _rsvd_00[63];            // 0xCC9F_3004 ~ 0xCC9F_30FC
    BND_CTRL_ME0_SYN_BND_ND0_R01_O22A0_T        bnd_nd0_r01;             // 0xCC9F_3100
    BND_CTRL_ME0_SYN_BND_ME0_R02_O22A0_T        bnd_me0_r02;             // 0xCC9F_3104
    BND_CTRL_ME0_SYN_BND_ME0_R03_O22A0_T        bnd_me0_r03;             // 0xCC9F_3108
    BND_CTRL_ME0_SYN_BND_ME0_R04_O22A0_T        bnd_me0_r04;             // 0xCC9F_310C
}BND_CTRL_ME0_REG_O22A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_ME0_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

