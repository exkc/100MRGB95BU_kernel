/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

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
#include "os_util.h"

#include "ovi_dbg.h"
#include "ovi_hal.h"
#include "ovi_hw_o18.h"
#include "ovi_reg_def_o18.h"
#include "ovi_reg_o18.h"

#include "../be/reg/be_reg_dpe_o18.h"

// For CTOP register access
#include "../../../core/sys/sys_regs.h"

#include "ovi_output_format_o18a0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define OVI_HW_O18_GAMMA_TABLE_SIZENUM 1024
#define OVI_HW_O18_INPUT_OD_SIZENUM (17*17)
#define OVI_HW_O18_WB_GAIN_STEP	26	// 0.26% step per w/b gain 1
#define OVI_HW_O18_WB_OFFSET_STEP 8	// 8 step per w/b offset 1
#define OVI_HW_O18_WB_DEFAULT_GAIN 16384

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


#define OVI_HW_O18_CH_POWER_REG_MASK	0x00FFFFFF

#define OVI_HW_O18_REG_PARAM_OP_WRITE		0x0
#define OVI_HW_O18_REG_PARAM_OP_WAIT		0x1
#define OVI_HW_O18_REG_PARAM_OP_CHECK		0x2
#define OVI_HW_O18_REG_PARAM_OP_RESERVED	0x3
#define OVI_HW_O18_REG_PARAM_OP_MASK		0x3

#define OVI_HW_O18_REG_SET_A0_START		0x000000A0
#define OVI_HW_O18_REG_SET_B0_START		0x000000B0
// Max Value < 0x000000A0
#define OVI_HW_O18_REG_READ_START		0x00000001
#define OVI_HW_O18_REG_CHECK_END		0x00000000

#define OVI_HW_O18_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define OVI_HW_O18_BOE_FW_SIZE 32256

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	UINT32 chPowerOnRegValue1;
	UINT32 chPowerOnRegValue2;
	UINT32 chPowerOnRegValue3;
	UINT32 tconBaseAddress;
	UINT32 spreadSpectrumRegValue;

	UINT32 wbInSelRegFieldValue;
	UINT32 dgaInSelRegFieldValue;
	UINT32 odcInSelRegFieldValue;
	UINT32 hcicInSelRegFieldValue;
	UINT32 lodcInSelRegFieldValue;
	UINT32 postDitInSelRegFieldValue;

	UINT32 horReverseRegFieldValue;	// Value for non-reverse

	LX_OVI_DISP_OUTPUT_MODE_T dispOutputMode;

	LX_OVI_DISPLAY_INFO_T dispOption;
} OVI_HW_O18_INFO_T;

typedef struct{
	LX_OVI_OUTPUT_MODE_T	*pOVIOutputModes;
	UINT32 number_of_modes;
} OVI_HW_O18_OUTPUT_MODES_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T *gpOviTconMem;

extern DPE_LED_REG_O18_T gDPE_LED_O18;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
OVI_TCON_REG_O18_T gOVI_TCON_O18;
OVI_TCON_LODC_REG_O18_T gOVI_TCON_LODC_O18;
OVI_OIF_REG_O18_T gOVI_OIF_O18;

static volatile unsigned int *gMapped_address;

LX_OVI_OUTPUT_MODE_T _gOVIOutputModes_O18Ax[] =
{
	{"Disp-O18 4k60Hz Vx1\n",  ovi_o18a0_disp_4k60_vx1_8lane, sizeof(ovi_o18a0_disp_4k60_vx1_8lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-O18 4k120Hz Vx1\n",  ovi_o18a0_disp_4k120_vx1_16lane, sizeof(ovi_o18a0_disp_4k120_vx1_16lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-O18 4k120Hz Vx1 5Byte\n",  ovi_o18a0_disp_4k120_vx1_16lane_5byte, sizeof(ovi_o18a0_disp_4k120_vx1_16lane_5byte)/sizeof(LX_OVI_REG_T)},
	{"Disp-O18 4k120Hz EPI 12LANE RGB\n",  ovi_o18a0_disp_4k120_epi_v17_12lane_rgb, sizeof(ovi_o18a0_disp_4k120_epi_v17_12lane_rgb)/sizeof(LX_OVI_REG_T)}
};

OVI_HW_O18_OUTPUT_MODES_T _gOVIOutputModes_O18 =
{
	.pOVIOutputModes 	 = NULL,
	.number_of_modes	 = 0,
};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static UINT32 _OVI_O18_GetGain(UINT32 gain);
static SINT16 _OVI_O18_GetOffset(UINT32 offset);
static void _OVI_O18_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore);
static void _OVI_O18_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);
static void _OVI_O18_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);

//static void _OVI_O18_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_O18_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_O18_DispOutputEnable(BOOLEAN bParam);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _gPrevRedGain = OVI_HW_O18_WB_DEFAULT_GAIN;
static UINT32 _gPrevGreenGain = OVI_HW_O18_WB_DEFAULT_GAIN;
static UINT32 _gPrevBlueGain = OVI_HW_O18_WB_DEFAULT_GAIN;

static SINT16 _gPrevRedOffset = 0;
static SINT16 _gPrevGreenOffset = 0;
static SINT16 _gPrevBlueOffset = 0;

static OVI_HW_O18_INFO_T _gOviHwO18Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
static void _OVI_O18_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore)
{
	if (regParamVal >= OVI_HW_O18_REG_SET_A0_START)
	{
		if (lx_chip_rev() >= LX_CHIP_REV(O18, B0))
		{
			if (regParamVal != OVI_HW_O18_REG_SET_B0_START)
			{
				*pbIgnore = TRUE;
			}
		}
		else
		{
			if (regParamVal != OVI_HW_O18_REG_SET_A0_START)
			{
				*pbIgnore = TRUE;
			}
		}
	}
	else if (regParamVal == OVI_HW_O18_REG_CHECK_END)
	{
		*pbIgnore = FALSE;
	}

	return;
}

static void _OVI_O18_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN ignore = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_O18_REG_PARAM_OP_MASK)
		{
			case OVI_HW_O18_REG_PARAM_OP_WAIT:	// wait
				if (!ignore)
				{
					OS_UsecDelay(param->value);
				}
				OVI_DEBUG("delay(_%dms);\n", param->value/1000);
				break;

			case OVI_HW_O18_REG_PARAM_OP_CHECK:	// check
				_OVI_O18_IgnoreRegSet(param->value, &ignore);
				OVI_DEBUG("ignore : %d\n", ignore);
				break;

			case OVI_HW_O18_REG_PARAM_OP_RESERVED:
				OVI_DEBUG("OVI_HW_O18_REG_PARAM_OP_RESERVED\n");
				break;

			default:	// OVI_HW_O18_REG_PARAM_OP_WRITE
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

static void _OVI_O18_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN readReg = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_O18_REG_PARAM_OP_MASK)
		{
			case OVI_HW_O18_REG_PARAM_OP_CHECK:	// check for register read
				if (param->value == OVI_HW_O18_REG_READ_START)
				{
					readReg = TRUE;
				}
				else if (param->value == OVI_HW_O18_REG_CHECK_END)
				{
					readReg = FALSE;
				}
				OVI_DEBUG("readReg : %d\n", readReg);
				break;

			default:	// OVI_HW_O18_REG_PARAM_OP_WRITE
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
static void _OVI_O18_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;
	char opt[64];

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	if ((RET_OK==OS_ScanKernelCmdline("disp=%s", opt)) && !strncmp(opt,"hdmi",4))
	{
		stDispParams.panelInterface = LX_OVI_PANEL_VX1;
		stDispParams.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
	}

	if (RET_OK==OS_ScanKernelCmdline("hwopt=%s", opt))
	{
		if (opt[1] == '0') stDispParams.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
		else if (opt[1] == '1') stDispParams.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
	}
	
	if (RET_OK==OS_ScanKernelCmdline("disp=%s", opt))
	{
		if (!strncmp(opt,"4byte",5)) stDispParams.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
		else if (!strncmp(opt,"5byte",5)) stDispParams.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
	}
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					_OVI_O18_RegParamRead(ovi_o18a0_disp_2k60_lvds_2link, 
											OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_2k60_lvds_2link), 0);
					break;
					
				case LX_OVI_PANEL_VX1:
				default :
					_OVI_O18_RegParamRead(ovi_o18a0_disp_4k60_vx1_8lane, 
											OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k60_vx1_8lane), 0);
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					_OVI_O18_RegParamRead(ovi_o18a0_disp_4k120_epi_v17_12lane_rgb, 
											OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k120_epi_v17_12lane_rgb), 0);
					break;

				case LX_OVI_PANEL_LVDS:
					_OVI_O18_RegParamRead(ovi_o18a0_disp_2k120_lvds_4link, 
											OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_2k120_lvds_4link), 0);
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						_OVI_O18_RegParamRead(ovi_o18a0_disp_4k120_vx1_16lane_5byte, 
												OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k120_vx1_16lane_5byte), 0);
					}	
					else
					{
						_OVI_O18_RegParamRead(ovi_o18a0_disp_4k120_vx1_16lane, 
												OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k120_vx1_16lane), 0);
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

#define OVI_HW_O18_OPT_BIT_MASK_STB (1<<0)
static void _OVI_O18_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;
	char opt[64];

	OVI_PRINT("\n[_OVI_O18_DispInit] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
		pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
		pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
		pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	// Display Spread Spectrum
	if(((RET_OK==OS_ScanKernelCmdline("disp=%s", opt)) && !strncmp(opt,"hdmi",4))
		|| (stDispParams.userSpecificOption.all & OVI_HW_O18_OPT_BIT_MASK_STB))
	{
		OVI_REG_WR(0xC97D0004, 0x19A04C02);
	}
	else
	{
		OVI_REG_WR(0xC97D0004, 0x19785402);
		OVI_REG_WR(0xC97D0008, 0x044088A8);
		OVI_REG_WR(0xC97D000C, 0x00000201);
		OVI_REG_WR(0xC97D0004, 0x09785402);
	}

	if (RET_OK==OS_ScanKernelCmdline("hwopt=%s", opt))
	{
		if (opt[1] == '0') stDispParams.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
		else if (opt[1] == '1') stDispParams.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;

		if ((opt[17] != '0') && (opt[17] != '1'))
		{
			stDispParams.panelInterface = LX_OVI_PANEL_VX1;
			stDispParams.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			stDispParams.frcChipType = LX_OVI_FRC_CHIP_8K_BE_URSA17;
		}
	}

	if ((RET_OK==OS_ScanKernelCmdline("disp=%s", opt)) && !strncmp(opt,"hdmi",4))
	{
		stDispParams.panelInterface = LX_OVI_PANEL_VX1;
		stDispParams.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
	}
	
	if (RET_OK==OS_ScanKernelCmdline("disp=%s", opt))
	{
		if (!strncmp(opt,"4byte",5)) stDispParams.panelBacklight = LX_OVI_PANEL_BACKLIGHT_DIRECT_L;
		else if (!strncmp(opt,"5byte",5)) stDispParams.panelBacklight = LX_OVI_PANEL_BACKLIGHT_OLED;
	}
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_LVDS:
					_OVI_O18_RegParamSet(ovi_o18a0_disp_2k60_lvds_2link, 
											OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_2k60_lvds_2link), 0);
					break;
					
				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.frcChipType == LX_OVI_FRC_CHIP_8K_BE_URSA17)
					{
						_OVI_O18_RegParamSet(ovi_o18a0_disp_4k60_vx1_10lane, 
												OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k60_vx1_10lane), 0);
					}
					else
					{
						_OVI_O18_RegParamSet(ovi_o18a0_disp_4k60_vx1_8lane, 
												OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k60_vx1_8lane), 0);
					}
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					_OVI_O18_RegParamSet(ovi_o18a0_disp_4k120_epi_v17_12lane_rgb, 
											OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k120_epi_v17_12lane_rgb), 0);
					break;

				case LX_OVI_PANEL_LVDS:
					_OVI_O18_RegParamSet(ovi_o18a0_disp_2k120_lvds_4link, 
											OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_2k120_lvds_4link), 0);
					break;

				case LX_OVI_PANEL_VX1:
				default :
					if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						_OVI_O18_RegParamSet(ovi_o18a0_disp_4k120_vx1_16lane_5byte, 
												OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k120_vx1_16lane_5byte), 0);
					}	
					else
					{
						_OVI_O18_RegParamSet(ovi_o18a0_disp_4k120_vx1_16lane, 
												OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_4k120_vx1_16lane), 0);
					}
					break;
			}
			break;

		default :
			break;
	}

	_OVI_O18_RegParamSet(ovi_o18a0_disp_preEmp_swiLvl, 
												OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_preEmp_swiLvl), 0);
	
	return;
}

static void _OVI_O18_DispOutputEnable(BOOLEAN bParam)
{
	CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr36);
	if(bParam)// display output on
	{
		CTOP_CTRL_O18A0_Wr(CTOP_DPE, ctr36, _gOviHwO18Info.chPowerOnRegValue1);
		OVI_DEBUG("[OVI] display is changed to ON status!\n");

		if ((_gOviHwO18Info.dispOutputMode == LX_OVI_DISP_OUTPUT_MODE_4K120)
			|| (_gOviHwO18Info.dispOutputMode == LX_OVI_DISP_OUTPUT_MODE_4KVRR)
			|| (_gOviHwO18Info.dispOutputMode == LX_OVI_DISP_OUTPUT_MODE_4K4K60LR))
		{
			CTOP_CTRL_O18A0_Wr01(CTOP_DPE, ctr36, c4_pdb_ch12, 0x1);
			CTOP_CTRL_O18A0_Wr01(CTOP_DPE, ctr36, c4_pdb_ch13, 0x1);
			CTOP_CTRL_O18A0_Wr01(CTOP_DPE, ctr36, c4_pdb_ch14, 0x1);
			CTOP_CTRL_O18A0_Wr01(CTOP_DPE, ctr36, c4_pdb_ch15, 0x1);
			CTOP_CTRL_O18A0_Wr01(CTOP_DPE, ctr36, c4_pdb_ch16, 0x1);
			CTOP_CTRL_O18A0_Wr01(CTOP_DPE, ctr36, c4_pdb_ch17, 0x1);
			CTOP_CTRL_O18A0_Wr01(CTOP_DPE, ctr36, c4_pdb_ch18, 0x1);
			CTOP_CTRL_O18A0_Wr01(CTOP_DPE, ctr36, c4_pdb_ch19, 0x1);
		}
	}
	else // display output off
	{
		CTOP_CTRL_O18A0_Wr(CTOP_DPE, ctr36, _gOviHwO18Info.chPowerOnRegValue1 & (~OVI_HW_O18_CH_POWER_REG_MASK));
		OVI_DEBUG("[OVI] display is changed to OFF status!\n");
	}
	CTOP_CTRL_O18A0_WrFL(CTOP_DPE, ctr36);

	if (bParam) // display output on
	{
		if (lx_chip_rev() < LX_CHIP_REV(O18, B0))
		{
			CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr02);
			CTOP_CTRL_O18A0_Wr(CTOP_DPE, ctr02, _gOviHwO18Info.chPowerOnRegValue2);
			CTOP_CTRL_O18A0_WrFL(CTOP_DPE, ctr02);
		}

		CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr34);
		CTOP_CTRL_O18A0_Wr(CTOP_DPE, ctr34, _gOviHwO18Info.chPowerOnRegValue3);
		CTOP_CTRL_O18A0_WrFL(CTOP_DPE, ctr34);
	}
	else // display output off
	{
		if (lx_chip_rev() < LX_CHIP_REV(O18, B0))
		{
			CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr02);
			CTOP_CTRL_O18A0_Wr(CTOP_DPE, ctr02, _gOviHwO18Info.chPowerOnRegValue2 & (~0x4));
			CTOP_CTRL_O18A0_WrFL(CTOP_DPE, ctr02);
		}
		
		CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr34);
		CTOP_CTRL_O18A0_Wr(CTOP_DPE, ctr34, _gOviHwO18Info.chPowerOnRegValue3 & (~0x4));
		CTOP_CTRL_O18A0_WrFL(CTOP_DPE, ctr34);
	}
	
	return;
}

int OVI_HW_O18_Initialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("OVI chip revision is set to O18 A0\n");
		
		/* Set configuration of Output mode presets, for mode change on run time */
		_gOVIOutputModes_O18.pOVIOutputModes = _gOVIOutputModes_O18Ax;
		_gOVIOutputModes_O18.number_of_modes	 = sizeof(_gOVIOutputModes_O18Ax)/sizeof(LX_OVI_OUTPUT_MODE_T);

		gOVI_TCON_O18.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_REG_O18A0_T));
		gOVI_TCON_LODC_O18.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_LODC_REG_O18A0_T));
		gOVI_OIF_O18.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_OIF_REG_O18A0_T));

		gOVI_TCON_O18.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_O18A0_BASE, sizeof(OVI_TCON_REG_O18A0_T));
		gOVI_TCON_LODC_O18.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_O18A0_BASE, sizeof(OVI_TCON_LODC_REG_O18A0_T));
		gOVI_OIF_O18.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_O18A0_BASE, sizeof(OVI_OIF_REG_O18A0_T));

		/* for copying value used in channel power on/off function */
		CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr36);
		_gOviHwO18Info.chPowerOnRegValue1 = CTOP_CTRL_O18A0_Rd(CTOP_DPE, ctr36);
		CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr02);
		_gOviHwO18Info.chPowerOnRegValue2 = CTOP_CTRL_O18A0_Rd(CTOP_DPE, ctr02);
		CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr34);
		_gOviHwO18Info.chPowerOnRegValue3 = CTOP_CTRL_O18A0_Rd(CTOP_DPE, ctr34);

		/* for copying value used in H-Reverse on/off function */
		OVI_TCON_O18_RdFL(tcon_hor_mode);
		OVI_TCON_O18_Rd01(tcon_hor_mode, hor_reverse, _gOviHwO18Info.horReverseRegFieldValue);

		/* for copying value used in spread spectrum on/off function */
		//CTOP_CTRL_O18A0_RdFL(DPE, ctop_dpe_r28);
		//_gOviHwO18Info.spreadSpectrumRegValue = CTOP_CTRL_O18A0_Rd(DPE, ctop_dpe_r28);

		/* for copying value used in bypass enable/disable function */		
		OVI_TCON_O18_RdFL(tcon_odc_opt2);
		OVI_TCON_O18_Rd01(tcon_odc_opt2, wb_in_sel, _gOviHwO18Info.wbInSelRegFieldValue);
		OVI_TCON_O18_Rd01(tcon_odc_opt2, dga_in_sel, _gOviHwO18Info.dgaInSelRegFieldValue);
		OVI_TCON_O18_Rd01(tcon_odc_opt2, odc_in_sel, _gOviHwO18Info.odcInSelRegFieldValue);
		OVI_TCON_O18_Rd01(tcon_odc_opt2, fcic_in_sel, _gOviHwO18Info.hcicInSelRegFieldValue);
		OVI_TCON_O18_Rd01(tcon_odc_opt2, lodc_in_sel, _gOviHwO18Info.lodcInSelRegFieldValue);
		OVI_TCON_O18_Rd01(tcon_odc_opt2, post_dit_in_sel, _gOviHwO18Info.postDitInSelRegFieldValue);

		/* Update pre-emphasis & swing level value used in display resume */
		_OVI_O18_RegParamRead(ovi_o18a0_disp_preEmp_swiLvl, 
											OVI_HW_O18_ARRAY_SIZE(ovi_o18a0_disp_preEmp_swiLvl), 0);

		_gOviHwO18Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		_gOviHwO18Info.tconBaseAddress = gpOviTconMem->base;
		if (!(_gOviHwO18Info.tconBaseAddress))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! O18 ODC will be disabled!\n");
			break;
		}

		OVI_TCON_O18_RdFL(tcon_base_address);
		OVI_TCON_O18_Wr(tcon_base_address, _gOviHwO18Info.tconBaseAddress);
		OVI_TCON_O18_WrFL(tcon_base_address);
	} while(0);

	return ret;
}

int OVI_HW_O18_Close(void)
{
	int ret = RET_OK;

	if(gOVI_TCON_O18.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_O18.shdw.addr);
		gOVI_TCON_O18.shdw.addr = NULL;
	}
	if(gOVI_TCON_LODC_O18.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_LODC_O18.shdw.addr);
		gOVI_TCON_LODC_O18.shdw.addr = NULL;
	}
	if(gOVI_OIF_O18.shdw.addr)
	{
		OS_Free((void *)gOVI_OIF_O18.shdw.addr);
		gOVI_OIF_O18.shdw.addr = NULL;
	}

	if (gOVI_TCON_O18.phys.addr)
	{
		iounmap((void *)gOVI_TCON_O18.phys.addr);
		gOVI_TCON_O18.phys.addr = NULL;
	}
	if (gOVI_TCON_LODC_O18.phys.addr)
	{
		iounmap((void *)gOVI_TCON_LODC_O18.phys.addr);
		gOVI_TCON_LODC_O18.phys.addr = NULL;
	}
	if (gOVI_OIF_O18.phys.addr)
	{
		iounmap((void *)gOVI_OIF_O18.phys.addr);
		gOVI_OIF_O18.phys.addr = NULL;
	}

	return ret;
}

int OVI_HW_O18_Resume(void)
{
	int ret = RET_OK;

	do {
		CTOP_CTRL_O18A0_RdFL(CTOP_DPE, ctr36);
		if (!(CTOP_CTRL_O18A0_Rd(CTOP_DPE, ctr36) & OVI_HW_O18_CH_POWER_REG_MASK)) // Instant boot
		{
			_OVI_O18_DispInit(&_gOviHwO18Info.dispOption);
		}

		_gPrevRedGain = OVI_HW_O18_WB_DEFAULT_GAIN;
		_gPrevGreenGain = OVI_HW_O18_WB_DEFAULT_GAIN;
		_gPrevBlueGain = OVI_HW_O18_WB_DEFAULT_GAIN;

		_gPrevRedOffset = 0;
		_gPrevGreenOffset = 0;
		_gPrevBlueOffset = 0;

		_gOviHwO18Info.dispOutputMode = LX_OVI_DISP_OUTPUT_MODE_MAX;

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		_gOviHwO18Info.tconBaseAddress = gpOviTconMem->base;
		if (!(_gOviHwO18Info.tconBaseAddress))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! O18 ODC will be disabled!\n");
			break;
		}

		OVI_TCON_O18_RdFL(tcon_base_address);
		OVI_TCON_O18_Wr(tcon_base_address, _gOviHwO18Info.tconBaseAddress);
		OVI_TCON_O18_WrFL(tcon_base_address);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams)
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
		
		OVI_PRINT("\n[OVI_HW_O18_SetDisplayOption] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
			pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
			pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
			pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
			pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

		memcpy((void *)&_gOviHwO18Info.dispOption, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

		//_OVI_O18_DispRegDataInit(&_gOviHwO18Info.dispOption);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams)
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

		OVI_PRINT("\n[OVI_HW_O18_SetBypass] En[%d], Mask[0x%x]\n\r", pstParams->bEnable, pstParams->u32BlockMask);

		if ((pstParams->u32BlockMask & (LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC))
			&& ((pstParams->u32BlockMask & (LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC)) 
			!= (LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC)))
		{
			OVI_ERROR("[OVI] Not support for the blockMask(0x%x)!\n", pstParams->u32BlockMask);
			ret = RET_ERROR;
			break;
		}
		
		if (pstParams->u32BlockMask & (LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC))
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_O18_RdFL(tcon_odc_opt2);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, wb_in_sel, 0x0);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, dga_in_sel, 0x0);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, odc_in_sel, 0x0);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, fcic_in_sel, 0x0);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, lodc_in_sel, 0x0);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, post_dit_in_sel, 0x0);
				OVI_TCON_O18_WrFL(tcon_odc_opt2);
			}
			else
			{
				OVI_TCON_O18_RdFL(tcon_odc_opt2);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, wb_in_sel, _gOviHwO18Info.wbInSelRegFieldValue);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, dga_in_sel, _gOviHwO18Info.dgaInSelRegFieldValue);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, odc_in_sel, _gOviHwO18Info.odcInSelRegFieldValue);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, fcic_in_sel, _gOviHwO18Info.hcicInSelRegFieldValue);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, lodc_in_sel, _gOviHwO18Info.lodcInSelRegFieldValue);
				OVI_TCON_O18_Wr01(tcon_odc_opt2, post_dit_in_sel, _gOviHwO18Info.postDitInSelRegFieldValue);
				OVI_TCON_O18_WrFL(tcon_odc_opt2);
			}	
		}
	} while(0);

	return ret;
}

int OVI_HW_O18_SetCombination(UINT32 param)
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
			for(i=0; i<_gOVIOutputModes_O18.number_of_modes;i++)
			{
				printk("  Index[%d] : %s", i,_gOVIOutputModes_O18.pOVIOutputModes[i].index);
			}
			ret = RET_OK;
			break;
		}
		else if(param >= 10000)
		{
			param = param - 10000;
			printk("\n[OVI] Compare register values regarding to register-set index[%d]", param);

			if(param > _gOVIOutputModes_O18.number_of_modes) {
				OVI_ERROR("Unknown OVI index. Index was [%d]", param);
				break;
			}

			regs  = _gOVIOutputModes_O18.pOVIOutputModes[param].regs;
			count = _gOVIOutputModes_O18.pOVIOutputModes[param].count;
			index = _gOVIOutputModes_O18.pOVIOutputModes[param].index;

			printk("\n[OVI] Register Index[%d] => %s",param, (char *)index);
			for(i=0; i<count; i++){
				if (regs[i].addr == OVI_HW_O18_REG_PARAM_OP_WAIT) continue;

				if (regs[i].addr == OVI_HW_O18_REG_PARAM_OP_CHECK)
				{
					_OVI_O18_IgnoreRegSet(regs[i].value, &ignore);
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
		else if(param > _gOVIOutputModes_O18.number_of_modes) {
			OVI_ERROR("\nUnknown OVI mode. Index was [%d]\n", param);
			break;
		}

		/* Step 2. Set mode */
		regs  = _gOVIOutputModes_O18.pOVIOutputModes[param].regs;
		count = _gOVIOutputModes_O18.pOVIOutputModes[param].count;
		index = _gOVIOutputModes_O18.pOVIOutputModes[param].index;

		printk("\n[OVI] Setting to registers to register-set-index => %s", (char *)index);
		for(i=0; i<count; i++){
			if (regs[i].addr == OVI_HW_O18_REG_PARAM_OP_WAIT)
			{
				printk("\n[%03d] Delay... %dms", i, regs[i].value/1000);
				OS_UsecDelay(regs[i].value);
			}

			if (regs[i].addr == OVI_HW_O18_REG_PARAM_OP_CHECK)
			{
				_OVI_O18_IgnoreRegSet(regs[i].value, &ignore);
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

int OVI_HW_O18_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams)
{
	int ret = RET_OK;
#if 0
	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (_gOviHwO18Info.spreadSpectrumRegValue == 0xB000001C) break;

		if(pstParams->bEnable)
		{
			if (_gOviHwO18Info.spreadSpectrumRegValue == 0xB8013690) // Vx1/EPI
			{
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB8013694);
			}
			else // CEDS
			{
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB001368C);
			}
			CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r29, 0x0AA40280);
			CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r30, 0x01400000);
			CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
			CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r29);
			CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r30);

			if (_gOviHwO18Info.spreadSpectrumRegValue == 0xB8013690) // Vx1/EPI
			{
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB8013690);
			}
			else // CEDS
			{
				CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB0013688);
			}
			CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
		}
		else
		{
			CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r28, 0xB000001C);
			CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r29, 0x0AA40280);
			CTOP_CTRL_O18A0_Wr(DPE, ctop_dpe_r30, 0x01400000);
			CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r28);
			CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r29);
			CTOP_CTRL_O18A0_WrFL(DPE, ctop_dpe_r30);
		}
	} while(0);
#endif
	return ret;
}

int OVI_HW_O18_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr1 = NULL;
	volatile UINT32 *regAddr2 = NULL;
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

		odLutSizeNum = pstParams->odLut.sizeNum;

		if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
		{
			// check input table size
			if(odLutSizeNum != OVI_HW_O18_INPUT_OD_SIZENUM || pstParams->odLut.pData == NULL)
			{
				OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			// select address
			regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_O18A0_BASE + offsetof(OVI_TCON_REG_O18A0_T, tcon_odc_start_2d), 
												sizeof(UINT32)*OVI_HW_O18_INPUT_OD_SIZENUM);
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
			if(odLutSizeNum != OVI_HW_O18_INPUT_OD_SIZENUM || pstParams->odLut.pData == NULL)
			{
				OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			// select address
			regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_O18A0_BASE + offsetof(OVI_TCON_LODC_REG_O18A0_T, tcon_lodc_start_low), 
												sizeof(UINT32)*OVI_HW_O18_INPUT_OD_SIZENUM);
			if(regAddr1 == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}
		}
		else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_ON)
		{
			OVI_TCON_O18_RdFL(tcon_control);
			OVI_TCON_O18_Wr01(tcon_control, odc_en, 0x1);
			OVI_TCON_O18_WrFL(tcon_control);

			OVI_TCON_O18_RdFL(tcon_sts);
			OVI_TCON_O18_Wr01(tcon_sts, pix2_lock, 0x1);
			OVI_TCON_O18_WrFL(tcon_sts);
			break;
		}
		else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_OFF)
		{
			OVI_TCON_O18_RdFL(tcon_control);
			OVI_TCON_O18_Wr01(tcon_control, odc_en, 0x0);
			OVI_TCON_O18_WrFL(tcon_control);

			OVI_TCON_O18_RdFL(tcon_sts);
			OVI_TCON_O18_Wr01(tcon_sts, pix2_lock, 0x0);
			OVI_TCON_O18_WrFL(tcon_sts);
			break;
		}
		else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
		{
			// check input table size
			if(odLutSizeNum != (OVI_HW_O18_INPUT_OD_SIZENUM*2) || pstParams->odLut.pData == NULL)
			{
				OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			// select address
			regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_O18A0_BASE + offsetof(OVI_TCON_LODC_REG_O18A0_T, tcon_lodc_start_low), 
												sizeof(UINT32)*OVI_HW_O18_INPUT_OD_SIZENUM);
			if(regAddr1 == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}

			regAddr2 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_O18A0_BASE + offsetof(OVI_TCON_LODC_REG_O18A0_T, tcon_lodc_start_high), 
												sizeof(UINT32)*OVI_HW_O18_INPUT_OD_SIZENUM);
			if(regAddr2 == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}
		}

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

		if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
		{
			OVI_TCON_O18_RdFL(odc_lut_subpix_sel);
			OVI_TCON_O18_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x0);
			OVI_TCON_O18_WrFL(odc_lut_subpix_sel);
			
			for(i=0; i<OVI_HW_O18_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i], &regAddr1[i]);
			}

			OVI_TCON_O18_RdFL(odc_lut_subpix_sel);
			OVI_TCON_O18_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x1);
			OVI_TCON_O18_WrFL(odc_lut_subpix_sel);
			for(i=0; i<OVI_HW_O18_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i], &regAddr1[i]);
			}

			OVI_TCON_O18_RdFL(odc_lut_subpix_sel);
			OVI_TCON_O18_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x2);
			OVI_TCON_O18_WrFL(odc_lut_subpix_sel);
			for(i=0; i<OVI_HW_O18_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i], &regAddr1[i]);
			}
		}
		else
		{
			for(i=0; i<OVI_HW_O18_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i], &regAddr1[i]);
			}
		}

		if(pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
		{
			for(i=0; i<OVI_HW_O18_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i+OVI_HW_O18_INPUT_OD_SIZENUM], &regAddr2[i]);
			}
		}

		if(pstParams->eMode == LX_OVI_TCON_FRAMEOD)
		{
			OVI_TCON_O18_RdFL(odc_lut_upload);
			OVI_TCON_O18_Wr01(odc_lut_upload, odc_upload, 0x0);
			OVI_TCON_O18_WrFL(odc_lut_upload);
			OVI_TCON_O18_RdFL(odc_lut_upload);
			OVI_TCON_O18_Wr01(odc_lut_upload, odc_upload, 0x1);
			OVI_TCON_O18_WrFL(odc_lut_upload);
		}
		else
		{
			OVI_TCON_LODC_O18_RdFL(lodc_lut_upload);
			OVI_TCON_LODC_O18_Wr01(lodc_lut_upload, lodc_upload, 0x0);
			OVI_TCON_LODC_O18_WrFL(lodc_lut_upload);
			OVI_TCON_LODC_O18_RdFL(lodc_lut_upload);
			OVI_TCON_LODC_O18_Wr01(lodc_lut_upload, lodc_upload, 0x1);
			OVI_TCON_LODC_O18_WrFL(lodc_lut_upload);

			OVI_TCON_O18_RdFL(tcon_odc_opt1);
			if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				OVI_TCON_O18_Wr01(tcon_odc_opt1, lodc_en_2d, 0x1);
				OVI_TCON_O18_Wr01(tcon_odc_opt1, lodc_en_3d, 0x0);
				OVI_TCON_O18_Wr01(tcon_odc_opt1, pcid_mode, 0x3);
			}
			else  // LX_OVI_TCON_LINEOD_POD
			{
				OVI_TCON_O18_Wr01(tcon_odc_opt1, lodc_en_2d, 0x1);
				OVI_TCON_O18_Wr01(tcon_odc_opt1, lodc_en_3d, 0x0);
				OVI_TCON_O18_Wr01(tcon_odc_opt1, pcid_mode, 0x1);
				OVI_TCON_O18_Wr01(tcon_odc_opt1, pxod_order, 0x77);
			}
			OVI_TCON_O18_WrFL(tcon_odc_opt1);
		}
	} while(0);

	if(u8odLutData != NULL)
		vfree(u8odLutData);
	if(regAddr1 != NULL)
		iounmap((void *)regAddr1);
	if(regAddr2 != NULL)
		iounmap((void *)regAddr2);

	return ret;
}

int OVI_HW_O18_SetFrameOdcEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	
	do {
		// check TCON base address
		if (bParam && !(_gOviHwO18Info.tconBaseAddress))
		{
			OVI_ERROR("[OVI] TCON base address is Null!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_TCON_O18_RdFL(tcon_control);
		if(bParam)
			OVI_TCON_O18_Wr01(tcon_control, odc_en, 0x1);
		else
			OVI_TCON_O18_Wr01(tcon_control, odc_en, 0x0);
		OVI_TCON_O18_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_O18_SetColorTempEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_O18_RdFL(led_wb2p_en);
		if(bParam)
			DPE_LED_O18_Wr01(led_wb2p_en, wb2p_en, 0x1);
		else
			DPE_LED_O18_Wr01(led_wb2p_en, wb2p_en, 0x0);
		DPE_LED_O18_WrFL(led_wb2p_en);
	} while (0);

	return ret;
}

int OVI_HW_O18_SetGammaEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_O18_RdFL(led_dpg_en);
		if(bParam)
			DPE_LED_O18_Wr01(led_dpg_en, dpg_en, 0x1);
		else
			DPE_LED_O18_Wr01(led_dpg_en, dpg_en, 0x0);
		DPE_LED_O18_WrFL(led_dpg_en);
	} while (0);

	return ret;
}

int OVI_HW_O18_SetDitherEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	
	do {
		OVI_TCON_O18_RdFL(tcon_control);
		if(bParam)
		{
			OVI_TCON_O18_Wr01(tcon_control, post_dither_en, 0x1);
		}
		else
		{
			OVI_TCON_O18_Wr01(tcon_control, post_dither_en, 0x0);
		}
		OVI_TCON_O18_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_O18_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		/* Do Nothing */
	} while(0);

	return ret;
}

int OVI_HW_O18_SetDitherMode(LX_OVI_TCON_DITHER_T enParam)
{
	int ret = RET_OK;
	
	do {
		//Dither Enable
		OVI_TCON_O18_RdFL(tcon_control);
		OVI_TCON_O18_Wr01(tcon_control, post_dither_en, 0x1);
		OVI_TCON_O18_WrFL(tcon_control);
		
		OVI_TCON_O18_RdFL(tcon_dither_carry);
		switch(enParam)
		{
			case LX_OVI_TCON_DITHER_TRUNC:
				OVI_TCON_O18_Wr01(tcon_dither_carry, post_dither_sel, 0x0);
				break;
			case LX_OVI_TCON_DITHER_ROUND:
				OVI_TCON_O18_Wr01(tcon_dither_carry, post_dither_sel, 0x1);
				break;
			case LX_OVI_TCON_DITHER_RANDOM:
			default :
				OVI_TCON_O18_Wr01(tcon_dither_carry, post_dither_sel, 0x2);
				break;
		}
		OVI_TCON_O18_WrFL(tcon_dither_carry);
	} while(0);

	return ret;
}

static UINT32 _OVI_O18_GetGain(UINT32 gain)
{
	UINT32 ret_gain;
	UINT32 temp;

	temp = 10000 + (gain - 192) * OVI_HW_O18_WB_GAIN_STEP;
	ret_gain = (temp * OVI_HW_O18_WB_DEFAULT_GAIN) / 10000;

	return ret_gain;
}

static SINT16 _OVI_O18_GetOffset(UINT32 offset)
{
	SINT16 ret_offset;

	ret_offset = ((SINT32)offset - 64) * OVI_HW_O18_WB_OFFSET_STEP;
	return ret_offset;
}

int OVI_HW_O18_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams)
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

		// W/B Enable
		DPE_LED_O18_RdFL(led_wb2p_en);
		DPE_LED_O18_Wr01(led_wb2p_en, wb2p_en, 0x1);
		DPE_LED_O18_WrFL(led_wb2p_en);
		
		r_gain = _OVI_O18_GetGain(pstParams->r_gain);
		g_gain = _OVI_O18_GetGain(pstParams->g_gain);
		b_gain = _OVI_O18_GetGain(pstParams->b_gain);

		rOffset = _OVI_O18_GetOffset(pstParams->r_offset);
		gOffset = _OVI_O18_GetOffset(pstParams->g_offset);
		bOffset = _OVI_O18_GetOffset(pstParams->b_offset);

		if((_gPrevRedGain == r_gain) && (_gPrevGreenGain == g_gain) && (_gPrevBlueGain == b_gain)
			&& (_gPrevRedOffset == rOffset) && (_gPrevGreenOffset == gOffset) && (_gPrevBlueOffset == bOffset))
		{
			return RET_OK;
		}

		// Set red gain
		DPE_LED_O18_RdFL(led_wb2p_r_gain);
		DPE_LED_O18_Wr(led_wb2p_r_gain, r_gain);
		DPE_LED_O18_WrFL(led_wb2p_r_gain);

		// Set red offset
		DPE_LED_O18_RdFL(led_wb2p_r_offset);
		DPE_LED_O18_Wr(led_wb2p_r_offset, rOffset);
		DPE_LED_O18_WrFL(led_wb2p_r_offset);

		// Set green gain
		DPE_LED_O18_RdFL(led_wb2p_g_gain);
		DPE_LED_O18_Wr(led_wb2p_g_gain, g_gain);
		DPE_LED_O18_WrFL(led_wb2p_g_gain);

		// Set green offset
		DPE_LED_O18_RdFL(led_wb2p_g_offset);
		DPE_LED_O18_Wr(led_wb2p_g_offset, gOffset);
		DPE_LED_O18_WrFL(led_wb2p_g_offset);

		// Set blue gain
		DPE_LED_O18_RdFL(led_wb2p_b_gain);
		DPE_LED_O18_Wr(led_wb2p_b_gain, b_gain);
		DPE_LED_O18_WrFL(led_wb2p_b_gain);

		// Set blue offset
		DPE_LED_O18_RdFL(led_wb2p_b_offset);
		DPE_LED_O18_Wr(led_wb2p_b_offset, bOffset);
		DPE_LED_O18_WrFL(led_wb2p_b_offset);

		_gPrevRedGain = r_gain;
		_gPrevGreenGain = g_gain;
		_gPrevBlueGain = b_gain;
		_gPrevRedOffset = rOffset;
		_gPrevGreenOffset = gOffset;
		_gPrevBlueOffset = bOffset;

	} while(0);

	return ret;
}

int OVI_HW_O18_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams)
{
	int ret = RET_OK;
	UINT32 *rGammaTable = NULL;
	UINT32 *gGammaTable = NULL;
	UINT32 *bGammaTable = NULL;
	int i;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if((pstParams->rGammaLut.sizeNum != OVI_HW_O18_GAMMA_TABLE_SIZENUM)
		|| (pstParams->gGammaLut.sizeNum != OVI_HW_O18_GAMMA_TABLE_SIZENUM)
		|| (pstParams->bGammaLut.sizeNum != OVI_HW_O18_GAMMA_TABLE_SIZENUM))
		{
			OVI_ERROR("[OVI] Gamma table size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		rGammaTable = (UINT32 *)vmalloc(OVI_HW_O18_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		gGammaTable = (UINT32 *)vmalloc(OVI_HW_O18_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		bGammaTable = (UINT32 *)vmalloc(OVI_HW_O18_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		ret = copy_from_user(rGammaTable, (void __user *)pstParams->rGammaLut.pData, OVI_HW_O18_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		ret |= copy_from_user(gGammaTable, (void __user *)pstParams->gGammaLut.pData, OVI_HW_O18_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		ret |= copy_from_user(bGammaTable, (void __user *)pstParams->bGammaLut.pData, OVI_HW_O18_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		DPE_LED_O18_RdFL(led_dpg_lut_wdata);

		/* Setting Red Gamma Table */
		for(i=0; i<OVI_HW_O18_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_wdata, rGammaTable[i] & 0x7FFF);
			DPE_LED_O18_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Green Gamma Table */
		for(i=0; i<OVI_HW_O18_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_wdata, gGammaTable[i] & 0x7FFF);
			DPE_LED_O18_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Blue Gamma Table */
		for(i=0; i<OVI_HW_O18_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_O18_Wr01(led_dpg_lut_wdata, dpg_wdata, bGammaTable[i] & 0x7FFF);
			DPE_LED_O18_WrFL(led_dpg_lut_wdata);
		}

		DPE_LED_O18_RdFL(led_dpg_lut_wr_done);
		DPE_LED_O18_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
		DPE_LED_O18_WrFL(led_dpg_lut_wr_done);

		// Gamma Enable
		DPE_LED_O18_RdFL(led_dpg_en);
		DPE_LED_O18_Wr01(led_dpg_en, dpg_en, 0x1);
		DPE_LED_O18_WrFL(led_dpg_en);
	} while(0);

	if(rGammaTable != NULL)
		vfree(rGammaTable);
	if(gGammaTable != NULL)
		vfree(gGammaTable);
	if(bGammaTable != NULL)
		vfree(bGammaTable);

	return ret;
}

int OVI_HW_O18_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	UINT32 u32odcAddr=0;
	volatile UINT32 *pMappedAddr = NULL;

	do {
		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_FRAMEOD:
				u32odcAddr = OVI_TCON_REG_O18A0_BASE + offsetof(OVI_TCON_REG_O18A0_T, tcon_odc_start_2d);
				break;
			case LX_OVI_TCON_LINEOD_PCID:
				u32odcAddr = OVI_TCON_LODC_REG_O18A0_BASE + offsetof(OVI_TCON_LODC_REG_O18A0_T, tcon_lodc_start_low);
				break;
			default:
				break;
		}

		pstParams->odLut.sizeNum = OVI_HW_O18_INPUT_OD_SIZENUM;

		pMappedAddr = (volatile UINT32 *)ioremap(u32odcAddr, sizeof(UINT32)*OVI_HW_O18_INPUT_OD_SIZENUM);
		if(pMappedAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			break;
		}

		ret = copy_to_user((void __user *)pstParams->odLut.pData, (void*)pMappedAddr, sizeof(UINT32)*OVI_HW_O18_INPUT_OD_SIZENUM);
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

int OVI_HW_O18_SetTconReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	UINT32 regField;

	do {
		OVI_TCON_O18_RdFL(tcon_control);
		OVI_TCON_O18_Rd01(tcon_control, epi_out, regField);
		if (!regField) break;
		
		OVI_TCON_O18_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_O18_Wr01(tcon_hor_mode, hor_reverse, _gOviHwO18Info.horReverseRegFieldValue ? 0 : 1);
		}
		else {
			OVI_TCON_O18_Wr01(tcon_hor_mode, hor_reverse, _gOviHwO18Info.horReverseRegFieldValue);
		}
		OVI_TCON_O18_WrFL(tcon_hor_mode);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetLvdsReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	UINT32 regField;

	do {
		OVI_TCON_O18_RdFL(tcon_control);
		OVI_TCON_O18_Rd01(tcon_control, epi_out, regField);
		if (regField) break;
		
		OVI_TCON_O18_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_O18_Wr01(tcon_hor_mode, hor_reverse, 0x1);
		}
		else {
			OVI_TCON_O18_Wr01(tcon_hor_mode, hor_reverse, 0x0);
		}
		OVI_TCON_O18_WrFL(tcon_hor_mode);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O18_RdFL(tcon_pgen_ctl);

		// pattern source color setting
		OVI_TCON_O18_RdFL(tcon_pgen_agpr1);
		OVI_TCON_O18_Wr(tcon_pgen_agpr1, 0x03FF);
		OVI_TCON_O18_WrFL(tcon_pgen_agpr1);

		OVI_TCON_O18_RdFL(tcon_pgen_agpg1);
		OVI_TCON_O18_Wr(tcon_pgen_agpg1, 0x03FF);
		OVI_TCON_O18_WrFL(tcon_pgen_agpg1);

		OVI_TCON_O18_RdFL(tcon_pgen_agpb1);
		OVI_TCON_O18_Wr(tcon_pgen_agpb1, 0x03FF);
		OVI_TCON_O18_WrFL(tcon_pgen_agpb1);

		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_TPG_OFF:		// pattern off
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x0);
				break;
			case LX_OVI_TCON_TPG_BLACK:		// black pattern
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_mode, 0x4);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_WHITE:		// white pattern
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HVBAR:		// HVBar pattern
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_mode, 0x3);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR16GREY:		// Horizontal 16 grey pattern
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_mode, 0x8);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR64GREY:		// Horizontal 64 grey pattern
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_mode, 0x7);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR256GREY:		// Horizontal 256 grey pattern
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_mode, 0x6);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR1024GREY:		// Horizontal 1024 grey pattern
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_mode, 0x5);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_VER16GREY:		// Vertical 16 grey pattern
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_mode, 0xC);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_O18_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default :
				break;
		}
		OVI_TCON_O18_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetChannelPower(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		_OVI_O18_DispOutputEnable(bParam);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O18_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_LVDS_OUT_JEIDA:
				OVI_OIF_O18_Wr01(oif_lvds_config0, lvds_lsb_first, 0x0);
				break;
			case LX_OVI_LVDS_OUT_VESA:
				OVI_OIF_O18_Wr01(oif_lvds_config0, lvds_lsb_first, 0x1);
				break;
			default:
				break;
		}
		OVI_OIF_O18_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O18_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_8BIT:
				OVI_OIF_O18_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x1);
				break;
			case LX_OVI_10BIT:
				OVI_OIF_O18_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x0);
				break;
			default:
				break;
		}
		OVI_OIF_O18_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetLvdsBlack(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_O18_RdFL(oif_lvds_config1);
		OVI_OIF_O18_RdFL(oif_lvds_config2);
		OVI_OIF_O18_RdFL(oif_vx1_config3);
		OVI_OIF_O18_RdFL(oif_vx1_config4);

		if(!bParam) // original data out
		{
			OVI_OIF_O18_Wr01(oif_lvds_config1, lvds_force_even_data, 0x0);
			OVI_OIF_O18_Wr01(oif_lvds_config2, lvds_force_odd_data, 0x0);

			OVI_OIF_O18_Wr01(oif_vx1_config3, vx1_force_even_data, 0x0);
			OVI_OIF_O18_Wr01(oif_vx1_config4, vx1_force_odd_data, 0x0);
		}
		else // black data out
		{
			OVI_OIF_O18_Wr01(oif_lvds_config1, lvds_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_O18_Wr01(oif_lvds_config2, lvds_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);

			OVI_OIF_O18_Wr01(oif_vx1_config3, vx1_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_O18_Wr01(oif_vx1_config4, vx1_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);
		}
		OVI_OIF_O18_WrFL(oif_lvds_config1);
		OVI_OIF_O18_WrFL(oif_lvds_config2);
		OVI_OIF_O18_WrFL(oif_vx1_config3);
		OVI_OIF_O18_WrFL(oif_vx1_config4);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetClock(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_O18_RdFL(tcon_gclk_control);
		OVI_TCON_O18_RdFL(tcon_mclk_control);

		if(bParam)
		{
			OVI_TCON_O18_Wr01(tcon_gclk_control, gclk_en, 0x1);
			OVI_TCON_O18_Wr01(tcon_mclk_control, mclk_en, 0x1);
		}
		else
		{
			OVI_TCON_O18_Wr01(tcon_gclk_control, gclk_en, 0x0);
			OVI_TCON_O18_Wr01(tcon_mclk_control, mclk_en, 0x0);
		}

		OVI_TCON_O18_WrFL(tcon_gclk_control);
		OVI_TCON_O18_WrFL(tcon_mclk_control);
	} while(0);

	return ret;
}

int OVI_HW_O18_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam)
{
	int ret = RET_OK;
	char opt[64];

	do {
		OVI_PRINT("\n[OVI_HW_O18_SetDispOutputMode]enParam : %d\n\r", enParam);
			
		if (RET_OK==OS_ScanKernelCmdline("hwopt=%s", opt))
		{
			if ((opt[17] != '0') && (opt[17] != '1'))
			{
				OVI_TCON_O18_RdFL(tcon_odc_opt2);
				OVI_TCON_O18_RdFL(tcon_ddiv_mode);
				OVI_OIF_O18_RdFL(oif_vx1_lane_sel1);
				OVI_OIF_O18_RdFL(oif_vx1_lane_sel2);
				OVI_OIF_O18_RdFL(oif_vx1_lane_sel3);
				OVI_OIF_O18_RdFL(oif_vx1_lane_sel4);
				CTOP_CTRL_O18A0_RdFL(CTRL_TCON, crg_tcon01);
				CTOP_CTRL_O18A0_RdFL(CTRL_LED, crg_led01);
				CTOP_CTRL_O18A0_RdFL(CTRL_CCO, crg_cco01);
				CTOP_CTRL_O18A0_RdFL(CTRL_VSD, crg_vsd01);
				switch(enParam)
				{
					case LX_OVI_DISP_OUTPUT_MODE_4K60:
						OVI_TCON_O18_Wr01(tcon_odc_opt2, ddiv_in_sel, 0x0);
						OVI_TCON_O18_Wr01(tcon_ddiv_mode, lane_num, 0x8);
						OVI_TCON_O18_Wr01(tcon_ddiv_mode, division, 0x1);

						OVI_OIF_O18_Wr(oif_vx1_lane_sel1, 0x00010203);
						OVI_OIF_O18_Wr(oif_vx1_lane_sel2, 0x04050607);
						OVI_OIF_O18_Wr(oif_vx1_lane_sel3, 0x00010203);
						OVI_OIF_O18_Wr(oif_vx1_lane_sel4, 0x04050607);

						CTOP_CTRL_O18A0_Wr01(CTRL_TCON, crg_tcon01, tcon_pix2_clk_sel, 0x1);
						CTOP_CTRL_O18A0_Wr01(CTRL_TCON, crg_tcon01, tcon_fcic_clk_sel, 0x1);
						CTOP_CTRL_O18A0_Wr01(CTRL_TCON, crg_tcon01, tcon_clk_sel, 0x1);
						CTOP_CTRL_O18A0_Wr01(CTRL_LED, crg_led01, led_pxl_clk_sel, 0x1);
						CTOP_CTRL_O18A0_Wr01(CTRL_CCO, crg_cco01, disp_dsc_clk_sel, 0x1);
						CTOP_CTRL_O18A0_Wr01(CTRL_CCO, crg_cco01, disp_clk_sel, 0x1);
						CTOP_CTRL_O18A0_Wr01(CTRL_CCO, crg_cco01, disp_osd_clk_sel, 0x1);
						CTOP_CTRL_O18A0_Wr01(CTRL_VSD, crg_vsd01, disp_stb_clk_sel, 0x1);
						CTOP_CTRL_O18A0_Wr01(CTRL_VSD, crg_vsd01, det_clk_sel, 0x1);
						break;
						
					case LX_OVI_DISP_OUTPUT_MODE_4K120:
					case LX_OVI_DISP_OUTPUT_MODE_4KVRR:
					case LX_OVI_DISP_OUTPUT_MODE_4K4K60LR:
						if (enParam == LX_OVI_DISP_OUTPUT_MODE_4K4K60LR)
						{
							OVI_TCON_O18_Wr01(tcon_odc_opt2, ddiv_in_sel, 0x2);
							OVI_TCON_O18_Wr01(tcon_ddiv_mode, division, 0x2);
						}
						else
						{
							OVI_TCON_O18_Wr01(tcon_odc_opt2, ddiv_in_sel, 0x0);
							OVI_TCON_O18_Wr01(tcon_ddiv_mode, division, 0x1);
						}
						OVI_TCON_O18_Wr01(tcon_ddiv_mode, lane_num, 0x10);

						if (enParam == LX_OVI_DISP_OUTPUT_MODE_4K4K60LR)
						{
							OVI_OIF_O18_Wr(oif_vx1_lane_sel1, 0x00020406);
							OVI_OIF_O18_Wr(oif_vx1_lane_sel2, 0x080A0C0E);
							OVI_OIF_O18_Wr(oif_vx1_lane_sel3, 0x01030507);
							OVI_OIF_O18_Wr(oif_vx1_lane_sel4, 0x090B0D0F);
						}
						else
						{
							OVI_OIF_O18_Wr(oif_vx1_lane_sel1, 0x00010203);
							OVI_OIF_O18_Wr(oif_vx1_lane_sel2, 0x04050607);
							OVI_OIF_O18_Wr(oif_vx1_lane_sel3, 0x08090A0B);
							OVI_OIF_O18_Wr(oif_vx1_lane_sel4, 0x0C0D0E0F);
						}

						CTOP_CTRL_O18A0_Wr01(CTRL_TCON, crg_tcon01, tcon_pix2_clk_sel, 0x0);
						CTOP_CTRL_O18A0_Wr01(CTRL_TCON, crg_tcon01, tcon_fcic_clk_sel, 0x0);
						CTOP_CTRL_O18A0_Wr01(CTRL_TCON, crg_tcon01, tcon_clk_sel, 0x0);
						CTOP_CTRL_O18A0_Wr01(CTRL_LED, crg_led01, led_pxl_clk_sel, 0x0);
						CTOP_CTRL_O18A0_Wr01(CTRL_CCO, crg_cco01, disp_dsc_clk_sel, 0x0);
						CTOP_CTRL_O18A0_Wr01(CTRL_CCO, crg_cco01, disp_clk_sel, 0x0);
						CTOP_CTRL_O18A0_Wr01(CTRL_CCO, crg_cco01, disp_osd_clk_sel, 0x0);
						CTOP_CTRL_O18A0_Wr01(CTRL_VSD, crg_vsd01, disp_stb_clk_sel, 0x0);
						CTOP_CTRL_O18A0_Wr01(CTRL_VSD, crg_vsd01, det_clk_sel, 0x0);
						break;
					
					default:
						break;
				}
				OVI_TCON_O18_WrFL(tcon_odc_opt2);
				OVI_TCON_O18_WrFL(tcon_ddiv_mode);
				OVI_OIF_O18_WrFL(oif_vx1_lane_sel1);
				OVI_OIF_O18_WrFL(oif_vx1_lane_sel2);
				OVI_OIF_O18_WrFL(oif_vx1_lane_sel3);
				OVI_OIF_O18_WrFL(oif_vx1_lane_sel4);
				CTOP_CTRL_O18A0_WrFL(CTRL_TCON, crg_tcon01);
				CTOP_CTRL_O18A0_WrFL(CTRL_LED, crg_led01);
				CTOP_CTRL_O18A0_WrFL(CTRL_CCO, crg_cco01);
				CTOP_CTRL_O18A0_WrFL(CTRL_VSD, crg_vsd01);

				_gOviHwO18Info.dispOutputMode = enParam;
			}
		}
	} while(0);

	return ret;
}

int OVI_HW_O18_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams)
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
		
		if (memcmp(&_gOviHwO18Info.dispOption, pstParams, sizeof(LX_OVI_DISPLAY_INFO_T)) != 0)
		{
			OVI_PRINT("\n[OVI_HW_O18_DisplayResume] WARN:Disp Option Changed! [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
				pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
				pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
				pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
				pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);
		}

		_OVI_O18_DispOutputEnable(TRUE);
	} while(0);

	return ret;
}

int OVI_HW_O18_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int	i;
	UINT32 val;

	switch(proc_id)
	{
		case OVI_HAL_PROC_ID_DETAIL_INFO:
		{
			OVI_TCON_O18_RdFL(tcon_base_address);
			val = OVI_TCON_O18_Rd(tcon_base_address);
			seq_printf(m, "tcon_base_addr: 0x%08x\n", val);

			seq_printf(m, "ch_power_on_reg1: 0x%08x\n", _gOviHwO18Info.chPowerOnRegValue1 );

			for (i=0; i<_gOVIOutputModes_O18.number_of_modes; i++)
			{
				seq_printf(m, "output_mode%d: %s", i, _gOVIOutputModes_O18.pOVIOutputModes[i].index + strlen("Display settings for O18"));
			}

			OVI_OIF_O18_RdFL(oif_lvds_config0);

			OVI_OIF_O18_Rd01(oif_lvds_config0, lvds_lsb_first, val);
			seq_printf(m, "lvds.format: %s (0x%x)\n", (val)?"vesa":"jeida", val);

			OVI_OIF_O18_Rd01(oif_lvds_config0, lvds_8bit_mode, val);
			seq_printf(m, "lvds.bit: %d bit (0x%x)\n", (val)? 8:10, val);

			OVI_OIF_O18_RdFL(oif_lvds_config1);
			OVI_OIF_O18_Rd01(oif_lvds_config1, lvds_force_even_data, val);
			seq_printf(m, "lvds.black_out: %s (0x%x)\n", (val)? "black":"orignal", val);

			OVI_TCON_O18_RdFL(tcon_gclk_control);
			OVI_TCON_O18_Rd01(tcon_gclk_control, gclk_en, val);
			seq_printf(m, "tcon.gclk: %s (0x%x)\n", (val)?"on":"off", val);

			OVI_TCON_O18_RdFL(tcon_mclk_control);
			OVI_TCON_O18_Rd01(tcon_mclk_control, mclk_en, val);
			seq_printf(m, "tcon.mclk: %s (0x%x)\n", (val)?"on":"off", val);
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
