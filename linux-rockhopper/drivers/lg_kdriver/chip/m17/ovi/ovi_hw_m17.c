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
 *  date		2016.05.03
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
#include "ovi_hw_m17.h"
#include "ovi_reg_def_m17.h"
#include "ovi_reg_m17.h"

#include "../be/reg/be_reg_dpe_m17.h"

// For CTOP register access
#include "../../../core/sys/sys_regs.h"

#include "ovi_output_format_m17a0.h"
#include "ovi_output_format_m17c0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define OVI_HW_M17_GAMMA_TABLE_SIZENUM 1024
#define OVI_HW_M17_LGD_MPLUS_LUT_SIZENUM 464
#define OVI_HW_M17_BOE_MPLUS_LUT_SIZENUM 256
#define OVI_HW_M17_INPUT_OD_SIZENUM (17*17)
#define OVI_HW_M17_INPUT_POD2_SIZENUM (482)
#define OVI_HW_M17_INPUT_TSCIC_CTRL_SIZENUM (662)
#define OVI_HW_M17_INPUT_TSCIC_DATA_SIZE (377612)
#define OVI_HW_M17_INPUT_VCOM_PAT_DATA_SIZE (96)
#define OVI_HW_M17_WB_GAIN_STEP	26	// 0.26% step per w/b gain 1
#define OVI_HW_M17_WB_OFFSET_STEP 8	// 8 step per w/b offset 1
#define OVI_HW_M17_WB_DEFAULT_GAIN 16384

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


#define OVI_HW_M17_CH_POWER_REG_MASK	0x0FFF0000

#define OVI_HW_M17_REG_PARAM_OP_WRITE		0x0
#define OVI_HW_M17_REG_PARAM_OP_WAIT		0x1
#define OVI_HW_M17_REG_PARAM_OP_CHECK		0x2
#define OVI_HW_M17_REG_PARAM_OP_RESERVED	0x3
#define OVI_HW_M17_REG_PARAM_OP_MASK		0x3

#define OVI_HW_M17_REG_SET_A0_START		0x000000A0
#define OVI_HW_M17_REG_SET_B0_START		0x000000B0
// Max Value < 0x000000A0
#define OVI_HW_M17_REG_READ_START		0x00000001
#define OVI_HW_M17_REG_CHECK_END		0x00000000

#define OVI_HW_M17_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define OVI_HW_M17_BOE_FW_SIZENUM 32256

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	UINT32 chPowerOnRegValue1;
	UINT32 chPowerOnRegValue2;
	UINT32 tconBaseAddress;
	UINT32 spreadSpectrumRegValue;

	UINT32 wbInSelRegFieldValue;
	UINT32 dgaInSelRegFieldValue;
	UINT32 odcInSelRegFieldValue;
	UINT32 hcicInSelRegFieldValue;
	UINT32 lodcInSelRegFieldValue;
	UINT32 postDitInSelRegFieldValue;

	UINT32 horReverseRegFieldValue;	// Value for non-reverse

	UINT32 tconClkGatingRegValue1;
	UINT32 tconClkGatingRegValue2;

	LX_OVI_DISPLAY_INFO_T dispOption;

	struct task_struct* tscicThread;
	BOOLEAN tscicWritingFlag;
	UINT32 tscicSize;
	UINT32 *tscicTbl;
} OVI_HW_M17_INFO_T;

typedef struct{
	LX_OVI_OUTPUT_MODE_T	*pOVIOutputModes;
	UINT32 number_of_modes;
} OVI_HW_M17_OUTPUT_MODES_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T *gpOviTconMem;

extern DPE_LED_REG_M17_T gDPE_LED_M17;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
OVI_TCON_REG_M17_T gOVI_TCON_M17;
OVI_TCON_LODC_REG_M17_T gOVI_TCON_LODC_M17;
OVI_TCON_CAD_REG_M17_T gOVI_TCON_CAD_M17;
OVI_OIF_REG_M17_T gOVI_OIF_M17;
OVI_WPR_REG_M17_T gOVI_WPR_M17;

static volatile unsigned int *gMapped_address;

LX_OVI_OUTPUT_MODE_T _gOVIOutputModes_M17Ax[] =
{
	{"Disp-M17 4k60Hz Vx1\n",  ovi_m17a0_disp_4k60_vx1_8lane, sizeof(ovi_m17a0_disp_4k60_vx1_8lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k120Hz Vx1\n",  ovi_m17a0_disp_4k120_vx1_16lane, sizeof(ovi_m17a0_disp_4k120_vx1_16lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k60Hz EPI 6LANE RGBW\n",  ovi_m17a0_disp_4k60_epi_6lane_rgbw, sizeof(ovi_m17a0_disp_4k60_epi_6lane_rgbw)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k120Hz EPI 12LANE RGB\n",  ovi_m17a0_disp_4k120_epi_12lane_rgb, sizeof(ovi_m17a0_disp_4k120_epi_12lane_rgb)/sizeof(LX_OVI_REG_T)},	
	{"Disp-M17 4k120Hz EPI 24LANE RGB\n",  ovi_m17a0_disp_4k120_epi_24lane_rgb, sizeof(ovi_m17a0_disp_4k120_epi_24lane_rgb)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k120Hz EPI 12LANE RGBW\n",  ovi_m17a0_disp_4k120_epi_12lane_rgbw, sizeof(ovi_m17a0_disp_4k120_epi_12lane_rgbw)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k60Hz CEDS 12LANE RGBW\n",  ovi_m17a0_disp_4k60_ceds_12lane_rgbw, sizeof(ovi_m17a0_disp_4k60_ceds_12lane_rgbw)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k60Hz EPI V16 12LANE RGBW\n",  ovi_m17a0_disp_4k60_epi_v16_12lane_rgbw, sizeof(ovi_m17a0_disp_4k60_epi_v16_12lane_rgbw)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k120Hz EPI V16 24LANE RGB\n",  ovi_m17a0_disp_4k120_epi_v16_24lane_rgb, sizeof(ovi_m17a0_disp_4k120_epi_v16_24lane_rgb)/sizeof(LX_OVI_REG_T)}
};

LX_OVI_OUTPUT_MODE_T _gOVIOutputModes_M17Cx[] =
{
	{"Disp-M17 4k60Hz Vx1\n",  ovi_m17c0_disp_4k60_vx1_8lane, sizeof(ovi_m17c0_disp_4k60_vx1_8lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k120Hz Vx1\n",  ovi_m17c0_disp_4k120_vx1_16lane, sizeof(ovi_m17c0_disp_4k120_vx1_16lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k60Hz EPI 6LANE RGB\n",  ovi_m17c0_disp_4k60_epi_6lane_rgb, sizeof(ovi_m17c0_disp_4k60_epi_6lane_rgb)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k60Hz EPI 6LANE RGBW\n",  ovi_m17c0_disp_4k60_epi_6lane_rgbw, sizeof(ovi_m17c0_disp_4k60_epi_6lane_rgbw)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k60Hz EPI 8LANE RGB 65\n",  ovi_m17c0_disp_4k60_epi_8lane_rgb, sizeof(ovi_m17c0_disp_4k60_epi_8lane_rgb)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k60Hz EPI 8LANE RGBW 65\n",  ovi_m17c0_disp_4k60_epi_8lane_rgbw, sizeof(ovi_m17c0_disp_4k60_epi_8lane_rgbw)/sizeof(LX_OVI_REG_T)},
	{"Disp-M17 4k120Hz EPI 12LANE RGB\n",  ovi_m17c0_disp_4k120_epi_12lane_rgb, sizeof(ovi_m17c0_disp_4k120_epi_12lane_rgb)/sizeof(LX_OVI_REG_T)},	
	{"Disp-M17 4k60Hz CEDS 12LANE\n",  ovi_m17c0_disp_4k60_ceds_12lane, sizeof(ovi_m17c0_disp_4k60_ceds_12lane)/sizeof(LX_OVI_REG_T)}
};

OVI_HW_M17_OUTPUT_MODES_T _gOVIOutputModes_M17 =
{
	.pOVIOutputModes 	 = NULL,
	.number_of_modes	 = 0,
};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static UINT32 _OVI_M17_GetGain(UINT32 gain);
static SINT16 _OVI_M17_GetOffset(UINT32 offset);
static void _OVI_M17_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore);
static void _OVI_M17_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);
static void _OVI_M17_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);

static void _OVI_M17_DispRegDataInit_C0(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_M17_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_M17_DispInit_C0(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_M17_DispOutputEnable(BOOLEAN bParam);

/*----------------------------------------------------------------------------------------
	Internal Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int OVI_M17_TscicWriteThread(void* data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _gPrevRedGain = OVI_HW_M17_WB_DEFAULT_GAIN;
static UINT32 _gPrevGreenGain = OVI_HW_M17_WB_DEFAULT_GAIN;
static UINT32 _gPrevBlueGain = OVI_HW_M17_WB_DEFAULT_GAIN;

static SINT16 _gPrevRedOffset = 0;
static SINT16 _gPrevGreenOffset = 0;
static SINT16 _gPrevBlueOffset = 0;

static OVI_HW_M17_INFO_T _gOviHwM17Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
static void _OVI_M17_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore)
{
	if (regParamVal >= OVI_HW_M17_REG_SET_A0_START)
	{
		if (lx_chip_rev() >= LX_CHIP_REV(M17, B0))
		{
			if (regParamVal != OVI_HW_M17_REG_SET_B0_START)
			{
				*pbIgnore = TRUE;
			}
		}
		else
		{
			if (regParamVal != OVI_HW_M17_REG_SET_A0_START)
			{
				*pbIgnore = TRUE;
			}
		}
	}
	else if (regParamVal == OVI_HW_M17_REG_CHECK_END)
	{
		*pbIgnore = FALSE;
	}

	return;
}

static void _OVI_M17_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN ignore = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_M17_REG_PARAM_OP_MASK)
		{
			case OVI_HW_M17_REG_PARAM_OP_WAIT:	// wait
				if (!ignore)
				{
					OS_UsecDelay(param->value);
				}
				OVI_DEBUG("delay(_%dms);\n", param->value/1000);
				break;

			case OVI_HW_M17_REG_PARAM_OP_CHECK:	// check
				_OVI_M17_IgnoreRegSet(param->value, &ignore);
				OVI_DEBUG("ignore : %d\n", ignore);
				break;

			case OVI_HW_M17_REG_PARAM_OP_RESERVED:
				OVI_DEBUG("OVI_HW_M17_REG_PARAM_OP_RESERVED\n");
				break;

			default:	// OVI_HW_M17_REG_PARAM_OP_WRITE
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

static void _OVI_M17_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN readReg = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_M17_REG_PARAM_OP_MASK)
		{
			case OVI_HW_M17_REG_PARAM_OP_CHECK:	// check for register read
				if (param->value == OVI_HW_M17_REG_READ_START)
				{
					readReg = TRUE;
				}
				else if (param->value == OVI_HW_M17_REG_CHECK_END)
				{
					readReg = FALSE;
				}
				OVI_DEBUG("readReg : %d\n", readReg);
				break;

			default:	// OVI_HW_M17_REG_PARAM_OP_WRITE
				if (readReg)
				{
					OVI_REG_RD((param->addr + addrOffset), param->value);

					if ((param->addr + addrOffset) == 0xC930A408 || (param->addr + addrOffset) == 0xC930A448) // CH_PDB & FLIP
					{
						param->value = param->value & (~OVI_HW_M17_CH_POWER_REG_MASK);
					}
				}
				OVI_DEBUG("REG_READ( 0x%08x, 0x%08x);\n", (param->addr + addrOffset), param->value);
				break;
		}
		
		param++;
	}
}

static void _OVI_M17_DispRegDataInit_C0(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;
	char opt[64];

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	if ((RET_OK==OS_ScanKernelCmdline("disp=%s", opt)) && !strncmp(opt,"hdmi",4))
	{
		stDispParams.panelInterface = LX_OVI_PANEL_VX1;
		stDispParams.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
	}
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
				case LX_OVI_PANEL_EPI_QSAC:
					if (stDispParams.dispOutLaneBw == LX_OVI_OUTPUT_LANE_BANDWIDTH_2_1G)
					{
						if (stDispParams.panelCellType == LX_OVI_PANEL_CELL_RGB)
						{
							_OVI_M17_RegParamRead(ovi_m17c0_disp_4k60_epi_8lane_rgb, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_epi_8lane_rgb), 0);
						}
						else
						{
							_OVI_M17_RegParamRead(ovi_m17c0_disp_4k60_epi_8lane_rgbw, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_epi_8lane_rgbw), 0);
						}
					}
					else
					{
						if (stDispParams.panelCellType == LX_OVI_PANEL_CELL_RGB)
						{
							_OVI_M17_RegParamRead(ovi_m17c0_disp_4k60_epi_6lane_rgb, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_epi_6lane_rgb), 0);
						}
						else
						{
							_OVI_M17_RegParamRead(ovi_m17c0_disp_4k60_epi_6lane_rgbw, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_epi_6lane_rgbw), 0);
						}
					}	
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M17_RegParamRead(ovi_m17c0_disp_4k60_vx1_8lane, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_vx1_8lane), 0);
					break;

				case LX_OVI_PANEL_CEDS:
					_OVI_M17_RegParamRead(ovi_m17c0_disp_4k60_ceds_12lane, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_ceds_12lane), 0);
					break;

				default :
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					_OVI_M17_RegParamRead(ovi_m17c0_disp_4k120_epi_12lane_rgb, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k120_epi_12lane_rgb), 0);
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M17_RegParamRead(ovi_m17c0_disp_4k120_vx1_16lane, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k120_vx1_16lane), 0);
					break;

				default :
					break;
			}
			break;

		default :
			break;
	}

	if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_EDGE_LED
		|| stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_DIRECT_L)
	{
		_OVI_M17_RegParamRead(ovi_m17c0_led_spi, OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_led_spi), 0);
	}

	return;
}

#define OVI_HW_M17_OPT_BIT_MASK_STB (1<<0)
static void _OVI_M17_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;
	char opt[64];
	UINT32 regVal;

	OVI_PRINT("\n[_OVI_M17_DispInit] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
		pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
		pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
		pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	// Display Spread Spectrum
	if(((RET_OK==OS_ScanKernelCmdline("disp=%s", opt)) && !strncmp(opt,"hdmi",4))
		|| (stDispParams.userSpecificOption.all & OVI_HW_M17_OPT_BIT_MASK_STB))
	{
		OVI_REG_WR(0xC930A470, 0xB000001C);
		OVI_REG_WR(0xC930A474, 0x0AA40280);
		OVI_REG_WR(0xC930A478, 0x01400000);
	}
	else
	{
		switch (stDispParams.panelInterface)
		{
			case LX_OVI_PANEL_VX1:
			case LX_OVI_PANEL_EPI:
				OVI_REG_WR(0xC930A470, 0xB8013694);
				OVI_REG_WR(0xC930A474, 0x0AA40280);
				OVI_REG_WR(0xC930A478, 0x01400000);
				OVI_REG_WR(0xC930A470, 0xB8013690);
				break;
			case LX_OVI_PANEL_CEDS:
				OVI_REG_WR(0xC930A470, 0xB001368C);
				OVI_REG_WR(0xC930A474, 0x0AA40280);
				OVI_REG_WR(0xC930A478, 0x01400000);
				OVI_REG_WR(0xC930A470, 0xB0013688);
				break;
			default :
				break;
		}
	}

	if ((RET_OK==OS_ScanKernelCmdline("disp=%s", opt)) && !strncmp(opt,"hdmi",4))
	{
		stDispParams.panelInterface = LX_OVI_PANEL_VX1;
		stDispParams.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
	}

	// DPE path setting (Picture Enhance block -> L/D)
	OVI_REG_WR(0xC902001C, 0x00000001);
	
	if ((lx_chip_rev() >= LX_CHIP_REV(M17 ,A0))
		&& (lx_chip_rev() < LX_CHIP_REV(M17 ,B0)))
	{
		// Audio Clock Disable
		OVI_REG_RD(0xC9105060, regVal);
		regVal = (regVal & (~0x40)) | (1 << 6);
		OVI_REG_WR(0xC9105060, regVal);
	}
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					if (stDispParams.panelVersion == LX_OVI_PANEL_V16)
					{
						_OVI_M17_RegParamSet(ovi_m17a0_disp_4k60_epi_v16_12lane_rgbw, 
												OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k60_epi_v16_12lane_rgbw), 0);
					}
					else
					{
						char toolOpt[128];
						int i;
						int cnt = 0;
						int to9Pos = 0;
						int endPos = 0;
						int toolOpt9 = 0;
						BOOLEAN isUh75 = FALSE;
						BOOLEAN isUh63 = FALSE;

						// Get Tool Option9 Info.
						if (RET_OK==OS_ScanKernelCmdline("ToolOpt=%s", toolOpt))
						{
							for (i=0; i<128; i++)
							{
								if (toolOpt[i] == ':')
								{
									cnt++;
									if (cnt == 8) // Tool Option9
									{
										to9Pos = i+1;
									}
								}
								else if (cnt == 8 && (toolOpt[i] < '0' || toolOpt[i] > '9'))
								{
									endPos = i-1;
									if (endPos >= to9Pos)
									{
										int tmp;
										toolOpt[endPos+1] = '\0';
										tmp = kstrtoint(&toolOpt[to9Pos], 10, &toolOpt9);
									}
									break;
								}
							}

							if ((toolOpt9 >= 0) && (((toolOpt9 >> 7) & 0x7) == 0x6))
							{
								isUh75 = TRUE;
							}
							else if ((toolOpt9 >= 0) && (((toolOpt9 >> 7) & 0x7) == 0x2))
							{
								isUh63 = TRUE;
							}
						}

						
						switch(stDispParams.panelInch)
						{
							case LX_OVI_PANEL_INCH_43:
								if (isUh75)
								{
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_43_uj75, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_43_uj75), 0);
								}
								else
								{
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_43_uj65, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_43_uj65), 0);
								}
								break;
							case LX_OVI_PANEL_INCH_48:
								_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_48_uj76, 
														OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_48_uj76), 0);
								break;
							case LX_OVI_PANEL_INCH_49:
								if (isUh75)
								{
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_49_uj75, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_49_uj75), 0);
								}	
								else if (stDispParams.panelMaker == LX_OVI_PANEL_MAKER_LGD_CA)
								{
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_49_uj65ca, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_49_uj65ca), 0);
								}
								else
								{
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_49_uj65, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_49_uj65), 0);
								}
								break;
							case LX_OVI_PANEL_INCH_55:
							default :
								if (isUh75)
								{
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_55_uj75, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_55_uj75), 0);
								}
								else if (isUh63)
								{
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_55_uj63, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_55_uj63), 0);
								}
								else
								{
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_55_uj65, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k60_epi_6lane_rgbw_55_uj65), 0);
								}
						}
						_OVI_M17_RegParamSet(ovi_m17a0_disp_4k60_epi_6lane_rgbw, 
												OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k60_epi_6lane_rgbw), 0);
					}
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M17_RegParamSet(ovi_m17a0_disp_4k60_vx1_8lane, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k60_vx1_8lane), 0);

					if (stDispParams.panelMaker == LX_OVI_PANEL_MAKER_SHARP)
					{
						OVI_REG_RD(0xC90A0300, regVal);
						regVal = (regVal & (~0x1F000)) | (2 << 12);
						OVI_REG_WR(0xC90A0300, regVal);

						OVI_REG_WR(0xC90A000C, 0x0000000E);
						OVI_REG_WR(0xC90A9098, 0x00020406);
						OVI_REG_WR(0xC90A909C, 0x01030507);

						OVI_REG_WR(0xC930A40C, 0x00000000);
						OVI_REG_WR(0xC930A410, 0x000B6D00);
						OVI_REG_WR(0xC930A414, 0xB6D00000);
						OVI_REG_WR(0xC930A44C, 0x00000000);
						OVI_REG_WR(0xC930A450, 0x00000000);
						OVI_REG_WR(0xC930A454, 0x00000000);
					}
					break;

				case LX_OVI_PANEL_CEDS:
					_OVI_M17_RegParamSet(ovi_m17a0_disp_4k60_ceds_12lane_rgbw, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k60_ceds_12lane_rgbw), 0);
					break;

				case LX_OVI_PANEL_LVDS:
				default :
					_OVI_M17_RegParamSet(ovi_m17a0_disp_2k60_lvds_2link, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_2k60_lvds_2link), 0);
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					if (stDispParams.panelVersion == LX_OVI_PANEL_V16)
					{
						_OVI_M17_RegParamSet(ovi_m17a0_disp_4k120_epi_v16_24lane_rgb, 
												OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k120_epi_v16_24lane_rgb), 0);
					}
					else
					{
						if (stDispParams.panelCellType == LX_OVI_PANEL_CELL_RGBW)
						{
							switch(stDispParams.panelInch)
							{
								case LX_OVI_PANEL_INCH_49:
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k120_epi_12lane_rgbw_49, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k120_epi_12lane_rgbw_49), 0);
									break;
								case LX_OVI_PANEL_INCH_55:
								default :
									_OVI_M17_RegParamSet(ovi_m17a0_tcon_4k120_epi_12lane_rgbw_55, 
															OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_tcon_4k120_epi_12lane_rgbw_55), 0);
							}
							_OVI_M17_RegParamSet(ovi_m17a0_disp_4k120_epi_12lane_rgbw, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k120_epi_12lane_rgbw), 0);
						}
						else if (stDispParams.dispOutLaneBw == LX_OVI_OUTPUT_LANE_BANDWIDTH_2_1G)
						{
							_OVI_M17_RegParamSet(ovi_m17a0_disp_4k120_epi_24lane_rgb, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k120_epi_24lane_rgb), 0);
						}
						else
						{
							_OVI_M17_RegParamSet(ovi_m17a0_disp_4k120_epi_12lane_rgb, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k120_epi_12lane_rgb), 0);
						}
					}
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M17_RegParamSet(ovi_m17a0_disp_4k120_vx1_16lane, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_4k120_vx1_16lane), 0);

					if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						OVI_REG_WR(0xC930A40C, 0x00000000);
						OVI_REG_WR(0xC930A410, 0x000B6D00);
						OVI_REG_WR(0xC930A414, 0xB6D00000);
						OVI_REG_WR(0xC930A44C, 0x00000000);
						OVI_REG_WR(0xC930A450, 0x00000000);
						OVI_REG_WR(0xC930A454, 0xB6DB6D00);
					}
					else if (stDispParams.panelInch == LX_OVI_PANEL_INCH_86)
					{
						OVI_REG_WR(0xC930A40C, 0x12492000);
						OVI_REG_WR(0xC930A410, 0x480B6D00);
						OVI_REG_WR(0xC930A414, 0xB6D00000);
						OVI_REG_WR(0xC930A44C, 0x00492492);
						OVI_REG_WR(0xC930A450, 0x00000000);
						OVI_REG_WR(0xC930A454, 0xB6DB6D00);
					}
					break;

				case LX_OVI_PANEL_LVDS:
				default :
					_OVI_M17_RegParamSet(ovi_m17a0_disp_2k120_lvds_4link, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_disp_2k120_lvds_4link), 0);
					break;
			}
			break;

		default :
			break;
	}

	// Local Dimming settings
	CTOP_CTRL_M17A0_RdFL(FMC, ctop_fmc_r07);
	CTOP_CTRL_M17A0_Wr01(FMC, ctop_fmc_r07, jtag0_disable_cco, 1);
	CTOP_CTRL_M17A0_WrFL(FMC, ctop_fmc_r07);

	if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_EDGE_LED)
	{
		_OVI_M17_RegParamSet(ovi_m17a0_led_spi_common1, OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_led_spi_common1), 0);

#if 0 // PQE F/W setting		
		if (stDispParams.panelFramerate == LX_OVI_PANEL_FRAMERATE_60HZ)
		{
			_OVI_M17_RegParamSet(ovi_m17a0_led_spi_disp60hz_common, OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_led_spi_disp60hz_common), 0);
		}
#endif

		switch(stDispParams.panelLedBar)
		{
			case LX_OVI_PANEL_LED_BAR_6:
				_OVI_M17_RegParamSet(ovi_m17a0_led_spi_edge6, OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_led_spi_edge6), 0);
				break;
			case LX_OVI_PANEL_LED_BAR_12:
				_OVI_M17_RegParamSet(ovi_m17a0_led_spi_edge12, OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_led_spi_edge12), 0);
				break;
			case LX_OVI_PANEL_LED_BAR_16:
				_OVI_M17_RegParamSet(ovi_m17a0_led_spi_edge16, OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_led_spi_edge16), 0);
				break;
			case LX_OVI_PANEL_LED_BAR_24:
			default :
				_OVI_M17_RegParamSet(ovi_m17a0_led_spi_edge24, OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_led_spi_edge24), 0);
		}

		_OVI_M17_RegParamSet(ovi_m17a0_led_spi_common2, OVI_HW_M17_ARRAY_SIZE(ovi_m17a0_led_spi_common2), 0);
	}
	
	return;
}

static void _OVI_M17_DispInit_C0(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;
	char opt[64];
	UINT32 regVal;

	OVI_PRINT("\n[_OVI_M17_DispInit] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
		pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
		pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
		pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	// Display Spread Spectrum
	if((RET_OK==OS_ScanKernelCmdline("disp=%s", opt)) && !strncmp(opt,"hdmi",4))
	{
		OVI_REG_WR(0xC930A470, 0xB000001C);
		OVI_REG_WR(0xC930A474, 0x0AA40280);

		OVI_REG_RD(0xC930A478, regVal);
		regVal = (regVal | (0x01400000));
		OVI_REG_WR(0xC930A478, regVal);
	}
	else
	{
		switch (stDispParams.panelInterface)
		{
			case LX_OVI_PANEL_VX1:
			case LX_OVI_PANEL_EPI:
			case LX_OVI_PANEL_EPI_QSAC:
			case LX_OVI_PANEL_CEDS:
				OVI_REG_WR(0xC930A470, _gOviHwM17Info.spreadSpectrumRegValue | 0x4);
				OVI_REG_WR(0xC930A474, 0x0AA40280);

				OVI_REG_RD(0xC930A478, regVal);
				regVal = (regVal | (0x01400000));
				OVI_REG_WR(0xC930A478, regVal);

				OVI_REG_WR(0xC930A470, _gOviHwM17Info.spreadSpectrumRegValue);
				break;
			default :
				break;
		}
	}

	if ((RET_OK==OS_ScanKernelCmdline("disp=%s", opt)) && !strncmp(opt,"hdmi",4))
	{
		stDispParams.panelInterface = LX_OVI_PANEL_VX1;
		stDispParams.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
	}

	// DPE path setting (Picture Enhance block -> L/D)
	OVI_REG_WR(0xC902001C, 0x00000001);
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
				case LX_OVI_PANEL_EPI_QSAC:
					if (stDispParams.dispOutLaneBw == LX_OVI_OUTPUT_LANE_BANDWIDTH_2_1G)
					{
						if (stDispParams.panelCellType == LX_OVI_PANEL_CELL_RGB)
						{
							_OVI_M17_RegParamSet(ovi_m17c0_disp_4k60_epi_8lane_rgb, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_epi_8lane_rgb), 0);
						}
						else
						{
							_OVI_M17_RegParamSet(ovi_m17c0_disp_4k60_epi_8lane_rgbw, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_epi_8lane_rgbw), 0);
						}
					}
					else
					{
						if (stDispParams.panelCellType == LX_OVI_PANEL_CELL_RGB)
						{
							_OVI_M17_RegParamSet(ovi_m17c0_disp_4k60_epi_6lane_rgb, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_epi_6lane_rgb), 0);
						}
						else
						{
							_OVI_M17_RegParamSet(ovi_m17c0_disp_4k60_epi_6lane_rgbw, 
													OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_epi_6lane_rgbw), 0);
						}
					}	
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M17_RegParamSet(ovi_m17c0_disp_4k60_vx1_8lane, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_vx1_8lane), 0);

					if (stDispParams.panelMaker == LX_OVI_PANEL_MAKER_SHARP)
					{
						OVI_REG_RD(0xC90A0300, regVal);
						regVal = (regVal & (~0x1F000)) | (2 << 12);
						OVI_REG_WR(0xC90A0300, regVal);

						OVI_REG_WR(0xC90A000C, 0x0000000E);
						OVI_REG_WR(0xC90A9098, 0x00020406);
						OVI_REG_WR(0xC90A909C, 0x01030507);
					}
					break;

				case LX_OVI_PANEL_CEDS:
					_OVI_M17_RegParamSet(ovi_m17c0_disp_4k60_ceds_12lane, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k60_ceds_12lane), 0);
					break;

				case LX_OVI_PANEL_LVDS:
				default :
					_OVI_M17_RegParamSet(ovi_m17c0_disp_2k60_lvds_2link, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_2k60_lvds_2link), 0);
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					_OVI_M17_RegParamSet(ovi_m17c0_disp_4k120_epi_12lane_rgb, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k120_epi_12lane_rgb), 0);
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M17_RegParamSet(ovi_m17c0_disp_4k120_vx1_16lane, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_4k120_vx1_16lane), 0);

					if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_OLED)
					{
						OVI_REG_WR(0xC930A40C, 0x00000000);
						OVI_REG_WR(0xC930A410, 0x000B6D00);
						OVI_REG_WR(0xC930A414, 0xB6D00000);
						OVI_REG_WR(0xC930A44C, 0x00000000);
						OVI_REG_WR(0xC930A450, 0x00000000);
						OVI_REG_WR(0xC930A454, 0xB6DB6D00);
					}
					else if (stDispParams.panelInch == LX_OVI_PANEL_INCH_86)
					{
						OVI_REG_WR(0xC930A40C, 0x12492000);
						OVI_REG_WR(0xC930A410, 0x480B6D00);
						OVI_REG_WR(0xC930A414, 0xB6D00000);
						OVI_REG_WR(0xC930A44C, 0x00492492);
						OVI_REG_WR(0xC930A450, 0x00000000);
						OVI_REG_WR(0xC930A454, 0xB6DB6D00);
					}
					break;

				case LX_OVI_PANEL_LVDS:
				default :
					_OVI_M17_RegParamSet(ovi_m17c0_disp_2k120_lvds_4link, 
											OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_disp_2k120_lvds_4link), 0);
					break;
			}
			break;

		default :
			break;
	}

	// Clock Gating ON
	CTOP_CTRL_M17A0_RdFL(DPE_SYN, crg_dpe00);
	CTOP_CTRL_M17A0_Wr(DPE_SYN, crg_dpe00, _gOviHwM17Info.tconClkGatingRegValue1);
	CTOP_CTRL_M17A0_WrFL(DPE_SYN, crg_dpe00);

	OVI_TCON_M17C0_RdFL(tcon_btc_config);
	OVI_TCON_M17C0_Wr(tcon_btc_config, _gOviHwM17Info.tconClkGatingRegValue2);
	OVI_TCON_M17C0_WrFL(tcon_btc_config);
	
	// Local Dimming settings
	CTOP_CTRL_M17A0_RdFL(FMC, ctop_fmc_r07);
	CTOP_CTRL_M17A0_Wr01(FMC, ctop_fmc_r07, jtag0_disable_cco, 1);
	CTOP_CTRL_M17A0_WrFL(FMC, ctop_fmc_r07);

	if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_EDGE_LED
		|| stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_DIRECT_L)
	{
		_OVI_M17_RegParamSet(ovi_m17c0_led_spi, OVI_HW_M17_ARRAY_SIZE(ovi_m17c0_led_spi), 0);
	}
	
	return;
}

static void _OVI_M17_DispOutputEnable(BOOLEAN bParam)
{
	CTOP_CTRL_M17A0_RdFL(DPE, ctop_dpe_r02);
	CTOP_CTRL_M17A0_RdFL(DPE, ctop_dpe_r18);
	if (bParam)// display output on
	{
		CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r02, _gOviHwM17Info.chPowerOnRegValue1);
		CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r18, _gOviHwM17Info.chPowerOnRegValue2);
		OVI_DEBUG("[OVI] display is changed to ON status!\n");
	}
	else // display output off
	{
		CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r02, _gOviHwM17Info.chPowerOnRegValue1 & (~OVI_HW_M17_CH_POWER_REG_MASK));
		CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r18, _gOviHwM17Info.chPowerOnRegValue2 & (~OVI_HW_M17_CH_POWER_REG_MASK));
		OVI_DEBUG("[OVI] display is changed to OFF status!\n");
	}
	CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r02);
	CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r18);

	if (bParam)
	{
		// SW reset(TCON, WPR, SIW, FCIC, Pix, Pix2) release
		CTOP_CTRL_M17A0_RdFL(DPE_SYN, crg_dpe01);
		CTOP_CTRL_M17A0_Wr(DPE_SYN, crg_dpe01, 0x0);
		CTOP_CTRL_M17A0_WrFL(DPE_SYN, crg_dpe01);
	}

	return;
}

int OVI_M17_TscicWriteThread(void* data)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr1 = NULL;
	UINT32 tscicSize;
	UINT32 tscicSizeNum;

	do {
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{

			if (_gOviHwM17Info.tscicWritingFlag == TRUE)
			{
				OVI_ERROR("[OVI] already running!\n");
				ret = RET_ERROR;
				return ret;
			}

			_gOviHwM17Info.tscicWritingFlag = TRUE;

			tscicSize = _gOviHwM17Info.tscicSize;

			// check input table size
			if ((tscicSize != OVI_HW_M17_INPUT_TSCIC_DATA_SIZE) || (_gOviHwM17Info.tscicTbl == NULL))
			{
				OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			tscicSizeNum = tscicSize / sizeof(UINT32);

			// select address
			regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17C0_BASE + offsetof(OVI_TCON_REG_M17C0_T, tcon_fcic_data_a), 
												sizeof(UINT32));
			if (regAddr1 == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}

			OVI_TCON_M17C0_RdFL(tcon_fcic_ctrl);
			OVI_TCON_M17C0_Wr01(tcon_fcic_ctrl, checksum_clr, 0x0);
			OVI_TCON_M17C0_Wr01(tcon_fcic_ctrl, flash_done, 0x0);
			OVI_TCON_M17C0_WrFL(tcon_fcic_ctrl);

			OVI_TCON_M17C0_RdFL(tcon_fcic_addr);
			OVI_TCON_M17C0_Wr01(tcon_fcic_addr, flash_addr, 0x0);
			OVI_TCON_M17C0_WrFL(tcon_fcic_addr);

			for (i=0; i<tscicSizeNum; i++)
			{
				if (kthread_should_stop())
				{
					ret = RET_ERROR;

					if (_gOviHwM17Info.tscicTbl != NULL)
					{
						vfree(_gOviHwM17Info.tscicTbl);
						_gOviHwM17Info.tscicTbl = NULL;
					}
					if (regAddr1 != NULL)
						iounmap((void *)regAddr1);

					_gOviHwM17Info.tscicThread = NULL;
					_gOviHwM17Info.tscicWritingFlag = FALSE;

					return ret;
				}
				writel_relaxed(_gOviHwM17Info.tscicTbl[i], &regAddr1[0]);
			}

			OVI_TCON_M17C0_RdFL(tcon_fcic_ctrl);
			OVI_TCON_M17C0_Wr01(tcon_fcic_ctrl, flash_done, 0x1);
			OVI_TCON_M17C0_WrFL(tcon_fcic_ctrl);

			OVI_TCON_M17C0_RdFL(tcon_init_test);
			OVI_TCON_M17C0_Wr01(tcon_init_test, init1_test, 0x1);
			OVI_TCON_M17C0_Wr01(tcon_init_test, init2_test, 0x1);
			OVI_TCON_M17C0_WrFL(tcon_init_test);

		}
		else
		{
			/* Do Nothing */
		}
	} while(0);

	if (_gOviHwM17Info.tscicTbl != NULL)
	{
		vfree(_gOviHwM17Info.tscicTbl);
		_gOviHwM17Info.tscicTbl = NULL;
	}
	if (regAddr1 != NULL)
		iounmap((void *)regAddr1);

	_gOviHwM17Info.tscicThread = NULL;
	_gOviHwM17Info.tscicWritingFlag = FALSE;

	return ret;
}

int OVI_HW_M17_Initialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("OVI chip revision is set to M17 A0\n");
		
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			/* Set configuration of Output mode presets, for mode change on run time */
			_gOVIOutputModes_M17.pOVIOutputModes = _gOVIOutputModes_M17Cx;
			_gOVIOutputModes_M17.number_of_modes	 = sizeof(_gOVIOutputModes_M17Cx)/sizeof(LX_OVI_OUTPUT_MODE_T);

			gOVI_TCON_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_REG_M17C0_T));
			gOVI_TCON_LODC_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_LODC_REG_M17C0_T));
			gOVI_TCON_CAD_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_CAD_REG_M17C0_T));
			gOVI_OIF_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_OIF_REG_M17C0_T));
			gOVI_WPR_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_WPR_REG_M17C0_T));

			gOVI_TCON_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17C0_BASE, sizeof(OVI_TCON_REG_M17C0_T));
			gOVI_TCON_LODC_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_M17C0_BASE, sizeof(OVI_TCON_LODC_REG_M17C0_T));
			gOVI_TCON_CAD_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_M17C0_BASE, sizeof(OVI_TCON_CAD_REG_M17C0_T));
			gOVI_OIF_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_M17C0_BASE, sizeof(OVI_OIF_REG_M17C0_T));
			gOVI_WPR_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_WPR_REG_M17C0_BASE, sizeof(OVI_WPR_REG_M17C0_T));
		}
		else
		{
			/* Set configuration of Output mode presets, for mode change on run time */
			_gOVIOutputModes_M17.pOVIOutputModes = _gOVIOutputModes_M17Ax;
			_gOVIOutputModes_M17.number_of_modes	 = sizeof(_gOVIOutputModes_M17Ax)/sizeof(LX_OVI_OUTPUT_MODE_T);

			gOVI_TCON_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_REG_M17A0_T));
			gOVI_TCON_LODC_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_LODC_REG_M17A0_T));
			gOVI_OIF_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_OIF_REG_M17A0_T));
			gOVI_WPR_M17.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_WPR_REG_M17A0_T));

			gOVI_TCON_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17A0_BASE, sizeof(OVI_TCON_REG_M17A0_T));
			gOVI_TCON_LODC_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_M17A0_BASE, sizeof(OVI_TCON_LODC_REG_M17A0_T));
			gOVI_OIF_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_M17A0_BASE, sizeof(OVI_OIF_REG_M17A0_T));
			gOVI_WPR_M17.phys.addr = (volatile UINT32 *)ioremap(OVI_WPR_REG_M17A0_BASE, sizeof(OVI_WPR_REG_M17A0_T));
		}

		/* for copying value used in channel power on/off function */
		CTOP_CTRL_M17A0_RdFL(DPE, ctop_dpe_r02);
		_gOviHwM17Info.chPowerOnRegValue1 = CTOP_CTRL_M17A0_Rd(DPE, ctop_dpe_r02);
		CTOP_CTRL_M17A0_RdFL(DPE, ctop_dpe_r18);
		_gOviHwM17Info.chPowerOnRegValue2 = CTOP_CTRL_M17A0_Rd(DPE, ctop_dpe_r18);

		/* for copying value used in H-Reverse on/off function */
		OVI_TCON_M17_RdFL(tcon_hor_mode);
		OVI_TCON_M17_Rd01(tcon_hor_mode, hor_reverse, _gOviHwM17Info.horReverseRegFieldValue);

		/* for copying value used in spread spectrum on/off & display resume function */
		CTOP_CTRL_M17A0_RdFL(DPE, ctop_dpe_r28);
		_gOviHwM17Info.spreadSpectrumRegValue = CTOP_CTRL_M17A0_Rd(DPE, ctop_dpe_r28);

		/* for copying value used in display resume function */
		CTOP_CTRL_M17A0_RdFL(DPE_SYN, crg_dpe00);
		_gOviHwM17Info.tconClkGatingRegValue1 = CTOP_CTRL_M17A0_Rd(DPE_SYN, crg_dpe00);
		OVI_TCON_M17C0_RdFL(tcon_btc_config);
		_gOviHwM17Info.tconClkGatingRegValue2 = OVI_TCON_M17C0_Rd(tcon_btc_config);

		/* for copying value used in bypass enable/disable function */
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
			OVI_TCON_M17C0_Rd01(tcon_odc_opt2, wb_in_sel, _gOviHwM17Info.wbInSelRegFieldValue);
			OVI_TCON_M17C0_Rd01(tcon_odc_opt2, dga_in_sel, _gOviHwM17Info.dgaInSelRegFieldValue);
			OVI_TCON_M17C0_Rd01(tcon_odc_opt2, odc_in_sel, _gOviHwM17Info.odcInSelRegFieldValue);
			OVI_TCON_M17C0_Rd01(tcon_odc_opt2, fcic_in_sel, _gOviHwM17Info.hcicInSelRegFieldValue);
			OVI_TCON_M17C0_Rd01(tcon_odc_opt2, lodc_in_sel, _gOviHwM17Info.lodcInSelRegFieldValue);
			OVI_TCON_M17C0_Rd01(tcon_odc_opt2, post_dit_in_sel, _gOviHwM17Info.postDitInSelRegFieldValue);
		}
		else
		{
			OVI_TCON_M17_RdFL(tcon_odc_opt2);
			OVI_TCON_M17_Rd01(tcon_odc_opt2, wb_in_sel, _gOviHwM17Info.wbInSelRegFieldValue);
			OVI_TCON_M17_Rd01(tcon_odc_opt2, dga_in_sel, _gOviHwM17Info.dgaInSelRegFieldValue);
			OVI_TCON_M17_Rd01(tcon_odc_opt2, odc_in_sel, _gOviHwM17Info.odcInSelRegFieldValue);
			OVI_TCON_M17_Rd01(tcon_odc_opt2, hcic_in_sel, _gOviHwM17Info.hcicInSelRegFieldValue);
			OVI_TCON_M17_Rd01(tcon_odc_opt2, lodc_in_sel, _gOviHwM17Info.lodcInSelRegFieldValue);
			OVI_TCON_M17_Rd01(tcon_odc_opt2, post_dit_in_sel, _gOviHwM17Info.postDitInSelRegFieldValue);
		}

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		_gOviHwM17Info.tconBaseAddress = gpOviTconMem->base;
		if (!(_gOviHwM17Info.tconBaseAddress))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! M17 ODC will be disabled!\n");
			break;
		}

		OVI_TCON_M17_RdFL(tcon_base_address);
		OVI_TCON_M17_Wr(tcon_base_address, _gOviHwM17Info.tconBaseAddress);
		OVI_TCON_M17_WrFL(tcon_base_address);

		_gOviHwM17Info.tscicWritingFlag = FALSE;
		_gOviHwM17Info.tscicThread = NULL;
		_gOviHwM17Info.tscicTbl = NULL;

	} while(0);

	return ret;
}

int OVI_HW_M17_Close(void)
{
	int ret = RET_OK;

	if(gOVI_TCON_M17.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_M17.shdw.addr);
		gOVI_TCON_M17.shdw.addr = NULL;
	}
	if(gOVI_TCON_LODC_M17.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_LODC_M17.shdw.addr);
		gOVI_TCON_LODC_M17.shdw.addr = NULL;
	}
	if(gOVI_TCON_CAD_M17.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_CAD_M17.shdw.addr);
		gOVI_TCON_CAD_M17.shdw.addr = NULL;
	}
	if(gOVI_OIF_M17.shdw.addr)
	{
		OS_Free((void *)gOVI_OIF_M17.shdw.addr);
		gOVI_OIF_M17.shdw.addr = NULL;
	}
	if(gOVI_WPR_M17.shdw.addr)
	{
		OS_Free((void *)gOVI_WPR_M17.shdw.addr);
		gOVI_WPR_M17.shdw.addr = NULL;
	}

	if (gOVI_TCON_M17.phys.addr)
	{
		iounmap((void *)gOVI_TCON_M17.phys.addr);
		gOVI_TCON_M17.phys.addr = NULL;
	}
	if (gOVI_TCON_LODC_M17.phys.addr)
	{
		iounmap((void *)gOVI_TCON_LODC_M17.phys.addr);
		gOVI_TCON_LODC_M17.phys.addr = NULL;
	}
	if (gOVI_TCON_CAD_M17.phys.addr)
	{
		iounmap((void *)gOVI_TCON_CAD_M17.phys.addr);
		gOVI_TCON_CAD_M17.phys.addr = NULL;
	}
	if (gOVI_OIF_M17.phys.addr)
	{
		iounmap((void *)gOVI_OIF_M17.phys.addr);
		gOVI_OIF_M17.phys.addr = NULL;
	}
	if (gOVI_WPR_M17.phys.addr)
	{
		iounmap((void *)gOVI_WPR_M17.phys.addr);
		gOVI_WPR_M17.phys.addr = NULL;
	}

	return ret;
}

int OVI_HW_M17_Resume(void)
{
	int ret = RET_OK;

	do {
		CTOP_CTRL_M17A0_RdFL(DPE, ctop_dpe_r02);
		CTOP_CTRL_M17A0_RdFL(DPE, ctop_dpe_r18);
		if (!(CTOP_CTRL_M17A0_Rd(DPE, ctop_dpe_r02) & OVI_HW_M17_CH_POWER_REG_MASK)
			&& !(CTOP_CTRL_M17A0_Rd(DPE, ctop_dpe_r18) & OVI_HW_M17_CH_POWER_REG_MASK)) // Instant boot
		{
			if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
			{
				_OVI_M17_DispInit_C0(&_gOviHwM17Info.dispOption);

				if (_gOviHwM17Info.tscicWritingFlag == TRUE)
				{
					if (_gOviHwM17Info.tscicThread != NULL)
					{
						kthread_stop(_gOviHwM17Info.tscicThread);
						_gOviHwM17Info.tscicThread = NULL;
					}

					_gOviHwM17Info.tscicWritingFlag = FALSE;
				}
			}
			else
			{
				_OVI_M17_DispInit(&_gOviHwM17Info.dispOption);
			}
		}

		_gPrevRedGain = OVI_HW_M17_WB_DEFAULT_GAIN;
		_gPrevGreenGain = OVI_HW_M17_WB_DEFAULT_GAIN;
		_gPrevBlueGain = OVI_HW_M17_WB_DEFAULT_GAIN;

		_gPrevRedOffset = 0;
		_gPrevGreenOffset = 0;
		_gPrevBlueOffset = 0;

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		_gOviHwM17Info.tconBaseAddress = gpOviTconMem->base;
		if (!(_gOviHwM17Info.tconBaseAddress))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! M17 ODC will be disabled!\n");
			break;
		}

		OVI_TCON_M17_RdFL(tcon_base_address);
		OVI_TCON_M17_Wr(tcon_base_address, _gOviHwM17Info.tconBaseAddress);
		OVI_TCON_M17_WrFL(tcon_base_address);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams)
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
		
		OVI_PRINT("\n[OVI_HW_M17_SetDisplayOption] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
			pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
			pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
			pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
			pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

		memcpy((void *)&_gOviHwM17Info.dispOption, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			_OVI_M17_DispRegDataInit_C0(&_gOviHwM17Info.dispOption);
		}
	} while(0);

	return ret;
}

int OVI_HW_M17_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams)
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

		OVI_PRINT("\n[OVI_HW_M17_SetBypass] En[%d], Mask[0x%x]\n\r", pstParams->bEnable, pstParams->u32BlockMask);

		if ((pstParams->u32BlockMask & (LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC))
			&& ((pstParams->u32BlockMask & (LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC)) 
			!= (LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC)))
		{
			OVI_ERROR("[OVI] Not support for the blockMask(0x%x)!\n", pstParams->u32BlockMask);
			ret = RET_ERROR;
			break;
		}
		
		if (pstParams->u32BlockMask & LX_OVI_TCON_BOE_RGBW)
		{
			if (pstParams->bEnable)
			{
				if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
				{
					OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
					OVI_TCON_M17C0_WrFL(tcon_odc_opt2);
				}
				else
				{
					OVI_REG_WR(0xC9090004, 0x00);
					OVI_REG_WR(0xC9090000, 0x00);
					OVI_REG_WR(0xC9080C00, 0x06);
				}
			}
			else
			{
				if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
				{
					OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, odc_bypass, 0x0);
					OVI_TCON_M17C0_WrFL(tcon_odc_opt2);
				}
				else
				{
					OVI_REG_WR(0xC9080C00, 0x0F);
					OVI_REG_WR(0xC9090004, 0x07);
					OVI_REG_WR(0xC9090000, 0x01);
				}
			}
		}
		
		if (pstParams->u32BlockMask & LX_OVI_TCON_LGD_RGBW)
		{
			if (pstParams->bEnable)
			{
				if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
				{
					OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
					OVI_TCON_M17C0_WrFL(tcon_odc_opt2);
				}
				else
				{
					OVI_TCON_M17_RdFL(tcon_odc_opt2);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
					OVI_TCON_M17_WrFL(tcon_odc_opt2);
				}
			}
			else
			{
				if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
				{
					OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, odc_bypass, 0x0);
					OVI_TCON_M17C0_WrFL(tcon_odc_opt2);
				}
				else
				{
					OVI_TCON_M17_RdFL(tcon_odc_opt2);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, odc_bypass, 0x0);
					OVI_TCON_M17_WrFL(tcon_odc_opt2);
				}
			}
		}
		
		if (pstParams->u32BlockMask & (LX_OVI_TCON_GAMMA|LX_OVI_TCON_WB|LX_OVI_TCON_LODC|LX_OVI_TCON_ODC))
		{
			if (pstParams->bEnable)
			{
				if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
				{
					OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, wb_in_sel, 0x0);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, dga_in_sel, 0x0);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, odc_in_sel, 0x0);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, fcic_in_sel, 0x0);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, lodc_in_sel, 0x0);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, post_dit_in_sel, 0x0);
					OVI_TCON_M17C0_WrFL(tcon_odc_opt2);
				}
				else
				{
					OVI_TCON_M17_RdFL(tcon_odc_opt2);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, wb_in_sel, 0x0);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, dga_in_sel, 0x0);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, odc_in_sel, 0x0);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, hcic_in_sel, 0x0);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, lodc_in_sel, 0x0);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, post_dit_in_sel, 0x0);
					OVI_TCON_M17_WrFL(tcon_odc_opt2);
				}
			}
			else
			{
				if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
				{
					OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, wb_in_sel, _gOviHwM17Info.wbInSelRegFieldValue);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, dga_in_sel, _gOviHwM17Info.dgaInSelRegFieldValue);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, odc_in_sel, _gOviHwM17Info.odcInSelRegFieldValue);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, fcic_in_sel, _gOviHwM17Info.hcicInSelRegFieldValue);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, lodc_in_sel, _gOviHwM17Info.lodcInSelRegFieldValue);
					OVI_TCON_M17C0_Wr01(tcon_odc_opt2, post_dit_in_sel, _gOviHwM17Info.postDitInSelRegFieldValue);
					OVI_TCON_M17C0_WrFL(tcon_odc_opt2);
				}
				else
				{
					OVI_TCON_M17_RdFL(tcon_odc_opt2);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, wb_in_sel, _gOviHwM17Info.wbInSelRegFieldValue);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, dga_in_sel, _gOviHwM17Info.dgaInSelRegFieldValue);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, odc_in_sel, _gOviHwM17Info.odcInSelRegFieldValue);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, hcic_in_sel, _gOviHwM17Info.hcicInSelRegFieldValue);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, lodc_in_sel, _gOviHwM17Info.lodcInSelRegFieldValue);
					OVI_TCON_M17_Wr01(tcon_odc_opt2, post_dit_in_sel, _gOviHwM17Info.postDitInSelRegFieldValue);
					OVI_TCON_M17_WrFL(tcon_odc_opt2);
				}
			}	
		}
	} while(0);

	return ret;
}

int OVI_HW_M17_SetCombination(UINT32 param)
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
			for(i=0; i<_gOVIOutputModes_M17.number_of_modes;i++)
			{
				printk("  Index[%d] : %s", i,_gOVIOutputModes_M17.pOVIOutputModes[i].index);
			}
			ret = RET_OK;
			break;
		}
		else if(param >= 10000)
		{
			param = param - 10000;
			printk("\n[OVI] Compare register values regarding to register-set index[%d]", param);

			if(param > _gOVIOutputModes_M17.number_of_modes) {
				OVI_ERROR("Unknown OVI index. Index was [%d]", param);
				break;
			}

			regs  = _gOVIOutputModes_M17.pOVIOutputModes[param].regs;
			count = _gOVIOutputModes_M17.pOVIOutputModes[param].count;
			index = _gOVIOutputModes_M17.pOVIOutputModes[param].index;

			printk("\n[OVI] Register Index[%d] => %s",param, (char *)index);
			for(i=0; i<count; i++){
				if (regs[i].addr == OVI_HW_M17_REG_PARAM_OP_WAIT) continue;

				if (regs[i].addr == OVI_HW_M17_REG_PARAM_OP_CHECK)
				{
					_OVI_M17_IgnoreRegSet(regs[i].value, &ignore);
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
		else if(param > _gOVIOutputModes_M17.number_of_modes) {
			OVI_ERROR("\nUnknown OVI mode. Index was [%d]\n", param);
			break;
		}

		/* Step 2. Set mode */
		regs  = _gOVIOutputModes_M17.pOVIOutputModes[param].regs;
		count = _gOVIOutputModes_M17.pOVIOutputModes[param].count;
		index = _gOVIOutputModes_M17.pOVIOutputModes[param].index;

		printk("\n[OVI] Setting to registers to register-set-index => %s", (char *)index);
		for(i=0; i<count; i++){
			if (regs[i].addr == OVI_HW_M17_REG_PARAM_OP_WAIT)
			{
				printk("\n[%03d] Delay... %dms", i, regs[i].value/1000);
				OS_UsecDelay(regs[i].value);
			}

			if (regs[i].addr == OVI_HW_M17_REG_PARAM_OP_CHECK)
			{
				_OVI_M17_IgnoreRegSet(regs[i].value, &ignore);
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

int OVI_HW_M17_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams)
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

		if (_gOviHwM17Info.spreadSpectrumRegValue == 0xB000001C) break;

		if(pstParams->bEnable)
		{
			CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r28, _gOviHwM17Info.spreadSpectrumRegValue | 0x4);
			CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r29, 0x0AA40280);
			CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r30, 0x01400000);
			CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r28);
			CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r29);
			CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r30);

			CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r28, _gOviHwM17Info.spreadSpectrumRegValue);
			CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r28);
		}
		else
		{
			CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r28, 0xB000001C);
			CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r29, 0x0AA40280);
			CTOP_CTRL_M17A0_Wr(DPE, ctop_dpe_r30, 0x01400000);
			CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r28);
			CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r29);
			CTOP_CTRL_M17A0_WrFL(DPE, ctop_dpe_r30);
		}
	} while(0);

	return ret;
}

int OVI_HW_M17_SetMcuCommand(LX_OVI_TCON_MCU_CMD_T *pstParams)
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
		
		if (pstParams->type == LX_OVI_TCON_FW_BOE)
		{
			OVI_REG_WR(0xC9090020, pstParams->cmd);

			OVI_TCON_M17_RdFL(tcon_control);
			OVI_TCON_M17_Wr01(tcon_control, hm_mcu_int_in, 0x0);
			OVI_TCON_M17_WrFL(tcon_control);
		}
	} while(0);
		
	return ret;
}

int OVI_HW_M17_UpdateFirmware(LX_OVI_TCON_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	volatile UINT32 *fwRegAddr = NULL;
	CHAR buff;

	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if (pstParams->pData == NULL)
		{
			OVI_ERROR("[OVI] Invalid parameter!\n");
			ret = RET_ERROR;
			break;
		}

		if (pstParams->type == LX_OVI_TCON_FW_BOE)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
			{
				UINT32 buff32;
				
				if (pstParams->sizeNum != OVI_HW_M17_BOE_MPLUS_LUT_SIZENUM) 
				{
					OVI_ERROR("[OVI] Invalid BOE M+ LUT size! \n");
					ret = RET_ERROR;
					break;
				}

				fwRegAddr = (volatile UINT32 *)ioremap(OVI_SIW_RGBW_START_REG_M17C0_BASE, sizeof(UINT32)*(pstParams->sizeNum));
				if(fwRegAddr == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}

				for (i=0; i<pstParams->sizeNum; i++)
				{
					get_user(buff32, &(((UINT32 *)pstParams->pData)[i]));
					writel_relaxed(buff32, &fwRegAddr[i]);
				}
			}
			else
			{
				if (pstParams->sizeNum != OVI_HW_M17_BOE_FW_SIZENUM) 
				{
					OVI_ERROR("[OVI] Invalid BOE FW size! \n");
					ret = RET_ERROR;
					break;
				}

				OVI_TCON_M17_RdFL(tcon_control);
				OVI_TCON_M17_Wr01(tcon_control, hm_mcu_int_in, 0x1);
				OVI_TCON_M17_WrFL(tcon_control);

				OVI_REG_WR(0xC9090020, 0x00);

				OVI_REG_WR(0xC9090000, 0x00);
				OVI_REG_WR(0xC9090004, 0x00);
					
				CTOP_CTRL_M17A0_RdFL(DPE_SYN, crg_dpe01);
				CTOP_CTRL_M17A0_Wr01(DPE_SYN, crg_dpe01, swrst_tcon_mcu, 1);
				CTOP_CTRL_M17A0_WrFL(DPE_SYN, crg_dpe01);

				fwRegAddr = (volatile UINT32 *)ioremap(0xC9060000, sizeof(UINT32)*(pstParams->sizeNum));
				if(fwRegAddr == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}

				for (i=0; i<pstParams->sizeNum; i++)
				{
					get_user(buff, &(((CHAR *)pstParams->pData)[i]));
					writel_relaxed(buff, &fwRegAddr[i]);
				}
				
				CTOP_CTRL_M17A0_RdFL(DPE_SYN, crg_dpe01);
				CTOP_CTRL_M17A0_Wr01(DPE_SYN, crg_dpe01, swrst_tcon_mcu, 0);
				CTOP_CTRL_M17A0_WrFL(DPE_SYN, crg_dpe01);

				OS_UsecDelay(100);
							
				OVI_REG_WR(0xC9090004, 0x07);
				OVI_REG_WR(0xC9090000, 0x01);

				
			}
		}
		else if (pstParams->type == LX_OVI_TCON_FW_LGD)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
			{
				if (pstParams->sizeNum != OVI_HW_M17_LGD_MPLUS_LUT_SIZENUM) 
				{
					if (pstParams->sizeNum > OVI_HW_M17_LGD_MPLUS_LUT_SIZENUM)
					{
						pstParams->sizeNum = OVI_HW_M17_LGD_MPLUS_LUT_SIZENUM;
					}
					else
					{
						OVI_ERROR("[OVI] Invalid LGD M+ LUT size! \n");
						ret = RET_ERROR;
						break;
					}
				}
				
				fwRegAddr = (volatile UINT32 *)ioremap(OVI_WPR_MPLUS_START_REG_M17C0_BASE, sizeof(UINT32)*(pstParams->sizeNum));
				if(fwRegAddr == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}

				for (i=0; i<pstParams->sizeNum; i++)
				{
					get_user(buff, &(((CHAR *)pstParams->pData)[i]));
					writel_relaxed(buff, &fwRegAddr[i]);
				}
			}
		}
	} while(0);

	if(fwRegAddr != NULL)
		iounmap((void *)fwRegAddr);
	
	return ret;
}

int OVI_HW_M17_GetFirmwareVersion(LX_OVI_TCON_FW_VER_T *pstParams)
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

		if (pstParams->ver == NULL)
		{
			OVI_ERROR("[OVI] Invalid parameter!\n");
			ret = RET_ERROR;
			break;
		}

		if (pstParams->type == LX_OVI_TCON_FW_BOE)
		{
			LX_OVI_TCON_BOE_FW_VER_T stBoeFwVer;

			OVI_REG_RD(0xC9090030, stBoeFwVer.b0);
			OVI_REG_RD(0xC9090034, stBoeFwVer.b1);
			OVI_REG_RD(0xC9090038, stBoeFwVer.b2);
			
			OVI_TCON_M17_RdFL(tcon_control);
			OVI_TCON_M17_Wr01(tcon_control, hm_mcu_int_in, 0x1);
			OVI_TCON_M17_WrFL(tcon_control);

			OVI_REG_WR(0xC9090020, 0x00);

			ret = copy_to_user((void __user *)pstParams->ver, (void *)&stBoeFwVer, sizeof(LX_OVI_TCON_BOE_FW_VER_T));
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


int OVI_HW_M17_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
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
			if((odLutSizeNum != OVI_HW_M17_INPUT_OD_SIZENUM && odLutSizeNum != (4*OVI_HW_M17_INPUT_OD_SIZENUM)) 
				|| pstParams->odLut.pData == NULL)
			{
				OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			// select address
			regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17A0_BASE + offsetof(OVI_TCON_REG_M17A0_T, tcon_odc_start_2d), 
												sizeof(UINT32)*OVI_HW_M17_INPUT_OD_SIZENUM);
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
			if(odLutSizeNum != OVI_HW_M17_INPUT_OD_SIZENUM || pstParams->odLut.pData == NULL)
			{
				OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			// select address
			regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_M17A0_BASE + offsetof(OVI_TCON_LODC_REG_M17A0_T, tcon_lodc_start_low), 
												sizeof(UINT32)*OVI_HW_M17_INPUT_OD_SIZENUM);
			if(regAddr1 == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}
		}
		else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_ON)
		{
			OVI_TCON_M17_RdFL(tcon_control);
			OVI_TCON_M17_Wr01(tcon_control, odc_en, 0x1);
			OVI_TCON_M17_WrFL(tcon_control);

			OVI_TCON_M17_RdFL(tcon_sts);
			OVI_TCON_M17_Wr01(tcon_sts, pix2_lock, 0x1);
			OVI_TCON_M17_WrFL(tcon_sts);
			break;
		}
		else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_OFF)
		{
			OVI_TCON_M17_RdFL(tcon_control);
			OVI_TCON_M17_Wr01(tcon_control, odc_en, 0x0);
			OVI_TCON_M17_WrFL(tcon_control);

			OVI_TCON_M17_RdFL(tcon_sts);
			OVI_TCON_M17_Wr01(tcon_sts, pix2_lock, 0x0);
			OVI_TCON_M17_WrFL(tcon_sts);
			break;
		}
		else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
			{
				// check input table size
				if(odLutSizeNum != OVI_HW_M17_INPUT_POD2_SIZENUM || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_M17C0_BASE + offsetof(OVI_TCON_CAD_REG_M17C0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_M17_INPUT_POD2_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}
			else
			{
				// check input table size
				if(odLutSizeNum != (OVI_HW_M17_INPUT_OD_SIZENUM*2) || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_M17A0_BASE + offsetof(OVI_TCON_LODC_REG_M17A0_T, tcon_lodc_start_low), 
													sizeof(UINT32)*OVI_HW_M17_INPUT_OD_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}

				regAddr2 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_M17A0_BASE + offsetof(OVI_TCON_LODC_REG_M17A0_T, tcon_lodc_start_high), 
													sizeof(UINT32)*OVI_HW_M17_INPUT_OD_SIZENUM);
				if(regAddr2 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
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

		if ((lx_chip_rev() >= LX_CHIP_REV(M17, C0)) && (pstParams->eMode == LX_OVI_TCON_FRAMEOD))
		{
			UINT32 regField;
			UINT32 regField2;
			UINT32 odLutDataOffsetInc = 0;

			OVI_WPR_M17C0_RdFL(wpr_reg_main);
			regField = OVI_WPR_M17C0_Rd(wpr_reg_main);
			regField = regField & 0x3; // check wpr_on,lgd_siw_mux
			OVI_TCON_M17_RdFL(tcon_control);
			OVI_TCON_M17_Rd01(tcon_control, hm_rgbw_en, regField2);
			regField = regField | regField2;

			OVI_TCON_M17C0_RdFL(odc_lut_subpix_sel);
			OVI_TCON_M17C0_Wr01(odc_lut_subpix_sel, lut_rgbw_en, regField == 0 ? 0x0 : 0x1);
			OVI_TCON_M17C0_WrFL(odc_lut_subpix_sel);

			OVI_TCON_M17C0_RdFL(odc_lut_subpix_sel);
			OVI_TCON_M17C0_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x0);
			OVI_TCON_M17C0_WrFL(odc_lut_subpix_sel);

			if (odLutSizeNum == (4*OVI_HW_M17_INPUT_OD_SIZENUM))
			{
				odLutDataOffsetInc = OVI_HW_M17_INPUT_OD_SIZENUM;
			}

			for(i=0; i<OVI_HW_M17_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i], &regAddr1[i]);
			}

			OVI_TCON_M17C0_RdFL(odc_lut_subpix_sel);
			OVI_TCON_M17C0_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x1);
			OVI_TCON_M17C0_WrFL(odc_lut_subpix_sel);
			for(i=0; i<OVI_HW_M17_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i+(1*odLutDataOffsetInc)], &regAddr1[i]);
			}

			OVI_TCON_M17C0_RdFL(odc_lut_subpix_sel);
			OVI_TCON_M17C0_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x2);
			OVI_TCON_M17C0_WrFL(odc_lut_subpix_sel);
			for(i=0; i<OVI_HW_M17_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i+(2*odLutDataOffsetInc)], &regAddr1[i]);
			}

			if (regField != 0)
			{
				OVI_TCON_M17C0_RdFL(odc_lut_subpix_sel);
				OVI_TCON_M17C0_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x3);
				OVI_TCON_M17C0_WrFL(odc_lut_subpix_sel);
				for(i=0; i<OVI_HW_M17_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i+(3*odLutDataOffsetInc)], &regAddr1[i]);
				}
			}
		}
		else if ((lx_chip_rev() >= LX_CHIP_REV(M17, C0)) && (pstParams->eMode == LX_OVI_TCON_LINEOD_POD))
		{
			for(i=0; i<OVI_HW_M17_INPUT_POD2_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i], &regAddr1[i]);
			}
		}
		else
		{
			for(i=0; i<OVI_HW_M17_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i], &regAddr1[i]);
			}
		}

		if ((lx_chip_rev() < LX_CHIP_REV(M17, C0)) && (pstParams->eMode == LX_OVI_TCON_LINEOD_POD))
		{
			for(i=0; i<OVI_HW_M17_INPUT_OD_SIZENUM; i++)
			{
				writel_relaxed(u8odLutData[i+OVI_HW_M17_INPUT_OD_SIZENUM], &regAddr2[i]);
			}
		}

		if(pstParams->eMode == LX_OVI_TCON_FRAMEOD)
		{
			if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
			{
				OVI_TCON_M17C0_RdFL(odc_lut_upload);
				OVI_TCON_M17C0_Wr01(odc_lut_upload, odc_upload, 0x0);
				OVI_TCON_M17C0_WrFL(odc_lut_upload);
				OVI_TCON_M17C0_RdFL(odc_lut_upload);
				OVI_TCON_M17C0_Wr01(odc_lut_upload, odc_upload, 0x1);
				OVI_TCON_M17C0_WrFL(odc_lut_upload);
			}
			else
			{
				OVI_TCON_M17_RdFL(tcon_odc_opt2);
				OVI_TCON_M17_Wr01(tcon_odc_opt2, odc_upload, 0x0);
				OVI_TCON_M17_WrFL(tcon_odc_opt2);
				OVI_TCON_M17_RdFL(tcon_odc_opt2);
				OVI_TCON_M17_Wr01(tcon_odc_opt2, odc_upload, 0x1);
				OVI_TCON_M17_WrFL(tcon_odc_opt2);
			}
		}
		else
		{
			if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
			{
				OVI_TCON_LODC_M17C0_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_M17C0_Wr01(lodc_lut_upload, lodc_upload, 0x0);
				OVI_TCON_LODC_M17C0_WrFL(lodc_lut_upload);
				OVI_TCON_LODC_M17C0_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_M17C0_Wr01(lodc_lut_upload, lodc_upload, 0x1);
				OVI_TCON_LODC_M17C0_WrFL(lodc_lut_upload);
			}
			else
			{
				OVI_TCON_M17_RdFL(tcon_odc_opt2);
				OVI_TCON_M17_Wr01(tcon_odc_opt2, lodc_upload, 0x0);
				OVI_TCON_M17_WrFL(tcon_odc_opt2);
				OVI_TCON_M17_RdFL(tcon_odc_opt2);
				OVI_TCON_M17_Wr01(tcon_odc_opt2, lodc_upload, 0x1);
				OVI_TCON_M17_WrFL(tcon_odc_opt2);
			}

			OVI_TCON_M17_RdFL(tcon_odc_opt1);
			if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				OVI_TCON_M17_Wr01(tcon_odc_opt1, lodc_en_2d, 0x1);
				OVI_TCON_M17_Wr01(tcon_odc_opt1, lodc_en_3d, 0x0);
				OVI_TCON_M17_Wr01(tcon_odc_opt1, pcid_mode, 0x3);
			}
			else  // LX_OVI_TCON_LINEOD_POD
			{
				if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
				{
					OVI_TCON_CAD_M17C0_RdFL(tcon_cad_reg_main);
					OVI_TCON_CAD_M17C0_Wr01(tcon_cad_reg_main, cad_on, 0x1);
					OVI_TCON_CAD_M17C0_WrFL(tcon_cad_reg_main);
				}
				else
				{
					OVI_TCON_M17_Wr01(tcon_odc_opt1, lodc_en_2d, 0x1);
					OVI_TCON_M17_Wr01(tcon_odc_opt1, lodc_en_3d, 0x0);
					OVI_TCON_M17_Wr01(tcon_odc_opt1, pcid_mode, 0x1);
					OVI_TCON_M17_Wr01(tcon_odc_opt1, pxod_order, 0x77);
				}
			}
			OVI_TCON_M17_WrFL(tcon_odc_opt1);
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

int OVI_HW_M17_SetFrameOdcEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	
	do {
		// check TCON base address
		if (bParam && !(_gOviHwM17Info.tconBaseAddress))
		{
			OVI_ERROR("[OVI] TCON base address is Null!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_TCON_M17_RdFL(tcon_control);
		if(bParam)
			OVI_TCON_M17_Wr01(tcon_control, odc_en, 0x1);
		else
			OVI_TCON_M17_Wr01(tcon_control, odc_en, 0x0);
		OVI_TCON_M17_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_M17_SetColorTempEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M17_RdFL(tcon_control);
		if(bParam)
			OVI_TCON_M17_Wr01(tcon_control, wb_en, 0x1);
		else
			OVI_TCON_M17_Wr01(tcon_control, wb_en, 0x0);
		OVI_TCON_M17_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_M17_SetGammaEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_M17_RdFL(led_dpg_en);
		if(bParam)
			DPE_LED_M17_Wr01(led_dpg_en, dpg_en, 0x1);
		else
			DPE_LED_M17_Wr01(led_dpg_en, dpg_en, 0x0);
		DPE_LED_M17_WrFL(led_dpg_en);
	} while (0);

	return ret;
}

int OVI_HW_M17_SetDitherEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	
	do {
		OVI_TCON_M17_RdFL(tcon_control);
		if(bParam)
		{
			OVI_TCON_M17_Wr01(tcon_control, post_dither_en, 0x1);
		}
		else
		{
			OVI_TCON_M17_Wr01(tcon_control, post_dither_en, 0x0);
		}
		OVI_TCON_M17_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_M17_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		/* Do Nothing */
	} while(0);

	return ret;
}

int OVI_HW_M17_SetDitherMode(LX_OVI_TCON_DITHER_T enParam)
{
	int ret = RET_OK;
	
	do {
		//Dither Enable
		OVI_TCON_M17_RdFL(tcon_control);
		OVI_TCON_M17_Wr01(tcon_control, post_dither_en, 0x1);
		OVI_TCON_M17_WrFL(tcon_control);
		
		OVI_TCON_M17_RdFL(tcon_dither_carry);
		switch(enParam)
		{
			case LX_OVI_TCON_DITHER_TRUNC:
				OVI_TCON_M17_Wr01(tcon_dither_carry, post_dither_sel, 0x0);
				break;
			case LX_OVI_TCON_DITHER_ROUND:
				OVI_TCON_M17_Wr01(tcon_dither_carry, post_dither_sel, 0x1);
				break;
			case LX_OVI_TCON_DITHER_RANDOM:
			default :
				OVI_TCON_M17_Wr01(tcon_dither_carry, post_dither_sel, 0x2);
				break;
		}
		OVI_TCON_M17_WrFL(tcon_dither_carry);
	} while(0);

	return ret;
}

static UINT32 _OVI_M17_GetGain(UINT32 gain)
{
	UINT32 ret_gain;
	UINT32 temp;

	temp = 10000 + (gain - 192) * OVI_HW_M17_WB_GAIN_STEP;
	ret_gain = (temp * OVI_HW_M17_WB_DEFAULT_GAIN) / 10000;

	return ret_gain;
}

static SINT16 _OVI_M17_GetOffset(UINT32 offset)
{
	SINT16 ret_offset;

	ret_offset = ((SINT32)offset - 64) * OVI_HW_M17_WB_OFFSET_STEP;
	return ret_offset;
}

int OVI_HW_M17_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams)
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
		OVI_TCON_M17_RdFL(tcon_control);
		OVI_TCON_M17_Wr01(tcon_control, wb_en, 0x1);
		OVI_TCON_M17_WrFL(tcon_control);
		
		r_gain = _OVI_M17_GetGain(pstParams->r_gain);
		g_gain = _OVI_M17_GetGain(pstParams->g_gain);
		b_gain = _OVI_M17_GetGain(pstParams->b_gain);

		rOffset = _OVI_M17_GetOffset(pstParams->r_offset);
		gOffset = _OVI_M17_GetOffset(pstParams->g_offset);
		bOffset = _OVI_M17_GetOffset(pstParams->b_offset);

		if((_gPrevRedGain == r_gain) && (_gPrevGreenGain == g_gain) && (_gPrevBlueGain == b_gain)
			&& (_gPrevRedOffset == rOffset) && (_gPrevGreenOffset == gOffset) && (_gPrevBlueOffset == bOffset))
		{
			return RET_OK;
		}

		// Set red gain
		OVI_TCON_M17_RdFL(tcon_wb_rgain);
		OVI_TCON_M17_Wr(tcon_wb_rgain, r_gain);
		OVI_TCON_M17_WrFL(tcon_wb_rgain);

		// Set red offset
		OVI_TCON_M17_RdFL(tcon_wb_roffset);
		OVI_TCON_M17_Wr(tcon_wb_roffset, rOffset);
		OVI_TCON_M17_WrFL(tcon_wb_roffset);

		// Set green gain
		OVI_TCON_M17_RdFL(tcon_wb_ggain);
		OVI_TCON_M17_Wr(tcon_wb_ggain, g_gain);
		OVI_TCON_M17_WrFL(tcon_wb_ggain);

		// Set green offset
		OVI_TCON_M17_RdFL(tcon_wb_goffset);
		OVI_TCON_M17_Wr(tcon_wb_goffset, gOffset);
		OVI_TCON_M17_WrFL(tcon_wb_goffset);

		// Set blue gain
		OVI_TCON_M17_RdFL(tcon_wb_bgain);
		OVI_TCON_M17_Wr(tcon_wb_bgain, b_gain);
		OVI_TCON_M17_WrFL(tcon_wb_bgain);

		// Set blue offset
		OVI_TCON_M17_RdFL(tcon_wb_boffset);
		OVI_TCON_M17_Wr(tcon_wb_boffset, bOffset);
		OVI_TCON_M17_WrFL(tcon_wb_boffset);

		_gPrevRedGain = r_gain;
		_gPrevGreenGain = g_gain;
		_gPrevBlueGain = b_gain;
		_gPrevRedOffset = rOffset;
		_gPrevGreenOffset = gOffset;
		_gPrevBlueOffset = bOffset;

	} while(0);

	return ret;
}

int OVI_HW_M17_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams)
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

		if((pstParams->rGammaLut.sizeNum != OVI_HW_M17_GAMMA_TABLE_SIZENUM)
		|| (pstParams->gGammaLut.sizeNum != OVI_HW_M17_GAMMA_TABLE_SIZENUM)
		|| (pstParams->bGammaLut.sizeNum != OVI_HW_M17_GAMMA_TABLE_SIZENUM))
		{
			OVI_ERROR("[OVI] Gamma table size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		rGammaTable = (UINT32 *)vmalloc(OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		gGammaTable = (UINT32 *)vmalloc(OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		bGammaTable = (UINT32 *)vmalloc(OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		ret = copy_from_user(rGammaTable, (void __user *)pstParams->rGammaLut.pData, OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		ret |= copy_from_user(gGammaTable, (void __user *)pstParams->gGammaLut.pData, OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		ret |= copy_from_user(bGammaTable, (void __user *)pstParams->bGammaLut.pData, OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		DPE_LED_M17_RdFL(led_dpg_lut_wdata);

		/* Setting Red Gamma Table */
		for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_wdata, rGammaTable[i] & 0x7FFF);
			DPE_LED_M17_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Green Gamma Table */
		for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_wdata, gGammaTable[i] & 0x7FFF);
			DPE_LED_M17_WrFL(led_dpg_lut_wdata);
		}
		/* Setting Blue Gamma Table */
		for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
		{
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
			DPE_LED_M17_Wr01(led_dpg_lut_wdata, dpg_wdata, bGammaTable[i] & 0x7FFF);
			DPE_LED_M17_WrFL(led_dpg_lut_wdata);
		}

		DPE_LED_M17_RdFL(led_dpg_lut_wr_done);
		DPE_LED_M17_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
		DPE_LED_M17_WrFL(led_dpg_lut_wr_done);

		// Gamma Enable
		DPE_LED_M17_RdFL(led_dpg_en);
		DPE_LED_M17_Wr01(led_dpg_en, dpg_en, 0x1);
		DPE_LED_M17_WrFL(led_dpg_en);
	} while(0);

	if(rGammaTable != NULL)
		vfree(rGammaTable);
	if(gGammaTable != NULL)
		vfree(gGammaTable);
	if(bGammaTable != NULL)
		vfree(bGammaTable);

	return ret;
}

int OVI_HW_M17_SetGammaRGBW(LX_OVI_TCON_GAMMA_RGBW_T *pstParams)
{
	int ret = RET_OK;
	UINT32 *gammaTable = NULL;
	volatile UINT32 *reg_start = NULL;
	int i;

	do {
		// check structure pointer
		if(pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}

		if((pstParams->rGammaLut.sizeNum != OVI_HW_M17_GAMMA_TABLE_SIZENUM)
		|| (pstParams->gGammaLut.sizeNum != OVI_HW_M17_GAMMA_TABLE_SIZENUM)
		|| (pstParams->bGammaLut.sizeNum != OVI_HW_M17_GAMMA_TABLE_SIZENUM)
		|| (pstParams->wGammaLut.sizeNum != OVI_HW_M17_GAMMA_TABLE_SIZENUM))
		{
			OVI_ERROR("[OVI] Gamma table size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		gammaTable = (UINT32 *)vmalloc(OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(gammaTable == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		/* Setting Red Gamma Table */
		ret = copy_from_user(gammaTable, (void __user *)pstParams->rGammaLut.pData, 
							OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}
		
		reg_start = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17A0_BASE+offsetof(OVI_TCON_REG_M17A0_T, tcon_dga_low_rs), 
											OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_start == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
			{
				reg_start[i] = gammaTable[i] << 3;
			}
		}
		else
		{
			for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
			{
				reg_start[i] = gammaTable[i] << 2;
			}
		}
		iounmap((void *)reg_start); reg_start = NULL;
		
		/* Setting Green Gamma Table */
		ret = copy_from_user(gammaTable, (void __user *)pstParams->gGammaLut.pData, 
							OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}
		
		reg_start = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17A0_BASE+offsetof(OVI_TCON_REG_M17A0_T, tcon_dga_low_gs), 
											OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_start == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}
		
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
			{
				reg_start[i] = gammaTable[i] << 3;
			}
		}
		else
		{
			for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
			{
				reg_start[i] = gammaTable[i] << 2;
			}
		}
		iounmap((void *)reg_start); reg_start = NULL;
		
		/* Setting Blue Gamma Table */
		ret = copy_from_user(gammaTable, (void __user *)pstParams->bGammaLut.pData, 
							OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}
		
		reg_start = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17A0_BASE+offsetof(OVI_TCON_REG_M17A0_T, tcon_dga_low_bs), 
											OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_start == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}
		
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
			{
				reg_start[i] = gammaTable[i] << 3;
			}
		}
		else
		{
			for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
			{
				reg_start[i] = gammaTable[i] << 2;
			}
		}
		iounmap((void *)reg_start); reg_start = NULL;
		
		/* Setting White Gamma Table */
		ret = copy_from_user(gammaTable, (void __user *)pstParams->wGammaLut.pData, 
							OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}
		
		reg_start = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17A0_BASE+offsetof(OVI_TCON_REG_M17A0_T, tcon_dga_low_ws), 
											OVI_HW_M17_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_start == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}
		
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
			{
				reg_start[i] = gammaTable[i] << 3;
			}
		}
		else
		{
			for(i=0; i<OVI_HW_M17_GAMMA_TABLE_SIZENUM; i++)
			{
				reg_start[i] = gammaTable[i] << 2;
			}
		}
		iounmap((void *)reg_start); reg_start = NULL;

		// gamma table upload
		OVI_TCON_M17_RdFL(tcon_dga_mode);
		OVI_TCON_M17_Wr01(tcon_dga_mode, dga_up_mode, 0x0);	// dga_up_mode : 0 -> sync update
		OVI_TCON_M17_WrFL(tcon_dga_mode);
		OVI_TCON_M17_RdFL(tcon_dga_mode);
		OVI_TCON_M17_Wr01(tcon_dga_mode, dga_upload, 0x1);	// dga_upload : 1 -> upload bit cleared by HW
		OVI_TCON_M17_WrFL(tcon_dga_mode);

		// Gamma Enable
		OVI_TCON_M17_RdFL(tcon_control);
		OVI_TCON_M17_Wr01(tcon_control, dga_en, 0x1);
		OVI_TCON_M17_WrFL(tcon_control);
	} while(0);

	if (gammaTable != NULL)
		vfree(gammaTable);

	if (reg_start != NULL)
		iounmap((void *)reg_start);
	
	return ret;
}

int OVI_HW_M17_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	UINT32 u32odcAddr=0;
	volatile UINT32 *pMappedAddr = NULL;

	do {
		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_FRAMEOD:
				u32odcAddr = OVI_TCON_REG_M17A0_BASE + offsetof(OVI_TCON_REG_M17A0_T, tcon_odc_start_2d);
				break;
			case LX_OVI_TCON_LINEOD_PCID:
				u32odcAddr = OVI_TCON_LODC_REG_M17A0_BASE + offsetof(OVI_TCON_LODC_REG_M17A0_T, tcon_lodc_start_low);
				break;
			default:
				break;
		}

		pstParams->odLut.sizeNum = OVI_HW_M17_INPUT_OD_SIZENUM;

		pMappedAddr = (volatile UINT32 *)ioremap(u32odcAddr, sizeof(UINT32)*OVI_HW_M17_INPUT_OD_SIZENUM);
		if(pMappedAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			break;
		}

		ret = copy_to_user((void __user *)pstParams->odLut.pData, (void*)pMappedAddr, sizeof(UINT32)*OVI_HW_M17_INPUT_OD_SIZENUM);
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

int OVI_HW_M17_SetMleMode(LX_OVI_TCON_MLE_MODE_T enParam)
{
	int ret = RET_OK;

	do {
		// W/A for M17C0 MLE mode OFF
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
			if (enParam == LX_OVI_TCON_MLE_MODE_OFF)
			{
				OVI_TCON_M17C0_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
			}
			else
			{
				OVI_TCON_M17C0_Wr01(tcon_odc_opt2, odc_bypass, 0x0);
			}
			OVI_TCON_M17C0_WrFL(tcon_odc_opt2);
		}
				
		switch(enParam)
		{
			case LX_OVI_TCON_HIGH_LUM1_MSE_ON:
				OVI_REG_WR(0xC90AA7FC, 0x00101101);
				break;
			case LX_OVI_TCON_HIGH_LUM1_MSE_OFF:
				OVI_REG_WR(0xC90AA7FC, 0x00101001);
				break;
			case LX_OVI_TCON_HIGH_LUM2:
				OVI_REG_WR(0xC90AA7FC, 0x00102001);
				break;
			case LX_OVI_TCON_LOW_POWER1:
				OVI_REG_WR(0xC90AA7FC, 0x00100001);
				break;
			case LX_OVI_TCON_LOW_POWER2:
			case LX_OVI_TCON_LOW_POWER2_SC_OFF:
				OVI_REG_WR(0xC90AA7FC, 0x00103001);
				break;
			case LX_OVI_TCON_BOE_CINEMA:
			case LX_OVI_TCON_BOE_VIVID:
			case LX_OVI_TCON_BOE_UTUBE0:
			case LX_OVI_TCON_BOE_UTUBE1:
				if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
				{
					OVI_WPR_M17C0_RdFL(siw_reg_main);
					OVI_WPR_M17C0_Wr01(siw_reg_main, dga_mode_sel, enParam - LX_OVI_TCON_BOE_CINEMA);
					OVI_WPR_M17C0_WrFL(siw_reg_main);
				}
				break;
			case LX_OVI_TCON_MLE_MODE_OFF:
			default :
				OVI_REG_WR(0xC90AA7FC, 0x00000000);
				break;
		}
	} while(0);

	return ret;
}

int OVI_HW_M17_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr1 = NULL;
	UINT8 *u8tscicCtrlData = NULL;
	UINT32 tscicCtrlSizeNum;

	do {
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{

			if ((pstParams == NULL) || (_gOviHwM17Info.tscicWritingFlag == TRUE))
			{
				OVI_ERROR("[OVI] structure is pointed Null pointer! or already running!\n");
				ret = RET_ERROR;
				break;
			}

			if (pstParams->u32TscicSize == 0) // TSCIC disable for debug
			{
				// [NOTE] FCIC function enable/disable : 0xC90A50A8 [3:0] - 0x0/0xC
				// TCON path setting for FCIC
				OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
				OVI_TCON_M17C0_Wr01(tcon_odc_opt2, fcic_in_sel, 0x0);
				OVI_TCON_M17C0_Wr01(tcon_odc_opt2, dga_in_sel, 0x4);
				OVI_TCON_M17C0_WrFL(tcon_odc_opt2);

				// FCIC Clock gating ON
				CTOP_CTRL_M17A0_RdFL(DPE_SYN, crg_dpe00);
				CTOP_CTRL_M17A0_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 1);
				CTOP_CTRL_M17A0_WrFL(DPE_SYN, crg_dpe00);

				return RET_OK;
			}

			tscicCtrlSizeNum = pstParams->u32Ctrlsize;

			// check input table size
			if ((tscicCtrlSizeNum != OVI_HW_M17_INPUT_TSCIC_CTRL_SIZENUM) || (pstParams->pu8ControlTbl == NULL))
			{
				OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			if ((pstParams->u32TscicSize != OVI_HW_M17_INPUT_TSCIC_DATA_SIZE) || (pstParams->pu32TscicTbl == NULL))
			{
				OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
				ret = RET_ERROR;
				break;
			}

			_gOviHwM17Info.tscicSize = pstParams->u32TscicSize;

			// select address
			regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M17C0_BASE + offsetof(OVI_TCON_REG_M17C0_T, tcon_cic_reg000), 
												sizeof(UINT32)*OVI_HW_M17_INPUT_TSCIC_CTRL_SIZENUM);
			if (regAddr1 == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}

			u8tscicCtrlData = (UINT8 *)vmalloc(tscicCtrlSizeNum);

			if(u8tscicCtrlData == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user(u8tscicCtrlData, (void __user *)pstParams->pu8ControlTbl, tscicCtrlSizeNum);

			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			_gOviHwM17Info.tscicTbl = (UINT32 *)vmalloc(_gOviHwM17Info.tscicSize);

			if(_gOviHwM17Info.tscicTbl == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user(_gOviHwM17Info.tscicTbl, (void __user *)pstParams->pu32TscicTbl, _gOviHwM17Info.tscicSize);

			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				if(_gOviHwM17Info.tscicTbl != NULL)
				{
					vfree(_gOviHwM17Info.tscicTbl);
					_gOviHwM17Info.tscicTbl = NULL;
				}
				break;
			}

			// FCIC Clock gating OFF
			CTOP_CTRL_M17A0_RdFL(DPE_SYN, crg_dpe00);
			CTOP_CTRL_M17A0_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 0);
			CTOP_CTRL_M17A0_WrFL(DPE_SYN, crg_dpe00);

			// TCON path setting for FCIC
			OVI_TCON_M17C0_RdFL(tcon_odc_opt2);
			OVI_TCON_M17C0_Wr01(tcon_odc_opt2, fcic_in_sel, 0x3);
			OVI_TCON_M17C0_Wr01(tcon_odc_opt2, dga_in_sel, 0x3);
			OVI_TCON_M17C0_WrFL(tcon_odc_opt2);

			for(i=0; i<OVI_HW_M17_INPUT_TSCIC_CTRL_SIZENUM; i++)
			{
				writel_relaxed(u8tscicCtrlData[i], &regAddr1[i]);
			}

			_gOviHwM17Info.tscicThread = kthread_run(OVI_M17_TscicWriteThread, NULL, "ovi_tscic");

			if (IS_ERR(_gOviHwM17Info.tscicThread))
			{
				OVI_ERROR("[OVI] Error in starting thread! \n");
				ret = RET_ERROR;
				if(_gOviHwM17Info.tscicTbl != NULL)
				{
					vfree(_gOviHwM17Info.tscicTbl);
					_gOviHwM17Info.tscicTbl = NULL;
				}
				break;
			}

		}
		else
		{
			/* Do Nothing */
		}
	} while(0);

	if(u8tscicCtrlData != NULL)
		vfree(u8tscicCtrlData);
	if(regAddr1 != NULL)
		iounmap((void *)regAddr1);

	return ret;
}

int OVI_HW_M17_SetTconReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	UINT32 regField;

	do {
		OVI_TCON_M17_RdFL(tcon_control);
		OVI_TCON_M17_Rd01(tcon_control, epi_out, regField);
		if (!regField) break;
		
		OVI_TCON_M17_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_M17_Wr01(tcon_hor_mode, hor_reverse, _gOviHwM17Info.horReverseRegFieldValue ? 0 : 1);
		}
		else {
			OVI_TCON_M17_Wr01(tcon_hor_mode, hor_reverse, _gOviHwM17Info.horReverseRegFieldValue);
		}
		OVI_TCON_M17_WrFL(tcon_hor_mode);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetLvdsReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	UINT32 regField;

	do {
		OVI_TCON_M17_RdFL(tcon_control);
		OVI_TCON_M17_Rd01(tcon_control, epi_out, regField);
		if (regField) break;
		
		OVI_TCON_M17_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_M17_Wr01(tcon_hor_mode, hor_reverse, 0x1);
		}
		else {
			OVI_TCON_M17_Wr01(tcon_hor_mode, hor_reverse, 0x0);
		}
		OVI_TCON_M17_WrFL(tcon_hor_mode);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M17_RdFL(tcon_pgen_ctl);

		// pattern source color setting
		OVI_TCON_M17_RdFL(tcon_pgen_agpr1);
		OVI_TCON_M17_Wr(tcon_pgen_agpr1, 0x03FF);
		OVI_TCON_M17_WrFL(tcon_pgen_agpr1);

		OVI_TCON_M17_RdFL(tcon_pgen_agpg1);
		OVI_TCON_M17_Wr(tcon_pgen_agpg1, 0x03FF);
		OVI_TCON_M17_WrFL(tcon_pgen_agpg1);

		OVI_TCON_M17_RdFL(tcon_pgen_agpb1);
		OVI_TCON_M17_Wr(tcon_pgen_agpb1, 0x03FF);
		OVI_TCON_M17_WrFL(tcon_pgen_agpb1);

		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_TPG_OFF:		// pattern off
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x0);
				break;
			case LX_OVI_TCON_TPG_BLACK:		// black pattern
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x4);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_WHITE:		// white pattern
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HVBAR:		// HVBar pattern
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x3);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR16GREY:		// Horizontal 16 grey pattern
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x8);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR64GREY:		// Horizontal 64 grey pattern
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x7);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR256GREY:		// Horizontal 256 grey pattern
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x6);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR1024GREY:		// Horizontal 1024 grey pattern
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x5);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_VER16GREY:		// Vertical 16 grey pattern
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0xC);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default :
				break;
		}
		OVI_TCON_M17_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetChannelPower(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		_OVI_M17_DispOutputEnable(bParam);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_M17_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_LVDS_OUT_JEIDA:
				OVI_OIF_M17_Wr01(oif_lvds_config0, lvds_lsb_first, 0x0);
				break;
			case LX_OVI_LVDS_OUT_VESA:
				OVI_OIF_M17_Wr01(oif_lvds_config0, lvds_lsb_first, 0x1);
				break;
			default:
				break;
		}
		OVI_OIF_M17_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_M17_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_8BIT:
				OVI_OIF_M17_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x1);
				break;
			case LX_OVI_10BIT:
				OVI_OIF_M17_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x0);
				break;
			default:
				break;
		}
		OVI_OIF_M17_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetLvdsBlack(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_M17_RdFL(oif_lvds_config1);
		OVI_OIF_M17_RdFL(oif_lvds_config2);
		OVI_OIF_M17_RdFL(oif_vx1_config3);
		OVI_OIF_M17_RdFL(oif_vx1_config4);

		if(!bParam) // original data out
		{
			OVI_OIF_M17_Wr01(oif_lvds_config1, lvds_force_even_data, 0x0);
			OVI_OIF_M17_Wr01(oif_lvds_config2, lvds_force_odd_data, 0x0);

			OVI_OIF_M17_Wr01(oif_vx1_config3, vx1_force_even_data, 0x0);
			OVI_OIF_M17_Wr01(oif_vx1_config4, vx1_force_odd_data, 0x0);
		}
		else // black data out
		{
			OVI_OIF_M17_Wr01(oif_lvds_config1, lvds_force_even_data, 0x40000000);
			OVI_OIF_M17_Wr01(oif_lvds_config2, lvds_force_odd_data, 0x40000000);

			OVI_OIF_M17_Wr01(oif_vx1_config3, vx1_force_even_data, 0x40000000);
			OVI_OIF_M17_Wr01(oif_vx1_config4, vx1_force_odd_data, 0x40000000);
		}
		OVI_OIF_M17_WrFL(oif_lvds_config1);
		OVI_OIF_M17_WrFL(oif_lvds_config2);
		OVI_OIF_M17_WrFL(oif_vx1_config3);
		OVI_OIF_M17_WrFL(oif_vx1_config4);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetClock(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M17_RdFL(tcon_gclk_control);
		OVI_TCON_M17_RdFL(tcon_mclk_control);

		if(bParam)
		{
			OVI_TCON_M17_Wr01(tcon_gclk_control, gclk_en, 0x1);
			OVI_TCON_M17_Wr01(tcon_mclk_control, mclk_en, 0x1);
		}
		else
		{
			OVI_TCON_M17_Wr01(tcon_gclk_control, gclk_en, 0x0);
			OVI_TCON_M17_Wr01(tcon_mclk_control, mclk_en, 0x0);
		}

		OVI_TCON_M17_WrFL(tcon_gclk_control);
		OVI_TCON_M17_WrFL(tcon_mclk_control);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetEpiDataScramble(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M17_RdFL(tcon_epi_mode);

		if(bParam)
		{
			OVI_TCON_M17_Wr01(tcon_epi_mode, scr_en, 0x1);
		}
		else
		{
			OVI_TCON_M17_Wr01(tcon_epi_mode, scr_en, 0x0);
		}

		OVI_TCON_M17_WrFL(tcon_epi_mode);
	} while(0);

	return ret;
}

int OVI_HW_M17_SetAdvanced10bit(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			OVI_TCON_M17C0_RdFL(a10_ctrl);
			OVI_TCON_M17C0_RdFL(tcon_odc_opt2);

			if(bParam)
			{
				OVI_TCON_M17C0_Wr01(a10_ctrl, a10_on, 0x1);
				OVI_TCON_M17C0_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x1);
			}
			else
			{
				OVI_TCON_M17C0_Wr01(a10_ctrl, a10_on, 0x0);
				OVI_TCON_M17C0_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x0);
			}

			OVI_TCON_M17C0_WrFL(a10_ctrl);
			OVI_TCON_M17C0_WrFL(tcon_odc_opt2);
		}
		else
		{
			/* Do Nothing */
		}
	} while(0);

	return ret;
}

int OVI_HW_M17_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam)
{
	int ret = RET_OK;
	UINT16 *u16vcomPatData = NULL;
	int i,k,idx;

	do {
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			UINT32 patData[4] = {0,0,0,0};
			UINT32 level = 0;

			if (pstParam == NULL)
			{
				OVI_ERROR("[OVI] structure is pointed Null pointer! \n");
				ret = RET_ERROR;
				break;
			}

			if (OVI_HW_M17_INPUT_VCOM_PAT_DATA_SIZE != pstParam->sizeNum)
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

			OVI_TCON_M17C0_RdFL(tcon_pgen_vcomp0);
			OVI_TCON_M17C0_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, patData[0]);
			OVI_TCON_M17C0_WrFL(tcon_pgen_vcomp0);

			OVI_TCON_M17C0_RdFL(tcon_pgen_vcomp1);
			OVI_TCON_M17C0_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, patData[1]);
			OVI_TCON_M17C0_WrFL(tcon_pgen_vcomp1);

			OVI_TCON_M17C0_RdFL(tcon_pgen_vcomp2);
			OVI_TCON_M17C0_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, patData[2]);
			OVI_TCON_M17C0_WrFL(tcon_pgen_vcomp2);

			OVI_TCON_M17C0_RdFL(tcon_pgen_vcomp3);
			OVI_TCON_M17C0_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, patData[3]);
			OVI_TCON_M17C0_WrFL(tcon_pgen_vcomp3);

			if (level > 0)
			{
				OVI_TCON_M17C0_RdFL(tcon_pgen_agpr1);
				OVI_TCON_M17C0_Wr01(tcon_pgen_agpr1, pgen_color_r1, level);
				OVI_TCON_M17C0_WrFL(tcon_pgen_agpr1);

				OVI_TCON_M17C0_RdFL(tcon_pgen_agpg1);
				OVI_TCON_M17C0_Wr01(tcon_pgen_agpg1, pgen_color_g1, level);
				OVI_TCON_M17C0_WrFL(tcon_pgen_agpg1);

				OVI_TCON_M17C0_RdFL(tcon_pgen_agpb1);
				OVI_TCON_M17C0_Wr01(tcon_pgen_agpb1, pgen_color_b1, level);
				OVI_TCON_M17C0_WrFL(tcon_pgen_agpb1);
			}

		}
		else
		{
			/* Do Nothing */
		}
	} while(0);

	if(u16vcomPatData != NULL)
		vfree(u16vcomPatData);

	return ret;
}

int OVI_HW_M17_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam)
{
	int ret = RET_OK;

	do {
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			OVI_TCON_M17_RdFL(tcon_pgen_ctl);

			switch(enParam)
			{
				case LX_OVI_TCON_VCOM_PAT_CTRL_OFF:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x0);

					OVI_TCON_M17C0_RdFL(tcon_pgen_vcomp0);
					OVI_TCON_M17C0_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, 0x0);
					OVI_TCON_M17C0_WrFL(tcon_pgen_vcomp0);

					OVI_TCON_M17C0_RdFL(tcon_pgen_vcomp1);
					OVI_TCON_M17C0_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, 0x0);
					OVI_TCON_M17C0_WrFL(tcon_pgen_vcomp1);

					OVI_TCON_M17C0_RdFL(tcon_pgen_vcomp2);
					OVI_TCON_M17C0_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, 0x0);
					OVI_TCON_M17C0_WrFL(tcon_pgen_vcomp2);

					OVI_TCON_M17C0_RdFL(tcon_pgen_vcomp3);
					OVI_TCON_M17C0_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, 0x0);
					OVI_TCON_M17C0_WrFL(tcon_pgen_vcomp3);

					OVI_TCON_M17C0_RdFL(tcon_pgen_agpr1);
					OVI_TCON_M17C0_Wr01(tcon_pgen_agpr1, pgen_color_r1, 0x3FF);
					OVI_TCON_M17C0_WrFL(tcon_pgen_agpr1);

					OVI_TCON_M17C0_RdFL(tcon_pgen_agpg1);
					OVI_TCON_M17C0_Wr01(tcon_pgen_agpg1, pgen_color_g1, 0x3FF);
					OVI_TCON_M17C0_WrFL(tcon_pgen_agpg1);

					OVI_TCON_M17C0_RdFL(tcon_pgen_agpb1);
					OVI_TCON_M17C0_Wr01(tcon_pgen_agpb1, pgen_color_b1, 0x3FF);
					OVI_TCON_M17C0_WrFL(tcon_pgen_agpb1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_ON:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x1E);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM1:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x16);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM2:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x17);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM3:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x18);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM4:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x19);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM5:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x1A);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM6:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x1B);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM7:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x1C);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM8:
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_mode, 0x1D);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
					OVI_TCON_M17_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
					break;
				default:
					break;
			}

			OVI_TCON_M17_WrFL(tcon_pgen_ctl);
		}
		else
		{
			/* Do Nothing */
		}
	} while(0);

	return ret;
}

int OVI_HW_M17_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams)
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
		
		if (memcmp(&_gOviHwM17Info.dispOption, pstParams, sizeof(LX_OVI_DISPLAY_INFO_T)) != 0)
		{
			OVI_PRINT("\n[OVI_HW_M17_DisplayResume] WARN:Disp Option Changed! [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
				pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
				pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
				pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
				pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);
		}

		_OVI_M17_DispOutputEnable(TRUE);
	} while(0);

	return ret;
}

int OVI_HW_M17_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int	i;
	UINT32 val;

	switch(proc_id)
	{
		case OVI_HAL_PROC_ID_DETAIL_INFO:
		{
			OVI_TCON_M17_RdFL(tcon_base_address);
			val = OVI_TCON_M17_Rd(tcon_base_address);
			seq_printf(m, "tcon_base_addr: 0x%08x\n", val);

			seq_printf(m, "ch_power_on_reg1: 0x%08x\n", _gOviHwM17Info.chPowerOnRegValue1 );
			seq_printf(m, "ch_power_on_reg2: 0x%08x\n", _gOviHwM17Info.chPowerOnRegValue2 );

			for (i=0; i<_gOVIOutputModes_M17.number_of_modes; i++)
			{
				seq_printf(m, "output_mode%d: %s", i, _gOVIOutputModes_M17.pOVIOutputModes[i].index + strlen("Display settings for M17"));
			}

			OVI_OIF_M17_RdFL(oif_lvds_config0);

			OVI_OIF_M17_Rd01(oif_lvds_config0, lvds_lsb_first, val);
			seq_printf(m, "lvds.format: %s (0x%x)\n", (val)?"vesa":"jeida", val);

			OVI_OIF_M17_Rd01(oif_lvds_config0, lvds_8bit_mode, val);
			seq_printf(m, "lvds.bit: %d bit (0x%x)\n", (val)? 8:10, val);

			OVI_OIF_M17_RdFL(oif_lvds_config1);
			OVI_OIF_M17_Rd01(oif_lvds_config1, lvds_force_even_data, val);
			seq_printf(m, "lvds.black_out: %s (0x%x)\n", (val)? "black":"orignal", val);

			OVI_TCON_M17_RdFL(tcon_gclk_control);
			OVI_TCON_M17_Rd01(tcon_gclk_control, gclk_en, val);
			seq_printf(m, "tcon.gclk: %s (0x%x)\n", (val)?"on":"off", val);

			OVI_TCON_M17_RdFL(tcon_mclk_control);
			OVI_TCON_M17_Rd01(tcon_mclk_control, mclk_en, val);
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
