#ifndef _MICOM_MCRG_CTRL_WOC_REG_O26A0_H_
#define _MICOM_MCRG_CTRL_WOC_REG_O26A0_H_

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
    0xF33A_0000    crg_main_woc000 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0004    crg_main_woc001 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0008    crg_main_woc002 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edid_gmac_rx_clk_inv_sel: 1,    //     0
    reg_edid_gmac_tx_clk_inv_sel: 1,    //     1
                              : 30;    //   31:2 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_000C    crg_main_woc003 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ion0_sel_clk_dly      :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0010    crg_main_woc004 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ion0_sel_clk_ext      :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0014    crg_main_woc005 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_sel_fb_clk_src        :  2,    //   1: 0
                              : 30;    //   31:2 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0018    crg_main_woc006 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_bypass_mode  :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_001C    crg_main_woc007 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_clk_sel      :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC007_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0020    crg_main_woc008 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_filter_margin_sel: 2,    //  1:0
                              : 30;    //   31:2 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC008_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0024    crg_main_woc009 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext1_invert_sel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC009_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0028    crg_main_woc010 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_bypass_mode  :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC010_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_002C    crg_main_woc011 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_clk_sel      :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC011_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0030    crg_main_woc012 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_filter_margin_sel: 2,    //  1:0
                              : 30;    //   31:2 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC012_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0034    crg_main_woc013 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_ext2_invert_sel   :  1,    //      0
                              : 31;    //   31:1 reserved
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC013_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_mcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC000_O26A0_T    crg_main_woc000;    // 0xF33A_0000
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC001_O26A0_T    crg_main_woc001;    // 0xF33A_0004
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC002_O26A0_T    crg_main_woc002;    // 0xF33A_0008
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC003_O26A0_T    crg_main_woc003;    // 0xF33A_000C
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC004_O26A0_T    crg_main_woc004;    // 0xF33A_0010
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC005_O26A0_T    crg_main_woc005;    // 0xF33A_0014
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC006_O26A0_T    crg_main_woc006;    // 0xF33A_0018
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC007_O26A0_T    crg_main_woc007;    // 0xF33A_001C
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC008_O26A0_T    crg_main_woc008;    // 0xF33A_0020
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC009_O26A0_T    crg_main_woc009;    // 0xF33A_0024
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC010_O26A0_T    crg_main_woc010;    // 0xF33A_0028
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC011_O26A0_T    crg_main_woc011;    // 0xF33A_002C
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC012_O26A0_T    crg_main_woc012;    // 0xF33A_0030
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC013_O26A0_T    crg_main_woc013;    // 0xF33A_0034
}MICOM_MCRG_CTRL_WOC_REG_O26A0_T;
/* 13 regs */

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

#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC000_O26A0_T_OFF     (BASEADDRESS+0x0000)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC001_O26A0_T_OFF     (BASEADDRESS+0x0004)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC002_O26A0_T_OFF     (BASEADDRESS+0x0008)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC003_O26A0_T_OFF     (BASEADDRESS+0x000C)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC004_O26A0_T_OFF     (BASEADDRESS+0x0010)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC005_O26A0_T_OFF     (BASEADDRESS+0x0014)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC006_O26A0_T_OFF     (BASEADDRESS+0x0018)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC007_O26A0_T_OFF     (BASEADDRESS+0x001C)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC008_O26A0_T_OFF     (BASEADDRESS+0x0020)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC009_O26A0_T_OFF     (BASEADDRESS+0x0024)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC010_O26A0_T_OFF     (BASEADDRESS+0x0028)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC011_O26A0_T_OFF     (BASEADDRESS+0x002C)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC012_O26A0_T_OFF     (BASEADDRESS+0x0030)
#define MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC013_O26A0_T_OFF     (BASEADDRESS+0x0034)

/*-----------------------------------------------------------------------------------------
    0xF33A_0000    crg_main_woc000 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC000_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0004    crg_main_woc001 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC001_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0008    crg_main_woc002 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edid_gmac_rx_clk_inv_sel: 1;    //  0
    UINT32 reg_edid_gmac_tx_clk_inv_sel: 1;    //  1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC002_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_000C    crg_main_woc003 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ion0_sel_clk_dly: 2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC003_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0010    crg_main_woc004 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ion0_sel_clk_ext: 2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC004_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0014    crg_main_woc005 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_sel_fb_clk_src : 2;    //   1: 0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC005_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0018    crg_main_woc007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_bypass_mode: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC006_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_001C    crg_main_woc007 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_clk_sel: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC007_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0020    crg_main_woc008 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_filter_margin_sel: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC008_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0024    crg_main_woc009 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext1_invert_sel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC009_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0028    crg_main_woc010 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_bypass_mode: 1;    //  0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC010_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_002C    crg_main_woc011 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_clk_sel: 1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC011_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0030    crg_main_woc012 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_filter_margin_sel: 2;    //  1:0
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC012_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xF33A_0034    crg_main_woc013 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_ext2_invert_sel: 1;    //   0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC013_O26A0_T;

/*-----------------------------------------------------------------------------------------
    micom_mcrg_ctrl_woc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC000_O26A0_T    crg_main_woc000;    // 0xF33A_0000
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC001_O26A0_T    crg_main_woc001;    // 0xF33A_0004
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC002_O26A0_T    crg_main_woc002;    // 0xF33A_0008
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC003_O26A0_T    crg_main_woc003;    // 0xF33A_000C
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC004_O26A0_T    crg_main_woc004;    // 0xF33A_0010
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC005_O26A0_T    crg_main_woc005;    // 0xF33A_0014
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC006_O26A0_T    crg_main_woc006;    // 0xF33A_0018
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC007_O26A0_T    crg_main_woc007;    // 0xF33A_001C
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC008_O26A0_T    crg_main_woc008;    // 0xF33A_0020
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC009_O26A0_T    crg_main_woc009;    // 0xF33A_0024
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC010_O26A0_T    crg_main_woc010;    // 0xF33A_0028
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC011_O26A0_T    crg_main_woc011;    // 0xF33A_002C
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC012_O26A0_T    crg_main_woc012;    // 0xF33A_0030
    MICOM_MCRG_CTRL_WOC_CRG_MAIN_WOC013_O26A0_T    crg_main_woc013;    // 0xF33A_0034
}MICOM_MCRG_CTRL_WOC_REG_O26A0_T;
/* 13 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_MICOM_MCRG_CTRL_WOC_REG_O26A0_H_

/* from 'O26_CRG_SUB_Register_Manual.xlsx'  2025.3.27  KJH by LGSiCRDV V3.1C*/

