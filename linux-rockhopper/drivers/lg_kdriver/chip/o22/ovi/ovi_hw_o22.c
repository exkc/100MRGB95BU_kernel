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
#include <linux/delay.h>
#include "os_util.h"

#include "ovi_dbg.h"
#include "ovi_hal.h"
#include "ovi_hw_o22.h"
#include "ovi_reg_def_o22.h"
#include "ovi_reg_o22.h"

#include "../be/reg/be_reg_dpe_o22.h"

// For CTOP register access
#include "../../../core/sys/sys_regs.h"

#include "ovi_output_format_o22a0.h"

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
#include "be_cfg.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define OVI_HW_O22_PQE_PM_DEVICE_SUSPEND_PREPARE	0
//fw stall
#define OVI_HW_O22_PQE_PM_DEVICE_SUSPEND			1
//cg on
#define OVI_HW_O22_PQE_PM_DEVICE_SUSPEND_COMPLETED	2
#define OVI_HW_O22_PQE_PM_DEVICE_RESUME_PREPARE		3
//cg off
#define OVI_HW_O22_PQE_PM_DEVICE_RESUME				4
//fw restart
#define OVI_HW_O22_PQE_PM_DEVICE_RESUME_COMPLETED	5

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
#else
#define OVI_HW_O22_GAMMA_TABLE_SIZENUM 1024
#endif
#if 0
#define OVI_HW_O22_INPUT_OD_SIZENUM (17*17)
#define OVI_HW_O22_INPUT_LOD_SIZENUM (876)
#define OVI_HW_O22_INPUT_POD2_SIZENUM (1848)
#define OVI_HW_O22_INPUT_TSCIC_CTRL_SIZENUM (43)
#define OVI_HW_O22_INPUT_TSCIC_DATA_SIZE (377612)
#endif
#define OVI_HW_O22_INPUT_VCOM_PAT_DATA_SIZE (96)
#define OVI_HW_O22_WB_GAIN_STEP1 26	// 0.26% step per w/b gain 1
#define OVI_HW_O22_WB_GAIN_STEP2 38	// 0.38% step per w/b gain 1
#define OVI_HW_O22_WB_OFFSET_STEP 8	// 8 step per w/b offset 1
#define OVI_HW_O22_WB_DEFAULT_GAIN 16384
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
#define OVI_HW_F22_REG_DPG_LUT_WDATA 0xF4080A08
#define OVI_HW_F22_REG_DPG_LUT_WR_DONE 0xF4080A04
#define OVI_HW_F22_REG_DPG_EN 0xF4080A00
#define OVI_HW_F22_REG_WB_EN 0xF4080AC0
#define OVI_HW_F22_REG_WB_R_GAIN 0xF4080AC4
#define OVI_HW_F22_REG_WB_G_GAIN 0xF4080AC8
#define OVI_HW_F22_REG_WB_B_GAIN 0xF4080ACC
#define OVI_HW_F22_REG_WB_R_OFFSET 0xF4080AD0
#define OVI_HW_F22_REG_WB_G_OFFSET 0xF4080AD4
#define OVI_HW_F22_REG_WB_B_OFFSET 0xF4080AD8

#define _B2L32(data) ((((UINT32)(data&0xff000000) >> 24) & 0x000000ff) |   \
					(((UINT32)(data&0x00ff0000) >>  8) & 0x0000ff00) |   \
					(((UINT32)(data&0x0000ff00) <<  8) & 0x00ff0000) |   \
					(((UINT32)(data&0x000000ff) << 24) & 0xff000000))
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


#define OVI_HW_O22_CH_POWER_REG_MASK	0x00FFFFFF

#define OVI_HW_O22_REG_PARAM_OP_WRITE		0x0
#define OVI_HW_O22_REG_PARAM_OP_WAIT		0x1
#define OVI_HW_O22_REG_PARAM_OP_CHECK		0x2
#define OVI_HW_O22_REG_PARAM_OP_RESERVED	0x3
#define OVI_HW_O22_REG_PARAM_OP_MASK		0x3

#define OVI_HW_O22_REG_SET_A0_START		0x000000A0
#define OVI_HW_O22_REG_SET_B0_START		0x000000B0
// Max Value < 0x000000A0
#define OVI_HW_O22_REG_READ_START		0x00000001
#define OVI_HW_O22_REG_CHECK_END		0x00000000

#define OVI_HW_O22_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define OVI_HW_O22_BOE_FW_SIZE 32256

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
typedef struct{
	UINT8 pemp[24];
	UINT8 itune[24];
} OVI_HW_O22_PEMP_ITUNE_DATA_T;

typedef struct {
	struct delayed_work dlyWork;
	UINT32 *pu32LutR;
	UINT32 *pu32LutG;
	UINT32 *pu32LutB;
} OVI_HW_O22_DLY_RGB_GAMMA_T;

typedef struct {
	UINT32 chPowerOnRegValue1;
	UINT32 chPowerOnRegValue2;
	UINT32 tconBaseAddress;

	UINT32 spreadSpectrumRegValue1;
	UINT32 spreadSpectrumRegValue2;
	UINT32 spreadSpectrumRegValue3;

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

	UINT32 pllMuxSelRegValue;

	UINT32 tconClkGatingRegValue;

	LX_OVI_DISPLAY_INFO_T dispOption; // use only for display resume
	LX_OVI_HW_DISPLAY_INFO_T hwDispOption;

	BOOLEAN mute;
	UINT32 mirrorV;
	UINT32 mirrorH;

	struct task_struct* tscicThread;
	BOOLEAN tscicWritingFlag;
	UINT32 tscicSize;
	UINT32 *tscicU32Tbl;
	UINT32 tscicCtrlSizeNum;
	UINT8 *tscicU8CtrlData;
	OVI_HW_O22_PEMP_ITUNE_DATA_T pempItuneData;
	UINT8 dcVal[24];
	UINT32 patType;
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
	void *pVx1ChipInfoVMapAddr;
	BE_OVI_HW_O22_VX1_CHIP_INFO_T *pVx1ChipInfo[BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_NUM];
#endif

	OVI_HW_O22_DLY_RGB_GAMMA_T delayedRGBGamma;

	UINT32 pm_status;
	UINT32 pm_suspend;
} OVI_HW_O22_INFO_T;

typedef struct{
	LX_OVI_OUTPUT_MODE_T	*pOVIOutputModes;
	UINT32 number_of_modes;
} OVI_HW_O22_OUTPUT_MODES_T;

#if 0
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
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O22A0_T;

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
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O22A0_T;

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
}OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_O22A0_T;
#endif

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T *gpOviTconMem;
extern DPE_LED_REG_O22_T gDPE_LED_O22;
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
extern BE_FRM_MEM_CFG_T *gpBeChInfMem;
#endif

extern int g_panelFrameRate;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
OVI_TCON_REG_O22_T gOVI_TCON_O22;
#if 0
OVI_TCON_LODC_REG_O22_T gOVI_TCON_LODC_O22;
OVI_TCON_CAD_REG_O22_T gOVI_TCON_CAD_O22;
#endif
OVI_OIF_REG_O22_T gOVI_OIF_O22;

static volatile unsigned int *gMapped_address;

LX_OVI_OUTPUT_MODE_T _gOVIOutputModes_O22Ax[] =
{
	{"Disp-O22 4k60Hz Vx1\n",  ovi_o22a0_disp_4k60_vx1_8lane, sizeof(ovi_o22a0_disp_4k60_vx1_8lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-O22 4k120Hz Vx1\n",  ovi_o22a0_disp_4k120_vx1_16lane, sizeof(ovi_o22a0_disp_4k120_vx1_16lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-O22 4k120Hz Vx1 5Byte\n",  ovi_o22a0_disp_4k120_vx1_16lane_5byte, sizeof(ovi_o22a0_disp_4k120_vx1_16lane_5byte)/sizeof(LX_OVI_REG_T)},
	{"Disp-O22 4k120Hz Vx1 24LANE 5Byte\n",  ovi_o22a0_disp_4k120_vx1_24lane_5byte, sizeof(ovi_o22a0_disp_4k120_vx1_24lane_5byte)/sizeof(LX_OVI_REG_T)}
};

OVI_HW_O22_OUTPUT_MODES_T _gOVIOutputModes_O22 =
{
	.pOVIOutputModes 	 = NULL,
	.number_of_modes	 = 0,
};

#if 0
volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O22A0_T *gOVI_HW_O22_SS_CTRL1 = NULL;
volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O22A0_T *gOVI_HW_O22_SS_CTRL2 = NULL;
volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_O22A0_T *gOVI_HW_O22_SS_CTRL3 = NULL;
#endif

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static UINT32 _OVI_O22_GetGain(UINT32 gain);
static SINT16 _OVI_O22_GetOffset(UINT32 offset);
static void _OVI_O22_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore);
__attribute__((unused)) static void _OVI_O22_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);
__attribute__((unused)) static void _OVI_O22_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);

static void _OVI_O22_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_O22_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_O22_DispOutputEnable(BOOLEAN bParam);
static void _OVI_O22_GetHWDispOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);
static void _OVI_O22_DispSpreadSpectrumInit(void);

static void _OVI_O22_CallbackDelayedGamma(struct work_struct *work);

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
static int _OVI_O22_Vx1ChipInfoMemInit(void);
static void _OVI_O22_Vx1ChipInfoMemFill(void);
static void _OVI_O22_UpdateChipInfoHeader(void);
#endif

static int _OVI_O22_GetPempItuneData(OVI_HW_O22_PEMP_ITUNE_DATA_T *pstParams);
static int _OVI_O22_SetPempItuneData(OVI_HW_O22_PEMP_ITUNE_DATA_T *pstParams);
static void _OVI_O22_Set_DC_Cal(UINT8 *data);
static void _OVI_O22_Get_DC_Cal(UINT8 *data);
static void _OVI_O22_Draw_Pat(int num);
/*----------------------------------------------------------------------------------------
	Internal Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int OVI_O22_TscicWriteThread(void* data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _gPrevRedGain = OVI_HW_O22_WB_DEFAULT_GAIN;
static UINT32 _gPrevGreenGain = OVI_HW_O22_WB_DEFAULT_GAIN;
static UINT32 _gPrevBlueGain = OVI_HW_O22_WB_DEFAULT_GAIN;

static SINT16 _gPrevRedOffset = 0;
static SINT16 _gPrevGreenOffset = 0;
static SINT16 _gPrevBlueOffset = 0;

static LX_OVI_TCON_COLOR_TEMP_T _gColTemp;

static OVI_HW_O22_INFO_T _gOviHwO22Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
static void _OVI_O22_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore)
{
	if (regParamVal >= OVI_HW_O22_REG_SET_A0_START)
	{
		if (lx_chip_rev() >= LX_CHIP_REV(O22, B0))
		{
			if (regParamVal != OVI_HW_O22_REG_SET_B0_START)
			{
				*pbIgnore = TRUE;
			}
		}
		else
		{
			if (regParamVal != OVI_HW_O22_REG_SET_A0_START)
			{
				*pbIgnore = TRUE;
			}
		}
	}
	else if (regParamVal == OVI_HW_O22_REG_CHECK_END)
	{
		*pbIgnore = FALSE;
	}

	return;
}

__attribute__((unused)) static void _OVI_O22_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN ignore = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_O22_REG_PARAM_OP_MASK)
		{
			case OVI_HW_O22_REG_PARAM_OP_WAIT:	// wait
				if (!ignore)
				{
					OS_UsecDelay(param->value);
				}
				OVI_DEBUG("delay(_%dms);\n", param->value/1000);
				break;

			case OVI_HW_O22_REG_PARAM_OP_CHECK:	// check
				_OVI_O22_IgnoreRegSet(param->value, &ignore);
				OVI_DEBUG("ignore : %d\n", ignore);
				break;

			case OVI_HW_O22_REG_PARAM_OP_RESERVED:
				OVI_DEBUG("OVI_HW_O22_REG_PARAM_OP_RESERVED\n");
				break;

			default:	// OVI_HW_O22_REG_PARAM_OP_WRITE
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

__attribute__((unused)) static void _OVI_O22_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN readReg = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_O22_REG_PARAM_OP_MASK)
		{
			case OVI_HW_O22_REG_PARAM_OP_CHECK:	// check for register read
				if (param->value == OVI_HW_O22_REG_READ_START)
				{
					readReg = TRUE;
				}
				else if (param->value == OVI_HW_O22_REG_CHECK_END)
				{
					readReg = FALSE;
				}
				OVI_DEBUG("readReg : %d\n", readReg);
				break;

			default:	// OVI_HW_O22_REG_PARAM_OP_WRITE
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

static void _OVI_O22_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	//OVI_REG_RD(0xCC432070, _gOviHwO22Info.pllMuxSelRegValue);
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					#if 0 // block for bringup
					_OVI_O22_RegParamRead(ovi_o22a0_disp_2k60_lvds_2link, 
											OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_2k60_lvds_2link), 0);
					#endif
					break;
					
				case LX_OVI_PANEL_VX1:
				default :
					_OVI_O22_RegParamRead(ovi_o22a0_disp_4k60_vx1_8lane, 
											OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k60_vx1_8lane), 0);
					_gOviHwO22Info.chPowerOnRegValue1 = 0x00000FF0;
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					#if 0 // block for bringup
					_OVI_O22_RegParamRead(ovi_o22a0_disp_2k120_lvds_4link, 
											OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_2k120_lvds_4link), 0);
					#endif
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22)
					{
						_OVI_O22_RegParamRead(ovi_o22a0_disp_4k120_vx1_24lane_5byte, 
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k120_vx1_24lane_5byte), 0);
						_gOviHwO22Info.chPowerOnRegValue1 = 0x00FFFFFF;
					}
					else if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						_OVI_O22_RegParamRead(ovi_o22a0_disp_4k120_vx1_16lane_5byte, 
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k120_vx1_16lane_5byte), 0);
						_gOviHwO22Info.chPowerOnRegValue1 = 0x000FFFF0;
					}
					else if (stDispParams.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
					{
						_OVI_O22_RegParamRead(ovi_o22a0_disp_2k120_vx1_4lane_4byte,
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_2k120_vx1_4lane_4byte), 0);
						_gOviHwO22Info.chPowerOnRegValue1 = 0x00000FF0;
					}
					else
					{
						_OVI_O22_RegParamRead(ovi_o22a0_disp_4k120_vx1_16lane, 
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k120_vx1_16lane), 0);
						_gOviHwO22Info.chPowerOnRegValue1 = 0x000FFFF0;
					}
					break;
			}
			break;
		case LX_OVI_PANEL_FRAMERATE_144Hz:
			UINT32 regVal;
			if (RET_OK == OS_ScanKernelCmdlineToken("WirelessAV"))
			{
#if 0
				OVI_REG_RD(0xCC432058, regVal)
				if(regVal != (0x010C7001))
				{
					OVI_REG_WR(0xC603306C, 0x000007F3); //85.86MHz wireless model

					OVI_REG_WR(0xCC43207C, 0x1A808810);
					OVI_REG_WR(0xCC432080, 0x1BDA5105);
					OVI_REG_WR(0xCC432084, 0xBF000000);
					OVI_REG_WR(0xC603306C, 0x000007FB);

					OVI_REG_WR(0xCC432058, 0x010C7001);
					OVI_REG_WR(0xCC432060, 0x00303032);
					OVI_REG_WR(0xCC43205C, 0x01A0C099);
					OVI_REG_WR(0xCC43205C, 0x0120C099);
					OVI_REG_WR(0xC603306C, 0x000007FF);

					OVI_REG_WR(0xcc460090, 0x401bda51);
					_OVI_O22_RegParamRead(ovi_o22a0_disp_4k144_vx1_16lane_5byte_lcd_wireless, OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k144_vx1_16lane_5byte_lcd_wireless), 0);
					_gOviHwO22Info.chPowerOnRegValue1 = 0x000FFFF0;
				}
#endif
				_OVI_O22_RegParamRead(ovi_o22a0_disp_4k144_vx1_16lane_5byte_lcd_wireless, OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k144_vx1_16lane_5byte_lcd_wireless), 0);
				_gOviHwO22Info.chPowerOnRegValue1 = 0x000FFFF0;
			}
			else
			{
				_OVI_O22_RegParamRead(ovi_o22a0_disp_4k144_vx1_16lane_5byte, OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k144_vx1_16lane_5byte), 0);
				_gOviHwO22Info.chPowerOnRegValue1 = 0x000FFFF0;
			}
			break;

		default :
			break;
	}
	
	return;
}

static void _OVI_O22_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;
	char hw_opt[32];

	OVI_PRINT("\n[_OVI_O22_DispInit] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
		pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
		pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
		pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

	if(pstParams->panelInterface == 0 && pstParams->panelFramerate == 0 && pstParams->panelFramerate == 0 && pstParams->panelBacklight == 0 && pstParams->panelInch == 0)
	{
		OVI_PRINT("DispInit skip\n");
		return;
	}

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	if(stDispParams.panelFramerate != LX_OVI_PANEL_FRAMERATE_144Hz)
	{
		// Display Spread Spectrum
		_OVI_O22_DispSpreadSpectrumInit();
		OVI_PRINT("_OVI_O22_DispSpreadSpectrumInit setting\n");
	}
	else
	{
		OVI_PRINT("_OVI_O22_DispSpreadSpectrumInit skip\n");
	}

	// Display PLL MUX setting for DCO FCW control
	OVI_REG_RD(0xCC432070, _gOviHwO22Info.pllMuxSelRegValue);
	_gOviHwO22Info.pllMuxSelRegValue = (_gOviHwO22Info.pllMuxSelRegValue & 0xFFFFFCCF) | (1 << 4) | (1 << 8);
	OVI_REG_WR(0xCC432070, _gOviHwO22Info.pllMuxSelRegValue);

	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					#if 0 // block for bringup
					_OVI_O22_RegParamSet(ovi_o22a0_disp_2k60_lvds_2link, 
											OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_2k60_lvds_2link), 0);

					if (stDispParams.lvdsType == LX_OVI_LVDS_OUT_JEIDA)
					{
						OVI_REG_WR(0xCC44901C, 0x1814E);
					}
					#endif
					break;
					
				case LX_OVI_PANEL_VX1:
				default :
					_OVI_O22_RegParamSet(ovi_o22a0_disp_4k60_vx1_8lane, 
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k60_vx1_8lane), 0);
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					#if 0 // block for bringup
					_OVI_O22_RegParamSet(ovi_o22a0_disp_2k120_lvds_4link, 
											OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_2k120_lvds_4link), 0);
					#endif
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22)
					{
						_OVI_O22_RegParamSet(ovi_o22a0_disp_4k120_vx1_24lane_5byte, 
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k120_vx1_24lane_5byte), 0);
					}
					else if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						_OVI_O22_RegParamSet(ovi_o22a0_disp_4k120_vx1_16lane_5byte, 
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k120_vx1_16lane_5byte), 0);
					}
					else if (stDispParams.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
					{
						_OVI_O22_RegParamSet(ovi_o22a0_disp_2k120_vx1_4lane_4byte,
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_2k120_vx1_4lane_4byte), 0);
					}
					else
					{
						_OVI_O22_RegParamSet(ovi_o22a0_disp_4k120_vx1_16lane, 
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k120_vx1_16lane), 0);
					}
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_144Hz:
			UINT32 regVal;
			if (RET_OK == OS_ScanKernelCmdlineToken("WirelessAV"))
			{
				OVI_PRINT("=================== KDRV Disp_init LCD_144Hz_wireless_model\n");
				OVI_REG_RD(0xCC432058, regVal)
				if(regVal != (0x010C7001))
				{
					OVI_PRINT("=================== KDRV Disp_init set!!\n");
					OVI_REG_WR(0xC603306C, 0x000007F3); //85.86MHz wireless model

					OVI_REG_WR(0xCC43207C, 0x1A808810);
					OVI_REG_WR(0xCC432080, 0x1BDA5105);
					OVI_REG_WR(0xCC432084, 0xBF000000);
					OVI_REG_WR(0xC603306C, 0x000007FB);

					OVI_REG_WR(0xCC432058, 0x010C7001);
					OVI_REG_WR(0xCC432060, 0x00303032);
					OVI_REG_WR(0xCC43205C, 0x01A0C099);
					OVI_REG_WR(0xCC43205C, 0x0120C099);
					OVI_REG_WR(0xC603306C, 0x000007FF);

					OVI_REG_WR(0xcc460090, 0x401bda51);

					_OVI_O22_RegParamSet(ovi_o22a0_disp_4k144_vx1_16lane_5byte_lcd_wireless, OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k144_vx1_16lane_5byte_lcd_wireless), 0);
				}
			}
			else
			{
				OVI_REG_RD(0xCC432058, regVal)
				if(regVal != (0x02177163))
				{
					OVI_REG_WR(0xC603306C, 0x000007F7); //84.24MHz

					OVI_REG_WR(0xCC432058, 0x02177163);
					OVI_REG_WR(0xCC43205C, 0x01A18024);
					OVI_REG_WR(0xCC432060, 0x00010042);
					OVI_REG_WR(0xCC43205C, 0x01218024); //spread spectrum setting

					OVI_REG_WR(0xC603306C, 0x000007FF);

					_OVI_O22_RegParamSet(ovi_o22a0_disp_4k144_vx1_16lane_5byte, OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_4k144_vx1_16lane_5byte), 0);
					OVI_PRINT("OVI DispInit: 144Hz pannel setting\n");
				}
			}
			break;

		default :
			break;
	}

	#if 0 // not support
	_OVI_O22_RegParamSet(ovi_o22a0_disp_preEmp_swiLvl, 
												OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_preEmp_swiLvl), 0);
	#endif

	if (RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
	{
		if (!strncmp(hw_opt,"oled",4)) // LCD H/W option -> forced OLED option
		{
			// PWM forced high
			OVI_REG_WR(0xCC460110, 0x1);
			OVI_REG_WR(0xCC46011C, 0x1);
			OVI_REG_WR(0xCC460118, 0x40000000);
			OVI_REG_WR(0xCC460124, 0x40000000);
		}
	}
	
	return;
}

static void _OVI_O22_DispOutputEnable(BOOLEAN bParam)
{

	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r04);
	CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r05);
	if(bParam)// display output on
	{
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r04, _gOviHwO22Info.chPowerOnRegValue1);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r05, _gOviHwO22Info.chPowerOnRegValue2);
		OVI_DEBUG("[OVI] display is changed to ON status!\n");

		{	// initialize Vx1 Lock status counter
			CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
			CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r01, 0x00000030);
			CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r01);

			CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
			CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r01, 0x00000020);
			CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r01);
		}
	}
	else // display output off
	{
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r04, _gOviHwO22Info.chPowerOnRegValue1 & (~OVI_HW_O22_CH_POWER_REG_MASK));
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r05, _gOviHwO22Info.chPowerOnRegValue2 & (~0x10));
		OVI_DEBUG("[OVI] display is changed to OFF status!\n");
	}
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r04);
	CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r05);

	_gOviHwO22Info.isDispOutDisabled = bParam ? FALSE : TRUE;
	
	return;
}

/* Notice!! : 
Cannot use block register macro(ex. CTOP_CTRL_..., OVI_TCON_...) - because of the function call timing */
static void _OVI_O22_GetHWDispOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
{
	__attribute__((unused)) char hw_opt[32];
	LX_OVI_HW_DISPLAY_INFO_T dispOpt;

	dispOpt.panelInterface = LX_OVI_PANEL_VX1;
	dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_3840X2160;
	dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_3840X2160;
	dispOpt.frcChipType = LX_OVI_FRC_CHIP_INTERNAL;
	dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_EDGE_LED;
	dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
	dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
	dispOpt.isVx15Byte = FALSE;
	dispOpt.isDispForceFreerun = FALSE;
	dispOpt.panel_fr_option = LX_OVI_PANEL_FR_OPTION_NONE;

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

		if (hw_opt[3] == '0') // HD resolution
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
		}
		else if (hw_opt[3] == '1') // FHD resolution
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
		}
		else if ((hw_opt[3] == '3') || (hw_opt[17] == '9')) // 8k 
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_7680X4320;
		}

		if (hw_opt[4] == '0') // NO FRC(main SoC)
		{
			dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
		}

		if (hw_opt[9] == '0') // panel output framerate 60HZ
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
		}
		else if (hw_opt[9] == '2') // panel output framerate 144Hz
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_144Hz;
			dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_144Hz;
		}

		if (hw_opt[12] == '1') // OLED
		{
			dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
		}

		if (hw_opt[17] == '9') // FRC type F22
		{
			dispOpt.frcChipType = LX_OVI_FRC_CHIP_UD_BE_F22;
		}
	}
	else
	{
		__attribute__((unused)) UINT32 regVal;
		
		/* 2k/4k model
		(4k 60Hz : 0xCC450010[5:4] - 1, 4k 120Hz : 0xCC450010[5:4] - 0)
		(2k 60Hz : 0xCC450010[5:4] - 3, 2k 120Hz : 0xCC450010[5:4] - 2)
		*/
		OVI_REG_RD(0xCC450010, regVal);
		regVal = (regVal >> 4) & 0x3;
		if (regVal == 1 || regVal == 3)
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;

			if (regVal == 3)
			{
				dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
				dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
			}
		}
		
		OVI_REG_RD(0xCC490010, regVal);
		if (regVal & 0x1)
		{
			dispOpt.frcChipType = LX_OVI_FRC_CHIP_UD_BE_F22;
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_7680X4320;
		}
	}

	if (RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
	{
		if ((!strncmp(hw_opt,"hdmi60",6))
				&& (dispOpt.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22))
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ_FIXED; // Ext. FRC freerun + 60Hz fixed frame rate
		}
		else if ((!strncmp(hw_opt,"hdmi5060",8))
				&& (dispOpt.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22))
		{
			dispOpt.isDispForceFreerun = TRUE; // Main SoC/Ext. FRC freerun
		}
		else if (!strncmp(hw_opt,"hdmi",4))
		{
			dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;

			if (!strncmp(hw_opt,"hdmi60",6))
			{
				dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ_FIXED;
				dispOpt.isDispForceFreerun = TRUE;
			}
			else if (!strncmp(hw_opt,"hdmi5060",8))
			{
				dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
				dispOpt.isDispForceFreerun = TRUE;
			}
			else
			{
				dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			}
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
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1920X1080;
		}
		else if (strstr(hw_opt,"1366x768"))
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1366X768;
		}
		else if (strstr(hw_opt,"1280x720"))
		{
			dispOpt.panelResolution = LX_OVI_PANEL_RESOLUTION_1280X720;
			dispOpt.dispResolution = LX_OVI_PANEL_RESOLUTION_1280X720;
		}

		if (strstr(hw_opt,"stb"))
		{
			dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_NONE;
		}
	}

	if(RET_OK==OS_ScanKernelCmdline("id_disptype=%s", hw_opt))
	{
		if(strstr(hw_opt,"amled144"))
		{
			if (dispOpt.panelResolution == LX_OVI_PANEL_RESOLUTION_1920X1080)
			{
				dispOpt.panel_fr_option = LX_OVI_PANEL_FR_OPTION_02;//amled144, 2K LGD(SCDCRID-3366)
			}
			else
			{
				dispOpt.panel_fr_option = LX_OVI_PANEL_FR_OPTION_01;//amled144, 4K,2K LGD(SCDCRID-3267)
			}
		}
		else if(strstr(hw_opt,"pmled"))
		{
			dispOpt.panel_fr_option = LX_OVI_PANEL_FR_OPTION_05;//pmled, 4K LED(SCDCRID-3459)
		}
	}

	memcpy((void *)pstParams, (void *)&dispOpt, sizeof(LX_OVI_HW_DISPLAY_INFO_T));
	
	return;
}

static void _OVI_O22_DispSpreadSpectrumInit(void)
{
	if (_gOviHwO22Info.spreadSpectrumRegValue2 & (1<<23)) // DSS OFF
	{
		OVI_REG_WR(0xCC43205C, _gOviHwO22Info.spreadSpectrumRegValue2);
	}
	else // 0.5%, 30KHz
	{
		OVI_REG_WR(0xC603306C, 0x00000FF7); //Power Down for DISP PLL setting (not for DISP SS setting)

		OVI_REG_WR(0xCC432058, _gOviHwO22Info.spreadSpectrumRegValue1);
		OVI_REG_WR(0xCC43205C, _gOviHwO22Info.spreadSpectrumRegValue2 | (1<<23));
		if (_gOviHwO22Info.hwDispOption.panel_fr_option != LX_OVI_PANEL_FR_OPTION_NONE)
		{
			OVI_REG_WR(0xCC432060, _gOviHwO22Info.spreadSpectrumRegValue3);
		}
		else
		{
			OVI_REG_WR(0xCC432060, 0x00111042);
		}

		OVI_REG_WR(0xC603306C, 0x00000FFF); //Power On

		OS_UsecDelay(100);

		OVI_REG_WR(0xCC43205C, _gOviHwO22Info.spreadSpectrumRegValue2);
	}

	return;
}


static void _OVI_O22_CallbackDelayedGamma(struct work_struct *work)
{
	int i;
	__attribute__((unused)) UINT32 regField;

	if (_gOviHwO22Info.pm_suspend == 1)
	{
		OVI_PRINT("skip (in suspend)(%d)\n",_gOviHwO22Info.pm_status);
		return;
	}

	if ((_gOviHwO22Info.delayedRGBGamma.pu32LutR == NULL)
		|| (_gOviHwO22Info.delayedRGBGamma.pu32LutG == NULL)
		|| (_gOviHwO22Info.delayedRGBGamma.pu32LutB == NULL)) return;

	OVI_DEBUG("\n\nRetry Gamma setting!\n\n\r");

	DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
	DPE_LED_O22_Rd01(led_dpg_lut_wr_done, dpg_lut_cpy_status, regField);

	if (regField)
	{
		schedule_delayed_work(&_gOviHwO22Info.delayedRGBGamma.dlyWork, msecs_to_jiffies(10));
	}
	else
	{
		DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
		DPE_LED_O22_Wr01(led_dpg_lut_wr_done, dpg_wstart_o, 0x1);
		DPE_LED_O22_WrFL(led_dpg_lut_wr_done);

		DPE_LED_O22_RdFL(led_dpg_lut_wdata);

		/* Setting Red Gamma Table */
		for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwO22Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_O22_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Green Gamma Table */
		for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwO22Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_O22_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Blue Gamma Table */
		for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_wdata, _gOviHwO22Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			DPE_LED_O22_WrFL(led_dpg_lut_wdata);
		}

		DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
		DPE_LED_O22_Wr01(led_dpg_lut_wr_done, dpg_wdone_o, 0x1);
		DPE_LED_O22_WrFL(led_dpg_lut_wr_done);

		DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
		DPE_LED_O22_Wr01(led_dpg_lut_wr_done, dpg_lut_update, 0x1);
		DPE_LED_O22_WrFL(led_dpg_lut_wr_done);

		vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutR);
		vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutG);
		vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutB);
		_gOviHwO22Info.delayedRGBGamma.pu32LutR = NULL;
		_gOviHwO22Info.delayedRGBGamma.pu32LutG = NULL;
		_gOviHwO22Info.delayedRGBGamma.pu32LutB = NULL;
	}

}

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
static int _OVI_O22_Vx1ChipInfoMemInit(void)
{
	int ret = RET_OK;
	BE_FRM_MEM_CFG_T *pChInfMem = gpBeChInfMem;
	int i;
		
	do {
		_gOviHwO22Info.pVx1ChipInfoVMapAddr = NULL;

		if (_gOviHwO22Info.hwDispOption.frcChipType != LX_OVI_FRC_CHIP_UD_BE_F22) break;
		
		if (pChInfMem == NULL 
			|| !pChInfMem->frame_base)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		if ((pChInfMem->frame_size != BE_OVI_HW_O22_VX1_CHIP_INFO_TOTAL_MEM_SIZE)
			|| (sizeof(BE_OVI_HW_O22_VX1_CHIP_INFO_T) != BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_PACK_SIZE))
		{
			OVI_ERROR("[OVI] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		_gOviHwO22Info.pVx1ChipInfoVMapAddr = vmap_phys(pChInfMem->frame_base, pChInfMem->frame_size);
		if (_gOviHwO22Info.pVx1ChipInfoVMapAddr == NULL)
		{
			OVI_ERROR("[OVI] pVMapAddr is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		for (i=0; i<BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
		{
			if (pChInfMem->frame_size < ((BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
											+BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET \
											+sizeof(BE_OVI_HW_O22_VX1_CHIP_INFO_T))) break;
			
			_gOviHwO22Info.pVx1ChipInfo[i] = (BE_OVI_HW_O22_VX1_CHIP_INFO_T *)(_gOviHwO22Info.pVx1ChipInfoVMapAddr \
																			+(BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
																			+BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
		}
		if (i != BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_NUM)
		{
			OVI_ERROR("[OVI] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		_OVI_O22_Vx1ChipInfoMemFill();
	} while(0);

	if (ret && (_gOviHwO22Info.pVx1ChipInfoVMapAddr != NULL))
	{
		vunmap_phys(_gOviHwO22Info.pVx1ChipInfoVMapAddr);
		_gOviHwO22Info.pVx1ChipInfoVMapAddr = NULL;
	}

	return ret;
}

static void _OVI_O22_Vx1ChipInfoMemFill(void)
{
	int i;
	UINT32 *addr;
	
	if (_gOviHwO22Info.pVx1ChipInfoVMapAddr == NULL) return;

	// Fill in HDR/CRC with default value for BUFF
	for (i=0; i<BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_TOTAL_NUM; i++)
	{
		addr = (UINT32 *)(_gOviHwO22Info.pVx1ChipInfoVMapAddr+ \
							(i*BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_SIZE)+BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
		addr[0] = _B2L32(BE_OVI_HW_O22_VX1_CHIP_INFO_HDR|BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_SIZE);
		addr[1] = 0;
#else
		*addr = _B2L32(0x0EE00000|BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_SIZE);
#endif
	}

	for (i=0; i<BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
	{
		// Fill in HDR/CRC for BUFF0,3
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.info.maxNum = BE_OVI_HW_O22_VX1_CHIP_INFO_APB_NUM;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.info.bufIdx0 = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.info.bufIdx1 = 3;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.info.version = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.info.u32Data = _B2L32(_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.info.u32Data);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt1.u32Data = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt2.u32Data = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt3.u32Data = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt4.u32Data = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt5.u32Data = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt6.u32Data = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt7.u32Data = 0;
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, dpg);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->dpg);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].u32Data \
													= _B2L32(_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].u32Data);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, colorTemp);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].u32Data \
													= _B2L32(_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].u32Data);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, ledSpiCtrl);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->ledSpiCtrl);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].u32Data \
													= _B2L32(_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].u32Data);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, pcc);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->pcc);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].u32Data \
													= _B2L32(_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].u32Data);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, osdLvCtrl);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->osdLvCtrl);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].u32Data \
													= _B2L32(_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].u32Data);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, phdr);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->phdr);
		_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].u32Data \
													= _B2L32(_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].u32Data);
		_gOviHwO22Info.pVx1ChipInfo[i]->hwCrc = 0xFFFFFFFF;
		_gOviHwO22Info.pVx1ChipInfo[i]->endPacket = _B2L32(BE_OVI_HW_O22_VX1_CHIP_INFO_EP);
#else
		_gOviHwO22Info.pVx1ChipInfo[i]->dpg.dataHwHdr = _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZE); 
		_gOviHwO22Info.pVx1ChipInfo[i]->dpg.dataHwCrc = 0xFFFFFFFF;
		_gOviHwO22Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr = _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZE); 
		_gOviHwO22Info.pVx1ChipInfo[i]->dpg.ctrlHwCrc = 0xFFFFFFFF;
		_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZE); 
		_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
		_gOviHwO22Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE); 
		_gOviHwO22Info.pVx1ChipInfo[i]->ledSpiCtrl.hwCrc = 0xFFFFFFFF;
		_gOviHwO22Info.pVx1ChipInfo[i]->pcc.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_PCC_SIZE); 
		_gOviHwO22Info.pVx1ChipInfo[i]->pcc.hwCrc = 0xFFFFFFFF;
		_gOviHwO22Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE);
		_gOviHwO22Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
		_gOviHwO22Info.pVx1ChipInfo[i]->phdr.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_PHDR_SIZE);
		_gOviHwO22Info.pVx1ChipInfo[i]->phdr.hwCrc = 0xFFFFFFFF;
		_gOviHwO22Info.pVx1ChipInfo[i]->rsvd.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZE);
		_gOviHwO22Info.pVx1ChipInfo[i]->rsvd.hwCrc = 0xFFFFFFFF; 
#endif
	}

	wmb();

	return;
}

static void _OVI_O22_UpdateChipInfoHeader(void)
{
	int i;
	UINT32 hdrVal;

	if (_gOviHwO22Info.pVx1ChipInfoVMapAddr == NULL) return;

	for (i=0; i<BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
	{
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
		BE_OVI_HW_O22_VX1_CHIP_INFO_DAT_HDR_T hdr;

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->hwHdr;
		rmb();
		if (hdrVal != _B2L32(BE_OVI_HW_O22_VX1_CHIP_INFO_HDR|BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_SIZE))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->hwHdr = _B2L32(BE_OVI_HW_O22_VX1_CHIP_INFO_HDR|BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_DATA_SIZE);
		}

		hdr.info.maxNum = BE_OVI_HW_O22_VX1_CHIP_INFO_APB_NUM;
		hdr.info.bufIdx0 = 0;
		hdr.info.bufIdx1 = 3;
		hdr.info.version = 0;
		hdr.info.u32Data = _B2L32(hdr.info.u32Data);

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->datHdr.info.u32Data;
		rmb();
		if (hdrVal != hdr.info.u32Data)
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.info.u32Data = hdr.info.u32Data;
		}

		hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, dpg);
		hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->dpg);
		hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].u32Data = _B2L32(hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].u32Data);

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].u32Data;
		rmb();
		if (hdrVal != hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].u32Data)
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].u32Data = hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_DPG].u32Data;
		}

		hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, colorTemp);
		hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp);
		hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].u32Data = _B2L32(hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].u32Data);

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].u32Data;
		rmb();
		if (hdrVal != hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].u32Data)
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].u32Data = hdr.pos[OVI_HW_O22_VX1_CHIP_INFO_CLR_TMP].u32Data;
		}

		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, ledSpiCtrl);
		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->ledSpiCtrl);
		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].u32Data = _B2L32(hdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].u32Data);

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].u32Data;
		rmb();
		if (hdrVal != hdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].u32Data)
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].u32Data = hdr.pos[BE_HW_O22_VX1_CHIP_INFO_LED_CTRL].u32Data;
		}

		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, pcc);
		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->pcc);
		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].u32Data = _B2L32(hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].u32Data);

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].u32Data;
		rmb();
		if (hdrVal != hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].u32Data)
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].u32Data = hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PCC].u32Data;
		}

		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, osdLvCtrl);
		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->osdLvCtrl);
		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].u32Data = _B2L32(hdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].u32Data);

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].u32Data;
		rmb();
		if (hdrVal != hdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].u32Data)
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].u32Data = hdr.pos[BE_HW_O22_VX1_CHIP_INFO_OSD_LVL].u32Data;
		}

		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].offset = 0xFFFF & offsetof(BE_OVI_HW_O22_VX1_CHIP_INFO_T, phdr);
		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].size = 0xFFFF & sizeof(_gOviHwO22Info.pVx1ChipInfo[i]->phdr);
		hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].u32Data = _B2L32(hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].u32Data);

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].u32Data;
		rmb();
		if (hdrVal != hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].u32Data)
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].u32Data = hdr.pos[BE_HW_O22_VX1_CHIP_INFO_PHDR].u32Data;
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->hwCrc;
		rmb();
		if (hdrVal != 0xFFFFFFFF)
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->hwCrc = 0xFFFFFFFF;
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->endPacket;
		rmb();
		if (hdrVal != _B2L32(BE_OVI_HW_O22_VX1_CHIP_INFO_EP))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->endPacket = _B2L32(BE_OVI_HW_O22_VX1_CHIP_INFO_EP);
		}

#else
		// Check HDR error
		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->dpg.dataHwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZE))
			&& (hdrVal != _B2L32(0x0A010000|OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZE)))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->dpg.dataHwHdr = _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZE);
			_gOviHwO22Info.pVx1ChipInfo[i]->dpg.dataHwCrc = 0xFFFFFFFF;
			OVI_PRINT("O22A0 OVI HW UpdateChipInfoHeader dpg data: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZE)))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr = _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZE);
			_gOviHwO22Info.pVx1ChipInfo[i]->dpg.ctrlHwCrc = 0xFFFFFFFF;
			OVI_PRINT("O22A0 OVI HW UpdateChipInfoHeader dpg ctrl: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZE)))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32(0x0EE00000|OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZE);
			_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O22A0 OVI HW UpdateChipInfoHeader colrtmp: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE)))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE);
			_gOviHwO22Info.pVx1ChipInfo[i]->ledSpiCtrl.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O22A0 OVI HW UpdateChipInfoHeader ledspi: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->pcc.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_PCC_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_O22_VX1_CHIP_INFO_PCC_SIZE)))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->pcc.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_PCC_SIZE);
			_gOviHwO22Info.pVx1ChipInfo[i]->pcc.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O22A0 OVI HW UpdateChipInfoHeader pcc: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE)))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE);
			_gOviHwO22Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O22A0 OVI HW UpdateChipInfoHeader osd rgblv: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->phdr.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_PHDR_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_O22_VX1_CHIP_INFO_PHDR_SIZE)))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->phdr.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_PHDR_SIZE);
			_gOviHwO22Info.pVx1ChipInfo[i]->phdr.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O22A0 OVI HW UpdateChipInfoHeader phdr: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO22Info.pVx1ChipInfo[i]->rsvd.hwHdr;
		rmb();
		if (hdrVal != _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZE))
		{
			_gOviHwO22Info.pVx1ChipInfo[i]->rsvd.hwHdr = _B2L32(0x0EE00000|BE_HW_O22_VX1_CHIP_INFO_RSVD_SIZE);
			_gOviHwO22Info.pVx1ChipInfo[i]->rsvd.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O22A0 OVI HW UpdateChipInfoHeader rsvd: 0x%x \n",hdrVal);
		}
#endif
	}

	wmb();

	return;
}
#endif

int OVI_O22_TscicWriteThread(void* data)
{
	int ret = RET_OK;
	#if 0 // not support
	int i;
	volatile UINT32 *regAddr = NULL;
	UINT32 tscicSizeNum;
	UINT32 tscicCtrlSizeNum;
	do {

		if (_gOviHwO22Info.tscicWritingFlag == TRUE)
		{
			OVI_ERROR("[OVI] already running!\n");
			ret = RET_ERROR;
			return ret;
		}

		_gOviHwO22Info.tscicWritingFlag = TRUE;

		// check input table size
		if ((_gOviHwO22Info.tscicCtrlSizeNum != OVI_HW_O22_INPUT_TSCIC_CTRL_SIZENUM) || (_gOviHwO22Info.tscicU8CtrlData == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		if ((_gOviHwO22Info.tscicSize != OVI_HW_O22_INPUT_TSCIC_DATA_SIZE) || (_gOviHwO22Info.tscicU32Tbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		tscicSizeNum = _gOviHwO22Info.tscicSize / sizeof(UINT32);
		tscicCtrlSizeNum = _gOviHwO22Info.tscicCtrlSizeNum;

		// FCIC data setting
		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_O22A0_BASE + offsetof(OVI_TCON_REG_O22A0_T, tcon_fcic_data_a), 
											sizeof(UINT32));
		if (regAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		OVI_TCON_O22_RdFL(tcon_fcic_ctrl);
		OVI_TCON_O22_Wr01(tcon_fcic_ctrl, checksum_clr, 0x0);
		OVI_TCON_O22_Wr01(tcon_fcic_ctrl, flash_done, 0x0);
		OVI_TCON_O22_WrFL(tcon_fcic_ctrl);

		OVI_TCON_O22_RdFL(tcon_fcic_addr);
		OVI_TCON_O22_Wr01(tcon_fcic_addr, flash_addr, 0x0);
		OVI_TCON_O22_WrFL(tcon_fcic_addr);

		for (i=0; i<tscicSizeNum; i++)
		{
			if (kthread_should_stop())
			{
				ret = RET_ERROR;

				if(_gOviHwO22Info.tscicU8CtrlData != NULL)
				{
					vfree(_gOviHwO22Info.tscicU8CtrlData);
					_gOviHwO22Info.tscicU8CtrlData = NULL;
				}
				if (_gOviHwO22Info.tscicU32Tbl != NULL)
				{
					vfree(_gOviHwO22Info.tscicU32Tbl);
					_gOviHwO22Info.tscicU32Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwO22Info.tscicThread = NULL;
				_gOviHwO22Info.tscicWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwO22Info.tscicU32Tbl[i], &regAddr[0]);
		}

		OVI_TCON_O22_RdFL(tcon_fcic_ctrl);
		OVI_TCON_O22_Wr01(tcon_fcic_ctrl, flash_done, 0x1);
		OVI_TCON_O22_WrFL(tcon_fcic_ctrl);

		iounmap((void *)regAddr);
		regAddr = NULL;

		// FCIC CTRL data setting
		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_O22A0_BASE + offsetof(OVI_TCON_REG_O22A0_T, tcon_cic_reg000), 
											sizeof(UINT32)*OVI_HW_O22_INPUT_TSCIC_CTRL_SIZENUM);
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

				if(_gOviHwO22Info.tscicU8CtrlData != NULL)
				{
					vfree(_gOviHwO22Info.tscicU8CtrlData);
					_gOviHwO22Info.tscicU8CtrlData = NULL;
				}
				if (_gOviHwO22Info.tscicU32Tbl != NULL)
				{
					vfree(_gOviHwO22Info.tscicU32Tbl);
					_gOviHwO22Info.tscicU32Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwO22Info.tscicThread = NULL;
				_gOviHwO22Info.tscicWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwO22Info.tscicU8CtrlData[i], &regAddr[i]);
		}

		OVI_TCON_O22_RdFL(tcon_init_test);
		OVI_TCON_O22_Wr01(tcon_init_test, init1_test, 0x1);
		OVI_TCON_O22_Wr01(tcon_init_test, init2_test, 0x1);
		OVI_TCON_O22_WrFL(tcon_init_test);
	} while(0);

	if(_gOviHwO22Info.tscicU8CtrlData != NULL)
	{
		vfree(_gOviHwO22Info.tscicU8CtrlData);
		_gOviHwO22Info.tscicU8CtrlData = NULL;
	}
	if (_gOviHwO22Info.tscicU32Tbl != NULL)
	{
		vfree(_gOviHwO22Info.tscicU32Tbl);
		_gOviHwO22Info.tscicU32Tbl = NULL;
	}
	if (regAddr != NULL)
		iounmap((void *)regAddr);

	_gOviHwO22Info.tscicThread = NULL;
	_gOviHwO22Info.tscicWritingFlag = FALSE;

	#endif
	return ret;
}

void OVI_HW_O22_HWDisplayOptionInit(void)
{
	OVI_PRINT("O22A0 OVI HW display option init!\n");

	_OVI_O22_GetHWDispOption(&_gOviHwO22Info.hwDispOption);
}

int OVI_HW_O22_PreInitialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("O22A0 OVI pre init!\n");

		_OVI_O22_GetHWDispOption(&_gOviHwO22Info.hwDispOption);
	} while(0);

	return ret;
}

int OVI_HW_O22_Initialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("OVI chip revision is set to O22 A0\n");

		_gOviHwO22Info.pm_status = 0xff;
		_gOviHwO22Info.pm_suspend = 0;

		/* Set configuration of Output mode presets, for mode change on run time */
		_gOVIOutputModes_O22.pOVIOutputModes = _gOVIOutputModes_O22Ax;
		_gOVIOutputModes_O22.number_of_modes	 = sizeof(_gOVIOutputModes_O22Ax)/sizeof(LX_OVI_OUTPUT_MODE_T);

		gOVI_TCON_O22.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_REG_O22A0_T));
		#if 0 // not support
		gOVI_TCON_LODC_O22.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_LODC_REG_O22A0_T));
		gOVI_TCON_CAD_O22.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_CAD_REG_O22A0_T));
		#endif
		gOVI_OIF_O22.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_OIF_REG_O22A0_T));

		gOVI_TCON_O22.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_O22A0_BASE, sizeof(OVI_TCON_REG_O22A0_T));
		#if 0 // not support
		gOVI_TCON_LODC_O22.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_O22A0_BASE, sizeof(OVI_TCON_LODC_REG_O22A0_T));
		gOVI_TCON_CAD_O22.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_O22A0_BASE, sizeof(OVI_TCON_CAD_REG_O22A0_T));
		#endif
		gOVI_OIF_O22.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_O22A0_BASE, sizeof(OVI_OIF_REG_O22A0_T));

		/* for copying value used in channel power on/off function */
		//CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r04);
		//_gOviHwO22Info.chPowerOnRegValue1 = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r04);
		//CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r05);
		//_gOviHwO22Info.chPowerOnRegValue2 = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r05);
		_gOviHwO22Info.chPowerOnRegValue1 = 0x00FFFFFF;
		_gOviHwO22Info.chPowerOnRegValue2 = 0x10000011;

		/* for copying value used in H-Reverse on/off function */
		OVI_REG_RD(0xCC44001C, _gOviHwO22Info.horReverseRegFieldValue); // read line_delay init value
		_gOviHwO22Info.horReverseRegFieldValue = (_gOviHwO22Info.horReverseRegFieldValue >> 28) & 0x1; // [28]

		/* for copying value used in spread spectrum on/off & display resume function */
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, disp_aiopll_r00);
		_gOviHwO22Info.spreadSpectrumRegValue1 = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, disp_aiopll_r00);
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, disp_aiopll_r01);
		_gOviHwO22Info.spreadSpectrumRegValue2 = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, disp_aiopll_r01);
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, disp_aiopll_r02);
		_gOviHwO22Info.spreadSpectrumRegValue3 = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, disp_aiopll_r02);

		#if 0
		gOVI_HW_O22_SS_CTRL1 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O22A0_T *)ioremap(0xC930E400, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O22A0_T));
		gOVI_HW_O22_SS_CTRL2 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O22A0_T *)ioremap(0xC930E404, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O22A0_T));
		gOVI_HW_O22_SS_CTRL3 = (volatile OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_O22A0_T *)ioremap(0xC930E408, sizeof(OVI_CTOP_CTRL_FMS_DISP_AIOPLL2_O22A0_T));

		/* for copying value used in display resume function */
		OVI_REG_RD(0xC930F000, _gOviHwO22Info.tconClkGatingRegValue);
		#endif

#if 0
		/* for copying value used in display resume function */
		CTOP_CTRL_O22Ax_RdFL(DPE_SYN, crg_dpe00);
		_gOviHwO22Info.tconClkGatingRegValue = CTOP_CTRL_O22Ax_Rd(DPE_SYN, crg_dpe00);
#endif

		#if 0 // not support
		/* for copying value used in bypass function */
		OVI_TCON_O22_RdFL(tcon_odc_opt2);
		OVI_TCON_O22_Rd01(tcon_odc_opt2, odc_bypass, _gOviHwO22Info.odcBypassRegFieldValue); 
		OVI_TCON_O22_Rd01(tcon_odc_opt2, lodc_bypass, _gOviHwO22Info.lodcBypassRegFieldValue);

		/* Update pre-emphasis & swing level value used in display resume */
		_OVI_O22_RegParamRead(ovi_o22a0_disp_preEmp_swiLvl, 
											OVI_HW_O22_ARRAY_SIZE(ovi_o22a0_disp_preEmp_swiLvl), 0);
		#endif

		_gOviHwO22Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		_gOviHwO22Info.tscicWritingFlag = FALSE;
		_gOviHwO22Info.tscicThread = NULL;
		_gOviHwO22Info.tscicU32Tbl = NULL;
		_gOviHwO22Info.tscicU8CtrlData = NULL;

		_gOviHwO22Info.delayedRGBGamma.pu32LutR = NULL;
		_gOviHwO22Info.delayedRGBGamma.pu32LutG = NULL;
		_gOviHwO22Info.delayedRGBGamma.pu32LutB = NULL;

		_gColTemp.bIsGet = 0;
		_gColTemp.r_gain = OVI_HW_O22_WB_DEFAULT_GAIN;
		_gColTemp.g_gain = OVI_HW_O22_WB_DEFAULT_GAIN;
		_gColTemp.b_gain = OVI_HW_O22_WB_DEFAULT_GAIN;
		_gColTemp.r_offset = 0;
		_gColTemp.g_offset = 0;
		_gColTemp.b_offset = 0;

		INIT_DELAYED_WORK(&_gOviHwO22Info.delayedRGBGamma.dlyWork, _OVI_O22_CallbackDelayedGamma);

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
		ret = _OVI_O22_Vx1ChipInfoMemInit();
		if (ret)
		{
			OVI_ERROR("[OVI] Vx1 chip info memory init is failed!\n");
			OVI_BREAK_WRONG(ret);
		}
#endif

		_OVI_O22_GetPempItuneData(&_gOviHwO22Info.pempItuneData);
		_OVI_O22_Get_DC_Cal(_gOviHwO22Info.dcVal);

		{	// initialize Vx1 Lock status counter
			CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
			CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r01, 0x00000030);
			CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r01);

			CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
			CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r01, 0x00000020);
			CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r01);
		}

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base)
			|| (!gpOviTconMem->size))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! O22 ODC will be disabled!\n");

			_gOviHwO22Info.tconBaseAddress = 0;
		}
		else
		{
			_gOviHwO22Info.tconBaseAddress = gpOviTconMem->base;

			#if 0 // not support
			OVI_TCON_O22_RdFL(tcon_base_address);
			OVI_TCON_O22_Wr(tcon_base_address, _gOviHwO22Info.tconBaseAddress);
			OVI_TCON_O22_WrFL(tcon_base_address);
			#endif
		}
	} while(0);

	return ret;
}

int OVI_HW_O22_Close(void)
{
	int ret = RET_OK;

	cancel_delayed_work_sync(&_gOviHwO22Info.delayedRGBGamma.dlyWork);
	if (_gOviHwO22Info.delayedRGBGamma.pu32LutR != NULL) 
	{
		vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutR);
		_gOviHwO22Info.delayedRGBGamma.pu32LutR = NULL;
	}
	if (_gOviHwO22Info.delayedRGBGamma.pu32LutG != NULL) 
	{
		vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutG);
		_gOviHwO22Info.delayedRGBGamma.pu32LutG = NULL;
	}
	if (_gOviHwO22Info.delayedRGBGamma.pu32LutB != NULL) 
	{
		vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutB);
		_gOviHwO22Info.delayedRGBGamma.pu32LutB = NULL;
	}

	if(gOVI_TCON_O22.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_O22.shdw.addr);
		gOVI_TCON_O22.shdw.addr = NULL;
	}
	#if 0 // not support
	if(gOVI_TCON_LODC_O22.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_LODC_O22.shdw.addr);
		gOVI_TCON_LODC_O22.shdw.addr = NULL;
	}
	if(gOVI_TCON_CAD_O22.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_CAD_O22.shdw.addr);
		gOVI_TCON_CAD_O22.shdw.addr = NULL;
	}
	#endif
	if(gOVI_OIF_O22.shdw.addr)
	{
		OS_Free((void *)gOVI_OIF_O22.shdw.addr);
		gOVI_OIF_O22.shdw.addr = NULL;
	}

	if (gOVI_TCON_O22.phys.addr)
	{
		iounmap((void *)gOVI_TCON_O22.phys.addr);
		gOVI_TCON_O22.phys.addr = NULL;
	}
	#if 0 // not support
	if (gOVI_TCON_LODC_O22.phys.addr)
	{
		iounmap((void *)gOVI_TCON_LODC_O22.phys.addr);
		gOVI_TCON_LODC_O22.phys.addr = NULL;
	}
	if (gOVI_TCON_CAD_O22.phys.addr)
	{
		iounmap((void *)gOVI_TCON_CAD_O22.phys.addr);
		gOVI_TCON_CAD_O22.phys.addr = NULL;
	}
	#endif
	if (gOVI_OIF_O22.phys.addr)
	{
		iounmap((void *)gOVI_OIF_O22.phys.addr);
		gOVI_OIF_O22.phys.addr = NULL;
	}
	#if 0 // not support
	if (gOVI_HW_O22_SS_CTRL1)
	{
		iounmap((void *)gOVI_HW_O22_SS_CTRL1);
		gOVI_HW_O22_SS_CTRL1 = NULL;
	}
	if (gOVI_HW_O22_SS_CTRL2)
	{
		iounmap((void *)gOVI_HW_O22_SS_CTRL2);
		gOVI_HW_O22_SS_CTRL2 = NULL;
	}
	if (gOVI_HW_O22_SS_CTRL3)
	{
		iounmap((void *)gOVI_HW_O22_SS_CTRL3);
		gOVI_HW_O22_SS_CTRL3 = NULL;
	}
	#endif
	
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
	if (_gOviHwO22Info.pVx1ChipInfoVMapAddr != NULL)
	{
		vunmap_phys(_gOviHwO22Info.pVx1ChipInfoVMapAddr);
		_gOviHwO22Info.pVx1ChipInfoVMapAddr = NULL;
	}
#endif

	return ret;
}

int OVI_HW_O22_Suspend(void)
{
	int ret = RET_OK;

	do {
		cancel_delayed_work_sync(&_gOviHwO22Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutR);
			_gOviHwO22Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutG);
			_gOviHwO22Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutB);
			_gOviHwO22Info.delayedRGBGamma.pu32LutB = NULL;
		}
	} while(0);

	return ret;
}

int OVI_HW_O22_EarlyResume(void)
{
	int ret = RET_OK;

	do {

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r04);
		if (!(CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r04) & OVI_HW_O22_CH_POWER_REG_MASK)) // Instant boot
		{
			_OVI_O22_DispInit(&_gOviHwO22Info.dispOption);
		}

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
		else
		{
			_OVI_O22_Vx1ChipInfoMemFill();
		}
#endif
	} while(0);

	return ret;
}

int OVI_HW_O22_Resume(void)
{
	int ret = RET_OK;

	do {
		#if 0 // not support
		CTOP_CTRL_O22Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
		if (!(CTOP_CTRL_O22Ax_Rd(CTOP_DPE, ctop_dpe_r42) & OVI_HW_O22_CH_POWER_REG_MASK)) // Instant boot
		{
			if (_gOviHwO22Info.tscicWritingFlag == TRUE)
			{
				if (_gOviHwO22Info.tscicThread != NULL)
				{
					kthread_stop(_gOviHwO22Info.tscicThread);
					_gOviHwO22Info.tscicThread = NULL;
				}

				_gOviHwO22Info.tscicWritingFlag = FALSE;
			}

			_gOviHwO22Info.isDispOutDisabled = TRUE;
		}
		#endif

		_gOviHwO22Info.wbEn = FALSE;
		_gOviHwO22Info.wbBypassEn = FALSE;
		_gOviHwO22Info.dgaEn = FALSE;
		_gOviHwO22Info.dgaBypassEn = FALSE;
		_gOviHwO22Info.mleModeOff = FALSE;
		_gOviHwO22Info.odcBypassEn = FALSE;

		cancel_delayed_work_sync(&_gOviHwO22Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutR);
			_gOviHwO22Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutG);
			_gOviHwO22Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutB);
			_gOviHwO22Info.delayedRGBGamma.pu32LutB = NULL;
		}
		
		_gPrevRedGain = OVI_HW_O22_WB_DEFAULT_GAIN;
		_gPrevGreenGain = OVI_HW_O22_WB_DEFAULT_GAIN;
		_gPrevBlueGain = OVI_HW_O22_WB_DEFAULT_GAIN;

		_gPrevRedOffset = 0;
		_gPrevGreenOffset = 0;
		_gPrevBlueOffset = 0;

		_gOviHwO22Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		_OVI_O22_SetPempItuneData(&_gOviHwO22Info.pempItuneData);
		_OVI_O22_Set_DC_Cal(_gOviHwO22Info.dcVal);

		{	// initialize Vx1 Lock status counter
			CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
			CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r01, 0x00000030);
			CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r01);

			CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
			CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r01, 0x00000020);
			CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r01);
		}

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base)
			|| (!gpOviTconMem->size))
		{
			OVI_PRINT("o22 Do not support ODC\n");

			_gOviHwO22Info.tconBaseAddress = 0;
		}
		else
		{
			_gOviHwO22Info.tconBaseAddress = gpOviTconMem->base;

			#if 0 // not support
			OVI_TCON_O22_RdFL(tcon_base_address);
			OVI_TCON_O22_Wr(tcon_base_address, _gOviHwO22Info.tconBaseAddress);
			OVI_TCON_O22_WrFL(tcon_base_address);
			#endif
		}
	} while(0);
#if 1
	if(g_panelFrameRate == 3)
	{
		__attribute__((unused)) UINT32 regVal;

		if (RET_OK == OS_ScanKernelCmdlineToken("WirelessAV"))
		{
			OVI_PRINT("=================== Resume LCD_144Hz_wireless_model\n");
			OVI_REG_RD(0xCC432058, regVal)
			if(regVal != (0x010C7001))
			{
				OVI_REG_WR(0xC603306C, 0x000007F3); //85.86MHz wireless model

				OVI_REG_WR(0xCC43207C, 0x1A808810);
				OVI_REG_WR(0xCC432080, 0x1BDA5105);
				OVI_REG_WR(0xCC432084, 0xBF000000);
				OVI_REG_WR(0xC603306C, 0x000007FB);

				OVI_REG_WR(0xCC432058, 0x010C7001);
				OVI_REG_WR(0xCC432060, 0x00303032);
				OVI_REG_WR(0xCC43205C, 0x01A0C099);
				OVI_REG_WR(0xCC43205C, 0x0120C099);
				OVI_REG_WR(0xC603306C, 0x000007FF);

				OVI_REG_WR(0xcc460090, 0x401bda51);
			}
		}
		else
		{
			OVI_REG_RD(0xCC432058, regVal)
			if(regVal != (0x02177163))
			{
				OVI_REG_WR(0xC603306C, 0x000007F7); //84.24MHz

				OVI_REG_WR(0xCC432058, 0x02177163);
				OVI_REG_WR(0xCC43205C, 0x01A18024);
				OVI_REG_WR(0xCC432060, 0x00010042);
				OVI_REG_WR(0xCC43205C, 0x01218024); //spread spectrum setting

				OVI_REG_WR(0xC603306C, 0x000007FF);
				OVI_PRINT("OVI Resume: 144Hz pannel setting\n");
			}
			else
			{
				OVI_PRINT("OVI Resume 144Hz pannel setting skip\n");
			}
		}
	}
#endif
	return ret;
}

#define OVI_HW_O22_OPT_BIT_MASK_STB (1<<0)
int OVI_HW_O22_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams)
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
		
		OVI_PRINT("\n[OVI_HW_O22_SetDisplayOption] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
			pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
			pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
			pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
			pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

		memcpy((void *)&_gOviHwO22Info.dispOption, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

		if (!_gOviHwO22Info.dispOption.userSpecificOption.flags.SocOptionBIT31) // SocOptionBIT31 : 1 -> setDisplayOption debug mode
		{
			__attribute__((unused)) char hw_opt[32];
			
			// Forced settings by HW option(or boot option)
			if (_gOviHwO22Info.hwDispOption.frcChipType > LX_OVI_FRC_CHIP_INTERNAL)
			{
				_gOviHwO22Info.dispOption.panelInterface = LX_OVI_PANEL_VX1;
			}
			else
			{
				_gOviHwO22Info.dispOption.panelInterface = _gOviHwO22Info.hwDispOption.panelInterface;
			}

			_gOviHwO22Info.dispOption.panelFramerate = _gOviHwO22Info.hwDispOption.dispFramerate;
			_gOviHwO22Info.dispOption.panelResolution = _gOviHwO22Info.hwDispOption.dispResolution;
			if (_gOviHwO22Info.hwDispOption.isVx15Byte)
			{
				_gOviHwO22Info.dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
			}
			else
			{
				_gOviHwO22Info.dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
			}
			_gOviHwO22Info.dispOption.frcChipType = _gOviHwO22Info.hwDispOption.frcChipType;

			if (_gOviHwO22Info.hwDispOption.panelInterface == LX_OVI_PANEL_LVDS)
			{
				if ((RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
					&& (!strncmp(hw_opt,"hdmi",4)))
				{
					_gOviHwO22Info.dispOption.lvdsType = LX_OVI_LVDS_OUT_JEIDA;
				}
				else
				{
					_gOviHwO22Info.dispOption.lvdsType = LX_OVI_LVDS_OUT_VESA;
				}
			}
		}

		_OVI_O22_DispRegDataInit(&_gOviHwO22Info.dispOption);
	} while(0);

	return ret;
}

int OVI_HW_O22_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams)
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

		OVI_PRINT("\n[OVI_HW_O22_SetBypass] En[%d], Mask[0x%x]\n\r", pstParams->bEnable, pstParams->u32BlockMask);

		#if 0 // not support
		if ((pstParams->u32BlockMask & LX_OVI_TCON_BOE_RGBW)
			|| (pstParams->u32BlockMask & LX_OVI_TCON_LGD_RGBW))
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O22_RdFL(tcon_odc_opt2);
				OVI_TCON_O22_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_O22_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwO22Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_O22_RdFL(tcon_odc_opt2);
					OVI_TCON_O22_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwO22Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_O22_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwO22Info.odcBypassEn = pstParams->bEnable;
		}	
		#endif

		if (pstParams->u32BlockMask & LX_OVI_TCON_GAMMA)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O22_RdFL(tcon_control);
				OVI_TCON_O22_Wr01(tcon_control, dga_en, 0x0);
				OVI_TCON_O22_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_O22_RdFL(tcon_control);
				OVI_TCON_O22_Wr01(tcon_control, dga_en, _gOviHwO22Info.dgaEn ? 0x1 : 0x0);
				OVI_TCON_O22_WrFL(tcon_control);
			}
			_gOviHwO22Info.dgaBypassEn = pstParams->bEnable;
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_WB)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O22_RdFL(tcon_control);
				OVI_TCON_O22_Wr01(tcon_control, wb_en, 0x0);
				OVI_TCON_O22_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_O22_RdFL(tcon_control);
				OVI_TCON_O22_Wr01(tcon_control, wb_en, _gOviHwO22Info.wbEn ? 0x1 : 0x0);
				OVI_TCON_O22_WrFL(tcon_control);
			}
			_gOviHwO22Info.wbBypassEn = pstParams->bEnable;
		}

		#if 0 // not support
		if (pstParams->u32BlockMask & LX_OVI_TCON_LODC)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O22_RdFL(tcon_odc_opt2);
				OVI_TCON_O22_Wr01(tcon_odc_opt2, lodc_bypass, 0x1);
				OVI_TCON_O22_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwO22Info.lodcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_O22_RdFL(tcon_odc_opt2);
					OVI_TCON_O22_Wr01(tcon_odc_opt2, lodc_bypass, 0x0);
					OVI_TCON_O22_WrFL(tcon_odc_opt2);
				}
			}
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_ODC)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O22_RdFL(tcon_odc_opt2);
				OVI_TCON_O22_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_O22_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwO22Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_O22_RdFL(tcon_odc_opt2);
					OVI_TCON_O22_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwO22Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_O22_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwO22Info.odcBypassEn = pstParams->bEnable;
		}
		#endif
	} while(0);

	return ret;
}

int OVI_HW_O22_SetCombination(UINT32 param)
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
			for(i=0; i<_gOVIOutputModes_O22.number_of_modes;i++)
			{
				printk("  Index[%d] : %s", i,_gOVIOutputModes_O22.pOVIOutputModes[i].index);
			}
			ret = RET_OK;
			break;
		}
		else if(param >= 10000)
		{
			param = param - 10000;
			printk("\n[OVI] Compare register values regarding to register-set index[%d]", param);

			if(param > _gOVIOutputModes_O22.number_of_modes) {
				OVI_ERROR("Unknown OVI index. Index was [%d]", param);
				break;
			}

			regs  = _gOVIOutputModes_O22.pOVIOutputModes[param].regs;
			count = _gOVIOutputModes_O22.pOVIOutputModes[param].count;
			index = _gOVIOutputModes_O22.pOVIOutputModes[param].index;

			printk("\n[OVI] Register Index[%d] => %s",param, (char *)index);
			for(i=0; i<count; i++){
				if (regs[i].addr == OVI_HW_O22_REG_PARAM_OP_WAIT) continue;

				if (regs[i].addr == OVI_HW_O22_REG_PARAM_OP_CHECK)
				{
					_OVI_O22_IgnoreRegSet(regs[i].value, &ignore);
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
		else if(param > _gOVIOutputModes_O22.number_of_modes) {
			OVI_ERROR("\nUnknown OVI mode. Index was [%d]\n", param);
			break;
		}

		/* Step 2. Set mode */
		regs  = _gOVIOutputModes_O22.pOVIOutputModes[param].regs;
		count = _gOVIOutputModes_O22.pOVIOutputModes[param].count;
		index = _gOVIOutputModes_O22.pOVIOutputModes[param].index;

		printk("\n[OVI] Setting to registers to register-set-index => %s", (char *)index);
		for(i=0; i<count; i++){
			if (regs[i].addr == OVI_HW_O22_REG_PARAM_OP_WAIT)
			{
				printk("\n[%03d] Delay... %dms", i, regs[i].value/1000);
				OS_UsecDelay(regs[i].value);
			}

			if (regs[i].addr == OVI_HW_O22_REG_PARAM_OP_CHECK)
			{
				_OVI_O22_IgnoreRegSet(regs[i].value, &ignore);
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

int OVI_HW_O22_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal = 0;
#if 0 // not support
	OVI_CTOP_CTRL_FMS_DISP_AIOPLL0_O22A0_T ss_ctrl0;
	OVI_CTOP_CTRL_FMS_DISP_AIOPLL1_O22A0_T ss_ctrl1;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (_gOviHwO22Info.spreadSpectrumRegValue1 & 0x4) break; // default DSS OFF

		if(pstParams->bEnable)
		{
			if (pstParams->eSpreadRatio == 0 || pstParams->u16Period == 0)
			{
				CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO22Info.spreadSpectrumRegValue1 | 0x4);
				CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll0);

				CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll1, _gOviHwO22Info.spreadSpectrumRegValue2);
				CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll2, 0x01400000);

				CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll1);
				CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll2);

				CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO22Info.spreadSpectrumRegValue1);
				CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll0);

				OVI_REG_RD(0xC930E400, regVal);
				OVI_PRINT("Enable DSS with initial value. register val: 0x%x\n", regVal);
			}
			else
			{
				UINT32 M, NPC, NSC;
				UINT32 ACCURACY, UPDN_MAX, MOD_FREQ, RESULT_RF;

				UINT32 spread_ratio, disp_mod_freq;

				ss_ctrl0 = *gOVI_HW_O22_SS_CTRL1;
				ss_ctrl1 = *gOVI_HW_O22_SS_CTRL2;

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

				CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO22Info.spreadSpectrumRegValue1 | 0x4);
				CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll0);

				ss_ctrl0 = *gOVI_HW_O22_SS_CTRL1;
				ss_ctrl0.reg_aiopll_accuracy = ACCURACY;
				ss_ctrl0.reg_aiopll_updn_max = UPDN_MAX;
				ss_ctrl0.reg_aiopll_mod_freq_max = MOD_FREQ;
				*gOVI_HW_O22_SS_CTRL1 = ss_ctrl0;

				CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll1, _gOviHwO22Info.spreadSpectrumRegValue2);
				CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll2, 0x01400000);

				CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll1);
				CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll2);

				//CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO22Info.spreadSpectrumRegValue1);
				//CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll0);
				ss_ctrl0 = *gOVI_HW_O22_SS_CTRL1;
				ss_ctrl0.reg_aiopll_dss = 0;
				*gOVI_HW_O22_SS_CTRL1 = ss_ctrl0;

				OVI_REG_RD(0xC930E400, regVal);
				OVI_PRINT("register val: 0x%x\n", regVal);
			}
		}
		else
		{
			CTOP_CTRL_O22Ax_Wr(CTOP_FMS, disp_aiopll0, _gOviHwO22Info.spreadSpectrumRegValue1 | 0x4);
			CTOP_CTRL_O22Ax_WrFL(CTOP_FMS, disp_aiopll0);
		}
	} while(0);
#endif
	return ret;
}

int OVI_HW_O22_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) int i;
	__attribute__((unused)) volatile UINT32 *regAddr1 = NULL;
	__attribute__((unused)) UINT8 *u8odLutData = NULL;
	__attribute__((unused)) UINT32 odLutSizeNum;
	#if 0 // not support
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
				if((odLutSizeNum != OVI_HW_O22_INPUT_OD_SIZENUM && odLutSizeNum != (4*OVI_HW_O22_INPUT_OD_SIZENUM)) 
					|| pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_O22A0_BASE + offsetof(OVI_TCON_REG_O22A0_T, tcon_odc_start_2d), 
													sizeof(UINT32)*OVI_HW_O22_INPUT_OD_SIZENUM);
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
				if(odLutSizeNum != OVI_HW_O22_INPUT_LOD_SIZENUM || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_O22A0_BASE + offsetof(OVI_TCON_LODC_REG_O22A0_T, tcon_lodc_start), 
													sizeof(UINT32)*OVI_HW_O22_INPUT_LOD_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_ON)
			{
				OVI_TCON_O22_RdFL(tcon_control);
				OVI_TCON_O22_Wr01(tcon_control, odc_en, 0x1);
				OVI_TCON_O22_WrFL(tcon_control);

				OVI_TCON_O22_RdFL(tcon_sts);
				OVI_TCON_O22_Wr01(tcon_sts, pix2_lock, 0x1);
				OVI_TCON_O22_WrFL(tcon_sts);
				break;
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_OFF)
			{
				OVI_TCON_O22_RdFL(tcon_control);
				OVI_TCON_O22_Wr01(tcon_control, odc_en, 0x0);
				OVI_TCON_O22_WrFL(tcon_control);

				OVI_TCON_O22_RdFL(tcon_sts);
				OVI_TCON_O22_Wr01(tcon_sts, pix2_lock, 0x0);
				OVI_TCON_O22_WrFL(tcon_sts);
				break;
			}
			else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
			{
				// check input table size
				if(odLutSizeNum != OVI_HW_O22_INPUT_POD2_SIZENUM || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_O22A0_BASE + offsetof(OVI_TCON_CAD_REG_O22A0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_O22_INPUT_POD2_SIZENUM);
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
				//__attribute__((unused)) UINT32 regField; // block for bring-up
				//UINT32 regField2;
				UINT32 odLutDataOffsetInc = 0;

	#if 0 // block for bring-up
				OVI_WPR_O22_RdFL(wpr_reg_main);
				regField = OVI_WPR_O22_Rd(wpr_reg_main);
				regField = regField & 0x3; // check wpr_on,lgd_siw_mux
				OVI_TCON_O22_RdFL(tcon_control);
				OVI_TCON_O22_Rd01(tcon_control, hm_rgbw_en, regField2);
				regField = regField | regField2;
	#endif

				OVI_TCON_O22_RdFL(odc_lut_subpix_sel);
				OVI_TCON_O22_Wr01(odc_lut_subpix_sel, lut_rgbw_en, 0x0);
				OVI_TCON_O22_WrFL(odc_lut_subpix_sel);

				OVI_TCON_O22_RdFL(odc_lut_subpix_sel);
				OVI_TCON_O22_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x0);
				OVI_TCON_O22_WrFL(odc_lut_subpix_sel);

				if (odLutSizeNum == (4*OVI_HW_O22_INPUT_OD_SIZENUM))
				{
					odLutDataOffsetInc = OVI_HW_O22_INPUT_OD_SIZENUM;
				}

				for(i=0; i<OVI_HW_O22_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i], &regAddr1[i]);
				}

				OVI_TCON_O22_RdFL(odc_lut_subpix_sel);
				OVI_TCON_O22_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x1);
				OVI_TCON_O22_WrFL(odc_lut_subpix_sel);
				for(i=0; i<OVI_HW_O22_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i+(1*odLutDataOffsetInc)], &regAddr1[i]);
				}

				OVI_TCON_O22_RdFL(odc_lut_subpix_sel);
				OVI_TCON_O22_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x2);
				OVI_TCON_O22_WrFL(odc_lut_subpix_sel);
				for(i=0; i<OVI_HW_O22_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i+(2*odLutDataOffsetInc)], &regAddr1[i]);
				}
	#if 0 // block for bring-up
				if (regField != 0)
				{
					OVI_TCON_O22_RdFL(odc_lut_subpix_sel);
					OVI_TCON_O22_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x3);
					OVI_TCON_O22_WrFL(odc_lut_subpix_sel);
					for(i=0; i<OVI_HW_O22_INPUT_OD_SIZENUM; i++)
					{
						writel_relaxed(u8odLutData[i+(3*odLutDataOffsetInc)], &regAddr1[i]);
					}
				}
	#endif
			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
			{
				for(i=0; i<OVI_HW_O22_INPUT_POD2_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i], &regAddr1[i]);
				}
			}
			else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				for(i=0; i<OVI_HW_O22_INPUT_LOD_SIZENUM; i++)
				{
					get_user(regAddr1[i], &(((UINT32 *)pstParams->odLut.pData)[i]));
				}
			}

			if(pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				OVI_TCON_O22_RdFL(odc_lut_upload);
				OVI_TCON_O22_Wr01(odc_lut_upload, odc_upload, 0x0);
				OVI_TCON_O22_WrFL(odc_lut_upload);
				OVI_TCON_O22_RdFL(odc_lut_upload);
				OVI_TCON_O22_Wr01(odc_lut_upload, odc_upload, 0x1);
				OVI_TCON_O22_WrFL(odc_lut_upload);
			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				OVI_TCON_CAD_O22_RdFL(tcon_cad_reg_main);
				OVI_TCON_CAD_O22_Wr01(tcon_cad_reg_main, cad_on, 0x0);
				OVI_TCON_CAD_O22_WrFL(tcon_cad_reg_main);

				OVI_TCON_O22_RdFL(tcon_control);
				OVI_TCON_O22_Wr01(tcon_control, mem_sel, 0x1);
				OVI_TCON_O22_WrFL(tcon_control);

				OVI_TCON_O22_RdFL(tcon_odc_lut1_opt);
				OVI_TCON_O22_Wr01(tcon_odc_lut1_opt, lut1_add_opt, 0x0);
				OVI_TCON_O22_Wr01(tcon_odc_lut1_opt, lut1_full_opt, 0x0);
				OVI_TCON_O22_Wr01(tcon_odc_lut1_opt, lut1_zero_opt, 0x0);
				OVI_TCON_O22_Wr01(tcon_odc_lut1_opt, lut1_same_opt, 0x0);
				OVI_TCON_O22_WrFL(tcon_odc_lut1_opt);

				OVI_TCON_LODC_O22_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_O22_Wr01(lodc_lut_upload, lodc_upload, 0x0);
				OVI_TCON_LODC_O22_WrFL(lodc_lut_upload);
				OVI_TCON_LODC_O22_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_O22_Wr01(lodc_lut_upload, lodc_upload, 0x1);
				OVI_TCON_LODC_O22_WrFL(lodc_lut_upload);

				OVI_TCON_O22_RdFL(tcon_odc_opt1);
				OVI_TCON_O22_Wr01(tcon_odc_opt1, lodc_en_2d, 0x1);
				OVI_TCON_O22_Wr01(tcon_odc_opt1, lodc_en_3d, 0x0);
				OVI_TCON_O22_Wr01(tcon_odc_opt1, pcid_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_odc_opt1, pcid20_en, 0x1);
				OVI_TCON_O22_WrFL(tcon_odc_opt1);
			}
			else
			{
				__attribute__((unused)) UINT32 regField;

				//CTOP_CTRL_O22Ax_RdFL(DPE_SYN, crg_dpe00); // block for bring-up
				//CTOP_CTRL_O22Ax_Rd01(DPE_SYN, crg_dpe00, tcon_pod_clk_gate_en, regField); // block for bring-up
				OVI_REG_RD(0xC930F000,regField);
				regField = (regField & 0x200) >> 9;

				OVI_TCON_O22_RdFL(tcon_control);
				if (regField) // POD clock gating enable
				{
					// Prevention for black screen when using CEDS board
					OVI_TCON_O22_Wr01(tcon_control, mem_sel, 0x1);
				}
				else
				{
					OVI_TCON_O22_Wr01(tcon_control, mem_sel, 0x0);
				}
				OVI_TCON_O22_WrFL(tcon_control);

				OVI_TCON_CAD_O22_RdFL(tcon_cad_reg_main);
				OVI_TCON_CAD_O22_Wr01(tcon_cad_reg_main, cad_on, 0x1);
				OVI_TCON_CAD_O22_WrFL(tcon_cad_reg_main);
			}
		}
		else
		{
			if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				UINT8 buff;

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_O22A0_BASE + offsetof(OVI_TCON_REG_O22A0_T, tcon_odc_start_2d), 
													sizeof(UINT32)*OVI_HW_O22_INPUT_OD_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = OVI_HW_O22_INPUT_OD_SIZENUM;

				for (i = 0; i < OVI_HW_O22_INPUT_OD_SIZENUM; i++)
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
				regAddr2 = (volatile UINT8 *)ioremap(OVI_TCON_LODC_REG_O22A0_BASE + offsetof(OVI_TCON_LODC_REG_O22A0_T, tcon_lodc_start), 
													sizeof(UINT32)*OVI_HW_O22_INPUT_LOD_SIZENUM);
				if(regAddr2 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = sizeof(UINT32)*OVI_HW_O22_INPUT_LOD_SIZENUM;

				for (i = 0; i < sizeof(UINT32)*OVI_HW_O22_INPUT_LOD_SIZENUM; i++)
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
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_O22A0_BASE + offsetof(OVI_TCON_CAD_REG_O22A0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_O22_INPUT_POD2_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = OVI_HW_O22_INPUT_POD2_SIZENUM;

				for (i = 0; i < OVI_HW_O22_INPUT_POD2_SIZENUM; i++)
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
	#endif
	return ret;
}


int OVI_HW_O22_SetFrameOdcEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	#if 0 // not support
	do {
		// check TCON base address
		if (bParam && !(_gOviHwO22Info.tconBaseAddress))
		{
			OVI_ERROR("[OVI] TCON base address is Null!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_TCON_O22_RdFL(tcon_control);
		if(bParam)
			OVI_TCON_O22_Wr01(tcon_control, odc_en, 0x1);
		else
			OVI_TCON_O22_Wr01(tcon_control, odc_en, 0x0);
		OVI_TCON_O22_WrFL(tcon_control);
	} while (0);
	#endif
	return ret;
}

int OVI_HW_O22_SetColorTempEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_O22_RdFL(led_wb2p_en);
		if(bParam)
			DPE_LED_O22_Wr01(led_wb2p_en, wb2p_en, 0x1);
		else
			DPE_LED_O22_Wr01(led_wb2p_en, wb2p_en, 0x0);
		DPE_LED_O22_WrFL(led_wb2p_en);
	} while (0);

	return ret;
}

int OVI_HW_O22_SetGammaEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_O22_RdFL(led_dpg_en);
		if(bParam)
			DPE_LED_O22_Wr01(led_dpg_en, dpg_en, 0x1);
		else
			DPE_LED_O22_Wr01(led_dpg_en, dpg_en, 0x0);
		DPE_LED_O22_WrFL(led_dpg_en);
	} while (0);

	return ret;
}

int OVI_HW_O22_SetDitherEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O22_RdFL(tcon_control);
		if(bParam)
		{
			OVI_TCON_O22_Wr01(tcon_control, pre_dither_en, 0x1);
		}
		else
		{
			OVI_TCON_O22_Wr01(tcon_control, pre_dither_en, 0x0);
		}
		OVI_TCON_O22_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_O22_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		/* Do Nothing */
	} while(0);

	return ret;
}

int OVI_HW_O22_SetDitherMode(LX_OVI_TCON_DITHER_T enParam)
{
	int ret = RET_OK;

	do {
		//Dither Enable
		OVI_TCON_O22_RdFL(tcon_control);
		OVI_TCON_O22_Wr01(tcon_control, pre_dither_en, 0x1);
		OVI_TCON_O22_WrFL(tcon_control);
		
		OVI_TCON_O22_RdFL(tcon_dither_carry);
		switch(enParam)
		{
			case LX_OVI_TCON_DITHER_TRUNC:
				OVI_TCON_O22_Wr01(tcon_dither_carry, pre_dither_sel, 0x0);
				break;
			case LX_OVI_TCON_DITHER_ROUND:
				OVI_TCON_O22_Wr01(tcon_dither_carry, pre_dither_sel, 0x1);
				break;
			case LX_OVI_TCON_DITHER_RANDOM:
			default :
				OVI_TCON_O22_Wr01(tcon_dither_carry, pre_dither_sel, 0x2);
				break;
		}
		OVI_TCON_O22_WrFL(tcon_dither_carry);
	} while(0);

	return ret;
}

static UINT32 _OVI_O22_GetGain(UINT32 gain)
{
	UINT32 ret_gain;
	UINT32 temp;
	UINT32 rangeOpt;

	rangeOpt = (gain >> 31) & 0x1;
	gain &= (~(1 << 31));

	if ((rangeOpt == 0)
		|| ((rangeOpt == 1) && (gain >= 192)))
	{
		temp = 10000 + (gain - 192) * OVI_HW_O22_WB_GAIN_STEP1;
	}
	else
	{
		temp = 10000 + (gain - 192) * OVI_HW_O22_WB_GAIN_STEP2;
	}
	ret_gain = (temp * OVI_HW_O22_WB_DEFAULT_GAIN) / 10000;

	return ret_gain;
}

static SINT16 _OVI_O22_GetOffset(UINT32 offset)
{
	SINT16 ret_offset;

	ret_offset = ((SINT32)offset - 64) * OVI_HW_O22_WB_OFFSET_STEP;
	return ret_offset;
}

int OVI_HW_O22_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams)
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
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
			if (_gOviHwO22Info.pVx1ChipInfoVMapAddr != NULL)		
			{
				UINT32 dataSize;
				int i;
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
				BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT0_T count;
#endif
				
				r_gain = _OVI_O22_GetGain(pstParams->r_gain);
				g_gain = _OVI_O22_GetGain(pstParams->g_gain);
				b_gain = _OVI_O22_GetGain(pstParams->b_gain);

				rOffset = _OVI_O22_GetOffset(pstParams->r_offset);
				gOffset = _OVI_O22_GetOffset(pstParams->g_offset);
				bOffset = _OVI_O22_GetOffset(pstParams->b_offset);

				_gColTemp = *pstParams;

				for (i=0; i<BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
				{
					dataSize = 0;
					
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbEnRegAddr = _B2L32(OVI_HW_F22_REG_WB_EN); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbEnVal = _B2L32(0x1); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbRGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_R_GAIN); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbRGainVal = _B2L32(r_gain); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbROffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_R_OFFSET); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbROffsetVal = _B2L32(rOffset); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbGGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_G_GAIN); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbGGainVal = _B2L32(g_gain); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbGOffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_G_OFFSET); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbGOffsetVal = _B2L32(gOffset); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbBGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_B_GAIN); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbBGainVal = _B2L32(b_gain); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbBOffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_B_OFFSET); dataSize++;
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.wbBOffsetVal = _B2L32(bOffset); dataSize++;
					dataSize = sizeof(UINT32) * dataSize;

#ifndef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
#endif

					if (dataSize != OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZE)
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
					count.u32Data = _B2L32(_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data);

					if (count.colorTemp == 0xFF)
					{
						count.colorTemp = 1;
					}
					else
					{
						count.colorTemp++;
					}

					_gOviHwO22Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data = _B2L32(count.u32Data);
#else
					_gOviHwO22Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32((0x0A000000|OVI_HW_O22_VX1_CHIP_INFO_COLOR_TEMP_SIZE));
#endif

					wmb();
					_OVI_O22_UpdateChipInfoHeader();
				}
				if (ret != RET_OK) break;
			}
			else
			{
#endif
				// W/B Enable
				DPE_LED_O22_RdFL(led_wb2p_en);
				DPE_LED_O22_Wr01(led_wb2p_en, wb2p_en, 0x1);
				DPE_LED_O22_WrFL(led_wb2p_en);
			
				r_gain = _OVI_O22_GetGain(pstParams->r_gain);
				g_gain = _OVI_O22_GetGain(pstParams->g_gain);
				b_gain = _OVI_O22_GetGain(pstParams->b_gain);

				rOffset = _OVI_O22_GetOffset(pstParams->r_offset);
				gOffset = _OVI_O22_GetOffset(pstParams->g_offset);
				bOffset = _OVI_O22_GetOffset(pstParams->b_offset);

				_gColTemp = *pstParams;

				if((_gPrevRedGain == r_gain) && (_gPrevGreenGain == g_gain) && (_gPrevBlueGain == b_gain)
					&& (_gPrevRedOffset == rOffset) && (_gPrevGreenOffset == gOffset) && (_gPrevBlueOffset == bOffset))
				{
					return RET_OK;
				}

				// Set red gain
				DPE_LED_O22_RdFL(led_wb2p_r_gain);
				DPE_LED_O22_Wr(led_wb2p_r_gain, r_gain);
				DPE_LED_O22_WrFL(led_wb2p_r_gain);

				// Set red offset
				DPE_LED_O22_RdFL(led_wb2p_r_offset);
				DPE_LED_O22_Wr(led_wb2p_r_offset, rOffset);
				DPE_LED_O22_WrFL(led_wb2p_r_offset);

				// Set green gain
				DPE_LED_O22_RdFL(led_wb2p_g_gain);
				DPE_LED_O22_Wr(led_wb2p_g_gain, g_gain);
				DPE_LED_O22_WrFL(led_wb2p_g_gain);

				// Set green offset
				DPE_LED_O22_RdFL(led_wb2p_g_offset);
				DPE_LED_O22_Wr(led_wb2p_g_offset, gOffset);
				DPE_LED_O22_WrFL(led_wb2p_g_offset);

				// Set blue gain
				DPE_LED_O22_RdFL(led_wb2p_b_gain);
				DPE_LED_O22_Wr(led_wb2p_b_gain, b_gain);
				DPE_LED_O22_WrFL(led_wb2p_b_gain);

				// Set blue offset
				DPE_LED_O22_RdFL(led_wb2p_b_offset);
				DPE_LED_O22_Wr(led_wb2p_b_offset, bOffset);
				DPE_LED_O22_WrFL(led_wb2p_b_offset);

				_gPrevRedGain = r_gain;
				_gPrevGreenGain = g_gain;
				_gPrevBlueGain = b_gain;
				_gPrevRedOffset = rOffset;
				_gPrevGreenOffset = gOffset;
				_gPrevBlueOffset = bOffset;
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
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

int OVI_HW_O22_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams)
{
	int ret = RET_OK;
	UINT32 *rGammaTable = NULL;
	UINT32 *gGammaTable = NULL;
	UINT32 *bGammaTable = NULL;
	__attribute__((unused)) UINT32 regField;
	int i;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		cancel_delayed_work_sync(&_gOviHwO22Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutR != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutR);
			_gOviHwO22Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutG != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutG);
			_gOviHwO22Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO22Info.delayedRGBGamma.pu32LutB != NULL) 
		{
			vfree(_gOviHwO22Info.delayedRGBGamma.pu32LutB);
			_gOviHwO22Info.delayedRGBGamma.pu32LutB = NULL;
		}

		if (!pstParams->bIsGet)
		{
			if((pstParams->rGammaLut.sizeNum != OVI_HW_O22_GAMMA_TABLE_SIZENUM)
			|| (pstParams->gGammaLut.sizeNum != OVI_HW_O22_GAMMA_TABLE_SIZENUM)
			|| (pstParams->bGammaLut.sizeNum != OVI_HW_O22_GAMMA_TABLE_SIZENUM))
			{
				OVI_ERROR("[OVI] Gamma table size is not correct! \n");
				ret = RET_ERROR;
				break;
			}

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user((void *)rGammaTable, (void __user *)pstParams->rGammaLut.pData, OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user((void *)gGammaTable, (void __user *)pstParams->gGammaLut.pData, OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user((void *)bGammaTable, (void __user *)pstParams->bGammaLut.pData, OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
			if (_gOviHwO22Info.pVx1ChipInfoVMapAddr != NULL)
			{
				UINT32 dataSize;
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
				BE_OVI_HW_O22_VX1_CHIP_INFO_APB_CNT0_T count;
#else
				UINT32 ctrlSize;
#endif
				int idx;

				for (idx=0; idx<BE_OVI_HW_O22_VX1_CHIP_INFO_MEM_BUFF_NUM; idx++)
				{
					dataSize = 0;
#ifndef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
					ctrlSize= 0;
#endif

					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.wDataRegAddr = _B2L32(OVI_HW_F22_REG_DPG_LUT_WDATA); dataSize++;
					/* Setting Red Gamma Table */
					for (i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.wdata[i] = _B2L32(((0x4<<28)|(i<<16)|(rGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O22_GAMMA_TABLE_SIZENUM;
					/* Setting Green Gamma Table */
					for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.wdata[i+OVI_HW_O22_GAMMA_TABLE_SIZENUM] = _B2L32(((0x2<<28)|(i<<16)|(gGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O22_GAMMA_TABLE_SIZENUM;
					/* Setting Blue Gamma Table */
					for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.wdata[i+(OVI_HW_O22_GAMMA_TABLE_SIZENUM*2)] = _B2L32(((0x1<<28)|(i<<16)|(bGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O22_GAMMA_TABLE_SIZENUM;
					dataSize = sizeof(UINT32) * dataSize;

#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO_APB_SLAVE
					if (dataSize != OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZE)
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();
					
					count.u32Data = _B2L32(_gOviHwO22Info.pVx1ChipInfo[idx]->datHdr.cnt0.u32Data);
					
					if (count.dpg == 0xFF)
					{
						count.dpg = 1;
					}
					else
					{
						count.dpg++;
					}

					_gOviHwO22Info.pVx1ChipInfo[idx]->datHdr.cnt0.u32Data = _B2L32(count.u32Data);
					wmb();
#else
					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.dataHwCrc = 0xFFFFFFFF;

					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.wrDoneRegAddr = _B2L32(OVI_HW_F22_REG_DPG_LUT_WR_DONE); ctrlSize++;
					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.wrDoneVal = _B2L32(0x1); ctrlSize++;
					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.enRegAddr = _B2L32(OVI_HW_F22_REG_DPG_EN); ctrlSize++;
					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.enVal = _B2L32(0x1); ctrlSize++;
					ctrlSize = sizeof(UINT32) * ctrlSize;
					
					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.ctrlHwCrc = 0xFFFFFFFF;

					if ((dataSize != OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZE)
						|| (ctrlSize != OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZE))
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();
					
					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.dataHwHdr = _B2L32((0x0A010000|OVI_HW_O22_VX1_CHIP_INFO_DPG_DATA_SIZE));
					wmb();
					_gOviHwO22Info.pVx1ChipInfo[idx]->dpg.ctrlHwHdr = _B2L32((0x0A000000|OVI_HW_O22_VX1_CHIP_INFO_DPG_CTRL_SIZE));
					wmb();
					_OVI_O22_UpdateChipInfoHeader();
#endif
				}
				if (ret != RET_OK) break;
			}
			else
			{
#endif
				DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
				DPE_LED_O22_Rd01(led_dpg_lut_wr_done, dpg_lut_cpy_status, regField);

				if (regField)
				{
					_gOviHwO22Info.delayedRGBGamma.pu32LutR = rGammaTable;
					_gOviHwO22Info.delayedRGBGamma.pu32LutG = gGammaTable;
					_gOviHwO22Info.delayedRGBGamma.pu32LutB = bGammaTable;
					
					schedule_delayed_work(&_gOviHwO22Info.delayedRGBGamma.dlyWork, msecs_to_jiffies(10));
				}
				else
				{
					DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
					DPE_LED_O22_Wr01(led_dpg_lut_wr_done, dpg_wstart_o, 0x1);
					DPE_LED_O22_WrFL(led_dpg_lut_wr_done);

					DPE_LED_O22_RdFL(led_dpg_lut_wdata);

					/* Setting Red Gamma Table */
					for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_wdata, rGammaTable[i] & 0x7FFF);
						DPE_LED_O22_WrFL(led_dpg_lut_wdata);
					}
					/* Setting Green Gamma Table */
					for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_wdata, gGammaTable[i] & 0x7FFF);
						DPE_LED_O22_WrFL(led_dpg_lut_wdata);
					}
					/* Setting Blue Gamma Table */
					for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
					{
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
						DPE_LED_O22_Wr01(led_dpg_lut_wdata, dpg_wdata, bGammaTable[i] & 0x7FFF);
						DPE_LED_O22_WrFL(led_dpg_lut_wdata);
					}

					DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
					DPE_LED_O22_Wr01(led_dpg_lut_wr_done, dpg_wdone_o, 0x1);
					DPE_LED_O22_WrFL(led_dpg_lut_wr_done);

					DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
					DPE_LED_O22_Wr01(led_dpg_lut_wr_done, dpg_lut_update, 0x1);
					DPE_LED_O22_WrFL(led_dpg_lut_wr_done);

					// Gamma Enable
					DPE_LED_O22_RdFL(led_dpg_en);
					DPE_LED_O22_Wr01(led_dpg_en, dpg_en, 0x1);
					DPE_LED_O22_WrFL(led_dpg_en);
				}
#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
			}
#endif
		}
		else
		{

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			#if 0
			DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
			DPE_LED_O22_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_O22_WrFL(led_dpg_lut_wr_done);

			OS_UsecDelay(25000);
			#endif

			/* Setting Red Gamma Table */
			for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_O22_RdFL(led_dpg_lut_rdata);
				DPE_LED_O22_Wr01(led_dpg_lut_rdata, dpg_re, 0x4);
				DPE_LED_O22_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_O22_WrFL(led_dpg_lut_rdata);
				DPE_LED_O22_RdFL(led_dpg_lut_rdata);
				DPE_LED_O22_Rd01(led_dpg_lut_rdata, dpg_rdata, rGammaTable[i]);
			}
			/* Setting Green Gamma Table */
			for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_O22_RdFL(led_dpg_lut_rdata);
				DPE_LED_O22_Wr01(led_dpg_lut_rdata, dpg_re, 0x2);
				DPE_LED_O22_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_O22_WrFL(led_dpg_lut_rdata);
				DPE_LED_O22_RdFL(led_dpg_lut_rdata);
				DPE_LED_O22_Rd01(led_dpg_lut_rdata, dpg_rdata, gGammaTable[i]);
			}
			/* Setting Blue Gamma Table */
			for(i=0; i<OVI_HW_O22_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_O22_RdFL(led_dpg_lut_rdata);
				DPE_LED_O22_Wr01(led_dpg_lut_rdata, dpg_re, 0x1);
				DPE_LED_O22_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_O22_WrFL(led_dpg_lut_rdata);
				DPE_LED_O22_RdFL(led_dpg_lut_rdata);
				DPE_LED_O22_Rd01(led_dpg_lut_rdata, dpg_rdata, bGammaTable[i]);
			}

			#if 0
			DPE_LED_O22_RdFL(led_dpg_lut_wr_done);
			DPE_LED_O22_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_O22_WrFL(led_dpg_lut_wr_done);
			#endif

			pstParams->rGammaLut.sizeNum = OVI_HW_O22_GAMMA_TABLE_SIZENUM;
			pstParams->gGammaLut.sizeNum = OVI_HW_O22_GAMMA_TABLE_SIZENUM;
			pstParams->bGammaLut.sizeNum = OVI_HW_O22_GAMMA_TABLE_SIZENUM;

			ret = copy_to_user(pstParams->rGammaLut.pData, (void __user *)rGammaTable, OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->gGammaLut.pData, (void __user *)gGammaTable, OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->bGammaLut.pData, (void __user *)bGammaTable, OVI_HW_O22_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

		}
	} while(0);

	if((rGammaTable != NULL) && (_gOviHwO22Info.delayedRGBGamma.pu32LutR == NULL))
		vfree((const void *)rGammaTable);
	if((gGammaTable != NULL) && (_gOviHwO22Info.delayedRGBGamma.pu32LutG == NULL))
		vfree((const void *)gGammaTable);
	if((bGammaTable != NULL) && (_gOviHwO22Info.delayedRGBGamma.pu32LutB == NULL))
		vfree((const void *)bGammaTable);

	return ret;
}

int OVI_HW_O22_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 u32odcAddr=0;
	__attribute__((unused)) volatile UINT32 *pMappedAddr = NULL;
	#if 0 // not support
	do {
		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_FRAMEOD:
				u32odcAddr = OVI_TCON_REG_O22A0_BASE + offsetof(OVI_TCON_REG_O22A0_T, tcon_odc_start_2d);
				break;
			case LX_OVI_TCON_LINEOD_PCID:
				u32odcAddr = OVI_TCON_LODC_REG_O22A0_BASE + offsetof(OVI_TCON_LODC_REG_O22A0_T, tcon_lodc_start);
				break;
			default:
				break;
		}

		pstParams->odLut.sizeNum = OVI_HW_O22_INPUT_OD_SIZENUM;

		pMappedAddr = (volatile UINT32 *)ioremap(u32odcAddr, sizeof(UINT32)*OVI_HW_O22_INPUT_OD_SIZENUM);
		if(pMappedAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			break;
		}

		ret = copy_to_user((void __user *)pstParams->odLut.pData, (void*)pMappedAddr, sizeof(UINT32)*OVI_HW_O22_INPUT_OD_SIZENUM);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying to user! \n");
			ret = RET_ERROR;
			break;
		}
	}while(0);

	if(pMappedAddr != NULL)
		iounmap((void *)pMappedAddr);
	#endif
	return ret;
}

int OVI_HW_O22_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regField;
	#if 0 // not support
	do {

		if ((pstParams == NULL) || (_gOviHwO22Info.tscicWritingFlag == TRUE))
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer! or already running!\n");
			ret = RET_ERROR;
			break;
		}

		if (pstParams->u32TscicSize == 0) // TSCIC disable for debug
		{
			// [NOTE] FCIC function enable/disable : 0xC90750A8 [3:0] - 0x0/0xC
			// FCIC disable setting
			OVI_TCON_O22_RdFL(tcon_control);
			OVI_TCON_O22_Wr01(tcon_control, fcic_en, 0x0);
			OVI_TCON_O22_WrFL(tcon_control);

			// FCIC Clock gating ON
			//CTOP_CTRL_O22Ax_RdFL(DPE_SYN, crg_dpe00);
			//CTOP_CTRL_O22Ax_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 1);
			//CTOP_CTRL_O22Ax_WrFL(DPE_SYN, crg_dpe00);
			OVI_REG_RD(0xC930F000,regField);
			regField = (regField | 0x00000040);
			OVI_REG_WR(0xC930F000,regField);

			return RET_OK;
		}

		// check input table size
		if ((pstParams->u32Ctrlsize != OVI_HW_O22_INPUT_TSCIC_CTRL_SIZENUM) || (pstParams->pu8ControlTbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		if ((pstParams->u32TscicSize != OVI_HW_O22_INPUT_TSCIC_DATA_SIZE) || (pstParams->pu32TscicTbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		_gOviHwO22Info.tscicSize = pstParams->u32TscicSize;
		_gOviHwO22Info.tscicCtrlSizeNum = pstParams->u32Ctrlsize;

		_gOviHwO22Info.tscicU8CtrlData = (UINT8 *)vmalloc(_gOviHwO22Info.tscicCtrlSizeNum);
		if(_gOviHwO22Info.tscicU8CtrlData == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		ret = copy_from_user(_gOviHwO22Info.tscicU8CtrlData, (void __user *)pstParams->pu8ControlTbl, _gOviHwO22Info.tscicCtrlSizeNum);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			if(_gOviHwO22Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwO22Info.tscicU8CtrlData);
				_gOviHwO22Info.tscicU8CtrlData = NULL;
			}
			break;
		}

		_gOviHwO22Info.tscicU32Tbl = (UINT32 *)vmalloc(_gOviHwO22Info.tscicSize);
		if(_gOviHwO22Info.tscicU32Tbl == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			if(_gOviHwO22Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwO22Info.tscicU8CtrlData);
				_gOviHwO22Info.tscicU8CtrlData = NULL;
			}
			break;
		}

		ret = copy_from_user(_gOviHwO22Info.tscicU32Tbl, (void __user *)pstParams->pu32TscicTbl, _gOviHwO22Info.tscicSize);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			if(_gOviHwO22Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwO22Info.tscicU8CtrlData);
				_gOviHwO22Info.tscicU8CtrlData = NULL;
			}
			if(_gOviHwO22Info.tscicU32Tbl != NULL)
			{
				vfree(_gOviHwO22Info.tscicU32Tbl);
				_gOviHwO22Info.tscicU32Tbl = NULL;
			}
			break;
		}

		// FCIC Clock gating OFF
		//CTOP_CTRL_O22Ax_RdFL(DPE_SYN, crg_dpe00);
		//CTOP_CTRL_O22Ax_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 0);
		//CTOP_CTRL_O22Ax_WrFL(DPE_SYN, crg_dpe00);
		OVI_REG_RD(0xC930F000,regField);
		regField = (regField & 0xFFFFFFBF);
		OVI_REG_WR(0xC930F000,regField);

		// FCIC enable setting
		OVI_TCON_O22_RdFL(tcon_control);
		OVI_TCON_O22_Wr01(tcon_control, fcic_en, 0x1);
		OVI_TCON_O22_WrFL(tcon_control);

		_gOviHwO22Info.tscicThread = kthread_run(OVI_O22_TscicWriteThread, NULL, "ovi_tscic");
		if (IS_ERR(_gOviHwO22Info.tscicThread))
		{
			OVI_ERROR("[OVI] Error in starting thread! \n");
			ret = RET_ERROR;
			if(_gOviHwO22Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwO22Info.tscicU8CtrlData);
				_gOviHwO22Info.tscicU8CtrlData = NULL;
			}
			if(_gOviHwO22Info.tscicU32Tbl != NULL)
			{
				vfree(_gOviHwO22Info.tscicU32Tbl);
				_gOviHwO22Info.tscicU32Tbl = NULL;
			}
			break;
		}
	} while(0);
	#endif
	return ret;
}

int OVI_HW_O22_SetTconHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regField;

	#if 0 // not support
	do {
		#if 0
		OVI_TCON_O22_RdFL(tcon_control);
		OVI_TCON_O22_Rd01(tcon_control, epi_out, regField);
		if (!regField) break;
		
		OVI_TCON_O22_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_O22_Wr01(tcon_hor_mode, hor_reverse, _gOviHwO22Info.horReverseRegFieldValue ? 0 : 1);
		}
		else {
			OVI_TCON_O22_Wr01(tcon_hor_mode, hor_reverse, _gOviHwO22Info.horReverseRegFieldValue);
		}
		OVI_TCON_O22_WrFL(tcon_hor_mode);
		#endif

		OVI_TCON_O22_RdFL(tcon_ddiv_mode);
		OVI_TCON_O22_RdFL(tcon_ddiv_hblank);
		if(bParam) {
			OVI_TCON_O22_Wr01(tcon_ddiv_mode, rd_mode, 0x0);
			OVI_TCON_O22_Wr01(tcon_ddiv_mode, line_delay, 0x1);
			OVI_TCON_O22_Wr01(tcon_ddiv_hblank, hb_width, 0xA);
		}
		else {
			OVI_TCON_O22_Wr01(tcon_ddiv_mode, rd_mode, 0x1);
			OVI_TCON_O22_Wr01(tcon_ddiv_mode, line_delay, _gOviHwO22Info.horReverseRegFieldValue);
			OVI_TCON_O22_Wr01(tcon_ddiv_hblank, hb_width, 0x4);
		}
		OVI_TCON_O22_WrFL(tcon_ddiv_mode);
		OVI_TCON_O22_WrFL(tcon_ddiv_hblank);
	} while(0);
	#endif

	return ret;
}

int OVI_HW_O22_SetLvdsHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regField;

	do {
		#if 0
		OVI_TCON_O22_RdFL(tcon_control);
		OVI_TCON_O22_Rd01(tcon_control, epi_out, regField);
		if (regField) break;
		
		OVI_TCON_O22_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_O22_Wr01(tcon_hor_mode, hor_reverse, 0x1);
		}
		else {
			OVI_TCON_O22_Wr01(tcon_hor_mode, hor_reverse, 0x0);
		}
		OVI_TCON_O22_WrFL(tcon_hor_mode);
		#endif

		OVI_TCON_O22_RdFL(tcon_ddiv_mode);
		if(bParam) {
			OVI_TCON_O22_Wr01(tcon_ddiv_mode, rd_mode, 0x0);
			OVI_TCON_O22_Wr01(tcon_ddiv_mode, line_delay, 0x1);
		}
		else {
			OVI_TCON_O22_Wr01(tcon_ddiv_mode, rd_mode, 0x1);
			OVI_TCON_O22_Wr01(tcon_ddiv_mode, line_delay, 0x0);
		}
		OVI_TCON_O22_WrFL(tcon_ddiv_mode);

		_gOviHwO22Info.mirrorH = bParam;

	} while(0);

	return ret;
}

int OVI_HW_O22_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams)
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
		
		OVI_TCON_O22_RdFL(tcon_pgen_ctl);

		// pattern source color setting
		OVI_TCON_O22_RdFL(tcon_pgen_agpr1);
		OVI_TCON_O22_Wr(tcon_pgen_agpr1, 0x03FF);
		OVI_TCON_O22_WrFL(tcon_pgen_agpr1);

		OVI_TCON_O22_RdFL(tcon_pgen_agpg1);
		OVI_TCON_O22_Wr(tcon_pgen_agpg1, 0x03FF);
		OVI_TCON_O22_WrFL(tcon_pgen_agpg1);

		OVI_TCON_O22_RdFL(tcon_pgen_agpb1);
		OVI_TCON_O22_Wr(tcon_pgen_agpb1, 0x03FF);
		OVI_TCON_O22_WrFL(tcon_pgen_agpb1);

		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_TPG_OFF:		// pattern off
				OVI_TCON_O22_Wr(tcon_pgen_ctl, 0x0);
				_gOviHwO22Info.mute = 0;
				break;
			case LX_OVI_TCON_TPG_BLACK:		// black pattern
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x4);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				_gOviHwO22Info.mute = 1;
				break;
			case LX_OVI_TCON_TPG_WHITE:		// white pattern
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HVBAR:		// HVBar pattern
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x3);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR16GREY:		// Horizontal 16 grey pattern
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x8);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR64GREY:		// Horizontal 64 grey pattern
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x7);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR256GREY:		// Horizontal 256 grey pattern
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x6);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR1024GREY:		// Horizontal 1024 grey pattern
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x5);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_VER16GREY:		// Vertical 16 grey pattern
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0xC);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default :
				break;
		}
		OVI_TCON_O22_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_O22_SetChannelPower(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		_OVI_O22_DispOutputEnable(bParam);
	} while(0);

	return ret;
}

int OVI_HW_O22_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O22_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_LVDS_OUT_JEIDA:
				OVI_OIF_O22_Wr01(oif_lvds_config0, lvds_lsb_first, 0x0);
				break;
			case LX_OVI_LVDS_OUT_VESA:
				OVI_OIF_O22_Wr01(oif_lvds_config0, lvds_lsb_first, 0x1);
				break;
			default:
				break;
		}
		OVI_OIF_O22_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_O22_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O22_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_8BIT:
				OVI_OIF_O22_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x1);
				break;
			case LX_OVI_10BIT:
				OVI_OIF_O22_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x0);
				break;
			default:
				break;
		}
		OVI_OIF_O22_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_O22_SetLvdsBlack(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O22_RdFL(oif_lvds_config1);
		OVI_OIF_O22_RdFL(oif_lvds_config2);
		OVI_OIF_O22_RdFL(oif_vx1_config3);
		OVI_OIF_O22_RdFL(oif_vx1_config4);

		if(!bParam) // original data out
		{
			OVI_OIF_O22_Wr01(oif_lvds_config1, lvds_force_even_data, 0x0);
			OVI_OIF_O22_Wr01(oif_lvds_config2, lvds_force_odd_data, 0x0);

			OVI_OIF_O22_Wr01(oif_vx1_config3, vx1_force_even_data, 0x0);
			OVI_OIF_O22_Wr01(oif_vx1_config4, vx1_force_odd_data, 0x0);
		}
		else // black data out
		{
			OVI_OIF_O22_Wr01(oif_lvds_config1, lvds_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_O22_Wr01(oif_lvds_config2, lvds_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);

			OVI_OIF_O22_Wr01(oif_vx1_config3, vx1_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_O22_Wr01(oif_vx1_config4, vx1_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);
		}
		OVI_OIF_O22_WrFL(oif_lvds_config1);
		OVI_OIF_O22_WrFL(oif_lvds_config2);
		OVI_OIF_O22_WrFL(oif_vx1_config3);
		OVI_OIF_O22_WrFL(oif_vx1_config4);
	} while(0);

	return ret;
}

int OVI_HW_O22_SetClock(BOOLEAN bParam)
{
	int ret = RET_OK;
	#if 0 // not support
	do {
		OVI_TCON_O22_RdFL(tcon_gclk_control);
		OVI_TCON_O22_RdFL(tcon_mclk_control);

		if(bParam)
		{
			OVI_TCON_O22_Wr01(tcon_gclk_control, gclk_en, 0x1);
			OVI_TCON_O22_Wr01(tcon_mclk_control, mclk_en, 0x1);
		}
		else
		{
			OVI_TCON_O22_Wr01(tcon_gclk_control, gclk_en, 0x0);
			OVI_TCON_O22_Wr01(tcon_mclk_control, mclk_en, 0x0);
		}

		OVI_TCON_O22_WrFL(tcon_gclk_control);
		OVI_TCON_O22_WrFL(tcon_mclk_control);
	} while(0);
	#endif
	return ret;
}

int OVI_HW_O22_SetEpiDataScramble(BOOLEAN bParam)
{
	int ret = RET_OK;
	#if 0 // not support
	do {
		OVI_TCON_O22_RdFL(tcon_epi_mode);

		if(bParam)
		{
			OVI_TCON_O22_Wr01(tcon_epi_mode, scr_en, 0x1);
		}
		else
		{
			OVI_TCON_O22_Wr01(tcon_epi_mode, scr_en, 0x0);
		}

		OVI_TCON_O22_WrFL(tcon_epi_mode);
	} while(0);
	#endif
	return ret;
}

int OVI_HW_O22_SetAdvanced10bit(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		//OVI_TCON_O22_RdFL(a10_ctrl);
		OVI_TCON_O22_RdFL(tcon_odc_opt2);

		if(bParam)
		{
			//OVI_TCON_O22_Wr01(a10_ctrl, a10_on, 0x1);
			OVI_TCON_O22_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x1);
		}
		else
		{
			//OVI_TCON_O22_Wr01(a10_ctrl, a10_on, 0x0);
			OVI_TCON_O22_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x0);
		}

		//OVI_TCON_O22_WrFL(a10_ctrl);
		OVI_TCON_O22_WrFL(tcon_odc_opt2);
	} while(0);

	return ret;
}

int OVI_HW_O22_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam)
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

		if (OVI_HW_O22_INPUT_VCOM_PAT_DATA_SIZE != pstParam->sizeNum)
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

		OVI_TCON_O22_RdFL(tcon_pgen_vcomp0);
		OVI_TCON_O22_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, patData[0]);
		OVI_TCON_O22_WrFL(tcon_pgen_vcomp0);

		OVI_TCON_O22_RdFL(tcon_pgen_vcomp1);
		OVI_TCON_O22_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, patData[1]);
		OVI_TCON_O22_WrFL(tcon_pgen_vcomp1);

		OVI_TCON_O22_RdFL(tcon_pgen_vcomp2);
		OVI_TCON_O22_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, patData[2]);
		OVI_TCON_O22_WrFL(tcon_pgen_vcomp2);

		OVI_TCON_O22_RdFL(tcon_pgen_vcomp3);
		OVI_TCON_O22_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, patData[3]);
		OVI_TCON_O22_WrFL(tcon_pgen_vcomp3);

		if (level > 0)
		{
			OVI_TCON_O22_RdFL(tcon_pgen_agpr1);
			OVI_TCON_O22_Wr01(tcon_pgen_agpr1, pgen_color_r1, level);
			OVI_TCON_O22_WrFL(tcon_pgen_agpr1);

			OVI_TCON_O22_RdFL(tcon_pgen_agpg1);
			OVI_TCON_O22_Wr01(tcon_pgen_agpg1, pgen_color_g1, level);
			OVI_TCON_O22_WrFL(tcon_pgen_agpg1);

			OVI_TCON_O22_RdFL(tcon_pgen_agpb1);
			OVI_TCON_O22_Wr01(tcon_pgen_agpb1, pgen_color_b1, level);
			OVI_TCON_O22_WrFL(tcon_pgen_agpb1);
		}
	} while(0);

	if(u16vcomPatData != NULL)
		vfree(u16vcomPatData);

	return ret;
}

int OVI_HW_O22_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O22_RdFL(tcon_pgen_ctl);

		switch(enParam)
		{
			case LX_OVI_TCON_VCOM_PAT_CTRL_OFF:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x0);

				OVI_TCON_O22_RdFL(tcon_pgen_vcomp0);
				OVI_TCON_O22_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, 0x0);
				OVI_TCON_O22_WrFL(tcon_pgen_vcomp0);

				OVI_TCON_O22_RdFL(tcon_pgen_vcomp1);
				OVI_TCON_O22_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, 0x0);
				OVI_TCON_O22_WrFL(tcon_pgen_vcomp1);

				OVI_TCON_O22_RdFL(tcon_pgen_vcomp2);
				OVI_TCON_O22_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, 0x0);
				OVI_TCON_O22_WrFL(tcon_pgen_vcomp2);

				OVI_TCON_O22_RdFL(tcon_pgen_vcomp3);
				OVI_TCON_O22_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, 0x0);
				OVI_TCON_O22_WrFL(tcon_pgen_vcomp3);

				OVI_TCON_O22_RdFL(tcon_pgen_agpr1);
				OVI_TCON_O22_Wr01(tcon_pgen_agpr1, pgen_color_r1, 0x3FF);
				OVI_TCON_O22_WrFL(tcon_pgen_agpr1);

				OVI_TCON_O22_RdFL(tcon_pgen_agpg1);
				OVI_TCON_O22_Wr01(tcon_pgen_agpg1, pgen_color_g1, 0x3FF);
				OVI_TCON_O22_WrFL(tcon_pgen_agpg1);

				OVI_TCON_O22_RdFL(tcon_pgen_agpb1);
				OVI_TCON_O22_Wr01(tcon_pgen_agpb1, pgen_color_b1, 0x3FF);
				OVI_TCON_O22_WrFL(tcon_pgen_agpb1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_ON:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x1E);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM1:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x16);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM2:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x17);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM3:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x18);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM4:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x19);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM5:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x1A);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM6:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x1B);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM7:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x1C);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM8:
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_mode, 0x1D);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O22_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default:
				break;
		}

		OVI_TCON_O22_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_O22_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam)
{
	int ret = RET_OK;
	OVI_PRINT("frcChipType:%d, panelResolution:%d, panelFramerate:%d\n",_gOviHwO22Info.hwDispOption.frcChipType, _gOviHwO22Info.hwDispOption.panelResolution, _gOviHwO22Info.hwDispOption.panelFramerate);
	do {
		if ((_gOviHwO22Info.hwDispOption.frcChipType == LX_OVI_FRC_CHIP_INTERNAL)
			&& (_gOviHwO22Info.hwDispOption.panelResolution == LX_OVI_PANEL_RESOLUTION_3840X2160)
			&& (_gOviHwO22Info.hwDispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_120HZ))
		{
			switch(enParam)
			{
				case LX_OVI_DISP_OUTPUT_MODE_4K60:
					OVI_TCON_O22_RdFL(tcon_ddiv_mode);
					OVI_OIF_O22_RdFL(oif_vx1_lane_sel3);
					OVI_OIF_O22_RdFL(oif_vx1_lane_sel4);
					OVI_TCON_O22_Wr01(tcon_ddiv_mode, lane_num, 0x8);
					OVI_OIF_O22_Wr(oif_vx1_lane_sel3, 0x00010203);
					OVI_OIF_O22_Wr(oif_vx1_lane_sel4, 0x04050607);
					OVI_TCON_O22_WrFL(tcon_ddiv_mode);
					OVI_OIF_O22_WrFL(oif_vx1_lane_sel3);
					OVI_OIF_O22_WrFL(oif_vx1_lane_sel4);

					// O22 TCON clock
					OVI_REG_WR(0xCC450010, 0x00000011);
					// O22 LED clock
					OVI_REG_WR(0xCC420010, 0x00000011);
					// O22 CCO clock
					OVI_REG_WR(0xCC490010, 0x00111100);
					// O22 VSD clock
					OVI_REG_WR(0xCC470010, 0x00001120);
					break;
					
				case LX_OVI_DISP_OUTPUT_MODE_4K120:
				default:
					OVI_TCON_O22_RdFL(tcon_ddiv_mode);
					OVI_OIF_O22_RdFL(oif_vx1_lane_sel3);
					OVI_OIF_O22_RdFL(oif_vx1_lane_sel4);
					OVI_TCON_O22_Wr01(tcon_ddiv_mode, lane_num, 0x10);
					OVI_OIF_O22_Wr(oif_vx1_lane_sel3, 0x08090A0B);
					OVI_OIF_O22_Wr(oif_vx1_lane_sel4, 0x0C0D0E0F);
					OVI_TCON_O22_WrFL(tcon_ddiv_mode);
					OVI_OIF_O22_WrFL(oif_vx1_lane_sel3);
					OVI_OIF_O22_WrFL(oif_vx1_lane_sel4);

					// O22 TCON clock
					OVI_REG_WR(0xCC450010, 0x00000000);
					// O22 LED clock
					OVI_REG_WR(0xCC420010, 0x00000000);
					// O22 CCO clock
					OVI_REG_WR(0xCC490010, 0x00000000);
					// O22 VSD clock
					OVI_REG_WR(0xCC470010, 0x00000000);
					break;
			}

			_gOviHwO22Info.dispOutputMode = enParam;
		}
	} while(0);
	
	return ret;
}

int OVI_HW_O22_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams)
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
		
		if (memcmp(&_gOviHwO22Info.dispOption, pstParams, sizeof(LX_OVI_DISPLAY_INFO_T)) != 0)
		{
			OVI_PRINT("\n[OVI_HW_O22_DisplayResume] WARN:Disp Option Changed! [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
				pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
				pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
				pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
				pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);
		}
	} while(0);

	return ret;
}

static int _OVI_O22_GetPempItuneData(OVI_HW_O22_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	UINT8* u8pempData;
	UINT8* u8ituneData;
	__attribute__((unused)) UINT32 regVal = 0;
	__attribute__((unused)) int i = 0;
	__attribute__((unused)) int j = 0;

	u8pempData = pstParams->pemp;
	u8ituneData = pstParams->itune;

	do {
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r06);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r06);

		for (i = 0, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8ituneData[i] = (regVal >> j) & 0xF;
			u8ituneData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, pqe_frpll_r00);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, pqe_frpll_r00);

		for (i = 16, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8ituneData[i] = (regVal >> j) & 0xF;
			u8ituneData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r06);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r06);

		for (i = 2, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8ituneData[i] = (regVal >> j) & 0xF;
			u8ituneData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, pqe_frpll_r00);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, pqe_frpll_r00);

		for (i = 18, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8ituneData[i] = (regVal >> j) & 0xF;
			u8ituneData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r06);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r06);

		for (i = 0, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8pempData[i] = (regVal >> j) & 0x7;
			u8pempData[i+1] = (regVal >> (j+4)) & 0x7;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, pqe_frpll_r00);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, pqe_frpll_r00);

		for (i = 16, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8pempData[i] = (regVal >> j) & 0x7;
			u8pempData[i+1] = (regVal >> (j+4)) & 0x7;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r06);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r06);

		for (i = 2, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8pempData[i] = (regVal >> j) & 0x7;
			u8pempData[i+1] = (regVal >> (j+4)) & 0x7;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, pqe_frpll_r00);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, pqe_frpll_r00);

		for (i = 18, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8pempData[i] = (regVal >> j) & 0x7;
			u8pempData[i+1] = (regVal >> (j+4)) & 0x7;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

	}while(0);

	return ret;

}

static int _OVI_O22_SetPempItuneData(OVI_HW_O22_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	UINT8* u8pempData;
	UINT8* u8ituneData;

	u8pempData = pstParams->pemp;
	u8ituneData = pstParams->itune;

	do {
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[0] & 0xF) | ((u8ituneData[1] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[2] & 0xF) | ((u8ituneData[3] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[0] & 0x7) | ((u8pempData[1] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[2] & 0x7) | ((u8pempData[3] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[4] & 0xF) | ((u8ituneData[5] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[6] & 0xF) | ((u8ituneData[7] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[4] & 0x7) | ((u8pempData[5] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[6] & 0x7) | ((u8pempData[7] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[8] & 0xF) | ((u8ituneData[9] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[10] & 0xF) | ((u8ituneData[11] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[8] & 0x7) | ((u8pempData[9] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[10] & 0x7) | ((u8pempData[11] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[12] & 0xF) | ((u8ituneData[13] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[14] & 0xF) | ((u8ituneData[15] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[12] & 0x7) | ((u8pempData[13] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[14] & 0x7) | ((u8pempData[15] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[16] & 0xF) | ((u8ituneData[17] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[18] & 0xF) | ((u8ituneData[19] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[16] & 0x7) | ((u8pempData[17] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[18] & 0x7) | ((u8pempData[19] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[20] & 0xF) | ((u8ituneData[21] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8ituneData[22] & 0xF) | ((u8ituneData[23] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[20] & 0x7) | ((u8pempData[21] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8pempData[22] & 0x7) | ((u8pempData[23] << 4) & 0x70));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

	}while(0);

	return ret;

}

int OVI_HW_O22_SetPempItune(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	OVI_HW_O22_PEMP_ITUNE_DATA_T param;

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
			ret = copy_from_user(param.pemp, (void __user *)pstParams->pPemp, 24*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user(param.itune, (void __user *)pstParams->pItune, 24*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			ret = _OVI_O22_SetPempItuneData(&param);
		}
		else
		{
			ret = _OVI_O22_GetPempItuneData(&param);

			ret = copy_to_user((void __user *)pstParams->pPemp, (void*)param.pemp, 24*sizeof(UINT8));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_to_user((void __user *)pstParams->pItune, (void*)param.itune, 24*sizeof(UINT8));
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

static void _OVI_O22_Get_DC_Cal(UINT8 *data)
{
	UINT8* u8DcData;
	__attribute__((unused)) UINT32 regVal = 0;
	int i = 0;
	int j = 0;

	u8DcData = data;

	do {
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r06);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r06);

		for (i = 0, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8DcData[i] = (regVal >> j) & 0xF;
			u8DcData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, pqe_frpll_r00);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, pqe_frpll_r00);

		for (i = 16, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8DcData[i] = (regVal >> j) & 0xF;
			u8DcData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r06);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, bnd_dpe_r06);

		for (i = 2, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8DcData[i] = (regVal >> j) & 0xF;
			u8DcData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, pqe_frpll_r00);
		regVal = CTOP_CTRL_O22Ax_Rd(BND_CTRL_DPE, pqe_frpll_r00);

		for (i = 18, j = 0; i < 24 && j < 32; i= i+4, j= j+8)
		{
			u8DcData[i] = (regVal >> j) & 0xF;
			u8DcData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

	}while(0);

	return;

}

static void _OVI_O22_Set_DC_Cal(UINT8 *data)
{
	UINT8* u8DcData;

	u8DcData = data;

	do {
		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[0] & 0xF) | ((u8DcData[1] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[2] & 0xF) | ((u8DcData[3] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[4] & 0xF) | ((u8DcData[5] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[6] & 0xF) | ((u8DcData[7] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[8] & 0xF) | ((u8DcData[9] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[10] & 0xF) | ((u8DcData[11] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[12] & 0xF) | ((u8DcData[13] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[14] & 0xF) | ((u8DcData[15] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[16] & 0xF) | ((u8DcData[17] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[18] & 0xF) | ((u8DcData[19] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x8);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[20] & 0xF) | ((u8DcData[21] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_addr, 0x7);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wrdata, (u8DcData[22] & 0xF) | ((u8DcData[23] << 4) & 0xF0));
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r02, reg_c4_ext_reg_wren, 0x1);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r02);
		CTOP_CTRL_O22Ax_Wr(BND_CTRL_DPE, bnd_dpe_r02, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r02);
		OS_UsecDelay(1);

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r03);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link0_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link1_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link2_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link3_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link4_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_Wr01(BND_CTRL_DPE, bnd_dpe_r03, reg_c4_link5_ext_reg_en, 0x0);
		CTOP_CTRL_O22Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r03);
		OS_UsecDelay(1);

	}while(0);

	return;

}

int OVI_HW_O22_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
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

		*pstParams = _gOviHwO22Info.hwDispOption;
	}while(0);

	return ret;
}

int OVI_HW_O22_GetLockStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal;

	do{
		// check structure pointer
		if (pbParam == NULL)
		{
			OVI_ERROR("[OVI] parameter is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		CTOP_CTRL_O22Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
		CTOP_CTRL_O22Ax_Rd01(BND_CTRL_DPE, bnd_dpe_r01, reg_c4_vx1_lockn_main_counter, regVal);

		if (regVal == 0x0)
		{
			*pbParam = TRUE;
		}
		else
		{
			*pbParam = FALSE;
		}

	} while(0);

	return ret;
}

int OVI_HW_O22_SetPmMode(UINT32 u32Param)
{
	int ret = RET_OK;
//	OVI_PRINT(" %d (0:S_PREPARE,1:SUSPEND,2:S_COMPLETED,3:R_PREPARE,4:RESUME,5:R_COMPLETED)\n",u32Param);

	_gOviHwO22Info.pm_status = u32Param;

	switch (u32Param)
	{
		case OVI_HW_O22_PQE_PM_DEVICE_SUSPEND_PREPARE:
			_gOviHwO22Info.pm_suspend = 1;
			cancel_delayed_work_sync(&_gOviHwO22Info.delayedRGBGamma.dlyWork);
			usleep_range(20000, 20000);//20ms
			OVI_PRINT("SUSPEND_PREPARE done\n");
			break;
		case OVI_HW_O22_PQE_PM_DEVICE_SUSPEND:
			break;
		case OVI_HW_O22_PQE_PM_DEVICE_SUSPEND_COMPLETED:
			if(_gOviHwO22Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_144Hz)
			{
				OVI_REG_WR(0xC603306C, 0x000007F7); //84.24MHz
		
				OVI_REG_WR(0xCC432058, 0x02177163);
				OVI_REG_WR(0xCC43205C, 0x01A18024);
				OVI_REG_WR(0xCC432060, 0x00010042);
				OVI_REG_WR(0xCC43205C, 0x01218024); //spread spectrum setting
		
				OVI_REG_WR(0xC603306C, 0x000007FF);
			}
			//	AIOPLL_DISP 1/16 freq. down
			OVI_REG_WR(0xCC432058, 0x010C7001);
			OVI_REG_WR(0xCC43205C, 0x00A10063);
			OVI_REG_WR(0xCC432060, 0x08343032);
			OVI_PRINT("SUSPEND_COMPLETED done(%d)\n",_gOviHwO22Info.dispOption.panelFramerate);
			break;
		case OVI_HW_O22_PQE_PM_DEVICE_RESUME_PREPARE:
			// restore AIOPLL_DISP
			OVI_REG_WR(0xCC432058, 0x010f6002);
			OVI_REG_WR(0xCC43205C, 0x00a14050);
			OVI_REG_WR(0xCC432060, 0x08111042);
			_OVI_O22_DispSpreadSpectrumInit();

			if(_gOviHwO22Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_144Hz)
			{
				OVI_REG_WR(0xC603306C, 0x000007F7); //84.24MHz
		
				OVI_REG_WR(0xCC432058, 0x02177163);
				OVI_REG_WR(0xCC43205C, 0x01A18024);
				OVI_REG_WR(0xCC432060, 0x00010042);
				OVI_REG_WR(0xCC43205C, 0x01218024); //spread spectrum setting
		
				OVI_REG_WR(0xC603306C, 0x000007FF);
				OS_UsecDelay(200);
			}
			OVI_PRINT("RESUME_PREPARE done(%d)\n",_gOviHwO22Info.dispOption.panelFramerate);
			break;
		case OVI_HW_O22_PQE_PM_DEVICE_RESUME:
			break;
		case OVI_HW_O22_PQE_PM_DEVICE_RESUME_COMPLETED:
			_gOviHwO22Info.pm_suspend = 0;
			OVI_PRINT("RESUME_COMPLETED done\n");
			break;
		default:
			break;
	}

	return ret;
}

static void _OVI_O22_Draw_Pat(int num)
{
	switch (num)
	{
		case 0: // clear
			OVI_TCON_O22_RdFL(tcon_pgen_ctl);
			OVI_TCON_O22_Wr(tcon_pgen_ctl, 0x00000000);
			OVI_TCON_O22_WrFL(tcon_pgen_ctl);

			OVI_OIF_O22_RdFL(oif_vx1_config3);
			OVI_OIF_O22_Wr(oif_vx1_config3, 0x00000000);
			OVI_OIF_O22_WrFL(oif_vx1_config3);

			OVI_OIF_O22_RdFL(oif_vx1_config4);
			OVI_OIF_O22_Wr(oif_vx1_config4, 0x00000000);
			OVI_OIF_O22_WrFL(oif_vx1_config4);
			break;

		case 1: // tcon exter hvbar
			OVI_TCON_O22_RdFL(tcon_odc_opt2);
			OVI_TCON_O22_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_O22_WrFL(tcon_odc_opt2);

			OVI_TCON_O22_RdFL(tcon_pgen_ctl);
			OVI_TCON_O22_Wr(tcon_pgen_ctl, 0x00000019);
			OVI_TCON_O22_WrFL(tcon_pgen_ctl);
			break;

		case 2: // tcon exter hgradi
			OVI_TCON_O22_RdFL(tcon_odc_opt2);
			OVI_TCON_O22_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_O22_WrFL(tcon_odc_opt2);

			OVI_TCON_O22_RdFL(tcon_pgen_ctl);
			OVI_TCON_O22_Wr(tcon_pgen_ctl, 0x00000029);
			OVI_TCON_O22_WrFL(tcon_pgen_ctl);
			break;

		case 3: // tcon inter hvbar
			OVI_TCON_O22_RdFL(tcon_odc_opt2);
			OVI_TCON_O22_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_O22_WrFL(tcon_odc_opt2);

			OVI_TCON_O22_RdFL(tcon_pgen_ctl);
			OVI_TCON_O22_Wr(tcon_pgen_ctl, 0x0000001b);
			OVI_TCON_O22_WrFL(tcon_pgen_ctl);
			break;

		case 4: // tcon inter hgradi
			OVI_TCON_O22_RdFL(tcon_odc_opt2);
			OVI_TCON_O22_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_O22_WrFL(tcon_odc_opt2);

			OVI_TCON_O22_RdFL(tcon_pgen_ctl);
			OVI_TCON_O22_Wr(tcon_pgen_ctl, 0x0000002b);
			OVI_TCON_O22_WrFL(tcon_pgen_ctl);
			break;

		case 5: // pixel repl
			OVI_OIF_O22_RdFL(oif_vx1_config3);
			OVI_OIF_O22_Wr(oif_vx1_config3, 0x400003ff);
			OVI_OIF_O22_WrFL(oif_vx1_config3);

			OVI_OIF_O22_RdFL(oif_vx1_config4);
			OVI_OIF_O22_Wr(oif_vx1_config4, 0x400003ff);
			OVI_OIF_O22_WrFL(oif_vx1_config4);
			break;

		case 6: // led pat
			break;

		default:
			break;
	}
}

int OVI_HW_O22_UpdateChipInfoHeader(void)
{
	int ret = RET_OK;

	do{
		#ifdef BE_OVI_HW_O22_USE_VX1_CHIP_INFO
		_OVI_O22_UpdateChipInfoHeader();
		#endif
	} while(0);

	return ret;
}

int OVI_HW_O22_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	__attribute__((unused)) int	i;
	__attribute__((unused)) UINT32 val;

	switch(proc_id)
	{
		case OVI_HAL_PROC_ID_DETAIL_INFO:
		{
			#if 0 // not support
			OVI_TCON_O22_RdFL(tcon_base_address);
			val = OVI_TCON_O22_Rd(tcon_base_address);
			seq_printf(m, "tcon_base_addr: 0x%08x\n", val);
			#endif

			seq_printf(m, "ch_power_on_reg1: 0x%08x\n", _gOviHwO22Info.chPowerOnRegValue1 );

			for (i=0; i<_gOVIOutputModes_O22.number_of_modes; i++)
			{
				seq_printf(m, "output_mode%d: %s", i, _gOVIOutputModes_O22.pOVIOutputModes[i].index + strlen("Display settings for O22"));
			}

			OVI_OIF_O22_RdFL(oif_lvds_config0);

			OVI_OIF_O22_Rd01(oif_lvds_config0, lvds_lsb_first, val);
			seq_printf(m, "lvds.format: %s (0x%x)\n", (val)?"vesa":"jeida", val);

			OVI_OIF_O22_Rd01(oif_lvds_config0, lvds_8bit_mode, val);
			seq_printf(m, "lvds.bit: %d bit (0x%x)\n", (val)? 8:10, val);

			OVI_OIF_O22_RdFL(oif_lvds_config1);
			OVI_OIF_O22_Rd01(oif_lvds_config1, lvds_force_even_data, val);
			seq_printf(m, "lvds.black_out: %s (0x%x)\n", (val)? "black":"orignal", val);

			seq_printf(m, "\n");
			seq_printf(m, "<dispOption>\n");
			seq_printf(m, "panelBacklight    : %d (4:OLED)\n",_gOviHwO22Info.dispOption.panelBacklight);
			seq_printf(m, "panelFramerate    : %d (0:60,1:120,3:144)\n",_gOviHwO22Info.dispOption.panelFramerate);

			seq_printf(m, "\n");
			seq_printf(m, "<hwDispOption>\n");
			seq_printf(m, "isDispOutDisabled : %d\n",_gOviHwO22Info.isDispOutDisabled);
			seq_printf(m, "mirrorH           : %d\n",_gOviHwO22Info.mirrorH);
			seq_printf(m, "mirrorV           : %d\n",_gOviHwO22Info.mirrorV);
			seq_printf(m, "panelBacklight    : %d (4:OLED)\n",_gOviHwO22Info.hwDispOption.panelBacklight);
			seq_printf(m, "panelFramerate    : %d (0:60,1:120,3:144)\n",_gOviHwO22Info.hwDispOption.panelFramerate);
			seq_printf(m, "dispFramerate     : %d (0:60,1:120,3:144)\n",_gOviHwO22Info.hwDispOption.dispFramerate);
			seq_printf(m, "isVx15Byte        : %d\n",_gOviHwO22Info.hwDispOption.isVx15Byte);
			seq_printf(m, "year_option       : %d\n",_gOviHwO22Info.hwDispOption.year_option);

			seq_printf(m, "\n");
			seq_printf(m, "<info>\n");
			seq_printf(m, "mute              : %d\n",_gOviHwO22Info.mute);

			#if 0 // not support
			OVI_TCON_O22_RdFL(tcon_gclk_control);
			OVI_TCON_O22_Rd01(tcon_gclk_control, gclk_en, val);
			seq_printf(m, "tcon.gclk: %s (0x%x)\n", (val)?"on":"off", val);

			OVI_TCON_O22_RdFL(tcon_mclk_control);
			OVI_TCON_O22_Rd01(tcon_mclk_control, mclk_en, val);
			seq_printf(m, "tcon.mclk: %s (0x%x)\n", (val)?"on":"off", val);
			#endif
		}
		break;
		case OVI_HAL_PROC_ID_DISP_OUTPUT_INFO:
		{
			char *iface[LX_OVI_PANEL_INTERFACE_MAX] = {"LVDS","EPI","EPI_QSAC","Vx1","CEDS"};
			char *lockStatus[3] = {"Locked","Unlocked","Unknown"};
			//UINT32 reverseVal;
			UINT32 lockFlag;
			//__attribute__((unused)) UINT32 regVal;

			//OVI_REG_RD(0xC930F030, regVal); // dpe_syn c4tx_ctrl NEED FIX

			if (_gOviHwO22Info.dispOption.panelInterface == LX_OVI_PANEL_VX1)
			{
				BOOLEAN bLock;
				OVI_HW_O22_GetLockStatus(&bLock);
				if (bLock == TRUE)
				{
					lockFlag = 0;
				}
				else
				{
					lockFlag = 1;
				}
			}
			else
			{
				lockFlag = 2;
			}

			#if 0 // not support
			OVI_TCON_O22_RdFL(tcon_hor_mode);
			OVI_TCON_O22_Rd01(tcon_hor_mode, hor_reverse, reverseVal);
			#endif

			seq_printf(m, "vbe_lockStatus=%s\n", lockStatus[lockFlag]);
			seq_printf(m, "vbe_displayOutput=%s\n", _gOviHwO22Info.isDispOutDisabled ? "off" : "on");
			seq_printf(m, "vbe_outputFrameRate=%s\n", _gOviHwO22Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ ? "60" : "120");
			seq_printf(m, "vbe_panelInterface=%s\n", iface[_gOviHwO22Info.dispOption.panelInterface]);
			seq_printf(m, "vbe_mute=%s\n", _gOviHwO22Info.mute ? "on" : "off");
			seq_printf(m, "vbe_mirrorH=%s\n", _gOviHwO22Info.mirrorH ? "on" : "off");
			seq_printf(m, "vbe_mirrorV=%s\n", _gOviHwO22Info.mirrorV ? "on" : "off");
			if (_gOviHwO22Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ)
			{
				seq_printf(m, "vbe_outputFrameRate=60\n");
			}
			else if (_gOviHwO22Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_120HZ)
			{
				seq_printf(m, "vbe_outputFrameRate=120\n");
			}
			else
			{
				seq_printf(m, "vbe_outputFrameRate=144\n");
			}
		}
		break;
		case OVI_HAL_PROC_ID_MIRROR_VERTICAL_INFO:
		{
			_gOviHwO22Info.mirrorV = *((UINT32 *)data);
		}
		break;
		case OVI_HAL_PROC_ID_DRAW_PATTERN:
		{
			_gOviHwO22Info.patType = *((UINT32 *)data);
			_OVI_O22_Draw_Pat(0);
			_OVI_O22_Draw_Pat(_gOviHwO22Info.patType);
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
