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
#include "hdmi21_rx_snps_misc.h"

/* LX_CHIP_REV() */
#include "os_util.h"
#include "sys_regs.h"
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
static char *__rst_type_to_str(HDMI21_SNPS_RST_TYPE_T type);

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
UINT32 HDMI21_MISC_Rx_Get_CoreID(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return 0xFFFFFFFF;

	/* Return Value */
	return _p->link_read(HDMI21_SNPS_REG_CORE_ID);
}

UINT32 HDMI21_MISC_Rx_Get_CoreVerNum(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return 0xFFFFFFFF;

	/* Return Value */
	return _p->link_read(HDMI21_SNPS_REG_VER_NUMBER);
}

UINT32 HDMI21_MISC_Rx_Get_CoreVerType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return 0xFFFFFFFF;

	/* Return Value */
	return _p->link_read(HDMI21_SNPS_REG_VER_TYPE);
}

UINT32 HDMI21_MISC_Rx_Get_CoreTStampHHMM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return 0xFFFFFFFF;

	/* Return Value */
	return _p->link_read(HDMI21_SNPS_REG_CORE_TIMESTAMP_HHMM);
}

UINT32 HDMI21_MISC_Rx_Get_CoreTStampMMDD(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return 0xFFFFFFFF;

	/* Return Value */
	return _p->link_read(HDMI21_SNPS_REG_CORE_TIMESTAMP_MMDD);
}

UINT32 HDMI21_MISC_Rx_Get_CoreTStampYYYY(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return 0xFFFFFFFF;

	/* Return Value */
	return _p->link_read(HDMI21_SNPS_REG_CORE_TIMESTAMP_YYYY);
}

void HDMI21_MISC_Rx_Set_ResetCore(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_SNPS_RST_TYPE_T type)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	switch(type)
	{
		case HDMI21_SNPS_RST_MAIN:
			__data = HDMI21_SNPS_FIELD_MAIN_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_AVPUNIT:
			__data = HDMI21_SNPS_FIELD_AVPUNIT_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_AUDIO:
			__data = HDMI21_SNPS_FIELD_AUDIO_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_HDCP:
			__data = HDMI21_SNPS_FIELD_HDCP_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_PKTFIFO:
			__data = HDMI21_SNPS_FIELD_PKTFIFO_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_DATAPATH:
			__data = HDMI21_SNPS_FIELD_DATAPATH_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_CEC:
			__data = HDMI21_SNPS_FIELD_CEC_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_APB:
			__data = HDMI21_SNPS_FIELD_APB_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_PHYCTRL:
			__data = HDMI21_SNPS_FIELD_PHYCTRL_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_EARCTX:
			__data = HDMI21_SNPS_FIELD_EARCTX_SWRESETREQ;
			break;
		case HDMI21_SNPS_RST_DATAPATHONLY:
			__data = HDMI21_SNPS_FIELD_DATAPATHONLY_SWRESETREQ;
			/* 2025/03/25 won.hur : Suppose this would be identical to O26 ... */
			if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
				_p->top_write(HDMI21_TOP_REG_NEW_REG_O24_SNPSRST, HDMI21_TOP_BIT_NEW_REG_O24_DATAPATHONLY);
			}
			break;
		case HDMI21_SNPS_RST_HDCPQP:
			__data = HDMI21_SNPS_FIELD_HDCPQP_SWRESETREQ;
			break;
			
		default : 
			/* Do nothing */
			break;
	}

	if(__data != 0) {
		HDMI21_LINE_DBG(7166, "Info[%d] : Link Reset[%s]. Caller[%pS]\n", _p->port, __rst_type_to_str(type), __builtin_return_address(0));
		_p->link_write(HDMI21_SNPS_REG_GLOBAL_SWRESET_REQUEST, __data);
	}

	return;
}

void HDMI21_MISC_Rx_Set_RefClkValue(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	HDMI21_LINE_DBG(213, "DBG[%d] : Set Link Core refClkVal to [%d]Hz\n", _p->port, value);

	/* irefclk register is only 29 bit long */
 	if(value < 0x20000000) {
		_p->link_write(HDMI21_SNPS_REG_GLOBAL_TIMER_REF_BASE, value);
	}
	else {
		HDMI20_WARN("Warn[%d] : irefClk cannot be over 0x2000000. Set to maximum value\n", _p->port);
		_p->link_write(HDMI21_SNPS_REG_GLOBAL_TIMER_REF_BASE, 0x1FFFFFFF);
	}

	return;
}

UINT32 HDMI21_MISC_Rx_Get_RefClkValue(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return 0;

	return _p->link_read(HDMI21_SNPS_REG_GLOBAL_TIMER_REF_BASE);
}


void 	HDMI21_MISC_Rx_Set_CoreHpdConfig(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;

	/* Null Pointer Defence */
	if(_p == NULL) return;


	/* For this function, register value is overwritten with the provided argument */
	_p->link_write(HDMI21_SNPS_REG_CORE_CONFIG, value);

	return;
}

void 	HDMI21_MISC_Rx_Set_CoreCmuTmdsQpClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __val;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_CMU_CONFIG0);

	/* CMU Margin settings are only up to 15 bit, need to consider overflow */
	if(value >= 0x8000) { __val = 0x00007FFF;	}
	else 				{ __val = value; __val &= 0x00007FFF;}

	/* Bit shift */
	__val = __val << 16;

	/* Reset Field */
	__data &= (~HDMI21_SNPS_FIELD_TMDSQPCLK_STABLE_FREQ_MARGIN);
	__data |= __val;

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_CMU_CONFIG0, __data);

	return;
}

void 	HDMI21_MISC_Rx_Set_CoreCmuAudioClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __val;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_CMU_CONFIG0);

	/* CMU Margin settings are only up to 15 bit, need to consider overflow */
	if(value >= 0x8000) { __val = 0x7FFF;	}
	else 				{ __val = value; __val &= 0x00007FFF;}


	/* Reset Field */
	__data &= (~HDMI21_SNPS_FIELD_AUDCLK_STABLE_FREQ_MARGIN);
	__data |= __val;

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_CMU_CONFIG0, __data);

	return;
}

void 	HDMI21_MISC_Rx_Set_CoreCmuFlrClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __val;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_CMU_CONFIG3);

	/* CMU Margin settings are only up to 15 bit, need to consider overflow */
	if(value >= 0x8000) { __val = 0x7FFF;	}
	else 				{ __val = value; __val &= 0x00007FFF;}


	/* Reset Field */
	__data &= (~HDMI21_SNPS_FIELD_FRLCLK_STABLE_FREQ_MARGIN);
	__data |= __val;

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_CMU_CONFIG3, __data);

	return;
}

void 	HDMI21_MISC_Rx_Set_CoreCmuEarcBpClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __val;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_CMU_CONFIG4);

	/* CMU Margin settings are only up to 15 bit, need to consider overflow */
	if(value >= 0x8000) { __val = 0x00007FFF;	}
	else 				{ __val = value; __val &= 0x00007FFF;}

	/* Bit shift */
	__val = __val << 16;

	/* Reset Field */
	__data &= (~HDMI21_SNPS_FIELD_EARC_BPCLK_STABLE_FREQ_MARGIN);
	__data |= __val;

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_CMU_CONFIG4, __data);

	return;

}

void 	HDMI21_MISC_Rx_Set_CoreCmuEarcAudClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32 __data, __val;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_CMU_CONFIG4);

	/* CMU Margin settings are only up to 15 bit, need to consider overflow */
	if(value >= 0x8000) { __val = 0x00007FFF;	}
	else 				{ __val = value; __val &= 0x00007FFF;}

	/* Reset Field */
	__data &= (~HDMI21_SNPS_FIELD_EARC_AUDCLK_STABLE_FREQ_MARGIN);
	__data |= __val;

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_CMU_CONFIG4, __data);

	return;
}

HDMI21_SNPS_CMU_STATUS_T HDMI21_MISC_Rx_Get_CoreCmuStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32  ret = 0xFFFFFFFF;

	/* Null Pointer Defence */
	if(_p == NULL) return (HDMI21_SNPS_CMU_STATUS_T)ret;

	/* Read Register */
	ret = _p->link_read(HDMI21_SNPS_REG_CMU_STATUS);

	return (HDMI21_SNPS_CMU_STATUS_T)ret;
}

UINT32	HDMI21_MISC_Rx_Get_CoreCmuAudClkFreq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32  ret = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Read Register */
	ret = _p->link_read(HDMI21_SNPS_REG_CMU_AUDCLK_FREQ);

	/* Mask other bit field */
	ret &= (HDMI21_SNPS_FIELD_AUDCLK_FREQ);

	return ret;
}

UINT32	HDMI21_MISC_Rx_Get_CoreCmuTmdsQpClkFreq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32  ret = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return ret;

	/* Read Register */
	ret = _p->link_read(HDMI21_SNPS_REG_CMU_TMDSQPCLK_FREQ);

	/* Mask other bit field */
	ret &= (HDMI21_SNPS_FIELD_TMDSQPCLK_FREQ);

	return ret;
}

void	HDMI21_MISC_Rx_Set_CoreCmuEnable(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool enable)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32  __data = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_CMU_MAIN_CONFIG);

	/* Mask other bit field */
	if(enable)	{	__data |= ( HDMI21_SNPS_FIELD_CMU_EN);	}
	else		{	__data &= (~HDMI21_SNPS_FIELD_CMU_EN);	}

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_CMU_MAIN_CONFIG, __data);

	return;
}


void 	HDMI21_MISC_Rx_Set_I2cSlaveSpikeSuppr(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32  __data = 0, __val = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_I2C_SLAVE_CONFIG0);

	/* Spike Suppresion setting is only up to 2 bit, need to consider overflow */
	if(value >= 0x4)	{ __val = 0x3;	}
	else				{ __val = value; __val &= 0x00003;}

	/* Bit shift */
	__val = __val << 8;

	/* Reset Field */
	__data &= (~HDMI21_SNPS_FIELD_I2C_SPIKE_SUPPR_QST);
	__data |= __val;

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_I2C_SLAVE_CONFIG0, __data);

	return;
}

void 	HDMI21_MISC_Rx_Set_I2cSlaveTimeOutEn(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool enable)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32  __data = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_I2C_SLAVE_CONFIG0);

	/* Set Field */
	if(enable)	{ __data |= ( HDMI21_SNPS_FIELD_I2C_TIMEOUT_EN_QST); }
	else		{ __data &= (~HDMI21_SNPS_FIELD_I2C_TIMEOUT_EN_QST); }

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_I2C_SLAVE_CONFIG0, __data);

	return;
}

void 	HDMI21_MISC_Rx_Set_I2cSlaveTimeOutCnt(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 value)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32  __data = 0, __val = 0;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_I2C_SLAVE_CONFIG0);

	/* Spike Suppresion setting is only up to 2 bit, need to consider overflow */
	if(value >= 0x8)	{ __val = 0x7;	}
	else				{ __val = value; __val &= 0x7;}

	/* Reset Field */
	__data &= (~HDMI21_SNPS_FIELD_I2C_TIMEOUT_CNT_QST);
	__data |= __val;

	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_I2C_SLAVE_CONFIG0, __data);

	return;

}

void	HDMI21_MISC_Rx_Set_I2cSlaveSdaHoldTime(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 holdOut, UINT32 holdIn)
{
	HDMI21_HAL_RX_DEVICE_DATA *_p = pDevHandler;
	UINT32  __data, __val_in, __val_out;

	/* Null Pointer Defence */
	if(_p == NULL) return;

	/* Read Register */
	__data = _p->link_read(HDMI21_SNPS_REG_I2C_SLAVE_CONFIG1);

	/* I2C Hold time setting is only up to 8 bit, need to consider overflow */
	if(holdOut >= 0x100)	{ __val_out = 0xFF;	}
	else					{ __val_out = holdOut; __val_out &= 0xFF;}

	if(holdIn >= 0x100)		{ __val_in = 0xFF;	}
	else					{ __val_in = holdIn; __val_in &= 0xFF;}

	/* Bit shift */
	__val_out = __val_out << 8;

	/* Reset Field */
	__data &= (~HDMI21_SNPS_FIELD_I2C_SDA_OUT_HOLD_VALUE_QST);
	__data &= (~HDMI21_SNPS_FIELD_I2C_SDA_IN_HOLD_VALUE_QST);
	
	__data |= __val_out;
	__data |= __val_in;


	/* Write Register */
	_p->link_write(HDMI21_SNPS_REG_I2C_SLAVE_CONFIG1, __data);

	return;
}


/*========================================================================================
 Static Function Implementation 
======================================================================================== */
static char *__rst_type_to_str(HDMI21_SNPS_RST_TYPE_T type)
{
	switch(type)
	{
		case HDMI21_SNPS_RST_MAIN:
			return "MAIN";
		case HDMI21_SNPS_RST_AVPUNIT:
			return "AVPUnit";
		case HDMI21_SNPS_RST_AUDIO:
			return "AUDIO";
		case HDMI21_SNPS_RST_HDCP:
			return "HDCP";
		case HDMI21_SNPS_RST_PKTFIFO:
			return "PKTFIFO";
		case HDMI21_SNPS_RST_DATAPATH:
			return "DATAPATH";
		case HDMI21_SNPS_RST_CEC:
			return "CEC";
		case HDMI21_SNPS_RST_APB:
			return "APB";
		case HDMI21_SNPS_RST_PHYCTRL:
			return "PHYCTRL";
		case HDMI21_SNPS_RST_EARCTX:
			return "EARCTX";
		case HDMI21_SNPS_RST_DATAPATHONLY:
			return "DATA ONLY";
		case HDMI21_SNPS_RST_HDCPQP:
			return "HDCPQP";
		default : 
			return "Unknown";
	}

}

