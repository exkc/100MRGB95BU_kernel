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
 *  @author     won.hur
 *  @version    1.0
 *  @date       2019-04-01
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_SNPS_VMON_H_
#define	_HDMI21_RX_SNPS_VMON_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/**
 * Bit field mask
 * @param m	width
 * @param n shift
 */
#ifndef MSK
#define MSK(m, n)		(((1 << (m)) - 1) << (n))
#endif

/**
 * Bit mask
 * @param n shift
 */
#ifndef BIT
#define BIT(n)			MSK(1, (n))
#endif


#define HDMI21_SNPS_REG_VMON_CONTROL				(0x1560)
#define HDMI21_SNPS_FIELD_VMON_SOURCE_SEL			MSK(3, 28)
#define HDMI21_SNPS_FIELD_VMON_IRQ_THR_MODE			BIT(24)
#define HDMI21_SNPS_FIELD_VMON_DATAEN_DIPH_SEL		MSK(3, 16)
#define HDMI21_SNPS_FIELD_VMON_VSYNC_DIPH_SEL		MSK(3, 8)
#define HDMI21_SNPS_FIELD_VMON_HSYNC_DIPH_SEL		MSK(3, 0)


#define HDMI21_SNPS_REG_VMON_STATUS1				(0x1580)
#define HDMI21_SNPS_FIELD_VMON_HSYNCWIDTH			MSK(16, 16)
#define HDMI21_SNPS_FIELD_VMON_HFRONT				MSK(16, 0)

#define HDMI21_SNPS_REG_VMON_STATUS2				(0x1584)
#define HDMI21_SNPS_FIELD_VMON_HBLANK				MSK(16, 16)
#define HDMI21_SNPS_FIELD_VMON_HBACK				MSK(16, 0)

#define HDMI21_SNPS_REG_VMON_STATUS3				(0x1588)
#define HDMI21_SNPS_FIELD_VMON_HTOTAL				MSK(16, 16)
#define HDMI21_SNPS_FIELD_VMON_HACTIVE				MSK(16, 0)

#define HDMI21_SNPS_REG_VMON_STATUS4				(0x158C)
#define HDMI21_SNPS_FIELD_VMON_VSYNCWIDTH			MSK(16, 16)
#define HDMI21_SNPS_FIELD_VMON_VFRONT				MSK(16, 0)

#define HDMI21_SNPS_REG_VMON_STATUS5				(0x1590)
#define HDMI21_SNPS_FIELD_VMON_VBLANK				MSK(16, 16)
#define HDMI21_SNPS_FIELD_VMON_VBACK				MSK(16, 0)

#define HDMI21_SNPS_REG_VMON_STATUS6				(0x1594)
#define HDMI21_SNPS_FIELD_VMON_VTOTAL				MSK(16, 16)
#define HDMI21_SNPS_FIELD_VMON_VACTIVE				MSK(16, 0)

#define HDMI21_SNPS_REG_VMON_STATUS7				(0x1598)
#define HDMI21_SNPS_FIELD_VMON_FIELD_DETECT			BIT(0)
#define HDMI21_SNPS_FIELD_VMON_ILACE_DETECT			BIT(4)	
#define HDMI21_SNPS_FIELD_VMON_ALT_DETECT			BIT(8)



	
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{	
	bool isEvenFrame;
	bool isInterlaced;
	bool isField1;
	UINT32 hsync;
	UINT32 hfront;
	UINT32 hblank;
	UINT32 hback;
	UINT32 htotal;
	UINT32 hactive;
	UINT32 vsync;
	UINT32 vfront;
	UINT32 vblank;
	UINT32 vback;
	UINT32 vtotal;
	UINT32 vactive;
} HDMI21_VMON_VIDEO_SYNC_T;


	
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void HDMI21_VMON_Rx_Set_Initiate(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int sourceType);
void HDMI21_VMON_Rx_Get_VideoSync(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_VMON_VIDEO_SYNC_T *pData);
void HDMI21_VMON_Rx_Set_InsertVideoSyncToHandler(HDMI21_VMON_VIDEO_SYNC_T *pData, HDMI21_HAL_VIDEO_TIMING_T *pDest);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

