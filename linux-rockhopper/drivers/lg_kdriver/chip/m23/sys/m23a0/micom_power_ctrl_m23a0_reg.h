#ifndef _MICOM_POWER_CTRL_M23A0_REG_H_
#define _MICOM_POWER_CTRL_M23A0_REG_H_

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
    0xF351_3000    power_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    clk_gate_en               :  1,    //      0
                              :  3,    //   3: 1 reserved
    apb_lockup_chk_en         :  1,    //      4
                              :  3,    //   7: 5 reserved
    apb_ch2_lockup_chk_en     :  1,    //      8
                              :  3,    //  11: 9 reserved
    auto_flush_mode_en        :  1,    //     12
                              :  3,    //  15:13 reserved
    axi_lockup_mode_en        :  1,    //     16
                              : 15;    //  31:17 reserved
}MICOM_POWER_CTRL_POWER_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_3004    power_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vd1_ipw_clk_gate_en   :  1,    //      0
    reg_vd0_ipw_clk_gate_en   :  1,    //      1
    reg_sb_tiv_ipw_clk_gate_en:  1,    //      2
    reg_venc_ipw_clk_gate_en  :  1,    //      3
    reg_icod_ipw_clk_gate_en  :  1,    //      4
    reg_te_ipw_clk_gate_en    :  1,    //      5
    reg_pdm_ipw_clk_gate_en   :  1,    //      6
    reg_aud_ipw_clk_gate_en   :  1,    //      7
    reg_vmcu_ipw_clk_gate_en  :  1,    //      8
    reg_sb_cvd_ipw_clk_gate_en:  1,    //      9
    reg_hdmi_ipw_clk_gate_en  :  1,    //     10
    reg_tcon_ipw_clk_gate_en  :  1,    //     11
    reg_vsd_ipw_clk_gate_en   :  1,    //     12
    reg_vdo_ipw_clk_gate_en   :  1,    //     13
    reg_sre_ipw_clk_gate_en   :  1,    //     14
    reg_nd_ipw_clk_gate_en    :  1,    //     15
    reg_lne_ipw_clk_gate_en   :  1,    //     16
    reg_led_ipw_clk_gate_en   :  1,    //     17
    reg_imx_ipw_clk_gate_en   :  1,    //     18
    reg_hdr_ipw_clk_gate_en   :  1,    //     19
    reg_gsc_ipw_clk_gate_en   :  1,    //     20
    reg_me_ipw_clk_gate_en    :  1,    //     21
    reg_fms_ipw_clk_gate_en   :  1,    //     22
    reg_fmc_ipw_clk_gate_en   :  1,    //     23
    reg_dne_ipw_clk_gate_en   :  1,    //     24
    reg_cvi_ipw_clk_gate_en   :  1,    //     25
    reg_cco_ipw_clk_gate_en   :  1,    //     26
    reg_pmcu_ipw_clk_gate_en  :  1,    //     27
                              :  4;    //  31:28 reserved
}MICOM_POWER_CTRL_POWER_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_3008    power_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_m0_ipw_clk_gate_en    :  1,    //      0
    reg_dbb_ipw_clk_gate_en   :  1,    //      1
    reg_lbus_ipw_clk_gate_en  :  1,    //      2
    reg_sb_ddr_ipw_clk_gate_en:  1,    //      3
    reg_sb_emu_ipw_clk_gate_en:  1,    //      4
    reg_sb_epu_ipw_clk_gate_en:  1,    //      5
    reg_edid1_ipw_clk_gate_en :  1,    //      6
    reg_edid0_ipw_clk_gate_en :  1,    //      7
    reg_usb_hs3_ipw_clk_gate_en: 1,    //      8
    reg_usb_hs2_ipw_clk_gate_en: 1,    //      9
    reg_usb_hs1_ipw_clk_gate_en: 1,    //     10
    reg_ephy_ipw_clk_gate_en  :  1,    //     11
    reg_emmc_ipw_clk_gate_en  :  1,    //     12
    reg_gfx_ipw_clk_gate_en   :  1,    //     13
    reg_cpu_ipw_clk_gate_en   :  1,    //     14
                              : 17;    //  31:15 reserved
}MICOM_POWER_CTRL_POWER_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_300C    power_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_i_rst_cpuav_i_vd1_d100: 1,    //  0
    reg_swrst_i_rst_cpuav_i_vd1: 1,    //      1
    reg_swrst_i_rst_cpuav_i_vd0_d100: 1,    //  2
    reg_swrst_i_rst_cpuav_i_vd0: 1,    //      3
    reg_swrst_i_rst_cpuav_i_nd0_d100: 1,    //  4
    reg_swrst_i_rst_cpuav_i_nd0: 1,    //      5
    reg_swrst_i_rst_cpuav_i_me0_d100: 1,    //  6
    reg_swrst_i_rst_cpuav_i_me0: 1,    //      7
    reg_swrst_i_rst_cpuav_i_edid_d100: 1,    //  8
    reg_swrst_i_rst_cpuav_i_edid: 1,    //     9
    reg_swrst_i_rst_disp_i_dpe_d100: 1,    //  10
    reg_swrst_i_rst_disp_i_dpe:  1,    //     11
    reg_swrst_i_rst_cpuav_i_cvi_d100: 1,    //  12
    reg_swrst_i_rst_cpuav_i_cvi: 1,    //     13
    reg_swrst_i_rst_cpuav_i_cpu_d100: 1,    //  14
    reg_swrst_i_rst_cpuav_i_cpu: 1,    //     15
    reg_swrst_i_rst_cpuav_i_bus_d100: 1,    //  16
    reg_swrst_i_rst_cpuav_i_bus: 1,    //     17
    reg_swrst_i_rst_cpuav_i_bmc_d100: 1,    //  18
    reg_swrst_i_rst_cpuav_i_bmc: 1,    //     19
    reg_swrst_i_rst_cpuav_i_fms_d100: 1,    //  20
    reg_swrst_i_rst_cpuav_i_fms: 1,    //     21
    reg_swrst_i_rst_cpuav_i_fmc_d100: 1,    //  22
    reg_swrst_i_rst_cpuav_i_fmc: 1,    //     23
    reg_swrst_i_rst_cpuav_i_aud_d100: 1,    //  24
    reg_swrst_i_rst_cpuav_i_aud: 1,    //     25
    reg_swrst_i_rst_cpuav_i_m0_d100: 1,    //  26
    reg_swrst_i_rst_cpuav_i_m0:  1,    //     27
                              :  4;    //  31:28 reserved
}MICOM_POWER_CTRL_POWER_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_3010    nisol_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_cpu_syn         :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_POWER_CTRL_NISOL_R01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_3014    power_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pdm_0_axi_lockup_chk_en: 1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ephy_0_axi_lockup_chk_en: 1,    //     4
                              :  3,    //   7: 5 reserved
    reg_micom_1_axi_lockup_chk_en: 1,    //    8
                              :  3,    //  11: 9 reserved
    reg_micom_0_axi_lockup_chk_en: 1,    //   12
                              : 19;    //  31:13 reserved
}MICOM_POWER_CTRL_POWER_04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_POWER_CTRL_POWER_00_M23A0_T      power_00   ;             // 0xF351_3000
    MICOM_POWER_CTRL_POWER_01_M23A0_T      power_01   ;             // 0xF351_3004
    MICOM_POWER_CTRL_POWER_02_M23A0_T      power_02   ;             // 0xF351_3008
    MICOM_POWER_CTRL_POWER_03_M23A0_T      power_03   ;             // 0xF351_300C
    MICOM_POWER_CTRL_NISOL_R01_M23A0_T     nisol_r01  ;             // 0xF351_3010
    MICOM_POWER_CTRL_POWER_04_M23A0_T      power_04   ;             // 0xF351_3014
}MICOM_POWER_CTRL_REG_M23A0_T;
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

#define MICOM_POWER_CTRL_POWER_00_M23A0_T_OFF                   (BASEADDRESS+0x0000)
#define MICOM_POWER_CTRL_POWER_01_M23A0_T_OFF                   (BASEADDRESS+0x0004)
#define MICOM_POWER_CTRL_POWER_02_M23A0_T_OFF                   (BASEADDRESS+0x0008)
#define MICOM_POWER_CTRL_POWER_03_M23A0_T_OFF                   (BASEADDRESS+0x000C)
#define MICOM_POWER_CTRL_NISOL_R01_M23A0_T_OFF                  (BASEADDRESS+0x0010)
#define MICOM_POWER_CTRL_POWER_04_M23A0_T_OFF                   (BASEADDRESS+0x0014)

/*-----------------------------------------------------------------------------------------
    0xF351_3000    power_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 clk_gate_en        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 apb_lockup_chk_en  :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 apb_ch2_lockup_chk_en: 1;    //     8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 auto_flush_mode_en :  1;    //     12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 axi_lockup_mode_en :  1;    //     16
    UINT32 resvd04            : 15;    //  31:17 reserved
    };
}MICOM_POWER_CTRL_POWER_00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_3004    power_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vd1_ipw_clk_gate_en: 1;    //   0
    UINT32 reg_vd0_ipw_clk_gate_en: 1;    //   1
    UINT32 reg_sb_tiv_ipw_clk_gate_en: 1;    //  2
    UINT32 reg_venc_ipw_clk_gate_en: 1;    //  3
    UINT32 reg_icod_ipw_clk_gate_en: 1;    //  4
    UINT32 reg_te_ipw_clk_gate_en: 1;    //    5
    UINT32 reg_pdm_ipw_clk_gate_en: 1;    //   6
    UINT32 reg_aud_ipw_clk_gate_en: 1;    //   7
    UINT32 reg_vmcu_ipw_clk_gate_en: 1;    //  8
    UINT32 reg_sb_cvd_ipw_clk_gate_en: 1;    //  9
    UINT32 reg_hdmi_ipw_clk_gate_en: 1;    //  10
    UINT32 reg_tcon_ipw_clk_gate_en: 1;    //  11
    UINT32 reg_vsd_ipw_clk_gate_en: 1;    //  12
    UINT32 reg_vdo_ipw_clk_gate_en: 1;    //  13
    UINT32 reg_sre_ipw_clk_gate_en: 1;    //  14
    UINT32 reg_nd_ipw_clk_gate_en: 1;    //   15
    UINT32 reg_lne_ipw_clk_gate_en: 1;    //  16
    UINT32 reg_led_ipw_clk_gate_en: 1;    //  17
    UINT32 reg_imx_ipw_clk_gate_en: 1;    //  18
    UINT32 reg_hdr_ipw_clk_gate_en: 1;    //  19
    UINT32 reg_gsc_ipw_clk_gate_en: 1;    //  20
    UINT32 reg_me_ipw_clk_gate_en: 1;    //   21
    UINT32 reg_fms_ipw_clk_gate_en: 1;    //  22
    UINT32 reg_fmc_ipw_clk_gate_en: 1;    //  23
    UINT32 reg_dne_ipw_clk_gate_en: 1;    //  24
    UINT32 reg_cvi_ipw_clk_gate_en: 1;    //  25
    UINT32 reg_cco_ipw_clk_gate_en: 1;    //  26
    UINT32 reg_pmcu_ipw_clk_gate_en: 1;    //  27
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MICOM_POWER_CTRL_POWER_01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_3008    power_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_m0_ipw_clk_gate_en: 1;    //    0
    UINT32 reg_dbb_ipw_clk_gate_en: 1;    //   1
    UINT32 reg_lbus_ipw_clk_gate_en: 1;    //  2
    UINT32 reg_sb_ddr_ipw_clk_gate_en: 1;    //  3
    UINT32 reg_sb_emu_ipw_clk_gate_en: 1;    //  4
    UINT32 reg_sb_epu_ipw_clk_gate_en: 1;    //  5
    UINT32 reg_edid1_ipw_clk_gate_en: 1;    //  6
    UINT32 reg_edid0_ipw_clk_gate_en: 1;    //  7
    UINT32 reg_usb_hs3_ipw_clk_gate_en: 1;    //  8
    UINT32 reg_usb_hs2_ipw_clk_gate_en: 1;    //  9
    UINT32 reg_usb_hs1_ipw_clk_gate_en: 1;    //  10
    UINT32 reg_ephy_ipw_clk_gate_en: 1;    //  11
    UINT32 reg_emmc_ipw_clk_gate_en: 1;    //  12
    UINT32 reg_gfx_ipw_clk_gate_en: 1;    //  13
    UINT32 reg_cpu_ipw_clk_gate_en: 1;    //  14
    UINT32 resvd00            : 17;    //  31:15 reserved
    };
}MICOM_POWER_CTRL_POWER_02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_300C    power_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_i_rst_cpuav_i_vd1_d100: 1;    //  0
    UINT32 reg_swrst_i_rst_cpuav_i_vd1: 1;    //  1
    UINT32 reg_swrst_i_rst_cpuav_i_vd0_d100: 1;    //  2
    UINT32 reg_swrst_i_rst_cpuav_i_vd0: 1;    //  3
    UINT32 reg_swrst_i_rst_cpuav_i_nd0_d100: 1;    //  4
    UINT32 reg_swrst_i_rst_cpuav_i_nd0: 1;    //  5
    UINT32 reg_swrst_i_rst_cpuav_i_me0_d100: 1;    //  6
    UINT32 reg_swrst_i_rst_cpuav_i_me0: 1;    //  7
    UINT32 reg_swrst_i_rst_cpuav_i_edid_d100: 1;    //  8
    UINT32 reg_swrst_i_rst_cpuav_i_edid: 1;    //  9
    UINT32 reg_swrst_i_rst_disp_i_dpe_d100: 1;    //  10
    UINT32 reg_swrst_i_rst_disp_i_dpe: 1;    //  11
    UINT32 reg_swrst_i_rst_cpuav_i_cvi_d100: 1;    //  12
    UINT32 reg_swrst_i_rst_cpuav_i_cvi: 1;    //  13
    UINT32 reg_swrst_i_rst_cpuav_i_cpu_d100: 1;    //  14
    UINT32 reg_swrst_i_rst_cpuav_i_cpu: 1;    //  15
    UINT32 reg_swrst_i_rst_cpuav_i_bus_d100: 1;    //  16
    UINT32 reg_swrst_i_rst_cpuav_i_bus: 1;    //  17
    UINT32 reg_swrst_i_rst_cpuav_i_bmc_d100: 1;    //  18
    UINT32 reg_swrst_i_rst_cpuav_i_bmc: 1;    //  19
    UINT32 reg_swrst_i_rst_cpuav_i_fms_d100: 1;    //  20
    UINT32 reg_swrst_i_rst_cpuav_i_fms: 1;    //  21
    UINT32 reg_swrst_i_rst_cpuav_i_fmc_d100: 1;    //  22
    UINT32 reg_swrst_i_rst_cpuav_i_fmc: 1;    //  23
    UINT32 reg_swrst_i_rst_cpuav_i_aud_d100: 1;    //  24
    UINT32 reg_swrst_i_rst_cpuav_i_aud: 1;    //  25
    UINT32 reg_swrst_i_rst_cpuav_i_m0_d100: 1;    //  26
    UINT32 reg_swrst_i_rst_cpuav_i_m0: 1;    //  27
    UINT32 resvd00            :  4;    //  31:28 reserved
    };
}MICOM_POWER_CTRL_POWER_03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_3010    nisol_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nisol_cpu_syn  :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_POWER_CTRL_NISOL_R01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xF351_3014    power_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pdm_0_axi_lockup_chk_en: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_ephy_0_axi_lockup_chk_en: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_micom_1_axi_lockup_chk_en: 1;    //  8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_micom_0_axi_lockup_chk_en: 1;    //  12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}MICOM_POWER_CTRL_POWER_04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    base_address Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_POWER_CTRL_POWER_00_M23A0_T      power_00   ;             // 0xF351_3000
    MICOM_POWER_CTRL_POWER_01_M23A0_T      power_01   ;             // 0xF351_3004
    MICOM_POWER_CTRL_POWER_02_M23A0_T      power_02   ;             // 0xF351_3008
    MICOM_POWER_CTRL_POWER_03_M23A0_T      power_03   ;             // 0xF351_300C
    MICOM_POWER_CTRL_NISOL_R01_M23A0_T     nisol_r01  ;             // 0xF351_3010
    MICOM_POWER_CTRL_POWER_04_M23A0_T      power_04   ;             // 0xF351_3014
}MICOM_POWER_CTRL_REG_M23A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CTOP_SYN_Register_Manual.xlsx'  2022.2.28  KJH by LGSiCRDV V3.1C*/

