#ifndef _PE_CHPI_REG_O22F22A0_H_
#define _PE_CHPI_REG_O22F22A0_H_

#include "pe_chpi_cco_reg_o22f22a0.h"
#include "pe_chpi_hdr_reg_o22f22a0.h"

typedef union {
	UINT32 udata32;
	struct {
	UINT32 max_num                      :8;	//7:0
	UINT32 resvd                        :12;
	UINT32 bufidx1                      :4;	//23:20
	UINT32 bufidx0                      :4;	//27:24
	UINT32 version                      :4;	//31:28
	};
}PE_CHPI_APB_INFO_O22F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 ofst                         :16;//15:0
	UINT32 size                         :16;//31:16
	};
}PE_CHPI_APB_POS_O22F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 cmn0                         :8;	//7:0
	UINT32 cen0                         :8;	//15:8
	UINT32 cen1                         :8;	//23:16
	UINT32 cw0                          :8;	//31:24
	};
}PE_CHPI_APB0_CNT0_O22F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 vsp0                         :8;	//7:0
	UINT32 dse0                         :8;	//15:8
	UINT32 dce0                         :8;	//23:16
	UINT32 dtm0                         :8;	//31:24
	};
}PE_CHPI_APB0_CNT1_O22F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 lll0                         :8;	//7:0
	UINT32 fsw0                         :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_APB0_CNT2_O22F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 resvd0                       :8;	//7:0
	UINT32 resvd1                       :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_APB0_CNT3_O22F22_T;


typedef union {
	UINT32 udata32;
	struct {
	UINT32 resvd0                       :8;	//7:0
	UINT32 resvd1                       :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_APB0_CNT4_O22F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 resvd0                       :8;	//7:0
	UINT32 resvd1                       :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_APB0_CNT5_O22F22_T;

/* fw ctrl */
typedef union {
	UINT32 udata32;
	struct {
	UINT32 tm                           :8;	//7:0
	UINT32 yg                           :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_APB0_CNT6_O22F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 hs                           :8;	//7:0
	UINT32 pcc                          :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_APB0_CNT7_O22F22_T;

typedef struct
{
	PE_CHPI_APB_INFO_O22F22_T              info;
	PE_CHPI_APB0_CNT0_O22F22_T             cnt0;
	PE_CHPI_APB0_CNT1_O22F22_T             cnt1;
	PE_CHPI_APB0_CNT2_O22F22_T             cnt2;
	PE_CHPI_APB0_CNT3_O22F22_T             cnt3;
	PE_CHPI_APB0_CNT4_O22F22_T             cnt4;
	PE_CHPI_APB0_CNT5_O22F22_T             cnt5;
	PE_CHPI_APB0_CNT6_O22F22_T             cnt6;
	PE_CHPI_APB0_CNT7_O22F22_T             cnt7;
	PE_CHPI_APB_POS_O22F22_T               pos[32];
}PE_CHPI_APB0_DB_H_O22F22_T;

typedef struct
{
	UINT32                              resvd[987];
}PE_CHPI_APB0_RESVD0_O22F22_T;

typedef struct
{
	UINT32                              resvd[240];
}PE_CHPI_APB0_RESVD1_O22F22_T;

/* causion : Max Struct Size : 13312 + 12 Byte (Data 13k + Header 4 Byte + CRC0/1 8 Byte) -> u32[3331]*/
/* header : [31]Last_Block,[30:28]Reserved,[27:20]Packet_Number,[19]Addr_AI,[17:16]Mode,[15:00]Data_Size(Byte) */
/* endian conversion : setting data 0xABCDEF0 -> ddr data 0xF0DECDAB */
/*
2021/11/22 15:25
[CHI]head   (  164)(  41 x 4(byte) = 0x00a4) (0x0004)
[CHI]cmn0   (   24)(   3 x 8(byte) = 0x0018) (0x00a8)
[CHI]cen0   ( 3304)( 413 x 8(byte) = 0x0ce8) (0x00c0)
[CHI]cen1   (  328)(  41 x 8(byte) = 0x0148) (0x0da8)
[CHI]cw0    (  152)(  19 x 8(byte) = 0x0098) (0x0ef0)
[CHI]vsp0   (  160)(  20 x 8(byte) = 0x00a0) (0x0f88)
[CHI]dse0   (  416)(  52 x 8(byte) = 0x01a0) (0x1028)
[CHI]dce0   (   48)(   6 x 8(byte) = 0x0030) (0x11c8)
[CHI]dtm0   (  344)(  43 x 8(byte) = 0x0158) (0x11f8)
[CHI]lll0   ( 1168)( 146 x 8(byte) = 0x0490) (0x1350)
[CHI]fsw0   (  136)(  17 x 8(byte) = 0x0088) (0x17e0)
[CHI]resvd0 ( 3996)( 999 x 4(byte) = 0x0f9c) (0x1868)
[CHI]tm     ( 1656)( 207 x 8(byte) = 0x0678) (0x2804)
[CHI]yg     (  280)(  35 x 8(byte) = 0x0118) (0x2e7c)
[CHI]hs     (  136)(  17 x 8(byte) = 0x0088) (0x2f94)
[CHI]pcc    (   40)(   5 x 8(byte) = 0x0028) (0x301c)
[CHI]resvd1 (  960)( 240 x 4(byte) = 0x03c0) (0x3044)
[CHI]TOTAL  (13324)(0x340c) vs (13324)(0x340c)
*/
typedef struct
{
	UINT32                               head0;
	PE_CHPI_APB0_DB_H_O22F22_T           head1;
	PE_CHPI_CMN0_O22F22_T                 cmn0;//00
	PE_CHPI_CEN0_O22F22_T                 cen0;//01
	PE_CHPI_CEN1_O22F22_T                 cen1;//02
	PE_CHPI_CW0_O22F22_T                   cw0;//03
	PE_CHPI_VSP0_O22F22_T                 vsp0;//04
	PE_CHPI_DSE0_O22F22_T                 dse0;//05
	PE_CHPI_DCE0_O22F22_T                 dce0;//06
	PE_CHPI_DTM0_O22F22_T                 dtm0;//07
	PE_CHPI_LLL0_O22F22_T                 lll0;//08
	PE_CHPI_FSW0_O22F22_T                 fsw0;//09
	PE_CHPI_APB0_RESVD0_O22F22_T        resvd0;
	PE_CHPI_HDR_TM_O22F22_T                 tm;//24
	PE_CHPI_HDR_YG_O22F22_T                 yg;//25
	PE_CHPI_HDR_HS_O22F22_T                 hs;//28
	PE_CHPI_HDR_PCC_O22F22_T               pcc;//29
	PE_CHPI_APB0_RESVD1_O22F22_T         resvd1;
	UINT32                                 crc0;
	UINT32                                 crc1;
}PE_CHPI_REG_O22F22_T;

/* dbg : check size */
typedef struct
{
	UINT32                               head0;
	PE_CHPI_APB0_DB_H_O22F22_T           head1;
	PE_CHPI_CMN0_O22F22_T                 cmn0;//00
	PE_CHPI_CEN0_O22F22_T                 cen0;//01
	PE_CHPI_CEN1_O22F22_T                 cen1;//02
	PE_CHPI_CW0_O22F22_T                   cw0;//03
	PE_CHPI_VSP0_O22F22_T                 vsp0;//04
	PE_CHPI_DSE0_O22F22_T                 dse0;//05
	PE_CHPI_DCE0_O22F22_T                 dce0;//06
	PE_CHPI_DTM0_O22F22_T                 dtm0;//07
	PE_CHPI_LLL0_O22F22_T                 lll0;//08
	PE_CHPI_FSW0_O22F22_T                 fsw0;//09
	PE_CHPI_APB0_RESVD0_O22F22_T        resvd0;
}PE_CHPI_REG0_O22F22_T;

/* dbg : check size */
typedef struct
{
	PE_CHPI_HDR_TM_O22F22_T                 tm;//24
	PE_CHPI_HDR_YG_O22F22_T                 yg;//25
	PE_CHPI_HDR_HS_O22F22_T                 hs;//28
	PE_CHPI_HDR_PCC_O22F22_T               pcc;//29
	PE_CHPI_APB0_RESVD1_O22F22_T         resvd1;
	UINT32                                 crc0;
	UINT32                                 crc1;
}PE_CHPI_REG1_O22F22_T;

#endif
