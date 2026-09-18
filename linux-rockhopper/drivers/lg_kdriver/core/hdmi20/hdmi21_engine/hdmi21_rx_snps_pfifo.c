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
#include "hdmi21_rx_snps_pfifo.h"
#include "hdmi21_rx_snps_pextract.h"

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
static int __HDMI21_PFIFO_Rx_Set_PktFifoThresLevel(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 pass, UINT32 low, UINT32 high);
static int __HDMI21_PFIFO_Rx_Get_CheckTypeWithMask(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 type);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T	gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
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
void HDMI21_PFIFO_Rx_Set_Initialize(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool isEnable)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = 0;
	UINT32 __data = 0;
	UINT32 mask, pass, low, high;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Configure Packet FIFO store mask */
	mask =  gHDMI21RxDevLinkControler[HDMI21__LINK_PFIFO_ENABLE_MASK].value;
	_p->link_write(HDMI21_SNPS_REG_PKTFIFO_STORE_FILT_CONFIG, mask);

	/* Configure Packet Alarm Threshold */
	pass = gHDMI21RxDevLinkControler[HDMI21__LINK_PFIFO_PASS_THRESHOLD].value;
	low  = gHDMI21RxDevLinkControler[HDMI21__LINK_PFIFO_LOW_THRESHOLD].value;
	high = gHDMI21RxDevLinkControler[HDMI21__LINK_PFIFO_HIGH_THRESHOLD].value;
	ret = __HDMI21_PFIFO_Rx_Set_PktFifoThresLevel(_p, pass, low, high);
	if(ret != RET_OK) {
		HDMI20_WARN("Warning[%d] : Ret(%d) Error from Set_PktFifoThres. Will remain previous setting\n", _p->port, ret);
	}
	
	/* Set Enable Write operation to FIFO */
	__data = _p->link_read(HDMI21_SNPS_REG_PKTFIFO_CONFIG);
	if(isEnable)	{ __data |= ( HDMI21_SNPS_FIELD_PKTFIFO_WRITE_EN); }
	else			{ __data &= (~HDMI21_SNPS_FIELD_PKTFIFO_WRITE_EN); }
	_p->link_write(HDMI21_SNPS_REG_PKTFIFO_CONFIG, __data);

	/* Reset Packet FIFO */
	HDMI21_PFIFO_Rx_Set_ResetPktFifo(_p);

	return;
}

void HDMI21_PFIFO_Rx_Set_ResetPktFifo(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Note that this register is a write only resetHigh register. No need
	 * to read/mask unnessessary bit fields */
	
	/* Set Fields */
	__data |= (HDMI21_SNPS_FIELD_PKTFIFO_INIT_P);
	__data |= (HDMI21_SNPS_FIELD_PKTFIFO_LTFILL_CLR_P);

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_PKTFIFO_CONTROL, __data);

	return;
}


int HDMI21_PFIFO_Rx_Get_FifoData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __temp[HDMI21_PFIFO_READ_COUNT_PER_OP];
	UINT8  __data[HDMI21_PFIFO_READ_COUNT_PER_OP * 4];
	UINT8 __type;
	UINT8 __gen0, __gen1;
	/* 2020/05/25 */
	UINT8	__vsifHead[3];
	int i;
	int ret = RET_ERROR;
	UINT32 currentJiffies = 0;

	do{
		/* Null Pointer Defence */
		if(_p == NULL) break;

		/* Get Data, reading the register auto increments FIFO data address
		 * Reading twice will increament FIFO pointer, since one point is 64 bit long*/
		for(i=0; i<HDMI21_PFIFO_READ_COUNT_PER_OP; i++) {
			__temp[i] = _p->link_read(HDMI21_SNPS_REG_PKTFIFO_DATA);
		}
	
		/* Get Rid of the 4th byte */
		__data[0] = (UINT8)( __temp[0] & 0x000000FF);
		__data[1] = (UINT8)((__temp[0] & 0x0000FF00) >> 8); 
		__data[2] = (UINT8)((__temp[0] & 0x00FF0000) >> 16); 
		memcpy((void *)&__data[3], (void *)&__temp[1], (sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH) - 4);
		

		/* Get type value for GEN0, GEN1 packets */
		__gen0 = HDMI21_PEXTRACT_Rx_Get_GenPKTType(_p, 0);
		__gen1 = HDMI21_PEXTRACT_Rx_Get_GenPKTType(_p, 1);

		/* Parse Data and store it to handler data */
		__type = (UINT8)(__temp[0] & 0x000000FF);

		/* DBG Purpose */
		HDMI21_LINE_DBG(160, "DBG[%d] :Type[0x%02x]|[0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x][0x%08x]\n",\
				_p->port, __type, __temp[0], __temp[1], __temp[2], __temp[3], __temp[4], __temp[5], __temp[6], __temp[7]);

		/* 2020/11/26 : Check PFIFO, as we face issues with garbage data from memory */
		if((__HDMI21_PFIFO_Rx_Get_CheckTypeWithMask(_p, __type) == RET_ERROR) && (_p->isPhyLocked != 0)){
			/* Please warn user */
			HDMI20_INTR("ERROR[%d] : Detected garbage on PFIFO! Perform PKTFIFO Reset!  Type[0x%02x]\n", _p->port, __type);
			HDMI21_PFIFO_Rx_Set_ResetPktFifo(_p);
		
			/* Exit from Loop */
			ret = RET_OK; /* We do not want to make any exception for this.. as Reseting the PFIFO would just do the trick */
			break;
		}

		switch(__type)
		{
			case 0x01:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__ACR][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x03:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__GCP][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x04:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__ACP][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x05:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__ISRC1][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x06:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__ISRC2][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x0A:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__GAMUT][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x0D:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__AMD][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x7F:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__EMD][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x81:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__VSI][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);

				/* Get Current Time */
				currentJiffies = jiffies_to_msecs(jiffies);

				/* 2020/05/25 */
				/* Get Header */
				__vsifHead[0] = _p->dataPacket[HDMI21_DISLAND_DATA__VSI][4];
				__vsifHead[1] = _p->dataPacket[HDMI21_DISLAND_DATA__VSI][5];
				__vsifHead[2] = _p->dataPacket[HDMI21_DISLAND_DATA__VSI][6];

				/* H14B VSIF */
				if((__vsifHead[0] == HDMI21_RX_VSI_TYPE_H14B_OUI_0) \
						&& (__vsifHead[1] == HDMI21_RX_VSI_TYPE_H14B_OUI_1) \
						&& (__vsifHead[2] == HDMI21_RX_VSI_TYPE_H14B_OUI_2)) {
					memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__H14VSI], &_p->dataPacket[HDMI21_DISLAND_DATA__VSI], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);
		

					if((_p->dolbyVsiTimeStamp == 0) || \
							(_p->dolbyVsiTimeStamp > currentJiffies) || /* Considering Variable Overflow */ \
							((currentJiffies - _p->dolbyVsiTimeStamp) >= gHDMI21RxDevVideoControler[HDMI21__VIDEO_DOVI_PACKET_MS_TIMEOUT].value )) {
						/* 2020/08/21 : Integrated Buffer for Dolby Detection(H14F + Dolby VSI) */
						memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__DOVI], &_p->dataPacket[HDMI21_DISLAND_DATA__VSI], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);

						/* 2020/11/25 : Timeout feature for DOVI */
						_p->doviTimeStamp = currentJiffies; 
					}
				}
				else if((__vsifHead[0] == HDMI21_RX_VSI_TYPE_HF_OUI_0) \
						&& (__vsifHead[1] == HDMI21_RX_VSI_TYPE_HF_OUI_1) \
						&& (__vsifHead[2] == HDMI21_RX_VSI_TYPE_HF_OUI_2)) {
					memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__HFVSI], &_p->dataPacket[HDMI21_DISLAND_DATA__VSI], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);
				}
				else if((__vsifHead[0] == HDMI21_RX_VSI_TYPE_DOLBY_OUI_0) \
						&& (__vsifHead[1] == HDMI21_RX_VSI_TYPE_DOLBY_OUI_1) \
						&& (__vsifHead[2] == HDMI21_RX_VSI_TYPE_DOLBY_OUI_2)) {
					memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__DOLBYVSI], &_p->dataPacket[HDMI21_DISLAND_DATA__VSI], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);
					
					/* 2020/08/21 : Integrated Buffer for Dolby Detection(H14F + Dolby VSI) */
					memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__DOVI], &_p->dataPacket[HDMI21_DISLAND_DATA__VSI], sizeof(UINT8) * HDMI21_MAX_DATA_PACKET_LENGTH);
				
					/* 2020/11/25 : Timeout feature for DOVI */
					_p->doviTimeStamp = currentJiffies;

					/* 2020/12/03 : Need to keep record of Dolby VSI time stamps */
					_p->dolbyVsiTimeStamp = currentJiffies;
				}
				break;

			case 0x82:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__AVI][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x83:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__SPD][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x84:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__AIF][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x86:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__NTSCVBI][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			case 0x87:
				memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__DRM][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
				break;

			default : 
				{
					if(__type == __gen0) {
						memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__GEN0][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
					}
					else if(__type == __gen1) {
						memcpy((void *)&_p->dataPacket[HDMI21_DISLAND_DATA__GEN1][0], (void *)&__data, sizeof(UINT8)*HDMI21_MAX_DATA_PACKET_LENGTH);
					}
					else{
						HDMI20_WARN("WARN[%d] : Unknown Packet type[0x%02x] recieved from PFIFO\n", _p->port, __type);
					}
				}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}


/*========================================================================================
 Static Function Implementation 
======================================================================================== */
static int __HDMI21_PFIFO_Rx_Set_PktFifoThresLevel(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 pass, UINT32 low, UINT32 high)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	UINT32 __data = 0;
	UINT32 __tmp, __tmp1 = 0;

	do{
		/* Null Pointer Defence */
		if(_p == NULL) break;


		/* Packet FIFO size is 402 * 64 bits = (32 x 2) * (4 * 100) = 32 x 8 x 100,
		 * this means that maximun Packet count is 100 since every packet is 32 byte max.
		 * Default value in Hardware for pass-threshold is 0x32, where written in the document.
		 * 0x32 = d'50, where 50% of the FIFO is set to be the pass-threshold level */

		/* Check Values */
		if(pass > 100) {
			HDMI20_ERROR("Error[%d] : PassThreshold[%d] cannot exceed 0x64(d'100)\n", _p->port, pass);
			break;
		}

		if(low > 99) {
			HDMI20_ERROR("Error[%d] : LowThreshold[%d] atleast needs to be lower than 0x63(d'99)\n", _p->port, low);
			break;	
		}

		/* Note that high threshold should never be the same value as maximum(100) FIFO size */
		if(high > 99) {
			HDMI20_ERROR("Error[%d] : HighThreshold[%d] cannot exceed 0x63(d'99)\n", _p->port, high);
			break;	
		}

		if((pass == low) || (pass == high) || (low == high) || (high < pass) || (low > pass) || (high < low)) {
			HDMI20_ERROR("Error[%d] : low(%d) < pass(%d0 < high(%d) condition is manadatory!\n", _p->port, low, pass, high);
			break;
		}

		/* Set Pass Threshold */
		__data  = _p->link_read(HDMI21_SNPS_REG_PKTFIFO_THR_CONFIG0);
		__data &= (~HDMI21_SNPS_FIELD_PKTFIFO_THR_PASS_QST);
		__tmp = pass; 
		__tmp &= 0x000000FF; /* Incase corruption */
		__data |= __tmp;
		_p->link_write(HDMI21_SNPS_REG_PKTFIFO_THR_CONFIG0, __data);

		/* Set Low/High Threshold */
		__data = _p->link_read(HDMI21_SNPS_REG_PKTFIFO_THR_CONFIG1);
		__data &= (~HDMI21_SNPS_FIELD_PKTFIFO_THR_HIGH_QST);
		__data &= (~HDMI21_SNPS_FIELD_PKTFIFO_THR_LOW_QST);
		__tmp = low;
		__tmp &= 0x000000FF; /* Incase corruption */

		__tmp1 |= high;
		__tmp1 &= 0x000000FF; /* Incase corruption */
		__tmp1 = __tmp1 << 16;
		
		__data |= __tmp; 
		__data |= __tmp1;

		_p->link_write(HDMI21_SNPS_REG_PKTFIFO_THR_CONFIG0, __data);

		ret = RET_OK;
	} while(0);

	return ret;
}


static int __HDMI21_PFIFO_Rx_Get_CheckTypeWithMask(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT8 type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	int ret = RET_ERROR;
	UINT32 __mask;

	do{
		/* Null Pointer Defence */
		if(_p == NULL) break;

		/* Get Current Mask */
		__mask = _p->link_read(HDMI21_SNPS_REG_PKTFIFO_STORE_FILT_CONFIG);

		/* Break if FILTER is not enabled */
		if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_FILT_EN) == 0x0) {
			ret = RET_OK;
			break;
		}

		switch(type)
		{
			case 0x01:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_ACR) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x03:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_GCP) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x04:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_ACP) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x05:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_ISRC) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x06:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_ISRC) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x0A:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_GMD) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x0D:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_AMD) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x7F:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_EMD) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x81:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_VSIF) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x82:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_AVIIF) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x83:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_SRCPDIF) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x84:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_AUDIF) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x86:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_NTSCVBIIF) != 0x0) {
					ret = RET_OK;
				}
				break;

			case 0x87:
				if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_DRMIF) != 0x0) {
					ret = RET_OK;
				}
				break;

			default : 
				{
					if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_GENPKT0) != 0x0) {
						if(type == HDMI21_PEXTRACT_Rx_Get_GenPKTType(_p, 0)) {
							ret = RET_OK;
						}
					}
					else if((__mask & HDMI21_SNPS_FIELD_PKTFIFO_STORE_GENPKT1) != 0x0) {
						if(type == HDMI21_PEXTRACT_Rx_Get_GenPKTType(_p, 1)) {
							ret = RET_OK;
						}
					}
					break;
				}
		}
	} while(0);

	return ret;
}
