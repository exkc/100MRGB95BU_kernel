#ifndef _MCRG_CTRL_WOV_REG_H_
#define _MCRG_CTRL_WOV_REG_H_

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
    0x5A_0000    crg_main_wov00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MCRG_CTRL_WOV_CRG_MAIN_WOV00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0004    crg_main_wov01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MCRG_CTRL_WOV_CRG_MAIN_WOV01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0008    crg_main_wov02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov_apll_f_clk_inv_sel:  1,    //      0
    reg_wov_aud_hmr1spdifclk_inv_sel: 1,    //  1
    reg_wov_aud_hmr2spdifclk_inv_sel: 1,    //  2
    reg_wov_aud_hmr3spdifclk_inv_sel: 1,    //  3
    reg_wov_aud_hmr4spdifclk_inv_sel: 1,    //  4
    reg_wov_earc_frpll_clk_inv_sel: 1,    //   5
    reg_wov_fs00_clk_inv_sel  :  1,    //      6
                              : 25;    //   31:7 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_000C    crg_main_wov03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aclk_out_sel0_div     :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0010    crg_main_wov04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aclk_out_sel0_src     :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0014    crg_main_wov05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aclk_out_sel1_div     :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0018    crg_main_wov06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aclk_out_sel1_src     :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_001C    crg_main_wov07 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_WOV_CRG_MAIN_WOV07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0020    crg_main_wov08 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0024    crg_main_wov09 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0028    crg_main_wov10 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto0_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_002C    crg_main_wov11 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_WOV_CRG_MAIN_WOV11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0030    crg_main_wov12 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0034    crg_main_wov13 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0038    crg_main_wov14 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto1_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_003C    crg_main_wov15 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_add_value_pos   : 32;    //  31: 0
}MCRG_CTRL_WOV_CRG_MAIN_WOV15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0040    crg_main_wov16 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_err_value_pos   : 12,    //  11: 0
                              : 20;    //  31:12 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV16_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0044    crg_main_wov17 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_swrst_adto      :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV17_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0048    crg_main_wov18 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_adto2_sync_update     :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV18_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_004C    crg_main_wov19 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_clk_out_0_inv_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV19_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0050    crg_main_wov20 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_clk_out_1_inv_sel :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV20_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0054    crg_main_wov21 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_clk_out_sel       :  1,    //      0
                              : 31;    //   31:1 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV21_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0058    crg_main_wov22 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel0_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV22_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_005C    crg_main_wov23 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel0_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV23_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0060    crg_main_wov24 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel1_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV24_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0064    crg_main_wov25 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel1_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV25_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0068    crg_main_wov26 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel2_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV26_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_006C    crg_main_wov27 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel2_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV27_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0070    crg_main_wov28 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel3_aclk_div         :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV28_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0074    crg_main_wov29 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel3_aclk_src         :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV29_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0078    crg_main_wov30 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_wov__pdm_div_sel      :  3,    //   2: 0
                              : 29;    //   31:3 reserved
}MCRG_CTRL_WOV_CRG_MAIN_WOV30_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_main_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_WOV_CRG_MAIN_WOV00_O22A0_T    crg_main_wov00;      // 0x5A_0000
    MCRG_CTRL_WOV_CRG_MAIN_WOV01_O22A0_T    crg_main_wov01;      // 0x5A_0004
    MCRG_CTRL_WOV_CRG_MAIN_WOV02_O22A0_T    crg_main_wov02;      // 0x5A_0008
    MCRG_CTRL_WOV_CRG_MAIN_WOV03_O22A0_T    crg_main_wov03;      // 0x5A_000C
    MCRG_CTRL_WOV_CRG_MAIN_WOV04_O22A0_T    crg_main_wov04;      // 0x5A_0010
    MCRG_CTRL_WOV_CRG_MAIN_WOV05_O22A0_T    crg_main_wov05;      // 0x5A_0014
    MCRG_CTRL_WOV_CRG_MAIN_WOV06_O22A0_T    crg_main_wov06;      // 0x5A_0018
    MCRG_CTRL_WOV_CRG_MAIN_WOV07_O22A0_T    crg_main_wov07;      // 0x5A_001C
    MCRG_CTRL_WOV_CRG_MAIN_WOV08_O22A0_T    crg_main_wov08;      // 0x5A_0020
    MCRG_CTRL_WOV_CRG_MAIN_WOV09_O22A0_T    crg_main_wov09;      // 0x5A_0024
    MCRG_CTRL_WOV_CRG_MAIN_WOV10_O22A0_T    crg_main_wov10;      // 0x5A_0028
    MCRG_CTRL_WOV_CRG_MAIN_WOV11_O22A0_T    crg_main_wov11;      // 0x5A_002C
    MCRG_CTRL_WOV_CRG_MAIN_WOV12_O22A0_T    crg_main_wov12;      // 0x5A_0030
    MCRG_CTRL_WOV_CRG_MAIN_WOV13_O22A0_T    crg_main_wov13;      // 0x5A_0034
    MCRG_CTRL_WOV_CRG_MAIN_WOV14_O22A0_T    crg_main_wov14;      // 0x5A_0038
    MCRG_CTRL_WOV_CRG_MAIN_WOV15_O22A0_T    crg_main_wov15;      // 0x5A_003C
    MCRG_CTRL_WOV_CRG_MAIN_WOV16_O22A0_T    crg_main_wov16;      // 0x5A_0040
    MCRG_CTRL_WOV_CRG_MAIN_WOV17_O22A0_T    crg_main_wov17;      // 0x5A_0044
    MCRG_CTRL_WOV_CRG_MAIN_WOV18_O22A0_T    crg_main_wov18;      // 0x5A_0048
    MCRG_CTRL_WOV_CRG_MAIN_WOV19_O22A0_T    crg_main_wov19;      // 0x5A_004C
    MCRG_CTRL_WOV_CRG_MAIN_WOV20_O22A0_T    crg_main_wov20;      // 0x5A_0050
    MCRG_CTRL_WOV_CRG_MAIN_WOV21_O22A0_T    crg_main_wov21;      // 0x5A_0054
    MCRG_CTRL_WOV_CRG_MAIN_WOV22_O22A0_T    crg_main_wov22;      // 0x5A_0058
    MCRG_CTRL_WOV_CRG_MAIN_WOV23_O22A0_T    crg_main_wov23;      // 0x5A_005C
    MCRG_CTRL_WOV_CRG_MAIN_WOV24_O22A0_T    crg_main_wov24;      // 0x5A_0060
    MCRG_CTRL_WOV_CRG_MAIN_WOV25_O22A0_T    crg_main_wov25;      // 0x5A_0064
    MCRG_CTRL_WOV_CRG_MAIN_WOV26_O22A0_T    crg_main_wov26;      // 0x5A_0068
    MCRG_CTRL_WOV_CRG_MAIN_WOV27_O22A0_T    crg_main_wov27;      // 0x5A_006C
    MCRG_CTRL_WOV_CRG_MAIN_WOV28_O22A0_T    crg_main_wov28;      // 0x5A_0070
    MCRG_CTRL_WOV_CRG_MAIN_WOV29_O22A0_T    crg_main_wov29;      // 0x5A_0074
    MCRG_CTRL_WOV_CRG_MAIN_WOV30_O22A0_T    crg_main_wov30;      // 0x5A_0078
}MCRG_CTRL_WOV_REG_O22A0_T;
/* 31 regs */

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

#define MCRG_CTRL_WOV_CRG_MAIN_WOV00_O22A0_T_OFF             (BASEADDRESS+0x0000)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV01_O22A0_T_OFF             (BASEADDRESS+0x0004)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV02_O22A0_T_OFF             (BASEADDRESS+0x0008)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV03_O22A0_T_OFF             (BASEADDRESS+0x000C)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV04_O22A0_T_OFF             (BASEADDRESS+0x0010)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV05_O22A0_T_OFF             (BASEADDRESS+0x0014)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV06_O22A0_T_OFF             (BASEADDRESS+0x0018)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV07_O22A0_T_OFF             (BASEADDRESS+0x001C)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV08_O22A0_T_OFF             (BASEADDRESS+0x0020)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV09_O22A0_T_OFF             (BASEADDRESS+0x0024)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV10_O22A0_T_OFF             (BASEADDRESS+0x0028)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV11_O22A0_T_OFF             (BASEADDRESS+0x002C)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV12_O22A0_T_OFF             (BASEADDRESS+0x0030)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV13_O22A0_T_OFF             (BASEADDRESS+0x0034)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV14_O22A0_T_OFF             (BASEADDRESS+0x0038)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV15_O22A0_T_OFF             (BASEADDRESS+0x003C)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV16_O22A0_T_OFF             (BASEADDRESS+0x0040)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV17_O22A0_T_OFF             (BASEADDRESS+0x0044)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV18_O22A0_T_OFF             (BASEADDRESS+0x0048)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV19_O22A0_T_OFF             (BASEADDRESS+0x004C)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV20_O22A0_T_OFF             (BASEADDRESS+0x0050)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV21_O22A0_T_OFF             (BASEADDRESS+0x0054)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV22_O22A0_T_OFF             (BASEADDRESS+0x0058)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV23_O22A0_T_OFF             (BASEADDRESS+0x005C)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV24_O22A0_T_OFF             (BASEADDRESS+0x0060)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV25_O22A0_T_OFF             (BASEADDRESS+0x0064)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV26_O22A0_T_OFF             (BASEADDRESS+0x0068)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV27_O22A0_T_OFF             (BASEADDRESS+0x006C)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV28_O22A0_T_OFF             (BASEADDRESS+0x0070)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV29_O22A0_T_OFF             (BASEADDRESS+0x0074)
#define MCRG_CTRL_WOV_CRG_MAIN_WOV30_O22A0_T_OFF             (BASEADDRESS+0x0078)

/*-----------------------------------------------------------------------------------------
    0x5A_0000    crg_main_wov00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0004    crg_main_wov01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0008    crg_main_wov02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_wov_apll_f_clk_inv_sel: 1;    //  0
    UINT32 reg_wov_aud_hmr1spdifclk_inv_sel: 1;    //  1
    UINT32 reg_wov_aud_hmr2spdifclk_inv_sel: 1;    //  2
    UINT32 reg_wov_aud_hmr3spdifclk_inv_sel: 1;    //  3
    UINT32 reg_wov_aud_hmr4spdifclk_inv_sel: 1;    //  4
    UINT32 reg_wov_earc_frpll_clk_inv_sel: 1;    //  5
    UINT32 reg_wov_fs00_clk_inv_sel: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_000C    crg_main_wov03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aclk_out_sel0_div: 3;    //  2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0010    crg_main_wov04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aclk_out_sel0_src: 4;    //  3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0014    crg_main_wov05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aclk_out_sel1_div: 3;    //  2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0018    crg_main_wov06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aclk_out_sel1_src: 4;    //  3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_001C    crg_main_wov07 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV07_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0020    crg_main_wov08 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV08_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0024    crg_main_wov09 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV09_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0028    crg_main_wov10 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto0_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV10_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_002C    crg_main_wov11 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV11_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0030    crg_main_wov12 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV12_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0034    crg_main_wov13 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV13_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0038    crg_main_wov14 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto1_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV14_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_003C    crg_main_wov15 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_add_value_pos: 32;    //  31:0
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV15_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0040    crg_main_wov16 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_err_value_pos: 12;    //  11:0
    UINT32 resvd00            : 20;    //  31:12 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV16_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0044    crg_main_wov17 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_swrst_adto: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV17_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0048    crg_main_wov18 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_adto2_sync_update: 1;    //     0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV18_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_004C    crg_main_wov19 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_clk_out_0_inv_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV19_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0050    crg_main_wov20 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_clk_out_1_inv_sel: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV20_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0054    crg_main_wov21 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_clk_out_sel:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV21_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0058    crg_main_wov22 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel0_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV22_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_005C    crg_main_wov23 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel0_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV23_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0060    crg_main_wov24 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel1_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV24_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0064    crg_main_wov25 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel1_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV25_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0068    crg_main_wov26 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel2_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV26_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_006C    crg_main_wov27 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel2_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV27_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0070    crg_main_wov28 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel3_aclk_div  :  3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV28_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0074    crg_main_wov29 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel3_aclk_src  :  4;    //   3: 0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV29_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5A_0078    crg_main_wov30 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_wov__pdm_div_sel: 3;    //   2: 0
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}MCRG_CTRL_WOV_CRG_MAIN_WOV30_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_main_wov Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MCRG_CTRL_WOV_CRG_MAIN_WOV00_O22A0_T    crg_main_wov00;      // 0x5A_0000
    MCRG_CTRL_WOV_CRG_MAIN_WOV01_O22A0_T    crg_main_wov01;      // 0x5A_0004
    MCRG_CTRL_WOV_CRG_MAIN_WOV02_O22A0_T    crg_main_wov02;      // 0x5A_0008
    MCRG_CTRL_WOV_CRG_MAIN_WOV03_O22A0_T    crg_main_wov03;      // 0x5A_000C
    MCRG_CTRL_WOV_CRG_MAIN_WOV04_O22A0_T    crg_main_wov04;      // 0x5A_0010
    MCRG_CTRL_WOV_CRG_MAIN_WOV05_O22A0_T    crg_main_wov05;      // 0x5A_0014
    MCRG_CTRL_WOV_CRG_MAIN_WOV06_O22A0_T    crg_main_wov06;      // 0x5A_0018
    MCRG_CTRL_WOV_CRG_MAIN_WOV07_O22A0_T    crg_main_wov07;      // 0x5A_001C
    MCRG_CTRL_WOV_CRG_MAIN_WOV08_O22A0_T    crg_main_wov08;      // 0x5A_0020
    MCRG_CTRL_WOV_CRG_MAIN_WOV09_O22A0_T    crg_main_wov09;      // 0x5A_0024
    MCRG_CTRL_WOV_CRG_MAIN_WOV10_O22A0_T    crg_main_wov10;      // 0x5A_0028
    MCRG_CTRL_WOV_CRG_MAIN_WOV11_O22A0_T    crg_main_wov11;      // 0x5A_002C
    MCRG_CTRL_WOV_CRG_MAIN_WOV12_O22A0_T    crg_main_wov12;      // 0x5A_0030
    MCRG_CTRL_WOV_CRG_MAIN_WOV13_O22A0_T    crg_main_wov13;      // 0x5A_0034
    MCRG_CTRL_WOV_CRG_MAIN_WOV14_O22A0_T    crg_main_wov14;      // 0x5A_0038
    MCRG_CTRL_WOV_CRG_MAIN_WOV15_O22A0_T    crg_main_wov15;      // 0x5A_003C
    MCRG_CTRL_WOV_CRG_MAIN_WOV16_O22A0_T    crg_main_wov16;      // 0x5A_0040
    MCRG_CTRL_WOV_CRG_MAIN_WOV17_O22A0_T    crg_main_wov17;      // 0x5A_0044
    MCRG_CTRL_WOV_CRG_MAIN_WOV18_O22A0_T    crg_main_wov18;      // 0x5A_0048
    MCRG_CTRL_WOV_CRG_MAIN_WOV19_O22A0_T    crg_main_wov19;      // 0x5A_004C
    MCRG_CTRL_WOV_CRG_MAIN_WOV20_O22A0_T    crg_main_wov20;      // 0x5A_0050
    MCRG_CTRL_WOV_CRG_MAIN_WOV21_O22A0_T    crg_main_wov21;      // 0x5A_0054
    MCRG_CTRL_WOV_CRG_MAIN_WOV22_O22A0_T    crg_main_wov22;      // 0x5A_0058
    MCRG_CTRL_WOV_CRG_MAIN_WOV23_O22A0_T    crg_main_wov23;      // 0x5A_005C
    MCRG_CTRL_WOV_CRG_MAIN_WOV24_O22A0_T    crg_main_wov24;      // 0x5A_0060
    MCRG_CTRL_WOV_CRG_MAIN_WOV25_O22A0_T    crg_main_wov25;      // 0x5A_0064
    MCRG_CTRL_WOV_CRG_MAIN_WOV26_O22A0_T    crg_main_wov26;      // 0x5A_0068
    MCRG_CTRL_WOV_CRG_MAIN_WOV27_O22A0_T    crg_main_wov27;      // 0x5A_006C
    MCRG_CTRL_WOV_CRG_MAIN_WOV28_O22A0_T    crg_main_wov28;      // 0x5A_0070
    MCRG_CTRL_WOV_CRG_MAIN_WOV29_O22A0_T    crg_main_wov29;      // 0x5A_0074
    MCRG_CTRL_WOV_CRG_MAIN_WOV30_O22A0_T    crg_main_wov30;      // 0x5A_0078
}MCRG_CTRL_WOV_REG_O22A0_T;
/* 31 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.14  KJH by LGSiCRDV V3.1C*/

