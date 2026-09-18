#ifndef _MIP_CTRL_ACODEC_REG_O24A0_H_
#define _MIP_CTRL_ACODEC_REG_O24A0_H_

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
    0xCC9E_3000    mip_acodec00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_ic_vcom           :  2,    //   1: 0
    reg_aud_ic_vbuf           :  2,    //   3: 2
    reg_aud_ic_bgr            :  2,    //   5: 4
    reg_aud_ft_mode           :  1,    //      6
    reg_aud_cnt_rdiv          :  1,    //      7
    reg_aud_ccont             :  2,    //   9: 8
    reg_auda_chop_freq_scf    :  2,    //  11:10
    reg_auda_chop_freq_d2s    :  2,    //  13:12
    reg_auda_chop_en          :  1,    //     14
    reg_auda_pdb_clk          :  1,    //     15
    reg_auda_ic_scfr          :  2,    //  17:16
    reg_auda_ic_scfl          :  2,    //  19:18
    reg_auda_ic_refpr         :  2,    //  21:20
    reg_auda_ic_refpl         :  2,    //  23:22
    reg_auda_ic_refr          :  2,    //  25:24
    reg_auda_ic_refl          :  2,    //  27:26
    reg_auda_ic_d2sr          :  2,    //  29:28
    reg_auda_ic_d2sl          :  2;    //  31:30
}MIP_CTRL_ACODEC_MIP_ACODEC00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_3004    mip_acodec01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auda_pdb_dac          :  1,    //      0
                              :  9,    //   9: 1 reserved
    reg_auda_vcont_refp       :  3,    //  12:10
                              :  7,    //  19:13 reserved
    reg_auda_chop_en_scf      :  1,    //     20
                              :  1,    //     21 reserved
    reg_auda_chop_en_refp     :  1,    //     22
                              :  1,    //     23 reserved
    reg_auda_chop_en_ref      :  1,    //     24
    reg_auda_chop_en_d2s      :  1,    //     25
    reg_aud_vcom_cont         :  2,    //  27:26
    reg_aud_sel_vref_out      :  1,    //     28
    reg_aud_res               :  3;    //  31:29
}MIP_CTRL_ACODEC_MIP_ACODEC01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_3008    mip_acodec02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 13,    //  12: 0 reserved
    reg_aud_pdb_bias          :  1,    //     13
                              :  6,    //  19:14 reserved
    reg_reserve_in2           :  5,    //  24:20
                              :  7;    //  31:25 reserved
}MIP_CTRL_ACODEC_MIP_ACODEC02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_300C    mip_acodec03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_pga_gcont        :  3,    //   2: 0
                              :  1,    //      3 reserved
    reg_auad_ic_quant         :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_auad_sel_pga          :  2,    //   9: 8
                              :  2,    //  11:10 reserved
    reg_auad_adc_pdb          :  1,    //     12
                              :  3,    //  15:13 reserved
    reg_auad_pga_ref_pdb      :  1,    //     16
                              :  3,    //  19:17 reserved
    reg_auad_refp_pdb         :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_auad_pga_pdb          :  1,    //     24
                              :  7;    //  31:25 reserved
}MIP_CTRL_ACODEC_MIP_ACODEC03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_3010    mip_acodec04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_ch1_sel          :  1,    //      0
    reg_auad_refp_en          :  1,    //      1
    reg_auad_en_int_pga       :  1,    //      2
    reg_auad_pga_chop_en      :  1,    //      3
    reg_auad_ic_pga           :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_auad_ic_int1          :  2,    //   9: 8
                              :  6,    //  15:10 reserved
    reg_auad_ic_ref           :  2,    //  17:16
                              :  2,    //  19:18 reserved
    reg_auad_sdm_chop_en      :  1,    //     20
                              :  3,    //  23:21 reserved
    reg_auad_ic_int2          :  2,    //  25:24
    reg_auad_ic_refp          :  2,    //  27:26
                              :  4;    //  31:28 reserved
}MIP_CTRL_ACODEC_MIP_ACODEC04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_3014    mip_acodec05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_chen_amp         :  1,    //      0
    reg_auad_en_ext           :  1,    //      1
    reg_auad_chen_cmfb        :  1,    //      2
    reg_auad_ch2_sel          :  1,    //      3
    reg_auad_sel_refp         :  2,    //   5: 4
                              :  2,    //   7: 6 reserved
    reg_reserve_in1           :  5,    //  12: 8
                              :  3,    //  15:13 reserved
    reg_auad_ch_out_enb       :  1,    //     16
    reg_auad_refn_en          :  1,    //     17
    reg_auad_en_int           :  1,    //     18
    reg_auad_refp_ch_en       :  1,    //     19
    reg_auad_div_sel_sdm      :  3,    //  22:20
                              :  1,    //     23 reserved
    reg_auad_vcont_refp       :  3,    //  26:24
                              :  1,    //     27 reserved
    reg_auad_ref_chop_en      :  1,    //     28
    reg_auad_en_ext_pga       :  1,    //     29
    reg_auad_d_inv_enb        :  1,    //     30
    reg_auad_mclk_en          :  1;    //     31
}MIP_CTRL_ACODEC_MIP_ACODEC05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_acodec Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_ACODEC_MIP_ACODEC00_O24A0_T    mip_acodec00;       // 0xCC9E_3000
    MIP_CTRL_ACODEC_MIP_ACODEC01_O24A0_T    mip_acodec01;       // 0xCC9E_3004
    MIP_CTRL_ACODEC_MIP_ACODEC02_O24A0_T    mip_acodec02;       // 0xCC9E_3008
    MIP_CTRL_ACODEC_MIP_ACODEC03_O24A0_T    mip_acodec03;       // 0xCC9E_300C
    MIP_CTRL_ACODEC_MIP_ACODEC04_O24A0_T    mip_acodec04;       // 0xCC9E_3010
    MIP_CTRL_ACODEC_MIP_ACODEC05_O24A0_T    mip_acodec05;       // 0xCC9E_3014
}MIP_CTRL_ACODEC_REG_O24A0_T;
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

#define MIP_CTRL_ACODEC_MIP_ACODEC00_O24A0_T_OFF            (BASEADDRESS+0x0000)
#define MIP_CTRL_ACODEC_MIP_ACODEC01_O24A0_T_OFF            (BASEADDRESS+0x0004)
#define MIP_CTRL_ACODEC_MIP_ACODEC02_O24A0_T_OFF            (BASEADDRESS+0x0008)
#define MIP_CTRL_ACODEC_MIP_ACODEC03_O24A0_T_OFF            (BASEADDRESS+0x000C)
#define MIP_CTRL_ACODEC_MIP_ACODEC04_O24A0_T_OFF            (BASEADDRESS+0x0010)
#define MIP_CTRL_ACODEC_MIP_ACODEC05_O24A0_T_OFF            (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xCC9E_3000    mip_acodec00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_ic_vcom    :  2;    //   1: 0
    UINT32 reg_aud_ic_vbuf    :  2;    //   3: 2
    UINT32 reg_aud_ic_bgr     :  2;    //   5: 4
    UINT32 reg_aud_ft_mode    :  1;    //      6
    UINT32 reg_aud_cnt_rdiv   :  1;    //      7
    UINT32 reg_aud_ccont      :  2;    //   9: 8
    UINT32 reg_auda_chop_freq_scf: 2;    //  11:10
    UINT32 reg_auda_chop_freq_d2s: 2;    //  13:12
    UINT32 reg_auda_chop_en   :  1;    //     14
    UINT32 reg_auda_pdb_clk   :  1;    //     15
    UINT32 reg_auda_ic_scfr   :  2;    //  17:16
    UINT32 reg_auda_ic_scfl   :  2;    //  19:18
    UINT32 reg_auda_ic_refpr  :  2;    //  21:20
    UINT32 reg_auda_ic_refpl  :  2;    //  23:22
    UINT32 reg_auda_ic_refr   :  2;    //  25:24
    UINT32 reg_auda_ic_refl   :  2;    //  27:26
    UINT32 reg_auda_ic_d2sr   :  2;    //  29:28
    UINT32 reg_auda_ic_d2sl   :  2;    //  31:30
    };
}MIP_CTRL_ACODEC_MIP_ACODEC00_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_3004    mip_acodec01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auda_pdb_dac   :  1;    //      0
    UINT32 resvd00            :  9;    //   9: 1 reserved
    UINT32 reg_auda_vcont_refp:  3;    //  12:10
    UINT32 resvd01            :  7;    //  19:13 reserved
    UINT32 reg_auda_chop_en_scf: 1;    //     20
    UINT32 resvd02            :  1;    //     21 reserved
    UINT32 reg_auda_chop_en_refp: 1;    //    22
    UINT32 resvd03            :  1;    //     23 reserved
    UINT32 reg_auda_chop_en_ref: 1;    //     24
    UINT32 reg_auda_chop_en_d2s: 1;    //     25
    UINT32 reg_aud_vcom_cont  :  2;    //  27:26
    UINT32 reg_aud_sel_vref_out: 1;    //     28
    UINT32 reg_aud_res        :  3;    //  31:29
    };
}MIP_CTRL_ACODEC_MIP_ACODEC01_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_3008    mip_acodec02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 13;    //  12: 0 reserved
    UINT32 reg_aud_pdb_bias   :  1;    //     13
    UINT32 resvd01            :  6;    //  19:14 reserved
    UINT32 reg_reserve_in2    :  5;    //  24:20
    UINT32 resvd02            :  7;    //  31:25 reserved
    };
}MIP_CTRL_ACODEC_MIP_ACODEC02_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_300C    mip_acodec03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auad_pga_gcont :  3;    //   2: 0
    UINT32 resvd00            :  1;    //      3 reserved
    UINT32 reg_auad_ic_quant  :  2;    //   5: 4
    UINT32 resvd01            :  2;    //   7: 6 reserved
    UINT32 reg_auad_sel_pga   :  2;    //   9: 8
    UINT32 resvd02            :  2;    //  11:10 reserved
    UINT32 reg_auad_adc_pdb   :  1;    //     12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_auad_pga_ref_pdb: 1;    //     16
    UINT32 resvd04            :  3;    //  19:17 reserved
    UINT32 reg_auad_refp_pdb  :  1;    //     20
    UINT32 resvd05            :  3;    //  23:21 reserved
    UINT32 reg_auad_pga_pdb   :  1;    //     24
    UINT32 resvd06            :  7;    //  31:25 reserved
    };
}MIP_CTRL_ACODEC_MIP_ACODEC03_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_3010    mip_acodec04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auad_ch1_sel   :  1;    //      0
    UINT32 reg_auad_refp_en   :  1;    //      1
    UINT32 reg_auad_en_int_pga:  1;    //      2
    UINT32 reg_auad_pga_chop_en: 1;    //      3
    UINT32 reg_auad_ic_pga    :  2;    //   5: 4
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_auad_ic_int1   :  2;    //   9: 8
    UINT32 resvd01            :  6;    //  15:10 reserved
    UINT32 reg_auad_ic_ref    :  2;    //  17:16
    UINT32 resvd02            :  2;    //  19:18 reserved
    UINT32 reg_auad_sdm_chop_en: 1;    //     20
    UINT32 resvd03            :  3;    //  23:21 reserved
    UINT32 reg_auad_ic_int2   :  2;    //  25:24
    UINT32 reg_auad_ic_refp   :  2;    //  27:26
    UINT32 resvd04            :  4;    //  31:28 reserved
    };
}MIP_CTRL_ACODEC_MIP_ACODEC04_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9E_3014    mip_acodec05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auad_chen_amp  :  1;    //      0
    UINT32 reg_auad_en_ext    :  1;    //      1
    UINT32 reg_auad_chen_cmfb :  1;    //      2
    UINT32 reg_auad_ch2_sel   :  1;    //      3
    UINT32 reg_auad_sel_refp  :  2;    //   5: 4
    UINT32 resvd00            :  2;    //   7: 6 reserved
    UINT32 reg_reserve_in1    :  5;    //  12: 8
    UINT32 resvd01            :  3;    //  15:13 reserved
    UINT32 reg_auad_ch_out_enb:  1;    //     16
    UINT32 reg_auad_refn_en   :  1;    //     17
    UINT32 reg_auad_en_int    :  1;    //     18
    UINT32 reg_auad_refp_ch_en:  1;    //     19
    UINT32 reg_auad_div_sel_sdm: 3;    //  22:20
    UINT32 resvd02            :  1;    //     23 reserved
    UINT32 reg_auad_vcont_refp:  3;    //  26:24
    UINT32 resvd03            :  1;    //     27 reserved
    UINT32 reg_auad_ref_chop_en: 1;    //     28
    UINT32 reg_auad_en_ext_pga:  1;    //     29
    UINT32 reg_auad_d_inv_enb :  1;    //     30
    UINT32 reg_auad_mclk_en   :  1;    //     31
    };
}MIP_CTRL_ACODEC_MIP_ACODEC05_O24A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_acodec Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_ACODEC_MIP_ACODEC00_O24A0_T    mip_acodec00;       // 0xCC9E_3000
    MIP_CTRL_ACODEC_MIP_ACODEC01_O24A0_T    mip_acodec01;       // 0xCC9E_3004
    MIP_CTRL_ACODEC_MIP_ACODEC02_O24A0_T    mip_acodec02;       // 0xCC9E_3008
    MIP_CTRL_ACODEC_MIP_ACODEC03_O24A0_T    mip_acodec03;       // 0xCC9E_300C
    MIP_CTRL_ACODEC_MIP_ACODEC04_O24A0_T    mip_acodec04;       // 0xCC9E_3010
    MIP_CTRL_ACODEC_MIP_ACODEC05_O24A0_T    mip_acodec05;       // 0xCC9E_3014
}MIP_CTRL_ACODEC_REG_O24A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _MIP_CTRL_ACODEC_REG_H_

/* from 'O24_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

