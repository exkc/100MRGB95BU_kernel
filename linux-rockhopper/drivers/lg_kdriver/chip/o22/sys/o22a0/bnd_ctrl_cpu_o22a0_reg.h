#ifndef _BND_CTRL_CPU_REG_H_
#define _BND_CTRL_CPU_REG_H_

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
    0xCAA3_3000    bnd_cpu_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_auto_mode_apb_nw: 1,    //     0
    reg_pchkerr_apb_nw        :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3004    bnd_cpu_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_start_addr_apb_nw: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3008    bnd_cpu_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_end_addr_apb_nw: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_300C    bnd_cpu_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_auto_mode_apb_sw: 1,    //     0
    reg_pchkerr_apb_sw        :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3010    bnd_cpu_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_start_addr_apb_sw: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3014    bnd_cpu_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_end_addr_apb_sw: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3018    bnd_cpu_r06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_auto_mode_apb_se: 1,    //     0
    reg_pchkerr_apb_se        :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_301C    bnd_cpu_r07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_start_addr_apb_se: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3020    bnd_cpu_r08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_end_addr_apb_se: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3024    bnd_cpu_r09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_auto_mode_apb_ne: 1,    //     0
    reg_pchkerr_apb_ne        :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3028    bnd_cpu_r10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_start_addr_apb_ne: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_302C    bnd_cpu_r11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_end_addr_apb_ne: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3030    bnd_cpu_r12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_auto_mode_apb_cd: 1,    //     0
    reg_pchkerr_apb_cd        :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3034    bnd_cpu_r13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_start_addr_apb_cd: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3038    bnd_cpu_r14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_end_addr_apb_cd: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_303C    bnd_cpu_r15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_auto_mode_apb_pq: 1,    //     0
    reg_pchkerr_apb_pq        :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3040    bnd_cpu_r16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_start_addr_apb_pq: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R16_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3044    bnd_cpu_r17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pchkerr_end_addr_apb_pq: 28,    //  27:0
                              :  4;    //  31:28 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R17_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3048    bnd_cpu_r18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpo_outmux_sel        :  1,    //      0
    reg_tpi_cam_mux_sel       :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R18_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_304C    bnd_cpu_r19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_efuse_pd              :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R19_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3050    bnd_cpu_r20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tx_async_apb_auto_resp_disable: 1,    //  0
                              : 31;    //   31:1 reserved
}BND_CTRL_CPU_SYN_BND_CPU_R20_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_CPU_SYN_BND_CPU_R00_O22A0_T        bnd_cpu_r00;             // 0xCAA3_3000
    BND_CTRL_CPU_SYN_BND_CPU_R01_O22A0_T        bnd_cpu_r01;             // 0xCAA3_3004
    BND_CTRL_CPU_SYN_BND_CPU_R02_O22A0_T        bnd_cpu_r02;             // 0xCAA3_3008
    BND_CTRL_CPU_SYN_BND_CPU_R03_O22A0_T        bnd_cpu_r03;             // 0xCAA3_300C
    BND_CTRL_CPU_SYN_BND_CPU_R04_O22A0_T        bnd_cpu_r04;             // 0xCAA3_3010
    BND_CTRL_CPU_SYN_BND_CPU_R05_O22A0_T        bnd_cpu_r05;             // 0xCAA3_3014
    BND_CTRL_CPU_SYN_BND_CPU_R06_O22A0_T        bnd_cpu_r06;             // 0xCAA3_3018
    BND_CTRL_CPU_SYN_BND_CPU_R07_O22A0_T        bnd_cpu_r07;             // 0xCAA3_301C
    BND_CTRL_CPU_SYN_BND_CPU_R08_O22A0_T        bnd_cpu_r08;             // 0xCAA3_3020
    BND_CTRL_CPU_SYN_BND_CPU_R09_O22A0_T        bnd_cpu_r09;             // 0xCAA3_3024
    BND_CTRL_CPU_SYN_BND_CPU_R10_O22A0_T        bnd_cpu_r10;             // 0xCAA3_3028
    BND_CTRL_CPU_SYN_BND_CPU_R11_O22A0_T        bnd_cpu_r11;             // 0xCAA3_302C
    BND_CTRL_CPU_SYN_BND_CPU_R12_O22A0_T        bnd_cpu_r12;             // 0xCAA3_3030
    BND_CTRL_CPU_SYN_BND_CPU_R13_O22A0_T        bnd_cpu_r13;             // 0xCAA3_3034
    BND_CTRL_CPU_SYN_BND_CPU_R14_O22A0_T        bnd_cpu_r14;             // 0xCAA3_3038
    BND_CTRL_CPU_SYN_BND_CPU_R15_O22A0_T        bnd_cpu_r15;             // 0xCAA3_303C
    BND_CTRL_CPU_SYN_BND_CPU_R16_O22A0_T        bnd_cpu_r16;             // 0xCAA3_3040
    BND_CTRL_CPU_SYN_BND_CPU_R17_O22A0_T        bnd_cpu_r17;             // 0xCAA3_3044
    BND_CTRL_CPU_SYN_BND_CPU_R18_O22A0_T        bnd_cpu_r18;             // 0xCAA3_3048
    BND_CTRL_CPU_SYN_BND_CPU_R19_O22A0_T        bnd_cpu_r19;             // 0xCAA3_304C
    BND_CTRL_CPU_SYN_BND_CPU_R20_O22A0_T        bnd_cpu_r20;             // 0xCAA3_3050
}BND_CTRL_CPU_REG_O22A0_T;
/* 21 regs */

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

#define BND_CTRL_CPU_SYN_BND_CPU_R00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define BND_CTRL_CPU_SYN_BND_CPU_R01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define BND_CTRL_CPU_SYN_BND_CPU_R02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define BND_CTRL_CPU_SYN_BND_CPU_R03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define BND_CTRL_CPU_SYN_BND_CPU_R04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define BND_CTRL_CPU_SYN_BND_CPU_R05_O22A0_T_OFF                     (BASEADDRESS+0x0014)
#define BND_CTRL_CPU_SYN_BND_CPU_R06_O22A0_T_OFF                     (BASEADDRESS+0x0018)
#define BND_CTRL_CPU_SYN_BND_CPU_R07_O22A0_T_OFF                     (BASEADDRESS+0x001C)
#define BND_CTRL_CPU_SYN_BND_CPU_R08_O22A0_T_OFF                     (BASEADDRESS+0x0020)
#define BND_CTRL_CPU_SYN_BND_CPU_R09_O22A0_T_OFF                     (BASEADDRESS+0x0024)
#define BND_CTRL_CPU_SYN_BND_CPU_R10_O22A0_T_OFF                     (BASEADDRESS+0x0028)
#define BND_CTRL_CPU_SYN_BND_CPU_R11_O22A0_T_OFF                     (BASEADDRESS+0x002C)
#define BND_CTRL_CPU_SYN_BND_CPU_R12_O22A0_T_OFF                     (BASEADDRESS+0x0030)
#define BND_CTRL_CPU_SYN_BND_CPU_R13_O22A0_T_OFF                     (BASEADDRESS+0x0034)
#define BND_CTRL_CPU_SYN_BND_CPU_R14_O22A0_T_OFF                     (BASEADDRESS+0x0038)
#define BND_CTRL_CPU_SYN_BND_CPU_R15_O22A0_T_OFF                     (BASEADDRESS+0x003C)
#define BND_CTRL_CPU_SYN_BND_CPU_R16_O22A0_T_OFF                     (BASEADDRESS+0x0040)
#define BND_CTRL_CPU_SYN_BND_CPU_R17_O22A0_T_OFF                     (BASEADDRESS+0x0044)
#define BND_CTRL_CPU_SYN_BND_CPU_R18_O22A0_T_OFF                     (BASEADDRESS+0x0048)
#define BND_CTRL_CPU_SYN_BND_CPU_R19_O22A0_T_OFF                     (BASEADDRESS+0x004C)
#define BND_CTRL_CPU_SYN_BND_CPU_R20_O22A0_T_OFF                     (BASEADDRESS+0x0050)

/*-----------------------------------------------------------------------------------------
    0xCAA3_3000    bnd_cpu_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_auto_mode_apb_nw: 1;    //  0
    UINT32 reg_pchkerr_apb_nw :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3004    bnd_cpu_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_start_addr_apb_nw: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3008    bnd_cpu_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_end_addr_apb_nw: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_300C    bnd_cpu_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_auto_mode_apb_sw: 1;    //  0
    UINT32 reg_pchkerr_apb_sw :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3010    bnd_cpu_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_start_addr_apb_sw: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3014    bnd_cpu_r05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_end_addr_apb_sw: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3018    bnd_cpu_r06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_auto_mode_apb_se: 1;    //  0
    UINT32 reg_pchkerr_apb_se :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_301C    bnd_cpu_r07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_start_addr_apb_se: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3020    bnd_cpu_r08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_end_addr_apb_se: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3024    bnd_cpu_r09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_auto_mode_apb_ne: 1;    //  0
    UINT32 reg_pchkerr_apb_ne :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3028    bnd_cpu_r10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_start_addr_apb_ne: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_302C    bnd_cpu_r11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_end_addr_apb_ne: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3030    bnd_cpu_r12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_auto_mode_apb_cd: 1;    //  0
    UINT32 reg_pchkerr_apb_cd :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3034    bnd_cpu_r13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_start_addr_apb_cd: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3038    bnd_cpu_r14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_end_addr_apb_cd: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_303C    bnd_cpu_r15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_auto_mode_apb_pq: 1;    //  0
    UINT32 reg_pchkerr_apb_pq :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3040    bnd_cpu_r16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_start_addr_apb_pq: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R16_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3044    bnd_cpu_r17 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pchkerr_end_addr_apb_pq: 28;    //  27:0
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R17_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3048    bnd_cpu_r18 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpo_outmux_sel :  1;    //      0
    UINT32 reg_tpi_cam_mux_sel:  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R18_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_304C    bnd_cpu_r19 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_efuse_pd       :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R19_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xCAA3_3050    bnd_cpu_r20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tx_async_apb_auto_resp_disable: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_CPU_SYN_BND_CPU_R20_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_CPU_SYN_BND_CPU_R00_O22A0_T        bnd_cpu_r00;             // 0xCAA3_3000
    BND_CTRL_CPU_SYN_BND_CPU_R01_O22A0_T        bnd_cpu_r01;             // 0xCAA3_3004
    BND_CTRL_CPU_SYN_BND_CPU_R02_O22A0_T        bnd_cpu_r02;             // 0xCAA3_3008
    BND_CTRL_CPU_SYN_BND_CPU_R03_O22A0_T        bnd_cpu_r03;             // 0xCAA3_300C
    BND_CTRL_CPU_SYN_BND_CPU_R04_O22A0_T        bnd_cpu_r04;             // 0xCAA3_3010
    BND_CTRL_CPU_SYN_BND_CPU_R05_O22A0_T        bnd_cpu_r05;             // 0xCAA3_3014
    BND_CTRL_CPU_SYN_BND_CPU_R06_O22A0_T        bnd_cpu_r06;             // 0xCAA3_3018
    BND_CTRL_CPU_SYN_BND_CPU_R07_O22A0_T        bnd_cpu_r07;             // 0xCAA3_301C
    BND_CTRL_CPU_SYN_BND_CPU_R08_O22A0_T        bnd_cpu_r08;             // 0xCAA3_3020
    BND_CTRL_CPU_SYN_BND_CPU_R09_O22A0_T        bnd_cpu_r09;             // 0xCAA3_3024
    BND_CTRL_CPU_SYN_BND_CPU_R10_O22A0_T        bnd_cpu_r10;             // 0xCAA3_3028
    BND_CTRL_CPU_SYN_BND_CPU_R11_O22A0_T        bnd_cpu_r11;             // 0xCAA3_302C
    BND_CTRL_CPU_SYN_BND_CPU_R12_O22A0_T        bnd_cpu_r12;             // 0xCAA3_3030
    BND_CTRL_CPU_SYN_BND_CPU_R13_O22A0_T        bnd_cpu_r13;             // 0xCAA3_3034
    BND_CTRL_CPU_SYN_BND_CPU_R14_O22A0_T        bnd_cpu_r14;             // 0xCAA3_3038
    BND_CTRL_CPU_SYN_BND_CPU_R15_O22A0_T        bnd_cpu_r15;             // 0xCAA3_303C
    BND_CTRL_CPU_SYN_BND_CPU_R16_O22A0_T        bnd_cpu_r16;             // 0xCAA3_3040
    BND_CTRL_CPU_SYN_BND_CPU_R17_O22A0_T        bnd_cpu_r17;             // 0xCAA3_3044
    BND_CTRL_CPU_SYN_BND_CPU_R18_O22A0_T        bnd_cpu_r18;             // 0xCAA3_3048
    BND_CTRL_CPU_SYN_BND_CPU_R19_O22A0_T        bnd_cpu_r19;             // 0xCAA3_304C
    BND_CTRL_CPU_SYN_BND_CPU_R20_O22A0_T        bnd_cpu_r20;             // 0xCAA3_3050
}BND_CTRL_CPU_REG_O22A0_T;
/* 21 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_CPU_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

