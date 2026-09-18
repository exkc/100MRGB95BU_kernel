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
#include "hdmi21_rx_snps_hdcp.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMI21_HDCP_KEY_WR_TRIES		(50)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];

extern HDMI21_THREAD_CONTROLLER_T gHDMI21Thread;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
void HDMI21_HDCP_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __reg;


	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Set Data */
	__data = _p->link_read(HDMI21_SNPS_REG_HDCP14_CONFIG);

	/* HDCP1.4 Path Delay */
	if(gHDMI21RxDevLinkControler[HDMI21__LINK_HDCP_HDCP14DELAY_VAL].value > 3) {
		__reg = 3;	
	}
	else {
		__reg = gHDMI21RxDevLinkControler[HDMI21__LINK_HDCP_HDCP14DELAY_VAL].value;
	}
	__data &= (~HDMI21_SNPS_FIELD_HDCP14_DELAY_QST);
	__data = __data | (__reg <<30);

	/* Repeater Configuration will be done when key is being written */

	/* HDMI Reserved */
	__data |= (HDMI21_SNPS_FIELD_HDMI_RSVD_QST);

	/* Fast Reauth */
	__data |= (HDMI21_SNPS_FIELD_FASTREAUTH_QST);

	/* 1.1 Feature */
	__data &= (~HDMI21_SNPS_FIELD_FEATURES_1DOT1_QST);

	/* Fast I2C */
	__data &=(~HDMI21_SNPS_FIELD_FASTI2C_QST);
	
	/* Leave the rest to default settings */
	_p->link_write(HDMI21_SNPS_REG_HDCP14_CONFIG, __data);

	return;
}

int  HDMI21_HDCP_Rx_Get_IsCurrentHDCP14(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;
	UINT32 __hdcp14Reg = 0;
	UINT32 __hdcp22Reg = 0;

	/* Get Current Mode */
	do{
		/* Defence Code */
		if(!_p->initiated) {
			HDMI20_ERROR("[%s:%d] Error! HDMI21 device Handler not initiated!\n", __F__, __L__);
			break;
		}

		/* DBG */
		if(gHDMI21RxDevVideoControler[HDMI21__VIDEO_LINE_DEBUGGER].value == 136) {
			ret = 1;
			break;
		}


		/* 2021/01/29 : If Phy is not locked, return no HDCP */
		if(_p->isPhyLocked == 0) {
			break;
		}

		/* Read HDCP2/HDCP1.4 Reg */
		__hdcp22Reg = _p->link_read(HDMI21_SNPS_REG_HDCP2_STATUS);
		__hdcp14Reg = _p->link_read(HDMI21_SNPS_REG_HDCP14_STATUS);

		/* If HDCP2.2 Decrypt Status is valid, it means it is not HDCP1.4 */
		if((__hdcp22Reg & HDMI21_SNPS_FIELD_HDCP2_DECRYPTED) != 0) {
			break;
		}

		/* If HDCP1.4 Decrypt Status is Zero, we don't know for sure wheather this is HDCP1.4 */
		if((__hdcp14Reg & HDMI21_SNPS_FIELD_HDCP14_AUTH_ST) == 0) {
			break;	
		}

		/* 2021/01/29 : Since SNPS HDCP1.4 cannot be reseted with LINK-Reset sequence, we need to observe DECYPRT_ON(ENC_EN) */
		if((__hdcp14Reg & HDMI21_SNPS_FIELD_HDCP14_DECRYPT_ON) == 0) {
			break;
		}
	
		/* If you've got this far.. it should be HDCP1.4 */
		ret = 1;

	} while(0);

	return ret;
}

int  HDMI21_HDCP_Rx_Get_IsCurrentHDCP23(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;
	UINT32 __hdcp14Reg = 0;
	UINT32 __hdcp22Reg = 0;

	/* Get Current Mode */
	do{
		/* Defence Code */
		if(!_p->initiated) {
			HDMI20_ERROR("[%s:%d] Error! HDMI21 device Handler not initiated!\n", __F__, __L__);
			break;
		}

		/* 2021/01/29 : If Phy is not locked, return no HDCP */
		if(_p->isPhyLocked == 0) {
			break;
		}

		/* Read HDCP2/HDCP1.4 Reg */
		__hdcp22Reg = _p->link_read(HDMI21_SNPS_REG_HDCP2_STATUS);
		__hdcp14Reg = _p->link_read(HDMI21_SNPS_REG_HDCP14_STATUS);


		/* If HDCP2.2 Decrypt Status is Zero, it means it is not HDCP2 */
		if((__hdcp22Reg & HDMI21_SNPS_FIELD_HDCP2_DECRYPTED) == 0) {
			break;
		}

		/* If HDCP1.4 Decrypt Status is valid, it means it is not HDCP2 */
		if((__hdcp14Reg & HDMI21_SNPS_FIELD_HDCP14_DECRYPT_ON) != 0) {
			break;	
		}

		/* If you've got this far.. it should be HDCP1.4 */
		ret = 1;
	} while(0);

	return ret;
}

/* Should be only called on HDCP1.4 state */
void HDMI21_HDCP_Rx_Set_UpdateHDCP14StableFlag(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isClear)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_RX_HDCP_HDCP14_STATE_T __hdcp14State = HDMI21_RX_HDCP_HDCP14_UNAUTHENTICATED;
	UINT32 __hdcp14Reg = 0;

	if(isClear) {
		_p->stablehdcp14time = 0;
	}
	else{
		/* Get HDCP1.4 Status */
		__hdcp14Reg = _p->link_read(HDMI21_SNPS_REG_HDCP14_STATUS);
		__hdcp14State = (HDMI21_RX_HDCP_HDCP14_STATE_T)((__hdcp14Reg & HDMI21_SNPS_FIELD_AUTH_CURSTATE));


		if( __hdcp14State >=  HDMI21_RX_HDCP_HDCP14_AUTHENTICATED) {
			if(_p->stablehdcp14time <= gHDMI21RxDevVideoControler[HDMI21__THRESHOLD_FOR_DETECTING_HDCP14_STABILITY].value){
				_p->stablehdcp14time += gHDMI21Thread.mSleep;
			}
		}
		else{
			_p->stablehdcp14time = 0;
		}
	}

}

int HDMI21_HDCP_Rx_Get_HDCP14Info(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_RX_HDCP_HDCP14_INFO_T *pData)
{
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	HDMI21_RX_HDCP_HDCP14_INFO_T __data;
	UINT32 __d[2];

	do {
		/* Defence Code */
		if(!_p->initiated) {
			HDMI20_ERROR("[%s:%d] Error! HDMI21 device Handler not initiated!\n", __F__, __L__);
			break;
		}

		/* memset*/
		memset((HDMI21_RX_HDCP_HDCP14_INFO_T *)&__data, 0, sizeof(HDMI21_RX_HDCP_HDCP14_INFO_T));
		memset((HDMI21_RX_HDCP_HDCP14_INFO_T *)pData, 0, sizeof(HDMI21_RX_HDCP_HDCP14_INFO_T));

		/* Fill in Data */
		__d[1]  = _p->link_read(HDMI21_SNPS_REG_HDCP14_DDC_STATUS1);
		__d[0]  = _p->link_read(HDMI21_SNPS_REG_HDCP14_DDC_STATUS2);
		memcpy((void *)&__data.An, (void *)&__d, sizeof(unsigned char) * 8);

		__d[1]  = _p->link_read(HDMI21_SNPS_REG_HDCP14_DDC_STATUS3);
		__d[1] &= (HDMI21_SNPS_FIELD_HDCP_AKSV_HIGH);
		__d[0]  = _p->link_read(HDMI21_SNPS_REG_HDCP14_DDC_STATUS4);
		memcpy((void *)&__data.Aksv, (void *)&__d, sizeof(unsigned char) * 5);

		__d[1]  = _p->link_read(HDMI21_SNPS_REG_HDCP14_BKSV_H);
		__d[1] &= (HDMI21_SNPS_FIELD_HDCP_BKSV_HIGH_QST);
		__d[0]  = _p->link_read(HDMI21_SNPS_REG_HDCP14_BKSV_L);
		memcpy((void *)&__data.Bksv, (void *)&__d, sizeof(unsigned char) * 5);

		__d[0]  = _p->link_read(HDMI21_SNPS_REG_HDCP14_DDC_STATUS0);
		__d[0]  = __d[0]>>16;  
		__d[0] &= (0x0000FFFF); 
		memcpy((void *)&__data.Ri, (void *)&__d, sizeof(unsigned char) * 2);
		
		__data.Bcaps = 0x81;

		__d[0]  = _p->link_read(HDMI21_SNPS_REG_HDCP14_BSTATUS);
		__d[0] &= (0x0000FFFF); 
		memcpy((void *)&__data.Bstatus, (void *)&__d, sizeof(unsigned char) * 2);

		/* Copy to reciever */
		memcpy((HDMI21_RX_HDCP_HDCP14_INFO_T *)pData, (HDMI21_RX_HDCP_HDCP14_INFO_T *)&__data, sizeof(HDMI21_RX_HDCP_HDCP14_INFO_T));
		ret = RET_OK;
	} while(0);

	return ret;
}

void HDMI21_HDCP_Rx_Set_HDCP23KeyHistory(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isSet)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do {
		/* Get Handler */
		_p = pDevHandler;

		if(isSet > 0) {
			_p->gWasHDCP22Written = isSet;
			_p->gWasHDCP22FuncCalled = isSet;
		}
		else {
			_p->gWasHDCP22Written = 0;
			_p->gWasHDCP22FuncCalled = 0;
		}

	} while(0);

	return;
}

int HDMI21_HDCP_Rx_Set_HDCP14Keys(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, LX_HDMI20_HDCP14_DATA_T *pData)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	int __keyWriteFailed = 0;
	int i = 0, k = 0;
	UINT32 __data;

	do {
		/* Null Pointer Defence */
		if(_p == NULL) break;

		if(pData == NULL) {
			HDMI20_ERROR("Error[%d] : Null Pointer \n", _p->port);
			break;
		}

		/* Set Key Encryption OFF */
		__data = _p->link_read(HDMI21_SNPS_REG_HDCP14_CONFIG);
		__data &= (~HDMI21_SNPS_FIELD_KEY_DECRYPT_EN_QST);
		_p->link_write(HDMI21_SNPS_REG_HDCP14_CONFIG, __data);

		for (i = 0; i < HDMI20_HDCP_KEYS_SIZE; i += 2) {
			for (k = 0; k < HDMI21_HDCP_KEY_WR_TRIES; k++) {
				
				/* Read Key write HW status */
				__data = _p->link_read(HDMI21_SNPS_REG_HDCP14_KEY_STATUS);
				
				if ((__data &  HDMI21_SNPS_FIELD_HDCP_KEY_WR_OK)!= 0) {
					/* Only Proceed if HW is ready to accept / increament*/
					break;
				}
			}

			if (k < HDMI21_HDCP_KEY_WR_TRIES) {
				_p->link_write(HDMI21_SNPS_REG_HDCP14_KEY_H, pData->keys[i + 1]);
				_p->link_write(HDMI21_SNPS_REG_HDCP14_KEY_L, pData->keys[i + 0]);
			} else {
				__keyWriteFailed = (int)((__data & HDMI21_SNPS_FIELD_HDCP_KEY_INDEX) | 0x80000000);
				break;
			}

		}

		/* Write BKSV Value */
		_p->link_write(HDMI21_SNPS_REG_HDCP14_BKSV_H, pData->bksv[1]);
		_p->link_write(HDMI21_SNPS_REG_HDCP14_BKSV_L, pData->bksv[0]);

		/* Set Repeater Capability */
		__data = _p->link_read(HDMI21_SNPS_REG_HDCP14_CONFIG);
		if(pData->repeat != 0) {
			__data |= (HDMI21_SNPS_FIELD_REPEATER_QST);
		}
		else {
			__data &= (~HDMI21_SNPS_FIELD_REPEATER_QST);
		}

		if(__keyWriteFailed != 0)	{ ret = __keyWriteFailed;}
		else 						{ ret = RET_OK;}
	} while(0);

	return ret;
}

int HDMI21_HDCP_Rx_Set_HDCP14RptKsvList(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 *pData, UINT32 count, UINT32 depth)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	int i = 0, k = 0;
	UINT32 __data;
	int error = 0;

	do {
		/* Null Pointer Defence */
		if(_p == NULL) break;

		if(pData == NULL) {
			HDMI20_ERROR("Error[%d] : Null Pointer \n", _p->port);
			break;
		}

		/* Exit if Repeater is not enabled */
		__data = _p->link_read(HDMI21_SNPS_REG_HDCP14_CONFIG);
		if((__data & HDMI21_SNPS_FIELD_REPEATER_QST) == 0x0 ) {
			HDMI20_ERROR("HDCP RPT[%d] : Error! Rpt KSV List called on Reciever mode\n", _p->port);
			break;
		}

		/* Not sure whether to set BSTATUS values */
		#if 0
		if (count <= MAX_DEVICES && count <= KSV_FIFO_SIZE) {
			error |= io_write(ctx, RA_HDCP_RPT_BSTATUS, MAX_DEVS_EXCEEDED, 0);
			error |= io_write(ctx, RA_HDCP_RPT_BSTATUS, DEVICE_COUNT, count);
		} else {
			error |= io_write(ctx, RA_HDCP_RPT_BSTATUS, MAX_DEVS_EXCEEDED, 1);
			error |= io_write(ctx, RA_HDCP_RPT_BSTATUS, DEVICE_COUNT, 0);
			count = 0;		/* don't write KSV list */
		}
		if (depth <= MAX_CASCADE) {
			error |= io_write(ctx, RA_HDCP_RPT_BSTATUS, MAX_CASCADE_EXCEEDED, 0);
			error |= io_write(ctx, RA_HDCP_RPT_BSTATUS, DEPTH, depth);
		} else {
			error |= io_write(ctx, RA_HDCP_RPT_BSTATUS, MAX_CASCADE_EXCEEDED, 1);
			error |= io_write(ctx, RA_HDCP_RPT_BSTATUS, DEPTH, 0);
			count = 0;		/* don't write KSV list */
		}
		#endif

		for (i = 0; i < count; i++) {
			for (k = 0; k < HDMI21_HDCP_KEY_WR_TRIES; k++) {
				__data = _p->link_read(HDMI21_SNPS_REG_HDCP14_RPT_STATUS);

				if ((__data &  HDMI21_SNPS_FIELD_RPT_KSVHOLD)== 0) {
					break;
				}
			}

			if (k < HDMI21_HDCP_KEY_WR_TRIES) {
				/* Increment Index Register */
				__data = i; __data &= (HDMI21_SNPS_FIELD_RPT_KSV_INDEX);
				_p->link_write(HDMI21_SNPS_REG_HDCP14_RPT_KSVFIFO, __data);
	
				/* Write KSV data */
				_p->link_write(HDMI21_SNPS_REG_HDCP14_RPT_KSV_H, pData[i * 2 + 1]);
				_p->link_write(HDMI21_SNPS_REG_HDCP14_RPT_KSV_L, pData[i * 2 + 0]);

				HDMI20_VIDEO("HDCP RPT[%d] : [%d] KSV => [0x%08x] [0x%08x]\n", _p->port, i, pData[i * 2 + 0], pData[i * 2 + 1]);
			} else {
				HDMI20_ERROR("HDCP RPT[%d] : Error! HDCP1.4 Engine KSV Write Error on [%d]th Data", _p->port, i);
				error++;
				break;
			}
		}

	} while(0);


	if (error == 0) {
		_p->link_write(HDMI21_SNPS_REG_HDCP14_RPT_CONTROL, HDMI21_SNPS_FIELD_RPT_KSVLISTREADY);
		HDMI20_VIDEO("HDCP RPT[%d] : HDCP14 Engine successfully handled [%d]count of KSV", _p->port, count);	
		ret = RET_OK;
	}

	return ret;
}

/*========================================================================================
 Static Function Implementation 
======================================================================================== */


