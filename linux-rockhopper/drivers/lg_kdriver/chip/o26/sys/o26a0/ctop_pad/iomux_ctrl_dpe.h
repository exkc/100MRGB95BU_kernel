#ifndef _IOMUX_CTRL_DPE_REG_O26A0_H_
#define _IOMUX_CTRL_DPE_REG_O26A0_H_

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
    0xCC97_3000    pad_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_spi_sclk0__ds0    :  1,    //      4
    reg_pad_spi_sclk0__ds1    :  1,    //      5
    reg_pad_spi_sclk0__ds2    :  1,    //      6
    reg_pad_spi_sclk0__ds3    :  1,    //      7
    reg_pad_spi_sclk0__pd     :  1,    //      8
    reg_pad_spi_sclk0__pu     :  1,    //      9
    reg_pad_spi_sclk0__st     :  1,    //     10
    reg_pad_spi_do0__ds0      :  1,    //     11
    reg_pad_spi_do0__ds1      :  1,    //     12
    reg_pad_spi_do0__ds2      :  1,    //     13
    reg_pad_spi_do0__ds3      :  1,    //     14
    reg_pad_spi_do0__pd       :  1,    //     15
    reg_pad_spi_do0__pu       :  1,    //     16
    reg_pad_spi_do0__st       :  1,    //     17
    reg_pad_spi_di0__ds0      :  1,    //     18
    reg_pad_spi_di0__ds1      :  1,    //     19
    reg_pad_spi_di0__ds2      :  1,    //     20
    reg_pad_spi_di0__ds3      :  1,    //     21
    reg_pad_spi_di0__pd       :  1,    //     22
    reg_pad_spi_di0__pu       :  1,    //     23
    reg_pad_spi_di0__st       :  1,    //     24
    reg_pad_spi_cs0__ds0      :  1,    //     25
    reg_pad_spi_cs0__ds1      :  1,    //     26
    reg_pad_spi_cs0__ds2      :  1,    //     27
    reg_pad_spi_cs0__ds3      :  1,    //     28
    reg_pad_spi_cs0__pd       :  1,    //     29
    reg_pad_spi_cs0__pu       :  1,    //     30
    reg_pad_spi_cs0__st       :  1;    //     31
}IOMUX_CTRL_DPE_PAD_DPE00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_3004    pad_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  4,    //   3: 0 reserved
    reg_pad_spi_sclk1__ds0    :  1,    //      4
    reg_pad_spi_sclk1__ds1    :  1,    //      5
    reg_pad_spi_sclk1__ds2    :  1,    //      6
    reg_pad_spi_sclk1__ds3    :  1,    //      7
    reg_pad_spi_sclk1__pd     :  1,    //      8
    reg_pad_spi_sclk1__pu     :  1,    //      9
    reg_pad_spi_sclk1__st     :  1,    //     10
    reg_pad_spi_do1__ds0      :  1,    //     11
    reg_pad_spi_do1__ds1      :  1,    //     12
    reg_pad_spi_do1__ds2      :  1,    //     13
    reg_pad_spi_do1__ds3      :  1,    //     14
    reg_pad_spi_do1__pd       :  1,    //     15
    reg_pad_spi_do1__pu       :  1,    //     16
    reg_pad_spi_do1__st       :  1,    //     17
    reg_pad_spi_di1__ds0      :  1,    //     18
    reg_pad_spi_di1__ds1      :  1,    //     19
    reg_pad_spi_di1__ds2      :  1,    //     20
    reg_pad_spi_di1__ds3      :  1,    //     21
    reg_pad_spi_di1__pd       :  1,    //     22
    reg_pad_spi_di1__pu       :  1,    //     23
    reg_pad_spi_di1__st       :  1,    //     24
    reg_pad_spi_cs1__ds0      :  1,    //     25
    reg_pad_spi_cs1__ds1      :  1,    //     26
    reg_pad_spi_cs1__ds2      :  1,    //     27
    reg_pad_spi_cs1__ds3      :  1,    //     28
    reg_pad_spi_cs1__pd       :  1,    //     29
    reg_pad_spi_cs1__pu       :  1,    //     30
    reg_pad_spi_cs1__st       :  1;    //     31
}IOMUX_CTRL_DPE_PAD_DPE01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_3008    pad_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
                              :  1,    //      0 reserved
    reg_pad_edp_hpd1__ds0     :  1,    //      1
    reg_pad_edp_hpd1__ds1     :  1,    //      2
    reg_pad_edp_hpd1__ds2     :  1,    //      3
    reg_pad_edp_hpd1__ds3     :  1,    //      4
    reg_pad_edp_hpd1__pd      :  1,    //      5
    reg_pad_edp_hpd1__pu      :  1,    //      6
    reg_pad_edp_hpd1__st      :  1,    //      7
                              : 24;    //   31:8 reserved
}IOMUX_CTRL_DPE_PAD_DPE02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_3100    pad_dpe64 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_spi_sclk1_mux_sel :  4,    //   3: 0
    reg_pad_spi_do1_mux_sel   :  4,    //   7: 4
    reg_pad_spi_di1_mux_sel   :  4,    //  11: 8
    reg_pad_spi_cs1_mux_sel   :  4,    //  15:12
    reg_pad_spi_sclk0_mux_sel :  4,    //  19:16
    reg_pad_spi_do0_mux_sel   :  4,    //  23:20
    reg_pad_spi_di0_mux_sel   :  4,    //  27:24
    reg_pad_spi_cs0_mux_sel   :  4;    //  31:28
}IOMUX_CTRL_DPE_PAD_DPE64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_3104    pad_dpe65 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_pad_edp_hpd1_mux_sel  :  4,    //   3: 0
                              : 28;    //   31:4 reserved
}IOMUX_CTRL_DPE_PAD_DPE65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_DPE_PAD_DPE00_O26A0_T    pad_dpe00 ;             // 0xCC97_3000
    IOMUX_CTRL_DPE_PAD_DPE01_O26A0_T    pad_dpe01 ;             // 0xCC97_3004
    IOMUX_CTRL_DPE_PAD_DPE02_O26A0_T    pad_dpe02 ;             // 0xCC97_3008
    UINT32                             _rsvd_00[61];            // 0xCC97_300C ~ 0xCC97_30FC
    IOMUX_CTRL_DPE_PAD_DPE64_O26A0_T    pad_dpe64 ;             // 0xCC97_3100
    IOMUX_CTRL_DPE_PAD_DPE65_O26A0_T    pad_dpe65 ;             // 0xCC97_3104
}IOMUX_CTRL_DPE_REG_O26A0_T;
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

#define IOMUX_CTRL_DPE_PAD_DPE00_O26A0_T_OFF                (BASEADDRESS+0x0000)
#define IOMUX_CTRL_DPE_PAD_DPE01_O26A0_T_OFF                (BASEADDRESS+0x0004)
#define IOMUX_CTRL_DPE_PAD_DPE02_O26A0_T_OFF                (BASEADDRESS+0x0008)
#define IOMUX_CTRL_DPE_PAD_DPE64_O26A0_T_OFF                (BASEADDRESS+0x0100)
#define IOMUX_CTRL_DPE_PAD_DPE65_O26A0_T_OFF                (BASEADDRESS+0x0104)

/*-----------------------------------------------------------------------------------------
    0xCC97_3000    pad_dpe00 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_spi_sclk0__ds0: 1;    //    4
    UINT32 reg_pad_spi_sclk0__ds1: 1;    //    5
    UINT32 reg_pad_spi_sclk0__ds2: 1;    //    6
    UINT32 reg_pad_spi_sclk0__ds3: 1;    //    7
    UINT32 reg_pad_spi_sclk0__pd: 1;    //     8
    UINT32 reg_pad_spi_sclk0__pu: 1;    //     9
    UINT32 reg_pad_spi_sclk0__st: 1;    //    10
    UINT32 reg_pad_spi_do0__ds0: 1;    //     11
    UINT32 reg_pad_spi_do0__ds1: 1;    //     12
    UINT32 reg_pad_spi_do0__ds2: 1;    //     13
    UINT32 reg_pad_spi_do0__ds3: 1;    //     14
    UINT32 reg_pad_spi_do0__pd:  1;    //     15
    UINT32 reg_pad_spi_do0__pu:  1;    //     16
    UINT32 reg_pad_spi_do0__st:  1;    //     17
    UINT32 reg_pad_spi_di0__ds0: 1;    //     18
    UINT32 reg_pad_spi_di0__ds1: 1;    //     19
    UINT32 reg_pad_spi_di0__ds2: 1;    //     20
    UINT32 reg_pad_spi_di0__ds3: 1;    //     21
    UINT32 reg_pad_spi_di0__pd:  1;    //     22
    UINT32 reg_pad_spi_di0__pu:  1;    //     23
    UINT32 reg_pad_spi_di0__st:  1;    //     24
    UINT32 reg_pad_spi_cs0__ds0: 1;    //     25
    UINT32 reg_pad_spi_cs0__ds1: 1;    //     26
    UINT32 reg_pad_spi_cs0__ds2: 1;    //     27
    UINT32 reg_pad_spi_cs0__ds3: 1;    //     28
    UINT32 reg_pad_spi_cs0__pd:  1;    //     29
    UINT32 reg_pad_spi_cs0__pu:  1;    //     30
    UINT32 reg_pad_spi_cs0__st:  1;    //     31
    };
}IOMUX_CTRL_DPE_PAD_DPE00_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_3004    pad_dpe01 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  4;    //   3: 0 reserved
    UINT32 reg_pad_spi_sclk1__ds0: 1;    //    4
    UINT32 reg_pad_spi_sclk1__ds1: 1;    //    5
    UINT32 reg_pad_spi_sclk1__ds2: 1;    //    6
    UINT32 reg_pad_spi_sclk1__ds3: 1;    //    7
    UINT32 reg_pad_spi_sclk1__pd: 1;    //     8
    UINT32 reg_pad_spi_sclk1__pu: 1;    //     9
    UINT32 reg_pad_spi_sclk1__st: 1;    //    10
    UINT32 reg_pad_spi_do1__ds0: 1;    //     11
    UINT32 reg_pad_spi_do1__ds1: 1;    //     12
    UINT32 reg_pad_spi_do1__ds2: 1;    //     13
    UINT32 reg_pad_spi_do1__ds3: 1;    //     14
    UINT32 reg_pad_spi_do1__pd:  1;    //     15
    UINT32 reg_pad_spi_do1__pu:  1;    //     16
    UINT32 reg_pad_spi_do1__st:  1;    //     17
    UINT32 reg_pad_spi_di1__ds0: 1;    //     18
    UINT32 reg_pad_spi_di1__ds1: 1;    //     19
    UINT32 reg_pad_spi_di1__ds2: 1;    //     20
    UINT32 reg_pad_spi_di1__ds3: 1;    //     21
    UINT32 reg_pad_spi_di1__pd:  1;    //     22
    UINT32 reg_pad_spi_di1__pu:  1;    //     23
    UINT32 reg_pad_spi_di1__st:  1;    //     24
    UINT32 reg_pad_spi_cs1__ds0: 1;    //     25
    UINT32 reg_pad_spi_cs1__ds1: 1;    //     26
    UINT32 reg_pad_spi_cs1__ds2: 1;    //     27
    UINT32 reg_pad_spi_cs1__ds3: 1;    //     28
    UINT32 reg_pad_spi_cs1__pd:  1;    //     29
    UINT32 reg_pad_spi_cs1__pu:  1;    //     30
    UINT32 reg_pad_spi_cs1__st:  1;    //     31
    };
}IOMUX_CTRL_DPE_PAD_DPE01_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_3008    pad_dpe02 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 resvd00            :  1;    //      0 reserved
    UINT32 reg_pad_edp_hpd1__ds0: 1;    //     1
    UINT32 reg_pad_edp_hpd1__ds1: 1;    //     2
    UINT32 reg_pad_edp_hpd1__ds2: 1;    //     3
    UINT32 reg_pad_edp_hpd1__ds3: 1;    //     4
    UINT32 reg_pad_edp_hpd1__pd: 1;    //      5
    UINT32 reg_pad_edp_hpd1__pu: 1;    //      6
    UINT32 reg_pad_edp_hpd1__st: 1;    //      7
    UINT32 resvd01            : 24;    //   31:8 reserved
    };
}IOMUX_CTRL_DPE_PAD_DPE02_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_3100    pad_dpe64 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_spi_sclk1_mux_sel: 4;    //  3:0
    UINT32 reg_pad_spi_do1_mux_sel: 4;    //  7:4
    UINT32 reg_pad_spi_di1_mux_sel: 4;    //  11:8
    UINT32 reg_pad_spi_cs1_mux_sel: 4;    //  15:12
    UINT32 reg_pad_spi_sclk0_mux_sel: 4;    //  19:16
    UINT32 reg_pad_spi_do0_mux_sel: 4;    //  23:20
    UINT32 reg_pad_spi_di0_mux_sel: 4;    //  27:24
    UINT32 reg_pad_spi_cs0_mux_sel: 4;    //  31:28
    };
}IOMUX_CTRL_DPE_PAD_DPE64_O26A0_T;

/*-----------------------------------------------------------------------------------------
    0xCC97_3104    pad_dpe65 ''
-----------------------------------------------------------------------------------------*/
typedef union {
    UINT32 udata32;
    struct {
    UINT32 reg_pad_edp_hpd1_mux_sel: 4;    //  3:0
    UINT32 resvd00            : 28;    //   31:4 reserved
    };
}IOMUX_CTRL_DPE_PAD_DPE65_O26A0_T;

/*-----------------------------------------------------------------------------------------
    iomux_ctrl_dpe Register LIst
-----------------------------------------------------------------------------------------*/
typedef struct {
    IOMUX_CTRL_DPE_PAD_DPE00_O26A0_T    pad_dpe00 ;             // 0xCC97_3000
    IOMUX_CTRL_DPE_PAD_DPE01_O26A0_T    pad_dpe01 ;             // 0xCC97_3004
    IOMUX_CTRL_DPE_PAD_DPE02_O26A0_T    pad_dpe02 ;             // 0xCC97_3008
    UINT32                             _rsvd_00[61];            // 0xCC97_300C ~ 0xCC97_30FC
    IOMUX_CTRL_DPE_PAD_DPE64_O26A0_T    pad_dpe64 ;             // 0xCC97_3100
    IOMUX_CTRL_DPE_PAD_DPE65_O26A0_T    pad_dpe65 ;             // 0xCC97_3104
}IOMUX_CTRL_DPE_REG_O26A0_T;
/* 5 regs */

#ifdef __cplusplus
}
#endif

#endif


#endif //_IOMUX_CTRL_DPE_REG_H_

/* from 'O26_CTOP_PAD_Register_Manual.xlsx'  2025.3.20  KJH by LGSiCRDV V3.1C*/

