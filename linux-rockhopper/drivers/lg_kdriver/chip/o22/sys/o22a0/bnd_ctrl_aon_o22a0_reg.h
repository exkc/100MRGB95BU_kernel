#ifndef _BND_CTRL_AON_REG_H_
#define _BND_CTRL_AON_REG_H_

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
    0xF308_6000    general_aon_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    general_aon_reg0          : 32;    //  31: 0
}BND_CTRL_AON_GENERAL_AON_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6100    crg_top_wov_aon_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_only_watchdog_rst: 1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AON_CRG_TOP_WOV_AON_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6104    crg_top_wov_aon_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_watchdog_reset_disable: 1,    //   0
                              : 31;    //   31:1 reserved
}BND_CTRL_AON_CRG_TOP_WOV_AON_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6108    crg_top_wov_aon_r02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wdt_reset_mux_sel     :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AON_CRG_TOP_WOV_AON_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_610C    crg_top_wov_aon_r03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_crg_top_reset_mux_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AON_CRG_TOP_WOV_AON_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6110    crg_top_wov_aon_r04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cpu_sw_reset_mux_sel  :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AON_CRG_TOP_WOV_AON_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6114    crg_top_wov_aon_r05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_micom_sw_reset_mux_sel:  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AON_CRG_TOP_WOV_AON_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_611C    bnd_aon_rxclk_md_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_rxclkdrv_wov_pdb      :  1,    //      0
    reg_rxclkdrv_wov_smv      :  1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_AON_SYN_BND_AON_RXCLK_MD_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6120    aon_por_r00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_edid            :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AON_AON_POR_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6124    aon_por_r01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_nisol_top2wov         :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AON_AON_POR_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6128    aon_gateing_en ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_gating_bnd_en_w_cpu: 1,    //      0
    reg_bus_gating_bnd_en_r_cpu: 1,    //      1
                              : 30;    //   31:2 reserved
}BND_CTRL_AON_AON_GATEING_EN_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_aon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_AON_GENERAL_AON_R00_O22A0_T    general_aon_r00;         // 0xF308_6000
    UINT32                             _rsvd_00[63];            // 0xF308_6004 ~ 0xF308_60FC
    BND_CTRL_AON_CRG_TOP_WOV_AON_R00_O22A0_T    crg_top_wov_aon_r00;    // 0xF308_6100
    BND_CTRL_AON_CRG_TOP_WOV_AON_R01_O22A0_T    crg_top_wov_aon_r01;    // 0xF308_6104
    BND_CTRL_AON_CRG_TOP_WOV_AON_R02_O22A0_T    crg_top_wov_aon_r02;    // 0xF308_6108
    BND_CTRL_AON_CRG_TOP_WOV_AON_R03_O22A0_T    crg_top_wov_aon_r03;    // 0xF308_610C
    BND_CTRL_AON_CRG_TOP_WOV_AON_R04_O22A0_T    crg_top_wov_aon_r04;    // 0xF308_6110
    BND_CTRL_AON_CRG_TOP_WOV_AON_R05_O22A0_T    crg_top_wov_aon_r05;    // 0xF308_6114
    UINT32                             _rsvd_01[1];             // 0xF308_6118
    BND_CTRL_AON_SYN_BND_AON_RXCLK_MD_R00_O22A0_T    bnd_aon_rxclk_md_r00;    // 0xF308_611C
    BND_CTRL_AON_AON_POR_R00_O22A0_T        aon_por_r00;             // 0xF308_6120
    BND_CTRL_AON_AON_POR_R01_O22A0_T        aon_por_r01;             // 0xF308_6124
    BND_CTRL_AON_AON_GATEING_EN_O22A0_T     aon_gateing_en;          // 0xF308_6128
}BND_CTRL_AON_REG_O22A0_T;
/* 11 regs */

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

#define BND_CTRL_AON_GENERAL_AON_R00_O22A0_T_OFF                 (BASEADDRESS+0x0000)
#define BND_CTRL_AON_CRG_TOP_WOV_AON_R00_O22A0_T_OFF             (BASEADDRESS+0x0100)
#define BND_CTRL_AON_CRG_TOP_WOV_AON_R01_O22A0_T_OFF             (BASEADDRESS+0x0104)
#define BND_CTRL_AON_CRG_TOP_WOV_AON_R02_O22A0_T_OFF             (BASEADDRESS+0x0108)
#define BND_CTRL_AON_CRG_TOP_WOV_AON_R03_O22A0_T_OFF             (BASEADDRESS+0x010C)
#define BND_CTRL_AON_CRG_TOP_WOV_AON_R04_O22A0_T_OFF             (BASEADDRESS+0x0110)
#define BND_CTRL_AON_CRG_TOP_WOV_AON_R05_O22A0_T_OFF             (BASEADDRESS+0x0114)
#define BND_CTRL_AON_SYN_BND_AON_RXCLK_MD_R00_O22A0_T_OFF            (BASEADDRESS+0x011C)
#define BND_CTRL_AON_AON_POR_R00_O22A0_T_OFF                     (BASEADDRESS+0x0120)
#define BND_CTRL_AON_AON_POR_R01_O22A0_T_OFF                     (BASEADDRESS+0x0124)
#define BND_CTRL_AON_AON_GATEING_EN_O22A0_T_OFF                  (BASEADDRESS+0x0128)

/*-----------------------------------------------------------------------------------------
    0xF308_6000    general_aon_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 general_aon_reg0   : 32;    //  31: 0
    };
}BND_CTRL_AON_GENERAL_AON_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6100    crg_top_wov_aon_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_only_watchdog_rst: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AON_CRG_TOP_WOV_AON_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6104    crg_top_wov_aon_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_watchdog_reset_disable: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AON_CRG_TOP_WOV_AON_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6108    crg_top_wov_aon_r02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_wdt_reset_mux_sel: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AON_CRG_TOP_WOV_AON_R02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_610C    crg_top_wov_aon_r03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_crg_top_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AON_CRG_TOP_WOV_AON_R03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6110    crg_top_wov_aon_r04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cpu_sw_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AON_CRG_TOP_WOV_AON_R04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6114    crg_top_wov_aon_r05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_micom_sw_reset_mux_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AON_CRG_TOP_WOV_AON_R05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_611C    bnd_aon_rxclk_md_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_rxclkdrv_wov_pdb: 1;    //      0
    UINT32 reg_rxclkdrv_wov_smv: 1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_AON_SYN_BND_AON_RXCLK_MD_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6120    aon_por_r00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nisol_edid     :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AON_AON_POR_R00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6124    aon_por_r01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_nisol_top2wov  :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AON_AON_POR_R01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0xF308_6128    aon_gateing_en ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_gating_bnd_en_w_cpu: 1;    //  0
    UINT32 reg_bus_gating_bnd_en_r_cpu: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}BND_CTRL_AON_AON_GATEING_EN_O22A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_aon Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_AON_GENERAL_AON_R00_O22A0_T    general_aon_r00;         // 0xF308_6000
    UINT32                             _rsvd_00[63];            // 0xF308_6004 ~ 0xF308_60FC
    BND_CTRL_AON_CRG_TOP_WOV_AON_R00_O22A0_T    crg_top_wov_aon_r00;    // 0xF308_6100
    BND_CTRL_AON_CRG_TOP_WOV_AON_R01_O22A0_T    crg_top_wov_aon_r01;    // 0xF308_6104
    BND_CTRL_AON_CRG_TOP_WOV_AON_R02_O22A0_T    crg_top_wov_aon_r02;    // 0xF308_6108
    BND_CTRL_AON_CRG_TOP_WOV_AON_R03_O22A0_T    crg_top_wov_aon_r03;    // 0xF308_610C
    BND_CTRL_AON_CRG_TOP_WOV_AON_R04_O22A0_T    crg_top_wov_aon_r04;    // 0xF308_6110
    BND_CTRL_AON_CRG_TOP_WOV_AON_R05_O22A0_T    crg_top_wov_aon_r05;    // 0xF308_6114
    UINT32                             _rsvd_01[1];             // 0xF308_6118
    BND_CTRL_AON_SYN_BND_AON_RXCLK_MD_R00_O22A0_T    bnd_aon_rxclk_md_r00;    // 0xF308_611C
    BND_CTRL_AON_AON_POR_R00_O22A0_T        aon_por_r00;             // 0xF308_6120
    BND_CTRL_AON_AON_POR_R01_O22A0_T        aon_por_r01;             // 0xF308_6124
    BND_CTRL_AON_AON_GATEING_EN_O22A0_T     aon_gateing_en;          // 0xF308_6128
}BND_CTRL_AON_REG_O22A0_T;
/* 11 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_AON_REG_H_

/* from 'O22_CTOP_SYN_Register_Manual_org.xlsx'  2020.12.8  KJH by LGSiCRDV V3.1C*/

