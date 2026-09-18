/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

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
 *	OVI module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< printk() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <linux/seq_file.h>
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/vmalloc.h>
#include <linux/kthread.h>
#include "os_util.h"

#include "ovi_dbg.h"
#include "ovi_hal.h"
#include "ovi_hw_o20.h"
#include "ovi_reg_def_o20.h"
#include "ovi_reg_o20.h"

#include "../be/reg/be_reg_dpe_o20.h"

// For CTOP register access
#include "../../../core/sys/sys_regs.h"

#include "ovi_output_format_o20a0.h"

#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
#include "be_cfg.h"
#endif

#ifdef INCLUDE_KDRV_DE
#include "de_cfg.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
#else
#define OVI_HW_O20_GAMMA_TABLE_SIZENUM 1024
#endif
#define OVI_HW_O20_INPUT_OD_SIZENUM (17*17)
#define OVI_HW_O20_INPUT_LOD_SIZENUM (876)
#define OVI_HW_O20_INPUT_POD2_SIZENUM (1848)
#define OVI_HW_O20_INPUT_TSCIC_CTRL_SIZENUM (43)
#define OVI_HW_O20_INPUT_TSCIC_DATA_SIZE (377612)
#define OVI_HW_O20_INPUT_VCOM_PAT_DATA_SIZE (96)
#define OVI_HW_O20_WB_GAIN_STEP1 26	// 0.26% step per w/b gain 1
#define OVI_HW_O20_WB_GAIN_STEP2 36	// 0.36% step per w/b gain 1
#define OVI_HW_O20_WB_OFFSET_STEP 8	// 8 step per w/b offset 1
#define OVI_HW_O20_WB_DEFAULT_GAIN 16384
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
#define OVI_HW_F20_REG_DUMMY 0xF03425B8
#define OVI_HW_F20_REG_DPG_LUT_WDATA 0xF0367A08
#define OVI_HW_F20_REG_DPG_LUT_WR_DONE 0xF0367A04
#define OVI_HW_F20_REG_DPG_EN 0xF0367A00
#define OVI_HW_F20_REG_WB_EN 0xF0367AC0
#define OVI_HW_F20_REG_WB_R_GAIN 0xF0367AC4
#define OVI_HW_F20_REG_WB_G_GAIN 0xF0367AC8
#define OVI_HW_F20_REG_WB_B_GAIN 0xF0367ACC
#define OVI_HW_F20_REG_WB_R_OFFSET 0xF0367AD0
#define OVI_HW_F20_REG_WB_G_OFFSET 0xF0367AD4
#define OVI_HW_F20_REG_WB_B_OFFSET 0xF0367AD8

#define _B2L32(data) ((((data) >> 24) & 0x000000ff) |   \
         			(((data) >>  8) & 0x0000ff00) |   \
         			(((data) <<  8) & 0x00ff0000) |   \
         			(((data) << 24) & 0xff000000))
#endif

#define OVI_REG_WR(address,data)   \
	gMapped_address=(volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) break;\
		*gMapped_address = data;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#define OVI_REG_RD(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*gMapped_address;\
		iounmap((void *)gMapped_address);\
	}while(0);\


#define OVI_HW_O20_CH_POWER_REG_MASK	0x00FFFFFF

#define OVI_HW_O20_REG_PARAM_OP_WRITE		0x0
#define OVI_HW_O20_REG_PARAM_OP_WAIT		0x1
#define OVI_HW_O20_REG_PARAM_OP_CHECK		0x2
#define OVI_HW_O20_REG_PARAM_OP_RESERVED	0x3
#define OVI_HW_O20_REG_PARAM_OP_MASK		0x3

#define OVI_HW_O20_REG_SET_A0_START		0x000000A0
#define OVI_HW_O20_REG_SET_B0_START		0x000000B0
// Max Value < 0x000000A0
#define OVI_HW_O20_REG_READ_START		0x00000001
#define OVI_HW_O20_REG_CHECK_END		0x00000000

#define OVI_HW_O20_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define OVI_HW_O20_BOE_FW_SIZE 32256

/* GET_RESULT_RF *10 */
#define GET_RESULT_RF(ACCURACY) \
({ \
	UINT32 v = 0; \
	if(ACCURACY == 3) v = 10; \
	if(ACCURACY == 2) v = 10; \
	if(ACCURACY == 1) v = 20; \
	if(ACCURACY == 0 || ACCURACY >= 4) v = 40; \
	v; \
})

/* SPREAD_RATIO_OUT * 1000 */
#define SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF) \
		( (UPDN_MAX)*1000 * 50 * RESULT_RF / (60*((4*NPC)+NSC)) )

#define MOD_FREQ_OUT(FIN, M, MOD_FREQ, UPDN_MAX) \
		( (FIN/M) * 1000000 / ((MOD_FREQ+1)*((4*UPDN_MAX)+2)) )

#define FIN_DISP		(54) //DISP FIN
#define GETBIT_M(reg,bit) ((reg >> (bit)) & 1)
#define SETBIT_M(reg,bit) ((reg)|=((0x1)<<(bit)))
#define CLRBIT_M(reg,bit) ((reg)&=~((0x1)<<(bit)))

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	struct delayed_work dlyWork;
	UINT32 *pu32LutR;
	UINT32 *pu32LutG;
	UINT32 *pu32LutB;
} OVI_HW_O20_DLY_RGB_GAMMA_T;

typedef struct {
	UINT32 chPowerOnRegValue1;
	UINT32 chPowerOnRegValue2;
	UINT32 tconBaseAddress;

	UINT32 spreadSpectrumRegValue1;
	UINT32 spreadSpectrumRegValue2;

	BOOLEAN wbEn;
	BOOLEAN wbBypassEn;
	BOOLEAN dgaEn;
	BOOLEAN dgaBypassEn;
	BOOLEAN mleModeOff;
	BOOLEAN odcBypassEn;
	
	UINT32 odcBypassRegFieldValue;
	UINT32 lodcBypassRegFieldValue;

	UINT32 horReverseRegFieldValue;	// Value for non-reverse

	LX_OVI_DISP_OUTPUT_MODE_T dispOutputMode;
	BOOLEAN isDispOutDisabled;

	UINT32 tconClkGatingRegValue;

	LX_OVI_DISPLAY_INFO_T dispOption; // use only for display resume
	LX_OVI_HW_DISPLAY_INFO_T hwDispOption;

	BOOLEAN mute;
	UINT32 mirrorV;

	struct task_struct* tscicThread;
	BOOLEAN tscicWritingFlag;
	UINT32 tscicSize;
	UINT32 *tscicU32Tbl;
	UINT32 tscicCtrlSizeNum;
	UINT8 *tscicU8CtrlData;
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
	void *pVx1ChipInfoVMapAddr;
	BE_OVI_HW_O20_VX1_CHIP_INFO_T *pVx1ChipInfo[BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_NUM];
#endif

	OVI_HW_O20_DLY_RGB_GAMMA_T delayedRGBGamma;
} OVI_HW_O20_INFO_T;

typedef struct{
	LX_OVI_OUTPUT_MODE_T	*pOVIOutputModes;
	UINT32 number_of_modes;
} OVI_HW_O20_OUTPUT_MODES_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E400    disp_aiopll0 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    rsv0                      :  1,    //      0 reserved
    reg_aiopll_fine_div       :  1,    //      1
    reg_aiopll_dss            :  1,    //      2
    reg_aiopll_accuracy       :  2,    //   4: 3
    reg_aiopll_updn_max       :  7,    //  11: 5
    reg_aiopll_mod_freq_max   :  9,    //  20:12
    reg_aiopll_m              :  6,    //  26:21
    rsv1                      :  1,    //     27 reserved
    reg_aiopll_cih            :  4;    //  31:28
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E404    disp_aiopll1 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_lock           :  1,    //      0
    rsv0                      :  3,    //   3: 1 reserved
    reg_aiopll_offset_mode    :  1,    //      4
    reg_aiopll_fout3_post_od  :  3,    //   7: 5
    reg_aiopll_fout2_post_od  :  3,    //  10: 8
    reg_aiopll_fout_od        :  2,    //  12:11
    reg_aiopll_fout3_pre_od   :  3,    //  15:13
    reg_aiopll_fout2_pre_od   :  3,    //  18:16
    reg_aiopll_nsc            :  4,    //  22:19
    reg_aiopll_npc            :  6,    //  28:23
    reg_aiopll_fine_control   :  3;    //  31:29
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O20A0_T;

/*-----------------------------------------------------------------------------------------
    0xC930_E408    disp_aiopll2 ''
-----------------------------------------------------------------------------------------*/
typedef struct {
    UINT32
    reg_aiopll_freq_update    :  1,    //      0
    rsv0                      :  3,    //   3: 1 reserved
    reg_aiopll_sync_on        :  1,    //      4
    rsv1                      :  3,    //   7: 5 reserved
    reg_aiopll_in_sel         :  1,    //      8
    rsv2                      :  3,    //  11: 9 reserved
    reg_aiopll_pdb            :  1,    //     12
    rsv3                      :  9,    //  21:13 reserved
    reg_aiopll_wake_bypass    :  1,    //     22
    reg_aiopll_ddr_mode       :  1,    //     23
    reg_aiopll_offset         :  8;    //  31:24
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_O20A0_T;


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T *gpOviTconMem;
extern DPE_LED_REG_O20_T gDPE_LED_O20;
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
extern BE_FRM_MEM_CFG_T *gpBeChInfMem;
#endif

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
OVI_TCON_REG_O20_T gOVI_TCON_O20;
OVI_TCON_LODC_REG_O20_T gOVI_TCON_LODC_O20;
OVI_TCON_CAD_REG_O20_T gOVI_TCON_CAD_O20;
OVI_OIF_REG_O20_T gOVI_OIF_O20;

static volatile unsigned int *gMapped_address;

LX_OVI_OUTPUT_MODE_T _gOVIOutputModes_O20Ax[] =
{
	{"Disp-O20 4k60Hz Vx1\n",  ovi_o20a0_disp_4k60_vx1_8lane, sizeof(ovi_o20a0_disp_4k60_vx1_8lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-O20 4k120Hz Vx1\n",  ovi_o20a0_disp_4k120_vx1_16lane, sizeof(ovi_o20a0_disp_4k120_vx1_16lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-O20 4k120Hz Vx1 5Byte\n",  ovi_o20a0_disp_4k120_vx1_16lane_5byte, sizeof(ovi_o20a0_disp_4k120_vx1_16lane_5byte)/sizeof(LX_OVI_REG_T)},
	{"Disp-O20 4k120Hz EPI 12LANE RGB\n",  ovi_o20a0_disp_4k120_epi_v19_12lane_rgb, sizeof(ovi_o20a0_disp_4k120_epi_v19_12lane_rgb)/sizeof(LX_OVI_REG_T)}
};

OVI_HW_O20_OUTPUT_MODES_T _gOVIOutputModes_O20 =
{
	.pOVIOutputModes 	 = NULL,
	.number_of_modes	 = 0,
};

volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O20A0_T *gOVI_HW_O20_SS_CTRL1 = NULL;
volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O20A0_T *gOVI_HW_O20_SS_CTRL2 = NULL;
volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_O20A0_T *gOVI_HW_O20_SS_CTRL3 = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static UINT32 _OVI_O20_GetGain(UINT32 gain);
static SINT16 _OVI_O20_GetOffset(UINT32 offset);
static void _OVI_O20_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore);
static void _OVI_O20_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);
static void _OVI_O20_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);

//static void _OVI_O20_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_O20_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_O20_DispOutputEnable(BOOLEAN bParam);
static void _OVI_O20_GetHWDispOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);

static void _OVI_O20_CallbackDelayedGamma(struct work_struct *work);

#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
static int _OVI_O20_Vx1ChipInfoMemInit(void);
static void _OVI_O20_Vx1ChipInfoMemFill(void);
#endif

/*----------------------------------------------------------------------------------------
	Internal Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int OVI_O20_TscicWriteThread(void* data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _gPrevRedGain = OVI_HW_O20_WB_DEFAULT_GAIN;
static UINT32 _gPrevGreenGain = OVI_HW_O20_WB_DEFAULT_GAIN;
static UINT32 _gPrevBlueGain = OVI_HW_O20_WB_DEFAULT_GAIN;

static SINT16 _gPrevRedOffset = 0;
static SINT16 _gPrevGreenOffset = 0;
static SINT16 _gPrevBlueOffset = 0;

static LX_OVI_TCON_COLOR_TEMP_T _gColTemp;

static OVI_HW_O20_INFO_T _gOviHwO20Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
static void _OVI_O20_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore)
{
	if (regParamVal >= OVI_HW_O20_REG_SET_A0_START)
	{
		if (lx_chip_rev() >= LX_CHIP_REV(O20, B0))
		{
			if (regParamVal != OVI_HW_O20_REG_SET_B0_START)
			{
				*pbIgnore = TRUE;
			}
		}
		else
		{
			if (regParamVal != OVI_HW_O20_REG_SET_A0_START)
			{
				*pbIgnore = TRUE;
			}
		}
	}
	else if (regParamVal == OVI_HW_O20_REG_CHECK_END)
	{
		*pbIgnore = FALSE;
	}

	return;
}

static void _OVI_O20_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN ignore = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_O20_REG_PARAM_OP_MASK)
		{
			case OVI_HW_O20_REG_PARAM_OP_WAIT:	// wait
				if (!ignore)
				{
					OS_UsecDelay(param->value);
				}
				OVI_DEBUG("delay(_%dms);\n", param->value/1000);
				break;

			case OVI_HW_O20_REG_PARAM_OP_CHECK:	// check
				_OVI_O20_IgnoreRegSet(param->value, &ignore);
				OVI_DEBUG("ignore : %d\n", ignore);
				break;

			case OVI_HW_O20_REG_PARAM_OP_RESERVED:
				OVI_DEBUG("OVI_HW_O20_REG_PARAM_OP_RESERVED\n");
				break;

			default:	// OVI_HW_O20_REG_PARAM_OP_WRITE
				if (!ignore)
				{
					OVI_REG_WR((param->addr + addrOffset), param->value);
				}
				OVI_DEBUG("REG_WRITE( 0x%08x, 0x%08x);\n", (param->addr + addrOffset), param->value);
				break;
		}
		
		param++;
	}
}

static void _OVI_O20_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN readReg = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_O20_REG_PARAM_OP_MASK)
		{
			case OVI_HW_O20_REG_PARAM_OP_CHECK:	// check for register read
				if (param->value == OVI_HW_O20_REG_READ_START)
				{
					readReg = TRUE;
				}
				else if (param->value == OVI_HW_O20_REG_CHECK_END)
				{
					readReg = FALSE;
				}
				OVI_DEBUG("readReg : %d\n", readReg);
				break;

			default:	// OVI_HW_O20_REG_PARAM_OP_WRITE
				if (readReg)
				{
					OVI_REG_RD((param->addr + addrOffset), param->value);
				}
				OVI_DEBUG("REG_READ( 0x%08x, 0x%08x);\n", (param->addr + addrOffset), param->value);
				break;
		}
		
		param++;
	}
}

#if 0
static void _OVI_O20_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					_OVI_O20_RegParamRead(ovi_o20a0_disp_2k60_lvds_2link, 
											OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_2k60_lvds_2link), 0);
					break;
					
				case LX_OVI_PANEL_VX1:
				default :
					_OVI_O20_RegParamRead(ovi_o20a0_disp_4k60_vx1_8lane, 
											OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k60_vx1_8lane), 0);
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					_OVI_O20_RegParamRead(ovi_o20a0_disp_4k120_epi_v19_12lane_rgb, 
											OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k120_epi_v19_12lane_rgb), 0);
					break;

				case LX_OVI_PANEL_LVDS:
					_OVI_O20_RegParamRead(ovi_o20a0_disp_2k120_lvds_4link, 
											OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_2k120_lvds_4link), 0);
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						_OVI_O20_RegParamRead(ovi_o20a0_disp_4k120_vx1_16lane_5byte, 
												OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k120_vx1_16lane_5byte), 0);
					}	
					else
					{
						_OVI_O20_RegParamRead(ovi_o20a0_disp_4k120_vx1_16lane, 
												OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k120_vx1_16lane), 0);
					}
					break;
			}
			break;

		default :
			break;
	}
	
	return;
}
#endif

static void _OVI_O20_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;

	OVI_PRINT("\n[_OVI_O20_DispInit] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
		pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
		pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
		pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	// Display Spread Spectrum
	if (_gOviHwO20Info.spreadSpectrumRegValue1 & 0x4) // DSS OFF
	{
		OVI_REG_WR(0xC9300C30, 0x00003EFF); //Power Down for DISP PLL setting (not for DISP SS setting)
		
		OVI_REG_WR(0xC930E400, _gOviHwO20Info.spreadSpectrumRegValue1);
		OVI_REG_WR(0xC930E404, _gOviHwO20Info.spreadSpectrumRegValue2);

		OVI_REG_WR(0xC9300C30, 0x00003FFF); //Power On
	}
	else
	{
		OVI_REG_WR(0xC9300C30, 0x00003EFF); //Power Down for DISP PLL setting (not for DISP SS setting)
		
		OVI_REG_WR(0xC930E400, _gOviHwO20Info.spreadSpectrumRegValue1 | 0x4);
		OVI_REG_WR(0xC930E404, _gOviHwO20Info.spreadSpectrumRegValue2);
		OVI_REG_WR(0xC930E408, 0x01400000);

		OVI_REG_WR(0xC9300C30, 0x00003FFF); //Power On

		OS_UsecDelay(100);

		OVI_REG_WR(0xC930E400, _gOviHwO20Info.spreadSpectrumRegValue1);
	}
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					_OVI_O20_RegParamSet(ovi_o20a0_disp_2k60_lvds_2link, 
											OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_2k60_lvds_2link), 0);

					if (stDispParams.lvdsType == LX_OVI_LVDS_OUT_JEIDA)
					{
						OVI_REG_WR(0xC907901C, 0x1814E);
					}
					break;
					
				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F20)
					{
						_OVI_O20_RegParamSet(ovi_o20a0_disp_4k120_vx1_20lane, 
												OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k120_vx1_20lane), 0);
					}
					else
					{
						_OVI_O20_RegParamSet(ovi_o20a0_disp_4k60_vx1_8lane, 
												OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k60_vx1_8lane), 0);
					}
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					_OVI_O20_RegParamSet(ovi_o20a0_disp_4k120_epi_v19_12lane_rgb, 
											OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k120_epi_v19_12lane_rgb), 0);
					break;

				case LX_OVI_PANEL_LVDS:
					_OVI_O20_RegParamSet(ovi_o20a0_disp_2k120_lvds_4link, 
											OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_2k120_lvds_4link), 0);
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F20)
					{
						_OVI_O20_RegParamSet(ovi_o20a0_disp_4k120_vx1_20lane, 
												OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k120_vx1_20lane), 0);
					}
					else if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						_OVI_O20_RegParamSet(ovi_o20a0_disp_4k120_vx1_16lane_5byte, 
												OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k120_vx1_16lane_5byte), 0);
					}	
					else
					{
						_OVI_O20_RegParamSet(ovi_o20a0_disp_4k120_vx1_16lane, 
												OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_4k120_vx1_16lane), 0);
					}
					break;
			}
			break;

		default :
			break;
	}

	_OVI_O20_RegParamSet(ovi_o20a0_disp_preEmp_swiLvl, 
												OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_preEmp_swiLvl), 0);

	// Clock Gating ON
	OVI_REG_WR(0xC930F000, _gOviHwO20Info.tconClkGatingRegValue);
	
	return;
}

static void _OVI_O20_DispOutputEnable(BOOLEAN bParam)
{
	CTOP_CTRL_O20Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
	if(bParam)// display output on
	{
		CTOP_CTRL_O20Ax_Wr(CTOP_DPE, ctop_dpe_r42, _gOviHwO20Info.chPowerOnRegValue1);
		OVI_DEBUG("[OVI] display is changed to ON status!\n");

#if 0 // used for O18 8k model
		if ((_gOviHwO20Info.dispOutputMode == LX_OVI_DISP_OUTPUT_MODE_4K120)
			|| (_gOviHwO20Info.dispOutputMode == LX_OVI_DISP_OUTPUT_MODE_4KVRR)
			|| (_gOviHwO20Info.dispOutputMode == LX_OVI_DISP_OUTPUT_MODE_4K4K60LR))
		{
			CTOP_CTRL_O20Ax_Wr01(CTOP_DPE, ctop_dpe_r42, reg_c4_pdb_ch12, 0x1);
			CTOP_CTRL_O20Ax_Wr01(CTOP_DPE, ctop_dpe_r42, reg_c4_pdb_ch13, 0x1);
			CTOP_CTRL_O20Ax_Wr01(CTOP_DPE, ctop_dpe_r42, reg_c4_pdb_ch14, 0x1);
			CTOP_CTRL_O20Ax_Wr01(CTOP_DPE, ctop_dpe_r42, reg_c4_pdb_ch15, 0x1);
			CTOP_CTRL_O20Ax_Wr01(CTOP_DPE, ctop_dpe_r42, reg_c4_pdb_ch16, 0x1);
			CTOP_CTRL_O20Ax_Wr01(CTOP_DPE, ctop_dpe_r42, reg_c4_pdb_ch17, 0x1);
			CTOP_CTRL_O20Ax_Wr01(CTOP_DPE, ctop_dpe_r42, reg_c4_pdb_ch18, 0x1);
			CTOP_CTRL_O20Ax_Wr01(CTOP_DPE, ctop_dpe_r42, reg_c4_pdb_ch19, 0x1);
		}
#endif
	}
	else // display output off
	{
		CTOP_CTRL_O20Ax_Wr(CTOP_DPE, ctop_dpe_r42, _gOviHwO20Info.chPowerOnRegValue1 & (~OVI_HW_O20_CH_POWER_REG_MASK));
		OVI_DEBUG("[OVI] display is changed to OFF status!\n");
	}
	CTOP_CTRL_O20Ax_WrFL(CTOP_DPE, ctop_dpe_r42);

	if (bParam) // display output on
	{
		OS_UsecDelay(100);
			
		CTOP_CTRL_O20Ax_RdFL(CTOP_DPE, ctop_dpe_r40);
		CTOP_CTRL_O20Ax_Wr(CTOP_DPE, ctop_dpe_r40, _gOviHwO20Info.chPowerOnRegValue2);
		CTOP_CTRL_O20Ax_WrFL(CTOP_DPE, ctop_dpe_r40);
	}
	else // display output off
	{
		
		CTOP_CTRL_O20Ax_RdFL(CTOP_DPE, ctop_dpe_r40);
		CTOP_CTRL_O20Ax_Wr(CTOP_DPE, ctop_dpe_r40, _gOviHwO20Info.chPowerOnRegValue2 & (~0x4));
		CTOP_CTRL_O20Ax_WrFL(CTOP_DPE, ctop_dpe_r40);
	}

	_gOviHwO20Info.isDispOutDisabled = bParam ? FALSE : TRUE;
	
	return;
}

/* Notice!! : 
Cannot use block register macro(ex. CTOP_CTRL_..., OVI_TCON_...) - because of the function call timing */
static void _OVI_O20_GetHWDispOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
{
	char hw_opt[32];
	LX_OVI_HW_DISPLAY_INFO_T dispOpt;

	dispOpt.panelInterface = LX_OVI_PANEL_VX1;
	dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_3840X2160;
	dispOpt.frcChipType = LX_OVI_FRC_CHIP_INTERNAL;
	dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_EDGE_LED;
	dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
	dispOpt.isVx15Byte = FALSE;

	if(RET_OK==OS_ScanKernelCmdline("hwopt=%s", hw_opt))
	{
		if (hw_opt[1] == '1') // Vx1 5Byte
		{
			dispOpt.isVx15Byte = TRUE;
		}

		if (hw_opt[2] == '0') // EPI
		{
			dispOpt.panelInterface = LX_OVI_PANEL_EPI;
		}
		else if (hw_opt[2] == '1') // LVDS
		{
			dispOpt.panelInterface = LX_OVI_PANEL_LVDS;
		}
		else if (hw_opt[2] == '3') // CEDS
		{
			dispOpt.panelInterface = LX_OVI_PANEL_CEDS;
		}
		else if (hw_opt[2] == '4') // EPI_QSAC
		{
			dispOpt.panelInterface = LX_OVI_PANEL_EPI_QSAC;
		}

		if (hw_opt[3] == '1') // FHD resolution
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
		}
		else if (hw_opt[3] == '3') // 8k resolution
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_7680X4320;
		}

		if (hw_opt[4] == '0') // NO FRC
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
		}

		if (hw_opt[12] == '1') // OLED
		{
			dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
		}

		if (hw_opt[17] == '8') // FRC type F20
		{
			dispOpt.frcChipType = LX_OVI_FRC_CHIP_UD_BE_F20;
		}

		if ((hw_opt[3] == '3') || (hw_opt[17] == '8')) // 8k
		{
			if (hw_opt[9] == '0') // panel output framerate 60Hz
			{
				dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			}
			else
			{
				dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
			}
		}
	}
	else
	{
		UINT32 regVal;
		
		/* 2k/4k model
		(4k 60Hz : 0xC930F008[13:11] - 1, 4k 120Hz : 0xC930F008[13:11] - 0)
		(2k 60Hz : 0xC930F008[13:11] - 3, 2k 120Hz : 0xC930F008[13:11] - 2)
		*/
		OVI_REG_RD(0xC930F008, regVal);
		regVal = (regVal >> 11) & 0x7;
		if (regVal == 1 || regVal == 3)
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
		}

		OVI_REG_RD(0xC930F008, regVal);
		regVal = (regVal >> 17) & 0x3;
		if (regVal == 2)
		{
			dispOpt.frcChipType = LX_OVI_FRC_CHIP_UD_BE_F20;
		}
	}

	if (RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
	{
		if (!strncmp(hw_opt,"hdmi",4))
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
		}

		if (!strncmp(hw_opt,"4byte",5))
		{
			dispOpt.isVx15Byte = FALSE;
		}
		else if (!strncmp(hw_opt,"5byte",5))
		{
			dispOpt.isVx15Byte = TRUE;
		}
	}

	if(RET_OK==OS_ScanKernelCmdline("dispopts=%s", hw_opt))
	{
		if(strstr(hw_opt,"1920x1080"))
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
		}
		else if (strstr(hw_opt,"1366x768"))
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
		}
		else if (strstr(hw_opt,"1280x720"))
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1280X720;
		}

		if (strstr(hw_opt,"stb"))
		{
			dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_NONE;
		}
	}

	memcpy((void *)pstParams, (void *)&dispOpt, sizeof(LX_OVI_HW_DISPLAY_INFO_T));
	
	return;
}

static void _OVI_O20_CallbackDelayedGamma(struct work_struct *work)
{
	int i;
	UINT32 regField;

	if ((_gOviHwO20Info.delayedRGBGamma.pu32LutR == NULL)
		|| (_gOviHwO20Info.delayedRGBGamma.pu32LutG == NULL)
		|| (_gOviHwO20Info.delayedRGBGamma.pu32LutB == NULL)) return;

	OVI_DEBUG("\n\nRetry Gamma setting!\n\n\r");

	DPE_LED_O20_RdFL(led_dpg_lut_wr_done);
	DPE_LED_O20_Rd01(led_dpg_lut_wr_done, dpg_lut_wr_status, regField);

	if (regField)
	{
		schedule_delayed_work(&_gOviHwO20Info.delayedRGBGamma.dlyWork, msecs_to_jiffies(10));
	}
	else
	{
		DPE_LED_O20_RdFL(led_dpg_lut_wdata);

		/* Setting Red Gamma Table */
		for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwO20Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_O20_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Green Gamma Table */
		for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwO20Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_O20_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Blue Gamma Table */
		for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwO20Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_O20_WrFL(led_dpg_lut_wdata);
		}

		DPE_LED_O20_RdFL(led_dpg_lut_wr_done);
		DPE_LED_O20_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
		DPE_LED_O20_WrFL(led_dpg_lut_wr_done);

		vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutR);
		vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutG);
		vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutB);
		_gOviHwO20Info.delayedRGBGamma.pu32LutR = NULL;
		_gOviHwO20Info.delayedRGBGamma.pu32LutG = NULL;
		_gOviHwO20Info.delayedRGBGamma.pu32LutB = NULL;
	}
}

#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
static int _OVI_O20_Vx1ChipInfoMemInit(void)
{
	int ret = RET_OK;
	int i;
	#ifdef PQE_NEW_MAP
	BE_FRM_MEM_CFG_T chInfMem = {.frame_base = g_chipinfo.base, .frame_size = g_chipinfo.size};
	BE_FRM_MEM_CFG_T *pChInfMem = &chInfMem;
	#else
	BE_FRM_MEM_CFG_T *pChInfMem = gpBeChInfMem;
	#endif

	do {
		_gOviHwO20Info.pVx1ChipInfoVMapAddr = NULL;

		if (_gOviHwO20Info.hwDispOption.frcChipType != LX_OVI_FRC_CHIP_UD_BE_F20) break;
		
		if (pChInfMem == NULL 
			|| !pChInfMem->frame_base)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		if ((pChInfMem->frame_size != BE_OVI_HW_O20_VX1_CHIP_INFO_TOTAL_MEM_SIZE)
			|| (sizeof(BE_OVI_HW_O20_VX1_CHIP_INFO_T) != BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_PACK_SIZE))
		{
			OVI_ERROR("[OVI] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		_gOviHwO20Info.pVx1ChipInfoVMapAddr = vmap_phys(pChInfMem->frame_base, pChInfMem->frame_size);
		if (_gOviHwO20Info.pVx1ChipInfoVMapAddr == NULL)
		{
			OVI_ERROR("[OVI] pVMapAddr is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		for (i=0; i<BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
		{
			if (pChInfMem->frame_size < ((BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
											+BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET \
											+sizeof(BE_OVI_HW_O20_VX1_CHIP_INFO_T))) break;
			
			_gOviHwO20Info.pVx1ChipInfo[i] = (BE_OVI_HW_O20_VX1_CHIP_INFO_T *)(_gOviHwO20Info.pVx1ChipInfoVMapAddr \
																			+(BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
																			+BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
		}
		if (i != BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_NUM)
		{
			OVI_ERROR("[OVI] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		_OVI_O20_Vx1ChipInfoMemFill();
	} while(0);

	if (ret && (_gOviHwO20Info.pVx1ChipInfoVMapAddr != NULL))
	{
		vunmap_phys(_gOviHwO20Info.pVx1ChipInfoVMapAddr);
		_gOviHwO20Info.pVx1ChipInfoVMapAddr = NULL;
	}

	return ret;
}

static void _OVI_O20_Vx1ChipInfoMemFill(void)
{
	int i;
	UINT32 *addr;
	
	if (_gOviHwO20Info.pVx1ChipInfoVMapAddr == NULL) return;

	// Fill in HDR/CRC with default value for BUFF
	for (i=0; i<BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_TOTAL_NUM; i++)
	{
		addr = (UINT32 *)(_gOviHwO20Info.pVx1ChipInfoVMapAddr+ \
							(i*BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_SIZE)+BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
		addr[0] = _B2L32(BE_OVI_HW_O20_VX1_CHIP_INFO_HDR|BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_SIZE);
		addr[1] = 0;
#else
		*addr = _B2L32(0x0EE00000|BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_DATA_SIZE);
#endif
	}

	for (i=0; i<BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
	{
		// Fill in HDR/CRC for BUFF0,3
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.info.maxNum = BE_OVI_HW_O20_VX1_CHIP_INFO_APB_NUM;
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.info.bufIdx0 = 0;
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.info.bufIdx1 = 3;
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.info.version = 0;
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.info.u32Data = _B2L32(_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.info.u32Data);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data = 0;
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.cnt1.u32Data = 0;
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.cnt2.u32Data = 0;
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.cnt3.u32Data = 0;
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O20_VX1_CHIP_INFO_DPG].offset = 0xFFFF & offsetof(BE_OVI_HW_O20_VX1_CHIP_INFO_T, dpg);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O20_VX1_CHIP_INFO_DPG].size = 0xFFFF & sizeof(_gOviHwO20Info.pVx1ChipInfo[i]->dpg);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O20_VX1_CHIP_INFO_DPG].u32Data \
													= _B2L32(_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O20_VX1_CHIP_INFO_DPG].u32Data);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O20_VX1_CHIP_INFO_CLR_TMP].offset = 0xFFFF & offsetof(BE_OVI_HW_O20_VX1_CHIP_INFO_T, colorTemp);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O20_VX1_CHIP_INFO_CLR_TMP].size = 0xFFFF & sizeof(_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O20_VX1_CHIP_INFO_CLR_TMP].u32Data \
													= _B2L32(_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O20_VX1_CHIP_INFO_CLR_TMP].u32Data);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_LED_CTRL].offset = 0xFFFF & offsetof(BE_OVI_HW_O20_VX1_CHIP_INFO_T, ledSpiCtrl);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_LED_CTRL].size = 0xFFFF & sizeof(_gOviHwO20Info.pVx1ChipInfo[i]->ledSpiCtrl);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_LED_CTRL].u32Data \
													= _B2L32(_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_LED_CTRL].u32Data);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_PCC].offset = 0xFFFF & offsetof(BE_OVI_HW_O20_VX1_CHIP_INFO_T, pcc);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_PCC].size = 0xFFFF & sizeof(_gOviHwO20Info.pVx1ChipInfo[i]->pcc);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_PCC].u32Data \
													= _B2L32(_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_PCC].u32Data);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_OSD_LVL].offset = 0xFFFF & offsetof(BE_OVI_HW_O20_VX1_CHIP_INFO_T, osdLvCtrl);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_OSD_LVL].size = 0xFFFF & sizeof(_gOviHwO20Info.pVx1ChipInfo[i]->osdLvCtrl);
		_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_OSD_LVL].u32Data \
													= _B2L32(_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O20_VX1_CHIP_INFO_OSD_LVL].u32Data);
		_gOviHwO20Info.pVx1ChipInfo[i]->hwCrc = 0xFFFFFFFF;
		_gOviHwO20Info.pVx1ChipInfo[i]->endPacket = _B2L32(BE_OVI_HW_O20_VX1_CHIP_INFO_EP);
#else
		_gOviHwO20Info.pVx1ChipInfo[i]->dpg.dataHwHdr = _B2L32(0x0EE00000|OVI_HW_O20_VX1_CHIP_INFO_DPG_DATA_SIZE); 
		_gOviHwO20Info.pVx1ChipInfo[i]->dpg.dataHwCrc = 0xFFFFFFFF;
		_gOviHwO20Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr = _B2L32(0x0EE00000|OVI_HW_O20_VX1_CHIP_INFO_DPG_CTRL_SIZE); 
		_gOviHwO20Info.pVx1ChipInfo[i]->dpg.ctrlHwCrc = 0xFFFFFFFF;
		_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32(0x0EE00000|OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_SIZE); 
		_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
		_gOviHwO20Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O20_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE); 
		_gOviHwO20Info.pVx1ChipInfo[i]->ledSpiCtrl.hwCrc = 0xFFFFFFFF;
		_gOviHwO20Info.pVx1ChipInfo[i]->pcc.hwHdr = _B2L32(0x0EE00000|BE_HW_O20_VX1_CHIP_INFO_PCC_SIZE); 
		_gOviHwO20Info.pVx1ChipInfo[i]->pcc.hwCrc = 0xFFFFFFFF;
		_gOviHwO20Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O20_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE);
		_gOviHwO20Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
		_gOviHwO20Info.pVx1ChipInfo[i]->rsvd.hwHdr = _B2L32(0x0EE00000|BE_HW_O20_VX1_CHIP_INFO_RSVD_SIZE);
		_gOviHwO20Info.pVx1ChipInfo[i]->rsvd.hwCrc = 0xFFFFFFFF; 
#endif
	}

	wmb();

	return;
}
#endif

int OVI_O20_TscicWriteThread(void* data)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr = NULL;
	UINT32 tscicSizeNum;
	UINT32 tscicCtrlSizeNum;

	do {

		if (_gOviHwO20Info.tscicWritingFlag == TRUE)
		{
			OVI_ERROR("[OVI] already running!\n");
			ret = RET_ERROR;
			return ret;
		}

		_gOviHwO20Info.tscicWritingFlag = TRUE;

		// check input table size
		if ((_gOviHwO20Info.tscicCtrlSizeNum != OVI_HW_O20_INPUT_TSCIC_CTRL_SIZENUM) || (_gOviHwO20Info.tscicU8CtrlData == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		if ((_gOviHwO20Info.tscicSize != OVI_HW_O20_INPUT_TSCIC_DATA_SIZE) || (_gOviHwO20Info.tscicU32Tbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		tscicSizeNum = _gOviHwO20Info.tscicSize / sizeof(UINT32);
		tscicCtrlSizeNum = _gOviHwO20Info.tscicCtrlSizeNum;

		// FCIC data setting
		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_O20A0_BASE + offsetof(OVI_TCON_REG_O20A0_T, tcon_fcic_data_a), 
											sizeof(UINT32));
		if (regAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		OVI_TCON_O20_RdFL(tcon_fcic_ctrl);
		OVI_TCON_O20_Wr01(tcon_fcic_ctrl, checksum_clr, 0x0);
		OVI_TCON_O20_Wr01(tcon_fcic_ctrl, flash_done, 0x0);
		OVI_TCON_O20_WrFL(tcon_fcic_ctrl);

		OVI_TCON_O20_RdFL(tcon_fcic_addr);
		OVI_TCON_O20_Wr01(tcon_fcic_addr, flash_addr, 0x0);
		OVI_TCON_O20_WrFL(tcon_fcic_addr);

		for (i=0; i<tscicSizeNum; i++)
		{
			if (kthread_should_stop())
			{
				ret = RET_ERROR;

				if(_gOviHwO20Info.tscicU8CtrlData != NULL)
				{
					vfree(_gOviHwO20Info.tscicU8CtrlData);
					_gOviHwO20Info.tscicU8CtrlData = NULL;
				}
				if (_gOviHwO20Info.tscicU32Tbl != NULL)
				{
					vfree(_gOviHwO20Info.tscicU32Tbl);
					_gOviHwO20Info.tscicU32Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwO20Info.tscicThread = NULL;
				_gOviHwO20Info.tscicWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwO20Info.tscicU32Tbl[i], &regAddr[0]);
		}

		OVI_TCON_O20_RdFL(tcon_fcic_ctrl);
		OVI_TCON_O20_Wr01(tcon_fcic_ctrl, flash_done, 0x1);
		OVI_TCON_O20_WrFL(tcon_fcic_ctrl);

		iounmap((void *)regAddr);
		regAddr = NULL;

		// FCIC CTRL data setting
		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_O20A0_BASE + offsetof(OVI_TCON_REG_O20A0_T, tcon_cic_reg000), 
											sizeof(UINT32)*OVI_HW_O20_INPUT_TSCIC_CTRL_SIZENUM);
		if (regAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		for(i=0; i<tscicCtrlSizeNum; i++)
		{
			if (kthread_should_stop())
			{
				ret = RET_ERROR;

				if(_gOviHwO20Info.tscicU8CtrlData != NULL)
				{
					vfree(_gOviHwO20Info.tscicU8CtrlData);
					_gOviHwO20Info.tscicU8CtrlData = NULL;
				}
				if (_gOviHwO20Info.tscicU32Tbl != NULL)
				{
					vfree(_gOviHwO20Info.tscicU32Tbl);
					_gOviHwO20Info.tscicU32Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwO20Info.tscicThread = NULL;
				_gOviHwO20Info.tscicWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwO20Info.tscicU8CtrlData[i], &regAddr[i]);
		}

		OVI_TCON_O20_RdFL(tcon_init_test);
		OVI_TCON_O20_Wr01(tcon_init_test, init1_test, 0x1);
		OVI_TCON_O20_Wr01(tcon_init_test, init2_test, 0x1);
		OVI_TCON_O20_WrFL(tcon_init_test);
	} while(0);

	if(_gOviHwO20Info.tscicU8CtrlData != NULL)
	{
		vfree(_gOviHwO20Info.tscicU8CtrlData);
		_gOviHwO20Info.tscicU8CtrlData = NULL;
	}
	if (_gOviHwO20Info.tscicU32Tbl != NULL)
	{
		vfree(_gOviHwO20Info.tscicU32Tbl);
		_gOviHwO20Info.tscicU32Tbl = NULL;
	}
	if (regAddr != NULL)
		iounmap((void *)regAddr);

	_gOviHwO20Info.tscicThread = NULL;
	_gOviHwO20Info.tscicWritingFlag = FALSE;

	return ret;
}

void OVI_HW_O20_HWDisplayOptionInit(void)
{
	OVI_PRINT("O20A0 OVI HW display option init!\n");

	_OVI_O20_GetHWDispOption(&_gOviHwO20Info.hwDispOption);
}

int OVI_HW_O20_PreInitialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("O20A0 OVI pre init!\n");

	} while(0);

	return ret;
}

int OVI_HW_O20_Initialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("OVI chip revision is set to O20 A0\n");
		
		/* Set configuration of Output mode presets, for mode change on run time */
		_gOVIOutputModes_O20.pOVIOutputModes = _gOVIOutputModes_O20Ax;
		_gOVIOutputModes_O20.number_of_modes	 = sizeof(_gOVIOutputModes_O20Ax)/sizeof(LX_OVI_OUTPUT_MODE_T);

		gOVI_TCON_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_REG_O20A0_T));
		gOVI_TCON_LODC_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_LODC_REG_O20A0_T));
		gOVI_TCON_CAD_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_CAD_REG_O20A0_T));
		gOVI_OIF_O20.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_OIF_REG_O20A0_T));

		gOVI_TCON_O20.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_O20A0_BASE, sizeof(OVI_TCON_REG_O20A0_T));
		gOVI_TCON_LODC_O20.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_O20A0_BASE, sizeof(OVI_TCON_LODC_REG_O20A0_T));
		gOVI_TCON_CAD_O20.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_O20A0_BASE, sizeof(OVI_TCON_CAD_REG_O20A0_T));
		gOVI_OIF_O20.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_O20A0_BASE, sizeof(OVI_OIF_REG_O20A0_T));

		/* for copying value used in channel power on/off function */
		CTOP_CTRL_O20Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
		_gOviHwO20Info.chPowerOnRegValue1 = CTOP_CTRL_O20Ax_Rd(CTOP_DPE, ctop_dpe_r42);
		CTOP_CTRL_O20Ax_RdFL(CTOP_DPE, ctop_dpe_r40);
		_gOviHwO20Info.chPowerOnRegValue2 = CTOP_CTRL_O20Ax_Rd(CTOP_DPE, ctop_dpe_r40);

		/* for copying value used in H-Reverse on/off function */
		OVI_TCON_O20_RdFL(tcon_hor_mode);
		OVI_TCON_O20_Rd01(tcon_hor_mode, hor_reverse, _gOviHwO20Info.horReverseRegFieldValue);

		/* for copying value used in spread spectrum on/off & display resume function */
		CTOP_CTRL_O20Ax_RdFL(CTOP_FMS, disp_aiopll0);
		_gOviHwO20Info.spreadSpectrumRegValue1 = CTOP_CTRL_O20Ax_Rd(CTOP_FMS, disp_aiopll0);
		CTOP_CTRL_O20Ax_RdFL(CTOP_FMS, disp_aiopll1);
		_gOviHwO20Info.spreadSpectrumRegValue2 = CTOP_CTRL_O20Ax_Rd(CTOP_FMS, disp_aiopll1);

		gOVI_HW_O20_SS_CTRL1 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O20A0_T *)ioremap(0xC930E400, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O20A0_T));
		gOVI_HW_O20_SS_CTRL2 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O20A0_T *)ioremap(0xC930E404, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O20A0_T));
		gOVI_HW_O20_SS_CTRL3 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_O20A0_T *)ioremap(0xC930E408, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_O20A0_T));

		/* for copying value used in display resume function */
		OVI_REG_RD(0xC930F000, _gOviHwO20Info.tconClkGatingRegValue);

#if 0
		/* for copying value used in display resume function */
		CTOP_CTRL_O20Ax_RdFL(DPE_SYN, crg_dpe00);
		_gOviHwO20Info.tconClkGatingRegValue = CTOP_CTRL_O20Ax_Rd(DPE_SYN, crg_dpe00);
#endif

		/* for copying value used in bypass function */
		OVI_TCON_O20_RdFL(tcon_odc_opt2);
		OVI_TCON_O20_Rd01(tcon_odc_opt2, odc_bypass, _gOviHwO20Info.odcBypassRegFieldValue); 
		OVI_TCON_O20_Rd01(tcon_odc_opt2, lodc_bypass, _gOviHwO20Info.lodcBypassRegFieldValue);

		/* Update pre-emphasis & swing level value used in display resume */
		_OVI_O20_RegParamRead(ovi_o20a0_disp_preEmp_swiLvl, 
											OVI_HW_O20_ARRAY_SIZE(ovi_o20a0_disp_preEmp_swiLvl), 0);

		_gOviHwO20Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		_gOviHwO20Info.tscicWritingFlag = FALSE;
		_gOviHwO20Info.tscicThread = NULL;
		_gOviHwO20Info.tscicU32Tbl = NULL;
		_gOviHwO20Info.tscicU8CtrlData = NULL;

		_gOviHwO20Info.delayedRGBGamma.pu32LutR = NULL;
		_gOviHwO20Info.delayedRGBGamma.pu32LutG = NULL;
		_gOviHwO20Info.delayedRGBGamma.pu32LutB = NULL;

		_gColTemp.bIsGet = 0;
		_gColTemp.r_gain = OVI_HW_O20_WB_DEFAULT_GAIN;
		_gColTemp.g_gain = OVI_HW_O20_WB_DEFAULT_GAIN;
		_gColTemp.b_gain = OVI_HW_O20_WB_DEFAULT_GAIN;
		_gColTemp.r_offset = 0;
		_gColTemp.g_offset = 0;
		_gColTemp.b_offset = 0;

		INIT_DELAYED_WORK(&_gOviHwO20Info.delayedRGBGamma.dlyWork, _OVI_O20_CallbackDelayedGamma);

#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
		ret = _OVI_O20_Vx1ChipInfoMemInit();
		if (ret)
		{
			OVI_ERROR("[OVI] Vx1 chip info memory init is failed!\n");
			OVI_BREAK_WRONG(ret);
		}
#endif

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base)
			|| (!gpOviTconMem->size))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! O20 ODC will be disabled!\n");

			_gOviHwO20Info.tconBaseAddress = NULL;
		}
		else
		{
			_gOviHwO20Info.tconBaseAddress = gpOviTconMem->base;

			OVI_TCON_O20_RdFL(tcon_base_address);
			OVI_TCON_O20_Wr(tcon_base_address, _gOviHwO20Info.tconBaseAddress);
			OVI_TCON_O20_WrFL(tcon_base_address);
		}
	} while(0);

	return ret;
}

int OVI_HW_O20_Close(void)
{
	int ret = RET_OK;

	cancel_delayed_work_sync(&_gOviHwO20Info.delayedRGBGamma.dlyWork);
	if (_gOviHwO20Info.delayedRGBGamma.pu32LutR != NULL) 
	{
		vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutR);
		_gOviHwO20Info.delayedRGBGamma.pu32LutR = NULL;
	}
	if (_gOviHwO20Info.delayedRGBGamma.pu32LutG != NULL) 
	{
		vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutG);
		_gOviHwO20Info.delayedRGBGamma.pu32LutG = NULL;
	}
	if (_gOviHwO20Info.delayedRGBGamma.pu32LutB != NULL) 
	{
		vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutB);
		_gOviHwO20Info.delayedRGBGamma.pu32LutB = NULL;
	}

	if(gOVI_TCON_O20.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_O20.shdw.addr);
		gOVI_TCON_O20.shdw.addr = NULL;
	}
	if(gOVI_TCON_LODC_O20.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_LODC_O20.shdw.addr);
		gOVI_TCON_LODC_O20.shdw.addr = NULL;
	}
	if(gOVI_TCON_CAD_O20.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_CAD_O20.shdw.addr);
		gOVI_TCON_CAD_O20.shdw.addr = NULL;
	}
	if(gOVI_OIF_O20.shdw.addr)
	{
		OS_Free((void *)gOVI_OIF_O20.shdw.addr);
		gOVI_OIF_O20.shdw.addr = NULL;
	}

	if (gOVI_TCON_O20.phys.addr)
	{
		iounmap((void *)gOVI_TCON_O20.phys.addr);
		gOVI_TCON_O20.phys.addr = NULL;
	}
	if (gOVI_TCON_LODC_O20.phys.addr)
	{
		iounmap((void *)gOVI_TCON_LODC_O20.phys.addr);
		gOVI_TCON_LODC_O20.phys.addr = NULL;
	}
	if (gOVI_TCON_CAD_O20.phys.addr)
	{
		iounmap((void *)gOVI_TCON_CAD_O20.phys.addr);
		gOVI_TCON_CAD_O20.phys.addr = NULL;
	}
	if (gOVI_OIF_O20.phys.addr)
	{
		iounmap((void *)gOVI_OIF_O20.phys.addr);
		gOVI_OIF_O20.phys.addr = NULL;
	}
	if (gOVI_HW_O20_SS_CTRL1)
	{
		iounmap((void *)gOVI_HW_O20_SS_CTRL1);
		gOVI_HW_O20_SS_CTRL1 = NULL;
	}
	if (gOVI_HW_O20_SS_CTRL2)
	{
		iounmap((void *)gOVI_HW_O20_SS_CTRL2);
		gOVI_HW_O20_SS_CTRL2 = NULL;
	}
	if (gOVI_HW_O20_SS_CTRL3)
	{
		iounmap((void *)gOVI_HW_O20_SS_CTRL3);
		gOVI_HW_O20_SS_CTRL3 = NULL;
	}
	
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
	if (_gOviHwO20Info.pVx1ChipInfoVMapAddr != NULL)
	{
		vunmap_phys(_gOviHwO20Info.pVx1ChipInfoVMapAddr);
		_gOviHwO20Info.pVx1ChipInfoVMapAddr = NULL;
	}
#endif

	return ret;
}

int OVI_HW_O20_Suspend(void)
{
	int ret = RET_OK;

	do {
		cancel_delayed_work_sync(&_gOviHwO20Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutR);
			_gOviHwO20Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutG);
			_gOviHwO20Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutB);
			_gOviHwO20Info.delayedRGBGamma.pu32LutB = NULL;
		}
	} while(0);

	return ret;
}

int OVI_HW_O20_EarlyResume(void)
{
	int ret = RET_OK;

	do {
		CTOP_CTRL_O20Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
		if (!(CTOP_CTRL_O20Ax_Rd(CTOP_DPE, ctop_dpe_r42) & OVI_HW_O20_CH_POWER_REG_MASK)) // Instant boot
		{
			_OVI_O20_DispInit(&_gOviHwO20Info.dispOption);
		}
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
		else
		{
			_OVI_O20_Vx1ChipInfoMemFill();
		}
#endif
	} while(0);

	return ret;
}

int OVI_HW_O20_Resume(void)
{
	int ret = RET_OK;

	do {
		CTOP_CTRL_O20Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
		if (!(CTOP_CTRL_O20Ax_Rd(CTOP_DPE, ctop_dpe_r42) & OVI_HW_O20_CH_POWER_REG_MASK)) // Instant boot
		{
			if (_gOviHwO20Info.tscicWritingFlag == TRUE)
			{
				if (_gOviHwO20Info.tscicThread != NULL)
				{
					kthread_stop(_gOviHwO20Info.tscicThread);
					_gOviHwO20Info.tscicThread = NULL;
				}

				_gOviHwO20Info.tscicWritingFlag = FALSE;
			}

			_gOviHwO20Info.isDispOutDisabled = TRUE;
		}

		_gOviHwO20Info.wbEn = FALSE;
		_gOviHwO20Info.wbBypassEn = FALSE;
		_gOviHwO20Info.dgaEn = FALSE;
		_gOviHwO20Info.dgaBypassEn = FALSE;
		_gOviHwO20Info.mleModeOff = FALSE;
		_gOviHwO20Info.odcBypassEn = FALSE;

		cancel_delayed_work_sync(&_gOviHwO20Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutR);
			_gOviHwO20Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutG);
			_gOviHwO20Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutB);
			_gOviHwO20Info.delayedRGBGamma.pu32LutB = NULL;
		}
		
		_gPrevRedGain = OVI_HW_O20_WB_DEFAULT_GAIN;
		_gPrevGreenGain = OVI_HW_O20_WB_DEFAULT_GAIN;
		_gPrevBlueGain = OVI_HW_O20_WB_DEFAULT_GAIN;

		_gPrevRedOffset = 0;
		_gPrevGreenOffset = 0;
		_gPrevBlueOffset = 0;

		_gOviHwO20Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base)
			|| (!gpOviTconMem->size))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! O20 ODC will be disabled!\n");

			_gOviHwO20Info.tconBaseAddress = NULL;
		}
		else
		{
			_gOviHwO20Info.tconBaseAddress = gpOviTconMem->base;

			OVI_TCON_O20_RdFL(tcon_base_address);
			OVI_TCON_O20_Wr(tcon_base_address, _gOviHwO20Info.tconBaseAddress);
			OVI_TCON_O20_WrFL(tcon_base_address);
		}
	} while(0);

	return ret;
}

#define OVI_HW_O20_OPT_BIT_MASK_STB (1<<0)
int OVI_HW_O20_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_PRINT("\n[OVI_HW_O20_SetDisplayOption] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
			pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
			pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
			pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
			pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

		memcpy((void *)&_gOviHwO20Info.dispOption, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

		if (!_gOviHwO20Info.dispOption.userSpecificOption.flags.SocOptionBIT31) // SocOptionBIT31 : 1 -> setDisplayOption debug mode
		{
			char hw_opt[32];
			
			// Forced settings by HW option(or boot option)
			_gOviHwO20Info.dispOption.panelInterface = _gOviHwO20Info.hwDispOption.panelInterface;
			_gOviHwO20Info.dispOption.panelFramerate = _gOviHwO20Info.hwDispOption.panelFramerate;
			if (_gOviHwO20Info.hwDispOption.isVx15Byte)
			{
				_gOviHwO20Info.dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
			}
			else
			{
				_gOviHwO20Info.dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
			}
			_gOviHwO20Info.dispOption.frcChipType = _gOviHwO20Info.hwDispOption.frcChipType;

			if (_gOviHwO20Info.hwDispOption.panelInterface == LX_OVI_PANEL_LVDS)
			{
				if ((RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
					&& (!strncmp(hw_opt,"hdmi",4)))
				{
					_gOviHwO20Info.dispOption.lvdsType = LX_OVI_LVDS_OUT_JEIDA;
				}
				else
				{
					_gOviHwO20Info.dispOption.lvdsType = LX_OVI_LVDS_OUT_VESA;
				}
			}
		}

		//_OVI_O20_DispRegDataInit(&_gOviHwO20Info.dispOption);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams)
{
	int ret = RET_OK;
	
	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		OVI_PRINT("\n[OVI_HW_O20_SetBypass] En[%d], Mask[0x%x]\n\r", pstParams->bEnable, pstParams->u32BlockMask);
		
		if ((pstParams->u32BlockMask & LX_OVI_TCON_BOE_RGBW)
			|| (pstParams->u32BlockMask & LX_OVI_TCON_LGD_RGBW))
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O20_RdFL(tcon_odc_opt2);
				OVI_TCON_O20_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_O20_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwO20Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_O20_RdFL(tcon_odc_opt2);
					OVI_TCON_O20_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwO20Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_O20_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwO20Info.odcBypassEn = pstParams->bEnable;
		}	

		if (pstParams->u32BlockMask & LX_OVI_TCON_GAMMA)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O20_RdFL(tcon_control);
				OVI_TCON_O20_Wr01(tcon_control, dga_en, 0x0);
				OVI_TCON_O20_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_O20_RdFL(tcon_control);
				OVI_TCON_O20_Wr01(tcon_control, dga_en, _gOviHwO20Info.dgaEn ? 0x1 : 0x0);
				OVI_TCON_O20_WrFL(tcon_control);
			}
			_gOviHwO20Info.dgaBypassEn = pstParams->bEnable;
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_WB)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O20_RdFL(tcon_control);
				OVI_TCON_O20_Wr01(tcon_control, wb_en, 0x0);
				OVI_TCON_O20_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_O20_RdFL(tcon_control);
				OVI_TCON_O20_Wr01(tcon_control, wb_en, _gOviHwO20Info.wbEn ? 0x1 : 0x0);
				OVI_TCON_O20_WrFL(tcon_control);
			}
			_gOviHwO20Info.wbBypassEn = pstParams->bEnable;
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_LODC)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O20_RdFL(tcon_odc_opt2);
				OVI_TCON_O20_Wr01(tcon_odc_opt2, lodc_bypass, 0x1);
				OVI_TCON_O20_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwO20Info.lodcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_O20_RdFL(tcon_odc_opt2);
					OVI_TCON_O20_Wr01(tcon_odc_opt2, lodc_bypass, 0x0);
					OVI_TCON_O20_WrFL(tcon_odc_opt2);
				}
			}
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_ODC)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O20_RdFL(tcon_odc_opt2);
				OVI_TCON_O20_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_O20_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwO20Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_O20_RdFL(tcon_odc_opt2);
					OVI_TCON_O20_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwO20Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_O20_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwO20Info.odcBypassEn = pstParams->bEnable;
		}
	} while(0);

	return ret;
}

int OVI_HW_O20_SetCombination(UINT32 param)
{
	int ret = RET_ERROR;
	int i,count;
	volatile LX_OVI_REG_T	*regs;
	char	*index;
	unsigned int read_data, same;
	BOOLEAN ignore = FALSE;

	do {
		/* Step 1. Check whether paramater is valid */
		if(param == 119) {	// Magic keyword to print available output modes...
			printk("\n[OVI] Display all register-set-presets ...\n");
			for(i=0; i<_gOVIOutputModes_O20.number_of_modes;i++)
			{
				printk("  Index[%d] : %s", i,_gOVIOutputModes_O20.pOVIOutputModes[i].index);
			}
			ret = RET_OK;
			break;
		}
		else if(param >= 10000)
		{
			param = param - 10000;
			printk("\n[OVI] Compare register values regarding to register-set index[%d]", param);

			if(param > _gOVIOutputModes_O20.number_of_modes) {
				OVI_ERROR("Unknown OVI index. Index was [%d]", param);
				break;
			}

			regs  = _gOVIOutputModes_O20.pOVIOutputModes[param].regs;
			count = _gOVIOutputModes_O20.pOVIOutputModes[param].count;
			index = _gOVIOutputModes_O20.pOVIOutputModes[param].index;

			printk("\n[OVI] Register Index[%d] => %s",param, (char *)index);
			for(i=0; i<count; i++){
				if (regs[i].addr == OVI_HW_O20_REG_PARAM_OP_WAIT) continue;

				if (regs[i].addr == OVI_HW_O20_REG_PARAM_OP_CHECK)
				{
					_OVI_O20_IgnoreRegSet(regs[i].value, &ignore);
					continue;
				}

				if (ignore) continue;
				
				OVI_REG_RD(regs[i].addr, read_data);
				if(read_data == regs[i].value) same = 1;
				else same = 0;

				printk("\n[%03d] Current value of [0x%08x] => [0x%08x] / index value [0x%08x] (%s)", i, regs[i].addr, read_data, regs[i].value, same ? "SAME":"DIFFER");
			}
			printk("\n[OVI] Register read complete!\n");

			ret = RET_OK;
			break;
		}
		else if(param > _gOVIOutputModes_O20.number_of_modes) {
			OVI_ERROR("\nUnknown OVI mode. Index was [%d]\n", param);
			break;
		}

		/* Step 2. Set mode */
		regs  = _gOVIOutputModes_O20.pOVIOutputModes[param].regs;
		count = _gOVIOutputModes_O20.pOVIOutputModes[param].count;
		index = _gOVIOutputModes_O20.pOVIOutputModes[param].index;

		printk("\n[OVI] Setting to registers to register-set-index => %s", (char *)index);
		for(i=0; i<count; i++){
			if (regs[i].addr == OVI_HW_O20_REG_PARAM_OP_WAIT)
			{
				printk("\n[%03d] Delay... %dms", i, regs[i].value/1000);
				OS_UsecDelay(regs[i].value);
			}

			if (regs[i].addr == OVI_HW_O20_REG_PARAM_OP_CHECK)
			{
				_OVI_O20_IgnoreRegSet(regs[i].value, &ignore);
				continue;
			}

			if (ignore) continue;
			
			printk("\n[%03d] Writing... [0x%08x] <= [0x%08x]", i, regs[i].addr, regs[i].value);
			OVI_REG_WR(regs[i].addr, regs[i].value);
		}
		printk("\n[OVI] Setting preset complete!\n");

		ret = RET_OK;
	} while(0);

	return ret;
}

int OVI_HW_O20_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams)
{
	int ret = RET_OK;
	UINT32 regVal = 0;

	OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O20A0_T ss_ctrl0;
	OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O20A0_T ss_ctrl1;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (_gOviHwO20Info.spreadSpectrumRegValue1 & 0x4) break; // default DSS OFF

		if(pstParams->bEnable)
		{
			if (pstParams->eSpreadRatio == 0 || pstParams->u16Period == 0)
			{
				CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO20Info.spreadSpectrumRegValue1 | 0x4);
				CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll0);

				CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll1, _gOviHwO20Info.spreadSpectrumRegValue2);
				CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll2, 0x01400000);

				CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll1);
				CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll2);

				CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO20Info.spreadSpectrumRegValue1);
				CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll0);

				OVI_REG_RD(0xC930E400, regVal);
				OVI_PRINT("Enable DSS with initial value. register val: 0x%x\n", regVal);
			}
			else
			{
				UINT32 M, NPC, NSC;
				UINT32 ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF;

				UINT32 spread_ratio, disp_mod_freq;

				ss_ctrl0 = *gOVI_HW_O20_SS_CTRL1;
				ss_ctrl1 = *gOVI_HW_O20_SS_CTRL2;

				M = ss_ctrl0.reg_aiopll_m;
				NPC = ss_ctrl1.reg_aiopll_npc;
				NSC = ss_ctrl1.reg_aiopll_nsc;

				if(!M) M = 1;

				ACCURACY = ss_ctrl0.reg_aiopll_accuracy;
				UPDN_MAX = ss_ctrl0.reg_aiopll_updn_max;
				MOD_FREQ = ss_ctrl0.reg_aiopll_mod_freq_max;
				RESULT_RF = GET_RESULT_RF(ACCURACY);

				if (UPDN_MAX == 0 || RESULT_RF == 0 || (NPC == 0 && NSC == 0))
				{
					OVI_PRINT("error! wrong value\n");
					ret = RET_ERROR;
					break;
				}

				spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
				disp_mod_freq = MOD_FREQ_OUT(FIN_DISP, M, MOD_FREQ, UPDN_MAX);
				OVI_PRINT("current ==> M: %u, NPC: %u, NSC: %u\n",
				M, NPC, NSC);
				OVI_PRINT("disp accracy: %u, updn_max: %u, mod_freq_max: %u, result_rt: %u\n",
				ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
				OVI_PRINT("disp spread_ratio  : %u.%4u, mod_freq : %uHz\n",
				spread_ratio/10000, spread_ratio%10000, disp_mod_freq);

				OVI_REG_RD(0xC930E400, regVal);
				OVI_PRINT("register val: 0x%x\n", regVal);

				{ // calc SS
					UINT32 in_spread_ratio = pstParams->eSpreadRatio * 100;  // ?.?% * 1000
					UINT32 in_mod_freq = pstParams->u16Period * 100; // hz ( not khz)

					UINT32 div_result_val;
					UINT32 rating_factor;
					UINT32 result_rf;
					UINT32 calc_updn_max;
					UINT32 result_freq_max;

					div_result_val = (4 * NPC) + NSC;
					rating_factor = (in_spread_ratio * div_result_val) / 50;

					if(rating_factor <= 2000)
					{
						ACCURACY = 1;
						result_rf = 2;
					}
					else
					{
						ACCURACY = 0;
						result_rf = 4;
					}

					calc_updn_max = (((in_spread_ratio * 60) * div_result_val)
									/ ((result_rf * 50) * M));

					if (calc_updn_max > 60000)
					{
						OVI_PRINT("error! over max spread ratio\n");
						ret = RET_ERROR;
						break;
					}

					UPDN_MAX = (calc_updn_max + 500) / 1000;

					if(GETBIT_M(UPDN_MAX, 6) == 0x1)
					{
						OVI_PRINT("error! 6 bit, over max spread ratio\n");
						ret = RET_ERROR;
						break;
					}

					if((GETBIT_M(UPDN_MAX, 1) == 0x1)) {
						UPDN_MAX = UPDN_MAX + 0x4;
					}
					CLRBIT_M(UPDN_MAX, 0);
					CLRBIT_M(UPDN_MAX, 1);

					result_freq_max = ((((FIN_DISP * 1000000) / M) * 10)
									/ ((in_mod_freq) * ((4 * UPDN_MAX ) + 2))) - 10;

					MOD_FREQ = (result_freq_max + 5) / 10;

					RESULT_RF = GET_RESULT_RF(ACCURACY);

					if (UPDN_MAX == 0 || RESULT_RF == 0)
					{
						OVI_PRINT("error! wrong parameter\n");
						ret = RET_ERROR;
						break;
					}

					spread_ratio = SPREAD_RATIO_OUT(UPDN_MAX, NPC, NSC, RESULT_RF);
					disp_mod_freq = MOD_FREQ_OUT(FIN_DISP, M, MOD_FREQ, UPDN_MAX);
					OVI_PRINT("changed ==> M: %u, NPC: %u, NSC: %u\n",
					M, NPC, NSC);
					OVI_PRINT("disp accracy: %u, updn_max: %u, mod_freq_max: %u, result_rt: %u\n",
					ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF);
					OVI_PRINT("disp spread_ratio  : %u.%4u, mod_freq : %uHz\n",
					spread_ratio/10000, spread_ratio%10000, disp_mod_freq);
				}

				CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO20Info.spreadSpectrumRegValue1 | 0x4);
				CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll0);

				ss_ctrl0 = *gOVI_HW_O20_SS_CTRL1;
				ss_ctrl0.reg_aiopll_accuracy = ACCURACY;
				ss_ctrl0.reg_aiopll_updn_max = UPDN_MAX;
				ss_ctrl0.reg_aiopll_mod_freq_max = MOD_FREQ;
				*gOVI_HW_O20_SS_CTRL1 = ss_ctrl0;

				CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll1, _gOviHwO20Info.spreadSpectrumRegValue2);
				CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll2, 0x01400000);

				CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll1);
				CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll2);

				//CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO20Info.spreadSpectrumRegValue1);
				//CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll0);
				ss_ctrl0 = *gOVI_HW_O20_SS_CTRL1;
				ss_ctrl0.reg_aiopll_dss = 0;
				*gOVI_HW_O20_SS_CTRL1 = ss_ctrl0;

				OVI_REG_RD(0xC930E400, regVal);
				OVI_PRINT("register val: 0x%x\n", regVal);
			}
		}
		else
		{
			CTOP_CTRL_O20Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO20Info.spreadSpectrumRegValue1 | 0x4);
			CTOP_CTRL_O20Ax_WrFL(CTOP_FMS, disp_aiopll0);
		}
	} while(0);

	return ret;
}

int OVI_HW_O20_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr1 = NULL;
	UINT8 *u8odLutData = NULL;
	UINT32 odLutSizeNum;
	
	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{
			odLutSizeNum = pstParams->odLut.sizeNum;

			if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				// check input table size
				if((odLutSizeNum != OVI_HW_O20_INPUT_OD_SIZENUM && odLutSizeNum != (4*OVI_HW_O20_INPUT_OD_SIZENUM)) 
					|| pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_O20A0_BASE + offsetof(OVI_TCON_REG_O20A0_T, tcon_odc_start_2d), 
													sizeof(UINT32)*OVI_HW_O20_INPUT_OD_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				// check input table size
				if(odLutSizeNum != OVI_HW_O20_INPUT_LOD_SIZENUM || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_O20A0_BASE + offsetof(OVI_TCON_LODC_REG_O20A0_T, tcon_lodc_start), 
													sizeof(UINT32)*OVI_HW_O20_INPUT_LOD_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_ON)
			{
				OVI_TCON_O20_RdFL(tcon_control);
				OVI_TCON_O20_Wr01(tcon_control, odc_en, 0x1);
				OVI_TCON_O20_WrFL(tcon_control);

				OVI_TCON_O20_RdFL(tcon_sts);
				OVI_TCON_O20_Wr01(tcon_sts, pix2_lock, 0x1);
				OVI_TCON_O20_WrFL(tcon_sts);
				break;
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_OFF)
			{
				OVI_TCON_O20_RdFL(tcon_control);
				OVI_TCON_O20_Wr01(tcon_control, odc_en, 0x0);
				OVI_TCON_O20_WrFL(tcon_control);

				OVI_TCON_O20_RdFL(tcon_sts);
				OVI_TCON_O20_Wr01(tcon_sts, pix2_lock, 0x0);
				OVI_TCON_O20_WrFL(tcon_sts);
				break;
			}
			else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
			{
				// check input table size
				if(odLutSizeNum != OVI_HW_O20_INPUT_POD2_SIZENUM || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_O20A0_BASE + offsetof(OVI_TCON_CAD_REG_O20A0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_O20_INPUT_POD2_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}

			if (pstParams->eMode != LX_OVI_TCON_LINEOD_PCID)
			{
				u8odLutData = (UINT8 *)vmalloc(odLutSizeNum);
				if(u8odLutData == NULL)
				{
					OVI_ERROR("[OVI] memory allocate failed! \n");
					ret = RET_ERROR;
					break;
				}

				ret = copy_from_user(u8odLutData, (void __user *)pstParams->odLut.pData, odLutSizeNum);
				if(ret)
				{
					OVI_ERROR("[OVI] Error in copying from user! \n");
					ret = RET_ERROR;
					break;
				}
			}

			if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				//UINT32 regField; // block for bring-up
				//UINT32 regField2;
				UINT32 odLutDataOffsetInc = 0;

	#if 0 // block for bring-up
				OVI_WPR_O20_RdFL(wpr_reg_main);
				regField = OVI_WPR_O20_Rd(wpr_reg_main);
				regField = regField & 0x3; // check wpr_on,lgd_siw_mux
				OVI_TCON_O20_RdFL(tcon_control);
				OVI_TCON_O20_Rd01(tcon_control, hm_rgbw_en, regField2);
				regField = regField | regField2;
	#endif

				OVI_TCON_O20_RdFL(odc_lut_subpix_sel);
				OVI_TCON_O20_Wr01(odc_lut_subpix_sel, lut_rgbw_en, 0x0);
				OVI_TCON_O20_WrFL(odc_lut_subpix_sel);

				OVI_TCON_O20_RdFL(odc_lut_subpix_sel);
				OVI_TCON_O20_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x0);
				OVI_TCON_O20_WrFL(odc_lut_subpix_sel);

				if (odLutSizeNum == (4*OVI_HW_O20_INPUT_OD_SIZENUM))
				{
					odLutDataOffsetInc = OVI_HW_O20_INPUT_OD_SIZENUM;
				}

				for(i=0; i<OVI_HW_O20_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i], &regAddr1[i]);
				}

				OVI_TCON_O20_RdFL(odc_lut_subpix_sel);
				OVI_TCON_O20_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x1);
				OVI_TCON_O20_WrFL(odc_lut_subpix_sel);
				for(i=0; i<OVI_HW_O20_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i+(1*odLutDataOffsetInc)], &regAddr1[i]);
				}

				OVI_TCON_O20_RdFL(odc_lut_subpix_sel);
				OVI_TCON_O20_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x2);
				OVI_TCON_O20_WrFL(odc_lut_subpix_sel);
				for(i=0; i<OVI_HW_O20_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i+(2*odLutDataOffsetInc)], &regAddr1[i]);
				}
	#if 0 // block for bring-up
				if (regField != 0)
				{
					OVI_TCON_O20_RdFL(odc_lut_subpix_sel);
					OVI_TCON_O20_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x3);
					OVI_TCON_O20_WrFL(odc_lut_subpix_sel);
					for(i=0; i<OVI_HW_O20_INPUT_OD_SIZENUM; i++)
					{
						writel_relaxed(u8odLutData[i+(3*odLutDataOffsetInc)], &regAddr1[i]);
					}
				}
	#endif
			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
			{
				for(i=0; i<OVI_HW_O20_INPUT_POD2_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i], &regAddr1[i]);
				}
			}
			else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				for(i=0; i<OVI_HW_O20_INPUT_LOD_SIZENUM; i++)
				{
					get_user(regAddr1[i], &(((UINT32 *)pstParams->odLut.pData)[i]));
				}
			}

			if(pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				OVI_TCON_O20_RdFL(odc_lut_upload);
				OVI_TCON_O20_Wr01(odc_lut_upload, odc_upload, 0x0);
				OVI_TCON_O20_WrFL(odc_lut_upload);
				OVI_TCON_O20_RdFL(odc_lut_upload);
				OVI_TCON_O20_Wr01(odc_lut_upload, odc_upload, 0x1);
				OVI_TCON_O20_WrFL(odc_lut_upload);
			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				OVI_TCON_CAD_O20_RdFL(tcon_cad_reg_main);
				OVI_TCON_CAD_O20_Wr01(tcon_cad_reg_main, cad_on, 0x0);
				OVI_TCON_CAD_O20_WrFL(tcon_cad_reg_main);

				OVI_TCON_O20_RdFL(tcon_control);
				OVI_TCON_O20_Wr01(tcon_control, mem_sel, 0x1);
				OVI_TCON_O20_WrFL(tcon_control);

				OVI_TCON_O20_RdFL(tcon_odc_lut1_opt);
				OVI_TCON_O20_Wr01(tcon_odc_lut1_opt, lut1_add_opt, 0x0);
				OVI_TCON_O20_Wr01(tcon_odc_lut1_opt, lut1_full_opt, 0x0);
				OVI_TCON_O20_Wr01(tcon_odc_lut1_opt, lut1_zero_opt, 0x0);
				OVI_TCON_O20_Wr01(tcon_odc_lut1_opt, lut1_same_opt, 0x0);
				OVI_TCON_O20_WrFL(tcon_odc_lut1_opt);

				OVI_TCON_LODC_O20_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_O20_Wr01(lodc_lut_upload, lodc_upload, 0x0);
				OVI_TCON_LODC_O20_WrFL(lodc_lut_upload);
				OVI_TCON_LODC_O20_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_O20_Wr01(lodc_lut_upload, lodc_upload, 0x1);
				OVI_TCON_LODC_O20_WrFL(lodc_lut_upload);

				OVI_TCON_O20_RdFL(tcon_odc_opt1);
				OVI_TCON_O20_Wr01(tcon_odc_opt1, lodc_en_2d, 0x1);
				OVI_TCON_O20_Wr01(tcon_odc_opt1, lodc_en_3d, 0x0);
				OVI_TCON_O20_Wr01(tcon_odc_opt1, pcid_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_odc_opt1, pcid20_en, 0x1);
				OVI_TCON_O20_WrFL(tcon_odc_opt1);
			}
			else
			{
				UINT32 regField;

				//CTOP_CTRL_O20Ax_RdFL(DPE_SYN, crg_dpe00); // block for bring-up
				//CTOP_CTRL_O20Ax_Rd01(DPE_SYN, crg_dpe00, tcon_pod_clk_gate_en, regField); // block for bring-up
				OVI_REG_RD(0xC930F000,regField);
				regField = (regField & 0x200) >> 9;

				OVI_TCON_O20_RdFL(tcon_control);
				if (regField) // POD clock gating enable
				{
					// Prevention for black screen when using CEDS board
					OVI_TCON_O20_Wr01(tcon_control, mem_sel, 0x1);
				}
				else
				{
					OVI_TCON_O20_Wr01(tcon_control, mem_sel, 0x0);
				}
				OVI_TCON_O20_WrFL(tcon_control);

				OVI_TCON_CAD_O20_RdFL(tcon_cad_reg_main);
				OVI_TCON_CAD_O20_Wr01(tcon_cad_reg_main, cad_on, 0x1);
				OVI_TCON_CAD_O20_WrFL(tcon_cad_reg_main);
			}
		}
		else
		{
			if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				UINT8 buff;

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_O20A0_BASE + offsetof(OVI_TCON_REG_O20A0_T, tcon_odc_start_2d), 
													sizeof(UINT32)*OVI_HW_O20_INPUT_OD_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = OVI_HW_O20_INPUT_OD_SIZENUM;

				for (i = 0; i < OVI_HW_O20_INPUT_OD_SIZENUM; i++)
				{
					buff = readb_relaxed(&regAddr1[i]);
					put_user(buff, &(((UINT8 *)pstParams->odLut.pData)[i]));
				}

			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				UINT8 buff;
				volatile UINT8 *regAddr2 = NULL;

				// select address
				regAddr2 = (volatile UINT8 *)ioremap(OVI_TCON_LODC_REG_O20A0_BASE + offsetof(OVI_TCON_LODC_REG_O20A0_T, tcon_lodc_start), 
													sizeof(UINT32)*OVI_HW_O20_INPUT_LOD_SIZENUM);
				if(regAddr2 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = sizeof(UINT32)*OVI_HW_O20_INPUT_LOD_SIZENUM;

				for (i = 0; i < sizeof(UINT32)*OVI_HW_O20_INPUT_LOD_SIZENUM; i++)
				{
					buff = readb_relaxed(&regAddr2[i]);
					put_user(buff, &(((UINT8 *)pstParams->odLut.pData)[i]));
				}

				if(regAddr2 != NULL)
					iounmap((void *)regAddr2);

			}
			else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
			{
				UINT8 buff;

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_O20A0_BASE + offsetof(OVI_TCON_CAD_REG_O20A0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_O20_INPUT_POD2_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = OVI_HW_O20_INPUT_POD2_SIZENUM;

				for (i = 0; i < OVI_HW_O20_INPUT_POD2_SIZENUM; i++)
				{
					buff = readb_relaxed(&regAddr1[i]);
					put_user(buff, &(((UINT8 *)pstParams->odLut.pData)[i]));
				}
			}
		}
	} while(0);
	
	if(u8odLutData != NULL)
		vfree(u8odLutData);
	if(regAddr1 != NULL)
		iounmap((void *)regAddr1);
	
	return ret;
}


int OVI_HW_O20_SetFrameOdcEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	
	do {
		// check TCON base address
		if (bParam && !(_gOviHwO20Info.tconBaseAddress))
		{
			OVI_ERROR("[OVI] TCON base address is Null!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_TCON_O20_RdFL(tcon_control);
		if(bParam)
			OVI_TCON_O20_Wr01(tcon_control, odc_en, 0x1);
		else
			OVI_TCON_O20_Wr01(tcon_control, odc_en, 0x0);
		OVI_TCON_O20_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_O20_SetColorTempEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_O20_RdFL(led_wb2p_en);
		if(bParam)
			DPE_LED_O20_Wr01(led_wb2p_en, wb2p_en, 0x1);
		else
			DPE_LED_O20_Wr01(led_wb2p_en, wb2p_en, 0x0);
		DPE_LED_O20_WrFL(led_wb2p_en);
	} while (0);

	return ret;
}

int OVI_HW_O20_SetGammaEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_O20_RdFL(led_dpg_en);
		if(bParam)
			DPE_LED_O20_Wr01(led_dpg_en, dpg_en, 0x1);
		else
			DPE_LED_O20_Wr01(led_dpg_en, dpg_en, 0x0);
		DPE_LED_O20_WrFL(led_dpg_en);
	} while (0);

	return ret;
}

int OVI_HW_O20_SetDitherEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	
	do {
		OVI_TCON_O20_RdFL(tcon_control);
		if(bParam)
		{
			OVI_TCON_O20_Wr01(tcon_control, pre_dither_en, 0x1);
		}
		else
		{
			OVI_TCON_O20_Wr01(tcon_control, pre_dither_en, 0x0);
		}
		OVI_TCON_O20_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_O20_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		/* Do Nothing */
	} while(0);

	return ret;
}

int OVI_HW_O20_SetDitherMode(LX_OVI_TCON_DITHER_T enParam)
{
	int ret = RET_OK;
	
	do {
		//Dither Enable
		OVI_TCON_O20_RdFL(tcon_control);
		OVI_TCON_O20_Wr01(tcon_control, pre_dither_en, 0x1);
		OVI_TCON_O20_WrFL(tcon_control);
		
		OVI_TCON_O20_RdFL(tcon_dither_carry);
		switch(enParam)
		{
			case LX_OVI_TCON_DITHER_TRUNC:
				OVI_TCON_O20_Wr01(tcon_dither_carry, pre_dither_sel, 0x0);
				break;
			case LX_OVI_TCON_DITHER_ROUND:
				OVI_TCON_O20_Wr01(tcon_dither_carry, pre_dither_sel, 0x1);
				break;
			case LX_OVI_TCON_DITHER_RANDOM:
			default :
				OVI_TCON_O20_Wr01(tcon_dither_carry, pre_dither_sel, 0x2);
				break;
		}
		OVI_TCON_O20_WrFL(tcon_dither_carry);
	} while(0);

	return ret;
}

static UINT32 _OVI_O20_GetGain(UINT32 gain)
{
	UINT32 ret_gain;
	UINT32 temp;
	UINT32 rangeOpt;

	rangeOpt = (gain >> 31) & 0x1;
	gain &= (~(1 << 31));

	if ((rangeOpt == 0)
		|| ((rangeOpt == 1) && (gain >= 192)))
	{
		temp = 10000 + (gain - 192) * OVI_HW_O20_WB_GAIN_STEP1;
	}
	else
	{
		temp = 10000 + (gain - 192) * OVI_HW_O20_WB_GAIN_STEP2;
	}
	ret_gain = (temp * OVI_HW_O20_WB_DEFAULT_GAIN) / 10000;

	return ret_gain;
}

static SINT16 _OVI_O20_GetOffset(UINT32 offset)
{
	SINT16 ret_offset;

	ret_offset = ((SINT32)offset - 64) * OVI_HW_O20_WB_OFFSET_STEP;
	return ret_offset;
}

int OVI_HW_O20_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams)
{
	int ret = RET_OK;
	UINT32 r_gain, g_gain, b_gain;
	SINT16 rOffset, gOffset, bOffset;
	
	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
			if (_gOviHwO20Info.pVx1ChipInfoVMapAddr != NULL)		
			{
				UINT32 dataSize;
				int i;
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
				BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT0_T count;
#endif
				
				r_gain = _OVI_O20_GetGain(pstParams->r_gain);
				g_gain = _OVI_O20_GetGain(pstParams->g_gain);
				b_gain = _OVI_O20_GetGain(pstParams->b_gain);

				rOffset = _OVI_O20_GetOffset(pstParams->r_offset);
				gOffset = _OVI_O20_GetOffset(pstParams->g_offset);
				bOffset = _OVI_O20_GetOffset(pstParams->b_offset);

				_gColTemp = *pstParams;

				for (i=0; i<BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
				{
					dataSize = 0;
					
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbEnRegAddr = _B2L32(OVI_HW_F20_REG_WB_EN); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbEnVal = _B2L32(0x1); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbRGainRegAddr = _B2L32(OVI_HW_F20_REG_WB_R_GAIN); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbRGainVal = _B2L32(r_gain); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbROffsetRegAddr = _B2L32(OVI_HW_F20_REG_WB_R_OFFSET); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbROffsetVal = _B2L32(rOffset); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbGGainRegAddr = _B2L32(OVI_HW_F20_REG_WB_G_GAIN); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbGGainVal = _B2L32(g_gain); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbGOffsetRegAddr = _B2L32(OVI_HW_F20_REG_WB_G_OFFSET); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbGOffsetVal = _B2L32(gOffset); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbBGainRegAddr = _B2L32(OVI_HW_F20_REG_WB_B_GAIN); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbBGainVal = _B2L32(b_gain); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbBOffsetRegAddr = _B2L32(OVI_HW_F20_REG_WB_B_OFFSET); dataSize++;
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.wbBOffsetVal = _B2L32(bOffset); dataSize++;
					dataSize = sizeof(UINT32) * dataSize;

#ifndef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
#endif

					if (dataSize != OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_SIZE)
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();

#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
					count.u32Data = _B2L32(_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data);

					if (count.colorTemp == 0xF)
					{
						count.colorTemp = 1;
					}
					else
					{
						count.colorTemp++;
					}

					_gOviHwO20Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data = _B2L32(count.u32Data);
#else
					_gOviHwO20Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32((0x0A000000|OVI_HW_O20_VX1_CHIP_INFO_COLOR_TEMP_SIZE));
#endif

					wmb();
				}
				if (ret != RET_OK) break;
			}
			else
			{
#endif
				// W/B Enable
				DPE_LED_O20_RdFL(led_wb2p_en);
				DPE_LED_O20_Wr01(led_wb2p_en, wb2p_en, 0x1);
				DPE_LED_O20_WrFL(led_wb2p_en);
			
				r_gain = _OVI_O20_GetGain(pstParams->r_gain);
				g_gain = _OVI_O20_GetGain(pstParams->g_gain);
				b_gain = _OVI_O20_GetGain(pstParams->b_gain);

				rOffset = _OVI_O20_GetOffset(pstParams->r_offset);
				gOffset = _OVI_O20_GetOffset(pstParams->g_offset);
				bOffset = _OVI_O20_GetOffset(pstParams->b_offset);

				_gColTemp = *pstParams;

				if((_gPrevRedGain == r_gain) && (_gPrevGreenGain == g_gain) && (_gPrevBlueGain == b_gain)
					&& (_gPrevRedOffset == rOffset) && (_gPrevGreenOffset == gOffset) && (_gPrevBlueOffset == bOffset))
				{
					return RET_OK;
				}

				// Set red gain
				DPE_LED_O20_RdFL(led_wb2p_r_gain);
				DPE_LED_O20_Wr(led_wb2p_r_gain, r_gain);
				DPE_LED_O20_WrFL(led_wb2p_r_gain);

				// Set red offset
				DPE_LED_O20_RdFL(led_wb2p_r_offset);
				DPE_LED_O20_Wr(led_wb2p_r_offset, rOffset);
				DPE_LED_O20_WrFL(led_wb2p_r_offset);

				// Set green gain
				DPE_LED_O20_RdFL(led_wb2p_g_gain);
				DPE_LED_O20_Wr(led_wb2p_g_gain, g_gain);
				DPE_LED_O20_WrFL(led_wb2p_g_gain);

				// Set green offset
				DPE_LED_O20_RdFL(led_wb2p_g_offset);
				DPE_LED_O20_Wr(led_wb2p_g_offset, gOffset);
				DPE_LED_O20_WrFL(led_wb2p_g_offset);

				// Set blue gain
				DPE_LED_O20_RdFL(led_wb2p_b_gain);
				DPE_LED_O20_Wr(led_wb2p_b_gain, b_gain);
				DPE_LED_O20_WrFL(led_wb2p_b_gain);

				// Set blue offset
				DPE_LED_O20_RdFL(led_wb2p_b_offset);
				DPE_LED_O20_Wr(led_wb2p_b_offset, bOffset);
				DPE_LED_O20_WrFL(led_wb2p_b_offset);

				_gPrevRedGain = r_gain;
				_gPrevGreenGain = g_gain;
				_gPrevBlueGain = b_gain;
				_gPrevRedOffset = rOffset;
				_gPrevGreenOffset = gOffset;
				_gPrevBlueOffset = bOffset;
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
			}		
#endif
		}
		else
		{
			*pstParams = _gColTemp;
		}

	} while(0);

	return ret;
}

int OVI_HW_O20_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams)
{
	int ret = RET_OK;
	UINT32 *rGammaTable = NULL;
	UINT32 *gGammaTable = NULL;
	UINT32 *bGammaTable = NULL;
	UINT32 regField;
	int i;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		cancel_delayed_work_sync(&_gOviHwO20Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutR);
			_gOviHwO20Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutG);
			_gOviHwO20Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO20Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwO20Info.delayedRGBGamma.pu32LutB);
			_gOviHwO20Info.delayedRGBGamma.pu32LutB = NULL;
		}

		if (!pstParams->bIsGet)
		{
			if((pstParams->rGammaLut.sizeNum != OVI_HW_O20_GAMMA_TABLE_SIZENUM)
			|| (pstParams->gGammaLut.sizeNum != OVI_HW_O20_GAMMA_TABLE_SIZENUM)
			|| (pstParams->bGammaLut.sizeNum != OVI_HW_O20_GAMMA_TABLE_SIZENUM))
			{
				OVI_ERROR("[OVI] Gamma table size is not correct! \n");
				ret = RET_ERROR;
				break;
			}

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user(rGammaTable, (void __user *)pstParams->rGammaLut.pData, OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user(gGammaTable, (void __user *)pstParams->gGammaLut.pData, OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user(bGammaTable, (void __user *)pstParams->bGammaLut.pData, OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
			if (_gOviHwO20Info.pVx1ChipInfoVMapAddr != NULL)
			{
				UINT32 dataSize;
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
				BE_OVI_HW_O20_VX1_CHIP_INFO_APB_CNT0_T count;
#else
				UINT32 ctrlSize;
#endif
				int idx;

				for (idx=0; idx<BE_OVI_HW_O20_VX1_CHIP_INFO_MEM_BUFF_NUM; idx++)
				{
					dataSize = 0;
#ifndef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
					ctrlSize= 0;
#endif

					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.wDataRegAddr = _B2L32(OVI_HW_F20_REG_DPG_LUT_WDATA); dataSize++;
					/* Setting Red Gamma Table */
					for (i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.wdata[i] = _B2L32(((0x4<<28)|(i<<16)|(rGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O20_GAMMA_TABLE_SIZENUM;
					/* Setting Green Gamma Table */
					for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.wdata[i+OVI_HW_O20_GAMMA_TABLE_SIZENUM] = _B2L32(((0x2<<28)|(i<<16)|(gGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O20_GAMMA_TABLE_SIZENUM;
					/* Setting Blue Gamma Table */
					for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.wdata[i+(OVI_HW_O20_GAMMA_TABLE_SIZENUM*2)] = _B2L32(((0x1<<28)|(i<<16)|(bGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O20_GAMMA_TABLE_SIZENUM;
					dataSize = sizeof(UINT32) * dataSize;

#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO_APB_SLAVE
					if (dataSize != OVI_HW_O20_VX1_CHIP_INFO_DPG_DATA_SIZE)
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();
					
					count.u32Data = _B2L32(_gOviHwO20Info.pVx1ChipInfo[idx]->datHdr.cnt0.u32Data);
					
					if (count.dpg == 0xF)
					{
						count.dpg = 1;
					}
					else
					{
						count.dpg++;
					}

					_gOviHwO20Info.pVx1ChipInfo[idx]->datHdr.cnt0.u32Data = _B2L32(count.u32Data);
					wmb();
#else
					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.dataHwCrc = 0xFFFFFFFF;

					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.wrDoneRegAddr = _B2L32(OVI_HW_F20_REG_DPG_LUT_WR_DONE); ctrlSize++;
					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.wrDoneVal = _B2L32(0x1); ctrlSize++;
					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.enRegAddr = _B2L32(OVI_HW_F20_REG_DPG_EN); ctrlSize++;
					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.enVal = _B2L32(0x1); ctrlSize++;
					ctrlSize = sizeof(UINT32) * ctrlSize;
					
					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.ctrlHwCrc = 0xFFFFFFFF;

					if ((dataSize != OVI_HW_O20_VX1_CHIP_INFO_DPG_DATA_SIZE)
						|| (ctrlSize != OVI_HW_O20_VX1_CHIP_INFO_DPG_CTRL_SIZE))
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();
					
					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.dataHwHdr = _B2L32((0x0A010000|OVI_HW_O20_VX1_CHIP_INFO_DPG_DATA_SIZE));
					wmb();
					_gOviHwO20Info.pVx1ChipInfo[idx]->dpg.ctrlHwHdr = _B2L32((0x0A000000|OVI_HW_O20_VX1_CHIP_INFO_DPG_CTRL_SIZE));
					wmb();
#endif
				}
				if (ret != RET_OK) break;
			}
			else
			{
#endif
				DPE_LED_O20_RdFL(led_dpg_lut_wr_done);
				DPE_LED_O20_Rd01(led_dpg_lut_wr_done, dpg_lut_wr_status, regField);
				if (regField)
				{
					_gOviHwO20Info.delayedRGBGamma.pu32LutR = rGammaTable;
					_gOviHwO20Info.delayedRGBGamma.pu32LutG = gGammaTable;
					_gOviHwO20Info.delayedRGBGamma.pu32LutB = bGammaTable;
					
					schedule_delayed_work(&_gOviHwO20Info.delayedRGBGamma.dlyWork, msecs_to_jiffies(10));
				}
				else
				{
					DPE_LED_O20_RdFL(led_dpg_lut_wdata);

					/* Setting Red Gamma Table */
					for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_wdata, rGammaTable[i] & 0x7FFF);
						DPE_LED_O20_WrFL(led_dpg_lut_wdata);
					}
					/* Setting Green Gamma Table */
					for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_wdata, gGammaTable[i] & 0x7FFF);
						DPE_LED_O20_WrFL(led_dpg_lut_wdata);
					}
					/* Setting Blue Gamma Table */
					for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_O20_Wr01(led_dpg_lut_wdata, dpg_wdata, bGammaTable[i] & 0x7FFF);
						DPE_LED_O20_WrFL(led_dpg_lut_wdata);
					}

					DPE_LED_O20_RdFL(led_dpg_lut_wr_done);
					DPE_LED_O20_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
					DPE_LED_O20_WrFL(led_dpg_lut_wr_done);

					// Gamma Enable
					DPE_LED_O20_RdFL(led_dpg_en);
					DPE_LED_O20_Wr01(led_dpg_en, dpg_en, 0x1);
					DPE_LED_O20_WrFL(led_dpg_en);
				}
#ifdef BE_OVI_HW_O20_USE_VX1_CHIP_INFO
			}
#endif
		}
		else
		{

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			DPE_LED_O20_RdFL(led_dpg_lut_wr_done);
			DPE_LED_O20_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_O20_WrFL(led_dpg_lut_wr_done);

			OS_UsecDelay(25000);

			/* Setting Red Gamma Table */
			for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_O20_RdFL(led_dpg_lut_rdata);
				DPE_LED_O20_Wr01(led_dpg_lut_rdata, dpg_re, 0x4);
				DPE_LED_O20_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_O20_WrFL(led_dpg_lut_rdata);
				DPE_LED_O20_RdFL(led_dpg_lut_rdata);
				DPE_LED_O20_Rd01(led_dpg_lut_rdata, dpg_rdata, rGammaTable[i]);
			}
			/* Setting Green Gamma Table */
			for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_O20_RdFL(led_dpg_lut_rdata);
				DPE_LED_O20_Wr01(led_dpg_lut_rdata, dpg_re, 0x2);
				DPE_LED_O20_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_O20_WrFL(led_dpg_lut_rdata);
				DPE_LED_O20_RdFL(led_dpg_lut_rdata);
				DPE_LED_O20_Rd01(led_dpg_lut_rdata, dpg_rdata, gGammaTable[i]);
			}
			/* Setting Blue Gamma Table */
			for(i=0; i<OVI_HW_O20_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_O20_RdFL(led_dpg_lut_rdata);
				DPE_LED_O20_Wr01(led_dpg_lut_rdata, dpg_re, 0x1);
				DPE_LED_O20_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_O20_WrFL(led_dpg_lut_rdata);
				DPE_LED_O20_RdFL(led_dpg_lut_rdata);
				DPE_LED_O20_Rd01(led_dpg_lut_rdata, dpg_rdata, bGammaTable[i]);
			}

			DPE_LED_O20_RdFL(led_dpg_lut_wr_done);
			DPE_LED_O20_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_O20_WrFL(led_dpg_lut_wr_done);

			pstParams->rGammaLut.sizeNum = OVI_HW_O20_GAMMA_TABLE_SIZENUM;
			pstParams->gGammaLut.sizeNum = OVI_HW_O20_GAMMA_TABLE_SIZENUM;
			pstParams->bGammaLut.sizeNum = OVI_HW_O20_GAMMA_TABLE_SIZENUM;

			ret = copy_to_user(pstParams->rGammaLut.pData, (void __user *)rGammaTable, OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->gGammaLut.pData, (void __user *)gGammaTable, OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->bGammaLut.pData, (void __user *)bGammaTable, OVI_HW_O20_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

		}
	} while(0);

	if((rGammaTable != NULL) && (_gOviHwO20Info.delayedRGBGamma.pu32LutR == NULL))
		vfree(rGammaTable);
	if((gGammaTable != NULL) && (_gOviHwO20Info.delayedRGBGamma.pu32LutG == NULL))
		vfree(gGammaTable);
	if((bGammaTable != NULL) && (_gOviHwO20Info.delayedRGBGamma.pu32LutB == NULL))
		vfree(bGammaTable);

	return ret;
}

int OVI_HW_O20_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	UINT32 u32odcAddr=0;
	volatile UINT32 *pMappedAddr = NULL;

	do {
		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_FRAMEOD:
				u32odcAddr = OVI_TCON_REG_O20A0_BASE + offsetof(OVI_TCON_REG_O20A0_T, tcon_odc_start_2d);
				break;
			case LX_OVI_TCON_LINEOD_PCID:
				u32odcAddr = OVI_TCON_LODC_REG_O20A0_BASE + offsetof(OVI_TCON_LODC_REG_O20A0_T, tcon_lodc_start);
				break;
			default:
				break;
		}

		pstParams->odLut.sizeNum = OVI_HW_O20_INPUT_OD_SIZENUM;

		pMappedAddr = (volatile UINT32 *)ioremap(u32odcAddr, sizeof(UINT32)*OVI_HW_O20_INPUT_OD_SIZENUM);
		if(pMappedAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			break;
		}

		ret = copy_to_user((void __user *)pstParams->odLut.pData, (void*)pMappedAddr, sizeof(UINT32)*OVI_HW_O20_INPUT_OD_SIZENUM);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying to user! \n");
			ret = RET_ERROR;
			break;
		}
	}while(0);

	if(pMappedAddr != NULL)
		iounmap((void *)pMappedAddr);

	return ret;
}

int OVI_HW_O20_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams)
{
	int ret = RET_OK;
	UINT32 regField;

	do {

		if ((pstParams == NULL) || (_gOviHwO20Info.tscicWritingFlag == TRUE))
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer! or already running!\n");
			ret = RET_ERROR;
			break;
		}

		if (pstParams->u32TscicSize == 0) // TSCIC disable for debug
		{
			// [NOTE] FCIC function enable/disable : 0xC90750A8 [3:0] - 0x0/0xC
			// FCIC disable setting
			OVI_TCON_O20_RdFL(tcon_control);
			OVI_TCON_O20_Wr01(tcon_control, fcic_en, 0x0);
			OVI_TCON_O20_WrFL(tcon_control);

			// FCIC Clock gating ON
			//CTOP_CTRL_O20Ax_RdFL(DPE_SYN, crg_dpe00);
			//CTOP_CTRL_O20Ax_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 1);
			//CTOP_CTRL_O20Ax_WrFL(DPE_SYN, crg_dpe00);
			OVI_REG_RD(0xC930F000,regField);
			regField = (regField | 0x00000040);
			OVI_REG_WR(0xC930F000,regField);

			return RET_OK;
		}

		// check input table size
		if ((pstParams->u32Ctrlsize != OVI_HW_O20_INPUT_TSCIC_CTRL_SIZENUM) || (pstParams->pu8ControlTbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		if ((pstParams->u32TscicSize != OVI_HW_O20_INPUT_TSCIC_DATA_SIZE) || (pstParams->pu32TscicTbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		_gOviHwO20Info.tscicSize = pstParams->u32TscicSize;
		_gOviHwO20Info.tscicCtrlSizeNum = pstParams->u32Ctrlsize;

		_gOviHwO20Info.tscicU8CtrlData = (UINT8 *)vmalloc(_gOviHwO20Info.tscicCtrlSizeNum);
		if(_gOviHwO20Info.tscicU8CtrlData == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		ret = copy_from_user(_gOviHwO20Info.tscicU8CtrlData, (void __user *)pstParams->pu8ControlTbl, _gOviHwO20Info.tscicCtrlSizeNum);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			if(_gOviHwO20Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwO20Info.tscicU8CtrlData);
				_gOviHwO20Info.tscicU8CtrlData = NULL;
			}
			break;
		}

		_gOviHwO20Info.tscicU32Tbl = (UINT32 *)vmalloc(_gOviHwO20Info.tscicSize);
		if(_gOviHwO20Info.tscicU32Tbl == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			if(_gOviHwO20Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwO20Info.tscicU8CtrlData);
				_gOviHwO20Info.tscicU8CtrlData = NULL;
			}
			break;
		}

		ret = copy_from_user(_gOviHwO20Info.tscicU32Tbl, (void __user *)pstParams->pu32TscicTbl, _gOviHwO20Info.tscicSize);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			if(_gOviHwO20Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwO20Info.tscicU8CtrlData);
				_gOviHwO20Info.tscicU8CtrlData = NULL;
			}
			if(_gOviHwO20Info.tscicU32Tbl != NULL)
			{
				vfree(_gOviHwO20Info.tscicU32Tbl);
				_gOviHwO20Info.tscicU32Tbl = NULL;
			}
			break;
		}

		// FCIC Clock gating OFF
		//CTOP_CTRL_O20Ax_RdFL(DPE_SYN, crg_dpe00);
		//CTOP_CTRL_O20Ax_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 0);
		//CTOP_CTRL_O20Ax_WrFL(DPE_SYN, crg_dpe00);
		OVI_REG_RD(0xC930F000,regField);
		regField = (regField & 0xFFFFFFBF);
		OVI_REG_WR(0xC930F000,regField);

		// FCIC enable setting
		OVI_TCON_O20_RdFL(tcon_control);
		OVI_TCON_O20_Wr01(tcon_control, fcic_en, 0x1);
		OVI_TCON_O20_WrFL(tcon_control);

		_gOviHwO20Info.tscicThread = kthread_run(OVI_O20_TscicWriteThread, NULL, "ovi_tscic");
		if (IS_ERR(_gOviHwO20Info.tscicThread))
		{
			OVI_ERROR("[OVI] Error in starting thread! \n");
			ret = RET_ERROR;
			if(_gOviHwO20Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwO20Info.tscicU8CtrlData);
				_gOviHwO20Info.tscicU8CtrlData = NULL;
			}
			if(_gOviHwO20Info.tscicU32Tbl != NULL)
			{
				vfree(_gOviHwO20Info.tscicU32Tbl);
				_gOviHwO20Info.tscicU32Tbl = NULL;
			}
			break;
		}
	} while(0);

	return ret;
}

int OVI_HW_O20_SetTconHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	UINT32 regField;

	do {
		OVI_TCON_O20_RdFL(tcon_control);
		OVI_TCON_O20_Rd01(tcon_control, epi_out, regField);
		if (!regField) break;
		
		OVI_TCON_O20_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_O20_Wr01(tcon_hor_mode, hor_reverse, _gOviHwO20Info.horReverseRegFieldValue ? 0 : 1);
		}
		else {
			OVI_TCON_O20_Wr01(tcon_hor_mode, hor_reverse, _gOviHwO20Info.horReverseRegFieldValue);
		}
		OVI_TCON_O20_WrFL(tcon_hor_mode);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetLvdsHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	UINT32 regField;

	do {
		if( RET_OK == OS_ScanKernelCmdlineToken("ATELIER") )
		{
			OVI_TCON_O20_RdFL(tcon_ddiv_mode);
			if(bParam) {
				OVI_TCON_O20_Wr01(tcon_ddiv_mode, rd_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_ddiv_mode, line_delay, 0x1);
			}
			else {
				OVI_TCON_O20_Wr01(tcon_ddiv_mode, rd_mode, 0x1);
				OVI_TCON_O20_Wr01(tcon_ddiv_mode, line_delay, 0x0);
			}
			OVI_TCON_O20_WrFL(tcon_ddiv_mode);
		}
		else
		{
			OVI_TCON_O20_RdFL(tcon_control);
			OVI_TCON_O20_Rd01(tcon_control, epi_out, regField);
			if (regField) break;

			OVI_TCON_O20_RdFL(tcon_hor_mode);
			if(bParam) {
				OVI_TCON_O20_Wr01(tcon_hor_mode, hor_reverse, 0x1);
			}
			else {
				OVI_TCON_O20_Wr01(tcon_hor_mode, hor_reverse, 0x0);
			}
			OVI_TCON_O20_WrFL(tcon_hor_mode);
		}
	} while(0);

	return ret;
}

int OVI_HW_O20_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams)
{
	int ret = RET_OK;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_TCON_O20_RdFL(tcon_pgen_ctl);

		// pattern source color setting
		OVI_TCON_O20_RdFL(tcon_pgen_agpr1);
		OVI_TCON_O20_Wr(tcon_pgen_agpr1, 0x03FF);
		OVI_TCON_O20_WrFL(tcon_pgen_agpr1);

		OVI_TCON_O20_RdFL(tcon_pgen_agpg1);
		OVI_TCON_O20_Wr(tcon_pgen_agpg1, 0x03FF);
		OVI_TCON_O20_WrFL(tcon_pgen_agpg1);

		OVI_TCON_O20_RdFL(tcon_pgen_agpb1);
		OVI_TCON_O20_Wr(tcon_pgen_agpb1, 0x03FF);
		OVI_TCON_O20_WrFL(tcon_pgen_agpb1);

		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_TPG_OFF:		// pattern off
				OVI_TCON_O20_Wr(tcon_pgen_ctl, 0x0);
				_gOviHwO20Info.mute = 0;
				break;
			case LX_OVI_TCON_TPG_BLACK:		// black pattern
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x4);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				_gOviHwO20Info.mute = 1;
				break;
			case LX_OVI_TCON_TPG_WHITE:		// white pattern
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HVBAR:		// HVBar pattern
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x3);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR16GREY:		// Horizontal 16 grey pattern
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x8);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR64GREY:		// Horizontal 64 grey pattern
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x7);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR256GREY:		// Horizontal 256 grey pattern
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x6);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR1024GREY:		// Horizontal 1024 grey pattern
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x5);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_VER16GREY:		// Vertical 16 grey pattern
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0xC);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default :
				break;
		}
		OVI_TCON_O20_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetChannelPower(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		_OVI_O20_DispOutputEnable(bParam);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O20_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_LVDS_OUT_JEIDA:
				OVI_OIF_O20_Wr01(oif_lvds_config0, lvds_lsb_first, 0x0);
				break;
			case LX_OVI_LVDS_OUT_VESA:
				OVI_OIF_O20_Wr01(oif_lvds_config0, lvds_lsb_first, 0x1);
				break;
			default:
				break;
		}
		OVI_OIF_O20_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O20_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_8BIT:
				OVI_OIF_O20_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x1);
				break;
			case LX_OVI_10BIT:
				OVI_OIF_O20_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x0);
				break;
			default:
				break;
		}
		OVI_OIF_O20_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetLvdsBlack(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O20_RdFL(oif_lvds_config1);
		OVI_OIF_O20_RdFL(oif_lvds_config2);
		OVI_OIF_O20_RdFL(oif_vx1_config3);
		OVI_OIF_O20_RdFL(oif_vx1_config4);

		if(!bParam) // original data out
		{
			OVI_OIF_O20_Wr01(oif_lvds_config1, lvds_force_even_data, 0x0);
			OVI_OIF_O20_Wr01(oif_lvds_config2, lvds_force_odd_data, 0x0);

			OVI_OIF_O20_Wr01(oif_vx1_config3, vx1_force_even_data, 0x0);
			OVI_OIF_O20_Wr01(oif_vx1_config4, vx1_force_odd_data, 0x0);
		}
		else // black data out
		{
			OVI_OIF_O20_Wr01(oif_lvds_config1, lvds_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_O20_Wr01(oif_lvds_config2, lvds_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);

			OVI_OIF_O20_Wr01(oif_vx1_config3, vx1_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_O20_Wr01(oif_vx1_config4, vx1_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);
		}
		OVI_OIF_O20_WrFL(oif_lvds_config1);
		OVI_OIF_O20_WrFL(oif_lvds_config2);
		OVI_OIF_O20_WrFL(oif_vx1_config3);
		OVI_OIF_O20_WrFL(oif_vx1_config4);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetClock(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O20_RdFL(tcon_gclk_control);
		OVI_TCON_O20_RdFL(tcon_mclk_control);

		if(bParam)
		{
			OVI_TCON_O20_Wr01(tcon_gclk_control, gclk_en, 0x1);
			OVI_TCON_O20_Wr01(tcon_mclk_control, mclk_en, 0x1);
		}
		else
		{
			OVI_TCON_O20_Wr01(tcon_gclk_control, gclk_en, 0x0);
			OVI_TCON_O20_Wr01(tcon_mclk_control, mclk_en, 0x0);
		}

		OVI_TCON_O20_WrFL(tcon_gclk_control);
		OVI_TCON_O20_WrFL(tcon_mclk_control);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetEpiDataScramble(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O20_RdFL(tcon_epi_mode);

		if(bParam)
		{
			OVI_TCON_O20_Wr01(tcon_epi_mode, scr_en, 0x1);
		}
		else
		{
			OVI_TCON_O20_Wr01(tcon_epi_mode, scr_en, 0x0);
		}

		OVI_TCON_O20_WrFL(tcon_epi_mode);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetAdvanced10bit(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O20_RdFL(a10_ctrl);
		OVI_TCON_O20_RdFL(tcon_odc_opt2);

		if(bParam)
		{
			OVI_TCON_O20_Wr01(a10_ctrl, a10_on, 0x1);
			OVI_TCON_O20_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x1);
		}
		else
		{
			OVI_TCON_O20_Wr01(a10_ctrl, a10_on, 0x0);
			OVI_TCON_O20_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x0);
		}

		OVI_TCON_O20_WrFL(a10_ctrl);
		OVI_TCON_O20_WrFL(tcon_odc_opt2);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam)
{
	int ret = RET_OK;
	UINT16 *u16vcomPatData = NULL;
	int i,k,idx;

	do {
		UINT32 patData[4] = {0,0,0,0};
		UINT32 level = 0;

		if (pstParam == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer! \n");
			ret = RET_ERROR;
			break;
		}

		if (OVI_HW_O20_INPUT_VCOM_PAT_DATA_SIZE != pstParam->sizeNum)
		{
			OVI_ERROR("[OVI] Pattern Data size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		u16vcomPatData = (UINT16 *)vmalloc(sizeof(UINT16)*(pstParam->sizeNum));

		if (u16vcomPatData == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		ret = copy_from_user(u16vcomPatData, (void __user *)pstParam->pu16vcomPattern, sizeof(UINT16)*(pstParam->sizeNum));

		if (ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		for(i=0,idx=0; i<4; i++)
		{
			for(k=0; k<24; k++)
			{
				if (u16vcomPatData[idx] > 0)
				{
					patData[i] = patData[i] + (0x1 << k);

					if ((level == 0) && (u16vcomPatData[idx] > 1)) // u16vcomPatData[idx] = 1: on, 0: off, value > 1: on with pixel level
					{
						level = u16vcomPatData[idx];
					}
				}
				idx++;
			}
		}

		OVI_TCON_O20_RdFL(tcon_pgen_vcomp0);
		OVI_TCON_O20_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, patData[0]);
		OVI_TCON_O20_WrFL(tcon_pgen_vcomp0);

		OVI_TCON_O20_RdFL(tcon_pgen_vcomp1);
		OVI_TCON_O20_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, patData[1]);
		OVI_TCON_O20_WrFL(tcon_pgen_vcomp1);

		OVI_TCON_O20_RdFL(tcon_pgen_vcomp2);
		OVI_TCON_O20_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, patData[2]);
		OVI_TCON_O20_WrFL(tcon_pgen_vcomp2);

		OVI_TCON_O20_RdFL(tcon_pgen_vcomp3);
		OVI_TCON_O20_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, patData[3]);
		OVI_TCON_O20_WrFL(tcon_pgen_vcomp3);

		if (level > 0)
		{
			OVI_TCON_O20_RdFL(tcon_pgen_agpr1);
			OVI_TCON_O20_Wr01(tcon_pgen_agpr1, pgen_color_r1, level);
			OVI_TCON_O20_WrFL(tcon_pgen_agpr1);

			OVI_TCON_O20_RdFL(tcon_pgen_agpg1);
			OVI_TCON_O20_Wr01(tcon_pgen_agpg1, pgen_color_g1, level);
			OVI_TCON_O20_WrFL(tcon_pgen_agpg1);

			OVI_TCON_O20_RdFL(tcon_pgen_agpb1);
			OVI_TCON_O20_Wr01(tcon_pgen_agpb1, pgen_color_b1, level);
			OVI_TCON_O20_WrFL(tcon_pgen_agpb1);
		}
	} while(0);

	if(u16vcomPatData != NULL)
		vfree(u16vcomPatData);

	return ret;
}

int OVI_HW_O20_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O20_RdFL(tcon_pgen_ctl);

		switch(enParam)
		{
			case LX_OVI_TCON_VCOM_PAT_CTRL_OFF:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x0);

				OVI_TCON_O20_RdFL(tcon_pgen_vcomp0);
				OVI_TCON_O20_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, 0x0);
				OVI_TCON_O20_WrFL(tcon_pgen_vcomp0);

				OVI_TCON_O20_RdFL(tcon_pgen_vcomp1);
				OVI_TCON_O20_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, 0x0);
				OVI_TCON_O20_WrFL(tcon_pgen_vcomp1);

				OVI_TCON_O20_RdFL(tcon_pgen_vcomp2);
				OVI_TCON_O20_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, 0x0);
				OVI_TCON_O20_WrFL(tcon_pgen_vcomp2);

				OVI_TCON_O20_RdFL(tcon_pgen_vcomp3);
				OVI_TCON_O20_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, 0x0);
				OVI_TCON_O20_WrFL(tcon_pgen_vcomp3);

				OVI_TCON_O20_RdFL(tcon_pgen_agpr1);
				OVI_TCON_O20_Wr01(tcon_pgen_agpr1, pgen_color_r1, 0x3FF);
				OVI_TCON_O20_WrFL(tcon_pgen_agpr1);

				OVI_TCON_O20_RdFL(tcon_pgen_agpg1);
				OVI_TCON_O20_Wr01(tcon_pgen_agpg1, pgen_color_g1, 0x3FF);
				OVI_TCON_O20_WrFL(tcon_pgen_agpg1);

				OVI_TCON_O20_RdFL(tcon_pgen_agpb1);
				OVI_TCON_O20_Wr01(tcon_pgen_agpb1, pgen_color_b1, 0x3FF);
				OVI_TCON_O20_WrFL(tcon_pgen_agpb1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_ON:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x1E);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM1:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x16);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM2:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x17);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM3:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x18);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM4:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x19);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM5:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x1A);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM6:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x1B);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM7:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x1C);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM8:
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_mode, 0x1D);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O20_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default:
				break;
		}

		OVI_TCON_O20_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_O20_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam)
{
	int ret = RET_OK;

	do {
		if ((_gOviHwO20Info.hwDispOption.frcChipType == LX_OVI_FRC_CHIP_INTERNAL)
			&& (_gOviHwO20Info.hwDispOption.panelResolution == LX_OVI_PANEL_RESOLUTION_3840X2160)
			&& (_gOviHwO20Info.hwDispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_120HZ))
		{
			switch(enParam)
			{
				case LX_OVI_DISP_OUTPUT_MODE_4K60:
					OVI_TCON_O20_RdFL(tcon_ddiv_mode);
					OVI_OIF_O20_RdFL(oif_vx1_lane_sel3);
					OVI_OIF_O20_RdFL(oif_vx1_lane_sel4);
					OVI_TCON_O20_Wr01(tcon_ddiv_mode, lane_num, 0x8);
					OVI_OIF_O20_Wr(oif_vx1_lane_sel3, 0x00010203);
					OVI_OIF_O20_Wr(oif_vx1_lane_sel4, 0x04050607);
					OVI_TCON_O20_WrFL(tcon_ddiv_mode);
					OVI_OIF_O20_WrFL(oif_vx1_lane_sel3);
					OVI_OIF_O20_WrFL(oif_vx1_lane_sel4);

					// O20 DPE clock
					OVI_REG_WR(0xC930F008, 0x00000AA2);
					// O20 CCO clock
					OVI_REG_WR(0xC930C008, 0x00000049);
					// O20 GSC clock
					OVI_REG_WR(0xC930D018, 0x00000001);
					// O20 LED clock
					OVI_REG_WR(0xC930F020, 0x00000001);
					break;
					
				case LX_OVI_DISP_OUTPUT_MODE_4K120:
				default:
					OVI_TCON_O20_RdFL(tcon_ddiv_mode);
					OVI_OIF_O20_RdFL(oif_vx1_lane_sel3);
					OVI_OIF_O20_RdFL(oif_vx1_lane_sel4);
					OVI_TCON_O20_Wr01(tcon_ddiv_mode, lane_num, 0x10);
					OVI_OIF_O20_Wr(oif_vx1_lane_sel3, 0x08090A0B);
					OVI_OIF_O20_Wr(oif_vx1_lane_sel4, 0x0C0D0E0F);
					OVI_TCON_O20_WrFL(tcon_ddiv_mode);
					OVI_OIF_O20_WrFL(oif_vx1_lane_sel3);
					OVI_OIF_O20_WrFL(oif_vx1_lane_sel4);

					// O20 DPE clock
					OVI_REG_WR(0xC930F008, 0x00000220);
					// O20 CCO clock
					OVI_REG_WR(0xC930C008, 0x00000000);
					// O20 GSC clock
					OVI_REG_WR(0xC930D018, 0x00000000);
					// O20 LED clock
					OVI_REG_WR(0xC930F020, 0x00000000);
					break;
			}

			_gOviHwO20Info.dispOutputMode = enParam;
		}
	} while(0);

	return ret;
}

int OVI_HW_O20_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;
	
	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		if (memcmp(&_gOviHwO20Info.dispOption, pstParams, sizeof(LX_OVI_DISPLAY_INFO_T)) != 0)
		{
			OVI_PRINT("\n[OVI_HW_O20_DisplayResume] WARN:Disp Option Changed! [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
				pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
				pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
				pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
				pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);
		}
	} while(0);

	return ret;
}

int OVI_HW_O20_SetPempItune(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	UINT32 pemp_r0 = 0, pemp_r1 = 0, pemp_r2 = 0;
	UINT32 itune_r0 = 0, itune_r1 = 0, itune_r2 = 0;
	UINT8 u8pempData[24];
	UINT8 u8ituneData[24];

	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (!pstParams->bIsGet)
		{
			ret = copy_from_user(u8pempData, (void __user *)pstParams->pPemp, 24*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user(u8ituneData, (void __user *)pstParams->pItune, 24*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			pemp_r0 |= (0x7 & u8pempData[0]) << 0;
			pemp_r0 |= (0x7 & u8pempData[1]) << 3;
			pemp_r0 |= (0x7 & u8pempData[2]) << 6;
			pemp_r0 |= (0x7 & u8pempData[3]) << 9;
			pemp_r0 |= (0x7 & u8pempData[4]) << 12;
			pemp_r0 |= (0x7 & u8pempData[5]) << 15;
			pemp_r0 |= (0x7 & u8pempData[6]) << 18;
			pemp_r0 |= (0x7 & u8pempData[7]) << 21;
			pemp_r0 |= (0x7 & u8pempData[8]) << 24;
			pemp_r0 |= (0x7 & u8pempData[9]) << 27;
			pemp_r1 |= (0x7 & u8pempData[10]) << 0;
			pemp_r1 |= (0x7 & u8pempData[11]) << 3;
			pemp_r1 |= (0x7 & u8pempData[12]) << 6;
			pemp_r1 |= (0x7 & u8pempData[13]) << 9;
			pemp_r1 |= (0x7 & u8pempData[14]) << 12;
			pemp_r1 |= (0x7 & u8pempData[15]) << 15;
			pemp_r1 |= (0x7 & u8pempData[16]) << 18;
			pemp_r1 |= (0x7 & u8pempData[17]) << 21;
			pemp_r1 |= (0x7 & u8pempData[18]) << 24;
			pemp_r1 |= (0x7 & u8pempData[19]) << 27;
			pemp_r2 |= (0x7 & u8pempData[20]) << 0;
			pemp_r2 |= (0x7 & u8pempData[21]) << 3;
			pemp_r2 |= (0x7 & u8pempData[22]) << 6;
			pemp_r2 |= (0x7 & u8pempData[23]) << 9;

			itune_r0 |= (0x7 & u8ituneData[0]) << 0;
			itune_r0 |= (0x7 & u8ituneData[1]) << 3;
			itune_r0 |= (0x7 & u8ituneData[2]) << 6;
			itune_r0 |= (0x7 & u8ituneData[3]) << 9;
			itune_r0 |= (0x7 & u8ituneData[4]) << 12;
			itune_r0 |= (0x7 & u8ituneData[5]) << 15;
			itune_r0 |= (0x7 & u8ituneData[6]) << 18;
			itune_r0 |= (0x7 & u8ituneData[7]) << 21;
			itune_r0 |= (0x7 & u8ituneData[8]) << 24;
			itune_r0 |= (0x7 & u8ituneData[9]) << 27;
			itune_r1 |= (0x7 & u8ituneData[10]) << 0;
			itune_r1 |= (0x7 & u8ituneData[11]) << 3;
			itune_r1 |= (0x7 & u8ituneData[12]) << 6;
			itune_r1 |= (0x7 & u8ituneData[13]) << 9;
			itune_r1 |= (0x7 & u8ituneData[14]) << 12;
			itune_r1 |= (0x7 & u8ituneData[15]) << 15;
			itune_r1 |= (0x7 & u8ituneData[16]) << 18;
			itune_r1 |= (0x7 & u8ituneData[17]) << 21;
			itune_r1 |= (0x7 & u8ituneData[18]) << 24;
			itune_r1 |= (0x7 & u8ituneData[19]) << 27;
			itune_r2 |= (0x7 & u8ituneData[20]) << 0;
			itune_r2 |= (0x7 & u8ituneData[21]) << 3;
			itune_r2 |= (0x7 & u8ituneData[22]) << 6;
			itune_r2 |= (0x7 & u8ituneData[23]) << 9;

			OVI_REG_WR(0xC930F81C, pemp_r0);
			OVI_REG_WR(0xC930F820, pemp_r1);
			OVI_REG_WR(0xC930F824, pemp_r2);

			OVI_REG_WR(0xC930F80C, itune_r0);
			OVI_REG_WR(0xC930F810, itune_r1);
			OVI_REG_WR(0xC930F814, itune_r2);

		}
		else
		{
			OVI_REG_RD(0xC930F81C, pemp_r0);
			OVI_REG_RD(0xC930F820, pemp_r1);
			OVI_REG_RD(0xC930F824, pemp_r2);

			OVI_REG_RD(0xC930F80C, itune_r0);
			OVI_REG_RD(0xC930F810, itune_r1);
			OVI_REG_RD(0xC930F814, itune_r2);

			OVI_PRINT("[OVI] PEMP 0x%x, 0x%x, 0x%x\n",pemp_r0,pemp_r1,pemp_r2);
			OVI_PRINT("[OVI] ITUNE 0x%x, 0x%x, 0x%x\n",itune_r0,itune_r1,itune_r2);

			u8pempData[0] = (pemp_r0 >> 0) & 0x7;
		 	u8pempData[1] = (pemp_r0 >> 3) & 0x7;
			u8pempData[2] = (pemp_r0 >> 6) & 0x7;
			u8pempData[3] = (pemp_r0 >> 9) & 0x7;
			u8pempData[4] = (pemp_r0 >> 12) & 0x7;
			u8pempData[5] = (pemp_r0 >> 15) & 0x7;
			u8pempData[6] = (pemp_r0 >> 18) & 0x7;
			u8pempData[7] = (pemp_r0 >> 21) & 0x7;
			u8pempData[8] = (pemp_r0 >> 24) & 0x7;
			u8pempData[9] = (pemp_r0 >> 27) & 0x7;
			u8pempData[10] = (pemp_r1 >> 0) & 0x7;
		 	u8pempData[11] = (pemp_r1 >> 3) & 0x7;
			u8pempData[12] = (pemp_r1 >> 6) & 0x7;
			u8pempData[13] = (pemp_r1 >> 9) & 0x7;
			u8pempData[14] = (pemp_r1 >> 12) & 0x7;
			u8pempData[15] = (pemp_r1 >> 15) & 0x7;
			u8pempData[16] = (pemp_r1 >> 18) & 0x7;
			u8pempData[17] = (pemp_r1 >> 21) & 0x7;
			u8pempData[18] = (pemp_r1 >> 24) & 0x7;
			u8pempData[19] = (pemp_r1 >> 27) & 0x7;
			u8pempData[20] = (pemp_r2 >> 0) & 0x7;
			u8pempData[21] = (pemp_r2 >> 3) & 0x7;
			u8pempData[22] = (pemp_r2 >> 6) & 0x7;
			u8pempData[23] = (pemp_r2 >> 9) & 0x7;

			u8ituneData[0] = (itune_r0 >> 0) & 0x7;
		 	u8ituneData[1] = (itune_r0 >> 3) & 0x7;
			u8ituneData[2] = (itune_r0 >> 6) & 0x7;
			u8ituneData[3] = (itune_r0 >> 9) & 0x7;
			u8ituneData[4] = (itune_r0 >> 12) & 0x7;
			u8ituneData[5] = (itune_r0 >> 15) & 0x7;
			u8ituneData[6] = (itune_r0 >> 18) & 0x7;
			u8ituneData[7] = (itune_r0 >> 21) & 0x7;
			u8ituneData[8] = (itune_r0 >> 24) & 0x7;
			u8ituneData[9] = (itune_r0 >> 27) & 0x7;
			u8ituneData[10] = (itune_r1 >> 0) & 0x7;
		 	u8ituneData[11] = (itune_r1 >> 3) & 0x7;
			u8ituneData[12] = (itune_r1 >> 6) & 0x7;
			u8ituneData[13] = (itune_r1 >> 9) & 0x7;
			u8ituneData[14] = (itune_r1 >> 12) & 0x7;
			u8ituneData[15] = (itune_r1 >> 15) & 0x7;
			u8ituneData[16] = (itune_r1 >> 18) & 0x7;
			u8ituneData[17] = (itune_r1 >> 21) & 0x7;
			u8ituneData[18] = (itune_r1 >> 24) & 0x7;
			u8ituneData[19] = (itune_r1 >> 27) & 0x7;
			u8ituneData[20] = (itune_r2 >> 0) & 0x7;
			u8ituneData[21] = (itune_r2 >> 3) & 0x7;
			u8ituneData[22] = (itune_r2 >> 6) & 0x7;
			u8ituneData[23] = (itune_r2 >> 9) & 0x7;

			ret = copy_to_user((void __user *)pstParams->pPemp, (void*)u8pempData, 24*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_to_user((void __user *)pstParams->pItune, (void*)u8ituneData, 24*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}
		}

	} while(0);

	return ret;
}

int OVI_HW_O20_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		*pstParams = _gOviHwO20Info.hwDispOption;
	}while(0);

	return ret;
}

int OVI_HW_O20_SetPmMode(UINT32 u32Param)
{
	int ret = RET_OK;
	OVI_PRINT(" %d (0:S_PREPARE,1:SUSPEND,2:S_COMPLETED,3:R_PREPARE,4:RESUME,5:R_COMPLETED)\n",u32Param);

#define OVI_HW_O20_PQE_PM_DEVICE_SUSPEND_PREPARE		0
//fw stall
#define OVI_HW_O20_PQE_PM_DEVICE_SUSPEND				1
//cg on
#define OVI_HW_O20_PQE_PM_DEVICE_SUSPEND_COMPLETED	2
#define OVI_HW_O20_PQE_PM_DEVICE_RESUME_PREPARE		3
//cg off
#define OVI_HW_O20_PQE_PM_DEVICE_RESUME				4
//fw restart
#define OVI_HW_O20_PQE_PM_DEVICE_RESUME_COMPLETED	5

	switch (u32Param)
	{
		case OVI_HW_O20_PQE_PM_DEVICE_SUSPEND_PREPARE:
			break;
		case OVI_HW_O20_PQE_PM_DEVICE_SUSPEND:
			/* AVTASK-571, clear picinit */
		#if 0	//moved to f/w
			//BE_REG_WR(0xC9014000,0x0);//IMX_CTRL - PIC_INIT
			//BE_REG_WR(0xC9014100,0x0);//IMX_CTRL1 - PIC_INIT
			//BE_REG_WR(0xC9003000,0x0);//HDR_CTRL - PIC_INIT
			BE_REG_WR(0xC9037000,0x0);//FMC_CTRL - PIC_INIT
			BE_REG_WR(0xC9007000,0x0);//GSC_CTRL - PIC_INIT
			BE_REG_WR(0xC900B000,0x0);//VSD_CTRL - PIC_INIT
			//BE_REG_WR(0xC9010000,0x0);//CCO_CTRL - PIC_INIT. see chip/o20/fbdev/fbdev_o20_hw_cmn.c
			BE_REG_WR(0xC9023D00,0x0);//LED_CTRL - PIC_INIT
		#endif
			//BE_NOTI("clear picinit\n");
			/********************************/
			break;
		case OVI_HW_O20_PQE_PM_DEVICE_SUSPEND_COMPLETED:
		#if 0	//see _pqe_pm_o20_hw_handler
			/* AVTASK-570, sync gen disable */
			BE_REG_WR(0xC930D028,0x10);//CTOP_SYN - gsc - BND_CTRL01 - [4]reg_sync_gen_disable
			BE_NOTI("reg_sync_gen_disable\n");
			/********************************/
			/* AVTASK-570, cg on de,disp */
			/* CTOP_SYN - cco - CRG_CCO00 - [8]reg_cco__disp_clk_gate_en,[7]reg_cco__de_clk_gate_en */
			BE_REG_WR(0xC930C000,0x00000180);//[4]reg_cco__disp_osd_clk_gate_en ??? (confirm OSD off)
			/* CTOP_SYN - fmc - CRG_FMC00 - [4]reg_fmc__de_clk_gate_en */
			BE_REG_WR(0xC9304000,0x00000010);
			/* CTOP_SYN - gsc - CRG_GSC00 - [3]reg_gsc__de_clk_gate_en */
			BE_REG_WR(0xC930D000,0x00000008);
			/* CTOP_SYN - lgsr - CRG_LGSR00 - [14]reg_lgsr__de_soc_clk_gate_en */
			BE_REG_WR(0xC9302000,0x00004000);//lne,wov conflict ???
			/* CTOP_SYN - nd0 - CRG_ND000 - [2]reg_nd0__de_clk_gate_en */
			BE_REG_WR(0xC9307000,0x00000004);
			/* CTOP_SYN - nd1 - CRG_ND100 - [2]reg_nd1__de_clk_gate_en */
			BE_REG_WR(0xC9308000,0x00000004);
			BE_NOTI("cg on de,disp\n");
			/********************************/
		#endif
			break;
		case OVI_HW_O20_PQE_PM_DEVICE_RESUME_PREPARE:
		#if 0	//see _pqe_pm_o20_hw_handler
			/* AVTASK-570, cg off de,disp */
			/* CTOP_SYN - cco - CRG_CCO00 */
			BE_REG_WR(0xC930C000,0x0);
			/* CTOP_SYN - fmc - CRG_FMC00 */
			BE_REG_WR(0xC9304000,0x0);
			/* CTOP_SYN - gsc - CRG_GSC00 */
			BE_REG_WR(0xC930D000,0x0);
			/* CTOP_SYN - lgsr - CRG_LGSR00 */
			BE_REG_WR(0xC9302000,0x0);
			/* CTOP_SYN - nd0 - CRG_ND000 */
			BE_REG_WR(0xC9307000,0x0);
			/* CTOP_SYN - nd1 - CRG_ND100 */
			BE_REG_WR(0xC9308000,0x0);
			BE_NOTI("cg off de,disp\n");
			/********************************/
			/* AVTASK-570, sync gen enable */
			BE_REG_WR(0xC930D028,0x0);//CTOP_SYN - gsc - BND_CTRL01 - [4] reg_sync_gen_disable
			BE_NOTI("reg_sync_gen_enable\n");
			/********************************/
		#endif
			break;
		case OVI_HW_O20_PQE_PM_DEVICE_RESUME:
			/* AVTASK-571, restore picinit */
			//BE_REG_WR(0xC9010000,0x00FF0000);//CCO_CTRL - PIC_INIT. see chip/o20/fbdev/fbdev_o20_hw_cmn.c
			//BE_NOTI("restore picinit\n");
			/********************************/
			break;
		case OVI_HW_O20_PQE_PM_DEVICE_RESUME_COMPLETED:
			break;
		default:
			break;
	}

	return ret;
}

int OVI_HW_O20_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int	i;
	UINT32 val;

	switch(proc_id)
	{
		case OVI_HAL_PROC_ID_DETAIL_INFO:
		{
			OVI_TCON_O20_RdFL(tcon_base_address);
			val = OVI_TCON_O20_Rd(tcon_base_address);
			seq_printf(m, "tcon_base_addr: 0x%08x\n", val);

			seq_printf(m, "ch_power_on_reg1: 0x%08x\n", _gOviHwO20Info.chPowerOnRegValue1 );

			for (i=0; i<_gOVIOutputModes_O20.number_of_modes; i++)
			{
				seq_printf(m, "output_mode%d: %s", i, _gOVIOutputModes_O20.pOVIOutputModes[i].index + strlen("Display settings for O20"));
			}

			OVI_OIF_O20_RdFL(oif_lvds_config0);

			OVI_OIF_O20_Rd01(oif_lvds_config0, lvds_lsb_first, val);
			seq_printf(m, "lvds.format: %s (0x%x)\n", (val)?"vesa":"jeida", val);

			OVI_OIF_O20_Rd01(oif_lvds_config0, lvds_8bit_mode, val);
			seq_printf(m, "lvds.bit: %d bit (0x%x)\n", (val)? 8:10, val);

			OVI_OIF_O20_RdFL(oif_lvds_config1);
			OVI_OIF_O20_Rd01(oif_lvds_config1, lvds_force_even_data, val);
			seq_printf(m, "lvds.black_out: %s (0x%x)\n", (val)? "black":"orignal", val);

			OVI_TCON_O20_RdFL(tcon_gclk_control);
			OVI_TCON_O20_Rd01(tcon_gclk_control, gclk_en, val);
			seq_printf(m, "tcon.gclk: %s (0x%x)\n", (val)?"on":"off", val);

			OVI_TCON_O20_RdFL(tcon_mclk_control);
			OVI_TCON_O20_Rd01(tcon_mclk_control, mclk_en, val);
			seq_printf(m, "tcon.mclk: %s (0x%x)\n", (val)?"on":"off", val);
		}
		break;
		case OVI_HAL_PROC_ID_DISP_OUTPUT_INFO:
		{
			char *iface[LX_OVI_PANEL_INTERFACE_MAX] = {"LVDS","EPI","EPI_QSAC","Vx1","CEDS"};
			char *lockStatus[3] = {"Locked","Unlocked","Unknown"};
			UINT32 reverseVal;
			UINT32 lockFlag;
			UINT32 regVal;

			OVI_REG_RD(0xC930F030, regVal); // dpe_syn c4tx_ctrl

			if (_gOviHwO20Info.dispOption.panelInterface == LX_OVI_PANEL_VX1)
			{
				lockFlag = (regVal & 0x8) >> 3;
			}
			else if (_gOviHwO20Info.dispOption.panelInterface == LX_OVI_PANEL_EPI ||
				_gOviHwO20Info.dispOption.panelInterface == LX_OVI_PANEL_EPI_QSAC ||
				_gOviHwO20Info.dispOption.panelInterface == LX_OVI_PANEL_CEDS)
			{
				lockFlag = (regVal & 0x80) >> 7;
			}
			else
			{
				lockFlag = 2;
			}

			OVI_TCON_O20_RdFL(tcon_hor_mode);
			OVI_TCON_O20_Rd01(tcon_hor_mode, hor_reverse, reverseVal);

			seq_printf(m, "vbe_lockStatus=%s\n", lockStatus[lockFlag]);
			seq_printf(m, "vbe_displayOutput=%s\n", _gOviHwO20Info.isDispOutDisabled ? "off" : "on");
			seq_printf(m, "vbe_outputFrameRate=%s\n", _gOviHwO20Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ ? "60" : "120");
			seq_printf(m, "vbe_panelInterface=%s\n", iface[_gOviHwO20Info.dispOption.panelInterface]);
			seq_printf(m, "vbe_mute=%s\n", _gOviHwO20Info.mute ? "on" : "off");
			seq_printf(m, "vbe_mirrorH=%s\n", reverseVal == _gOviHwO20Info.horReverseRegFieldValue ? "off" : "on");
			seq_printf(m, "vbe_mirrorV=%s\n", _gOviHwO20Info.mirrorV ? "on" : "off");
			seq_printf(m, "is_ATELIER=%s\n", RET_OK == OS_ScanKernelCmdlineToken("ATELIER") ? "yes" : "no");

		}
		break;
		case OVI_HAL_PROC_ID_MIRROR_VERTICAL_INFO:
		{
			_gOviHwO20Info.mirrorV = *((UINT32 *)data);
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return RET_OK;
}

/** @} */
