#ifndef _BND_CTRL_VDEC1_A0_REG_H_
#define _BND_CTRL_VDEC1_A0_REG_H_

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
    0xC9FF_0400    crg_vd100 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gstcc_soc_clk_gate_en     :  1,    //      0
    de_soc_clk_gate_en        :  1,    //      1
    vd_axi1_clk_gate_en       :  1,    //      2
    vd_axi0_clk_gate_en       :  1,    //      3
    vd_mem_clk_gate_en        :  1,    //      4
    g1_clk_gate_en            :  1,    //      5
    hevcp1_clk_gate_en        :  1,    //      6
    ed_clk_gate_en            :  1,    //      7
    te_soc_clk_gate_en        :  1,    //      8
    hevc_lcu_clk_gate_en      :  1,    //      9
                              : 22;    //  31:10 reserved
}BND_CTRL_VDEC1_CRG_VD100_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC9FF_0404    crg_vd101 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    vd_mem_clk_sel            :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_VDEC1_CRG_VD101_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC9FF_0408    crg_vd102 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gstcc_soc           :  1,    //      0
    swrst_de_soc              :  1,    //      1
    swrst_vda1                :  1,    //      2
    swrst_vda0                :  1,    //      3
    swrst_mem                 :  1,    //      4
    swrst_g1                  :  1,    //      5
    swrst_dec                 :  1,    //      6
    swrst_hevcp1              :  1,    //      7
    swrst_ed                  :  1,    //      8
    swrst_te_soc              :  1,    //      9
    swrst_hevc_lcu            :  1,    //     10
                              : 21;    //  31:11 reserved
}BND_CTRL_VDEC1_CRG_VD102_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC9FF_040C    crg_vd103 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gnrm                :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_VDEC1_CRG_VD103_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC9FF_0410    crg_vd104 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gnrs                :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_VDEC1_CRG_VD104_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_vdec1 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_VDEC1_CRG_VD100_O18_A0              crg_vd100                ;         // 0xC9FF_0400
BND_CTRL_VDEC1_CRG_VD101_O18_A0              crg_vd101                ;         // 0xC9FF_0404
BND_CTRL_VDEC1_CRG_VD102_O18_A0              crg_vd102                ;         // 0xC9FF_0408
BND_CTRL_VDEC1_CRG_VD103_O18_A0              crg_vd103                ;         // 0xC9FF_040C
BND_CTRL_VDEC1_CRG_VD104_O18_A0              crg_vd104                ;         // 0xC9FF_0410
} BND_CTRL_VDEC1_REG_O18_A0;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_VDEC1_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

