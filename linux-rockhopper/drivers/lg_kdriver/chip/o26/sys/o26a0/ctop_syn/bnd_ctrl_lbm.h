#ifndef _BND_CTRL_LBM_REG_O26A0_H_
#define _BND_CTRL_LBM_REG_O26A0_H_

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
    0xC404_2100    lbus_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lbus_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_lbus_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_lbus_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_LBM_LBUS_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2104    lbus_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_lbus_urf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_LBM_LBUS_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2108    npp_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_npp_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_npp_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_npp_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_LBM_NPP_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_210C    npp_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_npp_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_LBM_NPP_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2110    npp_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_npp_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_LBM_NPP_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2114    gfx_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_gfx_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_gfx_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_LBM_GFX_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2118    gfx_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_gfx_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_LBM_GFX_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_211C    iommu_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_iommu_ls              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_iommu_ds              :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_iommu_sd              :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_LBM_IOMMU_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2120    iommu_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_iommu_urf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_LBM_IOMMU_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2124    iommu_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_iommu_srf_mem_ctrl    : 32;    //  31: 0
}BND_CTRL_LBM_IOMMU_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2128    tivvmsb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tivvmsb_ls            :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_tivvmsb_ds            :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_tivvmsb_sd            :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_LBM_TIVVMSB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_212C    tivvmsb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tivvmsb_urf_mem_ctrl  : 32;    //  31: 0
}BND_CTRL_LBM_TIVVMSB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2130    ddr0sb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ddr0sb_ls             :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ddr0sb_ds             :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_ddr0sb_sd             :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_LBM_DDR0SB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2134    ddr0sb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ddr0sb_urf_mem_ctrl   : 32;    //  31: 0
}BND_CTRL_LBM_DDR0SB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2138    ddr1sb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ddr1sb_ls             :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_ddr1sb_ds             :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_ddr1sb_sd             :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_LBM_DDR1SB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_213C    ddr1sb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_ddr1sb_urf_mem_ctrl   : 32;    //  31: 0
}BND_CTRL_LBM_DDR1SB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xC404_2000 ~ 0xC404_20FC
    BND_CTRL_LBM_LBUS_MEM0_O26A0_T     lbus_mem0  ;             // 0xC404_2100
    BND_CTRL_LBM_LBUS_MEM1_O26A0_T     lbus_mem1  ;             // 0xC404_2104
    BND_CTRL_LBM_NPP_MEM0_O26A0_T      npp_mem0   ;             // 0xC404_2108
    BND_CTRL_LBM_NPP_MEM1_O26A0_T      npp_mem1   ;             // 0xC404_210C
    BND_CTRL_LBM_NPP_MEM2_O26A0_T      npp_mem2   ;             // 0xC404_2110
    BND_CTRL_LBM_GFX_MEM0_O26A0_T      gfx_mem0   ;             // 0xC404_2114
    BND_CTRL_LBM_GFX_MEM1_O26A0_T      gfx_mem1   ;             // 0xC404_2118
    BND_CTRL_LBM_IOMMU_MEM0_O26A0_T    iommu_mem0 ;             // 0xC404_211C
    BND_CTRL_LBM_IOMMU_MEM1_O26A0_T    iommu_mem1 ;             // 0xC404_2120
    BND_CTRL_LBM_IOMMU_MEM2_O26A0_T    iommu_mem2 ;             // 0xC404_2124
    BND_CTRL_LBM_TIVVMSB_MEM0_O26A0_T    tivvmsb_mem0;          // 0xC404_2128
    BND_CTRL_LBM_TIVVMSB_MEM1_O26A0_T    tivvmsb_mem1;          // 0xC404_212C
    BND_CTRL_LBM_DDR0SB_MEM0_O26A0_T    ddr0sb_mem0;            // 0xC404_2130
    BND_CTRL_LBM_DDR0SB_MEM1_O26A0_T    ddr0sb_mem1;            // 0xC404_2134
    BND_CTRL_LBM_DDR1SB_MEM0_O26A0_T    ddr1sb_mem0;            // 0xC404_2138
    BND_CTRL_LBM_DDR1SB_MEM1_O26A0_T    ddr1sb_mem1;            // 0xC404_213C
}BND_CTRL_LBM_REG_O26A0_T;
/* 16 regs */

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

#define BND_CTRL_LBM_LBUS_MEM0_O26A0_T_OFF                  (BASEADDRESS+0x0100)
#define BND_CTRL_LBM_LBUS_MEM1_O26A0_T_OFF                  (BASEADDRESS+0x0104)
#define BND_CTRL_LBM_NPP_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_LBM_NPP_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x010C)
#define BND_CTRL_LBM_NPP_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x0110)
#define BND_CTRL_LBM_GFX_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0114)
#define BND_CTRL_LBM_GFX_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0118)
#define BND_CTRL_LBM_IOMMU_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x011C)
#define BND_CTRL_LBM_IOMMU_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x0120)
#define BND_CTRL_LBM_IOMMU_MEM2_O26A0_T_OFF                 (BASEADDRESS+0x0124)
#define BND_CTRL_LBM_TIVVMSB_MEM0_O26A0_T_OFF               (BASEADDRESS+0x0128)
#define BND_CTRL_LBM_TIVVMSB_MEM1_O26A0_T_OFF               (BASEADDRESS+0x012C)
#define BND_CTRL_LBM_DDR0SB_MEM0_O26A0_T_OFF                (BASEADDRESS+0x0130)
#define BND_CTRL_LBM_DDR0SB_MEM1_O26A0_T_OFF                (BASEADDRESS+0x0134)
#define BND_CTRL_LBM_DDR1SB_MEM0_O26A0_T_OFF                (BASEADDRESS+0x0138)
#define BND_CTRL_LBM_DDR1SB_MEM1_O26A0_T_OFF                (BASEADDRESS+0x013C)

/*-----------------------------------------------------------------------------------------
    0xC404_2100    lbus_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lbus_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_lbus_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_lbus_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_LBM_LBUS_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2104    lbus_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_lbus_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_LBUS_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2108    npp_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_npp_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_npp_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_npp_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_LBM_NPP_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_210C    npp_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_npp_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_NPP_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2110    npp_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_npp_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_NPP_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2114    gfx_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gfx_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_gfx_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_gfx_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_LBM_GFX_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2118    gfx_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_gfx_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_GFX_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_211C    iommu_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_iommu_ls       :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_iommu_ds       :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_iommu_sd       :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_LBM_IOMMU_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2120    iommu_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_iommu_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_IOMMU_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2124    iommu_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_iommu_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_IOMMU_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2128    tivvmsb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tivvmsb_ls     :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_tivvmsb_ds     :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_tivvmsb_sd     :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_LBM_TIVVMSB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_212C    tivvmsb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tivvmsb_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_TIVVMSB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2130    ddr0sb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ddr0sb_ls      :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_ddr0sb_ds      :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_ddr0sb_sd      :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_LBM_DDR0SB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2134    ddr0sb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ddr0sb_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_DDR0SB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_2138    ddr1sb_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ddr1sb_ls      :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_ddr1sb_ds      :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_ddr1sb_sd      :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_LBM_DDR1SB_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xC404_213C    ddr1sb_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_ddr1sb_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_LBM_DDR1SB_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_lbm Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xC404_2000 ~ 0xC404_20FC
    BND_CTRL_LBM_LBUS_MEM0_O26A0_T     lbus_mem0  ;             // 0xC404_2100
    BND_CTRL_LBM_LBUS_MEM1_O26A0_T     lbus_mem1  ;             // 0xC404_2104
    BND_CTRL_LBM_NPP_MEM0_O26A0_T      npp_mem0   ;             // 0xC404_2108
    BND_CTRL_LBM_NPP_MEM1_O26A0_T      npp_mem1   ;             // 0xC404_210C
    BND_CTRL_LBM_NPP_MEM2_O26A0_T      npp_mem2   ;             // 0xC404_2110
    BND_CTRL_LBM_GFX_MEM0_O26A0_T      gfx_mem0   ;             // 0xC404_2114
    BND_CTRL_LBM_GFX_MEM1_O26A0_T      gfx_mem1   ;             // 0xC404_2118
    BND_CTRL_LBM_IOMMU_MEM0_O26A0_T    iommu_mem0 ;             // 0xC404_211C
    BND_CTRL_LBM_IOMMU_MEM1_O26A0_T    iommu_mem1 ;             // 0xC404_2120
    BND_CTRL_LBM_IOMMU_MEM2_O26A0_T    iommu_mem2 ;             // 0xC404_2124
    BND_CTRL_LBM_TIVVMSB_MEM0_O26A0_T    tivvmsb_mem0;          // 0xC404_2128
    BND_CTRL_LBM_TIVVMSB_MEM1_O26A0_T    tivvmsb_mem1;          // 0xC404_212C
    BND_CTRL_LBM_DDR0SB_MEM0_O26A0_T    ddr0sb_mem0;            // 0xC404_2130
    BND_CTRL_LBM_DDR0SB_MEM1_O26A0_T    ddr0sb_mem1;            // 0xC404_2134
    BND_CTRL_LBM_DDR1SB_MEM0_O26A0_T    ddr1sb_mem0;            // 0xC404_2138
    BND_CTRL_LBM_DDR1SB_MEM1_O26A0_T    ddr1sb_mem1;            // 0xC404_213C
}BND_CTRL_LBM_REG_O26A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_LBM_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

