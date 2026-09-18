#ifndef _SCRG_CTRL_CVI_M23A0_REG_H_
#define _SCRG_CTRL_CVI_M23A0_REG_H_

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
    0xCC6A_0000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_CVI_CRG_CVI00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_0004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_CVI_CRG_CVI01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_0008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvd27_clk_gate_en     :  1,    //      0
    reg_cvd54_clk_gate_en     :  1,    //      1
    reg_cvi0_clk_gate_en      :  1,    //      2
    reg_cvi1_clk_gate_en      :  1,    //      3
    reg_cvi_apb_clk_gate_en   :  1,    //      4
    reg_cvi_axi_clk_gate_en   :  1,    //      5
    reg_cvi_de_clk_gate_en    :  1,    //      6
    reg_fly_phy1_hdmi_link_clk_gate_en: 1,    //  7
    reg_fly_phy2_hdmi_link_clk_gate_en: 1,    //  8
    reg_fly_phy3_hdmi_link_clk_gate_en: 1,    //  9
    reg_fly_phy4_hdmi_link_clk_gate_en: 1,    //  10
                              : 21;    //  31:11 reserved
}SCRG_CTRL_CVI_CRG_CVI02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_000C    crg_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_axi_n        :  1,    //      1
    reg_soft_rst_axi_sbus_n   :  1,    //      2
    reg_soft_rst_cvd27_n      :  1,    //      3
    reg_soft_rst_cvd54_n      :  1,    //      4
    reg_soft_rst_cvd_mif_n    :  1,    //      5
    reg_soft_rst_cvd_vbi_n    :  1,    //      6
    reg_soft_rst_cvi0_n       :  1,    //      7
    reg_soft_rst_cvi1_n       :  1,    //      8
    reg_soft_rst_de_n         :  1,    //      9
    reg_soft_rst_f_cvi_0_de_bnd_n: 1,    //   10
    reg_soft_rst_f_cvi_1_de_bnd_n: 1,    //   11
    reg_soft_rst_f_hdmi_0_cvi0_bnd_n: 1,    //  12
    reg_soft_rst_f_hdmi_1_cvi0_bnd_n: 1,    //  13
    reg_soft_rst_f_hdmi_2_cvi0_bnd_n: 1,    //  14
    reg_soft_rst_f_hdmi_3_cvi0_bnd_n: 1,    //  15
    reg_soft_rst_p_cvi_0_axi_bnd_n: 1,    //  16
    reg_soft_rst_x_cvi_0_axi_bnd_n: 1,    //  17
    reg_soft_rst_x_cvi_0_axi_n:  1,    //     18
                              : 13;    //  31:19 reserved
}SCRG_CTRL_CVI_CRG_CVI03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_0010    crg_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_fly_phy1_hdmi_link_clk_sel: 1,    //   0
                              :  3,    //   3: 1 reserved
    reg_fly_phy2_hdmi_link_clk_sel: 1,    //   4
                              :  3,    //   7: 5 reserved
    reg_fly_phy3_hdmi_link_clk_sel: 1,    //   8
                              :  3,    //  11: 9 reserved
    reg_fly_phy4_hdmi_link_clk_sel: 1,    //  12
                              :  3,    //  15:13 reserved
    reg_cvi0_clk_sel          :  3,    //  18:16
                              :  1,    //     19 reserved
    reg_cvi1_clk_sel          :  3,    //  22:20
                              :  9;    //  31:23 reserved
}SCRG_CTRL_CVI_CRG_CVI04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CVI_CRG_CVI00_M23A0_T    crg_cvi00  ;             // 0xCC6A_0000
    SCRG_CTRL_CVI_CRG_CVI01_M23A0_T    crg_cvi01  ;             // 0xCC6A_0004
    SCRG_CTRL_CVI_CRG_CVI02_M23A0_T    crg_cvi02  ;             // 0xCC6A_0008
    SCRG_CTRL_CVI_CRG_CVI03_M23A0_T    crg_cvi03  ;             // 0xCC6A_000C
    SCRG_CTRL_CVI_CRG_CVI04_M23A0_T    crg_cvi04  ;             // 0xCC6A_0010
}SCRG_CTRL_CVI_REG_M23A0_T;
/* 5 regs */

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

#define SCRG_CTRL_CVI_CRG_CVI00_M23A0_T_OFF                 (BASEADDRESS+0x0000)
#define SCRG_CTRL_CVI_CRG_CVI01_M23A0_T_OFF                 (BASEADDRESS+0x0004)
#define SCRG_CTRL_CVI_CRG_CVI02_M23A0_T_OFF                 (BASEADDRESS+0x0008)
#define SCRG_CTRL_CVI_CRG_CVI03_M23A0_T_OFF                 (BASEADDRESS+0x000C)
#define SCRG_CTRL_CVI_CRG_CVI04_M23A0_T_OFF                 (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC6A_0000    crg_cvi00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_CVI_CRG_CVI00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_0004    crg_cvi01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_CVI_CRG_CVI01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_0008    crg_cvi02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvd27_clk_gate_en: 1;    //     0
    UINT32 reg_cvd54_clk_gate_en: 1;    //     1
    UINT32 reg_cvi0_clk_gate_en: 1;    //      2
    UINT32 reg_cvi1_clk_gate_en: 1;    //      3
    UINT32 reg_cvi_apb_clk_gate_en: 1;    //   4
    UINT32 reg_cvi_axi_clk_gate_en: 1;    //   5
    UINT32 reg_cvi_de_clk_gate_en: 1;    //    6
    UINT32 reg_fly_phy1_hdmi_link_clk_gate_en: 1;    //  7
    UINT32 reg_fly_phy2_hdmi_link_clk_gate_en: 1;    //  8
    UINT32 reg_fly_phy3_hdmi_link_clk_gate_en: 1;    //  9
    UINT32 reg_fly_phy4_hdmi_link_clk_gate_en: 1;    //  10
    UINT32 resvd00            : 21;    //  31:11 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_000C    crg_cvi03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_axi_n :  1;    //      1
    UINT32 reg_soft_rst_axi_sbus_n: 1;    //   2
    UINT32 reg_soft_rst_cvd27_n: 1;    //      3
    UINT32 reg_soft_rst_cvd54_n: 1;    //      4
    UINT32 reg_soft_rst_cvd_mif_n: 1;    //    5
    UINT32 reg_soft_rst_cvd_vbi_n: 1;    //    6
    UINT32 reg_soft_rst_cvi0_n:  1;    //      7
    UINT32 reg_soft_rst_cvi1_n:  1;    //      8
    UINT32 reg_soft_rst_de_n  :  1;    //      9
    UINT32 reg_soft_rst_f_cvi_0_de_bnd_n: 1;    //  10
    UINT32 reg_soft_rst_f_cvi_1_de_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_f_hdmi_0_cvi0_bnd_n: 1;    //  12
    UINT32 reg_soft_rst_f_hdmi_1_cvi0_bnd_n: 1;    //  13
    UINT32 reg_soft_rst_f_hdmi_2_cvi0_bnd_n: 1;    //  14
    UINT32 reg_soft_rst_f_hdmi_3_cvi0_bnd_n: 1;    //  15
    UINT32 reg_soft_rst_p_cvi_0_axi_bnd_n: 1;    //  16
    UINT32 reg_soft_rst_x_cvi_0_axi_bnd_n: 1;    //  17
    UINT32 reg_soft_rst_x_cvi_0_axi_n: 1;    //  18
    UINT32 resvd00            : 13;    //  31:19 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC6A_0010    crg_cvi04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_fly_phy1_hdmi_link_clk_sel: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_fly_phy2_hdmi_link_clk_sel: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_fly_phy3_hdmi_link_clk_sel: 1;    //  8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_fly_phy4_hdmi_link_clk_sel: 1;    //  12
    UINT32 resvd03            :  3;    //  15:13 reserved
    UINT32 reg_cvi0_clk_sel   :  3;    //  18:16
    UINT32 resvd04            :  1;    //     19 reserved
    UINT32 reg_cvi1_clk_sel   :  3;    //  22:20
    UINT32 resvd05            :  9;    //  31:23 reserved
    };
}SCRG_CTRL_CVI_CRG_CVI04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_cvi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_CVI_CRG_CVI00_M23A0_T    crg_cvi00  ;             // 0xCC6A_0000
    SCRG_CTRL_CVI_CRG_CVI01_M23A0_T    crg_cvi01  ;             // 0xCC6A_0004
    SCRG_CTRL_CVI_CRG_CVI02_M23A0_T    crg_cvi02  ;             // 0xCC6A_0008
    SCRG_CTRL_CVI_CRG_CVI03_M23A0_T    crg_cvi03  ;             // 0xCC6A_000C
    SCRG_CTRL_CVI_CRG_CVI04_M23A0_T    crg_cvi04  ;             // 0xCC6A_0010
}SCRG_CTRL_CVI_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.2  KJH by LGSiCRDV V3.1C*/

