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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		won.hur
 *  @version	1.0
 *  @date		2019-03-25
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/delay.h>
#include "../hdmi20_drv.h" 			/* For debug prints */
#include "hdmi21_hal_driver.h"		/* Device Handler */
#include "hdmi21_rx_snps_isrunit.h"
#include "hdmi21_rx_snps_pdec.h"
#include "hdmi21_rx_disland.h"
#include "hdmi21_rx_snps_misc.h"
#include "hdmi21_rx_snps_pfifo.h"
#include "hdmi21_rx_snps_scdc.h"
#include "hdmi21_rx_phy.h"

#include "os_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mask;
	UINT32 clear;
	UINT32 force;
	UINT32 status;
	void (*irqFunc)(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
	UINT32 bitfield;
} HDMI21_ISRUNIT_SNPS_CTR_REG_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static void __HDMI21_ISRUNIT_Rx_Set_IsrMask(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_ISRUNIT_SNPS_TYPE_T type);

static void __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqScdcUnit(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqHdcpUnit(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
static void __HDMI21_ISRUNIT_Rx_ProcessIrqHdcp1Unit(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);



static void __HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int line);

static void __HDMI21_ISRUNIT_Rx_Set_ProceedAudioEarcDmacIsr(UINT32 intStatus);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevAudioControler[HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevPhyControler[HDMI21__DEV_PHY_CONTROL_LIST_MAXNUM];

/* 2019/09/04 */
extern void KDRV_AUDIO_EarcDmacIrq (UINT32 intStatus);

extern HDMI21_PHY_E60B0_SAFF_OFFSET_DATA_T gPhySaffOffsetResult[HDMI21_NUM_OF_PORTS_E60][HDMI21_HAL_CNT_OF_CHANNEL_IN_ONE_PHY];
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static int __gHDMI21SnpsIsrUnitInitiated = -1;

static UINT32 __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_MAXNUM];
static HDMI21_ISRUNIT_SNPS_CTR_REG_T __isrReg[HDMI21_IRQ_SNPS_MAXNUM];

void 	(*pF_HDMI21_ISRUNIT_Rx_Set_ProceedAudioEarcDmacIsr)(UINT32 intStatus) = NULL;
/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
/* Calling Init Function would enable ISR to be activated
 * This Function also sets ISR masks, this means that this would have to be
 * called after a Link Reset*/
void HDMI21_ISRUNIT_Rx_Initiate(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = (HDMI21_HAL_RX_DEVICE_DATA *)pDevHandler;
	HDMI20_DEV_CONTROL_T *_pDevLink = (HDMI20_DEV_CONTROL_T *)&gHDMI21RxDevLinkControler;
	UINT32 __d = 0;
	UINT32 __m = 0;
		
		/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Set Video/Audio Instant Mute Mask : Logical OR to add any...*/
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_HDCP_1].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_HDCP].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_SCDC].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_PKT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_PKT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_PKT_0].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_AVPUNIT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_AVPUNIT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_AVPUNIT_0].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_MAINUNIT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_MAINUNIT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDMUTE_ISRMASK_MAINUNIT_0].value = 0x0;
	
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_HDCP_1].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_HDCP].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_SCDC].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_PKT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_PKT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_PKT_0].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_AVPUNIT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_AVPUNIT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_AVPUNIT_0].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_MAINUNIT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_MAINUNIT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDMUTE_ISRMASK_MAINUNIT_0].value = 0x0;


	/* Set Audio/Video Change Flag attributes on ISR */
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_HDCP_1].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_HDCP].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_SCDC].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_0].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_0].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_0].value = 0x0;

	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_HDCP_1].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_HDCP].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_SCDC].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_0].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_0].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_2].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_1].value = 0x0;
	_pDevLink[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_0].value = 0x0;



	/* Register Each ISR mask/clear/force/status registers */
	__isrReg[HDMI21_IRQ_SNPS_HDCP_1_INTVEC].mask = HDMI21_SNPS_REG_HDCP_1_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_1_INTVEC].clear = HDMI21_SNPS_REG_HDCP_1_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_1_INTVEC].force = HDMI21_SNPS_REG_HDCP_1_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_1_INTVEC].status = HDMI21_SNPS_REG_HDCP_1_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_1_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqHdcp1Unit;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_1_INTVEC].bitfield = HDMI21_SNPS_FIELD_HDCP_1_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_HDCP_INTVEC].mask = HDMI21_SNPS_REG_HDCP_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_INTVEC].clear = HDMI21_SNPS_REG_HDCP_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_INTVEC].force = HDMI21_SNPS_REG_HDCP_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_INTVEC].status = HDMI21_SNPS_REG_HDCP_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqHdcpUnit;
	__isrReg[HDMI21_IRQ_SNPS_HDCP_INTVEC].bitfield = HDMI21_SNPS_FIELD_HDCP_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_SCDC_INTVEC].mask = HDMI21_SNPS_REG_SCDC_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_SCDC_INTVEC].clear = HDMI21_SNPS_REG_SCDC_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_SCDC_INTVEC].force = HDMI21_SNPS_REG_SCDC_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_SCDC_INTVEC].status = HDMI21_SNPS_REG_SCDC_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_SCDC_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqScdcUnit;
	__isrReg[HDMI21_IRQ_SNPS_SCDC_INTVEC].bitfield = HDMI21_SNPS_FIELD_SCDC_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_PKT_2_INTVEC].mask = HDMI21_SNPS_REG_PKT_2_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_PKT_2_INTVEC].clear = HDMI21_SNPS_REG_PKT_2_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_PKT_2_INTVEC].force = HDMI21_SNPS_REG_PKT_2_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_PKT_2_INTVEC].status = HDMI21_SNPS_REG_PKT_2_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_PKT_2_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit2;
	__isrReg[HDMI21_IRQ_SNPS_PKT_2_INTVEC].bitfield = HDMI21_SNPS_FIELD_PKT_2_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_PKT_1_INTVEC].mask = HDMI21_SNPS_REG_PKT_1_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_PKT_1_INTVEC].clear = HDMI21_SNPS_REG_PKT_1_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_PKT_1_INTVEC].force = HDMI21_SNPS_REG_PKT_1_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_PKT_1_INTVEC].status = HDMI21_SNPS_REG_PKT_1_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_PKT_1_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit1;
	__isrReg[HDMI21_IRQ_SNPS_PKT_1_INTVEC].bitfield = HDMI21_SNPS_FIELD_PKT_1_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_PKT_0_INTVEC].mask = HDMI21_SNPS_REG_PKT_0_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_PKT_0_INTVEC].clear = HDMI21_SNPS_REG_PKT_0_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_PKT_0_INTVEC].force = HDMI21_SNPS_REG_PKT_0_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_PKT_0_INTVEC].status = HDMI21_SNPS_REG_PKT_0_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_PKT_0_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit0;
	__isrReg[HDMI21_IRQ_SNPS_PKT_0_INTVEC].bitfield = HDMI21_SNPS_FIELD_PKT_0_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC].mask = HDMI21_SNPS_REG_AVPUNIT_2_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC].clear = HDMI21_SNPS_REG_AVPUNIT_2_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC].force = HDMI21_SNPS_REG_AVPUNIT_2_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC].status = HDMI21_SNPS_REG_AVPUNIT_2_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit2;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC].bitfield = HDMI21_SNPS_FIELD_AVPUNIT_2_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC].mask = HDMI21_SNPS_REG_AVPUNIT_1_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC].clear = HDMI21_SNPS_REG_AVPUNIT_1_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC].force = HDMI21_SNPS_REG_AVPUNIT_1_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC].status = HDMI21_SNPS_REG_AVPUNIT_1_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit1;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC].bitfield = HDMI21_SNPS_FIELD_AVPUNIT_1_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC].mask = HDMI21_SNPS_REG_AVPUNIT_0_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC].clear = HDMI21_SNPS_REG_AVPUNIT_0_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC].force = HDMI21_SNPS_REG_AVPUNIT_0_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC].status = HDMI21_SNPS_REG_AVPUNIT_0_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit0;
	__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC].bitfield = HDMI21_SNPS_FIELD_AVPUNIT_0_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC].mask = HDMI21_SNPS_REG_MAINUNIT_2_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC].clear = HDMI21_SNPS_REG_MAINUNIT_2_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC].force = HDMI21_SNPS_REG_MAINUNIT_2_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC].status = HDMI21_SNPS_REG_MAINUNIT_2_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit2;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC].bitfield = HDMI21_SNPS_FIELD_MAINUNIT_2_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC].mask = HDMI21_SNPS_REG_MAINUNIT_1_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC].clear = HDMI21_SNPS_REG_MAINUNIT_1_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC].force = HDMI21_SNPS_REG_MAINUNIT_1_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC].status = HDMI21_SNPS_REG_MAINUNIT_1_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit1;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC].bitfield = HDMI21_SNPS_FIELD_MAINUNIT_1_INTVEC;

	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC].mask = HDMI21_SNPS_REG_MAINUNIT_0_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC].clear = HDMI21_SNPS_REG_MAINUNIT_0_INT_CLR;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC].force = HDMI21_SNPS_REG_MAINUNIT_0_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC].status = HDMI21_SNPS_REG_MAINUNIT_0_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC].irqFunc = __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit0;
	__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC].bitfield = HDMI21_SNPS_FIELD_MAINUNIT_0_INTVEC;

	/* EARC */
	__isrReg[HDMI21_IRQ_SNPS_EARC_INTVEC].mask 		= HDMI21_SNPS_REG_EARC_INT_MASK_N;
	__isrReg[HDMI21_IRQ_SNPS_EARC_INTVEC].clear 	= HDMI21_SNPS_REG_EARC_INT_CLEAR;
	__isrReg[HDMI21_IRQ_SNPS_EARC_INTVEC].force 	= HDMI21_SNPS_REG_EARC_INT_FORCE;
	__isrReg[HDMI21_IRQ_SNPS_EARC_INTVEC].status 	= HDMI21_SNPS_REG_EARC_INT_STATUS;
	__isrReg[HDMI21_IRQ_SNPS_EARC_INTVEC].irqFunc 	= __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit0;
	__isrReg[HDMI21_IRQ_SNPS_EARC_INTVEC].bitfield 	= 0x0;	/* SNPS MAIN ISR does not have fields for eARC */


	/* Flag for Initiated */
	__gHDMI21SnpsIsrUnitInitiated = 1;

	/* Set Initial Mask Value */
	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_HDCP_1_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_HDCP_1_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_HDCP_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_HDCP_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_SCDC_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_SCDC_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_PKT_2_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_PKT_2_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_PKT_1_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_PKT_1_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_PKT_0_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_PKT_0_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_2_INTVEC].value);

	if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) {
		HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC,\
				gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_T].value);
	}
	else{
		HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC,\
				gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_F].value);
	}

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_0_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_MAINUNIT_2_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_MAINUNIT_1_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_MAINUNIT_0_INTVEC].value);

	HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_EARC_INTVEC,\
			gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_EARC_INTVEC].value);

	/* Set ISR Mask to Enable ISR */
	__HDMI21_ISRUNIT_Rx_Set_IsrMask(_p, HDMI21_IRQ_SNPS_MAXNUM);

	/*====== From E60B0 up.. : SCDC RCV ISR ====== */
	if(lx_chip_rev( ) >= LX_CHIP_REV(E60, B0)) {
		
		HDMI21_LINE_DBG(406, "Info[%d] : Link/Top SCDC ISR mask Set bit[0x%08x] to LOW\n", _p->port, gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value);

		/* #1. Configure Mask Value */
		__d = gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value;
		__d = __d << 16; __d = (~__d);

		/* #2. Read Current Masking status, Mask it with configuration, and Write back */
		__m = _p->top_read(HDMI21_TOP_REG_SCDC_ISR_MASK);
		__m &= (__d); 
		_p->top_write(HDMI21_TOP_REG_SCDC_ISR_MASK, __m);

		/* #3. Set Enable Bit */
		_p->top_write(HDMI21_TOP_REG_SCDC_ISR_ENABLE_CLR ,gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value);
	}
}

char *__isrvec_type_to_str(HDMI21_ISRUNIT_SNPS_TYPE_T type)
{
    switch (type)
	{
		case HDMI21_IRQ_SNPS_HDCP_1_INTVEC:
			return "HDCP_1";
		case HDMI21_IRQ_SNPS_HDCP_INTVEC:
			return "HDCP";
		case HDMI21_IRQ_SNPS_SCDC_INTVEC:
			return "SCDC";
		case HDMI21_IRQ_SNPS_PKT_2_INTVEC:
			return "PKT2";
		case HDMI21_IRQ_SNPS_PKT_1_INTVEC:
			return "PKT1";
		case HDMI21_IRQ_SNPS_PKT_0_INTVEC:
			return "PKT0";
		case HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC:
			return "AVPUnit2";
		case HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC:
			return "AVPUnit1";
		case HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC:
			return "AVPUnit0";
		case HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC:
			return "MainUnit2";
		case HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC:
			return "MainUnit1";
		case HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC:
			return "MainUnit0";
		default:
			return "Unknown";
	}
}

void HDMI21_ISRUNIT_Rx_Set_RegisterEarcDmacIsrCallBack(void (* function)(UINT32 intStatus))
{
	HDMI20_INFO("ISRUNIT : eARC Under/Overflow CallBack function registered as [0x%p]\n", function);

	pF_HDMI21_ISRUNIT_Rx_Set_ProceedAudioEarcDmacIsr = function;
	return;
}

void HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_ISRUNIT_SNPS_TYPE_T type, UINT32 val)
{
	/* Exit on unknown type */
	if(type >= HDMI21_IRQ_SNPS_MAXNUM) return;

	__gHDMI21SnpsIsrMask[type] = val;

	return;
}

UINT32 HDMI21_ISRUNIT_Rx_Get_IsrMaskValue(HDMI21_ISRUNIT_SNPS_TYPE_T type)
{
	UINT32 ret = 0;

	do{
		/* Break on unknown type */
		if(type >= HDMI21_IRQ_SNPS_MAXNUM) break;

		/* Get Mask value */
		ret = __gHDMI21SnpsIsrMask[type];
	} while(0);

	return ret;
}

void HDMI21_ISRUNIT_Rx_Set_ForceIsrSet(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_ISRUNIT_SNPS_TYPE_T type, UINT32 val)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	HDMI20_INFO("ISRUNIT Port[%d] : Force Set ISR[%s] to val[0x%08x]\n", _p->port, __isrvec_type_to_str(type), val);

	/* Break on unknown type */
	if(type >= HDMI21_IRQ_SNPS_MAXNUM) return;

	/* Access block if not initiated */
	if(__gHDMI21SnpsIsrUnitInitiated <= 0) return;

	/* Write Val to IRQ force register */
	_p->link_write(__isrReg[type].force, val);
}

int HDMI21_ISRUNIT_Rx_ProcessIRQ(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	int i;
	UINT32 __data, __temp;

	do{
		/* Null Pointer Defence */
		if(_p == NULL) break;

		/* Access block if not initiated */
		if(__gHDMI21SnpsIsrUnitInitiated <= 0) break;

		/* Read ISR Vector */
		__data = _p->link_read(HDMI21_SNPS_REG_MAINUNIT_INTVEC_INDEX);
		__temp = __data;

		HDMI21_LINE_DBG( 129, "DBG[%d] : Link ISR[0x%08x]\n", _p->port, __temp);

		/* Check each ISR Vector, and Process IRQ if occurred */
		for(i=0;i<HDMI21_IRQ_SNPS_MAXNUM;i++) {
			if((__data & __isrReg[i].bitfield) != 0){
				__temp &= (~__isrReg[i].bitfield);
				__isrReg[i].irqFunc(_p);
			}
		}

		/* To keep Track on Unknown ISR */
		if(__temp != 0) {
			HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
			_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
		}
		else{
			ret = RET_OK;
		}

		/* 2020/06/08 : SCDC ISR for E60B0 and up.. */
		if(lx_chip_rev( ) >= LX_CHIP_REV(E60, B0)) {
			/* Get ISR Status */
			__data  = _p->top_read(HDMI21_TOP_REG_SCDC_ISR_STATUS);

			
			/* Clear & Disable ISR */
			__data &= (HDMI21_TOP_FIELD_SCDC_ISR_STATUS);
			_p->top_write(HDMI21_TOP_REG_SCDC_ISR_ENABLE_CLR, __data);

			HDMI21_LINE_DBG( 133, "DBG[%d] : ISR on TOP/LINK SCDC [0x%08x]\n", _p->port, __temp);

			/* Bit shift Status for comparsion with definitions */
			__data = __data >> 8;
			__temp = __data;

			/* Process each for every ISR bits if HIGH */
			if((__data & HDMI21_TOP_BIT_SCDC_ISR_FRL_RATE_RCV) != 0) {
				_p->isr_count0[HDMI21_ISR_TOPLINK_SCDC_FRL_RATE_RCV]++;
				__temp &= (~HDMI21_TOP_BIT_SCDC_ISR_FRL_RATE_RCV);

				_p->frlRateRcv = true;

				HDMI20_PRINT("ISR[%d] : FRL Rate Receive Detected\n", _p->port);
			}

			if((__data & HDMI21_TOP_BIT_SCDC_ISR_FRL_RATE_SAME) != 0) {
				_p->isr_count0[HDMI21_ISR_TOPLINK_SCDC_FRL_RATE_SAME]++;
				__temp &= (~HDMI21_TOP_BIT_SCDC_ISR_FRL_RATE_SAME);
			}
			if((__data & HDMI21_TOP_BIT_SCDC_ISR_SCRAMBLE_RCV) != 0) {
				_p->isr_count0[HDMI21_ISR_TOPLINK_SCDC_SCRAMBLE_RCV]++;
				__temp &= (~HDMI21_TOP_BIT_SCDC_ISR_SCRAMBLE_RCV);
			}
			if((__data & HDMI21_TOP_BIT_SCDC_ISR_FRL_START_UP) != 0) {
				_p->isr_count0[HDMI21_ISR_TOPLINK_SCDC_FRL_START_UP]++;
				__temp &= (~HDMI21_TOP_BIT_SCDC_ISR_FRL_START_UP);
			}
			if((__data & HDMI21_TOP_BIT_SCDC_ISR_FRL_START_DN) != 0) {
				_p->isr_count0[HDMI21_TOP_BIT_SCDC_ISR_FRL_START_DN]++;
				__temp &= (~HDMI21_TOP_BIT_SCDC_ISR_FRL_START_DN);
			}
			if((__data & HDMI21_TOP_BIT_SCDC_ISR_FRL_UPDATE_UP) != 0) {
				_p->isr_count0[HDMI21_TOP_BIT_SCDC_ISR_FRL_UPDATE_UP]++;
				__temp &= (~HDMI21_TOP_BIT_SCDC_ISR_FRL_UPDATE_UP);
			}
			if((__data & HDMI21_TOP_BIT_SCDC_ISR_FRL_UPDATE_DN) != 0) {
				_p->isr_count0[HDMI21_TOP_BIT_SCDC_ISR_FRL_UPDATE_DN]++;
				__temp &= (~HDMI21_TOP_BIT_SCDC_ISR_FRL_UPDATE_DN);
			}

			if((__temp & gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value) != 0) {
				HDMI20_WARN("WARN [%d] : LINK ISR, top status is not Zero[0x%08x]!\n", _p->port, __temp);
			}


			/* Enable ISR */
			__data |= (HDMI21_TOP_FIELD_SCDC_ISR_ENABLE & gHDMI21RxDevLinkControler[HDMI21__LINK_TOP_SCDC_ISR_MASK].value);

			/* Test Mode for Tek device : Force error=0 on SCDC registers */
			if(gHDMI21RxDevLinkControler[HDMI21__LINK_TEST_SCDC_ERROR_FLAT_ENJECT].value > 0) {
				if(_p->isPhyLocked > 0) {
					__data |= 0x01000000;
				}

				if(gHDMI21RxDevLinkControler[HDMI21__LINK_TEST_SCDC_ERROR_FLAT_ENJECT].value >= 2) {
					__data |= 0x01000000;
				}
			}

			_p->top_write(HDMI21_TOP_REG_SCDC_ISR_ENABLE_CLR, __data);
		}

	} while(0);

	return ret;
}

int HDMI21_ISRUNIT_Rx_ProcessEarcIRQ(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;
	UINT32 __needToCallAudioEarc = 0;

	/* Null Pointer Defence Code */
	if(_p == NULL) return 0;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_EARC_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_EARC_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_EARC_INTVEC];
	__data = __temp;

	if(__temp == 0) return 0;

	HDMI21_LINE_DBG( 120, "DBG[%d] : ISR on EARC  [0x%08x]\n", _p->port, __temp);

	/* Process each ISR */
	if((__data &  HDMI21_SNPS_FIELD_REGBANK_READY_IRQ ) != 0){
		_p->isr_count0[HDMI21_IRQ_LINK_REGBANK_READY_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_REGBANK_READY_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_XACT_DONE_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_XACT_DONE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_XACT_DONE_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_BADPAR_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADPAR_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_BADPAR_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_BADECC_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADECC_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_BADECC_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_INCOMPLETE_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_INCOMPLETE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_INCOMPLETE_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_BADSYNC_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADSYNC_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_BADSYNC_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_BADPREAMBLE_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_RXPKT_BADPREAMBLE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_RXPKT_BADPREAMBLE_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_HEARTBEAT_CAP_CHNG_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_CAP_CHNG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_HEARTBEAT_CAP_CHNG_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_HEARTBEAT_STAT_CHNG_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_STAT_CHNG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_HEARTBEAT_STAT_CHNG_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_HEARTBEAT_LOST_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_HEARTBEAT_LOST_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_HEARTBEAT_LOST_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_DISCOVERY_TIMEOUT_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_DISCOVERY_TIMEOUT_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_DISCOVERY_TIMEOUT_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_CMDC_DISCOVERY_DONE_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_CMDC_DISCOVERY_DONE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_CMDC_DISCOVERY_DONE_IRQ);
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_DMAC_MUTE_REQUEST_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_DMAC_MUTE_REQUEST_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_DMAC_MUTE_REQUEST_IRQ);

		__needToCallAudioEarc = 1;
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_DMAC_AUDIO_FIFO_OVERFLOW_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_DMAC_AUDIO_FIFO_OVERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_DMAC_AUDIO_FIFO_OVERFLOW_IRQ);

		__needToCallAudioEarc = 1;
	}

	if((__data & HDMI21_SNPS_FIELD_EARCTX_DMAC_AUDIO_FIFO_UNDERFLOW_IRQ ) != 0){
		_p->isr_count0[HDMI21_ISR_TOP_EARCTX_DMAC_AUDIO_FIFO_UNDERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_DMAC_AUDIO_FIFO_UNDERFLOW_IRQ);

		__needToCallAudioEarc = 1;
	}

	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 120, "DBG[%d] : Unknown EARC ISR Detected! [0x%08x]\n", _p->port, __temp);
	}

	if(__needToCallAudioEarc  > 0)
	{
		HDMI21_LINE_DBG( 120, "DBG[%d] : Called eARC Audio!\n", _p->port);
		__HDMI21_ISRUNIT_Rx_Set_ProceedAudioEarcDmacIsr(__data);
	}

	return 1;
}


/*========================================================================================
 Static Function Implementation
======================================================================================== */
static void __HDMI21_ISRUNIT_Rx_Set_IsrMask(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_ISRUNIT_SNPS_TYPE_T type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int i = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	if(type >= HDMI21_IRQ_SNPS_MAXNUM) {
		/* Set Each ISR Vector Mask Value */
		for(i=0;i<HDMI21_IRQ_SNPS_MAXNUM;i++) {
			if((_p->port != 0) && (type == HDMI21_IRQ_SNPS_EARC_INTVEC)) {
				/* Do not set EARC INTEV to other ports than 0 */
			}
			else {
				HDMI21_LINE_DBG(406, "Info[%d] : ISR[%s] mask set to [0x%08x]\n", _p->port, __isrvec_type_to_str(i), __gHDMI21SnpsIsrMask[i]);
				_p->link_write(__isrReg[i].mask, __gHDMI21SnpsIsrMask[i]);
			}
		}
	}
	else {
		if((_p->port != 0) && (type == HDMI21_IRQ_SNPS_EARC_INTVEC)) {
			/* Do not set EARC INTEV to other ports than 0 */
		}
		else {
			HDMI21_LINE_DBG(406, "Info[%d] : ISR[%s] mask set to [0x%08x]\n", _p->port, __isrvec_type_to_str(type), __gHDMI21SnpsIsrMask[type]);
			_p->link_write(__isrReg[type].mask, __gHDMI21SnpsIsrMask[type]);
		}
	}

	return;
}


static void __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_MAINUNIT_0_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 130, "DBG[%d] : ISR on MainUnit0  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_0].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_0].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_0].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_0].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	/* Process each ISR */
	if((__data &  HDMI21_SNPS_FIELD_REGBANK_READY_IRQ ) != 0){
		_p->isr_count0[HDMI21_IRQ_LINK_REGBANK_READY_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_REGBANK_READY_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_APB_IF_READY_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_APB_IF_READY_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_APB_IF_READY_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_CDSENSE_CHG_MASK_N ) != 0) {
		_p->isr_count0[HDMI21_IRQ_CDSENSE_CHG_MASK_N]++;
		__temp &= (~HDMI21_SNPS_FIELD_CDSENSE_CHG_MASK_N);
	}

	if((__data &  HDMI21_SNPS_FIELD_TIMER_BASE_LOCKED_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_TIMER_BASE_LOCKED_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_TIMER_BASE_LOCKED_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_EARC_BPCLK_OFF_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_EARC_BPCLK_OFF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARC_BPCLK_OFF_CHG_IRQ);

	}

	if((__data &  HDMI21_SNPS_FIELD_EARC_BPCLK_LOCKED_CHG_IRQ ) != 0){
		_p->isr_count0[HDMI21_IRQ_LINK_EARC_BPCLK_LOCKED_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARC_BPCLK_LOCKED_CHG_IRQ);
	}


	if((__data &  HDMI21_SNPS_FIELD_EARC_AUDCLK_OFF_CHG_IRQ ) != 0){
		_p->isr_count0[HDMI21_IRQ_LINK_EARC_AUDCLK_OFF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARC_AUDCLK_OFF_CHG_IRQ);

	}

	if((__data &  HDMI21_SNPS_FIELD_EARC_AUDCLK_LOCKED_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_EARC_AUDCLK_LOCKED_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARC_AUDCLK_LOCKED_CHG_IRQ);

	}

	if((__data &  HDMI21_SNPS_FIELD_FRLCLK_OFF_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_FRLCLK_OFF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_FRLCLK_OFF_CHG_IRQ);

	}

	if((__data &  HDMI21_SNPS_FIELD_FRLCLK_LOCKED_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_FRLCLK_LOCKED_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_FRLCLK_LOCKED_CHG_IRQ);

	}

	if((__data &  HDMI21_SNPS_FIELD_TMDSQPCLK_OFF_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_TMDSQPCLK_OFF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_TMDSQPCLK_OFF_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_TMDSQPCLK_LOCKED_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_TMDSQPCLK_LOCKED_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_TMDSQPCLK_LOCKED_CHG_IRQ);

	}

	if((__data &  HDMI21_SNPS_FIELD_AUDCLK_OFF_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUDCLK_OFF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUDCLK_OFF_CHG_IRQ);
#if 1		
		if((_p->audio_state == HDMI21__AUDIO_STATE__2__ENABLE__WAIT_CLK_OFF_CHG)\
		&& !(_p->link_read(HDMI21_RX_CMU_STATUS) & HDMI21_RX_CMU_STATUS__AUDCLK_OFF_ST)){

			_p->audio_state = HDMI21__AUDIO_STATE__3__ENABLE__WAIT_FIFO_PASS_IRQ1;
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_INFO("Audio[%d] state %d->%d(audio clock off change, 0x%x)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__2__ENABLE__WAIT_CLK_OFF_CHG, HDMI21__AUDIO_STATE__3__ENABLE__WAIT_FIFO_PASS_IRQ1, _p->link_read(HDMI21_RX_CMU_STATUS));
		}
#endif
	}

	if((__data &  HDMI21_SNPS_FIELD_AUDCLK_LOCKED_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUDCLK_LOCKED_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUDCLK_LOCKED_CHG_IRQ);
	}

	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}

static void __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_MAINUNIT_1_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 130, "DBG[%d] : ISR on MainUnit1  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_1].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_1].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_1].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_1].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}

	if((__data &  HDMI21_SNPS_FIELD_DDC_SCDC_ACTIVITY_IRQ ) != 0) {

		_p->isr_count0[HDMI21_IRQ_LINK_DDC_SCDC_ACTIVITY_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_DDC_SCDC_ACTIVITY_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_DDC_HDCP_ACTIVITY_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_DDC_HDCP_ACTIVITY_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_DDC_HDCP_ACTIVITY_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_EARCTX_POWERED_DOWN_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_EARCTX_POWERED_DOWN_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_POWERED_DOWN_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_EARCTX_POWERED_UP_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_EARCTX_POWERED_UP_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARCTX_POWERED_UP_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_CEC_POWERED_DOWN_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_CEC_POWERED_DOWN_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_CEC_POWERED_DOWN_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_CEC_POWERED_UP_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_CEC_POWERED_UP_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_CEC_POWERED_UP_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AVPUNIT_POWERED_DOWN_IRQ	) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AVPUNIT_POWERED_DOWN_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AVPUNIT_POWERED_DOWN_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AVPUNIT_POWERED_UP_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AVPUNIT_POWERED_UP_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AVPUNIT_POWERED_UP_IRQ);
	}


	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}


}

static void __HDMI21_ISRUNIT_Rx_ProcessIrqMainUnit2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;
	UINT32 __r, __d;
	int i, _isNegative = 0;
	UINT32 _saffMaxValue[HDMI21_HAL_CNT_OF_CHANNEL_IN_ONE_PHY] = {0, };
	int tcs_result[HDMI21_AMOUNT_OF_TMDS_CHANNEL_IN_ONE_PHY] = {0,};
	volatile int __eq_success_sel_delay = gHDMI21RxDevLinkControler[HDMI21__LINK_DELAY_TO_EQ_SUCCESS_SEL].value;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_MAINUNIT_2_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 130, "DBG[%d] : ISR on MainUnit2  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_2].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_2].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_MAINUNIT_2].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_MAINUNIT_2].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_PHYCREG_CR_TIMEOUT_IRQ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PHYCREG_CR_TIMEOUT_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PHYCREG_CR_TIMEOUT_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_PHYCREG_CR_READ_DONE_IRQ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PHYCREG_CR_READ_DONE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PHYCREG_CR_READ_DONE_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_PHYCREG_CR_WRITE_DONE_IRQ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PHYCREG_CR_WRITE_DONE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PHYCREG_CR_WRITE_DONE_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_PHYCREG_CR_SELECTOR_DONE_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PHYCREG_CR_SELECTOR_DONE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PHYCREG_CR_SELECTOR_DONE_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_PHYCREG_CR_SELECTIONMODE_DONE_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PHYCREG_CR_SELECTIONMODE_DONE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PHYCREG_CR_SELECTIONMODE_DONE_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_EARC_BPCLK_VALID_STABLE_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_EARC_BPCLK_VALID_STABLE_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_EARC_BPCLK_VALID_STABLE_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_TMDSVALID_STABLE_CHG_IRQ	 ) != 0) {

		if((HDMI21_PHY_Rx_Get_IsPhyPdbPowerOn(_p->port) >= 0) & (_p->is5Vconnected > 0)){
			__r = 0x2c; __r = (__r << 2);  __d = _p->phyDR_read(__r);

			if((__d & 0x1) != 0x0) {
				HDMI20_INFO("Info[%d] : TCS Done Interrupt\n", _p->port);

				/* Priority #1. From Document, SNPS Core DataPath Reset must be asserted after PHY LOCK */
				HDMI21_HAL_Rx_Set_CoreResetWithMask(_p, gHDMI21RxDevLinkControler[HDMI21__LINK_MISC_RESET_ON_TCS_DONE_VAL].value);

				/* Priority #2. Reset CRG */
				/* 2020/01/08 : Reset INPUT FIFO */
				_p->top_write(0xa00, gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_HIGH_VAL].value);
				_p->top_write(0xa00, gHDMI21RxDevLinkControler[HDMI21__LINK_CRG_FIFO_RESET_LOW_VAL].value);

				/* PHY DFE Center SW WA */
				if((_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L)&&( lx_chip_rev( ) >= LX_CHIP_REV( O20, B0))){

					HDMI21_PHY_Rx_Set_InitiateDfeCenter(_p->port);
				}

				if(( lx_chip_rev( ) >= LX_CHIP_REV( E60, B0)) && (lx_chip( ) != LX_CHIP_M23) ){
					if((_p->phyInitiatedMode == HDMI21_HAL_PHY_INITIATED_3G) && (_p->phyCurrentTMDSExceptionRange == 0)) {

						/* 2020/06/04 : DG.Kim told me to do this */
						HDMI20_INFO("ISR[%d] : DFE SignPath Level 0 reset for HDMI1.4 Mode3 TCS Done\n", _p->port);
						__r = 0x81; __r = (__r << 2);  __d = 0x6F; _p->phyDR_write(__r, __d);
					}

					if(gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_BUG].value == 1) {
						if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
							HDMI21_PHY_Rx_Get_SaffValue(_p->port);

							/* Check if all SAFF offset values are positive values */
							for(i=0; i<HDMI21_HAL_CNT_OF_CHANNEL_IN_ONE_PHY;i++)
							{
								if(gPhySaffOffsetResult[_p->port][i].dep_os >= gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_M1_THR].value) {
									_isNegative++;
									break;
								}
								if(gPhySaffOffsetResult[_p->port][i].den_os >= gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_M1_THR].value) {
									_isNegative++;
									break;
								}
								if(gPhySaffOffsetResult[_p->port][i].dop_os >= gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_M1_THR].value) {
									_isNegative++;
									break;
								}
								if(gPhySaffOffsetResult[_p->port][i].don_os >= gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_M1_THR].value) {
									_isNegative++;
									break;
								}
							}

							if(_isNegative == 0) {
								HDMI20_INFO("ISR[%d] : 2SCOMPLIMENT SWWA M1-6> All DEP/DEN/DOP/DON values are Under[%d]n", _p->port, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_M1_THR].value);
							}
							else {
								HDMI20_INFO("ISR[%d] : 2SCOMPLIMENT SWWA M1-> Atleast on value is Over[%d]n", _p->port, gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_M1_THR].value);
								__r = 0x81; __r = (__r << 2);  __d = 0x1F; _p->phyDR_write(__r, __d);

								/* Get Max Values per channel */
								for(i=0;  i<HDMI21_HAL_CNT_OF_CHANNEL_IN_ONE_PHY;i++)
								{
									_saffMaxValue[i] = gPhySaffOffsetResult[_p->port][i].dep_os;
									if(gPhySaffOffsetResult[_p->port][i].den_os > _saffMaxValue[i]) _saffMaxValue[i] = gPhySaffOffsetResult[_p->port][i].den_os;
									if(gPhySaffOffsetResult[_p->port][i].dop_os > _saffMaxValue[i]) _saffMaxValue[i] = gPhySaffOffsetResult[_p->port][i].dop_os;
									if(gPhySaffOffsetResult[_p->port][i].don_os > _saffMaxValue[i]) _saffMaxValue[i] = gPhySaffOffsetResult[_p->port][i].don_os;

									if(_saffMaxValue[i] >= 0x20) _saffMaxValue[i] = _saffMaxValue[i] - 0x1F;
								}

								/* Write DFE B1 Values for All Channels */
								__r = 0x6E; __r = (__r << 2);  __d = _saffMaxValue[0]; _p->phyDR_write(__r, __d);
								__r = 0x73; __r = (__r << 2);  __d = _saffMaxValue[1]; _p->phyDR_write(__r, __d);
								__r = 0x78; __r = (__r << 2);  __d = _saffMaxValue[2]; _p->phyDR_write(__r, __d);
								__r = 0x7D; __r = (__r << 2);  __d = _saffMaxValue[3]; _p->phyDR_write(__r, __d);
							}

							/* DFE DIG ON */
							__r = 0x58; __r = (__r << 2);  __d = _p->phyDR_read(__r); __d |= 0x1; _p->phyDR_write(__r, __d);

						}
					}
					else if(gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_BUG].value == 2) {
						if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) {
							/* Read TCS Result */
							__r = 0x1c; __r = (__r << 2);  tcs_result[0] = _p->phyDR_read(__r);
							__r = 0x1d; __r = (__r << 2);  tcs_result[1] = _p->phyDR_read(__r);
							__r = 0x1e; __r = (__r << 2);  tcs_result[2] = _p->phyDR_read(__r);
							__r = 0x1f; __r = (__r << 2);  tcs_result[3] = _p->phyDR_read(__r);

							/* Write to manual */
							__r = 0xa2; __r = (__r << 2); _p->phyDR_write(__r, tcs_result[0]);
							__r = 0xa3; __r = (__r << 2); _p->phyDR_write(__r, tcs_result[1]);
							__r = 0xa4; __r = (__r << 2); _p->phyDR_write(__r, tcs_result[2]);
							__r = 0xa5; __r = (__r << 2); _p->phyDR_write(__r, tcs_result[3]);

							/* Set TCS MANUAL MODE */
							__r = 0xa1; __r = (__r << 2); __d = 0x3; _p->phyDR_write(__r, __d);

							/* LE_CAL_MAN_MODE */
							__r = 0xa8; __r = (__r << 2); __d = 0x50; _p->phyDR_write(__r, __d);
							/* CAL_RS_MODE_OFF*/
							__r = 0xDB; __r = (__r << 2); __d = 0x00; _p->phyDR_write(__r, __d);
							/* EQ_CAL_DONE MANUAL = 1 */
							__r = 0x45; __r = (__r << 2); __d = 0x11; _p->phyPDC_write(__r, __d);
							/* EQ_CAL_RESET ON */
							__r = 0xec; __r = (__r << 2); __d = 0x41; _p->phyDR_write(__r, __d);

							/* DFE DIG ON with 0x30 */
							__r = 0x58; __r = (__r << 2); __d = 0x30; _p->phyDR_write(__r, __d);
						}
					}

					if(_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
						
						if(gHDMI21RxDevPhyControler[HDMI21__PHY_EQ_SUCCESS_SEL_VAL].value == 0x7) {
							/* 2020/06/12 : JINWOO CHOI */
							/* EQ Success Sel 8->7 */
							/* EQ Success Sel write to 8 */						
							__r = 0x5a; __r = (__r << 2) + 0x400;  __d = _p->phyDR_read(__r); __d &= (0x0F); 
							__d |= (0x80); _p->phyDR_write(__r, __d);
						
							/* Need some delay */
							for(i=0; i<__eq_success_sel_delay; i++ ) { __asm__ __volatile__("nop"); }
							HDMI20_PHY("ISR[%d] : Set EQ Sucess Sel [8]->[7] (Delay:%d)\n", _p->port, __eq_success_sel_delay);
							
							/* EQ Success Sel Write to 7 */
							__d &= (0x0F); __d |= (0x70); _p->phyDR_write(__r, __d);
						}

						if( lx_chip_rev( ) >= LX_CHIP_REV( E60, B0) && (_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_10G_4L) ){
							if(gHDMI21RxDevPhyControler[HDMI21__PHY_E60_SWWA_2SCOMPLIMENT_BUG].value > 0) {
								/* Do Nothing */
							}
							else {
								if(gHDMI21RxDevPhyControler[HDMI21__PHY_CH0_SSB_CHECK_ON].value > 0 ) {
									_p->phyFrlSwWaState = 2;
								}
								else {
									_p->phyFrlSwWaState = 3;
								}
							}
						}
						else {
							if(gHDMI21RxDevPhyControler[HDMI21__PHY_CH0_SSB_CHECK_ON].value > 0 ) {
								_p->phyFrlSwWaState = 2;
							}
							else {
								_p->phyFrlSwWaState = 3;
							}
						}
					}
				}
			}
		}

		_p->isr_count0[HDMI21_IRQ_LINK_TMDSVALID_STABLE_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_TMDSVALID_STABLE_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AUDPLL_LOCK_STABLE_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUDPLL_LOCK_STABLE_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUDPLL_LOCK_STABLE_CHG_IRQ);
	}

	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}

static void __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_AVPUNIT_0_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 131, "DBG[%d] : ISR on AvpUnit0  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_0].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_0].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_0].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_0].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_CED_DYN_CNT_CH2_IRQ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_CED_DYN_CNT_CH2_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_CED_DYN_CNT_CH2_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_CED_DYN_CNT_CH1_IRQ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_CED_DYN_CNT_CH1_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_CED_DYN_CNT_CH1_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_CED_DYN_CNT_CH0_IRQ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_CED_DYN_CNT_CH0_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_CED_DYN_CNT_CH0_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_DESCRAND_SYNC_SEQ_ERR_IRQ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_DESCRAND_SYNC_SEQ_ERR_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_DESCRAND_SYNC_SEQ_ERR_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_DESCRAND_SYNC_IRQ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_DESCRAND_SYNC_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_DESCRAND_SYNC_IRQ);
	}


	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}

static void __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp, proc_config0;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 131, "DBG[%d] : ISR on AvpUnit1  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_1].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_1].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_1].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_1].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_VMON_VMEAS_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VMON_VMEAS_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VMON_VMEAS_IRQ);

		__HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(_p, __L__);
	}

	if((__data &  HDMI21_SNPS_FIELD_VMON_HMEAS_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VMON_HMEAS_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VMON_HMEAS_IRQ);

		__HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(_p, __L__);
	}

	if((__data &  HDMI21_SNPS_FIELD_AUD_CHSTATUS_SP3_IRQ	) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUD_CHSTATUS_SP3_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUD_CHSTATUS_SP3_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AUD_CHSTATUS_SP2_IRQ	) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUD_CHSTATUS_SP2_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUD_CHSTATUS_SP2_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AUD_CHSTATUS_SP1_IRQ	) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUD_CHSTATUS_SP1_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUD_CHSTATUS_SP1_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AUD_CHSTATUS_SP0_IRQ	) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUD_CHSTATUS_SP0_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUD_CHSTATUS_SP0_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AUD_MUTE_IRQ	) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUD_MUTE_IRQ	]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUD_MUTE_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AFIFO_UNDERFLOW_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AFIFO_UNDERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AFIFO_UNDERFLOW_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AFIFO_OVERFLOW_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AFIFO_OVERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AFIFO_OVERFLOW_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AFIFO_THR_MUTE_LOW_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AFIFO_THR_MUTE_LOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AFIFO_THR_MUTE_LOW_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AFIFO_THR_MUTE_HIGH_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AFIFO_THR_MUTE_HIGH_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AFIFO_THR_MUTE_HIGH_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AFIFO_THR_LOW_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AFIFO_THR_LOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AFIFO_THR_LOW_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AFIFO_THR_HIGH_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AFIFO_THR_HIGH_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AFIFO_THR_HIGH_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_AFIFO_THR_PASS_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AFIFO_THR_PASS_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AFIFO_THR_PASS_IRQ);

		if((_p->audio_state == HDMI21__AUDIO_STATE__3__ENABLE__WAIT_FIFO_PASS_IRQ1) || (!(_p->link_read(HDMI21_RX_CMU_STATUS) & HDMI21_RX_CMU_STATUS__AUDCLK_OFF_ST) && _p->audio_state == HDMI21__AUDIO_STATE__2__ENABLE__WAIT_CLK_OFF_CHG)){

			HDMI21_HAL_Rx_Set_Audio_Configure(_p->port, _p->phyInitiatedMode);
			_p->audio_state = HDMI21__AUDIO_STATE__4__ENABLE__WAIT_FIFO_PASS_IRQ2;
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_INFO("Audio[%d] : HDMI Audio state %d->%d(audio pass th irq1)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__3__ENABLE__WAIT_FIFO_PASS_IRQ1, HDMI21__AUDIO_STATE__4__ENABLE__WAIT_FIFO_PASS_IRQ2);
		}else if(_p->audio_state == HDMI21__AUDIO_STATE__4__ENABLE__WAIT_FIFO_PASS_IRQ2){
			proc_config0 = _p->link_read(HDMI21_RX_PROC_CONFIG0);
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) {
				HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC,\
						gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_T].value);
			}
			else{
				HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC,\
						gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_F].value);
			}
			
			/* Update Mask Value to SNPS Link */
			__HDMI21_ISRUNIT_Rx_Set_IsrMask(_p, HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC);

			_p->audio_state = HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ;
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_INFO("Audio[%d] : HDMI Audio state %d->%d(audio pass th irq2)!!!kkkkkk\n",  _p->port, HDMI21__AUDIO_STATE__4__ENABLE__WAIT_FIFO_PASS_IRQ2, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ);
		}
	}

	if((__data &  HDMI21_SNPS_FIELD_AUD_FMT_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_AUD_FMT_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_AUD_FMT_CHG_IRQ);
#if 0
		if(_p->audio_state == 55){
			if(_p->phyInitiatedMode <= HDMI21_HAL_PHY_INITIATED_6G) {
				HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC,\
						gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_T_A].value);
			}
			else{
				HDMI21_ISRUNIT_Rx_Set_IsrMaskValue(HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC,\
						gHDMI21RxDevLinkControler[HDMI21__LINK_ISRUNIT_ISRVAL_AVPUNIT_1_INTVEC_F_A].value);
			}

			/* Update Mask Value to SNPS Link */
			__HDMI21_ISRUNIT_Rx_Set_IsrMask(_p, HDMI21_IRQ_SNPS_AVPUNIT_1_INTVEC);

			HDMI21_HAL_Rx_Set_AudioEnable(_p->port, 0);
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_INFO("Audio[%d] : HDMI Audio state 5->1(format change)!!!kkkkkk\n", _p->port);
		}
#endif		
	}

	if((__data &  HDMI21_SNPS_FIELD_VPROC_SYNCGEN_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VPROC_SYNCGEN_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VPROC_SYNCGEN_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_VPROC_PP_DIFF_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VPROC_PP_DIFF_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VPROC_PP_DIFF_IRQ);

		__HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(_p, __L__);
	}

	if((__data &  HDMI21_SNPS_FIELD_VPROC_CD_TIMEOUT_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VPROC_CD_TIMEOUT_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VPROC_CD_TIMEOUT_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_VPROC_CD_CHG_IRQ	) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VPROC_CD_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VPROC_CD_CHG_IRQ);

		__HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(_p, __L__);
	}

	if((__data &  HDMI21_SNPS_FIELD_VSTREAM_FIFO_OVERFLOW_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VSTREAM_FIFO_OVERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VSTREAM_FIFO_OVERFLOW_IRQ);
	}	

	if((__data &  HDMI21_SNPS_FIELD_VSTREAM_FIFO_UNDERFLOW_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VSTREAM_FIFO_UNDERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VSTREAM_FIFO_UNDERFLOW_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_VSTREAM_FIFO_ALMOST_FULL_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VSTREAM_FIFO_ALMOST_FULL_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VSTREAM_FIFO_ALMOST_FULL_IRQ);
	}	

	if((__data &  HDMI21_SNPS_FIELD_VSTREAM_FIFO_ALMOST_EMPTY_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_VSTREAM_FIFO_ALMOST_EMPTY_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_VSTREAM_FIFO_ALMOST_EMPTY_IRQ);
	}	

	if((__data &  HDMI21_SNPS_FIELD_DEFRAMER_DVIHDMI_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_DEFRAMER_DVIHDMI_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_DEFRAMER_DVIHDMI_CHG_IRQ);

		__HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(_p, __L__);
	}

	if((__data &  HDMI21_SNPS_FIELD_DEFRAMER_GBDET_ERR_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_DEFRAMER_GBDET_ERR_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_DEFRAMER_GBDET_ERR_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_DEFRAMER_VSYNC_THR_REACHED_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_DEFRAMER_VSYNC_THR_REACHED_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_DEFRAMER_VSYNC_THR_REACHED_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_DEFRAMER_VSYNC_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_DEFRAMER_VSYNC_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_DEFRAMER_VSYNC_IRQ);

		/* Never use this isr. It is just a VSYNC isr */
	}


	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}

static void __HDMI21_ISRUNIT_Rx_ProcessIrqAvpUnit2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_AVPUNIT_2_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 131, "DBG[%d] : ISR on AvpUnit2  [0x%08x]\n", _p->port, __temp);


	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_2].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_2].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_AVPUNIT_2].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_AVPUNIT_2].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_FRL_CED_DYN_ERRCNT_THR_LANE3_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_FRL_CED_DYN_ERRCNT_THR_LANE3_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_FRL_CED_DYN_ERRCNT_THR_LANE3_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_FRL_CED_DYN_ERRCNT_THR_LANE2_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_FRL_CED_DYN_ERRCNT_THR_LANE2_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_FRL_CED_DYN_ERRCNT_THR_LANE2_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_FRL_CED_DYN_ERRCNT_THR_LANE1_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_FRL_CED_DYN_ERRCNT_THR_LANE1_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_FRL_CED_DYN_ERRCNT_THR_LANE1_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_FRL_CED_DYN_ERRCNT_THR_LANE0_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_FRL_CED_DYN_ERRCNT_THR_LANE0_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_FRL_CED_DYN_ERRCNT_THR_LANE0_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_UNPACKER_TYPE_ERR_CNT_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_UNPACKER_TYPE_ERR_CNT_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_UNPACKER_TYPE_ERR_CNT_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_UNPACKER_LENGTH_ERR_CNT_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_UNPACKER_LENGTH_ERR_CNT_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_UNPACKER_LENGTH_ERR_CNT_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_UNPACKER_FIFO_UNDERFLOW_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_UNPACKER_FIFO_UNDERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_UNPACKER_FIFO_UNDERFLOW_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_UNPACKER_FIFO_OVERFLOW_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_UNPACKER_FIFO_OVERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_UNPACKER_FIFO_OVERFLOW_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_FRL_DESCRAMB_SYNC_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_FRL_DESCRAMB_SYNC_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_FRL_DESCRAMB_SYNC_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_MARKER_SB_SIZE_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_MARKER_SB_SIZE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_MARKER_SB_SIZE_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_MARKER_SB_COUNT_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_MARKER_SB_COUNT_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_MARKER_SB_COUNT_IRQ);
	}


	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}

static void __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit0(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_PKT_0_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_PKT_0_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_PKT_0_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 132, "DBG[%d] : ISR on PktUnit0  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_0].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_0].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_0].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_0].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_VTEM_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_VTEM_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_VTEM_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Get_PktDataVTEM(_p);

		/* Check VRR */
		HDMI21_HAL_Rx_Get_UpdateVrrMode(_p, (UINT8 *)&_p->emp_vtemPacket);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_CVTEM_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_CVTEM_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_CVTEM_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Get_PktDataCVTEM(_p);

		/* Store to PPS data structure */
		/* 2025/05/07 won.hur -> Do not call this within an interrupt routine. It already exist inside the main thread!*/
		//HDMI21_HAL_Rx_Get_UpdateDscCvtemPpsData(_p);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_EMD_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_EMD_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_EMD_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__EMD);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_GENPKT1_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_GENPKT1_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_GENPKT1_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__GEN1);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_GENPKT0_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_GENPKT0_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_GENPKT0_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__GEN0);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_DRMIF_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_DRMIF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_DRMIF_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__DRM);

		/* SJ Youm */
		HDMI21_DISLAND_Rx_Set_CscHdrInfoToVSC(_p->port);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_NTSCVBIIF_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_NTSCVBIIF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_NTSCVBIIF_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__NTSCVBI);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_AUDIF_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_AUDIF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_AUDIF_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__AIF);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_SRCPDIF_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_SRCPDIF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_SRCPDIF_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__SPD);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_AVIIF_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_AVIIF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_AVIIF_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__AVI);

		/* Check Video changes, because AVI holds CSC/Pixel Repetition*/
		if(gHDMI21RxDevVideoControler[HDMI21__CHECK_VIDEO_CHG_ON_AVI_ISR].value > 0) {	
			__HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(_p, __L__);
		}
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_VSIF_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_VSIF_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_VSIF_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__VSI);

		if((_p->dataPacket[HDMI21_DISLAND_DATA__VSI][4] == HDMI21_RX_VSI_TYPE_HF_OUI_0) \
				&& (_p->dataPacket[HDMI21_DISLAND_DATA__VSI][5] == HDMI21_RX_VSI_TYPE_HF_OUI_1) \
				&& (_p->dataPacket[HDMI21_DISLAND_DATA__VSI][6] == HDMI21_RX_VSI_TYPE_HF_OUI_2)) 
		{
			/* Check for ALLM Mode */
			HDMI21_HAL_Rx_Get_UpdateAllmMode(_p, (__UINT8 *)&_p->dataPacket[HDMI21_DISLAND_DATA__HFVSI]);
		}
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_AMD_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_AMD_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_AMD_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__AMD);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_GMD_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_GMD_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_GMD_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__GAMUT);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ISRC2_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ISRC2_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ISRC2_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ISRC2);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ISRC1_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ISRC1_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ISRC1_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ISRC1);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ACP_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ACP_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ACP_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ACP);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_GCP_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_GCP_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_GCP_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__GCP);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ACR_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ACR_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ACR_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ACR);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ACP_TIMEOUT_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ACP_TIMEOUT_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ACP_TIMEOUT_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ACR_N_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ACR_N_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ACR_N_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ACR);
		if(_p->audio_state == HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ\
		|| _p->audio_state == HDMI21__AUDIO_STATE__0__DEFAULT)
		{
			HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, HDMI21_AUDIO_MUTE);
			HDMI21_HAL_Rx_Set_AudioEnable(_p->port, 0);
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_INFO("Audio[%d] state %d->%d(acr n change)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__5__ENABLE__CHANGE_IRQ, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV);
		}
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ACR_CTS_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ACR_CTS_CHG_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ACR);
	}


	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}

static void __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit1(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_PKT_1_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_PKT_1_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_PKT_1_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 132, "DBG[%d] : ISR on PktUnit1  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_1].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_1].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_1].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_1].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_PKTFIFO_NEW_ENTRY_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTFIFO_NEW_ENTRY_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTFIFO_NEW_ENTRY_IRQ);

		/* Store Data */
		if( HDMI21_PFIFO_Rx_Get_FifoData(_p)  != RET_OK) {
			HDMI20_WARN("WARN[%d] : Return Error from GetPFifoData\n", _p->port);
		}

		if((_p->dataPacket[HDMI21_DISLAND_DATA__VSI][4] == HDMI21_RX_VSI_TYPE_HF_OUI_0) \
				&& (_p->dataPacket[HDMI21_DISLAND_DATA__VSI][5] == HDMI21_RX_VSI_TYPE_HF_OUI_1) \
				&& (_p->dataPacket[HDMI21_DISLAND_DATA__VSI][6] == HDMI21_RX_VSI_TYPE_HF_OUI_2)) 
		{
			/* Check ALLM */
			HDMI21_HAL_Rx_Get_UpdateAllmMode(_p, (__UINT8 *)&_p->dataPacket[HDMI21_DISLAND_DATA__HFVSI]);
		}
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTFIFO_OVERFLOW_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTFIFO_OVERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTFIFO_OVERFLOW_IRQ);

		/* Reset Packet FIFO */
		HDMI21_PFIFO_Rx_Set_ResetPktFifo(_p);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTFIFO_UNDERFLOW_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTFIFO_UNDERFLOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTFIFO_UNDERFLOW_IRQ);

		/* Reset Packet FIFO */
		HDMI21_PFIFO_Rx_Set_ResetPktFifo(_p);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTFIFO_THR_HIGH_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTFIFO_THR_HIGH_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTFIFO_THR_HIGH_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTFIFO_THR_PASS_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTFIFO_THR_PASS_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTFIFO_THR_PASS_IRQ);

		/* 2025/06/17 won.hur : From SNPS document. Only call Get_FifoData when PKTFIFO_THR_PASS_IRQ was called without PKFIFO_NEW_ENTRY_IRQ */
		if((__data &  HDMI21_SNPS_FIELD_PKTFIFO_NEW_ENTRY_IRQ	 ) == 0) {
			/* Store Data */
			if( HDMI21_PFIFO_Rx_Get_FifoData(_p)  != RET_OK) {
				HDMI20_WARN("WARN[%d] : Return Error from GetPFifoData\n", _p->port);
			}

			if((_p->dataPacket[HDMI21_DISLAND_DATA__VSI][4] == HDMI21_RX_VSI_TYPE_HF_OUI_0) \
					&& (_p->dataPacket[HDMI21_DISLAND_DATA__VSI][5] == HDMI21_RX_VSI_TYPE_HF_OUI_1) \
					&& (_p->dataPacket[HDMI21_DISLAND_DATA__VSI][6] == HDMI21_RX_VSI_TYPE_HF_OUI_2)) 
			{
				/* Check ALLM */
				HDMI21_HAL_Rx_Get_UpdateAllmMode(_p, (__UINT8 *)&_p->dataPacket[HDMI21_DISLAND_DATA__HFVSI]);
			}
		}

	}

	if((__data &  HDMI21_SNPS_FIELD_PKTFIFO_THR_LOW_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTFIFO_THR_LOW_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTFIFO_THR_LOW_IRQ);
	}


	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}


static void __HDMI21_ISRUNIT_Rx_ProcessIrqPktUnit2(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_PKT_2_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_PKT_2_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_PKT_2_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 142, "DBG[%d] : ISR on PktUnit2  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_2].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0) {
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_2].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_PKT_2].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_PKT_2].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_VTEM_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_VTEM_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_VTEM_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Get_PktDataVTEM(_p);

		/* Check VRR */
		HDMI21_HAL_Rx_Get_UpdateVrrMode(_p, (UINT8 *)&_p->emp_vtemPacket);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_CVTEM_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_CVTEM_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_CVTEM_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Get_PktDataCVTEM(_p);

		/* Store to PPS data structure */
		/* 2025/05/07 won.hur -> Do not call this within an interrupt routine. It already exist inside the main thread!*/
		//HDMI21_HAL_Rx_Get_UpdateDscCvtemPpsData(_p);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_EMD_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_EMD_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_EMD_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__EMD);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_GENPKT1_RCV_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_GENPKT1_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_GENPKT1_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__GEN1);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_GENPKT0_RCV_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_GENPKT0_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_GENPKT0_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__GEN0);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_DRMIF_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_DRMIF_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_DRMIF_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__DRM);

		/* SJ Youm */
		HDMI21_DISLAND_Rx_Set_CscHdrInfoToVSC(_p->port);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_NTSCVBIIF_RCV_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_NTSCVBIIF_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_NTSCVBIIF_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__NTSCVBI);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_AUDIF_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_AUDIF_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_AUDIF_RCV_IRQ);

		if(_p->audio_state == HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV){
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_INFO("Audio[%d] state %d->%d(audif rcv audio enable)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV, HDMI21__AUDIO_STATE__2__ENABLE__WAIT_CLK_OFF_CHG);
			HDMI21_HAL_Rx_Set_AudioEnable(_p->port, 1);
		}

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__AIF);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_SRCPDIF_RCV_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_SRCPDIF_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_SRCPDIF_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__SPD);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_AVIIF_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_AVIIF_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_AVIIF_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__AVI);

		/* Check Video changes, because AVI holds CSC/Pixel Repetition*/
		if(gHDMI21RxDevVideoControler[HDMI21__CHECK_VIDEO_CHG_ON_AVI_ISR].value > 0) {	
			__HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(_p, __L__);
		}
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_VSIF_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_VSIF_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_VSIF_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__VSI);

		if((_p->dataPacket[HDMI21_DISLAND_DATA__VSI][4] == HDMI21_RX_VSI_TYPE_HF_OUI_0) \
				&& (_p->dataPacket[HDMI21_DISLAND_DATA__VSI][5] == HDMI21_RX_VSI_TYPE_HF_OUI_1) \
				&& (_p->dataPacket[HDMI21_DISLAND_DATA__VSI][6] == HDMI21_RX_VSI_TYPE_HF_OUI_2)) 
		{
			/* Check for ALLM Mode */
			HDMI21_HAL_Rx_Get_UpdateAllmMode(_p, (__UINT8 *)&_p->dataPacket[HDMI21_DISLAND_DATA__HFVSI]);
		}
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_AMD_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_AMD_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_AMD_RCV_IRQ);
		if(_p->audio_state == HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV){
			if(gHDMI21RxDevAudioControler[HDMI21__AUDIO_STATE].value != 0)HDMI20_INFO("Audio[%d] state %d->%d(amd rcv audio enable)!!!kkkkkk\n", _p->port, HDMI21__AUDIO_STATE__1__DISABLE__WAIT_AUDIF_RCV, HDMI21__AUDIO_STATE__2__ENABLE__WAIT_CLK_OFF_CHG);
			HDMI21_HAL_Rx_Set_AudioEnable(_p->port, 1);
		}
		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__AMD);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_GMD_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_GMD_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_GMD_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__GAMUT);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ISRC2_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ISRC2_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ISRC2_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ISRC2);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ISRC1_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ISRC1_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ISRC1_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ISRC1);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ACP_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ACP_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ACP_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ACP);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_GCP_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_GCP_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_GCP_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__GCP);
	}

	if((__data &  HDMI21_SNPS_FIELD_PKTDEC_ACR_RCV_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_PKTDEC_ACR_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_PKTDEC_ACR_RCV_IRQ);

		/* Store Packet */
		HDMI21_PDEC_Rx_Set_StorePktToHander(_p, HDMI21_DISLAND_DATA__ACR);
	}

	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}



static void __HDMI21_ISRUNIT_Rx_ProcessIrqScdcUnit(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_SCDC_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_SCDC_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_SCDC_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 133, "DBG[%d] : ISR on ScdcUnit  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_SCDC].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0){
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_SCDC].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_SCDC].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_SCDC].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_FRL_START_TIMEOUT_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_FRL_START_TIMEOUT_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_FRL_START_TIMEOUT_IRQ);

		HDMI20_PRINT("ISR[%d] : SCDC FRL start timeout detected \n", _p->port);
		HDMI21_SCDC_Rx_Set_FrlStartManualOn(_p);
	}

	if((__data &  HDMI21_SNPS_FIELD_SCDCTMDSCCFG_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_SCDCTMDSCCFG_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_SCDCTMDSCCFG_CHG_IRQ);

		HDMI20_PRINT("ISR[%d] : SCDC TMDS Config Change Detected\n", _p->port);
	}

	if((__data &  HDMI21_SNPS_FIELD_SCDCSCSTATUS_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_SCDCSCSTATUS_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_SCDCSCSTATUS_CHG_IRQ);

		/* This interrupt shows up too many times.. Best to not turn this on */
		HDMI21_LINE_DBG(4425, "ISR[%d] : SCDC Field Status Change Detected\n", _p->port);

	}

	if((__data &  HDMI21_SNPS_FIELD_SCDCCFG_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_SCDCCFG_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_SCDCCFG_CHG_IRQ);

		_p->frlRateRcv = true;

		HDMI20_PRINT("ISR[%d] : SCDC Config Change Detected\n", _p->port);
	}

	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}

static void __HDMI21_ISRUNIT_Rx_ProcessIrqHdcpUnit(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;
/*	UINT32 __rf, __r10, __r11, __r12,  __r18, __r19, __r1a, __r1b;
	UINT32 __df, __d10, __d11, __d12,  __d18, __d19, __d1a, __d1b; */

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_HDCP_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_HDCP_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_HDCP_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 134, "DBG[%d] : ISR on HdcpUnit  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_HDCP].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0){
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_HDCP].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_HDCP].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_HDCP].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_NOT_CAPABLE_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_NOT_CAPABLE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_NOT_CAPABLE_IRQ);
		HDMI20_INFO("ISR[%d] : HDCP2.2 Not Capable\n", _p->port);

		/* Set Handler Data */
		_p->isHDCP22 = false;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_CAPABLE_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_CAPABLE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_CAPABLE_IRQ);
		HDMI20_INFO("ISR[%d] : HDCP2.2 Capable\n", _p->port);
	
		/* Set Handler Data */
		_p->isHDCP22 = true;
		_p->isHDCP14 = false;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_DECRYPTED_CHG_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_DECRYPTED_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_DECRYPTED_CHG_IRQ);

		HDMI20_INFO("ISR[%d] : HDCP2.2 Decrypted Change\n", _p->port );
	
		/* For Low Power */
		_p->idleTick = 0;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_AUTHENTICATION_FAIL_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_AUTHENTICATION_FAIL_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_AUTHENTICATION_FAIL_IRQ);

		HDMI20_INFO("ISR[%d] : HDCP2.2 Authenticate Fail\n", _p->port);

		/* For Low Power */
		_p->idleTick = 0;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_AUTHENTICATED_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_AUTHENTICATED_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_AUTHENTICATED_IRQ);

		HDMI20_INFO("ISR[%d] : HDCP2.2 Authenticate Success\n", _p->port);

		/* Set Handler Data */
		_p->isHDCP22 = true;
		_p->isHDCP14 = false;

		/* For Low Power */
		_p->idleTick = 0;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_AUTHENTICATION_LOST_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_AUTHENTICATION_LOST_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_AUTHENTICATION_LOST_IRQ);

		HDMI20_INFO("ISR[%d] : HDCP2.2 Authenticate Lost\n", _p->port);

		if(gHDMI21RxDevLinkControler[HDMI21__LINK_DATAPATH_ONLY_RST_ON_REAUTH].value > 0) {
			HDMI21_HAL_Rx_Set_CoreResetWithMask(_p, HDMI21_SNPS_RST_DATAPATHONLY);
		}

		/* For Low Power */
		_p->idleTick = 0;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP_DKSET_DONE_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP_DKSET_DONE_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP_DKSET_DONE_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP14_OESS_EESS_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_OESS_EESS_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_OESS_EESS_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP14_ENCDIS_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_ENCDIS_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_ENCDIS_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP14_ENCEN_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_ENCEN_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_ENCEN_IRQ);

		/* Set Handler Data */
		_p->isHDCP22 = false;
		_p->isHDCP14 = true;
	}


	if((__data &  HDMI21_SNPS_FIELD_HDCP14_BSTATUS_READ_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_BSTATUS_READ_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_BSTATUS_READ_IRQ);
	
		/* Set Handler Data */
		#if 0 // 2021/10/25 : SKY-Q with Host Diagnosis Bug
		_p->isHDCP22 = false;
		_p->isHDCP14 = true;
		#endif
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP14_BCAPS_READ_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_BCAPS_READ_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_BCAPS_READ_IRQ);

		HDMI20_INFO("ISR[%d] : HDCP1.4 BCAPS read detected\n", _p->port);

		/* Set Handler Data */
		#if 0 // 2021/10/25 : SKY-Q with Host Diagnosis Bug
		_p->isHDCP22 = false;
		_p->isHDCP14 = true;
		#endif 

		/* For Low Power */
		_p->idleTick = 0;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP14_AKSV_RCV_IRQ		 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_AKSV_RCV_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_AKSV_RCV_IRQ);

		HDMI20_INFO("ISR[%d] : HDCP1.4 AKSV write detected\n", _p->port);
	
		/* Set Handler Data */
		_p->isHDCP22 = false;
		_p->isHDCP14 = true;

		/* For Low Power */
		_p->idleTick = 0;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP14_RI_READ_IRQ		 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_RI_READ_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_RI_READ_IRQ);

		/* Set Handler Data */
		_p->isHDCP22 = false;
		_p->isHDCP14 = true;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP14_BKSV_READ_IRQ		 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_BKSV_READ_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_BKSV_READ_IRQ);

		HDMI20_INFO("ISR[%d] : HDCP1.4 BKSV read detected\n", _p->port);

		/* Set Handler Data */
		#if 0 // 2021/10/25 : SKY-Q with Host Diagnosis Bug
		_p->isHDCP22 = false;
		_p->isHDCP14 = true;
		#endif

		/* For Low Power */
		_p->idleTick = 0;
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP14_AUTH_IRQ	 ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP14_AUTH_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP14_AUTH_IRQ);


		HDMI20_INFO("ISR[%d] : HDCP1.4 Authenticate Success\n", _p->port);

		/* Set Handler Data */
		_p->isHDCP22 = false;
		_p->isHDCP14 = true;

		/* For Low Power */
		_p->idleTick = 0;
	}


	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}


static void __HDMI21_ISRUNIT_Rx_ProcessIrqHdcp1Unit(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __temp;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Get ISR Status */
	__data = _p->link_read(__isrReg[HDMI21_IRQ_SNPS_HDCP_1_INTVEC].status);

	/* Clear ISR */
	_p->link_write(__isrReg[HDMI21_IRQ_SNPS_HDCP_1_INTVEC].clear, __data);

	__temp = __data & __gHDMI21SnpsIsrMask[HDMI21_IRQ_SNPS_HDCP_1_INTVEC];
	__data = __temp;

	HDMI21_LINE_DBG( 134, "DBG[%d] : ISR on Hdcp 1 Unit  [0x%08x]\n", _p->port, __temp);

	/* Set Instant Video Mute */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_HDCP_1].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Video Mute\n", _p->port);
		if(HDMI21_HAL_Rx_Get_IsLocalMuteOn(_p->port) == 0){
			HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);
		}
	}
	/* Set Instant Audio Mute */
		if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_HDCP_1].value) != 0) {
		HDMI21_LINE_DBG(386, "DBG[%d] : ISR Instant Audio Mute\n", _p->port);
		HDMI21_HAL_Rx_Set_AudioMuteControl(_p->port, 1);
	}
	/* Set Video Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_VIDCHANGE_ISRMASK_HDCP_1].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR Video Change trigger\n", _p->port);
		_p->video_change = 1;
	}
	/* Set Audio Change Mask */
	if( (__data & gHDMI21RxDevLinkControler[HDMI21__LINK_AUDCHANGE_ISRMASK_HDCP_1].value) != 0) {
		HDMI21_LINE_DBG(387, "DBG[%d] : ISR audio Change trigger\n", _p->port);
		_p->audio_change = 1;
	}


	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_15_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_15_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_15_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_14_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_14_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_14_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_13_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_13_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_13_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_12_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_12_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_12_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_11_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_11_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_11_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_10_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_10_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_10_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_9_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_9_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_9_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_8_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_8_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_8_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_7_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_7_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_7_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_6_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_6_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_6_CHG_IRQ);
	}

	if((__data &  HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_5_CHG_IRQ ) != 0) {
		_p->isr_count0[HDMI21_IRQ_LINK_HDCP2_ESM_P0_GPIO_OUT_5_CHG_IRQ]++;
		__temp &= (~HDMI21_SNPS_FIELD_HDCP2_ESM_P0_GPIO_OUT_5_CHG_IRQ);
	}

	if(__temp != 0) {
		/* To keep Track on Unknown ISR */
		HDMI21_LINE_DBG( 216, "DBG[%d] : Unknown ISR Detected! [0x%08x]\n", _p->port, __temp);
		_p->isr_count0[HDMI21_ISR_LINK_UNKNOWN]++;
	}

}


static void __HDMI21_ISRUNIT_Rx_Get_CheckChangeHwVideoInfo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int line)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __reg  = 0;
	UINT32 __data = 0;

	/* Null Pointer Defence Code */
	if(_p == NULL) return;

	/* Don't check this on VRR */
	if(_p->isFreeSyncMode > 0) return; 

	/* Trigger Video Change when Change is over tolerence */
	if(HDMI21_HAL_Rx_Get_IsVideoSyncChanged(_p, &_p->hwVideo) > 0) {

		HDMI21_LINE_DBG(1587, "ISR[%d] : Changed Detected. Check for difference.Caller[%pS][%d]\n", _p->port, __builtin_return_address(0), line);
		/* Local Mute when it is not muted */
		HDMI21_HAL_Rx_Set_LocalVideoMute(_p->port, 1, 1);

		/* Notify Main Thread */
		if(_p->stable_cnt >= gHDMI21RxDevVideoControler[HDMI21__STABLE_CHECK_CNT].value) {
			_p->video_change = true;

			if (_p->phyInitiatedMode >= HDMI21_HAL_PHY_INITIATED_FRL_3G_3L) {
				if(gHDMI21RxDevVideoControler[HDMI21__FLT_RESTART_ON_CHG].value > 0) {
					__reg = 0x66; __reg = (__reg << 2) + 0x400;  __data = _p->phyDR_read(__reg);
					__data |= ( 0x80); _p->phyDR_write(__reg, __data);

					HDMI20_INFO("ISR[%d] : Send FRL Restart request to Source Dev\n", _p->port);
					__data &= (~0x80); _p->phyDR_write(__reg, __data);
				}
			}
		}

		_p->stable_cnt = 0;
		_p->stablehdcp14time = 0;
	}

	return;
}


static void __HDMI21_ISRUNIT_Rx_Set_ProceedAudioEarcDmacIsr(UINT32 intStatus)
{
	if(pF_HDMI21_ISRUNIT_Rx_Set_ProceedAudioEarcDmacIsr != NULL) {
		HDMI21_LINE_DBG(120, "ISRUNIT : Audio Function Pointer[0x%p] called!\n", pF_HDMI21_ISRUNIT_Rx_Set_ProceedAudioEarcDmacIsr);
		pF_HDMI21_ISRUNIT_Rx_Set_ProceedAudioEarcDmacIsr(intStatus);
	}
	else{
		HDMI21_LINE_DBG(120, "ISRUNIT : Audio Function Pointer not set!\n");
		/* Do nothing */
	}

	return;
}

EXPORT_SYMBOL (HDMI21_ISRUNIT_Rx_Set_RegisterEarcDmacIsrCallBack);
