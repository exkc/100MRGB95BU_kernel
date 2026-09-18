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
 *	BE TOP module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
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
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/vmalloc.h>
#include "os_util.h"

#include "be_dbg.h"
#include "be_cfg.h"
#include "be_def.h"
#include "../fwi/ipc_def_m17.h"
#include "ipc_drv.h"
#include "be_top_hw_m17.h"

// For CTOP/DPE register access
#include "../../../core/sys/sys_regs.h"
#include "../reg/be_reg_dpe_m17.h"

#include "ipc_cmd_header.h"

// For Status Management
#include "../../../core/be/video_status_keeper.h"

#include "../../../core/de/de_sync.h"
#include "../../../core/gpio/gpio_drv.h"
#include "../../../core/gpio/gpio_core.h"
#include "../../../core/de/hal/ipc_phys_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define BE_TOP_HW_M17_LSR_TABLE_OFFSET 0x0
#define BE_TOP_HW_M17_GSR_TABLE_OFFSET (BE_TOP_HW_M17_LSR_TABLE_OFFSET + 0x800)

#define BE_TOP_HW_M17_TEST_INPUT_LAG
#ifdef BE_TOP_HW_M17_TEST_INPUT_LAG
#define	BE_TOP_HW_M17_IPP_PIXEL_CTRL_BASE		(0xC9001448)
#define BE_TOP_HW_M17_PATTERN_OFF		(0)
#define BE_TOP_HW_M17_PATTERN_WHITE		(1)
#define BE_TOP_HW_M17_PATTERN_BLACK		(2)
	
#define BE_TOP_HW_M17_PIN_MUX_PORT		(119)
#define BE_TOP_HW_M17_PIN_NORMAL		(0)
#define BE_TOP_HW_M17_PIN_GPIO			(1)
#endif

/* For register direct access
 * 2013-10-14 chobits : Need to change this ...*/

static volatile unsigned int *gMapped_address;
#define BE_REG_WR(address,data)   \
	gMapped_address=(volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) break;\
		*gMapped_address = data;\
		iounmap((void *)gMapped_address);\
	}while(0);\

#define BE_REG_RD(address,data)   \
	gMapped_address = (volatile UINT32 *)ioremap(address, sizeof(UINT32));\
	do{\
		if(gMapped_address == NULL) {data = 0; break;}\
		data = (unsigned int)*gMapped_address;\
		iounmap((void *)gMapped_address);\
	}while(0);\

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {

} BE_TOP_HW_M17_INFO_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern BE_MEM_CFG_T *gpBeMem;
extern DPE_LED_REG_M17_T gDPE_LED_M17;
extern PE_OSD_REG_M17_T gPE_OSD_M17;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
UINT32 gInputLagCnt_M17 = 0; 
volatile UINT32 *gIPP_PIXEL_CTRL_M17 = NULL;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#ifdef BE_TOP_HW_M17_TEST_INPUT_LAG
int BE_TOP_HW_M17_InputLagHandler(void);
static int BE_TOP_HW_M17_SetPattern(UINT32 bOnOff);
static int BE_TOP_HW_M17_SetGpioValue(UINT32 value);
static int BE_TOP_HW_M17_SetGpioMux(UINT32 value);
#endif

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
//static BE_TOP_HW_M17_INFO_T beTopHwM17Info;

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_TOP_HW_M17_Initialize(void)
{
	int ret = RET_OK;

	do {

	} while(0);

	return ret;
}

int BE_TOP_HW_M17_Close(void)
{
	int ret = RET_OK;

	do {

	} while(0);

	return ret;
}

int BE_TOP_HW_M17_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_BLOCK_BYPASS_T, stHwParams);

		if (pstParams->bLEDBypass <= 1)
		{
			DPE_LED_M17_RdFL(led_led_detour);
			if (pstParams->bLEDBypass)
			{
				DPE_LED_M17_Wr01(led_led_detour, led_detour, 0x1);
			}
			else
			{
				DPE_LED_M17_Wr01(led_led_detour, led_detour, 0x0);
			}
			DPE_LED_M17_WrFL(led_led_detour);
		}
		
		/* change value LX_BE to BE_IPC */
		stHwParams.uH3DBypass = (pstParams->bH3DBypass > 1) ? 0xFFFFFFFF : pstParams->bH3DBypass;
		stHwParams.uFRCBypass = (pstParams->bFRCBypass > 1) ? 0xFFFFFFFF : pstParams->bFRCBypass;
		stHwParams.uWCGBypass = (pstParams->bWCGBypass > 1) ? 0xFFFFFFFF : pstParams->bWCGBypass;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_BLOCK_BYPASS), (void*)&stHwParams, sizeof(BE_IPC_BLOCK_BYPASS_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M17_Toggle3DLR(LX_BE_3D_LR_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_3D_LR_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bOutLR = (pstParams->bOutLR == 0xFFFF) ? 0xFFFFFFFF : pstParams->bOutLR;

		/* Video Status */
		status = stHwParams.bOutLR;
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_H3D_LR_TOGGLE, status);

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_TOGGLE_3D_LR), (void*)&stHwParams, sizeof(BE_IPC_3D_LR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M17_Set3DConvergence(LX_BE_3D_CONVERGENCE_T *pstParams)
{
	int ret = RET_OK;
	unsigned int status;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_3D_CONVERGENCE_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bTDConvEnable = pstParams->u16ConvergenceEnable == 0xFFFF ? 0xFFFFFFFF : pstParams->u16ConvergenceEnable;
		stHwParams.uTDConvVal = pstParams->u16ConvergenceVal == 0xFFFF ? 0xFFFFFFFF : pstParams->u16ConvergenceVal;

		/* Video Status */
		status = (0xFFFF0000&(stHwParams.bTDConvEnable <<16))|(0x0000FFFF&(stHwParams.uTDConvVal));
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_BE, BE_SKEEPER_H3D_CONVERGENCE, status);

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_3D_CONVERGENCE), (void *)&stHwParams, sizeof(BE_IPC_3D_CONVERGENCE_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M17_SetBlackBar(LX_BE_BLACK_BAR_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_BLACK_BAR_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uTDBlackBarEnable = pstParams->u8BarOn == 0xFF ? 0xFFFFFFFF : pstParams->u8BarOn;
		stHwParams.uTDBlackBarVal = pstParams->u8BarVal == 0xFF ? 0xFFFFFFFF : pstParams->u8BarVal;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_BLACK_BAR), (void *)&stHwParams, sizeof(BE_IPC_BLACK_BAR_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M17_SetRealCinema(LX_BE_REAL_CINEMA_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_REAL_CINEMA_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uRealCinemaEnable = pstParams->u32RealCinemaEnable;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_REAL_CINEMA), (void *)&stHwParams, sizeof(BE_IPC_REAL_CINEMA_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M17_SetOrbit(LX_BE_ORBIT_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_ORBIT_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.bOrbitEnable = pstParams->bOnOff >= 0xFF ? 0xFFFFFFFF : pstParams->bOnOff;
		stHwParams.bAutoMode = pstParams->bAutoMode >= 0xFF ? 0xFFFFFFFF : pstParams->bAutoMode;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_ORBIT), (void *)&stHwParams, sizeof(BE_IPC_ORBIT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_TOP_HW_M17_SetLSR(BOOLEAN bParam)
{
	int ret = RET_OK;

	do{
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			/* Do Nothing */
		}
		else
		{
			IPC_SET_DEFAULT_PARAM(BE_IPC_LSR_T, stHwParams);

			/* change value LX_BE to BE_IPC */
			stHwParams.bLSRMode = bParam >= 0xFF ? 0xFFFFFFFF : bParam;

			ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_LSR), (void *)&stHwParams, sizeof(BE_IPC_LSR_T));
			if(ret) BREAK_WRONG(ret);
		}
	} while(0);

	return ret;
}

#ifdef BE_TOP_HW_M17_TEST_INPUT_LAG
int BE_TOP_HW_M17_SetLagParam(UINT32 bParam)
{
	int ret = RET_OK;

	BE_NOTI("BE_bParam: %d\n" ,bParam);

	if (bParam  == 1)	//start
	{
		//step 1. Interrupt enable
		ipc_phys_hal_InitInterrupt(0, TRUE);
		//step 2. remap gIPP_PIXEL_CTRL_M17
		if (gIPP_PIXEL_CTRL_M17 == NULL)
		{
			gIPP_PIXEL_CTRL_M17	= (volatile UINT32 *)ioremap(BE_TOP_HW_M17_IPP_PIXEL_CTRL_BASE, sizeof(UINT32));
		}
		//step 3. counter initialize & pattern black
		gInputLagCnt_M17 = 0;
		BE_TOP_HW_M17_SetPattern(BE_TOP_HW_M17_PATTERN_BLACK); //BLACK
		//step 4. GPIO setMux (NORMAL)
		BE_TOP_HW_M17_SetGpioMux(BE_TOP_HW_M17_PIN_GPIO);
		//step 5. interrupt regit
		de_srcsync_register(TRUE, BE_TOP_HW_M17_InputLagHandler, "inputLag_handler");
	}	
	else	// end
	{				
		//step 1. interrupt unregit
		de_srcsync_register(FALSE, BE_TOP_HW_M17_InputLagHandler, "inputLag_handler");		
		//step 2. GPIO setMux (GPIO) 
		BE_TOP_HW_M17_SetGpioMux(BE_TOP_HW_M17_PIN_NORMAL);
		//step 3. counter initialize & pattern off
		BE_TOP_HW_M17_SetPattern(BE_TOP_HW_M17_PATTERN_OFF); //OFF
		gInputLagCnt_M17 = 0;	
		//step 4. unmap gIPP_PICEL_CTRL
		if (gIPP_PIXEL_CTRL_M17)
		{
			iounmap((void *)gIPP_PIXEL_CTRL_M17);	
			gIPP_PIXEL_CTRL_M17 = NULL;
		}
		//step 5. Interrupt diable
		ipc_phys_hal_InitInterrupt(0, FALSE);
	}
	return ret;
}

int BE_TOP_HW_M17_InputLagHandler(void)
{
	//step 1. ex) if count ==64 --> pattern white & GPIO ON 
	//step 2. ex) if count ==128 --> pattern black & GPIO OFF
	//step 3. count increase 
#if 0
//	if ((gInputLagCnt_M17&0x1FF)  == 0x100)
	if (gInputLagCnt_M17 % 25 == 0)
	{
		BE_TOP_HW_M17_SetPattern(BE_TOP_HW_M17_PATTERN_WHITE); //white
		BE_TOP_HW_M17_SetGpioValue(TRUE);

		BE_NOTI("gInputLagCnt: %x, set white pattern\n" ,gInputLagCnt_M17);
	}
//	else if ((gInputLagCnt_M17&0x1FF)  == 0x000)
	else if (gInputLagCnt_M17 % 25 != 0)
	{
		BE_TOP_HW_M17_SetPattern(BE_TOP_HW_M17_PATTERN_BLACK); //bLack
		BE_TOP_HW_M17_SetGpioValue(FALSE);

		BE_NOTI("gInputLagCnt: %x, set black pattern\n" ,gInputLagCnt_M17);
	}
#endif

	int interruptCnt = 0; 
	interruptCnt = gInputLagCnt_M17/25;
	
	if (interruptCnt % 2 == 0)
	{
		BE_TOP_HW_M17_SetPattern(BE_TOP_HW_M17_PATTERN_WHITE); //bLack
		BE_TOP_HW_M17_SetGpioValue(TRUE);

		BE_NOTI("gInputLagCnt: %x, set black pattern\n" ,gInputLagCnt_M17);
	}
	else
	{
		BE_TOP_HW_M17_SetPattern(BE_TOP_HW_M17_PATTERN_BLACK); //white
		BE_TOP_HW_M17_SetGpioValue(FALSE);
		
		BE_NOTI("gInputLagCnt: %x, set white pattern\n" ,gInputLagCnt_M17);
	}
	gInputLagCnt_M17++;

	return 0;
}

// bOnOff: 0:off, 1:white, 2. black
static int BE_TOP_HW_M17_SetPattern(UINT32 bOnOff)
{
	if (bOnOff == BE_TOP_HW_M17_PATTERN_WHITE)
	{
		*gIPP_PIXEL_CTRL_M17 = 0x80FF8080;
	}
	else if (bOnOff == BE_TOP_HW_M17_PATTERN_BLACK)
	{
		*gIPP_PIXEL_CTRL_M17 = 0x80008080;
	}
	else //OFF BE_TOP_HW_M17_PATTERN_OFF
	{
		*gIPP_PIXEL_CTRL_M17 = 0x00008080;
	}
	return 0;
}

static int BE_TOP_HW_M17_SetGpioValue(UINT32 value)
{	
	GPIO_DevSetValue(BE_TOP_HW_M17_PIN_MUX_PORT, value);

	return 0;
}

static int BE_TOP_HW_M17_SetGpioMux(UINT32 value)
{
	GPIO_DevSetPinMux(BE_TOP_HW_M17_PIN_MUX_PORT, value);
//	GPIO_DevSetMode(TEST_GPIO_CONTROL, LX_GPIO_MODE_OUTPUT);
	
	return 0;
}
#endif


int BE_TOP_HW_M17_SetLSRParam(LX_BE_LSR_T *pstParams)
{
	int ret = RET_OK;
	int inSizeNum;
	int inSize;
	int lsrTblVer = 0x1;
	char *pBuffer = NULL;
	char *pAddr = NULL;
	BE_CH_MEM_T *pFwMem = NULL;

	do{
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			IPC_SET_DEFAULT_PARAM(BE_IPC_LSR_T, stHwParams);

			CHECK_NULL(pstParams);
			CHECK_NULL(pstParams->lsrTbl.pu32Data);

			inSizeNum = pstParams->lsrTbl.u32SizeNum;

			inSize = inSizeNum * sizeof(pstParams->lsrTbl.pu32Data[0]);
			
			pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
			CHECK_NULL(pFwMem);
			CHECK_NULL(pFwMem->fw_base);

			if ((inSize + BE_TOP_HW_M17_LSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

			pBuffer = (char *)vmalloc(inSize);
		 	CHECK_NULL(pBuffer);
		    ret = copy_from_user(pBuffer, (void __user *)pstParams->lsrTbl.pu32Data, inSize);
		    if (ret)
			{
				BREAK_WRONG(ret);
		    }

			((UINT32 *)pBuffer)[0] = ((UINT32 *)pBuffer)[0] & 0x00FFFFFF; // clear sizenum info

			pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
			CHECK_NULL(pAddr);
			memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_M17_LSR_TABLE_OFFSET), pBuffer, inSize);

			wmb();

			vunmap_phys(pAddr);

			/* change value LX_BE to BE_IPC */
			stHwParams.bLSRMode = (pstParams->u32LsrMode) >= 0xFF ? 0xFFFFFFFF : (pstParams->u32LsrMode);
			stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_M17_LSR_TABLE_OFFSET;
			stHwParams.uDbtype = (lsrTblVer << 16) | inSizeNum;

			ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_LSR), (void *)&stHwParams, sizeof(BE_IPC_LSR_T));
			if(ret) BREAK_WRONG(ret);
		}
	} while(0);

	if (pBuffer != NULL)
	{
		vfree(pBuffer);
	}
	
	return ret;
}

int BE_TOP_HW_M17_SetGSR(LX_BE_GSR_T *pstParams)
{
	int ret = RET_OK;
	int inSizeNum;
	int inSize;
	int gsrTblVer = 0x1;
	char *pBuffer = NULL;
	char *pAddr = NULL;
	BE_CH_MEM_T *pFwMem = NULL;

	do{
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			IPC_SET_DEFAULT_PARAM(BE_IPC_GSR_T, stHwParams);

			CHECK_NULL(pstParams);
			CHECK_NULL(pstParams->gsrTbl.pu32Data);

			inSizeNum = pstParams->gsrTbl.u32SizeNum;

			inSize = inSizeNum * sizeof(pstParams->gsrTbl.pu32Data[0]);
			
			pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[3];
			CHECK_NULL(pFwMem);
			CHECK_NULL(pFwMem->fw_base);

			if ((inSize + BE_TOP_HW_M17_GSR_TABLE_OFFSET) > pFwMem->fw_size) BREAK_WRONG(inSize);

			pBuffer = (char *)vmalloc(inSize);
			CHECK_NULL(pBuffer);
			ret = copy_from_user(pBuffer, (void __user *)pstParams->gsrTbl.pu32Data, inSize);
			if (ret)
			{
				BREAK_WRONG(ret);
			}

			((UINT32 *)pBuffer)[0] = ((UINT32 *)pBuffer)[0] & 0x00FFFFFF; // clear sizenum info

			pAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
			CHECK_NULL(pAddr);
			memcpy((char *)((uintptr_t)pAddr + (uintptr_t)BE_TOP_HW_M17_GSR_TABLE_OFFSET), pBuffer, inSize);

			wmb();

			vunmap_phys(pAddr);

			/* change value LX_BE to BE_IPC */
			stHwParams.bGSRMode = 1;
			stHwParams.uBaseAddr = pFwMem->fw_base + BE_TOP_HW_M17_GSR_TABLE_OFFSET;
			stHwParams.uDbtype = (gsrTblVer << 16) | inSizeNum;

			ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_GSR), (void *)&stHwParams, sizeof(BE_IPC_GSR_T));
			if(ret) BREAK_WRONG(ret);
		}
	} while(0);

	if (pBuffer != NULL)
	{
		vfree(pBuffer);
	}
	
	return ret;
}

int BE_TOP_HW_M17_GetGSRStatus(BOOLEAN *pbParam)
{
	int ret = RET_OK;
	UINT32 regVal;

	do{
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			CHECK_NULL(pbParam);

			BE_REG_RD(0xC9025028, regVal);

			*pbParam = (regVal & 0x40) ? TRUE : FALSE;
		}
	} while(0);
	
	return ret;
}

int BE_TOP_HW_M17_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams)
{
	int ret = RET_OK;
	UINT32 arrData[1];

	do{
		if (lx_chip_rev() >= LX_CHIP_REV(M17, C0))
		{
			CHECK_NULL(pstParams);

			if (pstParams->levelTbl.u32SizeNum != 1) BREAK_WRONG(pstParams->levelTbl.u32SizeNum);

			ret = copy_from_user(arrData, (void __user *)pstParams->levelTbl.pu32Data, sizeof(UINT32)*(pstParams->levelTbl.u32SizeNum));
			if(ret) BREAK_WRONG(ret);

			PE_OSD_M17C0_RdFL(osd0_vsp_bosd_ctrl_0);
			PE_OSD_M17C0_Wr01(osd0_vsp_bosd_ctrl_0, reg_vspyc_en, pstParams->bOnOff ? 0x1 : 0x0);
			if (arrData[0] == 0x0)
			{
				PE_OSD_M17C0_Wr01(osd0_vsp_bosd_ctrl_0, r_contrast, 0x200);
			}
			else
			{
				PE_OSD_M17C0_Wr01(osd0_vsp_bosd_ctrl_0, r_contrast, ((0xFF - arrData[0]) << 1));
			}
			PE_OSD_M17C0_WrFL(osd0_vsp_bosd_ctrl_0);

			PE_OSD_M17C0_RdFL(osd0_vsp_bosd_ctrl_1);
			if (arrData[0] == 0x0)
			{
				PE_OSD_M17C0_Wr01(osd0_vsp_bosd_ctrl_1, r_saturation, 0x80);
			}
			else
			{
				PE_OSD_M17C0_Wr01(osd0_vsp_bosd_ctrl_1, r_saturation, ((0xFF - arrData[0]) >> 1));
			}
			PE_OSD_M17C0_Wr01(osd0_vsp_bosd_ctrl_1, r_offset, 0x200);
			PE_OSD_M17C0_WrFL(osd0_vsp_bosd_ctrl_1);

		}
	} while(0);

	return ret;
}


int BE_TOP_HW_M17_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams)
{
	int ret = RET_OK;

	do{
		IPC_SET_DEFAULT_PARAM(BE_IPC_DEBUG_DISPLAY_T, stHwParams);

		/* change value LX_BE to BE_IPC */
		stHwParams.uH3DDebugdisplay = pstParams->u8H3DDebugDisplay == 0xFF ? 0xFFFFFFFF : pstParams->u8H3DDebugDisplay;
		stHwParams.uPEDebugDisplay = pstParams->u8PEDebugDisplay == 0xFF ? 0xFFFFFFFF : pstParams->u8PEDebugDisplay;
		stHwParams.uLEDDebugDisplay = pstParams->u8LEDDebugDisplay == 0xFF ? 0xFFFFFFFF : pstParams->u8LEDDebugDisplay;

		ret = BE_KIPC_SetData(TOP_PACK_CMD(BE_TOP_SET_DEBUG_DISPLAY), (void *)&stHwParams, sizeof(BE_IPC_DEBUG_DISPLAY_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

/** BE/TOP m17 proc handler */
int BE_TOP_HW_M17_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	switch(proc_id)
	{
		case BE_TOP_PROC_ID_DETAIL_INFO:
		{

		}
		break;

		default: break;
	}

	return RET_OK;
}

/** @} */
