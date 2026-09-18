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
 *	Closed Caption module control Drivers linux module
 *
 *  author      won.hur (won.hur@lge.com)
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg1132_CC
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

#include "vbi_kapi.h"

#include "vbi_module.h"
#include "vbi_hw.h"
#include "vbi_drv.h"
#include "os_util.h"
#include "vbi_data.h"

#include "sys_regs.h"
#include "../afe/de_cvd_reg.h"
#include "../afe/cvd_module.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PROBLEM_LATCH_UP_WHEN_THIS_PART_IS_ON	1

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	VBI_OFF	0
#define	VBI_ON	1

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

int CC_Hal_HWUninitialize(void);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern volatile DE_CVD_REG_T __iomem *gpRegCVD;
extern volatile DE_CVD_REG_T __iomem *gpRealRegCVD;


/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _CC_Hal_ReadBufferStatus(int *start, int *end, int *count);

static int _CC_Hal_ReadDataWrap(sCloseCaption *ppdata, int *pdata_pointer, int *pstart_inc, unsigned int *pvalid_packet_count);
static int _CC_Hal_ReadDataNormal(sCloseCaption *ppdata, int *pdata_pointer, int *pstart_inc, unsigned int *pvalid_packet_count);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static volatile void *gCC_addr;

static unsigned int	gEnableDebugPrintCCData = 0;
static unsigned int	gEnableDebugPrintCGMSData = 0;
static unsigned int	gEnableDebugPrintWSSData = 0;
//static unsigned int gPrevVline625 = 0xffffffff;

/*========================================================================================
	Implementation Group
========================================================================================*/
//cvd register
int CC_Hal_HWInitialize(void)
{
	int ret = 0;

	CC_PRINT("[%s:%d] Attempting IOREMAPPING address of [0x%08x] with size of [0x%08x]\n", __F__, __L__, gstRegCfgVBI->vbi_register_base, gstRegCfgVBI->vbi_register_size);

	gCC_addr = (volatile void *)ioremap(gstRegCfgVBI->vbi_register_base , gstRegCfgVBI->vbi_register_size);

	if((void *)gCC_addr == NULL){
		CC_PRINT("[%s:%d] Critical Error! Failed IOREMAPPING VBI HW memory IO.\n",__F__, __L__);
		return -1;
	}
	CC_PRINT("[%s:%d] Success IOREMAPPING address of [0x%08x] with size of [0x%08x] to [0x%8p]\n", __F__, __L__, gstRegCfgVBI->vbi_register_base, gstRegCfgVBI->vbi_register_size, gCC_addr);


	CVD_Reg_RdFL(vbi_ctrl_001);
	CVD_Reg_Wr01(vbi_ctrl_001, reg_vbi_little_endian, 1);
	CVD_Reg_WrFL(vbi_ctrl_001);

	//111128 wonsik.do : enabled one bit error ignore from M16Ax revision.
	if( lx_chip_rev( ) >= LX_CHIP_REV(L9,B0) )
	{
		CVD_Reg_RdFL(vbi_004);
		CVD_Reg_Wr01(vbi_004, reg_vbi_st_err_ignored, 1);
		CVD_Reg_WrFL(vbi_004);
	}

	/* 2013.06.27 won.hur : Added code for swrst_cvd_vbi set to 0
	 * There will be no operation in vbi module if this value is not set to 0.
	 * Please be aware of this CTOP register */
#ifdef INCLUDE_M16_CHIP_KDRV
	if( lx_chip_rev( ) <= LX_CHIP_REV(M16,B0) )
	{
		CTOP_CTRL_M16A0_RdFL(CVI_SYN, crg_cvi01);
		CTOP_CTRL_M16A0_Wr01(CVI_SYN, crg_cvi01, swrst_cvd_vbi, 0x0);
		CTOP_CTRL_M16A0_WrFL(CVI_SYN, crg_cvi01);
	}
#endif

	CC_PRINT("%s done\n", __func__);

	return ret;
}

int CC_Hal_HWUninitialize(void)
{
	int ret = 0;

	iounmap((void *)gCC_addr);

	return ret;
}

int CC_Hal_SetInputFormat(eVBIDataType type)
{
	int ret = 0;

	CC_PRINT("%s input : %d\n" , __func__ , type);

	switch(type)
	{
		case eDisable:
			CVD_Reg_RdFL(vbi_004);
			CVD_Reg_Wr01(vbi_004, reg_vbi_en, VBI_OFF);
			CVD_Reg_WrFL(vbi_004);
		break;
		case eClosedCaptionUS:
			CVD_Reg_RdFL(vbi_004);
			CVD_Reg_RdFL(vbi_006);
			CVD_Reg_RdFL(vbi_007);
			CVD_Reg_RdFL(vbi_008);
			CVD_Reg_RdFL(vbi_009);
			CVD_Reg_RdFL(vbi_010);
			CVD_Reg_RdFL(vbi_011);
			CVD_Reg_RdFL(vbi_014);
			CVD_Reg_RdFL(vbi_015);
			CVD_Reg_RdFL(vbi_016);
			CVD_Reg_RdFL(vbi_020);
			CVD_Reg_RdFL(iris_040);

			/* Added for M16Ax on improving performance & bugs... */
			/* 2012.10.22 won.hur */
			CVD_Reg_RdFL(vbi_023);
			CVD_Reg_RdFL(vbi_024);
			CVD_Reg_RdFL(vbi_025);
			CVD_Reg_RdFL(vbi_026);
			CVD_Reg_RdFL(vbi_027);
			CVD_Reg_RdFL(vbi_028);
			CVD_Reg_RdFL(vbi_029);
			CVD_Reg_RdFL(vbi_030);
			CVD_Reg_RdFL(vbi_031);
			CVD_Reg_RdFL(vbi_032);
			CVD_Reg_RdFL(vbi_033);
			CVD_Reg_RdFL(vbi_034);
			CVD_Reg_RdFL(vbi_035);
			CVD_Reg_RdFL(vbi_036);
			CVD_Reg_RdFL(vbi_037);
			CVD_Reg_RdFL(vbi_038);


			CVD_Reg_Wr01(vbi_004, reg_vbi_en, VBI_ON);

			//111130 wonsik.do : disable vbi muxout to prevent vbi data violate video data.
			CVD_Reg_Wr01(vbi_004, reg_vbi_muxout, 0);
			CVD_Reg_Wr(vbi_006, 0xE728);
			CVD_Reg_Wr(vbi_007, 0);
			CVD_Reg_Wr(vbi_008, 0);
			CVD_Reg_Wr(vbi_009, 0);
			//110929 : dws add Line 18, 22 for CC Slicing
			//111014 : dws add Line 24, 25 for CC Slicing(PAL line 21,22 can be inserted on line 24, 25 on NTSC system)
			//111014 : dws removed Line 24, 25 (this is no use)
			CVD_Reg_Wr(vbi_010, 0x1100DD11);
			//CVD_Reg_Wr(vbi_011, 0x11001111);
			CVD_Reg_Wr(vbi_011, 0x11000000);
			//CVD_Reg_Wr(vbi_010, 0x11);
			//CVD_Reg_Wr(vbi_011, 0);
			CVD_Reg_Wr(vbi_014, 0x35A012DB);
			CVD_Reg_Wr(vbi_015, 0x1E2B159A);	// 120531 : won.hur Changed DTO value for CGMS slicing
			//CVD_Reg_Wr(vbi_015, 0x2066159A);
			//CVD_Reg_Wr(vbi_020, 0x54548282);
			CVD_Reg_Wr(vbi_020, 0x5A548282);    // 2011.12.10 won.hur : Changed CC find start h-sync value
			CVD_Reg_Wr01(vbi_016, reg_wss625_frame_start, 0x2);
			CVD_Reg_Wr01(iris_040, reg_vsync_vbi_max, 0x25);

			/* Added for M16Ax on improving performance & bugs... */
			/* 2012.10.22 won.hur */
			CVD_Reg_Wr(vbi_023, 0x5F1B6110);
			CVD_Reg_Wr(vbi_024, 0x32E0222D);
			CVD_Reg_Wr(vbi_025, 0x00000000);
			CVD_Reg_Wr(vbi_026, 0x00000000);
			CVD_Reg_Wr(vbi_027, 0x400006A1);
			CVD_Reg_Wr(vbi_028, 0x400006A1);
			CVD_Reg_Wr(vbi_029, 0x00000000);
			CVD_Reg_Wr(vbi_030, 0x00000000);
			CVD_Reg_Wr(vbi_031, 0x00000000);
			CVD_Reg_Wr(vbi_032, 0x00000000);
			CVD_Reg_Wr(vbi_033, 0x00000000);
			CVD_Reg_Wr(vbi_034, 0x00000000);
			CVD_Reg_Wr(vbi_035, 0x11523001);
			CVD_Reg_Wr(vbi_036, 0x01181113);
			CVD_Reg_Wr(vbi_037, 0x00000001);
			CVD_Reg_Wr(vbi_038, 0x00000111);

			CVD_Reg_WrFL(vbi_023);
			CVD_Reg_WrFL(vbi_024);
			CVD_Reg_WrFL(vbi_025);
			CVD_Reg_WrFL(vbi_026);
			CVD_Reg_WrFL(vbi_027);
			CVD_Reg_WrFL(vbi_028);
			CVD_Reg_WrFL(vbi_029);
			CVD_Reg_WrFL(vbi_030);
			CVD_Reg_WrFL(vbi_031);
			CVD_Reg_WrFL(vbi_032);
			CVD_Reg_WrFL(vbi_033);
			CVD_Reg_WrFL(vbi_034);
			CVD_Reg_WrFL(vbi_035);
			CVD_Reg_WrFL(vbi_036);
			CVD_Reg_WrFL(vbi_037);
			CVD_Reg_WrFL(vbi_038);


			CVD_Reg_WrFL(vbi_004);
			CVD_Reg_WrFL(vbi_007);
			CVD_Reg_WrFL(vbi_008);
			CVD_Reg_WrFL(vbi_009);
			CVD_Reg_WrFL(vbi_010);
			CVD_Reg_WrFL(vbi_011);
			CVD_Reg_WrFL(vbi_006);
			CVD_Reg_WrFL(vbi_020);
			CVD_Reg_WrFL(vbi_014);
			CVD_Reg_WrFL(vbi_015);
			CVD_Reg_WrFL(vbi_016);
			CVD_Reg_WrFL(iris_040);

		break;
		default:

		CC_PRINT("[%s:%d] Error! Unknown CC type for [%d]\n", __F__, __L__, type);
		ret = -1;
		break;
	}

	if(ret >=0) CC_PRINT("%s done\n", __func__);
	return ret;
}


int CC_Hal_SetInterruptClear(void)
{
	int ret = 0;
	UINT32 intr_vp1_en;

	CVD_Reg_RdFL(cvd_intr1_clear0);
	intr_vp1_en = CVD_Reg_Rd(cvd_intr1_clear0);
	CVD_Reg_Wr(cvd_intr1_clear0, (intr_vp1_en |= VBI_INTERRUPT_MASK));
	CVD_Reg_WrFL(cvd_intr1_clear0);

	return ret;
}


int CC_Hal_SetInterrupt(int on_off)
{
	int ret = 0;
	UINT32 intr_vp1_en;

	if(on_off)
	{

		/* 2013.06.27 won.hur : Added code for swrst_cvd_vbi set to 0
		 * There will be no operation in vbi module if this value is not set to 0.
		 * Please be aware of this CTOP register */

#ifdef INCLUDE_M16_CHIP_KDRV
		if( lx_chip_rev( ) <= LX_CHIP_REV(M16,B0) )
		{
			CTOP_CTRL_M16A0_RdFL(CVI_SYN, crg_cvi01);
			CTOP_CTRL_M16A0_Wr01(CVI_SYN, crg_cvi01, swrst_cvd_vbi, 0x0);
			CTOP_CTRL_M16A0_WrFL(CVI_SYN, crg_cvi01);
		}
#endif

		CVD_Reg_RdFL(cvd_intr1_enable1);
		intr_vp1_en = CVD_Reg_Rd(cvd_intr1_enable1);
		CVD_Reg_Wr(cvd_intr1_enable1, (intr_vp1_en |= L9_VBI_INTERRUPT_MASK));
		CVD_Reg_WrFL(cvd_intr1_enable1);
	}
	else{
		CVD_Reg_RdFL(cvd_intr1_enable1);
		intr_vp1_en = CVD_Reg_Rd(cvd_intr1_enable1);
		CVD_Reg_Wr(cvd_intr1_enable1, (intr_vp1_en &= ~L9_VBI_INTERRUPT_MASK));
		CVD_Reg_WrFL(cvd_intr1_enable1);

		VBI_CC_SetInterruptClear();
	}

	return ret;

}


int CC_Hal_ParsingVBIData(unsigned int *packet_array)
{
	int ret = 0;
	unsigned int start, end, count;
	sCloseCaption data[6];	// 5->6 Added to prevent segmentation fault
	unsigned int valid_packet_count;
	unsigned int start_inc;
	int sent_data_count;
	int i;
	int data_pointer = 0;

	start = 0;
	end = 0;
	count = 0;

	ret = _CC_Hal_ReadBufferStatus(&start, &end, &count);

	if(ret != RET_OK)
		return ret;

	if(count > 0x800){
		if(gEnableDebugPrintCCData>0) CC_PRINT("ERROR! HW BUG! CVD VBI sliced data count is over 0x800!\n");
		return -1;
	}
	else
	{
		valid_packet_count = 0;
		start_inc = start * 4;

		if(count > 0) 
			data_pointer = count;
		else 
			data_pointer = 0;

		while(data_pointer >= 1)
		{
			if( ((gstRegCfgVBI->vbi_register_size>>2)*4 - start_inc) < 9)
			{
				_CC_Hal_ReadDataWrap(&data[0], &data_pointer, &start_inc, &valid_packet_count);
			}
			else
			{
				_CC_Hal_ReadDataNormal(&data[0], &data_pointer, &start_inc, &valid_packet_count);
			}
		}

		sent_data_count = 0;

		for(i=0; i<valid_packet_count; i++)
		{
			packet_array[sent_data_count] = ((data[i].LineCount & 0x3FF)<<22)|((data[i].Status & 0x0F)<<16)|(data[i].data1 << 8)|data[i].data0;
			sent_data_count++;
		}

		ret = sent_data_count;
	}

	return ret;
}

int CC_Hal_DebugPrintMode(int mode)
{
	int ret = 0;

	if(mode == 1) 
		gEnableDebugPrintCCData = 1;
	else if(mode == 3)
		gEnableDebugPrintCGMSData = 1;
	else if(mode == 4)
		gEnableDebugPrintWSSData = 1;
	else 
	{
		gEnableDebugPrintCCData = 0;
		gEnableDebugPrintCGMSData = 0;
		gEnableDebugPrintWSSData = 0;
	}
	VBI_PRINT("gEnableDebugPrintCCData:%d, gEnableDebugPrintCGMSData:%d ,gEnableDebugPrintWSSData:%d \n", \
			gEnableDebugPrintCCData, gEnableDebugPrintCGMSData, gEnableDebugPrintWSSData);

	return ret;
}

int CC_Hal_CheckVline625(void)
{
	int ret = RET_OK;
	//unsigned int isVline625;

	return ret;


	/* 2014.02.13 won.hur:
	 * Blocked code from the fact that NTSC TV sets do not support PAL nor SECAM videos */
	#if 0
	CVD_Reg_RdFL(iris_013);
	CVD_Reg_Rd01(iris_013, reg_vline_625, isVline625);

	if(isVline625 != 0)
	{
		if(isVline625 != gPrevVline625)
		{
			gPrevVline625 = isVline625;

			CVD_Reg_RdFL(vbi_010);
			CVD_Reg_RdFL(vbi_011);
			CVD_Reg_RdFL(vbi_015);

			CVD_Reg_Wr(vbi_010, 0x0000DD00);
			CVD_Reg_Wr(vbi_011, 0x000C0000);
			CVD_Reg_Wr(vbi_015, 0x2066159A);

			CVD_Reg_WrFL(vbi_010);
			CVD_Reg_WrFL(vbi_011);
			CVD_Reg_WrFL(vbi_015);

		}
	}
	else
	{
		if(isVline625 != gPrevVline625)
		{
			gPrevVline625 = isVline625;

			CVD_Reg_RdFL(vbi_010);
			CVD_Reg_RdFL(vbi_011);
			CVD_Reg_RdFL(vbi_015);

			CVD_Reg_Wr(vbi_010, 0x1100DD11);
			CVD_Reg_Wr(vbi_011, 0x11000000);
			CVD_Reg_Wr(vbi_015, 0x1E2B159A);

			CVD_Reg_WrFL(vbi_010);
			CVD_Reg_WrFL(vbi_011);
			CVD_Reg_WrFL(vbi_015);
		}
	}

	return ret;
	#endif
}

int CC_Hal_CheckAnalogCP(void)
{
	LX_VBI_CP_TYPE_T ret = RET_ERROR;	// NULL value for init value.
	unsigned int analog_cp_psync;
	unsigned int analog_cp_cstripe;
	unsigned int cur_hlock, cur_vlock;

	/* Get Lock info */
	CVD_Reg_RdFL(iris_001);
	CVD_Reg_Rd01(iris_001, reg_hlock, cur_hlock);
	CVD_Reg_RdFL(iris_001);
	CVD_Reg_Rd01(iris_001, reg_vlock, cur_vlock);

	/* Get CP infro */
	CVD_Reg_RdFL(iris_001);
	CVD_Reg_Rd01(iris_001, reg_mv_vbi_detected, analog_cp_psync);
	CVD_Reg_Rd01(iris_001, reg_mv_colourstripes, analog_cp_cstripe);

	do{
		ret = 0; 	// Initiate return value

		if((analog_cp_psync == 0)||(cur_hlock == 0)||(cur_vlock == 0))
		{
			ret = 0;
			break;
		}
		else {
			ret = (ret)|(LX_VBI_CP_TYPE_ANALOG_1);
		}

		/* DO NOT USE CSTRIPE INFO!
		 * CVD CP CSTRIPE HW DOES NOT WORK PROPERLY!! */
		//if(analog_cp_cstripe) ret = (ret)|(LX_VBI_CP_TYPE_ANALOG_2);
	}while(0);

	if(gEnableDebugPrintCCData){
//		VBI_PRINT("[%s] ret[0x%x] PSYNC[0x%x],CS[0x%x], Hlock[%d] Vlock[%d]\n", __F__, ret, analog_cp_psync, analog_cp_cstripe, cur_hlock, cur_vlock);
	}

	return (int)ret;
}

#ifdef	KDRV_CONFIG_PM

int CC_Hal_RunSuspend(void)
{
	// param will be saved automatically....
	return 0;
}

int CC_Hal_RunResume(void)
{
	CC_PRINT("[%s:%d] Resume phase #1\n", __F__, __L__);

	CVD_Reg_RdFL(vbi_ctrl_001);
	CVD_Reg_Wr01(vbi_ctrl_001, reg_vbi_little_endian, 1);
	CVD_Reg_WrFL(vbi_ctrl_001);

	//111128 wonsik.do : enabled one bit error ignore from M16Ax revision.
	if( lx_chip_rev( ) >= LX_CHIP_REV(L9,B0) )
	{
		CVD_Reg_RdFL(vbi_004);
		CVD_Reg_Wr01(vbi_004, reg_vbi_st_err_ignored, 1);
		CVD_Reg_WrFL(vbi_004);
	}

	/* 2013.06.27 won.hur : Added code for swrst_cvd_vbi set to 0
	 * There will be no operation in vbi module if this value is not set to 0.
	 * Please be aware of this CTOP register */
#ifdef INCLUDE_M16_CHIP_KDRV
	if( lx_chip_rev( ) <= LX_CHIP_REV(M16,B0) )
	{
		CTOP_CTRL_M16A0_RdFL(CVI_SYN, crg_cvi01);
		CTOP_CTRL_M16A0_Wr01(CVI_SYN, crg_cvi01, swrst_cvd_vbi, 0x0);
		CTOP_CTRL_M16A0_WrFL(CVI_SYN, crg_cvi01);
	}
#endif

	CC_Hal_SetInputFormat(eClosedCaptionUS);

	CC_PRINT("[%s:%d] Done \n", __F__, __L__);

	return 0;
}

#endif

static int _CC_Hal_ReadBufferStatus(int *start, int *end, int *count)
{
	int ret = RET_OK;
	unsigned int buffer_number;

	CVD_Reg_RdFL(vbi_ctrl_002);
	CVD_Reg_Rd01(vbi_ctrl_002, reg_vbi_buffer_number, buffer_number);

	switch(buffer_number)
	{
		case 0:
			CVD_Reg_RdFL(vbi_ctrl_002);
			CVD_Reg_RdFL(vbi_ctrl_003);

			CVD_Reg_Rd01(vbi_ctrl_002, reg_vbi0_start_addr, *start);
			CVD_Reg_Rd01(vbi_ctrl_003, reg_vbi0_end_addr, *end);
			CVD_Reg_Rd01(vbi_ctrl_002, reg_vbi0_data_cnt, *count);

			break;
		case 1:
			CVD_Reg_RdFL(vbi_ctrl_004);
			CVD_Reg_RdFL(vbi_ctrl_005);

			CVD_Reg_Rd01(vbi_ctrl_004, reg_vbi1_start_addr, *start);
			CVD_Reg_Rd01(vbi_ctrl_005, reg_vbi1_end_addr, *end);
			CVD_Reg_Rd01(vbi_ctrl_004, reg_vbi1_data_cnt, *count);

			break;
		case 2:
			CVD_Reg_RdFL(vbi_ctrl_006);
			CVD_Reg_RdFL(vbi_ctrl_007);

			CVD_Reg_Rd01(vbi_ctrl_006, reg_vbi2_start_addr, *start);
			CVD_Reg_Rd01(vbi_ctrl_007, reg_vbi2_end_addr, *end);
			CVD_Reg_Rd01(vbi_ctrl_006, reg_vbi2_data_cnt, *count);

			break;
		case 3:
			CVD_Reg_RdFL(vbi_ctrl_008);
			CVD_Reg_RdFL(vbi_ctrl_009);

			CVD_Reg_Rd01(vbi_ctrl_008, reg_vbi3_start_addr, *start);
			CVD_Reg_Rd01(vbi_ctrl_009, reg_vbi3_end_addr, *end);
			CVD_Reg_Rd01(vbi_ctrl_008, reg_vbi3_data_cnt, *count);

			break;
		default:
			ret = RET_ERROR;
			break;
	}
	return ret;
}

static int _CC_Hal_ReadDataWrap(sCloseCaption *ppdata, int *pdata_pointer, int *pstart_inc, unsigned int *pvalid_packet_count)
{
	unsigned int first_bytes, second_bytes;
	unsigned char vbi_data_type = 0x00;
	unsigned char *addr;
	sCGMS cgms_data;
	int i;

	first_bytes = ((gstRegCfgVBI->vbi_register_size>>2)*4 - *pstart_inc);

	if(first_bytes >= 4) 
		vbi_data_type = (unsigned char)(*(unsigned int *)(gCC_addr + *pstart_inc + 3));
	else 
		vbi_data_type = (unsigned char)(*(unsigned int *)(gCC_addr + 3 - first_bytes));

	/* For Closed Caption Data */
	if((vbi_data_type == 0x00) || (vbi_data_type == 0x01))
	{
		second_bytes = 9 - first_bytes;

		addr = (unsigned char *)(ppdata + *pvalid_packet_count);
		*pvalid_packet_count += 1;

		memcpy_fromio((void *)addr , (void *)((uintptr_t)gCC_addr + (uintptr_t)*pstart_inc ) , first_bytes );
		memcpy_fromio((void *)((uintptr_t)addr + (uintptr_t)first_bytes), (void *)(gCC_addr) ,second_bytes );

		if(gEnableDebugPrintCCData>0)
		{
			//printk("CC_MESSAGE_A= first[%d], second[%d], start_inc[0x%x]\n", first_bytes, second_bytes, *pstart_inc);
			printk("CC_MESSAGE_a start_inc[0x%4x]", *pstart_inc);
			for(i=0; i<9; i++) 
			{
				printk(" %2x",(unsigned char )(*(unsigned char *)(addr + i)));
			}
			printk("\n");
		}

		*pstart_inc = second_bytes;
		*pdata_pointer -= 9;
	}
	/* For CGMS data on 20 line */
	else if((vbi_data_type == 0x0A) || (vbi_data_type == 0x0B))
	{
		second_bytes = 10 - first_bytes;
#if PROBLEM_LATCH_UP_WHEN_THIS_PART_IS_ON
		memcpy_fromio((void *)&cgms_data, (void *)((uintptr_t)gCC_addr + (uintptr_t)*pstart_inc ) , first_bytes );
		memcpy_fromio((void *)((uintptr_t)&cgms_data + (uintptr_t)first_bytes), (void *)(gCC_addr) ,second_bytes );

		if(gEnableDebugPrintCGMSData>0)
		{
			//printk("CC_MESSAGE_B= %4d %4d %4d", start, end, count);
			printk("CG_MESSAGE_b start_inc[0x%4x]", *pstart_inc);
			/*
			for(i=0; i<first_bytes; i++) 
				printk(" %2x", (unsigned char )(*(unsigned int *)(gCC_addr + *pstart_inc + i)));
			for(i=0; i<second_bytes; i++) 
				printk(" %2x", (unsigned char )(*(unsigned int *)(gCC_addr + i)));
				*/
			for(i=0; i<10 ; i++) 
			{
				printk(" %2x",(unsigned char )*(((unsigned char *)&cgms_data) + i));
			}
			printk("\n");
		}

		VBI_PutCGMSData(&cgms_data);
#endif
		*pstart_inc = second_bytes;
		*pdata_pointer -= 10;
	}
	/* Exception case for WSS when 625i video input to CVD module */
	else if((vbi_data_type == 0x08) || (vbi_data_type == 0x09))
	{
		second_bytes = 9 - first_bytes;
#if PROBLEM_LATCH_UP_WHEN_THIS_PART_IS_ON
		memcpy_fromio((void *)&cgms_data, (void *)((uintptr_t)gCC_addr + (uintptr_t)*pstart_inc ) , first_bytes );
		memcpy_fromio((void *)((uintptr_t)&cgms_data + (uintptr_t)first_bytes), (void *)(gCC_addr) ,second_bytes );

		if(gEnableDebugPrintWSSData>0)
		{
			//printk("CC_MESSAGE_C= %4d %4d %4d", start, end, count);
			printk("WS_MESSAGE_c start_inc[0x%4x]", *pstart_inc);
			for(i=0; i<first_bytes; i++) 
			{
				printk(" %2x", (unsigned char )(*(unsigned int *)(gCC_addr + *pstart_inc + i)));
			}
			for(i=0; i<second_bytes; i++) 
			{
				printk(" %2x", (unsigned char )(*(unsigned int *)(gCC_addr + i)));
			}
			printk("\n");
		}

		VBI_PutCGMSData(&cgms_data);
#endif
		*pstart_inc = second_bytes;
		*pdata_pointer -= 9;
	}
	else
	{
		CC_PRINT("VBI CC : WARNING UNKNOWN VBI DATA CAME!! VBI DATA TYPE IS [0x%2x]!\n", vbi_data_type);
		*pdata_pointer = 0;	// Get out of while loop.
	}

	return RET_OK;
}

static int _CC_Hal_ReadDataNormal(sCloseCaption *ppdata, int *pdata_pointer, int *pstart_inc, unsigned int *pvalid_packet_count)
{
	unsigned char vbi_data_type = 0x00;
	sCGMS cgms_data;
	int i;

	vbi_data_type = *(unsigned char*)((uintptr_t)gCC_addr + (uintptr_t)(*pstart_inc + 3) );

	if((vbi_data_type == 0x00) || (vbi_data_type == 0x01))
	{
		memcpy_fromio((void *)&ppdata[*pvalid_packet_count], (void *)((uintptr_t)gCC_addr + (uintptr_t)(*pstart_inc) ) , 9);

		if(gEnableDebugPrintCCData>0)
		{
//			printk("CC_MESSAGE_A= %4d %4d %4d", start, end, count);
			printk("CC_MESSAGE_A start_inc[0x%4x]", *pstart_inc);
			for(i=0; i<9; i++) { printk(" %2x",(unsigned char )(*(unsigned int *)(gCC_addr + *pstart_inc + i))); }
			printk("\n");
		}

		*pvalid_packet_count += 1;

		*pstart_inc += 9;
		*pdata_pointer -= 9;
	}
	else if((vbi_data_type == 0x0A) || (vbi_data_type == 0x0B))
	{
		/* Exception */
		if(((gstRegCfgVBI->vbi_register_size>>2)*4 - *pstart_inc) == 9)
		{
			memcpy_fromio((void *)&cgms_data, (void *)((uintptr_t)gCC_addr + (uintptr_t)*pstart_inc ) , 9);
			memcpy_fromio((void *)&cgms_data, (void *)(gCC_addr), 1);

			if(gEnableDebugPrintCCData>0)
			{
				printk("cc_message_B start_inc[0x%4x]", *pstart_inc);
				for(i=0; i< 10; i++) { printk(" %2x",(unsigned char )(*(unsigned int *)((uintptr_t)gCC_addr + (uintptr_t)(*pstart_inc + i)))); }
				printk("\n");
			}
		}
		else
		{

			memcpy_fromio((void *)&cgms_data, (void *)((uintptr_t)gCC_addr + (uintptr_t)*pstart_inc ) , 10);

			if(gEnableDebugPrintCGMSData>0)
			{
				printk("CC_MESSAGE_B start_inc[0x%4x]", *pstart_inc);
				for(i=0; i<10 ; i++) 
				{
					printk(" %2x",(unsigned char )*(((unsigned char *)&cgms_data) + i));
				}
				printk("\n");
			}
		}
		VBI_PutCGMSData(&cgms_data);

		*pstart_inc += 10;
		*pdata_pointer -= 10;
	}
	else if((vbi_data_type == 0x08) || (vbi_data_type == 0x09))
	{
		memcpy_fromio((void *)&cgms_data, (void *)((uintptr_t)gCC_addr + (uintptr_t)(*pstart_inc) ) , 9 );
		VBI_PutCGMSData(&cgms_data);

		if(gEnableDebugPrintWSSData>0)
		{
			//printk("CC_MESSAGE_C= %4d %4d %4d", start, end, count);
			printk("WS_MESSAGE_C start_inc[0x%4x]", *pstart_inc);
			for(i=0; i< 9; i++) 
			{
				printk(" %2x",(unsigned char )(*(unsigned int *)((uintptr_t)gCC_addr + (uintptr_t)(*pstart_inc + i) )));
			}
			printk("\n");
		}

		*pstart_inc += 9;
		*pdata_pointer -= 9;
	}
	else
	{
		//CC_PRINT("VBI CC : WARNING UNKNOWN VBI DATA CAME!! VBI DATA TYPE IS [0x%2x]!\n", vbi_data_type);
		*pdata_pointer = 0; // Get out of while loop
	}

	return RET_OK;
}
/** @} */
