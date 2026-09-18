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

/** @file pe_cmn_hw_e60.c
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

#include "pe_hw_e60.h"
#include "pe_reg_e60.h"
#include "pe_fwi_e60.h"
#include "pe_inf_e60.h"
#include "pe_cmn_hw_e60.h"
#include "pe_dcm_hw_e60.h"
#include "pe_shp_hw_e60.h"
#include "pe_nrd_hw_e60.h"
#include "pe_hst_hw_e60.h"
#include "cvd_module.h"

#include "pe_lgsr_osdy_weight_set_00_e60.h"
//#include "pe_lgsr_osdy_weight_set_01_e60.h"
#include "pe_lgsr_osdy_apb_set_00_e60.h"
//#include "pe_lgsr_osdy_apb_set_01_e60.h"
#include "pe_lgsr_osda_weight_set_00_e60.h"
//#include "pe_lgsr_osda_weight_set_01_e60.h"
#include "pe_lgsr_osda_apb_set_00_e60.h"
//#include "pe_lgsr_osda_apb_set_01_e60.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* Enabling this macro will DISABLE LGSI code refactoring changes, so enable only if there is
any issue in LGSI refactored code. This provision is only for cross checking with original
source. It can be removed in the next version of the code*/

/* use vgain, voffset instead of lvctrl, when tnr,sc mem share mode */
#undef PE_CMN_HW_E60_USE_VGAIN_FOR_LVCTRL
/* use lvctrl of IMX instead of ND0 */
#define PE_CMN_HW_E60_USE_LVCTRL_OF_IMX

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMN_HW_E60_ERROR	printk
#define PE_CMN_HW_E60_DBG_PRINT(fmt,args...)	\
	if(_g_cmn_hw_e60_trace) printk("[%x,%x][%s,%d] "fmt,PE_CHIP_VER,g_pe_kdrv_ver_mask,__F__,__L__,##args)
#define PE_CMN_HW_E60_CHECK_CODE(_checker,_action,fmt,args...)	\
	if(_checker){PE_CMN_HW_E60_ERROR(fmt,##args);_action;}
#if 0
#define PE_LGSR_DDR_REG_E60_SEC_TYPE_TO_BUFF_APB(_x)		(\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_00  )? lgsr_inf_apb_set_00_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_01  )? lgsr_inf_apb_set_01_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_02  )? lgsr_inf_apb_set_02_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_03  )? lgsr_inf_apb_set_03_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_04  )? lgsr_inf_apb_set_04_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_05  )? lgsr_inf_apb_set_05_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_06  )? lgsr_inf_apb_set_06_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_07  )? lgsr_inf_apb_set_07_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_10  )? lgsr_inf_apb_set_10_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_11  )? lgsr_inf_apb_set_11_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_12  )? lgsr_inf_apb_set_12_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_13  )? lgsr_inf_apb_set_13_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_14  )? lgsr_inf_apb_set_14_e60:\
	lgsr_inf_apb_set_00_e60)

#define PE_LGSR_DDR_REG_E60_SEC_TYPE_TO_BUFF_WEIGHT(_x)		(\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_00  )? lgsr_inf_weight_set_00_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_01  )? lgsr_inf_weight_set_01_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_02  )? lgsr_inf_weight_set_02_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_03  )? lgsr_inf_weight_set_03_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_04  )? lgsr_inf_weight_set_04_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_05  )? lgsr_inf_weight_set_05_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_06  )? lgsr_inf_weight_set_06_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_07  )? lgsr_inf_weight_set_07_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_10  )? lgsr_inf_weight_set_10_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_11  )? lgsr_inf_weight_set_11_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_12  )? lgsr_inf_weight_set_12_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_13  )? lgsr_inf_weight_set_13_e60:\
	((_x)==PE_LGSR_DDR_E60_SEC_INF_SET_14  )? lgsr_inf_weight_set_14_e60:\
	lgsr_inf_weight_set_00_e60)

#define PE_LGSR_DDR_REG_E60F20_SEC_TYPE_TO_BUFF_APB(_x)		(\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_00  )? lgsr_inf_apb_set_00_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_01  )? lgsr_inf_apb_set_01_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_02  )? lgsr_inf_apb_set_02_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_03  )? lgsr_inf_apb_set_03_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_04  )? lgsr_inf_apb_set_04_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_05  )? lgsr_inf_apb_set_05_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_06  )? lgsr_inf_apb_set_06_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_07  )? lgsr_inf_apb_set_07_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_10  )? lgsr_inf_apb_set_10_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_11  )? lgsr_inf_apb_set_11_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_12  )? lgsr_inf_apb_set_12_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_13  )? lgsr_inf_apb_set_13_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_14  )? lgsr_inf_apb_set_14_e60:\
	lgsr_inf_apb_set_00_e60)

#define PE_LGSR_DDR_REG_E60F20_SEC_TYPE_TO_BUFF_WEIGHT(_x)		(\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_00  )? lgsr_inf_weight_set_00_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_01  )? lgsr_inf_weight_set_01_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_02  )? lgsr_inf_weight_set_02_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_03  )? lgsr_inf_weight_set_03_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_04  )? lgsr_inf_weight_set_04_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_05  )? lgsr_inf_weight_set_05_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_06  )? lgsr_inf_weight_set_06_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_07  )? lgsr_inf_weight_set_07_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_10  )? lgsr_inf_weight_set_10_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_11  )? lgsr_inf_weight_set_11_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_12  )? lgsr_inf_weight_set_12_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_13  )? lgsr_inf_weight_set_13_e60:\
	((_x)==PE_LGSR_DDR_E60F20_SEC_INF_SET_14  )? lgsr_inf_weight_set_14_e60:\
	lgsr_inf_weight_set_00_e60)

#endif
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern UINT32	g_pe_csc_e60_post_bypass_mode;
extern LX_DE_IPC_SYSTEM_INFO_T g_pe_lgsr_mem_info;

/*----------------------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
const UINT32 g_pe_cmn_hw_e60_crc_table[256] = {
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
static int PE_CMN_HW_E60_DownloadModeDb(void);
static int PE_CMN_HW_E60_DownloadCvdDb(void);
static int PE_CMN_HW_E60_InitChipInfo(PE_CFG_CTRL_T *pstParams);
static int PE_CMN_HW_E60F20_DownloadDb(PE_CFG_CTRL_T *pstParams);
static int PE_CMN_HW_E60F20_DownloadModeDb(void);
static int PE_CMN_HW_E60_LGSR_DownloadDb(void);
#if 0
static int PE_CMN_HW_E60_DownloadLGSROneSet(UINT32 setNum);
static int PE_CMN_HW_E60F20_DownloadLGSROneSet(UINT32 setNum);
#endif
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _g_cmn_hw_e60_trace=0x0;		//default should be off.
static PE_CMN_HW_E60_SETTINGS_T _g_pe_cmn_hw_e60_info;

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
int PE_CMN_HW_E60_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		memset(&_g_pe_cmn_hw_e60_info, 0, sizeof(PE_CMN_HW_E60_SETTINGS_T));
		if(PE_KDRV_VER_E60)
		{
			/* E60F20_APB : InitChipInfo should be on the top of pe_init */
			ret = PE_CMN_HW_E60_InitChipInfo(pstParams);
			PE_CMN_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_CMN_HW_E60_InitChipInfo() error.\n",__F__,__L__);
			/**********************************************************/
			PE_SHP_E60_QWr01(shp_core_ctrl_00,reg_top_mode_3d,0x0);
			//PE_CC_PE1_E60_QWr01(pe1_top_ctrl_02,mode_3d,0x0);
			PE_CMN_HW_E60_DBG_PRINT("vsp-yc,rgb, lvctrl : enable.\n");
			#ifdef PE_CMN_HW_E60_USE_LVCTRL_OF_IMX
			PE_IMX_E60_RdFL(ctrl_m0_y_level_ctrl);
			PE_IMX_E60_Wr01(ctrl_m0_y_level_ctrl,reg_lvctrl_en,0x1);
			PE_IMX_E60_Wr01(ctrl_m0_y_level_ctrl,level_offset,0x200);
			PE_IMX_E60_Wr01(ctrl_m0_y_level_ctrl,level_center,0x80);
			PE_IMX_E60_Wr01(ctrl_m0_y_level_ctrl,level_gain,0x80);
			PE_IMX_E60_WrFL(ctrl_m0_y_level_ctrl);
			#endif
			PE_ND0_E60_QWr04(lvcrtl_ctrl_00,     enable,             0x1, \
                                                    y_offset,           0x200, \
                                                    center_position,    0x80, \
                                                    y_gain,             0x80);
			/* vspyc center_position 0x0->0x10(related with 16~235 range) */
			PE_CC2_PE1_E60_QWr05(pe1_vspyc_ctrl_00,enable,            0x1, \
                                                     graycolor_enable,  0x0, \
                                                     color_only_enable, 0x0, \
                                                     center_position,   0x10, \
                                                     contrast,          0x200);
			PE_CC2_PE1_E60_QWr02(pe1_vspyc_ctrl_01,saturation,        0x80,\
                                                     brightness,        0x200);
			PE_CC_PE1_E60_QWr01(pe1_cen_ctrl_02,  ihsv_vgain,        0x80);
			PE_CC_PE1_E60_QWr02(pe1_cen_ctrl_03,  ihsv_voffset,      0x80, \
                                                     ihsv_hoffset,      0x80);
			#if 1	/* E60F20_APB */
			do {
				if (pstParams->resume_mode == 1)	break;//if qsm,skip

				/* addr */
				PE_CHPI_APB0_E60F20_QWr(cmn0.pe1_vspyc_ctrl_00.uaddr32,0xF0343000);
				PE_CHPI_APB0_E60F20_QWr(cmn0.pe1_vspyc_ctrl_01.uaddr32,0xF0343004);
				PE_CHPI_APB0_E60F20_QWr(cmn0.pe1_cen_ctrl_03.uaddr32,0xF03426DC);

				/* init */
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_00.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_00.enable,1);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_00.r_yc2rgb_en,1);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_00.center_position,0x10);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_00.contrast,0x200);
				PE_CHPI_APB0_E60F20_WrFL(cmn0.pe1_vspyc_ctrl_00.udata32);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_01.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_01.saturation_target,0x80);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_01.saturation,0x80);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_01.brightness,0x200);
				PE_CHPI_APB0_E60F20_WrFL(cmn0.pe1_vspyc_ctrl_01.udata32);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_cen_ctrl_03.udata32,0x0);//should set zero firstly(init)(bit settings)
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_cen_ctrl_03.ihsv_hoffset,0x80);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_cen_ctrl_03.ihsv_soffset,0x80);
				PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_cen_ctrl_03.ihsv_voffset,0x80);
				PE_CHPI_APB0_E60F20_WrFL(cmn0.pe1_cen_ctrl_03.udata32);

				/* header */
				PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_CMN0);

				PE_PRINT_NOTI("[APB][CMN]done(resume:%d)\n",pstParams->resume_mode);
				PE_INF_HW_E60_BACKUP_CHPI0("[APB][CMN]done(resume:%d)",pstParams->resume_mode);
			} while(0);
			#endif
			#if 1	/* E60F20_TBL */
			do {
				if (pstParams->resume_mode == 1)	break;//if qsm,skip

				/* addr */
				PE_CHPI_TBL0_E60F20_QWr(cco.pe1_dce_ctrl_00.uaddr32,0xF0342720);
				PE_CHPI_TBL0_E60F20_QWr(cco.pe1_dse_ctrl_00.uaddr32,0xF0342770);

				/* init */
				PE_CHPI_TBL0_E60F20_QWr(cco.pe1_dce_ctrl_00.udata32,0x050000A1);
				PE_CHPI_TBL0_E60F20_QWr(cco.pe1_dse_ctrl_00.udata32,0x000000A3);

				/* count */
				PE_INF_E60_IncChipInfoCount(PE_INF_E60_CHPI_CNT_CCO);

				PE_PRINT_NOTI("[TBL][CMN]done(resume:%d)\n",pstParams->resume_mode);
				PE_INF_HW_E60_BACKUP_CHPI1("[TBL][CMN]done(resume:%d)",pstParams->resume_mode);
			} while(0);
			#endif
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_GetMemInfo(unsigned int *base, unsigned int *size)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(base);
		CHECK_KNULL(size);
		if(PE_KDRV_VER_E60)
		{
			*base = PE_E60_DDR_DB0_BASE;
			*size = PE_E60_DDR_DB0_SIZE+PE_E60_DDR_DB1_SIZE+PE_E60_DDR_DB2_SIZE+PE_E60_DDR_DB3_SIZE;
			PE_PRINT_NOTI("base:%08x, size:%d\n", *base, *size);
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
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
int PE_CMN_HW_E60_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	PE_CMN_HW_E60_SETTINGS_T *pInfo = &_g_pe_cmn_hw_e60_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_E60_DBG_PRINT("set[%d] type:0x%x, print:0x%x, bypass:0x%x, fwc_en,dbg:%d,%d\n",\
			pstParams->win_id,pstParams->type,pstParams->print_lvl,pstParams->bypass,\
			pstParams->fwc.ctrl_en,pstParams->fwc.dbg_en);
		/* set print level */
		if(pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmn_hw_e60_trace = (pstParams->print_lvl & (0x1<<PE_ITEM_PKTMODL(CMN)))? 0x1:0x0;
			pInfo->dbg_print_lvl = pstParams->print_lvl;
			PE_FWI_E60_SetDbgPrint(_g_cmn_hw_e60_trace);
		}
		/* set bypass */
		if(pstParams->type&LX_PE_DBG_BY)
		{
			if(PE_KDRV_VER_E60)
			{
				if(pstParams->bypass & (0x1<<PE_ITEM_PKTMODL(CMN)))
				{
					PE_CMN_HW_E60_DBG_PRINT("cont,bri,sat disable, hue bypass.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_ND0_E60_QWr01(lvcrtl_ctrl_00,enable,0x0);
						PE_CC2_PE1_E60_QWr01(pe1_vspyc_ctrl_00,enable,0x0);
						PE_CC_PE1_E60_QWr01(pe1_cen_ctrl_03,ihsv_hoffset,0x80);
					}
				}
				else
				{
					PE_CMN_HW_E60_DBG_PRINT("cont,bri,sat enable.\n");
					if(PE_CHECK_WIN0(pstParams->win_id))
					{
						PE_ND0_E60_QWr01(lvcrtl_ctrl_00,enable,0x1);
						PE_CC2_PE1_E60_QWr01(pe1_vspyc_ctrl_00,enable,0x1);
					}
				}
			}
			else
			{
				PE_CMN_HW_E60_DBG_PRINT("do nothing.\n");	ret = RET_OK;
			}
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				pInfo->dbg_bypass[LX_PE_WIN_0] = pstParams->bypass;
			}
			if(PE_CHECK_WIN1(pstParams->win_id))
			{
				pInfo->dbg_bypass[LX_PE_WIN_1] = pstParams->bypass;
			}
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

/**
 * get cmn debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_E60_GetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	PE_CMN_HW_E60_SETTINGS_T *pInfo = &_g_pe_cmn_hw_e60_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_CHECK_WIN0(win_id))
		{
			pstParams->bypass = pInfo->dbg_bypass[LX_PE_WIN_0];
		}
		if(PE_CHECK_WIN1(win_id))
		{
			pstParams->bypass = pInfo->dbg_bypass[LX_PE_WIN_1];
		}
		pstParams->print_lvl = pInfo->dbg_print_lvl;
		if(PE_KDRV_VER_E60)
		{
			PE_FWI_E60_SETTINGS_T param;
			pstParams->fwc.dbg_en = PE_FWI_E60_GetDbgPrint();
			ret = PE_FWI_E60_GetCurFwiSettings(&param);
			PE_CMN_HW_E60_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_E60_GetCurFwiSettings() error.\n",__F__,__L__);
			pstParams->fwc.ctrl_en = param.fw_ctrl.enable;
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("not use fwc.\n");
			pstParams->fwc.dbg_en = 0;
			pstParams->fwc.ctrl_en = 0;
		}
		PE_CMN_HW_E60_DBG_PRINT("get[%d] type:0x%x, print:0x%x, bypass:0x%x, fwc_en,dbg:%d,%d\n",\
			pstParams->win_id,pstParams->type,pstParams->print_lvl,pstParams->bypass,\
			pstParams->fwc.ctrl_en,pstParams->fwc.dbg_en);
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_SetContrast(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_CMN1_CONTRAST_T *pp = (LX_PE_CMN1_CONTRAST_T *)pstParams;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_CMN_HW_E60_DBG_PRINT("set pstParams[%d] : %d\n",pp->win_id,pp->contrast);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CC2_PE1_E60_QWr01(pe1_vspyc_ctrl_00, contrast, GET_BITS(pp->contrast,0,10));
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_00.contrast,GET_BITS(pp->contrast,0,10));
					PE_CHPI_APB0_E60F20_WrFL(cmn0.pe1_vspyc_ctrl_00.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_CMN0);
					PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_00.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_00.udata32),\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_cen_ctrl_03.udata32));
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_GetContrast(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	LX_PE_CMN1_CONTRAST_T *pp = (LX_PE_CMN1_CONTRAST_T *)pstParams;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		win_id = PE_GET_CHECKED_WINID(pp->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC2_PE1_E60_QRd01(pe1_vspyc_ctrl_00, contrast, pp->contrast);
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_E60_QRd01(pe1_vspyc_ctrl_00, contrast, pstParams->contrast);
			}*/
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_E60_DBG_PRINT("get pstParams[%d] : %d\n",pp->win_id,pp->contrast);
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_SetBrightness(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_CMN1_BRIGHTNESS_T *pp = (LX_PE_CMN1_BRIGHTNESS_T *)pstParams;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		PE_CMN_HW_E60_DBG_PRINT("set pstParams[%d] : %d\n",pp->win_id,pp->brightness);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pp->win_id))
			{
				PE_CC2_PE1_E60_QWr01(pe1_vspyc_ctrl_01, brightness, GET_BITS(pp->brightness,0,10));
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_01.brightness,GET_BITS(pp->brightness,0,10));
					PE_CHPI_APB0_E60F20_WrFL(cmn0.pe1_vspyc_ctrl_01.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_CMN0);
					PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_00.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_00.udata32),\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_cen_ctrl_03.udata32));
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_GetBrightness(void *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	LX_PE_CMN1_BRIGHTNESS_T *pp = (LX_PE_CMN1_BRIGHTNESS_T *)pstParams;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pp->win_id);
		win_id = PE_GET_CHECKED_WINID(pp->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC2_PE1_E60_QRd01(pe1_vspyc_ctrl_01, brightness, pp->brightness);
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_E60_QRd01(pe1_vspyc_ctrl_01, brightness, pstParams->brightness);
			}*/
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_E60_DBG_PRINT("get pstParams[%d] : %d\n",pp->win_id,pp->brightness);
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_SetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_E60_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->saturation);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC2_PE1_E60_QWr01(pe1_vspyc_ctrl_01, saturation, GET_BITS(pstParams->saturation,0,8));
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_vspyc_ctrl_01.saturation,GET_BITS(pstParams->saturation,0,8));
					PE_CHPI_APB0_E60F20_WrFL(cmn0.pe1_vspyc_ctrl_01.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_CMN0);
					PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_00.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_00.udata32),\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_cen_ctrl_03.udata32));
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_GetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC2_PE1_E60_QRd01(pe1_vspyc_ctrl_01, saturation, pstParams->saturation);
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_E60_QRd01(pe1_vspyc_ctrl_01, saturation, pstParams->saturation);
			}*/
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_E60_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->saturation);
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_SetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		PE_CMN_HW_E60_DBG_PRINT("set pstParams[%d] : %d\n",pstParams->win_id,pstParams->hue);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_CC_PE1_E60_QWr01(pe1_cen_ctrl_03, ihsv_hoffset, GET_BITS(pstParams->hue,0,8));
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(cmn0.pe1_cen_ctrl_03.ihsv_hoffset,GET_BITS(pstParams->hue,0,8));
					PE_CHPI_APB0_E60F20_WrFL(cmn0.pe1_cen_ctrl_03.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_CMN0);
					PE_PRINT_CMN("shdw:0x%08x:0x%08x|0x%08x:0x%08x|0x%08x:0x%08x\n",\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_00.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_00.udata32),\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_01.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_vspyc_ctrl_01.udata32),\
						PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_cen_ctrl_03.uaddr32),PE_CHPI_APB0_E60F20_Rd(cmn0.pe1_cen_ctrl_03.udata32));
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_GetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_CC_PE1_E60_QRd01(pe1_cen_ctrl_03, ihsv_hoffset, pstParams->hue);
			}
			/*if(PE_CHECK_WIN1(win_id))
			{
				PE_CO_PE1_E60_QRd01(pe1_cen_ctrl_03, ihsv_hoffset, pstParams->hue);
			}*/
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_E60_DBG_PRINT("get pstParams[%d] : %d\n",pstParams->win_id,pstParams->hue);
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_SetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	#ifdef PE_CMN_HW_E60_USE_VGAIN_FOR_LVCTRL
	PE_CMN_HW_E60_SETTINGS_T *pInfo = &_g_pe_cmn_hw_e60_info;
	#endif
	do{
		CHECK_KNULL(pstParams);
		LX_PE_CMN_LEVEL_CTRL_T *pp = (LX_PE_CMN_LEVEL_CTRL_T *)pstParams;
		static LX_PE_CMN_LEVEL_CTRL_T prev[LX_PE_WIN_NUM];
		static UINT32 chk = 0x0;
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_CMN_LEVEL_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMN_HW_E60_DBG_PRINT("duplicated DB : LX_PE_CMN_LEVEL_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMN_HW_E60_DBG_PRINT("set pstParams[%d] : ofs:%d, center:%d, gain:%d, tp:%d\n",\
			pstParams->win_id,pstParams->offset,pstParams->center,\
			pstParams->gain,pstParams->tp_on);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				#ifdef PE_CMN_HW_E60_USE_LVCTRL_OF_IMX
				#if 0
					PE_ND0_E60_RdFL(ipp_fsw_ctrl_00);
					PE_ND0_E60_Wr01(ipp_fsw_ctrl_00,level_offset, GET_BITS(pstParams->offset,0,10));
					PE_ND0_E60_Wr01(ipp_fsw_ctrl_00,level_center, GET_BITS(pstParams->center,0,8));
					PE_ND0_E60_Wr01(ipp_fsw_ctrl_00,level_gain,   GET_BITS(pstParams->gain,0,8));
					PE_ND0_E60_WrFL(ipp_fsw_ctrl_00);
					PE_CEO_PE1_E60_QWr01(pe1_vspyc_ctrl_00,graycolor_enable,(pstParams->tp_on)? 0x1:0x0);
				#else
				PE_IMX_E60_RdFL(ctrl_m0_y_level_ctrl);
				PE_IMX_E60_Wr01(ctrl_m0_y_level_ctrl,reg_lvctrl_en,0x1);
				PE_IMX_E60_Wr01(ctrl_m0_y_level_ctrl,level_offset,GET_BITS(pstParams->offset,0,10));
				PE_IMX_E60_Wr01(ctrl_m0_y_level_ctrl,level_center,GET_BITS(pstParams->center,0,8));
				PE_IMX_E60_Wr01(ctrl_m0_y_level_ctrl,level_gain,GET_BITS(pstParams->gain,0,8));
				PE_IMX_E60_WrFL(ctrl_m0_y_level_ctrl);
				#endif
				#else //PE_CMN_HW_E60_USE_LVCTRL_OF_IMX
				#ifdef PE_CMN_HW_E60_USE_VGAIN_FOR_LVCTRL
				pInfo->cur_lvctrl_gain = GET_BITS(pstParams->gain,0,8);
				pInfo->cur_lvctrl_ofst = GET_BITS(pstParams->offset,0,10);
				PE_ND0_E60_QWr01(lvcrtl_ctrl_00, center_position, GET_BITS(pstParams->center,0,8));
				#else
				PE_ND0_E60_QWr03(lvcrtl_ctrl_00, y_offset,        GET_BITS(pstParams->offset,0,10), \
                                                    center_position, GET_BITS(pstParams->center,0,8), \
                                                    y_gain,          GET_BITS(pstParams->gain,0,8));
				#endif
				PE_CC2_PE1_E60_QWr01(pe1_vspyc_ctrl_00,graycolor_enable,(pstParams->tp_on)? 0x1:0x0);
				#endif
			}
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_GetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_ND0_E60_QRd03(lvcrtl_ctrl_00, y_offset,        pstParams->offset,\
                                                      center_position, pstParams->center,\
                                                      y_gain,          pstParams->gain);
				PE_CC2_PE1_E60_QRd01(pe1_vspyc_ctrl_00,graycolor_enable,pstParams->tp_on);
			}
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CMN_HW_E60_DBG_PRINT("get pstParams[%d] : ofs:%d, center:%d, gain:%d, tp:%d\n",\
			pstParams->win_id,pstParams->offset,pstParams->center,\
			pstParams->gain,pstParams->tp_on);
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_DownloadDb(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	PE_CFG_CTRL_T stParams;
	PE_DDR_E60_MD0_T *p_md0;
	PE_CMN_HW_E60_SETTINGS_T *p_inf = &_g_pe_cmn_hw_e60_info;
	PE_DDR_DB_SHDW_REG_E60_T *p_shdw_db = NULL;
	volatile PE_DDR_DB_PHYS_REG_E60_T *p_phys_db = NULL;
	volatile PE_DDR_DB_PHYS_REG_E60_T *p_phys_db_chk = NULL;
	volatile PE_LGSR_DDR_DB_PHYS_REG_E60_T *p_phys_lgsrdb_chk = NULL;
	p_shdw_db = gPE_DDR_DB_E60.shdw.data;
	p_phys_db = gPE_DDR_DB_E60.phys.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_E60)
		{
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
					p_phys_db_chk = (volatile PE_DDR_DB_PHYS_REG_E60_T *)gPE_DDR_DB_E60.phys.data;
					if (p_phys_db_chk->top_h.version != PE_DDR_E60_DB_VER || \
						p_phys_db_chk->top_h.db_base != PE_E60_DDR_DB0_BASE || \
						p_phys_db_chk->top_h.sec_num != PE_DDR_E60_SEC_NUM)
					{
						p_inf->db_initialized = 0;
						stParams.resume_mode = 0;//force normal
					}
					rmb();
				}
			}
			PE_PRINT_NOTI("[CMNDb]check(resume:%d <- %d,init:%d).\n",stParams.resume_mode,pstParams->resume_mode,p_inf->db_initialized);
			PE_INF_HW_E60_BACKUP_TRACE("[CMNDb]check(resume:%d <- %d,init:%d)",stParams.resume_mode,pstParams->resume_mode,p_inf->db_initialized);
			if (!p_inf->db_initialized)
			{
				/* move db mode setting here to avoid db mode clear on resume init */
				p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
				p_md0->shp_fw_en = 0;
				#ifdef PE_HW_E60_USE_FW_SRC_APL
				p_md0->hst_fw_en = 1;
				#else
				p_md0->hst_fw_en = 0;
				#endif
				p_md0->scl_fw_en = 1;
				p_md0->tnr_fw_en = 1;
				p_md0->dnr_fw_en = 0;
				if (!stParams.resume_mode)
				{
					p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_DDR_E60_DB_VER;
					p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_E60_DDR_DB0_BASE;
					p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_DDR_E60_SEC_NUM;
					/* *********************************************************************/
					/* Causion : Should be arranged in enum order **************************/
					/* *********************************************************************/
					/* mode : PE_DDR_E60_SEC_MODE(should be 1st one) */
					ret = PE_CMN_HW_E60_DownloadModeDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_CMN_HW_E60_DownloadModeDb() error.\n",__F__,__L__);
					/* drc : PE_DDR_E60_SEC_DRC_LUT */
					ret = PE_DCM_HW_E60_DownloadDrcDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_DCM_HW_E60_DownloadDrcDb() error.\n",__F__,__L__);
					/* cvd : PE_DDR_E60_SEC_CVD_DFLT */
					ret = PE_CMN_HW_E60_DownloadCvdDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_CMN_HW_E60_DownloadCvdDb() error.\n",__F__,__L__);
					/* scl : PE_DDR_E60_SEC_SCL_06T_M ~ PE_DDR_E60_SEC_SCL_04T_M */
					ret = PE_SHP_HW_E60_DownloadSclDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60_DownloadSclDb() error.\n",__F__,__L__);
					/* tnr : PE_DDR_E60_SEC_TNR_LUT ~ PE_DDR_E60_SEC_TNR_USER */
					ret = PE_NRD_HW_E60_DownloadTnrDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadTnrDb() error.\n",__F__,__L__);
					ret = PE_DCM_HW_E60_DownloadDrcCurvDbInit();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_DCM_HW_E60_DownloadDrcCurvDbInit() error.\n",__F__,__L__);
					ret = PE_NRD_HW_E60_DownloadTnr2ndDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadTnr2ndUserDb() error.\n",__F__,__L__);
					#if 1
					/* dnr : PE_DDR_E60_SEC_DNR_USER  */
					ret = PE_NRD_HW_E60_DownloadDnrInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadDnrInitDb() error.\n",__F__,__L__);
					/* nrd dcnt : PE_DDR_E60_SEC_DNR_DCNT_USER  */
					ret = PE_NRD_HW_E60_DownloadDnrDcntInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadDcntInitDb() error.\n",__F__,__L__);
					/* nrd dcnt : PE_DDR_E60_SEC_LED_DCNT_USER  */
					ret = PE_NRD_HW_E60_DownloadLedDcntInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadLedDcntInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_TNR_SQM  */
					ret = PE_NRD_HW_E60_DownloadTnrSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadDnrInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_TNR2ND_SQM  */
					ret = PE_NRD_HW_E60_DownloadTnr2ndSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadDnrInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_DNR_SQM  */
					ret = PE_NRD_HW_E60_DownloadDnrSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadDnrInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_DNR_DCNT_SQM  */
					ret = PE_NRD_HW_E60_DownloadDnrDcntSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadDnrInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_LED_DCNT_SQM  */
					ret = PE_NRD_HW_E60_DownloadLedDcntSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60_DownloadDnrInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_SHP_UI_SQM_2K  */
					ret = PE_SHP_HW_E60_DownloadShp2KSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60_DownloadShp2KSqmCmnInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_SHP_SQM_CMN_2K  */
					ret = PE_SHP_HW_E60_DownloadShp2KSqmDetailInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60_DownloadShp2KSqmDetailInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_SHP_UI_SQM_VSD  */
					ret = PE_SHP_HW_E60_DownloadShpSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60_DownloadShpSqmCmnInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_SHP_SQM_CMN_VSD  */
					ret = PE_SHP_HW_E60_DownloadShpSqmDetailInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60_DownloadShpSqmDetailInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_SHP_UI_SQM_4K  */
					ret = PE_SHP_HW_E60_DownloadSreSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60_DownloadSreSqmCmnInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_SHP_SQM_CMN_4K  */
					ret = PE_SHP_HW_E60_DownloadSreSqmDetailInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60_DownloadSreSqmDetailInitDb() error.\n",__F__,__L__);
					#endif
					wmb();
					ret = PE_CMN_HW_E60_LGSR_DownloadDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_CMN_HW_E60_LGSR_DownloadDb() error.\n",__F__,__L__);
				}
				else
				{
					#if 0	//TODO:
					rmb();
					p_phys_lgsrdb_chk = (volatile PE_LGSR_DDR_DB_PHYS_REG_E60_T *)gPE_LGSR_DDR_DB_E60.phys.data;
					if (p_phys_lgsrdb_chk->top_h.version == PE_LGSR_DDR_E60_DB_VER && \
						p_phys_lgsrdb_chk->top_h.db_base == PE_LGSR_DDR_E60_BASE_ADDR && \
						p_phys_lgsrdb_chk->top_h.sec_num == PE_LGSR_DDR_E60_SEC_NUM)
					{
						ret = PE_FWI_E60_LoadLGSRDbData(PE_LGSR_DDR_E60_BASE_ADDR);
						PE_CMN_HW_E60_CHECK_CODE(ret, break, \
							"[%s,%d] PE_FWI_E60_LoadLGSRDbData() error.\n",__F__,__L__);
						PE_PRINT_NOTI("DL lgsrdb done already.(base:0x%08x)\n",  PE_LGSR_DDR_E60_BASE_ADDR);
					}
					rmb();
					#endif
				}
				/* inform load db data */
				ret = PE_FWI_E60_LoadDbData(p_shdw_db->top_h.db_base);
				PE_CMN_HW_E60_CHECK_CODE(ret, break, \
					"[%s,%d] PE_FWI_E60_LoadDbData() error.\n",__F__,__L__);
				/* *********************************************************************/
				PE_PRINT_NOTI("DL db done.(md:0x%08x)(base:0x%08x)\n", p_inf->db_mode_data[0], PE_E60_DDR_DB0_BASE);
				p_inf->db_initialized = 1;
			}
			else
			{
				PE_PRINT_NOTI("DL db done already.(md:0x%08x)(base:0x%08x)\n", p_inf->db_mode_data[0], PE_E60_DDR_DB0_BASE);
				#if 0	//TODO:
				rmb();
				p_phys_lgsrdb_chk = (volatile PE_LGSR_DDR_DB_PHYS_REG_E60_T *)gPE_LGSR_DDR_DB_E60.phys.data;
				if (p_phys_lgsrdb_chk->top_h.version == PE_LGSR_DDR_E60_DB_VER && \
					p_phys_lgsrdb_chk->top_h.db_base == PE_LGSR_DDR_E60_BASE_ADDR && \
					p_phys_lgsrdb_chk->top_h.sec_num == PE_LGSR_DDR_E60_SEC_NUM)
				{
					ret = PE_FWI_E60_LoadLGSRDbData(PE_LGSR_DDR_E60_BASE_ADDR);
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_FWI_E60_LoadLGSRDbData() error.\n",__F__,__L__);
					PE_PRINT_NOTI("DL lgsrdb done already.(base:0x%08x)\n",  PE_LGSR_DDR_E60_BASE_ADDR);
				}
				rmb();
				#endif
			}
			#if 1
			ret = PE_CMN_HW_E60F20_DownloadDb(pstParams);
			PE_CMN_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] PE_CMN_HW_E60F20_DownloadDb() error.\n",__F__,__L__);
			#endif
			/* last step : if ext chip, bypass(psp,pe1) *//* E60F20_APB */
			do {
				LX_PE_CMN_BYPASS_BLOCKS_T block;
				PE_REG_E60_HW_OPT_T hw_opt = PE_REG_E60_GetDispOpt();
				if (hw_opt.external_chip==0)	break;
				block.u32BlockMask = 0x4;
				block.bOnOff = 1;
				ret = PE_CMN_HW_E60_SetBypassBlock(&block);
				PE_CMN_HW_E60_CHECK_CODE(ret,break,"[%s,%d] PE_CMN_HW_E60_SetBypassBlock() error.\n",__F__,__L__);
			} while(0);
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}
static int PE_CMN_HW_E60F20_DownloadDb(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
#ifndef PE_HW_E60_BRINGUP
	PE_CFG_CTRL_T stParams;
	PE_CMN_HW_E60_SETTINGS_T *p_inf = &_g_pe_cmn_hw_e60_info;
	PE_DDR_E60F20_MD0_T *p_md0;
	PE_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = NULL;
	volatile PE_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = NULL;
	volatile PE_DDR_DB_PHYS_REG_E60F20_T *p_phys_db_chk = NULL;
	volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *p_phys_dc_db_chk = NULL;
	//volatile PE_LGSR_DDR_DB_PHYS_REG_E60F20_T *p_phys_lgsrdb_chk = NULL;
	UINT32 load_data[3];
	UINT32 load_size;
	p_shdw_db = gPE_DDR_DB_E60F20.shdw.data;
	p_phys_db = gPE_DDR_DB_E60F20.phys.data;
	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_E60)
		{
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
					p_phys_db_chk = (volatile PE_DDR_DB_PHYS_REG_E60F20_T *)gPE_DDR_DB_E60F20.phys.data;
					//if ddr ruined - unnormal
					if (p_phys_db_chk->top_h.version != PE_DDR_E60F20_DB_VER || \
						p_phys_db_chk->top_h.db_base != PE_E60F20_DDR_BASE || \
						p_phys_db_chk->top_h.sec_num != PE_DDR_E60F20_SEC_NUM) 
					{
						p_inf->db2_initialized = 0;
						stParams.resume_mode = 0;//force normal
					}
					
					/* only for PE_DCM_HW_E60F20_DownloadLibDb */
					/* @resume, drv inform load db done instead platform */
					/* inform load db done *//* E60F20_APB */
					p_phys_dc_db_chk = (volatile PE_DCM_DDR_DB_PHYS_REG_E60F20_T *)gPE_DCM_DDR_DB_E60F20.phys.data;
					//if ddr ruined - unnormal
					if (p_phys_dc_db_chk->top_h.version == PE_DCM_DDR_E60F20_DB_VER || \
						p_phys_dc_db_chk->top_h.db_base == PE_E60F20_DCM_DDR_BASE || \
						p_phys_dc_db_chk->top_h.sec_num == PE_DCM_DDR_E60F20_SEC_NUM) 
					{
						do {
							UINT32 load_data[3];
							UINT32 load_size=0;
							load_data[0] = PE_E60F20_DCM_DDR_BASE;
							load_data[1] = sizeof(PE_DCM_DDR_DB_PHYS_REG_E60F20_T);
							load_data[2] = 3;
							load_size = (UINT32)(sizeof(UINT32)*3);
							ret = PE_FWI_E60_LoadDbDone(load_data,load_size);
							PE_CMN_HW_E60_CHECK_CODE(ret,break,"[%s,%d] PE_DCM_HW_E60F20_DownloadLibDb() error.\n",__F__,__L__);
							PE_PRINT_NOTI("[Db]DcmDbDone resume (0x%08x)(%d)(%d)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_size);
							PE_INF_HW_E60_BACKUP_TRACE("[Db]DcmDbDone resume (0x%08x)(%d)(%d)(size:%d)",load_data[0],load_data[1],load_data[2],load_size);
						} while(0);
					}
					rmb();
				}
			}
			PE_PRINT_NOTI("[CMNDb][E60F20]check(resume:%d <- %d,init2:%d).\n",stParams.resume_mode,pstParams->resume_mode,p_inf->db2_initialized);
			PE_INF_HW_E60_BACKUP_TRACE("[CMNDb][E60F20]check(resume:%d <- %d,init2:%d)",stParams.resume_mode,pstParams->resume_mode,p_inf->db2_initialized);
			if (!p_inf->db2_initialized)
			{
				/* move db mode setting here to avoid db mode clear on resume init */
				p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
				p_md0->shp_fw_en = 0;
				p_md0->hst_fw_en = 1;
				p_md0->scl_fw_en = 1;
				p_md0->tnr_fw_en = 1;
				p_md0->dnr_fw_en = 0;
				if (!stParams.resume_mode)
				{
					memset(p_phys_db,0,sizeof(PE_DDR_DB_PHYS_REG_E60F20_T));
					wmb();
					p_phys_db->top_h.version = p_shdw_db->top_h.version = PE_DDR_E60F20_DB_VER;
					p_phys_db->top_h.db_base = p_shdw_db->top_h.db_base = PE_E60F20_DDR_BASE;
					p_phys_db->top_h.sec_num = p_shdw_db->top_h.sec_num = PE_DDR_E60F20_SEC_NUM;
					PE_PRINT_NOTI("PE_E60F20_DDR_BASE: 0x%08x\n", PE_E60F20_DDR_BASE);
					/* *********************************************************************/
					/* Causion : Should be arranged in enum order **************************/
					/* *********************************************************************/
					/* mode : PE_DDR_E60_SEC_MODE(should be 1st one) */
					ret = PE_CMN_HW_E60F20_DownloadModeDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_CMN_HW_E60_DownloadModeDb() error.\n",__F__,__L__);
					/* drc : PE_DDR_E60F20_SEC_DRC_LUT */
					ret = PE_DCM_HW_E60F20_DownloadDrcDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_DCM_HW_E60F20_DownloadDrcDb() error.\n",__F__,__L__);
					/* scl : PE_DDR_E60_SEC_SCL_06T_M ~ PE_DDR_E60_SEC_SCL_04T_M */
					ret = PE_SHP_HW_E60F20_DownloadSclDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60F20_DownloadSclDb() error.\n",__F__,__L__);
				#if 1
					ret = PE_DCM_HW_E60F20_DownloadDrcCurvDbInit();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_DCM_HW_E60F20_DownloadDrcCurvDbInit() error.\n",__F__,__L__);
					/* tnr : PE_DDR_E60_SEC_TNR_LUT ~ PE_DDR_E60_SEC_TNR_USER */
					ret = PE_NRD_HW_E60F20_DownloadTnrDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60F20_DownloadTnrDb() error.\n",__F__,__L__);
					/* tnr : PE_DDR_E60_SEC_TNR_SQM  */
					ret = PE_NRD_HW_E60F20_DownloadTnrSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60F20_DownloadTnrSqmCmnInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_DNR_USER  */
					ret = PE_NRD_HW_E60F20_DownloadDnrInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60F20_DownloadDnrInitDb() error.\n",__F__,__L__);
					/* dnr : PE_DDR_E60_SEC_DNR_SQM  */
					ret = PE_NRD_HW_E60F20_DownloadDnrSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60F20_DownloadDnrSqmCmnInitDb() error.\n",__F__,__L__);
					/* nrd dcnt : PE_DDR_E60_SEC_DNR_DCNT_USER	*/
					ret = PE_NRD_HW_E60F20_DownloadDnrDcntInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60F20_DownloadDnrDcntInitDb() error.\n",__F__,__L__);
					/* nrd dcnt : PE_DDR_E60_SEC_DNR_DCNT_SQM  */
					ret = PE_NRD_HW_E60F20_DownloadDnrDcntSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60F20_DownloadDnrDcntSqmCmnInitDb() error.\n",__F__,__L__);
					/* led dcnt : PE_DDR_E60_SEC_LED_DCNT_USER	*/
					ret = PE_NRD_HW_E60F20_DownloadLedDcntInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60F20_DownloadLedDcntInitDb() error.\n",__F__,__L__);
					/* led dcnt : PE_DDR_E60_SEC_LED_DCNT_SQM  */
					ret = PE_NRD_HW_E60F20_DownloadLedDcntSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_NRD_HW_E60F20_DownloadLedDcntSqmCmnInitDb() error.\n",__F__,__L__);
					/* shp : PE_DDR_E60_SEC_SHP_UI_SQM_VSD	*/
					ret = PE_SHP_HW_E60F20_DownloadShpSqmCmnInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60F20_DownloadShpSqmCmnInitDb() error.\n",__F__,__L__);
					/* shp : PE_DDR_E60_SEC_SHP_SQM_CMN_VSD  */
					ret = PE_SHP_HW_E60F20_DownloadShpSqmDetailInitDb();
					PE_CMN_HW_E60_CHECK_CODE(ret, break, \
						"[%s,%d] PE_SHP_HW_E60F20_DownloadShpSqmDetailInitDb() error.\n",__F__,__L__);
				#endif
					wmb();
					/* E60F20_CRC */
					do {
						UINT32 i, j, ddr_size32, crc32 = 0xFFFFFFFF;
						volatile UINT32 *pddr_data32;
						UINT32 ddr_data32;
						UINT8 *pddr_data08;
						ddr_size32 = (sizeof(PE_DDR_DB_PHYS_REG_E60F20_T)>>2)-1;//except for crc
						pddr_data32 = (volatile UINT32 *)p_phys_db;
						pddr_data08 = (UINT8 *)&ddr_data32;
						PE_PRINT_NOTI("[CRC]S: size32:%d\n",ddr_size32);
						PE_INF_HW_E60_BACKUP_TRACE("[CRC]S: size32:%d",ddr_size32);
						for (i=0;i<ddr_size32;i++)
						{
							rmb();
							ddr_data32 = (UINT32)pddr_data32[i];
							rmb();

							j = ((int) (crc32 >> 24) ^ pddr_data08[0]) & 0xFF;
							crc32 = (crc32 << 8) ^ g_pe_cmn_hw_e60_crc_table[j];

							j = ((int) (crc32 >> 24) ^ pddr_data08[1]) & 0xFF;
							crc32 = (crc32 << 8) ^ g_pe_cmn_hw_e60_crc_table[j];

							j = ((int) (crc32 >> 24) ^ pddr_data08[2]) & 0xFF;
							crc32 = (crc32 << 8) ^ g_pe_cmn_hw_e60_crc_table[j];

							j = ((int) (crc32 >> 24) ^ pddr_data08[3]) & 0xFF;
							crc32 = (crc32 << 8) ^ g_pe_cmn_hw_e60_crc_table[j];
							#if 0
							PE_PRINT_NOTI("[%03d]data32:%08X,data08:%02X|%02X|%02X|%02X,table[%03d]:%08X,crc32:%08X\n",\
								i,ddr_data32,pddr_data08[0],pddr_data08[1],pddr_data08[2],pddr_data08[3],j,_g_pe_crc_table[j],crc32);
						#endif
						}
						p_phys_db->crc = ~crc32;
						wmb();
						PE_PRINT_NOTI("[CRC]E: crc:0x%08X <- 0x%08X\n",~crc32,crc32);
						PE_INF_HW_E60_BACKUP_TRACE("[CRC]E: crc:0x%08X <- 0x%08X",~crc32,crc32);
					} while(0);
				}
				p_inf->db2_initialized = 1;
			}
			/* inform load db done *//* E60F20_APB */
			do {
				UINT32 load_data[3];
				UINT32 load_size=0;
			#if 0
				UINT32 sec_typ;
				UINT32 ddr_total=0;
				//ret = PE_CMN_HW_E60_GetMemInfo(&load_data[0],&load_data[1]);
				//PE_CMN_HW_E60_CHECK_CODE(ret, break, "[%s,%d] PE_CMN_HW_E60_GetMemInfo() error.\n",__F__,__L__);
				for (sec_typ=0; sec_typ<PE_DDR_E60F20_SEC_NUM; sec_typ++)
				{
					ddr_total += p_shdw_db->top_h.sec_size[sec_typ];
				}
			#endif
				load_data[0] = PE_E60F20_DDR_BASE;
				load_data[1] = sizeof(PE_DDR_DB_PHYS_REG_E60F20_T);
				load_data[2] = 0;
				load_size = (UINT32)(sizeof(UINT32)*3);
				ret = PE_FWI_E60_LoadDbDone(load_data,load_size);
				PE_CMN_HW_E60_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_E60_LoadDbDone() error.\n",__F__,__L__);
				PE_PRINT_NOTI("[Db]LoadDbDone(0x%08x)(%d)(%d)(size:%d)\n",load_data[0],load_data[1],load_data[2],load_size);
				PE_INF_HW_E60_BACKUP_TRACE("[Db]LoadDbDone(0x%08x)(%d)(%d)(size:%d)",load_data[0],load_data[1],load_data[2],load_size);
			} while(0);
		#ifndef PE_CHPI_DEF_E60F20_USE_REG
			/* inform headers(to be clear) *//* E60F20_APB */
			do {
				UINT32 load_data[5];
				UINT32 load_size=0;
				load_data[0] = 1;//number
				load_data[1] = 0;//reserved
				load_data[2] = 10;//id
				load_data[3] = sizeof(PE_CHPI_CMN0_E60F20_T);//offset
				load_data[4] = (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_CEN0_E60F20_T)-8));//header
				load_size = (UINT32)(sizeof(UINT32)*5);
				ret = PE_FWI_E60_LoadDbDone(load_data,load_size);
				PE_CMN_HW_E60_CHECK_CODE(ret,break,"[%s,%d] PE_FWI_E60_LoadDbDone() error.\n",__F__,__L__);
				PE_PRINT_NOTI("[LoadDbDone]%d,%d,%d,0x%08x,0x%08x(%d)\n",load_data[0],load_data[1],load_data[2],load_data[3],load_data[4],load_size);
				PE_INF_HW_E60_BACKUP_TRACE("[LoadDbDone]%d,%d,%d,0x%08x,0x%08x(%d)",load_data[0],load_data[1],load_data[2],load_data[3],load_data[4],load_size);
			} while(0);
		#endif
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}


static int PE_CMN_HW_E60_LGSR_DownloadDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
#define PE_FWI_E60_LGSR_YSR_SIZE_WGT (0x5100)
#define PE_FWI_E60_LGSR_YSR_SIZE_APB (0x2EC)
#define PE_FWI_E60_LGSR_ASR_SIZE_WGT (0x3F00)
#define PE_FWI_E60_LGSR_ASR_SIZE_APB (0x244)
typedef struct
{
	// 2 * ((wgt(5184)+APB(187+ 1(dummy))
	UINT32 weight00[5184];
	UINT32 apb00[187];
	UINT32 dummy00;
	UINT32 weight01[5184];
	UINT32 apb01[187];
	UINT32 dummy01;
}
PE_LGSR_DDR_DB_OSDYSR_E60_T;
typedef struct
{
	// 2 * ((wgt(4032)+APB(145+3(dummy))
	UINT32 weight00[4032];
	UINT32 apb00[145];
	UINT32 dummy00[3];
	UINT32 weight01[4032];
	UINT32 apb01[145];
	UINT32 dummy01[3];
}
PE_LGSR_DDR_DB_OSDASR_E60_T;
	PE_LGSR_DDR_DB_OSDYSR_E60_T *pOsdYsr=NULL;
	PE_LGSR_DDR_DB_OSDASR_E60_T *pOsdAsr=NULL;
	UINT32 size_OsdYsr;
	UINT32 size_OsdAsr;
	UINT32 base_OsdYsr;
	UINT32 base_OsdAsr;
	LX_DE_IPC_SYSTEM_INFO_T *currMem = &g_pe_lgsr_mem_info;
	do{
		
		/*download LGSR OSD weight/apb*/
		base_OsdYsr = currMem->fw_dnn.base + 0x5C0000;
		size_OsdYsr = 2*(PE_FWI_E60_LGSR_YSR_SIZE_WGT+PE_FWI_E60_LGSR_YSR_SIZE_APB+4);//2개 model * ((wgt(5184개)+APB(187개+dummy 1개)*
		pOsdYsr = (volatile UINT32 *)vmap_phys(base_OsdYsr, size_OsdYsr+PAGE_SIZE);
		base_OsdAsr = currMem->fw_dnn.base + 0x610000;
		size_OsdAsr = 2*(PE_FWI_E60_LGSR_ASR_SIZE_WGT+PE_FWI_E60_LGSR_ASR_SIZE_APB+3*4);//2개 model * ((wgt(4032개)+APB(145개+dummy 3개)*
		pOsdAsr = (volatile UINT32 *)vmap_phys(base_OsdAsr, size_OsdAsr+PAGE_SIZE);
#if (CONFIG_LX_E60_CHIP_FIRMWARE == 1) 
		memcpy((UINT32 *)pOsdYsr->weight00,	lgsr_osdy_weight_set_00_e60,	PE_FWI_E60_LGSR_YSR_SIZE_WGT);
		memcpy((UINT32 *)pOsdYsr->apb00,	lgsr_osdy_apb_set_00_e60,		PE_FWI_E60_LGSR_YSR_SIZE_APB);
		memcpy((UINT32 *)pOsdYsr->weight01,	lgsr_osdy_weight_set_00_e60, 	PE_FWI_E60_LGSR_YSR_SIZE_WGT);
		memcpy((UINT32 *)pOsdYsr->apb01,	lgsr_osdy_apb_set_00_e60, 		PE_FWI_E60_LGSR_YSR_SIZE_APB);
		memcpy((UINT32 *)pOsdAsr->weight00,	lgsr_osda_weight_set_00_e60, 	PE_FWI_E60_LGSR_ASR_SIZE_WGT);
		memcpy((UINT32 *)pOsdAsr->apb00,	lgsr_osda_apb_set_00_e60, 		PE_FWI_E60_LGSR_ASR_SIZE_APB);
		memcpy((UINT32 *)pOsdAsr->weight01,	lgsr_osda_weight_set_00_e60, 	PE_FWI_E60_LGSR_ASR_SIZE_WGT);
		memcpy((UINT32 *)pOsdAsr->apb01,	lgsr_osda_apb_set_00_e60, 		PE_FWI_E60_LGSR_ASR_SIZE_APB);
		wmb();
#endif
			/* noti */
		PE_PRINT_NOTI("LGSR OSD data : DL done.(fw_dnn base:0x%08x)\n",base_OsdYsr);
	}while(0);
	if(pOsdYsr)	vunmap_phys((void*)pOsdYsr);
	if(pOsdAsr)	vunmap_phys((void*)pOsdAsr);
	#endif /*PE_HW_E60_BRINGUP*/
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
static int PE_CMN_HW_E60_DownloadModeDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_CMN_HW_E60_SETTINGS_T *p_inf = &_g_pe_cmn_hw_e60_info;
	PE_DDR_DB_SHDW_REG_E60_T *p_shdw_db = gPE_DDR_DB_E60.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_E60_T *p_phys_db = gPE_DDR_DB_E60.phys.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_E60)
		{
			/* header */
			sec_typ = PE_DDR_E60_SEC_MODE;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_E60_MODE_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_E60_MODE_SIZE;
			p_phys_db->mode.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->mode.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->mode.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->mode.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_E60_MODE_ITEM_NUM * PE_DDR_E60_MODE_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.db_base+sizeof(PE_DDR_E60_TOP_HEADER_T);
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_E60_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_E60_HEADER_T);
			/* wr ddr */
			p_phys_db->mode.data[0] = p_inf->db_mode_data[0];
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_E60_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
static int PE_CMN_HW_E60F20_DownloadModeDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size = 0, sec_typ = 0;
	PE_CMN_HW_E60_SETTINGS_T *p_inf = &_g_pe_cmn_hw_e60_info;
	PE_DDR_DB_SHDW_REG_E60F20_T *p_shdw_db = gPE_DDR_DB_E60F20.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_E60F20_T *p_phys_db = gPE_DDR_DB_E60F20.phys.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		if (PE_KDRV_VER_E60)
		{
			/* header */
			sec_typ = PE_DDR_E60F20_SEC_MODE;
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_E60F20_MODE_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_E60F20_MODE_SIZE;
			p_phys_db->mode.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->mode.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->mode.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->mode.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_E60F20_MODE_ITEM_NUM * PE_DDR_E60F20_MODE_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.db_base+sizeof(PE_DDR_E60F20_TOP_HEADER_T);
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_E60F20_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_E60F20_HEADER_T);
			/* wr ddr */
			p_phys_db->mode.data[0] = p_inf->db_mode_data[0];
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_E60F20_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
static int PE_CMN_HW_E60_DownloadCvdDb(void)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 size, sec_typ;
	PE_DDR_DB_SHDW_REG_E60_T *p_shdw_db = gPE_DDR_DB_E60.shdw.data;
	volatile PE_DDR_DB_PHYS_REG_E60_T *p_phys_db = gPE_DDR_DB_E60.phys.data;
	volatile UINT32 *p_cvd_dflt_data  = p_phys_db->cvd_dflt.data;
	do{
		CHECK_KNULL(p_shdw_db);
		CHECK_KNULL(p_phys_db);
		CHECK_KNULL(p_cvd_dflt_data);
		if (PE_KDRV_VER_E60)
		{
			/* cvd_dflt **************************************************************/
			sec_typ = PE_DDR_E60_SEC_CVD_DFLT;
			/* header */
			p_shdw_db->sec_d[sec_typ].header.version   = 0x1;
			p_shdw_db->sec_d[sec_typ].header.sec_type  = sec_typ;
			p_shdw_db->sec_d[sec_typ].header.item_num  = PE_DDR_E60_CVD_DFLT_ITEM_NUM;
			p_shdw_db->sec_d[sec_typ].header.item_size = PE_DDR_E60_CVD_DFLT_SIZE;
			p_phys_db->cvd_dflt.header.version   = p_shdw_db->sec_d[sec_typ].header.version;
			p_phys_db->cvd_dflt.header.sec_type  = p_shdw_db->sec_d[sec_typ].header.sec_type;
			p_phys_db->cvd_dflt.header.item_num  = p_shdw_db->sec_d[sec_typ].header.item_num;
			p_phys_db->cvd_dflt.header.item_size = p_shdw_db->sec_d[sec_typ].header.item_size;
			/* data */
			size = (PE_DDR_E60_CVD_DFLT_ITEM_NUM * PE_DDR_E60_CVD_DFLT_SIZE * sizeof(UINT32));
			p_shdw_db->top_h.sec_base[sec_typ] = \
				p_shdw_db->top_h.sec_base[sec_typ-1]+p_shdw_db->top_h.sec_size[sec_typ-1];
			p_shdw_db->top_h.sec_size[sec_typ] = size + sizeof(PE_DDR_E60_HEADER_T);
			p_phys_db->top_h.sec_base[sec_typ] = p_shdw_db->top_h.sec_base[sec_typ];
			p_phys_db->top_h.sec_size[sec_typ] = p_shdw_db->top_h.sec_size[sec_typ];
			p_shdw_db->sec_d[sec_typ].data_base = \
				p_shdw_db->top_h.sec_base[sec_typ] + sizeof(PE_DDR_E60_HEADER_T);
			/* wr ddr */
#ifdef INCLUDE_KDRV_AFE
			ret = CVD_SetPqModeToDdr(p_cvd_dflt_data);//fix compile error
			PE_CMN_HW_E60_CHECK_CODE(ret, break, \
				"[%s,%d] CVD_SetPqModeToDdr() error.\n",__F__,__L__);
#endif
			/* noti */
			PE_PRINT_NOTI("%s: DL done.(base:0x%08x)\n", \
				PE_DDR_REG_E60_SEC_TYPE_TO_STR(sec_typ), p_shdw_db->top_h.sec_base[sec_typ]);
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

/**
 * init chip info(E60F20_APB)(E60F20_TBL)
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
static int PE_CMN_HW_E60_InitChipInfo(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 i, data0, data1;
	UINT32 ofst, size;
	UINT32 ofst_cen0,ofst_cen1;

	#define PE_CMN_HW_E60_SIZE_CHK(_n,_x,_y)	(_x),((_x)/(_n)),(_n),(_x),(_y)

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(gPE_CHPI_DDR_E60);
		if (PE_KDRV_VER_E60)
		{
			data0 = 0xF03425B8;//pe1_apl_stat_01(RO)
			data1 = PE_SWAP32(data0);
			if (pstParams->resume_mode != 1)//if normal or snapshot
			{
				/* E60F20_APB */
				#ifdef PE_CHPI_DEF_E60F20_USE_REG
				PE_CHPI_APB0_E60F20_QWr(crc1,PE_CHPI_APB_E60F20_CRC1);
				PE_CHPI_APB0_E60F20_QWr(crc0,0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_Wr(head1.info.udata32,0);
				PE_CHPI_APB0_E60F20_Wr(head1.info.max_num,32);
				PE_CHPI_APB0_E60F20_Wr(head1.info.bufidx1,4);
				PE_CHPI_APB0_E60F20_Wr(head1.info.bufidx0,1);
				PE_CHPI_APB0_E60F20_Wr(head1.info.version,0);
				PE_CHPI_APB0_E60F20_WrFL(head1.info.udata32);
				PE_CHPI_APB0_E60F20_QWr(head1.cnt0.udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.cnt1.udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.cnt2.udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.cnt3.udata32,0);
				/* PE */
				ofst = sizeof(UINT32)+sizeof(PE_CHPI_APB0_DB_H_E60F20_T);
				size = sizeof(PE_CHPI_CMN0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[0].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[0].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[0].udata32);
				ofst += size;
				ofst_cen0 =ofst;
				size = sizeof(PE_CHPI_CEN0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[1].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[1].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[1].udata32);
				ofst += size;
				ofst_cen1 =ofst;
				size = sizeof(PE_CHPI_CEN1_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[2].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[2].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[2].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_CW0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[3].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[3].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[3].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_VSP0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[4].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[4].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[4].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DSE0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[5].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[5].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[5].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DCE0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[6].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[6].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[6].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DTM0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[7].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[7].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[7].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_FSW0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[8].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[8].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[8].udata32);
				//ofst += size;
				size = sizeof(PE_CHPI_CEN0_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[9].ofst,ofst_cen0);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[9].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[9].udata32);
				//ofst += size;
				size = sizeof(PE_CHPI_CEN1_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[10].ofst,ofst_cen1);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[10].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[10].udata32);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[11].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[12].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[13].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[14].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[15].udata32,0);

				/* HDR */
				ofst = PE_CHPI_APB_E60F20_OFST1;
				size = sizeof(PE_CHPI_HDR_TM_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[16].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[16].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[16].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_HDR_S2H_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[17].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[17].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[17].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_HDR_YG_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[18].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[18].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[18].udata32);

				PE_CHPI_APB0_E60F20_QWr(head1.pos[19].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[20].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[21].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[22].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[23].udata32,0);

				ofst += size;
				size = sizeof(PE_CHPI_HDR_HS_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[24].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[24].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[24].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_HDR_PCC_E60F20_T);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[25].ofst,ofst);
				PE_CHPI_APB0_E60F20_Wr(head1.pos[25].size,size);
				PE_CHPI_APB0_E60F20_WrFL(head1.pos[25].udata32);

				PE_CHPI_APB0_E60F20_QWr(head1.pos[26].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[27].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[28].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[29].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[30].udata32,0);
				PE_CHPI_APB0_E60F20_QWr(head1.pos[31].udata32,0);

				PE_CHPI_APB0_E60F20_QWr(head0,PE_CHPI_APB_E60F20_HEAD);

				#else

				wmb();
				/* except for header */
				for (i=1; i<(sizeof(PE_CHPI_REG_E60F20_T)>>2); i++)
				{
					gPE_CHPI_APB0_E60F20.shdw.addr[i] = data0;
					gPE_CHPI_APB0_E60F20.phys.addr[i] = data1;
					gPE_CHPI_APB1_E60F20.phys.addr[i] = data1;
					wmb();
				}
				PE_CHPI_APB0_E60F20_QWr(resvd1.crc, 0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(pcc.crc,    0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(hs.crc,     0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(yg.crc,     0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(s2h.crc,    0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(tm.crc,     0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(resvd0.crc, 0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(fsw0.crc,   0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(dtm0.crc,   0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(dce0.crc,   0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(dse0.crc,   0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(vsp0.crc,   0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(cw0.crc,    0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(cen1.crc,   0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(cen0.crc,   0xFFFFFFFF);
				PE_CHPI_APB0_E60F20_QWr(cmn0.crc,   0xFFFFFFFF);

				PE_CHPI_APB0_E60F20_QWr(resvd1.head, (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_RESVD1_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(pcc.head,    (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_HDR_PCC_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(hs.head,     (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_HDR_HS_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(yg.head,     (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_HDR_YG_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(s2h.head,    (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_HDR_S2H_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(tm.head,     (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_HDR_TM_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(resvd0.head, (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_RESVD0_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(fsw0.head,   (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_FSW0_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(dtm0.head,   (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_DTM0_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(dce0.head,   (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_DCE0_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(dse0.head,   (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_DSE0_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(vsp0.head,   (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_VSP0_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(cw0.head,    (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_CW0_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(cen1.head,   (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_CEN1_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(cen0.head,   (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_CEN0_E60F20_T)-8)));
				PE_CHPI_APB0_E60F20_QWr(cmn0.head,   (PE_CHPI_APB_E60F20_CLEAR|(sizeof(PE_CHPI_CMN0_E60F20_T)-8)));
				#endif

				/* E60F20_TBL 0 */
				PE_CHPI_TBL0_E60F20_QWr(crc1,PE_CHPI_TBL_E60F20_CRC1);
				PE_CHPI_TBL0_E60F20_QWr(crc0,0xFFFFFFFF);
				PE_CHPI_TBL0_E60F20_Wr(head1.info.udata32,0);
				PE_CHPI_TBL0_E60F20_Wr(head1.info.max_num,22);
				PE_CHPI_TBL0_E60F20_Wr(head1.info.bufidx1,5);
				PE_CHPI_TBL0_E60F20_Wr(head1.info.bufidx0,2);
				PE_CHPI_TBL0_E60F20_Wr(head1.info.version,0);
				PE_CHPI_TBL0_E60F20_WrFL(head1.info.udata32);
				PE_CHPI_TBL0_E60F20_QWr(head1.cnt0.udata32,0);
				PE_CHPI_TBL0_E60F20_QWr(head1.cnt1.udata32,0);
				PE_CHPI_TBL0_E60F20_QWr(head1.cnt2.udata32,0);
				PE_CHPI_TBL0_E60F20_QWr(head1.cnt3.udata32,0);
				ofst = sizeof(UINT32)+sizeof(PE_CHPI_TBL0_DB_H_E60F20_T);
				size = sizeof(PE_CHPI_CCO_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[0].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[0].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[0].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_OBO_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[1].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[1].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[1].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_OBF_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[2].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[2].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[2].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_RCO_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[3].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[3].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[3].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_RCF_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[4].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[4].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[4].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_RES_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[5].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[5].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[5].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_CTI_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[6].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[6].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[6].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_TNR_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[7].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[7].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[7].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DNR_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[8].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[8].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[8].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DNR_PSP_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[9].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[9].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[9].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DNR_LED_TBL_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[10].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[10].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[10].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_SHP_UI_SQM_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[11].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[11].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[11].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_SHP_CMN_SQM_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[12].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[12].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[12].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_TNR_SQM_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[13].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[13].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[13].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DNR_SQM_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[14].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[14].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[14].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DNR_DCNT_SQM_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[15].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[15].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[15].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_LED_DCNT_SQM_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[16].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[16].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[16].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_TNR_USER_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[17].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[17].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[17].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DNR_USER_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[18].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[18].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[18].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DNR_DCNT_USER_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[19].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[19].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[19].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_LED_DCNT_USER_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[20].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[20].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[20].udata32);
				ofst += size;
				size = sizeof(PE_CHPI_DRC_CUV_E60F20_T);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[21].ofst,ofst);
				PE_CHPI_TBL0_E60F20_Wr(head1.pos[21].size,size);
				PE_CHPI_TBL0_E60F20_WrFL(head1.pos[21].udata32);
				for (i=22; i<32; i++)
				{
					PE_CHPI_TBL0_E60F20_QWr(head1.pos[i].udata32,0);
				}
				PE_CHPI_TBL0_E60F20_QWr(head0,PE_CHPI_TBL_E60F20_HEAD);

				#ifdef PE_CHPI_DEF_E60F20_USE_REG
				ofst = 4;//from head1
				size = sizeof(PE_CHPI_APB0_DB_H_E60F20_T);    PE_PRINT_NOTI("[CHI]head   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CMN0_E60F20_T);         PE_PRINT_NOTI("[CHI]cmn0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CEN0_E60F20_T);         PE_PRINT_NOTI("[CHI]cen0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CEN1_E60F20_T);         PE_PRINT_NOTI("[CHI]cen1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CW0_E60F20_T);          PE_PRINT_NOTI("[CHI]cw0    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_VSP0_E60F20_T);         PE_PRINT_NOTI("[CHI]vsp0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DSE0_E60F20_T);         PE_PRINT_NOTI("[CHI]dse0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DCE0_E60F20_T);         PE_PRINT_NOTI("[CHI]dce0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DTM0_E60F20_T);         PE_PRINT_NOTI("[CHI]dtm0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_FSW0_E60F20_T);         PE_PRINT_NOTI("[CHI]fsw0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_APB0_RESVD0_E60F20_T);  PE_PRINT_NOTI("[CHI]resvd0 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_TM_E60F20_T);       PE_PRINT_NOTI("[CHI]tm     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_S2H_E60F20_T);      PE_PRINT_NOTI("[CHI]s2h    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_YG_E60F20_T);       PE_PRINT_NOTI("[CHI]yg     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_HS_E60F20_T);       PE_PRINT_NOTI("[CHI]hs     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_PCC_E60F20_T);      PE_PRINT_NOTI("[CHI]pcc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_APB0_RESVD1_E60F20_T);  PE_PRINT_NOTI("[CHI]resvd1 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_REG_E60F20_T);          PE_PRINT_NOTI("[CHI]TOTAL  (%5d)(0x%04x) vs (%5d)(0x%04x)\n",size,size,PE_CHPI_APB_E60F20_TOTAL,PE_CHPI_APB_E60F20_TOTAL);

				ofst = 4;//from head1
				size = sizeof(PE_CHPI_APB0_DB_H_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]head   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CMN0_E60F20_T);         PE_INF_HW_E60_BACKUP_CHPI0("[CHI]cmn0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CEN0_E60F20_T);         PE_INF_HW_E60_BACKUP_CHPI0("[CHI]cen0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CEN1_E60F20_T);         PE_INF_HW_E60_BACKUP_CHPI0("[CHI]cen1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CW0_E60F20_T);          PE_INF_HW_E60_BACKUP_CHPI0("[CHI]cw0    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_VSP0_E60F20_T);         PE_INF_HW_E60_BACKUP_CHPI0("[CHI]vsp0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DSE0_E60F20_T);         PE_INF_HW_E60_BACKUP_CHPI0("[CHI]dse0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DCE0_E60F20_T);         PE_INF_HW_E60_BACKUP_CHPI0("[CHI]dce0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DTM0_E60F20_T);         PE_INF_HW_E60_BACKUP_CHPI0("[CHI]dtm0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_FSW0_E60F20_T);         PE_INF_HW_E60_BACKUP_CHPI0("[CHI]fsw0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_APB0_RESVD0_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI0("[CHI]resvd0 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_TM_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI0("[CHI]tm     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_S2H_E60F20_T);      PE_INF_HW_E60_BACKUP_CHPI0("[CHI]s2h    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_YG_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI0("[CHI]yg     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_HS_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI0("[CHI]hs     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_PCC_E60F20_T);      PE_INF_HW_E60_BACKUP_CHPI0("[CHI]pcc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_APB0_RESVD1_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI0("[CHI]resvd1 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_REG_E60F20_T);          PE_INF_HW_E60_BACKUP_CHPI0("[CHI]TOTAL  (%5d)(0x%04x) vs (%5d)(0x%04x)",size,size,PE_CHPI_APB_E60F20_TOTAL,PE_CHPI_APB_E60F20_TOTAL);

				#else

				ofst = 0;//from base
				size = sizeof(PE_CHPI_CMN0_E60F20_T);    PE_PRINT_NOTI("[CHI]cmn0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CEN0_E60F20_T);    PE_PRINT_NOTI("[CHI]cen0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CEN1_E60F20_T);    PE_PRINT_NOTI("[CHI]cen1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CW0_E60F20_T);     PE_PRINT_NOTI("[CHI]cw0    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_VSP0_E60F20_T);    PE_PRINT_NOTI("[CHI]vsp0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DSE0_E60F20_T);    PE_PRINT_NOTI("[CHI]dse0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DCE0_E60F20_T);    PE_PRINT_NOTI("[CHI]dce0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DTM0_E60F20_T);    PE_PRINT_NOTI("[CHI]dtm0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_FSW0_E60F20_T);    PE_PRINT_NOTI("[CHI]fsw0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RESVD0_E60F20_T);  PE_PRINT_NOTI("[CHI]resvd0 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_TM_E60F20_T);  PE_PRINT_NOTI("[CHI]tm     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_S2H_E60F20_T); PE_PRINT_NOTI("[CHI]s2h    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_YG_E60F20_T);  PE_PRINT_NOTI("[CHI]yg     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_HS_E60F20_T);  PE_PRINT_NOTI("[CHI]hs     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_PCC_E60F20_T); PE_PRINT_NOTI("[CHI]pcc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RESVD1_E60F20_T);  PE_PRINT_NOTI("[CHI]resvd1 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_REG_E60F20_T);     PE_PRINT_NOTI("[CHI]TOTAL  (%5d)(0x%04x) vs (%5d)(0x%04x)\n",size,size,PE_CHPI_APB_E60F20_TOTAL,PE_CHPI_APB_E60F20_TOTAL);

				ofst = 0;//from base
				size = sizeof(PE_CHPI_CMN0_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]cmn0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CEN0_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]cen0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CEN1_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]cen1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CW0_E60F20_T);     PE_INF_HW_E60_BACKUP_CHPI0("[CHI]cw0    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_VSP0_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]vsp0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DSE0_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]dse0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DCE0_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]dce0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DTM0_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]dtm0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_FSW0_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI0("[CHI]fsw0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RESVD0_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI0("[CHI]resvd0 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_TM_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI0("[CHI]tm     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_S2H_E60F20_T); PE_INF_HW_E60_BACKUP_CHPI0("[CHI]s2h    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_YG_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI0("[CHI]yg     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_HS_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI0("[CHI]hs     (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_HDR_PCC_E60F20_T); PE_INF_HW_E60_BACKUP_CHPI0("[CHI]pcc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RESVD1_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI0("[CHI]resvd1 (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_REG_E60F20_T);     PE_INF_HW_E60_BACKUP_CHPI0("[CHI]TOTAL  (%5d)(0x%04x) vs (%5d)(0x%04x)",size,size,PE_CHPI_APB_E60F20_TOTAL,PE_CHPI_APB_E60F20_TOTAL);
				#endif

				ofst = 4;//from head1
				size = sizeof(PE_CHPI_TBL0_DB_H_E60F20_T);     PE_PRINT_NOTI("[CHI]head   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CCO_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]cco    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_OBO_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]obo    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_OBF_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]obf    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RCO_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]rco    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RCF_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]rcf    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RES_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]res    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CTI_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]cti    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TNR_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]tnr    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_TBL_E60F20_T);       PE_PRINT_NOTI("[CHI]dnr    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_PSP_TBL_E60F20_T);   PE_PRINT_NOTI("[CHI]psp    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_LED_TBL_E60F20_T);   PE_PRINT_NOTI("[CHI]led    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_SHP_UI_SQM_E60F20_T);    PE_PRINT_NOTI("[CHI]sqm0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_SHP_CMN_SQM_E60F20_T);   PE_PRINT_NOTI("[CHI]sqm1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TNR_SQM_E60F20_T);       PE_PRINT_NOTI("[CHI]sqm2   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_SQM_E60F20_T);       PE_PRINT_NOTI("[CHI]sqm3   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_DCNT_SQM_E60F20_T);  PE_PRINT_NOTI("[CHI]sqm4   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_LED_DCNT_SQM_E60F20_T);  PE_PRINT_NOTI("[CHI]sqm5   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TNR_USER_E60F20_T);      PE_PRINT_NOTI("[CHI]usr0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_USER_E60F20_T);      PE_PRINT_NOTI("[CHI]usr1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_DCNT_USER_E60F20_T); PE_PRINT_NOTI("[CHI]usr2   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_LED_DCNT_USER_E60F20_T); PE_PRINT_NOTI("[CHI]usr3   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DRC_CUV_E60F20_T);       PE_PRINT_NOTI("[CHI]drc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TBL0_RESVD_E60F20_T);    PE_PRINT_NOTI("[CHI]resvd  (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)\n",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TBL0_E60F20_T);          PE_PRINT_NOTI("[CHI]TOTAL  (%5d)(0x%04x) vs (%5d)(0x%04x)\n",size,size,PE_CHPI_TBL_E60F20_TOTAL,PE_CHPI_TBL_E60F20_TOTAL);

				ofst = 4;//from head1
				size = sizeof(PE_CHPI_TBL0_DB_H_E60F20_T);     PE_INF_HW_E60_BACKUP_CHPI1("[CHI]head   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CCO_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]cco    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_OBO_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]obo    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_OBF_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]obf    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RCO_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]rco    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RCF_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]rcf    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_RES_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]res    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_CTI_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]cti    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TNR_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]tnr    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_TBL_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]dnr    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_PSP_TBL_E60F20_T);   PE_INF_HW_E60_BACKUP_CHPI1("[CHI]psp    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_LED_TBL_E60F20_T);   PE_INF_HW_E60_BACKUP_CHPI1("[CHI]led    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(8,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_SHP_UI_SQM_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI1("[CHI]sqm0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_SHP_CMN_SQM_E60F20_T);   PE_INF_HW_E60_BACKUP_CHPI1("[CHI]sqm1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TNR_SQM_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]sqm2   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_SQM_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]sqm3   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_DCNT_SQM_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI1("[CHI]sqm4   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_LED_DCNT_SQM_E60F20_T);  PE_INF_HW_E60_BACKUP_CHPI1("[CHI]sqm5   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TNR_USER_E60F20_T);      PE_INF_HW_E60_BACKUP_CHPI1("[CHI]usr0   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_USER_E60F20_T);      PE_INF_HW_E60_BACKUP_CHPI1("[CHI]usr1   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DNR_DCNT_USER_E60F20_T); PE_INF_HW_E60_BACKUP_CHPI1("[CHI]usr2   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_LED_DCNT_USER_E60F20_T); PE_INF_HW_E60_BACKUP_CHPI1("[CHI]usr3   (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_DRC_CUV_E60F20_T);       PE_INF_HW_E60_BACKUP_CHPI1("[CHI]drc    (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TBL0_RESVD_E60F20_T);    PE_INF_HW_E60_BACKUP_CHPI1("[CHI]resvd  (%5d)(%4d x%2d(byte) = 0x%04x) (0x%04x)",PE_CMN_HW_E60_SIZE_CHK(4,size,ofst));ofst+=size;
				size = sizeof(PE_CHPI_TBL0_E60F20_T);          PE_INF_HW_E60_BACKUP_CHPI1("[CHI]TOTAL  (%5d)(0x%04x) vs (%5d)(0x%04x)",size,size,PE_CHPI_TBL_E60F20_TOTAL,PE_CHPI_TBL_E60F20_TOTAL);

			}
			PE_PRINT_NOTI("[CHI]done(resume:%d)\n",pstParams->resume_mode);
			PE_INF_HW_E60_BACKUP_TRACE("[CHI]done(resume:%d)",pstParams->resume_mode);
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");
			ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

/**
 * get db info.
 *
 * @param   inf_type [in] UINT32, see PE_CMN_HW_E60_DB_INF_TYPE
 * @param   sec_type [in] UINT32, see PE_DDR_E60_SEC_TYPE
 * @return  UINT32.
 * @see
 * @author
 */
UINT32 PE_CMN_HW_E60_GetDbInfo(UINT32 inf_type, UINT32 sec_type)
{
	UINT32 ret = 0;
	#ifndef PE_HW_E60_BRINGUP
	PE_DDR_E60_MD0_T *p_md0;
	PE_CMN_HW_E60_SETTINGS_T *p_inf = &_g_pe_cmn_hw_e60_info;
	PE_DDR_DB_SHDW_REG_E60_T *p_shdw_db = gPE_DDR_DB_E60.shdw.data;

	if (sec_type>=PE_DDR_E60_SEC_NUM)
	return ret;

	switch (inf_type)
	{
		case PE_CMN_HW_E60_DB_INF_IS_DB_INIT:
			ret = p_inf->db_initialized;
			break;
		case PE_CMN_HW_E60_DB_INF_TOP_VERSION:
			ret = p_shdw_db->top_h.version;
			break;
		case PE_CMN_HW_E60_DB_INF_TOP_BASE:
			ret = p_shdw_db->top_h.db_base;
			break;
		case PE_CMN_HW_E60_DB_INF_TOP_SEC_NUM:
			ret = p_shdw_db->top_h.sec_num;
			break;
		case PE_CMN_HW_E60_DB_INF_SEC_BASE:
			ret = p_shdw_db->top_h.sec_base[sec_type];
			break;
		case PE_CMN_HW_E60_DB_INF_SEC_SIZE:
			ret = p_shdw_db->top_h.sec_size[sec_type];
			break;
		case PE_CMN_HW_E60_DB_INF_SEC_VERSION:
			ret = p_shdw_db->sec_d[sec_type].header.version;
			break;
		case PE_CMN_HW_E60_DB_INF_SEC_TYPE:
			ret = p_shdw_db->sec_d[sec_type].header.sec_type;
			break;
		case PE_CMN_HW_E60_DB_INF_SEC_ITEM_NUM:
			ret = p_shdw_db->sec_d[sec_type].header.item_num;
			break;
		case PE_CMN_HW_E60_DB_INF_SEC_ITEM_SIZE:
			ret = p_shdw_db->sec_d[sec_type].header.item_size;
			break;
		case PE_CMN_HW_E60_DB_INF_SEC_DATA_BASE:
			ret = p_shdw_db->sec_d[sec_type].data_base;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_SHP_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->shp_fw_en;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_HST_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->hst_fw_en;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_SCL_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->scl_fw_en;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_TNR_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->tnr_fw_en;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_DNR_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			ret = p_md0->dnr_fw_en;
			break;
		default:
			ret = 0;
			break;
	}
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

/**
 * set db info.
 * - I think that shdw db modification is not good.
 *
 * @param   inf_type [in] UINT32, see PE_CMN_HW_E60_DB_INF_TYPE
 * @param   sec_type [in] UINT32, see PE_DDR_E60_SEC_TYPE
 * @param   value [in] UINT32
 * @return  UINT32.
 * @see
 * @author
 */
UINT32 PE_CMN_HW_E60_SetDbInfo(UINT32 inf_type, UINT32 sec_type, UINT32 value)
{
	UINT32 ret = 0;
	#ifndef PE_HW_E60_BRINGUP
	PE_DDR_E60_MD0_T *p_md0;
	PE_CMN_HW_E60_SETTINGS_T *p_inf = &_g_pe_cmn_hw_e60_info;

	if (sec_type>=PE_DDR_E60_SEC_NUM)
		return ret;

	switch (inf_type)
	{
		case PE_CMN_HW_E60_DB_INF_MD0_SHP_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			p_md0->shp_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_HST_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			p_md0->hst_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_SCL_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			p_md0->scl_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_TNR_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			p_md0->tnr_fw_en = value? 1:0;
			break;
		case PE_CMN_HW_E60_DB_INF_MD0_DNR_FW_EN:
			p_md0 = (PE_DDR_E60_MD0_T *)p_inf->db_mode_data;
			p_md0->dnr_fw_en = value? 1:0;
			break;
		default:
			ret = 0;
			break;
	}
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

/**
 * download db bin
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  void
 * @see     PE_TSK_E60_OPR_T
 * @author
 */
int PE_CMN_E60_DownloadDbBin(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	UINT32 db_addr = 0;
	UINT32 head_num, head_size, data_size;
	volatile UINT32 *ddr_addr = NULL;
	do {
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->size);
		CHECK_KNULL(pstParams->data);
		db_addr = pstParams->data[0];
		head_num = 1;
		head_size = sizeof(UINT32)*head_num;
		if (pstParams->size<(head_num<<1))
		{
			PE_PRINT_NOTI("warning. invalid(0) (addr:0x%08x, size:%d)\n",db_addr,pstParams->size);
			pstParams->size = (head_num<<1);
		}
		if (db_addr<PE_E60_DDR_DB0_BASE)
		{
			PE_PRINT_NOTI("warning. invalid(1) (addr:0x%08x, size:%d)\n",db_addr,pstParams->size);
		}
		if ((db_addr+pstParams->size)>(PE_E60_DDR_DB0_BASE+PE_E60_DDR_DB0_SIZE))
		{
			PE_PRINT_NOTI("warning. invalid(2) (addr:0x%08x, size:%d)\n",db_addr,pstParams->size);
		}
		data_size = (pstParams->size*sizeof(UINT32)) - head_size;
		PE_PRINT_NOTI("size:%d(%d), addr:0x%08x\n", pstParams->size, data_size, db_addr);
		ddr_addr = (volatile UINT32 *)vmap_phys(db_addr, data_size+PAGE_SIZE);
		if(!ddr_addr) {PE_PRINT_NOTI("ddr_addr is null.\n");break;}
		memcpy((UINT32 *)ddr_addr, pstParams->data + head_num, data_size);
		//for (i=0; i<(pstParams->size/sizeof(UINT32)); i++)	PE_PRINT_NOTI("db[%d]:0x%08x\n", i, pstParams->data[i]);
		wmb();
	} while(0);
	if(ddr_addr)	vunmap_phys((void*)ddr_addr);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}

/**
 * get general(all) picture info
 *
 * @param   *pstParams [in] LX_PE_ETC_TBL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_E60_GetDownloadInfo(LX_PE_ETC_TBL_T *pstParams)
{
    int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	char buffer[PE_TRACE_STR_SIZE];
	UINT32 rd_cnt=0;
	UINT32 used_size = sizeof(PE_DDR_DB_PHYS_REG_E60_T);

#define PE_CMN_E60_PRINT_START		"START_OF_PRINT"
#define PE_CMN_E60_PRINT_RESERVED	"RESERVED"
#define PE_CMN_E60_PRINT_END		"END_OF_PRINT"
#define PE_CMN_E60_PRINT_EXIT		"EXIT_OF_PRINT"
#define PE_CMN_E60_CASE_PRMENU(_cnt, _action, _buf, _item)	\
	case (_cnt):sprintf(_buf, "   [0x%02x] %s\n", (_item), #_item);_action;break
#define PE_CMN_E60_CASE_SPRINT(_cnt,_action,_buf,fmt,args...)	\
	case (_cnt):sprintf(_buf,fmt,##args);_action;break
#define PE_CMN_E60_DFLT_SPRINT(_action,_buf,fmt,args...)		\
	default:sprintf(_buf,fmt,##args);_action;break

	do{
		CHECK_KNULL(pstParams);
		CHECK_KNULL(pstParams->data);
		if(PE_KDRV_VER_E60)
		{
			rd_cnt = pstParams->oper;
			if (pstParams->data[0]==0)
			{
				switch(rd_cnt)
				{
					PE_CMN_E60_CASE_SPRINT( 0,rd_cnt++,buffer,PE_CMN_E60_PRINT_START);
					PE_CMN_E60_CASE_SPRINT( 1,rd_cnt++,buffer,\
						"   alloc base : 0x %08x ~ 0x %08x\n", \
						PE_E60_DDR_DB0_BASE, PE_E60_DDR_DB0_BASE+PE_E60_DDR_DB0_SIZE);
					PE_CMN_E60_CASE_SPRINT( 2,rd_cnt++,buffer,\
						"   free  base : 0x %08x\n", PE_E60_DDR_DB0_BASE+used_size);
					PE_CMN_E60_CASE_SPRINT( 3,rd_cnt++,buffer,\
						"   used  size : 0x %08x (%4d KB)\n", used_size, used_size>>10);
					PE_CMN_E60_CASE_SPRINT( 4,rd_cnt++,buffer,\
						"   free  size : 0x %08x (%4d KB)\n", \
						(PE_E60_DDR_DB0_SIZE-used_size), (PE_E60_DDR_DB0_SIZE-used_size)>>10);
					PE_CMN_E60_CASE_SPRINT( 5,rd_cnt++,buffer,PE_CMN_E60_PRINT_RESERVED);
					PE_CMN_E60_DFLT_SPRINT(rd_cnt=0,buffer,PE_CMN_E60_PRINT_END);
				}
			}
			else
			{
				sprintf(buffer, PE_CMN_E60_PRINT_EXIT);
				rd_cnt=0;
			}
			memcpy(pstParams->data,buffer,sizeof(char)*PE_TRACE_STR_SIZE);
		}
		else
		{
			PE_PRINT_NOTI("nothing to do.\n");
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_SuspendModule(void)
{
	PE_TSK_E60_SuspendModule(0);
	return RET_OK;
}
/**
 * set vcp level control
 *
 * @param   *pstParams [in] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_HW_E60_SetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	do{
		CHECK_KNULL(pstParams);
		LX_PE_CMN_VCP_LEVEL_CTRL_T *pp = (LX_PE_CMN_VCP_LEVEL_CTRL_T *)pstParams;
		static LX_PE_CMN_VCP_LEVEL_CTRL_T prev[LX_PE_WIN_NUM];
		static UINT32 chk = 0x0;
		PE_CHECK_WINID(pp->win_id);
		PE_CHECK_DUPLICATE(LX_PE_CMN_VCP_LEVEL_CTRL_T);
		if(pp->win_id > LX_PE_WIN_ALL)
		{
			PE_CMN_HW_E60_DBG_PRINT("duplicated DB : LX_PE_CMN_VCP_LEVEL_CTRL_T\n");
			ret=RET_OK;
			break;
		}
		PE_CMN_HW_E60_DBG_PRINT("set pstParams[%d] : enable:%d, center:%d, contrast:%d, brightness:%d, saturation:%d\n",\
			pstParams->win_id,pstParams->enable,pstParams->center_position,\
			pstParams->contrast,pstParams->brightness,pstParams->saturation);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(pstParams->win_id))
			{
				PE_VCP_DISP_E60_QWr03(vcp_vsp_u0_ctrl_00, 	enable, 		 GET_BITS(pstParams->enable,		 0,1),\
															center_position, GET_BITS(pstParams->center_position,0,8),\
															contrast,		 GET_BITS(pstParams->contrast,		 0,10));
				PE_VCP_DISP_E60_QWr02(vcp_vsp_u0_ctrl_01,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
															brightness,		 GET_BITS(pstParams->brightness,	 0,10));

				#if 1	/* E60F20_VERI */
				do {
					PE_VSD0_VERI_E60_QWr03(vsd0_veri_vsp_0, enable, 		 GET_BITS(pstParams->enable,		 0,1),\
															center_position, GET_BITS(pstParams->center_position,0,8),\
															contrast,		 GET_BITS(pstParams->contrast,		 0,10));
					PE_VSD0_VERI_E60_QWr02(vsd0_veri_vsp_1,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
															brightness,		 GET_BITS(pstParams->brightness,	 0,10));
				} while(0);
				#endif
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd0_veri_vsp_0.enable,GET_BITS(pstParams->enable,0,1));
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd0_veri_vsp_0.center_position,GET_BITS(pstParams->center_position,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd0_veri_vsp_0.contrast,GET_BITS(pstParams->contrast,0,10));
					PE_CHPI_APB0_E60F20_WrFL(fsw0.vsd0_veri_vsp_0.udata32);
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd0_veri_vsp_1.saturation,GET_BITS(pstParams->saturation,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd0_veri_vsp_1.brightness,GET_BITS(pstParams->brightness,0,10));
					PE_CHPI_APB0_E60F20_WrFL(fsw0.vsd0_veri_vsp_1.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_FSW0);
				} while(0);
				#endif
			}
			else if(PE_CHECK_WIN1(pstParams->win_id))
			{
				#if 0	//20200611, vcp_vsp_u1 moved to fw setting for estreamer(QEVENTTWEN-25839)(TVPM-12053)
				PE_VCP_DISP_E60_QWr03(vcp_vsp_u1_ctrl_00, 	enable, 		 GET_BITS(pstParams->enable,		 0,1),\
															center_position, GET_BITS(pstParams->center_position,0,8),\
															contrast,		 GET_BITS(pstParams->contrast,		 0,10));
				PE_VCP_DISP_E60_QWr02(vcp_vsp_u1_ctrl_01,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
															brightness,		 GET_BITS(pstParams->brightness,	 0,10));
				#endif
				#if 1	/* E60F20_VERI */
				do {
					PE_VSD1_VERI_E60_QWr03(vsd1_veri_vsp_0, enable, 		 GET_BITS(pstParams->enable,		 0,1),\
															center_position, GET_BITS(pstParams->center_position,0,8),\
															contrast,		 GET_BITS(pstParams->contrast,		 0,10));
					PE_VSD1_VERI_E60_QWr02(vsd1_veri_vsp_1,	saturation,		 GET_BITS(pstParams->saturation,	 0,8),\
															brightness,		 GET_BITS(pstParams->brightness,	 0,10));
				} while(0);
				#endif
				#if 1	/* E60F20_APB */
				do {
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd1_veri_vsp_0.enable,GET_BITS(pstParams->enable,0,1));
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd1_veri_vsp_0.center_position,GET_BITS(pstParams->center_position,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd1_veri_vsp_0.contrast,GET_BITS(pstParams->contrast,0,10));
					PE_CHPI_APB0_E60F20_WrFL(fsw0.vsd1_veri_vsp_0.udata32);
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd1_veri_vsp_1.saturation,GET_BITS(pstParams->saturation,0,8));
					PE_CHPI_APB0_E60F20_Wr(fsw0.vsd1_veri_vsp_1.brightness,GET_BITS(pstParams->brightness,0,10));
					PE_CHPI_APB0_E60F20_WrFL(fsw0.vsd1_veri_vsp_1.udata32);
					PE_INF_E60_SetChipInfoHead(PE_INF_E60_CHPI_BLOCK_FSW0);
				} while(0);
				#endif
			}
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_GetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	LX_PE_WIN_ID win_id;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if(PE_KDRV_VER_E60)
		{
			if(PE_CHECK_WIN0(win_id))
			{
				PE_VCP_DISP_E60_QRd03(vcp_vsp_u0_ctrl_00, 	enable, 		 pstParams->enable,\
															center_position, pstParams->center_position,\
															contrast,		 pstParams->contrast);
				PE_VCP_DISP_E60_QRd02(vcp_vsp_u0_ctrl_01,	saturation,		 pstParams->saturation,\
															brightness,		 pstParams->brightness);
			}
			else if(PE_CHECK_WIN1(win_id))
			{
				PE_VCP_DISP_E60_QRd03(vcp_vsp_u1_ctrl_00, 	enable, 		 pstParams->enable,\
															center_position, pstParams->center_position,\
															contrast,		 pstParams->contrast);
				PE_VCP_DISP_E60_QRd02(vcp_vsp_u1_ctrl_01,	saturation,		 pstParams->saturation,\
															brightness,		 pstParams->brightness);
			}
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do\n");	ret = RET_OK;
		}
		PE_CMN_HW_E60_DBG_PRINT("get pstParams[%d] : enable:%d, center:%d, contrast:%d, brightness:%d, saturation:%d\n",\
			pstParams->win_id,pstParams->enable,pstParams->center_position,\
			pstParams->contrast,pstParams->brightness,pstParams->saturation);
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
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
int PE_CMN_HW_E60_SetBypassBlock(LX_PE_CMN_BYPASS_BLOCKS_T *pstParams)
{
	int ret = RET_OK;
	#ifndef PE_HW_E60_BRINGUP
	static UINT32 bypass_flag = 0;
	static UINT32 bypass_param[6];             ///< 0:psp_en 1:dce_en 2:logo_en 3:drc_en 4:pcc_en 5:cw_en
	do {
		CHECK_KNULL(pstParams);
		PE_CMN_HW_E60_DBG_PRINT("set pstParams: u32BlockMask = 0x%08x, bOnOff = %d, bypass_flag = %d\n",
			pstParams->u32BlockMask, pstParams->bOnOff, bypass_flag);
		if (PE_KDRV_VER_E60)
		{
			if (pstParams->bOnOff)
			{
				if(pstParams->u32BlockMask & 0x1)//sharpness
				{
					PE_SR_CHR_SHP_E60_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x1);
					PE_SR_2K_SHP_E60_QWr02(shp_core_ctrl_00,reg_top_core_bypass, 0x1,\
															reg_top_core_detour, 0x1);
					PE_SR_4K_SHP_E60_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x1);
					PE_SHP_E60_QWr01(shp_core_ctrl_00,	reg_top_core_bypass,	0x1);
				}
				if(pstParams->u32BlockMask & 0x2)//object contrast
				{
					#if 0
					PE_VSD_OBC_O_E60_QRd01(psp_ctrl02, reg_psp_en,  bypass_param[0]);
					PE_VSD_OBC_O_E60_QWr01(psp_ctrl02, reg_psp_en,  0x0);
					PE_VSD_OBC_F_E60_QWr01(psp_ctrl02, reg_psp_en,  0x0);
					#endif
					//ret = PE_SHP_HW_E60_SetBypassObc(1);
 				}
				if(pstParams->u32BlockMask & 0x4)//color contrast
				{
					//PE_CE_PE1_E60_QWr01(pe1_top_ctrl_02,	master_en,	0x0);
					//PE_CO_PE1_E60_QWr01(pe1_top_ctrl_02,	master_en,	0x0);
					PE_CC_PE1_E60_QRd01(pe1_dce_ctrl_00,  dynamic_contrast_en, bypass_param[1]);
					PE_CC_PE1_E60_QWr01(pe1_dce_ctrl_00, dynamic_contrast_en, 0x0);
					PE_CC2_PE1_E60_QRd01(pe1_logo_ctrl_00, reg_logo_blend_en, bypass_param[2]);
					PE_CC2_PE1_E60_QWr01(pe1_logo_ctrl_00, reg_logo_blend_en, 0x0);
					PE_CC_PE1_E60_QRd01(pe1_drc_ctrl_00,  reg_drc_en, bypass_param[3]);
					PE_CC_PE1_E60_QWr01(pe1_drc_ctrl_00,  reg_drc_en, 0x0);
					PE_CC_PE1_E60_QWr01(pe1_cen_ctrl_00, cen_detour,0x1);
					PE_CC_PE1_E60_QRd01(pe_pcc_ctrl, reg_pcc_en, bypass_param[4]);
					PE_CC_PE1_E60_QWr01(pe_pcc_ctrl, reg_pcc_en, 0x0);
					PE_VSD_DTM_E60_QWr01(dtm_top_ctrl_02, reg_master_en, 0x0);
					PE_CC_PE1_E60_QWr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x0);
					PE_CC2_PE1_E60_QRd01(pe1_cw_ctrl_00, reg_cw_en, bypass_param[5]);
					PE_CC2_PE1_E60_QWr01(pe1_cw_ctrl_00, reg_cw_en, 0x0);
				}
				if(pstParams->u32BlockMask & 0x4)//vsp
				{
					PE_CC2_PE1_E60_QWr01(pe1_vspyc_ctrl_00, enable, 0x0);
 				}
				if(pstParams->u32BlockMask & 0x8000)//csc bypass
				{
					g_pe_csc_e60_post_bypass_mode = 0x1;
 				}
				bypass_flag =0x1;
				PE_CMN_HW_E60_DBG_PRINT("bypass ON!! save param: psp_en:%d, dce_en:%d, logo_en:%d, drc_en:%d, pcc_en:%d\n",\
					bypass_param[0],bypass_param[1],bypass_param[2],bypass_param[3],bypass_param[4]);
			}
			else
			{
				if(pstParams->u32BlockMask & 0x1)//sharpness
				{
					PE_SR_CHR_SHP_E60_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x0);
					PE_SR_2K_SHP_E60_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x0);
					PE_SR_4K_SHP_E60_QWr01(shp_core_ctrl_00,reg_top_core_bypass, 0x0);
					PE_SHP_E60_QWr01(shp_core_ctrl_00,	reg_top_core_bypass, 0x0);
				}
				if(pstParams->u32BlockMask & 0x2)//object contrast
				{
					#if 0
					PE_VSD_OBC_O_E60_QWr01(psp_ctrl02, reg_psp_en,  GET_BITS(bypass_param[0],0,1));
					PE_VSD_OBC_F_E60_QWr01(psp_ctrl02, reg_psp_en,  GET_BITS(bypass_param[0],0,1));
					#endif
					//ret = PE_SHP_HW_E60_SetBypassObc(0);
				}
				if(pstParams->u32BlockMask & 0x4)//color contrast
				{
					//PE_CE_PE1_E60_QWr01(pe1_top_ctrl_02,	master_en,	0x1);
					//PE_CO_PE1_E60_QWr01(pe1_top_ctrl_02,	master_en,	0x1);
					PE_CC_PE1_E60_QWr01(pe1_dce_ctrl_00, dynamic_contrast_en, 	GET_BITS(bypass_param[1],0,1));
					PE_CC2_PE1_E60_QWr01(pe1_logo_ctrl_00, reg_logo_blend_en, 	GET_BITS(bypass_param[2],0,1));
					PE_CC_PE1_E60_QWr01(pe1_drc_ctrl_00,reg_drc_en, 			GET_BITS(bypass_param[3],0,1));
					PE_CC_PE1_E60_QWr01(pe1_cen_ctrl_00, cen_detour,0x0);
					PE_CC_PE1_E60_QWr01(pe_pcc_ctrl, reg_pcc_en,				GET_BITS(bypass_param[4],0,1));
					PE_VSD_DTM_E60_QWr01(dtm_top_ctrl_02, reg_master_en, 0x1);
					PE_CC_PE1_E60_QWr01(pe1_dse_ctrl_00,	dynamic_saturation_en,	0x0);
					PE_CC2_PE1_E60_QWr01(pe1_cw_ctrl_00, reg_cw_en, GET_BITS(bypass_param[5],0,1));
				}
				if(pstParams->u32BlockMask & 0x4)//vsp
				{
					PE_CC2_PE1_E60_QWr01(pe1_vspyc_ctrl_00, enable, 0x1);
 				}
				if(pstParams->u32BlockMask & 0x8000)//csc
				{
					g_pe_csc_e60_post_bypass_mode = 0x0;
 				}
				bypass_flag = 0x0;
				PE_CMN_HW_E60_DBG_PRINT("bypass OFF!! set param: psp_en:%d, dce_en:%d, logo_en:%d, drc_en:%d, pcc_en:%d\n",\
				bypass_param[0],bypass_param[1],bypass_param[2],bypass_param[3],bypass_param[4]);
			}
			PE_PRINT_NOTI("[CMN]block:0x%x,on:%d\n",pstParams->u32BlockMask,pstParams->bOnOff);
			PE_INF_HW_E60_BACKUP_TRACE("[CMN]block:0x%x,on:%d",pstParams->u32BlockMask,pstParams->bOnOff);
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do\n");
			ret = RET_ERROR;
		}
	}while(0);
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
int PE_LGSR_HW_E60_GetMemInfo(void *pstParams)
{
	int ret = RET_ERROR;
	#ifndef PE_HW_E60_BRINGUP

	//LX_PE_WIN_ID win_id;
	LX_DE_IPC_SYSTEM_INFO_T *currMem = &g_pe_lgsr_mem_info;
	LX_MEMCFG_T *pstMem = (LX_MEMCFG_T *)pstParams;
	//int i;
	do{
		CHECK_KNULL(pstMem);
		if(PE_KDRV_VER_E60)
		{
			//output
			//pstMem->name = "fw_dnn+0x100000";
			pstMem->base = currMem->fw_dnn.base + 0x100000;
			pstMem->size = 0x4C0000;
		}
		else
		{
			PE_CMN_HW_E60_DBG_PRINT("nothing to do.\n");	ret = RET_OK;
		}
		PE_CMN_HW_E60_DBG_PRINT("base : 0x%08x, size : 0x%08x\n", pstMem->base, pstMem->size);
		ret = RET_OK;
	}while(0);
	#endif /*PE_HW_E60_BRINGUP*/
	return ret;
}
