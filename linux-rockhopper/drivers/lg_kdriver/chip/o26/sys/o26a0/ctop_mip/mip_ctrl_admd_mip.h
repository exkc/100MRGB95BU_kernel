#ifndef _MIP_CTRL_ADMD_MIP_REG_O26A0_H_
#define _MIP_CTRL_ADMD_MIP_REG_O26A0_H_

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
    0xC8A3_5000    mip_adc00 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_5004    mip_adc01 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_5008    mip_adc02 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_500C    mip_adc03 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_5010    mip_adc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_admd_apll_odpre       :  6,    //   5: 0
                              :  2,    //   7: 6 reserved
    reg_admd_apll_dto_en      :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_admd_apll_dto_divsel  :  1,    //     12
                              : 19;    //  31:13 reserved
}MIP_CTRL_ADMD_MIP_MIP_ADC04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_5014    mip_adc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pl_md_drv_pdb         :  1,    //      0
    reg_pl_md_drv_div2_enb    :  1,    //      1
    reg_admd_dpll_dto_en      :  1,    //      2
    reg_admd_dpll_dto_divsel  :  1,    //      3
                              : 28;    //   31:4 reserved
}MIP_CTRL_ADMD_MIP_MIP_ADC05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_admd_mip Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_ADMD_MIP_MIP_ADC00_O26A0_T    mip_adc00;           // 0xC8A3_5000
    MIP_CTRL_ADMD_MIP_MIP_ADC01_O26A0_T    mip_adc01;           // 0xC8A3_5004
    MIP_CTRL_ADMD_MIP_MIP_ADC02_O26A0_T    mip_adc02;           // 0xC8A3_5008
    MIP_CTRL_ADMD_MIP_MIP_ADC03_O26A0_T    mip_adc03;           // 0xC8A3_500C
    MIP_CTRL_ADMD_MIP_MIP_ADC04_O26A0_T    mip_adc04;           // 0xC8A3_5010
    MIP_CTRL_ADMD_MIP_MIP_ADC05_O26A0_T    mip_adc05;           // 0xC8A3_5014
}MIP_CTRL_ADMD_MIP_REG_O26A0_T;
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

#define MIP_CTRL_ADMD_MIP_MIP_ADC00_O26A0_T_OFF             (BASEADDRESS+0x0000)
#define MIP_CTRL_ADMD_MIP_MIP_ADC01_O26A0_T_OFF             (BASEADDRESS+0x0004)
#define MIP_CTRL_ADMD_MIP_MIP_ADC02_O26A0_T_OFF             (BASEADDRESS+0x0008)
#define MIP_CTRL_ADMD_MIP_MIP_ADC03_O26A0_T_OFF             (BASEADDRESS+0x000C)
#define MIP_CTRL_ADMD_MIP_MIP_ADC04_O26A0_T_OFF             (BASEADDRESS+0x0010)
#define MIP_CTRL_ADMD_MIP_MIP_ADC05_O26A0_T_OFF             (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xC8A3_5000    mip_adc00 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_5004    mip_adc01 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_5008    mip_adc02 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_500C    mip_adc03 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_5010    mip_adc04 ''
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
}MIP_CTRL_ADMD_MIP_MIP_ADC04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_5014    mip_adc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pl_md_drv_pdb  :  1;    //      0
    UINT32 reg_pl_md_drv_div2_enb: 1;    //    1
    UINT32 reg_admd_dpll_dto_en: 1;    //      2
    UINT32 reg_admd_dpll_dto_divsel: 1;    //  3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MIP_CTRL_ADMD_MIP_MIP_ADC05_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_admd_mip Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_ADMD_MIP_MIP_ADC00_O26A0_T    mip_adc00;           // 0xC8A3_5000
    MIP_CTRL_ADMD_MIP_MIP_ADC01_O26A0_T    mip_adc01;           // 0xC8A3_5004
    MIP_CTRL_ADMD_MIP_MIP_ADC02_O26A0_T    mip_adc02;           // 0xC8A3_5008
    MIP_CTRL_ADMD_MIP_MIP_ADC03_O26A0_T    mip_adc03;           // 0xC8A3_500C
    MIP_CTRL_ADMD_MIP_MIP_ADC04_O26A0_T    mip_adc04;           // 0xC8A3_5010
    MIP_CTRL_ADMD_MIP_MIP_ADC05_O26A0_T    mip_adc05;           // 0xC8A3_5014
}MIP_CTRL_ADMD_MIP_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MIP_CTRL_ADMD_MIP_REG_H_

/* from 'O26_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

