#ifndef _BND_CTRL_CCO_A0_REG_H_
#define _BND_CTRL_CCO_A0_REG_H_

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
    0xC910_F000    crg_cco00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    axi_soc_clk_gate_en       :  1,    //      0
    sosd_clk_gate_en          :  1,    //      1
    disp_dsc_clk_gate_en      :  1,    //      2
    disp_clk_gate_en          :  1,    //      3
    det_clk_gate_en           :  1,    //      4
    core_clk_gate_en          :  1,    //      5
    disp_osd_clk_gate_en      :  1,    //      6
                              : 25;    //   31:7 reserved
}BND_CTRL_CCO_CRG_CCO00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC910_F004    crg_cco01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sosd_clk_sel              :  3,    //   2: 0
    disp_dsc_clk_sel          :  3,    //   5: 3
    disp_clk_sel              :  3,    //   8: 6
    disp_osd_clk_sel          :  3,    //  11: 9
                              : 20;    //  31:12 reserved
}BND_CTRL_CCO_CRG_CCO01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC910_F008    crg_cco02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_axi_soc             :  1,    //      0
    swrst_disp_dsc            :  1,    //      1
    swrst_disp                :  1,    //      2
    swrst_det                 :  1,    //      3
    swrst_sosd                :  1,    //      4
    swrst_fms                 :  1,    //      5
    swrst_axi                 :  1,    //      6
    swrst_de                  :  1,    //      7
    swrst_apb                 :  1,    //      8
    swrst_disp_osd            :  1,    //      9
                              : 22;    //  31:10 reserved
}BND_CTRL_CCO_CRG_CCO02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC910_F00C    crg_cco03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pqe_cco_ctrl          : 32;    //  31: 0
}BND_CTRL_CCO_CRG_CCO03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC910_F010    crg_cco04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cpu_cco_detour_en         :  1,    //      0
    vid_2x1_mux_sel           :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_CCO_CRG_CCO04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC910_F014    crg_cco05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_oled                :  1,    //      0
    swrst_vsd_cco_vid         :  1,    //      1
    stb_swrst                 :  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_CCO_CRG_CCO05_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_cco Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_CCO_CRG_CCO00_O18_A0                crg_cco00                ;         // 0xC910_F000
BND_CTRL_CCO_CRG_CCO01_O18_A0                crg_cco01                ;         // 0xC910_F004
BND_CTRL_CCO_CRG_CCO02_O18_A0                crg_cco02                ;         // 0xC910_F008
BND_CTRL_CCO_CRG_CCO03_O18_A0                crg_cco03                ;         // 0xC910_F00C
BND_CTRL_CCO_CRG_CCO04_O18_A0                crg_cco04                ;         // 0xC910_F010
BND_CTRL_CCO_CRG_CCO05_O18_A0                crg_cco05                ;         // 0xC910_F014
} BND_CTRL_CCO_REG_O18_A0;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_CCO_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

