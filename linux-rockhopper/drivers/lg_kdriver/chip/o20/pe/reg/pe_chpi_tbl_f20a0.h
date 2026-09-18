#ifndef _PE_CHPI_TBL_F20A0_H_
#define _PE_CHPI_TBL_F20A0_H_

#include "pe_chpi_cco_tbl_f20a0.h"
#include "pe_chpi_obc_tbl_f20a0.h"
#include "pe_chpi_shp_tbl_f20a0.h"
#include "pe_chpi_tnr_tbl_f20a0.h"
#include "pe_chpi_dnr_tbl_f20a0.h"

typedef union {
	UINT32 udata32;
	struct {
	UINT32 max_num                      :8;	//7:0
	UINT32 resvd                        :12;
	UINT32 bufidx1                      :4;	//23:20
	UINT32 bufidx0                      :4;	//27:24
	UINT32 version                      :4;	//31:28
	};
}PE_CHPI_TBL_INFO_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 ofst                         :16;//15:0
	UINT32 size                         :16;//31:16
	};
}PE_CHPI_TBL_POS_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 cco                          :4;	//3:0
	UINT32 obo                          :4;	//7:4
	UINT32 obf                          :4;	//11:8
	UINT32 rco                          :4;	//15:12
	UINT32 rcf                          :4;	//19:16
	UINT32 res                          :4;	//23:20
	UINT32 cti                          :4;	//27:24
	UINT32 tnr                          :4;	//31:28
	};
}PE_CHPI_TBL0_CNT0_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 dnr                          :4;	//3:0
	UINT32 psp                          :4;	//7:4
	UINT32 led                          :4;	//11:8
	UINT32 sqm0                         :4;	//15:12
	UINT32 sqm1                         :4;	//19:16
	UINT32 sqm2                         :4;	//23:20
	UINT32 sqm3                         :4;	//27:24
	UINT32 sqm4                         :4;	//31:28
	};
}PE_CHPI_TBL0_CNT1_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 sqm5                         :4;	//3:0
	UINT32 usr0                         :4;	//7:4
	UINT32 usr1                         :4;	//11:8
	UINT32 usr2                         :4;	//15:12
	UINT32 usr3                         :4;	//19:16
	UINT32 drc                          :4;	//23:20
	UINT32 resvd6                       :4;	//27:24
	UINT32 resvd7                       :4;	//31:28
	};
}PE_CHPI_TBL0_CNT2_F20_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 resvd0                       :4;	//3:0
	UINT32 resvd1                       :4;	//7:4
	UINT32 resvd2                       :4;	//11:8
	UINT32 resvd3                       :4;	//15:12
	UINT32 resvd4                       :4;	//19:16
	UINT32 resvd5                       :4;	//23:20
	UINT32 resvd6                       :4;	//27:24
	UINT32 resvd7                       :4;	//31:28
	};
}PE_CHPI_TBL0_CNT3_F20_T;

typedef struct
{
	PE_CHPI_TBL_INFO_F20_T              info;
	PE_CHPI_TBL0_CNT0_F20_T             cnt0;
	PE_CHPI_TBL0_CNT1_F20_T             cnt1;
	PE_CHPI_TBL0_CNT2_F20_T             cnt2;
	PE_CHPI_TBL0_CNT3_F20_T             cnt3;
	PE_CHPI_TBL_POS_F20_T               pos[32];
}PE_CHPI_TBL0_DB_H_F20_T;

typedef struct
{
	UINT32                              resvd[1304];
}PE_CHPI_TBL0_RESVD_F20_T;

/* causion : Max Struct Size : 13312 + 12 Byte (Data 13k + Header 4 Byte + CRC0/1 8 Byte) -> u32[3331]*/
/* header : [31]Last_Block,[30:28]Reserved,[27:20]Packet_Number,[19]Addr_AI,[17:16]Mode,[15:00]Data_Size(Byte) */
/* endian conversion : setting data 0xABCDEF0 -> ddr data 0xF0DECDAB */
/* 20191127
[CHI]head   (  148)(  37 x 4(byte) = 0x0094) (0x0004)
[CHI]cco    (   16)(   2 x 8(byte) = 0x0010) (0x0098)
[CHI]obo    (  368)(  46 x 8(byte) = 0x0170) (0x00a8)
[CHI]obf    (  368)(  46 x 8(byte) = 0x0170) (0x0218)
[CHI]rco    (  256)(  32 x 8(byte) = 0x0100) (0x0388)
[CHI]rcf    (  256)(  32 x 8(byte) = 0x0100) (0x0488)
[CHI]res    ( 2000)( 250 x 8(byte) = 0x07d0) (0x0588)
[CHI]cti    (   56)(   7 x 8(byte) = 0x0038) (0x0d58)
[CHI]tnr    (  480)(  60 x 8(byte) = 0x01e0) (0x0d90)
[CHI]dnr    ( 1144)( 143 x 8(byte) = 0x0478) (0x0f70)
[CHI]psp    (  656)(  82 x 8(byte) = 0x0290) (0x13e8)
[CHI]led    (  752)(  94 x 8(byte) = 0x02f0) (0x1678)
[CHI]sqm0   (  168)(  42 x 4(byte) = 0x00a8) (0x1968)
[CHI]sqm1   (  212)(  53 x 4(byte) = 0x00d4) (0x1a10)
[CHI]sqm2   (   52)(  13 x 4(byte) = 0x0034) (0x1ae4)
[CHI]sqm3   (   68)(  17 x 4(byte) = 0x0044) (0x1b18)
[CHI]sqm4   (  100)(  25 x 4(byte) = 0x0064) (0x1b5c)
[CHI]sqm5   (  100)(  25 x 4(byte) = 0x0064) (0x1bc0)
[CHI]usr0   (  152)(  38 x 4(byte) = 0x0098) (0x1c24)
[CHI]usr1   (   40)(  10 x 4(byte) = 0x0028) (0x1cbc)
[CHI]usr2   (   40)(  10 x 4(byte) = 0x0028) (0x1ce4)
[CHI]usr3   (   40)(  10 x 4(byte) = 0x0028) (0x1d0c)
[CHI]drc    (  624)( 156 x 4(byte) = 0x0270) (0x1d34)
[CHI]resvd  ( 5216)(1304 x 4(byte) = 0x1460) (0x1fa4)
[CHI]TOTAL  (13324)(0x340c) vs (13324)(0x340c)
*/
typedef struct
{
	UINT32                               head0;
	PE_CHPI_TBL0_DB_H_F20_T              head1;
	PE_CHPI_CCO_TBL_F20_T                  cco;//00
	PE_CHPI_OBO_TBL_F20_T                  obo;//01
	PE_CHPI_OBF_TBL_F20_T                  obf;//02
	PE_CHPI_RCO_TBL_F20_T                  rco;//03
	PE_CHPI_RCF_TBL_F20_T                  rcf;//04
	PE_CHPI_RES_TBL_F20_T                  res;//05
	PE_CHPI_CTI_TBL_F20_T                  cti;//06
	PE_CHPI_TNR_TBL_F20_T                  tnr;//07
	PE_CHPI_DNR_TBL_F20_T                  dnr;//08
	PE_CHPI_DNR_PSP_TBL_F20_T              psp;//09
	PE_CHPI_DNR_LED_TBL_F20_T              led;//10
	PE_CHPI_SHP_UI_SQM_F20_T              sqm0;//11
	PE_CHPI_SHP_CMN_SQM_F20_T             sqm1;//12
	PE_CHPI_TNR_SQM_F20_T                 sqm2;//13
	PE_CHPI_DNR_SQM_F20_T                 sqm3;//14
	PE_CHPI_DNR_DCNT_SQM_F20_T            sqm4;//15
	PE_CHPI_LED_DCNT_SQM_F20_T            sqm5;//16
	PE_CHPI_TNR_USER_F20_T                usr0;//17
	PE_CHPI_DNR_USER_F20_T                usr1;//18
	PE_CHPI_DNR_DCNT_USER_F20_T           usr2;//19
	PE_CHPI_LED_DCNT_USER_F20_T           usr3;//20
	PE_CHPI_DRC_CUV_F20_T                 drc;//21
	PE_CHPI_TBL0_RESVD_F20_T             resvd;
	UINT32                                crc0;
	UINT32                                crc1;
}PE_CHPI_TBL0_F20_T;

#endif
