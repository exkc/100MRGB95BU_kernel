#ifndef _MIP_CTRL_CVBSAFE_REG_O26A0_H_
#define _MIP_CTRL_CVBSAFE_REG_O26A0_H_

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
    0xC8A3_4018    mip_adc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvbsafe_pll_offset_mode: 1,    //      0
    reg_cvbsafe_pll_freq_update: 1,    //      1
    reg_cvbsafe_pll_fout1_en  :  1,    //      2
    reg_cvbsafe_pll_fine_div  :  1,    //      3
    reg_cvbsafe_pll_dss       :  1,    //      4
    reg_cvbsafe_adc_datack_inv:  1,    //      5
    reg_cvbsafe_adc_pdb       :  1,    //      6
    reg_cvbsafe_adc_iclp      :  2,    //   8: 7
    reg_cvbsafe_adc_shield_on :  2,    //  10: 9
    reg_cvbsafe_adc_insel     :  1,    //     11
    reg_cvbsafe_adc_cksel     :  1,    //     12
    reg_cvbsafe_adc_lpf       :  1,    //     13
    reg_cvbsafe_adc_dcatt     :  1,    //     14
    reg_cvbsafe_adc_gc        :  3,    //  17:15
    reg_cvbsafe_adc_refsel    :  2,    //  19:18
    reg_cvbsafe_adc_decm      :  2,    //  21:20
    reg_cvbsafe_adc_clp       :  1,    //     22
    reg_cvbsafe_adc_iclp2     :  2,    //  24:23
    reg_cvbsafe_adc_pdbm      :  1,    //     25
    reg_cvbsafe_adc_isel      :  3,    //  28:26
    reg_cvbsafe_adc_bw        :  1,    //     29
    reg_cvbsafe_adc_dcsel     :  2;    //  31:30
}MIP_CTRL_CVBSAFE_MIP_ADC06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_401C    mip_adc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvbsafe_pll_m         :  6,    //   5: 0
    reg_cvbsafe_pll_fine_control: 3,    //  8: 6
    reg_cvbsafe_pll_accuracy  :  2,    //  10: 9
    reg_cvbsafe_pll_wake_bypass: 1,    //     11
    reg_cvbsafe_pll_sync_on   :  1,    //     12
    reg_cvbsafe_pll_icp_g     :  1,    //     13
    reg_cvbsafe_pll_nsc       :  4,    //  17:14
    reg_cvbsafe_pll_pdb       :  1,    //     18
    reg_cvbsafe_pll_cih       :  4,    //  22:19
    reg_cvbsafe_pll_npc       :  6,    //  28:23
                              :  3;    //  31:29 reserved
}MIP_CTRL_CVBSAFE_MIP_ADC07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_4020    mip_adc08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvbsafe_pll_offset    :  8,    //   7: 0
    reg_cvbsafe_pll_updn_max  :  7,    //  14: 8
    reg_cvbsafe_pll_out_div   :  7,    //  21:15
    reg_cvbsafe_pll_out_div2  :  7,    //  28:22
                              :  3;    //  31:29 reserved
}MIP_CTRL_CVBSAFE_MIP_ADC08_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_4024    mip_adc09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvbsafe_pll_mod_freq_max: 9,    //  8: 0
                              : 23;    //   31:9 reserved
}MIP_CTRL_CVBSAFE_MIP_ADC09_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_4028    mip_adc10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvbsafe_pll_lock_f    :  1,    //      0
                              : 31;    //   31:1 reserved
}MIP_CTRL_CVBSAFE_MIP_ADC10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_cvbsafe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[6];             // 0xC8A3_4000 ~ 0xC8A3_4014
    MIP_CTRL_CVBSAFE_MIP_ADC06_O26A0_T    mip_adc06;            // 0xC8A3_4018
    MIP_CTRL_CVBSAFE_MIP_ADC07_O26A0_T    mip_adc07;            // 0xC8A3_401C
    MIP_CTRL_CVBSAFE_MIP_ADC08_O26A0_T    mip_adc08;            // 0xC8A3_4020
    MIP_CTRL_CVBSAFE_MIP_ADC09_O26A0_T    mip_adc09;            // 0xC8A3_4024
    MIP_CTRL_CVBSAFE_MIP_ADC10_O26A0_T    mip_adc10;            // 0xC8A3_4028
}MIP_CTRL_CVBSAFE_REG_O26A0_T;
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

#define MIP_CTRL_CVBSAFE_MIP_ADC06_O26A0_T_OFF              (BASEADDRESS+0x0018)
#define MIP_CTRL_CVBSAFE_MIP_ADC07_O26A0_T_OFF              (BASEADDRESS+0x001C)
#define MIP_CTRL_CVBSAFE_MIP_ADC08_O26A0_T_OFF              (BASEADDRESS+0x0020)
#define MIP_CTRL_CVBSAFE_MIP_ADC09_O26A0_T_OFF              (BASEADDRESS+0x0024)
#define MIP_CTRL_CVBSAFE_MIP_ADC10_O26A0_T_OFF              (BASEADDRESS+0x0028)

/*-----------------------------------------------------------------------------------------
    0xC8A3_4018    mip_adc06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvbsafe_pll_offset_mode: 1;    //  0
    UINT32 reg_cvbsafe_pll_freq_update: 1;    //  1
    UINT32 reg_cvbsafe_pll_fout1_en: 1;    //  2
    UINT32 reg_cvbsafe_pll_fine_div: 1;    //  3
    UINT32 reg_cvbsafe_pll_dss:  1;    //      4
    UINT32 reg_cvbsafe_adc_datack_inv: 1;    //  5
    UINT32 reg_cvbsafe_adc_pdb:  1;    //      6
    UINT32 reg_cvbsafe_adc_iclp: 2;    //   8: 7
    UINT32 reg_cvbsafe_adc_shield_on: 2;    //  10:9
    UINT32 reg_cvbsafe_adc_insel: 1;    //    11
    UINT32 reg_cvbsafe_adc_cksel: 1;    //    12
    UINT32 reg_cvbsafe_adc_lpf:  1;    //     13
    UINT32 reg_cvbsafe_adc_dcatt: 1;    //    14
    UINT32 reg_cvbsafe_adc_gc :  3;    //  17:15
    UINT32 reg_cvbsafe_adc_refsel: 2;    //  19:18
    UINT32 reg_cvbsafe_adc_decm: 2;    //  21:20
    UINT32 reg_cvbsafe_adc_clp:  1;    //     22
    UINT32 reg_cvbsafe_adc_iclp2: 2;    //  24:23
    UINT32 reg_cvbsafe_adc_pdbm: 1;    //     25
    UINT32 reg_cvbsafe_adc_isel: 3;    //  28:26
    UINT32 reg_cvbsafe_adc_bw :  1;    //     29
    UINT32 reg_cvbsafe_adc_dcsel: 2;    //  31:30
    };
}MIP_CTRL_CVBSAFE_MIP_ADC06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_401C    mip_adc07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvbsafe_pll_m  :  6;    //   5: 0
    UINT32 reg_cvbsafe_pll_fine_control: 3;    //  8:6
    UINT32 reg_cvbsafe_pll_accuracy: 2;    //  10:9
    UINT32 reg_cvbsafe_pll_wake_bypass: 1;    //  11
    UINT32 reg_cvbsafe_pll_sync_on: 1;    //  12
    UINT32 reg_cvbsafe_pll_icp_g: 1;    //    13
    UINT32 reg_cvbsafe_pll_nsc:  4;    //  17:14
    UINT32 reg_cvbsafe_pll_pdb:  1;    //     18
    UINT32 reg_cvbsafe_pll_cih:  4;    //  22:19
    UINT32 reg_cvbsafe_pll_npc:  6;    //  28:23
    UINT32 resvd00            :  3;    //  31:29 reserved
    };
}MIP_CTRL_CVBSAFE_MIP_ADC07_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_4020    mip_adc08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvbsafe_pll_offset: 8;    //  7:0
    UINT32 reg_cvbsafe_pll_updn_max: 7;    //  14:8
    UINT32 reg_cvbsafe_pll_out_div: 7;    //  21:15
    UINT32 reg_cvbsafe_pll_out_div2: 7;    //  28:22
    UINT32 resvd00            :  3;    //  31:29 reserved
    };
}MIP_CTRL_CVBSAFE_MIP_ADC08_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_4024    mip_adc09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvbsafe_pll_mod_freq_max: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}MIP_CTRL_CVBSAFE_MIP_ADC09_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_4028    mip_adc10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvbsafe_pll_lock_f: 1;    //    0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MIP_CTRL_CVBSAFE_MIP_ADC10_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_cvbsafe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[6];             // 0xC8A3_4000 ~ 0xC8A3_4014
    MIP_CTRL_CVBSAFE_MIP_ADC06_O26A0_T    mip_adc06;            // 0xC8A3_4018
    MIP_CTRL_CVBSAFE_MIP_ADC07_O26A0_T    mip_adc07;            // 0xC8A3_401C
    MIP_CTRL_CVBSAFE_MIP_ADC08_O26A0_T    mip_adc08;            // 0xC8A3_4020
    MIP_CTRL_CVBSAFE_MIP_ADC09_O26A0_T    mip_adc09;            // 0xC8A3_4024
    MIP_CTRL_CVBSAFE_MIP_ADC10_O26A0_T    mip_adc10;            // 0xC8A3_4028
}MIP_CTRL_CVBSAFE_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MIP_CTRL_CVBSAFE_REG_H_

/* from 'O26_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

