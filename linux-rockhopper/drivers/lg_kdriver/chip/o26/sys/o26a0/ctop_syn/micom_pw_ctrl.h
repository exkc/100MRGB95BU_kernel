#ifndef _MICOM_PW_CTRL_REG_O26A0_H_
#define _MICOM_PW_CTRL_REG_O26A0_H_

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
    0xCA3A_2000    power_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    clk_gate_en               :  1,    //      0
                              :  3,    //   3: 1 reserved
    apb_lockup_chk_en         :  1,    //      4
                              :  7,    //  11: 5 reserved
    axi_lockup_mode_en        :  1,    //     12
                              : 19;    //  31:13 reserved
}MICOM_PW_CTRL_POWER_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_2010    power_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fme_sbw_clk_gate_en   :  1,    //      0
    reg_srco_sbw_clk_gate_en  :  1,    //      1
    reg_vsd_ipw_clk_gate_en   :  1,    //      2
    reg_vdo_ipw_clk_gate_en   :  1,    //      3
    reg_tcon_ipw_clk_gate_en  :  1,    //      4
    reg_sre_ipw_clk_gate_en   :  1,    //      5
    reg_npp_ipw_clk_gate_en   :  1,    //      6
    reg_nd1_ipw_clk_gate_en   :  1,    //      7
    reg_nd0_ipw_clk_gate_en   :  1,    //      8
    reg_me1_ipw_clk_gate_en   :  1,    //      9
    reg_me0_ipw_clk_gate_en   :  1,    //     10
    reg_lnx1_ipw_clk_gate_en  :  1,    //     11
    reg_lnx0_ipw_clk_gate_en  :  1,    //     12
    reg_led_ipw_clk_gate_en   :  1,    //     13
    reg_imx_ipw_clk_gate_en   :  1,    //     14
    reg_hdr_ipw_clk_gate_en   :  1,    //     15
    reg_gsc_ipw_clk_gate_en   :  1,    //     16
    reg_fms_ipw_clk_gate_en   :  1,    //     17
    reg_fmc_ipw_clk_gate_en   :  1,    //     18
    reg_dsc_ipw_clk_gate_en   :  1,    //     19
    reg_dnsr1_ipw_clk_gate_en :  1,    //     20
    reg_dnsr0_ipw_clk_gate_en :  1,    //     21
    reg_cvi_ipw_clk_gate_en   :  1,    //     22
    reg_cco_ipw_clk_gate_en   :  1,    //     23
    reg_pmcu_ipw_clk_gate_en  :  1,    //     24
                              :  7;    //  31:25 reserved
}MICOM_PW_CTRL_POWER_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_2014    power_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tiv_sbw_clk_gate_en   :  1,    //      0
    reg_tivvm_sbw_clk_gate_en :  1,    //      1
    reg_venc_ipw_clk_gate_en  :  1,    //      2
    reg_te_ipw_clk_gate_en    :  1,    //      3
    reg_lnx2_ipw_clk_gate_en  :  1,    //      4
    reg_icod_ipw_clk_gate_en  :  1,    //      5
    reg_vd1_ipw_clk_gate_en   :  1,    //      6
    reg_vd0_ipw_clk_gate_en   :  1,    //      7
    reg_aud_ipw_clk_gate_en   :  1,    //      8
    reg_vmcu_ipw_clk_gate_en  :  1,    //      9
                              : 22;    //  31:10 reserved
}MICOM_PW_CTRL_POWER_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_2018    power_03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_sbw_clk_gate_en   :  1,    //      0
    reg_emu_sbw_clk_gate_en   :  1,    //      1
    reg_iommu_ipw_clk_gate_en :  1,    //      2
    reg_usb_ss4_ipw_clk_gate_en: 1,    //      3
    reg_usb_hs3_ipw_clk_gate_en: 1,    //      4
    reg_usb_hs2_ipw_clk_gate_en: 1,    //      5
    reg_usb_hs1_ipw_clk_gate_en: 1,    //      6
    reg_gpu_ipw_clk_gate_en   :  1,    //      7
    reg_gfx_ipw_clk_gate_en   :  1,    //      8
    reg_ephy_ipw_clk_gate_en  :  1,    //      9
    reg_emmc_ipw_clk_gate_en  :  1,    //     10
    reg_cpu_ipw_clk_gate_en   :  1,    //     11
                              : 20;    //  31:12 reserved
}MICOM_PW_CTRL_POWER_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_201C    power_04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lb1_sbw_clk_gate_en   :  1,    //      0
    reg_lb0_sbw_clk_gate_en   :  1,    //      1
    reg_ddr1_sbw_clk_gate_en  :  1,    //      2
    reg_ddr0_sbw_clk_gate_en  :  1,    //      3
    reg_ion0_ipw_clk_gate_en  :  1,    //      4
    reg_ion1_ipw_clk_gate_en  :  1,    //      5
    reg_m1_ipw_clk_gate_en    :  1,    //      6
    reg_m0_ipw_clk_gate_en    :  1,    //      7
    reg_dmcu_ipw_clk_gate_en  :  1,    //      8
    reg_lbus_ipw_clk_gate_en  :  1,    //      9
    reg_hdmi_ipw_clk_gate_en  :  1,    //     10
    reg_edid_ipw_clk_gate_en  :  1,    //     11
    reg_dbb_ipw_clk_gate_en   :  1,    //     12
    reg_edptx_ipw_clk_gate_en :  1,    //     13
                              : 18;    //  31:14 reserved
}MICOM_PW_CTRL_POWER_04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_2020    power_06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_swrst_i_rst_disp_i_dpe_d100: 1,    //  0
    reg_swrst_i_rst_disp_i_cco_d100: 1,    //  1
    reg_swrst_i_rst_cpuav_i_venc_d100: 1,    //  2
    reg_swrst_i_rst_cpuav_i_vd1_d100: 1,    //  3
    reg_swrst_i_rst_cpuav_i_vd0_d100: 1,    //  4
    reg_swrst_i_rst_cpuav_i_sre_d100: 1,    //  5
    reg_swrst_i_rst_cpuav_i_nd1_d100: 1,    //  6
    reg_swrst_i_rst_cpuav_i_nd0_d100: 1,    //  7
    reg_swrst_i_rst_disp_i_me1_d100: 1,    //  8
    reg_swrst_i_rst_cpuav_i_me0_d100: 1,    //  9
    reg_swrst_i_rst_cpuav_i_m1_d100: 1,    //  10
    reg_swrst_i_rst_cpuav_i_m0_d100: 1,    //  11
    reg_swrst_i_rst_cpuav_i_lnx2_d100: 1,    //  12
    reg_swrst_i_rst_cpuav_i_lnx1_d100: 1,    //  13
    reg_swrst_i_rst_cpuav_i_lnx0_d100: 1,    //  14
    reg_swrst_i_rst_cpuav_i_lbm_d100: 1,    //  15
    reg_swrst_i_rst_cpuav_i_imx_d100: 1,    //  16
    reg_swrst_i_rst_cpuav_i_hdr_d100: 1,    //  17
    reg_swrst_i_rst_cpuav_i_hdmi_d100: 1,    //  18
    reg_swrst_i_rst_cpuav_i_gsc_d100: 1,    //  19
    reg_swrst_i_rst_cpuav_i_fms_d100: 1,    //  20
    reg_swrst_i_rst_cpuav_i_fmc_d100: 1,    //  21
    reg_swrst_i_rst_cpuav_i_emmc_d100: 1,    //  22
    reg_swrst_i_rst_cpuav_i_dnsr_d100: 1,    //  23
    reg_swrst_i_rst_cpuav_i_cpu_d100: 1,    //  24
    reg_swrst_i_rst_cpuav_i_bmc_d100: 1,    //  25
    reg_swrst_i_rst_cpuav_i_aud_d100: 1,    //  26
                              :  5;    //  31:27 reserved
}MICOM_PW_CTRL_POWER_06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_pw_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_PW_CTRL_POWER_00_O26A0_T     power_00   ;             // 0xCA3A_2000
    UINT32                             _rsvd_00[3];             // 0xCA3A_2004 ~ 0xCA3A_200C
    MICOM_PW_CTRL_POWER_01_O26A0_T     power_01   ;             // 0xCA3A_2010
    MICOM_PW_CTRL_POWER_02_O26A0_T     power_02   ;             // 0xCA3A_2014
    MICOM_PW_CTRL_POWER_03_O26A0_T     power_03   ;             // 0xCA3A_2018
    MICOM_PW_CTRL_POWER_04_O26A0_T     power_04   ;             // 0xCA3A_201C
    MICOM_PW_CTRL_POWER_06_O26A0_T     power_06   ;             // 0xCA3A_2020
}MICOM_PW_CTRL_REG_O26A0_T;
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

#define MICOM_PW_CTRL_POWER_00_O26A0_T_OFF                  (BASEADDRESS+0x0000)
#define MICOM_PW_CTRL_POWER_01_O26A0_T_OFF                  (BASEADDRESS+0x0010)
#define MICOM_PW_CTRL_POWER_02_O26A0_T_OFF                  (BASEADDRESS+0x0014)
#define MICOM_PW_CTRL_POWER_03_O26A0_T_OFF                  (BASEADDRESS+0x0018)
#define MICOM_PW_CTRL_POWER_04_O26A0_T_OFF                  (BASEADDRESS+0x001C)
#define MICOM_PW_CTRL_POWER_06_O26A0_T_OFF                  (BASEADDRESS+0x0020)

/*-----------------------------------------------------------------------------------------
    0xCA3A_2000    power_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 clk_gate_en        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 apb_lockup_chk_en  :  1;    //      4
    UINT32 resvd01            :  7;    //  11: 5 reserved
    UINT32 axi_lockup_mode_en :  1;    //     12
    UINT32 resvd02            : 19;    //  31:13 reserved
    };
}MICOM_PW_CTRL_POWER_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_2010    power_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fme_sbw_clk_gate_en: 1;    //   0
    UINT32 reg_srco_sbw_clk_gate_en: 1;    //  1
    UINT32 reg_vsd_ipw_clk_gate_en: 1;    //   2
    UINT32 reg_vdo_ipw_clk_gate_en: 1;    //   3
    UINT32 reg_tcon_ipw_clk_gate_en: 1;    //  4
    UINT32 reg_sre_ipw_clk_gate_en: 1;    //   5
    UINT32 reg_npp_ipw_clk_gate_en: 1;    //   6
    UINT32 reg_nd1_ipw_clk_gate_en: 1;    //   7
    UINT32 reg_nd0_ipw_clk_gate_en: 1;    //   8
    UINT32 reg_me1_ipw_clk_gate_en: 1;    //   9
    UINT32 reg_me0_ipw_clk_gate_en: 1;    //  10
    UINT32 reg_lnx1_ipw_clk_gate_en: 1;    //  11
    UINT32 reg_lnx0_ipw_clk_gate_en: 1;    //  12
    UINT32 reg_led_ipw_clk_gate_en: 1;    //  13
    UINT32 reg_imx_ipw_clk_gate_en: 1;    //  14
    UINT32 reg_hdr_ipw_clk_gate_en: 1;    //  15
    UINT32 reg_gsc_ipw_clk_gate_en: 1;    //  16
    UINT32 reg_fms_ipw_clk_gate_en: 1;    //  17
    UINT32 reg_fmc_ipw_clk_gate_en: 1;    //  18
    UINT32 reg_dsc_ipw_clk_gate_en: 1;    //  19
    UINT32 reg_dnsr1_ipw_clk_gate_en: 1;    //  20
    UINT32 reg_dnsr0_ipw_clk_gate_en: 1;    //  21
    UINT32 reg_cvi_ipw_clk_gate_en: 1;    //  22
    UINT32 reg_cco_ipw_clk_gate_en: 1;    //  23
    UINT32 reg_pmcu_ipw_clk_gate_en: 1;    //  24
    UINT32 resvd00            :  7;    //  31:25 reserved
    };
}MICOM_PW_CTRL_POWER_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_2014    power_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tiv_sbw_clk_gate_en: 1;    //   0
    UINT32 reg_tivvm_sbw_clk_gate_en: 1;    //  1
    UINT32 reg_venc_ipw_clk_gate_en: 1;    //  2
    UINT32 reg_te_ipw_clk_gate_en: 1;    //    3
    UINT32 reg_lnx2_ipw_clk_gate_en: 1;    //  4
    UINT32 reg_icod_ipw_clk_gate_en: 1;    //  5
    UINT32 reg_vd1_ipw_clk_gate_en: 1;    //   6
    UINT32 reg_vd0_ipw_clk_gate_en: 1;    //   7
    UINT32 reg_aud_ipw_clk_gate_en: 1;    //   8
    UINT32 reg_vmcu_ipw_clk_gate_en: 1;    //  9
    UINT32 resvd00            : 22;    //  31:10 reserved
    };
}MICOM_PW_CTRL_POWER_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_2018    power_03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb_sbw_clk_gate_en: 1;    //   0
    UINT32 reg_emu_sbw_clk_gate_en: 1;    //   1
    UINT32 reg_iommu_ipw_clk_gate_en: 1;    //  2
    UINT32 reg_usb_ss4_ipw_clk_gate_en: 1;    //  3
    UINT32 reg_usb_hs3_ipw_clk_gate_en: 1;    //  4
    UINT32 reg_usb_hs2_ipw_clk_gate_en: 1;    //  5
    UINT32 reg_usb_hs1_ipw_clk_gate_en: 1;    //  6
    UINT32 reg_gpu_ipw_clk_gate_en: 1;    //   7
    UINT32 reg_gfx_ipw_clk_gate_en: 1;    //   8
    UINT32 reg_ephy_ipw_clk_gate_en: 1;    //  9
    UINT32 reg_emmc_ipw_clk_gate_en: 1;    //  10
    UINT32 reg_cpu_ipw_clk_gate_en: 1;    //  11
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MICOM_PW_CTRL_POWER_03_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_201C    power_04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lb1_sbw_clk_gate_en: 1;    //   0
    UINT32 reg_lb0_sbw_clk_gate_en: 1;    //   1
    UINT32 reg_ddr1_sbw_clk_gate_en: 1;    //  2
    UINT32 reg_ddr0_sbw_clk_gate_en: 1;    //  3
    UINT32 reg_ion0_ipw_clk_gate_en: 1;    //  4
    UINT32 reg_ion1_ipw_clk_gate_en: 1;    //  5
    UINT32 reg_m1_ipw_clk_gate_en: 1;    //    6
    UINT32 reg_m0_ipw_clk_gate_en: 1;    //    7
    UINT32 reg_dmcu_ipw_clk_gate_en: 1;    //  8
    UINT32 reg_lbus_ipw_clk_gate_en: 1;    //  9
    UINT32 reg_hdmi_ipw_clk_gate_en: 1;    //  10
    UINT32 reg_edid_ipw_clk_gate_en: 1;    //  11
    UINT32 reg_dbb_ipw_clk_gate_en: 1;    //  12
    UINT32 reg_edptx_ipw_clk_gate_en: 1;    //  13
    UINT32 resvd00            : 18;    //  31:14 reserved
    };
}MICOM_PW_CTRL_POWER_04_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA3A_2020    power_06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_swrst_i_rst_disp_i_dpe_d100: 1;    //  0
    UINT32 reg_swrst_i_rst_disp_i_cco_d100: 1;    //  1
    UINT32 reg_swrst_i_rst_cpuav_i_venc_d100: 1;    //  2
    UINT32 reg_swrst_i_rst_cpuav_i_vd1_d100: 1;    //  3
    UINT32 reg_swrst_i_rst_cpuav_i_vd0_d100: 1;    //  4
    UINT32 reg_swrst_i_rst_cpuav_i_sre_d100: 1;    //  5
    UINT32 reg_swrst_i_rst_cpuav_i_nd1_d100: 1;    //  6
    UINT32 reg_swrst_i_rst_cpuav_i_nd0_d100: 1;    //  7
    UINT32 reg_swrst_i_rst_disp_i_me1_d100: 1;    //  8
    UINT32 reg_swrst_i_rst_cpuav_i_me0_d100: 1;    //  9
    UINT32 reg_swrst_i_rst_cpuav_i_m1_d100: 1;    //  10
    UINT32 reg_swrst_i_rst_cpuav_i_m0_d100: 1;    //  11
    UINT32 reg_swrst_i_rst_cpuav_i_lnx2_d100: 1;    //  12
    UINT32 reg_swrst_i_rst_cpuav_i_lnx1_d100: 1;    //  13
    UINT32 reg_swrst_i_rst_cpuav_i_lnx0_d100: 1;    //  14
    UINT32 reg_swrst_i_rst_cpuav_i_lbm_d100: 1;    //  15
    UINT32 reg_swrst_i_rst_cpuav_i_imx_d100: 1;    //  16
    UINT32 reg_swrst_i_rst_cpuav_i_hdr_d100: 1;    //  17
    UINT32 reg_swrst_i_rst_cpuav_i_hdmi_d100: 1;    //  18
    UINT32 reg_swrst_i_rst_cpuav_i_gsc_d100: 1;    //  19
    UINT32 reg_swrst_i_rst_cpuav_i_fms_d100: 1;    //  20
    UINT32 reg_swrst_i_rst_cpuav_i_fmc_d100: 1;    //  21
    UINT32 reg_swrst_i_rst_cpuav_i_emmc_d100: 1;    //  22
    UINT32 reg_swrst_i_rst_cpuav_i_dnsr_d100: 1;    //  23
    UINT32 reg_swrst_i_rst_cpuav_i_cpu_d100: 1;    //  24
    UINT32 reg_swrst_i_rst_cpuav_i_bmc_d100: 1;    //  25
    UINT32 reg_swrst_i_rst_cpuav_i_aud_d100: 1;    //  26
    UINT32 resvd00            :  5;    //  31:27 reserved
    };
}MICOM_PW_CTRL_POWER_06_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_pw_ctrl Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_PW_CTRL_POWER_00_O26A0_T     power_00   ;             // 0xCA3A_2000
    UINT32                             _rsvd_00[3];             // 0xCA3A_2004 ~ 0xCA3A_200C
    MICOM_PW_CTRL_POWER_01_O26A0_T     power_01   ;             // 0xCA3A_2010
    MICOM_PW_CTRL_POWER_02_O26A0_T     power_02   ;             // 0xCA3A_2014
    MICOM_PW_CTRL_POWER_03_O26A0_T     power_03   ;             // 0xCA3A_2018
    MICOM_PW_CTRL_POWER_04_O26A0_T     power_04   ;             // 0xCA3A_201C
    MICOM_PW_CTRL_POWER_06_O26A0_T     power_06   ;             // 0xCA3A_2020
}MICOM_PW_CTRL_REG_O26A0_T;
/* 6 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MICOM_PW_CTRL_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

