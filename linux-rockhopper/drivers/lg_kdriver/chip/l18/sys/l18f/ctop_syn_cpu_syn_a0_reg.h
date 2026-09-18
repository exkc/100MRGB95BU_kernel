#ifndef _CTOP_SYN_CPU_SYN_A0_REG_H_
#define _CTOP_SYN_CPU_SYN_A0_REG_H_

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
    0xC923_0000    crg_cpu00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    gfx_pclk_gate_en          :  1,    //      0
    gfx_cclk_gate_en          :  1,    //      1
                              : 30;    //   31:2 reserved
}SYN_CPU_SYN_CRG_CPU00_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0004    crg_cpu01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gfxp                :  1,    //      0
    swrst_gfxc                :  1,    //      1
                              : 30;    //   31:2 reserved
}SYN_CPU_SYN_CRG_CPU01_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0008    crg_cpu02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pclk_gate_en              :  1,    //      0
    mii_tx_clk_gate_en        :  1,    //      1
    mii_rx_clk_gate_en        :  1,    //      2
    femac_axi_clk_gate_en     :  1,    //      3
                              : 26,    //  29: 4 reserved
    ephy_tx_clk_inv_sel       :  1,    //     30
    ephy_rx_clk_inv_sel       :  1;    //     31
}SYN_CPU_SYN_CRG_CPU02_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_000C    crg_cpu03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_gem_apb             :  1,    //      0
    swrst_gem_ctrl            :  1,    //      1
    swrst_gem_ephy            :  1,    //      2
    swrst_gem_axi             :  1,    //      3
                              : 28;    //   31:4 reserved
}SYN_CPU_SYN_CRG_CPU03_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0010    crg_cpu04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    hsusb0_phy_core_clk_gate_en: 1,    //      0
    hsusb0_phy_clock_o_gate_en:  1,    //      1
    hsusb0_freeclk_o_gate_en  :  1,    //      2
    hsusb0_clk48mohci_o_gate_en: 1,    //      3
    hsusb0_clk12mohci_o_gate_en: 1,    //      4
    bus_clk_o_gate_en         :  1,    //      5
                              : 26;    //   31:6 reserved
}SYN_CPU_SYN_CRG_CPU04_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0014    crg_cpu05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_hsusb0_utmi         :  1,    //      0
    swrst_hsusb0_phy_por      :  1,    //      1
    swrst_hsusb0_core         :  1,    //      2
    swrst_hsusb0_bus          :  1,    //      3
    swrst_bus                 :  1,    //      4
                              : 27;    //   31:5 reserved
}SYN_CPU_SYN_CRG_CPU05_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0018    crg_cpu06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    tsclk_sel                 :  1,    //      0
    cssyclk_sel               :  1,    //      1
    cpu_clk_tzapb_sel         :  1,    //      2
    cpu_clk_spi_sel           :  1,    //      3
    cpu_clk_528m_sel          :  1,    //      4
    cpu_clk_50m_sel           :  1,    //      5
    cpu_clk_25m_sel           :  1,    //      6
    cpu_clk_200m_sel          :  1,    //      7
    cpu_clk_100m_sel          :  1,    //      8
    cpu_clk_200m_inv_sel      :  1,    //      9
    clken_sel                 :  1,    //     10
    sel_clkenout              :  1,    //     11
                              : 20;    //  31:12 reserved
}SYN_CPU_SYN_CRG_CPU06_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_001C    crg_cpu07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    cpu_clk_sc_gate_en        :  1,    //      0
    tsclk_gate_en             :  1,    //      1
    cssyclk_gate_en           :  1,    //      2
    cpu_clk_tzapb_gate_en     :  1,    //      3
    cpu_clk_spi_gate_en       :  1,    //      4
    cpu_clk_528m_gate_en      :  1,    //      5
    cpu_clk_50m_gate_en       :  1,    //      6
    cpu_clk_25m_gate_en       :  1,    //      7
    cpu_clk_200m_gate_en      :  1,    //      8
    cpu_clk_100m_gate_en      :  1,    //      9
    cpu_clk_200m_inv_gate_en  :  1,    //     10
    xtal_i_cpu_gate_en        :  1,    //     11
    cpu_clk_400m_gate_en      :  1,    //     12
    cpu_clk_gate              :  1,    //     13
                              : 18;    //  31:14 reserved
}SYN_CPU_SYN_CRG_CPU07_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0020    crg_cpu08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_tzapb               :  1,    //      0
    swrst_sc                  :  1,    //      1
    swrst_528m                :  1,    //      2
    swrst_400m                :  1,    //      3
    swrst_25m                 :  1,    //      4
    swrst_100m                :  1,    //      5
    swrst_200m                :  1,    //      6
    swrst_spi                 :  1,    //      7
    swrst_50m                 :  1,    //      8
    swrst_peri_dmaapb1        :  1,    //      9
    swrst_peri_dmaapb0        :  1,    //     10
    swrst_peri_coreapb        :  1,    //     11
    swrst_peri_dma080         :  1,    //     12
    swrst_peri_ci             :  1,    //     13
    swrst_peri_nfc            :  1,    //     14
    swrst_sk_dma330           :  1,    //     15
    swrst_sk_hc               :  1,    //     16
    swrst_sk_sc               :  1,    //     17
    swrst_gic                 :  1,    //     18
                              : 13;    //  31:19 reserved
}SYN_CPU_SYN_CRG_CPU08_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0024    crg_cpu09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    swrst_tsreset             :  1,    //      0
    swrst_cssyreset           :  1,    //      1
    swrst_cntreset            :  1,    //      2
    swrst_socdbgreset         :  1,    //      3
    swrst_pclkreset           :  1,    //      4
    swrst_mbistreset          :  1,    //      5
    swrst_l2reset             :  1,    //      6
    swrst_etmreset_0          :  1,    //      7
    swrst_etmreset_1          :  1,    //      8
    swrst_etmreset_2          :  1,    //      9
    swrst_etmreset_3          :  1,    //     10
    swrst_dbgreset_0          :  1,    //     11
    swrst_dbgreset_1          :  1,    //     12
    swrst_dbgreset_2          :  1,    //     13
    swrst_dbgreset_3          :  1,    //     14
    swrst_corereset_0         :  1,    //     15
    swrst_corereset_1         :  1,    //     16
    swrst_corereset_2         :  1,    //     17
    swrst_corereset_3         :  1,    //     18
    swrst_coreporeset_0       :  1,    //     19
    swrst_coreporeset_1       :  1,    //     20
    swrst_coreporeset_2       :  1,    //     21
    swrst_coreporeset_3       :  1,    //     22
    swrst_clkreset            :  1,    //     23
                              :  8;    //  31:24 reserved
}SYN_CPU_SYN_CRG_CPU09_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_0028    crg_cpu10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    phy_tmds_clk_inv_sel      :  1,    //      0
    phy_i2c_clk_sel           :  1,    //      1
                              : 30;    //   31:2 reserved
}SYN_CPU_SYN_CRG_CPU10_L18F_A0;

/*-----------------------------------------------------------------------------------------
    0xC923_002C    syn_cpu11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    pchkerr                   :  1,    //      0
    swrst_phy2                :  1,    //      1
                              : 30;    //   31:2 reserved
}SYN_CPU_SYN_SYN_CPU11_L18F_A0;

/*-----------------------------------------------------------------------------------------
    cpu_syn Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SYN_CPU_SYN_CRG_CPU00_L18F_A0            crg_cpu00                ;         // 0xC923_0000
    SYN_CPU_SYN_CRG_CPU01_L18F_A0            crg_cpu01                ;         // 0xC923_0004
    SYN_CPU_SYN_CRG_CPU02_L18F_A0            crg_cpu02                ;         // 0xC923_0008
    SYN_CPU_SYN_CRG_CPU03_L18F_A0            crg_cpu03                ;         // 0xC923_000C
    SYN_CPU_SYN_CRG_CPU04_L18F_A0            crg_cpu04                ;         // 0xC923_0010
    SYN_CPU_SYN_CRG_CPU05_L18F_A0            crg_cpu05                ;         // 0xC923_0014
    SYN_CPU_SYN_CRG_CPU06_L18F_A0            crg_cpu06                ;         // 0xC923_0018
    SYN_CPU_SYN_CRG_CPU07_L18F_A0            crg_cpu07                ;         // 0xC923_001C
    SYN_CPU_SYN_CRG_CPU08_L18F_A0            crg_cpu08                ;         // 0xC923_0020
    SYN_CPU_SYN_CRG_CPU09_L18F_A0            crg_cpu09                ;         // 0xC923_0024
    SYN_CPU_SYN_CRG_CPU10_L18F_A0            crg_cpu10                ;         // 0xC923_0028
    SYN_CPU_SYN_SYN_CPU11_L18F_A0            syn_cpu11                ;         // 0xC923_002C
} SYN_CPU_SYN_REG_L18F_A0;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif	/* _CTOP_SYN_CPU_SYN_A0_REG_H_ */

/* from 'L18F_CTOP_SYN_Register_Manual_55.xlsm'  2017.4.19  KST by LGSiCRDV V2.1B*/

