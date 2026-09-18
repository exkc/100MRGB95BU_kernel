#ifndef _PE_CHPI_REG_F20A0_H_
#define _PE_CHPI_REG_F20A0_H_

#include "pe_chpi_cco_reg_f20a0.h"
#include "pe_chpi_hdr_reg_f20a0.h"

#ifdef PE_CHPI_DEF_F20_USE_REG
typedef union {
	UINT32 udata32;
	struct {
	UINT32 max_num                      :8;	//7:0
	UINT32 resvd                        :12;
	UINT32 bufidx1                      :4;	//23:20
	UINT32 bufidx0                      :4;	//27:24
	UINT32 version                      :4;	//31:28
	};
}PE_CHPI_APB_INFO_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 ofst                         :16;//15:0
	UINT32 size                         :16;//31:16
	};
}PE_CHPI_APB_POS_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 cmn0                         :4;	//3:0
	UINT32 cen0                         :4;	//7:4
	UINT32 cen1                         :4;	//11:8
	UINT32 cw0                          :4;	//15:12
	UINT32 vsp0                         :4;	//19:16
	UINT32 dse0                         :4;	//23:20
	UINT32 dce0                         :4;	//27:24
	UINT32 dtm0                         :4;	//31:28
	};
}PE_CHPI_APB0_CNT0_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 fsw0                         :4;	//3:0
	UINT32 cen0_2nd                     :4;	//7:4
	UINT32 cen1_2nd                     :4;	//11:8
	UINT32 resvd3                       :4;	//15:12
	UINT32 resvd4                       :4;	//19:16
	UINT32 resvd5                       :4;	//23:20
	UINT32 resvd6                       :4;	//27:24
	UINT32 resvd7                       :4;	//31:28
	};
}PE_CHPI_APB0_CNT1_F20_T;

/* fw ctrl */
typedef union {
	UINT32 udata32;
	struct {
	UINT32 tm                           :4;	//3:0
	UINT32 s2h                          :4;	//7:4
	UINT32 yg                           :4;	//11:8
	UINT32 resvd3                       :4;	//15:12
	UINT32 resvd4                       :4;	//19:16
	UINT32 resvd5                       :4;	//23:20
	UINT32 resvd6                       :4;	//27:24
	UINT32 resvd7                       :4;	//31:28
	};
}PE_CHPI_APB0_CNT2_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 hs                           :4;	//3:0
	UINT32 pcc                          :4;	//7:4
	UINT32 resvd2                       :4;	//11:8
	UINT32 resvd3                       :4;	//15:12
	UINT32 resvd4                       :4;	//19:16
	UINT32 resvd5                       :4;	//23:20
	UINT32 resvd6                       :4;	//27:24
	UINT32 resvd7                       :4;	//31:28
	};
}PE_CHPI_APB0_CNT3_F20_T;

typedef struct
{
	PE_CHPI_APB_INFO_F20_T              info;
	PE_CHPI_APB0_CNT0_F20_T             cnt0;
	PE_CHPI_APB0_CNT1_F20_T             cnt1;
	PE_CHPI_APB0_CNT2_F20_T             cnt2;
	PE_CHPI_APB0_CNT3_F20_T             cnt3;
	PE_CHPI_APB_POS_F20_T               pos[32];
}PE_CHPI_APB0_DB_H_F20_T;

typedef struct
{
	UINT32                              resvd[461];
}PE_CHPI_APB0_RESVD0_F20_T;

typedef struct
{
	UINT32                              resvd[286];
}PE_CHPI_APB0_RESVD1_F20_T;

/* causion : Max Struct Size : 13312 + 12 Byte (Data 13k + Header 4 Byte + CRC0/1 8 Byte) -> u32[3331]*/
/* header : [31]Last_Block,[30:28]Reserved,[27:20]Packet_Number,[19]Addr_AI,[17:16]Mode,[15:00]Data_Size(Byte) */
/* endian conversion : setting data 0xABCDEF0 -> ddr data 0xF0DECDAB */
/* 20200309
[CHI]head   (  148)(  37 x 4(byte) = 0x0094) (0x0004)
[CHI]cmn0   (   24)(   3 x 8(byte) = 0x0018) (0x0098)
[CHI]cen0   ( 3296)( 412 x 8(byte) = 0x0ce0) (0x00b0)
[CHI]cen1   (  328)(  41 x 8(byte) = 0x0148) (0x0d90)
[CHI]cw0    (  152)(  19 x 8(byte) = 0x0098) (0x0ed8)
[CHI]vsp0   (  160)(  20 x 8(byte) = 0x00a0) (0x0f70)
[CHI]dse0   (  416)(  52 x 8(byte) = 0x01a0) (0x1010)
[CHI]dce0   (  296)(  37 x 8(byte) = 0x0128) (0x11b0)
[CHI]dtm0   ( 2488)( 311 x 8(byte) = 0x09b8) (0x12d8)
[CHI]fsw0   (   64)(   8 x 8(byte) = 0x0040) (0x1c90)
[CHI]resvd0 ( 1844)( 461 x 4(byte) = 0x0734) (0x1cd0)
[CHI]tm     ( 1656)( 207 x 8(byte) = 0x0678) (0x2404)
[CHI]s2h    (  840)( 105 x 8(byte) = 0x0348) (0x2a7c)
[CHI]yg     (  280)(  35 x 8(byte) = 0x0118) (0x2dc4)
[CHI]hs     (  136)(  17 x 8(byte) = 0x0088) (0x2edc)
[CHI]pcc    (   40)(   5 x 8(byte) = 0x0028) (0x2f64)
[CHI]resvd1 ( 1144)( 286 x 4(byte) = 0x0478) (0x2f8c)
[CHI]TOTAL  (13324)(0x340c) vs (13324)(0x340c)
*/
typedef struct
{
	UINT32                               head0;
	PE_CHPI_APB0_DB_H_F20_T              head1;
	PE_CHPI_CMN0_F20_T                    cmn0;//00
	PE_CHPI_CEN0_F20_T                    cen0;//01
	PE_CHPI_CEN1_F20_T                    cen1;//02
	PE_CHPI_CW0_F20_T                      cw0;//03
	PE_CHPI_VSP0_F20_T                    vsp0;//04
	PE_CHPI_DSE0_F20_T                    dse0;//05
	PE_CHPI_DCE0_F20_T                    dce0;//06
	PE_CHPI_DTM0_F20_T                    dtm0;//07
	PE_CHPI_FSW0_F20_T                    fsw0;//08
	PE_CHPI_APB0_RESVD0_F20_T           resvd0;
	PE_CHPI_HDR_TM_F20_T                    tm;//16
	PE_CHPI_HDR_S2H_F20_T                  s2h;//17
	PE_CHPI_HDR_YG_F20_T                    yg;//18
	PE_CHPI_HDR_HS_F20_T                    hs;//24
	PE_CHPI_HDR_PCC_F20_T                  pcc;//25
	PE_CHPI_APB0_RESVD1_F20_T           resvd1;
	UINT32                                crc0;
	UINT32                                crc1;
}PE_CHPI_REG_F20_T;

/* dbg : check size */
typedef struct
{
	UINT32                               head0;
	PE_CHPI_APB0_DB_H_F20_T              head1;
	PE_CHPI_CMN0_F20_T                    cmn0;//00
	PE_CHPI_CEN0_F20_T                    cen0;//01
	PE_CHPI_CEN1_F20_T                    cen1;//02
	PE_CHPI_CW0_F20_T                      cw0;//03
	PE_CHPI_VSP0_F20_T                    vsp0;//04
	PE_CHPI_DSE0_F20_T                    dse0;//05
	PE_CHPI_DCE0_F20_T                    dce0;//06
	PE_CHPI_DTM0_F20_T                    dtm0;//07
	PE_CHPI_FSW0_F20_T                    fsw0;//08
	PE_CHPI_APB0_RESVD0_F20_T           resvd0;
}PE_CHPI_REG0_F20_T;

/* dbg : check size */
typedef struct
{
	PE_CHPI_HDR_TM_F20_T                    tm;//16
	PE_CHPI_HDR_S2H_F20_T                  s2h;//17
	PE_CHPI_HDR_YG_F20_T                    yg;//18
	PE_CHPI_HDR_HS_F20_T                    hs;//24
	PE_CHPI_HDR_PCC_F20_T                  pcc;//25
	PE_CHPI_APB0_RESVD1_F20_T           resvd1;
	UINT32                                crc0;
	UINT32                                crc1;
}PE_CHPI_REG1_F20_T;

#else

typedef struct
{
	UINT32                                     head;//eg.APB:0x0A00abcd(0xcdab000A),FW Clear:0x0EE0abcd(0xcdabE00E)
	UINT32                                     resvd[1504];
	UINT32                                     crc;//default:0xFFFFFFFF
}PE_CHPI_RESVD0_F20_T;

typedef struct
{
	UINT32                                     head;//eg.APB:0x0A00abcd(0xcdab000A),FW Clear:0x0EE0abcd(0xcdabE00E)
	UINT32                                     resvd[274];
	UINT32                                     crc;//default:0xFFFFFFFF
}PE_CHPI_RESVD1_F20_T;

/* causion : Max Struct Size : 17408 + 8 Byte (Data 17k + HW Header 4 Byte + HW CRC 4 Byte) -> u32[4354]*/
/* header : [31]Last_Block,[30:28]Reserved,[27:20]Packet_Number,[19]Addr_AI,[17:16]Mode,[15:00]Data_Size(Byte) */
/* endian conversion : setting data 0xABCDEF0 -> ddr data 0xF0DECDAB */
/* 20200309
[CHI]cmn0   (   32)(   4 x 8(byte) = 0x0020) (0x0000)
[CHI]cen0   ( 3304)( 413 x 8(byte) = 0x0ce8) (0x0020)
[CHI]cen1   (  336)(  42 x 8(byte) = 0x0150) (0x0d08)
[CHI]cw0    (  160)(  20 x 8(byte) = 0x00a0) (0x0e58)
[CHI]vsp0   (  168)(  21 x 8(byte) = 0x00a8) (0x0ef8)
[CHI]dse0   (  424)(  53 x 8(byte) = 0x01a8) (0x0fa0)
[CHI]dce0   (  304)(  38 x 8(byte) = 0x0130) (0x1148)
[CHI]dtm0   ( 2496)( 312 x 8(byte) = 0x09c0) (0x1278)
[CHI]fsw0   (   72)(   9 x 8(byte) = 0x0048) (0x1c38)
[CHI]resvd0 ( 6024)(1506 x 4(byte) = 0x1788) (0x1c80)
[CHI]tm     ( 1664)( 208 x 8(byte) = 0x0680) (0x3408)
[CHI]s2h    (  848)( 106 x 8(byte) = 0x0350) (0x3a88)
[CHI]yg     (  288)(  36 x 8(byte) = 0x0120) (0x3dd8)
[CHI]hs     (  144)(  18 x 8(byte) = 0x0090) (0x3ef8)
[CHI]pcc    (   48)(   6 x 8(byte) = 0x0030) (0x3f88)
[CHI]resvd1 ( 1104)( 276 x 4(byte) = 0x0450) (0x3fb8)
[CHI]TOTAL  (17416)(0x4408) vs (17416)(0x4408)
*/
typedef struct
{
	PE_CHPI_CMN0_F20_T                         cmn0;
	PE_CHPI_CEN0_F20_T                         cen0;
	PE_CHPI_CEN1_F20_T                         cen1;
	PE_CHPI_CW0_F20_T                          cw0;
	PE_CHPI_VSP0_F20_T                         vsp0;
	PE_CHPI_DSE0_F20_T                         dse0;
	PE_CHPI_DCE0_F20_T                         dce0;
	PE_CHPI_DTM0_F20_T                         dtm0;
	PE_CHPI_FSW0_F20_T                         fsw0;
	PE_CHPI_RESVD0_F20_T                       resvd0;
	PE_CHPI_HDR_TM_F20_T                       tm;
	PE_CHPI_HDR_S2H_F20_T                      s2h;
	PE_CHPI_HDR_YG_F20_T                       yg;
	PE_CHPI_HDR_HS_F20_T                       hs;
	PE_CHPI_HDR_PCC_F20_T                      pcc;
	PE_CHPI_RESVD1_F20_T                       resvd1;
}PE_CHPI_REG_F20_T;

/* dbg : check size */
typedef struct
{
	PE_CHPI_CMN0_F20_T                         cmn0;
	PE_CHPI_CEN0_F20_T                         cen0;
	PE_CHPI_CEN1_F20_T                         cen1;
	PE_CHPI_CW0_F20_T                          cw0;
	PE_CHPI_VSP0_F20_T                         vsp0;
	PE_CHPI_DSE0_F20_T                         dse0;
	PE_CHPI_DCE0_F20_T                         dce0;
	PE_CHPI_DTM0_F20_T                         dtm0;
	PE_CHPI_FSW0_F20_T                         fsw0;
	PE_CHPI_RESVD0_F20_T                       resvd0;
}PE_CHPI_REG0_F20_T;

/* dbg : check size */
typedef struct
{
	PE_CHPI_HDR_TM_F20_T                       tm;
	PE_CHPI_HDR_S2H_F20_T                      s2h;
	PE_CHPI_HDR_YG_F20_T                       yg;
	PE_CHPI_HDR_HS_F20_T                       hs;
	PE_CHPI_HDR_PCC_F20_T                      pcc;
	PE_CHPI_RESVD1_F20_T                       resvd1;
}PE_CHPI_REG1_F20_T;
#endif

#endif
