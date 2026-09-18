#ifndef _PMCU_MIP_CTRL_SADC_CPU_REG_O24A0_H_
#define _PMCU_MIP_CTRL_SADC_CPU_REG_O24A0_H_

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
    0xC63F_6000    sadc_cpu_000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_cpu_pdb          :  1,    //      0
                              : 11,    //  11: 1 reserved
    reg_sadc_cpu_pc           :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_cpu_cc           :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_sadc_cpu_isel         :  3,    //  22:20
                              :  9;    //  31:23 reserved
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6004    sadc_cpu_001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_cpu_lpf_soc      :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_sadc_cpu_lpf_chsel    :  3,    //   6: 4
                              :  1,    //      7 reserved
    reg_sadc_cpu_lpf_start    :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_sadc_cpu_lpf_dsel     :  3,    //  14:12
                              :  1,    //     15 reserved
    reg_sadc_cpu_lpf_mode     :  3,    //  18:16
                              :  5,    //  23:19 reserved
    reg_sadc_cpu_lpf_eoc_inv  :  1,    //     24
                              :  3,    //  27:25 reserved
    reg_sadc_cpu_lpf_manual   :  1,    //     28
                              :  3;    //  31:29 reserved
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6008    sadc_cpu_002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_cpu_lpf_data_clear: 1,    //      0
                              : 31;    //   31:1 reserved
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_600C    sadc_cpu_003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_cpu_lpf_data012      : 32;    //  31: 0
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6010    sadc_cpu_004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_cpu_lpf_data345      : 32;    //  31: 0
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6014    sadc_cpu_005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sadc_cpu_lpf_debug_en :  1,    //      0
                              : 31;    //   31:1 reserved
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_005_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6018    sadc_cpu_006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sadc_cpu_lpf_debug_data   :  8,    //   7: 0
                              : 20,    //  27: 8 reserved
    sadc_cpu_lpf_adc_done     :  1,    //     28
                              :  3;    //  31:29 reserved
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_006_O24A0_T;

/*-----------------------------------------------------------------------------------------
    pmcu_mip_ctrl_sadc_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_000_O24A0_T    sadc_cpu_000;    // 0xC63F_6000
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_001_O24A0_T    sadc_cpu_001;    // 0xC63F_6004
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_002_O24A0_T    sadc_cpu_002;    // 0xC63F_6008
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_003_O24A0_T    sadc_cpu_003;    // 0xC63F_600C
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_004_O24A0_T    sadc_cpu_004;    // 0xC63F_6010
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_005_O24A0_T    sadc_cpu_005;    // 0xC63F_6014
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_006_O24A0_T    sadc_cpu_006;    // 0xC63F_6018
}PMCU_MIP_CTRL_SADC_CPU_REG_O24A0_T;
/* 7 regs */

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

#define PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_000_O24A0_T_OFF     (BASEADDRESS+0x0000)
#define PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_001_O24A0_T_OFF     (BASEADDRESS+0x0004)
#define PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_002_O24A0_T_OFF     (BASEADDRESS+0x0008)
#define PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_003_O24A0_T_OFF     (BASEADDRESS+0x000C)
#define PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_004_O24A0_T_OFF     (BASEADDRESS+0x0010)
#define PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_005_O24A0_T_OFF     (BASEADDRESS+0x0014)
#define PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_006_O24A0_T_OFF     (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0xC63F_6000    sadc_cpu_000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_cpu_pdb   :  1;    //      0
    UINT32 resvd00            : 11;    //  11: 1 reserved
    UINT32 reg_sadc_cpu_pc    :  3;    //  14:12
    UINT32 resvd01            :  1;    //     15 reserved
    UINT32 reg_sadc_cpu_cc    :  3;    //  18:16
    UINT32 resvd02            :  1;    //     19 reserved
    UINT32 reg_sadc_cpu_isel  :  3;    //  22:20
    UINT32 resvd03            :  9;    //  31:23 reserved
    };
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_000_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6004    sadc_cpu_001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_cpu_lpf_soc: 1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_sadc_cpu_lpf_chsel: 3;    //  6:4
    UINT32 resvd01            :  1;    //      7 reserved
    UINT32 reg_sadc_cpu_lpf_start: 1;    //    8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_sadc_cpu_lpf_dsel: 3;    //  14:12
    UINT32 resvd03            :  1;    //     15 reserved
    UINT32 reg_sadc_cpu_lpf_mode: 3;    //  18:16
    UINT32 resvd04            :  5;    //  23:19 reserved
    UINT32 reg_sadc_cpu_lpf_eoc_inv: 1;    //  24
    UINT32 resvd05            :  3;    //  27:25 reserved
    UINT32 reg_sadc_cpu_lpf_manual: 1;    //  28
    UINT32 resvd06            :  3;    //  31:29 reserved
    };
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_001_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6008    sadc_cpu_002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_cpu_lpf_data_clear: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_002_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_600C    sadc_cpu_003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 sadc_cpu_lpf_data012: 32;    //  31:0
    };
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_003_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6010    sadc_cpu_004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 sadc_cpu_lpf_data345: 32;    //  31:0
    };
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_004_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6014    sadc_cpu_005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sadc_cpu_lpf_debug_en: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_005_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xC63F_6018    sadc_cpu_006 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 sadc_cpu_lpf_debug_data: 8;    //  7:0
    UINT32 resvd00            : 20;    //  27: 8 reserved
    UINT32 sadc_cpu_lpf_adc_done: 1;    //    28
    UINT32 resvd01            :  3;    //  31:29 reserved
    };
}PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_006_O24A0_T;

/*-----------------------------------------------------------------------------------------
    pmcu_mip_ctrl_sadc_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_000_O24A0_T    sadc_cpu_000;    // 0xC63F_6000
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_001_O24A0_T    sadc_cpu_001;    // 0xC63F_6004
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_002_O24A0_T    sadc_cpu_002;    // 0xC63F_6008
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_003_O24A0_T    sadc_cpu_003;    // 0xC63F_600C
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_004_O24A0_T    sadc_cpu_004;    // 0xC63F_6010
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_005_O24A0_T    sadc_cpu_005;    // 0xC63F_6014
    PMCU_MIP_CTRL_SADC_CPU_SADC_CPU_006_O24A0_T    sadc_cpu_006;    // 0xC63F_6018
}PMCU_MIP_CTRL_SADC_CPU_REG_O24A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _PMCU_MIP_CTRL_SADC_CPU_REG_H_

/* from 'O24_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

