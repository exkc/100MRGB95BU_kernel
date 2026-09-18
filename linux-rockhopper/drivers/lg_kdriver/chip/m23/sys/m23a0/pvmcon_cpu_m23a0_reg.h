#ifndef _PVMCON_CPU_M23A0_REG_H_
#define _PVMCON_CPU_M23A0_REG_H_

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
    0xCA22_3000    int_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_int_en                :  1,    //      0
                              : 31;    //   31:1 reserved
}PVMCON_CPU_INT_CTRL_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3004    int_clr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_int_cl                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_int_st                :  1,    //      4
                              : 27;    //   31:5 reserved
}PVMCON_CPU_INT_CLR_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3030    hpm_con ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_rstn                  :  1,    //      0
    hpm_pdb                   :  1,    //      1
                              :  2,    //   3: 2 reserved
    pvm_rstn                  :  1,    //      4
    pvm_pdb                   :  1,    //      5
                              : 26;    //   31:6 reserved
}PVMCON_CPU_HPM_CON_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3034    PVM_CPU ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cnt_pulse_vm              :  7,    //   6: 0
                              :  1,    //      7 reserved
    cnt_ro_vm                 :  3,    //  10: 8
                              :  1,    //     11 reserved
    cnt_out_vm                :  1,    //     12
                              : 19;    //  31:13 reserved
}PVMCON_CPU_PVMCON_CPU_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3040    clk_cnt ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_ext_clk_cnt           : 14,    //  13: 0
                              :  2,    //  15:14 reserved
    cnt_digi_vm               : 16;    //  31:16
}PVMCON_CPU_CLK_CNT_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3044    sel_div ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_sel_div               :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}PVMCON_CPU_SEL_DIV_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3048    hpm_mode ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_mode                  :  4,    //   3: 0
    vm_mode                   :  3,    //   6: 4
                              : 25;    //   31:7 reserved
}PVMCON_CPU_HPM_MODE_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_304C    hpm_cnt ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hpm_dout_latch            : 14,    //  13: 0
                              :  2,    //  15:14 reserved
    pvm_dout_latch            : 14,    //  29:16
                              :  2;    //  31:30 reserved
}PVMCON_CPU_HPM_CNT_M23A0_T;

/*-----------------------------------------------------------------------------------------
    PVM_CPU Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    PVMCON_CPU_INT_CTRL_M23A0_T           int_ctrl   ;             // 0xCA22_3000
    PVMCON_CPU_INT_CLR_M23A0_T            int_clr    ;             // 0xCA22_3004
    UINT32                             _rsvd_00[10];            // 0xCA22_3008 ~ 0xCA22_302C
    PVMCON_CPU_HPM_CON_M23A0_T            hpm_con    ;             // 0xCA22_3030
    PVMCON_CPU_PVMCON_CPU_M23A0_T            PVM_CPU    ;             // 0xCA22_3034
    UINT32                             _rsvd_01[2];             // 0xCA22_3038 ~ 0xCA22_303C
    PVMCON_CPU_CLK_CNT_M23A0_T            clk_cnt    ;             // 0xCA22_3040
    PVMCON_CPU_SEL_DIV_M23A0_T            sel_div    ;             // 0xCA22_3044
    PVMCON_CPU_HPM_MODE_M23A0_T           hpm_mode   ;             // 0xCA22_3048
    PVMCON_CPU_HPM_CNT_M23A0_T            hpm_cnt    ;             // 0xCA22_304C
}PVMCON_CPU_REG_M23A0_T;
/* 8 regs */

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

#define PVMCON_CPU_INT_CTRL_M23A0_T_OFF                        (BASEADDRESS+0x0000)
#define PVMCON_CPU_INT_CLR_M23A0_T_OFF                         (BASEADDRESS+0x0004)
#define PVMCON_CPU_HPM_CON_M23A0_T_OFF                         (BASEADDRESS+0x0030)
#define PVMCON_CPU_PVMCON_CPU_M23A0_T_OFF                         (BASEADDRESS+0x0034)
#define PVMCON_CPU_CLK_CNT_M23A0_T_OFF                         (BASEADDRESS+0x0040)
#define PVMCON_CPU_SEL_DIV_M23A0_T_OFF                         (BASEADDRESS+0x0044)
#define PVMCON_CPU_HPM_MODE_M23A0_T_OFF                        (BASEADDRESS+0x0048)
#define PVMCON_CPU_HPM_CNT_M23A0_T_OFF                         (BASEADDRESS+0x004C)

/*-----------------------------------------------------------------------------------------
    0xCA22_3000    int_ctrl ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_int_en         :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}PVMCON_CPU_INT_CTRL_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3004    int_clr ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_int_cl         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_int_st         :  1;    //      4
    UINT32 resvd01            : 27;    //   31:5 reserved
    };
}PVMCON_CPU_INT_CLR_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3030    hpm_con ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_rstn           :  1;    //      0
    UINT32 hpm_pdb            :  1;    //      1
    UINT32 resvd00            :  2;    //   3: 2 reserved
    UINT32 pvm_rstn           :  1;    //      4
    UINT32 pvm_pdb            :  1;    //      5
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}PVMCON_CPU_HPM_CON_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3034    PVM_CPU ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 cnt_pulse_vm       :  7;    //   6: 0
    UINT32 resvd00            :  1;    //      7 reserved
    UINT32 cnt_ro_vm          :  3;    //  10: 8
    UINT32 resvd01            :  1;    //     11 reserved
    UINT32 cnt_out_vm         :  1;    //     12
    UINT32 resvd02            : 19;    //  31:13 reserved
    };
}PVMCON_CPU_PVMCON_CPU_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3040    clk_cnt ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_ext_clk_cnt    : 14;    //  13: 0
    UINT32 resvd00            :  2;    //  15:14 reserved
    UINT32 cnt_digi_vm        : 16;    //  31:16
    };
}PVMCON_CPU_CLK_CNT_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3044    sel_div ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_sel_div        :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}PVMCON_CPU_SEL_DIV_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_3048    hpm_mode ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_mode           :  4;    //   3: 0
    UINT32 vm_mode            :  3;    //   6: 4
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}PVMCON_CPU_HPM_MODE_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA22_304C    hpm_cnt ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 hpm_dout_latch     : 14;    //  13: 0
    UINT32 resvd00            :  2;    //  15:14 reserved
    UINT32 pvm_dout_latch     : 14;    //  29:16
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}PVMCON_CPU_HPM_CNT_M23A0_T;

/*-----------------------------------------------------------------------------------------
    PVM_CPU Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    PVMCON_CPU_INT_CTRL_M23A0_T           int_ctrl   ;             // 0xCA22_3000
    PVMCON_CPU_INT_CLR_M23A0_T            int_clr    ;             // 0xCA22_3004
    UINT32                             _rsvd_00[10];            // 0xCA22_3008 ~ 0xCA22_302C
    PVMCON_CPU_HPM_CON_M23A0_T            hpm_con    ;             // 0xCA22_3030
    PVMCON_CPU_PVMCON_CPU_M23A0_T            PVM_CPU    ;             // 0xCA22_3034
    UINT32                             _rsvd_01[2];             // 0xCA22_3038 ~ 0xCA22_303C
    PVMCON_CPU_CLK_CNT_M23A0_T            clk_cnt    ;             // 0xCA22_3040
    PVMCON_CPU_SEL_DIV_M23A0_T            sel_div    ;             // 0xCA22_3044
    PVMCON_CPU_HPM_MODE_M23A0_T           hpm_mode   ;             // 0xCA22_3048
    PVMCON_CPU_HPM_CNT_M23A0_T            hpm_cnt    ;             // 0xCA22_304C
}PVMCON_CPU_REG_M23A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

