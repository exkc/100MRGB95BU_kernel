/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_cmn_hw_o24.c
 *
 *  driver for picture enhance common functions. ( used only within kdriver )
 *
 *	@author			Seung-Jun,Youm(sj.youm@lge.com)
 *  @modifier		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *	@version		0.1
 *	@note
 *	@date			2012.04.12
 *  @modified date  2015.05.24 for SWMD
 *	@see
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_hw_o24.h"
#include "pe_reg_o24.h"
#include "pe_fwi_o24.h"
#include "pe_inf_o24.h"
#include "pe_cmn_hw_o24.h"
#include "pe_dcm_hw_o24.h"
#include "pe_shp_hw_o24.h"
#include "pe_nrd_hw_o24.h"
#include "pe_hst_hw_o24.h"
#ifdef INCLUDE_KDRV_AFE
#include "cvd_module.h"
#endif

#include "pe_lgsr_dnsr_coeff_set_o24.h"
//#include "pe_lgsr_dnsr_coeff_set_o24n.h"
#include "pe_lgsr_dnnr_coeff_set_o24.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#if (CONFIG_LX_O24_CHIP_FIRMWARE == 1) 
#define PE_FWI_O24_LGSR_DNSR_COEFF_NUM 290304
#define PE_FWI_O24_LGSR_DNNR_COEFF_NUM 206080
#define PE_FWI_O24_LGSR_SRMR_COEFF_NUM 5152
#define PE_FWI_O24_LGSR_DNSR_SIZE (sizeof(UINT32)*PE_FWI_O24_LGSR_DNSR_COEFF_NUM)
#define PE_FWI_O24_LGSR_DNNR_SIZE (sizeof(UINT32)*PE_FWI_O24_LGSR_DNNR_COEFF_NUM)
#define PE_FWI_O24_LGSR_SRMR_SIZE (sizeof(UINT32)*PE_FWI_O24_LGSR_SRMR_COEFF_NUM)
#endif
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMN_HW_O24_CHECK_CODE(_checker,_action,fmt,args...)	\
	if(_checker){PE_PRINT_ERROR(fmt,##args);_action;}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T gPeMem[10];//[0]:fw_dnn, [1~9]:none

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
const UINT32 g_pe_cmn_hw_o24_crc_table[256] = {
	0x00000000,    //000
	0x04C11DB7,    //001
	0x09823B6E,    //002
	0x0D4326D9,    //003
	0x130476DC,    //004
	0x17C56B6B,    //005
	0x1A864DB2,    //006
	0x1E475005,    //007
	0x2608EDB8,    //008
	0x22C9F00F,    //009
	0x2F8AD6D6,    //010
	0x2B4BCB61,    //011
	0x350C9B64,    //012
	0x31CD86D3,    //013
	0x3C8EA00A,    //014
	0x384FBDBD,    //015
	0x4C11DB70,    //016
	0x48D0C6C7,    //017
	0x4593E01E,    //018
	0x4152FDA9,    //019
	0x5F15ADAC,    //020
	0x5BD4B01B,    //021
	0x569796C2,    //022
	0x52568B75,    //023
	0x6A1936C8,    //024
	0x6ED82B7F,    //025
	0x639B0DA6,    //026
	0x675A1011,    //027
	0x791D4014,    //028
	0x7DDC5DA3,    //029
	0x709F7B7A,    //030
	0x745E66CD,    //031
	0x9823B6E0,    //032
	0x9CE2AB57,    //033
	0x91A18D8E,    //034
	0x95609039,    //035
	0x8B27C03C,    //036
	0x8FE6DD8B,    //037
	0x82A5FB52,    //038
	0x8664E6E5,    //039
	0xBE2B5B58,    //040
	0xBAEA46EF,    //041
	0xB7A96036,    //042
	0xB3687D81,    //043
	0xAD2F2D84,    //044
	0xA9EE3033,    //045
	0xA4AD16EA,    //046
	0xA06C0B5D,    //047
	0xD4326D90,    //048
	0xD0F37027,    //049
	0xDDB056FE,    //050
	0xD9714B49,    //051
	0xC7361B4C,    //052
	0xC3F706FB,    //053
	0xCEB42022,    //054
	0xCA753D95,    //055
	0xF23A8028,    //056
	0xF6FB9D9F,    //057
	0xFBB8BB46,    //058
	0xFF79A6F1,    //059
	0xE13EF6F4,    //060
	0xE5FFEB43,    //061
	0xE8BCCD9A,    //062
	0xEC7DD02D,    //063
	0x34867077,    //064
	0x30476DC0,    //065
	0x3D044B19,    //066
	0x39C556AE,    //067
	0x278206AB,    //068
	0x23431B1C,    //069
	0x2E003DC5,    //070
	0x2AC12072,    //071
	0x128E9DCF,    //072
	0x164F8078,    //073
	0x1B0CA6A1,    //074
	0x1FCDBB16,    //075
	0x018AEB13,    //076
	0x054BF6A4,    //077
	0x0808D07D,    //078
	0x0CC9CDCA,    //079
	0x7897AB07,    //080
	0x7C56B6B0,    //081
	0x71159069,    //082
	0x75D48DDE,    //083
	0x6B93DDDB,    //084
	0x6F52C06C,    //085
	0x6211E6B5,    //086
	0x66D0FB02,    //087
	0x5E9F46BF,    //088
	0x5A5E5B08,    //089
	0x571D7DD1,    //090
	0x53DC6066,    //091
	0x4D9B3063,    //092
	0x495A2DD4,    //093
	0x44190B0D,    //094
	0x40D816BA,    //095
	0xACA5C697,    //096
	0xA864DB20,    //097
	0xA527FDF9,    //098
	0xA1E6E04E,    //099
	0xBFA1B04B,    //100
	0xBB60ADFC,    //101
	0xB6238B25,    //102
	0xB2E29692,    //103
	0x8AAD2B2F,    //104
	0x8E6C3698,    //105
	0x832F1041,    //106
	0x87EE0DF6,    //107
	0x99A95DF3,    //108
	0x9D684044,    //109
	0x902B669D,    //110
	0x94EA7B2A,    //111
	0xE0B41DE7,    //112
	0xE4750050,    //113
	0xE9362689,    //114
	0xEDF73B3E,    //115
	0xF3B06B3B,    //116
	0xF771768C,    //117
	0xFA325055,    //118
	0xFEF34DE2,    //119
	0xC6BCF05F,    //120
	0xC27DEDE8,    //121
	0xCF3ECB31,    //122
	0xCBFFD686,    //123
	0xD5B88683,    //124
	0xD1799B34,    //125
	0xDC3ABDED,    //126
	0xD8FBA05A,    //127
	0x690CE0EE,    //128
	0x6DCDFD59,    //129
	0x608EDB80,    //130
	0x644FC637,    //131
	0x7A089632,    //132
	0x7EC98B85,    //133
	0x738AAD5C,    //134
	0x774BB0EB,    //135
	0x4F040D56,    //136
	0x4BC510E1,    //137
	0x46863638,    //138
	0x42472B8F,    //139
	0x5C007B8A,    //140
	0x58C1663D,    //141
	0x558240E4,    //142
	0x51435D53,    //143
	0x251D3B9E,    //144
	0x21DC2629,    //145
	0x2C9F00F0,    //146
	0x285E1D47,    //147
	0x36194D42,    //148
	0x32D850F5,    //149
	0x3F9B762C,    //150
	0x3B5A6B9B,    //151
	0x0315D626,    //152
	0x07D4CB91,    //153
	0x0A97ED48,    //154
	0x0E56F0FF,    //155
	0x1011A0FA,    //156
	0x14D0BD4D,    //157
	0x19939B94,    //158
	0x1D528623,    //159
	0xF12F560E,    //160
	0xF5EE4BB9,    //161
	0xF8AD6D60,    //162
	0xFC6C70D7,    //163
	0xE22B20D2,    //164
	0xE6EA3D65,    //165
	0xEBA91BBC,    //166
	0xEF68060B,    //167
	0xD727BBB6,    //168
	0xD3E6A601,    //169
	0xDEA580D8,    //170
	0xDA649D6F,    //171
	0xC423CD6A,    //172
	0xC0E2D0DD,    //173
	0xCDA1F604,    //174
	0xC960EBB3,    //175
	0xBD3E8D7E,    //176
	0xB9FF90C9,    //177
	0xB4BCB610,    //178
	0xB07DABA7,    //179
	0xAE3AFBA2,    //180
	0xAAFBE615,    //181
	0xA7B8C0CC,    //182
	0xA379DD7B,    //183
	0x9B3660C6,    //184
	0x9FF77D71,    //185
	0x92B45BA8,    //186
	0x9675461F,    //187
	0x8832161A,    //188
	0x8CF30BAD,    //189
	0x81B02D74,    //190
	0x857130C3,    //191
	0x5D8A9099,    //192
	0x594B8D2E,    //193
	0x5408ABF7,    //194
	0x50C9B640,    //195
	0x4E8EE645,    //196
	0x4A4FFBF2,    //197
	0x470CDD2B,    //198
	0x43CDC09C,    //199
	0x7B827D21,    //200
	0x7F436096,    //201
	0x7200464F,    //202
	0x76C15BF8,    //203
	0x68860BFD,    //204
	0x6C47164A,    //205
	0x61043093,    //206
	0x65C52D24,    //207
	0x119B4BE9,    //208
	0x155A565E,    //209
	0x18197087,    //210
	0x1CD86D30,    //211
	0x029F3D35,    //212
	0x065E2082,    //213
	0x0B1D065B,    //214
	0x0FDC1BEC,    //215
	0x3793A651,    //216
	0x3352BBE6,    //217
	0x3E119D3F,    //218
	0x3AD08088,    //219
	0x2497D08D,    //220
	0x2056CD3A,    //221
	0x2D15EBE3,    //222
	0x29D4F654,    //223
	0xC5A92679,    //224
	0xC1683BCE,    //225
	0xCC2B1D17,    //226
	0xC8EA00A0,    //227
	0xD6AD50A5,    //228
	0xD26C4D12,    //229
	0xDF2F6BCB,    //230
	0xDBEE767C,    //231
	0xE3A1CBC1,    //232
	0xE760D676,    //233
	0xEA23F0AF,    //234
	0xEEE2ED18,    //235
	0xF0A5BD1D,    //236
	0xF464A0AA,    //237
	0xF9278673,    //238
	0xFDE69BC4,    //239
	0x89B8FD09,    //240
	0x8D79E0BE,    //241
	0x803AC667,    //242
	0x84FBDBD0,    //243
	0x9ABC8BD5,    //244
	0x9E7D9662,    //245
	0x933EB0BB,    //246
	0x97FFAD0C,    //247
	0xAFB010B1,    //248
	0xAB710D06,    //249
	0xA6322BDF,    //250
	0xA2F33668,    //251
	0xBCB4666D,    //252
	0xB8757BDA,    //253
	0xB5365D03,    //254
	0xB1F740B4,    //255
};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int PE_CMN_HW_O24_DownloadModeDb(void);
static int PE_CMN_HW_O24_DownloadCvdDb(void);
static int PE_CMN_HW_O24_InitChipInfo(PE_CFG_CTRL_T *pstParams);
__attribute__((unused)) static int PE_CMN_HW_O24F22_DownloadDb(PE_CFG_CTRL_T *pstParams);
__attribute__((unused)) static int PE_CMN_HW_O24F22_DownloadModeDb(void);
static int PE_CMN_HW_O24_LGSR_DownloadDb(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_cmn_hw_o24_trace=0x0;		//default should be off.
static PE_CMN_HW_O24_SETTINGS_T _g_pe_cmn_hw_o24_info;

/*========================================================================================
	Implementation Group
========================================================================================*/
/**
 * init cmn
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		memset(&_g_pe_cmn_hw_o24_info, 0, sizeof(PE_CMN_HW_O24_SETTINGS_T));
		/* O24F22_APB : InitChipInfo should be on the top of pe_init */
		ret = PE_CMN_HW_O24_InitChipInfo(pstParams);
		PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_CMN_HW_O24_InitChipInfo() error.\n");
		/**********************************************************/
		PE_PRINT_NOTI("vsp-yc,rgb, lvctrl : enable\n");

		PE_IMX_O24_RdFL(ctrl_m0_y_level_ctrl);
		PE_IMX_O24_Wr01(ctrl_m0_y_level_ctrl,reg_lvctrl_en,0x1);
		PE_IMX_O24_Wr01(ctrl_m0_y_level_ctrl,level_offset,0x200);
		PE_IMX_O24_Wr01(ctrl_m0_y_level_ctrl,level_center,0x80);
		PE_IMX_O24_Wr01(ctrl_m0_y_level_ctrl,level_gain,0x80);
		PE_IMX_O24_WrFL(ctrl_m0_y_level_ctrl);

		PE_ND0_O24_QWr04(lvcrtl_ctrl_00,     enable,             0x1, \
												y_offset,           0x200, \
												center_position,    0x80, \
												y_gain,             0x80);
		/* vspyc center_position 0x0->0x10(related with 16~235 range) */
		PE_CC2_PE1_O24_QWr05(pe1_vspyc_ctrl_00,		enable,            0x1, \
													graycolor_enable,  0x0, \
													color_only_enable, 0x0, \
													center_position,   0x10, \
													contrast,          0x800);
		PE_CC2_PE1_O24_QWr02(pe1_vspyc_ctrl_01,		saturation,        0x80,\
													brightness,        0x200);
		PE_CC_PE1_O24_QWr01(pe1_cen_ctrl_02,  ihsv_vgain,        0x80);
		PE_CC_PE1_O24_QWr02(pe1_cen_ctrl_03,  ihsv_voffset,      0x80, \
													ihsv_hoffset,      0x80);
		/*init dummy reg to set brightness, contrast by output csc*/
		PE_CCO_VERI_O24_QWr02(contast_brightness_db, brightness, 0x200,\
													 contrast, 0x200);
		/*init vcp_vsp for blacklevel setting */
		PE_VCP_DISP_O24_QWr03(vcp_vsp_u0_ctrl_00,	enable, 		 0x1,\
													center_position, 0x0,\
													contrast,		 0x200);
		PE_VCP_DISP_O24_QWr02(vcp_vsp_u0_ctrl_01,	saturation, 	 0x80,\
													brightness, 	 0x200);
		PE_VSD0_VERI_O24_QWr03(vsd_veri_vsp0_0, 	enable, 		 0x1,\
													center_position, 0x0,\
													contrast,		 0x200);
		PE_VSD0_VERI_O24_QWr02(vsd_veri_vsp0_1, 	saturation, 	 0x80,\
													brightness, 	 0x200);
		PE_VSD0_VERI_O24_QWr02(vsd_veri_vsp1_0, 	brightness, 	 0x200,\
													contrast,		 0x200);
		PE_VSD0_VERI_O24_QWr02(vsd_veri_vsp1_1, 	saturation, 	 0x80,\
													brightness, 	 0x200);
		#if 0	/* O24F22_APB */
		do {
			if (pstParams->resume_mode == 1)	break;//if qsm,skip
			if (!gPE_CHPI_DDR_O24)	break;

			/* addr */
			PE_CHPI_APB0_O24F22_QWr(cmn0.cco_veri_sys_veri_8.uaddr32,0xF4060320);//cco0 veri SYS_VERI_8
			PE_CHPI_APB0_O24F22_QWr(cmn0.pe1_vspyc_ctrl_01.uaddr32,0xF4061004);
			PE_CHPI_APB0_O24F22_QWr(cmn0.pe1_cen_ctrl_03.uaddr32,  0xF40606DC);

			/* init */
			#if 0
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_00.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_00.enable,1);
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_00.r_yc2rgb_en,1);
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_00.center_position,0x10);
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_00.contrast,0x200);
			PE_CHPI_APB0_O24F22_WrFL(cmn0.pe1_vspyc_ctrl_00.udata32);
			#else
			PE_CHPI_APB0_O24F22_Wr(cmn0.cco_veri_sys_veri_8.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(cmn0.cco_veri_sys_veri_8.brightness,0x200);
			PE_CHPI_APB0_O24F22_Wr(cmn0.cco_veri_sys_veri_8.contrast,0x200);
			PE_CHPI_APB0_O24F22_WrFL(cmn0.cco_veri_sys_veri_8.udata32);
			#endif
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_01.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_01.saturation_target,0x80);
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_01.saturation,0x80);
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_01.brightness,0x200);
			PE_CHPI_APB0_O24F22_WrFL(cmn0.pe1_vspyc_ctrl_01.udata32);
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_cen_ctrl_03.udata32,0x0);//should set zero firstly(init)(bit settings)
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_cen_ctrl_03.ihsv_hoffset,0x80);
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_cen_ctrl_03.ihsv_soffset,0x80);
			PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_cen_ctrl_03.ihsv_voffset,0x80);
			PE_CHPI_APB0_O24F22_WrFL(cmn0.pe1_cen_ctrl_03.udata32);

			/* header */
			PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_CMN0);

			PE_INF_HW_O24_BACKUP_CHPI0("[APB][CMN]done(resume:%d)",pstParams->resume_mode);
		} while(0);
		#endif
		#if 0	/* O24F22_TBL */
		do {
			if (pstParams->resume_mode == 1)	break;//if qsm,skip
			if (!gPE_CHPI_DDR_O24)	break;

			/* addr */
			PE_CHPI_TBL0_O24F22_QWr(cco.pe1_dce_ctrl_00.uaddr32,0xF4060720);
			PE_CHPI_TBL0_O24F22_QWr(cco.pe1_dse_ctrl_00.uaddr32,0xF4060770);

			/* init */
			PE_CHPI_TBL0_O24F22_QWr(cco.pe1_dce_ctrl_00.udata32,0x050000A1);
			PE_CHPI_TBL0_O24F22_QWr(cco.pe1_dse_ctrl_00.udata32,0x000000A3);

			/* count */
			PE_INF_O24_IncChipInfoTblCount(PE_INF_O24_CHPI_TBL_CCO);

			PE_INF_HW_O24_BACKUP_CHPI1("[TBL][CCO]done(resume:%d)",pstParams->resume_mode);
		} while(0);
		#endif
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	PE_PRINT_NOTI("done\n");
	return ret;
}

/**
 * get mem info
 *
 * @param   *base [in] unsigned int
 * @param   *size [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_GetMemInfo(unsigned int *base, unsigned int *size)
{
	int ret = RET_OK;
#ifdef INCLUDE_KDRV_DE
	do {
		CHECK_KNULL(base);
		CHECK_KNULL(size);
		*base = PE_O24_DDR_DB_BASE;
		*size = PE_O24_DDR_DB_SIZE;
		PE_PRINT_NOTI("base:%08x, size:%d\n", *base, *size);
	} while(0);
#endif
	return ret;
}
/**
 * set cmn debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmn_hw_o24_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CMN)))? 0x1:0x0;
		}
		PE_PRINT_NOTI("wid:%d,type:0x%x,[0x%x]print:0x%x(%d),bypass:0x%x,fwc_en,dbg:%d,%d\n",\
			pstParams->win_id,pstParams->type,(0x1<<PE_ITEM_PKTMODL(CMN)),\
			pstParams->print_lvl,_g_cmn_hw_o24_trace,pstParams->bypass,\
			pstParams->fwc.ctrl_en,pstParams->fwc.dbg_en);
	} while(0);
	return ret;
}

/**
 * set contrast
 *
 * @param   *pstParams [in] LX_PE_CMN_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetContrast(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do {
		LX_PE_CMN1_CONTRAST_T *pp = (LX_PE_CMN1_CONTRAST_T *)pstParams;
		__attribute__((unused)) PE_REG_O24_HW_OPT_T hw_opt = PE_REG_O24_GetDispOpt();
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_DBG_CMN("set pstParams[%d] : %d\n",pp->win_id,pp->contrast);

		if(PE_CHECK_WIN0(pp->win_id))
		{
			if(pp->setbycsc)/* set brightness, contrast by output csc*/
			{
				//PE_CC2_PE1_O24_QWr01(pe1_vspyc_ctrl_00, contrast,0x200 );
				if (hw_opt.external_chip==0)// O24 onechip model
				{
					PE_CCO_VERI_O24_QWr01(contast_brightness_db, contrast, GET_BITS(pp->contrast,0,12));
				}
			}
			else
			{
				PE_CC2_PE1_O24_QWr01(pe1_vspyc_ctrl_00, contrast, GET_BITS(pp->contrast,0,12));
				PE_CCO_VERI_O24_QWr01(contast_brightness_db, contrast, 0x200);
			}
			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;
				PE_CHPI_APB0_O24F22_Wr(cmn0.cco_veri_sys_veri_8.contrast,GET_BITS(pp->contrast,0,10));
				PE_CHPI_APB0_O24F22_WrFL(cmn0.cco_veri_sys_veri_8.udata32);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_CMN0);
				PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
					PE_CHPI_APB0_O24F22_Rd(cmn0.cco_veri_sys_veri_8.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.cco_veri_sys_veri_8.udata32),\
					PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
					PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_cen_ctrl_03.udata32));
			} while(0);
			#endif
		}
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * get contrast
 *
 * @param   *pstParams [in/out] LX_PE_CMN_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_GetContrast(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		LX_PE_CMN1_CONTRAST_T *pp = (LX_PE_CMN1_CONTRAST_T *)pstParams;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		win_id = PE_GET_CHECKED_WINID(pp->win_id);

		if(PE_CHECK_WIN0(win_id))
		{
			PE_CC2_PE1_O24_QRd01(pe1_vspyc_ctrl_00, contrast, pp->contrast);
		}
		/*if(PE_CHECK_WIN1(win_id))
		{
			PE_CO_PE1_O24_QRd01(pe1_vspyc_ctrl_00, contrast, pp->contrast);
		}*/

		PE_DBG_CMN("get pstParams[%d] : %d\n",pp->win_id,pp->contrast);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * set brightness
 *
 * @param   *pstParams [in] LX_PE_CMN_BRIGHTNESS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetBrightness(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do {
		LX_PE_CMN1_BRIGHTNESS_T *pp = (LX_PE_CMN1_BRIGHTNESS_T *)pstParams;
		__attribute__((unused)) PE_REG_O24_HW_OPT_T hw_opt = PE_REG_O24_GetDispOpt();
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_DBG_CMN("set pstParams[%d] : %d\n",pp->win_id,pp->brightness);

		if(PE_CHECK_WIN0(pp->win_id))
		{
			if(pp->setbycsc)/* set brightness, contrast by output csc*/
			{
				//PE_CC2_PE1_O24_QWr01(pe1_vspyc_ctrl_01, brightness,0x200 );
				if (hw_opt.external_chip==0)// O24 onechip model
				{
					PE_CCO_VERI_O24_QWr01(contast_brightness_db, brightness, GET_BITS(pp->brightness,0,10));
				}
			}
			else
			{
				PE_CC2_PE1_O24_QWr01(pe1_vspyc_ctrl_01, brightness, GET_BITS(pp->brightness,0,10));
				PE_CCO_VERI_O24_QWr01(contast_brightness_db, brightness, 0x200);
			}
			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;
				PE_CHPI_APB0_O24F22_Wr(cmn0.cco_veri_sys_veri_8.brightness,GET_BITS(pp->brightness,0,10));
				PE_CHPI_APB0_O24F22_WrFL(cmn0.cco_veri_sys_veri_8.udata32);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_CMN0);
				PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
					PE_CHPI_APB0_O24F22_Rd(cmn0.cco_veri_sys_veri_8.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.cco_veri_sys_veri_8.udata32),\
					PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
					PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_cen_ctrl_03.udata32));
			} while(0);
			#endif
		}
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * get brightness
 *
 * @param   *pstParams [in/out] LX_PE_CMN_BRIGHTNESS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_GetBrightness(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		LX_PE_CMN1_BRIGHTNESS_T *pp = (LX_PE_CMN1_BRIGHTNESS_T *)pstParams;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		win_id = PE_GET_CHECKED_WINID(pp->win_id);

		if(PE_CHECK_WIN0(win_id))
		{
			PE_CC2_PE1_O24_QRd01(pe1_vspyc_ctrl_01, brightness, pp->brightness);
		}
		/*if(PE_CHECK_WIN1(win_id))
		{
			PE_CO_PE1_O24_QRd01(pe1_vspyc_ctrl_01, brightness, pstParams->brightness);
		}*/

		PE_DBG_CMN("get pstParams[%d] : %d\n",pp->win_id,pp->brightness);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * set saturation
 *
 * @param   *pstParams [in] LX_PE_CMN_SATURATION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DBG_CMN("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->saturation);

		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			PE_CC2_PE1_O24_QWr01(pe1_vspyc_ctrl_01, saturation, GET_BITS(pstParams->saturation,0,8));
			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;
				PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_vspyc_ctrl_01.saturation,GET_BITS(pstParams->saturation,0,8));
				PE_CHPI_APB0_O24F22_WrFL(cmn0.pe1_vspyc_ctrl_01.udata32);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_CMN0);
				PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
					PE_CHPI_APB0_O24F22_Rd(cmn0.cco_veri_sys_veri_8.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.cco_veri_sys_veri_8.udata32),\
					PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
					PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_cen_ctrl_03.udata32));
			} while(0);
			#endif
		}
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * get saturation
 *
 * @param   *pstParams [in/out] LX_PE_CMN_SATURATION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_GetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_CHECK_WIN0(win_id))
		{
			PE_CC2_PE1_O24_QRd01(pe1_vspyc_ctrl_01, saturation, pstParams->saturation);
		}
		/*if(PE_CHECK_WIN1(win_id))
		{
			PE_CO_PE1_O24_QRd01(pe1_vspyc_ctrl_01, saturation, pstParams->saturation);
		}*/

		PE_DBG_CMN("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->saturation);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * set hue
 *
 * @param   *pstParams [in] LX_PE_CMN_HUE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_DBG_CMN("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->hue);

		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			PE_CC_PE1_O24_QWr01(pe1_cen_ctrl_03, ihsv_hoffset, GET_BITS(pstParams->hue,0,8));
			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;
				PE_CHPI_APB0_O24F22_Wr(cmn0.pe1_cen_ctrl_03.ihsv_hoffset,GET_BITS(pstParams->hue,0,8));
				PE_CHPI_APB0_O24F22_WrFL(cmn0.pe1_cen_ctrl_03.udata32);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_CMN0);
				PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
					PE_CHPI_APB0_O24F22_Rd(cmn0.cco_veri_sys_veri_8.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.cco_veri_sys_veri_8.udata32),\
					PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
					PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_O24F22_Rd(cmn0.pe1_cen_ctrl_03.udata32));
			} while(0);
			#endif
		}
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * get hue
 *
 * @param   *pstParams [in/out] LX_PE_CMN_HUE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_GetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_CHECK_WIN0(win_id))
		{
			PE_CC_PE1_O24_QRd01(pe1_cen_ctrl_03, ihsv_hoffset, pstParams->hue);
		}
		/*if(PE_CHECK_WIN1(win_id))
		{
			PE_CO_PE1_O24_QRd01(pe1_cen_ctrl_03, ihsv_hoffset, pstParams->hue);
		}*/

		PE_DBG_CMN("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->hue);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * set level control
 *
 * @param   *pstParams [in] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	do {
		LX_PE_CMN_LEVEL_CTRL_T *pp = (LX_PE_CMN_LEVEL_CTRL_T *)pstParams;
		static LX_PE_CMN_LEVEL_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMN_LEVEL_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMN("duplicated DB : LX_PE_CMN_LEVEL_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_CMN("set pstParams[%d] : ofs:%d, center:%d, gain:%d, tp:%d\n",\
			pstParams->win_id,pstParams->offset,pstParams->center,\
			pstParams->gain,pstParams->tp_on);

		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			PE_IMX_O24_RdFL(ctrl_m0_y_level_ctrl);
			PE_IMX_O24_Wr01(ctrl_m0_y_level_ctrl,reg_lvctrl_en,0x1);
			PE_IMX_O24_Wr01(ctrl_m0_y_level_ctrl,level_offset,GET_BITS(pstParams->offset,0,10));
			PE_IMX_O24_Wr01(ctrl_m0_y_level_ctrl,level_center,GET_BITS(pstParams->center,0,8));
			PE_IMX_O24_Wr01(ctrl_m0_y_level_ctrl,level_gain,GET_BITS(pstParams->gain,0,8));
			PE_IMX_O24_WrFL(ctrl_m0_y_level_ctrl);
		}

	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * get level control
 *
 * @param   *pstParams [in/out] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_GetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_CHECK_WIN0(win_id))
		{
			PE_ND0_O24_QRd03(lvcrtl_ctrl_00, y_offset,        pstParams->offset,\
													center_position, pstParams->center,\
													y_gain,          pstParams->gain);
			PE_CC2_PE1_O24_QRd01(pe1_vspyc_ctrl_00,graycolor_enable,pstParams->tp_on);
		}
		PE_DBG_CMN("get pstParams[%d] : ofs:%d, center:%d, gain:%d, tp:%d\n",\
			pstParams->win_id,pstParams->offset,pstParams->center,pstParams->gain,pstParams->tp_on);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}

/**
 * download db
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_DownloadDb(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	PE_CFG_CTRL_T stParams;
	PE_DDR_O24_MD0_T *p_md0;
	PE_CMN_HW_O24_SETTINGS_T *p_inf = &_g_pe_cmn_hw_o24_info;
	PE_DDR_DB_SHDW_REG_O24_T *p_shdw_db = NULL;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O24_T *p_phys_db = NULL;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O24_T *p_phys_db_chk = NULL;
	//__attribute__((unused)) volatile PE_LGSR_DDR_DB_PHYS_REG_O24_T *p_phys_lgsrdb_chk = NULL;
	p_shdw_db = gPE_DDR_DB_O24.shdw.data;
	p_phys_db = gPE_DDR_DB_O24.phys.data;
	do {
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);

		PE_PRINT_NOTI("DL db start(resume:%d,init:%d).\n",pstParams->resume_mode,p_inf->db_initialized);
		stParams.resume_mode = pstParams->resume_mode;
		if (stParams.resume_mode > 0)
		{
			if (stParams.resume_mode == 2)//snapshot
			{
				p_inf->db_initialized = 0;
				stParams.resume_mode = 0;//force normal
			}
			else//instant
			{
				rmb();
				p_phys_db_chk = (volatile PE_DDR_DB_PHYS_REG_O24_T *)gPE_DDR_DB_O24.phys.data;
				if (p_phys_db_chk->top_h.version != PE_DDR_O24_DB_VER || \
					p_phys_db_chk->top_h.db_base != PE_O24_DDR_DB0_BASE || \
					p_phys_db_chk->top_h.sec_num != PE_DDR_O24_SEC_NUM)
				{
					p_inf->db_initialized = 0;
					stParams.resume_mode = 0;//force normal
				}
				rmb();
			}
		}
		PE_PRINT_NOTI("[CMNDb]check(resume:%d <- %d,init:%d).\n",stParams.resume_mode,pstParams->resume_mode,p_inf->db_initialized);
		PE_INF_HW_O24_BACKUP_TRACE("[CMNDb]check(resume:%d <- %d,init:%d)",stParams.resume_mode,pstParams->resume_mode,p_inf->db_initialized);
		if (!p_inf->db_initialized)
		{
			/* move db mode setting here to avoid db mode clear on resume init */
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			p_md0->shp_fw_en = 0;
			#ifdef PE_HW_O24_USE_FW_SRC_APL
			p_md0->hst_fw_en = 1;
			#else
			p_md0->hst_fw_en = 0;
			#endif
			p_md0->scl_fw_en = 1;
			p_md0->tnr_fw_en = 1;
			p_md0->dnr_fw_en = 0;
			if (!stParams.resume_mode)
			{
				p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_DDR_O24_DB_VER;
				p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_O24_DDR_DB0_BASE;
				p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_DDR_O24_SEC_NUM;
				/* *********************************************************************/
				/* Causion : Should be arranged in enum order **************************/
				/* *********************************************************************/
				/* mode : PE_DDR_O24_SEC_MODE(should be 1st one) */
				ret = PE_CMN_HW_O24_DownloadModeDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_CMN_HW_O24_DownloadModeDb() error.\n");
				/* drc : PE_DDR_O24_SEC_DRC_LUT */
				ret = PE_DCM_HW_O24_DownloadDrcDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_DCM_HW_O24_DownloadDrcDb() error.\n");
				/* cvd : PE_DDR_O24_SEC_CVD_DFLT */
				ret = PE_CMN_HW_O24_DownloadCvdDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_CMN_HW_O24_DownloadCvdDb() error.\n");
				/* scl : PE_DDR_O24_SEC_SCL_06T_M ~ PE_DDR_O24_SEC_SCL_04T_M */
				ret = PE_SHP_HW_O24_DownloadSclDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_SHP_HW_O24_DownloadSclDb() error.\n");
				/* tnr : PE_DDR_O24_SEC_TNR_LUT ~ PE_DDR_O24_SEC_TNR_USER */
				ret = PE_NRD_HW_O24_DownloadTnrDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadTnrDb() error.\n");
				ret = PE_DCM_HW_O24_DownloadDrcCurvDbInit();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_DCM_HW_O24_DownloadDrcCurvDbInit() error.\n");
				ret = PE_NRD_HW_O24_DownloadTnr2ndDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadTnr2ndUserDb() error.\n");
				#if 1
				/* dnr : PE_DDR_O24_SEC_DNR_USER  */
				ret = PE_NRD_HW_O24_DownloadDnrInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadDnrInitDb() error.\n");
				/* nrd dcnt : PE_DDR_O24_SEC_DNR_DCNT_USER  */
				ret = PE_NRD_HW_O24_DownloadDnrDcntInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadDcntInitDb() error.\n");
				/* nrd dcnt : PE_DDR_O24_SEC_LED_DCNT_USER  */
				ret = PE_NRD_HW_O24_DownloadCCODcntInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadCCODcntInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_TNR_SQM  */
				ret = PE_NRD_HW_O24_DownloadTnrSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadDnrInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_TNR2ND_SQM  */
				ret = PE_NRD_HW_O24_DownloadTnr2ndSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadDnrInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_DNR_SQM  */
				ret = PE_NRD_HW_O24_DownloadDnrSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadDnrInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_DNR_DCNT_SQM  */
				ret = PE_NRD_HW_O24_DownloadDnrDcntSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadDnrInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_SHP_UI_SQM_2K  */
				ret = PE_SHP_HW_O24_DownloadShp2KSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_SHP_HW_O24_DownloadShp2KSqmCmnInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_SHP_SQM_CMN_2K  */
				ret = PE_SHP_HW_O24_DownloadShp2KSqmDetailInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_SHP_HW_O24_DownloadShp2KSqmDetailInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_SHP_UI_SQM_VSD  */
				ret = PE_SHP_HW_O24_DownloadShpSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_SHP_HW_O24_DownloadShpSqmCmnInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_SHP_SQM_CMN_VSD  */
				ret = PE_SHP_HW_O24_DownloadShpSqmDetailInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_SHP_HW_O24_DownloadShpSqmDetailInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_CCO_DCNT_SQM  */
				ret = PE_NRD_HW_O24_DownloadCCODcntSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24_DownloadCCODcntSqmCmnInitDb() error.\n");
				/* hst : PE_DDR_O24_SEC_HST_SCR_Y  */
				ret = PE_HST_HW_O24_DownloadSrcYHistoInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_HST_HW_O24_DownloadSrcYHistoInitDb() error.\n");
				#endif
				wmb();
				ret = PE_CMN_HW_O24_LGSR_DownloadDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_CMN_HW_O24_LGSR_DownloadDb() error.\n");
			}
			/* inform load db data */
			ret = PE_FWI_O24_LoadDbData(p_shdw_db->top_h.db_base);
			PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_FWI_O24_LoadDbData() error.\n");
			/* *********************************************************************/
			PE_PRINT_NOTI("DL db done.(md:0x%08x)(base:0x%08x)\n", p_inf->db_mode_data[0], PE_O24_DDR_DB0_BASE);
			p_inf->db_initialized = 1;
		}
		else
		{
			PE_PRINT_NOTI("DL db done already.(md:0x%08x)(base:0x%08x)\n", p_inf->db_mode_data[0], PE_O24_DDR_DB0_BASE);
		}
		#ifdef PE_HW_O24_CHIPINFO_TABLE /* O24F22_APB */
		ret = PE_CMN_HW_O24F22_DownloadDb(pstParams);
		PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_CMN_HW_O24F22_DownloadDb() error.\n");
		#endif
		/* last step : if ext chip, bypass(psp,pe1) *//* O24F22_APB */
		do {
			LX_PE_CMN_BYPASS_BLOCKS_T block;
			__attribute__((unused)) PE_REG_O24_HW_OPT_T hw_opt = PE_REG_O24_GetDispOpt();
			if (hw_opt.external_chip==0)	break;
			block.u32BlockMask = 0x4;
			block.bOnOff = 1;
			ret = PE_CMN_HW_O24_SetBypassBlock(&block);
			PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_CMN_HW_O24_SetBypassBlock() error.\n");
		} while(0);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
__attribute__((unused)) static int PE_CMN_HW_O24F22_DownloadDb(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	PE_CFG_CTRL_T stParams;
	PE_CMN_HW_O24_SETTINGS_T *p_inf = &_g_pe_cmn_hw_o24_info;
	PE_DDR_O24F22_MD0_T *p_md0;
	PE_DDR_DB_SHDW_REG_O24F22_T *p_shdw_db = NULL;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O24F22_T *p_phys_db = NULL;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O24F22_T *p_phys_db_chk = NULL;
	volatile PE_DCM_DDR_DB_PHYS_REG_O24F22_T *p_phys_dc_db_chk = NULL;
	volatile PE_DBC_DDR_DB_PHYS_REG_O24F22_T *p_phys_dbc_db_chk = NULL;
	//volatile PE_LGSR_DDR_DB_PHYS_REG_O24F22_T *p_phys_lgsrdb_chk = NULL;
	__attribute__((unused)) UINT32 load_data[3];
	__attribute__((unused)) UINT32 load_size;
	p_shdw_db = gPE_DDR_DB_O24F22.shdw.data;
	p_phys_db = gPE_DDR_DB_O24F22.phys.data;
	do {
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);

		PE_PRINT_NOTI("DL db start(resume:%d,init2:%d).\n",pstParams->resume_mode,p_inf->db2_initialized);
		stParams.resume_mode = pstParams->resume_mode;
		if (stParams.resume_mode > 0)
		{
			if (stParams.resume_mode == 2)//snapshot
			{
				p_inf->db2_initialized = 0;
				stParams.resume_mode = 0;//force normal
			}
			else//instant
			{
				rmb();
				p_phys_db_chk = (volatile PE_DDR_DB_PHYS_REG_O24F22_T *)gPE_DDR_DB_O24F22.phys.data;
				//if ddr ruined - unnormal
				if (p_phys_db_chk->top_h.version != PE_DDR_O24F22_DB_VER || \
					p_phys_db_chk->top_h.db_base != PE_O24F22_DDR_BASE || \
					p_phys_db_chk->top_h.sec_num != PE_DDR_O24F22_SEC_NUM) 
				{
					p_inf->db2_initialized = 0;
					stParams.resume_mode = 0;//force normal
				}
				
				/* only for PE_DCM_HW_O24F22_DownloadLibDb */
				/* @resume, drv inform load db done instead platform */
				/* inform load db done *//* O24F22_APB */
				p_phys_dc_db_chk = (volatile PE_DCM_DDR_DB_PHYS_REG_O24F22_T *)gPE_DCM_DDR_DB_O24F22.phys.data;
				//if ddr ruined - unnormal
				if (p_phys_dc_db_chk->top_h.version == PE_DCM_DDR_O24F22_DB_VER || \
					p_phys_dc_db_chk->top_h.db_base == PE_O24F22_DCM_DDR_BASE || \
					p_phys_dc_db_chk->top_h.sec_num == PE_DCM_DDR_O24F22_SEC_NUM) 
				{
					do {
						__attribute__((unused)) UINT32 load_data[3];
						UINT32 load_size=0;
						load_data[0] = PE_O24F22_DCM_DDR_BASE;
						load_data[1] = sizeof(PE_DCM_DDR_DB_PHYS_REG_O24F22_T);
						load_data[2] = 3;
						load_size = (UINT32)(sizeof(UINT32)*3);
						ret = PE_FWI_O24_LoadDbDone(load_data,load_size);
						PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_DCM_HW_O24F22_DownloadLibDb() error.\n");
						PE_PRINT_NOTI("[Db]DcmDbDone resume (0x%08x)(%d)(%d)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_size);
						PE_INF_HW_O24_BACKUP_TRACE("[Db]DcmDbDone resume (0x%08x)(%d)(%d)(size:%d)",load_data[0],load_data[1],load_data[2],load_size);
					} while(0);
				}
				/* only for PE_DBC_DDR_DB_PHYS_REG_O24F22_T */
				/* @resume, drv inform load db done instead platform */
				/* inform load db done *//* O24F22_APB */
				p_phys_dbc_db_chk = (volatile PE_DBC_DDR_DB_PHYS_REG_O24F22_T *)gPE_DBC_DDR_DB_O24F22.phys.data;
				//if ddr ruined - unnormal
				if (p_phys_dbc_db_chk->top_h.version == PE_DCM_DDR_O24F22_DB_VER || \
					p_phys_dbc_db_chk->top_h.db_base == PE_O24F22_DBC_DDR_BASE || \
					p_phys_dbc_db_chk->top_h.sec_num == PE_DBC_DDR_O24F22_SEC_NUM) 
				{
					do {
						__attribute__((unused)) UINT32 load_data[3];
						UINT32 load_size=0;
						load_data[0] = PE_O24F22_DBC_DDR_BASE;
						load_data[1] = sizeof(PE_DBC_DDR_DB_PHYS_REG_O24F22_T);
						load_data[2] = 4;
						load_size = (UINT32)(sizeof(UINT32)*3);
						ret = PE_FWI_O24_LoadDbDone(load_data,load_size);
						PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_DCM_HW_O24F22_DownloadDBCDb() error.\n");
						PE_PRINT_NOTI("[Db]DbcLutDone resume (0x%08x)(%d)(%d)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_size);
						PE_INF_HW_O24_BACKUP_TRACE("[Db]DbcLutDone resume (0x%08x)(%d)(%d)(size:%d)",load_data[0],load_data[1],load_data[2],load_size);
					} while(0);
				}
				rmb();
			}
		}
		PE_PRINT_NOTI("[CMNDb][O24F22]check(resume:%d <- %d,init2:%d).\n",stParams.resume_mode,pstParams->resume_mode,p_inf->db2_initialized);
		PE_INF_HW_O24_BACKUP_TRACE("[CMNDb][O24F22]check(resume:%d <- %d,init2:%d)",stParams.resume_mode,pstParams->resume_mode,p_inf->db2_initialized);
		if (!p_inf->db2_initialized)
		{
			/* move db mode setting here to avoid db mode clear on resume init */
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			p_md0->shp_fw_en = 0;
			p_md0->hst_fw_en = 1;
			p_md0->scl_fw_en = 1;
			p_md0->tnr_fw_en = 1;
			p_md0->dnr_fw_en = 0;
			if (!stParams.resume_mode)
			{
				memset((void *)p_phys_db,0,sizeof(PE_DDR_DB_PHYS_REG_O24F22_T));
				wmb();
				p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_DDR_O24F22_DB_VER;
				p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_O24F22_DDR_BASE;
				p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_DDR_O24F22_SEC_NUM;
				PE_PRINT_NOTI("PE_O24F22_DDR_BASE: 0x%08x\n", PE_O24F22_DDR_BASE);
				/* *********************************************************************/
				/* Causion : Should be arranged in enum order **************************/
				/* *********************************************************************/
				/* mode : PE_DDR_O24_SEC_MODE(should be 1st one) */
				ret = PE_CMN_HW_O24F22_DownloadModeDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_CMN_HW_O24_DownloadModeDb() error.\n");
				/* drc : PE_DDR_O24F22_SEC_DRC_LUT */
				ret = PE_DCM_HW_O24F22_DownloadDrcDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_DCM_HW_O24F22_DownloadDrcDb() error.\n");
				/* scl : PE_DDR_O24_SEC_SCL_06T_M ~ PE_DDR_O24_SEC_SCL_04T_M */
				ret = PE_SHP_HW_O24F22_DownloadSclDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_SHP_HW_O24F22_DownloadSclDb() error.\n");
				ret = PE_DCM_HW_O24F22_DownloadDrcCurvDbInit();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_DCM_HW_O24F22_DownloadDrcCurvDbInit() error.\n");
				/* tnr : PE_DDR_O24_SEC_TNR_LUT ~ PE_DDR_O24_SEC_TNR_USER */
				ret = PE_NRD_HW_O24F22_DownloadTnrDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24F22_DownloadTnrDb() error.\n");
				/* tnr : PE_DDR_O24_SEC_TNR_SQM  */
				ret = PE_NRD_HW_O24F22_DownloadTnrSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24F22_DownloadTnrSqmCmnInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_DNR_USER  */
				ret = PE_NRD_HW_O24F22_DownloadDnrInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24F22_DownloadDnrInitDb() error.\n");
				/* dnr : PE_DDR_O24_SEC_DNR_SQM  */
				ret = PE_NRD_HW_O24F22_DownloadDnrSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24F22_DownloadDnrSqmCmnInitDb() error.\n");
				/* nrd dcnt : PE_DDR_O24_SEC_DNR_DCNT_USER	*/
				ret = PE_NRD_HW_O24F22_DownloadDnrDcntInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24F22_DownloadDnrDcntInitDb() error.\n");
				/* nrd dcnt : PE_DDR_O24_SEC_DNR_DCNT_SQM  */
				ret = PE_NRD_HW_O24F22_DownloadDnrDcntSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_NRD_HW_O24F22_DownloadDnrDcntSqmCmnInitDb() error.\n");
				/* shp : PE_DDR_O24_SEC_SHP_UI_SQM_VSD	*/
				ret = PE_SHP_HW_O24F22_DownloadShpSqmCmnInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_SHP_HW_O24F22_DownloadShpSqmCmnInitDb() error.\n");
				/* shp : PE_DDR_O24_SEC_SHP_SQM_CMN_VSD  */
				ret = PE_SHP_HW_O24F22_DownloadShpSqmDetailInitDb();
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_SHP_HW_O24F22_DownloadShpSqmDetailInitDb() error.\n");
				wmb();
				/* O24F22_CRC */
				do {
					UINT32 i, j, ddr_size32, crc32 = 0xFFFFFFFF;
					volatile UINT32 *pddr_data32;
					UINT32 ddr_data32;
					UINT8 *pddr_data08;
					ddr_size32 = (sizeof(PE_DDR_DB_PHYS_REG_O24F22_T)>>2)-1;//except for crc
					pddr_data32 = (volatile UINT32 *)p_phys_db;
					pddr_data08 = (UINT8 *)&ddr_data32;
					PE_PRINT_NOTI("[CRC]S: size32:%d\n",ddr_size32);
					PE_INF_HW_O24_BACKUP_TRACE("[CRC]S: size32:%d",ddr_size32);
					for (i=0;i<ddr_size32;i++)
					{
						rmb();
						ddr_data32 = (UINT32)pddr_data32[i];
						rmb();

						j = ((int) (crc32 >> 24) ^ pddr_data08[0]) & 0xFF;
						crc32 = (crc32 << 8) ^ g_pe_cmn_hw_o24_crc_table[j];

						j = ((int) (crc32 >> 24) ^ pddr_data08[1]) & 0xFF;
						crc32 = (crc32 << 8) ^ g_pe_cmn_hw_o24_crc_table[j];

						j = ((int) (crc32 >> 24) ^ pddr_data08[2]) & 0xFF;
						crc32 = (crc32 << 8) ^ g_pe_cmn_hw_o24_crc_table[j];

						j = ((int) (crc32 >> 24) ^ pddr_data08[3]) & 0xFF;
						crc32 = (crc32 << 8) ^ g_pe_cmn_hw_o24_crc_table[j];
						#if 0
						PE_PRINT_NOTI("[%03d]data32:%08X,data08:%02X|%02X|%02X|%02X,table[%03d]:%08X,crc32:%08X\n",\
							i,ddr_data32,pddr_data08[0],pddr_data08[1],pddr_data08[2],pddr_data08[3],j,_g_pe_crc_table[j],crc32);
						#endif
					}
					p_phys_db->crc = ~crc32;
					wmb();
					PE_PRINT_NOTI("[CRC]E: crc:0x%08X <- 0x%08X\n",~crc32,crc32);
					PE_INF_HW_O24_BACKUP_TRACE("[CRC]E: crc:0x%08X <- 0x%08X",~crc32,crc32);
				} while(0);
			}
			p_inf->db2_initialized = 1;
		}
		/* inform load db done *//* O24F22_APB */
		do {
			__attribute__((unused)) UINT32 load_data[3];
			UINT32 load_size=0;
			#if 0
			UINT32 sec_typ;
			UINT32 ddr_total=0;
			//ret = PE_CMN_HW_O24_GetMemInfo(&load_data[0],&load_data[1]);
			//PE_CMN_HW_O24_CHECK_CODE(ret, break, "PE_CMN_HW_O24_GetMemInfo() error.\n");
			for (sec_typ=0; sec_typ<PE_DDR_O24F22_SEC_NUM; sec_typ++)
			{
				ddr_total += p_shdw_db->top_h.sec_size[sec_typ];
			}
			#endif
			load_data[0] = PE_O24F22_DDR_BASE;
			load_data[1] = sizeof(PE_DDR_DB_PHYS_REG_O24F22_T);
			load_data[2] = 0;
			load_size = (UINT32)(sizeof(UINT32)*3);
			ret = PE_FWI_O24_LoadDbDone(load_data,load_size);
			PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_FWI_O24_LoadDbDone() error.\n");
			PE_PRINT_NOTI("[Db]LoadDbDone(0x%08x)(%d)(%d)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_size);
			PE_INF_HW_O24_BACKUP_TRACE("[Db]LoadDbDone(0x%08x)(%d)(%d)(size:%d)",load_data[0],load_data[1],load_data[2],load_size);
		} while(0);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}


static int PE_CMN_HW_O24_LGSR_DownloadDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	#if (CONFIG_LX_O24_CHIP_FIRMWARE == 1) 
/*
#define PE_FWI_O24_LGSR_DNSR_COEFF_NUM 290304
#define PE_FWI_O24_LGSR_DNNR_COEFF_NUM 206080
#define PE_FWI_O24_LGSR_SRMR_COEFF_NUM 5152
#define PE_FWI_O24_LGSR_DNSR_SIZE (sizeof(UINT32)*PE_FWI_O24_LGSR_DNSR_COEFF_NUM)
#define PE_FWI_O24_LGSR_DNNR_SIZE (sizeof(UINT32)*PE_FWI_O24_LGSR_DNNR_COEFF_NUM)
#define PE_FWI_O24_LGSR_SRMR_SIZE (sizeof(UINT32)*PE_FWI_O24_LGSR_SRMR_COEFF_NUM)

typedef struct
{
	// Coef. 41248 Byte * 12EA(2x 8�� + 3x 4��)
	UINT32 coeff[4*PE_FWI_O24_LGSR_DNSR_COEFF_NUM];
}
PE_LGSR_DDR_DB_DNSR_O24_T;
typedef struct
{
	// Coef. 29280 Byte * 8EA(2x 16ch 4�� + 3x 24ch 4��)
	UINT32 coeff[4*PE_FWI_O24_LGSR_DNNR_COEFF_NUM];
}
PE_LGSR_DDR_DB_DNNR_O24_T;
*/

	volatile UINT32 *pDnSr=NULL;
	volatile UINT32 *pDnNr=NULL;
	// volatile UINT32 *pSrMr=NULL; //SR MERGE
	UINT32 base_DnSr;
	UINT32 base_DnNr;
	UINT32 base_SrMr; //SR MERGE
	do {
		
		/*download LGSR OSD weight/apb*/
		base_DnSr = gPeMem[0].base + 0x2000;
		pDnSr     = (volatile UINT32 *)vmap_phys(base_DnSr, PE_FWI_O24_LGSR_DNSR_SIZE+PAGE_SIZE);
		base_DnNr = gPeMem[0].base + 0x11F800;
		pDnNr     = (volatile UINT32 *)vmap_phys(base_DnNr, PE_FWI_O24_LGSR_DNNR_SIZE+PAGE_SIZE);
		base_SrMr = gPeMem[0].base + 0x485D40;
		//pSrMr     = (volatile UINT32 *)vmap_phys(base_DnNr, PE_FWI_O24_LGSR_DNNR_SIZE+PAGE_SIZE);
		
		memcpy((UINT32 *)pDnSr,	lgsr_dnsr_coeff_set_o24,	PE_FWI_O24_LGSR_DNSR_SIZE);
		memcpy((UINT32 *)pDnNr,	lgsr_dnnr_coeff_set_o24,	PE_FWI_O24_LGSR_DNNR_SIZE);
		wmb();
			/* noti */
		PE_PRINT_NOTI("LGSR SR/NR data : DL done.(base:0x%08x, 0x%08x) ver.240712\n",base_DnSr, base_DnNr);
	} while(0);
	if(pDnSr)	vunmap_phys((void*)pDnSr);
	if(pDnNr)	vunmap_phys((void*)pDnNr);
	//if(pSrMr)	vunmap_phys((void*)pSrMr);
	#endif /*(CONFIG_LX_O24_CHIP_FIRMWARE == 1)*/
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}

/**
 * download mode db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_HW_O24_DownloadModeDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_CMN_HW_O24_SETTINGS_T *p_inf = &_g_pe_cmn_hw_o24_info;
	PE_DDR_DB_SHDW_REG_O24_T *p_shdw_db = gPE_DDR_DB_O24.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O24_T *p_phys_db = gPE_DDR_DB_O24.phys.data;
	do {
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);

		/* header */
		sec_typ = PE_DDR_O24_SEC_MODE;
		p_shdw_db->sec_d[sec_typ].header.version   = 0x3;
		p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
		p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O24_MODE_ITEM_NUM;
		p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O24_MODE_SIZE;
		p_phys_db->mode.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
		p_phys_db->mode.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
		p_phys_db->mode.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
		p_phys_db->mode.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
		/* data */
		size = (PE_DDR_O24_MODE_ITEM_NUM * PE_DDR_O24_MODE_SIZE * sizeof(UINT32));
		p_shdw_db->top_h.sec_base[sec_typ] = \
			p_shdw_db->top_h.db_base+sizeof(PE_DDR_O24_TOP_HEADER_T);
		p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O24_HEADER_T);
		p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
		p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
		p_shdw_db->sec_d[sec_typ].data_base = \
			p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O24_HEADER_T);
		/* wr ddr */
		p_phys_db->mode.data[0] = p_inf->db_mode_data[0];
		/* noti */
		PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
			PE_DDR_REG_O24_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * download mode db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
__attribute__((unused)) static int PE_CMN_HW_O24F22_DownloadModeDb(void)
{
	int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_CMN_HW_O24_SETTINGS_T *p_inf = &_g_pe_cmn_hw_o24_info;
	PE_DDR_DB_SHDW_REG_O24F22_T *p_shdw_db = gPE_DDR_DB_O24F22.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O24F22_T *p_phys_db = gPE_DDR_DB_O24F22.phys.data;
	do {
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);

		/* header */
		sec_typ = PE_DDR_O24F22_SEC_MODE;
		p_shdw_db->sec_d[sec_typ].header.version   = 0x0;
		p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
		p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O24F22_MODE_ITEM_NUM;
		p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O24F22_MODE_SIZE;
		p_phys_db->mode.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
		p_phys_db->mode.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
		p_phys_db->mode.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
		p_phys_db->mode.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
		/* data */
		size = (PE_DDR_O24F22_MODE_ITEM_NUM * PE_DDR_O24F22_MODE_SIZE * sizeof(UINT32));
		p_shdw_db->top_h.sec_base[sec_typ] = \
			p_shdw_db->top_h.db_base+sizeof(PE_DDR_O24F22_TOP_HEADER_T);
		p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O24F22_HEADER_T);
		p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
		p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
		p_shdw_db->sec_d[sec_typ].data_base = \
			p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O24F22_HEADER_T);
		/* wr ddr */
		p_phys_db->mode.data[0] = p_inf->db_mode_data[0];
		/* noti */
		PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
			PE_DDR_REG_O24F22_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}

/**
 * download cvd db
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_HW_O24_DownloadCvdDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	UINT32 size, sec_typ;
	PE_DDR_DB_SHDW_REG_O24_T *p_shdw_db = gPE_DDR_DB_O24.shdw.data;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O24_T *p_phys_db = gPE_DDR_DB_O24.phys.data;
	volatile UINT32 *p_cvd_dflt_data  = NULL;
	do {
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		p_cvd_dflt_data  = p_phys_db->cvd_dflt.data;
		CHECK_KNULL(p_cvd_dflt_data);
		/* cvd_dflt **************************************************************/
		sec_typ = PE_DDR_O24_SEC_CVD_DFLT;
		/* header */
		p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
		p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
		p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_O24_CVD_DFLT_ITEM_NUM;
		p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_O24_CVD_DFLT_SIZE;
		p_phys_db->cvd_dflt.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
		p_phys_db->cvd_dflt.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
		p_phys_db->cvd_dflt.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
		p_phys_db->cvd_dflt.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
		/* data */
		size = (PE_DDR_O24_CVD_DFLT_ITEM_NUM * PE_DDR_O24_CVD_DFLT_SIZE * sizeof(UINT32));
		p_shdw_db->top_h.sec_base[sec_typ] = \
			p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
		p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_O24_HEADER_T);
		p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
		p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
		p_shdw_db->sec_d[sec_typ].data_base = \
			p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_O24_HEADER_T);
		/* wr ddr */
#ifdef INCLUDE_KDRV_AFE
		ret = CVD_SetPqModeToDdr(p_cvd_dflt_data);//fix compile error
		PE_CMN_HW_O24_CHECK_CODE(ret,break,"CVD_SetPqModeToDdr() error.\n");
#endif
		/* noti */
		PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
			PE_DDR_REG_O24_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}

/**
 * init chip info(O24F22_APB)(O24F22_TBL)
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_HW_O24_InitChipInfo(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	UINT32 i, data0, data1;
	UINT32 ofst, size;

	#define PE_CMN_HW_O24_SIZE_CHK(_n,_x,_y)	(_x),((_x)/(_n)),(_n),(_x),(_y)

	do {
		CHECK_KNULL(pstParams);
		if (!gPE_CHPI_DDR_O24)	break;

		data0 = 0xF40605B4;//pe1_apl_stat_01(RO)
		data1 = PE_SWAP32(data0);
		if (pstParams->resume_mode != 1)//if normal or snapshot
		{
			/* O24F22_APB */
			PE_CHPI_APB0_O24F22_QWr(crc1,PE_CHPI_APB_O24F22_CRC1);
			PE_CHPI_APB0_O24F22_QWr(crc0,0xFFFFFFFF);
			PE_CHPI_APB0_O24F22_Wr(head1.info.udata32,0);
			PE_CHPI_APB0_O24F22_Wr(head1.info.max_num,32);
			PE_CHPI_APB0_O24F22_Wr(head1.info.bufidx1,4);
			PE_CHPI_APB0_O24F22_Wr(head1.info.bufidx0,1);
			PE_CHPI_APB0_O24F22_Wr(head1.info.version,0);
			PE_CHPI_APB0_O24F22_WrFL(head1.info.udata32);
			PE_CHPI_APB0_O24F22_QWr(head1.cnt0.udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.cnt1.udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.cnt2.udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.cnt3.udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.cnt4.udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.cnt5.udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.cnt6.udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.cnt7.udata32,0);

			/* PE */
			ofst = sizeof(UINT32)+sizeof(PE_CHPI_APB0_DB_H_O24F22_T);
			size = sizeof(PE_CHPI_CMN0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[0].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[0].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[0].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_CEN0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[1].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[1].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[1].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_CEN1_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[2].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[2].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[2].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_CW0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[3].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[3].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[3].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_VSP0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[4].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[4].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[4].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DSE0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[5].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[5].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[5].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DCE0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[6].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[6].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[6].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DTM0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[7].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[7].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[7].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_LLL0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[8].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[8].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[8].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_FSW0_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[9].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[9].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[9].udata32);

			PE_CHPI_APB0_O24F22_QWr(head1.pos[10].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[11].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[12].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[13].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[14].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[15].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[16].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[17].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[18].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[19].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[20].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[21].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[22].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[23].udata32,0);

			/* HDR */
			ofst = PE_CHPI_APB_O24F22_OFST1;
			size = sizeof(PE_CHPI_HDR_TM_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[24].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[24].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[24].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_HDR_YG_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[25].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[25].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[25].udata32);

			PE_CHPI_APB0_O24F22_QWr(head1.pos[26].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[27].udata32,0);

			ofst += size;
			size = sizeof(PE_CHPI_HDR_HS_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[28].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[28].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[28].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_HDR_PCC_O24F22_T);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[29].ofst,ofst);
			PE_CHPI_APB0_O24F22_Wr(head1.pos[29].size,size);
			PE_CHPI_APB0_O24F22_WrFL(head1.pos[29].udata32);

			PE_CHPI_APB0_O24F22_QWr(head1.pos[30].udata32,0);
			PE_CHPI_APB0_O24F22_QWr(head1.pos[31].udata32,0);

			PE_CHPI_APB0_O24F22_QWr(head0,PE_CHPI_APB_O24F22_HEAD);

			/* O24F22_TBL 0 */
			PE_CHPI_TBL0_O24F22_QWr(crc1,PE_CHPI_TBL_O24F22_CRC1);
			PE_CHPI_TBL0_O24F22_QWr(crc0,0xFFFFFFFF);
			PE_CHPI_TBL0_O24F22_Wr(head1.info.udata32,0);
			PE_CHPI_TBL0_O24F22_Wr(head1.info.max_num,22);
			PE_CHPI_TBL0_O24F22_Wr(head1.info.bufidx1,5);
			PE_CHPI_TBL0_O24F22_Wr(head1.info.bufidx0,2);
			PE_CHPI_TBL0_O24F22_Wr(head1.info.version,0);
			PE_CHPI_TBL0_O24F22_WrFL(head1.info.udata32);
			PE_CHPI_TBL0_O24F22_QWr(head1.cnt0.udata32,0);
			PE_CHPI_TBL0_O24F22_QWr(head1.cnt1.udata32,0);
			PE_CHPI_TBL0_O24F22_QWr(head1.cnt2.udata32,0);
			PE_CHPI_TBL0_O24F22_QWr(head1.cnt3.udata32,0);
			PE_CHPI_TBL0_O24F22_QWr(head1.cnt4.udata32,0);
			PE_CHPI_TBL0_O24F22_QWr(head1.cnt5.udata32,0);
			PE_CHPI_TBL0_O24F22_QWr(head1.cnt6.udata32,0);
			PE_CHPI_TBL0_O24F22_QWr(head1.cnt7.udata32,0);


			ofst = sizeof(UINT32)+sizeof(PE_CHPI_TBL0_DB_H_O24F22_T);
			size = sizeof(PE_CHPI_CCO_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[0].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[0].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[0].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_OBC_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[1].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[1].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[1].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_OBE_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[2].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[2].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[2].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_AMG_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[3].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[3].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[3].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_RES_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[4].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[4].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[4].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_CTI_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[5].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[5].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[5].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_TNR_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[6].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[6].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[6].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DNR_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[7].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[7].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[7].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DNR_OSD_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[8].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[8].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[8].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_SHP_UI_SQM_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[9].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[9].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[9].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_SHP_CMN_SQM_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[10].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[10].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[10].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_TNR_SQM_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[11].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[11].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[11].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DNR_SQM_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[12].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[12].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[12].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DNR_DCNT_SQM_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[13].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[13].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[13].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_TNR_USER_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[14].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[14].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[14].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DNR_USER_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[15].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[15].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[15].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DNR_DCNT_USER_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[16].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[16].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[16].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_DRC_CUV_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[17].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[17].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[17].udata32);
			ofst += size;
			size = sizeof(PE_CHPI_OBE_C_TBL_O24F22_T);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[18].ofst,ofst);
			PE_CHPI_TBL0_O24F22_Wr(head1.pos[18].size,size);
			PE_CHPI_TBL0_O24F22_WrFL(head1.pos[18].udata32);
			for (i=22; i<32; i++)
			{
				PE_CHPI_TBL0_O24F22_QWr(head1.pos[i].udata32,0);
			}
			PE_CHPI_TBL0_O24F22_QWr(head0,PE_CHPI_TBL_O24F22_HEAD);

			ofst = 4;//from head1
			size = sizeof(PE_CHPI_APB0_DB_H_O24F22_T);    PE_INF_HW_O24_BACKUP_CHPI0("[CHI]head   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_CMN0_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]cmn0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_CEN0_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]cen0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_CEN1_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]cen1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_CW0_O24F22_T);          PE_INF_HW_O24_BACKUP_CHPI0("[CHI]cw0    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_VSP0_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]vsp0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DSE0_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]dse0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DCE0_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]dce0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DTM0_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]dtm0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_LLL0_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]lll0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_FSW0_O24F22_T);         PE_INF_HW_O24_BACKUP_CHPI0("[CHI]fsw0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_APB0_RESVD0_O24F22_T);  PE_INF_HW_O24_BACKUP_CHPI0("[CHI]resvd0 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_HDR_TM_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI0("[CHI]tm     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_HDR_YG_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI0("[CHI]yg     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_HDR_HS_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI0("[CHI]hs     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_HDR_PCC_O24F22_T);      PE_INF_HW_O24_BACKUP_CHPI0("[CHI]pcc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_APB0_RESVD1_O24F22_T);  PE_INF_HW_O24_BACKUP_CHPI0("[CHI]resvd1 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_REG_O24F22_T);          PE_INF_HW_O24_BACKUP_CHPI0("[CHI]TOTAL  (%5d)(0x%04x) vs (%5d)(0x%04x)",size,size,PE_CHPI_APB_O24F22_TOTAL,PE_CHPI_APB_O24F22_TOTAL);

			ofst = 4;//from head1
			size = sizeof(PE_CHPI_TBL0_DB_H_O24F22_T);     PE_INF_HW_O24_BACKUP_CHPI1("[CHI]head   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_CCO_TBL_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]cco    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_OBC_TBL_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]obc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_OBE_TBL_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]obe    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_AMG_TBL_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]amg    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_RES_TBL_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]res    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_CTI_TBL_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]cti    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_TNR_TBL_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]tnr    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DNR_TBL_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]dnr    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DNR_OSD_TBL_O24F22_T);   PE_INF_HW_O24_BACKUP_CHPI1("[CHI]osd    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_SHP_UI_SQM_O24F22_T);    PE_INF_HW_O24_BACKUP_CHPI1("[CHI]sqm0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_SHP_CMN_SQM_O24F22_T);   PE_INF_HW_O24_BACKUP_CHPI1("[CHI]sqm1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_TNR_SQM_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]sqm2   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DNR_SQM_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]sqm3   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DNR_DCNT_SQM_O24F22_T);  PE_INF_HW_O24_BACKUP_CHPI1("[CHI]sqm4   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_TNR_USER_O24F22_T);      PE_INF_HW_O24_BACKUP_CHPI1("[CHI]usr0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DNR_USER_O24F22_T);      PE_INF_HW_O24_BACKUP_CHPI1("[CHI]usr1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DNR_DCNT_USER_O24F22_T); PE_INF_HW_O24_BACKUP_CHPI1("[CHI]usr2   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_DRC_CUV_O24F22_T);       PE_INF_HW_O24_BACKUP_CHPI1("[CHI]drc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_OBE_C_TBL_O24F22_T);     PE_INF_HW_O24_BACKUP_CHPI1("[CHI]obec   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(8,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_TBL0_RESVD_O24F22_T);    PE_INF_HW_O24_BACKUP_CHPI1("[CHI]resvd  (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_O24_SIZE_CHK(4,size,ofst));ofst+=size;
			size = sizeof(PE_CHPI_TBL0_O24F22_T);          PE_INF_HW_O24_BACKUP_CHPI1("[CHI]TOTAL  (%5d)(0x%04x) vs (%5d)(0x%04x)",size,size,PE_CHPI_TBL_O24F22_TOTAL,PE_CHPI_TBL_O24F22_TOTAL);

		}
		PE_PRINT_NOTI("[CHI]done(resume:%d)\n",pstParams->resume_mode);
		PE_INF_HW_O24_BACKUP_TRACE("[CHI]done(resume:%d)",pstParams->resume_mode);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}

/**
 * get db info.
 *
 * @param   inf_type [in] UINT32, see PE_CMN_HW_O24_DB_INF_TYPE
 * @param   sec_type [in] UINT32, see PE_DDR_O24_SEC_TYPE
 * @return  UINT32.
 * @see
 * @author
 */
UINT32 PE_CMN_HW_O24_GetDbInfo(UINT32 inf_type, UINT32 sec_type)
{
	UINT32 ret = 0;
	#ifdef PE_HW_O24_BRINGUP
	PE_DDR_O24_MD0_T *p_md0;
	PE_CMN_HW_O24_SETTINGS_T *p_inf = &_g_pe_cmn_hw_o24_info;
	PE_DDR_DB_SHDW_REG_O24_T *p_shdw_db = gPE_DDR_DB_O24.shdw.data;

	if (sec_type>=PE_DDR_O24_SEC_NUM)
	return ret;

	switch (inf_type)
	{
		case PE_CMN_HW_O24_DB_INF_IS_DB_INIT:
			ret = p_inf->db_initialized;
			break;
		case PE_CMN_HW_O24_DB_INF_TOP_VERSION:
			ret = p_shdw_db->top_h.version;
			break;
		case PE_CMN_HW_O24_DB_INF_TOP_BASE:
			ret = p_shdw_db->top_h.db_base;
			break;
		case PE_CMN_HW_O24_DB_INF_TOP_SEC_NUM:
			ret = p_shdw_db->top_h.sec_num;
			break;
		case PE_CMN_HW_O24_DB_INF_SEC_BASE:
			ret = p_shdw_db->top_h.sec_base[sec_type];
			break;
		case PE_CMN_HW_O24_DB_INF_SEC_SIZE:
			ret = p_shdw_db->top_h.sec_size[sec_type];
			break;
		case PE_CMN_HW_O24_DB_INF_SEC_VERSION:
			ret = p_shdw_db->sec_d[sec_type].header.version;
			break;
		case PE_CMN_HW_O24_DB_INF_SEC_TYPE:
			ret = p_shdw_db->sec_d[sec_type].header.sec_type;
			break;
		case PE_CMN_HW_O24_DB_INF_SEC_ITEM_NUM:
			ret = p_shdw_db->sec_d[sec_type].header.item_num;
			break;
		case PE_CMN_HW_O24_DB_INF_SEC_ITEM_SIZE:
			ret = p_shdw_db->sec_d[sec_type].header.item_size;
			break;
		case PE_CMN_HW_O24_DB_INF_SEC_DATA_BASE:
			ret = p_shdw_db->sec_d[sec_type].data_base;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_SHP_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->shp_fw_en;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_HST_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->hst_fw_en;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_SCL_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->scl_fw_en;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_TNR_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->tnr_fw_en;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_DNR_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->dnr_fw_en;
			break;
		default:
			ret = 0;
			break;
	}
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}

/**
 * set db info.
 * - I think that shdw db modification is not good.
 *
 * @param   inf_type [in] UINT32, see PE_CMN_HW_O24_DB_INF_TYPE
 * @param   sec_type [in] UINT32, see PE_DDR_O24_SEC_TYPE
 * @param   value [in] UINT32
 * @return  UINT32.
 * @see
 * @author
 */
UINT32 PE_CMN_HW_O24_SetDbInfo(UINT32 inf_type, UINT32 sec_type, UINT32 value)
{
	UINT32 ret = 0;
	#ifdef PE_HW_O24_BRINGUP
	PE_DDR_O24_MD0_T *p_md0;
	PE_CMN_HW_O24_SETTINGS_T *p_inf = &_g_pe_cmn_hw_o24_info;

	if (sec_type>=PE_DDR_O24_SEC_NUM)
		return ret;

	switch (inf_type)
	{
		case PE_CMN_HW_O24_DB_INF_MD0_SHP_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			p_md0->shp_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_HST_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			p_md0->hst_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_SCL_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			p_md0->scl_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_TNR_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			p_md0->tnr_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_O24_DB_INF_MD0_DNR_FW_EN:
			p_md0 = (PE_DDR_O24_MD0_T *)p_inf->db_mode_data;
			p_md0->dnr_fw_en = value? 1:0;
			break;
		default:
			ret = 0;
			break;
	}
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}


/**
 * set suspend module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SuspendModule(void)
{
	PE_TSK_O24_SuspendModule(0);
	return RET_OK;
}

int PE_CMN_HW_O24_ResumeModule(UINT32 enable)
{
    int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	PE_DDR_DB_SHDW_REG_O24F22_T *p_shdw_db = NULL;
	//volatile PE_DDR_DB_PHYS_REG_O24F22_T *p_phys_db = NULL;
	__attribute__((unused)) volatile PE_DDR_DB_PHYS_REG_O24F22_T *p_phys_db_chk = NULL;
	volatile PE_DCM_DDR_DB_PHYS_REG_O24F22_T *p_phys_dc_db_chk = NULL;
	volatile PE_DBC_DDR_DB_PHYS_REG_O24F22_T *p_phys_dbc_db_chk = NULL;
	__attribute__((unused)) UINT32 load_data[3];
	UINT32 load_size=0;
	do {
		if(enable) //resume
		{
			rmb();
			p_phys_db_chk = (volatile PE_DDR_DB_PHYS_REG_O24F22_T *)gPE_DDR_DB_O24F22.phys.data;
			//if ddr ruined - unnormal
			if (p_phys_db_chk->top_h.version == PE_DDR_O24F22_DB_VER || \
				p_phys_db_chk->top_h.db_base == PE_O24F22_DDR_BASE || \
				p_phys_db_chk->top_h.sec_num == PE_DDR_O24F22_SEC_NUM) 
			{
				load_data[0] = PE_O24F22_DDR_BASE;
				load_data[1] = sizeof(PE_DDR_DB_PHYS_REG_O24F22_T);
				load_data[2] = 0;
				load_size = (UINT32)(sizeof(UINT32)*3);
				ret = PE_FWI_O24_LoadDbDone(load_data,load_size);
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_FWI_O24_LoadDbDone() error.\n");
				PE_PRINT_NOTI("[Db]Resume:%d, LoadDbDone (0x%08x)(%d)(%d)(size:%d)\n",enable,load_data[0],load_data[1],load_data[2],load_size);
				PE_INF_HW_O24_BACKUP_TRACE("[Db]Resume:%d,LoadDbDone(0x%08x)(%d)(%d)(size:%d)",enable,load_data[0],load_data[1],load_data[2],load_size);
			}
			
			/* only for PE_DCM_HW_O24F22_DownloadLibDb */
			/* @resume, drv inform load db done instead platform */
			/* inform load db done *//* O24F22_APB */
			p_phys_dc_db_chk = (volatile PE_DCM_DDR_DB_PHYS_REG_O24F22_T *)gPE_DCM_DDR_DB_O24F22.phys.data;
			//if ddr ruined - unnormal
			if (p_phys_dc_db_chk->top_h.version == PE_DCM_DDR_O24F22_DB_VER || \
				p_phys_dc_db_chk->top_h.db_base == PE_O24F22_DCM_DDR_BASE || \
				p_phys_dc_db_chk->top_h.sec_num == PE_DCM_DDR_O24F22_SEC_NUM) 
			{
				load_data[0] = PE_O24F22_DCM_DDR_BASE;
				load_data[1] = sizeof(PE_DCM_DDR_DB_PHYS_REG_O24F22_T);
				load_data[2] = 3;
				load_size = (UINT32)(sizeof(UINT32)*3);
				ret = PE_FWI_O24_LoadDbDone(load_data,load_size);
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_DCM_HW_O24F22_DownloadLibDb() error.\n");
				PE_PRINT_NOTI("[Db]DcmDbDone resume (0x%08x)(%d)(%d)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_size);
				PE_INF_HW_O24_BACKUP_TRACE("[Db]DcmDbDone resume (0x%08x)(%d)(%d)(size:%d)",load_data[0],load_data[1],load_data[2],load_size);
			}
			/* only for PE_DBC_DDR_DB_PHYS_REG_O24F22_T */
			/* @resume, drv inform load db done instead platform */
			/* inform load db done *//* O24F22_APB */
			p_phys_dbc_db_chk = (volatile PE_DBC_DDR_DB_PHYS_REG_O24F22_T *)gPE_DBC_DDR_DB_O24F22.phys.data;
			//if ddr ruined - unnormal
			if (p_phys_dbc_db_chk->top_h.version == PE_DCM_DDR_O24F22_DB_VER || \
				p_phys_dbc_db_chk->top_h.db_base == PE_O24F22_DBC_DDR_BASE || \
				p_phys_dbc_db_chk->top_h.sec_num == PE_DBC_DDR_O24F22_SEC_NUM) 
			{
				__attribute__((unused)) UINT32 load_data[3];
				UINT32 load_size=0;
				load_data[0] = PE_O24F22_DBC_DDR_BASE;
				load_data[1] = sizeof(PE_DBC_DDR_DB_PHYS_REG_O24F22_T);
				load_data[2] = 4;
				load_size = (UINT32)(sizeof(UINT32)*3);
				ret = PE_FWI_O24_LoadDbDone(load_data,load_size);
				PE_CMN_HW_O24_CHECK_CODE(ret,break,"PE_DCM_HW_O24F22_DownloadDBCDb() error.\n");
				PE_PRINT_NOTI("[Db]DbcLutDone resume (0x%08x)(%d)(%d)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_size);
				PE_INF_HW_O24_BACKUP_TRACE("[Db]DbcLutDone resume (0x%08x)(%d)(%d)(size:%d)",load_data[0],load_data[1],load_data[2],load_size);
			}
			rmb();
		}
		else
		{
			PE_PRINT_NOTI("PE ResumeModule (enable:%d)\n",enable);
			PE_INF_HW_O24_BACKUP_TRACE("PE ResumeModule (enable:%d)\n",enable);
		}
	} while(0);
	#endif
	return ret;
}

/**
 * set vcp level control
 *
 * @param   *pstParams [in] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do {
		__attribute__((unused)) PE_REG_O24_HW_OPT_T hw_opt = PE_REG_O24_GetDispOpt();
		LX_PE_CMN_VCP_LEVEL_CTRL_T *pp = (LX_PE_CMN_VCP_LEVEL_CTRL_T *)pstParams;
		static LX_PE_CMN_VCP_LEVEL_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMN_VCP_LEVEL_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMN("duplicated DB : LX_PE_CMN_VCP_LEVEL_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_CMN("set pstParams[%d] : enable:%d, center:%d, contrast:%d, brightness:%d, saturation:%d\n",\
			pstParams->win_id,pstParams->enable,pstParams->center_position,\
			pstParams->contrast,pstParams->brightness,pstParams->saturation);

		if(PE_CHECK_WIN0(pstParams->win_id))
		{
			if(hw_opt.external_chip == 0x0) //4k model 
			{
				PE_VCP_DISP_O24_QWr03(vcp_vsp_u0_ctrl_00, 	enable, 		 GET_BITS(pstParams->enable,		 0,1),\
															center_position, GET_BITS(pstParams->center_position,0,8),\
															contrast,		 GET_BITS(pstParams->contrast,		 0,10));
				PE_VCP_DISP_O24_QWr02(vcp_vsp_u0_ctrl_01,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
															brightness,		 GET_BITS(pstParams->brightness,	 0,10));
			}
			#if 1	/* O24_VERI */
			do {
				PE_VSD0_VERI_O24_QWr03(vsd_veri_vsp0_0, enable, 		 GET_BITS(pstParams->enable,		 0,1),\
														center_position, GET_BITS(pstParams->center_position,0,8),\
														contrast,		 GET_BITS(pstParams->contrast,		 0,10));
				PE_VSD0_VERI_O24_QWr02(vsd_veri_vsp0_1,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
														brightness,		 GET_BITS(pstParams->brightness,	 0,10));
			} while(0);
			#endif
			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd0_veri_vsp_0.enable,GET_BITS(pstParams->enable,0,1));
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd0_veri_vsp_0.center_position,GET_BITS(pstParams->center_position,0,8));
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd0_veri_vsp_0.contrast,GET_BITS(pstParams->contrast,0,10));
				PE_CHPI_APB0_O24F22_WrFL(fsw0.vsd0_veri_vsp_0.udata32);
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd0_veri_vsp_1.saturation,GET_BITS(pstParams->saturation,0,8));
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd0_veri_vsp_1.brightness,GET_BITS(pstParams->brightness,0,10));
				PE_CHPI_APB0_O24F22_WrFL(fsw0.vsd0_veri_vsp_1.udata32);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_FSW0);
			} while(0);
			#endif
		}
		else if(PE_CHECK_WIN1(pstParams->win_id))
		{
			#if 0	//20200611, vcp_vsp_u1 moved to fw setting for estreamer(QEVENTTWEN-25839)(TVPM-12053)
			PE_VCP_DISP_O24_QWr03(vcp_vsp_u1_ctrl_00, 	enable, 		 GET_BITS(pstParams->enable,		 0,1),\
														center_position, GET_BITS(pstParams->center_position,0,8),\
														contrast,		 GET_BITS(pstParams->contrast,		 0,10));
			PE_VCP_DISP_O24_QWr02(vcp_vsp_u1_ctrl_01,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
														brightness,		 GET_BITS(pstParams->brightness,	 0,10));
			#endif
			#if 1	/* O24_VERI */
			do {
				PE_VSD0_VERI_O24_QWr03(vsd_veri_vsp1_0, enable, 		 GET_BITS(pstParams->enable,		 0,1),\
														brightness,		 GET_BITS(pstParams->brightness,	 0,10),\
														contrast,		 GET_BITS(pstParams->contrast,		 0,10));
				//PE_VSD0_VERI_O24_QWr01(vsd_veri_vsp1_1,	saturation,		 GET_BITS(pstParams->saturation,	 0,8));
			} while(0);
			#endif
			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd1_veri_vsp_0.enable,GET_BITS(pstParams->enable,0,1));
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd1_veri_vsp_0.brightness,GET_BITS(pstParams->brightness,0,10));
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd1_veri_vsp_0.contrast,GET_BITS(pstParams->contrast,0,10));
				PE_CHPI_APB0_O24F22_WrFL(fsw0.vsd1_veri_vsp_0.udata32);
				//PE_CHPI_APB0_O24F22_Wr(fsw0.vsd1_veri_vsp_1.saturation,GET_BITS(pstParams->saturation,0,8));
				//PE_CHPI_APB0_O24F22_Wr(fsw0.vsd1_veri_vsp_1.brightness,GET_BITS(pstParams->brightness,0,10));
				//PE_CHPI_APB0_O24F22_WrFL(fsw0.vsd1_veri_vsp_1.udata32);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_FSW0);
			} while(0);
			#endif
		}
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * get vcp level control
 *
 * @param   *pstParams [in/out] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_GetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifdef PE_HW_O24_BRINGUP
	LX_PE_WIN_ID win_id;
	do {
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);

		if(PE_CHECK_WIN0(win_id))
		{
			PE_VCP_DISP_O24_QRd03(vcp_vsp_u0_ctrl_00, 	enable, 		 pstParams->enable,\
														center_position, pstParams->center_position,\
														contrast,		 pstParams->contrast);
			PE_VCP_DISP_O24_QRd02(vcp_vsp_u0_ctrl_01,	saturation,		 pstParams->saturation,\
														brightness,		 pstParams->brightness);
		}
		else if(PE_CHECK_WIN1(win_id))
		{
			PE_VCP_DISP_O24_QRd03(vcp_vsp_u1_ctrl_00, 	enable, 		 pstParams->enable,\
														center_position, pstParams->center_position,\
														contrast,		 pstParams->contrast);
			PE_VCP_DISP_O24_QRd02(vcp_vsp_u1_ctrl_01,	saturation,		 pstParams->saturation,\
														brightness,		 pstParams->brightness);
		}
		else if(PE_CHECK_WIN2(win_id))
		{
			PE_VSD0_VERI_O24_RdFL(vsd_veri_vsp0_0);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp0_0,enable,pstParams->enable);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp0_0,center_position,pstParams->center_position);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp0_0,contrast,pstParams->contrast);
			PE_VSD0_VERI_O24_RdFL(vsd_veri_vsp0_1);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp0_1,saturation,pstParams->saturation);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp0_1,brightness,pstParams->brightness);
		}
		else if(PE_CHECK_WIN3(win_id))
		{
			PE_VSD0_VERI_O24_RdFL(vsd_veri_vsp1_0);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp1_0,enable,pstParams->enable);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp1_0,brightness,pstParams->brightness);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp1_0,contrast,pstParams->contrast);
			PE_VSD0_VERI_O24_RdFL(vsd_veri_vsp1_1);
			PE_VSD0_VERI_O24_Rd01(vsd_veri_vsp1_1,saturation,pstParams->saturation);
		}
		PE_DBG_CMN("get pstParams[%d] : enable:%d, center:%d, contrast:%d, brightness:%d, saturation:%d\n",\
			pstParams->win_id,pstParams->enable,pstParams->center_position,\
			pstParams->contrast,pstParams->brightness,pstParams->saturation);
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * set vcp saturation control
 *
 * @param   *pstParams [in] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetVcpSaturationCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	do {
		LX_PE_CMN_VCP_LEVEL_CTRL_T *pp = (LX_PE_CMN_VCP_LEVEL_CTRL_T *)pstParams;
		static LX_PE_CMN_VCP_LEVEL_CTRL_T prev[LX_PE_WIN_NUM] __attribute__((unused));
		__attribute__((unused)) static UINT32 chk = 0x0;
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		//PE_CHECK_DUPLICATE(LX_PE_CMN_VCP_LEVEL_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_DBG_CMN("duplicated DB : LX_PE_CMN_VCP_LEVEL_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_DBG_CMN("set pstParams[%d] : enable:%d, center:%d, contrast:%d, brightness:%d, saturation:%d\n",\
			pstParams->win_id,pstParams->enable,pstParams->center_position,\
			pstParams->contrast,pstParams->brightness,pstParams->saturation);

		if(PE_CHECK_WIN1(pstParams->win_id))
		{
			#if 0	//20200611, vcp_vsp_u1 moved to fw setting for estreamer(QEVENTTWEN-25839)(TVPM-12053)
			PE_VCP_DISP_O24_QWr03(vcp_vsp_u1_ctrl_00, 	enable, 		 GET_BITS(pstParams->enable,		 0,1),\
														center_position, GET_BITS(pstParams->center_position,0,8),\
														contrast,		 GET_BITS(pstParams->contrast,		 0,10));
			PE_VCP_DISP_O24_QWr02(vcp_vsp_u1_ctrl_01,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
														brightness,		 GET_BITS(pstParams->brightness,	 0,10));
			#endif
			#if 1	/* O24_VERI */
			do {
				PE_VSD0_VERI_O24_QWr02(vsd_veri_vsp1_1,	saturation,		GET_BITS(pstParams->saturation,	0,8),
														saturation_en,	GET_BITS(pstParams->enable,		0,1));
			} while(0);
			#endif
			#if 0	/* O24F22_APB */
			do {
				if (!gPE_CHPI_DDR_O24)	break;
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd1_veri_vsp_1.saturation,GET_BITS(pstParams->saturation,0,8));
				PE_CHPI_APB0_O24F22_Wr(fsw0.vsd1_veri_vsp_1.saturation_en,GET_BITS(pstParams->enable,0,1));
				//PE_CHPI_APB0_O24F22_Wr(fsw0.vsd1_veri_vsp_1.brightness,GET_BITS(pstParams->brightness,0,10));
				PE_CHPI_APB0_O24F22_WrFL(fsw0.vsd1_veri_vsp_1.udata32);
				PE_INF_O24_IncChipInfoApbCount(PE_INF_O24_CHPI_APB_FSW0);
			} while(0);
			#endif
		}
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
/**
 * set bypass blocks
 *
 * @param   *pstParams [in] LX_PE_CMN_BYPASS_BLOCKS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_O24_SetBypassBlock(LX_PE_CMN_BYPASS_BLOCKS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_O24_BRINGUP
	static UINT32 bypass_flag = 0;
	static UINT32 bypass_param[6];             ///< 0:psp_en 1:dce_en 2:logo_en 3:drc_en 4:pcc_en 5:cw_en
	do {
		CHECK_KNULL(pstParams);
		PE_DBG_CMN("set pstParams: u32BlockMask = 0x%08x, bOnOff = %d, bypass_flag = %d\n",
			pstParams->u32BlockMask, pstParams->bOnOff, bypass_flag);

		if (pstParams->bOnOff)
		{
			if(pstParams->u32BlockMask & 0x1)//sharpness
			{
				PE_SR_2K_SHC_O24_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x1);
				PE_SR_2K_SHP0_O24_QWr02(shp_core_ctrl_00,reg_top_core_bypass, 0x1,\
														reg_top_core_detour, 0x1);
				PE_SR_2K_SHP1_O24_QWr02(shp_core_ctrl_00,reg_top_core_bypass, 0x1,\
														reg_top_core_detour, 0x1);
				PE_VSD_SHP_O24_QWr01(shp_core_ctrl_00,	reg_top_core_bypass,	0x1);
			}
			if(pstParams->u32BlockMask & 0x2)//object contrast
			{
				#if 0
				PE_VSD_OBC_O_O24_QRd01(psp_ctrl02, reg_psp_en,  bypass_param[0]);
				PE_VSD_OBC_O_O24_QWr01(psp_ctrl02, reg_psp_en,  0x0);
				PE_VSD_OBC_F_O24_QWr01(psp_ctrl02, reg_psp_en,  0x0);
				#endif
				//ret = PE_SHP_HW_O24_SetBypassObc(1);
				PE_VSD_OBE_O24_QWr01(reg_obe_ctrl_000, reg_obe_en, 0x0);
			}
			if(pstParams->u32BlockMask & 0x4)//color contrast
			{
				//PE_CE_PE1_O24_QWr01(pe1_top_ctrl_02,	master_en,	0x0);
				//PE_CO_PE1_O24_QWr01(pe1_top_ctrl_02,	master_en,	0x0);
				PE_CC_PE1_O24_QRd01(pe1_dce_ctrl_00,  dynamic_contrast_en, bypass_param[1]);
				PE_CC_PE1_O24_QWr01(pe1_dce_ctrl_00, dynamic_contrast_en, 0x0);
				PE_CC2_PE1_O24_QRd01(pe1_logo_ctrl_00, reg_logo_blend_en, bypass_param[2]);
				PE_CC2_PE1_O24_QWr01(pe1_logo_ctrl_00, reg_logo_blend_en, 0x0);
				PE_CC_PE1_O24_QRd01(pe1_drc_ctrl_00,  reg_drc_en, bypass_param[3]);
				PE_CC_PE1_O24_QWr01(pe1_drc_ctrl_00,  reg_drc_en, 0x0);
				PE_CC_PE1_O24_QWr01(pe1_cen_ctrl_00, cen_detour,0x1);
				PE_CC_PE1_O24_QRd01(pe_pcc_ctrl, reg_pcc_en, bypass_param[4]);
				PE_CC_PE1_O24_QWr01(pe_pcc_ctrl, reg_pcc_en, 0x0);
				PE_VSD_DTM_O24_QWr01(dtm_top_ctrl_02, reg_master_en, 0x0);
				PE_CC_PE1_O24_QWr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x0);
				PE_CC2_PE1_O24_QRd01(pe1_cw_ctrl_00, reg_cw_en, bypass_param[5]);
				PE_CC2_PE1_O24_QWr01(pe1_cw_ctrl_00, reg_cw_en, 0x0);
			}
			if(pstParams->u32BlockMask & 0x4)//vsp
			{
				PE_CC2_PE1_O24_QWr01(pe1_vspyc_ctrl_00, enable, 0x0);
			}
			if(pstParams->u32BlockMask & 0x8000)//csc bypass
			{
				//TODO:
			}
			bypass_flag =0x1;
			PE_DBG_CMN("bypass ON!! save param: psp_en:%d, dce_en:%d, logo_en:%d, drc_en:%d, pcc_en:%d\n",\
				bypass_param[0],bypass_param[1],bypass_param[2],bypass_param[3],bypass_param[4]);
		}
		else
		{
			if(pstParams->u32BlockMask & 0x1)//sharpness
			{
				PE_SR_2K_SHC_O24_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x0);
				PE_SR_2K_SHP0_O24_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x0);
				PE_SR_2K_SHP1_O24_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x0);
				PE_VSD_SHP_O24_QWr01(shp_core_ctrl_00,	reg_top_core_bypass, 0x0);
			}
			if(pstParams->u32BlockMask & 0x2)//object contrast
			{
				#if 0
				PE_VSD_OBC_O_O24_QWr01(psp_ctrl02, reg_psp_en,  GET_BITS(bypass_param[0],0,1));
				PE_VSD_OBC_F_O24_QWr01(psp_ctrl02, reg_psp_en,  GET_BITS(bypass_param[0],0,1));
				#endif
				//ret = PE_SHP_HW_O24_SetBypassObc(0);
				PE_VSD_OBE_O24_QWr01(reg_obe_ctrl_000, reg_obe_en, 0x1);
			}
			if(pstParams->u32BlockMask & 0x4)//color contrast
			{
				//PE_CE_PE1_O24_QWr01(pe1_top_ctrl_02,	master_en,	0x1);
				//PE_CO_PE1_O24_QWr01(pe1_top_ctrl_02,	master_en,	0x1);
				PE_CC_PE1_O24_QWr01(pe1_dce_ctrl_00, dynamic_contrast_en, 	GET_BITS(bypass_param[1],0,1));
				PE_CC2_PE1_O24_QWr01(pe1_logo_ctrl_00, reg_logo_blend_en, 	GET_BITS(bypass_param[2],0,1));
				PE_CC_PE1_O24_QWr01(pe1_drc_ctrl_00,reg_drc_en, 			GET_BITS(bypass_param[3],0,1));
				PE_CC_PE1_O24_QWr01(pe1_cen_ctrl_00, cen_detour,0x0);
				PE_CC_PE1_O24_QWr01(pe_pcc_ctrl, reg_pcc_en,				GET_BITS(bypass_param[4],0,1));
				PE_VSD_DTM_O24_QWr01(dtm_top_ctrl_02, reg_master_en, 0x1);
				PE_CC_PE1_O24_QWr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x0);
				PE_CC2_PE1_O24_QWr01(pe1_cw_ctrl_00, reg_cw_en, GET_BITS(bypass_param[5],0,1));
			}
			if(pstParams->u32BlockMask & 0x4)//vsp
			{
				PE_CC2_PE1_O24_QWr01(pe1_vspyc_ctrl_00, enable, 0x1);
			}
			if(pstParams->u32BlockMask & 0x8000)//csc
			{
				//TODO:
			}
			bypass_flag = 0x0;
			PE_DBG_CMN("bypass OFF!! set param: psp_en:%d, dce_en:%d, logo_en:%d, drc_en:%d, pcc_en:%d\n",\
			bypass_param[0],bypass_param[1],bypass_param[2],bypass_param[3],bypass_param[4]);
		}
		PE_PRINT_NOTI("[CMN]block:0x%x,on:%d\n",pstParams->u32BlockMask,pstParams->bOnOff);
		PE_INF_HW_O24_BACKUP_TRACE("[CMN]block:0x%x,on:%d",pstParams->u32BlockMask,pstParams->bOnOff);
	} while(0);
	#endif
	return ret;
}
/**
 * get tag mem info
 *
 * @param   *pstParams [in/out] LX_PE_IPC_SYSTEM_MEM_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_LGSR_HW_O24_GetMemInfo(void *pstParams)
{
	int ret = RET_ERROR;
	#ifndef PE_HW_O24_BRINGUP
	LX_MEMCFG_T *pstMem = (LX_MEMCFG_T *)pstParams;
	do {
		CHECK_KNULL(pstMem);
		pstMem->base = gPeMem[0].base + 0x100000;
		pstMem->size = 0x300400;
		PE_PRINT_NOTI("[lgsr]Meminfo base : 0x%08x, size : 0x%08x\n", pstMem->base, pstMem->size);
		ret = RET_OK;
	} while(0);
	#endif /*PE_HW_O24_BRINGUP*/
	return ret;
}
