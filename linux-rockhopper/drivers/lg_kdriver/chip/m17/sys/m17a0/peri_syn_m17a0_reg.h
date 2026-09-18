#ifndef _PERI_SYN_M17A0_REG_H_
#define _PERI_SYN_M17A0_REG_H_

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
    0xC923_0000    crg_cpuperi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cssysclk_gate_en          :  1,    //      0
    tsclk_gate_en             :  1,    //      1
    tz_apb_clk_gate_en        :  1,    //      2
    cpu_bus_clk_gate_en       :  1,    //      3
    spi_core_clk_gate_en      :  1,    //      4
    peri_100m_clk_gate_en     :  1,    //      5
    peri_400m_clk_gate_en     :  1,    //      6
    peri_200m_inv_clk_gate_en :  1,    //      7
    peri_25m_ci_clk_gate_en   :  1,    //      8
    peri_50m_ci_clk_gate_en   :  1,    //      9
    zram_clk_gate_en          :  1,    //     10
    sdhc_drv_clk_gate_en      :  1,    //     11
    sdhc_sample_clk_gate_en   :  1,    //     12
    sdhc_cclk_in_clk_gate_en  :  1,    //     13
                              : 18;    //  31:14 reserved
}PERI_SYN_CRG_CPUPERI00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0004    crg_cpuperi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cssysclk_sel              :  1,    //      0
    tsclk_sel                 :  1,    //      1
    tz_apb_clk_sel            :  1,    //      2
    cpu_bus_clk_sel           :  1,    //      3
    spi_core_clk_sel          :  1,    //      4
    peri_100m_clk_sel         :  1,    //      5
    peri_200m_clk_sel         :  1,    //      6
    peri_400m_clk_sel         :  1,    //      7
    peri_200m_inv_clk_sel     :  1,    //      8
    peri_25m_ci_clk_sel       :  1,    //      9
    peri_50m_ci_clk_sel       :  1,    //     10
    zram_clk_sel              :  2,    //  12:11
    sanpietro_clkin_sel       :  1,    //     13
                              : 18;    //  31:14 reserved
}PERI_SYN_CRG_CPUPERI01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0008    crg_cpuperi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_bus                 : 14,    //  13: 0
                              : 18;    //  31:14 reserved
}PERI_SYN_CRG_CPUPERI02_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_000C    crg_cpuperi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_ahb                 : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}PERI_SYN_CRG_CPUPERI03_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0010    crg_cpuperi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_apb0                : 11,    //  10: 0
                              : 21;    //  31:11 reserved
}PERI_SYN_CRG_CPUPERI04_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0014    crg_cpuperi05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_apb1                : 22,    //  21: 0
                              : 10;    //  31:22 reserved
}PERI_SYN_CRG_CPUPERI05_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0018    crg_cpuperi06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_spi_core            :  1,    //      0
    swrst_cpu_bus             :  1,    //      1
    swrst_tz_apb              :  1,    //      2
    swrst_ts                  :  1,    //      3
    swrst_cnt                 :  1,    //      4
    swrst_cssys               :  1,    //      5
    swrst_zram                :  1,    //      6
    swrst_sdhc_cclk_in        :  1,    //      7
    swrst_sdhc_cclk_drv       :  1,    //      8
    swrst_sdhc_cclk_sample    :  1,    //      9
                              : 22;    //  31:10 reserved
}PERI_SYN_CRG_CPUPERI06_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0020    sanpietro_ctr00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sanpietro_ctr00           : 32;    //  31: 0
}PERI_SYN_SANPIETRO_CTR00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0024    sanpietro_ctr01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    sanpietro_ctr01           : 32;    //  31: 0
}PERI_SYN_SANPIETRO_CTR01_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0028    syn_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00                     : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}PERI_SYN_SYN_CPU00_M17_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_002C    syn_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    ctr00_ro                  : 16,    //  15: 0
                              : 16;    //  31:16 reserved
}PERI_SYN_SYN_CPU01_M17_A0;

/*-----------------------------------------------------------------------------------------
    peri_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
PERI_SYN_CRG_CPUPERI00_M17_A0                crg_cpuperi00            ;         // 0xC923_0000
PERI_SYN_CRG_CPUPERI01_M17_A0                crg_cpuperi01            ;         // 0xC923_0004
PERI_SYN_CRG_CPUPERI02_M17_A0                crg_cpuperi02            ;         // 0xC923_0008
PERI_SYN_CRG_CPUPERI03_M17_A0                crg_cpuperi03            ;         // 0xC923_000C
PERI_SYN_CRG_CPUPERI04_M17_A0                crg_cpuperi04            ;         // 0xC923_0010
PERI_SYN_CRG_CPUPERI05_M17_A0                crg_cpuperi05            ;         // 0xC923_0014
PERI_SYN_CRG_CPUPERI06_M17_A0                crg_cpuperi06            ;         // 0xC923_0018
UINT32                                                 _rsvd_00[   1] ;         // 0xC923_001C
PERI_SYN_SANPIETRO_CTR00_M17_A0              sanpietro_ctr00          ;         // 0xC923_0020
PERI_SYN_SANPIETRO_CTR01_M17_A0              sanpietro_ctr01          ;         // 0xC923_0024
PERI_SYN_SYN_CPU00_M17_A0                    syn_cpu00                ;         // 0xC923_0028
PERI_SYN_SYN_CPU01_M17_A0                    syn_cpu01                ;         // 0xC923_002C
} PERI_SYN_REG_M17_A0;
/* 11 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _PERI_SYN_M17A0_REG_H_ */

/* from 'M16PP_CTOP_SYN_Register_Manual_52.xlsm'  2017.6.20  KST by LGSiCRDV V2.1B*/

