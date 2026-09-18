#ifndef _PE_CHPI_TBL_O26F22A0_H_
#define _PE_CHPI_TBL_O26F22A0_H_

#include "pe_chpi_cco_tbl_o26f22a0.h"
#include "pe_chpi_obc_tbl_o26f22a0.h"
#include "pe_chpi_shp_tbl_o26f22a0.h"
#include "pe_chpi_tnr_tbl_o26f22a0.h"
#include "pe_chpi_dnr_tbl_o26f22a0.h"

typedef union {
	UINT32 udata32;
	struct {
	UINT32 max_num                      :8;	//7:0
	UINT32 resvd                        :12;
	UINT32 bufidx1                      :4;	//23:20
	UINT32 bufidx0                      :4;	//27:24
	UINT32 version                      :4;	//31:28
	};
}PE_CHPI_TBL_INFO_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 ofst                         :16;//15:0
	UINT32 size                         :16;//31:16
	};
}PE_CHPI_TBL_POS_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 cco                          :8;	//7:0
	UINT32 obc                          :8;	//15:8
	UINT32 obe                          :8;	//23:16
	UINT32 amg                          :8;	//31:24
	};
}PE_CHPI_TBL0_CNT0_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 res                          :8;	//7:0
	UINT32 cti                          :8;	//15:8
	UINT32 tnr                          :8;	//23:16
	UINT32 dnr                          :8;	//31:24
	};
}PE_CHPI_TBL0_CNT1_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 osd                          :8;	//7:0
	UINT32 sqm0                         :8;	//15:8
	UINT32 sqm1                         :8;	//23:16
	UINT32 sqm2                         :8;	//31:24
	};
}PE_CHPI_TBL0_CNT2_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 sqm3                         :8;	//7:0
	UINT32 sqm4                         :8;	//15:8
	UINT32 usr0                         :8;	//23:16
	UINT32 usr1                         :8;	//31:24
	};
}PE_CHPI_TBL0_CNT3_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 usr2                         :8;	//7:0
	UINT32 drc                          :8;	//15:8
	UINT32 obec                         :8;	//23:16
	UINT32 resvd2                       :8;	//31:24
	};
}PE_CHPI_TBL0_CNT4_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 resvd0                       :8;	//7:0
	UINT32 resvd1                       :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_TBL0_CNT5_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 resvd0                       :8;	//7:0
	UINT32 resvd1                       :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_TBL0_CNT6_O26F22_T;

typedef union {
	UINT32 udata32;
	struct {
	UINT32 resvd0                       :8;	//7:0
	UINT32 resvd1                       :8;	//15:8
	UINT32 resvd2                       :8;	//23:16
	UINT32 resvd3                       :8;	//31:24
	};
}PE_CHPI_TBL0_CNT7_O26F22_T;

typedef struct
{
	PE_CHPI_TBL_INFO_O26F22_T              info;
	PE_CHPI_TBL0_CNT0_O26F22_T             cnt0;
	PE_CHPI_TBL0_CNT1_O26F22_T             cnt1;
	PE_CHPI_TBL0_CNT2_O26F22_T             cnt2;
	PE_CHPI_TBL0_CNT3_O26F22_T             cnt3;
	PE_CHPI_TBL0_CNT4_O26F22_T             cnt4;
	PE_CHPI_TBL0_CNT5_O26F22_T             cnt5;
	PE_CHPI_TBL0_CNT6_O26F22_T             cnt6;
	PE_CHPI_TBL0_CNT7_O26F22_T             cnt7;
	PE_CHPI_TBL_POS_O26F22_T               pos[32];
}PE_CHPI_TBL0_DB_H_O26F22_T;

typedef struct
{
	UINT32                              resvd[1121];
}PE_CHPI_TBL0_RESVD_O26F22_T;

/* causion : Max Struct Size : 13312 + 12 Byte (Data 13k + Header 4 Byte + CRC0/1 8 Byte) -> u32[3331]*/
/* header : [31]Last_Block,[30:28]Reserved,[27:20]Packet_Number,[19]Addr_AI,[17:16]Mode,[15:00]Data_Size(Byte) */
/* endian conversion : setting data 0xABCDEF0 -> ddr data 0xF0DECDAB */
/*
2021/11/23 14:13
[CHI]head   (  164)(  41 x 4(byte) = 0x00a4) (0x0004)
[CHI]cco    (   16)(   2 x 8(byte) = 0x0010) (0x00a8)
[CHI]obc    (  296)(  37 x 8(byte) = 0x0128) (0x00b8)
[CHI]obe    (  272)(  34 x 8(byte) = 0x0110) (0x01e0)
[CHI]amg    (  896)( 112 x 8(byte) = 0x0380) (0x02f0)
[CHI]res    ( 2264)( 283 x 8(byte) = 0x08d8) (0x0670)
[CHI]cti    (   56)(   7 x 8(byte) = 0x0038) (0x0f48)
[CHI]tnr    (  480)(  60 x 8(byte) = 0x01e0) (0x0f80)
[CHI]dnr    ( 1536)( 192 x 8(byte) = 0x0600) (0x1160)
[CHI]osd    (  992)( 124 x 8(byte) = 0x03e0) (0x1760)
[CHI]sqm0   (  168)(  42 x 4(byte) = 0x00a8) (0x1b40)
[CHI]sqm1   (  292)(  73 x 4(byte) = 0x0124) (0x1be8)
[CHI]sqm2   (   52)(  13 x 4(byte) = 0x0034) (0x1d0c)
[CHI]sqm3   (   68)(  17 x 4(byte) = 0x0044) (0x1d40)
[CHI]sqm4   (  100)(  25 x 4(byte) = 0x0064) (0x1d84)
[CHI]usr0   (  152)(  38 x 4(byte) = 0x0098) (0x1de8)
[CHI]usr1   (   40)(  10 x 4(byte) = 0x0028) (0x1e80)
[CHI]usr2   (   40)(  10 x 4(byte) = 0x0028) (0x1ea8)
[CHI]drc    (  624)( 156 x 4(byte) = 0x0270) (0x1ed0)
[CHI]obec   (  320)(  40 x 8(byte) = 0x0140) (0x2140)
[CHI]resvd  ( 4484)(1121 x 4(byte) = 0x1184) (0x2280)
[CHI]TOTAL  (13324)(0x340c) vs (13324)(0x340c)
*/
typedef struct
{
	UINT32                               head0;
	PE_CHPI_TBL0_DB_H_O26F22_T           head1;
	PE_CHPI_CCO_TBL_O26F22_T               cco;//00
	PE_CHPI_OBC_TBL_O26F22_T               obc;//01
	PE_CHPI_OBE_TBL_O26F22_T               obe;//02
	PE_CHPI_AMG_TBL_O26F22_T               amg;//03
	PE_CHPI_RES_TBL_O26F22_T               res;//04
	PE_CHPI_CTI_TBL_O26F22_T               cti;//05
	PE_CHPI_TNR_TBL_O26F22_T               tnr;//06
	PE_CHPI_DNR_TBL_O26F22_T               dnr;//07
	PE_CHPI_DNR_OSD_TBL_O26F22_T           osd;//08
	PE_CHPI_SHP_UI_SQM_O26F22_T           sqm0;//09
	PE_CHPI_SHP_CMN_SQM_O26F22_T          sqm1;//10
	PE_CHPI_TNR_SQM_O26F22_T              sqm2;//11
	PE_CHPI_DNR_SQM_O26F22_T              sqm3;//12
	PE_CHPI_DNR_DCNT_SQM_O26F22_T         sqm4;//13
	PE_CHPI_TNR_USER_O26F22_T             usr0;//14
	PE_CHPI_DNR_USER_O26F22_T             usr1;//15
	PE_CHPI_DNR_DCNT_USER_O26F22_T        usr2;//16
	PE_CHPI_DRC_CUV_O26F22_T               drc;//17
	PE_CHPI_OBE_C_TBL_O26F22_T            obec;//18
	PE_CHPI_TBL0_RESVD_O26F22_T          resvd;
	UINT32                                crc0;
	UINT32                                crc1;
}PE_CHPI_TBL0_O26F22_T;

#endif
