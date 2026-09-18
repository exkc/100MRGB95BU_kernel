/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   COPYRIGHT(c) 1998-2010 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work covered by this copyright hereon
 *   may be reproduced, stored in a retrieval system, in any form
 *   or by any means, electronic, mechanical, photocopying, recording
 *   or otherwise, without the prior written  permission of LG Electronics.
 *****************************************************************************/

/** @file hdmi20_kwarp.c
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		won.hur (won.hur@lge.com)
 *  @version	1.0
 *  @date		2018-04-18
 *  @note		Additional information.
 */

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	File Inclusions
------------------------------------------------------------------------------*/
#include <linux/string.h>
#include <linux/kthread.h>
#include "hdmi20_kwarp.h"
#include "hdmi20_module.h"

#include <linux/delay.h>
#include <linux/mutex.h>
#include "os_util.h"
/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	global Variables
------------------------------------------------------------------------------*/
int isKwarpHDMI20Open = -1;
int isKwarpHDMI20Initialized = -1;

int gKwarpNumberOfPorts = 0;
int gIsHDCP14RxRepeater = 0;
/*------------------------------------------------------------------------------
	Static Function Prototypes Declarations
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
	Static Variables
------------------------------------------------------------------------------*/


static UINT8 _gHDMI20_KWARP__OLD_TestPattern[] = {
0x3C, 0xA0, 0xF4, 0x66, 0xF4, 0x00, 0x00, 0x00, 0x9E, 0x5D, 0x57, 0xD4, 0xCD, 0xC7, 0x8B, 0xF5,
0x43, 0x1A, 0x60, 0x0E, 0x7F, 0x73, 0x0E, 0xBE, 0xF5, 0x4F, 0xA9, 0x5E, 0xBF, 0x5B, 0x46, 0xFB,
0xAC, 0x2C, 0x3B, 0x68, 0x8F, 0x4F, 0x84, 0x06, 0xD3, 0xE2, 0xF1, 0xA9, 0x4C, 0x4F, 0x64, 0xDD,
0x34, 0x1E, 0x85, 0x98, 0xF3, 0x26, 0x64, 0xC1, 0x16, 0x06, 0xCC, 0x51, 0x50, 0xD0, 0x8F, 0x81,
0xF7, 0xB9, 0x0D, 0xC0, 0x63, 0x41, 0x37, 0x08, 0x82, 0x14, 0x6D, 0x32, 0xE1, 0x92, 0x9D, 0xC2,
0xC1, 0x69, 0x4A, 0xF7, 0xA6, 0xDD, 0x27, 0x37, 0xF7, 0xFE, 0x28, 0x35, 0xBB, 0x07, 0x0F, 0xBE,
0x97, 0x83, 0x0E, 0x81, 0xA9, 0xC7, 0x39, 0xFE, 0x3D, 0xD1, 0x6A, 0xBC, 0x4A, 0x80, 0x77, 0x50,
0x87, 0x44, 0xFB, 0x3A, 0xCA, 0xE1, 0xFE, 0x01, 0xF2, 0xCF, 0x5F, 0x02, 0x37, 0xD5, 0x7B, 0x7B,
0xCA, 0x2F, 0x1F, 0x1C, 0x69, 0x72, 0x6E, 0x59, 0x77, 0xA8, 0x15, 0xCB, 0xF5, 0x8A, 0xBB, 0x88,
0x05, 0xE2, 0x41, 0x9E, 0x08, 0xBC, 0x34, 0x1D, 0xFF, 0x9E, 0xBE, 0x69, 0x47, 0x9C, 0xD4, 0x67,
0x3A, 0x32, 0xE6, 0x39, 0xBF, 0x44, 0x3D, 0x0D, 0xA5, 0x7A, 0xA1, 0x73, 0xD5, 0x0F, 0x31, 0x0F,
0x66, 0xB3, 0x45, 0x98, 0x76, 0x72, 0xA3, 0x73, 0x15, 0x9E, 0xAF, 0x48, 0xF4, 0x95, 0x38, 0x2F,
0x7F, 0xCC, 0x7C, 0x0C, 0x8E, 0x1B, 0x2D, 0x55, 0x15, 0x29, 0x2A, 0x96, 0x8A, 0x9D, 0xD3, 0x87,
0x21, 0xE8, 0x2D, 0x28, 0x49, 0xF0, 0x8F, 0xE1, 0x71, 0xBF, 0xAA, 0x58, 0x9F, 0x43, 0xD1, 0x11,
0x8B, 0xCF, 0x76, 0xAC, 0x38, 0xF0, 0x0D, 0x1A, 0x41, 0xD1, 0x5A, 0xEF, 0x44, 0x46, 0xBE, 0x5D,
0x09, 0x6E, 0x05, 0x71, 0x0A, 0xCC, 0x9A, 0x3D, 0x14, 0x86, 0xE9, 0xEA, 0xAF, 0xF4, 0x35, 0x1D,
0xCF, 0x94, 0x0A, 0x7F, 0xDB, 0x41, 0x21, 0x5D, 0xA6, 0xD5, 0x60, 0x88, 0xEA, 0x99, 0xBA, 0x9B,
0x6B, 0x4C, 0xBC, 0x22, 0xA2, 0x0C, 0x7F, 0x8F, 0x9B, 0xB4, 0x66, 0x45, 0x12, 0x10, 0xD9, 0x82
};

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/


/*========================================================================================
	Implementation Group
========================================================================================*/


/**
 * HDMI device open
 * @param 	void
 * @return 	int
 */
int KWARP_HDMI20_Open(void)
{
	int		ret = RET_ERROR;

	do{
		if(isKwarpHDMI20Open >= 1){
			printk("%s:%d : Ingnore mulitple Open\n", __FUNCTION__, __LINE__);
			ret = KWARP_HDMI20_RETURN_IGNORE_MULTIPLE_OPEN;
			ret = RET_OK;
			break;
		}

		/* Flag for indication */
		isKwarpHDMI20Open = 1;

		if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
		{
			gKwarpNumberOfPorts = HDMI21_NUM_OF_PORTS_E60;
		}
		else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
		{
			gKwarpNumberOfPorts = HDMI21_NUM_OF_PORTS_O20;
		}
		else{
			gKwarpNumberOfPorts = HDMI20_NUM_OF_RX_PORTS;
		}

		ret = HDMI20_Module_Open();

	} while(0);

	return ret;
}

int KWARP_HDMI20_Close(void)
{
	int		ret = RET_ERROR;

	do{
		/* Flag for indication */
		isKwarpHDMI20Open = 0;
		isKwarpHDMI20Initialized = 0;
	
		ret = RET_OK;
	} while(0);

	return ret;
}

/**
 * HDMI20 device check open status
 * @param void
 * @return int
 */
int KWARP_HDMI20_IsOpen(void)
{
	return isKwarpHDMI20Open;
}


int KWARP_HDMI20_RX_Initialize(void)
{
	int ret = RET_ERROR;
//	int i;


	do{
		if(isKwarpHDMI20Initialized >= 1){
			printk("%s:%d : Ingnore mulitple Init\n", __FUNCTION__, __LINE__);	
			ret = KWARP_HDMI20_RETURN_IGNORE_MULTIPLE_INIT;
			ret = RET_OK;
			break;
		}

		isKwarpHDMI20Initialized = 1;

		/* End */
		ret =HDMI20_Module_Initialize(NULL, 0, 1);
	
		#if 0 
		for(i=0;i<gKwarpNumberOfPorts;i++){
			ret |= KWARP_HDMI20_RX_HDCP14_TestMode(i);
		}
		#endif
	
	}while(0);

	return ret;   
}


int KWARP_HDMI20_RX_GetTimingInfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pTimingInfo, int isInternalCall)
{
	int ret = RET_ERROR;


	do{
		if(isKwarpHDMI20Open <= 0){
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_OPEN;
			break;
		}

		if(isKwarpHDMI20Initialized <= 0) {		
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_INIT; 
			break;
		}

		if(pTimingInfo == NULL){
			ret = KWARP_HDMI20_RETURN_DEVICE_NULL_POINTER;
			break;
		}

		/* Step . Check Ports */
		if( port >= gKwarpNumberOfPorts){
			ret = KWARP_HDMI20_RETURN_WRONG_PORT;
			break;
		}

		/* End */
		ret = HDMI20_Module_Get_TimingInfo(port, pTimingInfo, sizeof(LX_HDMI_TIMING_INFO_T), 1);
	
	}while(0);

	return ret;   
}

int KWARP_HDMI20_RX_GetColorDomain(UINT8 port, LX_HDMI_COLOR_STATUS_T *pColorDomain )
{
	int ret = RET_ERROR;
	LX_HDMI_COLOR_DOMAIN_T colorInfo;	


	do{
		if(isKwarpHDMI20Open <= 0){
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_OPEN;
			break;
		}

		if(isKwarpHDMI20Initialized <= 0) {		
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_INIT; 
			break;
		}

		if(pColorDomain == NULL){
			ret = KWARP_HDMI20_RETURN_DEVICE_NULL_POINTER;
			break;
		}

		/* Step . Check Ports */
		if( port >= gKwarpNumberOfPorts){
			ret = KWARP_HDMI20_RETURN_WRONG_PORT;
			break;
		}


		/* Step 2. Load cmd to send over to kernel */
		memset((void *)&colorInfo, 0, sizeof(LX_HDMI_COLOR_DOMAIN_T));

		ret = 	HDMI20_Module_Get_COLORInfo(port, &colorInfo, sizeof(LX_HDMI_COLOR_DOMAIN_T), 1);

		/* Step 5. Set User data based on driver status */
		if (colorInfo.bHdmiMode)
		{
			switch(colorInfo.ePixelEncoding)
			{
				case LX_HDMI_AVI_COLORSPACE_RGB:
					//if (colorInfo.eITContent == LX_HDMI_AVI_IT_CONTENT_ITCONTENT || colorInfo.eRGBQuantizationRange == LX_HDMI_AVI_RGB_QUANTIZATION_RANGE_FULL)
					if (colorInfo.eRGBQuantizationRange == LX_HDMI_AVI_RGB_QUANTIZATION_RANGE_FULL)
						*pColorDomain = LX_HDMI_CS_FULL_RGB;
					else if (colorInfo.eRGBQuantizationRange == LX_HDMI_AVI_RGB_QUANTIZATION_RANGE_LIMITED)
						*pColorDomain = LX_HDMI_CS_LIMITED_RGB;
					else
						*pColorDomain = LX_HDMI_CS_LIMITED_RGB;
					break;

				case LX_HDMI_AVI_COLORSPACE_YCBCR422:
					if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_ITU601)
						*pColorDomain = LX_HDMI_CS_YCBCR422_601;
					else if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_ITU709)
						*pColorDomain = LX_HDMI_CS_YCBCR422_709;
					else if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_EXTEND)
					{
						if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC601)
							*pColorDomain = LX_HDMI_CS_XVYCC422_601;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC709)
							*pColorDomain = LX_HDMI_CS_XVYCC422_709;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_BT2020CL)
							*pColorDomain = LX_HDMI_CS_YCBCR422_2020_CL;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_BT2020NCL)
							*pColorDomain = LX_HDMI_CS_YCBCR422_2020_NCL;
						else
							*pColorDomain = LX_HDMI_CS_YCBCR422_709;		// To do : checkif (ret < 0) return NOT_OK;
					}
					else
						*pColorDomain = LX_HDMI_CS_YCBCR422_601; // To do : check return NOT_OK;
					break;

				case LX_HDMI_AVI_COLORSPACE_YCBCR444:
					if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_ITU601)
						*pColorDomain = LX_HDMI_CS_YCBCR444_601;
					else if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_ITU709)
						*pColorDomain = LX_HDMI_CS_YCBCR444_709;
					else if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_EXTEND)
					{
						if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC601)
							*pColorDomain = LX_HDMI_CS_XVYCC444_601;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC709)
							*pColorDomain = LX_HDMI_CS_XVYCC444_709;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_BT2020CL)
							*pColorDomain = LX_HDMI_CS_YCBCR444_2020_CL;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_BT2020NCL)
							*pColorDomain = LX_HDMI_CS_YCBCR444_2020_NCL;
						else
							*pColorDomain = LX_HDMI_CS_YCBCR444_709;		// To do : check return NOT_OK;
					}
					else
						*pColorDomain = LX_HDMI_CS_YCBCR444_601; // To do : check return NOT_OK;
					break;
				case LX_HDMI_AVI_COLORSPACE_YCBCR420:
					if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_ITU601)
						*pColorDomain = LX_HDMI_CS_YCBCR420_601;
					else if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_ITU709)
						*pColorDomain = LX_HDMI_CS_YCBCR420_709;
					else if (colorInfo.eColorimetry ==  LX_HDMI_AVI_COLORIMETRY_EXTEND)
					{
						if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC601)
							*pColorDomain = LX_HDMI_CS_XVYCC420_601;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_XVYCC709)
							*pColorDomain = LX_HDMI_CS_XVYCC420_709;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_BT2020CL)
							*pColorDomain = LX_HDMI_CS_YCBCR420_2020_CL;
						else if (colorInfo.eExtColorimetry == LX_HDMI_AVI_EXT_COLORIMETRY_BT2020NCL)
							*pColorDomain = LX_HDMI_CS_YCBCR420_2020_NCL;
						else
							*pColorDomain = LX_HDMI_CS_YCBCR420_709;		// To do : check return NOT_OK;
					}
					else
						*pColorDomain = LX_HDMI_CS_YCBCR420_601; // To do : check return NOT_OK;
					break;

				default:
					*pColorDomain = LX_HDMI_CS_FULL_RGB;
					break;
			}
		}
		else
		{
			*pColorDomain = LX_DVI_CS_FULL_RGB;  // To do : support DVI Limited RGB ???
		}
		/* End */
		ret = RET_OK;
	}while(0);

	return ret;   
}

int KWARP_HDMI20_RX_GetAspectRatio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pAspectRatio )
{
	int ret = RET_ERROR;


	do{
		if(isKwarpHDMI20Open <= 0){
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_OPEN;
			break;
		}

		if(isKwarpHDMI20Initialized <= 0) {		
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_INIT; 
			break;
		}

		if(pAspectRatio == NULL){
			ret = KWARP_HDMI20_RETURN_DEVICE_NULL_POINTER;
			break;
		}

		/* Step . Check Ports */
		if( port >= gKwarpNumberOfPorts){
			ret = KWARP_HDMI20_RETURN_WRONG_PORT;
			break;
		}

		ret = HDMI20_Module_Get_AspectRatio(port, pAspectRatio, sizeof(LX_HDMI_ASPECTRATIO_T), 1);
	}while(0);

	return ret;   
}



int KWARP_HDMI20_RX_WriteHDCP14(UINT8 port, UINT8 *pData, int size, int isRepeater)
{
 	int ret = RET_ERROR;
	int i, copy_pointer;
	UINT32  data0, data1;
	LX_HDMI20_HDCP14_DATA_T params;


	do{
		if(isKwarpHDMI20Open <= 0) {
			printk("%s:%d : KWARP HDMI20 Not Opened\n", __FUNCTION__, __LINE__);	
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_OPEN;
			break;
		}

		if(isKwarpHDMI20Initialized <= 0) {		
			printk("%s:%d : KWARP HDMI20 Not Initiated\n", __FUNCTION__, __LINE__);
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_INIT; 
			break;
		}

		if(pData == NULL) {
			printk("%s:%d : Null Pointer\n", __FUNCTION__, __LINE__);
			ret = KWARP_HDMI20_RETURN_DEVICE_NULL_POINTER;
			break;
		}

		/* Step . Check Ports */
		if( port >= gKwarpNumberOfPorts) {
			printk("%s:%d : Wrong Port[%d]\n", __FUNCTION__, __LINE__, port);
			ret = KWARP_HDMI20_RETURN_WRONG_PORT;
			break;
		}

		/* Step 1. Check size */
		if(size != HDMI20_HDCP_CUSTOMER_SIZE) {
			printk("%s:%d : Wrong Sort[0x%x]\n", __FUNCTION__, __LINE__, size);
			ret = KWARP_HDMI20_RETURN_WRONG_DATA;
			break;
		}

		/* Step 2. Initiate memory */
		memset(&params, 0, sizeof(LX_HDMI20_HDCP14_DATA_T));

		params.repeat = 0;
		params.seed = 0x0000a55a;

		/* Copy BKSV */
		memcpy((UINT32 *)&params.bksv, (UINT32 *)pData, (sizeof(UINT32) *2));

		/* Copy Key */
		copy_pointer = (sizeof(UINT32) * 2);
		for(i=0; i<HDMI20_HDCP_KEYS_SIZE; i=i+2){
			memcpy((void *)&data0, (void *)((unsigned long long)pData + copy_pointer), 4);
			copy_pointer += 4;
			memcpy((void *)&data1, (void *)((unsigned long long)pData + copy_pointer), 3); 
			copy_pointer += 3;

			data1 &= 0x00FFFFFF;

			params.keys[i]   = data0;
			params.keys[i+1] = data1;
		}

		if(isRepeater > 0){
			params.repeat = 1;
		}
		else{
			params.repeat = 0;
		}


		/* End */
		ret = HDMI20_Module_Set_HDCP14(port, (UINT32 *)&params, sizeof(LX_HDMI20_HDCP14_DATA_T), 1);
		if(ret < 0) printk("[%s:%d] Return Error from HDCP14 set\n", __FUNCTION__, __LINE__);
	}while(0);

	return ret;
}

int KWARP_HDMI20_RX_HDCP14_TestMode(UINT8 mode)
{
	int ret;
	UINT8 *pData = &_gHDMI20_KWARP__OLD_TestPattern[0];
	int size = sizeof(_gHDMI20_KWARP__OLD_TestPattern); 

	ret = KWARP_HDMI20_RX_WriteHDCP14( 0, pData, size, (int)mode);

	return ret;
}

int KWARP_HDMI20_RX_Set_ExecuteDscModule(UINT8 port)
{
	int ret = RET_ERROR;

	do{ 
		if(isKwarpHDMI20Open <= 0){
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_OPEN;
			break;
		}

		if(isKwarpHDMI20Initialized <= 0) {		
			ret = KWARP_HDMI20_RETURN_DEVICE_NOT_INIT; 
			break;
		}

		if( port >= gKwarpNumberOfPorts){
			ret = KWARP_HDMI20_RETURN_WRONG_PORT;
			break;
		}

		ret = HDMI20_Module_Set_ExecuteDscMode(port);

	} while(0);

	return ret;
}
