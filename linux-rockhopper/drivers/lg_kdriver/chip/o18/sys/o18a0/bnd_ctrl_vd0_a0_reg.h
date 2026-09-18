#ifndef _BND_CTRL_VD0_A0_REG_H_
#define _BND_CTRL_VD0_A0_REG_H_

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
    0xC9FF_8400    crg_vd000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sysclk_gate_en            :  6,    //   5: 0
    axi_soc_clk_gate_en       :  1,    //      6
    te_clk_gate_en            :  1,    //      7
    de_soc_clk_gate_en        :  1,    //      8
    vd_hevc_clk_gate_en       :  1,    //      9
    vd_mem_clk_gate_en        :  1,    //     10
    vd_axi2_clk_gate_en       :  1,    //     11
    vd_axi1_clk_gate_en       :  1,    //     12
    vd_axi0_clk_gate_en       :  1,    //     13
    vd_msvc_396_clk_gate_en   :  1,    //     14
    vd_msvc_clk_gate_en       :  1,    //     15
    vd_mcu_clk_gate_en        :  1,    //     16
    vd_apbclk_gate_en         :  1,    //     17
    vd_hevc_clk_lcu_gate_en   :  1,    //     18
    vd_hevc_clk_ed_gate_en    :  1,    //     19
                              : 12;    //  31:20 reserved
}BND_CTRL_VD0_CRG_VD000_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC9FF_8404    crg_vd001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sysclk_sel                :  6,    //   5: 0
    vd_mem_clk_sel            :  2,    //   7: 6
    vd_hevc_clk_sel           :  1,    //      8
    vd_msvc_clk_sel           :  1,    //      9
                              : 22;    //  31:10 reserved
}BND_CTRL_VD0_CRG_VD001_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC9FF_8408    crg_vd002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_sys                 :  6,    //   5: 0
    swrst_de_soc              :  1,    //      6
    swrst_axi_soc             :  1,    //      7
    swrst_te                  :  1,    //      8
    swrst_hevc                :  1,    //      9
    swrst_mem                 :  1,    //     10
    swrst_vda2                :  1,    //     11
    swrst_vda1                :  1,    //     12
    swrst_vda0                :  1,    //     13
    swrst_vd                  :  1,    //     14
    swrst_mcu                 :  1,    //     15
    swrst_apb                 :  1,    //     16
    swrst_hevc_lcu            :  1,    //     17
    swrst_hevc_ed             :  1,    //     18
                              : 13;    //  31:19 reserved
}BND_CTRL_VD0_CRG_VD002_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC9FF_840C    crg_vd003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gnrm                :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_VD0_CRG_VD003_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC9FF_8410    crg_vd004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gnrs                :  1,    //      0
    swrst_gstc                :  1,    //      1
    swrst_te1                 :  1,    //      2
    swrst_te0                 :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_VD0_CRG_VD004_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_vd0 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_VD0_CRG_VD000_O18_A0                crg_vd000                ;         // 0xC9FF_8400
BND_CTRL_VD0_CRG_VD001_O18_A0                crg_vd001                ;         // 0xC9FF_8404
BND_CTRL_VD0_CRG_VD002_O18_A0                crg_vd002                ;         // 0xC9FF_8408
BND_CTRL_VD0_CRG_VD003_O18_A0                crg_vd003                ;         // 0xC9FF_840C
BND_CTRL_VD0_CRG_VD004_O18_A0                crg_vd004                ;         // 0xC9FF_8410
} BND_CTRL_VD0_REG_O18_A0;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_VD0_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

