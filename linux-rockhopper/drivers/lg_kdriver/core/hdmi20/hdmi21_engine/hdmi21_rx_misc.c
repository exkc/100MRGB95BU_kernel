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
#include <linux/interrupt.h>
#include <linux/delay.h>
#include "../hdmi20_drv.h" 			/* For debug prints */
#include "hdmi21_hal_driver.h"		/* Device Handler */
#include "hdmi21_rx_irq.h"   		/* To map IRQ register to function pointers */
#include "hdmi21_rx_misc.h"

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
static UINT32 __HDMI21_HAL_Rx_PhyPDC_Read(UINT8 port, UINT32 addr);
static void   __HDMI21_HAL_Rx_PhyPDC_Write(UINT8 port, UINT32 addr, UINT32 data);
static UINT32 __HDMI21_HAL_Rx_PhyDR_Read(UINT8 port, UINT32 addr);
static void   __HDMI21_HAL_Rx_PhyDR_Write(UINT8 port, UINT32 addr, UINT32 data);
static UINT32 __HDMI21_HAL_Rx_ALED_Read(UINT8 port, UINT32 addr);
static void   __HDMI21_HAL_Rx_ALED_Write(UINT8 port, UINT32 addr, UINT32 data);
static UINT32 __HDMI21_HAL_Rx_TOP_Read(UINT8 port, UINT32 addr);
static void   __HDMI21_HAL_Rx_TOP_Write(UINT8 port, UINT32 addr, UINT32 data);
static UINT32 __HDMI21_HAL_Rx_LINK_Read(UINT8 port, UINT32 addr);
static void __HDMI21_HAL_Rx_LINK_Write(UINT8 port, UINT32 addr, UINT32 data);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern HDMI21_HAL_RX_DEVICE_DATA 	gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern HDMI20_DEV_CONTROL_T		gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
UINT32 *_pDevApbMask = &gHDMI21RxDevVideoControler[HDMI21__LINK_DISABLE_APB_ACCESS].value;


/* 2020/09/25 : CTA-861-G */
HDMI21_MISC_VIC_TABLE_T gHdmi21CtaTable[HDMI21_MISC_CTA861G_IDX_CNT] =
{
	{1,640,480,0,800,160,525,45,60,16,96,48,10,2,33},
	{2,720,480,0,858,138,525,45,60,16,62,60,9,6,30},
	{3,720,480,0,858,138,525,45,60,16,62,60,9,6,30},
	{4,1280,720,0,1650,370,750,30,60,110,40,220,5,5,20},
	{5,1920,1080,1,2200,280,1125,22.51,60,88,44,148,2,5,15},
	{6,1440,480,1,17162,276,525,22.51,60,38,124,114,4,3,15},
	{7,1440,480,1,17162,276,525,22.51,60,38,124,114,4,3,15},
	{8,1440,240,0,17162,276,262,22,60,38,124,114,4,3,15},
	{9,1440,240,0,17162,276,262,22,60,38,124,114,4,3,15},
	{10,2880,480,1,34322,552,525,22.51,60,76,248,228,4,3,15},
	{11,2880,480,1,34322,552,525,22.51,60,76,248,228,4,3,15},
	{12,2880,240,0,34322,552,262,22,60,76,248,228,4,3,15},
	{13,2880,240,0,34322,552,262,22,60,76,248,228,4,3,15},
	{14,1440,480,0,17162,276,525,45,60,32,124,120,9,6,30},
	{15,1440,480,0,17162,276,525,45,60,32,124,120,9,6,30},
	{16,1920,1080,0,2200,280,1125,45,60,88,44,148,4,5,36},
	{17,720,576,0,864,144,625,49,50,12,64,68,5,5,39},
	{18,720,576,0,864,144,625,49,50,12,64,68,5,5,39},
	{19,1280,720,0,1980,700,750,30,50,440,40,220,5,5,20},
	{20,1920,1080,1,2640,720,1125,22.51,50,528,44,148,2,5,15},
	{21,1440,576,1,17282,288,625,24.51,50,24,126,138,2,3,19},
	{22,1440,576,1,17282,288,625,24.51,50,24,126,138,2,3,19},
	{23,1440,288,0,17282,288,312,24,50,24,126,138,2,3,19},
	{24,1440,288,0,17282,288,312,24,50,24,126,138,2,3,19},
	{25,2880,576,1,34562,576,625,24.51,50,48,252,276,2,3,19},
	{26,2880,576,1,34562,576,625,24.51,50,48,252,276,2,3,19},
	{27,2880,288,0,34562,576,312,24,50,48,252,276,2,3,19},
	{28,2880,288,0,34562,576,312,24,50,48,252,276,2,3,19},
	{29,1440,576,0,17282,288,625,49,50,24,128,136,5,5,39},
	{30,1440,576,0,17282,288,625,49,50,24,128,136,5,5,39},
	{31,1920,1080,0,2640,720,1125,45,50,528,44,148,4,5,36},
	{32,1920,1080,0,2750,830,1125,45,24,638,44,148,4,5,36},
	{33,1920,1080,0,2640,720,1125,45,25,528,44,148,4,5,36},
	{34,1920,1080,0,2200,280,1125,45,30,88,44,148,4,5,36},
	{35,2880,480,0,34322,552,525,45,60,64,248,240,9,6,30},
	{36,2880,480,0,34322,552,525,45,60,64,248,240,9,6,30},
	{37,2880,576,0,34562,576,625,49,50,48,256,272,5,5,39},
	{38,2880,576,0,34562,576,625,49,50,48,256,272,5,5,39},
	{39,1920,1080,1,2304,384,1250,85,50,32,168,184,23,5,57},
	{40,1920,1080,1,2640,720,1125,22.51,100,528,44,148,2,5,15},
	{41,1280,720,0,1980,700,750,30,100,440,40,220,5,5,20},
	{42,720,576,0,864,144,625,49,100,12,64,68,5,5,39},
	{43,720,576,0,864,144,625,49,100,12,64,68,5,5,39},
	{44,1440,576,1,17282,288,625,24.51,100,24,126,138,2,3,19},
	{45,1440,576,1,17282,288,625,24.51,100,24,126,138,2,3,19},
	{46,1920,1080,1,2200,280,1125,22.51,120,88,44,148,2,5,15},
	{47,1280,720,0,1650,370,750,30,120,110,40,220,5,5,20},
	{48,720,480,0,858,138,525,45,120,16,62,60,9,6,30},
	{49,720,480,0,858,138,525,45,120,16,62,60,9,6,30},
	{50,1440,480,1,17162,276,525,22.51,120,38,124,114,4,3,15},
	{51,1440,480,1,17162,276,525,22.51,120,38,124,114,4,3,15},
	{52,720,576,0,864,144,625,49,200,12,64,68,5,5,39},
	{53,720,576,0,864,144,625,49,200,12,64,68,5,5,39},
	{54,14402,576,1,17282,288,625,24.51,200,24,126,138,2,3,19},
	{55,14402,576,1,17282,288,625,24.51,200,24,126,138,2,3,19},
	{56,720,480,0,858,138,525,45,240,16,62,60,9,6,30},
	{57,720,480,0,858,138,525,45,240,16,62,60,9,6,30},
	{58,14402,480,1,17162,276,525,22.51,240,38,124,114,4,3,15},
	{59,14402,480,1,17162,276,525,22.51,240,38,124,114,4,3,15},
	{60,1280,720,0,3300,2020,750,30,24,1760,40,220,5,5,20},
	{61,1280,720,0,3960,2680,750,30,25,2420,40,220,5,5,20},
	{62,1280,720,0,3300,2020,750,30,30,1760,40,220,5,5,20},
	{63,1920,1080,0,2200,280,1125,45,120,88,44,148,4,5,36},
	{64,1920,1080,0,2640,720,1125,45,100,528,44,148,4,5,36},
	{65,1280,720,0,3300,2020,750,30,24,1760,40,220,5,5,20},
	{66,1280,720,0,3960,2680,750,30,25,2420,40,220,5,5,20},
	{67,1280,720,0,3300,2020,750,30,30,1760,40,220,5,5,20},
	{68,1280,720,0,1980,700,750,30,50,440,40,220,5,5,20},
	{69,1280,720,0,1650,370,750,30,60,110,40,220,5,5,20},
	{70,1280,720,0,1980,700,750,30,100,440,40,220,5,5,20},
	{71,1280,720,0,1650,370,750,30,120,110,40,220,5,5,20},
	{72,1920,1080,0,2750,830,1125,45,24,638,44,148,4,5,36},
	{73,1920,1080,0,2640,720,1125,45,25,528,44,148,4,5,36},
	{74,1920,1080,0,2200,280,1125,45,30,88,44,148,4,5,36},
	{75,1920,1080,0,2640,720,1125,45,50,528,44,148,4,5,36},
	{76,1920,1080,0,2200,280,1125,45,60,88,44,148,4,5,36},
	{77,1920,1080,0,2640,720,1125,45,100,528,44,148,4,5,36},
	{78,1920,1080,0,2200,280,1125,45,120,88,44,148,4,5,36},
	{79,1680,720,0,3300,1620,750,30,24,1360,40,220,5,5,20},
	{80,1680,720,0,3168,1488,750,30,25,1228,40,220,5,5,20},
	{81,1680,720,0,2640,960,750,30,30,700,40,220,5,5,20},
	{82,1680,720,0,2200,520,750,30,50,260,40,220,5,5,20},
	{83,1680,720,0,2200,520,750,30,60,260,40,220,5,5,20},
	{84,1680,720,0,2000,320,825,105,100,60,40,220,5,5,95},
	{85,1680,720,0,2000,320,825,105,120,60,40,220,5,5,95},
	{86,2560,1080,0,3750,1190,1100,20,24,998,44,148,4,5,11},
	{87,2560,1080,0,3200,640,1125,45,25,448,44,148,4,5,36},
	{88,2560,1080,0,3520,960,1125,45,30,768,44,148,4,5,36},
	{89,2560,1080,0,3300,740,1125,45,50,548,44,148,4,5,36},
	{90,2560,1080,0,3000,440,1100,20,60,248,44,148,4,5,11},
	{91,2560,1080,0,2970,410,1250,170,100,218,44,148,4,5,161},
	{92,2560,1080,0,3300,740,1250,170,120,548,44,148,4,5,161},
	{93,3840,2160,0,5500,1660,2250,90,24,1276,88,296,8,10,72},
	{94,3840,2160,0,5280,1440,2250,90,25,1056,88,296,8,10,72},
	{95,3840,2160,0,4400,560,2250,90,30,176,88,296,8,10,72},
	{96,3840,2160,0,5280,1440,2250,90,50,1056,88,296,8,10,72},
	{97,3840,2160,0,4400,560,2250,90,60,176,88,296,8,10,72},
	{98,4096,2160,0,5500,1404,2250,90,24,1020,88,296,8,10,72},
	{99,4096,2160,0,5280,1184,2250,90,25,968,88,128,8,10,72},
	{100,4096,2160,0,4400,304,2250,90,30,88,88,128,8,10,72},
	{101,4096,2160,0,5280,1184,2250,90,50,968,88,128,8,10,72},
	{102,4096,2160,0,4400,304,2250,90,60,88,88,128,8,10,72},
	{103,3840,2160,0,5500,1660,2250,90,24,1276,88,296,8,10,72},
	{104,3840,2160,0,5280,1440,2250,90,25,1056,88,296,8,10,72},
	{105,3840,2160,0,4400,560,2250,90,30,176,88,296,8,10,72},
	{106,3840,2160,0,5280,1440,2250,90,50,1056,88,296,8,10,72},
	{107,3840,2160,0,4400,560,2250,90,60,176,88,296,8,10,72},
	{108,1280,720,0,2500,1220,750,30,48,960,40,220,5,5,20},
	{109,1280,720,0,2500,1220,750,30,48,960,40,220,5,5,20},
	{110,1680,720,0,2750,1070,750,30,48,810,40,220,5,5,20},
	{111,1920,1080,0,2750,830,1125,45,48,638,44,148,4,5,36},
	{112,1920,1080,0,2750,830,1125,45,48,638,44,148,4,5,36},
	{113,2560,1080,0,3750,1190,1100,20,48,998,44,148,4,5,11},
	{114,3840,2160,0,5500,1660,2250,90,48,1276,88,296,8,10,72},
	{115,4096,2160,0,5500,1404,2250,90,48,1020,88,296,8,10,72},
	{116,3840,2160,0,5500,1660,2250,90,48,1276,88,296,8,10,72},
	{117,3840,2160,0,5280,1440,2250,90,100,1056,88,296,8,10,72},
	{118,3840,2160,0,4400,560,2250,90,120,176,88,296,8,10,72},
	{119,3840,2160,0,5280,1440,2250,90,100,1056,88,296,8,10,72},
	{120,3840,2160,0,4400,560,2250,90,120,176,88,296,8,10,72},
	{121,5120,2160,0,7500,2380,2200,40,24,1996,88,296,8,10,22},
	{122,5120,2160,0,7200,2080,2200,40,25,1696,88,296,8,10,22},
	{123,5120,2160,0,6000,880,2200,40,30,664,88,128,8,10,22},
	{124,5120,2160,0,6250,1130,2475,315,48,746,88,296,8,10,297},
	{125,5120,2160,0,6600,1480,2250,90,50,1096,88,296,8,10,72},
	{126,5120,2160,0,5500,380,2250,90,60,164,88,128,8,10,72},
	{127,5120,2160,0,6600,1480,2250,90,100,1096,88,296,8,10,72},
	{193,5120,2160,0,5500,380,2250,90,120,164,88,128,8,10,72},
	{194,7680,4320,0,11000,3320,4500,180,24,2552,176,592,16,20,144},
	{195,7680,4320,0,10800,3120,4400,80,25,2352,176,592,16,20,44},
	{196,7680,4320,0,9000,1320,4400,80,30,552,176,592,16,20,44},
	{197,7680,4320,0,11000,3320,4500,180,48,2552,176,592,16,20,144},
	{198,7680,4320,0,10800,3120,4400,80,50,2352,176,592,16,20,44},
	{199,7680,4320,0,9000,1320,4400,80,60,552,176,592,16,20,44},
	{200,7680,4320,0,10560,2880,4500,180,100,2112,176,592,16,20,144},
	{201,7680,4320,0,8800,1120,4500,180,120,352,176,592,16,20,144},
	{202,7680,4320,0,11000,3320,4500,180,24,2552,176,592,16,20,144},
	{203,7680,4320,0,10800,3120,4400,80,25,2352,176,592,16,20,44},
	{204,7680,4320,0,9000,1320,4400,80,30,552,176,592,16,20,44},
	{205,7680,4320,0,11000,3320,4500,180,48,2552,176,592,16,20,144},
	{206,7680,4320,0,10800,3120,4400,80,50,2352,176,592,16,20,44},
	{207,7680,4320,0,9000,1320,4400,80,60,552,176,592,16,20,44},
	{208,7680,4320,0,10560,2880,4500,180,100,2112,176,592,16,20,144},
	{209,7680,4320,0,8800,1120,4500,180,120,352,176,592,16,20,144},
	{210,10240,4320,0,12500,2260,4950,630,24,1492,176,592,16,20,594},
	{211,10240,4320,0,13500,3260,4400,80,25,2492,176,592,16,20,44},
	{212,10240,4320,0,11000,760,4500,180,30,288,176,296,16,20,144},
	{213,10240,4320,0,12500,2260,4950,630,48,1492,176,592,16,20,594},
	{214,10240,4320,0,13500,3260,4400,80,50,2492,176,592,16,20,44},
	{215,10240,4320,0,11000,760,4500,180,60,288,176,296,16,20,144},
	{216,10240,4320,0,13200,2960,4500,180,100,2192,176,592,16,20,144},
	{217,10240,4320,0,11000,760,4500,180,120,288,176,296,16,20,144},
	{218,4096,2160,0,5280,1184,2250,90,100,800,88,296,8,10,72},
	{219,4096,2160,0,4400,304,2250,90,120,88,88,128,8,10,72}
};
/*----------------------------------------------------------------------------------------
	Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
irqreturn_t HDMI21_HAL_RX0_Top_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Top_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT0, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX1_Top_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Top_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT1, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX2_Top_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Top_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT2, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX3_Top_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Top_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT3, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX4_Top_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Top_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT4, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX0_Link_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Link_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT0, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX1_Link_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Link_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT1, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX2_Link_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Link_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT2, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX3_Link_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Link_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT3, irq, dev_id, regs);
}

irqreturn_t HDMI21_HAL_RX4_Link_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	return HDMI21_IRQ_Rx_Link_IRQ_Handler(HDMI21_HAL_LINK_DEVICE_ID_PORT4, irq, dev_id, regs);
}

UINT32 HDMI21_HAL_Rx_TOP_Read_Port0(UINT32 addr)
{
	return __HDMI21_HAL_Rx_TOP_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr);
}

UINT32 HDMI21_HAL_Rx_TOP_Read_Port1(UINT32 addr)
{
	return __HDMI21_HAL_Rx_TOP_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr);
}

UINT32 HDMI21_HAL_Rx_TOP_Read_Port2(UINT32 addr)
{
	return __HDMI21_HAL_Rx_TOP_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr);
}

UINT32 HDMI21_HAL_Rx_TOP_Read_Port3(UINT32 addr)
{
	return __HDMI21_HAL_Rx_TOP_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr);
}

UINT32 HDMI21_HAL_Rx_TOP_Read_Port4(UINT32 addr)
{
	return __HDMI21_HAL_Rx_TOP_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr);
}


void   HDMI21_HAL_Rx_TOP_Write_Port0(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_TOP_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr, data);
}

void   HDMI21_HAL_Rx_TOP_Write_Port1(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_TOP_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr, data);

}

void   HDMI21_HAL_Rx_TOP_Write_Port2(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_TOP_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr, data);

}

void   HDMI21_HAL_Rx_TOP_Write_Port3(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_TOP_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr, data);
}

void   HDMI21_HAL_Rx_TOP_Write_Port4(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_TOP_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr, data);
}

UINT32 HDMI21_HAL_Rx_ALED_Read_Port0(UINT32 addr)
{
	return __HDMI21_HAL_Rx_ALED_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr);
}

UINT32 HDMI21_HAL_Rx_ALED_Read_Port1(UINT32 addr)
{
	return __HDMI21_HAL_Rx_ALED_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr);
}

UINT32 HDMI21_HAL_Rx_ALED_Read_Port2(UINT32 addr)
{
	return __HDMI21_HAL_Rx_ALED_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr);
}

UINT32 HDMI21_HAL_Rx_ALED_Read_Port3(UINT32 addr)
{
	return __HDMI21_HAL_Rx_ALED_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr);
}

UINT32 HDMI21_HAL_Rx_ALED_Read_Port4(UINT32 addr)
{
	return __HDMI21_HAL_Rx_ALED_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr);
}


void   HDMI21_HAL_Rx_ALED_Write_Port0(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_ALED_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr, data);
}

void   HDMI21_HAL_Rx_ALED_Write_Port1(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_ALED_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr, data);
}

void   HDMI21_HAL_Rx_ALED_Write_Port2(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_ALED_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr, data);
}

void   HDMI21_HAL_Rx_ALED_Write_Port3(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_ALED_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr, data);
}

void   HDMI21_HAL_Rx_ALED_Write_Port4(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_ALED_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr, data);
}

UINT32 HDMI21_HAL_Rx_LINK_Read_Port0(UINT32 addr)
{
	return __HDMI21_HAL_Rx_LINK_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr);
}

UINT32 HDMI21_HAL_Rx_LINK_Read_Port1(UINT32 addr)
{
	return __HDMI21_HAL_Rx_LINK_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr);
}

UINT32 HDMI21_HAL_Rx_LINK_Read_Port2(UINT32 addr)
{
	return __HDMI21_HAL_Rx_LINK_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr);
}

UINT32 HDMI21_HAL_Rx_LINK_Read_Port3(UINT32 addr)
{
	return __HDMI21_HAL_Rx_LINK_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr);
}

UINT32 HDMI21_HAL_Rx_LINK_Read_Port4(UINT32 addr)
{
	return __HDMI21_HAL_Rx_LINK_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr);
}


void HDMI21_HAL_Rx_LINK_Write_Port0(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_LINK_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr, data);
}

void HDMI21_HAL_Rx_LINK_Write_Port1(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_LINK_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr, data);
}

void HDMI21_HAL_Rx_LINK_Write_Port2(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_LINK_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr, data);
}

void HDMI21_HAL_Rx_LINK_Write_Port3(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_LINK_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr, data);
}

void HDMI21_HAL_Rx_LINK_Write_Port4(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_LINK_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr, data);
}

void HDMI21_HAL_RX0_Enable_Top_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Top_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT0, bOnOff);
}

void HDMI21_HAL_RX1_Enable_Top_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Top_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT1, bOnOff);
}

void HDMI21_HAL_RX2_Enable_Top_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Top_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT2, bOnOff);
}

void HDMI21_HAL_RX3_Enable_Top_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Top_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT3, bOnOff);
}

void HDMI21_HAL_RX4_Enable_Top_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Top_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT4, bOnOff);
}

void HDMI21_HAL_RX0_Enable_Link_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Link_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT0, bOnOff);
}

void HDMI21_HAL_RX1_Enable_Link_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Link_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT1, bOnOff);
}

void HDMI21_HAL_RX2_Enable_Link_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Link_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT2, bOnOff);
}

void HDMI21_HAL_RX3_Enable_Link_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Link_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT3, bOnOff);
}

void HDMI21_HAL_RX4_Enable_Link_IRQ(int bOnOff)
{
	HDMI21_IRQ_Rx_Enable_Link_IRQ(HDMI21_HAL_LINK_DEVICE_ID_PORT4, bOnOff);
}

UINT32 HDMI21_HAL_Rx_PhyPDC_Read_Port0(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyPDC_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr);
}

UINT32 HDMI21_HAL_Rx_PhyPDC_Read_Port1(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyPDC_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr);
}

UINT32 HDMI21_HAL_Rx_PhyPDC_Read_Port2(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyPDC_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr);
}

UINT32 HDMI21_HAL_Rx_PhyPDC_Read_Port3(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyPDC_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr);
}

UINT32 HDMI21_HAL_Rx_PhyPDC_Read_Port4(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyPDC_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr);
}


void   HDMI21_HAL_Rx_PhyPDC_Write_Port0(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyPDC_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr, data);
}

void   HDMI21_HAL_Rx_PhyPDC_Write_Port1(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyPDC_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr, data);
}

void   HDMI21_HAL_Rx_PhyPDC_Write_Port2(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyPDC_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr, data);
}

void   HDMI21_HAL_Rx_PhyPDC_Write_Port3(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyPDC_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr, data);
}

void   HDMI21_HAL_Rx_PhyPDC_Write_Port4(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyPDC_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr, data);
}

UINT32 HDMI21_HAL_Rx_PhyDR_Read_Port0(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyDR_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr);
}

UINT32 HDMI21_HAL_Rx_PhyDR_Read_Port1(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyDR_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr);
}

UINT32 HDMI21_HAL_Rx_PhyDR_Read_Port2(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyDR_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr);
}

UINT32 HDMI21_HAL_Rx_PhyDR_Read_Port3(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyDR_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr);
}

UINT32 HDMI21_HAL_Rx_PhyDR_Read_Port4(UINT32 addr)
{
	return __HDMI21_HAL_Rx_PhyDR_Read(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr);
}


void   HDMI21_HAL_Rx_PhyDR_Write_Port0(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyDR_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT0, addr, data);
}

void   HDMI21_HAL_Rx_PhyDR_Write_Port1(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyDR_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT1, addr, data);
}

void   HDMI21_HAL_Rx_PhyDR_Write_Port2(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyDR_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT2, addr, data);
}

void   HDMI21_HAL_Rx_PhyDR_Write_Port3(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyDR_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT3, addr, data);
}

void   HDMI21_HAL_Rx_PhyDR_Write_Port4(UINT32 addr, UINT32 data)
{
	__HDMI21_HAL_Rx_PhyDR_Write(HDMI21_HAL_LINK_DEVICE_ID_PORT4, addr, data);
}

/*========================================================================================
 Static Function Implementation 
======================================================================================== */
static UINT32 __HDMI21_HAL_Rx_PhyPDC_Read(UINT8 port, UINT32 addr)
{
	UINT32 ret;

	/* PDB Defence Code : PHY Registers are I2C/APB bridged */
	if(gHDMI21RxHandler[port].is5Vconnected == 0) { return 0xDEAD;}

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_PHYPDC) != 0) { return 0; }

	if(gHDMI21RxHandler[port].phyPdcMem.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].phyPdcMem.pSwAddr + (uintptr_t)addr)));
		//HDMI20_INFO("PHY PDC[0x%x]->[0x%x]\n", addr, ret);
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI21_HAL_Rx_PhyPDC_Write(UINT8 port, UINT32 addr, UINT32 data)
{
	UINT32* dest;

	/* PDB Defence Code : PHY Registers are I2C/APB bridged */
	if(gHDMI21RxHandler[port].is5Vconnected == 0) { return; } 

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_PHYPDC) != 0) { return; }

	if(gHDMI21RxHandler[port].phyPdcMem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].phyPdcMem.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}

static UINT32 __HDMI21_HAL_Rx_PhyDR_Read(UINT8 port, UINT32 addr)
{
	UINT32 ret;

	/* PDB Defence Code : PHY Registers are I2C/APB bridged */
	if(gHDMI21RxHandler[port].is5Vconnected == 0) { return 0xDEAD;}

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_PHYPOSTDR) != 0) { return 0; }

	if(gHDMI21RxHandler[port].phyPostDrMem.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].phyPostDrMem.pSwAddr + (uintptr_t)addr)));
		//HDMI20_INFO("PHY DR[0x%x]->[0x%x]\n", addr, ret);
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI21_HAL_Rx_PhyDR_Write(UINT8 port, UINT32 addr, UINT32 data)
{
	UINT32* dest;

	/* PDB Defence Code : PHY Registers are I2C/APB bridged */
	if(gHDMI21RxHandler[port].is5Vconnected == 0) { return; }

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_PHYPOSTDR) != 0) { return; }

	if(gHDMI21RxHandler[port].phyPostDrMem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].phyPostDrMem.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}


static UINT32 __HDMI21_HAL_Rx_ALED_Read(UINT8 port, UINT32 addr)
{
	UINT32 ret;

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_ALED) != 0) { return 0; }

	if(gHDMI21RxHandler[port].aledMem.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].aledMem.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI21_HAL_Rx_ALED_Write(UINT8 port, UINT32 addr, UINT32 data)
{
	UINT32* dest;

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_ALED) != 0) { return; }

	if(gHDMI21RxHandler[port].aledMem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].aledMem.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}


static UINT32 __HDMI21_HAL_Rx_TOP_Read(UINT8 port, UINT32 addr)
{
	UINT32 ret;

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_TOP) != 0) { return 0; }

	if(gHDMI21RxHandler[port].topMem.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].topMem.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void   __HDMI21_HAL_Rx_TOP_Write(UINT8 port, UINT32 addr, UINT32 data)
{
	UINT32* dest;

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_TOP) != 0) { return; }

	if(gHDMI21RxHandler[port].topMem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].topMem.pSwAddr + (uintptr_t)addr));
		//HDMI20_LINK("Writing for Port[%d] : [0x%08x] <= [0x%08x] \n", port, (unsigned int)dest, (unsigned int)data);
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__ , __L__);
	}
}

static UINT32 __HDMI21_HAL_Rx_LINK_Read(UINT8 port, UINT32 addr)
{
	UINT32 ret;

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_LINK) != 0) { return 0; }

	if(gHDMI21RxHandler[port].linkMem.pSwAddr != NULL){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].linkMem.pSwAddr + (uintptr_t)addr)));
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n", __F__, __L__);
		ret = 0;
	}

	return ret;
}

static void __HDMI21_HAL_Rx_LINK_Write(UINT8 port, UINT32 addr, UINT32 data)
{
	UINT32* dest;

	/* APB Access Mask */
	if((*_pDevApbMask & HDMI21_RX_MISC_APB_MASK_LINK) != 0) { return; }


	if(gHDMI21RxHandler[port].linkMem.pSwAddr != NULL){
		dest = 	((UINT32 *)((uintptr_t)gHDMI21RxHandler[port].linkMem.pSwAddr + (uintptr_t)addr));
		*dest = data;	
	}
	else{
		HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.\n",__F__, __L__);
	}
}

