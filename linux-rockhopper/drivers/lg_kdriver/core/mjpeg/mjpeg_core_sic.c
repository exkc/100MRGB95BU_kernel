/*
SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
Copyright(c) 1998-2013 by LG Electronics Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
*/

/** @file
 *
 *  lg mjpeg decoder ip interface implementation.
 *
 *  author		Jihoon Lee (gaius.lee@lge.com)
 *  version		1.0
 *  date		2015.02.04
 *  note		Additional information.
 *
 *  @addtogroup lg1152_mjpeg
 *	@{
 */

/*-----------------------------------------------------------------------------
        Control Constants
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        File Inclusions
-----------------------------------------------------------------------------*/
#include <asm/io.h> // for ioremap
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/mm.h>
#include <linux/slab.h> /**< kmalloc() */
#include <linux/spinlock.h>

#include "mjpeg_cfg.h"
#include "mjpeg_core_sic.h"
#include "mjpeg_drv.h"
#include "mjpeg_queue.h"
#include "os_util.h"

#include "lgjpeg_reg.h"

static int enable_icod_dec_time = 0;
module_param(enable_icod_dec_time, int, 0644);

/*-----------------------------------------------------------------------------
        Constant Definitions
-----------------------------------------------------------------------------*/
#define DISABLE 0
#define ENABLE 1

enum {
	HUFF_DC_INDEX0 = 0,
	HUFF_AC_INDEX0 = 1,
	HUFF_DC_INDEX1 = 2,
	HUFF_AC_INDEX1 = 3,
};

enum {
	COMPONENT_Y = 0,
	COMPONENT_CB = 1,
	COMPONENT_CR = 2,
};

enum {
	REG_DPB0 = 1 << 0,
	REG_DPB1 = 1 << 1,
	REG_DPB2 = 1 << 2,
	REG_DPB3 = 1 << 3,
	REG_DPB_ALL = 0xf,
};

enum {
	COORD_Y = 0,
	COORD_X = 1,
};

/*-----------------------------------------------------------------------------
        Macro Definitions
-----------------------------------------------------------------------------*/
#ifndef MIN
#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#endif

#define _LOCK()
#define _UNLOCK()

/*-----------------------------------------------------------------------------
        Type Definitions
-----------------------------------------------------------------------------*/
typedef struct {
	LX_MJPEG_FRAME_HEADER_T stFrameHeader;
	LX_MJPEG_SCAN_HEADER_T stScanHeader;
	UINT16 ui16ResetInterval;
	LX_MJPEG_QUANTIZATION_TABLE_T stQuantiztionTables[4];
	LX_MJPEG_HUFFMAN_TABLE_T stHuffmanTables[4];

	LX_MJPEG_FORMAT_T eFormat;
	UINT16 ui16Height;
	UINT16 ui16Width;

	UINT32 ui32AddressY;
	UINT32 ui32AddressCb;
	UINT32 ui32AddressCr;
	UINT32 ui32StrideY;
	UINT32 ui32StrideC;
	UINT32 ui32SizeY;
	UINT32 ui32SizeCb;
	UINT32 ui32SizeCr;

	BOOLEAN bUVInterleaved;

	LX_MJPEG_ROTATION_T eRotation;
	LX_MJPEG_MIRRORING_T eMirroring;
	LX_MJPEG_SCALING_T eScaleHorizontal; // Deocder only
	LX_MJPEG_SCALING_T eScaleVertical; // Decoder only
	LX_MJPEG_OPERATION_T eOperation; // Decoder only
	BOOLEAN bQuality; // Encoder only
	UINT32 nQuality; // Encoder only 0-100 (0:low quality, 100:hight quality)
} LX_MJPEG_INFO_T;

/*-----------------------------------------------------------------------------
        External Function Prototype Declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        External Variables
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
        global Functions
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
        global Variables
-----------------------------------------------------------------------------*/
volatile JDEC_REG *gpRealRegLGJPEG = NULL; /** MJPEG register */
JDEC_REG *gpRegLGJPEG = NULL; /** MJPEG shadow register */

static MJPEG_WORK_QUEUE_T _gJPEGWorkQueue = {};

OS_EVENT_T *gpstEvent = NULL;
OS_EVENT_T gstEvent = {};

static BOOLEAN _gbUseQueue = FALSE;

static LXMJPEG_MSG_QUEUE_T _gMsgQueue;

/*-----------------------------------------------------------------------------
        Static Function Prototypes Declarations
-----------------------------------------------------------------------------*/
static void _MJPEG_AddList(UINT32 val);

/*-----------------------------------------------------------------------------
        Static Variables
-----------------------------------------------------------------------------*/

static LX_MJPEG_HEADER_T *_g_pstHeader;
static LX_MJPEG_IMAGE_INFO_T *_g_pstImageInfo;
static LX_MJPEG_IMAGE_BUF_T *g_pstImageBuffer;
static LX_MJPEG_OPTION_T *_g_pstOption;

/*========================================================================================
        Implementation Group
========================================================================================*/

// API_JPEG_INIT();
static void _REG_SetInit(BOOLEAN bUVInterleaved)
{
	MJPEG_INFO("Called.\n");

	/* GAMU setting what you want */
	/*
   * reg_gmau0Config.w = 0;
   * reg_gmau0Config.f.reg_gmau0_cmd_dly_cnt = 0;//0xFFFF;
   * reg_gmau0Config.f.reg_gmau0_cmd_pri1 = 0;
   * reg_gmau0Config.f.reg_gmau0_cmd_pri2 = 0;
   * reg_gmau0Config.f.reg_gmau0_cmd_txid = 0;
   *
   * reg_gmau1Config.w = 0;
   * reg_gmau1Config.f.reg_gmau0_cmd_dly_cnt = 0;//0xFF;
   * reg_gmau1Config.f.reg_gmau0_cmd_pri1 = 0;
   * reg_gmau1Config.f.reg_gmau0_cmd_pri2 = 0;
   * reg_gmau1Config.f.reg_gmau0_cmd_txid = 1;
   */

	LGJPEG_RdFL(gmau0_config);
	LGJPEG_Wr01(gmau0_config, reg_gmau0_cmd_dly_cnt, 0);
	LGJPEG_Wr01(gmau0_config, reg_gmau0_cmd_pri1, 0);
	LGJPEG_Wr01(gmau0_config, reg_gmau0_cmd_pri2, 0);
	LGJPEG_Wr01(gmau0_config, reg_gmau0_cmd_txid, 0);
	LGJPEG_WrFL(gmau0_config);

	LGJPEG_RdFL(gmau1_config);
	LGJPEG_Wr01(gmau1_config, reg_gmau0_cmd_dly_cnt, 0);
	LGJPEG_Wr01(gmau1_config, reg_gmau0_cmd_pri1, 0);
	LGJPEG_Wr01(gmau1_config, reg_gmau0_cmd_pri2, 0);
	LGJPEG_Wr01(gmau1_config, reg_gmau0_cmd_txid, 1);
	LGJPEG_WrFL(gmau1_config);

	/*
   * wmif_ctrl.w = 0;
   * wmif_ctrl.f.reg_wmif_endian = 0;
   * wmif_ctrl.f.reg_dpb0_clear = 1;
   * wmif_ctrl.f.reg_dpb1_clear = 1;
   * wmif_ctrl.f.reg_dpb2_clear = 1;
   * wmif_ctrl.f.reg_dpb3_clear = 1;
   * wmif_ctrl.f.reg_comp12_interleaving = bUVInterleaved;
   */

	LGJPEG_RdFL(wmif_ctrl);
	LGJPEG_Wr01(wmif_ctrl, rem_bvalid_chk, 0);
	LGJPEG_Wr01(wmif_ctrl, reg_wmif_endian, 0);
	LGJPEG_Wr01(wmif_ctrl, reg_dpb0_clear, 1);
	LGJPEG_Wr01(wmif_ctrl, reg_dpb1_clear, 1);
	LGJPEG_Wr01(wmif_ctrl, reg_dpb2_clear, 1);
	LGJPEG_Wr01(wmif_ctrl, reg_dpb3_clear, 1);
	LGJPEG_Wr01(wmif_ctrl, reg_comp12_interleaving, bUVInterleaved);
	LGJPEG_WrFL(wmif_ctrl);

	/*
   * rmif_ctrl.w = 0;
   * rmif_ctrl.f.reg_rmif_endian = 1;
   * rmif_ctrl.f.reg_rmif_unit = 0xF;
   */
	LGJPEG_RdFL(rmif_ctrl);
	LGJPEG_Wr01(rmif_ctrl, reg_rmif_endian, 1);
	LGJPEG_Wr01(rmif_ctrl, reg_rmif_unit, 0xF);
	LGJPEG_WrFL(rmif_ctrl);

	/*
   * reg_interrupt.w = 0;
   * reg_interrupt.f.intr_dec_done0 = 1;
   * reg_interrupt.f.intr_dec_done1 = 1;
   * reg_interrupt.f.intr_dec_done2 = 1;
   * reg_interrupt.f.intr_dec_done3 = 1;
   * reg_interrupt.f.intr_pic_done = 1;
   * reg_interrupt.f.intr_buffer_empty = 1;   //TODO
   * reg_interrupt.f.intr_pic_done_err = 1;
   * reg_interrupt.f.intr_start_err = 1;
   * reg_interrupt.f.intr_stream_err = 1; //TODO
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_INTR_EN, reg_interrupt.w );
   */

	LGJPEG_RdFL(intr_en);
	LGJPEG_Wr01(intr_en, intr_dec_done0, 1);
	LGJPEG_Wr01(intr_en, intr_dec_done1, 1);
	LGJPEG_Wr01(intr_en, intr_dec_done2, 1);
	LGJPEG_Wr01(intr_en, intr_dec_done3, 1);

	LGJPEG_Wr01(intr_en, intr_pic_done, 1);
	LGJPEG_Wr01(intr_en, intr_buffer_empty, 1); // TODO
	LGJPEG_Wr01(intr_en, intr_pic_done_err, 1);
	LGJPEG_Wr01(intr_en, intr_start_err, 1);
	LGJPEG_Wr01(intr_en, intr_stream_err, 1); // TODO
	LGJPEG_WrFL(intr_en);
}

static void _REG_SetCPB(UINT32 addr, UINT32 length)
{
	UINT32 val = 0;

	MJPEG_INFO("Called.\n");

	/*
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_CPB_BASE, dstAddress );
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_CPB_END, dstAddress + size );    //hjkim
   * test for cpb_empty_interrupt
   * //jpeg_bus_wr(REG_BASE_ICOD, AD_CPB_END , dstAddress+size-0x30); //test for
   * cpb_empty_interrupt prdata = bus_rd ( REG_BASE_ICOD, AD_RMIF_CTRL );
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_RMIF_CTRL, prdata | 0x10 );
   */

	LGJPEG_RdFL(cpb_base);
	LGJPEG_Wr(cpb_base, addr);
	LGJPEG_WrFL(cpb_base);

	LGJPEG_RdFL(cpb_end);
	LGJPEG_Wr(cpb_end, addr + length);
	LGJPEG_WrFL(cpb_end);

	LGJPEG_RdFL(rmif_ctrl);
	LGJPEG_Rd01(rmif_ctrl, reg_rmif_unit, val);
	LGJPEG_Wr01(rmif_ctrl, reg_rmif_unit, val | 0x10);
	LGJPEG_WrFL(rmif_ctrl);
}

static void _REG_ClearDPB(int dpbNum)
{
	MJPEG_INFO("Clear 0x%x\n", dpbNum);

	LGJPEG_RdFL(wmif_ctrl);
	if (dpbNum & REG_DPB0)
		LGJPEG_Wr01(wmif_ctrl, reg_dpb0_clear, 1);
	if (dpbNum & REG_DPB1)
		LGJPEG_Wr01(wmif_ctrl, reg_dpb1_clear, 1);
	if (dpbNum & REG_DPB2)
		LGJPEG_Wr01(wmif_ctrl, reg_dpb2_clear, 1);
	if (dpbNum & REG_DPB3)
		LGJPEG_Wr01(wmif_ctrl, reg_dpb3_clear, 1);
	LGJPEG_WrFL(wmif_ctrl);
}

static UINT16 _REG_GetCurrent_XY(BOOLEAN bIsX)
{
	UINT16 coord = 0;

	LGJPEG_RdFL(mon_wmif2);
	if (bIsX == COORD_X)
		LGJPEG_Rd01(mon_wmif2, ro_mcu_x, coord);
	else
		LGJPEG_Rd01(mon_wmif2, ro_mcu_y, coord);

	return coord;
}

static void _REG_SetDPB(LX_MJPEG_IMAGE_BUF_T *i_pstImageBuffer,
						LX_MJPEG_OPERATION_T eOperation, BOOLEAN bUVInterleaved)
{
	UINT32 sizeY, sizeCb, sizeCr;

	sizeY = i_pstImageBuffer->ui32SizeY / 2;
	sizeCb = i_pstImageBuffer->ui32SizeCb / 2;
	sizeCr = i_pstImageBuffer->ui32SizeCr / 2;

	// 2015.04.29 gaius.lee - jpeg decoder에서 interleaved 일 경우 *2 하지 않아도
	// 된다. ( 위에서는 하고 있으므로 아래에서 수정 )
	if (bUVInterleaved) {
		i_pstImageBuffer->ui32StrideC = i_pstImageBuffer->ui32StrideC / 2;
	}

	LGJPEG_RdFL(dpb0_base_comp0);
	LGJPEG_Wr(dpb0_base_comp0, i_pstImageBuffer->ui32AddressY);
	LGJPEG_WrFL(dpb0_base_comp0);

	LGJPEG_RdFL(dpb0_base_comp1);
	LGJPEG_Wr(dpb0_base_comp1, i_pstImageBuffer->ui32AddressCb);
	LGJPEG_WrFL(dpb0_base_comp1);

	LGJPEG_RdFL(dpb0_base_comp2);
	LGJPEG_Wr(dpb0_base_comp2, i_pstImageBuffer->ui32AddressCr);
	LGJPEG_WrFL(dpb0_base_comp2);

	LGJPEG_RdFL(dpb1_base_comp0);
	LGJPEG_Wr(dpb1_base_comp0, i_pstImageBuffer->ui32AddressY + sizeY);
	LGJPEG_WrFL(dpb1_base_comp0);

	LGJPEG_RdFL(dpb1_base_comp1);
	LGJPEG_Wr(dpb1_base_comp1, i_pstImageBuffer->ui32AddressCb + sizeCb);
	LGJPEG_WrFL(dpb1_base_comp1);

	LGJPEG_RdFL(dpb1_base_comp2);
	LGJPEG_Wr(dpb1_base_comp2, i_pstImageBuffer->ui32AddressCr + sizeCr);
	LGJPEG_WrFL(dpb1_base_comp2);

	LGJPEG_RdFL(stride_comp0);
	LGJPEG_Wr(stride_comp0, i_pstImageBuffer->ui32StrideY);
	LGJPEG_WrFL(stride_comp0);

	LGJPEG_RdFL(stride_comp1);
	LGJPEG_Wr(stride_comp1, i_pstImageBuffer->ui32StrideC);
	LGJPEG_WrFL(stride_comp1);

	LGJPEG_RdFL(stride_comp2);
	LGJPEG_Wr(stride_comp2, i_pstImageBuffer->ui32StrideC);
	LGJPEG_WrFL(stride_comp2);

	MJPEG_INFO("DPB0_0 = 0x%08X\n", i_pstImageBuffer->ui32AddressY);
	MJPEG_INFO("DPB0_1 = 0x%08X\n", i_pstImageBuffer->ui32AddressCb);
	MJPEG_INFO("DPB0_2 = 0x%08X\n", i_pstImageBuffer->ui32AddressCr);
}

static void _REG_SetPicInfo(UINT32 picWidth, UINT32 picHeight)
{
	UINT8 format = 0;

	MJPEG_INFO("Called.\n");

	switch (_g_pstImageInfo->eFormat) {
	case LX_MJPEG_FORMAT_420:
		format = 3;
		break;
	case LX_MJPEG_FORMAT_422:
		format = 1;
		break;
	case LX_MJPEG_FORMAT_224:
		format = 2;
		break;
	case LX_MJPEG_FORMAT_444:
		format = 0;
		break;
	case LX_MJPEG_FORMAT_400:
		format = 4;
		break;
	default:
		MJPEG_ERROR("Format???\n");
		break;
	}
	/*
   * reg_picturesize.w = 0;
   * reg_picturesize.f.reg_pic_height = inputSt->decSamplesInPicHeight;
   * reg_picturesize.f.reg_pic_width = inputSt->decSamplesInPicWidth;
   */
	LGJPEG_RdFL(picture_size);
	LGJPEG_Wr01(picture_size, reg_pic_width, picWidth);
	LGJPEG_Wr01(picture_size, reg_pic_height, picHeight);
	LGJPEG_WrFL(picture_size);

	// reg_inputformat.f.reg_mcu_size_comp0 =
	// getMCUsizeMode(inputSt->componentAttributes[0].hi << 8 |
	// inputSt->componentAttributes[0].vi);; reg_inputformat.f.reg_mcu_size_comp1
	// = getMCUsizeMode(inputSt->componentAttributes[1].hi << 8 |
	// inputSt->componentAttributes[1].vi);; reg_inputformat.f.reg_mcu_size_comp2
	// = getMCUsizeMode(inputSt->componentAttributes[2].hi << 8 |
	// inputSt->componentAttributes[2].vi);; reg_inputformat.f.reg_component_num =
	// inputSt->nf;
	/*
   * reg_inputformat.w = 0;
   * reg_inputformat.f.reg_file_format = inputSt->inputFormat;
   * reg_inputformat.f.reg_auto_stride_en = 0;
   * reg_inputformat.f.reg_htable_sel_comp0dc =
   * inputSt->componentAttributes[0].td;
   * reg_inputformat.f.reg_htable_sel_comp0ac =
   * inputSt->componentAttributes[0].ta;
   * reg_inputformat.f.reg_htable_sel_comp1dc =
   * inputSt->componentAttributes[1].td;
   * reg_inputformat.f.reg_htable_sel_comp1ac =
   * inputSt->componentAttributes[1].ta;
   * reg_inputformat.f.reg_htable_sel_comp2dc =
   * inputSt->componentAttributes[2].td;
   * reg_inputformat.f.reg_htable_sel_comp2ac =
   * inputSt->componentAttributes[2].ta; reg_inputformat.f.reg_qtable_sel_comp0
   * = inputSt->componentAttributes[0].tq;
   * reg_inputformat.f.reg_qtable_sel_comp1 =
   * inputSt->componentAttributes[1].tq; reg_inputformat.f.reg_qtable_sel_comp2
   * = inputSt->componentAttributes[2].tq;
   *
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_PICTURE_SIZE, reg_picturesize.w );
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_STRIDE_COMP0, inputSt->stride );
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_STRIDE_COMP1, inputSt->cStride );
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_STRIDE_COMP2, inputSt->cStride );
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_INPUT_FORMAT, reg_inputformat.w );
   */
	LGJPEG_RdFL(input_format);
	LGJPEG_Wr01(input_format, reg_auto_stride_en, FALSE);
	LGJPEG_Wr01(input_format, reg_file_format, format);
	LGJPEG_Wr01(
			input_format, reg_htable_sel_comp0dc,
			_g_pstHeader->stScanHeader.stComponents[0].ui8DC_HuffmanTableID);
	LGJPEG_Wr01(
			input_format, reg_htable_sel_comp0ac,
			_g_pstHeader->stScanHeader.stComponents[0].ui8AC_HuffmanTableID);
	LGJPEG_Wr01(
			input_format, reg_htable_sel_comp1dc,
			_g_pstHeader->stScanHeader.stComponents[1].ui8DC_HuffmanTableID);
	LGJPEG_Wr01(
			input_format, reg_htable_sel_comp1ac,
			_g_pstHeader->stScanHeader.stComponents[1].ui8AC_HuffmanTableID);
	LGJPEG_Wr01(
			input_format, reg_htable_sel_comp2dc,
			_g_pstHeader->stScanHeader.stComponents[2].ui8DC_HuffmanTableID);
	LGJPEG_Wr01(
			input_format, reg_htable_sel_comp2ac,
			_g_pstHeader->stScanHeader.stComponents[2].ui8AC_HuffmanTableID);
	LGJPEG_Wr01(input_format, reg_qtable_sel_comp0,
				_g_pstHeader->stFrameHeader.stComponents[0].ui8QTableID);
	LGJPEG_Wr01(input_format, reg_qtable_sel_comp1,
				_g_pstHeader->stFrameHeader.stComponents[1].ui8QTableID);
	LGJPEG_Wr01(input_format, reg_qtable_sel_comp2,
				_g_pstHeader->stFrameHeader.stComponents[2].ui8QTableID);
	LGJPEG_WrFL(input_format);

	/*
   * data = inputSt->restartInterval;
   * if ( data == 0 )
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_RESET_PRED, data );
   * else
   * jpeg_bus_wr ( REG_BASE_ICOD, AD_RESET_PRED, ( data | 0x10000 ) );
   */

	LGJPEG_RdFL(reset_pred);
	LGJPEG_Wr01(reset_pred, reg_reset_pre_interval,
				_g_pstHeader->ui16ResetInterval);
	LGJPEG_Wr01(reset_pred, reg_reset_pred_en,
				(_g_pstHeader->ui16ResetInterval) ? 1 : 0);
	LGJPEG_Wr01(
			reset_pred, stream_left_err_en,
			1); /* [12] 3648x2736-3.MPO 에서 STREAM ERROR나는 문제 해결. M16+
                     만 가능   */
	LGJPEG_Wr01(reset_pred, clipping_en,
				1); /* 28.jpg 에서 깨진 부분이 흰색으로 표시되는 현상 제거. M16+
                     만 가능 */
	LGJPEG_WrFL(reset_pred);

	MJPEG_INFO("END\n");
}

static int _generateDecodeTables(UINT8 *BITS, UINT32 *MAXCODE, UINT32 *VALPTR,
								 UINT32 *CODE)
{
	// Organize Huffman Codes to make the decoding process easier
	UINT32 i, index = 0;
	MJPEG_INFO("Called.\n");

	for (i = 0; i < 16; i++) {
		if (BITS[i] == 0) {
			MAXCODE[i] = -1;
		} else {
			VALPTR[i] = index;
			index = index + BITS[i] - 1;
			MAXCODE[i] = CODE[index];
			index += 1;
		}
	}
	MJPEG_INFO("END");
	return 0;
}

static int _generateCodeTable(UINT8 *TABLE_SIZE, UINT32 *CODE)
{
	// Huffman Codes Generation
	UINT32 index = 0, code = 0, length = 1;
	UINT32 count = 0;

	MJPEG_INFO("Called.\n");
	while (1) {
		// MJPEG_INFO ( "length =  %d TABLE_SIZE[%d] = %d\n", length, index,
		// TABLE_SIZE[index] );
		if (length == TABLE_SIZE[index]) {
			CODE[index] = code;
			code += 1;
			index += 1;
		} else {
			if (TABLE_SIZE[index] == 0)
				break;
			code <<= 1;
			length += 1;
		}

		// gaius.lee for prevent infinite loop
		if (count > 1024) {
			MJPEG_ERROR("Over Code.. \n");
			break;
		}

		count++;
	}
	MJPEG_INFO("END");
	return RET_OK;
}

static int _generateSizeTable(UINT8 *BITS, UINT8 *TABLE_SIZE)
{
	UINT32 i, count, index;

	MJPEG_INFO("Called.\n");

	for (i = 0, index = 0; i < 16; i++) {
		count = BITS[i];
		// MJPEG_INFO ( "count = %d\n", count );
		while (count > 0) {
			TABLE_SIZE[index] = i + 1;
			index++;
			count--;
		}
	}

	MJPEG_INFO("END");

	return RET_OK;
}

static void _Huff_SetMaxTables(UINT32 MAXCODE[16])
{
	UINT32 data;

	data = (((MAXCODE[0] << 24) & 0x1000000) | ((MAXCODE[1] << 16) & 0x30000) |
			((MAXCODE[2] << 8) & 0x700) | (MAXCODE[3] & 0xF));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((MAXCODE[4] << 24) & 0x1F000000) |
			((MAXCODE[5] << 16) & 0x3F0000) | ((MAXCODE[6] << 8) & 0x7F00) |
			(MAXCODE[7] & 0xFF));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((MAXCODE[8] << 16) & 0x1FF0000) | (MAXCODE[9] & 0x3FF));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((MAXCODE[10] << 16) & 0x7FF0000) | (MAXCODE[11] & 0xFFF));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((MAXCODE[12] << 16) & 0x1FFF0000) | (MAXCODE[13] & 0x3FFF));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((MAXCODE[14] << 16) & 0x7FFF0000) | (MAXCODE[15] & 0xFFFF));

	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);
}

static void _Huff_SetDCPtrTables(UINT32 VALPTR[16])
{
	UINT32 data;
	data = (((VALPTR[1] << 28) & 0x10000000) | ((VALPTR[2] << 24) & 0x3000000) |
			((VALPTR[3] << 20) & 0xF00000) | ((VALPTR[4] << 16) & 0xF0000) |
			((VALPTR[5] << 12) & 0xF000) | ((VALPTR[6] << 8) & 0xF00) |
			((VALPTR[7] << 4) & 0xF0) | (VALPTR[8] & 0xF));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((VALPTR[9] << 28) & 0xF0000000) |
			((VALPTR[10] << 24) & 0xF000000) | ((VALPTR[11] << 20) & 0xF00000) |
			((VALPTR[12] << 16) & 0xF0000) | ((VALPTR[13] << 12) & 0xF000) |
			((VALPTR[14] << 8) & 0xF00) | ((VALPTR[15] << 4) & 0xF0));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);
}

static void _Huff_SetACPtrTables(UINT32 VALPTR[16])
{
	UINT32 data;

	data = (((VALPTR[1] << 24) & 0x1000000) | ((VALPTR[2] << 16) & 0x30000) |
			((VALPTR[3] << 8) & 0xF00) | ((VALPTR[4]) & 0x1F));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((VALPTR[5] << 24) & 0x3f000000) | ((VALPTR[6] << 16) & 0x3f0000) |
			((VALPTR[7] << 8) & 0xFF00) | ((VALPTR[8]) & 0xFF));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((VALPTR[9] << 24) & 0xFF000000) | ((VALPTR[10] << 16) & 0xFF0000) |
			((VALPTR[11] << 8) & 0xFF00) | ((VALPTR[12]) & 0xFF));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	data = (((VALPTR[13] << 24) & 0xFF000000) |
			((VALPTR[14] << 16) & 0xFF0000) | ((VALPTR[15] << 8) & 0xFF00));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);
}

static void _Huff_SetDCValueTables(UINT8 Value[162])
{
	UINT32 data;
	int iCount = 0;

	for (iCount = 0; iCount <= 8; iCount = iCount + 4) {
		data = (((Value[iCount] << 24) & 0xFF000000) |
				((Value[iCount + 1] << 16) & 0x00FF0000) |
				((Value[iCount + 2] << 8) & 0x0000FF00) |
				((Value[iCount + 3]) & 0x000000FF));
		LGJPEG_Wr(htable_data, data);
		LGJPEG_WrFL(htable_data);
		// MJPEG_INFO("0x%08X\n", data);
	}
}

static void _Huff_SetACValueTables(UINT8 Value[162])
{
	UINT32 data;
	int iCount = 0;

	for (iCount = 0; iCount < 160; iCount = iCount + 4) {
		data = (((Value[iCount] << 24) & 0xFF000000) |
				((Value[iCount + 1] << 16) & 0x00FF0000) |
				((Value[iCount + 2] << 8) & 0x0000FF00) |
				((Value[iCount + 3]) & 0x000000FF));
		LGJPEG_Wr(htable_data, data);
		LGJPEG_WrFL(htable_data);
		// MJPEG_INFO("0x%08X\n", data);
	}

	data = (((Value[160] << 24) & 0xFF000000) |
			((Value[161] << 16) & 0x00FF0000));
	LGJPEG_Wr(htable_data, data);
	LGJPEG_WrFL(htable_data);
	// MJPEG_INFO("0x%08X\n", data);

	// MJPEG_INFO("0x%08X\n", data);
}

static int _REG_SetHuffmanTable(LX_MJPEG_HUFFMAN_TABLE_T *i_pstHuffman)
{
	UINT8 *Value, *Bits;
	SINT32 iTableNumber, iCount;

	UINT8 **TABLE_SIZE;
	UINT32 **CODE;
	UINT32 **MAXCODE;
	UINT32 **VALPTR;

	MJPEG_INFO("Called.\n");

	// allocate tables
	TABLE_SIZE = kzalloc(sizeof(UINT8 *) * 4, GFP_KERNEL);
	CODE = kzalloc(sizeof(UINT32 *) * 4, GFP_KERNEL);
	MAXCODE = kzalloc(sizeof(UINT32 *) * 4, GFP_KERNEL);
	VALPTR = kzalloc(sizeof(UINT32 *) * 4, GFP_KERNEL);

	if (!TABLE_SIZE || !CODE || !MAXCODE || !VALPTR) {
		MJPEG_ERROR("Failed to get allocation 1!!\n");
		if (TABLE_SIZE)
			kfree(TABLE_SIZE);
		if (CODE)
			kfree(CODE);
		if (MAXCODE)
			kfree(MAXCODE);
		if (VALPTR)
			kfree(VALPTR);
		return FALSE;
	}

	// Generate Huffman table
	for (iTableNumber = 0; iTableNumber < 4; ++iTableNumber) {
		// table size for DC is 16, AC is 512.
		UINT32 alloc_size = ((iTableNumber == HUFF_DC_INDEX0) ||
							 (iTableNumber == HUFF_DC_INDEX1)) ?
									16 :
									512;

		// allocate tables
		TABLE_SIZE[iTableNumber] =
				kzalloc(sizeof(UINT8) * alloc_size, GFP_KERNEL);
		CODE[iTableNumber] = kzalloc(sizeof(UINT32) * alloc_size, GFP_KERNEL);
		MAXCODE[iTableNumber] = kzalloc(sizeof(UINT32) * 16, GFP_KERNEL);
		VALPTR[iTableNumber] = kzalloc(sizeof(UINT32) * 16, GFP_KERNEL);

		if (!TABLE_SIZE[iTableNumber] || !CODE[iTableNumber] ||
			!MAXCODE[iTableNumber] || !VALPTR[iTableNumber]) {
			MJPEG_ERROR("Failed to get allocation[%d]!!\n", iTableNumber);
			for (iCount = iTableNumber; iCount >= 0; --iCount) {
				if (TABLE_SIZE[iCount])
					kfree(TABLE_SIZE[iCount]);
				if (CODE[iCount])
					kfree(CODE[iCount]);
				if (MAXCODE[iCount])
					kfree(MAXCODE[iCount]);
				if (VALPTR[iCount])
					kfree(VALPTR[iCount]);
			}
			kfree(TABLE_SIZE);
			kfree(CODE);
			kfree(MAXCODE);
			kfree(VALPTR);
			return FALSE;
		}

		_generateSizeTable(i_pstHuffman[iTableNumber].ui8CodeLengths,
						   TABLE_SIZE[iTableNumber]);
		_generateCodeTable(TABLE_SIZE[iTableNumber], CODE[iTableNumber]);
		_generateDecodeTables(i_pstHuffman[iTableNumber].ui8CodeLengths,
							  MAXCODE[iTableNumber], VALPTR[iTableNumber],
							  CODE[iTableNumber]);
	}

	// 0 : HUFF_DC_INDEX0
	// 1 : HUFF_AC_INDEX0
	// 2 : HUFF_DC_INDEX1
	// 3 : HUFF_AC_INDEX1
	for (iTableNumber = 0; iTableNumber < 4; iTableNumber++) {
		UINT8 ui8TableNum = (iTableNumber == 0) ? HUFF_DC_INDEX0 :
							(iTableNumber == 1) ? HUFF_DC_INDEX1 :
							(iTableNumber == 2) ? HUFF_AC_INDEX0 :
												  HUFF_AC_INDEX1;

		LGJPEG_RdFL(htable_idx);
		LGJPEG_Wr01(htable_idx, reg_htable_endian, 1);
		LGJPEG_Wr01(htable_idx, reg_htable_idx_auto, ENABLE);
		LGJPEG_Wr01(htable_idx, reg_htable_sel, iTableNumber);
		LGJPEG_Wr01(htable_idx, reg_htable_idx, 0);
		LGJPEG_WrFL(htable_idx);

		MJPEG_INFO("START [%d]\n", ui8TableNum);

		// 1. MAX Table
		_Huff_SetMaxTables(MAXCODE[ui8TableNum]);

		Value = i_pstHuffman[ui8TableNum].ui8CodeValues;
		Bits = i_pstHuffman[ui8TableNum].ui8CodeLengths;

		if ((ui8TableNum == HUFF_DC_INDEX0) ||
			(ui8TableNum == HUFF_DC_INDEX1)) {
			// DC 0,1
			// 2. VALPTR
			_Huff_SetDCPtrTables(VALPTR[ui8TableNum]);

			// 3. VAL Table
			_Huff_SetDCValueTables(Value);
		} else {
			// AC 0, 1
			// 2. VALPTR
			_Huff_SetACPtrTables(VALPTR[ui8TableNum]);

			// 3. VAL Table
			_Huff_SetACValueTables(Value);
		}
	}

	// free tables
	for (iTableNumber = 0; iTableNumber < 4; ++iTableNumber) {
		kfree(TABLE_SIZE[iTableNumber]);
		kfree(CODE[iTableNumber]);
		kfree(MAXCODE[iTableNumber]);
		kfree(VALPTR[iTableNumber]);
	}

	kfree(TABLE_SIZE);
	kfree(CODE);
	kfree(MAXCODE);
	kfree(VALPTR);

	return TRUE;
}

static void _REG_SetQTable(LX_MJPEG_FRAME_HEADER_T *i_pstFrameInfo,
						   LX_MJPEG_QUANTIZATION_TABLE_T *i_pstQTable)
{
	UINT32 data;
	SINT32 iCompID, iCount;

	MJPEG_INFO("Called.\n");

	for (iCompID = 0; iCompID < i_pstFrameInfo->ui8NumberOfComponents;
		 ++iCompID) {
		SINT32 QTableID = i_pstFrameInfo->stComponents[iCompID].ui8QTableID;

		LGJPEG_RdFL(qtable_idx);
		LGJPEG_Wr01(qtable_idx, reg_qtable_idx, 0);
		LGJPEG_Wr01(qtable_idx, reg_qtable_idx_auto, ENABLE);
		LGJPEG_Wr01(qtable_idx, reg_qtable_sel, iCompID);
		LGJPEG_WrFL(qtable_idx);

		for (iCount = 0; iCount < 64; iCount += 4) {
			data = ((i_pstQTable[QTableID].ui8Elements[iCount] << 24) |
					(i_pstQTable[QTableID].ui8Elements[iCount + 1] << 16) |
					(i_pstQTable[QTableID].ui8Elements[iCount + 2] << 8) |
					(i_pstQTable[QTableID].ui8Elements[iCount + 3] << 0));
			LGJPEG_Wr(qtable_data, data);
			LGJPEG_WrFL(qtable_data);
		}
	}
}

static void _REG_SetPostProcessing(LX_MJPEG_SCALING_T eScaleVertical,
								   LX_MJPEG_SCALING_T eScaleHorizontal,
								   LX_MJPEG_MIRRORING_T eMirroring,
								   LX_MJPEG_ROTATION_T eRotation)
{
	MJPEG_INFO("Called.\n");

	/*
   * reg_ppctrl.w = 0;
   * reg_ppctrl.f.reg_v_scale_f = inputSt->scalefactorVer;
   * reg_ppctrl.f.reg_h_scale_f = inputSt->scalefactorHor;
   * reg_ppctrl.f.reg_rot_angle = inputSt->rotationAngle;
   * reg_ppctrl.f.reg_flip_dir = inputSt->flipDirection;
   */
	LGJPEG_RdFL(pp_ctrl);
	LGJPEG_Wr01(pp_ctrl, reg_v_scale_f, eScaleVertical);
	LGJPEG_Wr01(pp_ctrl, reg_h_scale_f, eScaleHorizontal);
	LGJPEG_Wr01(pp_ctrl, reg_flip_dir, eMirroring);
	LGJPEG_Wr01(pp_ctrl, reg_rot_angle, eRotation);
	LGJPEG_WrFL(pp_ctrl);
}

#define PARTIAL_LINE 16
static void _REG_SetDecCtrl(LX_MJPEG_OPERATION_T eOperation,
							UINT8 scaleVertical)
{
	// 2015.05.15 gaius.lee - jpeg decoder에서 line 수를 scale factor 로 나누어서
	//                        세팅을 하므로, 원래대로 16라인을 쓰려면 shift 해서
	//                        세팅해주어야 한다.
	UINT8 line = PARTIAL_LINE << scaleVertical;
	// UINT32 line =  (( ( 512 * 1024 ) / g_pstImageBuffer->ui32StrideY) / 8 ) *
	// 8; UINT32 line =  (( g_pstImageBuffer->ui32SizeY /
	// g_pstImageBuffer->ui32StrideY) / 8 ) * 8; line <<= scaleVertical;

	MJPEG_INFO("Called.\n");
	MJPEG_PRINT(
			" g_pstImageBuffer->ui32SizeY = %d _g_pstImageInfo->ui16Width = "
			"%d line = %d\n",
			g_pstImageBuffer->ui32SizeY, g_pstImageBuffer->ui32StrideY, line);

	/*
   * reg_decctrl.w = 0;
   * reg_decctrl.f.reg_dec_start = 1;
   * reg_decctrl.f.reg_dec_mode = 0;
   * reg_decctrl.f.reg_recon_ptr_ctrl_mode = RECON_PTR_CTRL_MODE;
   * reg_decctrl.f.reg_iqit_lcl_recon_ptr = 2;
   * reg_decctrl.f.reg_dpb_num_m1 = ( inputSt->dpb_num - 1 );
   * //reg_decctrl.f.reg_dec_line_num_div8 =
   * ((inputSt->decSamplesInPicHeight)/(inputSt->dpb_num))/8;
   * reg_decctrl.f.reg_dec_line_num_div8 = 0;
   * reg_decctrl.f.reg_swreset = 0;
   */

	LGJPEG_RdFL(dec_ctrl);

	if (eOperation == LX_MJPEG_OPERATION_PARTIAL) {
		LGJPEG_Wr01(dec_ctrl, reg_dec_mode, 1);
		LGJPEG_Wr01(dec_ctrl, reg_dpb_num_m1, 1 - 1); // number of DPB - 1
		LGJPEG_Wr01(dec_ctrl, reg_dec_line_num_div8, line / 8); // line / 8
	} else {
		LGJPEG_Wr01(dec_ctrl, reg_dec_mode, 0);
		LGJPEG_Wr01(dec_ctrl, reg_dpb_num_m1, 0);
		LGJPEG_Wr01(dec_ctrl, reg_dec_line_num_div8, 0);
	}

	LGJPEG_Wr01(dec_ctrl, reg_dec_start, 1);
	LGJPEG_Wr01(dec_ctrl, reg_recon_ptr_ctrl_mode, 1);
	LGJPEG_Wr01(dec_ctrl, reg_recon_ptr_interval, 2);
	LGJPEG_Wr01(dec_ctrl, reg_swreset, 0);
	LGJPEG_WrFL(dec_ctrl);
}

static SAMPLE_FACTOR_T
_CalulateSampleFactor(LX_MJPEG_FRAME_HEADER_T *pstFrameHeader)
{
	SAMPLE_FACTOR_T eSampleFactor = MJPEG_SAMPLE_400;
	int iCount = 0;

	// Calculate format
	if (pstFrameHeader->ui8NumberOfComponents == 3) {
		UINT8 min_comp_id = 255;

		for (iCount = 0; iCount < pstFrameHeader->ui8NumberOfComponents;
			 ++iCount) {
			min_comp_id =
					MIN(min_comp_id,
						pstFrameHeader->stComponents[iCount].ui8ComponentID);
		}

		for (iCount = 0; iCount < pstFrameHeader->ui8NumberOfComponents;
			 ++iCount) {
			if (pstFrameHeader->stComponents[iCount].ui8ComponentID ==
				min_comp_id) {
				eSampleFactor =
						((pstFrameHeader->stComponents[iCount].ui8HSampleFreq &
						  3)
						 << 2) |
						(pstFrameHeader->stComponents[iCount].ui8VSampleFreq &
						 3);
			} else if (pstFrameHeader->stComponents[iCount].ui8HSampleFreq !=
							   1 ||
					   pstFrameHeader->stComponents[iCount].ui8VSampleFreq !=
							   1) {
				MJPEG_DEBUG(("[DEC] Not Supported Sampling Factor\n"));
				eSampleFactor = MJPEG_SAMPLE_NONE;
			}
		}
	} else if (pstFrameHeader->ui8NumberOfComponents == 1) {
		eSampleFactor = MJPEG_SAMPLE_400;
	} else {
		eSampleFactor = MJPEG_SAMPLE_NONE;
	}

	switch (eSampleFactor) {
	case MJPEG_SAMPLE_420: {
		_g_pstImageInfo->eFormat = LX_MJPEG_FORMAT_420;
		break;
	}
	case MJPEG_SAMPLE_H422: {
		_g_pstImageInfo->eFormat = LX_MJPEG_FORMAT_422;
		break;
	}
	case MJPEG_SAMPLE_V422: {
		_g_pstImageInfo->eFormat = LX_MJPEG_FORMAT_224;
		break;
	}
	case MJPEG_SAMPLE_444: {
		_g_pstImageInfo->eFormat = LX_MJPEG_FORMAT_444;
		break;
	}
	default: /* 4:0:0 */
	{
		_g_pstImageInfo->eFormat = LX_MJPEG_FORMAT_400;
	}
	}

	return eSampleFactor;
}

// return 0 : OK
// return 1 : Error
static int _CheckSanity(LX_MJPEG_HEADER_T *_pstHeader,
						LX_MJPEG_OPTION_T *_pstOption)
{
	int checked = 0;

	// Check satisfies
	if ((_pstHeader->stFrameHeader.ui8SamplingPrecision != 8) ||
		(_pstHeader->stFrameHeader.ui16Height < MIN_VSIZE) ||
		(_pstHeader->stFrameHeader.ui16Height > MAX_VSIZE) ||
		(_pstHeader->stFrameHeader.ui16Width < MIN_HSIZE) ||
		(_pstHeader->stFrameHeader.ui16Width > MAX_HSIZE) ||
		((_pstHeader->stFrameHeader.ui8NumberOfComponents != 1) &&
		 (_pstHeader->stFrameHeader.ui8NumberOfComponents != 3)) ||
		(_pstHeader->stScanHeader.ui8Ss != 0) ||
		(_pstHeader->stScanHeader.ui8Se != 0x3F) ||
		(_pstHeader->stScanHeader.ui8Ah != 0) ||
		(_pstHeader->stScanHeader.ui8Al != 0)) {
		checked = 1;
	}

	// Check invalide option
	if (((_pstOption->eMirroring != LX_MJPEG_MIRROR_NONE) ||
		 (_pstOption->eRotation != LX_MJPEG_ROTATE_0)) &&
		((_pstOption->eScaleHorizontal != LX_MJPEG_SCALE_NONE) ||
		 (_pstOption->eScaleVertical != LX_MJPEG_SCALE_NONE))) {
		checked = 1;
	}

	return checked;
}

/**
 * interrupt handler for MJPEG device.
 *
 */
static irqreturn_t _ISR(int i_iIrq, void *pDevId)
{
	BOOLEAN eStatus;

	UINT32 intr_check = 0;
	UINT32 stEvent = 0;

	LGJPEG_RdFL(intr_st);
	LGJPEG_RdFL(intr_cl);

	intr_check = LGJPEG_Rd(intr_st);

	MJPEG_DEBUG("intr status check = 0x%x\n", intr_check);

	LGJPEG_Rd01(intr_st, intr_pic_done, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_DONE;

		LGJPEG_Wr01(intr_cl, intr_pic_done, 1);
		MJPEG_DEBUG("Interrupt : [Done]\n");
		if (enable_icod_dec_time) {
			LGJPEG_RdFL(dec_time);
			MJPEG_NOTI("dec time %x\n", gpRegLGJPEG->dec_time);
		}
	}

	LGJPEG_Rd01(intr_st, intr_pic_done_err, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_ERROR;

		LGJPEG_Wr01(intr_cl, intr_pic_done_err, 1);
		MJPEG_DEBUG("Interrupt : [PIC_DON_ERROR]\n");
	}

	LGJPEG_Rd01(intr_st, intr_stream_err, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_STREAM_ERROR;

		LGJPEG_Wr01(intr_cl, intr_stream_err, 1);
		MJPEG_DEBUG("Interrupt : [STREAM_ERROR]\n");

		// sw reset when got stream error
		LGJPEG_RdFL(dec_ctrl);
		LGJPEG_Wr01(dec_ctrl, reg_swreset, TRUE);
		LGJPEG_WrFL(dec_ctrl);
	}

	LGJPEG_Rd01(intr_st, intr_start_err, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_OVER;

		LGJPEG_Wr01(intr_cl, intr_start_err, 1);
		MJPEG_DEBUG("Interrupt : [START_ERROR]\n");
	}

	LGJPEG_Rd01(intr_st, intr_buffer_empty, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_BBC;

		LGJPEG_Wr01(intr_cl, intr_buffer_empty, 1);
		MJPEG_DEBUG("Interrupt : [BUF EMPTY]\n");
	}

	LGJPEG_Rd01(intr_st, intr_dec_done0, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_BUFFER0;
		LGJPEG_Wr01(intr_cl, intr_dec_done0, 1);
		MJPEG_DEBUG("Interrupt : [BUFFER0]\n");
	}

	LGJPEG_Rd01(intr_st, intr_dec_done1, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_BUFFER1;

		LGJPEG_Wr01(intr_cl, intr_dec_done1, 1);
		MJPEG_DEBUG("Interrupt : [BUFFER1]\n");
	}

	LGJPEG_Rd01(intr_st, intr_dec_done2, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_BUFFER2;
		LGJPEG_Wr01(intr_cl, intr_dec_done2, 1);
		MJPEG_DEBUG("Interrupt : [BUFFER2]\n");
	}

	LGJPEG_Rd01(intr_st, intr_dec_done3, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_BUFFER3;

		LGJPEG_Wr01(intr_cl, intr_dec_done3, 1);
		MJPEG_DEBUG("Interrupt : [BUFFER3]\n");
	}

	LGJPEG_Rd01(intr_st, intr_time_out, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_TIMEOUT;

		LGJPEG_Wr01(intr_cl, intr_time_out, 1);
		MJPEG_DEBUG("Interrupt : [TIMEOUT]\n");
	}

	LGJPEG_Rd01(intr_st, intr_dc_error, eStatus);
	if (eStatus) {
		stEvent |= MJPEG_EVENT_DC_ERROR;

		LGJPEG_Wr01(intr_cl, intr_dc_error, 1);
		MJPEG_DEBUG("Interrupt : [DC ERROR]\n");
	}

	// clear interrupt
	LGJPEG_WrFL(intr_cl);

	if (stEvent == 0) {
		stEvent = intr_check;
		MJPEG_ERROR("Unknown HW Interrupt = 0x%x\n", stEvent);
	}
	MJPEG_QueuePush(&_gMsgQueue, stEvent);
	OS_SendEvent(&gstEvent, stEvent);
	// use only use queue mode..
	if (_gbUseQueue)
		_MJPEG_AddList(stEvent);

	return IRQ_HANDLED;
}

static void _MJPEG_AddList(UINT32 val)
{
	MJPEG_LIST_T *list;

	// check if work queue is initialized.
	if (_gJPEGWorkQueue.WorkQueue == NULL)
		return;

	list = kmalloc(sizeof(MJPEG_LIST_T), GFP_ATOMIC);
	if (!list) {
		MJPEG_WARN("not enough memory\n");
		return;
	}

	list->val = val;

	spin_lock(&_gJPEGWorkQueue.work_lock);
	list_add_tail(&list->list, &_gJPEGWorkQueue.list_head);
	spin_unlock(&_gJPEGWorkQueue.work_lock);
	queue_work(_gJPEGWorkQueue.WorkQueue, &_gJPEGWorkQueue.work);
}

static void _MJPEG_Worker(struct work_struct *_work)
{
	MJPEG_WORK_QUEUE_T *workqueue = NULL;
	MJPEG_LIST_T *list;
	int ret = RET_ERROR;

	MJPEG_PRINT("Called!!\n");

	workqueue = container_of(_work, MJPEG_WORK_QUEUE_T, work);

	while (1) {
		list = list_first_entry_or_null(&_gJPEGWorkQueue.list_head,
										MJPEG_LIST_T, list);
		if (list)
			list_del(&list->list); /* remove from the head */
		if (!list)
			break;

		MJPEG_PRINT("Get val.. [%d]\n", list->val);
		ret = MJPEG_AddNotify(list->val);
		if (ret == RET_OK)
			MJPEG_WakeupNotify();

		kfree(list);
	}
}

int _MJPEG_Init_Workqueue(void)
{
	MJPEG_PRINT("Initialize Workqueue.. \n");

	//_gJPEGWorkQueue = (MJPEG_WORK_QUEUE_T *)kzalloc(sizeof(MJPEG_WORK_QUEUE_T),
	//GFP_KERNEL);
	memset(&_gJPEGWorkQueue, 0, sizeof(_gJPEGWorkQueue));

	_gJPEGWorkQueue.WorkQueue = create_workqueue("MJPEG_WORKQ");

	if (_gJPEGWorkQueue.WorkQueue == NULL) {
		MJPEG_ERROR("MJPEG workwqueue allocation failed\n");
		return -1;
	}

	/* filter callback */
	INIT_LIST_HEAD(&_gJPEGWorkQueue.list_head);
	spin_lock_init(&_gJPEGWorkQueue.work_lock);
	INIT_WORK(&_gJPEGWorkQueue.work, (void *)&_MJPEG_Worker);

	return 0;
}

int _MJPEG_Destory_Workqueue(void)
{
	MJPEG_PRINT("Destory Workqueue.. \n");

	destroy_workqueue(_gJPEGWorkQueue.WorkQueue);

	memset(&_gJPEGWorkQueue, 0, sizeof(_gJPEGWorkQueue));
	MJPEG_PRINT("Destory sucess.. \n");

	return 0;
}

/**
 * Initialize decoder
 *
 */
UINT32 MJPEG_DEC_Init(LX_MJPEG_HEADER_T *i_pstHeader,
					  LX_MJPEG_IMAGE_BUF_T *i_pstImageBuf,
					  LX_MJPEG_OPTION_T *i_pstOption,
					  LX_MJPEG_IMAGE_INFO_T *o_pstImageInfo)
{
	UINT32 ui32OutputSize;
	LX_MJPEG_FRAME_HEADER_T *pstFrameHeader;

	MJPEG_INFO("Called.\n");

	_g_pstHeader = i_pstHeader;
	_g_pstImageInfo = o_pstImageInfo;
	g_pstImageBuffer = i_pstImageBuf;
	_g_pstOption = i_pstOption;

	if (_g_pstOption->eOperation == LX_MJPEG_OPERATION_PARTIAL) {
		_g_pstOption->eRotation = LX_MJPEG_ROTATE_0;
		_g_pstOption->eMirroring = LX_MJPEG_MIRROR_NONE;
		//_g_pstOption->eScaleHorizontal = LX_MJPEG_SCALE_NONE;
		//_g_pstOption->eScaleVertical = LX_MJPEG_SCALE_NONE;
	}

	pstFrameHeader = &_g_pstHeader->stFrameHeader;

	// Check satisfies & invalide option
	if (_CheckSanity(_g_pstHeader, _g_pstOption)) {
		MJPEG_ERROR("Check Error!!!\n");
		return 0;
	}

	// Calculate format
	if (_CalulateSampleFactor(pstFrameHeader) == MJPEG_SAMPLE_NONE) {
		MJPEG_ERROR("Can't calculate sample factor!\n");
		return 0;
	}

	// Picture size alignment
	if (_g_pstImageInfo->eFormat == LX_MJPEG_FORMAT_420 ||
		_g_pstImageInfo->eFormat == LX_MJPEG_FORMAT_422)
		_g_pstImageInfo->ui16Width =
				((pstFrameHeader->ui16Width + 15) / 16) * 16;
	else
		_g_pstImageInfo->ui16Width = ((pstFrameHeader->ui16Width + 7) / 8) * 8;

	if (_g_pstImageInfo->eFormat == LX_MJPEG_FORMAT_420 ||
		_g_pstImageInfo->eFormat == LX_MJPEG_FORMAT_224)
		_g_pstImageInfo->ui16Height =
				((pstFrameHeader->ui16Height + 15) / 16) * 16;
	else
		_g_pstImageInfo->ui16Height =
				((pstFrameHeader->ui16Height + 7) / 8) * 8;

	// Calculate output image size
	switch (_g_pstImageInfo->eFormat) {
	case LX_MJPEG_FORMAT_420: {
		ui32OutputSize = _g_pstImageInfo->ui16Width *
						 _g_pstImageInfo->ui16Height * 3 / 2;
		break;
	}
	case LX_MJPEG_FORMAT_422: {
		ui32OutputSize =
				_g_pstImageInfo->ui16Width * _g_pstImageInfo->ui16Height * 2;
		break;
	}
	case LX_MJPEG_FORMAT_224: {
		ui32OutputSize =
				_g_pstImageInfo->ui16Width * _g_pstImageInfo->ui16Height * 2;
		break;
	}
	case LX_MJPEG_FORMAT_444: {
		ui32OutputSize =
				_g_pstImageInfo->ui16Width * _g_pstImageInfo->ui16Height * 3;
		break;
	}
	default: /* 4:0:0 */
	{
		ui32OutputSize =
				_g_pstImageInfo->ui16Width * _g_pstImageInfo->ui16Height * 1;
	}
	}

	ui32OutputSize = (ui32OutputSize >> _g_pstOption->eScaleHorizontal) >>
					 _g_pstOption->eScaleVertical;

	MJPEG_INFO("Initialized decoder.\n");

	return ui32OutputSize;
}

/**
 * Start decoding
 *
 */
int MJPEG_DEC_Start(LX_MJPEG_MEM_BUF_T *i_pstDataBuf, UINT32 i_ui32DataLength,
					BOOLEAN bEndOfStream)
{
	LX_MJPEG_MEM_STREAM_T stInputStream;
	UINT32 ui32PagePointer, ui32WordPointer, ui32ReadPointer;
	UINT16 ui16Temp;
	BOOLEAN bSwap;
	UINT32 ui32ReceivedEvent;
	int ret = LX_MJPEG_RESULT_ERROR;

	_LOCK();

	OS_ClearEvent(&gstEvent);
	QueueInit(&_gMsgQueue);

	MJPEG_INFO("Called.\n");
	stInputStream.mem_buf.addr =
			LX_CALC_ALIGNED_VALUE(i_pstDataBuf->addr - 3, 2);
	stInputStream.mem_buf.length = i_pstDataBuf->length;
	stInputStream.curr_offset = i_pstDataBuf->addr - stInputStream.mem_buf.addr;

	ui32PagePointer = stInputStream.curr_offset / 256;
	ui32WordPointer = (stInputStream.curr_offset % 256) / 4 +
					  ((ui32PagePointer & 1) ? 64 : 0);
	ui32WordPointer -= ((ui32WordPointer & 1) ? 1 : 0);
	ui32ReadPointer = (stInputStream.curr_offset % 4) * 8 +
					  ((((stInputStream.curr_offset % 256) / 4) & 1) ? 32 : 0);

	MJPEG_INFO("Buffer = 0x%d, Length = %d\n", stInputStream.mem_buf.addr,
			   stInputStream.mem_buf.length);
	MJPEG_INFO("Picture [%d x %d]\n", _g_pstImageInfo->ui16Width,
			   _g_pstImageInfo->ui16Height);

	_REG_SetInit(g_pstImageBuffer->bUVInterleaved);
	_REG_SetCPB(stInputStream.mem_buf.addr, stInputStream.mem_buf.length);
	ret = _REG_SetHuffmanTable(_g_pstHeader->stHuffmanTables);
	if (ret == FALSE) {
		MJPEG_ERROR("error in SetHuffmanTable\n");
		_UNLOCK();
		goto exit;
	}
	_REG_SetQTable(&_g_pstHeader->stFrameHeader,
				   _g_pstHeader->stQuantiztionTables);
	_REG_SetPicInfo(_g_pstImageInfo->ui16Width, _g_pstImageInfo->ui16Height);
	_REG_SetPostProcessing(_g_pstOption->eScaleVertical,
						   _g_pstOption->eScaleHorizontal,
						   _g_pstOption->eMirroring, _g_pstOption->eRotation);
	_REG_SetDPB(g_pstImageBuffer, _g_pstOption->eOperation,
				g_pstImageBuffer->bUVInterleaved);
	_REG_SetDecCtrl(_g_pstOption->eOperation,
					(UINT8)_g_pstOption->eScaleVertical);

	// Recalculate output image
	bSwap = ((_g_pstOption->eRotation == LX_MJPEG_ROTATE_90) ||
			 (_g_pstOption->eRotation == LX_MJPEG_ROTATE_270)) ?
					TRUE :
					FALSE;
	ui16Temp = _g_pstImageInfo->ui16Width >> _g_pstOption->eScaleHorizontal;
	_g_pstImageInfo->ui16Width = (bSwap) ?
										 _g_pstImageInfo->ui16Height >>
												 _g_pstOption->eScaleVertical :
										 ui16Temp;
	_g_pstImageInfo->ui16Height =
			(bSwap) ?
					ui16Temp :
					_g_pstImageInfo->ui16Height >> _g_pstOption->eScaleVertical;

	if (bSwap == TRUE) {
		_g_pstImageInfo->eFormat =
				(_g_pstImageInfo->eFormat == LX_MJPEG_FORMAT_422) ?
						LX_MJPEG_FORMAT_224 :
				(_g_pstImageInfo->eFormat == LX_MJPEG_FORMAT_224) ?
						LX_MJPEG_FORMAT_422 :
						_g_pstImageInfo->eFormat;
	}

	MJPEG_INFO("Start decoding.\n");

	_UNLOCK();

	if (!_gbUseQueue) {
		ret = OS_RecvEvent(
				&gstEvent,
				MJPEG_EVENT_BBC | MJPEG_EVENT_DONE | MJPEG_EVENT_BUFFER,
				&ui32ReceivedEvent, OS_EVENT_RECEIVE_ANY, MJPEG_TIMEOUT);
		MJPEG_INFO("ret = %d ui32ReceivedEvent = 0x%x\n", ret,
				   ui32ReceivedEvent);

		ui32ReceivedEvent = MJPEG_QueuePopLoop(&_gMsgQueue);

		if (ret == RET_OK)
			ret = ui32ReceivedEvent;
		else
			MJPEG_ERROR("timeout occured, ui32ReceivedEvent = 0x%x\n",
						ui32ReceivedEvent);
	} else
		ret = RET_OK;

exit:
	return ret;
}

/**
 * Continue partial decoding
 *
 */
int MJPEG_DEC_PartialContinue(UINT32 u32PartialBuffer)
{
	// ULONG flags;
	// BOOLEAN eStatus;
	UINT32 ui32ReceivedEvent = 0;
	int ret = LX_MJPEG_RESULT_ERROR;

	MJPEG_INFO("Called.\n");

	_LOCK();

	// OS_ClearEvent (&gstEvent); //Modified to handle consecutive ISR events
	// QueueInit (&_gMsgQueue);   //SICDTV-12467

	_REG_ClearDPB(REG_DPB0);

	_UNLOCK();

	if (!_gbUseQueue) {
		ret = OS_RecvEvent(&gstEvent,
						   MJPEG_EVENT_BBC | MJPEG_EVENT_DONE |
								   MJPEG_EVENT_BUFFER | MJPEG_EVENT_ERROR,
						   &ui32ReceivedEvent, OS_EVENT_RECEIVE_ANY,
						   MJPEG_TIMEOUT);

		MJPEG_INFO("recvEvent ret = %d Event = 0x%x\n", ret, ui32ReceivedEvent);
		ui32ReceivedEvent = MJPEG_QueuePopLoop(&_gMsgQueue);

		if (ret == RET_OK) {
			if ((ui32ReceivedEvent & MJPEG_EVENT_BBC) &&
				(ui32ReceivedEvent & MJPEG_EVENT_BUFFER)) {
				MJPEG_INFO("Double ISR Event = 0x%x \n", ui32ReceivedEvent);
				OS_SendEvent(&gstEvent, ui32ReceivedEvent);
			}
			ret = ui32ReceivedEvent;
			MJPEG_INFO("return Event = 0x%x\n", ui32ReceivedEvent);
		} else {
			if (ui32ReceivedEvent)
				ret = ui32ReceivedEvent;
			MJPEG_WARN("timeout ret = %d Event = 0x%x\n", ret,
					   ui32ReceivedEvent);
		}
	} else
		ret = RET_OK;

	return ret;
}

/**
 * Continue decoding
 *
 */

int MJPEG_DEC_Continue(LX_MJPEG_MEM_BUF_T *i_pstDataBuf,
					   UINT32 i_ui32DataLength, BOOLEAN bEndOfStream,
					   BOOLEAN bSkipCheck)
{
	LX_MJPEG_MEM_STREAM_T stInputStream;
	int ret = LX_MJPEG_RESULT_ERROR;
	UINT32 ui32ReceivedEvent = 0;
	//  BOOLEAN bEndOfStream;

	_LOCK();

	MJPEG_INFO("Called.\n");

	// OS_ClearEvent (&gstEvent); //Modified to handle consecutive ISR events
	// QueueInit (&_gMsgQueue);   //SICDTV-12467

	stInputStream.mem_buf.addr =
			LX_CALC_ALIGNED_VALUE(i_pstDataBuf->addr - 3, 2);
	stInputStream.mem_buf.length = i_pstDataBuf->length;
	stInputStream.curr_offset = i_pstDataBuf->addr - stInputStream.mem_buf.addr;

	_REG_SetCPB(stInputStream.mem_buf.addr, stInputStream.mem_buf.length);
	_REG_SetDecCtrl(_g_pstOption->eOperation,
					(UINT8)_g_pstOption->eScaleVertical);

	// gaius.lee 2015.07.21 - BUFFER0 이랑 BUFFER_EMPTY 가 동시에 떴을 땐 이것도
	// 해주어야한다.
	if (bSkipCheck) {
		MJPEG_INFO("bSkipCheck\n");
		_REG_ClearDPB(REG_DPB0);
	}

	_UNLOCK();

	if (!_gbUseQueue) {
		ret = OS_RecvEvent(
				&gstEvent,
				MJPEG_EVENT_BBC | MJPEG_EVENT_DONE | MJPEG_EVENT_BUFFER,
				&ui32ReceivedEvent, OS_EVENT_RECEIVE_ANY, MJPEG_TIMEOUT);
		MJPEG_INFO("recvEvent ret = %d Event = 0x%x\n", ret, ui32ReceivedEvent);
		ui32ReceivedEvent = MJPEG_QueuePopLoop(&_gMsgQueue);

		if (ret == RET_OK) {
			if ((ui32ReceivedEvent & MJPEG_EVENT_BBC) &&
				(ui32ReceivedEvent & MJPEG_EVENT_BUFFER)) {
				MJPEG_INFO("Double ISR Event = 0x%x \n", ui32ReceivedEvent);
				OS_SendEvent(&gstEvent, ui32ReceivedEvent);
			}
			ret = ui32ReceivedEvent;
			MJPEG_INFO("return Event = 0x%x\n", ui32ReceivedEvent);
		} else {
			if (ui32ReceivedEvent)
				ret = ui32ReceivedEvent;
			MJPEG_WARN("timeout ret = %d Event = 0x%x\n", ret,
					   ui32ReceivedEvent);
		}

	} else
		ret = RET_OK;

	return ret;
}

int MJPEG_DEC_GetCurrentCoordinate(UINT16 *x, UINT16 *y)
{
	*x = _REG_GetCurrent_XY(TRUE);
	*y = _REG_GetCurrent_XY(FALSE);

	return RET_OK;
}

/**
 * Software reset for MJPEG device.
 *
 */
int MJPEG_HwReset(void)
{
	BOOLEAN bResetAckRmif, bResetAckWmif;
	UINT32 count = 0;

	//  memset((void *)&g_MJPEG_device->stImageInfo, 0,
	//  sizeof(LX_MJPEG_MEM_STREAM_T));

	// SW Reset must be done after clear DPBs.
	_REG_ClearDPB(REG_DPB_ALL);

#define RESET_TIMEOUT 100
	LGJPEG_RdFL(dec_ctrl);
	LGJPEG_Wr01(dec_ctrl, reg_swreset, TRUE);
	LGJPEG_WrFL(dec_ctrl);

	while (count++ < RESET_TIMEOUT) {
		LGJPEG_RdFL(dec_ctrl);
		LGJPEG_Rd02(dec_ctrl, reg_swreset_ack_rmif, bResetAckRmif,
					reg_swreset_ack_wmif, bResetAckWmif);
		if (bResetAckRmif && bResetAckWmif)
			break;
		msleep(1);
	}
	LGJPEG_Wr01(dec_ctrl, reg_swreset, FALSE);
	LGJPEG_WrFL(dec_ctrl);

	if (count >= RESET_TIMEOUT) {
		MJPEG_ERROR("Reset Timeout. [count %d]\n", count);

		return RET_ERROR;
	}
	MJPEG_INFO("Software Reset. [count %d]\n", count);

	return RET_OK;
}

int MJPEG_HwInit(void)
{
	int err;
	void *pRegVirt = NULL;
	LX_MJPEG_DEF_T *pMJPEGDef = NULL;

	MJPEG_INFO("Called.\n");

	/* TODO : initialize your module not specific minor device */
	pMJPEGDef = MJPEG_GetDef();
	if (pMJPEGDef == NULL) {
		MJPEG_WARN("can't init MJPEG device\n");
		return -EIO;
	}

	pRegVirt = ioremap(pMJPEGDef->jpeg_reg_base, 0x120);

	MJPEG_INFO("ICOD_REG_BASE = 0x%08X\n", pMJPEGDef->jpeg_reg_base);

	gpRealRegLGJPEG = (volatile JDEC_REG *)(pRegVirt + 0x0);
	gpRegLGJPEG = (JDEC_REG *)OS_KMalloc(sizeof(JDEC_REG));

	if (gpRegLGJPEG == NULL) {
		MJPEG_ERROR("Shadow register memory allocation error\n");
		return RET_ERROR;
	}

	err = request_irq(pMJPEGDef->irq_num, (irq_handler_t)_ISR, 0, "JpgDec",
					  NULL);

	if (err) {
		MJPEG_WARN("request_irq JpgDec in %s is failed %d\n", __FUNCTION__,
				   err);
		return -EIO;
	}

	MJPEG_PRINT("JpgDec registered :%d:\n", pMJPEGDef->irq_num);

	OS_InitEvent(&gstEvent);
	// gpstEvent = pstEvent;
	// MJPEG_INFO("mjpeg register initialized");

	_MJPEG_Init_Workqueue();

	return RET_OK;
}

int MJPEG_HwEnd(void)
{
	LX_MJPEG_DEF_T *pMJPEGDef = NULL;

	MJPEG_INFO("Called.\n");

	/* TODO : cleanup your module not specific minor device */
	pMJPEGDef = MJPEG_GetDef();
	if (pMJPEGDef != NULL) {
		free_irq(pMJPEGDef->irq_num, NULL);
	}

	if (gpRealRegLGJPEG != NULL) {
		iounmap(gpRealRegLGJPEG);
	}

	if (gpRegLGJPEG != NULL) {
		OS_KFree(gpRegLGJPEG);
		gpRegLGJPEG = NULL;
		gpRealRegLGJPEG = NULL;
	}

	_MJPEG_Destory_Workqueue();

	// MJPEG_INFO("register cleanup");

	if (gpRealRegLGJPEG != NULL || gpRegLGJPEG != NULL) {
		return RET_ERROR;
	} else {
		return RET_OK;
	}
}

int MJPEG_SetIsUseQueue(BOOLEAN bUseQueue)
{
	_gbUseQueue = bUseQueue;
	return 0;
}

UINT32 MJPEG_ENC_Init(LX_MJPEG_IMAGE_INFO_T *i_pstImageInfo,
					  LX_MJPEG_IMAGE_BUF_T *i_pstImageBuf,
					  LX_MJPEG_OPTION_T *i_pstOption,
					  LX_MJPEG_HEADER_T *o_pstHeader)
{
	return RET_OK;
}

int MJPEG_ENC_Start(LX_MJPEG_MEM_BUF_T *i_pstDataBuf,
					UINT32 *pui32ReceivedEvent)
{
	return RET_OK;
}

int MJPEG_ENC_Continue(UINT32 *pui32ReceivedEvent, UINT32 *pui32Size)
{
	return RET_OK;
}

UINT32 MJPEG_ENC_End(void)
{
	return RET_OK;
}
