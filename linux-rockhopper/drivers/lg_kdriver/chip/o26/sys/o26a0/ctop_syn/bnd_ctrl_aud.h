#ifndef _BND_CTRL_AUD_REG_O26A0_H_
#define _BND_CTRL_AUD_REG_O26A0_H_

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
    0xCE7B_2000    aud_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpo_outmux_sel        :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AUD_AUD_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2004    aud_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tpi_cam_mux_sel       :  1,    //      0
                              : 31;    //   31:1 reserved
}BND_CTRL_AUD_AUD_SYN_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2008    aud_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_audio_dto0_sel        :  1,    //      0
    reg_audio_dto1_sel        :  1,    //      1
    reg_audio_dto2_sel        :  1,    //      2
                              : 29;    //   31:3 reserved
}BND_CTRL_AUD_AUD_SYN_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2100    aud_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_aud_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_aud_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_AUD_AUD_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2104    aud_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_AUD_AUD_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2108    aud_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_rf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_AUD_AUD_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_210C    aud_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_AUD_AUD_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2110    aud_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aud_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_AUD_AUD_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2114    te_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te_ls                 :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_te_ds                 :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_te_sd                 :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_AUD_TE_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2118    te_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te_urf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_AUD_TE_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_211C    te_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te_rf_mem_ctrl        : 32;    //  31: 0
}BND_CTRL_AUD_TE_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2120    te_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_te_srf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_AUD_TE_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_AUD_AUD_SYN_00_O26A0_T    aud_syn_00 ;             // 0xCE7B_2000
    BND_CTRL_AUD_AUD_SYN_01_O26A0_T    aud_syn_01 ;             // 0xCE7B_2004
    BND_CTRL_AUD_AUD_SYN_02_O26A0_T    aud_syn_02 ;             // 0xCE7B_2008
    UINT32                             _rsvd_00[61];            // 0xCE7B_200C ~ 0xCE7B_20FC
    BND_CTRL_AUD_AUD_MEM0_O26A0_T      aud_mem0   ;             // 0xCE7B_2100
    BND_CTRL_AUD_AUD_MEM1_O26A0_T      aud_mem1   ;             // 0xCE7B_2104
    BND_CTRL_AUD_AUD_MEM2_O26A0_T      aud_mem2   ;             // 0xCE7B_2108
    BND_CTRL_AUD_AUD_MEM3_O26A0_T      aud_mem3   ;             // 0xCE7B_210C
    BND_CTRL_AUD_AUD_MEM4_O26A0_T      aud_mem4   ;             // 0xCE7B_2110
    BND_CTRL_AUD_TE_MEM0_O26A0_T       te_mem0    ;             // 0xCE7B_2114
    BND_CTRL_AUD_TE_MEM1_O26A0_T       te_mem1    ;             // 0xCE7B_2118
    BND_CTRL_AUD_TE_MEM2_O26A0_T       te_mem2    ;             // 0xCE7B_211C
    BND_CTRL_AUD_TE_MEM3_O26A0_T       te_mem3    ;             // 0xCE7B_2120
}BND_CTRL_AUD_REG_O26A0_T;
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

#define BND_CTRL_AUD_AUD_SYN_00_O26A0_T_OFF                 (BASEADDRESS+0x0000)
#define BND_CTRL_AUD_AUD_SYN_01_O26A0_T_OFF                 (BASEADDRESS+0x0004)
#define BND_CTRL_AUD_AUD_SYN_02_O26A0_T_OFF                 (BASEADDRESS+0x0008)
#define BND_CTRL_AUD_AUD_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0100)
#define BND_CTRL_AUD_AUD_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0104)
#define BND_CTRL_AUD_AUD_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x0108)
#define BND_CTRL_AUD_AUD_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x010C)
#define BND_CTRL_AUD_AUD_MEM4_O26A0_T_OFF                   (BASEADDRESS+0x0110)
#define BND_CTRL_AUD_TE_MEM0_O26A0_T_OFF                    (BASEADDRESS+0x0114)
#define BND_CTRL_AUD_TE_MEM1_O26A0_T_OFF                    (BASEADDRESS+0x0118)
#define BND_CTRL_AUD_TE_MEM2_O26A0_T_OFF                    (BASEADDRESS+0x011C)
#define BND_CTRL_AUD_TE_MEM3_O26A0_T_OFF                    (BASEADDRESS+0x0120)

/*-----------------------------------------------------------------------------------------
    0xCE7B_2000    aud_syn_00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpo_outmux_sel :  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AUD_AUD_SYN_00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2004    aud_syn_01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tpi_cam_mux_sel:  1;    //      0
    UINT32 resvd00            : 31;    //   31:1 reserved
    };
}BND_CTRL_AUD_AUD_SYN_01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2008    aud_syn_02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_audio_dto0_sel :  1;    //      0
    UINT32 reg_audio_dto1_sel :  1;    //      1
    UINT32 reg_audio_dto2_sel :  1;    //      2
    UINT32 resvd00            : 29;    //   31:3 reserved
    };
}BND_CTRL_AUD_AUD_SYN_02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2100    aud_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_aud_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_aud_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_AUD_AUD_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2104    aud_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_AUD_AUD_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2108    aud_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_rf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_AUD_AUD_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_210C    aud_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_AUD_AUD_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2110    aud_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_aud_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_AUD_AUD_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2114    te_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_te_ls          :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_te_ds          :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_te_sd          :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_AUD_TE_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2118    te_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_te_urf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_AUD_TE_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_211C    te_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_te_rf_mem_ctrl : 32;    //  31: 0
    };
}BND_CTRL_AUD_TE_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCE7B_2120    te_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_te_srf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_AUD_TE_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_aud Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    BND_CTRL_AUD_AUD_SYN_00_O26A0_T    aud_syn_00 ;             // 0xCE7B_2000
    BND_CTRL_AUD_AUD_SYN_01_O26A0_T    aud_syn_01 ;             // 0xCE7B_2004
    BND_CTRL_AUD_AUD_SYN_02_O26A0_T    aud_syn_02 ;             // 0xCE7B_2008
    UINT32                             _rsvd_00[61];            // 0xCE7B_200C ~ 0xCE7B_20FC
    BND_CTRL_AUD_AUD_MEM0_O26A0_T      aud_mem0   ;             // 0xCE7B_2100
    BND_CTRL_AUD_AUD_MEM1_O26A0_T      aud_mem1   ;             // 0xCE7B_2104
    BND_CTRL_AUD_AUD_MEM2_O26A0_T      aud_mem2   ;             // 0xCE7B_2108
    BND_CTRL_AUD_AUD_MEM3_O26A0_T      aud_mem3   ;             // 0xCE7B_210C
    BND_CTRL_AUD_AUD_MEM4_O26A0_T      aud_mem4   ;             // 0xCE7B_2110
    BND_CTRL_AUD_TE_MEM0_O26A0_T       te_mem0    ;             // 0xCE7B_2114
    BND_CTRL_AUD_TE_MEM1_O26A0_T       te_mem1    ;             // 0xCE7B_2118
    BND_CTRL_AUD_TE_MEM2_O26A0_T       te_mem2    ;             // 0xCE7B_211C
    BND_CTRL_AUD_TE_MEM3_O26A0_T       te_mem3    ;             // 0xCE7B_2120
}BND_CTRL_AUD_REG_O26A0_T;
/* 12 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_AUD_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

