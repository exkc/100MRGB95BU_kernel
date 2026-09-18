/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2021 by LG Electronics Inc.

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
 *  @date		2021-04-19
 *  @note		Additional information. 
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/interrupt.h>
#include <linux/delay.h>
#include "../hdmi20_drv.h" 			/* For debug prints */
#include "hdmi21_hal_driver.h"		/* Device Handler */
#include "hdmi21_rx_ddcmon.h"

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

/*----------------------------------------------------------------------------------------
	Static Function Prototype Declarations
----------------------------------------------------------------------------------------*/
static int __HDMI21_DDCMON_Rx_Get_CheckAndDumpData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 bank, UINT32 isrType, UINT8 prevIndex); 
static char *__ddc_mon_type_to_str(HDMI21_DDCMON_DDC_SEL_TYPE_T type);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI21_HAL_RX_DEVICE_DATA 	gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/
static UINT8 __prevDdcBankIsrIndex[HDMI21_NUM_OF_MAX_PORTS] = {0,};

/*========================================================================================
	Implementation Group
========================================================================================*/

void HDMI21_DDCMON_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __clearMask = (HDMI21_TOP_FIELD_DDC1_INTR_CLR | HDMI21_TOP_FIELD_DDC2_INTR_CLR | HDMI21_TOP_FIELD_DDC3_INTR_CLR | HDMI21_TOP_FIELD_DDC4_INTR_CLR);

	/* Defence Code */
	if(!_p->initiated) return;

	/* Clear DDC Mon lastest rcv history */
	_p->ddcBufPnt = 0;
	_p->ddcBufPrevBank = 0;

	/* Enable Off */
	HDMI21_DDCMON_Rx_Set_EnableMonitor(_p, 0);

	/* Enable for all 4 banks */
	HDMI21_DDCMON_Rx_Set_InterruptEnable(_p, 5, 1);

	/* Set CLR bit */
	HDMI21_DDCMON_Rx_Set_ClearMonitor(_p, 1);
	/* Clear CLR bit */
	/* 2021/04/19 won.hur : Note that some register setting is between CLR set&clr. 
	 * This is to give some time between clear action*/
	HDMI21_DDCMON_Rx_Set_ClearMonitor(_p, 0);

	/* Set DDC Selection Type */
	HDMI21_DDCMON_Rx_Set_ModeType(_p, gHDMI21RxDevVideoControler[HDMI21__VIDEO_DDCMON_ADDR_SEL].value);

	/* Set CLR interrupt flag, just in case. Write Only register, do not need to disable "set-clear" */
	HDMI21_DDCMON_Rx_Set_InterruptClear(_p, __clearMask);

	return;
}


void HDMI21_DDCMON_Rx_Set_EnableMonitor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isEnable)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Defence Code */
	if(!_p->initiated) return;

	HDMI20_VIDEO("DDCMON[%d] : Setting [%s] DDC Monitor\n", _p->port, isEnable?"Enable":"Disable");

	/* Register Read */
	__data = _p->top_read(HDMI21_TOP_REG_DDC_MONITOR_CONFIG);


	/* Set Field */
	if(isEnable) 	{	__data |= ( HDMI21_TOP_FIELD_MONITOR_EN); _p->isDdcMonEnabled = 1;}
	else 			{	__data &= (~HDMI21_TOP_FIELD_MONITOR_EN); _p->isDdcMonEnabled = 0;}

	/* Register Write */
	_p->top_write(HDMI21_TOP_REG_DDC_MONITOR_CONFIG, __data);

	return;
}

int HDMI21_DDCMON_Rx_Get_ProcessIsr(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;
	UINT32 __isrType = 0;
	int _turnOff = 0;
	int i;
	int __processCnt = 0;
	int __previousCnt = 0;

	do{
		if(!_p->initiated) break;

		/* Defence Code */
		if(_p->isDdcMonEnabled <= 0) {	_turnOff = 1;}

		/* Read ISR status */
		__isrType = _p->top_read(HDMI21_TOP_REG_DDC_INTR);

		/* Exit if ISR incase of false-alaram. If appropriate call, then return values as ISR status */
		if(__isrType == 0) {
			HDMI21_LINE_DBG(667, "DBG[%d] : DDCMon ISR was called without any DDCMON Flags\n", _p->port);
			break;
		}
		else {
			HDMI21_LINE_DBG(667, "DBG[%d] : DDCMON ISR[0x%08x] / PreIndex[%d]\n", _p->port, __isrType, __prevDdcBankIsrIndex[_p->port]);
			
			__previousCnt = __prevDdcBankIsrIndex[_p->port];	
			ret = (int)__isrType;
		}

		/* Exit if buffer was not allocated */
		if(_p->pDdcBuf == NULL) {
			HDMI20_INFO("DDCMon ISR[%d] : No Buffer allocated. Disable DDCMon Interrupt\n", _p->port);
			_turnOff = 1;
			break;
		}

		/* Stop when buffer is full. May need to change this to add more features */
		if((_p->ddcBufPnt >= _p->ddcBufCnt)) {
			HDMI20_INFO("DDCMon ISR[%d] : Buffer is Full. Disable DDCMon Interrupt!(Pnt[%d]/Cnt[%d]\n", _p->port, _p->ddcBufPnt, _p->ddcBufCnt);
			_turnOff = 1;
			break;
		}

		/* Process for triggered bank. Would be weird if ISR was triggered with more than one bank */
		if(__previousCnt  == 0) {
			for(i=1; i<= HDMI21_DDCMON_NUM_OF_DDC_BANK; i++) {
				if(__HDMI21_DDCMON_Rx_Get_CheckAndDumpData(_p, i, __isrType, __previousCnt) > 0) {
					__processCnt++;

					/* Interrupt Clear */
					HDMI21_DDCMON_Rx_Set_InterruptClear(_p, i);
				}
			}
		}
		else {
			for(i = __previousCnt; i<= HDMI21_DDCMON_NUM_OF_DDC_BANK; i++) {
				if(__HDMI21_DDCMON_Rx_Get_CheckAndDumpData(_p, i, __isrType, __previousCnt) > 0) {
					__processCnt++;

					/* Interrupt Clear */
					HDMI21_DDCMON_Rx_Set_InterruptClear(_p, i);
				}
			}

			for(i = 1; i< __previousCnt; i++) {
				if(__HDMI21_DDCMON_Rx_Get_CheckAndDumpData(_p, i, __isrType, __previousCnt) > 0) {
					__processCnt++;

					/* Interrupt Clear */
					HDMI21_DDCMON_Rx_Set_InterruptClear(_p, i);
				}
			}
		}

		/* If ISR contained all 4 banks, system is too slow for this HW. Turn off */
		if(__processCnt >= HDMI21_DDCMON_NUM_OF_DDC_BANK) {
			HDMI20_INFO("DDCMon ISR[%d] : Covered upto max bank at once[%d]. System is too slow. Disable DDCMon!\n", _p->port, __processCnt);
		}
	} while(0);


	/* Disable Interrupt for selected conditinos */
	if(_turnOff > 0) {
		HDMI21_DDCMON_Rx_Set_EnableMonitor(_p, 0);
		HDMI21_DDCMON_Rx_Set_InterruptEnable(_p, 5, 0);
	}

	return ret;
}

void HDMI21_DDCMON_Rx_Set_ClearMonitor(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isClear)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;

	/* Defence Code */
	if(!_p->initiated) return;

	HDMI20_VIDEO("DDCMON[%d] : Clear [%s] DDC Monitor\n", _p->port, isClear?"Active":"Deactive");

	/* Register Read */
	__data = _p->top_read(HDMI21_TOP_REG_DDC_MONITOR_CONFIG);


	/* Set Field */
	if(isClear) 	{	__data |= ( HDMI21_TOP_FIELD_MONITOR_CLR);	}
	else 			{	__data &= (~HDMI21_TOP_FIELD_MONITOR_CLR);	}

	/* Register Write */
	_p->top_write(HDMI21_TOP_REG_DDC_MONITOR_CONFIG, __data);


	/* Clear Index History */
	__prevDdcBankIsrIndex[_p->port] = 0;

	return;
}

void HDMI21_DDCMON_Rx_Set_ModeType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_DDCMON_DDC_SEL_TYPE_T type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data = 0;
	UINT32 __temp = 0;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Defence Code */
	if(type >= HDMI21_DDCMON_DDC_MAXNUM) {
		HDMI20_ERROR("DDCMON[%d] : Error! Unknown type[%d]\n", _p->port, type);
	}

	HDMI20_VIDEO("DDCMON[%d] : DDC Monitor is set to Capture [%s]\n", _p->port, __ddc_mon_type_to_str(type));

	/* Register Read */
	__data = _p->top_read(HDMI21_TOP_REG_DDC_MONITOR_CONFIG);

	/* Set Field based on types */
	/* 1-1 : Clear field */
	__data &= (~HDMI21_TOP_FIELD_DDC_SEL);

	/* 1-2 : Set field values */
	switch (type)
	{
		case HDMI21_DDCMON_DDC_ENABLE_ALL:
			{
				__temp = 0x0;
				break;
			}
		case HDMI21_DDCMON_DDC_EDID_ONLY :
			{
				__temp = 0x1;
				break;
			}
		case HDMI21_DDCMON_DDC_SCDC_ONLY :
			{
				__temp = 0x2;
				break;
			}
		case HDMI21_DDCMON_DDC_HDCP_ONLY :
			{
				__temp = 0x3;
				break;
			}
		default :
			{
				__temp = 0x0;
				break;
			}
	}

	/* 1-3 : bit shift & clear all other values before OR*/
	__temp  = __temp << 8;
	__temp &= (HDMI21_TOP_FIELD_DDC_SEL);

	/* 1-4 : merge selected value field to origin dest shawdow */
	__data |= __temp;


	/* Register Write */
	_p->top_write(HDMI21_TOP_REG_DDC_MONITOR_CONFIG, __data);

	return;
}


void HDMI21_DDCMON_Rx_Set_InterruptEnable(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 bank, bool isEnable)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __temp = 0;
	UINT32 __data = 0;

	/* Defence Code */
	if(!_p->initiated) return;

	/* Set BIT offset for appropriate bank # */
	if(bank == 1) 		{ __temp = HDMI21_TOP_FIELD_DDC1_INTR_EN;}
	else if(bank == 2)	{ __temp = HDMI21_TOP_FIELD_DDC2_INTR_EN;}
	else if(bank == 3)	{ __temp = HDMI21_TOP_FIELD_DDC3_INTR_EN;}
	else if(bank == 4)	{ __temp = HDMI21_TOP_FIELD_DDC4_INTR_EN;}
	else if(bank >= 5) {
		__temp =   HDMI21_TOP_FIELD_DDC1_INTR_EN \
				 | HDMI21_TOP_FIELD_DDC2_INTR_EN \
				 | HDMI21_TOP_FIELD_DDC3_INTR_EN \
				 | HDMI21_TOP_FIELD_DDC4_INTR_EN;
	}
	else {
		/* Fatal Error */
		HDMI20_ERROR("DDC MON[%d] : Fatal Error! Code/Op corrupted case\n", _p->port);
		return;
	}

	/* Read register value */
	__data = _p->top_read(HDMI21_TOP_REG_DDC_INTR_EN);
	
	/* Set bit field */
	if(isEnable)	{	__data |= ( __temp);}
	else 			{	__data &= (~__temp);}

	/* Write register value */
	_p->top_write(HDMI21_TOP_REG_DDC_INTR_EN, __data);

	return;
}

void HDMI21_DDCMON_Rx_Set_InterruptClear(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 bank)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __temp = 0;

	/* Defence Code */
	if(!_p->initiated) return;



	/* Set BIT offset for appropriate bank # */
	if(bank == 1) 		{ __temp = HDMI21_TOP_FIELD_DDC1_INTR_CLR;}
	else if(bank == 2)	{ __temp = HDMI21_TOP_FIELD_DDC2_INTR_CLR;}
	else if(bank == 3)	{ __temp = HDMI21_TOP_FIELD_DDC3_INTR_CLR;}
	else if(bank == 4)	{ __temp = HDMI21_TOP_FIELD_DDC4_INTR_CLR;}
	else if(bank >= 5) {
		__temp =   HDMI21_TOP_FIELD_DDC1_INTR_CLR \
				 | HDMI21_TOP_FIELD_DDC2_INTR_CLR \
				 | HDMI21_TOP_FIELD_DDC3_INTR_CLR \
				 | HDMI21_TOP_FIELD_DDC4_INTR_CLR;
	}
	else {
		/* Fatal Error */
		HDMI20_ERROR("DDC MON[%d] : Fatal Error! Code/Op corrupted case\n", _p->port);
		return;
	}

	HDMI21_LINE_DBG(667, "DDC Mon[%d] : Clear Interrupt. [0x%08x] <- [0x%08x]\n", _p->port, HDMI21_TOP_REG_DDC_INTR_CLR, __temp);

	/* Write register value */
	_p->top_write(HDMI21_TOP_REG_DDC_INTR_CLR, __temp);

	return;
}

int HDMI21_DDCMON_Rx_Get_Data(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 bank, HDMI21_HAL_DDC_HW_UNITDATA_T *pData)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data;
	HDMI21_HAL_DDC_HW_UNITDATA_T __userdata;
	HDMI21_DDCMON_DDC_STATUS_T *__pStatus;
	HDMI21_DDCMON_DDC_ADDR_T *__pAddr;
	UINT32 __offsetStatus, __offsetAddr,  __offsetData;
	int ret = RET_ERROR;

	do{
		/* Defence Code */
		if(!_p->initiated) break;

		/* Defence Code */
		if(pData == NULL) break;
		else {
			memset((HDMI21_HAL_DDC_HW_UNITDATA_T *)pData, 0, sizeof(HDMI21_HAL_DDC_HW_UNITDATA_T));
			memset((HDMI21_HAL_DDC_HW_UNITDATA_T *)&__userdata, 0, sizeof(HDMI21_HAL_DDC_HW_UNITDATA_T));
		}

		/* Defence Code */
		if((bank <= 0) || (bank > HDMI21_DDCMON_NUM_OF_DDC_BANK)) {
			break;	
		}

		/* Set BIT offset for appropriate bank # */
		if(bank == 1) 		{ 
			__offsetStatus 	= HDMI21_TOP_REG_DDC1_STATUS; 
			__offsetAddr 	= HDMI21_TOP_REG_DDC1_ADDR;
			__offsetData	= HDMI21_TOP_REG_DDC1_DATA;
		}
		else if(bank == 2)	{ 
			__offsetStatus 	= HDMI21_TOP_REG_DDC2_STATUS; 
			__offsetAddr 	= HDMI21_TOP_REG_DDC2_ADDR;
			__offsetData 	= HDMI21_TOP_REG_DDC2_DATA; 
		}
		else if(bank == 3)	{ 
			__offsetStatus 	= HDMI21_TOP_REG_DDC3_STATUS; 
			__offsetAddr 	= HDMI21_TOP_REG_DDC3_ADDR;
			__offsetData 	= HDMI21_TOP_REG_DDC3_DATA; 
		}
		else if(bank == 4)	{ 
			__offsetStatus 	= HDMI21_TOP_REG_DDC4_STATUS; 
			__offsetAddr 	= HDMI21_TOP_REG_DDC4_ADDR;
			__offsetData 	= HDMI21_TOP_REG_DDC4_DATA; 
		}
		else {
			/* Fatal Error */
			HDMI20_ERROR("DDC MON[%d] : Fatal Error! Code/Op corrupted case\n", _p->port);
			break;
		}

		/* Read Register */
		/* Store Bank Info */
		__userdata.bank = bank;

		/* 1 : Read status reg */
		__data = _p->top_read(__offsetStatus);
		__pStatus = (HDMI21_DDCMON_DDC_STATUS_T *)&__data; 

		/* Match fields to dest */
		__userdata.op_mode 			= __pStatus->op_mode;
		__userdata.intr_err 		= __pStatus->intr_err;
		__userdata.cap_length 		= __pStatus->cap_length;
		__userdata.finish 			= __pStatus->finish;
		__userdata.nack 			= __pStatus->nack;
		__userdata.scdc_short_rd 	= __pStatus->scdc_short_rd;
		__userdata.hdcp_short_rd 	= __pStatus->hdcp_short_rd;

		/* 2 : Read Addr reg */
		__data = _p->top_read(__offsetAddr);
		__pAddr = (HDMI21_DDCMON_DDC_ADDR_T *)&__data;

		/* Match field to user data struct */
		__userdata.sub_addr 		= __pAddr->sub_addr;
		__userdata.dev_addr			= __pAddr->dev_addr;

		/* 3 : Read DDC data : Need to decide whether to block mask none-count data*/
		__userdata.data 			= _p->top_read(__offsetData);

		/* 4 : Get Time */
		__userdata.msec 			= jiffies_to_msecs(jiffies);

		/* Memcopy to dest */
		memcpy((HDMI21_HAL_DDC_HW_UNITDATA_T *)pData, (HDMI21_HAL_DDC_HW_UNITDATA_T *)&__userdata, sizeof(HDMI21_HAL_DDC_HW_UNITDATA_T));

		ret = RET_OK;
	} while(0);


	return ret;
}

/*========================================================================================
 Static Function Implementation 
======================================================================================== */
static char *__ddc_mon_type_to_str(HDMI21_DDCMON_DDC_SEL_TYPE_T type)
{
	switch (type)
	{

		case HDMI21_DDCMON_DDC_ENABLE_ALL:
			return "ALL(HDCP/SCDC/EDID)";
		case HDMI21_DDCMON_DDC_EDID_ONLY :
			return "EDID ONLY";
		case HDMI21_DDCMON_DDC_SCDC_ONLY :
			return "SCDC ONLY";
		case HDMI21_DDCMON_DDC_HDCP_ONLY :
			return "HDCP ONLY";
		default :
				return "Unknown";
	}
}


static int __HDMI21_DDCMON_Rx_Get_CheckAndDumpData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 bank, UINT32 isrType,UINT8 prevIndex) 
{	
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;

	if(bank == 1) {
		if((isrType &  HDMI21_TOP_FIELD_DDC1_INTR) != 0) {

			if(prevIndex != 1) {
				/* Get Data */
				if(HDMI21_DDCMON_Rx_Get_Data(_p, 1, &_p->pDdcBuf[_p->ddcBufPnt]) == RET_OK) {
					_p->ddcBufPnt++;
				}
			}
			/* Set History */
			_p->isr_count0[HDMI21_ISR_TOP_DDCMON_DDC1_IRQ]++;

			ret = 1;
		}
	}
	else if(bank == 2) {
		if((isrType &  HDMI21_TOP_FIELD_DDC2_INTR) != 0) {

			if(prevIndex != 2) {
				/* Get Data */
				if(HDMI21_DDCMON_Rx_Get_Data(_p, 2, &_p->pDdcBuf[_p->ddcBufPnt]) == RET_OK) {
					_p->ddcBufPnt++;
				}
			}
			/* Set History */
			_p->isr_count0[HDMI21_ISR_TOP_DDCMON_DDC2_IRQ]++;

			ret = 2;
		}

	}
	else if(bank == 3) {
		if((isrType &  HDMI21_TOP_FIELD_DDC3_INTR) != 0) {
	
			if(prevIndex != 3) {
				/* Get Data */
				if(HDMI21_DDCMON_Rx_Get_Data(_p, 3, &_p->pDdcBuf[_p->ddcBufPnt]) == RET_OK) {
					_p->ddcBufPnt++;
				}
			}

			/* Set History */
			_p->isr_count0[HDMI21_ISR_TOP_DDCMON_DDC3_IRQ]++;

			ret = 3;
		}

	}
	else if(bank == 4) {
		if((isrType &  HDMI21_TOP_FIELD_DDC4_INTR) != 0) {
	
			if(prevIndex != 4) {
				/* Get Data */
				if(HDMI21_DDCMON_Rx_Get_Data(_p, 4, &_p->pDdcBuf[_p->ddcBufPnt]) == RET_OK) {
					_p->ddcBufPnt++;
				}
			}

			/* Set History */
			_p->isr_count0[HDMI21_ISR_TOP_DDCMON_DDC4_IRQ]++;

			ret = 4;
		}
	}

	HDMI21_LINE_DBG(667, "DBG[%d] : Checked for Bank[%d] / ret [%d] / IsrType[0x%08x]\n", _p->port, bank, ret, isrType);

	/* Save bank History */
	if(ret > 0) {
		HDMI21_LINE_DBG(667, "DBG[%d] : DDCMON Hist Update from [%d] to [%d]\n", _p->port, __prevDdcBankIsrIndex[_p->port], ret);
		__prevDdcBankIsrIndex[_p->port] = ret;
	}

	return ret;
}

