/****************** COPYRIGHT AND CONFIDENTIALITY INFORMATION ******************
  Copyright (C) 2014-2018  Technicolor Technology Licensing LLC and/or
                           its Group Company
  All rights reserved.

  This program contains proprietary information which is a trade secret of
  Technicolor and also is protected by intellectual property as an unpublished
  work under applicable Copyright laws/right of authorship.
  This program is also subject to some patent and pending patent applications.
  Technicolor (R) is registered trademark and trade name of Technicolor group
  company, and shall not be used in any manner without express written from
  Technicolor.
  The use of the program and documentation is strictly limited to your own
  internal evaluation of such program and its functionalities, unless expressly
  agreed otherwise by Technicolor under a specific agreement.
  Recipient is to retain this program in confidence and is not permitted to use
  or make copies thereof other than as permitted in a written agreement with
  Technicolor, unless otherwise expressly allowed by applicable laws.
  Recipient is not allowed to make any copy, decompile, reverse engineer,
  disassemble, and attempt to derive the source code of, modify, or create
  derivative works of the program, any update, or any part thereof.
  Any violation or attempt to do so is a violation of the rights of Technicolor.
  If you or any person under your control or authority breach this restriction,
  you may be subject to prosecution and damages.
*******************************************************************************/

/** @mainpage HDR Hardware Decoder C model
 *
 * @brief Reconstructs HDR YUV-422 10b format video, based on YUV-420 10b frame and ETSI SL-HDR1 metadata
 *
 * @param parameters_file : video characteristics = height, width, bit per pixels, yuv range
 * @param display_OETF : 0 = BT1886, 1 = PQ, 2 = BT709, 3 = ARIB
 * @param metadata_file : ETSI SL-HDR1 metadata
 * @param yuv_in : binary video file, 420 format
 * @param yuv_upsampled : binary video file, 444 format
 * @param yuv_out : binary video file, 422 format
 * @param rgb_out : binary video file, RGB format
 * @param nb_frames : nb of frames to process
 * @param display_Brightness : cd/m2
*/

#include "SL_common.h"

#ifdef PE_PRIME_V142
#include "SL_static_LUT_fill.h"
#include "SL_compute.h"
//#include "osa_kadp.h"
//#include "debug_kadp.h"
//#include "pe_kadp.h"
//#include "pe_kadp_def.h"
//#include "pe_kadp_dbg.h"
//#include "pe_kadp_hdr.h"

#include "pe_def.h"
#include "pe_hdr.h"
//#include "pe_kwrap.h"
//#include "pe_kwrap_hdr.h"
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SL_filesIO.h"
#include "SL_filters.h"
#include "SL_HWModel.h"
#include "SL_static_LUT_fill.h"
#include "SL_compute.h"
#endif

#ifdef PE_PRIME_V142
#ifndef MAP_FAILED
#define MAP_FAILED					(void *)-1
#endif
#define KADP_PE_SL_DBG_PRINT(_x)	PE_PRINT_NOTI("%s : %d\n", #_x, (_x))

/* pe_def.h */
/*****************************************************************/
#define PE_LOGM_LEVEL_PRIME0	22
#define PE_LOGM_LEVEL_PRIME1	23
#define PE_LOGM_LEVEL_PRIME2	24
#define PE_LOGM_LEVEL_PRIME3	25
#define PE_LOGM_LEVEL_PRIME4	26
#define PE_LOGM_LEVEL_PRIME5	27
#define PE_LOGM_LEVEL_PRIME6	28
#define PE_LOGM_LEVEL_PRIME7	29
#define PE_LOGM_LEVEL_PRIME8	30
#define PE_LOGM_LEVEL_PRIME9	31
/* debug message(prime) */
#define PE_PRINT_PRIME0(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME0, format, ##args)
#define PE_PRINT_PRIME1(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME1, format, ##args)
#define PE_PRINT_PRIME2(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME2, format, ##args)
#define PE_PRINT_PRIME3(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME3, format, ##args)
#define PE_PRINT_PRIME4(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME4, format, ##args)
#define PE_PRINT_PRIME5(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME5, format, ##args)
#define PE_PRINT_PRIME6(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME6, format, ##args)
#define PE_PRINT_PRIME7(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME7, format, ##args)
#define PE_PRINT_PRIME8(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME8, format, ##args)
#define PE_PRINT_PRIME9(format, args...)	\
	DBG_PRINT(g_pe_debug_fd, PE_LOGM_LEVEL_PRIME9, format, ##args)
/*****************************************************************/

static int g_sl_init = 0;
int sl_shm_fd = -1;
SL_HDR_SHM_MAP_T *p_sl_shm = NULL;
SL_HDR_SHM_MAP_T volatile *sptr_sl_shm = NULL;
static int sl_version = 14202;//201805101340
static int sl_dbg_level = 0;
static int sl_dbg_oetf = PQ;
static int sl_dbg_bright = 1000;
static unsigned int sl_dbg_info[10] = {2,2,2,2,2,2,2,2,2,2};

static void KADP_PE_SL_DBG_ShowHdrPrimeMeta(void *setting);
static void KADP_PE_SL_DBG_ShowHdrPrimeLut(void *setting);
static int KADP_PE_SL_GetHdrPrimeLut(struct hdr_data *data, struct sl_hdr_metadata *meta, SL_HDR_PRIME_LUT_T *lut);
static int KADP_PE_SL13_GetMetaOnPayloadMode1(struct hdr_data *data, struct sl_hdr_metadata *meta);
static int KADP_PE_SL13_GetMetaOnPayloadMode0(struct hdr_data *data, struct sl_hdr_metadata *meta);
static int KADP_PE_SL14_GetPrimeMeta(struct hdr_data *data, struct sl_hdr_metadata *meta);
static int KADP_PE_SL13_GetPrimeMeta(struct hdr_data *data, struct sl_hdr_metadata *meta);
static int KADP_PE_SL_GetPrimeMeta(struct hdr_data *data, struct sl_hdr_metadata *meta);

void KADP_PE_SL_SetHdrPrimeLutDbgLevel(int value)
{
	sl_dbg_level = value;
}
int KADP_PE_SL_GetHdrPrimeLutDbgLevel(void)
{
	return sl_dbg_level;
}
void KADP_PE_SL_SetHdrPrimeLutDbgOetf(int value)
{
	sl_dbg_oetf = value;
}
int KADP_PE_SL_GetHdrPrimeLutDbgOetf(void)
{
	return sl_dbg_oetf;//0:BT1886,1:PQ,2:BT709,3:ARIB
}
void KADP_PE_SL_SetHdrPrimeLutDbgBright(int value)
{
	sl_dbg_bright = value;
}
int KADP_PE_SL_GetHdrPrimeLutDbgBright(void)
{
	return sl_dbg_bright;//100,1000,2000
}
int KADP_PE_SL_GetHdrPrimeVersion(void)
{
	return sl_version;
}
void KADP_PE_SL_SetHdrPrimeLutDbgInfo(unsigned int *value)
{
	memcpy(sl_dbg_info, value, sizeof(unsigned int)*10);
}
void KADP_PE_SL_GetHdrPrimeLutDbgInfo(unsigned int *value)
{
	memcpy(value, sl_dbg_info, sizeof(unsigned int)*10);
}
static void KADP_PE_SL_DBG_ShowHdrPrimeMeta(void *setting)
{
	struct sl_hdr_metadata *meta;
	if (!setting)	{PE_PRINT_NOTI("[HdrPrimeMeta]setting is null\n");return;}
	meta = (struct sl_hdr_metadata *)setting;

	KADP_PE_SL_DBG_PRINT(meta->partID);
	KADP_PE_SL_DBG_PRINT(meta->majorSpecVersionID);
	KADP_PE_SL_DBG_PRINT(meta->minorSpecVersionID);
	KADP_PE_SL_DBG_PRINT(meta->payloadMode);
	KADP_PE_SL_DBG_PRINT(meta->hdrPicColourSpace);
	KADP_PE_SL_DBG_PRINT(meta->hdrDisplayColourSpace);
	KADP_PE_SL_DBG_PRINT(meta->hdrDisplayMaxLuminance);
	KADP_PE_SL_DBG_PRINT(meta->hdrDisplayMinLuminance);
	KADP_PE_SL_DBG_PRINT(meta->sdrPicColourSpace);
	KADP_PE_SL_DBG_PRINT(meta->sdrDisplayColourSpace);
	KADP_PE_SL_DBG_PRINT(meta->sdrDisplayMaxLuminance);
	KADP_PE_SL_DBG_PRINT(meta->sdrDisplayMinLuminance);
	KADP_PE_SL_DBG_PRINT(meta->matrixCoefficient[0]);
	KADP_PE_SL_DBG_PRINT(meta->matrixCoefficient[1]);
	KADP_PE_SL_DBG_PRINT(meta->matrixCoefficient[2]);
	KADP_PE_SL_DBG_PRINT(meta->matrixCoefficient[3]);
	KADP_PE_SL_DBG_PRINT(meta->chromaToLumaInjection[0]);
	KADP_PE_SL_DBG_PRINT(meta->chromaToLumaInjection[1]);
	KADP_PE_SL_DBG_PRINT(meta->kCoefficient[0]);
	KADP_PE_SL_DBG_PRINT(meta->kCoefficient[1]);
	KADP_PE_SL_DBG_PRINT(meta->kCoefficient[2]);
	if (!meta->payloadMode)	//use variables
	{
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmInputSignalBlackLevelOffset);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmInputSignalWhiteLevelOffset);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.shadowGain);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.highlightGain);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.midToneWidthAdjFactor);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningNumVal);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningX[0]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningX[1]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningX[8]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningX[9]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningY[0]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningY[1]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningY[8]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.tmOutputFineTuningY[9]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainNumVal);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainX[0]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainX[1]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainX[4]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainX[5]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainY[0]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainY[1]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainY[4]);
		KADP_PE_SL_DBG_PRINT(meta->u.variables.saturationGainY[5]);
	}
	else	//use tables
	{
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingNumVal);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingX[0]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingX[1]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingX[31]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingX[32]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingX[63]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingX[64]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingY[0]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingY[1]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingY[31]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingY[32]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingY[63]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.luminanceMappingY[64]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionNumVal);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionX[0]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionX[1]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionX[31]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionX[32]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionX[63]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionX[64]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionY[0]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionY[1]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionY[31]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionY[32]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionY[63]);
		KADP_PE_SL_DBG_PRINT(meta->u.tables.colourCorrectionY[64]);
	}
	PE_PRINT_NOTI("\n");
	return;
}
static void KADP_PE_SL_DBG_ShowHdrPrimeLut(void *setting)
{
	SL_HDR_PRIME_LUT_T *lut;
	if (!setting)	{PE_PRINT_NOTI("[HdrPrimeLut]setting is null\n");return;}
	lut = (SL_HDR_PRIME_LUT_T *)setting;
	KADP_PE_SL_DBG_PRINT(lut->mu0);
	KADP_PE_SL_DBG_PRINT(lut->mu1);
	KADP_PE_SL_DBG_PRINT(lut->C_LUT[0]);
	KADP_PE_SL_DBG_PRINT(lut->C_LUT[1]);
	KADP_PE_SL_DBG_PRINT(lut->C_LUT[63]);
	KADP_PE_SL_DBG_PRINT(lut->C_LUT[64]);
	KADP_PE_SL_DBG_PRINT(lut->P_LUT[0]);
	KADP_PE_SL_DBG_PRINT(lut->P_LUT[1]);
	KADP_PE_SL_DBG_PRINT(lut->P_LUT[63]);
	KADP_PE_SL_DBG_PRINT(lut->P_LUT[64]);
	KADP_PE_SL_DBG_PRINT(lut->S_LUT[0]);
	KADP_PE_SL_DBG_PRINT(lut->S_LUT[1]);
	KADP_PE_SL_DBG_PRINT(lut->S_LUT[63]);
	KADP_PE_SL_DBG_PRINT(lut->S_LUT[64]);
	KADP_PE_SL_DBG_PRINT(lut->I_LUT[0]);
	KADP_PE_SL_DBG_PRINT(lut->I_LUT[1]);
	KADP_PE_SL_DBG_PRINT(lut->I_LUT[63]);
	KADP_PE_SL_DBG_PRINT(lut->I_LUT[64]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT[0]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT[1]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT[63]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT[64]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT_THRESHOLD[0]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT_THRESHOLD[1]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT_THRESHOLD[2]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT_STEP[0]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT_STEP[1]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT_STEP[2]);
	KADP_PE_SL_DBG_PRINT(lut->D_LUT_STEP[3]);
	KADP_PE_SL_DBG_PRINT(lut->OCT[0]);
	KADP_PE_SL_DBG_PRINT(lut->OCT[1]);
	KADP_PE_SL_DBG_PRINT(lut->OCT[5]);
	KADP_PE_SL_DBG_PRINT(lut->OCT[6]);
	PE_PRINT_NOTI("\n");
	return;
}
static int KADP_PE_SL_GetHdrPrimeLut(struct hdr_data *data, struct sl_hdr_metadata *meta, SL_HDR_PRIME_LUT_T *lut)
{
    // Main parameters
    int display_OETF = sl_dbg_oetf;
	int display_Brightness = sl_dbg_bright;//sl_hdr_metadata->hdrDisplayMaxLuminance
    int display_Brightness_Max;
	int yuv_range = YUV_LIMITED_RANGE;
	//int i,cc_shift, mapy_cl, cur_dbg_level;//fix compile warning
	unsigned int timestamp = -1;
	unsigned short mu0;
	unsigned short mu1;
    // UV2SRGB matrix
    int *OCT;
    unsigned short *C_LUT;
    unsigned short *P_LUT;
    unsigned short *S_LUT;
    unsigned short *I_LUT;
    unsigned short *D_LUT;
    unsigned short *D_LUT_THRESHOLD;
    unsigned short *D_LUT_STEP;
    int inv_y_ratio, inv_chroma_ratio, footroom, l_headroom, c_headroom;
    // RGB2YUV matrix (fixed)
    //int RGBtoYUV_709[9] = { 186, 627, 63, -103, -346, 448, 448, -407, -41 };
    //int RGBtoYUV_2020[9] = { 230, 595, 52, -125, -323, 448, 448, -412, -36 };
    //int *RGBtoYUV;
    //int OCT_709_SDR2MDR[7]  = { 32, 70, 175, 403, -48, -120, 475 };
    //int OCT_2020_SDR2MDR[7] = { 33, 58, 203, 377, -42, -146, 482 };
    //int OCT_709_HDR2MDR[7]  = {  0,  0,   0, 202, -24, -60, 238 };
    //int OCT_2020_HDR2MDR[7] = {  0,  0,   0, 189, -21, -73, 241 };

	if (meta==NULL)		return -100;
	if (lut==NULL)		return -101;
	if (data==NULL)		return -102;

	timestamp = data->timestamp;
	OCT = lut->OCT;
	C_LUT = lut->C_LUT;
	P_LUT = lut->P_LUT;
	S_LUT = lut->S_LUT;
	I_LUT = lut->I_LUT;
	D_LUT = lut->D_LUT;
	D_LUT_THRESHOLD = lut->D_LUT_THRESHOLD;
	D_LUT_STEP = lut->D_LUT_STEP;

    Fill_S_LUT(S_LUT);
    Fill_I_LUT(I_LUT);

	display_Brightness_Max = meta->hdrDisplayMaxLuminance + ((meta->hdrDisplayMaxLuminance + 2) >> 2);
	if (display_Brightness > display_Brightness_Max)
	{
		PE_PRINT_NOTI("Bad input : display_Brightness (%d) > display_Brightness_Max (%d)\n", display_Brightness, display_Brightness_Max);
		display_Brightness = display_Brightness_Max;
	}
	// Compute LUTs
	Compute_LUTs(meta, display_Brightness, yuv_range, &mu0, &mu1, OCT, C_LUT, P_LUT, &inv_y_ratio, &inv_chroma_ratio, &footroom, &l_headroom, &c_headroom);

	// Fill D_LUT
	Fill_D_LUT(meta, display_OETF, display_Brightness, D_LUT, D_LUT_THRESHOLD, D_LUT_STEP);
	lut->mu0 = mu0;
	lut->mu1 = mu1;

	if (sl_dbg_level==0x100)
	{
		KADP_PE_SL_DBG_ShowHdrPrimeMeta((void *)meta);
	}
	if (sl_dbg_level==0x101)
	{
		PE_PRINT_NOTI("mu:%4d,%4d ",lut->mu0, lut->mu1);
		PE_PRINT_NOTI("C:%4d,%4d,%4d,%4d ",C_LUT[0],C_LUT[1],C_LUT[63],C_LUT[64]);
		PE_PRINT_NOTI("P:%4d,%4d,%4d,%4d ",P_LUT[0],P_LUT[1],P_LUT[63],P_LUT[64]);
		PE_PRINT_NOTI("S:%4d,%4d,%4d,%4d ",S_LUT[0],S_LUT[1],S_LUT[63],S_LUT[64]);
		PE_PRINT_NOTI("I:%4d,%4d,%4d,%4d ",I_LUT[0],I_LUT[1],I_LUT[63],I_LUT[64]);
		PE_PRINT_NOTI("D:%4d,%4d,%4d,%4d,%4d,%4d ",D_LUT[0],D_LUT[64],D_LUT_THRESHOLD[0],D_LUT_THRESHOLD[2],D_LUT_STEP[0],D_LUT_STEP[3]);
		PE_PRINT_NOTI("O:%4d,%4d,%4d,%4d\n",OCT[0],OCT[1],OCT[5],OCT[6]);
	}
	if (sl_dbg_level==0x102)
	{
		KADP_PE_SL_DBG_ShowHdrPrimeLut((void *)lut);
	}

	PE_PRINT_PRIME2("[meta][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d\n",timestamp,
		meta->partID,
		meta->majorSpecVersionID,
		meta->minorSpecVersionID,
		meta->payloadMode,
		meta->hdrPicColourSpace,

		meta->hdrDisplayColourSpace,
		meta->hdrDisplayMaxLuminance,
		meta->hdrDisplayMinLuminance,
		meta->sdrPicColourSpace,
		meta->sdrDisplayColourSpace,

		meta->sdrDisplayMaxLuminance,
		meta->sdrDisplayMinLuminance,
		meta->matrixCoefficient[0],
		meta->matrixCoefficient[1],
		meta->matrixCoefficient[2],

		meta->matrixCoefficient[3],
		meta->chromaToLumaInjection[0],
		meta->chromaToLumaInjection[1],
		meta->kCoefficient[0],
		meta->kCoefficient[1],

		meta->kCoefficient[2]);

	if (!meta->payloadMode)	//use variables
	{
		PE_PRINT_PRIME3("[meta.v][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d\n",timestamp,
			meta->u.variables.tmInputSignalBlackLevelOffset,
			meta->u.variables.tmInputSignalWhiteLevelOffset,
			meta->u.variables.shadowGain,
			meta->u.variables.highlightGain,
			meta->u.variables.midToneWidthAdjFactor,

			meta->u.variables.tmOutputFineTuningNumVal,
			meta->u.variables.tmOutputFineTuningX[0],
			meta->u.variables.tmOutputFineTuningX[1],
			meta->u.variables.tmOutputFineTuningX[8],
			meta->u.variables.tmOutputFineTuningX[9],

			meta->u.variables.tmOutputFineTuningY[0],
			meta->u.variables.tmOutputFineTuningY[1],
			meta->u.variables.tmOutputFineTuningY[8],
			meta->u.variables.tmOutputFineTuningY[9],
			meta->u.variables.saturationGainNumVal,

			meta->u.variables.saturationGainX[0],
			meta->u.variables.saturationGainX[1],
			meta->u.variables.saturationGainX[4],
			meta->u.variables.saturationGainX[5],
			meta->u.variables.saturationGainY[0],

			meta->u.variables.saturationGainY[1],
			meta->u.variables.saturationGainY[4],
			meta->u.variables.saturationGainY[5]);
	}
	else
	{
		PE_PRINT_PRIME3("[meta.t][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d\n",timestamp,
			meta->u.tables.luminanceMappingNumVal,
			meta->u.tables.luminanceMappingX[0],
			meta->u.tables.luminanceMappingX[1],
			meta->u.tables.luminanceMappingX[32],
			meta->u.tables.luminanceMappingX[63],

			meta->u.tables.luminanceMappingX[64],
			meta->u.tables.luminanceMappingY[0],
			meta->u.tables.luminanceMappingY[1],
			meta->u.tables.luminanceMappingY[32],
			meta->u.tables.luminanceMappingY[63],

			meta->u.tables.luminanceMappingY[64],
			meta->u.tables.colourCorrectionNumVal,
			meta->u.tables.colourCorrectionX[0],
			meta->u.tables.colourCorrectionX[1],
			meta->u.tables.colourCorrectionX[32],

			meta->u.tables.colourCorrectionX[63],
			meta->u.tables.colourCorrectionX[64],
			meta->u.tables.colourCorrectionY[0],
			meta->u.tables.colourCorrectionY[1],
			meta->u.tables.colourCorrectionY[32],

			meta->u.tables.colourCorrectionY[63],
			meta->u.tables.colourCorrectionY[64]);
	}

	PE_PRINT_PRIME0("[LUT0][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d\n",timestamp,
		lut->mu0,
		lut->mu1,
		lut->C_LUT[0],
		lut->C_LUT[1],
		lut->C_LUT[31],

		lut->C_LUT[32],
		lut->C_LUT[63],
		lut->C_LUT[64],
		lut->P_LUT[0],
		lut->P_LUT[1],

		lut->P_LUT[31],
		lut->P_LUT[32],
		lut->P_LUT[63],
		lut->P_LUT[64],
		lut->S_LUT[0],

		lut->S_LUT[1],
		lut->S_LUT[63],
		lut->S_LUT[64],
		lut->I_LUT[0],
		lut->I_LUT[1],

		lut->I_LUT[63],
		lut->I_LUT[64]);

	PE_PRINT_PRIME1("[LUT1][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d\n",timestamp,
		lut->D_LUT[0],
		lut->D_LUT[1],
		lut->D_LUT[31],
		lut->D_LUT[32],
		lut->D_LUT[63],

		lut->D_LUT[64],
		lut->D_LUT_THRESHOLD[0],
		lut->D_LUT_THRESHOLD[1],
		lut->D_LUT_THRESHOLD[2],
		lut->D_LUT_STEP[0],

		lut->D_LUT_STEP[1],
		lut->D_LUT_STEP[2],
		lut->D_LUT_STEP[3],
		lut->OCT[0],
		lut->OCT[1],

		lut->OCT[2],
		lut->OCT[3],
		lut->OCT[4],
		lut->OCT[5],
		lut->OCT[6]);
    return 0;
}
static int KADP_PE_SL13_GetMetaOnPayloadMode1(struct hdr_data *data, struct sl_hdr_metadata *meta)
{
	int ret = 0;
	UINT32 i,j;
	unsigned int timestamp = -1;
	struct hdr_vui *pVui = data->vui;
	struct hdr_sei *pSei = data->sei;
	struct hdr_cri *pCri = data->cri;
	struct hdr_tsi *pTsi = data->tsi;

	timestamp = data->timestamp;

	/* PAYLOAD MODE 1, CRI */
	if (pCri->colour_remap_primaries == 1 && pCri->colour_remap_matrix_coefficients == 1)
	{
		meta->hdrPicColourSpace = 0;
	}
	else if (pCri->colour_remap_primaries == 9 && pCri->colour_remap_matrix_coefficients == 9)
	{
		meta->hdrPicColourSpace = 1;
	}

	if (pSei->disp_prim_x[0] == 15000 && pSei->disp_prim_y[0] == 30000)
	{
		meta->hdrDisplayColourSpace = 0;
	}
	else if (pSei->disp_prim_x[0] == 8500 && pSei->disp_prim_y[0] == 39850)
	{
		meta->hdrDisplayColourSpace = 1;
	}
	else if (pSei->disp_prim_x[0] == 13250 && pSei->disp_prim_y[0] == 34500)
	{
		meta->hdrDisplayColourSpace = 2;
	}

	meta->hdrDisplayMaxLuminance = Min(50*((pSei->max_disp_mastering_luminance+250000)/500000),10000);
	meta->hdrDisplayMinLuminance = Min(pSei->min_disp_mastering_luminance/10000,10000);

	//Common
	if (pVui->color_primaries == 1 && pVui->matrix_coeffs == 1)
	{
		meta->sdrPicColourSpace = 0;
	}
	else if (pVui->color_primaries == 9 && pVui->matrix_coeffs == 9)
	{
		meta->sdrPicColourSpace = 1;
	}

	meta->sdrDisplayColourSpace = 0; //N/A

	#if 1	//TODO:
	meta->sdrDisplayMaxLuminance = 100;
	meta->sdrDisplayMinLuminance = 0;
	if (!meta->hdrPicColourSpace)
	{
		meta->matrixCoefficient[0] = 915;
		meta->matrixCoefficient[1] = 464;
		meta->matrixCoefficient[2] = 392;
		meta->matrixCoefficient[3] = 987;
		meta->chromaToLumaInjection[0] = 0;
		meta->chromaToLumaInjection[1] = 0;
	}
	else
	{
		meta->matrixCoefficient[0] = 889;
		meta->matrixCoefficient[1] = 470;
		meta->matrixCoefficient[2] = 366;
		meta->matrixCoefficient[3] = 994;
		meta->chromaToLumaInjection[0] = 0;
		meta->chromaToLumaInjection[1] = 1638;
	}
	meta->kCoefficient[0] = 0;
	meta->kCoefficient[1] = 0;
	meta->kCoefficient[2] = 0;
	#endif

	meta->u.tables.luminanceMappingNumVal = pCri->post_lut_num_val_minus1[0]+1;

	#if 1	//TODO:
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 2; j++) {
			meta->u.tables.luminanceMappingX[2 * i + j] = ((2 - j) * pCri->post_lut_coded_value[0][i] + j * pCri->post_lut_coded_value[0][i+1] + 1) >> 1;
			meta->u.tables.luminanceMappingY[2 * i + j] = ((2 - j) * pCri->post_lut_target_value[0][i] + j * pCri->post_lut_target_value[0][i+1] + 1) >> 1;
		}
	}
	meta->u.tables.luminanceMappingX[64] = pCri->post_lut_coded_value[0][32];
	meta->u.tables.luminanceMappingY[64] = pCri->post_lut_target_value[0][32];
	#else
	for (i=0;i<65;i++)
	{
		if (i>32)	meta->u.tables.luminanceMappingX[i] = pCri->post_lut_coded_value[0][32];
		else		meta->u.tables.luminanceMappingX[i] = pCri->post_lut_coded_value[0][i];
	}

	for (i=0;i<65;i++)
	{
		if (i>32)	meta->u.tables.luminanceMappingY[i] = pCri->post_lut_target_value[0][32];
		else		meta->u.tables.luminanceMappingY[i] = pCri->post_lut_target_value[0][i];
	}
	#endif

	meta->u.tables.colourCorrectionNumVal = pCri->post_lut_num_val_minus1[1]+1;

	#if 1	//TODO:
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 2; j++) {
			meta->u.tables.colourCorrectionX[2 * i + j] = ((2 - j) * pCri->post_lut_coded_value[1][i] + j * pCri->post_lut_coded_value[1][i+1] + 1) >> 1;
			meta->u.tables.colourCorrectionY[2 * i + j] = ((2 - j) * pCri->post_lut_target_value[1][i] + j * pCri->post_lut_target_value[1][i+1] + 1) >> 1;
		}
	}
    meta->u.tables.colourCorrectionX[64] = pCri->post_lut_coded_value[0][32];
    meta->u.tables.colourCorrectionY[64] = pCri->post_lut_target_value[0][32];
	#else
	for (i=0;i<65;i++)
	{
		if (i>32)	meta->u.tables.colourCorrectionX[i] = pCri->post_lut_coded_value[1][32];
		else		meta->u.tables.colourCorrectionX[i] = pCri->post_lut_coded_value[1][i];
	}

	for (i=0;i<65;i++)
	{
		if (i>32)	meta->u.tables.colourCorrectionY[i] = pCri->post_lut_target_value[1][32];
		else		meta->u.tables.colourCorrectionY[i] = pCri->post_lut_target_value[1][i];
	}
	#endif

	PE_PRINT_PRIME4("[tsi][%d] %d %d %d %d %d [cri0] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d\n",timestamp,
		pTsi->itu_t_t35_country_code,
		pTsi->terminal_provider_code,
		pTsi->terminal_provider_oriented_code_message_idc,
		pTsi->ts_103_433_spec_version,
		pTsi->ts_103_433_payload_mode,

		pCri->colour_remap_id,
		pCri->colour_remap_cancel_flag,
		pCri->colour_remap_persistence_flag,
		pCri->colour_remap_video_signal_info_present_flag,
		pCri->colour_remap_full_range_flag,

		pCri->colour_remap_primaries,
		pCri->colour_remap_transfer_function,
		pCri->colour_remap_matrix_coefficients,
		pCri->colour_remap_input_bit_depth,
		pCri->colour_remap_bit_depth,

		pCri->pre_lut_num_val_minus1[0],
		pCri->pre_lut_num_val_minus1[1],
		pCri->pre_lut_num_val_minus1[2],
		pCri->pre_lut_coded_value[0][0],
		pCri->pre_lut_coded_value[0][32]);

	PE_PRINT_PRIME5("[cri1][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d\n",timestamp,
		pCri->pre_lut_coded_value[1][0],
		pCri->pre_lut_coded_value[1][32],
		pCri->pre_lut_coded_value[2][0],
		pCri->pre_lut_coded_value[2][32],
		pCri->pre_lut_target_value[0][0],

		pCri->pre_lut_target_value[0][32],
		pCri->pre_lut_target_value[1][0],
		pCri->pre_lut_target_value[1][32],
		pCri->pre_lut_target_value[2][0],
		pCri->pre_lut_target_value[2][32],

		pCri->colour_remap_matrix_present_flag,
		pCri->log2_matrix_denom,
		pCri->colour_remap_coeffs[0][0],
		pCri->colour_remap_coeffs[0][2],
		pCri->colour_remap_coeffs[1][0]);

	PE_PRINT_PRIME6("[cri2][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d\n",timestamp,
		pCri->colour_remap_coeffs[1][2],
		pCri->colour_remap_coeffs[2][0],
		pCri->colour_remap_coeffs[2][2],
		pCri->post_lut_num_val_minus1[0],
		pCri->post_lut_num_val_minus1[1],

		pCri->post_lut_num_val_minus1[2],
		pCri->post_lut_coded_value[0][0],
		pCri->post_lut_coded_value[0][32],
		pCri->post_lut_coded_value[1][0],
		pCri->post_lut_coded_value[1][32],

		pCri->post_lut_coded_value[2][0],
		pCri->post_lut_coded_value[2][32],
		pCri->post_lut_target_value[0][0],
		pCri->post_lut_target_value[0][32],
		pCri->post_lut_target_value[1][0],

		pCri->post_lut_target_value[1][32],
		pCri->post_lut_target_value[2][0],
		pCri->post_lut_target_value[2][32]);

	PE_PRINT_PRIME7("[sei][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d [vui] %d %d %d %d\n",timestamp,
		pSei->disp_prim_x[0],
		pSei->disp_prim_x[1],
		pSei->disp_prim_x[2],
		pSei->disp_prim_y[0],
		pSei->disp_prim_y[1],

		pSei->disp_prim_y[2],
		pSei->white_point_x,
		pSei->white_point_y,
		pSei->max_disp_mastering_luminance,
		pSei->min_disp_mastering_luminance,

		pSei->max_content_light_level,
		pSei->max_pic_average_light_level,
		pSei->hdr_transfer_characteristic_idc,

		pVui->transfer_characteristics,
		pVui->color_primaries,
		pVui->matrix_coeffs,
		pVui->video_full_range_flag);
	return ret;
}
static int KADP_PE_SL13_GetMetaOnPayloadMode0(struct hdr_data *data, struct sl_hdr_metadata *meta)
{
	int ret = 0;
	UINT32 i;
	unsigned int timestamp = -1;
	struct hdr_vui *pVui = data->vui;
	struct hdr_sei *pSei = data->sei;
	struct hdr_cvri *pCvri = data->cvri;
	struct hdr_tsi *pTsi = data->tsi;

	timestamp = data->timestamp;

	/* PAYLOAD MODE 0, CVRI */
	if(pCvri->cv_rec_primaries == 1 && pCvri->cv_rec_matrix_coefficients == 1)
	{
		meta->hdrPicColourSpace = 0;
	}
	else if(pCvri->cv_rec_primaries == 9 && pCvri->cv_rec_matrix_coefficients == 9)
	{
		meta->hdrPicColourSpace = 1;
	}

	if (pSei->disp_prim_x[0] == 15000 && pSei->disp_prim_y[0] == 30000)
	{
		meta->hdrDisplayColourSpace = 0;
	}
	else if (pSei->disp_prim_x[0] == 8500 && pSei->disp_prim_y[0] == 39850)
	{
		meta->hdrDisplayColourSpace = 1;
	}
	else if (pSei->disp_prim_x[0] == 13250 && pSei->disp_prim_y[0] == 34500)
	{
		meta->hdrDisplayColourSpace = 2;
	}

	meta->hdrDisplayMaxLuminance = Min(50*((pSei->max_disp_mastering_luminance+250000)/500000),10000);
	meta->hdrDisplayMinLuminance = Min(pSei->min_disp_mastering_luminance/10000,10000);

	//Common
	if (pVui->color_primaries == 1 && pVui->matrix_coeffs == 1)
	{
		meta->sdrPicColourSpace = 0;
	}
	else if (pVui->color_primaries == 9 && pVui->matrix_coeffs == 9)
	{
		meta->sdrPicColourSpace = 1;
	}

	meta->sdrDisplayColourSpace = 0; //N/A

	/*****************************************/
	/* fixed for v1300 */
	/*****************************************/
	meta->sdrDisplayMaxLuminance = 100;
	meta->sdrDisplayMinLuminance = 0;
	if (!meta->hdrPicColourSpace)
	{
		meta->matrixCoefficient[0] = 915;
		meta->matrixCoefficient[1] = 464;
		meta->matrixCoefficient[2] = 392;
		meta->matrixCoefficient[3] = 987;
		meta->chromaToLumaInjection[0] = 0;
		meta->chromaToLumaInjection[1] = 0;
	}
	else
	{
		meta->matrixCoefficient[0] = 889;
		meta->matrixCoefficient[1] = 470;
		meta->matrixCoefficient[2] = 366;
		meta->matrixCoefficient[3] = 994;
		meta->chromaToLumaInjection[0] = 0;
		meta->chromaToLumaInjection[1] = 1638;
	}
	meta->kCoefficient[0] = 0;
	meta->kCoefficient[1] = 0;
	meta->kCoefficient[2] = 0;
	/*****************************************/

	meta->u.variables.tmInputSignalBlackLevelOffset = pCvri->tone_mapping_input_signal_black_level_offset;
	meta->u.variables.tmInputSignalWhiteLevelOffset = pCvri->tone_mapping_input_signal_white_level_offset;
	meta->u.variables.shadowGain = pCvri->shadow_gain_control;
	meta->u.variables.highlightGain = pCvri->highlight_gain_control;
	meta->u.variables.midToneWidthAdjFactor = pCvri->mid_tone_width_adjustment_factor;
	meta->u.variables.tmOutputFineTuningNumVal = pCvri->tone_mapping_output_fine_tuning_num_val;

	for (i=0;i<10;i++)
	{
		meta->u.variables.tmOutputFineTuningX[i] = pCvri->tone_mapping_output_fine_tuning_x[i];
	}

	for (i=0;i<10;i++)
	{
		meta->u.variables.tmOutputFineTuningY[i] = pCvri->tone_mapping_output_fine_tuning_y[i];
	}

	meta->u.variables.saturationGainNumVal = pCvri->saturation_gain_num_val;

	for (i=0;i<6;i++)
	{
		meta->u.variables.saturationGainX[i] = pCvri->saturation_gain_x[i];
	}

	for (i=0;i<6;i++)
	{
		meta->u.variables.saturationGainY[i] = pCvri->saturation_gain_y[i];
	}

	PE_PRINT_PRIME4("[tsi][%d] %d %d %d %d %d [cvri0] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d\n",timestamp,
		pTsi->itu_t_t35_country_code,
		pTsi->terminal_provider_code,
		pTsi->terminal_provider_oriented_code_message_idc,
		pTsi->ts_103_433_spec_version,
		pTsi->ts_103_433_payload_mode,

		pCvri->itu_t_t35_country_code,
		pCvri->terminal_provider_code,
		pCvri->terminal_provider_oriented_code_message_idc,
		pCvri->cv_rec_id,
		pCvri->cv_rec_cancel_flag,

		pCvri->cv_rec_persistence_flag,
		pCvri->cv_rec_target_info_flag,
		pCvri->cv_rec_primaries,
		pCvri->cv_rec_matrix_coefficients,
		pCvri->tone_mapping_input_signal_black_level_offset,

		pCvri->tone_mapping_input_signal_white_level_offset,
		pCvri->shadow_gain_control,
		pCvri->highlight_gain_control,
		pCvri->mid_tone_width_adjustment_factor,
		pCvri->tone_mapping_output_fine_tuning_num_val);

	PE_PRINT_PRIME5("[cvri][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d\n",timestamp,
		pCvri->tone_mapping_output_fine_tuning_x[0],
		pCvri->tone_mapping_output_fine_tuning_x[1],
		pCvri->tone_mapping_output_fine_tuning_x[5],
		pCvri->tone_mapping_output_fine_tuning_x[7],
		pCvri->tone_mapping_output_fine_tuning_x[9],

		pCvri->tone_mapping_output_fine_tuning_y[0],
		pCvri->tone_mapping_output_fine_tuning_y[1],
		pCvri->tone_mapping_output_fine_tuning_y[5],
		pCvri->tone_mapping_output_fine_tuning_y[7],
		pCvri->tone_mapping_output_fine_tuning_y[9],

		pCvri->saturation_gain_num_val,
		pCvri->saturation_gain_x[0],
		pCvri->saturation_gain_x[1],
		pCvri->saturation_gain_x[2],
		pCvri->saturation_gain_x[3],

		pCvri->saturation_gain_x[4],
		pCvri->saturation_gain_x[5],
		pCvri->saturation_gain_y[0],
		pCvri->saturation_gain_y[1],
		pCvri->saturation_gain_y[2],

		pCvri->saturation_gain_y[3],
		pCvri->saturation_gain_y[4],
		pCvri->saturation_gain_y[5]);

	PE_PRINT_PRIME6("[sei][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d [vui] %d %d %d %d\n",timestamp,
		pSei->disp_prim_x[0],
		pSei->disp_prim_x[1],
		pSei->disp_prim_x[2],
		pSei->disp_prim_y[0],
		pSei->disp_prim_y[1],

		pSei->disp_prim_y[2],
		pSei->white_point_x,
		pSei->white_point_y,
		pSei->max_disp_mastering_luminance,
		pSei->min_disp_mastering_luminance,

		pSei->max_content_light_level,
		pSei->max_pic_average_light_level,
		pSei->hdr_transfer_characteristic_idc,

		pVui->transfer_characteristics,
		pVui->color_primaries,
		pVui->matrix_coeffs,
		pVui->video_full_range_flag);
	return ret;
}
static int KADP_PE_SL14_GetPrimeMeta(struct hdr_data *data, struct sl_hdr_metadata *meta)
{
	int ret = 0;
	UINT32 i;
	unsigned int timestamp = -1;
	struct hdr_vui *pVui;
	struct hdr_sei *pSei;
	struct hdr_sl_hdr *pSl_hdr;

	if (data==NULL)				return -400;
	if (meta==NULL)				return -401;
	if (data->vui==NULL)		return -402;
	if (data->sei==NULL)		return -403;
	if (data->sl_hdr==NULL)		return -404;

	timestamp = data->timestamp;
	pVui = data->vui;
	pSei = data->sei;
	pSl_hdr = data->sl_hdr;

	meta->partID = pSl_hdr->sl_hdr_mode_value_minus1+1;
	meta->majorSpecVersionID = pSl_hdr->sl_hdr_spec_major_version_idc;
	meta->minorSpecVersionID = pSl_hdr->sl_hdr_spec_major_version_idc;
	meta->payloadMode = pSl_hdr->sl_hdr_payload_mode;
	for (i = 0; i < 4; i++) {
		meta->matrixCoefficient[i] = pSl_hdr->matrix_coefficient_value[i];
	}
	for (i = 0; i < 2; i++) {
		meta->chromaToLumaInjection[i] = pSl_hdr->chroma_to_luma_injection[i];
	}
	for (i = 0; i < 3; i++) {
		meta->kCoefficient[i] = pSl_hdr->k_coefficient_value[i];
	}

	if (pSl_hdr->src_mdcv_info_present_flag==1)
	{
		meta->sdrPicColourSpace = (pSl_hdr->target_picture_primaries==1)? 0:1;
		meta->sdrDisplayMaxLuminance = Min(50 * ((pSl_hdr->target_picture_max_luminance + 25) / 50), 10000);
		meta->sdrDisplayMinLuminance = (pSl_hdr->target_picture_min_luminance + 5000) / 10000;

		if (pSl_hdr->src_mdcv_primaries_x[0] == 15000)      // 0.300 * 50000
			meta->hdrDisplayColourSpace = 0;
		else if (pSl_hdr->src_mdcv_primaries_x[0] == 8500)  // 0.170 * 50000
			meta->hdrDisplayColourSpace = 1;
		else if (pSl_hdr->src_mdcv_primaries_x[0] == 13250) // 0.265 * 50000
			meta->hdrDisplayColourSpace = 2;
		else
			meta->hdrDisplayColourSpace = 0;

		meta->hdrPicColourSpace = (meta->hdrDisplayColourSpace || meta->sdrPicColourSpace)? 1 : 0;
		meta->sdrDisplayColourSpace = (meta->sdrPicColourSpace == meta->hdrPicColourSpace)? meta->hdrDisplayColourSpace : 0;

		meta->hdrDisplayMaxLuminance = Min(50 * ((pSl_hdr->src_mdcv_max_mastering_luminance+ 25) / 50), 10000);
		meta->hdrDisplayMinLuminance = (pSl_hdr->src_mdcv_min_mastering_luminance + 5000) / 10000;
	}
	else
	{
		meta->sdrPicColourSpace = (pSl_hdr->target_picture_primaries==1)? 0:1;
		meta->sdrDisplayMaxLuminance = Min(50 * ((pSl_hdr->target_picture_max_luminance + 25) / 50), 10000);
		meta->sdrDisplayMinLuminance = (pSl_hdr->target_picture_min_luminance + 5000) / 10000;

		if (pSei->disp_prim_x[0] == 15000)      // 0.300 * 50000
			meta->hdrDisplayColourSpace = 0;
		else if (pSei->disp_prim_x[0] == 8500)  // 0.170 * 50000
			meta->hdrDisplayColourSpace = 1;
		else if (pSei->disp_prim_x[0] == 13250) // 0.265 * 50000
			meta->hdrDisplayColourSpace = 2;
		else
			meta->hdrDisplayColourSpace = 0;

		meta->hdrPicColourSpace = (meta->hdrDisplayColourSpace || meta->sdrPicColourSpace)? 1 : 0;
		meta->sdrDisplayColourSpace = (meta->sdrPicColourSpace == meta->hdrPicColourSpace)? meta->hdrDisplayColourSpace : 0;

		meta->hdrDisplayMaxLuminance = Min(50*((pSei->max_disp_mastering_luminance+250000)/500000),10000);
		meta->hdrDisplayMinLuminance = Min(pSei->min_disp_mastering_luminance/10000,10000);
	}

	if (!meta->payloadMode)
	{
		meta->u.variables.tmInputSignalBlackLevelOffset = pSl_hdr->tone_mapping_input_signal_black_level_offset;
		meta->u.variables.tmInputSignalWhiteLevelOffset = pSl_hdr->tone_mapping_input_signal_white_level_offset;
		meta->u.variables.shadowGain = pSl_hdr->shadow_gain_control;
		meta->u.variables.highlightGain = pSl_hdr->highlight_gain_control;
		meta->u.variables.midToneWidthAdjFactor = pSl_hdr->mid_tone_width_adjustment_factor;
		meta->u.variables.tmOutputFineTuningNumVal = pSl_hdr->tone_mapping_output_fine_tuning_num_val;
		meta->u.variables.saturationGainNumVal = pSl_hdr->saturation_gain_num_val;
		for (i = 0; i < meta->u.variables.tmOutputFineTuningNumVal; i++) {
			meta->u.variables.tmOutputFineTuningX[i] = pSl_hdr->tone_mapping_output_fine_tuning_x[i];
			meta->u.variables.tmOutputFineTuningY[i] = pSl_hdr->tone_mapping_output_fine_tuning_y[i];
		}
		for (i = 0; i < meta->u.variables.saturationGainNumVal; i++) {
			meta->u.variables.saturationGainX[i] = pSl_hdr->saturation_gain_x[i];
			meta->u.variables.saturationGainY[i] = pSl_hdr->saturation_gain_y[i];
		}
	}
	else
	{
		meta->u.tables.luminanceMappingNumVal = pSl_hdr->luminance_mapping_num_val;
		for (i = 0; i < meta->u.tables.luminanceMappingNumVal; i++) {
			if (!pSl_hdr->lm_uniform_sampling_flag)
				meta->u.tables.luminanceMappingX[i] = pSl_hdr->luminance_mapping_x[i];
			else
				meta->u.tables.luminanceMappingX[i] = i << 7;
			meta->u.tables.luminanceMappingY[i] = pSl_hdr->luminance_mapping_y[i];
		}
		meta->u.tables.colourCorrectionNumVal = pSl_hdr->colour_correction_num_val;
		for (i = 0; i < meta->u.tables.colourCorrectionNumVal; i++) {
			if (!pSl_hdr->cc_uniform_sampling_flag)
				meta->u.tables.colourCorrectionX[i] = pSl_hdr->colour_correction_x[i];
			else
				meta->u.tables.colourCorrectionX[i] = i << 5;
			meta->u.tables.colourCorrectionY[i] = pSl_hdr->colour_correction_y[i];
		}
	}

	PE_PRINT_PRIME4("[vui][%d] %d %d %d %d [sei] %d %d %d %d %d|%d %d %d %d %d|%d %d %d\n",timestamp,
		pVui->transfer_characteristics,
		pVui->color_primaries,
		pVui->matrix_coeffs,
		pVui->video_full_range_flag,

		pSei->disp_prim_x[0],
		pSei->disp_prim_x[1],
		pSei->disp_prim_x[2],
		pSei->disp_prim_y[0],
		pSei->disp_prim_y[1],

		pSei->disp_prim_y[2],
		pSei->white_point_x,
		pSei->white_point_y,
		pSei->max_disp_mastering_luminance,
		pSei->min_disp_mastering_luminance,

		pSei->max_content_light_level,
		pSei->max_pic_average_light_level,
		pSei->hdr_transfer_characteristic_idc);

	PE_PRINT_PRIME5("[sl0][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d\n",timestamp,
		pSl_hdr->itu_t_t35_country_code,
		pSl_hdr->terminal_provider_code,
		pSl_hdr->terminal_provider_oriented_code_message_idc,
		pSl_hdr->sl_hdr_mode_value_minus1,
		pSl_hdr->sl_hdr_spec_major_version_idc,

		pSl_hdr->sl_hdr_spec_minor_version_idc,
		pSl_hdr->sl_hdr_cancel_flag,
		pSl_hdr->sl_hdr_persistence_flag,
		pSl_hdr->coded_picture_info_present_flag,
		pSl_hdr->target_picture_info_present_flag,

		pSl_hdr->src_mdcv_info_present_flag,
		pSl_hdr->sl_hdr_extension_present_flag,
		pSl_hdr->sl_hdr_payload_mode,
		pSl_hdr->coded_picture_primaries,
		pSl_hdr->coded_picture_max_luminance,

		pSl_hdr->coded_picture_min_luminance,
		pSl_hdr->target_picture_primaries,
		pSl_hdr->target_picture_max_luminance,
		pSl_hdr->target_picture_min_luminance,
		pSl_hdr->src_mdcv_primaries_x[0]);

	PE_PRINT_PRIME6("[sl1][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d\n",timestamp,
		pSl_hdr->src_mdcv_primaries_x[1],
		pSl_hdr->src_mdcv_primaries_x[2],
		pSl_hdr->src_mdcv_primaries_y[0],
		pSl_hdr->src_mdcv_primaries_y[1],
		pSl_hdr->src_mdcv_primaries_y[2],

		pSl_hdr->src_mdcv_ref_white_x,
		pSl_hdr->src_mdcv_ref_white_y,
		pSl_hdr->src_mdcv_max_mastering_luminance,
		pSl_hdr->src_mdcv_min_mastering_luminance,
		pSl_hdr->matrix_coefficient_value[0],

		pSl_hdr->matrix_coefficient_value[1],
		pSl_hdr->matrix_coefficient_value[2],
		pSl_hdr->matrix_coefficient_value[3],
		pSl_hdr->chroma_to_luma_injection[0],
		pSl_hdr->chroma_to_luma_injection[1],

		pSl_hdr->k_coefficient_value[0],
		pSl_hdr->k_coefficient_value[1],
		pSl_hdr->k_coefficient_value[2]);

	if (!pSl_hdr->sl_hdr_payload_mode)
	{
		PE_PRINT_PRIME7("[sl2][p0][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d\n",timestamp,
			pSl_hdr->tone_mapping_input_signal_black_level_offset,
			pSl_hdr->tone_mapping_input_signal_white_level_offset,
			pSl_hdr->shadow_gain_control,
			pSl_hdr->highlight_gain_control,
			pSl_hdr->mid_tone_width_adjustment_factor,

			pSl_hdr->tone_mapping_output_fine_tuning_num_val,
			pSl_hdr->saturation_gain_num_val,
			pSl_hdr->tone_mapping_output_fine_tuning_x[0],
			pSl_hdr->tone_mapping_output_fine_tuning_x[1],
			pSl_hdr->tone_mapping_output_fine_tuning_x[14],

			pSl_hdr->tone_mapping_output_fine_tuning_x[15],
			pSl_hdr->tone_mapping_output_fine_tuning_y[0],
			pSl_hdr->tone_mapping_output_fine_tuning_y[1],
			pSl_hdr->tone_mapping_output_fine_tuning_y[14],
			pSl_hdr->tone_mapping_output_fine_tuning_y[15],

			pSl_hdr->saturation_gain_x[0],
			pSl_hdr->saturation_gain_x[1],
			pSl_hdr->saturation_gain_x[14],
			pSl_hdr->saturation_gain_x[15],
			pSl_hdr->saturation_gain_y[0],

			pSl_hdr->saturation_gain_y[1],
			pSl_hdr->saturation_gain_y[14],
			pSl_hdr->saturation_gain_y[15]);
	}
	else
	{
		PE_PRINT_PRIME7("[sl2][p1][%d] %d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d %d|%d %d %d %d\n",timestamp,
			pSl_hdr->lm_uniform_sampling_flag,
			pSl_hdr->luminance_mapping_num_val,
			pSl_hdr->luminance_mapping_x[0],
			pSl_hdr->luminance_mapping_x[1],
			pSl_hdr->luminance_mapping_x[64],

			pSl_hdr->luminance_mapping_x[126],
			pSl_hdr->luminance_mapping_x[127],
			pSl_hdr->luminance_mapping_y[0],
			pSl_hdr->luminance_mapping_y[1],
			pSl_hdr->luminance_mapping_y[64],

			pSl_hdr->luminance_mapping_y[126],
			pSl_hdr->luminance_mapping_y[127],
			pSl_hdr->cc_uniform_sampling_flag,
			pSl_hdr->colour_correction_num_val,
			pSl_hdr->colour_correction_x[0],

			pSl_hdr->colour_correction_x[1],
			pSl_hdr->colour_correction_x[64],
			pSl_hdr->colour_correction_x[126],
			pSl_hdr->colour_correction_x[127],
			pSl_hdr->colour_correction_y[0],

			pSl_hdr->colour_correction_y[1],
			pSl_hdr->colour_correction_y[64],
			pSl_hdr->colour_correction_y[126],
			pSl_hdr->colour_correction_y[127]);
	}
	return ret;
}
static int KADP_PE_SL13_GetPrimeMeta(struct hdr_data *data, struct sl_hdr_metadata *meta)
{
	int ret = 0;
	struct hdr_tsi *pTsi;
	if (data==NULL)				return -300;
	if (meta==NULL)				return -301;
	if (data->vui==NULL)		return -302;
	if (data->sei==NULL)		return -303;
	if (data->tsi==NULL)		return -304;

	pTsi = data->tsi;

	/*****************************************/
	/* fixed for v1300 */
	/*****************************************/
	//partID 1 : SDR2MDR (VUI transfer_characteristics = ITU-R BT.709)  bright = 1000
	//partID 2 : HDR2MDR (VUI transfer_characteristics = SMPTE ST-2084) bright = 100
	meta->partID = 1;
	meta->majorSpecVersionID = 0;
	meta->minorSpecVersionID = 0;
	/*****************************************/

	meta->payloadMode = pTsi->ts_103_433_payload_mode;
	if (pTsi->ts_103_433_payload_mode)
	{
		if (data->cri==NULL)	return -305;
		ret = KADP_PE_SL13_GetMetaOnPayloadMode1(data, meta);
		if (ret)	return ret;
	}
	else
	{
		if (data->cvri==NULL)	return -306;
		ret = KADP_PE_SL13_GetMetaOnPayloadMode0(data, meta);
		if (ret)	return ret;
	}
	return ret;
}
static int KADP_PE_SL_GetPrimeMeta(struct hdr_data *data, struct sl_hdr_metadata *meta)
{
	int ret = 0;
	//struct hdr_tsi *pTsi;//fix compile warning
	if (data==NULL)			return -200;
	if (meta==NULL)			return -201;
	if (data->vui==NULL)	return -202;
	if (data->sei==NULL)	return -203;

	if (data->sl_hdr!=NULL)
	{
		ret = KADP_PE_SL14_GetPrimeMeta(data, meta);
	}
	else if (data->tsi!=NULL)
	{
		ret = KADP_PE_SL13_GetPrimeMeta(data, meta);
	}
	else
	{
		return -204;
	}
	return ret;
}
int KADP_PE_SL_Init(void)
{
	int ret = RET_OK;
	#if 0	//legacy
	do {
		if (g_sl_init>0)		{PE_PRINT_NOTI("already init. (%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);break;}
		if (sl_shm_fd>0)		{PE_PRINT_NOTI("already open. (%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);break;}
		if (p_sl_shm!=NULL)		{PE_PRINT_NOTI("already mmap0.(%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);break;}
		if (sptr_sl_shm!=NULL)	{PE_PRINT_NOTI("already mmap1.(%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);break;}
		sl_shm_fd = shm_open(PE_KWRAP_HDR_SHARED_MEM,O_CREAT | O_RDWR,0666);
		PE_CHECK_CODE(sl_shm_fd < 0, ret=RET_ERROR;break, "Error: shm_open failed. %d %s\n",sl_shm_fd,strerror(errno));
		ftruncate(sl_shm_fd,sizeof(SL_HDR_SHM_MAP_T));
		p_sl_shm = (SL_HDR_SHM_MAP_T *)mmap (NULL, sizeof(SL_HDR_SHM_MAP_T), PROT_READ|PROT_WRITE, MAP_SHARED,	sl_shm_fd, 0);
		PE_CHECK_CODE(p_sl_shm==MAP_FAILED, ret=RET_ERROR;break, "Error: mmap failed. %s\n",strerror(errno));
		sptr_sl_shm = p_sl_shm;
		g_sl_init = 1;
		PE_PRINT_NOTI("done.(%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);
	} while(0);
	#endif
	return ret;
}
int KADP_PE_SL_UnInit(void)
{
	int ret = RET_OK;
	#if 0	//legacy
	do {
		if (sptr_sl_shm==NULL)	{PE_PRINT_NOTI("already munmap1.(%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);break;}
		if (p_sl_shm==NULL)		{PE_PRINT_NOTI("already munmap0.(%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);break;}
		if (sl_shm_fd<=0)		{PE_PRINT_NOTI("already close.  (%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);break;}
		if (g_sl_init<=0)		{PE_PRINT_NOTI("already uninit. (%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);break;}
		//memset(p_sl_shm,0,sizeof(SL_HDR_SHM_MAP_T));
		munmap(p_sl_shm,sizeof(SL_HDR_SHM_MAP_T));
		p_sl_shm = NULL;
		sptr_sl_shm = NULL;
		close(sl_shm_fd);
		sl_shm_fd = -1;
		g_sl_init = 0;
		PE_PRINT_NOTI("done.(%d,%d,%p,%p)\n",g_sl_init,sl_shm_fd,p_sl_shm,sptr_sl_shm);
	} while(0);
	#endif
	return ret;
}
int KADP_PE_HDR_GetPrimeLut(struct hdr_data *data, SL_HDR_PRIME_LUT_T *lut)
{
	int ret = 0;
	struct sl_hdr_metadata meta;
	do {
		PE_PRINT_PRIME9("S %d, %d,%d,%d,%d,%d|%d,%d,%d,%d,%d\n",g_sl_init,\
			sl_dbg_info[0],sl_dbg_info[1],sl_dbg_info[2],sl_dbg_info[3],sl_dbg_info[4],\
			sl_dbg_info[5],sl_dbg_info[6],sl_dbg_info[7],sl_dbg_info[8],sl_dbg_info[9]);
		//KADP_PE_SL_Init();
		if (g_sl_init<=0)	break;
		/* set cfg */
		do {
			if (sptr_sl_shm==NULL)		break;
			sl_dbg_level = sptr_sl_shm->data[0];
			sl_dbg_bright = (data->sl_hdr!=NULL)? sptr_sl_shm->data[1]:1000;
			sl_dbg_oetf = (data->sl_hdr!=NULL)? sptr_sl_shm->data[2]:PQ;
			if (sl_dbg_level!=0x200)	break;
			PE_PRINT_NOTI("shm : %x %d %d %d %d|%d %d %d %d %d\n", sptr_sl_shm->data[0], \
				sptr_sl_shm->data[1], sptr_sl_shm->data[2], sptr_sl_shm->data[3], \
				sptr_sl_shm->data[4], sptr_sl_shm->data[5], sptr_sl_shm->data[6], \
				sptr_sl_shm->data[7], sptr_sl_shm->data[8], sptr_sl_shm->data[9]);
		} while(0);
		/* get meta */
		ret = KADP_PE_SL_GetPrimeMeta(data, &meta);
		if (ret)	{PE_PRINT_ERROR("KADP_PE_SL_GetPrimeMeta() ERR:%d\n",ret);break;}
		/* get lut */
		ret = KADP_PE_SL_GetHdrPrimeLut(data, &meta, lut);
		if (ret)	{PE_PRINT_ERROR("KADP_PE_SL_GetHdrPrimeLut() ERR:%d\n",ret);break;}
		sl_dbg_info[0]++;
		//KADP_PE_SL_UnInit();
	} while(0);
    return ret;
}
#else
//-------------------------------------------------------------------------------------------------

void PrintUsage(char *argv[])
{
    printf("\nCommand line:\n");
    printf("%s <parameters_file> <display_OETF> <metadata> <Input YUV 420 file> <Input YUV 444 upsampled> <Output RGB file> <Output YUV 422 or 420 file> <Output RsGsBs file> <nb frame> <display_Brightness>\n", argv[0]);
}

//-------------------------------------------------------------------------------------------------

// Parse command line arguments
void parse_args(int argc,
                char *argv[],
                char **parameters_file_name,
                int *display_OETF,
                char **metadata_file_name,
                char **yuv_in_name,
                char **yuv444_in_name,
                char **rgb_out_name,
                char **yuv_out_name,
                char **rsgsbs_out_name,
                int *nb_frame,
                int *display_Brightness
)
{
    if (argc != 11)
    {
        PrintUsage(argv);
        exit(EXIT_FAILURE);
    }

    // Read command line parameters
    *parameters_file_name = argv[1];
    *display_OETF = atoi(argv[2]);
    *metadata_file_name = argv[3];
    *yuv_in_name = argv[4];
    *yuv444_in_name = argv[5];
    *rgb_out_name = argv[6];
    *yuv_out_name = argv[7];
    *rsgsbs_out_name = argv[8];
    *nb_frame = atoi(argv[9]);
    *display_Brightness = atoi(argv[10]);
}

//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // Main parameters
    int display_OETF, display_Brightness, display_Brightness_Max;
    int height;
    int width;
    int bit_depth;
    int yuv_range;
    char *rgb_out_name, *yuv_out_name;
    char *parameters_file_name;
    char *yuv_in_name, *yuv444_in_name;
    char *metadata_file_name;
    char *rsgsbs_out_name;
    int nb_frame;
    int colour_primaries, transfer_characteristics;
    struct sl_hdr_metadata sl_hdr_metadata;

    // UV2SRGB matrix
    int OCT[7];

    // RGB2YUV matrix (fixed)
    int RGBtoYUV_709[9] = { 186, 627, 63, -103, -346, 448, 448, -407, -41 };
    int RGBtoYUV_2020[9] = { 230, 595, 52, -125, -323, 448, 448, -412, -36 };
    int *RGBtoYUV;

    uint16_t *Y_pic;
    uint16_t *U_pic;
    uint16_t *V_pic;
    uint16_t *U_420_pic;
    uint16_t *V_420_pic;
    uint16_t *U_422_pic;
    uint16_t *V_422_pic;
    uint16_t *R_pic, *G_pic, *B_pic;
    uint16_t *Rs_pic, *Gs_pic, *Bs_pic;

    // LUTs pointers and variables
    uint16_t mu0, mu1;
    uint16_t C_LUT[65];
    uint16_t P_LUT[65];
    uint16_t S_LUT[65];
    uint16_t I_LUT[65];
    uint16_t D_LUT[65];
    uint16_t D_LUT_THRESHOLD[3];
    uint16_t D_LUT_STEP[4];
    int inv_y_ratio, inv_chroma_ratio, footroom, l_headroom, c_headroom;

    // Parse command line arguments
    parse_args(argc,
        argv,
        &parameters_file_name,
        &display_OETF,
        &metadata_file_name,
        &yuv_in_name,
        &yuv444_in_name,
        &rgb_out_name,
        &yuv_out_name,
        &rsgsbs_out_name,
        &nb_frame,
        &display_Brightness
    );

    if (display_Brightness != 100 &&
        display_Brightness != 150 &&
        display_Brightness != 250 &&
        display_Brightness != 400 &&
        display_Brightness != 550 &&
        display_Brightness != 700 &&
        display_Brightness != 850 &&
        display_Brightness != 1000 &&
        display_Brightness != 1250 &&
        display_Brightness != 1500 &&
        display_Brightness != 1750 &&
        display_Brightness != 2000 &&
        display_Brightness != 2500 &&
        display_Brightness != 3000 &&
        display_Brightness != 3500 &&
        display_Brightness != 4000 &&
        display_Brightness != 5000)
    {
        fprintf(stderr, "Bad input : display_Brightness must be equal to 100, 150, 250, 400, 550, 700, 850, 1000, 1250, 1500, 1750, 2000, 2500, 3000, 3500, 4000 or 5000\n");
        exit(EXIT_FAILURE);
    }

    // Open parameters file
    FILE *param_fp;

    if ((param_fp = fopen(parameters_file_name ,  "r")) == NULL)
    {
        fprintf(stderr, "Can not open file %s for input\n", parameters_file_name);
        exit(EXIT_FAILURE);
    }

    // Read parameters file
    read_parameter_file(param_fp, &width, &height, &bit_depth, &yuv_range);

    // Close parameters file
    fclose(param_fp);

    // Memory allocation, according to picture dimension
    Y_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));
    U_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));
    V_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));
    U_420_pic = (uint16_t *)malloc(width*height/4*sizeof(uint16_t));
    V_420_pic = (uint16_t *)malloc(width*height/4*sizeof(uint16_t));
    U_422_pic = (uint16_t *)malloc(width*height/2*sizeof(uint16_t));
    V_422_pic = (uint16_t *)malloc(width*height/2*sizeof(uint16_t));
    R_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));
    G_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));
    B_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));
    Rs_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));
    Gs_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));
    Bs_pic = (uint16_t *)malloc(width*height*sizeof(uint16_t));

    // Open input YUV 420 file
    FILE *yuv_in_fp;

    if ((yuv_in_fp = fopen(yuv_in_name, "rb")) == NULL)
    {
        fprintf(stderr, "Can not open file %s for input\n", yuv_in_name);
        exit(EXIT_FAILURE);
    }

    // Open upsampled YUV 444 file
    FILE *yuv444_in_fp;

    // Open input YUV file
    if ((yuv444_in_fp = fopen(yuv444_in_name, "wb")) == NULL)
    {
        fprintf(stderr, "Can not open file %s for input\n", yuv444_in_name);
        exit(EXIT_FAILURE);
    }

    // Open output video file
    FILE *rgb_out_fp, *yuv_out_fp;

    if ((rgb_out_fp = fopen(rgb_out_name, "wb")) == NULL)
    {
        fprintf(stderr, "Can not open file %s for output\n", rgb_out_name);
        exit(EXIT_FAILURE);
    }

    if ((yuv_out_fp = fopen(yuv_out_name, "wb")) == NULL)
    {
        fprintf(stderr, "Can not open file %s for output\n", yuv_out_name);
        exit(EXIT_FAILURE);
    }

    // Open output RsBsGs conformance file
    FILE *rsgsbs_out_fp;

    if ((rsgsbs_out_fp = fopen(rsgsbs_out_name, "wb")) == NULL)
    {
        fprintf(stderr, "Can not open file %s for output\n", rsgsbs_out_name);
        exit(EXIT_FAILURE);
    }

    // Open metadata file
    FILE *metadata_fp = NULL;

    if ((metadata_fp = fopen(metadata_file_name, "r")) == NULL)
        printf("Info: Cannot open file %s for input : recovery mode is applied\n", metadata_file_name);

    //--------------------------------------------------------------------------------
    //
    // Initialize metadata with recovery mode values
    //
    if (strstr(metadata_file_name, "709")) /* VUI colour_primaries = BT.709 */
      colour_primaries = 1;
    else /* VUI colour_primaries = BT.2020 */
      colour_primaries = 9;

    if (strstr(metadata_file_name, "hdr2mdr")) /* VUI transfer_characteristics = SMPTE ST-2084 */
      transfer_characteristics = 16;
    else /* VUI transfer_characteristics = ITU-R BT.709 or ITU-R BT.2020 */
      transfer_characteristics = (colour_primaries == 1) ? 1 : 14;

    Fill_MetadataRecovery(&sl_hdr_metadata, display_Brightness, colour_primaries, transfer_characteristics);

    //--------------------------------------------------------------------------------
    //
    // Preparation of "static" LUTs
    //
    Fill_S_LUT(S_LUT);
    Fill_I_LUT(I_LUT);

    //--------------------------------------------------------------------------------
    //
    // Loop for all frames
    int frame;
    for (frame = 0; frame < nb_frame; frame++)
    {
        printf("\nFrame %d\n", frame);

        // Read current YUV 4:2:0 frame
        read_yuv_file(yuv_in_fp, Y_pic, U_420_pic, V_420_pic, height, width);

        // Upsample the Chroma 420 to 444
        upsample_420to444(U_420_pic, V_420_pic, U_pic, V_pic, height, width, (1<<bit_depth)-1);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // 4:4:4  =  INPUT CONFORMANCE point
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        write_yuv_file(yuv444_in_fp, Y_pic, U_pic, V_pic, height, width, 1);

        // Read metadata
        if (metadata_fp)
          read_metadata_file(metadata_fp, &sl_hdr_metadata);

        display_Brightness_Max = sl_hdr_metadata.hdrDisplayMaxLuminance + ((sl_hdr_metadata.hdrDisplayMaxLuminance + 2) >> 2);


        if (display_Brightness > display_Brightness_Max)
        {
            fprintf(stderr, "Bad input : display_Brightness (%d) > display_Brightness_Max (%d)\n", display_Brightness, display_Brightness_Max);
            exit(EXIT_FAILURE);
        }

        // Compute LUTs
        Compute_LUTs(&sl_hdr_metadata, display_Brightness, yuv_range, &mu0, &mu1, OCT, C_LUT, P_LUT, &inv_y_ratio, &inv_chroma_ratio, &footroom, &l_headroom, &c_headroom);

        // Fill D_LUT
        Fill_D_LUT(&sl_hdr_metadata, display_OETF, display_Brightness, D_LUT, D_LUT_THRESHOLD, D_LUT_STEP);

        if (sl_hdr_metadata.hdrPicColourSpace == 0) // rec709
            RGBtoYUV = RGBtoYUV_709;
        else // rec2020
            RGBtoYUV = RGBtoYUV_2020;

        // Compute YUV to RGB : output is written in Y_pic, U_pic, V_pic input
        compute_HDRDecode(
            Y_pic,
            U_pic,
            V_pic,
            height,
            width,
            inv_y_ratio, inv_chroma_ratio, footroom, l_headroom, c_headroom,
            mu0,
            mu1,
            C_LUT,
            P_LUT,
            S_LUT,
            I_LUT,
            D_LUT,
            D_LUT_THRESHOLD,
            D_LUT_STEP,
            OCT,
            RGBtoYUV,
            R_pic,
            G_pic,
            B_pic,
            Rs_pic,
            Gs_pic,
            Bs_pic
        );

        write_rgb_file(rgb_out_fp, R_pic, G_pic, B_pic, height, width);

        if (strstr(yuv_out_name, "p422")) { // Downsample 444 to 422
            downsample_444to422(U_pic, V_pic, U_422_pic, V_422_pic, height, width, (1 << bit_depth)-1);
            // Write current output YUV frame
            write_yuv_file(yuv_out_fp, Y_pic, U_422_pic, V_422_pic, height, width, 2);
        }
        else if (strstr(yuv_out_name, "p420")) { // Downsample 444 to 420
            downsample_444to420(U_pic, V_pic, U_420_pic, V_420_pic, height, width, (1 << bit_depth)-1);
            // Write current output YUV frame
            write_yuv_file(yuv_out_fp, Y_pic, U_420_pic, V_420_pic, height, width, 4);
        }
        else {
            fprintf(stderr, "p422 or p420 must be specified in output YUV file\n");
            exit(EXIT_FAILURE);
        }

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // Write Conformance RsGsBs Output
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        write_int_file(rsgsbs_out_fp, Rs_pic, Gs_pic, Bs_pic, height, width);
    }

    // Close "video" files
    fclose(yuv_in_fp);
    fclose(yuv_out_fp);
    fclose(rgb_out_fp);

    // Close metadata files
    if (metadata_fp)
        fclose(metadata_fp);

    //memory desallocations
    free(Y_pic);
    free(U_pic);
    free(V_pic);
    free(U_420_pic);
    free(V_420_pic);
    free(U_422_pic);
    free(V_422_pic);
    free(R_pic);
    free(G_pic);
    free(B_pic);
    free(Rs_pic);
    free(Gs_pic);
    free(Bs_pic);

    return 0;
}
#endif

