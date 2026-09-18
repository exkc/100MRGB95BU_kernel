#ifndef _SCRG_CTRL_CPU_REG_O26A0_H_
#define _SCRG_CTRL_CPU_REG_O26A0_H_

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
    0xCA21_0000    crg_cpu000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CPU_CRG_CPU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0004    crg_cpu001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CPU_CRG_CPU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0008    crg_cpu002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adaprx_x_emusb_0__peri_400m_clk_gate_en: 1,    //  0
    reg_adaprx_x_ephy_0__peri_400m_clk_gate_en: 1,    //  1
    reg_adaprx_x_isol__peri_400m_clk_gate_en: 1,    //  2
    reg_adaprx_x_micom_0__peri_400m_clk_gate_en: 1,    //  3
    reg_adaprx_x_usbsb_0__peri_400m_clk_gate_en: 1,    //  4
    reg_adaptx_x_cpu_0__peri_400m_clk_gate_en: 1,    //  5
    reg_adaptx_x_cpu_1__peri_662m_clk_gate_en: 1,    //  6
    reg_adaptx_x_cpu_2__peri_662m_clk_gate_en: 1,    //  7
    reg_adaptx_x_cpu_3__peri_400m_clk_gate_en: 1,    //  8
    reg_adaptx_x_cpu_4__peri_400m_clk_gate_en: 1,    //  9
    reg_peri_200m_clk_gate_en :  1,    //     10
    reg_peri_200m_clk_n_gate_en: 1,    //     11
    reg_peri_25m_ci_clk_gate_en: 1,    //     12
    reg_peri_400m_clk_gate_en :  1,    //     13
    reg_peri_50m_ci_clk_gate_en: 1,    //     14
    reg_peri_660m_clk_gate_en :  1,    //     15
    reg_tzapb_clk_gate_en     :  1,    //     16
    reg_xtal_clk_w_gate_en    :  1,    //     17
                              : 14;    //  31:18 reserved
}SCRG_CTRL_CPU_CRG_CPU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_000C    crg_cpu003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_p_cpu_0_axi_bnd_n: 1,    //   0
    reg_soft_rst_p_cpu_1_axi_bnd_n: 1,    //   1
    reg_soft_rst_p_cpu_2_axi_bnd_n: 1,    //   2
    reg_soft_rst_p_cpu_3_axi_bnd_n: 1,    //   3
    reg_soft_rst_p_cpu_4_axi_bnd_n: 1,    //   4
    reg_soft_rst_p_emusb_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_p_ephy_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_p_isol_axi_bnd_n: 1,    //    7
    reg_soft_rst_p_micom_0_axi_bnd_n: 1,    //  8
    reg_soft_rst_p_usbsb_0_axi_bnd_n: 1,    //  9
    reg_soft_rst_x_cpu_0_axi_n:  1,    //     10
    reg_soft_rst_x_cpu_1_axi_n:  1,    //     11
    reg_soft_rst_x_cpu_2_axi_n:  1,    //     12
    reg_soft_rst_x_cpu_3_axi_n:  1,    //     13
    reg_soft_rst_x_cpu_4_axi_n:  1,    //     14
    reg_soft_rst_x_emusb_0_axi_n: 1,    //    15
    reg_soft_rst_x_ephy_0_axi_n: 1,    //     16
    reg_soft_rst_x_isol_axi_n :  1,    //     17
    reg_soft_rst_x_micom_0_axi_n: 1,    //    18
    reg_soft_rst_x_usbsb_0_axi_n: 1,    //    19
                              : 12;    //  31:20 reserved
}SCRG_CTRL_CPU_CRG_CPU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CPU_CRG_CPU000_O26A0_T    crg_cpu000;             // 0xCA21_0000
    SCRG_CTRL_CPU_CRG_CPU001_O26A0_T    crg_cpu001;             // 0xCA21_0004
    SCRG_CTRL_CPU_CRG_CPU002_O26A0_T    crg_cpu002;             // 0xCA21_0008
    SCRG_CTRL_CPU_CRG_CPU003_O26A0_T    crg_cpu003;             // 0xCA21_000C
}SCRG_CTRL_CPU_REG_O26A0_T;
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

#define SCRG_CTRL_CPU_CRG_CPU000_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_CPU_CRG_CPU001_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_CPU_CRG_CPU002_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_CPU_CRG_CPU003_O26A0_T_OFF                (BASEADDRESS+0x000C)

/*-----------------------------------------------------------------------------------------
    0xCA21_0000    crg_cpu000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CPU_CRG_CPU000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0004    crg_cpu001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CPU_CRG_CPU001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_0008    crg_cpu002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adaprx_x_emusb_0__peri_400m_clk_gate_en: 1;    //  0
    UINT32 reg_adaprx_x_ephy_0__peri_400m_clk_gate_en: 1;    //  1
    UINT32 reg_adaprx_x_isol__peri_400m_clk_gate_en: 1;    //  2
    UINT32 reg_adaprx_x_micom_0__peri_400m_clk_gate_en: 1;    //  3
    UINT32 reg_adaprx_x_usbsb_0__peri_400m_clk_gate_en: 1;    //  4
    UINT32 reg_adaptx_x_cpu_0__peri_400m_clk_gate_en: 1;    //  5
    UINT32 reg_adaptx_x_cpu_1__peri_662m_clk_gate_en: 1;    //  6
    UINT32 reg_adaptx_x_cpu_2__peri_662m_clk_gate_en: 1;    //  7
    UINT32 reg_adaptx_x_cpu_3__peri_400m_clk_gate_en: 1;    //  8
    UINT32 reg_adaptx_x_cpu_4__peri_400m_clk_gate_en: 1;    //  9
    UINT32 reg_peri_200m_clk_gate_en: 1;    //  10
    UINT32 reg_peri_200m_clk_n_gate_en: 1;    //  11
    UINT32 reg_peri_25m_ci_clk_gate_en: 1;    //  12
    UINT32 reg_peri_400m_clk_gate_en: 1;    //  13
    UINT32 reg_peri_50m_ci_clk_gate_en: 1;    //  14
    UINT32 reg_peri_660m_clk_gate_en: 1;    //  15
    UINT32 reg_tzapb_clk_gate_en: 1;    //    16
    UINT32 reg_xtal_clk_w_gate_en: 1;    //   17
    UINT32 resvd00            : 14;    //  31:18 reserved
    };
}SCRG_CTRL_CPU_CRG_CPU002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCA21_000C    crg_cpu003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_p_cpu_0_axi_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_p_cpu_1_axi_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_cpu_2_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_p_cpu_3_axi_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_p_cpu_4_axi_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_p_emusb_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_p_ephy_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_p_isol_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_micom_0_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_p_usbsb_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_cpu_0_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_cpu_1_axi_n: 1;    //  11
    UINT32 reg_soft_rst_x_cpu_2_axi_n: 1;    //  12
    UINT32 reg_soft_rst_x_cpu_3_axi_n: 1;    //  13
    UINT32 reg_soft_rst_x_cpu_4_axi_n: 1;    //  14
    UINT32 reg_soft_rst_x_emusb_0_axi_n: 1;    //  15
    UINT32 reg_soft_rst_x_ephy_0_axi_n: 1;    //  16
    UINT32 reg_soft_rst_x_isol_axi_n: 1;    //  17
    UINT32 reg_soft_rst_x_micom_0_axi_n: 1;    //  18
    UINT32 reg_soft_rst_x_usbsb_0_axi_n: 1;    //  19
    UINT32 resvd00            : 12;    //  31:20 reserved
    };
}SCRG_CTRL_CPU_CRG_CPU003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cpu Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CPU_CRG_CPU000_O26A0_T    crg_cpu000;             // 0xCA21_0000
    SCRG_CTRL_CPU_CRG_CPU001_O26A0_T    crg_cpu001;             // 0xCA21_0004
    SCRG_CTRL_CPU_CRG_CPU002_O26A0_T    crg_cpu002;             // 0xCA21_0008
    SCRG_CTRL_CPU_CRG_CPU003_O26A0_T    crg_cpu003;             // 0xCA21_000C
}SCRG_CTRL_CPU_REG_O26A0_T;
/* 4 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_SCRG_CTRL_CPU_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

