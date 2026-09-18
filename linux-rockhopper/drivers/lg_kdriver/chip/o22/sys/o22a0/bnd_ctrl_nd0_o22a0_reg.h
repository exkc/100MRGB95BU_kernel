#ifndef _BND_CTRL_ND0_REG_H_
#define _BND_CTRL_ND0_REG_H_

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
    0xCC83_2000    bnd_hdr_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_flush_en__s0_bus      :  1,    //      0
    reg_bus_r_access_gating__s0_bus: 1,    //  1
    reg_bus_w_access_gating__s0_bus: 1,    //  2
                              :  1,    //      3 reserved
    reg_flush_done__s0_bus    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_bus_r_data_access_in_gating__s0_bus: 1,    //  8
    reg_bus_r_cmd_access_in_gating__s0_bus: 1,    //  9
    reg_bus_w_data_access_in_gating__s0_bus: 1,    //  10
    reg_bus_w_cmd_access_in_gating__s0_bus: 1,    //  11
                              : 20;    //  31:12 reserved
}BND_CTRL_ND0_SYN_BND_HDR_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC83_2004    bnd_hdr_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_flush_en__s1_cpu      :  1,    //      0
    reg_bus_r_access_gating__s1_cpu: 1,    //  1
    reg_bus_w_access_gating__s1_cpu: 1,    //  2
                              :  1,    //      3 reserved
    reg_flush_done__s1_cpu    :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_bus_r_data_access_in_gating__s1_cpu: 1,    //  8
    reg_bus_r_cmd_access_in_gating__s1_cpu: 1,    //  9
    reg_bus_w_data_access_in_gating__s1_cpu: 1,    //  10
    reg_bus_w_cmd_access_in_gating__s1_cpu: 1,    //  11
                              : 20;    //  31:12 reserved
}BND_CTRL_ND0_SYN_BND_HDR_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_ND0_SYN_BND_HDR_R00_O22A0_T        bnd_hdr_r00;             // 0xCC83_2000
    BND_CTRL_ND0_SYN_BND_HDR_R01_O22A0_T        bnd_hdr_r01;             // 0xCC83_2004
}BND_CTRL_ND0_REG_O22A0_T;
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

#define BND_CTRL_ND0_SYN_BND_HDR_R00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define BND_CTRL_ND0_SYN_BND_HDR_R01_O22A0_T_OFF                     (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xCC83_2000    bnd_hdr_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_flush_en__s0_bus: 1;    //      0
    UINT32 reg_bus_r_access_gating__s0_bus: 1;    //  1
    UINT32 reg_bus_w_access_gating__s0_bus: 1;    //  2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_flush_done__s0_bus: 1;    //    4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_bus_r_data_access_in_gating__s0_bus: 1;    //  8
    UINT32 reg_bus_r_cmd_access_in_gating__s0_bus: 1;    //  9
    UINT32 reg_bus_w_data_access_in_gating__s0_bus: 1;    //  10
    UINT32 reg_bus_w_cmd_access_in_gating__s0_bus: 1;    //  11
    UINT32 resvd02            : 20;    //  31:12 reserved
    };
}BND_CTRL_ND0_SYN_BND_HDR_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC83_2004    bnd_hdr_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_flush_en__s1_cpu: 1;    //      0
    UINT32 reg_bus_r_access_gating__s1_cpu: 1;    //  1
    UINT32 reg_bus_w_access_gating__s1_cpu: 1;    //  2
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_flush_done__s1_cpu: 1;    //    4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_bus_r_data_access_in_gating__s1_cpu: 1;    //  8
    UINT32 reg_bus_r_cmd_access_in_gating__s1_cpu: 1;    //  9
    UINT32 reg_bus_w_data_access_in_gating__s1_cpu: 1;    //  10
    UINT32 reg_bus_w_cmd_access_in_gating__s1_cpu: 1;    //  11
    UINT32 resvd02            : 20;    //  31:12 reserved
    };
}BND_CTRL_ND0_SYN_BND_HDR_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_nd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_ND0_SYN_BND_HDR_R00_O22A0_T        bnd_hdr_r00;             // 0xCC83_2000
    BND_CTRL_ND0_SYN_BND_HDR_R01_O22A0_T        bnd_hdr_r01;             // 0xCC83_2004
}BND_CTRL_ND0_REG_O22A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_ND0_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

