#ifndef _SCRG_CTRL_DNNR_REG_O24A0_H_
#define _SCRG_CTRL_DNNR_REG_O24A0_H_

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
    0xCC69_0000    crg_dnnr0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved             : 32;    //  31: 0
}SCRG_CTRL_DNNR_CRG_DNNR0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC69_0004    crg_dnnr1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    test_reserved_ro          : 32;    //  31: 0
}SCRG_CTRL_DNNR_CRG_DNNR1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC69_0008    crg_dnnr2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_nr_clk_gate_en    :  1,    //      0
    reg_axi_nr_clk_gate_en    :  1,    //      1
    reg_mem_nr_clk_gate_en    :  1,    //      2
    reg_nr_clk_gate_en        :  1,    //      3
                              : 28;    //   31:4 reserved
}SCRG_CTRL_DNNR_CRG_DNNR2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC69_000C    crg_dnnr3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_soft_rst_apb_nr_n     :  1,    //      0
    reg_soft_rst_axi_nr_n     :  1,    //      1
    reg_soft_rst_gmau_nr_n    :  1,    //      2
    reg_soft_rst_h_dnnr_0_nr_bnd_n: 1,    //   3
    reg_soft_rst_h_sre_1_nr_bnd_n: 1,    //    4
    reg_soft_rst_nr_n         :  1,    //      5
    reg_soft_rst_p_dnnr_0_axi_bnd_n: 1,    //  6
    reg_soft_rst_x_dnnr_0_axi_bnd_n: 1,    //  7
    reg_soft_rst_x_dnnr_0_axi_n: 1,    //      8
                              : 23;    //   31:9 reserved
}SCRG_CTRL_DNNR_CRG_DNNR3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC69_0010    crg_dnnr4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_apb_nr_clk_sel        :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_axi_nr_clk_sel        :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_mem_nr_clk_sel        :  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_nr_clk_sel            :  1,    //     12
                              : 19;    //  31:13 reserved
}SCRG_CTRL_DNNR_CRG_DNNR4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dnnr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNNR_CRG_DNNR0_O24A0_T    crg_dnnr0 ;             // 0xCC69_0000
    SCRG_CTRL_DNNR_CRG_DNNR1_O24A0_T    crg_dnnr1 ;             // 0xCC69_0004
    SCRG_CTRL_DNNR_CRG_DNNR2_O24A0_T    crg_dnnr2 ;             // 0xCC69_0008
    SCRG_CTRL_DNNR_CRG_DNNR3_O24A0_T    crg_dnnr3 ;             // 0xCC69_000C
    SCRG_CTRL_DNNR_CRG_DNNR4_O24A0_T    crg_dnnr4 ;             // 0xCC69_0010
}SCRG_CTRL_DNNR_REG_O24A0_T;
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

#define SCRG_CTRL_DNNR_CRG_DNNR0_O24A0_T_OFF                (BASEADDRESS+0x0000)
#define SCRG_CTRL_DNNR_CRG_DNNR1_O24A0_T_OFF                (BASEADDRESS+0x0004)
#define SCRG_CTRL_DNNR_CRG_DNNR2_O24A0_T_OFF                (BASEADDRESS+0x0008)
#define SCRG_CTRL_DNNR_CRG_DNNR3_O24A0_T_OFF                (BASEADDRESS+0x000C)
#define SCRG_CTRL_DNNR_CRG_DNNR4_O24A0_T_OFF                (BASEADDRESS+0x0010)

/*-----------------------------------------------------------------------------------------
    0xCC69_0000    crg_dnnr0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved      : 32;    //  31: 0
    };
}SCRG_CTRL_DNNR_CRG_DNNR0_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC69_0004    crg_dnnr1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 test_reserved_ro   : 32;    //  31: 0
    };
}SCRG_CTRL_DNNR_CRG_DNNR1_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC69_0008    crg_dnnr2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_nr_clk_gate_en: 1;    //    0
    UINT32 reg_axi_nr_clk_gate_en: 1;    //    1
    UINT32 reg_mem_nr_clk_gate_en: 1;    //    2
    UINT32 reg_nr_clk_gate_en :  1;    //      3
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}SCRG_CTRL_DNNR_CRG_DNNR2_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC69_000C    crg_dnnr3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_soft_rst_apb_nr_n: 1;    //     0
    UINT32 reg_soft_rst_axi_nr_n: 1;    //     1
    UINT32 reg_soft_rst_gmau_nr_n: 1;    //    2
    UINT32 reg_soft_rst_h_dnnr_0_nr_bnd_n: 1;    //  3
    UINT32 reg_soft_rst_h_sre_1_nr_bnd_n: 1;    //  4
    UINT32 reg_soft_rst_nr_n  :  1;    //      5
    UINT32 reg_soft_rst_p_dnnr_0_axi_bnd_n: 1;    //  6
    UINT32 reg_soft_rst_x_dnnr_0_axi_bnd_n: 1;    //  7
    UINT32 reg_soft_rst_x_dnnr_0_axi_n: 1;    //  8
    UINT32 resvd00            : 23;    //   31:9 reserved
    };
}SCRG_CTRL_DNNR_CRG_DNNR3_O24A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC69_0010    crg_dnnr4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_apb_nr_clk_sel :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_axi_nr_clk_sel :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_mem_nr_clk_sel :  1;    //      8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_nr_clk_sel     :  1;    //     12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}SCRG_CTRL_DNNR_CRG_DNNR4_O24A0_T;

/*-----------------------------------------------------------------------------------------
    scrg_ctrl_dnnr Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    SCRG_CTRL_DNNR_CRG_DNNR0_O24A0_T    crg_dnnr0 ;             // 0xCC69_0000
    SCRG_CTRL_DNNR_CRG_DNNR1_O24A0_T    crg_dnnr1 ;             // 0xCC69_0004
    SCRG_CTRL_DNNR_CRG_DNNR2_O24A0_T    crg_dnnr2 ;             // 0xCC69_0008
    SCRG_CTRL_DNNR_CRG_DNNR3_O24A0_T    crg_dnnr3 ;             // 0xCC69_000C
    SCRG_CTRL_DNNR_CRG_DNNR4_O24A0_T    crg_dnnr4 ;             // 0xCC69_0010
}SCRG_CTRL_DNNR_REG_O24A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif // _SCRG_CTRL_DNNR_REG_H_

/* from 'O24_CRG_SUB_Register_Manual.xlsx'  2023.3.30  KJH by LGSiCRDV V3.1C*/

