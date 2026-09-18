#ifndef _LNE_TILELET_O22A0_REG_H_
#define _LNE_TILELET_O22A0_REG_H_

/*----------------------------------------------------------------------------------------
   Control Constants
---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
   File Inclusions
---------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------
    0x0    tlt_reg_status ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    rcore_status              :  1,    //      0
    npu_status                :  1,    //      1
    mem_in_status             :  1,    //      2
    syn_status                :  1,    //      3
    mem_out_status            :  1,    //      4
    mem_mat_status            :  1,    //      5
    stp_status                :  1,    //      6
                              : 25;    //   31:7 reserved
} LNE_TLT_REG_STATUS;

/*-----------------------------------------------------------------------------------------
    0x4    tlt_reg_config0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    tlt_start                 :  4,    //   3: 0
    npu_data_format           :  6,    //   9: 4
                              :  2,    //  11:10 reserved
    npu_wgt_format            :  6,    //  17:12
                              :  2,    //  19:18 reserved
    npu_out_sft               :  4,    //  23:20
    npu_bias_q                :  5,    //  28:24
                              :  1,    //     29 reserved
    ic_invalid                :  1,    //     30
    npu_sat                   :  1;    //     31
} LNE_TLT_REG_CONFIG0;

/*-----------------------------------------------------------------------------------------
    0x8    tlt_reg_config1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    mblob0_config             :  4,    //   3: 0
    mblob1_config             :  4,    //   7: 4
    mblob2_config             :  4,    //  11: 8
                              : 20;    //  31:12 reserved
} LNE_TLT_REG_CONFIG1;

/*-----------------------------------------------------------------------------------------
    0xC    tlt_reg_maddr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    addr                      : 22,    //  21: 0
                              :  8,    //  29:22 reserved
    auto_addr_inc             :  1,    //     30
    rw                        :  1;    //     31
} LNE_TLT_REG_MADDR;

/*-----------------------------------------------------------------------------------------
    0x10    tlt_reg_mdata ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    data                      : 32;    //  31: 0
} LNE_TLT_REG_MDATA;

/*-----------------------------------------------------------------------------------------
    0x14    tlt_reg_error ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    error                     :  1,    //      0
    trap                      :  1,    //      1
                              : 30;    //   31:2 reserved
} LNE_TLT_REG_ERROR;

/*-----------------------------------------------------------------------------------------
    0x18    tlt_reg_lsema ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    local_sema                : 16,    //  15: 0
                              : 16;    //  31:16 reserved
} LNE_TLT_REG_LSEMA;

/*-----------------------------------------------------------------------------------------
    0x1C    tlt_reg_tltid ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    tlt_id                    :  4,    //   3: 0
    tle_id                    :  4,    //   7: 4
    chip_id                   :  4,    //  11: 8
                              : 20;    //  31:12 reserved
} LNE_TLT_REG_TLTID;

/*-----------------------------------------------------------------------------------------
    0x20    tlt_reg_param0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    param0                    : 32;    //  31: 0
} LNE_TLT_REG_PARAM0;

/*-----------------------------------------------------------------------------------------
    0x24    tlt_reg_param1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    param1                    : 32;    //  31: 0
} LNE_TLT_REG_PARAM1;

/*-----------------------------------------------------------------------------------------
    0x28    tlt_reg_param2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    param2                    : 32;    //  31: 0
} LNE_TLT_REG_PARAM2;

/*-----------------------------------------------------------------------------------------
    0x2C    tlt_reg_param3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    param3                    : 32;    //  31: 0
} LNE_TLT_REG_PARAM3;

/*-----------------------------------------------------------------------------------------
    0x30    tlt_reg_param4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    param4                    : 32;    //  31: 0
} LNE_TLT_REG_PARAM4;

/*-----------------------------------------------------------------------------------------
    0x34    tlt_reg_stp0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    dst_addr                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
} LNE_TLT_REG_STP0;

/*-----------------------------------------------------------------------------------------
    0x38    tlt_reg_stp1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    sema_idx                  :  4,    //   3: 0
    sema_en                   :  1,    //      4
                              :  3,    //   7: 5 reserved
    tlt_dst                   : 16,    //  23: 8
    tle_dst                   :  4,    //  27:24
    chip_dst                  :  4;    //  31:28
} LNE_TLT_REG_STP1;

/*-----------------------------------------------------------------------------------------
    0x3C    tlt_reg_prvpc ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    prv32_pc                  : 32;    //  31: 0
} LNE_TLT_REG_PRVPC;

/*-----------------------------------------------------------------------------------------
    0x40    tlt_reg_icbaddr ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    ic_base_addr              : 32;    //  31: 0
} LNE_TLT_REG_ICBADDR;

/*-----------------------------------------------------------------------------------------
    0x44    tlt_reg_gpr0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    gpr0                      : 32;    //  31: 0
} LNE_TLT_REG_GPR0;

/*-----------------------------------------------------------------------------------------
    0x48    tlt_reg_gpr1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    gpr1                      : 32;    //  31: 0
} LNE_TLT_REG_GPR1;

/*-----------------------------------------------------------------------------------------
    0x4C    tlt_reg_gpr2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    gpr2                      : 32;    //  31: 0
} LNE_TLT_REG_GPR2;

/*-----------------------------------------------------------------------------------------
    0x50    tlt_reg_gpr3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    gpr3                      : 32;    //  31: 0
} LNE_TLT_REG_GPR3;

/*-----------------------------------------------------------------------------------------
    0x54    tlt_reg_tp0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    tp0                       : 32;    //  31: 0
} LNE_TLT_REG_TP0;

/*-----------------------------------------------------------------------------------------
    0x58    tlt_reg_tp1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    uint32_t
    tp1                       : 32;    //  31: 0
} LNE_TLT_REG_TP1;

/*-----------------------------------------------------------------------------------------
    lne Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    LNE_TLT_REG_STATUS                      tlt0_reg_status           ;         // 0x0
    LNE_TLT_REG_CONFIG0                     tlt0_reg_config0          ;         // 0x4
    LNE_TLT_REG_CONFIG1                     tlt0_reg_config1          ;         // 0x8
    LNE_TLT_REG_MADDR                       tlt0_reg_maddr            ;         // 0xC
    LNE_TLT_REG_MDATA                       tlt0_reg_mdata            ;         // 0x10
    LNE_TLT_REG_ERROR                       tlt0_reg_error            ;         // 0x14
    LNE_TLT_REG_LSEMA                       tlt0_reg_lsema            ;         // 0x18
    LNE_TLT_REG_TLTID                       tlt0_reg_tltid            ;         // 0x1C
    LNE_TLT_REG_PARAM0                      tlt0_reg_param0           ;         // 0x20
    LNE_TLT_REG_PARAM1                      tlt0_reg_param1           ;         // 0x24
    LNE_TLT_REG_PARAM2                      tlt0_reg_param2           ;         // 0x28
    LNE_TLT_REG_PARAM3                      tlt0_reg_param3           ;         // 0x2C
    LNE_TLT_REG_PARAM4                      tlt0_reg_param4           ;         // 0x30
    LNE_TLT_REG_STP0                        tlt0_reg_stp0             ;         // 0x34
    LNE_TLT_REG_STP1                        tlt0_reg_stp1             ;         // 0x38
    LNE_TLT_REG_PRVPC                       tlt0_reg_prvpc            ;         // 0x3C
    LNE_TLT_REG_ICBADDR                     tlt0_reg_icbaddr          ;         // 0x40
    LNE_TLT_REG_GPR0                        tlt0_reg_gpr0             ;         // 0x44
    LNE_TLT_REG_GPR1                        tlt0_reg_gpr1             ;         // 0x48
    LNE_TLT_REG_GPR2                        tlt0_reg_gpr2             ;         // 0x4C
    LNE_TLT_REG_GPR3                        tlt0_reg_gpr3             ;         // 0x50
    LNE_TLT_REG_TP0                         tlt0_reg_tp0              ;         // 0x54
    LNE_TLT_REG_TP1                         tlt0_reg_tp1              ;         // 0x58
    uint32_t                                           _rsvd_00[  41] ;         // 0x5C ~ 0xFC
    LNE_TLT_REG_STATUS                      tlt1_reg_status           ;         // 0x100
    LNE_TLT_REG_CONFIG0                     tlt1_reg_config0          ;         // 0x104
    LNE_TLT_REG_CONFIG1                     tlt1_reg_config1          ;         // 0x108
    LNE_TLT_REG_MADDR                       tlt1_reg_maddr            ;         // 0x10C
    LNE_TLT_REG_MDATA                       tlt1_reg_mdata            ;         // 0x110
    LNE_TLT_REG_ERROR                       tlt1_reg_error            ;         // 0x114
    LNE_TLT_REG_LSEMA                       tlt1_reg_lsema            ;         // 0x118
    LNE_TLT_REG_TLTID                       tlt1_reg_tltid            ;         // 0x11C
    LNE_TLT_REG_PARAM0                      tlt1_reg_param0           ;         // 0x120
    LNE_TLT_REG_PARAM1                      tlt1_reg_param1           ;         // 0x124
    LNE_TLT_REG_PARAM2                      tlt1_reg_param2           ;         // 0x128
    LNE_TLT_REG_PARAM3                      tlt1_reg_param3           ;         // 0x12C
    LNE_TLT_REG_PARAM4                      tlt1_reg_param4           ;         // 0x130
    LNE_TLT_REG_STP0                        tlt1_reg_stp0             ;         // 0x134
    LNE_TLT_REG_STP1                        tlt1_reg_stp1             ;         // 0x138
    LNE_TLT_REG_PRVPC                       tlt1_reg_prvpc            ;         // 0x13C
    LNE_TLT_REG_ICBADDR                     tlt1_reg_icbaddr          ;         // 0x140
    LNE_TLT_REG_GPR0                        tlt1_reg_gpr0             ;         // 0x144
    LNE_TLT_REG_GPR1                        tlt1_reg_gpr1             ;         // 0x148
    LNE_TLT_REG_GPR2                        tlt1_reg_gpr2             ;         // 0x14C
    LNE_TLT_REG_GPR3                        tlt1_reg_gpr3             ;         // 0x150
    LNE_TLT_REG_TP0                         tlt1_reg_tp0              ;         // 0x154
    LNE_TLT_REG_TP1                         tlt1_reg_tp1              ;         // 0x158
    uint32_t                                           _rsvd_01[  41] ;         // 0x15C ~ 0x1FC
    LNE_TLT_REG_STATUS                      tlt2_reg_status           ;         // 0x200
    LNE_TLT_REG_CONFIG0                     tlt2_reg_config0          ;         // 0x204
    LNE_TLT_REG_CONFIG1                     tlt2_reg_config1          ;         // 0x208
    LNE_TLT_REG_MADDR                       tlt2_reg_maddr            ;         // 0x20C
    LNE_TLT_REG_MDATA                       tlt2_reg_mdata            ;         // 0x210
    LNE_TLT_REG_ERROR                       tlt2_reg_error            ;         // 0x214
    LNE_TLT_REG_LSEMA                       tlt2_reg_lsema            ;         // 0x218
    LNE_TLT_REG_TLTID                       tlt2_reg_tltid            ;         // 0x21C
    LNE_TLT_REG_PARAM0                      tlt2_reg_param0           ;         // 0x220
    LNE_TLT_REG_PARAM1                      tlt2_reg_param1           ;         // 0x224
    LNE_TLT_REG_PARAM2                      tlt2_reg_param2           ;         // 0x228
    LNE_TLT_REG_PARAM3                      tlt2_reg_param3           ;         // 0x22C
    LNE_TLT_REG_PARAM4                      tlt2_reg_param4           ;         // 0x230
    LNE_TLT_REG_STP0                        tlt2_reg_stp0             ;         // 0x234
    LNE_TLT_REG_STP1                        tlt2_reg_stp1             ;         // 0x238
    LNE_TLT_REG_PRVPC                       tlt2_reg_prvpc            ;         // 0x23C
    LNE_TLT_REG_ICBADDR                     tlt2_reg_icbaddr          ;         // 0x240
    LNE_TLT_REG_GPR0                        tlt2_reg_gpr0             ;         // 0x244
    LNE_TLT_REG_GPR1                        tlt2_reg_gpr1             ;         // 0x248
    LNE_TLT_REG_GPR2                        tlt2_reg_gpr2             ;         // 0x24C
    LNE_TLT_REG_GPR3                        tlt2_reg_gpr3             ;         // 0x250
    LNE_TLT_REG_TP0                         tlt2_reg_tp0              ;         // 0x254
    LNE_TLT_REG_TP1                         tlt2_reg_tp1              ;         // 0x258
    uint32_t                                           _rsvd_02[  41] ;         // 0x25C ~ 0x2FC
    LNE_TLT_REG_STATUS                      tlt3_reg_status           ;         // 0x300
    LNE_TLT_REG_CONFIG0                     tlt3_reg_config0          ;         // 0x304
    LNE_TLT_REG_CONFIG1                     tlt3_reg_config1          ;         // 0x308
    LNE_TLT_REG_MADDR                       tlt3_reg_maddr            ;         // 0x30C
    LNE_TLT_REG_MDATA                       tlt3_reg_mdata            ;         // 0x310
    LNE_TLT_REG_ERROR                       tlt3_reg_error            ;         // 0x314
    LNE_TLT_REG_LSEMA                       tlt3_reg_lsema            ;         // 0x318
    LNE_TLT_REG_TLTID                       tlt3_reg_tltid            ;         // 0x31C
    LNE_TLT_REG_PARAM0                      tlt3_reg_param0           ;         // 0x320
    LNE_TLT_REG_PARAM1                      tlt3_reg_param1           ;         // 0x324
    LNE_TLT_REG_PARAM2                      tlt3_reg_param2           ;         // 0x328
    LNE_TLT_REG_PARAM3                      tlt3_reg_param3           ;         // 0x32C
    LNE_TLT_REG_PARAM4                      tlt3_reg_param4           ;         // 0x330
    LNE_TLT_REG_STP0                        tlt3_reg_stp0             ;         // 0x334
    LNE_TLT_REG_STP1                        tlt3_reg_stp1             ;         // 0x338
    LNE_TLT_REG_PRVPC                       tlt3_reg_prvpc            ;         // 0x33C
    LNE_TLT_REG_ICBADDR                     tlt3_reg_icbaddr          ;         // 0x340
    LNE_TLT_REG_GPR0                        tlt3_reg_gpr0             ;         // 0x344
    LNE_TLT_REG_GPR1                        tlt3_reg_gpr1             ;         // 0x348
    LNE_TLT_REG_GPR2                        tlt3_reg_gpr2             ;         // 0x34C
    LNE_TLT_REG_GPR3                        tlt3_reg_gpr3             ;         // 0x350
    LNE_TLT_REG_TP0                         tlt3_reg_tp0              ;         // 0x354
    LNE_TLT_REG_TP1                         tlt3_reg_tp1              ;         // 0x358
} LNE_TILELET_O22A0_REG;
/* 23 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _LNE_TILELET_O22A0_REG_H_ */

/* from 'O22-A0_LNE_reg_man.xlsx'  2020.6.24  KST by LGSiCRDV V3.1B*/
