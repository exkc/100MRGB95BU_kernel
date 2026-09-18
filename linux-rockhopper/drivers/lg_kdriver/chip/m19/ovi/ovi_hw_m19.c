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
#include "ovi_hw_m19.h"
#include "ovi_reg_def_m19.h"
#include "ovi_reg_m19.h"

#include "../be/reg/be_reg_dpe_m19.h"

// For CTOP register access
#include "../../../core/sys/sys_regs.h"

#include "ovi_output_format_m19a0.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define OVI_HW_M19_GAMMA_TABLE_SIZENUM 1024
#define OVI_HW_M19_LGD_MPLUS_LUT_SIZENUM 928
#define OVI_HW_M19_BOE_MPLUS_LUT_SIZENUM 256
#define OVI_HW_M19_INPUT_OD_SIZENUM (17*17)
#define OVI_HW_M19_INPUT_LOD_SIZENUM (876)
#define OVI_HW_M19_INPUT_POD2_SIZENUM (1848)
#define OVI_HW_M19_INPUT_TSCIC_CTRL_SIZENUM (43)
#define OVI_HW_M19_INPUT_TSCIC_DATA_SIZE (377612)
#define OVI_HW_M19_INPUT_VCOM_PAT_DATA_SIZE (96)
#define OVI_HW_M19_WB_GAIN_STEP	26	// 0.26% step per w/b gain 1
#define OVI_HW_M19_WB_OFFSET_STEP 8	// 8 step per w/b offset 1
#define OVI_HW_M19_WB_DEFAULT_GAIN 16384

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


#define OVI_HW_M19_CH_POWER_REG_MASK	0xFFFFFF

#define OVI_HW_M19_REG_PARAM_OP_WRITE		0x0
#define OVI_HW_M19_REG_PARAM_OP_WAIT		0x1
#define OVI_HW_M19_REG_PARAM_OP_CHECK		0x2
#define OVI_HW_M19_REG_PARAM_OP_RESERVED	0x3
#define OVI_HW_M19_REG_PARAM_OP_MASK		0x3

#define OVI_HW_M19_REG_SET_A0_START		0x000000A0
#define OVI_HW_M19_REG_SET_B0_START		0x000000B0
// Max Value < 0x000000A0
#define OVI_HW_M19_REG_READ_START		0x00000001
#define OVI_HW_M19_REG_CHECK_END		0x00000000

#define OVI_HW_M19_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define OVI_HW_M19_BOE_FW_SIZENUM 32256

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	UINT32 chPowerOnRegValue1;
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

	UINT32 tconClkGatingRegValue;

	LX_OVI_DISPLAY_INFO_T dispOption;

	struct task_struct* tscicThread;
	BOOLEAN tscicWritingFlag;
	UINT32 tscicSize;
	UINT32 *tscicU32Tbl;
	UINT32 tscicCtrlSizeNum;
	UINT8 *tscicU8CtrlData;
} OVI_HW_M19_INFO_T;

typedef struct{
	LX_OVI_OUTPUT_MODE_T	*pOVIOutputModes;
	UINT32 number_of_modes;
} OVI_HW_M19_OUTPUT_MODES_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_MEMCFG_T *gpOviTconMem;

extern DPE_LED_REG_M19_T gDPE_LED_M19;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
OVI_TCON_REG_M19_T gOVI_TCON_M19;
OVI_TCON_LODC_REG_M19_T gOVI_TCON_LODC_M19;
OVI_TCON_CAD_REG_M19_T gOVI_TCON_CAD_M19;
OVI_OIF_REG_M19_T gOVI_OIF_M19;
OVI_WPR_REG_M19_T gOVI_WPR_M19;

static volatile unsigned int *gMapped_address;

LX_OVI_OUTPUT_MODE_T _gOVIOutputModes_M19Ax[] =
{
	{"Disp-M19 4k60Hz Vx1\n",  ovi_m19a0_disp_4k60_vx1_8lane, sizeof(ovi_m19a0_disp_4k60_vx1_8lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-M19 4k120Hz Vx1\n",  ovi_m19a0_disp_4k120_vx1_16lane, sizeof(ovi_m19a0_disp_4k120_vx1_16lane)/sizeof(LX_OVI_REG_T)},
	{"Disp-M19 4k60Hz EPI\n",  ovi_m19a0_disp_4k60_epi, sizeof(ovi_m19a0_disp_4k60_epi)/sizeof(LX_OVI_REG_T)},
	{"Disp-M19 4k120Hz EPI\n",  ovi_m19a0_disp_4k120_epi, sizeof(ovi_m19a0_disp_4k120_epi)/sizeof(LX_OVI_REG_T)},
	{"Disp-M19 4k60Hz CEDS\n",  ovi_m19a0_disp_4k60_ceds, sizeof(ovi_m19a0_disp_4k60_ceds)/sizeof(LX_OVI_REG_T)},
	{"Disp-M19 4k120Hz CEDS\n",  ovi_m19a0_disp_4k120_ceds, sizeof(ovi_m19a0_disp_4k120_ceds)/sizeof(LX_OVI_REG_T)},
	{"Disp-M19 2k60Hz LVDS\n",  ovi_m19a0_disp_2k60_lvds_2link, sizeof(ovi_m19a0_disp_2k60_lvds_2link)/sizeof(LX_OVI_REG_T)},
	{"Disp-M19 2k120Hz LVDS\n",  ovi_m19a0_disp_2k120_lvds_4link, sizeof(ovi_m19a0_disp_2k120_lvds_4link)/sizeof(LX_OVI_REG_T)}
};

OVI_HW_M19_OUTPUT_MODES_T _gOVIOutputModes_M19 =
{
	.pOVIOutputModes 	 = NULL,
	.number_of_modes	 = 0,
};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static UINT32 _OVI_M19_GetGain(UINT32 gain);
static SINT16 _OVI_M19_GetOffset(UINT32 offset);
static void _OVI_M19_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore);
static void _OVI_M19_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);
static void _OVI_M19_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset);

static void _OVI_M19_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_M19_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams);
static void _OVI_M19_DispOutputEnable(BOOLEAN bParam);

/*----------------------------------------------------------------------------------------
	Internal Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int OVI_M19_TscicWriteThread(void* data);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static UINT32 _gPrevRedGain = OVI_HW_M19_WB_DEFAULT_GAIN;
static UINT32 _gPrevGreenGain = OVI_HW_M19_WB_DEFAULT_GAIN;
static UINT32 _gPrevBlueGain = OVI_HW_M19_WB_DEFAULT_GAIN;

static SINT16 _gPrevRedOffset = 0;
static SINT16 _gPrevGreenOffset = 0;
static SINT16 _gPrevBlueOffset = 0;

static LX_OVI_TCON_COLOR_TEMP_T _gColTemp;

static OVI_HW_M19_INFO_T _gOviHwM19Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
static void _OVI_M19_IgnoreRegSet(UINT32 regParamVal, BOOLEAN *pbIgnore)
{
	if (regParamVal >= OVI_HW_M19_REG_SET_A0_START)
	{
		if (lx_chip_rev() >= LX_CHIP_REV(M19, B0))
		{
			if (regParamVal != OVI_HW_M19_REG_SET_B0_START)
			{
				*pbIgnore = TRUE;
			}
		}
		else
		{
			if (regParamVal != OVI_HW_M19_REG_SET_A0_START)
			{
				*pbIgnore = TRUE;
			}
		}
	}
	else if (regParamVal == OVI_HW_M19_REG_CHECK_END)
	{
		*pbIgnore = FALSE;
	}

	return;
}

static void _OVI_M19_RegParamSet(const LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN ignore = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_M19_REG_PARAM_OP_MASK)
		{
			case OVI_HW_M19_REG_PARAM_OP_WAIT:	// wait
				if (!ignore)
				{
					OS_UsecDelay(param->value);
				}
				OVI_DEBUG("delay(_%dms);\n", param->value/1000);
				break;

			case OVI_HW_M19_REG_PARAM_OP_CHECK:	// check
				_OVI_M19_IgnoreRegSet(param->value, &ignore);
				OVI_DEBUG("ignore : %d\n", ignore);
				break;

			case OVI_HW_M19_REG_PARAM_OP_RESERVED:
				OVI_DEBUG("OVI_HW_M19_REG_PARAM_OP_RESERVED\n");
				break;

			default:	// OVI_HW_M19_REG_PARAM_OP_WRITE
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

static void _OVI_M19_RegParamRead(LX_OVI_REG_T *param, UINT32 cnt, UINT32 addrOffset)
{
	BOOLEAN readReg = FALSE;
	
	while(cnt--)
	{
		switch(param->addr & OVI_HW_M19_REG_PARAM_OP_MASK)
		{
			case OVI_HW_M19_REG_PARAM_OP_CHECK:	// check for register read
				if (param->value == OVI_HW_M19_REG_READ_START)
				{
					readReg = TRUE;
				}
				else if (param->value == OVI_HW_M19_REG_CHECK_END)
				{
					readReg = FALSE;
				}
				OVI_DEBUG("readReg : %d\n", readReg);
				break;

			default:	// OVI_HW_M19_REG_PARAM_OP_WRITE
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

static void _OVI_M19_DispRegDataInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));
	
	switch (stDispParams.panelFramerate)
	{
		case LX_OVI_PANEL_FRAMERATE_60HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
				case LX_OVI_PANEL_EPI_QSAC:
					_OVI_M19_RegParamRead(ovi_m19a0_disp_4k60_epi, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k60_epi), 0);	
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M19_RegParamRead(ovi_m19a0_disp_4k60_vx1_8lane, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k60_vx1_8lane), 0);
					break;

				case LX_OVI_PANEL_CEDS:
					_OVI_M19_RegParamRead(ovi_m19a0_disp_4k60_ceds, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k60_ceds), 0);
					break;

				case LX_OVI_PANEL_LVDS:
				default :
					_OVI_M19_RegParamRead(ovi_m19a0_disp_2k60_lvds_2link, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_2k60_lvds_2link), 0);
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					_OVI_M19_RegParamRead(ovi_m19a0_disp_4k120_epi, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k120_epi), 0);
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M19_RegParamRead(ovi_m19a0_disp_4k120_vx1_16lane, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k120_vx1_16lane), 0);
					break;

				case LX_OVI_PANEL_CEDS:
					_OVI_M19_RegParamRead(ovi_m19a0_disp_4k120_ceds, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k120_ceds), 0);
					break;

				case LX_OVI_PANEL_LVDS:
				default :
					_OVI_M19_RegParamRead(ovi_m19a0_disp_2k120_lvds_4link, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_2k120_lvds_4link), 0);
					break;
			}
			break;

		default :
			break;
	}

	if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_EDGE_LED
		|| stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_DIRECT_L)
	{
		_OVI_M19_RegParamRead(ovi_m19a0_led_spi, OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_led_spi), 0);
	}
	
	return;
}

static void _OVI_M19_DispInit(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	LX_OVI_DISPLAY_INFO_T stDispParams;
	UINT32 regVal;

	OVI_PRINT("\n[_OVI_M19_DispInit] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
		pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
		pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker,
		pstParams->panelBacklight, pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
		pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

	memcpy((void *)&stDispParams, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

	// Display Spread Spectrum
	if (_gOviHwM19Info.spreadSpectrumRegValue1 & 0x4) // DSS OFF
	{
		OVI_REG_WR(0xC9C10438, 0xFB800000); //Power Down for DISP PLL setting (not for DISP SS setting)
		
		OVI_REG_WR(0xC930A084, _gOviHwM19Info.spreadSpectrumRegValue1);
		OVI_REG_WR(0xC930A088, _gOviHwM19Info.spreadSpectrumRegValue2);

		OVI_REG_WR(0xC9C10438, 0xFF800000); //Power On
	}
	else
	{
		OVI_REG_WR(0xC9C10438, 0xFB800000); //Power Down for DISP PLL setting (not for DISP SS setting)
		
		OVI_REG_WR(0xC930A084, _gOviHwM19Info.spreadSpectrumRegValue1 | 0x4);
		OVI_REG_WR(0xC930A088, _gOviHwM19Info.spreadSpectrumRegValue2);

		OVI_REG_RD(0xC930A08C, regVal);
		regVal = (regVal | (0x01400000));
		OVI_REG_WR(0xC930A08C, regVal);

		OVI_REG_WR(0xC9C10438, 0xFF800000); //Power On

		OS_UsecDelay(100);

		OVI_REG_WR(0xC930A084, _gOviHwM19Info.spreadSpectrumRegValue1);
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
					_OVI_M19_RegParamSet(ovi_m19a0_disp_4k60_epi, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k60_epi), 0);	
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M19_RegParamSet(ovi_m19a0_disp_4k60_vx1_8lane, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k60_vx1_8lane), 0);

					if (stDispParams.panelMaker == LX_OVI_PANEL_MAKER_SHARP)
					{
						OVI_REG_RD(0xC9070300, regVal);
						regVal = (regVal & (~0x1F000)) | (2 << 12);
						OVI_REG_WR(0xC9070300, regVal);

						OVI_REG_WR(0xC907000C, 0x0000000E);
						OVI_REG_WR(0xC9079098, 0x00020406);
						OVI_REG_WR(0xC907909C, 0x01030507);
					}
					break;

				case LX_OVI_PANEL_CEDS:
					_OVI_M19_RegParamSet(ovi_m19a0_disp_4k60_ceds, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k60_ceds), 0);
					break;

				case LX_OVI_PANEL_LVDS:
				default :
					_OVI_M19_RegParamSet(ovi_m19a0_disp_2k60_lvds_2link, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_2k60_lvds_2link), 0);
					break;
			}
			break;

		case LX_OVI_PANEL_FRAMERATE_120HZ:
			switch (stDispParams.panelInterface)
			{
				case LX_OVI_PANEL_EPI:
					_OVI_M19_RegParamSet(ovi_m19a0_disp_4k120_epi, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k120_epi), 0);
					break;

				case LX_OVI_PANEL_VX1:
					_OVI_M19_RegParamSet(ovi_m19a0_disp_4k120_vx1_16lane, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k120_vx1_16lane), 0);
					break;

				case LX_OVI_PANEL_CEDS:
					_OVI_M19_RegParamSet(ovi_m19a0_disp_4k120_ceds, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_4k120_ceds), 0);
					break;

				case LX_OVI_PANEL_LVDS:
				default :
					_OVI_M19_RegParamSet(ovi_m19a0_disp_2k120_lvds_4link, 
											OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_disp_2k120_lvds_4link), 0);
					break;
			}
			break;

		default :
			break;
	}

	// Clock Gating ON
	CTOP_CTRL_M19Ax_RdFL(DPE_SYN, crg_dpe00);
	CTOP_CTRL_M19Ax_Wr(DPE_SYN, crg_dpe00, _gOviHwM19Info.tconClkGatingRegValue);
	CTOP_CTRL_M19Ax_WrFL(DPE_SYN, crg_dpe00);
	
	// Local Dimming settings
	CTOP_CTRL_M19Ax_RdFL(CTOP_FMS, ctop_fms_r06);
	CTOP_CTRL_M19Ax_Wr01(CTOP_FMS, ctop_fms_r06, reg_jtag0_disable, 1);
	CTOP_CTRL_M19Ax_WrFL(CTOP_FMS, ctop_fms_r06);

	if (stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_EDGE_LED
		|| stDispParams.panelBacklight == LX_OVI_PANEL_BACKLIGHT_DIRECT_L)
	{
		_OVI_M19_RegParamSet(ovi_m19a0_led_spi, OVI_HW_M19_ARRAY_SIZE(ovi_m19a0_led_spi), 0);
	}
	
	return;
}

static void _OVI_M19_DispOutputEnable(BOOLEAN bParam)
{
	if (bParam && _gOviHwM19Info.dispOption.panelInterface == LX_OVI_PANEL_CEDS)
	{
		// Soft reset(WPR, SIW, FCIC, Pix)
		CTOP_CTRL_M19Ax_RdFL(DPE_SYN, crg_dpe02);
		CTOP_CTRL_M19Ax_Wr(DPE_SYN, crg_dpe02, 0x1F3810);
		CTOP_CTRL_M19Ax_WrFL(DPE_SYN, crg_dpe02);
	}

	CTOP_CTRL_M19Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
	if (bParam)// display output on
	{
		CTOP_CTRL_M19Ax_Wr(CTOP_DPE, ctop_dpe_r42, _gOviHwM19Info.chPowerOnRegValue1);
		OVI_DEBUG("[OVI] display is changed to ON status!\n");
	}
	else // display output off
	{
		CTOP_CTRL_M19Ax_Wr(CTOP_DPE, ctop_dpe_r42, _gOviHwM19Info.chPowerOnRegValue1 & (~OVI_HW_M19_CH_POWER_REG_MASK));
		OVI_DEBUG("[OVI] display is changed to OFF status!\n");
	}
	CTOP_CTRL_M19Ax_WrFL(CTOP_DPE, ctop_dpe_r42);

	if (_gOviHwM19Info.dispOption.panelInterface == LX_OVI_PANEL_EPI
		|| _gOviHwM19Info.dispOption.panelInterface == LX_OVI_PANEL_CEDS)
	{
		OVI_TCON_M19_RdFL(tcon_gclk_control);
		OVI_TCON_M19_RdFL(tcon_mclk_control);

		if(bParam)
		{
			OVI_TCON_M19_Wr01(tcon_gclk_control, gclk_en, 0x1);
			OVI_TCON_M19_Wr01(tcon_mclk_control, mclk_en, 0x1);
		}
		else
		{
			OVI_TCON_M19_Wr01(tcon_gclk_control, gclk_en, 0x0);
			OVI_TCON_M19_Wr01(tcon_mclk_control, mclk_en, 0x0);
		}

		OVI_TCON_M19_WrFL(tcon_gclk_control);
		OVI_TCON_M19_WrFL(tcon_mclk_control);
	}

	if (bParam)
	{
		// SW reset(TCON, WPR, SIW, FCIC, Pix, Pix2) release
		CTOP_CTRL_M19Ax_RdFL(DPE_SYN, crg_dpe02);
		CTOP_CTRL_M19Ax_Wr(DPE_SYN, crg_dpe02, 0x0);
		CTOP_CTRL_M19Ax_WrFL(DPE_SYN, crg_dpe02);

		if (_gOviHwM19Info.dispOption.panelInterface == LX_OVI_PANEL_CEDS)
		{
			UINT32 regField;
			
			OVI_TCON_LODC_M19_RdFL(lodc_lut_upload);
			OVI_TCON_LODC_M19_Rd01(lodc_lut_upload, lodc_upload, regField);
			if (regField == 1)
			{
				OVI_TCON_LODC_M19_Wr01(lodc_lut_upload, lodc_upload, 0x0);
				OVI_TCON_LODC_M19_WrFL(lodc_lut_upload);

				OVI_TCON_LODC_M19_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_M19_Wr01(lodc_lut_upload, lodc_upload, 0x1);
				OVI_TCON_LODC_M19_WrFL(lodc_lut_upload);
			}
		}
	}

	return;
}

int OVI_M19_TscicWriteThread(void* data)
{
	int ret = RET_OK;
	int i;
	volatile UINT32 *regAddr = NULL;
	UINT32 tscicSizeNum;
	UINT32 tscicCtrlSizeNum;

	do {

		if (_gOviHwM19Info.tscicWritingFlag == TRUE)
		{
			OVI_ERROR("[OVI] already running!\n");
			ret = RET_ERROR;
			return ret;
		}

		_gOviHwM19Info.tscicWritingFlag = TRUE;

		// check input table size
		if ((_gOviHwM19Info.tscicCtrlSizeNum != OVI_HW_M19_INPUT_TSCIC_CTRL_SIZENUM) || (_gOviHwM19Info.tscicU8CtrlData == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}
		
		if ((_gOviHwM19Info.tscicSize != OVI_HW_M19_INPUT_TSCIC_DATA_SIZE) || (_gOviHwM19Info.tscicU32Tbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		tscicSizeNum = _gOviHwM19Info.tscicSize / sizeof(UINT32);
		tscicCtrlSizeNum = _gOviHwM19Info.tscicCtrlSizeNum;

		// FCIC data setting
		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE + offsetof(OVI_TCON_REG_M19A0_T, tcon_fcic_data_a), 
											sizeof(UINT32));
		if (regAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		OVI_TCON_M19_RdFL(tcon_fcic_ctrl);
		OVI_TCON_M19_Wr01(tcon_fcic_ctrl, checksum_clr, 0x0);
		OVI_TCON_M19_Wr01(tcon_fcic_ctrl, flash_done, 0x0);
		OVI_TCON_M19_WrFL(tcon_fcic_ctrl);

		OVI_TCON_M19_RdFL(tcon_fcic_addr);
		OVI_TCON_M19_Wr01(tcon_fcic_addr, flash_addr, 0x0);
		OVI_TCON_M19_WrFL(tcon_fcic_addr);

		for (i=0; i<tscicSizeNum; i++)
		{
			if (kthread_should_stop())
			{
				ret = RET_ERROR;

				if(_gOviHwM19Info.tscicU8CtrlData != NULL)
				{
					vfree(_gOviHwM19Info.tscicU8CtrlData);
					_gOviHwM19Info.tscicU8CtrlData = NULL;
				}
				if (_gOviHwM19Info.tscicU32Tbl != NULL)
				{
					vfree(_gOviHwM19Info.tscicU32Tbl);
					_gOviHwM19Info.tscicU32Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwM19Info.tscicThread = NULL;
				_gOviHwM19Info.tscicWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwM19Info.tscicU32Tbl[i], &regAddr[0]);
		}

		OVI_TCON_M19_RdFL(tcon_fcic_ctrl);
		OVI_TCON_M19_Wr01(tcon_fcic_ctrl, flash_done, 0x1);
		OVI_TCON_M19_WrFL(tcon_fcic_ctrl);

		iounmap((void *)regAddr);
		regAddr = NULL;

		// FCIC CTRL data setting
		regAddr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE + offsetof(OVI_TCON_REG_M19A0_T, tcon_cic_reg000), 
											sizeof(UINT32)*OVI_HW_M19_INPUT_TSCIC_CTRL_SIZENUM);
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

				if(_gOviHwM19Info.tscicU8CtrlData != NULL)
				{
					vfree(_gOviHwM19Info.tscicU8CtrlData);
					_gOviHwM19Info.tscicU8CtrlData = NULL;
				}
				if (_gOviHwM19Info.tscicU32Tbl != NULL)
				{
					vfree(_gOviHwM19Info.tscicU32Tbl);
					_gOviHwM19Info.tscicU32Tbl = NULL;
				}
				if (regAddr != NULL)
					iounmap((void *)regAddr);

				_gOviHwM19Info.tscicThread = NULL;
				_gOviHwM19Info.tscicWritingFlag = FALSE;

				return ret;
			}
			writel_relaxed(_gOviHwM19Info.tscicU8CtrlData[i], &regAddr[i]);
		}

		OVI_TCON_M19_RdFL(tcon_init_test);
		OVI_TCON_M19_Wr01(tcon_init_test, init1_test, 0x1);
		OVI_TCON_M19_Wr01(tcon_init_test, init2_test, 0x1);
		OVI_TCON_M19_WrFL(tcon_init_test);
	} while(0);

	if(_gOviHwM19Info.tscicU8CtrlData != NULL)
	{
		vfree(_gOviHwM19Info.tscicU8CtrlData);
		_gOviHwM19Info.tscicU8CtrlData = NULL;
	}
	if (_gOviHwM19Info.tscicU32Tbl != NULL)
	{
		vfree(_gOviHwM19Info.tscicU32Tbl);
		_gOviHwM19Info.tscicU32Tbl = NULL;
	}
	if (regAddr != NULL)
		iounmap((void *)regAddr);

	_gOviHwM19Info.tscicThread = NULL;
	_gOviHwM19Info.tscicWritingFlag = FALSE;

	return ret;
}

int OVI_HW_M19_Initialize(void)
{
	int ret = RET_OK;

	do {
		OVI_PRINT("OVI chip revision is set to M19 A0\n");

		/* Set configuration of Output mode presets, for mode change on run time */
		_gOVIOutputModes_M19.pOVIOutputModes = _gOVIOutputModes_M19Ax;
		_gOVIOutputModes_M19.number_of_modes	 = sizeof(_gOVIOutputModes_M19Ax)/sizeof(LX_OVI_OUTPUT_MODE_T);

		gOVI_TCON_M19.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_REG_M19A0_T));
		gOVI_TCON_LODC_M19.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_LODC_REG_M19A0_T));
		gOVI_TCON_CAD_M19.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_TCON_CAD_REG_M19A0_T));
		gOVI_OIF_M19.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_OIF_REG_M19A0_T));
		gOVI_WPR_M19.shdw.addr = (UINT32 *)OS_KMalloc(sizeof(OVI_WPR_REG_M19A0_T));

		gOVI_TCON_M19.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE, sizeof(OVI_TCON_REG_M19A0_T));
		gOVI_TCON_LODC_M19.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_M19A0_BASE, sizeof(OVI_TCON_LODC_REG_M19A0_T));
		gOVI_TCON_CAD_M19.phys.addr = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_M19A0_BASE, sizeof(OVI_TCON_CAD_REG_M19A0_T));
		gOVI_OIF_M19.phys.addr = (volatile UINT32 *)ioremap(OVI_OIF_REG_M19A0_BASE, sizeof(OVI_OIF_REG_M19A0_T));
		gOVI_WPR_M19.phys.addr = (volatile UINT32 *)ioremap(OVI_WPR_REG_M19A0_BASE, sizeof(OVI_WPR_REG_M19A0_T));

		/* for copying value used in channel power on/off function */
		CTOP_CTRL_M19Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
		_gOviHwM19Info.chPowerOnRegValue1 = CTOP_CTRL_M19Ax_Rd(CTOP_DPE, ctop_dpe_r42);

		/* for copying value used in H-Reverse on/off function */
		OVI_TCON_M19_RdFL(tcon_hor_mode);
		OVI_TCON_M19_Rd01(tcon_hor_mode, hor_reverse, _gOviHwM19Info.horReverseRegFieldValue);

		/* for copying value used in spread spectrum on/off & display resume function */
		CTOP_CTRL_M19Ax_RdFL(CTOP_DPE, ctop_dpe_r33);
		_gOviHwM19Info.spreadSpectrumRegValue1 = CTOP_CTRL_M19Ax_Rd(CTOP_DPE, ctop_dpe_r33);
		CTOP_CTRL_M19Ax_RdFL(CTOP_DPE, ctop_dpe_r34);
		_gOviHwM19Info.spreadSpectrumRegValue2 = CTOP_CTRL_M19Ax_Rd(CTOP_DPE, ctop_dpe_r34);

		/* for copying value used in display resume function */
		CTOP_CTRL_M19Ax_RdFL(DPE_SYN, crg_dpe00);
		_gOviHwM19Info.tconClkGatingRegValue = CTOP_CTRL_M19Ax_Rd(DPE_SYN, crg_dpe00);

		/* for copying value used in bypass function */
		OVI_TCON_M19_RdFL(tcon_odc_opt2);
		OVI_TCON_M19_Rd01(tcon_odc_opt2, odc_bypass, _gOviHwM19Info.odcBypassRegFieldValue); 
		OVI_TCON_M19_RdFL(tcon_btc_config);
		OVI_TCON_M19_Rd01(tcon_btc_config, lodc_bypass, _gOviHwM19Info.lodcBypassRegFieldValue); 
	
		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		_gOviHwM19Info.tconBaseAddress = gpOviTconMem->base;
		if (!(_gOviHwM19Info.tconBaseAddress))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! M19 ODC will be disabled!\n");
			break;
		}

		OVI_TCON_M19_RdFL(tcon_base_address);
		OVI_TCON_M19_Wr(tcon_base_address, _gOviHwM19Info.tconBaseAddress);
		OVI_TCON_M19_WrFL(tcon_base_address);

		_gOviHwM19Info.tscicWritingFlag = FALSE;
		_gOviHwM19Info.tscicThread = NULL;
		_gOviHwM19Info.tscicU32Tbl = NULL;
		_gOviHwM19Info.tscicU8CtrlData = NULL;

		_gColTemp.bIsGet = 0;
		_gColTemp.r_gain = OVI_HW_M19_WB_DEFAULT_GAIN;
		_gColTemp.g_gain = OVI_HW_M19_WB_DEFAULT_GAIN;
		_gColTemp.b_gain = OVI_HW_M19_WB_DEFAULT_GAIN;
		_gColTemp.r_offset = 0;
		_gColTemp.g_offset = 0;
		_gColTemp.b_offset = 0;

	} while(0);

	return ret;
}

int OVI_HW_M19_Close(void)
{
	int ret = RET_OK;

	if(gOVI_TCON_M19.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_M19.shdw.addr);
		gOVI_TCON_M19.shdw.addr = NULL;
	}
	if(gOVI_TCON_LODC_M19.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_LODC_M19.shdw.addr);
		gOVI_TCON_LODC_M19.shdw.addr = NULL;
	}
	if(gOVI_TCON_CAD_M19.shdw.addr)
	{
		OS_Free((void *)gOVI_TCON_CAD_M19.shdw.addr);
		gOVI_TCON_CAD_M19.shdw.addr = NULL;
	}
	if(gOVI_OIF_M19.shdw.addr)
	{
		OS_Free((void *)gOVI_OIF_M19.shdw.addr);
		gOVI_OIF_M19.shdw.addr = NULL;
	}
	if(gOVI_WPR_M19.shdw.addr)
	{
		OS_Free((void *)gOVI_WPR_M19.shdw.addr);
		gOVI_WPR_M19.shdw.addr = NULL;
	}

	if (gOVI_TCON_M19.phys.addr)
	{
		iounmap((void *)gOVI_TCON_M19.phys.addr);
		gOVI_TCON_M19.phys.addr = NULL;
	}
	if (gOVI_TCON_LODC_M19.phys.addr)
	{
		iounmap((void *)gOVI_TCON_LODC_M19.phys.addr);
		gOVI_TCON_LODC_M19.phys.addr = NULL;
	}
	if (gOVI_TCON_CAD_M19.phys.addr)
	{
		iounmap((void *)gOVI_TCON_CAD_M19.phys.addr);
		gOVI_TCON_CAD_M19.phys.addr = NULL;
	}
	if (gOVI_OIF_M19.phys.addr)
	{
		iounmap((void *)gOVI_OIF_M19.phys.addr);
		gOVI_OIF_M19.phys.addr = NULL;
	}
	if (gOVI_WPR_M19.phys.addr)
	{
		iounmap((void *)gOVI_WPR_M19.phys.addr);
		gOVI_WPR_M19.phys.addr = NULL;
	}

	return ret;
}

int OVI_HW_M19_EarlyResume(void)
{
	int ret = RET_OK;

	do {
		CTOP_CTRL_M19Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
		if (!(CTOP_CTRL_M19Ax_Rd(CTOP_DPE, ctop_dpe_r42) & OVI_HW_M19_CH_POWER_REG_MASK)) // Instant boot
		{
			_OVI_M19_DispInit(&_gOviHwM19Info.dispOption);
		}
	} while(0);

	return ret;
}

int OVI_HW_M19_Resume(void)
{
	int ret = RET_OK;

	do {
		CTOP_CTRL_M19Ax_RdFL(CTOP_DPE, ctop_dpe_r42);
		if (!(CTOP_CTRL_M19Ax_Rd(CTOP_DPE, ctop_dpe_r42) & OVI_HW_M19_CH_POWER_REG_MASK)) // Instant boot
		{
			if (_gOviHwM19Info.tscicWritingFlag == TRUE)
			{
				if (_gOviHwM19Info.tscicThread != NULL)
				{
					kthread_stop(_gOviHwM19Info.tscicThread);
					_gOviHwM19Info.tscicThread = NULL;
				}

				_gOviHwM19Info.tscicWritingFlag = FALSE;
			}
		}

		_gOviHwM19Info.wbEn = FALSE;
		_gOviHwM19Info.wbBypassEn = FALSE;
		_gOviHwM19Info.dgaEn = FALSE;
		_gOviHwM19Info.dgaBypassEn = FALSE;
		_gOviHwM19Info.mleModeOff = FALSE;
		_gOviHwM19Info.odcBypassEn = FALSE;

		_gPrevRedGain = OVI_HW_M19_WB_DEFAULT_GAIN;
		_gPrevGreenGain = OVI_HW_M19_WB_DEFAULT_GAIN;
		_gPrevBlueGain = OVI_HW_M19_WB_DEFAULT_GAIN;

		_gPrevRedOffset = 0;
		_gPrevGreenOffset = 0;
		_gPrevBlueOffset = 0; 

		/* Get tcon base address for Frame OD */
		if (!gpOviTconMem)
		{
			OVI_ERROR("[OVI] TCON memory is not configured!\n");
			OVI_BREAK_WRONG((unsigned int)(uintptr_t)gpOviTconMem);
		}

		_gOviHwM19Info.tconBaseAddress = gpOviTconMem->base;
		if (!(_gOviHwM19Info.tconBaseAddress))
		{
			OVI_ERROR("[WARN][OVI] TCON memory is not configured! M19 ODC will be disabled!\n");
			break;
		}

		OVI_TCON_M19_RdFL(tcon_base_address);
		OVI_TCON_M19_Wr(tcon_base_address, _gOviHwM19Info.tconBaseAddress);
		OVI_TCON_M19_WrFL(tcon_base_address);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams)
{
	int ret = RET_OK;
	char opt[64];

	do {
		// check structure pointer
		if (pstParams == NULL)
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_PRINT("\n[OVI_HW_M19_SetDisplayOption] [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
			pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
			pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
			pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
			pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);

		memcpy((void *)&_gOviHwM19Info.dispOption, (void *)pstParams, sizeof(LX_OVI_DISPLAY_INFO_T));

		if (RET_OK==OS_ScanKernelCmdline("disp=%s", opt))
		{
			if (!strncmp(opt,"hdmi",4))
			{
				_gOviHwM19Info.dispOption.panelInterface = LX_OVI_PANEL_VX1;
				_gOviHwM19Info.dispOption.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			}
			else if (!strncmp(opt,"60epi",5))
			{
				_gOviHwM19Info.dispOption.panelInterface = LX_OVI_PANEL_EPI;
				_gOviHwM19Info.dispOption.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			}
			else if (!strncmp(opt,"120epi",6))
			{
				_gOviHwM19Info.dispOption.panelInterface = LX_OVI_PANEL_EPI;
				_gOviHwM19Info.dispOption.panelFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
			}
			else if (!strncmp(opt,"120boe",6))
			{
				_gOviHwM19Info.dispOption.panelInterface = LX_OVI_PANEL_CEDS;
				_gOviHwM19Info.dispOption.panelFramerate = LX_OVI_PANEL_FRAMERATE_120HZ;
			}
			else if (!strncmp(opt,"60boe",5))
			{
				_gOviHwM19Info.dispOption.panelInterface = LX_OVI_PANEL_CEDS;
				_gOviHwM19Info.dispOption.panelFramerate = LX_OVI_PANEL_FRAMERATE_60HZ;
			}
		}

		_OVI_M19_DispRegDataInit(&_gOviHwM19Info.dispOption);

	} while(0);

	return ret;
}

int OVI_HW_M19_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams)
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

		OVI_PRINT("\n[OVI_HW_M19_SetBypass] En[%d], Mask[0x%x]\n\r", pstParams->bEnable, pstParams->u32BlockMask);
		
		if (pstParams->u32BlockMask & LX_OVI_TCON_BOE_RGBW)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M19_RdFL(tcon_odc_opt2);
				OVI_TCON_M19_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_M19_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwM19Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_M19_RdFL(tcon_odc_opt2);
					OVI_TCON_M19_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwM19Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_M19_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwM19Info.odcBypassEn = pstParams->bEnable;
		}
		
		if (pstParams->u32BlockMask & LX_OVI_TCON_LGD_RGBW)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M19_RdFL(tcon_odc_opt2);
				OVI_TCON_M19_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_M19_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwM19Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_M19_RdFL(tcon_odc_opt2);
					OVI_TCON_M19_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwM19Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_M19_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwM19Info.odcBypassEn = pstParams->bEnable;
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_GAMMA)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M19_RdFL(tcon_control);
				OVI_TCON_M19_Wr01(tcon_control, dga_en, 0x0);
				OVI_TCON_M19_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_M19_RdFL(tcon_control);
				OVI_TCON_M19_Wr01(tcon_control, dga_en, _gOviHwM19Info.dgaEn ? 0x1 : 0x0);
				OVI_TCON_M19_WrFL(tcon_control);
			}
			_gOviHwM19Info.dgaBypassEn = pstParams->bEnable;
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_WB)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M19_RdFL(tcon_control);
				OVI_TCON_M19_Wr01(tcon_control, wb_en, 0x0);
				OVI_TCON_M19_WrFL(tcon_control);
			}
			else
			{
				OVI_TCON_M19_RdFL(tcon_control);
				OVI_TCON_M19_Wr01(tcon_control, wb_en, _gOviHwM19Info.wbEn ? 0x1 : 0x0);
				OVI_TCON_M19_WrFL(tcon_control);
			}
			_gOviHwM19Info.wbBypassEn = pstParams->bEnable;
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_LODC)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M19_RdFL(tcon_btc_config);
				OVI_TCON_M19_Wr01(tcon_btc_config, lodc_bypass, 0x1);
				OVI_TCON_M19_WrFL(tcon_btc_config);
			}
			else
			{
				if (!_gOviHwM19Info.lodcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_M19_RdFL(tcon_btc_config);
					OVI_TCON_M19_Wr01(tcon_btc_config, lodc_bypass, 0x0);
					OVI_TCON_M19_WrFL(tcon_btc_config);
				}
			}
		}

		if (pstParams->u32BlockMask & LX_OVI_TCON_ODC)
		{
			if (pstParams->bEnable)
			{
				OVI_TCON_M19_RdFL(tcon_odc_opt2);
				OVI_TCON_M19_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
				OVI_TCON_M19_WrFL(tcon_odc_opt2);
			}
			else
			{
				if (!_gOviHwM19Info.odcBypassRegFieldValue) // prevent Vx1(or LVDS) unlock
				{
					OVI_TCON_M19_RdFL(tcon_odc_opt2);
					OVI_TCON_M19_Wr01(tcon_odc_opt2, odc_bypass, _gOviHwM19Info.mleModeOff ? 0x1 : 0x0);
					OVI_TCON_M19_WrFL(tcon_odc_opt2);
				}
			}
			_gOviHwM19Info.odcBypassEn = pstParams->bEnable;
		}
	} while(0);

	return ret;
}

int OVI_HW_M19_SetCombination(UINT32 param)
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
			for(i=0; i<_gOVIOutputModes_M19.number_of_modes;i++)
			{
				printk("  Index[%d] : %s", i,_gOVIOutputModes_M19.pOVIOutputModes[i].index);
			}
			ret = RET_OK;
			break;
		}
		else if(param >= 10000)
		{
			param = param - 10000;
			printk("\n[OVI] Compare register values regarding to register-set index[%d]", param);

			if(param > _gOVIOutputModes_M19.number_of_modes) {
				OVI_ERROR("Unknown OVI index. Index was [%d]", param);
				break;
			}

			regs  = _gOVIOutputModes_M19.pOVIOutputModes[param].regs;
			count = _gOVIOutputModes_M19.pOVIOutputModes[param].count;
			index = _gOVIOutputModes_M19.pOVIOutputModes[param].index;

			printk("\n[OVI] Register Index[%d] => %s",param, (char *)index);
			for(i=0; i<count; i++){
				if (regs[i].addr == OVI_HW_M19_REG_PARAM_OP_WAIT) continue;

				if (regs[i].addr == OVI_HW_M19_REG_PARAM_OP_CHECK)
				{
					_OVI_M19_IgnoreRegSet(regs[i].value, &ignore);
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
		else if(param > _gOVIOutputModes_M19.number_of_modes) {
			OVI_ERROR("\nUnknown OVI mode. Index was [%d]\n", param);
			break;
		}

		/* Step 2. Set mode */
		regs  = _gOVIOutputModes_M19.pOVIOutputModes[param].regs;
		count = _gOVIOutputModes_M19.pOVIOutputModes[param].count;
		index = _gOVIOutputModes_M19.pOVIOutputModes[param].index;

		printk("\n[OVI] Setting to registers to register-set-index => %s", (char *)index);
		for(i=0; i<count; i++){
			if (regs[i].addr == OVI_HW_M19_REG_PARAM_OP_WAIT)
			{
				printk("\n[%03d] Delay... %dms", i, regs[i].value/1000);
				OS_UsecDelay(regs[i].value);
			}

			if (regs[i].addr == OVI_HW_M19_REG_PARAM_OP_CHECK)
			{
				_OVI_M19_IgnoreRegSet(regs[i].value, &ignore);
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

int OVI_HW_M19_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams)
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

		if (_gOviHwM19Info.spreadSpectrumRegValue1 & 0x4) break; // default DSS OFF

		if(pstParams->bEnable)
		{
			CTOP_CTRL_M19Ax_Wr(CTOP_DPE, ctop_dpe_r33, _gOviHwM19Info.spreadSpectrumRegValue1 | 0x4);
			CTOP_CTRL_M19Ax_Wr(CTOP_DPE, ctop_dpe_r34, _gOviHwM19Info.spreadSpectrumRegValue2);
			CTOP_CTRL_M19Ax_RdFL(CTOP_DPE, ctop_dpe_r35);
			CTOP_CTRL_M19Ax_Wr(CTOP_DPE, ctop_dpe_r35, CTOP_CTRL_M19Ax_Rd(CTOP_DPE, ctop_dpe_r35) | 0x01400000);
			CTOP_CTRL_M19Ax_WrFL(CTOP_DPE, ctop_dpe_r33);
			CTOP_CTRL_M19Ax_WrFL(CTOP_DPE, ctop_dpe_r34);
			CTOP_CTRL_M19Ax_WrFL(CTOP_DPE, ctop_dpe_r35);

			CTOP_CTRL_M19Ax_Wr(CTOP_DPE, ctop_dpe_r33, _gOviHwM19Info.spreadSpectrumRegValue1);
			CTOP_CTRL_M19Ax_WrFL(CTOP_DPE, ctop_dpe_r33);
		}
		else
		{
			CTOP_CTRL_M19Ax_Wr(CTOP_DPE, ctop_dpe_r33, _gOviHwM19Info.spreadSpectrumRegValue1 | 0x4);
			CTOP_CTRL_M19Ax_WrFL(CTOP_DPE, ctop_dpe_r33);
		}
	} while(0);

	return ret;
}

int OVI_HW_M19_SetMcuCommand(LX_OVI_TCON_MCU_CMD_T *pstParams)
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

			OVI_TCON_M19_RdFL(tcon_control);
			OVI_TCON_M19_Wr01(tcon_control, hm_mcu_int_in, 0x0);
			OVI_TCON_M19_WrFL(tcon_control);
		}
	} while(0);
		
	return ret;
}

int OVI_HW_M19_UpdateFirmware(LX_OVI_TCON_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	UINT32 i;
	volatile UINT32 *fwRegAddr = NULL;

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
			if (pstParams->sizeNum != OVI_HW_M19_BOE_MPLUS_LUT_SIZENUM) 
			{
				OVI_ERROR("[OVI] Invalid BOE M+ LUT size! \n");
				ret = RET_ERROR;
				break;
			}

			fwRegAddr = (volatile UINT32 *)ioremap(OVI_SIW_RGBW_START_REG_M19A0_BASE, sizeof(UINT32)*(pstParams->sizeNum));
			if(fwRegAddr == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}

			for (i=0; i<pstParams->sizeNum; i++)
			{
				if (pstParams->read)
				{
					put_user(fwRegAddr[i], &(((UINT32 *)pstParams->pData)[i]));
				}
				else
				{
					get_user(fwRegAddr[i], &(((UINT32 *)pstParams->pData)[i]));
				}
			}

		}
		else if (pstParams->type == LX_OVI_TCON_FW_LGD)
		{
			CHAR buff;
			
			if (pstParams->sizeNum != OVI_HW_M19_LGD_MPLUS_LUT_SIZENUM) 
			{
				OVI_ERROR("[OVI] Invalid LGD M+ LUT size! \n");
				ret = RET_ERROR;
				break;
			}
			
			fwRegAddr = (volatile UINT32 *)ioremap(OVI_WPR_MPLUS_START_REG_M19A0_BASE, sizeof(UINT32)*(pstParams->sizeNum));
			if(fwRegAddr == NULL)
			{
				OVI_ERROR("[OVI] Error in ioremap! \n");
				ret = RET_ERROR;
				break;
			}

			for (i=0; i<pstParams->sizeNum; i++)
			{
				if (pstParams->read)
				{
					buff = readb_relaxed(&fwRegAddr[i]);
					put_user(buff, &(((CHAR *)pstParams->pData)[i]));
				}
				else
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

int OVI_HW_M19_GetFirmwareVersion(LX_OVI_TCON_FW_VER_T *pstParams)
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
			
			OVI_TCON_M19_RdFL(tcon_control);
			OVI_TCON_M19_Wr01(tcon_control, hm_mcu_int_in, 0x1);
			OVI_TCON_M19_WrFL(tcon_control);

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


int OVI_HW_M19_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
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
				if((odLutSizeNum != OVI_HW_M19_INPUT_OD_SIZENUM && odLutSizeNum != (4*OVI_HW_M19_INPUT_OD_SIZENUM)) 
					|| pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE + offsetof(OVI_TCON_REG_M19A0_T, tcon_odc_start_2d), 
													sizeof(UINT32)*OVI_HW_M19_INPUT_OD_SIZENUM);
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
				if(odLutSizeNum != OVI_HW_M19_INPUT_LOD_SIZENUM || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_LODC_REG_M19A0_BASE + offsetof(OVI_TCON_LODC_REG_M19A0_T, tcon_lodc_start), 
													sizeof(UINT32)*OVI_HW_M19_INPUT_LOD_SIZENUM);
				if(regAddr1 == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! \n");
					ret = RET_ERROR;
					break;
				}
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_ON)
			{
				OVI_TCON_M19_RdFL(tcon_control);
				OVI_TCON_M19_Wr01(tcon_control, odc_en, 0x1);
				OVI_TCON_M19_WrFL(tcon_control);

				OVI_TCON_M19_RdFL(tcon_sts);
				OVI_TCON_M19_Wr01(tcon_sts, pix2_lock, 0x1);
				OVI_TCON_M19_WrFL(tcon_sts);
				break;
			}
			else if (pstParams->eMode == LX_OVI_TCON_OD_BW_DEBUG_OFF)
			{
				OVI_TCON_M19_RdFL(tcon_control);
				OVI_TCON_M19_Wr01(tcon_control, odc_en, 0x0);
				OVI_TCON_M19_WrFL(tcon_control);

				OVI_TCON_M19_RdFL(tcon_sts);
				OVI_TCON_M19_Wr01(tcon_sts, pix2_lock, 0x0);
				OVI_TCON_M19_WrFL(tcon_sts);
				break;
			}
			else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
			{
				// check input table size
				if(odLutSizeNum != OVI_HW_M19_INPUT_POD2_SIZENUM || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Input OD LUT size is not correct! or Data is NULL!\n");
					ret = RET_ERROR;
					break;
				}

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_M19A0_BASE + offsetof(OVI_TCON_CAD_REG_M19A0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_M19_INPUT_POD2_SIZENUM);
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
				UINT32 regField;
				UINT32 regField2;
				UINT32 odLutDataOffsetInc = 0;

				OVI_WPR_M19_RdFL(wpr_reg_main);
				regField = OVI_WPR_M19_Rd(wpr_reg_main);
				regField = regField & 0x3; // check wpr_on,lgd_siw_mux
				OVI_TCON_M19_RdFL(tcon_control);
				OVI_TCON_M19_Rd01(tcon_control, hm_rgbw_en, regField2);
				regField = regField | regField2;

				OVI_TCON_M19_RdFL(odc_lut_subpix_sel);
				OVI_TCON_M19_Wr01(odc_lut_subpix_sel, lut_rgbw_en, regField == 0 ? 0x0 : 0x1);
				OVI_TCON_M19_WrFL(odc_lut_subpix_sel);

				OVI_TCON_M19_RdFL(odc_lut_subpix_sel);
				OVI_TCON_M19_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x0);
				OVI_TCON_M19_WrFL(odc_lut_subpix_sel);

				if (odLutSizeNum == (4*OVI_HW_M19_INPUT_OD_SIZENUM))
				{
					odLutDataOffsetInc = OVI_HW_M19_INPUT_OD_SIZENUM;
				}

				for(i=0; i<OVI_HW_M19_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i], &regAddr1[i]);
				}

				OVI_TCON_M19_RdFL(odc_lut_subpix_sel);
				OVI_TCON_M19_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x1);
				OVI_TCON_M19_WrFL(odc_lut_subpix_sel);
				for(i=0; i<OVI_HW_M19_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i+(1*odLutDataOffsetInc)], &regAddr1[i]);
				}

				OVI_TCON_M19_RdFL(odc_lut_subpix_sel);
				OVI_TCON_M19_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x2);
				OVI_TCON_M19_WrFL(odc_lut_subpix_sel);
				for(i=0; i<OVI_HW_M19_INPUT_OD_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i+(2*odLutDataOffsetInc)], &regAddr1[i]);
				}

				if (regField != 0)
				{
					OVI_TCON_M19_RdFL(odc_lut_subpix_sel);
					OVI_TCON_M19_Wr01(odc_lut_subpix_sel, lut_subpix_sel, 0x3);
					OVI_TCON_M19_WrFL(odc_lut_subpix_sel);
					for(i=0; i<OVI_HW_M19_INPUT_OD_SIZENUM; i++)
					{
						writel_relaxed(u8odLutData[i+(3*odLutDataOffsetInc)], &regAddr1[i]);
					}
				}
			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_POD)
			{
				for(i=0; i<OVI_HW_M19_INPUT_POD2_SIZENUM; i++)
				{
					writel_relaxed(u8odLutData[i], &regAddr1[i]);
				}
			}
			else //if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				for(i=0; i<OVI_HW_M19_INPUT_LOD_SIZENUM; i++)
				{
					get_user(regAddr1[i], &(((UINT32 *)pstParams->odLut.pData)[i]));
				}
			}

			if(pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				OVI_TCON_M19_RdFL(odc_lut_upload);
				OVI_TCON_M19_Wr01(odc_lut_upload, odc_upload, 0x0);
				OVI_TCON_M19_WrFL(odc_lut_upload);
				OVI_TCON_M19_RdFL(odc_lut_upload);
				OVI_TCON_M19_Wr01(odc_lut_upload, odc_upload, 0x1);
				OVI_TCON_M19_WrFL(odc_lut_upload);
			}
			else if (pstParams->eMode == LX_OVI_TCON_LINEOD_PCID)
			{
				OVI_TCON_CAD_M19_RdFL(tcon_cad_reg_main);
				OVI_TCON_CAD_M19_Wr01(tcon_cad_reg_main, cad_on, 0x0);
				OVI_TCON_CAD_M19_WrFL(tcon_cad_reg_main);

				OVI_TCON_M19_RdFL(tcon_odc_lut1_opt);
				OVI_TCON_M19_Wr01(tcon_odc_lut1_opt, lut1_add_opt, 0x0);
				OVI_TCON_M19_Wr01(tcon_odc_lut1_opt, lut1_full_opt, 0x0);
				OVI_TCON_M19_Wr01(tcon_odc_lut1_opt, lut1_zero_opt, 0x0);
				OVI_TCON_M19_Wr01(tcon_odc_lut1_opt, lut1_same_opt, 0x0);
				OVI_TCON_M19_WrFL(tcon_odc_lut1_opt);

				OVI_TCON_LODC_M19_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_M19_Wr01(lodc_lut_upload, lodc_upload, 0x0);
				OVI_TCON_LODC_M19_WrFL(lodc_lut_upload);
				OVI_TCON_LODC_M19_RdFL(lodc_lut_upload);
				OVI_TCON_LODC_M19_Wr01(lodc_lut_upload, lodc_upload, 0x1);
				OVI_TCON_LODC_M19_WrFL(lodc_lut_upload);

				OVI_TCON_M19_RdFL(tcon_odc_opt1);
				OVI_TCON_M19_Wr01(tcon_odc_opt1, lodc_en_2d, 0x1);
				OVI_TCON_M19_Wr01(tcon_odc_opt1, lodc_en_3d, 0x0);
				OVI_TCON_M19_Wr01(tcon_odc_opt1, pcid_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_odc_opt1, pcid20_en, 0x1);
				OVI_TCON_M19_WrFL(tcon_odc_opt1);
			}
			else
			{
				UINT32 regField;

				CTOP_CTRL_M19Ax_RdFL(DPE_SYN, crg_dpe00);
				CTOP_CTRL_M19Ax_Rd01(DPE_SYN, crg_dpe00, tcon_pod_clk_gate_en, regField);

				OVI_TCON_M19_RdFL(tcon_btc_config);
				if (regField) // POD clock gating enable
				{
					// Prevention for black screen when using CEDS board
					OVI_TCON_M19_Wr01(tcon_btc_config, lodc_mem_sel, 0x1);
				}
				else
				{
					OVI_TCON_M19_Wr01(tcon_btc_config, lodc_mem_sel, 0x0);
				}
				OVI_TCON_M19_WrFL(tcon_btc_config);

				OVI_TCON_CAD_M19_RdFL(tcon_cad_reg_main);
				OVI_TCON_CAD_M19_Wr01(tcon_cad_reg_main, cad_on, 0x1);
				OVI_TCON_CAD_M19_WrFL(tcon_cad_reg_main);
			}
		}
		else
		{
			if (pstParams->eMode == LX_OVI_TCON_FRAMEOD)
			{
				UINT8 buff;

				// select address
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE + offsetof(OVI_TCON_REG_M19A0_T, tcon_odc_start_2d), 
													sizeof(UINT32)*OVI_HW_M19_INPUT_OD_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = OVI_HW_M19_INPUT_OD_SIZENUM;

				for (i = 0; i < OVI_HW_M19_INPUT_OD_SIZENUM; i++)
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
				regAddr2 = (volatile UINT8 *)ioremap(OVI_TCON_LODC_REG_M19A0_BASE + offsetof(OVI_TCON_LODC_REG_M19A0_T, tcon_lodc_start), 
													sizeof(UINT32)*OVI_HW_M19_INPUT_LOD_SIZENUM);
				if(regAddr2 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = sizeof(UINT32)*OVI_HW_M19_INPUT_LOD_SIZENUM;

				for (i = 0; i < sizeof(UINT32)*OVI_HW_M19_INPUT_LOD_SIZENUM; i++)
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
				regAddr1 = (volatile UINT32 *)ioremap(OVI_TCON_CAD_REG_M19A0_BASE + offsetof(OVI_TCON_CAD_REG_M19A0_T, tcon_cad_reg_start), 
													sizeof(UINT32)*OVI_HW_M19_INPUT_POD2_SIZENUM);
				if(regAddr1 == NULL || pstParams->odLut.pData == NULL)
				{
					OVI_ERROR("[OVI] Error in ioremap! or Null pointer! \n");
					ret = RET_ERROR;
					break;
				}

				pstParams->odLut.sizeNum = OVI_HW_M19_INPUT_POD2_SIZENUM;

				for (i = 0; i < OVI_HW_M19_INPUT_POD2_SIZENUM; i++)
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

int OVI_HW_M19_SetFrameOdcEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	
	do {
		// check TCON base address
		if (bParam && !(_gOviHwM19Info.tconBaseAddress))
		{
			OVI_ERROR("[OVI] TCON base address is Null!\n");
			ret = RET_ERROR;
			break;
		}
		
		OVI_TCON_M19_RdFL(tcon_control);
		if(bParam)
			OVI_TCON_M19_Wr01(tcon_control, odc_en, 0x1);
		else
			OVI_TCON_M19_Wr01(tcon_control, odc_en, 0x0);
		OVI_TCON_M19_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_M19_SetColorTempEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		if (!_gOviHwM19Info.wbBypassEn)
		{
			OVI_TCON_M19_RdFL(tcon_control);
			if(bParam)
				OVI_TCON_M19_Wr01(tcon_control, wb_en, 0x1);
			else
				OVI_TCON_M19_Wr01(tcon_control, wb_en, 0x0);
			OVI_TCON_M19_WrFL(tcon_control);
		}
		_gOviHwM19Info.wbEn = bParam;
	} while (0);

	return ret;
}

int OVI_HW_M19_SetGammaEnable(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		DPE_LED_M19_RdFL(led_dpg_en);
		if(bParam)
			DPE_LED_M19_Wr01(led_dpg_en, dpg_en, 0x1);
		else
			DPE_LED_M19_Wr01(led_dpg_en, dpg_en, 0x0);
		DPE_LED_M19_WrFL(led_dpg_en);
	} while (0);

	return ret;
}

int OVI_HW_M19_SetDitherEnable(BOOLEAN bParam)
{
	int ret = RET_OK;
	
	do {
		OVI_TCON_M19_RdFL(tcon_control);
		if(bParam)
		{
			OVI_TCON_M19_Wr01(tcon_control, pre_dither_en, 0x1);
		}
		else
		{
			OVI_TCON_M19_Wr01(tcon_control, pre_dither_en, 0x0);
		}
		OVI_TCON_M19_WrFL(tcon_control);
	} while (0);

	return ret;
}

int OVI_HW_M19_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams)
{
	int ret = RET_OK;

	do {
		/* Do Nothing */
	} while(0);

	return ret;
}

int OVI_HW_M19_SetDitherMode(LX_OVI_TCON_DITHER_T enParam)
{
	int ret = RET_OK;
	
	do {
		//Dither Enable
		OVI_TCON_M19_RdFL(tcon_control);
		OVI_TCON_M19_Wr01(tcon_control, pre_dither_en, 0x1);
		OVI_TCON_M19_WrFL(tcon_control);
		
		OVI_TCON_M19_RdFL(tcon_dither_carry);
		switch(enParam)
		{
			case LX_OVI_TCON_DITHER_TRUNC:
				OVI_TCON_M19_Wr01(tcon_dither_carry, pre_dither_sel, 0x0);
				break;
			case LX_OVI_TCON_DITHER_ROUND:
				OVI_TCON_M19_Wr01(tcon_dither_carry, pre_dither_sel, 0x1);
				break;
			case LX_OVI_TCON_DITHER_RANDOM:
			default :
				OVI_TCON_M19_Wr01(tcon_dither_carry, pre_dither_sel, 0x2);
				break;
		}
		OVI_TCON_M19_WrFL(tcon_dither_carry);
	} while(0);

	return ret;
}

static UINT32 _OVI_M19_GetGain(UINT32 gain)
{
	UINT32 ret_gain;
	UINT32 temp;

	temp = 10000 + (gain - 192) * OVI_HW_M19_WB_GAIN_STEP;
	ret_gain = (temp * OVI_HW_M19_WB_DEFAULT_GAIN) / 10000;

	return ret_gain;
}

static SINT16 _OVI_M19_GetOffset(UINT32 offset)
{
	SINT16 ret_offset;

	ret_offset = ((SINT32)offset - 64) * OVI_HW_M19_WB_OFFSET_STEP;
	return ret_offset;
}

int OVI_HW_M19_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams)
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
			// W/B Enable
			if (!_gOviHwM19Info.wbBypassEn)
			{
				OVI_TCON_M19_RdFL(tcon_control);
				OVI_TCON_M19_Wr01(tcon_control, wb_en, 0x1);
				OVI_TCON_M19_WrFL(tcon_control);
			}
			_gOviHwM19Info.wbEn = TRUE;
			
			r_gain = _OVI_M19_GetGain(pstParams->r_gain);
			g_gain = _OVI_M19_GetGain(pstParams->g_gain);
			b_gain = _OVI_M19_GetGain(pstParams->b_gain);

			rOffset = _OVI_M19_GetOffset(pstParams->r_offset);
			gOffset = _OVI_M19_GetOffset(pstParams->g_offset);
			bOffset = _OVI_M19_GetOffset(pstParams->b_offset);

			_gColTemp = *pstParams;

			if((_gPrevRedGain == r_gain) && (_gPrevGreenGain == g_gain) && (_gPrevBlueGain == b_gain)
				&& (_gPrevRedOffset == rOffset) && (_gPrevGreenOffset == gOffset) && (_gPrevBlueOffset == bOffset))
			{
				return RET_OK;
			}

			// Set red gain
			OVI_TCON_M19_RdFL(tcon_wb_rgain);
			OVI_TCON_M19_Wr(tcon_wb_rgain, r_gain);
			OVI_TCON_M19_WrFL(tcon_wb_rgain);

			// Set red offset
			OVI_TCON_M19_RdFL(tcon_wb_roffset);
			OVI_TCON_M19_Wr(tcon_wb_roffset, rOffset);
			OVI_TCON_M19_WrFL(tcon_wb_roffset);

			// Set green gain
			OVI_TCON_M19_RdFL(tcon_wb_ggain);
			OVI_TCON_M19_Wr(tcon_wb_ggain, g_gain);
			OVI_TCON_M19_WrFL(tcon_wb_ggain);

			// Set green offset
			OVI_TCON_M19_RdFL(tcon_wb_goffset);
			OVI_TCON_M19_Wr(tcon_wb_goffset, gOffset);
			OVI_TCON_M19_WrFL(tcon_wb_goffset);

			// Set blue gain
			OVI_TCON_M19_RdFL(tcon_wb_bgain);
			OVI_TCON_M19_Wr(tcon_wb_bgain, b_gain);
			OVI_TCON_M19_WrFL(tcon_wb_bgain);

			// Set blue offset
			OVI_TCON_M19_RdFL(tcon_wb_boffset);
			OVI_TCON_M19_Wr(tcon_wb_boffset, bOffset);
			OVI_TCON_M19_WrFL(tcon_wb_boffset);

			_gPrevRedGain = r_gain;
			_gPrevGreenGain = g_gain;
			_gPrevBlueGain = b_gain;
			_gPrevRedOffset = rOffset;
			_gPrevGreenOffset = gOffset;
			_gPrevBlueOffset = bOffset;
		}
		else
		{
			*pstParams = _gColTemp;
		}

	} while(0);

	return ret;
}

int OVI_HW_M19_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams)
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

		if (!pstParams->bIsGet)
		{
			if((pstParams->rGammaLut.sizeNum != OVI_HW_M19_GAMMA_TABLE_SIZENUM)
			|| (pstParams->gGammaLut.sizeNum != OVI_HW_M19_GAMMA_TABLE_SIZENUM)
			|| (pstParams->bGammaLut.sizeNum != OVI_HW_M19_GAMMA_TABLE_SIZENUM))
			{
				OVI_ERROR("[OVI] Gamma table size is not correct! \n");
				ret = RET_ERROR;
				break;
			}

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			ret = copy_from_user(rGammaTable, (void __user *)pstParams->rGammaLut.pData, OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user(gGammaTable, (void __user *)pstParams->gGammaLut.pData, OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_from_user(bGammaTable, (void __user *)pstParams->bGammaLut.pData, OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying from user! \n");
				ret = RET_ERROR;
				break;
			}

			DPE_LED_M19_RdFL(led_dpg_lut_wdata);

			/* Setting Red Gamma Table */
			for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_we, 0x4);
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_wdata, rGammaTable[i] & 0x7FFF);
				DPE_LED_M19_WrFL(led_dpg_lut_wdata);
			}
			/* Setting Green Gamma Table */
			for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_we, 0x2);
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_wdata, gGammaTable[i] & 0x7FFF);
				DPE_LED_M19_WrFL(led_dpg_lut_wdata);
			}
			/* Setting Blue Gamma Table */
			for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_we, 0x1);
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_waddr, i);
				DPE_LED_M19_Wr01(led_dpg_lut_wdata, dpg_wdata, bGammaTable[i] & 0x7FFF);
				DPE_LED_M19_WrFL(led_dpg_lut_wdata);
			}

			DPE_LED_M19_RdFL(led_dpg_lut_wr_done);
			DPE_LED_M19_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_M19_WrFL(led_dpg_lut_wr_done);

			// Gamma Enable
			DPE_LED_M19_RdFL(led_dpg_en);
			DPE_LED_M19_Wr01(led_dpg_en, dpg_en, 0x1);
			DPE_LED_M19_WrFL(led_dpg_en);
		}
		else
		{

			rGammaTable = (UINT32 *)vmalloc(OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			gGammaTable = (UINT32 *)vmalloc(OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			bGammaTable = (UINT32 *)vmalloc(OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(rGammaTable == NULL || gGammaTable == NULL || bGammaTable == NULL)
			{
				OVI_ERROR("[OVI] memory allocate failed! \n");
				ret = RET_ERROR;
				break;
			}

			DPE_LED_M19_RdFL(led_dpg_lut_wr_done);
			DPE_LED_M19_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_M19_WrFL(led_dpg_lut_wr_done);

			OS_UsecDelay(25000);

			/* Setting Red Gamma Table */
			for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M19_RdFL(led_dpg_lut_rdata);
				DPE_LED_M19_Wr01(led_dpg_lut_rdata, dpg_re, 0x4);
				DPE_LED_M19_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_M19_WrFL(led_dpg_lut_rdata);
				DPE_LED_M19_RdFL(led_dpg_lut_rdata);
				DPE_LED_M19_Rd01(led_dpg_lut_rdata, dpg_rdata, rGammaTable[i]);
			}
			/* Setting Green Gamma Table */
			for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M19_RdFL(led_dpg_lut_rdata);
				DPE_LED_M19_Wr01(led_dpg_lut_rdata, dpg_re, 0x2);
				DPE_LED_M19_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_M19_WrFL(led_dpg_lut_rdata);
				DPE_LED_M19_RdFL(led_dpg_lut_rdata);
				DPE_LED_M19_Rd01(led_dpg_lut_rdata, dpg_rdata, gGammaTable[i]);
			}
			/* Setting Blue Gamma Table */
			for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
			{
				DPE_LED_M19_RdFL(led_dpg_lut_rdata);
				DPE_LED_M19_Wr01(led_dpg_lut_rdata, dpg_re, 0x1);
				DPE_LED_M19_Wr01(led_dpg_lut_rdata, dpg_raddr, i);
				DPE_LED_M19_WrFL(led_dpg_lut_rdata);
				DPE_LED_M19_RdFL(led_dpg_lut_rdata);
				DPE_LED_M19_Rd01(led_dpg_lut_rdata, dpg_rdata, bGammaTable[i]);
			}

			DPE_LED_M19_RdFL(led_dpg_lut_wr_done);
			DPE_LED_M19_Wr01(led_dpg_lut_wr_done, dpg_lut_wr_done, 0x1);
			DPE_LED_M19_WrFL(led_dpg_lut_wr_done);

			pstParams->rGammaLut.sizeNum = OVI_HW_M19_GAMMA_TABLE_SIZENUM;
			pstParams->gGammaLut.sizeNum = OVI_HW_M19_GAMMA_TABLE_SIZENUM;
			pstParams->bGammaLut.sizeNum = OVI_HW_M19_GAMMA_TABLE_SIZENUM;

			ret = copy_to_user(pstParams->rGammaLut.pData, (void __user *)rGammaTable, OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->gGammaLut.pData, (void __user *)gGammaTable, OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			ret |= copy_to_user(pstParams->bGammaLut.pData, (void __user *)bGammaTable, OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
			if(ret)
			{
				OVI_ERROR("[OVI] Error in copying to user! \n");
				ret = RET_ERROR;
				break;
			}

		}
	} while(0);

	if(rGammaTable != NULL)
		vfree(rGammaTable);
	if(gGammaTable != NULL)
		vfree(gGammaTable);
	if(bGammaTable != NULL)
		vfree(bGammaTable);

	return ret;
}

int OVI_HW_M19_SetGammaRGBW(LX_OVI_TCON_GAMMA_RGBW_T *pstParams)
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

		if((pstParams->rGammaLut.sizeNum != OVI_HW_M19_GAMMA_TABLE_SIZENUM)
		|| (pstParams->gGammaLut.sizeNum != OVI_HW_M19_GAMMA_TABLE_SIZENUM)
		|| (pstParams->bGammaLut.sizeNum != OVI_HW_M19_GAMMA_TABLE_SIZENUM)
		|| (pstParams->wGammaLut.sizeNum != OVI_HW_M19_GAMMA_TABLE_SIZENUM))
		{
			OVI_ERROR("[OVI] Gamma table size is not correct! \n");
			ret = RET_ERROR;
			break;
		}

		gammaTable = (UINT32 *)vmalloc(OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(gammaTable == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		/* Setting Red Gamma Table */
		ret = copy_from_user(gammaTable, (void __user *)pstParams->rGammaLut.pData, 
							OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}
		
		reg_start = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE+offsetof(OVI_TCON_REG_M19A0_T, tcon_dga_low_rs), 
											OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_start == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
		{
			reg_start[i] = gammaTable[i] << 3;
		}

		iounmap((void *)reg_start); reg_start = NULL;
		
		/* Setting Green Gamma Table */
		ret = copy_from_user(gammaTable, (void __user *)pstParams->gGammaLut.pData, 
							OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}
		
		reg_start = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE+offsetof(OVI_TCON_REG_M19A0_T, tcon_dga_low_gs), 
											OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_start == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
		{
			reg_start[i] = gammaTable[i] << 3;
		}

		iounmap((void *)reg_start); reg_start = NULL;

		/* Setting Blue Gamma Table */
		ret = copy_from_user(gammaTable, (void __user *)pstParams->bGammaLut.pData, 
							OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		reg_start = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE+offsetof(OVI_TCON_REG_M19A0_T, tcon_dga_low_bs), 
											OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_start == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
		{
			reg_start[i] = gammaTable[i] << 3;
		}

		iounmap((void *)reg_start); reg_start = NULL;

		/* Setting White Gamma Table */
		ret = copy_from_user(gammaTable, (void __user *)pstParams->wGammaLut.pData, 
							OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			break;
		}

		reg_start = (volatile UINT32 *)ioremap(OVI_TCON_REG_M19A0_BASE+offsetof(OVI_TCON_REG_M19A0_T, tcon_dga_low_ws), 
											OVI_HW_M19_GAMMA_TABLE_SIZENUM*sizeof(UINT32));
		if(reg_start == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			ret = RET_ERROR;
			break;
		}

		for(i=0; i<OVI_HW_M19_GAMMA_TABLE_SIZENUM; i++)
		{
			reg_start[i] = gammaTable[i] << 3;
		}

		iounmap((void *)reg_start); reg_start = NULL;

		// gamma table upload
		OVI_TCON_M19_RdFL(tcon_dga_mode);
		OVI_TCON_M19_Wr01(tcon_dga_mode, dga_up_mode, 0x0);	// dga_up_mode : 0 -> sync update
		OVI_TCON_M19_WrFL(tcon_dga_mode);
		OVI_TCON_M19_RdFL(tcon_dga_mode);
		OVI_TCON_M19_Wr01(tcon_dga_mode, dga_upload, 0x1);	// dga_upload : 1 -> upload bit cleared by HW
		OVI_TCON_M19_WrFL(tcon_dga_mode);

		// Gamma Enable
		if (!_gOviHwM19Info.dgaBypassEn)
		{
			OVI_TCON_M19_RdFL(tcon_control);
			OVI_TCON_M19_Wr01(tcon_control, dga_en, 0x1);
			OVI_TCON_M19_WrFL(tcon_control);
		}
		_gOviHwM19Info.dgaEn = TRUE;
	} while(0);

	if (gammaTable != NULL)
		vfree(gammaTable);

	if (reg_start != NULL)
		iounmap((void *)reg_start);
	
	return ret;
}

int OVI_HW_M19_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams)
{
	int ret = RET_OK;
	UINT32 u32odcAddr=0;
	volatile UINT32 *pMappedAddr = NULL;

	do {
		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_FRAMEOD:
				u32odcAddr = OVI_TCON_REG_M19A0_BASE + offsetof(OVI_TCON_REG_M19A0_T, tcon_odc_start_2d);
				break;
			case LX_OVI_TCON_LINEOD_PCID:
				u32odcAddr = OVI_TCON_LODC_REG_M19A0_BASE + offsetof(OVI_TCON_LODC_REG_M19A0_T, tcon_lodc_start);
				break;
			default:
				break;
		}

		pstParams->odLut.sizeNum = OVI_HW_M19_INPUT_OD_SIZENUM;

		pMappedAddr = (volatile UINT32 *)ioremap(u32odcAddr, sizeof(UINT32)*OVI_HW_M19_INPUT_OD_SIZENUM);
		if(pMappedAddr == NULL)
		{
			OVI_ERROR("[OVI] Error in ioremap! \n");
			break;
		}

		ret = copy_to_user((void __user *)pstParams->odLut.pData, (void*)pMappedAddr, sizeof(UINT32)*OVI_HW_M19_INPUT_OD_SIZENUM);
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

int OVI_HW_M19_SetMleMode(LX_OVI_TCON_MLE_MODE_T enParam)
{
	int ret = RET_OK;

	do {
		// W/A for M19A0 MLE mode OFF
		OVI_TCON_M19_RdFL(tcon_odc_opt2);
		if (enParam == LX_OVI_TCON_MLE_MODE_OFF)
		{
			OVI_TCON_M19_Wr01(tcon_odc_opt2, odc_bypass, 0x1);
		}
		else
		{
			if (!_gOviHwM19Info.odcBypassEn)
			{
				OVI_TCON_M19_Wr01(tcon_odc_opt2, odc_bypass, 0x0);
			}
		}
		OVI_TCON_M19_WrFL(tcon_odc_opt2);
		_gOviHwM19Info.mleModeOff = (enParam == LX_OVI_TCON_MLE_MODE_OFF) ? TRUE : FALSE;

		switch(enParam)
		{
			case LX_OVI_TCON_HIGH_LUM1_MSE_ON:
				OVI_REG_WR(0xC907AFFC, 0x00101101);
				break;
			case LX_OVI_TCON_HIGH_LUM1_MSE_OFF:
				OVI_REG_WR(0xC907AFFC, 0x00101001);
				break;
			case LX_OVI_TCON_HIGH_LUM2:
				OVI_REG_WR(0xC907AFFC, 0x00102001);
				break;
			case LX_OVI_TCON_LOW_POWER1:
				OVI_REG_WR(0xC907AFFC, 0x00100001);
				break;
			case LX_OVI_TCON_LOW_POWER2:
			case LX_OVI_TCON_LOW_POWER2_SC_OFF:
				OVI_REG_WR(0xC907AFFC, 0x00103001);
				break;
			case LX_OVI_TCON_BOE_CINEMA:
			case LX_OVI_TCON_BOE_VIVID:
			case LX_OVI_TCON_BOE_UTUBE0:
			case LX_OVI_TCON_BOE_UTUBE1:
				OVI_WPR_M19_RdFL(siw_reg_main);
				OVI_WPR_M19_Wr01(siw_reg_main, dga_mode_sel, enParam - LX_OVI_TCON_BOE_CINEMA);
				OVI_WPR_M19_WrFL(siw_reg_main);
				break;
			case LX_OVI_TCON_MLE_MODE_OFF:
			default :
				OVI_REG_WR(0xC907AFFC, 0x00000000);
				break;
		}
	} while(0);

	return ret;
}

int OVI_HW_M19_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams)
{
	int ret = RET_OK;
	
	do {

		if ((pstParams == NULL) || (_gOviHwM19Info.tscicWritingFlag == TRUE))
		{
			OVI_ERROR("[OVI] structure is pointed Null pointer! or already running!\n");
			ret = RET_ERROR;
			break;
		}

		if (pstParams->u32TscicSize == 0) // TSCIC disable for debug
		{
			// [NOTE] FCIC function enable/disable : 0xC90750A8 [3:0] - 0x0/0xC
			// FCIC disable setting
			OVI_TCON_M19_RdFL(tcon_control);
			OVI_TCON_M19_Wr01(tcon_control, fcic_en, 0x0);
			OVI_TCON_M19_WrFL(tcon_control);

			// FCIC Clock gating ON
			CTOP_CTRL_M19Ax_RdFL(DPE_SYN, crg_dpe00);
			CTOP_CTRL_M19Ax_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 1);
			CTOP_CTRL_M19Ax_WrFL(DPE_SYN, crg_dpe00);

			return RET_OK;
		}

		// check input table size
		if ((pstParams->u32Ctrlsize != OVI_HW_M19_INPUT_TSCIC_CTRL_SIZENUM) || (pstParams->pu8ControlTbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Control size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		if ((pstParams->u32TscicSize != OVI_HW_M19_INPUT_TSCIC_DATA_SIZE) || (pstParams->pu32TscicTbl == NULL))
		{
			OVI_ERROR("[OVI] Input TSCIC Table size is not correct! or Data is NULL!\n");
			ret = RET_ERROR;
			break;
		}

		_gOviHwM19Info.tscicSize = pstParams->u32TscicSize;
		_gOviHwM19Info.tscicCtrlSizeNum = pstParams->u32Ctrlsize;

		_gOviHwM19Info.tscicU8CtrlData = (UINT8 *)vmalloc(_gOviHwM19Info.tscicCtrlSizeNum);
		if(_gOviHwM19Info.tscicU8CtrlData == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			break;
		}

		ret = copy_from_user(_gOviHwM19Info.tscicU8CtrlData, (void __user *)pstParams->pu8ControlTbl, _gOviHwM19Info.tscicCtrlSizeNum);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			if(_gOviHwM19Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwM19Info.tscicU8CtrlData);
				_gOviHwM19Info.tscicU8CtrlData = NULL;
			}
			break;
		}

		_gOviHwM19Info.tscicU32Tbl = (UINT32 *)vmalloc(_gOviHwM19Info.tscicSize);
		if(_gOviHwM19Info.tscicU32Tbl == NULL)
		{
			OVI_ERROR("[OVI] memory allocate failed! \n");
			ret = RET_ERROR;
			if(_gOviHwM19Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwM19Info.tscicU8CtrlData);
				_gOviHwM19Info.tscicU8CtrlData = NULL;
			}
			break;
		}

		ret = copy_from_user(_gOviHwM19Info.tscicU32Tbl, (void __user *)pstParams->pu32TscicTbl, _gOviHwM19Info.tscicSize);
		if(ret)
		{
			OVI_ERROR("[OVI] Error in copying from user! \n");
			ret = RET_ERROR;
			if(_gOviHwM19Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwM19Info.tscicU8CtrlData);
				_gOviHwM19Info.tscicU8CtrlData = NULL;
			}
			if(_gOviHwM19Info.tscicU32Tbl != NULL)
			{
				vfree(_gOviHwM19Info.tscicU32Tbl);
				_gOviHwM19Info.tscicU32Tbl = NULL;
			}
			break;
		}

		// FCIC Clock gating OFF
		CTOP_CTRL_M19Ax_RdFL(DPE_SYN, crg_dpe00);
		CTOP_CTRL_M19Ax_Wr01(DPE_SYN, crg_dpe00, tcon_fcic_clk_gate_en, 0);
		CTOP_CTRL_M19Ax_WrFL(DPE_SYN, crg_dpe00);

		// FCIC enable setting
		OVI_TCON_M19_RdFL(tcon_control);
		OVI_TCON_M19_Wr01(tcon_control, fcic_en, 0x1);
		OVI_TCON_M19_WrFL(tcon_control);

		_gOviHwM19Info.tscicThread = kthread_run(OVI_M19_TscicWriteThread, NULL, "ovi_tscic");
		if (IS_ERR(_gOviHwM19Info.tscicThread))
		{
			OVI_ERROR("[OVI] Error in starting thread! \n");
			ret = RET_ERROR;
			if(_gOviHwM19Info.tscicU8CtrlData != NULL)
			{
				vfree(_gOviHwM19Info.tscicU8CtrlData);
				_gOviHwM19Info.tscicU8CtrlData = NULL;
			}
			if(_gOviHwM19Info.tscicU32Tbl != NULL)
			{
				vfree(_gOviHwM19Info.tscicU32Tbl);
				_gOviHwM19Info.tscicU32Tbl = NULL;
			}
			break;
		}
	} while(0);

	return ret;
}

int OVI_HW_M19_SetTconReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	UINT32 regField;

	do {
		OVI_TCON_M19_RdFL(tcon_control);
		OVI_TCON_M19_Rd01(tcon_control, epi_out, regField);
		if (!regField) break;
		
		OVI_TCON_M19_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_M19_Wr01(tcon_hor_mode, hor_reverse, _gOviHwM19Info.horReverseRegFieldValue ? 0 : 1);
		}
		else {
			OVI_TCON_M19_Wr01(tcon_hor_mode, hor_reverse, _gOviHwM19Info.horReverseRegFieldValue);
		}
		OVI_TCON_M19_WrFL(tcon_hor_mode);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetLvdsReverse(BOOLEAN bParam)
{
	int ret = RET_OK;
	UINT32 regField;

	do {
		OVI_TCON_M19_RdFL(tcon_control);
		OVI_TCON_M19_Rd01(tcon_control, epi_out, regField);
		if (regField) break;
		
		OVI_TCON_M19_RdFL(tcon_hor_mode);
		if(bParam) {
			OVI_TCON_M19_Wr01(tcon_hor_mode, hor_reverse, 0x1);
		}
		else {
			OVI_TCON_M19_Wr01(tcon_hor_mode, hor_reverse, 0x0);
		}
		OVI_TCON_M19_WrFL(tcon_hor_mode);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M19_RdFL(tcon_pgen_ctl);

		// pattern source color setting
		OVI_TCON_M19_RdFL(tcon_pgen_agpr1);
		OVI_TCON_M19_Wr(tcon_pgen_agpr1, 0x03FF);
		OVI_TCON_M19_WrFL(tcon_pgen_agpr1);

		OVI_TCON_M19_RdFL(tcon_pgen_agpg1);
		OVI_TCON_M19_Wr(tcon_pgen_agpg1, 0x03FF);
		OVI_TCON_M19_WrFL(tcon_pgen_agpg1);

		OVI_TCON_M19_RdFL(tcon_pgen_agpb1);
		OVI_TCON_M19_Wr(tcon_pgen_agpb1, 0x03FF);
		OVI_TCON_M19_WrFL(tcon_pgen_agpb1);

		switch(pstParams->eMode)
		{
			case LX_OVI_TCON_TPG_OFF:		// pattern off
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x0);
				break;
			case LX_OVI_TCON_TPG_BLACK:		// black pattern
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x4);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_WHITE:		// white pattern
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HVBAR:		// HVBar pattern
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x3);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR16GREY:		// Horizontal 16 grey pattern
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x8);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR64GREY:		// Horizontal 64 grey pattern
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x7);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR256GREY:		// Horizontal 256 grey pattern
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x6);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_HOR1024GREY:		// Horizontal 1024 grey pattern
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x5);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_TPG_VER16GREY:		// Vertical 16 grey pattern
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0xC);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_reverse, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default :
				break;
		}
		OVI_TCON_M19_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetChannelPower(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		_OVI_M19_DispOutputEnable(bParam);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_M19_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_LVDS_OUT_JEIDA:
				OVI_OIF_M19_Wr01(oif_lvds_config0, lvds_lsb_first, 0x0);
				break;
			case LX_OVI_LVDS_OUT_VESA:
				OVI_OIF_M19_Wr01(oif_lvds_config0, lvds_lsb_first, 0x1);
				break;
			default:
				break;
		}
		OVI_OIF_M19_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_M19_RdFL(oif_lvds_config0);
		switch(enParam)
		{
			case LX_OVI_8BIT:
				OVI_OIF_M19_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x1);
				break;
			case LX_OVI_10BIT:
				OVI_OIF_M19_Wr01(oif_lvds_config0, lvds_8bit_mode, 0x0);
				break;
			default:
				break;
		}
		OVI_OIF_M19_WrFL(oif_lvds_config0);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetLvdsBlack(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_OIF_M19_RdFL(oif_lvds_config1);
		OVI_OIF_M19_RdFL(oif_lvds_config2);
		OVI_OIF_M19_RdFL(oif_vx1_config3);
		OVI_OIF_M19_RdFL(oif_vx1_config4);

		if(!bParam) // original data out
		{
			OVI_OIF_M19_Wr01(oif_lvds_config1, lvds_force_even_data, 0x0);
			OVI_OIF_M19_Wr01(oif_lvds_config2, lvds_force_odd_data, 0x0);

			OVI_OIF_M19_Wr01(oif_vx1_config3, vx1_force_even_data, 0x0);
			OVI_OIF_M19_Wr01(oif_vx1_config4, vx1_force_odd_data, 0x0);
		}
		else // black data out
		{
			OVI_OIF_M19_Wr01(oif_lvds_config1, lvds_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_M19_Wr01(oif_lvds_config2, lvds_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);

			OVI_OIF_M19_Wr01(oif_vx1_config3, vx1_force_even_data, bParam == 1 ? 0x40000000 : 0x400003FF);
			OVI_OIF_M19_Wr01(oif_vx1_config4, vx1_force_odd_data, bParam == 1 ? 0x40000000 : 0x400003FF);
		}
		OVI_OIF_M19_WrFL(oif_lvds_config1);
		OVI_OIF_M19_WrFL(oif_lvds_config2);
		OVI_OIF_M19_WrFL(oif_vx1_config3);
		OVI_OIF_M19_WrFL(oif_vx1_config4);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetClock(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M19_RdFL(tcon_gclk_control);
		OVI_TCON_M19_RdFL(tcon_mclk_control);

		if(bParam)
		{
			OVI_TCON_M19_Wr01(tcon_gclk_control, gclk_en, 0x1);
			OVI_TCON_M19_Wr01(tcon_mclk_control, mclk_en, 0x1);
		}
		else
		{
			OVI_TCON_M19_Wr01(tcon_gclk_control, gclk_en, 0x0);
			OVI_TCON_M19_Wr01(tcon_mclk_control, mclk_en, 0x0);
		}

		OVI_TCON_M19_WrFL(tcon_gclk_control);
		OVI_TCON_M19_WrFL(tcon_mclk_control);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetEpiDataScramble(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M19_RdFL(tcon_epi_mode);

		if(bParam)
		{
			OVI_TCON_M19_Wr01(tcon_epi_mode, scr_en, 0x1);
		}
		else
		{
			OVI_TCON_M19_Wr01(tcon_epi_mode, scr_en, 0x0);
		}

		OVI_TCON_M19_WrFL(tcon_epi_mode);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetAdvanced10bit(BOOLEAN bParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M19_RdFL(a10_ctrl);
		OVI_TCON_M19_RdFL(tcon_odc_opt2);

		if(bParam)
		{
			OVI_TCON_M19_Wr01(a10_ctrl, a10_on, 0x1);
			OVI_TCON_M19_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x1);
		}
		else
		{
			OVI_TCON_M19_Wr01(a10_ctrl, a10_on, 0x0);
			OVI_TCON_M19_Wr01(tcon_odc_opt2, pre_dit_in_sel, 0x0);
		}

		OVI_TCON_M19_WrFL(a10_ctrl);
		OVI_TCON_M19_WrFL(tcon_odc_opt2);
	} while(0);

	return ret;
}

int OVI_HW_M19_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam)
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

		if (OVI_HW_M19_INPUT_VCOM_PAT_DATA_SIZE != pstParam->sizeNum)
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

		OVI_TCON_M19_RdFL(tcon_pgen_vcomp0);
		OVI_TCON_M19_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, patData[0]);
		OVI_TCON_M19_WrFL(tcon_pgen_vcomp0);

		OVI_TCON_M19_RdFL(tcon_pgen_vcomp1);
		OVI_TCON_M19_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, patData[1]);
		OVI_TCON_M19_WrFL(tcon_pgen_vcomp1);

		OVI_TCON_M19_RdFL(tcon_pgen_vcomp2);
		OVI_TCON_M19_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, patData[2]);
		OVI_TCON_M19_WrFL(tcon_pgen_vcomp2);

		OVI_TCON_M19_RdFL(tcon_pgen_vcomp3);
		OVI_TCON_M19_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, patData[3]);
		OVI_TCON_M19_WrFL(tcon_pgen_vcomp3);

		if (level > 0)
		{
			OVI_TCON_M19_RdFL(tcon_pgen_agpr1);
			OVI_TCON_M19_Wr01(tcon_pgen_agpr1, pgen_color_r1, level);
			OVI_TCON_M19_WrFL(tcon_pgen_agpr1);

			OVI_TCON_M19_RdFL(tcon_pgen_agpg1);
			OVI_TCON_M19_Wr01(tcon_pgen_agpg1, pgen_color_g1, level);
			OVI_TCON_M19_WrFL(tcon_pgen_agpg1);

			OVI_TCON_M19_RdFL(tcon_pgen_agpb1);
			OVI_TCON_M19_Wr01(tcon_pgen_agpb1, pgen_color_b1, level);
			OVI_TCON_M19_WrFL(tcon_pgen_agpb1);
		}
	} while(0);

	if(u16vcomPatData != NULL)
		vfree(u16vcomPatData);

	return ret;
}

int OVI_HW_M19_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam)
{
	int ret = RET_OK;

	do {
		OVI_TCON_M19_RdFL(tcon_pgen_ctl);

		switch(enParam)
		{
			case LX_OVI_TCON_VCOM_PAT_CTRL_OFF:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x0);

				OVI_TCON_M19_RdFL(tcon_pgen_vcomp0);
				OVI_TCON_M19_Wr01(tcon_pgen_vcomp0, pgen_vcomp0, 0x0);
				OVI_TCON_M19_WrFL(tcon_pgen_vcomp0);

				OVI_TCON_M19_RdFL(tcon_pgen_vcomp1);
				OVI_TCON_M19_Wr01(tcon_pgen_vcomp1, pgen_vcomp1, 0x0);
				OVI_TCON_M19_WrFL(tcon_pgen_vcomp1);

				OVI_TCON_M19_RdFL(tcon_pgen_vcomp2);
				OVI_TCON_M19_Wr01(tcon_pgen_vcomp2, pgen_vcomp2, 0x0);
				OVI_TCON_M19_WrFL(tcon_pgen_vcomp2);

				OVI_TCON_M19_RdFL(tcon_pgen_vcomp3);
				OVI_TCON_M19_Wr01(tcon_pgen_vcomp3, pgen_vcomp3, 0x0);
				OVI_TCON_M19_WrFL(tcon_pgen_vcomp3);

				OVI_TCON_M19_RdFL(tcon_pgen_agpr1);
				OVI_TCON_M19_Wr01(tcon_pgen_agpr1, pgen_color_r1, 0x3FF);
				OVI_TCON_M19_WrFL(tcon_pgen_agpr1);

				OVI_TCON_M19_RdFL(tcon_pgen_agpg1);
				OVI_TCON_M19_Wr01(tcon_pgen_agpg1, pgen_color_g1, 0x3FF);
				OVI_TCON_M19_WrFL(tcon_pgen_agpg1);

				OVI_TCON_M19_RdFL(tcon_pgen_agpb1);
				OVI_TCON_M19_Wr01(tcon_pgen_agpb1, pgen_color_b1, 0x3FF);
				OVI_TCON_M19_WrFL(tcon_pgen_agpb1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_ON:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x1E);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM1:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x16);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM2:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x17);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM3:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x18);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM4:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x19);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM5:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x1A);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM6:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x1B);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM7:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x1C);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			case LX_OVI_TCON_VCOM_PAT_CTRL_VCOM8:
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_mode, 0x1D);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_sync_mode, 0x0);
				OVI_TCON_M19_Wr01(tcon_pgen_ctl, pgen_test, 0x1);
				break;
			default:
				break;
		}

		OVI_TCON_M19_WrFL(tcon_pgen_ctl);
	} while(0);

	return ret;
}

int OVI_HW_M19_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams)
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
		
		if (memcmp(&_gOviHwM19Info.dispOption, pstParams, sizeof(LX_OVI_DISPLAY_INFO_T)) != 0)
		{
			OVI_PRINT("\n[OVI_HW_M19_DisplayResume] WARN:Disp Option Changed! [%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-%d-0x%x]\n\r",
				pstParams->panelInterface, pstParams->panelResolution, pstParams->frcChipType, pstParams->panelCellType,
				pstParams->panelVersion, pstParams->panelInch, pstParams->panelMaker, pstParams->panelBacklight, 
				pstParams->panelLedBar, pstParams->panelFramerate, pstParams->lvdsBit,
				pstParams->lvdsType, pstParams->dispOutLaneBw, pstParams->userSpecificOption.all);
		}

		_OVI_M19_DispOutputEnable(TRUE);
	} while(0);

	return ret;
}

int OVI_HW_M19_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int	i;
	UINT32 val;

	switch(proc_id)
	{
		case OVI_HAL_PROC_ID_DETAIL_INFO:
		{
			OVI_TCON_M19_RdFL(tcon_base_address);
			val = OVI_TCON_M19_Rd(tcon_base_address);
			seq_printf(m, "tcon_base_addr: 0x%08x\n", val);

			seq_printf(m, "ch_power_on_reg1: 0x%08x\n", _gOviHwM19Info.chPowerOnRegValue1 );

			for (i=0; i<_gOVIOutputModes_M19.number_of_modes; i++)
			{
				seq_printf(m, "output_mode%d: %s", i, _gOVIOutputModes_M19.pOVIOutputModes[i].index + strlen("Display settings for M19"));
			}

			OVI_OIF_M19_RdFL(oif_lvds_config0);

			OVI_OIF_M19_Rd01(oif_lvds_config0, lvds_lsb_first, val);
			seq_printf(m, "lvds.format: %s (0x%x)\n", (val)?"vesa":"jeida", val);

			OVI_OIF_M19_Rd01(oif_lvds_config0, lvds_8bit_mode, val);
			seq_printf(m, "lvds.bit: %d bit (0x%x)\n", (val)? 8:10, val);

			OVI_OIF_M19_RdFL(oif_lvds_config1);
			OVI_OIF_M19_Rd01(oif_lvds_config1, lvds_force_even_data, val);
			seq_printf(m, "lvds.black_out: %s (0x%x)\n", (val)? "black":"orignal", val);

			OVI_TCON_M19_RdFL(tcon_gclk_control);
			OVI_TCON_M19_Rd01(tcon_gclk_control, gclk_en, val);
			seq_printf(m, "tcon.gclk: %s (0x%x)\n", (val)?"on":"off", val);

			OVI_TCON_M19_RdFL(tcon_mclk_control);
			OVI_TCON_M19_Rd01(tcon_mclk_control, mclk_en, val);
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
