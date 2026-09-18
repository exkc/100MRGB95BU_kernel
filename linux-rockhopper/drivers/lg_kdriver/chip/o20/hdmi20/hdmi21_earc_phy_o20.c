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
 *  @author		taejun.lee	
 *  @version	1.0 
 *  @date		2019-05-13
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */

#include "hdmi21_earc_phy_o20.h"
#include "hdmi21_cfg_o20.h"
#include "../../../core/hdmi20/hdmi21_engine/hdmi21_hal_driver.h"
#include "../../../core/hdmi20/hdmi21_engine/hdmi21_earc_driver.h"
#include "hdmi20_drv.h"

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

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern UINT32 HDMI21_EARC_I2cApbRead(UINT32 addr);
extern void   HDMI21_EARC_I2cApbWrite(UINT32 addr, UINT32 data);

static void __attribute__((unused)) __PHY_EARC_Reg_O20A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData);
static void __attribute__((unused)) __PHY_EARC_Reg_O20A0_WrFL(UINT8 port, UINT32 reg, UINT32 data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI21_HAL_RX_DEVICE_DATA gHDMI21RxHandler[HDMI21_NUM_OF_RX_PORTS];
extern HDMI20_DEV_CONTROL_T	gHDMI21EARCDevControler;
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
HDMI21_EARC_PHY_REG_CTRL_O20A0_T 	phyEARC_Reg_o20a0;

/*----------------------------------------------------------------------------------------
    Implementation
----------------------------------------------------------------------------------------*/
int HDMI21_PHY_EARC_O20A0_InitiatePhySystemCtrl(void)
{
	int ret = RET_ERROR;

	do{
		HDMI20_PHY("[%s] Entered\n", __F__);

		/* Mem allocate Phy Block #0 SHDW space */
		if((phyEARC_Reg_o20a0.shdw.addr == NULL)){
			phyEARC_Reg_o20a0.shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_EARC_PHY_REG_CTRL_O20A0_T));

		}
		else {
			OS_Free((void *)phyEARC_Reg_o20a0.shdw.addr);
			phyEARC_Reg_o20a0.shdw.addr = (UINT32 *)OS_KMalloc((size_t)sizeof(HDMI21_EARC_PHY_REG_CTRL_O20A0_T));
		}
		
		ret = RET_OK;
	} while(0);

	return ret;
}

/* IOCTL */
int HDMI21_PHY_EARC_O20A0_Rx_AccessPhy(LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size)
{
	int ret = RET_ERROR;

	LX_HDMI20_PHY_ACCESS_T data;

	do{
		if(pPhyCtrl == NULL){
			HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
			break;
		}

		if(size != sizeof(LX_HDMI20_PHY_ACCESS_T) ){
			HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI20_PHY_ACCESS_T) , size);
			break;
		}

		memset((void *)&data, 0, sizeof(LX_HDMI20_PHY_ACCESS_T));

		if( copy_from_user(&data, (void __user *)pPhyCtrl, sizeof(LX_HDMI20_PHY_ACCESS_T))){
			HDMI20_ERROR("Cannot copy HDMI20 phy data structure from user\n");
			break;
		}

		if(data.isWrite){
		//	gHDMI21RxHandler[port].phyPDC_write( (data.regAddr << 2), data.data);
		}
		else{
			//data.data = gHDMI21RxHandler[port].phyPDC_read( (data.regAddr << 2));
		}

		ret = copy_to_user((LX_HDMI20_PHY_ACCESS_T *)pPhyCtrl, (void *)&data, sizeof(LX_HDMI20_PHY_ACCESS_T));
		if(ret) {
			HDMI20_ERROR("Copy Error to USER space for [%s] data.\n", "PHY" );
			break;
		}


		ret = RET_OK;
	} while(0);

	return ret;
}


static void __attribute__((unused)) __PHY_EARC_Reg_O20A0_RdFL(UINT8 port, UINT32 reg, UINT32 *pData)
{
	UINT32 apb_addr;
	if(pData == NULL) return;

	apb_addr = reg << 2;

	*pData = HDMI21_EARC_I2cApbRead(apb_addr);	

	return;
}

static void __attribute__((unused)) __PHY_EARC_Reg_O20A0_WrFL(UINT8 port, UINT32 reg, UINT32 data)
{
	UINT32 apb_addr;
	
	apb_addr = reg << 2;

	HDMI21_EARC_I2cApbWrite(apb_addr, data);	
	return;
}
