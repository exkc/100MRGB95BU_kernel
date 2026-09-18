#ifndef _SCRG_CTRL_VENC_REG_H_
#define _SCRG_CTRL_VENC_REG_H_

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
    0x5F_0000    crg_venc00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VENC_CRG_VENC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0004    crg_venc01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VENC_CRG_VENC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0008    crg_venc02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ve_apb_clk_gate_en    :  1,    //      0
    reg_veclk_gate_en         :  1,    //      1
                              : 30;    //   31:2 reserved
}SCRG_CTRL_VENC_CRG_VENC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_000C    crg_venc03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_f_te_0_ve_apb_bnd_n: 1,    //  0
    reg_soft_rst_f_te_1_ve_apb_bnd_n: 1,    //  1
    reg_soft_rst_p_venc_0_axi_bnd_n: 1,    //  2
    reg_soft_rst_ve_apb_n     :  1,    //      3
    reg_soft_rst_ve_n         :  1,    //      4
    reg_soft_rst_x_venc_0_axi_bnd_n: 1,    //  5
    reg_soft_rst_x_venc_0_axi_n: 1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_VENC_CRG_VENC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0010    crg_venc04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_ipw_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ve_apb_clk_sel        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_veclk_sel             :  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VENC_CRG_VENC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0014    crg_venc05 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ve_apb_clk_skip_ctrl  :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VENC_CRG_VENC05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0018    crg_venc06 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_veclk_skip_ctrl       :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VENC_CRG_VENC06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VENC_CRG_VENC00_O22A0_T        crg_venc00 ;             // 0x5F_0000
    SCRG_CTRL_VENC_CRG_VENC01_O22A0_T        crg_venc01 ;             // 0x5F_0004
    SCRG_CTRL_VENC_CRG_VENC02_O22A0_T        crg_venc02 ;             // 0x5F_0008
    SCRG_CTRL_VENC_CRG_VENC03_O22A0_T        crg_venc03 ;             // 0x5F_000C
    SCRG_CTRL_VENC_CRG_VENC04_O22A0_T        crg_venc04 ;             // 0x5F_0010
    SCRG_CTRL_VENC_CRG_VENC05_O22A0_T        crg_venc05 ;             // 0x5F_0014
    SCRG_CTRL_VENC_CRG_VENC06_O22A0_T        crg_venc06 ;             // 0x5F_0018
}SCRG_CTRL_VENC_REG_O22A0_T;
/* 7 regs */

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

#define SCRG_CTRL_VENC_CRG_VENC00_O22A0_T_OFF                     (BASEADDRESS+0x0000)
#define SCRG_CTRL_VENC_CRG_VENC01_O22A0_T_OFF                     (BASEADDRESS+0x0004)
#define SCRG_CTRL_VENC_CRG_VENC02_O22A0_T_OFF                     (BASEADDRESS+0x0008)
#define SCRG_CTRL_VENC_CRG_VENC03_O22A0_T_OFF                     (BASEADDRESS+0x000C)
#define SCRG_CTRL_VENC_CRG_VENC04_O22A0_T_OFF                     (BASEADDRESS+0x0010)
#define SCRG_CTRL_VENC_CRG_VENC05_O22A0_T_OFF                     (BASEADDRESS+0x0014)
#define SCRG_CTRL_VENC_CRG_VENC06_O22A0_T_OFF                     (BASEADDRESS+0x0018)

/*-----------------------------------------------------------------------------------------
    0x5F_0000    crg_venc00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VENC_CRG_VENC00_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0004    crg_venc01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VENC_CRG_VENC01_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0008    crg_venc02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ve_apb_clk_gate_en: 1;    //    0
    UINT32 reg_veclk_gate_en  :  1;    //      1
    UINT32 resvd00            : 30;    //   31:2 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC02_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_000C    crg_venc03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_f_te_0_ve_apb_bnd_n: 1;    //  0
    UINT32 reg_soft_rst_f_te_1_ve_apb_bnd_n: 1;    //  1
    UINT32 reg_soft_rst_p_venc_0_axi_bnd_n: 1;    //  2
    UINT32 reg_soft_rst_ve_apb_n: 1;    //     3
    UINT32 reg_soft_rst_ve_n  :  1;    //      4
    UINT32 reg_soft_rst_x_venc_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_venc_0_axi_n: 1;    //  6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC03_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0010    crg_venc04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_ipw_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_ve_apb_clk_sel :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_veclk_sel      :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC04_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0014    crg_venc05 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ve_apb_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC05_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x5F_0018    crg_venc06 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_veclk_skip_ctrl:  9;    //   8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VENC_CRG_VENC06_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_venc Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VENC_CRG_VENC00_O22A0_T        crg_venc00 ;             // 0x5F_0000
    SCRG_CTRL_VENC_CRG_VENC01_O22A0_T        crg_venc01 ;             // 0x5F_0004
    SCRG_CTRL_VENC_CRG_VENC02_O22A0_T        crg_venc02 ;             // 0x5F_0008
    SCRG_CTRL_VENC_CRG_VENC03_O22A0_T        crg_venc03 ;             // 0x5F_000C
    SCRG_CTRL_VENC_CRG_VENC04_O22A0_T        crg_venc04 ;             // 0x5F_0010
    SCRG_CTRL_VENC_CRG_VENC05_O22A0_T        crg_venc05 ;             // 0x5F_0014
    SCRG_CTRL_VENC_CRG_VENC06_O22A0_T        crg_venc06 ;             // 0x5F_0018
}SCRG_CTRL_VENC_REG_O22A0_T;
/* 7 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

