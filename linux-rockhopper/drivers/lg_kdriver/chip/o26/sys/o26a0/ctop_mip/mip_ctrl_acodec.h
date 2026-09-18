#ifndef _MIP_CTRL_ACODEC_REG_O26A0_H_
#define _MIP_CTRL_ACODEC_REG_O26A0_H_

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
    0xC8A3_3000    mip_acodec00 ''
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
}MIP_CTRL_ACODEC_MIP_ACODEC00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_3004    mip_acodec01 ''
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
}MIP_CTRL_ACODEC_MIP_ACODEC01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_3008    mip_acodec02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              : 13,    //  12: 0 reserved
    reg_aud_pdb_bias          :  1,    //     13
                              :  6,    //  19:14 reserved
    reg_reserve_in1           :  5,    //  24:20
    reg_reserve_in2           :  5,    //  29:25
                              :  2;    //  31:30 reserved
}MIP_CTRL_ACODEC_MIP_ACODEC02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_300C    mip_acodec03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_auad_ic_pga           :  2,    //   1: 0
    reg_auad_ic_int1          :  2,    //   3: 2
    reg_auad_ic_ref           :  2,    //   5: 4
    reg_auad_ic_int2          :  2,    //   7: 6
    reg_auad_ic_refp          :  2,    //   9: 8
    reg_auad_ic_quant         :  2,    //  11:10
                              : 20;    //  31:12 reserved
}MIP_CTRL_ACODEC_MIP_ACODEC03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_acodec Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_ACODEC_MIP_ACODEC00_O26A0_T    mip_acodec00;       // 0xC8A3_3000
    MIP_CTRL_ACODEC_MIP_ACODEC01_O26A0_T    mip_acodec01;       // 0xC8A3_3004
    MIP_CTRL_ACODEC_MIP_ACODEC02_O26A0_T    mip_acodec02;       // 0xC8A3_3008
    MIP_CTRL_ACODEC_MIP_ACODEC03_O26A0_T    mip_acodec03;       // 0xC8A3_300C
}MIP_CTRL_ACODEC_REG_O26A0_T;
/* 4 regs */

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

#define MIP_CTRL_ACODEC_MIP_ACODEC00_O26A0_T_OFF            (BASEADDRESS+0x0000)
#define MIP_CTRL_ACODEC_MIP_ACODEC01_O26A0_T_OFF            (BASEADDRESS+0x0004)
#define MIP_CTRL_ACODEC_MIP_ACODEC02_O26A0_T_OFF            (BASEADDRESS+0x0008)
#define MIP_CTRL_ACODEC_MIP_ACODEC03_O26A0_T_OFF            (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xC8A3_3000    mip_acodec00 ''
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
}MIP_CTRL_ACODEC_MIP_ACODEC00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_3004    mip_acodec01 ''
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
}MIP_CTRL_ACODEC_MIP_ACODEC01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_3008    mip_acodec02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            : 13;    //  12: 0 reserved
    UINT32 reg_aud_pdb_bias   :  1;    //     13
    UINT32 resvd01            :  6;    //  19:14 reserved
    UINT32 reg_reserve_in1    :  5;    //  24:20
    UINT32 reg_reserve_in2    :  5;    //  29:25
    UINT32 resvd02            :  2;    //  31:30 reserved
    };
}MIP_CTRL_ACODEC_MIP_ACODEC02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC8A3_300C    mip_acodec03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_auad_ic_pga    :  2;    //   1: 0
    UINT32 reg_auad_ic_int1   :  2;    //   3: 2
    UINT32 reg_auad_ic_ref    :  2;    //   5: 4
    UINT32 reg_auad_ic_int2   :  2;    //   7: 6
    UINT32 reg_auad_ic_refp   :  2;    //   9: 8
    UINT32 reg_auad_ic_quant  :  2;    //  11:10
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MIP_CTRL_ACODEC_MIP_ACODEC03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    mip_ctrl_acodec Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MIP_CTRL_ACODEC_MIP_ACODEC00_O26A0_T    mip_acodec00;       // 0xC8A3_3000
    MIP_CTRL_ACODEC_MIP_ACODEC01_O26A0_T    mip_acodec01;       // 0xC8A3_3004
    MIP_CTRL_ACODEC_MIP_ACODEC02_O26A0_T    mip_acodec02;       // 0xC8A3_3008
    MIP_CTRL_ACODEC_MIP_ACODEC03_O26A0_T    mip_acodec03;       // 0xC8A3_300C
}MIP_CTRL_ACODEC_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MIP_CTRL_ACODEC_REG_H_

/* from 'O26_CTOP_MIP_Adaptor_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

