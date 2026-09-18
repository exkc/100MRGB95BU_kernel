#ifndef _SCRG_CTRL_VD3_REG_H_
#define _SCRG_CTRL_VD3_REG_H_

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
    0x59_0000    crg_vd300 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_VD3_CRG_VD300_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0004    crg_vd301 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_VD3_CRG_VD301_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0008    crg_vd302 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_gate_en       :  1,    //      0
    reg_av1_clk_gate_en       :  1,    //      1
    reg_axi0_clk_gate_en      :  1,    //      2
    reg_axi1_clk_gate_en      :  1,    //      3
    reg_bus_clk_gate_en       :  1,    //      4
    reg_mem_clk_gate_en       :  1,    //      5
    reg_msvc_clk_gate_en      :  1,    //      6
                              : 25;    //   31:7 reserved
}SCRG_CTRL_VD3_CRG_VD302_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_000C    crg_vd303 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_n        :  1,    //      0
    reg_soft_rst_av1_n        :  1,    //      1
    reg_soft_rst_axi0_n       :  1,    //      2
    reg_soft_rst_axi1_n       :  1,    //      3
    reg_soft_rst_bus_n        :  1,    //      4
    reg_soft_rst_mem_n        :  1,    //      5
    reg_soft_rst_msvc_n       :  1,    //      6
    reg_soft_rst_p_vd3_0_axi_bnd_n: 1,    //   7
    reg_soft_rst_p_vd3_1_axi_bnd_n: 1,    //   8
    reg_soft_rst_x_vd3_0_axi_bnd_n: 1,    //   9
    reg_soft_rst_x_vd3_0_axi_n:  1,    //     10
    reg_soft_rst_x_vd3_1_axi_bnd_n: 1,    //  11
    reg_soft_rst_x_vd3_1_axi_n:  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_VD3_CRG_VD303_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0010    crg_vd304 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mem_clk_sel           :  1,    //      0
                              : 31;    //   31:1 reserved
}SCRG_CTRL_VD3_CRG_VD304_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0014    crg_vd305 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD3_CRG_VD305_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0018    crg_vd306 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_av1_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD3_CRG_VD306_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_001C    crg_vd307 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi0_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD3_CRG_VD307_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0020    crg_vd308 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_axi1_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD3_CRG_VD308_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0024    crg_vd309 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_bus_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD3_CRG_VD309_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0028    crg_vd310 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_mem_clk_skip_ctrl     :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD3_CRG_VD310_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_002C    crg_vd311 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_msvc_clk_skip_ctrl    :  9,    //   8: 0
                              : 23;    //   31:9 reserved
}SCRG_CTRL_VD3_CRG_VD311_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vd3 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD3_CRG_VD300_O22A0_T          crg_vd300  ;             // 0x59_0000
    SCRG_CTRL_VD3_CRG_VD301_O22A0_T          crg_vd301  ;             // 0x59_0004
    SCRG_CTRL_VD3_CRG_VD302_O22A0_T          crg_vd302  ;             // 0x59_0008
    SCRG_CTRL_VD3_CRG_VD303_O22A0_T          crg_vd303  ;             // 0x59_000C
    SCRG_CTRL_VD3_CRG_VD304_O22A0_T          crg_vd304  ;             // 0x59_0010
    SCRG_CTRL_VD3_CRG_VD305_O22A0_T          crg_vd305  ;             // 0x59_0014
    SCRG_CTRL_VD3_CRG_VD306_O22A0_T          crg_vd306  ;             // 0x59_0018
    SCRG_CTRL_VD3_CRG_VD307_O22A0_T          crg_vd307  ;             // 0x59_001C
    SCRG_CTRL_VD3_CRG_VD308_O22A0_T          crg_vd308  ;             // 0x59_0020
    SCRG_CTRL_VD3_CRG_VD309_O22A0_T          crg_vd309  ;             // 0x59_0024
    SCRG_CTRL_VD3_CRG_VD310_O22A0_T          crg_vd310  ;             // 0x59_0028
    SCRG_CTRL_VD3_CRG_VD311_O22A0_T          crg_vd311  ;             // 0x59_002C
}SCRG_CTRL_VD3_REG_O22A0_T;
/* 12 regs */

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

#define SCRG_CTRL_VD3_CRG_VD300_O22A0_T_OFF                       (BASEADDRESS+0x0000)
#define SCRG_CTRL_VD3_CRG_VD301_O22A0_T_OFF                       (BASEADDRESS+0x0004)
#define SCRG_CTRL_VD3_CRG_VD302_O22A0_T_OFF                       (BASEADDRESS+0x0008)
#define SCRG_CTRL_VD3_CRG_VD303_O22A0_T_OFF                       (BASEADDRESS+0x000C)
#define SCRG_CTRL_VD3_CRG_VD304_O22A0_T_OFF                       (BASEADDRESS+0x0010)
#define SCRG_CTRL_VD3_CRG_VD305_O22A0_T_OFF                       (BASEADDRESS+0x0014)
#define SCRG_CTRL_VD3_CRG_VD306_O22A0_T_OFF                       (BASEADDRESS+0x0018)
#define SCRG_CTRL_VD3_CRG_VD307_O22A0_T_OFF                       (BASEADDRESS+0x001C)
#define SCRG_CTRL_VD3_CRG_VD308_O22A0_T_OFF                       (BASEADDRESS+0x0020)
#define SCRG_CTRL_VD3_CRG_VD309_O22A0_T_OFF                       (BASEADDRESS+0x0024)
#define SCRG_CTRL_VD3_CRG_VD310_O22A0_T_OFF                       (BASEADDRESS+0x0028)
#define SCRG_CTRL_VD3_CRG_VD311_O22A0_T_OFF                       (BASEADDRESS+0x002C)

/*-----------------------------------------------------------------------------------------
    0x59_0000    crg_vd300 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_VD3_CRG_VD300_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0004    crg_vd301 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_VD3_CRG_VD301_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0008    crg_vd302 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_gate_en:  1;    //      0
    UINT32 reg_av1_clk_gate_en:  1;    //      1
    UINT32 reg_axi0_clk_gate_en: 1;    //      2
    UINT32 reg_axi1_clk_gate_en: 1;    //      3
    UINT32 reg_bus_clk_gate_en:  1;    //      4
    UINT32 reg_mem_clk_gate_en:  1;    //      5
    UINT32 reg_msvc_clk_gate_en: 1;    //      6
    UINT32 resvd00            : 25;    //   31:7 reserved
    };
}SCRG_CTRL_VD3_CRG_VD302_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_000C    crg_vd303 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_n :  1;    //      0
    UINT32 reg_soft_rst_av1_n :  1;    //      1
    UINT32 reg_soft_rst_axi0_n:  1;    //      2
    UINT32 reg_soft_rst_axi1_n:  1;    //      3
    UINT32 reg_soft_rst_bus_n :  1;    //      4
    UINT32 reg_soft_rst_mem_n :  1;    //      5
    UINT32 reg_soft_rst_msvc_n:  1;    //      6
    UINT32 reg_soft_rst_p_vd3_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_p_vd3_1_axi_bnd_n: 1;    //  8
    UINT32 reg_soft_rst_x_vd3_0_axi_bnd_n: 1;    //  9
    UINT32 reg_soft_rst_x_vd3_0_axi_n: 1;    //  10
    UINT32 reg_soft_rst_x_vd3_1_axi_bnd_n: 1;    //  11
    UINT32 reg_soft_rst_x_vd3_1_axi_n: 1;    //  12
    UINT32 resvd00            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_VD3_CRG_VD303_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0010    crg_vd304 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mem_clk_sel    :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}SCRG_CTRL_VD3_CRG_VD304_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0014    crg_vd305 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD3_CRG_VD305_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0018    crg_vd306 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_av1_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD3_CRG_VD306_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_001C    crg_vd307 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi0_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD3_CRG_VD307_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0020    crg_vd308 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_axi1_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD3_CRG_VD308_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0024    crg_vd309 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_bus_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD3_CRG_VD309_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_0028    crg_vd310 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_mem_clk_skip_ctrl: 9;    //  8: 0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD3_CRG_VD310_O22A0_T;

/*-----------------------------------------------------------------------------------------
    0x59_002C    crg_vd311 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_msvc_clk_skip_ctrl: 9;    //  8:0
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_VD3_CRG_VD311_O22A0_T;

/*-----------------------------------------------------------------------------------------
    crg_vd3 Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_VD3_CRG_VD300_O22A0_T          crg_vd300  ;             // 0x59_0000
    SCRG_CTRL_VD3_CRG_VD301_O22A0_T          crg_vd301  ;             // 0x59_0004
    SCRG_CTRL_VD3_CRG_VD302_O22A0_T          crg_vd302  ;             // 0x59_0008
    SCRG_CTRL_VD3_CRG_VD303_O22A0_T          crg_vd303  ;             // 0x59_000C
    SCRG_CTRL_VD3_CRG_VD304_O22A0_T          crg_vd304  ;             // 0x59_0010
    SCRG_CTRL_VD3_CRG_VD305_O22A0_T          crg_vd305  ;             // 0x59_0014
    SCRG_CTRL_VD3_CRG_VD306_O22A0_T          crg_vd306  ;             // 0x59_0018
    SCRG_CTRL_VD3_CRG_VD307_O22A0_T          crg_vd307  ;             // 0x59_001C
    SCRG_CTRL_VD3_CRG_VD308_O22A0_T          crg_vd308  ;             // 0x59_0020
    SCRG_CTRL_VD3_CRG_VD309_O22A0_T          crg_vd309  ;             // 0x59_0024
    SCRG_CTRL_VD3_CRG_VD310_O22A0_T          crg_vd310  ;             // 0x59_0028
    SCRG_CTRL_VD3_CRG_VD311_O22A0_T          crg_vd311  ;             // 0x59_002C
}SCRG_CTRL_VD3_REG_O22A0_T;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif

/* from 'O22_CTOP_CRG_Register_Manual.xlsx'  2020.12.11  KJH by LGSiCRDV V3.1C*/

