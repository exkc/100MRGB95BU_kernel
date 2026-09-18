#ifndef _MIP_ADC_CTRL_BMC_M23A0_REG_H_
#define _MIP_ADC_CTRL_BMC_M23A0_REG_H_

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
    0xC615_5000    mip_adc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  5,    //   4: 0 reserved
    reg_admd_t_sel_clkinv     :  1,    //      5
    reg_admd_i_pdb            :  1,    //      6
    reg_admd_a_sel_sif        :  1,    //      7
    reg_admd_a_adc_icon       :  3,    //  10: 8
    reg_admd_apll_icp         :  4,    //  14:11
                              :  5,    //  19:15 reserved
    reg_admd_apll_autofreq    :  1,    //     20
    reg_admd_a_adc_refsel     :  2,    //  22:21
    reg_admd_apll_icp_g       :  1,    //     23
    reg_admd_a_pdb            :  1,    //     24
    reg_admd_apll_outsel      :  1,    //     25
    reg_admd_a_bias_pdb       :  1,    //     26
    reg_admd_apll_lpf_on      :  1,    //     27
    reg_admd_a_sel_clkinv     :  1,    //     28
    reg_admd_apll_frequp      :  1,    //     29
    reg_admd_a_decm           :  2;    //  31:30
}MIP_ADC_CTRL_BMC_MIP_ADC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5004    mip_adc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_admd_apll_insel       :  1,    //      1
    reg_admd_apll_cken        :  3,    //   4: 2
    reg_admd_dpll_wakebypass  :  1,    //      5
    reg_admd_dpll_lpf_on      :  1,    //      6
    reg_admd_t_pdb            :  1,    //      7
    reg_admd_i_decm           :  2,    //   9: 8
    reg_admd_apll_lockf       :  1,    //     10
    reg_admd_apll_wakebypass  :  1,    //     11
    reg_admd_dpll_od_en       :  1,    //     12
    reg_admd_dpll_frequp      :  1,    //     13
    reg_admd_q_pdb            :  1,    //     14
    reg_admd_adc_icon         :  3,    //  17:15
    reg_admd_dpll_lockc       :  1,    //     18
    reg_admd_apll_od_en       :  1,    //     19
    reg_admd_dpll_odpre       :  6,    //  25:20
    reg_admd_dpll_m           :  6;    //  31:26
}MIP_ADC_CTRL_BMC_MIP_ADC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5008    mip_adc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_admd_dpll_autofreq    :  1,    //      1
    reg_admd_i_sel_clkinv     :  1,    //      2
    reg_admd_apll_odpost      :  6,    //   8: 3
    reg_admd_apll_divint      :  9,    //  17: 9
    reg_admd_dpll_syncon      :  1,    //     18
    reg_admd_dpll_icp_g       :  1,    //     19
    reg_admd_t_decm           :  2,    //  21:20
    reg_admd_bias_pdb         :  1,    //     22
    reg_admd_apll_lockc       :  1,    //     23
    reg_admd_dpll_insel       :  1,    //     24
    reg_admd_apll_syncon      :  1,    //     25
    reg_admd_dpll_cken        :  3,    //  28:26
    reg_admd_dpll_outsel      :  1,    //     29
    reg_admd_q_decm           :  2;    //  31:30
}MIP_ADC_CTRL_BMC_MIP_ADC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_500C    mip_adc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_admd_apll_m           :  6,    //   6: 1
    reg_admd_dpll_pdb         :  1,    //      7
    reg_admd_dpll_icp         :  4,    //  11: 8
    reg_admd_q_sel_clkinv     :  1,    //     12
    reg_admd_adc_refsel       :  2,    //  14:13
    reg_admd_dpll_lockf       :  1,    //     15
    reg_admd_apll_pdb         :  1,    //     16
    reg_admd_dpll_odpost      :  6,    //  22:17
    reg_admd_dpll_divint      :  9;    //  31:23
}MIP_ADC_CTRL_BMC_MIP_ADC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5010    mip_adc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_admd_apll_odpre       :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_admd_apll_dto_en      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_admd_apll_dto_divsel  :  1,    //     12
                              : 19;    //  31:13 reserved
}MIP_ADC_CTRL_BMC_MIP_ADC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5014    mip_adc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_refpll_cpll_pdb       :  1,    //      0
    reg_refpll_regpdb         :  1,    //      1
    reg_refpll_pdb            :  1,    //      2
    reg_cvbsafe_cvbs_pdbm     :  1,    //      3
    reg_cvbsafe_cvbs_reg_pdb  :  1,    //      4
    reg_cvbsafe_cvbs_pdb      :  1,    //      5
                              : 26;    //   31:6 reserved
}MIP_ADC_CTRL_BMC_MIP_ADC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5018    mip_adc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvbsafe_cvbs_adcisel_bs2: 2,    //  1: 0
    reg_cvbsafe_cvbs_dcatt    :  1,    //      2
    reg_cvbsafe_cvbs_cmlfsel  :  3,    //   5: 3
    reg_cvbsafe_cvbs_isel     :  3,    //   8: 6
                              :  3,    //  11: 9 reserved
    reg_cvbsafe_cvbs_refsel   :  2,    //  13:12
    reg_refpll_cvbs_lock      :  2,    //  15:14
    reg_cvbsafe_cvbs_decm     :  2,    //  17:16
    reg_refpll_nsc            :  4,    //  21:18
    reg_cvbsafe_cvbs_clp      :  1,    //     22
    reg_cvbsafe_cvbs_iclp2    :  2,    //  24:23
    reg_cvbsafe_cvbs_adcisel_bs1: 2,    //  26:25
    reg_cvbsafe_cvbs_bw       :  1,    //     27
    reg_cvbsafe_cvbs_dcsel    :  2,    //  29:28
                              :  2;    //  31:30 reserved
}MIP_ADC_CTRL_BMC_MIP_ADC06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_501C    mip_adc07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_refpll_icpcon         :  5,    //   4: 0
    reg_cvbsafe_cvbs_regsel   :  2,    //   6: 5
    reg_cvbsafe_cvbs_iclp     :  2,    //   8: 7
    reg_cvbsafe_cvbs_shield_on:  2,    //  10: 9
    reg_cvbsafe_cvbs_insel    :  1,    //     11
    reg_cvbsafe_cvbs_adcisel_vref_bs: 2,    //  13:12
    reg_cvbsafe_cvbs_cksel    :  1,    //     14
    reg_cvbsafe_cvbs_adcisel_bs3: 2,    //  16:15
    reg_refpll_npc            :  5,    //  21:17
    reg_refpll_lpfr_dis       :  1,    //     22
    reg_refpll_ref_vcon       :  1,    //     23
    reg_refpll_ref_lock_ctl   :  2,    //  25:24
    reg_refpll_div10_sel      :  1,    //     26
    reg_cvbsafe_cvbs_lpf      :  1,    //     27
    reg_cvbsafe_cvbs_ibuf     :  3,    //  30:28
                              :  1;    //  31:31 reserved
}MIP_ADC_CTRL_BMC_MIP_ADC07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mip_adc_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_ADC_CTRL_BMC_MIP_ADC00_M23A0_T    mip_adc00;            // 0xC615_5000
    MIP_ADC_CTRL_BMC_MIP_ADC01_M23A0_T    mip_adc01;            // 0xC615_5004
    MIP_ADC_CTRL_BMC_MIP_ADC02_M23A0_T    mip_adc02;            // 0xC615_5008
    MIP_ADC_CTRL_BMC_MIP_ADC03_M23A0_T    mip_adc03;            // 0xC615_500C
    MIP_ADC_CTRL_BMC_MIP_ADC04_M23A0_T    mip_adc04;            // 0xC615_5010
    MIP_ADC_CTRL_BMC_MIP_ADC05_M23A0_T    mip_adc05;            // 0xC615_5014
    MIP_ADC_CTRL_BMC_MIP_ADC06_M23A0_T    mip_adc06;            // 0xC615_5018
    MIP_ADC_CTRL_BMC_MIP_ADC07_M23A0_T    mip_adc07;            // 0xC615_501C
}MIP_ADC_CTRL_BMC_REG_M23A0_T;
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

#define MIP_ADC_CTRL_BMC_MIP_ADC00_M23A0_T_OFF              (BASEADDRESS+0x0000)
#define MIP_ADC_CTRL_BMC_MIP_ADC01_M23A0_T_OFF              (BASEADDRESS+0x0004)
#define MIP_ADC_CTRL_BMC_MIP_ADC02_M23A0_T_OFF              (BASEADDRESS+0x0008)
#define MIP_ADC_CTRL_BMC_MIP_ADC03_M23A0_T_OFF              (BASEADDRESS+0x000C)
#define MIP_ADC_CTRL_BMC_MIP_ADC04_M23A0_T_OFF              (BASEADDRESS+0x0010)
#define MIP_ADC_CTRL_BMC_MIP_ADC05_M23A0_T_OFF              (BASEADDRESS+0x0014)
#define MIP_ADC_CTRL_BMC_MIP_ADC06_M23A0_T_OFF              (BASEADDRESS+0x0018)
#define MIP_ADC_CTRL_BMC_MIP_ADC07_M23A0_T_OFF              (BASEADDRESS+0x001C)

/*-----------------------------------------------------------------------------------------
    0xC615_5000    mip_adc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  5;    //   4: 0 reserved
    UINT32 reg_admd_t_sel_clkinv: 1;    //     5
    UINT32 reg_admd_i_pdb     :  1;    //      6
    UINT32 reg_admd_a_sel_sif :  1;    //      7
    UINT32 reg_admd_a_adc_icon:  3;    //  10: 8
    UINT32 reg_admd_apll_icp  :  4;    //  14:11
    UINT32 resvd01            :  5;    //  19:15 reserved
    UINT32 reg_admd_apll_autofreq: 1;    //   20
    UINT32 reg_admd_a_adc_refsel: 2;    //  22:21
    UINT32 reg_admd_apll_icp_g:  1;    //     23
    UINT32 reg_admd_a_pdb     :  1;    //     24
    UINT32 reg_admd_apll_outsel: 1;    //     25
    UINT32 reg_admd_a_bias_pdb:  1;    //     26
    UINT32 reg_admd_apll_lpf_on: 1;    //     27
    UINT32 reg_admd_a_sel_clkinv: 1;    //    28
    UINT32 reg_admd_apll_frequp: 1;    //     29
    UINT32 reg_admd_a_decm    :  2;    //  31:30
    };
}MIP_ADC_CTRL_BMC_MIP_ADC00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5004    mip_adc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_admd_apll_insel:  1;    //      1
    UINT32 reg_admd_apll_cken :  3;    //   4: 2
    UINT32 reg_admd_dpll_wakebypass: 1;    //  5
    UINT32 reg_admd_dpll_lpf_on: 1;    //      6
    UINT32 reg_admd_t_pdb     :  1;    //      7
    UINT32 reg_admd_i_decm    :  2;    //   9: 8
    UINT32 reg_admd_apll_lockf:  1;    //     10
    UINT32 reg_admd_apll_wakebypass: 1;    //  11
    UINT32 reg_admd_dpll_od_en:  1;    //     12
    UINT32 reg_admd_dpll_frequp: 1;    //     13
    UINT32 reg_admd_q_pdb     :  1;    //     14
    UINT32 reg_admd_adc_icon  :  3;    //  17:15
    UINT32 reg_admd_dpll_lockc:  1;    //     18
    UINT32 reg_admd_apll_od_en:  1;    //     19
    UINT32 reg_admd_dpll_odpre:  6;    //  25:20
    UINT32 reg_admd_dpll_m    :  6;    //  31:26
    };
}MIP_ADC_CTRL_BMC_MIP_ADC01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5008    mip_adc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_admd_dpll_autofreq: 1;    //    1
    UINT32 reg_admd_i_sel_clkinv: 1;    //     2
    UINT32 reg_admd_apll_odpost: 6;    //   8: 3
    UINT32 reg_admd_apll_divint: 9;    //  17: 9
    UINT32 reg_admd_dpll_syncon: 1;    //     18
    UINT32 reg_admd_dpll_icp_g:  1;    //     19
    UINT32 reg_admd_t_decm    :  2;    //  21:20
    UINT32 reg_admd_bias_pdb  :  1;    //     22
    UINT32 reg_admd_apll_lockc:  1;    //     23
    UINT32 reg_admd_dpll_insel:  1;    //     24
    UINT32 reg_admd_apll_syncon: 1;    //     25
    UINT32 reg_admd_dpll_cken :  3;    //  28:26
    UINT32 reg_admd_dpll_outsel: 1;    //     29
    UINT32 reg_admd_q_decm    :  2;    //  31:30
    };
}MIP_ADC_CTRL_BMC_MIP_ADC02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_500C    mip_adc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_admd_apll_m    :  6;    //   6: 1
    UINT32 reg_admd_dpll_pdb  :  1;    //      7
    UINT32 reg_admd_dpll_icp  :  4;    //  11: 8
    UINT32 reg_admd_q_sel_clkinv: 1;    //    12
    UINT32 reg_admd_adc_refsel:  2;    //  14:13
    UINT32 reg_admd_dpll_lockf:  1;    //     15
    UINT32 reg_admd_apll_pdb  :  1;    //     16
    UINT32 reg_admd_dpll_odpost: 6;    //  22:17
    UINT32 reg_admd_dpll_divint: 9;    //  31:23
    };
}MIP_ADC_CTRL_BMC_MIP_ADC03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5010    mip_adc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_admd_apll_odpre:  6;    //   5: 0
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_admd_apll_dto_en: 1;    //      8
    UINT32 resvd01            :  3;    //  11: 9 reserved
    UINT32 reg_admd_apll_dto_divsel: 1;    //  12
    UINT32 resvd02            : 19;    //  31:13 reserved
    };
}MIP_ADC_CTRL_BMC_MIP_ADC04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5014    mip_adc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_refpll_cpll_pdb:  1;    //      0
    UINT32 reg_refpll_regpdb  :  1;    //      1
    UINT32 reg_refpll_pdb     :  1;    //      2
    UINT32 reg_cvbsafe_cvbs_pdbm: 1;    //     3
    UINT32 reg_cvbsafe_cvbs_reg_pdb: 1;    //  4
    UINT32 reg_cvbsafe_cvbs_pdb: 1;    //      5
    UINT32 resvd00            : 26;    //   31:6 reserved
    };
}MIP_ADC_CTRL_BMC_MIP_ADC05_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_5018    mip_adc06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvbsafe_cvbs_adcisel_bs2: 2;    //  1:0
    UINT32 reg_cvbsafe_cvbs_dcatt: 1;    //    2
    UINT32 reg_cvbsafe_cvbs_cmlfsel: 3;    //  5:3
    UINT32 reg_cvbsafe_cvbs_isel: 3;    //  8: 6
    UINT32 resvd00            :  3;    //  11: 9 reserved
    UINT32 reg_cvbsafe_cvbs_refsel: 2;    //  13:12
    UINT32 reg_refpll_cvbs_lock: 2;    //  15:14
    UINT32 reg_cvbsafe_cvbs_decm: 2;    //  17:16
    UINT32 reg_refpll_nsc     :  4;    //  21:18
    UINT32 reg_cvbsafe_cvbs_clp: 1;    //     22
    UINT32 reg_cvbsafe_cvbs_iclp2: 2;    //  24:23
    UINT32 reg_cvbsafe_cvbs_adcisel_bs1: 2;    //  26:25
    UINT32 reg_cvbsafe_cvbs_bw:  1;    //     27
    UINT32 reg_cvbsafe_cvbs_dcsel: 2;    //  29:28
    UINT32 resvd01            :  2;    //  31:30 reserved
    };
}MIP_ADC_CTRL_BMC_MIP_ADC06_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xC615_501C    mip_adc07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_refpll_icpcon  :  5;    //   4: 0
    UINT32 reg_cvbsafe_cvbs_regsel: 2;    //  6:5
    UINT32 reg_cvbsafe_cvbs_iclp: 2;    //  8: 7
    UINT32 reg_cvbsafe_cvbs_shield_on: 2;    //  10:9
    UINT32 reg_cvbsafe_cvbs_insel: 1;    //   11
    UINT32 reg_cvbsafe_cvbs_adcisel_vref_bs: 2;    //  13:12
    UINT32 reg_cvbsafe_cvbs_cksel: 1;    //   14
    UINT32 reg_cvbsafe_cvbs_adcisel_bs3: 2;    //  16:15
    UINT32 reg_refpll_npc     :  5;    //  21:17
    UINT32 reg_refpll_lpfr_dis:  1;    //     22
    UINT32 reg_refpll_ref_vcon:  1;    //     23
    UINT32 reg_refpll_ref_lock_ctl: 2;    //  25:24
    UINT32 reg_refpll_div10_sel: 1;    //     26
    UINT32 reg_cvbsafe_cvbs_lpf: 1;    //     27
    UINT32 reg_cvbsafe_cvbs_ibuf: 3;    //  30:28
    UINT32 resvd00            :  1;    //  31:31 reserved
    };
}MIP_ADC_CTRL_BMC_MIP_ADC07_M23A0_T;

/*-----------------------------------------------------------------------------------------
    mip_adc_ctrl_bmc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_ADC_CTRL_BMC_MIP_ADC00_M23A0_T    mip_adc00;            // 0xC615_5000
    MIP_ADC_CTRL_BMC_MIP_ADC01_M23A0_T    mip_adc01;            // 0xC615_5004
    MIP_ADC_CTRL_BMC_MIP_ADC02_M23A0_T    mip_adc02;            // 0xC615_5008
    MIP_ADC_CTRL_BMC_MIP_ADC03_M23A0_T    mip_adc03;            // 0xC615_500C
    MIP_ADC_CTRL_BMC_MIP_ADC04_M23A0_T    mip_adc04;            // 0xC615_5010
    MIP_ADC_CTRL_BMC_MIP_ADC05_M23A0_T    mip_adc05;            // 0xC615_5014
    MIP_ADC_CTRL_BMC_MIP_ADC06_M23A0_T    mip_adc06;            // 0xC615_5018
    MIP_ADC_CTRL_BMC_MIP_ADC07_M23A0_T    mip_adc07;            // 0xC615_501C
}MIP_ADC_CTRL_BMC_REG_M23A0_T;
/* 8 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

