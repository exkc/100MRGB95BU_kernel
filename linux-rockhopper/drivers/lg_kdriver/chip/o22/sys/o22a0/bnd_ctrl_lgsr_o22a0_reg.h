#ifndef _BND_CTRL_LGSR_REG_H_
#define _BND_CTRL_LGSR_REG_H_

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
    0xCC3F_3000    bnd_lgsr_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    flush_en__s0_sr           :  1,    //      0
    bus_r_access_gating__s0_sr:  1,    //      1
                              :  2,    //   3: 2 reserved
    flush_done__s0_sr         :  1,    //      4
                              :  3,    //   7: 5 reserved
    bus_r_data_access_in_gating__s0_sr: 1,    //  8
    bus_r_cmd_access_in_gating__s0_sr: 1,    //  9
    bus_w_data_access_in_gating__s0_sr: 1,    //  10
    bus_w_cmd_access_in_gating__s0_sr: 1,    //  11
                              : 20;    //  31:12 reserved
}BND_CTRL_LGSR_SYN_BND_LGSR_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_3004    bnd_lgsr_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    flush_en__s1_nr           :  1,    //      0
    bus_r_access_gating__s1_nr:  1,    //      1
                              :  2,    //   3: 2 reserved
    flush_done__s1_nr         :  1,    //      4
                              :  3,    //   7: 5 reserved
    bus_r_data_access_in_gating__s1_nr: 1,    //  8
    bus_r_cmd_access_in_gating__s1_nr: 1,    //  9
    bus_w_data_access_in_gating__s1_nr: 1,    //  10
    bus_w_cmd_access_in_gating__s1_nr: 1,    //  11
                              : 20;    //  31:12 reserved
}BND_CTRL_LGSR_SYN_BND_LGSR_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_lgsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_LGSR_SYN_BND_LGSR_R01_O22A0_T      bnd_lgsr_r01;            // 0xCC3F_3000
    BND_CTRL_LGSR_SYN_BND_LGSR_R02_O22A0_T      bnd_lgsr_r02;            // 0xCC3F_3004
}BND_CTRL_LGSR_REG_O22A0_T;
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

#define BND_CTRL_LGSR_SYN_BND_LGSR_R01_O22A0_T_OFF                   (BASEADDRESS+0x0000)
#define BND_CTRL_LGSR_SYN_BND_LGSR_R02_O22A0_T_OFF                   (BASEADDRESS+0x0004)

/*-----------------------------------------------------------------------------------------
    0xCC3F_3000    bnd_lgsr_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 flush_en__s0_sr    :  1;    //      0
    UINT32 bus_r_access_gating__s0_sr: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 flush_done__s0_sr  :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 bus_r_data_access_in_gating__s0_sr: 1;    //  8
    UINT32 bus_r_cmd_access_in_gating__s0_sr: 1;    //  9
    UINT32 bus_w_data_access_in_gating__s0_sr: 1;    //  10
    UINT32 bus_w_cmd_access_in_gating__s0_sr: 1;    //  11
    UINT32 resvd02            : 20;    //  31:12 reserved
    };
}BND_CTRL_LGSR_SYN_BND_LGSR_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC3F_3004    bnd_lgsr_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 flush_en__s1_nr    :  1;    //      0
    UINT32 bus_r_access_gating__s1_nr: 1;    //  1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 flush_done__s1_nr  :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 bus_r_data_access_in_gating__s1_nr: 1;    //  8
    UINT32 bus_r_cmd_access_in_gating__s1_nr: 1;    //  9
    UINT32 bus_w_data_access_in_gating__s1_nr: 1;    //  10
    UINT32 bus_w_cmd_access_in_gating__s1_nr: 1;    //  11
    UINT32 resvd02            : 20;    //  31:12 reserved
    };
}BND_CTRL_LGSR_SYN_BND_LGSR_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_lgsr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_LGSR_SYN_BND_LGSR_R01_O22A0_T      bnd_lgsr_r01;            // 0xCC3F_3000
    BND_CTRL_LGSR_SYN_BND_LGSR_R02_O22A0_T      bnd_lgsr_r02;            // 0xCC3F_3004
}BND_CTRL_LGSR_REG_O22A0_T;
/* 2 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_LGSR_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

