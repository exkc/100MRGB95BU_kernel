#ifndef _SCRG_CTRL_ME_M23A0_REG_H_
#define _SCRG_CTRL_ME_M23A0_REG_H_

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
    0xCC9D_0000    crg_me00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_ME_CRG_ME00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9D_0004    crg_me01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_ME_CRG_ME01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9D_0008    crg_me02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_me0_clk_gate_en   :  1,    //      0
    reg_axi_me0_clk_gate_en   :  1,    //      1
    reg_de_clk_gate_en        :  1,    //      2
    reg_me0_clk_gate_en       :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_ME_CRG_ME02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9D_000C    crg_me03 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_me0_n    :  1,    //      0
    reg_soft_rst_axi_me0_n    :  1,    //      1
    reg_soft_rst_de_n         :  1,    //      2
    reg_soft_rst_f_me_0_de_bnd_n: 1,    //     3
    reg_soft_rst_me0_n        :  1,    //      4
    reg_soft_rst_p_me_0_axi_bnd_n: 1,    //    5
    reg_soft_rst_x_me_0_axi_bnd_n: 1,    //    6
    reg_soft_rst_x_me_0_axi_n :  1,    //      7
                              : 24;    //   31:8 reserved
}SCRG_CTRL_ME_CRG_ME03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9D_0010    crg_me04 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_me0_clk_sel       :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_axi_me0_clk_sel       :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_me0_clk_sel           :  1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_ME_CRG_ME04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME_CRG_ME00_M23A0_T      crg_me00   ;             // 0xCC9D_0000
    SCRG_CTRL_ME_CRG_ME01_M23A0_T      crg_me01   ;             // 0xCC9D_0004
    SCRG_CTRL_ME_CRG_ME02_M23A0_T      crg_me02   ;             // 0xCC9D_0008
    SCRG_CTRL_ME_CRG_ME03_M23A0_T      crg_me03   ;             // 0xCC9D_000C
    SCRG_CTRL_ME_CRG_ME04_M23A0_T      crg_me04   ;             // 0xCC9D_0010
}SCRG_CTRL_ME_REG_M23A0_T;
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

#define SCRG_CTRL_ME_CRG_ME00_M23A0_T_OFF                   (BASEADDRESS+0x0000)
#define SCRG_CTRL_ME_CRG_ME01_M23A0_T_OFF                   (BASEADDRESS+0x0004)
#define SCRG_CTRL_ME_CRG_ME02_M23A0_T_OFF                   (BASEADDRESS+0x0008)
#define SCRG_CTRL_ME_CRG_ME03_M23A0_T_OFF                   (BASEADDRESS+0x000C)
#define SCRG_CTRL_ME_CRG_ME04_M23A0_T_OFF                   (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC9D_0000    crg_me00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_ME_CRG_ME00_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9D_0004    crg_me01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_ME_CRG_ME01_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9D_0008    crg_me02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_me0_clk_gate_en: 1;    //   0
    UINT32 reg_axi_me0_clk_gate_en: 1;    //   1
    UINT32 reg_de_clk_gate_en :  1;    //      2
    UINT32 reg_me0_clk_gate_en:  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_ME_CRG_ME02_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9D_000C    crg_me03 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_me0_n: 1;    //    0
    UINT32 reg_soft_rst_axi_me0_n: 1;    //    1
    UINT32 reg_soft_rst_de_n  :  1;    //      2
    UINT32 reg_soft_rst_f_me_0_de_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_me0_n :  1;    //      4
    UINT32 reg_soft_rst_p_me_0_axi_bnd_n: 1;    //  5
    UINT32 reg_soft_rst_x_me_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_me_0_axi_n: 1;    //  7
    UINT32 resvd00            : 24;    //   31:8 reserved
    };
}SCRG_CTRL_ME_CRG_ME03_M23A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC9D_0010    crg_me04 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_me0_clk_sel:  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_axi_me0_clk_sel:  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_me0_clk_sel    :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_ME_CRG_ME04_M23A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_me Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_ME_CRG_ME00_M23A0_T      crg_me00   ;             // 0xCC9D_0000
    SCRG_CTRL_ME_CRG_ME01_M23A0_T      crg_me01   ;             // 0xCC9D_0004
    SCRG_CTRL_ME_CRG_ME02_M23A0_T      crg_me02   ;             // 0xCC9D_0008
    SCRG_CTRL_ME_CRG_ME03_M23A0_T      crg_me03   ;             // 0xCC9D_000C
    SCRG_CTRL_ME_CRG_ME04_M23A0_T      crg_me04   ;             // 0xCC9D_0010
}SCRG_CTRL_ME_REG_M23A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'M23_CRG_SUB_Register_Manual.xlsx'  2022.3.3  KJH by LGSiCRDV V3.1C*/

