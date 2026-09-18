#ifndef _BND_CTRL_HDMI_REG_O26A0_H_
#define _BND_CTRL_HDMI_REG_O26A0_H_

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
    0xC877_2000    cvi_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmirx_prt1_phy_wr_sel:  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdmirx_prt2_phy_wr_sel:  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdmirx_prt3_phy_wr_sel:  1,    //      8
                              :  3,    //  11: 9 reserved
    reg_hdmirx_prt4_phy_wr_sel:  1,    //     12
                              : 19;    //  31:13 reserved
}BND_CTRL_HDMI_CVI_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2004    cvi_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_earctx_apb_i2c_sel    :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_txclkdrv_hdmi_div2_enb:  1,    //      4
    reg_txclkdrv_hdmi_pdb     :  1,    //      5
                              : 26;    //   31:6 reserved
}BND_CTRL_HDMI_CVI_SYN_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2100    hdmi_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_hdmi_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_hdmi_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_HDMI_HDMI_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2104    hdmi_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_urf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_HDMI_HDMI_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2108    hdmi_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_rf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDMI_HDMI_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_210C    hdmi_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_srf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_HDMI_HDMI_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2110    hdmi_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_hdmi_sra_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_HDMI_HDMI_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2114    cvi_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_cvi_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_cvi_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_HDMI_CVI_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2118    cvi_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDMI_CVI_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_211C    cvi_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi_rf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_HDMI_CVI_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2120    cvi_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_cvi_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDMI_CVI_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2124    dsc_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_dsc_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_dsc_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_HDMI_DSC_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2128    dsc_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDMI_DSC_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_212C    dsc_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_dsc_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_HDMI_DSC_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_HDMI_CVI_SYN_00_O26A0_T    cvi_syn_00;             // 0xC877_2000
    BND_CTRL_HDMI_CVI_SYN_01_O26A0_T    cvi_syn_01;             // 0xC877_2004
    UINT32                             _rsvd_00[62];            // 0xC877_2008 ~ 0xC877_20FC
    BND_CTRL_HDMI_HDMI_MEM0_O26A0_T    hdmi_mem0  ;             // 0xC877_2100
    BND_CTRL_HDMI_HDMI_MEM1_O26A0_T    hdmi_mem1  ;             // 0xC877_2104
    BND_CTRL_HDMI_HDMI_MEM2_O26A0_T    hdmi_mem2  ;             // 0xC877_2108
    BND_CTRL_HDMI_HDMI_MEM3_O26A0_T    hdmi_mem3  ;             // 0xC877_210C
    BND_CTRL_HDMI_HDMI_MEM4_O26A0_T    hdmi_mem4  ;             // 0xC877_2110
    BND_CTRL_HDMI_CVI_MEM0_O26A0_T     cvi_mem0   ;             // 0xC877_2114
    BND_CTRL_HDMI_CVI_MEM1_O26A0_T     cvi_mem1   ;             // 0xC877_2118
    BND_CTRL_HDMI_CVI_MEM2_O26A0_T     cvi_mem2   ;             // 0xC877_211C
    BND_CTRL_HDMI_CVI_MEM3_O26A0_T     cvi_mem3   ;             // 0xC877_2120
    BND_CTRL_HDMI_DSC_MEM0_O26A0_T     dsc_mem0   ;             // 0xC877_2124
    BND_CTRL_HDMI_DSC_MEM1_O26A0_T     dsc_mem1   ;             // 0xC877_2128
    BND_CTRL_HDMI_DSC_MEM2_O26A0_T     dsc_mem2   ;             // 0xC877_212C
}BND_CTRL_HDMI_REG_O26A0_T;
/* 14 regs */

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

#define BND_CTRL_HDMI_CVI_SYN_00_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define BND_CTRL_HDMI_CVI_SYN_01_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define BND_CTRL_HDMI_HDMI_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x0100)
#define BND_CTRL_HDMI_HDMI_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0104)
#define BND_CTRL_HDMI_HDMI_MEM2_O26A0_T_OFF                 (BASEADDRESS+0x0108)
#define BND_CTRL_HDMI_HDMI_MEM3_O26A0_T_OFF                 (BASEADDRESS+0x010C)
#define BND_CTRL_HDMI_HDMI_MEM4_O26A0_T_OFF                 (BASEADDRESS+0x0110)
#define BND_CTRL_HDMI_CVI_MEM0_O26A0_T_OFF                  (BASEADDRESS+0x0114)
#define BND_CTRL_HDMI_CVI_MEM1_O26A0_T_OFF                  (BASEADDRESS+0x0118)
#define BND_CTRL_HDMI_CVI_MEM2_O26A0_T_OFF                  (BASEADDRESS+0x011C)
#define BND_CTRL_HDMI_CVI_MEM3_O26A0_T_OFF                  (BASEADDRESS+0x0120)
#define BND_CTRL_HDMI_DSC_MEM0_O26A0_T_OFF                  (BASEADDRESS+0x0124)
#define BND_CTRL_HDMI_DSC_MEM1_O26A0_T_OFF                  (BASEADDRESS+0x0128)
#define BND_CTRL_HDMI_DSC_MEM2_O26A0_T_OFF                  (BASEADDRESS+0x012C)

/*-----------------------------------------------------------------------------------------
    0xC877_2000    cvi_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmirx_prt1_phy_wr_sel: 1;    //  0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_hdmirx_prt2_phy_wr_sel: 1;    //  4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_hdmirx_prt3_phy_wr_sel: 1;    //  8
    UINT32 resvd02            :  3;    //  11: 9 reserved
    UINT32 reg_hdmirx_prt4_phy_wr_sel: 1;    //  12
    UINT32 resvd03            : 19;    //  31:13 reserved
    };
}BND_CTRL_HDMI_CVI_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2004    cvi_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_earctx_apb_i2c_sel: 1;    //    0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_txclkdrv_hdmi_div2_enb: 1;    //  4
    UINT32 reg_txclkdrv_hdmi_pdb: 1;    //     5
    UINT32 resvd01            : 26;    //   31:6 reserved
    };
}BND_CTRL_HDMI_CVI_SYN_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2100    hdmi_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_hdmi_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_hdmi_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_HDMI_HDMI_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2104    hdmi_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDMI_HDMI_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2108    hdmi_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_rf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDMI_HDMI_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_210C    hdmi_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDMI_HDMI_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2110    hdmi_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_hdmi_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDMI_HDMI_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2114    cvi_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_cvi_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_cvi_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_HDMI_CVI_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2118    cvi_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDMI_CVI_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_211C    cvi_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi_rf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_HDMI_CVI_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2120    cvi_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_cvi_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDMI_CVI_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2124    dsc_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dsc_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_dsc_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_dsc_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_HDMI_DSC_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_2128    dsc_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dsc_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDMI_DSC_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC877_212C    dsc_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_dsc_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_HDMI_DSC_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_hdmi Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_HDMI_CVI_SYN_00_O26A0_T    cvi_syn_00;             // 0xC877_2000
    BND_CTRL_HDMI_CVI_SYN_01_O26A0_T    cvi_syn_01;             // 0xC877_2004
    UINT32                             _rsvd_00[62];            // 0xC877_2008 ~ 0xC877_20FC
    BND_CTRL_HDMI_HDMI_MEM0_O26A0_T    hdmi_mem0  ;             // 0xC877_2100
    BND_CTRL_HDMI_HDMI_MEM1_O26A0_T    hdmi_mem1  ;             // 0xC877_2104
    BND_CTRL_HDMI_HDMI_MEM2_O26A0_T    hdmi_mem2  ;             // 0xC877_2108
    BND_CTRL_HDMI_HDMI_MEM3_O26A0_T    hdmi_mem3  ;             // 0xC877_210C
    BND_CTRL_HDMI_HDMI_MEM4_O26A0_T    hdmi_mem4  ;             // 0xC877_2110
    BND_CTRL_HDMI_CVI_MEM0_O26A0_T     cvi_mem0   ;             // 0xC877_2114
    BND_CTRL_HDMI_CVI_MEM1_O26A0_T     cvi_mem1   ;             // 0xC877_2118
    BND_CTRL_HDMI_CVI_MEM2_O26A0_T     cvi_mem2   ;             // 0xC877_211C
    BND_CTRL_HDMI_CVI_MEM3_O26A0_T     cvi_mem3   ;             // 0xC877_2120
    BND_CTRL_HDMI_DSC_MEM0_O26A0_T     dsc_mem0   ;             // 0xC877_2124
    BND_CTRL_HDMI_DSC_MEM1_O26A0_T     dsc_mem1   ;             // 0xC877_2128
    BND_CTRL_HDMI_DSC_MEM2_O26A0_T     dsc_mem2   ;             // 0xC877_212C
}BND_CTRL_HDMI_REG_O26A0_T;
/* 14 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_HDMI_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

