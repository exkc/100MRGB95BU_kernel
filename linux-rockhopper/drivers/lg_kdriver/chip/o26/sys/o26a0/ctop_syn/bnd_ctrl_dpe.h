#ifndef _BND_CTRL_DPE_REG_O26A0_H_
#define _BND_CTRL_DPE_REG_O26A0_H_

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
    0xCC97_2100    tcon_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tcon_ls               :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_tcon_ds               :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_tcon_sd               :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_DPE_TCON_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2104    tcon_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tcon_rf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_DPE_TCON_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2108    tcon_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_tcon_srf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_DPE_TCON_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_210C    led_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_led_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_led_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_DPE_LED_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2110    led_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_DPE_LED_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2114    led_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_rf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_DPE_LED_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2118    led_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_led_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_DPE_LED_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_211C    usb_ss_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_ss_ls             :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_usb_ss_ds             :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_usb_ss_sd             :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_DPE_USB_SS_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2120    usb_ss_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_usb_ss_sra_mem_ctrl   : 32;    //  31: 0
}BND_CTRL_DPE_USB_SS_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2124    vsd_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_ls                :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_vsd_ds                :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_vsd_sd                :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_DPE_VSD_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2128    vsd_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_urf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_DPE_VSD_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_212C    vsd_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_rf_mem_ctrl       : 32;    //  31: 0
}BND_CTRL_DPE_VSD_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2130    vsd_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_srf_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_DPE_VSD_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2134    vsd_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_vsd_sra_mem_ctrl      : 32;    //  31: 0
}BND_CTRL_DPE_VSD_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2138    edptx_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edptx_ls              :  1,    //      0
                              :  3,    //   3: 1 reserved
    reg_edptx_ds              :  1,    //      4
                              :  3,    //   7: 5 reserved
    reg_edptx_sd              :  1,    //      8
                              : 23;    //   31:9 reserved
}BND_CTRL_DPE_EDPTX_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_213C    edptx_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_edptx_rf_mem_ctrl     : 32;    //  31: 0
}BND_CTRL_DPE_EDPTX_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCC97_2000 ~ 0xCC97_20FC
    BND_CTRL_DPE_TCON_MEM0_O26A0_T     tcon_mem0  ;             // 0xCC97_2100
    BND_CTRL_DPE_TCON_MEM1_O26A0_T     tcon_mem1  ;             // 0xCC97_2104
    BND_CTRL_DPE_TCON_MEM2_O26A0_T     tcon_mem2  ;             // 0xCC97_2108
    BND_CTRL_DPE_LED_MEM0_O26A0_T      led_mem0   ;             // 0xCC97_210C
    BND_CTRL_DPE_LED_MEM1_O26A0_T      led_mem1   ;             // 0xCC97_2110
    BND_CTRL_DPE_LED_MEM2_O26A0_T      led_mem2   ;             // 0xCC97_2114
    BND_CTRL_DPE_LED_MEM3_O26A0_T      led_mem3   ;             // 0xCC97_2118
    BND_CTRL_DPE_USB_SS_MEM0_O26A0_T    usb_ss_mem0;            // 0xCC97_211C
    BND_CTRL_DPE_USB_SS_MEM1_O26A0_T    usb_ss_mem1;            // 0xCC97_2120
    BND_CTRL_DPE_VSD_MEM0_O26A0_T      vsd_mem0   ;             // 0xCC97_2124
    BND_CTRL_DPE_VSD_MEM1_O26A0_T      vsd_mem1   ;             // 0xCC97_2128
    BND_CTRL_DPE_VSD_MEM2_O26A0_T      vsd_mem2   ;             // 0xCC97_212C
    BND_CTRL_DPE_VSD_MEM3_O26A0_T      vsd_mem3   ;             // 0xCC97_2130
    BND_CTRL_DPE_VSD_MEM4_O26A0_T      vsd_mem4   ;             // 0xCC97_2134
    BND_CTRL_DPE_EDPTX_MEM0_O26A0_T    edptx_mem0 ;             // 0xCC97_2138
    BND_CTRL_DPE_EDPTX_MEM1_O26A0_T    edptx_mem1 ;             // 0xCC97_213C
}BND_CTRL_DPE_REG_O26A0_T;
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

#define BND_CTRL_DPE_TCON_MEM0_O26A0_T_OFF                  (BASEADDRESS+0x0100)
#define BND_CTRL_DPE_TCON_MEM1_O26A0_T_OFF                  (BASEADDRESS+0x0104)
#define BND_CTRL_DPE_TCON_MEM2_O26A0_T_OFF                  (BASEADDRESS+0x0108)
#define BND_CTRL_DPE_LED_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x010C)
#define BND_CTRL_DPE_LED_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0110)
#define BND_CTRL_DPE_LED_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x0114)
#define BND_CTRL_DPE_LED_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x0118)
#define BND_CTRL_DPE_USB_SS_MEM0_O26A0_T_OFF                (BASEADDRESS+0x011C)
#define BND_CTRL_DPE_USB_SS_MEM1_O26A0_T_OFF                (BASEADDRESS+0x0120)
#define BND_CTRL_DPE_VSD_MEM0_O26A0_T_OFF                   (BASEADDRESS+0x0124)
#define BND_CTRL_DPE_VSD_MEM1_O26A0_T_OFF                   (BASEADDRESS+0x0128)
#define BND_CTRL_DPE_VSD_MEM2_O26A0_T_OFF                   (BASEADDRESS+0x012C)
#define BND_CTRL_DPE_VSD_MEM3_O26A0_T_OFF                   (BASEADDRESS+0x0130)
#define BND_CTRL_DPE_VSD_MEM4_O26A0_T_OFF                   (BASEADDRESS+0x0134)
#define BND_CTRL_DPE_EDPTX_MEM0_O26A0_T_OFF                 (BASEADDRESS+0x0138)
#define BND_CTRL_DPE_EDPTX_MEM1_O26A0_T_OFF                 (BASEADDRESS+0x013C)

/*-----------------------------------------------------------------------------------------
    0xCC97_2100    tcon_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tcon_ls        :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_tcon_ds        :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_tcon_sd        :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_DPE_TCON_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2104    tcon_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tcon_rf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_TCON_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2108    tcon_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_tcon_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_TCON_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_210C    led_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_led_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_led_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_DPE_LED_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2110    led_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_LED_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2114    led_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_rf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_DPE_LED_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2118    led_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_led_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_LED_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_211C    usb_ss_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb_ss_ls      :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_usb_ss_ds      :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_usb_ss_sd      :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_DPE_USB_SS_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2120    usb_ss_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_usb_ss_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_USB_SS_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2124    vsd_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_ls         :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_vsd_ds         :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_vsd_sd         :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_DPE_VSD_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2128    vsd_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_urf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_VSD_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_212C    vsd_mem2 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_rf_mem_ctrl: 32;    //  31: 0
    };
}BND_CTRL_DPE_VSD_MEM2_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2130    vsd_mem3 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_srf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_VSD_MEM3_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2134    vsd_mem4 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_vsd_sra_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_VSD_MEM4_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_2138    edptx_mem0 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edptx_ls       :  1;    //      0
    UINT32 resvd00            :  3;    //   3: 1 reserved
    UINT32 reg_edptx_ds       :  1;    //      4
    UINT32 resvd01            :  3;    //   7: 5 reserved
    UINT32 reg_edptx_sd       :  1;    //      8
    UINT32 resvd02            : 23;    //   31:9 reserved
    };
}BND_CTRL_DPE_EDPTX_MEM0_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_213C    edptx_mem1 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_edptx_rf_mem_ctrl: 32;    //  31:0
    };
}BND_CTRL_DPE_EDPTX_MEM1_O26A0_T;

/*-----------------------------------------------------------------------------------------
    bnd_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32                             _rsvd_00[64];            // 0xCC97_2000 ~ 0xCC97_20FC
    BND_CTRL_DPE_TCON_MEM0_O26A0_T     tcon_mem0  ;             // 0xCC97_2100
    BND_CTRL_DPE_TCON_MEM1_O26A0_T     tcon_mem1  ;             // 0xCC97_2104
    BND_CTRL_DPE_TCON_MEM2_O26A0_T     tcon_mem2  ;             // 0xCC97_2108
    BND_CTRL_DPE_LED_MEM0_O26A0_T      led_mem0   ;             // 0xCC97_210C
    BND_CTRL_DPE_LED_MEM1_O26A0_T      led_mem1   ;             // 0xCC97_2110
    BND_CTRL_DPE_LED_MEM2_O26A0_T      led_mem2   ;             // 0xCC97_2114
    BND_CTRL_DPE_LED_MEM3_O26A0_T      led_mem3   ;             // 0xCC97_2118
    BND_CTRL_DPE_USB_SS_MEM0_O26A0_T    usb_ss_mem0;            // 0xCC97_211C
    BND_CTRL_DPE_USB_SS_MEM1_O26A0_T    usb_ss_mem1;            // 0xCC97_2120
    BND_CTRL_DPE_VSD_MEM0_O26A0_T      vsd_mem0   ;             // 0xCC97_2124
    BND_CTRL_DPE_VSD_MEM1_O26A0_T      vsd_mem1   ;             // 0xCC97_2128
    BND_CTRL_DPE_VSD_MEM2_O26A0_T      vsd_mem2   ;             // 0xCC97_212C
    BND_CTRL_DPE_VSD_MEM3_O26A0_T      vsd_mem3   ;             // 0xCC97_2130
    BND_CTRL_DPE_VSD_MEM4_O26A0_T      vsd_mem4   ;             // 0xCC97_2134
    BND_CTRL_DPE_EDPTX_MEM0_O26A0_T    edptx_mem0 ;             // 0xCC97_2138
    BND_CTRL_DPE_EDPTX_MEM1_O26A0_T    edptx_mem1 ;             // 0xCC97_213C
}BND_CTRL_DPE_REG_O26A0_T;
/* 16 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_BND_CTRL_DPE_REG_H_

/* from 'O26_CTOP_SYN_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

