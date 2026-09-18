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
#include "ovi_hw_o26.h"
#include "ovi_reg_def_o26.h"
#include "ovi_reg_o26.h"

#include "v4l2_vbe.h"
#include "pwm_hal.h"
#include "../be/reg/be_reg_dpe_o26.h"
#include "../be/reg/be_reg_pwm_o26.h"

//TODO:
#undef OVI_USE_CTOP_CODES_FOR_O26

//#ifdef OVI_USE_CTOP_CODES_FOR_O26
#include "../../../core/sys/sys_regs.h"
//#endif

#include "ovi_output_format_o26a0.h"

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
#include "be_cfg.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define OVI_HW_O26_PQE_PM_DEVICE_SUSPEND_PREPARE	0
//fw stall
#define OVI_HW_O26_PQE_PM_DEVICE_SUSPEND			1
//cg on
#define OVI_HW_O26_PQE_PM_DEVICE_SUSPEND_COMPLETED	2
#define OVI_HW_O26_PQE_PM_DEVICE_RESUME_PREPARE		3
//cg off
#define OVI_HW_O26_PQE_PM_DEVICE_RESUME				4
//fw restart
#define OVI_HW_O26_PQE_PM_DEVICE_RESUME_COMPLETED	5

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
#else
#define OVI_HW_O26_GAMMA_TABLE_SIZENUM 1024
#endif
#define OVI_HW_O26_INPUT_VCOM_PAT_DATA_SIZE (96)
#define OVI_HW_O26_WB_GAIN_STEP1 26	// 0.26% step per w/b gain 1
#define OVI_HW_O26_WB_GAIN_STEP2 38	// 0.38% step per w/b gain 1
#define OVI_HW_O26_WB_OFFSET_STEP 8	// 8 step per w/b offset 1
#define OVI_HW_O26_WB_DEFAULT_GAIN 16384
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
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

#define _B2L32(data) ((((UINT32)((data)&0xff000000) >> 24) & 0x000000ff) |   \
					(((UINT32)((data)&0x00ff0000) >>  8) & 0x0000ff00) |   \
					(((UINT32)((data)&0x0000ff00) <<  8) & 0x00ff0000) |   \
					(((UINT32)((data)&0x000000ff) << 24) & 0xff000000))
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


#define OVI_HW_O26_CH_POWER_REG_MASK	0x00FFFFFF

#define OVI_HW_O26_REG_PARAM_OP_WRITE		0x0
#define OVI_HW_O26_REG_PARAM_OP_WAIT		0x1
#define OVI_HW_O26_REG_PARAM_OP_CHECK		0x2
#define OVI_HW_O26_REG_PARAM_OP_RESERVED	0x3
#define OVI_HW_O26_REG_PARAM_OP_MASK		0x3

#define OVI_HW_O26_REG_SET_A0_START		0x000000A0
#define OVI_HW_O26_REG_SET_B0_START		0x000000B0
// Max Value < 0x000000A0
#define OVI_HW_O26_REG_READ_START		0x00000001
#define OVI_HW_O26_REG_CHECK_END		0x00000000

#define OVI_HW_O26_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define OVI_HW_O26_BOE_FW_SIZE 32256

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
} OVI_HW_O26_PEMP_ITUNE_DATA_T;

typedef struct {
	struct delayed_work dlyWork;
	UINT32 *pu32LutR;
	UINT32 *pu32LutG;
	UINT32 *pu32LutB;
} OVI_HW_O26_DLY_RGB_GAMMA_T;

typedef struct {
	UINT32 chPowerOnRegValue1;
	UINT32 chPowerOnRegValue2;
	UINT32 tconBaseAddress;

	UINT32 spreadSpectrumRegValue1;
	UINT32 spreadSpectrumRegValue2;
	UINT32 spreadSpectrumRegValue3;

	UINT32 oif_vx1_config0;
	UINT32 dispout_mute;

	BOOLEAN wbEn;
	BOOLEAN wbBypassEn;
	BOOLEAN dgaEn;
	BOOLEAN dgaBypassEn;
	BOOLEAN mleModeOff;
	BOOLEAN odcBypassEn;

	UINT32 horReverseRegFieldValue;	// Value for non-reverse

	LX_OVI_DISP_OUTPUT_MODE_T dispOutputMode;
	BOOLEAN isDispOutDisabled;

	UINT32 pllMuxSelRegValue;

	//UINT32 tconClkGatingRegValue;

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
	OVI_HW_O26_PEMP_ITUNE_DATA_T pempItuneData;
	UINT8 dcVal[24];
	UINT32 patType;
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
	void *pVx1ChipInfoVMapAddr;
	BE_OVI_HW_O26_VX1_CHIP_INFO_T *pVx1ChipInfo[BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM];
#endif

	OVI_HW_O26_DLY_RGB_GAMMA_T delayedRGBGamma;

	UINT32 pm_status;
	UINT32 pm_suspend;

	UINT32 vrr_on;
	UINT32 high_clk;
	UINT32 set_ss;

	UINT32 crg_hdr004_org;
	UINT32 crg_hdr004_cur;
	struct ovi_clk_ctrl clk_ctrl;
	struct mutex clk_ctrl_mutex_lock;

	char tool[16];
} OVI_HW_O26_INFO_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T *gpOviTconMem;
extern BE_LED_REG_O26_T gBE_LED_O26;
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
extern BE_FRM_MEM_CFG_T *gpBeChInfMem;
#endif
extern BE_PWM_REG_O26_T gBE_PWM_O26;

extern BE_PCC_REG_O26_T gBE_PCC_O26;
extern BE_PCC_WIN_REG_O26_T gBE_PCC_WIN_O26;
extern BE_L3D_REG_O26_T gBE_L3D_O26;
extern BE_L3D_REG_O26_T gBE_L3D_O26;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
OVI_TCON_REG_O26_T gOVI_TCON_O26;
OVI_OIF_REG_O26_T gOVI_OIF_O26;

static volatile unsigned int *gMapped_address;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static UINT32 _OVI_O26_GetGain(UINT32 gain);
static SINT16 _OVI_O26_GetOffset(UINT32 offset);
static void _OVI_O26_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore);
__attribute__((unused)) static void _OVI_O26_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);
__attribute__((unused)) static void _OVI_O26_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);

static void _OVI_O26_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams, UINT32 vrr_on, UINT32 high_clk);
static void _OVI_O26_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams, UINT32 vrr_on, UINT32 high_clk);
static void _OVI_O26_DispOutputEnable(BOOLEAN bParam);
static void _OVI_O26_GetHWDispOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);
// static void _OVI_O26_DispSpreadSpectrumInit(void);

static void _OVI_O26_CallbackDelayedGamma(struct work_struct *work);

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
static int _OVI_O26_Vx1ChipInfoMemInit(void);
static void _OVI_O26_Vx1ChipInfoMemFill(void);
static void _OVI_O26_UpdateChipInfoHeader(void);
#endif

static int _OVI_O26_GetPempItuneData(OVI_HW_O26_PEMP_ITUNE_DATA_T *pstParams);
static int _OVI_O26_SetPempItuneData(OVI_HW_O26_PEMP_ITUNE_DATA_T *pstParams);
static void _OVI_O26_Set_DC_Cal(UINT8 *data);
static void _OVI_O26_Get_DC_Cal(UINT8 *data);
static void _OVI_O26_Draw_Pat(int num);

static int _ovi_hw_o26_hdr_scrg(UINT32 vrr, UINT32 data);

/*----------------------------------------------------------------------------------------
	Internal Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _gPrevRedGain = OVI_HW_O26_WB_DEFAULT_GAIN;
static UINT32 _gPrevGreenGain = OVI_HW_O26_WB_DEFAULT_GAIN;
static UINT32 _gPrevBlueGain = OVI_HW_O26_WB_DEFAULT_GAIN;

static SINT16 _gPrevRedOffset = 0;
static SINT16 _gPrevGreenOffset = 0;
static SINT16 _gPrevBlueOffset = 0;

static LX_OVI_TCON_COLOR_TEMP_T _gColTemp;
static OVI_HW_O26_INFO_T _gOviHwO26Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
static char *_ovi_o26_str_panel_framerate(LX_OVI_PANEL_FRAMERATE_T idx)
{
	char *str[] = {"60HZ","120HZ","60HZ_FIXED","144HZ","165HZ"};
	return (idx >= 0 && idx < OVI_HW_O26_ARRAY_SIZE(str))? str[idx]:"NA";
}

static char *_ovi_o26_str_panel_interface(LX_OVI_PANEL_INTERFACE_T idx)
{
	char *str[] = {"LVDS","EPI","EPI_QSAC","VX1","CEDS"};
	return (idx >= 0 && idx < OVI_HW_O26_ARRAY_SIZE(str))? str[idx]:"NA";
}

static char *_ovi_o26_str_frc_chip_type(LX_OVI_FRC_CHIP_TYPE_T idx)
{
	char *str[] = {"NONE","INT","U9","U9P","U11","U11P","F16","U17","F20","F22","KLD"};
	return (idx >= 0 && idx < OVI_HW_O26_ARRAY_SIZE(str))? str[idx]:"NA";
}

static char *_ovi_o26_str_panel_backlight(LX_OVI_PANEL_BACKLIGHT_T idx)
{
	char *str[] = {"EDGE","ALEF","DIR_M","DIR_L","OLED","DIR_VI","DIR_SKY","NONE"};
	return (idx >= 0 && idx < OVI_HW_O26_ARRAY_SIZE(str))? str[idx]:"NA";
}

static void _OVI_O26_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore)
{
	if (regParamVal >= OVI_HW_O26_REG_SET_A0_START)
	{
		if (lx_chip_rev() >= LX_CHIP_REV(O26, B0))
		{
			if (regParamVal != OVI_HW_O26_REG_SET_B0_START)
			{
				*pbIgnore = TRUE;
			}
		}
		else
		{
			if (regParamVal != OVI_HW_O26_REG_SET_A0_START)
			{
				*pbIgnore = TRUE;
			}
		}
	}
	else if (regParamVal == OVI_HW_O26_REG_CHECK_END)
	{
		*pbIgnore = FALSE;
	}

	return;
}

__attribute__((unused)) static void _OVI_O26_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN ignore = FALSE;

	while(cnt--)
	{
		switch(param->addr & OVI_HW_O26_REG_PARAM_OP_MASK)
		{
			case OVI_HW_O26_REG_PARAM_OP_WAIT:	// wait
				if (!ignore)
				{
					OS_UsecDelay(param->value);
				}
				OVI_DEBUG("delay(_%dms);\n", param->value/1000);
				break;

			case OVI_HW_O26_REG_PARAM_OP_CHECK:	// check
				_OVI_O26_IgnoreRegSet(param->value, &ignore);
				OVI_DEBUG("ignore : %d\n", ignore);
				break;

			case OVI_HW_O26_REG_PARAM_OP_RESERVED:
				OVI_DEBUG("OVI_HW_O26_REG_PARAM_OP_RESERVED\n");
				break;

			default:	// OVI_HW_O26_REG_PARAM_OP_WRITE
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

__attribute__((unused)) static void _OVI_O26_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN readReg = FALSE;

	while(cnt--)
	{
		switch(param->addr & OVI_HW_O26_REG_PARAM_OP_MASK)
		{
			case OVI_HW_O26_REG_PARAM_OP_CHECK:	// check for register read
				if (param->value == OVI_HW_O26_REG_READ_START)
				{
					readReg = TRUE;
				}
				else if (param->value == OVI_HW_O26_REG_CHECK_END)
				{
					readReg = FALSE;
				}
				OVI_DEBUG("readReg : %d\n", readReg);
				break;

			default:	// OVI_HW_O26_REG_PARAM_OP_WRITE
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

static void _OVI_O26_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams, UINT32 vrr_on, UINT32 high_clk)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;

	if (pstParams == NULL)
	{
		OVI_ERROR("pstParams null\n");
		return;
	}

	OVI_PRINT("%d(%s)-%d-%d(%s)-%d-%d-%d-%d-%d(%s)-%d-%d(%s)-%d-%d-%d-0x%x-W:%d-Vrr,high:%d,%d\n",
		pstParams->panelInterface, _ovi_o26_str_panel_interface(pstParams->panelInterface),
		pstParams->panelResolution, pstParams->frcChipType, _ovi_o26_str_frc_chip_type(pstParams->frcChipType),
		pstParams->panelCellType, pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, _ovi_o26_str_panel_backlight(pstParams->panelBacklight),
		pstParams->panelLedBar, pstParams->panelFramerate, _ovi_o26_str_panel_framerate(pstParams->panelFramerate),
		pstParams->lvdsBit, pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all,
		_gOviHwO26Info.hwDispOption.wirelessAV,vrr_on,high_clk);

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));
	_gOviHwO26Info.vrr_on = vrr_on;
	_gOviHwO26Info.high_clk = high_clk;

	//OVI_REG_RD(0xCC432070, _gOviHwO26Info.pllMuxSelRegValue);

	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					break;
				case LX_OVI_PANEL_VX1:
				default :
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22)
					{
					}
					else if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
					}
					else
					{
					}
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_144Hz:
			if (RET_OK == OS_ScanKernelCmdlineToken("WirelessAV"))
			{
			}
			else
			{
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_165Hz:
			if (vrr_on == 1)
			{
			}
			else
			{
			}
			break;
		default :
			break;
	}

	return;
}

static void _OVI_O26_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams, UINT32 vrr_on, UINT32 high_clk)
{
	UINT32 reg_0xCC240010 = 0x00000002;// 0:core800_clk(800.0MHz), 1:din780_clk(780.0MHz), 2:core600_clk(600.0MHz)
	LX_OVI_DISPLAY_INFO_T stDispParams;
	__attribute__((unused)) char hw_opt[32];
	__attribute__((unused)) UINT32 is_G6_i55i65i77i83 = 0;

	if (pstParams == NULL)
	{
		OVI_ERROR("pstParams null\n");
		return;
	}

	if ((pstParams->panelInch == LX_OVI_PANEL_INCH_55) || (pstParams->panelInch == LX_OVI_PANEL_INCH_65) || (pstParams->panelInch == LX_OVI_PANEL_INCH_77)) {
		if (!strncmp(_gOviHwO26Info.tool,"G6",strlen("G6"))) {
			is_G6_i55i65i77i83 = 1;
		}
	}

	OVI_PRINT("%d(%s)-%d-%d(%s)-%d-%d-%d-%d-%d(%s)-%d-%d(%s)-%d-%d-%d-0x%x-W:%d-Vrr,high:%d,%d-T:%s(%d)\n",
		pstParams->panelInterface, _ovi_o26_str_panel_interface(pstParams->panelInterface),
		pstParams->panelResolution, pstParams->frcChipType, _ovi_o26_str_frc_chip_type(pstParams->frcChipType),
		pstParams->panelCellType, pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, _ovi_o26_str_panel_backlight(pstParams->panelBacklight),
		pstParams->panelLedBar, pstParams->panelFramerate, _ovi_o26_str_panel_framerate(pstParams->panelFramerate),
		pstParams->lvdsBit, pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all,
		_gOviHwO26Info.hwDispOption.wirelessAV,vrr_on,high_clk,_gOviHwO26Info.tool,is_G6_i55i65i77i83);

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					OVI_PRINT("60HZ:LVDS\n");
					break;
				case LX_OVI_PANEL_VX1:
				default :
					OVI_PRINT("60HZ:VX1\n");
					break;
			}
			// vbe_noti_chg_clk_done(594000000);
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					OVI_PRINT("120HZ:LVDS\n");
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_UD_BE_F22)
					{
						OVI_PRINT("120HZ:VX1:F22\n");
					}
					else if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						OVI_PRINT("120HZ:VX1:OLED\n");
						//FRPLL_PQE : 54.00  MHz
						//disp_clk : 594.00 MHz (S : OIF PLL)
						//din_clk : 600.00 MHz (S : CORE PLL)
						//oif_clk : 594.00 MHz (S : OIF PLL)
						//Vx1_clk : 74.25  MHz
						OVI_REG_WR(0xCCC20018, 0x00000000);//	clock source sel(imx scrg, core800)
						OVI_REG_WR(0xCC240010, 0x00000000);//	clock source sel(hdr scrg, core800)
						OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
						//FRPLL_PQE config
						OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
						OVI_REG_WR(0xCC975020, 0x1B808768);
						OVI_REG_WR(0xCC975024, 0x66666605);
						OVI_REG_WR(0xCC975028, 0xBF000000);
						OVI_REG_WR(0xCC97502C, 0x02001613);
						OVI_REG_WR(0xCC4C40B0, 0x00007E7F);

						udelay(100);
						//DISP PLL config
						OVI_REG_WR(0xCC975000, 0x000A440A);
						OVI_REG_WR(0xCC975004, 0x0C07F004);//	[3]: DSS
						OVI_REG_WR(0xCC975008, 0x00000001);
						OVI_REG_WR(0xCC975000, 0x000A4402);

						udelay(100);
						//OIF PLL config
						OVI_REG_WR(0xCC975010, 0x8042A294);//	[2]: DSS
						OVI_REG_WR(0xCC975014, 0x55020440);
						OVI_REG_WR(0xCC975018, 0x00000180);
						OVI_REG_WR(0xCC975010, 0x8042A290);//	DSS ON SSC : 0.4%/28khz

						OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
						udelay(100);

						OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
						OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp_mode disable)
						OVI_REG_WR(0xCCC20018, 0x00000002);//	clock source sel (imx scrg, core600)
						OVI_REG_WR(0xCC240010, 0x00000002);//	clock source sel (hdr scrg, core600)

						_OVI_O26_RegParamSet(ovi_o26a0_disp_4k120_vx1_16lane_5byte,
								OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k120_vx1_16lane_5byte), 0);
					}
					else
					{
						OVI_PRINT("120HZ:VX1:LCD\n");
						//FRPLL_PQE : 54.00  MHz
						//disp_clk : 594.00 MHz (S : OIF PLL)
						//din_clk : 600.00 MHz (S : CORE PLL)
						//oif_clk : 594.00 MHz (S : OIF PLL)
						//Vx1_clk : 74.25  MHz
						OVI_REG_WR(0xCCC20018, 0x00000000);//	clock source sel(imx scrg, core800)
						OVI_REG_WR(0xCC240010, 0x00000000);//	clock source sel(hdr scrg, core800)
						OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
						//FRPLL_PQE config
						OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
						OVI_REG_WR(0xCC975020, 0x1B808768);
						OVI_REG_WR(0xCC975024, 0x66666605);
						OVI_REG_WR(0xCC975028, 0xBF000000);
						OVI_REG_WR(0xCC97502C, 0x02001613);
						OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
						udelay(100);
						//DISP PLL config
						OVI_REG_WR(0xCC975000, 0x000A440A);
						OVI_REG_WR(0xCC975004, 0x0C07F004);//	[3]: DSS
						OVI_REG_WR(0xCC975008, 0x00000001);
						OVI_REG_WR(0xCC975000, 0x000A4402);
						udelay(100);
						//OIF PLL config
						OVI_REG_WR(0xCC975010, 0x8042A294);//	[2]: DSS
						OVI_REG_WR(0xCC975014, 0x55020440);
						OVI_REG_WR(0xCC975018, 0x00000180);
						OVI_REG_WR(0xCC975010, 0x8042A290);//	DSS ON SSC : 0.4%/28khz

						OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
						udelay(100);
						OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
						OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp_mode disable)
						OVI_REG_WR(0xCCC20018, 0x00000002);//	clock source sel (imx scrg, core600)
						OVI_REG_WR(0xCC240010, 0x00000002);//	clock source sel (hdr scrg, core600)

						_OVI_O26_RegParamSet(ovi_o26a0_disp_4k120_vx1_16lane,
								OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k120_vx1_16lane), 0);
					}
					break;
			}
			// vbe_noti_chg_clk_done(594000000);
			break;

		case LX_OVI_PANEL_FRAMERATE_144Hz:
			if ((RET_OK == OS_ScanKernelCmdlineToken("WirelessAV")) && (stDispParams.panelBacklight != LX_OVI_PANEL_BACKLIGHT_OLED))
			{
				OVI_PRINT("144HZ:WirelessAV\n");
				OVI_PRINT("ovi_o26a0_disp_4k144_vx1_16lane_5byte_wirelessAV setting\n");
				//vbe_noti_chg_clk_wait();
				//FRPLL_PQE : 57.24  MHz
				//disp_clk : 686.88 Mhz (s : oif pll)
				//din_clk : 686.88 MHz (s : disp pll)
				//oif_clk : 686.88 MHz (s : oif pll)
				//Vx1_clk : 85.86  MHz
				OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
				OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
				OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
				//FRPLL_PQE config
				OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
				OVI_REG_WR(0xCC975020, 0x19818748);
				OVI_REG_WR(0xCC975024, 0x62824007);
				OVI_REG_WR(0xCC975028, 0xBF000000);
				OVI_REG_WR(0xCC97502C, 0x02001911);
				OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
				udelay(100);
				//DISP PLL config
				OVI_REG_WR(0xCC975000, 0x000B440A);
				OVI_REG_WR(0xCC975004, 0x10069004);//	[3]: DSS
				OVI_REG_WR(0xCC975008, 0x00000001);
				OVI_REG_WR(0xCC975000, 0x000B4402);
				
				udelay(100);
				//OIF PLL config
				OVI_REG_WR(0xCC975010, 0xB0426314);//	[2]: DSS
				OVI_REG_WR(0xCC975014, 0x5D020440);
				OVI_REG_WR(0xCC975018, 0x00000180);
				OVI_REG_WR(0xCC975010, 0xB0426310);//	DSS ON SSC : 0.4%/28khz
				
				OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
				udelay(100);
				OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
				OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
				OVI_REG_WR(0xCCC20018, 0x00000001);//	clock source sel(imx scrg, din
				OVI_REG_WR(0xCC240010, 0x00000001);//	clock source sel(hdr scrg, din)

				_OVI_O26_RegParamSet(ovi_o26a0_disp_4k144_vx1_16lane_5byte_wirelessAV,
												OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k144_vx1_16lane_5byte_wirelessAV), 0);
				//vbe_noti_chg_clk_done(686880000);
			}
			else
			{
				if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED) //144Hz OLED panel setting
				{
					if (is_G6_i55i65i77i83 == 1)
					{
						OVI_PRINT("144HZ:normal\n");
						OVI_PRINT("ovi_o26a0_disp_4k144_vx1_16lane_5byte_55_65_77_83inch(4) setting\n");
						vbe_noti_chg_clk_wait();
						//FRPLL_PQE : 51.84  MHz
						//disp_clk : 673.92 Mhz (s : oif pll)
						//din_clk : 673.92 MHz (s : disp pll)
						//oif_clk : 673.92 MHz (s : oif pll)
						//Vx1_clk : 84.24  MHz
						OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
						OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
						OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
						//FRPLL_PQE config
						OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
						OVI_REG_WR(0xCC975020, 0x1C818768);
						OVI_REG_WR(0xCC975024, 0x18FC5007);
						OVI_REG_WR(0xCC975028, 0xBF000000);
						OVI_REG_WR(0xCC97502C, 0x02003B07);
						OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
						udelay(100);
						//DISP PLL config
						OVI_REG_WR(0xCC975000, 0x000C450A);
						OVI_REG_WR(0xCC975004, 0x1005F004);//	[3]: DSS
						OVI_REG_WR(0xCC975008, 0x00000001);
						OVI_REG_WR(0xCC975000, 0x000C4502);
						udelay(100);
						//OIF PLL config
						OVI_REG_WR(0xCC975010, 0xB0422314);//	[2]: DSS
						OVI_REG_WR(0xCC975014, 0x65020440);
						OVI_REG_WR(0xCC975018, 0x00000180);
						OVI_REG_WR(0xCC975010, 0xB0422310);//	 DSS ON SSC : 0.4%/28khz

						OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
						udelay(100);
						OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
						OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
						OVI_REG_WR(0xCCC20018, 0x00000001);//	clock s sel (imx scrg, din)
						OVI_REG_WR(0xCC240010, 0x00000001);//	clock s sel (hdr scrg, din)

						_OVI_O26_RegParamSet(ovi_o26a0_disp_4k144_vx1_16lane_5byte_55_65_77_83inch, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k144_vx1_16lane_5byte_55_65_77_83inch), 0);
						vbe_noti_chg_clk_done(673920000);
					}
					else
					{
						OVI_PRINT("144HZ:normal\n");
						OVI_PRINT("ovi_o24a0_disp_4k144_vx1_16lane_5byte(4) setting\n");
						vbe_noti_chg_clk_wait();
						//FRPLL_PQE : 51.84  MHz
						//disp_clk : 673.92 Mhz (s : oif pll)
						//din_clk : 673.92 MHz (s : disp pll)
						//oif_clk : 673.92 MHz (s : oif pll)
						//Vx1_clk : 84.24  MHz
						OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
						OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
						OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
						//FRPLL_PQE config
						OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
						OVI_REG_WR(0xCC975020, 0x1C818768);
						OVI_REG_WR(0xCC975024, 0x18FC5007);
						OVI_REG_WR(0xCC975028, 0xBF000000);
						OVI_REG_WR(0xCC97502C, 0x02003B07);
						OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
						udelay(100);
						//DISP PLL config
						OVI_REG_WR(0xCC975000, 0x000C450A);
						OVI_REG_WR(0xCC975004, 0x1005F004);//	[3]: DSS
						OVI_REG_WR(0xCC975008, 0x00000001);
						OVI_REG_WR(0xCC975000, 0x000C4502);
						udelay(100);
						//OIF PLL config
						OVI_REG_WR(0xCC975010, 0xB0422314);//	[2]: DSS
						OVI_REG_WR(0xCC975014, 0x65020440);
						OVI_REG_WR(0xCC975018, 0x00000180);
						OVI_REG_WR(0xCC975010, 0xB0422310);//	 DSS ON SSC : 0.4%/28khz

						OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
						udelay(100);
						OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
						OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
						OVI_REG_WR(0xCCC20018, 0x00000001);//	clock s sel (imx scrg, din)
						OVI_REG_WR(0xCC240010, 0x00000001);//	clock s sel (hdr scrg, din)

						_OVI_O26_RegParamSet(ovi_o26a0_disp_4k144_vx1_16lane_5byte, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k144_vx1_16lane_5byte), 0);
						vbe_noti_chg_clk_done(673920000);
					}
				}
				else
				{
					OVI_PRINT("144HZ:LCD setting\n");
					vbe_noti_chg_clk_wait();
					//OVI_PRINT("ovi_o26a0_disp_4k144_vx1_16lane_5byte_wirelessAV setting\n");
					//FRPLL_PQE : 57.24  MHz
					//disp_clk : 686.88 Mhz (s : oif pll)
					//din_clk : 686.88 MHz (s : disp pll)
					//oif_clk : 686.88 MHz (s : oif pll)
					//Vx1_clk : 85.86  MHz
					OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
					OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
					OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
					//FRPLL_PQE config
					OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
					OVI_REG_WR(0xCC975020, 0x19818748);
					OVI_REG_WR(0xCC975024, 0x62824007);
					OVI_REG_WR(0xCC975028, 0xBF000000);
					OVI_REG_WR(0xCC97502C, 0x02001911);
					OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
					udelay(100);
					//DISP PLL config
					OVI_REG_WR(0xCC975000, 0x000B440A);
					OVI_REG_WR(0xCC975004, 0x10069004);//	[3]: DSS
					OVI_REG_WR(0xCC975008, 0x00000001);
					OVI_REG_WR(0xCC975000, 0x000B4402);

					udelay(100);
					//OIF PLL config
					OVI_REG_WR(0xCC975010, 0xB0426314);//	[2]: DSS
					OVI_REG_WR(0xCC975014, 0x5D020440);
					OVI_REG_WR(0xCC975018, 0x00000180);
					OVI_REG_WR(0xCC975010, 0xB0426310);//	DSS ON SSC : 0.4%/28khz

					OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
					udelay(100);
					OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
					OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
					OVI_REG_WR(0xCCC20018, 0x00000001);//	clock source sel(imx scrg, din
					OVI_REG_WR(0xCC240010, 0x00000001);//	clock source sel(hdr scrg, din)

					_OVI_O26_RegParamSet(ovi_o26a0_disp_4k144_vx1_16lane_5byte_wirelessAV,
													OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k144_vx1_16lane_5byte_wirelessAV), 0);
					vbe_noti_chg_clk_done(686880000);
				}
			}
			reg_0xCC240010 = 0x00000001;
			break;

		case LX_OVI_PANEL_FRAMERATE_165Hz:
			if (vrr_on == 1)
			{
				_gOviHwO26Info.vrr_on = vrr_on;
				if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
				{
					if (is_G6_i55i65i77i83 == 1)
					{
						if (RET_OK != OS_ScanKernelCmdlineToken("maxBitRate13bit")) //V26 vrr 11bit setting
						{
							OVI_PRINT("ovi_o24a0_disp_4k165_vx1_16lane_4byte_5_1_vrr 55/65/77/83inch setting\n");
							vbe_noti_chg_clk_wait();
							//FRPLL_PQE : 23.928960  MHz
							//disp_clk : 735.815520 MHz (s : DISP PLL)
							//din_clk : 800.000000	MHz (s: CORE PLL
							//oif_clk : 759.744480	MHz (s : OIF PLL)
							//Vx1_clk : 94.968060 MHz
							OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
							OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
							OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
							//FRPLL_PQE config
							OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
							OVI_REG_WR(0xCC975020, 0x410187C8);
							OVI_REG_WR(0xCC975024, 0x371DA307);
							OVI_REG_WR(0xCC975028, 0xBF000000);
							OVI_REG_WR(0xCC97502C, 0x02003B07);
							OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
							udelay(100);
							//DISP PLL config
							OVI_REG_WR(0xCC975004, 0x24013004);//	[3]: DSS
							OVI_REG_WR(0xCC975008, 0x00000001);
							OVI_REG_WR(0xCC975000, 0x001D7D09);
							udelay(100);
							//OIF PLL config
							OVI_REG_WR(0xCC975010, 0x7021740C);//	[2]: DSS
							OVI_REG_WR(0xCC975014, 0x79C20440);
							OVI_REG_WR(0xCC975018, 0x00000180);
							OVI_REG_WR(0xCC975010, 0x70217408);//	DSS ON SSC : 0.4%/28khz
							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);
							udelay(100);

							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
							udelay(100);
							OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
			//				OVI_REG_WR(0xCC975060, 0x00000000);//	clock mux sel(disp)
							OVI_REG_WR(0xCC970008, 0x00000001);//	clock source sel(edp mcrg, edp_mode disable)

							_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr_55_65_77_83inch, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr_55_65_77_83inch), 0);
							vbe_noti_chg_clk_done(735815520);

							reg_0xCC240010 = 0x00000000;
						}
						else //V26 vrr 13bit setting
						{
							OVI_PRINT("ovi_o24a0_disp_4k165_vx1_16lane_4byte_5_1_vrr 55/65/77/83inch setting\n");
							vbe_noti_chg_clk_wait();
							//FRPLL_PQE : 23.928960  MHz
							//disp_clk : 735.815520 MHz (s : DISP PLL)
							//din_clk : 800.000000	MHz (s: CORE PLL
							//oif_clk : 759.744480	MHz (s : OIF PLL)
							//Vx1_clk : 94.968060 MHz
							OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
							OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
							OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
							//FRPLL_PQE config
							OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
							OVI_REG_WR(0xCC975020, 0x410187C8);
							OVI_REG_WR(0xCC975024, 0x371DA307);
							OVI_REG_WR(0xCC975028, 0xBF000000);
							OVI_REG_WR(0xCC97502C, 0x02003B07);
							OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
							udelay(100);
							//DISP PLL config
							OVI_REG_WR(0xCC975004, 0x24013004);//	[3]: DSS
							OVI_REG_WR(0xCC975008, 0x00000001);
							OVI_REG_WR(0xCC975000, 0x001D7D09);
							udelay(100);
							//OIF PLL config
							OVI_REG_WR(0xCC975010, 0x7021740C);//	[2]: DSS
							OVI_REG_WR(0xCC975014, 0x79C20440);
							OVI_REG_WR(0xCC975018, 0x00000180);
							OVI_REG_WR(0xCC975010, 0x70217408);//	DSS ON SSC : 0.4%/28khz
							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);
							udelay(100);

							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
							udelay(100);
							OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
			//				OVI_REG_WR(0xCC975060, 0x00000000);//	clock mux sel(disp)
							OVI_REG_WR(0xCC970008, 0x00000001);//	clock source sel(edp mcrg, edp_mode disable)

							_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr_55_65_77_83inch, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr_55_65_77_83inch), 0);
							vbe_noti_chg_clk_done(735815520);

							reg_0xCC240010 = 0x00000000;
						}
					}
					else
					{
						if (RET_OK != OS_ScanKernelCmdlineToken("maxBitRate13bit")) //V26 vrr 11bit setting
						{
							OVI_PRINT("ovi_o24a0_disp_4k165_vx1_16lane_4byte_5_1_vrr setting\n");
							vbe_noti_chg_clk_wait();
							//FRPLL_PQE : 23.928960  MHz
							//disp_clk : 735.815520 MHz (s : DISP PLL)
							//din_clk : 800.000000	MHz (s: CORE PLL
							//oif_clk : 759.744480	MHz (s : OIF PLL)
							//Vx1_clk : 94.968060 MHz
							OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
							OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
							OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
							//FRPLL_PQE config
							OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
							OVI_REG_WR(0xCC975020, 0x410187C8);
							OVI_REG_WR(0xCC975024, 0x371DA307);
							OVI_REG_WR(0xCC975028, 0xBF000000);
							OVI_REG_WR(0xCC97502C, 0x02003B07);
							OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
							udelay(100);
							//DISP PLL config
							OVI_REG_WR(0xCC975004, 0x24013004);//	[3]: DSS
							OVI_REG_WR(0xCC975008, 0x00000001);
							OVI_REG_WR(0xCC975000, 0x001D7D09);
							udelay(100);
							//OIF PLL config
							OVI_REG_WR(0xCC975010, 0x7021740C);//	[2]: DSS
							OVI_REG_WR(0xCC975014, 0x79C20440);
							OVI_REG_WR(0xCC975018, 0x00000180);
							OVI_REG_WR(0xCC975010, 0x70217408);//	DSS ON SSC : 0.4%/28khz
							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);
							udelay(100);

							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
							udelay(100);
							OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
			//				OVI_REG_WR(0xCC975060, 0x00000000);//	clock mux sel(disp)
							OVI_REG_WR(0xCC970008, 0x00000001);//	clock source sel(edp mcrg, edp_mode disable)

							_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr), 0);
							vbe_noti_chg_clk_done(735815520);

							reg_0xCC240010 = 0x00000000;
						}
						else //V26 vrr 13bit setting
						{
							OVI_PRINT("ovi_o24a0_disp_4k165_vx1_16lane_4byte_5_1_vrr setting\n");
							vbe_noti_chg_clk_wait();
							//FRPLL_PQE : 23.928960  MHz
							//disp_clk : 735.815520 MHz (s : DISP PLL)
							//din_clk : 800.000000	MHz (s: CORE PLL
							//oif_clk : 759.744480	MHz (s : OIF PLL)
							//Vx1_clk : 94.968060 MHz
							OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
							OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
							OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
							//FRPLL_PQE config
							OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
							OVI_REG_WR(0xCC975020, 0x410187C8);
							OVI_REG_WR(0xCC975024, 0x371DA307);
							OVI_REG_WR(0xCC975028, 0xBF000000);
							OVI_REG_WR(0xCC97502C, 0x02003B07);
							OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
							udelay(100);
							//DISP PLL config
							OVI_REG_WR(0xCC975004, 0x24013004);//	[3]: DSS
							OVI_REG_WR(0xCC975008, 0x00000001);
							OVI_REG_WR(0xCC975000, 0x001D7D09);
							udelay(100);
							//OIF PLL config
							OVI_REG_WR(0xCC975010, 0x7021740C);//	[2]: DSS
							OVI_REG_WR(0xCC975014, 0x79C20440);
							OVI_REG_WR(0xCC975018, 0x00000180);
							OVI_REG_WR(0xCC975010, 0x70217408);//	DSS ON SSC : 0.4%/28khz
							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);
							udelay(100);

							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
							udelay(100);
							OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
			//				OVI_REG_WR(0xCC975060, 0x00000000);//	clock mux sel(disp)
							OVI_REG_WR(0xCC970008, 0x00000001);//	clock source sel(edp mcrg, edp_mode disable)

							_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr), 0);
							vbe_noti_chg_clk_done(735815520);

							reg_0xCC240010 = 0x00000000;
						}
					}
				}
				else
				{
					OVI_PRINT("165Hz LCD panel vrr setting\n");
				}
			}
			else if (high_clk == 1)
			{
				OVI_PRINT("ovi_o24a0_disp_4k165_vx1_16lane_4byte(8-1) motion Boost setting\n");
				vbe_noti_chg_clk_wait();
				//FRPLL_PQE : 48.26  MHz
				//disp_clk : 772.16 MHz (s : OIF PLL)
				//din_clk : 800.000000  MHz (s: CORE PLL)
				//oif_clk : 772.16  MHz (s : OIF PLL)
				//Vx1_clk : 96.52 MHz
				OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
				OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
				OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
				//FRPLL_PQE config
				OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
				OVI_REG_WR(0xCC975020, 0x210187E0);
				OVI_REG_WR(0xCC975024, 0xB404EA07);
				OVI_REG_WR(0xCC975028, 0xBF000000);
				OVI_REG_WR(0xCC97502C, 0x02006204);
				OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
				udelay(100);
				//DISP PLL config
				OVI_REG_WR(0xCC975000, 0x000F470A);
				OVI_REG_WR(0xCC975004, 0x1005E004);//	[3]: DSS
				OVI_REG_WR(0xCC975008, 0x00000001);
				OVI_REG_WR(0xCC975000, 0x000F4702);
				udelay(100);
				//OIF PLL config
				OVI_REG_WR(0xCC975010, 0xF041840C);//	[2]: DSS
				OVI_REG_WR(0xCC975014, 0x7D020440);
				OVI_REG_WR(0xCC975018, 0x00000180);
				OVI_REG_WR(0xCC975010, 0xF0418408);//	 DSS ON SSC : 0.4%/28khz

				OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
				udelay(100);
				OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
				OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)

				_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte_motion_boost, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte_motion_boost), 0);
				vbe_noti_chg_clk_done(772160000);

				reg_0xCC240010 = 0x00000000;
			}
			else
			{
				if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
				{
					if (is_G6_i55i65i77i83 == 1)
					{
						if (RET_OK != OS_ScanKernelCmdlineToken("maxBitRate13bit"))
						{
							OVI_PRINT("ovi_o24a0_disp_4k165_vx1_16lane_4byte(5) 11bit 55/65/77/83inch setting\n");
							vbe_noti_chg_clk_wait();
							//FRPLL_PQE : 51.84  MHz
							//disp_clk : 673.92 Mhz (s : oif pll)
							//din_clk : 673.92 MHz (s : disp pll)
							//oif_clk : 673.92 MHz (s : oif pll)
							//Vx1_clk : 84.24  MHz
							OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
							OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
							OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
							//FRPLL_PQE config
							OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
							OVI_REG_WR(0xCC975020, 0x1C818768);
							OVI_REG_WR(0xCC975024, 0x18FC5007);
							OVI_REG_WR(0xCC975028, 0xBF000000);
							OVI_REG_WR(0xCC97502C, 0x02003B07);
							OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
							udelay(100);
							//DISP PLL config
							OVI_REG_WR(0xCC975000, 0x000C450A);
							OVI_REG_WR(0xCC975004, 0x1005F004);//	[3]: DSS
							OVI_REG_WR(0xCC975008, 0x00000001);
							OVI_REG_WR(0xCC975000, 0x000C4502);
							udelay(100);
							//OIF PLL config
							OVI_REG_WR(0xCC975010, 0xB0422314);//	[2]: DSS
							OVI_REG_WR(0xCC975014, 0x65020440);
							OVI_REG_WR(0xCC975018, 0x00000180);
							OVI_REG_WR(0xCC975010, 0xB0422310);//	 DSS ON SSC : 0.4%/28khz

							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
							udelay(100);
							OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
							OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
							OVI_REG_WR(0xCCC20018, 0x00000001);//	clock s sel (imx scrg, din)
							OVI_REG_WR(0xCC240010, 0x00000001);//	clock s sel (hdr scrg, din)

							_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte_55_65_77_83inch, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte_55_65_77_83inch), 0);
							vbe_noti_chg_clk_done(673920000);

							reg_0xCC240010 = 0x00000001;
						}
						else //V26 13bit setting
						{
							OVI_PRINT("ovi_o24a0_disp_4k165_vx1_16lane_4byte(6) 13bit 55/65/77/83inch setting\n");
							vbe_noti_chg_clk_wait();
							//FRPLL_PQE : 51.84  MHz
							//disp_clk : 673.92 Mhz (s : oif pll)
							//din_clk : 673.92 MHz (s : disp pll)
							//oif_clk : 673.92 MHz (s : oif pll)
							//Vx1_clk : 84.24  MHz
							OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
							OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
							OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
							//FRPLL_PQE config
							OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
							OVI_REG_WR(0xCC975020, 0x1C818768);
							OVI_REG_WR(0xCC975024, 0x18FC5007);
							OVI_REG_WR(0xCC975028, 0xBF000000);
							OVI_REG_WR(0xCC97502C, 0x02003B07);
							OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
							udelay(100);
							OVI_REG_WR(0xCC975000, 0x000C450A);//	//DISP PLL config
							OVI_REG_WR(0xCC975004, 0x1005F004);//	[3]: DSS
							OVI_REG_WR(0xCC975008, 0x00000001);
							OVI_REG_WR(0xCC975000, 0x000C4502);//	DISPLL SS 0.5%
							udelay(100);
							//OIF PLL config
							OVI_REG_WR(0xCC975010, 0xB0422314);//	[2]: DSS
							OVI_REG_WR(0xCC975014, 0x65020440);
							OVI_REG_WR(0xCC975018, 0x00000180);
							OVI_REG_WR(0xCC975010, 0xB0422310);//	 DSS ON SSC : 0.4%/28khz

							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
							udelay(100);
							OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
							OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
							OVI_REG_WR(0xCCC20018, 0x00000001);//	clock s sel (imx scrg, din)
							OVI_REG_WR(0xCC240010, 0x00000001);//	clock s sel (hdr scrg, din)

							_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit_55_65_77_83inch, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit_55_65_77_83inch), 0);
							vbe_noti_chg_clk_done(673920000);

							reg_0xCC240010 = 0x00000001;
						}
					}
					else
					{
						if (RET_OK != OS_ScanKernelCmdlineToken("maxBitRate13bit"))
						{
							OVI_PRINT("ovi_o24a0_disp_4k165_vx1_16lane_4byte(5) 11bit setting\n");
							vbe_noti_chg_clk_wait();
							//FRPLL_PQE : 51.84  MHz
							//disp_clk : 673.92 Mhz (s : oif pll)
							//din_clk : 673.92 MHz (s : disp pll)
							//oif_clk : 673.92 MHz (s : oif pll)
							//Vx1_clk : 84.24  MHz
							OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
							OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
							OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
							//FRPLL_PQE config
							OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
							OVI_REG_WR(0xCC975020, 0x1C818768);
							OVI_REG_WR(0xCC975024, 0x18FC5007);
							OVI_REG_WR(0xCC975028, 0xBF000000);
							OVI_REG_WR(0xCC97502C, 0x02003B07);
							OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
							udelay(100);
							//DISP PLL config
							OVI_REG_WR(0xCC975000, 0x000C450A);
							OVI_REG_WR(0xCC975004, 0x1005F004);//	[3]: DSS
							OVI_REG_WR(0xCC975008, 0x00000001);
							OVI_REG_WR(0xCC975000, 0x000C4502);
							udelay(100);
							//OIF PLL config
							OVI_REG_WR(0xCC975010, 0xB0422314);//	[2]: DSS
							OVI_REG_WR(0xCC975014, 0x65020440);
							OVI_REG_WR(0xCC975018, 0x00000180);
							OVI_REG_WR(0xCC975010, 0xB0422310);//	 DSS ON SSC : 0.4%/28khz

							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
							udelay(100);
							OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
							OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
							OVI_REG_WR(0xCCC20018, 0x00000001);//	clock s sel (imx scrg, din)
							OVI_REG_WR(0xCC240010, 0x00000001);//	clock s sel (hdr scrg, din)

							_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte), 0);
							vbe_noti_chg_clk_done(673920000);

							reg_0xCC240010 = 0x00000001;
						}
						else //V26 13bit setting
						{
							OVI_PRINT("ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit(6) 13bit setting\n");
							vbe_noti_chg_clk_wait();
							//FRPLL_PQE : 51.84  MHz
							//disp_clk : 673.92 Mhz (s : oif pll)
							//din_clk : 673.92 MHz (s : disp pll)
							//oif_clk : 673.92 MHz (s : oif pll)
							//Vx1_clk : 84.24  MHz
							OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
							OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
							OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
							//FRPLL_PQE config
							OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
							OVI_REG_WR(0xCC975020, 0x1C818768);
							OVI_REG_WR(0xCC975024, 0x18FC5007);
							OVI_REG_WR(0xCC975028, 0xBF000000);
							OVI_REG_WR(0xCC97502C, 0x02003B07);
							OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
							udelay(100);
							OVI_REG_WR(0xCC975000, 0x000C450A);//	//DISP PLL config
							OVI_REG_WR(0xCC975004, 0x1005F004);//	[3]: DSS
							OVI_REG_WR(0xCC975008, 0x00000001);
							OVI_REG_WR(0xCC975000, 0x000C4502);//	DISPLL SS 0.5%
							udelay(100);
							//OIF PLL config
							OVI_REG_WR(0xCC975010, 0xB0422314);//	[2]: DSS
							OVI_REG_WR(0xCC975014, 0x65020440);
							OVI_REG_WR(0xCC975018, 0x00000180);
							OVI_REG_WR(0xCC975010, 0xB0422310);//	 DSS ON SSC : 0.4%/28khz

							OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
							udelay(100);
							OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
							OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
							OVI_REG_WR(0xCCC20018, 0x00000001);//	clock s sel (imx scrg, din)
							OVI_REG_WR(0xCC240010, 0x00000001);//	clock s sel (hdr scrg, din)

							_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit, OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit), 0);
							vbe_noti_chg_clk_done(673920000);

							reg_0xCC240010 = 0x00000001;
						}
					}
				}
				else
				{
					OVI_PRINT("4k165_120_16lane_LCD_4byte_KLD_8 setting\n");
					vbe_noti_chg_clk_wait();
					//OVI_PRINT("ovi_o26a0_disp_4k165_120_16lane_LCD_4byte_KLD_8 setting\n");
					//FRPLL_PQE : 57.24  MHz
					//disp_clk : 686.88 Mhz (s : oif pll)
					//din_clk : 686.88 MHz (s : disp pll)
					//oif_clk : 686.88 MHz (s : oif pll)
					//Vx1_clk : 85.86  MHz
					OVI_REG_WR(0xCCC20018, 0x00000000);//	clock s sel(imx scrg, core800)
					OVI_REG_WR(0xCC240010, 0x00000000);//	clock s sel(hdr scrg, core800)
					OVI_REG_WR(0xCC975060, 0x00000003);//	clock mux sel(oif/disp)
					//FRPLL_PQE config
					OVI_REG_WR(0xCC4C40B0, 0x00007C7F);//	power down(oif/disp/din)
					OVI_REG_WR(0xCC975020, 0x19818748);
					OVI_REG_WR(0xCC975024, 0x62824007);
					OVI_REG_WR(0xCC975028, 0xBF000000);
					OVI_REG_WR(0xCC97502C, 0x02001911);
					OVI_REG_WR(0xCC4C40B0, 0x00007E7F);
					udelay(100);
					//DISP PLL config
					OVI_REG_WR(0xCC975000, 0x000B440A);
					OVI_REG_WR(0xCC975004, 0x10069004);//	[3]: DSS
					OVI_REG_WR(0xCC975008, 0x00000001);
					OVI_REG_WR(0xCC975000, 0x000B4402);

					udelay(100);
					//OIF PLL config
					OVI_REG_WR(0xCC975010, 0xB0426314);//	[2]: DSS
					OVI_REG_WR(0xCC975014, 0x5D020440);
					OVI_REG_WR(0xCC975018, 0x00000180);
					OVI_REG_WR(0xCC975010, 0xB0426310);//	DSS ON SSC : 0.4%/28khz

					OVI_REG_WR(0xCC4C40B0, 0x00007FFF);//	power on
					udelay(100);
					OVI_REG_WR(0xCC975060, 0x00000001);//	clock mux sel(oif)
					OVI_REG_WR(0xCC970008, 0x00000001);//	clock s sel(edp mcrg, edp x)
					OVI_REG_WR(0xCCC20018, 0x00000001);//	clock source sel(imx scrg, din
					OVI_REG_WR(0xCC240010, 0x00000001);//	clock source sel(hdr scrg, din)

					_OVI_O26_RegParamSet(ovi_o26a0_disp_4k165_120_16lane_LCD_4byte_KLD_8,
													OVI_HW_O26_ARRAY_SIZE(ovi_o26a0_disp_4k165_120_16lane_LCD_4byte_KLD_8), 0);
					vbe_noti_chg_clk_done(686880000);
					reg_0xCC240010 = 0x00000001;
				}
			}
			break;
		default :
			break;
	}

	_ovi_hw_o26_hdr_scrg(vrr_on,reg_0xCC240010);

	OVI_PRINT("done\n");
	return;
}

static void _OVI_O26_DispOutputEnable(BOOLEAN bParam)
{
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_09);
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_00);
		if(bParam)// display output on
		{
			CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_09, _gOviHwO26Info.chPowerOnRegValue1);
			CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_00, _gOviHwO26Info.chPowerOnRegValue2);
			CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_09);
			CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_00);
			OVI_DEBUG("[OVI] display is changed to ON status!\n");

			{	// initialize Vx1 Lock status counter
				CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
				CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_02, 0x00000030);
				CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_02);

				CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
				CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_02, 0x00000020);
				CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
			}
		}
		else // display output off
		{
			CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_09, _gOviHwO26Info.chPowerOnRegValue1 & (~OVI_HW_O26_CH_POWER_REG_MASK));
			CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_00, _gOviHwO26Info.chPowerOnRegValue2 & (~0x1));
			CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_09);
			CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_00);
			OVI_DEBUG("[OVI] display is changed to OFF status!\n");
		}

		_gOviHwO26Info.isDispOutDisabled = bParam ? FALSE : TRUE;

#if 0 //def OVI_USE_CTOP_CODES_FOR_O26 //o22
	CTOP_CTRL_O26Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r04);
	CTOP_CTRL_O26Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r05);
	if(bParam)// display output on
	{
		CTOP_CTRL_O26Ax_Wr(BND_CTRL_DPE, bnd_dpe_r04, _gOviHwO26Info.chPowerOnRegValue1);
		CTOP_CTRL_O26Ax_Wr(BND_CTRL_DPE, bnd_dpe_r05, _gOviHwO26Info.chPowerOnRegValue2);
		OVI_DEBUG("[OVI] display is changed to ON status!\n");

		{	// initialize Vx1 Lock status counter
			CTOP_CTRL_O26Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
			CTOP_CTRL_O26Ax_Wr(BND_CTRL_DPE, bnd_dpe_r01, 0x00000030);
			CTOP_CTRL_O26Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r01);

			CTOP_CTRL_O26Ax_RdFL(BND_CTRL_DPE, bnd_dpe_r01);
			CTOP_CTRL_O26Ax_Wr(BND_CTRL_DPE, bnd_dpe_r01, 0x00000020);
			CTOP_CTRL_O26Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r01);
		}
	}
	else // display output off
	{
		CTOP_CTRL_O26Ax_Wr(BND_CTRL_DPE, bnd_dpe_r04, _gOviHwO26Info.chPowerOnRegValue1 & (~OVI_HW_O26_CH_POWER_REG_MASK));
		CTOP_CTRL_O26Ax_Wr(BND_CTRL_DPE, bnd_dpe_r05, _gOviHwO26Info.chPowerOnRegValue2 & (~0x10));
		OVI_DEBUG("[OVI] display is changed to OFF status!\n");
	}
	CTOP_CTRL_O26Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r04);
	CTOP_CTRL_O26Ax_WrFL(BND_CTRL_DPE, bnd_dpe_r05);

	_gOviHwO26Info.isDispOutDisabled = bParam ? FALSE : TRUE;
#endif
	return;
}

/* Notice!! :
Cannot use block register macro(ex. CTOP_CTRL_..., OVI_TCON_...) - because of the function call timing */
static void _OVI_O26_GetHWDispOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
{
	__attribute__((unused)) UINT32 year = 0;
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
	dispOpt.wirelessAV = 0;
	dispOpt.ovi_in_bit = 11;
	dispOpt.oled_boost_x4 = 1;

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
		else if (hw_opt[9] == '3') // panel output framerate 165Hz
		{
			dispOpt.panelFramerate = LX_OVI_PANEL_FRAMERATE_165Hz;
			dispOpt.dispFramerate = LX_OVI_PANEL_FRAMERATE_165Hz;
		}

		if (hw_opt[12] == '1') // OLED
		{
			dispOpt.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
		}

		if (hw_opt[17] == '9') // FRC type F22
		{
			dispOpt.frcChipType = LX_OVI_FRC_CHIP_UD_BE_F22;
		}
		else if (hw_opt[17] == 'a') // FRC type KLD
		{
			dispOpt.frcChipType = LX_OVI_FRC_CHIP_UD_BE_KLD;
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
			dispOpt.panel_fr_option = LX_OVI_PANEL_FR_OPTION_01;//amled144, 4K,2K LGD(SCDCRID-3267)
		}
	}

#ifdef BUILD_FEATURE_y29_board
	year = 29;
#elif defined BUILD_FEATURE_y28_board
	year = 28;
#elif defined BUILD_FEATURE_y27_board
	year = 27;
#elif defined BUILD_FEATURE_y26_board
	year = 26;
#elif defined BUILD_FEATURE_y25_board
	year = 25;
#elif defined BUILD_FEATURE_y24_board
	year = 24;
#elif defined BUILD_FEATURE_y23_board
	year = 23;
#elif defined BUILD_FEATURE_y22_board
	year = 22;
#endif
	dispOpt.year_option = year;

	dispOpt.oled_boost_x4 = (dispOpt.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)? 1:0;

	if (RET_OK == OS_ScanKernelCmdlineToken("WirelessAV")) {
		dispOpt.wirelessAV = 1;
	}

	if (dispOpt.panelBacklight != LX_OVI_PANEL_BACKLIGHT_OLED) {
		dispOpt.ovi_in_bit = 10;
	}
	else if (RET_OK == OS_ScanKernelCmdlineToken("maxBitRate13bit")) {
		dispOpt.ovi_in_bit = 13;
	}
	else {
		dispOpt.ovi_in_bit = 11;
	}

	memcpy((void *)pstParams, (void *)&dispOpt, sizeof(LX_OVI_HW_DISPLAY_INFO_T));

	memset(_gOviHwO26Info.tool,0,16);
    if (RET_OK==OS_ScanKernelCmdline("pqe.tool=%s",_gOviHwO26Info.tool)) {
        OVI_PRINT("pqe.tool:%s\n",_gOviHwO26Info.tool);
    } else {
		_gOviHwO26Info.tool[0] = '\0';
        OVI_PRINT("pqe.tool:NA\n");
	}

	OVI_PRINT("%d(%s) %d-%d(%s) %d(%s) %d(%s) x4:%d W:%d T:%s\n",
		pstParams->panelInterface, _ovi_o26_str_panel_interface(pstParams->panelInterface),
		pstParams->panelResolution, pstParams->frcChipType, _ovi_o26_str_frc_chip_type(pstParams->frcChipType),
		pstParams->panelBacklight, _ovi_o26_str_panel_backlight(pstParams->panelBacklight),
		pstParams->panelFramerate, _ovi_o26_str_panel_framerate(pstParams->panelFramerate),
		pstParams->oled_boost_x4,pstParams->wirelessAV,_gOviHwO26Info.tool);

	return;
}
#if 0	//not used
static void _OVI_O26_DispSpreadSpectrumInit(void)
{
#if 0 //o26
	// from m23
	CTOP_CTRL_O26Ax_RdFL(DRG_CTRL, disp_aiopllss_00);
	CTOP_CTRL_O26Ax_Wr(DRG_CTRL, disp_aiopllss_00, _gOviHwO26Info.spreadSpectrumRegValue1);//wr prev value
	CTOP_CTRL_O26Ax_Wr01(DRG_CTRL, disp_aiopllss_00, reg_disp_aiopllss_dss, 1);//enable
	CTOP_CTRL_O26Ax_WrFL(DRG_CTRL, disp_aiopllss_00);

	CTOP_CTRL_O26Ax_RdFL(DRG_CTRL, disp_aiopllss_01);
	CTOP_CTRL_O26Ax_Wr(DRG_CTRL, disp_aiopllss_01, _gOviHwO26Info.spreadSpectrumRegValue2);//wr prev value
	CTOP_CTRL_O26Ax_WrFL(DRG_CTRL, disp_aiopllss_01);

	CTOP_CTRL_O26Ax_RdFL(DRG_CTRL, disp_aiopllss_02);
	CTOP_CTRL_O26Ax_Wr(DRG_CTRL, disp_aiopllss_02, _gOviHwO26Info.spreadSpectrumRegValue3);//wr prev value
	CTOP_CTRL_O26Ax_Wr01(DRG_CTRL, disp_aiopllss_02, reg_disp_aiopllss_offset, 1);//enable
	CTOP_CTRL_O26Ax_WrFL(DRG_CTRL, disp_aiopllss_02);

	CTOP_CTRL_O26Ax_RdFL(DRG_CTRL, disp_aiopllss_00);
	CTOP_CTRL_O26Ax_Wr(DRG_CTRL, disp_aiopllss_00, _gOviHwO26Info.spreadSpectrumRegValue1);//wr prev value
	CTOP_CTRL_O26Ax_WrFL(DRG_CTRL, disp_aiopllss_00);
#endif

#if 0	//m23
	OVI_REG_WR(0xCC922000, (_gOviHwM23Info.spreadSpectrumRegValue1 | 0x4));
	OVI_REG_WR(0xCC922004, _gOviHwM23Info.spreadSpectrumRegValue2);
	OVI_REG_WR(0xCC922008, 0x01000000);
	OVI_REG_WR(0xCC922000, _gOviHwM23Info.spreadSpectrumRegValue1);
#endif

#if 0	//o22
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
#endif
	return;
}
#endif
static void _OVI_O26_CallbackDelayedGamma(struct work_struct *work)
{
	int i;
	__attribute__((unused)) UINT32 regField;

	if (_gOviHwO26Info.pm_suspend == 1)
	{
		OVI_PRINT("skip (in suspend)(%d)\n",_gOviHwO26Info.pm_status);
		return;
	}

	if ((_gOviHwO26Info.delayedRGBGamma.pu32LutR == NULL)
		|| (_gOviHwO26Info.delayedRGBGamma.pu32LutG == NULL)
		|| (_gOviHwO26Info.delayedRGBGamma.pu32LutB == NULL)) return;

	OVI_DEBUG("\n\nRetry Gamma setting!\n\n\r");

	BE_LED_O26_RdFL(ad_dpg_lut_wr_done);
	BE_LED_O26_Rd01(ad_dpg_lut_wr_done, dpg_lut_cpy_status, regField);

	if (regField)
	{
		schedule_delayed_work(&_gOviHwO26Info.delayedRGBGamma.dlyWork, msecs_to_jiffies(10));
	}
	else
	{
		BE_LED_O26_RdFL(ad_dpg_lut_wr_done);
		BE_LED_O26_Wr01(ad_dpg_lut_wr_done, dpg_wstart_o, 0x1);
		BE_LED_O26_WrFL(ad_dpg_lut_wr_done);

		BE_LED_O26_RdFL(ad_dpg_lut_wdata);

		/* Setting Red Gamma Table */
		for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
		{
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_we, 0x4);
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_waddr, i);
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_wdata, _gOviHwO26Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			BE_LED_O26_WrFL(ad_dpg_lut_wdata);
		}
		/* Setting Green Gamma Table */
		for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
		{
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_we, 0x2);
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_waddr, i);
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_wdata, _gOviHwO26Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			BE_LED_O26_WrFL(ad_dpg_lut_wdata);
		}
		/* Setting Blue Gamma Table */
		for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
		{
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_we, 0x1);
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_waddr, i);
			BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_wdata, _gOviHwO26Info.delayedRGBGamma.pu32LutR[i] & 0x7FFF);
			BE_LED_O26_WrFL(ad_dpg_lut_wdata);
		}

		BE_LED_O26_RdFL(ad_dpg_lut_wr_done);
		BE_LED_O26_Wr01(ad_dpg_lut_wr_done, dpg_wdone_o, 0x1);
		BE_LED_O26_WrFL(ad_dpg_lut_wr_done);

		BE_LED_O26_RdFL(ad_dpg_lut_wr_done);
		BE_LED_O26_Wr01(ad_dpg_lut_wr_done, dpg_lut_update, 0x1);
		BE_LED_O26_WrFL(ad_dpg_lut_wr_done);

		vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutR);
		vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutG);
		vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutB);
		_gOviHwO26Info.delayedRGBGamma.pu32LutR = NULL;
		_gOviHwO26Info.delayedRGBGamma.pu32LutG = NULL;
		_gOviHwO26Info.delayedRGBGamma.pu32LutB = NULL;
	}

}

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
static int _OVI_O26_Vx1ChipInfoMemInit(void)
{
	int ret = RET_OK;
	BE_FRM_MEM_CFG_T *pChInfMem = gpBeChInfMem;
	int i;

	do {
		_gOviHwO26Info.pVx1ChipInfoVMapAddr = NULL;

		if (_gOviHwO26Info.hwDispOption.frcChipType != LX_OVI_FRC_CHIP_UD_BE_F22) break;

		if (pChInfMem == NULL
			|| !pChInfMem->frame_base)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if ((pChInfMem->frame_size != BE_OVI_HW_O26_VX1_CHIP_INFO_TOTAL_MEM_SIZE)
			|| (sizeof(BE_OVI_HW_O26_VX1_CHIP_INFO_T) != BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_PACK_SIZE))
		{
			OVI_ERROR("[OVI] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		_gOviHwO26Info.pVx1ChipInfoVMapAddr = vmap_phys(pChInfMem->frame_base, pChInfMem->frame_size);
		if (_gOviHwO26Info.pVx1ChipInfoVMapAddr == NULL)
		{
			OVI_ERROR("[OVI] pVMapAddr is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		for (i=0; i<BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
		{
			if (pChInfMem->frame_size < ((BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
											+BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET \
											+sizeof(BE_OVI_HW_O26_VX1_CHIP_INFO_T))) break;

			_gOviHwO26Info.pVx1ChipInfo[i] = (BE_OVI_HW_O26_VX1_CHIP_INFO_T *)(_gOviHwO26Info.pVx1ChipInfoVMapAddr \
																			+(BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_SIZE*BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_IDX_TAP*i) \
																			+BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
		}
		if (i != BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM)
		{
			OVI_ERROR("[OVI] Vx1 chip info memory size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		_OVI_O26_Vx1ChipInfoMemFill();
	} while(0);

	if (ret && (_gOviHwO26Info.pVx1ChipInfoVMapAddr != NULL))
	{
		vunmap_phys(_gOviHwO26Info.pVx1ChipInfoVMapAddr);
		_gOviHwO26Info.pVx1ChipInfoVMapAddr = NULL;
	}

	return ret;
}

static void _OVI_O26_Vx1ChipInfoMemFill(void)
{
	int i;
	UINT32 *addr;

	if (_gOviHwO26Info.pVx1ChipInfoVMapAddr == NULL) return;

	// Fill in HDR/CRC with default value for BUFF
	for (i=0; i<BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_TOTAL_NUM; i++)
	{
		addr = (UINT32 *)(_gOviHwO26Info.pVx1ChipInfoVMapAddr+ \
							(i*BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_SIZE)+BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_PACK_OFFSET);
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
		addr[0] = _B2L32(BE_OVI_HW_O26_VX1_CHIP_INFO_HDR|BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_SIZE);
		addr[1] = 0;
#else
		*addr = _B2L32(0x0EE00000|BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_SIZE);
#endif
	}

	for (i=0; i<BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
	{
		// Fill in HDR/CRC for BUFF0,3
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.info.maxNum = BE_OVI_HW_O26_VX1_CHIP_INFO_APB_NUM;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.info.bufIdx0 = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.info.bufIdx1 = 3;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.info.version = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.info.u32Data = _B2L32(_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.info.u32Data);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt1.u32Data = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt2.u32Data = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt3.u32Data = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt4.u32Data = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt5.u32Data = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt6.u32Data = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt7.u32Data = 0;
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, dpg);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->dpg);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].u32Data \
													= _B2L32(_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].u32Data);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, colorTemp);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].u32Data \
													= _B2L32(_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].u32Data);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, ledSpiCtrl);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->ledSpiCtrl);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].u32Data \
													= _B2L32(_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].u32Data);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, pcc);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->pcc);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].u32Data \
													= _B2L32(_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].u32Data);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, osdLvCtrl);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->osdLvCtrl);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].u32Data \
													= _B2L32(_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].u32Data);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, phdr);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->phdr);
		_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].u32Data \
													= _B2L32(_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].u32Data);
		_gOviHwO26Info.pVx1ChipInfo[i]->hwCrc = 0xFFFFFFFF;
		_gOviHwO26Info.pVx1ChipInfo[i]->endPacket = _B2L32(BE_OVI_HW_O26_VX1_CHIP_INFO_EP);
#else
		_gOviHwO26Info.pVx1ChipInfo[i]->dpg.dataHwHdr = _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_DPG_DATA_SIZE);
		_gOviHwO26Info.pVx1ChipInfo[i]->dpg.dataHwCrc = 0xFFFFFFFF;
		_gOviHwO26Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr = _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_DPG_CTRL_SIZE);
		_gOviHwO26Info.pVx1ChipInfo[i]->dpg.ctrlHwCrc = 0xFFFFFFFF;
		_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_COLOR_TEMP_SIZE);
		_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
		_gOviHwO26Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE);
		_gOviHwO26Info.pVx1ChipInfo[i]->ledSpiCtrl.hwCrc = 0xFFFFFFFF;
		_gOviHwO26Info.pVx1ChipInfo[i]->pcc.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_PCC_SIZE);
		_gOviHwO26Info.pVx1ChipInfo[i]->pcc.hwCrc = 0xFFFFFFFF;
		_gOviHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE);
		_gOviHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
		_gOviHwO26Info.pVx1ChipInfo[i]->phdr.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_PHDR_SIZE);
		_gOviHwO26Info.pVx1ChipInfo[i]->phdr.hwCrc = 0xFFFFFFFF;
		_gOviHwO26Info.pVx1ChipInfo[i]->rsvd.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_RSVD_SIZE);
		_gOviHwO26Info.pVx1ChipInfo[i]->rsvd.hwCrc = 0xFFFFFFFF;
#endif
	}

	wmb();

	return;
}

static void _OVI_O26_UpdateChipInfoHeader(void)
{
	int i;
	UINT32 hdrVal;

	if (_gOviHwO26Info.pVx1ChipInfoVMapAddr == NULL) return;

	for (i=0; i<BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
	{
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
		BE_OVI_HW_O26_VX1_CHIP_INFO_DAT_HDR_T hdr;

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->hwHdr;
		rmb();
		if (hdrVal != _B2L32(BE_OVI_HW_O26_VX1_CHIP_INFO_HDR|BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_SIZE))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->hwHdr = _B2L32(BE_OVI_HW_O26_VX1_CHIP_INFO_HDR|BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_DATA_SIZE);
		}

		hdr.info.maxNum = BE_OVI_HW_O26_VX1_CHIP_INFO_APB_NUM;
		hdr.info.bufIdx0 = 0;
		hdr.info.bufIdx1 = 3;
		hdr.info.version = 0;
		hdr.info.u32Data = _B2L32(hdr.info.u32Data);

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->datHdr.info.u32Data;
		rmb();
		if (hdrVal != hdr.info.u32Data)
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.info.u32Data = hdr.info.u32Data;
		}

		hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, dpg);
		hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->dpg);
		hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].u32Data = _B2L32(hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].u32Data);

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].u32Data;
		rmb();
		if (hdrVal != hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].u32Data)
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].u32Data = hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_DPG].u32Data;
		}

		hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, colorTemp);
		hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp);
		hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].u32Data = _B2L32(hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].u32Data);

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].u32Data;
		rmb();
		if (hdrVal != hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].u32Data)
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].u32Data = hdr.pos[OVI_HW_O26_VX1_CHIP_INFO_CLR_TMP].u32Data;
		}

		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, ledSpiCtrl);
		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->ledSpiCtrl);
		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].u32Data = _B2L32(hdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].u32Data);

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].u32Data;
		rmb();
		if (hdrVal != hdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].u32Data)
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].u32Data = hdr.pos[BE_HW_O26_VX1_CHIP_INFO_LED_CTRL].u32Data;
		}

		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, pcc);
		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->pcc);
		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].u32Data = _B2L32(hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].u32Data);

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].u32Data;
		rmb();
		if (hdrVal != hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].u32Data)
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].u32Data = hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PCC].u32Data;
		}

		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, osdLvCtrl);
		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->osdLvCtrl);
		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].u32Data = _B2L32(hdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].u32Data);

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].u32Data;
		rmb();
		if (hdrVal != hdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].u32Data)
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].u32Data = hdr.pos[BE_HW_O26_VX1_CHIP_INFO_OSD_LVL].u32Data;
		}

		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].offset = 0xFFFF & offsetof(BE_OVI_HW_O26_VX1_CHIP_INFO_T, phdr);
		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].size = 0xFFFF & sizeof(_gOviHwO26Info.pVx1ChipInfo[i]->phdr);
		hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].u32Data = _B2L32(hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].u32Data);

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].u32Data;
		rmb();
		if (hdrVal != hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].u32Data)
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].u32Data = hdr.pos[BE_HW_O26_VX1_CHIP_INFO_PHDR].u32Data;
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->hwCrc;
		rmb();
		if (hdrVal != 0xFFFFFFFF)
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->hwCrc = 0xFFFFFFFF;
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->endPacket;
		rmb();
		if (hdrVal != _B2L32(BE_OVI_HW_O26_VX1_CHIP_INFO_EP))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->endPacket = _B2L32(BE_OVI_HW_O26_VX1_CHIP_INFO_EP);
		}

#else
		// Check HDR error
		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->dpg.dataHwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_DPG_DATA_SIZE))
			&& (hdrVal != _B2L32(0x0A010000|OVI_HW_O26_VX1_CHIP_INFO_DPG_DATA_SIZE)))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->dpg.dataHwHdr = _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_DPG_DATA_SIZE);
			_gOviHwO26Info.pVx1ChipInfo[i]->dpg.dataHwCrc = 0xFFFFFFFF;
			OVI_PRINT("O26A0 OVI HW UpdateChipInfoHeader dpg data: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_DPG_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|OVI_HW_O26_VX1_CHIP_INFO_DPG_CTRL_SIZE)))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->dpg.ctrlHwHdr = _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_DPG_CTRL_SIZE);
			_gOviHwO26Info.pVx1ChipInfo[i]->dpg.ctrlHwCrc = 0xFFFFFFFF;
			OVI_PRINT("O26A0 OVI HW UpdateChipInfoHeader dpg ctrl: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_COLOR_TEMP_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|OVI_HW_O26_VX1_CHIP_INFO_COLOR_TEMP_SIZE)))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32(0x0EE00000|OVI_HW_O26_VX1_CHIP_INFO_COLOR_TEMP_SIZE);
			_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O26A0 OVI HW UpdateChipInfoHeader colrtmp: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_O26_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE)))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->ledSpiCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_LED_SPI_CTRL_SIZE);
			_gOviHwO26Info.pVx1ChipInfo[i]->ledSpiCtrl.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O26A0 OVI HW UpdateChipInfoHeader ledspi: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->pcc.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_PCC_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_O26_VX1_CHIP_INFO_PCC_SIZE)))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->pcc.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_PCC_SIZE);
			_gOviHwO26Info.pVx1ChipInfo[i]->pcc.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O26A0 OVI HW UpdateChipInfoHeader pcc: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_O26_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE)))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_OSD_RGBLV_CTRL_SIZE);
			_gOviHwO26Info.pVx1ChipInfo[i]->osdLvCtrl.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O26A0 OVI HW UpdateChipInfoHeader osd rgblv: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->phdr.hwHdr;
		rmb();
		if ((hdrVal != _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_PHDR_SIZE))
			&& (hdrVal != _B2L32(0x0A000000|BE_HW_O26_VX1_CHIP_INFO_PHDR_SIZE)))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->phdr.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_PHDR_SIZE);
			_gOviHwO26Info.pVx1ChipInfo[i]->phdr.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O26A0 OVI HW UpdateChipInfoHeader phdr: 0x%x \n",hdrVal);
		}

		hdrVal = _gOviHwO26Info.pVx1ChipInfo[i]->rsvd.hwHdr;
		rmb();
		if (hdrVal != _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_RSVD_SIZE))
		{
			_gOviHwO26Info.pVx1ChipInfo[i]->rsvd.hwHdr = _B2L32(0x0EE00000|BE_HW_O26_VX1_CHIP_INFO_RSVD_SIZE);
			_gOviHwO26Info.pVx1ChipInfo[i]->rsvd.hwCrc = 0xFFFFFFFF;
			OVI_PRINT("O26A0 OVI HW UpdateChipInfoHeader rsvd: 0x%x \n",hdrVal);
		}
#endif
	}

	wmb();

	return;
}
#endif

void OVI_HW_O26_HWDisplayOptionInit(void)
{
	OVI_PRINT("O26A0 OVI HW display option init!\n");

	_OVI_O26_GetHWDispOption(&_gOviHwO26Info.hwDispOption);
}

int OVI_HW_O26_PreInitialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("O26A0 OVI pre init!\n");

		_OVI_O26_GetHWDispOption(&_gOviHwO26Info.hwDispOption);
	} while(0);

	return ret;
}

int OVI_HW_O26_Initialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("OVI chip revision is set to O26 A0\n");

		_gOviHwO26Info.pm_status = 0xff;
		_gOviHwO26Info.pm_suspend = 0;

		gOVI_TCON_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_O26A0_TCON_REG_T));
		gOVI_OIF_O26.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_O26A0_OIF_REG_T));

		gOVI_TCON_O26.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_O26A0_BASE, sizeof(OVI_O26A0_TCON_REG_T));
		gOVI_OIF_O26.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_O26A0_BASE, sizeof(OVI_O26A0_OIF_REG_T));

		/* for dispout mute */
		OVI_OIF_O26_RdFL(oif_vx1_config0);
		_gOviHwO26Info.oif_vx1_config0 = OVI_OIF_O26_Rd(oif_vx1_config0);
		_gOviHwO26Info.dispout_mute = -1;

		/* for copying value used in channel power on/off function */
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_09);
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_00);
		_gOviHwO26Info.chPowerOnRegValue1 = CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_09);
		_gOviHwO26Info.chPowerOnRegValue2 = CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_00);

		/* for copying value used in H-Reverse on/off function */
		OVI_TCON_O26_RdFL(tcon_odc_opt2);
		OVI_TCON_O26_Rd01(tcon_odc_opt2, wb_in_sel, _gOviHwO26Info.horReverseRegFieldValue);

		/* for copying value used in spread spectrum on/off & display resume function */
		CTOP_CTRL_O26Ax_RdFL(DRG_CTRL, disp_aiopllss_00); //bringup-check // need to check when apply ss
		_gOviHwO26Info.spreadSpectrumRegValue1 = CTOP_CTRL_O26Ax_Rd(DRG_CTRL, disp_aiopllss_00);//0xCC93_2000
		CTOP_CTRL_O26Ax_RdFL(DRG_CTRL, disp_aiopllss_01);
		_gOviHwO26Info.spreadSpectrumRegValue2 = CTOP_CTRL_O26Ax_Rd(DRG_CTRL, disp_aiopllss_01);//0xCC93_2004
		CTOP_CTRL_O26Ax_RdFL(DRG_CTRL, disp_aiopllss_02);
		_gOviHwO26Info.spreadSpectrumRegValue3 = CTOP_CTRL_O26Ax_Rd(DRG_CTRL, disp_aiopllss_02);//0xCC93_2008

		CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_HDR,crg_hdr004);
		_gOviHwO26Info.crg_hdr004_org = CTOP_CTRL_O26Ax_Rd(SCRG_CTRL_HDR,crg_hdr004);//0xCC240010
		_gOviHwO26Info.crg_hdr004_cur = _gOviHwO26Info.crg_hdr004_org;
		memset(&_gOviHwO26Info.clk_ctrl,0,sizeof(struct ovi_clk_ctrl));
		mutex_init(&_gOviHwO26Info.clk_ctrl_mutex_lock);

		_gOviHwO26Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		_gOviHwO26Info.tscicWritingFlag = FALSE;
		_gOviHwO26Info.tscicThread = NULL;
		_gOviHwO26Info.tscicU32Tbl = NULL;
		_gOviHwO26Info.tscicU8CtrlData = NULL;

		_gOviHwO26Info.delayedRGBGamma.pu32LutR = NULL;
		_gOviHwO26Info.delayedRGBGamma.pu32LutG = NULL;
		_gOviHwO26Info.delayedRGBGamma.pu32LutB = NULL;

		_gColTemp.bIsGet = 0;
		_gColTemp.r_gain = OVI_HW_O26_WB_DEFAULT_GAIN;
		_gColTemp.g_gain = OVI_HW_O26_WB_DEFAULT_GAIN;
		_gColTemp.b_gain = OVI_HW_O26_WB_DEFAULT_GAIN;
		_gColTemp.r_offset = 0;
		_gColTemp.g_offset = 0;
		_gColTemp.b_offset = 0;

		INIT_DELAYED_WORK(&_gOviHwO26Info.delayedRGBGamma.dlyWork, _OVI_O26_CallbackDelayedGamma);

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
		ret = _OVI_O26_Vx1ChipInfoMemInit();
		if (ret)
		{
			OVI_ERROR("[OVI] Vx1 chip info memory init is failed!\n");
			OVI_BREAK_WRONG(ret);
		}
#endif

		_OVI_O26_GetPempItuneData(&_gOviHwO26Info.pempItuneData);
		_OVI_O26_Get_DC_Cal((UINT8 *)&_gOviHwO26Info.dcVal);

		// initialize Vx1 Lock status counter
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_02, 0x00000030);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_02);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_02, 0x00000020);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
	
		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_PRINT("TCON memory not support\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base) || (!gpOviTconMem->size))
		{
			OVI_PRINT("TCON memory not support : ODC off\n");
			_gOviHwO26Info.tconBaseAddress = 0;
		}
		else
		{
			_gOviHwO26Info.tconBaseAddress = gpOviTconMem->base;
		}
	} while(0);

	return ret;
}

int OVI_HW_O26_Close(void)
{
	int ret = RET_OK;

	cancel_delayed_work_sync(&_gOviHwO26Info.delayedRGBGamma.dlyWork);
	if (_gOviHwO26Info.delayedRGBGamma.pu32LutR != NULL)
	{
		vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutR);
		_gOviHwO26Info.delayedRGBGamma.pu32LutR = NULL;
	}
	if (_gOviHwO26Info.delayedRGBGamma.pu32LutG != NULL)
	{
		vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutG);
		_gOviHwO26Info.delayedRGBGamma.pu32LutG = NULL;
	}
	if (_gOviHwO26Info.delayedRGBGamma.pu32LutB != NULL)
	{
		vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutB);
		_gOviHwO26Info.delayedRGBGamma.pu32LutB = NULL;
	}

	if(gOVI_TCON_O26.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_O26.shdw.addr);
		gOVI_TCON_O26.shdw.addr = NULL;
	}

	if(gOVI_OIF_O26.shdw.addr)
	{
		OS_Free((void *)gOVI_OIF_O26.shdw.addr);
		gOVI_OIF_O26.shdw.addr = NULL;
	}

	if (gOVI_TCON_O26.phys.addr)
	{
		iounmap((void *)gOVI_TCON_O26.phys.addr);
		gOVI_TCON_O26.phys.addr = NULL;
	}

	if (gOVI_OIF_O26.phys.addr)
	{
		iounmap((void *)gOVI_OIF_O26.phys.addr);
		gOVI_OIF_O26.phys.addr = NULL;
	}

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
	if (_gOviHwO26Info.pVx1ChipInfoVMapAddr != NULL)
	{
		vunmap_phys(_gOviHwO26Info.pVx1ChipInfoVMapAddr);
		_gOviHwO26Info.pVx1ChipInfoVMapAddr = NULL;
	}
#endif

	return ret;
}

int OVI_HW_O26_Suspend(void)
{
	int ret = RET_OK;

	do {
		cancel_delayed_work_sync(&_gOviHwO26Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutR != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutR);
			_gOviHwO26Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutG != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutG);
			_gOviHwO26Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutB != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutB);
			_gOviHwO26Info.delayedRGBGamma.pu32LutB = NULL;
		}
	} while(0);

	return ret;
}

int OVI_HW_O26_EarlyResume(void)
{
	int ret = RET_OK;

	do {
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_08);
		if (!(CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_08) & OVI_HW_O26_CH_POWER_REG_MASK)) // Instant boot
		{
			_OVI_O26_DispInit(&_gOviHwO26Info.dispOption,0,0);
		}
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
		else
		{
			_OVI_O26_Vx1ChipInfoMemFill();
		}
#endif
	} while(0);


	return ret;
}

int OVI_HW_O26_Resume(void)
{
	int ret = RET_OK;

	do {
		_gOviHwO26Info.wbEn = FALSE;
		_gOviHwO26Info.wbBypassEn = FALSE;
		_gOviHwO26Info.dgaEn = FALSE;
		_gOviHwO26Info.dgaBypassEn = FALSE;
		_gOviHwO26Info.mleModeOff = FALSE;
		_gOviHwO26Info.odcBypassEn = FALSE;

		cancel_delayed_work_sync(&_gOviHwO26Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutR != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutR);
			_gOviHwO26Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutG != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutG);
			_gOviHwO26Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutB != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutB);
			_gOviHwO26Info.delayedRGBGamma.pu32LutB = NULL;
		}

		_gPrevRedGain = OVI_HW_O26_WB_DEFAULT_GAIN;
		_gPrevGreenGain = OVI_HW_O26_WB_DEFAULT_GAIN;
		_gPrevBlueGain = OVI_HW_O26_WB_DEFAULT_GAIN;

		_gPrevRedOffset = 0;
		_gPrevGreenOffset = 0;
		_gPrevBlueOffset = 0;

		_gOviHwO26Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		_OVI_O26_SetPempItuneData(&_gOviHwO26Info.pempItuneData);
		_OVI_O26_Set_DC_Cal((UINT8 *)&_gOviHwO26Info.dcVal);

		// initialize Vx1 Lock status counter
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_02, 0x00000030);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_02);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_02, 0x00000020);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_02);

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		if ((!gpOviTconMem->base)
			|| (!gpOviTconMem->size))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! O26 ODC will be disabled!\n");

			_gOviHwO26Info.tconBaseAddress = 0;
		}
		else
		{
			_gOviHwO26Info.tconBaseAddress = gpOviTconMem->base;
		}
	} while(0);

	return ret;
}

#define OVI_HW_O26_OPT_BIT_MASK_STB (1<<0)
int OVI_HW_O26_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams)
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

		OVI_PRINT("%d(%s)-%d-%d(%s)-%d-%d-%d-%d-%d(%s)-%d-%d(%s)-%d-%d-%d-0x%x-W:%d\n",
			pstParams->panelInterface, _ovi_o26_str_panel_interface(pstParams->panelInterface),
			pstParams->panelResolution, pstParams->frcChipType, _ovi_o26_str_frc_chip_type(pstParams->frcChipType),
			pstParams->panelCellType, pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
			pstParams->panelBacklight, _ovi_o26_str_panel_backlight(pstParams->panelBacklight),
			pstParams->panelLedBar, pstParams->panelFramerate, _ovi_o26_str_panel_framerate(pstParams->panelFramerate),
			pstParams->lvdsBit, pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all,
			_gOviHwO26Info.hwDispOption.wirelessAV);

		memcpy((void *)&_gOviHwO26Info.dispOption, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

		if (!_gOviHwO26Info.dispOption.userSpecificOption.flags.SocOptionBIT31) // SocOptionBIT31 : 1 -> setDisplayOption debug mode
		{
			__attribute__((unused)) char hw_opt[32];

			// Forced settings by HW option(or boot option)
			if (_gOviHwO26Info.hwDispOption.frcChipType > LX_OVI_FRC_CHIP_INTERNAL)
			{
				_gOviHwO26Info.dispOption.panelInterface = LX_OVI_PANEL_VX1;
			}
			else
			{
				_gOviHwO26Info.dispOption.panelInterface = _gOviHwO26Info.hwDispOption.panelInterface;
			}

			_gOviHwO26Info.dispOption.panelFramerate = _gOviHwO26Info.hwDispOption.dispFramerate;
			_gOviHwO26Info.dispOption.panelResolution = _gOviHwO26Info.hwDispOption.dispResolution;
#if 0
			if (_gOviHwO26Info.hwDispOption.isVx15Byte)
			{
				_gOviHwO26Info.dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
			}
			else
			{
				_gOviHwO26Info.dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
			}
#endif
			_gOviHwO26Info.dispOption.frcChipType = _gOviHwO26Info.hwDispOption.frcChipType;

			if (_gOviHwO26Info.hwDispOption.panelInterface == LX_OVI_PANEL_LVDS)
			{
				if ((RET_OK==OS_ScanKernelCmdline("disp=%s", hw_opt))
					&& (!strncmp(hw_opt,"hdmi",4)))
				{
					_gOviHwO26Info.dispOption.lvdsType = LX_OVI_LVDS_OUT_JEIDA;
				}
				else
				{
					_gOviHwO26Info.dispOption.lvdsType = LX_OVI_LVDS_OUT_VESA;
				}
			}
		}
#if 0
		if (_gOviHwO26Info.hwDispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_165Hz)
		{
			//OIF PLL config
			OVI_REG_WR(0xCC975010, 0x6028319C);//	[2]: DSS
			OVI_REG_WR(0xCC975014, 0x31020440);
			OVI_REG_WR(0xCC975018, 0x00000380);
			OVI_REG_WR(0xCC975010, 0x60283198);//	DSS ON SSC : 0.4%/28khz
			OVI_REG_WR(0xCC4C40B0, 0x00007FFF);
			udelay(100);
		}
#endif
		_OVI_O26_DispRegDataInit(&_gOviHwO26Info.dispOption,0,0);
	} while(0);

	return ret;
}

int OVI_HW_O26_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams)
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

		OVI_PRINT("En[%d], Mask[0x%x]\n", pstParams->bEnable, pstParams->u32BlockMask);

		if (pstParams->u32BlockMask & LX_OVI_TCON_GAMMA)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O26_RdFL(tcon_control);
				OVI_TCON_O26_Wr01(tcon_control, dga_en, 0x0);
				OVI_TCON_O26_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_O26_RdFL(tcon_control);
				OVI_TCON_O26_Wr01(tcon_control, dga_en, _gOviHwO26Info.dgaEn ? 0x1 : 0x0);
				OVI_TCON_O26_WrFL(tcon_control);
			}
			_gOviHwO26Info.dgaBypassEn = pstParams->bEnable;
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_WB)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O26_RdFL(tcon_control);
				OVI_TCON_O26_Wr01(tcon_control, wb_en, 0x0);
				OVI_TCON_O26_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_O26_RdFL(tcon_control);
				OVI_TCON_O26_Wr01(tcon_control, wb_en, _gOviHwO26Info.wbEn ? 0x1 : 0x0);
				OVI_TCON_O26_WrFL(tcon_control);
			}
			_gOviHwO26Info.wbBypassEn = pstParams->bEnable;
		}
	} while(0);

	return ret;
}

int OVI_HW_O26_SetCombination(UINT32 param)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	return ret;
}


int OVI_HW_O26_SetFrameOdcEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetColorTempEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		BE_LED_O26_RdFL(ad_wb2p_en);
		if(bParam)
			BE_LED_O26_Wr01(ad_wb2p_en, wb2p_en, 0x1);
		else
			BE_LED_O26_Wr01(ad_wb2p_en, wb2p_en, 0x0);
		BE_LED_O26_WrFL(ad_wb2p_en);
	} while (0);

	return ret;
}

int OVI_HW_O26_SetGammaEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		BE_LED_O26_RdFL(ad_dpg_en);
		if(bParam)
			BE_LED_O26_Wr01(ad_dpg_en, dpg_en, 0x1);
		else
			BE_LED_O26_Wr01(ad_dpg_en, dpg_en, 0x0);
		BE_LED_O26_WrFL(ad_dpg_en);
	} while (0);

	return ret;
}

int OVI_HW_O26_SetDitherEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O26_RdFL(tcon_control);
		if(bParam)
		{
			OVI_TCON_O26_Wr01(tcon_control, pre_dither_en, 0x1);
		}
		else
		{
			OVI_TCON_O26_Wr01(tcon_control, pre_dither_en, 0x0);
		}
		OVI_TCON_O26_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_O26_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetDitherMode(LX_OVI_TCON_DITHER_T enParam)
{
	int ret = RET_OK;

	do {
		//Dither Enable
		OVI_TCON_O26_RdFL(tcon_control);
		OVI_TCON_O26_Wr01(tcon_control, pre_dither_en, 0x1);
		OVI_TCON_O26_WrFL(tcon_control);

		OVI_TCON_O26_RdFL(tcon_dither_carry);
		switch(enParam)
		{
			case LX_OVI_TCON_DITHER_TRUNC:
				OVI_TCON_O26_Wr01(tcon_dither_carry, pre_dither_sel, 0x0);
				break;
			case LX_OVI_TCON_DITHER_ROUND:
				OVI_TCON_O26_Wr01(tcon_dither_carry, pre_dither_sel, 0x1);
				break;
			case LX_OVI_TCON_DITHER_RANDOM:
			default :
				OVI_TCON_O26_Wr01(tcon_dither_carry, pre_dither_sel, 0x2);
				break;
		}
		OVI_TCON_O26_WrFL(tcon_dither_carry);
	} while(0);

	return ret;
}

static UINT32 _OVI_O26_GetGain(UINT32 gain)
{
	UINT32 ret_gain;
	UINT32 temp;
	UINT32 rangeOpt;

	rangeOpt = (gain >> 31) & 0x1;
	gain &= (~(1 << 31));

	if ((rangeOpt == 0)
		|| ((rangeOpt == 1) && (gain >= 192)))
	{
		temp = 10000 + (gain - 192) * OVI_HW_O26_WB_GAIN_STEP1;
	}
	else
	{
		temp = 10000 + (gain - 192) * OVI_HW_O26_WB_GAIN_STEP2;
	}
	ret_gain = (temp * OVI_HW_O26_WB_DEFAULT_GAIN) / 10000;

	return ret_gain;
}

static SINT16 _OVI_O26_GetOffset(UINT32 offset)
{
	SINT16 ret_offset;

	ret_offset = ((SINT32)offset - 64) * OVI_HW_O26_WB_OFFSET_STEP;
	return ret_offset;
}

int OVI_HW_O26_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams)
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
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
			if (_gOviHwO26Info.pVx1ChipInfoVMapAddr != NULL)
			{
				UINT32 dataSize;
				int i;
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
				BE_OVI_HW_O26_VX1_CHIP_INFO_APB_CNT0_T count;
#endif

				r_gain = _OVI_O26_GetGain(pstParams->r_gain);
				g_gain = _OVI_O26_GetGain(pstParams->g_gain);
				b_gain = _OVI_O26_GetGain(pstParams->b_gain);

				rOffset = _OVI_O26_GetOffset(pstParams->r_offset);
				gOffset = _OVI_O26_GetOffset(pstParams->g_offset);
				bOffset = _OVI_O26_GetOffset(pstParams->b_offset);

				_gColTemp = *pstParams;

				for (i=0; i<BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM; i++)
				{
					dataSize = 0;

					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbEnRegAddr = _B2L32(OVI_HW_F22_REG_WB_EN); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbEnVal = _B2L32(0x1); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbRGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_R_GAIN); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbRGainVal = _B2L32(r_gain); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbROffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_R_OFFSET); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbROffsetVal = _B2L32(rOffset); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbGGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_G_GAIN); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbGGainVal = _B2L32(g_gain); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbGOffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_G_OFFSET); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbGOffsetVal = _B2L32(gOffset); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbBGainRegAddr = _B2L32(OVI_HW_F22_REG_WB_B_GAIN); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbBGainVal = _B2L32(b_gain); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbBOffsetRegAddr = _B2L32(OVI_HW_F22_REG_WB_B_OFFSET); dataSize++;
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.wbBOffsetVal = _B2L32(bOffset); dataSize++;
					dataSize = sizeof(UINT32) * dataSize;

#ifndef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.hwCrc = 0xFFFFFFFF;
#endif

					if (dataSize != OVI_HW_O26_VX1_CHIP_INFO_COLOR_TEMP_SIZE)
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
					count.u32Data = _B2L32(_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data);

					if (count.colorTemp == 0xFF)
					{
						count.colorTemp = 1;
					}
					else
					{
						count.colorTemp++;
					}

					_gOviHwO26Info.pVx1ChipInfo[i]->datHdr.cnt0.u32Data = _B2L32(count.u32Data);
#else
					_gOviHwO26Info.pVx1ChipInfo[i]->colorTemp.hwHdr = _B2L32((0x0A000000|OVI_HW_O26_VX1_CHIP_INFO_COLOR_TEMP_SIZE));
#endif

					wmb();
					_OVI_O26_UpdateChipInfoHeader();
				}
				if (ret != RET_OK) break;
			}
			else
			{
#endif
				// W/B Enable
				BE_LED_O26_RdFL(ad_wb2p_en);
				BE_LED_O26_Wr01(ad_wb2p_en, wb2p_en, 0x1);
				BE_LED_O26_WrFL(ad_wb2p_en);

				r_gain = _OVI_O26_GetGain(pstParams->r_gain);
				g_gain = _OVI_O26_GetGain(pstParams->g_gain);
				b_gain = _OVI_O26_GetGain(pstParams->b_gain);

				rOffset = _OVI_O26_GetOffset(pstParams->r_offset);
				gOffset = _OVI_O26_GetOffset(pstParams->g_offset);
				bOffset = _OVI_O26_GetOffset(pstParams->b_offset);

				_gColTemp = *pstParams;

				if((_gPrevRedGain == r_gain) && (_gPrevGreenGain == g_gain) && (_gPrevBlueGain == b_gain)
					&& (_gPrevRedOffset == rOffset) && (_gPrevGreenOffset == gOffset) && (_gPrevBlueOffset == bOffset))
				{
					return RET_OK;
				}

				if (_gOviHwO26Info.hwDispOption.oled_boost_x4 == 1)
				{
					// Set red gain
					BE_LED_O26_RdFL(ad_wb2p_r_gain);
					BE_LED_O26_Wr(ad_wb2p_r_gain, r_gain >> 2);
					BE_LED_O26_WrFL(ad_wb2p_r_gain);

					// Set red offset
					BE_LED_O26_RdFL(ad_wb2p_r_offset);
					BE_LED_O26_Wr(ad_wb2p_r_offset, rOffset);
					BE_LED_O26_WrFL(ad_wb2p_r_offset);

					// Set green gain
					BE_LED_O26_RdFL(ad_wb2p_g_gain);
					BE_LED_O26_Wr(ad_wb2p_g_gain, g_gain >> 2);
					BE_LED_O26_WrFL(ad_wb2p_g_gain);

					// Set green offset
					BE_LED_O26_RdFL(ad_wb2p_g_offset);
					BE_LED_O26_Wr(ad_wb2p_g_offset, gOffset);
					BE_LED_O26_WrFL(ad_wb2p_g_offset);

					// Set blue gain
					BE_LED_O26_RdFL(ad_wb2p_b_gain);
					BE_LED_O26_Wr(ad_wb2p_b_gain, b_gain >> 2);
					BE_LED_O26_WrFL(ad_wb2p_b_gain);

					// Set blue offset
					BE_LED_O26_RdFL(ad_wb2p_b_offset);
					BE_LED_O26_Wr(ad_wb2p_b_offset, bOffset);
					BE_LED_O26_WrFL(ad_wb2p_b_offset);
				}
				else
				{
					// Set red gain
					BE_LED_O26_RdFL(ad_wb2p_r_gain);
					BE_LED_O26_Wr(ad_wb2p_r_gain, r_gain);
					BE_LED_O26_WrFL(ad_wb2p_r_gain);

					// Set red offset
					BE_LED_O26_RdFL(ad_wb2p_r_offset);
					BE_LED_O26_Wr(ad_wb2p_r_offset, rOffset << 2);
					BE_LED_O26_WrFL(ad_wb2p_r_offset);

					// Set green gain
					BE_LED_O26_RdFL(ad_wb2p_g_gain);
					BE_LED_O26_Wr(ad_wb2p_g_gain, g_gain);
					BE_LED_O26_WrFL(ad_wb2p_g_gain);

					// Set green offset
					BE_LED_O26_RdFL(ad_wb2p_g_offset);
					BE_LED_O26_Wr(ad_wb2p_g_offset, gOffset << 2);
					BE_LED_O26_WrFL(ad_wb2p_g_offset);

					// Set blue gain
					BE_LED_O26_RdFL(ad_wb2p_b_gain);
					BE_LED_O26_Wr(ad_wb2p_b_gain, b_gain);
					BE_LED_O26_WrFL(ad_wb2p_b_gain);

					// Set blue offset
					BE_LED_O26_RdFL(ad_wb2p_b_offset);
					BE_LED_O26_Wr(ad_wb2p_b_offset, bOffset<< 2);
					BE_LED_O26_WrFL(ad_wb2p_b_offset);
				}
				_gPrevRedGain = r_gain;
				_gPrevGreenGain = g_gain;
				_gPrevBlueGain = b_gain;
				_gPrevRedOffset = rOffset;
				_gPrevGreenOffset = gOffset;
				_gPrevBlueOffset = bOffset;
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
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

int OVI_HW_O26_SetMultiWinGamut(LX_OVI_MULTIWIN_GAMUT_T *pstParams)
{
	int ret = RET_OK;
	__attribute__((unused)) UINT32 regVal,regVal1,regVal2,regVal3;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		OVI_TRACE("=========================================pstParams:%d, %d, %d, %d, %d\n", pstParams->win_id,pstParams->pcc_eotf_en,pstParams->pcc_oetf_en,pstParams->reg_pcc_en,pstParams->reg_l3d_en);

		switch(pstParams->win_id)
		{
			case LX_OVI_WIN_0:
				if(pstParams->pcc_eotf_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_00, win0_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_00);

				BE_PCC_O26_RdFL(pe_pcc_ctrl);
				BE_PCC_O26_Rd01(pe_pcc_ctrl,pcc_eotf_en,regVal);

				OVI_TRACE("=========================================pcc_eotf_en: %x\n",regVal);
				OVI_TRACE("=========================================pcc_winctrl_00: %d\n",pstParams->win_id);

				}
				else if(pstParams->pcc_eotf_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_00, win0_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_00);

				BE_PCC_O26_RdFL(pe_pcc_ctrl);
				BE_PCC_O26_Rd01(pe_pcc_ctrl,pcc_eotf_en,regVal);

				OVI_TRACE("=========================================pcc_eotf_en: %x\n",regVal);
				OVI_TRACE("=========================================pcc_winctrl_00: %d\n",pstParams->win_id);
				}

				if(pstParams->pcc_oetf_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_01, win0_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_01);

				BE_PCC_O26_RdFL(pe_pcc_ctrl);
				BE_PCC_O26_Rd01(pe_pcc_ctrl,pcc_oetf_en,regVal1);

				OVI_TRACE("=========================================pcc_oetf_en: %x\n",regVal1);
				OVI_TRACE("=========================================pcc_winctrl_00: %d\n",pstParams->win_id);
				}
				else if(pstParams->pcc_oetf_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_01, win0_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_01);

				BE_PCC_O26_RdFL(pe_pcc_ctrl);
				BE_PCC_O26_Rd01(pe_pcc_ctrl,pcc_oetf_en,regVal1);

				OVI_TRACE("=========================================pcc_oetf_en: %x\n",regVal1);
				OVI_TRACE("=========================================pcc_winctrl_00: %d\n",pstParams->win_id);

				}

				if(pstParams->reg_pcc_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_02, win0_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_02);

				BE_PCC_O26_RdFL(pe_pcc_ctrl);
				BE_PCC_O26_Rd01(pe_pcc_ctrl,reg_pcc_en,regVal2);

				OVI_TRACE("=========================================reg_pcc_en: %x\n",regVal2);
				OVI_TRACE("=========================================pcc_winctrl_00: %d\n",pstParams->win_id);

				}
				else if(pstParams->reg_pcc_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_02, win0_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_02);

				BE_PCC_O26_RdFL(pe_pcc_ctrl);
				BE_PCC_O26_Rd01(pe_pcc_ctrl,reg_pcc_en,regVal2);

				OVI_TRACE("=========================================reg_pcc_en: %x\n",regVal2);
				OVI_TRACE("=========================================pcc_winctrl_00: %d\n",pstParams->win_id);
				}

				if(pstParams->reg_l3d_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_03, win0_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_03);

				BE_L3D_O26_RdFL(l3d_core_ctrl_00);
				BE_L3D_O26_Rd01(l3d_core_ctrl_00,reg_l3d_en,regVal3);

				OVI_TRACE("=========================================reg_l3d_en: %x\n",regVal3);
				OVI_TRACE("=========================================pcc_winctrl_00: %d\n",pstParams->win_id);

				}
				else if(pstParams->reg_l3d_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_03, win0_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_03);

				BE_L3D_O26_RdFL(l3d_core_ctrl_00);
				BE_L3D_O26_Rd01(l3d_core_ctrl_00,reg_l3d_en,regVal3);

				OVI_TRACE("=========================================reg_l3d_en: %x\n",regVal3);
				OVI_TRACE("=========================================pcc_winctrl_00: %d\n",pstParams->win_id);

				}
				break;
			case LX_OVI_WIN_1:
				if(pstParams->pcc_eotf_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_00, win1_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_00);

				OVI_TRACE("=========================================pcc_eotf_en: %x\n",BE_PCC_O26_Rd(pe_pcc_ctrl));
				OVI_TRACE("=========================================pcc_winctrl_00: %x\n",BE_PCC_WIN_O26_Rd(pcc_winctrl_00));
				}
				else if(pstParams->pcc_eotf_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_00, win1_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_00);

				OVI_TRACE("=========================================pcc_eotf_en: %x\n",BE_PCC_O26_Rd(pe_pcc_ctrl));
				OVI_TRACE("=========================================pcc_winctrl_00: %x\n",BE_PCC_WIN_O26_Rd(pcc_winctrl_00));
				}

				if(pstParams->pcc_oetf_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_01, win1_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_01);
				}
				else if(pstParams->pcc_oetf_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_01, win1_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_01);
				}

				if(pstParams->reg_pcc_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_02, win1_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_02);
				}
				else if(pstParams->reg_pcc_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_02, win1_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_02);
				}

				if(pstParams->reg_l3d_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_03, win1_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_03);
				}
				else if(pstParams->reg_l3d_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_03, win1_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_03);
				}
				break;
			case LX_OVI_WIN_2:
				if(pstParams->pcc_eotf_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_00, win2_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_00);
				}
				else if(pstParams->pcc_eotf_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_00, win2_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_00);
				}

				if(pstParams->pcc_oetf_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_01, win2_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_01);
				}
				else if(pstParams->pcc_oetf_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_01, win2_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_01);
				}

				if(pstParams->reg_pcc_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_02, win2_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_02);
				}
				else if(pstParams->reg_pcc_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_02, win2_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_02);
				}

				if(pstParams->reg_l3d_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_03, win2_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_03);
				}
				else if(pstParams->reg_l3d_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_03, win2_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_03);
				}
				break;
			case LX_OVI_WIN_3:
				if(pstParams->pcc_eotf_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_00, win3_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_00);
				}
				else if(pstParams->pcc_eotf_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_00, win3_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_00);
				}

				if(pstParams->pcc_oetf_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_01, win3_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_01);
				}
				else if(pstParams->pcc_oetf_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_01, win3_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_01);
				}

				if(pstParams->reg_pcc_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_02, win3_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_02);
				}
				else if(pstParams->reg_pcc_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_02, win3_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_02);
				}

				if(pstParams->reg_l3d_en == 1)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_03, win3_en, 0x1);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_03);
				}
				else if(pstParams->reg_l3d_en == 0)
				{
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Wr01(pcc_winctrl_03, win3_en, 0x0);
					BE_PCC_WIN_O26_WrFL(pcc_winctrl_03);
				}
				break;
			default:
				break;
		}
	} while(0);
	return ret;
}

int OVI_HW_O26_GetMultiWinGamut(LX_OVI_MULTIWIN_GAMUT_T *pstParams)
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

		switch(pstParams->win_id)
		{
			case LX_OVI_WIN_0:
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_00,win0_en,pstParams->pcc_eotf_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_01,win0_en,pstParams->pcc_oetf_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_02,win0_en,pstParams->reg_pcc_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_03,win0_en,pstParams->reg_l3d_en);
				break;
			case LX_OVI_WIN_1:
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_00,win1_en,pstParams->pcc_eotf_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_01,win1_en,pstParams->pcc_oetf_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_02,win1_en,pstParams->reg_pcc_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_03,win1_en,pstParams->reg_l3d_en);
				break;
			case LX_OVI_WIN_2:
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_00,win2_en,pstParams->pcc_eotf_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_01,win2_en,pstParams->pcc_oetf_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_02,win2_en,pstParams->reg_pcc_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_03,win2_en,pstParams->reg_l3d_en);
				break;
			case LX_OVI_WIN_3:
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_00);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_00,win3_en,pstParams->pcc_eotf_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_01);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_01,win3_en,pstParams->pcc_oetf_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_02);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_02,win3_en,pstParams->reg_pcc_en);
					BE_PCC_WIN_O26_RdFL(pcc_winctrl_03);
					BE_PCC_WIN_O26_Rd01(pcc_winctrl_03,win3_en,pstParams->reg_l3d_en);
				break;
			default:
				break;
		}
	} while(0);
	return ret;
}

int OVI_HW_O26_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams)
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

		cancel_delayed_work_sync(&_gOviHwO26Info.delayedRGBGamma.dlyWork);
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutR != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutR);
			_gOviHwO26Info.delayedRGBGamma.pu32LutR = NULL;
		}
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutG != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutG);
			_gOviHwO26Info.delayedRGBGamma.pu32LutG = NULL;
		}
		if (_gOviHwO26Info.delayedRGBGamma.pu32LutB != NULL)
		{
			vfree(_gOviHwO26Info.delayedRGBGamma.pu32LutB);
			_gOviHwO26Info.delayedRGBGamma.pu32LutB = NULL;
		}

		if (!pstParams->bIsGet)
		{
			if((pstParams->rGammaLut.sizeNum != OVI_HW_O26_GAMMA_TABLE_SIZENUM)
			|| (pstParams->gGammaLut.sizeNum != OVI_HW_O26_GAMMA_TABLE_SIZENUM)
			|| (pstParams->bGammaLut.sizeNum != OVI_HW_O26_GAMMA_TABLE_SIZENUM))
			{
				OVI_ERROR("[OVI] Gamma table size is not correct! \n");
				ret = RET_ERROR;
				break;
			}

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user((void *)rGammaTable, (void __user *)pstParams->rGammaLut.pData, OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user((void *)gGammaTable, (void __user *)pstParams->gGammaLut.pData, OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user((void *)bGammaTable, (void __user *)pstParams->bGammaLut.pData, OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
			if (_gOviHwO26Info.pVx1ChipInfoVMapAddr != NULL)
			{
				UINT32 dataSize;
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
				BE_OVI_HW_O26_VX1_CHIP_INFO_APB_CNT0_T count;
#else
				UINT32 ctrlSize;
#endif
				int idx;

				for (idx=0; idx<BE_OVI_HW_O26_VX1_CHIP_INFO_MEM_BUFF_NUM; idx++)
				{
					dataSize = 0;
#ifndef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
					ctrlSize= 0;
#endif

					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.wDataRegAddr = _B2L32(OVI_HW_F22_REG_DPG_LUT_WDATA); dataSize++;
					/* Setting Red Gamma Table */
					for (i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.wdata[i] = _B2L32(((0x4<<28)|(i<<16)|(rGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O26_GAMMA_TABLE_SIZENUM;
					/* Setting Green Gamma Table */
					for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.wdata[i+OVI_HW_O26_GAMMA_TABLE_SIZENUM] = _B2L32(((0x2<<28)|(i<<16)|(gGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O26_GAMMA_TABLE_SIZENUM;
					/* Setting Blue Gamma Table */
					for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
					{
						_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.wdata[i+(OVI_HW_O26_GAMMA_TABLE_SIZENUM*2)] = _B2L32(((0x1<<28)|(i<<16)|(bGammaTable[i] & 0x7FFF)));
					}
					dataSize += OVI_HW_O26_GAMMA_TABLE_SIZENUM;
					dataSize = sizeof(UINT32) * dataSize;

#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO_APB_SLAVE
					if (dataSize != OVI_HW_O26_VX1_CHIP_INFO_DPG_DATA_SIZE)
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();

					count.u32Data = _B2L32(_gOviHwO26Info.pVx1ChipInfo[idx]->datHdr.cnt0.u32Data);

					if (count.dpg == 0xFF)
					{
						count.dpg = 1;
					}
					else
					{
						count.dpg++;
					}

					_gOviHwO26Info.pVx1ChipInfo[idx]->datHdr.cnt0.u32Data = _B2L32(count.u32Data);
					wmb();
#else
					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.dataHwCrc = 0xFFFFFFFF;

					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.wrDoneRegAddr = _B2L32(OVI_HW_F22_REG_DPG_LUT_WR_DONE); ctrlSize++;
					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.wrDoneVal = _B2L32(0x1); ctrlSize++;
					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.enRegAddr = _B2L32(OVI_HW_F22_REG_DPG_EN); ctrlSize++;
					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.enVal = _B2L32(0x1); ctrlSize++;
					ctrlSize = sizeof(UINT32) * ctrlSize;

					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.ctrlHwCrc = 0xFFFFFFFF;

					if ((dataSize != OVI_HW_O26_VX1_CHIP_INFO_DPG_DATA_SIZE)
						|| (ctrlSize != OVI_HW_O26_VX1_CHIP_INFO_DPG_CTRL_SIZE))
					{
						OVI_ERROR("[OVI] Error in Vx1 chip info data size! \n");
						ret = RET_ERROR;
						break;
					}

					wmb();

					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.dataHwHdr = _B2L32((0x0A010000|OVI_HW_O26_VX1_CHIP_INFO_DPG_DATA_SIZE));
					wmb();
					_gOviHwO26Info.pVx1ChipInfo[idx]->dpg.ctrlHwHdr = _B2L32((0x0A000000|OVI_HW_O26_VX1_CHIP_INFO_DPG_CTRL_SIZE));
					wmb();
					_OVI_O26_UpdateChipInfoHeader();
#endif
				}
				if (ret != RET_OK) break;
			}
			else
			{
#endif
				BE_LED_O26_RdFL(ad_dpg_lut_wr_done);
				BE_LED_O26_Rd01(ad_dpg_lut_wr_done, dpg_lut_cpy_status, regField);

				if (regField)
				{
					_gOviHwO26Info.delayedRGBGamma.pu32LutR = rGammaTable;
					_gOviHwO26Info.delayedRGBGamma.pu32LutG = gGammaTable;
					_gOviHwO26Info.delayedRGBGamma.pu32LutB = bGammaTable;

					schedule_delayed_work(&_gOviHwO26Info.delayedRGBGamma.dlyWork, msecs_to_jiffies(10));
				}
				else
				{
					BE_LED_O26_RdFL(ad_dpg_lut_wr_done);
					BE_LED_O26_Wr01(ad_dpg_lut_wr_done, dpg_wstart_o, 0x1);
					BE_LED_O26_WrFL(ad_dpg_lut_wr_done);

					BE_LED_O26_RdFL(ad_dpg_lut_wdata);

					/* Setting Red Gamma Table */
					for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
					{
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_we, 0x4);
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_waddr, i);
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_wdata, rGammaTable[i] & 0x7FFF);
						BE_LED_O26_WrFL(ad_dpg_lut_wdata);
					}
					/* Setting Green Gamma Table */
					for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
					{
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_we, 0x2);
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_waddr, i);
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_wdata, gGammaTable[i] & 0x7FFF);
						BE_LED_O26_WrFL(ad_dpg_lut_wdata);
					}
					/* Setting Blue Gamma Table */
					for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
					{
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_we, 0x1);
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_waddr, i);
						BE_LED_O26_Wr01(ad_dpg_lut_wdata, dpg_wdata, bGammaTable[i] & 0x7FFF);
						BE_LED_O26_WrFL(ad_dpg_lut_wdata);
					}

					BE_LED_O26_RdFL(ad_dpg_lut_wr_done);
					BE_LED_O26_Wr01(ad_dpg_lut_wr_done, dpg_wdone_o, 0x1);
					BE_LED_O26_WrFL(ad_dpg_lut_wr_done);

					BE_LED_O26_RdFL(ad_dpg_lut_wr_done);
					BE_LED_O26_Wr01(ad_dpg_lut_wr_done, dpg_lut_update, 0x1);
					BE_LED_O26_WrFL(ad_dpg_lut_wr_done);

					// Gamma Enable
					BE_LED_O26_RdFL(ad_dpg_en);
					BE_LED_O26_Wr01(ad_dpg_en, dpg_en, 0x1);
					BE_LED_O26_WrFL(ad_dpg_en);
				}
#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
			}
#endif
		}
		else
		{

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			/* Setting Red Gamma Table */
			for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
			{
				BE_LED_O26_RdFL(ad_dpg_lut_rdata);
				BE_LED_O26_Wr01(ad_dpg_lut_rdata, dpg_re, 0x4);
				BE_LED_O26_Wr01(ad_dpg_lut_rdata, dpg_raddr, i);
				BE_LED_O26_WrFL(ad_dpg_lut_rdata);
				BE_LED_O26_RdFL(ad_dpg_lut_rdata);
				BE_LED_O26_Rd01(ad_dpg_lut_rdata, dpg_rdata, rGammaTable[i]);
			}
			/* Setting Green Gamma Table */
			for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
			{
				BE_LED_O26_RdFL(ad_dpg_lut_rdata);
				BE_LED_O26_Wr01(ad_dpg_lut_rdata, dpg_re, 0x2);
				BE_LED_O26_Wr01(ad_dpg_lut_rdata, dpg_raddr, i);
				BE_LED_O26_WrFL(ad_dpg_lut_rdata);
				BE_LED_O26_RdFL(ad_dpg_lut_rdata);
				BE_LED_O26_Rd01(ad_dpg_lut_rdata, dpg_rdata, gGammaTable[i]);
			}
			/* Setting Blue Gamma Table */
			for(i=0; i<OVI_HW_O26_GAMMA_TABLE_SIZENUM; i++)
			{
				BE_LED_O26_RdFL(ad_dpg_lut_rdata);
				BE_LED_O26_Wr01(ad_dpg_lut_rdata, dpg_re, 0x1);
				BE_LED_O26_Wr01(ad_dpg_lut_rdata, dpg_raddr, i);
				BE_LED_O26_WrFL(ad_dpg_lut_rdata);
				BE_LED_O26_RdFL(ad_dpg_lut_rdata);
				BE_LED_O26_Rd01(ad_dpg_lut_rdata, dpg_rdata, bGammaTable[i]);
			}

			pstParams->rGammaLut.sizeNum = OVI_HW_O26_GAMMA_TABLE_SIZENUM;
			pstParams->gGammaLut.sizeNum = OVI_HW_O26_GAMMA_TABLE_SIZENUM;
			pstParams->bGammaLut.sizeNum = OVI_HW_O26_GAMMA_TABLE_SIZENUM;

			ret = copy_to_user(pstParams->rGammaLut.pData, (void __user *)rGammaTable, OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->gGammaLut.pData, (void __user *)gGammaTable, OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->bGammaLut.pData, (void __user *)bGammaTable, OVI_HW_O26_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

		}
	} while(0);

	if((rGammaTable != NULL) && (_gOviHwO26Info.delayedRGBGamma.pu32LutR == NULL))
		vfree((const void *)rGammaTable);
	if((gGammaTable != NULL) && (_gOviHwO26Info.delayedRGBGamma.pu32LutG == NULL))
		vfree((const void *)gGammaTable);
	if((bGammaTable != NULL) && (_gOviHwO26Info.delayedRGBGamma.pu32LutB == NULL))
		vfree((const void *)bGammaTable);

	return ret;
}

int OVI_HW_O26_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetTconHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetLvdsHReverse(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O26_RdFL(tcon_ddiv_mode);
		if(bParam) {
			OVI_TCON_O26_Wr01(tcon_ddiv_mode, rd_mode, 0x0);
			OVI_TCON_O26_Wr01(tcon_ddiv_mode, line_delay, 0x1);
		}
		else {
			OVI_TCON_O26_Wr01(tcon_ddiv_mode, rd_mode, 0x1);
			OVI_TCON_O26_Wr01(tcon_ddiv_mode, line_delay, 0x0);
		}
		OVI_TCON_O26_WrFL(tcon_ddiv_mode);
		_gOviHwO26Info.mirrorH = bParam;
	} while(0);

	return ret;
}

int OVI_HW_O26_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams)
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

		OVI_TCON_O26_RdFL(tcon_pgen_ctl);

		// pattern source color setting
		OVI_TCON_O26_RdFL(tcon_pgen_agpr1);
		OVI_TCON_O26_Wr(tcon_pgen_agpr1, 0x03FF);
		OVI_TCON_O26_WrFL(tcon_pgen_agpr1);

		OVI_TCON_O26_RdFL(tcon_pgen_agpg1);
		OVI_TCON_O26_Wr(tcon_pgen_agpg1, 0x03FF);
		OVI_TCON_O26_WrFL(tcon_pgen_agpg1);

		OVI_TCON_O26_RdFL(tcon_pgen_agpb1);
		OVI_TCON_O26_Wr(tcon_pgen_agpb1, 0x03FF);
		OVI_TCON_O26_WrFL(tcon_pgen_agpb1);

		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_TPG_OFF:		// pattern off
				OVI_TCON_O26_Wr(tcon_pgen_ctl, 0x0);
				_gOviHwO26Info.mute = 0;
				break;
			case LX_OVI_TCON_TPG_BLACK:		// black pattern
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x4);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				_gOviHwO26Info.mute = 1;
				break;
			case LX_OVI_TCON_TPG_WHITE:		// white pattern
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HVBAR:		// HVBar pattern
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x3);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR16GREY:		// Horizontal 16 grey pattern
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x8);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR64GREY:		// Horizontal 64 grey pattern
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x7);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR256GREY:		// Horizontal 256 grey pattern
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x6);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR1024GREY:		// Horizontal 1024 grey pattern
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x5);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_VER16GREY:		// Vertical 16 grey pattern
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0xC);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, pstParams->bUseInternalSync ? 0x1 : 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default :
				break;
		}
		OVI_TCON_O26_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_O26_SetChannelPower(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		_OVI_O26_DispOutputEnable(bParam);
	} while(0);

	return ret;
}

int OVI_HW_O26_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O26_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_LVDS_OUT_JEIDA:
				OVI_OIF_O26_Wr01(oif_lvds_config0, lvds_lsb_first, 0x0);
				break;
			case LX_OVI_LVDS_OUT_VESA:
				OVI_OIF_O26_Wr01(oif_lvds_config0, lvds_lsb_first, 0x1);
				break;
			default:
				break;
		}
		OVI_OIF_O26_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_O26_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O26_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_8BIT:
				OVI_OIF_O26_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x1);
				break;
			case LX_OVI_10BIT:
				OVI_OIF_O26_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x0);
				break;
			default:
				break;
		}
		OVI_OIF_O26_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_O26_SetLvdsBlack(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O26_RdFL(oif_lvds_config1);
		OVI_OIF_O26_RdFL(oif_lvds_config2);
		OVI_OIF_O26_RdFL(oif_vx1_config3);
		OVI_OIF_O26_RdFL(oif_vx1_config4);

		if(!bParam) // original data out
		{
			OVI_OIF_O26_Wr01(oif_lvds_config1, lvds_force_even_data, 0x0);
			OVI_OIF_O26_Wr01(oif_lvds_config2, lvds_force_odd_data, 0x0);

			OVI_OIF_O26_Wr01(oif_vx1_config3, vx1_force_even_data, 0x0);
			OVI_OIF_O26_Wr01(oif_vx1_config4, vx1_force_odd_data, 0x0);
		}
		else // black data out
		{
			OVI_OIF_O26_Wr01(oif_lvds_config1, lvds_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_O26_Wr01(oif_lvds_config2, lvds_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);

			OVI_OIF_O26_Wr01(oif_vx1_config3, vx1_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_O26_Wr01(oif_vx1_config4, vx1_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);
		}
		OVI_OIF_O26_WrFL(oif_lvds_config1);
		OVI_OIF_O26_WrFL(oif_lvds_config2);
		OVI_OIF_O26_WrFL(oif_vx1_config3);
		OVI_OIF_O26_WrFL(oif_vx1_config4);
	} while(0);

	return ret;
}

int OVI_HW_O26_SetClock(BOOLEAN bParam)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetEpiDataScramble(BOOLEAN bParam)
{
	int ret = RET_OK;
	return ret;
}

int OVI_HW_O26_SetAdvanced10bit(BOOLEAN bParam)
{
	int ret = RET_OK;

	OVI_TCON_O26_RdFL(tcon_odc_opt2);
	OVI_TCON_O26_Wr01(tcon_odc_opt2, pre_dit_in_sel, bParam? 1:0);
	OVI_TCON_O26_WrFL(tcon_odc_opt2);

	return ret;
}

int OVI_HW_O26_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam)
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

		if (OVI_HW_O26_INPUT_VCOM_PAT_DATA_SIZE != pstParam->sizeNum)
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

		OVI_TCON_O26_RdFL(tcon_pgen_vcomp0);
		OVI_TCON_O26_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, patData[0]);
		OVI_TCON_O26_WrFL(tcon_pgen_vcomp0);

		OVI_TCON_O26_RdFL(tcon_pgen_vcomp1);
		OVI_TCON_O26_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, patData[1]);
		OVI_TCON_O26_WrFL(tcon_pgen_vcomp1);

		OVI_TCON_O26_RdFL(tcon_pgen_vcomp2);
		OVI_TCON_O26_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, patData[2]);
		OVI_TCON_O26_WrFL(tcon_pgen_vcomp2);

		OVI_TCON_O26_RdFL(tcon_pgen_vcomp3);
		OVI_TCON_O26_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, patData[3]);
		OVI_TCON_O26_WrFL(tcon_pgen_vcomp3);

		if (level > 0)
		{
			OVI_TCON_O26_RdFL(tcon_pgen_agpr1);
			OVI_TCON_O26_Wr01(tcon_pgen_agpr1, pgen_color_r1, level);
			OVI_TCON_O26_WrFL(tcon_pgen_agpr1);

			OVI_TCON_O26_RdFL(tcon_pgen_agpg1);
			OVI_TCON_O26_Wr01(tcon_pgen_agpg1, pgen_color_g1, level);
			OVI_TCON_O26_WrFL(tcon_pgen_agpg1);

			OVI_TCON_O26_RdFL(tcon_pgen_agpb1);
			OVI_TCON_O26_Wr01(tcon_pgen_agpb1, pgen_color_b1, level);
			OVI_TCON_O26_WrFL(tcon_pgen_agpb1);
		}
	} while(0);

	if(u16vcomPatData != NULL)
		vfree(u16vcomPatData);

	return ret;
}

int OVI_HW_O26_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O26_RdFL(tcon_pgen_ctl);

		switch(enParam)
		{
			case LX_OVI_TCON_VCOM_PAT_CTRL_OFF:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x0);

				OVI_TCON_O26_RdFL(tcon_pgen_vcomp0);
				OVI_TCON_O26_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, 0x0);
				OVI_TCON_O26_WrFL(tcon_pgen_vcomp0);

				OVI_TCON_O26_RdFL(tcon_pgen_vcomp1);
				OVI_TCON_O26_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, 0x0);
				OVI_TCON_O26_WrFL(tcon_pgen_vcomp1);

				OVI_TCON_O26_RdFL(tcon_pgen_vcomp2);
				OVI_TCON_O26_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, 0x0);
				OVI_TCON_O26_WrFL(tcon_pgen_vcomp2);

				OVI_TCON_O26_RdFL(tcon_pgen_vcomp3);
				OVI_TCON_O26_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, 0x0);
				OVI_TCON_O26_WrFL(tcon_pgen_vcomp3);

				OVI_TCON_O26_RdFL(tcon_pgen_agpr1);
				OVI_TCON_O26_Wr01(tcon_pgen_agpr1, pgen_color_r1, 0x3FF);
				OVI_TCON_O26_WrFL(tcon_pgen_agpr1);

				OVI_TCON_O26_RdFL(tcon_pgen_agpg1);
				OVI_TCON_O26_Wr01(tcon_pgen_agpg1, pgen_color_g1, 0x3FF);
				OVI_TCON_O26_WrFL(tcon_pgen_agpg1);

				OVI_TCON_O26_RdFL(tcon_pgen_agpb1);
				OVI_TCON_O26_Wr01(tcon_pgen_agpb1, pgen_color_b1, 0x3FF);
				OVI_TCON_O26_WrFL(tcon_pgen_agpb1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_ON:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x1E);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM1:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x16);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM2:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x17);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM3:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x18);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM4:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x19);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM5:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x1A);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM6:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x1B);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM7:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x1C);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM8:
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_mode, 0x1D);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O26_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default:
				break;
		}

		OVI_TCON_O26_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_O26_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam)
{
	int ret = RET_OK;
	OVI_PRINT("frcChipType:%d, panelResolution:%d, panelFramerate:%d\n",_gOviHwO26Info.hwDispOption.frcChipType, _gOviHwO26Info.hwDispOption.panelResolution, _gOviHwO26Info.hwDispOption.panelFramerate);
	do {
		if ((_gOviHwO26Info.hwDispOption.frcChipType == LX_OVI_FRC_CHIP_INTERNAL)
			&& (_gOviHwO26Info.hwDispOption.panelResolution == LX_OVI_PANEL_RESOLUTION_3840X2160)
			&& (_gOviHwO26Info.hwDispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_120HZ))
		{
			switch(enParam)
			{
				case LX_OVI_DISP_OUTPUT_MODE_4K60:
					OVI_TCON_O26_RdFL(tcon_ddiv_mode);
					OVI_TCON_O26_RdFL(tcon_ddiv_rgbsel1);
					OVI_TCON_O26_Wr01(tcon_ddiv_mode, lane_num, 0x8);
					OVI_TCON_O26_Wr(tcon_ddiv_rgbsel1, 0x01234567);
					OVI_TCON_O26_WrFL(tcon_ddiv_mode);
					OVI_TCON_O26_WrFL(tcon_ddiv_rgbsel1);

					// O26 TCON clock
					CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_TCON, crg_tcon004);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TCON, crg_tcon004, reg_pix2_clk_sel, 0x1);
					CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_TCON, crg_tcon004);

					// O26 LED clock
					CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_LED, crg_led004);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_LED, crg_led004, reg_led_pxl_clk_sel, 0x1);
					CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_LED, crg_led004);

					// O26 CCO clock
					CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_CCO, crg_cco004);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CCO, crg_cco004, reg_bosd_clk_sel, 0x1);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CCO, crg_cco004, reg_cco_disp_clk_sel, 0x1);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CCO, crg_cco004, reg_cco_disp_osd_clk_sel, 0x1);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CCO, crg_cco004, reg_cco_gcf_clk_sel, 0x1);
					CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_CCO, crg_cco004);

					// O26 VSD clock
					CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_VSD, crg_vsd004);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_VSD, crg_vsd004, reg_vsd_obs_clk_sel, 0x3);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_VSD, crg_vsd004, reg_vsd_det_clk_sel, 0x1);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_VSD, crg_vsd004, reg_vsd_disp_clk_sel, 0x1);
					CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_VSD, crg_vsd004);
					break;
				case LX_OVI_DISP_OUTPUT_MODE_4K120:
				default:
					OVI_TCON_O26_RdFL(tcon_ddiv_mode);
					OVI_TCON_O26_RdFL(tcon_ddiv_rgbsel1);
					OVI_TCON_O26_Wr01(tcon_ddiv_mode, lane_num, 0x10);
					OVI_TCON_O26_Wr(tcon_ddiv_rgbsel1, 0x89ABCDEF);
					OVI_TCON_O26_WrFL(tcon_ddiv_mode);
					OVI_TCON_O26_WrFL(tcon_ddiv_rgbsel1);

					// O26 TCON clock
					CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_TCON, crg_tcon004);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_TCON, crg_tcon004, reg_pix2_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_TCON, crg_tcon004);

					// O26 LED clock
					CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_LED, crg_led004);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_LED, crg_led004, reg_led_pxl_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_LED, crg_led004);

					// O26 CCO clock
					CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_CCO, crg_cco004);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CCO, crg_cco004, reg_bosd_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CCO, crg_cco004, reg_cco_disp_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CCO, crg_cco004, reg_cco_disp_osd_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_CCO, crg_cco004, reg_cco_gcf_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_CCO, crg_cco004);
					// O26 VSD clock
					CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_VSD, crg_vsd004);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_VSD, crg_vsd004, reg_vsd_det_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_VSD, crg_vsd004, reg_vsd_disp_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_Wr01(SCRG_CTRL_VSD, crg_vsd004, reg_vsd_obs_clk_sel, 0x0);
					CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_VSD, crg_vsd004);
					break;
			}

			_gOviHwO26Info.dispOutputMode = enParam;
		}
	} while(0);

	return ret;
}

int OVI_HW_O26_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams)
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

		if (memcmp(&_gOviHwO26Info.dispOption, pstParams, sizeof(LX_OVI_DISPLAY_INFO_T)) != 0)
		{
			OVI_PRINT("changed:%d(%s)-%d-%d(%s)-%d-%d-%d-%d-%d(%s)-%d-%d(%s)-%d-%d-%d-0x%x-W:%d\n",
				pstParams->panelInterface, _ovi_o26_str_panel_interface(pstParams->panelInterface),
				pstParams->panelResolution, pstParams->frcChipType, _ovi_o26_str_frc_chip_type(pstParams->frcChipType),
				pstParams->panelCellType, pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
				pstParams->panelBacklight, _ovi_o26_str_panel_backlight(pstParams->panelBacklight),
				pstParams->panelLedBar, pstParams->panelFramerate, _ovi_o26_str_panel_framerate(pstParams->panelFramerate),
				pstParams->lvdsBit, pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all,
				_gOviHwO26Info.hwDispOption.wirelessAV);
		}
	} while(0);
	return ret;
}

static int _OVI_O26_GetPempItuneData(OVI_HW_O26_PEMP_ITUNE_DATA_T *pstParams)
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
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_05, 0x7); // link on(0~2)
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x3); // itune ch 0,1 addr
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_06);
		regVal = CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_06);

		for (i = 0, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8ituneData[i] = (regVal >> j) & 0xF;
			u8ituneData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x2); // itune ch 2,3 addr
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_06);
		regVal = CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_06);

		for (i = 2, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8ituneData[i] = (regVal >> j) & 0xF;
			u8ituneData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x1); // pemp ch 0,1 addr
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_06);
		regVal = CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_06);

		for (i = 0, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8pempData[i] = (regVal >> j) & 0xF;
			u8pempData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x0); // pemp ch 2,3 addr
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_06);
		regVal = CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_06);

		for (i = 2, j = 16; i < 12 && j >= 0; i= i+4, j= j-8)
		{
			u8pempData[i] = (regVal >> j) & 0xF;
			u8pempData[i+1] = (regVal >> (j+4)) & 0xF;
		}

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_05, 0x0); // link off
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		OS_UsecDelay(1);

	}while(0);
	return ret;
}

static int _OVI_O26_SetPempItuneData(OVI_HW_O26_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	UINT8* u8pempData;
	UINT8* u8ituneData;

	u8pempData = pstParams->pemp;
	u8ituneData = pstParams->itune;
	do {
		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_05, 0x1); // link on
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8ituneData[0] & 0xF) | ((u8ituneData[1] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8ituneData[2] & 0xF) | ((u8ituneData[3] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8pempData[0] & 0xF) | ((u8pempData[1] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8pempData[2] & 0xF) | ((u8pempData[3] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_05, 0x2); // link on
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8ituneData[4] & 0xF) | ((u8ituneData[5] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8ituneData[6] & 0xF) | ((u8ituneData[7] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8pempData[4] & 0xF) | ((u8pempData[5] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8pempData[6] & 0xF) | ((u8pempData[7] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_05, 0x4); // link on
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x3);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8ituneData[8] & 0xF) | ((u8ituneData[9] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x2);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8ituneData[10] & 0xF) | ((u8ituneData[11] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x1);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8pempData[8] & 0xF) | ((u8pempData[9] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_addr, 0x0);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wrdata, (u8pempData[10] & 0xF) | ((u8pempData[11] << 4) & 0xF0));
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x0);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr01(MIP_CTRL_C4TX16, mip_c4tx16_04, reg_c4_ext_reg_wr_en, 0x1);
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_04, 0x1000000); // reset
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_04);
		OS_UsecDelay(1);

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		CTOP_CTRL_O26Ax_Wr(MIP_CTRL_C4TX16, mip_c4tx16_05, 0x0); // link off
		CTOP_CTRL_O26Ax_WrFL(MIP_CTRL_C4TX16, mip_c4tx16_05);
		OS_UsecDelay(1);

	}while(0);
	return ret;
}

int OVI_HW_O26_SetPempItune(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams)
{
	int ret = RET_OK;
	OVI_HW_O26_PEMP_ITUNE_DATA_T param;

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

			ret = _OVI_O26_SetPempItuneData(&param);
		}
		else
		{
			ret = _OVI_O26_GetPempItuneData(&param);

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

static void _OVI_O26_Get_DC_Cal(UINT8 *data)
{
	//TODO:
}

static void _OVI_O26_Set_DC_Cal(UINT8 *data)
{
	//TODO:
}

int OVI_HW_O26_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams)
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

		*pstParams = _gOviHwO26Info.hwDispOption;
	}while(0);

	return ret;
}

int OVI_HW_O26_GetLockStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;

	do {
		__attribute__((unused)) UINT32 regVal;
		// check structure pointer
		if (pbParam == NULL)
		{
			OVI_ERROR("[OVI] parameter is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
		CTOP_CTRL_O26Ax_Rd01(MIP_CTRL_C4TX16, mip_c4tx16_02, reg_c4_vx1_lockn_main_counter, regVal);

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

int OVI_HW_O26_SetPmMode(UINT32 u32Param)
{
	int ret = RET_OK;
	static UINT32 _gARnomalVal = 0;
//	OVI_PRINT(" %d (0:S_PREPARE,1:SUSPEND,2:S_COMPLETED,3:R_PREPARE,4:RESUME,5:R_COMPLETED)\n",u32Param);

	_gOviHwO26Info.pm_status = u32Param;

	switch (u32Param)
	{
		case OVI_HW_O26_PQE_PM_DEVICE_SUSPEND_PREPARE:
			_gOviHwO26Info.pm_suspend = 1;
			cancel_delayed_work_sync(&_gOviHwO26Info.delayedRGBGamma.dlyWork);
			usleep_range(20000, 20000);//20ms
			OVI_PRINT("SUSPEND_PREPARE done\n");
			break;
		case OVI_HW_O26_PQE_PM_DEVICE_SUSPEND:
			break;
		case OVI_HW_O26_PQE_PM_DEVICE_SUSPEND_COMPLETED:
			CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_09);//0xCC974024
			_gARnomalVal = CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_09);

			/* 20250924, add ldo, http://jira.lge.com/issue/browse/SICDTV-16228 */
			OVI_REG_WR(0xCC974010, 0x01000000);// # c4_ext_reg_rstn=1  org
			OVI_REG_WR(0xCC974014, 0x00000040);// # pll_ext_reg_en=1  org
			OVI_REG_WR(0xCC974010, 0x01000101);// # sel_reg=00
			OVI_REG_WR(0xCC974010, 0x01010101);//
			OVI_REG_WR(0xCC974010, 0x01000708);// # pdb_pll_reg=0
			OVI_REG_WR(0xCC974010, 0x01010708);//
			OVI_REG_WR(0xCC974010, 0x01000000);// #WR_EN_CLR           org
			OVI_REG_WR(0xCC974014, 0x0000000F);// # link_ext_reg_en=1
			OVI_REG_WR(0xCC974010, 0x01000E00);// # pdb_link_reg=0, sel_reg=00
			OVI_REG_WR(0xCC974010, 0x01010E00);//
			OVI_REG_WR(0xCC974010, 0x01000000);// #WR_EN_CLR           org
			OVI_REG_WR(0xCC974000, 0x00000000);// # c4_rstn_vtxlink=0
			OVI_REG_WR(0xCC974024, 0x00000000);// # c4_pdb=0, c4_pdb_ch=0
			usleep_range(100, 100);//100us

			OVI_PRINT("SUSPEND_COMPLETED ldo.done_%x\n",_gARnomalVal);
			break;
		case OVI_HW_O26_PQE_PM_DEVICE_RESUME_PREPARE:
			/* 20250924, add ldo, http://jira.lge.com/issue/browse/SICDTV-16228 */
			OVI_REG_WR(0xCC974024, 0x01000000);// # c4_pdb=1
			usleep_range(100, 100);//100us
			OVI_REG_WR(0xCC974010, 0x01000000);// # c4_ext_reg_rstn=1  org
			OVI_REG_WR(0xCC974014, 0x00000040);// # pll_ext_reg_en=1   org
			OVI_REG_WR(0xCC974010, 0x01000111);// # sel_reg=01
			OVI_REG_WR(0xCC974010, 0x01010111);//
			OVI_REG_WR(0xCC974010, 0x0100070C);// # pdb_pll_reg=1
			OVI_REG_WR(0xCC974010, 0x0101070C);//
			OVI_REG_WR(0xCC974010, 0x01000000);// #WR_EN_CLR           org
			OVI_REG_WR(0xCC974014, 0x0000000F);// # link_ext_reg_en=1  org
			OVI_REG_WR(0xCC974010, 0x01000E99);// # pdb_link_reg=1, sel_reg=01
			OVI_REG_WR(0xCC974010, 0x01010E99);//
			OVI_REG_WR(0xCC974010, 0x01000000);// #WR_EN_CLR           org
			OVI_REG_WR(0xCC974024, _gARnomalVal);// # c4_pdb_ch=1        org
			usleep_range(100, 100);//100us
			OVI_REG_WR(0xCC974000, 0x00000001);// # c4_rstn_vtxlink=1  org
			//_OVI_O26_DispSpreadSpectrumInit();

			OVI_PRINT("RESUME_PREPARE ldo.done_%x\n",_gARnomalVal);
			break;
		case OVI_HW_O26_PQE_PM_DEVICE_RESUME:
			break;
		case OVI_HW_O26_PQE_PM_DEVICE_RESUME_COMPLETED:
			_gOviHwO26Info.pm_suspend = 0;
			OVI_PRINT("RESUME_COMPLETED done\n");
			break;
		default:
			break;
	}

	return ret;
}

static void _OVI_O26_Draw_Pat(int num)
{
	switch (num)
	{
		case 0: // clear
			OVI_TCON_O26_RdFL(tcon_pgen_ctl);
			OVI_TCON_O26_Wr(tcon_pgen_ctl, 0x00000000);
			OVI_TCON_O26_WrFL(tcon_pgen_ctl);

			OVI_OIF_O26_RdFL(oif_vx1_config3);
			OVI_OIF_O26_Wr(oif_vx1_config3, 0x00000000);
			OVI_OIF_O26_WrFL(oif_vx1_config3);

			OVI_OIF_O26_RdFL(oif_vx1_config4);
			OVI_OIF_O26_Wr(oif_vx1_config4, 0x00000000);
			OVI_OIF_O26_WrFL(oif_vx1_config4);
			break;

		case 1: // tcon exter hvbar
			OVI_TCON_O26_RdFL(tcon_odc_opt2);
			OVI_TCON_O26_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_O26_WrFL(tcon_odc_opt2);

			OVI_TCON_O26_RdFL(tcon_pgen_ctl);
			OVI_TCON_O26_Wr(tcon_pgen_ctl, 0x00000019);
			OVI_TCON_O26_WrFL(tcon_pgen_ctl);
			break;

		case 2: // tcon exter hgradi
			OVI_TCON_O26_RdFL(tcon_odc_opt2);
			OVI_TCON_O26_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_O26_WrFL(tcon_odc_opt2);

			OVI_TCON_O26_RdFL(tcon_pgen_ctl);
			OVI_TCON_O26_Wr(tcon_pgen_ctl, 0x00000029);
			OVI_TCON_O26_WrFL(tcon_pgen_ctl);
			break;

		case 3: // tcon inter hvbar
			OVI_TCON_O26_RdFL(tcon_odc_opt2);
			OVI_TCON_O26_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_O26_WrFL(tcon_odc_opt2);

			OVI_TCON_O26_RdFL(tcon_pgen_ctl);
			OVI_TCON_O26_Wr(tcon_pgen_ctl, 0x0000001b);
			OVI_TCON_O26_WrFL(tcon_pgen_ctl);
			break;

		case 4: // tcon inter hgradi
			OVI_TCON_O26_RdFL(tcon_odc_opt2);
			OVI_TCON_O26_Wr(tcon_odc_opt2, 0x00000054);
			OVI_TCON_O26_WrFL(tcon_odc_opt2);

			OVI_TCON_O26_RdFL(tcon_pgen_ctl);
			OVI_TCON_O26_Wr(tcon_pgen_ctl, 0x0000002b);
			OVI_TCON_O26_WrFL(tcon_pgen_ctl);
			break;

		case 5: // pixel repl
			OVI_OIF_O26_RdFL(oif_vx1_config3);
			OVI_OIF_O26_Wr(oif_vx1_config3, 0x400003ff);
			OVI_OIF_O26_WrFL(oif_vx1_config3);

			OVI_OIF_O26_RdFL(oif_vx1_config4);
			OVI_OIF_O26_Wr(oif_vx1_config4, 0x400003ff);
			OVI_OIF_O26_WrFL(oif_vx1_config4);
			break;

		case 6: // led pat
			break;

		default:
			break;
	}
}

int OVI_HW_O26_UpdateChipInfoHeader(void)
{
	int ret = RET_OK;

	do{
		#ifdef BE_OVI_HW_O26_USE_VX1_CHIP_INFO
		_OVI_O26_UpdateChipInfoHeader();
		#endif
	} while(0);

	return ret;
}

int OVI_HW_O26_SetDispOutMute(UINT32 u32Param)
{
	int ret = RET_OK;
	UINT32 wr_data = _gOviHwO26Info.oif_vx1_config0;
	OVI_O26A0_OIF_VX1_CONFIG0_T *p = (OVI_O26A0_OIF_VX1_CONFIG0_T *)&wr_data;//0x9008

	p->vx1_video_mute = (u32Param)? 1:0;
	//OVI_OIF_O26_RdFL(oif_vx1_config0);
	OVI_OIF_O26_Wr(oif_vx1_config0, wr_data);
	OVI_OIF_O26_WrFL(oif_vx1_config0);

	OVI_PRINT("[OVI] mute : %d, wr_data : 0x%08x <- 0x%08x\n",u32Param,wr_data,_gOviHwO26Info.oif_vx1_config0);

	_gOviHwO26Info.dispout_mute = u32Param;
	_gOviHwO26Info.oif_vx1_config0 = wr_data;

	return ret;
}

/* 20240705, (SCDCR-6884) */
int OVI_HW_O26_SetDClock(UINT32 *pu32Param)
{
	int ret = RET_OK;
	UINT32 vrr_on = 0;
	LX_OVI_DISPLAY_INFO_T dispOption;

	do{
		if (pu32Param == NULL)
		{
			OVI_ERROR("[OVI] parameter is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		memcpy(&dispOption,&_gOviHwO26Info.dispOption,sizeof(LX_OVI_DISPLAY_INFO_T));

		//1:165hz,0:basic
		if (*pu32Param == 1) {
			vrr_on = 1;
		}

		_OVI_O26_DispInit(&dispOption,vrr_on,0);
	} while(0);

	return ret;
}

/* SICREQ-1217 */
int OVI_HW_O26_SetOutputTiming(LX_OVI_TCON_OUTPUT_TIMING_T *pstParams)
{
	int ret = RET_OK;
//	UINT32 vrr_on = 0;
//	LX_OVI_DISPLAY_INFO_T dispOption;
	UINT32 high_clk = 0;

	do {
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] parameter is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		switch (pstParams->frameRate)
		{
			case 144:
			case 165:
			case 288:
			case 330:
				high_clk = 1;
				break;
			case 120:
			case 240:
			default:
				break;
		}
		OVI_DEBUG("[OVI] Set output timing: frameRate=%d, high_clk=%d\n",pstParams->frameRate, high_clk);
		_OVI_O26_DispInit(&_gOviHwO26Info.dispOption, 0, high_clk);
	} while (0);

	return ret;
}

int OVI_HW_O26_GetStatus(UINT32 *pu32Param)
{
	int ret = RET_OK;
	CTOP_CTRL_O26Ax_RdFL(MIP_CTRL_C4TX16, mip_c4tx16_02);
	OVI_PRINT("lock:0x%x\n",CTOP_CTRL_O26Ax_Rd(MIP_CTRL_C4TX16, mip_c4tx16_02));
	return ret;
}

int ovi_hw_o26_clk_ctrl(struct ovi_clk_ctrl *p_ctrl)
{
	OVI_HW_O26_INFO_T *p = &_gOviHwO26Info;
	struct ovi_clk_ctrl *p_clk = &p->clk_ctrl;

	if (!p_ctrl) {
		OVI_ERROR("p_ctrl null\n");
		return -1;
	}

	mutex_lock(&p->clk_ctrl_mutex_lock);
	p_clk->type = p_ctrl->type;

	if (p_clk->type == OVI_CRG_CTRL_TYPE_SRC) {
		p_clk->src = p_ctrl->src;
	} else if (p_clk->type == OVI_CRG_CTRL_TYPE_VRR) {
		p_clk->vrr = p_ctrl->vrr;
	}

	if (!p_clk->vrr && p_clk->src == OVI_CRG_CTRL_SRC_VDEC) {
		p->crg_hdr004_cur = 0x2;//2:core600_clk(600.0MHz)
		OVI_PRINT("core600_clk\n");
	} else {
		p->crg_hdr004_cur = p->crg_hdr004_org;
	}

	// crg_hdr004(0xCC240010) [1:0]reg_hdr_clk_sel
	// 0:core800_clk(800.0MHz), 1:din780_clk(780.0MHz), 2:core600_clk(600.0MHz)
	CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_HDR,crg_hdr004);
	CTOP_CTRL_O26Ax_Wr(SCRG_CTRL_HDR,crg_hdr004,p->crg_hdr004_cur);
	CTOP_CTRL_O26Ax_WrFL(SCRG_CTRL_HDR,crg_hdr004);

	OVI_PRINT("typ:%d src:%d vrr:%d - org:0x%x cur:0x%x\n",\
		p_clk->type,p_clk->src,p_clk->vrr,p->crg_hdr004_org,p->crg_hdr004_cur);

	mutex_unlock(&p->clk_ctrl_mutex_lock);
	return 0;
}

static int _ovi_hw_o26_hdr_scrg(UINT32 vrr, UINT32 data)
{
	struct ovi_clk_ctrl ctrl;
	OVI_HW_O26_INFO_T *p = &_gOviHwO26Info;

	ctrl.type = OVI_CRG_CTRL_TYPE_VRR;
	ctrl.vrr = vrr;
	p->crg_hdr004_org = data;

	return ovi_hw_o26_clk_ctrl(&ctrl);
}

int OVI_HW_O26_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	__attribute__((unused)) int	i;
	__attribute__((unused)) UINT32 val;
	__attribute__((unused)) char hw_opt[64];

	switch(proc_id)
	{
		case OVI_HAL_PROC_ID_DETAIL_INFO:
		{
			seq_printf(m, "ovi:update O26KLD settings(v3.5:8-1.Fix Hsync missing at VRR 165Hz and Hbllank delay for Vactive 2160)\n");
			seq_printf(m, "gpOviTconMem : base:0x%08x, size:%dKb\n",gpOviTconMem->base,gpOviTconMem->size>>10);
			seq_printf(m, "Info.tconBaseAddress : 0x%08x\n",_gOviHwO26Info.tconBaseAddress);

			seq_printf(m, "chPowerOnRegValue1: 0x%08x\n", _gOviHwO26Info.chPowerOnRegValue1 );
			seq_printf(m, "chPowerOnRegValue2: 0x%08x\n", _gOviHwO26Info.chPowerOnRegValue2 );

			seq_printf(m, "oif_vx1_config0: 0x%08x\n", _gOviHwO26Info.oif_vx1_config0 );
			seq_printf(m, "dispout_mute   : %d\n", _gOviHwO26Info.dispout_mute );

			OVI_OIF_O26_RdFL(oif_lvds_config0);

			OVI_OIF_O26_Rd01(oif_lvds_config0, lvds_lsb_first, val);
			seq_printf(m, "lvds.format: %s (0x%x)\n", (val)?"vesa":"jeida", val);

			OVI_OIF_O26_Rd01(oif_lvds_config0, lvds_8bit_mode, val);
			seq_printf(m, "lvds.bit: %d bit (0x%x)\n", (val)? 8:10, val);

			OVI_OIF_O26_RdFL(oif_lvds_config1);
			OVI_OIF_O26_Rd01(oif_lvds_config1, lvds_force_even_data, val);
			seq_printf(m, "lvds.black_out: %s (0x%x)\n", (val)? "black":"orignal", val);

			seq_printf(m, "\n");
			seq_printf(m, "<dispOption>\n");
			seq_printf(m, "panelBacklight    : %d (%s)\n",_gOviHwO26Info.dispOption.panelBacklight,_ovi_o26_str_panel_backlight(_gOviHwO26Info.dispOption.panelBacklight));
			seq_printf(m, "panelFramerate    : %d (%s)\n",_gOviHwO26Info.dispOption.panelFramerate,_ovi_o26_str_panel_framerate(_gOviHwO26Info.dispOption.panelFramerate));
			seq_printf(m, "frcChipType       : %d (%s)\n",_gOviHwO26Info.dispOption.frcChipType,_ovi_o26_str_frc_chip_type(_gOviHwO26Info.dispOption.frcChipType));
			seq_printf(m, "panelInterface    : %d (%s)\n",_gOviHwO26Info.dispOption.panelInterface,_ovi_o26_str_panel_interface(_gOviHwO26Info.dispOption.panelInterface));
			seq_printf(m, "panelInch         : %d (%d:55,%d:65,%d:77)\n",_gOviHwO26Info.dispOption.panelInch,LX_OVI_PANEL_INCH_55,LX_OVI_PANEL_INCH_65,LX_OVI_PANEL_INCH_77);

			seq_printf(m, "\n");
			seq_printf(m, "<hwDispOption>\n");
			if (RET_OK==OS_ScanKernelCmdline("hwopt=%s", hw_opt)) {
				seq_printf(m, "hw_opt            : %s\n",hw_opt);
			}
			seq_printf(m, "tool              : %s\n",_gOviHwO26Info.tool);
			seq_printf(m, "isDispOutDisabled : %d\n",_gOviHwO26Info.isDispOutDisabled);
			seq_printf(m, "mirrorH           : %d\n",_gOviHwO26Info.mirrorH);
			seq_printf(m, "mirrorV           : %d\n",_gOviHwO26Info.mirrorV);
			seq_printf(m, "panelInterface    : %d (%s)\n",_gOviHwO26Info.hwDispOption.panelInterface,_ovi_o26_str_panel_interface(_gOviHwO26Info.hwDispOption.panelInterface));
			seq_printf(m, "panelBacklight    : %d (%s)\n",_gOviHwO26Info.hwDispOption.panelBacklight,_ovi_o26_str_panel_backlight(_gOviHwO26Info.hwDispOption.panelBacklight));
			seq_printf(m, "panelFramerate    : %d (%s)\n",_gOviHwO26Info.hwDispOption.panelFramerate,_ovi_o26_str_panel_framerate(_gOviHwO26Info.hwDispOption.panelFramerate));
			seq_printf(m, "dispFramerate     : %d (%s)\n",_gOviHwO26Info.hwDispOption.dispFramerate,_ovi_o26_str_panel_framerate(_gOviHwO26Info.hwDispOption.dispFramerate));
			seq_printf(m, "frcChipType       : %d (%s)\n",_gOviHwO26Info.hwDispOption.frcChipType,_ovi_o26_str_frc_chip_type(_gOviHwO26Info.hwDispOption.frcChipType));
			seq_printf(m, "isVx15Byte        : %d\n",_gOviHwO26Info.hwDispOption.isVx15Byte);
			seq_printf(m, "year_option       : %d\n",_gOviHwO26Info.hwDispOption.year_option);
			seq_printf(m, "wirelessAV        : %d\n",_gOviHwO26Info.hwDispOption.wirelessAV);
			seq_printf(m, "oled_boost_x4     : %d\n",_gOviHwO26Info.hwDispOption.oled_boost_x4);

			seq_printf(m, "\n");
			seq_printf(m, "<info>\n");
			seq_printf(m, "mute              : %d\n",_gOviHwO26Info.mute);
			seq_printf(m, "vrr_on            : %d\n",_gOviHwO26Info.vrr_on);
			seq_printf(m, "high_clk          : %d\n",_gOviHwO26Info.high_clk);
			seq_printf(m, "set_ss            : %d\n",_gOviHwO26Info.set_ss);
			seq_printf(m, "ssRegValue1       : 0x%08x\n",_gOviHwO26Info.spreadSpectrumRegValue1);
			seq_printf(m, "ssRegValue2       : 0x%08x\n",_gOviHwO26Info.spreadSpectrumRegValue2);
			seq_printf(m, "ssRegValue3       : 0x%08x\n",_gOviHwO26Info.spreadSpectrumRegValue3);

			seq_printf(m, "\n");
			seq_printf(m, "<clk_ctrl>\n");
			seq_printf(m, "crg_hdr004_cur    : 0x%08x\n",_gOviHwO26Info.crg_hdr004_cur);
			seq_printf(m, "crg_hdr004_org    : 0x%08x\n",_gOviHwO26Info.crg_hdr004_org);
			seq_printf(m, "clk_ctrl.type     : %d\n",_gOviHwO26Info.clk_ctrl.type);
			seq_printf(m, "clk_ctrl.src      : %d\n",_gOviHwO26Info.clk_ctrl.src);
			seq_printf(m, "clk_ctrl.vrr      : %d\n",_gOviHwO26Info.clk_ctrl.vrr);
			CTOP_CTRL_O26Ax_RdFL(SCRG_CTRL_HDR,crg_hdr004);
			val = CTOP_CTRL_O26Ax_Rd(SCRG_CTRL_HDR,crg_hdr004);
			seq_printf(m, "Rd(crg_hdr004)    : 0x%08x\n",val);
		}
		break;
		case OVI_HAL_PROC_ID_DISP_OUTPUT_INFO:
		{
			char *iface[LX_OVI_PANEL_INTERFACE_MAX] = {"LVDS","EPI","EPI_QSAC","Vx1","CEDS"};
			char *lockStatus[3] = {"Locked","Unlocked","Unknown"};
			//UINT32 reverseVal;
			UINT32 lockFlag;
			__attribute__((unused)) UINT32 regVal;

			//OVI_REG_RD(0xC930F030, regVal); // dpe_syn c4tx_ctrl NEED FIX

			if (_gOviHwO26Info.dispOption.panelInterface == LX_OVI_PANEL_VX1)
			{
				BOOLEAN bLock;
				OVI_HW_O26_GetLockStatus(&bLock);
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

			seq_printf(m, "vbe_lockStatus=%s\n", lockStatus[lockFlag]);
			seq_printf(m, "vbe_displayOutput=%s\n", _gOviHwO26Info.isDispOutDisabled ? "off" : "on");
			seq_printf(m, "vbe_outputFrameRate=%s\n", _gOviHwO26Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ ? "60" : "120");
			seq_printf(m, "vbe_panelInterface=%s\n", iface[_gOviHwO26Info.dispOption.panelInterface]);
			seq_printf(m, "vbe_mute=%s\n", _gOviHwO26Info.mute ? "on" : "off");
			seq_printf(m, "vbe_mirrorH=%s\n", _gOviHwO26Info.mirrorH ? "on" : "off");
			seq_printf(m, "vbe_mirrorV=%s\n", _gOviHwO26Info.mirrorV ? "on" : "off");
			if (_gOviHwO26Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ)
			{
				seq_printf(m, "vbe_outputFrameRate=60\n");
			}
			else if (_gOviHwO26Info.dispOption.panelFramerate == LX_OVI_PANEL_FRAMERATE_120HZ)
			{
				seq_printf(m, "vbe_outputFrameRate=120\n");
			}
			else
			{
				seq_printf(m, "vbe_outputFrameRate=144\n");
			}
			// {
			// extern BE_PQ_RPT_PCCE_T be_pq_rpt_pcce_t;
			// seq_printf(m, "vbe_PcceMsgFromFW=%s\n", be_pq_rpt_pcce_t.str);  //mhlee, pcce msg from fw
			// seq_printf(m, "vbe_PcceMsgFromFW_UI=%u\n", be_pq_rpt_pcce_t.ui);
			// seq_printf(m, "vbe_PcceMsgFromFW_En=%u\n", be_pq_rpt_pcce_t.en);
			// seq_printf(m, "vbe_PcceMsgFromFW_Status=0x%08x\n", be_pq_rpt_pcce_t.status);
			// }
			seq_printf(m, "vbe_PcceMsgFromFW=%s\n", (char*)data);	//mhlee, pcce msg from fw
		}
		break;
		case OVI_HAL_PROC_ID_MIRROR_VERTICAL_INFO:
		{
			_gOviHwO26Info.mirrorV = *((UINT32 *)data);
		}
		break;
		case OVI_HAL_PROC_ID_DRAW_PATTERN:
		{
			_gOviHwO26Info.patType = *((UINT32 *)data);
			_OVI_O26_Draw_Pat(0);
			_OVI_O26_Draw_Pat(_gOviHwO26Info.patType);
		}
		break;
		case OVI_HAL_PROC_ID_DEBUG:
		{
			OVI_PRINT("command (%s)\n", (char *)data);

			if (!strncasecmp((char *)data, "dispout mute", strlen("dispout mute"))) {
				if (strstr((char *)data,"on")) {
					OVI_HW_O26_SetDispOutMute(1);
				}
				else if (strstr((char *)data,"off")) {
					OVI_HW_O26_SetDispOutMute(0);
				}
			}
			else if (!strncasecmp((char *)data, "dispinit", strlen("dispinit"))) {
				UINT32 vrr_on = 0;
				UINT32 high_clk = 0;
				LX_OVI_DISPLAY_INFO_T dispOption;

				memcpy(&dispOption,&_gOviHwO26Info.dispOption,sizeof(LX_OVI_DISPLAY_INFO_T));

				if (strstr((char *)data,"165")) {
					dispOption.panelFramerate = LX_OVI_PANEL_FRAMERATE_165Hz;
				}
				else if (strstr((char *)data,"144")) {
					dispOption.panelFramerate = LX_OVI_PANEL_FRAMERATE_144Hz;
				}
				else if (strstr((char *)data,"120")) {
					dispOption.panelFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
				}

				if (strstr((char *)data,"oled")) {
					dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
				}
				else if (strstr((char *)data,"lcd")) {
					dispOption.panelBacklight = LX_OVI_PANEL_BACKLIGHT_EDGE_LED;
				}

				if (strstr((char *)data,"vx1")) {
					dispOption.panelInterface = LX_OVI_PANEL_VX1;
				}
				else if (strstr((char *)data,"lvds")) {
					dispOption.panelInterface = LX_OVI_PANEL_LVDS;
				}

				if (strstr((char *)data,"vrr")) {
					vrr_on = 1;
				}

				if (strstr((char *)data,"high")) {
					high_clk = 1;
				}

				_OVI_O26_DispInit(&dispOption,vrr_on,high_clk);
			}
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
