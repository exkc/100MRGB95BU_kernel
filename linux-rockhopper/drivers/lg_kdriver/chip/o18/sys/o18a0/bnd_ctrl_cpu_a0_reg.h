#ifndef _BND_CTRL_CPU_A0_REG_H_
#define _BND_CTRL_CPU_A0_REG_H_

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
    0xC7FF_0000    crg_peri00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sdhc_cclk_in_clk_gate_en  :  1,    //      0
    sdhc_drv_clk_gate_en      :  1,    //      1
    sdhc_sample_clk_gate_en   :  1,    //      2
    peri_50m_ci_clk_gate_en   :  1,    //      3
    peri_25m_ci_clk_gate_en   :  1,    //      4
    peri_200m_inv_clk_gate_en :  1,    //      5
    peri_400m_clk_gate_en     :  1,    //      6
    peri_528m_clk_gate_en     :  1,    //      7
    tz_apb_clk_gate_en        :  1,    //      8
    tsclk_gate_en             :  1,    //      9
    cssysclk_gate_en          :  1,    //     10
                              : 21;    //  31:11 reserved
}BND_CTRL_CPU_CRG_PERI00_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FF_0004    crg_peri01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    peri_50m_ci_clk_sel       :  1,    //      0
    peri_25m_ci_clk_sel       :  1,    //      1
    peri_200m_inv_clk_sel     :  1,    //      2
    peri_400m_clk_sel         :  1,    //      3
    peri_200m_clk_sel         :  1,    //      4
    peri_528m_clk_sel         :  1,    //      5
    tz_apb_clk_sel            :  1,    //      6
    tsclk_sel                 :  1,    //      7
    cssysclk_sel              :  1,    //      8
    sevilla_clkin_sel         :  1,    //      9
                              : 22;    //  31:10 reserved
}BND_CTRL_CPU_CRG_PERI01_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FF_0008    crg_peri02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_peri0               : 32;    //  31: 0
}BND_CTRL_CPU_CRG_PERI02_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FF_000C    crg_peri03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_peri1               : 32;    //  31: 0
}BND_CTRL_CPU_CRG_PERI03_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FF_0010    crg_peri04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_peri2               : 32;    //  31: 0
}BND_CTRL_CPU_CRG_PERI04_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FF_0014    crg_peri05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sevilla_ctr00             : 32;    //  31: 0
}BND_CTRL_CPU_CRG_PERI05_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FF_0018    crg_peri06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sevilla_ctr01             : 32;    //  31: 0
}BND_CTRL_CPU_CRG_PERI06_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FF_001C    crg_peri07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pcherr0                   :  1,    //      0
    pcherr1                   :  1,    //      1
    pcherr2                   :  1,    //      2
    pcherr3                   :  1,    //      3
                              : 28;    //   31:4 reserved
}BND_CTRL_CPU_CRG_PERI07_O18_A0;

/*-----------------------------------------------------------------------------------------
    0xC7FF_0020    crg_peri08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sevilla_bist_rm_l1        :  4,    //   3: 0
    sevilla_bist_rm_l2        :  4,    //   7: 4
    sevilla_bist_rme_l1       :  1,    //      8
    sevilla_bist_rme_l2       :  1,    //      9
                              : 22;    //  31:10 reserved
}BND_CTRL_CPU_CRG_PERI08_O18_A0;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
BND_CTRL_CPU_CRG_PERI00_O18_A0               crg_peri00               ;         // 0xC7FF_0000
BND_CTRL_CPU_CRG_PERI01_O18_A0               crg_peri01               ;         // 0xC7FF_0004
BND_CTRL_CPU_CRG_PERI02_O18_A0               crg_peri02               ;         // 0xC7FF_0008
BND_CTRL_CPU_CRG_PERI03_O18_A0               crg_peri03               ;         // 0xC7FF_000C
BND_CTRL_CPU_CRG_PERI04_O18_A0               crg_peri04               ;         // 0xC7FF_0010
BND_CTRL_CPU_CRG_PERI05_O18_A0               crg_peri05               ;         // 0xC7FF_0014
BND_CTRL_CPU_CRG_PERI06_O18_A0               crg_peri06               ;         // 0xC7FF_0018
BND_CTRL_CPU_CRG_PERI07_O18_A0               crg_peri07               ;         // 0xC7FF_001C
BND_CTRL_CPU_CRG_PERI08_O18_A0               crg_peri08               ;         // 0xC7FF_0020
} BND_CTRL_CPU_REG_O18_A0;
/* 9 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _BND_CTRL_CPU_A0_REG_H_ */

/* from 'O18_CTOP_SYN_Register_Manual_54.xlsm'  2017.6.1  KST by LGSiCRDV V2.1B*/

